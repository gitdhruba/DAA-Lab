#include <stdio.h>
#include<stdlib.h>
#include<time.h>

// Merge Sort
void merge(float arr[], int l, int m, int r)
{
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;
  
    // Creating temp arrays
    float L[n1], R[n2];
    for (i = 0; i < n1; i++) L[i] = arr[l + i];
    for (j = 0; j < n2; j++) R[j] = arr[m + 1 + j];
    i = j = 0;
    k = l;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        }
        else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

void mergeSort(float arr[], int l, int r)
{
    if (l < r) {
        int m = l + (r - l) / 2;
  
        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);
  
        merge(arr, l, m, r);
    }
}



void maximunOverlappingInterval(float arrl[], float exit[], int n)
{
    mergeSort(arrl, 0,n);
    mergeSort(exit, 0, n);

    int guests_in = 1, max_guests = 1;
    float time = arrl[0];
    int i = 1, j = 0;

    while (i < n && j < n)
    {
        if (arrl[i] <= exit[j])
        {
            guests_in++;
            if (guests_in > max_guests)
            {
                max_guests = guests_in;
                time = arrl[i];
            }
            i++; 
        }
        else 
        {    
            guests_in--;
            j++;

        }
    }

    printf("Maximum Number of Intervals = %d\tat Starting Time %.2f\n",max_guests , time );
}

// Driver program to test above function
int main()
{   
    int n;
    printf("Enter Number of Intervals: ");
    scanf("%d", &n);


    float arrl[n+1];
    float exit[n+1];

    srand(time(0));
    for (int i = 0; i < n; i++)
    {
        float s = (rand() % 100) / 100.0;
        float e = (rand() % 100) / 100.0;

        if (s > e)
        {
            s = s + e;
            e = s - e;
            s = s - e;
        }
        arrl[i] = s;
        exit[i] = e;
        printf("Interval %d is %.2f %.2f \n", i + 1, arrl[i],  exit[i]);
    }

    // finding number of maximum overlapping intervals and their starting time
    maximunOverlappingInterval(arrl, exit, n);
    return 0;
}
 