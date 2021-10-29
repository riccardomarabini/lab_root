#include <array>
#include <cmath>
#include <string>
#include <iostream>

#include "Particle.h"
#include "ParticleType.h"
#include "ResonanceType.h"

#include "TMath.h"
#include "TRandom.h"
#include "TH1F.h"
#include "TFile.h"
#include "TCanvas.h"

R__LOAD_LIBRARY(ParticleType_cpp.so)
R__LOAD_LIBRARY(ResonanceType_cpp.so)
R__LOAD_LIBRARY(Particle_cpp.so)

using namespace ParticlePhysics;

void GenerateMain()
{
  // Fill the particles chart
  /*constexpr int MaxNumParticleType = 10;
  constexpr int NumParTypeAvailable = 7;

  std::array<std::string, 7> name = {
      "pion+", "pion-", "kaon+", "kaon-", "proton+", "proton-", "K*"};
  std::array<double, 7> mass = {
      0.13957, 0.13957, 0.49367, 0.49367, 0.93827, 0.93827, 0.89166};

  std::array<int, 7> charge = {1, -1, 1, -1, 1, -1, 0};
  std::array<double, 7> width = {0, 0, 0, 0, 0, 0, 0.050};

  for (int i = 0; i < 7; ++i)
  {
    Particle::AddParticleType(name[i], mass[i], charge[i], width[i]);
  }*/

  Particle::AddParticleType("pion+", 0.13957, 1, 0);
  Particle::AddParticleType("pion-", 0.13957, -1, 0);
  Particle::AddParticleType("kaon+", 0.49367, 1, 0);
  Particle::AddParticleType("kaon-", 0.49367, -1, 0);
  Particle::AddParticleType("proton+", 0.93827, 1, 0);
  Particle::AddParticleType("proton-", 0.93827, -1, 0);
  Particle::AddParticleType("K*", 0.89166, 0, 0.050);

  Particle::PrintParticleType(); // check insertion has been executed correctly

  // Histo definition
  TH1F *hParType =
      new TH1F("hParType", "Abundance of particles", 7, -0.5, 6.5); // filled
  TH1F *hPhi = new TH1F("hPhi", "Azimuth distribution", 1000, 0,
                        2 * TMath::Pi()); // filled
  TH1F *hTheta =
      new TH1F("hTheta", "Polar distribution", 1000, 0, TMath::Pi()); // filled
  TH1F *hMomentum =
      new TH1F("hMomentum", "Momentum distribution", 1000, 0, 10); // filled
  TH1F *hMomentumOrtho =
      new TH1F("hMomentumOrtho", "Orthogonal Momentum distribution", 1000, 0,
               10); // filled
  TH1F *hEtot =
      new TH1F("hEtot", "Energy distribution", 1000, 0, 10); // filled ll.126

  TH1F *hInvMass = new TH1F("hInvMass", "Invariant Mass distribution", 1000, 0,
                            5); // range 0-2
  TH1F *hInvMassOpposite = new TH1F(
      "hInvMass+-", "Invariant Mass opposite charges distribution", 1000, 0, 5);
  TH1F *hInvMassSame = new TH1F(
      "hInvMass++_--", "Invariant Mass same charges distribution", 1000, 0, 5);
  TH1F *hInvMPionKOpposite =
      new TH1F("hInvM_pion_K_opposite",
               "Invariant Mass pion+_K- / pion-_k+ distribution", 1000, 0, 5);
  TH1F *hInvMPionKSame =
      new TH1F("hInvM_pion_K_same",
               "Invariant Mass pion+_K+ / pion-_k- distribution", 1000, 0, 5);
  TH1F *hInvMPionKDecay =
      new TH1F("hInvM_pion_K_decay", "Invariant Mass pion/K decay distribution",
               500, 0, 5);

  // setting Sumw2() for invmass histos
  hInvMass->Sumw2();
  hInvMassOpposite->Sumw2();
  hInvMassSame->Sumw2();
  hInvMPionKOpposite->Sumw2();
  hInvMPionKSame->Sumw2();
  hInvMPionKDecay->Sumw2();

  std::cout << "OK, it is fine till now\n";

  constexpr int N = 120;

  std::array<Particle, N> particle = {};
  gRandom->SetSeed();

  for (int i = 0; i < 10000; ++i)
  {

    std::vector<int> UnstableParIndex;

    for (int j = 0; j < 100; ++j)
    {
      double phi = gRandom->TRandom::Uniform(0, 2 * TMath::Pi());
      hPhi->Fill(phi); // hPhi
      double theta = gRandom->TRandom::Uniform(0, TMath::Pi());
      hTheta->Fill(theta); // hTheta
      double momentum = gRandom->TRandom::Exp(1);
      hMomentum->Fill(momentum); // hMomentum

      double Px = sin(theta) * cos(phi) * momentum;
      double Py = sin(theta) * sin(phi) * momentum;
      double Pz = cos(theta) * momentum;
      particle[j].SetP(Px, Py, Pz);
      const double momentumOrtho = hypot(Px, Py);
      hMomentumOrtho->Fill(momentumOrtho); // hMomentumOrtho

      // setting the type of each particle
      double prob = gRandom->TRandom::Rndm();

      if (prob < 0.4)
      {
        particle[j].SetParticleType(0);
        hParType->Fill(0);
      }
      else if (prob < 0.8)
      {
        particle[j].SetParticleType(1);
        hParType->Fill(1);
      }
      else if (prob < 0.85)
      {
        particle[j].SetParticleType(2);
        hParType->Fill(2);
      }
      else if (prob < 0.9)
      {
        particle[j].SetParticleType(3);
        hParType->Fill(3);
      }
      else if (prob < 0.945)
      {
        particle[j].SetParticleType(4);
        hParType->Fill(4);
      }
      else if (prob < 0.99)
      {
        particle[j].SetParticleType(5);
        hParType->Fill(5);
      }
      else
      {
        particle[j].SetParticleType(6);
        hParType->Fill(6);
        UnstableParIndex.push_back(j);
      }

      // hEtot
      hEtot->Fill(particle[j].GetEtot());
    }

    // unstable particles are bound to decay
    const int size = static_cast<int>(UnstableParIndex.size());
    for (int s = 0; s < size; ++s)
    {
      // set randomly what are the result of the decay and fill the histo of
      // types
      if (gRandom->TRandom::Rndm() < 0.5)
      {
        particle[100 + 2 * s].SetParticleType(0);
        // hParType->Fill(0);
        particle[100 + 2 * s + 1].SetParticleType(3);
        // hParType->Fill(3);
      }
      else
      {
        particle[100 + 2 * s].SetParticleType(1);
        // hParType->Fill(1);
        particle[100 + 2 * s + 1].SetParticleType(2);
        // hParType->Fill(2);
      }

      particle[UnstableParIndex[s]].Decay2body(particle[100 + 2 * s], particle[100 + 2 * s + 1]);

      // per questo assegnamento è stato definito anche l'opratore = per
      // Particle
      // particle[100 + 2 * s] = decay1;
      // particle[100 + 2 * s + 1] = decay2;

      hInvMPionKDecay->Fill((particle[100 + 2 * s + 1]).InvMass(particle[100 + 2 * s]));
    }

    // fill the invMass histo_s
    // among all particles of each generation, decay products included

    for (int p1 = 0; p1 < (100 + 2 * size); ++p1)
    {
      for (int p2 = p1 + 1; p2 < (100 + 2 * size); ++p2)
      {
        // it is sensible to create local instances in order
        // to be able to read particles specs without
        // fecthing info from vector continuously
        Particle particle1(particle[p1]);
        Particle particle2(particle[p2]);
        const int index1 = particle1.GetParticleIndex();
        const int index2 = particle2.GetParticleIndex();

        if (index1 != 6 && index2 != 6)
        {
          hInvMass->Fill(particle1.InvMass(particle2));
        }
        // opposite charge
        if ((particle1.GetCharge() * particle2.GetCharge()) < 0)
        {
          hInvMassOpposite->Fill(particle1.InvMass(particle2));
        }
        // same charge
        if ((particle1.GetCharge() * particle2.GetCharge()) > 0)
        {
          hInvMassSame->Fill(particle1.InvMass(particle2));
        }
        // pion+ ang k- or pion- and k+
        if ((index1 == 0 && index2 == 3))
        {
          hInvMPionKOpposite->Fill(particle1.InvMass(particle2));
        }
        if ((index1 == 1 && index2 == 2))
        {
          hInvMPionKOpposite->Fill(particle1.InvMass(particle2));
        }
        // pion+ and k+ or pion- and k-
        if ((index1 == 0 && index2 == 2))
        {
          hInvMPionKSame->Fill(particle1.InvMass(particle2));
        }
        if ((index1 == 1 && index2 == 3))
        {
          hInvMPionKSame->Fill(particle1.InvMass(particle2));
        }
      }
    }

    UnstableParIndex.clear();
  }

  // Drawing all histos as a double-check
  TCanvas *c1 = new TCanvas("c1", "control canvass", 10, 20, 800, 800);

  c1->Divide(4, 3);
  c1->cd(1);
  hParType->Draw();
  c1->cd(2);
  hPhi->Draw();
  c1->cd(3);
  hTheta->Draw();
  c1->cd(4);
  hMomentum->Draw();
  c1->cd(5);
  hMomentumOrtho->Draw();
  c1->cd(6);
  hEtot->Draw();
  c1->cd(7);
  hInvMass->Draw();
  c1->cd(8);
  hInvMassOpposite->Draw();
  c1->cd(9);
  hInvMassSame->Draw();
  c1->cd(10);
  hInvMPionKOpposite->Draw();
  c1->cd(11);
  hInvMPionKSame->Draw();
  c1->cd(12);
  hInvMPionKDecay->Draw();

  // WRITING ALL EXISTING OBJECTS IN A TFILE
  TFile *particleRootFile = new TFile("particleRootFile.root", "RECREATE");
  particleRootFile->cd();
  hParType->Write();
  hPhi->Write();
  hTheta->Write();
  hMomentum->Write();
  hMomentumOrtho->Write();
  hEtot->Write();
  hInvMass->Write();
  hInvMassOpposite->Write();
  hInvMassSame->Write();
  hInvMPionKOpposite->Write();
  hInvMPionKSame->Write();
  hInvMPionKDecay->Write();

  particleRootFile->Close();
}