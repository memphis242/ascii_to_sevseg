.POSIX:

################################# The Prelude ##################################

.PHONY: test
.PHONY: test1
.PHONY: test2
.PHONY: test3
.PHONY: _test
.PHONY: lib
.PHONY: release
.PHONY: unity_static_analysis
.PHONY: clean

BUILD_TYPE ?= RELEASE

# Target to run a test build for every config combo
test:
	@echo "----------------------------------------"
	@echo -e "Test for \033[35mnumbers only version\033[0m..."
	@echo "----------------------------------------"
	@$(MAKE) --always-make BUILD_TYPE=TEST TEST_CATEGORY=NUMS_ONLY _test
	@echo "----------------------------------------"
	@echo
	@echo "----------------------------------------"
	@echo -e "Test for \033[35mnumbers + 'error' version\033[0m..."
	@echo "----------------------------------------"
	@$(MAKE) --always-make BUILD_TYPE=TEST TEST_CATEGORY=NUMS_AND_ERROR_ONLY _test
	@echo "----------------------------------------"
	@echo
	@echo "----------------------------------------"
	@echo -e "Test for \033[35mcomplete version\033[0m..."
	@echo "----------------------------------------"
	@$(MAKE) --always-make BUILD_TYPE=TEST _test
	@echo "----------------------------------------"
	@echo

# Targets to run only one config combo.
# NOTE: If you run testX and then want to run testY, make sure to clean first!
test1:
	@echo "----------------------------------------"
	@echo -e "Test for \033[35mnumbers only version\033[0m..."
	@echo "----------------------------------------"
	@$(MAKE) BUILD_TYPE=TEST TEST_CATEGORY=NUMS_ONLY _test

test2:
	@echo "----------------------------------------"
	@echo -e "Test for \033[35mnumbers + 'error' version\033[0m..."
	@echo "----------------------------------------"
	@$(MAKE) --always-make BUILD_TYPE=TEST TEST_CATEGORY=NUMS_AND_ERROR_ONLY _test

test3:
	@echo "----------------------------------------"
	@echo -e "Test for \033[35mcomplete version\033[0m..."
	@echo "----------------------------------------"
	@$(MAKE) --always-make BUILD_TYPE=TEST _test

$(info This test run)

CLEANUP = rm -f
MKDIR = mkdir -p
TARGET_EXTENSION=exe
# Set the OS-specific tool cmds / executable extensions
ifeq ($(OS),Windows_NT)

  TARGET_EXTENSION = exe
  STATIC_LIB_EXTENSION = lib

  ifeq ($(shell uname -s),) # not in a bash-like shell
    CLEANUP = del /F /Q
    MKDIR = mkdir
  else # in a bash-like shell, like msys
    CLEANUP = rm -f
    MKDIR = mkdir -p
  endif

else

  TARGET_EXTENSION = out
  STATIC_LIB_EXTENSION = a
  CLEANUP = rm -f
  MKDIR = mkdir -p

endif

# Relevant paths
PATH_UNITY        = test/Unity/src/
PATH_SRC          = src/
PATH_INC          = inc/
PATH_TEST_FILES   = test/
PATH_BUILD        = build/
PATH_OBJECT_FILES = $(PATH_BUILD)objs/
PATH_RESULTS      = $(PATH_BUILD)results/
PATH_PROFILE      = $(PATH_BUILD)profile/
PATH_BENCHMARK	   = benchmark/
PATH_SCRIPTS      = scripts/
PATH_RELEASE		= $(PATH_BUILD)release/
PATH_DEBUG			= $(PATH_BUILD)debug/
BUILD_DIRS        = $(PATH_BUILD) $(PATH_OBJECT_FILES) $(PATH_RELEASE) $(PATH_DEBUG)

# Lists of files
# The pattern employed here is to generate lists of files which shall then be
# used as pre-requisities in downstream rules.
COLORIZE_CPPCHECK_SCRIPT = $(PATH_SCRIPTS)colorize_cppcheck.py
COLORIZE_UNITY_SCRIPT = $(PATH_SCRIPTS)colorize_unity.py

UNITY_SRC_FILES = $(wildcard $(PATH_UNITY)*.c)
UNITY_HDR_FILES = $(wildcard $(PATH_UNITY)*.h)
UNITY_OBJ_FILES = $(patsubst %.c, $(PATH_OBJECT_FILES)%.o, $(notdir $(UNITY_SRC_FILES)))

LIB_NAME = ascii7seg

