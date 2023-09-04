#include <stdio.h>
#include <stdlib.h>

// 트리 노드 구조체
typedef struct TreeNode{
    char key;
    struct TreeNode * left;
    struct TreeNode * right;
} tree_node;

// 큐 노드 구조체 정의
typedef struct QueueNode{
    tree_node* data;
    int level;
    struct QueueNode* next;
} queue_node;

// 큐 구조체 정의
typedef struct Queue {
    queue_node* front;
    queue_node* rear;
} Queue;

// 큐 노드 만들기
Queue* creatQueue() {
    Queue* queue = (Queue*)malloc(sizeof(Queue));
    if (queue == NULL) {
        fprintf(stderr, "메모리 할당 오류\n");
        exit(1);
    }
    queue -> front = NULL;
    queue -> rear = NULL;
    return queue;
}

// 새 노드 생성
tree_node * create_node(char data) {
    tree_node* new_node = (tree_node*)malloc(sizeof(tree_node));
    if (new_node==NULL) {
        fprintf(stderr, "메모리 할당 오류\n");
        exit(1);
    }
    // 초기화 및 key갑 넣기
    new_node -> key = data;
    new_node -> left = NULL;
    new_node -> right = NULL;
    return new_node;
}

// 큐가 비었는지 확인하는 함수
int isEmpty(Queue* queue) {
    return (queue->front == NULL);
}

// 큐에 데이터를 추가하는 함수
void enqueue(Queue* queue, tree_node* item, int level) {
    queue_node* new_node = (queue_node*)malloc(sizeof(queue_node));
    if (new_node == NULL) {
        fprintf(stderr, "메모리 할당 오류\n");
        exit(1);
    }
    new_node->data = item;
    new_node->level = level;
    new_node->next = NULL;

    if(isEmpty(queue)) {
        queue -> front = new_node;
        queue->rear = new_node;
    } else {
        queue->rear->next = new_node;
        queue->rear = new_node;
    }
}

queue_node* dequeue(Queue* queue) {
    if (isEmpty(queue)) {
        fprintf(stderr, "큐가 비었음\n");
        exit(1);
    }
    queue_node* temp = queue->front;
    queue->front = temp->next;

    if (queue->front == NULL){
        queue->rear = NULL;
    }

    return temp;
}

// // 이진 트리 삽입 함수
// tree_node * insert(tree_node * root,int data){
//     tree_node* current = root;
//     if (root == NULL) {
//         return create_node(data);
//     }

//     if (data < root -> key){
//         root -> left = insert(root->left, data);
//     } else if (data > root-> key){
//         root -> right = insert(root->right, data);
//     }
//     return root;
// }

// 이진 트리 삽입 함수
tree_node * insert(tree_node * root, char data) {
    tree_node* current = root;
    tree_node* parent = NULL;

    while (current != NULL) {
        parent = current;
        if (current->key == data) {
            fprintf(stderr,"중복\n");
            return root;
        } else if (current->key < data) {
            current = current -> right;
        } else {
            current = current -> left;
        }
    }

    // 새노드 할당
    tree_node* new_node = create_node(data);

    // parent의 자식으로 새 노드 붙이기.
    if(parent != NULL) {
        if (parent->key < new_node->key){
            parent -> right = new_node;
        } else {
            parent -> left = new_node;
        }
    } else {
        root = new_node;
    }
    return root;
}

//  이진 트리 탐색 함수
tree_node * search(tree_node * root,char find) {
    tree_node* current = root;
    int count = 0;
    while (current != NULL){
        if (current->key == find) {
            fprintf(stderr,"exist: %d",count);
            return NULL;
        } else if (current->key < find) {
            current = current -> right;
        } else {
            current = current -> left;
        }
        count ++;
    }
    fprintf(stderr,"emtpy");
    return NULL;
}

// 이진 트리 삭제 함수
tree_node * delete(tree_node * root,char del) {
    tree_node* current = root;
    tree_node* parent = NULL;
    while ((current != NULL) && (current->key != del)) {
        parent = current;
        } if (current->key < del) {
            current = current -> right;
        } else {
            current = current -> left;
        }
    if (current==NULL){
        fprintf(stderr,"찾는 노드가 없음\n");
        return root;
    }    
    // root만 있는 경우
    if (current->left == NULL && current -> right == NULL) {
        if (parent == NULL){
            root = NULL;
        } else {
            if (parent -> left == current){
                parent -> left = NULL;
            } else {
                parent -> right = NULL;
            }
        }
    }
    else if (current->left==NULL || current->right == NULL){
        tree_node * child = (current->left != NULL) ? current->left: current->right;
        if (parent == NULL){
            root = child;
        }
        else {
            if (parent -> left == current){
                parent -> left == child;
            } else {
                parent -> right == child;
            }
        }
    }
    else {
        tree_node* succ_parent = current;
        tree_node* succ = current -> right;
        while (succ->left != NULL){
            succ_parent = succ;
            succ = succ->left;
        }
        current -> key = succ -> key;
        if (succ_parent -> left == succ){
            succ_parent -> left == succ->right;
        } else {
            succ_parent -> right = succ -> right;
        current = succ;
        }
    }
    free(current);
    return root;
}

// 트리의 노드개수
int tree_size(tree_node* root){
    if (root == NULL) {
        return 0;
    }
    return 1 + tree_size(root->left) + tree_size(root->right);
}

// 후위 순회
void postorder(tree_node* root) {
    if (root == NULL){
        return;
    }
    postorder(root->left);
    postorder(root->right);
    fprintf(stderr,"%c -> ",root->key);
}
// 중위 순회
void inorder(tree_node* root) {
    if (root == NULL){
        return;
    }
    inorder(root->left);
    fprintf(stderr,"%c -> ",root->key);
    inorder(root->right);
}
// 전위 순회
void preorder(tree_node* root) {
    if (root == NULL){
        return;
    }
    fprintf(stderr,"%c -> ",root->key);
    preorder(root->left);
    preorder(root->right);
}
// 레벨 순회
void levelorder(tree_node* root) {
    if (root == NULL){
        return;
    }
    Queue* queue = creatQueue();
    enqueue(queue,root,1);

    int currentLevel = 1;
    printf("Level %d: ",currentLevel);

    while(!isEmpty(queue)) {
        queue_node* node = dequeue(queue);
        tree_node* current = node->data;
        if ( node->level > currentLevel){
            printf("\nLevel %d: ", currentLevel);
            currentLevel = node->level;
        }
        
        printf("%c ", current->key);

        if (current->left != NULL) {
            enqueue(queue, current->left, node->level + 1);
        }

        if (current->right != NULL) {
            enqueue(queue, current->right, node->level + 1);
        }
    }
    printf("\n");
    free(queue);
}

int main(){
    tree_node* root = insert(NULL,'D');
    insert(root,'I');
    insert(root,'F');
    insert(root,'A');
    insert(root,'G');
    insert(root,'C');
    insert(root,'H');
    insert(root,'W');
    insert(root,'Q');
    insert(root,'E');
    insert(root,'R');
    printf("tree size: \n");
    tree_size(root); fprintf(stderr,"\n");
    printf("preorder: \n");
    preorder(root); fprintf(stderr,"\n");
    printf("inorder: \n");
    inorder(root); fprintf(stderr,"\n");
    printf("postorder: \n");
    postorder(root); fprintf(stderr,"\n");
    printf("\n");
    search(root,'H');
    printf("\n");
    printf("Level Order Traversal: \n");
    levelorder(root);
    int node_count = tree_size(root);
    printf("conunt tree node: %d\n", node_count);

    return 0;
}