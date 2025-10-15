cmake_minimum_required(VERSION 3.14)
project(LAB_3 VERSION 1.0.0 LANGUAGES CXX)

# Настройка стандарта C++
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Более надежный способ подключения Google Test
include(FetchContent)
FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG release-1.12.1  # Стабильная версия
)
FetchContent_MakeAvailable(googletest)

# Основная программа
add_executable(LAB_3 
    src/main.cpp
    src/Figure.cpp
    src/Hexagon.cpp
    src/Octagon.cpp
    src/Triangle.cpp
    src/FigureArray.cpp
)

target_include_directories(LAB_3 PUBLIC include)

# Тесты
add_executable(test_figures 
    tests/test_figures.cpp
    src/Figure.cpp
    src/Hexagon.cpp
    src/Octagon.cpp
    src/Triangle.cpp
    src/FigureArray.cpp
)

target_include_directories(test_figures PUBLIC include)
target_link_libraries(test_figures PRIVATE gtest_main)

# Цель для запуска тестов
add_custom_target(run_tests
    COMMAND test_figures
    DEPENDS test_figures
    COMMENT "Running unit tests..."
)