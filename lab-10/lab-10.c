#include <stdio.h>
#include <stdlib.h>

int min(int x, int y) {
	return (x <= y ? x : y);
}


typedef struct Node 
{
	int val;
	struct Node *next;
} node;

node * CreateNode(int v) {
	node * newNode = (node *)malloc(sizeof(node));
	newNode->val = v;
	newNode->next = NULL;
	return newNode;
}

void printlist(node *head) {
	node *ptr = head;
	while (ptr) {
		printf("%d ", ptr->val);
		ptr = ptr->next;
	}
	printf("\n");
}

void insert(node *head, node *new) {
	new->next = head->next;
	head->next = new;
}

int colorize(node * adj[], int i, int col[], int currcol) {
	if (col[i]!=-1) {
		if (col[i] == currcol) return 1;
		else return 0; 
	}
	
	col[i] = currcol;
	currcol ^= 1;
	int res = 1;
	for (node *nei = adj[i]->next; nei != NULL; nei = nei->next) {
		res &= colorize(adj, nei->val, col, currcol);
	}
	
	return res;
}

void findcr(node *adj[], int u, int p, int vis[], int tin[], int low[], int *tm) {
	int chld = 0;
	vis[u] = 1;
	tin[u] = low[u] = ++(*tm);
	node *ptr = adj[u]->next;
	while (ptr) {
		int v = ptr->val;
		if (!vis[v]) {
			chld++;
			findcr(adj, v, u, vis, tin, low, tm);
			low[u] = min(low[u], low[v]);
			if (p!=-1 && low[v]>=tin[u]) {
				printf("node - %d for %d\n", u, v);
			}
		}
		else if (v != p) low[u] = min(low[u], tin[v]);
		ptr = ptr->next;
	}
	
	if(p == -1 && chld >= 2) printf("node - %d for %d\n", u, p);
}

int main() 
{
	int n; scanf("%d", &n);
	node * adj[n];
	for (int i = 0; i < n; i++) adj[i] = CreateNode(-1);
	int e; scanf("%d", &e);
	for (int i = 0; i < e; i++) {
		int u, v;
		scanf("%d %d", &u, &v);
		insert(adj[u], CreateNode(v));
		insert(adj[v], CreateNode(u));
	}
	
	printf("adj: \n");
	for (int i = 0; i < n; i++) {
		printf("node %d: ", i);
		printlist(adj[i]->next);
	}
	
	printf("bipartiteness: ");
	int col[n]; int isbipar = 1;
	for (int i = 0; i < n; i++) col[i] = -1;
	for (int i = 0; i < n; i++) {
		if (col[i] == -1) {
			if (!colorize(adj, i, col, 0)) {
				isbipar = 0;
				break;
			}
		}
	}
	printf((isbipar ? "bipartite\n" : "not bipartite\n"));
	
	printf("finding critical points\n");
	int timer = 0;
	int tin[n], low[n];
	for (int i = 0; i < n; i++) {tin[i] = low[i] = -1; col[i] = 0;}
	
	for (int i = 0; i < n; i++) {
		if(col[i] == 0) findcr(adj, i, -1, col, tin, low, &timer);
	}
	
	return 0;
}
