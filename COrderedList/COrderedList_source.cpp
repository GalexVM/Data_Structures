//ordenada
//no acepta repeticiones
//solo tiene next->
#include <iostream>

template<class T>
class COrderedList {
public:
	bool Find(T x, CNode<T>**& p);
	bool Ins(T x);
	bool Rem(T x);
};

