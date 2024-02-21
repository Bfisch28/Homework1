#include <iostream>

using namespace std;

int main() {
    // Variables to store user input
    double emptyWeight, emptyWeightMoment;
    int numFrontSeatOccupants, numRearSeatOccupants;
    double frontSeatWeight, rearSeatWeight, baggageWeight;
    double frontSeatArm, rearSeatArm, fuelWeightsPerGallon, fuelTankArm, baggageMomentArm;
    int gallonsOfUsableFuel;

    // Prompt user for input and store in variables
    cout << "Enter airplane empty weight (pounds): ";
    cin >> emptyWeight;

    cout << "Enter airplane empty-weight moment (pounds-inches): ";
    cin >> emptyWeightMoment;

    cout << "Enter the number of front seat occupants: ";
    cin >> numFrontSeatOccupants;

    cout << "Enter weight of each front seat occupant (pounds): ";
    cin >> frontSeatWeight;

    cout << "Enter front seat moment arm (inches): ";
    cin >> frontSeatArm;

    cout << "Enter the number of rear seat occupants: ";
    cin >> numRearSeatOccupants;

    cout << "Enter weight of each rear seat occupant (pounds): ";
    cin >> rearSeatWeight;

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

    // Calculating gross weight and moment
    double totalWeight = emptyWeight + numFrontSeatOccupants * frontSeatWeight +
        numRearSeatOccupants * rearSeatWeight +
        gallonsOfUsableFuel * fuelWeightsPerGallon +
        baggageWeight;

    double totalMoment = emptyWeightMoment +
        numFrontSeatOccupants * frontSeatWeight * frontSeatArm +
        numRearSeatOccupants * rearSeatWeight * rearSeatArm +
        gallonsOfUsableFuel * fuelWeightsPerGallon * fuelTankArm +
        baggageWeight * baggageMomentArm;

    // Output the results
    cout << "\nTotal Gross Weight: " << totalWeight << " pounds" << endl;
    cout << "Total Moment: " << totalMoment << " pound-inches" << endl;

    // Calculate and output the center of gravity (CG) location
    double centerOfGravity = totalMoment / totalWeight;
    cout << "Center of Gravity (CG): " << centerOfGravity << " inches" << endl;

    return 0;
}
