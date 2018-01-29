#include <cmath>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;

const int M = 5e4 + 7, L = 57;

int m, k, l, n, cnt = 0, tot = 0, ans = 0;
int st[M * L / 2], to[M * L / 2], nx[M * L / 2], id[M * L / 2], pos[M * L / 2], w1[M * L / 2], w2[M * L / 2], vis[M * L / 2];
int val[M * L / 2], son[M * L / 2][26]; //玄学,必须/2,不然MLE
char str[L];

inline void add(int u, int v) { to[++tot] = v, nx[tot] = st[u], st[u] = tot; } //加边

void insert(char *s, int po)
{
	int now = 0;
	while (*s != '\0')
	{
		int num = *s - 'A';
		if (!son[now][num]) son[now][num] = ++cnt, add(cnt, now); //字典树添加,同时建图,便于叶子节点往根走
		now = son[now][num];
		s++;
	}
	val[now]++, id[po] = now; //id[i]表示叶子节点i在字典树中的编号
}

int getw(int x)
{
	if (~w2[x]) return w2[x]; //这里使用了记忆化搜索
	w2[x] = val[x];
	for (int i = st[x]; i; i = nx[i]) w2[x] += getw(to[i]); //把路上的金子数目加起来
	return w2[x];
}

int dfs(int x)
{
	if (vis[x]) return 0; //已走过,不能走
	vis[x] = 1; int ret = val[x]; //标记为走过
	for (int i = st[x]; i; i = nx[i]) ret += dfs(to[i]); //把路上的金子数目加起来
	return ret;
}

void init()
{
	scanf("%d%d%d%d", &m, &k, &l, &n);
	for (int i = 1; i <= m; i++)
	{
		scanf("%s", str);
		insert(str, i);
	}
}

void solve()
{
	memset(w2, 0xff, sizeof(w2)); //0xff赋进w2后是0xffffffff,即-1
	for (int i = 1; i <= m; i++) w1[i] = getw(id[i]); //先处理出每个叶子节点所能得到的金子数
	for (int i = 1; i <= m; i++) pos[i] = i; 
	sort(pos + 1, pos + m + 1, [](int x, int y) { return w1[x] > w1[y]; }); //骚排序法,请查lambda表达式,仅限C++11贵族VIP7才可享用,也就是从大到小
	memset(w1, 0, sizeof(w1));
	for (int i = 1; i <= m; i++) w1[i] = dfs(id[pos[i]]); //从叶子节点往根走,统计出金子数
	sort(w1 + 1, w1 + m + 1); //从小到大排序
	for (int i = m; i >= m - n + 1; i--) ans += w1[i]; //从大到小选n个
	printf("%d\n", ans);
}

int main()
{
	init();
	solve();
	return 0;
}
