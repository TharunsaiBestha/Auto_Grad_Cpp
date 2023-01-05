#include "Graph_Algo.h"
#include<iostream>
int main(){
    Graph_Node<int> lhs(5);
    Graph_Node<int> rhs(0);
    Graph<Graph_Node<int>,int> g;
    std::vector<std::pair<int,int>> v={{0,2},{0,3},{2,4},{2,5},{3,7},{4,6},{5,6},{5,7},{1,1}};
    for(auto i:v){
        lhs.value=i.first;
        rhs.value=i.second;
        g.add_edge(lhs,rhs);
    }
    lhs.value=0;
    auto it=g.get_it_vertex(lhs);
    Topo_Sort<Graph_Node<int>,int> ts(g);
    it=ts.next_node();
    while(it!=ts.end()){
        std::cout<<(*it).node_value.value<<"->";
        it=ts.next_node();
    }
    std::cout<<"\n";
}