// PHYS 30762 Programming in C++
// Assignment 5
// Practice inheritance, smart pointers and friendship in C++ classes

#include<iostream>
#include<string>
#include<vector>
#include<cmath>

using std::string;

#include "random-function.h"
#include "four-momentum.h"
#include "lepton.h"
#include "electron.h"
#include "muon.h"
#include "neutrino.h"
#include "tau.h"

// Friend function to calculate the dot product of two Lepton objects
double dot_product(const lepton& particle_1, const lepton& particle_2)
{
  // Check if both particles have valid four_momentum objects
  if(!particle_1.four_momentum || !particle_2.four_momentum)
  {
    std::cerr<<"Invalid particle: Four-momentum not initialized."<<std::endl;
    return 0.0;
  }

  // Access FourMomentum objects through smart pointers
  const FourMomentum& momentum_1 = *(particle_1.four_momentum);
  const FourMomentum& momentum_2 = *(particle_2.four_momentum);

  // Calculate dot product
  return momentum_1.get_energy() * momentum_2.get_energy() - momentum_1.get_momentum_x() * momentum_2.get_momentum_x() - momentum_1.get_momentum_y() * momentum_2.get_momentum_y() - momentum_1.get_momentum_z() * momentum_2.get_momentum_z();
}

// Friend function to sum two Lepton objects
FourMomentum sum(const lepton& particle_1, const lepton& particle_2)
{
  // Check if both particles have valid FourMomentum objects
  if(!particle_1.four_momentum || !particle_2.four_momentum)
  {
    std::cerr<<"Invalid particle: Four-momentum not initialized."<<std::endl;
    return FourMomentum(); // Return default-constructed FourMomentum
  }

  // Access FourMomentum objects through smart pointers
  const FourMomentum& momentum_1 = *(particle_1.four_momentum);
  const FourMomentum& momentum_2 = *(particle_2.four_momentum);

  // Sum the components
  FourMomentum result;
  result.set_energy(momentum_1.get_energy() + momentum_2.get_energy());
  result.set_momentum_x(momentum_1.get_momentum_x() + momentum_2.get_momentum_x());
  result.set_momentum_y(momentum_1.get_momentum_y() + momentum_2.get_momentum_y());
  result.set_momentum_z(momentum_1.get_momentum_z() + momentum_2.get_momentum_z());
  return result;
}

// Main program
int main()
{
  // Create a vector of shared pointers to lepton objects
  std::vector<std::shared_ptr<lepton>> particles;

  // Add two electrons
  auto electron1 = std::make_shared<electronClass>(electronClass::electron());
  auto electron2 = std::make_shared<electronClass>(electronClass::electron());

  // Add four muons
  auto muon1 = std::make_shared<muonClass>(muonClass::muon());
  auto muon2 = std::make_shared<muonClass>(muonClass::muon());
  auto muon3 = std::make_shared<muonClass>(muonClass::muon());
  auto muon4 = std::make_shared<muonClass>(muonClass::muon());

  // Add one antielectron
  auto electron3 = std::make_shared<electronClass>(electronClass::positron());

  // Add one antimuon
  auto muon5 = std::make_shared<muonClass>(muonClass::antimuon());

  // Add one muon neutrino
  neutrinoClass neutrino1("neutrino", 940.6, 0, random_value(), false, "muon", random_boolean());

  // Add one electron neutrino
  neutrinoClass neutrino2("neutrino", 940.6, 0, random_value(), false, "electron", random_boolean());

  // Add one tau decaying into a muon, a muon antineutrino, and a tau neutrino
  tauClass tau1("tau", 1777, -1, random_value(), false, true, false);
  tau1.leptonic_decay(true, [](){return muonClass::muon();}, "", true);

  // Add one antitau decaying into an antielectron, an electron neutrino, and a tau antineutrino
  tauClass tau2("antitau", 1777, 1, random_value(), true, true, false);
  tau2.leptonic_decay(true, [](){return electronClass::positron();}, "electron", false);

  // put all particles into a vector
  particles.push_back(electron1);
  particles.push_back(electron2);
  particles.push_back(muon1);
  particles.push_back(muon2);
  particles.push_back(muon3);
  particles.push_back(muon4);
  particles.push_back(electron3);
  particles.push_back(muon5);
  particles.push_back(std::make_shared<neutrinoClass>(neutrino1));
  particles.push_back(std::make_shared<neutrinoClass>(neutrino2));
  particles.push_back(std::make_shared<tauClass>(tau1));
  particles.push_back(std::make_shared<tauClass>(tau2));

  // Print information of all particles in the vector
  for(const auto& particle : particles) {particle->print();}

  // Sum the four-vectors of the two electrons and print the result
  FourMomentum electron_sum = sum(*electron1, *electron2);
  std::cout<<"Sum of four-vectors of electrons: "<<"("<<electron_sum.get_energy()<<","<<electron_sum.get_momentum_x()<<","<<electron_sum.get_momentum_y()<<","<<electron_sum.get_momentum_z()<<") MeV"<<std::endl;

  // Take the dot products of the antielectron and antimuon four-vector and print the result
  double dot_product_result = dot_product(*electron3, *muon5);
  std::cout<<"Dot product of antielectron and antimuon four-vector: "<<dot_product_result<<" (MeV)^2"<<std::endl;

  // Create a unique pointer for a new electron and move its data to another electron using std::move
  std::unique_ptr<electronClass> new_electron = std::make_unique<electronClass>(electronClass::electron());
  std::unique_ptr<electronClass> another_electron = std::move(new_electron);
  std::cout << "Address of new electron: " << new_electron.get() << std::endl;
  std::cout << "Address of another electron: " << another_electron.get() << std::endl;
  std::cout<<"new electron with data moved from another electron:"<<std::endl;
  another_electron->print();

  // Create a shared pointer for a tau lepton that is owned by multiple variables
  std::shared_ptr<tauClass> shared_tau = std::make_shared<tauClass>(tauClass::tau());
  std::shared_ptr<tauClass> shared_tau_copy = shared_tau;
  shared_tau->hadronic_decay(random_boolean());
  std::cout << "Addresses of the pointers that own the tau lepton:" << std::endl;
  std::cout << "shared_tau: " << shared_tau.get() << std::endl;
  std::cout << "shared_tau_copy: " << shared_tau_copy.get() << std::endl;
  std::cout<<"tau lepton owned by multiple variables:"<<std::endl; //print out the addresses of the pointer that owns it
  shared_tau->print();

  return 0;
}