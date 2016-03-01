#include <cstring>
#include <iostream>
#define STUDENT_VARIANT 19


class IUVector{
    double * collection;
    int dim;
public:
    IUVector()
        :dim(0)
    {
        collection = new double [dim];
    }

    IUVector(double * data, int len)
        :dim(len)
    {
        collection = new double [dim];
        memcpy(collection, data, dim * sizeof(double));
    }

    IUVector(const IUVector& _IUVector)
        :dim(_IUVector.dim)
    {
        collection = new double [dim];
        memcpy(collection, _IUVector.collection, dim * sizeof(double));
    }

    IUVector & operator=(const IUVector& _IUVector)
    {
        if (this == &_IUVector)
            return *this;
        delete [] collection;
        dim = _IUVector.dim;
        collection = new double [dim];
        memcpy(collection, _IUVector.collection, dim * sizeof(double));
        return *this;
    }

    void insert(double el, int index){
        IUVector temp(*this);
        delete [] collection;
        collection = new double [++dim];
        collection[index] = el;
        memcpy(collection, temp.collection, index * sizeof(double));
        memcpy(collection + index + 1, temp.collection + index, (dim - index) * sizeof(double));
    }

    int size(){
        return dim;
    }

    bool empty(){
        if (dim == 0)
            return true;
        else
            return false;
    }

    double & operator[](int index){
        return collection[index];
    }

    friend std::ostream& operator<<(std::ostream&, const IUVector&);

    friend double operator*(double *, const IUVector&);

    friend double operator*(const IUVector&, double *);

    ~IUVector(){
        delete [] collection;
    }

};

std::ostream& operator<<(std::ostream& os, const IUVector& _IUVector){
    for(int i = 0; i < _IUVector.dim; i++)
        std::cout << _IUVector.collection[i] << " ";
    return os;
}

double operator*(double * vector, const IUVector& _IUVector){
    double composition = 0;
    for (int i = 0; i < _IUVector.dim; i++)
        composition += _IUVector.collection[i] * vector[i];
    return composition;
}

double operator*(const IUVector& _IUVector, double * vector){
    double composition = 0;
    for (int i = 0; i < _IUVector.dim; i++)
        composition += _IUVector.collection[i] * vector[i];
    return composition;
}
