#include<iostream>
using namespace std;

struct node
{
	int key,prior,cnt;
	node *left,*right;
	node(int key,int prior) : key(key),prior(prior),left(NULL),right(NULL){}
};

typedef node* pitem;

class treaps
{
public:
	pitem tree;

	treaps()
	{
		tree = NULL;
	}

	
public:

	void split(pitem tree,int key,pitem &left,pitem &right)
	{
		if(!tree)
		{
			left=NULL;
			right=NULL;
		}
		else if(key < tree->key){
			split(tree->left,key,left,tree->left);
			right=tree;
		}
		else{
			split(tree->right,key,tree->right,right);
			left=tree;
		}
	}



	void add(pitem &tree,pitem it)
	{
		if(!tree)
			tree=it;
		else if(it->prior > tree->prior){
			split(tree,it->key,it->left,it->right);
			tree = it;
		}
		else
			add(it->key < tree->key ? tree->left : tree->right,it);
	}


	void merge(pitem &tree,pitem left,pitem right)
	{
		if(!left || !right)
			tree = left ? left : right;
		else if(left->prior > right->prior){
			merge(left->right,left->right,right);
			tree = left;
		}
		else
		{
			merge(right->left,left,right->left);
			tree = right;
		}
	}


	void showIt(pitem tree)
	{
		if(!tree)
			return ; 
		showIt(tree->left);
		cout<<tree->key<<":"<<tree->prior<<endl;
		showIt(tree->right);
	}


	// utility function To Delete a specified value from the treap
	void Erase(pitem &tree,int key)
	{
		if(key == tree->key)
			merge(tree,tree->left,tree->right);
		else
			Erase(key < tree->key ? tree->left : tree->right,key);

	}


	void Show()
	{
		showIt(this->tree);
	}

	void Insert(pitem it)
	{
		add(this->tree,it);
	}


	// Delete Method 
	void Delete(int key)
	{
		Erase(this->tree,key);
	}

};



int main()
{
	treaps treepi;

	node* p = new node(23,22);
	node* p1 = new node(34,425);
	node* p2 = new node(10,45);

	node* p3 = new node(50,48);

	treepi.Insert(p1);
	treepi.Insert(p);
	treepi.Insert(p2);
	treepi.Insert(p3);


	treepi.Delete(34);

	treepi.Show();

}