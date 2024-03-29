# Alternative GNU Make workspace makefile autogenerated by Premake

ifndef config
  config=debug
endif

ifndef verbose
  SILENT = @
endif

ifeq ($(config),debug)
  gui3_config = debug

else ifeq ($(config),release)
  gui3_config = release

else
  $(error "invalid configuration $(config)")
endif

PROJECTS := gui3

.PHONY: all clean help $(PROJECTS) 

all: $(PROJECTS)

gui3:
ifneq (,$(gui3_config))
	@echo "==== Building gui3 ($(gui3_config)) ===="
	@${MAKE} --no-print-directory -C build -f Makefile config=$(gui3_config)
endif

clean:
	@${MAKE} --no-print-directory -C build -f Makefile clean

help:
	@echo "Usage: make [config=name] [target]"
	@echo ""
	@echo "CONFIGURATIONS:"
	@echo "  debug"
	@echo "  release"
	@echo ""
	@echo "TARGETS:"
	@echo "   all (default)"
	@echo "   clean"
	@echo "   gui3"
	@echo ""
	@echo "For more information, see https://github.com/premake/premake-core/wiki"