//Brandon Fischer
//AERSP 424
// Code was made with the assistance of ChatGPT
#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <map>

using namespace std;
//Question 1
void q1() {
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
    stringstream ss2(rearSeatWeightsStr);
    vector<double> rearSeatWeights;
    double weightrear;
    while (getline(ss2, rearSeatWeightsStr, ',')) {
        stringstream(rearSeatWeightsStr) >> weightrear;
        rearSeatWeights.push_back(weightrear);
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
        double fueladjustment = (totalWeight - 2950) / fuelWeightsPerGallon;
        cout << "Fuel Drain needed: " << abs(fueladjustment) << " gallons" << endl;
        if (fueladjustment > gallonsOfUsableFuel) {
            cout << "Impossible to make weight with fuel drain" << endl;
            exit(1);
        }
        gallonsOfUsableFuel -= fueladjustment;
        totalWeight = 2950;
    }

    // Check if the center of gravity (C.G.) location is within the forward and aft C.G. limits, this might be wrong
    if (centerOfGravity < 82.1 || centerOfGravity > 84.7) {
        cout << "Warning: Center of Gravity (C.G.) location is out of design limits!" << endl;
        double adjustment = (centerOfGravity < 82.1) ? (82.1 - centerOfGravity) : (centerOfGravity - 84.7);
        double adjustmentFuel = adjustment * totalWeight / fuelTankArm;
        cout << "Fuel adjustment needed: " << adjustmentFuel << " gallons" << endl;
        gallonsOfUsableFuel += adjustmentFuel;
        totalWeight += adjustmentFuel * fuelWeightsPerGallon;
    }
    // Recalculate total moment
    totalMoment = emptyWeightMoment +
        totalFrontSeatWeight * frontSeatArm +
        numRearSeatOccupants * totalrearSeatWeight * rearSeatArm +
        gallonsOfUsableFuel * fuelWeightsPerGallon * fuelTankArm +
        baggageWeight * baggageMomentArm;

    // Output the adjusted results
    cout << "\nAdjusted Total Gross Weight: " << totalWeight << " pounds" << endl;
    cout << "Adjusted Total Moment: " << totalMoment << " pound-inches" << endl;

    // Calculate and output the adjusted center of gravity (CG) location
    centerOfGravity = totalMoment / totalWeight;
    cout << "Adjusted Center of Gravity (CG): " << centerOfGravity << " inches" << endl;
}

//Question 2
class FlightContainer {
public:
    map<pair<string, string>, int> distanceMap{
        {{"SCE", "PHL"}, 160},
        {{"SCE", "ORD"}, 640},
        {{"SCE", "EWR"}, 220}
    };

    int getDistance(const string& origin, const string& destination) const {
        // Check if the pair is in the map
        auto it = distanceMap.find({ origin, destination });
        if (it != distanceMap.end()) {
            return it->second; // Return distance if found
        }
        else {
            return 0; // Return 0 if pair not found
        }
    }
};


// Question 3
class Plane {
private:
    double pos;
    double vel;
    double distance;
    bool at_SCE;
    string origin;
    string destination;
    FlightContainer& flights;

public:
    Plane(const string& from, const string& to, FlightContainer& flightContainer)
        : pos(0), vel(0), at_SCE(true), origin(from), destination(to), flights(flightContainer) {
        // Initialize distance using FlightContainer
        distance = flights.getDistance(origin, destination); // Corrected initialization
        cout << "Plane Created at " << this << endl;
    }


    ~Plane() {
        cout << "Plane Destroyed" << endl;
    }

    double getPos() const { return pos; }
    string getOrigin() const { return origin; }
    string getDestination() const { return destination; }
    bool getAtSCE() const { return at_SCE; }
    double getVel() const { return vel; }
    void setVel(double v) { vel = v; }
    double getDistance() const { return distance; } // Public member function to retrieve distance

    // Add a member function to update the state of the plane
    void updateState(const string& newOrigin, const string& newDestination) {
        origin = newOrigin;
        destination = newDestination;
        distance = flights.getDistance(origin, destination);
        pos = 0.0;
        at_SCE = (destination == "SCE");
    }

    // Add the operate function to the Plane class
    void operate(double dt);
};



//Question 4
void Plane::operate(double dt) {
    cout << "Velocity: " << vel << ", Time Step: " << dt << ", Position: " << pos << ", Distance: " << distance << endl;

    if (pos + vel * dt < distance) {
        pos += vel * dt;
        at_SCE = false;
        return; // End
    }

    if (destination == "SCE") {
        at_SCE = true;
        swap(origin, destination);
        distance = flights.getDistance(origin, destination); // Update distance
        pos = 0.0;
    }
    else {
        // Update the state of the plane when it reaches its destination
        swap(origin, destination);
        distance = flights.getDistance(origin, destination); // Update distance
        pos = 0.0;
        at_SCE = (destination == "SCE"); // Check if destination is SCE
    }
}






