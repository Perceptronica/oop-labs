cmake_minimum_required(VERSION 3.20)

project(lab6)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(COMPILE_FILES
    lib/UI.h
    lib/NPC.h
    lib/NPCFabric.h
    lib/Observer.h
    lib/Visitor.h
    lib/DeathAgregator.h
    lib/Menu.h
)

add_executable(lab6 src/main.cpp ${COMPILE_FILES})