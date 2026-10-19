#include "searchable_tree_bag.hpp"
#include <iostream>

// insert() is not implemented yet, so build the tree by hand via the protected members.
struct test_bag : public searchable_tree_bag {
    test_bag() { tree = 0; }
    static node *mk(int v, node *l = 0, node *r = 0) {
        node *n = new node;
        n->value = v; n->l = l; n->r = r;
        return n;
    }
    void build() { tree = mk(1, mk(2, mk(4)), mk(3)); }
    node *root() const { return tree; }
};

static int fails = 0;
static void check(const char *name, bool ok) {
    std::cout << (ok ? "[OK]   " : "[FAIL] ") << name << std::endl;
    if (!ok) ++fails;
}

int main() {
    test_bag a;
    a.build();

    check("has(1) root", a.has(1));
    check("has(4) deep", a.has(4));
    check("has(3) right", a.has(3));
    check("!has(99)", !a.has(99));

    test_bag b(a);  // copy ctor: must be a deep copy
    check("copy: has(4)", b.has(4));
    check("copy: distinct root", b.root() != a.root());
    check("copy: distinct leaf", b.root()->l->l != a.root()->l->l);

    test_bag c;
    c = a;          // operator=
    check("assign: has(2)", c.has(2));
    check("assign: distinct root", c.root() != a.root());

    a.clear();      // destroyTree: run under valgrind/-fsanitize=address to check for leaks
    std::cout << (fails ? "FAILED" : "ALL PASSED") << std::endl;
    return fails != 0;
}
