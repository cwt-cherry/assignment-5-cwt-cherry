#include<iostream>
#include "muon.h"

// setters
void muonClass::set_name(string particle_name)
{
  if(particle_name == "muon" || particle_name == "antimuon")
  {
    name = particle_name;
  }
  else
  {
    throw std::invalid_argument("Invalid particle name.");
  }
}

void muonClass::set_isolated_status(bool status) {isolated_status = status;}

// print muon data
void muonClass::print() const
{
  lepton::print(); // Call base class print function

  // Print additional characteristics specific to muonClass (if/ else if in short form)
  std::cout<<"Isolated status: "<<(isolated_status ? "Isolated" : "Not isolated")<<std::endl;
  std::cout<<"---------------------------------"<<std::endl;
}