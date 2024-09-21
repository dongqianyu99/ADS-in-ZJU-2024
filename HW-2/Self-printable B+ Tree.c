#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct node *tree;
struct node
{
    int key_size;
    int key[3];
    bool isLeaf;
    tree left, right, middle;
};

struct node* stack[10000];  // to store the parents(the path from root to ptr)
int top = 0;

void push(struct node* NODE){
    stack[top++] = NODE;
}

struct node* pop(){
    return stack[--top];
}

tree queue[10000];
int front, rear;

void enqueue (struct node* NODE){
    front = (front + 1) % 10000;
    queue[front] = NODE;
}

tree dequeue(){
    rear = (rear + 1) % 10000;
    return queue[rear];
}

int findrightmin(struct node* NODE){
    while (NODE->isLeaf == false){
        NODE = NODE->left;
    }
    return NODE->key[0];
}

void print(tree T){
    if (T == NULL)
        return;
    struct node* ptr = NULL;
    enqueue(T);
    int curr_layer_count = 1;
    int next_layer_count = 0;
    while (front != rear){  // BFS
        ptr = dequeue();
        if (ptr->isLeaf == false){
            curr_layer_count--;
            printf("[%d", ptr->key[0]);
            enqueue(ptr->left);
            next_layer_count++;
            if (ptr->middle != NULL){
                printf(",%d]", ptr->key[1]);
                enqueue(ptr->middle);
                next_layer_count++;
            }
            else{
                printf("]");
            }
            enqueue(ptr->right);
            next_layer_count++;
            if (curr_layer_count == 0){
                printf("\n");
                curr_layer_count = next_layer_count;
                next_layer_count = 0;
            }
        }
        else{
            printf("[%d", ptr->key[0]);
            if (ptr->key[1] != -1)
                printf(",%d", ptr->key[1]);
            if (ptr->key[2] != -1)
                printf(",%d", ptr->key[2]);
            printf("]");
        }
    } 
    printf("\n");
}

