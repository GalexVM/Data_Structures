#include <iostream>

struct CNode
{
    CNode(int x)
    {
        value = x;
        next = prev = 0;
    }
    int value;
    CNode* next, * prev;
};

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

    void push_back(int x)
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

    void push_front(int x)
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
    void print2()
    {
        std::cout << "\n";
        for (int i = 0; i < nelem; i++)
            std::cout << (*this)[i] << " ";
    }

private:
    CNode* head, * tail;
    int nelem;
};

int main()
{
    CList l;
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

    l.pop_front();
    l.pop_back();

    l.print();
    l.print2();

    std::cout << "\nelem 4:" << l[4] << "\n";
}