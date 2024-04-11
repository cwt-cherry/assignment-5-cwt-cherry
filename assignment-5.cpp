// PHYS 30762 Programming in C++
// Assignment 5
// Practice inheritance in C++ classes
// See slides for guidance

#include<iostream>
#include<string>
#include<vector>
#include<cmath>
#include<memory> // Include the <memory> header for smart pointers

#include <functional>

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
        throw std::invalid_argument("Invalid energy. Energy should be positive.");
      }
    }

    void set_momentum_x(double particle_momentum_x)
    {
      if(particle_momentum_x >= 0) // not limiting momentum to the speed of light due to change in slides
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
      if(particle_momentum_y >= 0) // not limiting momentum to the speed of light due to change in slides
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
      if(particle_momentum_z >= 0) // not limiting momentum to the speed of light due to change in slides
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
    std::shared_ptr<FourMomentum> fourMomentum; // Smart pointer to FourMomentum object
  
  public:
    // default constructor
    lepton(): name{}, rest_mass{}, charge{}, velocity{}, beta{}, antiparticle{}, fourMomentum(std::make_shared<FourMomentum>()) {}

    // Parameterised Constructor
    lepton(string particle_name, double particle_rest_mass, int particle_charge, double particle_velocity, bool particle_antiparticle):
      name{particle_name}, rest_mass{particle_rest_mass}, charge{particle_charge}, velocity{particle_velocity}, beta{particle_velocity/speed_of_light}, antiparticle(particle_antiparticle), fourMomentum(std::make_shared<FourMomentum>()) {}

    // Destructor
    virtual ~lepton() {std::cout<<"Destroying lepton"<<std::endl;}

    // Setter functions
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
    virtual void print() const
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

    // Copy constructor
    lepton(const lepton& copy):
      name(copy.name),
      rest_mass(copy.rest_mass),
      charge(copy.charge),
      velocity(copy.velocity),
      beta(copy.beta),
      antiparticle(copy.antiparticle),
      fourMomentum(copy.fourMomentum ? std::make_shared<FourMomentum>(*copy.fourMomentum) : nullptr)
    {}

    // Copy assignment operator
    lepton& operator=(const lepton& copy)
    {
      if(this != &copy)
      {
        name = copy.name;
        rest_mass = copy.rest_mass;
        charge = copy.charge;
        velocity = copy.velocity;
        beta = copy.beta;
        antiparticle = copy.antiparticle;
        fourMomentum = copy.fourMomentum ? std::make_shared<FourMomentum>(*copy.fourMomentum) : nullptr;
      }
      return *this;
    }

    // Move constructor
    lepton(lepton&& move) noexcept:
      name(std::move(move.name)),
      rest_mass(std::move(move.rest_mass)),
      charge(std::move(move.charge)),
      velocity(std::move(move.velocity)),
      beta(std::move(move.beta)),
      antiparticle(std::move(move.antiparticle)),
      fourMomentum(std::move(move.fourMomentum))
    {}

    // Move assignment operator
    lepton& operator=(lepton&& move) noexcept
    {
      if(this != &move)
      {
        name = std::move(move.name);
        rest_mass = std::move(move.rest_mass);
        charge = std::move(move.charge);
        velocity = std::move(move.velocity);
        beta = std::move(move.beta);
        antiparticle = std::move(move.antiparticle);
        fourMomentum = std::move(move.fourMomentum);
      }
      return *this;
    }

};
// End of lepton class and associated member functions

// generate random number
double lepton::random_value() {return static_cast<double>(std::rand()) / RAND_MAX;}

