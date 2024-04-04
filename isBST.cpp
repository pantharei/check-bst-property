#include <iostream>
#include <cstdlib>
#include <time.h>

//struct that represents a bst node
struct node{
    int label;
    struct node* left{nullptr};
    struct node* right{nullptr};

    node(int k):label(k){}
};

//overloading of operator<< with given node
std::ostream& operator<<(std::ostream& out, const node* n){
    out << n->label;
    return out;
}

//function that deallocates/frees the heap
node* dealloca(node* root){
    if(!root)return root;
    root->left = dealloca(root->left);
    root->right = dealloca(root->right);
    delete root;
    return nullptr;
}

//binary search tree inserton
node* insert(node* root, int k){
    if(!root){
        root = new node{k};
    }else if(k < root->label)
        root->left = insert(root->left,k);
    else if(k > root->label)
        root->right = insert(root->right,k);
        
    return root;
}

//inOrder/simmetric visit
void inOrder(const node* root){
    if(root){
        inOrder(root->left);
        std::cout << root << ' ';
        inOrder(root->right);
    }
}

//function that checks if the given tree is a BST
void p_check(node* root, bool& flag){
    if(!root || !flag)return;
    if(root->left)
        if(root->left->label >= root->label)
            flag *= false;
    if(root->right){
        if(root->right->label <= root->label)
            flag*=false;
    }

    p_check(root->left,flag);
    p_check(root->right,flag);

}

//returns the node with label = key
//(if exists) else returns nullptr
node* search(node* root, int key){
    if(!root)return root;
    if(key < root->label)
        search(root->left,key);
    else if(key > root->label)
        search(root->right,key);
    else return root;
}

//generic insertion to test p_check function
//true = right, false = left  --->  [pos]
void insert_generic(node* root, int key, bool pos){
    if(!root)return;
    node* child = new node{key};
    if(pos && !root->right)
        root->right = child;
    if(!pos && !root->left)
        root->left = child;
}

//void f. that returns via int& the bst's max value
void getMax(node* root, int&max){
    if(!root)return;
    if(!root->right)max = root->label;
    getMax(root->right,max);
}

int main(){
    using std::cout;
    //init randomization
    srand(time(NULL));

    //m will be used for getting the max value
    int n = 10,m{};
    node* root{nullptr};

    cout << "Numeri estratti :\n";
    for(int i =0;i<n;++i){
        int random = rand(); //random extraction
        std::cout << random << std::endl;
        root = insert(root, random);
    }

    getMax(root,m);

    cout << "Estrazione completata\n";
    cout << "Stampa crescente bst in corso..\n";
    inOrder(root);

    cout << '\n';

    //key to insert for testing p_check
    int key{m+1};

    //insert as a left child of m a node with major label
    //(there is no more a bst)
    insert_generic(search(root,m),key,false);

    bool check{true};
    p_check(root,check);

    if(check){
        cout << "Test bst ok\n";
    }else cout << "non e' bst\n";


    //freeing memory..
    cout << "deallocazione in corso..";
    dealloca(root);
    cout << "OK!\n";

    return 0;
}