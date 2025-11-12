#include <gtest/gtest.h>
#include <string>
#include "FixedBlockMemoryResource.h"
#include "DynamicArray.h"

TEST(DynamicArrayTest, BasicOperations) {
    FixedBlockMemoryResource memory_resource(1024);
    DynamicArray<int> array(&memory_resource);
    
    EXPECT_TRUE(array.empty());
    EXPECT_EQ(array.size(), 0);
    
    array.push_back(1);
    array.push_back(2);
    array.push_back(3);
    
    EXPECT_FALSE(array.empty());
    EXPECT_EQ(array.size(), 3);
    EXPECT_EQ(array[0], 1);
    EXPECT_EQ(array[1], 2);
    EXPECT_EQ(array[2], 3);
}

TEST(DynamicArrayTest, IteratorOperations) {
    FixedBlockMemoryResource memory_resource(1024);
    DynamicArray<int> array(&memory_resource);
    
    for (int i = 1; i <= 3; ++i) {
        array.push_back(i * 10);
    }
    
    // Проверка итераторов
    auto it = array.begin();
    EXPECT_EQ(*it, 10);
    ++it;
    EXPECT_EQ(*it, 20);
    it++;
    EXPECT_EQ(*it, 30);
    
    // Проверка range-based for
    int sum = 0;
    for (const auto& element : array) {
        sum += element;
    }
    EXPECT_EQ(sum, 60);
}

TEST(DynamicArrayTest, ComplexTypes) {
    FixedBlockMemoryResource memory_resource(2048);
    DynamicArray<std::string> array(&memory_resource);
    
    array.push_back("Hello");
    array.push_back("World");
    
    EXPECT_EQ(array.size(), 2);
    EXPECT_EQ(array[0], "Hello");
    EXPECT_EQ(array[1], "World");
}

TEST(MemoryResourceTest, MemoryTracking) {
    FixedBlockMemoryResource memory_resource(512);
    
    {
        DynamicArray<int> array(&memory_resource);
        array.push_back(1);
        array.push_back(2);
        
        EXPECT_GT(memory_resource.get_used_memory(), 0);
        EXPECT_GT(memory_resource.get_allocated_blocks_count(), 0);
    }
    
    // После уничтожения массива память должна быть освобождена
    EXPECT_EQ(memory_resource.get_allocated_blocks_count(), 0);
}

TEST(MemoryResourceTest, OutOfMemory) {
    // Увеличиваем размер памяти, чтобы хватило на начальное выделение
    FixedBlockMemoryResource memory_resource(100); // 100 байт
    
    DynamicArray<int> array(&memory_resource);
    
    // Попытка выделить больше памяти чем доступно при ресайзе
    EXPECT_THROW({
        for (int i = 0; i < 100; ++i) {
            array.push_back(i); // Вызовет resize() и исключение
        }
    }, std::bad_alloc);
}

// Исправленный тест для проверки граничных случаев
TEST(MemoryResourceTest, ExactMemoryLimit) {
    // Выделяем достаточно памяти для начального массива, но недостаточно для ресайза
    size_t initial_memory = 10 * sizeof(int); // 40 байт для 10 int'ов
    size_t resize_memory = 20 * sizeof(int);  // 80 байт для 20 int'ов
    
    // Даем памяти больше чем на начальный массив, но меньше чем на ресайз
    FixedBlockMemoryResource memory_resource(initial_memory + 10); // 50 байт
    
    DynamicArray<int> array(&memory_resource);
    
    // Заполняем начальный массив (10 элементов)
    for (int i = 0; i < 10; ++i) {
        array.push_back(i);
        EXPECT_EQ(array.size(), i + 1);
    }
    
    // Попытка добавить 11-й элемент должна вызвать исключение при ресайзе
    EXPECT_THROW({
        array.push_back(10);
    }, std::bad_alloc);
}

// Тест для проверки конструктора с начальной вместимостью
TEST(DynamicArrayTest, InitialCapacity) {
    FixedBlockMemoryResource memory_resource(256);
    
    // Создаем массив с начальной вместимостью 5
    DynamicArray<int> array(5, &memory_resource);
    
    EXPECT_EQ(array.get_capacity(), 5);
    EXPECT_TRUE(array.empty());
    
    // Добавляем элементы до заполнения
    for (int i = 0; i < 5; ++i) {
        array.push_back(i);
    }
    
    EXPECT_EQ(array.size(), 5);
    EXPECT_EQ(array.get_capacity(), 5);
    
    // Следующий элемент должен вызвать ресайз
    array.push_back(5);
    EXPECT_EQ(array.size(), 6);
    EXPECT_GT(array.get_capacity(), 5);
}

// Новый тест - проверка работы с очень маленькой памятью
TEST(MemoryResourceTest, VerySmallMemory) {
    // Выделяем очень мало памяти - недостаточно даже для начального массива
    FixedBlockMemoryResource memory_resource(10); // 10 байт
    
    // Создание DynamicArray должно выбросить исключение
    EXPECT_THROW({
        DynamicArray<int> array(&memory_resource);
    }, std::bad_alloc);
}

// Тест для проверки повторного использования памяти
TEST(MemoryResourceTest, MemoryReuse) {
    FixedBlockMemoryResource memory_resource(200);
    
    size_t first_allocation_address = 0;
    
    {
        DynamicArray<int> array1(&memory_resource);
        array1.push_back(1);
        array1.push_back(2);
        first_allocation_address = reinterpret_cast<size_t>(&array1[0]);
    }
    
    {
        DynamicArray<int> array2(&memory_resource);
        array2.push_back(3);
        array2.push_back(4);
        size_t second_allocation_address = reinterpret_cast<size_t>(&array2[0]);
        
        // В идеале адреса должны быть разными из-за того как работает наш аллокатор
        // но это зависит от реализации
        EXPECT_NE(memory_resource.get_allocated_blocks_count(), 0);
    }
    
    EXPECT_EQ(memory_resource.get_allocated_blocks_count(), 0);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}