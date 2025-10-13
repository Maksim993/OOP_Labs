cmake_minimum_required(VERSION 3.14)
project(LAB_1 VERSION 1.0.0 LANGUAGES CXX)

# Настройка стандарта C++
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Поиск Google Test с проверкой доступных путей
if(NOT GTEST_ROOT AND EXISTS "C:/Program Files (x86)/googletest-distribution")
    set(GTEST_ROOT "C:/Program Files (x86)/googletest-distribution")
endif()

find_package(GTest REQUIRED)
if(NOT GTest_FOUND)
    message(FATAL_ERROR "Google Test not found. Please install it or set GTEST_ROOT variable.")
endif()

# Основная программа
add_executable(LAB_1 
    src/main.cpp 
    src/my_function.cpp
)
target_include_directories(LAB_1 PUBLIC include)

# Тесты
add_executable(test_my_function 
    tests/test_my_function.cpp 
    src/my_function.cpp
)
target_include_directories(test_my_function PUBLIC include ${GTEST_INCLUDE_DIRS})
target_link_libraries(test_my_function PRIVATE GTest::gtest GTest::gtest_main)

# Цель для запуска тестов
add_custom_target(run_tests
    COMMAND $<TARGET_FILE:test_my_function>
    DEPENDS test_my_function
    COMMENT "Running unit tests..."
    VERBATIM
)

# Добавляем тесты в CTest
include(CTest)
add_test(NAME unit_tests COMMAND test_my_function)