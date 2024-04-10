#include<iostream>
#include "particle.h"

// Function to print info about a particle
void particle::print_data() const
{
  std::cout<<"particle type: "<<get_name()<<std::endl;
  std::cout<<"rest mass: "<<get_rest_mass()<<" MeV"<<std::endl;
  std::cout<<"charge: "<<get_charge()<<std::endl;
  std::cout<<"velocity: "<<get_velocity()<<" m/s"<<std::endl;
  std::cout<<"beta value: "<<get_beta()<<std::endl;
  std::cout<<"---------------------------------"<<std::endl;
}