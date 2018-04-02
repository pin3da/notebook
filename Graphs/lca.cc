void init(vector<vector<edge> > &g, int root) {
  // g is undirected
  dfs(g, root);
  int N = g.size(), i, j;

  for (i = 0; i < N; i++) {
    for (j = 0; 1 << j < N; j++) {
      P[i][j] = -1;
      MI[i][j] = inf;
    }
  }

  for (i = 0; i < N; i++) {
    P[i][0] = T[i];
    MI[i][0] = W[i];
  }

  for (j = 1; 1 << j < N; j++)
    for (i = 0; i < N; i++)
      if (P[i][j - 1] != -1) {
        P[i][j] = P[P[i][j - 1]][j - 1];
        MI[i][j] = min(MI[i][j-1], MI[ P[i][j - 1] ][j - 1]);
      }
}

