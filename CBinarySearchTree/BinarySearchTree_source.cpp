#include <iostream>
#include <queue>
#include <list>
using namespace std;


template<class T>
struct CLess
{
    inline bool operator()(T a, T b)
    {
        return a < b;
    }
};

template<class T>
struct CGreater
{
    inline bool operator()(T a, T b)
    {
        return a > b;
    }
};

template <class T>
struct CBinTreeNode
{
    CBinTreeNode(T v)
    {
        value = v;
        nodes[0] = nodes[1] = 0;
    }
    T value;
    CBinTreeNode<T>* nodes[2]; //0 left, 1 right
};

template <class T, class C>
class CBinTree
{
public:
    CBinTree();
    ~CBinTree();
    CBinTreeNode<T>* Root();
    bool Find(T x, CBinTreeNode<T>**& p);
    bool Ins(T x);
    bool Rem(T x);
    CBinTreeNode<T>** Rep(CBinTreeNode<T>** p);
    void InOrder(CBinTreeNode<T>* n);
    void PreOrder(CBinTreeNode<T>* n);
    void PosOrder(CBinTreeNode<T>* n);
    void ReverseOrder(CBinTreeNode<T>* n);
    void InversePosOrder(CBinTreeNode<T>* n);
    void LevelOrder(CBinTreeNode<T>* n);
    int MaxDepth(CBinTreeNode<T>* n);
    void FindAVL_L_R(CBinTreeNode<T>* n);
    void FindAVL_R_L(CBinTreeNode<T>* n);
    bool ALVNeed(CBinTreeNode<T>* n);
    void ALV(CBinTreeNode<T>* n);
    void SeparateLevels(list<T>* mat, CBinTreeNode<T>* n);
    void PrintNiveles(list<T>* mat);
    void Print();
   

private:
    CBinTreeNode<T>* root;
    bool brep;
    C cmp;
};

template <class T, class C>
CBinTree<T, C>::CBinTree()
{
    root = 0;
    brep = 0;
}

template <class T, class C>
CBinTree<T, C>::~CBinTree()
{
    delete[] root;
}

template <class T, class C>
CBinTreeNode<T>* CBinTree<T, C>::Root()
{
    return root;
}

template <class T, class C>
bool CBinTree<T, C>::Find(T x, CBinTreeNode<T>**& p)
{
    for (p = &root;
        *p && (*p)->value != x;
        p = &((*p)->nodes[cmp((*p)->value, x)])
        );
    return *p != 0;
}

