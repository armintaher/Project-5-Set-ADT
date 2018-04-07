/*
 * Set ADT
 * Project5.c 
 *
 * My Name
 * My Section Time
 * Spring 2017
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "Set.h"
#include <string.h>
/*
 * Several of the required functions have been written already
 * You may use these functions as-is or you may modify them in any way. 
 * Please NOTE, you are responsible for ensuring that the functions work correctly in 
 * your project solution. Just because the function works correctly in my solution does 
 * NOT mean that the function will work correctly in yours. 
 */

/*
 * Design NOTES:
 *
 * The design provided in this starter kit assumes
 * (1) empty sets will be represented with length == 0 and elements == nullptr (i.e., address 0)
 * (2) amortized doubling is not used, and capacity is ignored/unused. Functions should assume that 
 * the amount of storage available in the elements[] array is equal to length
 */


/* done for you already */
void destroySet(Set* self) {
	free(self->elements);
}

/* done for you already */
void createEmptySet(Set* self) {
	self->len = 0;
	self->elements = 0;
}

/* done for you already */
void createSingletonSet(Set* self, int x) {
	self->elements = (int*) malloc(sizeof(int));
	self->elements[0] = x;
	self->len = 1;
}

/* done for you already */
void createCopySet(Set* self, const Set* other) {
	self->elements = (int*) malloc(other->len * sizeof(int));
	for (int k = 0; k < other->len; k += 1) {
		self->elements[k] = other->elements[k];
	}
	self->len = other->len;	
}

/* done for you already */
void assignSet(Set* self, const Set* other) {
	if (self == other) { return; }
	
	destroySet(self);
	createCopySet(self, other);
}

/* return true if x is an element of self */
bool isMemberSet(const Set* self, int x) {
    int mid = self->len / 2;
    while (mid>=1)
    {
        if (self->elements[mid] == x)
            return true;
        if (self->elements[mid] > x) {
            mid = (mid-1)/2;
        }
        else {
            mid = mid + self->len /2;
        }
    }

}

/*
 * add x as a new member to this set. 
 * If x is already a member, then self should not be changed
 * Be sure to restore the design invariant property that elemnts[] remains sorted
 * (yes, you can assume it is sorted when the function is called, that's what an invariant is all about)
 */
void insertSet(Set* self, int x) {
    if (isMemberSet(self, x)) {
        int n = self->len;
        int i;
        for (i = n - 1; (i >= 0 && self->elements[i] > x); i--) {
            self->elements[i + 1] = self->elements[i];

            self->elements[i + 1] = x;
            self->len++;
        }
    }
}

/*
 * don't forget: it is OK to try to remove an element
 * that is NOT in the set.  
 * If 'x' is not in the set 'self', then
 * removeSet should do nothing (it's not an error)
 * Otherwise, ('x' IS in the set), remove x. Be sure to update self->length
 * It is not necessary (nor recommended) to call malloc -- if removing an element means the 
 * array on the heap is "too big", that's almost certainly OK, and reallocating a smaller array 
 * is almost definitely NOT worth the trouble
 */
void removeSet(Set* self, int x) {
    int flag=0;
    for (int i =1; i < self->len; i++){
        if (self->elements[i-1] == x){
            flag = 1;
        }
        if (flag){
            self->elements[i-1] = self->elements[i];
            self->elements[i] = 0;
            self->len --;
        }
    }

}

/* done for you already */
void displaySet(const Set* self) {
	int k;
	
	printf("{");

	if (self->len == 0) { 
		printf("}"); 
	}
	else {
		for (k = 0; k < self->len; k += 1) {
			if (k < self->len - 1) {
				printf("%d,", self->elements[k]);
			} else {
				printf("%d}", self->elements[k]);
			}
		}
	}
}

/* return true if self and other have exactly the same elements */
bool isEqualToSet(const Set* self, const Set* other) {
    if (self->len == other->len) {
        for (int i = 0; (i < self->len) && (self->elements[i] == other->elements[i]); i++) {
            if (i == self->len -1){
                return true;
            }

        }
    }
}

/* return true if every element of self is also an element of other */
bool isSubsetOf(const Set* self, const Set* other) {
    int count =0;
    int j=0;
    if (self->len == 0) return true;
    if (self->len <= other->len ){
        for (int i=0 ; i< self->len ; j++){
            if (self->elements[i] == other->elements[j]){
                count++;
                i++;
            }

        }

    }
    if (count == self->len)return true;

}

/* done for you */
bool isEmptySet(const Set* self) {
	return self->len == 0;
}

/* remove all elements from self that are not also elements of other */
void intersectFromSet(Set* self, const Set* other) {

}

/* remove all elements from self that are also elements of other */
void subtractFromSet(Set* self, const Set* other) {
}

/* add all elements of other to self (obviously, without creating duplicate elements) */
void unionInSet(Set* self, const Set* other) {
}
