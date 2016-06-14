#include <iostream>
#include <thread>
#include <ctime>
#include <mutex>
#define _WIN32
#include "InfInt.cpp"

void sum(InfInt n, InfInt n1, InfInt & s)
{
    for (InfInt i = n; i != n1; i++)
        s += i;
}

inline void factorial (InfInt n, InfInt n1, InfInt & s)
{
    for(InfInt i = n; i != n1; i++)
        s *= i;
}

inline void factorial2(InfInt n, InfInt & l)
{

    InfInt s = 1;
    for(InfInt i = 1; i != n + 1; i++)
        s *= i;
    l = s;
}

void donth () {}
InfInt cnk(InfInt n, InfInt k)
{
    InfInt n1, k1, nk, c = n - k;

    factorial2(n, n1);
    factorial2(k, k1);
    factorial2(c, nk);




    return n1 / (k1 * nk);
}

inline InfInt cnk1(InfInt n, InfInt k)
{
    InfInt n1, k1, nk, c = n - k;

    std::thread t1(factorial2, n, std::ref(n1));
    std::thread t2(factorial2, k, std::ref(k1));
    std::thread t3(factorial2, c, std::ref(nk));

    t1.join();
    t2.join();
    t3.join();


    return n1 / (k1 * nk);
}

static InfInt * qwet;

inline InfInt ** Multiply(InfInt ** a, int arow, int acol, InfInt ** b, int bcol, InfInt *& product1)
{
    InfInt ** product = new InfInt * [arow];
    for (int i = 0; i < arow; i++)
        product[i] = new InfInt[bcol];
    for (int i = 0; i < arow; i++)
    {
        for (int j = 0; j < bcol; j++)
            product[i][j] = 0;
    }

    for (int row = 0; row < arow; row++)
    {
        for (int col = 0; col < bcol; col++)
        {
            for (int inner = 0; inner < acol; inner++)
            {
                product[row][col] += a[row][inner] * b[inner][col];
            }
        }
    }
    for (int j = 0; j < bcol; j++)
        product1[j] = product[0][j];
    return product;
}

class THR
{
    std::thread t;
    InfInt ** a1, ** b, *& product;
    int arow,  acol, bcol;
public:
    THR() : a1(nullptr), b(nullptr), product(qwet) {}
    THR(InfInt ** _a1, int _arow, int _acol, InfInt ** _b, int _bcol, InfInt *& _product) : arow(_arow), acol(_acol), bcol(_bcol), product(_product)
    {
        a1 = new InfInt * [arow];
        for (int i = 0; i < arow; i++)
            a1[i] = new InfInt[acol];

        b = new InfInt * [acol];
        for (int i = 0; i < acol; i++)
            b[i] = new InfInt[bcol];
        
        for (int i = 0; i < arow; i++)
            for (int j = 0; j < acol; j++)
                a1[i][j] = _a1[i][j];

        for (int i = 0; i < acol; i++)
            for (int j = 0; j < bcol; j++)
                b[i][j] = _b[i][j];


    }

    THR & operator=(const THR & other)
    {
        arow = other.arow;
        acol = other.acol;
        bcol = other.bcol;
        if(!a1)
        {
            a1 = new InfInt * [arow];
            for (int i = 0; i < arow; i++)
                a1[i] = new InfInt[acol];
        }
        if(!b)
        {
            b = new InfInt * [acol];
            for (int i = 0; i < acol; i++)
                b[i] = new InfInt[bcol];
        }


        for (int i = 0; i < arow; i++)
            for (int j = 0; j < acol; j++)
                a1[i][j] = other.a1[i][j];

        for (int i = 0; i < acol; i++)
            for (int j = 0; j < bcol; j++)
                b[i][j] = other.b[i][j];
        product = other.product;
        return *this;
    }

    void launch()
    {
        t = std::thread(Multiply, a1, arow, acol, b, bcol, std::ref(product));
    }
    void join()
    {
        if (t.joinable())
            t.join();
    }

    ~THR ()
    {
        for (int i = 0; i < arow; i++)
            delete [] a1[i];
        delete [] a1;
        for (int i = 0; i < acol; i++)
            delete [] b[i];
        delete [] b;
        if (t.joinable())
            t.join();
    }
};

