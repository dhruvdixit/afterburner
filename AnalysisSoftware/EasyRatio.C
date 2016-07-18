// provided by Gamma Conversion Group, PWGGA, Lucia Leardini lucia.leardini@cern.ch
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
#include "CommonHeaders/FittingGammaConversion.h"
#include "CommonHeaders/ConversionFunctions.h"
#include "CommonHeaders/ConversionFunctionsBasicsAndLabeling.h"

void EasyRatio(TString input = "",TString Centrality = "0-10%", TString fileDir = "",  TString label = "", TString meson = "", TString prefix2 = "", Int_t VariationsNumber = 2, TString suffix = "pdf", TString outputDir = ""){


	TString 	VariationAdv[50] = {"NotFlat","Flat"};
	TString 	Variation[50] = {"NotFlat","Flat"};
	TString 	LabelNames[2] = {"BG with THnSparse", "BG with TH2"};
	
	Color_t color[20] = {kBlack, kAzure, kGreen+2, kOrange+2, kRed, kViolet, kBlue-9, kSpring+10, kCyan+3, kCyan-10, kCyan, kGreen+4, kGreen-9, kGreen, kYellow+4, kYellow+3, kMagenta+4, kMagenta-8};

	Bool_t pictDrawingOptions[4] = {kFALSE, kFALSE, kFALSE, kTRUE};
	Float_t pictDrawingCoordinates[9] = {0.55, 0.8, 0.25, 0.04, 0.7,0.5, 0.18, 0.035,0};

//    ifstream in(input.Data());
//    cout << "Variations: " << endl;
//    string TempVariation;
//    Int_t Number1 = 0;
//    while(getline(in, TempVariation)){
//       TString tempVariationAdv = TempVariation;
//       TString tempVariation(tempVariationAdv(0,12));
//       VariationAdv[Number1] = tempVariationAdv;
// 
//       Variation[Number1] = LabelNames[Number1]; //tempVariation;
// 	   cout << "************************************************"  << endl;
//            cout << Variation[Number1].Data() << endl;
// 	   cout << VariationAdv[Number1].Data() << endl;
// 	   cout << "************************************************"  << endl;
//       Number1++;
//    }

	TString 	cutNumber[50];
	TString 	cutNumberAdv[50] = {"5010001_00200009247602008250400000_01525065000000", "5010001_00200009247602008250400000_01525065000000"};

	TString inputString = "due.txt";
	ifstream in2(inputString.Data());
	cout<<"Available Cuts:"<<endl;
	string TempCutNumber;
	Int_t Number = 0;
	//	while(getline(in2, TempCutNumber)){
	//		TString tempCutNumberAdv = TempCutNumber;
	//// 		TString tempCutNumber(tempCutNumberAdv(0,58));
	//		cutNumberAdv[Number] = tempCutNumberAdv;
	//		cutNumber[Number] = tempCutNumberAdv;
	//		cout<< cutNumber[Number]<<endl;
	//		Number++;
	//	}
	cout<<"=========================="<<endl;


	TString textMeson;
	if (meson.CompareTo("Pi0")==0 || meson.CompareTo("Pi0EtaBinning")==0){
	textMeson = "#pi^{0}";
	pictDrawingOptions[3] = kTRUE;
	} else {
	pictDrawingOptions[3] = kFALSE;
	textMeson = "#eta";
	}

	const Int_t ConstVariations = VariationsNumber;
	TString FileNameCorrected[ConstVariations];
	TString FileNameUnCorrected[ConstVariations];

	TFile *Cutcorrfile[ConstVariations];
	TFile *Cutuncorrfile[ConstVariations];

	TH1D *histoCorrectedYield[ConstVariations];
	TH1D *histoRawYield[ConstVariations];
	TH1D *histoSign[ConstVariations];
	TH1D *histoEfficiency[ConstVariations];
	TH1D *histoRatioCorrectedYield[ConstVariations];
	TH1D *histoRatioRawYield[ConstVariations];
	TH1D *histoRatioSign[ConstVariations];
	TH1D *histoRatioEfficiency[ConstVariations];

	Float_t nEvt[ConstVariations];
	TH1F *histoEventQuality[ConstVariations];
	TString centralityString;

	for (Int_t i=0; i< VariationsNumber; i++){

	cout<<"=========================="<<endl;
	cout<<"Fetching histograms"<<endl; 

	FileNameCorrected[i] = Form("%s/%s/%s/PbPb_2.76TeV/%s_%s_GammaConvV1Correction_%s.root",fileDir.Data(),VariationAdv[i].Data(),cutNumberAdv[i].Data(),meson.Data(),prefix2.Data(),cutNumberAdv[i].Data());
	cout<< FileNameCorrected[i] << endl;
	Cutcorrfile[i] = new TFile(FileNameCorrected[i]);
	if (Cutcorrfile[i]->IsZombie()) return;
	FileNameUnCorrected[i] = Form("%s/%s/%s/PbPb_2.76TeV/%s_%s_GammaConvV1WithoutCorrection_%s.root",fileDir.Data(),VariationAdv[i].Data(),cutNumberAdv[i].Data(),meson.Data(),prefix2.Data(),cutNumberAdv[i].Data());
	cout<< FileNameUnCorrected[i] << endl;
	Cutuncorrfile[i] = new TFile(FileNameUnCorrected[i]);
	if (Cutuncorrfile[i]->IsZombie()) return;

	TString nameCorrectedYield = "CorrectedYieldTrueEff";
	histoCorrectedYield[i] =(TH1D*)Cutcorrfile[i]->Get(nameCorrectedYield.Data());
	histoCorrectedYield[i]->SetName(Form("CorrectedYieldTrueEff_%s",cutNumberAdv[i].Data()));
	histoRawYield[i] =(TH1D*)Cutuncorrfile[i]->Get("histoYieldMesonPerEvent");
	histoRawYield[i]->SetName(Form("histoYieldMesonPerEvent_%s",cutNumberAdv[i].Data()));
	//histoRawYield[i]->Scale(1./nEvt[i]);
	histoSign[i] =(TH1D*)Cutuncorrfile[i]->Get("Mapping_BckNorm_InvMass_in_Pt_Bin08");
	histoSign[i]->SetName(Form("histoback_%s",cutNumberAdv[i].Data()));
	histoEfficiency[i] =(TH1D*)Cutcorrfile[i]->Get("TrueMesonEffiPt");
	histoEfficiency[i]->SetName(Form("TrueEff_%s",cutNumberAdv[i].Data()));

	histoRatioCorrectedYield[i] = (TH1D*) histoCorrectedYield[i]->Clone(Form("histoRatioCorrectedYield_%s",cutNumberAdv[i].Data()));
	histoRatioCorrectedYield[i]->Divide(histoRatioCorrectedYield[i],histoCorrectedYield[0],1.,1.,"B");

	histoRatioRawYield[i] = (TH1D*) histoRawYield[i]->Clone(Form("histoRatioRawYield_%s",cutNumberAdv[i].Data()));
	histoRatioRawYield[i]->Divide(histoRatioRawYield[i],histoRawYield[0],1.,1.,"B");

	histoRatioSign[i] = (TH1D*) histoSign[i]->Clone(Form("histoRatioback_%s",cutNumberAdv[i].Data()));
	histoRatioSign[i]->Divide(histoRatioSign[i],histoSign[0],1.,1.,"B");

	histoRatioEfficiency[i] = (TH1D*) histoEfficiency[i]->Clone(Form("histoRatioEfficiency_%s",cutNumberAdv[i].Data()));
	histoRatioEfficiency[i]->Divide(histoRatioEfficiency[i],histoEfficiency[0],1.,1.,"B");

	}
	cout<<"=========================="<<endl;


	//**************************************************************************************
	//********************* Plotting RAW-Yield *********************************************
	//**************************************************************************************

	TCanvas* canvasRawYieldMeson = new TCanvas("canvasRawYieldMeson","",1350,1500);  // gives the page size
	canvasRawYieldMeson->SetTickx();
	canvasRawYieldMeson->SetTicky();
	canvasRawYieldMeson->SetGridx(0);
	canvasRawYieldMeson->SetGridy(0);
	canvasRawYieldMeson->SetLogy(0);
	canvasRawYieldMeson->SetLeftMargin(0.13);
	canvasRawYieldMeson->SetRightMargin(0.02);
	canvasRawYieldMeson->SetTopMargin(0.02);
	canvasRawYieldMeson->SetFillColor(0);

	TPad* padRawYield = new TPad("padRawYield", "", 0., 0.33, 1., 1.,-1, -1, -2);
	padRawYield->SetFillColor(0);
	padRawYield->GetFrame()->SetFillColor(0);
	padRawYield->SetBorderMode(0);
	padRawYield->SetLeftMargin(0.12);
	padRawYield->SetBottomMargin(0.);
	padRawYield->SetRightMargin(0.02);
	padRawYield->SetTopMargin(0.04);
	padRawYield->SetLogy();
	padRawYield->Draw();

	TPad* padRawYieldRatios = new TPad("padRawYieldRatios", "", 0., 0., 1., 0.33,-1, -1, -2);
	padRawYieldRatios->SetFillColor(0);
	padRawYieldRatios->GetFrame()->SetFillColor(0);
	padRawYieldRatios->SetBorderMode(0);
	padRawYieldRatios->SetLeftMargin(0.12);
	padRawYieldRatios->SetBottomMargin(0.25);
	padRawYieldRatios->SetRightMargin(0.02);
	padRawYieldRatios->SetTopMargin(0.);
	padRawYieldRatios->Draw();

	padRawYield->cd();
	padRawYield->SetTickx();
	padRawYield->SetTicky();

	TLegend* legendRawMeson = new TLegend(0.15,0.02,0.3,0.3);
	legendRawMeson->SetTextSize(0.03);
	legendRawMeson->SetFillColor(0);
	legendRawMeson->SetLineColor(0);
	for(Int_t i = 0; i< VariationsNumber; i++){
		if(i == 0){
			DrawGammaSetMarker(histoRawYield[i], 20, 1., color[0], color[0]);
			DrawAutoGammaMesonHistos( histoRawYield[i],
				"", "p_{T} (GeV/c)", Form("%s RAW Yield/N_{ev}",textMeson.Data()),
				kTRUE, 5., 10e-10, kTRUE,
				kFALSE, 0.0, 0.030,
				kFALSE, 0., 10.);
			legendRawMeson->AddEntry(histoRawYield[i],Form("standard: %s",Variation[i].Data()));
		} else {
			if(i<20){
				DrawGammaSetMarker(histoRawYield[i], 20+i, 1.,color[i],color[i]);
			} else {
				DrawGammaSetMarker(histoRawYield[i], 20+i, 1.,color[i-20],color[i]);
			}
			histoRawYield[i]->DrawCopy("same,e1,p");
			legendRawMeson->AddEntry(histoRawYield[i],Variation[i].Data());
		}
	}
	legendRawMeson->Draw();
	TLatex *labelCollisionSystem = new TLatex(0.55,0.91,"PbPb_2.76TeV");
	SetStyleTLatex( labelCollisionSystem, 0.038,4);
	labelCollisionSystem->Draw();

	TLatex *labelcentrality = new TLatex(0.55,0.81,Form("%s",Centrality.Data()));
	SetStyleTLatex( labelcentrality, 0.038,4);
	labelcentrality->Draw();   

	padRawYieldRatios->cd();
	padRawYieldRatios->SetTickx();
	padRawYieldRatios->SetTicky();

	for(Int_t i = 0; i< VariationsNumber; i++){
		if(i==0){
			for(Int_t b = 0; b< histoRatioRawYield[i]->GetNbinsX(); b++){
				histoRatioRawYield[i]->SetXTitle("p_{T} (GeV/c)");
				histoRatioRawYield[i]->SetYTitle("#frac{modified}{standard}");
				histoRatioRawYield[i]->GetYaxis()->SetRangeUser(0.7,1.3);

				histoRatioRawYield[i]->GetYaxis()->SetLabelSize(0.07);
				histoRatioRawYield[i]->GetYaxis()->SetNdivisions(505);
				histoRatioRawYield[i]->GetYaxis()->SetTitleSize(0.1);
				histoRatioRawYield[i]->GetYaxis()->SetDecimals();
				histoRatioRawYield[i]->GetYaxis()->SetTitleOffset(0.5);
				histoRatioRawYield[i]->GetXaxis()->SetTitleSize(0.11);
				histoRatioRawYield[i]->GetXaxis()->SetLabelSize(0.08);
				histoRatioRawYield[i]->SetMarkerStyle(22);
				histoRatioRawYield[i]->SetMarkerSize(1.);
				histoRatioRawYield[i]->SetMarkerColor(color[0]);
				histoRatioRawYield[i]->SetLineColor(color[0]);
				DrawGammaSetMarker(histoRatioRawYield[i], 20, 1., 1, 1);

				// 			 histoRatioRawYield[i]->SetBinError(b+1,histoRawYield[i]->GetBinError(b+1)/histoRawYield[i]->GetBinContent(b+1));
				// 			 histoRatioRawYield[i]->SetFillColor(1);
				// 			 histoRatioRawYield[i]->SetFillStyle(0);
				histoRatioRawYield[i]->DrawCopy("p,e2");
			}
		} else{
			if(i<20){
				DrawGammaSetMarker(histoRatioRawYield[i], 20+i, 1.,color[i],color[i]);
			} else {
				DrawGammaSetMarker(histoRatioRawYield[i], 20+i, 1.,color[i-20],color[i]);
			}
			histoRatioRawYield[i]->DrawCopy("same,e1,p");
		}
	}
	canvasRawYieldMeson->Update();
	canvasRawYieldMeson->SaveAs(Form("%s/%s_%s_RAWYield_%s.%s",outputDir.Data(),meson.Data(),prefix2.Data(),label.Data(),suffix.Data()));
	delete canvasRawYieldMeson;



	//**************************************************************************************
	//********************* Plotting RAW-Yield *********************************************
	//**************************************************************************************

	TCanvas* canvasSignMeson = new TCanvas("canvasSignMeson","",1350,1500);  // gives the page size
	canvasSignMeson->SetTickx();
	canvasSignMeson->SetTicky();
	canvasSignMeson->SetGridx(0);
	canvasSignMeson->SetGridy(0);
	canvasSignMeson->SetLogy(0);
	canvasSignMeson->SetLeftMargin(0.13);
	canvasSignMeson->SetRightMargin(0.02);
	canvasSignMeson->SetTopMargin(0.02);
	canvasSignMeson->SetFillColor(0);

	TPad* padSign = new TPad("padSign", "", 0., 0.33, 1., 1.,-1, -1, -2);
	padSign->SetFillColor(0);
	padSign->GetFrame()->SetFillColor(0);
	padSign->SetBorderMode(0);
	padSign->SetLeftMargin(0.15);
	padSign->SetBottomMargin(0.);
	padSign->SetRightMargin(0.02);
	padSign->SetTopMargin(0.04);
	//padSign->SetLogy();
	padSign->Draw();

	TPad* padSignRatios = new TPad("padSignRatios", "", 0., 0., 1., 0.33,-1, -1, -2);
	padSignRatios->SetFillColor(0);
	padSignRatios->GetFrame()->SetFillColor(0);
	padSignRatios->SetBorderMode(0);
	padSignRatios->SetLeftMargin(0.15);
	padSignRatios->SetBottomMargin(0.3);
	padSignRatios->SetRightMargin(0.02);
	padSignRatios->SetTopMargin(0.);
	padSignRatios->Draw();

	padSign->cd();
	padSign->SetTickx();
	padSign->SetTicky();

	TLegend* legendSign = new TLegend(0.45,0.02,0.42,0.3);
	legendSign->SetTextSize(0.03);
	legendSign->SetFillColor(0);
	legendSign->SetLineColor(0);
	for(Int_t i = 0; i< VariationsNumber; i++){
		if(i == 0){
			DrawGammaSetMarker(histoSign[i], 20, 1., color[0], color[0]);
			DrawAutoGammaMesonHistos( histoSign[i],
				"", "p_{T} (GeV/c)", Form("%s backgorund (norm.)",textMeson.Data()),
				kFALSE, 5., 10e-10, kFALSE,
				kTRUE, 0.001, 3.5e5,
				kFALSE, 0., 10.);
			legendSign->AddEntry(histoSign[i],Form("standard: %s",Variation[i].Data()));
		} else {
			if(i<20){
				DrawGammaSetMarker(histoSign[i], 20+i, 1.,color[i],color[i]);
			} else {
				DrawGammaSetMarker(histoSign[i], 20+i, 1.,color[i-20],color[i]);
			}
			histoSign[i]->DrawCopy("same,e1,p");
			legendSign->AddEntry(histoSign[i],Variation[i].Data());
		}
	}
	legendSign->Draw();
	labelCollisionSystem->Draw();
	labelcentrality->Draw();   

	padSignRatios->cd();
	padSignRatios->SetTickx();
	padSignRatios->SetTicky();

	for(Int_t i = 0; i< VariationsNumber; i++){
		if(i==0){
			for(Int_t b = 0; b< histoRatioSign[i]->GetNbinsX(); b++){
				histoRatioSign[i]->SetYTitle("#frac{modified}{standard}");
				histoRatioSign[i]->GetYaxis()->SetRangeUser(0.97,1.03);

				histoRatioSign[i]->GetYaxis()->SetLabelSize(0.07);
				histoRatioSign[i]->GetYaxis()->SetNdivisions(505);
				histoRatioSign[i]->GetYaxis()->SetTitleSize(0.1);
				histoRatioSign[i]->GetYaxis()->SetDecimals();
				histoRatioSign[i]->GetYaxis()->SetTitleOffset(0.6);
				histoRatioSign[i]->GetXaxis()->SetTitleSize(0.11);
				histoRatioSign[i]->GetXaxis()->SetLabelSize(0.08);
				histoRatioSign[i]->SetMarkerStyle(22);
				histoRatioSign[i]->SetMarkerSize(1.);
				histoRatioSign[i]->SetMarkerColor(color[0]);
				histoRatioSign[i]->SetLineColor(color[0]);
				DrawGammaSetMarker(histoRatioSign[i], 20, 1., 1, 1);

				// 			 histoRatioSign[i]->SetBinError(b+1,histoSign[i]->GetBinError(b+1)/histoSign[i]->GetBinContent(b+1));
				// 			 histoRatioSign[i]->SetFillColor(1);
				// 			 histoRatioSign[i]->SetFillStyle(0);
				histoRatioSign[i]->DrawCopy("p,e2");
			}
		} else{
			if(i<20){
				DrawGammaSetMarker(histoRatioSign[i], 20+i, 1.,color[i],color[i]);
			} else {
				DrawGammaSetMarker(histoRatioSign[i], 20+i, 1.,color[i-20],color[i]);
			}
			histoRatioSign[i]->DrawCopy("same,e1,p");
		}
	}
	canvasSignMeson->Update();
	//canvasSignMeson->SaveAs(Form("%s/%s_%s_back_%s.%s",outputDir.Data(),meson.Data(),prefix2.Data(),label.Data(),suffix.Data()));
	delete canvasSignMeson;


	//*****************************************************************************************
	//******************* Compare Corrected Yields ********************************************
	//*****************************************************************************************
	TCanvas* canvasCorrectedYieldMeson = new TCanvas("canvasCorrectedYieldMeson","",1350,1500);  // gives the page size
	canvasCorrectedYieldMeson->SetTickx();
	canvasCorrectedYieldMeson->SetTicky();
	canvasCorrectedYieldMeson->SetGridx(0);
	canvasCorrectedYieldMeson->SetGridy(0);
	canvasCorrectedYieldMeson->SetLogy(0);
	canvasCorrectedYieldMeson->SetLeftMargin(0.13);
	canvasCorrectedYieldMeson->SetRightMargin(0.02);
	canvasCorrectedYieldMeson->SetTopMargin(0.02);
	canvasCorrectedYieldMeson->SetFillColor(0);

	TPad* padCorrectedYield = new TPad("padCorrectedYield", "", 0., 0.33, 1., 1.,-1, -1, -2);
	padCorrectedYield->SetFillColor(0);
	padCorrectedYield->GetFrame()->SetFillColor(0);
	padCorrectedYield->SetBorderMode(0);
	padCorrectedYield->SetLeftMargin(0.12);
	padCorrectedYield->SetBottomMargin(0.);
	padCorrectedYield->SetRightMargin(0.02);
	padCorrectedYield->SetTopMargin(0.02);
	padCorrectedYield->SetLogy(1);
	padCorrectedYield->Draw();

	TPad* padCorrectedYieldRatios = new TPad("padCorrectedYieldRatios", "", 0., 0., 1., 0.33,-1, -1, -2);
	padCorrectedYieldRatios->SetFillColor(0);
	padCorrectedYieldRatios->GetFrame()->SetFillColor(0);
	padCorrectedYieldRatios->SetBorderMode(0);
	padCorrectedYieldRatios->SetLeftMargin(0.12);
	padCorrectedYieldRatios->SetBottomMargin(0.2);
	padCorrectedYieldRatios->SetRightMargin(0.02);
	padCorrectedYieldRatios->SetTopMargin(0.);
	padCorrectedYieldRatios->SetLogy(1);
	padCorrectedYieldRatios->Draw();

	padCorrectedYield->cd();
	padCorrectedYield->SetTickx();
	padCorrectedYield->SetTicky();
	padCorrectedYield->SetLogy(1);

	TLegend* legendCorrectedYieldMeson = new TLegend(0.15,0.02,0.3,0.3);
	legendCorrectedYieldMeson->SetTextSize(0.03);
	legendCorrectedYieldMeson->SetFillColor(0);
	legendCorrectedYieldMeson->SetLineColor(0);

	for(Int_t i = 0; i< VariationsNumber; i++){
		if(i == 0){
			DrawAutoGammaMesonHistos( histoCorrectedYield[i],
				"", "p_{T} (GeV/c)", "#frac{1}{2#pi N_{ev.}} #frac{d^{2}N}{p_{T}dp_{T}dy} (c/GeV)",
				kTRUE, 5., 5e-10,kTRUE,
				kFALSE, 0.0, 0.030,
				kFALSE, 0., 10.);
			DrawGammaSetMarker(histoCorrectedYield[i], 20, 1., color[0], color[0]);
			histoCorrectedYield[i]->DrawCopy("e1,p");
			legendCorrectedYieldMeson->AddEntry(histoCorrectedYield[i], Form("standard: %s",Variation[i].Data()));
		} else{
			if(i<20){
				DrawGammaSetMarker(histoCorrectedYield[i], 20+i, 1.,color[i],color[i]);
			} else {
				DrawGammaSetMarker(histoCorrectedYield[i], 20+i, 1.,color[i-20],color[i]);
			}
			histoCorrectedYield[i]->DrawCopy("same,e1,p");
			legendCorrectedYieldMeson->AddEntry(histoCorrectedYield[i], Variation[i].Data());
		}
	}
	legendCorrectedYieldMeson->Draw();
	labelCollisionSystem->Draw();
	labelcentrality->Draw();

	padCorrectedYieldRatios->cd();
	padCorrectedYieldRatios->SetTickx();
	padCorrectedYieldRatios->SetTicky();
	padCorrectedYieldRatios->SetLogy(0);

	for(Int_t i = 0; i< VariationsNumber; i++){
		if(i==0){
			for(Int_t b = 0; b< histoRatioCorrectedYield[i]->GetNbinsX(); b++){
				histoRatioCorrectedYield[i]->SetYTitle("#frac{modified}{standard}");
				histoRatioCorrectedYield[i]->SetXTitle("p_{T} (GeV/c)");
				histoRatioCorrectedYield[i]->GetYaxis()->SetRangeUser(0.45,1.55);

				histoRatioCorrectedYield[i]->GetYaxis()->SetLabelSize(0.07);
				histoRatioCorrectedYield[i]->GetYaxis()->SetNdivisions(505);
				histoRatioCorrectedYield[i]->GetYaxis()->SetTitleSize(0.1);
				histoRatioCorrectedYield[i]->GetYaxis()->SetDecimals();
				histoRatioCorrectedYield[i]->GetYaxis()->SetTitleOffset(0.5);
				histoRatioCorrectedYield[i]->GetXaxis()->SetTitleSize(0.11);
				histoRatioCorrectedYield[i]->GetXaxis()->SetLabelSize(0.08);
				histoRatioCorrectedYield[i]->SetMarkerStyle(22);
				histoRatioCorrectedYield[i]->SetMarkerSize(1.);
				histoRatioCorrectedYield[i]->SetMarkerColor(color[0]);
				histoRatioCorrectedYield[i]->SetLineColor(color[0]);

				DrawGammaSetMarker(histoRatioCorrectedYield[i], 20, 1., 1, 1);
				//        	histoRatioCorrectedYield[i]->SetBinError(b+1,histoCorrectedYield[i]->GetBinError(b+1)/histoCorrectedYield[i]->GetBinContent(b+1));
				// 		histoRatioCorrectedYield[i]->SetFillColor(1);
				// 		histoRatioCorrectedYield[i]->SetFillStyle(0);
				histoRatioCorrectedYield[i]->DrawCopy("p,e2");
			}		
		} else{
			if(i<20){
				DrawGammaSetMarker(histoRatioCorrectedYield[i], 20+i, 1.,color[i],color[i]);
			} else {
				DrawGammaSetMarker(histoRatioCorrectedYield[i], 20+i, 1.,color[i-20],color[i]);
			}
			histoRatioCorrectedYield[i]->DrawCopy("same,e1,p");
			cout << "problem?" << endl;
		}
	}
	canvasCorrectedYieldMeson->Update();
	canvasCorrectedYieldMeson->SaveAs(Form("%s/%s_%s_CorrectedYield_%s.%s",outputDir.Data(), meson.Data(),prefix2.Data(),label.Data(),suffix.Data()));
	delete canvasCorrectedYieldMeson;


	//*****************************************************************************************
	//**********************  Compare Efficiency  *********************************************
	//*****************************************************************************************
	TCanvas* canvasEfficiencyMeson = new TCanvas("canvasEfficiencyMeson","",1350,1500);  // gives the page size
	canvasEfficiencyMeson->SetTickx();
	canvasEfficiencyMeson->SetTicky();
	canvasEfficiencyMeson->SetGridx(0);
	canvasEfficiencyMeson->SetGridy(0);
	//canvasEfficiencyMeson->SetLogy(0);
	canvasEfficiencyMeson->SetLeftMargin(0.13);
	canvasEfficiencyMeson->SetRightMargin(0.02);
	canvasEfficiencyMeson->SetTopMargin(0.02);
	canvasEfficiencyMeson->SetFillColor(0);

	TPad* padEfficiency = new TPad("padEfficiency", "", 0., 0.33, 1., 1.,-1, -1, -2);
	padEfficiency->SetFillColor(0);
	padEfficiency->GetFrame()->SetFillColor(0);
	padEfficiency->SetBorderMode(0);
	padEfficiency->SetLeftMargin(0.12);
	padEfficiency->SetBottomMargin(0.);
	padEfficiency->SetRightMargin(0.02);
	padEfficiency->SetTopMargin(0.02);
	//padEfficiency->SetLogy(1);
	padEfficiency->Draw();

	TPad* padEfficiencyRatios = new TPad("padEfficiencyRatios", "", 0., 0., 1., 0.33,-1, -1, -2);
	padEfficiencyRatios->SetFillColor(0);
	padEfficiencyRatios->GetFrame()->SetFillColor(0);
	padEfficiencyRatios->SetBorderMode(0);
	padEfficiencyRatios->SetLeftMargin(0.12);
	padEfficiencyRatios->SetBottomMargin(0.2);
	padEfficiencyRatios->SetRightMargin(0.02);
	padEfficiencyRatios->SetTopMargin(0.);
	//padEfficiencyRatios->SetLogy(1);
	padEfficiencyRatios->Draw();

	padEfficiency->cd();
	padEfficiency->SetTickx();
	padEfficiency->SetTicky();
	//padEfficiency->SetLogy(1);

	TLegend* legendEfficiencyMeson = new TLegend(0.3,0.02,0.4,0.3);
	legendEfficiencyMeson->SetTextSize(0.03);
	legendEfficiencyMeson->SetFillColor(0);
	legendEfficiencyMeson->SetLineColor(0);

	for(Int_t i = 0; i< VariationsNumber; i++){
		cout << "first loop"  << i << endl;
		if(i == 0){
			DrawAutoGammaMesonHistos( histoEfficiency[i],
				"", "p_{T} (GeV/c)", "#epsilon",
				kFALSE, 5., 5e-10,kTRUE,
				kTRUE, 0.0, 0.0025,
				kFALSE, 0., 10.);
			DrawGammaSetMarker(histoEfficiency[i], 20, 1., color[0], color[0]);
			histoEfficiency[i]->DrawCopy("e1,p");
			legendEfficiencyMeson->AddEntry(histoEfficiency[i], Form("standard: %s",Variation[i].Data()));
			} else{
				if(i<20){
					DrawGammaSetMarker(histoEfficiency[i], 20+i, 1.,color[i],color[i]);
				} else {
					DrawGammaSetMarker(histoEfficiency[i], 20+i, 1.,color[i-20],color[i]);
				}
				histoEfficiency[i]->DrawCopy("same,e1,p");
				legendEfficiencyMeson->AddEntry(histoEfficiency[i], Variation[i].Data());
			}
	}
	legendEfficiencyMeson->Draw();
	labelCollisionSystem->Draw();
	labelcentrality->Draw();


	padEfficiencyRatios->cd();
	padEfficiencyRatios->SetTickx();
	padEfficiencyRatios->SetTicky();
	padEfficiencyRatios->SetLogy(0);

	for(Int_t i = 0; i< VariationsNumber; i++){
		cout << "second loop"  << i << endl;
		if(i==0){
			for(Int_t b = 0; b< histoRatioEfficiency[i]->GetNbinsX(); b++){
				histoRatioEfficiency[i]->SetYTitle("#frac{modified}{standard}");
				histoRatioEfficiency[i]->SetXTitle("p_{T} (GeV/c)");
				histoRatioEfficiency[i]->GetYaxis()->SetRangeUser(0.45,1.55);

				histoRatioEfficiency[i]->GetYaxis()->SetLabelSize(0.07);
				histoRatioEfficiency[i]->GetYaxis()->SetNdivisions(505);
				histoRatioEfficiency[i]->GetYaxis()->SetTitleSize(0.1);
				histoRatioEfficiency[i]->GetYaxis()->SetDecimals();
				histoRatioEfficiency[i]->GetYaxis()->SetTitleOffset(0.5);
				histoRatioEfficiency[i]->GetXaxis()->SetTitleSize(0.11);
				histoRatioEfficiency[i]->GetXaxis()->SetLabelSize(0.08);
				histoRatioEfficiency[i]->SetMarkerStyle(22);
				histoRatioEfficiency[i]->SetMarkerSize(1.);
				histoRatioEfficiency[i]->SetMarkerColor(color[0]);
				histoRatioEfficiency[i]->SetLineColor(color[0]);

				DrawGammaSetMarker(histoRatioEfficiency[i], 20, 1., 1, 1);
				//       	 histoRatioEfficiency[i]->SetBinError(b+1,histoEfficiency[i]->GetBinError(b+1)/histoEfficiency[i]->GetBinContent(b+1));
				// 		 histoRatioEfficiency[i]->SetFillColor(1);
				// 		 histoRatioEfficiency[i]->SetFillStyle(0);
				histoRatioEfficiency[i]->DrawCopy("p,e2");
			}		
		} else{
			if(i<20){
				DrawGammaSetMarker(histoRatioEfficiency[i], 20+i, 1.,color[i],color[i]);
			} else {
				DrawGammaSetMarker(histoRatioEfficiency[i], 20+i, 1.,color[i-20],color[i]);
			}
			histoRatioEfficiency[i]->DrawCopy("same,e1,p");
			cout << "problem?" << endl;
		}
	}

	canvasEfficiencyMeson->Update();
	canvasEfficiencyMeson->SaveAs(Form("%s/%s_%s_Efficiency_%s.%s",outputDir.Data(), meson.Data(),prefix2.Data(),label.Data(),suffix.Data()));
	delete canvasEfficiencyMeson;

}//end





