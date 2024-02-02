#include "Body.h"
#include <cmath>
#include <iostream>

const double G = 0.00005; // Gravitational constant

Body::Body(std::string name, double x, double y, double vx, double vy, double mass)
    : name(name), x(x), y(y), vx(vx), vy(vy), mass(mass) {}

Body::~Body() {}

double Body::getX() const {
    return x;
}

double Body::getY() const {
    return y;
}

double Body::getMass() const {
    return mass;
}

std::string Body::getName() const {
    return name;
}

void Body::calculateForce(const Body& other, double& fx, double& fy) const {
    // hoyer biyiin hoorondoh huch zai
    double dx = other.x - x;
    double dy = other.y - y;
    double distance = sqrt(dx * dx + dy * dy);
    double force = G * (mass * other.mass) / (distance * distance);

    // huch oloh heseg
    fx = force * (dx / distance);
    fy = force * (dy / distance);
}

void Body::updatePositionAndVelocity(double timeStep) {
    // hurdatgal ashiglan pos updateleh
    x += vx * timeStep;
    y += vy * timeStep;
}

void Body::display() const {
    // Display the body information
    std::cout << "Body " << name << " - Position: (" << x << ", " << y << ") - Mass: " << mass << std::endl;
}

void Body::setVx(double newVx) {
    vx = newVx;
}

void Body::setVy(double newVy) {
    vy = newVy;
}

double Body::getVx() const {
    return vx;
}

double Body::getVy() const {
    return vy;
}
