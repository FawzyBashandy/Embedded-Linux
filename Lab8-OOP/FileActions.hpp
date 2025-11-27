#ifndef FILEACTIONS_HPP
#define FILEACTIONS_HPP
#include <fcntl.h>
#include <initializer_list>
#include <iostream>
#include <string>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <vector>

class FileActions {
private:
    int* fd;                  
    int*& fdRef_;             
    std::vector<std::pair<std::string,int>> actions_; 

public:

    FileActions(const std::string& path);

    FileActions(const FileActions& other);

    void registerActions(std::initializer_list<std::pair<std::string,int>> list);

    void executeActions();

    ~FileActions();
};

#endif // FILEACTIONS_HPP
