#include<bits/stdc++.h>
using namespace std;

class SegmentTree
{
    public:
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
            Segment_Tree[i] = INT_MIN;
            lazy[i] = 0;
        }

        Construtc_Segment_Tree(0,n-1,0);
    }
    
    
    
    void Construtc_Segment_Tree(int low,int high,int pos)
    {
        if(low == high)
        {
            Segment_Tree[pos] = input[low];
            return;
        }
        
        int mid = (low+high)/2;
        Construtc_Segment_Tree(low,mid,(2*pos)+1);
        Construtc_Segment_Tree(mid+1,high,(2*pos)+2);
        
        Segment_Tree[pos] = max(Segment_Tree[(2*pos)+1],Segment_Tree[(2*pos)+2]);
    }
    
    
    
    void UpdateRange(int startRange, int endRange,int delta, int low, int high, int pos)
    {
        if(low>high)
        return;
        
        if(lazy[pos] != 0)
        {
            Segment_Tree[pos] += lazy[pos];
            
            if(low!=high)
            {
                lazy[(2*pos)+1] = lazy[pos];
                lazy[(2*pos)+2] = lazy[pos];
            }
            lazy[pos] = 0;
        }
        
        
        //no overlap condition
        if(startRange > high || endRange < low) {
            return;
        }
        
         //total overlap condition
        if(startRange <= low && endRange >= high) {
            Segment_Tree[pos] += delta;
            
            if(low != high) {
                lazy[2*pos + 1] += delta;
                lazy[2*pos + 2] += delta;
            }
            return;
        }
        
        int mid = (low+high)/2;
        
        UpdateRange(startRange,endRange,delta,low,mid,(2*pos)+1);
        UpdateRange(startRange,endRange,delta,mid+1,high,(2*pos)+2);
        
        Segment_Tree[pos] = max(Segment_Tree[2*pos + 1], Segment_Tree[2*pos + 2]);
        

    }
    
    
    
    int RangeQuery(int qlow, int qhigh,int low, int high, int pos)
    {
        if(low > high) {
            return INT_MIN;
        }

        //make sure all propagation is done at pos. If not update tree
        //at pos and mark its children for lazy propagation.
        if (lazy[pos] != 0) {
            Segment_Tree[pos] += lazy[pos];
            
            if (low != high) { //not a leaf node
                lazy[2 * pos + 1] += lazy[pos];
                lazy[2 * pos + 2] += lazy[pos];
            }
            lazy[pos] = 0;
        }

        //no overlap
        if(qlow > high || qhigh < low){
            return INT_MIN;
        }

        //total overlap
        if(qlow <= low && qhigh >= high){
            return Segment_Tree[pos];
        }

        //partial overlap
        int mid = (low+high)/2;
        return max(RangeQuery(qlow, qhigh,
                        low, mid, 2 * pos + 1),
                RangeQuery(qlow, qhigh,
                        mid + 1, high, 2 * pos + 2));
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
    
    
};

int main()
{
    int a[] = {0,0,0,0,0};
    
    SegmentTree obj(a,5);
    
    obj.UpdateRange(0,2,100,0,4,0);
    
    std::cout << obj.RangeQuery(0,2,0,4,0) << std::endl;
    
}
