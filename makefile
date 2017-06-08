EXTENSION = jsonb_deep_sum
DATA = jsonb_deep_sum--0.0.1.sql
REGRESS	 = jsonb_deep_sum_test
MODULES = jsonb_deep_sum

# postgres stuff
PG_CONFIG = pg_config
PGXS := $(shell $(PG_CONFIG) --pgxs)
include $(PGXS)
