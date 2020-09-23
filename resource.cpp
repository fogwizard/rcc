#include "resource.h"

resource::resource(string dir): mDir(dir)
{

}

int resource::dumpHeader(string name)
{
    std::ofstream fheader(name, std::ios::out | std::ios::trunc);

    fheader << "#ifndef RESOURCES_H\n"
            "#define RESOURCES_H\n\n"
            "const char* getResource(const char* resource, unsigned long long *size);\n\n"
            "#endif" << std::endl;
    fheader.close();
}

int resource::run(void)
{
    string res_hpp = string(mDir + "/res.h");
    string res_cpp = string(mDir + "/res.cpp");

    /* remove out file */
    remove(res_hpp.c_str());
    remove(res_cpp.c_str());

    trave_dir(mDir.c_str());
    if(mFileList.size() == 0) {
        return -1;
    }

    dumpHeader(res_hpp);

    std::ofstream fsource(res_cpp, std::ios::binary);
    fsource << "#include <iostream>" << endl;
    fsource << "#include <vector>"   << endl;
    fsource << "#include <memory>"   << endl;
    fsource << "#include \"res.h\"" << endl << endl;;

    int count = 0;
    for(auto i: mFileList) {
        count++;
        string var_name = string("res_" + to_string(count));
        fsource << "static unsigned char " << var_name << "= {" << endl;
        {
            ifstream inFile(i,ios::in|ios::binary);
            if(inFile.fail()) {
                continue;
            }
            char c;
            auto line_count = 0;
            while(inFile.get(c)) {
                fsource << toHEX(static_cast<unsigned char >(c)) << ",";
                if(++line_count%12 == 0) {
                    fsource << endl;
                }
            }
            inFile.close();
        }
        fsource << "};" << endl;
    }

    fsource.close();

    return 0;
}

#include <string.h>
#include <dirent.h>
#include <sys/stat.h>

#define MAX_PATH_LEN (512)

int resource::trave_dir(const char* path)
{
    DIR *d = nullptr;
    struct dirent *dp = nullptr;
    struct stat st;
    char p[MAX_PATH_LEN] = {0};

    if(stat(path, &st) < 0 || !S_ISDIR(st.st_mode)) {
        cout << "invalid path:" <<  path << endl;
        return -1;
    }

    if(!(d = opendir(path))) {
        cout <<"opendir[%s] error: " <<  path << endl;
        return -2;
    }

    while((dp = readdir(d)) != NULL) {
        if((!strncmp(dp->d_name, ".", 1)) || \
                (!strncmp(dp->d_name, "..", 2))) {
            continue;
        }
        snprintf(p, sizeof(p) - 1, "%s/%s", path, dp->d_name);
        stat(p, &st);
        if(!S_ISDIR(st.st_mode)) {
            string s(p);
            mFileList.push_back(s);
        } else {
            trave_dir(p);
        }
    }
    closedir(d);

    return 0;
}

string resource::toHEX(unsigned char c)
{
    char *hb = (char *) malloc(sizeof(char) * 3);
    sprintf(hb, "%X", c);
    std::string hex = "0x";
    hex += strlen(hb) == 1 ? "0" : "";
    hex += hb;
    free(hb);
    return hex;
}

