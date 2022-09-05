cmake_minimum_required(VERSION 3.0.0)

project( pct LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


add_executable ( pct main.cpp )

target_link_libraries( pct pistache )
