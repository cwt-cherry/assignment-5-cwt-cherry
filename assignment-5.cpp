// PHYS 30762 Programming in C++
// Assignment 5
// Practice inheritance in C++ classes
// See slides for guidance

#include<iostream>
#include<string>
#include<vector>
#include<cmath>
#include<memory> // Include the <memory> header for smart pointers

using std::string;

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

    // setters
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

    void set_momentum_x(double particle_momentum_x)
    {
      if(particle_momentum_x >= 0) // not limiting energy to the speed of light due to change in slides
      {
        momentum_x = particle_momentum_x;
      }
      else
      {
        throw std::invalid_argument("Invalid momentum. Momentum should be positive.");
      }
    }

    void set_momentum_y(double particle_momentum_y)
    {
      if(particle_momentum_y >= 0) // not limiting energy to the speed of light due to change in slides
      {
        momentum_y = particle_momentum_y;
      }
      else
      {
        throw std::invalid_argument("Invalid momentum. Momentum should be positive.");
      }
    }

    void set_momentum_z(double particle_momentum_z)
    {
      if(particle_momentum_z >= 0) // not limiting energy to the speed of light due to change in slides
      {
        momentum_z = particle_momentum_z;
      }
      else
      {
        throw std::invalid_argument("Invalid momentum. Momentum should be positive.");
      }
    }

    // getters
    double get_energy() const {return energy;}
    double get_momentum_x() const {return momentum_x;}
    double get_momentum_y() const {return momentum_y;}
    double get_momentum_z() const {return momentum_z;}

    // Copy constructor
    FourMomentum(const FourMomentum& copy): energy{copy.energy}, momentum_x{copy.momentum_x}, momentum_y{copy.momentum_y}, momentum_z{copy.momentum_z}
    {
      std::cout<<"calling copy constructor of four momentum\n";
    }

    // Copy assignment operator
    FourMomentum& operator=(const FourMomentum& copy)
    {
      std::cout<<"calling copy operator of four momentum\n";
      if (this != &copy)
      {
        energy = copy.energy;
        momentum_x = copy.momentum_x;
        momentum_y = copy.momentum_y;
        momentum_z = copy.momentum_z;
      }
      return *this;
    }

    // Move constructor
    FourMomentum(FourMomentum&& move) noexcept: energy{move.energy}, momentum_x{move.momentum_x}, momentum_y{move.momentum_y}, momentum_z{move.momentum_z}
    {
      std::cout<<"calling move constructor of four momentum\n";
      move.energy = 0;
      move.momentum_x = 0;
      move.momentum_y = 0;
      move.momentum_z = 0;
      
    }

    // Move assignment operator
    FourMomentum& operator=(FourMomentum&& move) noexcept
    {
      std::cout<<"calling move operator of four momentum\n";
      if (this != &move)
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

  // Friend declarations
  friend double dot_product(const FourMomentum& momentum1, const FourMomentum& momentum2);
  friend FourMomentum sum(const FourMomentum& momentum1, const FourMomentum& momentum2);

};

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
    std::unique_ptr<FourMomentum> fourMomentum; // Smart pointer to FourMomentum object
  
  public:
    // default constructor
    lepton(): name{}, rest_mass{}, charge{}, velocity{}, beta{}, antiparticle{}, fourMomentum(std::make_unique<FourMomentum>()) {}

    // Parameterised Constructor
    lepton(string particle_name, double particle_rest_mass, int particle_charge, double particle_velocity, bool particle_antiparticle):
      name{particle_name}, rest_mass{particle_rest_mass}, charge{particle_charge}, velocity{particle_velocity}, beta{particle_velocity/speed_of_light}, antiparticle(particle_antiparticle), fourMomentum(std::make_unique<FourMomentum>())

    {}

    // Destructor
    //~lepton() {std::cout<<"Destroying "<<name<<std::endl;}
    virtual ~lepton() {std::cout << "Destroying " << name << std::endl;}


    // Setter functions
    void set_name(string particle_name)
    {
      if(particle_name == "electron" || particle_name == "positron" || particle_name == "muon" || particle_name == "antimuon")
      {
        name = particle_name;
      }
      else
      {
        throw std::invalid_argument("Invalid particle name.");
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
        throw std::invalid_argument("Invalid particle charge. Value should be either +1 or -1");
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
        throw std::invalid_argument("Invalid velocity. Velocity should be between 0 and the speed of light.");
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
        throw std::invalid_argument("Invalid beta value. Value should be between 0 and 1.");
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

  // Function to print info about a particle
  void print_data() const
  {
    std::cout<<"particle type: "<<get_name()<<std::endl;
    std::cout<<"rest mass: "<<get_rest_mass()<<" MeV"<<std::endl;
    std::cout<<"charge: "<<get_charge()<<std::endl;
    std::cout<<"velocity: "<<get_velocity()<<" m/s"<<std::endl;
    std::cout<<"beta value: "<<get_beta()<<std::endl;
    std::cout<<"---------------------------------"<<std::endl;
  }

  // Friend declaration
  friend double dot_product(const lepton& particle1, const lepton& particle2);
  friend FourMomentum sum(const lepton& particle1, const lepton& particle2);

  // Static member function declaration
  static double random_value();

};
// End of lepton class and associated member functions

// Static member function definition
double lepton::random_value()
{
  return static_cast<double>(std::rand()) / RAND_MAX;
}

// Friend function to calculate the dot product of two Lepton objects
double dot_product(const lepton& particle1, const lepton& particle2)
{
  // Check if both particles have valid FourMomentum objects
  if (!particle1.fourMomentum || !particle2.fourMomentum)
  {
    std::cerr << "Invalid particle: Four-momentum not initialized." << std::endl;
    return 0.0;
  }

  // Access FourMomentum objects through smart pointers
  const FourMomentum& momentum1 = *(particle1.fourMomentum);
  const FourMomentum& momentum2 = *(particle2.fourMomentum);

  // Calculate dot product
  return momentum1.get_energy() * momentum2.get_energy() - momentum1.get_momentum_x() * momentum2.get_momentum_x() - momentum1.get_momentum_y() * momentum2.get_momentum_y() - momentum1.get_momentum_z() * momentum2.get_momentum_z();
}

// Friend function to sum two Lepton objects
FourMomentum sum(const lepton& particle1, const lepton& particle2)
{
  // Check if both particles have valid FourMomentum objects
  if (!particle1.fourMomentum || !particle2.fourMomentum)
  {
    std::cerr << "Invalid particle: Four-momentum not initialized." << std::endl;
    return FourMomentum(); // Return default-constructed FourMomentum
  }

  // Access FourMomentum objects through smart pointers
  const FourMomentum& momentum1 = *(particle1.fourMomentum);
  const FourMomentum& momentum2 = *(particle2.fourMomentum);

  // Sum the components
  FourMomentum result;
  result.set_energy(momentum1.get_energy() + momentum2.get_energy());
  result.set_momentum_x(momentum1.get_momentum_x() + momentum2.get_momentum_x());
  result.set_momentum_y(momentum1.get_momentum_y() + momentum2.get_momentum_y());
  result.set_momentum_z(momentum1.get_momentum_z() + momentum2.get_momentum_z());
  return result;
}

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
    static muonClass muon()
    {
      return muonClass("muon", 105.6, -1, random_value(), false, false);
    }

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
    std::unique_ptr<lepton> decay_product_1; // Smart pointer for decay product 1
    std::unique_ptr<tauClass> decay_product_2; // Smart pointer for decay product 2
    std::unique_ptr<neutrinoClass> decay_product_3; // Smart pointer for decay product 3

  public:

    // default constructor
    tauClass(): lepton{} {}

    // parameterised constructor
    tauClass(string particle_name, double particle_rest_mass, int particle_charge, double particle_velocity, bool particle_antiparticle, bool particle_leptonic_decay, bool particle_hadronic_decay): 
    lepton(particle_name, particle_rest_mass, particle_charge, particle_velocity, particle_antiparticle) {}

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
    void hadronic_decay(bool decay)
    {
      if(decay==true)
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

    // Flag for leptonic decay
    void leptonic_decay(bool decay)
    {
      if (decay==true)
      {
        if (name=="tau")
        {
          // Smart pointers for decay products
          decay_product_1 = std::make_unique<lepton>();
          decay_product_2 = std::make_unique<tauClass>(tauClass::tau()); // Creating a tau object using the static member function
          decay_product_3 = std::make_unique<neutrinoClass>();
          decay_product_3->set_flavour(decay_product_1->get_name());
          //delete this;
        }
        else if (name=="antitau")
        {
          // Smart pointers for decay products
          decay_product_1 = std::make_unique<lepton>();
          decay_product_2 = std::make_unique<tauClass>(tauClass::antitau()); // Creating an antitau object using the static member function
          decay_product_3 = std::make_unique<neutrinoClass>();
          decay_product_3->set_flavour(decay_product_1->get_name());
          //delete this;
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

// Implementation of functions from a class should be done outside the class, preferably in another file

// Main program
int main()
{
  // Create a vector of particles
  std::vector<std::unique_ptr<lepton>> particles;

  // Add two electrons
  particles.push_back(std::make_unique<electronClass>(electronClass::electron()));
  particles.push_back(std::make_unique<electronClass>(electronClass::positron()));

  // Add four muons
  particles.push_back(std::make_unique<muonClass>());
  particles.push_back(std::make_unique<muonClass>());
  particles.push_back(std::make_unique<muonClass>());
  particles.push_back(std::make_unique<muonClass>());
  particles.push_back(std::make_unique<muonClass>(muonClass::antimuon()));

  // Add one antielectron
  particles.push_back(std::make_unique<electronClass>(electronClass::positron()));

  // Add one antimuon
  particles.push_back(std::make_unique<muonClass>(muonClass::antimuon()));

  // Add one muon neutrino
  particles.push_back(std::make_unique<neutrinoClass>(neutrinoClass::neutrino()));

  // Add one electron neutrino
  particles.push_back(std::make_unique<neutrinoClass>(neutrinoClass::antineutrino()));

  // Add one tau decaying into a muon, a muon antineutrino, and a tau neutrino
  tauClass tauParticle = tauClass::tau();
  tauParticle.leptonic_decay(true);
  particles.push_back(std::make_unique<tauClass>(tauParticle));

  // Add one antitau decaying into an antielectron, an electron neutrino, and a tau antineutrino
  tauClass antitauParticle = tauClass::antitau();
  antitauParticle.leptonic_decay(true);
  particles.push_back(std::make_unique<tauClass>(antitauParticle));

  // Print information of all particles in the vector
  for (const auto& particle : particles)
  {
      particle->print_data();
  }

  // Sum the four-vectors of the two electrons and print the result
  std::cout << "Sum of four-vectors of electrons:" << std::endl;
  FourMomentum electron_sum = sum(*particles[0], *particles[1]);
  std::cout << "Energy: " << electron_sum.get_energy() << std::endl;
  std::cout << "Momentum X: " << electron_sum.get_momentum_x() << std::endl;
  std::cout << "Momentum Y: " << electron_sum.get_momentum_y() << std::endl;
  std::cout << "Momentum Z: " << electron_sum.get_momentum_z() << std::endl;

  // Take the dot products of the antielectron and antimuon four-vector and print the result
  std::cout << "Dot product of antielectron and antimuon four-vector: ";
  double dot_product_result = dot_product(*particles[2], *particles[3]);
  std::cout << dot_product_result << std::endl;

  // Create a unique pointer for a new electron and move its data to another electron using std::move
  std::unique_ptr<electronClass> newElectron = std::make_unique<electronClass>(electronClass::electron());
  std::unique_ptr<electronClass> anotherElectron = std::move(newElectron);

  // Create a shared pointer for a tau lepton that is owned by multiple variables
  std::shared_ptr<tauClass> sharedTau = std::make_shared<tauClass>(tauClass::tau());
  std::shared_ptr<tauClass> sharedTauCopy = sharedTau;

  return 0;
}
