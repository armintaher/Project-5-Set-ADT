/*
 * Set ADT
 * Project5.c
 *
 * Armin Mohammadtaher
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
int binarySearch(const Set* set, int num) {
    int min = 0;
    int max = set->len - 1;
    while (max >= min) {
        int mid = min + (max - min) / 2;
        if (set->elements[mid] == num) {
            return mid;
        }
        else if (set->elements[mid] < num) {
            min = mid + 1;
        }
        else {
            max = mid - 1;
        }
    }
    return -1;
}
int log(int l) {
    int x = 0;
    while ((l = l>>1) != 0) {
        x++;
    }
    return x;
}
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
    int n = self->len;
    int* A = self->elements;
    int low = 0, high = n - 1;

    while(low <= high)
    {
        int mid = (low + high)/2;

        if (x == A[mid])
            return true;

        if (A[mid] <= A[high])
        {
            if(x > A[mid] && x <= A[high])
                low = mid + 1;
            else
                high = mid - 1;
        }

        else
        {
            if(x >= A[low] && x < A[mid])
                high = mid - 1;
            else
                low = mid + 1;
        }
    }
    return false;
}

/*
 * add x as a new member to this set.
 * If x is already a member, then self should not be changed
 * Be sure to restore the design invariant property that elemnts[] remains sorted
 * (yes, you can assume it is sorted when the function is called, that's what an invariant is all about)
 */
void insertSet(Set* self, int x) {
    if (!(isMemberSet(self, x))) {
        int* ptr = (int*)realloc(self->elements, (self->len +1) * sizeof(int));
        self->elements = ptr;
        int i = self->len ;
        while ((i > 0) && (x < self->elements[i-1]))
        {
            self->elements[i] = self->elements[i-1];
            i = i - 1;
        }
        self->elements[i] = x;
        self->len++;
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
    int i;
    if ((i = binarySearch(self, x)) == -1) {
        return;
    }
    int* dst = &self->elements[i];
    int* src = (&self->elements[i]) + 1;
    int size = (self->len - i - 1) * sizeof(int);
    memmove(dst, src, size);
    self->len -= 1;

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
    if (self->len != other->len) return false;
    int x;
    for (x = 0; x < self->len; x++) {
        if (self->elements[x] != other->elements[x]) {
            return false;
        }
    }
    return true;
}

/* return true if every element of self is also an element of other */
bool isSubsetOf(const Set* self, const Set* other) {
    if (self->len > other->len) {
        return false;
    }
    int x = 0;
    int y = 0;
    for (; x < self->len; x++) {
        while (1) {
            if (self->elements[x] == other->elements[y]) {
                break;
            }
            if (other->elements[y] > self->elements[x]){
                return false;
            }
            y++;
            if (x == other->len) {
                return false;
            }
        }
    }
    return true;

}

/* done for you */
bool isEmptySet(const Set* self) {
    return self->len == 0;
}

/* remove all elements from self that are not also elements of other */
void intersectFromSet(Set* self, const Set* other) {
    int x = 0;
    int y = 0;
    int z = 0;
    int* ptr = (int*) malloc(self->len * sizeof(int));

    if ((self->len + other->len) < (self->len*log(other->len))) {
        while ((y < self->len) && (z < other->len)) {
            if (self->elements[y] < other->elements[z]) {
                y++;
            } else if (self->elements[y] > other->elements[z]) z++;
            else {
                ptr[x++] = self->elements[y];
                y++;
                z++;
            }
        }
    } else {
        for (z = 0; z < self->len; z++) {
            if (isMemberSet(other, self->elements[z])) {
                ptr[x++] = self->elements[z];
            }
        }
    }
    free(self->elements);
    self->elements = ptr;
    self->len = x;

}

/* remove all elements from self that are also elements of other */
void subtractFromSet(Set* self, const Set* other) {
    int x = 0;
    int y = 0;
    int z = 0;
    int* ptr = (int*) malloc(self->len * sizeof(int));

    if ((self->len + other->len) < (self->len*log(other->len))) {
        while (y < self->len) {
            if (z >= other->len) {
                ptr[x++] = self->elements[y];
                y++;
            } else if (self->elements[y] < other->elements[z]) {
                ptr[x++] = self->elements[y];
                y++;}
              else if (self->elements[y] > other->elements[z]) z++;
            else {
                y++;
                z++;
            }
        }
    } else {
        for (z = 0; z < self->len; z++) {
            if (!isMemberSet(other, self->elements[z])) {
                ptr[x++] = self->elements[z];
            }
        }
    }
    free(self->elements);
    self->elements = ptr;
    self->len = x;
}

/* add all elements of other to self (obviously, without creating duplicate elements) */
void unionInSet(Set* self, const Set* other) {
    int x = 0;
    int y = 0;
    int z = 0;
    int* ptr = (int*) malloc((self->len+other->len) * sizeof(int));
    while (y < self->len || z < other->len) {
        if (y >= self->len) {
            ptr[x++] = other->elements[z];
            z++;
        } else if (z >= other->len) {
            ptr[x++] = self->elements[y];
            y++;
        } else if (self->elements[y] < other->elements[z]) {
            ptr[x++] = self->elements[y];
            y++;
        } else if (self->elements[y] > other->elements[z]) {
            ptr[x++] = other->elements[z];
            z++;
        } else {
            ptr[x++] = self->elements[y];
            y++;
            z++;
        }
    }
    free(self->elements);
    self->elements = ptr;
    self->len = x;
}
