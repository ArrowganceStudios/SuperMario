cmake_minimum_required(VERSION 3.5)

project(SuperMario)
set(CMAKE_CXX_STANDARD 11)

find_package(PkgConfig)
if(NOT PKG_CONFIG_FOUND)
  message(FATAL_ERROR "pkg-config not found!")
endif()

pkg_check_modules(ALLEGRO5 REQUIRED
    allegro-5
    allegro_font-5
    allegro_ttf-5
    allegro_image-5
    allegro_primitives-5
)

file(GLOB SOURCE_FILES
    src/*.cpp
    src/*.hpp
)

add_executable(mario ${SOURCE_FILES})
target_link_libraries(mario ${ALLEGRO5_LIBRARIES})
target_include_directories(mario PUBLIC ${ALLEGRO5_INCLUDE_DIRS})
target_compile_options(mario PUBLIC ${ALLEGRO5_CFLAGS_OTHER})

file(COPY assets DESTINATION ${CMAKE_BINARY_DIR})
