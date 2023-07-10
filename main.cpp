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
public:
    // Constructor with arguments
    // Name, sPosition, sVelocity, mass,
    Particle( string namep, float massp, VectorXd positionp, VectorXd velocityp, string colorp, float anglep) {
        name = namep;
        mass = massp;
        positions.insert(positions.begin(), positionp);
        velocities.insert(velocities.begin(), velocityp);
        color = colorp;
        angle = anglep;
        cout << "Particle initialized ---";
    };

    void set_acceleration(const VectorXd& accel) {
        accelerations.insert(accelerations.begin(), accel);
    };

    void set_values(const string& namep, const float& massp, const VectorXd& positionp, const VectorXd& velocityp, const string& colorp, const float& anglep) {
        name = namep;
        mass = massp;
        positions.insert(positions.begin(), positionp);
        velocities.insert(velocities.begin(), velocityp);
        color = colorp;
        angle = anglep;
    };

    void iteration(double& step, vector<Particle>& particles) {
        VectorXd force {{0, 0}};
        vector<VectorXd> forces;
        for (auto & element : particles) {
            // force from element added to old force. But multiplied to binary expression for equality.
            force = force + f_i(this->get_positions().back(), element.get_positions().back(), this->get_mass(), element.get_mass() )*(element.positions.front() != this->positions.front());
        }
        accelerations.insert(accelerations.begin(), force/mass);
    };

    const vector<VectorXd> &get_positions() const { return positions; };

    const float &get_mass() const { return mass; };

    VectorXd const rotate(const VectorXd& r, const float& angle_deg) {
        MatrixXd rot_mx {{cos(angle_deg), sin(angle_deg)}, {-sin(angle_deg), cos(angle_deg)}};
        return rot_mx*r;
    };

    // Function: gravity force acting on I, at iteration S
    // Inputs: particle1, particle2, S
    VectorXd f_i_s_p(const Particle& p1, const Particle& p2) {
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
    vector<Particle> particles;
    float end_time;
    double step;
public:
    // Засовываем в партиклес Симулятора все партиклы, их вообще нужно ещё вытащить из файла, и передать
    void set_objects(vector<Particle> prtls) {
        for (auto & element : prtls) {particles.insert(particles.begin(), element); }
    };

    vector <vector <VectorXd> > get_positions() {
        vector <vector <VectorXd> > poses;
        for (auto & element : particles) {poses.insert(poses.begin(), element.get_positions()); }
        return poses;
    };

    void simulation() {
        for (float tau = 0; tau < end_time; tau = tau+step) {
            for (auto & element : particles) {element.iteration(step, particles); }
        }
    };
};

int main() {
    const clock_t begin_time = clock();

    int N = 10;

    // === Generating objects (just mean)
    for (int i = 0; i < N; i++) {
        Particle p( to_string(i), random_f(4.0), VectorXd {{random_f(2.0), 0.0}}, VectorXd {{0.0, random_f(20.0)}}, "w", random_f(M_PI/2) );
        cout << i << "\n";
    }

    // print runtime
    cout << "\n --- Runtime: " << float( clock() - begin_time ) /  CLOCKS_PER_SEC << " sec" << endl;
    return 0;
}

int earth_example() {
    VectorXd r {{1.016725701, 0.0}};
    VectorXd v {{0.0, 6.1754482536}};
    Particle earth("Earth", 1.0, r, v, "aqua", 224.0); // Consrtucting object of class
    for (auto & element : earth.get_positions()) { cout << element << "-- el \n"; } // Printing positions
}

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
