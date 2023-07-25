/*
	Author: Mainaak Chakraborty
	Roll: 21CS8046
	Date: 25/7/23 
	Lab-2
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <assert.h>
typedef long long ll;

// Swap two elements in the array
void swap(char *a, char *b) {
    char temp=*a;
    *a=*b;
    *b=temp;
}

// checks if a string has only 1 occurence of 'xyz' in O(N) time
bool isFeasible(char *s, int n) {
	int cnt=0;
	for (int i=0; i<n-2; i++) {
		if (s[i]=='x' && s[i+1]=='y' && s[i+2]=='z') {
			cnt++;
		}
	}
	return (cnt==1)?true:false;
}

// Find the next lexicographically greater permutation of the array
bool nextPermutation(char *s, int n) {
    int i=n-2, j=n-1;
	// find pivot
	for (i=n-2; i>=0; i--) {
		if (s[i]<s[i+1]) {
			break;
		}
	}
	// if no pivot then it is greatest permutation
	if (i<0) {
		return false;
	}
	else {
		for (j=n-1; j>i; j--) {
			if (s[j]>s[i]) {
				break;
			}
		}
		swap(&s[i],&s[j]);
		// reverse the suffix
		int l=i+1, r=n-1;
		while (l<r) {
			swap(&s[l],&s[r]);
			l++;
			r--;
		}
		return true;
	}
}

ll searchIt2(int n) {
	ll ans=0;
	char *s=(char*)malloc((n+1)*sizeof(char));
	// number of x
	for (int i=0; i<=n; i++) {
		// number of y
		for (int j=0; j<=n-i; j++) {
			s[n]='\0';
			// push required number of x,y,z
			for (int k=0; k<i; k++) s[k]='x';
			for (int k=i; k<i+j; k++) s[k]='y';
			for (int k=i+j; k<n; k++) s[k]='z';

			// generate and test new permutations iteratively
			do {
				if (isFeasible(s,n)==true) {
					ans++;
				}
			}
			while (nextPermutation(s,n));
		}
	}
	//free the memory
	free(s);
	return ans;
}

// calculate value of S(i)
ll S(int i, ll pow3[20], ll ncr[20][20]) {
	ll si=0;
	si+=pow3[i];
	for (int k=1; k<=i/3; k++) {
		ll tmp=ncr[i-2*k][k]*pow3[i-3*k];
		if (k%2) si-=tmp;
		else si+=tmp;
	}
	return si;
}

//calculates count of possible strings iteratively in O(N^2)
ll searchIt(int n, ll pow3[20], ll ncr[20][20]) {
	ll ans=0;
	for (int i=0; i<=n-3; i++) {
		 ll tmp=S(i,pow3,ncr)*S(n-i-3,pow3,ncr);
		 ans+=tmp;
	}
	return ans;
}


// generates all allowed substrings in time complexity of O(N*3^N)
ll searchEx(char *s, int ind, int n) {
	if (ind==n) {
		return isFeasible(s,n)==true;
	}
	// generate all combos
	ll ans=0;
	for (char ch='x'; ch<='z'; ch++) {
		s[ind]=ch;
		ans+=searchEx(s,ind+1,n);
	}
	return ans;
}

int main() {
	int n;
	printf("Enter value of n: \n");
	scanf("%d",&n);
	char *s=(char*)malloc((n+1)*sizeof(char));
	s[n]='\0';
	
	//Measure time for exhaustive search
	clock_t c1=clock();
	//exhaustive search function call
	ll ansEx=searchEx(s,0,n);
	
	clock_t c2=clock();
	//calculate time taken for recursion
	double t=(c2-c1)/(double)CLOCKS_PER_SEC;
	
	//printing results for recursive method
	printf("Time taken by exhaustive recursive search: %lf \n", t);
	printf("Count of strings is : %lld \n\n",ansEx);
	
	
	// iterative method
	ll pow3[20]={1};
	ll ncr[20][20];
	// precompute powers of 3
	for (int i=1; i<20; i++) {
		pow3[i]=pow3[i-1]*3LL;
	}
	// precompute values of nCr
	for (int i=0; i<20; i++) ncr[i][0]=1;
	for (int i=1; i<20; i++) ncr[0][i]=0;
	for (int i=1; i<20; i++) {
		for (int j=1; j<20; j++) {
			ncr[i][j]=ncr[i-1][j-1]+ncr[i-1][j];
		}
	}
	// calculate time for iterative method
	c1=clock();
	ll ansIt=searchIt(n, pow3, ncr);
	c2=clock();
	
	//calculate time taken for iteration
	t=(c2-c1)/(double)CLOCKS_PER_SEC;
	
	//printing results for iterative method
	printf("Time taken by closed form formula: %lf \n", t);
	printf("Count of strings is : %lld \n\n",ansIt);

	//Measure time for exhaustive iterative search
	c1=clock();
	//exhaustive search function call
	ll ansIt2=searchIt2(n);
	
	c2=clock();
	//calculate time taken for exhaustive iterative search
	t=(c2-c1)/CLOCKS_PER_SEC;
	
	//printing results for recursive method
	printf("Time taken by exhaustive iterative search: %lf \n", t);
	printf("Count of strings is : %lld \n\n",ansIt2);

	// assertion for checking if all counts equal
	assert((ansEx==ansIt) && (ansIt==ansIt2));
	printf("Check passed: All counts equal.\n\n");

	return 0;
}
