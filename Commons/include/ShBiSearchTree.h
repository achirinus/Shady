#ifndef SH_BISEARCHTREE_H
#define SH_BISEARCHTREE_H

#include "ShMath.h"
#include "ShStack.h"
#include "ShArray.h"

#define BISTREE_ACCEPTED_BALANCE 1
namespace Shady
{
	template<typename T>
	struct BiSearchTreeNode
	{
		using Node = BiSearchTreeNode<T>; 
		T Data;
		Node* Left; 
		Node* Right;
	
		BiSearchTreeNode(const T& d, Node* l = 0, Node* r = 0):
			Data{d}, Left{l}, Right{r} {}

	};
	template<typename T>
	class BiSearchTree
	{
		using Node = BiSearchTreeNode<T>;
		Node* mRoot;
		u32 mSize;

		b8 Add(const T& Data, Node*& CurrentNode)
		{
			if (CurrentNode)
			{
				s32 Res = Compare(Data, CurrentNode->Data);
				if (!Res) return false;
				if (Res > 0)
				{
					b8 Added = Add(Data, CurrentNode->Left);
					
				}
				else
				{
					Add(Data, CurrentNode->Right);
				}
			}
			else
			{
				CurrentNode = new Node(Data);
			}
			return true;
		}

		//For now this also removes subtrees, maybe should remove just the node with data
		//and reasign the left and the right
		b8 Remove(const T& Data, Node*& CurrentNode)
		{
			b8 Result = false;
			if (CurrentNode)
			{
				s32 Res = Compare(Data, CurrentNode->Data);
				if (!Res)
				{
					Remove(CurrentNode);
					Result = true;
				}
				if (Res > 0)
				{
					Result = Remove(Data, CurrentNode->Left);
				}
				if(Res < 0)
				{
					Result = Remove(Data, CurrentNode->Right);
				}
			}
			return Result;
		}

		void RotateLL(Node*& CurrentNode)
		{
			Node* FirstLeft = CurrentNode->Left;
			Node* SecondLeft = CurrentNode->Left->Left;
			
			if (FirstLeft->Right)
			{
				CurrentNode->Left = FirstLeft->Right;
			}
			else
			{
				CurrentNode->Left = 0;
			}

			FirstLeft->Right = CurrentNode;
			CurrentNode = FirstLeft;
		}

		void RotateLR(Node*& CurrentNode)
		{
			Node* FirstLeft = CurrentNode->Left;
			Node* SecondRight = CurrentNode->Left->Right;

			Node* ThirdRight = SecondRight->Right;
			Node* ThirdLeft = SecondRight->Left;

			SecondRight->Right = CurrentNode;
			SecondRight->Left = FirstLeft;

			if (ThirdRight)
			{
				CurrentNode->Left = ThirdRight;
			}
			else
			{
				CurrentNode->Left = 0;
			}
			if (ThirdLeft)
			{
				FirstLeft->Right = ThirdLeft;
			}
			else
			{
				FirstLeft->Right = 0;
			}
			
			CurrentNode = SecondRight;
		}

		void RotateRR(Node*& CurrentNode)
		{
			Node* FirstRight = CurrentNode->Right;
			Node* SecondRight = CurrentNode->Right->Right;

			if (FirstRight->Left)
			{
				CurrentNode->Right = FirstRight->Left;
			}
			else
			{
				CurrentNode->Right = 0;
			}

			FirstRight->Left = CurrentNode;
			CurrentNode = FirstRight;
		}

		void RotateRL(Node*& CurrentNode)
		{
			Node* FirstRight = CurrentNode->Right;
			Node* SecondLeft = CurrentNode->Right->Left;

			Node* ThirdRight = SecondLeft->Right;
			Node* ThirdLeft = SecondLeft->Left;

			SecondLeft->Right = FirstRight;
			SecondLeft->Left = CurrentNode;

			if (ThirdLeft)
			{
				CurrentNode->Right = ThirdLeft;
			}
			else
			{
				CurrentNode->Right = 0;
			}
			if (ThirdRight)
			{
				FirstRight->Left = ThirdRight;
			}
			else
			{
				FirstRight->Left = 0;
			}

			CurrentNode = SecondLeft;
		}

