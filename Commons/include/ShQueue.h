#ifndef SH_QUEUE_H
#define SH_QUEUE_H

#include <Commons.h>

namespace Shady
{
	template<typename T>
	struct QNode
	{
		T elem;
		QNode* next;
		QNode* back;
		QNode() = default;
		QNode(T e, QNode<T>* n = nullptr, QNode<T>* b = nullptr): elem{e}, next{n}, back{b} {}
	};
	template<typename T>
	class Queue
	{
		typedef QNode<T> Node;

		Node* mTail;
		Node* mHead;
		u32 mSize;


	public:
		Queue(): mTail(nullptr), mHead(nullptr), mSize(0) {}
		~Queue()
		{
			Node* last = mTail;
			while(last)
			{
				Node* temp = last;
				last = last->next;
				delete temp;
			}
		} 

		void push(T elem)
		{
			if(!mTail)
			{
				mTail = new Node(elem);
				mHead = mTail;
			}
			else
			{
				Node* temp = new Node(elem, mTail);
				mTail->back = temp;
				mTail = temp;
			}
			mSize++;
		}

		T pop()
		{
			SH_ASSERT(mSize > 0);

			T result = mHead->elem;
			
			Node* temp = mHead; 
			mHead = temp->back;
			if(mHead)
			{
				mHead->next = nullptr;	
			}
			else
			{
				mTail = mHead;
			} 
			delete temp;

			mSize--;
			return result;
		}

		u32 size() { return mSize;}
	};
}

#endif