#include "Eleven.h"
#include <stdexcept>
#include <algorithm>

// пустое число
Eleven::Eleven() : len(1) {
    nums = new unsigned char[1];
    nums[0] = 0;
}

// число из n одинаковых цифр
Eleven::Eleven(const size_t& n, unsigned char t) : len(n) {
    if (n == 0) throw std::invalid_argument("размер не может быть 0");
    if (t > 10) throw std::invalid_argument("цифра должна быть от 0 до 10");
    
    nums = new unsigned char[n];
    for (size_t i = 0; i < n; i++) {
        nums[i] = t;
    }
    trimZeros();
}

// из списка {1,2,3}
Eleven::Eleven(const std::initializer_list<unsigned char>& items) {
    len = items.size();
    if (len == 0) throw std::invalid_argument("список не может быть пустым");
    
    nums = new unsigned char[len];
    
    size_t idx = 0;
    for (auto it = items.end() - 1; it >= items.begin(); --it) {
        unsigned char d = *it;
        if (d > 10) {
            delete[] nums;
            throw std::invalid_argument("неверная цифра в списке");
        }
        nums[idx++] = d;
        if (idx >= len) break;
    }
    trimZeros();
}

// из строки
Eleven::Eleven(const std::string& s) {
    if (s.empty()) throw std::invalid_argument("строка не может быть пустой");
    
    len = s.length();
    nums = new unsigned char[len];
    
    for (size_t i = 0; i < len; i++) {
        char c = s[i];
        unsigned char d;
        
        if (c >= '0' && c <= '9') {
            d = c - '0';
        } else if (c == 'A' || c == 'a') {
            d = 10;
        } else {
            delete[] nums;
            throw std::invalid_argument("неверный символ в строке");
        }
        
        nums[len - 1 - i] = d;
    }
    trimZeros();
}

// копирование
Eleven::Eleven(const Eleven& other) : len(other.len) {
    nums = new unsigned char[len];
    for (size_t i = 0; i < len; i++) {
        nums[i] = other.nums[i];
    }
}

// перемещение
Eleven::Eleven(Eleven&& other) noexcept : nums(other.nums), len(other.len) {
    other.nums = nullptr;
    other.len = 0;
}

// деструктор
Eleven::~Eleven() noexcept {
    delete[] nums;
}

// убираем ведущие нули
void Eleven::trimZeros() {
    size_t new_len = len;
    while (new_len > 1 && nums[new_len - 1] == 0) {
        new_len--;
    }
    
    if (new_len != len) {
        unsigned char* new_nums = new unsigned char[new_len];
        for (size_t i = 0; i < new_len; i++) {
            new_nums[i] = nums[i];
        }
        delete[] nums;
        nums = new_nums;
        len = new_len;
    }
}

size_t Eleven::length() const {
    return len;
}

unsigned char* Eleven::getNums() const {
    unsigned char* copy = new unsigned char[len];
    for (size_t i = 0; i < len; i++) copy[i] = nums[i];
    return copy;
}

bool Eleven::equals(const Eleven& other) const {
    if (len != other.len) return false;
    for (size_t i = 0; i < len; i++) {
        if (nums[i] != other.nums[i]) return false;
    }
    return true;
}

bool Eleven::greater(const Eleven& other) const {
    if (len > other.len) return true;
    if (len < other.len) return false;
    
    for (int i = len - 1; i >= 0; i--) {
        if (nums[i] > other.nums[i]) return true;
        if (nums[i] < other.nums[i]) return false;
    }
    return false;
}

bool Eleven::less(const Eleven& other) const {
    return !equals(other) && !greater(other);
}

// сложение
Eleven Eleven::plus(const Eleven& other) const {
    size_t max_len = std::max(len, other.len) + 1;
    std::vector<unsigned char> res(max_len, 0);
    
    unsigned char carry = 0;
    for (size_t i = 0; i < max_len; i++) {
        unsigned char sum = carry;
        if (i < len) sum += nums[i];
        if (i < other.len) sum += other.nums[i];
        res[i] = sum % 11;
        carry = sum / 11;
    }
    
    // в строку
    std::string s;
    for (int i = res.size() - 1; i >= 0; i--) {
        if (res[i] < 10) {
            s += '0' + res[i];
        } else {
            s += 'A';
        }
    }
    
    // убираем нули в начале
    size_t start = s.find_first_not_of('0');
    if (start == std::string::npos) {
        return Eleven("0");
    }
    
    return Eleven(s.substr(start));
}

// вычитание
Eleven Eleven::minus(const Eleven& other) const {
    if (less(other)) throw std::invalid_argument("нельзя вычитать большее число");
    
    std::vector<unsigned char> res(len, 0);
    int borrow = 0;
    
    for (size_t i = 0; i < len; i++) {
        int diff = nums[i] - borrow;
        if (i < other.len) diff -= other.nums[i];
        if (diff < 0) {
            diff += 11;
            borrow = 1;
        } else {
            borrow = 0;
        }
        res[i] = diff;
    }
    
    // в строку
    std::string s;
    for (int i = res.size() - 1; i >= 0; i--) {
        if (res[i] < 10) {
            s += '0' + res[i];
        } else {
            s += 'A';
        }
    }
    
    // убираем нули в начале
    size_t start = s.find_first_not_of('0');
    if (start == std::string::npos) {
        return Eleven("0");
    }
    
    return Eleven(s.substr(start));
}

std::string Eleven::to_string() const {
    std::string s;
    for (int i = len - 1; i >= 0; i--) {
        if (nums[i] < 10) {
            s += '0' + nums[i];
        } else {
            s += 'A';
        }
    }
    return s;
}

Eleven& Eleven::operator=(const Eleven& other) {
    if (this != &other) {
        delete[] nums;
        len = other.len;
        nums = new unsigned char[len];
        for (size_t i = 0; i < len; i++) {
            nums[i] = other.nums[i];
        }
    }
    return *this;
}

Eleven& Eleven::operator=(Eleven&& other) noexcept {
    if (this != &other) {
        delete[] nums;
        nums = other.nums;
        len = other.len;
        other.nums = nullptr;
        other.len = 0;
    }
    return *this;
}