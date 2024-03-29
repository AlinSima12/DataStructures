#include "IteratorMultime.h"
//#include "Multime.h"


void IteratorMultime::deplasare(){
	//O(m)
//gaseste prima lista nevida incepand cu locatia poz din tabela
	while (poz < multime.m && multime.l[poz] == nullptr)
		poz++;
	if (poz < multime.m)
		curent = multime.l[poz];
}

IteratorMultime::IteratorMultime(const Multime& m) : multime(m){
	//O(m)
	poz = 0;
	deplasare();
}


void IteratorMultime::prim() {
	//O(m)
	poz = 0;
	deplasare();
}


void IteratorMultime::urmator() {
	//O(m)
	if (valid()) {
		curent = curent->urm;
		if (curent == nullptr) {
			poz = poz + 1;
			deplasare();
		}
	}
}


TElem IteratorMultime::element() const {
	//Q(1)
	if (valid())
		return curent->e;
	return -1;
}

bool IteratorMultime::valid() const {
	//Q(1)
	return (poz < multime.m) && (curent != nullptr);
}