# Relevant files
SRC_FILES = $(wildcard $(PATH_SRC)*.c)
HDR_FILES = $(wildcard $(PATH_INC)*.h)
SRC_TEST_FILES = $(wildcard $(PATH_TEST_FILES)*.c)
LIB_FILE = $(PATH_BUILD)lib$(LIB_NAME).$(STATIC_LIB_EXTENSION)
LIB_OBJ_FILES = $(patsubst %.c, $(PATH_OBJECT_FILES)%.o, $(notdir $(SRC_FILES)))
TEST_EXECUTABLES = $(PATH_BUILD)test_$(LIB_NAME).$(TARGET_EXTENSION)
LIB_LIST_FILE = $(patsubst %.$(STATIC_LIB_EXTENSION), $(PATH_BUILD)%.lst, $(notdir $(LIB_FILE)))
TEST_LIST_FILE = $(patsubst %.$(TARGET_EXTENSION), $(PATH_BUILD)%.lst, $(notdir $(TEST_EXECUTABLES)))
TEST_OBJ_FILES = $(patsubst %.c, $(PATH_OBJECT_FILES)%.o, $(notdir $(SRC_TEST_FILES)))
RESULTS = $(patsubst %.$(TARGET_EXTENSION), $(PATH_RESULTS)%.txt, $(notdir $(TEST_EXECUTABLES)))

ifeq ($(BUILD_TYPE), TEST)
  BUILD_DIRS += $(PATH_RESULTS)
else ifeq ($(BUILD_TYPE), PROFILE)
  BUILD_DIRS += $(PATH_PROFILE)
endif

# Compiler setup
CROSS	= 
CC = $(CROSS)gcc

COMPILER_WARNINGS = \
    -Wall -Wextra -Wpedantic -pedantic-errors \
    -Wconversion -Wdouble-promotion -Wnull-dereference \
    -Wwrite-strings -Wformat=2 -Wformat-overflow=2 \
    -Wformat-signedness -Wuseless-cast -Wstrict-prototypes \
    -Wcast-align=strict -Wimplicit-fallthrough=3 -Wswitch-default \
    -Wswitch-enum -Wfloat-equal -Wuse-after-free=2 \
    -Wdeprecated-declarations -Wmissing-prototypes -Wparentheses \
    -Wreturn-type -Wlogical-op -Wstrict-aliasing \
    -Wuninitialized -Wmaybe-uninitialized -Wshadow \
    -Wduplicated-cond -Wduplicated-branches \
    -Walloc-zero -Walloc-size

# Includes some -Wno-... flags for warnings that I'd normally want for my lib
# src but **not** for my test file, which intentionally has all sorts of
# naughty shenanigans going on
COMPILER_WARNINGS_TEST_BUILD = \
    -Wall -Wextra -Wpedantic -pedantic-errors \
    -Wconversion -Wdouble-promotion -Wnull-dereference \
    -Wwrite-strings -Wformat=2 -Wformat-overflow=2 \
    -Wformat-signedness \
    -Wcast-align=strict -Wimplicit-fallthrough=3 -Wswitch-default \
    -Wswitch-enum -Wfloat-equal -Wuse-after-free=2 \
    -Wdeprecated-declarations -Wmissing-prototypes -Wparentheses \
    -Wreturn-type -Wlogical-op -Wstrict-aliasing \
    -Wuninitialized -Wmaybe-uninitialized -Wshadow \
    -Wsuggest-attribute=const \
    -Walloc-zero -Walloc-size \
    -Wno-analyzer-use-of-uninitialized-value -Wno-uninitialized \
    -Wno-maybe-uninitialized

# Consider -Wmismatched-dealloc
COMPILER_SANITIZERS = -fsanitize=bool -fsanitize=undefined -fsanitize-trap
COMPILER_OPTIMIZATION_LEVEL_DEBUG = -Og -g3
COMPILER_OPTIMIZATION_LEVEL_SPEED = -O3
COMPILER_OPTIMIZATION_LEVEL_SPACE = -Os
COMPILER_STANDARD = -std=c99
INCLUDE_PATHS = -I. -I$(PATH_INC) -I$(PATH_UNITY)
TEST_DEFINES ?=

COMMON_DEFINES =
ifeq ($(TEST_CATEGORY), NUMS_ONLY)
  COMMON_DEFINES += -DASCII_7SEG_NUMS_ONLY # -DASCII_7SEG_DONT_USE_LOOKUP_TABLE -DASCII_7SEG_BIT_PACK
else ifeq ($(TEST_CATEGORY), NUMS_AND_ERROR_ONLY)
  COMMON_DEFINES += -DASCII_7SEG_NUMS_AND_ERROR_ONLY # -DASCII_7SEG_DONT_USE_LOOKUP_TABLE -DASCII_7SEG_BIT_PACK
