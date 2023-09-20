/*
      Author: Dhruba Sinha
      @ GNU/Linux Users' Group, NIT DGP
*/


#include <stdio.h>


typedef struct Ans {
	int pr;
	int bp, sp;
} Ans;

Ans func(int b[], int s[], int l, int r, int c) {
	Ans fi;
	if(l > r) {
		fi.pr = -1; fi.bp = fi.sp = 0;
		return fi;
	}
	else if(l == r) {
		fi.pr = s[l]-b[l];
		fi.bp = fi.sp = l;
		return fi;
	}
	
	int mid = (l + r) >> 1;
	Ans lans = func(b, s, l, mid, c);
	Ans rans = func(b, s, mid+1, r, c);
	
	int currpr, bidx, sidx;
	if(lans.pr >= rans.pr) {
		currpr = lans.pr;
		bidx = lans.bp;
		sidx = lans.sp; 
	}
	else {
		currpr = rans.pr;
		bidx = rans.bp;
		sidx = rans.sp;
	}
	
	int bi = l, si = mid+1;
	for (int i = l; i <= mid; i++) {
		if(b[bi] > b[i]) bi = i;
	}
	
	for (int i = mid+1; i <= r; i++) {
		if(s[si] < s[i]) si = i;
	}
	
	int curr = (c / b[bi]) * (s[si] - b[bi]);
	if(curr >= currpr) {
		currpr = curr;
		bidx = bi;
		sidx = si;
	}
	
	fi.pr = currpr;
	fi.bp = bidx;
	fi.sp = sidx;
	return fi;
}

//optimal profit with one transaction using divide and conquer technique
//TC: O(nlogn)
void singletrans_dc(int b[], int s[], int n, int c) {
	Ans ans = func(b, s, 0, n-1, c);
	printf("buying date %d and buying price %d\n", ans.bp, b[ans.bp]);
	printf("selling date %d and selling price %d\n", ans.sp, s[ans.sp]);
	printf("profit: %d\n\n", ans.pr);
}


//optimal profit with one transaction
//TC: O(n)
void singletrans(int b[], int s[], int n, int c) {
	int profit = 0;
	int buy, sell;
	buy = sell = 0;
	for (int i = 0, bidx = 0; i < n; i++) {
		if (b[i] < b[bidx]) bidx = i;
		
		int curr = (c / b[bidx]) * (s[i] - b[bidx]);
		if (curr >= profit) {
			profit = curr;
			sell = i;
			buy = bidx;
		}
	}
	
	printf("buying date %d and buying price %d\n", buy, b[buy]);
	printf("selling date %d and selling price %d\n", sell, s[sell]);
	printf("profit: %d\n\n", profit);
}

void printpath(int idx, int b[], int s[], int dp[], int bdp[], int sdp[]) {
	if(idx <= 0) return;
	
	printpath(bdp[idx]-1, b, s, dp, bdp, sdp);
	
	printf("buying date %d and buying price %d\n", bdp[idx]-1, b[bdp[idx] - 1]);
	printf("selling date %d and selling price %d\n", sdp[idx]-1, s[sdp[idx] - 1]);
	printf("current capital: %d\n\n", dp[idx]);
	
}


//optimal profit with any number of transactions
//TC: O(n^2)
void multitrans(int b[], int s[], int n, int c) {
	int dp[n+1];
	int bdp[n+1], sdp[n+1];
	dp[0] = c;
	bdp[0] = sdp[0] = 0;
	for (int i = 1; i <= n; i++) {
		dp[i] = dp[i-1];
		bdp[i] = bdp[i-1];
		sdp[i] = sdp[i-1];
		
		for (int j = i; j; j--) {
			int buy = b[j-1], sell = s[i-1];
			int curr = dp[j-1] + (dp[j-1] / buy) * (sell - buy);
			if (curr > dp[i]) {
				dp[i] = curr;
				bdp[i] = j;
				sdp[i] = i;
			}
		}
	}
	
	printf("optimal multi transactions: \n");
	printpath(n, b, s, dp, bdp, sdp);
	printf("%d\n", dp[n]-c);
}


//main driver
int main()
{
	int n;
	scanf("%d", &n);
	int b[n], s[n];
	for (int i = 0; i < n; i++) scanf("%d", &b[i]);
	for (int i = 0; i < n; i++) scanf("%d", &s[i]);
	int c;
	scanf("%d", &c);
	
	printf("optimal single transaction: \n");
	singletrans_dc(b, s, n, c);
	singletrans(b, s, n, c);
	multitrans(b, s, n, c);
	return 0;
}
