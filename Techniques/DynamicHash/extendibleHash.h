#ifndef EXTENDIBLE_HASH_H
#define EXTENDIBLE_HASH_H

#include "bucket.h"

template <typename TKey>
class ExtendibleHash{
private:
    string fileName;
    string indexName;
    unordered_map<string, long> index;
    unordered_map<string, long> index_size;
    hash<TKey> _hash;
    long freeListBucket = -1;
    string hash_function(TKey key){
        auto hash_code = _hash(key);
        string hash_code_string = bitset<HASH_HEIGHT>(hash_code).to_string();
        return hash_code_string;

    }
    void initIndex();
    void readIndex();
    void writeIndex();
    void insertInFreeList(fstream &f);
    void divideBucket(fstream &f, Bucket<TKey> &bucket, long pos);
    bool exists(TKey key);
public:
    ExtendibleHash(string _fileName, string _indexName) {
        this->fileName = _fileName + ".dat";
        this->indexName = _indexName + ".dat";
        if(isFileEmpty(indexName)){
            cout  << "File initialization\n";
            initIndex();
        }
        readIndex();
        fopen(fileName);
        isfopen{
            f.seekg(0, ios::beg);
            write(f, freeListBucket);
            f.close();
        }else cout << "Hash error al abrir data en constructor para leer freelist\n";
    }
    
    ~ExtendibleHash(){
        writeIndex();
    }
    void showAll(){
        cout << "FreeList: " << freeListBucket << "\n";
        fopen(fileName);
        isfopen{
            cout << "\nIndex:\n";
            for(long i = 0; i < (1 << HASH_HEIGHT); i++){
                string cad = bitset<HASH_HEIGHT>(i).to_string();
                cout << i << " - " << cad << "\t" << index[cad] << "\t" << index_size[cad] << "\n";
                cout << "Bucket: ";
                Bucket<TKey> bucket;
                f.seekg(index[cad], ios::beg);
                read(f, bucket);
                bucket.showNotAll();
            }
            cout << "\nData:\n";
            for(long i = 0; i < (1 << HASH_HEIGHT); i++){
                string cad = bitset<HASH_HEIGHT>(i).to_string();
                if(index_size[cad] > 0){
                    cout << i << " - " << cad << " tiene " << index_size[cad] << " registros\n";
                    Bucket<TKey> bucket;
                    long pos = index[cad];
                    int cont = 1;
                    while(pos != -1){
                        f.seekg(pos, ios::beg);
                        read(f, bucket);
                        cout << "Bucket " << cont++ << ":\n";
                        bucket.showAll();
                        pos = bucket.getNext();
                    }
                    cout << "\n";
                }
            }

            f.close();
        }else cout << "Hash error al abrir data en showAll\n";
    }

