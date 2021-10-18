#include "Particle.h"

#include <algorithm>
#include <array>
#include <cmath>
#include <iostream>
#include <vector>

#include "ParticleType.h"
#include "ResonanceType.h"

namespace ParticlePhysics {

// constructors
Particle::Particle(std::string const& name, double Px, double Py, double Pz)
    : Px_{Px}, Py_{Py}, Pz_{Pz} {
  int index = Particle::FindParticle(name);
  if (index != -1) {
    // throw std::runtime_error("No match found with particle name ");
    index_ = index;
  } else {
    std::cerr << "Creation failed" << '\n';
  }
}

Particle::Particle(std::string const& name)
    : Particle::Particle(name, 0., 0., 0.){};

Particle::Particle() : index_{-1}, Px_{0}, Py_{0}, Pz_{0} {};

// getters
int Particle::GetParticleIndex() const noexcept { return index_; }
double Particle::GetPx() const { return Px_; };
double Particle::GetPy() const { return Py_; };
double Particle::GetPz() const { return Py_; };
std::vector<double> Particle::GetP() const { return {Px_, Py_, Pz_}; };
double Particle::GetMass() const { return ParticleType_[index_]->GetMass(); }
double Particle::GetEtot() const {
  double m = GetMass();  // IS IT ILLICIT?
  // DA CONTROLLARE PERCHE' NON PRENDE TRE PARAMETRI ANCHE SE SI IMPOSTA CPP17
  double p = hypot(Px_, Py_);
  p = hypot(p, Pz_);
  return hypot(m, p);
}

// setters
void Particle::SetParticleType(int index) {
  if (index > -1 && index <= NParticleType_) {
    index_ = index;
  } else {
    std::cout << "Invalid index value " << '\n';
  }
}
void Particle::SetParticleType(std::string const& name) {
  int index = Particle::FindParticle(name);
  if (index != -1) {
    index_ = 0;
  }
}
void Particle::SetP(double Px, double Py, double Pz) {
  Px_ = Px;
  Py_ = Py;
  Pz_ = Pz;
}

// print
void Particle::PrintParticle() {
  std::cout << "Index: " << index_ << '\n'
            << "Name: " << ParticleType_[index_]->GetName() << '\n';
  std::cout << "(Px,Py,Pz) = (" << Px_ << " , " << Py_ << " , " << Pz_ << " )"
            << '\n';
}

// manipolazione
double Particle::InvMass(Particle const& p) const {
  double Px = Px_ + GetPx();
  double Py = Py_ + GetPy();
  double Pz = Pz_ + GetPz();
  double norm2 = pow(hypot(hypot(Px, Py), Pz), 2);
  double E2 = pow(GetEtot() - p.GetEtot(), 2);
  double M2 = E2 - norm2;
  return pow(M2, .5);
}

// static methods and attributes

int Particle::NParticleType_ = 0;
std::array<ParticleType*, Particle::MaxNumParticleType_>
    Particle::ParticleType_ = {0};

// check particle is in the array and
// return the index according to the name
// DA SOSTITUIRE CON FIND_IF!!!!!!!!!!!!!!!!!
int Particle::FindParticle(std::string const& name) {
  /*int index = -1;
  for (int i = 0; i < NParticleType_; ++i) {
    if (name == (ParticleType_[i]->GetName())) {
      index = i;
      break;
    }
  }
  if (index == -1) {
    std::cout << "No match particle name" << '\n';
  }
  return index;*/

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
  }
}

//  controllare che non sia pieno con if else e che non sia già stata inserita e
//  aumetare nparticletype
void Particle::AddParticleType(std::string const& name, double mass,
                               double charge, double width) {
  int index = FindParticle(name);
  if (index == -1 && NParticleType_ < 10) {
    if (width == 0) {
      ParticleType_[NParticleType_] = new ParticleType(name, mass, charge);
    } else {
      ParticleType_[NParticleType_] =
          new ResonanceType(name, mass, charge, width);
    }
    NParticleType_ += 1;
    std::cout << "Particle added " << '\n';
  }
}

void Particle::PrintParticleType() {
  // alternativo più elegante
  /*for (auto const& particleType : ParticleType_) {
    if (particleType != nullptr) {
      particleType->Print();
    }
  }*/

  for (int i = 0; i < NParticleType_; ++i) {
    ParticleType_[i]->Print();
  }
}

}  // namespace ParticlePhysics
