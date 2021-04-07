#pragma once

#include <vector>
#include <string>
#include <iostream>

using std::vector;
using std::cout;

/**
 * Storage for arbitrary data.
 *
 * @tparam T the type of data stored in the vector.
 */
template<class T>
class Repository
{
protected:
	vector<T*> repository;
public:
	Repository<T>();
	virtual ~Repository<T>();
	virtual void add(T* object);
	virtual void del(size_t position);
	virtual void update(size_t position, T* newObject);
	size_t getSize();
	vector<T*> getAll();
	void clear();
	T* getObject(size_t position);
};

/**
 * Default constructor.
 *
 * @tparam T the type of data stored in the vector.
 */
template<class T>
Repository<T>::Repository() {}

/**
 * Default destructor.
 *
 * @tparam T the type of data stored in the vector.
 */
template<class T>
Repository<T>::~Repository()
{
	this->clear();
}

/**
 * Adds an object to the vector.
 *
 * @tparam T the type of data stored in the vector.
 * 
 * @param object = T.
 */
template<class T>
void Repository<T>::add(T* object)
{
	bool ok = 1;
	for (size_t i = 0; i < this->repository.size(); i++)
		if (object == this->repository[i])
			ok = 0;

	if (ok == 1)
		this->repository.push_back(object);
	else cout << "Object already exists!" << '\n';
}

/**
 * Removes an object from the vector by its position.
 *
 * @tparam T the type of data stored in the vector.
 *
 * @param position = size_t.
 */
template<class T>
void Repository<T>::del(size_t position)
{
	if (position >= 0 && position <= this->repository.size())
		this->repository.erase(this->repository.begin() + position);
	else
		cout << "Given position is out of bounds!" << '\n';
}

/**
 * Updates an object from the vector by its position.
 *
 * @tparam T the type of data stored in the vector.
 *
 * @param position = size_t, newObject = T.
 */
template<class T>
void Repository<T>::update(size_t position, T* newObject)
{
	if (position >= 0 && position < this->repository.size())
	{
		for (size_t i = 0; i < this->repository.size(); i++)
			if (position == i)
				this->repository[i] = newObject;
	}
	else
		cout << "Given position is out of bounds!" << '\n';
}

/**
 * Returns the size of the vector.
 *
 * @tparam T the type of data stored in the vector.
 *
 * @return size = size_t.
 */
template<class T>
size_t Repository<T>::getSize()
{
	return this->repository.size();
}

/**
 * Returns all elements in the vector.
 *
 * @tparam T the type of data stored in the vector.
 *
 * @return repository = vector<T*>.
 */
template<class T>
vector<T*> Repository<T>::getAll()
{
	return this->repository;
}

/**
 * Empties the vector.
 *
 * @tparam T the type of data stored in the vector.
 */
template<class T>
void Repository<T>::clear()
{
	this->repository.clear();
}

/**
 * Returns an object by its position.
 *
 * @tparam T the type of data stored in the vector.
 *
 * @return position = size_t.
 */
template<class T>
T* Repository<T>::getObject(size_t position)
{
	if (position >= 0 && position < this->repository.size())
		return this->repository[position];
	else
		cout << "Given position is out of bounds!" << '\n';
}