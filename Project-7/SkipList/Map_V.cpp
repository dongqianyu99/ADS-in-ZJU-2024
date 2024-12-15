//这个代码完全使用 map 实现
//因为 map 没有实现找第 k 小的功能，所以复杂度是 N^2 的
//但是正确性完全可以保证

#include <cstdio>
#include <map>

std::map<int,int> M;
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
				int i = 0;
				for(auto it = M.begin() ; it != M.end() ; it ++ ){
					i ++ ;	
					if(i == k){
						printf("%d\n",it->first);
						break;
					}
				}				
			}

		}
	}
	return 0 ;
}
