#pragma once
template <class T> class Node;
template <class T> class DoubleLinkedList;
template <class T> class DLinkedListItertator;

template <class T>
class Node
{
public:
	T data;
	Node *Next;
	Node *Prev;

	void InsertAfter(T data)
	{
		Node<T> *newNode = new Node<T>();
		newNode->Prev = this;
		newNode->Next = Next;
		Next = newNode;

		// Next가 NULL인지 아닌지 검사 필요
		if (0 != newNode->Next)
		{
			newNode->Next->Prev = newNode;
		}
		newNode->data = data;
	}

	void InsertBefore(T data)
	{
		Node<T> *newNode = new Node<T>();
		newNode->Next = this;
		newNode->Prev = this->Prev;

		if (0 != this->Prev)
		{
			this->Prev->Next = newNode;
		}
		this->Prev = newNode;
		newNode->data = data;
	}

	void DLink()
	{
		if (0 != Prev)
		{
			Prev->Next = Next;
		}

		if (0 != Next)
		{
			Next->Prev = Prev;
		}
	}
};

template <class T>
class DoubleLinkedList
{
public:
	Node<T> *_Head;
	Node<T> *_Tail;
	int _Count;

	DoubleLinkedList()
	{
		_Head = 0;
		_Tail = 0;
		_Count = 0;
	}

	~DoubleLinkedList()
	{
		Node<T> *node = _Head;
		Node<T> *next;

		while (0 != node)
		{
			next = node->Next;
			delete node;
			node = next;
		}
	}

	// Append 기능 : 링크드리스트 맨 마지막에 새로운 노드를 붙이는 기능
	void Append(T data)
	{
		if (_Head == 0)
		{
			Node<T>* newNode = new Node<T>();
			newNode->data = data;
			_Tail = _Head = newNode;
			_Head->Prev = 0;
			_Tail->Next = 0;
		}
		else
		{
			_Tail->InsertAfter(data);
			_Tail = _Tail->Next;
		}

		_Count++;

	}

	// Prepend 기능 : Tail 뒤에다가 노드를 추가하는 기능
	void Prepend(T data)
	{
		if (_Head == 0)
		{
			Node<T>* nd = new Node<T>();
			nd->data = data;

			_Head = _Tail = nd;
			_Head->Prev = 0;
			_Tail->Next = 0;
		}
		else
		{
			_Head->InsertBefore(data);
			_Head = _Head->Prev;
		}

		_Count++;

	}

	// Head를 삭제
	void RemoveHead()
	{
		if (0 != _Head)
		{
			Node<T> *node = _Head->Next;
			delete _Head;
			_Head = node;

			if (0 == _Head)
				_Tail = 0;
			else
				_Head->Prev = 0;
		}
	}

	// Tail 삭제
	void RemoveTail()
	{
		if (0 != _Tail)
		{
			Node<T> *node = _Tail->Prev;
			delete _Tail;
			_Tail = node;

			if (0 == _Tail)
				_Head = 0;
			else
				_Tail->Next = 0;
		}
	}

	int GetCount()
	{
		return _Count;
	}

	DLinkedListItertator<T> GetIterator()
	{
		return DLinkedListItertator<T>(this, _Head);
	}

	void Remove(DLinkedListItertator<T> &itr)
	{
		if (itr.node == 0)
		{
			return;
		}
		Node<T> *newNode = itr.node;

		newNode = itr.node;
		if (itr.node == _Head)
		{
			_Head = _Head->Next;
		}

		if (itr.node == _Tail)
		{
			_Tail = _Tail->Prev;
		}

		itr.Forth();
		newNode->DLink();
		delete newNode;

		if (0 == _Head)
		{
			_Tail = 0;
		}

		_Count--;
	}

	void InsertAfter(DLinkedListItertator<T> &itr, T data)
	{
		if (0 != itr.Node)
		{
			itr.Node->InsertAfter(data);
			if (itr.Node == _Tail)
			{
				_Tail = itr.Node->Next;
				_Count++;
			}
		}
		else
		{
			Append(data);
		}
	}

	void InsertBefore(DLinkedListItertator<T> &itr, T data)
	{
		if (0 != itr.node)
		{
			itr.node->InsertBefore(data);
			if (itr.node == _Head)
			{
				_Head = itr.node->Prev;
				_Count++;
			}
		}
		else
		{
			Prepend(data);
		}
	}

	void SaveData()
	{
		FILE *fp = fopen("Filename", "w+b");

		if (0 == fp)
		{
			return;
		}

		fwrite(&_Count, sizeof(int), 1, fp);

		Node<T> *node = _Head;

		while (node != 0)
		{
			fwrite(&node->data, sizeof(int), 1, fp);
			node = node->Next;
		}

		fclose(fp);

	}

	void LoadData()
	{
		FILE *fp = fopen("Filename", "rb");

		if (0 == fp)
		{
			return;
		}

		int LoadCount;		// 갯수를 가지고 있는 공간

		fread(&LoadCount, sizeof(int), 1, fp);

		for (int i = 0; i < LoadCount; i++)
		{
			int buffer;		// 임시 데이터 저장 공간
			fread(&buffer, sizeof(int), 1, fp);
			Append(buffer);
		}

		fclose(fp);

	}
};

template <class T>
class DLinkedListItertator
{
public:

	DoubleLinkedList<T> *LinkedList;
	Node<T> *node;

	DLinkedListItertator(DoubleLinkedList<T> *I, Node<T> *_node)
	{
		LinkedList = I;
		node = _node;
	}

	void Start()
	{
		node = LinkedList->_Head;
	}

	void End()
	{
		node = LinkedList->_Tail;
	}

	void Forth()
	{
		if (0 != node)
		{
			node = node->Next;
		}
	}

	void Back()
	{
		if (0 != node)
		{
			node = node->Prev;
		}
	}

	bool Valid()
	{
		if (0 != node)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	T Item()
	{
		return node->data;
	}

};