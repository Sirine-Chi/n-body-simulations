//
// Created by Ilya Belov on 7/23/23.
//

#ifndef N_BODY_SIMULATIONS_N_BODY_LIB_H
#define N_BODY_SIMULATIONS_N_BODY_LIB_H

#endif //N_BODY_SIMULATIONS_N_BODY_LIB_H


#include <iostream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <random>
#include "string"
#include "vector"
#include <cmath>
#include <ctime>
#include "lib/Eigen/Dense"
#include "lib/Eigen/Geometry"

#ifdef __APPLE__
#include <OpenCL/opencl.h>
#else
#include <CL/cl.h>
#endif

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