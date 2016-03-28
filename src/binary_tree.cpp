#include "binary_tree.h"

// Creates an empty binary tree
binary_tree::binary_tree(){
    this->tree = new node;
}

// Creates a binary tree with an initial value to store
binary_tree::binary_tree(int value){
    this->tree = new node;
    this->tree->data=value;
}

// Creates a binary tree from a collection of existing values
binary_tree::binary_tree(const std::vector<int> &values){
    this->tree = new node;
    
    for(int i = 0;i<values.size();i++){
        this->insert(values[i]);
    }
}

void deep_copy_worker(node * old_tree, node * new_tree,int value){
    
}
// Creates a binary tree by copying an existing tree
binary_tree::binary_tree(const binary_tree &rhs){
    this->tree = new node;
    if(rhs->tree->data){
        deep_copy_worker(rhs->tree,this->tree,rhs->tree->data);
    }else{
        std::cout << "No data at the root of the tree, means empty tree" << std::endl;
    }
}

// Destroys (cleans up) the tree
binary_tree::~binary_tree(){
    
}

// Recursion function to insert value
void insert_worker(node *tree, int value){
    // if the tree is empty, just insert the value in this node
    if(tree == nullptr){
        tree = new node;
    }    
    if(!tree->data){
        tree->data = value;
    }else if(value < tree->data){
        if(tree->left == nullptr){
            tree->left = new node;
        }
        insert_worker(tree->left, value);
        
    }else if(value > tree->data){
        if(tree->right == nullptr){
            tree->right = new node;
        }
        insert_worker(tree->right,value);
    }
    
}
// Adds a value to the tree
void binary_tree::insert(int value){
    // leave all the work to the worker that can work recursively
    insert_worker(this->tree,value);
}
// Removes a value from the tree
void binary_tree::remove(int value){
    if(this->tree->left == nullptr && this->tree->right == nullptr){
        delete this->tree;
    }
}

// Checks if a value is in the tree
bool binary_tree::exists(int value) const{
    return true;
}

// Prints the tree to standard out in numerical order
// Takes in the root of a tree so we can make it recursive
std::string inorder_worker(node *tree){
    // Check if the passed in node is a valid tree
    if(tree != nullptr){
        
        std::string text = "";
        
        if(tree->left != nullptr){
            #ifdef DEBUG
            // cout << "INORDER WORKER LEFT: " << text << endl;
            #endif
            text+= inorder_worker(tree->left);
            text+= " ";
        }
        if(tree->data){
            #ifdef DEBUG
            // cout << "INORDER WORKER DATA: " << text << endl;
            #endif
            text += std::to_string(tree->data);
        }
        
        if(tree->right != nullptr){
            #ifdef DEBUG
            // cout << "INORDER WORKER RIGHT: " << text << endl;
            #endif
            text+= " ";
            text+= inorder_worker(tree->right);
        }
        return text;
    }else{
        return std::string("");
    }
}

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
    return std::string("");
}

// Copy assignment operator
binary_tree& binary_tree::operator=(const binary_tree &other){
    // return binary_tree();
}

// Checks if two trees are equal
bool binary_tree::operator==(const binary_tree &other) const
{
    return true;
}

// Checks if two trees are not equal
bool binary_tree::operator!=(const binary_tree &other) const
{
    return true;
}

// Inserts a new value into the binary tree
binary_tree& binary_tree::operator+(int value){
    // return binary_tree();
}

// Removes a value from the binary tree
binary_tree& binary_tree::operator-(int value){
    // return binary_tree();
}

// Reads in values from an input stream into the tree
std::istream& operator>>(std::istream &in, binary_tree &value){
    return in;
}

// Writes the values, in-order, to an output stream
std::ostream& operator<<(std::ostream &out, const binary_tree &value){
    return out;
}