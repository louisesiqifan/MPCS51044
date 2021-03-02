#include "btree_edit.h"

int main(int argc, char const *argv[]) {
    btree tree;
    tree.insert(2);
    tree.insert(1);
    tree.insert(3);
    auto a = tree.search(3);
    if (a == nullptr) {
        cout << "null\n";
    } else {
        cout << "found element\n";
    }
    auto b = tree.search(4);
    if (b == nullptr) {
        cout << "null\n";
    } else {
        cout << "found element\n";
    }
    tree.destroy_tree();
    return 0;
}
