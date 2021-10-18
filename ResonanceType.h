#ifndef RESONANCETYPE_H
#define RESONANCETYPE_H

#include "ParticleType.h"
namespace ParticlePhysics {
class ResonanceType : public ParticleType {
 public:
  explicit ResonanceType(std::string const& name, double mass, double charge,
                         double width);
  double GetWidth() const noexcept;
  void Print() const noexcept;

 private:
  const double width_;
};
}  // namespace ParticlePhysics

#endif