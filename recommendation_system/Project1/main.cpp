#include "DataLoader.h"
#include "ManhattanDistance.h"
#include "MergeSort.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <chrono>
#include <vector>

using namespace std;

double predictRatingUBCF(int userID, int movieID) {
    vector<pair<int, double>> similarities;

    for (const auto& [otherUserID, ratings] : userRatings) {
        if (otherUserID == userID || ratings.find(movieID) == ratings.end())
            continue;

        double similarity = calculateManhattanDistance(userRatings[userID], ratings);
        similarities.emplace_back(otherUserID, similarity);
    }

    mergeSort(similarities, 0, similarities.size() - 1);

    double weightedSum = 0.0, totalWeight = 0.0;
    for (const auto& [otherUserID, similarity] : similarities) {
        if (similarity <= 0.0)
            break;

        weightedSum += similarity * userRatings[otherUserID][movieID];
        totalWeight += similarity;
    }

    return (totalWeight > 0.0) ? (weightedSum / totalWeight) : 3.0; // Default prediction
}

double calculateRMSE(const vector<double>& actual, const vector<double>& predicted) {
    double sumSquaredError = 0.0;
    for (size_t i = 0; i < actual.size(); ++i) {
        double error = actual[i] - predicted[i];
        sumSquaredError += error * error;
    }
    return sqrt(sumSquaredError / actual.size());
}

int main() {
    auto startTime = chrono::high_resolution_clock::now();

    loadTrainingData("public_training_data.txt");

    ifstream testFile("public_test_data.txt");
    if (!testFile.is_open()) {
        cerr << "Error: Unable to open test file!" << endl;
        return -1;
    }

    vector<double> actualRatings, predictedRatings;
    string line;
    while (getline(testFile, line)) {
        istringstream ss(line);
        int userID, movieID;
        double actualRating;

        if (!(ss >> userID >> movieID >> actualRating)) {
            cerr << "Malformed test row skipped: " << line << endl;
            continue;
        }

        double predictedRating = predictRatingUBCF(userID, movieID);
        actualRatings.push_back(actualRating);
        predictedRatings.push_back(predictedRating);
    }
    testFile.close();

    double rmse = calculateRMSE(actualRatings, predictedRatings);
    cout << "Root Mean Squared Error (RMSE): " << rmse << endl;

    auto endTime = chrono::high_resolution_clock::now();
    chrono::duration<double> elapsed = endTime - startTime;
    cout << "Execution time: " << elapsed.count() << " seconds" << endl;

    return 0;
}
