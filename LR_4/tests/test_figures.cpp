// test_figures.cpp
#include <gtest/gtest.h>
#include "Rectangle.h"
#include "Trapezoid.h"
#include "Rhombus.h"
#include "FigureArray.h"

TEST(FigureTest, RectangleArea) {
    Rectangle<double> rect(0, 0, 1);
    EXPECT_NEAR(rect.area(), 2.0, 0.001); // area = 2 * r^2 = 2
}

TEST(FigureTest, TrapezoidArea) {
    Trapezoid<double> trap(0, 0, 1);
    EXPECT_NEAR(trap.area(), 2.25, 0.001); // (1.8 + 1.2) * 1.5 / 2 = 2.25
}

TEST(FigureTest, RhombusArea) {
    Rhombus<double> rhomb(0, 0, 1);
    EXPECT_NEAR(rhomb.area(), 1.5, 0.001); // (2 * 1.5) / 2 = 1.5
}

TEST(FigureArrayTest, AddAndRemove) {
    FigureArray<double> array;
    array.addRectangle(0, 0, 1);
    array.addRhombus(1, 1, 2);
    
    EXPECT_EQ(array.size(), 2);
    
    array.removeFigure(0);
    EXPECT_EQ(array.size(), 1);
}

TEST(FigureArrayTest, TotalArea) {
    FigureArray<double> array;
    array.addRectangle(0, 0, 1);
    array.addRhombus(0, 0, 1);
    
    double total = array.totalArea();
    EXPECT_GT(total, 0);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}