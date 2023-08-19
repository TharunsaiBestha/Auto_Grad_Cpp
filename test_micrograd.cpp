#include "micrograd.h"
#include <iostream>
int main()
{
    float x=1;
    Value<float> a(x);x++;
    Value<float> b(x);x++;
    Value<float> c(x);x++;
    Value<float> d(x);x++;
     Value<float> g;
    // Value<float> e,f,g;
    // e=a+b;
    // f=c*d;
    // g=f+e;
     g=c*d/(a+b);
    g.grad=1;
    backpropagate(&g);
    std::cout<<a.grad<<std::endl;
}