int main()
{
    InfInt n = 9999, k = 7, s1 = 0, s2 = 0, s3 = 0, s4 = 0, s = 0;
    unsigned int start_time = clock();
    sum(0, n, s); // начальное время
    unsigned int end_time = clock(); // конечное время
    unsigned int search_time = end_time - start_time; // искомое время
    std::cout << "1 thread time sum from 0 to n: " << search_time << std::endl;
    s = 0;

    start_time = clock();     // начальное время
    std::thread t1(sum, 0, n / 4, std::ref(s1));
    std::thread t2(sum, n / 4, n / 2, std::ref(s2));
    std::thread t3(sum, n / 2, n * 3 / 4, std::ref(s3));
    std::thread t4(sum, n * 3 / 4, n, std::ref(s4));
    t1.join();
    t2.join();
    t3.join();
    t4.join();
    s = s1 + s2 + s3 + s4;
    end_time = clock(); // конечное время
    search_time = end_time - start_time; // искомое время
    std::cout << "4 thread time sum from 0 to n: " << search_time << std::endl;
    s = s1 = s2 = s3 = s4 = 1;
    start_time = clock(); // начальное время
    factorial(1, n, s);
    end_time = clock(); // конечное время
    search_time = end_time - start_time; // искомое время
    std::cout << "1 thread time n!: " << search_time << std::endl;

    start_time = clock(); // начальное время
    std::thread t5(factorial, 1, n / 4, std::ref(s1));
    std::thread t6(factorial, n / 4 + 1, n / 2, std::ref(s2));
    std::thread t7(factorial, n / 2 + 1, n * 3 / 4, std::ref(s3));
    std::thread t8(factorial, n * 3 / 4 + 1, n, std::ref(s4));
    s = s1 * s2 * s3 * s4;
    t5.join();
    t6.join();
    t7.join();
    t8.join();
    end_time = clock(); // конечное время
    search_time = end_time - start_time; // искомое время
    std::cout << "4 thread time n!: " << search_time << std::endl;

    start_time = clock(); // начальное время
    cnk(n, k);
    end_time = clock(); // конечное время
    search_time = end_time - start_time; // искомое время
    std::cout << "1 thread time nCk: " << search_time << std::endl;

    start_time = clock(); // начальное время
    cnk1(n, k);
    end_time = clock(); // конечное время
    search_time = end_time - start_time; // искомое время
    std::cout << "3 thread time nCk: " << search_time << std::endl;

    int arow = rand() % 1000, acol = rand() % 1000, bcol = rand() % 1000;//3, acol = 4, bcol = 5;

    InfInt ** a = new InfInt * [arow];
    for (int i = 0; i < arow; i++)
        a[i] = new InfInt[acol];

    for (int i = 0; i < arow; i++)
        for (int j = 0; j < acol; j++)
            a[i][j] = rand();//i + j + 1;

    InfInt ** b = new InfInt * [acol];
    for (int i = 0; i < acol; i++)
        b[i] = new InfInt[bcol];

    for (int i = 0; i < acol; i++)
        for (int j = 0; j < bcol; j++)
            b[i][j] =  rand();//i - j + 2;
/*
    for (int i = 0; i < arow; i++)
    {
        for (int j = 0; j < acol; j++)
            std::cout << a[i][j] << " ";
        std::cout << std::endl;
    }
    std::cout << std::endl;

    for (int i = 0; i < acol; i++)
    {
        for (int j = 0; j < bcol; j++)
            std::cout << b[i][j] << " ";
        std::cout << std::endl;
    }

*/
    InfInt ** product,  ** product1, ** a1;
    product1 = new InfInt * [1];
    product1[0] = new InfInt [bcol];

    start_time = clock(); // начальное время
    product = Multiply(a, arow, acol, b, bcol, product1[0]);
    end_time = clock(); // конечное время
    search_time = end_time - start_time; // искомое время
    std::cout << "1 thread time Multiply: " << search_time << std::endl;



    for (int i = 0; i < arow; i++)
    {
        for (int j = 0; j < bcol; j++)
            product[i][j] = 0;
    }
    
    a1 = new InfInt * [1];
    a1[0] = new InfInt [acol];
    start_time = clock(); // начальное время
    THR * tr = new THR [arow];
    for (int f = 0; f < arow; f++)
    {
        for (int j = 0; j < acol; j++)
            a1[0][j] = a[f][j];
        tr[f] = THR(a1, 1, acol, b, bcol, product[f]);
        tr[f].launch();
    }
    for (int i = 0; i < arow; i++)
    {
        tr[i].join();
    }
    end_time = clock(); // конечное время
    search_time = end_time - start_time; // искомое время
    std::cout << "Multi thread time Multiply: " << search_time << std::endl;

    
    for (int i = 0; i < arow; i++)
        delete [] a[i];
    delete [] a;
    for (int i = 0; i < acol; i++)
        delete [] b[i];
    delete [] b;
    delete [] product1[0];
    delete [] product1;
    delete [] a1[0];
    delete [] a1;


    return 0;
}











