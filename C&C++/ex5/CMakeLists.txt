cmake_minimum_required(VERSION 3.16)
project(ex5_tomerm1)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(ex5_tomerm1
        Movie.cpp
        Movie.h
        RecommenderSystem.h
        RecommenderSystemLoader.h
        RSUser.cpp
        RSUser.h
        RSUsersLoader.h RecommenderSystem.cpp RecommenderSystemLoader.cpp RSUsersLoader.cpp test_RS_by_cf.cpp)
