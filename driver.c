#include <stdio.h>
#include <string.h>
#include "user.h"


int main(void) {
	struct User * head=NULL;
	head = add(head, "rob");
	head = add(head, "hanif");
	head = add(head, "gahyun");
	head = add(head, "matt");
	head = add(head, "sumita");
	head = add(head, "james");
	verify(head);

	head = add(head, "Alice");
	head = add(head, "Bob");
	head = add(head, "Charlie");

	printf("\n--- Initial Verification ---\n");
	verify(head);

	printf("\n--- Executing Tamper Test ---\n");
	tamperUsername(head->next, "Eve");

	printf("\n--- Verification After Tampering ---\n");
	verify(head);
}