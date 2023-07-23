//
// Created by Ilya Belov on 7/23/23.
//

#ifndef N_BODY_SIMULATIONS_SIMULATOR_H
#define N_BODY_SIMULATIONS_SIMULATOR_H

#endif //N_BODY_SIMULATIONS_SIMULATOR_H

#include "n_body_lib.h"
#include "particle.h"

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