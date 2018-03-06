#ifndef SH_LIST_H
#define SH_LIST_H

#include "ShIterator.h"
#include "ShAssert.h"
#include <new>
namespace Shady
{
	template<typename T>
	struct LNode
	{
		T elem;
		LNode<T>* next;
		LNode<T>* back;
		LNode()
		{
			next = 0;
			back = 0;
		}
		LNode(const T& e, LNode<T>* n = 0, LNode<T>* b = 0)
		{
			elem = e;
			next = n;
			back = b;
		}
		LNode(const LNode<T>& other)
		{
			elem = other.elem;
			next = other.next; 
			back = other.back;
		}

	};

	//This is implemented as a double linked list.
	template<typename T>
	class List
	{
		typedef LNode<T> Node;
		template <typename T>
		struct ListIterator 
		{
			friend List;
			List<T>* list;
			Node* node;
			IteratorPosition position;
			ListIterator(List<T>* l, IteratorPosition pos = IteratorPosition::BEGIN): 
						list{l}, node{nullptr}, position{pos}
			{
				switch(pos)
				{
					case IteratorPosition::BEGIN:
					{
						node = list->mHead;
					}break;
					case IteratorPosition::END:
					{
						node = 0;
					}break;
					case IteratorPosition::RBEGIN:
					{
						node = list->mTail;
					}break;
					case IteratorPosition::REND:
					{
						node = 0;
					}break;
				}
			}

			b8 IsReverse() {return (position == IteratorPosition::RBEGIN) || (position == IteratorPosition::REND);}
			T& operator*()
			{
				SH_ASSERT(node);
				return node->elem;
			}

			ListIterator& operator=(const ListIterator& other)
			{
				list = other.list;
				node = other.node;
				return *this;
			}

			ListIterator operator+(u32 offset)
			{
				ListIterator result = *this;
				if(IsReverse())
				{
					while(offset--)
					{
						if(result.node) result.node = result.node->back;
						if(!result.node) break;
					}
				}
				else
				{
					while(offset--)
					{
						if(result.node) result.node = result.node->next;
						if(!result.node) break;
					}
				}
				return result;
			}
			ListIterator operator-(u32 offset)
			{
				ListIterator result = *this;
				if(IsReverse())
				{
					while(offset--)
					{
						if(result.node) result.node = result.node->next;
						if(!result.node) break;
					}
				}
				else
				{
					while(offset--)
					{
						if(result.node) result.node = result.node->back;
						if(!result.node) break;
					}
				}
				return result;	
			}
			ListIterator& operator+=(u32 offset)
			{
				if(IsReverse())
				{
					while(offset--)
					{
						if(node) node = node->back;
						if(!node) break;
					}
				}
				else
				{
					while(offset--)
					{
						if(node) node = node->next;
						if(!node) break;
					}
				}
				return *this;	
			}
			ListIterator& operator-=(u32 offset) 
			{
				if(IsReverse())
				{
					while(offset--)
					{
						if(node) node = node->next;
						if(!node) break;
					}
				}
				else
				{
					while(offset--)
					{
						if(node) node = node->back;
						if(!node) break;
					}
				}
				return *this;	
			}
			ListIterator operator++() 
			{
				ListIterator temp = *this;
				if(IsReverse())
				{
					if(node) node = node->back;
				}
				else
				{
					if(node) node = node->next;
				}
				return temp;
			}
			ListIterator operator++(int)
			{
				if(IsReverse())
				{
					if(node) node = node->back;
				}
				else
				{
					if(node) node = node->next;
				}
				return *this;
			}
			ListIterator operator--()
			{
				ListIterator temp = *this;
				if(IsReverse())
				{
					if(temp.node) temp.node = temp.node->next;
				}
				else
				{
					if(temp.node) temp.node = temp.node->back;
				}
				return temp;	
			}
			ListIterator operator--(int)
			{
				if(IsReverse())
				{
					if(node) node = node->back;
				}
				else
				{
					if(node) node = node->next;
				}
				return *this;	
			}
			b8 operator==(const ListIterator& other)
			{
				return ((list == other.list) && (node == other.node));
			}
			b8 operator!=(const ListIterator& other)
			{
				return ((list != other.list) || (node != other.node));
			}

		};
	protected:
		
