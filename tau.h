#ifndef TAU_H
#define TAU_H

#include<iostream>
#include <functional>

#include "lepton.h"
#include "neutrino.h"
#include "random-function.h"

// tau class (derived class)
class tauClass: public lepton
{
  private:
    bool hadronic_decay_status;
    bool leptonic_decay_status;
    std::shared_ptr<lepton> decay_product_1; // Smart pointer for decay product 1
    std::shared_ptr<neutrinoClass> decay_product_2; // Smart pointer for decay product 2
    std::shared_ptr<neutrinoClass> decay_product_3; // Smart pointer for decay product 3

  public:

    // default constructor
    tauClass(): lepton{}, hadronic_decay_status{}, leptonic_decay_status{} {}

    // parameterised constructor
    tauClass(string particle_name, double particle_rest_mass, int particle_charge, double particle_velocity, bool particle_antiparticle, bool particle_leptonic_decay, bool particle_hadronic_decay): 
    lepton(particle_name, particle_rest_mass, particle_charge, particle_velocity, particle_antiparticle), leptonic_decay_status{particle_leptonic_decay}, hadronic_decay_status{particle_hadronic_decay} {}

    // destructor
    ~tauClass() {std::cout<<"Destroying "<<name<<std::endl;} 

    // setter 
    void set_name(string particle_name);

    // Flag for hadronic decay (leave it as flag)
    void hadronic_decay(bool decay);

    // Flag for leptonic decay
    void leptonic_decay(bool decay, std::function<lepton()>decay_product_input, string decay_product_3_flavour, bool decay_product_3_antiparticle);

    // Constructor for tau
    static tauClass tau() {return tauClass("tau", 1777, -1, random_value(), false, random_boolean(), !random_boolean());} // either goes through hadronic or leptonic decay

    // Constructor for antitau
    static tauClass antitau() {return tauClass("antitau", 1777, +1, random_value(), true, random_boolean(), !random_boolean());}

    // print tau data
    void print() const override;
};

#endif