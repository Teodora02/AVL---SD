#include <iostream>
using namespace std;

struct Node
{
    int key; 
    Node *left; 
    Node *right;
    int height; 
};

// Calculate height
int height(Node *N)  
{
    if (N == NULL) 
        return 0;
    return N->height;
}



Node *newNode(int key)
{
    Node *node = new Node(); 
    node->key = key; 
    node->left = NULL; 
    node->right = NULL;
    node->height = 1; 
    return (node);
}


Node *rightRotate(Node *y) 
{
    Node *x = y->left; 
    Node *T2 = x->right; 
    
    x->right = y; 
    y->left = T2; 
    y->height = max(height(y->left),
                    height(y->right)) +1;
    x->height = max(height(x->left),
                    height(x->right)) +1; 
    return x;
}


Node *leftRotate(Node *x)    
{
    Node *y = x->right; 
    Node *T2 = y->left; 
    y->left = x;  
    x->right = T2; 
    x->height = max(height(x->left),
                    height(x->right)) + 1;
    y->height = max(height(y->left),
                    height(y->right)) +1;
    return y;
}

int getBalanceFactor(Node *N)
{
    if (N == NULL)
        return 0; 
    return height(N->left) -
           height(N->right);
}

//INSERT
Node *insertNode(Node *node, int key)  
{
    if (node == NULL)  
        return (newNode(key));
    if (key < node->key) 
        node->left = insertNode(node->left, key);
    else if (key > node->key) 
        node->right = insertNode(node->right, key);
    else
        return node;  

//echilibram inaltimile
    node->height = 1 + max(height(node->left),
                           height(node->right)); 
    int balanceFactor = getBalanceFactor(node); 
   

    if (balanceFactor > 1)   
    {
        if (key < node->left->key)   
        {
            return rightRotate(node); /
        }
        else if (key > node->left->key)
        {
            node->left = leftRotate(node->left); 
            return rightRotate(node); 
        }
    }

    if (balanceFactor < -1)  
    {
      
        if (key > node->right->key)  
        {
            return leftRotate(node); 
        }
        else if (key < node->right->key)
        {
            node->right = rightRotate(node->right); 
            return leftRotate(node); 
        }
    }
    return node;
}

// Caut nodul cu valoarea minima, imi va trebui la delete, nodul cu valoarea minima este cel mai din stanga
Node *nodeWithMimumValue(Node *node)
{
    Node *current = node;
    while (current->left != NULL) 
        current = current->left; 
    return current; 
}

Node *deleteNode(Node *root, int key)   
{
    if (root == NULL) 
        return root; 
    if (key < root->key) 
        root->left = deleteNode(root->left, key); 
    else if (key > root->key) 
        root->right = deleteNode(root->right, key); 
    else 
    {
        if ((root->left == NULL) ||  
                (root->right == NULL))  
        {
            Node *temp = root->left ? root->left : root->right; 
            if (temp == NULL)  
            {
                temp = root; 
                root = NULL; 
            }
            else
                *root = *temp; 
        }

     
        else
        {
            Node *temp = nodeWithMimumValue(root->right); 
            root->key = temp->key; 
            root->right = deleteNode(root->right,
                                     temp->key); 
        }
    }

    if (root == NULL)
        return root; 
    root->height = 1 + max(height(root->left),
                           height(root->right));

    int balanceFactor = getBalanceFactor(root); 
    if (balanceFactor > 1) 
    {
        if (getBalanceFactor(root->left) >= 0)  
        {
            return rightRotate(root);
        }
        else
        {
            root->left = leftRotate(root->left);
            return rightRotate(root);
        }
    }
    
    if (balanceFactor < -1)  
    {
        if (getBalanceFactor(root->right) <= 0)  
        {
            return leftRotate(root); 
        }
        else
        {
            root->right = rightRotate(root->right); 
            return leftRotate(root);
        }
    }
    return root;
}

//caut valoarea key
int search(Node* node,int key)
{
    
    if(node == NULL ) 
        return 0; 
    if (key < node->key)
        search(node->left, key);
    else if (key > node->key) 
        search(node->right, key); 
    else
        return 1; 
}

void printvalues(Node *node)
{
    if(node == NULL) 
        return;
    printvalues(node->left);
    cout << node->key; 
    printvalues(node->right); 
}

int main()
{
    Node *root = NULL; 

    //insert
    root =  insertNode(root,3); //am introdus valoarea 3
    //delete
    root = deleteNode(root,3); //am sters valoarea 3
    //insert
    root =  insertNode(root,7); //am introdus valoarea 3
    //search
    cout << search(root,7); //returneaza 1 daca exista, 0 daca nu
    //print
    printvalues(root);
}
