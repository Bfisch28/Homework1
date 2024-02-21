#include <iostream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

int main() {
    // Variables to store user input
    double emptyWeight, emptyWeightMoment;
    int numFrontSeatOccupants, numRearSeatOccupants;
    string frontSeatWeightsStr, rearSeatWeightsStr; // Comma-separated string for front seat occupant weights
    double baggageWeight;
    double frontSeatArm, rearSeatArm, fuelWeightsPerGallon, fuelTankArm, baggageMomentArm;
    int gallonsOfUsableFuel;

    // Prompt user for input and store in variables
    cout << "Enter airplane empty weight (pounds): ";
    cin >> emptyWeight;

    cout << "Enter airplane empty-weight moment (pounds-inches): ";
    cin >> emptyWeightMoment;

    cout << "Enter the number of front seat occupants: ";
    cin >> numFrontSeatOccupants;

    cout << "Enter weight of each front seat occupant (comma-separated list, e.g., 150,160,170): ";
    cin >> frontSeatWeightsStr;

    cout << "Enter front seat moment arm (inches): ";
    cin >> frontSeatArm;

    cout << "Enter the number of rear seat occupants: ";
    cin >> numRearSeatOccupants;

    cout << "Enter weight of each rear seat occupant (comma-separated list, e.g., 150,160,170): ";
    cin >> rearSeatWeightsStr;

    cout << "Enter rear seat moment arm (inches): ";
    cin >> rearSeatArm;

    cout << "Enter the number of gallons of usable fuel (gallons): ";
    cin >> gallonsOfUsableFuel;

    cout << "Enter usable fuel weights per gallon (pounds): ";
    cin >> fuelWeightsPerGallon;

    cout << "Enter fuel tank moment arm (inches): ";
    cin >> fuelTankArm;

    cout << "Enter baggage weight (pounds): ";
    cin >> baggageWeight;

    cout << "Enter baggage moment arm (inches): ";
    cin >> baggageMomentArm;

    // Parsing comma-separated string of front seat occupant weights
    stringstream ss(frontSeatWeightsStr);
    vector<double> frontSeatWeights;
    double weight;
    while (getline(ss, frontSeatWeightsStr, ',')) {
        stringstream(frontSeatWeightsStr) >> weight;
        frontSeatWeights.push_back(weight);
    }

    // Calculating total weight of front seat occupants
    double totalFrontSeatWeight = 0.0;
    for (double w : frontSeatWeights) {
        totalFrontSeatWeight += w;
    }

    // Parsing comma-separated string of rear seat occupant weights
    stringstream ss(rearSeatWeightsStr);
    vector<double> rearSeatWeights;
    double weight;
    while (getline(ss, rearSeatWeightsStr, ',')) {
        stringstream(rearSeatWeightsStr) >> weight;
        rearSeatWeights.push_back(weight);
    }

    // Calculating total weight of front seat occupants
    double totalrearSeatWeight = 0.0;
    for (double w : rearSeatWeights) {
        totalrearSeatWeight += w;
    }

    // Calculating gross weight and moment
    double totalWeight = emptyWeight + totalFrontSeatWeight +
        numRearSeatOccupants * totalrearSeatWeight +
        gallonsOfUsableFuel * fuelWeightsPerGallon +
        baggageWeight;

    double totalMoment = emptyWeightMoment +
        totalFrontSeatWeight * frontSeatArm +
        numRearSeatOccupants * totalrearSeatWeight * rearSeatArm +
        gallonsOfUsableFuel * fuelWeightsPerGallon * fuelTankArm +
        baggageWeight * baggageMomentArm;

    // Output the results
    cout << "\nTotal Gross Weight: " << totalWeight << " pounds" << endl;
    cout << "Total Moment: " << totalMoment << " pound-inches" << endl;

    // Calculate and output the center of gravity (CG) location
    double centerOfGravity = totalMoment / totalWeight;
    cout << "Center of Gravity (CG): " << centerOfGravity << " inches" << endl;

    // Check if the gross weight is within the maximum allowable gross weight limit
    if (totalWeight > 2950) {
        cout << "Warning: Gross weight exceeds maximum allowable gross weight!" << endl;
    }

    // Check if the center of gravity (C.G.) location is within the forward and aft C.G. limits
    if (centerOfGravity < 82.1 || centerOfGravity > 84.7) {
        cout << "Warning: Center of Gravity (C.G.) location is out of design limits!" << endl;
    }

    return 0;
}
