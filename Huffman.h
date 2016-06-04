#include<iostream>
#include"MinHeap.h"
using namespace std;

template<class T>
struct HuffmanNode
{
	T _weight;
	HuffmanNode<T> *_left;
	HuffmanNode<T> *_right;
	HuffmanNode<T>(T  x)
		: _weight(x)
		,_left(NULL)
		, _right(NULL)
	{}
};
template<class T>
class HuffmanTree
{
	typedef  HuffmanNode<T> Node;
public:
	HuffmanTree(const T * a, size_t size, const T & invalid)//构造函数
	{
		_root = CreateTree(a, size, invalid);//建树
	}
	bool operator()(Node* cmp1,Node *cmp2)//仿函数
	{
		return cmp1_weight < cmp2->_weight;
	}
	Node *&Top()//返回根
	{
		return _root;
	}
	Node * CreateTree(const T *& a, size_t size, const T & invalid)//建树
	{
		assert(a);
		Heap<Node *> _heap;
		for (size_t i = 0; i < size; i++)
		{
			if (!(a[i] == invalid))//如果不是非法值，就插入到堆
			{
				Node *tmp = new Node(a[i]);
				_heap.Insert(tmp);
			}	
		}
		Node * left = NULL;
		Node * right = NULL;
		if (_heap.Size() == 1)//如果堆只有一个数，则返回
		{
			return _heap.Top();
		}
		else//否则，利用堆进行构建HuffmanTree
		{
			while (_heap.Size()>1)//如果对的数为1，则跳出循环，
			{
				//一次取一个堆顶元素，取两次，分别为left,right 用他们俩构造root，root->_left=left,root->_right=right,再将root push到堆中
				left = _heap.Top();
				_heap.Pop();
				right = _heap.Top();
				_heap.Pop();
				Node *sum = new Node(left->_weight + right->_weight);
				sum->_left = left;
				sum->_right = right;
				_heap.Insert(sum);
			}
			return _heap.Top();//最后返回堆顶元素
		}
		return NULL;
	}
protected:
	Node* _root;
};

