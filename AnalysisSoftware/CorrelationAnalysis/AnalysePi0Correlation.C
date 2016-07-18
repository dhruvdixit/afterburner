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

void AnalysePi0Correlation(TString nameFileData = "GammaConvCorr_Data.root", TString cutSelection = "001023", TString suffix ="eps", TString optData = "Data", TString optEnergy = "7TeV", TString optMCGenerator = ""){
		
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
	outputDirectory =	 	Form("%s/%s/Pi0Correlation",cutSelection.Data(),suffix.Data());
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
	
	TFile* filePi0Corr = new TFile(nameFileData.Data());
	TDirectory*  directoryPi0Corr = 		(TDirectory*)filePi0Corr->Get(Form("CorrPi0_%s",  cutSelection.Data())); 	

	TH2F*	histoCorrPi0_InvMass_Pt =	(TH2F*) directoryPi0Corr->Get("ESD_CorrPi0_InvMass_Pt");
	TH2F*	histoCorrPi0SideBand_InvMass_Pt =	(TH2F*) directoryPi0Corr->Get("ESD_CorrPi0SideBand_InvMass_Pt");
	
	TH2F*	histoCorrPi0_Phi_Eta = (TH2F*)directoryPi0Corr->Get("ESD_CorrPi0_Phi_Eta");
	Float_t numberOfTriggerPi0s = histoCorrPi0_Phi_Eta->Integral();
	histoCorrPi0_Phi_Eta->Scale(1./numberOfTriggerPi0s);
 	cout << "number of trigger pi0s: \t " << numberOfTriggerPi0s << endl;
 	ConvGammaRebinWithBinCorrection2D(histoCorrPi0_Phi_Eta, 1, 1, 3);
	PlotStandard2D( histoCorrPi0_Phi_Eta , Form("%s/%s_Pi0Corr_PhiCh_EtaCh.%s",outputDirectory.Data(),optData.Data(),suffix.Data()), "", "#phi (rad)", "#eta", "#frac{dN_{#pi^{0},trig}}{N_{#pi^{0}, trig} d#eta d#phi}",  kTRUE, -TMath::Pi(), TMath::Pi(),kTRUE, -0.9, 0.9, kTRUE,  9e-2, histoCorrPi0_Phi_Eta->GetMaximum(), 0,0, 1, floatLocationRightUp2DXY,1000,880,rightMargin, leftMargin,bottomMargin,topMargin, "Perf","SURF7");
// 	delete histoCorrPi0_Phi_Eta;

	TH2F*	histoCorrPi0SideBand_Phi_Eta = (TH2F*)directoryPi0Corr->Get("ESD_CorrPi0SideBand_Phi_Eta");
	Float_t numberOfTriggerPi0SideBands = histoCorrPi0SideBand_Phi_Eta->Integral();
	cout << "number of trigger pi0s in SideBand: \t " << numberOfTriggerPi0SideBands << endl;
	histoCorrPi0SideBand_Phi_Eta->Scale(1./numberOfTriggerPi0s);
 	ConvGammaRebinWithBinCorrection2D(histoCorrPi0SideBand_Phi_Eta, 1, 1, 3);
	PlotStandard2D( histoCorrPi0SideBand_Phi_Eta , Form("%s/%s_Pi0SideBandCorr_PhiCh_EtaCh.%s",outputDirectory.Data(),optData.Data(),suffix.Data()), "", "#phi (rad)", "#eta", "#frac{dN_{#pi^{0},trig}}{N_{#pi^{0}, trig} d#eta d#phi}",  kTRUE, -TMath::Pi(), TMath::Pi(),kTRUE, -0.9, 0.9, kTRUE,  9e-4, histoCorrPi0SideBand_Phi_Eta->GetMaximum(), 0,0, 1, floatLocationRightUp2DXY,1000,880,rightMargin, leftMargin,bottomMargin,topMargin, "Perf","SURF7");
	
	TH2F*	histoCorrPi0_Phi_Pt = (TH2F*)directoryPi0Corr->Get("ESD_CorrPi0_Phi_Pt");
	histoCorrPi0_Phi_Pt->Scale(1./numberOfTriggerPi0s);
 	ConvGammaRebinWithBinCorrection2D(histoCorrPi0_Phi_Pt, 1, 1, 3);
	PlotStandard2D( histoCorrPi0_Phi_Pt , Form("%s/%s_Pi0Corr_Phi_Pt.%s",outputDirectory.Data(),optData.Data(),suffix.Data()), "", "#phi (rad)", "p_{t} (GeV/c)", "#frac{dN_{#pi^{0},trig}}{N_{#pi^{0}, trig} d#phi dp_{t}}",  kTRUE, -TMath::Pi(), TMath::Pi(),kTRUE, 0.5, 50., kTRUE,  9e-4, histoCorrPi0_Phi_Pt->GetMaximum(), 0,1, 1, floatLocationRightUp2DXY,1000,880,rightMargin2, leftMargin2,bottomMargin,topMargin, "Perf","COLZ");
	delete histoCorrPi0_Phi_Pt;

	TH2F*	histoCorrPi0_Eta_Pt = (TH2F*)directoryPi0Corr->Get("ESD_CorrPi0_Eta_Pt");
	histoCorrPi0_Eta_Pt->Scale(1./numberOfTriggerPi0s);
 	ConvGammaRebinWithBinCorrection2D(histoCorrPi0_Eta_Pt, 1, 1, 3);
	PlotStandard2D( histoCorrPi0_Eta_Pt , Form("%s/%s_Pi0Corr_Eta_Pt.%s",outputDirectory.Data(),optData.Data(),suffix.Data()), "", "#eta", "p_{t} (GeV/c)", "#frac{dN_{#pi^{0},trig}}{N_{#pi^{0}, trig} d#phi dp_{t}}", kTRUE, -0.9, 0.9,kTRUE, 0.5, 50., kTRUE,  9e-4, histoCorrPi0_Eta_Pt->GetMaximum(), 0,1, 1, floatLocationRightUp2DXY,1000,880,rightMargin2, leftMargin2,bottomMargin,topMargin, "Perf","COLZ");
	delete histoCorrPi0_Eta_Pt;

	TH2F*	histoCorrPi0SideBand_Phi_Pt = (TH2F*)directoryPi0Corr->Get("ESD_CorrPi0SideBand_Phi_Pt");
	histoCorrPi0SideBand_Phi_Pt->Scale(1./numberOfTriggerPi0s);
 	ConvGammaRebinWithBinCorrection2D(histoCorrPi0SideBand_Phi_Pt, 1, 1, 3);
	PlotStandard2D( histoCorrPi0SideBand_Phi_Pt , Form("%s/%s_Pi0SideBandCorr_Phi_Pt.%s",outputDirectory.Data(),optData.Data(),suffix.Data()), "", "#phi (rad)", "p_{t} (GeV/c)", "#frac{dN_{#pi^{0},trig}}{N_{#pi^{0}, trig} d#phi dp_{t}}",  kTRUE, -TMath::Pi(), TMath::Pi(),kTRUE, 0.5, 50., kTRUE,  9e-4, histoCorrPi0SideBand_Phi_Pt->GetMaximum(), 0,1, 1, floatLocationRightUp2DXY,1000,880,rightMargin2, leftMargin2,bottomMargin,topMargin, "Perf","COLZ");
	delete histoCorrPi0SideBand_Phi_Pt;

	TH2F*	histoCorrPi0SideBand_Eta_Pt = (TH2F*)directoryPi0Corr->Get("ESD_CorrPi0SideBand_Eta_Pt");
	histoCorrPi0SideBand_Eta_Pt->Scale(1./numberOfTriggerPi0s);
 	ConvGammaRebinWithBinCorrection2D(histoCorrPi0SideBand_Eta_Pt, 1, 1, 3);
	PlotStandard2D( histoCorrPi0SideBand_Eta_Pt , Form("%s/%s_Pi0SideBandCorr_Eta_Pt.%s",outputDirectory.Data(),optData.Data(),suffix.Data()), "", "#eta", "p_{t} (GeV/c)", "#frac{dN_{#pi^{0},trig}}{N_{#pi^{0}, trig} d#phi dp_{t}}", kTRUE, -0.9, 0.9,kTRUE, 0.5, 50., kTRUE,  9e-4, histoCorrPi0SideBand_Eta_Pt->GetMaximum(), 0,1, 1, floatLocationRightUp2DXY,1000,880,rightMargin2, leftMargin2,bottomMargin,topMargin, "Perf","COLZ");
	delete histoCorrPi0SideBand_Eta_Pt;

 	TH2F*	histoCorrPi0_dPhiCh_dEtaCh = (TH2F*)directoryPi0Corr->Get("ESD_CorrPi0_dPhiCh_dEtaCh");
	histoCorrPi0_dPhiCh_dEtaCh->Scale(1./numberOfTriggerPi0s);
	ConvGammaRebinWithBinCorrection2D(histoCorrPi0_dPhiCh_dEtaCh, 1, 1, 3);
	PlotStandard2D( histoCorrPi0_dPhiCh_dEtaCh , Form("%s/%s_Pi0Corr_dPhiCh_dEtaCh.%s",outputDirectory.Data(),optData.Data(),suffix.Data()), "", "#Delta#phi (rad)", "#Delta#eta", "#frac{dN_{ch,ass}}{N_{#pi^{0}, trig} d#Delta#eta d#Delta#phi}", kTRUE, -TMath::Pi(), TMath::Pi(), kTRUE, -1., 1.,kTRUE,  6.e-2, histoCorrPi0_dPhiCh_dEtaCh->GetMaximum(), 0, 0,1, floatLocationRightUp2DXY,1000,880,rightMargin, leftMargin,bottomMargin,topMargin, "Perf","SURF7");
	delete histoCorrPi0_dPhiCh_dEtaCh;

	TH2F*	histoCorrPi0SideBand_dPhiCh_dEtaCh = (TH2F*)directoryPi0Corr->Get("ESD_CorrPi0SideBand_dPhiCh_dEtaCh");
	histoCorrPi0SideBand_dPhiCh_dEtaCh->Scale(1./numberOfTriggerPi0s);
	ConvGammaRebinWithBinCorrection2D(histoCorrPi0SideBand_dPhiCh_dEtaCh, 1, 1, 3);
	PlotStandard2D( histoCorrPi0SideBand_dPhiCh_dEtaCh , Form("%s/%s_Pi0SideBandCorr_dPhiCh_dEtaCh.%s",outputDirectory.Data(),optData.Data(),suffix.Data()), "", "#Delta#phi (rad)", "#Delta#eta", "#frac{dN_{ch,ass}}{N_{#pi^{0}, trig} d#Delta#eta d#Delta#phi}", kTRUE, -TMath::Pi(), TMath::Pi(), kTRUE, -1., 1.,kTRUE,  6.e-4, histoCorrPi0SideBand_dPhiCh_dEtaCh->GetMaximum(), 0, 0,1, floatLocationRightUp2DXY,1000,880,rightMargin, leftMargin,bottomMargin,topMargin, "Perf","SURF7");
	delete histoCorrPi0SideBand_dPhiCh_dEtaCh;

 	TH2F*	histoCorrPi0_dPhiCh_dEtaCh_PtA1GeV_PtT2GeV = (TH2F*)directoryPi0Corr->Get("ESD_CorrPi0_dPhiCh_dEtaCh_PtA1GeV_PtT2GeV");
	histoCorrPi0_dPhiCh_dEtaCh_PtA1GeV_PtT2GeV->Scale(1./numberOfTriggerPi0s);
 	ConvGammaRebinWithBinCorrection2D(histoCorrPi0_dPhiCh_dEtaCh_PtA1GeV_PtT2GeV, 1, 1, 3);
	PlotStandard2D( histoCorrPi0_dPhiCh_dEtaCh_PtA1GeV_PtT2GeV , Form("%s/%s_Pi0Corr_dPhiCh_dEtaCh_PtA1GeV_PtT2GeV.%s",outputDirectory.Data(),optData.Data(),suffix.Data()), "p_{t}^{A} > 1 GeV/c, p_{t}^{T} > 2 GeV/c", "#Delta#phi (rad)", "#Delta#eta","#frac{dN_{ch,ass}}{N_{#pi^{0}, trig} d#Delta#eta d#Delta#phi}", kTRUE, -TMath::Pi(), TMath::Pi(), kTRUE, -1., 1.,kTRUE,  1.e-3, histoCorrPi0_dPhiCh_dEtaCh_PtA1GeV_PtT2GeV->GetMaximum(), 0, 0, 1, floatLocationRightUp2DXY,1000,880,rightMargin, leftMargin,bottomMargin,topMargin, "Perf","SURF7","p_{t}^{A} > 1 GeV/c, p_{t}^{T} > 2 GeV/c");
	delete histoCorrPi0_dPhiCh_dEtaCh_PtA1GeV_PtT2GeV;
	
	TH2F*	histoCorrPi0_dPhiCh_dEtaCh_PtA1GeV_PtT5GeV = (TH2F*)directoryPi0Corr->Get("ESD_CorrPi0_dPhiCh_dEtaCh_PtA1GeV_PtT5GeV");
	histoCorrPi0_dPhiCh_dEtaCh_PtA1GeV_PtT5GeV->Scale(1./numberOfTriggerPi0s);
 	ConvGammaRebinWithBinCorrection2D(histoCorrPi0_dPhiCh_dEtaCh_PtA1GeV_PtT5GeV, 1, 1, 3);
	PlotStandard2D( histoCorrPi0_dPhiCh_dEtaCh_PtA1GeV_PtT5GeV , Form("%s/%s_Pi0Corr_dPhiCh_dEtaCh_PtA1GeV_PtT5GeV.%s",outputDirectory.Data(),optData.Data(),suffix.Data()), "p_{t}^{A} > 1 GeV/c, p_{t}^{T} > 5 GeV/c", "#Delta#phi (rad)", "#Delta#eta", "#frac{dN_{ch,ass}}{N_{#pi^{0}, trig} d#Delta#eta d#Delta#phi}", kTRUE, -TMath::Pi(), TMath::Pi(), kTRUE, -1., 1.,kTRUE,  1.e-5, histoCorrPi0_dPhiCh_dEtaCh_PtA1GeV_PtT5GeV->GetMaximum(), 0, 0, 1, floatLocationRightUp2DXY,1000,880,rightMargin, leftMargin,bottomMargin,topMargin, "Perf","SURF7","p_{t}^{A} > 1 GeV/c, p_{t}^{T} > 5 GeV/c");
	delete histoCorrPi0_dPhiCh_dEtaCh_PtA1GeV_PtT5GeV;
	
	TH2F*	histoCorrPi0_dPhiGa_dEtaGa =(TH2F*)directoryPi0Corr->Get("ESD_CorrPi0_dPhiGa_dEtaGa");
	
	histoCorrPi0_dPhiGa_dEtaGa->Scale(1./numberOfTriggerPi0s);
	ConvGammaRebinWithBinCorrection2D(histoCorrPi0_dPhiGa_dEtaGa, 1, 1, 3);
	PlotStandard2D( histoCorrPi0_dPhiGa_dEtaGa , Form("%s/%s_Pi0Corr_dPhiGa_dEtaGa.%s",outputDirectory.Data(),optData.Data(),suffix.Data()), "", "#Delta#phi (rad)", "#Delta#eta", "#frac{dN_{#gamma,ass}}{N_{#pi^{0}, trig} d#Delta#eta d#Delta#phi}", kFALSE, 0., 15., kTRUE, -1., 1.,kTRUE,  2.e-3, histoCorrPi0_dPhiGa_dEtaGa->GetMaximum(), 0, 0, 1, floatLocationRightUp2DXY,1000,880,rightMargin, leftMargin,bottomMargin,topMargin, "Perf","SURF7");
	delete histoCorrPi0_dPhiGa_dEtaGa;
	
	TH2F*	histoCorrPi0SideBand_dPhiGa_dEtaGa =(TH2F*)directoryPi0Corr->Get("ESD_CorrPi0SideBand_dPhiGa_dEtaGa");
	
	histoCorrPi0SideBand_dPhiGa_dEtaGa->Scale(1./numberOfTriggerPi0s);
	ConvGammaRebinWithBinCorrection2D(histoCorrPi0SideBand_dPhiGa_dEtaGa, 1, 1, 3);
	PlotStandard2D( histoCorrPi0SideBand_dPhiGa_dEtaGa , Form("%s/%s_Pi0SideBandCorr_dPhiGa_dEtaGa.%s",outputDirectory.Data(),optData.Data(),suffix.Data()), "", "#Delta#phi (rad)", "#Delta#eta", "#frac{dN_{#gamma,ass}}{N_{#pi^{0}, trig} d#Delta#eta d#Delta#phi}", kFALSE, 0., 15., kTRUE, -1., 1.,kTRUE,  2.e-3, histoCorrPi0SideBand_dPhiGa_dEtaGa->GetMaximum(), 0, 0, 1, floatLocationRightUp2DXY,1000,880,rightMargin, leftMargin,bottomMargin,topMargin, "Perf","SURF7");
	delete histoCorrPi0SideBand_dPhiGa_dEtaGa;

	
// 	TH2F*	histoCorrPi0_IsoCh_PtTrig = (TH2F*)directoryPi0Corr->Get("ESD_CorrPi0_IsoCh_PtTrig");
// 	TH2F*	histoCorrPi0_IsoGa_PtTrig = (TH2F*)directoryPi0Corr->Get("ESD_CorrPi0_IsoGa_PtTrig");
// 	TH2F*	histoCorrPi0_IsoMin_Pt = (TH2F*)directoryPi0Corr->Get("ESD_CorrPi0_IsoMin_Pt");

 	TH2F*	histoCorrPi0_IsoMin_Pt = (TH2F*)directoryPi0Corr->Get("ESD_CorrPi0_IsoMin_Pt");
	histoCorrPi0_IsoMin_Pt->Scale(1./numberOfTriggerPi0s);
	ConvGammaRebinWithBinCorrection2D(histoCorrPi0_IsoMin_Pt, 1, 1, 3);
 	PlotStandard2D( histoCorrPi0_IsoMin_Pt , Form("%s/%s_Pi0Corr_IsoMin_PtTrig.%s",outputDirectory.Data(),optData.Data(),suffix.Data()), "", "R_{min}", "p_{t}^{T} (GeV/c)", "#frac{dN_{#gamma,trig}}{N_{#gamma, trig} dR dp_{t}}", kFALSE, 0., 15., kFALSE, -1., 1.,kTRUE,  2.e-5, histoCorrPi0_IsoMin_Pt->GetMaximum(), 0,0,  1, floatLocationRightUp2DXY,1000,880,rightMargin2, leftMargin2,bottomMargin,topMargin, "Perf","Colz");

	TH3F*	histoCorrPi0_dPhiCh_PtAssoc_PtTrig = (TH3F*)directoryPi0Corr->Get("ESD_CorrPi0_dPhiCh_PtAssoc_PtTrig");
	TH2D* histo2DPi0_dPhi_PtTrig = (TH2D*)histoCorrPi0_dPhiCh_PtAssoc_PtTrig->Project3D("zx_CorrPi0PhiA");
	histoCorrPi0_dPhiCh_PtAssoc_PtTrig->GetYaxis()->SetRange(histoCorrPi0_dPhiCh_PtAssoc_PtTrig->GetYaxis()->FindBin(1.),histoCorrPi0_dPhiCh_PtAssoc_PtTrig->GetYaxis()->FindBin(50.));
	TH2D* histo2DPi0_dPhi_PtTrig_minPtAss05 = (TH2D*)histoCorrPi0_dPhiCh_PtAssoc_PtTrig->Project3D("zx_CorrPi0PhiB");
	histoCorrPi0_dPhiCh_PtAssoc_PtTrig->GetYaxis()->SetRange(histoCorrPi0_dPhiCh_PtAssoc_PtTrig->GetYaxis()->FindBin(2.),histoCorrPi0_dPhiCh_PtAssoc_PtTrig->GetYaxis()->FindBin(50.));
	TH2D* histo2DPi0_dPhi_PtTrig_minPtAss1 = (TH2D*)histoCorrPi0_dPhiCh_PtAssoc_PtTrig->Project3D("zx_CorrPi0PhiC");
 	delete histoCorrPi0_dPhiCh_PtAssoc_PtTrig;
	
	TH3F*	histoCorrPi0_dEtaCh_PtAssoc_PtTrig = (TH3F*)directoryPi0Corr->Get("ESD_CorrPi0_dEtaCh_PtAssoc_PtTrig");
	TH2D* histo2DPi0_dEta_PtTrig = (TH2D*)histoCorrPi0_dEtaCh_PtAssoc_PtTrig->Project3D("zx_CorrPi0EtaA");
	histoCorrPi0_dEtaCh_PtAssoc_PtTrig->GetYaxis()->SetRange(histoCorrPi0_dEtaCh_PtAssoc_PtTrig->GetYaxis()->FindBin(1.),histoCorrPi0_dEtaCh_PtAssoc_PtTrig->GetYaxis()->FindBin(50.));
	TH2D* histo2DPi0_dEta_PtTrig_minPtAss05 = (TH2D*)histoCorrPi0_dEtaCh_PtAssoc_PtTrig->Project3D("zx_CorrPi0EtaB");
	histoCorrPi0_dEtaCh_PtAssoc_PtTrig->GetYaxis()->SetRange(histoCorrPi0_dEtaCh_PtAssoc_PtTrig->GetYaxis()->FindBin(2.),histoCorrPi0_dEtaCh_PtAssoc_PtTrig->GetYaxis()->FindBin(50.));
	TH2D* histo2DPi0_dEta_PtTrig_minPtAss1 = (TH2D*)histoCorrPi0_dEtaCh_PtAssoc_PtTrig->Project3D("zx_CorrPi0EtaC");
 	delete histoCorrPi0_dEtaCh_PtAssoc_PtTrig;

	TH3F*	histoCorrPi0_dPhiGa_PtAssoc_PtTrig = (TH3F*)directoryPi0Corr->Get("ESD_CorrPi0_dPhiGa_PtAssoc_PtTrig");
	TH2D* histo2DPi0_dPhiGa_PtTrig = (TH2D*)histoCorrPi0_dPhiGa_PtAssoc_PtTrig->Project3D("zx_CorrPi0PhiGaA");
	histoCorrPi0_dPhiGa_PtAssoc_PtTrig->GetYaxis()->SetRange(histoCorrPi0_dPhiGa_PtAssoc_PtTrig->GetYaxis()->FindBin(1.),histoCorrPi0_dPhiGa_PtAssoc_PtTrig->GetYaxis()->FindBin(50.));
	TH2D* histo2DPi0_dPhiGa_PtTrig_minPtAss05 = (TH2D*)histoCorrPi0_dPhiGa_PtAssoc_PtTrig->Project3D("zx_CorrPi0PhiGaB");
	histoCorrPi0_dPhiGa_PtAssoc_PtTrig->GetYaxis()->SetRange(histoCorrPi0_dPhiGa_PtAssoc_PtTrig->GetYaxis()->FindBin(2.),histoCorrPi0_dPhiGa_PtAssoc_PtTrig->GetYaxis()->FindBin(50.));
	TH2D* histo2DPi0_dPhiGa_PtTrig_minPtAss1 = (TH2D*)histoCorrPi0_dPhiGa_PtAssoc_PtTrig->Project3D("zx_CorrPi0PhiGaC");
 	delete histoCorrPi0_dPhiGa_PtAssoc_PtTrig;

	TH3F*	histoCorrPi0_dEtaGa_PtAssoc_PtTrig = (TH3F*)directoryPi0Corr->Get("ESD_CorrPi0_dEtaGa_PtAssoc_PtTrig");
	TH2D* histo2DPi0_dEtaGa_PtTrig = (TH2D*)histoCorrPi0_dEtaGa_PtAssoc_PtTrig->Project3D("zx_CorrPi0EtaGaA");
	histoCorrPi0_dEtaGa_PtAssoc_PtTrig->GetYaxis()->SetRange(histoCorrPi0_dEtaGa_PtAssoc_PtTrig->GetYaxis()->FindBin(1.),histoCorrPi0_dEtaGa_PtAssoc_PtTrig->GetYaxis()->FindBin(50.));
	TH2D* histo2DPi0_dEtaGa_PtTrig_minPtAss05 = (TH2D*)histoCorrPi0_dEtaGa_PtAssoc_PtTrig->Project3D("zx_CorrPi0EtaGaB");
	histoCorrPi0_dEtaGa_PtAssoc_PtTrig->GetYaxis()->SetRange(histoCorrPi0_dEtaGa_PtAssoc_PtTrig->GetYaxis()->FindBin(2.),histoCorrPi0_dEtaGa_PtAssoc_PtTrig->GetYaxis()->FindBin(50.));
	TH2D* histo2DPi0_dEtaGa_PtTrig_minPtAss1 = (TH2D*)histoCorrPi0_dEtaGa_PtAssoc_PtTrig->Project3D("zx_CorrPi0EtaGaC");
 	delete histoCorrPi0_dEtaGa_PtAssoc_PtTrig;

	
	TH3F*	histoCorrPi0SideBand_dPhiCh_PtAssoc_PtTrig = (TH3F*)directoryPi0Corr->Get("ESD_CorrPi0SideBand_dPhiCh_PtAssoc_PtTrig");
	TH2D* histo2DPi0SideBand_dPhi_PtTrig = (TH2D*)histoCorrPi0SideBand_dPhiCh_PtAssoc_PtTrig->Project3D("zx_CorrPi0SBPhiA");
	histoCorrPi0SideBand_dPhiCh_PtAssoc_PtTrig->GetYaxis()->SetRange(histoCorrPi0SideBand_dPhiCh_PtAssoc_PtTrig->GetYaxis()->FindBin(1.),histoCorrPi0SideBand_dPhiCh_PtAssoc_PtTrig->GetYaxis()->FindBin(50.));
	TH2D* histo2DPi0SideBand_dPhi_PtTrig_minPtAss05 = (TH2D*)histoCorrPi0SideBand_dPhiCh_PtAssoc_PtTrig->Project3D("zx_CorrPi0SBPhiB");
	histoCorrPi0SideBand_dPhiCh_PtAssoc_PtTrig->GetYaxis()->SetRange(histoCorrPi0SideBand_dPhiCh_PtAssoc_PtTrig->GetYaxis()->FindBin(2.),histoCorrPi0SideBand_dPhiCh_PtAssoc_PtTrig->GetYaxis()->FindBin(50.));
	TH2D* histo2DPi0SideBand_dPhi_PtTrig_minPtAss1 = (TH2D*)histoCorrPi0SideBand_dPhiCh_PtAssoc_PtTrig->Project3D("zx_CorrPi0SBPhiC");
 	delete histoCorrPi0SideBand_dPhiCh_PtAssoc_PtTrig;
	
	TH3F*	histoCorrPi0SideBand_dEtaCh_PtAssoc_PtTrig = (TH3F*)directoryPi0Corr->Get("ESD_CorrPi0SideBand_dEtaCh_PtAssoc_PtTrig");
	TH2D* histo2DPi0SideBand_dEta_PtTrig = (TH2D*)histoCorrPi0SideBand_dEtaCh_PtAssoc_PtTrig->Project3D("zx_CorrPi0SBEtaA");
	histoCorrPi0SideBand_dEtaCh_PtAssoc_PtTrig->GetYaxis()->SetRange(histoCorrPi0SideBand_dEtaCh_PtAssoc_PtTrig->GetYaxis()->FindBin(1.),histoCorrPi0SideBand_dEtaCh_PtAssoc_PtTrig->GetYaxis()->FindBin(50.));
	TH2D* histo2DPi0SideBand_dEta_PtTrig_minPtAss05 = (TH2D*)histoCorrPi0SideBand_dEtaCh_PtAssoc_PtTrig->Project3D("zx_CorrPi0SBEtaB");
	histoCorrPi0SideBand_dEtaCh_PtAssoc_PtTrig->GetYaxis()->SetRange(histoCorrPi0SideBand_dEtaCh_PtAssoc_PtTrig->GetYaxis()->FindBin(2.),histoCorrPi0SideBand_dEtaCh_PtAssoc_PtTrig->GetYaxis()->FindBin(50.));
	TH2D* histo2DPi0SideBand_dEta_PtTrig_minPtAss1 = (TH2D*)histoCorrPi0SideBand_dEtaCh_PtAssoc_PtTrig->Project3D("zx_CorrPi0SBEtaC");
 	delete histoCorrPi0SideBand_dEtaCh_PtAssoc_PtTrig;
	
	TH3F*	histoCorrPi0SideBand_dPhiGa_PtAssoc_PtTrig = (TH3F*)directoryPi0Corr->Get("ESD_CorrPi0SideBand_dPhiGa_PtAssoc_PtTrig");
	TH2D* histo2DPi0SideBand_dPhiGa_PtTrig = (TH2D*)histoCorrPi0SideBand_dPhiGa_PtAssoc_PtTrig->Project3D("zx_CorrPi0SBPhiGaA");
	histoCorrPi0SideBand_dPhiGa_PtAssoc_PtTrig->GetYaxis()->SetRange(histoCorrPi0SideBand_dPhiGa_PtAssoc_PtTrig->GetYaxis()->FindBin(1.),histoCorrPi0SideBand_dPhiGa_PtAssoc_PtTrig->GetYaxis()->FindBin(50.));
	TH2D* histo2DPi0SideBand_dPhiGa_PtTrig_minPtAss05 = (TH2D*)histoCorrPi0SideBand_dPhiGa_PtAssoc_PtTrig->Project3D("zx_CorrPi0SBPhiGaB");
	histoCorrPi0SideBand_dPhiGa_PtAssoc_PtTrig->GetYaxis()->SetRange(histoCorrPi0SideBand_dPhiGa_PtAssoc_PtTrig->GetYaxis()->FindBin(2.),histoCorrPi0SideBand_dPhiGa_PtAssoc_PtTrig->GetYaxis()->FindBin(50.));
	TH2D* histo2DPi0SideBand_dPhiGa_PtTrig_minPtAss1 = (TH2D*)histoCorrPi0SideBand_dPhiGa_PtAssoc_PtTrig->Project3D("zx_CorrPi0SBPhiGaC");
 	delete histoCorrPi0SideBand_dPhiGa_PtAssoc_PtTrig;
	
	TH3F*	histoCorrPi0SideBand_dEtaGa_PtAssoc_PtTrig = (TH3F*)directoryPi0Corr->Get("ESD_CorrPi0SideBand_dEtaGa_PtAssoc_PtTrig");
	TH2D* histo2DPi0SideBand_dEtaGa_PtTrig = (TH2D*)histoCorrPi0SideBand_dEtaGa_PtAssoc_PtTrig->Project3D("zx_CorrPi0SBEtaGaA");
	histoCorrPi0SideBand_dEtaGa_PtAssoc_PtTrig->GetYaxis()->SetRange(histoCorrPi0SideBand_dEtaGa_PtAssoc_PtTrig->GetYaxis()->FindBin(1.),histoCorrPi0SideBand_dEtaGa_PtAssoc_PtTrig->GetYaxis()->FindBin(50.));
	TH2D* histo2DPi0SideBand_dEtaGa_PtTrig_minPtAss05 = (TH2D*)histoCorrPi0SideBand_dEtaGa_PtAssoc_PtTrig->Project3D("zx_CorrPi0SBEtaGaB");
	histoCorrPi0SideBand_dEtaGa_PtAssoc_PtTrig->GetYaxis()->SetRange(histoCorrPi0SideBand_dEtaGa_PtAssoc_PtTrig->GetYaxis()->FindBin(2.),histoCorrPi0SideBand_dEtaGa_PtAssoc_PtTrig->GetYaxis()->FindBin(50.));
	TH2D* histo2DPi0SideBand_dEtaGa_PtTrig_minPtAss1 = (TH2D*)histoCorrPi0SideBand_dEtaGa_PtAssoc_PtTrig->Project3D("zx_CorrPi0SBEtaGaC");
 	delete histoCorrPi0SideBand_dEtaGa_PtAssoc_PtTrig;
	
	
	TH3F*	histoCorrPi0Iso_dPhiCh_PtAssoc_PtTrig = (TH3F*)directoryPi0Corr->Get("ESD_CorrPi0Iso_dPhiCh_PtAssoc_PtTrig");
	TH2D* histo2DPi0Iso_dPhi_PtTrig = (TH2D*)histoCorrPi0Iso_dPhiCh_PtAssoc_PtTrig->Project3D("zx_Pi0CorrIsoPhiA");
	histoCorrPi0Iso_dPhiCh_PtAssoc_PtTrig->GetYaxis()->SetRange(histoCorrPi0Iso_dPhiCh_PtAssoc_PtTrig->GetYaxis()->FindBin(1.),histoCorrPi0Iso_dPhiCh_PtAssoc_PtTrig->GetYaxis()->FindBin(50.));
	TH2D* histo2DPi0Iso_dPhi_PtTrig_minPtAss05 = (TH2D*)histoCorrPi0Iso_dPhiCh_PtAssoc_PtTrig->Project3D("zx_Pi0CorrIsoPhiB");
	histoCorrPi0Iso_dPhiCh_PtAssoc_PtTrig->GetYaxis()->SetRange(histoCorrPi0Iso_dPhiCh_PtAssoc_PtTrig->GetYaxis()->FindBin(2.),histoCorrPi0Iso_dPhiCh_PtAssoc_PtTrig->GetYaxis()->FindBin(50.));
	TH2D* histo2DPi0Iso_dPhi_PtTrig_minPtAss1 = (TH2D*)histoCorrPi0Iso_dPhiCh_PtAssoc_PtTrig->Project3D("zx_Pi0CorrIsoPhiC");
 	delete histoCorrPi0Iso_dPhiCh_PtAssoc_PtTrig;


	TH3F*	histoCorrPi0Iso_dEtaCh_PtAssoc_PtTrig = (TH3F*)directoryPi0Corr->Get("ESD_CorrPi0Iso_dEtaCh_PtAssoc_PtTrig");
	TH2D* histo2DPi0Iso_dEta_PtTrig = (TH2D*)histoCorrPi0Iso_dEtaCh_PtAssoc_PtTrig->Project3D("zx_Pi0CorrIsoEtaA");
	histoCorrPi0Iso_dEtaCh_PtAssoc_PtTrig->GetYaxis()->SetRange(histoCorrPi0Iso_dEtaCh_PtAssoc_PtTrig->GetYaxis()->FindBin(1.),histoCorrPi0Iso_dEtaCh_PtAssoc_PtTrig->GetYaxis()->FindBin(50.));
	TH2D* histo2DPi0Iso_dEta_PtTrig_minPtAss05 = (TH2D*)histoCorrPi0Iso_dEtaCh_PtAssoc_PtTrig->Project3D("zx_Pi0CorrIsoEtaB");
	histoCorrPi0Iso_dEtaCh_PtAssoc_PtTrig->GetYaxis()->SetRange(histoCorrPi0Iso_dEtaCh_PtAssoc_PtTrig->GetYaxis()->FindBin(2.),histoCorrPi0Iso_dEtaCh_PtAssoc_PtTrig->GetYaxis()->FindBin(50.));
	TH2D* histo2DPi0Iso_dEta_PtTrig_minPtAss1 = (TH2D*)histoCorrPi0Iso_dEtaCh_PtAssoc_PtTrig->Project3D("zx_Pi0CorrIsoEtaC");
 	delete histoCorrPi0Iso_dEtaCh_PtAssoc_PtTrig;
	
	
	TString fileNameOutput = "CorrelationOutputNew1stStep.root";
	TFile* fileCorrWrite = new TFile(fileNameOutput.Data(),"UPDATE");
	fileCorrWrite->mkdir(Form("CorrPi0_%s",  cutSelection.Data()));
	fileCorrWrite->cd(Form("CorrPi0_%s",  cutSelection.Data()));
	
	histoCorrPi0_Phi_Eta->Write(Form("ESD_%s_CorrPi0_Phi_Eta",optData.Data()),TObject::kWriteDelete);
	histoCorrPi0_InvMass_Pt->Write(Form("ESD_%s_CorrPi0_InvMass_Pt",optData.Data()),TObject::kWriteDelete);
	histo2DPi0_dEta_PtTrig->Write(Form("ESD_%s_CorrPi0_dEtaCh_PtTrig",optData.Data()),TObject::kWriteDelete);
	histo2DPi0_dEta_PtTrig_minPtAss05->Write(Form("ESD_%s_CorrPi0_dEtaCh_PtTrig_minPtAssA",optData.Data()),TObject::kWriteDelete);
	histo2DPi0_dEta_PtTrig_minPtAss1->Write(Form("ESD_%s_CorrPi0_dEtaCh_PtTrig_minPtAssB",optData.Data()),TObject::kWriteDelete);
	histo2DPi0_dEtaGa_PtTrig->Write(Form("ESD_%s_CorrPi0_dEtaGa_PtTrig",optData.Data()),TObject::kWriteDelete);
	histo2DPi0_dEtaGa_PtTrig_minPtAss05->Write(Form("ESD_%s_CorrPi0_dEtaGa_PtTrig_minPtAssA",optData.Data()),TObject::kWriteDelete);
	histo2DPi0_dEtaGa_PtTrig_minPtAss1->Write(Form("ESD_%s_CorrPi0_dEtaGa_PtTrig_minPtAssB",optData.Data()),TObject::kWriteDelete);
	
	histo2DPi0_dPhi_PtTrig->Write(Form("ESD_%s_CorrPi0_dPhiCh_PtTrig",optData.Data()),TObject::kWriteDelete);
	histo2DPi0_dPhi_PtTrig_minPtAss05->Write(Form("ESD_%s_CorrPi0_dPhiCh_PtTrig_minPtAssA",optData.Data()),TObject::kWriteDelete);
	histo2DPi0_dPhi_PtTrig_minPtAss1->Write(Form("ESD_%s_CorrPi0_dPhiCh_PtTrig_minPtAssB",optData.Data()),TObject::kWriteDelete);
	histo2DPi0_dPhiGa_PtTrig->Write(Form("ESD_%s_CorrPi0_dPhiGa_PtTrig",optData.Data()),TObject::kWriteDelete);
	histo2DPi0_dPhiGa_PtTrig_minPtAss05->Write(Form("ESD_%s_CorrPi0_dPhiGa_PtTrig_minPtAssA",optData.Data()),TObject::kWriteDelete);
	histo2DPi0_dPhiGa_PtTrig_minPtAss1->Write(Form("ESD_%s_CorrPi0_dPhiGa_PtTrig_minPtAssB",optData.Data()),TObject::kWriteDelete);
	
	histoCorrPi0SideBand_Phi_Eta->Write(Form("ESD_%s_CorrPi0SideBand_Phi_Eta",optData.Data()),TObject::kWriteDelete);
	histoCorrPi0SideBand_InvMass_Pt->Write(Form("ESD_%s_CorrPi0SideBand_InvMass_Pt",optData.Data()),TObject::kWriteDelete);
	histo2DPi0SideBand_dEta_PtTrig->Write(Form("ESD_%s_CorrPi0SideBand_dEtaCh_PtTrig",optData.Data()),TObject::kWriteDelete);
	histo2DPi0SideBand_dEta_PtTrig_minPtAss05->Write(Form("ESD_%s_CorrPi0SideBand_dEtaCh_PtTrig_minPtAssA",optData.Data()),TObject::kWriteDelete);
	histo2DPi0SideBand_dEta_PtTrig_minPtAss1->Write(Form("ESD_%s_CorrPi0SideBand_dEtaCh_PtTrig_minPtAssB",optData.Data()),TObject::kWriteDelete);
	histo2DPi0SideBand_dEtaGa_PtTrig->Write(Form("ESD_%s_CorrPi0SideBand_dEtaGa_PtTrig",optData.Data()),TObject::kWriteDelete);
	histo2DPi0SideBand_dEtaGa_PtTrig_minPtAss05->Write(Form("ESD_%s_CorrPi0SideBand_dEtaGa_PtTrig_minPtAssA",optData.Data()),TObject::kWriteDelete);
	histo2DPi0SideBand_dEtaGa_PtTrig_minPtAss1->Write(Form("ESD_%s_CorrPi0SideBand_dEtaGa_PtTrig_minPtAssB",optData.Data()),TObject::kWriteDelete);
	
	histo2DPi0SideBand_dPhi_PtTrig->Write(Form("ESD_%s_CorrPi0SideBand_dPhiCh_PtTrig",optData.Data()),TObject::kWriteDelete);
	histo2DPi0SideBand_dPhi_PtTrig_minPtAss05->Write(Form("ESD_%s_CorrPi0SideBand_dPhiCh_PtTrig_minPtAssA",optData.Data()),TObject::kWriteDelete);
	histo2DPi0SideBand_dPhi_PtTrig_minPtAss1->Write(Form("ESD_%s_CorrPi0SideBand_dPhiCh_PtTrig_minPtAssB",optData.Data()),TObject::kWriteDelete);
	histo2DPi0SideBand_dPhiGa_PtTrig->Write(Form("ESD_%s_CorrPi0SideBand_dPhiGa_PtTrig",optData.Data()),TObject::kWriteDelete);
	histo2DPi0SideBand_dPhiGa_PtTrig_minPtAss05->Write(Form("ESD_%s_CorrPi0SideBand_dPhiGa_PtTrig_minPtAssA",optData.Data()),TObject::kWriteDelete);
	histo2DPi0SideBand_dPhiGa_PtTrig_minPtAss1->Write(Form("ESD_%s_CorrPi0SideBand_dPhiGa_PtTrig_minPtAssB",optData.Data()),TObject::kWriteDelete);
	
	
	histoCorrPi0_IsoMin_Pt->Write(Form("ESD_%s_CorrPi0_IsoMin_Pt",optData.Data()),TObject::kWriteDelete);		
	histo2DPi0Iso_dEta_PtTrig->Write(Form("ESD_%s_CorrPi0Iso_dEtaCh_PtTrig",optData.Data()),TObject::kWriteDelete);
	histo2DPi0Iso_dEta_PtTrig_minPtAss05->Write(Form("ESD_%s_CorrPi0Iso_dEtaCh_PtTrig_minPtAssA",optData.Data()),TObject::kWriteDelete);
	histo2DPi0Iso_dEta_PtTrig_minPtAss1->Write(Form("ESD_%s_CorrPi0Iso_dEtaCh_PtTrig_minPtAssB",optData.Data()),TObject::kWriteDelete);
	histo2DPi0Iso_dPhi_PtTrig->Write(Form("ESD_%s_CorrPi0Iso_dPhiCh_PtTrig",optData.Data()),TObject::kWriteDelete);
	histo2DPi0Iso_dPhi_PtTrig_minPtAss05->Write(Form("ESD_%s_CorrPi0Iso_dPhiCh_PtTrig_minPtAssA",optData.Data()),TObject::kWriteDelete);
	histo2DPi0Iso_dPhi_PtTrig_minPtAss1->Write(Form("ESD_%s_CorrPi0Iso_dPhiCh_PtTrig_minPtAssB",optData.Data()),TObject::kWriteDelete);
	
	
	fileCorrWrite->Write();

	if (optData.CompareTo("MCRec") ==0){
		optData = "MCTrue" ;
		TH2F*	histoCorrTruePi0_InvMass_Pt =	(TH2F*) directoryPi0Corr->Get("ESD_CorrTruePi0_InvMass_Pt");
		TH2F*	histoCorrTruePi0SideBand_InvMass_Pt =	(TH2F*) directoryPi0Corr->Get("ESD_CorrTruePi0SideBand_InvMass_Pt");
		
		TH2F*	histoCorrTruePi0_Phi_Eta = (TH2F*)directoryPi0Corr->Get("ESD_CorrTruePi0_Phi_Eta");
		Float_t numberOfTriggerTruePi0s = histoCorrTruePi0_Phi_Eta->Integral();
		histoCorrTruePi0_Phi_Eta->Scale(1./numberOfTriggerTruePi0s);
		cout << "number of trigger pi0s: \t " << numberOfTriggerTruePi0s << endl;
		ConvGammaRebinWithBinCorrection2D(histoCorrTruePi0_Phi_Eta, 1, 1, 3);
		PlotStandard2D( histoCorrTruePi0_Phi_Eta , Form("%s/%s_Pi0Corr_PhiCh_EtaCh.%s",outputDirectory.Data(),optData.Data(),suffix.Data()), "", "#phi (rad)", "#eta", "#frac{dN_{#pi^{0},trig}}{N_{#pi^{0}, trig} d#eta d#phi}",  kTRUE, -TMath::Pi(), TMath::Pi(),kTRUE, -0.9, 0.9, kTRUE,  9e-2, histoCorrTruePi0_Phi_Eta->GetMaximum(), 0,0, 1, floatLocationRightUp2DXY,1000,880,rightMargin, leftMargin,bottomMargin,topMargin, "Perf","SURF7");
	// 	delete histoCorrPi0_Phi_Eta;

		TH2F*	histoCorrTruePi0SideBand_Phi_Eta = (TH2F*)directoryPi0Corr->Get("ESD_CorrTruePi0SideBand_Phi_Eta");
		Float_t numberOfTriggerTruePi0SideBands = histoCorrTruePi0SideBand_Phi_Eta->Integral();
		cout << "number of trigger pi0s in SideBand: \t " << numberOfTriggerTruePi0SideBands << endl;
		histoCorrTruePi0SideBand_Phi_Eta->Scale(1./numberOfTriggerTruePi0s);
		ConvGammaRebinWithBinCorrection2D(histoCorrTruePi0SideBand_Phi_Eta, 1, 1, 3);
		PlotStandard2D( histoCorrTruePi0SideBand_Phi_Eta , Form("%s/%s_Pi0SideBandCorr_PhiCh_EtaCh.%s",outputDirectory.Data(),optData.Data(),suffix.Data()), "", "#phi (rad)", "#eta", "#frac{dN_{#pi^{0},trig}}{N_{#pi^{0}, trig} d#eta d#phi}",  kTRUE, -TMath::Pi(), TMath::Pi(),kTRUE, -0.9, 0.9, kTRUE,  9e-4, histoCorrTruePi0SideBand_Phi_Eta->GetMaximum(), 0,0, 1, floatLocationRightUp2DXY,1000,880,rightMargin, leftMargin,bottomMargin,topMargin, "Perf","SURF7");
		
		TH2F*	histoCorrTruePi0_dPhiCh_dEtaCh = (TH2F*)directoryPi0Corr->Get("ESD_CorrTruePi0_dPhiCh_dEtaCh");
		histoCorrTruePi0_dPhiCh_dEtaCh->Scale(1./numberOfTriggerTruePi0s);
		ConvGammaRebinWithBinCorrection2D(histoCorrTruePi0_dPhiCh_dEtaCh, 1, 1, 3);
		PlotStandard2D( histoCorrTruePi0_dPhiCh_dEtaCh , Form("%s/%s_Pi0Corr_dPhiCh_dEtaCh.%s",outputDirectory.Data(),optData.Data(),suffix.Data()), "", "#Delta#phi (rad)", "#Delta#eta", "#frac{dN_{ch,ass}}{N_{#pi^{0}, trig} d#Delta#eta d#Delta#phi}", kTRUE, -TMath::Pi(), TMath::Pi(), kTRUE, -1., 1.,kTRUE,  6.e-2, histoCorrTruePi0_dPhiCh_dEtaCh->GetMaximum(), 0, 0,1, floatLocationRightUp2DXY,1000,880,rightMargin, leftMargin,bottomMargin,topMargin, "Perf","SURF7");
		delete histoCorrTruePi0_dPhiCh_dEtaCh;

		TH2F*	histoCorrTruePi0SideBand_dPhiCh_dEtaCh = (TH2F*)directoryPi0Corr->Get("ESD_CorrTruePi0SideBand_dPhiCh_dEtaCh");
		histoCorrTruePi0SideBand_dPhiCh_dEtaCh->Scale(1./numberOfTriggerTruePi0s);
		ConvGammaRebinWithBinCorrection2D(histoCorrTruePi0SideBand_dPhiCh_dEtaCh, 1, 1, 3);
		PlotStandard2D( histoCorrTruePi0SideBand_dPhiCh_dEtaCh , Form("%s/%s_Pi0SideBandCorr_dPhiCh_dEtaCh.%s",outputDirectory.Data(),optData.Data(),suffix.Data()), "", "#Delta#phi (rad)", "#Delta#eta", "#frac{dN_{ch,ass}}{N_{#pi^{0}, trig} d#Delta#eta d#Delta#phi}", kTRUE, -TMath::Pi(), TMath::Pi(), kTRUE, -1., 1.,kTRUE,  6.e-4, histoCorrTruePi0SideBand_dPhiCh_dEtaCh->GetMaximum(), 0, 0,1, floatLocationRightUp2DXY,1000,880,rightMargin, leftMargin,bottomMargin,topMargin, "Perf","SURF7");
		delete histoCorrTruePi0SideBand_dPhiCh_dEtaCh;

		TH2F*	histoCorrTruePi0_dPhiCh_dEtaCh_PtA1GeV_PtT2GeV = (TH2F*)directoryPi0Corr->Get("ESD_CorrTruePi0_dPhiCh_dEtaCh_PtA1GeV_PtT2GeV");
		histoCorrTruePi0_dPhiCh_dEtaCh_PtA1GeV_PtT2GeV->Scale(1./numberOfTriggerTruePi0s);
		ConvGammaRebinWithBinCorrection2D(histoCorrTruePi0_dPhiCh_dEtaCh_PtA1GeV_PtT2GeV, 1, 1, 3);
		PlotStandard2D( histoCorrTruePi0_dPhiCh_dEtaCh_PtA1GeV_PtT2GeV , Form("%s/%s_Pi0Corr_dPhiCh_dEtaCh_PtA1GeV_PtT2GeV.%s",outputDirectory.Data(),optData.Data(),suffix.Data()), "p_{t}^{A} > 1 GeV/c, p_{t}^{T} > 2 GeV/c", "#Delta#phi (rad)", "#Delta#eta","#frac{dN_{ch,ass}}{N_{#pi^{0}, trig} d#Delta#eta d#Delta#phi}", kTRUE, -TMath::Pi(), TMath::Pi(), kTRUE, -1., 1.,kTRUE,  1.e-3, histoCorrTruePi0_dPhiCh_dEtaCh_PtA1GeV_PtT2GeV->GetMaximum(), 0, 0, 1, floatLocationRightUp2DXY,1000,880,rightMargin, leftMargin,bottomMargin,topMargin, "Perf","SURF7","p_{t}^{A} > 1 GeV/c, p_{t}^{T} > 2 GeV/c");
		delete histoCorrTruePi0_dPhiCh_dEtaCh_PtA1GeV_PtT2GeV;
		
		TH2F*	histoCorrTruePi0_dPhiCh_dEtaCh_PtA1GeV_PtT5GeV = (TH2F*)directoryPi0Corr->Get("ESD_CorrTruePi0_dPhiCh_dEtaCh_PtA1GeV_PtT5GeV");
		histoCorrTruePi0_dPhiCh_dEtaCh_PtA1GeV_PtT5GeV->Scale(1./numberOfTriggerTruePi0s);
		ConvGammaRebinWithBinCorrection2D(histoCorrTruePi0_dPhiCh_dEtaCh_PtA1GeV_PtT5GeV, 1, 1, 3);
		PlotStandard2D( histoCorrTruePi0_dPhiCh_dEtaCh_PtA1GeV_PtT5GeV , Form("%s/%s_Pi0Corr_dPhiCh_dEtaCh_PtA1GeV_PtT5GeV.%s",outputDirectory.Data(),optData.Data(),suffix.Data()), "p_{t}^{A} > 1 GeV/c, p_{t}^{T} > 5 GeV/c", "#Delta#phi (rad)", "#Delta#eta", "#frac{dN_{ch,ass}}{N_{#pi^{0}, trig} d#Delta#eta d#Delta#phi}", kTRUE, -TMath::Pi(), TMath::Pi(), kTRUE, -1., 1.,kTRUE,  1.e-5, histoCorrTruePi0_dPhiCh_dEtaCh_PtA1GeV_PtT5GeV->GetMaximum(), 0, 0, 1, floatLocationRightUp2DXY,1000,880,rightMargin, leftMargin,bottomMargin,topMargin, "Perf","SURF7","p_{t}^{A} > 1 GeV/c, p_{t}^{T} > 5 GeV/c");
		delete histoCorrTruePi0_dPhiCh_dEtaCh_PtA1GeV_PtT5GeV;
		
		TH2F*	histoCorrTruePi0_dPhiGa_dEtaGa =(TH2F*)directoryPi0Corr->Get("ESD_CorrTruePi0_dPhiGa_dEtaGa");
		
		histoCorrTruePi0_dPhiGa_dEtaGa->Scale(1./numberOfTriggerTruePi0s);
		ConvGammaRebinWithBinCorrection2D(histoCorrTruePi0_dPhiGa_dEtaGa, 1, 1, 3);
		PlotStandard2D( histoCorrTruePi0_dPhiGa_dEtaGa , Form("%s/%s_Pi0Corr_dPhiGa_dEtaGa.%s",outputDirectory.Data(),optData.Data(),suffix.Data()), "", "#Delta#phi (rad)", "#Delta#eta", "#frac{dN_{#gamma,ass}}{N_{#pi^{0}, trig} d#Delta#eta d#Delta#phi}", kFALSE, 0., 15., kTRUE, -1., 1.,kTRUE,  2.e-3, histoCorrTruePi0_dPhiGa_dEtaGa->GetMaximum(), 0, 0, 1, floatLocationRightUp2DXY,1000,880,rightMargin, leftMargin,bottomMargin,topMargin, "Perf","SURF7");
		delete histoCorrTruePi0_dPhiGa_dEtaGa;
		
		TH2F*	histoCorrTruePi0SideBand_dPhiGa_dEtaGa =(TH2F*)directoryPi0Corr->Get("ESD_CorrTruePi0SideBand_dPhiGa_dEtaGa");
		
		histoCorrTruePi0SideBand_dPhiGa_dEtaGa->Scale(1./numberOfTriggerTruePi0s);
		ConvGammaRebinWithBinCorrection2D(histoCorrTruePi0SideBand_dPhiGa_dEtaGa, 1, 1, 3);
		PlotStandard2D( histoCorrTruePi0SideBand_dPhiGa_dEtaGa , Form("%s/%s_Pi0SideBandCorr_dPhiGa_dEtaGa.%s",outputDirectory.Data(),optData.Data(),suffix.Data()), "", "#Delta#phi (rad)", "#Delta#eta", "#frac{dN_{#gamma,ass}}{N_{#pi^{0}, trig} d#Delta#eta d#Delta#phi}", kFALSE, 0., 15., kTRUE, -1., 1.,kTRUE,  2.e-3, histoCorrTruePi0SideBand_dPhiGa_dEtaGa->GetMaximum(), 0, 0, 1, floatLocationRightUp2DXY,1000,880,rightMargin, leftMargin,bottomMargin,topMargin, "Perf","SURF7");
		delete histoCorrTruePi0SideBand_dPhiGa_dEtaGa;

		TH2F*	histoCorrTruePi0_IsoMin_Pt = (TH2F*)directoryPi0Corr->Get("ESD_CorrTruePi0_IsoMin_Pt");
		histoCorrTruePi0_IsoMin_Pt->Scale(1./numberOfTriggerTruePi0s);
		ConvGammaRebinWithBinCorrection2D(histoCorrTruePi0_IsoMin_Pt, 1, 1, 3);
		PlotStandard2D( histoCorrTruePi0_IsoMin_Pt , Form("%s/%s_TruePi0Corr_IsoMin_PtTrig.%s",outputDirectory.Data(),optData.Data(),suffix.Data()), "", "R_{min}", "p_{t}^{T} (GeV/c)", "#frac{dN_{#gamma,trig}}{N_{#gamma, trig} dR dp_{t}}", kFALSE, 0., 15., kFALSE, -1., 1.,kTRUE,  2.e-5, histoCorrTruePi0_IsoMin_Pt->GetMaximum(), 0,0,  1, floatLocationRightUp2DXY,1000,880,rightMargin2, leftMargin2,bottomMargin,topMargin, "Perf","Colz");

		TH3F*	histoCorrTruePi0_dPhiCh_PtAssoc_PtTrig = (TH3F*)directoryPi0Corr->Get("ESD_CorrTruePi0_dPhiCh_PtAssoc_PtTrig");
		TH2D* histo2DTruePi0_dPhi_PtTrig = (TH2D*)histoCorrTruePi0_dPhiCh_PtAssoc_PtTrig->Project3D("zx_CorrTruePi0PhiA");
		histoCorrTruePi0_dPhiCh_PtAssoc_PtTrig->GetYaxis()->SetRange(histoCorrTruePi0_dPhiCh_PtAssoc_PtTrig->GetYaxis()->FindBin(1.),histoCorrTruePi0_dPhiCh_PtAssoc_PtTrig->GetYaxis()->FindBin(50.));
		TH2D* histo2DTruePi0_dPhi_PtTrig_minPtAss05 = (TH2D*)histoCorrTruePi0_dPhiCh_PtAssoc_PtTrig->Project3D("zx_CorrTruePi0PhiB");
		histoCorrTruePi0_dPhiCh_PtAssoc_PtTrig->GetYaxis()->SetRange(histoCorrTruePi0_dPhiCh_PtAssoc_PtTrig->GetYaxis()->FindBin(2.),histoCorrTruePi0_dPhiCh_PtAssoc_PtTrig->GetYaxis()->FindBin(50.));
		TH2D* histo2DTruePi0_dPhi_PtTrig_minPtAss1 = (TH2D*)histoCorrTruePi0_dPhiCh_PtAssoc_PtTrig->Project3D("zx_CorrTruePi0PhiC");
		delete histoCorrTruePi0_dPhiCh_PtAssoc_PtTrig;
		
		TH3F*	histoCorrTruePi0_dEtaCh_PtAssoc_PtTrig = (TH3F*)directoryPi0Corr->Get("ESD_CorrTruePi0_dEtaCh_PtAssoc_PtTrig");
		TH2D* histo2DTruePi0_dEta_PtTrig = (TH2D*)histoCorrTruePi0_dEtaCh_PtAssoc_PtTrig->Project3D("zx_CorrTruePi0EtaA");
		histoCorrTruePi0_dEtaCh_PtAssoc_PtTrig->GetYaxis()->SetRange(histoCorrTruePi0_dEtaCh_PtAssoc_PtTrig->GetYaxis()->FindBin(1.),histoCorrTruePi0_dEtaCh_PtAssoc_PtTrig->GetYaxis()->FindBin(50.));
		TH2D* histo2DTruePi0_dEta_PtTrig_minPtAss05 = (TH2D*)histoCorrTruePi0_dEtaCh_PtAssoc_PtTrig->Project3D("zx_CorrTruePi0EtaB");
		histoCorrTruePi0_dEtaCh_PtAssoc_PtTrig->GetYaxis()->SetRange(histoCorrTruePi0_dEtaCh_PtAssoc_PtTrig->GetYaxis()->FindBin(2.),histoCorrTruePi0_dEtaCh_PtAssoc_PtTrig->GetYaxis()->FindBin(50.));
		TH2D* histo2DTruePi0_dEta_PtTrig_minPtAss1 = (TH2D*)histoCorrTruePi0_dEtaCh_PtAssoc_PtTrig->Project3D("zx_CorrTruePi0EtaC");
		delete histoCorrTruePi0_dEtaCh_PtAssoc_PtTrig;

		TH3F*	histoCorrTruePi0_dPhiGa_PtAssoc_PtTrig = (TH3F*)directoryPi0Corr->Get("ESD_CorrTruePi0_dPhiGa_PtAssoc_PtTrig");
		TH2D* histo2DTruePi0_dPhiGa_PtTrig = (TH2D*)histoCorrTruePi0_dPhiGa_PtAssoc_PtTrig->Project3D("zx_CorrTruePi0PhiGaA");
		histoCorrTruePi0_dPhiGa_PtAssoc_PtTrig->GetYaxis()->SetRange(histoCorrTruePi0_dPhiGa_PtAssoc_PtTrig->GetYaxis()->FindBin(1.),histoCorrTruePi0_dPhiGa_PtAssoc_PtTrig->GetYaxis()->FindBin(50.));
		TH2D* histo2DTruePi0_dPhiGa_PtTrig_minPtAss05 = (TH2D*)histoCorrTruePi0_dPhiGa_PtAssoc_PtTrig->Project3D("zx_CorrTruePi0PhiGaB");
		histoCorrTruePi0_dPhiGa_PtAssoc_PtTrig->GetYaxis()->SetRange(histoCorrTruePi0_dPhiGa_PtAssoc_PtTrig->GetYaxis()->FindBin(2.),histoCorrTruePi0_dPhiGa_PtAssoc_PtTrig->GetYaxis()->FindBin(50.));
		TH2D* histo2DTruePi0_dPhiGa_PtTrig_minPtAss1 = (TH2D*)histoCorrTruePi0_dPhiGa_PtAssoc_PtTrig->Project3D("zx_CorrTruePi0PhiGaC");
		delete histoCorrTruePi0_dPhiGa_PtAssoc_PtTrig;

		TH3F*	histoCorrTruePi0_dEtaGa_PtAssoc_PtTrig = (TH3F*)directoryPi0Corr->Get("ESD_CorrTruePi0_dEtaGa_PtAssoc_PtTrig");
		TH2D* histo2DTruePi0_dEtaGa_PtTrig = (TH2D*)histoCorrTruePi0_dEtaGa_PtAssoc_PtTrig->Project3D("zx_CorrTruePi0EtaGaA");
		histoCorrTruePi0_dEtaGa_PtAssoc_PtTrig->GetYaxis()->SetRange(histoCorrTruePi0_dEtaGa_PtAssoc_PtTrig->GetYaxis()->FindBin(1.),histoCorrTruePi0_dEtaGa_PtAssoc_PtTrig->GetYaxis()->FindBin(50.));
		TH2D* histo2DTruePi0_dEtaGa_PtTrig_minPtAss05 = (TH2D*)histoCorrTruePi0_dEtaGa_PtAssoc_PtTrig->Project3D("zx_CorrTruePi0EtaGaB");
		histoCorrTruePi0_dEtaGa_PtAssoc_PtTrig->GetYaxis()->SetRange(histoCorrTruePi0_dEtaGa_PtAssoc_PtTrig->GetYaxis()->FindBin(2.),histoCorrTruePi0_dEtaGa_PtAssoc_PtTrig->GetYaxis()->FindBin(50.));
		TH2D* histo2DTruePi0_dEtaGa_PtTrig_minPtAss1 = (TH2D*)histoCorrTruePi0_dEtaGa_PtAssoc_PtTrig->Project3D("zx_CorrTruePi0EtaGaC");
		delete histoCorrTruePi0_dEtaGa_PtAssoc_PtTrig;

		
		TH3F*	histoCorrTruePi0SideBand_dPhiCh_PtAssoc_PtTrig = (TH3F*)directoryPi0Corr->Get("ESD_CorrTruePi0SideBand_dPhiCh_PtAssoc_PtTrig");
		TH2D* histo2DTruePi0SideBand_dPhi_PtTrig = (TH2D*)histoCorrTruePi0SideBand_dPhiCh_PtAssoc_PtTrig->Project3D("zx_CorrTruePi0SBPhiA");
		histoCorrTruePi0SideBand_dPhiCh_PtAssoc_PtTrig->GetYaxis()->SetRange(histoCorrTruePi0SideBand_dPhiCh_PtAssoc_PtTrig->GetYaxis()->FindBin(1.),histoCorrTruePi0SideBand_dPhiCh_PtAssoc_PtTrig->GetYaxis()->FindBin(50.));
		TH2D* histo2DTruePi0SideBand_dPhi_PtTrig_minPtAss05 = (TH2D*)histoCorrTruePi0SideBand_dPhiCh_PtAssoc_PtTrig->Project3D("zx_CorrTruePi0SBPhiB");
		histoCorrTruePi0SideBand_dPhiCh_PtAssoc_PtTrig->GetYaxis()->SetRange(histoCorrTruePi0SideBand_dPhiCh_PtAssoc_PtTrig->GetYaxis()->FindBin(2.),histoCorrTruePi0SideBand_dPhiCh_PtAssoc_PtTrig->GetYaxis()->FindBin(50.));
		TH2D* histo2DTruePi0SideBand_dPhi_PtTrig_minPtAss1 = (TH2D*)histoCorrTruePi0SideBand_dPhiCh_PtAssoc_PtTrig->Project3D("zx_CorrTruePi0SBPhiC");
		delete histoCorrTruePi0SideBand_dPhiCh_PtAssoc_PtTrig;
		
		TH3F*	histoCorrTruePi0SideBand_dEtaCh_PtAssoc_PtTrig = (TH3F*)directoryPi0Corr->Get("ESD_CorrTruePi0SideBand_dEtaCh_PtAssoc_PtTrig");
		TH2D* histo2DTruePi0SideBand_dEta_PtTrig = (TH2D*)histoCorrTruePi0SideBand_dEtaCh_PtAssoc_PtTrig->Project3D("zx_CorrTruePi0SBEtaA");
		histoCorrTruePi0SideBand_dEtaCh_PtAssoc_PtTrig->GetYaxis()->SetRange(histoCorrTruePi0SideBand_dEtaCh_PtAssoc_PtTrig->GetYaxis()->FindBin(1.),histoCorrTruePi0SideBand_dEtaCh_PtAssoc_PtTrig->GetYaxis()->FindBin(50.));
		TH2D* histo2DTruePi0SideBand_dEta_PtTrig_minPtAss05 = (TH2D*)histoCorrTruePi0SideBand_dEtaCh_PtAssoc_PtTrig->Project3D("zx_CorrTruePi0SBEtaB");
		histoCorrTruePi0SideBand_dEtaCh_PtAssoc_PtTrig->GetYaxis()->SetRange(histoCorrTruePi0SideBand_dEtaCh_PtAssoc_PtTrig->GetYaxis()->FindBin(2.),histoCorrTruePi0SideBand_dEtaCh_PtAssoc_PtTrig->GetYaxis()->FindBin(50.));
		TH2D* histo2DTruePi0SideBand_dEta_PtTrig_minPtAss1 = (TH2D*)histoCorrTruePi0SideBand_dEtaCh_PtAssoc_PtTrig->Project3D("zx_CorrTruePi0SBEtaC");
		delete histoCorrTruePi0SideBand_dEtaCh_PtAssoc_PtTrig;
		
		TH3F*	histoCorrTruePi0SideBand_dPhiGa_PtAssoc_PtTrig = (TH3F*)directoryPi0Corr->Get("ESD_CorrTruePi0SideBand_dPhiGa_PtAssoc_PtTrig");
		TH2D* histo2DTruePi0SideBand_dPhiGa_PtTrig = (TH2D*)histoCorrTruePi0SideBand_dPhiGa_PtAssoc_PtTrig->Project3D("zx_CorrTruePi0SBPhiGaA");
		histoCorrTruePi0SideBand_dPhiGa_PtAssoc_PtTrig->GetYaxis()->SetRange(histoCorrTruePi0SideBand_dPhiGa_PtAssoc_PtTrig->GetYaxis()->FindBin(1.),histoCorrTruePi0SideBand_dPhiGa_PtAssoc_PtTrig->GetYaxis()->FindBin(50.));
		TH2D* histo2DTruePi0SideBand_dPhiGa_PtTrig_minPtAss05 = (TH2D*)histoCorrTruePi0SideBand_dPhiGa_PtAssoc_PtTrig->Project3D("zx_CorrTruePi0SBPhiGaB");
		histoCorrTruePi0SideBand_dPhiGa_PtAssoc_PtTrig->GetYaxis()->SetRange(histoCorrTruePi0SideBand_dPhiGa_PtAssoc_PtTrig->GetYaxis()->FindBin(2.),histoCorrTruePi0SideBand_dPhiGa_PtAssoc_PtTrig->GetYaxis()->FindBin(50.));
		TH2D* histo2DTruePi0SideBand_dPhiGa_PtTrig_minPtAss1 = (TH2D*)histoCorrTruePi0SideBand_dPhiGa_PtAssoc_PtTrig->Project3D("zx_CorrTruePi0SBPhiGaC");
		delete histoCorrTruePi0SideBand_dPhiGa_PtAssoc_PtTrig;
		
		TH3F*	histoCorrTruePi0SideBand_dEtaGa_PtAssoc_PtTrig = (TH3F*)directoryPi0Corr->Get("ESD_CorrTruePi0SideBand_dEtaGa_PtAssoc_PtTrig");
		TH2D* histo2DTruePi0SideBand_dEtaGa_PtTrig = (TH2D*)histoCorrTruePi0SideBand_dEtaGa_PtAssoc_PtTrig->Project3D("zx_CorrTruePi0SBEtaGaA");
		histoCorrTruePi0SideBand_dEtaGa_PtAssoc_PtTrig->GetYaxis()->SetRange(histoCorrTruePi0SideBand_dEtaGa_PtAssoc_PtTrig->GetYaxis()->FindBin(1.),histoCorrTruePi0SideBand_dEtaGa_PtAssoc_PtTrig->GetYaxis()->FindBin(50.));
		TH2D* histo2DTruePi0SideBand_dEtaGa_PtTrig_minPtAss05 = (TH2D*)histoCorrTruePi0SideBand_dEtaGa_PtAssoc_PtTrig->Project3D("zx_CorrTruePi0SBEtaGaB");
		histoCorrTruePi0SideBand_dEtaGa_PtAssoc_PtTrig->GetYaxis()->SetRange(histoCorrTruePi0SideBand_dEtaGa_PtAssoc_PtTrig->GetYaxis()->FindBin(2.),histoCorrTruePi0SideBand_dEtaGa_PtAssoc_PtTrig->GetYaxis()->FindBin(50.));
		TH2D* histo2DTruePi0SideBand_dEtaGa_PtTrig_minPtAss1 = (TH2D*)histoCorrTruePi0SideBand_dEtaGa_PtAssoc_PtTrig->Project3D("zx_CorrTruePi0SBEtaGaC");
		delete histoCorrTruePi0SideBand_dEtaGa_PtAssoc_PtTrig;
		
		
		TH3F*	histoCorrTruePi0Iso_dPhiCh_PtAssoc_PtTrig = (TH3F*)directoryPi0Corr->Get("ESD_CorrTruePi0Iso_dPhiCh_PtAssoc_PtTrig");
		TH2D* histo2DTruePi0Iso_dPhi_PtTrig = (TH2D*)histoCorrTruePi0Iso_dPhiCh_PtAssoc_PtTrig->Project3D("zx_TruePi0CorrIsoPhiA");
		histoCorrTruePi0Iso_dPhiCh_PtAssoc_PtTrig->GetYaxis()->SetRange(histoCorrTruePi0Iso_dPhiCh_PtAssoc_PtTrig->GetYaxis()->FindBin(1.),histoCorrTruePi0Iso_dPhiCh_PtAssoc_PtTrig->GetYaxis()->FindBin(50.));
		TH2D* histo2DTruePi0Iso_dPhi_PtTrig_minPtAss05 = (TH2D*)histoCorrTruePi0Iso_dPhiCh_PtAssoc_PtTrig->Project3D("zx_TruePi0CorrIsoPhiB");
		histoCorrTruePi0Iso_dPhiCh_PtAssoc_PtTrig->GetYaxis()->SetRange(histoCorrTruePi0Iso_dPhiCh_PtAssoc_PtTrig->GetYaxis()->FindBin(2.),histoCorrTruePi0Iso_dPhiCh_PtAssoc_PtTrig->GetYaxis()->FindBin(50.));
		TH2D* histo2DTruePi0Iso_dPhi_PtTrig_minPtAss1 = (TH2D*)histoCorrTruePi0Iso_dPhiCh_PtAssoc_PtTrig->Project3D("zx_TruePi0CorrIsoPhiC");
		delete histoCorrTruePi0Iso_dPhiCh_PtAssoc_PtTrig;


		TH3F*	histoCorrTruePi0Iso_dEtaCh_PtAssoc_PtTrig = (TH3F*)directoryPi0Corr->Get("ESD_CorrTruePi0Iso_dEtaCh_PtAssoc_PtTrig");
		TH2D* histo2DTruePi0Iso_dEta_PtTrig = (TH2D*)histoCorrTruePi0Iso_dEtaCh_PtAssoc_PtTrig->Project3D("zx_TruePi0CorrIsoEtaA");
		histoCorrTruePi0Iso_dEtaCh_PtAssoc_PtTrig->GetYaxis()->SetRange(histoCorrTruePi0Iso_dEtaCh_PtAssoc_PtTrig->GetYaxis()->FindBin(1.),histoCorrTruePi0Iso_dEtaCh_PtAssoc_PtTrig->GetYaxis()->FindBin(50.));
		TH2D* histo2DTruePi0Iso_dEta_PtTrig_minPtAss05 = (TH2D*)histoCorrTruePi0Iso_dEtaCh_PtAssoc_PtTrig->Project3D("zx_TruePi0CorrIsoEtaB");
		histoCorrTruePi0Iso_dEtaCh_PtAssoc_PtTrig->GetYaxis()->SetRange(histoCorrTruePi0Iso_dEtaCh_PtAssoc_PtTrig->GetYaxis()->FindBin(2.),histoCorrTruePi0Iso_dEtaCh_PtAssoc_PtTrig->GetYaxis()->FindBin(50.));
		TH2D* histo2DTruePi0Iso_dEta_PtTrig_minPtAss1 = (TH2D*)histoCorrTruePi0Iso_dEtaCh_PtAssoc_PtTrig->Project3D("zx_TruePi0CorrIsoEtaC");
		delete histoCorrTruePi0Iso_dEtaCh_PtAssoc_PtTrig;
		
		
		fileCorrWrite->cd(Form("CorrPi0_%s",  cutSelection.Data()));
		
		histoCorrTruePi0_Phi_Eta->Write(Form("ESD_%s_CorrPi0_Phi_Eta",optData.Data()),TObject::kWriteDelete);
		histoCorrTruePi0_InvMass_Pt->Write(Form("ESD_%s_CorrPi0_InvMass_Pt",optData.Data()),TObject::kWriteDelete);
		histo2DTruePi0_dEta_PtTrig->Write(Form("ESD_%s_CorrPi0_dEtaCh_PtTrig",optData.Data()),TObject::kWriteDelete);
		histo2DTruePi0_dEta_PtTrig_minPtAss05->Write(Form("ESD_%s_CorrPi0_dEtaCh_PtTrig_minPtAssA",optData.Data()),TObject::kWriteDelete);
		histo2DTruePi0_dEta_PtTrig_minPtAss1->Write(Form("ESD_%s_CorrPi0_dEtaCh_PtTrig_minPtAssB",optData.Data()),TObject::kWriteDelete);
		histo2DTruePi0_dEtaGa_PtTrig->Write(Form("ESD_%s_CorrPi0_dEtaGa_PtTrig",optData.Data()),TObject::kWriteDelete);
		histo2DTruePi0_dEtaGa_PtTrig_minPtAss05->Write(Form("ESD_%s_CorrPi0_dEtaGa_PtTrig_minPtAssA",optData.Data()),TObject::kWriteDelete);
		histo2DTruePi0_dEtaGa_PtTrig_minPtAss1->Write(Form("ESD_%s_CorrPi0_dEtaGa_PtTrig_minPtAssB",optData.Data()),TObject::kWriteDelete);
		
		histo2DTruePi0_dPhi_PtTrig->Write(Form("ESD_%s_CorrPi0_dPhiCh_PtTrig",optData.Data()),TObject::kWriteDelete);
		histo2DTruePi0_dPhi_PtTrig_minPtAss05->Write(Form("ESD_%s_CorrPi0_dPhiCh_PtTrig_minPtAssA",optData.Data()),TObject::kWriteDelete);
		histo2DTruePi0_dPhi_PtTrig_minPtAss1->Write(Form("ESD_%s_CorrPi0_dPhiCh_PtTrig_minPtAssB",optData.Data()),TObject::kWriteDelete);
		histo2DTruePi0_dPhiGa_PtTrig->Write(Form("ESD_%s_CorrPi0_dPhiGa_PtTrig",optData.Data()),TObject::kWriteDelete);
		histo2DTruePi0_dPhiGa_PtTrig_minPtAss05->Write(Form("ESD_%s_CorrPi0_dPhiGa_PtTrig_minPtAssA",optData.Data()),TObject::kWriteDelete);
		histo2DTruePi0_dPhiGa_PtTrig_minPtAss1->Write(Form("ESD_%s_CorrPi0_dPhiGa_PtTrig_minPtAssB",optData.Data()),TObject::kWriteDelete);
		
		histoCorrTruePi0SideBand_Phi_Eta->Write(Form("ESD_%s_CorrPi0SideBand_Phi_Eta",optData.Data()),TObject::kWriteDelete);
		histoCorrTruePi0SideBand_InvMass_Pt->Write(Form("ESD_%s_CorrPi0SideBand_InvMass_Pt",optData.Data()),TObject::kWriteDelete);
		histo2DTruePi0SideBand_dEta_PtTrig->Write(Form("ESD_%s_CorrPi0SideBand_dEtaCh_PtTrig",optData.Data()),TObject::kWriteDelete);
		histo2DTruePi0SideBand_dEta_PtTrig_minPtAss05->Write(Form("ESD_%s_CorrPi0SideBand_dEtaCh_PtTrig_minPtAssA",optData.Data()),TObject::kWriteDelete);
		histo2DTruePi0SideBand_dEta_PtTrig_minPtAss1->Write(Form("ESD_%s_CorrPi0SideBand_dEtaCh_PtTrig_minPtAssB",optData.Data()),TObject::kWriteDelete);
		histo2DTruePi0SideBand_dEtaGa_PtTrig->Write(Form("ESD_%s_CorrPi0SideBand_dEtaGa_PtTrig",optData.Data()),TObject::kWriteDelete);
		histo2DTruePi0SideBand_dEtaGa_PtTrig_minPtAss05->Write(Form("ESD_%s_CorrPi0SideBand_dEtaGa_PtTrig_minPtAssA",optData.Data()),TObject::kWriteDelete);
		histo2DTruePi0SideBand_dEtaGa_PtTrig_minPtAss1->Write(Form("ESD_%s_CorrPi0SideBand_dEtaGa_PtTrig_minPtAssB",optData.Data()),TObject::kWriteDelete);
		
		histo2DTruePi0SideBand_dPhi_PtTrig->Write(Form("ESD_%s_CorrPi0SideBand_dPhiCh_PtTrig",optData.Data()),TObject::kWriteDelete);
		histo2DTruePi0SideBand_dPhi_PtTrig_minPtAss05->Write(Form("ESD_%s_CorrPi0SideBand_dPhiCh_PtTrig_minPtAssA",optData.Data()),TObject::kWriteDelete);
		histo2DTruePi0SideBand_dPhi_PtTrig_minPtAss1->Write(Form("ESD_%s_CorrPi0SideBand_dPhiCh_PtTrig_minPtAssB",optData.Data()),TObject::kWriteDelete);
		histo2DTruePi0SideBand_dPhiGa_PtTrig->Write(Form("ESD_%s_CorrPi0SideBand_dPhiGa_PtTrig",optData.Data()),TObject::kWriteDelete);
		histo2DTruePi0SideBand_dPhiGa_PtTrig_minPtAss05->Write(Form("ESD_%s_CorrPi0SideBand_dPhiGa_PtTrig_minPtAssA",optData.Data()),TObject::kWriteDelete);
		histo2DTruePi0SideBand_dPhiGa_PtTrig_minPtAss1->Write(Form("ESD_%s_CorrPi0SideBand_dPhiGa_PtTrig_minPtAssB",optData.Data()),TObject::kWriteDelete);
		
		
		histoCorrTruePi0_IsoMin_Pt->Write(Form("ESD_%s_CorrPi0_IsoMin_Pt",optData.Data()),TObject::kWriteDelete);		
		histo2DTruePi0Iso_dEta_PtTrig->Write(Form("ESD_%s_CorrPi0Iso_dEtaCh_PtTrig",optData.Data()),TObject::kWriteDelete);
		histo2DTruePi0Iso_dEta_PtTrig_minPtAss05->Write(Form("ESD_%s_CorrPi0Iso_dEtaCh_PtTrig_minPtAssA",optData.Data()),TObject::kWriteDelete);
		histo2DTruePi0Iso_dEta_PtTrig_minPtAss1->Write(Form("ESD_%s_CorrPi0Iso_dEtaCh_PtTrig_minPtAssB",optData.Data()),TObject::kWriteDelete);
		histo2DTruePi0Iso_dPhi_PtTrig->Write(Form("ESD_%s_CorrPi0Iso_dPhiCh_PtTrig",optData.Data()),TObject::kWriteDelete);
		histo2DTruePi0Iso_dPhi_PtTrig_minPtAss05->Write(Form("ESD_%s_CorrPi0Iso_dPhiCh_PtTrig_minPtAssA",optData.Data()),TObject::kWriteDelete);
		histo2DTruePi0Iso_dPhi_PtTrig_minPtAss1->Write(Form("ESD_%s_CorrPi0Iso_dPhiCh_PtTrig_minPtAssB",optData.Data()),TObject::kWriteDelete);
		
		
		fileCorrWrite->Write();
		fileCorrWrite->Close();
	}
}