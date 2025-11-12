#ifndef DYNAMICARRAYITERATOR_H
#define DYNAMICARRAYITERATOR_H

#include <iterator>
#include <type_traits>

template<typename T>
class DynamicArrayIterator {
private:
    T* ptr;

public:
    // Требования итератора
    using iterator_category = std::forward_iterator_tag;
    using value_type = std::remove_cv_t<T>;
    using difference_type = std::ptrdiff_t;
    using pointer = T*;
    using reference = T&;

    // Конструкторы
    DynamicArrayIterator(T* p = nullptr) : ptr(p) {}
    
    // Копирование
    DynamicArrayIterator(const DynamicArrayIterator& other) : ptr(other.ptr) {}
    
    template<typename U>
    DynamicArrayIterator(const DynamicArrayIterator<U>& other) : ptr(other.ptr) {}

    // Операторы доступа
    reference operator*() const { return *ptr; }
    pointer operator->() const { return ptr; }

    // Префиксные операторы
    DynamicArrayIterator& operator++() {
        ++ptr;
        return *this;
    }

    DynamicArrayIterator operator++(int) {
        DynamicArrayIterator temp = *this;
        ++ptr;
        return temp;
    }

    // Операторы сравнения
    bool operator==(const DynamicArrayIterator& other) const { return ptr == other.ptr; }
    bool operator!=(const DynamicArrayIterator& other) const { return ptr != other.ptr; }

    // Приведение типов
    operator DynamicArrayIterator<const T>() const { 
        return DynamicArrayIterator<const T>(ptr); 
    }

    // Для доступа к внутреннему указателю (только для разработки)
    T* get_pointer() const { return ptr; }
};

#endif