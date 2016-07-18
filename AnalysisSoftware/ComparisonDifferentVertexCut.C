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
#include "CommonHeaders/PlottingGammaConversionHistos.h"
#include "CommonHeaders/PlottingGammaConversionAdditional.h"

struct SysErrorConversion {
   Double_t value;
   Double_t error;
   //	TString name;
};



void ComparisonDifferentVertexCut(const char *suffix = "eps", TString meson = "Pi0"){

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
	prefix2 = 			"data";
	pictDrawingOptions[1] = 	kFALSE;

	TString collisionSystem = "pp @ 2.76 TeV";
	
	TString FileNameCorrected[6];
	FileNameCorrected[0] = "/home/fredi/Photon/Results/ppAnalysis2760GeVFeb2013/0000011002093663003800000_01631031009/data_GammaConversionResultsFullCorrectionNoBinShifting.root";
	FileNameCorrected[1] = "/home/fredi/Photon/Results/ppAnalysis2760GeVNovSmallerVtxCut/00000100020936630038000000_01631031009/data_GammaConversionResultsFullCorrectionNoBinShifting.root";
	FileNameCorrected[2] ="/home/fredi/Photon/Results/ppAnalysis2760GeVFeb2013/0002011002093663003800000_01631031009/data_GammaConversionResultsFullCorrectionNoBinShifting.root";
	FileNameCorrected[3] ="/home/fredi/Photon/Results/ppAnalysis2760GeVDec/00000100020936630038000000_01631031009/data_GammaConversionResultsFullCorrectionNoBinShifting.root";		FileNameCorrected[4] ="/home/fredi/Photon/Results/ppAnalysis2760GeVFeb2013/0001011002093663003800000_01631031009/data_GammaConversionResultsFullCorrectionNoBinShifting.root";
	FileNameCorrected[5] ="/home/fredi/Photon/Results/ppAnalysis2760GeVFeb2013/0000012002093663003800000_01631031009/data_GammaConversionResultsFullCorrectionNoBinShifting.root";

	TFile *Cutcorrfile[6];

	TH1D *histoSpectra2760GeV[6];
	TH1D *histoEffi2760GeV[6];
	TH1D *histoRawYield2760GeV[6];
	TH1D *histoSpectra7TeV[6];
	TH1D *histoEffi7TeV[6];
	TH1D *histoRawYield[6];

	TDirectory *directoryPi02760GeV[6];
	TDirectory *directoryPi07TeV[6];
	TH1D *histoRatioSpectra2760TeVVtx;
	TH1D *histoRatioSpectra2760TeVAddedSig;
	TH1D *histoRatioSpectra2760TeVWithSDD;
	TH1D *histoRatioSpectra2760TeVEffiFitted;
	TH1D *histoRatioSpectra2760TeVV0AND_V0OR;
	TH1D *histoRatioSpectra7TeVV0AND_V0OR;
	TH1D *histoRatioSpectra7TeVNew_Pub;
	TH1D *histoRatioEffiWithSDD;
	TH1D *histoRatioRAWYieldWithSDD;
	
	Float_t nEvt2760GeV[6];
	Float_t nEvt7TeV[6];
	TH1F *histoEventQuality2760GeV;
	TH1F *histoEventQuality7TeV;
	
	for (Int_t i=0; i< 6; i++){
		cout<< FileNameCorrected[i] << endl;
// 		if (i == 4) continue;
		Cutcorrfile[i] = new TFile(FileNameCorrected[i]);
		histoEventQuality2760GeV = (TH1F*)Cutcorrfile[i]->Get("histoNumberOfEvents2.76TeV");
		cout << "here" << endl;
		nEvt2760GeV[i] = histoEventQuality2760GeV->GetBinContent(1);
		cout << "here" << endl;
		directoryPi02760GeV[i] = 	(TDirectory*)Cutcorrfile[i]->Get("Pi02.76TeV"); 
		cout << "here" << endl;
		histoSpectra2760GeV[i] =(TH1D*)directoryPi02760GeV[i]->Get("InvCrossSectionPi0");
		cout << "here" << endl;
		histoEffi2760GeV[i] = (TH1D*)directoryPi02760GeV[i]->Get("EfficiencyPi0");
		histoRawYield2760GeV[i] = (TH1D*)directoryPi02760GeV[i]->Get("RAWYieldPerEventsPi0");
		if (i == 1 || i == 2 || i == 4 || i == 5) continue;
		histoEventQuality7TeV = (TH1F*)Cutcorrfile[i]->Get("histoNumberOfEvents7TeV");
		cout << "here" << endl;
		nEvt7TeV[i] = histoEventQuality7TeV->GetBinContent(1);
		cout << "here" << endl;
		directoryPi07TeV[i] = 	(TDirectory*)Cutcorrfile[i]->Get("Pi07TeV"); 
		cout << "here" << endl;
		histoSpectra7TeV[i] =(TH1D*)directoryPi07TeV[i]->Get("InvCrossSectionPi0");
		cout << "here" << endl;
		histoEffi7TeV[i] = (TH1D*)directoryPi07TeV[i]->Get("EfficiencyPi0");
		histoRawYield[i] = (TH1D*)directoryPi07TeV[i]->Get("RAWYieldPerEventsPi0");
	}
	cout<<"=========================="<<endl;

	histoRatioSpectra2760TeVVtx = (TH1D*) histoSpectra2760GeV[1]->Clone("histoRatioSpectra2760TeVVtx");
	histoRatioSpectra2760TeVVtx->Divide(histoSpectra2760GeV[1], histoSpectra2760GeV[0], 1.,1.,"B");
	histoRatioSpectra2760TeVAddedSig = (TH1D*) histoSpectra2760GeV[5]->Clone("histoRatioSpectra2760TeVAddedSig");
	histoRatioSpectra2760TeVAddedSig->Divide(histoSpectra2760GeV[5], histoSpectra2760GeV[0], 1.,1.,"B");
	
	histoRatioSpectra2760TeVWithSDD = (TH1D*) histoSpectra2760GeV[2]->Clone("histoRatioSpectra2760TeVWithSDD");
	histoRatioSpectra2760TeVWithSDD->Divide(histoSpectra2760GeV[2], histoSpectra2760GeV[0], 1.,1.,"B");
	histoRatioSpectra2760TeVEffiFitted = (TH1D*) histoSpectra2760GeV[3]->Clone("histoRatioSpectra2760TeVEffiFitted");
	histoRatioSpectra2760TeVEffiFitted->Divide(histoSpectra2760GeV[3], histoSpectra2760GeV[0], 1.,1.,"B");
	histoRatioSpectra7TeVNew_Pub = (TH1D*) histoSpectra7TeV[3]->Clone("histoRatioSpectra7TeVNew_Pub");
	histoRatioSpectra7TeVNew_Pub->Divide(histoSpectra7TeV[0], histoSpectra7TeV[3], 1.,1.,"B");

	histoRatioSpectra2760TeVV0AND_V0OR = (TH1D*) histoSpectra2760GeV[4]->Clone("histoRatioSpectra2760TeVV0AND_V0OR");
	histoRatioSpectra2760TeVV0AND_V0OR->Divide(histoSpectra2760GeV[4], histoSpectra2760GeV[0], 1.,1.,"B");
// 	histoRatioSpectra7TeVV0AND_V0OR = (TH1D*) histoSpectra7TeV[4]->Clone("histoRatioSpectra7TeVV0AND_V0OR");
// 	histoRatioSpectra7TeVV0AND_V0OR->Divide(histoSpectra7TeV[4], histoSpectra7TeV[0], 1.,1.,"");
	histoRatioEffiWithSDD = (TH1D*) histoEffi2760GeV[2]->Clone("histoRatioEffiWithSDD");
	histoRatioEffiWithSDD->Divide(histoEffi2760GeV[2], histoEffi2760GeV[0], 1.,1.,"");
	histoRatioRAWYieldWithSDD = (TH1D*) histoRawYield2760GeV[2]->Clone("histoRatioRAWYieldWithSDD");
	histoRatioRAWYieldWithSDD->Divide(histoRawYield2760GeV[2], histoRawYield2760GeV[0], 1.,1.,"B");
	
	cout << "V0OR, Without SDD nominal vertex cut: " << nEvt2760GeV[0] << endl;
	cout << "V0OR, Without SDD tighter vertex cut: " << nEvt2760GeV[1] << endl;
	cout << "V0OR, With SDD nominal vertex cut: " << nEvt2760GeV[2] << endl;
	cout << "V0AND: " << nEvt2760GeV[4] << endl;
	
// 	cout << "V0AND: " << nEvt7TeV[4] << endl;
	cout << "V0OR: " << nEvt7TeV[0] << endl;
	
	
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


	DrawGammaSetMarker(histoRatioSpectra2760TeVVtx, 20, 1., kBlue+2, kBlue+2);
	DrawAutoGammaMesonHistos( histoRatioSpectra2760TeVVtx,
					"", "p_{T} (GeV/c)", "#frac{N^{corr}_{#pi^{0},z_{vtx} < 5cm}}{N^{corr}_{#pi^{0},z_{vtx} < 10cm}}, pp @ 2.76TeV",
					kFALSE, 5., 10e-10, kTRUE,
					kTRUE, 0.5, 1.5,
					kTRUE, 0., 7.9);
	canvasFraction->Update();
	DrawGammaLines(0., 8.,1., 1.,0.1);

	canvasFraction->SaveAs(Form("%s_RatioCorrectedYieldDifferentVertexCuts.%s",meson.Data(),suffix));
	delete canvasFraction;

	TCanvas* canvasFraction2 = new TCanvas("canvasFraction2","",1550,1200);  // gives the page size
	canvasFraction2->SetTickx();
	canvasFraction2->SetTicky();
	canvasFraction2->SetGridx(0);
	canvasFraction2->SetGridy(0);
	canvasFraction2->SetLogy(0);
	canvasFraction2->SetLeftMargin(0.13);
	canvasFraction2->SetRightMargin(0.02);
	canvasFraction2->SetTopMargin(0.02);
	canvasFraction2->SetFillColor(0);


	DrawGammaSetMarker(histoRatioSpectra2760TeVWithSDD, 20, 1., kBlue+2, kBlue+2);
	DrawAutoGammaMesonHistos( histoRatioSpectra2760TeVWithSDD,
					"", "p_{T} (GeV/c)", "#frac{N^{corr}_{#pi^{0},with SDD}}{N^{corr}_{#pi^{0},without SDD}}, pp @ 2.76TeV",
					kFALSE, 5., 10e-10, kTRUE,
					kTRUE, 0.5, 1.5,
					kTRUE, 0., 7.9);
	canvasFraction2->Update();
	DrawGammaLines(0., 8.,1., 1.,0.1);

	canvasFraction2->SaveAs(Form("%s_RatioCorrectedYieldWithAndWithoutSDD.%s",meson.Data(),suffix));
// 	delete canvasFraction2;
	
	canvasFraction2->cd();
	DrawGammaSetMarker(histoRatioEffiWithSDD, 20, 1., kBlue+2, kBlue+2);
	DrawAutoGammaMesonHistos( histoRatioEffiWithSDD,
					"", "p_{T} (GeV/c)", "#frac{#epsilon_{#pi^{0},with SDD}}{#epsilon_{#pi^{0},without SDD}}, pp @ 2.76 TeV",
					kFALSE, 5., 10e-10, kTRUE,
					kTRUE, 0.5, 1.5,
					kTRUE, 0., 7.9);
	canvasFraction2->Update();
	DrawGammaLines(0., 8.,1., 1.,0.1);

	canvasFraction2->SaveAs(Form("%s_RatioEffiWithAndWithoutSDD.%s",meson.Data(),suffix));

	canvasFraction2->cd();
	DrawGammaSetMarker(histoRatioSpectra2760TeVEffiFitted, 20, 1., kBlue+2, kBlue+2);
	DrawAutoGammaMesonHistos( histoRatioSpectra2760TeVEffiFitted,
					"", "p_{T} (GeV/c)", "#frac{N^{corr}_{#pi^{0},effi not fitted}}{N^{corr}_{#pi^{0},effi fitted}}, pp @ 2.76 TeV ",
					kFALSE, 5., 10e-10, kTRUE,
					kTRUE, 0.5, 1.5,
					kTRUE, 0., 7.9);
	canvasFraction2->Update();
	DrawGammaLines(0., 8.,1., 1.,0.1);

	canvasFraction2->SaveAs(Form("%s_RatioCorrectedYieldEffiFitted.%s",meson.Data(),suffix));


	
	canvasFraction2->cd();
	DrawGammaSetMarker(histoRatioSpectra2760TeVAddedSig, 20, 1., kBlue+2, kBlue+2);
	DrawAutoGammaMesonHistos( histoRatioSpectra2760TeVAddedSig,
					"", "p_{T} (GeV/c)", "#frac{N^{corr}_{#pi^{0},add Sig}}{N^{corr}_{#pi^{0}}}, pp @ 2.76 TeV ",
					kFALSE, 5., 10e-10, kTRUE,
					kTRUE, 0.5, 1.5,
					kTRUE, 0., 7.9);
	canvasFraction2->Update();
	DrawGammaLines(0., 8.,1., 1.,0.1);

	canvasFraction2->SaveAs(Form("%s_RatioCorrectedYieldaddedSig.%s",meson.Data(),suffix));

	canvasFraction2->cd();
	DrawGammaSetMarker(histoRatioSpectra2760TeVV0AND_V0OR, 20, 1., kBlue+2, kBlue+2);
	DrawAutoGammaMesonHistos( histoRatioSpectra2760TeVV0AND_V0OR,
					"", "p_{T} (GeV/c)", "#frac{N^{corr}_{#pi^{0},V0AND}}{N^{corr}_{#pi^{0},V0OR}}, pp @ 2.76 TeV",
					kFALSE, 5., 10e-10, kTRUE,
					kTRUE, 0.5, 1.5,
					kTRUE, 0., 7.9);
	canvasFraction2->Update();
	DrawGammaLines(0., 8.,1., 1.,0.1);

	canvasFraction2->SaveAs(Form("%s_RatioCorrectedXSectionV0AND_VOOR.%s",meson.Data(),suffix));
// 
// 	canvasFraction2->cd();
// 	DrawGammaSetMarker(histoRatioSpectra7TeVV0AND_V0OR, 20, 1., kBlue+2, kBlue+2);
// 	DrawAutoGammaMesonHistos( histoRatioSpectra7TeVV0AND_V0OR,
// 					"", "p_{T} (GeV/c)", "#frac{N^{corr}_{#pi^{0},V0AND}}{N^{corr}_{#pi^{0},V0OR}}, pp @ 7 TeV",
// 					kFALSE, 5., 10e-10, kTRUE,
// 					kTRUE, 0.5, 1.5,
// 					kTRUE, 0., 7.9);
// 	canvasFraction2->Update();
// 	DrawGammaLines(0., 8.,1., 1.,0.1);
// 
// 	canvasFraction2->SaveAs(Form("%s_RatioCorrectedXSectionV0AND_VOOR_7TeV.%s",meson.Data(),suffix));

	canvasFraction2->cd();
	DrawGammaSetMarker(histoRatioSpectra7TeVNew_Pub, 20, 1., kBlue+2, kBlue+2);
	DrawAutoGammaMesonHistos( histoRatioSpectra7TeVNew_Pub,
					"", "p_{T} (GeV/c)", "#frac{N^{corr}_{#pi^{0},new}}{N^{corr}_{#pi^{0},pub}}, pp @ 7 TeV",
					kFALSE, 5., 10e-10, kTRUE,
					kTRUE, 0.5, 1.5,
					kTRUE, 0., 15.9);
	canvasFraction2->Update();
	DrawGammaLines(0., 16.,1., 1.,0.1);

	canvasFraction2->SaveAs(Form("%s_RatioCorrectedXSectionNew_Old_7TeV.%s",meson.Data(),suffix));

	
	
	canvasFraction2->cd();
	DrawGammaSetMarker(histoRatioRAWYieldWithSDD, 20, 1., kBlue+2, kBlue+2);
	DrawAutoGammaMesonHistos( histoRatioRAWYieldWithSDD,
					"", "p_{T} (GeV/c)", "#frac{N_{#pi^{0},with SDD}^{raw}}{N_{#pi^{0},without SDD}^{raw}}, pp @ 2.76 TeV",
					kFALSE, 5., 10e-10, kTRUE,
					kTRUE, 0.5, 1.5,
					kTRUE, 0., 7.9);
	canvasFraction2->Update();
	DrawGammaLines(0., 8.,1., 1.,0.1);

	canvasFraction2->SaveAs(Form("%s_RatioRawYieldWithAndWithoutSDD.%s",meson.Data(),suffix));

	
	canvasFraction2->cd();
	canvasFraction2->SetLeftMargin(0.09);
	canvasFraction2->SetTopMargin(0.03);
	DrawGammaSetMarker(histoEffi2760GeV[0], 20, 1., kBlue+2, kBlue+2);
	DrawAutoGammaMesonHistos( histoEffi2760GeV[0],
					"", "p_{T} (GeV/c)", "#epsilon_{#pi^{0}}",
					kTRUE, 1.5, 10e-10, kTRUE,
					kFALSE, 0.5, 1.5,
					kTRUE, 0., 7.9);
	canvasFraction2->Update();
	DrawGammaSetMarker(histoEffi2760GeV[2], 20, 1., kRed+2, kRed+2);
	histoEffi2760GeV[2]->Draw("same,p2");
// 	DrawGammaLines(0., 8.,1., 1.,0.1);
	DrawGammaSetMarker(histoEffi7TeV[3], 20, 1., kBlack, kBlack);
	histoEffi7TeV[3]->Draw("same,p2");
	TLegend* legendMultDataPP = new TLegend(0.15,0.8,0.4,0.95);
	legendMultDataPP->SetFillColor(0);
	legendMultDataPP->SetLineColor(0);
	legendMultDataPP->SetTextSize(0.04);
	legendMultDataPP->AddEntry(histoEffi2760GeV[0],"2.76TeV without SDD","p");
	legendMultDataPP->AddEntry(histoEffi2760GeV[2],"2.76TeV with SDD","p");
	legendMultDataPP->AddEntry(histoEffi7TeV[3], "7 TeV","p");
	legendMultDataPP->Draw();

	
	canvasFraction2->SaveAs(Form("%s_EffiComp.%s",meson.Data(),suffix));

}


