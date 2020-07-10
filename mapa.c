#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

typedef struct dataNode {
	char dataRef[10];
	int codReg;
	char informante[30];
	char desc[30];
	float qttProd;
}DataNode;

typedef struct node {
	DataNode *data;
	struct node* next;
}Node;

typedef struct list {
	Node *head;
	int size;
}List;


List* createList();

FILE* open(char fileName[]);

void read(FILE *arq, List* list);

void push(List *list, Node *no);

void showInfo(List *list);

int main(void){
	setlocale(LC_ALL, "Portuguese");
	char fileName[] = "csv_mapa.csv";
	FILE * csv = open(fileName);
	
	if(csv == NULL)
	{
		printf("Não foi possível abrir o arquivo especificado!");
		return 1;
	}
	
	List *lista = createList();
	
	
	read(csv, lista);
	showInfo(lista);
	
	free(lista);
	fclose(csv);
	return 0;
}

void read(FILE *arq, List* list){
	char parsedLine[1088];
	while(fgets(parsedLine, 1088, arq) != NULL)
	{

		Node* n = (Node*)malloc(sizeof(Node));
		DataNode *d = (DataNode*)malloc(sizeof(DataNode));
		char *rest;
		
		char *dr = strtok_r(parsedLine, ";", &rest);
		strcpy(d->dataRef, dr);
		
		char *cr = strtok_r(rest, ";",&rest);
		int crInt = atoi(cr);
		d->codReg = crInt;		
		
		char *inf = strtok_r(rest, ";",&rest);
		strcpy(d->informante, inf);
		
		char *desc = strtok_r(rest, ";",&rest);
		strcpy(d->desc, desc);
		
		char *qtt = strtok_r(rest, ";",&rest);
		float qttFloat = atof(qtt);
		d->qttProd = qttFloat;
		
		n->data = d;
		n->next = NULL;
		
		push(list, n);
			
	}
}

void showInfo(List *list)
{

	printf("Trabalho Mapa Yuri Barbosa Perira - RA:1869040-5\n");
	printf("Curso: BACHARELADO EM ENGENHARIA DE SOFTWARE\n");	
	printf("Dataset ");
	printf("A - Movimentação de derivados de petróleo, gás natural e biocombustíveis - Combustíveis de aviação \n\n");
	printf("Total de itens: %d \n\n", list->size);
	Node *head = list->head;
	while(head->next != NULL)
	{
		printf("Data de Referência    :%c%c%c%c/%c%c\n", head->data->dataRef[0],head->data->dataRef[1],head->data->dataRef[2],head->data->dataRef[3], head->data->dataRef[4],head->data->dataRef[5]);
		printf("Código Regulado       :%d\n", head->data->codReg);
		printf("Informante            :%s\n", head->data->informante);
		printf("Descrição do produto  :%s\n", head->data->desc);
		printf("Quantidade do produto :%.2f\n", head->data->qttProd);
		printf("\n\n");
		head = head->next;
	}
	
}

void push(List* list, Node *no)
{
	
	if(list->head == NULL)
	{
		list->head = no;
	}else{
	
		Node *aux = (Node*)malloc(sizeof(Node));
		aux = list->head;
	
		while(aux->next != NULL)
		{
			aux = aux->next;
		}
		aux->next = no;
	}
		
	list->size += 1;
}

List* createList()
{
	List* l = (List*)malloc(sizeof(List));
	l->head = NULL;
	l->size = 0;
	return l;
}

FILE* open(char fileName[])
{
	
	FILE *f = fopen(fileName, "r");
	return f;
}


