#ifndef INCLUDED_UTILS
#define INCLUDED_UTILS

#include <box2d/box2d.h>
#include <iostream>
#include <stdexcept>
#include <algorithm>
#include <vector>
#include <thread>
#include <functional>
using namespace std;

#include "include/prettyprint.hpp"
#include "common/colour.h"
#include "common/vector2.h"

// !todo Clean this file up

// Forward declaration
class Node;

void markPosition(Vector2 position, string text, Colour colour = RED, float radius = 10.0f, float width = 1.0f);

template <typename Any>
float sign(Any value) {
    return (value > 0.0f) - (value < 0.0f);
}
Vector2 sign(Vector2 value);

string wrapString(string str, int line_chars);
vector<string> splitString(string str, char splitter);
const char* plusFile(const char* path, const char* file_to_add);
string plusFile(string path, string file_to_add);

constexpr unsigned int str2int(const char* str, int h = 0) {
    return !str[h] ? 5381 : (str2int(str, h+1) * 33) ^ str[h];
}
int getStringWidth(string str);
const vector<string> long_characters = {
    "─", "━", "│", "┃",
    "┌", "┐", "┏", "┓",
    "└", "┘", "┗", "┛",
    "├", "┤", "┣", "┫"
};
string equaliseStringLineWidths(string str);
bool stringBeginsWith(string str, string begins);
string vector2str(Vector2 value, int max_decimals = 2, bool decorate = false);
string vector2str(b2Vec2 value, int max_decimals = 2, bool decorate = false);
const char* int2char(int value);
string encaseStringInBox(string str, bool thick = false, int margin = 2);
string repeatString(string str, int amount);
string strVector2str(vector<string> vector, string splitter = ", ");
string concatChars(const char* A, const char* B);
string stringPadDecimals(string str, int max_decimals);

template<typename MapType, typename KeyType>
void eraseMapKey(MapType* map, KeyType key) {
    map->erase(key);
}

template <typename Any>
int vectorFindValue(vector<Any>* vector, Any value) {
    int ret = -1;
    for (auto i = vector->begin(); i != vector->end(); ++i) {
        ret++;
        if (*i == value) {
            break;
        }
    }
    return ret;
}
template <typename Any>
bool vectorContainsValue(vector<Any>* vector, Any value) {
    return find(vector->begin(), vector->end(), value) != vector->end();
}
template <typename Any>
void vectorRemoveValue(vector<Any>* vector, Any value) {
    vector->erase(remove(vector->begin(), vector->end(), value), vector->end());
}

void print_stacktrace(int additional_skip = 0);

void warn(string message, bool throw_error = false);

#undef assert

#if DEBUG_ENABLED
#define assert(expr)						                          \
    if (!static_cast<bool>(expr)) {                                  \
        print_stacktrace();                                           \
        __assert_fail (#expr, __FILE__, __LINE__, __ASSERT_FUNCTION); \
    }
#else
#define assert(expr)
#endif

template<typename F, typename O, typename... A>
void makeThread(F function, O* object, A... args) {
    thread(bind(function, object, args...), args...).detach();
}

template<class ObjectType, class ReturnType, class... ArgumentTypes>
struct Functor {

    using TMemberFunction = ReturnType (ObjectType::*)(ArgumentTypes...);
    TMemberFunction ptr;
    ObjectType     *object;


    ReturnType operator()(ArgumentTypes... params) {
        return (object->*ptr)(params...);
    }
};

Vector2 convertVector2(b2Vec2 value);
b2Vec2 convertVector2(Vector2 value);

Colour combineColours(Colour a, Colour b);
Colour normaliseColour(Colour colour);

string formatPath(string& path);

#endif