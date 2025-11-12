#ifndef DYNAMICARRAY_H
#define DYNAMICARRAY_H

#include <memory_resource>
#include <iterator>
#include <stdexcept>
#include <iostream>
#include <utility>  // Добавляем для std::move
#include "DynamicArrayIterator.h"

template<typename T>
class DynamicArray {
private:
    T* data;                            // Указатель на массив данных
    size_t capacity;                    // Вместимость массива
    size_t size_;                       // Текущий размер
    std::pmr::polymorphic_allocator<T> allocator; // Полиморфный аллокатор

public:
    // Итераторы
    using iterator = DynamicArrayIterator<T>;
    using const_iterator = DynamicArrayIterator<const T>;

    // Конструкторы
    DynamicArray(std::pmr::memory_resource* resource = std::pmr::get_default_resource()) 
        : capacity(10), size_(0), allocator(resource) {
        data = allocator.allocate(capacity);
        std::cout << "DynamicArray: создан с вместимостью " << capacity << "\n";
    }

    DynamicArray(size_t initial_capacity, std::pmr::memory_resource* resource = std::pmr::get_default_resource())
        : capacity(initial_capacity), size_(0), allocator(resource) {
        data = allocator.allocate(capacity);
        std::cout << "DynamicArray: создан с вместимостью " << capacity << "\n";
    }

    // Деструктор
    ~DynamicArray() {
        // Уничтожаем объекты
        for (size_t i = 0; i < size_; ++i) {
            allocator.destroy(data + i);
        }
        // Освобождаем память
        allocator.deallocate(data, capacity);
        std::cout << "DynamicArray: уничтожен\n";
    }

    // Копирование запрещено (для простоты)
    DynamicArray(const DynamicArray&) = delete;
    DynamicArray& operator=(const DynamicArray&) = delete;

    // Перемещение
    DynamicArray(DynamicArray&& other) noexcept
        : data(other.data), capacity(other.capacity), size_(other.size_), 
          allocator(std::move(other.allocator)) {
        other.data = nullptr;
        other.capacity = 0;
        other.size_ = 0;
    }

    DynamicArray& operator=(DynamicArray&& other) noexcept {
        if (this != &other) {
            // Освобождаем текущие ресурсы
            for (size_t i = 0; i < size_; ++i) {
                allocator.destroy(data + i);
            }
            allocator.deallocate(data, capacity);

            // Перемещаем ресурсы
            data = other.data;
            capacity = other.capacity;
            size_ = other.size_;
            allocator = std::move(other.allocator);

            // Обнуляем other
            other.data = nullptr;
            other.capacity = 0;
            other.size_ = 0;
        }
        return *this;
    }

    // Добавление элемента
    void push_back(const T& value) {
        if (size_ >= capacity) {
            resize(capacity * 2);
        }
        allocator.construct(data + size_, value);
        ++size_;
        std::cout << "push_back: добавлен элемент, размер: " << size_ << "\n";
    }

    // Добавление элемента с перемещением
    void push_back(T&& value) {
        if (size_ >= capacity) {
            resize(capacity * 2);
        }
        allocator.construct(data + size_, std::move(value));
        ++size_;
        std::cout << "push_back: добавлен элемент (move), размер: " << size_ << "\n";
    }

    // Доступ к элементам
    T& operator[](size_t index) {
        if (index >= size_) {
            throw std::out_of_range("Index out of range");
        }
        return data[index];
    }

    const T& operator[](size_t index) const {
        if (index >= size_) {
            throw std::out_of_range("Index out of range");
        }
        return data[index];
    }

    // Размер и вместимость
    size_t size() const { return size_; }
    size_t get_capacity() const { return capacity; }
    bool empty() const { return size_ == 0; }

    // Итераторы
    iterator begin() { return iterator(data); }
    iterator end() { return iterator(data + size_); }
    const_iterator begin() const { return const_iterator(data); }
    const_iterator end() const { return const_iterator(data + size_); }
    const_iterator cbegin() const { return const_iterator(data); }
    const_iterator cend() const { return const_iterator(data + size_); }

private:
    // Изменение размера массива
    void resize(size_t new_capacity) {
        std::cout << "resize: изменение вместимости с " << capacity << " на " << new_capacity << "\n";
        
        T* new_data = allocator.allocate(new_capacity);
        
        // Копируем существующие элементы
        for (size_t i = 0; i < size_; ++i) {
            allocator.construct(new_data + i, std::move(data[i]));
            allocator.destroy(data + i);
        }
        
        // Освобождаем старую память
        allocator.deallocate(data, capacity);
        
        data = new_data;
        capacity = new_capacity;
    }
};

#endif