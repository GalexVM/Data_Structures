#include "PQ.h"
#include <iostream>
#include <functional>
using std::cout;
using std::endl;
using std::function;
PQ::PQ(vector<int> valores)
{
	arr = valores;
	n = arr.size();
	MinHeap();
}
PQ::PQ()
{
	arr = vector<int>();
	n = 0;
	MinHeap();
}
void PQ::MinHeap()
{
	HeapType = 0;
	for (auto i = n / 2 - 1; i >= 0; i--)
	{
		Heapify(&Lower, i);
	}
}
void PQ::MaxHeap()
{
	HeapType = 1;
	for (auto i = n / 2 - 1; i >= 0; i--)
	{
		Heapify(&Higher, i);
	}
}
void PQ::PrintArr()
{
	for (auto& i : arr)
	{
		cout << i << ' ';
	}cout << endl;
}
void PQ::Insert(int num)
{
	if (n == 0)
		arr.push_back(num);
	else
	{
		arr.push_back(num);
		if (HeapType == 0)
			MinHeap();
		else
			MaxHeap();
	}
	n++;
}
void PQ::Delete(int num)
{
	if (num == arr[n - 1])
	{
		arr.pop_back();
	}
	else
	{
		int i;
		for (i = 0; i < n; i++)
			if (arr[i] == num)
				break;
		swap(&arr[i], &arr[n - 1]);
		arr.pop_back();
		n--;
		if (HeapType == 0)
			MinHeap();
		else
			MaxHeap();
	}

}
int PQ::Top()
{
	return arr[0];
}
int PQ::Extract()
{
	int r = Top();
	Delete(r);
	return r;
}
void PQ::Heapify(function<int(int, int)> diff, int i)
{
	int pivot = i;
	if (2 * i + 1 < n)
		pivot = (diff(arr[i], arr[2 * i + 1])) ? i : 2 * i + 1;
	if (2 * i + 2 < n)
		pivot = (diff(arr[pivot], arr[2 * i + 2])) ? pivot : 2 * i + 2;
	if (arr[pivot] != arr[i])
	{
		swap(&arr[i], &arr[pivot]);
		Heapify(diff, pivot);
	}
}

void swap(int* a, int* b)
{
	int temp = *b;
	*b = *a;
	*a = temp;
}
bool Lower(int a, int b){ return (a < b) ? true : false; }
bool Higher(int a, int b) { return (a > b) ? true : false; }


