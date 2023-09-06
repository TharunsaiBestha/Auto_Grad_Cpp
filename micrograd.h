#include "Value.h"
//template<typename T>
//void update_grad_Node(T& Value){
//    T& lhs=*Value.children.first;
//    T& rhs=*Value.children.second;
//    switch(Value.op){
//        case '+':lhs.grad+=Value.grad;rhs.grad+=Value.grad;break;
//        case '-':lhs.grad+=Value.grad;rhs.grad-=Value.grad;break;
//        case '*':lhs.grad+=Value.grad*transpose(rhs.value);
//                 rhs.grad+=transpose(lhs.value)*Value.grad;
//                 break;
//        case 't':lhs.grad+=(1.0-pow(lhs.value,2.0))*Value.grad;break;
//        case 's':lhs.grad+=lhs.value*(1.0-lhs.value)*Value.grad;break;
//        case 'S':lhs.grad+=Softmax_backpropagation(Value.grad,Value.value);break;
//        case 'T':lhs.grad+=transpose(Value.grad);break;
//        case 'E':lhs.grad+=SE_backpropagation(lhs.value,rhs.value);break;
//        case ' ':break;
//}
template<typename T>
void update_Value_Node(T& Node){
     T& lhs=*Node.children.first;
     T& rhs=*Node.children.second;
     switch(Node.op){
        case '+': Node.value=lhs.value+rhs.value;break;
        case '-': Node.value=lhs.value-rhs.value;break;
        case '*': Node.value=lhs.value*rhs.value;break;
        case '/': Node.value=lhs.value/rhs.value;break;
        case 't': Node.value=tanh(lhs.value);break;
        case ' ':break;
     }
}
template<typename T>
 void update_grad_Node(T& Node){
     T& lhs=*Node.children.first;
     T& rhs=*Node.children.second;
     switch(Node.op){
         case '+':lhs.grad+=Node.grad;rhs.grad+=Node.grad;break;
         case '-':lhs.grad+=Node.grad;rhs.grad-=Node.grad;break;
         case '*':lhs.grad+=Node.grad*(rhs.value);
                  rhs.grad+=(lhs.value)*Node.grad;
                  break;
         case '/':lhs.grad+=Node.grad*(1/(rhs.value));
                  rhs.grad+=Node.grad*(-lhs.value/(rhs.value*rhs.value));
                  break;
         case 't':lhs.grad+=(1.0-pow(lhs.value,2))*Node.grad;break;
         case ' ':break;
     }
 }
template<typename T>
std::vector<T*> topological_sort(T* out){
    std::stack<T*> s;
    std::stack<T*> s_res;
    std::vector<T*> v;
    T* it;
    T* lhs;
    T* rhs;
    bool t;
    s.push(out);
    while(!s.empty()){
        it=s.top();
        t=(*it).visited;
        if(t){s_res.push(s.top());s.pop();}
        else{
            (*it).visited=true;
            lhs=(*it).children.first;
            rhs=(*it).children.second;
            if(lhs!=nullptr && !(*lhs).visited )s.push(lhs);
            if(rhs!=nullptr && !(*rhs).visited)s.push(rhs);
        }
    }
    while(!s_res.empty()){v.push_back(s_res.top());
    s_res.pop();}
    return v;
}
template<typename T>
void backpropagate(T* out){
    std::vector<T*> v=topological_sort(out);
    for(auto i:v){
        update_grad_Node(*i);
    }
}
template<typename T>
struct Network_Handler{
std::vector<T*> v;
T* out;
Network_Handler(T* Node):out{Node}{}
void order_nodes(){
    v=topological_sort(out);
}
void forward(){
 for(auto i=v.rbegin();i!=v.rend();i++)update_Value_Node(**i);   
}
void back_propagate(){
    for(auto i:v)update_grad_Node(*i);
}
};
