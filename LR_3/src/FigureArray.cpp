#include "FigureArray.h"

void FigureArray::addHexagon(double x, double y, double radius) {
    figures.push_back(std::make_shared<Hexagon>(x, y, radius));
}

void FigureArray::addOctagon(double x, double y, double radius) {
    figures.push_back(std::make_shared<Octagon>(x, y, radius));
}

void FigureArray::addTriangle(double x, double y, double radius) {
    figures.push_back(std::make_shared<Triangle>(x, y, radius));
}

void FigureArray::removeFigure(int index) {
    if (index >= 0 && index < figures.size()) {
        figures.erase(figures.begin() + index);
    }
}

size_t FigureArray::size() const {
    return figures.size();
}

double FigureArray::totalArea() const {
    double total = 0;
    for (const auto& figure : figures) {
        total += figure->area();
    }
    return total;
}

void FigureArray::printAllCenters() const {
    std::cout << "Geometric Centers:" << std::endl;
    for (size_t i = 0; i < figures.size(); ++i) {
        auto center = figures[i]->getCenter();
        std::cout << "Figure " << i << ": (" << center.first << ", " << center.second << ")" << std::endl;
    }
}

void FigureArray::printAllAreas() const {
    std::cout << "Areas:" << std::endl;
    for (size_t i = 0; i < figures.size(); ++i) {
        std::cout << "Figure " << i << ": " << figures[i]->area() << std::endl;
    }
}

void FigureArray::printAllInfo() const {
    std::cout << "All Figures Information:" << std::endl;
    for (size_t i = 0; i < figures.size(); ++i) {
        std::cout << "Figure " << i << ": " << *figures[i] << std::endl;
    }
}

std::shared_ptr<Figure> FigureArray::operator[](size_t index) {
    return figures[index];
}

const std::shared_ptr<Figure> FigureArray::operator[](size_t index) const {
    return figures[index];
}