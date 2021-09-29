#include <iostream>
#include <sstream>
#include <string>

using std::istringstream;
using std::ostringstream;
using std::cout;
using std::endl;
using std::cin;
using std::string;



struct CNode
{
    CNode(string x)
    {
        value = x;
        next = prev = 0;
    }
    string value;
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
        for (; head != tail; head = head->next)
            delete head->prev;
        delete head;
    }

    void push_back(string x)
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
        CNode* n = tail;
        tail = tail->prev;
        delete n;
        nelem--;
    }

    string& operator[](int i)
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
    int GetNumElem() {
        return nelem;
    }
    bool IsEmpty() {
        if (head == tail)
            return 1;
        return 0;
    }
private:
    CNode* head, * tail;
    int nelem;
};

template<class S>
class CStack
{
public:
    void push(string x)
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
    string& operator[](int i) {
        return seq[GetNumElem() - 1 - i];
    }
    void Print() {
        seq.print();
    }
private:
    S seq;
};

template<class S>
void RPN(CStack<S>& stack, string* p, string* q);


template<class S>
int EvaluarRPN(CStack<S>& stack, string* q);

template<class S>
void Ingresar(CStack<S>& stack, string ch);

template<class S>
void DesplegarParentesis(CStack<S>& stack, string* p, string*& q);


void Desplegar(string ch, string*& q);

template< class S>
void Extraer(CStack<S>& stack, string*& q);

template<class S>
string Sumar2Primeros(CStack<S>& stack);

template<class S>
string Restar2Primeros(CStack<S>& stack);

template<class S>
string Producto2Primeros(CStack<S>& stack);

int main() {
    CStack<CList> pila1;
    string expresionInfija[15] = { "(","3","+","5",")","*","(","7","-","4",")"};
   
    string expresionPostfija[15] = {};
    
    RPN(pila1, expresionInfija, expresionPostfija);
    
    cout << "Evaluación: " << EvaluarRPN(pila1, expresionPostfija) << endl;
 
}

template<class S>
void RPN(CStack<S>& stack, string* p, string* q) {
    string* aux = q;
    for (; *p != ""; p++) {
        
        if (*p == "(") {
            Ingresar(stack, *p);
        }
        else if (*p == "+" || *p == "-" || *p == "*") {
            Ingresar(stack, *p);
        }
        else if (*p == ")") {
            DesplegarParentesis(stack, p, q);
        }
        else {
            Desplegar(*p, q);
        }
    }
    Extraer(stack, q);
    cout << "Expresion postfija: ";
    for (; aux != q; aux++) {
        cout << *aux;
    }cout << endl;

}

template<class S>
void Ingresar(CStack<S>& stack, string ch) {
    stack.push(ch);
}


void Desplegar(string ch, string*& q) {
    *q = ch;
    q++;
}

template<class S>
void DesplegarParentesis(CStack<S>& stack, string* p, string*& q) {
    while (stack[0] != "(") {
        *q = stack[0];
        q++;
        stack.pop();
    }
    stack.pop();
}

template<class S>
void Extraer(CStack<S>& stack, string*& q) {
    for (int i = 0; i < stack.GetNumElem(); i++) {
        *q = stack[i];
        q++;
    }
    while (!stack.IsEmpty())
        stack.pop();
    stack[0] = "";


}

template<class S>
int EvaluarRPN(CStack<S>& stack, string* q) {
    int resultado = 0;
    for (; *q != ""; q++) {

        if (*q == "+") {
            Ingresar(stack, Sumar2Primeros(stack));
        }
        else if (*q == "-") {
            Ingresar(stack, Restar2Primeros(stack));
        }
        else if (*q == "*") {
            Ingresar(stack, Producto2Primeros(stack));
        }else{
            Ingresar(stack, *q);
        }
    }
    istringstream ultimoElem(stack[0]);
    ultimoElem >> resultado;
    
    return resultado;
}


template<class S>
string Sumar2Primeros(CStack<S>& stack) {
    int a,b;
    istringstream ch1 (stack[0]);
    ch1 >> a;
    stack.pop();
    istringstream ch2(stack[0]);
    ch2 >> b;
    stack.pop();
    a = b + a;
    ostringstream resultado;
    resultado << a;
    return resultado.str();
}

template<class S>
string Restar2Primeros(CStack<S>& stack) {
    int a, b;
    istringstream ch1(stack[0]);
    ch1 >> a;
    stack.pop();
    istringstream ch2(stack[0]);
    ch2 >> b;
    stack.pop();
    a = b - a;
    ostringstream resultado;
    resultado << a;
    return resultado.str();
}

template<class S>
string Producto2Primeros(CStack<S>& stack) {
    int a, b;
    istringstream ch1(stack[0]);
    ch1 >> a;
    stack.pop();
    istringstream ch2(stack[0]);
    ch2 >> b;
    stack.pop();
    a = b * a;
    ostringstream resultado;
    resultado << a;
    return resultado.str();
}

