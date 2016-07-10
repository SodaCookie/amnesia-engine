#include "../primitive/vector.h"
#include <utility>

extern "C" {
bool should_unwrap(std::pair<bool, Vector *> *pair) { return pair->first; }
Vector *unwrap(std::pair<bool, Vector *> *pair) { return pair->second; }
}
