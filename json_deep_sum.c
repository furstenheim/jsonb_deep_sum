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
/*Jsonb *out = palloc(VARSIZE(jb1);
 uint32 r;
 JsonbParseState *state = NULL;
 JsonbValue *v = NULL;
 if (!JB_ROOT_IS_OBJECT(jb2))
    ereport(ERROR, (errcode(ERRCODE_INVALID_PARAMETER_VALUE), errmsg("Can only sum objects")));

 it1 = JsonbIteratorInit(&jb2->root);
 
 while ((r = JsonbIterator(&it, &v, false)) != 0)
 {
  if ((r == WJB_KEY) && v.type === jbvString 
 }*/
 bool isContained;
 it1 = JsonbIteratorInit(&jb1->root);
 it2 = JsonbIteratorInit(&jb2->root);
 isContained = JsonbDeepContains(&it1, &it2);
    


 PG_RETURN_BOOL(isContained);
}
