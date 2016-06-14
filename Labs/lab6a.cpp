#include <iostream>
#include <math.h>
#include <cstring>
#include <cstdio>
#include <functional>

float Div(float FirstArg, float SecondArg)
{
    if (SecondArg == 0)
    {
        throw std::invalid_argument("second arg is 0");
    }
    return FirstArg / SecondArg;
}


void CatchException(std::function<void()> func)
{
    try {
        func();
    }
    catch (std::out_of_range& ia) {
        std::cout << ia.what() << std::endl;
    }
    catch( ... )
    {
        std::cout << "all exceptions" << std::endl;
    }
}

void CatchThrowException(std::function<void()> func)
{
    try {
        func();
    }
    catch (std::out_of_range& ia) {
        std::cout << ia.what() << std::endl;
    }
    catch( ... )
    {
        throw std::logic_error("bad_function_call");
    }
}



class TTestRAII
{
    MyResource * res;
    public:
    TTestRAII(MyResource * ptr)
    {
    	res = ptr;
        res->lock();
    }
    ~TTestRAII()
    {
        res->unlock();
        delete res;
    }
};



