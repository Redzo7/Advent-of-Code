#include <iostream>
#include <vector>
#include <fstream>
#include <string>

class FileSystemEntity
{
public:
    FileSystemEntity* parentDir;
    std::string name;

    FileSystemEntity() {}
    virtual ~FileSystemEntity() {}

    virtual int Size() = 0;
};

class Directory : public FileSystemEntity
{
public:

    std::vector<FileSystemEntity*> elems;

    Directory(Directory* p, std::string n) 
    {
        parentDir = p;
        name = n;
    }

    int Size()
    {
        int sum = 0;
        for(unsigned int i = 0; i < elems.size(); i++)
        {
            sum += elems[i]->Size();
        }

        return sum;
    }

    ~Directory()
    {
        for(unsigned int i = 0; i < elems.size(); i++)
        {
            delete elems[i];
        }
    }
};

class File : public FileSystemEntity
{
private:
    int size;
public:
    File(int s, Directory* p, std::string n): size(s) 
    {
        parentDir = p;
        name = n;
    }

    int Size()
    {
        return this->size;
    }

    ~File() {}
};

int main()
{
    Directory* fileSystem = new Directory(nullptr, "/");

    std::ifstream file("07_in.txt");

    std::string line;
    std::getline(file, line);


    Directory* currDir = fileSystem;

    std::vector<Directory*> dirList;
    dirList.push_back(fileSystem);

    while( std::getline(file, line) )
    {
        
        if(line == "$ ls")
        {
            
            std::vector<std::string> fileLines;
            std::string currFile;

            while( std::getline(file, currFile) && currFile[0] != '$')
            {
                fileLines.push_back(currFile);
            }
            
            std::vector<FileSystemEntity*> files;

            for(std::string curr : fileLines)
            {
                int spaceInd = curr.find(' ');
                std::string name = curr.substr(spaceInd + 1);
                if(curr.substr(0, spaceInd) == "dir")
                {
                    files.push_back( new Directory(currDir, name) );

                    dirList.push_back((Directory*)files[files.size() - 1]);
                }
                else
                {
                    int size = std::stoi(curr.substr(0, spaceInd));
                    
                    files.push_back( new File(size, currDir, name) );
                }   
            }
            currDir->elems = files;

            line = currFile;
        }

        if(line.substr(0, 4) == "$ cd")
        {
            std::string dirName = line.substr(5);
            if(dirName == "..")
            {
                currDir = (Directory*)currDir->parentDir;
            }
            else
            {
                unsigned int ind = 0;
                while(ind < currDir->elems.size() && currDir->elems[ind]->name != dirName)
                {
                    ind++;
                }

                currDir = (Directory*)currDir->elems[ind];
            }
        }
    }

    file.close();

    int maxStorage = 70000000;
    int storageNeeded = 30000000;

    int currStorage = maxStorage - fileSystem->Size();

    Directory* min = fileSystem;
    for(Directory* d : dirList )
    {
        if(currStorage + d->Size() >= storageNeeded && d->Size() < min->Size())
        {
            min = d;
        }
    }
    std::cout << min->Size();
    delete fileSystem;

    return 0;
}