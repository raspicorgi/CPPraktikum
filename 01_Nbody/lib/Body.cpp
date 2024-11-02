#include <iostream>
#include "Body.hpp"



    // default constructor
    Body::Body() : id(-1), x(0), y(0), z(0), vx(0), vy(0), vz(0), mass(0) {}
    //id constructor
    Body::Body(int id) : id(id), x(0), y(0), z(0), vx(0), vy(0), vz(0), mass(0) {}
    // id and mass constructor
    Body::Body(int id, long double mass) : id(id), x(0), y(0), z(0), vx(0), vy(0), vz(0), mass(mass) {}
    // Constructor
    Body::Body(int id, long double x, long double y, long double z, long double vx, long double vy, long double vz, long double mass)
        : id(id), x(x), y(y), z(z), vx(vx), vy(vy), vz(vz), mass(mass) {}

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
    int Body::getId() const { return id; }

    // Setters
    void Body::setX(long double x) { this->x = x; }
    void Body::setY(long double y) { this->y = y; }
    void Body::setZ(long double z) { this->z = z; }
    void Body::setVx(long double vx) { this->vx = vx; }
    void Body::setVy(long double vy) { this->vy = vy; }
    void Body::setVz(long double vz) { this->vz = vz; }
    void Body::setMass(long double mass) { this->mass = mass; }
    void Body::setPosition(Vector3d position) {
        this-> x = position.getX();
        this-> y = position.getY();
        this-> z = position.getZ();
    }
    void Body::setVelocity(Vector3d velocity) {
        this->vx = velocity.getX();
        this->vy = velocity.getY();
        this->vz = velocity.getZ();
    }
    void Body::setId(int id) { this->id = id; }

    // Method to print the current state of the object
    void Body::printState() const {
        std::cout << "Body ID: " << id << ", ";
        std::cout << "Position: (" << x << ", " << y << ", " << z << "), ";
        std::cout << "Velocity: (" << vx << ", " << vy << ", " << vz << "), ";
        std::cout << "Mass: " << mass << "\n";
    }

    
    int Body::is_equal(Body other_body) const {
        if(this->id == other_body.getId()){
            return 1;
        }
        return 0;
        // if(this->x == other_body.getX() && this->y == other_body.getY() && this->z == other_body.getZ() && this->vx == other_body.getVx() && this->vy == other_body.getVy() && this->vz == other_body.getVz() && this->mass == other_body.getMass()){
        //     return 1;
        // }
        // return 0;
    }
