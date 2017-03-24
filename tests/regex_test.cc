#include "../noey_algos"

int main() {
    noey::pool p(1000);
    assert(noey::match("c", noey::build_nfa("ab.b*c|", &p)));
}
