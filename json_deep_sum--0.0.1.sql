\echo Use "Create extension json_deep_sum to load this file. \quit

create function json_list(mjson json)
Returns json
language plpgsql immutable strict
 as $$
   begin
     return mjson->'a';
   end;
 $$;
