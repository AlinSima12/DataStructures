#pragma once

using namespace std;

#define MAX 60000

typedef int TElem;

typedef bool(*Relatie)(TElem, TElem);

//in implementarea operatiilor se va folosi functia (relatia) rel (de ex, pentru <=)
// va fi declarata in .h si implementata in .cpp ca functie externa colectiei
bool rel(TElem, TElem);

class IteratorMultime;

class Multime {
public:
	friend class IteratorMultime;

	int radacina;

	int nrElemente;

	TElem* val;
	int* st;
	int* dr;

	int dimensiune;

	int primLiber;

	int adauga_recursiv(int rad, TElem elem, bool& adaugat);

	int suma_recursiv(int nod_curent);

	int sterge_recursiv(int rad, TElem elem, bool& sters);

	int minim(int rad);

	//constructorul implicit
	Multime();

	//adauga un element in multime
	//returneaza adevarat daca elementul a fost adaugat (nu exista deja in multime)
	bool adauga(TElem e);

	int suma();

	//sterge un element din multime
	//returneaza adevarat daca elementul a existat si a fost sters
	bool sterge(TElem e);

	//verifica daca un element se afla in multime
	bool cauta(TElem elem) const;


	//intoarce numarul de elemente din multime;
	int dim() const;

	//verifica daca multimea e vida;
	bool vida() const;

	//returneaza un iterator pe multime
	IteratorMultime iterator() const;

	// destructorul multimii
	~Multime();

};

