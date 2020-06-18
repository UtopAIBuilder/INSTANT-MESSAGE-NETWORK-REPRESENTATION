// here goes the damn fucking Partial persistance...

#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>
#include "header.h"


int mod_in_val=1,mod_in_next=2,no_mod=0,mod_in_leftPtr=2,mod_in_right=3;
int at_rear=0,at_front=1;
int **active_convo;
int occupied_indexs=0;
int globalVersion=0;
int base_version=0;
int flag_delete=0;
//int ver=0;


struct LinkedListNode* update(LinkedListNode* n1,LinkedListNode* n2,List *l)
{
	//printf("update called\n");
	if (n1==NULL)
	{
		createNewHead(n2,l);
		if(n2)
		n2->back_ptr=NULL;
		return NULL;
	}
	if (n1->flag==no_mod)
	{
		n1->flag=mod_in_next;
		n1->mod.ver=l->ver;
		n1->mod.uf.mnext=n2;
		l->main_header->highest_ver=l->ver;
		if (n2)
			n2->back_ptr=n1;
		return n1;
	}
	LinkedListNode *t=(LinkedListNode*)malloc(sizeof(LinkedListNode));
	copyLatestMods(t,n1);
	t->next=n2;
	if(n2)
	n2->back_ptr=t;
	update(t->back_ptr,t,l);
	return t;
}


LinkedListNode* getPosition(int p,List *l)
{
	if (p < 1)
	{
		printf("invalid deletion.. underflow...\n");
		exit(1);
	}

	LinkedListNode *curr = l->main_header->actual_list;
	while (p > 1 && curr != NULL)
	{
		if (curr->flag == mod_in_next)
		{
			curr = curr->mod.uf.mnext;
		}
		else
		{
			curr = curr->next;
		}
		p--;
	}
	return curr;
}

LinkedListNode* getNodeByvalue(int val,List *l)
{
	LinkedListNode *curr = l->main_header->actual_list;
	while (curr!=NULL && curr->val!=val)
	{
		if (curr->flag == mod_in_next)
		{
			curr = curr->mod.uf.mnext;
		}
		else
		{
			curr = curr->next;
		}
	}
	return curr;
}
void insertion(List *l,int posi,int val)
{
	
	if (l==NULL || l->main_header==NULL)
	{
		printf("damn it, insertion failed due to uninitialized list\n");
		exit(1);
	}
	LinkedListNode * n1=(LinkedListNode*)malloc(sizeof(LinkedListNode));
	n1->val=val;
	n1->flag=no_mod;
	LinkedListNode *temp;
	if(posi==1)
	{
		n1->next=l->main_header->actual_list;
		if (n1->next)
		{
			n1->next->back_ptr=n1;
		}
		if(!flag_delete)
		{
			globalVersion++;
			l->ver=globalVersion;
			flag_delete=1;
		}
		update(NULL,n1,l);
	}
	else
	{
		temp=getPosition(posi-1,l);
		if (temp==NULL)
		{
		printf("invalid insertion.. overflow...\n");
		exit(1);
		}
		if (temp->flag==mod_in_next)
		{
			n1->next=temp->mod.uf.mnext;
		}
		else
		n1->next=temp->next;

		if(n1->next)
		n1->next->back_ptr=n1;
		//n1->back_ptr=temp;
		if(!flag_delete)
		{
			globalVersion++;
			l->ver=globalVersion;
			flag_delete=1;
		}
		update(temp,n1,l);

	}


}
void deletion(List *l,int val)
{
	LinkedListNode * t=getNodeByvalue(val,l);
	if (t==NULL)
	{
		printf("invalid deletion.. underflow...\n");
		exit(1);
	}

	if (t->flag==mod_in_next)
	{	
		if(!flag_delete)
		{
			globalVersion++;
			l->ver=globalVersion;
			flag_delete=1;
		}
		update(t->back_ptr,t->mod.uf.mnext,l);
	}
	else 
	{
		if(!flag_delete)
		{
			globalVersion++;
			l->ver=globalVersion;
			flag_delete=1;
		}
		update(t->back_ptr,t->next,l);
	}

		

}

void initList(List *list)
{
	list->main_header=(HeaderListNode*)malloc(sizeof(HeaderListNode));
	list->main_header->highest_ver=globalVersion;
	list->main_header->lowest_ver=globalVersion;
	list->main_header->actual_list=NULL;
	list->main_header->next=NULL;
	list->ver=globalVersion;
}

void createNewHead(LinkedListNode *node,List *l)
{
	HeaderListNode *header= (HeaderListNode*)malloc(sizeof(HeaderListNode));
	header->next=l->main_header;
	header->actual_list=node;
	header->highest_ver=l->ver;
	header->lowest_ver=l->ver;
	l->main_header=header;
}

void copyLatestMods(LinkedListNode *t,LinkedListNode * temp)
{
	t->val=temp->val;
	t->next=temp->next;
	t->back_ptr=temp->back_ptr;
	t->flag=no_mod;
	if (temp->flag==mod_in_val)
	{
		t->val=temp->mod.uf.mval;
	}
	else if (temp->flag==mod_in_next)
	{
		t->next=temp->mod.uf.mnext;
	}

	
}

