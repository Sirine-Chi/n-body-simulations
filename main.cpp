//
// Created by Ilya Belov on 7/9/23.
//

#include <iostream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <random>
#include "string"
#include "vector"
#include <cmath>
#include <ctime>
#include "build/Eigen/Dense"
#include "build/Eigen/Geometry"

#ifdef __APPLE__
#include <OpenCL/opencl.h>
#else
#include <CL/cl.h>
#endif

#define MAX_SOURCE_SIZE (0x100000)

using namespace std;
using Eigen::MatrixXd;
using Eigen::VectorXd;

#define G 0.0001184069 // In units Earth mass, AU, A Year

double radians(const double& degrees) { return degrees * (M_PI / 180); }

double degrees(const double& radians) { return radians / (M_PI / 180); }

float random_f(const float& mean) {
    random_device rd;
    normal_distribution<float> d {mean, mean/3};
    return d(rd);

}

template <typename T>
T vector_sum(const vector<T>& vec_to_sum)  {
    T sum;
    sum *= 0;
    for (auto & element : vec_to_sum) {
        sum += element;
    };
    return sum;
};

auto eiler = [] (auto &x, auto &y, const float &step) {
    return x+(step*y);
};


// Function, gravity force acting on I, ri, rj, mi, mj
VectorXd f_i(const VectorXd& ri, const VectorXd& rj, const float& mi, const float& mj) {
    return (rj-ri)*G*mi*mj*pow((rj-ri).norm(), -3.0/2);
}




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





class Simulator {
    // subclasses: different iteration method

    // def Initialise: set variables and vectors
    // def Iterator method: add new components to RS, VS, AS
    // def Render method: specify start time, in loop Sim.iteration(self), save delta
    // def get_time
    // def get_positions
    // def get_velocities
private:
    clock_t begin_time;
    vector<Particle> particles;
    float end_time;
    double step;
public:
    // Constructor custom
    Simulator(const vector<Particle>& particlesp, const float& end_timep, const double& stepp) {
        const clock_t begin_time = clock();
        particles = particlesp;
        end_time = end_timep;
        step = stepp;
    };

    // Засовываем в партиклес Симулятора все партиклы, их вообще нужно ещё вытащить из файла, и передать
    void set_objects(vector<Particle> prtls) {
        for (auto & element : prtls) {particles.push_back(element); }
    };

    void simulation() {
        for (float tau = 0; tau < end_time; tau += step) {
            for (auto & element : particles) {element.iteration(step, particles); }
        }
    };

    // --- Getters

    vector <vector <VectorXd> > get_positions() {
        vector <vector <VectorXd> > poses;
        for (auto & element : particles) {poses.push_back(element.get_positions()); }
        return poses;
    };

    float get_time() { return float( clock() - begin_time ) / CLOCKS_PER_SEC; };
};




int main() {
    const clock_t begin_time = clock();

    float end_time = 10;
    float step = 0.00005;

    int N = 2;
    vector <Particle> particle_system;

    // === Generating objects (just mean)
//    for (int i = 0; i < N; i++) {
//        Particle p( to_string(i), random_f(4.0), VectorXd {{random_f(2.0), 0.0}}, VectorXd {{0.0, random_f(20.0)}}, "w", random_f(M_PI/2) );
//        particle_system.push_back(p);
//        cout << i << "\n";
//    }

    Particle sun("Sun",332840.0,VectorXd {{0,0}}, VectorXd {{0,0}}, "y" ,0);
    Particle p2("Mercury", 0.0553,VectorXd {{0.4667045037,0}}, VectorXd {{0,8.19188772}}, "maroon", 192.12);
    particle_system.push_back(sun);
    particle_system.push_back(p2);

    // Rotate on start position
    for (auto & p : particle_system) { p.rotate_self(); }

    // Calculating zero forces
    for (auto & p : particle_system) {
        p.set_acceleration(p.f_I_p(particle_system));
    }

    //Iterating
    for (float t = 0; t < end_time; t += step) {
        for (auto & p : particle_system) {
            //p.print_log();
            // cout << "\n" << p.get_name() << ":\n" << p.get_last_position() << ", ";
            p.iteration(step, particle_system);
        };
    }

    //Printing final positions
    // VectorXd off = sun.get_last_position();
    cout << "\noff:\n" << sun.get_last_position() << "\n";
    for (auto & p : particle_system) {
        cout << "\n" << p.get_name() << "\n" << p.get_last_position()  << "\n"; // - particle_system.at(0).get_last_position()
    }

//    for (auto & p : particle_system) {
//        for (auto & i : p.get_positions()) {
//            cout << i;
//        };
//    };



    // print runtime
    cout << "\n --- Runtime: " << float( clock() - begin_time ) /  CLOCKS_PER_SEC << " sec" << endl;
    return 0;
}

int earth_example() {
    VectorXd r {{1.016725701, 0.0}};
    VectorXd v {{0.0, 6.1754482536}};
    Particle earth("Earth", 1.0, r, v, "aqua", 224.0); // Consrtucting object of class
    for (auto & element : earth.get_positions()) { cout << element << "-- el \n"; } // Printing positions
    return 0;
};

int in_out() {

    // read text
    char was[50];
    ifstream in("input.txt", ios_base::in);
    in.getline(was, 50);
    in.close();
    cout << was;

    // set values
    float a = 1.2;
    float b = 3.2;
    float m1 = 1.3;
    float m2 = 1.1;
    VectorXd vec1 {{a, b}};
    VectorXd vec2 {{2*b, a/3}};

    // print to output.txt
    ofstream out("output.txt", ios_base::out);
    out << "--- vec1\n" << vec1 << endl << "--- vec2\n" << vec2 << endl;
    out << "force\n" << f_i(vec1, vec2, m1, m2) << "\n";
    out.close();

    return 0;
}
