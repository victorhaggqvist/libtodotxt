#include "gtest/gtest.h"
#include "todoitem.h"
#include "todotxt.h"

#include <string>
#include <vector>

using namespace std;
using namespace Snilius;

/**
 * Tests for todo.txt items
 * Some cases are straight from Ginas spec
 * https://github.com/ginatrapani/todo.txt-cli/wiki/The-Todo.txt-Format
 * @brief TEST
 */

TEST(Todotxt, createObject){
  string base = ".";
  Todotxt *todo = new Todotxt(base);
}
