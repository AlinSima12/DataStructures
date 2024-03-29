#include "IteratorColectie.h"
#include "Colectie.h"


IteratorColectie::IteratorColectie(const Colectie& c): col(c) {
	//COMPLEXITATE O(1)
	curent = 0;
}

TElem IteratorColectie::element() const{
	//COMPLEXITATE O(1)
	if(valid())
		return col.e[curent];

	return -1;
}

bool IteratorColectie::valid() const {
	//COMPLEXITATE O(1)
	if (curent < col.dim())
		return true;
	return false;
}

void IteratorColectie::urmator() {
	//COMPLEXITATE O(1)
	curent++;
}

void IteratorColectie::prim() {
	//COMPLEXITATE O(1)
	curent = 0;
}
