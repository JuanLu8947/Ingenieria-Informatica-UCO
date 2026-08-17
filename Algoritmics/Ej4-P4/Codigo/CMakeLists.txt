cmake_minimum_required(VERSION 3.10)
project(P4_ALG)

set(CMAKE_CXX_STANDARD 17)

add_executable(
    p4 
    main.cpp 
    medioNivel.cpp 
    punto.cpp 
    recta.cpp 
    serietemporal.cpp
    algoritmos.cpp
    auxiliares.cpp
    tiempos.cpp
)

set_target_properties(p4 PROPERTIES
    #RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}
)
