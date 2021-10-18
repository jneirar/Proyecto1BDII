#ifndef RAMEN_MENU_H
#define RAMEN_MENU_H

#include "../Techniques/DynamicHash/extendibleHash.h"
#define NOMBRE_ARCHIVO_RAMEN "Ramen.csv"
#include <stdio.h>
#include <time.h>

bool esEntero_r(string linea)
{
    bool esEntero = true;
    int longitud = linea.size();

    if (longitud == 0)
    {
        esEntero = false;
    }
    else if (longitud == 1 && !isdigit(linea[0]))
    {
        esEntero = false;
    }
    else
    {
        int indice = 0;
        if (linea[0] == '+' || linea[0] == '-')
        {
            indice = 1;
        }
        else
        {
            indice = 0;
        }

        while (indice < longitud)
        {
            if (!isdigit(linea[indice]))
            {
                esEntero = false;
                break;
            }
            indice++;
        }
    }

    return esEntero;
}
void post_insertar_aleatorio_hash(ExtendibleHash<int> &eh);

void insertar_hash(ExtendibleHash<int> &eh)
{

    ifstream archivo(NOMBRE_ARCHIVO_RAMEN);
    string linea;
    clock_t t;
    char delimitador = ',';
    // Leemos la primea linea para descartarla, pues es el encabezado
    getline(archivo, linea);
    vector<RecordHash<int>> records;
    // Leemos todos las linea
    while (getline(archivo, linea))
    {
        stringstream stream(linea); //Convertir la cadena a un stream
        string review, brand, style, country, stars;
        //Extraer todos los valores
        getline(stream, review, delimitador);
        getline(stream, brand, delimitador);
        getline(stream, style, delimitador);
        getline(stream, country, delimitador);
        getline(stream, stars, delimitador);
        RecordHash<int> temp(stoi(review), brand, style, country, stof(stars));
        records.push_back(temp);
    }

    t = clock();
    int accesos = eh.insertAll(records);
    t = clock() - t;
    double time_taken = ((double)t) / CLOCKS_PER_SEC; // calculate the elapsed time
    cout << endl;
    printf("El programa tomó %f segundos en insertar los %zu registros", time_taken, records.size());
    printf("\nEl programa tomó %d accesos a memoria secundaria", accesos);
    dump();
    post_insertar_aleatorio_hash(eh);
}

void post_insertar_aleatorio_hash(ExtendibleHash<int> &eh)
{
    string input;
    int opcion;
    bool repite = true;
    do
    {
        cout << "\e[1;1H\e[2J";
        cout << "Se insertaron los datos existosamente" << endl;
        cout << endl;
        cout << "¿Deseas verlos?" << endl;
        cout << "-> Elige un número" << endl;
        cout << endl;
        cout << endl;
        cout << "1. Si -> Mostrar datos" << endl;
        cout << endl;
        cout << "2. No -> Regresar al menu de inicio" << endl;
        cout << endl;
        cout << "3. Salir" << endl;
        cout << endl;

        getline(cin, input);
        if (esEntero_r(input))
        {
            repite = false;
        }
    } while (repite);

    opcion = atoi(input.c_str());

    switch (opcion)
    {
    case 1:
        eh.showRecords();
        break;
    case 2:
        return;
        break;
    case 3:
        exit(-1);
        break;
    default:
        post_insertar_aleatorio_hash(eh);
        break;
    }
    dump();
}

void insertar_registro_hash(ExtendibleHash<int> &eh)
{
    cout << "\n\n----------Insertar----------\n\n";
    string brand, style, country;
    float stars;
    int codigo;
    clock_t t;
    cout << "Ingrese el codigo: ";
    cin >> codigo;
    cout << "Ingrese la marca (35 carac. max): ";
    cin >> brand;
    cout << "Ingrese el estilo (5 carac. max): ";
    cin >> style;
    cout << "Ingrese el pais (15 carac. max): ";
    cin >> country;
    cout << "Ingrese las estrellas: ";
    cin >> stars;

    RecordHash<int> rec(codigo, toLower(brand), toLower(style), toLower(country), stars);
    int accesos = 0;
    t = clock();
    eh.insert(rec, accesos);
    t = clock() - t;
    double time_taken = ((double)t) / CLOCKS_PER_SEC; // calculate the elapsed time
    cout << endl;
    printf("El programa tomó %f segundos en insertar el registro", time_taken);
    printf("\nEl programa tomó %d accesos a memoria secundaria", accesos);
    dump();
}

void buscar_registro_hash(ExtendibleHash<int> &eh)
{
    cout << "\n\n----------Busqueda----------\n\n";
    cout << "Ingrese codigo a buscar: ";
    int key;
    clock_t t;
    cin >> key;
    int accesos = 0;
    t = clock();
    auto result = eh.search(key, accesos);
    if (result)
    {
        (*result).showRecord(1);
        t = clock() - t;
        double time_taken = ((double)t) / CLOCKS_PER_SEC; // calculate the elapsed time
        cout << endl;
        printf("El programa tomó %f segundos en buscar el registro", time_taken);
        printf("\nEl programa tomó %d accesos a memoria secundaria", accesos);
    }
    else
    {
        cout << "No se encontro " << key << "\n";
    }
    dump();
}

void buscar_rango_registro_hash(ExtendibleHash<int> &eh)
{
    cout << "\n\n----------Busqueda por rango----------\n\n";
    int key1, key2;
    clock_t t;
    cout << "Inserte registro inicial: ";
    cin >> key1;
    cout << "Inserte registro final: ";
    cin >> key2;
    if (key1 > key2)
    {
        auto t = key1;
        key1 = key2;
        key2 = t;
    }
    t = clock();
    auto result = eh.searchRange(key1, key2);
    cout << "Resultado: " << result.size() << "\n";
    int cont = 1;
    for (auto r : result)
    {
        r.showRecord(cont++);
    }
    t = clock() - t;
    double time_taken = ((double)t) / CLOCKS_PER_SEC; // calculate the elapsed time
    cout << endl;
    printf("El programa tomó %f segundos en buscar el rango de registros", time_taken);
    dump();
}

void eliminar_registro_hash(ExtendibleHash<int> &eh)
{
    cout << "\n\n----------Eliminar----------\n\n";
    cout << "Ingrese codigo a eliminar: ";
    int key;
    cin >> key;
    if (eh.erase(key))
    {
        cout << "Registro eliminado\n";
    }
    else
    {
        cout << "No se elimino\n";
    }

    dump();
}

#endif