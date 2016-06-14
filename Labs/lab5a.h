#include <iostream>
#include <cstring>

enum TypeOfRoad {
    CounryRoad = 1,
    CityRoad,
    IceRoad,
    Water
};

class Car
{
protected:
    char * _govNumber;
    int _horsepower;
public:
    Car() :_horsepower(0), _govNumber(nullptr) { }

    Car(char * govNumber, int horsepower) :_horsepower(horsepower)
    {
        _govNumber = new char [strlen(govNumber) + 1];
        strcpy(_govNumber, govNumber);
    }

    virtual bool canMove(TypeOfRoad typeOfRoad) const
    {
        if ((typeOfRoad == CounryRoad) || (typeOfRoad == CityRoad))
            return true;
        return false;
    }

    ~Car(){
        delete [] _govNumber;
        std::cout << ".dcor Car" << std::endl;
    }
};

class Lorry : public Car
{
protected:
    int _capacity;
public:
    Lorry() : Car(), _capacity(0) { }

    Lorry(char * govNumber, int horsepower, int capacity) : Car(govNumber, horsepower), _capacity(capacity) { }

    bool canMove(TypeOfRoad typeOfRoad) const
    {
        if (typeOfRoad == CityRoad)
            return true;
        return false;
    }

    ~Lorry(){
        std::cout << ".dcor Lorry" << std::endl;
    }

};

class CrossCountry : public Car
{
public:
    CrossCountry() : Car() { }

    CrossCountry(char * govNumber, int horsepower) : Car(govNumber, horsepower) { }

    bool canMove(TypeOfRoad typeOfRoad) const { return true; }

    ~ CrossCountry(){
        std::cout << ".dcor CrossCountry" << std::endl;
    }
    
};