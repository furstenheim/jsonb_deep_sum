CREATE EXTENSION jsonb_deep_sum;
SELECT jsonb_deep_add('{"a": 2, "b": 1}', '{"a": 5}');
SELECT jsonb_deep_add('{"a": 2, "b": 3}', '{"a": 5, "b": 4}');
-- Objects with keys in different order
SELECT jsonb_deep_add('{"b": 2, "a": 3}', '{"a": 5, "b": 4}');
-- LHS key greater than RHS
SELECT jsonb_deep_add('{"b": 1}', '{"a": 2}');
-- RHS key greater than LHS
SELECT jsonb_deep_add('{"a": 2}', '{"b": 1}');
-- empty object
SELECT jsonb_deep_add('{}', '{"a": 2}');
-- not an object
SELECT jsonb_deep_add('1', '{"a": 1}');
-- NULL object
SELECT jsonb_deep_add(NULL, '{"a": 1}');
SELECT jsonb_deep_add('{"a": "bb"}', '{"b": 1}');
-- Nested and independent
SELECT jsonb_deep_add('{"a": {"a": 1}}', '{"b": 1}');
-- Deeply nested and independent
SELECT jsonb_deep_add('{"a": {"a": {"a": 1}}}', '{"b": 1}');
-- Nested reverse order
SELECT jsonb_deep_add('{"b": 1}', '{"a": {"a": 1}}');
-- Nested sum
SELECT jsonb_deep_add('{"a": {"a": 1}}', '{"a": {"a": 2}}');
-- Nested sum and additional property
SELECT jsonb_deep_add('{"a": {"a": 1}, "b": 1}', '{"a": {"a": 2}}');
-- Reversed nested sum and additional prooperty
SELECT jsonb_deep_add('{"a": {"a": 1}}', '{"a": {"a": 2}, "b": 1}');
-- Deeply nested sum
SELECT jsonb_deep_add('{"a": {"a": {"a": 4}}}', '{"a": {"a": {"a": 3}}}');
SELECT jsonb_deep_add('{"a": true}', '{"b": 1}');
SELECT jsonb_deep_add('{"a": [1, 2, 3,4]}', '{"b": 1}');
-- Incompatible objects
SELECT jsonb_deep_add('{"a": {"a": 1}}', '{"a": 1}');
SELECT jsonb_deep_add('{"a": 1}', '{"a": {"a": 1}}');


