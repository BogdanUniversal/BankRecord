#pragma once

#include "RepositoryFileCSV.h"
#include <vector>

/**
 * Derived class from RepositoryFileCSV<Y>.
 *
 * @tparam T the type of data stored in the vector.
 */
template<class T>
class RepositoryFileHTML : public RepositoryFileCSV<T>
{
private:
	string fileName;
public:
	typedef typename std::remove_reference<T>::type V;
	RepositoryFileHTML();
	RepositoryFileHTML(string fileName);
	~RepositoryFileHTML();
	void loadFromFile();
	void saveToFile();
};

/**
 * Default constructor.
 *
 * @tparam T the type of data stored in the vector.
 */
template<class T>
RepositoryFileHTML<T>::RepositoryFileHTML() { this->fileName = ""; }

/**
 * Constructor with a parameter that is the name of the file from where to get and store elements.
 *
 * @tparam T the type of data stored in the vector.
 *
 * @param fileName = string.
 */
template<class T>
RepositoryFileHTML<T>::RepositoryFileHTML(string fileName)
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
RepositoryFileHTML<T>::~RepositoryFileHTML()
{ 
	this->fileName = "";
	Repository<T>::clear();
}

/**
 * Method that loads the elements from the desired file.
 *
 * @tparam T the type of data stored in the vector.
 */
template<class T>
void RepositoryFileHTML<T>::loadFromFile()
{
	Repository<T>::clear();
	string line;
	std::ifstream f(this->fileName);
	while (getline(f, line, '<')) {
		if (line.size() > 1) {
			V* object = new V(line);
			Repository<T>::add(object);
		}
		getline(f, line, '>');
	}
	f.close();
}

/**
 * Method that saves the elements to the desired file.
 *
 * @tparam T the type of data stored in the vector.
 */
template<class T>
void RepositoryFileHTML<T>::saveToFile() 
{
	std::ofstream fout(this->fileName);
	std::vector<T*> localRepository;
	localRepository = Repository<T>::getAll();
	fout << "<!DOCTYPE html>\n";
	fout << "<html>\n";
	fout << "<body>\n";
	for (auto itr = localRepository.begin(); itr != localRepository.end(); itr++) {
		fout << "<p>";
		fout << (*itr)->toStringHTML();
		fout << "</p>\n";
	}
	fout << "</body>\n";
	fout << "</html>\n";

	fout.close();
}

