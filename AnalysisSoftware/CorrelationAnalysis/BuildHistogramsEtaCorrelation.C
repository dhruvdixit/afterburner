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



void BuildHistogramsEtaCorrelation(TString fileName = "kkoch_GammaConvMaterialTree.root", TString CutSelection="00000" , Int_t kMC=0, Bool_t merge=0, TString nameAddition =""){

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
	
	Double_t minPtEtaCut = 0.0;
	if (minPtTrigCutNumber.CompareTo("0") == 0){
		minPtEtaCut = 0.0;
 	} else if (minPtTrigCutNumber.CompareTo("1") == 0 ){
		minPtEtaCut = 0.05;
 	} else if (minPtTrigCutNumber.CompareTo("2") == 0 ){
		minPtEtaCut = 0.1;
	} else if (minPtTrigCutNumber.CompareTo("3") == 0 ){
		minPtEtaCut = 0.15;
 	} else if (minPtTrigCutNumber.CompareTo("4") == 0 ){
		minPtEtaCut = 0.2;
	}  else if (minPtTrigCutNumber.CompareTo("4") == 0 ){
		minPtEtaCut = 0.4;
	}
	cout<< "Min pt Trig-photon: " << minPtEtaCut << endl;
	
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
   Double_t        ptLeadingEta;
   Double_t        phiLeadingEta;
   Double_t        etaLeadingEta;
   Double_t        massLeadingEta;
   Double_t        ptLeadingChargedEta;
   Int_t           indexLeadingChargedEta;
   Int_t           nAssociatedChEta;
   Int_t           nAssociatedGammaEta;
   TVectorF * ptGammaAssosiatedEta = new TVectorF;
   TVectorF * dPhiGammaAssosiatedEta = new TVectorF;
   TVectorF * dEtaGammaAssosiatedEta= new TVectorF;
   TVectorF * isoGammaAssosiatedEta= new TVectorF;
   TVectorF * ptChAssociatedEta= new TVectorF;
   TVectorF * dPhiChAssosiatedEta= new TVectorF;
   TVectorF * dEtaChAssosiatedEta= new TVectorF;
   TVectorF * isoChAssosiatedEta= new TVectorF;
	
	TTree* treeCorrEta = (TTree*)gDirectory->Get("EtaCorr");
 
   treeCorrEta->SetBranchAddress("ptLeadingEta", &ptLeadingEta);
	treeCorrEta->SetBranchAddress("phiLeadingEta", &phiLeadingEta);
   treeCorrEta->SetBranchAddress("etaLeadingEta", &etaLeadingEta);
   treeCorrEta->SetBranchAddress("massLeadingEta", &massLeadingEta);
   treeCorrEta->SetBranchAddress("ptLeadingCharged", &ptLeadingChargedEta);
	treeCorrEta->SetBranchAddress("indexLeadingCharged", &indexLeadingChargedEta);
	treeCorrEta->SetBranchAddress("nAssociatedCh", &nAssociatedChEta);
	treeCorrEta->SetBranchAddress("nAssociatedGamma", &nAssociatedGammaEta);
   treeCorrEta->SetBranchAddress("ptGammaAssosiated.", &ptGammaAssosiatedEta);
   treeCorrEta->SetBranchAddress("dPhiGammaAssosiated.", &dPhiGammaAssosiatedEta);
   treeCorrEta->SetBranchAddress("dEtaGammaAssosiated.", &dEtaGammaAssosiatedEta);
   treeCorrEta->SetBranchAddress("isoGammaAssosiated.", &isoGammaAssosiatedEta);
   treeCorrEta->SetBranchAddress("ptChAssosiated.", &ptChAssociatedEta);
   treeCorrEta->SetBranchAddress("dPhiChAssosiated.", &dPhiChAssosiatedEta);
   treeCorrEta->SetBranchAddress("dEtaChAssosiated.", &dEtaChAssosiatedEta);
   treeCorrEta->SetBranchAddress("isoChAssosiated.", &isoChAssosiatedEta);

	
	cout<< "here" << endl;
	Int_t nPhiCorr 		= 200;
	Double_t firstBinPhiCorr= -TMath::Pi();
	Double_t lastBinPhiCorr = TMath::Pi();

	Int_t ndPhiCorr 		= 200;
	Double_t firstBindPhiCorr= -0.5*TMath::Pi();
	Double_t lastBindPhiCorr = 1.5*TMath::Pi();

	Int_t nEtaCorr 			= 40;
	Double_t firstBinEtaCorr 	= -1.;
	Double_t lastBinEtaCorr 	= 1.;
	
	Int_t ndEtaCorr 			= 120;
	Double_t firstBindEtaCorr 	= -3.;
	Double_t lastBindEtaCorr 	= 3.;
	
	Int_t nPtCorr 			= 500;
	Double_t firstBinPtCorr 	= 0.;
	Double_t lastBinPtCorr 	= 50.;
	
	Int_t nInvMassEta = 600;
	Double_t firstBinInvMasCorr 	= 0.4;
	Double_t lastBinInvMassCorr 	= 0.7;

	Int_t nIsoCorr 			= 100;
	Double_t firstBinIsoCorr 	= 0.;
	Double_t lastBinIsoCorr 	= 10.;
	
	
	TH2F* histoCorrEta_Phi_Eta;
	TH2F* histoCorrEta_Phi_Pt;
	TH2F* histoCorrEta_Eta_Pt;
	TH2F* histoCorrEta_InvMass_Pt;
	TH2F* histoCorrEta_dPhiCh_dEtaCh ;
	TH2F* histoCorrEta_dPhiCh_dEtaCh_PtA1GeV_PtT2GeV ;
	TH2F* histoCorrEta_dPhiCh_dEtaCh_PtA1GeV_PtT5GeV ;
	TH3F* histoCorrEta_dPhiCh_PtAssoc_PtTrig;
	TH3F* histoCorrEta_dEtaCh_PtAssoc_PtTrig;
	TH2F* histoCorrEta_IsoCh_PtTrig;
	TH2F* histoCorrEta_dPhiGa_dEtaGa ;
	TH3F* histoCorrEta_dPhiGa_PtAssoc_PtTrig;
	TH3F* histoCorrEta_dEtaGa_PtAssoc_PtTrig;
	TH2F* histoCorrEta_IsoGa_PtTrig;
	TH2F* histoCorrEtaSideBand_Phi_Eta;
	TH2F* histoCorrEtaSideBand_Phi_Pt;
	TH2F* histoCorrEtaSideBand_Eta_Pt;
	TH2F* histoCorrEtaSideBand_InvMass_Pt;
	TH2F* histoCorrEtaSideBand_dPhiCh_dEtaCh ;
	TH3F* histoCorrEtaSideBand_dPhiCh_PtAssoc_PtTrig;
	TH3F* histoCorrEtaSideBand_dEtaCh_PtAssoc_PtTrig;
	TH2F* histoCorrEtaSideBand_IsoCh_PtTrig;
	TH2F* histoCorrEtaSideBand_dPhiGa_dEtaGa ;
	TH3F* histoCorrEtaSideBand_dPhiGa_PtAssoc_PtTrig;
	TH3F* histoCorrEtaSideBand_dEtaGa_PtAssoc_PtTrig;
	TH2F* histoCorrEtaSideBand_IsoGa_PtTrig;
	TH2F* histoCorrEta_IsoMin_Pt;
	TH3F* histoCorrEtaIso_dEtaCh_PtAssoc_PtTrig;
	TH3F* histoCorrEtaIso_dPhiCh_PtAssoc_PtTrig;
	
	TString fileNameOutput;
	if (kMC==1){
		fileNameOutput = Form("EtaConvCorr_%s_MCrec.root",nameAddition.Data());
	} else if (kMC==0){
		fileNameOutput = Form("EtaConvCorr_%s_Data.root",nameAddition.Data());
	} else if (kMC==2){
		fileNameOutput = Form("EtaConvCorr_%s_MCtrue.root",nameAddition.Data());
	}
	TFile* fileGammaCorr = new TFile(fileNameOutput.Data());
	TDirectory*  directoryEtaCorr = 		(TDirectory*)fileGammaCorr->Get(Form("CorrEta_%s",  CutSelection.Data())); 	
	cout << "here" << endl;
	if (!merge || directoryEtaCorr==0) {			
		cout << "here" << endl;
		histoCorrEta_Phi_Eta =  new TH2F("ESD_CorrEta_Phi_Eta","", nPhiCorr, firstBinPhiCorr, lastBinPhiCorr, nEtaCorr, firstBinEtaCorr, lastBinEtaCorr);
		histoCorrEta_Phi_Pt =  new TH2F("ESD_CorrEta_Phi_Pt","", nPhiCorr, firstBinPhiCorr, lastBinPhiCorr, nPtCorr, firstBinPtCorr, lastBinPtCorr);
		histoCorrEta_Eta_Pt =  new TH2F("ESD_CorrEta_Eta_Pt","", nEtaCorr, firstBinEtaCorr, lastBinEtaCorr, nPtCorr, firstBinPtCorr, lastBinPtCorr);
		histoCorrEta_InvMass_Pt =  new TH2F("ESD_CorrEta_InvMass_Pt","", nInvMassEta, firstBinInvMasCorr, lastBinInvMassCorr, nPtCorr, firstBinPtCorr, lastBinPtCorr);
		histoCorrEta_dPhiCh_dEtaCh =  new TH2F("ESD_CorrEta_dPhiCh_dEtaCh","", ndPhiCorr , firstBindPhiCorr, lastBindPhiCorr, ndEtaCorr, firstBindEtaCorr, lastBindEtaCorr);
		histoCorrEta_dPhiCh_dEtaCh_PtA1GeV_PtT2GeV =  new TH2F("ESD_CorrEta_dPhiCh_dEtaCh_PtA1GeV_PtT2GeV","", ndPhiCorr , firstBindPhiCorr, lastBindPhiCorr, ndEtaCorr, firstBindEtaCorr, lastBindEtaCorr);
		histoCorrEta_dPhiCh_dEtaCh_PtA1GeV_PtT5GeV =  new TH2F("ESD_CorrEta_dPhiCh_dEtaCh_PtA1GeV_PtT5GeV","", ndPhiCorr , firstBindPhiCorr, lastBindPhiCorr, ndEtaCorr, firstBindEtaCorr, lastBindEtaCorr);
		
		histoCorrEta_dPhiCh_PtAssoc_PtTrig =  new TH3F("ESD_CorrEta_dPhiCh_PtAssoc_PtTrig","", ndPhiCorr, firstBindPhiCorr, lastBindPhiCorr, nPtCorr, firstBinPtCorr, lastBinPtCorr, nPtCorr, firstBinPtCorr, lastBinPtCorr);
		histoCorrEta_dEtaCh_PtAssoc_PtTrig =  new TH3F("ESD_CorrEta_dEtaCh_PtAssoc_PtTrig","", ndEtaCorr, firstBindEtaCorr, lastBindEtaCorr, nPtCorr, firstBinPtCorr, lastBinPtCorr, nPtCorr, firstBinPtCorr, lastBinPtCorr);
		histoCorrEta_IsoCh_PtTrig = new TH2F("ESD_CorrEta_IsoCh_PtTrig","", nIsoCorr, firstBinIsoCorr, lastBinIsoCorr, nPtCorr, firstBinPtCorr, lastBinPtCorr);
		histoCorrEta_dPhiGa_dEtaGa =  new TH2F("ESD_CorrEta_dPhiGa_dEtaGa","", ndPhiCorr , firstBindPhiCorr, lastBindPhiCorr, ndEtaCorr, firstBindEtaCorr, lastBindEtaCorr);
		histoCorrEta_dPhiGa_PtAssoc_PtTrig =  new TH3F("ESD_CorrEta_dPhiGa_PtAssoc_PtTrig","", ndPhiCorr, firstBindPhiCorr, lastBindPhiCorr, nPtCorr, firstBinPtCorr, lastBinPtCorr, nPtCorr, firstBinPtCorr, lastBinPtCorr);
		histoCorrEta_dEtaGa_PtAssoc_PtTrig =  new TH3F("ESD_CorrEta_dEtaGa_PtAssoc_PtTrig","", ndEtaCorr, firstBindEtaCorr, lastBindEtaCorr, nPtCorr, firstBinPtCorr, lastBinPtCorr, nPtCorr, firstBinPtCorr, lastBinPtCorr);
		histoCorrEta_IsoGa_PtTrig = new TH2F("ESD_CorrEta_IsoGa_PtTrig","", nIsoCorr, firstBinIsoCorr, lastBinIsoCorr, nPtCorr, firstBinPtCorr, lastBinPtCorr);
		histoCorrEtaSideBand_Phi_Eta =  new TH2F("ESD_CorrEtaSideBand_Phi_Eta","", nPhiCorr, firstBinPhiCorr, lastBinPhiCorr, nEtaCorr, firstBinEtaCorr, lastBinEtaCorr);
		histoCorrEtaSideBand_Phi_Pt =  new TH2F("ESD_CorrEtaSideBand_Phi_Pt","", nPhiCorr, firstBinPhiCorr, lastBinPhiCorr, nPtCorr, firstBinPtCorr, lastBinPtCorr);
		histoCorrEtaSideBand_Eta_Pt =  new TH2F("ESD_CorrEtaSideBand_Eta_Pt","", nEtaCorr, firstBinEtaCorr, lastBinEtaCorr, nPtCorr, firstBinPtCorr, lastBinPtCorr);
		histoCorrEtaSideBand_InvMass_Pt =  new TH2F("ESD_CorrEtaSideBand_InvMass_Pt","", nInvMassEta, firstBinInvMasCorr, lastBinInvMassCorr, nPtCorr, firstBinPtCorr, lastBinPtCorr);
		histoCorrEtaSideBand_dPhiCh_dEtaCh =  new TH2F("ESD_CorrEtaSideBand_dPhiCh_dEtaCh","", ndPhiCorr , firstBindPhiCorr, lastBindPhiCorr, ndEtaCorr, firstBindEtaCorr, lastBindEtaCorr);
		histoCorrEtaSideBand_dPhiCh_PtAssoc_PtTrig =  new TH3F("ESD_CorrEtaSideBand_dPhiCh_PtAssoc_PtTrig","", ndPhiCorr, firstBindPhiCorr, lastBindPhiCorr, nPtCorr, firstBinPtCorr, lastBinPtCorr, nPtCorr, firstBinPtCorr, lastBinPtCorr);
		histoCorrEtaSideBand_dEtaCh_PtAssoc_PtTrig =  new TH3F("ESD_CorrEtaSideBand_dEtaCh_PtAssoc_PtTrig","", ndEtaCorr, firstBindEtaCorr, lastBindEtaCorr, nPtCorr, firstBinPtCorr, lastBinPtCorr, nPtCorr, firstBinPtCorr, lastBinPtCorr);
		histoCorrEtaSideBand_IsoCh_PtTrig = new TH2F("ESD_CorrEtaSideBand_IsoCh_PtTrig","", nIsoCorr, firstBinIsoCorr, lastBinIsoCorr, nPtCorr, firstBinPtCorr, lastBinPtCorr);
		histoCorrEtaSideBand_dPhiGa_dEtaGa =  new TH2F("ESD_CorrEtaSideBand_dPhiGa_dEtaGa","", ndPhiCorr , firstBindPhiCorr, lastBindPhiCorr, ndEtaCorr, firstBindEtaCorr, lastBindEtaCorr);
		histoCorrEtaSideBand_dPhiGa_PtAssoc_PtTrig =  new TH3F("ESD_CorrEtaSideBand_dPhiGa_PtAssoc_PtTrig","", ndPhiCorr, firstBindPhiCorr, lastBindPhiCorr, nPtCorr, firstBinPtCorr, lastBinPtCorr, nPtCorr, firstBinPtCorr, lastBinPtCorr);
		histoCorrEtaSideBand_dEtaGa_PtAssoc_PtTrig =  new TH3F("ESD_CorrEtaSideBand_dEtaGa_PtAssoc_PtTrig","", ndEtaCorr, firstBindEtaCorr, lastBindEtaCorr, nPtCorr, firstBinPtCorr, lastBinPtCorr, nPtCorr, firstBinPtCorr, lastBinPtCorr);
		histoCorrEtaSideBand_IsoGa_PtTrig = new TH2F("ESD_CorrEtaSideBand_IsoGa_PtTrig","", nIsoCorr, firstBinIsoCorr, lastBinIsoCorr, nPtCorr, firstBinPtCorr, lastBinPtCorr);
		histoCorrEta_IsoMin_Pt =  new TH2F("ESD_CorrEta_IsoMin_Pt","", nIsoCorr, firstBinIsoCorr, lastBinIsoCorr, nPtCorr, firstBinPtCorr, lastBinPtCorr);
		histoCorrEtaIso_dPhiCh_PtAssoc_PtTrig =  new TH3F("ESD_CorrEtaIso_dPhiCh_PtAssoc_PtTrig","", ndPhiCorr, firstBindPhiCorr, lastBindPhiCorr, nPtCorr, firstBinPtCorr, lastBinPtCorr, nPtCorr, firstBinPtCorr, lastBinPtCorr);
		histoCorrEtaIso_dEtaCh_PtAssoc_PtTrig =  new TH3F("ESD_CorrEtaIso_dEtaCh_PtAssoc_PtTrig","", ndEtaCorr, firstBindEtaCorr, lastBindEtaCorr, nPtCorr, firstBinPtCorr, lastBinPtCorr, nPtCorr, firstBinPtCorr, lastBinPtCorr);				
	} else {
		histoCorrEta_Phi_Eta = 	(TH2F*)directoryEtaCorr->Get("ESD_CorrEta_Phi_Eta");
		histoCorrEta_Phi_Pt = 	(TH2F*)directoryEtaCorr->Get("ESD_CorrEta_Phi_Pt");
		histoCorrEta_Eta_Pt = 	(TH2F*)directoryEtaCorr->Get("ESD_CorrEta_Eta_Pt");
		histoCorrEta_InvMass_Pt = 	(TH2F*)directoryEtaCorr->Get("ESD_CorrEta_InvMass_Pt");
		histoCorrEta_dPhiCh_dEtaCh = 	(TH2F*)directoryEtaCorr->Get("ESD_CorrEta_dPhiCh_dEtaCh");
		histoCorrEta_dPhiCh_dEtaCh_PtA1GeV_PtT2GeV = (TH2F*)directoryEtaCorr->Get("ESD_CorrEta_dPhiCh_dEtaCh_PtA1GeV_PtT2GeV");
		histoCorrEta_dPhiCh_dEtaCh_PtA1GeV_PtT5GeV = (TH2F*)directoryEtaCorr->Get("ESD_CorrEta_dPhiCh_dEtaCh_PtA1GeV_PtT5GeV");
		histoCorrEta_dPhiCh_PtAssoc_PtTrig = 	(TH3F*)directoryEtaCorr->Get("ESD_CorrEta_dPhiCh_PtAssoc_PtTrig");
		histoCorrEta_dEtaCh_PtAssoc_PtTrig = 	(TH3F*)directoryEtaCorr->Get("ESD_CorrEta_dEtaCh_PtAssoc_PtTrig");
		histoCorrEta_IsoCh_PtTrig = 	(TH2F*)directoryEtaCorr->Get("ESD_CorrEta_IsoCh_PtTrig");
		histoCorrEta_dPhiGa_dEtaGa = 	(TH2F*)directoryEtaCorr->Get("ESD_CorrEta_dPhiGa_dEtaGa");
		histoCorrEta_dPhiGa_PtAssoc_PtTrig = 	(TH3F*)directoryEtaCorr->Get("ESD_CorrEta_dPhiGa_PtAssoc_PtTrig");
 		histoCorrEta_dEtaGa_PtAssoc_PtTrig = 	(TH3F*)directoryEtaCorr->Get("ESD_CorrEta_dEtaGa_PtAssoc_PtTrig");
		histoCorrEta_IsoGa_PtTrig = 	(TH2F*)directoryEtaCorr->Get("ESD_CorrEta_IsoGa_PtTrig");
		histoCorrEtaSideBand_Phi_Eta = 	(TH2F*)directoryEtaCorr->Get("ESD_CorrEtaSideBand_Phi_Eta");
		histoCorrEtaSideBand_Phi_Pt = 	(TH2F*)directoryEtaCorr->Get("ESD_CorrEtaSideBand_Phi_Pt");
		histoCorrEtaSideBand_Eta_Pt = 	(TH2F*)directoryEtaCorr->Get("ESD_CorrEtaSideBand_Eta_Pt");
		histoCorrEtaSideBand_InvMass_Pt = 	(TH2F*)directoryEtaCorr->Get("ESD_CorrEtaSideBand_InvMass_Pt");
		histoCorrEtaSideBand_dPhiCh_dEtaCh = 	(TH2F*)directoryEtaCorr->Get("ESD_CorrEtaSideBand_dPhiCh_dEtaCh");
		histoCorrEtaSideBand_dPhiCh_PtAssoc_PtTrig = 	(TH3F*)directoryEtaCorr->Get("ESD_CorrEtaSideBand_dPhiCh_PtAssoc_PtTrig");
		histoCorrEtaSideBand_dEtaCh_PtAssoc_PtTrig = 	(TH3F*)directoryEtaCorr->Get("ESD_CorrEtaSideBand_dEtaCh_PtAssoc_PtTrig");
		histoCorrEtaSideBand_IsoCh_PtTrig = 	(TH2F*)directoryEtaCorr->Get("ESD_CorrEtaSideBand_IsoCh_PtTrig");
		histoCorrEtaSideBand_dPhiGa_dEtaGa = 	(TH2F*)directoryEtaCorr->Get("ESD_CorrEtaSideBand_dPhiGa_dEtaGa");
		histoCorrEtaSideBand_dPhiGa_PtAssoc_PtTrig = 	(TH3F*)directoryEtaCorr->Get("ESD_CorrEtaSideBand_dPhiGa_PtAssoc_PtTrig");
		histoCorrEtaSideBand_dEtaGa_PtAssoc_PtTrig = 	(TH3F*)directoryEtaCorr->Get("ESD_CorrEtaSideBand_dEtaGa_PtAssoc_PtTrig");
		histoCorrEtaSideBand_IsoGa_PtTrig = 	(TH2F*)directoryEtaCorr->Get("ESD_CorrEtaSideBand_IsoGa_PtTrig");
		histoCorrEta_IsoMin_Pt = 	(TH2F*)directoryEtaCorr->Get("ESD_CorrEta_IsoMin_Pt");
		histoCorrEtaIso_dPhiCh_PtAssoc_PtTrig = 	(TH3F*)directoryEtaCorr->Get("ESD_CorrEtaIso_dPhiCh_PtAssoc_PtTrig");
		histoCorrEtaIso_dEtaCh_PtAssoc_PtTrig = 	(TH3F*)directoryEtaCorr->Get("ESD_CorrEtaIso_dEtaCh_PtAssoc_PtTrig");				
		
		histoCorrEta_Phi_Eta->Sumw2();
		histoCorrEta_Phi_Pt->Sumw2();
		histoCorrEta_Eta_Pt->Sumw2();
		histoCorrEta_InvMass_Pt->Sumw2();
		histoCorrEta_dPhiCh_dEtaCh->Sumw2();
		histoCorrEta_dPhiCh_dEtaCh_PtA1GeV_PtT2GeV->Sumw2();
		histoCorrEta_dPhiCh_dEtaCh_PtA1GeV_PtT5GeV->Sumw2();
		histoCorrEta_dPhiCh_PtAssoc_PtTrig->Sumw2();
		histoCorrEta_dEtaCh_PtAssoc_PtTrig->Sumw2();
		histoCorrEta_IsoCh_PtTrig->Sumw2();
		histoCorrEta_dPhiGa_dEtaGa->Sumw2();
		histoCorrEta_dPhiGa_PtAssoc_PtTrig->Sumw2();
		histoCorrEta_dEtaGa_PtAssoc_PtTrig->Sumw2();
		histoCorrEta_IsoGa_PtTrig->Sumw2();
		histoCorrEtaSideBand_Phi_Eta->Sumw2();
		histoCorrEtaSideBand_Phi_Pt->Sumw2();
		histoCorrEtaSideBand_Eta_Pt->Sumw2();
		histoCorrEtaSideBand_InvMass_Pt->Sumw2();
		histoCorrEtaSideBand_dPhiCh_dEtaCh->Sumw2();
		histoCorrEtaSideBand_dPhiCh_PtAssoc_PtTrig->Sumw2();
		histoCorrEtaSideBand_dEtaCh_PtAssoc_PtTrig->Sumw2();
		histoCorrEtaSideBand_IsoCh_PtTrig->Sumw2();
		histoCorrEtaSideBand_dPhiGa_dEtaGa->Sumw2();
		histoCorrEtaSideBand_dPhiGa_PtAssoc_PtTrig->Sumw2();
		histoCorrEtaSideBand_dEtaGa_PtAssoc_PtTrig->Sumw2();
		histoCorrEtaSideBand_IsoGa_PtTrig->Sumw2();
		histoCorrEta_IsoMin_Pt->Sumw2();
		histoCorrEtaIso_dPhiCh_PtAssoc_PtTrig->Sumw2();
		histoCorrEtaIso_dEtaCh_PtAssoc_PtTrig->Sumw2();		
	}
	
	Double_t massEtaMax = 0.6;
	Double_t massEtaMin = 0.45;
	
	Long64_t nEntriesCorrEta = treeCorrEta->GetEntries();
   Long64_t nbytesEta = 0;
	for (Long64_t i=0; i<nEntriesCorrEta;i++) {
		nbytesEta += treeCorrEta->GetEntry(i);
		if (ptLeadingEta > minPtEtaCut && massLeadingEta > massEtaMin && massLeadingEta < massEtaMax && TMath::Abs(etaLeadingEta) < etaMaxCut-0.2){ //&& ptLeadingEta > ptLeadingChargedEta
				
			histoCorrEta_Phi_Eta->Fill(phiLeadingEta,etaLeadingEta);
			histoCorrEta_Phi_Pt->Fill(phiLeadingEta,ptLeadingEta);
			histoCorrEta_Eta_Pt->Fill(etaLeadingEta,ptLeadingEta);
			histoCorrEta_InvMass_Pt->Fill(massLeadingEta,ptLeadingEta);
			Double_t isoMin = 100.;
			Double_t sumPtCone = 0.;
			for (Int_t j = 0; j < nAssociatedChEta; j++){
				if (TMath::Abs(etaLeadingEta+(*dEtaChAssosiatedEta)[j]) > etaMaxCut) continue;
				if (ptLeadingEta> 2 && (*ptChAssociatedEta)[j]> 1){
					histoCorrEta_dPhiCh_dEtaCh_PtA1GeV_PtT2GeV->Fill((*dPhiChAssosiatedEta)[j],(*dEtaChAssosiatedEta)[j]);
				}
				if (ptLeadingEta> 5 && (*ptChAssociatedEta)[j]> 1){
					histoCorrEta_dPhiCh_dEtaCh_PtA1GeV_PtT5GeV->Fill((*dPhiChAssosiatedEta)[j],(*dEtaChAssosiatedEta)[j]);
				}
			
				histoCorrEta_dPhiCh_dEtaCh->Fill((*dPhiChAssosiatedEta)[j],(*dEtaChAssosiatedEta)[j]);
				histoCorrEta_dPhiCh_PtAssoc_PtTrig->Fill((*dPhiChAssosiatedEta)[j],(*ptChAssociatedEta)[j],ptLeadingEta);
				histoCorrEta_dEtaCh_PtAssoc_PtTrig->Fill((*dEtaChAssosiatedEta)[j],(*ptChAssociatedEta)[j],ptLeadingEta);
				histoCorrEta_IsoCh_PtTrig->Fill((*isoChAssosiatedEta)[j],ptLeadingEta);
				if ((*isoChAssosiatedEta)[j] < isoCut){
					sumPtCone=+(*ptChAssociatedEta)[j];
				}
				if (isoMin > (*isoChAssosiatedEta)[j]){
					isoMin = (*isoChAssosiatedEta)[j];
				}
			}
			histoCorrEta_IsoMin_Pt->Fill(isoMin,ptLeadingEta);
			if (sumPtCone < maxSumInCone* ptLeadingEta){
				for (Int_t j = 0; j < nAssociatedChEta; j++){
					histoCorrEtaIso_dPhiCh_PtAssoc_PtTrig->Fill((*dPhiChAssosiatedEta)[j],(*ptChAssociatedEta)[j],ptLeadingEta);
					histoCorrEtaIso_dEtaCh_PtAssoc_PtTrig->Fill((*dEtaChAssosiatedEta)[j],(*ptChAssociatedEta)[j],ptLeadingEta);
				}
			}
			for (Int_t k = 0; k < nAssociatedGammaEta; k++){
				if (TMath::Abs(etaLeadingEta+(*dEtaGammaAssosiatedEta)[k]) > etaMaxCut) continue;
				histoCorrEta_dPhiGa_dEtaGa->Fill((*dPhiGammaAssosiatedEta)[k],(*dEtaGammaAssosiatedEta)[k]);
 				histoCorrEta_dPhiGa_PtAssoc_PtTrig->Fill((*dPhiGammaAssosiatedEta)[k],(*ptGammaAssosiatedEta)[k],ptLeadingEta);
				histoCorrEta_dEtaGa_PtAssoc_PtTrig->Fill((*dEtaGammaAssosiatedEta)[k],(*ptGammaAssosiatedEta)[k],ptLeadingEta);
				histoCorrEta_IsoGa_PtTrig->Fill((*isoGammaAssosiatedEta)[k],ptLeadingEta);
			}
			
		} else if (ptLeadingEta > minPtEtaCut && TMath::Abs(etaLeadingEta) < etaMaxCut-0.2 && massLeadingEta > massEtaMax ){ //&& ptLeadingEta > ptLeadingChargedEta
			histoCorrEtaSideBand_Phi_Eta->Fill(phiLeadingEta,etaLeadingEta);
			histoCorrEtaSideBand_Phi_Pt->Fill(phiLeadingEta,ptLeadingEta);
			histoCorrEtaSideBand_Eta_Pt->Fill(etaLeadingEta,ptLeadingEta);
			histoCorrEtaSideBand_InvMass_Pt->Fill(massLeadingEta,ptLeadingEta);
			for (Int_t j = 0; j < nAssociatedChEta; j++){
				if (TMath::Abs(etaLeadingEta+(*dEtaChAssosiatedEta)[j]) > etaMaxCut) continue;
				histoCorrEtaSideBand_dPhiCh_dEtaCh->Fill((*dPhiChAssosiatedEta)[j],(*dEtaChAssosiatedEta)[j]);
				histoCorrEtaSideBand_dPhiCh_PtAssoc_PtTrig->Fill((*dPhiChAssosiatedEta)[j],(*ptChAssociatedEta)[j],ptLeadingEta);
				histoCorrEtaSideBand_dEtaCh_PtAssoc_PtTrig->Fill((*dEtaChAssosiatedEta)[j],(*ptChAssociatedEta)[j],ptLeadingEta);
				histoCorrEtaSideBand_IsoCh_PtTrig->Fill((*isoChAssosiatedEta)[j],ptLeadingEta);
			}
			for (Int_t k = 0; k < nAssociatedGammaEta; k++){
				if (TMath::Abs(etaLeadingEta+(*dEtaGammaAssosiatedEta)[k]) > etaMaxCut) continue;
				histoCorrEtaSideBand_dPhiGa_dEtaGa->Fill((*dPhiGammaAssosiatedEta)[k],(*dEtaGammaAssosiatedEta)[k]);
				histoCorrEtaSideBand_dPhiGa_PtAssoc_PtTrig->Fill((*dPhiGammaAssosiatedEta)[k],(*ptGammaAssosiatedEta)[k],ptLeadingEta);
				histoCorrEtaSideBand_dEtaGa_PtAssoc_PtTrig->Fill((*dEtaGammaAssosiatedEta)[k],(*ptGammaAssosiatedEta)[k],ptLeadingEta);
				histoCorrEtaSideBand_IsoGa_PtTrig->Fill((*isoGammaAssosiatedEta)[k],ptLeadingEta);
			}
			
		}
	}

	
	
	TFile* fileCorrWrite = new TFile(fileNameOutput.Data(),"UPDATE");
	fileCorrWrite->mkdir(Form("CorrEta_%s",  CutSelection.Data()));
	fileCorrWrite->cd(Form("CorrEta_%s",  CutSelection.Data()));
	
		histoCorrEta_Phi_Eta->Write("ESD_CorrEta_Phi_Eta",TObject::kWriteDelete);		
		histoCorrEta_Phi_Pt->Write("ESD_CorrEta_Phi_Pt",TObject::kWriteDelete);		
		histoCorrEta_Eta_Pt->Write("ESD_CorrEta_Eta_Pt",TObject::kWriteDelete);		
		histoCorrEta_InvMass_Pt->Write("ESD_CorrEta_InvMass_Pt",TObject::kWriteDelete);		
		histoCorrEta_dPhiCh_dEtaCh->Write("ESD_CorrEta_dPhiCh_dEtaCh",TObject::kWriteDelete);		
		histoCorrEta_dPhiCh_dEtaCh_PtA1GeV_PtT2GeV->Write("ESD_CorrEta_dPhiCh_dEtaCh_PtA1GeV_PtT2GeV",TObject::kWriteDelete);		
		histoCorrEta_dPhiCh_dEtaCh_PtA1GeV_PtT5GeV->Write("ESD_CorrEta_dPhiCh_dEtaCh_PtA1GeV_PtT5GeV",TObject::kWriteDelete);		
		
		histoCorrEta_dPhiCh_PtAssoc_PtTrig->Write("ESD_CorrEta_dPhiCh_PtAssoc_PtTrig",TObject::kWriteDelete);		
		histoCorrEta_dEtaCh_PtAssoc_PtTrig->Write("ESD_CorrEta_dEtaCh_PtAssoc_PtTrig",TObject::kWriteDelete);		
		histoCorrEta_IsoCh_PtTrig->Write("ESD_CorrEta_IsoCh_PtTrig",TObject::kWriteDelete);		
		histoCorrEta_dPhiGa_dEtaGa->Write("ESD_CorrEta_dPhiGa_dEtaGa",TObject::kWriteDelete);		
 		histoCorrEta_dPhiGa_PtAssoc_PtTrig->Write("ESD_CorrEta_dPhiGa_PtAssoc_PtTrig",TObject::kWriteDelete);		
		histoCorrEta_dEtaGa_PtAssoc_PtTrig->Write("ESD_CorrEta_dEtaGa_PtAssoc_PtTrig",TObject::kWriteDelete);		
		histoCorrEta_IsoGa_PtTrig->Write("ESD_CorrEta_IsoGa_PtTrig",TObject::kWriteDelete);		
		
		histoCorrEtaSideBand_Phi_Eta->Write("ESD_CorrEtaSideBand_Phi_Eta",TObject::kWriteDelete);		
		histoCorrEtaSideBand_Phi_Pt->Write("ESD_CorrEtaSideBand_Phi_Pt",TObject::kWriteDelete);		
		histoCorrEtaSideBand_Eta_Pt->Write("ESD_CorrEtaSideBand_Eta_Pt",TObject::kWriteDelete);		
		histoCorrEtaSideBand_InvMass_Pt->Write("ESD_CorrEtaSideBand_InvMass_Pt",TObject::kWriteDelete);		
		histoCorrEtaSideBand_dPhiCh_dEtaCh->Write("ESD_CorrEtaSideBand_dPhiCh_dEtaCh",TObject::kWriteDelete);		
		histoCorrEtaSideBand_dPhiCh_PtAssoc_PtTrig->Write("ESD_CorrEtaSideBand_dPhiCh_PtAssoc_PtTrig",TObject::kWriteDelete);		
		histoCorrEtaSideBand_dEtaCh_PtAssoc_PtTrig->Write("ESD_CorrEtaSideBand_dEtaCh_PtAssoc_PtTrig",TObject::kWriteDelete);		
		histoCorrEtaSideBand_IsoCh_PtTrig->Write("ESD_CorrEtaSideBand_IsoCh_PtTrig",TObject::kWriteDelete);		
		histoCorrEtaSideBand_dPhiGa_dEtaGa->Write("ESD_CorrEtaSideBand_dPhiGa_dEtaGa",TObject::kWriteDelete);		
		histoCorrEtaSideBand_dPhiGa_PtAssoc_PtTrig->Write("ESD_CorrEtaSideBand_dPhiGa_PtAssoc_PtTrig",TObject::kWriteDelete);		
		histoCorrEtaSideBand_dEtaGa_PtAssoc_PtTrig->Write("ESD_CorrEtaSideBand_dEtaGa_PtAssoc_PtTrig",TObject::kWriteDelete);		
		histoCorrEtaSideBand_IsoGa_PtTrig->Write("ESD_CorrEtaSideBand_IsoGa_PtTrig",TObject::kWriteDelete);		
	
		histoCorrEta_IsoMin_Pt->Write("ESD_CorrEta_IsoMin_Pt",TObject::kWriteDelete);
		histoCorrEtaIso_dPhiCh_PtAssoc_PtTrig->Write("ESD_CorrEtaIso_dPhiCh_PtAssoc_PtTrig",TObject::kWriteDelete);
		histoCorrEtaIso_dEtaCh_PtAssoc_PtTrig->Write("ESD_CorrEtaIso_dEtaCh_PtAssoc_PtTrig",TObject::kWriteDelete);				
		
	fileCorrWrite->Write();
	fileCorrWrite->Close();

	delete histoCorrEta_Phi_Eta;
	delete histoCorrEta_Phi_Pt;
	delete histoCorrEta_Eta_Pt;
	delete histoCorrEta_InvMass_Pt;
	delete histoCorrEta_dPhiCh_dEtaCh;
	delete histoCorrEta_dPhiCh_dEtaCh_PtA1GeV_PtT2GeV;
	delete histoCorrEta_dPhiCh_dEtaCh_PtA1GeV_PtT5GeV;
	delete histoCorrEta_dPhiCh_PtAssoc_PtTrig;
	delete histoCorrEta_dEtaCh_PtAssoc_PtTrig;
	delete histoCorrEta_IsoCh_PtTrig;
	delete histoCorrEta_dPhiGa_dEtaGa;
	delete histoCorrEta_dPhiGa_PtAssoc_PtTrig;
	delete histoCorrEta_dEtaGa_PtAssoc_PtTrig;
	delete histoCorrEta_IsoGa_PtTrig;
	delete histoCorrEtaSideBand_Phi_Eta;
	delete histoCorrEtaSideBand_Phi_Pt;
	delete histoCorrEtaSideBand_Eta_Pt;
	delete histoCorrEtaSideBand_InvMass_Pt;
	delete histoCorrEtaSideBand_dPhiCh_dEtaCh;
	delete histoCorrEtaSideBand_dPhiCh_PtAssoc_PtTrig;
	delete histoCorrEtaSideBand_dEtaCh_PtAssoc_PtTrig;
	delete histoCorrEtaSideBand_IsoCh_PtTrig;
	delete histoCorrEtaSideBand_dPhiGa_dEtaGa;
	delete histoCorrEtaSideBand_dPhiGa_PtAssoc_PtTrig;
	delete histoCorrEtaSideBand_dEtaGa_PtAssoc_PtTrig;
	delete histoCorrEtaSideBand_IsoGa_PtTrig;
	delete histoCorrEta_IsoMin_Pt;
	delete histoCorrEtaIso_dPhiCh_PtAssoc_PtTrig;
	delete histoCorrEtaIso_dEtaCh_PtAssoc_PtTrig;
		

	
}	
