#include <iostream>

template<class T>
struct CBinTreeNode
{
	CBinTreeNode(T v) {
		value = v;
		nodes[0] = nodes[1] = 0;
	}
	T value;
	CBinTreeNode<T>* nodes[2];//0 left, 1 right
};

template<class T>
class CBinTree
{
public:
	CBinTree();
	~CBinTree();
	bool Find(T x, CBinTreeNode<T>**& p);
	bool Ins(T x);
	bool Rem(T x);
	bool Print(T x);
};
template<class T>
CBinTree<T>::CBinTree(){}

template<class T>
CBinTree<T>::~CBinTree(){}

template<class T>
bool CBinTree<T>::Find(T x, CBinTreeNode<T>**& p) {
	/*
	while(*p && (*p)->value != x) 
		p = (*p)->nodes[(*p)->value < x];//1 o 0 según sea v o f.
	*/
	for(; *p && (*p)->value != x; p = (*p)->nodes[(*p)->value < x])

	return *p != 0;
}

template<class T>
bool CBinTree<T>::Ins(T x) {
	CBinTreeNode<T>** p;
	if (find(x, p))return 0;//no puee haber valores repetidos
	*p = new CBinTreeNode<T>(x);
}

template<class T>
bool CBinTree<T>::Rem(T x){}

template<class T>
bool CBinTree<T>::Print(T x){}


int main() {
	return 0;
}