#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
using namespace std;

int n;
char ch[3];

void work(int num, int from, int by, int to)
{
	if (num == 1)
	{
		cout << ch[from] << "->" << num << "->" << ch[to] << endl;
		return;
	}
	work(num - 1, from, to, by);
	cout << ch[from] << "->" << num << "->" << ch[to] << endl;
	work(num - 1, by, from, to);
}

int main()
{
	cin >> n >> ch[0] >> ch[1] >> ch[2];
	work(n, 0, 1, 2);
	return 0;
}
