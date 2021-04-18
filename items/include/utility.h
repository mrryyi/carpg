#pragma once
#include <iostream> // for cout
#include <vector> // for vector
#include <map> // for map
#include <string> // for to_string
#include <iterator> // for back_inserter
#include <stdlib.h> // srand, rand
#include <time.h> // time
#include <unordered_set> // unordered_set

#define List std::vector
#define __DEBUGMODE__

void debug_print(std::string origin, std::string message) {
#ifdef __DEBUGMODE__
    std::cout << "[DEBUG] ORIGIN: " << origin << ", " << message << std::endl;
#endif
}

int next_session_item_id() {
    static int nextID = 0;
    return ++nextID;
}
