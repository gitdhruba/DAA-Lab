#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Structure for interval
typedef struct itv
{
  float start;
  float end;
} itv;

// Generate random intervals
void generate_intervals(itv *arr, int n)
{
  for (int i = 0; i < n; i++)
  {
    float start = (float)(rand() % 100) / (float)(100);
    float end = (float)(rand() % 100) / (float)(100);
    if (end < start)
    {
      float temp = start;
      start = end;
      end = temp;
    }
    arr[i].start = start;
    arr[i].end = end;
  }
}

// Merge Function
void merge(itv *arr, int l, int r, int mid)
{
  itv temp[r - l + 1];
  int i = l, j = mid + 1, k = 0;
  while (i <= mid && j <= r)
  {
    if (arr[i].start < arr[j].start)
    {
      temp[k] = arr[i];
      k++;
      i++;
    }
    else if (arr[j].start < arr[i].start)
    {
      temp[k] = arr[j];
      k++;
      j++;
    }
    else if (arr[i].end < arr[j].end)
    {
      temp[k] = arr[i];
      k++;
      i++;
    }
    else
    {
      temp[k] = arr[j];
      k++;
      j++;
    }
  }

  while (i <= mid)
  {
    temp[k] = arr[i];
    i++;
    k++;
  }
  while (j <= r)
  {
    temp[k] = arr[j];
    j++;
    k++;
  }
  for (int k = 0; k <= (r - l); k++)
  {
    arr[l + k] = temp[k];
  }
}

// Merge Sort Function
void merge_sort(itv *arr, int l, int r)
{
  if (l >= r)
    return;

  int mid = l + (r - l) / 2;
  merge_sort(arr, l, mid);
  merge_sort(arr, mid + 1, r);
  merge(arr, l, r, mid);
}

// Display Intervals
void display_intervals(itv *arr, int n)
{
  for (int i = 0; i < n; i++)
  {
    printf("Interval No. %d : [%.2f,%.2f] \n", i + 1, arr[i].start, arr[i].end);
  }
}

int main()
{
  int n;
  printf("Enter numbr of intervals: ");
  scanf("%d", &n);
  srand(time(0));

  // Generate Intervals
  itv *arr = (itv *)malloc((n + 1) * sizeof(itv));
  generate_intervals(arr, n);

  // Display Intervals
  // display_intervals(arr,n);
  merge_sort(arr, 0, n - 1);

  // Display after merge sort
  display_intervals(arr, n);

  // Find maximum overlapping intervals and their starting time
  float start = arr[0].start, end = arr[0].end, globalstart = 0, globalend = 0;
  int maxcount = 0, curcount = 1;
  // printf("%f,%f \n",start,end);
  for (int i = 1; i < n; i++)
  {
    float curstart = arr[i].start;
    float curend = arr[i].end;
    if (curstart >= end || (i == n - 1))
    {
      if (maxcount <= curcount)
      {
        globalstart = start;
        globalend = end;
        maxcount = curcount;
      }
      start = curstart;
      end = curend;
      curcount = 1;
    }
    else
    {
      curcount++;
      start = (curstart > start) ? curstart : start;
      end = (curend < end) ? curend : end;
    }
    // printf("(%f,%f) %d %d \n",start,end,curcount,maxcount);
  }

  printf("\nMaximum overalpping intervals: %d \n", maxcount);
  printf("starting time: %f \n", globalstart);
  printf("Overalpping intervals are: \n");

  for (int i = 0; i < n; i++)
  {
    if (arr[i].start <= globalstart && arr[i].end >= globalend)
    {
      printf("Interval: %d [%.2f,%.2f] \n", i + 1, arr[i].start, arr[i].end);
    }
  }
  return 0;
}