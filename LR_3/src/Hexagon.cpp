#include "Hexagon.h"
#include <cmath>
#include <iostream>

Hexagon::Hexagon(double x, double y, double r) 
    : Figure(x, y, r, 6) {}

double Hexagon::area() const {
    return (3 * std::sqrt(3) * radius * radius) / 2;
}

void Hexagon::printVertices(std::ostream& os) const {
    for (int i = 0; i < 6; ++i) {
        double angle = 2 * M_PI * i / 6;
        double x = center_x + radius * std::cos(angle);
        double y = center_y + radius * std::sin(angle);
        os << "(" << x << ", " << y << ") ";
    }
}

void Hexagon::readFromStream(std::istream& is) {
    is >> center_x >> center_y >> radius;
    sides = 6;
}

Hexagon::Hexagon(const Hexagon& other) : Figure(other) {}

Hexagon::Hexagon(Hexagon&& other) noexcept : Figure(std::move(other)) {}

Hexagon& Hexagon::operator=(const Hexagon& other) {
    Figure::operator=(other);
    return *this;
}

Hexagon& Hexagon::operator=(Hexagon&& other) noexcept {
    Figure::operator=(std::move(other));
    return *this;
}