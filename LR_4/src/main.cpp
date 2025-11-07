#include <iostream>
#include "FigureArray.h"

void displayMenu() {
    std::cout << "\n=== Figure Management System ===" << std::endl;
    std::cout << "1. Add Rectangle" << std::endl;
    std::cout << "2. Add Trapezoid" << std::endl;
    std::cout << "3. Add Rhombus" << std::endl;
    std::cout << "4. Remove Figure" << std::endl;
    std::cout << "5. Display All Figures" << std::endl;
    std::cout << "6. Display Centers" << std::endl;
    std::cout << "7. Display Areas" << std::endl;
    std::cout << "8. Display Total Area" << std::endl;
    std::cout << "9. Exit" << std::endl;
    std::cout << "Choose an option: ";
}

int main() {
    FigureArray<double> figures;
    int choice;
    
    do {
        displayMenu();
        std::cin >> choice;
        
        switch (choice) {
            case 1: {
                double x, y, radius;
                std::cout << "Enter center (x y) and radius: ";
                std::cin >> x >> y >> radius;
                figures.addRectangle(x, y, radius);
                std::cout << "Rectangle added successfully!" << std::endl;
                break;
            }
            case 2: {
                double x, y, radius;
                std::cout << "Enter center (x y) and radius: ";
                std::cin >> x >> y >> radius;
                figures.addTrapezoid(x, y, radius);
                std::cout << "Trapezoid added successfully!" << std::endl;
                break;
            }
            case 3: {
                double x, y, radius;
                std::cout << "Enter center (x y) and radius: ";
                std::cin >> x >> y >> radius;
                figures.addRhombus(x, y, radius);
                std::cout << "Rhombus added successfully!" << std::endl;
                break;
            }
            case 4: {
                if (figures.size() == 0) {
                    std::cout << "No figures to remove!" << std::endl;
                    break;
                }
                size_t index;
                std::cout << "Enter index to remove (0-" << figures.size() - 1 << "): ";
                std::cin >> index;
                if (index < figures.size()) {
                    figures.removeFigure(index);
                    std::cout << "Figure removed successfully!" << std::endl;
                } else {
                    std::cout << "Invalid index!" << std::endl;
                }
                break;
            }
            case 5:
                if (figures.size() == 0) {
                    std::cout << "No figures to display!" << std::endl;
                } else {
                    figures.printAllInfo();
                }
                break;
            case 6:
                if (figures.size() == 0) {
                    std::cout << "No figures to display!" << std::endl;
                } else {
                    figures.printAllCenters();
                }
                break;
            case 7:
                if (figures.size() == 0) {
                    std::cout << "No figures to display!" << std::endl;
                } else {
                    figures.printAllAreas();
                }
                break;
            case 8:
                if (figures.size() == 0) {
                    std::cout << "No figures to calculate area!" << std::endl;
                } else {
                    std::cout << "Total area: " << figures.totalArea() << std::endl;
                }
                break;
            case 9:
                std::cout << "Goodbye!" << std::endl;
                break;
            default:
                std::cout << "Invalid option! Please try again." << std::endl;
        }
    } while (choice != 9);
    
    return 0;
}