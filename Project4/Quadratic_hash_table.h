/*****************************************
 * Instructions
 *  - Replace 'uwuserid' with your uWaterloo User ID
 *  - Select the current calendar term and enter the year
 *  - List students with whom you had discussions and who helped you
 *
 * uWaterloo User ID:  uwuserid @uwaterloo.ca
 * Submitted for ECE 250
 * Department of Electrical and Computer Engineering
 * University of Waterloo
 * Calender Term of Submission:  (Winter) 2015
 *
 * By submitting this file, I affirm that
 * I am the author of all modifications to
 * the provided code.
 *
 * The following is a list of uWaterloo User IDs of those students
 * I had discussions with in preparing this project:
 *    -
 *
 * The following is a list of uWaterloo User IDs of those students
 * who helped me with this project (describe their help; e.g., debugging):
 *    -
 *****************************************/

#ifndef DOUBLE_HASH_TABLE_H
#define DOUBLE_HASH_TABLE_H

#ifndef nullptr
#define nullptr 0
#endif

#include "exception.h"
#include "ece250.h"

enum bin_state_t { UNOCCUPIED, OCCUPIED, ERASED };

/*
 *
 */
template <typename Type>
class Quadratic_hash_table {
	
	// member variables
	private:
		const int m = 5;			//
		int count;					// number of elements in the hash
		int power;					// 
		int array_size;				// array size of the hash table
		int mask;
		int erased;
		Type *array;
		bin_state_t *occupied;

	// member functions
	public:
        //constructor
        Quadratic_hash_table();
		Quadratic_hash_table(int m);
    	~Quadratic_hash_table();

		// accessors
		int size() const;
		int capacity() const;
		double load_factor() const;
		bool empty() const;
		bool member(Type const &obj) const;
		int hash( Type const &obj ) const;
		Type bin(int n) const;
		void print() const;

		// mutators
		void insert(Type const &obj);
		bool erase(Type const &obj);
		void clear();


	// Friends

	template <typename T>
	friend std::ostream &operator<<( std::ostream &, Quadratic_hash_table<T> const & );
};

/*********************************************************************
 * ***************************************************************** *
 * *                                                               * *
 * *   Constructor, Copy Constructor, Deconstructor                * *
 * *                                                               * *
 * ***************************************************************** *
 *********************************************************************/

/*
 * Constructor:
 *
 */
template <typename Type>
Quadratic_hash_table<Type>::Quadratic_hash_table(int n):
count( 0 ), power( n ),
array_size( 1 << power ),
mask( array_size - 1 ),
array( new Type[array_size] ),
occupied( new bin_state_t[array_size] ) {

	for ( int i = 0; i < array_size; ++i ) {
		occupied[i] = UNOCCUPIED;
	}
}

/*
 * Constructor:
 *
 */
template <typename Type>
Quadratic_hash_table<Type>::Quadratic_hash_table():
count( 0 ), power( m ),
array_size( 1 << power ),
mask( array_size - 1 ),
array( new Type[array_size] ),
occupied( new bin_state_t[array_size] ) {

	for ( int i = 0; i < array_size; ++i ) {
		occupied[i] = UNOCCUPIED;
	}
}

/*
 * Destructor:
 *
 */
template <typename Type>
Quadratic_hash_table<Type>::~Quadratic_hash_table() {

	delete [] array;
	delete [] occupied;
}

/*********************************************************************
 * ***************************************************************** *
 * *                                                               * *
 * *   Accessors                                                   * *
 * *                                                               * *
 * ***************************************************************** *
 *********************************************************************/

/*
 * Accessor: int size()
 *
 * Returns: number of entities in the hash table
 */
template<typename Type>
int Quadratic_hash_table<Type>::size() const {
	return count;
}

/*
 * Accessor: int capacity()
 *
 * Returns: the capacity of the current array
 */
template<typename Type>
int Quadratic_hash_table<Type>::capacity() const {
	return array_size;
}

/*
 * Accessor: double load_factor()
 *
 * calculates the load factor of hash table and returns it.
 * load factor = (erased +  count) / capacity
 *
 * Returns: 
 */
template<typename Type>
double Quadratic_hash_table<Type>::load_factor() const {
	return (double)(erased + count) / (double)array_size;
}

