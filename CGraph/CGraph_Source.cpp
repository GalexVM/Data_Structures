#include<iostream>
#include<deque>
#include<list>
#include<vector>
#include <thread>
using namespace std;

int nThreads = 4; //Trabajaré con 4 porque '::hardware_concurrency()' me da resultados diferentes en diferentes
                    //compiladores

template<class G>
struct DijkstraTag
{
    typedef typename G::N       N;
    typedef typename G::E       E;
    typedef typename G::Edge    Edge;
    typedef typename G::Node    Node;
    E pAcumulado = 0;
    Node* nAnterior = 0;
    int nPasos = 0;
    void Reset()
    {
        pAcumulado = 0;
        nAnterior = 0;
        nPasos = 0;
    }
    void Set(E e, Node* n, int i)
    {
        pAcumulado = e;
        nAnterior = n;
        nPasos = i;
    }
    void Print()
    {
        cout << "Peso acumulado: " << pAcumulado << endl;
        cout << "Nodo anterior: " << nAnterior->value << endl;
        cout << "Número de pasos: " << nPasos << endl;
    }
};

template<class G>
struct DijkstraMap
{
    typedef typename G::N       N;
    typedef typename G::E       E;
    typedef typename G::Edge    Edge;
    typedef typename G::Node    Node;

    N aNode = 0;
    N bNode = 0;
    E minDis = 0;
    list<Node*> minRec;

    void Set(N n1, N n2, E e)
    {
        aNode = n1;
        bNode = n2;
        minDis = e;
    }

    void Print()
    {
        cout << aNode << " -> " << bNode << ": " << minDis << "|";
        typename list<Node*>::iterator it1;
        for (it1 = minRec.begin(); it1 != minRec.end(); ++it1)
        {
            if(*it1)
                cout << "--> " << (*it1)->value << " ";
            else
                cout << "--> " << '0' << " ";
        }
        cout << endl;
    }

};

template<class G>
struct CNode
{
    typedef typename G::Edge    Edge;
    typedef typename G::N       N;
    typedef typename G::Tag     Tag;

    N value;
    std::list<Edge*> edges;
    deque<Tag*> tag;
    deque<bool> cookie;
    //Tag tag;
    //bool cookie = 0;
    CNode(N valor) :value(valor) 
    {
        for (int i = 0; i < nThreads; ++i)
        {
            Tag* tg = new Tag;
            tag.push_back(tg);
            cookie.push_back(0);
        }
    };
};

template<class G>
struct CEdge
{
    typedef typename G::Node    Node;
    typedef typename G::E       E;

    E value;
    Node* nodes[2];
    bool dir; // 0 -> bidireccional, 1 -> [0]->[1]
    CEdge(Node* a, Node* b, E e, bool d) {
        nodes[0] = a;
        nodes[1] = b;
        value = e;
        dir = d;
    }
};

template<class _N, class _E>
class CGraph
{
public:
    typedef CGraph<_N, _E>   G;
    typedef CNode<G>        Node;
    typedef CEdge<G>        Edge;
    typedef DijkstraTag<G>  Tag;
    typedef DijkstraMap<G>  Map;
    typedef _N              N;
    typedef _E              E;
    typedef typename deque<Node*>::iterator i;
    typedef typename list<Edge*>::iterator j;

    bool FindNode(N n, i& p);
    bool FindEdge(E n, j& p, i& a);
    bool InsNode(N n);
    bool InsEdge(N a, N b, E e, bool d);
    bool RemEdge(N a, N b, E e);
    bool RemNode(N n);
    void PrintNodes();
    void PrintEdges();
    void BuildMap(int a); //Ejecuta dijkstra en cada nodo y arma
    void Dijkstra(Node *n, int c);//Llena las etiquetas de cada nodo respecto de el seleccionado
    void AddMap(Node *n, int c);//Agrega mapas a fullMap con la información de las etiquetas. a = n, b = x
    void PrintMap();
    void GetMinDistance(N a, N b);
    
    int nNodes = 0;
    deque<Node*> nodes;
    list<Map*> fullMap;
};

struct Coord
{
    float x, y;
};

template<class _N, class _E>
bool CGraph<_N, _E>::FindNode(N n, i& p) {
    auto i = nodes.begin();
    for (; i != nodes.end(); i++) {
        if ((*i)->value == n) {
            p = i;
            return true;
        }
    }
    return false;
}

template<class _N, class _E>
bool CGraph<_N, _E>::FindEdge(E e, j& p, i& a) {
    auto i = (*a)->edges.begin();
    for (; i != (*a)->edges.end(); i++) {
        if ((*i)->value == e) {
            p = i;
            return true;
        }
    }
    return false;
}

