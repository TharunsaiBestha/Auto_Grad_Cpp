#include "micrograd.h"
#include <iostream>
template<> Graph_storage<Value<float>> Value<float>::GS{};
Value<float>& add(Value<float>& a,Value<float>& b){
    return a+b;
}
int main()
{
float x=2;
Value<float> a(x);x++;
Value<float> b(x);x++;
Value<float>& c=add(a,b);
c.grad=1.23;
Network_Handler<Value<float>> NH(&c);
NH.order_nodes();
for(int i=0;i<10;i++){
    a.value=i+0.0;
    b.value=i+10.0;
    NH.forward();
    NH.back_propagate();
   std::cout<<c.value<<std::endl;
}
}
