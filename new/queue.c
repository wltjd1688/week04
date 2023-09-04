#include <stdio.h>
#include <stdlib.h>

// 큐 노드 구조체 정의
typedef struct QueueNode{
    int data;
    struct QueueNode *next;
}queue_node;

// 큐 구조체 정의
typedef struct Queue {
    queue_node* front;
    queue_node* rear;
}Queue;

// 큐 생성 함수
queue_node* create_nueue_node(int data){
    queue_node* new_node = (queue_node*)malloc(sizeof(queue_node));
    if (new_node == NULL){
        fprintf(stderr,"메모리 할당 오류\n");
        exit(1);
    }
    new_node->data = data;
    new_node->next = NULL;
    return new_node;
}

// 큐 초기화 함수
void initializeQueue(Queue* queue) {
    queue->front = NULL;
    queue->rear = NULL;
}

// 큐 데이터 추가 함수 - enqueue
void enqueue(Queue* queue, int data){
    queue_node* new_node = create_nueue_node(data);

    if (queue->rear==NULL) {
        queue->front = new_node;
        queue->rear = new_node;
    } else {
        queue->rear->next = new_node;
        queue->rear = new_node;
    }
};

// 큐 데이터 추가 함수 - dequeue
int dequeue(Queue* queue){
    if (queue->front == NULL){
        fprintf(stderr,"큐가 비어 있습니다. \n");
        exit(1);
    }
    queue_node* temp = queue->front;
    int item = temp -> data;
    queue->front = temp->next;

    if(queue->front == NULL){
        queue->rear = NULL;
    }

    free(temp);
    return item;
}
// 큐의 front
int front(Queue* queue){
    if (queue->front==NULL){
        fprintf(stderr,"큐가 비어있습니다. \n");
        exit(1);
    }
    return queue->front->data;
}

// 큐가 비었는지 확인
int is_empty(Queue* queue){
    if (queue->front==NULL){
        return 1;
    } else {
        return 0;
    }
}

// 큐 사이즈 확인
int q_size(Queue* queue){
    int count = 0;
    queue_node* current = queue->front;
    while (current !=NULL){
        count ++;
        current = current->next;
    }
    return count;
}

// 큐 비우기
void q_clean(Queue* queue){
    if (queue->front==NULL){
        fprintf(stderr,"큐가 비어있습니다. \n");
        return;
    }
    queue_node* current = queue->front;
    while (current != NULL){
        queue_node* temp = current;
        current = current -> next;
        queue->front = current->next;
        free(temp);
    }
    queue -> front = NULL;
    queue -> rear = NULL;
}


int main() {
    Queue queue;
    initializeQueue(&queue);
    printf("is emty?: %d\n",is_empty(&queue));

    for (int i=0; i<10; i++){
        enqueue(&queue,i);
    }
    printf("queue size: %d\n",q_size(&queue));

    printf("front: %d\n", front(&queue));

    q_clean(&queue);

    return 0;
}