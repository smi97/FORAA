#include <iostream>

class Circle
{
protected:
    double radius;
    Circle(int rad) : radius(rad){}
public:
    Circle() : radius(10) {}

    double sqv() const
    {
        return 3.14 * radius * radius;
    }

    void show() const
    {
        std::cout << "Radius: " << radius << std::endl << "Square: " << 3.14 * radius * radius << std::endl;
    }

    ~Circle ()
    {
    }
};

class Globe : protected Circle
{
public:
    Globe(double rad) : Circle(rad) {}

    double sqv() const
    {
        return 3.14 * radius * radius * radius * 3 / 4;
    }

    ~Globe()
    {
    }
};

template<class T>
double square(const T a)
{
    return a.sqv();
}

int main()
{
    Circle a;
    Globe b(30);
    std::cout << square(a) << std::endl;
    std::cout << square(b) << std::endl;

    return 0;
}









