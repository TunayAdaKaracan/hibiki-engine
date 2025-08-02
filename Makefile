CLEAN_OUT=.zig-cache zig-out
CLEAN_OTHER =.cache

clean:
	rm -rf $(CLEAN_OUT)

clean-all: clean
	rm -rf $(CLEAN_OTHER)
