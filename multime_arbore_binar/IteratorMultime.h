#pragma once
#include <exception>
#include <stack>
#include "Multime.h"

using std::bad_exception;
using std::stack;

typedef int TElem;

class IteratorMultime
{
private:
	friend class Multime;

	//constructorul primeste o referinta catre Container
	//iteratorul va referi primul element din container
	IteratorMultime(const Multime& m);

	//contine o referinta catre containerul pe care il itereaza
	const Multime& mult;

	// referinta catre primul element din arbore
	int curent;

	// stiva de pointeri la Nod
	stack<int> stiva;

public:

		//reseteaza pozitia iteratorului la inceputul containerului
		void prim();

		//muta iteratorul in container
		// arunca exceptie daca iteratorul nu e valid
		void urmator();

		//verifica daca iteratorul e valid (indica un element al containerului)
		bool valid();

		//returneaza valoarea elementului din container referit de iterator
		//arunca exceptie daca iteratorul nu e valid
		TElem element();
};

