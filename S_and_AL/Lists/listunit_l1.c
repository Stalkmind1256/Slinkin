#include "listunit_l1.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


  pnodeL1 createNodeL1(char *data) {
  pnodeL1 newNode = (pnodeL1)malloc(sizeof(tnodeL1));
  if (newNode != NULL) {
    newNode->data = (char*)malloc(strlen(data) + 1);
    strcpy(newNode->data, data);
    newNode->pnext = NULL;
  }
  return newNode;
}

 pnodeL1 addFirstNodeL1(pnodeL1 *ph, pnodeL1 p)
 {
	if(*ph == NULL){
		*ph = p;
	}else{
		p->pnext= *ph;
		*ph = p;	
	}
  return p;
 }

 pnodeL1 addLastNodeL1(pnodeL1 *ph, pnodeL1 p)
 {
	 if(*ph == NULL){
		 *ph = p;
	 }else{
		pnodeL1 current = *ph;
		while(current->pnext != NULL){
			current = current->pnext;
		}
		current->pnext = p;
	}
  return p;
 }

 pnodeL1 insertAfterNodeL1(pnodeL1 pn, pnodeL1 p)
 {
	 p->pnext = pn->pnext;
	 pn->pnext = p;
  return p;
 }

 void disposeNodeL1(pnodeL1 *pn)
 {
	 free((*pn)->data);
	 free(*pn);
	 *pn = NULL;
 }

 pnodeL1 deleteAfterNodeL1(pnodeL1 pn)
 {
	 pnodeL1 nodeTodelete = pn->pnext;
	 if(nodeTodelete != NULL){
		 pn->pnext = nodeTodelete->pnext;
		 disposeNodeL1(&nodeTodelete);
		 }
  return pn->pnext;
 }

 void disposeAfterNodeL1(pnodeL1 pn)
 {
	pnodeL1 nodeToDelete = pn->pnext;
		while (nodeToDelete != NULL){
			pn->pnext = nodeToDelete->pnext;
			disposeNodeL1(&nodeToDelete);
			nodeToDelete = pn->pnext;
		}
}
 void disposeListL1(pnodeL1 *ph)
 {
	disposeAfterNodeL1(*ph);
	disposeNodeL1(ph);
	 }

 void listActionL1(pnodeL1 ph, listfunc func) /// Что с ней делать?
 {
	 pnodeL1 current = ph;
	 while(current != NULL){
		int result =  func(current->data);
		printf("Result function for Node%d\n",result);
		 current = current->pnext;
		 }
	 }

 void listOutL1(pnodeL1 ph) //вывод узлов
 {
	 pnodeL1 current = ph;
	 while(current != NULL){
		 printf("%s",current->data);
		 current = current->pnext;
		 }
		 printf("\n");
	 }

 int listCountL1(pnodeL1 ph) // Количество узлов
 {
	 int count = 0;
	 pnodeL1 current = ph;
	 while(current != NULL){
		 count++;
		 current = current->pnext;
		 }
		 return count;
	 }

char *listSumStr(char *dest, int maxsize, pnodeL1 ph, char *delimiter)
{
    dest[0] = '\0';
    pnodeL1 current = ph;

    while (current != NULL) {
        int currentLen = strlen(current->data);
        int destLen = strlen(dest);

        if (destLen + currentLen + strlen(delimiter) < maxsize) {
            strcat(dest, current->data);
            
            if (current->pnext != NULL) {
                strcat(dest, delimiter);
            }
        } else {
            break;
        }
        
        current = current->pnext;
    }

    return dest;
}
