cmake_minimum_required(VERSION 4.2)

project(task_management
        VERSION 0.1.0
        DESCRIPTION "Terminal-based Task Management App in C++"
        LANGUAGE CXX
)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if (MSVC)
    add_compile_options(/W4 /permissive-)
else ()
    add_compile_options(-Wall -Wextra -Wpedantic)
endif ()

find_package(nlohmann_json CONFIG REQUIRED)

add_executable(task_management
    src/main.cpp

    src/domain/task.cpp
    src/doamin/datetime.cpp

    src/storage/storage.cpp
)

target_include_directories(task_management
    PRIVATE
        include
)

target_link_libraries(task_management
    PRIVATE
        nlohmann_json:nlohmann_json
)

enable_testing()
add_subdirectory(tests)