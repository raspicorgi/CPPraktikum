#include "Integrator.hpp"
#include "Tools.cpp"


class Hermite : public Integrator {
    public:
         std::vector<Body> integrate(const std::vector<Body>* bodies, const double maxTimeStep) override {
            std::vector<Body> newBodies;
            for(Body current_body : *bodies)
            {
                Body predicted_body = current_body;
                Body corrected_body = current_body;
                Vector3d initial_accelaration = Tools::calc_acceleration_3dvec(*bodies,current_body);
                Vector3d initial_jerk = Tools::calc_jerk_3dvec(*bodies,current_body);
                predicted_body.setVelocity(current_body.getVelocity() + initial_accelaration * maxTimeStep + initial_jerk * 0.5 * pow(maxTimeStep,2));
                predicted_body.setPosition(current_body.getPosition() + current_body.getVelocity() * maxTimeStep + initial_accelaration * 0.5 * pow(maxTimeStep,2) + initial_jerk *(1/6)* pow(maxTimeStep,3));
                Vector3d predicted_accelaration = Tools::calc_acceleration_3dvec(*bodies,predicted_body);
                Vector3d predicted_jerk = Tools::calc_jerk_3dvec(*bodies,predicted_body);
                Vector3d second_derivative_accelaration = ((initial_accelaration - predicted_accelaration)*(-3)/(pow(maxTimeStep,2)) - (((initial_jerk * 2)-predicted_jerk)/(maxTimeStep) )) * 2;
                Vector3d third_derivative_accelaration = (((initial_accelaration - predicted_accelaration)*(2)/(pow(maxTimeStep,3))) + ((initial_jerk-predicted_jerk)/(pow(maxTimeStep,2))))*6;
                corrected_body.setVelocity(predicted_body.getVelocity() + second_derivative_accelaration *(1/6) * pow(maxTimeStep,3) + third_derivative_accelaration * (1/24) * pow(maxTimeStep,4));
                corrected_body.setPosition(predicted_body.getPosition() + second_derivative_accelaration * (1/24) * pow(maxTimeStep,4) + third_derivative_accelaration * (1/120) * pow(maxTimeStep,5));
                newBodies.push_back(corrected_body);
            }
            return newBodies;
        }
};