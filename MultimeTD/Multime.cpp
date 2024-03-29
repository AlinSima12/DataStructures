#include "Multime.h"
#include "IteratorMultime.h"

#include <iostream>

using namespace std;
Nod::Nod(TElem _e, PNod _urm) {
	//Q(1)
	this->e = _e;
	this->urm = _urm;
}

Multime::Multime() {
	//Q(m)
	this->m = MAX;
	for (int i = 0; i < m; i++) {
		l[i] = nullptr;
	}
	this->dimensiune = 0;
}

int Multime::d(TElem e) const{
	//Q(1)
	return abs(e % m);
}

bool Multime::adauga(TElem elem) {
	//Q(1)
	if (!cauta(elem)) {
		PNod curent = l[d(elem)];
		PNod nod_nou = new Nod(elem, curent);
		l[d(elem)] = nod_nou;
		this->dimensiune++;
		return true;
	}
	return false;
}


bool Multime::sterge(TElem elem) {
	//O(m)
	if (cauta(elem)) {
		PNod curent = l[d(elem)];
		PNod fcurent = curent;

		if (curent->e == elem) {
			l[d(elem)] = curent->urm;
			this->dimensiune--;
			return true;
		}

		curent = curent->urm;

		while (curent != nullptr) {
			if (curent->e == elem) {
				fcurent->urm = curent->urm;
			}
			fcurent = curent;
			curent = curent->urm;
		}
		this->dimensiune--;
		return true;
	}
	return false;
}


bool Multime::cauta(TElem elem) const {
	//O(m)
	PNod curent = l[d(elem)];
	//cout << d(elem);
	while (curent != nullptr) {
		if (curent->e == elem)
			return true;
		curent = curent->urm;
	}
	return false;
}

int Multime::diferentaMaxMin() {
	//Q(n)
	if (vida())
		return -1;
	else {
		PNod curent;
		int minim = INT_MAX;
		int maxim = -INT_MAX;
		for (int i = 0; i < m; i++) {
			curent = l[i];
			while (curent != nullptr) {
				if (curent->e < minim)
					minim = curent->e;
				if (curent->e > maxim)
					maxim = curent->e;
				curent = curent->urm;
			}
		}
		return maxim - minim;
	}
}

/*
PSEUDOCOD
Subalgoritm
	Daca vida() == true
		returneaza -1
	Altfel
		minim <- INF
		maxim <- -INF
		Pentru  i = 0, m executa
			curent <- l[i]
			CatTimp curent != NILL
				Daca curent->e < minim
					minim <- curent->e
				SfDaca
				Daca curent->e < maxim
					maxim <- curent->e
				SfDaca
				curent <- curent->urm
			SfCatTimp
		SfPentru
	SfDaca
SfSubalgoritm
*/


int Multime::dim() const {
	//Q(1)
	return dimensiune;
}

bool Multime::vida() const {
	//Q(1)
	if (dimensiune != 0)
		return false;
	return true;
}


Multime::~Multime() {
}



IteratorMultime Multime::iterator() const {
	return IteratorMultime(*this);
}

