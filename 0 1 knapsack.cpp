#include<bits/stdc++.h>
using namespace std;
int knapsack(int n,vector<int>&wt,vector<int>&val,int capacity,vector<int>&chosen)
{
    vector<vector<int> >dp(n+1,vector<int>(capacity+1,0));
    for(int i=1;i<n;i++)
    {
        for(int w=1;w<n;w++)
        {
            if(w>=wt[i-1])
            {
                dp[i][w]=max(val[i-1]+dp[i-1][w-wt[i-1]],dp[i-1][w]);
            }
            else{
                dp[i][w]=dp[i-1][w];
            }
        }
    }
    int w=capacity;
    for(int i=n;i>0;i--)
    {
        if(dp[i][w]!=dp[i-1][w])
        {
            chosen.push_back(i);
            w-=wt[i-1];
        }
    }
    return dp[n][capacity];
}
int main()
{
    int n;
    cin>>n;
    vector<int>wt(n);
    for(int i=0;i<n;i++)
    {
        cin>>wt[i];
    }
    vector<int>val(n);
    for(int i=0;i<n;i++)
    {
        cin>>val[i];
    }
    int capacity;
    cin>>capacity;
    vector<int>chosen;
    int maxval=knapsack(n,wt,val,capacity,chosen);
    cout<<maxval<<endl;
    for(int i=chosen.size()-1;i>=0;i--)
    {
        cout<<chosen[i]<<" ";
    }
    cout<<endl;

}
