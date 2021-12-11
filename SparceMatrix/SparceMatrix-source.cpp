#include<iostream>
using std::cout;
using std::endl;
#include <vector>
using std::vector;

template<class T>
class SparceMatrixNode 
{
public:
	SparceMatrixNode(T v, int cX, int cY);
	~SparceMatrixNode();
	T value;
	int coords[2] = { 0,0 };
	SparceMatrixNode<T>* next[2] = { 0,0 };//X-Y
};

template<class T>
class SparceMatrixList 
{
private:
	SparceMatrixNode<T>* head;
	
public:
	bool dirección;
	SparceMatrixList(int n);
	~SparceMatrixList();
	bool FindNode(SparceMatrixNode<T>* n, SparceMatrixNode<T>**& p);
	bool FindNode(int c, SparceMatrixNode<T>**& p);
	bool InsNode(SparceMatrixNode<T>* n);
	bool RemNode(SparceMatrixNode<T>* n);
	void Print();
};

template<int SzX, int SzY, class T, T N>
class SparceMatrix 
{
private:
	void Ins(int c1, int c2, T v);
	void Rm(int c1, int c2);
	vector<SparceMatrixList<T>> edgeX;
	vector<SparceMatrixList<T>> edgeY;

public:
	SparceMatrix();
	~SparceMatrix();
	T Get(int c1, int c2);
	void Set(int c1, int c2, T v);
	void Print();
	
};

template<int SzX, int SzY, class T, T N>
SparceMatrix<SzX, SzY, T, N>::SparceMatrix()
{
	for (int i = 0; i < SzX; ++i)
	{
		SparceMatrixList<T>* a = new SparceMatrixList<T>(0);
		edgeX.push_back(*a);
	}
		
	for (int i = 0; i < SzY; ++i)
	{
		SparceMatrixList<T>* a = new SparceMatrixList<T>(1);
		edgeY.push_back(*a);
	}
		
}

template<int SzX, int SzY, class T, T N>
SparceMatrix<SzX, SzY, T, N>::~SparceMatrix()
{
	//...
}

template<int SzX, int SzY, class T, T N>
T SparceMatrix<SzX, SzY, T, N>::Get(int c1, int c2)
{
	SparceMatrixNode<T>** p;
	if (c2 > c1)
	{
		if (edgeX[c2].FindNode(c1, p))
			return (*p)->value;
		return N;
	}
	else
	{
		if (edgeY[c1].FindNode(c2, p))
			return (*p)->value;
		return N;
	}
}
template<int SzX, int SzY, class T, T N>
void SparceMatrix<SzX, SzY, T, N>::Set(int c1, int c2, T v)
{
	if (v == N) {
		Rm(c1, c2);
		return;
	}

	SparceMatrixNode<T>** p;
	if (c2 > c1)
	{
		if (edgeX[c2].FindNode(c1, p))
		{
			//cout << "a " << v << endl;
			(*p)->value = v;
			return;
		}
		Ins(c1, c2, v);
	}
	else
	{
		if (edgeY[c1].FindNode(c2, p))
		{
			//cout << "b " << v << endl;
			(*p)->value = v;
			return;
		}
		Ins(c1, c2, v);
	}
}
template<int SzX, int SzY, class T, T N>
void SparceMatrix<SzX, SzY, T, N>::Print()
{
	cout << "Edge X:\n";
	for(int i = 0; i < SzX; ++i)
	{
		cout << i << ": ";
		edgeX[i].Print();
	}
	cout << endl;
	cout << "Edge Y:\n";
	for (int i = 0; i < SzY; ++i)
	{
		cout << i << ": ";
		edgeY[i].Print();
	}
	cout << endl;
}
template<int SzX, int SzY, class T, T N>
void SparceMatrix<SzX, SzY, T, N>::Rm(int c1, int c2)
{
	SparceMatrixNode<T>** p;
	SparceMatrixNode<T>** q;
	
	if (!(edgeX[c1].FindNode(c2, p)))
	{
		cout << "Error, valor no anexado en ambos ejes\n";
		return;
	}
	edgeX[c1].RemNode(*p);
	//edgeY[c2].RemNode(*q);
	delete (*p);
}
template<int SzX, int SzY, class T, T N>
void SparceMatrix<SzX, SzY, T, N>::Ins(int c1, int c2, T v)
{
	SparceMatrixNode<T>* n = new SparceMatrixNode<T>(v, c1, c2);
	//cout << "Agregando valor " << n->value << endl;
	//cout << "c2:" << c2 << endl;
	edgeX[c2].InsNode(n);
	edgeY[c1].InsNode(n);
}
//list
template<class T>
SparceMatrixList<T>::SparceMatrixList(int n)
{
	dirección = n;
	//cout << dirección << endl;
	head = 0;
}
template<class T>
SparceMatrixList<T>::~SparceMatrixList()
{
//...		
}

