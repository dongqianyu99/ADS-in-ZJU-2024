#include <cstdio>
#include <math.h>
#include<fstream>
#include<iostream>
#include<windows.h>

const int maxn = 6e6 + 5;
typedef long long Element_Type;

int n,m,s; // 点数，边数，起点

struct edge{
	int v,nxt;
	Element_Type w;
}e[maxn];

int fir[maxn],edge_cnt;

//链表方式存储边
void add_edge(int u,int v,Element_Type w){
	e[++edge_cnt].nxt = fir[u]; e[edge_cnt].v = v; e[edge_cnt].w = w; fir[u] = edge_cnt;
}

template<typename T>
inline void swap(T &a,T &b){
	T temp = a; a = b; b = temp;
}

struct BioHeap{
	//数组实现二叉堆（小根堆）
	struct node{
		int id;Element_Type val;//dis[id] = val
		node(int Id = 0,Element_Type Val = 0){
			id = Id;
			val = Val;
		}
		bool operator<(node other){
			return val < other.val;
		}
		bool operator>(node other){
			return val > other.val;
		}
	}H[maxn];
	int siz;//堆内元素个数
	
	int pos[maxn];//记录在堆内的位置,pos[H[k].id] = k

	//上浮
	void percolate_up(int id){
		for(;id > 1;id /= 2){
			if(H[id/2] > H[id]) swap(pos[H[id/2].id],pos[H[id].id]),swap(H[id/2],H[id]);
			else break;
		}
	}

	//下沉
	void percolate_down(int id){
		while(id*2 <= siz){
			int t = id*2;
			if(t<siz && H[t]>H[t+1]) t = t + 1;
			if(H[id] > H[t]){
				swap(pos[H[id].id],pos[H[t].id]);
				swap(H[id],H[t]); id = t;
			}
			else break;
		}
	}

	void insert(int id,Element_Type val){
		pos[id] = ++siz;
		H[siz] = node(id,val); percolate_up(siz);
	}
	void decrease_key(int id,Element_Type val){
		int p = pos[id];
		if(H[p].val < val){
			puts("Error:meets a higher key when decrease key in BioHeap");
			return ;
		}
		H[p].val = val; percolate_up(p);
	}
	//查询当前最近节点
	int get_min(){
		if(siz == 0){
			puts("Error:empty heap when get min in BioHeap");
			return 0;
		}
		return H[1].id;
	}
	void delete_min(){
		if(siz == 0){
			puts("Error:empty heap when delete_min in BioHeap");
			return ;
		}
		swap(pos[H[1].id],pos[H[siz].id]); swap(H[1],H[siz]);
		siz--;
		percolate_down(1);
	}
	int empty(){return siz == 0;}
}Bio;

//斐波那契堆
struct FibHeap{
	struct node{
		int id;Element_Type val;
		int deg;//度数
		node *l,*r;//左兄弟和右兄弟，双向循环链表维护兄弟关系
		node *son,*fa;//第一个孩子，父亲
		bool mark;//是否被删除过孩子
		node(int Id = 0,Element_Type Val = 0){
			id = Id;val = Val;
			deg = 0;l = r = this ;son = fa = 0; mark = 0;
			//初始 左右兄弟都指向自己，从而保证循环
		}
		bool operator<(node other){
			return val < other.val;
		}
		bool operator>(node other){
			return val > other.val;
		}
	}*Min,*pos[maxn];
	//Min 表示整个 FibHeap 中的最小节点
	int siz;

	//在双向链表中，将 t 接到 s 后面
	void insert_list(node *s,node *t){
		// if(s==0 || t==0) while(1);
		t->r = s->r; s->r->l = t;
		t->l = s; s->r = t;
	}

	//在双向链表中，删掉 s
	void remove_list(node *s){
		// if(s == 0) while(1);
		s->l->r = s->r;
		s->r->l = s->l;
	}

