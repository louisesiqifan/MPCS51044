#include <iostream>
#include <functional>
#include <iterator>
#include <string.h>
using namespace std;

class A {
    public:
        A(): name("default"), id{0} {}
        A(string s, int k): name(s), id(k) {}
        string name;
        int id;
        int set_id(int * new_id) {
            id = *new_id;
            return 0;
        }
        int call_id(double (*f)(float &)) {
            float float_id = (float) id;
            return (int) f(float_id);
        }
        friend ostream& operator<<(ostream& os, const A& a) {
            os << "Class A object, id " << a.id << " name " << a.name << ".";
            return os;
        }
};


typedef int (A::*SetIDPtr)(int *);
typedef int (A::**SetIDPtrPtr)(int *);
typedef int (A::*&SetIDPtrRef)(int *);
typedef int (A::*IDCallable)(double (float &));

int fnc_int() {
    return 1;
}

char * fnc_conc(char * left, char * right) {
    strcat(left, right);
    return left;
}

double float_to_double(float & k) {
    return (double) k*0.5;
}

void void_fcn(void (*f)()) {
    return f();
}


int main() {
    int n = 1;
    float m = 1.1;
    const char c = 'c';

    // int *
    int * int_ptr = &n;
    cout << "| int * | " << int_ptr << endl;

    // int &
    int & int_ref = n;
    cout << "| int & | " << int_ref << endl;

    // double
    double d = 1.1;
    cout << "| double | " << d << endl;

    // A* (A is any appropriate class)
    A a = A();
    A * a_ptr = &a;
    cout << "| A * | " << a << endl;

    // char const *
    const char * c_ptr = new char[5];
    c_ptr = "a string";
    cout << "| char const * | " << c_ptr << endl;

    // char const &
    const char & c_ref = c;
    cout << "| char const & | "<< c_ref << endl;

    // long[7]
    long l[7] = {1, 2, 3, 4, 5, 6, 7};
    cout << "| long[7] | ";
    copy(l, l + sizeof(l) / sizeof(l[0]), ostream_iterator<long>(cout, ", "));
    cout << endl;

    // int**
    int ** int_ptr_ptr = &int_ptr;
    cout << "| int ** | " << int_ptr_ptr << endl;

    // int *&
    int *& int_ptr_ref = int_ptr;
    cout << "| int *& | " << int_ptr_ref << endl;

    // float &
    float & f_ref = m;
    cout << "| float & | " << f_ref << endl;

    // int (*) ()
    int (*f_ptr)();
    f_ptr = fnc_int;
    cout << "| int (*) () | " << f_ptr() << endl;

    // int(*&)()
    int (*&f_ptr_ref)() = f_ptr;
    cout << "| int (*&) () | " << f_ptr_ref() << endl;

    // char *(*)(char *, char *)
    char * (*conc)(char *, char *);
    conc = fnc_conc;
    char s1[] = "Hello ";
    char s2[] = "World!";
    cout << "| char *(*)(char *, char *) | "<< conc(s1, s2) << endl;

    // int A::*
    int A::* id_ptr = &A::id;
    a.*id_ptr = 1;
    cout << "| int A::* | " << a << endl;

    // int (A::*)(int *)
    SetIDPtr set_id_ptr = & A::set_id;
    int new_id2 = 2;
    int r2 = invoke(set_id_ptr, a, &new_id2);
    cout << "| int (A::*)(int *) | " << a << endl;

    // int (A::**)(int *)
    SetIDPtrPtr set_id_ptr_ptr = & set_id_ptr;
    int new_id3 = 3;
    int r3 = invoke(*set_id_ptr_ptr, a, &new_id3);
    cout << "| int (A::**)(int *) | " << a << endl;

    // int (A::*&)(int *)
    SetIDPtrRef set_id_ptr_ref = set_id_ptr;
    int new_id4 = 4;
    int r4 = invoke(set_id_ptr_ref, a, &new_id4);
    cout << "| int (A::*&)(int *) | " << a << endl;

    // int (A::*)(double (*)(float &))
    IDCallable id_callable = &A::call_id;
    cout << "| int (A::*)(double (*)(float &)) | "
         << invoke(id_callable, a, float_to_double) << endl;

    // void (*p[10]) (void (*)() )
    cout << "| void (*p[10]) (void (*)() ) | ";
    void (*p[10]) (void (*)());
    for (int i=0; i<10; i++) {
        p[i] = &void_fcn;
        cout << i << " ";
    }
    cout << endl;

    return 0;
}
