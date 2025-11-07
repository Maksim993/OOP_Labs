#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "Concepts.h"
#include "Figure.h"
#include <cmath>

template<Scalar T>
class Rectangle : public Figure<T> {
private:
    T width, height;

public:
    Rectangle(T x = 0, T y = 0, T r = 1) : Figure<T>(x, y, r) {
        // Для прямоугольника, вписанного в окружность
        width = r * std::sqrt(2);
        height = r * std::sqrt(2);
    }
    
    double area() const override {
        return static_cast<double>(width) * static_cast<double>(height);
    }
    
    void printVertices(std::ostream& os) const override {
        T half_width = width / 2;
        T half_height = height / 2;
        T center_x = this->center->getX();
        T center_y = this->center->getY();
        
        os << "(" << center_x - half_width << ", " << center_y - half_height << ") ";
        os << "(" << center_x + half_width << ", " << center_y - half_height << ") ";
        os << "(" << center_x + half_width << ", " << center_y + half_height << ") ";
        os << "(" << center_x - half_width << ", " << center_y + half_height << ")";
    }
    
    void readFromStream(std::istream& is) override {
        T x, y, r;
        is >> x >> y >> r;
        this->center = std::make_unique<Point<T>>(x, y);
        this->radius = r;
        width = r * std::sqrt(2);
        height = r * std::sqrt(2);
    }
};

#endif