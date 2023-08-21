#include <stdlib.h>
#include <stdio.h>
#define ll long long

static inline ll max(ll a, ll b) {
	return (a<=b)?b:a;
}

ll countR(ll n) {
	if (n==0) return 1;
	if (n<0) return 0;
	ll ways=0;
	for (int i=1; i<=3; i++) {
		ways+=countR(n-i);
	}
	return max(0,ways);
}

ll countDP(ll n) {
	ll* dp=(ll*)malloc((n+1)*sizeof(ll));
	for (int i=0; i<=n; i++) dp[i]=0;
	dp[0]=1;
	for (int i=1; i<=n; i++) {
		ll ans=0;
		if (i-3>=0) ans+=dp[i-3];
		if (i-2>=0) ans+=dp[i-2];
		if (i-1>=0) ans+=dp[i-1];
		dp[i]=ans;
	}
	return dp[n];
}

ll countNMDP(ll n, ll m) {
	ll ncr[20][20];
	for (int i=0; i<20; i++) ncr[i][0]=1;
	for (int i=1; i<20; i++) ncr[0][i]=0;
	for (int i=1; i<20; i++) {
		for (int j=1; j<20; j++) {
			ncr[i][j]=ncr[i-1][j-1]+ncr[i-1][j];
		}
	}
	return ncr[n-1][m-1];
}

ll countNMRec(ll n, ll m) {
	if (n==0) {
		return m==0;
	}
	if (m==0) {
		return n==0;
	}
	ll ways=0;
	for (int i=1; i<=n; i++) {
		ways+=countNMRec(n-i,m-1);
	}
	return ways;
}

int main() {
	ll n,m;
	printf("Enter n: \n");
	scanf("%lld", &n);
	printf("Count (recursive): %lld\n", countR(n));
	printf("Count (iterative): %lld\n", countDP(n));
	printf("Enter n: \n");
	scanf("%lld", &n);
	printf("Enter m: \n");
	scanf("%lld", &m);
	printf("Count r(n,m) (recursive): %lld\n", countNMRec(n,m));
	printf("Count r(n,m) (iterative): %lld\n", countNMDP(n,m));
	return 0;
}
