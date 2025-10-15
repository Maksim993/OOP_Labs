#ifndef FIGURE_ARRAY_H
#define FIGURE_ARRAY_H

#include "Figure.h"
#include "Hexagon.h"
#include "Octagon.h"
#include "Triangle.h"
#include <vector>
#include <memory>

class FigureArray {
private:
    std::vector<std::shared_ptr<Figure>> figures;

public:
    FigureArray() = default;
    
    // Добавление фигур
    void addHexagon(double x, double y, double radius);
    void addOctagon(double x, double y, double radius);
    void addTriangle(double x, double y, double radius);
    
    // Удаление по индексу
    void removeFigure(int index);
    
    // Получение информации
    size_t size() const;
    double totalArea() const;
    
    // Вывод информации
    void printAllCenters() const;
    void printAllAreas() const;
    void printAllInfo() const;
    
    // Доступ к фигурам
    std::shared_ptr<Figure> operator[](size_t index);
    const std::shared_ptr<Figure> operator[](size_t index) const;
};

#endif