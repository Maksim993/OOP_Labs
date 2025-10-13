cmake_minimum_required(VERSION 3.14)
project(LAB_2 VERSION 1.0.0 LANGUAGES CXX)

# Настройка стандарта C++ (C++17 для Google Test)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Автоматическая загрузка Google Test
include(FetchContent)
FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG release-1.12.1  # Стабильная версия
)
FetchContent_MakeAvailable(googletest)


# Основная программа
add_executable(LAB_2 
    src/main.cpp
    src/Eleven.cpp
)

# Указываем где искать заголовочные файлы
target_include_directories(LAB_2 PUBLIC include)

# Тесты
add_executable(test_eleven 
    tests/test_eleven.cpp
    src/Eleven.cpp
)

# Указываем пути для тестов
target_include_directories(test_eleven PUBLIC include)
target_link_libraries(test_eleven PRIVATE gtest_main)

# Цель для удобного запуска тестов
add_custom_target(run_tests
    COMMAND test_eleven
    DEPENDS test_eleven
    COMMENT "Running unit tests..."
)