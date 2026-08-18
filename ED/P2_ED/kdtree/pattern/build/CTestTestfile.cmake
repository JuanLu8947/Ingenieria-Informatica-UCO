# CMake generated Testfile for 
# Source directory: /home/juanlu/ED/P2/kdtree/pattern
# Build directory: /home/juanlu/ED/P2/kdtree/pattern/build
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(TestPattern "/usr/bin/python3" "run_tests.py" "/home/juanlu/ED/P2/kdtree/pattern/build//test_pattern" "01_tests_pattern")
set_tests_properties(TestPattern PROPERTIES  WORKING_DIRECTORY "/home/juanlu/ED/P2/kdtree/pattern" _BACKTRACE_TRIPLES "/home/juanlu/ED/P2/kdtree/pattern/CMakeLists.txt;22;add_test;/home/juanlu/ED/P2/kdtree/pattern/CMakeLists.txt;0;")
add_test(TestDataset "/usr/bin/python3" "run_tests.py" "/home/juanlu/ED/P2/kdtree/pattern/build//test_pattern" "02_tests_pattern_dataset")
set_tests_properties(TestDataset PROPERTIES  WORKING_DIRECTORY "/home/juanlu/ED/P2/kdtree/pattern" _BACKTRACE_TRIPLES "/home/juanlu/ED/P2/kdtree/pattern/CMakeLists.txt;23;add_test;/home/juanlu/ED/P2/kdtree/pattern/CMakeLists.txt;0;")
add_test(TestPatternDistances "/usr/bin/python3" "run_tests.py" "/home/juanlu/ED/P2/kdtree/pattern/build//test_pattern" "03_tests_pattern_distances")
set_tests_properties(TestPatternDistances PROPERTIES  WORKING_DIRECTORY "/home/juanlu/ED/P2/kdtree/pattern" _BACKTRACE_TRIPLES "/home/juanlu/ED/P2/kdtree/pattern/CMakeLists.txt;24;add_test;/home/juanlu/ED/P2/kdtree/pattern/CMakeLists.txt;0;")