	//新建节点，并插入到 root_list 中
	void insert(int id,Element_Type val){
		node *cur = new node(id,val);
		if(siz == 0) Min = cur;
		else{
			insert_list(Min,cur);
			if(cur->val < Min->val) Min = cur;
		}
		siz ++ ;
		pos[id] = cur;
	}

	//将 t 接为 s 的儿子
	void link(node *s,node *t){
		if(s->son) insert_list(s->son,t);
		else s->son = t,t->l=t->r=t;
		t->fa = s;
		s->son = t;
		s->deg ++ ;
	}

	node* tmp[maxn];

	void delete_min(){
		//处理特殊情况
		if(siz == 0){
			puts("Error:empty heap when delete_min in FibHeap");
			return ;
		}
		if(siz == 1){
			pos[Min->id] =0;
			delete Min;
			Min = 0;siz = 0;
			return ;
		}
		int D = ceil(log(siz)/log(1.6)); //度数上界
		//将 Min 的所有儿子放入 root_list 中
		node *cur = Min->son;
		if(cur){
			do{
				node *nxt = cur->r;
				cur->fa = 0 ;
				insert_list(Min,cur);
				cur = nxt;
			}while(cur != Min->son);
		}

		//对 root_list 中除了 Min 之外的节点按度数合并
		cur = Min->r;
		for(int i = 0 ; i <= D ; i ++ ) tmp[i] = 0;
		while(cur != Min){
			node *nxt = cur->r; remove_list(cur);
			cur->l = cur->r = cur;
			int d = cur->deg;
			while(tmp[d]){
				//保证 cur 更小
				if(tmp[d]->val < cur->val) swap(tmp[d],cur);
				link(cur,tmp[d]);
				tmp[d] = 0;
				d ++ ; //合并后度数 + 1
			}
			tmp[d] = cur; cur = nxt;
		}
		pos[Min->id] = 0; delete Min ; Min = 0; //删除 Min
		//将合并后的结果重新连成 root_list
		for(int i = 0; i <= D; i ++ ){
			if(tmp[i] == 0) continue;
			if(Min == 0) Min = tmp[i];
			else{
				insert_list(Min,tmp[i]);
				if(Min->val > tmp[i]->val) Min = tmp[i];
			}
			tmp[i] = 0;
		}
		siz -- ;
	}

	//将 cur 结点从其父亲上脱离，并放到 root_list 中，mark 置 0
	void cutoff(node *cur){
		if(cur->fa){
			//维护父亲的 deg , son
			cur->fa->deg -- ;
			if(cur->fa->son == cur){
				if(cur->r != cur) cur->fa->son = cur->r;
				else cur->fa->son = 0;
			}
			remove_list(cur),insert_list(Min,cur) ; //这里如果在 cur->fa == 0 的情况下执行这行代码就会出问题
			cur->fa = 0; cur->mark = 0 ;
		}
	}

	//递归剪切，将 mark == 0 的 mark 置为 1 并返回，否则将其 cutoff 并继续递归
	void clean(node *cur){
		if(cur == 0) return ;
		if(cur->mark == 0) cur->mark = 1;
		else{
			node *fa = cur->fa ;
			cutoff(cur); clean(fa);
		}
	}

	void decrease_key(int id,Element_Type val){
		node *cur = pos[id];
		if(cur == 0){
			puts("Error:ZERO");
			return ;
		}
		if(cur->id != id){
			puts("Error:wrong position!");
			return ;
		}
		if(cur->val < val){
			puts("Error:meets a higher key when decrease key in FibHeap");
			return ;
		}
		cur->val = val;
		if(Min == cur) return ;
		node *fa = cur->fa;
		if(fa && cur->val < fa->val){
			cutoff(cur) ; clean(fa);
		}
		if(Min->val > cur->val) Min = cur;
	}
	int get_min(){
		if(Min == 0){
			printf("siz:%d\n",siz);
			puts("Error:empty heap when get min in FibHeap");
			return 0 ;
		}
		return Min->id;
	}
	int empty(){return siz == 0;}
	
