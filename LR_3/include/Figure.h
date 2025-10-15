#ifndef FIGURE_H
#define FIGURE_H

#include <iostream>
#include <vector>
#include <memory>
#include <cmath>

#ifndef M_PI
#define M_PI 3.14159265358979323846264338327950288
#endif

class Figure {
protected:
    double center_x, center_y; // Координаты центра
    double radius;             // Радиус описанной окружности
    int sides;                 // Количество сторон

public:
    Figure(double x = 0, double y = 0, double r = 1, int s = 3);
    virtual ~Figure() = default;

    // Виртуальные методы
    virtual std::pair<double, double> getCenter() const;
    virtual double area() const = 0;
    virtual void printVertices(std::ostream& os) const = 0;
    virtual void readFromStream(std::istream& is) = 0;

    // Перегрузка операторов
    virtual bool operator==(const Figure& other) const;
    Figure& operator=(const Figure& other);
    
    // Приведение к double (площадь)
    operator double() const;

    // Дружественные операторы ввода/вывода
    friend std::ostream& operator<<(std::ostream& os, const Figure& fig);
    friend std::istream& operator>>(std::istream& is, Figure& fig);
};

#endif