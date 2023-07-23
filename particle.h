//
// Created by Ilya Belov on 7/23/23.
//

#ifndef N_BODY_SIMULATIONS_PARTICLE_H
#define N_BODY_SIMULATIONS_PARTICLE_H

#endif //N_BODY_SIMULATIONS_PARTICLE_H


#include "n_body_lib.h"

class Particle {
private:
    string name;
    float mass;
    vector<VectorXd> positions;
    vector<VectorXd> velocities;
    vector<VectorXd> accelerations;
    string color;
    float angle;

    vector<float> times;
public:
    // Constructor with arguments
    // Name, sPosition, sVelocity, mass,
    Particle(const string &namep, const float &massp, const VectorXd &positionp, const VectorXd &velocityp, const string &colorp, const float &anglep) {
        name = namep;
        mass = massp;
        positions.push_back(positionp);
        velocities.push_back(velocityp);
        color = colorp;
        angle = anglep;

        times.push_back(0.0);
        cout << "Particle initialized ---";
    };

    void set_acceleration(const VectorXd& accel) { accelerations.push_back(accel); };
    void set_last_position(const VectorXd& pos) {
        cout << "s\n" << positions.back() << "\ns";
        positions.pop_back();
        cout << "p\n" << positions.back() << "\np";
        positions.push_back(pos);
    };

    void offset(const VectorXd& offset_vector) {
        // cout << "\nOff pos back: " << positions.back() << "\n";
        // positions.back() = positions.back() - offset_vector;
        set_last_position(positions.back() - offset_vector);
    };

    VectorXd f_I_p(const vector<Particle> &particles) {
        VectorXd force {{0, 0}};
        for (auto & other : particles) {
            // force from element added to old force. But multiplied to binary expression for equality.
            if (other.positions.front() != positions.front()) {
                force += f_i(positions.back(), other.get_positions().back(), mass, other.get_mass() );
            }
        }
        return force;
    };

    void iteration(const double &step, const vector<Particle> &particles) {
        accelerations.push_back(f_I_p(particles)/mass);
        velocities.push_back( eiler(velocities.back(), accelerations.back(), step) );
        positions.push_back( eiler(positions.back(), accelerations.back(), step) );
        times.push_back(times.back() + step);
    };

    void print_log() {
        cout << "\n - General " << name << " : " << mass << ", " << color << ", " << angle;
        cout << "\n - Positions\n";
        for (auto & i : positions) {
            cout << i << " ";
        };
//        cout << "\n - Velocities\n";
//        for (auto & i : velocities) {
//            cout << i << " ";
//        };
        cout << "\n - Accelerations\n";
        for (auto & i : accelerations) {
            cout << i << " ";
        };
    };

    const string &get_name() const {return name; }

    const vector<VectorXd> &get_positions() const { return positions; };

    const VectorXd &get_last_position() const { return positions.back(); };

    const float &get_mass() const { return mass; };

    VectorXd const rotate(const VectorXd &r, const float &angle_deg) {
        double angle_rad = radians(angle_deg);
        MatrixXd rot_mx {{cos(angle_rad), sin(angle_rad)}, {-sin(angle_rad), cos(angle_rad)}};
        return rot_mx*r;
    };

    void rotate_self() {
        positions.front() = rotate(positions.front(), angle);
    };

    // Function: gravity force acting on I, at iteration S
    // Inputs: particle1, particle2, S
    VectorXd f_ij_s_p(const Particle &p1, const Particle &p2) {
        return f_i(p1.positions.back(), p2.positions.back(), p1.mass, p2.mass);
    };
};