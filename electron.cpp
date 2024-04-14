#include<iostream>
#include "electron.h"

// setters
void electronClass::set_name(string particle_name)
{
  if(particle_name == "electron" || particle_name == "positron")
  {
    name = particle_name;
  }
  else
  {
    throw std::invalid_argument("Invalid particle name.");
  }
}

void electronClass::set_deposit_energy(double EM_1_energy, double EM_2_energy, double HAD_1_energy, double HAD_2_energy)
{
  double total_energy = EM_1_energy + EM_2_energy + HAD_1_energy + HAD_2_energy;
  double normalization_factor = four_momentum->get_energy() / total_energy;

  // Set energies for calorimeter layers after normalizing
  calorimeter_energies.push_back(EM_1_energy * normalization_factor);
  calorimeter_energies.push_back(EM_2_energy * normalization_factor);
  calorimeter_energies.push_back(HAD_1_energy * normalization_factor);
  calorimeter_energies.push_back(HAD_2_energy * normalization_factor);
}

// Function to print energies deposited in calorimeter layers
void electronClass::print_calorimeter_energies() const
{
  std::vector<std::string> layer_names = {"EM 1", "EM 2", "HAD 1", "HAD 2"};
  std::cout<<"Energies deposited in calorimeter layers:"<<std::endl;
  for (size_t i = 0; i < calorimeter_energies.size(); ++i)
  {
    std::cout<<layer_names[i]<<" layer: "<<calorimeter_energies[i]<<" MeV"<<std::endl;
  }
}

// Constructor for electron with deposit energy
electronClass electronClass::electron()
{
  double EM_1_energy = random_value();
  double EM_2_energy = random_value();
  double HAD_1_energy = random_value();
  double HAD_2_energy = random_value();
  electronClass create_electron("electron", 0.511, -1, random_value(), false);
  create_electron.set_deposit_energy(EM_1_energy, EM_2_energy, HAD_1_energy, HAD_2_energy);
  return create_electron;
}

// Constructor for positron (antielectron)
electronClass electronClass::positron()
{
  double EM_1_energy = random_value();
  double EM_2_energy = random_value();
  double HAD_1_energy = random_value();
  double HAD_2_energy = random_value();
  electronClass create_positron("positron", 0.511, +1, random_value(), true);
  create_positron.set_deposit_energy(EM_1_energy, EM_2_energy, HAD_1_energy, HAD_2_energy);
  return create_positron;
}

// Override the print function in each derived class
void electronClass::print() const
{
  lepton::print(); // Call base class print function
  print_calorimeter_energies(); // Print additional characteristics specific to electronClass
}