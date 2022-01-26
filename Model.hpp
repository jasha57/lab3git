#ifndef MODEL_HPP
#define MODEL_HPP
#include <iostream>
#include <vector>


struct strcNeib {
    int numb;
    int weight;
    bool operator == (const strcNeib & a){
        return (numb == a.numb) && (weight == a.weight);
    }
};

template<typename Tnode>
class Model{
    private:
    std::vector < std::vector < strcNeib > > list;
    std::vector < Tnode> nodes;

    public:

    Model(int _size) : list(_size), nodes(_size) {}
    Model() {}

    std::vector < strcNeib > neib(int index) {
        if(list.size() <= index) {
            return std::vector<strcNeib> ();
        } 
        return list[index];
    }

    Tnode Get(int index) {
        if(nodes.size() <= index) {
            return Tnode ();
        }
        return nodes[index];
    }

    int searchNode(Tnode  serch) {
        for(int i = 0; i < nodes.size(); i++) {
            if(nodes[i] == serch) {
                return i;
            }
        }
        return -1;
    }

    void Set(int index, Tnode & set){
        if(nodes.size() <= index){
            return;
        }
        nodes[index] = set;
    }

    void SetNeibor(int index, std::vector<strcNeib> neib){
        if(nodes.size() <= index)
            return;
        list[index] = neib;
    }

    int addNode(Tnode & data, std::vector<strcNeib> neibor){
        nodes.push_back(data);
        list.push_back(neibor);
        return nodes.size() - 1;
    }

    std::vector<int> acycle() {
        std::vector<int> ans;
        std::vector<char> color(nodes.size(), 0); // 0 - white, 1 - grey , 2 - black
        std::vector<int> p(nodes.size());
        int cycle_end;
        int cycle_st;
        for(int i = 0; i < nodes.size(); i++) {
            if(color[i] == 0){
                if(!acycle_dfs(color, i, p, cycle_end, cycle_st)) {
                    ans.push_back(cycle_end);
                    ans.push_back(cycle_st);
                    int t = p[cycle_st];
                    while(t != cycle_end){
                        t = p[t];
                        ans.push_back(t);
                    }
                    return ans;
                }
            }
        }

        return std::vector<int> ();
    }
    


    std::vector<int> topology_sort(){
        std::vector<int> ans;
        std::vector<bool> visit(nodes.size(), false);
        if(acycle().size() == 0){
            for(int i = 0; i < nodes.size(); i++){
                if(!visit[i])
                    topology_sort_dfs(visit, ans, i);
            }
            return ans;
        } else {
            std::cerr << "Graph not acycle" << std::endl; // for DEBUG
            return std::vector<int> ();
        }
    }

    bool greated(int index1, int index2) { // check in index1 > index2
        std::vector<bool> visit(nodes.size(), false);
        return greated_dfs(visit, index1, index2);
    }
    

    int size(){
        return nodes.size();
    }

    void DEBUG_INFO(){
        for(int i = 0; i < list.size(); i++){
            std::cout << i << ": " ;
            for(int j = 0; j < list[i].size(); j++){
                std::cout << list[i][j].numb << "(" << nodes[list[i][j].numb] << ") ," ;
            }
            std::cout << std::endl;
        }
    }


    protected:

    bool greated_dfs(std::vector<bool> & visit, int index1, int index2){
        visit[index1] = true;
        for(int i = 0; i < list[index1].size(); i++){
            if(list[index1][i].numb == index2){
                return true;
            }
            if(!visit[list[index1][i].numb]){
                if(greated_dfs(visit, list[index1][i].numb, index2)){
                    return true;
                }
            }
        }

        return false;
    }

    void topology_sort_dfs(std::vector<bool> & visit, std::vector<int>& ans, int index){
        visit[index] = true;
        for(int i = 0; i < list[index].size(); i++){
            if(!visit[list[index][i].numb]){
                topology_sort_dfs(visit, ans, list[index][i].numb);
            }
        }
        ans.push_back(index);
    }

    bool acycle_dfs(std::vector<char> & color, int index, std::vector<int> & p, int & cycle_end, int & cycle_st ){
        color[index] = 1;
        for(int i = 0; i < list[index].size(); i++){
            if(color[ list[index][i].numb ] == 0 ){
                p[ list[index][i].numb ] = index;
                if(!acycle_dfs(color, list[index][i].numb , p, cycle_end, cycle_st)){
                    return false;
                }
            }else if(color[ list[index][i].numb ]== 1){
                cycle_end = index;
			    cycle_st = list[index][i].numb;
                return false;
            }
        }
        color[index] = 2;

        return true;
    }

};


#endif