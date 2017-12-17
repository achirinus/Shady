#ifndef SH_BI_TREE_H
#define SH_BI_TREE_H

namespace Shady
{
	template<typename T>
	struct BiTreeNode
	{
		using Node = BiTreeNode<T>; 
		T data;
		Node* left; 
		Node* right;
		s8 factor;

		BiTreeNode(const T& d, Node* l = 0, Node* r = 0, s8 f = 0):
					data{d}, left{l}, right{r}, factor{f} {}

	};
	template<typename T>
	class BiTree
	{
		using Node = BiTreeNode<T>;
		Node* root;
		u32 size;

	public:
		BiTree(): root{0}, size{0} {}
		~BiTree()
		{
			Remove(&root);
		}

		void Remove(Node** node)
		{
			if(*node)
			{
				if(*node->left)
				{
					Remove(&(*node->left));
				}
				if(*node->right)
				{
					Remove(&(*node->right));
				}
				
				delete *node;
				*node = 0;
			}
		}

		b8 Find(const T& data, Node** node = &root)
		{
			b8 result = false;
			if(*node)
			{
				if(data == *node->data) 
				{
					result = true;
					return result;
				}
				if(Find(data, &(*node->left))) 
				{
					result = true;
					return result;
				}
				if(Find(data, &(*node->right)))
				{
					result = true;
					return result;
				}
			}
			
			return result;
		}

		b8 Add(const T& data, Node** node = &root)
		{
			if(*node)
			{
				s32 res = Compare(data, *node->data);
				if(!res) return false;
				if(res > 0)
				{
					Add(data, &(*node->left));
				}
				else
				{
					Add(data, &(*node->right));
				}
			}
			else
			{
				*node = new Node(data);
			}
			return true;
		}
	};
}

#endif
