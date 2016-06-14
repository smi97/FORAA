#include <iostream>
#include <cstring>


class TDict {
    static int count;
    int * data;
    char * keys;
public:
    TDict () :data(nullptr), keys(nullptr) { count++; }

    TDict (const char * keys_, int * data_)
    {
        keys = new char [strlen(keys_) + 1];
        data = new int [strlen(keys_)];
        strcpy(keys, keys_);
        memcpy(data, data_, strlen(keys_) * sizeof(int));
        count++;
    }

    TDict ( int * data_, const char * keys_)
    {
        keys = new char [strlen(keys_) + 1];
        data = new int [strlen(keys_)];
        strcpy(keys, keys_);
        memcpy(data, data_, strlen(keys_) * sizeof(int));
        count++;
    }

    TDict (const TDict & Dict)
    {
        keys = new char [strlen(Dict.keys) + 1];
        data = new int [strlen(Dict.keys)];
        strcpy(keys, Dict.keys);
        memcpy(data, Dict.data, strlen(Dict.keys) * sizeof(int));
        count++;
    }

    TDict & operator = (const TDict & Dict)
    {
        if (this == & Dict)
            return * this;
        if (keys) delete [] keys;
        if (data) delete [] data;
        keys = new char [strlen(Dict.keys) + 1];
        data = new int [strlen(Dict.keys)];
        strcpy(keys, Dict.keys);
        memcpy(data, Dict.data, strlen(Dict.keys) * sizeof(int));
        count++;
        return * this;
    }

    ~ TDict ()
    {
        delete [] keys;
        delete [] data;
        count--;
    }

    int operator [] (char ch) const
    {
        for(int i = 0; i < strlen(keys); i++)
            if (ch == keys[i]) return data[i];
        return -1;
    }

    int & operator [] (char ch) {
        for(int i = 0; i < strlen(keys); i++)
            if (ch == keys[i]) return data[i];
        return data[0];
    }

    TDict & operator += (const TDict & Dict) {
        if (this == & Dict)
        {
            memset(data, 0, strlen(keys)*sizeof(int));

            return * this;
        }
        bool flag = true;
        char tmp[2];
        int n = strlen(keys), k = strlen(Dict.keys), add = 0;
        for (int j = 0; j < k; j++, flag = true)
        {
            for (int i = 0; i < n; i++)
            {
                if (Dict.keys[j] == keys[i]) {
                    flag = false;
                    break;
                }
            }
            if (flag)
            {
                tmp[0] = Dict.keys[j];
                strcat(keys, tmp);
                add++;
            } 
        }
        delete [] data;
        data = new int [strlen(keys) + add];
        memset(data, 0, strlen(keys)*sizeof(int));
        return * this; 
    }

    bool operator == (const TDict & Dict) const
    {
        return !strcmp(keys, Dict.keys);
    }
    
    static int GetCountObjects(); 
    
    friend std::ostream & operator << (std::ostream &, const TDict &);
}; 

int TDict::count = 0; 

TDict operator + (const TDict & Dict1, const TDict & Dict2)
{
    TDict Dict3(Dict1); 
    Dict3 += Dict2; 
    return Dict3; 
} 

std::ostream & operator << (std::ostream & out, const TDict & Dict)
{ 
    for (int i = 0; i < strlen(Dict.keys); i++)
    { 
        out << Dict.keys[i] << ":" << Dict.data[i] << " ";
    } 
    return out; 
} 

int TDict::GetCountObjects()
{ 
    return count; 
}
