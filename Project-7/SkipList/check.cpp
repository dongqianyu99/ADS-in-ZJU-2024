#include <windows.h>
#include <cstdio>

int main(){
	// int x = system("C:\\Windows\\System32\\fc.exe a.txt a.txt");
	// printf("%d\n",x);
	int N = 100000;
	for(int i = 1 ; i <= 5 ; i ++ ){
		system(".\\gen.exe");
		system(".\\Map.exe");
		system(".\\SkipList.exe");
		int x = system("C:\\Windows\\System32\\fc.exe SkipList.out Map.out");
		if(x) break ;
	}
	return 0 ;
}
