#include "IteratorDictionar.h"
#include "Dictionar.h"

#include <exception>

using namespace std;
using std::bad_exception;

IteratorDictionar::IteratorDictionar(const Dictionar& d) : dict(d){
	//BC=AC=WC=Q(1)
	this->poz_curenta = dict.prim_elem;
}


void IteratorDictionar::prim() {
	//BC=AC=WC=Q(1)
	this->poz_curenta = dict.prim_elem;
}


void IteratorDictionar::urmator() {
	//BC=AC=WC=Q(1)
	if (valid()) {
		this->poz_curenta = dict.urm[poz_curenta];
	}
	else
		throw bad_exception();
}


TElem IteratorDictionar::element() const{
	//BC=AC=WC=Q(1)
	if (valid()) {
		return dict.elems[poz_curenta];
	}
	else {
		throw bad_exception();
	}
	return pair <TCheie, TValoare>  (-1, -1);
}


bool IteratorDictionar::valid() const {
	//BC=AC=WC=Q(1)
	if (poz_curenta != -1)
		return true;
	return false;
}

