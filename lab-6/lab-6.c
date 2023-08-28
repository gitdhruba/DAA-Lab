/*
    Author : Dhruba Sinha(21CS8051)
    @ GNU/Linux Users' Group , NIT DGP
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct Point 
{
	int x, y;
	int id;
};

typedef struct Point point;

int compslope(point p, point q) {
	return ((p.y * q.x) <= (p.x * q.y) ? 1 : 0);
}


void findsuperiority_brute(point points[], int n, int supidx[]) {
	for (int i = 0; i < n; i ++) {
		int cnt = 0;
		for (int j = 0; j < n; j ++) {
			if(i == j) continue;
			
			if(points[i].x > points[j].x && points[i].y > points[j].y) cnt ++;
		}
		
		supidx[points[i].id] = cnt;
    }
}

void findsuperiority_opt(point points[], int l, int r, int supidx[]) {
	if (l >= r) return;
	
	int mid = (l + r) >> 1;
	findsuperiority_opt(points, l, mid, supidx);
	findsuperiority_opt(points, mid + 1, r, supidx);
	
	for (int i = mid+1, j = l; i <= r; i++) {
		while ((j<=mid) && points[j].y<points[i].y) j++;
		supidx[points[i].id] += (j - l);
	}
	
	point tmp[(r-l) + 1];
	int idx = 0, i = l, j = mid+1;
	while(i<=mid && j<=r) {
		if(points[j].y>points[i].y) tmp[idx++] = points[i++];
		else tmp[idx++] = points[j++];
	}
	
	while(i <= mid) tmp[idx++] = points[i++];
	while(j <= r) tmp[idx++] = points[j++];
	
	for (idx = 0; idx <= (r-l); idx++) points[idx + l] = tmp[idx];
}


void msort(point points[], int l, int r) {
	if (l >= r) return;
	
	int mid = (l + r) >> 1;
	msort(points, l, mid);
	msort(points, mid + 1, r);
	
	point tmp[(r-l) + 1];
	int idx = 0, i = l, j = mid+1;
	while(i<=mid && j<=r) {
		if(points[i].x < points[j].x) tmp[idx++] = points[i++];
		else tmp[idx++] = points[j++];
	}
	
	while(i <= mid) tmp[idx++] = points[i++];
	while(j <= r) tmp[idx++] = points[j++];
	
	for (idx = 0; idx <= (r-l); idx++) points[idx + l] = tmp[idx];
}


int main() 
{
	int n;
	scanf("%d", &n);
	point points[n];
	int supidx_opt[n], supidx_brute[n];
	for (int i = 0; i < n; i++) supidx_brute[i] = supidx_opt[i] = 0;
	
	srand(time(NULL));
	//for (int i = 0; i < n; i++) scanf("%d %d", &points[i].x, &points[i].y);
	for (int i = 0; i < n; i++) {
		points[i].x = rand() % 5000;
		points[i].y = rand() % 5000;
		points[i].id = i;
	}
	
	msort(points, 0, n-1);
	
	printf("superiority using bruteforce: \n");
	findsuperiority_brute(points, n, supidx_brute);
	
	printf("\nsuperiority using D&C: \n");
	findsuperiority_opt(points, 0, n-1, supidx_opt);
	for (int i = 0; i < n; i++) printf("superiority of point (%d %d) id %d is %d \n", points[i].x, points[i].y, points[i].id, supidx_opt[points[i].id]);
	printf("\n");
	
	for (int i = 0; i < n; i++) {
		if(supidx_brute[i] != supidx_opt[i]) {
			printf("not matching\n");
			return 0;
		}
	}
	
	printf("matching\n");
	return 0;
}	
