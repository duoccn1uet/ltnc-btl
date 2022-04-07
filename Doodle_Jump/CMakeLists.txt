cmake_minimum_required(VERSION 3.0.0)
project(doodle_jump VERSION 0.1.0)

set(SDL2_INCLUDE_DIR D:/SDL/include)
set(SDL2_LIB_DIR D:/SDL/lib)

include_directories(${SDL2_INCLUDE_DIR})
link_directories(${SDL2_LIB_DIR})


#FILE(GLOB cpp_file ${CMAKE_SOURCE_DIR}/*.cpp)
file(GLOB cpp_file *.cpp)
add_executable(doodle_jump main.cpp Character.cpp CommonFunc.cpp CreateWindow.cpp Game.cpp
                           ImgProcess.cpp Map.cpp Menu.cpp Platform.cpp Text.cpp Timer.cpp Motion.cpp Option.cpp)

#add_executable(doodle_jump ${cpp_file})

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)

target_link_libraries(doodle_jump ${SDL2_LIBRARY} -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf)
