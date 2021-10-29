#include "TH1F.h"
#include "TFile.h"
#include "TMath.h"
#include <iostream>

void analysis()
{
    // analysing histo of types
    TFile *particleRootFile_ = new TFile("particleRootFile.root");

    TH1F *hParType_ = (TH1F *)particleRootFile_->Get("hParType");

    hParType_->Draw();

    // fitting angular histos

    TH1F *hPhi = (TH1F *)particleRootFile_->Get("hPhi");
}
