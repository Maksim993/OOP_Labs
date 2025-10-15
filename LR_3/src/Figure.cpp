#include "Figure.h"

Figure::Figure(double x, double y, double r, int s) 
    : center_x(x), center_y(y), radius(r), sides(s) {}

std::pair<double, double> Figure::getCenter() const {
    return {center_x, center_y};
}

bool Figure::operator==(const Figure& other) const {
    return center_x == other.center_x && 
           center_y == other.center_y && 
           radius == other.radius && 
           sides == other.sides;
}

Figure& Figure::operator=(const Figure& other) {
    if (this != &other) {
        center_x = other.center_x;
        center_y = other.center_y;
        radius = other.radius;
        sides = other.sides;
    }
    return *this;
}

Figure::operator double() const {
    return area();
}

std::ostream& operator<<(std::ostream& os, const Figure& fig) {
    os << "Center: (" << fig.center_x << ", " << fig.center_y << "), ";
    os << "Radius: " << fig.radius << ", ";
    os << "Sides: " << fig.sides << ", ";
    os << "Vertices: ";
    fig.printVertices(os);
    return os;
}

std::istream& operator>>(std::istream& is, Figure& fig) {
    fig.readFromStream(is);
    return is;
}