#include <iostream>

class CVector
{
public:
    CVector(int size)
    {
        m_size = size;
        m_v = new int[m_size];
        m_nelem = 0;
    }
    ~CVector()
    {
        delete m_v;
    }

    void expand()
    {
        int* p = new int[2 * m_size];
        for (int i = 0; i < m_size; i++)
            p[i] = m_v[i];
        delete m_v;
        m_v = p;
        m_size = 2 * m_size;
    }

    void push_back(int x)
    {
        if (m_nelem == m_size)
            expand();
        m_v[m_nelem] = x;
        m_nelem++;
    }

    void pop_back()
    {
        m_nelem--;
    }

    void push_front(int x)
    {
        if (m_nelem == m_size)
            expand();
        for (int i = m_nelem - 1; i >= 0; i--)
            m_v[i + 1] = m_v[i];
        m_v[0] = x;
        m_nelem++;
    }

    void pop_front()
    {
        for (int i = 0; i < m_nelem - 1; i++)
            m_v[i] = m_v[i + 1];
        m_nelem--;
    }

    void print()
    {
        for (int i = 0; i < m_nelem; i++) {
            std::cout << m_v[i] << ' ';
        }std::cout << std::endl;
    }
    int& operator[](int i)
    {
        return m_v[i];
    }
private:
    int* m_v;
    int m_size;
    int m_nelem;
};

int main()
{
    CVector v(5);
    v.push_back(2);
    v.push_back(7);
    v.push_back(9);
    v.push_back(1);
    v.push_back(3);
    v.push_back(8);
    v.pop_back();
    v.pop_front();

    v.print();

    int a = v[2];
    v[2] = 1;

    a = 1;


}