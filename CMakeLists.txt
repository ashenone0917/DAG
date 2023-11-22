cmake_minimum_required(VERSION 3.6)
set(DAG "DirectedAcyclicGraph")
project(
	DAG
	LANGUAGES C CXX
)

set(CMAKE_CXX_STANDARD 17) 

set(SOURCE_FILES
    DirectedAcyclicGraph.h
    DirectedGraph.cpp
)

add_executable(DAG ${SOURCE_FILES})