#include <iostream>

template <class T>
struct CForwardNode
{
    CForwardNode(T x)
    {
        value = x;  next = 0;
    }
    T value;
    CForwardNode<T>* next;
};

template <class T>
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

template <class T>
CForwardList<T>::CForwardList()
{
    head = 0;
}

template <class T>
CForwardList<T>::~CForwardList()
{
    //...
}

template <class T>
bool CForwardList<T>::Find(T x, CForwardNode<T>**& p)
{
    for (p = &head; *p && (*p)->value < x; p = &(*p)->next);
    return *p && (*p)->value == x;
}

template <class T>
bool CForwardList<T>::Ins(T x)
{
    CForwardNode<T>** p;
    if (Find(x, p)) return 0;
    CForwardNode<T>* t = new CForwardNode<T>(x);
    t->next = *p;
    *p = t;
    return 1;
}

template <class T>
bool CForwardList<T>::Rem(T x)
{
    CForwardNode<T>** p;
    if (!Find(x, p)) return 0;
    CForwardNode<T>* t = *p;
    *p = t->next;
    delete t;
    return 1;
}

template <class T>
void CForwardList<T>::Print()
{
    for (CForwardNode<T>* t = head; t != 0; t = t->next)
        std::cout << t->value << " ";
    std::cout << "\n";
}

int main()
{
    CForwardList<int> l;
    l.Ins(9);
    l.Ins(11);
    l.Ins(15);
    l.Ins(3);
    l.Ins(7);
    l.Ins(1);
    l.Ins(18);

    l.Print();

    l.Rem(7); l.Print();
    l.Rem(1); l.Print();
    l.Rem(15); l.Print();

}