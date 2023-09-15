
#include <iostream>
#include <string>
#include <vector>
using namespace std;

const char DefaultVehicleName[] = "Untyped vehicle";
const char DefaultCoachName[] = "Default Coach";
const char DefaultAutomobileName[] = "Default Automobile";
const char DefaultAeroplaneName[] = "Default Aeroplane";
const double DefaultVehicleSpeed = -1.;
const double DefaultCoachSpeed = 10.;
const double DefaultAutomobileSpeed = 100.;
const double DefaultAeroplaneSpeed = 500.;
const double DefaultTimeToBoot = 0.01;
const int Defaultfly = 10000;
const double DefaultTimeSinceLastRepair = 0;
const double BaseAeroplaneSpeed = 80.;
const double BaseAutomobileSpeed = 20.;
const double BaseCoachSpeed = 5.;
const double DefaultMAXDISTANCE = 1000.;

//5 задание
const double DefaultMoneyVehicle = 0;
const double DefaultMoneyAutomobile = 1000.;
const double DefaultMoneyCoach = 100.;
const double DefaultMoneyAeroplane = 5000.;

//базовый класс
class Vehicle
{
public:
    double TotalDistance;
    double TotalTime;
    string name;
    double speed;
    double basespeed;

    //5 задание
    double money;
    void SetMoney(double money) {
        this->money = money;
    }
    virtual double GetMoney() const = 0;

    void SetSpeed(double speed) {
        this->speed = speed;
    }
    double GetTotalDistance() {
        return this->TotalDistance;
    }
    void SetTotalDistance(double distance) {
        this->TotalDistance = this->TotalDistance + distance;
    }
    double GetTotalTime() {
        return this->TotalTime;
    }
    void SetTotalTime(double time) {
        this->TotalTime = this->TotalTime + time;
    }
    const string const GetName() const {
        return this->name;
    }

    virtual double GetSpeed() const = 0;


    double GetBaseSpeed() const {
        return basespeed;
    }

    bool operator< (Vehicle& rhs) const {
        if (GetSpeed() < rhs.GetSpeed()) {
            return true;
        }
        return false;
    }

    virtual bool MakeTrip(double distanceOfTrip) = 0;

    Vehicle() : basespeed(0), TotalDistance(0), TotalTime(0), speed(DefaultVehicleSpeed), name(DefaultVehicleName), money(DefaultMoneyVehicle) {
    }

    Vehicle(string vehiclename = DefaultVehicleName, double vehiclespeed = DefaultVehicleSpeed, double basespeed = 0, double vehiclemoney = DefaultMoneyVehicle) {
        this->money = vehiclemoney;
        this->name = vehiclename;
        this->speed = vehiclespeed;
        this->basespeed = basespeed;
        this->TotalDistance = 0;
        this->TotalTime = 0;
    }
    ~Vehicle() {
    }
};

//бортовой компьютер
class Computer {
public:
    Computer() : baseTimeToBoot(DefaultTimeToBoot) {}
    double GetTimeToBoot() {
        return baseTimeToBoot;
    }
protected:
    double baseTimeToBoot;
};

//самолет
class Airplane : public Vehicle, protected Computer {
public:
    double GetSpeed() const {
        return GetBaseSpeed();
    }

    //5 задание
    double GetMoney() const {
        return this->money;
    }

    int maxflytime;
    double timeSinceLastRepair;

    void SetMaxFlyTime(int newflytime) {
        this->maxflytime = newflytime;
    }

    void Repair() {
        timeSinceLastRepair = 0;
    }
    double GetTimeSinceLastRepair() const {
        return timeSinceLastRepair;
    }

    bool MakeTrip(double distanceOfTrip) {
        double timeOfTrip = distanceOfTrip / GetSpeed() + GetTimeToBoot();
        if (timeSinceLastRepair + timeOfTrip > maxflytime) {
            return false;
        }
        timeSinceLastRepair += timeOfTrip;
        SetTotalDistance(distanceOfTrip);
        TotalTime += timeOfTrip;
        return true;
    }

