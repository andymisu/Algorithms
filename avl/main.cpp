#include <bits/stdc++.h>
#include "Profiler.h"

Profiler p("AVL");
using namespace std;
struct Node{
    int key;
    int height;
    int size;
    Node* left;
    Node* right;
};

Node* createNode(int k){
    Node* node = (Node*)calloc(1, sizeof(Node));
    node->key = k;
    node->height = 1;
    node->size = 1;
    node->left = NULL;
    node->right = NULL;
    return node;
}

int get_height(Node* node){
    if(node == NULL){
        return 0;
    }
    return node->height;
}

int get_size(Node* node){
    if(node == NULL){
        return 0;
    }
    return node->size;
}


void update_node(Node* node){
    if(node != NULL){
        node->height = 1 + max(get_height(node->left), get_height(node->right));
        node->size = 1 + get_size(node->left) + get_size(node->right);
    }
}

int get_balance(Node* node){
    if(node == NULL){
        return 0;
    }
    return get_height(node->left) - get_height(node->right);
}

Node* right_rotation(Node* y){
    Node* x = y->left;
    Node* z = x->right;

    x->right = y;
    y->left = z;

    update_node(y);
    update_node(x);
    return x;
}

Node* left_rotation(Node* x){
    Node* y = x->right;
    Node* z = y->left;

    y->left = x;
    x->right = z;

    update_node(x);
    update_node(y);

    return y;
}

Node* insert(Node* node, int key, Operation* op){

    op->count();

    if (node == NULL){
        return createNode(key);
    }

    op->count();

    if(key < node->key){
        node->left = insert(node->left, key, op);

        op->count();

    }else if (key > node->key){
        node->right = insert(node->right, key, op);

        op->count();

    }else{
        return node;
    }

    update_node(node);
    op->count(2);

    int balance = get_balance(node);
    op->count();

    op->count(4);

    if (balance > 1 && key < node->left->key){
        op->count(6);
        return right_rotation(node);
    }

    if (balance < -1 && key > node->right->key){
        op->count(6);
        return left_rotation(node);
    }

    if (balance > 1 && key > node->left->key){
        node->left = left_rotation(node->left);
        op->count(13);
        return right_rotation(node);
    }

    if (balance < -1 && key < node->right->key){
        op->count(13);
        node->right = right_rotation(node->right);
        return left_rotation(node);
    }

    return node;
}



void pretty_print(Node* node, int h){
    for(int i = 0; i < h; i++){
        cout<<"     ";
    }
    cout<<node->key<<"\n";
    if(node->left != NULL){
        pretty_print(node->left, h+1);
    }
    if(node->right != NULL){
        pretty_print(node->right, h + 1);
    }
}

Node* delete_min(Node* node, Node** minNode,Operation* op){
    if(node->left == NULL){
        *minNode = node;
        op->count();
        return node->right;
    }

    node->left = delete_min(node->left, minNode, op);
    op->count();

    update_node(node);
    op->count(2);
    return node;
}

Node* deleteKth(Node* root, int k, Operation* op) {
    op->count(2);
    if (root == NULL || k < 1 || k > get_size(root)) {
        return root;
    }

    op->count(2);
    int leftsize = get_size(root->left);

    if (k == leftsize + 1) {
        op->count(2);
        if (root->left == NULL) {
            return root->right;
        }
        if (root->right == NULL) {
            return root->left;
        }

        op->count(2);
        Node* minNode = NULL;
        root->right = delete_min(root->right, &minNode, op);
        root->key = minNode->key;
        free(minNode);
    } else if (k <= leftsize) {
        op->count();
        root->left = deleteKth(root->left, k, op);
    } else {
        op->count();
        root->right = deleteKth(root->right, k - leftsize - 1, op);
    }

    update_node(root);
    op->count(2);
    op->count();
    int balance = get_balance(root);

    op->count(8);
    if (balance > 1 && get_balance(root->left) >= 0) {
        op->count(6);
        return right_rotation(root);
    }
    if (balance > 1 && get_balance(root->left) < 0) {
        op->count(13);
        root->left = left_rotation(root->left);
        return right_rotation(root);
    }
    if (balance < -1 && get_balance(root->right) <= 0) {
        op->count(6);
        return left_rotation(root);
    }
    if (balance < -1 && get_balance(root->right) > 0) {
        op->count(13);
        root->right = right_rotation(root->right);
        return left_rotation(root);
    }

    return root;
}

/*
void preorder(Node* node){
    if(node != NULL){
        cout<<node->key;
        preorder(node->left);
        preorder(node->right);
    }
}
 */

int select(Node* root, int k, Operation* op){
    op->count(2);
    if (!root || k < 1 || k > get_size(root)) {
        return -1;
    }

    op->count();
    int leftsize = get_size(root->left);
    if(leftsize + 1 == k){
        return root->key;
    }else if (k <= leftsize){
        return select(root->left, k, op);
    }else{
        return select(root->right, k - leftsize - 1, op);
    }
}


void demo(){
    Node* node = NULL;
    Operation op = p.createOperation("op", 1);
    for(int i = 1; i <= 9; i++){
        node = insert(node,i,&op);
    }
    cout<<endl;
    pretty_print(node,0);
    for(int i = 0; i < 5; i++){
        random_device rd;
        int dr = 9 - i;
        uniform_int_distribution dist(1,dr);
        int ind = dist(rd);
        int s = select(node, ind, &op);
        if(s == -1){
            cout<<"Nu se poate "<<ind;
        }else{
            cout<<ind<<" "<<s;
        }
        cout<<endl;
        node = deleteKth(node, ind, &op);
        pretty_print(node, 0);
    }
}

int erorr = 0;
void perf(){
    for(int size = 100; size <= 10000; size += 100){
        for(int k = 0; k < 5; k++){
            int *v = (int*)calloc(size, sizeof(int));
            FillRandomArray(v,size);
            Operation opINS = p.createOperation("opINS", size);
            Operation opSEL = p.createOperation("opSEL", size);
            Operation opDEL = p.createOperation("opDEL", size);
            Node* root = NULL;
            for(int i = 0; i < size; i++){
                root = insert(root,v[i],&opINS);
            }

            for(int i = 0; i < size; i++){
                random_device rd;
                uniform_int_distribution<int> dist(1, size - i);
                int pos = dist(rd);
                int x = select(root, pos, &opSEL);
                root = deleteKth(root, pos, &opDEL);
            }
        }
        p.createGroup("OP", "opINS", "opSEL", "opDEL");
    }
    p.divideValues("opINS", 5);
    p.divideValues("opSEL", 5);
    p.divideValues("opDEL", 5);
    p.showReport();
}
int main(){
    int x;
    cin>>x;
    if(x == 1){
        demo();
    }if(x == 2){
        perf();
    }
    return 0;
}
