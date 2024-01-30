#include<bits/stdc++.h>
using namespace std;



int getIndex(int in[],int n,int val){
        for(int i=0;i<n;i++){
            if(in[i]==val) return i;
        }
        return -1;
    }
    
    Node *bTree(int in[],int pre[],int is, int ie, int &pindex,int n){
        if(pindex>=n || is>ie )
            return NULL;
            
        Node *root= new Node(pre[pindex++]);
        //int iindex=mp[root->data];
        int iindex= getIndex(in,n,root->data);
        
        root->left=bTree(in,pre,is,iindex-1,pindex,n);
        root->right=bTree(in,pre,iindex+1,ie,pindex,n);
        
        return root;
    }
    
    Node* buildTree(int in[],int pre[], int n)
    {
        int pindex=0;
        return bTree(in,pre,0,n-1,pindex,n);
    }


    int main(){


        return 0;
    }