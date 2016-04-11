#include "binary_tree.h"
#include <sstream>
#include <typeinfo>

// Worker functions
// Recursion function to insert value
node* insert_worker(node *parent_node,node *tree, int value){
    // if the passed in parent node is null, it means the tree is the root.
    if(parent_node == nullptr){    
        parent_node = tree;
    }
    // if the tree is empty, just insert the value in this node
    if(tree == nullptr){
        tree = new node;
        tree->data = value;
        // tree->parent = parent_node;
    }else if(value < tree->data){
        tree->left = insert_worker(tree,tree->left, value);
    }else if(value > tree->data){
        tree->right = insert_worker(tree,tree->right, value);
    }
    return tree;
}

std::string inorder_worker(node *tree){
    // Check if the passed in node is a valid tree
    if(tree != nullptr){
        if(tree->left != nullptr && tree->right != nullptr){
            return inorder_worker(tree->left)+" "+std::to_string(tree->data)+" "+inorder_worker(tree->right);
        }else if(tree->right == nullptr && tree->left != nullptr){
            return inorder_worker(tree->left)+" "+std::to_string(tree->data);
        }else if(tree->left == nullptr && tree->right != nullptr){
            return std::to_string(tree->data)+" "+inorder_worker(tree->right);
        }else if(tree->left == nullptr && tree->right == nullptr){
            return std::to_string(tree->data);
        }
    }else{
        return "";
    }
}

std::string postorder_worker(node *tree){
    // Check if the passed in node is a valid tree
    if(tree != nullptr){
        if(tree->left != nullptr && tree->right != nullptr){
            return std::to_string(tree->data)+" "+inorder_worker(tree->left)+" "+inorder_worker(tree->right);
        }else if(tree->right == nullptr && tree->left != nullptr){
            return std::to_string(tree->data)+" "+inorder_worker(tree->left);
        }else if(tree->left == nullptr && tree->right != nullptr){
            return std::to_string(tree->data)+" "+inorder_worker(tree->right);
        }else if(tree->left == nullptr && tree->right == nullptr){
            return std::to_string(tree->data);
        }
    }else{
        return "";
    }
}

// Return node and assign
node * deep_copy_worker(node* new_tree,node* old_tree){
    if(new_tree == nullptr){
        new_tree = new node;
    }
    // Check if the passed in node is a valid tree
    if(old_tree != nullptr){
        new_tree->data = old_tree->data;
        new_tree->left = deep_copy_worker(new_tree->left,old_tree->left);
        new_tree->right = deep_copy_worker(new_tree->right,old_tree->right);
        return new_tree;
    }else{
        return nullptr;
    }
            
}

// Find a node in the tree that holds a specified value
node* findNode(node* tree, int value){
    if(tree == nullptr){
        return nullptr;
    }else if(value == tree->data){
        return tree;
    }else if(value > tree->data){
        return findNode(tree->right,value);
    }else if(value < tree->data){
        return findNode(tree->left,value);
    }else{
        return nullptr;
    }
}

//Finds the smallest value in the right subtree
int smallest_right_val(node *root){
	if (root->left != nullptr) {
        return smallest_right_val(root->left);
    }else {
        return root->data;
    }
}

void destroyer(node *root){
	if (root != nullptr && typeid(root) == typeid(node*)){
		if(root->left != nullptr){
            destroyer(root->left);
        }
		if(root->right != nullptr){
            destroyer(root->right);
        }
		delete root;
	}
}

node * remove_worker(node *tree, node *parent, int value){
    if(tree != nullptr){
        // proceed to deletion if the node is found
        if(tree->data == value){

            node *temp = tree;
            int smallestDataRight;

            if (tree->left == nullptr && tree->right == nullptr){
                tree = nullptr;
                if(tree == parent){
                    parent = nullptr;
                }
                delete temp;

            }else if (tree->left == nullptr && tree->right != nullptr){
                parent->right = tree->right;
                temp->right = nullptr;
                delete temp;

            }else if (tree->left != nullptr && tree->right == nullptr){
                parent->left = tree->left;
                temp->left = nullptr;
                delete temp;

            }else{
                smallestDataRight = smallest_right_val(tree->right);
                tree = remove_worker(tree,parent,smallestDataRight);
                tree->data = smallestDataRight;
            }

        }else{
            if(tree->data > value){
                parent->left = remove_worker(tree->left,tree,value);
            }else{
                parent->right = remove_worker(tree->right,tree,value);
            }
        }
    }
    // Deleting temp also deletes tree, so return parent.
    // Doesn't affect since on the first call, parent==tree
    return parent;
}

// Creates an empty binary tree
binary_tree::binary_tree(){
    this->tree = nullptr;
}

// Creates a binary tree with an initial value to store
binary_tree::binary_tree(int value){
    this->tree = new node;
    this->tree->data=value;
}

// Creates a binary tree from a collection of existing values
binary_tree::binary_tree(const std::vector<int> &values){
    this->tree = nullptr;
    for(auto &v : values){
        this->insert(v);
    }
}
// Creates a binary tree by copying an existing tree
binary_tree::binary_tree(const binary_tree &rhs){
    this->tree = deep_copy_worker(this->tree,rhs.tree);
}

// Destroys (cleans up) the tree
binary_tree::~binary_tree(){
    destroyer(this->tree);
    this->tree = nullptr;
    
}
// Adds a value to the tree
void binary_tree::insert(int value){
    // leave all the work to the worker that can work recursively
    if(!this->exists(value)){
        this->tree = insert_worker(this->tree,this->tree,value);
    }
}

// Removes a value from the tree
void binary_tree::remove(int value){
    if(this->exists(value)){
        this->tree = remove_worker(this->tree,this->tree,value);
    }
}

// Checks if a value is in the tree
bool binary_tree::exists(int value) const{
    return findNode(this->tree,value) != nullptr;
}

// Returns a string representation of the tree to in numerical order
// Takes in the root of a tree so we can make it recursive

// Handler to make it recursive
std::string binary_tree::inorder() const{
    return inorder_worker(this->tree);
}

// Prints the tree in pre-order
std::string binary_tree::preorder() const{
    return std::string("");
}

// Prints the tree in post-order
std::string binary_tree::postorder() const{
    return postorder_worker(this->tree);
}

// Copy assignment operator
binary_tree& binary_tree::operator=(const binary_tree &other){
    if(this->tree == nullptr){
        this->tree = new node;
    }
    deep_copy_worker(other.tree,this->tree);
    return *this;
}

// Checks if two trees are equal
bool binary_tree::operator==(const binary_tree &other) const{
    return (this->inorder() == other.inorder());
}

// Checks if two trees are not equal
bool binary_tree::operator!=(const binary_tree &other) const{
    return (this->inorder() != other.inorder());
}

// Inserts a new value into the binary tree
binary_tree& binary_tree::operator+(int value){
    this->insert(value);
    return *this;
}

// Removes a value from the binary tree
binary_tree& binary_tree::operator-(int value){
    this->remove(value);
    return *this;
}

// Reads in values from an input stream into the tree
std::istream& operator>>(std::istream &in, binary_tree &value){
    return in;
}

// Writes the values, in-order, to an output stream
std::ostream& operator<<(std::ostream &out, const binary_tree &value){
    return out;
}