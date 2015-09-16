#include <iostream>
#include <iomanip>
#include <algorithm>
#include <vector>
#include <string>
#include <cmath>
#include <memory.h>
#include <sstream>
#include <stack>
#include <fstream>
#include <cstdio>
#include <unordered_map>
#include <map>
#include <list>
#include <queue>
#include <set>
using namespace std;

//Static 2D segment tree for sorted 2D array

vector<vector<int> > tree;

int a[801][801];

vector<int> build(int i, int x1, int x2, int y1, int y2)
{
	if (x1 > x2 || y1 > y2) return vector<int>();
	while (tree.size() <= i) tree.push_back(vector<int>());
	if (x1 == x2 && y1 == y2)
	{
		tree[i] = vector<int> (1);
		tree[i][0] = a[x1][y1];
		return tree[i];
	}
	vector<int> d[4];
	d[0] = build(i*4 + 1, x1, (x1+x2)/2, y1, (y1+y2) / 2);
	d[1] = build(i*4 + 2, (x1+x2)/2+1, x2, y1, (y1+y2) / 2);
	d[2] = build(i*4 + 3, x1, (x1+x2)/2, (y1+y2)/2+1, y2);
	d[3] = build(i*4 + 4, (x1+x2)/2+1, x2, (y1+y2)/2+1, y2);
	priority_queue<pair<int, int> > q;
	int in[4] = {0};
	for (int j = 0; j < 4; j++)
	{
		if (d[j].size()) q.push(make_pair(-d[j][0], j));
	}
	while (!q.empty())
	{
		pair<int, int> cur = q.top();
		q.pop();
		tree[i].push_back(-cur.first);
		in[cur.second]++;
		if (in[cur.second] < d[cur.second].size())
		{
			q.push(make_pair(-d[cur.second][in[cur.second]], cur.second));
		}
	}
	return tree[i];
}

//Get number of elements <= x in submatrix (x1,y1) => (x2, y2)
int query(int i, int x1, int x2, int y1, int y2, int a, int b, int c, int d, int x)
{
	if (x1 > x2 || y1 > y2) return 0;
	if (x1 > b || x2 < a || y1 > d || y2 < c) return 0;
	if (x1 >= a && x2 <= b && y1 >= c && y2 <= d)
	{
		return upper_bound(tree[i].begin(), tree[i].end(), x)- tree[i].begin();
	}
	int r = query(i*4 + 1, x1, (x1+x2)/2, y1, (y1+y2) / 2, a,b,c,d,x);
	r += query(i*4 + 2, (x1+x2)/2+1, x2, y1, (y1+y2) / 2, a,b,c,d,x);
	r += query(i*4 + 3, x1, (x1+x2)/2, (y1+y2)/2+1, y2, a,b,c,d,x);
	r += query(i*4 + 4, (x1+x2)/2+1, x2, (y1+y2)/2+1, y2, a,b,c,d,x);
	return r;
}