    void insert(RecordHash<TKey> record){
        if(exists(record.getKey())){
            cout << "Ya existe el registro " << record.getKey() << "\n";
            return;
        }
        string cad = hash_function(record.getKey());
        fopen(fileName);
        isfopen{
            Bucket<TKey> bucket;
            long pos = index[cad];
            f.seekg(pos, ios::beg);
            read(f, bucket);
            
            if(bucket.isFull()){
                //required division or linked
                if(bucket.hasMaxLocalHeight()){
                    //Verificar si hay espacio en linked buckets
                    long prev_pos = pos; //En prev_pos está el bucket
                    while(1){
                        prev_pos = pos;
                        pos = bucket.getNext();
                        if(pos == -1) break;
                        f.seekg(pos, ios::beg);
                        read(f, bucket);
                    }
                    if(bucket.isFull()){
                        //insert new linked bucket
                        Bucket<TKey> new_bucket;
                        new_bucket.insertRecord(record);
                        
                        insertInFreeList(f);    //Posiciona al lugar donde se debe insertar un nuevo bucket

                        long new_pos = f.tellp();
                        bucket.setNext(new_pos);
                        write(f, new_bucket);
                        f.seekp(prev_pos, ios::beg);
                        write(f, bucket);
                    }else{
                        //insertar
                        bucket.insertRecord(record);
                        f.seekp(prev_pos, ios::beg);
                        write(f, bucket);
                    }
                }else{
                    //requiere division del bucket y sumar 1 a su local_height, puede hacerse hasta generar linkedlist
                    bool requiredLindekPage = false;
                    while(1){
                        divideBucket(f, bucket, pos);
                        /*
                        cout << "\n---------------\n";
                        for(long i = 0; i < (1 << HASH_HEIGHT); i++){
                            string cad = bitset<HASH_HEIGHT>(i).to_string();
                            cout << cad << "\t" << index[cad] << "\n";
                        }
                        cout << "\n---------------\n";
                        */
                        pos = index[cad];
                        f.seekg(pos, ios::beg);
                        read(f, bucket);
                        if(bucket.isFull() && bucket.hasMaxLocalHeight()){
                            requiredLindekPage = true;
                            break;
                        }
                        if(!bucket.isFull())    break;
                        //Si está lleno y no tiene el máx height, volver a hacer la división
                    }
                    //Si no requere linked, insertar en la posición dada
                    if(requiredLindekPage){
                        Bucket<TKey> new_bucket;
                        new_bucket.insertRecord(record);
                        
                        insertInFreeList(f);    //Posiciona al lugar donde se debe insertar un nuevo bucket

                        long new_pos = f.tellp();
                        bucket.setNext(new_pos);
                        write(f, new_bucket);
                        f.seekp(pos, ios::beg);
                        write(f, bucket);
                    }else{
                        //Inserta en bucket
                        bucket.insertRecord(record);
                        f.seekp(pos, ios::beg);
                        write(f, bucket);
                    }
                }
            }else{
                //Inserta en bucket
                bucket.insertRecord(record);
                f.seekp(pos, ios::beg);
                write(f, bucket);
            }
            index_size[cad]++;
            f.close();
        }else cout << "Hash error al abrir data en insert\n";
    }
    
    RecordHash<TKey>* search(TKey key){
        string cad = hash_function(key);
        if(index_size[cad] == 0)    return nullptr;

        fopen(fileName);
        isfopen{
            Bucket<TKey> bucket;
            long pos = index[cad];
            while(pos != -1){
                f.seekg(pos, ios::beg);
                read(f, bucket);
                RecordHash<TKey>* rec = bucket.searchRecord(key);
                if(rec){
                    f.close();
                    return rec;
                }
                pos = bucket.getNext();
            }
            return nullptr;
            f.close();
        }else cout << "Hash error al abrir data en search\n";
        return nullptr;
    }
    vector<RecordHash<TKey>> search(TKey key1, TKey key2){
        vector<RecordHash<TKey>> result;
        unordered_set<long> visited;
        fopen(fileName);
        isfopen{
            for(long i = 0; i < (1 << HASH_HEIGHT); i++){
                string cad = bitset<HASH_HEIGHT>(i).to_string();
                long pos = index[cad];
                if(visited.count(pos))   continue;
                visited.insert(pos);
                
                while(pos != -1){
                    Bucket<TKey> bucket;
                    f.seekg(pos, ios::beg);
                    read(f, bucket);
                    bucket.searchRange(key1, key2, result);
                    pos = bucket.getNext();
                }
            }
        }else cout << "Hash error al abrir data en search range\n";
        return result;
    }
    bool erase(TKey key){
        if(!exists(key))    return false;
        
        return false;
    }
};

