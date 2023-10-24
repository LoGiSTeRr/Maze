cmake_minimum_required(VERSION 3.25)
project(FinalProjectMaze)

set(CMAKE_CXX_STANDARD 14)

include_directories(FinalProjectMaze)
include_directories(FinalProjectMaze/Console)

add_executable(FinalProjectMaze
        FinalProjectMaze/Console/console.cpp
        FinalProjectMaze/Console/console.h
        FinalProjectMaze/Console/console_manip.cpp
        FinalProjectMaze/Console/console_manip.h
        FinalProjectMaze/Console/resource.h
        FinalProjectMaze/GhostLogic.cpp
        FinalProjectMaze/GhostLogic.h
        FinalProjectMaze/GlobalVariables.cpp
        FinalProjectMaze/GlobalVariables.h
        FinalProjectMaze/main.cpp
        FinalProjectMaze/MazeGeneration.cpp
        FinalProjectMaze/MazeGeneration.h
        FinalProjectMaze/PlayerMovement.cpp
        FinalProjectMaze/PlayerMovement.h
        FinalProjectMaze/TopAndFiles.cpp
        FinalProjectMaze/TopAndFiles.h
        FinalProjectMaze/UI.cpp
        FinalProjectMaze/UI.h
        FinalProjectMaze/Unit.h
        FinalProjectMaze/UnitFuncs.h
        FinalProjectMaze/UnitFuns.cpp)
