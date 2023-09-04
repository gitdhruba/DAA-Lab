#include <stdio.h>
#include <stdlib.h>

int max(int a, int b)
{
    return a >= b ? a : b;
}

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
        // printf("%d \n",time[i]);
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
    printf("Closing time is %d\n", close_time);
    printf("Waiting time= %d\n", wait_time);
}

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
        time[min_idx] += arr[i];
    }
    int close_time = -1;
    for (int i = 0; i < k; i++)
    {
        // printf("%d \n",time[i]);
        close_time = max(close_time, time[i]);
    }

    int sch_idx[n];
    int new_schedule[k][n];
    for (int i = 0; i < k; i++)
    {
        for (int j = 0; j < n; j++)
        {
            new_schedule[i][j] = 0;
        }
    }
    for (int i = 0; i < k; i++)
    {
        int idx = 0;
        for (int j = 0; j < n; j++)
        {
            if (schedule[i][j] != 0)
            {
                new_schedule[i][idx++] = schedule[i][j];
            }
        }
        sch_idx[i] = idx;
    }
    printf("Order Schedule:\n");
    for (int i = 0; i < k; i++)
    {
        rev_arr(new_schedule[i], sch_idx[i]);
        printf("Counter %d: ", i + 1);
        for (int j = 0; j < n; j++)
        {
            if (new_schedule[i][j] != 0)
                printf("%d ", new_schedule[i][j]);
        }
        printf("\n");

        int curr = 0, x = 0;
        for (int j = 0; j < sch_idx[i] - 1; j++)
        {
            x += new_schedule[i][j];
            curr += x;
        }

        wait_time += curr;
    }
    printf("Closing time is %d\n", close_time);
    printf("Waiting time= %d\n", wait_time);
}

void schedule_orders_b(int *arr, int n, int k)
{
    msort(arr, 0, n - 1);
    schedule_orders_a(arr, n, k);
}

void print_schedule(int **schedule, int n, int k)
{
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
}
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

    printf("Part a\n");
    schedule_orders_a(arr, n, k);

    printf("\nPart b\n");
    schedule_orders_b(arr, n, k);

    printf("\nPart c\n");
    schedule_orders_c(arr, n, k);
}