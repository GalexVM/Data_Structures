#include <iostream>

template<class T>
struct CNode
{
    CNode(T x)
    {
        value = x;
        next = prev = 0;
    }
    T value;
    CNode<T>* next, * prev;
};

template<class T>
class CList
{
public:
    CList()
    {
        head = tail = 0;
        nelem = 0;
    }
    ~CList()
    {
        //...
    }

    void push_back(T x)
    {
        CNode<T>* n = new CNode<T>(x);
        if (!nelem)
            head = tail = n;
        else
        {
            n->prev = tail;
            tail->next = n;
            tail = n;
        }
        nelem++;
    }

    void pop_back()
    {
        //...
    }

    void push_front(T x)
    {
        CNode<T>* n = new CNode<T>(x);
        if (!nelem)
            head = tail = n;
        else
        {
            n->next = head;
            head->prev = n;
            head = n;
        }
        nelem++;
    }

    void pop_front()
    {
        //...
    }

    T& operator[](int i)
    {
        CNode<T>* n = head;
        for (int k = 0; k != i; k++)
            n = n->next;
        return n->value;
    }

    void print()
    {
        std::cout << "\n";
        for (CNode<T>* n = head; n != 0; n = n->next)
            std::cout << n->value << " ";
    }
    void print2()
    {
        std::cout << "\n";
        for (int i = 0; i < nelem; i++)
            std::cout << (*this)[i] << " ";

    }

private:
    CNode<T>* head, * tail;
    int nelem;
};

//////////////////////////////////////////////////////////////////////

template<class T>
class CVector
{
public:
    CVector(int size = 5)
    {
        m_size = size;
        m_v = new T[m_size];
        m_nelem = 0;
    }
    ~CVector()
    {
        delete m_v;
    }

    void expand()
    {
        T* p = new T[2 * m_size];
        for (int i = 0; i < m_size; i++)
            p[i] = m_v[i];
        delete m_v;
        m_v = p;
        m_size = 2 * m_size;
    }

    void push_back(T x)
    {
        if (m_nelem == m_size)
            expand();
        m_v[m_nelem] = x;
        m_nelem++;
    }

    void pop_back()
    {
        //nelem --;
        //collapse
    }

    void push_front(T x)
    {
        if (m_nelem == m_size)
            expand();
        for (int i = m_nelem - 1; i >= 0; i--)
            m_v[i + 1] = m_v[i];
        m_v[0] = x;
        m_nelem++;
    }

    void pop_front()
    {
        //nelem --;
        //collapse
    }

    T& operator[](int i)
    {
        return m_v[i];
    }

    void print()
    {
        for (int i = 0; i < m_nelem; i++)
            std::cout << m_v[i] << " ";
        std::cout << std::endl;
    }

private:
    T* m_v;
    int m_size;
    int m_nelem;
};

//////////////////////////////////////////////////////////////////////

template<class T, class S>
class CStack
{
public:
    void push(T x)
    {
        seq.push_back(x);
    }
    void pop()
    {
        seq.pop_back();
    }
private:
    S seq;
};

//////////////////////////////////////////////////////////////////////

template<class T, class S>
class CQueue
{
public:
    void push(T x)
    {
        seq.push_back(x);
    }
    void pop()
    {
        seq.pop_front();
    }

private:
    S seq;
};


int main()
{

    CQueue<int, CList<int>> q;
    q.push(3);
    q.push(6);
    q.push(1);
    q.pop();
    q.pop();

    CStack<int, CVector<int>> s;
    s.push(3);
    s.push(6);
    s.push(1);
    s.pop();
    s.pop();

    CList<int> l;

    l.push_back(2);
    l.push_back(7);
    l.push_back(9);
    l.push_back(1);
    l.push_back(3);
    l.push_back(8);
    l.push_front(6);
    l.push_front(4);

    l.print();
    l.print2();

    std::cout << "\nelem 4:" << l[4] << "\n";
}