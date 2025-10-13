#ifndef ELEVEN_H
#define ELEVEN_H

#include <iostream>
#include <vector>

class Eleven {
    unsigned char* nums;  // цифры числа
    size_t len;           // длина числа
    
    void trimZeros();
    
public:
    // конструкторы
    Eleven();
    Eleven(const size_t& n, unsigned char t = 0);
    Eleven(const std::initializer_list<unsigned char>& items);
    Eleven(const std::string& s);
    Eleven(const Eleven& other);
    Eleven(Eleven&& other) noexcept;
    
    ~Eleven() noexcept;
    
    // основные методы
    size_t length() const;
    unsigned char* getNums() const;
    
    bool equals(const Eleven& other) const;
    bool greater(const Eleven& other) const;
    bool less(const Eleven& other) const;
    
    Eleven plus(const Eleven& other) const;
    Eleven minus(const Eleven& other) const;
    
    std::string to_string() const;
    
    // операторы присваивания
    Eleven& operator=(const Eleven& other);
    Eleven& operator=(Eleven&& other) noexcept;
};

#endif