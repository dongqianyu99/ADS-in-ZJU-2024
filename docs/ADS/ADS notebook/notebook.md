# ADS

## Chapter 1: AVL Tree & Splay Tree & Amortized Analysis

### AVL Trees 

#### Defination

>The height of an empty tree is defined to be **-1**  

>An empty binary tree is height balanced.   
>If T is a nonempty binary tree with T~L~ and T~R~ as its left and right subtrees, then T is height balanced if  
>1. T~L~ and T~R~ are height balanced  
>2. **|h~L~ - h~R~| <= 1**  
>  
>The **balance factor** **BF(node)** = h~L~ - h~R~; In an AVL tree, BF(node) = -1, 0 or 1

#### Implementation

- Single Rotation  
  - LL Rotation  
  ![alt text](image-14.png)
  - RR Rotation  
  ![alt text](image-13.png)
- Double Rotation  
  - LR Rotation  
  ![alt text](image-15.png)
  - RL Rotation  
  ![alt text](image-16.png)

>**Trouble finder**: The lowest unbalanced node  

#### Time Complexity

T = O(h)  
Let n~h~ be the minimum number of nodes in a height balanced tree of height h. Then the tree must look like:  

![alt text](image-17.png)

*Fibonacci* number theory gives that:   

![alt text](image-18.png)

#### Coding

##### Structure Define
```c
struct AvlNode
{
    ElementType Element;
    AvlTree  Left;
    AvlTree  Right;
    int      Height;
};
```
##### Height
```c
static int
Height( Position P )
{
    if( P == NULL )
        return -1;
    else
        return P->Height;
}
```

##### Single Rotation With Left(LL Rotation)
```c
static Position
SingleRotateWithLeft( Position K2 )  // K2 is grandfather
{
    Position K1;  // K1 is parent

    K1 = K2->Left;
    K2->Left = K1->Right;
    K1->Right = K2;

    K2->Height = Max( Height( K2->Left ), Height( K2->Right ) ) + 1;  // Don't forget "+1"
    K1->Height = Max( Height( K1->Left ), K2->Height ) + 1;

    return K1;  /* New root */
}
```

##### Single Rotation With Right
```c
static Position
SingleRotateWithRight( Position K1 )
{
    Position K2;

    K2 = K1->Right;
    K1->Right = K2->Left;
    K2->Left = K1;

    K1->Height = Max( Height( K1->Left ), Height( K1->Right ) ) + 1;
    K2->Height = Max( Height( K2->Right ), K1->Height ) + 1;

    return K2;  /* New root */
}
```

##### Double Rotation With Left
```c
static Position
DoubleRotateWithLeft( Position K3 )  // K3 is grandfather
{
    /* Rotate between K1 and K2 */
    K3->Left = SingleRotateWithRight( K3->Left );

    /* Rotate between K3 and K2 */
    return SingleRotateWithLeft( K3 );
}
```

##### Double Rotation With Right
```c
static Position
DoubleRotateWithRight( Position K1 )
{
    /* Rotate between K3 and K2 */
    K1->Right = SingleRotateWithLeft( K1->Right );

    /* Rotate between K1 and K2 */
    return SingleRotateWithRight( K1 );
}
```

##### Insert
```c
AvlTree
Insert( ElementType X, AvlTree T )
{
    if( T == NULL )
    {
        /* Create and return a one-node tree */
        T = malloc( sizeof( struct AvlNode ) );
        if( T == NULL )
            FatalError( "Out of space!!!" );
        else
        {  // End of recursion to create a leaf node
            T->Element = X; T->Height = 0;
            T->Left = T->Right = NULL;
        }
    }
    else
    if( X < T->Element )
    {
        T->Left = Insert( X, T->Left );
        if( Height( T->Left ) - Height( T->Right ) == 2 )
            if( X < T->Left->Element )
                T = SingleRotateWithLeft( T );
            else
                T = DoubleRotateWithLeft( T );
    }
    else
    if( X > T->Element )
    {
        T->Right = Insert( X, T->Right );
        if( Height( T->Right ) - Height( T->Left ) == 2 )
            if( X > T->Right->Element )
                T = SingleRotateWithRight( T );
            else
                T = DoubleRotateWithRight( T );
    }
    /* Else X is in the tree already; we'll do nothing */

    T->Height = Max( Height( T->Left ), Height( T->Right ) ) + 1;
    return T;
}
```

