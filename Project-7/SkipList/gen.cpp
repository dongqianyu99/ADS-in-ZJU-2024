#include <cstdio>
#include <random>
#include <vector>
#include <ctime>
#include <cstdlib>

std::vector<int> key_list;
int N = 500000;

int rand_int(){return (rand()<<15) + rand();}
const int RAND_INT_MAX = (RAND_MAX << 15) + RAND_MAX;

int main(){
	srand(time(0));
	// for(int i = 1; i <= 10 ; i ++ ){
	// 	printf("%d\n",rand_int());
	// }
	// return 0 ;
	freopen("data.in","w",stdout);
	// scanf("%d",&N);
	printf("%d\n",N);
	key_list.push_back(rand_int());
	for(int i = 1; i <= N ; i ++ ) {
		int opt = rand()%4 ;
		//为了让 SkipList 长度增加，25%查询，50% 插入，25% 删除
		if(opt == 0){
			int x = rand();
			if(x<RAND_MAX*0.4){
				printf("0 %d\n",key_list[rand_int()%key_list.size()]);
			}
			else if(x<RAND_MAX*0.8){
				printf("3 %d\n",1+rand_int()%key_list.size());
			}
			else printf("0 %d\n",rand_int());
		}
		if(opt == 1 || opt == 3){
			if(rand()<RAND_MAX*0.8){
				int key = rand_int();
				printf("1 %d %d\n",key,rand_int());
				key_list.push_back(key);
			}
			else printf("1 %d %d\n",key_list[rand_int()%key_list.size()],rand_int());
		}
		if(opt == 2){
			if(rand()<RAND_MAX*0.8){
				printf("2 %d\n",key_list[rand_int()%key_list.size()]);
			}
			else printf("2 %d\n",rand_int());
		}
	}
	return 0 ;
}
