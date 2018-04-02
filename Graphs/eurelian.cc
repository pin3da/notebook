struct edge;
typedef list<edge>::iterator iter;

struct edge {
  int next_vertex;
  iter reverse_edge;

  edge(int next_vertex) :next_vertex(next_vertex) {}
};

const int max_vertices = 6666;
int num_vertices;
list<edge> adj[max_vertices];  // adjacency list
vector<int> path;

void find_path(int v) {
  while(adj[v].size() > 0) {
    int vn = adj[v].front().next_vertex;
    adj[vn].erase(adj[v].front().reverse_edge);
    adj[v].pop_front();
    find_path(vn);
  }
  path.push_back(v);
}

void add_edge(int a, int b) {
  adj[a].push_front(edge(b));
  iter ita = adj[a].begin();
  adj[b].push_front(edge(a));
  iter itb = adj[b].begin();
  ita->reverse_edge = itb;
  itb->reverse_edge = ita;
}
