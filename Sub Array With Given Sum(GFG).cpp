#include<bits/stdc++.h>

using namespace std;

//     ***Subarray with given sum ***

//link-->  https://practice.geeksforgeeks.org/problems/subarray-with-given-sum-1587115621/1#

vector<int> subarraySum(int arr[], int n, long long s) // main function.
    {
        // Your code here
        long long sum;
        vector<int>sas;
        for(int i=0;i<n;i++){
            sum=s;
            for(int j=i;j<n;j++){
                sum-=arr[j];
                if(sum<0)break;
                if(sum==0){
                        sas.push_back(i+1);
                        sas.push_back(j+1);                  
                    return sas;
                    }
                }
            }
        sas.push_back(-1);
        return sas;
        
    }

int main(){
	// test input..
	int arr[]={1, 2, 3, 7, 5};

	vector<int>v=subarraySum(arr,5,12); // T(n)= O(n^2) Worst Case
    cout<<endl;
	for(auto it: v)
		cout<<it<<" ";
}




