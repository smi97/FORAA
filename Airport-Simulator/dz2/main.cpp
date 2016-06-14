
#include "stdafx.h"

using namespace std;

int main() {
    int a = 0, i = 0;
    int passengers_max_count = 111, average_speed = 111, fuel_consumption = 111, tank_volume = 111, age,  salary, experience, level;
    string buff;
    string model_name;
    string name;
    vector<Plane> plane;
    vector<AirportInsideWorker> InWorker;
    vector<AirportOutsideWorker> OutWorker;

    ifstream file("ADB.txt");
    while(file >> model_name)
    {
        file >> buff;
        model_name += " " + buff;
        while (a < 4)
        {
            file >> buff;
           switch (a)
            {
                case 0:
                    passengers_max_count = atoi(buff.c_str());
                    break;
                case 1:
                    average_speed = atoi(buff.c_str());
                    break;
                case 2:
                    fuel_consumption = atoi(buff.c_str());
                    break;
                case 3:
                    tank_volume = atoi(buff.c_str());
                    break;
            }
            a++;
        }
        a = 0;
        plane.push_back(*new Plane(model_name, passengers_max_count, average_speed, fuel_consumption, tank_volume));
        i++;
    }

  /* for(auto it = plane.begin(); it != plane.end(); it++)
   {
        it->info();
        cout << endl;
    }
*/

    ifstream file1("IWDB.txt");
    while(file >> name)
    {
        while (a < 3)
        {
            file >> buff;
            switch (a)
            {
                case 0:
                    age = atoi(buff.c_str());
                    break;
                case 1:
                    salary = atoi(buff.c_str());
                    break;
                case 2:
                    experience = atoi(buff.c_str());
                    break;
                case 3:
                    level = atoi(buff.c_str());
                    break;
            }
            a++;
        }
        a = 0;
        InWorker.push_back(*new AirportInsideWorker(age, salary, experience, level, name));
        i++;
    }

    cout << endl << endl << endl;
    for(auto it = InWorker.begin(); it != InWorker.end(); it++)
    {
        it->info();
        cout << endl;
    }

   // InWorker[0].info();

    ifstream file2("OWDB.txt");
    while(file >> name)
    {

        while (a < 3)
        {
            file >> buff;
            switch (a)
            {
                case 0:
                    age = atoi(buff.c_str());
                    break;
                case 1:
                    salary = atoi(buff.c_str());
                    break;
                case 2:
                    experience = atoi(buff.c_str());
                    break;
            }
            a++;
        }
        a = 0;
        OutWorker.push_back(*new AirportOutsideWorker(age, salary, experience, level, name));
        i++;
    }
    cout << endl << endl << endl;
    for(auto it = OutWorker.begin(); it != OutWorker.end(); it++)
    {
        it->info();
        cout << endl;
    }

    Flight flighttorus(&plane[0], "Russia, Moscow", 1000);
    OutWorker[0].PreparePlane(1230, &plane[0]);
    InWorker[0].MakeBoarding(109, 300, &plane[0]);
    flighttorus.MakeFlight();

    file.close();
    file1.close();
    file2.close();

    return 1;
}
