// PHYS 30762 Programming in C++
// Assignment 4
// Practice special functions and operators in C++ classes

#include<iostream>
#include<string>
#include<vector>
#include<cmath>
#include "particle.h"

using std::string;

// Random value generating function
double random_value() 
{
  return static_cast<double>(std::rand()) / RAND_MAX;
}

// Main program
int main()
{
  // Create the following particles: 
  // two electrons, four muons, one antielectron, one antimuon 
  // Use the parameterised constructor to do these
  particle electron1("electron", -1, false, random_value(), random_value(), random_value(), random_value());
  particle electron2("electron", -1, false, random_value(), random_value(), random_value(), random_value());
  particle electron3("positron", 1, true, random_value(), random_value(), random_value(), random_value());
  particle muon1("muon", -1, false, random_value(), random_value(), random_value(), random_value());
  particle muon2("muon", -1, false, random_value(), random_value(), random_value(), random_value());
  particle muon3("muon", -1, false, random_value(), random_value(), random_value(), random_value());
  particle muon4("muon", -1, false, random_value(), random_value(), random_value(), random_value());
  particle muon5("antimuon", 1, true, random_value(), random_value(), random_value(), random_value());

  std::vector<particle> particles;

  particles.push_back(electron1);
  particles.push_back(electron2);
  particles.push_back(electron3);
  particles.push_back(muon1);
  particles.push_back(muon2);
  particles.push_back(muon3);
  particles.push_back(muon4);
  particles.push_back(muon5);

  // (optional but nice) Print out the data from all the particles (put them in a vector)
  for(particle &each_particle: particles)
  {
    each_particle.print_data();
  }

  // Sum the four-momenta of the two electrons 
  particle sum_particle = electron1 + electron2;
  std::cout<<"Sum of four-momentum vector of 2 electrons = ";
  sum_particle.print_vector();

  // Do the dot product of the first two four-muons
  double dot_particle = muon1.dot_product(muon2);
  std::cout<<"Dot product of four-momentum vector of 2 muons = "<<dot_particle<<"(MeV)^2"<<std::endl;

  // Assignment operator of an electron to a new electron
  particle copy_operator_particle;
  copy_operator_particle.operator = (electron1);
  copy_operator_particle.print_data();
  // Copy constructor of the first muon to a new muon
  particle copy_constructor_particle(muon1);
  copy_constructor_particle.print_data();
  // Move the antielectron into another antielectron using the move constructor 
  particle move_constructor_particle(std::move(electron3));
  move_constructor_particle.print_data();
  // Assign the antimuon to another antimuon using the move assignment
  particle move_operator_particle;
  move_operator_particle.operator = (std::move(muon5));
  move_operator_particle.print_data();

  // (optional but nice) Here or at the end of each step, print the new particle info
  // to convince yourself that you have used all special functions and operations correctly

  return 0;
}