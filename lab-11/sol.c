/*
      Author: Dhruba Sinha
      @ GNU/Linux Users' Group, NIT DGP
*/

#include <stdio.h>
#include <stdlib.h>

int abs(int x) {
	return (x >= 0 ? x : -x);
}

int max(int x, int y) {
	return (x >= y ? x : y);
}


typedef struct Node 
{
	int val, w;
	struct Node *next;
} node;

typedef struct Ans {
	int u, v;
	int gamma;
} ans;

node * CreateNode(int v, int cost) {
	node * newNode = (node *)malloc(sizeof(node));
	newNode->val = v;
	newNode->w = cost;
	newNode->next = NULL;
	return newNode;
}

void printlist(node *head) {
	node *ptr = head;
	while (ptr) {
		printf("(%d %d) ", ptr->val, ptr->w);
		ptr = ptr->next;
	}
	printf("\n");
}

void insert(node *head, node *new) {
	new->next = head->next;
	head->next = new;
}

int dfs(node *adj[], int i, int vis[], int w[], ans *answ) {
	vis[i] = 1;
	
	int subw = 0;
	int curr = 0;
	for (node *nei = adj[i]->next; nei != NULL; nei = nei->next) {
		if(!vis[nei->val]) {
			curr = dfs(adj, nei->val, vis, w, answ);
			int currgm = nei->w - abs(w[0] - curr - curr);
			if (answ->gamma < currgm) {
				answ->gamma = currgm;
				answ->u = i;
				answ->v = nei->val;
			}
			
			subw += curr;
		}
	}
	
	return (w[i] + subw);
}

int accumw(node *adj[], int i, int p, int w[]) {
	int curr = 0;
	for (node *nei = adj[i]->next; nei != NULL; nei = nei->next) {
		if (nei->val == p) continue;
		curr += accumw(adj, nei->val, i, w);
	}
	
	return (curr + w[i]);
}


int main() 
{
	int n; scanf("%d", &n);
	node * adj[n+1];
	for (int i = 0; i <= n; i++) adj[i] = CreateNode(-1, -1);
	int w[n+1];
	for (int i = 1; i <= n; i++) scanf("%d", &w[i]);
	for (int i = 1; i < n; i++) {
		int u, v, c;
		scanf("%d %d %d", &u, &v, &c);
		insert(adj[u], CreateNode(v, c));
		insert(adj[v], CreateNode(u, c));
	}
	
	printf("adj: \n");
	for (int i = 1; i <= n; i++) {
		printf("node %d: w = %d --> ", i, w[i]);
		printlist(adj[i]->next);
	}
	
	printf("\nO(n) sol: \n");
	w[0] = 0;
	for (int i = 1; i <= n; i++) w[0] += w[i];
	int vis[n+1];
	for (int i = 1; i <= n; i++) vis[i] = 0;
	ans answ = {-1, -1, -1e9};
	dfs(adj, 1, vis, w, &answ);
	
	printf("max gamma : %d for edge (%d %d)\n", answ.gamma, answ.u, answ.v);
	
	printf("\nO(n^2) sol: \n");
	answ.gamma = -1e9;
	for (int i = 1; i <= n; i++) {
		for (node *nei = adj[i]->next; nei != NULL; nei = nei->next) {
			int x1 = accumw(adj, i, nei->val, w);
			int x2 = accumw(adj, nei->val, i, w);
			int currgm = nei->w - abs(x1 - x2);
			if (answ.gamma < currgm) {
				answ.gamma = currgm;
				answ.u = i;
				answ.v = nei->val;
			}
		}
	}
	
	printf("max gamma : %d for edge (%d %d)\n", answ.gamma, answ.u, answ.v);
	return 0;
}
