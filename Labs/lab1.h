
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>

using namespace std;

class TMyFirstClass{
private:
    static int count;
    char * FIO;
    int ots[4];
public:

    TMyFirstClass(){
        FIO = new char [33];
        memset(FIO, 'a', 32);
        memset(ots, 0, sizeof(ots));
        cout << ".ctor" << endl;
        count++;
    }

    TMyFirstClass(char * fio, int * bal){
        FIO = new char [strlen(fio)];
        strcpy(FIO,fio);
        memcpy(ots, bal, 16);
        cout << ".ctor" << endl;
        count++;
    }
    double sredbal(){
        double srb = 0;
        for(int i = 0; i < 4; i++)
            srb += ots[i];
        srb /= 4;
        return srb;
    }
    void pechat(){
        cout << "FIO: " << FIO << endl;
        for(int i = 0; i < 4; i++)
            cout << ots[i] << endl;
    }
    void set(char * fio, int * bal){
        strcpy(FIO,fio);
        memcpy(ots, bal, 16);
    }
    static void kol()
    {
        cout << endl << count;
    }

    ~TMyFirstClass(){
        count--;
        cout << ".dtor" << endl;

    }

};

int TMyFirstClass::count = 0;
