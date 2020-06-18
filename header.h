#include<stdio.h>
#include<stdlib.h>
struct LinkedListNode
{
	//empheral part...
	int val;
	struct LinkedListNode * next;
	// partial persitance..
	struct LinkedListNode * back_ptr;
	int flag; // 1 means change in val, 2 means change in nextPtr,0 means no mod;
	struct Mods
	{
		int ver;
		union fvalue
		{
			int mval;
			struct LinkedListNode * mnext;
		} uf;

	} mod;
};

typedef struct  LinkedListNode LinkedListNode;

struct HeaderListNode
{
	int highest_ver;
	int lowest_ver;
	LinkedListNode * actual_list;
	struct HeaderListNode *next; 

};

typedef struct HeaderListNode HeaderListNode;

struct List
{
	HeaderListNode * main_header;
	int ver;
};
typedef struct List List;
struct Graph
{
    List* adjList;
    int vertices;
};
typedef struct Graph Graph; 
void initGraph(Graph *g);
void Erdos_Renyi_randGen(int v, float p, char* outputFile);
void createAdjList(Graph *g,FILE *fp);
int startConvo();
int endConvo();
int freeIndex(int v);
int noOfConnects(Graph *g,int version,int userId);
void modify(int posi, List *l,int val);
struct LinkedListNode* update(LinkedListNode* node1,LinkedListNode* node_next, List* l);
LinkedListNode* getPosition(int p,List *l);
LinkedListNode* getNodeByvalue(int val,List *l);
void insertion(List *l,int posi,int val);
void deletion(List *l,int posi);
void initList(List*);
void createNewHead(LinkedListNode *node,List *l);
void copyLatestMods(LinkedListNode *t,LinkedListNode * temp);
int printVersions(int ver,List *l);
