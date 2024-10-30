#include <stdio.h>

#define MAXN 10
#define MAXS 1000

int need_time(const int time[], const int score[], int happy_score, int n);

int main() {
  int n, i, happy_score;
  int time[MAXN], score[MAXN];
  scanf("%d %d", &n, &happy_score);
  for (i = 0; i < n; ++i)
      scanf("%d", &time[i]);
  for (i = 0; i < n; ++i)
      scanf("%d", &score[i]);
  printf("%d\n", need_time(time, score, happy_score, n));
  return 0;
}

/* Your function will be put here */

//依次考虑是否做每个题目
//f[i][j]表示已经处理前 i 个题目，获得的总分数为 j 时需要的最短时间
int min(int a, int b){
    return a < b ? a : b;
}

int need_time(const int time[], const int score[], int happy_score, int n){
    int score_tol = 0;
    for (int i = 0; i < n; i++)
        score_tol += score[i];

    int f[n + 5][score_tol + 5];
    for (int i = 0; i <= n; i++)
        for (int j = 0; j <= score_tol; j++)
            f[i][j] = 0x3f3f3f3f;

    // printf("1");
    f[0][0] = 0;

    for (int i = 1; i <= n; i++){
        for (int j = 0; j <= score_tol; j++)
            f[i][j] = f[i - 1][j];
        for (int j = score[i - 1]; j <= score_tol; j++)
            f[i][j] = min(f[i][j], f[i - 1][j - score[i - 1]] + time[i - 1]);
    }

    int res = 0x3f3f3f3f;
    for (int j = happy_score; j <= score_tol; j++)
        res = min(res, f[n][j]);

    if (res == 0x3f3f3f3f)
        res = -1;

    return res;
}