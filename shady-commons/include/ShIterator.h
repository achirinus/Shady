#ifndef SH_ITERATOR_H
#define SH_ITERATOR_H

namespace Shady
{
	enum class IteratorPosition
	{	
		BEGIN,
		END
	};
	template <typename Child, typename T>
	struct Iterator
	{
		
		virtual T& operator*() = 0;
		virtual Child& operator=(const Child& other) = 0;
		virtual Child operator+(u32 offset) = 0;
		virtual Child operator-(u32 offset) = 0;
		virtual Child& operator+=(u32 offset) = 0;
		virtual Child& operator-=(u32 offset) = 0;
		virtual Child operator++() = 0;
		virtual Child operator++(int) = 0;
		virtual Child operator--() = 0;
		virtual Child operator--(int) = 0;
		virtual b8 operator==(const Child& other) = 0;
		virtual b8 operator!=(const Child& other) = 0;
	};
}

#endif