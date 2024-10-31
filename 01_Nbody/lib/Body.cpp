#include <iostream>
#include "Vector3d.hpp"
#include "Body.hpp"


    // Constructor
    Body::Body(double x, double y, double z, double vx, double vy, double vz, double mass)
        : x(x), y(y), z(z), vx(vx), vy(vy), vz(vz), position(Vector3d(x,y,z)), velocity(Vector3d(vx,vy,vz)), mass(mass) {}

    // Getters
    double Body::getX() const { return x; }
    double Body::getY() const { return y; }
    double Body::getZ() const { return z; }
    double Body::getVx() const { return vx; }
    double Body::getVy() const { return vy; }
    double Body::getVz() const { return vz; }
    double Body::getMass() const { return mass; }
    Vector3d Body::getPosition() const { return Vector3d(x, y, z); }
    Vector3d Body::getVelocity() const { return Vector3d(vx, vy, vz); }

    // Setters
    void Body::setX(double x) { this->x = x; }
    void Body::setY(double y) { this->y = y; }
    void Body::setZ(double z) { this->z = z; }
    void Body::setVx(double vx) { this->vx = vx; }
    void Body::setVy(double vy) { this->vy = vy; }
    void Body::setVz(double vz) { this->vz = vz; }
    void Body::setMass(double mass) { this->mass = mass; }
    void Body::setPosition(Vector3d position) { this->position = position; }
    void Body::setVelocity(Vector3d velocity) { this->velocity = velocity; }

    // Method to print the current state of the object
    void Body::printState() const {
        std::cout << "Position: (" << x << ", " << y << ", " << z << ")\n";
        std::cout << "Velocity: (" << vx << ", " << vy << ", " << vz << ")\n";
        std::cout << "Mass: " << mass << "\n";
    }

    int Body::is_equal(Body other_body){
        if(this->x == other_body.getX() && this->y == other_body.getY() && this->z == other_body.getZ() && this->vx == other_body.getVx() && this->vy == other_body.getVy() && this->vz == other_body.getVz() && this->mass == other_body.getMass()){
            return 1;
        }
        return 0;
    }
