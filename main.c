#include <stdio.h>
#include <stdlib.h>

typedef struct process
{
    int id;
    int arrival;
    int burst;
} process;

int fcfs(/* in */ process*, /* in */ int, /* out */ float*, /* out */ float*); 

int main()
{
    int n, i;
	float avrActiveTime = 0, avrWaitingTime = 0;
    process* arr;

    printf("Enter the number of processes: ");
    scanf("%d", &n);
	arr = (process*)malloc(n * sizeof(process));

    for(i = 0; i < n; i++)
    {
        arr[i].id = i;
        printf("Enter process %d Arrival time: ", arr[i].id);
        scanf("%d", &(arr[i].arrival));
        printf("Enter process %d CPU Burst: ", arr[i].id);
        scanf("%d", &(arr[i].burst));
		printf("\n");
    }

	fcfs(arr, n, &avrActiveTime, &avrWaitingTime);

    printf("Average Active Time: %.2f\nAverage Waiting Time: %.2f\n", avrActiveTime, avrWaitingTime);
	getchar();
	getchar();
    
	free(arr);
    return 0;
}

int swap(process* a, process* b)
{
	process t = *a;
	*a = *b;
	*b = t;
	return 0;
}

int partition(process* arr, int start, int end)
{
	process pivot = arr[end];
	int i;
	int j = start;

	for (i = start; i < end; i++) {
		if (arr[i].arrival < pivot.arrival) {
			swap(arr + i, arr + j);
			j++;
		}
	}

	swap(arr + j, arr + end);
	return j;
}

int quickSort(process* arr, int low, int high)
{
	if (low < high) {
		int pi = partition(arr, low, high);
		
		quickSort(arr, low, pi - 1);
		quickSort(arr, pi + 1, high);
	}
	return 0;
}

int sort(process* arr, int n)
{
    return quickSort(arr, 0, n - 1);
}

int fcfs(/* in */ process* arr, /* in */ int n, /* out */ float* avrActiveTime, /* out */ float* avrWaitingTime) {
	int i, activeTime, waitingTime, timeline = 0;

	if (sort(arr, n) != 0) {
		return -1;
	}

	printf("Process\t\tArrival Time\tBurst Time\tActive Time\tWaiting Time\n");
    for(i = 0; i < n; i++)
    {
		if(arr[i].arrival > timeline)
		{
			timeline = arr[i].arrival;
		}

        timeline += arr[i].burst;

        activeTime = timeline - arr[i].arrival;
        waitingTime = activeTime - arr[i].burst;
        *avrActiveTime += activeTime;
        *avrWaitingTime += waitingTime;
        printf("%7d\t%20d\t%10d\t%11d\t%12d\n", arr[i].id, arr[i].arrival, arr[i].burst, activeTime, waitingTime);
    }

	*avrActiveTime /= n;
	*avrWaitingTime /= n;

	return 0;
}