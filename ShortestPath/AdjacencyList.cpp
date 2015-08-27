/***************************************
Author: YinWen
email: yinwenatbit@163.com
date: 2015/8/23
description:ʹ���ڽӱ�ʵ��ͼ�����ݽṹ
			ʹ���˿��Ŷ�ַ�Ĺ�ϣ��
********************************************/

#include "AdjacencyList.h"
#include <cstdlib>
#include <iostream>
#include "queue.h"

/*��ʼ��ͼ*/
Graph intializeGraph(int VertexNum)
{
	return initializeTable(VertexNum);
}

/*���붥�㣬ֱ�ӵ��ù�ϣ��Ĳ����ֵ*/
void insertVertex(VertexType vertex, Graph G)
{
	insertKey(vertex, G);
	G->vertex++;
}

/*����ߣ���Ҫ�Ƚ����жϱߵ����������Ƿ���ڣ����������Ȳ��붥��*/
void insertEdge(VertexType vertex1, VertexType vertex2, WeightType weight, Graph G)
{
	Position P1, P2;
	P1 = FindKey(vertex1, G);
	P2 = FindKey(vertex2, G);
	
	if(G->TheCells[P2].Info != Legitimate)
		insertVertex(vertex2, G);
	if(G->TheCells[P1].Info != Legitimate)
		insertVertex(vertex1, G);
	
	/*�����µı�*/
	Edge newEdge = (Edge)malloc(sizeof(EdgeNode));
	newEdge->vertexIndex = P2;
	newEdge->weight = weight;
	newEdge->next = G->TheCells[P1].next;
	G->TheCells[P1].next = newEdge;
	/*������һ*/
	G->edge++;
}

/*Ѱ�Ҷ�������*/
Position findVertex(VertexType vertex, Graph G)
{
	return FindKey(vertex, G);
}


/*�Ƴ��ߣ���ȷ�϶������*/
void removeEdge(VertexType vertex1, VertexType vertex2, Graph G)
{
	Position P1, P2;
	P1 = FindKey(vertex1, G);
	P2 = FindKey(vertex2, G);
	
	if(G->TheCells[P2].Info != Legitimate && G->TheCells[P1].Info == Legitimate)
	{
		fprintf(stderr, "Edge not exist\n");
		return;
	}

	VertexNode * V = &G->TheCells[P1];

	Edge parent = V->next;

	/*�жϸñ��Ƿ��ǵ�һ����*/
	if(parent->vertexIndex == P2)
	{
		V->next = parent->next;
		free(parent);
	}
	else
	{
		Edge temp;

		while(parent->next->vertexIndex != P2)
			parent = parent->next;

		temp = parent->next;
		parent->next = temp->next;
		free(temp);
	}
}

/*ɾ����*/
void DestroyEdge(Edge E)
{
	Edge temp;	
	while(E != NULL)
	{
		temp = E->next;
		free(E);
		E = temp;
	}
}

/*ɾ��ͼ����Ҫ��ɾ���ߣ��ٵ���ɾ����ϣ��*/
void  DestroyGraph(Graph G)
{
	for(int i =0; i<G->TableSize; i++)
		if(G->TheCells[i].Info == Legitimate &&G->TheCells[i].next != NULL)
			DestroyEdge(G->TheCells[i].next);

	DestroyTable(G);
}







/*��ӡ��*/
void PrintEdge(VertexNode * V, Graph G)
{
	Edge edgeNext;
	edgeNext = V->next;
	while(edgeNext != NULL)
	{
		printf("Edge: %s -->  ", V->vertexName);
		Index P2 = edgeNext->vertexIndex;
		printf("%s  ",G->TheCells[P2].vertexName);
		printf("weight: %d\n",edgeNext->weight);
		edgeNext = edgeNext->next;
	}
}

/*��ӡͼ*/
void PrintGraph(Graph G)
{
	for(int i =0; i<G->TableSize; i++)
		if(G->TheCells[i].Info == Legitimate)
			PrintEdge(&G->TheCells[i], G);
}





