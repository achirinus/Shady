#ifndef SH_QUEUE_H
#define SH_QUEUE_H

#include <Commons.h>
#include "ShIterator.h"

namespace Shady
{
	template<typename T>
	struct QNode
	{
		T elem;
		QNode* front;
		QNode* back;
		QNode() = default;
		QNode(const T& e, QNode<T>* b = nullptr, QNode<T>* f = nullptr): elem{e}, front{f}, back{b} {}
	};
	template<typename T>
	class Queue
	{
		typedef QNode<T> Node;

		Node* mTail;
		Node* mHead;
		u32 mSize;
	public:
		template <typename T> struct QueueIterator;
		
		Queue(): mTail(nullptr), mHead(nullptr), mSize(0) {}

		Queue(const Queue<T>& Other): Queue()
		{
			for (T& el: Other)
			{
				Push(el);
			}
		}

		Queue(Queue<T>&& Other)
		{
			mSize = Other.mSize;
			mTail = Other.mTail;
			mHead = Other.mHead;

			Other.mHead = 0;
			Other.mTail = 0;
			Other.mSize = 0;
		}

		Queue<T>& operator=(Queue<T>&& Other)
		{
			mSize = Other.mSize;
			mTail = Other.mTail;
			mHead = Other.mHead;

			Other.mHead = 0;
			Other.mTail = 0;
			Other.mSize = 0;
			return *this;
		}

		Queue<T>& operator=(const Queue<T>& Other) 
		{
			Clear();
			for (T& el : Other)
			{
				Push(el);
			}
			return *this;
		}

		~Queue()
		{
			Clear();
		} 

		void Push(const T& elem)
		{
			if(!mTail)
			{
				mTail = new Node(elem);
				mHead = mTail;
			}
			else
			{
				if (mHead == mTail)
				{
					Node* temp = new Node(elem, mTail);
					mTail->front = temp;
					mHead = temp;
				}
				else
				{
					Node* temp = new Node(elem, mHead);
					mHead->front = temp;
					mHead = temp;
				}
			}
			mSize++;
		}

		T Pop()
		{
			SH_ASSERT(mSize > 0);

			T result = mTail->elem;
			
			Node* temp = mTail; 
			mTail = temp->front;
			if(mTail)
			{
				mTail->back = nullptr;
			}
			else
			{
				mHead = mTail;
			} 
			delete temp;

			mSize--;
			return result;
		}

		u32 Size() const { return mSize;}

		void Clear()
		{
			Node* last = mTail;
			while (last)
			{
				Node* temp = last;
				last = last->front;
				delete temp;
			}
		}

		QueueIterator<T> begin()
		{
			return QueueIterator<T>(this, IteratorPosition::BEGIN);
		}

		QueueIterator<T> end()
		{
			return QueueIterator<T>(this, IteratorPosition::END);
		}




		//Iterator - Begin//////////////////////////////////////////////////////////////////////////
		template <typename T>
		struct QueueIterator
		{
			friend Queue;
			Queue<T>* que;
			Node* node;
			IteratorPosition position;
			QueueIterator(Queue<T>* q, IteratorPosition pos = IteratorPosition::BEGIN) :
				que{ q }, node{ nullptr }, position{ pos }
			{
				switch (pos)
				{
				case IteratorPosition::BEGIN:
				{
					node = que->mHead;
				}break;
				case IteratorPosition::END:
				{
					node = 0;
				}break;
				case IteratorPosition::RBEGIN:
				{
					node = que->mTail;
				}break;
				case IteratorPosition::REND:
				{
					node = 0;
				}break;
				}
			}

			b8 IsReverse() { return (position == IteratorPosition::RBEGIN) || (position == IteratorPosition::REND); }
			T& operator*()
			{
				SH_ASSERT(node);
				return node->elem;
			}

			QueueIterator& operator=(const QueueIterator& other)
			{
				que = other.que;
				node = other.node;
				return *this;
			}

			QueueIterator operator+(u32 offset)
			{
				QueueIterator result = *this;

				while (offset--)
				{
					if (IsReverse())
					{
						if (result.node) result.node = result.node->front;
					}
					else
					{
						if (result.node) result.node = result.node->back;
					}
					if (!result.node) break;
				}

				return result;
			}
			QueueIterator operator-(u32 offset)
			{
				QueueIterator result = *this;
				while (offset--)
				{
					if (IsReverse())
					{
						if (result.node) result.node = result.node->back;
					}
					else
					{
						if (result.node) result.node = result.node->front;
					}
					if (!result.node) break;
				}

				return result;
			}
			QueueIterator& operator+=(u32 offset)
			{
				while (offset--)
				{
					if (IsReverse())
					{
						if (node) node = node->front;
					}
					else
					{
						if (node) node = node->back;
					}
					if (!node) break;
				}

				return *this;
			}
			QueueIterator& operator-=(u32 offset)
			{
				while (offset--)
				{
					if (IsReverse())
					{
						if (node) node = node->back;
					}
					else
					{
						if (node) node = node->front;
					}
					if (!node) break;
				}

				return *this;
			}
			QueueIterator operator++()
			{
				QueueIterator temp = *this;
				if (IsReverse())
				{
					if (node) node = node->front;
				}
				else
				{
					if (node) node = node->back;
				}
				return temp;
			}
			QueueIterator operator++(int)
			{
				if (IsReverse())
				{
					if (node) node = node->front;
				}
				else
				{
					if (node) node = node->back;
				}
				return *this;
			}
			QueueIterator operator--()
			{
				QueueIterator temp = *this;
				if (IsReverse())
				{
					if (temp.node) temp.node = temp.node->back;
				}
				else
				{
					if (temp.node) temp.node = temp.node->front;
				}
				return temp;
			}
			QueueIterator operator--(int)
			{
				if (IsReverse())
				{
					if (node) node = node->back;
				}
				else
				{
					if (node) node = node->front;
				}
				return *this;
			}
			b8 operator==(const QueueIterator& other)
			{
				return ((que == other.que) && (node == other.node));
			}
			b8 operator!=(const QueueIterator& other)
			{
				return ((que != other.que) || (node != other.node));
			}

		};

		//Iterator - End//////////////////////////////////////////////////////////////////////////
		
	};
}

#endif