endif
#COMMON_DEFINES = # -DASCII_7SEG_DONT_USE_LOOKUP_TABLE -DASCII_7SEG_BIT_PACK

DIAGNOSTIC_FLAGS = -fdiagnostics-color
COMPILER_STATIC_ANALYZER = -fanalyzer

# Compile up the compiler flags
CFLAGS = $(INCLUDE_PATHS) $(COMMON_DEFINES) \
			$(DIAGNOSTIC_FLAGS) $(COMPILER_WARNINGS) $(COMPILER_STATIC_ANALYZER) \
			$(COMPILER_STANDARD)

CFLAGS_TEST = \
         -DTEST $(COMMON_DEFINES) $(TEST_DEFINES) \
         $(INCLUDE_PATHS) \
         $(DIAGNOSTIC_FLAGS) $(COMPILER_WARNINGS_TEST_BUILD) \
         $(COMPILER_STATIC_ANALYZER) $(COMPILER_STANDARD) \
         $(COMPILER_SANITIZERS) $(COMPILER_OPTIMIZATION_LEVEL_DEBUG)

ifeq ($(BUILD_TYPE), RELEASE)
CFLAGS += -DNDEBUG $(COMPILER_OPTIMIZATION_LEVEL_SPEED)

else ifeq ($(BUILD_TYPE), BENCHMARK)
CFLAGS += -DNDEBUG $(COMPILER_OPTIMIZATION_LEVEL_SPEED)

else ifeq ($(BUILD_TYPE), PROFILE)
CFLAGS += -DNDEBUG $(COMPILER_OPTIMIZATION_LEVEL_DEBUG) -pg
LDFLAGS += -pg

else
CFLAGS += $(COMPILER_SANITIZERS) $(COMPILER_OPTIMIZATION_LEVEL_DEBUG)
endif

# Compile up linker flags
LDFLAGS += $(DIAGNOSTIC_FLAGS)

# CppCheck flags/options

# Explanations for suppressions:
# 	- unknownEvaluationOrder:
#	  • CppCheck flagged as an error the following construct in ascii7seg.c:
# 		   const union Ascii7Seg_Encoding_U MasterLUT[ UINT8_MAX ] =
#        {
#           // cppcheck-suppress expressionDependOnOrderOfEvaluation
#           [(uint8_t)'0'] = { .segments = { .a = 1, .b = 1, .c = 1, .d = 1, .e = 1, .f = 1, .g = 0 }, },
#           ...
#
#    • This is _not_ an error. There are no internal side-effects being relied
#		 upon here. I think CppCheck is getting thrown off by the designated initializers.
CPPCHECK_SUPPRESSIONS = --suppress=unknownEvaluationOrder

CPPCHECK_OPTIONS = --std=c99 --cppcheck-build-dir=$(PATH_BUILD) $(CPPCHECK_SUPPRESSIONS)

############################# The Rules & Recipes ##############################

######################### Lib Rules ########################
release: lib
# Build the static library files
lib: $(BUILD_DIRS) $(LIB_FILE) $(LIB_LIST_FILE)
	@echo
	@echo "----------------------------------------"
	@echo -e "Library \033[35m$(LIB_FILE) \033[32;1mbuilt\033[0m!"
	@echo "----------------------------------------"

$(LIB_FILE): $(LIB_OBJ_FILES) $(BUILD_DIRS) 
	@echo
	@echo "----------------------------------------"
	@echo -e "\033[36mConstructing\033[0m the static library: $@..."
	@echo
	ar rcs $@ $<

######################## Test Rules ########################
_test: $(BUILD_DIRS) $(TEST_EXECUTABLES) $(LIB_FILE) $(TEST_LIST_FILE) $(RESULTS)
	@echo
	@echo -e "\033[36mAll tests completed!\033[0m"
	@echo

# Write the test results to a result .txt file
$(PATH_RESULTS)%.txt: $(PATH_BUILD)%.$(TARGET_EXTENSION) $(COLORIZE_UNITY_SCRIPT)
	@echo
	@echo "----------------------------------------"
	@echo -e "\033[36mRunning\033[0m $<..."
	@echo
	-./$< 2>&1 | tee $@ | python $(COLORIZE_UNITY_SCRIPT)

$(PATH_BUILD)%.$(TARGET_EXTENSION): $(TEST_OBJ_FILES) $(UNITY_OBJ_FILES) $(LIB_FILE)
	@echo
	@echo "----------------------------------------"
	@echo -e "\033[36mLinking\033[0m $(TEST_OBJ_FILES), $(UNITY_OBJ_FILES), and the static lib $(LIB_FILE) into an executable..."
	@echo
	$(CC) $(LDFLAGS) $(TEST_OBJ_FILES) $(UNITY_OBJ_FILES) -L$(PATH_BUILD) -l$(basename $(notdir $(LIB_FILE))) -o $@

