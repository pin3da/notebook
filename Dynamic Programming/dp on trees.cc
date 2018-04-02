/**
 *  for any node, save the total answer and the answer of every children.
 *  for the query(node, pi) the answer is ans[node] - partial[node][pi]
 *  cases:
 *    - all children missing
 *    - no child is missing
 *    - missing child is current pi
 * */
void add_edge(int u, int v) {
  int id_u_v = g[u].size();
  int id_v_u = g[v].size();
  g[u].emplace_back(v, id_v_u); // id of the parent in the child's list (g[v][id] -> u)
  g[v].emplace_back(u, id_u_v); // id of the parent in the child's list (g[u][id] -> v)
}
