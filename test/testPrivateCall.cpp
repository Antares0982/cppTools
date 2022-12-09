#include "PrivateCaller.h"
#include "test.h"
#include <iostream>

using namespace std;

class A {
    virtual void g() {}

    virtual void h(int a) { cout << a << endl; }

    virtual void f(int a, int b) const { cout << "succeed!" << '\t' << a << '\t' << b << endl; }
};

class B : public A, public TVirtualPrivateCaller<B> {
public:
    virtual void f(int, int) const override { cout << "fail!" << endl; }
};

struct Af {
    using Type = void (A::*)(int, int) const;
    // typedef void (A::*Type)(int, int) const;
};

template
class CallTNonVirtualPrivateSetter<Af, &A::f>;

ADD_TEST(PrivateCaller,
         {
             const A a;
             B::Call(&B::f, a, 1, 3);
             TNonVirtualPrivateCaller<Af>::Call(a, 2, 4);
         }
)
