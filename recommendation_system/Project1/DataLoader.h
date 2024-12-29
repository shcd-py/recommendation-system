#ifndef DATALOADER_H
#define DATALOADER_H

#include <unordered_map>
#include <string>

using namespace std;

// Global deðiþken
extern unordered_map<int, unordered_map<int, double>> userRatings;

// Fonksiyon prototipi
void loadTrainingData(const string& filePath);

#endif
