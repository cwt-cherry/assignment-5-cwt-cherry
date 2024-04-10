// PHYS 30762 Programming in C++
// Assignment 5
// Practice inheritance in C++ classes
// See slides for guidance

#include<iostream>
#include<string>
#include<vector>
#include<cmath>

using std::string;

// Beginning of lepton class (hint: start from assignment 4 particle class)
// base class
class lepton
{
  private:

  protected:
    string name; // electron, muon, tau, neutrino
    double rest_mass{0}; // Unit of MeV
    int charge{1}; // -1 or +1
    const double speed_of_light = 2.9979245e8; // Unit of m/s
    double velocity{0}; // Between 0 and c, in m/s
    double beta{0}; // Between 0-1
    bool antiparticle;

    static double random_value() 
    {
      return static_cast<double>(std::rand()) / RAND_MAX;
    }
  
  public:
    // default constructor
    lepton(): name{}, rest_mass{}, charge{}, velocity{}, beta{}, antiparticle{} {}

    // Parameterised Constructor
    lepton(string particle_name, double particle_rest_mass, int particle_charge, double particle_velocity, bool particle_antiparticle):
      name{particle_name}, rest_mass{particle_rest_mass}, charge{particle_charge}, velocity{particle_velocity}, beta{particle_velocity/speed_of_light}, antiparticle(particle_antiparticle)
    {}

    // Destructor
    ~lepton() {std::cout<<"Destroying "<<name<<std::endl;}

    // Setter functions
    void set_name(string particle_name)
    {
      if(particle_name == "electron" || particle_name == "positron" || particle_name == "muon" || particle_name == "antimuon")
      {
        name = particle_name;
      }
      else
      {
        std::cerr << "Invalid particle name." << std::endl;
        exit(0);
      }
    }

    void set_rest_mass(double particle_rest_mass) {rest_mass = particle_rest_mass;}

    void set_charge(int particle_charge)
    {
      if(particle_charge == 1 || particle_charge == -1)
      {
        charge = particle_charge;
      }
      else
      {
        std::cerr << "Invalid particle charge. Value should be either +1 or -1" << std::endl;
        exit(0);
      }
    }

    void set_velocity(double particle_velocity)
    {
      if(speed_of_light >= particle_velocity && particle_velocity >= 0)
      {
        velocity = particle_velocity;
      }
      else
      {
        std::cerr<<"Invalid velocity. Velocity should be between 0 and the speed of light."<<std::endl;
        exit(0);
      }
    }

    void set_beta(double particle_velocity)
    {
      if(speed_of_light >= particle_velocity && particle_velocity >= 0)
      {
        beta = particle_velocity/speed_of_light;
      }
      else
      {
        std::cerr<<"Invalid beta value. Value should be between 0 and 1."<<std::endl;
        exit(0);
      }
    }

    void set_antiparticle(bool particle_antiparticle) {antiparticle = particle_antiparticle;}

    // Getter functions
  string get_name() const {return name;}
  double get_velocity() const {return velocity;}
  double get_rest_mass() const {return rest_mass;}
  int get_charge() const {return charge;}
  double get_beta() const {return beta;}
  bool get_antiparticle() const {return antiparticle;}

};
// End of lepton class and associated member functions

// Derived classes for other particles, and four-momentum class go here

// electron class (derived class)
class electronClass: public lepton
{
  // private:
  //   string electron;
  //   double mass{0.511};
  //   int charge{-1};
  //   double velocity{0};
  //   bool antiparticle;

  public:
    // dafault constructor
    electronClass(): lepton{} {}

    // parameterised constructor
    electronClass(string particle_name, double particle_rest_mass, int particle_charge, double particle_velocity, bool particle_antiparticle): 
    lepton(particle_name, particle_rest_mass, particle_charge, particle_velocity, particle_antiparticle) {}

    // destructor
    ~electronClass() {std::cout<<"Destroying "<<name<<std::endl;}

    // Constructor for electron
    static electronClass electron()
    {
      return electronClass("electron", 0.511, -1, random_value(), false);
    }

    // Constructor for positron (antielectron)
    static electronClass positron()
    {
      return electronClass("positron", 0.511, +1, random_value(), true);
    }

    // data members (cpp file)
    // assume calorimeter has 4 layers, measure the energy a particle loses as it passes through the detector 
    // EM_1, EM_2, HAD_1, HAD_2
    // liquid argon calorimeter (LAr):
    // measures the energy of electrons, photons and hadrons, identify photons and electrons
    // tile hadronic calorimeter:
    // measure energy of hadronic particles

};

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

    // Constructor for muon
    muonClass(): lepton("muon", 105.6, -1, random_value(), false), isolated_status{false} {}

    // Constructor for antimuon
    static muonClass antimuon()
    {
      return muonClass("antimuon", 105.6, +1, random_value(), true, false);
    }

    // data members (cpp file)

    // Getter and setter for isolated status
    void set_isolated_status(bool status) 
    { 
      isolated_status = status;
    }

    bool get_isolated_status() const 
    { 
      return isolated_status; 
    }
};

