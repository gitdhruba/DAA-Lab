#include <stdio.h>
#include <stdlib.h>

// Function to find maximum of two numbers
int max(int a, int b)
{
    return a >= b ? a : b;
}

// Function to reverse an array
void rev_arr(int *arr, int n)
{
    int i = 0, j = n - 1;
    while (i < j)
    {
        int tmp = arr[i];
        arr[i] = arr[j];
        arr[j] = tmp;
        i++;
        j--;
    }
}

// Merge Sort
// TC: O(nlogn)
void msort(int *arr, int l, int r)
{
    if (l >= r)
        return;

    int mid = (l + r) >> 1;
    msort(arr, l, mid);
    msort(arr, mid + 1, r);

    int tmp[(r - l) + 1];
    int idx = 0, i = l, j = mid + 1;
    while (i <= mid && j <= r)
    {
        if (arr[i] >= arr[j])
            tmp[idx++] = arr[i++];
        else
            tmp[idx++] = arr[j++];
    }

    while (i <= mid)
        tmp[idx++] = arr[i++];
    while (j <= r)
        tmp[idx++] = arr[j++];

    for (idx = 0; idx <= (r - l); idx++)
        arr[idx + l] = tmp[idx];
}

// Function to schedule orders(A)
// TC: O(n*k)
void schedule_orders_a(int *arr, int n, int k)
{
    int schedule[k][n + 1];
    int wait_time = 0;
    for (int i = 0; i < k; i++)
    {
        for (int j = 0; j < n; j++)
            schedule[i][j] = 0;
    }
    int time[k];
    for (int i = 0; i < k; i++)
        time[i] = 0;

    for (int i = 0; i < n; i++)
    {
        int min_time = 1000000;
        int min_idx = -1;
        for (int j = 0; j < k; j++)
        {
            if (time[j] < min_time)
            {
                min_time = time[j];
                min_idx = j;
            }
        }
        schedule[min_idx][i] = arr[i];
        wait_time += time[min_idx];
        time[min_idx] += arr[i];
    }
    int close_time = -1;
    for (int i = 0; i < k; i++)
    {
        close_time = max(close_time, time[i]);
    }
    printf("Order Schedule:\n");
    for (int i = 0; i < k; i++)
    {
        printf("Counter %d: ", i + 1);
        for (int j = 0; j < n; j++)
        {
            if (schedule[i][j] != 0)
                printf("%d ", schedule[i][j]);
        }
        printf("\n");
    }
    printf("Cafe closes at time %d\n", close_time);
    printf("Total Waiting time= %d\n", wait_time);
}

// Function to schedule orders(C)
// TC: O(nlogn + n*k)
void schedule_orders_c(int *arr, int n, int k)
{
    int schedule[k][n + 1];
    int wait_time = 0;
    for (int i = 0; i < k; i++)
    {
        for (int j = 0; j < n; j++)
            schedule[i][j] = 0;
    }
    int time[k];
    for (int i = 0; i < k; i++)
        time[i] = 0;
    int sch_idx[k];
    for (int i = 0; i < k; i++)
        sch_idx[i] = 0;

    for (int i = 0; i < n; i++)
    {
        int min_time = 1000000;
        int min_idx = -1;
        for (int j = 0; j < k; j++)
        {
            if (time[j] < min_time)
            {
                min_time = time[j];
                min_idx = j;
            }
        }
        for (int j = 0; j < n; j++)
        {
            if (schedule[min_idx][j] == 0)
            {
                schedule[min_idx][j] = arr[i];
                sch_idx[min_idx]++;
                break;
            }
        }
        time[min_idx] += arr[i];
    }
    int close_time = -1;
    for (int i = 0; i < k; i++)
    {
        close_time = max(close_time, time[i]);
    }
    printf("Order Schedule:\n");
    for (int i = 0; i < k; i++)
    {
        rev_arr(schedule[i], sch_idx[i]);
        printf("Counter %d: ", i + 1);
        for (int j = 0; j < n; j++)
        {
            if (schedule[i][j] != 0)
                printf("%d ", schedule[i][j]);
        }
        printf("\n");

        // Calculate waiting time
        int tmp = 0, sum = 0;
        for (int j = 0; j < sch_idx[i] - 1; j++)
        {
            sum += schedule[i][j];
            tmp += sum;
        }
        wait_time += tmp;
    }
    printf("Cafe closes at time %d\n", close_time);
    printf("Total Waiting time= %d\n", wait_time);
}

// Function to schedule orders(B)
// TC: O(nlogn + n*k)
void schedule_orders_b(int *arr, int n, int k)
{
    msort(arr, 0, n - 1);
    schedule_orders_a(arr, n, k);
}

// Main Function
int main()
{
    int n, k;
    printf("Enter n: ");
    scanf("%d", &n);

    printf("Enter k: ");
    scanf("%d", &k);

    int *arr = (int *)malloc(sizeof(int) * n);
    printf("Enter order processing time: ");
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &arr[i]);
    }

    printf("\nPart (a)\n");
    schedule_orders_a(arr, n, k);
    printf("\n --- \n");

    printf("\nPart (b)\n");
    schedule_orders_b(arr, n, k);
    printf("\n --- \n");

    printf("\nPart (c)\n");
    schedule_orders_c(arr, n, k);
}