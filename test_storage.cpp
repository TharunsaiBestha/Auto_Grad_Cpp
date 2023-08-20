#include "Graph_storage.h"
#include<iostream>
int main(){
    Graph_storage<int> GS;
    int temp;
    for(int i=0;i<10;i++){
        temp=GS.add_node(i);
        std::cout<<temp<<" ";
    }
    int& t=GS.add_node(11);
    std::cout<<"\n";
    t=55;
    for(auto i:GS.Node_storage)std::cout<<i<<" ";
    std::cout<<"\n";
}