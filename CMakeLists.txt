cmake_minimum_required(VERSION 3.21)
project(CPP1_s21_matrixplus-0)

set(CMAKE_CXX_STANDARD 17)


#file(GLOB SRC_FILES ${PROJECT_SOURCE_DIR}/src/*.cc)

#add_executable(${PROJECT_TEST_NAME} ${TEST_SRC_FILES} ${SRC_FILES})


add_executable(CPP1_s21_matrixplus-0
        src/s21_matrix_oop.cc
        src/s21_matrix_oop.h
        src/test.cc)

#add_executable(S21MatrixTest src/test.cc)

#gtest_add_tests(TARGET      S21MatrixTest
#        TEST_SUFFIX .noArgs
#        TEST_LIST   noArgsTests
#        )
#gtest_add_tests(TARGET      S21MatrixTest
#        EXTRA_ARGS  --someArg someValue
#        TEST_SUFFIX .withArgs
#        TEST_LIST   withArgsTests
#        )
include(GoogleTest)
#find_package(GTest)
#target_link_libraries(CPP1_s21_matrixplus-0{GTEST_LIBRARY})