int printVersions(int pver,List *l)
{
	pver=pver+base_version;
	if (pver>globalVersion)
	{
		printf("this version not available yet...\n");
		return 1;
	}
	HeaderListNode *curr_header=l->main_header;
	while(curr_header!=NULL && pver<curr_header->lowest_ver)
	{
		curr_header=curr_header->next;
	}

	LinkedListNode * curr=NULL;
	if (curr_header)
	{
		curr=curr_header->actual_list;
	}

	while(curr!=NULL)
	{
		if (curr->flag!=mod_in_val || curr->mod.ver>pver)
		{
			printf("%d->",curr->val);
			if (curr->flag==mod_in_next && curr->mod.ver<=pver)
			{
				curr=curr->mod.uf.mnext;
			}
			else
				curr=curr->next;

		}
		else 
		{
			printf("%d->",curr->mod.uf.mval);
			curr=curr->next;
		}
		
	}

	printf("NULL\n");
	return 1;



}

void initGraph(Graph *g)
{
    int v = 20;
    printf("enter the no. of users for demo(>=2)\n");
    scanf("%d", &v);
    g->vertices = v;
    g->adjList = (List *)malloc(sizeof(List) * (v + 1));
    float p = 0.3 * log(v) / v;
    if (v <= 2)
    {
        printf("invalid numberOfNodes... terminating the program...\n");
        exit(1);
    }
    if (p >= .8)
    {
        p = .8;
    }
    //printf("prob:%f\n",p );
    Erdos_Renyi_randGen(v, p, "testingGen.txt");
    char *graphFile = "testingGen.txt";
    FILE *fp = fopen(graphFile, "r"); //contact-high-school-proj-graph
    if (fp == NULL)
    {
        printf("error retrieving FILE\n");
        exit(1);
    }
    createAdjList(g, fp);
	base_version=globalVersion;
}

void createAdjList(Graph *g,FILE *fp)
{
	//node **adjArray=(node**)malloc(sizeof(node*)*(v+1)); // one dummy node...
    //node *temp;
	int node1,node2,eweight;
    srand(time(0));
    active_convo=(int**)malloc(sizeof(int*)*g->vertices);
	for (int i = 1; i <= g->vertices; ++i)
	{
		initList(g->adjList+i);
        active_convo[i-1]=(int*)calloc(g->vertices,sizeof(int));
        active_convo[i-1][i-1]=-1;
	}

	
	while(fscanf(fp,"%d %d %d\n",&node1,&node2,&eweight)!=EOF)
	{
		/* temp=(node*)malloc(sizeof(node*));
		temp->val=node2;
		temp->next=adjArray[node1];
		adjArray[node1]=temp;
		temp=(node*)malloc(sizeof(node*));
		temp->val=node1;
		temp->next=adjArray[node2];
		adjArray[node2]=temp; */
        occupied_indexs++;
        active_convo[node1-1][node2-1]=1;
        active_convo[node2-1][node1-1]=1;
        insertion(g->adjList+node1,1,node2);
        insertion(g->adjList+node2,1,node1);
	}
	fclose(fp);
}
int startConvo(Graph *g)
{
	flag_delete=0;
	int resultantIndex = freeIndex(g->vertices);
	int j = resultantIndex % g->vertices;
	int i = (resultantIndex - j) / g->vertices;
	if (resultantIndex == -1 || active_convo[i][j] != 0)
	{
		printf("something is fucked up... check the code... resut: %d\n", resultantIndex);
		exit(1);
	}
	occupied_indexs++;
	active_convo[i][j] = 1;
	active_convo[j][i] = 1;
	insertion(g->adjList + i + 1, 1, j + 1);
	insertion(g->adjList + j + 1, 1, i + 1);
	printf("started convo between (%d,%d)\n",i+1,j+1);
	return 1;
}
int endConvo(Graph *g)
{
	int i;
	flag_delete=0;
	do
	{
		i = rand() % g->vertices;
	} while ((g->adjList + i + 1)->main_header->actual_list == NULL);
	int val = (g->adjList + i + 1)->main_header->actual_list->val;
	deletion(g->adjList + i + 1, val);
	deletion(g->adjList + val, i + 1);
	occupied_indexs--;
	active_convo[i][val - 1] = 0;
	active_convo[val - 1][i] = 0;
	printf("ended convo between (%d,%d)\n",i+1,val);
	return 1;
}
int freeIndex(int v)
{
    if ((v*v-v)/2 == occupied_indexs)
    {
        return -1;
    }
    
    int count=rand()%((v*v-v)/2 - occupied_indexs);
    int return_index=-1;
    for (int i = 0; i < v; i++)
    {
        for (int j = i+1; j < v && count!=-1; j++)
        {
            if(active_convo[i][j]==0)
            {
                count--;
                return_index=i*v+j;
            }
        }
        
    }
    return return_index;
    
}

int noOfConnects(Graph *g,int version,int userId)
{
	int count=0;
	version+=base_version;
	HeaderListNode *curr_header=(g->adjList+userId)->main_header;
	while(curr_header!=NULL && version<curr_header->lowest_ver)
	{
		curr_header=curr_header->next;
	}

	LinkedListNode * curr=NULL;
	if (curr_header)
	{
		curr=curr_header->actual_list;
	}

	while(curr!=NULL)
	{
		if (curr->flag!=mod_in_val || curr->mod.ver>version)
		{
			count++;
			if (curr->flag==mod_in_next && curr->mod.ver<=version)
			{
				curr=curr->mod.uf.mnext;
			}
			else
				curr=curr->next;

		}
		else 
		{
			count++;
			curr=curr->next;
		}
		
	}
	return count;

}

