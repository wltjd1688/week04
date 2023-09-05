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

void delete_rbtree(rbtree *t) {
  // TODO: reclaim the tree nodes's memory
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
  if (x == x->parent->left){
    x->parent->left = y;
  } else {
    x->parent->right = y;
  }
  y->left = x;
  x->parent = y;
}

// 오른쪽 로테이션
void rbtree_right_rotate(rbtree *t, node_t * x) {
  node_t* y = x->left;
  x->left = y->right;
  if (y->right != t->nil){
    y->right->parent = x;
  }
  y->parent = x->parent;
  if (x == x->parent->left){
    x->parent->left = y;
  } else {
    x->parent->right = y;
  }
  y->right = x;
  x->parent = y;
}

// 삽입 fixup
void rbtree_inserte_fixup(rbtree* t, node_t* z){
  color_t red = RBTREE_RED;
  color_t black = RBTREE_BLACK;
  while (z->parent->color==red){
    if (z->parent==z->parent->parent->left){
      node_t* y = z->parent->parent->right;
      if (y->color == red){
        z->parent->color = black;
        y->color = black;
        z->parent->parent->color = red;
        z = z->parent->parent;
      }else{
        if (z == z->parent->right){
          z = z->parent;
          rbtree_left_rotate(t,z);
        }
        z->parent->color = black;
        z->parent->parent->color = red;
        rbtree_right_rotate(t,z->parent->parent);
      }
    }
    node_t* y = z->parent->parent->left;
    if (y->color == red){
      z->parent->color = black;
      y->color = black;
      z->parent->parent->color = red;
    }else{
    if (z == z->parent->left){
      z = z->parent;
      rbtree_right_rotate(t,z);
    }
    z->parent->color = black;
    z->parent->parent->color = red;
    rbtree_left_rotate(t,z->parent->parent);
    }
  }
  t->root->color = black;
}

// 삽입
node_t* rbtree_insert(rbtree *t, const key_t key) {
  node_t* y = t->nil;
  node_t* x = t->root;
  node_t* z = (node_t*)malloc(sizeof(node_t));
  z->key = key;
  color_t red = RBTREE_RED;

  while (x != t->nil){
    y = x;
    if (z->key < x->key){
      x = x->left;
    } else {
      x = x-> right;
    }
  }
  z->parent = y;
  if (y==t->nil){
    t->root = z;
  } else if (z->key < y->key){
      y->left = z;
  } else {
    y->left = z;
  }
  z->left = t->nil;
  z->right = t->nil;
  z->color = red;
  rbtree_inserte_fixup(t,z);
  return t->root;
}

node_t* rbtree_find(const rbtree *t, const key_t key) {
  // TODO: implement find
  return t->root;
}

node_t* rbtree_min(const rbtree *t) {
  // TODO: implement find
  return t->root;
}

node_t* rbtree_max(const rbtree *t) {
  // TODO: implement find
  return t->root;
}

int rbtree_erase(rbtree *t, node_t *p) {
  // TODO: implement erase
  return 0;
}

int rbtree_to_array(const rbtree *t, key_t *arr, const size_t n) {
  // TODO: implement to_array
  return 0;
}

int main(){
  rbtree *p = (rbtree *)calloc(1, sizeof(rbtree));
  node_t new_node;

  new_node.color = RBTREE_RED;
  p -> root = &new_node;
  rbtree_insert(p,14);
}