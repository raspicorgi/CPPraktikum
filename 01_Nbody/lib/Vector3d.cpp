#include "Vector3d.hpp"

// Constructors
Vector3d::Vector3d() : x(0), y(0), z(0) {}
Vector3d::Vector3d(long double x, long double y, long double z) : x(x), y(y), z(z) {}

// Getters
double Vector3d::getX() const { return x; }
double Vector3d::getY() const { return y; }
double Vector3d::getZ() const { return z; }

// Setters
void Vector3d::setX(long double x) { this->x = x; }
void Vector3d::setY(long double y) { this->y = y; }
void Vector3d::setZ(long double z) { this->z = z; }

// Member functions
long double Vector3d::magnitude() const { return std::sqrt(x * x + y * y + z * z); }
Vector3d Vector3d::normalize() const { long double mag = magnitude(); return Vector3d(x / mag, y / mag, z / mag); }

/**
 * @brief Computes the scalar (dot) product of this vector with another vector.
 * 
 * The scalar product is defined as the sum of the products of the corresponding components of the two vectors.
 * 
 * @param other The vector to compute the scalar product with.
 * @return The scalar product of this vector and the other vector.
 */
long double Vector3d::scalar_product(Vector3d other) const { return (x * other.x + y * other.y + z * other.z); }

/**
 * @brief Computes the cross product of this vector with another vector.
 * 
 * The cross product (a x b) is computed, where a is the vector on which the function is called.
 *  
 * @param other The vector to compute the cross product with.
 * @return A new Vector3d representing the cross product of this vector and the other vector.
 */
Vector3d Vector3d::cross_product(Vector3d other) const { return Vector3d(y * other.z - z * other.y, z * other.x - x * other.z, x * other.y - y * other.x); }

// Operator overloads
Vector3d Vector3d::operator+(const Vector3d& other) const { return Vector3d(x + other.x, y + other.y, z + other.z); }
Vector3d Vector3d::operator-(const Vector3d& other) const { return Vector3d(x - other.x, y - other.y, z - other.z); }
Vector3d Vector3d::operator*(long double scalar) const { return Vector3d(x * scalar, y * scalar, z * scalar); }
Vector3d Vector3d::operator/(long double scalar) const { return Vector3d(x / scalar, y / scalar, z / scalar); }
Vector3d Vector3d::operator+=(const Vector3d& other) { x += other.x; y += other.y; z += other.z; return *this; }