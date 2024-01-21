#include "listunit_l1.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//rfrfrrf
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
	p->pnext = *ph;
	*ph = p;
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
   if (pn != NULL && *pn != NULL) {
      free((*pn)->data);
      free(*pn);
      *pn = NULL;
   }
}

 pnodeL1 deleteAfterNodeL1(pnodeL1 pn)
 {
	 //pnodeL1 nodeTodelete = pn->pnext;
	// if(nodeTodelete != NULL){
		// pn->pnext = nodeTodelete->pnext;
		// free(nodeTodelete);
		 //disposeNodeL1(&nodeTodelete);		 
 // return pn->pnext;
	 if(pn != NULL && pn->pnext != NULL){
		 pnodeL1 nodeTodelete = pn->pnext;
		 pn->pnext = nodeTodelete->pnext;
		 nodeTodelete->pnext = NULL;
		 return nodeTodelete;
		 //disposeNodeL1(&nodeTodelete);
		 }
  
  return  NULL;
 }

 void disposeAfterNodeL1(pnodeL1 pn)
 {
	if (pn != NULL && pn->pnext != NULL) {
        pnodeL1 nodeToDelete = pn->pnext;
        pn->pnext = nodeToDelete->pnext;
        disposeNodeL1(&nodeToDelete);
       
    }
}
 void disposeListL1(pnodeL1 *ph) {
    while (*ph != NULL) {
        pnodeL1 nodeToDelete = *ph;
        *ph = (*ph)->pnext;
        free(nodeToDelete->data);
        free(nodeToDelete);
    }
    *ph = NULL;
}
void listActionL1(pnodeL1 ph, listfunc func) {
    pnodeL1 current = ph;
    int index = 0;
    while (current != NULL) {
        int result = func(current->data);
        printf("Result function for Node %d: %d\n", index, result);
        current = current->pnext;
        index++;
    }
}

 void listOutL1(pnodeL1 ph) //output
 {
	 pnodeL1 current = ph;
	 while(current != NULL){
		 printf("%s ",current->data);
		 current = current->pnext;
		 }
		 printf("\n");
	 }

 int listCountL1(pnodeL1 ph) // count
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
