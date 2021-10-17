#ifndef RECORD_HASH_H
#define RECORD_HASH_H

#include "../lib.h"

template <typename TKey>
class RecordHash
{
    TKey key;
    char nombre[20];
    char brand[20];
    char style[20];
    char country[20];
    char stars[20];
    
//Review,Brand,Style,Country,Stars
public:
    void setData(TKey key, string _brand, string _style, string _country, string _stars)
    {
        this->key = key;
        string nombre = "Plato " + to_string(key);
        strcpy(this->nombre, nombre.c_str());
        strcpy(this->brand, _brand.c_str());
        strcpy(this->style, _style.c_str());
        strcpy(this->country, _country.c_str());
        strcpy(this->stars, _stars.c_str());
    }

    void showData()
    {
        cout << "\tKey: " << key << "\n";
        cout << "\tNombre: " << nombre << "\n\n";
        cout << "\tBrand: " << brand << "\n\n";
        cout << "\tStyle: " << style << "\n\n";
        cout << "\tcountry: " << country << "\n\n";
        cout << "\tStars: " << stars << "\n\n";
    }
    TKey getKey()
    {
        return key;
    }

    RecordHash &operator=(const RecordHash &a)
    {
        this->key = a.key;
        for (int i = 0; i < 20; i++){
            this->nombre[i] = a.nombre[i];
            this->brand[i] = a.brand[i];
            this->style[i] = a.style[i];
            this->country[i] = a.country[i];
            this->stars[i] = a.stars[i];
        }
        return *this;
    }
    bool operator<(const RecordHash &a) { return this->key < a.key; }
    bool operator>(const RecordHash &a) { return this->key > a.key; }
    bool operator<=(const RecordHash &a) { return this->key <= a.key; }
    bool operator>=(const RecordHash &a) { return this->key >= a.key; }
    bool operator==(const RecordHash &a) { return this->key == a.key; }
    bool operator!=(const RecordHash &a) { return this->key != a.key; }
};

#endif //RECORD_HASH.H