    void ComputerUpdate(double newTimeToBoot) {
        this->baseTimeToBoot = newTimeToBoot;
    }

    Airplane(string aeroplanename = DefaultAeroplaneName, double aeroplanespeed = DefaultAeroplaneSpeed, double aeroplanemoney = DefaultMoneyAeroplane) : Vehicle(aeroplanename, aeroplanespeed, aeroplanemoney, BaseAeroplaneSpeed) {
        timeSinceLastRepair = DefaultTimeSinceLastRepair;
        maxflytime = Defaultfly;
    }

};

//повозка
class Coach : public Vehicle {
public:
    double MAX_DISTANCE;
    Coach(string coachname = DefaultCoachName, double coachspeed = DefaultCoachSpeed, double coachmoney = DefaultMoneyCoach) : Vehicle(coachname, coachspeed, coachmoney, BaseCoachSpeed) {
        MAX_DISTANCE = DefaultMAXDISTANCE;
    }

    double GetSpeed() const {
        return this->speed;
    }

    //5 задание
    double GetMoney() const {
        return this->money;
    }

    bool MakeTrip(double distanceOfTrip) {
        if (distanceOfTrip > MAX_DISTANCE) return 0;
        double timeOfTrip = distanceOfTrip / GetSpeed();
        SetTotalDistance(distanceOfTrip);
        SetTotalTime(timeOfTrip);
        SetSpeed(GetBaseSpeed() * exp(-TotalTime / 500.));
        return 1;
    }
};

//машина
class Automobile : public Vehicle {
public:
    Automobile(string automobilename = DefaultAutomobileName, double automobilespeed = DefaultAutomobileSpeed, double automobilemoney = DefaultMoneyAutomobile) : Vehicle(automobilename, automobilespeed, automobilemoney, BaseAutomobileSpeed) {};

    double GetSpeed() const {
        return this->speed;
    }

    //5 задание
    double GetMoney() const {
        return this->money;
    }

    bool MakeTrip(double distanceOfTrip) {
        double timeOfTrip = distanceOfTrip / GetSpeed();
        SetTotalDistance(distanceOfTrip);
        SetTotalTime(timeOfTrip);
        SetSpeed(GetBaseSpeed() * exp(-TotalDistance / 500.));
        return 1;
    }
};

//случайные перемещения
void CommitRandomTrips(vector<Vehicle*>& vehicles) {
    for (int i = 0; i < vehicles.size(); ++i) {
        double randomDistance = double(rand() % 20001) / 10.;
        vehicles[i]->MakeTrip(randomDistance);
    }
}

//случайная стоимость (5 задание)
void CommitRandomMoney(vector<Vehicle*>& vehicles) {
    for (int i = 0; i < vehicles.size(); ++i) {
        double randomMoney = double(rand() % 20001) / 100.;
        vehicles[i]->SetMoney(randomMoney);
    }
}

//отображение ТС
void DisplayVehicles(const vector<Vehicle*>& vehicles) {
    for (int i = 0; i < vehicles.size(); ++i) {
        cout << i + 1 << " vehicle info:" << endl;
        cout << "Name: " << vehicles[i]->GetName() << " Speed: " << vehicles[i]->GetSpeed() << " Total distance: " << vehicles[i]->TotalDistance << " Total time: " << vehicles[i]->TotalTime << " Cost: " << vehicles[i]->GetMoney() << endl << endl;
    }
}

