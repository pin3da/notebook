/**
 *  Important notes:
 *   - When using lazy propagation remembert to create new versions for each push_down operation!!!
 *   - remember to set left and right pointers to NULL
 * */

struct node {
  long long ans, pending;
  node *left, *right;
  node() : ans(0), left(NULL), right(NULL), pending(0) {}
};
