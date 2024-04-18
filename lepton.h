#ifndef LEPTON_H
#define LEPTON_H

#include<string>
#include<memory> // for smart pointers
#include "four-momentum.h"
#include "random-function.h"

using std::string;

// base class
class lepton
{
  protected:
    string name; // only getters, setters in derived classes
    double rest_mass{0}; // Unit of MeV
    int charge{1}; // -1 or +1
    const double speed_of_light = 2.9979245e8; // Unit of m/s
    double velocity{0}; // Between 0 and c, in m/s
    double beta{0}; // Between 0-1
    bool antiparticle;
    std::shared_ptr<FourMomentum> four_momentum; // Smart pointer to FourMomentum object
  
  public:
    // default constructor
    lepton(): name{}, rest_mass{}, charge{}, velocity{}, beta{}, antiparticle{}, four_momentum(std::make_shared<FourMomentum>()) {}

    // Parameterised Constructor
    lepton(string particle_name, double particle_rest_mass, int particle_charge, double particle_velocity, bool particle_antiparticle):
      name{particle_name}, rest_mass{particle_rest_mass}, charge{particle_charge}, velocity{particle_velocity}, beta{particle_velocity/speed_of_light}, antiparticle(particle_antiparticle), four_momentum(std::make_shared<FourMomentum>()) 
      {
        // Set random values for energy and momenta using the setters
        four_momentum->set_energy(random_value());
        four_momentum->set_momentum_x(random_value());
        four_momentum->set_momentum_y(random_value());
        four_momentum->set_momentum_z(random_value());
      }

    // Destructor
    virtual ~lepton() {std::cout<<"Destroying lepton"<<std::endl;}

    // Setter functions
    void set_rest_mass(double particle_rest_mass);
    void set_charge(int particle_charge);
    void set_velocity(double particle_velocity);
    void set_beta(double particle_velocity);
    void set_antiparticle(bool particle_antiparticle);

    // Getter functions
    string get_name() const {return name;}
    double get_velocity() const {return velocity;}
    double get_rest_mass() const {return rest_mass;}
    int get_charge() const {return charge;}
    double get_beta() const {return beta;}
    bool get_antiparticle() const {return antiparticle;}

    // Friend declaration
    friend double dot_product(const lepton& particle_1, const lepton& particle_2);
    friend FourMomentum sum(const lepton& particle_1, const lepton& particle_2);

    // Copy constructor
    lepton(const lepton& copy);

    // Copy assignment operator
    lepton& operator=(const lepton& copy);

    // Move constructor
    lepton(lepton&& move) noexcept;

    // Move assignment operator
    lepton& operator=(lepton&& move) noexcept;
    
    // Function to print info about a particle
    virtual void print() const;
};
// End of lepton class

#endif