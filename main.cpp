#include <iostream>
#include <cstring>

int gcdex(int a, int b, int &x, int &y){
    if(a == 0){
        x = 0;
        y = 1;
        return b;
    }
    int x1, y1;
    int g = gcdex (b%a, a, x1, y1);
    x = y1 - (b / a) * x1;
    y = x1;
    return g;
}

int reverse(int a, int m){
    int x, y;
    if (gcdex(a, m, x, y) != 1) {
        std::cout << "не существует ";
        return -1;
    }
    else if (x > 0) {
        return x;
    }
    return y;
}

int main()
{
    int a, b;
    std::cin >> a >> b;
    int x, y;
    std::cout << "nod: " << gcdex(a, b, x, y) << std::endl << "x = " << x << std::endl << "y = " << y << std::endl << "Обратный к " << a << " по модулю " << b << ": " << reverse(a, b) << std::endl;
    return 0;
}
