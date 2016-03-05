#include <iostream>

bool ifpalindrom(std::string a){
    auto it1 = a.begin(), it2 = a.end() - 1;
    int len = a.length() / 2;
    for (int ind = 0; ind < len; ind ++){
        if ((*it1) != (*it2))
            return false;
        it1++;
        it2--;
    }
    return true;
}

int main()
{
    std::string str;
    while(getline(std::cin, str))
        if(ifpalindrom(str))
            std::cout << "Palindrom" << std::endl;
        else std::cout << "Not palindrom" << std::endl;
    return 0;
}
