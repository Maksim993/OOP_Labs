#include "Triangle.h"
#include <cmath>
#include <iostream>

Triangle::Triangle(double x, double y, double r) 
    : Figure(x, y, r, 3) {}

double Triangle::area() const {
    return (3 * std::sqrt(3) * radius * radius) / 4;
}

void Triangle::printVertices(std::ostream& os) const {
    for (int i = 0; i < 3; ++i) {
        double angle = 2 * M_PI * i / 3;
        double x = center_x + radius * std::cos(angle);
        double y = center_y + radius * std::sin(angle);
        os << "(" << x << ", " << y << ") ";
    }
}

void Triangle::readFromStream(std::istream& is) {
    is >> center_x >> center_y >> radius;
    sides = 3;
}

Triangle::Triangle(const Triangle& other) : Figure(other) {}

Triangle::Triangle(Triangle&& other) noexcept : Figure(std::move(other)) {}

Triangle& Triangle::operator=(const Triangle& other) {
    Figure::operator=(other);
    return *this;
}

Triangle& Triangle::operator=(Triangle&& other) noexcept {
    Figure::operator=(std::move(other));
    return *this;
}