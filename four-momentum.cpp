#include<iostream>
#include "four-momentum.h"

// setters
void FourMomentum::set_energy(double particle_energy)
{
  if(particle_energy >= 0)
  {
    energy = particle_energy;
  }
  else
  {
    throw std::invalid_argument("Invalid energy. Energy should be positive.");
  }
}

void FourMomentum::set_momentum_x(double particle_momentum_x)
{
  if(particle_momentum_x >= 0)
  {
    momentum_x = particle_momentum_x;
  }
  else
  {
    throw std::invalid_argument("Invalid momentum. Momentum should be positive.");
  }
}

void FourMomentum::set_momentum_y(double particle_momentum_y)
{
  if(particle_momentum_y >= 0)
  {
    momentum_y = particle_momentum_y;
  }
  else
  {
    throw std::invalid_argument("Invalid momentum. Momentum should be positive.");
  }
}

void FourMomentum::set_momentum_z(double particle_momentum_z)
{
  if(particle_momentum_z >= 0)
  {
    momentum_z = particle_momentum_z;
  }
  else
  {
    throw std::invalid_argument("Invalid momentum. Momentum should be positive.");
  }
}

// Copy constructor
FourMomentum::FourMomentum(const FourMomentum& copy): energy{copy.energy}, momentum_x{copy.momentum_x}, momentum_y{copy.momentum_y}, momentum_z{copy.momentum_z}
{
  std::cout<<"calling copy constructor of four momentum\n";
}

// Copy assignment operator
FourMomentum& FourMomentum::operator=(const FourMomentum& copy)
{
  std::cout<<"calling copy operator of four momentum\n";
  if(this != &copy)
  {
    energy = copy.energy;
    momentum_x = copy.momentum_x;
    momentum_y = copy.momentum_y;
    momentum_z = copy.momentum_z;
  }
  return *this;
}

// Move constructor
FourMomentum::FourMomentum(FourMomentum&& move) noexcept: energy{move.energy}, momentum_x{move.momentum_x}, momentum_y{move.momentum_y}, momentum_z{move.momentum_z}
{
  std::cout<<"calling move constructor of four momentum\n";
  move.energy = 0;
  move.momentum_x = 0;
  move.momentum_y = 0;
  move.momentum_z = 0;
}

// Move assignment operator
FourMomentum& FourMomentum::operator=(FourMomentum&& move) noexcept
{
  std::cout<<"calling move operator of four momentum\n";
  if(this != &move)
  {
    energy = move.energy;
    momentum_x = move.momentum_x;
    momentum_y = move.momentum_y;
    momentum_z = move.momentum_z;
    // Reset other object
    move.energy = 0;
    move.momentum_x = 0;
    move.momentum_y = 0;
    move.momentum_z = 0;
  }
  return *this;
}