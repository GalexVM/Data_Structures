#include <iostream>
#include <sstream>
#include <string>

using std::cout;
using std::endl;
using std::cin;
using std::string;


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
        for (; head != tail; head = head->next)
            delete head->prev;
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
    int GetNumElem() {
        return nelem;
    }
    bool IsEmpty() {
        if (head == tail)
            return 1;
        return 0;
    }
private:
    CNode<T>* head, * tail;
    int nelem;
};

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
    int GetNumElem() {
        return seq.GetNumElem();
    }
    bool IsEmpty() {
        return seq.IsEmpty();
    }
    T& operator[](int i) {
        return seq[GetNumElem() - 1 - i];
    }
    void Print() {
        seq.print();
    }
private:
    S seq;
};

template<class T, class S>
void RPN(CStack<T, S>& stack, T* p, T* q);


template<class T, class S>
int EvaluarRPN(CStack<T, S>& stack, T* q);

template<class T, class S>
void Ingresar(CStack<T, S>& stack, T ch);

template<class T, class S>
void DesplegarParentesis(CStack<T, S>& stack, T* p, T*& q);

template<class T>
void Desplegar(T ch, T*& q);

template<class T, class S>
void Extraer(CStack<T, S>& stack, T*& q);

template<class T, class S>
char Sumar2Primeros(CStack<T, S>& stack);

template<class T, class S>
char Restar2Primeros(CStack<T, S>& stack);

template<class T, class S>
char Producto2Primeros(CStack<T, S>& stack);

int main() {
    CStack<char, CList<char>> pila1;
    char expresionInfija[15] = { '(','3','+','5',')','*','(','7','-','4',')' };
    
    //{"(3+5)*(7-4)","(4*2)-(5+1)","2+(3+5)*2"};
    char expresionPostfija[15] = {};
    
    RPN(pila1, expresionInfija, expresionPostfija);
    
    EvaluarRPN(pila1, expresionPostfija);
 
}

template<class T, class S>
void RPN(CStack<T, S>& stack, T* p, T* q) {
    T* aux = q;
    for (; *p; p++) {
        switch (*p) {
        case '(': Ingresar(stack, *p); break;
        case '+': Ingresar(stack, *p); break;
        case '-': Ingresar(stack, *p); break;
        case '*': Ingresar(stack, *p); break;
        case ')': DesplegarParentesis(stack, p, q); break;
        default: Desplegar(*p, q);
        }
    }
    Extraer(stack, q);
    cout << "Expresion postfija: ";
    for (; aux != q; aux++) {
        cout << *aux;
    }cout << endl;

}

template<class T, class S>
void Ingresar(CStack<T, S>& stack, T ch) {
    stack.push(ch);
}

template<class T>
void Desplegar(T ch, T*& q) {
    *q = ch;
    q++;
}

template<class T, class S>
void DesplegarParentesis(CStack<T, S>& stack, T* p, T*& q) {
    while (stack[0] != '(') {
        *q = stack[0];
        q++;
        stack.pop();
    }
    stack.pop();
}

template<class T, class S>
void Extraer(CStack<T, S>& stack, T*& q) {
    for (int i = 0; i < stack.GetNumElem(); i++) {
        *q = stack[i];
        q++;
    }
    while (!stack.IsEmpty())
        stack.pop();
    stack[0] = 0;


}

template<class T, class S>
int EvaluarRPN(CStack<T, S>& stack, T* q) {
    int resultado = 0;
    for (; *q; q++) {
        switch (*q)
        {
        case '+':
            Sumar2Primeros(stack); break;
        case '-':
            Restar2Primeros(stack); break;
        case '*':
            Producto2Primeros(stack); break;
        default:
            Ingresar(stack, *q);
        }
    }
    
    return resultado;
}


template<class T, class S>
char Sumar2Primeros(CStack<T, S>& stack) {
    int a = (int)stack[0] - '0';
    stack.pop();
    int b = (int)stack[0] - '0';
    stack.pop();
    cout << "a,b: " << a << ' ' << b << endl;
    return 0;
}

template<class T, class S>
char Restar2Primeros(CStack<T, S>& stack) {
    return 0;
}

template<class T, class S>
char Producto2Primeros(CStack<T, S>& stack) {
    return 0;
}

