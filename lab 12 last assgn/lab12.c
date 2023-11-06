#include <stdio.h>
#include <stdlib.h>

// Structure to store coordinates (row and column indices) as a pair
typedef struct
{
   int colidx;
   int rowidx;
} pair;

// Structure to represent the bhulbhuaiya maze
typedef struct
{
   int m, n; // Dimensions of the maze
   pair **P; // Parent pointers to store the path
   int **H;  // Horizontal walls
   int **V;  // Vertical walls
} bhul;

typedef int **path;

// Function prototypes
// Function to initialize the bhulbhuaiya maze with given dimensions
bhul initbhul(int m, int n);
// Function to print a cell based on its type
char prncell(int t);
// Function to print the bhulbhuaiya maze
void prnbhul(bhul M, int **path);
// Depth-first search algorithm to generate the bhulbhuaiya maze
void DFS(int **visited, bhul M, int i, int j);
// Function to generate the bhulbhuaiya maze
void genbhul(bhul M);
// Function to generate the path from start to target in the bhulbhuaiya maze
int **genpath(bhul M, int u, int v, int x, int y);

int main(void)
{
   // Variable declarations
   int m, n, u, v, x, y;
   bhul M;

   // User input for maze dimensions
   printf("\nm = ");
   scanf("%d", &m);
   printf("n = ");
   scanf("%d", &n);

   // Initialize the bhulbhuaiya maze
   M = initbhul(m, n);

   // Generate the maze and print the initial state
   genbhul(M);
   printf("\n+++ Random bhulbhuaiya maze generated\n");
   prnbhul(M, NULL);

   // Randomly select start and target points
   do
   {
      u = rand() % m;
      v = rand() % n;
      x = rand() % m;
      y = rand() % n;
   } while ((u == x) && (v == y));

   // Generate the path from start to target and print the maze with the path
   int **path = genpath(M, u, v, x, y);
   path[x][y] = 3; // Mark target cell in the path
   path[u][v] = 2; // Mark start cell in the path
   printf("\n+++ Path from S = (%d,%d) to T = (%d,%d)\n", u, v, x, y);
   prnbhul(M, path);

   return 0;
}

// Function to initialize the bhulbhuaiya maze with given dimensions
bhul initbhul(int m, int n)
{
   bhul M;
   int i, j;

   // Allocate memory for horizontal walls
   M.H = (int **)malloc((m - 1) * sizeof(int *));
   for (i = 0; i < m - 1; ++i)
   {
      M.H[i] = (int *)malloc(n * sizeof(int));
      for (j = 0; j < n; ++j)
         M.H[i][j] = 1;
   }

   // Allocate memory for vertical walls
   M.V = (int **)malloc(m * sizeof(int *));
   for (i = 0; i < m; ++i)
   {
      M.V[i] = (int *)malloc((n - 1) * sizeof(int));
      for (j = 0; j < n - 1; ++j)
         M.V[i][j] = 1;
   }

   // Allocate memory for parent pointers and initialize them to (-1, -1)
   M.P = (pair **)malloc(m * sizeof(pair *));
   for (i = 0; i < m; ++i)
   {
      M.P[i] = (pair *)malloc(n * sizeof(pair));
      for (j = 0; j < n; ++j)
         M.P[i][j] = (pair){-1, -1};
   }

   // Set dimensions of the maze
   M.m = m;
   M.n = n;

   return M;
}

// Function to print a cell based on its type
char prncell(int t)
{
   if (t == 1)
      return 'x'; // Wall cell
   if (t == 3)
      return 'T'; // Target cell
   if (t == 2)
      return 'S'; // Start cell
   return ' ';    // Empty cell
}

// Function to print the bhulbhuaiya maze
void prnbhul(bhul M, int **path)
{
   // Printing maze walls and cells
   int i, j;

   printf("    +");
   for (j = 0; j < M.n; ++j)
      printf("---+");
   printf("\n");
   for (i = 0; i < M.m; ++i)
   {
      printf("    |");
      if (path == NULL)
      {
         for (j = 0; j < M.n - 1; ++j)
            printf("   %c", M.V[i][j] ? '|' : ' ');
         printf("   |\n");
      }
      else
      {
         for (j = 0; j < M.n - 1; ++j)
            printf(" %c %c", prncell(path[i][j]), M.V[i][j] ? '|' : ' ');
         printf(" %c |\n", prncell(path[i][M.n - 1]));
      }
      if (i != M.m - 1)
      {
         printf("    +");
         for (j = 0; j < M.n; ++j)
            printf("%s+", M.H[i][j] ? "---" : "   ");
         printf("\n");
      }
   }
   printf("    +");
   for (j = 0; j < M.n; ++j)
      printf("---+");
   printf("\n");
}

// Depth-first search algorithm to generate the bhulbhuaiya maze
void DFS(int **visited, bhul M, int i, int j)
{
   visited[i][j] = 1;
   int d, k, m, n, u, v;

   d = rand() % 4;
   m = M.m;
   n = M.n;
   for (k = 0; k <= 3; ++k)
   {
      switch (d)
      {
      case 0:
         u = i;
         v = j - 1;
         break;
      case 2:
         u = i;
         v = j + 1;
         break;
      case 1:
         u = i - 1;
         v = j;
         break;
      case 3:
         u = i + 1;
         v = j;
         break;
      }
      if ((u >= 0) && (u < m) && (v < n) && (visited[u][v] == 0) && (v >= 0))
      {
         M.P[u][v] = (pair){i, j};
         switch (d)
         {
         case 0:
            M.V[u][v] = 0;
            break;
         case 2:
            M.V[i][j] = 0;
            break;
         case 1:
            M.H[u][v] = 0;
            break;
         case 3:
            M.H[i][j] = 0;
            break;
         }
         DFS(visited, M, u, v);
      }
      ++d;
      d %= 4;
   }
}

// Function to generate the bhulbhuaiya maze
void genbhul(bhul M)
{
   int m, n, i, j;
   int **visited;

   m = M.m;
   n = M.n;
   visited = (int **)malloc(m * sizeof(int *));
   for (i = 0; i < m; ++i)
   {
      visited[i] = (int *)malloc(n * sizeof(int));
      for (j = 0; j < n; ++j)
         visited[i][j] = 0;
   }

   j = rand() % n;
   i = rand() % m;
   DFS(visited, M, i, j);
}

// Function to generate the path from start to target in the bhulbhuaiya maze
path genpath(bhul M, int u, int v, int x, int y)
{
   int m, n, i, j;
   path p;
   pair t;

   m = M.m;
   n = M.n;
   p = (int **)malloc(m * sizeof(int *));
   for (i = 0; i < m; ++i)
   {
      p[i] = (int *)malloc(n * sizeof(int));
      for (j = 0; j < n; ++j)
         p[i][j] = 0;
   }

   t = (pair){u, v};
   while (t.rowidx >= 0)
   {
      p[t.rowidx][t.colidx] = 1;
      t = M.P[t.rowidx][t.colidx];
   }

   t = (pair){x, y};
   while (p[t.rowidx][t.colidx] == 0)
   {
      p[t.rowidx][t.colidx] = 1;
      t = M.P[t.rowidx][t.colidx];
   }

   t = M.P[t.rowidx][t.colidx];
   while (t.rowidx >= 0)
   {
      p[t.rowidx][t.colidx] = 0;
      t = M.P[t.rowidx][t.colidx];
   }

   return p;
}