template<class _N, class _E>
bool CGraph<_N, _E>::InsNode(N n) {
    i p;
    if (!FindNode(n, p)) {
        Node* nodo = new Node(n);
        nodes.push_back(nodo);
        nNodes++;
        return 1;
    }
    return 0;
}

template<class _N, class _E>
bool CGraph<_N, _E>::InsEdge(N a, N b, E e, bool d) {
    i p1, p2;
    if (FindNode(a, p1) && FindNode(b, p2)) {
        j q;
        //if (!FindEdge(e, q, p1) && !FindEdge(e, q, p2)) {
            Edge* ed = new Edge(*p1, *p2, e, d);
            (*p1)->edges.push_back(ed);
            (*p2)->edges.push_back(ed);           
            return 1;
    }
    return 0;
}

template<class _N, class _E>
bool CGraph<_N, _E>::RemEdge(N a, N b, E e) {
    j q1, q2;
    i p1, p2;
    if (!FindNode(a, p1) || !FindNode(b, p2)) return false;
    if (!FindEdge(e, q1, p1) || !FindEdge(e, q2, p2)) return false;
    (*p1)->edges.erase(q1);
    (*p2)->edges.erase(q2);
    return true;
}

template<class _N, class _E>
bool CGraph<_N, _E>::RemNode(N e) {
    i p;
    std::deque<j> dq;
    if (FindNode(e, p)) {
        j it = (*p)->edges.begin();  
        for (; it != (*p)->edges.end(); ++it) 
        {
            j temp = it;
            dq.push_back(temp);
            cout << 'i' << endl;
        } 
        //i it2;
        typename std::deque<j>::iterator it2;
        for(it2 = dq.begin();it2 != dq.end(); ++it2)
            RemEdge((**it2)->nodes[0]->value, (**it2)->nodes[1]->value, (**it2)->value);
        nodes.erase(p);
        return true;
    }
}

template<class _N, class _E>
void CGraph<_N, _E>::PrintNodes() {
    auto i = nodes.begin();
    for (; i != nodes.end(); i++) {
        cout << (*i)->value << " ";
    }
}

template<class _N, class _E>
void CGraph<_N, _E>::PrintEdges() {
    auto i = nodes.begin();
    for (; i != nodes.end(); i++) {
        auto j = (*i)->edges.begin();
        for (; j != (*i)->edges.end(); j++)
            cout << "(" << (*j)->nodes[0]->value << ")->" << (*j)->value << "->(" << (*j)->nodes[1]->value << ")" << endl;
        cout << endl;
    }
}

