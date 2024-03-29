#pragma once
#define CAPACITATE 2
template<typename TElement>
class Iterator;

template<typename TElement>

class MyList {
private:
	// reprezentare
	TElement* elems;

	int capacitate;

	int lungime;

	// pentru redimensionare
	void redim();

public:
	// constructor default
	MyList();

	// constructor de copiere
	MyList(const MyList& ot);

	// operator de asignare =
	MyList& operator=(const MyList& ot);

	//deconstructor
	~MyList();

	// pastram numele functiilor ca si cele din stl
	// functie de adaugare
	void push_back(TElement e);

	// functie de stergere
	// erase
	// get element de pe o pozitie
	TElement& get(int poz);

	// set element pe o pozitie
	void set(TElement elem, int poz);

	// get-er pentru dimensiune
	int size();

	//iterator
	friend class Iterator<TElement>;

	Iterator <TElement> begin();
	Iterator <TElement> end();

};

template<typename TElement>

class Iterator {
private:
	const MyList<TElement>& vec;

	int poz = 0;

public:
	Iterator(const MyList<TElement>& v) noexcept;

	Iterator(const MyList<TElement>& v, int poz) noexcept;

	bool valid() const;

	TElement& element() const;

	void next();

	TElement& operator*();

	Iterator& operator++();

	bool operator==(const Iterator& ot) noexcept;

	bool operator!=(const Iterator& ot) noexcept;
};

// puteam si intr un program cpp separat sa facem asta

// pentru MyList..................................

