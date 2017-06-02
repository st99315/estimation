cmake_minimum_required (VERSION 3.0)

project(estimation)

# using c++ 11 standard
add_definitions(-std=c++11)

# set of include directory
set(INCLUDE_DIR
    ./proj1
    ./proj2
)
# include
include_directories(${INCLUDE_DIR})

# generate executable file
add_executable(test_func TestMain.cpp)

# generate libraries
add_library(VecMat
    ./proj1/fVector.cpp
    ./proj1/fMatrix.cpp
)
add_library(ParamEstimator
    ./proj2/ParamEstimator.cpp
)
add_library(MatchingPoints
    ./proj2/MatchingPoints.cpp
)

# link libraries to executable
target_link_libraries(test_func
    VecMat
    ParamEstimator
    MatchingPoints
)
