#include <iostream>

using std::cout;
using std::endl;

template<class T>
class CPage {
	T* array;
	int p_size;
	int n_elem;
public:
	CPage(int s) {
		p_size = s;
		array = new T[p_size];
		n_elem = 0;
	}
	~CPage() {
		delete array;
	}
	T& operator[](int i) {
		return array[i];
	}
	
	void print() {
		T* p = array;
		for (int i = 0; i < p_size; i++)
			cout << array[i] << " ";
		
		cout << endl;
	}
};

int mod(int a, int b);

template<class T>
class CDeque {
	CPage<T>** map;
	CPage<T>* head;
	int n_elem, n_pags, p_size, pageSpaces, mapSpaces;
public:
	CDeque(int s) {
		p_size = s;
		n_elem = 0;
		n_pags = 1;
		pageSpaces = mapSpaces = s/2;
		map = new CPage<T>*[p_size];
		map[s/2] = new CPage<T>(p_size);
		head = *(map + mapSpaces);
	}
	void push_front(T x){
		
		if (pageSpaces == 0) {
			mapSpaces--;
			map[mapSpaces] = new CPage<T>(p_size);
			head = *(map + mapSpaces);
		}
		//if (mapSpaces == 0)
			//extend_map_front();

		pageSpaces = mod(pageSpaces - 1, p_size);//Reducir los espacios
		CPage<T>* pagina = map[mapSpaces]; 
		(*pagina)[pageSpaces] = x;
		n_elem++;
	}
	void push_back(T x) {
		if ((n_elem + 1 + pageSpaces) % p_size == 1 && n_elem + 1 != 1) {
			
			map[n_pags + mapSpaces] = new CPage<T>(p_size);
			n_pags++;
			cout << "nueva pag agregada\n";
		}
		
		CPage<T>* aux = map[mapSpaces + ((n_elem + pageSpaces) / 5)];
		(*aux)[(pageSpaces + n_elem) % 5] = x;
		n_elem++;
	}
	T pop_front() {

	}
	T pop_back() {

	}
	void print() {
		
		for (int i = 0; i < n_pags; i++) {

			(*head).print();	
			head = *(map + mapSpaces + i + 1);
			
		}
		cout << endl;
		head = *(map + mapSpaces);
	}
	T& operator[](int i) {
		CPage<T>* aux = map[mapSpaces + ((i + pageSpaces) / p_size)];
		if (i > (n_pags * p_size)-1) {
			return(*aux)[((n_pags * p_size) - 1) % p_size];//último valor disponible
		}
		return (*aux)[(i + pageSpaces) % p_size];
		
	}
	~CDeque(){
		delete[] map;
	}
	
};



int main() {
	CPage<int> pag1(5);
	CDeque<int> deque1(5);
	deque1.push_back(0);
	deque1.push_back(1);
	deque1.push_back(2);
	deque1.push_back(3);
	/*deque1.push_back(4);
	deque1.push_back(5);
	deque1.push_back(6);
	deque1.push_back(7);
	deque1.push_back(8);
	deque1.push_back(9);
	deque1.push_back(10);
	deque1.push_back(11);*/

	deque1.push_front(1);
	deque1.push_front(2);
	deque1.push_front(3);
	
	deque1.print();
	cout << deque1[5];
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