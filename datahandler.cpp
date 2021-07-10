#include "datahandler.h"

datahandler::datahandler(int m) {
    switch (m) {
    case 1:
        data = new Array<webclass>();
        break;
    case 2:
        data = new AVLTree<webclass>();
        break;
    case 3:
        data = new hashtable<webclass>();
        break;
    }
    this->setMode(m);
}

void datahandler::remove(int id, int neighbor) {
    webclass *wc = data->find(id);
    if (wc != nullptr) {
        wc->neighbors->remove(neighbor);
    }
}

Array<webclass> datahandler::dfs() {
    std::vector<webclass> all_Wc = data->return_all();
    Array<webclass> o;

    for (int i = 0; i < all_Wc.size(); i++) {
        o.insert(all_Wc[i]);
    }

    int s = all_Wc.size();
    for (int i = 0; i < s; i++) {
        int current_id = all_Wc[i].id;
        std::vector<int> neighs = o.find(current_id)->neighbors->return_all();
        for (int j = 0; j < neighs.size(); j++) {
            webclass *exists = o.find(neighs[j]);
            if (exists != nullptr) {
                exists->neighbors->insert(current_id);
            } else {
                webclass new_wc = webclass(getMode());
                new_wc.id = neighs[j];
                new_wc.neighbors->insert(current_id);
                o.insert(new_wc);  
            }
        }
    }
    return o;
}

void datahandler::insert(int id, int neighbor) {
    clock_t a = clock();
    webclass *wc = data->find(id);
    if (wc != nullptr) { // Check if class exists
        wc->neighbors->insert(neighbor);
    } else { // If class doesn't exist create it
        webclass new_wc = webclass(getMode());
        new_wc.id = id;
        new_wc.neighbors->insert(neighbor);
        data->insert(new_wc);
    }
    clock_t b = clock();
}

std::vector<int> datahandler::findNeighbors(int id) {
    webclass *wc = data->find(id);
    std::vector<int> res;

    if (wc != nullptr) {
        res = wc->neighbors->return_all();
    }
    std::sort(res.begin(), res.end());
    return res;
}