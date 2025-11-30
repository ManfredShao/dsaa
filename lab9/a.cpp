#include <iostream>
#include <stack>
using namespace std;

struct TreeNode{
    int key;
    TreeNode* left;
    TreeNode* right;
    TreeNode* parent;
    TreeNode(int x) : key(x), left(nullptr), right(nullptr), parent(nullptr) {}
};

void insert(TreeNode* &root, int val){
    TreeNode* z = new TreeNode(val);
    TreeNode* x = root;
    TreeNode* y = nullptr;
    while(x != nullptr){
        y = x;
        if(val < x->key){
            x = x->left;
        }else{
            x = x->right;
        }
    }
    z->parent = y;
    if(y == nullptr){
        root = z;
    }else if(z->key < y->key){
        y->left = z;
    }else{
        y->right = z;
    }
}

TreeNode* search(TreeNode* root, int val){
    TreeNode* x = root;
    while(x != nullptr && x->key != val){
        if(val < x->key){
            x = x->left;
        }else{
            x = x->right;
        }
    }
    return x;
}

void remove(TreeNode* &root, int val){
    TreeNode* z = search(root, val);
    if(z == nullptr){
        return;
    }
    
    TreeNode* child = nullptr;
    if(z->left == nullptr){
        child = z->right;
    }else if(z->right == nullptr){
        child = z->left;
    }else{
        TreeNode* y = z->right;
        while(y->left != nullptr){
            y = y->left;
        }
        z->key = y->key;
        if(y->parent != z){
            if(y->right != nullptr){
                y->right->parent = y->parent;
            }
            y->parent->left = y->right;
        }else{
            if(y->right != nullptr){
                y->right->parent = z;
            }
            z->right = y->right;
        }
        delete y;
        return;
    }
    
    if(child != nullptr){
        child->parent = z->parent;
    }
    
    if(z->parent == nullptr){
        root = child;
    }else if(z == z->parent->left){
        z->parent->left = child;
    }else{
        z->parent->right = child;
    }
    
    delete z;
}

int countSmaller(TreeNode* root, int val){
    if(root == nullptr) return 0;
    if(root->key < val){
        return 1 + countSmaller(root->left, val) + countSmaller(root->right, val);
    }else{
        return countSmaller(root->left, val);
    }
}

TreeNode* successor(TreeNode* root,int val){
    TreeNode* x = root;
    TreeNode* succ = nullptr;
    while(x != nullptr){
        if(x->key > val){
            succ = x;
            x = x->left;
        }else{
            x = x->right;
        }
    }
    return succ;
}

TreeNode* predecessor(TreeNode* root,int val){
    TreeNode* x = root;
    TreeNode* pred = nullptr;
    while(x != nullptr){
        if(x->key < val){
            pred = x;
            x = x->right;
        }else{
            x = x->left;
        }
    }
    return pred;
}

TreeNode* Rank(TreeNode* root, int k){
    if(root == nullptr || k <= 0) return nullptr;
    
    stack<TreeNode*> st;
    TreeNode* curr = root;
    int count = 0;
    
    while(curr != nullptr || !st.empty()){
        while(curr != nullptr){
            st.push(curr);
            curr = curr->left;
        }
        curr = st.top();
        st.pop();
        count++;
        if(count == k){
            return curr;
        }
        curr = curr->right;
    }
    return nullptr;
}

int main(){
    int n;
    cin >> n;
    TreeNode* root = nullptr;
    while(n--){
        int a,b;
        cin >> a >> b;
        if(a == 1){
            insert(root, b);
        }
        else if(a == 2){
            remove(root, b);
        }
        else if(a == 3){
            int res =countSmaller(root,b) + 1;
            cout << res << endl;
        }
        else if(a == 4){
            TreeNode* res = Rank(root, b);
            cout << res->key << endl;
        }
        else if(a == 5){
            TreeNode* res = predecessor(root, b);
            if(res != nullptr) cout << res->key << endl;
        }
        else if(a == 6){
            TreeNode* res = successor(root, b);
            if(res != nullptr) cout << res->key << endl;
        }
    }
   return 0;
}