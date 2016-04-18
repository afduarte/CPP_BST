#include "binary_tree.h"
#include <sstream>
#include <typeinfo>
/**************************************
 *  Private Worker Functions
 **************************************/

// Recursive function to insert value
node* insert_worker(node *tree, int value){
    // if the tree is empty, just insert the value in the current node
    // All empty nodes are set to nullptr, so they must be initialized to a node type
    if(tree == nullptr){
        tree = new node;
        tree->data = value;
    // Else if the value is smaller than the current node, recurse into left branch
    }else if(value < tree->data){
        tree->left = insert_worker(tree->left, value);
    // Else if the value is larger than the current node, recurse into right branch
    }else if(value > tree->data){
        tree->right = insert_worker(tree->right, value);
    }
    //Return the tree that holds the newly inserted value
    return tree;
}

// Recursive function to print the tree in order
std::string inorder_worker(node *tree){
    // Check if the passed in node is a valid tree
    if(tree != nullptr){
        // if tree has left && right, call on left, to_string this and then call on right. Return the resulting string 
        if(tree->left != nullptr && tree->right != nullptr){
            return inorder_worker(tree->left)+" "+std::to_string(tree->data)+" "+inorder_worker(tree->right);
        // if tree has only left, call on left and to_string this. Return the resulting string    
        }else if(tree->right == nullptr && tree->left != nullptr){
            return inorder_worker(tree->left)+" "+std::to_string(tree->data);
        // if tree has only right, to_string this and call on right. Return the resulting string
        }else if(tree->left == nullptr && tree->right != nullptr){
            return std::to_string(tree->data)+" "+inorder_worker(tree->right);
        // if tree has no left or right, just return this as a string
        }else if(tree->left == nullptr && tree->right == nullptr){
            return std::to_string(tree->data);
        }
    // in case the node is null, return an empty string    
    }else{
        return "";
    }
}

// Recursive function to print the tree in pre order (data=>left=>right)
std::string preorder_worker(node *tree){
    if(tree != nullptr){
        if(tree->left != nullptr && tree->right != nullptr){
            return std::to_string(tree->data)+" "+preorder_worker(tree->left)+" "+preorder_worker(tree->right);
        }else if(tree->right == nullptr && tree->left != nullptr){
            return std::to_string(tree->data)+" "+preorder_worker(tree->left);
        }else if(tree->left == nullptr && tree->right != nullptr){
            return std::to_string(tree->data)+" "+preorder_worker(tree->right);
        }else if(tree->left == nullptr && tree->right == nullptr){
            return std::to_string(tree->data);
        }
    }else{
        return "";
    }
}

// Recursive function to print the tree in post order (left=>right=>data)
std::string postorder_worker(node *tree){
    if(tree != nullptr){
        if(tree->left != nullptr && tree->right != nullptr){
            return postorder_worker(tree->left)+" "+postorder_worker(tree->right)+" "+std::to_string(tree->data);
        }else if(tree->right == nullptr && tree->left != nullptr){
            return postorder_worker(tree->left)+" "+std::to_string(tree->data);
        }else if(tree->left == nullptr && tree->right != nullptr){
            return postorder_worker(tree->right)+" "+std::to_string(tree->data);
        }else if(tree->left == nullptr && tree->right == nullptr){
            return std::to_string(tree->data);
        }
    }else{
        return "";
    }
}

// Recursive function to deep-copy the tree into a new tree
node * deep_copy_worker(node* source,node* destination){
    // Check if the source node is a valid tree
    if(source != nullptr){
        // if the destination is null, assign it to a new node
        if (destination == nullptr){
            destination = new node;
        }
        //copy data in this node
        destination->data = source->data;
        // Recurse into the left
        destination->left = deep_copy_worker(source->left,destination->left);
        // Recurse into the right
        destination->right = deep_copy_worker(source->right,destination->right);
        // Return the resulting tree
        return destination;
    // if the source node is null, return null
    }else{
        return nullptr;
    }
            
}

// Find a node in the tree that holds a specified value
node* findNode(node* tree, int value){
    // If the tree is null, just return null
    if(tree == nullptr){
        return nullptr;
    // if the value we're looking for is in this node, return this node
    }else if(value == tree->data){
        return tree;
    // If the value is greater than the one on this node, recurse into the right
    }else if(value > tree->data){
        return findNode(tree->right,value);
    // If the value is smaller than the one on this node, recurse into the left
    }else if(value < tree->data){
        return findNode(tree->left,value);
    // Something has gone terribly wrong
    }else{
        return nullptr;
    }
}

//Finds the smallest value in the right subtree
int smallest_right_val(node *root){
    //If there is a value to the left, recurse into it
	if(root->left != nullptr) {
        return smallest_right_val(root->left);
    // else, return this value
    }else{
        return root->data;
    }
}

// Destroy a tree
// Recursively delete every node in the tree
void destroyer(node *root){
    // if the root is a valid tree
	if (root != nullptr){
            // If there is a left, recurse into it
		if(root->left != nullptr){
            destroyer(root->left);
        }
            // If there is a right, recurse into it
		if(root->right != nullptr){
            destroyer(root->right);
        }
            // Delete this node
		delete root;
	}
}

