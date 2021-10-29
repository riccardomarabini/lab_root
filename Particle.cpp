#include "Particle.h"

#include <algorithm>
#include <array>
#include <cmath>   // for M_PI
#include <cstdlib> //for RAND_MAX
#include <iostream>
#include <vector>

#include "ParticleType.h"
#include "ResonanceType.h"

namespace ParticlePhysics
{

  // constructors
  Particle::Particle(std::string const &name, double Px, double Py, double Pz)
      : Px_{Px}, Py_{Py}, Pz_{Pz}
  {
    int index = Particle::FindParticle(name);
    if (index != -1)
    {
      // throw std::runtime_error("No match found with particle name ");
      index_ = index;
    }
    else
    {
      std::cerr << "Creation failed" << '\n';
    }
  }
  Particle::Particle(std::string const &name)
      : Particle::Particle(name, 0., 0., 0.){};
  Particle::Particle() : index_{-1}, Px_{0.}, Py_{0.}, Pz_{0.} {};
  // copy constructor
  Particle::Particle(Particle const &other)
  {
    index_ = other.GetParticleIndex();
    Px_ = other.GetPx();
    Py_ = other.GetPy();
    Pz_ = other.GetPz();
  };

  Particle &Particle::operator=(Particle const &other)
  {
    if (this != &other)
    {
      index_ = other.GetParticleIndex();
      Px_ = other.GetPx();
      Py_ = other.GetPy();
      Pz_ = other.GetPz();
    }
    return *this;
  }

  // getters
  int Particle::GetParticleIndex() const noexcept { return index_; }
  double Particle::GetPx() const { return Px_; };
  double Particle::GetPy() const { return Py_; };
  double Particle::GetPz() const { return Py_; };
  std::vector<double> Particle::GetP() const { return {Px_, Py_, Pz_}; };
  double Particle::GetMass() const { return ParticleType_[index_]->GetMass(); }
  double Particle::GetCharge() const
  {
    return ParticleType_[index_]->GetCharge();
  }
  double Particle::GetEtot() const
  {
    double m =
        GetMass(); // no argument in getmass, is it illicit? (works fine for me)
    // DA CONTROLLARE PERCHE' NON PRENDE TRE PARAMETRI ANCHE SE SI IMPOSTA CPP17
    double p = hypot(Px_, Py_);
    p = hypot(p, Pz_);
    return hypot(m, p);
  }

  // setters
  void Particle::SetParticleType(int index)
  {
    if (index > -1 && index <= NParticleType_)
    {
      index_ = index;
    }
    else
    {
      std::cout << "Invalid index value " << '\n';
    }
  }
  void Particle::SetParticleType(std::string const &name)
  {
    int index = Particle::FindParticle(name);
    if (index != -1)
    {
      index_ = 0;
    }
  }
  void Particle::SetP(double Px, double Py, double Pz)
  {
    Px_ = Px;
    Py_ = Py;
    Pz_ = Pz;
  }

  // print
  void Particle::PrintParticle()
  {
    std::cout << "Index: " << index_ << '\n';
    if (index_ != -1)
    {
      std::cout << "Name: " << ParticleType_[index_]->GetName() << '\n';
    }
    std::cout << "(Px,Py,Pz) = (" << Px_ << " , " << Py_ << " , " << Pz_ << " )"
              << '\n';
  }

