#include "IteratorMultime.h"
#include "Multime.h"


IteratorMultime::IteratorMultime(const Multime& m) : mult(m) {
	prim();
}

// inordine

TElem IteratorMultime::element() {
	//Q(1)
	if (!valid())
		throw bad_exception();

	return mult.val[this->curent];
}

bool IteratorMultime::valid() {
	//Q(1)
	if (this->curent != -1)
		return true;

	return false;
}

void IteratorMultime::urmator() {
	//O(log(n))
	if (!valid())
		throw bad_exception();

	int nod = this->stiva.top();
	this->stiva.pop();

	if (mult.dr[nod] != -1) {
		nod = mult.dr[nod];
		while (nod != -1) {
			this->stiva.push(nod);
			nod = mult.st[nod];
		}
	}

	if (!this->stiva.empty()) {
		this->curent = this->stiva.top();
	}
	else {
		this->curent = -1;
	}
}

void IteratorMultime::prim() {
	//O(log(n))
	this->curent = mult.radacina;
	while (!this->stiva.empty())
		this->stiva.pop();

	while (this->curent != -1) {
		this->stiva.push(this->curent);
		this->curent = mult.st[this->curent];
	}

	if (!this->stiva.empty())
		this->curent = this->stiva.top();
	else
		this->curent = -1;
}

