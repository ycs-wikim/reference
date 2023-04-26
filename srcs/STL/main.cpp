#include <iostream>
#include <stdlib.h>
#include "stl_vector.h"
#include "stl_pair.h"
#include "stl_list.h"
#include <list>
using namespace std;

/*bool Condition(int i) {
    return ((i % 2) == 0);
}*/

int main() {
    STLList<int> l1, l2;

    l1.PushBack(1);
    l1.PushBack(2);
    l1.PushBack(3);
    l1.PushBack(4);
    l1.PushBack(5);

    l2.PushBack(6);
    l2.PushBack(7);
    l2.PushBack(8);
    l2.PushBack(9);
    l2.PushBack(10);


    STLList<int>::Iterator it = l1.Begin();

    cout << l1.Size() << endl << endl;

    it++;

    STLList<int>::Iterator it1 = l2.Begin();
    STLList<int>::Iterator ait2 = l2.End();

    l1.Splice(it, l2, it1, ait2);

    cout << l1.Size() << endl << endl;

    for (it = l1.Begin(); it != l1.End(); ++it) {
        cout << *it << endl;
    }

    cout << endl << "list2" << endl;

    STLList<int>::Iterator it2;

    for (it2 = l2.Begin(); it2 != l2.End(); ++it2) {
        cout << *it2 << endl;
    }

    return 0;
}
