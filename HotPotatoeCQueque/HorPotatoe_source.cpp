#include<iostream>


template<class T>
struct CNode
{
    CNode(T x)
    {
        value = x;
        next = prev = 0;
    }
    T value;
    CNode* next, * prev;
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

        for (; head != tail; head = head->next) {

            delete head->prev;
        }

        delete head;
    }

    void push_back(T x)
    {
        CNode* n = new CNode(x);
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
        CNode<T>* n = tail;
        tail = tail->prev;
        delete n;
        nelem--;
    }

    void push_front(T x)
    {
        CNode* n = new CNode(x);
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
        CNode* n = head;
        head = head->next;
        head->prev = 0;
        delete n;
        nelem--;
    }

    int& operator[](int i)
    {
        CNode* n = head;
        for (int k = 0; k != i; k++)
            n = n->next;

        return n->value;
    }

    void print()
    {
        std::cout << "\n";
        for (CNode* n = head; n != 0; n = n->next)
            std::cout << n->value << " ";
    }

private:
    CNode* head, * tail;
    int nelem;
};

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

int main() {

}