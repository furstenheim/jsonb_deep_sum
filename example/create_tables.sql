DROP TABLE IF EXISTS test_table;
CREATE TABLE test_table (id serial, info jsonb);

-- One level nesting
INSERT INTO test_table (info) SELECT 
    jsonb_build_object(
        substr('abcd', trunc(random()*4)::integer + 1, 1), random(), 
        substr('efgh', trunc(random()*4)::integer + 1, 1), random()
    ) FROM generate_series(1, 2*1000*1000);


SELECT jsonb_deep_sum(info) from test_table;

--- Time: 3705,791 ms


-- Two levels nesting

DROP TABLE IF EXISTS test_table;
CREATE TABLE test_table (id serial, info jsonb);
INSERT INTO test_table (info) SELECT
    jsonb_build_object(
        substr('abcd', trunc(random()*4)::integer + 1, 1), 
            jsonb_build_object('a', random(), 'b', random(), 'c', random()),
        substr('efgh', trunc(random()*4)::integer + 1, 1), 
            jsonb_build_object('a', random(), 'b', random(), 'c', random())  
    ) FROM generate_series(1, 2*1000*1000);


SELECT jsonb_deep_sum(info) from test_table;
-- Time: 12014,711 ms
