#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Structure for point
typedef struct Point
{
    int x;
    int y;
    int id;
} point;

// Brute force solution
// TC: O(n^2)
void solve_brute(point points[], int n, int supidx[])
{
    for (int i = 0; i < n; i++)
    {
        int cnt = 0;
        for (int j = 0; j < n; j++)
        {
            if (i == j)
                continue;
            if (points[i].x > points[j].x && points[i].y > points[j].y)
                cnt++;
        }
        supidx[points[i].id] = cnt;
    }
}

// Divide and conquer solution
// TC: O(nlogn)
void solve_opt(point points[], int l, int r, int supidx[])
{
    if (l >= r)
        return;

    int mid = (l + r) >> 1;
    solve_opt(points, l, mid, supidx);
    solve_opt(points, mid + 1, r, supidx);

    for (int i = mid + 1, j = l; i <= r; i++)
    {
        while ((j <= mid) && points[j].y < points[i].y)
            j++;
        supidx[points[i].id] += (j - l);
    }

    point tmp[(r - l) + 1];
    int idx = 0, i = l, j = mid + 1;
    while (i <= mid && j <= r)
    {
        if (points[j].y > points[i].y)
            tmp[idx++] = points[i++];
        else
            tmp[idx++] = points[j++];
    }

    while (i <= mid)
        tmp[idx++] = points[i++];
    while (j <= r)
        tmp[idx++] = points[j++];

    for (idx = 0; idx <= (r - l); idx++)
        points[idx + l] = tmp[idx];
}

// Merge function for merge sort
void merge(point *points, int l, int mid, int r)
{
    point tmp[(r - l) + 1];
    int idx = 0, i = l, j = mid + 1;
    while (i <= mid && j <= r)
    {
        if (points[i].x < points[j].x)
            tmp[idx++] = points[i++];
        else
            tmp[idx++] = points[j++];
    }

    while (i <= mid)
        tmp[idx++] = points[i++];
    while (j <= r)
        tmp[idx++] = points[j++];

    for (idx = 0; idx <= (r - l); idx++)
        points[idx + l] = tmp[idx];
}

// Merge sort function
void merge_sort(point *points, int l, int r)
{
    if (l >= r)
        return;

    int mid = (l + r) / 2;
    merge_sort(points, l, mid);
    merge_sort(points, mid + 1, r);
    merge(points, l, mid, r);
}

// Driver Function
int main()
{
    int n;
    printf("Enter n: ");
    scanf("%d", &n);
    point *points = (point *)malloc(sizeof(point) * (n + 1));

    int *supidx_brute = (int *)malloc(sizeof(int) * (n + 1));
    int *supidx_opt = (int *)malloc(sizeof(int) * (n + 1));

    // Initialize both arrays with zero
    for (int i = 0; i < n; i++)
    {
        supidx_brute[i] = supidx_opt[i] = 0;
    }

    // printf("Enter n points: \n");
    // for (int i = 0; i < n; i++) {
    //	scanf("%d %d", &points[i].x, &points[i].y);
    // }

    srand(time(NULL));
    for (int i = 0; i < n; i++)
    {
        points[i].x = rand() % 1000;
        points[i].y = rand() % 1000;
        points[i].id = i;
    }

    merge_sort(points, 0, n - 1);

    // Brute force solution
    printf("Superiority of points(brute force): \n");
    solve_brute(points, n, supidx_brute);
    for (int i = 0; i < n; i++)
    {
        printf("Superiority of point (%d %d) is %d \n", points[i].x, points[i].y, supidx_brute[points[i].id]);
    }

    // Divide and conquer solution
    printf("\nSuperiority of points(Divide and conquer): \n");
    solve_opt(points, 0, n - 1, supidx_opt);
    for (int i = 0; i < n; i++)
    {
        printf("superiority of point (%d %d) is %d \n", points[i].x, points[i].y, supidx_opt[points[i].id]);
    }
    printf("\n");

    for (int i = 0; i < n; i++)
    {
        if (supidx_brute[i] != supidx_opt[i])
        {
            printf("not matching\n");
            return 0;
        }
    }

    printf("matching\n");
    return 0;
}