/*
 * Accessor: bool empty()
 *
 * Returns: true if the hash table has no elements in it
 */
 template<typename Type>
 bool Quadratic_hash_table<Type>::empty() const {
 	return count == 0;
 }

/*
 * Accessor: bool member(Type const &obj)
 * 			 Quadratically probes array for obj
 *
 * Returns: true if the hash table contains the obj
 */
template<typename Type>
bool Quadratic_hash_table<Type>::member(Type const &obj) const {
	// initial bin
	int bin = hash(obj);

	// retrun if matched
	if (array[bin] == obj){
		return true;
	}

	// quadratically probe array for obj
	for (int i = 0; i < capacity(); i++) {
		bin = (bin + i) % capacity();
		if (array[bin] == obj){
			return true;
		}
	}

	// obj not found
	return false;
}

/*
 * Accessor: int hash(Type const &obj)
 *
 * Returns: hash value for obj
 */
template<typename Type>
int Quadratic_hash_table<Type>::hash(Type const &obj) const {
	int i  = static_cast<int>(obj);

	if (i >= 0) {
	 	return i % array_size;
	} else {
		return i % array_size + array_size;
	}
}

/*
 * Accessor: Type bin(int n)
 *
 * Returns: value in bin
 */
template<typename Type>
Type Quadratic_hash_table<Type>::bin(int n) const {
	if (occupied[n] == OCCUPIED) {
		return array[n];
	} else {
		//TODO
        return Type();
	}
}

/*
 * Accessor:
 *
 * Returns: 
 */
template<typename Type>
void Quadratic_hash_table<Type>::print() const {
	//TODO OR NOT TODO
}

/*********************************************************************
 * ***************************************************************** *
 * *                                                               * *
 * *   Mutators                                                    * *
 * *                                                               * *
 * ***************************************************************** *
 *********************************************************************/

/*
 * Method: 
 *
 * Returns: 
 */
template<typename Type>
void Quadratic_hash_table<Type>::insert(Type const &obj) {
	// hash value
	int h = hash(obj);

	//insertion
	switch (occupied[h]) {
		case UNOCCUPIED:
			//insert and set flag
			array[h] = obj;
			occupied[h] = OCCUPIED;
			return;

		case OCCUPIED:
			//quadratically probe for an empty bin
			for (int i = 0; i < capacity(); i++) {
				h = (h + i) % capacity();
				if (occupied[h] == UNOCCUPIED || occupied[h] == ERASED) {
					//insertion
					array[h] = obj;
					occupied[h] = OCCUPIED;
					//update erase count
					if (occupied[h] == ERASED) erased--;
					return;
				}
			}

			//if array is full
			throw overflow();

		case ERASED:
			//insert and set flag
			array[h] = obj;
			occupied[h] = OCCUPIED;
			erased--;
			return;
	}
}

/*
 * Method: 
 *
 * Returns: 
 */
template<typename Type>
bool Quadratic_hash_table<Type>::erase(Type const &obj) {

	//initial bin
	int bin = hash(obj);

	//check initial bin
	if (array[bin] == obj){
		//erase and increment erased
		occupied[bin] = ERASED;
		erased++;
		return true;
	}

	//quadratically probe array for obj
	for (int i = 0; i < capacity(); i++) {
		bin = (bin + i) % capacity();
		if (array[bin] == obj){
			//erase and increment erased
			occupied[bin] = ERASED;
			erased++;
			return true;
		}
	}

	// obj not found
	return false;


}

/*
 * Method: erase contents of the hash table
 *
 * Returns: 
 */
template<typename Type>
void Quadratic_hash_table<Type>::clear() {
	
	//erase all occupied bins
	for (int i = 0; i < capacity(); i++) {
		if (occupied[i] == OCCUPIED) {
			occupied[i] = ERASED;
			erased++;
		}
	}
}

template <typename T>
std::ostream &operator<<( std::ostream &out, Quadratic_hash_table<T> const &hash ) {
	for ( int i = 0; i < hash.capacity(); ++i ) {
		if ( hash.occupied[i] == UNOCCUPIED ) {
			out << "- ";
		} else if ( hash.occupied[i] == ERASED ) {
			out << "x ";
		} else {
			out << hash.array[i] << ' ';
		}
	}

	return out;
}

#endif
