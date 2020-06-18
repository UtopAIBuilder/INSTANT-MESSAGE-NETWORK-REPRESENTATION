#include<stdio.h>
#include<stdlib.h>
#include "header.h"
#define m 30
int main()
{
    Graph g;
    initGraph(&g);
    printf("success\n");
    int count=m;
    while (count--)
    {
        startConvo(&g);
    }
    printf("success in start of convo...\n");
    count=m;
    while (count--)
    {
        endConvo(&g);
    }
    printf("success in end of convo...\n");

    for (int i = 0; i <= 2*m+1; i++)
    {
        for (int j = 1; j <= g.vertices; j++)
        {
            printf("adj[%d], noOfConnects:(%d) ",j,noOfConnects(&g,i,j));
            printVersions(i,g.adjList+j);
        }
        printf("\nthis was version:%d\n",i);
        
    }
    
/*     for (int j = 1; j <= g.vertices; j++)
        {
            printf("[");
            for (int i = 0; i < 60; i++)
            {
                printf("%d,",noOfConnects(&g,i,j));
            } 
            printf("%d],\n",noOfConnects(&g,60,j));
        }  */  
}
