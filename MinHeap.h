#include<iostream>
#include<vector>
#include<assert.h>

using namespace std;

template<class T>
struct cmp//仿函数
{
	bool operator()(T cmp1, T cmp2)
	{
		return cmp1->_weight < cmp2->_weight;
	}
};
template<class T, class Hcmp = cmp<T>>
class Heap
{
public:
	Heap()
	{}
	Heap(const T* a, size_t size)//构造函数
	{
		assert(a);
		_v.resize(size);
		for (size_t i = 0; i < size; i++)
		{
			_v[i] = a[i];
		}
		_CreatMinHeap();//构建最小堆函数
	}
	void Insert(T& x)//插入函数
	{
		//放到最后一个，然后进行是上调
		_v.push_back(x);
		_AdjustUp((_v.size() - 2) / 2);
	}
	T & Top()//返回根结点
	{
		return _v[0];
	}
	void Pop()//删除跟结点
	{
		if (_v.size())
		{
			//交换第一个跟最后一个结点，删除最后一个，然后将第一个进行下调
			swap(_v[0], _v[_v.size() - 1]);
			_v.pop_back();
			_AdiustDown(0);
		}
		else
		{
			cout << "heap is empty!" << endl;
		}
	}
	size_t Size()
	{
		return _v.size();
	}
	T &operator[](size_t size)//重载[]
	{
		return _v[size];
	}
protected:
	void _AdjustUp(size_t root)  //上调函数
	{
		if (_v.size()>1)
		{
			int parent = root;
			int child = parent * 2 + 1;
			while (parent >= 0)
			{
				//判断如果存在右孩子，比较左孩子跟右孩子，如果右孩子更小就将孩子的值赋值为右孩子
				if (child + 1 < _v.size() && Hcmp()(_v[child + 1], _v[child]))
				{
					child++;
				}
				if (Hcmp()(_v[child],_v[parent]))
				{
					//如果父亲结点小于孩子结点，交换两个节点，孩子赋值为父亲结点，父亲结点为孩子减1除2（这里的父亲和孩子指的是下标）
					T tmp = _v[child];
					_v[child] = _v[parent];
					_v[parent] = tmp;
					child = parent;
					parent = (child - 1) / 2;
				}
				else
				{
					break;
				}
			}
		}
	}
	void _AdiustDown(size_t root)//下调函数，给定一个跟，从跟开始往下，遇到比跟小的就往上调
	{
		if (_v.size()>1)
		{
			size_t parent = root;
			size_t child = parent * 2 + 1;
			while (child < _v.size())
			{//判断如果存在右孩子，比较左孩子跟右孩子，如果右孩子更小就将孩子的值赋值为右孩子
				if (child + 1 < _v.size() && Hcmp()(_v[child+1],_v[child]))
				{
					child++;
				}
				if (Hcmp()(_v[child],_v[parent]))
				{
					//如果父亲结点小于孩子结点，交换两个节点，父亲赋值为孩子结点，孩子结点为父亲结点的二倍加1（这里的父亲和孩子指的是下标）
					/*swap(a[child], a[parent]);*/
					T tmp = _v[child];
					_v[child] = _v[parent];
					_v[parent] = tmp;
					parent = child;
					child = parent * 2 + 1;
				}
				else
				{
					break;
				}
			}
		}
	}
	void _CreatMinHeap() //构建最小堆
	{
		for (int i = (_v.size() - 2) / 2; i >= 0; i--)//从最后一个非叶子节点开始往上
		{
			_AdiustDown(i); //下调函数
		}
	}

protected:
	vector<T> _v;
};


