#include <stdio.h>

int p[60];

int find(int x){
    return p[x] == x ? x : (p[x] = find(p[x]));
}

int main(){
    int e[][3] = {
        {3, 5, 1}, 
        {1, 2, 2}, 
        {4, 5, 2}, 
        {0, 1, 4}, 
        {0, 2, 4}, 
        {1, 3, 5}, 
        {2, 3, 5}, 
        {3, 4, 6}
    };

    int n = 6; //vertices
    int m = 8; //edges
    int a,b,w,cost=0;
    int i;

    for (i=0;i<60;i++){
        p[i] = i;
    }

    for(i=0; i<m ; i++){
        a = find(e[i][0]);
        b = find(e[i][1]);
        w = e[i][2];
        
        if(a != b){
            p[b] = a;
            cost = cost+w;
            print("%d - %d , (%d)",e[i][0],e[i][1],w);
        }
    }
    print("cost = %d",cost);
    
}