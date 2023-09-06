#include "rbtree.h"

#include <stdlib.h>

rbtree *new_rbtree(void) {
  rbtree *t = (rbtree *)calloc(1, sizeof(rbtree));
  // TODO: initialize struct if needed
  node_t* nil_node = (node_t*)calloc(1, sizeof(node_t));
  nil_node -> color = RBTREE_BLACK;
  t->nil = nil_node;
  t->root = nil_node;
  return t;
}

void delete_node(node_t* node, rbtree *t){
  if (node==t->nil){
    return;
  }
  delete_node(node->left,t);
  delete_node(node->right,t);
  free(node);
}

void delete_rbtree(rbtree *t) {
  if (t==NULL){
    return;
  }
  delete_node(t->root,t);
  free(t->nil);
  free(t);
}

// 왼쪽 로테이션
void rbtree_left_rotate(rbtree *t, node_t * x) {
  node_t* y = x->right;
  x->right = y->left;
  if (y->left != t->nil){
    y->left->parent = x;
  }
  y->parent = x->parent;

  if (x->parent == t->nil){
    t->root = y;
  }
  else if (x == x->parent->left){
    x->parent->left = y;
  } else {
    x->parent->right = y;
  }
  y->left = x;
  x->parent = y;
  return;
}

// 오른쪽 로테이션
void rbtree_right_rotate(rbtree *t, node_t *x) {
  node_t *y = x->left;
  x->left = y->right;
  if (y->right != t->nil){
    y->right->parent = x;
  }
  y->parent = x->parent;

  if (x->parent == t->nil){
    t->root = y;
  }
  else if (x == x->parent->right){
    x->parent->right = y;
  } else {
    x->parent->left = y;
  }
  y->right = x;
  x->parent = y;
  return;
}

// 삽입 fixup
void rbtree_inserte_fixup(rbtree* t, node_t* z){
  while (z->parent->color==RBTREE_RED){
    if (z->parent==z->parent->parent->left){
      node_t* y = z->parent->parent->right;
      if (y->color == RBTREE_RED){
        z->parent->color = RBTREE_BLACK;
        y->color = RBTREE_BLACK;
        z->parent->parent->color = RBTREE_RED;
        z = z->parent->parent;
      }else if (y->color == RBTREE_BLACK){
        if (z == z->parent->right){
          z = z->parent;
          rbtree_left_rotate(t,z);
        }
        z->parent->color = RBTREE_BLACK;
        z->parent->parent->color = RBTREE_RED;
        rbtree_right_rotate(t,z->parent->parent);
      }
    } else{
      node_t* y = z->parent->parent->left;
      if (y->color == RBTREE_RED){
        z->parent->color = RBTREE_BLACK;
        y->color = RBTREE_BLACK;
        z->parent->parent->color = RBTREE_RED;
        z = z->parent->parent;
      } else {
        if (z == z->parent->left){
          z = z->parent;
          rbtree_right_rotate(t,z);
        }
        z->parent->color = RBTREE_BLACK;
        z->parent->parent->color = RBTREE_RED;
        rbtree_left_rotate(t,z->parent->parent);
      }
    }
  }
  t->root->color = RBTREE_BLACK;
  return;
}

// 삽입
node_t* rbtree_insert(rbtree *t, const key_t key) {
  node_t* y = t->nil;
  node_t* x = t->root;
  node_t* k = (node_t*)malloc(sizeof(node_t));
  k->key = key;

  while (x != t->nil){
    y = x;
    if (k->key < x->key){
      x = x->left;
    } else {
      x = x-> right;
    }
  }
  k->parent = y;
  if (y==t->nil){
    t->root = k;
  } else if (k->key < y->key) {
    y->left = k;
  } else {
    y->right = k;
  }
  k->left = t->nil;
  k->right = t->nil;
  k->color = RBTREE_RED;
  rbtree_inserte_fixup(t,k);
  return t->root;
}

node_t* rbtree_find(const rbtree *t, const key_t key) {
  node_t* current = t->root;
  while (current != t->nil && key != current->key){
    if (key < current->key){
      current = current->left;
    } else{
      current = current->right;
    }
  }
  if (current==t->nil){
    return NULL;
  }
  return current;
}

