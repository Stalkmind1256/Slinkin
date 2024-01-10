#include <stdio.h>
#include <stdlib.h> 
#include "listunit_l1.h"

int proverka(char *data) {
    int num = atoi(data);
    int res = num * num;
    //printf("Result: %d\n", res);
    return res;
}


int main()
{
	pnodeL1 head = NULL;
	
	pnodeL1 node1 = createNodeL1("11");
	addFirstNodeL1(&head,node1);
	pnodeL1 node2 = createNodeL1("22");
	addLastNodeL1(&head,node2);
	pnodeL1 node3 = createNodeL1("33");
	addLastNodeL1(&head,node3);
	pnodeL1 node4 = createNodeL1("44");
	insertAfterNodeL1(node2,node4);
	
	//deleteAfterNodeL1(head);
	addLastNodeL1(&head, deleteAfterNodeL1(head));
	

	//disposeAfterNodeL1(head); //работает
	
	//disposeNodeL1(&node3);
	/*if(node3 == NULL){
		printf("free node\n");
		}else{
			printf("not free node\n");
			}
	*/		
	//disposeListL1(&head);
	
	
	
	listOutL1(head);
	
	int count = listCountL1(head);
	printf("count of Node:%d\n",count);
	
	printf("Processing list:\n");
	listActionL1(head,proverka);
	
	//char result [100];
	//char *delimiter = "=";
	//char *mergedStr = listSumStr(result, sizeof(result),head,delimiter);
	//printf("Merged String: %s\n",mergedStr);
	
	disposeListL1(&head);
	
  return 0;
}
