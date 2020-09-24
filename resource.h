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

class resInfo
{
public:
    resInfo(string name, string dat, int len):path(name),data(dat),length(len) {};
    string path;
    string data;
    int length;
};

class filePath
{
public:
    filePath(string s1, string s2):abs_path(s1),rel_path(s2) {}
    string abs_path;
    string rel_path;
};

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
    vector<filePath*>  mFileList;
    vector<resInfo *> mResList;
};

#endif