node_t* rbtree_min(const rbtree *t) {
  node_t* current = t->root;
  while(current->left != t->nil){
      current = current->left;
  }
  return current;
}

node_t* rbtree_max(const rbtree *t) {
  node_t* current = t->root;
  while(current->right != t->nil){
      current = current->right;
  }
  return current;
}

void rbtree_transplant(rbtree* t,node_t* u,node_t* v){
  if (u->parent == t->nil){
    t->root = v;
  } else if(u==u->parent->left){
    u->parent->left = v;
  } else {
    u -> parent -> right = v;
  }
  v->parent = u->parent;
  return ;
}

void rbtree_erase_fixup(rbtree* t, node_t* x){
  node_t* w;
  while(x!= t->root && x->color == RBTREE_BLACK){
    if (x==x->parent->left){
      w = x->parent->right;
      if(w->color==RBTREE_RED){
        w->color = RBTREE_BLACK;
        x->parent->color = RBTREE_RED;
        rbtree_left_rotate(t,x->parent);
        w = x->parent->right;
      }
      if(w->left->color == RBTREE_BLACK && w->right->color == RBTREE_BLACK){
        w->color = RBTREE_RED;
        x= x->parent;
      }else{
        if(w->right->color==RBTREE_BLACK){
          w->left->color = RBTREE_BLACK;
          w->color = RBTREE_RED;
          rbtree_right_rotate(t,w);
          w = x->parent->right;
        }
        w->color = x->parent->color;
        x->parent->color = RBTREE_BLACK;
        w->right->color = RBTREE_BLACK;
        rbtree_left_rotate(t,x->parent);
        x = t->root;
      }
    } else {
      w = x->parent->left;
      if(w->color==RBTREE_RED){
        w->color = RBTREE_BLACK;
        x->parent->color = RBTREE_RED;
        rbtree_right_rotate(t,x->parent);
        w = x->parent->left;
      }
      if(w->right->color == RBTREE_BLACK && w->left->color==RBTREE_BLACK){
        w->color = RBTREE_RED;
        x = x->parent;
      } else {
        if(w->left->color == RBTREE_BLACK){
          w->right->color = RBTREE_BLACK;
          w->color = RBTREE_RED;
          rbtree_left_rotate(t,w);
          w = x->parent->left;
        }
        w->color = x->parent->color;
        x->parent->color = RBTREE_BLACK;
        w->left->color = RBTREE_BLACK;
        rbtree_right_rotate(t,x->parent);
        x = t->root;
      }
    }
  }
  x->color = RBTREE_BLACK;
  return ;
}
// 오른쪽 서브트리의 min값 찾기
node_t* search_min(rbtree*t, node_t *target){
  node_t* current = target;
  while(current->left != t->nil){
      current = current->left;
  }
  return current;
}

int rbtree_erase(rbtree *t, node_t *z) {
  node_t* x;
  node_t* y = z;
  color_t y_original_color = y->color;
  if (z->left == t->nil){
    x = z->right;
    rbtree_transplant(t,z,z->right);
  } else if (z->right == t->nil) {
    x = z->left;
    rbtree_transplant(t,z,z->left);
  } else {
    y = search_min(t,z->right);
    y_original_color = y->color;
    x = y->right;
    if (y->parent == z){
      x->parent = y;
    } else{
      rbtree_transplant(t,y,y->right);
      y->right = z->right;
      y->right->parent = y;
    }
    rbtree_transplant(t,z,y);
    y->left = z->left;
    y->left->parent = y;
    y->color= z->color;
  } if (y_original_color == RBTREE_BLACK){
    rbtree_erase_fixup(t,x);
  }
  free(z);
  z=NULL;
  return 0;
}

int rbtree_inorder(node_t *nil, node_t *root, key_t *arr, const size_t n,int idx) {
  if(root==nil){
    return idx;
  }
  if (idx==n){
    return idx;
  }
  idx = rbtree_inorder(nil, root->left, arr, n, idx);
  if (idx<n){
    arr[idx++] = root -> key;
  }
  idx = rbtree_inorder(nil, root->right, arr, n, idx);
  return idx;
}

int rbtree_to_array(const rbtree *t, key_t *arr, const size_t n) {
  if (t->root==t->nil){
    return 0;
  }
  rbtree_inorder(t->nil, t->root, arr,n,0);
  return 0;
}