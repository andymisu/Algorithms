#include <bits/stdc++.h>
using namespace std;
int distx[8] = {1,2,2,-1,-2,-2,-1};
int disty[8] = {-2,-1,1,2,2,1,-1,-2};
int main() {
    for(int n = 1; n <= 20; n++){
        int k = n*n;
        vector<vector<int>> v(n,vector<int>(n));
        queue<pair<int,int>> q;
        q.push({0,0});
        while(!q.empty()){
            auto first = q.front();
            int x = first.first;
            int y = first.second;
            q.pop();
            for(int i = 0; i < 8; i++){
                int nextx = x + distx[i];
                int nexty = y + disty[i];
                if(nextx >= 0 && nextx < n && nexty >= 0 && nexty < n){
                    if(v[nextx][nexty] == 0){
                        v[nextx][nexty] = 1;
                        k--;
                        q.push({nextx,nexty});
                    }
                }
            }
            if(k == 0){
                break;
            }
        }
        if(k == 0){
            cout<<n<<" "<<"DA"<<endl;
        }else{
            cout<<n<<" "<<"NU"<<endl;
        }
    }
    return 0;
}
