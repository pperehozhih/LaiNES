cmake_minimum_required(VERSION 2.8)

project(LaiNES)

set(CMAKE_CXX_EXTENSIONS OFF)

include(FindPackageHandleStandardArgs)

configure_file(cmake/SDL.cmake.in
               ${CMAKE_BINARY_DIR}/SDL/CMakeLists.txt)

execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
                WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/SDL )
execute_process(COMMAND ${CMAKE_COMMAND} --build .
                WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/SDL )

configure_file(cmake/SDL_image.cmake.in
               ${CMAKE_BINARY_DIR}/SDL_image/CMakeLists.txt)

execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
                WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/SDL_image )
execute_process(COMMAND ${CMAKE_COMMAND} --build .
                WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/SDL_image )

configure_file(cmake/SDL_ttf.cmake.in
               ${CMAKE_BINARY_DIR}/SDL_ttf/CMakeLists.txt)

execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
                WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/SDL_ttf )
execute_process(COMMAND ${CMAKE_COMMAND} --build .
                WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/SDL_ttf )

include_directories(
   apu
   src
   3rd
   ${CMAKE_BINARY_DIR}/root/include
)

link_directories(
   ${CMAKE_BINARY_DIR}/root/lib
)

# Root section
aux_source_directory(src SRC_ROOT_FILE)
file(GLOB HDR_ROOT_FILE "src/*.h*")

set(SRC_FILES ${SRC_FILES} ${SRC_ROOT_FILE})
set(HDR_FILES ${HDR_FILES} ${HDR_ROOT_FILE})
source_group("src" FILES ${SRC_ROOT_FILE} ${HDR_ROOT_FILE})

# APU section
aux_source_directory(apu SRC_APU_ROOT_FILE)
file(GLOB HDR_APU_ROOT_FILE "apu/*.h*")

set(SRC_FILES ${SRC_FILES} ${SRC_APU_ROOT_FILE})
set(HDR_FILES ${HDR_FILES} ${HDR_APU_ROOT_FILE})
source_group("apu" FILES ${SRC_APU_ROOT_FILE} ${HDR_APU_ROOT_FILE})

# Mapper section
aux_source_directory(src/mappers SRC_MAPPER_FILE)
file(GLOB HDR_MAPPER_FILE "src/mappers/*.h*")

set(SRC_FILES ${SRC_FILES} ${SRC_MAPPER_FILE})
set(HDR_FILES ${HDR_FILES} ${HDR_MAPPER_FILE})
source_group("src//mappers" FILES ${SRC_MAPPER_FILE} ${HDR_MAPPER_FILE})

# 3rd section
aux_source_directory(3rd SRC_3RD_FILE)
file(GLOB HDR_3RD_FILE "3rd/*.h*")

set(SRC_FILES ${SRC_FILES} ${SRC_3RD_FILE})
set(HDR_FILES ${HDR_FILES} ${HDR_3RD_FILE})
source_group("3rd" FILES ${SRC_3RD_FILE} ${HDR_3RD_FILE})

add_executable(${PROJECT_NAME} ${SRC_FILES} ${HDR_FILES})
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 14)
target_link_libraries(${PROJECT_NAME} -lSDL2 -lSDL2_image -lSDL2_ttf)
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                  COMMAND ${CMAKE_COMMAND} -E copy_directory
                  "${PROJECT_SOURCE_DIR}/res"
                  $<TARGET_FILE_DIR:${PROJECT_NAME}>) 
