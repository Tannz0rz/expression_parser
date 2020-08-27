# Expression Parser



### Description
Expression Parser is an algebraic expression parser. The parser takes an input string expression and an input map of terms to parse & construct an expression tree for evaluation. The expression is parsed with recursive `std::regex` evaluations and the expression tree is constructed with polymorphic RAII-friendly `std::shared_ptr` nodes that represent various mathematical objects.



### Building
An example is provided as main.cpp. This example was built on Ubuntu 20.04.1 LTS compiled with GCC 9.3.0.
```
mkdir build && cd build
cmake .. && make
./ExpressionParser
```
