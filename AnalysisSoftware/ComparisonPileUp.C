/***************************************************************************************************
 ****** 	provided by Gamma Conversion Group, PWG4, 									*****
 ******		Ana Marin, marin@physi.uni-heidelberg.de								*****
 ******	   	Kathrin Koch, kkoch@physi.uni-heidelberg.de 								*****
 ******		Friederike Bock, friederike.bock@cern.ch								*****
 ****************************************************************************************************/

#include <Riostream.h>
#include <fstream>
#include "TMath.h"
#include <stdio.h>
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
#include "TVirtualFitter.h"
#include "TObject.h"
#include "TCanvas.h"
#include "TMultiGraph.h"
#include "TLegend.h"
#include "TDatabasePDG.h"
#include "TMinuit.h"
#include "TLatex.h"
#include "TASImage.h"
#include "TPostScript.h"
#include "TGraphErrors.h"
#include "TArrow.h"
#include "TMarker.h"
#include "TGraphAsymmErrors.h" 
#include "PlottingGammaConversionHistos.h"
#include "PlottingGammaConversionAdditional.h"

struct SysErrorConversion {
   Double_t value;
   Double_t error;
   //	TString name;
};



void ComparisonPileUp(const char *suffix = "gif", TString meson = "", TString isMC = "", TString optionEnergy=""){

	TString 	FileDirectory[2];
   TString 	cutNumberAdv[2];
	char* 	Input[256];
	TString 	prefix2;
	Double_t 	nColls[2];

	StyleSettingsThesis();

	SetPlotStyle();

	Bool_t pictDrawingOptions[4] = {kFALSE, kFALSE, kFALSE, kTRUE};

	TString textMeson;
	if (meson.CompareTo("Pi0")==0 || meson.CompareTo("Pi0EtaBinning")==0){
		textMeson = "#pi^{0}";
		pictDrawingOptions[3] = kTRUE;
	} else {
		pictDrawingOptions[3] = kFALSE;
		textMeson = "#eta";
	}
	if (isMC.CompareTo("kTRUE") ==0){
		prefix2 = 			"MC";
		pictDrawingOptions[1] = 	kTRUE;
	}
	else {
		prefix2 = 			"data";
		pictDrawingOptions[1] = 	kFALSE;
	}

	TString collisionSystem = collisionSystem = ReturnFullCollisionsSystem(optEnergy);
   if (collisionSystem.CompareTo("") == 0){
      cout << "No correct collision system specification, has been given" << endl;
      return;
   }
	
	cutNumberAdv[0] = "900366208010033211360000000900000000000";
   cutNumberAdv[1] = "900366208010033211361000000900000000000";

	TString FileNameCorrected[2];
	TString FileNameUnCorrected[2];

	TFile *Cutcorrfile[2];
	TFile *Cutuncorrfile[2];

	TH1D *histoRawYieldCut[2];
	TH1D *histoRatioPileUpMesons;
	TH1D *histoOnlyPileUpMesons;
	TH1D *histoAllMesons;
	TH1D *histoOnlyWithoutPileUpMesons;
	
	Float_t nEvt[2];
	TH1F *histoEventQuality;

	for (Int_t i=0; i< 2; i++){

		FileNameCorrected[i] = Form("%s_%s_AnalysisResultsCorrection_%s.root", meson.Data(),prefix2.Data(),cutNumberAdv[i].Data());
		cout<< FileNameCorrected[i] << endl;
		Cutcorrfile[i] = new TFile(FileNameCorrected[i]);
		FileNameUnCorrected[i] = Form("%s_%s_AnalysisResultsWithoutCorrection_%s.root",meson.Data(),prefix2.Data(),cutNumberAdv[i].Data());
		cout<< FileNameUnCorrected[i] << endl;
		Cutuncorrfile[i] = new TFile(FileNameUnCorrected[i]);

		histoEventQuality = (TH1F*)Cutcorrfile[i]->Get("ESD_EventQuality");
		nEvt[i] = histoEventQuality->GetEntries() -histoEventQuality->GetBinContent(4) - histoEventQuality->GetBinContent(6);

		histoRawYieldCut[i] =(TH1D*)Cutuncorrfile[i]->Get("histoYieldMeson");
		histoRawYieldCut[i]->SetName(Form("histoYieldMeson%s",cutNumberAdv[i].Data()));

	}
	cout<<"=========================="<<endl;

	histoOnlyPileUpMesons = (TH1D*) histoRawYieldCut[0]->Clone("histoOnlyPileUpMesons");
	histoOnlyPileUpMesons->Sumw2();
	histoOnlyPileUpMesons->Add(histoRawYieldCut[1], -1);
	histoOnlyPileUpMesons->Scale(1./(nEvt[0]-nEvt[1]));
	
	histoAllMesons = (TH1D*) histoRawYieldCut[0]->Clone("histoAllMesons");
	histoAllMesons->Sumw2();
	histoAllMesons->Scale(1./nEvt[0]);
	
	histoOnlyWithoutPileUpMesons = (TH1D*) histoRawYieldCut[1]->Clone("histoOnlyWithoutPileUpMesons");
	histoOnlyWithoutPileUpMesons->Sumw2();
	histoOnlyWithoutPileUpMesons->Scale(1./nEvt[1]);
	
	
	histoRatioPileUpMesons = (TH1D*) histoOnlyPileUpMesons->Clone("histoRatioPileUpMesons");
	histoRatioPileUpMesons->Divide(histoRatioPileUpMesons, histoAllMesons, 1.,1.,"");
	
	cout << histoOnlyPileUpMesons->Integral() << "\t" << histoAllMesons->Integral() << "\t" << histoOnlyWithoutPileUpMesons->Integral() << "\t" << histoOnlyPileUpMesons->Integral()/histoAllMesons->Integral()<<"\t" << histoOnlyPileUpMesons->Integral()/histoOnlyWithoutPileUpMesons->Integral() << endl;
	//**************************************************************************************
	//********************* Plotting RAW-Yield *********************************************
	//**************************************************************************************

	TCanvas* canvasFraction = new TCanvas("canvasFraction","",1550,1200);  // gives the page size
	canvasFraction->SetTickx();
	canvasFraction->SetTicky();
	canvasFraction->SetGridx(0);
	canvasFraction->SetGridy(0);
	canvasFraction->SetLogy(0);
	canvasFraction->SetLeftMargin(0.13);
	canvasFraction->SetRightMargin(0.02);
	canvasFraction->SetTopMargin(0.02);
	canvasFraction->SetFillColor(0);


	DrawGammaSetMarker(histoRatioPileUpMesons, 20, 1., kBlue+2, kBlue+2);
	DrawAutoGammaMesonHistos( histoRatioPileUpMesons,
					"", "p_{t} (GeV/c)", "#frac{N_{#pi^{0},PileUp}/N_{evt,PileUp}}{N_{#pi^{0},All}/N_{evt,All}}",
					kFALSE, 5., 10e-10, kTRUE,
					kTRUE, 0.0, 4.,
					kFALSE, 0., 10.);
	canvasFraction->Update();

	canvasFraction->SaveAs(Form("%s_FractionInPileUp.%s",meson.Data(),suffix));
	delete canvasFraction;

	TCanvas* canvasRawYieldMeson = new TCanvas("canvasRawYieldMeson","",1550,1200);  // gives the page size
	canvasRawYieldMeson->SetTickx();
	canvasRawYieldMeson->SetTicky();
	canvasRawYieldMeson->SetGridx(0);
	canvasRawYieldMeson->SetGridy(0);
	canvasRawYieldMeson->SetLogy(1);
	canvasRawYieldMeson->SetLeftMargin(0.13);
	canvasRawYieldMeson->SetRightMargin(0.02);
	canvasRawYieldMeson->SetTopMargin(0.02);
	canvasRawYieldMeson->SetFillColor(0);


	DrawGammaSetMarker(histoOnlyPileUpMesons, 20, 1., kBlue+2, kBlue+2);
	DrawAutoGammaMesonHistos( histoOnlyPileUpMesons,
					"", "p_{t} (GeV/c)", "RAW Yield",
					kTRUE, 5., 10e-10, kTRUE,
					kFALSE, 0.0, 4.,
					kFALSE, 0., 10.);
	DrawGammaSetMarker(histoAllMesons, 20, 1., kBlack, kBlack);
	histoAllMesons->Draw("same,pe1");
	canvasRawYieldMeson->Update();

	canvasRawYieldMeson->SaveAs(Form("%s_RawYield.%s",meson.Data(),suffix));
	delete canvasRawYieldMeson;
}


