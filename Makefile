# Top level Makefile for sub-projects.

CHILD_PROJECT_DIRS := Asteroids

WORKING_DIR := $(realpath .)
OUT_DIR_NAME := /build
export OUT_DIR := $(addsuffix $(OUT_DIR_NAME), $(WORKING_DIR))

release:
	@mkdir -p $(OUT_DIR)/$@
	$(foreach C, $(CHILD_PROJECT_DIRS), @$(MAKE) -C $(C) $@)

debug:
	@mkdir -p $(OUT_DIR)/$@
	$(foreach C, $(CHILD_PROJECT_DIRS), @$(MAKE) -C $(C) $@)

clean:
	@rm -rf $(OUT_DIR)
	$(foreach C, $(CHILD_PROJECT_DIRS), @$(MAKE) -C $(C) $@)