		Node* mTail;
		Node* mHead;
		u32 mSize;

	public:
		List()
		{
			mHead = 0;
			mTail = 0;
			mSize = 0;
		}
		List(const List<T>& other)
		{
			mHead = 0;
			mTail = 0;
			mSize = 0;
			for(T& elem : other)
			{
				AddFront(elem);
			}
		}
		List<T>& operator=(const List<T>& other)
		{
			Clear();
			for(T& elem: other)
			{
				AddBack(elem);
			}
			return *this;	
		}
		List(List<T>&& other)
		{
			mTail = other.mTail;
			mHead = other.mHead;
			mSize = other.mSize;

			other.mTail = 0;
			other.mHead = 0;
		}
		~List() 
		{
			Node* last = mTail;
			while(last)
			{
				Node* temp = last;
				last = last->next;
				delete temp;
			}
		}

		void AddBack(const T& elem)
		{
			if(!mTail)
			{
				mTail = new Node(elem);
				mHead = mTail;
			}
			else
			{
				Node* temp = new Node(elem, 0, mTail);
				if(mTail != mHead)
				{
					mTail->next = temp;
				}
				else
				{
					mHead->next = temp;
				}
				mTail = temp;
			}
			mSize++;
		}

		void AddFront(const T& elem)
		{
			if(!mHead)
			{
				mHead = new Node(elem);
				mTail = mHead;
			}
			else
			{
				Node* temp = new Node(elem, mHead, 0);
				if(mHead != mTail)
				{
					mHead->back = temp;	
				}
				else
				{
					mTail->back = temp;
				}
				mHead = temp;
			}
			mSize++;
		}

		void AddAfter(const T& elemBefore, const T& elem, b8 insAfterMulElems = false)
		{
			Node* test = mHead;
			while(test)
			{
				if(test->elem == elemBefore) // insert here
				{
					Node* nextNode = test->next;
					Node* temp = new Node(elem, nextNode, test);
					if(nextNode) nextNode->back = temp;
					test->next = temp;
					mSize++;
					if(test == mTail) mTail = temp;
					test = test->next;
					if(!insAfterMulElems) break;
				}
				if(test) test = test->next;
			}
		}

		void AddBefore(const T& elemBefore, const T& elem, b8 insAfterMulElems = false)
		{
			Node* test = mTail;
			while(test)
			{
				if(test->elem == elemBefore) // insert here
				{
					Node* lastNode = test->back;
					Node* temp = new Node(elem, test, lastNode);
					if(lastNode) lastNode->next = temp;
					test->back = temp;
					if(test == mHead) mHead = temp;
					mSize++;
					test = test->back;
					if(!insAfterMulElems) break;
				}
				if(test) test = test->back;
			}
		}
		//--------------Emplace----------------------//

		template<typename ...Args>
		void PutBack(Args... args)
		{
			if(!mTail)
			{
				mTail = new Node();
				new(&mTail->elem) T(args...);
				mHead = mTail;
			}
			else
			{
				Node* temp = new Node();
				new(&temp->elem) T(args...);
				temp->back = mTail;

				if(mTail != mHead)
				{
					mTail->next = temp;
				}
				else
				{
					mHead->next = temp;
				}
				mTail = temp;
			}
			mSize++;
		}

		template<typename ...Args>
		void PutFront(Args... args)
		{
			if(!mHead)
			{
				mHead = new Node();
				new(&mHead->elem) T(args...);
				mTail = mHead;
			}
			else
			{
				Node* temp = new Node();
				new(&temp->elem) T(args...);
				temp->next = mHead;

				if(mHead != mTail)
				{
					mHead->back = temp;	
				}
				else
				{
					mTail->back = temp;
				}
				mHead = temp;
			}
			mSize++;
		}

