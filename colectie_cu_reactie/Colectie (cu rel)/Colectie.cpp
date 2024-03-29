#include "Colectie.h"
#include "IteratorColectie.h"
#include <iostream>
#include <exception>

using namespace std;

bool rel(TElem e1, TElem e2) {
	//COMPLEXITATE O(1)
	if (e1 <= e2)
		return true;
	return false;
}

Colectie::Colectie() {

	//setam capacitatea
	this->cp = 2;

	//alocam spatiu de memorare pentru vector
	e = new TElem[cp];

	//setam numarul de elemente
	this->n = 0;
}

void Colectie::redim() {
	//COMPLEXITATE O(n)

	//alocam un spatiu de capacitate dubla
	TElem* eNou = new int[2 * cp];

	//copiem vechile valori in noua zona
	for (int i = 0; i < n; i++)
		eNou[i] = e[i];

	//dublam capacitatea
	cp = 2 * cp;

	//eliberam vechea zona
	delete[] e;

	//vectorul indica spre noua zona
	e = eNou;
}

void Colectie::adauga(TElem e) {
	//COMPLEXITATE O(n)
	if (n == cp)
		redim();
	int i = 0;
	while (i < n and rel(this->e[i], e)) {
		i++;
	}

	int cn = n;
	while (cn > i){
		this->e[cn] = this->e[cn - 1];
		cn--;
	}	this->e[i] = e;

	n++;
}


bool Colectie::sterge(TElem e) {
	//COMPLEXITATE O(n)
	int i = 0;
	while (i < n and this->e[i] != e) {
		i++;
	}
	if (this->e[i] == e and i < n) {
		while (i < n-1) {
			this->e[i] = this->e[i + 1];
			i++;
		}
		n--;
		return true;
	}
	return false;
}


bool Colectie::cauta(TElem elem) const {
	//BC: O(1)
	//WC: O(n)
	//AC: O(n)
	int i = 0;
	while (i < n and this->e[i] != elem) {
		i++;
	}
	if (this->e[i] == elem)
		return true;
	return false;
}


int Colectie::nrAparitii(TElem elem) const {
	//BC: O(1)
	//WC: O(n)
	//AC: O(n)
	int i = 0;
	while (i < n and this->e[i] != elem) {
		i++;
	}
	int nr_aparitii = 0;
	while (elem == this->e[i] and i < n) {
		nr_aparitii++;
		i++;
	}
	return nr_aparitii;
}



int Colectie::dim() const {
	//COMPLEXITATE O(1)
	if (this->n != 0)
		return this->n;
	return 0;
}


bool Colectie::vida() const {
	//COMPLEXITATE O(1)
	if (this->n != 0)
		return false;

	return true;
}


IteratorColectie Colectie::iterator() const {
	//COMPLEXITATE O(1)
	return  IteratorColectie(*this);
}


Colectie::~Colectie() {
	//COMPLEXITATE O(1)
	delete[] e;
}

void Colectie::adaugaAparitiiMultiple(int nr, TElem elem) {
	//COMPLEXITATE O(n*nr)
	if (nr < 0) {
		throw bad_exception();
	}
	else {
		while (nr > 0) {
			this->adauga(elem);
			nr--;
		}
	}
}

/*
PSEUDOCOD
Subalgoritm(intreg nr, TElem elem)
	daca nr < 0 atunci
		Throw Exception
	altfel
		CatTimp nr > 0
			adauga(elem)

*/