#ifndef SH_COM_FUNCS_H
#define SH_COM_FUNCS_H

#include "ShTypes.h"

namespace Shady
{
	template <typename T>
	void swap(T& left, T& right)
	{
		T temp = left;
		left = right;
		right = temp;
	}
}

#endif