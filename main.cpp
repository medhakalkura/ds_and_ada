/*Insertion and deletion to a binary tree*/

#include <iostream>
#include<stdlib.h>
#include<queue>
using namespace std;
struct node
{
    int data;
    struct node *right,*left;
};
struct node *newnode(int data) //allocates space for a new node
{
 struct node *n=(struct node*)malloc(sizeof(struct node));
 n->data=data;
 n->left=n->right=NULL;
 return n;
}
struct node *createtree(int a[],int x,int n,struct node *root) //creation of a tree from a given array of elements
{
    if(x<n)
    {
        struct node *t=newnode(a[x]);
        root=t;
        root->left=createtree(a,2*x+1,n,root->left);
        root->right=createtree(a,2*x+2,n,root->right);
    }
return root;
}
struct node *insertinto(int i,struct node *root) //inserts a new node to an existing tree
{
    queue<struct node *> q;
    struct node *t;
    q.push(root);
    while(!q.empty()) //using level order traversal to find a node which has no right child or left child
    {
        t=q.front();
        q.pop();
        if(t->left==NULL)
        {
            t->left=newnode(i);
            break;
        }
        else
            q.push(t->left);
        if(t->right==NULL)
        {
                t->right=newnode(i);
                break;
        }
        else
            q.push(t->right);

    }
    return root;
} 
void del(struct node *root,struct node *temp) //deletes the last node
{
    queue<struct node *> q;
    q.push(root);

    while(!q.empty())
    {
        struct node *tt;
        tt=q.front();
        q.pop();
        if(tt->left!=NULL)
        {
        if(tt->left==temp)
        {
            tt->left=NULL;
            delete(temp);
            return;
        }
        else
            q.push(tt->left);
        }

        if(tt->right!=NULL)
        {

        if(tt->right==temp)
            {
                tt->right=NULL;
                delete(temp);
                return;
            }
        else
            q.push(tt->right);
        }
    }
}
struct node * deletenode(int x,struct node *root) //finds out the node whose data field matches the key value.
{
    queue<struct node *> q;
    struct node *t,*key=NULL;
    q.push(root);
    while(!q.empty()) //uses level order traversal
    {
        t=q.front();
        q.pop();
        if(t->data==x)
            key=t;
        if(t->left!=NULL)
            q.push(t->left);
        if(t->right!=NULL)
            q.push(t->right);
    }

    int m = t->data;
    key->data = m; //copies the data of last node to the key node 
    del(root,t); //deletes the last node

return root;
}
void inorder(struct node *root) //inorder traversal of the tree
{
    if(root!=NULL)
    {
        inorder(root->left);
        cout<<" "<<root->data;
        inorder(root->right);
    }
}
int main()
{
    int n,ch;
    struct node *root=NULL;
    cout<<"\nEnter the number of nodes :";
    cin>>n;
    int i,a[n];
    cout<<"\nEnter the node data :";
    for(i=0;i<n;i++)
        cin>>a[i];
    root=createtree(a,0,n,root);
    inorder(root);
    cout<<"\nEnter choice 1.insert 2.delete ";
    cin>>ch;
    int x;
    switch(ch)
    {
        case 1: cout<<"\nEnter the data you want to insert :";
                cin>>x;
                root=insertinto(x,root);
                inorder(root);
                break;
        case 2: cout<<"\nEnter the node data to be deleted :";
                cin>>x;
                root=deletenode(x,root);
                inorder(root);
                break;
        default: exit(0);
    }
    return 0;
}
