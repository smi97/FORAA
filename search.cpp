#include <iostream>
#include <fstream>
#include <vector>

void search(std::ifstream &file){
    std::string word, wordc, collection;
    std::vector<bool> flag;
    std::vector <int> count;
    int i = 0, j = 0, pos = 0;
    bool first = true;

    while (file >> word) {
        pos += word.length() + 1;
        if(first){
            flag.push_back(true);
            flag.push_back(true);
            count.push_back(1);
        }

        if (flag[i]) {
            j = i;
            while(file >> wordc) {
                ++j;
                if(first) {
                    flag.push_back(true);
                    count.push_back(1);
                }
                if(wordc == word) {
                    flag[j] = false;
                    count[i] += 1;
                }
            }
            collection += word + " " + std::to_string(count[i]) + "\n";
            file.clear();
            file.seekg(pos, file.beg);
        }
        ++i;
        if (first)
            first = false;
    }

    std::cout << collection << std::endl;
}

int main()
{
    std::ifstream file;
    file.open("input.txt");
    if (!file.is_open()){
        std::cout << "Ошибка открытия файла!\n";
        return 1;
    }
    search(file);
    file.close();
    return 0;
}
