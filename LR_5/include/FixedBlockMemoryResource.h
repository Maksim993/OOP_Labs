#ifndef FIXEDBLOCKMEMORYRESOURCE_H
#define FIXEDBLOCKMEMORYRESOURCE_H

#include <memory_resource>
#include <list>
#include <vector>
#include <cstddef>
#include <iostream>
#include <algorithm>  //для std::find_if

class FixedBlockMemoryResource : public std::pmr::memory_resource {
private:
    void* memory_block;           // Указатель на фиксированный блок памяти
    size_t block_size;           // Размер всего блока
    size_t used_memory;          // Использованная память
    std::list<std::pair<void*, size_t>> allocated_blocks; // Список выделенных блоков: (указатель, размер)

public:
    // Конструктор: выделяет фиксированный блок памяти
    FixedBlockMemoryResource(size_t total_size) 
        : block_size(total_size), used_memory(0) {
        memory_block = ::operator new(total_size);
        std::cout << "FixedBlockMemoryResource: выделен блок " << total_size << " байт\n";
    }

    // Деструктор: освобождает всю память
    ~FixedBlockMemoryResource() override {
        // Освобождаем все выделенные блоки
        for (auto& block : allocated_blocks) {
            ::operator delete(block.first, block.second);
        }
        // Освобождаем основной блок
        ::operator delete(memory_block, block_size);
        std::cout << "FixedBlockMemoryResource: блок памяти освобожден\n";
    }

protected:
    // Выделение памяти
    void* do_allocate(size_t bytes, size_t alignment) override {
        // Проверяем, хватает ли места
        if (used_memory + bytes > block_size) {
            throw std::bad_alloc();
        }
        // Выделяем память из нашего блока
        void* ptr = static_cast<char*>(memory_block) + used_memory;
        used_memory += bytes;
        // Сохраняем информацию о выделенном блоке
        allocated_blocks.emplace_back(ptr, bytes);
        
        std::cout << "do_allocate: выделено " << bytes << " байт по адресу " << ptr 
                  << " (использовано: " << used_memory << "/" << block_size << ")\n";
        
        return ptr;
    }

    // Освобождение памяти (помечаем как свободную для повторного использования)
    void do_deallocate(void* ptr, size_t bytes, size_t alignment) override {
        // Ищем блок в списке выделенных
        auto it = std::find_if(allocated_blocks.begin(), allocated_blocks.end(),
            [ptr](const auto& block) { return block.first == ptr; });
        if (it != allocated_blocks.end()) {
            std::cout << "do_deallocate: освобождено " << bytes << " байт по адресу " << ptr << "\n";
            allocated_blocks.erase(it); // Удаляем из списка выделенных
            
            // В реальной реализации здесь можно добавить логику для повторного использования памяти
            // Но для простоты мы просто отмечаем память как свободную
        } else {
            std::cout << "do_deallocate: попытка освободить невыделенную память!\n";
        }
    }
    // Сравнение аллокаторов
    bool do_is_equal(const std::pmr::memory_resource& other) const noexcept override {
        return this == &other; // Сравниваем по указателям
    }

public:
    // Методы для получения информации
    size_t get_used_memory() const { return used_memory; }
    size_t get_total_memory() const { return block_size; }
    size_t get_allocated_blocks_count() const { return allocated_blocks.size(); }
};

#endif