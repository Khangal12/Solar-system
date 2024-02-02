#ifndef BODY_H
#define BODY_H

#include <string>

class Body {
public:
    Body(std::string name, double x, double y, double vx, double vy, double mass);
    ~Body();

    double getX() const;
    double getY() const;
    double getMass() const;
    std::string getName() const;

    void calculateForce(const Body& other, double& fx, double& fy) const;
    void updatePositionAndVelocity(double timeStep);
    void display() const;

    void setVx(double newVx);
    void setVy(double newVy);
    double getVx() const;
    double getVy() const;

public:
    std::string name;
    double x;
    double y;
    double vx;
    double vy;
    double mass;
};

#endif
