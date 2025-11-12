cmake_minimum_required(VERSION 3.15)
project(LAB_5 VERSION 1.0.0 LANGUAGES CXX)

# Настройка стандарта C++
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Настройка выходных директорий
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Подключение GoogleTest
include(FetchContent)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/tags/v1.13.0.zip
)
FetchContent_MakeAvailable(googletest)

# Основная программа
add_executable(LAB_5 
    src/main.cpp
)

target_include_directories(LAB_5 PUBLIC include)

# Тесты
add_executable(test_dynamic_array 
    tests/test_dynamic_array.cpp
)

target_include_directories(test_dynamic_array PUBLIC include)
target_link_libraries(test_dynamic_array PRIVATE GTest::gtest_main)

# Для Windows
if(WIN32)
    target_compile_definitions(LAB_5 PRIVATE _USE_MATH_DEFINES)
    target_compile_definitions(test_dynamic_array PRIVATE _USE_MATH_DEFINES)
endif()

# Цели для запуска
add_custom_target(run
    COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/LAB_5.exe
    DEPENDS LAB_5
    COMMENT "Запуск основной программы..."
)

add_custom_target(test
    COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/test_dynamic_array.exe
    DEPENDS test_dynamic_array
    COMMENT "Запуск тестов..."
)