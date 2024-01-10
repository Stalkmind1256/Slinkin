#include <stdio.h>
#include <stdlib.h> 
#include "listunit_l2c.h"

int main() {
    pnodeL2C head = NULL;
  
    pnodeL2C node1 = createNodeL2C(10.5);
    addFirstNodeL2C(&head, node1);
  
    pnodeL2C node2 = createNodeL2C(20.5);
    addFirstNodeL2C(&head, node2);
  
    pnodeL2C node3 = createNodeL2C(30.5);
    addFirstNodeL2C(&head, node3);
  
    printf("Number of nodes in the list: %d\n", listCountL2C(head));
  
	//disposeNodeL2C(&node1);
	//disposeNodeL2C(&node2);
	//disposeNodeL2C(&node3);
  
		
    disposeListL2C(&head);
  
    return 0;
} 
