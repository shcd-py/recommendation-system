#include "DataLoader.h"
#include <fstream>
#include <sstream>
#include <iostream>

using namespace std;

// Global deðiþkenin tanýmý
unordered_map<int, unordered_map<int, double>> userRatings;

// Training verisini yükleyen fonksiyonun implementasyonu
void loadTrainingData(const string& filePath) {
    ifstream file(filePath);
    if (!file.is_open()) {
        cerr << "Error: Unable to open training file!" << endl;
        exit(-1);
    }

    string line;
    while (getline(file, line)) {
        istringstream ss(line);
        int userID, movieID;
        double rating;

        if (!(ss >> userID >> movieID >> rating)) {
            cerr << "Malformed line skipped: " << line << endl;
            continue;
        }

        userRatings[userID][movieID] = rating;
    }
    file.close();
}
