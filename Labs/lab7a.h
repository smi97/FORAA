#include <iostream>
#include <vector>


template<class T, class IT>
IT find(IT begin, IT end, T val)
{
    for(IT i = begin; i != end; i++)
    {
        if (val == *i)
            return i;
    }
    return end;
}

template<class IT, class PRED>
size_t count_if(IT begin, IT end, PRED pred)
{
    size_t n = 0;
    for(IT i = begin; i != end; i++)
    {
        if (pred(*i) == true)
            n++;
    }
    return n;
}

template<class T, class IT>
T minElem(IT begin, IT end)
{
    T min = *begin;
    for(IT i = begin; i != end; i++)
    {
        if (*i < min)
            min = *i;
    }
    return min;
}

template<class IT, class PRED>
void transform(IT begin, IT end, PRED pred)
{
    for(IT i = begin; i != end; i++)
    {
        *i = pred(*i);
    }
}

template<class T, class IT>
T mean(IT begin, IT end)
{
    T sred = 0;
    size_t n = 0;
    for(IT i = begin; i != end; i++)
    {
        sred += *i;
        ++n;
    }
    return sred / n;
}

template<class T, class IT, class PRED>
void replace_if(IT begin, IT end, PRED pred, T newValue)
{
    for(IT i = begin; i != end; i++)
    {
        if (pred(*i) == true)
            *i = newValue;
    }
}

bool foo(int a)
{
    if (a == 0) return true;
    return false;
}

bool foo1(int a)
{
    if ((a % 2) == 0)
        return true;
    return false;
}
/*
void TEST()
{
    std::vector<int> a;
    for (int i = 0; i < 5; i++)
        a.push_back(i);
    std::vector<int>::iterator it = ::find(a.begin(), a.end(), 3);
    size_t l = ::count_if(a.begin(), a.end(), foo);
    int min = ::minElem<int>(a.begin(), a.end());
    ::transform(a.begin(), a.end(), foo1);
    int sred = ::mean<int>(a.begin(), a.end());
    ::replace_if(a.begin(), a.end(), foo1, 2);

}


*/





