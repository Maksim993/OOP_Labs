#include <iostream>
#include <string>
#include "FixedBlockMemoryResource.h"
#include "DynamicArray.h"

// Сложный тип данных для демонстрации
struct Person {
    std::string name;
    int age;
    double salary;

    Person(const std::string& n = "", int a = 0, double s = 0.0) 
        : name(n), age(a), salary(s) {}

    Person(std::string&& n, int a = 0, double s = 0.0) 
        : name(std::move(n)), age(a), salary(s) {}

    friend std::ostream& operator<<(std::ostream& os, const Person& p) {
        return os << "Person{name: " << p.name << ", age: " << p.age 
                  << ", salary: " << p.salary << "}";
    }
};

void demo_simple_types() {
    std::cout << "\n=== ДЕМОНСТРАЦИЯ С ПРОСТЫМИ ТИПАМИ (int) ===\n";
    
    // Создаем аллокатор с фиксированным блоком памяти
    FixedBlockMemoryResource memory_resource(1024); // 1KB
    
    // Создаем динамический массив с нашим аллокатором
    DynamicArray<int> array(&memory_resource);
    
    // Добавляем элементы
    for (int i = 1; i <= 5; ++i) {
        array.push_back(i * 10);
    }
    
    // Демонстрация доступа по индексу
    std::cout << "\nДоступ по индексу:\n";
    for (size_t i = 0; i < array.size(); ++i) {
        std::cout << "array[" << i << "] = " << array[i] << "\n";
    }
    
    // Демонстрация итераторов
    std::cout << "\nИтерация с помощью итераторов:\n";
    for (auto it = array.begin(); it != array.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << "\n";
    
    // Демонстрация range-based for
    std::cout << "\nRange-based for loop:\n";
    for (const auto& element : array) {
        std::cout << element << " ";
    }
    std::cout << "\n";
    
    std::cout << "Размер: " << array.size() 
              << ", Вместимость: " << array.get_capacity() << "\n";
    std::cout << "Использовано памяти: " << memory_resource.get_used_memory() 
              << "/" << memory_resource.get_total_memory() << " байт\n";
}

void demo_complex_types() {
    std::cout << "\n=== ДЕМОНСТРАЦИЯ СО СЛОЖНЫМИ ТИПАМИ (Person) ===\n";
    
    // Создаем аллокатор с фиксированным блоком памяти
    FixedBlockMemoryResource memory_resource(2048); // 2KB
    
    // Создаем динамический массив с нашим аллокатором
    DynamicArray<Person> people(&memory_resource);
    
    // Добавляем сложные объекты
    people.push_back(Person("Alice", 25, 50000.0));
    people.push_back(Person("Bob", 30, 60000.0));
    
    // Демонстрация перемещения
    std::string name = "Charlie";
    people.push_back(Person(std::move(name), 35, 70000.0)); // Перемещаем
    
    // Демонстрация итераторов со сложными типами
    std::cout << "\nСписок людей:\n";
    for (const auto& person : people) {
        std::cout << person << "\n";
    }
    
    // Модификация через итератор
    std::cout << "\nПосле увеличения зарплаты на 10%:\n";
    for (auto it = people.begin(); it != people.end(); ++it) {
        it->salary *= 1.1;
        std::cout << *it << "\n";
    }
    
    std::cout << "Использовано памяти: " << memory_resource.get_used_memory() 
              << "/" << memory_resource.get_total_memory() << " байт\n";
}

void demo_memory_reuse() {
    std::cout << "\n=== ДЕМОНСТРАЦИЯ ПОВТОРНОГО ИСПОЛЬЗОВАНИЯ ПАМЯТИ ===\n";
    
    FixedBlockMemoryResource memory_resource(512); // 512 байт
    
    {
        DynamicArray<int> array1(&memory_resource);
        array1.push_back(1);
        array1.push_back(2);
        array1.push_back(3);
        std::cout << "Массив 1 создан, размер: " << array1.size() << "\n";
    } // array1 уничтожается здесь, память освобождается
    
    {
        DynamicArray<int> array2(&memory_resource);
        array2.push_back(4);
        array2.push_back(5);
        std::cout << "Массив 2 создан в той же памяти, размер: " << array2.size() << "\n";
    }
}

int main() {
    std::cout << "ЛАБОРАТОРНАЯ РАБОТА №5: ИТЕРАТОРЫ И АЛЛОКАТОРЫ\n";
    std::cout << "Контейнер: Динамический массив\n";
    std::cout << "Аллокатор: Фиксированный блок памяти с std::list\n";
    
    try {
        demo_simple_types();
        demo_complex_types();
        demo_memory_reuse();
        
        std::cout << "\n=== ВСЕ ДЕМОНСТРАЦИИ УСПЕШНО ЗАВЕРШЕНЫ ===\n";
    } catch (const std::exception& e) {
        std::cerr << "ОШИБКА: " << e.what() << "\n";
        return 1;
    }
    
    return 0;
}