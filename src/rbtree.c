#include "rbtree.h"

#include <stdlib.h>

rbtree *new_rbtree(void) {
  rbtree *t = (rbtree *)calloc(1, sizeof(rbtree));
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
//작은값 찾기
node_t* rbtree_min(const rbtree *t) {
  node_t* current = t->root;
  while(current->left != t->nil){
      current = current->left;
  }
  return current;
}
// 큰값 찾기
node_t* rbtree_max(const rbtree *t) {
  node_t* current = t->root;
  while(current->right != t->nil){
      current = current->right;
  }
  return current;
}

// u자리에 v를 넣는다.
void rbtree_transplant(rbtree* t,node_t* u,node_t* v){
  // u가 root일때 u대신 v를 root로 바꾼다.
  if (u->parent == t->nil){
    t->root = v;
  // 
  } else if(u==u->parent->left){
    u->parent->left = v;
  } else {
    u -> parent -> right = v;
  }
  v->parent = u->parent;
  return ;
}

// 삭제후 조건 맞추기
void rbtree_erase_fixup(rbtree* t, node_t* x){
  node_t* w; // 형제노드
  while(x!= t->root && x->color == RBTREE_BLACK){
    if (x==x->parent->left){
      w = x->parent->right;
      // case 1 - 형제가 red일때: black로 만들어주면 case 2,3,4중 하나에서 해졀해줌
      if(w->color==RBTREE_RED){
        w->color = RBTREE_BLACK;
        x->parent->color = RBTREE_RED;
        rbtree_left_rotate(t,x->parent);
        // 로테이션해서 x 가 바꼈으니까?
        w = x->parent->right;
      }//
      //case 2 - 형제의 자식들이 black일때: 루트노드면 black으로 해결, 아니면 case중 다른 무언가가 해결해줄거임
      if(w->left->color == RBTREE_BLACK && w->right->color == RBTREE_BLACK){
        w->color = RBTREE_RED;
        x= x->parent;
      //
      }else{
        //case 3 - 형제의 오른쪽 자식이 black일때: red로 변경하고 case4를 적용
        if(w->right->color==RBTREE_BLACK){
          w->left->color = RBTREE_BLACK;
          w->color = RBTREE_RED;
          rbtree_right_rotate(t,w);
          w = x->parent->right;
        }//case 4 - 형제 노드의 왼쪽 자식이 red일때: 그냥 회전시키기, 나중에 case3에서 잡아줄거임
        w->color = x->parent->color;
        x->parent->color = RBTREE_BLACK;
        w->right->color = RBTREE_BLACK;
        rbtree_left_rotate(t,x->parent);
        x = t->root;
      }//
    } else {
      w = x->parent->left;
      // case 1
      if(w->color==RBTREE_RED){
        w->color = RBTREE_BLACK;
        x->parent->color = RBTREE_RED;
        rbtree_right_rotate(t,x->parent);
        w = x->parent->left;
      }//
      // case 2
      if(w->right->color == RBTREE_BLACK && w->left->color==RBTREE_BLACK){
        w->color = RBTREE_RED;
        x = x->parent;
      //
      } else {
        // case 3
        if(w->left->color == RBTREE_BLACK){
          w->right->color = RBTREE_BLACK;
          w->color = RBTREE_RED;
          rbtree_left_rotate(t,w);
          w = x->parent->left;
        } // case 4
        w->color = x->parent->color;
        x->parent->color = RBTREE_BLACK;
        w->left->color = RBTREE_BLACK;
        rbtree_right_rotate(t,x->parent);
        x = t->root;
      }//
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

// 삭제
int rbtree_erase(rbtree *t, node_t *z) {
  node_t* x;
  node_t* y = z;
  color_t y_original_color = y->color;
  // z 왼쪽에 아무것도 없으면 x를 오른쪽으로 설정하고 x를 z의 부모랑 붙인다.
  if (z->left == t->nil){
    x = z->right;
    rbtree_transplant(t,z,z->right);
    // z 오른쪽에 아무것도 없으면 x를 왼쪽으로 설정하고 x를 z의 부모랑 붙인다.
  } else if (z->right == t->nil) {
    x = z->left;
    rbtree_transplant(t,z,z->left);
    // z밑에 둘다 있을 때
  } else {
    // z의 오른쪽에서 제일 작은걸 찾고 y로 설정한다.
    y = search_min(t,z->right);
    // 이때 y에 대한 색깔을 저장해둬야하는데 이는 삭제시에 확인할때 쓰인다.
    y_original_color = y->color;
    // x를 y의 왼쪽으로 설정한다.
    x = y->right;
    // 
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

// 중위순회
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

// 노드연결 확인용
int rbtree_to_array(const rbtree *t, key_t *arr, const size_t n) {
  if (t->root==t->nil){
    return 0;
  }
  
  rbtree_inorder(t->nil, t->root, arr,n,0);
  return 0;
}