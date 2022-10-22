#include <stdlib.h>
#include <string.h>
#include "array.h"

/// @brief Function to call to init an dynamic array.
/// @brief Note that you will need to free the memory by calling the arr_free() function.
/// @param data_size Pass the size of the data to store with sizeof.
/// @return A pointer to a dynamic array or NULL if the function failed. 
array* arr_init(size_t data_size) {
    array* temp = NULL;
    temp = malloc(sizeof *temp);
    if(temp == NULL) return NULL; ///Error to handle in the caller function
    temp->arr = NULL;
    temp->data_size = data_size;
    temp->length = 0;
    return temp;
}

/// @brief Function to get the length of a dynamic array.
/// @param arr The array we want the length from.
/// @return The length of the array pass in parameter. Return -1 if the array is NULL.
size_t arr_lenght(array* arr) {
    if(arr == NULL) return -1; /// Just in case the arr variable has not been initialized
    return arr->length;
}

/// @brief Function to get the front value of an array.
/// @param arr The array we want to get the front value from.
/// @return return the front value of the array. Return NULL if the array is NULL.
void* arr_front(array* arr) {
    if(arr == NULL) return NULL; /// Just in case the arr variable has not been initialized
    return (char*)(arr->arr);
}

/// @brief Function to get the end value of an array.
/// @param arr The array we want to get the front value from.
/// @return return the front value of the array. Return NULL if the array is NULL.
void* arr_end(array* arr) {
    if(arr == NULL) return NULL; /// Just in case the arr variable has not been initialized
    return (char*)(arr->arr) + ((arr->length - 1) * arr->data_size);
}

/// @brief Push a value at the end of the array.
/// @param arr The array where the value need to be inserted.
/// @param elem The new element to insert.
/// @return true on success. false on realloc failed.
bool arr_push_back(array* arr, void* elem) {
    void* temp = NULL;
    temp = realloc(arr->arr, arr->data_size * (arr->length + 1));
    if(temp == NULL) return false; ///Error to handle in the caller function
    arr->arr = temp;
    memcpy(((char*) arr->arr) + (arr->length) * arr->data_size, elem, arr->data_size); ///Add the new elem
    arr->length = arr->length + 1;
    return true;
}

/// @brief Pop a value at the end of the array.
/// @param arr The array wher the value need to be removed.
/// @return pointer toward the data at the last place in the array. Handle the memory with this pointer. Return NULL on error.
void* arr_pop_back(array* arr) {
    void* temp = NULL;
    void* data = NULL;
    if(arr == NULL) return NULL; 
    if(arr->length == 0) return NULL; 
    data = arr_end(arr); ///Store the data to not loose it
    temp = realloc(arr->arr, (arr->length - 1) * arr->data_size);
    if(temp == NULL) return NULL; ///Error to handle in the caller function
    arr->arr = temp;
    arr->length = arr->length - 1;
    return data;
}

/// @brief Function to insert a new element at a given index. Since all the values after the index need to be shifted the complexity is O(n)
/// @param arr The array where the new elem need to be inserted.
/// @param index The index where the elem need to be inserted.
/// @param elem The new element to be inserted.
/// @return false on error. true on success. 
bool arr_insert(array* arr, int index, void* elem) {
    if(index > arr->length) return false;

    void* temp = NULL;
    temp = realloc(arr->arr, (arr->length + 1) * arr->data_size);
    if(temp == NULL) return false; ///Error to handle in the caller

    for(int j=index; j<arr->length; j++) { ///Shifting the value to created the space where the new item will be inserted
        void* after = ((char*) temp) + (j+1) * arr->data_size;
        void* before = ((char*) temp) + (j) * arr->data_size;
        memcpy(after, before, arr->data_size);
    }
    memcpy(((char*) temp) + (index) * arr->data_size, elem, arr->data_size);
    arr->arr = temp;
    arr->length += 1;
    return true;
}

/// @brief Function to erase an element at a given index. Since all the values after the index need to be shifted the complexity is O(n)
/// @param arr The array where the new elem need to be erased.
/// @param index The index where the elem need to be erased.
/// @return the data store at the index. Handle the memory yourself. Return NULL on error.
void* arr_erase(array* arr, int index) {
    if(arr->length == 0) return NULL;
    if(index < arr->length && index > 0) return NULL;

    void* temp = NULL;
    void* data = NULL;
    temp = realloc(arr->arr, (arr->length - 1) * arr->data_size);
    if(temp == NULL) return NULL;

    for(int j=index; j<arr->length-1; j++) {
        void* after = ((char*) arr->arr) + (j+1) * arr->data_size;
        void* before = ((char*) temp) + (j) * arr->data_size;
        memcpy(before, after, arr->data_size);
    }
    data = ((char*) temp) + (index) * arr->data_size;
    arr->arr = temp;
    arr->length -= 1;
    return data;
}

void arr_swapp(array* arr1, array* arr2);

/// @brief Function to make the array empty. Warning it does not handle the memory inside the array. Handle it yourself.
/// @param arr The array which need to be empty.
void arr_empty(array* arr) {
    arr->length = 0;
}

/// @brief Function to test if an array is empty.
/// @param arr The array to test.
/// @return true if empty.
bool arr_is_empty(array* arr) {
    return (arr->length == 0);
}

/// @brief Function to create an array from a array or list initializer. {...}, [...].
/// @param arr An array of values. To create from a list initializer please cast it to (type[]).
/// @param len The number of values.
/// @param type_size the size of the type of the array. Use sizeof
/// @return A pointer to the created array. Call arr_free() to free the memory.
array* linkedList_create_from_list(void* arr, int len, size_t type_size) {
    array* temp = arr_init(type_size);
    if(temp == NULL) return NULL;
    for(int i=1; i<len; i++) {
        arr_push_back(arr, (((char*)arr) + (i) * temp->data_size));
    }
    return temp;
}

/// @brief Function to free an array.
/// @param arr The array to be free.
void arr_free(array *arr) {
    free(arr);
}

/// @brief Function to get an element from an array at a given index.
/// @param arr The array to retrieve the element from.
/// @param index The index of the element to retrieve inside the array.
/// @return a pointer toward the data store at the given index. Return NULL in case of an error.
void* arr_get(array* arr, int index) {
    if(arr_is_empty(arr)) return NULL;
    if(index > arr_lenght(arr) || index < 0) return NULL;
    return ((char*) arr->arr) + (index) * arr->data_size;
}