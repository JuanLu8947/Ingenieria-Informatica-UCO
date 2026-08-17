cmake_minimum_required(VERSION 3.10)
project(P5_Alg)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(p5
    main.cpp
    funcionesMedioNivel.cpp
    funcionesGrafos.cpp
    funcionesNReinas.cpp
    tiempos.cpp
)

#target_include_directories(p5 PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
    
#set_target_properties(p5 PROPERTIES
    #RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}
    #RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}
#)
