#include "vector.h"

template<typename TElement>

MyList<TElement>::MyList() {
	this->elems = new TElement[CAPACITATE];
	this->lungime = 0;
	this->capacitate = CAPACITATE;
}

template<typename TElement>

MyList<TElement>::MyList(const MyList& ot) {

	// alocam spatiu
	this->elems = new TElement[ot.capacitate];

	// copiem elmentele
	for (int i = 0; i < ot.lungime; i++) {
		this->elems[i] = ot.elems[i];
	}

	this->capacitate = ot.capacitate;
	this->lungime = ot.lungime;
}

template<typename TElement>

MyList<TElement>& MyList<TElement>::operator=(const MyList& ot) {

	//daca v1=v1
	if (this == &ot) {
		return *this;
	}

	delete[] this->elems;

	this->elems = new TElement[ot.capacitate];
	for (int i = 0; i < ot.capacitate; i++) {
		this->elems[i] = ot.elems[i];
	}

	this->lungime = ot.lungime;
	this->capacitate = ot.capacitate;
	return *this;
}

template<typename TElement>

void MyList<TElement>::redim() {
	int newcapacity = this->capacitate * 2;
	TElement* newElems = new TElement[newcapacity];

	for (int i = 0; i < this->capacitate; i++) {
		newElems[i] = this->elems[i];
	}

	delete[] this->elems;
	this->elems = newElems;
	this->capacitate = newcapacity;
}

template<typename TElement>

MyList<TElement>::~MyList() {
	delete[] this->elems;
}

// adaugare
template<typename TElement>

void MyList<TElement>::push_back(TElement e) {
	if (this->lungime == this->capacitate)
		redim();

	this->elems[this->lungime] = e;
	this->lungime++;
}

template<typename TElement>

TElement& MyList<TElement>::get(int poz) {
	return this->elems[poz];
}

template<typename TElement>

int MyList<TElement>::size() {
	return this->lungime;
}

template<typename TElement>

Iterator<TElement> MyList<TElement>::begin() {
	return Iterator<TElement>(*this);
}
template<typename TElement>

Iterator<TElement> MyList<TElement>::end() {
	return Iterator<TElement>(*this, this->lungime);
}

// pentru iterator...............................
template<typename TElement>

Iterator<TElement>::Iterator(const MyList<TElement>& v) noexcept : vec{ v } {};

template<typename TElement>

Iterator<TElement>::Iterator(const MyList<TElement>& v, int poz) noexcept : vec{ v }, poz{ poz } {};

template<typename TElement>

bool Iterator<TElement>::valid() const {
	return this->poz < this->vec.lungime;
}

template<typename TElement>

TElement& Iterator<TElement>::element() const {
	return this->vec.elems[this->poz];
}

template<typename TElement>

void Iterator<TElement>::next() {
	this->poz++;
}

// operatori

template<typename TElement>

TElement& Iterator<TElement>::operator*() {
	return this->element();
}

template<typename TElement>

Iterator<TElement>& Iterator<TElement>::operator++() {
	this->next();
	return *this;
}

template<typename TElement>

bool Iterator<TElement>:: operator==(const Iterator<TElement>& ot) noexcept {
	return this->poz == ot.poz;
}

template<typename TElement>

bool Iterator<TElement>:: operator!=(const Iterator<TElement>& ot) noexcept {
	return this->poz != ot.poz;
}
