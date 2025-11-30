#include <iostream>
#include <algorithm>

using namespace std;
using ull = unsigned long long;
using ll = long long;

struct Node {
    int key;
    int height;
    int sz;   // subtree total elements (including duplicates)
    int cnt;  // count of this key (duplicates)
    Node *left, *right;
    Node(int k): key(k), height(1), sz(1), cnt(1), left(nullptr), right(nullptr) {}
};

int getHeight(Node* t){ return t ? t->height : 0; }
int getSize(Node* t){ return t ? t->sz : 0; }

void update(Node* t){
    if(!t) return;
    t->height = 1 + max(getHeight(t->left), getHeight(t->right));
    t->sz = t->cnt + getSize(t->left) + getSize(t->right);
}

Node* rightRotate(Node* y){
    Node* x = y->left;
    Node* T2 = x->right;
    x->right = y;
    y->left = T2;
    update(y);
    update(x);
    return x;
}

Node* leftRotate(Node* x){
    Node* y = x->right;
    Node* T2 = y->left;
    y->left = x;
    x->right = T2;
    update(x);
    update(y);
    return y;
}

Node* balance(Node* root){
    if(!root) return root;
    int bf = getHeight(root->left) - getHeight(root->right);
    if(bf > 1){
        if(getHeight(root->left->left) >= getHeight(root->left->right))
            root = rightRotate(root); // LL
        else {
            root->left = leftRotate(root->left); // LR
            root = rightRotate(root);
        }
    } else if(bf < -1){
        if(getHeight(root->right->right) >= getHeight(root->right->left))
            root = leftRotate(root); // RR
        else {
            root->right = rightRotate(root->right); // RL
            root = leftRotate(root);
        }
    }
    return root;
}

Node* insert(Node* root, int key){
    if(!root) return new Node(key);
    if(key == root->key){
        root->cnt++;
    } else if(key < root->key){
        root->left = insert(root->left, key);
    } else {
        root->right = insert(root->right, key);
    }
    update(root);
    return balance(root);
}

// kth smallest (1-based)
Node* kth(Node* root, int k){
    if(!root || k <= 0 || k > getSize(root)) return nullptr;
    int leftSize = getSize(root->left);
    if(k <= leftSize) return kth(root->left, k);
    if(k <= leftSize + root->cnt) return root;
    return kth(root->right, k - leftSize - root->cnt);
}

// count how many elements < key
int countSmaller(Node* root, int key){
    if(!root) return 0;
    if(key <= root->key) return countSmaller(root->left, key);
    // key > root->key
    return getSize(root->left) + root->cnt + countSmaller(root->right, key);
}

Node* successor(Node* root, int val){
    Node* cur = root;
    Node* succ = nullptr;
    while(cur){
        if(cur->key > val){
            succ = cur;
            cur = cur->left;
        } else cur = cur->right;
    }
    return succ;
}
Node* predecessor(Node* root, int val){
    Node* cur = root;
    Node* pred = nullptr;
    while(cur){
        if(cur->key < val){
            pred = cur;
            cur = cur->right;
        } else cur = cur->left;
    }
    return pred;
}

Node* remove(Node* root, int key){
    if(!root) return nullptr;
    if(key < root->key){
        root->left = remove(root->left, key);
    } else if(key > root->key){
        root->right = remove(root->right, key);
    } else {
        if(root->cnt > 1){
            root->cnt--;
        } else {
            if(!root->left || !root->right){
                Node* temp = root->left ? root->left : root->right;
                delete root;
                return temp;
            } else {
                Node* suc = root->right;
                while(suc->left) suc = suc->left;
                root->key = suc->key;
                root->cnt = suc->cnt;
                suc->cnt = 1;
                root->right = remove(root->right, suc->key);
            }
        }
    }
    update(root);
    return balance(root);
}

// preorder checksum: visit each node exactly once (node-based)
ull checksum = 0;
unsigned int idx_global = 1;
void preorder(Node* root){
    if(!root) return;
    // use llabs for safety on INT_MIN
    checksum += (ull)( (ull)idx_global ^ (ull) llabs((long long)root->key) );
    idx_global++;
    preorder(root->left);
    preorder(root->right);
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    if(!(cin >> n)) return 0;
    Node* root = nullptr;
    while(n--){
        int op, x;
        cin >> op >> x;
        if(op == 1){
            root = insert(root, x);
        } else if(op == 2){
            root = remove(root, x);
        } else if(op == 3){
            int res = countSmaller(root, x) + 1;
            cout << res << '\n';
        } else if(op == 4){
            Node* ans = kth(root, x);
            if(ans) cout << ans->key << '\n';
        } else if(op == 5){
            Node* ans = predecessor(root, x);
            if(ans) cout << ans->key << '\n';
        } else if(op == 6){
            Node* ans = successor(root, x);
            if(ans) cout << ans->key << '\n';
        }
    }
    preorder(root);
    const ull MOD = (1ULL << 32);
    checksum %= MOD;
    cout << checksum << '\n';
    return 0;
}
