#include <stdio.h>
#include "listunit_l1.h"


int main()
{
	pnodeL1 head = NULL;
	
	pnodeL1 node1 = createNodeL1("11\n");
	pnodeL1 node2 = createNodeL1("22\n");
	pnodeL1 node3 = createNodeL1("33\n");
	pnodeL1 node4 = createNodeL1("44\n");

	addFirstNodeL1(&head,node1);
	addFirstNodeL1(&head,node2);
	addLastNodeL1(&head,node3);
	insertAfterNodeL1(node1,node4);
	disposeNodeL1(&node3); // возможно не правильно
	
	listOutL1(head);
	
	int count = listCountL1(head);
	printf("count of Node:%d\n",count);

	
/*	if(node != NULL){
		printf("Create Node: %s\n",node->data);
	}else{
		printf("Eror of create Node");
	}
*/	
	
  return 0;
}
