#ifndef RECORD_HASH_H
#define RECORD_HASH_H

#include "../lib.h"

template <typename TKey>
class RecordHash{
    TKey key;
    char nombre[20];
public:
    void setData(TKey key){
        this->key = key;
        string nombre = "Alumno " + to_string(key);
        strcpy(this->nombre, nombre.c_str());
    }

    void showData() {
        cout << "\tKey: " << key << "\n";
        cout << "\tNombre: " << nombre << "\n\n";
    }
    TKey getKey() {
        return key;
    }

    RecordHash& operator =(const RecordHash& a){
        this->key = a.key;
        for(int i = 0; i < 20; i++) this->nombre[i] = a.nombre[i];
        return *this;
    }
    bool operator <(const RecordHash& a) { return this->key < a.key; }
    bool operator >(const RecordHash& a) { return this->key > a.key; }
    bool operator <=(const RecordHash& a){ return this->key <= a.key;}
    bool operator >=(const RecordHash& a){ return this->key >= a.key;}
    bool operator ==(const RecordHash& a){ return this->key == a.key;}
    bool operator !=(const RecordHash& a){ return this->key != a.key;}
};


#endif  //RECORD_HASH.H