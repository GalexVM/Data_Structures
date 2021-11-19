#include<iostream>
using std::cout;
using std::endl;
#include<list>
using std::list;


struct CFd1 
{
	inline unsigned long operator()(int x) {
		return x+1;
	}
};

template<class T,class S,class Fd,unsigned long Sz>//tipo de dato, tipo de estructura auxiliar, función dispersión, size
class CHashTable 
{
public:
	CHashTable();
	~CHashTable();
	bool Find(T v);
	bool Ins(T v);
	bool Rem(T v);
	void PrintGraph();
	S* table;
	Fd fd;
};
template<class T, class S, class Fd, unsigned long Sz>
CHashTable<T, S, Fd, Sz>::CHashTable() {
	table = new S[Sz];
}
template<class T, class S, class Fd, unsigned long Sz>
CHashTable<T, S, Fd, Sz>::~CHashTable() {
	delete[] table;
}
template<class T, class S, class Fd, unsigned long Sz>
bool CHashTable<T, S, Fd, Sz>::Find(T v) {
	
	S& l = table[fd(v) % Sz];
	typename S::iterator i;// C++ lo pide así
	for (i = l.begin(); i != l.end(); ++i)
		if (v == *i)
			return 1;
	return 0;
}
template<class T, class S, class Fd, unsigned long Sz>
bool CHashTable<T, S, Fd, Sz>::Ins(T v) {
	/*Recibo un valor del conjunto, se tiene que pasar
	a la función de dispersión, e insertar el valor que
	devuelva en la estructura de datos*/
	table[fd(v) % Sz].push_back(v);
	return 1;
}
template<class T, class S, class Fd, unsigned long Sz>
bool CHashTable<T, S, Fd, Sz>::Rem(T v) {
	table[fd(v) % Sz].remove(v);
	return 0;
}

template<class T, class S, class Fd, unsigned long Sz>
void CHashTable<T, S, Fd, Sz>::PrintGraph() {
	cout << "graph:\n";
	for (int i = 0; i < Sz; ++i) {
		typename S::iterator it1;
		S& l = table[i];
		cout << i << ": ";
		for (it1 = l.begin(); it1 != l.end(); ++it1) {
			cout << '#';
		}cout << endl;
	}
	
}

int main() {
	CHashTable<int, list<int>, CFd1, 19> ht;
	ht.Ins(11);
	ht.Find(11);
	ht.Ins(8);
	ht.Ins(4);
	ht.Ins(9);
	ht.Ins(1);
	ht.Ins(2);
	ht.Ins(3);
	ht.Ins(5);
	ht.Ins(6);
	ht.Ins(7);
	ht.Ins(10);
	ht.Ins(11);
	ht.Ins(12);
	ht.Ins(13);
	ht.Rem(8);
	ht.PrintGraph();
	
}
