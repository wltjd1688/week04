#include <stdio.h>
#include <stdlib.h>

// 리스트 구조체
typedef struct Node_t{
    int data;
    struct Node_t *next;
}Node_t;

// 프린트
void linkPrint(Node_t **head){
        Node_t *cur = *head;
        while (cur!=NULL){
            printf("%d\n",cur->data);
            cur = cur -> next;
        }
        printf("NULL\n");
};

// 찾기
int find(Node_t **head, int F){
        Node_t *cur = *head;
        while (cur!=NULL){
            if (cur->data==F){
                return 1;
            }
            cur = cur -> next;
        }
        return 0;
};

//메모리 해제 함수
void free_link(Node_t **head){
    Node_t* current = *head;
    while(current != NULL){
        Node_t* temp = current;
        current = current -> next;
        free(temp);
    }
    *head = NULL;
};

//과제 : 업데이트
int update(Node_t **head, int F, int H){
        Node_t *cur = *head;

        while (cur!=NULL){
            if (cur->data==F){
                cur ->data = H;
                return 1;
            }
            cur = cur -> next;
        }
        return 0;
};

// 삭제
int delete(Node_t **head, int D){
        Node_t *cur = *head;
        Node_t *pre;
        // 예외케이스
        // 1. 노드가 비어있을때
        if (*head==NULL){
            printf("비어있음\n");
            return 0;
        } 
        // 2. 맨 처음꺼(head)가 D일 때
        if (cur->data==D){
            *head = cur->next;
            free(cur);                                        // 메모리 반환(체크아웃): 메모리 누수방지
            return 1;
        }
        // 3. 그 외
        while (cur!=NULL){
            if (cur->data==D){
                pre->next = cur->next;
                free(cur);        
                return 1;
            }
            pre = cur;
            cur = cur -> next;
        }
        return 0;
};

//넣기
void insert(Node_t **head, int N){
    Node_t *new_node = (Node_t*)malloc(sizeof(Node_t));
    new_node -> next = NULL;                                    //현재 노드 다음 노드를 null로 만들어 준다.
    new_node->data = N;

    //2가지 고려해야할것
    //1. head가 null인경우에는 그대로 넣기
    if (*head==NULL){
        *head= new_node;
        return;
    }else{
    //2. head가 null이 아닌경우에는 노드를 타고들어가서 null노드를 발견하면 넣는다.
        Node_t *cur = *head;                                    //  커서로 시작지점을 알려줌
        while (cur->next!=NULL){                                //  커서가 null을 가리킬때 멈추도록 만든다.
            cur = cur -> next;                                  //  커서를 next로 이동
        }
        cur -> next = new_node;
        return;
    }
};

int main(){
    Node_t * head = NULL;
    // Node_t * new_node = (Node_t*)malloc(sizeof(Node_t));
    // new_node->data = 10;
    // printf("%d\n",new_node->data);
    // head = new_node;
    // printf("%d\n",head->data);
    // printf("%d\n",head->data);
    // Node_t *second = head->next;
    for (int i=0;i<10;++i){
        insert(&head,i);
    }
    // linkPrint(&head);
    // if (find(&head,10)){
    //     printf("찾음\n");
    // }else{
    //     printf("못찾음\n");
    // };
    // if (update(&head,10,119)){
    //     printf("바꿈\n");
    // }else{
    //     printf("못바꿈\n");
    // };
    linkPrint(&head);
    delete(&head,1);
    printf("--------\n");
    linkPrint(&head);
    free_link(&head);
    linkPrint(&head);
    delete(&head,2);
    printf("--------\n");
    linkPrint(&head);

};

// #include <stdio.h>
// #include <stdlib.h>

// typedef struct Node_t{
//     int data;
//     struct Node_t *next;
// }Node_t;
// // 프린트
// void linkPrint(Node_t *head){
//         Node_t *cur = head->next;
//         while (cur!=NULL){
//             printf("%d\n",cur->data);
//             cur = cur -> next;
//         }
// };
// // 찾기
// int find(Node_t *head, int F){
//         Node_t *cur = head;
//         while (cur!=NULL){
//             if (cur->data==F){
//                 return 1;
//             }
//             cur = cur -> next;
//         }
//         return 0;
// };

// //과제 : 업데이트
// int update(Node_t *head, int F, int H){
//         Node_t *cur = head;

//         while (cur!=NULL){
//             if (cur->data==F){
//                 cur ->data = H;
//                 return 1;
//             }
//             cur = cur -> next;
//         }
//         return 0;
// };

// // 삭제
// int delete(Node_t *head, int D){
//         Node_t *cur = head;
//         Node_t *pre;
//         // 예외케이스
//         // 1. 노드가 비어있을때
//         if (head==NULL){
//             printf("비어있음\n");
//             return 0;
//         } 
//         // 2. 맨 처음꺼(head)가 D일 때
//         if (cur->data==D){
//             head = cur->next;
//             free(cur);                                        // 메모리 반환(체크아웃): 메모리 누수방지
//             return 1;
//         }
//         // 3. 그 외
//         while (cur!=NULL){
//             if (cur->data==D){
//                 pre->next = cur->next;
//                 free(cur);        
//                 return 1;
//             }
//             pre = cur;
//             cur = cur -> next;
//         }
//         return 0;
// };

// //넣기
// void insert(Node_t *head, int N){
//     Node_t *new_node = malloc(sizeof(Node_t));
//     new_node -> next = NULL;                                    //현재 노드 다음 노드를 null로 만들어 준다.
//     new_node->data = N;

//     //2가지 고려해야할것
//     //1. head가 null인경우에는 그대로 넣기
//     if (head==NULL){
//         head= new_node;
//         return;
//     }else{
//     //2. head가 null이 아닌경우에는 노드를 타고들어가서 null노드를 발견하면 넣는다.
//         Node_t *cur = head;                                    //  커서로 시작지점을 알려줌
//         while (cur->next!=NULL){                                //  커서가 null을 가리킬때 멈추도록 만든다.
//             cur = cur -> next;                                  //  커서를 next로 이동
//         }
//         cur -> next = new_node;
//         return;
//     }
// }

// int main(){
//     Node_t * head = malloc(sizeof(Node_t));
//     // Node_t * head = (Node_t*)malloc(sizeof(Node_t));
//     // new_node->data = 10;
//     // printf("%d\n",new_node->data);
//     // head = new_node;
//     // printf("%d\n",head->data);
//     // printf("%d\n",head->data);
//     // Node_t *second = head->next;
//     printf("%d\n",head);
    
    
//     for(int i =0; i<10; i++){
//         insert(head, i);
//     }
//     // linkPrint(&head);
//     // if (find(&head,10)){
//     //     printf("찾음\n");
//     // }else{
//     //     printf("못찾음\n");
//     // };
//     // if (update(&head,10,119)){
//     //     printf("바꿈\n");
//     // }else{
//     //     printf("못바꿈\n");
//     // };
//     linkPrint(head);
//     delete(head,1);
//     printf("--------\n");
//     linkPrint(head);

// }