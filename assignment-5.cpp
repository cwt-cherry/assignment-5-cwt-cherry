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
// base class
class lepton
{
  private:

  protected:
    string name; // electron or muon
    double rest_mass{0}; // Unit of MeV
    int charge{1}; // -1 or +1
    const double speed_of_light = 2.9979245e8; // Unit of m/s
    double velocity{0}; // Between 0 and c, in m/s
    double beta{0}; // Between 0-1
    bool antiparticle;
  
  public:
    // default constructor
    lepton(): name{}, rest_mass{}, charge{}, velocity{}, beta{}, antiparticle{} {}

    // Parameterised Constructor
    lepton(string particle_name, double particle_rest_mass, int particle_charge, double particle_velocity, bool particle_antiparticle):
      name{particle_name}, rest_mass{particle_rest_mass}, charge{particle_charge}, velocity{particle_velocity}, beta{particle_velocity/speed_of_light}, antiparticle(particle_antiparticle)
    {}

    // Destructor
    ~lepton() {std::cout<<"Destroying "<<name<<std::endl;}

};
// End of lepton class and associated member functions

// Derived classes for other particles, and four-momentum class go here

// electron class (derived class)


// four-momentum class
class FourMomentum
{
  private:
    double energy{0}; // E>0
    double momentum_x{0};
    double momentum_y{0};
    double momentum_z{0};

  public:
    // default constructor
    FourMomentum(): energy{}, momentum_x{}, momentum_y{}, momentum_z{} {}

    // parameterised constructor
    FourMomentum(double particle_energy, double particle_momentum_x, double particle_momentum_y, double particle_momentum_z):
    energy{particle_energy}, momentum_x{particle_momentum_x}, momentum_y{particle_momentum_y}, momentum_z{particle_momentum_z}
    {}

    // destructor
    ~FourMomentum() {}

    // setter for energy
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

    // smart pointer to a four-momentum object contained in each particle (unique or shared)

};

// Implementation of functions from a class should be done outside the class, preferably in another file

// Main program
int main()
{
  //...
  return 0;
}