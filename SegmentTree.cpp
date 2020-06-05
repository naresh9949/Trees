#include<iostream>
using namespace std;

class SegmentTree
{
	int array_size;
	int seg_tree_size;
	int *input,*Segment_Tree;
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

		for (int i = 0; i < seg_tree_size; i++)
			Segment_Tree[i] = INT_MAX;


		/*for(int i=0;i<n;i++)
			cout<<input[i]<<" ";
		cout<<endl;

		for (int i = 0; i < seg_tree_size; i++)
			cout<<Segment_Tree[i]<<" ";
		cout<<endl;*/

		Construtc_Segment_Tree(0,n-1,0);

		/*for (int i = 0; i < seg_tree_size; i++)
			cout<<Segment_Tree[i]<<" ";
		cout<<endl;*/

	}


	void show()
	{
		for(int i=0;i<array_size;i++)
			cout<<input[i]<<" ";
		cout<<endl;

		for (int i = 0; i < seg_tree_size; i++)
			cout<<Segment_Tree[i]<<" ";
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


	int Range_Query(int low,int high)
	{
		return Range_Utility(low,high,0,array_size-1,0);
	}

	void Update(int pos,int new_value)
	{
		Update_Utility(0,array_size-1,0,new_value);

		input[pos] = new_value;
	}



	void Update_Utility(int low,int high,int pos,int new_value)
	{
		if(low==high)
			Segment_Tree[pos] = new_value;
		else
		{
			int mid = (low+high)/2;

			if(pos<=mid)
				Update_Utility(low,mid,(2*pos)+1,new_value);
			else
				Update_Utility(mid+1,high,(2*pos)+2,new_value);

			Segment_Tree[pos] = min(Segment_Tree[(2*pos)+1],Segment_Tree[(2*pos)+2]);

		}
	}


	int Range_Utility(int qlow,int qhigh,int low,int high,int pos)
	{
		if(low>=qlow && high<=qhigh)
			return Segment_Tree[pos];

		if(qlow > high || qhigh<low)
			return INT_MAX;

		int mid = (low+high)/2;

		return min(Range_Utility(qlow,qhigh,low,mid,(2*pos)+1),Range_Utility(qlow,qhigh,mid+1,high,(2*pos)+2));
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

	obj.show();
	obj.Update(1,-8);
	obj.show();
}