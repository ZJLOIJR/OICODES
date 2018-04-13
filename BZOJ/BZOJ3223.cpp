#include <cmath>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;
 
const int N = 100007;
 
int n, q, u, v;
 
inline int read()
{
    int x = 0, f = 0;
    char c = getchar();
    for (; c < '0' || c > '9'; c = getchar()) if (c == '-') f = 1;
    for (; c >= '0' && c <= '9'; c = getchar()) x = (x << 1) + (x << 3) + c - '0';
    return f ? -x : x;
}
 
inline void swap(int &a, int &b)
{
    int t = a;
    a = b, b = t;
}
 
struct SplayTree
{
    int fa[N], son[N][2], key[N], tag[N], siz[N];
    int root, tot;
 
    void init() { tot = 0, root = 0; }
 
    void down(int x)
    {
        if (x == 0 || tag[x] == 0) return;
        swap(son[x][0], son[x][1]);
        tag[son[x][0]] ^= 1, tag[son[x][1]] ^= 1;
        tag[x] = 0;
    }
 
    void update(int x) { if (x) siz[x] = siz[son[x][0]] + siz[son[x][1]] + 1; }
 
    int get(int x) { return son[fa[x]][1] == x; }
 
    void rotate(int x)
    {
        int y = fa[x], z = fa[y], kind = !get(x);
        son[y][!kind] = son[x][kind];
        if (son[x][kind])
            fa[son[x][kind]] = y;
        fa[x] = z;
        if (z)
            son[z][get(y)] = x;
        son[x][kind] = y, fa[y] = x;
        down(y), down(x);
        update(y), update(x);
    }
 
    void splay(int x, int anc)
    {
        while (fa[x] != anc)
        {
            int y = fa[x];
            if (fa[y] == anc)
                rotate(x);
            else
                rotate(get(x) == get(y) ? y : x);
        }
        if (anc == 0)
            root = x;
    }
 
    void insert(int x)
    {
        if (!root)
            root = ++tot, fa[root] = 0, key[root] = x, tag[root] = 0, siz[root] = 1;
        else
        {
            int now = root;
            while (2333)
            {
                siz[now]++;
                if (!son[now][x > key[now]])
                {
                    son[now][x > key[now]] = ++tot, fa[tot] = now, key[tot] = x, tag[tot] = 0, siz[tot] = 1;
                    break;
                }
                now = son[now][x > key[now]];
            }
            splay(tot, 0);
        }
    }
 
    int findkth(int k)
    {
        int now = root, cnt;
        while (2333)
        {
            down(now);
            cnt = siz[son[now][0]];
            if (k - 1 == cnt) return now;
            else if (k - 1 < cnt) now = son[now][0];
            else now = son[now][1], k -= cnt + 1;
        }
    }
 
    void reverse(int l, int r)
    {
        int lx = findkth(l), rx = findkth(r + 2);
        splay(lx, 0);
        splay(rx, lx);
        tag[son[son[root][1]][0]] ^= 1;
    }
 
    void print(int x)
    {
        if (x == 0)
            return;
        down(x);
        print(son[x][0]);
        if (key[x] != 2147483647 && key[x] != -2147483647) printf("%d ", key[x]);
        print(son[x][1]);
    }
} tree;
 
int main()
{
    tree.init();
    n = read(), q = read();
    tree.insert(-2147483647);
    for (int i = 1; i <= n; i++)
        tree.insert(i);
    tree.insert(2147483647);
    while (q--)
    {
        u = read(), v = read();
        tree.reverse(u, v);
    }
    tree.print(tree.root);
    return 0;
}
