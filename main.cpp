//
// Created by Ilya Belov on 7/9/23.
//

#include <iostream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <cmath>
#include "../eigen/Eigen/Dense"

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

class Simulator {
public:
    // Constant
    float G = 0.0001184069;
};

// Return gravitational force acting on bodies with positions ri, rj, and masses mi, mj
VectorXd f_i(VectorXd ri, VectorXd rj, float mi, float mj) {
    return (rj-ri)*G*mi*mj*pow((ri-rj).norm(), -3.0/2);
};

struct Particle {
    string name;
    vector <VectorXd> rs; // Не уверен, может нужны вектора векторов или матрицы?
    vector <VectorXd> vs;
    float m;
    string color;
};

int main() {
    char was[50];
    ifstream in("input.txt", ios_base::in);
    in.getline(was, 50);
    in.close();

    cout << was;

    float a = 1.2;
    float b = 3.2;
    float m1 = 1.3;
    float m2 = 1.1;
    VectorXd vec1 {{a, b}};
    VectorXd vec2 {{2*b, a/3}};

    cout << "--- vec1\n" << vec1 << endl << "--- vec2\n" << vec2 << endl;
    cout << "force\n" << f_i(vec1, vec2, m1, m2);

    ofstream out("output.txt", ios_base::out);
    out << "--- vec1\n" << vec1 << endl << "--- vec2\n" << vec2 << endl;
    out << "force\n" << f_i(vec1, vec2, m1, m2);
    out.close();

    return 0;
}
