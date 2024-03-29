#ifndef IO_FUNCTIONS_H
#define IO_FUNCTIONS_H

#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include "json.hpp"

using namespace std;
using json = nlohmann::json;

void write_data_to_json(vector<double> data, string key_name, string filename) {
    json jsonData;
    
    ifstream inFile;
    inFile.open(filename);
    inFile >> jsonData;
    inFile.close();
    
    ofstream outFile;
    outFile.open(filename);
    
    if(!outFile) {
        cerr << "Error: Unable to open file " << filename << endl;
        return;
    }

    jsonData[key_name] = data;

    outFile << jsonData.dump(4) << endl;

    outFile.close();
}

#endif