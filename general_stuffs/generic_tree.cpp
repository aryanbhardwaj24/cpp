#include <bits/stdc++.h>
using namespace std;

class generic_tree;

class TreeNode {
    private:
        int val;
        vector<TreeNode*> children;
    public:
        TreeNode () : val(0) {}
        TreeNode (int val) : val(val) {}

        ~TreeNode () {
            for(auto &i:this->children) delete i;
        }

        friend class generic_tree;
};

class generic_tree {
    private:
        TreeNode* root;

        TreeNode* take_input_recursively() {
            int data;
            cin>>data;
            TreeNode* r = new TreeNode(data);

            int num_children;
            cin>>num_children;

            for(int i=0;i<num_children;i++) {
                TreeNode* child = this->take_input_recursively();
                r->children.push_back(child);
            }

            return r;
        }

        TreeNode* take_input_levelwise () {
            int root_data;
            cout<<"Enter root data: ";
            cin>>root_data;

            TreeNode* r = new TreeNode(root_data);

            queue<TreeNode*> q;
            q.push(r);

            while(!q.empty()) {
                auto var = q.front();
                q.pop();

                int num_children;
                cout<<"Enter the number of children of "<<var->val<<" : ";
                cin>>num_children;

                for(int i=0;i<num_children;i++) {
                    int child_data;
                    cout<<"Enter the data of children "<<i+1<<" of "<<var->val<<" : ";
                    cin>>child_data;

                    TreeNode* child = new TreeNode(child_data);
                    q.push(child);
                    var->children.push_back(child);
                }
            }
            return r;
        }

        void print_recursively(TreeNode* root) {
            cout<<root->val<<" : ";
            for(auto &i:root->children) cout<<i->val<<" ";
            cout<<endl;

            for(auto &i:root->children) print_recursively(i);
        }

        void print_levelwise(TreeNode* root) {
            queue<TreeNode*> q;
            q.push(root);

            while(!q.empty()) {
                auto var = q.front();
                q.pop();

                cout<<var->val<<" ";
                for(auto &i:var->children) q.push(i);
            }
            cout<<endl;
        }

        void print_levelwise_modified(TreeNode* root) {
            queue<TreeNode*> q;
            q.push(root);

            while(!q.empty()) {
                auto var = q.front();
                q.pop();

                cout<<var->val<<" : ";
                for(auto &i:var->children) {
                    cout<<i->val<<" ";
                    q.push(i);
                }
                cout<<endl;
            }
        }

        int count_nodes_helper(TreeNode* root) {
            int ans = 1;
            for(auto &i:root->children) ans += count_nodes_helper(i);
            return ans;
        }

        int height_helper(TreeNode* root) {
            int ans=0;
            for(auto &i:root->children) ans = max(ans,height_helper(i));
            return 1+ans;
        }

        vector<TreeNode*> print_nodes_at_level_K_helper(TreeNode* root,int k) {
            vector<TreeNode*> ans;
            queue<TreeNode*> q;
            q.push(root);
            q.push(NULL);

            while(!q.empty() && k>=0) {
                auto var = q.front();
                q.pop();

                if(!var) {
                    k--;
                    if(!q.empty()) q.push(NULL);
                }
                else {
                    if(k==0) ans.push_back(var);
                    for(auto &i:var->children) q.push(i);
                }
            }
            return ans;
        }

        int count_leaf_nodes_helper(TreeNode* root) {
            if(root->children.size()==0) return 1;
            int ans = 0;
            for(auto &i:root->children) ans += count_leaf_nodes_helper(i);
            return ans;
        }

        void pre_order_traversal_helper(TreeNode* root, vector<TreeNode*> &ans) {
            ans.push_back(root);
            for(auto &i:root->children) pre_order_traversal_helper(i,ans);
        }

        void post_order_traversal_helper(TreeNode* root, vector<TreeNode*> &ans) {
            for(auto &i:root->children) post_order_traversal_helper(i,ans);
            ans.push_back(root);
        }

    public:
        generic_tree () {
            // this->root = this->take_input_recursively();
            this->root = this->take_input_levelwise();
        }

        void print_tree () {
            cout<<"Printing the tree recursively: "<<endl;
            print_recursively(this->root);

            cout<<"Printing the tree levelwise: "<<endl;
            print_levelwise(this->root);

            cout<<"Printing the tree levelwise (modified): "<<endl;
            print_levelwise_modified(this->root);
        }

        void count_nodes() {
            cout<<"Number of nodes: "<<count_nodes_helper(this->root)<<endl;
        }

        void height() {
            cout<<"Height of tree: "<<height_helper(this->root)<<endl;
        }

        void print_nodes_at_level_K(int k) {
            auto var = print_nodes_at_level_K_helper(this->root,k);
            cout<<"Nodes of the tree at level "<<k<<" : ";
            for(auto &i:var) cout<<i->val<<" ";
            cout<<endl;
        }

        void count_leaf_nodes() {
            cout<<"Number of leaf nodes: "<<count_leaf_nodes_helper(this->root)<<endl;
        }

        void pre_order_traversal() {
            cout<<"Pre-order traversal: ";
            vector<TreeNode*> ans;
            pre_order_traversal_helper(this->root,ans);
            for(auto &i:ans) cout<<i->val<<" ";
            cout<<endl;
        }

        void post_order_traversal() {
            cout<<"Post-order traversal: ";
            vector<TreeNode*> ans;
            post_order_traversal_helper(this->root,ans);
            for(auto &i:ans) cout<<i->val<<" ";
            cout<<endl;
        }

        ~generic_tree() {
            delete this->root;
        }
};

int main () {
    generic_tree t;
    t.print_tree();
    t.count_nodes();
    t.height();
    t.print_nodes_at_level_K(2);
    t.count_leaf_nodes();
    t.pre_order_traversal();
    t.post_order_traversal();
    return 0;
}

/*
                                Time Complexity         Space Complexity
print_recursively                   O(n)                      O(n) //Recursive stack space
print_levelwise                     O(n)                      O(n)
print_levelwise_modified            O(n)                      O(n)
count_nodes                         O(n)                      O(n) //Recursive stack space
height                              O(n)                      O(n) //Recursive stack space
print_nodes_at_level_K              O(k)                      O(k)
count_leaf_nodes                    O(n)                      O(n) //Recursive stack space
pre_order_traversal                 O(n)                      O(n) //Recursive stack space
post_order_traversal                O(n)                      O(n) //Recursive stack space
*/