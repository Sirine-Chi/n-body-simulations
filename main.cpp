//
// Created by Ilya Belov on 7/9/23.
//

#include "particle.h"

int main() {
    const clock_t begin_time = clock();

    float end_time = 1e+1;
    float step = 5e-5;

    int N = 2;
    vector <Particle> particle_system;

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

    // Iterating
    for (float t = 0; t < end_time; t += step) {
        for (auto & p : particle_system) {
            //p.print_log();
            // cout << "\n" << p.get_name() << ":\n" << p.get_last_position() << ", ";
            p.iteration(step, particle_system);
        };
    }

    // Printing final positions
    VectorXd off = particle_system[0].get_last_position();
    cout << "\noff:\n" << particle_system[0].get_last_position() << "\n";
    for (auto & p : particle_system) {
        cout << "\n" << p.get_name() << "\n" << (p.get_last_position() - off)  << "\n"; // - particle_system.at(0).get_last_position()
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
