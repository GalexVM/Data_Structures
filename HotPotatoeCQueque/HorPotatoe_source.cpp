#include<iostream>
using namespace std;


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
    int returnNumElem()
    {
        return nelem;
    }

private:
    CNode<T>* head, * tail;
    int nelem;
};

template<class T, class S>
class CQueque
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
    void print() {
        seq.print();
    }
    int giveNumElem() {
        return seq.returnNumElem();
    }
    int giveLastValue() {
        return seq[0];
    }
private:
    S seq;
};


template <class T, class S>
void recorrerPatata(CQueque<T, S<T>>* queque, int hotValue);

int main() {
    CQueque<int, CList<int>> papaCaliente;
    for (int i = 0; i < 5; i++)
        papaCaliente.push(i + 1);
    papaCaliente.print();

    int hotValue = 0;
    cout << "\n\nIngresa un numero del 1 al "<< papaCaliente.giveNumElem() << ": ";
    cin >> hotValue;
    cout << "\n";


}

template <class T, class S>
void recorrerPatata(CQueque<T, S<T>>* queque, int hotValue) {
    T tempValue;

    for (int i = 0; i < hotValue; i++) {
        tempValue = queque.giveLastValue();
        queque.pop();
        queque.push(tempValue);
    }
    

}
