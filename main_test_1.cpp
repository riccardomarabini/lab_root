#include <array>
#include <memory>

#include "ParticleType.h"
#include "ResonanceType.h"

using namespace ParticlePhysics;

int main() {
  ParticleType ptype_1("Electron", 0.501, 1.6e-19);
  ptype_1.Print();

  ResonanceType rtype_1("R_particle", 1., 1., 1.);
  rtype_1.Print();

  /*std::array<std::unique_ptr<ParticleType>, 2> arr;
arr[0] = std::make_unique<ParticleType>("Electron",0.501,1.6e-19);
arr[1] = std::make_unique<ResonanceType>("R_particle", 1. , 1. , 1. );*/

  ParticleType* arr[2];
  arr[0] = new ParticleType("Electron", 0.501, 1.6e-19);
  arr[1] = new ResonanceType("R_particle", 1., 1., 1.);
  for (auto const& i : arr) {
    i->Print();
  }
  
  /*for (auto const& i : arr) {
    delete i;
  }*/
}
