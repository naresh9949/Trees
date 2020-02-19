/*

	Implementation of AVL-Tree
	insertion
	deletion using rotations

*/
#include<iostream> 
#include<algorithm>
using namespace std; 
struct node
{
	int data;
	int height;
	node* left;
	node* right;
};

node* Getnode(int key)
{
	node* nn=new node();
	nn->data=key;
	nn->left=NULL;
	nn->right=NULL;
	nn->height=1;

	return nn;
}

int Height(node* n)
{
	if(n==NULL)
		return 0;
	return n->height;
}
node* Get_Min_valu_Node(node* root)
{
	if(root==NULL)
		return root;
	node* temp=root;
	while(temp->left!=NULL)
		temp=temp->left;
	return temp;
}
node* RightRotate(node* n)
{
	node* x=n->left;
	node* y=x->right;

	//rotation
	x->right=n;
	n->left=y;

	n->height=max(Height(n->left),Height(n->right))+1;
	x->height=max(Height(x->left),Height(x->right))+1;

	return x;
}

node* LeftRotation(node* n)
{
	node* x=n->right;
	node* y=x->left;

	//Rotation
	x->left=n;
	n->right=y;

	n->height=max(Height(n->left),Height(n->right))+1;
	x->height=max(Height(x->left),Height(x->right))+1;

	return x;
}

int GetBalance(node* n)
{
	if(n==NULL)
		return 0;
	return (Height(n->left)-Height(n->right));
}


node* Insert(node* root,int key)
{
	 if(root==NULL)
	 	return Getnode(key);
	 else if(root->data<key)
	 	root->right=Insert(root->right,key);
	 else if(root->data>key)
	 	root->left=Insert(root->left,key);
	 else 
	 	return root;

	 root->height=max(Height(root->left),Height(root->right))+1;

	 int balance=GetBalance(root);

	 if(balance>1 && key<root->left->data){
	 	return RightRotate(root);
	 	return root;
	 }

	 if(balance<-1 && key>root->right->data){
	 	return LeftRotation(root);
	 	return root;
	 }

	 if(balance>1 && key>root->left->data)
	 {
	 	root->left=LeftRotation(root->left);
	 	return RightRotate(root);
	 	return root;

	 }

	 if(balance<-1 && key<root->right->data)
	 {
	 	root->right=RightRotate(root->right);
	 	return LeftRotation(root);
	 	return root;

	 }
	 return root;
}

node* DeleteNode(node* root,int key)
{
	if(root==NULL)
		return root;
	if(key<root->data)
		root->left=DeleteNode(root->left,key);
	else if(key>root->data)
		root->right=DeleteNode(root->right,key);
	else
	{
		// node with one child or no child
		if(root->left==NULL || root->right==NULL)
		{
			node* temp=root->left?root->left:root->right;
			if(temp==NULL)//No child case
			{
				temp=root;
				root=NULL;

			}
			else
				*root=*temp;
			free(temp);
		}
		else
		{
			node* temp=Get_Min_valu_Node(root);
			root->data=temp->data;
			root->right=DeleteNode(root->right,temp->data);
		}
	}

	if(root==NULL)
		return root;
	root->height=1+max(Height(root->left),Height(root->right));

	int balance=GetBalance(root);

	if(balance>1 && GetBalance(root->left)>=0)
		return RightRotate(root);
	if(balance>1 && GetBalance(root->left)<0)
	{
		root->left=LeftRotation(root->left);
		return RightRotate(root);
	}
	if(balance<-1 && GetBalance(root->right)<=0)
		return LeftRotation(root);
	if(balance<-1 && GetBalance(root->right)>0)
	{
		root->right=RightRotate(root->right);
		return LeftRotation(root);
	}

	return root;

}

void print(node* n)
{
	node* temp=n;
	if(temp!=NULL)
	{
		print(temp->left);
		cout<<temp->data<<" ";
		print(temp->right);
	}
}
int main()
{
	node* root=NULL;
	
	root = Insert(root, 40); 
	root = Insert(root, 5); 
	root = Insert(root, 25); 
	root = Insert(root, 10); 
	root = Insert(root, 2); 
	root = Insert(root, 30); 
	root = DeleteNode(root,10);
	root = DeleteNode(root,5);
	print(root);
	cout<<endl;
}

