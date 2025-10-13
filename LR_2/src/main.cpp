#include <iostream>
#include "Eleven.h"

void show_work() {
    std::cout << "=== Работа с 11-ричными числами ===" << std::endl;
    
    try {
        Eleven a("146");
        Eleven b("123");
        Eleven c("555");
        
        std::cout << "a: " << a.to_string() << std::endl;
        std::cout << "b: " << b.to_string() << std::endl;
        std::cout << "c: " << c.to_string() << std::endl;

        std::cout << "\nСравнения:" << std::endl;
        std::cout << "a == b: " << (a.equals(b) ? "да" : "нет") << std::endl;
        std::cout << "a > b: " << (a.greater(b) ? "да" : "нет") << std::endl;
        std::cout << "a < b: " << (a.less(b) ? "да" : "нет") << std::endl;

        std::cout << "\nАрифметика:" << std::endl;
        Eleven sum = a.plus(b);
        std::cout << a.to_string() << " + " << b.to_string() << " = " << sum.to_string() << std::endl;
        
        Eleven diff = a.minus(b);
        std::cout << a.to_string() << " - " << b.to_string() << " = " << diff.to_string() << std::endl;
        
        try {
            Eleven diff2 = b.minus(a);
        } catch (const std::exception& e) {
            std::cout << "Ошибка: " << e.what() << " (ожидаемо)" << std::endl;
        }
        
    } catch (const std::exception& e) {
        std::cerr << "Ошибка: " << e.what() << std::endl;
    }
}

void simple_demo() {
    std::cout << "\n=== Простые примеры ===" << std::endl;
    
    Eleven x("A");
    Eleven y("1");
    Eleven z = x.plus(y);
    std::cout << "A + 1 = " << z.to_string() << std::endl;
    
    Eleven p("15");
    Eleven q("3");
    Eleven r = p.minus(q);
    std::cout << "15 - 3 = " << r.to_string() << std::endl;
}

int main() {
    std::cout << "Лабораторная работа по 11-ричным числам" << std::endl;
    show_work();
    simple_demo();
    std::cout << "\nГотово!" << std::endl;
    return 0;
}