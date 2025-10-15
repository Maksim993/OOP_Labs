#include <iostream>
#include <memory>
#include "FigureArray.h"

void displayMenu() {
    std::cout << "\n=== Figure Management System ===" << std::endl;
    std::cout << "1. Add Hexagon" << std::endl;
    std::cout << "2. Add Octagon" << std::endl;
    std::cout << "3. Add Triangle" << std::endl;
    std::cout << "4. Remove Figure" << std::endl;
    std::cout << "5. Display All Figures" << std::endl;
    std::cout << "6. Display Centers" << std::endl;
    std::cout << "7. Display Areas" << std::endl;
    std::cout << "8. Display Total Area" << std::endl;
    std::cout << "9. Exit" << std::endl;
    std::cout << "Choose an option: ";
}

int main() {
    FigureArray figures;
    int choice;
    
    do {
        displayMenu();
        std::cin >> choice;
        
        switch (choice) {
            case 1: {
                double x, y, radius;
                std::cout << "Enter center (x y) and radius: ";
                std::cin >> x >> y >> radius;
                figures.addHexagon(x, y, radius);
                break;
            }
            case 2: {
                double x, y, radius;
                std::cout << "Enter center (x y) and radius: ";
                std::cin >> x >> y >> radius;
                figures.addOctagon(x, y, radius);
                break;
            }
            case 3: {
                double x, y, radius;
                std::cout << "Enter center (x y) and radius: ";
                std::cin >> x >> y >> radius;
                figures.addTriangle(x, y, radius);
                break;
            }
            case 4: {
                int index;
                std::cout << "Enter index to remove: ";
                std::cin >> index;
                figures.removeFigure(index);
                break;
            }
            case 5:
                figures.printAllInfo();
                break;
            case 6:
                figures.printAllCenters();
                break;
            case 7:
                figures.printAllAreas();
                break;
            case 8:
                std::cout << "Total area: " << figures.totalArea() << std::endl;
                break;
            case 9:
                std::cout << "Goodbye!" << std::endl;
                break;
            default:
                std::cout << "Invalid option!" << std::endl;
        }
    } while (choice != 9);
    
    return 0;
}