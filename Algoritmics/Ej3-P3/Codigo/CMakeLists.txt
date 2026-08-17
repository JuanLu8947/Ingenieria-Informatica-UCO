cmake_minimum_required(VERSION 3.10)
project(P3_ALG)

set(CMAKE_CXX_STANDARD 17)

add_executable(
    p3 
    main.cpp 
    medioNivel.cpp 
    algoritmos.cpp
    punto.cpp 
    recta.cpp 
    serietemporal.cpp
    auxiliares.cpp
)

set_target_properties(p3 PROPERTIES
    #RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}
)
