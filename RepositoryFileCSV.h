#pragma once

#include "Repository.h"
#include <string>
#include <fstream>
#include <istream>

using std::string;

/**
 * Derived class from Repository<T>.
 *
 * @tparam T the type of data stored in the vector.
 */
template<class T>
class RepositoryFileCSV : public Repository<T>
{
private:
	string fileName;
public:
	typedef typename std::remove_reference<T>::type V;
	RepositoryFileCSV();
	RepositoryFileCSV(string fileName);
	virtual ~RepositoryFileCSV();
	virtual void loadFromFile();
	virtual void saveToFile();
	void add(T* object);
	void del(size_t position);
	void update(size_t position, T* newObject);
};

/**
 * Default constructor.
 *
 * @tparam T the type of data stored in the vector.
 */
template<class T>
RepositoryFileCSV<T>::RepositoryFileCSV() { this->fileName = ""; }

/**
 * Constructor with a parameter that is the name of the file from where to get and store elements.
 *
 * @tparam T the type of data stored in the vector.
 * 
 * @param fileName = string.
 */
template<class T>
RepositoryFileCSV<T>::RepositoryFileCSV(string fileName)
{
	this->fileName = fileName;
	this->loadFromFile();
}

/**
 * Destructor.
 *
 * @tparam T the type of data stored in the vector.
 */
template<class T>
RepositoryFileCSV<T>::~RepositoryFileCSV()
{
	this->fileName = "";
	Repository<T>::clear();
}

/**
 * Virtual method that loads the elements from the desired file.
 *
 * @tparam T the type of data stored in the vector.
 */
template<class T>
void RepositoryFileCSV<T>::loadFromFile()
{
	Repository<T>::clear();
	string line;
	std::ifstream f(this->fileName);
	while (getline(f, line))
	{
		if (!line.empty())
		{
			V* object = new V(line);
			Repository<T>::add(object);
		}
		else break;
	}
	f.close();
}

/**
 * Virtual method that saves the stored elements to the desired file.
 *
 * @tparam T the type of data stored in the vector.
 */
template<class T>
void RepositoryFileCSV<T>::saveToFile() {

	std::ofstream fout(this->fileName);
	std::vector<T*> localRepository;
	localRepository = Repository<T>::getAll();
	for (auto itr = localRepository.begin(); itr != localRepository.end(); itr++)
	{
		if (itr < localRepository.end() - 1)
			fout << (*itr)->toStringCSV() << '\n';
		else
			fout << (*itr)->toStringCSV();
	}
	fout.close();
}

/**
 * Method that saves the element to the desired file.
 *
 * @tparam T the type of data stored in the vector.
 *
 * @param object = T.
 */
template<class T>
void RepositoryFileCSV<T>::add(T* object)
{

	Repository<T>::add(object);
	this->saveToFile();
}

/**
 * Method that deletes an element at a given position from the desired file.
 *
 * @tparam T the type of data stored in the vector.
 *
 * @param position = size_t.
 */
template <class T>
void RepositoryFileCSV<T>::del(size_t position)
{
	Repository<T>::del(position);
	this->saveToFile();
}

/**
 * Method that updates an element at a given position from the desired file.
 *
 * @tparam T the type of data stored in the vector.
 *
 * @param position = size_t, newObject = T.
 */
template<class T>
void RepositoryFileCSV<T>::update(size_t position, T* newObject)
{
	Repository<T>::update(position, newObject);
	this->saveToFile();
}