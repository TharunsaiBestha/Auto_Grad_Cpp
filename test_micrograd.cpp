#include "micrograd.h"
#include <iostream>
int main()
{
    int x=1;
    Value<int> a(x);x++;
    Value<int> b(x);x++;
    Value<int> c(x);x++;
    Value<int> d(x);x++;
     Value<int> g;
    // Value<int> e,f,g;
    // e=a+b;
    // f=c*d;
    // g=f+e;
     g=c*d/(a+b);
    g.grad=1;
    backpropagate(&g);
    std::cout<<a.grad;
}