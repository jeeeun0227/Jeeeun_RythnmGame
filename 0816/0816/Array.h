#pragma once

template <class T>		// Template 선언하기
class Array
{
private:
	T *_array;
	int _size;
public:
	Array(int size)
	{
		_array = new T[size];
		_size = size;
	}

	~Array()
	{
		if (NULL != _array)		// NULL체크
		{
			delete[] _array;
		}
		_array = NULL;
		_size = 0;
	}

	T& Array::operator[](int index);

	operator T *();		// 반환연산자
						// ()안에 들어가는것을 정수형 포인터로 반환할것이다.
	
	void Resize(int newSize);

	void Set(int index, T newItem)
	{
		_array[index] = newItem;
	}

	T Get(int index)
	{
		return _array[index];
		// 에러 (1)
	}

	void Insert(T InsertNum, int InsertLocate);
	void Remove(int RemoveIndex);

	bool SaveDate(const char*filename);
	bool LoadDate(const char*filename);

	int ReturnSize();
};

// 복사 시작
template <class T>		// Template를 사용하기 위해서 함수마다 붙여준다.
T& Array<T>::operator[](int index)		// Template 안에 있는 멤버함수를 사용하기 위해서는 <T>를 붙여준다.
{
	return _array[index];
}

template <class T>
Array<T>::operator T *()
{
	return _array;
}

template <class T>
void Array<T>::Resize(int newSize)
{
	int *newArray = new int[newSize];

	if (NULL == newArray)
	{
		return;
	}

	int minSize = 0;

	if (_size > newSize)
	{
		minSize = newSize;
	}
	else
	{
		minSize = _size;
	}

	for (int i = 0; i < minSize; i++)
	{
		newArray[i] = _array[i];
	}

	if (NULL != _array)
	{
		delete[] _array;
	}

	_array = newArray;
	_size = newSize;
}

template <class T>
void Array<T>::Insert(T InsertNum, int InsertLocate)
{
	for (int i = _size - 1; i > InsertLocate; i--)
	{
		_array[i] = _array[i - 1];
	}
	_array[InsertLocate] = InsertNum;
}

template <class T>
void Array<T>::Remove(int RemoveIndex)
{
	for (int i = RemoveIndex; i < _size; i++)
	{
		_array[i] = _array[i + 1];
	}
}

template <class T>
bool Array<T>::SaveDate(const char *filename)
{
	FILE *fp = fopen(filename, "wb");
	if (NULL == fp)
	{
		return false;
	}

	int Binary = fwrite(_array, sizeof(T), _size, fp);

	fclose(fp);

	if (Binary != _size)
	{
		return false;
	}

	return true;
}

template <class T>
bool Array<T>::LoadDate(const char*filename)
{

	FILE *fp = fopen(filename, "rb");
	if (NULL == fp)
	{
		return false;
	}

	int Binary = fread(_array, sizeof(T), _size, fp);

	fclose(fp);

	if (Binary != _size)
	{
		return false;
	}

	return true;
}

template <class T>
int Array<T>::ReturnSize()
{
	return _size;
}
// 여기까지 복사