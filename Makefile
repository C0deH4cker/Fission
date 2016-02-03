# Target specific variables
TARGET := fsn
OFLAGS += -O2 -flto
CXXFLAGS += -std=c++11

# Macro to find all source files in a directory
get_cc_srcs = $(wildcard $1*.[cm])
get_cxx_srcs = $(wildcard $1*.cpp) $(wildcard $1*.mm)

# General build path variables
BUILD := build
CC_SRCS := $(call get_cc_srcs,) $(foreach d,$(SRC_DIRS),$(call get_cc_srcs,$d/))
CXX_SRCS := $(call get_cxx_srcs,) $(foreach d,$(SRC_DIRS),$(call get_cxx_srcs,$d/))
ALL_SRCS := $(CC_SRCS) $(CXX_SRCS)
SRC_DIRS := $(sort $(filter-out .,$(patsubst %/,%,$(dir $(ALL_SRCS)))))
OBJS := $(patsubst %,$(BUILD)/%.o,$(ALL_SRCS))
DEPS := $(OBJS:.o=.d)
BUILD_DIR_RULES := $(BUILD)/.dir $(patsubst %,$(BUILD)/%/.dir,$(SRC_DIRS))

# Tools and flags to use
CLANG := clang
CLANGXX := clang++
GCC := gcc
GXX := g++

# Default to using clang unless USE_GCC is defined
ifdef USE_GCC
CC := $(GCC)
CXX := $(GXX)
LD := $(GXX)
else
CC := $(CLANG)
CXX := $(CLANGXX)
LD := $(CLANGXX)
endif


# Print all commands executed when VERBOSE is defined
ifdef VERBOSE
_v :=
else
_v := @
endif


# Build the target by default
all: $(TARGET)

# Build in debug mode (with asserts enabled)
debug: override CFLAGS += -ggdb -DDEBUG=1 -UNDEBUG
debug: override OFLAGS :=
debug: $(TARGET)

# Uses clang's Address Sanitizer to help detect memory errors
debug+: override CFLAGS += -ggdb -DDEBUG=1 -UNDEBUG -fsanitize=address
debug+: override OFLAGS :=
debug+: override LDFLAGS += -fsanitize=address
debug+: debug


# Linking rule
$(TARGET): $(OBJS)
	@echo 'Linking $(@F)'
	$(_v)$(LD) $(OFLAGS) $(LDFLAGS) -o $@ $^


# Compiling rule
$(BUILD)/%.cpp.o: %.cpp | $(BUILD_DIR_RULES)
	@echo 'Compiling $<'
	$(_v)$(CXX) $(OFLAGS) $(CFLAGS) $(CXXFLAGS) -I$(<D) -MD -MP -MF $(BUILD)/$*.d -c -o $@ $<


# Build dependency rules
-include $(DEPS)


# Install rules

install: /usr/local/bin/$(TARGET)

.PHONY: install

/usr/local/bin/$(TARGET): $(TARGET)
	@echo 'Install $< to $@'
	$(_v)cp $< $@

# Make sure that the .dir files aren't automatically deleted after building
.SECONDARY:

# Directory creation rule
%/.dir:
	$(_v)mkdir -p $* && touch $@

# Build products cleaning rule
clean:
	@echo 'Removing built products'
	$(_v)rm -rf $(BUILD) $(TARGET)

.PHONY: all debug debug+ clean

