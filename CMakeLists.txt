project(TextHashing)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(GENERATOR_SOURCE_FILES Generator/main.cpp)
add_executable(Generator ${GENERATOR_SOURCE_FILES})

set(JACCARD_SOURCE_FILES Jaccard/main.cpp)
add_executable(Jaccard ${JACCARD_SOURCE_FILES})

set(APPROXIMATION_SOURCE_FILES Approximation/main.cpp)
add_executable(Approximation ${APPROXIMATION_SOURCE_FILES})

set(LSH_SOURCE_FILES LSH/main.cpp)
add_executable(LSH ${LSH_SOURCE_FILES})
