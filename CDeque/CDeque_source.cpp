#include <iostream>
using std::cout;
using std::endl;

int mod(int a, int b);

class CVector
{
public:
    CVector(int size = 5)
    {
        m_size = size;
        m_v = new int[m_size];
        m_nelem = 0;
    }

    ~CVector()
    {
        delete m_v;
    }

    int& operator[](int i)
    {
        return m_v[i];
    }

    void print() {
        for (int i = 0; i < m_size; i++) {
            std::cout << m_v[i] << std::endl;
        }
    }
private:
    int* m_v;
    int m_size;
    int m_nelem;
};

class CDeque
{
public:
    CDeque(int size = 5) {
        m_size = size;
        m_nvect = 1;
        m_nelemTotales = 0;
        bg = end = centerController = m_size / 2;
        vectController = 2;
        indexController = -3;
        map = new CVector [m_size];
    }
    ~CDeque() {
        delete[] map;
    }
    int& operator[](int i) {
        return map[i / m_size][i%m_size];
    }
  
    void UpdateIndexes() {
        vectController = (vectController == 0) ? 4 : vectController - 1;
        indexController = (indexController == -4) ? 0 : indexController - 1;
    }
    void addVectFront() {
        bg--;
        centerController--;
    }
    void addVectBack() {
        end++;
    }
    void push_back(int x) {
        m_nelemTotales++;
        if (mod(m_nelemTotales - 1 + indexController, m_size) == 0 && m_nelemTotales != 1) {
            addVectBack();
            m_nvect++;
        }
        map[((m_nelemTotales - 1 + vectController) / m_size)+centerController][mod(m_nelemTotales - 1 + indexController, m_size)] = x;
           
    }
    void print() {
        
        if (bg == end) {
            map[bg].print();
        }
        else {
           
            for (int i = bg; i <= end; i++) {
                map[i].print();
                cout << endl;
            }
        }
        
    }
private:
    CVector* map;
    int m_size;
    int m_nvect;
    int m_nelemTotales;
    int bg, end;
    int vectController, indexController, centerController;
};


int main() {
    CDeque deque1;
    for (int i = 0; i < 13; i++) {
        deque1.push_back(i);
    }
   
    deque1.print();
    return 0;
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

