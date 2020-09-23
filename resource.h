#ifndef RESOURCE_H
#define RESOURCE_H

#include <iostream>
#include <vector>
#include <memory>
#include <fstream>

using namespace std;

template<typename T, typename... Ts>
std::unique_ptr<T> make_unique(Ts&&... params)
{
    return std::unique_ptr<T>(new T(std::forward<Ts>(params)...));
}

class resource
{
public:
    resource(string dir);
    int run(void);
    int dumpHeader(string file);
    string toHEX(unsigned char c);
    int trave_dir(const char* path);
private:
    string mDir;
    vector<string> mFileList;
};

#endif
