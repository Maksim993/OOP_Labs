#ifndef FIGURE_H
#define FIGURE_H

// Для M_PI на Windows
#define _USE_MATH_DEFINES
#include <cmath>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

#include "Point.h"
#include <memory>
#include <iostream>
#include "Concepts.h"

template<Scalar T>
class Figure {
protected:
    std::unique_ptr<Point<T>> center;
    T radius;

public:
    Figure(T x = 0, T y = 0, T r = 1) 
        : center(std::make_unique<Point<T>>(x, y)), radius(r) {}
    
    virtual ~Figure() = default;

    // Виртуальные методы
    Point<T> getCenter() const { return *center; }
    virtual double area() const = 0;
    virtual void printVertices(std::ostream& os) const = 0;
    virtual void readFromStream(std::istream& is) = 0;

    // Перегрузка операторов
    virtual bool operator==(const Figure<T>& other) const {
        return *center == other.getCenter() && radius == other.radius;
    }
    
    Figure& operator=(const Figure& other) {
        if (this != &other) {
            center = std::make_unique<Point<T>>(other.getCenter());
            radius = other.radius;
        }
        return *this;
    }

    // Приведение к double (площадь)
    operator double() const { return area(); }

    // Дружественные операторы ввода/вывода
    friend std::ostream& operator<<(std::ostream& os, const Figure& fig) {
        os << "Center: " << *(fig.center) << ", Radius: " << fig.radius << ", ";
        os << "Vertices: ";
        fig.printVertices(os);
        return os;
    }

    friend std::istream& operator>>(std::istream& is, Figure& fig) {
        fig.readFromStream(is);
        return is;
    }
};

#endif