void insert(int x, tree* T)
{
    if (x < 0)
        return;
    top = 0;
    // set up the root
    if (*T == NULL){
        *T = (tree)malloc(sizeof(struct node));
        (*T)->key_size = 1;
        (*T)->key[0] = x;
        (*T)->key[1] = -1;
        (*T)->key[2] = -1;
        (*T)->isLeaf = true;
        (*T)->left = NULL;
        (*T)->right = NULL;
        (*T)->middle = NULL;
        return;
    }
    struct node *ptr = *T;
    // find the leaf
    while (ptr->isLeaf != true){
        push(ptr);
        if (ptr->key_size == 1){
            if (x < ptr->key[0])
                ptr = ptr->left;
            else if (x > ptr->key[0])
                ptr = ptr->right;
            else{ 
                printf("Key %d is duplicated\n", x);
                return;
            }
        }
        else if (ptr->key_size == 2){
            if (x < ptr->key[0])
                ptr = ptr->left;
            else if (x > ptr->key[1])
                ptr = ptr->right;
            else if (x > ptr->key[0] && x < ptr->key[1])
                ptr = ptr->middle;
            else{
                printf("Key %d is duplicated\n", x);
                return;
            }
        }
    }

    // the leaf is not full
    if (ptr->key_size != 3){
        // while (i >= 0 && x <= ptr->key[i]){
        //     if (x == ptr->key[i]){
        //         printf("Key %d is duplicated\n", x);
        //         return;
        //     }
        //     ptr->key[i + 1] = ptr->key[i];
        //     i--;
        // }
        int i = 0;
        for (; i < ptr->key_size; i++){
            if (x == ptr->key[i]){
                printf("Key %d is duplicated\n", x);
                return;
            }
        }
        i = ptr->key_size - 1;
        while (i >= 0 && x < ptr->key[i])
        {
            ptr->key[i + 1] = ptr->key[i];
            i--;
        }
        ptr->key[i + 1] = x;
        ptr->key_size++;
        return;
    }
    else{ // the leaf is full ==> split the node
        int i = 0;
        for (; i < ptr->key_size; i++){
            if (x == ptr->key[i]){
                printf("Key %d is duplicated\n", x);
                return;
            }
        }
        int val[4];
        int j = 2;
        while (j >= 0 && ptr->key[j] > x) 
            val[j + 1] = ptr->key[j], j--;
        val[j + 1] = x;
        while (j >= 0) 
            val[j] = ptr->key[j], j--;

        struct node* node1 = (struct node*)malloc(sizeof(struct node));
        struct node* node2 = (struct node*)malloc(sizeof(struct node));

        node1->isLeaf = true;
        node1->key[0] = val[0];
        node1->key[1] = val[1];
        node1->key[2] = -1;
        node1->key_size = 2;
        node1->left = NULL;
        node1->right = NULL;
        node1->middle = NULL;

        node2->isLeaf = true;
        node2->key[0] = val[2];
        node2->key[1] = val[3];
        node2->key[2] = -1;
        node2->key_size = 2;
        node2->left = NULL;
        node2->right = NULL;
        node2->middle = NULL;

        // adjustment
        struct node* parent = NULL;
        struct node* tmp = ptr;
        while (tmp != NULL){
            if (top == 0)
                parent = NULL;
            else 
                parent = pop();
            // 1. ptr is root
            if (parent == NULL){
                struct node* root = (struct node*)malloc(sizeof(struct node));
                root->isLeaf = false;
                root->key[0] = findrightmin(node2);
                root->key[1] = -1;
                root->key[2] = -1;
                root->key_size = 1;
                root->left = node1;
                root->right = node2;
                root->middle = NULL;
                *T = root;
                break;
            }
            else if (parent->key_size == 1){ // 2. the parent is not full
                if (x < parent->key[0]){
                    parent->key[1] = parent->key[0];
                    parent->key[0] = findrightmin(node2);
                    parent->key_size = 2;
                    parent->left = node1;
                    parent->middle = node2;
                    break;
                }
                else{
                    parent->key[1] = findrightmin(node2);
                    parent->key_size = 2;
                    parent->middle = node1;
                    parent->right = node2;
                    break;
                }
            }
            else if (parent->key_size == 2){ // 3. the parent is full ==> split the parent
                struct node* parent_node1 = (struct node*)malloc(sizeof(struct node));
                struct node* parent_node2 = (struct node*)malloc(sizeof(struct node));
                parent_node1->isLeaf = false;
                parent_node2->isLeaf = false;
                parent_node1->key[1] = -1;
                parent_node1->key[2] = -1;
                parent_node2->key[1] = -1;
                parent_node2->key[2] = -1;
                if (x < parent->key[0]){ // node1, node2, middle, right
                    parent_node1->left = node1;
                    parent_node1->middle = NULL;
                    parent_node1->right = node2;
                    parent_node1->key[0] = findrightmin(node2);
                    parent_node1->key_size = 1;

                    parent_node2->left = parent->middle;
                    parent_node2->middle = NULL;
                    parent_node2->right = parent->right;
                    parent_node2->key[0] = findrightmin(parent->right);
                    parent_node2->key_size = 1;
                }
                else if (x > parent->key[0] && x < parent->key[1]){ // left, node1, node2, right 
                    parent_node1->left = parent->left;
                    parent_node1->middle = NULL;
                    parent_node1->right = node1;
                    parent_node1->key[0] = findrightmin(node1);
                    parent_node1->key_size = 1;

                    parent_node2->left = node2;
                    parent_node2->middle = NULL;
                    parent_node2->right = parent->right;
                    parent_node2->key[0] = findrightmin(parent->right);
                    parent_node2->key_size = 1;
                }
                else if (x > parent->key[1]){ // left, middle, node1, node2
                    parent_node1->left = parent->left;
                    parent_node1->middle = NULL;
                    parent_node1->right = parent->middle;
                    parent_node1->key[0] = findrightmin(parent->middle);
                    parent_node1->key_size = 1;

                    parent_node2->left = node1;
                    parent_node2->middle = NULL;
                    parent_node2->right = node2;
                    parent_node2->key[0] = findrightmin(node2);
                    parent_node2->key_size = 1;
                }

                node1 = parent_node1;
                node2 = parent_node2;
                tmp = parent;
            }
        }
    }

    return;
}


int main()
{
    int n, x;
    front = 0;
    rear = 0;
    scanf("%d", &n);
    tree TREE=NULL;
    tree *T = &TREE;
    for (int i = 1; i <= n; i++){
        scanf("%d", &x);
        insert(x, T);
    }
    print(TREE);
    return 0;
}