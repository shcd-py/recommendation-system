#include "ManhattanDistance.h"

using namespace std;

double calculateManhattanDistance(const unordered_map<int, double>& ratingsA, const unordered_map<int, double>& ratingsB) {
    double distance = 0.0;

    for (const auto& [movieID, ratingA] : ratingsA) {
        if (ratingsB.find(movieID) != ratingsB.end()) {
            double ratingB = ratingsB.at(movieID);
            distance += abs(ratingA - ratingB);
        }
    }

    return 1.0 / (1.0 + distance); // Normalize edilmiþ benzerlik skoru
}
