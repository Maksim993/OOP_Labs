#ifndef OCTAGON_H
#define OCTAGON_H

#include "Figure.h"

class Octagon : public Figure {
public:
    Octagon(double x = 0, double y = 0, double r = 1);
    
    double area() const override;
    void printVertices(std::ostream& os) const override;
    void readFromStream(std::istream& is) override;
    
    // Конструкторы и операторы
    Octagon(const Octagon& other);
    Octagon(Octagon&& other) noexcept;
    Octagon& operator=(const Octagon& other);
    Octagon& operator=(Octagon&& other) noexcept;
};

#endif