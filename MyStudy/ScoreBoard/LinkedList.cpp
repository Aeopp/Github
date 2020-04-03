#pragma once
#include "LinkedList.h"

void LinkedList::DeleteAll() const
{
	Node* Target = Head->Next;

	while (Target && Target != Tail)
	{
		Node* NextTarget = Target->Next;
		Utility::SAFE_DELETE(Target);
		Target = NextTarget;
	};

}