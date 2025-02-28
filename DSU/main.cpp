#include <bits/stdc++.h>
#include "Profiler.h"

Profiler p("AVL");

using namespace std;

class DSU{
    int* parent;
    int* rank;

public:
    DSU(int n, Operation* op){
        parent = new int[n];
        rank = new int[n];

        for (int i = 0; i < n; ++i){
            op->count(2);
            parent[i] = -1;
            rank[i] = 1;
        }
    }

    int get_rank(int i){
        return rank[i];
    }

    int find(int i, Operation* op){
        if(parent[i] == -1){
            return i;
        }
        op->count(2);
        return parent[i] = find(parent[i],op);
    }

    void unite(int x, int y, Operation* op){
        int parentx = find(x, op);
        int parenty = find(y, op);

        op->count();
        if(parentx != parenty){
            op->count();
            if(rank[parentx] < rank[parenty]){
                op->count();
                parent[parentx] = parenty;
            }else if(rank[parentx] > rank[parenty]){
                op->count();
                parent[parenty] = parentx;
            }else{
                op->count(2);
                parent[parenty] = parentx;
                rank[parentx]++;
            }
        }
    }
};
void demo1(){
    Operation op =p.createOperation("op", 0);
    DSU set(10,&op);

    if(set.find(0, &op) != set.find(1, &op)){
        set.unite(0,1, &op);
    }

    if(set.find(2,&op) != set.find(3,&op)){
        set.unite(2,3,&op);
    }

    if(set.find(0,&op) != set.find(2,&op)){
        set.unite(0,2,&op);
    }

    if(set.find(4,&op) != set.find(5,&op)){
        set.unite(4,5,&op);
    }

    if(set.find(6,&op) != set.find(7,&op)){
        set.unite(6,7,&op);
    }

    queue<int> q;
    for(int i = 0; i < 10; i++){
        if(set.get_rank(i) > 1){
            q.push(i);
        }
        if(set.get_rank(i) == 1 && set.find(i,&op) == i){
            cout<<i<<endl;
        }
    }
    while(!q.empty()){
        int x = q.front();
        q.pop();
        int ok = 0;
        for(int i = 0; i < 10; i++){
            if(set.find(i,&op) == x){
                cout<<i<<" ";
                ok = 1;
            }
        }
        if(ok == 1){
            cout<<endl;
        }
    }
}
int kruskal(int k,vector<tuple<int,int,int>> val, Operation* opFIND, Operation* opUNITE, Operation* opMAKE,int mod){
    DSU set(k,opMAKE);
    map<int, vector<pair<int,int>>> edges;
    for(auto it : val){
        int first = get<0>(it);
        int second = get<1>(it);
        int third = get<2>(it);
        edges[third].push_back({first,second});
    }
    int sol = 0;
    for(auto elem : edges){
        for(auto it : elem.second){
            int x = it.first;
            int y = it.second;
            int cost = elem.first;
            if(set.find(x,opFIND) != set.find(y,opFIND)){
                sol += cost;
                if(mod == 1){
                    cout<<x<<" "<<y<<endl;
                }
                set.unite(x,y,opUNITE);
            }
        }
    }
    return sol;
}
void demoKruskal(){
    Operation op = p.createOperation("op", 0);
    vector<tuple<int,int,int>> val = { {1,2,3}, {0,2,1}, {0,3,4}, {2,3,5}, {2,4,1}, {3,1,2}, {3,4,5}, {4,1,2}, {0,4,6}};
    int sol = kruskal(5,val,&op,&op,&op,1);
    cout<<sol;
}

void perf(){
    for(int size = 100; size <= 10000; size += 100){


        std::random_device rd;
        std::uniform_int_distribution<int> dist_nod(0,size-1);
        std::uniform_int_distribution<int> dist_cost(1,1000);
        vector<tuple<int,int,int>> v;
        vector<int> not_conec(size-1);
        for(int i = 0; i < size-1; i++){
            not_conec[i] = i+1;
        }
        vector<int> con;
        con.push_back(0);
        for(int i = 0; i < size-1; i++){
            int size_not = not_conec.size();
            int size_con = con.size();
            uniform_int_distribution<int> dist_x(0,size_not-1);
            uniform_int_distribution<int> dist_y(0,size_con-1);
            int x = not_conec[dist_x(rd)];
            int y = con[dist_y(rd)];
            int cost = dist_cost(rd);
            con.push_back(x);
            auto it = std::find(not_conec.begin(), not_conec.end(),x);
            not_conec.erase(it);
            v.push_back({x,y,cost});
        }

        for(int i = 0; i < 3*size; i++){
            int x = dist_nod(rd);
            int y = dist_nod(rd);
            int cost = dist_cost(rd);
            while(x == y){
                y = dist_nod(rd);
            }
            v.push_back({x,y,cost});
        }

        Operation opMAKE = p.createOperation("opMAKE", size);
        Operation opUNITE = p.createOperation("opUNITE", size);
        Operation opFIND = p.createOperation("opFIND", size);

        int sol = kruskal(size,v,&opFIND, &opUNITE,&opMAKE,0);
        p.createGroup("OP", "opMAKE", "opFIND", "opUNITE");
    }
    p.showReport();
}

int main() {
    int c;
    cin>>c;
    if(c == 1){
        demo1();
    }else if(c == 2){
        demoKruskal();
    }else if(c == 3){
        perf();
    }
    return 0;
}
