#include <bits/stdc++.h>
using namespace std;
struct Node{
    int key;
    struct Node* left;
    struct Node* right;
};

struct MultiNode{
    int key;
    int nrsons;
    vector<MultiNode*> son;
};
int work;
struct MultiBinaryNode{
    int key;
    MultiBinaryNode* brother;
    MultiBinaryNode* son;
};

MultiBinaryNode* createMultiBinaryNode(int key){
    MultiBinaryNode* node = (MultiBinaryNode*) calloc(1,sizeof(MultiBinaryNode));
    node->key = key;
    return node;
}

MultiNode* createMultiNode(int key){
    MultiNode* node = (MultiNode*)calloc(1,sizeof(MultiNode));
    node->key = key;
    node->nrsons = 0;
    return node;
}

Node* createNode(int key){
    Node* node = (Node*)calloc(1,sizeof(Node));
    node->key = key;
    return node;
}

void preorder(MultiBinaryNode* root){
    if(root != NULL){
        cout<<root->key<<" ";
        preorder(root->son);
        preorder(root->brother);
    }
}

void iterative_preorder(MultiBinaryNode* root){
    if(root != NULL){
        stack<MultiBinaryNode*> st;
        st.push(root);
        while(!st.empty()){
            MultiBinaryNode* node = st.top();
            cout<<node->key<<" ";
            st.pop();
            if(node->brother != NULL){
                st.push(node->brother);
            }
            if(node->son != NULL){
                st.push(node->son);
            }
        }
    }
}

void pretty_print_vector_tati(vector<int> v, int n, int h, int dad){
    for(int i = 0; i < n; i++){
        if(v[i] == dad){
            for(int j = 0; j < h; j++){
                cout<<"     ";
            }
            cout<<i+1<<endl;
            pretty_print_vector_tati(v,n,h+1, i+1);
        }
    }
}
void pretty_print_multi(MultiNode* root, int h){
    for(int i = 0; i < h; i++){
        cout<<"     ";
    }
    cout<<root->key<<"\n";

    for(auto it : root->son){
        pretty_print_multi(it,h+1);
    }
}

MultiNode* vector_tati_to_multi(vector<int> v, int n){

    vector<MultiNode*> H(n+1);
    for(int i = 1; i <= n; i++){
        MultiNode* node = createMultiNode(i);
        H[i] = node;
    }
    MultiNode* root = NULL;
    for(int i = 0; i < n; i++){
        if(v[i] == -1){
            root = H[i+1];
        }else{
            MultiNode* dad = H[v[i]];
            MultiNode* son = H[i+1];
            dad->son.push_back(son);
            dad->nrsons++;
        }
    }



    pretty_print_multi(root,0);
    return root;
}
void pretty_print_ab(MultiBinaryNode* root,int h){
    for(int i = 0; i < h; i++){
        cout<<"     ";
    }
    cout<<root->key<<"\n";
    if(root->son != NULL){
        pretty_print_ab(root->son, h+1);
    }
    if(root->brother != NULL){
        pretty_print_ab(root->brother, h);
    }
}


MultiBinaryNode* multi_to_binary(MultiNode* root) {
    MultiBinaryNode* binary_root = createMultiBinaryNode(root->key);
    queue<MultiNode*> q;
    queue<MultiBinaryNode*> q_binary;

    q.push(root);
    q_binary.push(binary_root);

    while (!q.empty()) {
        MultiNode* node = q.front();
        MultiBinaryNode* binaryNode = q_binary.front();
        q.pop();
        q_binary.pop();

        if (node->nrsons > 0) {

            // Cream fiul pentru primul copil
            binaryNode->son = createMultiBinaryNode(node->son[0]->key);
            q.push(node->son[0]);
            q_binary.push(binaryNode->son);

            // Adaugam fratii copilului
            MultiBinaryNode* currentBrother = binaryNode->son;
            for (int i = 1; i < node->nrsons; i++) {
                currentBrother->brother = createMultiBinaryNode(node->son[i]->key);
                currentBrother = currentBrother->brother;
                q.push(node->son[i]);
                q_binary.push(currentBrother);
            }
        }
    }
    pretty_print_ab(binary_root,0);
    return binary_root;
}
void demo(){
    vector<int> v = {2, 7, 5, 2, 7, 7, -1, 5, 2};
    pretty_print_vector_tati(v,9,0,-1);
    MultiNode* root = vector_tati_to_multi(v,9);
    MultiBinaryNode *binary_root = multi_to_binary(root);
    preorder(binary_root);
    cout<<"\n";
    iterative_preorder(binary_root);
    cout<<"\n";
}

void preoder_node(Node* root, int caz){
    if(root != NULL){
        if(caz == 0){
            cout<<root->key;
        }else{
            work++;
        }
        preoder_node(root->left, caz);
        preoder_node(root->right, caz);
    }
}

void iterative_preorder_node(Node* root, int caz){
    if(root != NULL){
        stack<Node*> st;
        st.push(root);
        while(!st.empty()){
            Node* node = st.top();
            if(caz == 0){
                cout<<node->key<<" ";
            }else{
                work++;
            }
            st.pop();
            if(node->right != NULL){
                st.push(node->right);
            }
            if(node->left != NULL){
                st.push(node->left);
            }
        }
    }
}
void insert_random(Node* root, int key){
    random_device rd;
    uniform_int_distribution<int> dist(0,1);
    int direction = dist(rd);
    if(direction == 0){
        if(root->left == NULL){
            Node* node = createNode(key);
            root->left = node;
        }else{
            insert_random(root->left, key);
        }
    }else{
        if(root->right == NULL){
            Node* node = createNode(key);
            root->right = node;
        }else{
            insert_random(root->right, key);
        }
    }
}
void perf(){
    random_device rd;
    uniform_int_distribution<int> dist(0,10000);
    Node* root = createNode(dist(rd));
    for(int i = 100; i <= 1000; i += 100){
        int l;
        if(i == 100){
            l = 99;
        }else{
            l = 100;
        }
        for(int j = 0; j < l; j++){
            int x = dist(rd);
            insert_random(root, x);
        }
        work = 0;
        preoder_node(root, 1);
        cout<<"Noduri: ";
        cout<<i<<"    Operatii recursiv: "<<work<<"    Operatii Iterative: ";
        work = 0;
        iterative_preorder_node(root, 1);
        cout<<work<<"\n";

    }
}

int main() {
    int c;
    while(true) {
        cout << "1 pentru demo, 2 pentru perf";
        cin >> c;
        if (c == 1) {
            demo();
        } else if(c == 2) {
            perf();
        }else{
            break;
        }
    }

    return 0;
}
