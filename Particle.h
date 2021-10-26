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
  Particle();
  // FOLLOWING THE RULE OF FIVE
  Particle(Particle const& other);
  // ASSIGNMENT
  Particle& operator=(Particle const& other);
  Particle(Particle&& other) = delete;
  Particle& operator=(Particle&& other) = default;
  ~Particle() = default;

  // getters
  int GetParticleIndex() const noexcept;
  double GetPx() const;
  double GetPy() const;
  double GetPz() const;
  std::vector<double> GetP() const;
  double GetMass() const;
  double GetCharge() const;
  double GetEtot() const;

  // setters
  void SetParticleType(int index);
  void SetParticleType(std::string const& name);
  void SetP(double Px, double Py, double Pz);

  // print
  void PrintParticle();

  // manipolazione
  double InvMass(Particle const& p) const;
  int Decay2body(Particle& dau1, Particle& dau2) const;

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
  void Boost(double bx, double by, double bz);
};

}  // namespace ParticlePhysics

#endif