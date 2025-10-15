#include "Octagon.h"
#include <cmath>
#include <iostream>

Octagon::Octagon(double x, double y, double r) 
    : Figure(x, y, r, 8) {}

double Octagon::area() const {
    return 2 * radius * radius * (1 + std::sqrt(2));
}

void Octagon::printVertices(std::ostream& os) const {
    for (int i = 0; i < 8; ++i) {
        double angle = 2 * M_PI * i / 8;
        double x = center_x + radius * std::cos(angle);
        double y = center_y + radius * std::sin(angle);
        os << "(" << x << ", " << y << ") ";
    }
}

void Octagon::readFromStream(std::istream& is) {
    is >> center_x >> center_y >> radius;
    sides = 8;
}

Octagon::Octagon(const Octagon& other) : Figure(other) {}

Octagon::Octagon(Octagon&& other) noexcept : Figure(std::move(other)) {}

Octagon& Octagon::operator=(const Octagon& other) {
    Figure::operator=(other);
    return *this;
}

Octagon& Octagon::operator=(Octagon&& other) noexcept {
    Figure::operator=(std::move(other));
    return *this;
}