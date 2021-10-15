#include<iostream>

#include <stdlib.h>     /* srand, rand */
#include <time.h> 
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
        CNode<T>* n = head;
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
    int size()
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
    int size() {
        return seq.size();
    }
    int front() {
        return seq[0];
    }
private:
    S seq;
};



int main() {
    CQueque<int, CList<int>> papaCaliente;
    for (int i = 0; i < 10; i++)
        papaCaliente.push(i + 1);
    papaCaliente.print();
    int hotValue = 0;
    
    while (papaCaliente.size() != 1) {
        /*
        cout << "\n\nIngresa un numero del 0 al " << papaCaliente.size() << ": ";
        cin >> hotValue;
        cout << "\n";
        */
        srand(time(NULL));
        hotValue = rand() % papaCaliente.size();
        cout << endl << "valor obtenido: " << hotValue << endl;
        

        for (int i = 0; i < hotValue; i++) {
            papaCaliente.push(papaCaliente.front());
            papaCaliente.pop();
        }
        cout << "\nJugador " << papaCaliente.front() << " fuera!\n";

        papaCaliente.pop();
        
        papaCaliente.print();

        if (papaCaliente.size())
            cout << "\nEl ganador es el jugador: " << papaCaliente.front() << endl;;
    }
    
    


}


    
    


