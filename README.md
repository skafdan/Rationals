# Rationals
Etude_8 Cosc326.

Integer and Rational library that includes operators and gcd and function.

## Installation
`Rational` is dependent on `Integer` both files must be included in implementation file and located in path to project.

```$ path_to_directory/src/Rational.cpp Rational.h Integer.cpp Integer.h foo.cpp```

Compile with `$ g++ -o <Your Program Name> <Your Files.cpp> Integer.cpp Rational.cpp`


### Evaluation 
The program aims to use encapsulation and reusing of operators as much as possible. All `Rational` operators are created using the operators of the `Integer` class.

Binary operators are created using the arithmetic assignment operators. 

For all operations we tried to mathmatical equivalents to reuse operators. 
e.g :
- `-x + y = y - x = z`
- `x < y = y > x`
- `a/b / c/d = a/b * d/c`