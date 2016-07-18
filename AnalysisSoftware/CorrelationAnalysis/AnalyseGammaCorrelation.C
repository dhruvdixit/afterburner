#include <stdlib.h>
#include <iostream>
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
#include "TH3F.h"
#include "TF1.h"
#include "TVirtualFitter.h"
#include "TObject.h"
#include "TCanvas.h"
#include "TMultiGraph.h"
#include "TLegend.h"
#include "TTree.h"
#include "TMinuit.h"
#include "TLatex.h"
#include "TMath.h"
#include "TPostScript.h"
#include "TGraphErrors.h"
#include "TArrow.h"
#include "TGraphAsymmErrors.h"
#include "TGaxis.h"
#include "TMarker.h"
#include "TVectorT.h"
#include "TDatabasePDG.h"
#include "TASImage.h"

#include "PlottingGammaConversionHistos.h"
#include "PlottingGammaConversionAdditional.h"
#include "PlottingCorrelation.h"


void AnalyseGammaCorrelation(TString nameFileData = "GammaConvCorr_Data.root", TString cutSelection = "001023", TString suffix ="eps",TString optData = "Data", TString optEnergy = "7TeV", TString optMCGenerator = ""){
		
	gROOT->Reset();
	gROOT->SetStyle("Plain");
 
	TString collisionSystem;
	if(optEnergy.CompareTo("7TeV") == 0){
			collisionSystem = 			"pp @  #sqrt{#it{s}} = 7 TeV";          
	} else if( optEnergy.CompareTo("2.76TeV") == 0) {
		collisionSystem = 			"pp @ #sqrt{#it{s}} = 2.76 TeV";
	} else if( optEnergy.CompareTo("900GeV") == 0) {
			collisionSystem = 			"pp @ #sqrt{#it{s}} = 0.9 TeV";
	} else if( optEnergy.CompareTo("HI") == 0) {
			collisionSystem =			"PbPb @ #sqrt{#it{s}_{_{NN}}} = 2.76 TeV";
	} else {
			cout << "No correct collision system specification, has been given" << endl;
			return;         
	}

	TString textGenerator;
	if(optMCGenerator.CompareTo("") ==0){
		textGenerator = "";
	} else {
		textGenerator = optMCGenerator;
	}
	TString outputDirectory;
	TString outputDirectory1;
	TString outputDirectory2;
	outputDirectory1 =	 Form("%s",cutSelection.Data());
	outputDirectory2 =	 Form("%s/%s/",cutSelection.Data(),suffix.Data());
	outputDirectory =	 	Form("%s/%s/GammaCorrelation",cutSelection.Data(),suffix.Data());
	gSystem->Exec("mkdir "+outputDirectory1);
	gSystem->Exec("mkdir "+outputDirectory2);
	gSystem->Exec("mkdir "+outputDirectory);
     
	StyleSettingsThesis();
//  	SetPlotStyle();
	SetPlotStyleNConts(99);
	
	//How big should the right margin in 2D plots be? 
	Float_t 	rightMargin = 			0.01;
	Float_t 	leftMargin = 			0.15;
	Float_t 	rightMargin2 = 		0.12;
	Float_t 	leftMargin2 = 			0.12;
	Float_t 	bottomMargin = 		0.07;
	Float_t 	topMargin = 		0.01;
	// Array defintion for printing Logo in right upper corner
	Float_t 	floatLocationRightUp[4]= {0.8,0.605,0.15, 0.02};
	Float_t 	floatLocationRightUpR[4]= {0.8,0.45,0.15, 0.02};
	Float_t 	floatLocationRightUp2[4]= {0.8,0.76,0.15, 0.02};
	Float_t 	floatLocationRightDown[4]=	{0.7,0.23,0.15, 0.02};
	Float_t 	floatLocationRightUp2D[4]=	{0.68,0.775,0.11, 0.02};
	Float_t 	floatLocationRightUp2DXY[4]=	{0.69,0.85,0.115, 0.025};
	Float_t 	floatLocationRightUp2DZR[4]=	{0.69,0.23,0.115, 0.025};
	// Array defintion for printing Logo in left upper corner
	Float_t 	floatLocationLeftUp[4]=		{0.18,0.76, 0.15, 0.02};
	// Array defintion for printing text in right upper corner
	Float_t 	floatLocationRightUpText[4]=	{0.16,0.92,0.15, 0.04};
	Float_t 	floatLocationRightUpText2[4]=	{0.7,0.8,0.15, 0.04};
	
	TFile* fileGammaCorr = new TFile(nameFileData.Data());
	TDirectory*  directoryGammaCorr = 		(TDirectory*)fileGammaCorr->Get(Form("CorrGamma_%s",  cutSelection.Data())); 	
	
	TH1F*	histoAssociatedGamma = 	(TH1F*)directoryGammaCorr->Get("ESD_AssociatedGamma");
	Float_t numberOfTriggerGammas = histoAssociatedGamma->Integral();
	cout << "number of trigger photons: \t " << numberOfTriggerGammas << endl;
	histoAssociatedGamma->Scale(1/numberOfTriggerGammas);
	PlotStandard1D( histoAssociatedGamma, Form("%s/%s_NumberAssociatedGamma.%s",outputDirectory.Data(),optData.Data(),suffix.Data()), "", "number associated #gamma", "N_{#gamma, assoc}/N_{#gamma, trig}", kTRUE, 0, 20, kFALSE, 1.5,1e-7, kTRUE, 0, 1, floatLocationRightUp2DXY);
// 	delete histoAssociatedGamma;
	
	TH1F*	histoAssociatedCh =  (TH1F*)directoryGammaCorr->Get("ESD_AssociatedCh");
	histoAssociatedCh->Scale(1/numberOfTriggerGammas);
	PlotStandard1D( histoAssociatedCh, Form("%s/%s_NumberAssociatedCharged.%s",outputDirectory.Data(),optData.Data(),suffix.Data()), "", "number associated h^{+/-}", "N_{#gamma, ch}/N_{#gamma, trig}", kTRUE, 0, 200, kFALSE, 1.5,1e-9, kTRUE, 0, 1, floatLocationRightUp2DXY);
// 	delete histoAssociatedCh;

	TH2F*	histoCorrGamma_Phi_Pt = (TH2F*)directoryGammaCorr->Get("ESD_CorrGamma_Phi_Pt");
	histoCorrGamma_Phi_Pt->Scale(1./numberOfTriggerGammas);
 	ConvGammaRebinWithBinCorrection2D(histoCorrGamma_Phi_Pt, 1, 1, 3);
	PlotStandard2D( histoCorrGamma_Phi_Pt , Form("%s/%s_GammaCorr_Phi_Pt.%s",outputDirectory.Data(),optData.Data(),suffix.Data()), "", "#phi (rad)", "p_{t} (GeV/c)", "#frac{dN_{#gamma,trig}}{N_{#gamma, trig} d#phi dp_{t}}",  kTRUE, -TMath::Pi(), TMath::Pi(),kTRUE, 0.1, 50., kTRUE,  9e-6, histoCorrGamma_Phi_Pt->GetMaximum(), 0,1, 1, floatLocationRightUp2DXY,1000,880,rightMargin2, leftMargin2,bottomMargin,topMargin, "Perf","COLZ");
	delete histoCorrGamma_Phi_Pt;

	TH2F*	histoCorrGamma_Eta_Pt = (TH2F*)directoryGammaCorr->Get("ESD_CorrGamma_Eta_Pt");
	histoCorrGamma_Eta_Pt->Scale(1./numberOfTriggerGammas);
 	ConvGammaRebinWithBinCorrection2D(histoCorrGamma_Eta_Pt, 1, 1, 3);
	PlotStandard2D( histoCorrGamma_Eta_Pt , Form("%s/%s_GammaCorr_Eta_Pt.%s",outputDirectory.Data(),optData.Data(),suffix.Data()), "", "#eta", "p_{t} (GeV/c)", "#frac{dN_{#gamma,trig}}{N_{#gamma, trig} d#phi dp_{t}}", kTRUE, -0.9, 0.9,kTRUE, 0.1, 50., kTRUE,  9e-6, histoCorrGamma_Eta_Pt->GetMaximum(), 0,1, 1, floatLocationRightUp2DXY,1000,880,rightMargin2, leftMargin2,bottomMargin,topMargin, "Perf","COLZ");
	delete histoCorrGamma_Eta_Pt;

	
	TH2F*	histoCorrGamma_Phi_Eta = (TH2F*)directoryGammaCorr->Get("ESD_CorrGamma_Phi_Eta");
	histoCorrGamma_Phi_Eta->Scale(1./numberOfTriggerGammas);
	ConvGammaRebinWithBinCorrection2D(histoCorrGamma_Phi_Eta, 4, 4, 3);
	PlotStandard2D( histoCorrGamma_Phi_Eta , Form("%s/%s_GammaCorr_PhiCh_EtaCh.%s",outputDirectory.Data(),optData.Data(),suffix.Data()), "", "#phi (rad)", "#eta", "#frac{dN_{#gamma,trig}}{N_{#gamma, trig} d#eta d#phi}",  kTRUE, -TMath::Pi(), TMath::Pi(),kTRUE, -0.9, 0.9, kTRUE,  9e-2, histoCorrGamma_Phi_Eta->GetMaximum(), 0, 0, 1, floatLocationRightUp2DXY,1000,880,rightMargin, leftMargin,bottomMargin,topMargin, "Perf","SURF7");
	delete histoCorrGamma_Phi_Eta;
	
 	TH2F*	histoCorrGamma_dPhiCh_dEtaCh = (TH2F*)directoryGammaCorr->Get("ESD_CorrGamma_dPhiCh_dEtaCh");
	histoCorrGamma_dPhiCh_dEtaCh->Scale(1./numberOfTriggerGammas);
	ConvGammaRebinWithBinCorrection2D(histoCorrGamma_dPhiCh_dEtaCh, 4, 3, 3);
	PlotStandard2D( histoCorrGamma_dPhiCh_dEtaCh , Form("%s/%s_GammaCorr_dPhiCh_dEtaCh.%s",outputDirectory.Data(),optData.Data(),suffix.Data()), "", "#Delta#phi (rad)", "#Delta#eta", "#frac{dN_{ch,ass}}{N_{#gamma, trig} d#Delta#eta d#Delta#phi}", kFALSE, 0., 15., kTRUE, -1., 1.,kTRUE,  6.e-2, histoCorrGamma_dPhiCh_dEtaCh->GetMaximum(), 0, 0, 1, floatLocationRightUp2DXY,1000,880,rightMargin, leftMargin,bottomMargin,topMargin, "Perf","SURF7");
	delete histoCorrGamma_dPhiCh_dEtaCh;
	
 	TH2F*	histoCorrGamma_dPhiCh_dEtaCh_PtA1GeV_PtT2GeV = (TH2F*)directoryGammaCorr->Get("ESD_CorrGamma_dPhiCh_dEtaCh_PtA1GeV_PtT2GeV");
	histoCorrGamma_dPhiCh_dEtaCh_PtA1GeV_PtT2GeV->Scale(1./numberOfTriggerGammas);
	ConvGammaRebinWithBinCorrection2D(histoCorrGamma_dPhiCh_dEtaCh_PtA1GeV_PtT2GeV, 4, 3, 3);
	PlotStandard2D( histoCorrGamma_dPhiCh_dEtaCh_PtA1GeV_PtT2GeV , Form("%s/%s_GammaCorr_dPhiCh_dEtaCh_PtA1GeV_PtT2GeV.%s",outputDirectory.Data(),optData.Data(),suffix.Data()), "p_{t}^{A} > 1 GeV/c, p_{t}^{T} > 2 GeV/c", "#Delta#phi (rad)", "#Delta#eta","#frac{dN_{ch,ass}}{N_{#gamma, trig} d#Delta#eta d#Delta#phi}", kFALSE, 0., 15., kTRUE, -1., 1.,kTRUE,  1.e-3, histoCorrGamma_dPhiCh_dEtaCh_PtA1GeV_PtT2GeV->GetMaximum(), 0,0,  1, floatLocationRightUp2DXY,1000,880,rightMargin, leftMargin,bottomMargin,topMargin, "Perf","SURF7","p_{t}^{A} > 1 GeV/c, p_{t}^{T} > 2 GeV/c");
	delete histoCorrGamma_dPhiCh_dEtaCh_PtA1GeV_PtT2GeV;
	
	TH2F*	histoCorrGamma_dPhiCh_dEtaCh_PtA1GeV_PtT5GeV = (TH2F*)directoryGammaCorr->Get("ESD_CorrGamma_dPhiCh_dEtaCh_PtA1GeV_PtT5GeV");
	histoCorrGamma_dPhiCh_dEtaCh_PtA1GeV_PtT5GeV->Scale(1./numberOfTriggerGammas);
	ConvGammaRebinWithBinCorrection2D(histoCorrGamma_dPhiCh_dEtaCh_PtA1GeV_PtT5GeV, 4, 3, 3);
	PlotStandard2D( histoCorrGamma_dPhiCh_dEtaCh_PtA1GeV_PtT5GeV , Form("%s/%s_GammaCorr_dPhiCh_dEtaCh_PtA1GeV_PtT5GeV.%s",outputDirectory.Data(),optData.Data(),suffix.Data()), "p_{t}^{A} > 1 GeV/c, p_{t}^{T} > 5 GeV/c", "#Delta#phi (rad)", "#Delta#eta", "#frac{dN_{ch,ass}}{N_{#gamma, trig} d#Delta#eta d#Delta#phi}", kFALSE, 0., 15., kTRUE, -1., 1.,kTRUE,  1.e-5, histoCorrGamma_dPhiCh_dEtaCh_PtA1GeV_PtT5GeV->GetMaximum(), 0, 0, 1, floatLocationRightUp2DXY,1000,880,rightMargin, leftMargin,bottomMargin,topMargin, "Perf","SURF7","p_{t}^{A} > 1 GeV/c, p_{t}^{T} > 5 GeV/c");
	delete histoCorrGamma_dPhiCh_dEtaCh_PtA1GeV_PtT5GeV;
	
	TH2F*	histoCorrGamma_dPhiGa_dEtaGa =(TH2F*)directoryGammaCorr->Get("ESD_CorrGamma_dPhiGa_dEtaGa");
	histoCorrGamma_dPhiGa_dEtaGa->Scale(1./numberOfTriggerGammas);
	ConvGammaRebinWithBinCorrection2D(histoCorrGamma_dPhiGa_dEtaGa, 4, 3, 3);
	PlotStandard2D( histoCorrGamma_dPhiGa_dEtaGa , Form("%s/%s_GammaCorr_dPhiGa_dEtaGa.%s",outputDirectory.Data(),optData.Data(),suffix.Data()), "", "#Delta#phi (rad)", "#Delta#eta", "#frac{dN_{#gamma,ass}}{N_{#gamma, trig} d#Delta#eta d#Delta#phi}", kFALSE, 0., 15., kTRUE, -1., 1.,kTRUE,  2.e-3, histoCorrGamma_dPhiGa_dEtaGa->GetMaximum(), 0,0,  1, floatLocationRightUp2DXY,1000,880,rightMargin, leftMargin,bottomMargin,topMargin, "Perf","SURF7");
	delete histoCorrGamma_dPhiGa_dEtaGa;
	
// 	TH2F*	histoCorrGamma_IsoCh_PtTrig = (TH2F*)directoryGammaCorr->Get("ESD_CorrGamma_IsoCh_PtTrig");
// 	TH2F*	histoCorrGamma_IsoGa_PtTrig = (TH2F*)directoryGammaCorr->Get("ESD_CorrGamma_IsoGa_PtTrig");
 	TH2F*	histoCorrGamma_IsoMin_Pt = (TH2F*)directoryGammaCorr->Get("ESD_CorrGamma_IsoMin_Pt");
	histoCorrGamma_IsoMin_Pt->Scale(1./numberOfTriggerGammas);
	ConvGammaRebinWithBinCorrection2D(histoCorrGamma_IsoMin_Pt, 1, 1, 3);
 	PlotStandard2D( histoCorrGamma_IsoMin_Pt , Form("%s/%s_GammaCorr_IsoMin_PtTrig.%s",outputDirectory.Data(),optData.Data(),suffix.Data()), "", "R_{min}", "p_{t}^{T} (GeV/c)", "#frac{dN_{#gamma,trig}}{N_{#gamma, trig} dR dp_{t}}", kFALSE, 0., 15., kFALSE, -1., 1.,kTRUE,  2.e-5, histoCorrGamma_IsoMin_Pt->GetMaximum(), 0,0,  1, floatLocationRightUp2DXY,1000,880,rightMargin2, leftMargin2,bottomMargin,topMargin, "Perf","Colz");

	TH3F*	histoCorrGamma_dPhiCh_PtAssoc_PtTrig = (TH3F*)directoryGammaCorr->Get("ESD_CorrGamma_dPhiCh_PtAssoc_PtTrig");
	TH2D* histo2DGamma_dPhi_PtTrig = (TH2D*)histoCorrGamma_dPhiCh_PtAssoc_PtTrig->Project3D("zx_CorrGammaPhiA");
	histoCorrGamma_dPhiCh_PtAssoc_PtTrig->GetYaxis()->SetRange(histoCorrGamma_dPhiCh_PtAssoc_PtTrig->GetYaxis()->FindBin(1.),histoCorrGamma_dPhiCh_PtAssoc_PtTrig->GetYaxis()->FindBin(50.));
	TH2D* histo2DGamma_dPhi_PtTrig_minPtAss05 = (TH2D*)histoCorrGamma_dPhiCh_PtAssoc_PtTrig->Project3D("zx_CorrGammaPhiB");
	histoCorrGamma_dPhiCh_PtAssoc_PtTrig->GetYaxis()->SetRange(histoCorrGamma_dPhiCh_PtAssoc_PtTrig->GetYaxis()->FindBin(2.),histoCorrGamma_dPhiCh_PtAssoc_PtTrig->GetYaxis()->FindBin(50.));
	TH2D* histo2DGamma_dPhi_PtTrig_minPtAss1 = (TH2D*)histoCorrGamma_dPhiCh_PtAssoc_PtTrig->Project3D("zx_CorrGammaPhiC");
 	delete histoCorrGamma_dPhiCh_PtAssoc_PtTrig;
	
	TH3F*	histoCorrGamma_dEtaCh_PtAssoc_PtTrig = (TH3F*)directoryGammaCorr->Get("ESD_CorrGamma_dEtaCh_PtAssoc_PtTrig");
	TH2D* histo2DGamma_dEta_PtTrig = (TH2D*)histoCorrGamma_dEtaCh_PtAssoc_PtTrig->Project3D("zx_CorrGammaEtaA");
	histoCorrGamma_dEtaCh_PtAssoc_PtTrig->GetYaxis()->SetRange(histoCorrGamma_dEtaCh_PtAssoc_PtTrig->GetYaxis()->FindBin(1.),histoCorrGamma_dEtaCh_PtAssoc_PtTrig->GetYaxis()->FindBin(50.));
	TH2D* histo2DGamma_dEta_PtTrig_minPtAss05 = (TH2D*)histoCorrGamma_dEtaCh_PtAssoc_PtTrig->Project3D("zx_CorrGammaEtaB");
	histoCorrGamma_dEtaCh_PtAssoc_PtTrig->GetYaxis()->SetRange(histoCorrGamma_dEtaCh_PtAssoc_PtTrig->GetYaxis()->FindBin(2.),histoCorrGamma_dEtaCh_PtAssoc_PtTrig->GetYaxis()->FindBin(50.));
	TH2D* histo2DGamma_dEta_PtTrig_minPtAss1 = (TH2D*)histoCorrGamma_dEtaCh_PtAssoc_PtTrig->Project3D("zx_CorrGammaEtaC");
 	delete histoCorrGamma_dEtaCh_PtAssoc_PtTrig;

	TH3F*	histoCorrGamma_dPhiGa_PtAssoc_PtTrig = (TH3F*)directoryGammaCorr->Get("ESD_CorrGamma_dPhiGa_PtAssoc_PtTrig");
	TH2D* histo2DGamma_dPhiGa_PtTrig = (TH2D*)histoCorrGamma_dPhiGa_PtAssoc_PtTrig->Project3D("zx_CorrGammaPhiGaA");
	histoCorrGamma_dPhiGa_PtAssoc_PtTrig->GetYaxis()->SetRange(histoCorrGamma_dPhiGa_PtAssoc_PtTrig->GetYaxis()->FindBin(1.),histoCorrGamma_dPhiGa_PtAssoc_PtTrig->GetYaxis()->FindBin(50.));
	TH2D* histo2DGamma_dPhiGa_PtTrig_minPtAss05 = (TH2D*)histoCorrGamma_dPhiGa_PtAssoc_PtTrig->Project3D("zx_CorrGammaPhiGaB");
	histoCorrGamma_dPhiGa_PtAssoc_PtTrig->GetYaxis()->SetRange(histoCorrGamma_dPhiGa_PtAssoc_PtTrig->GetYaxis()->FindBin(2.),histoCorrGamma_dPhiGa_PtAssoc_PtTrig->GetYaxis()->FindBin(50.));
	TH2D* histo2DGamma_dPhiGa_PtTrig_minPtAss1 = (TH2D*)histoCorrGamma_dPhiGa_PtAssoc_PtTrig->Project3D("zx_CorrGammaPhiGaC");
 	delete histoCorrGamma_dPhiGa_PtAssoc_PtTrig;

	TH3F*	histoCorrGamma_dEtaGa_PtAssoc_PtTrig = (TH3F*)directoryGammaCorr->Get("ESD_CorrGamma_dEtaGa_PtAssoc_PtTrig");
	TH2D* histo2DGamma_dEtaGa_PtTrig = (TH2D*)histoCorrGamma_dEtaGa_PtAssoc_PtTrig->Project3D("zx_CorrGammaEtaGaA");
	histoCorrGamma_dEtaGa_PtAssoc_PtTrig->GetYaxis()->SetRange(histoCorrGamma_dEtaGa_PtAssoc_PtTrig->GetYaxis()->FindBin(1.),histoCorrGamma_dEtaGa_PtAssoc_PtTrig->GetYaxis()->FindBin(50.));
	TH2D* histo2DGamma_dEtaGa_PtTrig_minPtAss05 = (TH2D*)histoCorrGamma_dEtaGa_PtAssoc_PtTrig->Project3D("zx_CorrGammaEtaGaB");
	histoCorrGamma_dEtaGa_PtAssoc_PtTrig->GetYaxis()->SetRange(histoCorrGamma_dEtaGa_PtAssoc_PtTrig->GetYaxis()->FindBin(2.),histoCorrGamma_dEtaGa_PtAssoc_PtTrig->GetYaxis()->FindBin(50.));
	TH2D* histo2DGamma_dEtaGa_PtTrig_minPtAss1 = (TH2D*)histoCorrGamma_dEtaGa_PtAssoc_PtTrig->Project3D("zx_CorrGammaEtaGaC");
 	delete histoCorrGamma_dEtaGa_PtAssoc_PtTrig;

	TH3F*	histoCorrGammaIso_dPhiCh_PtAssoc_PtTrig = (TH3F*)directoryGammaCorr->Get("ESD_CorrGammaIso_dPhiCh_PtAssoc_PtTrig");
	TH2D* histo2DGammaIso_dPhi_PtTrig = (TH2D*)histoCorrGammaIso_dPhiCh_PtAssoc_PtTrig->Project3D("zx_GammaCorrIsoPhiA");
	histoCorrGammaIso_dPhiCh_PtAssoc_PtTrig->GetYaxis()->SetRange(histoCorrGammaIso_dPhiCh_PtAssoc_PtTrig->GetYaxis()->FindBin(1.),histoCorrGammaIso_dPhiCh_PtAssoc_PtTrig->GetYaxis()->FindBin(50.));
	TH2D* histo2DGammaIso_dPhi_PtTrig_minPtAss05 = (TH2D*)histoCorrGammaIso_dPhiCh_PtAssoc_PtTrig->Project3D("zx_GammaCorrIsoPhiB");
	histoCorrGammaIso_dPhiCh_PtAssoc_PtTrig->GetYaxis()->SetRange(histoCorrGammaIso_dPhiCh_PtAssoc_PtTrig->GetYaxis()->FindBin(2.),histoCorrGammaIso_dPhiCh_PtAssoc_PtTrig->GetYaxis()->FindBin(50.));
	TH2D* histo2DGammaIso_dPhi_PtTrig_minPtAss1 = (TH2D*)histoCorrGammaIso_dPhiCh_PtAssoc_PtTrig->Project3D("zx_GammaCorrIsoPhiC");
 	delete histoCorrGammaIso_dPhiCh_PtAssoc_PtTrig;


	TH3F*	histoCorrGammaIso_dEtaCh_PtAssoc_PtTrig = (TH3F*)directoryGammaCorr->Get("ESD_CorrGammaIso_dEtaCh_PtAssoc_PtTrig");
	TH2D* histo2DGammaIso_dEta_PtTrig = (TH2D*)histoCorrGammaIso_dEtaCh_PtAssoc_PtTrig->Project3D("zx_GammaCorrIsoEtaA");
	histoCorrGammaIso_dEtaCh_PtAssoc_PtTrig->GetYaxis()->SetRange(histoCorrGammaIso_dEtaCh_PtAssoc_PtTrig->GetYaxis()->FindBin(1.),histoCorrGammaIso_dEtaCh_PtAssoc_PtTrig->GetYaxis()->FindBin(50.));
	TH2D* histo2DGammaIso_dEta_PtTrig_minPtAss05 = (TH2D*)histoCorrGammaIso_dEtaCh_PtAssoc_PtTrig->Project3D("zx_GammaCorrIsoEtaB");
	histoCorrGammaIso_dEtaCh_PtAssoc_PtTrig->GetYaxis()->SetRange(histoCorrGammaIso_dEtaCh_PtAssoc_PtTrig->GetYaxis()->FindBin(2.),histoCorrGammaIso_dEtaCh_PtAssoc_PtTrig->GetYaxis()->FindBin(50.));
	TH2D* histo2DGammaIso_dEta_PtTrig_minPtAss1 = (TH2D*)histoCorrGammaIso_dEtaCh_PtAssoc_PtTrig->Project3D("zx_GammaCorrIsoEtaC");
 	delete histoCorrGammaIso_dEtaCh_PtAssoc_PtTrig;
	
	
	TString fileNameOutput = "CorrelationOutputNew1stStep.root";
	TFile* fileCorrWrite = new TFile(fileNameOutput.Data(),"UPDATE");
	fileCorrWrite->mkdir(Form("CorrGamma_%s",  cutSelection.Data()));
	fileCorrWrite->cd(Form("CorrGamma_%s",  cutSelection.Data()));
	
	histoCorrGamma_IsoMin_Pt->Write(Form("ESD_%s_CorrGamma_IsoMin_Pt",optData.Data()),TObject::kWriteDelete);		
	
	histoAssociatedGamma->Write(Form("ESD_%s_AssociatedGamma",optData.Data()),TObject::kWriteDelete);		
	histoAssociatedCh->Write(Form("ESD_%s_AssociatedCh",optData.Data()),TObject::kWriteDelete);		
	
	histo2DGamma_dEta_PtTrig->Write(Form("ESD_%s_CorrGamma_dEtaCh_PtTrig",optData.Data()),TObject::kWriteDelete);
	histo2DGamma_dEta_PtTrig_minPtAss05->Write(Form("ESD_%s_CorrGamma_dEtaCh_PtTrig_minPtAssA",optData.Data()),TObject::kWriteDelete);
	histo2DGamma_dEta_PtTrig_minPtAss1->Write(Form("ESD_%s_CorrGamma_dEtaCh_PtTrig_minPtAssB",optData.Data()),TObject::kWriteDelete);
	histo2DGammaIso_dEta_PtTrig->Write(Form("ESD_%s_CorrGammaIso_dEtaCh_PtTrig",optData.Data()),TObject::kWriteDelete);
	histo2DGammaIso_dEta_PtTrig_minPtAss05->Write(Form("ESD_%s_CorrGammaIso_dEtaCh_PtTrig_minPtAssA",optData.Data()),TObject::kWriteDelete);
	histo2DGammaIso_dEta_PtTrig_minPtAss1->Write(Form("ESD_%s_CorrGammaIso_dEtaCh_PtTrig_minPtAssB",optData.Data()),TObject::kWriteDelete);
	histo2DGamma_dEtaGa_PtTrig->Write(Form("ESD_%s_CorrGamma_dEtaGa_PtTrig",optData.Data()),TObject::kWriteDelete);
	histo2DGamma_dEtaGa_PtTrig_minPtAss05->Write(Form("ESD_%s_CorrGamma_dEtaGa_PtTrig_minPtAssA",optData.Data()),TObject::kWriteDelete);
	histo2DGamma_dEtaGa_PtTrig_minPtAss1->Write(Form("ESD_%s_CorrGamma_dEtaGa_PtTrig_minPtAssB",optData.Data()),TObject::kWriteDelete);
	
	histo2DGamma_dPhi_PtTrig->Write(Form("ESD_%s_CorrGamma_dPhiCh_PtTrig",optData.Data()),TObject::kWriteDelete);
	histo2DGamma_dPhi_PtTrig_minPtAss05->Write(Form("ESD_%s_CorrGamma_dPhiCh_PtTrig_minPtAssA",optData.Data()),TObject::kWriteDelete);
	histo2DGamma_dPhi_PtTrig_minPtAss1->Write(Form("ESD_%s_CorrGamma_dPhiCh_PtTrig_minPtAssB",optData.Data()),TObject::kWriteDelete);
	histo2DGammaIso_dPhi_PtTrig->Write(Form("ESD_%s_CorrGammaIso_dPhiCh_PtTrig",optData.Data()),TObject::kWriteDelete);
	histo2DGammaIso_dPhi_PtTrig_minPtAss05->Write(Form("ESD_%s_CorrGammaIso_dPhiCh_PtTrig_minPtAssA",optData.Data()),TObject::kWriteDelete);
	histo2DGammaIso_dPhi_PtTrig_minPtAss1->Write(Form("ESD_%s_CorrGammaIso_dPhiCh_PtTrig_minPtAssB",optData.Data()),TObject::kWriteDelete);
	histo2DGamma_dPhiGa_PtTrig->Write(Form("ESD_%s_CorrGamma_dPhiGa_PtTrig",optData.Data()),TObject::kWriteDelete);
	histo2DGamma_dPhiGa_PtTrig_minPtAss05->Write(Form("ESD_%s_CorrGamma_dPhiGa_PtTrig_minPtAssA",optData.Data()),TObject::kWriteDelete);
	histo2DGamma_dPhiGa_PtTrig_minPtAss1->Write(Form("ESD_%s_CorrGamma_dPhiGa_PtTrig_minPtAssB",optData.Data()),TObject::kWriteDelete);
	
	fileCorrWrite->Write();

	if (optData.CompareTo("MCRec")== 0){
		optData = "MCTrue" ;
		TH2F*	histoCorrTrueGamma_Phi_Eta = (TH2F*)directoryGammaCorr->Get("ESD_CorrTrueGamma_Phi_Eta");
		histoCorrTrueGamma_Phi_Eta->Scale(1./numberOfTriggerGammas);
		ConvGammaRebinWithBinCorrection2D(histoCorrTrueGamma_Phi_Eta, 4, 4, 3);
		PlotStandard2D( histoCorrTrueGamma_Phi_Eta , Form("%s/%s_GammaCorr_PhiCh_EtaCh.%s",outputDirectory.Data(),optData.Data(),suffix.Data()), "", "#phi (rad)", "#eta", "#frac{dN_{#gamma,trig}}{N_{#gamma, trig} d#eta d#phi}",  kTRUE, -TMath::Pi(), TMath::Pi(),kTRUE, -0.9, 0.9, kTRUE,  9e-2, histoCorrTrueGamma_Phi_Eta->GetMaximum(), 0, 0, 1, floatLocationRightUp2DXY,1000,880,rightMargin, leftMargin,bottomMargin,topMargin, "Perf","SURF7");
		delete histoCorrTrueGamma_Phi_Eta;
		
		TH2F*	histoCorrTrueGamma_dPhiCh_dEtaCh = (TH2F*)directoryGammaCorr->Get("ESD_CorrTrueGamma_dPhiCh_dEtaCh");
		histoCorrTrueGamma_dPhiCh_dEtaCh->Scale(1./numberOfTriggerGammas);
		ConvGammaRebinWithBinCorrection2D(histoCorrTrueGamma_dPhiCh_dEtaCh, 4, 3, 3);
		PlotStandard2D( histoCorrTrueGamma_dPhiCh_dEtaCh , Form("%s/%s_GammaCorr_dPhiCh_dEtaCh.%s",outputDirectory.Data(),optData.Data(),suffix.Data()), "", "#Delta#phi (rad)", "#Delta#eta", "#frac{dN_{ch,ass}}{N_{#gamma, trig} d#Delta#eta d#Delta#phi}", kFALSE, 0., 15., kTRUE, -1., 1.,kTRUE,  6.e-2, histoCorrTrueGamma_dPhiCh_dEtaCh->GetMaximum(), 0, 0, 1, floatLocationRightUp2DXY,1000,880,rightMargin, leftMargin,bottomMargin,topMargin, "Perf","SURF7");
		delete histoCorrTrueGamma_dPhiCh_dEtaCh;
		
		TH2F*	histoCorrTrueGamma_dPhiCh_dEtaCh_PtA1GeV_PtT2GeV = (TH2F*)directoryGammaCorr->Get("ESD_CorrTrueGamma_dPhiCh_dEtaCh_PtA1GeV_PtT2GeV");
		histoCorrTrueGamma_dPhiCh_dEtaCh_PtA1GeV_PtT2GeV->Scale(1./numberOfTriggerGammas);
		ConvGammaRebinWithBinCorrection2D(histoCorrTrueGamma_dPhiCh_dEtaCh_PtA1GeV_PtT2GeV, 4, 3, 3);
		PlotStandard2D( histoCorrTrueGamma_dPhiCh_dEtaCh_PtA1GeV_PtT2GeV , Form("%s/%s_GammaCorr_dPhiCh_dEtaCh_PtA1GeV_PtT2GeV.%s",outputDirectory.Data(),optData.Data(),suffix.Data()), "p_{t}^{A} > 1 GeV/c, p_{t}^{T} > 2 GeV/c", "#Delta#phi (rad)", "#Delta#eta","#frac{dN_{ch,ass}}{N_{#gamma, trig} d#Delta#eta d#Delta#phi}", kFALSE, 0., 15., kTRUE, -1., 1.,kTRUE,  1.e-3, histoCorrTrueGamma_dPhiCh_dEtaCh_PtA1GeV_PtT2GeV->GetMaximum(), 0,0,  1, floatLocationRightUp2DXY,1000,880,rightMargin, leftMargin,bottomMargin,topMargin, "Perf","SURF7","p_{t}^{A} > 1 GeV/c, p_{t}^{T} > 2 GeV/c");
		delete histoCorrTrueGamma_dPhiCh_dEtaCh_PtA1GeV_PtT2GeV;
		
		TH2F*	histoCorrTrueGamma_dPhiCh_dEtaCh_PtA1GeV_PtT5GeV = (TH2F*)directoryGammaCorr->Get("ESD_CorrTrueGamma_dPhiCh_dEtaCh_PtA1GeV_PtT5GeV");
		histoCorrTrueGamma_dPhiCh_dEtaCh_PtA1GeV_PtT5GeV->Scale(1./numberOfTriggerGammas);
		ConvGammaRebinWithBinCorrection2D(histoCorrTrueGamma_dPhiCh_dEtaCh_PtA1GeV_PtT5GeV, 4, 3, 3);
		PlotStandard2D( histoCorrTrueGamma_dPhiCh_dEtaCh_PtA1GeV_PtT5GeV , Form("%s/%s_GammaCorr_dPhiCh_dEtaCh_PtA1GeV_PtT5GeV.%s",outputDirectory.Data(),optData.Data(),suffix.Data()), "p_{t}^{A} > 1 GeV/c, p_{t}^{T} > 5 GeV/c", "#Delta#phi (rad)", "#Delta#eta", "#frac{dN_{ch,ass}}{N_{#gamma, trig} d#Delta#eta d#Delta#phi}", kFALSE, 0., 15., kTRUE, -1., 1.,kTRUE,  1.e-5, histoCorrTrueGamma_dPhiCh_dEtaCh_PtA1GeV_PtT5GeV->GetMaximum(), 0, 0, 1, floatLocationRightUp2DXY,1000,880,rightMargin, leftMargin,bottomMargin,topMargin, "Perf","SURF7","p_{t}^{A} > 1 GeV/c, p_{t}^{T} > 5 GeV/c");
		delete histoCorrTrueGamma_dPhiCh_dEtaCh_PtA1GeV_PtT5GeV;
		
		TH2F*	histoCorrTrueGamma_dPhiGa_dEtaGa =(TH2F*)directoryGammaCorr->Get("ESD_CorrTrueGamma_dPhiGa_dEtaGa");
		histoCorrTrueGamma_dPhiGa_dEtaGa->Scale(1./numberOfTriggerGammas);
		ConvGammaRebinWithBinCorrection2D(histoCorrTrueGamma_dPhiGa_dEtaGa, 4, 3, 3);
		PlotStandard2D( histoCorrTrueGamma_dPhiGa_dEtaGa , Form("%s/%s_GammaCorr_dPhiGa_dEtaGa.%s",outputDirectory.Data(),optData.Data(),suffix.Data()), "", "#Delta#phi (rad)", "#Delta#eta", "#frac{dN_{#gamma,ass}}{N_{#gamma, trig} d#Delta#eta d#Delta#phi}", kFALSE, 0., 15., kTRUE, -1., 1.,kTRUE,  2.e-3, histoCorrTrueGamma_dPhiGa_dEtaGa->GetMaximum(), 0,0,  1, floatLocationRightUp2DXY,1000,880,rightMargin, leftMargin,bottomMargin,topMargin, "Perf","SURF7");
		delete histoCorrTrueGamma_dPhiGa_dEtaGa;
		
		TH2F*	histoCorrTrueGamma_IsoMin_Pt = (TH2F*)directoryGammaCorr->Get("ESD_CorrTrueGamma_IsoMin_Pt");
		histoCorrTrueGamma_IsoMin_Pt->Scale(1./numberOfTriggerGammas);
		ConvGammaRebinWithBinCorrection2D(histoCorrTrueGamma_IsoMin_Pt, 1, 1, 3);
		PlotStandard2D( histoCorrTrueGamma_IsoMin_Pt , Form("%s/%s_GammaCorr_IsoMin_PtTrig.%s",outputDirectory.Data(),optData.Data(),suffix.Data()), "", "R_{min}", "p_{t}^{T} (GeV/c)", "#frac{dN_{#gamma,trig}}{N_{#gamma, trig} dR dp_{t}}", kFALSE, 0., 15., kFALSE, -1., 1.,kTRUE,  2.e-5, histoCorrTrueGamma_IsoMin_Pt->GetMaximum(), 0,0,  1, floatLocationRightUp2DXY,1000,880,rightMargin2, leftMargin2,bottomMargin,topMargin, "Perf","Colz");

		TH3F*	histoCorrTrueGamma_dPhiCh_PtAssoc_PtTrig = (TH3F*)directoryGammaCorr->Get("ESD_CorrTrueGamma_dPhiCh_PtAssoc_PtTrig");
		TH2D* histo2DTrueGamma_dPhi_PtTrig = (TH2D*)histoCorrTrueGamma_dPhiCh_PtAssoc_PtTrig->Project3D("zx_CorrTrueGammaPhiA");
		histoCorrTrueGamma_dPhiCh_PtAssoc_PtTrig->GetYaxis()->SetRange(histoCorrTrueGamma_dPhiCh_PtAssoc_PtTrig->GetYaxis()->FindBin(1.),histoCorrTrueGamma_dPhiCh_PtAssoc_PtTrig->GetYaxis()->FindBin(50.));
		TH2D* histo2DTrueGamma_dPhi_PtTrig_minPtAss05 = (TH2D*)histoCorrTrueGamma_dPhiCh_PtAssoc_PtTrig->Project3D("zx_CorrTrueGammaPhiB");
		histoCorrTrueGamma_dPhiCh_PtAssoc_PtTrig->GetYaxis()->SetRange(histoCorrTrueGamma_dPhiCh_PtAssoc_PtTrig->GetYaxis()->FindBin(2.),histoCorrTrueGamma_dPhiCh_PtAssoc_PtTrig->GetYaxis()->FindBin(50.));
		TH2D* histo2DTrueGamma_dPhi_PtTrig_minPtAss1 = (TH2D*)histoCorrTrueGamma_dPhiCh_PtAssoc_PtTrig->Project3D("zx_CorrTrueGammaPhiC");
		delete histoCorrTrueGamma_dPhiCh_PtAssoc_PtTrig;
		
		TH3F*	histoCorrTrueGamma_dEtaCh_PtAssoc_PtTrig = (TH3F*)directoryGammaCorr->Get("ESD_CorrTrueGamma_dEtaCh_PtAssoc_PtTrig");
		TH2D* histo2DTrueGamma_dEta_PtTrig = (TH2D*)histoCorrTrueGamma_dEtaCh_PtAssoc_PtTrig->Project3D("zx_CorrTrueGammaEtaA");
		histoCorrTrueGamma_dEtaCh_PtAssoc_PtTrig->GetYaxis()->SetRange(histoCorrTrueGamma_dEtaCh_PtAssoc_PtTrig->GetYaxis()->FindBin(1.),histoCorrTrueGamma_dEtaCh_PtAssoc_PtTrig->GetYaxis()->FindBin(50.));
		TH2D* histo2DTrueGamma_dEta_PtTrig_minPtAss05 = (TH2D*)histoCorrTrueGamma_dEtaCh_PtAssoc_PtTrig->Project3D("zx_CorrTrueGammaEtaB");
		histoCorrTrueGamma_dEtaCh_PtAssoc_PtTrig->GetYaxis()->SetRange(histoCorrTrueGamma_dEtaCh_PtAssoc_PtTrig->GetYaxis()->FindBin(2.),histoCorrTrueGamma_dEtaCh_PtAssoc_PtTrig->GetYaxis()->FindBin(50.));
		TH2D* histo2DTrueGamma_dEta_PtTrig_minPtAss1 = (TH2D*)histoCorrTrueGamma_dEtaCh_PtAssoc_PtTrig->Project3D("zx_CorrTrueGammaEtaC");
		delete histoCorrTrueGamma_dEtaCh_PtAssoc_PtTrig;

		TH3F*	histoCorrTrueGamma_dPhiGa_PtAssoc_PtTrig = (TH3F*)directoryGammaCorr->Get("ESD_CorrTrueGamma_dPhiGa_PtAssoc_PtTrig");
		TH2D* histo2DTrueGamma_dPhiGa_PtTrig = (TH2D*)histoCorrTrueGamma_dPhiGa_PtAssoc_PtTrig->Project3D("zx_CorrTrueGammaPhiGaA");
		histoCorrTrueGamma_dPhiGa_PtAssoc_PtTrig->GetYaxis()->SetRange(histoCorrTrueGamma_dPhiGa_PtAssoc_PtTrig->GetYaxis()->FindBin(1.),histoCorrTrueGamma_dPhiGa_PtAssoc_PtTrig->GetYaxis()->FindBin(50.));
		TH2D* histo2DTrueGamma_dPhiGa_PtTrig_minPtAss05 = (TH2D*)histoCorrTrueGamma_dPhiGa_PtAssoc_PtTrig->Project3D("zx_CorrTrueGammaPhiGaB");
		histoCorrTrueGamma_dPhiGa_PtAssoc_PtTrig->GetYaxis()->SetRange(histoCorrTrueGamma_dPhiGa_PtAssoc_PtTrig->GetYaxis()->FindBin(2.),histoCorrTrueGamma_dPhiGa_PtAssoc_PtTrig->GetYaxis()->FindBin(50.));
		TH2D* histo2DTrueGamma_dPhiGa_PtTrig_minPtAss1 = (TH2D*)histoCorrTrueGamma_dPhiGa_PtAssoc_PtTrig->Project3D("zx_CorrTrueGammaPhiGaC");
		delete histoCorrTrueGamma_dPhiGa_PtAssoc_PtTrig;

		TH3F*	histoCorrTrueGamma_dEtaGa_PtAssoc_PtTrig = (TH3F*)directoryGammaCorr->Get("ESD_CorrTrueGamma_dEtaGa_PtAssoc_PtTrig");
		TH2D* histo2DTrueGamma_dEtaGa_PtTrig = (TH2D*)histoCorrTrueGamma_dEtaGa_PtAssoc_PtTrig->Project3D("zx_CorrTrueGammaEtaGaA");
		histoCorrTrueGamma_dEtaGa_PtAssoc_PtTrig->GetYaxis()->SetRange(histoCorrTrueGamma_dEtaGa_PtAssoc_PtTrig->GetYaxis()->FindBin(1.),histoCorrTrueGamma_dEtaGa_PtAssoc_PtTrig->GetYaxis()->FindBin(50.));
		TH2D* histo2DTrueGamma_dEtaGa_PtTrig_minPtAss05 = (TH2D*)histoCorrTrueGamma_dEtaGa_PtAssoc_PtTrig->Project3D("zx_CorrTrueGammaEtaGaB");
		histoCorrTrueGamma_dEtaGa_PtAssoc_PtTrig->GetYaxis()->SetRange(histoCorrTrueGamma_dEtaGa_PtAssoc_PtTrig->GetYaxis()->FindBin(2.),histoCorrTrueGamma_dEtaGa_PtAssoc_PtTrig->GetYaxis()->FindBin(50.));
		TH2D* histo2DTrueGamma_dEtaGa_PtTrig_minPtAss1 = (TH2D*)histoCorrTrueGamma_dEtaGa_PtAssoc_PtTrig->Project3D("zx_CorrTrueGammaEtaGaC");
		delete histoCorrTrueGamma_dEtaGa_PtAssoc_PtTrig;

		TH3F*	histoCorrTrueGammaIso_dPhiCh_PtAssoc_PtTrig = (TH3F*)directoryGammaCorr->Get("ESD_CorrTrueGammaIso_dPhiCh_PtAssoc_PtTrig");
		TH2D* histo2DTrueGammaIso_dPhi_PtTrig = (TH2D*)histoCorrTrueGammaIso_dPhiCh_PtAssoc_PtTrig->Project3D("zx_TrueGammaCorrIsoPhiA");
		histoCorrTrueGammaIso_dPhiCh_PtAssoc_PtTrig->GetYaxis()->SetRange(histoCorrTrueGammaIso_dPhiCh_PtAssoc_PtTrig->GetYaxis()->FindBin(1.),histoCorrTrueGammaIso_dPhiCh_PtAssoc_PtTrig->GetYaxis()->FindBin(50.));
		TH2D* histo2DTrueGammaIso_dPhi_PtTrig_minPtAss05 = (TH2D*)histoCorrTrueGammaIso_dPhiCh_PtAssoc_PtTrig->Project3D("zx_TrueGammaCorrIsoPhiB");
		histoCorrTrueGammaIso_dPhiCh_PtAssoc_PtTrig->GetYaxis()->SetRange(histoCorrTrueGammaIso_dPhiCh_PtAssoc_PtTrig->GetYaxis()->FindBin(2.),histoCorrTrueGammaIso_dPhiCh_PtAssoc_PtTrig->GetYaxis()->FindBin(50.));
		TH2D* histo2DTrueGammaIso_dPhi_PtTrig_minPtAss1 = (TH2D*)histoCorrTrueGammaIso_dPhiCh_PtAssoc_PtTrig->Project3D("zx_TrueGammaCorrIsoPhiC");
		delete histoCorrTrueGammaIso_dPhiCh_PtAssoc_PtTrig;


		TH3F*	histoCorrTrueGammaIso_dEtaCh_PtAssoc_PtTrig = (TH3F*)directoryGammaCorr->Get("ESD_CorrTrueGammaIso_dEtaCh_PtAssoc_PtTrig");
		TH2D* histo2DTrueGammaIso_dEta_PtTrig = (TH2D*)histoCorrTrueGammaIso_dEtaCh_PtAssoc_PtTrig->Project3D("zx_TrueGammaCorrIsoEtaA");
		histoCorrTrueGammaIso_dEtaCh_PtAssoc_PtTrig->GetYaxis()->SetRange(histoCorrTrueGammaIso_dEtaCh_PtAssoc_PtTrig->GetYaxis()->FindBin(1.),histoCorrTrueGammaIso_dEtaCh_PtAssoc_PtTrig->GetYaxis()->FindBin(50.));
		TH2D* histo2DTrueGammaIso_dEta_PtTrig_minPtAss05 = (TH2D*)histoCorrTrueGammaIso_dEtaCh_PtAssoc_PtTrig->Project3D("zx_TrueGammaCorrIsoEtaB");
		histoCorrTrueGammaIso_dEtaCh_PtAssoc_PtTrig->GetYaxis()->SetRange(histoCorrTrueGammaIso_dEtaCh_PtAssoc_PtTrig->GetYaxis()->FindBin(2.),histoCorrTrueGammaIso_dEtaCh_PtAssoc_PtTrig->GetYaxis()->FindBin(50.));
		TH2D* histo2DTrueGammaIso_dEta_PtTrig_minPtAss1 = (TH2D*)histoCorrTrueGammaIso_dEtaCh_PtAssoc_PtTrig->Project3D("zx_TrueGammaCorrIsoEtaC");
		delete histoCorrTrueGammaIso_dEtaCh_PtAssoc_PtTrig;
		
		fileCorrWrite->cd(Form("CorrGamma_%s",  cutSelection.Data()));
		
		histoCorrTrueGamma_IsoMin_Pt->Write(Form("ESD_%s_CorrGamma_IsoMin_Pt",optData.Data()),TObject::kWriteDelete);		
		
		histo2DTrueGamma_dEta_PtTrig->Write(Form("ESD_%s_CorrGamma_dEtaCh_PtTrig",optData.Data()),TObject::kWriteDelete);
		histo2DTrueGamma_dEta_PtTrig_minPtAss05->Write(Form("ESD_%s_CorrGamma_dEtaCh_PtTrig_minPtAssA",optData.Data()),TObject::kWriteDelete);
		histo2DTrueGamma_dEta_PtTrig_minPtAss1->Write(Form("ESD_%s_CorrGamma_dEtaCh_PtTrig_minPtAssB",optData.Data()),TObject::kWriteDelete);
		histo2DTrueGammaIso_dEta_PtTrig->Write(Form("ESD_%s_CorrGammaIso_dEtaCh_PtTrig",optData.Data()),TObject::kWriteDelete);
		histo2DTrueGammaIso_dEta_PtTrig_minPtAss05->Write(Form("ESD_%s_CorrGammaIso_dEtaCh_PtTrig_minPtAssA",optData.Data()),TObject::kWriteDelete);
		histo2DTrueGammaIso_dEta_PtTrig_minPtAss1->Write(Form("ESD_%s_CorrGammaIso_dEtaCh_PtTrig_minPtAssB",optData.Data()),TObject::kWriteDelete);
		histo2DTrueGamma_dEtaGa_PtTrig->Write(Form("ESD_%s_CorrGamma_dEtaGa_PtTrig",optData.Data()),TObject::kWriteDelete);
		histo2DTrueGamma_dEtaGa_PtTrig_minPtAss05->Write(Form("ESD_%s_CorrGamma_dEtaGa_PtTrig_minPtAssA",optData.Data()),TObject::kWriteDelete);
		histo2DTrueGamma_dEtaGa_PtTrig_minPtAss1->Write(Form("ESD_%s_CorrGamma_dEtaGa_PtTrig_minPtAssB",optData.Data()),TObject::kWriteDelete);
		
		histo2DTrueGamma_dPhi_PtTrig->Write(Form("ESD_%s_CorrGamma_dPhiCh_PtTrig",optData.Data()),TObject::kWriteDelete);
		histo2DTrueGamma_dPhi_PtTrig_minPtAss05->Write(Form("ESD_%s_CorrGamma_dPhiCh_PtTrig_minPtAssA",optData.Data()),TObject::kWriteDelete);
		histo2DTrueGamma_dPhi_PtTrig_minPtAss1->Write(Form("ESD_%s_CorrGamma_dPhiCh_PtTrig_minPtAssB",optData.Data()),TObject::kWriteDelete);
		histo2DTrueGammaIso_dPhi_PtTrig->Write(Form("ESD_%s_CorrGammaIso_dPhiCh_PtTrig",optData.Data()),TObject::kWriteDelete);
		histo2DTrueGammaIso_dPhi_PtTrig_minPtAss05->Write(Form("ESD_%s_CorrGammaIso_dPhiCh_PtTrig_minPtAssA",optData.Data()),TObject::kWriteDelete);
		histo2DTrueGammaIso_dPhi_PtTrig_minPtAss1->Write(Form("ESD_%s_CorrGammaIso_dPhiCh_PtTrig_minPtAssB",optData.Data()),TObject::kWriteDelete);
		histo2DTrueGamma_dPhiGa_PtTrig->Write(Form("ESD_%s_CorrGamma_dPhiGa_PtTrig",optData.Data()),TObject::kWriteDelete);
		histo2DTrueGamma_dPhiGa_PtTrig_minPtAss05->Write(Form("ESD_%s_CorrGamma_dPhiGa_PtTrig_minPtAssA",optData.Data()),TObject::kWriteDelete);
		histo2DTrueGamma_dPhiGa_PtTrig_minPtAss1->Write(Form("ESD_%s_CorrGamma_dPhiGa_PtTrig_minPtAssB",optData.Data()),TObject::kWriteDelete);
		
		fileCorrWrite->Write();
		fileCorrWrite->Close();

	}
	
}
