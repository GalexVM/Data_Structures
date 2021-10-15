#include <iostream>
using namespace std;

int mod(int a, int b);

template <class T>
class cPage {
public:
    T* ini_log;
    T* ini_fis;
    T* fin_log;
    T* fin_fis;
    int m_size;
    cPage(int size) {
        m_size = size;
        ini_fis = new T[size];
        ini_fis[0] = 4;
        fin_fis = ini_fis + size;
        ini_log = ini_fis + size / 2;
        fin_log = ini_log;
    }
    ~cPage() {
        delete[] ini_fis;
    }
    int& operator[](int i)
    {
        return ini_fis[i];
    }
    void print() {
        cout << endl;
        for (int i = 0; i < m_size; i++)
            cout << ini_fis[i] << " ";
    }
};

template <class T>
class cDeque {
public:
    cPage<T>** map;
    cPage<T>* ini_log;
    cPage<T>* ini_fis;
    cPage<T>* fin_log;
    cPage<T>* fin_fis;
    int nelem = 0;
    int m_size;
    int vm, vp, mv, pv;
    cDeque(int size) {
        map = new cPage<T>*[size];
        m_size = size;
        vp = vm = mv = pv = m_size / 2;
        for (int i = 0; i < size; i++) {
            map[i] = new cPage<T>(size);
        }
        init_pointers();
    }
    ~cDeque() {
        delete[] map;
    }
    void init_pointers() {
        ini_fis = *map;
        fin_fis = map[m_size - 1];
        ini_log = fin_log = map[m_size / 2];
    }
    void extend_map_front() {
        cPage<T>** p = new cPage<T>*[2 * m_size];
        for (int i = 0; i < m_size; i++)
            p[i] = new cPage<T>(m_size);
        for (int i = m_size; i < m_size * 2; i++)
            p[i] = map[i - m_size];
        delete map;
        map = p;
        m_size = 2 * m_size;
        init_pointers();
    }
    void extend_map_back() {
        cPage<T>** p = new cPage<T>*[2 * m_size];
        for (int i = 0; i < m_size; i++)
            p[i] = map[i];
        for (int i = m_size; i < m_size * 2; i++)
            p[i] = new cPage<T>(m_size);
        delete map;
        map = p;
        m_size = 2 * m_size;
        init_pointers();
    }
    void push_front(T x) {
        cPage<T>* pagina;
        T* p;

        if (vp == 0)
            vm--;

        if (vm == 0)
            extend_map_front();

        if (nelem > 0)
            vp = mod(vp - 1, m_size);


        pagina = (*map + vm);

        p = (*pagina).ini_fis;
        cout << (*pagina).ini_fis << endl;
        p += vp;
        cout << p << endl;

        *p = x;
        cout << "aaaaaaaaaaaa" << endl;
        cout << *p;
        nelem++;
        pagina->print();
        //cout<<endl<<(*map + 1)->ini_fis<<endl;
    }

    void push_back(T x) {

        if (mv == 0)
            extend_map_back();

        ini_fis[vm + (nelem / m_size)][mod(vp + nelem, m_size)] = x;

        nelem++;

        cPage<T>* pagina = (*map + vm);

        pagina->print();
        cout << 'a' << endl;
    }
    T pop_front() {
        T& p = ini_fis[vm][vp];
        T v = p;
        vp = mod(vp + 1, m_size);
        p = 0;
        nelem--;
        ini_fis[vm].print();

        return v;
    }
    T pop_back() {
        T& p = ini_fis[vm + (nelem / m_size)][mod(vp + nelem - 1, m_size)];
        T v = p;
        p = 0;
        nelem--;
        ini_fis[vm].print();
        return v;
    }
    T& operator[](int i) {
        //int vacios = (ini_log->ini_log) - (ini_log->ini_fis);
        //cout<<vm<<vp<<endl;
        return ini_fis[i / m_size + vm][i % m_size + vp];
        //return *(*(map + ((i/m_size)+vm)) + (mod(i,m_size)+vp));
    }
    void print()
    {
        std::cout << "\n";
        for (int i = 0; i < nelem; i++)
            cout << map[i]->print << " ";
    }
};

int mod(int a, int b) {
    int q = a / b;
    int	r = a - (q * b);
    if (a < int(0)) {
        int ar = r;
        r = b + ar;
    }
    return r;
}

int main() {
    cDeque<int> deq(5);
    //deq.push_back(5);
   // deq.push_back(6);
    //deq.push_front(4);
    deq.push_front(3);
    deq.push_front(1);
    //deq.push_back(2);
    //deq.push_front(2);
    //deq.push_back(7);
    //deq.pop_front();
    //deq.pop_back();
    //deq.push_front(9);
    //deq.push_back(8);
    //cout<<deq.pop_back()<<endl;
    //cout << deq[0] << endl;
    //cout << *(deq.fin_log->fin_log) << endl;

}