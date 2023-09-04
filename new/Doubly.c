#include <stdio.h>
#include <stdlib.h>

/*만들고자 하는 기능 - Doubly linked list
1. 인덱스의 데이터 가져오기
2. 노드 탐색하기
3. 노드 추가
4. 노드 제거*/

// 양방향 링크드리스트 노드 정의
typedef struct Node_t{
    int data;
    struct Node_t *next;
    struct Node_t *prev;
} Node_t;

//더블리스트용 head tail 생성 구조체 생성
typedef struct doublyList{
    struct Node_t *head;
    struct Node_t *tail;
}mylist;

// 노드 생성 함수
Node_t* createNode(int data){
    Node_t* new_node = (Node_t*)malloc(sizeof(Node_t));
    if (new_node==NULL){
        printf("메모리 할당 오류\n");
        exit(1);
    }
    new_node->data = data;
    new_node->prev = NULL;
    new_node->next = NULL;
    return new_node;
}

// 리스트 초기화 함수
void initialize_list(mylist* list){
    list->head = NULL;
    list->tail = NULL;
}

// 노드 추가 함수(뒤))
void append(mylist* list, int input_value){
    Node_t* new_node = createNode(input_value);
    if (list->head==NULL){
        list->head = new_node;
        list->tail = new_node;
    } else {
        new_node->prev = list -> tail;
        list -> tail ->next = new_node;
        list->tail = new_node;
    }
}

// 노드 추가 함수(앞)
void prepend(mylist* list, int input_value){
    Node_t* new_node = createNode(input_value);
    if (list->head==NULL){
        list->head = new_node;
        list->tail = new_node;
    } else {
        new_node->next = list -> head;
        list -> head -> prev = new_node;
        list->head = new_node;
    }
};

// 노드 삭제 함수
void delete_node(mylist* list, int delete_value){
    Node_t* current = list->head;
    while (current != NULL){
        if (current->data == delete_value){
            if (current->prev != NULL){
                current->prev->next = current->next;
            } else {
                list -> head = current->next;
            }
            if (current->next != NULL) {
                current->next->prev = current->prev;
            } else {
                list->tail = current->prev;
            }
            free(current);
            return;
        }
        current = current -> next;
    }
}

// 앞쪽에서 프린트
void print_foront(mylist* list){
    Node_t* current = list->head;
    while(current != NULL) {
        printf("%d <->",current->data);
        current = current->next;
    }
    printf("NUll\n");
}

// 뒤쪽에서 프린트
void print_Back(mylist* list){
    Node_t* current = list->tail;
    while(current != NULL) {
        printf("%d <->",current->data);
        current = current->prev;
    }
    printf("NUll\n");
}

// 메모리 해제 함수
void free_list(mylist* list){
    Node_t* current = list->head;
    while(current != NULL){
        Node_t * temp = current;
        current = current -> next;
        free(temp);
    }
    list -> head = NULL;
    list -> tail = NULL;
}

// 업데이트 함수
void update(mylist* list){
    Node_t* current = list->head;
    
}

int main(){
    mylist list;
    initialize_list(&list);

    for (int i=0; i < 10; i++){
        append(&list,i);
    }
    prepend(&list,100);

    printf("Foront: ");
    print_foront(&list);
    printf("\nback: ");
    print_Back(&list);
    printf("\ndelete: ");
    delete_node(&list,8);
    print_foront(&list);
    printf("\nfree: ");
    free_list(&list);
    print_foront(&list);
    return 0;
}