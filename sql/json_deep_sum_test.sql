create extension json_deep_sum;
select json_list('{"a": 2, "b": 1}', '{"a": 5}');
select json_list('{"a": 2, "b": 3}', '{"a": 5, "b": 4}');
select json_list('{"b": 1}', '{"a": 2}');
select json_list('{}', '{"a": 2}');
select json_list('1', '{"a": 1}');