### Splay Trees

#### Defination

>After a node is accessed, it is **pushed to the root** a series of AVL tree rotations  

>Target:  
>Any M consecutive tree operations starting **from an empty** tree take at most **O(MlogN)** time  

easy to implement, no extra space, adaptive(continuous access)  

#### Implementation

##### Splay(X)
For any nonroot node X, denote its parent by P and gradparent by G:  

*case 1(zig)*: P is the root -> Rotate X and P  

*case 2*: P is not the root  
- *zig-zag* ==> double rotation(same as AVL)  
    ![alt text](image-19.png)

- *zig-zig* ==> single rotation(*different from AVL*)  
    ![alt text](image-20.png)

##### Findkey
1. find as in BST  
2. *splay the found node*  

##### Insert
1. insert as in BST  
2. *splay the new node*  

##### Delete(X)
1. Find(X) -> X will be at the root  
2. Remove(X)  
3. FindMax(T~L~) -> The largest element will be the root of T~L~, and has **no right child**  
4. Make T~R~ the right child of the root of T~L~  

#### Coding

##### Structure Define
```c
struct SplayNode
{
    ElementType Element;
    SplayTree      Left;
    SplayTree      Right;
};

typedef struct SplayNode *Position;
static Position NullNode = NULL;  /* Needs initialization */
```

##### Splay
```c
SplayTree
Splay( ElementType Item, Position X )
{
    static struct SplayNode Header;
    Position LeftTreeMax, RightTreeMin;

    Header.Left = Header.Right = NullNode;
    LeftTreeMax = RightTreeMin = &Header;
    NullNode->Element = Item;

    while( Item != X->Element )
    {
        if( Item < X->Element )
        {
            if( Item < X->Left->Element )
                X = SingleRotateWithLeft( X );
            if( X->Left == NullNode )
                break;
            /* Link right */
            RightTreeMin->Left = X;
            RightTreeMin = X;
            X = X->Left;
        }
        else
        {
            if( Item > X->Right->Element )
                X = SingleRotateWithRight( X );
            if( X->Right == NullNode )
                break;
            /* Link left */
            LeftTreeMax->Right = X;
            LeftTreeMax = X;
            X = X->Right;
        }
    }  /* while Item != X->Element */

    /* Reassemble */
    LeftTreeMax->Right = X->Left;
    RightTreeMin->Left = X->Right;
    X->Left = Header.Right;
    X->Right = Header.Left;

    return X;
}
```

##### Delete
```c
SplayTree
Remove( ElementType Item, SplayTree T )
{
    Position NewTree;

    if( T != NullNode )
    {
        T = Splay( Item, T );
        if( Item == T->Element )
        {
            /* Found it! */
            if( T->Left == NullNode )
                NewTree = T->Right;
            else
            {
                NewTree = T->Left;
                NewTree = Splay( Item, NewTree );
                NewTree->Right = T->Right;
            }
            free( T );
            T = NewTree;
        }
    }

    return T;
}
```

### Amortized Analysis

consider the worst-case running time for any **sequence of M operations**  

>Target:
>Any M consecutive operations (**from initial stat**) take at most **O(MlogN)** time -- **Amortized time bound**  

>**worst-case bound >= amortized bound >= average-case bound**    

#### Aggregate analysis
e.g. *Stack with MultiPop*  

Consider a sequence of n  
*Push*, *Pop* and *MultiPop* operations on an initially empty stack

T~amortized~ = O(n)/n = O(1)  

#### Accounting method

>When an operation's amortized cost *c~i~_hat* exceeds its actual cost *c~i~*, we assign the difference to specific objects in the data structure ad **credit**  
>
>Credit can help pay for later operations whose amortized cost is less than their actual cost  

![alt text](image-21.png)

e.g.  

![alt text](image-22.png)

#### Potential method  

Take a closer look at the **credit** --  

![alt text](image-23.png)

We call the $\phi$ **potential function**  

![alt text](image-24.png)
![alt text](image-25.png)  

**In general, a good potential function should always assume its minimum at the start of the sequence(like 0)**  

