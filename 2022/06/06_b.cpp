#include <iostream>
#include <set>
#include <string>
#include <fstream>

int main()
{
    std::string line;
    std::ifstream ifs("06_in.txt");

    std::getline(ifs, line);

    unsigned int i = 0;
    for(i = 0; i < line.length() - 14; i++)
    {
        std::set<char> charSet;
        for(unsigned int j = i; j < i + 14; j++)
        {
            charSet.insert(line[j]);
        }

        if(charSet.size() == 14)
        {
            break;
        }
    }

    std::cout << i + 14 << std::endl;
    return 0;
}