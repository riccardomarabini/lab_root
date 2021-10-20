#ifndef PARTICLETYPE_H
#define PARTICLETYPE_H

#include <string>

namespace ParticlePhysics {
class ParticleType {
 public:
  explicit ParticleType(std::string const& name, double mass, double charge);
  std::string GetName() const noexcept;
  double GetMass() const noexcept;
  double GetCharge() const noexcept;
  virtual double GetWidth() const noexcept;
  virtual void Print() const noexcept;

  // virtual ~ParticleType()=0;

 private:
  const std::string name_;
  const double mass_;
  const double charge_;
};
}  // namespace ParticlePhysics

#endif