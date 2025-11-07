#ifndef FIGURE_ARRAY_H
#define FIGURE_ARRAY_H

#include "Concepts.h"
#include "Array.h"
#include "Rectangle.h"
#include "Trapezoid.h"
#include "Rhombus.h"
#include <iostream>
#include <memory>

template<Scalar T>
class FigureArray {
private:
    Array<Figure<T>> figures;

public:
    FigureArray(size_t initial_capacity = 10) : figures(initial_capacity) {}
    
    void addRectangle(T x, T y, T radius) {
        auto rect = std::make_shared<Rectangle<T>>(x, y, radius);
        figures.add(std::static_pointer_cast<Figure<T>>(rect));
    }
    
    void addTrapezoid(T x, T y, T radius) {
        auto trap = std::make_shared<Trapezoid<T>>(x, y, radius);
        figures.add(std::static_pointer_cast<Figure<T>>(trap));
    }
    
    void addRhombus(T x, T y, T radius) {
        auto rhomb = std::make_shared<Rhombus<T>>(x, y, radius);
        figures.add(std::static_pointer_cast<Figure<T>>(rhomb));
    }
    
    void removeFigure(size_t index) {
        figures.remove(index);
    }
    
    size_t size() const { return figures.size(); }
    
    double totalArea() const {
        double total = 0;
        for (size_t i = 0; i < figures.size(); ++i) {
            total += figures[i]->area();
        }
        return total;
    }
    
    void printAllCenters() const {
        std::cout << "Geometric Centers:" << std::endl;
        for (size_t i = 0; i < figures.size(); ++i) {
            auto center = figures[i]->getCenter();
            std::cout << "Figure " << i << ": (" << center.getX() << ", " << center.getY() << ")" << std::endl;
        }
    }
    
    void printAllAreas() const {
        std::cout << "Areas:" << std::endl;
        for (size_t i = 0; i < figures.size(); ++i) {
            std::cout << "Figure " << i << ": " << figures[i]->area() << std::endl;
        }
    }
    
    void printAllInfo() const {
        std::cout << "All Figures Information:" << std::endl;
        for (size_t i = 0; i < figures.size(); ++i) {
            std::cout << "Figure " << i << ": " << *figures[i] << std::endl;
        }
    }
    
    std::shared_ptr<Figure<T>> operator[](size_t index) const {
        return figures[index];
    }
};

#endif