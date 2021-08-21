#include "../ds/MapBoard.h"
#include <cassert>

int main() {
    MapBoard m;
    m[4][4]='e';
    assert(m[4][4] == 'e');
    m[4][4]='x';
    assert(m[4][4] == 'x');
}