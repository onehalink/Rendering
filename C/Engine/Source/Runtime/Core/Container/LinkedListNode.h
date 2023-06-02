#pragma once

#include "../System/Allocator.h"



typedef struct LinkedListNode LinkedListNode;

struct LinkedListNode
{
	LinkedListNode*	next;
	Void*			dataArea;
};


struct FLinkedListNode
{
	LinkedListNode*(*Construct)(SizeType datatypeSize);
	Void(*Destruct)(LinkedListNode* instance);
};

extern ENGINE_API struct FLinkedListNode FLinkedListNode;