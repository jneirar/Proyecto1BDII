#include "Menus/menu.h"
#include "Techniques/Sequential/sequential.h"
#include "Techniques/DynamicHash/extendibleHash.h"

int main()
{
    init();
    Sequential<Record<char[25]>, string> seq("data", "daux");
    ExtendibleHash<int> extendibleHash("dataHash", "index");
    menu_principal(seq, extendibleHash);
    return 0;
}