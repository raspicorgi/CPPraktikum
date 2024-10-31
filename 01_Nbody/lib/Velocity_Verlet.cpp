#include "Integrator.hpp"
#include "Tools.cpp"

class Velocity_Verlet : public Integrator{
    public:
        std::vector<Body> integrate(const std::vector<Body>* bodies, const double maxTimeStep) override {
            std::vector<Body> new_bodies;
            for(Body current_body : *bodies){
                Body new_current_body = current_body;
                std::vector<double> accelaration = Tools::calc_acceleration(*bodies,current_body);
                new_current_body.setX(current_body.getX() + current_body.getVx() * maxTimeStep + 0.5 * accelaration[0]*pow(maxTimeStep,2));
                new_current_body.setY(current_body.getY() + current_body.getVy() * maxTimeStep + 0.5 * accelaration[1]*pow(maxTimeStep,2));
                new_current_body.setZ(current_body.getZ() + current_body.getVz() * maxTimeStep + 0.5 * accelaration[2]*pow(maxTimeStep,2));
                std::vector<double> new_accelaration = Tools::calc_acceleration(*bodies,new_current_body);
                new_current_body.setVx(current_body.getVx() + 0.5*(accelaration[0]+new_accelaration[0])*maxTimeStep);
                new_current_body.setVy(current_body.getVy() + 0.5*(accelaration[1]+new_accelaration[1])*maxTimeStep);
                new_current_body.setVz(current_body.getVz() + 0.5*(accelaration[2]+new_accelaration[2])*maxTimeStep);
                new_bodies.push_back(new_current_body);
            } 
            return new_bodies;
        }
};