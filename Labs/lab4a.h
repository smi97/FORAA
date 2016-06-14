#pragma warning(disable:4996)

#include <iostream>
#include <cstring>

class Engine
{
public:
    Engine() :_ls(100.0)
    {
        ++_countObjecs;
        _internalId = _countObjecs;
        //std::cout << ".cor of Engine(ID=" << _internalId << ")" << std::endl;
        _modelName = new char[10000];
    }
    

    Engine(char * modelName) :_ls(100.0)
    {
        ++_countObjecs;
        _internalId = _countObjecs;
        //std::cout << ".cor of Engine(ID=" << _internalId << ")" << std::endl;
        int len = strlen(modelName);
        _modelName = new char[len + 1];
        strcpy(_modelName, modelName);
    }
    

    Engine(double ls, char * modelName) :_ls(ls)
    {
        ++_countObjecs;
        _internalId = _countObjecs;
        //std::cout << ".cor of Engine(ID=" << _internalId << ")" << std::endl;
        int len = strlen(modelName);
        _modelName = new char[len + 1];
        strcpy(_modelName, modelName);
    }

    Engine(const Engine& Eng) : _ls(Eng._ls)
    {
        _modelName = new char [strlen(Eng._modelName) + 1];
        strcpy(_modelName, Eng._modelName);
    }

    Engine& operator=(const Engine& Eng)
    {
        if (_modelName)
            delete[] _modelName;
        _modelName = new char [strlen(Eng._modelName) + 1];
        strcpy(_modelName, Eng._modelName);
        _ls = Eng._ls;
        return * this;
    }

    ~Engine()
    {
        --_countObjecs;
        if (_modelName)
            delete[] _modelName;

        //std::cout << ".dcor of Engine(ID=" << _internalId << ")" << std::endl;
    }

    void changeName(char * name)
    {
        if (_modelName)
            delete[] _modelName;
        _modelName = new char [strlen(name) + 1];
        strcpy(_modelName, name);
    }

    friend std::ostream & operator << (std::ostream &, const Engine &);

private:
    static int _countObjecs;
    int _internalId;
    char * _modelName;
    double _ls;
};



enum class Season
{
    Summer,
    Winter
};

class Wheel
{
public:
    Wheel() : _radius(19), _season(Season::Summer)
    {
        ++_countObjecs;
        _internalId = _countObjecs;
        //std::cout << ".cor of Wheel(ID=" << _internalId << ")" << std::endl;
    }

    Wheel(float radius, Season season) :
    _radius(radius), _season(season)
    {
        ++_countObjecs;
        _internalId = _countObjecs;
        //std::cout << ".cor of Wheel(ID=" << _internalId << ")" << std::endl;
    }

    ~Wheel()
    {
        --_countObjecs;
        //std::cout << ".dcor of Wheel(ID=" << _internalId << ")" << std::endl;
    }

    Wheel& operator=(const Wheel&) = default;
    Wheel(const Wheel&) = default;

    friend std::ostream & operator << (std::ostream &, const Wheel &);
private:
    static int _countObjecs;
    int _internalId;
    float _radius;
    Season _season;
};


class Car
{
public:
    Car() : _engine(Engine("simpleEngine1234"))
    {
        ++_countObjecs;
        _internalId = _countObjecs;
        //std::cout << ".cor of Car(ID=" << _internalId << ")" << std::endl;
        _wheels = new Wheel[4];
    }

    Car(char * nameOfEngine) : _engine(Engine(nameOfEngine))
    {
        ++_countObjecs;
        _internalId = _countObjecs;
        //std::cout << ".cor of Car(ID=" << _internalId << ")" << std::endl;
        _wheels = new Wheel[4];
    }

    Car(const Car &object)
    : _engine(object._engine)
    {
        ++_countObjecs;
        _internalId = _countObjecs;
        //std::cout << ".cor of Car(ID=" << _internalId << ")" << std::endl;
        _wheels = new Wheel[4];
    }
    
    ~Car()
    {
        --_countObjecs;
        //std::cout << ".dcor of Car(ID=" << _internalId << ")" << std::endl;
    }
    
    void changeEngineName(char * name)
    {
        _engine.changeName(name);
    }
    
    Car& operator=(const Car&) = default;

    friend std::ostream & operator << (std::ostream &out, const Car &c);
    
private:
    static int _countObjecs;
    int _internalId;
    Wheel * _wheels;
    Engine _engine;
};


int Car::_countObjecs = 0;
int Wheel::_countObjecs = 0;
int Engine::_countObjecs = 0;