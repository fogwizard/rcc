#include "resource.h"
#include "unistd.h"

int usage(string s)
{
    cout << s << endl;
    cout << "[rcc]usage: rcc <dir>" << endl;
}

int main(int argc, char *argv[])
{
    if(2 != argc) {
        return usage("[rcc]params too short");
    } else if(-1 == (access(argv[1], 0 ))) {
        return usage("[rcc]dir not exit");
    }

    auto app = make_unique<resource>(argv[1]);
    return app->run();
}

