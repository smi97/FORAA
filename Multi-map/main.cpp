#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include "map.h"

using namespace std;



int main(int argc, char* argv[])
{
    smi::multimap <char, int> p, a;
    if(p.empty()) cout << "empty" << endl;
    p.insert('c', 8);
    p.insert('b', 3);
    p.insert('a', 3);

    p.insert('w', 1);
    if(!p.empty()) cout << "not empty" << endl;

    smi::multimap<char, int>::iterator it = p.begin(), it1;
    for(it = p.begin(); it != p.end(); it++)
    {
        cout << *it << endl;
    }
    p.erase('a');
    cout << endl;
    a.insert('a', 4);
    p.swap(a);
    a.print();
    p.print();
    if( a == p )
        cout << "yes" << endl;
    else cout << "no" << endl;
    a = p;
    if( a == p )
        cout << "yes" << endl;
    else cout << "no" << endl;
    p.clear();
    if(p.empty()) cout << "empty" << endl;
    return 0;
}
 
