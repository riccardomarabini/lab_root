#include <iostream>

#include "Particle.h"
#include "ParticleType.h"
#include "ResonanceType.h"

using namespace ParticlePhysics;

int main() {
  Particle::AddParticleType("particle 1", 4, 1, 5);
  Particle::AddParticleType("particle 2", 1, 2, 5);
  Particle::AddParticleType("particle 3", 1, 2, 5);
  Particle::AddParticleType("particle 4", 1, 2, 5);
  Particle::AddParticleType("particle 5", 1, 2, 5);
  Particle::AddParticleType("particle 6", 1, 2, 5);
  Particle::AddParticleType("particle 7", 1, 2, 5);
  Particle::AddParticleType("particle 8", 1, 2, 0);
  Particle::AddParticleType("particle 9", 1, 2, 0);
  Particle::AddParticleType("particle 10", 1, 2, 5);
  // this should not be inserted
  Particle::AddParticleType("particle 11", 1, 2, 5);

  Particle::PrintParticleType();

  Particle wrong_particle("particle", 1, 1, 1);

  Particle particle("particle 1", 1, 1, 1);
  std::cout << particle.GetMass() << '\n' << particle.GetEtot() << '\n';

  // checking copy constructor
  Particle particle_copy(particle);
  particle_copy.PrintParticle();
  // checking assignment
  Particle particle_c;
  // particle_c = particle_copy;
  particle_c.PrintParticle();
}