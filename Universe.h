#ifndef UNIVERSE_H
#define UNIVERSE_H

#include "Body.h"
#include <vector>

class Universe {
public:
    Universe(std::string filename);
    ~Universe();

    void readDataFile(std::string filename);
    void displayBodies() const;
    void initializePositions();
    void updateBodies(double timeStep);
    void clearScreen() const;
    void putText(const std::string& text, double x, double y) const;

private:
    std::vector<Body> bodies;
    double screenWidth;
    double screenHeight;
    double maxX;
    double maxY;
};

#endif
