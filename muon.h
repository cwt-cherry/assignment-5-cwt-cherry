#ifndef MUON_H
#define MUON_H

#include<iostream>
#include "lepton.h"
#include "random-function.h"

// muon class (derived class)
class muonClass: public lepton
{
  private:
    bool isolated_status; // indicate if muon is isolated from other particles

  public:
    // default constructor
    muonClass(): lepton{}, isolated_status{false} {}

    // parameterised constructor
    muonClass(string particle_name, double particle_rest_mass, int particle_charge, double particle_velocity, bool particle_antiparticle, bool particle_isolated_status): 
    lepton(particle_name, particle_rest_mass, particle_charge, particle_velocity, particle_antiparticle), isolated_status{particle_isolated_status} {}
    
    // destructor
    ~muonClass() {std::cout<<"Destroying "<<name<<std::endl;}

    // setters
    void set_name(string particle_name);
    void set_isolated_status(bool status);

    // getters
    bool get_isolated_status() const {return isolated_status;}

    // Constructor for muon
    static muonClass muon() {return muonClass("muon", 105.6, -1, random_value(), false, random_boolean());}

    // Constructor for antimuon
    static muonClass antimuon() {return muonClass("antimuon", 105.6, +1, random_value(), true, random_boolean());}

    // print muon data
    void print() const override;

};

#endif