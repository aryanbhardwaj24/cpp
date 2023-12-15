#include <bits/stdc++.h>
using namespace std;

class binary_tree;

class TreeNode {
    private:
        int val;
        TreeNode* left;
        TreeNode* right;
    public:
        TreeNode () : val(0), left(NULL), right(NULL) {}
        TreeNode (int val) : val(val), left(NULL), right(NULL) {}

        ~TreeNode () {
            delete this->left;
            delete this->right;
        }

        friend class binary_tree;
};

class binary_tree {
    private:
        TreeNode* root;

        TreeNode* take_input_recursively() {
            int data;
            cin>>data;
            if(data==-1) return NULL;

            TreeNode* r = new TreeNode(data);
            r->left = this->take_input_recursively();
            r->right = this->take_input_recursively();
            return r;
        }

        TreeNode* take_input_levelwise() {
            int r_data;
            cout<<"Enter root val: ";
            cin>>r_data;
            if(r_data==-1) return NULL;

            TreeNode* r = new TreeNode(r_data);

            queue<TreeNode*> q;
            q.push(r);

            while(!q.empty()) {
                auto var = q.front();
                q.pop();

                int l_c_data;
                cout<<"Enter the val of left child of "<<var->val<<" : ";
                cin>>l_c_data;
                if(l_c_data==-1) var->left = NULL;
                else {
                    TreeNode* l_c = new TreeNode(l_c_data);
                    q.push(l_c);
                    var->left = l_c;
                }

                int r_c_data;
                cout<<"Enter the val of right child of "<<var->val<<" : ";
                cin>>r_c_data;
                if(r_c_data==-1) var->right = NULL;
                else {
                    TreeNode* r_c = new TreeNode(r_c_data);
                    var->right = r_c;
                    q.push(r_c);
                }
            }
            return r;
        }

        void print_tree_recursively(TreeNode* root) {
            if(!root) return;
            cout<<root->val<<" : ";
            if(root->left) cout<<"L"<<root->left->val<<" ";
            if(root->right) cout<<"R"<<root->right->val<<" ";
            cout<<endl;

            print_tree_recursively(root->left);
            print_tree_recursively(root->right);
        }

        void print_tree_levelwise(TreeNode* root) {
            if(!root) return;

            queue<TreeNode*> q;
            q.push(root);

            while(!q.empty()) {
                auto var = q.front();
                q.pop();

                cout<<var->val<<" ";
                if(var->left) q.push(var->left);
                if(var->right) q.push(var->right);
            }
            cout<<endl;
        }

        void print_tree_levelwise_modified(TreeNode* root) {
            if(!root) return;

            queue<TreeNode*> q;
            q.push(root);
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

        void inorder_traversal_helper(TreeNode* root) {
            if(!root) return;
            inorder_traversal_helper(root->left);
            cout<<root->val<<" ";
            inorder_traversal_helper(root->right);
        }

        void pre_order_traversal_helper(TreeNode* root) {
            if(!root) return;
            cout<<root->val<<" ";
            pre_order_traversal_helper(root->left);
            pre_order_traversal_helper(root->right);
        }

        void post_order_traversal_helper(TreeNode* root) {
            if(!root) return;
            post_order_traversal_helper(root->left);
            post_order_traversal_helper(root->right);
            cout<<root->val<<" ";
        }

        int height_helper(TreeNode* root) {
            if(!root) return 0;
            return 1+max(height_helper(root->left),height_helper(root->right));
        }

        bool is_symmetric_helper(TreeNode* root1, TreeNode* root2) {
            if(!root1 && !root2) return true;
            if(!root1) return false;
            if(!root2) return false;
            return root1->val==root2->val && is_symmetric_helper(root1->left,root2->right) && is_symmetric_helper(root1->right,root2->left);
        }

        int count_leaf_nodes_helper(TreeNode* root) {
            if(!root) return 0;
            if(!root->left && !root->right) return 1;
            return count_leaf_nodes_helper(root->left)+count_leaf_nodes_helper(root->right);
        }

        int diameter_helper(TreeNode* root) {
            if(!root) return 0;
            return max(height_helper(root->left)+height_helper(root->right),max(diameter_helper(root->left),diameter_helper(root->right)));
        }

        pair<int,int> diameter_optimized_approach_helper(TreeNode* root) {
            if(!root) return {0,0};
            auto l = diameter_optimized_approach_helper(root->left);
            auto r = diameter_optimized_approach_helper(root->right);

            return {1+max(l.first,r.first),max(l.first+r.first,max(l.second,r.second))};
        }

    public:
        binary_tree() {
            // this->root = this->take_input_recursively();
            this->root = this->take_input_levelwise();
        }

        void print_tree() {
            cout<<"Printing the tree recursively: "<<endl;
            print_tree_recursively(this->root);

            cout<<"Printing the tree levelwise: "<<endl;
            print_tree_levelwise(this->root);

            cout<<"Printing the tree levelwise (modified): "<<endl;
            print_tree_levelwise_modified(this->root);
        }

        void inorder_traversal() {
            cout<<"Inorder traversal: ";
            inorder_traversal_helper(this->root);
            cout<<endl;
        }

        void pre_order_traversal() {
            cout<<"Pre-order traversal: ";
            pre_order_traversal_helper(this->root);
            cout<<endl;
        }

        void post_order_traversal() {
            cout<<"Post-order traversal: ";
            post_order_traversal_helper(this->root);
            cout<<endl;
        }

        void height() {
            cout<<"Height of binary tree: "<<height_helper(this->root)<<endl;
        }

        void is_symmetric() {
            if(is_symmetric_helper(root->left,root->right)) cout<<"Symmetric!"<<endl;
            else cout<<"Not symmetric!"<<endl;
        }

        void count_leaf_nodes() {
            cout<<"Number of leaf nodes: "<<count_leaf_nodes_helper(this->root)<<endl;
        }

        void diameter() {
            cout<<"Diameter of binary tree: "<<diameter_helper(this->root)<<endl;
        }

        void diameter_optimized_approach() {
            auto d = diameter_optimized_approach_helper(this->root);
            cout<<"Diameter of binary tree (optimized approach): "<<d.second<<endl;
        }
};

int main () {
    binary_tree t;
    t.print_tree();
    t.inorder_traversal();
    t.pre_order_traversal();
    t.post_order_traversal();
    t.height();
    t.is_symmetric();
    t.count_leaf_nodes();
    t.diameter();
    t.diameter_optimized_approach();
    return 0;
}

/*
                                Time Complexity        Space Complexity
print_tree_recursively              O(n)                    O(n) //Recursive stack space
print_tree_levelwise                O(n)                    O(n)
print_tree_levelwise_modified       O(n)                    O(n)
inorder_traversal                   O(n)                    O(n) //Recursive stack space
pre_order_traversal                 O(n)                    O(n) //Recursive stack space
post_order_traversal                O(n)                    O(n) //Recursive stack space
height                              O(n)                    O(n) //Recursive stack space
is_symmetric                        O(n)                    O(n) //Recursive stack space
count_leaf_nodes                    O(n)                    O(n) //Recursive stack space
diameter                            O(n*h)                  O(n) //Recursive stack space
                                    -here, 'h' is the height of the binary tree.
                                    -Also, 
                                        -for symmetric tree: h~O(logn)
                                        -worst case scenario (case of skewed tree): h~O(n)
diameter_optimized_approach         O(n)                    O(n) //Recursive stack space                                        
*/