template <class T, class C>
bool CBinTree<T, C>::Ins(T x)
{
    CBinTreeNode<T>** p;
    if (Find(x, p)) return 0;
    *p = new CBinTreeNode<T>(x);
    if ((*p)->value < root->value)
        FindAVL_L_R(root);
    else
        FindAVL_R_L(root);
    return 1;
}
template <class T, class C>
void CBinTree<T, C>::FindAVL_L_R(CBinTreeNode<T>* n) {
    if (!n) return;
    FindAVL_L_R(n->nodes[0]);
    FindAVL_L_R(n->nodes[1]);
    if (ALVNeed(n)) ALV(n);
}
template <class T, class C>
void CBinTree<T, C>::FindAVL_R_L(CBinTreeNode<T>* n) {
    if (!n) return;
    FindAVL_L_R(n->nodes[1]);
    FindAVL_L_R(n->nodes[0]);
    if (ALVNeed(n)) ALV(n);
}
template<class T, class C>
bool CBinTree<T, C>::ALVNeed(CBinTreeNode<T>* n){
    cout << "maxdepth: " << n->value << "->" << MaxDepth(n->nodes[1]) + 1 - (MaxDepth(n->nodes[0]) + 1) << endl;
    if (MaxDepth(n->nodes[1]) + 1 - (MaxDepth(n->nodes[0]) + 1) >= 2 ||
        MaxDepth(n->nodes[1]) + 1 - (MaxDepth(n->nodes[0]) + 1) <= -2) 
        return true;
    return false;
}
template<class T, class C>
void CBinTree<T, C>::ALV(CBinTreeNode<T>* n){
   
    if ((!n->nodes[0] || MaxDepth(n->nodes[1]) > MaxDepth(n->nodes[0]) ) &&(
        !n->nodes[1]->nodes[0] || 
        MaxDepth(n->nodes[1]->nodes[1]) > MaxDepth(n->nodes[1]->nodes[0])))//tipo 1
    {
        cout << "tipo1\n";
        CBinTreeNode<T>* aux1 = n;
        CBinTreeNode<T>* aux2 = n->nodes[1];
        aux1->nodes[1] = aux2->nodes[0];
        aux2->nodes[0] = aux1;
        Print();

        CBinTreeNode<T>** p = &root;
        for (p = &root;
            *p && (*p)==aux1;
            p = &((*p)->nodes[cmp((*p)->value, aux1->value)])
            );
        cout << (*p)->value << endl;
        *p = aux2;
      
    }
    else if ((!n->nodes[0] || MaxDepth(n->nodes[1]) > MaxDepth(n->nodes[0])) &&(
        !n->nodes[1]->nodes[1] ||
        MaxDepth(n->nodes[1]->nodes[0]) > MaxDepth(n->nodes[1]->nodes[1])))//tipo 4
    {
        cout << "tipo4\n";
        CBinTreeNode<T>* aux1 = n;
        CBinTreeNode<T>* aux2 = n->nodes[1];
        CBinTreeNode<T>* aux3 = n->nodes[1]->nodes[0];

        aux1->nodes[1] = aux3->nodes[0];
        aux2->nodes[0] = aux3->nodes[1];
        aux3->nodes[0] = aux1;
        aux3->nodes[1] = aux2;

        CBinTreeNode<T>** p = &root;
        for (p = &root;
            *p && ((*p)->nodes[0] == aux1 || (*p)->nodes[1] == aux1);
            p = &((*p)->nodes[cmp((*p)->value, n->value)])
            );

        if ((*p)->nodes[0] == aux1)
            (*p)->nodes[0] = aux3;
        else if ((*p)->nodes[1] == aux1)
            (*p)->nodes[1] = aux3;

    }
    else if ((!n->nodes[1] || MaxDepth(n->nodes[0]) > MaxDepth(n->nodes[1])) &&(
        !n->nodes[0]->nodes[1] ||
        MaxDepth(n->nodes[0]->nodes[0]) > MaxDepth(n->nodes[0]->nodes[1])))//tipo 3
    {
        cout << "tipo3\n";
        CBinTreeNode<T>* aux1 = n;
        CBinTreeNode<T>* aux2 = n->nodes[0];
        CBinTreeNode<T>* aux3 = n->nodes[0]->nodes[1];

        aux1->nodes[0] = aux3->nodes[1];
        aux2->nodes[1] = aux3->nodes[0];
        aux3->nodes[0] = aux1;
        aux3->nodes[1] = aux2;

        CBinTreeNode<T>** p = &root;
        for (p = &root;
            *p && ((*p)->nodes[0] == aux1 || (*p)->nodes[1] == aux1);
            p = &((*p)->nodes[cmp((*p)->value, n->value)])
            );

        if ((*p)->nodes[0] == aux1)
            (*p)->nodes[0] = aux3;
        else if ((*p)->nodes[1] == aux1)
            (*p)->nodes[1] = aux3;

    }
    else if ((!n->nodes[1] || MaxDepth(n->nodes[0]) > MaxDepth(n->nodes[1])) &&(
        !n->nodes[0]->nodes[0] ||
        MaxDepth(n->nodes[0]->nodes[1]) > MaxDepth(n->nodes[0]->nodes[0])))//tipo 2
    {
        cout << "tipo2\n";
        CBinTreeNode<T>* aux1 = n;
        CBinTreeNode<T>* aux2 = n->nodes[0];
        (aux1)->nodes[0] = n->nodes[0]->nodes[1];

        CBinTreeNode<T>** p = &root;
        for (p = &root;
            *p && ((*p)->nodes[0] == n || (*p)->nodes[1] == n);
            p = &((*p)->nodes[cmp((*p)->value, n->value)])
            );

        if ((*p)->nodes[0] == aux1)
            (*p)->nodes[0] = aux2;
        else if ((*p)->nodes[1] == aux1)
            (*p)->nodes[1] = aux2;

    }
}
template <class T, class C>
bool CBinTree<T, C>::Rem(T x)
{
    CBinTreeNode<T>** p;
    if (!Find(x, p)) return 0;
    if ((*p)->nodes[0] && (*p)->nodes[1])
    {
        CBinTreeNode<T>** q = Rep(p);
        (*p)->value = (*q)->value;
        p = q;
    }
    CBinTreeNode<T>* t = *p;
    *p = (*p)->nodes[(*p)->nodes[1] != 0];
    delete t;
    return 1;
}

