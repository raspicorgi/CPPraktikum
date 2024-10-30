#ifndef VECTOR3D_HPP
#define VECTOR3D_HPP

class Vector3d {
public:
    // Constructors
    Vector3d();
    Vector3d(double x, double y, double z);

    // Member functions
    double magnitude() const;
    Vector3d normalize() const;

    // Operator overloads
    Vector3d operator+(const Vector3d& other) const;
    Vector3d operator-(const Vector3d& other) const;
    Vector3d operator*(double scalar) const;
    Vector3d operator/(double scalar) const;

private:
    double x, y, z;
};

#endif // VECTOR3D_HPP