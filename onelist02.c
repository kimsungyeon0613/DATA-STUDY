#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int id;
    struct Node* prev;
    struct Node* next;
} Node;

Node* head = NULL;         // 이중 연결 리스트의 헤드
Node* stack_top = NULL;    // 스택의 탑

// 노드 생성 함수
Node* create_node(int id) {
    Node* new_node = (Node*)malloc(sizeof(Node));
    new_node->id = id;
    new_node->prev = NULL;
    new_node->next = NULL;
    return new_node;
}

// 리스트 끝에 노드 삽입
void append(int id) {
    Node* new_node = create_node(id);
    if (head == NULL) {
        head = new_node;
        return;
    }

    Node* temp = head;
    while (temp->next != NULL)
        temp = temp->next;

    temp->next = new_node;
    new_node->prev = temp;
}

// 리스트 출력
void print_list(Node* start) {
    Node* temp = start;
    while (temp != NULL) {
        printf("ID: %d\n", temp->id);
        temp = temp->next;
    }
}

// 특정 ID 뒤에 노드 삽입
void insert_after(int target_id, int new_id) {
    Node* temp = head;
    while (temp != NULL && temp->id != target_id)
        temp = temp->next;

    if (temp == NULL)
        return;

    Node* new_node = create_node(new_id);
    new_node->next = temp->next;
    new_node->prev = temp;

    if (temp->next != NULL)
        temp->next->prev = new_node;

    temp->next = new_node;
}

// 특정 ID 노드 삭제
void delete_node(int target_id) {
    Node* temp = head;

    while (temp != NULL && temp->id != target_id)
        temp = temp->next;

    if (temp == NULL)
        return;

    if (temp->prev != NULL)
        temp->prev->next = temp->next;
    else
        head = temp->next;

    if (temp->next != NULL)
        temp->next->prev = temp->prev;

    free(temp);
}

// 스택에 노드 푸시 (스택은 단일 연결 리스트처럼 사용)
void push_stack(int id) {
    Node* new_node = create_node(id);
    new_node->next = stack_top;
    stack_top = new_node;
}

// 스택에서 팝하고 ID 출력
void pop_stack_all() {
    printf("\n4. 스택에서 ID를 꺼낸 순서 (LIFO):\n");
    while (stack_top != NULL) {
        printf("Pop ID: %d\n", stack_top->id);
        Node* temp = stack_top;
        stack_top = stack_top->next;
        free(temp);
    }
}

int main() {
    // 리스트 초기화
    for (int i = 10; i <= 100; i += 10)
        append(i);

    printf("1. 초기 노드 출력:\n");
    print_list(head);

    printf("\n2. ID가 35인 노드를 30과 40 사이에 삽입 후:\n");
    insert_after(30, 35);
    print_list(head);

    printf("\n3. ID가 50인 노드 삭제 후:\n");
    delete_node(50);
    print_list(head);

    // 스택에 ID 10, 20, 30 push
    push_stack(10);
    push_stack(20);
    push_stack(30);

    // 스택에서 pop 하며 출력
    pop_stack_all();

    return 0;
}