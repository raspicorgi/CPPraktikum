#include <iostream>
#include <Vector3d.hpp>

class Body {
private:
    double x, y, z;       
    double vx, vy, vz;    
    double mass;          

public:
    // Constructor
    Body(double x, double y, double z, double vx, double vy, double vz, double mass)
        : x(x), y(y), z(z), vx(vx), vy(vy), vz(vz), mass(mass) {}

    // Getters
    double getX() const { return x; }
    double getY() const { return y; }
    double getZ() const { return z; }
    double getVx() const { return vx; }
    double getVy() const { return vy; }
    double getVz() const { return vz; }
    double getMass() const { return mass; }
    Vector3d getPosition() const { return Vector3d(x, y, z); }
    Vector3d getVelocity() const { return Vector3d(vx, vy, vz); }

    // Setters
    void setX(double x) { this->x = x; }
    void setY(double y) { this->y = y; }
    void setZ(double z) { this->z = z; }
    void setVx(double vx) { this->vx = vx; }
    void setVy(double vy) { this->vy = vy; }
    void setVz(double vz) { this->vz = vz; }
    void setMass(double mass) { this->mass = mass; }

    // Method to print the current state of the object
    void printState() const {
        std::cout << "Position: (" << x << ", " << y << ", " << z << ")\n";
        std::cout << "Velocity: (" << vx << ", " << vy << ", " << vz << ")\n";
        std::cout << "Mass: " << mass << "\n";
    }
};