#include <bits/stdc++.h>
using namespace std;

#define N 9973

typedef struct cell{
    int key;
    int status;
} Cell;

enum { FREE, OCCUPIED, DELETED};

int work;

int h_prime(int k, int m) {
    return k%m;
}

int quadratic_probing(int k, int m, int i) {
    return (h_prime(k,m) + 6 * i * i + 4 * i) % m;
}

void insert_key(int k, Cell *T, int m) {
    int pos;

    for(int i = 0; i < m; i++){
        pos = quadratic_probing(k, m, i);
        if(T[pos].status == FREE || T[pos].status == DELETED){
            T[pos].status = OCCUPIED;
            T[pos].key = k;
            return;
        }
    }
    cout<<"Table is fool " << k<<"\n";
}

int search_key(int k, Cell* T, int m) {
    int pos;

    for(int i = 0; i < m; i++){
        work++;
        pos = quadratic_probing(k, m, i);
        if(T[pos].status == FREE){
            return -1;
        }
        if(T[pos].status == OCCUPIED && T[pos].key == k){
            return pos;
        }
    }
    return -1;
}

void set_table_free(Cell *T, int m) {
    int i;
    for (i = 0; i<m; i++){
        T[i].status = FREE;
    }
}

int delete_key(int k, Cell* T, int m) {
    int pos;
    pos = search_key(k, T, m);
    if(pos != -1){
        T[pos].status = DELETED;
    }
    return pos;
}

void demo(){
    Cell* T = (Cell*)malloc(10 * sizeof(Cell));
    set_table_free(T,10);
    vector<int> v;
    random_device rd;
    uniform_int_distribution<int> dist(1,1000);
    for(int i = 0; i < 6; i++){
        int x = dist(rd);
        insert_key(x,T,10);
        v.push_back(x);
    }

    for(auto it : v){
        cout<<it<<" "<<search_key(it,T,10)<<"\n";
    }

    for(int i = 0; i < 6; i++){
        int x = dist(rd);
        cout<<x<<" "<<search_key(x,T,10)<<"\n";
    }

    int k = 0;
    for(auto it : v){
        delete_key(it, T, 10);
        k++;
        if(k == 3){
            break;
        }
    }
    cout<<"\n";
    for(auto it : v){
        cout<<it<<" "<<search_key(it, T, 10)<<"\n";
    }
}

void factor_umplere_cautare(){
    int factor[5] = {80,85,90,95,99};
    for(int i = 0; i < 5; i++){
        int umplere = factor[i];
        vector<int> v;
        Cell* T = (Cell*)malloc(N * sizeof(Cell));
        set_table_free(T,N);
        int n = N * umplere / 100;
        random_device rd;
        uniform_int_distribution<int> dist(1,100000);
        while(n){
            n--;
            int x = dist(rd);
            insert_key(x, T, N);
            v.push_back(x);
        }
        auto rng = default_random_engine{rd()};
        shuffle(v.begin(), v.end(), rng);
        int mid_effort_found = 0;
        int max_effort_found = 0;
        int mid_effort_notfound = 0;
        int max_effort_notfound = 0;
        int found = 0;
        int notfound = 0;
        for(int caz = 0; caz < 5; caz++) {
            for (int j = 0; j < 1500; j++) {
                work = 0;
                int x = dist(rd);
                int find = search_key(x, T, N);
                if (find != -1) {
                    mid_effort_found += work;
                    found++;
                    max_effort_found = max(max_effort_found, work);
                } else {
                    mid_effort_notfound += work;
                    notfound++;
                    max_effort_notfound = max(max_effort_notfound, work);
                }
            }

            for (int j = 0; j < 1500; j++) {
                work = 0;
                int find = search_key(v[j], T, N);
                if (find != -1) {
                    mid_effort_found += work;
                    found++;
                    max_effort_found = max(max_effort_found, work);
                }
            }
        }
        cout<<"factor de umplere " << umplere<<"\n";
        cout<<"efort mediu gasite " << mid_effort_found / found<<"\n";
        cout<<"efort maxim gasite " << max_effort_found<<"\n";
        cout<<"efort mediu negasite " << mid_effort_notfound / notfound<<"\n";
        cout<<"efort maxim negasite " << max_effort_notfound<<"\n";
        cout<<"\n";
    }
}

void factor_umplere_stergere(){
    int umplere = 99;
    vector<int> v;
    Cell* T = (Cell*)malloc(N * sizeof(Cell));
    set_table_free(T,N);
    int n = N * umplere / 100;
    int aux = n;
    random_device rd;
    uniform_int_distribution<int> dist(1,100000);
    while(n){
        n--;
        int x = dist(rd);
        insert_key(x, T, N);
        v.push_back(x);
    }
    auto rng = default_random_engine{rd()};
    shuffle(v.begin(), v.end(), rng);
    n = aux;
    int umplere_dorita = n*100 / N;
    while(umplere_dorita > 80){
        n--;
        delete_key(v[0],T,N);
        v.erase(v.begin());
        umplere_dorita = n*100 / N;
    }
    shuffle(v.begin(), v.end(), rng);
    int mid_effort_found = 0;
    int max_effort_found = 0;
    int mid_effort_notfound = 0;
    int max_effort_notfound = 0;
    int found = 0;
    int notfound = 0;
    for(int caz = 0; caz < 5; caz++) {
        for (int j = 0; j < 1500; j++) {
            work = 0;
            int x = dist(rd);
            int find = search_key(x, T, N);
            if (find != -1) {
                mid_effort_found += work;
                found++;
                max_effort_found = max(max_effort_found, work);
            } else {
                mid_effort_notfound += work;
                notfound++;
                max_effort_notfound = max(max_effort_notfound, work);
            }
        }

        for (int j = 0; j < 1500; j++) {
            work = 0;
            int find = search_key(v[j], T, N);
            if (find != -1) {
                mid_effort_found += work;
                found++;
                max_effort_found = max(max_effort_found, work);
            }
        }
    }
    cout<<"factor de umplere " << umplere_dorita<<"\n";
    cout<<"efort mediu gasite " << mid_effort_found / found<<"\n";
    cout<<"efort maxim gasite " << max_effort_found<<"\n";
    cout<<"efort mediu negasite " << mid_effort_notfound / notfound<<"\n";
    cout<<"efort maxim negasite " << max_effort_notfound<<"\n";
    cout<<"\n";
}


int main() {
    while(1) {
        cout << "Selectati 1 pentru demo, 2 pentru evaluare cautare, 3 pentru evaluare cautare dupa stergere sau altceva pentru oprire\n";
        int c;
        cin >> c;
        if (c == 1) {
            demo();
        } else if(c == 2){
            factor_umplere_cautare();
        }else if(c == 3){
            factor_umplere_stergere();
        }else{
            break;
        }
    }
    return 0;
}