template<class T>
bool SparceMatrixList<T>::FindNode(SparceMatrixNode<T>* n, SparceMatrixNode<T>**& p)
{
	for (p = &head; *p && (*p)->value < n->value; p = &(*p)->next[dirección]);//Recorre entre puntero y puntero
	return *p && (*p)->value == n->value;
}

template<class T>
bool SparceMatrixList<T>::FindNode(int c, SparceMatrixNode<T>**& p)
{
	for (p = &head; *p; p = &(*p)->next[dirección])
		if ((*p)->coords[dirección] == c)//dirección devuelve la coord del eje contrario (c)
			return true;
	return false;
}

template<class T>
bool SparceMatrixList<T>::InsNode(SparceMatrixNode<T>* n)
{
	SparceMatrixNode<T>** p;
	if (FindNode(n, p))return 0;
	//cout << "no se encontro el nodo\n";
	//cout << "direccion:" << dirección << endl;
	n->next[dirección] = *p;
	*p = n;
	return 1;
}
template<class T>
bool SparceMatrixList<T>::RemNode(SparceMatrixNode<T>* n)
{
	SparceMatrixNode<T>** p;
	if (!FindNode(n, p))return 0;
	*p = n->next[dirección];
	return 1;
}
template<class T>
void SparceMatrixList<T>::Print()
{
	SparceMatrixNode<T>** p;
	cout << '[';
	if (head)
		for (p = &head; *p; p = &(*p)->next[dirección])
			cout << (*p)->value << ' ';
	cout << ']' << endl;
}
//node
template<class T>
SparceMatrixNode<T>::SparceMatrixNode(T v, int cX, int cY)
{
	value = v;
	coords[0] = cX;
	coords[1] = cY;
	next[0] = 0;
	next[1] = 0;
}
template<class T>
SparceMatrixNode<T>::~SparceMatrixNode()
{
	//...
}
int main(){
	SparceMatrix<3, 3, int, 0> mat1;
	mat1.Set(0, 0, 1);
	mat1.Set(0, 1, 2);
	mat1.Set(0, 2, 3);
	mat1.Set(1, 0, 4);
	mat1.Set(1, 1, 5);
	mat1.Set(1, 2, 6);
	mat1.Set(2, 0, 7);
	mat1.Set(2, 1, 8);
	mat1.Set(2, 2, 9);

	cout << mat1.Get(0, 0) << endl;
	cout << mat1.Get(0, 1) << endl;
	cout << mat1.Get(0, 2) << endl;
	cout << mat1.Get(1, 0) << endl;
	cout << mat1.Get(1, 1) << endl;
	cout << mat1.Get(1, 2) << endl;
	cout << mat1.Get(2, 0) << endl;
	cout << mat1.Get(2, 1) << endl;
	cout << mat1.Get(2, 2) << endl;



	mat1.Print();
	return 0;
}
//TODO: hacer que el atributo dirección funcione , crear de forma adecuada los vectores
//TODO: revisar si con eso se soluciona el bug del Rm



