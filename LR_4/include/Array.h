#ifndef ARRAY_H
#define ARRAY_H

#include <memory>
#include <vector>
#include <stdexcept>
#include <utility>

template<typename T>
class Array {
private:
    std::vector<std::shared_ptr<T>> data;
    size_t capacity;

public:
    Array(size_t initial_capacity = 10) : capacity(initial_capacity) {
        data.reserve(capacity);
    }
    
    void add(std::shared_ptr<T> element) {
        if (data.size() >= capacity) {
            // Увеличиваем capacity и используем move семантику
            capacity *= 2;
            std::vector<std::shared_ptr<T>> new_data;
            new_data.reserve(capacity);
            for (auto& item : data) {
                new_data.push_back(std::move(item));
            }
            data = std::move(new_data);
        }
        data.push_back(std::move(element));
    }
    
    void remove(size_t index) {
        if (index >= data.size()) {
            throw std::out_of_range("Index out of range");
        }
        data.erase(data.begin() + index);
    }
    
    std::shared_ptr<T> operator[](size_t index) const {
        if (index >= data.size()) {
            throw std::out_of_range("Index out of range");
        }
        return data[index];
    }
    
    size_t size() const { return data.size(); }
    size_t getCapacity() const { return capacity; }
    
    // Для вычисления общей площади (специализация для фигур)
    template<typename U = T>
    auto totalArea() const -> decltype(std::declval<U>().area()) {
        double total = 0;
        for (const auto& item : data) {
            total += item->area();
        }
        return total;
    }
};

#endif