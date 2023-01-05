#include<vector>
#include<iostream>
#include<algorithm>
#include<list>
template<typename Node_type,typename Edge_type>
struct Node{
    Node_type node_value;
    std::vector<std::pair<typename std::list<Node>::iterator,Edge_type>> link_from_node;
    Node(Node_type& value):node_value(value){}
    void add_link(typename std::list<Node>::iterator edge,Edge_type val=Edge_type{}){
        std::pair<typename std::list<Node>::iterator,Edge_type> temp;
        temp.first=edge;
        temp.second=val;
        for(auto& i:link_from_node){
            if(i.first==temp.first)return;
        }
        link_from_node.push_back(temp);
    }
};
template<typename Node_type,typename Edge_type>
bool operator==(const Node<Node_type,Edge_type>& lhs,const Node<Node_type,Edge_type>& rhs){
    return lhs.node_value==rhs.node_value;
}
template<typename Node_type,typename Edge_type>
struct Graph{
    std::list<Node<Node_type, Edge_type>> Node_list;
    auto add_vertex(Node_type& val){
        Node<Node_type, Edge_type> temp(val);
        if(Node_list.empty())Node_list.push_back(temp);
        for(auto i=Node_list.begin();i!=Node_list.end();++i){
            if((*i)==temp)return i;
        }
        Node_list.push_back(temp);
        for(auto i=Node_list.begin();i!=Node_list.end();++i){
            if((*i)==temp)return i;
        }
    }
    void add_edge(Node_type& lhs,Node_type& rhs){
        auto lhs_it=add_vertex(lhs);
        auto rhs_it=add_vertex(rhs);
       // auto node=*lhs_it;
        (*lhs_it).add_link(rhs_it);
    }
    auto get_it_vertex(Node_type& val){
        Node<Node_type, Edge_type> temp(val);
        for(auto i=Node_list.begin();i!=Node_list.end();++i){
            if((*i)==temp)return i;
        }
        return Node_list.end();
    }  
};