#include<iostream>
using namespace std;

class SegmentTree
{
	int array_size;
	int seg_tree_size;
	int *input,*Segment_Tree,*lazy;
public:
	SegmentTree(int a[],int n)
	{
		array_size = n;

		input = new int[n];

		for(int i=0;i<n;i++)
			input[i] = a[i];

		if(isPowerOfTwo(n))
			seg_tree_size = (2*n)-1;
		else
		{
			int k = nextPowerOf2(n);
			seg_tree_size = (2*k)-1;
		}

		Segment_Tree = new int[seg_tree_size];

		lazy = new int[seg_tree_size];


		for (int i = 0; i < seg_tree_size; i++){
			Segment_Tree[i] = INT_MAX;
			lazy[i] = 0;
		}

		Construtc_Segment_Tree(0,n-1,0);

	}




	void show()
	{

		cout<<"SEG ";
		for (int i = 0; i < seg_tree_size; i++)
			cout<<Segment_Tree[i]<<" ";
		cout<<endl;

		cout<<"lazy ";
		for (int i = 0; i < seg_tree_size; i++)
			cout<<lazy[i]<<" ";
		cout<<endl;
	}



	void Construtc_Segment_Tree(int low,int high,int pos)
	{
		if(low==high)
		{
			Segment_Tree[pos] = input[low];
			return;
		}

		int mid = (low+high)/2;

		Construtc_Segment_Tree(low,mid,(2*pos)+1);
		Construtc_Segment_Tree(mid+1,high,(2*pos)+2);

		Segment_Tree[pos] = min(Segment_Tree[(2*pos)+1],Segment_Tree[(2*pos)+2]);
	}




	void Update_Range(int l,int r,int new_value)
	{
		Update_Utility(0,array_size-1,l,r,0,new_value);

	}

	void Update_Index(int pos,int value)
	{
		Update_Utility(0,array_size-1,pos,pos,0,value);
	}





	void Update_Utility(int low,int high,int l,int r,int pos,int new_value)
	{
		if(low>high)
			return;

		if(lazy[pos]!=0)
		{
			Segment_Tree[pos] += lazy[pos]; // update seg tree with lazy value
			
			if(low!=high){
			lazy[(2*pos)+1] = lazy[pos];    // push lazy value to the child if it is not a leaf
			lazy[(2*pos)+2] = lazy[pos];
			}

			lazy[pos] = 0;  //put lazy[pos] = 0 to delete lazy value
		}

		if(l>high || r<low)
			return;

		if(low>=l && high<=r){
			
			Segment_Tree[pos] += new_value; // update seg tree with lazy value
			
			if(low!=high){
			lazy[(2*pos)+1] = new_value;    // push lazy value to the child if it is not a leaf
			lazy[(2*pos)+2] = new_value;
			}

			return;
		}

		int mid = (low+high)/2;

		Update_Utility(low,mid,l,r,(2*pos)+1,new_value);

		Update_Utility(mid+1,high,l,r,(2*pos)+2,new_value);

		Segment_Tree[pos] = min(Segment_Tree[(2*pos)+1],Segment_Tree[(2*pos)+2]);

	}




	int Range_Query(int l,int r)
	{
		return Range_Query_Utility(0,array_size-1,l,r,0);
	}



	int Range_Query_Utility(int low,int high,int l,int r,int pos)
	{
		if(low>high)
			return INT_MAX;
		if(lazy[pos]!=0)
		{
			Segment_Tree[pos] += lazy[pos];

			if(low!=high)
			{
				lazy[(2*pos)+1] = lazy[pos];
				lazy[(2*pos)+2] = lazy[pos];
			}

			lazy[pos] = 0;
		}

		if(l>high || r<low)
			return INT_MAX;

		if(low>=l && high<=r)
			return Segment_Tree[pos];

		int mid = (low+high)/2;

		return min(Range_Query_Utility(low,mid,l,r,(2*pos)+1),
			Range_Query_Utility(mid+1,high,l,r,(2*pos)+2));

	}




	bool isPowerOfTwo (int x)  
	{  
    /* First x in the below expression is for the case when x is 0 */
    return x && (!(x&(x-1)));  
	}


	int nextPowerOf2(int n)  
	{  
    	int p = 1;  
    	if (n && !(n & (n - 1)))  
        return n;  
  
    	while (p < n)  
        	p <<= 1;  
        return p;
      
	}  

	//~SegmentTree();
	
};

int main()
{
	int n=5;
	int a[] = {1,2,4,-2,6};

	SegmentTree obj(a,n);

	//obj.show();

	obj.Update_Range(1,4,100);

	obj.Update_Range(0,2,100);

	obj.Update_Range(3,4,100);

	obj.Update_Index(2,500);

	//obj.show();

	cout<<obj.Range_Query(2,2)<<endl;



}