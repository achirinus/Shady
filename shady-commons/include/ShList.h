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
		LNode() = default;
		LNode(T e, LNode<T>* n = nullptr, LNode<T>* b = nullptr): elem{e}, next{n}, back{b} {}
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
						node = nullptr;
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
		List(): mTail{nullptr}, mHead{nullptr}, mSize{0} { }
		List(const List<T>& other): mTail{nullptr}, mHead{nullptr}, mSize{0}
		{
			for(T& elem : other)
			{
				PushFront(elem);
			}
		}
		List<T>& operator=(const List<T>& other)
		{
			Node* last = mTail;
			while(last)
			{
				Node* temp = last;
				last = last->next;
				delete temp;
			}
			mSize = 0;

			for(T& elem: other)
			{
				PushFront(elem);
			}
				
			return *this;	
		}
		List(List<T>&& other)
		{
			mTail = other.mTail;
			mHead = other.mHead;
			mSize = other.mSize;

			other.mTail = nullptr;
			other.mHead = nullptr;
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

		void PushBack(T elem)
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

		void PushFront(T elem)
		{
			if(!mHead)
			{
				mHead = new Node(elem);
				mTail = mHead;
			}
			else
			{
				Node* temp = new Node(elem, nullptr, mHead);
				mHead->next = temp;
				mHead = temp;
			}
			mSize++;
		}

		void InsertAfter(const T& elemBefore, T elem, b8 insAfterMulElems = false)
		{
			Node* test = mTail;
			while(test)
			{
				if(test->elem == elemBefore) // insert here
				{
					Node* temp = new Node(elem, test->next, test);
					if(test->next) test->next->back = temp;

					if(test == mHead) mHead = temp;

					test->next = temp;
					mSize++;
					test = test->next;
					if(!insAfterMulElems) break;
				}
				test = test->next;
			}
		}

		void InsertBefore(const T& elemBefore, T elem, b8 insAfterMulElems = false)
		{
			Node* test = mTail;
			while(test)
			{
				if(test->elem == elemBefore) // insert here
				{
					Node* temp = new Node(elem, test, test->back);
					if(test->back) test->back->next = temp;
					if(test == mTail) mTail = temp;
					test->back = temp;
					mSize++;
					
					if(!insAfterMulElems) break;
				}
				test = test->next;
			}
		}

		T PopBack()
		{
			SH_ASSERT(mSize > 0);

			T result = mTail->elem;
			Node* temp = mTail;
			mTail = temp->next;
			if(mTail) mTail->back = nullptr;
			delete temp;

			mSize--;
			return result;
		}

		T PopFront()
		{
			SH_ASSERT(mSize > 0);
			
			T result = mHead->elem;
			
			Node* temp = mHead; 
			mHead = temp->back;
			if(mHead) mHead->next = nullptr;
			delete temp;

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
							mHead = mTail = nullptr;
							temp = nullptr;
						}
						else
						{
							mHead = mHead->next;
							if(mHead)
							{
								mHead->back = nullptr;	
							}
							temp = temp->next;	
						}
					}
					else if(temp == mTail)
					{
						mTail = mTail->back;
						if(mTail)
						{
							mTail->next = nullptr;
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