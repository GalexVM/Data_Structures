//ordenada
//no acepta repeticiones
//solo tiene next->
#include <iostream>


template<class T>
struct CForwardNode
{
	CForwardNode(T x) {
		value = x;
		next = 0;
	}
	T value;
	CForwardNode<T>* next;

};

template<class T>
class CForwardList
{
public:
	CForwardList();
	~CForwardList();
	bool Find(T x, CForwardNode<T>**& p);
	bool Ins(T x);
	bool Rem(T x);
	void Print();
private:
	CForwardNode<T>* head;
};

template<class T>
CForwardList<T>::CForwardList() {
	head = 0;
}

template<class T>
bool CForwardList<T>::Find(T x, CForwardNode<T>**& p) {

	for(p = &head; *p && (*p)->value < x; p = &(*p)->next )
	return *p && (*p)->value == x;

}

template<class T>
bool  CForwardList<T>::Ins(T x) {
	CForwardNode<T>** p;
	if (Find(x, p))return 0;
	CForwardNode<T>* t = new CForwardNode<T>(x);
	t->next = *p;
	*p = t;
	return 1;
}

template<class T>
bool  CForwardList<T>::Rem(T x) {
	
	CForwardNode<T>** p;
	if (!Find(x, p)) return 0;
	CForwardNode<T>* t = *p;
	*p = t->next;
	delete t;
	return 1;


}

template<class T>
void CForwardList<T>::Print() {
	for (CForwardNode<T>* t = head; t != 0; t = t->next) {
		std::cout << t->value << " ";
	}
}

template<class T>
CForwardList<T>::~CForwardList() {
 
}

int main() {
	CForwardList<int> list1;
	list1.Ins(9);
	list1.Ins(10);
	list1.Ins(11);
	list1.Ins(15);
	list1.Ins(15);
	list1.Print();
}