// tau class (derived class)
class tauClass: public lepton
{
  private:
    bool hadronic_decay;
    bool leptonic_decay;
    std::unique_ptr<lepton> decay_product_1; // Smart pointer for decay product 1
    std::unique_ptr<tauClass> decay_product_2; // Smart pointer for decay product 2
    std::unique_ptr<neutrinoClass> decay_product_3; // Smart pointer for decay product 3

  public:

    // default constructor
    tauClass(): lepton{}, leptonic_decay{} {}

    // parameterised constructor
    tauClass(string particle_name, double particle_rest_mass, int particle_charge, double particle_velocity, bool particle_antiparticle, bool particle_leptonic_decay, bool particle_hadronic_decay): 
    lepton(particle_name, particle_rest_mass, particle_charge, particle_velocity, particle_antiparticle), leptonic_decay{particle_leptonic_decay}, hadronic_decay{particle_hadronic_decay} {}

    // destructor
    ~tauClass() {std::cout<<"Destroying "<<name<<std::endl;} 

    // Constructor for tau
    static tauClass tau()
    {
      return tauClass("antitau", 1777, -1, random_value(), false, true, false);
    }

    // Constructor for antitau
    static tauClass antitau()
    {
      return tauClass("antitau", 1777, +1, random_value(), true, true, false);
    }

    // Flag for hadronic decay
    void set_hadronic_decay(bool decay)
    {
      hadronic_decay = decay;
      if(hadronic_decay)
      {
        if(name=="tau")
        {
          std::cout<<"Tau undergoes hadronic decay into hadrons and a tau neutrino."<<std::endl;
          // change tau (obj) into hadrons and tau neutrino (using the objects from derived class)
        }
        else if(name=="antitau")
        {
          std::cout<<"Antitau undergoes hadronic decay into hadrons and a antitau neutrino."<<std::endl;
          // change the antitau object into hadrons and antitau neutrino (using the objects from derived class)
        }
        else
        {
          throw std::invalid_argument("Invalid decay status.");
        }
      }
      else
      {
        throw std::invalid_argument("Tau/ antitau does not go through hadronic decay.");
      }
    }

    void set_leptonic_decay(bool decay)
    {
      leptonic_decay =  decay;
      if (leptonic_decay)
      {
        if (name=="tau")
        {
          // Smart pointers for decay products
          decay_product_1 = std::make_unique<lepton>();
          decay_product_2 = std::make_unique<tauClass>(tauClass::tau()); // Creating a tau object using the static member function
          decay_product_3 = std::make_unique<neutrinoClass>();
          decay_product_3->set_flavour(decay_product_1->get_name());
          delete this;
        }
        else if (name=="antitau")
        {
          // Smart pointers for decay products
          decay_product_1 = std::make_unique<lepton>();
          decay_product_2 = std::make_unique<tauClass>(tauClass::antitau()); // Creating an antitau object using the static member function
          decay_product_3 = std::make_unique<neutrinoClass>();
          decay_product_3->set_flavour(decay_product_1->get_name());
          delete this;
        }
        else
        {
          throw std::invalid_argument("Invalid decay status.");
        }
      }
    }

};

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

    // setter and getters
    void set_flavour(const string& particle_flavour)
    {
      // Check if the provided flavour is valid
      if(particle_flavour == "electron" || particle_flavour == "muon" || particle_flavour == "tau")
      {
        flavour = particle_flavour + " neutrino";
      }
      else if(particle_flavour == "positron" || particle_flavour == "antimuon" || particle_flavour == "antitau")
      {
        flavour = particle_flavour + " neutrino";
      }
      else
      {
        // If the provided flavour is not valid, set a default flavour
        flavour = "unknown";
      }
    }

    string get_flavour() const
    {
      return flavour;
    }

    void set_interaction(bool interaction_status)
    {
      hasInteracted = interaction_status;
    }

    bool get_interaction() const
    {
      return hasInteracted;
    }
    
    // Constructor for neutrinos
    //neutrinoClass(): lepton("neutrino", 940.6, 0, random_value(), false), flavour(get_flavour), hasInteracted(get_interaction) {}
    static neutrinoClass neutrino()
    {
      return neutrinoClass("neutrino", 940.6, 0, random_value(), false, "unknown", false);
    }

    // Constructor for antineutrinos
    static neutrinoClass antineutrino()
    {
      return neutrinoClass("antineutrino", 940.6, 0, random_value(), true, "unknown", true);
    }

    // data member (cpp)


};

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
    {}

    // destructor
    ~FourMomentum() {}

    // setter for energy
    void set_energy(double particle_energy)
    {
      if(particle_energy >= 0) // not limiting energy to the speed of light due to change in slides
      {
        energy = particle_energy;
      }
      else
      {
        throw std::invalid_argument("Energy should be positive.");
      }
    }

    // smart pointer to a four-momentum object contained in each particle (unique or shared)

};

// Implementation of functions from a class should be done outside the class, preferably in another file

// Main program
int main()
{
  return 0;
}