#ifndef SH_LIST_H
#define SH_LIST_H

#include "ShIterator.h"

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

		template<typename ...Args>
		LNode(LNode<T>* n, LNode<T>* b , Args... vArgs): 
		{
			next = n;
			back = b;
			new(elem) T(vArgs...);
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
		struct ListIterator : public Shady::Iterator<ListIterator<T>, T>
		{
			friend List;
			List<T>* list;
			Node* node;
			ListIterator(List<T>* l, IteratorPosition pos = IteratorPosition::BEGIN): list{l}
			{
				switch(pos)
				{
					case IteratorPosition::BEGIN:
					{
						node = list->mTail;
					}break;
					case IteratorPosition::END:
					{
						node = 0;
					}break;
				}
			}


			virtual T& operator*()
			{
				SH_ASSERT(node);
				return node->elem;
			}

			virtual ListIterator& operator=(const ListIterator& other)
			{
				list = other.list;
				node = other.node;
				return *this;
			}

			virtual ListIterator operator+(u32 offset)
			{
				SH_ASSERT(offset >= 0); //TODO maybe allow negative offsets
				ListIterator result = *this;
				while(offset--)
				{
					if(result.node) result.node = result.node->next;
					if(!result.node) break;
				}
				return result;
			}
			virtual ListIterator operator-(u32 offset)
			{
				SH_ASSERT(offset >= 0); //TODO maybe allow negative offsets
				ListIterator result = *this;
				while(offset--)
				{
					if(result.node) result.node = result.node->back;
					if(!result.node) break;
				}
				return result;	
			}
			virtual ListIterator& operator+=(u32 offset)
			{
				SH_ASSERT(offset >= 0); //TODO maybe allow negative offsets
				while(offset--)
				{
					if(node) node = node->next;
					if(!node) break;
				}
				return *this;	
			}
			virtual ListIterator& operator-=(u32 offset) 
			{
				SH_ASSERT(offset >= 0); //TODO maybe allow negative offsets
				while(offset--)
				{
					if(node) node = node->back;
					if(!node) break;
				}
				return *this;	
			}
			virtual ListIterator operator++() 
			{
				ListIterator temp = *this;
				if(node) node = node->next;
				return temp;
			}
			virtual ListIterator operator++(int)
			{
				if(node) node = node->next;
				return *this;
			}
			virtual ListIterator operator--()
			{
				ListIterator temp = *this;
				if(node) node = node->back;
				return temp;	
			}
			virtual ListIterator operator--(int)
			{
				if(node) node = node->back;
				return *this;	
			}
			virtual b8 operator==(const ListIterator& other)
			{
				return ((list == other.list) && (node == other.node));
			}
			virtual b8 operator!=(const ListIterator& other)
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

		//-------------------Emplace functions--------//
		
		template<typename ...Args>
		void PutBack(Args... vArgs)
		{
			if(!mTail)
			{
				mTail = new Node(0, 0, vArgs...);
				mHead = mTail;
			}
			else
			{
				Node* temp = new Node(0, mTail, vArgs...);
				if(mTail != mHead)
				{
					mTail->next = temp;
				}
				mTail = temp;
			}
			mSize++;
		}

		template<typename ...Args>
		void PutFront(Args... vArgs)
		{
			if(!mHead)
			{
				mHead = new Node(0, 0, vArgs...);
				mTail = mHead;
			}
			else
			{
				Node* temp = new Node(mHead, 0, vArgs...);
				if(mHead != mTail)
				{
					mHead->back = temp;	
				}
				mHead = temp;
			}
			mSize++;
		}

		template<typename ...Args>
		void PutAfter(const T& elemBefore, Args... vArgs)
		{
			Node* test = mHead;
			while(test)
			{
				if(test->elem == elemBefore) // insert here
				{
					Node* nextNode = test->next;
					Node* temp = new Node(nextNode, test, vArgs...);
					
					if(nextNode) nextNode->back = temp;
					test->next = temp;
					mSize++;
					if(test == mTail) mTail = temp;
					test = test->next;
					break;
				}
				if(test) test = test->next;
			}
		}

		template<typename ...Args>
		void PutBefore(const T& elemBefore, Args... vArgs)
		{
			Node* test = mTail;
			while(test)
			{
				if(test->elem == elemBefore) // insert here
				{
					Node* lastNode = test->back;
					Node* temp = new Node(test, lastNode, vArgs...);
					if(lastNode) lastNode->next = temp;
					test->back = temp;
					if(test == mHead) mHead = temp;
					mSize++;
					test = test->back;
					break;
				}
				if(test) test = test->back;
			}
		}
		
		//--------------------------------------------//

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

		ListIterator<T> begin() const 
		{
			return ListIterator<T>(const_cast<List<T>*>(this), IteratorPosition::BEGIN);
		}

		ListIterator<T> end() const
		{
			return ListIterator<T>(const_cast<List<T>*>(this), IteratorPosition::END);
		}
	};
}

#endif