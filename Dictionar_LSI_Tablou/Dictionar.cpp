#include "Dictionar.h"
#include <iostream>
#include "IteratorDictionar.h"

#include <iostream>
#include <vector>

using namespace std;


Dictionar::Dictionar() {
	//Q(n)
	this->cap = INITIAL_CAPACITY;

	this->elems = new TElem[cap];
	this->urm = new int[cap];


	for (int i = 0; i < this->cap - 1; i++) {
		this->urm[i] = i + 1;
	}
	this->urm[cap - 1] = -1;

	this->prim_elem = -1;

	this->prim_liber = 0;

	this->dimensiune = 0;
}

Dictionar::~Dictionar() {
}

void Dictionar::resize() {
	//BC=AC=WC=Q(n)
		//pt elems
		int newcapacity = this->cap * 2;
		TElem* newElems = new TElem[newcapacity];

		for (int i = 0; i < this->cap; i++) {
			newElems[i] = this->elems[i];
		}

		delete[] this->elems;
		this->elems = newElems;

		//pt urm
		int* newurm = new int[newcapacity];

		for (int i = 0; i < this->cap; i++) {
			newurm[i] = this->urm[i];
		}

		delete[] this->urm;
		this->urm = newurm;
		this->cap = newcapacity;
	this->prim_liber = this->dimensiune;
	for (int i = this->dimensiune; i < this->cap; i++) {
		urm[i] = i + 1;
	}
	this->urm[cap - 1] = -1;
}

bool Dictionar::cauta_add(TCheie c) const {
	//O(n)
	if (!vid()) {
		int poz_curenta = prim_elem;
		while (this->urm[poz_curenta] != -1) {
			if (this->elems[poz_curenta].first == c)
				return true;
			poz_curenta = urm[poz_curenta];
		}
		if (this->elems[poz_curenta].first == c)
			return true;
	}
	return false;
}

TValoare Dictionar::ceaMaiFrecventaValoare()const {
	//BC=AC=WC=Q(n^2)
	std::vector <int> frecvente;
	std::vector <TValoare> elemente;
	if (!vid()) {
		int poz_curenta = prim_elem;
		while (this->urm[poz_curenta] != -1) {
			bool gasit = false;
			for (int i = 0; i < elemente.size(); i++)
				if (elemente[i] == elems[poz_curenta].second)
					frecvente[i]++, gasit = true;
			if (!gasit)
				elemente.push_back(elems[poz_curenta].second), frecvente.push_back(1);
			poz_curenta = urm[poz_curenta];
		}
		for (int i = 0; i < elemente.size(); i++) {
			if (elemente[i] == elems[poz_curenta].second)
				frecvente[i]++;
		}
		poz_curenta = urm[poz_curenta];
	}
	else
		return -1;
	int max = 0, poz_max;
	for (int i = 0; i < elemente.size(); i++) {
		if (frecvente[i] > max)
			max = frecvente[i], poz_max = i;
	}
	return elemente[poz_max];
}

/*PSEUDOCOD
Subalgoritm ceaMaiFrecventaValoare()
	Daca (!vid)
		poz_curenta <- prim_element
		CatTimp urm[poz_curenta] != -1 executa
			Pentru i, 0, elemente.size() executa
				Daca elemente[i] = elems[poz_curenta].second
					frecvente[i] = frecvente[i] + 1
				SfDaca
			SfPentru
			poz_curenta = urm[poz_curenta]
		SfCatTimp
	Altfel
		ceaMaiFrecventaValoare <- -1
	Pentru i, 0, elemente.size() executa
		Daca frecvente[i] > max
			max = frecvente[i]
			poz_max = i
		SfDaca
	SfPentru
	ceaMaiFrecventaValoare<-elemente[poz_max]
*/

TValoare Dictionar::adauga(TCheie c, TValoare v){
	//O(n)
	TValoare ret = NULL_TVALOARE;
	if (this->cauta_add(c) == false) {
		if (!vid()) {
			if (dimensiune == cap) {
				this->resize();
			}
			int aux;
			this->elems[prim_liber] = TElem(c, v);
			aux = this->urm[prim_liber];
			this->urm[prim_liber] = this->prim_elem;
			this->prim_elem = this->prim_liber;
			this->prim_liber = aux;
			this->dimensiune++;
		}
		else {
			this->elems[prim_liber] = TElem(c, v);
			this->prim_elem = this->prim_liber;
			this->prim_liber = this->urm[prim_liber];
			this->urm[prim_elem] = -1;
			this->dimensiune++;
		}
	}
	else {
		int poz_curenta = prim_elem;
		while (this->urm[poz_curenta] != -1) {
			if (this->elems[poz_curenta].first == c) {
				ret = this->elems[poz_curenta].second;
				this->elems[poz_curenta].second = v;
			}
			poz_curenta = this->urm[poz_curenta];
		}
		if (this->elems[poz_curenta].first == c) {
			ret = this->elems[poz_curenta].second;
			this->elems[poz_curenta].second = v;
		}
	}
	return ret;
}



//cauta o cheie si returneaza valoarea asociata (daca dictionarul contine cheia) sau null
TValoare Dictionar::cauta(TCheie c) const{
	//O(n)
	if (!vid()) {
		int poz_curenta = prim_elem;
		while (this->urm[poz_curenta] != -1) {
			if (this->elems[poz_curenta].first == c)
				return this->elems[poz_curenta].second;
			poz_curenta = urm[poz_curenta];
		}
		if (this->elems[poz_curenta].first == c)
			return this->elems[poz_curenta].second;
	}
	return NULL_TVALOARE;
}


TValoare Dictionar::sterge(TCheie c){
	//O(n)
	int poz_curenta = prim_elem;
	if (this->cauta_add(c) == true) {
		if (this->elems[prim_elem].first == c) {
			TValoare ret = NULL_TVALOARE;
			ret = elems[prim_elem].second;
			int aux = prim_liber;
			int aux2 = urm[prim_elem];
			prim_liber = prim_elem;
			urm[prim_liber] = aux;
			prim_elem = aux2;
			this->dimensiune--;
			return ret;
		}
		while (this->urm[poz_curenta] != -1) {
			if (this->elems[this->urm[poz_curenta]].first == c) {
				TValoare ret = NULL_TVALOARE;
				ret = elems[urm[poz_curenta]].second;
				int aux = this->urm[this->urm[poz_curenta]];
				this->urm[this->urm[poz_curenta]] = prim_liber;
				prim_liber = this->urm[poz_curenta];
				urm[poz_curenta] = aux;
				this->dimensiune--;
				return ret;
			}
			poz_curenta = urm[poz_curenta];
		}
	}
	return NULL_TVALOARE;
}


int Dictionar::dim() const {
	//BC=AC=WC=Q(1)
	return this->dimensiune;
}

bool Dictionar::vid() const{
	//BC=AC=WC=Q(1)
	if (dimensiune != 0)
		return false;
	return true;
}


IteratorDictionar Dictionar::iterator() const {
	//BC=AC=WC=Q(1)
	return  IteratorDictionar(*this);
}


