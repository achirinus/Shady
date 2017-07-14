#ifndef SH_QUEUE_H
#define SH_QUEUE_H

namespace Shady
{
	template<typename T>
	struct Node
	{
		Node<T>* before;
		T* elem;
		Node<T>* after;
	};
	template<typename T>
	class Queue
	{
		Node<T>* mLast;
		u32 mSize;
	public:
		Queue(): mLast(nullptr), mSize(0) {}
		~Queue()
		{
			while(mLast)
			{
				Node<T>* temp = mLast;
				mLast = mLast->before;
				delete temp;
			}
		} 

		void push(T* elem)
		{
			if(!mLast)
			{
				mLast = new Node<T>();
				mLast->elem = elem;

			}
			else
			{
				mLast->after = new Node<T>();
				mLast->after->before = mLast;
				mLast->after->elem = elem;
				mLast = mLast->after;
			}
			mSize++;
		}

		T* pop()
		{
			T* result = nullptr;
			if(mLast)
			{
				result = mLast->elem;
				Node<T>* temp = mLast;
				if(mLast->before)
				{
					mLast = mLast->before;
					mLast->after = nullptr;
				}
				else
				{
					mLast = nullptr;
				}
				delete temp;
			}
			
			return result;
		}

		u32 size() { return mSize;}
	};
}

#endif