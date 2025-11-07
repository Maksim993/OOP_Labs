#ifndef RHOMBUS_H
#define RHOMBUS_H

#include "Concepts.h"
#include "Figure.h"
#include <cmath>

template<Scalar T>
class Rhombus : public Figure<T> {
private:
    T diagonal1, diagonal2;

public:
    Rhombus(T x = 0, T y = 0, T r = 1) : Figure<T>(x, y, r) {
        // Для ромба, вписанного в окружность
        diagonal1 = r * 2;
        diagonal2 = r * 1.5;
    }
    
    double area() const override {
        return (static_cast<double>(diagonal1) * static_cast<double>(diagonal2)) / 2.0;
    }
    
    void printVertices(std::ostream& os) const override {
        T center_x = this->center->getX();
        T center_y = this->center->getY();
        T half_d1 = diagonal1 / 2;
        T half_d2 = diagonal2 / 2;
        
        os << "(" << center_x << ", " << center_y + half_d2 << ") ";
        os << "(" << center_x + half_d1 << ", " << center_y << ") ";
        os << "(" << center_x << ", " << center_y - half_d2 << ") ";
        os << "(" << center_x - half_d1 << ", " << center_y << ")";
    }
    
    void readFromStream(std::istream& is) override {
        T x, y, r;
        is >> x >> y >> r;
        this->center = std::make_unique<Point<T>>(x, y);
        this->radius = r;
        diagonal1 = r * 2;
        diagonal2 = r * 1.5;
    }
};

#endif