#pragma GCC optimize(2) //不想打一般的字符串哈希了，只能无耻开O(2)
#include <map>
#include <iostream>
#include <string>
using namespace std;

const int N = 200000;

int n, m, tot = 0, fa[N * 2 + 7];
string a, b, c;
map<string, int> buc;

int getfa(int x) { return fa[x] == x ? x : fa[x] = getfa(fa[x]); }
void link(int x, int y) { fa[getfa(y)] = getfa(x); }

int main()
{
	ios::sync_with_stdio(false);
	cin >> n >> m;
	for (int i = 1; i <= 400000; i++) fa[i] = i;
	for (int i = 1; i <= n; i++)
	{
		cin >> a >> b >> c;
		if (!buc[a]) buc[a] = ++tot;
		if (!buc[b]) buc[b] = ++tot;
		int x = buc[a], y = buc[b];
		if (c[0] == 'p')
		{
			if (getfa(x + N) == getfa(y) || getfa(x) == getfa(y + N))
			{
				printf("Waterloo\n");
				return 0;
			}
			link(x, y), link(x + N, y + N);
		}
		else
		{
			if (getfa(x + N) == getfa(y + N) || getfa(x) == getfa(y))
			{
				printf("Waterloo\n");
				return 0;
			}
			link(x + N, y), link(x, y + N);
		}
	}
	for (int i = 1; i <= m; i++)
	{
		cin >> a >> b;
		if (!buc[a] || !buc[b]) printf("unknown\n");
		else
		{
			int x = buc[a], y = buc[b];
			if (getfa(x) == getfa(y) || getfa(x + N) == getfa(y + N)) printf("parallel\n");
			else if (getfa(x + N) == getfa(y) || getfa(x) == getfa(y + N)) printf("intersect\n");
			else printf("unknown\n");
		}
	}
	return 0;
}
