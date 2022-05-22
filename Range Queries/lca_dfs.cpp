vector<pair<int,int>> depth;
int pos[MM];
void lca_dfs(int u=1, int p=0, int d=0) {
	if (pos[u] == -1) pos[u] = int(depth.size());
	depth.push_back({d,u});
	for (auto x : adj[u]) {
		if (x.v != p) {
			lca_dfs(x.v, u, d+1);
			depth.push_back({d,u});
		}
	}
}
