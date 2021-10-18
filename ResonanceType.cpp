#include "ResonanceType.h"

#include <iostream>

#include "ParticleType.h"

namespace ParticlePhysics {
ResonanceType::ResonanceType(std::string const& name, double mass,
                             double charge, double width)
    : ParticleType(name, mass, charge), width_{width} {
  if (width < 0) {
    throw std::runtime_error("Invalid negative Width");
  }
}

double ResonanceType::GetWidth() const noexcept { return width_; }
void ResonanceType::Print() const noexcept {
  ParticleType::Print();
  std::cout << "Width: " << width_ << '\n';
}

}  // namespace ParticlePhysics
