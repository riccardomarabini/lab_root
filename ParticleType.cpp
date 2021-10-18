#include "ParticleType.h"

#include <iostream>

namespace ParticlePhysics {

ParticleType::ParticleType(std::string const& name, double mass, double charge)
    : name_{name}, mass_{mass}, charge_{charge} {
  if (mass < 0) {
    throw std::runtime_error("Invalid negative mass");
  }
}

std::string ParticleType::GetName() const noexcept { return name_; }
double ParticleType::GetMass() const noexcept { return mass_; }
double ParticleType::GetCharge() const noexcept { return charge_; }
void ParticleType::Print() const noexcept {
  std::cout << "Name: " << name_ << '\n'
            << "Mass: " << mass_ << '\n'
            << "Charge: " << charge_ << '\n';
}

}  // namespace ParticlePhysics
