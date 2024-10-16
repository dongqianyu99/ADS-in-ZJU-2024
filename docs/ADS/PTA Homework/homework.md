# PTA Homework of ZJU Advanced Data Structure and Algorithm

Reference:
[Jianjun Zhou's Notebook](https://zhoutimemachine.github.io/note/courses/ads-hw-review/)

## HW-1

1. If the depth of an AVL tree is 6 (the depth of an empty tree is defined to be -1), then the minimum possible number of nodes in this tree is:  
A. 13  
B. 17  
C. 20  
==D. 33==  
**n~h~ = h~h-1~ + h~h-2~ + 1**
![alt text](image.png)
<br/>
2. For the result of accessing the keys 3, 9, 1, 5 in order in the splay tree in the following figure, which one of the following statements is FALSE?  
![alt text](128.jpg)  
A. 5 is the root  
B. 1 and 9 are siblings  
C. 6 and 10 are siblings  
<mark>D. 3 is the parent of 4</mark>  
<br/>
3. When doing amortized analysis, which one of the following statements is FALSE?  
A.Aggregate analysis shows that for all n, a sequence of nn operations takes worst-case time T(n) in total.  Then the amortized cost per operation is therefore T(n)/n  
<mark>B. For potential method, a good potential function should always assume its ~~maximum~~（minimum） at the start of the sequence</mark>  
C. For accounting method, when an operation's amortized cost exceeds its actual cost, we save the difference as credit to pay for later operations whose amortized cost is less than their actual cost  
D. The difference between aggregate analysis and accounting method is that the later one assumes that the amortized costs of the operations may differ from each other  
<br/>
4. (**Wrong**)Insert 2, 1, 4, 5, 9, 3, 6, 7 into an initially empty AVL tree.  Which one of the following statements is FALSE?  
A. 4 is the root  
==B. 3 and 7 are siblings==  
C. 2 and 6 are siblings  
D. 9 is the parent of 7  

![alt text](image-1.png)    
[AVL Tree Visulization](https://www.cs.usfca.edu/~galles/visualization/AVLtree.html)  
<br/>
5. (**Wrong**)Consider the following buffer management problem. Initially the buffer size (the number of blocks) is one. Each block can accommodate exactly one item. As soon as a new item arrives, check if there is an available block. If yes, put the item into the block, induced a cost of one. Otherwise, the buffer size is doubled, and then the item is able to put into. Moreover, the old items have to  be moved into the new buffer so it costs k+1 to make this insertion, where k is the number of old items. Clearly, if there are N items, the worst-case cost for one insertion can be $\Omega (N)$.  To show that the average cost is O(1), let us turn to the amortized analysis. To simplify the problem, assume that the buffer is full after all the N items are placed. Which of the following potential functions works?  
A. The number of items currently in the buffer  
B. The opposite number of items currently in the buffer  
C. The number of available blocks currently in the buffer  
==D. The opposite number of available blocks in the buffer==  

>When given the potential function, we need to calculate $\Delta$$\phi$ and add it to c~i~, which equals to c~i~_hat. The potentail function is working when in every situation the c~i~_hat equals to the target average cost.  
>
>![alt text](image-2.png)

<br/>

### Root of AVL Tree  
```c
# include <stdio.h>
# include <stdlib.h>

struct node;
typedef struct node* pos;
typedef struct node* tree;
pos LLROTATION( pos );
pos LRROTATION( pos );
pos RRROTATION( pos );
pos RLROTATION( pos );

int max( int a, int b )
{
    return ( a > b ) ? a : b;
}

struct node
{
    int element;
    tree left;
    tree right;
    int height;
};

int height( pos p )
{
    if ( p == NULL )
        return -1;
    else 
        return p->height; 
};

struct node* insert( int x, tree t )
{
    if ( t == NULL ){  // End of recursion
        t = ( struct node* )malloc( sizeof( struct node ) );  
        t->element = x;
        t->height = 0;
        t->left = NULL, t->right = NULL;
    }
    else if ( x < t->element ){  // Decide the type of rotation
        t->left = insert( x, t->left );
        if( height( t->left ) - height( t->right ) == 2 ){
            if( x < t->left->element )
                t = LLROTATION( t );
            else
                t = LRROTATION( t );
        }
    }
    else if ( x > t->element ){
        t->right = insert( x, t->right );
        if( height( t->right ) - height( t->left ) == 2 ){
            if( x > t->right->element )
                t = RRROTATION( t );
            else
                t = RLROTATION( t );
        }
    }

    t->height = max( height( t->left ), height( t->right ) ) + 1;  // "+1"
    return t;
};

pos LLROTATION( pos grandfather)
{
    pos father = grandfather->left;
    grandfather->left = father->right;
    father->right = grandfather;

    grandfather->height = max( height( grandfather->left ), height( grandfather->right ) ) + 1;
    father->height = max( height( father->left ), height( father->right ) ) + 1;

    return father;
}

pos LRROTATION( pos grandfather)
{
    pos father = grandfather->left;
    grandfather->left = RRROTATION( father );
    return LLROTATION( grandfather );
}

pos RRROTATION( pos grandfather )
{
    pos father = grandfather->right;
    grandfather->right = father->left;
    father->left = grandfather;

    grandfather->height = max( height( grandfather->left ), height( grandfather->right ) ) + 1;
    father->height = max( height( father->left ), height( father->right ) ) + 1;

    return father;
}

pos RLROTATION( pos grandfather )
{
    pos father = grandfather->right;
    grandfather->right = LLROTATION( father );
    return RRROTATION( grandfather );
}

int main()
{
    int n;
    scanf("%d", &n);

    int x;
    tree root = NULL;
    for( int i = 1; i <= n; i++){
        scanf("%d", &x);
        root = insert(x, root);
    }

    printf("%d", root->element);

    return 0;
}
```
<br/>

## EX-1

1. Amortized bounds are weaker than the corresponding worst-case bounds, because there is no guarantee for any single operation.  
==A. T==  
B. F  
<br/>
2. Suppose we have a potential function $\phi$ such that for all $\phi$(Di)$\geq$$\phi$(D0) for all ii, but $\phi$(D0)$\neq$0. Then there exists a potential $\phi$′ such that $\phi$′(D0)=0, $\phi$′(Di)$\geq$0 for all i$\geq$1, and the amortized costs using $\phi$′ are the same as the amortized costs using $\phi$.  
==A. T==  
B. F
<br/>
3. For the result of accessing the keys 1 and 2 in order in the splay tree in the following figure, let's define size(v)=number of nodes in subtree of v ( vv included ) and potential $\phi$=$\sum$v[log~⁡2~size(v)], where [x] means the greatest interger no larger than x.  
How many of the following statements is/are TRUE?  
a. the potential change from the initial tree to the resulted tree is -4 ==(-5?)==  
b. ==1 is the sibling of 4==  
c. ==5 is the child of 6==  
![alt text](071d7a8c-c028-4160-a47c-398cf901bc96.png)
<br/>
4. (**WRONG**)Insert { 9, 8, 7, 2, 3, 5, 6, 4 } one by one into an initially empty AVL tree. How many of the following statements is/are FALSE?  
   - the total number of rotations made is 5 (Note: double rotation counts 2 and single rotation counts 1)  
   - ==the expectation (round to 0.01) of access time is 2.75==  
   - there are 2 nodes with a balance factor of -1  
<br/>
5. (**WRONG**)Which one of the following statements is FALSE?  
A. For red-black trees, the total cost of rebalancing for m consecutive insertions in a tree of n nodes is O(n+m).  
==B. To obtain O(1) armortized time for the function decrease-key, the potential function used for Fibonacci heaps is Φ(H)=t(H)+m(H), where t(H) is the number of trees in the root list of heap H, and m(H) is the number of marked nodes in H.(?)==  
C. Let S(x) be the number of descendants of x (x included). If the potential function used for splay tree is Φ(T)=∑~x∈T~log⁡S(x), then the amortized cost of one splay operation is O(log⁡n).  
D. In the potential method, the amortized cost of an operation is equal to the actual cost plus the increase in potential due to this operation.  

## HW-2  

1. In the red-black tree that results after successively inserting the keys 41; 38; 31; 12; 19; 8 into an initially empty red-black tree, which one of the following statements is FALSE?  
A. 38 is the root  
==B. 19 and 41 are siblings, and they are both red(41 is black)==  
C. 12 and 31 are siblings, and they are both black  
D. 8 is red  
![alt text](image-3.png)
[Red/Black Tree Visulization](https://www.cs.usfca.edu/~galles/visualization/RedBlack.html)
<br/>
2. After deleting 15 from the red-black tree given in the figure, which one of the following statements **must be**(two way of deletion) FALSE?  
![alt text](129.jpg)  
A. 11 is the parent of 17, and 11 is black  
B. 17 is the parent of 11, and 11 is red  
==C. 11 is the parent of 17, and 11 is red==  
D. 17 is the parent of 11, and 17 is black  
<br/>
3. Insert 3, 1, 4, 5, 9, 2, 6, 8, 7, 0 into an initially empty 2-3 tree (with splitting).  Which one of the following statements is FALSE?  
==A. 7 and 8 are in the same node==  
B. the parent of the node containing 5 has 3 children  
C. the first key stored in the root is 6  
D. there are 5 leaf nodes  
![alt text](image-4.png)
<br/>
4. After deleting 9 from the 2-3 tree given in the figure, which one of the following statements is FALSE?  
![alt text](130.jpg)  
A. the root is full  
B. the second key stored in the root is 6  
C. 6 and 8 are in the same node  
==D. 6 and 5 are in the same node==  
<br/>
5. Which of the following statements concerning a B+ tree of order M is TRUE?  
A. the root always has between 2 and M children  
B. not all leaves are at the same depth  
==C. leaves and nonleaf nodes have some key values in common==  
D. all nonleaf nodes have between $\lceil{M/2}\rceil$ and M children  

### Self-printable B+ Tree
```c
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
```

## EX-2

1. (**WRONG**)If we insert N(N⩾2) nodes (with different integer elements) consecutively to build a red-black tree T from an empty tree, which of the following situations is possible:  
A. All nodes in T are black  
B. The number of leaf nodes (NIL) in T is 2N−1  
C. 2N rotations occurred during the construction of T  
D. The height of T is ⌈3log⁡2(N+1)⌉ (assume the height of the empty tree is 0)  


## HW-3

1. When evaluating the performance of data **retrieval**, it is important to measure the **relevancy** of the answer set.  
A. T  
==B. F==  
<br/>
2. While accessing a term by hashing in an inverted file index, range searches are expensive.  
==A. T==  
B. F  
<br/>

### Document Distance

Score: 6/10

```cpp
#include <cstdio>
#include <iostream>
#include <string>
#include <cmath>
#include <map>
#include <set>
#include <vector>

using namespace std;

const int MAXN = 100;

int N, M, vocabSize;
string title;

vector <int> freq[MAXN];
set <string> dict;
map <string, int> count[MAXN];
map <string, int> titleList;

double docDis(int m, int n)
{
    int sum = 0;
    for (int i = 1; i <= vocabSize; i++)
        sum += freq[m][i] * freq[n][i];

    int length_m = 0;
    for (int i = 1; i <= vocabSize; i++)
        length_m += freq[m][i] * freq[m][i];
    int length_n = 0;
    for (int i = 1; i <= vocabSize; i++)
        length_n += freq[n][i] * freq[n][i];
    
    return acos(sum * 1.0 / (sqrt(length_m) * sqrt(length_n) * 1.0));
}

string stemmer(string str){
    if (str.size() > 7 && str.substr(str.size() - 7) == "ational") {
        return(str.substr(0, str.size() - 7) + "ate");
    }
    if (str.size() > 6 && str.substr(str.size() - 6) == "tional") {
        return(str.substr(0, str.size() - 6) + "tion");
    }
    if (str.size() > 4 && str.substr(str.size() - 4) == "enci") {
        return(str.substr(0, str.size() - 4) + "ence");
    }

    ...

    if (str.size() > 2 && str.substr(str.size() - 2) == "al") {
        return(str.substr(0, str.size() - 2) + "");
    }

    return str;
}

void tokenizer(int ID){
    char ch;
    string token;
    do{
        scanf("%c", &ch);
        if (isalpha(ch))
            token += tolower(ch);
        else{
            token = stemmer(token);
            dict.insert(token);
            count[ID][token]++;
            token = "";
        }
    } while (ch != '#');
}

void setfreq(){
    for (int i = 1; i <= N; i++){
        freq[i].resize(vocabSize);
        int j = 0;
        for (auto word = dict.begin(); word != dict.end(); word++)
            freq[i][j++] = count[i][*word];
    }
}

int main()
{
    scanf("%d", &N);
    for (int ID = 1; ID <= N; ID++){
        cin >> title;
        titleList[title] = ID;
        tokenizer(ID);
    }
    vocabSize = dict.size();
    setfreq();

    string title1, title2;
    scanf("%d", &M);
    for (int i = 1; i <= M; i++){
        cin >> title1 >> title2;
        printf("Case %d: %.3f\n", i, docDis(titleList[title1], titleList[title2]));
    }
}
```

## HW-4  
1. **(HARD)** We can perform BuildHeap for leftist heaps by considering each element as a one-node leftist heap, placing all these heaps on a queue, and performing the following step: Until only one heap is on the queue, dequeue two heaps, merge them, and enqueue the result.  Which one of the following statements is FALSE?
A. in the $k^{th}$ run, $\lceil N/2^k \rceil$ leftist heaps are formed, each contains $2^k$ nodes
B. the worst case is when $N=2^K$ for some integer $K$
C. the time complexity $T(N) = O(\frac{N}{2}log 2^0 + \frac{N}{2^2}log 2^1 + \frac{N}{2^3}log 2^2 + \cdots + \frac{N}{2^K}log 2^{K-1})$ for some integer $K$ so that $N=2^K$
==D. the worst case time complexity of this algorithm is $\Theta (NlogN)$==  

>From C, $T(N)=O(N)$
**$T(N)=2T(N/2)+O(logN)$** to get C  

### The function is to merge two leftist heaps H1 and H2.
```c
PriorityQueue Merge( PriorityQueue H1, PriorityQueue H2 )
{ 
    if (H1==NULL) return H2;
    if (H2==NULL) return H1;
    if [(H1->Element > H2->Element)]
        swap(H1, H2);  //swap H1 and H2
    if ( H1->Left == NULL )
        [SwapChildren(H1)];                   ;
    else {
        H1->Right = Merge( H1->Right, H2 );
        if ( H1->Left->Npl < H1->Right->Npl )
        SwapChildren( H1 );  //swap the left child and right child of H1
    [H1->Npl = H1->Right->Npl + 1];
    }
    return H1;
}
```

## HW-5  
1. Merge the two binomial queues in the following figure.  Which one of the following statements must be FALSE?  
A. there are two binomial trees after merging, which are B2B_2 and B4B_4  
B. 13 and 15 are the children of 4  
C. if 23 is a child of 2, then 12 must be another child of 2  
==D. if 4 is a child of 2, then 23 must be another child of 2==  
![alt text](132.jpg)  
<br/>
### The functions `BinQueue_Find` and `Recur_Find` are to find X in a binomial queue H.  Return the node pointer if found, otherwise return NULL.  

```c
BinTree BinQueue_Find( BinQueue H, ElementType X )
{
    BinTree T, result = NULL;
    int i, j; 

    for( i=0, j=1; j<=H->CurrentSize; i++, j*=2) {  /* for each tree in H */
        T= H->TheTrees[i];
        if ( X [>= T->Element] ){  /* if need to search inside this tree */
            result = Recur_Find(T, X);
            if ( result != NULL ) return result;
        } 
    }
    return result;
}

BinTree Recur_Find( BinTree T, ElementType X )
{
    BinTree result = NULL;
    if ( X==T->Element ) return T;
    if ( T->LeftChild!=NULL ){
        result = Recur_Find(T->LeftChild, X);
        if ( result!=NULL ) return result;
    } 
    if ( [T->NextSibling!=NULL] )
        result = Recur_Find(T->NextSibling, X);
    return result;
}
```

## HW-6  

1. Given the following game tree, which node is the first one to be pruned with α-β pruning algorithm?  
![alt text](aa3cd703-e174-4e1c-9b3d-3cd7864c3cf1.png)  
A. a  
B. b  
==C. c== (Just follw the steps on oi-wiki)  
D. d