		void Balance()
		{
			Array<Node**> NodeArr{mSize};
			Node** CurrentNode = &mRoot;
			if(*CurrentNode) NodeArr.Add(CurrentNode);
			while (NodeArr.Size())
			{
				Array<Node**> TempNodes(NodeArr.Size() * 2);
				for (Node** FENode : NodeArr)
				{
					Node*& Left = (*FENode)->Left;
					Node*& Right = (*FENode)->Right;

					if (Left) TempNodes.Add(&Left);
					if (Right) TempNodes.Add(&Right);
					
					if (!Left && !Right) continue;

					s32 LeftHeight = GetHeight(Left);
					s32 RightHeight = GetHeight(Right);
					
					if ((LeftHeight - RightHeight) > BISTREE_ACCEPTED_BALANCE)
					{
						Node*& LLeft = Left->Left;
						Node*& LRight = Left->Right;
						
						s32 LLeftHeight = GetHeight(LLeft);
						s32 LRightHeight = GetHeight(LRight);
						if (LLeftHeight > LRightHeight)
						{
							RotateLL(*FENode);
							return;
						}
						else if (LRightHeight > LLeftHeight)
						{
							RotateLR(*FENode);
							return;
						}
					}
					else if ((RightHeight - LeftHeight) > BISTREE_ACCEPTED_BALANCE)
					{
						Node*& RLeft = Right->Left;
						Node*& RRight = Right->Right;

						s32 RLeftHeight = GetHeight(RLeft);
						s32 RRightHeight = GetHeight(RRight);
						if (RLeftHeight > RRightHeight)
						{
							RotateRL(*FENode);
							return;
						}
						else if (RRightHeight > RLeftHeight)
						{
							RotateRR(*FENode);
							return;
						}
					}
				} // Foreach
				NodeArr = Move(TempNodes);
			}
		}

		s32 GetHeight(Node* node)
		{
			if (!node) return -1;
			if (!node->Left && !node->Right) return 0;
			return 1 + Max(GetHeight(node->Left), GetHeight(node->Right));
		}

		b8 Find(const T& Data, Node*& CurrentNode)
		{
			b8 Result = false;
			if (CurrentNode)
			{
				if (Data == CurrentNode->Data)
				{
					Result = true;
					return Result;
				}
				if (Find(Data, CurrentNode->Left))
				{
					Result = true;
					return Result;
				}
				if (Find(Data, CurrentNode->Right))
				{
					Result = true;
					return Result;
				}
			}
			return Result;
		}

	public:
		BiSearchTree(): mRoot{0}, mSize{0} {}
		~BiSearchTree()
		{
			Remove(mRoot);
		}

		void Remove(Node*& CurrentNode)
		{
			if(CurrentNode)
			{
				if(CurrentNode->Left)
				{
					Remove(CurrentNode->Left);
				}
				if(CurrentNode->Right)
				{
					Remove(CurrentNode->Right);
				}
				
				delete CurrentNode;
				CurrentNode = 0;
			}
		}

		
		b8 Remove(const T& Data)
		{
			b8 Result = Remove(Data, mRoot);
			if (Result)
			{
				mSize--;
				Balance();
			}
			return Result;
		}

		b8 Find(const T& Data)
		{
			return Find(Data, mRoot);
		}

		b8 Add(const T& Data)
		{
			b8 Added = Add(Data, mRoot);
			if (Added)
			{
				mSize++;
				Balance();
			}
			return Added;
		}

		s32 GetHeight()
		{
			return GetHeight(mRoot);
		}
	};
}


#undef BISTREE_ACCEPTED_BALANCE
#endif
