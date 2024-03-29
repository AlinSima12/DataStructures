#include "Iterator.h"
#include "LO.h"

#include <iostream>

using namespace std;

Iterator::Iterator(const LO& lo) : lista(lo){
	//BC=AC=WC=Q(1)
	this->curent_nod = this->lista.prim;
}

void Iterator::prim() {
	//BC=AC=WC=Q(n)
	this->curent_nod = this->lista.prim;
}

void Iterator::urmator(){
	//BC=AC=WC=Q(n)
	if (!valid())
		throw bad_exception();
	this->curent_nod = this->curent_nod->urm;
}

bool Iterator::valid() const{
	//BC=AC=WC=Q(n)
	if (this->curent_nod != NULL)
		return true;
	return false;
}

TElement Iterator::element() const{
	//O(n)
	if (this->valid()) {
		return this->lista.element(curent_nod->index);
	}
	return -1;
}


