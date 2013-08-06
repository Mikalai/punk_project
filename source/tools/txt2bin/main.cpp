#include <iostream>
#include "../../punk_engine.h"

using namespace std;

int main(int argc, char** argv)
{
    if (argc < 3)
    {
        cout << "txt2bin input output" << std::endl;
        return 0;
    }

    System::Object* o = Utility::ParsePunkFile(System::string(argv[1]));

    if (o == nullptr)
        return 0;

    std::ofstream stream(argv[2]);
    o->Save(stream);

    return 0;
}
