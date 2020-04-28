#include <iostream>
#include <bits/stdc++.h>

using namespace std;

ifstream in("abce.in");
ofstream out("abce.out");


class SplayTree
{
private:
    struct node
    {
        int val;
        node *left, *right, *parent;
    };
    node* root = nullptr;
    node* newNode(int data,node* p)
    {
        node* aux = new node;

        aux -> val = data;

        aux -> left = NULL;
        aux -> right = NULL;
        aux -> parent = p;
        return aux;
    }
public:
    node* getroot()
    {
        return root;
    }

    node* minValue(node* curr)
    {
        if(curr == nullptr)
            return nullptr;
        while(curr->left != nullptr)
        {
            curr = curr->left;
        }
        return curr;
    }

    void rightRotate(node *x)
    {
        node *y = x -> left;
        if(x -> left != nullptr)
        {
            x -> left = y -> right;
        }
        if(y -> right != nullptr)
        {
            y -> right -> parent = x;
        }
        y -> parent = x -> parent;
        if(x -> parent == nullptr)
        {
            root = y;
        }
        else if(x -> parent -> left == x)
        {
            x -> parent -> left = y;
        }
        else
        {
            x -> parent -> right = y;
        }
        y -> right = x;
        x -> parent = y;
    }

    void leftRotate(node *x)
    {
        node *y = x -> right;
        if(x -> right != nullptr)
        {
            x -> right = y -> left;
        }
        if(y -> left != nullptr)
        {
            y -> left -> parent = x;
        }
        y -> parent = x -> parent;
        if(x -> parent == nullptr)
        {
            root = y;
        }
        else if(x -> parent -> left == x)
        {
            x -> parent -> left = y;
        }
        else
        {
            x -> parent -> right = y;
        }
        y -> left = x;
        x -> parent = y;
    }

    void splay(node *x)
    {
        if(x == nullptr)
            return;
        while(x -> parent != nullptr)
        {
            if(x -> parent -> parent == nullptr)
            {
                ///zig or zag
                if(x -> parent -> left == x)
                    rightRotate(x -> parent); /// zig
                else
                    leftRotate(x -> parent); ///zag
            }
            else
            {
                if(x -> parent -> left == x)
                {
                    if(x -> parent -> parent -> left == x -> parent)
                    {
                        ///zig-zig
                        rightRotate(x -> parent -> parent);
                        rightRotate(x -> parent);
                    }
                    else
                    {
                        ///zig-zag
                        rightRotate(x -> parent);
                        leftRotate(x -> parent);
                    }
                }
                else
                {
                    if(x -> parent -> parent -> right == x -> parent)
                    {
                        ///zag-zag
                        leftRotate(x -> parent -> parent);
                        leftRotate(x -> parent);
                    }
                    else
                    {
                        ///zag-zig
                        leftRotate(x -> parent);
                        rightRotate(x -> parent);
                    }
                }
            }
        }
    }

    void insert_node(int value)
    {
        if (root == nullptr)
        {
            root = newNode(value,nullptr);
            return;
        }
        // start with root node
        node *curr = root;
        // parent of root
        node *parent = nullptr;

        while(curr != nullptr)
        {
            parent = curr;
            if(curr -> val > value)
                curr = curr -> left;
            else
                curr = curr -> right;
        }
        node *splaynode = newNode(value,parent);
        if (value < parent -> val)
            parent->left = splaynode;
        else
            parent->right = splaynode;
        splay(splaynode);
    }

