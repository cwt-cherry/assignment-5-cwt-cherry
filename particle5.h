#ifndef PARTICLE_H
#define PARTICLE_H

#include<iostream>
#include<string>
#include<vector>
#include<cmath>

using std::string;

// Beginning of particle class
class particle
{
private:
  string name; // electron or muon
  double rest_mass{0}; // Unit of MeV
  int charge{1}; // -1 or +1
  const double speed_of_light = 2.9979245e8; // Unit of m/s
  double velocity{0}; // Between 0 and c, in m/s
  double beta{0}; // Between 0-1
  bool antiparticle;

public:
  // Default Constructor
  particle(): name{}, rest_mass{}, charge{}, velocity{}, beta{}, antiparticle{}
  {
  }

  // Parameterised Constructor
  particle(string particle_name, double particle_rest_mass, int particle_charge, double particle_velocity, bool particle_antiparticle):
    name{particle_name}, rest_mass{particle_rest_mass}, charge{particle_charge}, velocity{particle_velocity}, beta{particle_velocity/speed_of_light}, antiparticle(particle_antiparticle)
  {
  }

  // Destructor
  ~particle()
  {
    std::cout<<"Destroying "<<name<<std::endl;
  }

  // Getter functions
  string get_name() const
  {
    return name;
  }

  double get_velocity() const
  {
    return velocity;
  }

  double get_rest_mass() const
  {
    return rest_mass;
  }

  int get_charge() const
  {
    return charge;
  }

  double get_beta() const
  {
    return beta;
  }

  bool get_antiparticle() const
  {
    return antiparticle;
  }

  // Setter functions
  void set_name(string particle_name)
  {
    if(particle_name == "electron" || particle_name == "positron" || particle_name == "muon" || particle_name == "antimuon")
    {
      name = particle_name;
    }
    else
    {
      std::cerr << "Invalid particle name." << std::endl;
      exit(0);
    }
  }

  void set_velocity(double particle_velocity)
  {
    if(speed_of_light >= particle_velocity && particle_velocity >= 0)
    {
      velocity = particle_velocity;
    }
    else
    {
      std::cerr<<"Invalid velocity. Velocity should be between 0 and the speed of light."<<std::endl;
      exit(0);
    }
  }

  void set_rest_mass(double particle_rest_mass)
  {
    rest_mass = particle_rest_mass;
  }

  void set_charge(int particle_charge)
  {
    if(particle_charge == 1 || particle_charge == -1)
    {
      charge = particle_charge;
    }
    else
    {
      std::cerr << "Invalid particle charge. Value should be either +1 or -1" << std::endl;
      exit(0);
    }
  }

  void set_beta(double particle_velocity)
  {
    if(speed_of_light >= particle_velocity && particle_velocity >= 0)
    {
      beta = particle_velocity/speed_of_light;
    }
    else
    {
      std::cerr<<"Invalid beta value. Value should be between 0 and 1."<<std::endl;
      exit(0);
    }
  }

  void set_antiparticle(bool particle_antiparticle)
  {
    antiparticle = particle_antiparticle;
  }

  void print_data() const;

};
// End of particle class and associated member functions

#endif