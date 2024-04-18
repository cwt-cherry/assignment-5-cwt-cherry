#include<iostream>
#include "tau.h"
#include "neutrino.h"

// setter 
void tauClass::set_name(string particle_name)
{
  if(particle_name == "tau" || particle_name == "antitau")
  {
    name = particle_name;
  }
  else
  {
    throw std::invalid_argument("Invalid particle name.");
  }
}

// Flag for hadronic decay (leave it as flag)
void tauClass::hadronic_decay(bool decay)
{
  if(decay)
  {
    hadronic_decay_status = true;
    if(name=="tau")
    {
      std::cout<<"Tau undergoes hadronic decay into hadrons and a tau neutrino."<<std::endl;
    }
    else if(name=="antitau")
    {
      std::cout<<"Antitau undergoes hadronic decay into hadrons and a antitau neutrino."<<std::endl;
    }
    else
    {
      throw std::invalid_argument("Invalid decay status.");
    }
  }
  else
  {
    hadronic_decay_status = false;
    std::cout<<"Tau/ antitau does not go through hadronic decay."<<std::endl;
  }
}

// Flag for leptonic decay
void tauClass::leptonic_decay(bool decay, std::function<lepton()>decay_product_input)
{
  if(decay)
  {
    leptonic_decay_status = true;
    if(name=="tau")
    {
      // Smart pointers for decay products
      decay_product_1 = std::make_shared<lepton>(decay_product_input());
      decay_product_2 = std::make_shared<neutrinoClass>(neutrinoClass::neutrino());
      decay_product_2->set_flavour("tau");
      decay_product_3 = std::make_shared<neutrinoClass>(neutrinoClass::neutrino());
      decay_product_3->set_flavour(decay_product_1->get_name()); // the neutrino from decay has the same flavour of the lepton
    }
    else if(name=="antitau")
    {
      // Smart pointers for decay products
      decay_product_1 = std::make_shared<lepton>(decay_product_input());
      decay_product_2 = std::make_shared<neutrinoClass>(neutrinoClass::antineutrino());
      decay_product_2->set_flavour("tau");
      decay_product_3 = std::make_shared<neutrinoClass>(neutrinoClass::antineutrino());
      decay_product_3->set_flavour(decay_product_1->get_name()); // the neutrino from decay has the same flavour of the lepton
    }
    else
    {
      leptonic_decay_status = false;
      throw std::invalid_argument("Invalid decay status.");
    }
  }
  else
  {
    leptonic_decay_status = false;
    std::cout<<"Tau/ antitau does not go through leptonic decay."<<std::endl;    
  }
}

// print tau data
void tauClass::print() const
{
  lepton::print();
  if (hadronic_decay_status)
  {
    std::cout<<"Particle undergoes hadronic decay."<<std::endl;
  }
  if (leptonic_decay_status)
  {
    std::cout<<"Particle undergoes leptonic decay."<<std::endl;
    std::cout<<"Decay Products:"<<std::endl;
    // Print information about decay products here
    std::cout<<"1. ";
    if (decay_product_1) decay_product_1->print();
    std::cout<<"2. ";
    if (decay_product_2) decay_product_2->print();
    std::cout<<"3. ";
    if (decay_product_3) decay_product_3->print();
  }
  std::cout<<"---------------------------------"<<std::endl;
}