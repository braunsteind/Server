cmake_minimum_required(VERSION 3.8)
project(Server)

set(CMAKE_CXX_STANDARD 98)
set(CMAKE_CXX_FLAGS -pthread)

set(SOURCE_FILES main.cpp Server.cpp Server.h ConfigurationFileHandler.cpp ConfigurationFileHandler.h Command.h CommandsManager.cpp CommandsManager.h StartCommand.cpp StartCommand.h JoinCommand.cpp JoinCommand.h ListGamesCommand.cpp ListGamesCommand.h GamesList.cpp GamesList.h GameRoom.cpp GameRoom.h Task.h ThreadPool.cpp ThreadPool.h)
add_executable(Server ${SOURCE_FILES})