	//调试用代码
	void prints(node *cur){
		if(cur == 0) return ;
		node *p=cur;
		do{
			printf("id:%d fa:%d\n",p->id,p->fa?p->fa->id:0);
			prints(p->son);
			p = p->r;
		}while(p!=cur);
		puts("");
	}
	void print(){
		puts("----------------------------------------------");
		printf("siz:%d\n",siz);
		prints(Min);
		puts("-----------------------------------------------");
		fflush(stdout);
	}
}Fib;

const Element_Type inf = 1e18;

//Dijktra 二叉堆实现
Element_Type dis_bio[maxn];bool vis_bio[maxn];
void Dij_bioheap(){
	for(int i = 1; i <= n; i ++ ) dis_bio[i] = inf;
	dis_bio[s] = 0;Bio.insert(s,0);vis_bio[s] = 1;
	while(!Bio.empty()){
		int u = Bio.get_min() ; Bio.delete_min() ;
		// printf("u:%d\n",u);
		for(int i = fir[u]; i ; i = e[i].nxt){
			int v = e[i].v;
			if(dis_bio[v] > dis_bio[u] + e[i].w){
				dis_bio[v] = dis_bio[u] + e[i].w;
				if(vis_bio[v] == 0){
					vis_bio[v] = 1;
					Bio.insert(v,dis_bio[v]);
				}
				else Bio.decrease_key(v,dis_bio[v]);
			}
		}
	}
	for(int i = 1; i <= n; i ++ ) printf("%lld%c",dis_bio[i],i==n?'\n':' ');
}

//斐波那契堆实现
Element_Type dis_fib[maxn];bool vis_fib[maxn];
void Dij_fibheap(){
	for(int i = 1; i <= n; i ++ ) dis_fib[i] = inf;
	dis_fib[s] = 0;Fib.insert(s,0);vis_fib[s] = 1;
	while(!Fib.empty()){
		int u = Fib.get_min() ; Fib.delete_min() ;
		for(int i = fir[u]; i ; i = e[i].nxt){
			int v = e[i].v; 
			if(dis_fib[v] > dis_fib[u] + e[i].w){
				dis_fib[v] = dis_fib[u] + e[i].w;
				if(vis_fib[v] == 0){
					vis_fib[v] = 1;
					Fib.insert(v,dis_fib[v]);
				}
				else Fib.decrease_key(v,dis_fib[v]);
			}
		}
	}
	for(int i = 1; i <= n; i ++ ) printf("%lld%c",dis_fib[i],i==n?'\n':' ');
}

int main(){
	freopen("D:\\Project-2\\Dij\\road\\road_NY.txt","r",stdin);
	freopen("output_NY_try.txt","w",stdout);
	// std::ifstream infile("road_CAL.txt");
	// 	if(!infile){
	// 		std::cerr<<"无法打开文件！"<<std::endl;
	// 		return 1;
	// 	}

	scanf("%d%d%d",&n,&m,&s);   //n个点，m条边，s是起点
	//infile>>n>>m>>s;
	// printf("%d\n",n); return 0 ;
	DWORD t1,t2,t3,t4;
	for(int i = 1; i <= m; i ++ ){
		int u,v; Element_Type w; 
		scanf("%d%d%lld",&u,&v,&w); 
		// infile>>u>>v>>w;
		add_edge(u,v,w);
		// add_edge(v,u,w); //如果是无向图
	}
	t1=GetTickCount();
    Dij_bioheap();
	t2=GetTickCount();
	t3 = GetTickCount();
	Dij_fibheap();
	t4 = GetTickCount();
	printf("Bioheap time:%dms\n",t2-t1);
	printf("Fibheap time:%dms\n",t4-t3);
	return 0 ;
}
