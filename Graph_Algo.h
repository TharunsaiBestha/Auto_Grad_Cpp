#include "Graph.h"
#include<stack>
#include<queue>
template<typename T>
struct Graph_Node
{
    T value;
    bool visited;
    Graph_Node():value(),visited(false){}
    Graph_Node(T v):value(v),visited(false){}
//    Graph_Node(const Graph_Node& V){value=V.value;visited=V.visited;}
//    void operator=(const Graph_Node& V){value=V.value;visited=V.visited;}
};
template<typename T>
bool operator==(const Graph_Node<T>& lhs,const Graph_Node<T>& rhs){
    return lhs.value==rhs.value;
}
template<typename Node_type,typename Edge_type>
using graph_itr=typename std::list<Node<Node_type,Edge_type>>::iterator;
template<typename Node_type,typename Edge_type>
struct DFS{
    graph_itr<Node_type, Edge_type> e;
    std::stack<graph_itr<Node_type, Edge_type>> s;
    DFS(graph_itr<Node_type, Edge_type> i,Graph<Node_type, Edge_type>& g){
        e=g.Node_list.end();s.push(i);}
    DFS(Graph<Node_type, Edge_type>& g){e=g.Node_list.end();}
    void set_init(graph_itr<Node_type, Edge_type> i){
        while(!s.empty())s.pop();
        s.push(i);
    }
    graph_itr<Node_type, Edge_type> next_node(){
    graph_itr<Node_type, Edge_type> v_it;
    bool t;
    //if(s.empty())return end();
        do{
            if(s.empty())return end();
    v_it=s.top();
    s.pop();}while((*v_it).node_value.visited);
    (*v_it).node_value.visited=true;
    for(auto i:(*v_it).link_from_node){
             t=(*i.first).node_value.visited;
             if(!t)s.push(i.first);
         }
         return v_it;}
         auto end(){
            return e; 
         }
};
template<typename Node_type,typename Edge_type>
using graph_itr=typename std::list<Node<Node_type,Edge_type>>::iterator;
template<typename Node_type,typename Edge_type>
struct BFS{
    graph_itr<Node_type, Edge_type> e;
    std::queue<graph_itr<Node_type, Edge_type>> q;
    BFS(graph_itr<Node_type, Edge_type> i,Graph<Node_type, Edge_type>& g){
        e=g.Node_list.end();q.push(i);}
    graph_itr<Node_type, Edge_type> next_node(){
    graph_itr<Node_type, Edge_type> v_it;
    bool t;
    //if(q.empty())return end();
        do{
            if(q.empty())return end();
    v_it=q.front();
    q.pop();}while((*v_it).node_value.visited);
    (*v_it).node_value.visited=true;
    for(auto i:(*v_it).link_from_node){
             t=(*i.first).node_value.visited;
             if(!t)q.push(i.first);
         }
         return v_it;}
         auto end(){
            return e; 
         }
};
template<typename Node_type,typename Edge_type>
using graph_itr=typename std::list<Node<Node_type,Edge_type>>::iterator;
template<typename Node_type,typename Edge_type>
struct Topo_Sort{
    graph_itr<Node_type, Edge_type> e;
    std::stack<graph_itr<Node_type, Edge_type>> s;
    std::stack<graph_itr<Node_type, Edge_type>> s_res;
    Topo_Sort(Graph<Node_type, Edge_type>& g){
        e=g.Node_list.end();
        init(g);}
        void init(Graph<Node_type, Edge_type>& g){
            graph_itr<Node_type, Edge_type> v_it;
            bool t=true;
            for(auto i=g.Node_list.begin();i!=g.Node_list.end();++i){
                if(!(*i).node_value.visited){
                    s.push(i);
            while(!s.empty()){
                v_it=s.top();
                t=(*v_it).node_value.visited;
                if(t){s_res.push(s.top());s.pop();}
                else{
                 (*v_it).node_value.visited=true;
                for(auto i:(*v_it).link_from_node){
                    t=(*i.first).node_value.visited;
                    if(!t)s.push(i.first);
                    }}}}}}
        auto next_node(){
            if(s_res.empty())return e;
            else{
                auto i=s_res.top();
                s_res.pop();
                return i;
            }
        }
        auto end(){
            return e; 
         }
};