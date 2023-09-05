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
  node = NULL;
  return;
}

void delete_rbtree(rbtree *t) {
  if (t==NULL){
    return;
  }
  delete_node(t->root,t);
  free(t->nil);
  t->nil = NULL;
  free(t);
  t = NULL;
  return;
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
  else if (x == x->parent->left){
    x->parent->left = y;
  } else {
    x->parent->right = y;
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
  node_t* z = (node_t*)malloc(sizeof(node_t));
  z->key = key;

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
  } else if (z->key < y->key) {
    y->left = z;
  } else {
    y->right = z;
  }
  z->left = t->nil;
  z->right = t->nil;
  z->color = RBTREE_RED;
  rbtree_inserte_fixup(t,z);
  return t->root;
}

node_t* rbtree_find(const rbtree *t, const key_t key) {
  node_t* current = t->root;
  while (current != t->nil){
    if(key == current->key){
      return current;
    }
    else if (key < current->key){
      current = current->left;
    } else{
      current = current->right;
    }
  }
  return NULL;
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

int rbtree_erase(rbtree *t, node_t *p) {
  // TODO: implement erase
  return 0;
}

int rbtree_to_array(const rbtree *t, key_t *arr, const size_t n) {
  // TODO: implement to_array
  return 0;
}