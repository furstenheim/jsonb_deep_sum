\echo Use "Create extension json_deep_sum to load this file. \quit

create function jsonb_deep_add(jsonb, jsonb)
Returns jsonb 
as '$libdir/jsonb_deep_sum'
language c immutable strict;
