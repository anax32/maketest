#####################################################
# Makefile which generates executables for each .cpp
# file under the TEST_DIR directory.
#
# caller makefiles should include this and define the
# TEST_DIR variable.
# TEST_DIR must have a trailing directory marker.
# A subdir will be created $(TEST_DIR)bin
#
# requirements:
# TEST_DIR:
#	directory containing test code for compilation.
#	each .cpp file becomes an executable.
#	can contain sub-directories.
#
# commands:
# <test-cpp-file>.test:
#	build and execute the named test files.
#	(NB: replace the filetype with .test)
#
# all_tests:
#	build and execute all test files.
#
# run_tests:
#	run all executes in TEST_DIR/bin
#
# clean_tests:
#	remove TEST_DIR/bin and contents
######################################################

TEST_MKDIR = mkdir -p
TEST_BIN_DIR = $(TEST_DIR)bin

TESTS = $(wildcard $(TEST_DIR)*/*.cpp)
TEST_OUTPUTS = $(TESTS:.cpp=.test)
#TEST_OUTPUTS = $(TESTS:.cpp=)

$(TEST_BIN_DIR):
	$(TEST_MKDIR) $(TEST_BIN_DIR)

%.test : $(TEST_BIN_DIR)
	$(CXX) $(CXXFLAGS) $(LDLIBS) -o $(TEST_BIN_DIR)$(notdir $(basename $@)) $(basename $@).cpp
	$(TEST_BIN_DIR)$(notdir $(basename $@))

all_tests : $(TEST_OUTPUTS) $(TEST_BIN_DIR)

run_tests :
	run-parts $(TEST_BIN_DIR)

clean_tests :
	rm -drf $(TEST_BIN_DIR)
