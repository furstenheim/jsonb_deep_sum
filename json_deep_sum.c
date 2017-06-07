#include "postgres.h"
#include "catalog/pg_type.h"
#include "fmgr.h"
#include "utils/builtins.h"
#include "utils/jsonb.h"
PG_MODULE_MAGIC;

PG_FUNCTION_INFO_V1(json_list);
Datum
json_list(PG_FUNCTION_ARGS)
{
 Jsonb *jb1 = PG_GETARG_JSONB(0);
 Jsonb *jb2 = PG_GETARG_JSONB(1);
 JsonbIterator *it1, *it2;
 JsonbValue v1, v2;
 JsonbIteratorToken r1, r2;
 JsonbValue *res;
 JsonbParseState *state = NULL; // Here we create the new jsonb

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
 pushJsonbValue(&state, WJB_BEGIN_OBJECT, NULL);
 res = pushJsonbValue(&state, WJB_END_OBJECT, NULL);

 PG_RETURN_JSONB(JsonbValueToJsonb(res));
 /* pushJsonbValue(state, r1, NULL); // Start object
 r1 = JsonbIteratorNext(&it1, &v1, true);
 r2 = JsonbIteratorNext(&it2, &v2, true);
 PG_RETURN_NULL();
 
 
 while (r1 != WJB_END_OBJECT || r2 != WJB_END_OBJECT)
 {
  if (r1 == WJB_END_OBJECT) {
    pushJsonbValue(state, r2, &v2);
    r2 = JsonbIteratorNext(&it2, &v2, true);
    continue;
  }
  if (r2 == WJB_END_OBJECT) {
    pushJsonbValue(state, r1, &v1);
    r1 = JsonbIteratorNext(&it1, &v1, true);
    continue;
  }
  
    r2 = JsonbIteratorNext(&it2, &v2, true);
    r1 = JsonbIteratorNext(&it1, &v1, true);
 }

 res = pushJsonbValue(state, WJB_END_OBJECT, NULL);
 
 Assert(res != NULL);

 PG_RETURN_JSONB(JsonbValueToJsonb(res));

*/
}
