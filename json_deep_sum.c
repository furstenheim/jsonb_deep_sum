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
 text *key;
 JsonbValue *v;
 JsonbValue kval;
 key = cstring_to_text("a");

 kval.type = jbvString;
 kval.val.string.val = VARDATA_ANY(key);
 kval.val.string.len = VARSIZE_ANY_EXHDR(key);
 if (!JB_ROOT_IS_OBJECT(jb1))
     PG_RETURN_NULL();

 v = findJsonbValueFromContainer(&jb1->root, JB_FOBJECT, &kval);

 if (v != NULL)
    PG_RETURN_JSONB(JsonbValueToJsonb(v));
 PG_RETURN_NULL();
}
