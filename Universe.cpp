#include "Universe.h"
#include <fstream>
#include <iostream>
#include <cmath>
const double G = 0.00005; // G

Universe::Universe(std::string filename) {
    readDataFile(filename);
    screenWidth = 100; // terminaliin undur urt
    screenHeight = 40; // 
    maxX = 400;        //
    maxY = 400;        // Uusgej baiga hemje
    initializePositions();
}

Universe::~Universe() {}

void Universe::readDataFile(std::string filename) {
    std::ifstream inputFile(filename);
    if (!inputFile.is_open()) {
        std::cerr << "Error opening file: " << filename << std::endl;
        exit(1);
    }

    double gravitationalConstant;
    inputFile >> gravitationalConstant;

    while (!inputFile.eof()) {
        std::string name;
        double x, y, vx, vy, mass;
        inputFile >> name >> x >> y >> vx >> vy >> mass;
        bodies.emplace_back(name, x, y, vx, vy, mass);
    }

    inputFile.close();
}

void Universe::displayBodies() const {
    // terminaliig ehled ustgah
    clearScreen();

    // Bvh Biyetiin medeellig haruullah
    for (const auto& body : bodies) {
        putText(body.getName(), static_cast<unsigned>(body.getX()), static_cast<unsigned>(body.getY()));
    }
}

void Universe::initializePositions() {
    const double centerX = maxX / 2.0;
    const double centerY = maxY / 2.0;
//nariig hiih
    if (!bodies.empty()) {
        bodies[0].x = centerX;
        bodies[0].y = centerY;
    }

    const double numBodies = bodies.size() - 1;
    const double sunMass = bodies[0].getMass(); // nariig hiih vildel

   
    for (size_t i = 1; i < bodies.size(); ++i) {
        double angle = (i - 1) * (2.0 * M_PI / numBodies);
        double distance = 50.0 + i * 30.0; // narnas distance bodoh
        double x = centerX + distance * cos(angle);
        double y = centerY + distance * sin(angle);

        // hurd
        double speed = sqrt(G * sunMass / distance);
        double vx = -speed * sin(angle);
        double vy = speed * cos(angle);

        bodies[i].x = x;
        bodies[i].y = y;
        bodies[i].setVx(vx);
        bodies[i].setVy(vy);
    }
}

void Universe::updateBodies(double timeStep) {

    // pos bolon hurdatgalar uurchluh
    for (auto& body : bodies) {
        double totalForceX = 0.0;
        double totalForceY = 0.0;

        for (const auto& other : bodies) {
            if (&body != &other) {
                double forceX, forceY;
                body.calculateForce(other, forceX, forceY);
                totalForceX += forceX;
                totalForceY += forceY;
            }
        }

        double accelerationX = totalForceX / body.getMass();
        double accelerationY = totalForceY / body.getMass();

        body.setVx(body.getVx() + accelerationX * timeStep);
        body.setVy(body.getVy() + accelerationY * timeStep);
    }

    // buh huch hurdatgalaar bodoj positioniig uurchluh
    for (auto& body : bodies) {
        body.x += body.getVx() * timeStep;
        body.y += body.getVy() * timeStep;
    }
}

void Universe::clearScreen() const {
    std::cout << "\x1B[2J\x1B[H";
}

void Universe::putText(const std::string& text, double x, double y) const {
    // Map world coordinates to screen coordinates
    unsigned screenX = static_cast<unsigned>(x * screenWidth / maxX);
    unsigned screenY = static_cast<unsigned>(y * screenHeight / maxY);

    // Print the text at the mapped screen coordinates
    std::cout << "\033[" << screenY << ";" << screenX << "H";
    std::cout << text << std::flush;
}
