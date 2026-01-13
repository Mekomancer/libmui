# wrapper script for developing qol (nvim's :make command)
.PHONY: b d r fmt build debug run format clean

build_dir = ../build
run_cmd = $(build_dir)/target/*
jobcnt = $$((`nproc`-1))
nin = ninja -j$(jobcnt) -C $(build_dir)

# Aliases
b: build
d: debug
r: run
fmt: format

build: $(build_dir)/build.ninja
	$(nin)

run: build
	$(run_cmd)

$(build_dir)/build.ninja: | $(build_dir)
	env -C $(build_dir) cmake .. --preset=default 

$(build_dir):
	mkdir $(build_dir)

# Non-build targets
format: $(build_dir)/build.ninja
	$(nin) format

debug:
	gdbtui $(run_cmd)

clean:
	rm -rf $(build_dir)




