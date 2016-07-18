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



void CompareSignalBGDiffMC(TString MC1Folder = "13g_CutStudies_15a3a",
                           TString MC2Folder = "13g_CutStudies_15g2",
                           TString CutString = "00000113_1111121060032220000_0163103100000050",
                           TString EnergyString = "2.76TeV",
                           const Int_t mode = 4,
                           const Int_t bin = 16){
  
  
  gROOT->Reset();
  gROOT->SetStyle("Plain");
  
  StyleSettingsThesis();
  SetPlotStyle();

  Size_t textSizeSpectra = 0.04;

  TString fEventCutSelection;
  TString fGammaCutSelection;
  TString fClusterCutSelection;
  TString fElectronCutSelection;
  TString fMesonCutSelection;
  
  ReturnSeparatedCutNumberAdvanced(CutString,fEventCutSelection, fGammaCutSelection, fClusterCutSelection, fElectronCutSelection, fMesonCutSelection, mode);

  InitializeBinning("Pi0", 27, EnergyString, "", 4, fEventCutSelection, fClusterCutSelection);
  
  Double_t startPt = fBinsPt[bin];
  Double_t endPt = fBinsPt[bin+1];

  // open the files that will be compared
  // uncorrected stuff
  TFile* fMCWithout1 = new TFile(Form("./%s/%s/%s/Pi0_MC_GammaConvV1WithoutCorrection_%s.root",MC1Folder.Data(),CutString.Data(),EnergyString.Data(),CutString.Data()));
  TFile* fMCWithout2 = new TFile(Form("./%s/%s/%s/Pi0_MC_GammaConvV1WithoutCorrection_%s.root",MC2Folder.Data(),CutString.Data(),EnergyString.Data(),CutString.Data()));

  TFile* fMCCorr1 = new TFile(Form("./%s/%s/%s/Pi0_MC_GammaConvV1Correction_%s.root",MC1Folder.Data(),CutString.Data(),EnergyString.Data(),CutString.Data()));
  TFile* fMCCorr2 = new TFile(Form("./%s/%s/%s/Pi0_MC_GammaConvV1Correction_%s.root",MC2Folder.Data(),CutString.Data(),EnergyString.Data(),CutString.Data()));

  // get the MC yields
  TH1D* InputYieldMC1 = (TH1D*) fMCWithout1->Get("MC_Pi0InAcc_Pt")->Clone("InputYieldMC1");
  TH1D* InputYieldMC2 = (TH1D*) fMCWithout2->Get("MC_Pi0InAcc_Pt")->Clone("InputYieldMC2");
  
  // get the efficiencies
  TH1D* MesonEffiMC1 = (TH1D*) fMCCorr1->Get("TrueMesonEffiPt")->Clone("MesonEffiMC1");
  TH1D* MesonEffiMC2 = (TH1D*) fMCCorr2->Get("TrueMesonEffiPt")->Clone("MesonEffiMC2");

  // get the GG and BG histograms
  char name[64];
  // FG
  sprintf(name,"Mapping_GG_InvMass_in_Pt_Bin%d",bin);
  if(bin<10)
    sprintf(name,"Mapping_GG_InvMass_in_Pt_Bin0%d",bin);
  TH1D* GG_InvMass_MC1 = (TH1D*) fMCWithout1->Get(name)->Clone("GG_InvMass_MC1");
  TH1D* GG_InvMass_MC2 = (TH1D*) fMCWithout2->Get(name)->Clone("GG_InvMass_MC2");
  // BG
  sprintf(name,"Mapping_BckNorm_InvMass_in_Pt_Bin%d",bin);
  if(bin<10)
    sprintf(name,"Mapping_BckNorm_InvMass_in_Pt_Bin0%d",bin);
  TH1D* Bck_InvMass_MC1 = (TH1D*) fMCWithout1->Get(name)->Clone("Bck_InvMass_MC1");
  TH1D* Bck_InvMass_MC2 = (TH1D*) fMCWithout2->Get(name)->Clone("Bck_InvMass_MC2");
  // subtracted
  sprintf(name,"histoSignalRemainingBGSubtractedBin%d",bin);
  if(bin<10)
    sprintf(name,"histoSignalRemainingBGSubtractedBin0%d",bin);
  TH1D* Subt_InvMass_MC1 = (TH1D*) fMCWithout1->Get(name)->Clone("Subt_InvMass_MC1");
  TH1D* Subt_InvMass_MC2 = (TH1D*) fMCWithout2->Get(name)->Clone("Subt_InvMass_MC2");

  // input yield ratio
  TH1D* InputYieldRatio = (TH1D*) InputYieldMC1->Clone("InputYieldRatio");
  InputYieldRatio->Divide(InputYieldMC2);
  InputYieldRatio->SetMarkerColor(kRed-2);
  InputYieldRatio->SetMarkerStyle(34);
  InputYieldRatio->SetLineColor(kRed-2);

  // efficiency ratio
  TH1D* EffiRatio = (TH1D*)MesonEffiMC2->Clone("EffiRatio");
  EffiRatio->Divide(MesonEffiMC1);
  EffiRatio->SetMarkerColor(kRed-2);
  EffiRatio->SetMarkerStyle(34);
  EffiRatio->SetLineColor(kRed-2);
  
  // normalize the input spectra, bin by bin ...
  
  Double_t scf = InputYieldMC1->GetBinContent(bin)/InputYieldMC2->GetBinContent(bin);
  
  
  // first, normalize the 2nd MC GG to the 1st MC GG distribution
  TH1D* GG_FG_Ratio = (TH1D*)GG_InvMass_MC1->Clone("GG_FG_Ratio");
  GG_FG_Ratio->Divide(GG_InvMass_MC2);
  
  TH1D* Bck_Ratio = (TH1D*)Bck_InvMass_MC1->Clone("Bck_Ratio");
  Bck_Ratio->Divide(Bck_InvMass_MC2);

  // plot ratio of Foreground and of Background, and fit Background
  TCanvas* canvasMinvRatios = new TCanvas("canvasMinvRatios","",900,600);
  DrawGammaCanvasSettings(canvasMinvRatios,0.15,0.015,0.015,0.08);
  
  TH2F * histo2DMinvRatios;
  histo2DMinvRatios = new TH2F("histo2DMinvRatios","histo2DMinvRatios",1000,0., 0.3,1000,0.,25.);
  SetStyleHistoTH2ForGraphs(histo2DMinvRatios, "#it{M}_{#gamma#gamma} (GeV/#it{c}^{2})","#frac{Trigger 1}{Trigger 2}",
                            0.85*textSizeSpectra,textSizeSpectra, 0.85*textSizeSpectra,textSizeSpectra, 0.85,1.5);
  histo2DMinvRatios->DrawCopy();

  GG_FG_Ratio->SetMarkerStyle(21);
  GG_FG_Ratio->SetMarkerColor(kBlack);
  GG_FG_Ratio->Draw("p,same");
  Bck_Ratio->SetMarkerStyle(34);
  Bck_Ratio->SetMarkerColor(kBlue);
  Bck_Ratio->Draw("p,same");
  
  TF1* sclp1 = new TF1("sclp1","pol1",0.03,0.29);
  sclp1->SetLineColor(kBlue);
  Bck_Ratio->Fit(sclp1,"RE");
  
  // now scale histograms
//  GG_InvMass_MC2->Multiply(sclp1);
//  Bck_InvMass_MC2->Multiply(sclp1);
  GG_InvMass_MC2->Scale(scf);
  Bck_InvMass_MC2->Scale(scf);
  Subt_InvMass_MC2->Scale(scf);
  
  // and draw all four histograms in one canvas
  // plot ratio of Foreground and of Background, and fit Background
  TCanvas* canvasMinvComp = new TCanvas("canvasMinvComp","",900,600);
  DrawGammaCanvasSettings(canvasMinvComp,0.15,0.015,0.015,0.08);
  
  Double_t maximum = GG_InvMass_MC1->GetMaximum()*1.1;
  if(GG_InvMass_MC2->GetMaximum()*1.1 > maximum){
    maximum = GG_InvMass_MC2->GetMaximum()*1.1;
  }
  
  TH2F * histo2DMinvComp;
  histo2DMinvComp = new TH2F("histo2DMinvComp","histo2DMinvComp",1000,0.015, 0.3,1000,0.,maximum);
  SetStyleHistoTH2ForGraphs(histo2DMinvComp, "#it{M}_{#gamma#gamma} (GeV/#it{c}^{2})","#frac{d#it{N}_{#gamma#gamma}}{d#it{M}_{#gamma#gamma}}",
                            0.85*textSizeSpectra,textSizeSpectra, 0.85*textSizeSpectra,textSizeSpectra, 0.85,1.5);
  histo2DMinvComp->DrawCopy();

  TLegend* legendMinvComp = GetAndSetLegend2(0.6, 0.65, 0.95, 0.95,13);
//  legendMinvComp->AddEntry(GG_InvMass_MC1,Form("%s, Foreground",MC1Folder.Data()));
//  legendMinvComp->AddEntry(GG_InvMass_MC2,Form("%s, Foreground, scaled",MC2Folder.Data()));
//  legendMinvComp->AddEntry(Bck_InvMass_MC1,Form("%s, scaled Background",MC1Folder.Data()));
//  legendMinvComp->AddEntry(Bck_InvMass_MC2,Form("%s, scaled Background, scaled",MC2Folder.Data()));
  legendMinvComp->SetHeader(Form("%s, Bin %d (%.2f < #it{p}_{T} < %.2f), inp yld frac = %.2f",EnergyString.Data(),bin,startPt,endPt,scf));
  legendMinvComp->AddEntry(GG_InvMass_MC1,"JJ, Foreground");
  legendMinvComp->AddEntry(GG_InvMass_MC2,"MB Foreground, scaled");
  legendMinvComp->AddEntry(Bck_InvMass_MC1,"JJ, scaled Background");
  legendMinvComp->AddEntry(Bck_InvMass_MC2,"MB, scaled Background, scaled");
  legendMinvComp->AddEntry(Subt_InvMass_MC1,"JJ, Signal");
  legendMinvComp->AddEntry(Subt_InvMass_MC2,"MB, Signal, scaled");

  legendMinvComp->Draw();
  
  
  Bck_InvMass_MC1->SetMarkerColor(kBlue);
  Bck_InvMass_MC1->SetMarkerStyle(29);
  Bck_InvMass_MC1->SetMarkerSize(1);
  Bck_InvMass_MC1->Draw("same");

  Bck_InvMass_MC2->SetMarkerColor(kBlue-2);
  Bck_InvMass_MC2->SetLineColor(kBlue-2);
  Bck_InvMass_MC2->SetMarkerStyle(30);
  Bck_InvMass_MC2->SetMarkerSize(1);
  Bck_InvMass_MC2->Draw("same");

  GG_InvMass_MC1->SetMarkerColor(kBlack);
  GG_InvMass_MC1->SetMarkerStyle(21);
  GG_InvMass_MC1->SetMarkerSize(0.75);
  GG_InvMass_MC1->Draw("p,same");

  GG_InvMass_MC2->SetMarkerColor(kGray+2);
  GG_InvMass_MC2->SetLineColor(kGray+2);
  GG_InvMass_MC2->SetMarkerStyle(25);
  GG_InvMass_MC2->SetMarkerSize(0.75);
  GG_InvMass_MC2->Draw("p,same");

  Subt_InvMass_MC1->SetMarkerStyle(34);
  Subt_InvMass_MC1->SetMarkerColor(kRed);
  Subt_InvMass_MC1->SetLineColor(kRed);
  Subt_InvMass_MC1->SetMarkerSize(1);
  Subt_InvMass_MC1->Draw("same");

  Subt_InvMass_MC2->SetMarkerStyle(28);
  Subt_InvMass_MC2->SetMarkerColor(kRed-2);
  Subt_InvMass_MC2->SetLineColor(kRed-2);
  Subt_InvMass_MC2->SetMarkerSize(1);
  Subt_InvMass_MC2->Draw("same");
  
  canvasMinvComp->SaveAs(Form("./plots/pi0_peak_comparison_MCs_MB_JJ_bin%d.eps",bin));
  
  TCanvas* canvasEffiComp = new TCanvas("canvasEffiComp","",900,900);
  DrawGammaCanvasSettings(canvasEffiComp,0.15,0.015,0.015,0.08);
  
  TPad* TopPad1 = new TPad("TopPad1","TopPad1",0.0,0.3,1.,1.);
  TopPad1->Draw();
  TopPad1->cd();

  TH2F * histo2DEffiComp;
  histo2DEffiComp = new TH2F("histo2DEffiComp","histo2DEffiComp",1000,0, 22,1000,0.,0.6);
  SetStyleHistoTH2ForGraphs(histo2DEffiComp, "#it{p}_{T} (GeV/#it{c})","#epsilon",
                            0.85*textSizeSpectra,textSizeSpectra, 0.85*textSizeSpectra,textSizeSpectra, 0.85,1.5);
  histo2DEffiComp->SetTitleOffset(0.95,"X");
  histo2DEffiComp->DrawCopy();
  
  MesonEffiMC1->SetLineColor(kBlack);
  MesonEffiMC1->SetMarkerColor(kBlack);
  MesonEffiMC1->SetMarkerStyle(20);

  MesonEffiMC2->SetLineColor(kGray+2);
  MesonEffiMC2->SetMarkerColor(kGray+2);
  MesonEffiMC2->SetMarkerStyle(24);
  
  TLegend* legendEffiComp = GetAndSetLegend2(0.8, 0.85, 0.95, 0.95,13);
  legendEffiComp->AddEntry(MesonEffiMC1,"JJ MC");
  legendEffiComp->AddEntry(MesonEffiMC2,"MB MC");
//  legendEffiComp->AddEntry(EffiRatio,"Ratio JJ/MB");
  legendEffiComp->Draw();

  MesonEffiMC1->Draw("p,same");
  MesonEffiMC2->Draw("p,same");

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

  EffiRatio->Draw("p,same");
  canvasEffiComp->Update();
  
  canvasEffiComp->SaveAs("./plots/pi0_efficiency_comparison_MCs_MB_JJ.eps");
  
  TCanvas* canvasInputYldComp = new TCanvas("canvasInputYldComp","",900,900);
  DrawGammaCanvasSettings(canvasInputYldComp,0.15,0.015,0.015,0.08);

  canvasInputYldComp->cd();
  
  TH2F * histo2DYldComp;
  histo2DYldComp = new TH2F("histo2DYldComp","histo2DYldComp",1000,0, 22,1000,1,1e8);
  SetStyleHistoTH2ForGraphs(histo2DYldComp, "#it{p}_{T} (GeV/#it{c})","#frac{d#it{N}_{#gamma#gamma}}{d#it{p}_{T,#gamma#gamma}}",
                            0.85*textSizeSpectra,textSizeSpectra, 0.85*textSizeSpectra,textSizeSpectra, 0.85,1.5);

  TPad* TopPad2 = new TPad("TopPad2","TopPad2",0.0,0.3,1.,1.);
  TopPad2->SetLogy();
  TopPad2->Draw();
  TopPad2->cd();

  InputYieldMC1->SetMarkerStyle(20);
  InputYieldMC1->SetMarkerColor(1);
  InputYieldMC1->SetLineColor(1);
  
  InputYieldMC2->SetMarkerStyle(24);
  InputYieldMC2->SetMarkerColor(kGray+2);
  InputYieldMC2->SetLineColor(kGray+2);
  
  
  histo2DYldComp->DrawCopy();
  InputYieldMC1->Draw("psame");
  InputYieldMC2->Draw("psame");
  
  legendEffiComp->Draw("same");
  
  canvasInputYldComp->cd();
  TPad* BottomPad2 = new TPad("BottomPad2","BottomPad2",0.0,0.0,1.,0.3);
  BottomPad2->SetTopMargin(0.08);
  BottomPad2->SetBottomMargin(0.02);
  BottomPad2->Draw();
  BottomPad2->cd();

  TH2F * histo2DYldRat;
  histo2DYldRat = new TH2F("histo2DYldRat","histo2DYldRat",1000,0, 22,1000,0.0001,20.);
  SetStyleHistoTH2ForGraphs(histo2DYldRat, "","ratio JJ/MB",
                            0.85*textSizeSpectra,textSizeSpectra, 0.85*textSizeSpectra,textSizeSpectra, 0.85,1.5);
  histo2DYldRat->SetLabelSize(0.08,"X");
  histo2DYldRat->SetLabelOffset(0.01,"X");
  histo2DYldRat->SetLabelSize(0.08,"Y");
  histo2DYldRat->SetTitleSize(0.08,"Y");
  histo2DYldRat->SetTitleOffset(0.7,"Y");
  histo2DYldRat->DrawCopy("X+");
  
  InputYieldRatio->Draw("p,same");
  
  canvasInputYldComp->Update();
  canvasInputYldComp->SaveAs("./plots/pi0_input_yield_comparison_MCs_MB_JJ.eps");

}


