#pragma once
#include <vector>
#include <functional>
using std::vector;
using std::function;

void swap(int* a, int* b);
bool Lower(int a, int b); 
bool Higher(int a, int b); 


class PQ
{
public:
	vector<int> arr;
	PQ(vector<int> valores);
	PQ();
	void MinHeap();
	void MaxHeap();
	void PrintArr();
	void Insert(int num);
	void Delete(int num);
	int Top();
	int Extract();
private:
	void Heapify(function<int(int, int)> diff, int i);
	int n;
	bool HeapType;
};

