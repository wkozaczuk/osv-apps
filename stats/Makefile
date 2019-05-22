.PHONY: module
module: stats

CXXFLAGS = -fpie -rdynamic

stats: stats.cc
	$(CC) -pie -o $@ $(CXXFLAGS) $(LDFLAGS) stats.cc

clean:
	rm -f stats
