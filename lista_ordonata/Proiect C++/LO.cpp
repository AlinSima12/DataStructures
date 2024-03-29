#include "Iterator.h"
#include "LO.h"

#include <iostream>
using namespace std;

#include <exception>

LO::LO(Relatie r) {
	//BC=AC=WC=Q(1)
	this->r = r;

	this->dimensiune = 0;
	
	this->prim = NULL;

}

// returnare dimensiune
int LO::dim() const {
//BC=AC=WC=Q(1)
	return this->dimensiune;
}

// verifica daca LO e vida
bool LO::vida() const {
//BC=AC=WC=Q(1)
	if (dim() != 0)
		return false;
	return true;
}

// returnare element
//arunca exceptie daca i nu e valid
TElement LO::element(int i) const{
	//O(n)
	if (i < 0 or i >= dimensiune)
		throw bad_exception();

	Nod* curent = this->prim;

	while (curent->index != i) {
		curent = curent->urm;
	}

	return curent->e;
}

// sterge element de pe o pozitie i si returneaza elementul sters
//arunca exceptie daca i nu e valid
TElement LO::sterge(int i) {
	//O(n)
	if (i < 0 or i >= dimensiune)
		throw bad_exception();
	Nod* curent = this->prim;
	Nod* nod_sters = this->prim;
	Nod* fost_curent = this->prim;
	if (dimensiune == 1) {
		nod_sters = prim;
		prim = NULL;
	}
	else if (dimensiune == 2 and i == 0) {
		nod_sters = prim;
		prim = prim->urm;
		prim->index = 0;
	}
	else {
		if (i == 0) {
			nod_sters = prim;
			prim = prim->urm;
			prim->index = 0;
			curent = prim->urm;
		}
		while (curent->index < dimensiune - 1) {
			if (curent->index < i) {
				fost_curent = curent;
			}
			else if (curent->index == i) {
				nod_sters = curent;
				fost_curent->urm = curent->urm;
			}
			else {
				curent->index--;
			}

			curent = curent->urm;
		}
		if (curent->index == i) {
			nod_sters = curent;
			fost_curent->urm = curent->urm;
		}
		else {
			curent->index--;
		}
	}
	TElement de_returnat = nod_sters->e;
	delete nod_sters;
	dimensiune--;
	return de_returnat;
}

// cauta element si returneaza prima pozitie pe care apare (sau -1)
int LO::cauta(TElement e) const {
	//O(n)
	Nod* curent = this->prim;
	int i = 0;
	if (dimensiune > 0) {
		while (curent->index < dimensiune - 1 and r(curent->e, e)) {
			if (curent->e == e) {
				return curent->index;
			}
			curent = curent->urm;
		}
		if (curent->e == e) {
			return curent->index;
		}
	}
	return -1;
}

int LO::ultimulIndex(TElement e) const {
	//BC=AC=WC=Q(n)
	Nod* curent = this->prim;
	int i = 0, ret = -1;
	if (!vida()) {
		while (curent->index < dimensiune - 1) {
			if (curent->e == e) {
				ret = curent->index;
			}
			curent = curent->urm;
		}
		if (curent->e == e) {
			ret =  curent->index;
		}
	}
	return ret;
}
/*PSEUDOCOD
* Subalgoritm ultimulIndex(TElement e (i))
	Daca (!vida)
		CatTimp curent.index < dimensiune - 1 executa
			Daca curent.e == e 
				ret <- curent.index
			SfDaca
			curent = curent.urm
		SfCatTimp
		Daca curent.e == e
			ret = curent.index
		SfDaca
	SfDaca
	ultimIndex <- ret
SfSubalgoritm
*/

// adaugare element in LO
void LO::adauga(TElement e) {
	//BC=AC=WC=Q(n)
	Nod* nod_nou = new Nod;
	Nod* curent = this->prim;
	Nod* fost_curent = this->prim;
	bool gasit = false;
	nod_nou->e = e;
	nod_nou->urm = NULL;

	if (vida()) {
		this->prim = nod_nou;
		nod_nou->index = 0;
		this->prim->urm = NULL;
	}
	else {
		if (!r(curent->e, e)) {
			gasit = true;
			nod_nou->urm = prim;
			nod_nou->index = 0;
			prim = nod_nou;
			curent = prim->urm;
		}
		while (curent->index < dimensiune - 1) {
			if (r(curent->e, e)) {
				fost_curent = curent;
			}
			else if (!r(curent->e, e) and !gasit) {
				nod_nou->urm = fost_curent->urm;
				nod_nou->index = fost_curent->index + 1;
				fost_curent->urm = nod_nou;
				gasit = true;
				curent->index++;
			}
			else {
				curent->index++;
			}

			curent = curent->urm;
		}
		if (gasit) {
			curent->index++;
		}
		if (r(curent->e, e) and !gasit) {
			curent->urm = nod_nou;
			nod_nou->index = curent->index + 1;
		}
		else if (!r(curent->e, e) and !gasit) {
			nod_nou->urm = fost_curent->urm;
				nod_nou->index = fost_curent->index + 1;
				fost_curent->urm = nod_nou;
				gasit = true;
				curent->index++;
		}
	}
	dimensiune++;
}

// returnare iterator
Iterator LO::iterator(){
	//BC=AC=WC=Q(1)
	return Iterator(*this);
}


//destructor
LO::~LO() {
}
