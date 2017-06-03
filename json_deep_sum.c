#include "postgres.h"
#include "fmgr.h"
#include "utils/builtins.h"


PG_MODULE_MAGIC;

PG_FUNCTION_INFO_V1(json_deep_sum);
Datum
json_list(PG_FUNCTION_ARGS)
{
 PG_RETURN_INT16(1);
}
