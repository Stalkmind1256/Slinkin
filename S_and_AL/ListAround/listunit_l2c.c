#include "listunit_l2c.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"

pnodeL2C createNodeL2C(double data){
	pnodeL2C newNode = (pnodeL2C)malloc(sizeof(tnodeL2C));
	if(newNode != NULL){
		newNode ->data = data;
		newNode ->pprev = NULL;
		newNode ->pnext = NULL;
		
		}
		return newNode;
	} 

pnodeL2C addFirstNodeL2C(pnodeL2C *ph, pnodeL2C p) {
    if (*ph == NULL) {
        *ph = p;
        p->pprev = p;
        p->pnext = p;
    }
    else {
        p->pprev = (*ph)->pprev;
        p->pnext = *ph;
        (*ph)->pprev->pnext = p;
        (*ph)->pprev = p;
        *ph = p;
    }
    return p;
}



int listCountL2C(pnodeL2C ph) {
    if (ph == NULL) {
        return 0;
    }
    int count = 0;
    pnodeL2C current = ph;
    do {
        count++;
        current = current->pnext;
    } while (current != ph);
    return count;
}


void disposeNodeL2C(pnodeL2C *pn) {
    if (*pn != NULL) {
        free(*pn);
        *pn = NULL;
    }
}

void disposeListL2C(pnodeL2C *ph) {
    pnodeL2C current = *ph;
    while (current != NULL) {
        pnodeL2C temp = current;
        current = current->pnext;
        disposeNodeL2C(&temp);
    }
    *ph = NULL;
}
