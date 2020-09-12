#define DOCTEST_CONFIG_IMPLEMENT
#include "doctest.h"
#include <iostream>;
#include "LinkedList.h";

//Basic Insertion
TEST_CASE("Insertion Test")
{
    LinkedList<int> LL; 
    LL.add_element(1);
    LL.add_element(2);
    CHECK(LL.length() == 2);
    LL.add_element(3);
    LL.add_element(4);
    CHECK(LL.length() == 4);

    CHECK(LL.get_element_at(0) == 1);
    CHECK(LL.get_element_at(1) == 2);
    CHECK(LL.get_element_at(2) == 3);
    CHECK(LL.get_element_at(3) == 4);
}


int main()
{
	doctest::Context().run();
}