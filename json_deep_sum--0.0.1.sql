\echo Use "Create extension json_deep_sum to load this file. \quit

create function json_list(mjson jsonb)
Returns integer 
as '$libdir/json_deep_sum'
language c immutable strict;
