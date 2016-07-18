/****************************************************************************************************************************
 ****** 	provided by Gamma Conversion Group, PWG4, 														*****
 ******		Ana Marin, marin@physi.uni-heidelberg.de													*****
 ******	   	Kathrin Koch, kkoch@physi.uni-heidelberg.de 													*****
 ******		Friederike Bock, friederike.bock@cern.ch													*****
 *****************************************************************************************************************************/

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
#include "CommonHeaders/PlottingGammaConversionHistos.h"
#include "CommonHeaders/PlottingGammaConversionAdditional.h"


extern TRandom*	gRandom;
extern TBenchmark*	gBenchmark;
extern TSystem*	gSystem;
extern TMinuit*  	gMinuit;

struct SysErrorConversion {
	Double_t value;
	Double_t error;
	//	TString name;
};

void  CombineMCAndData(const char *fileNamePi0Data = "myOutput", const char *fileNameMC = "", TString suffix ="eps"){	
	
	gROOT->Reset();	
	gROOT->SetStyle("Plain");
	
	StyleSettingsThesis();	
	SetPlotStyle();

	TFile* fileConversionsData = 		new TFile(fileNamePi0Data);
	TDirectory* directoryPi07TeV = 			(TDirectory*)fileConversionsData->Get("Pi07TeV"); 
	TDirectory* directoryEta7TeV = 			(TDirectory*)fileConversionsData->Get("Eta7TeV");
	TH1D* histoInvCrossSectionPi0= 				(TH1D*)directoryPi07TeV->Get("InvCrossSectionPi0");
	TH1D* histoInvCrossSectionEta= 				(TH1D*)directoryEta7TeV->Get("InvCrossSectionEta");

	TFile* fileConversionsMC = 		new TFile(fileNameMC);
	TDirectory* directoryPi07TeVMC = 			(TDirectory*)fileConversionsMC->Get("Pi07TeV"); 
	TDirectory* directoryEta7TeVMC = 			(TDirectory*)fileConversionsMC->Get("Eta7TeV");
	TH1D* histoInvCrossSectionPi0MC= 				(TH1D*)directoryPi07TeVMC->Get("InvCrossSectionPi0");
	TH1D* histoInvCrossSectionEtaMC= 				(TH1D*)directoryEta7TeVMC->Get("InvCrossSectionEta");
	
	TCanvas* canvasInvXSectionRatioPi0 = new TCanvas("canvasInvXSectionRatioPi0","",200,10,1200,700);  // gives the page size
	DrawGammaCanvasSettings( canvasInvXSectionRatioPi0,  0.08, 0.01, 0.015, 0.13);

	canvasInvXSectionRatioPi0->SetLogx();
	TH2F * ratio2DInvXSectionPi0;
	ratio2DInvXSectionPi0 = new TH2F("ratio2DInvXSectionPi0","ratio2DInvXSectionPi0",1000,0.,30.,1000,0.35,1.85);
	SetStyleHistoTH2ForGraphs(ratio2DInvXSectionPi0, "p_{t} (GeV/c)","Data/Fit", 0.05,0.07, 0.05,0.07, 0.8,0.6, 512, 505);
	ratio2DInvXSectionPi0->DrawCopy(); 
	
	DrawGammaSetMarker(histoInvCrossSectionPi0, 20,1., kBlack , kBlack);
	histoInvCrossSectionPi0->Draw("same,p");
	
	DrawGammaSetMarker(histoInvCrossSectionPi0MC, 20,1., kRed , kRed);
	histoInvCrossSectionPi0MC->Draw("same,p");
	
	canvasInvXSectionRatioPi0->Update();
	canvasInvXSectionRatioPi0->Print(Form("InvXSection_OnlyRatioEta7TeV_Paper.%s",suffix.Data()));

		
}