// Friend function to calculate the dot product of two Lepton objects
double dot_product(const lepton& particle1, const lepton& particle2)
{
  // Check if both particles have valid FourMomentum objects
  if(!particle1.fourMomentum || !particle2.fourMomentum)
  {
    std::cerr<<"Invalid particle: Four-momentum not initialized."<<std::endl;
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
  if(!particle1.fourMomentum || !particle2.fourMomentum)
  {
    std::cerr<<"Invalid particle: Four-momentum not initialized."<<std::endl;
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
  private:
    std::vector<double> calorimeter_energies; // Vector to store energies deposited in each calorimeter layer
    FourMomentum four_momentum;
    double total_energy;
  
  public:
    // dafault constructor
    electronClass(): lepton{} {}

    // parameterised constructor
    electronClass(string particle_name, double particle_rest_mass, int particle_charge, double particle_velocity, bool particle_antiparticle): 
    lepton(particle_name, particle_rest_mass, particle_charge, particle_velocity, particle_antiparticle) {}

    // destructor
    ~electronClass() {std::cout<<"Destroying "<<name<<std::endl;}

    // data members (cpp file)
    // assume calorimeter has 4 layers, measure the energy a particle loses as it passes through the detector 
    // EM_1, EM_2, HAD_1, HAD_2
    // liquid argon calorimeter (LAr):
    // measures the energy of electrons, photons and hadrons, identify photons and electrons
    // tile hadronic calorimeter:
    // measure energy of hadronic particles
    
    // setters
    void set_name(string particle_name)
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

    void set_deposit_energy(const std::string& layer)
    {
      if(layer == "EM_1" || layer == "EM_2" || layer == "HAD_1" || layer == "HAD_2")
      {
        calorimeter_energies[0] = random_value();
        calorimeter_energies[1] = random_value();
        calorimeter_energies[2] = random_value();
        calorimeter_energies[3] = random_value();
      }
      else
      {
        throw std::invalid_argument("Error: Invalid calorimeter layer specified.");
      }
    }

    void set_total_energy()
    {
      if(calorimeter_energies[0] + calorimeter_energies[1] + calorimeter_energies[2] + calorimeter_energies[3]==four_momentum.get_energy())
      {
        total_energy = calorimeter_energies[0] + calorimeter_energies[1] + calorimeter_energies[2] + calorimeter_energies[3];
      }
      else
      {
        throw std::invalid_argument("Error. Total energy deposited in the calorimeter layers does not match the energy in four-momentum vector.");
      }
    }

    // getters
    std::vector<double> get_deposit_energy() {return calorimeter_energies;}
    double get_total_energy() const {return total_energy;}

    // Function to print energies deposited in calorimeter layers
    void print_calorimeter_energies() const
    {
      std::cout<<"Energies deposited in calorimeter layers:"<<std::endl;
      for(size_t i = 0; i < calorimeter_energies.size(); ++i)
      {
        std::cout<<"Layer "<<i + 1<<": "<<calorimeter_energies[i]<<" MeV"<<std::endl;
      }
    }

    // Constructor for electron
    static electronClass electron() {return electronClass("electron", 0.511, -1, random_value(), false);}

    // Constructor for positron (antielectron)
    static electronClass positron() {return electronClass("positron", 0.511, +1, random_value(), true);}

    // Override the print function in each derived class
    void print() const override
    {
      lepton::print(); // Call base class print function
      print_calorimeter_energies(); // Print additional characteristics specific to electronClass
    }

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

    // data members (cpp file)

    // setters
    void set_name(string particle_name)
    {
      if(particle_name == "muon" || particle_name == "antimuon")
      {
        name = particle_name;
      }
      else
      {
        throw std::invalid_argument("Invalid particle name.");
      }
    }

    void set_isolated_status(bool status) {isolated_status = status;}

    // getters
    bool get_isolated_status() const {return isolated_status;}

    // Constructor for muon
    static muonClass muon() {return muonClass("muon", 105.6, -1, random_value(), false, false);}

    // Constructor for antimuon
    static muonClass antimuon() {return muonClass("antimuon", 105.6, +1, random_value(), true, false);}

    // print muon data
    void print() const override
    {
      lepton::print(); // Call base class print function

      // Print additional characteristics specific to muonClass
      std::cout << "Isolated status: " << (isolated_status ? "Isolated" : "Not isolated") << std::endl;
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

    // data member (cpp)

    // setters
    void set_name(string particle_name)
    {
      if(particle_name == "neutrino" || particle_name == "antineutrino")
      {
        name = particle_name;
      }
      else
      {
        throw std::invalid_argument("Invalid particle name.");
      }
    }

    void set_flavour(const string& particle_flavour)
    {
      if(particle_flavour == "electron" || particle_flavour == "muon" || particle_flavour == "tau")
      {
        flavour = particle_flavour;
      }
      else
      {
        throw std::invalid_argument("Invalid neutrino flavour.");
      }
    }

    void set_interaction(bool interaction_status) {hasInteracted = interaction_status;}

    // getters
    string get_flavour() const {return flavour;}
    bool get_interaction() const {return hasInteracted;}
    
    // Constructor for neutrinos
    static neutrinoClass neutrino() {return neutrinoClass("neutrino", 940.6, 0, random_value(), false, "electron", false);}

    // Constructor for antineutrinos
    static neutrinoClass antineutrino() {return neutrinoClass("antineutrino", 940.6, 0, random_value(), true, "electron", true);}

    // print neutrino data
    void print() const override
    {
      lepton::print(); // Call base class print function

      // Print additional characteristics specific to neutrinoClass
      std::cout << "Flavour: " << flavour << std::endl; 
      std::cout << "Interacted: " << (hasInteracted ? "Yes" : "No") << std::endl;
    }

};

// tau class (derived class)
class tauClass: public lepton
{
  private:
    std::shared_ptr<lepton> decay_product_1; // Smart pointer for decay product 1
    std::shared_ptr<neutrinoClass> decay_product_2; // Smart pointer for decay product 2
    std::shared_ptr<neutrinoClass> decay_product_3; // Smart pointer for decay product 3

  public:

    // default constructor
    tauClass(): lepton{} {}

    // parameterised constructor
    tauClass(string particle_name, double particle_rest_mass, int particle_charge, double particle_velocity, bool particle_antiparticle, bool particle_leptonic_decay, bool particle_hadronic_decay): 
    lepton(particle_name, particle_rest_mass, particle_charge, particle_velocity, particle_antiparticle) {}

    // destructor
    ~tauClass() {std::cout<<"Destroying "<<name<<std::endl;} 

    // Constructor for tau
    static tauClass tau() {return tauClass("tau", 1777, -1, random_value(), false, true, false);}

    // Constructor for antitau
    static tauClass antitau() {return tauClass("antitau", 1777, +1, random_value(), true, true, false);}

    // setter 
    void set_name(string particle_name)
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
    void hadronic_decay(bool decay)
    {
      if(decay==true)
      {
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
        throw std::invalid_argument("Tau/ antitau does not go through hadronic decay.");
      }
    }

    // Flag for leptonic decay
    void leptonic_decay(bool decay, std::function<lepton()>decay_product_input)
    {
      if(decay==true)
      {
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
          //decay_product_1 = std::make_shared<lepton>(decay_product_1_type);
          decay_product_1 = std::make_shared<lepton>(decay_product_input());
          decay_product_2 = std::make_shared<neutrinoClass>(neutrinoClass::antineutrino());
          decay_product_2->set_flavour("tau");
          decay_product_3 = std::make_shared<neutrinoClass>(neutrinoClass::antineutrino());
          decay_product_3->set_flavour(decay_product_1->get_name()); // the neutrino from decay has the same flavour of the lepton
        }
        else
        {
          throw std::invalid_argument("Invalid decay status.");
        }
      }
    }

    // print tau data
    void print() const override {lepton::print();}

};

// Implementation of functions from a class should be done outside the class, preferably in another file


// Random value generating function
double random_value() {return static_cast<double>(std::rand()) / RAND_MAX;}

// Main program
int main()
{
  // Create the following particles:
  // Add two electrons
  electronClass electron1("electron", 0.511, -1, random_value(), false);
  electronClass electron2("electron", 0.511, -1, random_value(), false);

  // Add four muons
  muonClass muon1("muon", 105.6, -1, random_value(), false, false);
  muonClass muon2("muon", 105.6, -1, random_value(), false, false);
  muonClass muon3("muon", 105.6, -1, random_value(), false, true);
  muonClass muon4("muon", 105.6, -1, random_value(), false, true);

  // Add one antielectron
  electronClass electron3("positron", 0.511, 1, random_value(), true);

  // Add one antimuon
  muonClass muon5("antimuon", 105.6, 1, random_value(), true, true);

  // Add one muon neutrino
  neutrinoClass neutrino1("neutrino", 940.6, 0, random_value(), false, "muon", false);

  // Add one electron neutrino
  neutrinoClass neutrino2("neutrino", 940.6, 0, random_value(), false, "electron", true);

  // Add one tau decaying into a muon, a muon antineutrino, and a tau neutrino
  tauClass tau1("tau", 1777, -1, random_value(), false, true, false);
  tau1.leptonic_decay(true, [](){ return muonClass::muon(); });

  // Add one antitau decaying into an antielectron, an electron neutrino, and a tau antineutrino
  tauClass tau2("antitau", 1777, -1, random_value(), true, true, false);
  tau2.leptonic_decay(true, [](){ return muonClass::muon(); });


  // Create a vector of pointers to lepton objects
  std::vector<lepton*> particles;

  // Push pointers to the created particles into the vector
  particles.push_back(&electron1);
  particles.push_back(&electron2);
  particles.push_back(&electron3);
  particles.push_back(&muon1);
  particles.push_back(&muon2);
  particles.push_back(&muon3);
  particles.push_back(&muon4);
  particles.push_back(&muon5);


  // Print information of all particles in the vector
  for(const auto& particle : particles)
  {
    particle->print();
  }

  // Sum the four-vectors of the two electrons and print the result
  std::cout<<"Sum of four-vectors of electrons:"<<std::endl;
  FourMomentum electron_sum = sum(*particles[0], *particles[1]);
  std::cout<<"Energy: "<<electron_sum.get_energy()<<std::endl;
  std::cout<<"Momentum X: "<<electron_sum.get_momentum_x()<<std::endl;
  std::cout<<"Momentum Y: "<<electron_sum.get_momentum_y()<<std::endl;
  std::cout<<"Momentum Z: "<<electron_sum.get_momentum_z()<<std::endl;

  // Take the dot products of the antielectron and antimuon four-vector and print the result
  std::cout<<"Dot product of antielectron and antimuon four-vector: ";
  double dot_product_result = dot_product(*particles[2], *particles[3]);
  std::cout<<dot_product_result<<std::endl;

  // Create a shared pointer for a new electron and move its data to another electron using std::move
  std::shared_ptr<electronClass> newElectron = std::make_shared<electronClass>(electronClass::electron());
  std::shared_ptr<electronClass> anotherElectron = std::move(newElectron);

  // Create a shared pointer for a tau lepton that is owned by multiple variables
  std::shared_ptr<tauClass> sharedTau = std::make_shared<tauClass>(tauClass::tau());
  std::shared_ptr<tauClass> sharedTauCopy = sharedTau;

  return 0;
}