template<typename TKey>
void ExtendibleHash<TKey>::initIndex(){
    cleanFile(fileName);
    fopen(indexName);
    isfopen{
    faopen(fileName);
    isfaopen{
        freeListBucket = -1;
        write(fa, freeListBucket);
        Bucket<TKey> bucket0, bucket1;
        long pos0 = fa.tellp();
        write(fa, bucket0);
        long pos1 = fa.tellp();
        write(fa, bucket1);
        string cad;
        long size = 0;
        for(long i = 0; i < (1 << HASH_HEIGHT); i++){
            cad = bitset<HASH_HEIGHT>(i).to_string();
            f.write(cad.c_str(), HASH_HEIGHT);
            if(cad[HASH_HEIGHT-1] == '0')    
                write(f, pos0);                
            else
                write(f, pos1);
            write(f, size); //size = 0
        }
        f.close();
        fa.close();
    }else cout << "Hash error al abrir data en initIndex\n";
    }else cout << "Hash error al abrir index en initIndex\n";
}
template<typename TKey>
void ExtendibleHash<TKey>::readIndex(){
    fopen(indexName);
    isfopen{
        string cad;
        long pos;
        long size;
        for(auto i = 0; i < (1 << HASH_HEIGHT); i++){
            char* buffer = new char[HASH_HEIGHT + 1];
            //read cad
            f.read(buffer, HASH_HEIGHT);
            buffer[HASH_HEIGHT] = '\0';
            cad = buffer;
            delete buffer;
            if(cad == "")  return;
            //read page
            f.read((char*)&pos, sizeof(pos));
            //read page
            f.read((char*)&size, sizeof(size));
            index[cad] = pos;
            index_size[cad] = size;
        }
        f.close();
    }else cout << "Hash error al abrir index en readIndex\n";
}

template<typename TKey>
void ExtendibleHash<TKey>::writeIndex(){
    fopen(indexName);
    isfopen{
        for(long i = 0; i < (1 << HASH_HEIGHT); i++){
            string cad = bitset<HASH_HEIGHT>(i).to_string();
            f.write(cad.c_str(), HASH_HEIGHT);
            f.write((char*) &index[cad], sizeof(index[cad]));
            f.write((char*) &index_size[cad], sizeof(index_size[cad]));
        }
        f.close();
    }else cout << "Hash error al abrir index en writeIndex\n";
}

template<typename TKey>
void ExtendibleHash<TKey>::insertInFreeList(fstream &f){
    if(freeListBucket == -1){
        //Inserta al final
        f.seekp(0, ios::end);
    }else{
        //Inserta en la posición disponible y actualiza freelist
        Bucket<TKey> deleted_bucket;
        f.seekg(freeListBucket, ios::beg);
        read(f, deleted_bucket);
        f.seekp(freeListBucket, ios::beg);
        freeListBucket = deleted_bucket.getNext();
    }
}

template<typename TKey>
void ExtendibleHash<TKey>::divideBucket(fstream &f, Bucket<TKey> &bucket, long pos){
    //Dividir bucket: new tiene a los que empiezan con 1, y bucket se queda con los que empiezan con 0
    Bucket<TKey> new_bucket = bucket.divide();
    
    //Actualiza buckets
    f.seekp(pos);
    write(f, bucket);
    
    insertInFreeList(f);    //Posiciona al lugar donde se debe insertar un nuevo bucket
    
    long new_pos = f.tellp();
    f.seekp(new_pos);
    write(f, new_bucket);

    //Actualiza index 
    long local_height = bucket.getLocalHeight();
    for(auto &p : index)
        if(p.first[HASH_HEIGHT - local_height] == '1' && p.second == pos)
            p.second = new_pos;
}

template<typename TKey>
bool ExtendibleHash<TKey>::exists(TKey key){
    string cad = hash_function(key);
    if(index_size[cad] == 0)    return false;

    fopen(fileName);
    isfopen{
        Bucket<TKey> bucket;
        long pos = index[cad];
        while(pos != -1){
            f.seekg(pos, ios::beg);
            read(f, bucket);
            if(bucket.existsRecord(key))
                return true;
            pos = bucket.getNext();
        }
        return false;
        f.close();
    }else cout << "Hash error al abrir data en exists\n";
    return false;
}

#endif  //EXTENDIBLE_HASH.H