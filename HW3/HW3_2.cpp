#include <iostream>
using namespace std;

struct InitIOS {
    public:
    InitIOS() {
        ios_base::Init();
        cout << "Init ios_base\n";
    }
};

struct HelloWorld: public InitIOS {
    public:
    HelloWorld() {
        cout << "Hello World!\n";
    }
};

HelloWorld hello_world;
/*
When we create HelloWorld class which is derived from InitIOS class,
the members of HelloWorld can only be initialized by the InitIOS’s constructor
as the definition of these members exists in InitIOS class only.
Therefore the constructor of InitIOS will be called first. 
*/

int main() {
    return 0;
}
