#ifndef VECTOR3D_HPP
#define VECTOR3D_HPP

#include <cmath>
#include <vector>
#include <ostream>

class Vector3d {
public:
    // Constructors
    Vector3d();
    Vector3d(long double x, long double y, long double z);

    // Getters
    double getX() const;
    double getY() const;
    double getZ() const;

    // Setters
    void setX(long double x);
    void setY(long double y);
    void setZ(long double z);


    // Member functions
    long double magnitude() const;
    Vector3d normalize() const;
    long double scalar_product(Vector3d other) const;
    Vector3d cross_product(Vector3d other) const;

    // Operator overloads
    Vector3d operator+(const Vector3d& other) const;
    Vector3d operator-(const Vector3d& other) const;
    Vector3d operator*(long double scalar) const;
    Vector3d operator/(long double scalar) const;
    Vector3d operator+=(const Vector3d& other);
    Vector3d operator<<(std::ostream& os) const;

    friend std::ostream& operator<<(std::ostream& os, const Vector3d& vector);

private:
    long double x;
    long double y;
    long double z;
};

#endif // VECTOR3D_HPP