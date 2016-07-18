#include <Riostream.h>
#include <fstream>
#include "TMath.h"
#include <stdlib.h>
#include <fstream>
#include <math.h>
#include <TROOT.h>
#include <TApplication.h>
#include <TPaveLabel.h>
#include <TSystem.h>
#include <TFrame.h>
#include <TStyle.h>
#include <TString.h>
#include "TGaxis.h"
#include "TFile.h"
#include "TH1F.h"
#include "TH1D.h"
#include "TH2F.h"
#include "TF1.h"
#include "TPad.h"
#include "TVirtualFitter.h"
#include "TObject.h"
#include "TCanvas.h"
#include "TMultiGraph.h"
#include "TLegend.h"
#include "TDatabasePDG.h"
#include "TMinuit.h"
#include "TBenchmark.h"
#include "TRandom.h"
#include "TLatex.h"
#include "TASImage.h"
#include "TPostScript.h"
#include "TGraphErrors.h"
#include "TFitResultPtr.h"
#include "TFitResult.h"
#include "TMatrixDSym.h"
#include "TArrow.h"
#include "TGraphAsymmErrors.h"
#include "TGaxis.h"
#include "TMarker.h"
#include "./CommonHeaders/PlottingGammaConversionHistos.h"
#include "./CommonHeaders/PlottingGammaConversionAdditional.h"
#include "./CommonHeaders/FittingGammaConversion.h"
#include "./CommonHeaders/ExtractSignalBinning.h"
// #include "./CommonHeaders/ConversionFunctionsBasicsAndLabeling.h"
#include "./CommonHeaders/ConversionFunctions.h"
#include "./CommonHeaders/CombinationFunctions.h"

extern TRandom*    gRandom;
extern TBenchmark*    gBenchmark;
extern TSystem*    gSystem;
extern TMinuit*      gMinuit;

