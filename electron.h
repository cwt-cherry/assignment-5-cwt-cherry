#ifndef ELECTRON_H
#define ELECTRON_H

#include<iostream>
#include<vector>
#include "lepton.h"
#include "random-function.h"

// electron class (derived class)
class electronClass: public lepton
{
  private:
    std::vector<double> calorimeter_energies; // Vector to store energies deposited in each calorimeter layer
    double total_energy;
  
  public:
    // dafault constructor
    electronClass(): lepton{}, calorimeter_energies(4) {}

    // parameterised constructor
    electronClass(string particle_name, double particle_rest_mass, int particle_charge, double particle_velocity, bool particle_antiparticle): 
    lepton(particle_name, particle_rest_mass, particle_charge, particle_velocity, particle_antiparticle), calorimeter_energies{} {}

    // destructor
    ~electronClass() {std::cout<<"Destroying "<<name<<std::endl;}
    
    // setters
    void set_name(string particle_name);
    void set_deposit_energy(double EM_1_energy, double EM_2_energy, double HAD_1_energy, double HAD_2_energy);

    // getters
    std::vector<double> get_deposit_energy() {return calorimeter_energies;}

    // Function to print energies deposited in calorimeter layers
    void print_calorimeter_energies() const;

    // static function for electron
    static electronClass electron();

    // static function for positron (antielectron)
    static electronClass positron();

    // Override the print function in each derived class
    void print() const override;

};

#endif