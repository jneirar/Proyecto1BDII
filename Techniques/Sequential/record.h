#ifndef RECORD_H
#define RECORD_H

#include "../lib.h"

template <typename TKey>
class Record
{
    TKey key;
    char nombre[20];
    long next = -1;
    char file = 'd';

public:
    void setData(TKey key)
    {
        this->key = key;
        string nombre = "Alumno " + to_string(key);
        strcpy(this->nombre, nombre.c_str());
        this->next = -1;
        char file = 'd';
    }

    void showData()
    {
        cout << "Key: " << key << "\n";
        cout << "Nombre: " << nombre << "\n";
        cout << "Next : " << next << "\n";
        cout << "NextFile : " << file << "\n\n";
    }
    void setNext(long _next, char _file)
    {
        next = _next;
        file = _file;
    }
    long getNext()
    {
        return next;
    }
    char getFile()
    {
        return file;
    }
    int getKey()
    {
        return key;
    }
    Record &operator=(const Record &a)
    {
        this->key = a.key;
        for (int i = 0; i < 20; i++)
            this->nombre[i] = a.nombre[i];
        this->next = a.next;
        this->file = a.file;
        return *this;
    }
    bool operator<(const Record &a) { return this->key < a.key; }
    bool operator>(const Record &a) { return this->key > a.key; }
    bool operator<=(const Record &a) { return this->key <= a.key; }
    bool operator>=(const Record &a) { return this->key >= a.key; }
    bool operator==(const Record &a) { return this->key == a.key; }
    bool operator!=(const Record &a) { return this->key != a.key; }
};

#endif //RECORD.H