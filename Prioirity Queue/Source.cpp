#include <iostream>
#include <vector>
#include <functional>
#include "PQ.h"
using namespace std;

int main()
{
	vector<int> a{ 3,9,2,1,4,5 };
	PQ hp1(a);
	hp1.PrintArr();
	hp1.MaxHeap();
	hp1.PrintArr();
	hp1.MinHeap();
	hp1.PrintArr();
	hp1.Insert(10);
	hp1.MaxHeap();
	hp1.PrintArr();
	hp1.Delete(5);
	hp1.PrintArr();
	cout << hp1.Top() <<endl;
	cout << hp1.Extract() <<endl;
	hp1.PrintArr();
	return 0;
}

