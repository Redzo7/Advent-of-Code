#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include <stack>

struct Command
{
    int count, from, to;

    Command(int c, int f, int t): count(c), from(f), to(t) {}
};

int main()
{
    // Reading file
    std::ifstream file("05_in.txt");
    
    std::string line; // buffer
    std::stack<std::string> crateLines;

    // Read crates
    while( std::getline(file, line) && !line.empty() )
    {
        crateLines.push(line);
    }
    crateLines.pop();

    // Read commands
    std::vector<Command> commands;
    while(std::getline(file, line))
    {
        int count, from, to;
        std::sscanf(line.c_str(), "move %d from %d to %d", &count, &from, &to);

        commands.push_back(Command(count, from, to));
    }

    // Create stacks
    std::vector<std::stack<char>> stacks((crateLines.top().length()+1) / 4);

    while(!crateLines.empty())
    {
        std::string curr = crateLines.top() + "X"; 
        for(unsigned int j = 0; j < curr.length(); j+=4)
        {
            char c = curr.substr(j, j+3)[1];
            if(c != ' ') stacks[j/4].push(c);
        }

        crateLines.pop();
    }

    // Move crates
    for(unsigned int i = 0; i < commands.size(); i++)
    {
        for(int c = 0; c < commands[i].count; c++)
        {
            char toMove = stacks[commands[i].from - 1].top();
            stacks[commands[i].from - 1].pop();

            stacks[commands[i].to - 1].push(toMove);
        }
    }
    
    std::string solution = "";
    for(unsigned int i = 0; i < stacks.size(); i++)
    {
        solution += stacks[i].top();
    }
    std::cout << solution << std::endl;

    return 0;
}