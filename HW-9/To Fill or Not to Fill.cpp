#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <map>

using namespace std;

double Cmax, D, Davg;
int N;
double maxToGo;

struct station{
    double price;
    double dist;
}stations[510]; 

bool cmp(station s1, station s2){
    return s1.dist < s2.dist;
}  

int main()
{
    cin >> Cmax >> D >> Davg >> N;  // Cmax油箱最大容量，D距离，Davg单位油能跑的距离，N有多少加油站
    maxToGo = Cmax * Davg;
    for (int i = 1; i <= N; i++)
        scanf("%lf%lf", &stations[i].price, &stations[i].dist);
    sort(stations, stations + N + 1, cmp);
    stations[N + 1].dist = D;
    

    // for (int i = 1; i <= N; i++){
    //     cout << stations[i].dist << endl;
    // }
    
    double res = 0;
    if ( stations[1].dist != 0)
        printf("The maximum travel distance = 0.00\n");
    double curoil = 0;
    for (int i = 1; i <= N; i++){
        if (stations[i].dist + maxToGo < stations[i + 1].dist){
            printf("The maximum travel distance = %.2lf\n", stations[i].dist + maxToGo);
            break;
        }
        if (i != 1)
            curoil -= (stations[i].dist - stations[i - 1].dist) / Davg;
        
        bool flag = false;  // 查看后面有没有比当前便宜的加油站
        for (int j = i + 1; j <= N; j++)
            if ((stations[j].dist - stations[i].dist) <= maxToGo && stations[j].price < stations[i].price){
                flag = true;
                double cost = (stations[j].dist - stations[i].dist) / Davg;
                if (cost > curoil){
                    res += stations[i].price * (cost - curoil);
                    curoil = cost;
                }
                break;
            }
        if (!flag){
            if ((stations[i].dist + maxToGo) >= D){
                res += ((D - stations[i].dist) / Davg - curoil) * stations[i].price;
                printf("%.2lf\n",res);
                break;
            }
            else{
                res += (Cmax - curoil) * stations[i].price;
                curoil = Cmax;
            }
        }
        // printf("%d", flag);
    }

    return 0;
}