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
	HuffmanTree(const T * a, size_t size, const T & invalid)//���캯��
	{
		_root = CreateTree(a, size, invalid);//����
	}
	bool operator()(Node* cmp1,Node *cmp2)//�º���
	{
		return cmp1_weight < cmp2->_weight;
	}
	Node *&Top()//���ظ�
	{
		return _root;
	}
	Node * CreateTree(const T *& a, size_t size, const T & invalid)//����
	{
		assert(a);
		Heap<Node *> _heap;
		for (size_t i = 0; i < size; i++)
		{
			if (!(a[i] == invalid))//������ǷǷ�ֵ���Ͳ��뵽��
			{
				Node *tmp = new Node(a[i]);
				_heap.Insert(tmp);
			}	
		}
		Node * left = NULL;
		Node * right = NULL;
		if (_heap.Size() == 1)//�����ֻ��һ�������򷵻�
		{
			return _heap.Top();
		}
		else//�������öѽ��й���HuffmanTree
		{
			while (_heap.Size()>1)//����Ե���Ϊ1��������ѭ����
			{
				//һ��ȡһ���Ѷ�Ԫ�أ�ȡ���Σ��ֱ�Ϊleft,right ������������root��root->_left=left,root->_right=right,�ٽ�root push������
				left = _heap.Top();
				_heap.Pop();
				right = _heap.Top();
				_heap.Pop();
				Node *sum = new Node(left->_weight + right->_weight);
				sum->_left = left;
				sum->_right = right;
				_heap.Insert(sum);
			}
			return _heap.Top();//��󷵻ضѶ�Ԫ��
		}
		return NULL;
	}
protected:
	Node* _root;
};