void ComparePtHardBinsEfficiency(TString MCFolder = "13g_CutStudies_15a3a",
                                 TString MCFolderMB = "13g_CutStudies_15g2",
                                TString BinPrefix = "bin",
                                TString CutString = "00000113_1111121060032220000_0163103100000050",
                                TString EnergyString = "2.76TeV",
                                const Int_t mode = 4,
                                const Int_t minbin=1,
                                const Int_t maxbin=4){

  
  gROOT->Reset();
  gROOT->SetStyle("Plain");
  
  StyleSettingsThesis();
  SetPlotStyle();
  
  Size_t textSizeSpectra = 0.04;

  Color_t colorBin[12]        = {kBlack, kRed+2, kBlue+2, kGreen+2, kCyan+2, kViolet, kMagenta+2, kGray+1, kRed-2, kBlue-2, kCyan-2, kRed+5};
  Color_t colorBinShade[12]    = {kGray+1, kRed-6, kBlue-6, kGreen-8, kCyan-6, kViolet-8, kMagenta-8, kGray, kRed-8, kBlue-8, kCyan-8, kRed-1};
  Marker_t markerBin[12]    = {20, 21, 33, 34, 29, 24, 25, 27, 28, 30, 24, 25};

  const Int_t nbins = maxbin-minbin+1;
  
  // files, histograms, ...
  TFile* fMCCorr[nbins];
  TH1D* MesonEffiMC[nbins];
  TH1D* MesonEffiRatio[nbins];
  
  // MB stuff
  TFile* fMCCorrMB = new TFile(Form("./%s/%s/%s/Pi0_MC_GammaConvV1Correction_%s.root",MCFolderMB.Data(),CutString.Data(),EnergyString.Data(),CutString.Data()));
  TH1D* MesonEffiMCMB = (TH1D*) fMCCorrMB->Get("TrueMesonEffiPt")->Clone("MesonEffiMCMB");

  // canvas for drawing
  TCanvas* canvasEffiComp = new TCanvas("canvasEffiComp","",900,900);
  DrawGammaCanvasSettings(canvasEffiComp,0.15,0.015,0.015,0.08);
  
  canvasEffiComp->cd();

  TPad* TopPad1 = new TPad("TopPad1","TopPad1",0.0,0.3,1.,1.);
  TopPad1->Draw();
  TopPad1->cd();
  
  TH2F * histo2DEffiComp;
  histo2DEffiComp = new TH2F("histo2DEffiComp","histo2DEffiComp",1000,0, 22,1000,0.,0.6);
  SetStyleHistoTH2ForGraphs(histo2DEffiComp, "#it{p}_{T} (GeV/#it{c})","#epsilon",
                            0.85*textSizeSpectra,textSizeSpectra, 0.85*textSizeSpectra,textSizeSpectra, 0.85,1.5);
  histo2DEffiComp->SetTitleOffset(0.95,"X");
  histo2DEffiComp->DrawCopy();

  TLegend* legendEffiComp = GetAndSetLegend2(0.75, 0.55, 0.98, 0.96,16);
  legendEffiComp->SetHeader("#pi^{0} eff. per bin");
  
  MesonEffiMCMB->SetLineColor(colorBin[0]);
  MesonEffiMCMB->SetMarkerColor(colorBin[0]);
  MesonEffiMCMB->SetMarkerStyle(markerBin[0]);

  MesonEffiMCMB->Draw("p,same");
  legendEffiComp->AddEntry(MesonEffiMCMB,"MB MC");
  
  // loop through bins
  for(int ibin=minbin;ibin<=maxbin;ibin++){
    
    fMCCorr[ibin] = new TFile(Form("./%s/bin%d/%s/%s/Pi0_MC_GammaConvV1Correction_%s.root",MCFolder.Data(),ibin,CutString.Data(),EnergyString.Data(),CutString.Data()));
    
    MesonEffiMC[ibin] = (TH1D*) fMCCorr[ibin]->Get("TrueMesonEffiPt")->Clone(Form("MesonEffiMC%d",ibin));
    
    MesonEffiMC[ibin]->SetLineColor(colorBin[ibin]);
    MesonEffiMC[ibin]->SetMarkerColor(colorBin[ibin]);
    MesonEffiMC[ibin]->SetMarkerStyle(markerBin[ibin]);

    MesonEffiMC[ibin]->Draw("p,same");
    legendEffiComp->AddEntry(MesonEffiMC[ibin],Form("#it{p}_{T}^{hard} bin %d",ibin));
  }
  legendEffiComp->Draw();
  
  canvasEffiComp->cd();
  TPad* BottomPad1 = new TPad("BottomPad1","BottomPad1",0.0,0.0,1.,0.3);
  BottomPad1->SetTopMargin(0.08);
  BottomPad1->SetBottomMargin(0.02);
  BottomPad1->Draw();
  BottomPad1->cd();

  TH2F * histo2DEffiRat;
  histo2DEffiRat = new TH2F("histo2DEffiRat","histo2DEffiRat",1000,0, 22,1000,0.51,1.49);
  SetStyleHistoTH2ForGraphs(histo2DEffiRat, "","ratio MB/JJ",
                            0.85*textSizeSpectra,textSizeSpectra, 0.85*textSizeSpectra,textSizeSpectra, 0.85,1.5);
  histo2DEffiRat->SetLabelSize(0.08,"X");
  histo2DEffiRat->SetLabelOffset(0.01,"X");
  histo2DEffiRat->SetLabelSize(0.08,"Y");
  histo2DEffiRat->SetTitleSize(0.08,"Y");
  histo2DEffiRat->SetTitleOffset(0.7,"Y");
  
  histo2DEffiRat->DrawCopy("X+");
  
  for(int ibin=minbin;ibin<=maxbin;ibin++){
    MesonEffiRatio[ibin] = (TH1D*) MesonEffiMCMB->Clone(Form("MesonEffiRatio%d",ibin));
    MesonEffiRatio[ibin]->Divide(MesonEffiMC[ibin]);
    
    MesonEffiRatio[ibin]->SetLineColor(colorBin[ibin]);
    MesonEffiRatio[ibin]->SetMarkerColor(colorBin[ibin]);
    MesonEffiRatio[ibin]->SetMarkerStyle(markerBin[ibin]);
    
    MesonEffiRatio[ibin]->Draw("p,same");
  }
  
  canvasEffiComp->SaveAs("./plots/pi0_efficiency_pt_hard_bin_comparison.eps");
}
