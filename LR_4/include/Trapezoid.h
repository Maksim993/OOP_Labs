#ifndef TRAPEZOID_H
#define TRAPEZOID_H

#include "Concepts.h"
#include "Figure.h"
#include <cmath>

template<Scalar T>
class Trapezoid : public Figure<T> {
private:
    T top_base, bottom_base, height;

public:
    Trapezoid(T x = 0, T y = 0, T r = 1) : Figure<T>(x, y, r) {
        // Для равнобедренной трапеции, вписанной в окружность
        bottom_base = r * 1.8;
        top_base = r * 1.2;
        height = r * 1.5;
    }
    
    double area() const override {
        return (static_cast<double>(top_base) + static_cast<double>(bottom_base)) * static_cast<double>(height) / 2.0;
    }
    
    void printVertices(std::ostream& os) const override {
        T center_x = this->center->getX();
        T center_y = this->center->getY();
        T top_half = top_base / 2;
        T bottom_half = bottom_base / 2;
        T half_height = height / 2;
        
        os << "(" << center_x - bottom_half << ", " << center_y - half_height << ") ";
        os << "(" << center_x + bottom_half << ", " << center_y - half_height << ") ";
        os << "(" << center_x + top_half << ", " << center_y + half_height << ") ";
        os << "(" << center_x - top_half << ", " << center_y + half_height << ")";
    }
    
    void readFromStream(std::istream& is) override {
        T x, y, r;
        is >> x >> y >> r;
        this->center = std::make_unique<Point<T>>(x, y);
        this->radius = r;
        bottom_base = r * 1.8;
        top_base = r * 1.2;
        height = r * 1.5;
    }
};

#endif