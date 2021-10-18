#ifndef RECORD_HASH_H
#define RECORD_HASH_H

#include "../lib.h"

template <typename TKey>
class RecordHash
{
    TKey key;
    char brand[35];
    char style[5];
    char country[15];
    float stars;

public:
    RecordHash()
    {
        this->key = 0;
        string brand = "brand";
        strcpy(this->brand, brand.c_str());
        string style = "style";
        strcpy(this->style, style.c_str());
        string country = "country";
        strcpy(this->country, country.c_str());
        this->stars = 0.0;
    }

    RecordHash(TKey key, string brand, string style, string country, float stars)
    {
        this->key = key;
        strcpy(this->brand, brand.c_str());
        strcpy(this->style, style.c_str());
        strcpy(this->country, country.c_str());
        this->stars = stars;
    }

    void setData(TKey key, string brand, string style, string country, float stars)
    {
        this->key = key;
        strcpy(this->brand, brand.c_str());
        strcpy(this->style, style.c_str());
        strcpy(this->country, country.c_str());
        this->stars = stars;
    }

    void showData()
    {
        cout << "\tKey: " << key << "\n";
        cout << "\tBrand: " << brand << "\n\n";
        cout << "\tStyle: " << style << "\n\n";
        cout << "\tCountry: " << country << "\n\n";
        cout << "\tStars: " << stars << "\n\n";
    }
    TKey getKey()
    {
        return key;
    }

    RecordHash &operator=(const RecordHash &a)
    {
        TKey key;
        char brand[35];
        char style[5];
        char country[15];
        float stars;

        this->key = a.key;
        for (int i = 0; i < 35; i++)
            this->brand[i] = a.brand[i];
        for (int i = 0; i < 5; i++)
            this->style[i] = a.style[i];
        for (int i = 0; i < 15; i++)
            this->country[i] = a.country[i];
        this->stars = a.stars;
        return *this;
    }
    bool operator<(const RecordHash &a) { return this->key < a.key; }
    bool operator>(const RecordHash &a) { return this->key > a.key; }
    bool operator<=(const RecordHash &a) { return this->key <= a.key; }
    bool operator>=(const RecordHash &a) { return this->key >= a.key; }
    bool operator==(const RecordHash &a) { return this->key == a.key; }
    bool operator!=(const RecordHash &a) { return this->key != a.key; }

    void showRecord(int cont)
    {

        cout << setw(5) << cont << setw(5) << key << setw(40) << brand << setw(10) << style << setw(20) << country << setw(7) << stars << "\n";
    }
};

#endif //RECORD_HASH.H