template <class T, class C>
CBinTreeNode<T>** CBinTree<T, C>::Rep(CBinTreeNode<T>** p)
{
    CBinTreeNode<T>** q;
    for (q = &(*p)->nodes[!brep];
        (*q)->nodes[brep];
        q = &(*q)->nodes[brep]);
    brep = !brep;
    return q;
}

template <class T, class C>
void CBinTree<T, C>::InOrder(CBinTreeNode<T>* n)//L-U-R
{
    if (!n) return;
    InOrder(n->nodes[0]);
    std::cout << n->value << " ";
    InOrder(n->nodes[1]);
}

template <class T, class C>
void CBinTree<T, C>::PreOrder(CBinTreeNode<T>* n)//U-L-R
{
    if (!n) return;
    std::cout << n->value << " ";
    PreOrder(n->nodes[0]);
    PreOrder(n->nodes[1]);
}

template <class T, class C>
void CBinTree<T, C>::PosOrder(CBinTreeNode<T>* n)//L-R-U
{
    if (!n) return;
    PosOrder(n->nodes[0]);
    PosOrder(n->nodes[1]);
    std::cout << n->value << " ";
}
template <class T, class C>
void CBinTree<T, C>::InversePosOrder(CBinTreeNode<T>* n)//L-R-U
{
    if (!n) return;
    PosOrder(n->nodes[1]);
    PosOrder(n->nodes[0]);
    std::cout << n->value << " ";
}

template <class T, class C>
void CBinTree<T, C>::ReverseOrder(CBinTreeNode<T>* n)//R-U-L
{
    if (!n) return;
    ReverseOrder(n->nodes[1]);
    std::cout << n->value << " ";
    ReverseOrder(n->nodes[0]);
}

template <class T, class C>
void CBinTree<T, C>::LevelOrder(CBinTreeNode<T>* n)
{
    if (!root) return;
    std::queue< CBinTreeNode<T>* > q;
    for (q.push(root); !q.empty(); q.pop())
    {
        std::cout << q.front()->value << " ";
        if (q.front()->nodes[0]) q.push(q.front()->nodes[0]);
        if (q.front()->nodes[1]) q.push(q.front()->nodes[1]);
    }
}

template <class T, class C>
int CBinTree<T, C>::MaxDepth(CBinTreeNode<T>* n)
{
    if (!n) return 0;
    return std::max(MaxDepth(n->nodes[0]), MaxDepth(n->nodes[1])) + 1;
}

template <class T, class C>
void CBinTree<T, C>::Print()
{
    InOrder(root);
    std::cout << "\n";
}

template<class T, class C>
void CBinTree<T, C>::SeparateLevels(list<T>* mat, CBinTreeNode<T>* n)
{
    mat->push_back(n->value);
    if (n->nodes[0])
        SeparateLevels(mat + 1, n->nodes[0]);
    if (n->nodes[1])
        SeparateLevels(mat + 1, n->nodes[1]);
}

