#include<stdio.h>
#include<stdlib.h>
//checks if given array is valid 
//TC:O(n)
int chk(int *arr,int n){
   int hsh[16]={0};
   for(int i=0;i<n;i++) hsh[arr[i]]++;
   
   for(int i=0;i<n;i++){
      if(hsh[i]!=arr[i]) return 0;
   }
   return 1;
}
//find max of 2 numbers
int max(int a,int b){
   if(a>=b) return a;
   return b;
}
//recursively find all possible arrays
//TC: O(n^n)
void f(int idx,int *arr,int n){
   if(idx==n){//base case
      if(chk(arr,n)){
          for(int i=0;i<n;i++){
             if(arr[i]>=10) printf("%c",(char)((arr[i]-10)+'A'));//prints the number in hexadecimal form
             else printf("%d",arr[i]);
          }
          printf("\n");
      }
      return;
   }
   
   int sum=0;
   for(int i=0;i<n;i++) sum+=arr[i];
   
   for(int i=0;i<=max(0,n-sum);i++){
       arr[idx]=i;
       f(idx+1,arr,n);
       arr[idx]=0;//backtracking step
   }
   
}
//main function to calculate the numbers
int main(){
    for(int n=4;n<=16;n++){//iterate over all bases
        int *arr=(int *)malloc(sizeof(int)*n);
        for(int i=0;i<n;i++) arr[i]=0;//initialise all elements with 0
        printf("Base %d:\n",n);
        f(0,arr,n);
    }
    return 0;
}
