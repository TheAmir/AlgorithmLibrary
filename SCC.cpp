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

class SCC
{
private:
	vector<vector<int> > gt;
	vector<int> f;
	vector<bool> tk;
public:
	vector<int> SCCG;
	vector<vector<int> > g;
	vector<vector<int> > dag;

	void dfs1(int i)
	{
		tk[i] = true;
		for (int j = 0; j < g[i].size(); j++)
		{
			if (!tk[g[i][j]]) dfs1(g[i][j]);
		}
		f.push_back(i);
	}
	void dfs2(int i, int group)
	{
		tk[i] = true;
		SCCG[i] = group;
		for (int j =0; j < gt[i].size(); j++)
		{
			if (!tk[gt[i][j]]) dfs2(gt[i][j], group);
		}
	}

	void computeSCC()
	{
		SCCG = vector<int> (g.size(), -1);
		tk = vector<bool> (g.size(), false);
		f.clear();
		for (int i = 0; i < g.size(); i++)
		{
			if (!tk[i]) dfs1(i);
		}
		gt = vector<vector<int> >(g.size());
		for (int i = 0; i < g.size(); i++)
		{
			for (int j = 0; j < g[i].size(); j++)
			{
				gt[g[i][j]].push_back(i);
			}
		}
		int gr = 0;
		tk = vector<bool>(g.size(), false);
		for (int i = f.size()-1; i >= 0; i--)
		{
			if (!tk[f[i]])
			{
				dfs2(f[i], gr);
				gr++;
			}
		}
		dag = vector<vector<int> > (gr);
		set<pair<int, int> > edges;
		
		for (int i = 0; i < g.size(); i++)
		{
			for (int j = 0; j < g[i].size(); j++)
			{
				int u, v;
				u = i;
				v = g[i][j];
				if (SCCG[u] != SCCG[v])
				{
					if (edges.count(make_pair(SCCG[u], SCCG[v])) == 0)
					{
						dag[SCCG[u]].push_back(SCCG[v]);
						edges.insert(make_pair(SCCG[u], SCCG[v]));
					}

				}
			}
		}
	}	
};
