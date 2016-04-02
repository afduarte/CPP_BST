#include "binary_tree.h"
#include <sstream>

// Worker functions
// Recursion function to insert value
node* insert_worker(node *parent_node,node *tree, int value){
    // if the tree is empty, just insert the value in this node
    if(tree == nullptr){
        tree = new node;
        tree->data = value;
        tree->parent = parent_node;
    }else if(value < tree->data){
        tree->left = insert_worker(parent_node,tree->left, value);
    }else if(value > tree->data){
        tree->right = insert_worker(parent_node,tree->right, value);
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

void deep_copy_worker(node* new_tree,node* old_tree){
    std::stringstream stream(inorder_worker(old_tree));
    int n;
    while(stream >> n){
        new_tree = insert_worker(new_tree,new_tree,n);
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

// Finds the node that is the parent of a node that holds a specified value
// node* findParentNode(node* tree, int value){
//     if(tree == nullptr){
//         return nullptr;
//     }else if(value == tree->left->data || value == tree->right->data || value == tree->data){
//         return tree;
//     }else if(value > tree->data){
//         return findParentNode(tree->right,value);
//     }else if(value < tree->data){
//         return findParentNode(tree->left,value);
//     }else{
//         return nullptr;
//     }
// }

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
    std::stringstream stream(inorder_worker(rhs.tree));
    int n;
    this->tree = nullptr;
    while(stream >> n){
        this->insert(n);
    }
    // this->tree = nullptr;
    // deep_copy_worker(this->tree,rhs.tree);
}

// Destroys (cleans up) the tree
binary_tree::~binary_tree(){
    
}
// Adds a value to the tree
void binary_tree::insert(int value){
    // leave all the work to the worker that can work recursively
    this->tree = insert_worker(this->tree,this->tree,value);
}

void remove_worker(node *tree, int value){
// if toRemove and parentNode are the same address, means the node is the root of the tree, just delete it
// if it's a single child, delete the node and the link on the parent
    node *toRemove = findNode(tree,value);
    if(toRemove != nullptr){
        node *parent = toRemove->parent;
        if(toRemove->left == nullptr && toRemove->right == nullptr){
            if(toRemove == parent->left){
                std::cout << "Is left" << std::endl;
                toRemove->parent->left = nullptr;
            }else if(toRemove == toRemove->parent->right){
                std::cout << "Is right" << std::endl;
                parent->right = nullptr;
            }
        }
        delete parent;
        delete toRemove;
    }
    
}

// Removes a value from the tree
void binary_tree::remove(int value){
    remove_worker(this->tree,value);
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
    return std::string("");
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