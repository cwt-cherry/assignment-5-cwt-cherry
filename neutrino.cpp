#include<iostream>
#include "neutrino.h"

    // setters
    void neutrinoClass::set_name(string particle_name)
    {
      if(particle_name == "neutrino" || particle_name == "antineutrino")
      {
        name = particle_name;
      }
      else
      {
        throw std::invalid_argument("Invalid particle name.");
      }
    }

    void neutrinoClass::set_flavour(const string& particle_flavour)
    {
      if(particle_flavour == "electron" || particle_flavour == "muon" || particle_flavour == "tau")
      {
        flavour = particle_flavour;
      }
      else
      {
        throw std::invalid_argument("Invalid neutrino flavour.");
      }
    }

    void neutrinoClass::set_interaction(bool interaction_status) {hasInteracted = interaction_status;}

    // print neutrino data
    void neutrinoClass::print() const
    {
      lepton::print(); // Call base class print function

      // Print additional characteristics specific to neutrinoClass
      std::cout<<"Flavour: "<<flavour<<std::endl; 
      std::cout<<"Interacted: "<<(hasInteracted ? "Yes" : "No")<<std::endl;
      std::cout<<"---------------------------------"<<std::endl;
    }