#include <iostream>
#include "Model.hpp"
#include <vector>
#include <algorithm>
#include <set>

int main(){
    std::cout << "Hello in Mashalab3" << std::endl;
    std::cout << "My lab is about order relation" << std::endl;

    int n = 0;
    std::cout << "Enter amount object:" << std::endl;
    std::cin >> n;

    Model<int> rel(n);
    int m = 0;
    for(int i = 0; i < n; i++){
        std::cout << i << " > ? (enter -1 for end)" << std::endl;
        std::vector<strcNeib> neib;
        do{
            std::cin >> m;
            if(m >= n){
                std::cerr << "Warning, object doesn't exist" << std::endl;
            } else if (m >= 0) {
                strcNeib p = {m, 0};
                if(!(std::find(neib.begin(), neib.end(), p) == neib.end())){
                    std::cerr << "Warning, object has been already added" << std::endl;
                    continue;
                } else {
                    neib.push_back(p);
                }
            }
        }while(m != -1);
        rel.Set(i,i);
        rel.SetNeibor(i, neib);
    }

    if(rel.acycle().size() > 0){
        std::cerr << "Error, order relation has cycle" << std::endl;
        return 0;
    }
    std::vector<int> top = rel.topology_sort();
    std::set<int> search;
    std::cout << "Enter set {X} (enter -1 for end)" << std::endl;
    m = -1;
    do{
        std::cin >> m;
        if(m >= n){
            std::cerr << "Warning, object doesn't exist" << std::endl;
        } else if ( m >= 0) {
            search.insert(m);
        }
    }while(m != -1);

    int indsup = n - 1;
    int indinf = 0;
    while(indsup >= 0){
        if(!(search.find(top[indsup]) == search.end())){
            break;
        }
        indsup--;
    }

    for(; indsup < n; indsup++){
        bool issup = true;
        for(int i: search){
            if(i == top[indsup]){
                continue;
            }
            issup = issup && rel.greated(top[indsup], i);
        }

        if(issup){
            break;
        }
    }

    if(indsup == n){
        std::cout << "Sup wasn't found" << std::endl;
    } else {
        std:: cout << "Sup(X) = " << top[indsup] << std::endl;
        if(!(search.find(top[indsup]) == search.end())){
            std::cout << "Max(X) = " << top[indsup] << std::endl;
        }else {
            std::cout << "Max wasn't found" << std::endl;
        }
    }

    while(indinf < n){
        if(!(search.find(top[indinf]) == search.end())){
            break;
        }
        indinf++;
    }

    for(; indinf >= 0; indinf--){
        bool isinf = true;
        for(int i: search){
            if(i == top[indinf]){
                continue;
            }
            isinf = isinf && rel.greated(i, top[indinf]);
        }

        if(isinf){
            break;
        }
    }

    if(indinf < 0){
        std::cout << "Inf wasn't found" << std::endl;
    } else {
        std:: cout << "Inf(X) = " << top[indinf] << std::endl;
        if(!(search.find(top[indinf]) == search.end())){
            std::cout << "Min(X) = " << top[indinf] << std::endl;
        }else {
            std::cout << "Min wasn't found" << std::endl;
        }
    }



    return 0;
}