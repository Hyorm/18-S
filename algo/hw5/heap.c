#include <stdio.h>

#define SZ 100

int heap[SZ];
int lastIdx = 0;

// returns the index of a smaller child of the node 'idx'
int whoIsSmaller(int idx)
{
	int leftIdx = 2 * idx;
	int rightIdx = leftIdx + 1;

	if (rightIdx > lastIdx)
	{
		return leftIdx;
	}
	if (heap[leftIdx] < heap[rightIdx])
	{
		return leftIdx;
	}
	else
	{
		return rightIdx;
	}
}


int dequeFromPQ()
{
	if (lastIdx < 1)
	{
		return -999;
	}
	int retVal = heap[1];
	heap[1] = heap[lastIdx];
	lastIdx--;

	int myIdx = 1;
	while (1)
	{
		int leftIdx = 2 * myIdx;
		int rightIdx = leftIdx + 1;

		if (leftIdx > lastIdx)  // no child
		{
			break;
		}

		int sIdx = whoIsSmaller(myIdx);

		if (heap[myIdx] < heap[sIdx])
		{
			break;
		}
		else
		{
			int temp = heap[sIdx];
			heap[sIdx] = heap[myIdx];
			heap[myIdx] = temp;
			myIdx = sIdx;
		}
	}

	return retVal;
}

void enqueToPQ(int v)
{
	lastIdx++;
	heap[lastIdx] = v;

	int myIdx = lastIdx;
	int pIdx = myIdx / 2;

	while(1)
	{
		if (pIdx < 1)
		{
			return;
		}
		if (heap[myIdx] > heap[pIdx])
		{
			return;
		}
		int temp = heap[myIdx];
		heap[myIdx] = heap[pIdx];
		heap[pIdx] = temp;
		myIdx = pIdx;
		pIdx = myIdx / 2;
	}
}

int main(void)
{
	enqueToPQ(0); // enqueue to Priority Queue
	enqueToPQ(1); // enqueue to Priority Queue
	enqueToPQ(1); // enqueue to Priority Queue
	enqueToPQ(1); // enqueue to Priority Queue
	enqueToPQ(1); // enqueue to Priority Queue
	enqueToPQ(1);

	//printf("%d %d %d\n", heap[1], heap[2], heap[3]);

	printf("%d\n", dequeFromPQ()); // should print '1'
	printf("%d\n", dequeFromPQ()); // should print '2'
	printf("%d\n", dequeFromPQ()); // should print '3'
	printf("%d\n", dequeFromPQ()); // should print '4'
	printf("%d\n", dequeFromPQ()); // should print '5'
	printf("%d\n", dequeFromPQ()); // should print '-999'
	return 0;
}


