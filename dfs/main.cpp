#include <bits/stdc++.h>
#include "Profiler.h"

Profiler p("AVL");
using namespace std;

void dfs(int node,vector<vector<int>> edges, vector<bool>& fr, int mode, Operation *op){
    fr[node] = 1;
    op->count();
    if(mode == 1){
        cout<<node<<" ";
    }
    for(auto it : edges[node]){
        op->count();
        if(fr[it] == 0){
            dfs(it,edges,fr,mode,op);
        }
    }
}

void strongly_connected(int node, vector<vector<int>>& edges, vector<int>& disc, vector<int>& low, stack<int>& st, vector<bool>& fr, int& time){
    disc[node] = low[node] = ++time;
    st.push(node);
    fr[node] = true;

    for (auto it : edges[node]){
        int aux = it;
        if (disc[aux] == -1){
            strongly_connected(aux, edges, disc, low, st, fr, time);
            low[node] = min(low[node], low[aux]);
        } else if (fr[aux]){
            low[node] = min(low[node], disc[aux]);
        }
    }

    if (low[node] == disc[node]){
        while (!st.empty() && st.top() != node){
            int x = st.top();
            cout << x << " ";
            fr[x] = false;
            st.pop();
        }
        int x = st.top();
        cout << x << "\n";
        fr[x] = false;
        st.pop();
    }
}

void initializare(int n, vector<vector<int>> edges){
    vector<int> disc(n, -1);
    vector<int> low(n, -1);
    vector<bool> fr(n, false);
    stack<int> st;
    int time = 0;

    for (int i = 0; i < n; i++) {
        if (disc[i] == -1) {
            strongly_connected(i, edges, disc, low, st, fr, time);
        }
    }
}

//trebuie sa fie aciclic
void topological(int node, vector<vector<int>>& edges, vector<bool>& fr,stack<int>& st){
    fr[node] = 1;
    for(auto it : edges[node]){
        if(!fr[it]){
            topological(it,edges,fr,st);
        }
    }
    st.push(node);
}
void topo_sort(int n,vector<vector<int>> edges){
    stack<int> st;
    vector<bool> fr(n,false);

    for(int i = 0; i < n; i++){
        if(!fr[i]){
            topological(i,edges,fr,st);
        }
    }

    while(!st.empty()){
        cout<<st.top()<<" ";
        st.pop();
    }
    cout<<"\n\n";
}
void demo(){
    int n = 11;

    vector<vector<int>> edgeDFS(5);
    edgeDFS[0].push_back(1);
    edgeDFS[0].push_back(2);
    edgeDFS[1].push_back(3);
    edgeDFS[1].push_back(4);
    edgeDFS[2].push_back(3);
    edgeDFS[2].push_back(4);
    edgeDFS[3].push_back(4);

    for(int i = 0; i < 5; i++){
        cout<<i<<" : ";
        for(auto it : edgeDFS[i]){
            cout<<it<<" ";
        }
        cout<<"\n";
    }
    vector<bool> fr(5);
    Operation op = p.createOperation("op",1);
    dfs(0,edgeDFS,fr,1,&op);
    cout<<"\n\n";
    topo_sort(5,edgeDFS);
    vector<vector<int>> edges(n);
    edges[0].push_back(1);
    edges[0].push_back(3);
    edges[1].push_back(2);
    edges[1].push_back(4);
    edges[2].push_back(0);
    edges[2].push_back(6);
    edges[3].push_back(2);
    edges[4].push_back(5);
    edges[4].push_back(6);
    edges[5].push_back(6);
    edges[5].push_back(7);
    edges[5].push_back(8);
    edges[5].push_back(9);
    edges[6].push_back(4);
    edges[7].push_back(9);
    edges[8].push_back(9);
    edges[9].push_back(8);

    initializare(n,edges);
}

void perf(){
    int v = 100;
    for(int e = 1000; e <= 4500; e += 100){
        set<pair<int,int>> S;
        random_device rd;
        uniform_int_distribution<int> dist(0,v-1);
        vector<vector<int>> edge(v);

        for(int i = 0; i < e; i++){
            int x = dist(rd);
            int y = dist(rd);
            if(x == y){
                y = dist(rd);
            }
            if(!S.contains({x,y})){
                S.insert({x,y});
                edge[x].push_back(y);
            }else{
                i--;
            }
        }

        Operation op = p.createOperation("OP-E",e);
        vector<bool> fr(v,false);
        for(int i = 0; i < v; i++){
            if(fr[i] == 0){
                dfs(i,edge,fr,0,&op);
            }
        }
    }

    int e = 4500;
    for(int vv = 100; vv <= 200; vv += 10){
        set<pair<int,int>> S;
        random_device rd;
        uniform_int_distribution<int> dist(0,vv-1);
        vector<vector<int>> edge(vv);

        for(int i = 0; i < e; i++){
            int x = dist(rd);
            int y = dist(rd);
            if(x == y){
                y = dist(rd);
            }
            if(!S.contains({x,y})){
                S.insert({x,y});
                edge[x].push_back(y);
            }else{
                i--;
            }
        }

        Operation op = p.createOperation("OP-V",vv);
        vector<bool> fr(vv,false);
        for(int i = 0; i < vv; i++){
            if(fr[i] == 0){
                dfs(i,edge,fr,0,&op);
            }
        }

    }
    p.showReport();
}
int main() {
    demo();
    perf();
    return 0;
}
