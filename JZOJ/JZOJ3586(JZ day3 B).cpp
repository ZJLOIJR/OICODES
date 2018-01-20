#include <cmath>
#include <cstdio>
#include <string>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <algorithm>
using namespace std;

struct person
{
	string name;
	int score;
} a[11];

int n, m, len, tot, none = 0;
char str[1007];

int cmp(person x, person y)
{ return x.score > y.score; }

int main()
{
	cin >> n >> m;
	for (int i = 1; i <= n; i++)
	{
		cin >> a[i].name;
		a[i].score = 0;
	}
	for (int i = 1; i <= m; i++)
	{
		scanf("%s", str + 1);
		len = strlen(str + 1), tot = 0;
		for (int j = 1; j <= len; j++) if (str[j] == 'X') tot++;
		if (tot == 0 || tot > 1) none++;
		else
			for (int j = 1; j <= len; j++)
				if (str[j] == 'X') a[j].score++;
	}
	stable_sort(a + 1, a + n + 1, cmp);
	for (int i = 1; i <= n; i++)
	{
		cout << a[i].name << ' ';
		printf("%.2lf%c\n", a[i].score * 100.0 / m + 0.0000005, '%');
	}
	printf("Invalid %.2lf%c\n", none * 100.0 / m + 0.0000005, '%');
	return 0;
}