    node* find_value(int value)
    {
        // start with root node
        node *curr = root;
        // searching the value
        while (curr != nullptr && curr -> val != value)
        {
            // if given value is less than the current node, go to left subtree
            // else go to right subtree
            if (value < curr -> val)
                curr = curr -> left;
            else
                curr = curr -> right;
        }
        // if value is not present in the tree
        if (curr == nullptr)
            return nullptr;
        else
            return curr;

    }
    void delete_node(int value)
    {
        node* curr = find_value(value);
        if (curr == nullptr)
            return;
        splay(curr);
        node* parent = curr -> parent;
        ///node has no children
        if(curr -> left == nullptr && curr -> right == nullptr)
        {
            /// if node to be deleted is not a root node, then set its
            /// parent left/right child to null
            if (curr != root)
            {
                if (parent->left == curr)
                    parent->left = nullptr;
                else
                    parent->right = nullptr;
            }
            else
                root = nullptr;
            delete curr;
        }
        ///node has 2 children
        else if(curr -> left != nullptr && curr -> right != nullptr)
        {
            node* successor  = minValue(curr->right);
            ///interschimb nodurile si reduc la cazul in care sterg un nod care e frunza sau care are doar un fiu
            node *aux = successor;
            int valoare = curr -> val;
            successor = curr;
            successor -> val = aux -> val;
            curr = aux;
            curr -> val = valoare;
            parent = curr -> parent;
            ///daca e frunza
            if(curr -> right == nullptr)
            {
                if (curr != root)
                {
                    if (parent->left == curr)
                        parent->left = nullptr;
                    else
                        parent->right = nullptr;
                }
                else
                    root = nullptr;
                delete curr;
            }
            ///daca are fiu drept
            else
            {
                node* child = curr -> right;
                if (curr != root)
                {
                    if (curr == parent->left)
                        parent->left = child;
                    else
                        parent->right = child;
                    child -> parent = parent;
                }
                else
                {
                    root = child;
                    child -> parent = nullptr;
                }
                delete curr;
            }
        }
        ///node has 1 children
        else
        {
            /// find child node
            node* child;
            if(curr -> left != nullptr)
                child = curr -> left;
            else
                child = curr -> right;
            /// if node to be deleted is not a root node, then set its parent
            /// to its child
            child -> parent = parent;
            if (curr != root)
            {
                if (curr == parent->left)
                    parent->left = child;
                else
                    parent->right = child;
            }
            /// if node to be deleted is root node, then set the root to child
            else
            {
                root = child;
                child -> parent = nullptr;
            }
            delete curr;
        }
    }
    int max_node(int value)
    {
        node *curr = root, *parent = nullptr;
        while (curr != nullptr)
        {
            if (value == curr -> val)
            {
                splay(curr);
                return curr -> val;
            }
            if (value < curr -> val)
                curr = curr -> left;
            else
            {
                parent = curr;
                curr = curr -> right;
            }
        }
        splay(parent);
        return parent -> val;
    }

    int min_node(int value)
    {
        node *curr = root, *parent = nullptr;
        while (curr != nullptr)
        {
            if (value == curr -> val)
            {
                splay(curr);
                return curr -> val;
            }
            if (value < curr -> val)
            {
                parent = curr;
                curr = curr -> left;
            }
            else
            {
                curr = curr -> right;
            }
        }
        splay(parent);
        return parent -> val;
    }

    void inorder(node* root)
    {
        if (root == nullptr)
            return;
        inorder(root -> left);
        cout << root -> val << " ";
        inorder(root -> right);
    }
    void print_numbers(node* root,int x,int y)
    {
        if ( root == nullptr )
            return;
        if ( x < root -> val )
            print_numbers(root -> left, x, y);
        if (x <= root -> val && y >= root -> val )
            out<<root -> val<<" ";
        if ( y > root -> val )
            print_numbers(root -> right,x,y);
    }
};

int main()
{
    int q, tip, x, y;
    in >> q;
    SplayTree a;
    while (q--)
    {
        in >> tip >> x;
        if(tip == 1)
            a.insert_node(x);
        if(tip == 2)
            a.delete_node(x);
        if(tip == 3)
        {
            if(a.find_value(x) == nullptr)
                out << false << '\n';
            else
                out<< true << '\n';
        }
        if(tip == 4)
            out << a.max_node(x) << '\n';
        if(tip == 5)
            out << a.min_node(x) << '\n';
        if(tip == 6)
        {
            in >> y;
            a.print_numbers(a.getroot(),x,y);
            out<<'\n';
        }
        /*a.inorder(a.getroot());
        cout<<" o afisare " << '\n';
        */
    }
    return 0;
}