$(PATH_OBJECT_FILES)%.o: $(PATH_TEST_FILES)%.c $(COLORIZE_CPPCHECK_SCRIPT)
	@echo
	@echo "----------------------------------------"
	@echo -e "\033[36mCompiling\033[0m the test file: $<..."
	@echo
	$(CC) -c $(CFLAGS_TEST) $< -o $@
	@echo

$(PATH_OBJECT_FILES)%.o: $(PATH_UNITY)%.c $(PATH_UNITY)%.h
	@echo
	@echo "----------------------------------------"
	@echo -e "\033[36mCompiling\033[0m the unity file: $<..."
	@echo
	$(CC) -c $(CFLAGS_TEST) $< -o $@
	@echo

unity_static_analysis: $(PATH_UNITY)unity.c $(COLORIZE_CPPCHECK_SCRIPT)
	@echo
	@echo "----------------------------------------"
	@echo -e "\033[36mRunning static analysis\033[0m on $<..."
	@echo
	cppcheck $(CPPCHECK_OPTIONS) --template='{severity}: {file}:{line}: {message}' $< 2>&1 | tee $(PATH_BUILD)cppcheck.log | python $(COLORIZE_CPPCHECK_SCRIPT)

######################### Generic ##########################

# Compile the primary source file into an object file
$(PATH_OBJECT_FILES)%.o : $(PATH_SRC)%.c $(PATH_INC)%.h $(COLORIZE_CPPCHECK_SCRIPT)
	@echo
	@echo "----------------------------------------"
	@echo -e "\033[36mCompiling\033[0m the primary source file: $<..."
	@echo
	$(CC) -c $(CFLAGS) $< -o $@
	@echo
	@echo "----------------------------------------"
	@echo -e "\033[36mRunning static analysis\033[0m on $<..."
	@echo
	cppcheck $(CPPCHECK_OPTIONS) --template='{severity}: {file}:{line}: {message}' $< 2>&1 | tee $(PATH_BUILD)cppcheck.log | python $(COLORIZE_CPPCHECK_SCRIPT)

$(LIB_LIST_FILE): $(LIB_FILE)
	@echo
	@echo "----------------------------------------"
	@echo -e "\033[36mDisassembly\033[0m of $< into $@..."
	@echo
	objdump -D $< > $@

# Produces an object dump that includes the disassembly of the executable
$(PATH_BUILD)%.lst: $(PATH_BUILD)%.$(TARGET_EXTENSION)
	@echo
	@echo "----------------------------------------"
	@echo -e "\033[36mDisassembly\033[0m of $< into $@..."
	@echo
	objdump -D $< > $@

# Make the directories if they don't already exist
$(PATH_RESULTS):
	$(MKDIR) $@

$(PATH_OBJECT_FILES):
	$(MKDIR) $@

$(PATH_BUILD):
	$(MKDIR) $@

$(PATH_PROFILE):
	$(MKDIR) $@

$(PATH_RELEASE):
	$(MKDIR) $@

$(PATH_DEBUG):
	$(MKDIR) $@

# Clean rule to remove generated files
clean:
	@echo
	$(CLEANUP) $(PATH_OBJECT_FILES)*.o
	$(CLEANUP) $(PATH_BUILD)*.$(TARGET_EXTENSION)
	$(CLEANUP) $(PATH_RESULTS)*.txt
	$(CLEANUP) $(PATH_BUILD)*.lst
	$(CLEANUP) $(PATH_BUILD)*.log
	$(CLEANUP) $(PATH_BUILD)*.$(STATIC_LIB_EXTENSION)
	$(CLEANUP) $(PATH_RELEASE)*.o
	$(CLEANUP) $(PATH_RELEASE)*.$(TARGET_EXTENSION)
	$(CLEANUP) $(PATH_RELEASE)*.$(STATIC_LIB_EXTENSION)
	$(CLEANUP) $(PATH_DEBUG)*.o
	$(CLEANUP) $(PATH_DEBUG)*.$(TARGET_EXTENSION)
	$(CLEANUP) $(PATH_DEBUG)*.$(STATIC_LIB_EXTENSION)
	@echo

.PRECIOUS: $(PATH_BUILD)%.$(TARGET_EXTENSION)
.PRECIOUS: $(PATH_BUILD)Test%.o
.PRECIOUS: $(PATH_RESULTS)%.txt
.PRECIOUS: $(PATH_RESULTS)%.lst