		//-------------------------------------------//

		T PopBack()
		{
			SH_ASSERT(mSize > 0);

			T result = mTail->elem;
			if(mTail != mHead)
			{
				Node* temp = mTail;
				mTail = temp->back;
				if(mTail) mTail->next = 0;	
				delete temp;
			}
			else
			{
				delete mHead;
				mHead = mTail = 0;
			}
			mSize--;
			return result;
		}

		T PopFront()
		{
			SH_ASSERT(mSize > 0);
			
			T result = mHead->elem;
			if(mHead != mTail)
			{
				Node* temp = mHead; 
				mHead = temp->next;
				if(mHead) mHead->back = 0;
				delete temp;
			}
			else
			{
				delete mHead;
				mHead = mTail = 0;
			}
			mSize--;
			return result;
		}

		T& PeekBack()
		{
			SH_ASSERT(mSize > 0);
			return mTail->elem;	
		}

		T& PeekFront()
		{
			SH_ASSERT(mSize > 0);
			return mHead->elem;	
		}

		b8 Remove(const T& elem)
		{
			b8 result = false;
			Node* temp = mHead;
			while(temp)
			{
				Node* tempToDel = temp;

				if(temp->elem == elem)
				{
					if(temp == mHead)
					{
						if(mHead == mTail)
						{
							mHead = mTail = 0;
							temp = 0;
						}
						else
						{
							mHead = mHead->next;
							if(mHead)
							{
								mHead->back = 0;	
							}
							temp = temp->next;	
						}
					}
					else if(temp == mTail)
					{
						mTail = mTail->back;
						if(mTail)
						{
							mTail->next = 0;
						}
						temp = temp->next;	
					}
					else
					{
						if(temp->back) 
						{
							temp->back->next = temp->next;
						}
						if(temp->next)
						{
							temp->next->back = temp->back;
						}
						temp = temp->next;
					}
					result = true;
					
					delete tempToDel;
					mSize--;
				}// If elem found
				else
				{
					temp = temp->next;	
				} 
			} // while
			return result;
		}

		List<T>& Clear()
		{
			Node* temp = mHead;
			if(temp == mTail)
			{
				delete temp;
			}
			else
			{
				while(temp)
				{
					Node* nextTemp = temp->next;
					delete temp;
					temp = nextTemp; 
				}
			}
			mHead = 0;
			mTail = 0;
			mSize = 0;
			return *this;
		}

		void Swap(List<T>& other)
		{
			Node* tHead = mHead;
			Node* tTail = mTail;
			u32 tSize = mSize;

			mHead = other.mHead;
			mTail = other.mTail;
			mSize = other.mSize;

			other.mHead = tHead;
			other.mTail = tTail;
			other.mSize = tSize;
		}

		ListIterator<T> begin()
		{
			return ListIterator<T>(const_cast<List<T>*>(this), IteratorPosition::BEGIN);
		}

		ListIterator<T> end() 
		{
			return ListIterator<T>(const_cast<List<T>*>(this), IteratorPosition::END);
		}
		const ListIterator<T> begin() const 
		{
			return ListIterator<T>(const_cast<List<T>*>(this), IteratorPosition::BEGIN);
		}

		const ListIterator<T> end() const
		{
			return ListIterator<T>(const_cast<List<T>*>(this), IteratorPosition::END);
		}

		ListIterator<T> rbegin() 
		{
			return ListIterator<T>(const_cast<List<T>*>(this), IteratorPosition::RBEGIN);
		}

		ListIterator<T> rend() 
		{
			return ListIterator<T>(const_cast<List<T>*>(this), IteratorPosition::REND);
		}
		const ListIterator<T> rbegin() const 
		{
			return ListIterator<T>(const_cast<List<T>*>(this), IteratorPosition::RBEGIN);
		}

		const ListIterator<T> rend() const
		{
			return ListIterator<T>(const_cast<List<T>*>(this), IteratorPosition::REND);
		}

	};
}

#endif