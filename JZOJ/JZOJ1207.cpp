#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;

typedef long long ll;
const int LEN = 256, P = 19260817;

int n, m, len, ans, sum;
bool buc[P];
char str[LEN];

int id(char c) { return c >= 'a' && c <= 'z' ? c - 'a' : c - 'A' + 26; }

struct largeint
{
	int len, arr[2107];
	void print() { for (int i = len; i >= 1; i--) printf("%d", arr[i]); }
	largeint operator=(largeint a) { len = a.len; memcpy(arr, a.arr, sizeof(a.arr)); }
	largeint operator+(largeint a)
	{
		largeint ret;
		ret.len = 0; memset(ret.arr, 0, sizeof(ret.arr));
		ret.len = max(len, a.len);
		for (int i = 1; i <= ret.len; i++)
		{
			ret.arr[i] += arr[i] + a.arr[i];
			ret.arr[i + 1] += ret.arr[i] / 10;
			ret.arr[i] %= 10;
		}
		if (ret.arr[ret.len + 1]) ret.len++;
		return ret;
	}
} a, b, c;

int main()
{
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; i++)
	{
		scanf("%s", str);
		len = strlen(str), sum = 0;
		for (int j = 0; j < len; j++) sum = (sum * 255LL % P + id(str[j])) % P, buc[sum] = 1;
	}
	while (m--)
	{
		scanf("%s", str);
		len = strlen(str), sum = 0;
		int flag = 1;
		for (int j = 0; j < len; j++)
		{
			sum = (sum * 255LL % P + id(str[j])) % P;
			if (!buc[sum]) { flag = 0; break; }
		}
		ans += flag;
	}
	printf("%d\n", ans);
	if (n == 1) printf("1\n");
	else if (n == 2) printf("2\n");
	else
	{
		a.arr[a.len = 1] = 1, b.arr[b.len = 1] = 2;
		for (int i = 3; i <= n; i++) c = a + b, a = b, b = c;
		c.print();
	}
	return 0;
}