//Сортировка выбором
template <class SemenPi>
void MySwap(SemenPi& v1, SemenPi& v2) {
    SemenPi v3 = v1;
    v1 = v2;
    v2 = v3;
}
template <class SemenExp, class SemenLess>
int FindMinimumIndex(SemenExp& data_array, int beginIndex, int endIndex, SemenLess LessFunction) {
    int minimumIndex = beginIndex;
    for (int element_number = beginIndex + 1; element_number <= endIndex; ++element_number) {
        if (LessFunction(data_array[element_number], data_array[minimumIndex])) {
            minimumIndex = element_number;
        }
    }
    return minimumIndex;
}
template <class SemenExp, class SemenLess>
void SelectionSort(SemenExp& data_array, int beginIndex, int endIndex, SemenLess LessFunction) {
    for (int element_number = beginIndex; element_number < endIndex; ++element_number) {
        int minimumIndex = FindMinimumIndex(data_array, element_number, endIndex, LessFunction);
        MySwap(data_array[minimumIndex], data_array[element_number]);
    }
}
bool CompareDefault(Vehicle* lhs, Vehicle* rhs) {
    return (*lhs < *rhs);
}
bool CompareTime(Vehicle* lhs, Vehicle* rhs) {
    return lhs->GetTotalTime() < rhs->GetTotalTime();
}

int main()
{
    srand(time(NULL));

    vector<Coach> coaches;
    vector<Automobile> automobiles;
    vector<Airplane> aeroplanes;

    coaches.push_back(Coach("Coach 1", 9.));
    coaches.push_back(Coach("Coach 2", 11.));
    coaches.push_back(Coach("Coach 3", 10.));
    coaches.push_back(Coach("Coach 4", 9.5));
    coaches.push_back(Coach("Coach 5"));

    automobiles.push_back(Automobile("Automobile 1"));
    automobiles.push_back(Automobile("Automobile 2", 90.));
    automobiles.push_back(Automobile("Automobile 3", 120.));
    automobiles.push_back(Automobile("Automobile 4", 150.));

    aeroplanes.push_back(Airplane("Aeroplane 1", 1030.));
    aeroplanes.push_back(Airplane("Aeroplane 2", 560.));
    aeroplanes.push_back(Airplane("Aeroplane 3", 2200.));

    vector<Vehicle*> coachPointers;
    vector<Vehicle*> automobilePointers;
    vector<Vehicle*> aeroplanePointers;

    for (int i = 0; i < coaches.size(); ++i) {
        coachPointers.push_back(&coaches[i]);
    }
    for (int i = 0; i < automobiles.size(); ++i) {
        automobilePointers.push_back(&automobiles[i]);
    }
    for (int i = 0; i < aeroplanes.size(); ++i) {
        aeroplanePointers.push_back(&aeroplanes[i]);
    }

    vector<Vehicle*> vehiclePointers;
    vehiclePointers.insert(vehiclePointers.end(), coachPointers.begin(), coachPointers.end());
    vehiclePointers.insert(vehiclePointers.end(), automobilePointers.begin(), automobilePointers.end());
    vehiclePointers.insert(vehiclePointers.end(), aeroplanePointers.begin(), aeroplanePointers.end());

    CommitRandomMoney(vehiclePointers);
    CommitRandomTrips(vehiclePointers);
    DisplayVehicles(vehiclePointers);

    cout << endl << "Sorted aeroplane array: " << endl;
    SelectionSort(aeroplanePointers, 0, aeroplanePointers.size() - 1, CompareDefault);
    DisplayVehicles(aeroplanePointers);

    cout << endl << "Sorted automobile array: " << endl;
    SelectionSort(automobilePointers, 0, automobilePointers.size() - 1, CompareDefault);
    DisplayVehicles(automobilePointers);

    cout << endl << "Sorted coach array: " << endl;
    SelectionSort(coachPointers, 0, coachPointers.size() - 1, CompareDefault);
    DisplayVehicles(coachPointers);

    cout << endl << "Sorted vehicle array: " << endl;
    SelectionSort(vehiclePointers, 0, vehiclePointers.size() - 1, CompareDefault);
    DisplayVehicles(vehiclePointers);

    return 0;
}