#include<iostream>
#include "random-function.h"

// Random value generating function
double random_value() {return static_cast<double>(std::rand()) / RAND_MAX;}

// Convert the random number to boolean (0 -> false, 1 -> true), std::rand()%2 returns 2 values: 0 or 1
bool random_boolean() {return static_cast<bool>(std::rand()%2);}