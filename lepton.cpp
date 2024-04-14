#include<iostream>
#include "lepton.h"

// Setter functions
void lepton::set_rest_mass(double particle_rest_mass) {rest_mass = particle_rest_mass;}

void lepton::set_charge(int particle_charge)
{
  if(particle_charge == 1 || particle_charge == -1)
  {
    charge = particle_charge;
  }
  else
  {
    throw std::invalid_argument("Invalid particle charge. Value should be either +1 or -1");
  }
}

void lepton::set_velocity(double particle_velocity)
{
  if(speed_of_light >= particle_velocity && particle_velocity >= 0)
  {
    velocity = particle_velocity;
  }
  else
  {
    throw std::invalid_argument("Invalid velocity. Velocity should be between 0 and the speed of light.");
  }
}

void lepton::set_beta(double particle_velocity)
{
  if(speed_of_light >= particle_velocity && particle_velocity >= 0)
  {
    beta = particle_velocity/speed_of_light;
  }
  else
  {
    throw std::invalid_argument("Invalid beta value. Value should be between 0 and 1.");
  }
}

void lepton::set_antiparticle(bool particle_antiparticle) {antiparticle = particle_antiparticle;}

// Copy constructor
lepton::lepton(const lepton& copy):
  name(copy.name),
  rest_mass(copy.rest_mass),
  charge(copy.charge),
  velocity(copy.velocity),
  beta(copy.beta),
  antiparticle(copy.antiparticle),
  four_momentum(copy.four_momentum ? std::make_shared<FourMomentum>(*copy.four_momentum):nullptr)
  {}

// Copy assignment operator
lepton& lepton::operator=(const lepton& copy)
{
  if(this != &copy)
  {
    name = copy.name;
    rest_mass = copy.rest_mass;
    charge = copy.charge;
    velocity = copy.velocity;
    beta = copy.beta;
    antiparticle = copy.antiparticle;
    four_momentum = copy.four_momentum ? std::make_shared<FourMomentum>(*copy.four_momentum):nullptr;
  }
  return *this;
}

// Move constructor
lepton::lepton(lepton&& move) noexcept:
  name(std::move(move.name)),
  rest_mass(std::move(move.rest_mass)),
  charge(std::move(move.charge)),
  velocity(std::move(move.velocity)),
  beta(std::move(move.beta)),
  antiparticle(std::move(move.antiparticle)),
  four_momentum(std::move(move.four_momentum))
{}

// Move assignment operator
lepton& lepton::operator=(lepton&& move) noexcept
{
  if(this != &move)
  {
    name = std::move(move.name);
    rest_mass = std::move(move.rest_mass);
    charge = std::move(move.charge);
    velocity = std::move(move.velocity);
    beta = std::move(move.beta);
    antiparticle = std::move(move.antiparticle);
    four_momentum = std::move(move.four_momentum);
  }
  return *this;
}

// Function to print info about a particle
void lepton::print() const
{
  std::cout<<"---------------------------------"<<std::endl;
  std::cout<<"particle type: "<<get_name()<<std::endl;
  std::cout<<"rest mass: "<<get_rest_mass()<<" MeV"<<std::endl;
  std::cout<<"charge: "<<get_charge()<<std::endl;
  std::cout<<"velocity: "<<get_velocity()<<" m/s"<<std::endl;
  std::cout<<"beta value: "<<get_beta()<<std::endl;
  std::cout<<"antiparticle: "<<std::boolalpha<<get_antiparticle()<<std::endl;
  std::cout<<"four momentum vector: "<<"("<<four_momentum->get_energy()<<","<<four_momentum->get_momentum_x()<<","<<four_momentum->get_momentum_y()<<","<<four_momentum->get_momentum_z()<<") MeV"<<std::endl;
}