  // manipolazione
  double Particle::InvMass(Particle const &p) const
  {
    /*double Px = Px_ + p.GetPx();
    double Py = Py_ + p.GetPy();
    double Pz = Pz_ + p.GetPz();
    double norm2 = pow(hypot(hypot(Px, Py), Pz), 2);
    double E2 = pow(GetEtot() + p.GetEtot(), 2);
    double M2 = E2 - norm2;
    return pow(M2, .5);*/
    return sqrt(pow(GetEtot() + p.GetEtot(), 2) - (pow(Px_ + p.GetPx(), 2) + pow(Py_ + p.GetPy(), 2) + pow(Pz_ + p.GetPz(), 2)));
  }
  int Particle::Decay2body(Particle &dau1, Particle &dau2) const
  {
    if (GetMass() == 0.0)
    {
      printf("Decayment cannot be preformed if mass is zero\n");
      return 1;
    }

    double massMot = GetMass();
    double massDau1 = dau1.GetMass();
    double massDau2 = dau2.GetMass();

    if (index_ > -1)
    { // add width effect

      // gaussian random numbers

      float x1, x2, w, y1, y2;

      double invnum = 1. / RAND_MAX;
      do
      {
        x1 = 2.0 * rand() * invnum - 1.0;
        x2 = 2.0 * rand() * invnum - 1.0;
        w = x1 * x1 + x2 * x2;
      } while (w >= 1.0);

      w = sqrt((-2.0 * log(w)) / w);
      y1 = x1 * w;
      y2 = x2 * w;

      massMot += ParticleType_[index_]->GetWidth() * y1;
    }

    if (massMot < massDau1 + massDau2)
    {
      printf(
          "Decayment cannot be preformed because mass is too low in this "
          "channel\n");
      return 2;
    }

    double pout =
        sqrt(
            (massMot * massMot - (massDau1 + massDau2) * (massDau1 + massDau2)) *
            (massMot * massMot - (massDau1 - massDau2) * (massDau1 - massDau2))) /
        massMot * 0.5;

    double norm = 2 * M_PI / RAND_MAX;

    double phi = rand() * norm;
    double theta = rand() * norm * 0.5 - M_PI / 2.;
    dau1.SetP(pout * sin(theta) * cos(phi), pout * sin(theta) * sin(phi),
              pout * cos(theta));
    dau2.SetP(-pout * sin(theta) * cos(phi), -pout * sin(theta) * sin(phi),
              -pout * cos(theta));

    double energy = sqrt(Px_ * Px_ + Py_ * Py_ + Pz_ * Pz_ + massMot * massMot);

    double bx = Px_ / energy;
    double by = Py_ / energy;
    double bz = Pz_ / energy;

    dau1.Boost(bx, by, bz);
    dau2.Boost(bx, by, bz);

    return 0;
  }
  void Particle::Boost(double bx, double by, double bz)
  {
    double energy = GetEtot();

    // Boost this Lorentz vector
    double b2 = bx * bx + by * by + bz * bz;
    double gamma = 1.0 / sqrt(1.0 - b2);
    double bp = bx * Px_ + by * Py_ + bz * Pz_;
    double gamma2 = b2 > 0 ? (gamma - 1.0) / b2 : 0.0;

    Px_ += gamma2 * bp * bx + gamma * bx * energy;
    Py_ += gamma2 * bp * by + gamma * by * energy;
    Pz_ += gamma2 * bp * bz + gamma * bz * energy;
  }

  // static methods and attributes

  int Particle::NParticleType_ = 0;
  std::array<ParticleType *, Particle::MaxNumParticleType_>
      Particle::ParticleType_ = {0};

  // check particle is in the array and
  // return the index according to the name
  // DA SOSTITUIRE CON FIND_IF!!!!!!!!!!!!!!!!!
  int Particle::FindParticle(std::string const &name)
  {
    int index = -1;
    for (int i = 0; i < NParticleType_; ++i)
    {
      if (name == (ParticleType_[i]->GetName()))
      {
        index = i;
        break;
      }
    }
    if (index == -1)
    {
      std::cout << "No match particle name" << '\n';
    }
    return index;
    /*
      auto it = std::find_if(ParticleType_.begin(), ParticleType_.end(),
                             [&name](auto const& particleType) {
                               if (particleType != nullptr) {
                                 return name == particleType->GetName();
                               } else {
                                 return particleType != nullptr;
                               }
                             });
      if (it != ParticleType_.end()) {
        return std::distance(ParticleType_.begin(), it);
      } else {
        std::cout << "No match particle name" << '\n';
        return -1;
      }*/
  }

  //  controllare che non sia pieno con if else e che non sia già stata inserita e
  //  aumetare nparticletype
  void Particle::AddParticleType(std::string const &name, double mass,
                                 double charge, double width)
  {
    int index = FindParticle(name);
    if (index == -1 && NParticleType_ < 10)
    {
      if (width == 0)
      {
        ParticleType_[NParticleType_] = new ParticleType(name, mass, charge);
      }
      else
      {
        ParticleType_[NParticleType_] =
            new ResonanceType(name, mass, charge, width);
      }
      NParticleType_ += 1;
      std::cout << "Particle added \n"
                << "-----------------------\n";
    }
    else
    {
      std::cout << "Insertion failed: max capacity reached \n"
                << "-----------------------\n";
    }
  }

  void Particle::PrintParticleType()
  {
    // alternativo più elegante
    /*for (auto const& particleType : ParticleType_) {
      if (particleType != nullptr) {
        particleType->Print();
      }
    }*/
    std::cout << NParticleType_ << " particles have been added" << '\n';
    for (int i = 0; i < NParticleType_; ++i)
    {
      ParticleType_[i]->Print();
      std::cout << "+++++++++++++++++++++++++++\n";
    }
  }

} // namespace ParticlePhysics