void binary_tree::remove_worker(node *local_tree, node *parent, int value){
    if(local_tree != nullptr){
        // proceed to deletion if the node is found
        if(local_tree->data == value){
            node *temp = local_tree;
            // No children
            if (local_tree->left == nullptr && local_tree->right == nullptr){
                if(parent != nullptr){
                    if(parent->left != nullptr && value == parent->left->data){
                        // if tree is left child of parent, make parent->left null
                        parent->left = nullptr;
                        delete temp;
                    }else{
                        // if tree is right child of parent, make parent->right null
                        parent->right = nullptr;
                        delete temp;
                    }
                }else{
                    // if tree has no parent, delete and set tree to null
                    delete this->tree;
                    this->tree = nullptr;
                    delete temp;
                }
            // Single child to the right
            }else if (local_tree->left == nullptr && local_tree->right != nullptr){
                if(parent != nullptr) {
                    // if tree is left child of parent, parent->left becomes tree->right
                    if(parent->left != nullptr && value == parent->left->data){
                        parent->left = local_tree->right;
                    // if tree is right child of parent, parent->right becomes tree->right
                    }else{
                        parent->right = local_tree->right;
                    }
                // if tree has no parent, set tree to its right child
                }else{
                    this->tree = temp->right;
                    temp->right = nullptr;
                }
                delete temp;
                temp = nullptr;

            // Single child to the left
            }else if (local_tree->left != nullptr && local_tree->right == nullptr){
                if(parent != nullptr) {
                    // Value is on the left of the parent
                    if(parent->left != nullptr && value == parent->left->data){
                        parent->left = local_tree->left;
                        //Value is on the right of the parent
                    }else{
                        parent->right = local_tree->left;
                    }
                    local_tree = nullptr;
                // if tree has no parent, set tree to its left child
                }else{
                    this->tree = temp->left;
                    temp->left = nullptr;
                }
                delete temp;
                temp = nullptr;

            // Children to the left and to the right
            }else{
                // find the smallest value on right subtree
                int small_val_right = smallest_right_val(local_tree->right);
                // Remove it from the tree (will happen again if that node has both children)
                remove_worker(local_tree,parent,small_val_right);
                // Assign the value in this node to the value of the removed node
                local_tree->data = small_val_right;
            }
        // This is not the node you're looking for
        }else{
            // if the value we want to remove is smaller, recurse into the left
            if(local_tree->data > value){
                remove_worker(local_tree->left,local_tree,value);
            // if the value we want to remove is smaller, recurse into the left
            }else{
                remove_worker(local_tree->right,local_tree,value);
            }
        }
    }
}


/**************************************
 *  Constructors
 **************************************/

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
    this->tree = deep_copy_worker(rhs.tree,this->tree);
}

// Destroys (cleans up) the tree
binary_tree::~binary_tree(){
    destroyer(this->tree);
    this->tree = nullptr;
    
}

/**************************************
 *  Member Methods
 **************************************/
 
// Adds a value to the tree
void binary_tree::insert(int value){
    // leave all the work to the worker that can work recursively
    if(!this->exists(value)){
        this->tree = insert_worker(this->tree,value);
    }
}

// Removes a value from the tree
void binary_tree::remove(int value){
    // if it exists, proceed to removal with the recursive handler
    if(this->exists(value)){
        remove_worker(this->tree,nullptr,value);
    }
}

// Checks if a value is in the tree
bool binary_tree::exists(int value) const{
    // check if the node returned from the findNode function is different than null
    return findNode(this->tree,value) != nullptr;
}

// The following methods return a string representation of the tree to in numerical order
std::string binary_tree::inorder() const{
    return inorder_worker(this->tree);
}

// Prints the tree in pre-order
std::string binary_tree::preorder() const{
    return preorder_worker(this->tree);
}

// Prints the tree in post-order
std::string binary_tree::postorder() const{
    return postorder_worker(this->tree);
}

/**************************************
 *  Operator Overloads
 **************************************/

// Copy assignment operator
binary_tree& binary_tree::operator=(const binary_tree &other){
    // just call the copy method with source other and destination this->tree
    this->tree = deep_copy_worker(other.tree,this->tree);
    // return pointer to this as required by an operator overload
    return *this;
}

// Checks if two trees are equal
bool binary_tree::operator==(const binary_tree &other) const{
    // check if the string representation of both trees is equal and return the reult of the comparison
    return (this->inorder() == other.inorder());
}

// Checks if two trees are not equal
bool binary_tree::operator!=(const binary_tree &other) const{
        // check if the string representation of both trees is not equal and return the reult of the comparison
    return (this->inorder() != other.inorder());
}

// Inserts a new value into the binary tree
binary_tree& binary_tree::operator+(int value){
    this->insert(value);
    // return pointer to this as required by an operator overload
    return *this;
}

// Removes a value from the binary tree
binary_tree& binary_tree::operator-(int value){
    this->remove(value);
    // return pointer to this as required by an operator overload
    return *this;
}

// Reads in values from an input stream into the tree
std::istream& operator>>(std::istream &in, binary_tree &value){
    int n;
    // while there are int values in the input stream, insert them in the tree
    while( in >> n ) {
        value.insert(n);
    }
    return in;
}

// Writes the values, in-order, to an output stream
std::ostream& operator<<(std::ostream &out, const binary_tree &value){
    // just call the inorder method and return that to the output stream
    if (value.tree != nullptr)
        out << value.inorder();
    return out;
}