// Max number of states in the matching machine.
// Should be equal to the sum of the length of all keywords.
const int MAXS = 6 * 50 + 10;
const int MAXC = 26;
// Bit i in this mask is on if the keyword with index i
// appears when the machine enters this state.
int out[MAXS];

int f[MAXS]; // Failure function
int g[MAXS][MAXC]; // Goto function, or -1 if fail.

int buildMatchingMachine(const vector<string> &words,
    char lowestChar = 'a', char highestChar = 'z') {
  memset(out, 0, sizeof out);
  memset(f, -1, sizeof f);
  memset(g, -1, sizeof g);

  int states = 1; // Initially, we just have the 0 state

  for (int i = 0; i < words.size(); ++i) {
    const string &keyword = words[i];
    int currentState = 0;
    for (int j = 0; j < keyword.size(); ++j) {
      int c = keyword[j] - lowestChar;
      if (g[currentState][c] == -1) {
        g[currentState][c] = states++;
      }
      currentState = g[currentState][c];
    }
    // There's a match of keywords[i] at node currentState.
    out[currentState] |= (1 << i);
  }

  // State 0 should have an outgoing edge for all characters.
  for (int c = 0; c < MAXC; ++c) {
    if (g[0][c] == -1) {
      g[0][c] = 0;
    }
  }

  queue<int> q;
  // Iterate over every possible input
  for (int c = 0; c <= highestChar - lowestChar; ++c) {
    // All nodes s of depth 1 have f[s] = 0
    if (g[0][c] != -1 and g[0][c] != 0) {
      f[g[0][c]] = 0;
      q.push(g[0][c]);
    }
  }
  while (q.size()) {
    int state = q.front();
    q.pop();
    for (int c = 0; c <= highestChar - lowestChar; ++c) {
      if (g[state][c] != -1) {
        int failure = f[state];
        while (g[failure][c] == -1) {
          failure = f[failure];
        }
        failure = g[failure][c];
        f[g[state][c]] = failure;

        // Merge out values
        out[g[state][c]] |= out[failure];
        q.push(g[state][c]);
      }
    }
  }
  return states;
}
int findNextState(int currentState, char nextInput,
    char lowestChar = 'a') {
  int answer = currentState;
  int c = nextInput - lowestChar;
  while (g[answer][c] == -1) answer = f[answer];
  return g[answer][c];
}
