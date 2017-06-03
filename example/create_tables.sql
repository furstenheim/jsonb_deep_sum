create table test_table (id serial, info json);

insert into test_table (info) select json_build_object(substr('abcd', trunc(random()*4)::integer + 1, 1), random(), substr('efgh', trunc(random()*4)::integer + 1, 1), random()) from generate_series(1, 200000);

