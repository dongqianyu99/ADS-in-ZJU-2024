#include <cstdio>
#include <map>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp> //若不能 include ，说明你的环境不是 GCC 而是 MSVC 。
//pb_ds 库是 GNU C++ 标准库的一部分，其中包含了红黑树

//这个代码使用了 pb_ds 库实现
//正确性和复杂度均可以保证。

// std::map<int,int> M;

__gnu_pbds::tree<int,int,std::less<int>,__gnu_pbds::rb_tree_tag,__gnu_pbds::tree_order_statistics_node_update> M;
int n ;

int main(){
	freopen("data.in","r",stdin);
	freopen("Map.out","w",stdout);
	scanf("%d",&n);
	for(int i = 1; i <= n; i ++ ){
		int opt ; scanf("%d",&opt);
		if(opt == 0){
			int key; scanf("%d",&key);
			auto it = M.find(key);
			if(it != M.end()) printf("%d\n",it->second);
			else puts("0");
		}
		if(opt == 1){
			int key,value ; scanf("%d%d",&key,&value);
			M[key] = value ;
		}
		if(opt == 2){
			int key; scanf("%d",&key);
			auto it = M.find(key);
			if(it == M.end()) puts("Error:delete_key doesn't exist");
			else M.erase(key);
		}
		if(opt == 3){
			int k ; scanf("%d",&k) ;
			if(k > M.size()) puts("0");
			else{
				printf("%d\n",M.find_by_order(k-1)->first);
				// M.find_by_order(k-1) 表示 M 中第 k 小。因为最小的被编号为 0
			}
		}
	}
	return 0 ;
}
