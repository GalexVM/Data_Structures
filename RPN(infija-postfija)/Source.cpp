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
        if ( n == nullptr) {
            string nullstring = "";
            return nullstring;
        }
        else {
            for (int k = 0; k != i; k++)
                n = n->next;
            return n->value;
        }

        
    }
    void print()
    {
        
        for (CNode* n = head; n != 0; n = n->next)
            std::cout << n->value << " ";
        cout << endl;
    }
    int size() {
        return nelem;
    }
    bool empty() {
        if (head == tail)
            return 1;
        return 0;
    }
    CNode* back() {
        return tail;
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
    int size() {
        return seq.size();
    }
    bool empty() {
        return seq.empty();
    }
    /*
    string& operator[](int i) {
        if (size())
            return seq[0];
        return seq[size() - 1 - i];
    }*/
    CNode* top() {
        return seq.back();
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

template<class S>
bool CompararPrecedencia(string a, CStack<S>& stack);


void Desplegar(string ch, string*& q);

template< class S>
void ExtraerTodaPila(CStack<S>& stack, string*& q);

template<class S>
string Sumar2Primeros(CStack<S>& stack);

template<class S>
string Restar2Primeros(CStack<S>& stack);

template<class S>
string Producto2Primeros(CStack<S>& stack);

template<class S>
string Division2Primeros(CStack<S>& stack);

template<class S>
string Potencia2Primeros(CStack<S>& stack);

int pot(int base, int exponente);

int mod(int a, int b);



int main() {
    CStack<CList> pila1;

    string expresionInfija[25] = { "(","3","^","5",")","*","(","2","+","3",")"};//Ingresar expresión.
   
    string expresionPostfija[25] = {};

    cout << "Expresion infija: ";
    for (string* p = expresionInfija; *p != ""; p++) 
        cout << *p;
    cout << endl;
    
    RPN(pila1, expresionInfija, expresionPostfija);
   
    cout << "Evaluacion: " << EvaluarRPN(pila1, expresionPostfija) << endl;

 
}

template<class S>
void RPN(CStack<S>& stack, string* p, string* q) {
    string* aux = q;
    for (; *p != ""; p++) {
        if (*p == "(" ) {
            Ingresar(stack, *p);
        }
        else if (*p == "+" || *p == "-" || *p == "*" || *p == "^" || *p == "/") {
            if (stack.size() == 0) {
                Ingresar(stack, *p);
            }
            else {
                while (!CompararPrecedencia(*p, stack)) {
                    Desplegar(stack.top()->value, q);
                    stack.pop();
                }
                Ingresar(stack, *p);
            }
            
        }
        else if (*p == ")") {
            DesplegarParentesis(stack, p, q);
        }
        else {
            Desplegar(*p, q);
        }
    }
    ExtraerTodaPila(stack, q);
    cout << "Expresion postfija: ";
    for (; aux != q; aux++) {
        cout << *aux;
    }cout << endl;

}

template<class S>
bool CompararPrecedencia(string a, CStack<S>& stack) {
    switch (a[0]){
        if (stack.size() == 0) {
            return 1;
        }
        case  '+':
        case '-':
            switch (stack.top()->value[0]){
                
                case '+':
                    return 1; break;
                case '-':
                    return 1; break;
                case '*': 
                    return 0; break;
                case '^': 
                    return 0; break;
                default:
                    return 1; break;
            }break;
        case '/':
        case '*':
            switch (stack.top()->value[0]){
                case '+':
                    return 1; break;
                case '-':
                    return 1; break;
                case '*': 
                    return 1; break;
                case '^': 
                    return 0; break;
                default:
                    return 1; break;
            }break;
        case '^':
            return 1; break;
        default:
            cout << "Error\n";
    }
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
    while (stack.top()->value != "(") {
        *q = stack.top()->value;
        q++;
        stack.pop();
    }
    stack.pop();
}

template<class S>
void ExtraerTodaPila(CStack<S>& stack, string*& q) {
    for (int i = 0; i < stack.size();) {
        Desplegar(stack.top()->value, q);
        stack.pop();        
    }
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
        }
        else if (*q == "^") {
            Ingresar(stack, Potencia2Primeros(stack) );
        }
        else{
            Ingresar(stack, *q);
        }
    }
    istringstream ultimoElem(stack.top()->value);
    ultimoElem >> resultado;
    
    return resultado;
}


template<class S>
string Sumar2Primeros(CStack<S>& stack) {
    int a,b;
    istringstream ch1 (stack.top()->value);
    ch1 >> a;
    stack.pop();
    istringstream ch2(stack.top()->value);
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
    istringstream ch1(stack.top()->value);
    ch1 >> a;
    stack.pop();
    istringstream ch2(stack.top()->value);
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
    istringstream ch1(stack.top()->value);
    ch1 >> a;
    stack.pop();
    istringstream ch2(stack.top()->value);
    ch2 >> b;
    stack.pop();
    a = b * a;
    ostringstream resultado;
    resultado << a;
    return resultado.str();
}

template<class S>
string Division2Primeros(CStack<S>& stack) {
    int a, b;
    istringstream ch1(stack.top()->value);
    ch1 >> a;
    stack.pop();
    istringstream ch2(stack.top()->value);
    ch2 >> b;
    stack.pop();
    a = b / a;
    ostringstream resultado;
    resultado << a;
    return resultado.str();
}

template<class S>
string Potencia2Primeros(CStack<S>& stack) {
    int a, b;
    istringstream ch1(stack.top()->value);
    ch1 >> a;
    stack.pop();
    istringstream ch2(stack.top()->value);
    ch2 >> b;
    stack.pop();
    a = pot(b,a);
    ostringstream resultado;
    resultado << a;
    return resultado.str();
}

int pot(int base, int exponente) {
    if (exponente == 0) return int(1);
    int x = pot(base, exponente / 2);
    if (mod(exponente, int(2)) == 0) return x * x;
    return x * x * base;
}

int mod(int a, int b) {
    int q = a / b;
    int	r = a - (q * b);
    if (a < int(0)) {
        int ar = r;
        r = b + ar;
    }
    return r;
}

