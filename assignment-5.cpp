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
    string name; // electron, muon, tau, neutrino
    double rest_mass{0}; // Unit of MeV
    int charge{1}; // -1 or +1
    const double speed_of_light = 2.9979245e8; // Unit of m/s
    double velocity{0}; // Between 0 and c, in m/s
    double beta{0}; // Between 0-1
    bool antiparticle;

    static double random_value() 
    {
      return static_cast<double>(std::rand()) / RAND_MAX;
    }
  
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
class electronClass: public lepton
{
  // private:
  //   string electron;
  //   double mass{0.511};
  //   int charge{-1};
  //   double velocity{0};
  //   bool antiparticle;

  public:
    // dafault constructor
    electronClass(): lepton{} {}

    // parameterised constructor
    electronClass(string particle_name, double particle_rest_mass, int particle_charge, double particle_velocity, bool particle_antiparticle): 
    lepton(particle_name, particle_rest_mass, particle_charge, particle_velocity, particle_antiparticle) {}
    
    // Constructor for Electron
    electronClass(): lepton("electron", 0.511, -1, random_value(), false) {}

    // Constructor for Positron (antielectron)
    static electronClass positron()
    {
      return electronClass("positron", 0.511, +1, random_value(), true);
    }

    // destructor
    ~electronClass() {std::cout<<"Destroying "<<name<<std::endl;}

};

// muon class (derived class)
class muonClass: public lepton
{
  private:

  public:
    // default constructor
    muonClass(): lepton{} {}

    // parameterised constructor
    muonClass(string particle_name, double particle_rest_mass, int particle_charge, double particle_velocity, bool particle_antiparticle): 
    lepton(particle_name, particle_rest_mass, particle_charge, particle_velocity, particle_antiparticle) {}
    
    // Constructor for muon
    muonClass(): lepton("muon", 105.6, -1, random_value(), false) {}

    // Constructor for antimuon
    static muonClass antimuon()
    {
      return muonClass("antimuon", 105.6, +1, random_value(), true);
    }

};

// tau class (derived class)
class tauClass: public lepton
{
  private:
  public:

    // default constructor
    tauClass(): lepton{} {}

    // parameterised constructor
    tauClass(string particle_name, double particle_rest_mass, int particle_charge, double particle_velocity, bool particle_antiparticle): 
    lepton(particle_name, particle_rest_mass, particle_charge, particle_velocity, particle_antiparticle) {}
    
    // Constructor for tau
    tauClass(): lepton("tau", 1777, -1, random_value(), false) {}

    // Constructor for antitau
    static tauClass positron()
    {
      return tauClass("antitau", 1777, +1, random_value(), true);
    }
};

// neutrinos class (derived class)
class neutrinoClass: public lepton
{
  private:
  public:
    // default constructor
    neutrinoClass(): lepton{} {}

    // parameterised constructor
    neutrinoClass(string particle_name, double particle_rest_mass, int particle_charge, double particle_velocity, bool particle_antiparticle): 
    lepton(particle_name, particle_rest_mass, particle_charge, particle_velocity, particle_antiparticle) {}
    
    // Constructor for neutrinos
    neutrinoClass(): lepton("neutrino", 940.6, 0, random_value(), false) {}

    // Constructor for Positron (antineutrinos)
    static neutrinoClass positron()
    {
      return neutrinoClass("antineutrino", 940.6, 0, random_value(), true);
    }
};

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