template<class T, class C>
void CBinTree<T, C>::PrintNiveles(list<T>* mat)
{
    for (int num = 0; num < MaxDepth(root); ++num)
        (mat + num)->clear();
    SeparateLevels(mat, root);
    typename list<T>::iterator a;
    //cout << "depth: " << MaxDepth(root) << endl;

    for (int num = 0; num < MaxDepth(root); ++num) {
        int espacios = 0;
        for (a = (mat + num)->begin(); a != (mat + num)->end(); ++a) {//recorrer lista
            for (int x = 0; x < *a - espacios; ++x)
                cout << ' ';
            cout << *a;
            espacios = *a;
        }
        cout << endl << endl;
    }
}
int main()
{
    CBinTree<int, CLess<int>> t;
    /*std::cout << "ins \n";
    t.Ins(65); t.Print();
    t.Ins(41); t.Print();
    t.Ins(79); t.Print();
    t.Ins(33); t.Print();
    t.Ins(51); t.Print();
    t.Ins(79); t.Print();
    t.Ins(68); t.Print();
    t.Ins(71); t.Print();
    t.Ins(81); t.Print();

    std::cout << "max depth \n";
    std::cout << t.MaxDepth(t.Root()) << "\n";

    std::cout << "rem \n";
    t.Rem(33); t.Print();
    t.Rem(68); t.Print();
    t.Rem(65); t.Print();

    std::cout << "DepthFirst\n";
    t.InOrder(t.Root());        std::cout << "\n";
    t.PreOrder(t.Root());       std::cout << "\n";
    t.PosOrder(t.Root());       std::cout << "\n";
    t.ReverseOrder(t.Root());   std::cout << "\n";
    std::cout << "BreadthFirst\n";
    t.LevelOrder(t.Root());     std::cout << "\n";
    */
    t.Ins(1);
        list<int>* levlMat = new list<int>[t.MaxDepth(t.Root())];
        t.PrintNiveles(levlMat);
        delete[] levlMat;
    t.Ins(2); 
        levlMat = new list<int>[t.MaxDepth(t.Root())];
        t.PrintNiveles(levlMat);
        delete[] levlMat;
    t.Ins(3); 
        cout << "Se insertó 3\n";
        levlMat = new list<int>[t.MaxDepth(t.Root())];
        t.PrintNiveles(levlMat);
        delete[] levlMat;
    t.Ins(4);
        levlMat = new list<int>[t.MaxDepth(t.Root())];
        t.PrintNiveles(levlMat);
        delete[] levlMat;
    t.Ins(5); 
       levlMat = new list<int>[t.MaxDepth(t.Root())];
        t.PrintNiveles(levlMat);
        delete[] levlMat;
    t.Ins(6); 
       levlMat = new list<int>[t.MaxDepth(t.Root())];
        t.PrintNiveles(levlMat);
        delete[] levlMat;
    t.Ins(7); 
        levlMat = new list<int>[t.MaxDepth(t.Root())];
        t.PrintNiveles(levlMat);
        delete[] levlMat;
    t.Ins(8); 
        levlMat = new list<int>[t.MaxDepth(t.Root())];
        t.PrintNiveles(levlMat);
        delete[] levlMat;

    
}




/*
 template <class T, class C>
 CBinTreeNode<T>** CBinTree<T,C>::Rep(CBinTreeNode<T>** p)
 {
     int b = rand()%2;
     CBinTreeNode<T>** q = &(*p)->nodes[b];
     while ( (*q)->nodes[!b] )
         q = &(*q)->nodes[!b];
     return q;
 }

 template <class T, class C>
 CBinTreeNode<T>** CBinTree<T,C>::Rep(CBinTreeNode<T>** p)
 {
     CBinTreeNode<T>** q = &(*p)->nodes[!brep];
     while ( (*q)->nodes[brep] )
         q = &(*q)->nodes[brep];
     brep = !brep;
     return q;
 }

 template <class T, class C>
 int CBinTree<T,C>::MaxDepth(CBinTreeNode<T>* n)
 {
     if ( !n ) return 0;
     int l, r;
     l = MaxDepth(n->nodes[0]);
     r = MaxDepth(n->nodes[1]);
     return (l>r ? l : r) + 1;
 }

 */
