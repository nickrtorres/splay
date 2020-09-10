#include <cstdint>
#include <iostream>

#include "tree.h"

#define tst_begin(name)         \
do {                            \
    std::cout << name << "..."; \
} while (0)

#define tst_check(cond)                                          \
do {                                                             \
    if (!(cond)) {                                               \
        std::cout << "fail => { " << #cond << " }" << std::endl; \
    } else {                                                     \
        std::cout << "ok" << std::endl;                          \
    }                                                            \
} while (0)

int main()
{
    {
        tst_begin("construct");
        auto t = Tree<uint32_t>{};
        tst_check(true);
    }

    {
        tst_begin("simple insert");
        auto t = Tree<uint32_t> {};
        t.Insert(42);
        tst_check(t.RootValue() == 42);
    }
}
