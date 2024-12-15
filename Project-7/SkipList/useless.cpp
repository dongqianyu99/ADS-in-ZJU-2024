//这是不支持第k小的简陋版本。没有用。

//假设操作分为查询，插入，删除
//每组数据为 (key,value)，且 key>0,value>0 ，查询时若 key 存在则返回 value，否则返回0
//插入时若 key 存在则修改其 value 为新值，不存在则新建节点
//删除时若 key 不存在，输出“Error:delete_key doesn't exist”

//指令格式：查询：0 key
//         插入：1 key value
//		   删除：2 key

#include <cstdio>
#include <random>
#include <ctime>
#include <cstdlib>

const double p = 0.5;
const int maxlevel = 20;
const int inf = INT32_MAX;

const int debug = 0;

struct node{
	int key,value;
	node *nxt[maxlevel + 1]; //nxt[i] 表示第 i 层中，当前节点的右节点
}*head,*tail;
//head:(-inf,0);tail:(inf,0)，哨兵节点，可以处理边界情况。
//head 和 tail 存在于每一层。

node *new_node(int key,int value){
	node *cur = new node;
	cur->key = key ; cur->value = value;
	return cur ;
}

int cur_maxlevel;

int get_level(){
	int level = 0;
	int P = p*RAND_MAX;
	while(level < maxlevel && rand()<P) level ++ ;//模拟“每层有p的概率向上一层”且限制最大层数
	return level ;
}

int search(int key){
	node *cur = head;
	for(int i = cur_maxlevel ; i >= 0 ; i-- ){
		while(cur->nxt[i]->key < key) //找到第 i 层最大的 键值小于key 的节点
		{
			if(debug){
				printf("cur_search:(%d,%d)\n",cur->key,cur->value);
				printf("cur->nxt[%d]:(%d,%d)\n",i,cur->nxt[i]->key,cur->nxt[i]->value);				
			}
			cur = cur->nxt[i];
		}
	}
	//现在cur是所有节点中最大的 键值小于key 的节点
	//是否找到取决于 cur 的右节点是否为待查询节点
	//注意，由于哨兵节点 head,tail 的存在，cur 和 cur -> nxt[0] 都是一定存在的
	if(debug){
		printf("cur:(%d,%d)\n",cur->key,cur->value);
		printf("cur->nxt[0]:(%d,%d)\n",cur->nxt[0]->key,cur->nxt[0]->value);
	}
	cur = cur->nxt[0];
	if(cur->key == key) return cur->value;
	return 0 ;
}

node *node_to_update[maxlevel+1];

//在第i层，将q置于p后
void insert_after(node *p,node *q,int i){
	q->nxt[i] = p->nxt[i] ;
	p->nxt[i] = q ;
}

//在第i层，将p后面的节点删除
void delete_after(node *p,int i){
	//此函数被调用，当且仅当 p->nxt[i] 为该删除节点，也即 p->nxt 不为 tail
	//故 p->nxt->nxt 必合法
	p->nxt[i] = p->nxt[i]->nxt[i];
}

void insert(int key,int value){
	node *cur = head;
	for(int i = cur_maxlevel ; i >= 0 ; i-- ){
		if(debug){
			printf("insert_i:%d\n",i);
		}
		while(cur != tail && cur->nxt[i]->key < key){
			if(debug) printf("cur:(%d,%d)\n",cur->key,cur->value);
			cur = cur->nxt[i];
		}
		if(cur == tail) puts("Error:cur = tail when inserting");
		//每一层需要修改的节点位置，即“最大的键值小于key的节点”，也即cur
		node_to_update[i] = cur; //记录下每一层待修改的节点位置
	}
	cur = cur->nxt[0] ;
	//若已存在，直接修改
	if(cur->key == key){
		cur->value = value ;
		return ;
	}
	//否则新建节点，并依次插入
	node *node_to_insert = new_node(key,value) ;
	int level = get_level();
	if(debug){
		printf("level:%d\n",level);
		fflush(stdout);
	}
	//若 level 超过 cur_maxlevel ，将其置为 cur_maxlevel + 1
	if(level > cur_maxlevel){//若 level > cur_maxlevel ，则 cur_maxlevel < maxlevel，即 cur_maxlevel+1 <= maxlevel
		cur_maxlevel ++ ;
		level = cur_maxlevel;
		//此新层的 node_to_update 为 head
		node_to_update[level] = head;
	}
	for(int i = level ; i >= 0 ; i-- ){
		insert_after(node_to_update[i],node_to_insert,i);
	}
}

void Delete(int key){
	node *cur = head;
	for(int i = cur_maxlevel ; i >= 0 ; i-- ){
		while(cur->nxt[i]->key < key)
			cur = cur->nxt[i];
		node_to_update[i] = cur; //记录下每一层待修改的节点位置
	}
	cur = cur->nxt[0] ;
	if(cur->key != key){
		puts("Error:delete_key doesn't exist");
		return ;
	}
	for(int i = cur_maxlevel ; i >= 0 ; i -- )
		if(node_to_update[i]->nxt[i]->key == key)
			delete_after(node_to_update[i],i);
	delete cur;//释放空间
	if(head->nxt[cur_maxlevel] == tail) cur_maxlevel--; //若当前最高层被删空，调整
}

void SkipList_init(){
	srand(time(0));
	head = new_node(-inf,0);
	tail = new_node(+inf,0);
	cur_maxlevel = -1 ;
	for(int i = 0 ; i <= maxlevel ; i ++ ) head->nxt[i] = tail;
}

int n;//指令个数

int main(){
	freopen("data.in","r",stdin);
	freopen("SkipList.out","w",stdout);
	SkipList_init();
	if(debug){
		for(int i = 0 ; i <= 10 ; i ++ ) printf("level:%d\n",get_level());
	}
	scanf("%d",&n);
	for(int i = 1; i <= n; i ++ ){
		int opt ; scanf("%d",&opt);
		if(opt == 0){
			int key; scanf("%d",&key);
			printf("%d\n",search(key));
		}
		if(opt == 1){
			int key,value ; scanf("%d%d",&key,&value);
			insert(key,value);
		}
		if(opt == 2){
			int key; scanf("%d",&key);
			Delete(key);
		}
		if(debug){
			printf("cur_maxlevel:%d\n",cur_maxlevel);
		}
	}	
	return 0 ;
}
