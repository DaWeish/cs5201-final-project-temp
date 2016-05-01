##############################################################################
# file: makefile
# author: Connor Walsh - 5201 A
# date: Wed Feb 10 18:37:43 CST 2016
# brief: Makefile for general program compilation
##############################################################################

# Commented out lines are for a future improvement to have the .o files mimic
# the same directory structure as the source modules

SHELL = /bin/sh

MODULES := driver
TEST_MODULES := test

SOURCE_DIR := src
BUILD_DIR  := build
DEPEND_DIR := depends

SOURCE_MODULE_DIR := $(addprefix $(SOURCE_DIR)/,$(MODULES))
TEST_MODULE_DIR := $(addprefix $(SOURCE_DIR)/,$(TEST_MODULES))
#BUILD_MODULE_DIR  := $(addprefix $(BUILD_DIR)/,$(MODULES))

CPPFLAGS =
CXX      = /usr/bin/g++
CXXFLAGS = -g -std=c++11 -Wall -Wextra -pedantic-errors
TESTFLAGS = -lgtest
DEPFLAGS = -MT $@ -MMD -MP -MF $(DEPEND_DIR)/$*.Tmpd

SOURCES      := $(foreach srcdir,$(SOURCE_MODULE_DIR),$(wildcard $(srcdir)/*.cpp))
TEST_SOURCES := $(foreach srcdir,$(TEST_MODULE_DIR),$(wildcard $(srcdir)/*.cpp))

OBJECTS      := $(addprefix $(BUILD_DIR)/,$(addsuffix .o,$(basename $(notdir $(SOURCES)))))
TEST_OBJECTS := $(addprefix $(BUILD_DIR)/,$(addsuffix .o,$(basename $(notdir $(TEST_SOURCES)))))
#OBJECTS := $(patsubst $(SOURCE_DIR)/%.cpp,$(BUILD_DIR)/%.o,$(SOURCES))
INCLUDES := $(addprefix -I,$(SOURCE_MODULE_DIR)) $(addprefix -I,$(TEST_MODULE_DIR))

vpath %.cpp $(SOURCE_MODULE_DIR) $(TEST_MODULE_DIR)

.PHONY = all clean

.SUFFIXES =
.SUFFIXES = .cpp

COMPILECXX  = $(CXX) $(DEPFLAGS) $(CXXFLAGS) $(CPPFLAGS) $(INCLUDES) -c
POSTCOMPILE = mv -f $(DEPEND_DIR)/$*.Tmpd $(DEPEND_DIR)/$*.d

#define make-goal
#$1/%.o : %.cpp
#	$(COMPILECXX) -MT $$@ -MMD -MP -MF $(DEPEND_DIR)/$$*.Tmpd $$< -o $$@
#endef

$(BUILD_DIR)/%.o : %.cpp $(DEPEND_DIR)/%.d | $(BUILD_DIR)
	@echo Detected Changes in: $?
	@echo ---- Compiling $< ----
	@$(COMPILECXX) $< -o $@
	@$(POSTCOMPILE)
	@echo ---- Compile Success ----

default : all

all : driver

driver : $(OBJECTS)
	@echo ---- Linking $@ ----
	@$(CXX) $(CXXFLAGS) $^ -o $@
	@echo ---- Link Success ----

tests : $(TEST_OBJECTS)
	@echo ---- Linking $@ ----
	@$(CXX) $(CXXFLAGS) $(TESTFLAGS) $^ -o $@
	@echo ---- Link Success ----

$(DEPEND_DIR)/%.d : | $(DEPEND_DIR) ;
.PRECIOUS: $(DEPEND_DIR)/%.d

$(BUILD_DIR) :
	@mkdir -p $@

$(DEPEND_DIR) :
	@mkdir -p $@

clean :
	@echo Removing $(BUILD_DIR) and $(DEPEND_DIR) directories...
	-@rm -f core
	@echo Removing driver...
	-@rm -f driver
	-@rm -f tests
	-@rm -Rf $(DEPEND_DIR)
	-@rm -Rf $(BUILD_DIR)

#$(foreach bdir,$(BUILD_MODULE_DIR),$(eval $(call make-goal,$(bdir))))

-include $(patsubst %,$(DEPEND_DIR)/%.d,$(notdir $(basename $(SOURCES))))
-include $(patsubst %,$(DEPEND_DIR)/%.d,$(notdir $(basename $(TEST_SOURCES))))
