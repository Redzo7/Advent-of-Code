#include <iostream>
#include <string>
#include <fstream>
#include <vector>

int isBetween(int from, int to, int x)
{
    return from <= x && x <= to;
}

struct Pair
{
    int from, to;

    Pair(int a, int b): from(a), to(b) {}

    int getIntervalSize()
    {
        return to - from + 1;
    }

    bool containsInterval(Pair const& p)
    {
        return this->from <= p.from && p.to <= this->to;
    }

    bool IntervalContainsAny(Pair const& p)
    {
        return isBetween(this->from, this->to, p.from) || isBetween(this->from, this->to, p.to);
    }

    friend std::ostream& operator <<(std::ostream& _stream, Pair const& p)
    {
        _stream << p.from << " - " << p.to;

        return _stream;
    }
};

int main()
{
    std::fstream file("./04_in.txt");
    std::vector<Pair> pairs;

    std::string line;
    while(file >> line)
    {
        int ind = line.find(',');
        std::string first, second;
        first  = line.substr(0, ind);
        second = line.substr(ind + 1);
        pairs.push_back(
                Pair(
                    std::stoi(first.substr(0, first.find('-'))),
                    std::stoi(first.substr(first.find('-')+1))
                ));

        pairs.push_back(
        Pair(
            std::stoi(second.substr(0, second.find('-'))),
            std::stoi(second.substr(second.find('-')+1))
        ));
    }

    file.close();

    int count = 0;
    for(unsigned int i = 0; i < pairs.size(); i+=2)
    {
        count += pairs[i].IntervalContainsAny(pairs[i+1]) || pairs[i+1].IntervalContainsAny(pairs[i]);
    }

    std::cout << count << std::endl;
    return 0;
}