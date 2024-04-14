#ifndef NEUTRINO_H
#define NEUTRINO_H

#include<iostream>
#include "lepton.h"
#include "random-function.h"

// neutrinos class (derived class)
class neutrinoClass: public lepton
{
  private:
    string flavour;
    bool hasInteracted; // whether particle interacts with detector *(set to false for now)

  public:
    // default constructor
    neutrinoClass(): lepton{}, flavour{}, hasInteracted{} {}

    // parameterised constructor
    neutrinoClass(string particle_name, double particle_rest_mass, int particle_charge, double particle_velocity, bool particle_antiparticle, string particle_flavour, bool particle_interaction): 
    lepton(particle_name, particle_rest_mass, particle_charge, particle_velocity, particle_antiparticle), flavour{particle_flavour}, hasInteracted{particle_interaction} {}
    
    // destructor
    ~neutrinoClass() {std::cout<<"Destroying "<<name<<std::endl;}

    // data member (cpp)

    // setters
    void set_name(string particle_name);
    void set_flavour(const string& particle_flavour);
    void set_interaction(bool interaction_status);

    // getters
    string get_flavour() const {return flavour;}
    bool get_interaction() const {return hasInteracted;}
    
    // Constructor for neutrinos
    static neutrinoClass neutrino() {return neutrinoClass("neutrino", 940.6, 0, random_value(), false, "electron", random_boolean());}

    // Constructor for antineutrinos
    static neutrinoClass antineutrino() {return neutrinoClass("antineutrino", 940.6, 0, random_value(), true, "electron", random_boolean());}

    // print neutrino data
    void print() const override;

};

#endif