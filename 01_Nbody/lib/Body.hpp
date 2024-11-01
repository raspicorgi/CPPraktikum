#ifndef BODY_HPP
#define BODY_HPP
#include <iostream>
#include "Vector3d.hpp"


class Body {
private:
    int id;
    double x, y, z;   
    double vx, vy, vz;
    double mass;        

public:
    /**
     * @brief Default constructor for the Body class.
     * Initializes all member variables to default values.
     */
    Body();

    /**
     * @brief Constructor for the Body class that initializes the body with a given id.
     * @param id The unique identifier for the body.
     */
    Body(int id);

    /**
     * @brief Constructor for the Body class that initializes all member variables.
     * @param id The unique identifier for the body.
     * @param x The initial x-coordinate of the body.
     * @param y The initial y-coordinate of the body.
     * @param z The initial z-coordinate of the body.
     * @param vx The initial velocity of the body along the x-axis.
     * @param vy The initial velocity of the body along the y-axis.
     * @param vz The initial velocity of the body along the z-axis.
     * @param mass The mass of the body.
     */
    Body(int id, double x, double y, double z, double vx, double vy, double vz, double mass);
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
    int getId() const;


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
    void setId(int id);
    int is_equal(Body other_body) const;
};

#endif // BODY_HPP