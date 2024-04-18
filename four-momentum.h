#ifndef FOUR_MOMENTUM_H
#define FOUR_MOMENTUM_H

// four-momentum class
class FourMomentum
{
  private:
    double energy{0}; // E>0
    double momentum_x{0};
    double momentum_y{0};
    double momentum_z{0};

  public:
    // default constructor
    FourMomentum(): energy{}, momentum_x{}, momentum_y{}, momentum_z{} {}

    // parameterised constructor
    FourMomentum(double particle_energy, double particle_momentum_x, double particle_momentum_y, double particle_momentum_z):
    energy{particle_energy}, momentum_x{particle_momentum_x}, momentum_y{particle_momentum_y}, momentum_z{particle_momentum_z}
    {
      // Check if energy and momenta are non-negative
      if (particle_energy < 0 || particle_momentum_x < 0 || particle_momentum_y < 0 || particle_momentum_z < 0)
      {
        throw std::invalid_argument("Invalid input. Energy and momenta should be non-negative.");
      }
      // Set the values if input is valid
      energy = particle_energy;
      momentum_x = particle_momentum_x;
      momentum_y = particle_momentum_y;
      momentum_z = particle_momentum_z;
    }

    // destructor
    ~FourMomentum() {}

    // setters
    void set_energy(double particle_energy);
    void set_momentum_x(double particle_momentum_x);
    void set_momentum_y(double particle_momentum_y);
    void set_momentum_z(double particle_momentum_z);

    // getters
    double get_energy() const {return energy;}
    double get_momentum_x() const {return momentum_x;}
    double get_momentum_y() const {return momentum_y;}
    double get_momentum_z() const {return momentum_z;}

    // Copy constructor
    FourMomentum(const FourMomentum& copy);

    // Copy assignment operator
    FourMomentum& operator=(const FourMomentum& copy);

    // Move constructor
    FourMomentum(FourMomentum&& move) noexcept;

    // Move assignment operator
    FourMomentum& operator=(FourMomentum&& move) noexcept;

    // Friend declarations
    friend double dot_product(const FourMomentum& momentum_1, const FourMomentum& momentum_2);
    friend FourMomentum sum(const FourMomentum& momentum_1, const FourMomentum& momentum_2);
};

#endif