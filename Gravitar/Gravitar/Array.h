#pragma once

//Array dinamico simile a std::vector
template <class T>
class Array
{
private:
	T* array_data;
	size_t array_size;
	size_t capacity;

	void grow() {
		if (capacity == 0)
		{
			capacity = 8;
		}
		else
		{
			capacity = capacity * 2;
		}

		T* new_data = new T[capacity];
		for (size_t i = 0; i < array_size; i++)
		{
			new_data[i] = array_data[i];
		}
		delete[] array_data;
		array_data = new_data;
	}

public:
	Array() {
		array_data = NULL;
		array_size = 0;
		capacity = 0;
	}

	~Array() {
		clear();
	}

	Array(Array<T>& other)
	{
		*this = other;
	}

	Array(Array<T>&& other)
	{
		*this = other;
	}

	Array<T>& operator=(const Array<T>& other)
	{
		array_size = other.array_size;
		capacity = other.capacity;
		array_data = new T[capacity];
		for (size_t i = 0; i < array_size; i++)
		{
			array_data[i] = other.array_data[i];
		}

		return *this;
	}

	Array<T>& operator=(Array<T>&& other)
	{
		array_size = other.array_size;
		capacity = other.capacity;
		array_data = other.array_data;

		other.array_data = NULL;
		other.array_size = 0;
		other.capacity = 0;

		return *this;
	}

	void add(const T& item)
	{
		if (array_size >= capacity)
		{
			grow();
		}
		array_data[array_size] = item;
		array_size++;
	}

	void remove(size_t index)
	{
		if (index < array_size)
		{
			for (size_t i = index; i < array_size - 1; i++)
			{
				array_data[i] = array_data[i + 1];
			}
			array_size--;
		}
	}

	size_t size()
	{
		return array_size;
	}

	void clear()
	{
		//se array_data e' NULL delete non fa niente
		delete[] array_data;
		array_data = NULL;
		array_size = 0;
		capacity = 0;
	}

	T& operator[] (size_t index)
	{
		return array_data[index];
	}

	T* data()
	{
		return array_data;
	}
};