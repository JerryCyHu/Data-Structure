#ifndef __jagged_array_h_
#define __jagged_array_h_
#include <iostream>
#include <fstream>
#include<iomanip>
#include<cmath>      
#include<cstdlib>
#include<fstream>
#include<string>
#include<vector>
#include <iterator>
#include<algorithm>
using namespace std;
template <class T>
class JaggedArray
{
public:
	//constructor
	JaggedArray(int num) {
		num_elements = 0;
		num_bins = num;
		counts = new int[num];
		unpacked_values = new T*[num];
		for (int i = 0; i < num; i++) {
			unpacked_values[i] = new T[1];
			unpacked_values[i][0] = NULL;
			counts[i] = 0;
		}
		is_packed = false;
		offsets = NULL;
		packed_values = NULL;
	}

	//copy constructor
	JaggedArray(JaggedArray& s) {
		if (s.is_packed == false) {
			num_elements = s.numElements();
			num_bins = s.numBins();
			counts = new int[s.numBins()];
			unpacked_values = new T * [s.numBins()];
			for (int i = 0; i < s.numBins(); i++) {
				unpacked_values[i] = new T[s.numElementsInBin(i)];
				for (int q = 0; q < s.numElementsInBin(i); q++) {
					unpacked_values[i][q] = s.getElement(i, q);
				}
				counts[i] = s.numElementsInBin(i);
			}
			is_packed = false;
			offsets = NULL;
			packed_values = NULL;
		}
		else
		{
			num_elements = s.numElements();
			num_bins = s.numBins();
			counts = NULL;
			unpacked_values = NULL;
			is_packed = true;
			offsets = new int[s.numBins()];
			packed_values = new T[s.numElements()];
			for (int i = 0; i < s.numBins(); i++)
			{
				offsets[i] = s.returnoffsets(i);
			}
			for (int i = 0; i < s.numElements(); i++)
			{
				packed_values[i] = s.returnpackedvalue(i);
			}
		}
	}

	//return the exact thing stored in the specific index in the offsets.
	int returnoffsets(int i) {
		if (is_packed) {
			return offsets[i];
		}
	}

	//return the exact thing stored in the specific index in the packed array.
	T returnpackedvalue(int i) {
		if (is_packed) {
			return packed_values[i];
		}
	}

	//rewrite "=" operator.
	void operator=(JaggedArray& s) {
		if (is_packed == false) {
			for (int i = 0; i < num_bins; i++) {
				delete[] unpacked_values[i];
			}
		}
		delete[] unpacked_values;
		delete[] counts;
		delete[] packed_values;
		delete[] offsets;

		if (s.is_packed == false) {
			num_elements = s.numElements();
			num_bins = s.numBins();
			counts = new int[s.numBins()];
			unpacked_values = new T * [s.numBins()];
			for (int i = 0; i < s.numBins(); i++) {
				unpacked_values[i] = new T[s.numElementsInBin(i)];
				for (int q = 0; q < s.numElementsInBin(i); q++) {
					unpacked_values[i][q] = s.getElement(i, q);
				}
				counts[i] = s.numElementsInBin(i);
			}
			is_packed = false;
			offsets = NULL;
			packed_values = NULL;
		}
		else
		{
			num_elements = s.numElements();
			num_bins = s.numBins();
			counts = NULL;
			unpacked_values = NULL;
			is_packed = true;
			offsets = new int[s.numBins()];
			packed_values = new T[s.numElements()];
			for (int i = 0; i < s.numBins(); i++)
			{
				offsets[i] = s.returnoffsets(i);
			}
			for (int i = 0; i < s.numElements(); i++)
			{
				packed_values[i] = s.returnpackedvalue(i);
			}
		}
	}

	//return number of bins
	int numBins() {
		return num_bins;
	};

	//return number of elements
	int numElements() {
		return num_elements;
	}

	//return whether the vector is in packed mode.
	bool isPacked() {
		return is_packed;
	}

	//packing the vector.
	void pack() {
		if (is_packed == false) {
			is_packed = true;
			packed_values = new T[num_elements];
			int counter = 0;
			offsets = new int[num_bins];
			offsets[0] = 0;
			for (int iBin = 0; iBin < num_bins; iBin++) {
				if (counts[iBin] != 0) {
					for (int iElement = 0; iElement < counts[iBin]; iElement++) {
						packed_values[counter] = unpacked_values[iBin][iElement];
						counter++;
					}
				}
				if (iBin != 0) {
					if (iBin == num_bins - 1) {
						offsets[iBin] = num_elements - counts[num_bins - 1];
					}
					else {
						offsets[iBin] = offsets[iBin - 1] + counts[iBin - 1];
					}
				}
			}
			for (int i = 0; i < num_bins; i++) {
				delete[] unpacked_values[i];
			}
			delete[] unpacked_values;
			unpacked_values = NULL;
			delete[] counts;
			counts = NULL;
		}
		else
		{
			cerr << "it's already packed";
			exit(1);
		}
	}

