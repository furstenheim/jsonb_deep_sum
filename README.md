## Jsonb deep sum

jsonb_deep_sum is a PostgreSQL extension to easily add jsonb numeric

    SELECT jsonb_deep_add('{"a": 1}', {"a": 2}');
    > '{"a": 3}'
    
    SELECT jsonb_deep_add('{"a": {"b": 1}}', '{"a": {"b": 1}}')
    > '{"a": {"b": 2}}'
    
It also provides an aggregation function `jsonb_deep_sum`
    
## INSTALLATION
    
In the directory where you downloaded jsonb_deep_sum, run

    make && make install
    
Make install will copy the extension files to the postgres folder, so make sure that you have the necessary permissions.
It might also happen that pgxs is not found. For that you might need to install postgresql-server-dev-all and postgresql-common [[link](https://github.com/travis-ci/travis-ci/issues/2864)].


Once you have successfully compiled the extension log into postgresql and do:

    CREATE EXTENSION jsonb_deep_sum;
    


## EXAMPLE

    CREATE TABLE simple_nested (data jsonb);
    INSERT INTO simple_nested VALUES ('{"a": 1}'), ('{"a": 2, "b": 1}'), ('{"a": 5}'), ('{"a": 3, "b": 1}'), (NULL);
    SELECT jsonb_deep_sum(data) FROM simple_nested;
    > {"a": 11, "b": 2}


## TESTING

To run the tests use:

    make install && make installcheck

All the tests are in the sql directory.

## BENCHMARKING

The exact queries can be found in `./example`

| Numbers of rows | Level of nesting |  jsonb_deep_sum (ms) | SQL (ms)
| --------------- | ---------------- | --------------- | ------- |
| 2 million       | 0   | 3705,791 |  11083,089 |
| 2 million | 1 | 12014,711 | ?


It would be nice to have benchmarks using custom sql aggregate, using PL/V8 and storing the info in plain columns à la hstore.

## INTERNALS

JSONB is internall represented as a tree in which all levels are sorted.
 Postgres provides iterators to walk this tree in DFS which respects this sorting. The algorithm uses this order to perform a [sorted merge join](https://en.wikipedia.org/wiki/Sort-merge_join).
  
  
## LIMITATIONS

Right now the algorithm only allows numeric types and objects. If nulls, strings, arrays or booleans are present it will raise an error.
In the future I might change this so that nulls is ignored in the sum or that strings are kept. Arrays are not supported because there isn't an obvious way to merge them.
