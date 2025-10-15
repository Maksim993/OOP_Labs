#include <gtest/gtest.h>
#include "Hexagon.h"
#include "Octagon.h"
#include "Triangle.h"
#include "FigureArray.h"

TEST(FigureTest, HexagonArea) {
    Hexagon hex(0, 0, 1);
    EXPECT_NEAR(hex.area(), 2.598, 0.001);
}

TEST(FigureTest, OctagonArea) {
    Octagon oct(0, 0, 1);
    EXPECT_NEAR(oct.area(), 4.828, 0.001);
}

TEST(FigureTest, TriangleArea) {
    Triangle tri(0, 0, 1);
    EXPECT_NEAR(tri.area(), 1.299, 0.001);
}

TEST(FigureTest, FigureComparison) {
    Hexagon hex1(0, 0, 1);
    Hexagon hex2(0, 0, 1);
    Hexagon hex3(1, 1, 2);
    
    EXPECT_TRUE(hex1 == hex2);
    EXPECT_FALSE(hex1 == hex3);
}

TEST(FigureArrayTest, AddAndRemove) {
    FigureArray array;
    array.addHexagon(0, 0, 1);
    array.addTriangle(1, 1, 2);
    
    EXPECT_EQ(array.size(), 2);
    
    array.removeFigure(0);
    EXPECT_EQ(array.size(), 1);
}

TEST(FigureArrayTest, TotalArea) {
    FigureArray array;
    array.addHexagon(0, 0, 1);
    array.addTriangle(0, 0, 1);
    
    double total = array.totalArea();
    EXPECT_GT(total, 0);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}