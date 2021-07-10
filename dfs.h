#ifndef DFS_H
#define DFS_H
#include "datahandler.h"
#include "array.h"
#include "webclass.h"
#include <vector>
#include "database.h"
class dfs {
  private:
  public:
    dfs(datahandler * db);
    std::vector<int> colors;
    std::vector<int> pred;
    datahandler *db;
    int start_dfs(Array<webclass> all_wc);

    void dfs_visit(int id);
};

#endif