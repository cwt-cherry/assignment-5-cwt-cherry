#ifndef RANDOM_FUNCTION_H
#define RANDOM_FUNCTION_H

#include<iostream>
#include <cstdlib> // for std::rand

// Random value generating function
double random_value();

// Convert the random number to boolean (0 -> false, 1 -> true), std::rand()%2 returns 2 values: 0 or 1
bool random_boolean();

#endif