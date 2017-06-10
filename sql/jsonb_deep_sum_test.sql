create extension jsonb_deep_sum;
select jsonb_deep_add('{"a": 2, "b": 1}', '{"a": 5}');
select jsonb_deep_add('{"a": 2, "b": 3}', '{"a": 5, "b": 4}');
-- Objects with keys in different order
select jsonb_deep_add('{"b": 2, "a": 3}', '{"a": 5, "b": 4}');
-- LHS key greater than RHS
select jsonb_deep_add('{"b": 1}', '{"a": 2}');
-- RHS key greater than LHS
select jsonb_deep_add('{"a": 2}', '{"b": 1}');
-- empty object
select jsonb_deep_add('{}', '{"a": 2}');
-- not an object
select jsonb_deep_add('1', '{"a": 1}');
-- NULL object
select jsonb_deep_add(NULL, '{"a": 1}');
select jsonb_deep_add('{"a": "bb"}', '{"b": 1}');
-- Nested and independent
select jsonb_deep_add('{"a": {"a": 1}}', '{"b": 1}');
-- Deeply nested and independent
select jsonb_deep_add('{"a": {"a": {"a": 1}}}', '{"b": 1}');
-- Nested reverse order
select jsonb_deep_add('{"b": 1}', '{"a": {"a": 1}}');
-- Nested sum
select jsonb_deep_add('{"a": {"a": 1}}', '{"a": {"a": 2}}');
-- Nested sum and additional property
select jsonb_deep_add('{"a": {"a": 1}, "b": 1}', '{"a": {"a": 2}}');
-- Reversed nested sum and additional prooperty
select jsonb_deep_add('{"a": {"a": 1}}', '{"a": {"a": 2}, "b": 1}');
-- Deeply nested sum
select jsonb_deep_add('{"a": {"a": {"a": 4}}}', '{"a": {"a": {"a": 3}}}');
select jsonb_deep_add('{"a": true}', '{"b": 1}');
select jsonb_deep_add('{"a": [1, 2, 3,4]}', '{"b": 1}');
-- Incompatible objects
select jsonb_deep_add('{"a": {"a": 1}}', '{"a": 1}');
select jsonb_deep_add('{"a": 1}', '{"a": {"a": 1}}');


