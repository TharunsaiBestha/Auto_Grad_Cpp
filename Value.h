//Author Bestha Gaddam Tharun Sai
#include "Graph_Algo.h"
#include<cmath>
#include "NN_fun.h"
#include "Graph_storage.h"
// template<typename Node_type,typename Edge_type>
// using graph_itr=typename std::list<Node<Node_type,Edge_type>>::iterator;
template<typename Node_type>
struct Value{
    Node_type value;
    bool visited;
    std::pair<Value*,Value*> children;
    char op;
    Node_type grad;
    std::string label;
    static Graph_storage<Value<Node_type>> GS;
    Value(Node_type v=Node_type{},std::pair<Value*,Value*> child={nullptr,nullptr},char ch=' ',std::string l=" "):value{v},
    visited{false},children{child},op{ch},grad{},label{l}{}
    Value(const Value& N){
        value=N.value;
        visited=N.visited;
        children=N.children;
        op=N.op;
        grad=N.grad;
        label=N.label;
    }
    Value(Value&& N){
        value=std::move(N.value);
        visited=N.visited;
        children=std::move(N.children);
        op=N.op;
        grad=std::move(N.grad);
        label=std::move(N.label);
    }
    Value& operator=(const Value& N){
        Value temp=N;
        temp.swap(*this);
        return *this;

    }
    Value& operator=(Value&& N){
        value=std::move(N.value);
        visited=N.visited;
        children=std::move(N.children);
        op=N.op;
        grad=std::move(N.grad);
        label=std::move(N.label);
        return *this;
    }
    typename std::list<Value<Node_type>>::iterator update(){
        return GS.add_node(*this);
    }
    void swap(Value& N){
        std::swap(value,N.value);
        std::swap(visited,N.visited);
        std::swap(children,N.children);
        std::swap(op,N.op);
        std::swap(grad,N.grad);
        std::swap(label,N.label);
    }
    Value& tanh(){
        std::pair<Value<Node_type>*,Value<Node_type>*> child(this,nullptr);
        Value<Node_type> out(tanh(value),child,'t');
        return *out.update();
    }
    Value& sigmoid(){
        std::pair<Value<Node_type>*,Value<Node_type>*> child(this,nullptr);
        Value<Node_type> out(sigmoid(value),child,'s');
        return *out.update();
    }
    Value& softmax(){
        std::pair<Value<Node_type>*,Value<Node_type>*> child(this,nullptr);
        Value<Node_type> out(Softmax(value),child,'S');
        return *out.update();
    }
    Value& T(){
        std::pair<Value<Node_type>*,Value<Node_type>*> child(this,nullptr);
        Value<Node_type> out(transpose(value),child,'T');
        return *out.update();
    }
    Value& Normalization(bool flag=false){
        std::pair<Value<Node_type>*,Value<Node_type>*> child(this,nullptr);
        Value<Node_type> out(normalization(value),child,'N');
        return *out.update();
    }
    Value& Square_Error(Value<Node_type>& N){
        std::pair<Value<Node_type>*,Value<Node_type>*> child(this,&N);
        Value<Node_type> out(SE(value,N.value),child,'E');
        return *out.update();
    }
};
template<typename Node_type>
Value<Node_type>& operator+(Value<Node_type>& lhs,Value<Node_type>& rhs){
    std::pair<Value<Node_type>*,Value<Node_type>*> child(&lhs,&rhs);
    Value<Node_type> out(lhs.value+rhs.value,child,'+');
    return *out.update();
}
template<typename Node_type>
Value<Node_type>& operator+(Value<Node_type>&& lhs,Value<Node_type>& rhs){
    return lhs+rhs;
}
template<typename Node_type>
Value<Node_type>& operator+(Value<Node_type>& lhs,Value<Node_type>&& rhs){
    return lhs+rhs;
}
template<typename Node_type>
Value<Node_type>& operator+(Value<Node_type>&& lhs,Value<Node_type>&& rhs){
    return lhs+rhs;
}
template<typename Node_type>
Value<Node_type>& operator+(Value<Node_type>& lhs,Node_type& rhs){
    std::pair<Value<Node_type>*,Value<Node_type>*> child(&lhs,nullptr);
    Value<Node_type> out(lhs.value+rhs,child,'+');
    return *out.update();
}
template<typename Node_type>
Value<Node_type>& operator+(Node_type& lhs,Value<Node_type> rhs){
    return rhs+lhs;
}
template<typename Node_type>
Value<Node_type>& operator-(Value<Node_type>& lhs,Value<Node_type>& rhs){
    std::pair<Value<Node_type>*,Value<Node_type>*> child(&lhs,&rhs);
    Value<Node_type> out(lhs.value-rhs.value,child,'-');
    return *out.update();
}
template<typename Node_type>
Value<Node_type>& operator-(Value<Node_type>&& lhs,Value<Node_type>& rhs){
    return lhs-rhs;
}
template<typename Node_type>
Value<Node_type>& operator-(Value<Node_type>& lhs,Value<Node_type>&& rhs){
    return lhs-rhs;
}
template<typename Node_type>
Value<Node_type>& operator-(Value<Node_type>&& lhs,Value<Node_type>&& rhs){
    return lhs-rhs;
}
template<typename Node_type>
Value<Node_type>& operator*(Value<Node_type>& lhs,Value<Node_type>& rhs){
    std::pair<Value<Node_type>*,Value<Node_type>*> child(&lhs,&rhs);
    Value<Node_type> out(lhs.value*rhs.value,child,'*');
    return *out.update();
}
template<typename Node_type>
Value<Node_type>& operator*(Value<Node_type>&& lhs,Value<Node_type>& rhs){
    return lhs*rhs;
}
template<typename Node_type>
Value<Node_type>& operator*(Value<Node_type>& lhs,Value<Node_type>&& rhs){
    return lhs*rhs;
}
template<typename Node_type>
Value<Node_type>& operator*(Value<Node_type>&& lhs,Value<Node_type>&& rhs){
    return lhs*rhs;
}
template<typename Node_type>
Value<Node_type>& operator/(Value<Node_type>& lhs,Value<Node_type>& rhs){
    std::pair<Value<Node_type>*,Value<Node_type>*> child(&lhs,&rhs);
    Value<Node_type> out(lhs.value/rhs.value,child,'/');
    return *out.update();
}
template<typename Node_type>
Value<Node_type>& operator/(Value<Node_type>&& lhs,Value<Node_type>& rhs){
    return lhs/rhs;
}
template<typename Node_type>
Value<Node_type>& operator/(Value<Node_type>& lhs,Value<Node_type>&& rhs){
    return lhs/rhs;
}
template<typename Node_type>
Value<Node_type>& operator/(Value<Node_type>&& lhs,Value<Node_type>&& rhs){
    return lhs/rhs;
}
