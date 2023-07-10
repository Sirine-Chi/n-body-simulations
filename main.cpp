//
// Created by Ilya Belov on 7/9/23.
//

#include <iostream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include "string"
#include "vector"
#include <cmath>
#include <ctime>
#include "build/Eigen/Dense"

#ifdef __APPLE__
#include <OpenCL/opencl.h>
#else
#include <CL/cl.h>
#endif

#define MAX_SOURCE_SIZE (0x100000)

using namespace std;
using Eigen::MatrixXd;
using Eigen::VectorXd;

const float G = 0.0001184069; // In units Earth mass, AU, A Year

// Function, gravity force acting on I, ri, rj, mi, mj
VectorXd f_i(VectorXd& ri, VectorXd& rj, float& mi, float& mj) {
    return (rj-ri)*G*mi*mj*pow((rj-ri).norm(), -3.0/2);
};

class Particle {
public:
    // Constructor with arguments
    // Name, sPosition, sVelocity, mass,
    Particle(string namep, float massp, VectorXd positionp, VectorXd velocityp, string colorp, float anglep) {
        name = namep;
        mass = massp;
        positions.insert(positions.begin(), positionp);
        velocities.insert(velocities.begin(), velocityp);
        color = colorp;
        angle = anglep;
    };

    void set_values(string& namep, float& massp, VectorXd& positionp, VectorXd& velocityp, string& colorp, float& anglep) {
        name = namep;
        mass = massp;
        positions.insert(positions.begin(), positionp);
        velocities.insert(velocities.begin(), velocityp);
        color = colorp;
        angle = anglep;
    };

    const vector<VectorXd> &get_positions() const {
        return positions;
    };
private:
    string name;
    float mass;
    vector<VectorXd> positions;
    vector<VectorXd> velocities;
    string color;
    float angle;

    // Function: gravity force acting on I, at iteration S
    // Inputs: particle1, particle2, S
    VectorXd f_i_s_p(Particle& p1, Particle& p2, int& s) {
        return f_i(p1.positions[s], p2.positions[s], p1.mass, p2.mass);
    };
};

//class Simulator {
//    // subclasses: different iteration method
//
//    // def Initialise: set variables and vectors
//    // def Iterator method: add new components to RS, VS, AS
//    // def Render method: specify start time, in loop Sim.iteration(self), save delta
//    // def get_time
//    // def get_positions
//    // def get_velocities
//public:
//    // Constant
//    float G = 0.0001184069;
//
//    void set_objects(vector<Particle>) {
//
//    };
//
//    vector<VectorXd> get_positions() {
//        return
//    };
//
//private:
//    vector<Particle> particles;
//};

int main() {
    const clock_t begin_time = clock();

    // read text
//    char was[50];
//    ifstream in("input.txt", ios_base::in);
//    in.getline(was, 50);
//    in.close();
//    cout << was;

    // set values
    float a = 1.2;
    float b = 3.2;
    float m1 = 1.3;
    float m2 = 1.1;
    VectorXd vec1 {{a, b}};
    VectorXd vec2 {{2*b, a/3}};

    cout << "--- vec1\n" << vec1 << "\n" << "--- vec2\n" << vec2 << "\n";
    cout << "force\n" << f_i(vec1, vec2, m1, m2) << "\n";

    VectorXd r {{1.016725701, 0.0}};
    VectorXd v {{0.0, 6.1754482536}};
    Particle earth("Earth", 1.0, r, v, "aqua", 224.0); // Consrtucting object of class
//    Particle earth;
//    earth.set_values("Earth", 1.0, r, v, "aqua", 224.0);
    vector <VectorXd> poses = earth.get_positions();

    for (auto & element : poses) { cout << element << "-- el \n"; }

    // print to output.txt
//    ofstream out("output.txt", ios_base::out);
//    out << "--- vec1\n" << vec1 << endl << "--- vec2\n" << vec2 << endl;
//    out << "force\n" << f_i(vec1, vec2, m1, m2) << "\n";
//    out.close();

    // print runtime
    cout << float( clock() - begin_time ) /  CLOCKS_PER_SEC << " sec" << endl;
    return 0;
}