	//unpack the vector
	void unpack() {
		if (is_packed == true) {
			unpacked_values = new T * [num_bins];
			counts = new int[num_bins];
			for (int i = 0; i < num_bins; i++) {
				counts[i] = 0;
			}
			for (int i = 0; i < num_bins; i++) {
				if (i != num_bins - 1) {
					counts[i] = offsets[i + 1] - offsets[i];
				}
				else
				{
					counts[i] = num_elements - offsets[i];
				}
			}
			for (int i = 0; i < num_bins; i++) {
				if (counts[i] != 0) {
					unpacked_values[i] = new T[counts[i]];
				}
				else
				{
					unpacked_values[i] = new T[1];
				}
				unpacked_values[i][0] = NULL;
			}
			int a = 0;
			for (int i = 0; i < num_bins; i++)
			{
				for (int q = a; q < a + counts[i]; q++) {
					unpacked_values[i][q - a] = packed_values[q];
				}
				a += counts[i];
			}
			delete[] packed_values;
			packed_values = NULL;
			delete[] offsets;
			offsets = NULL;
			is_packed = false;
		}
		else
		{
			cerr << "it's already unpacked";
			exit(1);
		}
	}

	//add element to specific bin
	void addElement(int indexOfBin, T obj) {
		if (indexOfBin < num_bins && indexOfBin >= 0 &&is_packed == false) {
			if (counts[indexOfBin] == 0) {
				unpacked_values[indexOfBin][0] = obj;
				counts[indexOfBin]++;
				num_elements++;
			}
			else
			{
				int length = counts[indexOfBin];
				T* value = new T[length + 1];
				for (int i = 0; i < length; i++) {
					value[i] = unpacked_values[indexOfBin][i];
				}
				value[length] = obj;
				delete[] unpacked_values[indexOfBin];
				unpacked_values[indexOfBin] = value;
				counts[indexOfBin]++;
				num_elements++;
			}
		}
		else {
			cerr << "invalid index or vector is packed\n";
			exit(1);
		}
	}

	//print the vactor.
	void print() {
		if (is_packed == false) {
			for (int i = 0; i < num_bins; i++)
			{
				cout << "|";
				for (int q = 0; q < numElementsInBin(i); q++) {
						cout << unpacked_values[i][q];
					
				}
				if (numElementsInBin(i) == 0) {
					cout << "NULL";
				}
			}
			cout << "|";
			cout << endl;
		}
		else
		{
			for (int i = 0; i < num_elements; i++) {
				cout << packed_values[i];
			}
			cout << endl;
		}
	}

	//return number of elements inside a specific bin.
	int numElementsInBin(int n) {
		if (0 <= n && n < num_bins) {
			if (is_packed == false) {
				return counts[n];
			}
			else {
				if (n == num_bins - 1) {
					return num_elements - offsets[n];
				}
				else
				{
					return offsets[n + 1] - offsets[n];
				}
			}
		}
		else
		{
			cerr << "invalid index\n";
			exit(1);
			return 0;
		}
	}

	//remove specific element in a specific bin by index.
	void removeElement(int bin, int element) {
		if (!is_packed) {
			int length = counts[bin];
			T* value = new T[length - 1];
			int a = 0;
			for (int i = 0; i < length; i++) {
				if (i != element) {
					value[a] = unpacked_values[bin][i];
					a++;
				}
			}
			delete[] unpacked_values[bin];
			unpacked_values[bin] = value;
			counts[bin]--;
			num_elements--;
		}
		else
		{
			cerr << "vector is not in packed mode";
			exit(1);
		}
	}

	//clear the vector(only unpacked mode).
	void clear() {
		if (is_packed == false) {
			for (int i = 0; i < num_bins; i++) {
				delete[] unpacked_values[i];
			}
			for (int i = 0; i < num_bins; i++) {
				unpacked_values[i] = new T[1];
				unpacked_values[i][0] = NULL;
				counts[i] = 0;
			}
			num_elements = 0;
		}
		else {
			cerr << "vector must be unpacked";
			exit(1);
		}
	}

	//get element in a specific bin by index.
	T getElement(int indexBin, int indexElement) {
		if (is_packed == false) {
			if (0 <= indexBin && indexBin < num_bins && indexElement >= 0 && indexElement < counts[indexBin]) {
				return unpacked_values[indexBin][indexElement];
			}
			else
			{
				cerr << "invalid index of bin or element";
				exit(1);
				return NULL;
			}
		}
		else
		{
			if (indexBin >= 0 && indexBin < num_bins&&indexElement>=0&& (indexBin == num_bins - 1 && indexElement < num_elements - offsets[indexBin]) || (indexElement<offsets[indexBin+1]-offsets[indexBin]  )) {
				int numEleHaveRead = 0;
				for (int i = 1; i <= indexBin; i++)
				{
					numEleHaveRead += offsets[i] - offsets[i - 1];
				}
				int realIndex = numEleHaveRead + indexElement;
				return packed_values[realIndex];
			}
			else
			{
				cerr << "invalid index of bin or element";
				exit(1);
				return NULL;
			}
		}
	}

	//destructor
	~JaggedArray() {
		if (is_packed == false) {
			for (int i = 0; i < num_bins; i++) {
				delete[] unpacked_values[i];
			}
		}
		delete[] unpacked_values;
		delete[] counts;
		delete[] packed_values;
		delete[] offsets;
	}

private:
	int num_elements;//number of elements in total
	int num_bins;//number of bins in total
	int *counts;//counters in unpacked mode
	T **unpacked_values;//storing arrays in unpacked mode
	int *offsets;//counters in packed mode
	T *packed_values;//storing arrays in packed mode
	bool is_packed;//packing status
};


#endif