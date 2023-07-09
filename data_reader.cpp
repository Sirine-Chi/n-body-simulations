//
// Created by Ilya Belov on 7/9/23.
//

#include "yaml.h"

using namespace std;

int main() {
    YAML::Node config = YAML::LoadFile("config.yaml");

    const string mode = config["mode"].as<string>();
    cout << mode;

}