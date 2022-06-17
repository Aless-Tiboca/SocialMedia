//
// Created by alext on 11/05/2022.
//

#ifndef PROIECTSDA_ARRAY_H
#define PROIECTSDA_ARRAY_H
#include <iostream>

using namespace std;

template<class T> class Array {
private:
    int CAP = 10;
    T* entities;
    int capacity;
    int size;

    void _resize() {
        this->capacity = this->capacity + this->CAP;
        T* newEntities = new T[this->capacity];
        for(int i = 0; i < this->size; i++) {
            newEntities[i] = this->entities[i];
        }
        delete[] this->entities;
        this->entities = newEntities;
    }
public:
    /**
     * Constructor
     */
    Array() {
        this->size = 0;
        this->capacity = CAP;
        entities = new T[this->capacity];
    }

    /**
     * Copy-constructor
     */
    Array(const Array<T> &array) {
        this->capacity = array.capacity;
        this->size = array.size;
        T* newEntities = new T[this->capacity];
        for(int i = 0; i < this->size; i++) {
            newEntities[i] = array[i];
        }
        this->entities = newEntities;
    }

    /**
     * Destructor
     */
    ~Array() {
        delete[] entities;
    }

    /**
     * Size getter
     */
    int getSize() const {
        return this->size;
    }

    /**
     * Capacity getter
     */
    int getCapacity() {
        return this->capacity;
    }

    /**
     * Checks if an array is empty
     * @return: true if the array is empty, false otherwise
     */
    bool empty() {
        return (size == 0);
    }

    /**
     * Clears an array
     */
    void clear() {
        delete[] this->entities;
        this->size = 0;
        this->capacity = CAP;
        this->entities = new T[this->capacity];
    }

    /**
     * Add entity at the end of an array
     * @param entity: T class object
     */
    void pushBack(T entity) {
        if(this->size == this->capacity) {
            _resize();
        }
        this->entities[this->size++] = entity;
    }

    /**
     * Returns and delete the last entity of an array
     * @return: last entity of an array
     */
    T popBack() {
        if(empty()) {
            throw out_of_range("Array is empty!");
        }
        T entity;
        entity = this->entities[--this->size];

        T* newEntities = new T[this->size];
        for(int i = 0; i < this->size; i++) {
            newEntities[i] = this->entities[i];
        }
        delete[] this->entities;

        this->entities = newEntities;

        return entity;
    }

    /**
     * Insert an entity in array at a specified index
     * @param index: position in array
     * @param entity: T class object
     */
    void insert(int index, T entity) {
        if (index < 0 || index > this->size) {
            throw out_of_range("Index out of range!");
        }
        if(this->size == this->capacity) {
            this->_resize();
        }
        T* newEntities = new T[this->capacity];
        for(int i = 0; i < this->size; i++) {
            newEntities[i] = this->entities[i];
        }
        delete[] this->entities;
        for(int i = this->size; i > index; i--) {
            newEntities[i] = newEntities[i-1];
        }
        newEntities[index] = entity;

        this->entities = newEntities;
        this->size++;
    }

    /**
     * Removes entity from array from a specified index
     * @param index: position in array
     */
    void erase(int index) {
        if(empty()) {
            throw out_of_range("Array is empty.");
        }
        if (index < 0 || index >= this->size) {
            throw out_of_range("Index out of range!");
        }

        T* newEntities = new T[this->capacity];
        for(int i = 0; i < this->size; i++) {
            newEntities[i] = this->entities[i];
        }
        delete[] this->entities;

        for(int i = index; i < this->size - 1; i++) {
            newEntities[i] = newEntities[i + 1];
        }

        this->size--;
        this->entities = newEntities;
    }


    /**
     * Show all elements of an array
     */
    void showAll() {
        for(int i = 0; i < this->size; i++) {
            cout << entities[i] << endl;
        }
    }

    /**
     * Array Index Operator
     */
    T& operator[](int index) const {
        return entities[index];
    }

    /**
     * Assignment Operator
     */
    Array<T> &operator=(const Array<T> &aux) {
        this->size = aux.size;
        this->capacity = aux.capacity;
        delete[] this->entities;
        this->entities = new T[this->capacity];
        for(int i = 0; i < this->size; i++) {
            this->entities[i] = aux.entities[i];
        }
        return *this;
    }
};

#endif //PROIECTSDA_ARRAY_H
