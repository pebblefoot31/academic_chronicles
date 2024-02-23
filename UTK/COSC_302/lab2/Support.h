#ifndef __SUPPORT_H__
#define __SUPPORT_H__
#include <cstdlib>
#include <iostream>
#include <vector>
using namespace std;

template <typename T>
void quicksort(vector<T> &A) { //for the initial call to quicksort on a vector

    quicksort(A, 0, A.size()-1); //call to quicksort considering entire array
}

template <typename T>
void quicksort(vector<T> &A, int left, int right) { 

    if (left < right) { //ensuring that there are at least two elements, since 
						//a list with only one element is already sorted

		// embedding partition logic
        int pindex;
        pindex = left + rand()%((right-left)+1); //choosing a pivot index randomly (% to ensure range)

        T pivot = A[pindex];

        // partition A: {<=}, {pivot}, {=>}
        swap(A[pindex], A[right]);

		///adjusting the sorting range to accomodate for a random pivot
        int i = left-1; 
        int j = right;

        while (1) {

            while (A[++i] < pivot) { } //i scans left-to-right for num > pivot

            while (pivot < A[--j]) { } //j scans right-to-left for num < pivot

            if (i>=j) { //if i and j go past each other (or equal), break
                break;
            }

            swap(A[i], A[j]); //swapping i and j (sorting)
        }

        pindex = i;
        swap(A[pindex], A[right]); //swap the pivot element with the element at i

        quicksort(A, left, pindex-1); //recursive call to quicksort left subarray
        quicksort(A, pindex+1, right); //recursive call to quicksort right subarray

    }

}

template <typename T>
void quickselect(vector<T> &A, int left, int k, int right) { 

    while (1) {


        int pindex;
        pindex = left + rand()%((right-left)+1); //finding the random element
        T pivot = A[pindex];
        
        // partition A: {<=}, {pivot}, {=>} 
		// embedding partition logic
        swap(A[pindex], A[right]);
        
        int i = left-1;
        int j = right;
        
        while (1) {
        
            while (A[++i] < pivot) { } //i scan
        
            while (pivot < A[--j]) { } //j scan
        
            if (i>=j) {
                break;
            }
        
            swap(A[i], A[j]);
        }
        
        pindex = i;
        swap(A[pindex], A[right]);


        if (pindex == k) { //if the pivot index is the index we want to sort, break (just sorted)
            return;
        }

        if (k < pindex) { //if the desired index is less than pivot index- narrow down the left subarray
            right = pindex-1;
        }

        else { //if desired index is greater than pivot- index narrows in on right subarray
               left = pindex+1;
        }

    }
}

#endif // __SUPPORT_H__
