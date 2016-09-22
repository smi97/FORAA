cmake_minimum_required(VERSION 3.6.2)	

project(hello_world)
	
include_directories(include)

set(SOURCE examples/main.cpp)

set(SOURCE_LIB sources/print_hello_world.cpp)	

add_library(phw STATIC ${SOURCE_LIB})	

add_executable(main ${SOURCE})	

target_link_libraries(main phw)