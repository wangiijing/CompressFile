#include<iostream>
using namespace std;
#include<string>
#include"Huffman.h"


#define  LongType unsigned long
struct NodeInfo
{
	unsigned char _ch; //字符
	LongType _count;   //出现次数
	string _code;     //Huffman code
	//构造函数
	NodeInfo(LongType _count = 0)
		:_ch(0)
		, _count(_count)
	{}
	//==的重载
	bool operator ==(NodeInfo cmp2)const
	{
		return _count == cmp2._count;
	}
	//重载+
	NodeInfo operator +(NodeInfo& tmp)
	{
		return _count + tmp._count;
	}
	//重载<
	bool operator <(NodeInfo cmp2)const
	{
		return _count < cmp2._count;
	}
};

class FileCompress
{
public:
	void Compress(const char *filename)
	{
		/*******************统计字符和字符出现的次数********************/
		FILE *Fout = fopen(filename, "rb");
		assert(Fout);
	    char ch = fgetc(Fout);
		while (ch != EOF)
		{
			_infos[(unsigned char)ch]._ch = ch;
			_infos[(unsigned char)ch]._count++;
			ch = fgetc(Fout);
		}
		/**************************************************************/

		/**********************构建HuffmanTree获得Huffman编码***********/
		NodeInfo tmp = (0);
		HuffmanTree<NodeInfo>_tree(_infos, 256, tmp);
		string name = "testi.txt";
		FILE * Fin1 = fopen(name.c_str(), "wb");
		string code;
		GenerateHuffmanCode(_tree.Top(), code, Fin1);
		fclose(Fin1);
		/**************************************************************/
		/*********************文件压缩  ******************************/
		name = "test1.txt";
		FILE * Fin = fopen(name.c_str(), "wb");
		assert(Fin);
		fseek(Fout, 0, SEEK_SET);
		ch = fgetc(Fout);
		unsigned char value = 0;
		int count = 0;
		while (ch != EOF)
		{
			while (count < 8 && ch!=EOF)
			{
				for (size_t i = 0; i < _infos[(unsigned char)ch]._code.size(); i++)
				{
					if (count < 8)
					{
						value = value << 1;
						value |= _infos[(unsigned char)ch]._code[i]-'0';
						count++;
					}
					else
					{
						fputc(value, Fin);
						count = 1;
						value = 0;
					    value = value << 1;
						value |= _infos[(unsigned char)ch]._code[i] - '0';
					}
					
				}
				ch = fgetc(Fout);
			}
			if (count >= 8 )
			{
				fputc(value, Fin);
				count = 0;
				value = 0;
			}	
		}
		value = value << (8 - count);
		fputc(value, Fin);
		fclose(Fout);
		fclose(Fin);
		
	}
	
	void UnCompress(const char *filename)
	{
		//初始化_infos[]
		string code;
		FILE * Fout1 = fopen("testi.txt", "rb");
		unsigned char ch = fgetc(Fout1);
		while (!feof(Fout1))
		{
			code.clear();
			_infos[ch]._ch = ch;
			fgetc(Fout1);
			GetLine(Fout1, code);
			_infos[ch]._count = atoi(code.c_str());
			ch = fgetc(Fout1);
		}

		//构建Huffmanshu
		NodeInfo tmp = (0);
		HuffmanTree<NodeInfo>_tree(_infos, 256, tmp);


		//读取压缩文件，解压文件
		string name(filename);
		FILE* Fout = fopen(name.c_str(), "rb");
		name += ".uncompress";
		FILE* Fin = fopen(name.c_str(), "wb");
		unsigned char value = fgetc(Fout);
		HuffmanNode<NodeInfo>* root = _tree.Top();
		HuffmanNode<NodeInfo>* cur = root;
		LongType size = root->_weight._count;
		int count = 0;
		while (1)
		{
			while (cur->_left != NULL && cur->_right != NULL && count < 8)
			{
				if (((value >>(7-count)) & 1)==1 )
				{
					cur = cur->_right;
				}
				else
				{
					cur = cur->_left;
				}
				count++;
			}
			if (cur->_left == NULL && cur->_right == NULL)
			{
				fputc(cur->_weight._ch, Fin);
				cur = root;
				if (--size == 0)
				{
					break;
				}	
			}
			else
			{
				value = fgetc(Fout);
				count = 0;
			}
		}
		fclose(Fout);
		fclose(Fin);

	}
protected:
	void GetLine(FILE* Fout, string & code)
	{
		char ch = fgetc(Fout);
		if (ch == '\n')
		{
			code += '\n';
		}
		while (!feof(Fout) && ch != '\n')
		{
			code += ch;
			ch = fgetc(Fout);
		}
	}

	void GenerateHuffmanCode(HuffmanNode <NodeInfo> * root, string code, FILE * Fin)
	{
		assert(root);
		if (root->_left != NULL && root->_right != NULL)
		{
			GenerateHuffmanCode(root->_left, code + '0',Fin);
			GenerateHuffmanCode(root->_right, code + '1',Fin);
		}
		for (int i = 0; i < code.size() ; i++)
		{
			root->_weight._code += code[i];
		}
		if (root->_left == NULL && root->_right == NULL)
		{
			_infos[root->_weight._ch]._code = root->_weight._code;
			fputc(_infos[root->_weight._ch]._ch, Fin);
			fputc(':', Fin);
			char str[256] = { 0 };
			fputs(_itoa(_infos[root->_weight._ch]._count,str,10), Fin);
			fputc('\n', Fin);
		}
	}
protected:
	NodeInfo _infos[256];
};

void Compresstest()
{
	FileCompress h;
	h.Compress("test.txt");
}
void UnCompresstest()
{
	FileCompress file;
	file.UnCompress("test1.txt");
}