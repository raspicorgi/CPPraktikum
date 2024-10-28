#include <iostream>

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

    // Setters
    void setX(double x) { this->x = x; }
    void setY(double y) { this->y = y; }
    void setZ(double z) { this->z = z; }
    void setVx(double vx) { this->vx = vx; }
    void setVy(double vy) { this->vy = vy; }
    void setVz(double vz) { this->vz = vz; }
    void setMass(double mass) { this->mass = mass; }

    // Method to update position based on velocity
    void updatePosition(double time) {
        x += vx * time;
        y += vy * time;
        z += vz * time;
    }

    // Method to print the current state of the object
    void printState() const {
        std::cout << "Position: (" << x << ", " << y << ", " << z << ")\n";
        std::cout << "Velocity: (" << vx << ", " << vy << ", " << vz << ")\n";
        std::cout << "Mass: " << mass << "\n";
    }
};