CREATE TABLE simple_nested (data jsonb);
INSERT INTO simple_nested VALUES ('{"a": 1}'), ('{"a": 2, "b": 1}'), ('{"a": 5}'), ('{"a": 3, "b": 1}'), (NULL);
SELECT jsonb_deep_sum(data) FROM simple_nested;

