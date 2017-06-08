create extension jsonb_deep_sum;
select jsonb_deep_add('{"a": 2, "b": 1}', '{"a": 5}');
select jsonb_deep_add('{"a": 2, "b": 3}', '{"a": 5, "b": 4}');
select jsonb_deep_add('{"b": 1}', '{"a": 2}');
select jsonb_deep_add('{}', '{"a": 2}');
select jsonb_deep_add('1', '{"a": 1}');
select jsonb_deep_add('{"a": "bb"}', '{"b": 1}');
select jsonb_deep_add('{"a": {"a": 1}}', '{"b": 1}');
select jsonb_deep_add('{"a": {"a": 1}}', '{"a": {"a": 2}}');
select jsonb_deep_add('{"a": true}', '{"b": 1}');
select jsonb_deep_add('{"a": [1, 2, 3,4]}', '{"b": 1}');
select jsonb_deep_add('{"a": {"a": 1}}', '{"a": 1}');


