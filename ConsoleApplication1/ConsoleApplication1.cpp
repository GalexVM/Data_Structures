#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
using namespace std;
using vi = vector<int>;
using Mat = vector<vi>;


class Matrix {
public:
	int f, c;
	Matrix(int a, int b)
	{
		f = a; c = b;
	}
};
class Dp_el {
public:
	int v=0, f, c;
};
class Mat_S {
public:
	int k;
	string s = "";
};
using MatS = vector<vector<Mat_S>>;
using vdp = vector<vector<Dp_el>>;
int MatMultDp(vector<Matrix> mats, vdp dp = vdp(100, vector<Dp_el>(100)));
string MatMultDp2(vector<Matrix> mats, vdp dp = vdp(100, vector<Dp_el>(100)), MatS r = MatS(100,vector<Mat_S>(100)));
int min_e(vi V);
void PrintDp(vdp dp, int N);
int main() {
	Matrix m1(1, 2);
	Matrix m2(2, 5);
	Matrix m3(5, 1);
	Matrix m4(1, 10);
	vector<Matrix> V{ m1,m2,m3,m4 };

	cout << MatMultDp(V) << endl;
	cout << MatMultDp2(V) << endl;
}
int min_e(vi V)
{
	int minIn = 0;
	for (int i = 0; i < V.size(); i++)
	{
		if (V[i] < V[minIn])
		{
			int t = minIn;
			minIn = i;
			i = t;
		}
	}
	return minIn;
}
string MatMultDp2(vector<Matrix> mats, vdp dp, MatS r)
{
	int N = mats.size();
	for (int i = 0; i < N - 1; i++)
	{
		dp[i][i].v = 0; dp[i][i].f = mats[i].f; dp[i][i].c = mats[i].c; //Rellenar valores iniciales
		dp[i][i + 1].v = mats[i].f * mats[i].c * mats[i + 1].c;
		dp[i][i + 1].f = mats[i].f; dp[i][i + 1].c = mats[i + 1].c;
		r[i][i + 1].s = "(" + to_string(i) + "*" + to_string(i + 1) + ")";

	}
	dp[N - 1][N - 1].v = 0;
	dp[N - 1][N - 1].f = mats[N - 1].f;
	dp[N - 1][N - 1].c = mats[N - 1].c;

	
	for (int l = 1; l < N; l++)
	{
		int j = l;
		int i = 0;
		while (j < N)//avanzar en diagonal
		{
			if (i != j && j != i + 1)
			{
				vi temp;
				for (int k = i; k < j; k++)
					temp.push_back(dp[i][k].v + dp[k + 1][j].v +
						(dp[i][k].f * dp[i][k].c * dp[k + 1][j].c));
				dp[i][j].f = mats[i].f; dp[i][j].c = mats[j].c;
				
				int minIn = min_e(temp);
				dp[i][j].v = temp[minIn];//valor mínimo dependiendo de k
				
				//Para imprimir
				r[i][j].k = i + minIn; //guardar el k que dió el óptimo 
				string str1, str2;
				str1 = r[i][r[i][j].k].s;
				str2 = r[r[i][j].k + 1][j].s;
				if (str1 == "") str1 = "(" + to_string(i) + ")";
				if (str2 == "") str2 = "(" + to_string(j) + ")";

				r[i][j].s = "(" + str1 + "*" + str2 + ")";

				
			}
			i++; j++;
		}
	}
	//PrintDp(dp, N);

	return r[0][N-1].s;
}
int MatMultDp(vector<Matrix> mats, vdp dp)
{
	int N = mats.size();
	for (int i = 0; i < N - 1; i++)
	{
		dp[i][i].v = 0; dp[i][i].f = mats[i].f; dp[i][i].c = mats[i].c;
		dp[i][i + 1].v = mats[i].f * mats[i].c * mats[i + 1].c;
		dp[i][i + 1].f = mats[i].f; dp[i][i + 1].c = mats[i + 1].c;
	}
	//PrintDp(dp, N);
	dp[N - 1][N - 1].v = 0; 
	dp[N - 1][N - 1].f = mats[N - 1].f; 
	dp[N - 1][N - 1].c = mats[N - 1].c;

	for (int l = 1; l < N; l++)
	{
		int j = l;
		int i = 0;
		while (j < N)
		{
			if (i != j && j != i + 1)
			{
				vi temp;
				for (int k = i; k < j; k++)
					temp.push_back(dp[i][k].v + dp[k + 1][j].v + 
						(dp[i][k].f * dp[i][k].c * dp[k + 1][j].c));
				dp[i][j].v = *min_element(temp.begin(), temp.end());
				dp[i][j].f = mats[i].f; dp[i][j].c = mats[j].c;
			}
			i++; j++;
		}
	}
	//PrintDp(dp, N);
	return dp[0][N - 1].v;
}

void PrintDp(vdp dp, int N)
{
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			cout << dp[i][j].v << '(' << dp[i][j].f << ' ' << dp[i][j].c << ')' << '\t';
		}
		cout << endl;
	}
	cout << endl;
}