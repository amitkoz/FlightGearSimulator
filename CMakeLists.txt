cmake_minimum_required(VERSION 3.15)
project(untitled1)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS -pthread)

add_executable(untitled1 main.cpp Command.h openDataServer.h S_yard.cpp S_yard.h Expression.cpp Expression.h Lexer.h Parser.h allCommands.h connectControlClient.h SetVarCommand.h ReadData.h While_and_If_Command.h)