//Question 6
// Pilot class
class Pilot {
private:
    string name;
    Plane* myPlane;

public:
    Pilot(const string& n, Plane* plane) : name(n), myPlane(plane) {
        cout << "Pilot " << name << " at the gate, ready to board the plane. Plane address: " << myPlane << endl;
    }

    ~Pilot() {
        cout << "Pilot " << name << " out of the plane." << endl;
    }

    string getName() const { return name; }
};

int q7() {
    FlightContainer flights;
    double speed = 450; // Speed in mph
    int timestep = 50; // Time step in seconds
    int max_iterations = 1500; // Maximum number of iterations

    // Instantiate Plane object
    Plane myPlane("SCE", "PHL", flights);
    myPlane.setVel(speed);

    // Instantiate pilots
    Pilot* pilot1 = new Pilot("Pilot-in-Command", &myPlane);
    Pilot* pilot2 = new Pilot("Co-Pilot", &myPlane);

    // Variable to track the current controlling pilot
    Pilot* currentPilot = pilot1;

    for (int i = 0; i < max_iterations; ++i) {
        cout << "Pilot: " << currentPilot->getName() << ", Plane Address: " << &myPlane << ", Pilot Address: " << currentPilot << endl;

        myPlane.operate(timestep);

        if (myPlane.getAtSCE()) {
            cout << "Plane is at SCE, Plane Address: " << &myPlane << endl;

            // Switching destination for demonstration
            string newDestination = (myPlane.getDestination() == "PHL") ? "ORD" : "PHL";
            myPlane.operate(timestep); // Move the plane a bit further
            myPlane.updateState("SCE", newDestination);
            cout << "New destination: " << newDestination << endl;

            // Switching pilots
            if (currentPilot == pilot1) {
                currentPilot = pilot2;
            }
            else {
                currentPilot = pilot1;
            }

            cout << "Switching to Pilot: " << currentPilot->getName() << ", Plane Address: " << &myPlane << ", Pilot Address: " << currentPilot << endl;
        }

        cout << "Plane position: " << myPlane.getPos() << " miles" << endl;
    }

    // Clean up memory
    delete pilot1;
    delete pilot2;

    return 0;
};

int q8() {
    FlightContainer flights;
    double speed = 450; // Speed in mph
    int timestep = 50; // Time step in seconds
    int max_iterations = 1500; // Maximum number of iterations

    Plane myPlane("SCE", "PHL", flights);
    myPlane.setVel(speed);

    Pilot pilot1("John", &myPlane);
    Pilot pilot2("Doe", &myPlane);

    Pilot* currentPilot = &pilot1;

    for (int i = 0; i < max_iterations; ++i) {
        cout << "Pilot " << currentPilot->getName() << " controlling the plane. Plane address: " << &myPlane << endl;

        myPlane.operate(timestep);

        if (myPlane.getAtSCE() && myPlane.getPos() == myPlane.getDistance()) {
            cout << "Plane is at SCE" << endl;

            // Switching destination for demonstration
            string newDestination = (myPlane.getDestination() == "PHL") ? "ORD" : "PHL";
            myPlane.operate(timestep); // Move the plane a bit further
            myPlane.updateState("SCE", newDestination);
            cout << "New destination: " << newDestination << endl;

            // Switching pilots
            if (currentPilot == &pilot1) {
                currentPilot = &pilot2;
            }
            else {
                currentPilot = &pilot1;
            }

            cout << "Switching to Pilot: " << currentPilot->getName() << endl;
        }

        cout << "Plane position: " << myPlane.getPos() << " miles" << endl;
    }

    return 0;
}



int main() {
    //q1();
    //Question 5
    FlightContainer flights;
    double speed = 450; // Speed in mph
    int timestep = 50; // Time step in seconds
    int max_iterations = 1500; // Maximum number of iterations

    Plane myPlane("SCE", "PHL", flights);
    myPlane.setVel(speed);

    double timestamp = 0.0; // Initialize timestamp

    for (int i = 0; i < max_iterations; ++i) {
        myPlane.operate(timestep);
        timestamp += timestep; // Increment timestamp

        cout << "Timestamp: " << timestamp << " seconds, Plane position: " << myPlane.getPos() << " miles" << endl;
    }

    //q7();
    q8();
    return 0;
}