e.g.  

![alt text](image-26.png)  

#### Analysis On the Splay Tree  

![alt text](image-27.png)  

![alt text](image-28.png)  

![alt text](image-29.png)

>**[Theorem]** The amortized time to splay a tree with root T at node X is at most **3(R(T) - R(X)) + 1 = O(logN)**  

![alt text](359abd6c46969337094c34579e6fe810.png)  

>To sum up  
>**Amortized bound:** Average cost for M consecutive operation from some initial state  
>**Credit(Accounting method):** The different between the amortized costs and actual costs  
>**Potential(Potential method):** A function of the state of the data structure. $\phi$(S) represents work that has been paid for but not yet performed  

## Chapter 2: Red-Blcak Tree & B+ Tree

### Red-Black Trees

[红黑树 - 定义, 插入, 构建](https://www.bilibili.com/video/BV1Xm421x7Lg/?spm_id_from=333.788&vd_source=14ad5ada89d0491ad8ab06103ead6ad6)
[红黑树 - 删除](https://www.bilibili.com/video/BV16m421u7Tb/?spm_id_from=333.788&vd_source=14ad5ada89d0491ad8ab06103ead6ad6)

#### Definition

>1. node color: red or black  
>2. root is black  
>3. leaves(NIL) is black  
>4. children of red must be black  
>5. for each node v, all descending paths from v to leaves contain the same number of black nodes  

>**Height:** called the black height of v: bh(v)[excluding v]  
>bh(T) = bh(root)  

![alt text](image.png)  

![alt text](image-1.png)  

>**Lemma：**  
>1. A red-black tree with N internal nodes has height at most 2ln(N + 1).  
>2. bh(Tree) >= h(Tree) / 2  
![alt text](image-31.png)  
>3. The subtree of node x has at least 2^bh(x)^ - 1 internal nodes.
[红黑树的时间复杂度分析](https://blog.csdn.net/l_o_s/article/details/105703296?ops_request_misc=&request_id=&biz_id=102&utm_term=%E7%BA%A2%E9%BB%91%E6%A0%91%E6%97%B6%E9%97%B4%E5%A4%8D%E6%9D%82%E5%BA%A6&utm_medium=distribute.pc_search_result.none-task-blog-2~all~sobaiduweb~default-7-105703296.142^v100^pc_search_result_base8&spm=1018.2226.3001.4187)

#### Implementation

##### Insert

>1. insert it as in BST  
>2. **mark the new node red**  

*case 1:* parent is black ==> Done  

*case 2:* parent is red & uncle is red  

![alt text](image-4.png)  
- parent & uncle & grandparent change color  
- check grandparent  

*case 3:* parent is red & uncle is black  

![alt text](image-6.png)

- (LL, LR, RL, RR) rotation  
- change the rotated node and rotation center(grandparent & parent)  

symmetric as the same  

##### Delete

###### Simple Delete
as if in BST(**only change the key, keep the color**)  
==> u(the node should be deleted) has no child or has only one child, u is black and the child is red 

###### Adjustment  

*x is the problem node*(suppose x on the left, symmetric as the same)

- x is red ==> Done  

- x is black ==> **Must add 1 black to the path of the replacing node**  

*case 1:* x's sibling(w) is red ==> change parent & w'color + rotate towards x  

![alt text](image-32.png)  


*case 2:* w is black & w's children are all black ==> change w into red  
- *case 2.1:* parent is red ==> change parent into black  
- *case 2.2:* parent is black ==> x change into its parent, continue to add 1 black to the path of x(new x)  

![alt text](image-33.png)  
  
*case 3:* w is black & w's left child is red & right child is black ==> change w into red + do RR Rotation ==> *case 4*  

*case 4:* w is black & w's right child is red ==> color change: w's right child into black, w into parent's color, parent into black + parent rotate towards x  

![alt text](image-34.png)  

e.g.  

![alt text](image-35.png)  

Number of *rotations*  
|   |AVL|Red-Black Tree|
|---|---|--------------|
|Insertion|<=2|<=2|
|Deletion|O(logN)|<=3|

### B+ Tree

#### Definition

>A B+ tree of order M is an M-ary tree with the following properties:  
>  
>1. The data items are stored at leaves  
>2. The nonleaf nodes store up to M - 1 keys to guide the searching; key i represents the smallest key in subtree i + 1  
>3. The root is either a leaf or has between 2 and M children  
>4. All nonleaf nodes(excpet the root) have betweeen [M / 2] and M children(fanout of an internal node); for root is between 2 and M  
>5. All leaves are at the same depth and have between [M / 2] and M data items; for root being the leaf is between 1 and M  

![alt text](image-30.png)  

![alt text](image-11.png)  

## Chapter 3: Inverted File Index

An inverted index is a database index storing a mapping from content to its locations in a table, or in a document or a set of documents. The purpose of an inverted index is to allow fast full-text searches, at a cost of increased processing when a document is added to the database. The inverted file may be the database file itself, rather than its index.   ---- WIKIPEDIA  

### Basic Form  

|No.|Term|<Times; (Document ID; Word ID)>|
|---|----|-------------------------------|
|1|Dongqianyu|<2; (9; 35), (6, 45)>|
| |Term Dictionary|Posting List|

>Why do we keep **"time"**(frequency)?
>- Can save memory space when doing **Boolean Query**.
>- Often kept in a linked list and stored for easy merging.

```c
while ( read a document D ) {
    while ( read a term T in D ) {
        if ( Find( Dictionary, T ) == false )
            Insert( Dictionary, T );
        Get T’s posting list;
        Insert a node to T’s posting list;
    }
}
Write the inverted index to disk;
```

- **read a term T in D**: Token Analyzer; Stop Filter
  - *Word Stemming*: only its stem or root form is left
  - *Stop Words*: useless to index them
  - <u>Byte Pair Encoding</u>
- **Find( Dictionary, T )**: Vocabulary Scanner
  - *Search Trees*: B- trees, B+ trees, Tries, ... 
  - *Hashing*
    - pros: faster for one word
    - cons: scanning in sequential order is not possible
  - *Thresholding*
    - Document: only retrieve the top x documents where the documents are ranked by weight ==> <u>Not feasible for Boolean queries</u>; Can miss some relevant documents due to truncation
    - Query: Sort the query terms by their frequency in <u>ascending</u>(low-frequency trems are more important) order; search according to only some percentage of the original query terms
    ![alt text](image-7.png)
- **Insert( Dictionary, T )**: Vocabulary Insertor
- **Write the inverted index to disk**: Memory management
  - *Distributed indexing*: Each node contains index of a subset of collection
    - Term-partitioned index: Strong disaster tolerance capability
    - Document-partitioned index
  - *Docs come in over time*
  ![alt text](image-3.png)
  - *Compression*
  ![alt text](image-5.png)
  
### Measures for a search engine 

- How fast does it index
- How fast does it search
- Expressiveness of query language

#### Relevance measurement
Relevance measurement requires 3 elements:
- A benchmark document collection
- A benchmark suite of queries
- A binary assessment of either **Relevant** or **Irrelevant** for each *query-doc pair*

| |Relevant|Irrelevant|
|-|--------|----------|
|Retrieved|R~R~|I~R~|
|Not Retrieved|R~N~|I~N~|

**Precision P** = RR / (RR + IR)
**Recall R** = RR / (RR + RN)

![alt text](image-8.png)

In machine learning: 
| |True(Gound Truth)|False|
|-|--------|----------|
|Positive(Pred)|TP|FP|
|Negative|TN|FN|

![alt text](image-9.png)

*AUC*: Area Under Curve

## Chapter 4: Heap

### Leftist Heap

define the **null path length**, *npl(X)*, of ant node X to be the length of the shortest path from X to a node without two children

the *npl* of a node with zero or one child is 0, while *npl*(nullptr) = -1

```
for every node X in the heap, the null path length of the left child is at least as large as that of the right child
(for each u, the right decending path from u to null is one of the shortest path from u to null)

ensure the tree is unbalanced, tend to have deep left paths and is preferable to facilitate merging
```

![alt text](image-12.png)

```
Lemma:
For a leftist heap with n nodes, its right path has at most log2(n + 1) nodes.
<==> A leftist heap with r nodes on the right path must have at least 2^r - 1 nodes.
```

#### merge

