#include "dfs.h"
#define WHITE 0
#define GRAY 1
#define BLACK 2


dfs::dfs(datahandler * db) {
    this->db = db;
}

int dfs::start_dfs(Array<webclass> wc) {
    std::vector<webclass> v = wc.return_all();
    int max_id = v.back();
    
    for (int i = 0; i < max_id; i++){
        colors.push_back(WHITE);
        pred.push_back(-1);
    }

    int components = 0;

    for(int i = 0; i < v.size(); i++){
        if(colors[v[i].id] == WHITE){
            dfs_visit(v[i].id);
            components++;
        }
    }
    return components;
}




void dfs::dfs_visit(int id) {
    colors[id] = GRAY;
    std::vector<int> n = db->findNeighbors(id);
    for(int i = 0; i < n.size(); i++){
        int neighbor = n[i]; // n[i] = id of neighbor.
        if(colors[neighbor] == WHITE){
            pred[neighbor] = id;
            dfs_visit(neighbor);
        }
    }
    colors[id] = BLACK;
}