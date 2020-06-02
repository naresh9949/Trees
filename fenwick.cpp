#include<iostream>
using namespace std;

class FenwickTree
{
	int size;
	int *Tree;
	int *ar;

public:
	FenwickTree(int arr[],int n)
	{
		Tree = new int[n+1];
		ar = new int[n];

		size = n+1;
		memset(Tree,0,size);
		
		for(int i=0;i<n;i++)
		{
			ar[i] = arr[i];
		}

		//construct the BIT
		for(int i=0;i<n;i++)
		{
			int pos = i+1;

			while(pos<size)
			{
				Tree[pos] = Tree[pos]+arr[i];
				pos = GetNext(pos);
			}
		}
		//for(int i=0;i<size;i++)
			//cout<<"i="<<i<<" "<<Tree[i]<<endl;
	}


	int GetSum(int index)
	{
		int pos = index+1;
		int sum = 0;
		while(pos!=0)
		{
			sum+=Tree[pos];
			pos = GetParent(pos);
		}
		return sum;
	}


	void Update(int index,int value)
	{
		int val = value - ar[index];
		Update_Util(index,val);
		ar[index] = value;
	}

	void Update_Util(int index,int value)
	{
		int pos = index+1;

		while(pos<size)
		{
			Tree[pos] = Tree[pos]+value;
			pos = GetNext(pos);
		}
	}

	void show()
	{
			cout<<"BIT :";
			for(int i=0;i<size;i++)
				cout<<Tree[i]<<" ";
			cout<<endl;

			cout<<"ARR ";

			for(int i=0;i<size-1;i++)
				cout<<ar[i]<<" ";
			cout<<endl;
	}

	int GetNext(int k)
	{
		return k + (k & -k);
	}

	int GetParent(int k)
	{
		return k - (k & -k);
	}

};

int main()
{
	int n=11;
	int a[] = {3,2,-1,6,5,4,-3,3,7,2,3};

	FenwickTree tree(a,n);
	tree.show();

	cout<<"---"<<endl;

	tree.Update(1,22);

	tree.show();
	
}