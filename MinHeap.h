#include<iostream>
#include<vector>
#include<assert.h>

using namespace std;

template<class T>
struct cmp//�º���
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
	Heap(const T* a, size_t size)//���캯��
	{
		assert(a);
		_v.resize(size);
		for (size_t i = 0; i < size; i++)
		{
			_v[i] = a[i];
		}
		_CreatMinHeap();//������С�Ѻ���
	}
	void Insert(T& x)//���뺯��
	{
		//�ŵ����һ����Ȼ��������ϵ�
		_v.push_back(x);
		_AdjustUp((_v.size() - 2) / 2);
	}
	T & Top()//���ظ����
	{
		return _v[0];
	}
	void Pop()//ɾ�������
	{
		if (_v.size())
		{
			//������һ�������һ����㣬ɾ�����һ����Ȼ�󽫵�һ�������µ�
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
	T &operator[](size_t size)//����[]
	{
		return _v[size];
	}
protected:
	void _AdjustUp(size_t root)  //�ϵ�����
	{
		if (_v.size()>1)
		{
			int parent = root;
			int child = parent * 2 + 1;
			while (parent >= 0)
			{
				//�ж���������Һ��ӣ��Ƚ����Ӹ��Һ��ӣ�����Һ��Ӹ�С�ͽ����ӵ�ֵ��ֵΪ�Һ���
				if (child + 1 < _v.size() && Hcmp()(_v[child + 1], _v[child]))
				{
					child++;
				}
				if (Hcmp()(_v[child],_v[parent]))
				{
					//������׽��С�ں��ӽ�㣬���������ڵ㣬���Ӹ�ֵΪ���׽�㣬���׽��Ϊ���Ӽ�1��2������ĸ��׺ͺ���ָ�����±꣩
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
	void _AdiustDown(size_t root)//�µ�����������һ�������Ӹ���ʼ���£������ȸ�С�ľ����ϵ�
	{
		if (_v.size()>1)
		{
			size_t parent = root;
			size_t child = parent * 2 + 1;
			while (child < _v.size())
			{//�ж���������Һ��ӣ��Ƚ����Ӹ��Һ��ӣ�����Һ��Ӹ�С�ͽ����ӵ�ֵ��ֵΪ�Һ���
				if (child + 1 < _v.size() && Hcmp()(_v[child+1],_v[child]))
				{
					child++;
				}
				if (Hcmp()(_v[child],_v[parent]))
				{
					//������׽��С�ں��ӽ�㣬���������ڵ㣬���׸�ֵΪ���ӽ�㣬���ӽ��Ϊ���׽��Ķ�����1������ĸ��׺ͺ���ָ�����±꣩
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
	void _CreatMinHeap() //������С��
	{
		for (int i = (_v.size() - 2) / 2; i >= 0; i--)//�����һ����Ҷ�ӽڵ㿪ʼ����
		{
			_AdiustDown(i); //�µ�����
		}
	}

protected:
	vector<T> _v;
};


