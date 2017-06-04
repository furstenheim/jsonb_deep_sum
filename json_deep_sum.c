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
 Jsonb *jb = PG_GETARG_JSONB(0);

 PG_RETURN_INT16(1);
}
