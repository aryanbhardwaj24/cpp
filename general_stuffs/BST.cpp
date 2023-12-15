#include <bits/stdc++.h>
using namespace std;

class BST;

class TreeNode {
    private:
        int val;
        TreeNode* left;
        TreeNode* right;
    public:
        TreeNode() : val(0), left(NULL), right(NULL) {}
        TreeNode(int val) : val(val), left(NULL), right(NULL) {}

        ~TreeNode() {
            delete this->left;
            delete this->right;
        }

        friend class BST;
};

class BST {
    private:
        TreeNode* root;

        void inorder_traversal(TreeNode *node) {
            if(!node) return;
            inorder_traversal(node->left);
            cout<<node->val<<" ";
            inorder_traversal(node->right);
        }

        void pre_order_traversal(TreeNode* node) {
            if(!node) return;
            cout<<node->val<<" ";
            pre_order_traversal(node->left);
            pre_order_traversal(node->right);
        }

        void post_order_traversal(TreeNode* node) {
            if(!node) return;
            post_order_traversal(node->left);
            post_order_traversal(node->right);
            cout<<node->val<<" ";
        }

        void level_order_traversal(TreeNode* node) {
            if(!node) return;

            queue<TreeNode*> q;
            q.push(node);

            while(!q.empty()) {
                auto var = q.front();
                q.pop();

                cout<<var->val<<" ";
                if(var->left) q.push(var->left);
                if(var->right) q.push(var->right);
            }
            cout<<endl;
        }

        void level_order_traversal_modified(TreeNode* node) {
            if(!node) return;

            queue<TreeNode*> q;
            q.push(node);
            q.push(NULL);

            while(!q.empty()) {
                auto var = q.front();
                q.pop();

                if(!var) {
                    cout<<endl;
                    if(!q.empty()) q.push(NULL);
                }
                else {
                    cout<<var->val<<" ";
                    if(var->left) q.push(var->left);
                    if(var->right) q.push(var->right);
                }
            }
        }

        TreeNode* insert_node_helper(TreeNode* node, int key) {
            if(!node) {
                TreeNode* r = new TreeNode(key);
                return r;
            }
            if(node->val<key) node->right = insert_node_helper(node->right,key);
            else node->left = insert_node_helper(node->left,key);
            return node;
        }

        TreeNode* delete_node_helper(TreeNode* node, int key) {
            if(!node) return NULL;
            if(node->val==key) {
                if(!node->left && !node->right) {
                    delete node;
                    return NULL;
                }
                else if(node->left && !node->right) {
                    TreeNode* temp = node->left;
                    node->left = NULL;
                    delete node;
                    return temp;
                }
                else if(!node->left && node->right) {
                    TreeNode* temp = node->right;
                    node->right = NULL;
                    delete node;
                    return temp;
                }
                else {
                    int var = min_value_helper(node->right);
                    node->val = var;
                    node->right = delete_node_helper(node->right,var);
                    return node;
                }
            }
            else if(node->val<key) {
                node->right = delete_node_helper(node->right,key);
                return node;
            }
            else {
                node->left = delete_node_helper(node->left,key);
                return node;
            }
        }

        int max_value_helper(TreeNode* node) {
            TreeNode* curr = node;
            while(curr->right) curr = curr->right;
            return curr->val;
        }

        int min_value_helper(TreeNode* node) {
            TreeNode* curr = node;
            while(curr->left) curr = curr->left;
            return curr->val;
        }

    public:
        BST() : root(NULL) {}
        
        void print_tree() {
            cout<<"Inorder traversal: ";
            inorder_traversal(this->root);
            cout<<endl;

            cout<<"Pre-order traversal: ";
            pre_order_traversal(this->root);
            cout<<endl;

            cout<<"Post-order traversal: ";
            post_order_traversal(this->root);
            cout<<endl;

            cout<<"Level order traversal: ";
            level_order_traversal(this->root);

            cout<<"Level order traversal modified: "<<endl;
            level_order_traversal_modified(this->root);
        }

        void insert_node(int key) {
            this->root = insert_node_helper(this->root,key);
        }

        void delete_node(int key) {
            this->root = delete_node_helper(this->root,key);
        }

        void max_value() {
            cout<<"Maximum value: "<<max_value_helper(this->root)<<endl;
        }

        void min_value() {
            cout<<"Minimum value: "<<min_value_helper(this->root)<<endl;
        }

        ~BST() {
            delete this->root;
        }
};

int main () {
    BST t;
    t.insert_node(10);
    t.insert_node(5);
    t.insert_node(20);
    t.insert_node(7);
    t.insert_node(3);
    t.insert_node(15);
    t.print_tree();
    t.max_value();
    t.min_value();

    t.delete_node(10);
    t.print_tree();
    t.max_value();
    t.min_value();
    return 0;
}

/*
                                Time Complexity        Space Complexity
inorder_traversal                   O(n)                    O(n) //Recursive stack space
pre_order_traversal                 O(n)                    O(n) //Recursive stack space
post_order_traversal                O(n)                    O(n) //Recursive stack space
level_order_traversal               O(n)                    O(n)
level_order_traversal_modified      O(n)                    O(n)
insert_node                         O(h)                    O(h)
                                        -Here, 'h' denotes the height of BST
                                        -Also, 
                                            -In case of balanced BSTs (|(left_subtree_height)-(right_subtree_height)|<=1): h~O(logn)
                                            -Worst case scenario (case of skewed tree): h~O(n)
delete_node                         O(h)                    O(h)
                                        -Here, 'h' denotes the height of BST
                                        -Also, 
                                            -In case of balanced BSTs (|(left_subtree_height)-(right_subtree_height)|<=1): h~O(logn)
                                            -Worst case scenario (case of skewed tree): h~O(n)           
*/