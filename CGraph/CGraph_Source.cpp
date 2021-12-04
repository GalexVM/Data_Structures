#include<iostream>
#include<deque>
#include<queue>
#include<list>
#include<vector>
#include <algorithm>
#include <thread>
using namespace std;

/*
template<class G>
struct Camino {
    typedef typename G::Node    Node;
    typedef typename G::E       E;

    E distancia_total;
    vector<Node*> nodos;
};
template<class G>
struct Distancia {
    typedef typename G::N       N;
    typedef typename G::E       E;
    E distancia;
    N node;
    Distancia(int n, E d) :node(n), distancia(d) {};
    bool operator <(const Distancia& b) const //comparar distancias
    {
        return distancia > b.distancia;
    }
};
*/


template<class G>
struct CNode
{
    typedef typename G::Edge    Edge;
    typedef typename G::N       N;

    N value;
    std::list<Edge*> edges;
    CNode(N valor) :value(valor) {};
};

template<class G>
struct CEdge
{
    typedef typename G::Node    Node;
    typedef typename G::E       E;

    E value;
    Node* nodes[2];
    bool dir; // 0 -> bidireccional, 1 -> [0]->[1]
    bool cookie = 0;
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
    _E Distance(N a, N b);

    _E SearchClose(Node* a, N b);
    //Camino<G> Dijkstra(N origen, N destino);
    
    std::deque<Node*> nodes;
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
        return 1;
    }
    return 0;
}

template<class _N, class _E>
bool CGraph<_N, _E>::InsEdge(N a, N b, E e, bool d) {
    i p1, p2;
    if (FindNode(a, p1) && FindNode(b, p2)) {
        j q;
        if (!FindEdge(e, q, p1) && !FindEdge(e, q, p2)) {
            Edge* ed = new Edge(*p1, *p2, e, d);
            (*p1)->edges.push_back(ed);
            (*p2)->edges.push_back(ed);
            return 1;
        }
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
        cout << 'a' << endl;
        for (; it != (*p)->edges.end(); ++it) {
            
            j temp = it;
            dq.push_back(temp);
            cout << 'i' << endl;
        }
        cout << 'a' << endl;
        //i it2;
        typename std::deque<j>::iterator it2;
        for(it2 = dq.begin();it2 != dq.end(); ++it2)
            RemEdge((**it2)->nodes[0]->value, (**it2)->nodes[1]->value, (**it2)->value);
        cout << 'd' << endl;
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
/*
template<class _N, class _E>
_E CGraph<_N, _E>::Distance(N a, N b)
{
    //Encontrar nodos solicitados
    i it;
    Node* n1 = 0;
    Node* n2 = 0;
    Edge* minEd = 0;//Apuntará a la arista menor
    for (it = nodes.begin(); it != nodes.end(); ++it)
    {
        if ((*it)->value == a)
            n1 = *it;
        if ((*it)->value == b)
            n2 = *it;
    }

    //Nodos al rededor
    j it1;
    for (it1 = n1->edges.begin(); it1 != n1->edges.end(); ++it1)
    {
        if ((*it1)->cookie == false)
            minEd = *it1;//Menor provisional
        if ((*it1)->nodes[1] == n2)//Comprobar si B es adyacente
            return (*it1)->value;

    }

    //No se encontró, entonces
    //  Viajar hasta la arista con menor peso que tenga "cookie" en falso
    //bool isWay = 0;//Hay camino o se está estancado
    for (it1 = n1->edges.begin(); it1 != n1->edges.end(); ++it1)
    {
        if ((*it1)->cookie == false && (*it1)->value < minEd->value)
        {
            //isWay = true;
            minEd = *it1;
        }
            
    }
    if (!minEd)//Si se atascó (bucle o camino sin salida)
    {
       
    }
   

    
}
*/



class CGraphCity : public CGraph<Coord, int>
{
    // algoritmos optimizados con coordenas
    /*
     busquedas direccionada
     precalculo
     etc
     */
};

class CGraphChar : public CGraph<char, int>
{
    // algoritmos no optimizados
    void Print();
    /*
     implementar dikjstra, etc
     */
};

int main()
{
    CGraph<int, int> g1;
    cout << g1.InsNode(50);
    cout << g1.InsNode(60);
    cout << g1.InsNode(70);
    cout << g1.InsNode(80);
    cout << g1.InsEdge(50, 60, 5, 0);
    cout << g1.InsEdge(50, 70, 15, 0);
    //cout<<g1.RemEdge(50,60,5);
    //cout<<g1.RemEdge(50,70,15);
    
    //cout << g1.RemNode(50) << endl;
    g1.PrintNodes();
    g1.PrintEdges();
    g1.Distance(50, 70);
    //g1.Dijkstra(50,60);

}
