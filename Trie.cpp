#include<bits/stdc++.h>
using namespace std;

struct Node{
    
    //char data;
    int wc;
    Node* child[26];
};

Node* GetNode(char c)
{
    Node* nn = new Node();
    //nn->data = c;
    nn->wc = 0;
    
    for(int i=0;i<26;i++)
    nn->child[i] =NULL;
    
    return nn;
}


void Insert(Node* root,string s)
{
    Node* cur = root;
    
    int idx;
    
    for(int i=0;s[i];i++)
    {
        idx = s[i]-'a';
        
        if(cur->child[idx]==NULL)
        cur->child[idx] = GetNode(s[i]);
        
        cur->child[idx]->wc++;
        
        cur = cur->child[idx];
    }
}


bool Search(Node* root,string s)
{
    Node* cur = root;
    
    int idx;
    
    for(int i=0;s[i];i++)
    {
        idx = s[i]-'a';
        
        if(cur->child[idx]==NULL || cur->child[idx]->wc==0)
        return false;
        
        cur = cur->child[idx];
    }
    
    return true;
}

bool Delete(Node* root,string s)
{
    if(Search(root,s))
    {
        Node* cur = root;
        int idx;
        
        for(int i=0;s[i];i++)
        {
            idx = s[i]-'a';
            
            cur->child[idx]->wc--;
            cur = cur->child[idx];
        }
        
        return true;
    }
    
    return false;
}

int Prefix_Count(Node* root,string s)
{
    Node* cur = root;
    int idx ;
    
    for(int i=0;s[i];i++)
    {
        idx = s[i]-'a';
        
        if(cur->child[idx]==NULL || cur->child[idx]->wc==0)
        return 0;
        
        cur = cur->child[idx];
    }
    
    return cur->wc;
}

int main()
{
    Node* root = new Node();
    
    //root->data = '-';
    root->wc = 0;
    
    for(int i=0;i<26;i++)
    root->child[i] =NULL;
    
    Insert(root,"naresh");
    Insert(root,"narash");
    Insert(root,"narwsh");
    Insert(root,"nargsh");
    
    //std::cout << Search(root,"naresh") << std::endl;
    
    //Delete(root,"naresh");
    
    //std::cout << Search(root,"naresh") << std::endl;
    
    cout<<Prefix_Count(root,"nar")<<endl;
    
}