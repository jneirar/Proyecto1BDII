#include "extendibleHash.h"

using namespace std;

int main(){
    cout << "---------------Borrando archivos---------------\n";
    init2();
    ExtendibleHash<int> extendibleHash("data", "index");
    extendibleHash.showAll();
    RecordHash<int> r;
    r.setData(1);//001
    extendibleHash.insert(r);
    r.setData(2);//010
    extendibleHash.insert(r);
    r.setData(10);//010
    extendibleHash.insert(r);
    r.setData(18);//010
    extendibleHash.insert(r);
    extendibleHash.showAll();
    cout << "\n-----------------------DIVISION-----------------------\n";
    r.setData(26);//010
    extendibleHash.insert(r);
    r.setData(34);//010
    extendibleHash.insert(r);
    r.setData(42);//010
    extendibleHash.insert(r);
    r.setData(50);//010
    extendibleHash.insert(r);
    extendibleHash.showAll();

    cout << "\n-----------------------SEARCH-----------------------\n";
    auto rs = extendibleHash.search(1);
    if(rs)  (*rs).showData();
    else cout << "No existe 1\n";
    rs = extendibleHash.search(8);
    if(rs)  (*rs).showData();
    else cout << "No existe 8\n";
    rs = extendibleHash.search(26);
    if(rs)  (*rs).showData();
    else cout << "No existe 26\n";
    rs = extendibleHash.search(50);
    if(rs)  (*rs).showData();
    else cout << "No existe 50\n";

    cout << "\n-----------------------RANGE SEARCH-----------------------\n";
    auto rv = extendibleHash.search(1, 5);
    cout << rv.size() << "\n";
    for(auto rec : rv)
        rec.showData();
    return 0;
}