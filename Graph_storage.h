#include<list>
template<typename T>
struct Graph_storage{
    std::list<T> Node_storage;
    Graph_storage(){}
    typename std::list<T>::iterator add_node(const T val){
        Node_storage.push_back(val);
        typename std::list<T>::iterator iter=Node_storage.end();
        --iter;
        return iter;
    } 
};