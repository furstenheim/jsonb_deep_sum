\echo Use "Create extension json_deep_sum to load this file. \quit

CREATE FUNCTION jsonb_deep_add (jsonb, jsonb)
RETURNS jsonb 
AS '$libdir/jsonb_deep_sum'
LANGUAGE C IMMUTABLE STRICT;

CREATE AGGREGATE jsonb_deep_sum (jsonb)
(
    sfunc = jsonb_deep_add,
    stype = jsonb,
    initcond = '{}'
);


