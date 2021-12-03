#include<deque>
#include<list>

template<class G>
struct CNode
{
    typedef typename G::Edge    Edge;
    typedef typename G::N       N;

    N value;
    std::list<Edge*> edges;
};

template<class G>
struct CEdge
{
    typedef typename G::Node    Node;
    typedef typename G::E       E;

    E value;
    Node* nodes[2];
    bool dir; // 0 -> bidireccional, 1 -> [0]->[1]
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

    bool InsNode(N n);
    bool InsEdge(Node* a, Node* b, E e, bool d);
    bool RemEdge(Node* a, Node* b, E e);
    bool RemNode(N n);

    std::deque<Node*> nodes;
};

struct Coord
{
    float x, y;
};


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
    CGraphChar g1;
    CGraphCity g2;
}