#include <iostream>
using std::cout;
using std::endl;
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
        bg= end = m_size/2;
        map = new CVector [m_size];
    }
    ~CDeque() {
        delete[] map;
    }
    int& operator[](int i) {
        return map[i / m_size][i%m_size];
    }
    void addVectFront() {
        bg--;
    }
    void addVectBack() {
        end++;
    }
    void push_back(int x) {
        m_nelemTotales++;
        if (m_nvect == 1) {
            if (2 + (m_nelemTotales % m_size) - 1 == 5) {
                m_nvect++;
                addVectBack();
            }
            else {
                map[2 + (m_nelemTotales / (m_size - 1))][2 + (m_nelemTotales-1 % m_size) ] = x;
            }
        }
        if (m_nvect > 1) {
            if ((m_nelemTotales + 1) % m_size == 0 && m_nelemTotales != 5) {
                m_nvect++;
                addVectBack();
            }
            map[2 + ((m_nelemTotales + 1) / m_size)][((m_nelemTotales + 1) % m_size)] = x;
        }
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
};

int main() {
    CDeque deque1;
    deque1.push_back(1);
    deque1.push_back(2);
    deque1.push_back(3);
    deque1.push_back(4);
    deque1.push_back(5);
    deque1.push_back(6);
    deque1.push_back(7);
    deque1.push_back(8);
    deque1.push_back(9);
    deque1.push_back(10);
    deque1.print();
    return 0;
}