template<class _N, class _E>
void CGraph<_N, _E>::BuildMap(int a)
{
    int ini, end;
    ini = nNodes / nThreads * (a - 1);
    if (nNodes / nThreads * nThreads != nNodes && a == 4)//Si la división no es exacta y ya es la 4ta parte
        end = nNodes;
    else
        end = nNodes / nThreads * a;

    i it1 = nodes.begin() + ini;//Acceder por partes (4 threads)
    for (; it1 != nodes.begin() + end; ++it1)
    {
        Dijkstra(*it1, a-1);
        AddMap(*it1, a-1);
    }
}
template<class _N, class _E>
void CGraph<_N, _E>::Dijkstra(Node *n, int c)
{
    Node* p = n;//pivot
    Edge* min = 0;
    (*p).tag[c]->Reset();//poner todos los tags a 0
    deque<Edge*> minArray;
    
    for (int x  = 0; x < nNodes-1; ++x )//pasos para terminar
    {
        (*p).cookie[c] = true;
        auto j = (*p).edges.begin();
        for (; j != (*p).edges.end(); ++j)
            if ((*j)->nodes[0] == p || (*j)->dir == 0)//Si sale del nodo o es bidireccional
                minArray.push_back(*j);//Añadir los valores de los nodos
        
        for (unsigned int i = 0; i < minArray.size(); ++i)//Mínimo provisional
        {
            if (minArray[i]->nodes[1]->cookie[c] == 0)
            {
                min = minArray[i];
                break;
            }     
        }
        for (unsigned int i = 0; i < minArray.size(); ++i)//Etiquetar
        {  
            if (minArray[i]->dir == 1)
            {
                if(minArray[i]->value + (minArray[i]->nodes[0]->tag[c]->pAcumulado) <
                    minArray[i]->nodes[1]->tag[c]->pAcumulado ||
                    (minArray[i]->nodes[1]->tag[c]->pAcumulado == 0 &&
                    minArray[i]->nodes[1] != n)
                    )//Solo setear el tag si va a ser para un camino más corto, o si hay un 0
                    minArray[i]->nodes[1]->tag[c]->Set(minArray[i]->value + (minArray[i]->nodes[0]->tag[c]->pAcumulado),
                                                    minArray[i]->nodes[0],
                                                    1 + (minArray[i]->nodes[0]->tag[c]->nPasos));
            }
            else
            {
                //...
            }
            
            if (min && minArray[i] &&
                minArray[i]->nodes[1]->tag[c]->pAcumulado < min->nodes[1]->tag[c]->pAcumulado &&
                minArray[i]->nodes[1]->cookie[c] == 0)//Obtener mínimo
            {
                min = minArray[i];
            }
           
        }
        if(min)
            p = min->nodes[1];//Avanzar pivot al mínimo
        for (unsigned int i = 0; i < minArray.size(); ++i)//Eliminar min del array
        {
            if (*(minArray.begin() + i) == min)
            {
                minArray.erase(minArray.begin() + i);
                break;
            }   
        }
       
    }

}
template<class _N, class _E>
void CGraph<_N, _E>::AddMap(Node *n, int c)
{
   
    for (int i = 0; i < nNodes; ++i)//Agregar a fullmap
    {
        Map* x = new Map;
        x->Set(n->value, nodes[i]->value, nodes[i]->tag[c]->pAcumulado);//Ingresar nodo de ida, de llegada, recorrido
        Node* p = 0;
        for (int j = 0; j < nodes[i]->tag[c]->nPasos; j++)
        { 
            if (j != 0)//No primera iteración
            {
                Node* q = 0;
                q = p->tag[c]->nAnterior;
                x->minRec.push_front(q);
                p = q;
            }
            else
            {
               x->minRec.push_front(nodes[i]);
               x->minRec.push_front(nodes[i]->tag[c]->nAnterior);
               p = nodes[i]->tag[c]->nAnterior;
            }  
        }    
        fullMap.push_back(x);   
    }
    for (int i = 0; i < nNodes; ++i)//limpiar todos los tags y cookies
    {
        nodes[i]->tag[c]->Reset();
        nodes[i]->cookie[c] = 0;
    }
}

template<class _N, class _E>
void CGraph<_N, _E>::PrintMap()
{
    typename list<Map*>::iterator it1;
    for (it1 = fullMap.begin(); it1 != fullMap.end(); ++it1)
    {
        (*it1)->Print();
    }
}

template<class _N, class _E>
void CGraph<_N, _E>::GetMinDistance(N a, N b)
{
    typename list<Map*>::iterator it = fullMap.begin();
    for (; it != fullMap.end();++it)
    {
        if ((*it)->aNode == a && (*it)->bNode == b)
        {
            cout << "La distancia minima entre " << a << " y " << b << " es " << (*it)->minDis;
            break;
        }

    }
    cout << "\nEl recorrido minimo es: \n";
    typename list<Node*>::iterator it2 = (*it)->minRec.begin();
    for (; it2 != (*it)->minRec.end(); ++it2)
    {
        cout << " -> " << (*it2)->value;
    }cout << endl;
}
/*
class CGraphCity : public CGraph<Coord, int>
{
    // algoritmos optimizados con coordenas
    
     //busquedas direccionada
     //precalculo
     //etc
     
};

class CGraphChar : public CGraph<char, int>
{
    // algoritmos no optimizados
    //void Print();
    
    // implementar dikjstra, etc
     
};
*/

int main()
{
    CGraph<int, int> g1;
    
    g1.InsNode(1);
    g1.InsNode(2);
    g1.InsNode(3);
    g1.InsNode(4);
    g1.InsNode(5);

    g1.InsEdge(1, 2, 2, 1);
    g1.InsEdge(1, 5, 10, 1);
    g1.InsEdge(2, 3, 3, 1);
    g1.InsEdge(2, 5, 7, 1);
    g1.InsEdge(3, 1, 4, 1);
    g1.InsEdge(3, 4, 4, 1);
    g1.InsEdge(4, 5, 5, 1);
    g1.InsEdge(5, 3, 3, 1);

    g1.PrintNodes();
    cout << endl;
    g1.PrintEdges();
   
    
    vector<thread> ths(nThreads);
    
    int i, j;
    i = 0; 
    for (; i < nThreads; ++i)
    {
        j = i + 1;
        ths[i] = thread(
            [g = &g1, j]()
            {
                g->BuildMap(j);
            }
        );
    }
    i = 0;
    for (; i < nThreads; ++i)
    {
        ths[i].join();
    }
    g1.PrintMap();
    g1.GetMinDistance(4, 1);

}
