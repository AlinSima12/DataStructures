#include "Multime.h"
#include "IteratorMultime.h"
#include <iostream>

//using namespace std;

//o posibila relatie
bool rel(TElem e1, TElem e2) {
	//Q(1)
	if (e1 <= e2) {
		return true;
	}
	else {
		return false;
	}
}

Multime::Multime() {
	//Q(n)
	this->radacina = -1;	
	this->nrElemente = 0;
	this->dimensiune = MAX;

	this->val = new int[MAX];
	this->st = new int[MAX];
	this->dr = new int[MAX];

	for (int i = 0; i < dimensiune; i++) {
		this->st[i] = i + 1;
	}

	st[dimensiune - 1] = -1;

	this->primLiber = 0;
}

int Multime::adauga_recursiv(int rad, TElem elem, bool& adaugat) {
	//O(n)
	if (rad == -1) {
		rad = primLiber;
		primLiber = st[primLiber];
		val[rad] = elem;
		st[rad] = -1;
		dr[rad] = -1;
		// semnalam adaugarea cu succes a noului nod
		adaugat = true;			
	}
	// daca am gasit un nod cu aceeasi cheie
	// nu mai adaugam alt nod (este o multime)
	else if (elem == val[rad]) {
		adaugat = false;
	}
	else if (rel(elem, val[rad])) {
		st[rad] = adauga_recursiv(st[rad], elem, adaugat);
	}
	else {
		dr[rad] = adauga_recursiv(dr[rad], elem, adaugat);
	}

	return rad;

}


bool Multime::adauga(TElem elem) {
	//O(log(n))
	// o variabila booleana pentru a semnala 
	// adaugarea cu succes sau nu a unui element
	bool adaugat = false;

	// apelam functia recrusiva
	this->radacina = adauga_recursiv(this->radacina, elem, adaugat);

	// daca l am adaugat cu succes
	if(adaugat)
		// crestem numarul de elemente
		this->nrElemente++;

	return adaugat;
}

int Multime::suma() {
	//Q(n)
	return val[radacina] + suma_recursiv(this->radacina);
}
/*
PSEUDOCOD
Subalgoritm
	returneaza val[radacina] + suma_recursiv(radacina)
*/



int Multime::suma_recursiv(int nod_curent) {
	//Q(n)
	if (st[nod_curent] != -1 and dr[nod_curent] != -1)
		return suma_recursiv(st[nod_curent]) + suma_recursiv(dr[nod_curent]);
	else if (st[nod_curent] != -1 and dr[nod_curent] == -1)
		return suma_recursiv(st[nod_curent]) + val[nod_curent];
	else if (dr[nod_curent] != -1 and dr[nod_curent] == -1)
		return suma_recursiv(dr[nod_curent]) + val[nod_curent];
	else if (st[nod_curent] == -1 and dr[nod_curent] == -1)
		return val[nod_curent];
	}

/*
PSEUDOCOD
Subalgoritm
	Daca st[nod_curent] != -1
		returneaza suma_recursiv(st[nod_curent])
	Altfel Daca (st[nod_curent] != -1 si dr[nod_curent] == -1)
		returneaza suma_recursiv(st[nod_curent]) + val[nod_curent];
	Altfel Daca (dr[nod_curent] != -1 si dr[nod_curent] == -1)
		returneaza suma_recursiv(dr[nod_curent]) + val[nod_curent];
	Altfel Daca (st[nod_curent] == -1 si dr[nod_curent] == -1)
		returneaza val[nod_curent];
*/

int Multime::minim(int rad) {
	//Q(1)
	while (st[rad] != -1) {
		rad = st[rad];
	}
	return rad;
}

int Multime::sterge_recursiv(int rad, TElem elem, bool& sters) {
	//O(log(n))
	if (rad == -1) {
		return rad;
	}
	else if (rel(elem, val[rad]) && val[rad] != elem) {
		st[rad] = sterge_recursiv(st[rad], elem, sters);
		return rad;
	}
	else if (!(rel(elem, val[rad])) && val[rad] != elem) {
		dr[rad] = sterge_recursiv(dr[rad], elem, sters);
		return rad;
	}
	// l am gasit	
	else if (st[rad] != -1 && dr[rad] != -1) {
		// suntem cazul in care nodul are subarbore stang si drept

		// determinam minimul din subarborele drept al nodului de sters
		int temp = minim(dr[rad]);

		// se muta cheia in nodul de sters
		val[rad] = val[temp];

		// stergem minimul
		bool nimic = false;
		dr[rad] = sterge_recursiv(dr[rad], val[temp], nimic);

		// semnalam stergerea elementului
		sters = true;

		return rad;
	}
	else {
		int temp = rad;
		int newrad = -1;

		// nu exista subarbore stang
		if (st[temp] == -1) {
			newrad = dr[temp];
		}
		// nu exista subarbore drept
		else {
			newrad = st[temp];
		}

		// semnalam stergerea elementului
		sters = true;

		return newrad;
	}
}

bool Multime::sterge(TElem elem) {
	//O(log(n))
	// o variabila booleana pentru a semnala 
	// stergerea cu succes sau nu a unui element
	bool sters = false;

	// apelam functia recrusiva
	this->radacina = sterge_recursiv(this->radacina, elem, sters);

	// daca a fost sters cu succes
	if (sters)
		// micsoram numarul de elemente
		this->nrElemente--;

	return sters;
}


bool Multime::cauta(TElem elem) const {
	//O(log(n))
	if (vida())
		return false;
	
	int rad = this->radacina;

	while (rad != -1) {
		if (val[rad] == elem) {
			return true;
		}
		if (rel(elem, val[rad]))
			rad = st[rad];
		else
			rad = dr[rad];
	}
	return false;
}


int Multime::dim() const {
	//Q(1)
	return this->nrElemente;
}



bool Multime::vida() const {
	//Q(1)
	if (this->nrElemente == 0)
		return true;

	return false;
}

IteratorMultime Multime::iterator() const {
	//Q(1)
	return IteratorMultime(*this);
}

Multime::~Multime() {
	delete val;
	delete st;
	delete dr;
}






