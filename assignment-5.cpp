// PHYS 30762 Programming in C++
// Assignment 5
// Practice inheritance in C++ classes
// See slides for guidance

#include<iostream>
#include<string>
#include<vector>
#include<cmath>

using std::string;

// Beginning of lepton class (hint: start from assignment 4 particle class)
class lepton
{
private:
  //...
public:
  //...
protected: 
  //...

};
// End of lepton class and associated member functions

// Derived classes for other particles, and four-momentum class go here

class FourMomentum
{
  private:
    double energy{0}; // Between 0 and c
    double momentum_x{0};
    double momentum_y{0};
    double momentum_z{0};

  public:
    FourMomentum(): energy{}, momentum_x{}, momentum_y{}, momentum_z{}
    {}

    FourMomentum(double particle_energy, double particle_momentum_x, double particle_momentum_y, double particle_momentum_z):
    energy{particle_energy}, momentum_x{particle_momentum_x}, momentum_y{particle_momentum_y}, momentum_z{particle_momentum_z}
    {}

  void set_energy(double particle_energy)
  {
    if(particle_energy >= 0) // not limiting energy to the speed of light due to change in slides
    {
      energy = particle_energy;
    }
    else
    {
      std::cerr<<"Invalid energy. Energy should be positive."<<std::endl;
      exit(0);
    }
  }
};

// Implementation of functions from a class should be done outside the class, preferably in another file

// Main program
int main()
{
  //...
  return 0;
}