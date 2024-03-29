#ifndef IO_FUNCTIONS_H
#define IO_FUNCTIONS_H

#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

void write_to_tsv(vector<double> data, string filename) {
    ofstream outfile(filename);
    
    if(!outfile) {
        cerr << "Error: Unable to open file " << filename << endl;
        return;
    }

    for (size_t i = 0; i < data.size(); i++)
    {
        if (i > 0) {
            outfile << "\t";
        }
        outfile << data[i];

        outfile << "\t";
    }

    outfile.close();
}

#endif