#include <stdio.h>
#include <stdlib.h> 
#include "listunit_l1.h"

int proverka(char *data){
	int num = atoi(data);
	int res = num * num;
	printf("Result:%d\n",res);
	return 0;
}



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
	//disposeNodeL1(&node3); // возможно не правильно
	//deleteAfterNodeL1(node1); работает
	//disposeAfterNodeL1(node1); работает
	//disposeListL1(&head); работает
	
	listOutL1(head);
	
	int count = listCountL1(head);
	printf("count of Node:%d\n",count);
	
	printf("Processing list:\n");
	listActionL1(head,proverka);
	
	char result [100];
	char *delimiter = "=";
	char *mergedStr = listSumStr(result, sizeof(result),head,delimiter);
	printf("Merged String: %s\n",mergedStr);
	
	disposeListL1(&head);

	
  return 0;
}
