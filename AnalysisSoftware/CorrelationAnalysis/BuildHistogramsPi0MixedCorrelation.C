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

typedef TVectorT<float> TVectorF;



void BuildHistogramsPi0MixedCorrelation(TString fileName = "kkoch_GammaConvCorrelationMixedTree.root", TString CutSelection="00000" , Int_t kMC=0, Bool_t merge=0, TString nameAddition =""){

	TString V0Finder = CutSelection(0,1);
	TString etaCutNumber = CutSelection(1,1);
	TString minPtTrigCutNumber = CutSelection(2,1);
	TString minPtAssCutNumber = CutSelection(3,1);
	TString isoCutNumber = CutSelection(4,1);
	TString maxFracPtCutNumber = CutSelection(5,1);
	
	if ( V0Finder.CompareTo("0") == 0){
		cout << "V0Finder: " <<  "Onfly" << endl;
	} else if (	V0Finder.CompareTo("1") == 0){
		cout << "V0Finder: " <<  "Offline" << endl;
	}
	
	Double_t etaMaxCut = 0.;
	if (etaCutNumber.CompareTo("0") == 0){
		etaMaxCut = 0.9;
 	} else if (etaCutNumber.CompareTo("1") == 0 ){
		etaMaxCut = 0.8;
 	}else if (etaCutNumber.CompareTo("2") == 0 ){
		etaMaxCut = 1.2;
 	}else if (etaCutNumber.CompareTo("3") == 0 ){
		etaMaxCut = 1.4;
 	} else if (etaCutNumber.CompareTo("4") == 0 ){
		etaMaxCut = 0.1;
	} else {
		etaMaxCut = 0.9;
	}
	cout << "Eta range: " <<  "|eta| < " << etaMaxCut << endl;
	
	Double_t minPtPi0Cut = 0.0;
	if (minPtTrigCutNumber.CompareTo("0") == 0){
		minPtPi0Cut = 0.0;
 	} else if (minPtTrigCutNumber.CompareTo("1") == 0 ){
		minPtPi0Cut = 0.05;
 	} else if (minPtTrigCutNumber.CompareTo("2") == 0 ){
		minPtPi0Cut = 0.1;
	} else if (minPtTrigCutNumber.CompareTo("3") == 0 ){
		minPtPi0Cut = 0.15;
 	} else if (minPtTrigCutNumber.CompareTo("4") == 0 ){
		minPtPi0Cut = 0.2;
	}  else if (minPtTrigCutNumber.CompareTo("4") == 0 ){
		minPtPi0Cut = 0.4;
	}
	cout<< "Min pt Trig-photon: " << minPtPi0Cut << endl;
	
	Double_t minPtAssChCut = 0.0;
	if (minPtAssCutNumber.CompareTo("0") == 0){
		minPtAssChCut = 0.2;
 	} else if (minPtAssCutNumber.CompareTo("1") == 0 ){
		minPtAssChCut = 0.5;
 	} else if (minPtAssCutNumber.CompareTo("2") == 0 ){
		minPtAssChCut = 0.75;
	} else if (minPtAssCutNumber.CompareTo("3") == 0 ){
		minPtAssChCut = 1.;
 	} else if (minPtAssCutNumber.CompareTo("4") == 0 ){
		minPtAssChCut = 1.5;
	}  else if (minPtAssCutNumber.CompareTo("5") == 0 ){
		minPtAssChCut = 2.;
	}
	cout<< "Min pt associated charged: " << minPtAssChCut << endl;
	
	
	Double_t isoCut = 0.4;
	if (isoCutNumber.CompareTo("0") == 0){
		isoCut = 0.1;
 	} else if (isoCutNumber.CompareTo("1") == 0 ){
		isoCut = 0.2;
 	} else if (isoCutNumber.CompareTo("2") == 0 ){
		isoCut = 0.4;
	} else if (isoCutNumber.CompareTo("3") == 0 ){
		isoCut = 0.6;
	}
	cout<< "isolation Cut: " << isoCut << endl;
	
	Double_t maxSumInCone= 0.1;
	if (maxFracPtCutNumber.CompareTo("0") == 0){
		maxSumInCone = 0.01;
 	} else if (maxFracPtCutNumber.CompareTo("1") == 0 ){
		maxSumInCone = 0.05;
 	} else if (maxFracPtCutNumber.CompareTo("2") == 0 ){
		maxSumInCone = 0.075;
	} else if (maxFracPtCutNumber.CompareTo("3") == 0 ){
		maxSumInCone = 0.1;
	}
	cout<< "maximum Fraction of pt in cone: " << maxSumInCone << endl;
	

	TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject(fileName.Data());
   if (!f) {
      f = new TFile(fileName.Data());
   }

	// Declaration of leaf types
   Double_t        ptLeadingPi0;
   Double_t        phiLeadingPi0;
   Double_t        etaLeadingPi0;
   Double_t        massLeadingPi0;
   Int_t           nAssociatedChPi0;
   Int_t           nAssociatedGammaPi0;
   TVectorF * ptGammaAssosiatedPi0 = new TVectorF;
   TVectorF * dPhiGammaAssosiatedPi0 = new TVectorF;
   TVectorF * dEtaGammaAssosiatedPi0= new TVectorF;
   TVectorF * isoGammaAssosiatedPi0= new TVectorF;
   TVectorF * ptChAssociatedPi0= new TVectorF;
   TVectorF * dPhiChAssosiatedPi0= new TVectorF;
   TVectorF * dEtaChAssosiatedPi0= new TVectorF;
   TVectorF * isoChAssosiatedPi0= new TVectorF;
	
	TTree* treeCorrPi0 = (TTree*)gDirectory->Get("Pi0MixedEvent");
 
	
   treeCorrPi0->SetBranchAddress("ptLeadingMix", &ptLeadingPi0);
	treeCorrPi0->SetBranchAddress("phiLeadingMix", &phiLeadingPi0);
   treeCorrPi0->SetBranchAddress("etaLeadingMix", &etaLeadingPi0);
   treeCorrPi0->SetBranchAddress("massLeadingMix", &massLeadingPi0);
	treeCorrPi0->SetBranchAddress("nAssociatedCh", &nAssociatedChPi0);
	treeCorrPi0->SetBranchAddress("nAssociatedGamma", &nAssociatedGammaPi0);
   treeCorrPi0->SetBranchAddress("ptGammaAssosiated.", &ptGammaAssosiatedPi0);
   treeCorrPi0->SetBranchAddress("dPhiGammaAssosiated.", &dPhiGammaAssosiatedPi0);
   treeCorrPi0->SetBranchAddress("dEtaGammaAssosiated.", &dEtaGammaAssosiatedPi0);
   treeCorrPi0->SetBranchAddress("isoGammaAssosiated.", &isoGammaAssosiatedPi0);
   treeCorrPi0->SetBranchAddress("ptChAssosiated.", &ptChAssociatedPi0);
   treeCorrPi0->SetBranchAddress("dPhiChAssosiated.", &dPhiChAssosiatedPi0);
   treeCorrPi0->SetBranchAddress("dEtaChAssosiated.", &dEtaChAssosiatedPi0);
   treeCorrPi0->SetBranchAddress("isoChAssosiated.", &isoChAssosiatedPi0);

	
	cout<< "here" << endl;
	Int_t nPhiCorr 		= 200;
	Double_t firstBinPhiCorr= -TMath::Pi();
	Double_t lastBinPhiCorr = TMath::Pi();

	Int_t ndPhiCorr 		= 200;
	Double_t firstBindPhiCorr= -0.5*TMath::Pi();
	Double_t lastBindPhiCorr = 1.5*TMath::Pi();

	Int_t nEtaCorr 			= 100;
	Double_t firstBinEtaCorr 	= -1.;
	Double_t lastBinEtaCorr 	= 1.;
	
	Int_t ndEtaCorr 			= 90;
	Double_t firstBindEtaCorr 	= -3.;
	Double_t lastBindEtaCorr 	= 3.;
	
	Int_t nPtCorr 			= 250;
	Double_t firstBinPtCorr 	= 0.;
	Double_t lastBinPtCorr 	= 50.;
	
	Int_t nInvMassPi0 = 500;
	Double_t firstBinInvMasCorr 	= 0.08;
	Double_t lastBinInvMassCorr 	= 0.2;

	Int_t nIsoCorr 			= 100;
	Double_t firstBinIsoCorr 	= 0.;
	Double_t lastBinIsoCorr 	= 10.;
	
	
	TH2F* histoCorrPi0_Phi_Eta;
	TH2F* histoCorrPi0_Phi_Pt;
	TH2F* histoCorrPi0_Eta_Pt;
	TH2F* histoCorrPi0_InvMass_Pt;
	TH2F* histoCorrPi0_dPhiCh_dEtaCh ;
	TH2F* histoCorrPi0_dPhiCh_dEtaCh_PtA1GeV_PtT2GeV ;
	TH2F* histoCorrPi0_dPhiCh_dEtaCh_PtA1GeV_PtT5GeV ;
	TH3F* histoCorrPi0_dPhiCh_PtAssoc_PtTrig;
	TH3F* histoCorrPi0_dEtaCh_PtAssoc_PtTrig;
	TH3F* histoCorrPi0_PoutCh_PtAssoc_PtTrig;
	TH2F* histoCorrPi0_IsoCh_PtTrig;
	TH2F* histoCorrPi0_dPhiGa_dEtaGa ;
	TH3F* histoCorrPi0_dPhiGa_PtAssoc_PtTrig;
	TH3F* histoCorrPi0_dEtaGa_PtAssoc_PtTrig;
	TH2F* histoCorrPi0_IsoGa_PtTrig;
	TH2F* histoCorrPi0_IsoMin_Pt;
	TH3F* histoCorrPi0Iso_dEtaCh_PtAssoc_PtTrig;
	TH3F* histoCorrPi0Iso_dPhiCh_PtAssoc_PtTrig;
	
	TString fileNameOutput;
	if (kMC==1){
		fileNameOutput = Form("Pi0MixedConvCorr_%s_MCrec.root",nameAddition.Data());
	} else if (kMC==0){
		fileNameOutput = Form("Pi0MixedConvCorr_%s_Data.root",nameAddition.Data());
	} else if (kMC==2){
		fileNameOutput = Form("Pi0MixedConvCorr_%s_MCtrue.root",nameAddition.Data());
	}
	TFile* fileGammaCorr = new TFile(fileNameOutput.Data());
	TDirectory*  directoryPi0Corr = 		(TDirectory*)fileGammaCorr->Get(Form("CorrPi0_%s",  CutSelection.Data())); 	
	cout << "here" << endl;
	if (!merge || directoryPi0Corr==0) {			
		cout << "here" << endl;
		histoCorrPi0_Phi_Eta =  new TH2F("ESD_CorrPi0_Phi_Eta","", nPhiCorr, firstBinPhiCorr, lastBinPhiCorr, nEtaCorr, firstBinEtaCorr, lastBinEtaCorr);
		histoCorrPi0_Phi_Pt =  new TH2F("ESD_CorrPi0_Phi_Pt","", nPhiCorr, firstBinPhiCorr, lastBinPhiCorr, nPtCorr, firstBinPtCorr, lastBinPtCorr);
		histoCorrPi0_Eta_Pt =  new TH2F("ESD_CorrPi0_Eta_Pt","", nEtaCorr, firstBinEtaCorr, lastBinEtaCorr, nPtCorr, firstBinPtCorr, lastBinPtCorr);
		histoCorrPi0_InvMass_Pt =  new TH2F("ESD_CorrPi0_InvMass_Pt","", nInvMassPi0, firstBinInvMasCorr, lastBinInvMassCorr, nPtCorr, firstBinPtCorr, lastBinPtCorr);
		histoCorrPi0_dPhiCh_dEtaCh =  new TH2F("ESD_CorrPi0_dPhiCh_dEtaCh","", ndPhiCorr , firstBindPhiCorr, lastBindPhiCorr, ndEtaCorr, firstBindEtaCorr, lastBindEtaCorr);
		histoCorrPi0_dPhiCh_dEtaCh_PtA1GeV_PtT2GeV =  new TH2F("ESD_CorrPi0_dPhiCh_dEtaCh_PtA1GeV_PtT2GeV","", ndPhiCorr , firstBindPhiCorr, lastBindPhiCorr, ndEtaCorr, firstBindEtaCorr, lastBindEtaCorr);
		histoCorrPi0_dPhiCh_dEtaCh_PtA1GeV_PtT5GeV =  new TH2F("ESD_CorrPi0_dPhiCh_dEtaCh_PtA1GeV_PtT5GeV","", ndPhiCorr , firstBindPhiCorr, lastBindPhiCorr, ndEtaCorr, firstBindEtaCorr, lastBindEtaCorr);
		
		histoCorrPi0_dPhiCh_PtAssoc_PtTrig =  new TH3F("ESD_CorrPi0_dPhiCh_PtAssoc_PtTrig","", ndPhiCorr, firstBindPhiCorr, lastBindPhiCorr, nPtCorr, firstBinPtCorr, lastBinPtCorr, nPtCorr, firstBinPtCorr, lastBinPtCorr);
		histoCorrPi0_dEtaCh_PtAssoc_PtTrig =  new TH3F("ESD_CorrPi0_dEtaCh_PtAssoc_PtTrig","", ndEtaCorr, firstBindEtaCorr, lastBindEtaCorr, nPtCorr, firstBinPtCorr, lastBinPtCorr, nPtCorr, firstBinPtCorr, lastBinPtCorr);
		histoCorrPi0_PoutCh_PtAssoc_PtTrig =  new TH3F("ESD_CorrPi0_PoutCh_PtAssoc_PtTrig","", nPtCorr, firstBinPtCorr, lastBinPtCorr, nPtCorr, firstBinPtCorr, lastBinPtCorr, nPtCorr, firstBinPtCorr, lastBinPtCorr);
		
		histoCorrPi0_IsoCh_PtTrig = new TH2F("ESD_CorrPi0_IsoCh_PtTrig","", nIsoCorr, firstBinIsoCorr, lastBinIsoCorr, nPtCorr, firstBinPtCorr, lastBinPtCorr);
		histoCorrPi0_dPhiGa_dEtaGa =  new TH2F("ESD_CorrPi0_dPhiGa_dEtaGa","", ndPhiCorr , firstBindPhiCorr, lastBindPhiCorr, ndEtaCorr, firstBindEtaCorr, lastBindEtaCorr);
		histoCorrPi0_dPhiGa_PtAssoc_PtTrig =  new TH3F("ESD_CorrPi0_dPhiGa_PtAssoc_PtTrig","", ndPhiCorr, firstBindPhiCorr, lastBindPhiCorr, nPtCorr, firstBinPtCorr, lastBinPtCorr, nPtCorr, firstBinPtCorr, lastBinPtCorr);
		histoCorrPi0_dEtaGa_PtAssoc_PtTrig =  new TH3F("ESD_CorrPi0_dEtaGa_PtAssoc_PtTrig","", ndEtaCorr, firstBindEtaCorr, lastBindEtaCorr, nPtCorr, firstBinPtCorr, lastBinPtCorr, nPtCorr, firstBinPtCorr, lastBinPtCorr);
		histoCorrPi0_IsoGa_PtTrig = new TH2F("ESD_CorrPi0_IsoGa_PtTrig","", nIsoCorr, firstBinIsoCorr, lastBinIsoCorr, nPtCorr, firstBinPtCorr, lastBinPtCorr);
		histoCorrPi0_IsoMin_Pt =  new TH2F("ESD_CorrPi0_IsoMin_Pt","", nIsoCorr, firstBinIsoCorr, lastBinIsoCorr, nPtCorr, firstBinPtCorr, lastBinPtCorr);
		histoCorrPi0Iso_dPhiCh_PtAssoc_PtTrig =  new TH3F("ESD_CorrPi0Iso_dPhiCh_PtAssoc_PtTrig","", ndPhiCorr, firstBindPhiCorr, lastBindPhiCorr, nPtCorr, firstBinPtCorr, lastBinPtCorr, nPtCorr, firstBinPtCorr, lastBinPtCorr);
		histoCorrPi0Iso_dEtaCh_PtAssoc_PtTrig =  new TH3F("ESD_CorrPi0Iso_dEtaCh_PtAssoc_PtTrig","", ndEtaCorr, firstBindEtaCorr, lastBindEtaCorr, nPtCorr, firstBinPtCorr, lastBinPtCorr, nPtCorr, firstBinPtCorr, lastBinPtCorr);				
	} else {
		histoCorrPi0_Phi_Eta = 	(TH2F*)directoryPi0Corr->Get("ESD_CorrPi0_Phi_Eta");
		histoCorrPi0_Phi_Pt = 	(TH2F*)directoryPi0Corr->Get("ESD_CorrPi0_Phi_Pt");
		histoCorrPi0_Eta_Pt = 	(TH2F*)directoryPi0Corr->Get("ESD_CorrPi0_Eta_Pt");
		histoCorrPi0_InvMass_Pt = 	(TH2F*)directoryPi0Corr->Get("ESD_CorrPi0_InvMass_Pt");
		histoCorrPi0_dPhiCh_dEtaCh = 	(TH2F*)directoryPi0Corr->Get("ESD_CorrPi0_dPhiCh_dEtaCh");
		histoCorrPi0_dPhiCh_dEtaCh_PtA1GeV_PtT2GeV = (TH2F*)directoryPi0Corr->Get("ESD_CorrPi0_dPhiCh_dEtaCh_PtA1GeV_PtT2GeV");
		histoCorrPi0_dPhiCh_dEtaCh_PtA1GeV_PtT5GeV = (TH2F*)directoryPi0Corr->Get("ESD_CorrPi0_dPhiCh_dEtaCh_PtA1GeV_PtT5GeV");
		histoCorrPi0_dPhiCh_PtAssoc_PtTrig = 	(TH3F*)directoryPi0Corr->Get("ESD_CorrPi0_dPhiCh_PtAssoc_PtTrig");
		histoCorrPi0_dEtaCh_PtAssoc_PtTrig = 	(TH3F*)directoryPi0Corr->Get("ESD_CorrPi0_dEtaCh_PtAssoc_PtTrig");
		histoCorrPi0_IsoCh_PtTrig = 	(TH2F*)directoryPi0Corr->Get("ESD_CorrPi0_IsoCh_PtTrig");
		histoCorrPi0_dPhiGa_dEtaGa = 	(TH2F*)directoryPi0Corr->Get("ESD_CorrPi0_dPhiGa_dEtaGa");
		histoCorrPi0_dPhiGa_PtAssoc_PtTrig = 	(TH3F*)directoryPi0Corr->Get("ESD_CorrPi0_dPhiGa_PtAssoc_PtTrig");
		histoCorrPi0_dEtaGa_PtAssoc_PtTrig = 	(TH3F*)directoryPi0Corr->Get("ESD_CorrPi0_dEtaGa_PtAssoc_PtTrig");
		histoCorrPi0_PoutCh_PtAssoc_PtTrig = 	(TH3F*)directoryPi0Corr->Get("ESD_CorrPi0_PoutCh_PtAssoc_PtTrig");
		histoCorrPi0_IsoGa_PtTrig = 	(TH2F*)directoryPi0Corr->Get("ESD_CorrPi0_IsoGa_PtTrig");
		histoCorrPi0_IsoMin_Pt = 	(TH2F*)directoryPi0Corr->Get("ESD_CorrPi0_IsoMin_Pt");
		histoCorrPi0Iso_dPhiCh_PtAssoc_PtTrig = 	(TH3F*)directoryPi0Corr->Get("ESD_CorrPi0Iso_dPhiCh_PtAssoc_PtTrig");
		histoCorrPi0Iso_dEtaCh_PtAssoc_PtTrig = 	(TH3F*)directoryPi0Corr->Get("ESD_CorrPi0Iso_dEtaCh_PtAssoc_PtTrig");				
		
		histoCorrPi0_Phi_Eta->Sumw2();
		histoCorrPi0_Phi_Pt->Sumw2();
		histoCorrPi0_Eta_Pt->Sumw2();
		histoCorrPi0_InvMass_Pt->Sumw2();
		histoCorrPi0_dPhiCh_dEtaCh->Sumw2();
		histoCorrPi0_dPhiCh_dEtaCh_PtA1GeV_PtT2GeV->Sumw2();
		histoCorrPi0_dPhiCh_dEtaCh_PtA1GeV_PtT5GeV->Sumw2();
		
		histoCorrPi0_dPhiCh_PtAssoc_PtTrig->Sumw2();
		histoCorrPi0_dEtaCh_PtAssoc_PtTrig->Sumw2();
		histoCorrPi0_IsoCh_PtTrig->Sumw2();
		histoCorrPi0_dPhiGa_dEtaGa->Sumw2();
		histoCorrPi0_dPhiGa_PtAssoc_PtTrig->Sumw2();
		histoCorrPi0_dEtaGa_PtAssoc_PtTrig->Sumw2();
		histoCorrPi0_PoutCh_PtAssoc_PtTrig->Sumw2();
		histoCorrPi0_IsoGa_PtTrig->Sumw2();
		histoCorrPi0_IsoMin_Pt->Sumw2();
		histoCorrPi0Iso_dPhiCh_PtAssoc_PtTrig->Sumw2();
		histoCorrPi0Iso_dEtaCh_PtAssoc_PtTrig->Sumw2();
		
	}
	
	Double_t massPi0Max = 0.17;
	Double_t massPi0Min = 0.09;
	
	Long64_t nEntriesCorrPi0 = treeCorrPi0->GetEntries();
   Long64_t nbytesPi0 = 0;
	for (Long64_t i=0; i<nEntriesCorrPi0;i++) {
		nbytesPi0 += treeCorrPi0->GetEntry(i);
		if (ptLeadingPi0 > minPtPi0Cut && massLeadingPi0 > massPi0Min && massLeadingPi0 < massPi0Max && TMath::Abs(etaLeadingPi0) < etaMaxCut-0.2){
				
			histoCorrPi0_Phi_Eta->Fill(phiLeadingPi0,etaLeadingPi0);
			histoCorrPi0_Phi_Pt->Fill(phiLeadingPi0,ptLeadingPi0);
			histoCorrPi0_Eta_Pt->Fill(etaLeadingPi0,ptLeadingPi0);
			histoCorrPi0_InvMass_Pt->Fill(massLeadingPi0,ptLeadingPi0);
			Double_t isoMin = 100.;
			Double_t sumPtCone = 0.;
			for (Int_t j = 0; j < nAssociatedChPi0; j++){
				if (TMath::Abs(etaLeadingPi0+(*dEtaChAssosiatedPi0)[j]) > etaMaxCut) continue;
				if (ptLeadingPi0> 2 && (*ptChAssociatedPi0)[j]> 1){
					histoCorrPi0_dPhiCh_dEtaCh_PtA1GeV_PtT2GeV->Fill((*dPhiChAssosiatedPi0)[j],(*dEtaChAssosiatedPi0)[j]);
				}
				if (ptLeadingPi0> 5 && (*ptChAssociatedPi0)[j]> 1){
					histoCorrPi0_dPhiCh_dEtaCh_PtA1GeV_PtT5GeV->Fill((*dPhiChAssosiatedPi0)[j],(*dEtaChAssosiatedPi0)[j]);
				}
			
				histoCorrPi0_dPhiCh_dEtaCh->Fill((*dPhiChAssosiatedPi0)[j],(*dEtaChAssosiatedPi0)[j]);
				histoCorrPi0_dPhiCh_PtAssoc_PtTrig->Fill((*dPhiChAssosiatedPi0)[j],(*ptChAssociatedPi0)[j],ptLeadingPi0);
				histoCorrPi0_dEtaCh_PtAssoc_PtTrig->Fill((*dEtaChAssosiatedPi0)[j],(*ptChAssociatedPi0)[j],ptLeadingPi0);
				histoCorrPi0_PoutCh_PtAssoc_PtTrig->Fill((*ptChAssociatedPi0)[j]*TMath::Sin((*dPhiChAssosiatedPi0)[j]),(*ptChAssociatedPi0)[j],ptLeadingPi0);
				histoCorrPi0_IsoCh_PtTrig->Fill((*isoChAssosiatedPi0)[j],ptLeadingPi0);
				if ((*isoChAssosiatedPi0)[j] < isoCut){
					sumPtCone=+(*ptChAssociatedPi0)[j];
				}
				if (isoMin > (*isoChAssosiatedPi0)[j]){
					isoMin = (*isoChAssosiatedPi0)[j];
				}
			}
			histoCorrPi0_IsoMin_Pt->Fill(isoMin,ptLeadingPi0);
			if (sumPtCone < maxSumInCone* ptLeadingPi0){
				for (Int_t j = 0; j < nAssociatedChPi0; j++){
					histoCorrPi0Iso_dPhiCh_PtAssoc_PtTrig->Fill((*dPhiChAssosiatedPi0)[j],(*ptChAssociatedPi0)[j],ptLeadingPi0);
					histoCorrPi0Iso_dEtaCh_PtAssoc_PtTrig->Fill((*dEtaChAssosiatedPi0)[j],(*ptChAssociatedPi0)[j],ptLeadingPi0);
				}
			}
			for (Int_t k = 0; k < nAssociatedGammaPi0; k++){
				if (TMath::Abs(etaLeadingPi0+(*dEtaGammaAssosiatedPi0)[k]) > etaMaxCut) continue;
				histoCorrPi0_dPhiGa_dEtaGa->Fill((*dPhiGammaAssosiatedPi0)[k],(*dEtaGammaAssosiatedPi0)[k]);
				histoCorrPi0_dPhiGa_PtAssoc_PtTrig->Fill((*dPhiGammaAssosiatedPi0)[k],(*ptGammaAssosiatedPi0)[k],ptLeadingPi0);
				histoCorrPi0_dEtaGa_PtAssoc_PtTrig->Fill((*dEtaGammaAssosiatedPi0)[k],(*ptGammaAssosiatedPi0)[k],ptLeadingPi0);
				histoCorrPi0_IsoGa_PtTrig->Fill((*isoGammaAssosiatedPi0)[k],ptLeadingPi0);
			}
			
		}
	}

	
	
	TFile* fileCorrWrite = new TFile(fileNameOutput.Data(),"UPDATE");
	fileCorrWrite->mkdir(Form("CorrPi0_%s",  CutSelection.Data()));
	fileCorrWrite->cd(Form("CorrPi0_%s",  CutSelection.Data()));
	
		histoCorrPi0_Phi_Eta->Write("ESD_CorrPi0_Phi_Eta",TObject::kWriteDelete);		
		histoCorrPi0_Phi_Pt->Write("ESD_CorrPi0_Phi_Pt",TObject::kWriteDelete);		
		histoCorrPi0_Eta_Pt->Write("ESD_CorrPi0_Eta_Pt",TObject::kWriteDelete);		
		histoCorrPi0_InvMass_Pt->Write("ESD_CorrPi0_InvMass_Pt",TObject::kWriteDelete);		
		histoCorrPi0_dPhiCh_dEtaCh->Write("ESD_CorrPi0_dPhiCh_dEtaCh",TObject::kWriteDelete);		
		histoCorrPi0_dPhiCh_dEtaCh_PtA1GeV_PtT2GeV->Write("ESD_CorrPi0_dPhiCh_dEtaCh_PtA1GeV_PtT2GeV",TObject::kWriteDelete);		
		histoCorrPi0_dPhiCh_dEtaCh_PtA1GeV_PtT5GeV->Write("ESD_CorrPi0_dPhiCh_dEtaCh_PtA1GeV_PtT5GeV",TObject::kWriteDelete);		
		
		histoCorrPi0_dPhiCh_PtAssoc_PtTrig->Write("ESD_CorrPi0_dPhiCh_PtAssoc_PtTrig",TObject::kWriteDelete);		
		histoCorrPi0_dEtaCh_PtAssoc_PtTrig->Write("ESD_CorrPi0_dEtaCh_PtAssoc_PtTrig",TObject::kWriteDelete);		
		histoCorrPi0_PoutCh_PtAssoc_PtTrig->Write("ESD_CorrPi0_PoutCh_PtAssoc_PtTrig",TObject::kWriteDelete);		
		histoCorrPi0_IsoCh_PtTrig->Write("ESD_CorrPi0_IsoCh_PtTrig",TObject::kWriteDelete);		
		histoCorrPi0_dPhiGa_dEtaGa->Write("ESD_CorrPi0_dPhiGa_dEtaGa",TObject::kWriteDelete);		
		histoCorrPi0_dPhiGa_PtAssoc_PtTrig->Write("ESD_CorrPi0_dPhiGa_PtAssoc_PtTrig",TObject::kWriteDelete);		
		histoCorrPi0_dEtaGa_PtAssoc_PtTrig->Write("ESD_CorrPi0_dEtaGa_PtAssoc_PtTrig",TObject::kWriteDelete);		
		histoCorrPi0_IsoGa_PtTrig->Write("ESD_CorrPi0_IsoGa_PtTrig",TObject::kWriteDelete);		
			
		histoCorrPi0_IsoMin_Pt->Write("ESD_CorrPi0_IsoMin_Pt",TObject::kWriteDelete);
		histoCorrPi0Iso_dPhiCh_PtAssoc_PtTrig->Write("ESD_CorrPi0Iso_dPhiCh_PtAssoc_PtTrig",TObject::kWriteDelete);
		histoCorrPi0Iso_dEtaCh_PtAssoc_PtTrig->Write("ESD_CorrPi0Iso_dEtaCh_PtAssoc_PtTrig",TObject::kWriteDelete);				
		
	fileCorrWrite->Write();
	fileCorrWrite->Close();

	delete histoCorrPi0_Phi_Eta;
	delete histoCorrPi0_Phi_Pt;
	delete histoCorrPi0_Eta_Pt;
	delete histoCorrPi0_InvMass_Pt;
	delete histoCorrPi0_dPhiCh_dEtaCh;
	delete histoCorrPi0_dPhiCh_dEtaCh_PtA1GeV_PtT2GeV;
	delete histoCorrPi0_dPhiCh_dEtaCh_PtA1GeV_PtT5GeV;
	delete histoCorrPi0_dPhiCh_PtAssoc_PtTrig;
	delete histoCorrPi0_dEtaCh_PtAssoc_PtTrig;
	delete histoCorrPi0_PoutCh_PtAssoc_PtTrig;
	delete histoCorrPi0_IsoCh_PtTrig;
	delete histoCorrPi0_dPhiGa_dEtaGa;
	delete histoCorrPi0_dPhiGa_PtAssoc_PtTrig;
	delete histoCorrPi0_dEtaGa_PtAssoc_PtTrig;
	delete histoCorrPi0_IsoGa_PtTrig;
	delete histoCorrPi0_IsoMin_Pt;
	delete histoCorrPi0Iso_dPhiCh_PtAssoc_PtTrig;
	delete histoCorrPi0Iso_dEtaCh_PtAssoc_PtTrig;
		

	
}	