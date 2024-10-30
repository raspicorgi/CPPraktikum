#ifndef BODY_HPP
#define BODY_HPP

#include <iostream>

class Body {
private:
    double x, y, z;   
    double vx, vy, vz;
    double mass;      

public:
    // Constructor
    Body(double x, double y, double z, double vx, double vy, double vz, double mass);

    // Getters
    double getX() const;
    double getY() const;
    double getZ() const;
    double getVx() const;
    double getVy() const;
    double getVz() const;
    double getMass() const;

    // Setters
    void setX(double x);
    void setY(double y);
    void setZ(double z);
    void setVx(double vx);
    void setVy(double vy);
    void setVz(double vz);
    void setMass(double mass);

    // Method to print the current state of the object
    void printState() const;
};

#endif // BODY_HPP