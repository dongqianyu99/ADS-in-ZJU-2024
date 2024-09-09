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