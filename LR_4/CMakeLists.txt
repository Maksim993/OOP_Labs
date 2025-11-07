cmake_minimum_required(VERSION 3.14)
project(LAB_4 VERSION 1.0.0 LANGUAGES CXX)

# Настройка стандарта C++
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Более надежный способ подключения Google Test
include(FetchContent)
FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG release-1.12.1
)
FetchContent_MakeAvailable(googletest)

# Основная программа
add_executable(LAB_4 
    src/main.cpp
)

target_include_directories(LAB_4 PUBLIC include)

# Тесты
add_executable(test_figures 
    tests/test_figures.cpp
)

target_include_directories(test_figures PUBLIC include)
target_link_libraries(test_figures PRIVATE gtest_main)

# Цель для запуска тестов
add_custom_target(run_tests
    COMMAND test_figures
    DEPENDS test_figures
    COMMENT "Running unit tests..."
)