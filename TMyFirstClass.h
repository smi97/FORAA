#include <cstring>
#include <iostream>
#define STUDENT_VARIANT 19

using namespace std;

class IUVector{
    double * collection;
    int dim;
public:
    IUVector(){
        dim = 0;
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
        else {
        delete [] collection;
        dim = _IUVector.dim;
        collection = new double [dim];
        memcpy(collection, _IUVector.collection, dim * sizeof(double));
        }
        return *this;
    }

    void push(double el, int index){
        double * temp = new double [dim];
        memcpy(temp, collection, dim * sizeof(double));
        delete [] collection;
        if (index == dim){
            collection = new double [++dim];
            memcpy(collection, temp, index * sizeof(double));
            collection[index] = el;
        }
        else {
            collection = new double [++dim];
            if (index == 0){
                collection[0] = el;
                for(int i = 1; i < dim; i++)
                    collection[i] = temp[i-1];
            }
            else {
                memcpy(collection, temp, index * sizeof(double));
                collection[index] = el;
                for(int i = index + 1; i < dim; i++)
                    collection[i] = temp[i-1];
            }
        }
        delete [] temp;
    }

    int size(){
        return dim;
    }

    double & operator[](int index){
        return collection[index];
    }

    friend ostream& operator<<(ostream&, const IUVector&);

    friend double operator*(double *, const IUVector&);

    friend double operator*(const IUVector&, double *);

    ~IUVector(){
        delete [] collection;
    }

};

ostream& operator<<(ostream& os, const IUVector& _IUVector){
    for(int i = 0; i < _IUVector.dim; i++)
        cout << _IUVector.collection[i] << " ";
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
