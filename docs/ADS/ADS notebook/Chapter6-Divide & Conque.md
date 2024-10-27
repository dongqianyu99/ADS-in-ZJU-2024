# Chapter 6: Divide & Conquer  

>Recursively  
>   **Divide** the problem into a number of sub-problems  
>   **Conquer** the sub-problems by solving them recursively  
>   **Combine** the solutions to the sub-problems into the solution for the original problem  

$\Rightarrow$ **General recurrence:** $T(N)=aT(N/b)+f(N)$  

## Example: Closest Points Problem  

Given $N$ points in a plane. Find the *closest pair* of points. (If two points have the same position, then that pair is the closest with distance $0$.)  

**Divide and Conquer Way:**  
- Sort according to x-coordinates and divide  
- Conquer by forming a solution from left, right, and cross  

![alt text](54.png)  

Problem occurs when dealing with *cross*  

Suppose $min\{left, right\}=\delta$, we only need to deal with points inside the green bounds ($\delta$-strip):  

![alt text](55.png)  

Moreover, the possible points-pair should be in a $2\delta \times \delta$ rectangle:  

![alt text](c:/Users/DELL/AppData/Local/Temp/57.svg)  

and *for every points-pair in the left half or right half rectangle, the distence should be no less than* $\delta$, which means it at most contains 8 points (even with points overlaped):   

![alt text](58.png)  

We enumerate all the points in left strip and it takes at most $O(N)$  

Therefore, we have:  

$T(N) = \underbrace{2\; T(\frac{N}{2})}_{\text{Step 1. divide}} + \underbrace{O(N)}_{\text{Step 2. across}} = O(N\log N) \Rightarrow$ HOW TO CALCULATE?  

## Three methods for solving recurrences:  

$T(N)=aT(N/b)+f(N)$  

Details to be ignored:  
- if $(N/b)$ is an integer or not  
- always assume $T(n)=\Theta$ for small $n$  

### Substitution method  

***Guess, then prove by induction***  

example from [Isshiki修's Notebook](https://note.isshikih.top/cour_note/D2CX_AdvancedDataStructure/Lec07/#%E4%BB%A3%E6%8D%A2%E6%B3%95)

?>$T(N) = 2\; T(\frac{N}{2}) + N$

>**预设**：$T(N) = O(N\log N)$  
>**代入**：  
> - 对于足够小的 $m < N$，有：  
>$T(\frac{m}{2}) = O(\frac{m}{2}\log \frac{m}{2}) \leq c \frac{m}{2}\log \frac{m}{2}$  
> - 将上式代入：  
> $T(m) = 2\; T(\frac{m}{2}) + m$  
> - 得：  
> $T(m) \leq 2\; c \frac{m}{2}\log \frac{m}{2} + m \leq c m \log m \text{ for } c \geq 1$  
>对于足够小的 $m = 2$ 式子就可以成立，由归纳法得结论成立。  

### Recursion-tree method  



### Master method  


