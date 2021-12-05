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
        cout << aNode << " -> " << bNode << ": " << minDis << endl;
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
    Tag tag;
    bool cookie = 0;
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
    void BuildMap(); //Ejecuta dijkstra en cada nodo y arma
    void Dijkstra(Node *n);//Llena las etiquetas de cada nodo respecto de el seleccionado
    void AddMap(Node *n);//Agrega mapas a fullMap con la información de las etiquetas. a = n, b = x
    void HallarPredecesor(Node* n, Node* p);
    void PrintMap();
    


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

template<class _N, class _E>
void CGraph<_N, _E>::BuildMap()
{ 
    auto i = nodes.begin();//Elegir un nodo al azar para empezar
    //Dijkstra(*i);
    //AddMap(*i);
    for (; i != nodes.end(); ++i)
    {
        Dijkstra(*i);
        AddMap(*i);
    }
    
}
template<class _N, class _E>
void CGraph<_N, _E>::Dijkstra(Node *n)
{
    Node* p = n;
    Edge* min = 0;
    (*p).tag.Reset();
    deque<Edge*> minArray;
    for (int x  = 0; x < nNodes-1; ++x )
    {
        (*p).cookie = true;
        auto j = (*p).edges.begin();
        for (; j != (*p).edges.end(); ++j)
        {
            if ((*j)->nodes[0] == p || (*j)->dir == 0)//Si sale del nodo o es bidireccional
            {
                //cout << (*j)->nodes[0]->value << (*j)->nodes[1]->value << endl;
                minArray.push_back(*j);//Añadir los valores de los nodos
            }
        }
        for (int i = 0; i < minArray.size(); ++i)//Mínimo provisional
        {
            if (minArray[i]->nodes[1]->cookie == 0)
            {
                min = minArray[i];
                break;
            }
               
        }
        for (int i = 0; i < minArray.size(); ++i)//Recorrer para obtener el mínimo
        {
            
            if (minArray[i]->dir == 1)
            {
                if(minArray[i]->value + (minArray[i]->nodes[0]->tag.pAcumulado) <
                    minArray[i]->nodes[1]->tag.pAcumulado ||
                    (minArray[i]->nodes[1]->tag.pAcumulado == 0 &&
                    minArray[i]->nodes[1] != n)
                    )//Solo setear el tag si va a ser para un camino más corto, o si hay un 0
                    minArray[i]->nodes[1]->tag.Set(minArray[i]->value + (minArray[i]->nodes[0]->tag.pAcumulado),
                                                    minArray[i]->nodes[0],
                                                    1 + (minArray[i]->nodes[0]->tag.nPasos));
            }
            else
            {
                //...
            }
            if (minArray[i] &&
                minArray[i]->nodes[1]->tag.pAcumulado < min->nodes[1]->tag.pAcumulado &&
                minArray[i]->nodes[1]->cookie == 0)
            {
                min = minArray[i];
            }
        }

        p = min->nodes[1];
        //cout << "Permanente: " << p->value << endl;
        //p->tag.Print();
        for (int i = 0; i < minArray.size(); ++i)//Eliminar min del array
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
void CGraph<_N, _E>::AddMap(Node *n)
{
    for (int i = 0; i < nNodes; ++i)//Agregar a fullmap
    {
        Map* x = new Map;
        x->Set(n->value, nodes[i]->value, nodes[i]->tag.pAcumulado);//Ingresar nodo de ida, de llegada, recorrido
        
        /*for (int j = 0; j < nodes[i]->tag.nPasos; j++)
        { 
            if (!(i == nodes[i]->tag.nPasos - 1))//primera iteración
            {
                Node* p = 0;
               
                HallarPredecesor(nodes[i - 1], p);
               
                x->minRec.push_front(p);
            }
            else
            {
               x->minRec.push_front(nodes[i]->tag.nAnterior);
            }
                
        }    */
        fullMap.push_back(x);
        
    }
    for (int i = 0; i < nNodes; ++i)//limpiar todos los tags y cookies
    {
        nodes[i]->tag.Reset();
        nodes[i]->cookie = 0;
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

template<class _N, class _E>
void CGraph<_N, _E>::HallarPredecesor(Node* n, Node* p)
{
    p = n->tag.nAnterior;
}

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
    g1.BuildMap();
    g1.PrintMap();
 

}
