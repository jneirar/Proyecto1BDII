#include <iostream>
#include "Techniques/DynamicHash/extendibleHash.h"
#include "Techniques/Sequential/sequential.h"
#include "Techniques/Sequential/record.h"
#include "Techniques/DynamicHash/recordHash.h"
#include <sstream>
#include <fstream>
#include <vector>

#define NOMBRE_ARCHIVO_POKEMON "Pokemon.csv"
#define NOMBRE_ARCHIVO_RAMEN "Ramen.csv"

using namespace std;

template <typename tk>
void insertar_secuencial(Sequential<tk> &seq){

    ifstream archivo(NOMBRE_ARCHIVO_POKEMON);
    string linea;
    char delimitador = ',';
    // Leemos la primea linea para descartarla, pues es el encabezado
    getline(archivo,linea);
    vector<Record<int>> records;
    Record<int> temp;
  
    
    // Leemos todos las linea
    int count = 1;
    while (getline(archivo,linea))
    {

        stringstream stream(linea);//Convertir la cadena a un stream
        string Name, Type, Total, Generation, Legendary;
        //Extraer todos los valores
        getline(stream, Name, delimitador);
        getline(stream, Type, delimitador);
        getline(stream, Total, delimitador);
        getline(stream, Generation, delimitador);
        getline(stream, Legendary, delimitador);

        temp.setData(count,Name, Type, Total, Generation, Legendary);
        
        //guardar en vector
        records.push_back(temp);
        count += 1;
    }
    seq.insertAll(records);
}

template <typename tk>
void insert_hash(ExtendibleHash<tk> &eh){

    ifstream archivo(NOMBRE_ARCHIVO_RAMEN);
    string linea;
    char delimitador = ',';
    // Leemos la primea linea para descartarla, pues es el encabezado
    getline(archivo,linea);
    RecordHash<int> temp;
  
    
    // Leemos todos las linea
    while (getline(archivo,linea))
    {

        stringstream stream(linea);//Convertir la cadena a un stream
        string review, brand, style, country, stars;
        //Extraer todos los valores
        getline(stream, review, delimitador);
        getline(stream, brand, delimitador);
        getline(stream, style, delimitador);
        getline(stream, country, delimitador);
        getline(stream, stars, delimitador);

        stringstream intValue(review);
        int number = 0;
        intValue >> number;

        temp.setData(number, brand, style, country, stars);
        
        //guardar en vector
        eh.insert(temp);
    }
}


int main()
{
    init();
    init2();
    //Sequential<int> pokemon("data", "daux");


    //insertar_secuencial<int>(pokemon);
    //pokemon.showAll();

    ExtendibleHash<int> ramen("dataHash", "index");
    ramen.showBuckets();

    insert_hash(ramen);
    ramen.showBuckets();

    return 0;
}
