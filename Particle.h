#ifndef PARTICLE_H
#define PARTICLE_H

#include <array>
#include <string>
#include <vector>

#include "ParticleType.h"
#include "ResonanceType.h"

namespace ParticlePhysics {

class Particle {
 public:
  // constructors
  Particle(std::string const& name, double Px, double Py, double Pz);
  Particle(std::string const& name);
  Particle();  // quale indice dobiammo mettere di default

  // getters
  int GetParticleIndex() const noexcept;
  double GetPx() const;
  double GetPy() const;
  double GetPz() const;
  std::vector<double> GetP() const;
  double GetMass() const;
  double GetEtot() const;

  // setters
  void SetParticleType(int index);
  void SetParticleType(std::string const& name);
  void SetP(double Px, double Py, double Pz);

  // print
  void PrintParticle();

  // manipolazione
  double InvMass(Particle const& p) const;

  // metodi static di manipolazione
  static void AddParticleType(std::string const& name, double mass,
                              double charge, double width);
  static void PrintParticleType();

 private:
  static const int MaxNumParticleType_ = 10;
  static std::array<ParticleType*, MaxNumParticleType_> ParticleType_;
  static int NParticleType_;

  int index_;
  double Px_;
  double Py_;
  double Pz_;

  static int FindParticle(std::string const& name);
};

}  // namespace ParticlePhysics

#endif