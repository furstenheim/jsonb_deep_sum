#include "postgres.h"
#include "catalog/pg_type.h"
#include "fmgr.h"
#include "utils/builtins.h"
#include "utils/jsonb.h"
PG_MODULE_MAGIC;

/* Taken from src/backend/adt/jsonb_utils.c
 * Compare two jbvString JsonbValue values, a and b.
 *
 * This is a special qsort() comparator used to sort strings in certain
 * internal contexts where it is sufficient to have a well-defined sort order.
 * In particular, object pair keys are sorted according to this criteria to
 * facilitate cheap binary searches where we don't care about lexical sort
 * order.
 *
 * a and b are first sorted based on their length.  If a tie-breaker is
 * required, only then do we consider string binary equality.
 */
static int
lengthCompareJsonbStringValue(const void *a, const void *b)
{
    const JsonbValue *va = (const JsonbValue *) a;
    const JsonbValue *vb = (const JsonbValue *) b;
    int                 res;

    Assert(va->type == jbvString);
    Assert(vb->type == jbvString);

    if (va->val.string.len == vb->val.string.len)
    {
        res = memcmp(va->val.string.val, vb->val.string.val, va->val.string.len);
    }
    else
    {
        res = (va->val.string.len > vb->val.string.len) ? 1 : -1;
    }

    return res;
}



PG_FUNCTION_INFO_V1(jsonb_deep_add);
Datum
jsonb_deep_add(PG_FUNCTION_ARGS)
{
 Jsonb *jb1 = PG_GETARG_JSONB(0);
 Jsonb *jb2 = PG_GETARG_JSONB(1);
 JsonbIterator *it1, *it2;
 JsonbValue v1, v2;
 JsonbIteratorToken r1, r2;
 JsonbValue *res;
 JsonbParseState *state = NULL; // Here we create the new jsonb
 int nestedLevel = 0;
 if (jb1 == NULL)
     PG_RETURN_JSONB(jb2);
 if (jb2 == NULL)
     PG_RETURN_JSONB(jb1);

 if (!JB_ROOT_IS_OBJECT(jb1) || !JB_ROOT_IS_OBJECT(jb2))
        ereport(ERROR, (errcode(ERRCODE_INVALID_PARAMETER_VALUE), errmsg("Can only sum objects")));


 it1 = JsonbIteratorInit(&jb1 -> root);
 it2 = JsonbIteratorInit(&jb2 -> root);

 r1 = JsonbIteratorNext(&it1, &v1, false);
 r2 = JsonbIteratorNext(&it2, &v2, false);

 if (r1 != WJB_BEGIN_OBJECT || r2 != WJB_BEGIN_OBJECT)
        ereport(ERROR, (errcode(ERRCODE_INVALID_PARAMETER_VALUE), errmsg("Iterator was not an object")));

 pushJsonbValue(&state, r1, NULL); // Start object
 r1 = JsonbIteratorNext(&it1, &v1, false);
 r2 = JsonbIteratorNext(&it2, &v2, false);
 
 while (!(r1 == WJB_END_OBJECT && r2 == WJB_END_OBJECT && nestedLevel == 0))
 {
   int difference;
 //  Datum sum;
   JsonbValue newValue; 
  if (r1 == WJB_END_OBJECT && r2 == WJB_END_OBJECT && nestedLevel > 0) {
    pushJsonbValue(&state, WJB_END_OBJECT, NULL);
    r1 = JsonbIteratorNext(&it1, &v1, false);
    r2 = JsonbIteratorNext(&it2, &v2, false);
    nestedLevel--;   
    continue;
  }
  if (r1 == WJB_END_OBJECT) {
    pushJsonbValue(&state, r2, &v2);
    r2 = JsonbIteratorNext(&it2, &v2, true);
    continue;
  }
  if (r2 == WJB_END_OBJECT) {
    pushJsonbValue(&state, r1, &v1);
    r1 = JsonbIteratorNext(&it1, &v1, true);
    continue;
  }
   difference = lengthCompareJsonbStringValue(&v1, &v2);
 // first key is smaller
 if (difference < 0) {
  pushJsonbValue(&state, r1, &v1);
  r1 = JsonbIteratorNext(&it1, &v1, true);
 // jbvBinary is returned in skipNested mode
  if ((&v1)->type == jbvNumeric || (&v1)->type == jbvBinary) {
    pushJsonbValue(&state, r1, &v1);
  } else {
  ereport(ERROR, (errcode(ERRCODE_INVALID_PARAMETER_VALUE), errmsg("Only numeric values allowed")));
  }
  r1 = JsonbIteratorNext(&it1, &v1, true);
  continue;
 } else if (difference > 0) {
  pushJsonbValue(&state, r2, &v2);
  r2 = JsonbIteratorNext(&it2, &v2, true);

  if ((&v2)->type == jbvNumeric || (&v2)->type == jbvBinary) {
    pushJsonbValue(&state, r2, &v2);
  } else {
  ereport(ERROR, (errcode(ERRCODE_INVALID_PARAMETER_VALUE), errmsg("Only numeric values allowed")));
  }
  r2 = JsonbIteratorNext(&it2, &v2, true);
  continue;
 }   
 pushJsonbValue(&state, r1, &v1);
 r2 = JsonbIteratorNext(&it2, &v2, false);
 r1 = JsonbIteratorNext(&it1, &v1,false);
 if ((&v1)->type == jbvNumeric && (&v2)->type == jbvNumeric) {
   // TODO jbvString, jbvNull and jbvBool
     newValue.type = jbvNumeric;
 
     newValue.val.numeric = DatumGetNumeric((DirectFunctionCall2(numeric_add, PointerGetDatum(
        (&v1)->val.numeric), PointerGetDatum((&v2)->val.numeric))));

     pushJsonbValue(&state, WJB_VALUE, &newValue);
 } else if ((&v1)->type == jbvObject && (&v2)->type == jbvObject) {
   pushJsonbValue(&state, WJB_BEGIN_OBJECT, NULL);
   nestedLevel++;   
 } else {
   ereport(ERROR, (errcode(ERRCODE_INVALID_PARAMETER_VALUE), errmsg("Only numeric values allowed")));
 }
 r2 = JsonbIteratorNext(&it2, &v2, false);
 r1 = JsonbIteratorNext(&it1, &v1, false);

 }

 res = pushJsonbValue(&state, WJB_END_OBJECT, NULL);
 
 Assert(res != NULL);

 PG_RETURN_JSONB(JsonbValueToJsonb(res));


}
