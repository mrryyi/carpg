#pragma once
#include <iostream> // for cout
#include <vector> // for vector
#include <map> // for map
#include <string> // for to_string
#include <iterator> // for back_inserter
#include <stdlib.h> // srand, rand
#include <time.h> // time
#include <unordered_set> // unordered_set
#include <unordered_map>

#define List std::vector

void debug_print(std::string origin, std::string message) {
#ifdef _DEBUG
    std::cout << "[DEBUG] ORIGIN: " << origin << ", " << message << std::endl;
#endif
}

unsigned int next_session_item_id() {
    static unsigned int nextID = 0;
    return ++nextID;
}
