#include "micrograd.h"
#include <iostream>
template<> Graph_storage<Value<float>> Value<float>::GS{};
Value<float>& add(Value<float>& a,Value<float>& b){
    return a/b;
}
int main()
{
//    float x=1;
//    Value<float> a(x);x++;
//    Value<float> b(x);x++;
//    Value<float> c(x);x++;
//    Value<float> d(x);x++;
//     Value<float> g;
//     g=c*d/(a+b);
//    g.grad=1;
//    backpropagate(&g);
//    std::cout<<a.grad<<std::endl;
float x=1;
Value<float> a(x);x++;
Value<float> b(x);x++;
Value<float>& c=add(a,b);
c.grad=1.23;
backpropagate(&c);
std::cout<<b.grad<<std::endl;
}
