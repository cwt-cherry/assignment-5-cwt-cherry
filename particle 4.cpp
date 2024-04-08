#include<iostream>
#include "particle.h"
// Implementation of functions goes here

// Assignment operator
particle& particle::operator=(const particle& copy)
{
  std::cout<<"calling copy operator\n";
  // The assignment operator needs to avoid self-assignment using the *this pointer
  if(this != &copy)
  {
    // Copy data from other particle
    name = copy.name;
    charge = copy.charge;
    antiparticle = copy.antiparticle;
    energy = copy.energy;
    momentum_x = copy.momentum_x;
    momentum_y = copy.momentum_y;
    momentum_z = copy.momentum_z;

    // Deep copy of the four-momentum vector
    delete four_momentum;
    four_momentum = new std::vector<double>(*copy.four_momentum);
  }
  return *this;
}

// Move assignment operator
// The move assignment operator needs to correctly reassign the memory from the original object
particle& particle::operator=(particle&& move) noexcept
{
  std::cout<<"calling move operator\n";
  if(this != &move)
  {
    name = move.name;
    charge = move.charge;
    antiparticle = move.antiparticle;
    momentum_x = move.momentum_x;
    momentum_y = move.momentum_y;
    momentum_z = move.momentum_z;

    delete four_momentum;
    four_momentum = move.four_momentum;
    move.four_momentum = nullptr;
  }
  return *this;
}

// Sum operator
particle particle::operator+(const particle &other) const
{
  particle sum;
  sum.set_energy(((*four_momentum)[0] + other.four_momentum->at(0))*speed_of_light);
  sum.set_momentum_x((*four_momentum)[1] + other.four_momentum->at(1));
  sum.set_momentum_y((*four_momentum)[2] + other.four_momentum->at(2));
  sum.set_momentum_z((*four_momentum)[3] + other.four_momentum->at(3));
  return sum;
}

// Dot product operator
double particle::dot_product(const particle& other) const
{
  double dot_product_result{dot_product_result += (*four_momentum)[0] * other.four_momentum->at(0)};
  for(size_t i = 1; i < 4; ++i)
  {
    dot_product_result -= (*four_momentum)[i] * other.four_momentum->at(i);
  }
  return dot_product_result;
}

// Function to print info about a particle
void particle::print_data() const
{
  std::cout<<"---------------------------------"<<std::endl;
  std::cout<<"particle type: "<<get_name()<<std::endl;
  std::cout<<"charge: "<<get_charge()<<std::endl;
  std::cout<<"energy: "<<get_energy()<<" MeV"<<std::endl;
  std::cout<<"momentum x-component: "<<get_momentum_x()<<" MeV"<<std::endl;
  std::cout<<"momentum y-component: "<<get_momentum_y()<<" MeV"<<std::endl;
  std::cout<<"momentum z-component: "<<get_momentum_z()<<" MeV"<<std::endl;
  std::cout<<"four momentum vector: "<<"("<<get_energy()<<","<<get_momentum_x()<<","<<get_momentum_y()<<","<<get_momentum_z()<<") MeV"<<std::endl;
  std::cout<<"---------------------------------"<<std::endl;
}

void particle::print_vector() const
{
  std::cout<<"("<<get_energy()<<","<<get_momentum_x()<<","<<get_momentum_y()<<","<<get_momentum_z()<<") MeV"<<std::endl;
}