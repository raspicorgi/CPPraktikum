#ifndef VECTOR3D_HPP
#define VECTOR3D_HPP

#include <cmath>
#include <vector>

class Vector3d {
public:
    // Constructors
    Vector3d();
    Vector3d(double x, double y, double z);

    // Getters
    double getX() const;
    double getY() const;
    double getZ() const;

    // Setters
    void setX(double x);
    void setY(double y);
    void setZ(double z);


    // Member functions
    double magnitude() const;
    Vector3d normalize() const;
    double scalar_product(Vector3d other) const;
    Vector3d cross_product(Vector3d other) const;

    // Operator overloads
    Vector3d operator+(const Vector3d& other) const;
    Vector3d operator-(const Vector3d& other) const;
    Vector3d operator*(double scalar) const;
    Vector3d operator/(double scalar) const;

private:
    double x, y, z;
};

#endif // VECTOR3D_HPP