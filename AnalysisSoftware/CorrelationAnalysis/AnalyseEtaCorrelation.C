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

void AnalyseEtaCorrelation(TString nameFileData = "GammaConvCorr_Data.root", TString cutSelection = "001023", TString suffix ="eps", TString optData = "Data", TString optEnergy = "7TeV", TString optMCGenerator = ""){
		
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
	outputDirectory =	 	Form("%s/%s/EtaCorrelation",cutSelection.Data(),suffix.Data());
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
	
	TFile* fileEtaCorr = new TFile(nameFileData.Data());
	TDirectory*  directoryEtaCorr = 		(TDirectory*)fileEtaCorr->Get(Form("CorrEta_%s",  cutSelection.Data())); 	

	TH2F*	histoCorrEta_InvMass_Pt =	(TH2F*) directoryEtaCorr->Get("ESD_CorrEta_InvMass_Pt");
	TH2F*	histoCorrEtaSideBand_InvMass_Pt =	(TH2F*) directoryEtaCorr->Get("ESD_CorrEtaSideBand_InvMass_Pt");
	
	TH2F*	histoCorrEta_Phi_Eta = (TH2F*)directoryEtaCorr->Get("ESD_CorrEta_Phi_Eta");
	Float_t numberOfTriggerEtas = histoCorrEta_Phi_Eta->Integral();
	histoCorrEta_Phi_Eta->Scale(1./numberOfTriggerEtas);
 	cout << "number of trigger etas: \t " << numberOfTriggerEtas << endl;
 	ConvGammaRebinWithBinCorrection2D(histoCorrEta_Phi_Eta, 1, 1, 3);
	PlotStandard2D( histoCorrEta_Phi_Eta , Form("%s/%s_EtaCorr_PhiCh_EtaCh.%s",outputDirectory.Data(),optData.Data(),suffix.Data()), "", "#phi (rad)", "#eta", "#frac{dN_{#eta,trig}}{N_{#eta, trig} d#eta d#phi}",  kTRUE, -TMath::Pi(), TMath::Pi(),kTRUE, -0.9, 0.9, kTRUE,  9e-2, histoCorrEta_Phi_Eta->GetMaximum(), 0,0, 1, floatLocationRightUp2DXY,1000,880,rightMargin, leftMargin,bottomMargin,topMargin, "Perf","SURF7");
// 	delete histoCorrEta_Phi_Eta;

	TH2F*	histoCorrEtaSideBand_Phi_Eta = (TH2F*)directoryEtaCorr->Get("ESD_CorrEtaSideBand_Phi_Eta");
	Float_t numberOfTriggerEtaSideBands = histoCorrEtaSideBand_Phi_Eta->Integral();
	cout << "number of trigger etas in SideBand: \t " << numberOfTriggerEtaSideBands << endl;
	histoCorrEtaSideBand_Phi_Eta->Scale(1./numberOfTriggerEtas);
 	ConvGammaRebinWithBinCorrection2D(histoCorrEtaSideBand_Phi_Eta, 1, 1, 3);
	PlotStandard2D( histoCorrEtaSideBand_Phi_Eta , Form("%s/%s_EtaSideBandCorr_PhiCh_EtaCh.%s",outputDirectory.Data(),optData.Data(),suffix.Data()), "", "#phi (rad)", "#eta", "#frac{dN_{#eta,trig}}{N_{#eta, trig} d#Delta#eta d#Delta#phi}",  kTRUE, -TMath::Pi(), TMath::Pi(),kTRUE, -0.9, 0.9, kTRUE,  9e-4, histoCorrEtaSideBand_Phi_Eta->GetMaximum(), 0,0, 1, floatLocationRightUp2DXY,1000,880,rightMargin, leftMargin,bottomMargin,topMargin, "Perf","SURF7");
	
	TH2F*	histoCorrEta_Phi_Pt = (TH2F*)directoryEtaCorr->Get("ESD_CorrEta_Phi_Pt");
	histoCorrEta_Phi_Pt->Scale(1./numberOfTriggerEtas);
 	ConvGammaRebinWithBinCorrection2D(histoCorrEta_Phi_Pt, 1, 1, 3);
	PlotStandard2D( histoCorrEta_Phi_Pt , Form("%s/%s_EtaCorr_Phi_Pt.%s",outputDirectory.Data(),optData.Data(),suffix.Data()), "", "#phi (rad)", "p_{t} (GeV/c)", "#frac{dN_{#eta,trig}}{N_{#eta, trig} d#Delta#phi dp_{t}}",  kTRUE, -TMath::Pi(), TMath::Pi(),kTRUE, 0.5, 50., kTRUE,  9e-4, histoCorrEta_Phi_Pt->GetMaximum(), 0,1, 1, floatLocationRightUp2DXY,1000,880,rightMargin2, leftMargin2,bottomMargin,topMargin, "Perf","COLZ");
	delete histoCorrEta_Phi_Pt;

	TH2F*	histoCorrEta_Eta_Pt = (TH2F*)directoryEtaCorr->Get("ESD_CorrEta_Eta_Pt");
	histoCorrEta_Eta_Pt->Scale(1./numberOfTriggerEtas);
 	ConvGammaRebinWithBinCorrection2D(histoCorrEta_Eta_Pt, 1, 1, 3);
	PlotStandard2D( histoCorrEta_Eta_Pt , Form("%s/%s_EtaCorr_Eta_Pt.%s",outputDirectory.Data(),optData.Data(),suffix.Data()), "", "#eta", "p_{t} (GeV/c)", "#frac{dN_{#eta,trig}}{N_{#eta, trig} d#Delta#phi dp_{t}}", kTRUE, -0.9, 0.9,kTRUE, 0.5, 50., kTRUE,  9e-4, histoCorrEta_Eta_Pt->GetMaximum(), 0,1, 1, floatLocationRightUp2DXY,1000,880,rightMargin2, leftMargin2,bottomMargin,topMargin, "Perf","COLZ");
	delete histoCorrEta_Eta_Pt;

	TH2F*	histoCorrEtaSideBand_Phi_Pt = (TH2F*)directoryEtaCorr->Get("ESD_CorrEtaSideBand_Phi_Pt");
	histoCorrEtaSideBand_Phi_Pt->Scale(1./numberOfTriggerEtas);
 	ConvGammaRebinWithBinCorrection2D(histoCorrEtaSideBand_Phi_Pt, 1, 1, 3);
	PlotStandard2D( histoCorrEtaSideBand_Phi_Pt , Form("%s/%s_EtaSideBandCorr_Phi_Pt.%s",outputDirectory.Data(),optData.Data(),suffix.Data()), "", "#phi (rad)", "p_{t} (GeV/c)", "#frac{dN_{#eta,trig}}{N_{#eta, trig} d#Delta#phi dp_{t}}",  kTRUE, -TMath::Pi(), TMath::Pi(),kTRUE, 0.5, 50., kTRUE,  9e-4, histoCorrEtaSideBand_Phi_Pt->GetMaximum(), 0,1, 1, floatLocationRightUp2DXY,1000,880,rightMargin2, leftMargin2,bottomMargin,topMargin, "Perf","COLZ");
	delete histoCorrEtaSideBand_Phi_Pt;

	TH2F*	histoCorrEtaSideBand_Eta_Pt = (TH2F*)directoryEtaCorr->Get("ESD_CorrEtaSideBand_Eta_Pt");
	histoCorrEtaSideBand_Eta_Pt->Scale(1./numberOfTriggerEtas);
 	ConvGammaRebinWithBinCorrection2D(histoCorrEtaSideBand_Eta_Pt, 1, 1, 3);
	PlotStandard2D( histoCorrEtaSideBand_Eta_Pt , Form("%s/%s_EtaSideBandCorr_Eta_Pt.%s",outputDirectory.Data(),optData.Data(),suffix.Data()), "", "#eta", "p_{t} (GeV/c)", "#frac{dN_{#eta,trig}}{N_{#eta, trig} d#Delta#phi dp_{t}}", kTRUE, -0.9, 0.9,kTRUE, 0.5, 50., kTRUE,  9e-4, histoCorrEtaSideBand_Eta_Pt->GetMaximum(), 0,1, 1, floatLocationRightUp2DXY,1000,880,rightMargin2, leftMargin2,bottomMargin,topMargin, "Perf","COLZ");
	delete histoCorrEtaSideBand_Eta_Pt;

 	TH2F*	histoCorrEta_dPhiCh_dEtaCh = (TH2F*)directoryEtaCorr->Get("ESD_CorrEta_dPhiCh_dEtaCh");
	histoCorrEta_dPhiCh_dEtaCh->Scale(1./numberOfTriggerEtas);
	ConvGammaRebinWithBinCorrection2D(histoCorrEta_dPhiCh_dEtaCh, 1, 1, 3);
	PlotStandard2D( histoCorrEta_dPhiCh_dEtaCh , Form("%s/%s_EtaCorr_dPhiCh_dEtaCh.%s",outputDirectory.Data(),optData.Data(),suffix.Data()), "", "d#Delta#phi (rad)", "d#Delta#eta", "#frac{dN_{ch,ass}}{N_{#eta, trig} d#Delta#eta d#Delta#phi}", kTRUE, -TMath::Pi(), TMath::Pi(), kTRUE, -1., 1.,kTRUE,  6.e-2, histoCorrEta_dPhiCh_dEtaCh->GetMaximum(), 0, 0,1, floatLocationRightUp2DXY,1000,880,rightMargin, leftMargin,bottomMargin,topMargin, "Perf","SURF7");
	delete histoCorrEta_dPhiCh_dEtaCh;

	TH2F*	histoCorrEtaSideBand_dPhiCh_dEtaCh = (TH2F*)directoryEtaCorr->Get("ESD_CorrEtaSideBand_dPhiCh_dEtaCh");
	histoCorrEtaSideBand_dPhiCh_dEtaCh->Scale(1./numberOfTriggerEtas);
	ConvGammaRebinWithBinCorrection2D(histoCorrEtaSideBand_dPhiCh_dEtaCh, 1, 1, 3);
	PlotStandard2D( histoCorrEtaSideBand_dPhiCh_dEtaCh , Form("%s/%s_EtaSideBandCorr_dPhiCh_dEtaCh.%s",outputDirectory.Data(),optData.Data(),suffix.Data()), "", "d#Delta#phi (rad)", "d#Delta#eta", "#frac{dN_{ch,ass}}{N_{#eta, trig} d#Delta#eta d#Delta#phi}", kTRUE, -TMath::Pi(), TMath::Pi(), kTRUE, -1., 1.,kTRUE,  6.e-2, histoCorrEtaSideBand_dPhiCh_dEtaCh->GetMaximum(), 0, 0,1, floatLocationRightUp2DXY,1000,880,rightMargin, leftMargin,bottomMargin,topMargin, "Perf","SURF7");
	delete histoCorrEtaSideBand_dPhiCh_dEtaCh;

 	TH2F*	histoCorrEta_dPhiCh_dEtaCh_PtA1GeV_PtT2GeV = (TH2F*)directoryEtaCorr->Get("ESD_CorrEta_dPhiCh_dEtaCh_PtA1GeV_PtT2GeV");
	histoCorrEta_dPhiCh_dEtaCh_PtA1GeV_PtT2GeV->Scale(1./numberOfTriggerEtas);
 	ConvGammaRebinWithBinCorrection2D(histoCorrEta_dPhiCh_dEtaCh_PtA1GeV_PtT2GeV, 1, 1, 3);
	PlotStandard2D( histoCorrEta_dPhiCh_dEtaCh_PtA1GeV_PtT2GeV , Form("%s/%s_EtaCorr_dPhiCh_dEtaCh_PtA1GeV_PtT2GeV.%s",outputDirectory.Data(),optData.Data(),suffix.Data()), "p_{t}^{A} > 1 GeV/c, p_{t}^{T} > 2 GeV/c", "d#Delta#phi (rad)", "d#Delta#eta","#frac{dN_{ch,ass}}{N_{#eta, trig} d#Delta#eta d#Delta#phi}", kTRUE, -TMath::Pi(), TMath::Pi(), kTRUE, -1., 1.,kTRUE,  1.e-3, histoCorrEta_dPhiCh_dEtaCh_PtA1GeV_PtT2GeV->GetMaximum(), 0, 0, 1, floatLocationRightUp2DXY,1000,880,rightMargin, leftMargin,bottomMargin,topMargin, "Perf","SURF7","p_{t}^{A} > 1 GeV/c, p_{t}^{T} > 2 GeV/c");
	delete histoCorrEta_dPhiCh_dEtaCh_PtA1GeV_PtT2GeV;
	
	TH2F*	histoCorrEta_dPhiCh_dEtaCh_PtA1GeV_PtT5GeV = (TH2F*)directoryEtaCorr->Get("ESD_CorrEta_dPhiCh_dEtaCh_PtA1GeV_PtT5GeV");
	histoCorrEta_dPhiCh_dEtaCh_PtA1GeV_PtT5GeV->Scale(1./numberOfTriggerEtas);
 	ConvGammaRebinWithBinCorrection2D(histoCorrEta_dPhiCh_dEtaCh_PtA1GeV_PtT5GeV, 1, 1, 3);
	PlotStandard2D( histoCorrEta_dPhiCh_dEtaCh_PtA1GeV_PtT5GeV , Form("%s/%s_EtaCorr_dPhiCh_dEtaCh_PtA1GeV_PtT5GeV.%s",outputDirectory.Data(),optData.Data(),suffix.Data()), "p_{t}^{A} > 1 GeV/c, p_{t}^{T} > 5 GeV/c", "d#Delta#phi (rad)", "d#Delta#eta", "#frac{dN_{ch,ass}}{N_{#eta, trig} d#Delta#eta d#Delta#phi}", kTRUE, -TMath::Pi(), TMath::Pi(), kTRUE, -1., 1.,kTRUE,  1.e-5, histoCorrEta_dPhiCh_dEtaCh_PtA1GeV_PtT5GeV->GetMaximum(), 0, 0, 1, floatLocationRightUp2DXY,1000,880,rightMargin, leftMargin,bottomMargin,topMargin, "Perf","SURF7","p_{t}^{A} > 1 GeV/c, p_{t}^{T} > 5 GeV/c");
	delete histoCorrEta_dPhiCh_dEtaCh_PtA1GeV_PtT5GeV;
	
	TH2F*	histoCorrEta_dPhiGa_dEtaGa =(TH2F*)directoryEtaCorr->Get("ESD_CorrEta_dPhiGa_dEtaGa");
	
	histoCorrEta_dPhiGa_dEtaGa->Scale(1./numberOfTriggerEtas);
	ConvGammaRebinWithBinCorrection2D(histoCorrEta_dPhiGa_dEtaGa, 1, 1, 3);
	PlotStandard2D( histoCorrEta_dPhiGa_dEtaGa , Form("%s/%s_EtaCorr_dPhiGa_dEtaGa.%s",outputDirectory.Data(),optData.Data(),suffix.Data()), "", "d#Delta#phi (rad)", "d#Delta#eta", "#frac{dN_{#gamma,ass}}{N_{#eta, trig} d#Delta#eta d#Delta#phi}", kFALSE, 0., 15., kTRUE, -1., 1.,kTRUE,  2.e-3, histoCorrEta_dPhiGa_dEtaGa->GetMaximum(), 0, 0, 1, floatLocationRightUp2DXY,1000,880,rightMargin, leftMargin,bottomMargin,topMargin, "Perf","SURF7");
	delete histoCorrEta_dPhiGa_dEtaGa;
	
	TH2F*	histoCorrEtaSideBand_dPhiGa_dEtaGa =(TH2F*)directoryEtaCorr->Get("ESD_CorrEtaSideBand_dPhiGa_dEtaGa");
	
	histoCorrEtaSideBand_dPhiGa_dEtaGa->Scale(1./numberOfTriggerEtas);
	ConvGammaRebinWithBinCorrection2D(histoCorrEtaSideBand_dPhiGa_dEtaGa, 1, 1, 3);
	PlotStandard2D( histoCorrEtaSideBand_dPhiGa_dEtaGa , Form("%s/%s_EtaSideBandCorr_dPhiGa_dEtaGa.%s",outputDirectory.Data(),optData.Data(),suffix.Data()), "", "d#Delta#phi (rad)", "d#Delta#eta", "#frac{dN_{#gamma,ass}}{N_{#eta, trig} d#Delta#eta d#Delta#phi}", kFALSE, 0., 15., kTRUE, -1., 1.,kTRUE,  2.e-3, histoCorrEtaSideBand_dPhiGa_dEtaGa->GetMaximum(), 0, 0, 1, floatLocationRightUp2DXY,1000,880,rightMargin, leftMargin,bottomMargin,topMargin, "Perf","SURF7");
	delete histoCorrEtaSideBand_dPhiGa_dEtaGa;

	
// 	TH2F*	histoCorrEta_IsoCh_PtTrig = (TH2F*)directoryEtaCorr->Get("ESD_CorrEta_IsoCh_PtTrig");
// 	TH2F*	histoCorrEta_IsoGa_PtTrig = (TH2F*)directoryEtaCorr->Get("ESD_CorrEta_IsoGa_PtTrig");
// 	TH2F*	histoCorrEta_IsoMin_Pt = (TH2F*)directoryEtaCorr->Get("ESD_CorrEta_IsoMin_Pt");

 	TH2F*	histoCorrEta_IsoMin_Pt = (TH2F*)directoryEtaCorr->Get("ESD_CorrEta_IsoMin_Pt");
	histoCorrEta_IsoMin_Pt->Scale(1./numberOfTriggerEtas);
	ConvGammaRebinWithBinCorrection2D(histoCorrEta_IsoMin_Pt, 1, 1, 3);
 	PlotStandard2D( histoCorrEta_IsoMin_Pt , Form("%s/%s_EtaCorr_IsoMin_PtTrig.%s",outputDirectory.Data(),optData.Data(),suffix.Data()), "", "R_{min}", "p_{t}^{T} (GeV/c)", "#frac{dN_{#gamma,trig}}{N_{#gamma, trig} dR dp_{t}}", kFALSE, 0., 15., kFALSE, -1., 1.,kTRUE,  2.e-5, histoCorrEta_IsoMin_Pt->GetMaximum(), 0,0,  1, floatLocationRightUp2DXY,1000,880,rightMargin2, leftMargin2,bottomMargin,topMargin, "Perf","Colz");

	TH3F*	histoCorrEta_dPhiCh_PtAssoc_PtTrig = (TH3F*)directoryEtaCorr->Get("ESD_CorrEta_dPhiCh_PtAssoc_PtTrig");
	TH2D* histo2DEta_dPhi_PtTrig = (TH2D*)histoCorrEta_dPhiCh_PtAssoc_PtTrig->Project3D("zx_CorrEtaPhiA");
	histoCorrEta_dPhiCh_PtAssoc_PtTrig->GetYaxis()->SetRange(histoCorrEta_dPhiCh_PtAssoc_PtTrig->GetYaxis()->FindBin(0.5),histoCorrEta_dPhiCh_PtAssoc_PtTrig->GetYaxis()->FindBin(50.));
	TH2D* histo2DEta_dPhi_PtTrig_minPtAss05 = (TH2D*)histoCorrEta_dPhiCh_PtAssoc_PtTrig->Project3D("zx_CorrEtaPhiB");
	histoCorrEta_dPhiCh_PtAssoc_PtTrig->GetYaxis()->SetRange(histoCorrEta_dPhiCh_PtAssoc_PtTrig->GetYaxis()->FindBin(1.),histoCorrEta_dPhiCh_PtAssoc_PtTrig->GetYaxis()->FindBin(50.));
	TH2D* histo2DEta_dPhi_PtTrig_minPtAss1 = (TH2D*)histoCorrEta_dPhiCh_PtAssoc_PtTrig->Project3D("zx_CorrEtaPhiC");
 	delete histoCorrEta_dPhiCh_PtAssoc_PtTrig;
	
	TH3F*	histoCorrEta_dEtaCh_PtAssoc_PtTrig = (TH3F*)directoryEtaCorr->Get("ESD_CorrEta_dEtaCh_PtAssoc_PtTrig");
	TH2D* histo2DEta_dEta_PtTrig = (TH2D*)histoCorrEta_dEtaCh_PtAssoc_PtTrig->Project3D("zx_CorrEtaEtaA");
	histoCorrEta_dEtaCh_PtAssoc_PtTrig->GetYaxis()->SetRange(histoCorrEta_dEtaCh_PtAssoc_PtTrig->GetYaxis()->FindBin(0.5),histoCorrEta_dEtaCh_PtAssoc_PtTrig->GetYaxis()->FindBin(50.));
	TH2D* histo2DEta_dEta_PtTrig_minPtAss05 = (TH2D*)histoCorrEta_dEtaCh_PtAssoc_PtTrig->Project3D("zx_CorrEtaEtaB");
	histoCorrEta_dEtaCh_PtAssoc_PtTrig->GetYaxis()->SetRange(histoCorrEta_dEtaCh_PtAssoc_PtTrig->GetYaxis()->FindBin(1.),histoCorrEta_dEtaCh_PtAssoc_PtTrig->GetYaxis()->FindBin(50.));
	TH2D* histo2DEta_dEta_PtTrig_minPtAss1 = (TH2D*)histoCorrEta_dEtaCh_PtAssoc_PtTrig->Project3D("zx_CorrEtaEtaC");
 	delete histoCorrEta_dEtaCh_PtAssoc_PtTrig;

	TH3F*	histoCorrEta_dPhiGa_PtAssoc_PtTrig = (TH3F*)directoryEtaCorr->Get("ESD_CorrEta_dPhiGa_PtAssoc_PtTrig");
	TH2D* histo2DEta_dPhiGa_PtTrig = (TH2D*)histoCorrEta_dPhiGa_PtAssoc_PtTrig->Project3D("zx_CorrEtaPhiGaA");
	histoCorrEta_dPhiGa_PtAssoc_PtTrig->GetYaxis()->SetRange(histoCorrEta_dPhiGa_PtAssoc_PtTrig->GetYaxis()->FindBin(0.5),histoCorrEta_dPhiGa_PtAssoc_PtTrig->GetYaxis()->FindBin(50.));
	TH2D* histo2DEta_dPhiGa_PtTrig_minPtAss05 = (TH2D*)histoCorrEta_dPhiGa_PtAssoc_PtTrig->Project3D("zx_CorrEtaPhiGaB");
	histoCorrEta_dPhiGa_PtAssoc_PtTrig->GetYaxis()->SetRange(histoCorrEta_dPhiGa_PtAssoc_PtTrig->GetYaxis()->FindBin(1.),histoCorrEta_dPhiGa_PtAssoc_PtTrig->GetYaxis()->FindBin(50.));
	TH2D* histo2DEta_dPhiGa_PtTrig_minPtAss1 = (TH2D*)histoCorrEta_dPhiGa_PtAssoc_PtTrig->Project3D("zx_CorrEtaPhiGaC");
 	delete histoCorrEta_dPhiGa_PtAssoc_PtTrig;

	TH3F*	histoCorrEta_dEtaGa_PtAssoc_PtTrig = (TH3F*)directoryEtaCorr->Get("ESD_CorrEta_dEtaGa_PtAssoc_PtTrig");
	TH2D* histo2DEta_dEtaGa_PtTrig = (TH2D*)histoCorrEta_dEtaGa_PtAssoc_PtTrig->Project3D("zx_CorrEtaEtaGaA");
	histoCorrEta_dEtaGa_PtAssoc_PtTrig->GetYaxis()->SetRange(histoCorrEta_dEtaGa_PtAssoc_PtTrig->GetYaxis()->FindBin(0.5),histoCorrEta_dEtaGa_PtAssoc_PtTrig->GetYaxis()->FindBin(50.));
	TH2D* histo2DEta_dEtaGa_PtTrig_minPtAss05 = (TH2D*)histoCorrEta_dEtaGa_PtAssoc_PtTrig->Project3D("zx_CorrEtaEtaGaB");
	histoCorrEta_dEtaGa_PtAssoc_PtTrig->GetYaxis()->SetRange(histoCorrEta_dEtaGa_PtAssoc_PtTrig->GetYaxis()->FindBin(1.),histoCorrEta_dEtaGa_PtAssoc_PtTrig->GetYaxis()->FindBin(50.));
	TH2D* histo2DEta_dEtaGa_PtTrig_minPtAss1 = (TH2D*)histoCorrEta_dEtaGa_PtAssoc_PtTrig->Project3D("zx_CorrEtaEtaGaC");
 	delete histoCorrEta_dEtaGa_PtAssoc_PtTrig;

	
	TH3F*	histoCorrEtaSideBand_dPhiCh_PtAssoc_PtTrig = (TH3F*)directoryEtaCorr->Get("ESD_CorrEtaSideBand_dPhiCh_PtAssoc_PtTrig");
	TH2D* histo2DEtaSideBand_dPhi_PtTrig = (TH2D*)histoCorrEtaSideBand_dPhiCh_PtAssoc_PtTrig->Project3D("zx_CorrEtaSBPhiA");
	histoCorrEtaSideBand_dPhiCh_PtAssoc_PtTrig->GetYaxis()->SetRange(histoCorrEtaSideBand_dPhiCh_PtAssoc_PtTrig->GetYaxis()->FindBin(0.5),histoCorrEtaSideBand_dPhiCh_PtAssoc_PtTrig->GetYaxis()->FindBin(50.));
	TH2D* histo2DEtaSideBand_dPhi_PtTrig_minPtAss05 = (TH2D*)histoCorrEtaSideBand_dPhiCh_PtAssoc_PtTrig->Project3D("zx_CorrEtaSBPhiB");
	histoCorrEtaSideBand_dPhiCh_PtAssoc_PtTrig->GetYaxis()->SetRange(histoCorrEtaSideBand_dPhiCh_PtAssoc_PtTrig->GetYaxis()->FindBin(1.),histoCorrEtaSideBand_dPhiCh_PtAssoc_PtTrig->GetYaxis()->FindBin(50.));
	TH2D* histo2DEtaSideBand_dPhi_PtTrig_minPtAss1 = (TH2D*)histoCorrEtaSideBand_dPhiCh_PtAssoc_PtTrig->Project3D("zx_CorrEtaSBPhiC");
 	delete histoCorrEtaSideBand_dPhiCh_PtAssoc_PtTrig;
	
	TH3F*	histoCorrEtaSideBand_dEtaCh_PtAssoc_PtTrig = (TH3F*)directoryEtaCorr->Get("ESD_CorrEtaSideBand_dEtaCh_PtAssoc_PtTrig");
	TH2D* histo2DEtaSideBand_dEta_PtTrig = (TH2D*)histoCorrEtaSideBand_dEtaCh_PtAssoc_PtTrig->Project3D("zx_CorrEtaSBEtaA");
	histoCorrEtaSideBand_dEtaCh_PtAssoc_PtTrig->GetYaxis()->SetRange(histoCorrEtaSideBand_dEtaCh_PtAssoc_PtTrig->GetYaxis()->FindBin(0.5),histoCorrEtaSideBand_dEtaCh_PtAssoc_PtTrig->GetYaxis()->FindBin(50.));
	TH2D* histo2DEtaSideBand_dEta_PtTrig_minPtAss05 = (TH2D*)histoCorrEtaSideBand_dEtaCh_PtAssoc_PtTrig->Project3D("zx_CorrEtaSBEtaB");
	histoCorrEtaSideBand_dEtaCh_PtAssoc_PtTrig->GetYaxis()->SetRange(histoCorrEtaSideBand_dEtaCh_PtAssoc_PtTrig->GetYaxis()->FindBin(1.),histoCorrEtaSideBand_dEtaCh_PtAssoc_PtTrig->GetYaxis()->FindBin(50.));
	TH2D* histo2DEtaSideBand_dEta_PtTrig_minPtAss1 = (TH2D*)histoCorrEtaSideBand_dEtaCh_PtAssoc_PtTrig->Project3D("zx_CorrEtaSBEtaC");
 	delete histoCorrEtaSideBand_dEtaCh_PtAssoc_PtTrig;
	
	TH3F*	histoCorrEtaSideBand_dPhiGa_PtAssoc_PtTrig = (TH3F*)directoryEtaCorr->Get("ESD_CorrEtaSideBand_dPhiGa_PtAssoc_PtTrig");
	TH2D* histo2DEtaSideBand_dPhiGa_PtTrig = (TH2D*)histoCorrEtaSideBand_dPhiGa_PtAssoc_PtTrig->Project3D("zx_CorrEtaSBPhiGaA");
	histoCorrEtaSideBand_dPhiGa_PtAssoc_PtTrig->GetYaxis()->SetRange(histoCorrEtaSideBand_dPhiGa_PtAssoc_PtTrig->GetYaxis()->FindBin(0.5),histoCorrEtaSideBand_dPhiGa_PtAssoc_PtTrig->GetYaxis()->FindBin(50.));
	TH2D* histo2DEtaSideBand_dPhiGa_PtTrig_minPtAss05 = (TH2D*)histoCorrEtaSideBand_dPhiGa_PtAssoc_PtTrig->Project3D("zx_CorrEtaSBPhiGaB");
	histoCorrEtaSideBand_dPhiGa_PtAssoc_PtTrig->GetYaxis()->SetRange(histoCorrEtaSideBand_dPhiGa_PtAssoc_PtTrig->GetYaxis()->FindBin(1.),histoCorrEtaSideBand_dPhiGa_PtAssoc_PtTrig->GetYaxis()->FindBin(50.));
	TH2D* histo2DEtaSideBand_dPhiGa_PtTrig_minPtAss1 = (TH2D*)histoCorrEtaSideBand_dPhiGa_PtAssoc_PtTrig->Project3D("zx_CorrEtaSBPhiGaC");
 	delete histoCorrEtaSideBand_dPhiGa_PtAssoc_PtTrig;
	
	TH3F*	histoCorrEtaSideBand_dEtaGa_PtAssoc_PtTrig = (TH3F*)directoryEtaCorr->Get("ESD_CorrEtaSideBand_dEtaGa_PtAssoc_PtTrig");
	TH2D* histo2DEtaSideBand_dEtaGa_PtTrig = (TH2D*)histoCorrEtaSideBand_dEtaGa_PtAssoc_PtTrig->Project3D("zx_CorrEtaSBEtaGaA");
	histoCorrEtaSideBand_dEtaGa_PtAssoc_PtTrig->GetYaxis()->SetRange(histoCorrEtaSideBand_dEtaGa_PtAssoc_PtTrig->GetYaxis()->FindBin(0.5),histoCorrEtaSideBand_dEtaGa_PtAssoc_PtTrig->GetYaxis()->FindBin(50.));
	TH2D* histo2DEtaSideBand_dEtaGa_PtTrig_minPtAss05 = (TH2D*)histoCorrEtaSideBand_dEtaGa_PtAssoc_PtTrig->Project3D("zx_CorrEtaSBEtaGaB");
	histoCorrEtaSideBand_dEtaGa_PtAssoc_PtTrig->GetYaxis()->SetRange(histoCorrEtaSideBand_dEtaGa_PtAssoc_PtTrig->GetYaxis()->FindBin(1.),histoCorrEtaSideBand_dEtaGa_PtAssoc_PtTrig->GetYaxis()->FindBin(50.));
	TH2D* histo2DEtaSideBand_dEtaGa_PtTrig_minPtAss1 = (TH2D*)histoCorrEtaSideBand_dEtaGa_PtAssoc_PtTrig->Project3D("zx_CorrEtaSBEtaGaC");
 	delete histoCorrEtaSideBand_dEtaGa_PtAssoc_PtTrig;
	
	
	TH3F*	histoCorrEtaIso_dPhiCh_PtAssoc_PtTrig = (TH3F*)directoryEtaCorr->Get("ESD_CorrEtaIso_dPhiCh_PtAssoc_PtTrig");
	TH2D* histo2DEtaIso_dPhi_PtTrig = (TH2D*)histoCorrEtaIso_dPhiCh_PtAssoc_PtTrig->Project3D("zx_EtaCorrIsoPhiA");
	histoCorrEtaIso_dPhiCh_PtAssoc_PtTrig->GetYaxis()->SetRange(histoCorrEtaIso_dPhiCh_PtAssoc_PtTrig->GetYaxis()->FindBin(0.5),histoCorrEtaIso_dPhiCh_PtAssoc_PtTrig->GetYaxis()->FindBin(50.));
	TH2D* histo2DEtaIso_dPhi_PtTrig_minPtAss05 = (TH2D*)histoCorrEtaIso_dPhiCh_PtAssoc_PtTrig->Project3D("zx_EtaCorrIsoPhiB");
	histoCorrEtaIso_dPhiCh_PtAssoc_PtTrig->GetYaxis()->SetRange(histoCorrEtaIso_dPhiCh_PtAssoc_PtTrig->GetYaxis()->FindBin(1.),histoCorrEtaIso_dPhiCh_PtAssoc_PtTrig->GetYaxis()->FindBin(50.));
	TH2D* histo2DEtaIso_dPhi_PtTrig_minPtAss1 = (TH2D*)histoCorrEtaIso_dPhiCh_PtAssoc_PtTrig->Project3D("zx_EtaCorrIsoPhiC");
 	delete histoCorrEtaIso_dPhiCh_PtAssoc_PtTrig;


	TH3F*	histoCorrEtaIso_dEtaCh_PtAssoc_PtTrig = (TH3F*)directoryEtaCorr->Get("ESD_CorrEtaIso_dEtaCh_PtAssoc_PtTrig");
	TH2D* histo2DEtaIso_dEta_PtTrig = (TH2D*)histoCorrEtaIso_dEtaCh_PtAssoc_PtTrig->Project3D("zx_EtaCorrIsoEtaA");
	histoCorrEtaIso_dEtaCh_PtAssoc_PtTrig->GetYaxis()->SetRange(histoCorrEtaIso_dEtaCh_PtAssoc_PtTrig->GetYaxis()->FindBin(0.5),histoCorrEtaIso_dEtaCh_PtAssoc_PtTrig->GetYaxis()->FindBin(50.));
	TH2D* histo2DEtaIso_dEta_PtTrig_minPtAss05 = (TH2D*)histoCorrEtaIso_dEtaCh_PtAssoc_PtTrig->Project3D("zx_EtaCorrIsoEtaB");
	histoCorrEtaIso_dEtaCh_PtAssoc_PtTrig->GetYaxis()->SetRange(histoCorrEtaIso_dEtaCh_PtAssoc_PtTrig->GetYaxis()->FindBin(1.),histoCorrEtaIso_dEtaCh_PtAssoc_PtTrig->GetYaxis()->FindBin(50.));
	TH2D* histo2DEtaIso_dEta_PtTrig_minPtAss1 = (TH2D*)histoCorrEtaIso_dEtaCh_PtAssoc_PtTrig->Project3D("zx_EtaCorrIsoEtaC");
 	delete histoCorrEtaIso_dEtaCh_PtAssoc_PtTrig;
	
	
	TString fileNameOutput = "CorrelationOutput1stStep.root";
	TFile* fileCorrWrite = new TFile(fileNameOutput.Data(),"UPDATE");
	fileCorrWrite->mkdir(Form("CorrEta_%s",  cutSelection.Data()));
	fileCorrWrite->cd(Form("CorrEta_%s",  cutSelection.Data()));
	
	histoCorrEta_Phi_Eta->Write(Form("ESD_%s_CorrEta_Phi_Eta",optData.Data()),TObject::kWriteDelete);
	histoCorrEta_InvMass_Pt->Write(Form("ESD_%s_CorrEta_InvMass_Pt",optData.Data()),TObject::kWriteDelete);
	histo2DEta_dEta_PtTrig->Write(Form("ESD_%s_CorrEta_dEtaCh_PtTrig",optData.Data()),TObject::kWriteDelete);
	histo2DEta_dEta_PtTrig_minPtAss05->Write(Form("ESD_%s_CorrEta_dEtaCh_PtTrig_minPtAssA",optData.Data()),TObject::kWriteDelete);
	histo2DEta_dEta_PtTrig_minPtAss1->Write(Form("ESD_%s_CorrEta_dEtaCh_PtTrig_minPtAssB",optData.Data()),TObject::kWriteDelete);
	histo2DEta_dEtaGa_PtTrig->Write(Form("ESD_%s_CorrEta_dEtaGa_PtTrig",optData.Data()),TObject::kWriteDelete);
	histo2DEta_dEtaGa_PtTrig_minPtAss05->Write(Form("ESD_%s_CorrEta_dEtaGa_PtTrig_minPtAssA",optData.Data()),TObject::kWriteDelete);
	histo2DEta_dEtaGa_PtTrig_minPtAss1->Write(Form("ESD_%s_CorrEta_dEtaGa_PtTrig_minPtAssB",optData.Data()),TObject::kWriteDelete);
	
	histo2DEta_dPhi_PtTrig->Write(Form("ESD_%s_CorrEta_dPhiCh_PtTrig",optData.Data()),TObject::kWriteDelete);
	histo2DEta_dPhi_PtTrig_minPtAss05->Write(Form("ESD_%s_CorrEta_dPhiCh_PtTrig_minPtAssA",optData.Data()),TObject::kWriteDelete);
	histo2DEta_dPhi_PtTrig_minPtAss1->Write(Form("ESD_%s_CorrEta_dPhiCh_PtTrig_minPtAssB",optData.Data()),TObject::kWriteDelete);
	histo2DEta_dPhiGa_PtTrig->Write(Form("ESD_%s_CorrEta_dPhiGa_PtTrig",optData.Data()),TObject::kWriteDelete);
	histo2DEta_dPhiGa_PtTrig_minPtAss05->Write(Form("ESD_%s_CorrEta_dPhiGa_PtTrig_minPtAssA",optData.Data()),TObject::kWriteDelete);
	histo2DEta_dPhiGa_PtTrig_minPtAss1->Write(Form("ESD_%s_CorrEta_dPhiGa_PtTrig_minPtAssB",optData.Data()),TObject::kWriteDelete);
	
	histoCorrEtaSideBand_Phi_Eta->Write(Form("ESD_%s_CorrEtaSideBand_Phi_Eta",optData.Data()),TObject::kWriteDelete);
	histoCorrEtaSideBand_InvMass_Pt->Write(Form("ESD_%s_CorrEtaSideBand_InvMass_Pt",optData.Data()),TObject::kWriteDelete);
	histo2DEtaSideBand_dEta_PtTrig->Write(Form("ESD_%s_CorrEtaSideBand_dEtaCh_PtTrig",optData.Data()),TObject::kWriteDelete);
	histo2DEtaSideBand_dEta_PtTrig_minPtAss05->Write(Form("ESD_%s_CorrEtaSideBand_dEtaCh_PtTrig_minPtAssA",optData.Data()),TObject::kWriteDelete);
	histo2DEtaSideBand_dEta_PtTrig_minPtAss1->Write(Form("ESD_%s_CorrEtaSideBand_dEtaCh_PtTrig_minPtAssB",optData.Data()),TObject::kWriteDelete);
	histo2DEtaSideBand_dEtaGa_PtTrig->Write(Form("ESD_%s_CorrEtaSideBand_dEtaGa_PtTrig",optData.Data()),TObject::kWriteDelete);
	histo2DEtaSideBand_dEtaGa_PtTrig_minPtAss05->Write(Form("ESD_%s_CorrEtaSideBand_dEtaGa_PtTrig_minPtAssA",optData.Data()),TObject::kWriteDelete);
	histo2DEtaSideBand_dEtaGa_PtTrig_minPtAss1->Write(Form("ESD_%s_CorrEtaSideBand_dEtaGa_PtTrig_minPtAssB",optData.Data()),TObject::kWriteDelete);
	
	histo2DEtaSideBand_dPhi_PtTrig->Write(Form("ESD_%s_CorrEtaSideBand_dPhiCh_PtTrig",optData.Data()),TObject::kWriteDelete);
	histo2DEtaSideBand_dPhi_PtTrig_minPtAss05->Write(Form("ESD_%s_CorrEtaSideBand_dPhiCh_PtTrig_minPtAssA",optData.Data()),TObject::kWriteDelete);
	histo2DEtaSideBand_dPhi_PtTrig_minPtAss1->Write(Form("ESD_%s_CorrEtaSideBand_dPhiCh_PtTrig_minPtAssB",optData.Data()),TObject::kWriteDelete);
	histo2DEtaSideBand_dPhiGa_PtTrig->Write(Form("ESD_%s_CorrEtaSideBand_dPhiGa_PtTrig",optData.Data()),TObject::kWriteDelete);
	histo2DEtaSideBand_dPhiGa_PtTrig_minPtAss05->Write(Form("ESD_%s_CorrEtaSideBand_dPhiGa_PtTrig_minPtAssA",optData.Data()),TObject::kWriteDelete);
	histo2DEtaSideBand_dPhiGa_PtTrig_minPtAss1->Write(Form("ESD_%s_CorrEtaSideBand_dPhiGa_PtTrig_minPtAssB",optData.Data()),TObject::kWriteDelete);
	
	
	histoCorrEta_IsoMin_Pt->Write(Form("ESD_%s_CorrEta_IsoMin_Pt",optData.Data()),TObject::kWriteDelete);		
	histo2DEtaIso_dEta_PtTrig->Write(Form("ESD_%s_CorrEtaIso_dEtaCh_PtTrig",optData.Data()),TObject::kWriteDelete);
	histo2DEtaIso_dEta_PtTrig_minPtAss05->Write(Form("ESD_%s_CorrEtaIso_dEtaCh_PtTrig_minPtAssA",optData.Data()),TObject::kWriteDelete);
	histo2DEtaIso_dEta_PtTrig_minPtAss1->Write(Form("ESD_%s_CorrEtaIso_dEtaCh_PtTrig_minPtAssB",optData.Data()),TObject::kWriteDelete);
	histo2DEtaIso_dPhi_PtTrig->Write(Form("ESD_%s_CorrEtaIso_dPhiCh_PtTrig",optData.Data()),TObject::kWriteDelete);
	histo2DEtaIso_dPhi_PtTrig_minPtAss05->Write(Form("ESD_%s_CorrEtaIso_dPhiCh_PtTrig_minPtAssA",optData.Data()),TObject::kWriteDelete);
	histo2DEtaIso_dPhi_PtTrig_minPtAss1->Write(Form("ESD_%s_CorrEtaIso_dPhiCh_PtTrig_minPtAssB",optData.Data()),TObject::kWriteDelete);
	
	
	fileCorrWrite->Write();
	fileCorrWrite->Close();
}