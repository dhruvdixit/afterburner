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



void BuildHistogramsGammaMixedCorrelation(TString fileName = "kkoch_GammaConvCorrelationMixedTree.root", TString CutSelection="00000" , Int_t kMC=0, Bool_t merge=0, TString nameAddition =""){

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
	
	Double_t minPtPhotonCut = 0.0;
	if (minPtTrigCutNumber.CompareTo("0") == 0){
		minPtPhotonCut = 0.0;
 	} else if (minPtTrigCutNumber.CompareTo("1") == 0 ){
		minPtPhotonCut = 0.05;
 	} else if (minPtTrigCutNumber.CompareTo("2") == 0 ){
		minPtPhotonCut = 0.1;
	} else if (minPtTrigCutNumber.CompareTo("3") == 0 ){
		minPtPhotonCut = 0.15;
 	} else if (minPtTrigCutNumber.CompareTo("4") == 0 ){
		minPtPhotonCut = 0.2;
	}  else if (minPtTrigCutNumber.CompareTo("4") == 0 ){
		minPtPhotonCut = 0.4;
	}
	cout<< "Min pt Trig-photon: " << minPtPhotonCut << endl;
	
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
   Double_t        ptLeadingGamma;
   Double_t        phiLeadingGamma;
   Double_t        etaLeadingGamma;
   Int_t           nAssociatedChGamma;
   Int_t           nAssociatedGammaGamma;
   TVectorF * ptGammaAssosiatedGamma = new TVectorF;
   TVectorF * dPhiGammaAssosiatedGamma = new TVectorF;
   TVectorF * dEtaGammaAssosiatedGamma= new TVectorF;
   TVectorF * isoGammaAssosiatedGamma= new TVectorF;
   TVectorF * ptChAssociatedGamma= new TVectorF;
   TVectorF * dPhiChAssosiatedGamma= new TVectorF;
   TVectorF * dEtaChAssosiatedGamma= new TVectorF;
   TVectorF * isoChAssosiatedGamma= new TVectorF;
	
	TTree* treeCorrGamma = (TTree*)gDirectory->Get("MixedEventGamma");
 
   treeCorrGamma->SetBranchAddress("ptLeadingMix", &ptLeadingGamma);
	treeCorrGamma->SetBranchAddress("phiLeadingMix", &phiLeadingGamma);
   treeCorrGamma->SetBranchAddress("etaLeadingMix", &etaLeadingGamma);
	treeCorrGamma->SetBranchAddress("nAssociatedCh", &nAssociatedChGamma);
	treeCorrGamma->SetBranchAddress("nAssociatedGamma", &nAssociatedGammaGamma);
   treeCorrGamma->SetBranchAddress("ptGammaAssosiated.", &ptGammaAssosiatedGamma);
   treeCorrGamma->SetBranchAddress("dPhiGammaAssosiated.", &dPhiGammaAssosiatedGamma);
   treeCorrGamma->SetBranchAddress("dEtaGammaAssosiated.", &dEtaGammaAssosiatedGamma);
   treeCorrGamma->SetBranchAddress("isoGammaAssosiated.", &isoGammaAssosiatedGamma);
   treeCorrGamma->SetBranchAddress("ptChAssosiated.", &ptChAssociatedGamma);
   treeCorrGamma->SetBranchAddress("dPhiChAssosiated.", &dPhiChAssosiatedGamma);
   treeCorrGamma->SetBranchAddress("dEtaChAssosiated.", &dEtaChAssosiatedGamma);
   treeCorrGamma->SetBranchAddress("isoChAssosiated.", &isoChAssosiatedGamma);

	
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
	
	Int_t ndEtaCorr 			= 300;
	Double_t firstBindEtaCorr 	= -3.;
	Double_t lastBindEtaCorr 	= 3.;
	
	Int_t nPtCorr 			= 250;
	Double_t firstBinPtCorr 	= 0.;
	Double_t lastBinPtCorr 	= 50.;
	
	Int_t nIsoCorr 			= 100;
	Double_t firstBinIsoCorr 	= 0.;
	Double_t lastBinIsoCorr 	= 10.;
	
	Int_t nAssGam = 100;
	Double_t firstBinAssGam = -0.5;
	Double_t lastBinAssGam = 99.5;

	Int_t nAssCh = 1000;
	Double_t firstBinAssCh = -0.5;
	Double_t lastBinAssCh = 999.5;

	TH2F* histoCorrGamma_Phi_Eta;
	TH1F* histoAssociatedGamma;
	TH1F* histoAssociatedCh;
	TH2F* histoCorrGamma_Phi_Pt;
	TH2F* histoCorrGamma_Eta_Pt;
	TH2F* histoCorrGamma_IsoMin_Pt;
	TH2F* histoCorrGamma_dPhiCh_dEtaCh;
	TH2F* histoCorrGamma_dPhiCh_dEtaCh_PtA1GeV_PtT2GeV;
	TH2F* histoCorrGamma_dPhiCh_dEtaCh_PtA1GeV_PtT5GeV;
	TH3F* histoCorrGamma_dPhiCh_PtAssoc_PtTrig;
	TH3F* histoCorrGamma_dEtaCh_PtAssoc_PtTrig;
	TH3F* histoCorrGamma_PoutCh_PtAssoc_PtTrig;
	TH2F* histoCorrGamma_IsoCh_PtTrig;
	TH2F* histoCorrGamma_dPhiGa_dEtaGa ;
	TH3F* histoCorrGamma_dPhiGa_PtAssoc_PtTrig;
	TH3F* histoCorrGamma_dEtaGa_PtAssoc_PtTrig;
	TH2F* histoCorrGamma_IsoGa_PtTrig;
	TH3F* histoCorrGammaIso_dPhiCh_PtAssoc_PtTrig;
	TH3F* histoCorrGammaIso_dEtaCh_PtAssoc_PtTrig;
	
	TString fileNameOutput;
	if (kMC==1){
		fileNameOutput = Form("GammaMixedConvCorr_%s_MCrec.root",nameAddition.Data());
	} else if (kMC==0){
		fileNameOutput = Form("GammaMixedConvCorr_%s_Data.root",nameAddition.Data());
	} else if (kMC==2){
		fileNameOutput = Form("GammaMixedConvCorr_%s_MCtrue.root",nameAddition.Data());
	}

	
	TFile* fileGammaCorr = new TFile(fileNameOutput.Data());
	TDirectory*  directoryGammaCorr = 		(TDirectory*)fileGammaCorr->Get(Form("CorrGamma_%s",  CutSelection.Data())); 	
	cout << "here" << endl;
	if (!merge || directoryGammaCorr==0) {			
		cout << "here" << endl;
		histoAssociatedGamma =  new TH1F("ESD_AssociatedGamma","", nAssGam, firstBinAssGam, lastBinAssGam);
		histoCorrGamma_Phi_Eta =  new TH2F("ESD_CorrGamma_Phi_Eta","", nPhiCorr, firstBinPhiCorr, lastBinPhiCorr, nEtaCorr, firstBinEtaCorr, lastBinEtaCorr);	
		histoAssociatedCh =  new TH1F("ESD_AssociatedCh","", nAssCh, firstBinAssCh, lastBinAssCh);
		histoCorrGamma_Phi_Pt =  new TH2F("ESD_CorrGamma_Phi_Pt","", nPhiCorr, firstBinPhiCorr, lastBinPhiCorr, nPtCorr, firstBinPtCorr, lastBinPtCorr);
		histoCorrGamma_Eta_Pt =  new TH2F("ESD_CorrGamma_Eta_Pt","", nEtaCorr, firstBinEtaCorr, lastBinEtaCorr, nPtCorr, firstBinPtCorr, lastBinPtCorr);
		histoCorrGamma_dPhiCh_dEtaCh =  new TH2F("ESD_CorrGamma_dPhiCh_dEtaCh","", ndPhiCorr , firstBindPhiCorr, lastBindPhiCorr, ndEtaCorr, firstBindEtaCorr, lastBindEtaCorr);
		histoCorrGamma_dPhiCh_dEtaCh_PtA1GeV_PtT2GeV =  new TH2F("ESD_CorrGamma_dPhiCh_dEtaCh_PtA1GeV_PtT2GeV","", ndPhiCorr , firstBindPhiCorr, lastBindPhiCorr, ndEtaCorr, firstBindEtaCorr, lastBindEtaCorr);
		histoCorrGamma_dPhiCh_dEtaCh_PtA1GeV_PtT5GeV =  new TH2F("ESD_CorrGamma_dPhiCh_dEtaCh_PtA1GeV_PtT5GeV","", ndPhiCorr , firstBindPhiCorr, lastBindPhiCorr, ndEtaCorr, firstBindEtaCorr, lastBindEtaCorr);
		histoCorrGamma_dPhiCh_PtAssoc_PtTrig =  new TH3F("ESD_CorrGamma_dPhiCh_PtAssoc_PtTrig","", ndPhiCorr, firstBindPhiCorr, lastBindPhiCorr, nPtCorr, firstBinPtCorr, lastBinPtCorr, nPtCorr, firstBinPtCorr, lastBinPtCorr);
		histoCorrGamma_dEtaCh_PtAssoc_PtTrig =  new TH3F("ESD_CorrGamma_dEtaCh_PtAssoc_PtTrig","", ndEtaCorr, firstBindEtaCorr, lastBindEtaCorr, nPtCorr, firstBinPtCorr, lastBinPtCorr, nPtCorr, firstBinPtCorr, lastBinPtCorr);
		histoCorrGamma_PoutCh_PtAssoc_PtTrig =  new TH3F("ESD_CorrGamma_PoutCh_PtAssoc_PtTrig","", nPtCorr, firstBinPtCorr, lastBinPtCorr, nPtCorr, firstBinPtCorr, lastBinPtCorr, nPtCorr, firstBinPtCorr, lastBinPtCorr);
		
		histoCorrGamma_IsoCh_PtTrig = new TH2F("ESD_CorrGamma_IsoCh_PtTrig","", nIsoCorr, firstBinIsoCorr, lastBinIsoCorr, nPtCorr, firstBinPtCorr, lastBinPtCorr);
		histoCorrGamma_dPhiGa_dEtaGa =  new TH2F("ESD_CorrGamma_dPhiGa_dEtaGa","", ndPhiCorr , firstBindPhiCorr, lastBindPhiCorr, ndEtaCorr, firstBindEtaCorr, lastBindEtaCorr);
		histoCorrGamma_dPhiGa_PtAssoc_PtTrig =  new TH3F("ESD_CorrGamma_dPhiGa_PtAssoc_PtTrig","", ndPhiCorr, firstBindPhiCorr, lastBindPhiCorr, nPtCorr, firstBinPtCorr, lastBinPtCorr, nPtCorr, firstBinPtCorr, lastBinPtCorr);
		histoCorrGamma_dEtaGa_PtAssoc_PtTrig =  new TH3F("ESD_CorrGamma_dEtaGa_PtAssoc_PtTrig","", ndEtaCorr, firstBindEtaCorr, lastBindEtaCorr, nPtCorr, firstBinPtCorr, lastBinPtCorr, nPtCorr, firstBinPtCorr, lastBinPtCorr);
		histoCorrGamma_IsoGa_PtTrig = new TH2F("ESD_CorrGamma_IsoGa_PtTrig","", nIsoCorr, firstBinIsoCorr, lastBinIsoCorr, nPtCorr, firstBinPtCorr, lastBinPtCorr);
		histoCorrGamma_IsoMin_Pt =  new TH2F("ESD_CorrGamma_IsoMin_Pt","", nIsoCorr, firstBinIsoCorr, lastBinIsoCorr, nPtCorr, firstBinPtCorr, lastBinPtCorr);
		histoCorrGammaIso_dPhiCh_PtAssoc_PtTrig =  new TH3F("ESD_CorrGammaIso_dPhiCh_PtAssoc_PtTrig","", ndPhiCorr, firstBindPhiCorr, lastBindPhiCorr, nPtCorr, firstBinPtCorr, lastBinPtCorr, nPtCorr, firstBinPtCorr, lastBinPtCorr);
		histoCorrGammaIso_dEtaCh_PtAssoc_PtTrig =  new TH3F("ESD_CorrGammaIso_dEtaCh_PtAssoc_PtTrig","", ndEtaCorr, firstBindEtaCorr, lastBindEtaCorr, nPtCorr, firstBinPtCorr, lastBinPtCorr, nPtCorr, firstBinPtCorr, lastBinPtCorr);				
	} else {
		histoAssociatedGamma = 	(TH1F*)directoryGammaCorr->Get("ESD_AssociatedGamma");
		histoCorrGamma_Phi_Eta = (TH2F*)directoryGammaCorr->Get("ESD_CorrGamma_Phi_Eta");
		histoAssociatedCh =  (TH1F*)directoryGammaCorr->Get("ESD_AssociatedCh");
		histoCorrGamma_Phi_Pt = (TH2F*)directoryGammaCorr->Get("ESD_CorrGamma_Phi_Pt");
		histoCorrGamma_Eta_Pt = (TH2F*)directoryGammaCorr->Get("ESD_CorrGamma_Eta_Pt");
		histoCorrGamma_dPhiCh_dEtaCh = (TH2F*)directoryGammaCorr->Get("ESD_CorrGamma_dPhiCh_dEtaCh");
		histoCorrGamma_dPhiCh_dEtaCh_PtA1GeV_PtT2GeV = (TH2F*)directoryGammaCorr->Get("ESD_CorrGamma_dPhiCh_dEtaCh_PtA1GeV_PtT2GeV");
		histoCorrGamma_dPhiCh_dEtaCh_PtA1GeV_PtT5GeV = (TH2F*)directoryGammaCorr->Get("ESD_CorrGamma_dPhiCh_dEtaCh_PtA1GeV_PtT5GeV");
		histoCorrGamma_dPhiCh_PtAssoc_PtTrig = (TH3F*)directoryGammaCorr->Get("ESD_CorrGamma_dPhiCh_PtAssoc_PtTrig");
		histoCorrGamma_dEtaCh_PtAssoc_PtTrig = (TH3F*)directoryGammaCorr->Get("ESD_CorrGamma_dEtaCh_PtAssoc_PtTrig");
		histoCorrGamma_PoutCh_PtAssoc_PtTrig =  (TH3F*)directoryGammaCorr->Get("ESD_CorrGamma_PoutCh_PtAssoc_PtTrig");
		histoCorrGamma_IsoCh_PtTrig = (TH2F*)directoryGammaCorr->Get("ESD_CorrGamma_IsoCh_PtTrig");
		histoCorrGamma_dPhiGa_dEtaGa =(TH2F*)directoryGammaCorr->Get("ESD_CorrGamma_dPhiGa_dEtaGa");
		histoCorrGamma_dPhiGa_PtAssoc_PtTrig =(TH3F*)directoryGammaCorr->Get("ESD_CorrGamma_dPhiGa_PtAssoc_PtTrig");
		histoCorrGamma_dEtaGa_PtAssoc_PtTrig =(TH3F*)directoryGammaCorr->Get("ESD_CorrGamma_dEtaGa_PtAssoc_PtTrig");
		histoCorrGamma_IsoGa_PtTrig = (TH2F*)directoryGammaCorr->Get("ESD_CorrGamma_IsoGa_PtTrig");
		histoCorrGamma_IsoMin_Pt = (TH2F*)directoryGammaCorr->Get("ESD_CorrGamma_IsoMin_Pt");
		histoCorrGammaIso_dPhiCh_PtAssoc_PtTrig = (TH3F*)directoryGammaCorr->Get("ESD_CorrGammaIso_dPhiCh_PtAssoc_PtTrig");
		histoCorrGammaIso_dEtaCh_PtAssoc_PtTrig = (TH3F*)directoryGammaCorr->Get("ESD_CorrGammaIso_dEtaCh_PtAssoc_PtTrig");
		histoAssociatedCh->Sumw2();

		histoAssociatedGamma->Sumw2();
		histoCorrGamma_Phi_Eta->Sumw2();
		histoCorrGamma_Phi_Pt->Sumw2();
		histoCorrGamma_Eta_Pt->Sumw2();
		histoCorrGamma_dPhiCh_dEtaCh->Sumw2();
		histoCorrGamma_dPhiCh_dEtaCh_PtA1GeV_PtT2GeV->Sumw2();
		histoCorrGamma_dPhiCh_dEtaCh_PtA1GeV_PtT5GeV->Sumw2();
		histoCorrGamma_dPhiCh_PtAssoc_PtTrig->Sumw2();
		histoCorrGamma_dEtaCh_PtAssoc_PtTrig->Sumw2();
		histoCorrGamma_PoutCh_PtAssoc_PtTrig->Sumw2();
		histoCorrGamma_IsoCh_PtTrig->Sumw2();
		histoCorrGamma_dPhiGa_dEtaGa->Sumw2();
		histoCorrGamma_dPhiGa_PtAssoc_PtTrig->Sumw2();
		histoCorrGamma_dEtaGa_PtAssoc_PtTrig->Sumw2();
		histoCorrGamma_IsoGa_PtTrig->Sumw2();
		histoCorrGamma_IsoMin_Pt->Sumw2();
		histoCorrGammaIso_dPhiCh_PtAssoc_PtTrig->Sumw2();
		histoCorrGammaIso_dEtaCh_PtAssoc_PtTrig->Sumw2();
	}
	
	Long64_t nEntriesCorrGamma = treeCorrGamma->GetEntries();
   Long64_t nbytesGamma = 0;
	for (Long64_t i=0; i<nEntriesCorrGamma;i++) {
		nbytesGamma += treeCorrGamma->GetEntry(i);
		if (ptLeadingGamma > minPtPhotonCut && TMath::Abs(etaLeadingGamma) < etaMaxCut-0.2){ 
			histoAssociatedCh->Fill(nAssociatedChGamma);
			histoAssociatedGamma->Fill(nAssociatedGammaGamma);
			histoCorrGamma_Phi_Eta->Fill(phiLeadingGamma,etaLeadingGamma);
			histoCorrGamma_Phi_Pt->Fill(phiLeadingGamma,ptLeadingGamma);
			histoCorrGamma_Eta_Pt->Fill(etaLeadingGamma,ptLeadingGamma);
			Double_t isoMin = 100.;
			Double_t sumPtCone = 0.;
			for (Int_t j = 0; j < nAssociatedChGamma; j++){
				if (TMath::Abs(etaLeadingGamma+(*dEtaChAssosiatedGamma)[j]) > etaMaxCut) continue;
				if (ptLeadingGamma> 2 && (*ptChAssociatedGamma)[j]> 1){
					histoCorrGamma_dPhiCh_dEtaCh_PtA1GeV_PtT2GeV->Fill((*dPhiChAssosiatedGamma)[j],(*dEtaChAssosiatedGamma)[j]);
				}
				if (ptLeadingGamma> 5 && (*ptChAssociatedGamma)[j]> 1){
					histoCorrGamma_dPhiCh_dEtaCh_PtA1GeV_PtT5GeV->Fill((*dPhiChAssosiatedGamma)[j],(*dEtaChAssosiatedGamma)[j]);
				}
				histoCorrGamma_dPhiCh_dEtaCh->Fill((*dPhiChAssosiatedGamma)[j],(*dEtaChAssosiatedGamma)[j]);
				histoCorrGamma_dPhiCh_PtAssoc_PtTrig->Fill((*dPhiChAssosiatedGamma)[j],(*ptChAssociatedGamma)[j],ptLeadingGamma);
				histoCorrGamma_dEtaCh_PtAssoc_PtTrig->Fill((*dEtaChAssosiatedGamma)[j],(*ptChAssociatedGamma)[j],ptLeadingGamma);
				histoCorrGamma_PoutCh_PtAssoc_PtTrig->Fill((*ptChAssociatedGamma)[j]*TMath::Sin((*dPhiChAssosiatedGamma)[j]),(*ptChAssociatedGamma)[j],ptLeadingGamma);
				histoCorrGamma_IsoCh_PtTrig->Fill((*isoChAssosiatedGamma)[j],ptLeadingGamma);
				if ((*isoChAssosiatedGamma)[j] < isoCut){
					sumPtCone=+(*ptChAssociatedGamma)[j];
				}
				if (isoMin > (*isoChAssosiatedGamma)[j]){
					isoMin = (*isoChAssosiatedGamma)[j];
				}
			}
			histoCorrGamma_IsoMin_Pt->Fill(isoMin,ptLeadingGamma);
			if (sumPtCone < maxSumInCone* ptLeadingGamma){
				for (Int_t j = 0; j < nAssociatedChGamma; j++){
					histoCorrGammaIso_dPhiCh_PtAssoc_PtTrig->Fill((*dPhiChAssosiatedGamma)[j],(*ptChAssociatedGamma)[j],ptLeadingGamma);
					histoCorrGammaIso_dEtaCh_PtAssoc_PtTrig->Fill((*dEtaChAssosiatedGamma)[j],(*ptChAssociatedGamma)[j],ptLeadingGamma);
				}
			}
				
			for (Int_t k = 0; k < nAssociatedGammaGamma; k++){
				if (TMath::Abs(etaLeadingGamma+(*dEtaGammaAssosiatedGamma)[k]) > etaMaxCut) continue;
				histoCorrGamma_dPhiGa_dEtaGa->Fill((*dPhiGammaAssosiatedGamma)[k],(*dEtaGammaAssosiatedGamma)[k]);
				histoCorrGamma_dPhiGa_PtAssoc_PtTrig->Fill((*dPhiGammaAssosiatedGamma)[k],(*ptGammaAssosiatedGamma)[k],ptLeadingGamma);
				histoCorrGamma_dEtaGa_PtAssoc_PtTrig->Fill((*dEtaGammaAssosiatedGamma)[k],(*ptGammaAssosiatedGamma)[k],ptLeadingGamma);
				histoCorrGamma_IsoGa_PtTrig->Fill((*isoGammaAssosiatedGamma)[k],ptLeadingGamma);
			}			
		}
	}

	
	
	TFile* fileCorrWrite = new TFile(fileNameOutput.Data(),"UPDATE");
	fileCorrWrite->mkdir(Form("CorrGamma_%s",  CutSelection.Data()));
	fileCorrWrite->cd(Form("CorrGamma_%s",  CutSelection.Data()));
		histoAssociatedCh->Write("ESD_AssociatedCh",TObject::kWriteDelete);		
		histoAssociatedGamma->Write("ESD_AssociatedGamma",TObject::kWriteDelete);		
		histoCorrGamma_Phi_Eta->Write("ESD_CorrGamma_Phi_Eta",TObject::kWriteDelete);		
		histoCorrGamma_Phi_Pt->Write("ESD_CorrGamma_Phi_Pt",TObject::kWriteDelete);		
		histoCorrGamma_Eta_Pt->Write("ESD_CorrGamma_Eta_Pt",TObject::kWriteDelete);		
		histoCorrGamma_dPhiCh_dEtaCh->Write("ESD_CorrGamma_dPhiCh_dEtaCh",TObject::kWriteDelete);		
		histoCorrGamma_dPhiCh_dEtaCh_PtA1GeV_PtT2GeV->Write("ESD_CorrGamma_dPhiCh_dEtaCh_PtA1GeV_PtT2GeV",TObject::kWriteDelete);		
		histoCorrGamma_dPhiCh_dEtaCh_PtA1GeV_PtT5GeV->Write("ESD_CorrGamma_dPhiCh_dEtaCh_PtA1GeV_PtT5GeV",TObject::kWriteDelete);		
		histoCorrGamma_dPhiCh_PtAssoc_PtTrig->Write("ESD_CorrGamma_dPhiCh_PtAssoc_PtTrig",TObject::kWriteDelete);		
		histoCorrGamma_dEtaCh_PtAssoc_PtTrig->Write("ESD_CorrGamma_dEtaCh_PtAssoc_PtTrig",TObject::kWriteDelete);		
		histoCorrGamma_PoutCh_PtAssoc_PtTrig->Write("ESD_CorrGamma_PoutCh_PtAssoc_PtTrig",TObject::kWriteDelete);		
		histoCorrGamma_IsoCh_PtTrig->Write("ESD_CorrGamma_IsoCh_PtTrig",TObject::kWriteDelete);		
		histoCorrGamma_dPhiGa_dEtaGa->Write("ESD_CorrGamma_dPhiGa_dEtaGa",TObject::kWriteDelete);		
		histoCorrGamma_dPhiGa_PtAssoc_PtTrig->Write("ESD_CorrGamma_dPhiGa_PtAssoc_PtTrig",TObject::kWriteDelete);		
		histoCorrGamma_dEtaGa_PtAssoc_PtTrig->Write("ESD_CorrGamma_dEtaGa_PtAssoc_PtTrig",TObject::kWriteDelete);		
		histoCorrGamma_IsoGa_PtTrig->Write("ESD_CorrGamma_IsoGa_PtTrig",TObject::kWriteDelete);		
		histoCorrGamma_IsoMin_Pt->Write("ESD_CorrGamma_IsoMin_Pt",TObject::kWriteDelete);		
		histoCorrGammaIso_dPhiCh_PtAssoc_PtTrig->Write("ESD_CorrGammaIso_dPhiCh_PtAssoc_PtTrig",TObject::kWriteDelete);		
		histoCorrGammaIso_dEtaCh_PtAssoc_PtTrig->Write("ESD_CorrGammaIso_dEtaCh_PtAssoc_PtTrig",TObject::kWriteDelete);		
		
	fileCorrWrite->Write();
	fileCorrWrite->Close();

	delete histoAssociatedCh;
	delete histoAssociatedGamma;
	delete histoCorrGamma_Phi_Eta;
	delete histoCorrGamma_Phi_Pt;
	delete histoCorrGamma_Eta_Pt;
	delete histoCorrGamma_dPhiCh_dEtaCh;
	delete histoCorrGamma_dPhiCh_dEtaCh_PtA1GeV_PtT2GeV;
	delete histoCorrGamma_dPhiCh_dEtaCh_PtA1GeV_PtT5GeV;
	delete histoCorrGamma_dPhiCh_PtAssoc_PtTrig;
	delete histoCorrGamma_dEtaCh_PtAssoc_PtTrig;
	delete histoCorrGamma_PoutCh_PtAssoc_PtTrig;
	delete histoCorrGamma_IsoCh_PtTrig;
	delete histoCorrGamma_dPhiGa_dEtaGa;
	delete histoCorrGamma_dPhiGa_PtAssoc_PtTrig;
	delete histoCorrGamma_dEtaGa_PtAssoc_PtTrig;
	delete histoCorrGamma_IsoGa_PtTrig;
	delete histoCorrGamma_IsoMin_Pt;
	delete histoCorrGammaIso_dPhiCh_PtAssoc_PtTrig;
	delete histoCorrGammaIso_dEtaCh_PtAssoc_PtTrig;		
	
}	