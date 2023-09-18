#include<stdio.h>
#include<stdbool.h>
#include<string.h>
#include<stdlib.h>
#define ll long long
//dp soln to check if t is realizable
//TC : O(n*s)
bool realizable(ll a[],ll n,ll t){
    ll s=0;
    for(int i=0;i<n;i++) s+=a[i];
    bool dp[n][s*2+1];
    memset(dp,0,sizeof(dp));
    
    dp[0][a[0]+s]=dp[0][-a[0]+s]=1;
    for(int i=1;i<n;i++){
       for(ll j=0;j<=(s<<1);j++){
           dp[i][j]|=(j-a[i]>=0)?dp[i-1][j-a[i]]:0;
           dp[i][j]|=(j+a[i]<=(s<<1))?dp[i-1][j+a[i]]:0;
       }
    }
    return dp[n-1][t+s];
}
//recursive solution to print all ways
//TC : O((n*s))
void printAllWays(ll idx,ll a[],bool ***dp,ll t,ll path[],int n){
    if(idx<0){
        //printf("****\n");
       for(int i=0;i<n;i++){
          if(path[i]>=0) printf("+%lld",path[i]);
          else printf("%lld",path[i]);
       }
       ll sum=0;
       for(int i=0;i<n;i++) sum+=path[i];
       printf(" = %lld",sum);
       printf("\n");
       return;
    }
    if(dp[idx][t][1]){
        path[idx]=a[idx];
        //printf("+%lld ",a[idx]);
        printAllWays(idx-1,a,dp,t-a[idx],path,n);
    }
    if(dp[idx][t][0]){
        path[idx]=-a[idx];
        //printf("-%lld ",a[idx]);
        printAllWays(idx-1,a,dp,t+a[idx],path,n);
    }
}
//dp soln to print one realization
//TC : O(n*s)
void showone(ll a[],ll n,ll t){
    ll s=0;
    for(int i=0;i<n;i++) s+=a[i];
    
    bool ***dp=(bool ***)malloc(n*sizeof(bool **));
    for(int i=0;i<n;i++){
       dp[i]=(bool **)malloc((2*s+10)*sizeof(bool *));
       for(int j=0;j<=(s<<1);j++){
          dp[i][j]=(bool *)malloc(3*sizeof(bool));
       }
    }
    
    for(int i=0;i<n;i++){
       for(int j=0;j<=(s<<1);j++){
           for(int k=0;k<3;k++) dp[i][j][k]=0;
       }
    }
    
    dp[0][a[0]+s][1]=dp[0][-a[0]+s][0]=1;
    for(int i=1;i<n;i++){
       for(ll j=0;j<=(s<<1);j++){
          dp[i][j][1]|=(j-a[i]>=0)?(dp[i-1][j-a[i]][0]|dp[i-1][j-a[i]][1]):0;
          dp[i][j][0]|=(j+a[i]<=(s<<1))?(dp[i-1][j+a[i]][0]|dp[i-1][j+a[i]][1]):0;
       }
    }
    if(dp[n-1][t+s][0] || dp[n-1][t+s][1]){
        //printf("%d\n",dp[n-1][t+s][0]);
        int sign[n];
        int tmp=t+s;
        
        for(int i=n-1;i>=0;i--){
           if(dp[i][tmp][1]){
                sign[i]=1;
                tmp-=a[i];
           }else{
	        sign[i]=0;
	        tmp+=a[i];
           }
        }
        
        printf("Path:\n");
        for(int i=0;i<n;i++){
           if(sign[i]) printf(" + %lld",a[i]);
           else printf(" - %lld",a[i]);
        }
        
        printf(" = %lld\n",t);
        
        ll path[n];
        printf("Print all ways:\n");
        printAllWays(n-1,a,dp,t+s,path,n);
    }
}
int main(){
    ll n,t;
    scanf("%lld %lld",&n,&t);
    
    ll a[n];
    for(int i=0;i<n;i++) scanf("%lld",&a[i]);
    if(realizable(a,n,t)) printf("Realizable\n");
    else printf("Not realizable\n");
    ll path[n];
    //f(0,a,n,t,path);
    showone(a,n,t);
    return 0;
}
