#ifndef BODY_HPP
#define BODY_HPP
#include "Vector3d.hpp"
#include <iostream>

class Body {
private:
    double x, y, z;   
    double vx, vy, vz;
    double mass;
    Vector3d position;
    Vector3d velocity;          

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
    Vector3d getPosition() const;
    Vector3d getVelocity() const;


    // Setters
    void setX(double x);
    void setY(double y);
    void setZ(double z);
    void setVx(double vx);
    void setVy(double vy);
    void setVz(double vz);
    void setMass(double mass);
     void setPosition(Vector3d position);
    void setVelocity(Vector3d velocity);
    // Method to print the current state of the object
    void printState() const;
     int is_equal(Body other_body);
};

#endif // BODY_HPP