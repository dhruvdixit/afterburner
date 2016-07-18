/****************************************************************************************************************************
****** 		provided by Gamma Conversion Group, PWG4, 													*****
******		Ana Marin, marin@physi.uni-heidelberg.de													*****
******	   	Kathrin Koch, kkoch@physi.uni-heidelberg.de 													*****
******		Friederike Bock, friederike.bock@cern.ch													*****
*****************************************************************************************************************************/

#include <Riostream.h>
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
#include "TArrow.h"
#include "TGraphAsymmErrors.h" 
#include "TGaxis.h"
#include "TMarker.h"
#include "Math/WrappedTF1.h"
#include "Math/BrentRootFinder.h"
#include "CommonHeaders/PlottingGammaConversionHistos.h"
#include "CommonHeaders/PlottingGammaConversionAdditional.h"
#include "CommonHeaders/FittingGammaConversion.h"
#include "CommonHeaders/ConversionFunctionsBasicsAndLabeling.h"
#include "CommonHeaders/ConversionFunctions.h"
#include "CommonHeaders/CombinationFunctions.h"


extern TRandom*	gRandom;
extern TBenchmark*	gBenchmark;
extern TSystem*	gSystem;
extern TMinuit*  	gMinuit;

void CompareFinalPi0ToPreliminary(TString outputDir = "eps/CombineMesonMeasurementsPbPbX", TString suffix = "eps"){

	gROOT->Reset();	
	gROOT->SetStyle("Plain");
	
	StyleSettingsThesis();	
	SetPlotStyle();

	Color_t	colorComb0005				= kRed+1;
	Color_t	colorComb0510				= 807;
	Color_t	colorComb1020				= 800;
	Color_t	colorComb2040				= kGreen+2;
	Color_t	colorComb4060				= kCyan+2;
	Color_t	colorComb6080				= kBlue+1;

	Style_t 	markerStyleCommmonSpectrum0005 	= 20 ;
	Style_t 	markerStyleCommmonSpectrum0510 	= 21 ;
	Style_t 	markerStyleCommmonSpectrum1020 	= 29 ;
	Style_t 	markerStyleCommmonSpectrum2040 	= 33 ;
	Style_t 	markerStyleCommmonSpectrum4060 	= 20 ;
	Style_t 	markerStyleCommmonSpectrum6080 	= 21 ;

	Size_t 	markerSizeCommonSpectrum0005 	= 2.;
	Size_t 	markerSizeCommonSpectrum0510 	= 2.;
	Size_t 	markerSizeCommonSpectrum1020 	= 2.5;
	Size_t 	markerSizeCommonSpectrum2040 	= 2.5;
	Size_t 	markerSizeCommonSpectrum4060 	= 2.;
	Size_t 	markerSizeCommonSpectrum6080 	= 2.;
	
	Width_t 	widthLinesBoxes;

	TString collisionSystemPP = "pp #sqrt{#it{s}} = 2.76 TeV";		
	TString collisionSystemCent0 = "0-5% Pb-Pb #sqrt{#it{s}_{_{NN}}} = 2.76 TeV";		
	TString collisionSystemCent1 = "5-10% Pb-Pb #sqrt{#it{s}_{_{NN}}} = 2.76 TeV";		
	TString collisionSystemCent2 = "10-20% Pb-Pb #sqrt{#it{s}_{_{NN}}} = 2.76 TeV";		
	TString collisionSystemCent = "0-20% Pb-Pb #sqrt{#it{s}_{_{NN}}} = 2.76 TeV";		
	TString collisionSystemSemiCent = "20-40% Pb-Pb #sqrt{#it{s}_{_{NN}}} = 2.76 TeV";		
	TString collisionSystemSemiPer = "40-60% Pb-Pb #sqrt{#it{s}_{_{NN}}} = 2.76 TeV";		
	TString collisionSystemPer = "60-80% Pb-Pb #sqrt{#it{s}_{_{NN}}} = 2.76 TeV";		

	Size_t markerSizeComparison = 1.5;
	
	TFile* fileConversionPrelim = new TFile("FinalResults/Neutral_Pions_CTS_CONV_110521.root");

	TH1D*	histoYieldPrelimPi0PCM0020 = (TH1D*)fileConversionPrelim->Get("CorrectedYieldTruePb_00_20");
	TH1D*	histoYieldPrelimPi0PCM2040 = (TH1D*)fileConversionPrelim->Get("CorrectedYieldTruePb_20_40");
	TH1D*	histoYieldPrelimPi0PCM4060 = (TH1D*)fileConversionPrelim->Get("CorrectedYieldTruePb_40_60");
	TH1D*	histoYieldPrelimPi0PCM6080 = (TH1D*)fileConversionPrelim->Get("CorrectedYieldTruePb_60_80");
	TGraphAsymmErrors*	graphYieldPrelimPi0PCMSyst0020 = (TGraphAsymmErrors*)fileConversionPrelim->Get("CorrectedYieldTrueEffSys_00_20");
	TGraphAsymmErrors*	graphYieldPrelimPi0PCMSyst2040 = (TGraphAsymmErrors*)fileConversionPrelim->Get("CorrectedYieldTrueEffSys_20_40");
	TGraphAsymmErrors*	graphYieldPrelimPi0PCMSyst4060 = (TGraphAsymmErrors*)fileConversionPrelim->Get("CorrectedYieldTrueEffSys_40_60");
	TGraphAsymmErrors*	graphYieldPrelimPi0PCMSyst6080 = (TGraphAsymmErrors*)fileConversionPrelim->Get("CorrectedYieldTrueEffSys_60_80");
	graphYieldPrelimPi0PCMSyst0020->RemovePoint(0);
	graphYieldPrelimPi0PCMSyst0020->RemovePoint(0);
	graphYieldPrelimPi0PCMSyst6080->RemovePoint(0);
	graphYieldPrelimPi0PCMSyst6080->RemovePoint(0);

	TGraphAsymmErrors*	 graphYieldPrelimPi0PCMStat0020 = new TGraphAsymmErrors(histoYieldPrelimPi0PCM0020->GetNbinsX()-1);
	
	for (Int_t i = 0; i < histoYieldPrelimPi0PCM0020->GetNbinsX()-1; i++){
		cout << histoYieldPrelimPi0PCM0020->GetBinCenter(i+2) << "\t" << histoYieldPrelimPi0PCM0020->GetBinContent(i+2) << endl;
		graphYieldPrelimPi0PCMStat0020->SetPoint(i,histoYieldPrelimPi0PCM0020->GetBinCenter(i+2),histoYieldPrelimPi0PCM0020->GetBinContent(i+2));
		graphYieldPrelimPi0PCMStat0020->SetPointError(i, histoYieldPrelimPi0PCM0020->GetBinWidth(i+2)/2, histoYieldPrelimPi0PCM0020->GetBinWidth(i+2)/2, histoYieldPrelimPi0PCM0020->GetBinError(i+2), histoYieldPrelimPi0PCM0020->GetBinError(i+2));
	}
	graphYieldPrelimPi0PCMStat0020->Print();
	
// 	
	TFile* fCombResults= new TFile("CombinedResultsPbPb.root");
		TGraphAsymmErrors*	graphYieldPi0CombPbPb0005StatErr = (TGraphAsymmErrors*)fCombResults->Get("InvYieldPbPbStatErr_0005");
		TGraphAsymmErrors*	graphYieldPi0CombPbPb0005SysErr = (TGraphAsymmErrors*)fCombResults->Get("InvYieldPbPbSysErr_0005");
		TGraphAsymmErrors*	graphYieldPi0PCMPbPb0005StatErr = (TGraphAsymmErrors*)fCombResults->Get("InvYieldPbPbPCMStatErr_0005");
		TGraphAsymmErrors*	graphYieldPi0PCMPbPb0005SysErr = (TGraphAsymmErrors*)fCombResults->Get("InvYieldPbPbPCMSysErr_0005");
		TGraphAsymmErrors*	graphYieldPi0PHOSPbPb0005StatErr = (TGraphAsymmErrors*)fCombResults->Get("InvYieldPbPbPHOSStatErr_0005");
		TGraphAsymmErrors*	graphYieldPi0PHOSPbPb0005SysErr = (TGraphAsymmErrors*)fCombResults->Get("InvYieldPbPbPHOSSysErr_0005");
		TGraphAsymmErrors*	graphYieldPi0CombPbPb0510StatErr = (TGraphAsymmErrors*)fCombResults->Get("InvYieldPbPbStatErr_0510");
		TGraphAsymmErrors*	graphYieldPi0CombPbPb0510SysErr = (TGraphAsymmErrors*)fCombResults->Get("InvYieldPbPbSysErr_0510");
		TGraphAsymmErrors*	graphYieldPi0PCMPbPb0510StatErr = (TGraphAsymmErrors*)fCombResults->Get("InvYieldPbPbPCMStatErr_0510");
		TGraphAsymmErrors*	graphYieldPi0PCMPbPb0510SysErr = (TGraphAsymmErrors*)fCombResults->Get("InvYieldPbPbPCMSysErr_0510");
		TGraphAsymmErrors*	graphYieldPi0PHOSPbPb0510StatErr = (TGraphAsymmErrors*)fCombResults->Get("InvYieldPbPbPHOSStatErr_0510");
		TGraphAsymmErrors*	graphYieldPi0PHOSPbPb0510SysErr = (TGraphAsymmErrors*)fCombResults->Get("InvYieldPbPbPHOSSysErr_0510");
		TGraphAsymmErrors*	graphYieldPi0CombPbPb1020StatErr = (TGraphAsymmErrors*)fCombResults->Get("InvYieldPbPbStatErr_1020");
		TGraphAsymmErrors*	graphYieldPi0CombPbPb1020SysErr = (TGraphAsymmErrors*)fCombResults->Get("InvYieldPbPbSysErr_1020");
		TGraphAsymmErrors*	graphYieldPi0PCMPbPb1020StatErr = (TGraphAsymmErrors*)fCombResults->Get("InvYieldPbPbPCMStatErr_1020");
		TGraphAsymmErrors*	graphYieldPi0PCMPbPb1020SysErr = (TGraphAsymmErrors*)fCombResults->Get("InvYieldPbPbPCMSysErr_1020");
		TGraphAsymmErrors*	graphYieldPi0PHOSPbPb1020StatErr = (TGraphAsymmErrors*)fCombResults->Get("InvYieldPbPbPHOSStatErr_1020");
		TGraphAsymmErrors*	graphYieldPi0PHOSPbPb1020SysErr = (TGraphAsymmErrors*)fCombResults->Get("InvYieldPbPbPHOSSysErr_1020");
		TGraphAsymmErrors*	graphYieldPi0CombPbPb2040StatErr = (TGraphAsymmErrors*)fCombResults->Get("InvYieldPbPbStatErr_2040");
		TGraphAsymmErrors*	graphYieldPi0CombPbPb2040SysErr = (TGraphAsymmErrors*)fCombResults->Get("InvYieldPbPbSysErr_2040");
		TGraphAsymmErrors*	graphYieldPi0PCMPbPb2040StatErr = (TGraphAsymmErrors*)fCombResults->Get("InvYieldPbPbPCMStatErr_2040");
		TGraphAsymmErrors*	graphYieldPi0PCMPbPb2040SysErr = (TGraphAsymmErrors*)fCombResults->Get("InvYieldPbPbPCMSysErr_2040");
		TGraphAsymmErrors*	graphYieldPi0PHOSPbPb2040StatErr = (TGraphAsymmErrors*)fCombResults->Get("InvYieldPbPbPHOSStatErr_2040");
		TGraphAsymmErrors*	graphYieldPi0PHOSPbPb2040SysErr = (TGraphAsymmErrors*)fCombResults->Get("InvYieldPbPbPHOSSysErr_2040");
		TGraphAsymmErrors*	graphYieldPi0CombPbPb4060StatErr = (TGraphAsymmErrors*)fCombResults->Get("InvYieldPbPbStatErr_4060");
		TGraphAsymmErrors*	graphYieldPi0CombPbPb4060SysErr = (TGraphAsymmErrors*)fCombResults->Get("InvYieldPbPbSysErr_4060");
		TGraphAsymmErrors*	graphYieldPi0PCMPbPb4060StatErr = (TGraphAsymmErrors*)fCombResults->Get("InvYieldPbPbPCMStatErr_4060");
		TGraphAsymmErrors*	graphYieldPi0PCMPbPb4060SysErr = (TGraphAsymmErrors*)fCombResults->Get("InvYieldPbPbPCMSysErr_4060");
		TGraphAsymmErrors*	graphYieldPi0PHOSPbPb4060StatErr = (TGraphAsymmErrors*)fCombResults->Get("InvYieldPbPbPHOSStatErr_4060");
		TGraphAsymmErrors*	graphYieldPi0PHOSPbPb4060SysErr = (TGraphAsymmErrors*)fCombResults->Get("InvYieldPbPbPHOSSysErr_4060");
		TGraphAsymmErrors*	graphYieldPi0CombPbPb6080StatErr = (TGraphAsymmErrors*)fCombResults->Get("InvYieldPbPbStatErr_6080");
		TGraphAsymmErrors*	graphYieldPi0CombPbPb6080SysErr = (TGraphAsymmErrors*)fCombResults->Get("InvYieldPbPbSysErr_6080");
		TGraphAsymmErrors*	graphYieldPi0PCMPbPb6080StatErr = (TGraphAsymmErrors*)fCombResults->Get("InvYieldPbPbPCMStatErr_6080");
		TGraphAsymmErrors*	graphYieldPi0PCMPbPb6080SysErr = (TGraphAsymmErrors*)fCombResults->Get("InvYieldPbPbPCMSysErr_6080");
		TGraphAsymmErrors*	graphYieldPi0PHOSPbPb6080StatErr = (TGraphAsymmErrors*)fCombResults->Get("InvYieldPbPbPHOSStatErr_6080");
		TGraphAsymmErrors*	graphYieldPi0PHOSPbPb6080SysErr = (TGraphAsymmErrors*)fCombResults->Get("InvYieldPbPbPHOSSysErr_6080");
	
		
	// ***************************************************************************************************************
	// ************************************ Charged Pion  *********************************************************
	// ***************************************************************************************************************
	TCanvas * canvas6PartCompChargedPionsSpec = new TCanvas("canvas6PartCompChargedPionsSpec","",10,10,1834,1400);  // gives the page size		
	canvas6PartCompChargedPionsSpec->cd();
	DrawGammaCanvasSettings( canvas6PartCompChargedPionsSpec, 0.13, 0.0, 0.02, 0.1);
	
	TPad* pad6PartCompChargedPionsSpec1 = new TPad("pad6PartCompChargedPionsSpec1", "", 0., 0.52, 0.35, 1.,-1, -1, -2);
	DrawGammaPadSettings( pad6PartCompChargedPionsSpec1, 0.15, 0.0, 0.02, 0.);
	pad6PartCompChargedPionsSpec1->Draw();
	TPad* pad6PartCompChargedPionsSpec2 = new TPad("pad6PartCompChargedPionsSpec2", "", 0., 0., 0.35, 0.52,-1, -1, -2);
	DrawGammaPadSettings( pad6PartCompChargedPionsSpec2, 0.15, 0.0, 0., 0.09);
	pad6PartCompChargedPionsSpec2->Draw();
	
	TPad* pad6PartCompChargedPionsSpec3 = new TPad("pad6PartCompChargedPionsSpec3", "", 0.35, 0.52, 0.68, 1.,-1, -1, -2);
	DrawGammaPadSettings( pad6PartCompChargedPionsSpec3, 0.0, 0.0, 0.02, 0.);
	pad6PartCompChargedPionsSpec3->Draw();
	TPad* pad6PartCompChargedPionsSpec4 = new TPad("pad6PartCompChargedPionsSpec4", "", 0.35, 0., 0.68, 0.52,-1, -1, -2);
	DrawGammaPadSettings( pad6PartCompChargedPionsSpec4, 0.0, 0.0, 0., 0.09);
	pad6PartCompChargedPionsSpec4->Draw();

	TPad* pad6PartCompChargedPionsSpec5 = new TPad("pad6PartCompChargedPionsSpec5", "", 0.68, 0.52, 1., 1.,-1, -1, -2);
	DrawGammaPadSettings( pad6PartCompChargedPionsSpec5, 0.0, 0.02, 0.02, 0.);
	pad6PartCompChargedPionsSpec5->Draw();
	TPad* pad6PartCompChargedPionsSpec6 = new TPad("pad6PartCompChargedPionsSpec6", "", 0.68, 0., 1., 0.52,-1, -1, -2);
	DrawGammaPadSettings( pad6PartCompChargedPionsSpec6, 0.0, 0.02, 0., 0.09);
	pad6PartCompChargedPionsSpec6->Draw();

	TH2F * histo2DCompCombinedSpec2;
	histo2DCompCombinedSpec2 = new TH2F("histo2DCompCombinedSpec2","histo2DCompCombinedSpec2",1000,0.3,20.,1000,1e-7,2e4	);
// 	histo2DCompCombinedSpec2->GetYaxis()->SetRangeUser(0.6,2.1);
	histo2DCompCombinedSpec2->GetXaxis()->SetRangeUser(0.,30.);
	SetStyleHistoTH2ForGraphs(histo2DCompCombinedSpec2, "p_{T} (GeV/c)","#frac{1}{2#pi N_{ev}} #frac{d^{2}N}{p_{T}dp_{T}dy} (GeV/c)^{-2}",0.03,0.04, 0.03,0.04, 1.,1.5);
	
	TH2F* histo2DCompCombinedSpec;
	histo2DCompCombinedSpec = new TH2F("histo2DCompCombinedSpec","histo2DCompCombinedSpec",1000,0.29,20.,1000,1e-7,2e4	);
// 	histo2DCompCombinedSpec->GetYaxis()->SetRangeUser(0.6,2.1);
	histo2DCompCombinedSpec->GetXaxis()->SetRangeUser(0.09,30.);
	SetStyleHistoTH2ForGraphs(histo2DCompCombinedSpec, "p_{T} (GeV/c)","#frac{1}{2#pi N_{ev}} #frac{d^{2}N}{p_{T}dp_{T}dy} (GeV/c)^{-2}",0.03,0.04, 0.03,0.04, 1.,1.5);

	pad6PartCompChargedPionsSpec1->cd();
	pad6PartCompChargedPionsSpec1->SetLogx();
	pad6PartCompChargedPionsSpec1->SetLogy();
	histo2DCompCombinedSpec2->GetXaxis()->SetRangeUser(0.,30.);
// 	histo2DCompCombinedSpec2->GetYaxis()->SetRangeUser(0.6,2.1);
	histo2DCompCombinedSpec2->DrawCopy();
		
		DrawGammaSetMarker(histoYieldPrelimPi0PCM0020,21,markerSizeComparison, kBlack , kBlack);
		DrawGammaSetMarkerTGraphAsym(graphYieldPrelimPi0PCMSyst0020, 21,markerSizeComparison, kBlack , kBlack);
		graphYieldPrelimPi0PCMSyst0020->Draw("same,e2");
		histoYieldPrelimPi0PCM0020->Draw("E1psame");
	
		DrawGammaSetMarkerTGraphAsym(graphYieldPi0CombPbPb0005SysErr, markerStyleCommmonSpectrum0005,markerSizeCommonSpectrum0005, colorComb0005 , colorComb0005, widthLinesBoxes, kTRUE);//, colorComb0005-5);
		graphYieldPi0CombPbPb0005SysErr->Draw("E2same");
		DrawGammaSetMarkerTGraphAsym(graphYieldPi0CombPbPb0005StatErr, markerStyleCommmonSpectrum0005,markerSizeCommonSpectrum0005, colorComb0005 , colorComb0005);
		graphYieldPi0CombPbPb0005StatErr->Draw("p,same,e1");

		TLatex *labelPi0PrelimCompFinalSpecPbPb0005 = new TLatex(0.18,0.9,collisionSystemCent0.Data());
		SetStyleTLatex( labelPi0PrelimCompFinalSpecPbPb0005, 0.048,4);
		labelPi0PrelimCompFinalSpecPbPb0005->Draw();
				
		TLegend* legendPi0CompChargedPionsSpecPbPb0005 = new TLegend(0.2,0.82,0.9,0.88);
		legendPi0CompChargedPionsSpecPbPb0005->SetFillColor(0);
		legendPi0CompChargedPionsSpecPbPb0005->SetLineColor(0);
		legendPi0CompChargedPionsSpecPbPb0005->SetNColumns(2);
		legendPi0CompChargedPionsSpecPbPb0005->SetTextSize(0.045);
		legendPi0CompChargedPionsSpecPbPb0005->AddEntry(graphYieldPi0CombPbPb0005SysErr,"#pi^{0} current","pf");
		legendPi0CompChargedPionsSpecPbPb0005->AddEntry(histoYieldPrelimPi0PCM0020,"#pi^{0} preliminary","pe");
		legendPi0CompChargedPionsSpecPbPb0005->Draw();
	
	histo2DCompCombinedSpec2->Draw("axis,same");
	pad6PartCompChargedPionsSpec1->Update();
	pad6PartCompChargedPionsSpec2->cd();
	pad6PartCompChargedPionsSpec2->SetLogx();
	pad6PartCompChargedPionsSpec2->SetLogy();

// 	histo2DCompCombinedSpec2->GetYaxis()->SetRangeUser(0.6,2.1);
 	histo2DCompCombinedSpec2->DrawCopy();

		DrawGammaSetMarker(histoYieldPrelimPi0PCM2040,21,markerSizeComparison, kBlack , kBlack);
		DrawGammaSetMarkerTGraphAsym(graphYieldPrelimPi0PCMSyst2040, 21,markerSizeComparison, kBlack , kBlack);
		graphYieldPrelimPi0PCMSyst2040->Draw("same,e2");
		histoYieldPrelimPi0PCM2040->Draw("E1psame");
	
		DrawGammaSetMarkerTGraphAsym(graphYieldPi0CombPbPb2040SysErr, markerStyleCommmonSpectrum2040,markerSizeCommonSpectrum2040, colorComb2040 , colorComb2040, widthLinesBoxes, kTRUE);//, colorComb2040-5);
		graphYieldPi0CombPbPb2040SysErr->Draw("E2same");
		DrawGammaSetMarkerTGraphAsym(graphYieldPi0CombPbPb2040StatErr, markerStyleCommmonSpectrum2040,markerSizeCommonSpectrum2040, colorComb2040 , colorComb2040);
		graphYieldPi0CombPbPb2040StatErr->Draw("p,same,e1");
		
// 		DrawGammaSetMarkerTGraphErr(graphRatioPrelimComb2040,21,markerSizeComparison, kBlack , kBlack);
// 		DrawGammaSetMarkerTGraphErr(graphRatioLowPtChargedPionsComb2040,20,markerSizeComparison, kViolet,kViolet);
// 		graphRatioPrelimComb2040->Draw("E1psame");
// 		graphRatioLowPtChargedPionsComb2040->Draw("E1psame");

		TLatex *labelPi0PrelimCompFinalSpecPbPb2040 = new TLatex(0.18,0.93,collisionSystemSemiCent.Data());
		SetStyleTLatex( labelPi0PrelimCompFinalSpecPbPb2040, 0.046,4);
		labelPi0PrelimCompFinalSpecPbPb2040->Draw();

	histo2DCompCombinedSpec2->Draw("axis,same");
	pad6PartCompChargedPionsSpec2->Update();
	pad6PartCompChargedPionsSpec3->cd();
	pad6PartCompChargedPionsSpec3->SetLogx();
	pad6PartCompChargedPionsSpec3->SetLogy();

	histo2DCompCombinedSpec->GetXaxis()->SetRangeUser(0.09,30.);
// 	histo2DCompCombinedSpec->GetYaxis()->SetRangeUser(0.6,2.1);
	histo2DCompCombinedSpec->DrawCopy();
		DrawGammaSetMarker(histoYieldPrelimPi0PCM0020,21,markerSizeComparison, kBlack , kBlack);
		DrawGammaSetMarkerTGraphAsym(graphYieldPrelimPi0PCMSyst0020, 21,markerSizeComparison, kBlack , kBlack);
		graphYieldPrelimPi0PCMSyst0020->Draw("same,e2");
		histoYieldPrelimPi0PCM0020->Draw("E1psame");

		DrawGammaSetMarkerTGraphAsym(graphYieldPi0CombPbPb0510SysErr, markerStyleCommmonSpectrum0510,markerSizeCommonSpectrum0510, colorComb0510 , colorComb0510, widthLinesBoxes, kTRUE);//, colorComb0510-5);
		graphYieldPi0CombPbPb0510SysErr->Draw("E2same");
		DrawGammaSetMarkerTGraphAsym(graphYieldPi0CombPbPb0510StatErr, markerStyleCommmonSpectrum0510,markerSizeCommonSpectrum0510, colorComb0510 , colorComb0510);
		graphYieldPi0CombPbPb0510StatErr->Draw("p,same,e1");
	
		TLatex *labelPi0PrelimCompFinalSpecPbPb0510 = new TLatex(0.03,0.9,collisionSystemCent1.Data());
		SetStyleTLatex( labelPi0PrelimCompFinalSpecPbPb0510, 0.05,4);
		labelPi0PrelimCompFinalSpecPbPb0510->Draw(); 

		TLatex *labelPi0PrelimCompFinalComment = new TLatex(0.03,0.1,"final results in 0-5%, 5-10% and 10-20%");
		SetStyleTLatex( labelPi0PrelimCompFinalComment, 0.048,4,2);
		labelPi0PrelimCompFinalComment->Draw();
		TLatex *labelPi0PrelimCompFinalComment2 = new TLatex(0.03,0.05,"are compared to preliminary result in 0-20%");
		SetStyleTLatex( labelPi0PrelimCompFinalComment2, 0.048,4,2);
		labelPi0PrelimCompFinalComment2->Draw();

	histo2DCompCombinedSpec->Draw("axis,same");
	pad6PartCompChargedPionsSpec3->Update();
	pad6PartCompChargedPionsSpec4->cd();
	pad6PartCompChargedPionsSpec4->SetLogx();
	pad6PartCompChargedPionsSpec4->SetLogy();

// 	histo2DCompCombinedSpec->GetYaxis()->SetRangeUser(0.6,2.1);
	histo2DCompCombinedSpec->DrawCopy();
		DrawGammaSetMarker(histoYieldPrelimPi0PCM4060,21,markerSizeComparison, kBlack , kBlack);
		DrawGammaSetMarkerTGraphAsym(graphYieldPrelimPi0PCMSyst4060, 21,markerSizeComparison, kBlack , kBlack);
		graphYieldPrelimPi0PCMSyst4060->Draw("same,e2");
		histoYieldPrelimPi0PCM4060->Draw("E1psame");
	
		DrawGammaSetMarkerTGraphAsym(graphYieldPi0CombPbPb4060SysErr, markerStyleCommmonSpectrum4060,markerSizeCommonSpectrum4060, colorComb4060 , colorComb4060, widthLinesBoxes, kTRUE);//, colorComb4060-5);
		graphYieldPi0CombPbPb4060SysErr->Draw("E2same");
		DrawGammaSetMarkerTGraphAsym(graphYieldPi0CombPbPb4060StatErr, markerStyleCommmonSpectrum4060,markerSizeCommonSpectrum4060, colorComb4060 , colorComb4060);
		graphYieldPi0CombPbPb4060StatErr->Draw("p,same,e1");
		
		TLatex *labelPi0PrelimCompFinalSpecPbPb4060 = new TLatex(0.03,0.93,collisionSystemSemiPer.Data());
		SetStyleTLatex( labelPi0PrelimCompFinalSpecPbPb4060, 0.048,4);
		labelPi0PrelimCompFinalSpecPbPb4060->Draw();		

	histo2DCompCombinedSpec->Draw("axis,same");
	
	pad6PartCompChargedPionsSpec4->Update();
	pad6PartCompChargedPionsSpec5->cd();
	pad6PartCompChargedPionsSpec5->SetLogx();
	pad6PartCompChargedPionsSpec5->SetLogy();

// 	histo2DCompCombinedSpec->GetYaxis()->SetRangeUser(0.6,2.1);
	histo2DCompCombinedSpec->DrawCopy();
		DrawGammaSetMarker(histoYieldPrelimPi0PCM0020,21,markerSizeComparison, kBlack , kBlack);
		DrawGammaSetMarkerTGraphAsym(graphYieldPrelimPi0PCMSyst0020, 21,markerSizeComparison, kBlack , kBlack);
		graphYieldPrelimPi0PCMSyst0020->Draw("samee2");
		histoYieldPrelimPi0PCM0020->Draw("E1psame");
		
		DrawGammaSetMarkerTGraphAsym(graphYieldPi0CombPbPb1020SysErr, markerStyleCommmonSpectrum1020,markerSizeCommonSpectrum1020, colorComb1020 , colorComb1020, widthLinesBoxes, kTRUE);//, colorComb1020-5);
		graphYieldPi0CombPbPb1020SysErr->Draw("E2same");
		DrawGammaSetMarkerTGraphAsym(graphYieldPi0CombPbPb1020StatErr, markerStyleCommmonSpectrum1020,markerSizeCommonSpectrum1020, colorComb1020 , colorComb1020);
		graphYieldPi0CombPbPb1020StatErr->Draw("p,same,e1");

		TLatex *labelPi0PrelimCompFinalSpecPbPb1020 = new TLatex(0.03,0.9,collisionSystemCent2.Data());
		SetStyleTLatex( labelPi0PrelimCompFinalSpecPbPb1020, 0.05,4);
		labelPi0PrelimCompFinalSpecPbPb1020->Draw();		
		
	histo2DCompCombinedSpec->Draw("axis,same");
	pad6PartCompChargedPionsSpec5->Update();
	pad6PartCompChargedPionsSpec6->cd();
	pad6PartCompChargedPionsSpec6->SetLogx();
	pad6PartCompChargedPionsSpec6->SetLogy();

// 	histo2DCompCombinedSpec->GetYaxis()->SetRangeUser(0.6,2.1);
	histo2DCompCombinedSpec->DrawCopy();
		DrawGammaSetMarker(histoYieldPrelimPi0PCM6080,21,markerSizeComparison, kBlack , kBlack);
		DrawGammaSetMarkerTGraphAsym(graphYieldPrelimPi0PCMSyst6080, 21,markerSizeComparison, kBlack , kBlack);
		graphYieldPrelimPi0PCMSyst6080->Draw("same,e2");
		histoYieldPrelimPi0PCM6080->Draw("E1psame");
	
		DrawGammaSetMarkerTGraphAsym(graphYieldPi0CombPbPb6080SysErr, markerStyleCommmonSpectrum6080,markerSizeCommonSpectrum6080, colorComb6080 , colorComb6080, widthLinesBoxes, kTRUE);//, colorComb6080-5);
		graphYieldPi0CombPbPb6080SysErr->Draw("E2same");
		DrawGammaSetMarkerTGraphAsym(graphYieldPi0CombPbPb6080StatErr, markerStyleCommmonSpectrum6080,markerSizeCommonSpectrum6080, colorComb6080 , colorComb6080);
		graphYieldPi0CombPbPb6080StatErr->Draw("p,same,e1");

		TLatex *labelPi0PrelimCompFinalSpecPbPb6080 = new TLatex(0.04,0.93,collisionSystemPer.Data());
		SetStyleTLatex( labelPi0PrelimCompFinalSpecPbPb6080, 0.048,4);
		labelPi0PrelimCompFinalSpecPbPb6080->Draw();	

	histo2DCompCombinedSpec->Draw("axis,same");
	
	pad6PartCompChargedPionsSpec6->Update();

	canvas6PartCompChargedPionsSpec->Update();	
	canvas6PartCompChargedPionsSpec->SaveAs(Form("%s/ComparisonPreliminaryToCombinedSpectra_Paper.%s",outputDir.Data(),suffix.Data()));
	delete pad6PartCompChargedPionsSpec1;	
	delete pad6PartCompChargedPionsSpec2;	
	delete pad6PartCompChargedPionsSpec3;	
	delete pad6PartCompChargedPionsSpec4;	
	delete canvas6PartCompChargedPionsSpec;
		
		
// 	cout << "*************************************************************************"<< endl;	
// 	cout << "******************************  PbPb 0-5% *******************************"<< endl;
// 	cout << "*************************************************************************"<< endl;
// 		
// 	TGraphAsymmErrors* graphYieldPi0CombPbPb0005StatErrCopy = (TGraphAsymmErrors*) graphYieldPi0CombPbPb0005StatErr->Clone("graphYieldPi0CombPbPb0005StatErrCopy");
// 	graphYieldPi0CombPbPb0005StatErrCopy->RemovePoint(0);
// 	TGraphAsymmErrors* graphYieldPi0CombPbPb0005SysErrCopy = (TGraphAsymmErrors*) graphYieldPi0CombPbPb0005SysErr->Clone("graphYieldPi0CombPbPb0005SysErrCopy");
// 	graphYieldPi0CombPbPb0005SysErrCopy->RemovePoint(0);
// 	TGraphAsymmErrors* graphYieldPi0PCMPbPb0005StatErrCopy = (TGraphAsymmErrors*) graphYieldPi0PCMPbPb0005StatErr->Clone("graphYieldPi0PCMPbPb0005StatErrCopy");
// 	TGraphAsymmErrors* graphYieldPi0PCMPbPb0005SysErrCopy = (TGraphAsymmErrors*) graphYieldPi0PCMPbPb0005SysErr->Clone("graphYieldPi0PCMPbPb0005SysErrCopy");
// 	TGraphAsymmErrors* graphYieldPi0PHOSPbPb0005StatErrCopy = (TGraphAsymmErrors*) graphYieldPi0PHOSPbPb0005StatErr->Clone("graphYieldPi0PHOSPbPb0005StatErrCopy");
// 	TGraphAsymmErrors* graphYieldPi0PHOSPbPb0005SysErrCopy = (TGraphAsymmErrors*) graphYieldPi0PHOSPbPb0005SysErr->Clone("graphYieldPi0PHOSPbPb0005SysErrCopy");
// 	
// 	TGraphAsymmErrors* graphYieldPrelimPi0PCMSyst0020Copy = (TGraphAsymmErrors*) graphYieldPrelimPi0PCMSyst0020->Clone("graphYieldPrelimPi0PCMSyst0020Copy");
// 	TGraphAsymmErrors* graphYieldPrelimPi0PCMStat0020Copy = (TGraphAsymmErrors*) graphYieldPrelimPi0PCMStat0020->Clone("graphYieldPrelimPi0PCMStat0020Copy");
// 	
// 	
// 	cout << "combined Spectrum" << endl;
// 	TGraphErrors* graphRatioPrelimComb0005 = CalculateRatioBetweenSpectraWithDifferentBinning(graphYieldPrelimPi0PCMSyst0020Copy, graphYieldPrelimPi0PCMStat0020Copy, graphYieldPi0CombPbPb0005StatErrCopy, graphYieldPi0CombPbPb0005SysErrCopy,   kTRUE,  kTRUE)	;
// 	graphRatioPrelimComb0005->Print();
// 	
// 	cout << "PCM" << endl;
// 	TGraphErrors* graphRatioPrelimPCM0005 = CalculateRatioBetweenSpectraWithDifferentBinning(graphYieldPrelimPi0PCMSyst0020Copy, graphYieldPrelimPi0PCMStat0020Copy, graphYieldPi0PCMPbPb0005StatErrCopy, graphYieldPi0PCMPbPb0005SysErrCopy,   kTRUE,  kTRUE)	;
// 	graphRatioPrelimPCM0005->Print();
// 	
// 	cout << "PHOS" << endl;
// 	TGraphErrors* graphRatioPrelimPHOS0005 = CalculateRatioBetweenSpectraWithDifferentBinning(graphYieldPrelimPi0PCMSyst0020Copy, graphYieldPrelimPi0PCMStat0020Copy, graphYieldPi0PHOSPbPb0005StatErrCopy, graphYieldPi0PHOSPbPb0005SysErrCopy,   kTRUE,  kTRUE)	;
// 	graphRatioPrelimPHOS0005->Print();
// 	
// 	
// 	
// 	cout << "*************************************************************************"<< endl;	
// 	cout << "******************************  PbPb 5-10% ******************************"<< endl;
// 	cout << "*************************************************************************"<< endl;
// 	
// 	TGraphAsymmErrors* graphYieldPi0CombPbPb0510StatErrCopy = (TGraphAsymmErrors*) graphYieldPi0CombPbPb0510StatErr->Clone("graphYieldPi0CombPbPb0510StatErrCopy");
// 	TGraphAsymmErrors* graphYieldPi0CombPbPb0510SysErrCopy = (TGraphAsymmErrors*) graphYieldPi0CombPbPb0510SysErr->Clone("graphYieldPi0CombPbPb0510SysErrCopy");
// 	TGraphAsymmErrors* graphYieldPi0PCMPbPb0510StatErrCopy = (TGraphAsymmErrors*) graphYieldPi0PCMPbPb0510StatErr->Clone("graphYieldPi0PCMPbPb0510StatErrCopy");
// 	TGraphAsymmErrors* graphYieldPi0PCMPbPb0510SysErrCopy = (TGraphAsymmErrors*) graphYieldPi0PCMPbPb0510SysErr->Clone("graphYieldPi0PCMPbPb0510SysErrCopy");
// 	TGraphAsymmErrors* graphYieldPi0PHOSPbPb0510StatErrCopy = (TGraphAsymmErrors*) graphYieldPi0PHOSPbPb0510StatErr->Clone("graphYieldPi0PHOSPbPb0510StatErrCopy");
// 	TGraphAsymmErrors* graphYieldPi0PHOSPbPb0510SysErrCopy = (TGraphAsymmErrors*) graphYieldPi0PHOSPbPb0510SysErr->Clone("graphYieldPi0PHOSPbPb0510SysErrCopy");
// 	
// 	cout << "combined Spectrum" << endl;
// 	TGraphErrors* graphRatioPrelimComb0510 = CalculateRatioBetweenSpectraWithDifferentBinning(graphYieldPrelimPi0PCMSyst0020Copy, graphYieldPrelimPi0PCMStat0020Copy, graphYieldPi0CombPbPb0510StatErrCopy, graphYieldPi0CombPbPb0510SysErrCopy,  kTRUE,  kTRUE)	;
// 	graphRatioPrelimComb0510->Print();
// 	
// 	cout << "PCM" << endl;
// 	TGraphErrors* graphRatioPrelimPCM0510 = CalculateRatioBetweenSpectraWithDifferentBinning(graphYieldPrelimPi0PCMSyst0020Copy, graphYieldPrelimPi0PCMStat0020Copy, graphYieldPi0PCMPbPb0510StatErrCopy, graphYieldPi0PCMPbPb0510SysErrCopy,  kTRUE,  kTRUE)	;
// 	graphRatioPrelimPCM0510->Print();
// 	
// 	cout << "PHOS" << endl;
// 	TGraphErrors* graphRatioPrelimPHOS0510 = CalculateRatioBetweenSpectraWithDifferentBinning(graphYieldPrelimPi0PCMSyst0020Copy, graphYieldPrelimPi0PCMStat0020Copy, graphYieldPi0PHOSPbPb0510StatErrCopy, graphYieldPi0PHOSPbPb0510SysErrCopy, kTRUE,  kTRUE)	;
// 	graphRatioPrelimPHOS0510->Print();
// 	
// 	
// 	cout << "*************************************************************************"<< endl;	
// 	cout << "******************************  PbPb 10-20% *****************************"<< endl;
// 	cout << "*************************************************************************"<< endl;
// 	
// 	TGraphAsymmErrors* graphYieldPi0CombPbPb1020StatErrCopy = (TGraphAsymmErrors*) graphYieldPi0CombPbPb1020StatErr->Clone("graphYieldPi0CombPbPb1020StatErrCopy");
// 	TGraphAsymmErrors* graphYieldPi0CombPbPb1020SysErrCopy = (TGraphAsymmErrors*) graphYieldPi0CombPbPb1020SysErr->Clone("graphYieldPi0CombPbPb1020SysErrCopy");
// 	TGraphAsymmErrors* graphYieldPi0PCMPbPb1020StatErrCopy = (TGraphAsymmErrors*) graphYieldPi0PCMPbPb1020StatErr->Clone("graphYieldPi0PCMPbPb1020StatErrCopy");
// 	TGraphAsymmErrors* graphYieldPi0PCMPbPb1020SysErrCopy = (TGraphAsymmErrors*) graphYieldPi0PCMPbPb1020SysErr->Clone("graphYieldPi0PCMPbPb1020SysErrCopy");
// 	TGraphAsymmErrors* graphYieldPi0PHOSPbPb1020StatErrCopy = (TGraphAsymmErrors*) graphYieldPi0PHOSPbPb1020StatErr->Clone("graphYieldPi0PHOSPbPb1020StatErrCopy");	
// 	TGraphAsymmErrors* graphYieldPi0PHOSPbPb1020SysErrCopy = (TGraphAsymmErrors*) graphYieldPi0PHOSPbPb1020SysErr->Clone("graphYieldPi0PHOSPbPb1020SysErrCopy");
// 	
// 	cout << "combined Spectrum" << endl;
// 	TGraphErrors* graphRatioPrelimComb1020 = CalculateRatioBetweenSpectraWithDifferentBinning(graphYieldPrelimPi0PCMSyst0020Copy, graphYieldPrelimPi0PCMStat0020Copy, graphYieldPi0CombPbPb1020StatErrCopy, graphYieldPi0CombPbPb1020SysErrCopy,  kTRUE,  kTRUE)	;
// 	graphRatioPrelimComb1020->Print();
// 	
// 	cout << "PCM" << endl;
// 	TGraphErrors* graphRatioPrelimPCM1020 = CalculateRatioBetweenSpectraWithDifferentBinning(graphYieldPrelimPi0PCMSyst0020Copy, graphYieldPrelimPi0PCMStat0020Copy, graphYieldPi0PCMPbPb1020StatErrCopy, graphYieldPi0PCMPbPb1020SysErrCopy,  kTRUE,  kTRUE)	;
// 	graphRatioPrelimPCM1020->Print();
// 	
// 	cout << "PHOS" << endl;
// 	TGraphErrors* graphRatioPrelimPHOS1020 = CalculateRatioBetweenSpectraWithDifferentBinning(graphYieldPrelimPi0PCMSyst0020Copy, graphYieldPrelimPi0PCMStat0020Copy, graphYieldPi0PHOSPbPb1020StatErrCopy, graphYieldPi0PHOSPbPb1020SysErrCopy, kTRUE,  kTRUE)	;
// 	graphRatioPrelimPHOS1020->Print();
// 	
// 	/*
// 	cout << "*************************************************************************"<< endl;	
// 	cout << "******************************  PbPb 20-40% *****************************"<< endl;
// 	cout << "*************************************************************************"<< endl;
// 	
// 	TGraphAsymmErrors* graphYieldPi0CombPbPb2040StatErrCopy = (TGraphAsymmErrors*) graphYieldPi0CombPbPb2040StatErr->Clone("graphYieldPi0CombPbPb2040StatErrCopy");
// 	TGraphAsymmErrors* graphYieldPi0CombPbPb2040SysErrCopy = (TGraphAsymmErrors*) graphYieldPi0CombPbPb2040SysErr->Clone("graphYieldPi0CombPbPb2040SysErrCopy");
// 	TGraphAsymmErrors* graphYieldPi0PCMPbPb2040StatErrCopy = (TGraphAsymmErrors*) graphYieldPi0PCMPbPb2040StatErr->Clone("graphYieldPi0PCMPbPb2040StatErrCopy");
// 	TGraphAsymmErrors* graphYieldPi0PCMPbPb2040SysErrCopy = (TGraphAsymmErrors*) graphYieldPi0PCMPbPb2040SysErr->Clone("graphYieldPi0PCMPbPb2040SysErrCopy");
// 	TGraphAsymmErrors* graphYieldPi0PHOSPbPb2040StatErrCopy = (TGraphAsymmErrors*) graphYieldPi0PHOSPbPb2040StatErr->Clone("graphYieldPi0PHOSPbPb2040StatErrCopy");
// 	TGraphAsymmErrors* graphYieldPi0PHOSPbPb2040SysErrCopy = (TGraphAsymmErrors*) graphYieldPi0PHOSPbPb2040SysErr->Clone("graphYieldPi0PHOSPbPb2040SysErrCopy");
// 	
// 	cout << "combined Spectrum" << endl;
// 	TGraphErrors* graphRatioPrelimComb2040 = CalculateRatioBetweenSpectraWithDifferentBinning(graphYieldPi0CombPbPb2040StatErrCopy, graphYieldPi0CombPbPb2040SysErrCopy, histoChargedPionSpecHighPtStat2040, histoChargedPionSpecHighPtSyst2040,  kTRUE,  kTRUE)	;
// 	graphRatioPrelimComb2040->Print();
// 	TGraphErrors* graphRatioLowPtChargedPionsComb2040 = CalculateRatioBetweenSpectraWithDifferentBinning(graphYieldPi0CombPbPb2040StatErrCopy, graphYieldPi0CombPbPb2040SysErrCopy, histoChargedPionSpecLowPtStat2040, histoChargedPionSpecLowPtSyst2040,  kTRUE,  kTRUE)	;
// 	graphRatioLowPtChargedPionsComb2040->Print();
// 	
// 	
// 	cout << "PCM" << endl;
// 	TGraphErrors* graphRatioPrelimPCM2040 = CalculateRatioBetweenSpectraWithDifferentBinning(graphYieldPi0PCMPbPb2040StatErrCopy, graphYieldPi0PCMPbPb2040SysErrCopy, histoChargedPionSpecHighPtStat2040, histoChargedPionSpecHighPtSyst2040,  kTRUE,  kTRUE)	;
// 	graphRatioPrelimPCM2040->Print();
// 	TGraphErrors* graphRatioLowPtChargedPionsPCM2040 = CalculateRatioBetweenSpectraWithDifferentBinning(graphYieldPi0PCMPbPb2040StatErrCopy, graphYieldPi0PCMPbPb2040SysErrCopy, histoChargedPionSpecLowPtStat2040, histoChargedPionSpecLowPtSyst2040,  kTRUE,  kTRUE)	;
// 	graphRatioLowPtChargedPionsPCM2040->Print();
// 	
// 	cout << "PHOS" << endl;
// 	TGraphErrors* graphRatioPrelimPHOS2040 = CalculateRatioBetweenSpectraWithDifferentBinning(graphYieldPi0PHOSPbPb2040StatErrCopy, graphYieldPi0PHOSPbPb2040SysErrCopy, histoChargedPionSpecHighPtStat2040, histoChargedPionSpecHighPtSyst2040,  kTRUE,  kTRUE)	;
// 	graphRatioPrelimPHOS2040->Print();
// 	TGraphErrors* graphRatioLowPtChargedPionsPHOS2040 = CalculateRatioBetweenSpectraWithDifferentBinning(graphYieldPi0PHOSPbPb2040StatErrCopy, graphYieldPi0PHOSPbPb2040SysErrCopy, histoChargedPionSpecLowPtStat2040, histoChargedPionSpecLowPtSyst2040,  kTRUE,  kTRUE)	;
// 	graphRatioLowPtChargedPionsPHOS2040->Print();
// 	
// 	cout << "*************************************************************************"<< endl;	
// 	cout << "******************************  PbPb 40-60% *****************************"<< endl;
// 	cout << "*************************************************************************"<< endl;
// 	
// 	TGraphAsymmErrors* graphYieldPi0CombPbPb4060StatErrCopy = (TGraphAsymmErrors*) graphYieldPi0CombPbPb4060StatErr->Clone("graphYieldPi0CombPbPb4060StatErrCopy");
// 	TGraphAsymmErrors* graphYieldPi0CombPbPb4060SysErrCopy = (TGraphAsymmErrors*) graphYieldPi0CombPbPb4060SysErr->Clone("graphYieldPi0CombPbPb4060SysErrCopy");
// 	TGraphAsymmErrors* graphYieldPi0PCMPbPb4060StatErrCopy = (TGraphAsymmErrors*) graphYieldPi0PCMPbPb4060StatErr->Clone("graphYieldPi0PCMPbPb4060StatErrCopy");
// 	TGraphAsymmErrors* graphYieldPi0PCMPbPb4060SysErrCopy = (TGraphAsymmErrors*) graphYieldPi0PCMPbPb4060SysErr->Clone("graphYieldPi0PCMPbPb4060SysErrCopy");
// 	TGraphAsymmErrors* graphYieldPi0PHOSPbPb4060StatErrCopy = (TGraphAsymmErrors*) graphYieldPi0PHOSPbPb4060StatErr->Clone("graphYieldPi0PHOSPbPb4060StatErrCopy");
// 	TGraphAsymmErrors* graphYieldPi0PHOSPbPb4060SysErrCopy = (TGraphAsymmErrors*) graphYieldPi0PHOSPbPb4060SysErr->Clone("graphYieldPi0PHOSPbPb4060SysErrCopy");
// 	
// 	cout << "combined Spectrum" << endl;
// 	TGraphErrors* graphRatioPrelimComb4060 = CalculateRatioBetweenSpectraWithDifferentBinning(graphYieldPi0CombPbPb4060StatErrCopy, graphYieldPi0CombPbPb4060SysErrCopy, histoChargedPionSpecHighPtStat4060, histoChargedPionSpecHighPtSyst4060,  kTRUE,  kTRUE)	;
// 	graphRatioPrelimComb4060->Print();
// 	TGraphErrors* graphRatioLowPtChargedPionsComb4060 = CalculateRatioBetweenSpectraWithDifferentBinning(graphYieldPi0CombPbPb4060StatErrCopy, graphYieldPi0CombPbPb4060SysErrCopy, histoChargedPionSpecLowPtStat4060, histoChargedPionSpecLowPtSyst4060,  kTRUE,  kTRUE)	;
// 	graphRatioLowPtChargedPionsComb4060->Print();
// 	
// 	
// 	cout << "PCM" << endl;
// 	TGraphErrors* graphRatioPrelimPCM4060 = CalculateRatioBetweenSpectraWithDifferentBinning(graphYieldPi0PCMPbPb4060StatErrCopy, graphYieldPi0PCMPbPb4060SysErrCopy, histoChargedPionSpecHighPtStat4060, histoChargedPionSpecHighPtSyst4060,  kTRUE,  kTRUE)	;
// 	graphRatioPrelimPCM4060->Print();
// 	TGraphErrors* graphRatioLowPtChargedPionsPCM4060 = CalculateRatioBetweenSpectraWithDifferentBinning(graphYieldPi0PCMPbPb4060StatErrCopy, graphYieldPi0PCMPbPb4060SysErrCopy, histoChargedPionSpecLowPtStat4060, histoChargedPionSpecLowPtSyst4060,  kTRUE,  kTRUE)	;
// 	graphRatioLowPtChargedPionsPCM4060->Print();
// 	
// 	cout << "PHOS" << endl;
// 	TGraphErrors* graphRatioPrelimPHOS4060 = CalculateRatioBetweenSpectraWithDifferentBinning(graphYieldPi0PHOSPbPb4060StatErrCopy, graphYieldPi0PHOSPbPb4060SysErrCopy, histoChargedPionSpecHighPtStat4060, histoChargedPionSpecHighPtSyst4060,  kTRUE,  kTRUE)	;
// 	graphRatioPrelimPHOS4060->Print();
// 	TGraphErrors* graphRatioLowPtChargedPionsPHOS4060 = CalculateRatioBetweenSpectraWithDifferentBinning(graphYieldPi0PHOSPbPb4060StatErrCopy, graphYieldPi0PHOSPbPb4060SysErrCopy, histoChargedPionSpecLowPtStat4060, histoChargedPionSpecLowPtSyst4060,  kTRUE,  kTRUE)	;
// 	graphRatioLowPtChargedPionsPHOS4060->Print();
// 	
// 	cout << "*************************************************************************"<< endl;	
// 	cout << "******************************  PbPb 60-80% *****************************"<< endl;
// 	cout << "*************************************************************************"<< endl;
// 	
// 	TGraphAsymmErrors* graphYieldPi0CombPbPb6080StatErrCopy = (TGraphAsymmErrors*) graphYieldPi0CombPbPb6080StatErr->Clone("graphYieldPi0CombPbPb6080StatErrCopy");
// 	TGraphAsymmErrors* graphYieldPi0CombPbPb6080SysErrCopy = (TGraphAsymmErrors*) graphYieldPi0CombPbPb6080SysErr->Clone("graphYieldPi0CombPbPb6080SysErrCopy");
// 	TGraphAsymmErrors* graphYieldPi0PCMPbPb6080StatErrCopy = (TGraphAsymmErrors*) graphYieldPi0PCMPbPb6080StatErr->Clone("graphYieldPi0PCMPbPb6080StatErrCopy");
// 	TGraphAsymmErrors* graphYieldPi0PCMPbPb6080SysErrCopy = (TGraphAsymmErrors*) graphYieldPi0PCMPbPb6080SysErr->Clone("graphYieldPi0PCMPbPb6080SysErrCopy");
// 	TGraphAsymmErrors* graphYieldPi0PHOSPbPb6080StatErrCopy = (TGraphAsymmErrors*) graphYieldPi0PHOSPbPb6080StatErr->Clone("graphYieldPi0PHOSPbPb6080StatErrCopy");
// 	TGraphAsymmErrors* graphYieldPi0PHOSPbPb6080SysErrCopy = (TGraphAsymmErrors*) graphYieldPi0PHOSPbPb6080SysErr->Clone("graphYieldPi0PHOSPbPb6080SysErrCopy");
// 	
// 	cout << "combined Spectrum" << endl;
// 	TGraphErrors* graphRatioPrelimComb6080 = CalculateRatioBetweenSpectraWithDifferentBinning(graphYieldPi0CombPbPb6080StatErrCopy, graphYieldPi0CombPbPb6080SysErrCopy, histoChargedPionSpecHighPtStat6080, histoChargedPionSpecHighPtSyst6080,  kTRUE,  kTRUE)	;
// 	graphRatioPrelimComb6080->Print();
// 	TGraphErrors* graphRatioLowPtChargedPionsComb6080 = CalculateRatioBetweenSpectraWithDifferentBinning(graphYieldPi0CombPbPb6080StatErrCopy, graphYieldPi0CombPbPb6080SysErrCopy, histoChargedPionSpecLowPtStat6080, histoChargedPionSpecLowPtSyst6080,  kTRUE,  kTRUE)	;
// 	graphRatioLowPtChargedPionsComb6080->Print();
// 	
// 	
// 	cout << "PCM" << endl;
// 	TGraphErrors* graphRatioPrelimPCM6080 = CalculateRatioBetweenSpectraWithDifferentBinning(graphYieldPi0PCMPbPb6080StatErrCopy, graphYieldPi0PCMPbPb6080SysErrCopy, histoChargedPionSpecHighPtStat6080, histoChargedPionSpecHighPtSyst6080,  kTRUE,  kTRUE)	;
// 	graphRatioPrelimPCM6080->Print();
// 	TGraphErrors* graphRatioLowPtChargedPionsPCM6080 = CalculateRatioBetweenSpectraWithDifferentBinning(graphYieldPi0PCMPbPb6080StatErrCopy, graphYieldPi0PCMPbPb6080SysErrCopy, histoChargedPionSpecLowPtStat6080, histoChargedPionSpecLowPtSyst6080,  kTRUE,  kTRUE)	;
// 	graphRatioLowPtChargedPionsPCM6080->Print();
// 	
// 	cout << "PHOS" << endl;
// 	TGraphErrors* graphRatioPrelimPHOS6080 = CalculateRatioBetweenSpectraWithDifferentBinning(graphYieldPi0PHOSPbPb6080StatErrCopy, graphYieldPi0PHOSPbPb6080SysErrCopy, histoChargedPionSpecHighPtStat6080, histoChargedPionSpecHighPtSyst6080,  kTRUE,  kTRUE)	;
// 	graphRatioPrelimPHOS6080->Print();
// 	TGraphErrors* graphRatioLowPtChargedPionsPHOS6080 = CalculateRatioBetweenSpectraWithDifferentBinning(graphYieldPi0PHOSPbPb6080StatErrCopy, graphYieldPi0PHOSPbPb6080SysErrCopy, histoChargedPionSpecLowPtStat6080, histoChargedPionSpecLowPtSyst6080,  kTRUE,  kTRUE)	;
// 	graphRatioLowPtChargedPionsPHOS6080->Print();
// 	
// 	*/
// 	// ***************************************************************************************************************
// 	// ************************************ Charged Pion  *********************************************************
// 	// ***************************************************************************************************************
// 	TCanvas * canvas6PartCompChargedPions = new TCanvas("canvas6PartCompChargedPions","",10,10,1834,1000);  // gives the page size		
// 	canvas6PartCompChargedPions->cd();
// 	DrawGammaCanvasSettings( canvas6PartCompChargedPions, 0.13, 0.0, 0.02, 0.09);
// 	
// 	TPad* pad6PartCompChargedPions1 = new TPad("pad6PartCompChargedPions1", "", 0., 0.52, 0.35, 1.,-1, -1, -2);
// 	DrawGammaPadSettings( pad6PartCompChargedPions1, 0.12, 0.0, 0.02, 0.);
// 	pad6PartCompChargedPions1->Draw();
// 	TPad* pad6PartCompChargedPions2 = new TPad("pad6PartCompChargedPions2", "", 0., 0., 0.35, 0.52,-1, -1, -2);
// 	DrawGammaPadSettings( pad6PartCompChargedPions2, 0.12, 0.0, 0., 0.12);
// 	pad6PartCompChargedPions2->Draw();
// 	
// 	TPad* pad6PartCompChargedPions3 = new TPad("pad6PartCompChargedPions3", "", 0.35, 0.52, 0.68, 1.,-1, -1, -2);
// 	DrawGammaPadSettings( pad6PartCompChargedPions3, 0.0, 0.0, 0.02, 0.);
// 	pad6PartCompChargedPions3->Draw();
// 	TPad* pad6PartCompChargedPions4 = new TPad("pad6PartCompChargedPions4", "", 0.35, 0., 0.68, 0.52,-1, -1, -2);
// 	DrawGammaPadSettings( pad6PartCompChargedPions4, 0.0, 0.0, 0., 0.12);
// 	pad6PartCompChargedPions4->Draw();
// 
// 	TPad* pad6PartCompChargedPions5 = new TPad("pad6PartCompChargedPions5", "", 0.68, 0.52, 1., 1.,-1, -1, -2);
// 	DrawGammaPadSettings( pad6PartCompChargedPions5, 0.0, 0.02, 0.02, 0.);
// 	pad6PartCompChargedPions5->Draw();
// 	TPad* pad6PartCompChargedPions6 = new TPad("pad6PartCompChargedPions6", "", 0.68, 0., 1., 0.52,-1, -1, -2);
// 	DrawGammaPadSettings( pad6PartCompChargedPions6, 0.0, 0.02, 0., 0.12);
// 	pad6PartCompChargedPions6->Draw();
// 
// 	TH2F * histo2DCompCombinedRatio2;
// 	histo2DCompCombinedRatio2 = new TH2F("histo2DCompCombinedRatio2","histo2DCompCombinedRatio2",1000,0.,20.,1000,0.2,4.	);
// 	histo2DCompCombinedRatio2->GetYaxis()->SetRangeUser(0.6,2.1);
// 	histo2DCompCombinedRatio2->GetXaxis()->SetRangeUser(0.,15.);
// 	SetStyleHistoTH2ForGraphs(histo2DCompCombinedRatio2, "p_{T} (GeV/c)","#pi^{0}/#pi^{#pm}", 0.05,0.064, 0.05,0.06, 0.8,0.9, 512, 505);
// 	
// 	TH2F* histo2DCompCombinedRatio;
// 	histo2DCompCombinedRatio = new TH2F("histo2DCompCombinedRatio","histo2DCompCombinedRatio",1000,-0.25,20.,1000,0.2,4.	);
// 	histo2DCompCombinedRatio->GetYaxis()->SetRangeUser(0.6,2.1);
// 	histo2DCompCombinedRatio->GetXaxis()->SetRangeUser(-0.05,15.);
// 	SetStyleHistoTH2ForGraphs(histo2DCompCombinedRatio, "p_{T} (GeV/c)","#pi^{0}/#pi^{#pm}", 0.05,0.064, 0.05,0.06, 0.8,0.6, 512, 505); 
// 
// 	pad6PartCompChargedPions1->cd();
// 	histo2DCompCombinedRatio2->GetXaxis()->SetRangeUser(0.,15.);
// 	histo2DCompCombinedRatio2->GetYaxis()->SetRangeUser(0.6,2.1);
// 	histo2DCompCombinedRatio2->DrawCopy();
// 		
// 		DrawGammaSetMarkerTGraphErr(graphRatioPrelimComb0005,21,markerSizeComparison, kBlack , kBlack);;
// 		graphRatioPrelimComb0005->Draw("E1psame");
// 		TLatex *labelPi0PrelimCompFinalPbPb0005 = new TLatex(0.15,0.9,collisionSystemCent0.Data());
// 		SetStyleTLatex( labelPi0PrelimCompFinalPbPb0005, 0.05,4);
// 		labelPi0PrelimCompFinalPbPb0005->Draw();
// 				
// 		TLegend* legendPi0CompChargedPionsPbPb0005 = new TLegend(0.18,0.82,0.9,0.88);
// 		legendPi0CompChargedPionsPbPb0005->SetFillColor(0);
// 		legendPi0CompChargedPionsPbPb0005->SetLineColor(0);
// 		legendPi0CompChargedPionsPbPb0005->SetNColumns(1);
// 		legendPi0CompChargedPionsPbPb0005->SetTextSize(0.045);
// 		legendPi0CompChargedPionsPbPb0005->AddEntry(graphRatioPrelimComb0005,"#pi^{0} Prelim /#pi^{0} new","p");
// 		legendPi0CompChargedPionsPbPb0005->Draw();
// 		DrawGammaLines(0., 19.5 , 1, 1 ,1,kGray);
// 	
// 	histo2DCompCombinedRatio2->Draw("axis,same");
// 	pad6PartCompChargedPions1->Update();
// 	pad6PartCompChargedPions2->cd();
// 	histo2DCompCombinedRatio2->GetYaxis()->SetRangeUser(0.6,2.1);
//  	histo2DCompCombinedRatio2->DrawCopy();
// 	
// // 		DrawGammaSetMarkerTGraphErr(graphRatioPrelimComb2040,21,markerSizeComparison, kBlack , kBlack);
// // 		DrawGammaSetMarkerTGraphErr(graphRatioLowPtChargedPionsComb2040,20,markerSizeComparison, kBlue , kBlue);
// // 		graphRatioPrelimComb2040->Draw("E1psame");
// // 		graphRatioLowPtChargedPionsComb2040->Draw("E1psame");
// 
// 		TLatex *labelPi0PrelimCompFinalPbPb2040 = new TLatex(0.15,0.93,collisionSystemSemiCent.Data());
// 		SetStyleTLatex( labelPi0PrelimCompFinalPbPb2040, 0.05,4);
// 		labelPi0PrelimCompFinalPbPb2040->Draw();
// 		DrawGammaLines(0., 19.5 , 1, 1 ,1,kGray);	
// 
// 	histo2DCompCombinedRatio2->Draw("axis,same");
// 	pad6PartCompChargedPions2->Update();
// 	pad6PartCompChargedPions3->cd();
// 	histo2DCompCombinedRatio->GetXaxis()->SetRangeUser(-0.25,15.);
// 	histo2DCompCombinedRatio->GetYaxis()->SetRangeUser(0.6,2.1);
// 	histo2DCompCombinedRatio->DrawCopy();
// 			
//  		DrawGammaSetMarkerTGraphErr(graphRatioPrelimComb0510,21,markerSizeComparison, kBlack , kBlack);
//  		graphRatioPrelimComb0510->Draw("E1psame");
// 		
// 		TLatex *labelPi0PrelimCompFinalPbPb0510 = new TLatex(0.03,0.9,collisionSystemCent1.Data());
// 		SetStyleTLatex( labelPi0PrelimCompFinalPbPb0510, 0.05,4);
// 		labelPi0PrelimCompFinalPbPb0510->Draw(); 
// 		DrawGammaLines(0., 19.5 , 1, 1 ,1,kGray);
// 	
// 	histo2DCompCombinedRatio->Draw("axis,same");
// 	pad6PartCompChargedPions3->Update();
// 	pad6PartCompChargedPions4->cd();
// 	histo2DCompCombinedRatio->GetYaxis()->SetRangeUser(0.6,2.1);
// 	histo2DCompCombinedRatio->DrawCopy();
// 
// // 		DrawGammaSetMarkerTGraphErr(graphRatioPrelimComb4060,21,markerSizeComparison, kBlack , kBlack);
// // 		DrawGammaSetMarkerTGraphErr(graphRatioLowPtChargedPionsComb4060,20,markerSizeComparison, kBlue , kBlue);
// // 		graphRatioPrelimComb4060->Draw("E1psame");
// // 		graphRatioLowPtChargedPionsComb4060->Draw("E1psame");
// 		
// 		TLatex *labelPi0PrelimCompFinalPbPb4060 = new TLatex(0.03,0.93,collisionSystemSemiPer.Data());
// 		SetStyleTLatex( labelPi0PrelimCompFinalPbPb4060, 0.047,4);
// 		labelPi0PrelimCompFinalPbPb4060->Draw();		
// 		DrawGammaLines(0., 19.5 , 1, 1 ,1,kGray);
// 
// 	histo2DCompCombinedRatio->Draw("axis,same");
// 	
// 	pad6PartCompChargedPions4->Update();
// 	pad6PartCompChargedPions5->cd();
// 	histo2DCompCombinedRatio->GetYaxis()->SetRangeUser(0.6,2.1);
// 	histo2DCompCombinedRatio->DrawCopy();
// 	
// 		DrawGammaSetMarkerTGraphErr(graphRatioPrelimComb1020,21,markerSizeComparison, kBlack , kBlack);
// 		graphRatioPrelimComb1020->Draw("E1psame");
// 
// 	
// 		TLatex *labelPi0PrelimCompFinalPbPb1020 = new TLatex(0.03,0.9,collisionSystemCent2.Data());
// 		SetStyleTLatex( labelPi0PrelimCompFinalPbPb1020, 0.05,4);
// 		labelPi0PrelimCompFinalPbPb1020->Draw();		
// 		DrawGammaLines(0., 19.5 , 1, 1 ,1,kGray);
// 		
// 	histo2DCompCombinedRatio->Draw("axis,same");
// 	pad6PartCompChargedPions5->Update();
// 	pad6PartCompChargedPions6->cd();
// 	histo2DCompCombinedRatio->GetYaxis()->SetRangeUser(0.6,2.1);
// 	histo2DCompCombinedRatio->DrawCopy();
// 	
// // 		DrawGammaSetMarkerTGraphErr(graphRatioPrelimComb6080,21,markerSizeComparison, kBlack , kBlack);
// // 		DrawGammaSetMarkerTGraphErr(graphRatioLowPtChargedPionsComb6080,20,markerSizeComparison, kBlue , kBlue);
// // 		graphRatioPrelimComb6080->Draw("E1psame");
// // 		graphRatioLowPtChargedPionsComb6080->Draw("E1psame");
// 		
// 		TLatex *labelPi0PrelimCompFinalPbPb6080 = new TLatex(0.04,0.93,collisionSystemPer.Data());
// 		SetStyleTLatex( labelPi0PrelimCompFinalPbPb6080, 0.047,4);
// 		labelPi0PrelimCompFinalPbPb6080->Draw();	
// 		DrawGammaLines(0., 19.5 , 1, 1 ,1,kGray);
// 
// 	histo2DCompCombinedRatio->Draw("axis,same");
// 	
// 	pad6PartCompChargedPions6->Update();
// 
// 	canvas6PartCompChargedPions->Update();	
// 	canvas6PartCompChargedPions->SaveAs(Form("%s/ComparisonPreliminarytoNewCombined_6Parted_Paper.%s",outputDir.Data(),suffix.Data()));
// 	delete pad6PartCompChargedPions1;	
// 	delete pad6PartCompChargedPions2;	
// 	delete pad6PartCompChargedPions3;	
// 	delete pad6PartCompChargedPions4;	
// 	delete canvas6PartCompChargedPions;
// 
// 		// ***************************************************************************************************************
// 	// ************************************ Charged Pion  *********************************************************
// 	// ***************************************************************************************************************
// 	TCanvas * canvas6PartCompChargedIndPions = new TCanvas("canvas6PartCompChargedIndPions","",10,10,1834,1000);  // gives the page size		
// 	canvas6PartCompChargedIndPions->cd();
// 	DrawGammaCanvasSettings( canvas6PartCompChargedIndPions, 0.13, 0.0, 0.02, 0.09);
// 	
// 	TPad* pad6PartCompChargedIndPions1 = new TPad("pad6PartCompChargedIndPions1", "", 0., 0.52, 0.35, 1.,-1, -1, -2);
// 	DrawGammaPadSettings( pad6PartCompChargedIndPions1, 0.12, 0.0, 0.02, 0.);
// 	pad6PartCompChargedIndPions1->Draw();
// 	TPad* pad6PartCompChargedIndPions2 = new TPad("pad6PartCompChargedIndPions2", "", 0., 0., 0.35, 0.52,-1, -1, -2);
// 	DrawGammaPadSettings( pad6PartCompChargedIndPions2, 0.12, 0.0, 0., 0.12);
// 	pad6PartCompChargedIndPions2->Draw();
// 	
// 	TPad* pad6PartCompChargedIndPions3 = new TPad("pad6PartCompChargedIndPions3", "", 0.35, 0.52, 0.68, 1.,-1, -1, -2);
// 	DrawGammaPadSettings( pad6PartCompChargedIndPions3, 0.0, 0.0, 0.02, 0.);
// 	pad6PartCompChargedIndPions3->Draw();
// 	TPad* pad6PartCompChargedIndPions4 = new TPad("pad6PartCompChargedIndPions4", "", 0.35, 0., 0.68, 0.52,-1, -1, -2);
// 	DrawGammaPadSettings( pad6PartCompChargedIndPions4, 0.0, 0.0, 0., 0.12);
// 	pad6PartCompChargedIndPions4->Draw();
// 
// 	TPad* pad6PartCompChargedIndPions5 = new TPad("pad6PartCompChargedIndPions5", "", 0.68, 0.52, 1., 1.,-1, -1, -2);
// 	DrawGammaPadSettings( pad6PartCompChargedIndPions5, 0.0, 0.02, 0.02, 0.);
// 	pad6PartCompChargedIndPions5->Draw();
// 	TPad* pad6PartCompChargedIndPions6 = new TPad("pad6PartCompChargedIndPions6", "", 0.68, 0., 1., 0.52,-1, -1, -2);
// 	DrawGammaPadSettings( pad6PartCompChargedIndPions6, 0.0, 0.02, 0., 0.12);
// 	pad6PartCompChargedIndPions6->Draw();
// 
// 	pad6PartCompChargedIndPions1->cd();
// 	histo2DCompCombinedRatio2->GetXaxis()->SetRangeUser(0.,15.);
// 	histo2DCompCombinedRatio2->GetYaxis()->SetRangeUser(0.6,2.1);
// 	histo2DCompCombinedRatio2->DrawCopy();
// 		
// 		DrawGammaSetMarkerTGraphErr(graphRatioPrelimPCM0005,21,markerSizeComparison, kBlack , kBlack);
// 		graphRatioPrelimPCM0005->Draw("E1psame");
// 		DrawGammaSetMarkerTGraphErr(graphRatioPrelimPHOS0005,21,markerSizeComparison, kRed+2 , kRed+2);
// 		graphRatioPrelimPHOS0005->Draw("E1psame");
// 		
// 		labelPi0PrelimCompFinalPbPb0005->Draw();
// 				
// 		TLegend* legendPi0CompChargedIndPionsPbPb0005 = new TLegend(0.18,0.76,0.9,0.88);
// 		legendPi0CompChargedIndPionsPbPb0005->SetFillColor(0);
// 		legendPi0CompChargedIndPionsPbPb0005->SetLineColor(0);
// 		legendPi0CompChargedIndPionsPbPb0005->SetNColumns(1);
// 		legendPi0CompChargedIndPionsPbPb0005->SetTextSize(0.045);
// 		legendPi0CompChargedIndPionsPbPb0005->AddEntry(graphRatioPrelimPCM0005,"#pi^{0} Prelim /#pi^{0} new PCM","p");
// 		legendPi0CompChargedIndPionsPbPb0005->AddEntry(graphRatioPrelimPHOS0005,"#pi^{0} Prelim /#pi^{0} new PHOS","p");
// 		legendPi0CompChargedIndPionsPbPb0005->Draw();
// 		DrawGammaLines(0., 19.5 , 1, 1 ,1,kGray);
// 	
// 	histo2DCompCombinedRatio2->Draw("axis,same");
// 	pad6PartCompChargedIndPions1->Update();
// 	pad6PartCompChargedIndPions2->cd();
// 	histo2DCompCombinedRatio2->GetYaxis()->SetRangeUser(0.6,2.1);
//  	histo2DCompCombinedRatio2->DrawCopy();
// 	
// // 		DrawGammaSetMarkerTGraphErr(graphRatioPrelimPCM2040,21,markerSizeComparison, kBlack , kBlack);
// // 		DrawGammaSetMarkerTGraphErr(graphRatioLowPtChargedPionsPCM2040,20,markerSizeComparison, kBlue+2, kBlue+2);
// // 		graphRatioPrelimPCM2040->Draw("E1psame");
// // 		graphRatioLowPtChargedPionsPCM2040->Draw("E1psame");
// // 		DrawGammaSetMarkerTGraphErr(graphRatioPrelimPHOS2040,21,markerSizeComparison, kRed+2 , kRed+2);
// // 		DrawGammaSetMarkerTGraphErr(graphRatioLowPtChargedPionsPHOS2040,20,markerSizeComparison, kMagenta+1, kMagenta+1);
// // 		graphRatioPrelimPHOS2040->Draw("E1psame");
// // 		graphRatioLowPtChargedPionsPHOS2040->Draw("E1psame");
// // 
// 		
// 		labelPi0PrelimCompFinalPbPb2040->Draw();
// 		DrawGammaLines(0., 19.5 , 1, 1 ,1,kGray);	
// 
// 	histo2DCompCombinedRatio2->Draw("axis,same");
// 	pad6PartCompChargedIndPions2->Update();
// 	pad6PartCompChargedIndPions3->cd();
// 	histo2DCompCombinedRatio->GetXaxis()->SetRangeUser(-0.25,15.);
// 	histo2DCompCombinedRatio->GetYaxis()->SetRangeUser(0.6,2.1);
// 	histo2DCompCombinedRatio->DrawCopy();
// 			
//  		DrawGammaSetMarkerTGraphErr(graphRatioPrelimPCM0510,21,markerSizeComparison, kBlack , kBlack);
//  		graphRatioPrelimPCM0510->Draw("E1psame");
// // 		
// 		DrawGammaSetMarkerTGraphErr(graphRatioPrelimPHOS0510,21,markerSizeComparison, kRed+2 , kRed+2);
// 		graphRatioPrelimPHOS0510->Draw("E1psame");
// 		
// 		labelPi0PrelimCompFinalPbPb0510->Draw(); 
// 		DrawGammaLines(0., 19.5 , 1, 1 ,1,kGray);
// 	
// 	histo2DCompCombinedRatio->Draw("axis,same");
// 	pad6PartCompChargedIndPions3->Update();
// 	pad6PartCompChargedIndPions4->cd();
// 	histo2DCompCombinedRatio->GetYaxis()->SetRangeUser(0.6,2.1);
// 	histo2DCompCombinedRatio->DrawCopy();
// 
// // 		DrawGammaSetMarkerTGraphErr(graphRatioPrelimPCM4060,21,markerSizeComparison, kBlack , kBlack);
// // 		DrawGammaSetMarkerTGraphErr(graphRatioLowPtChargedPionsPCM4060,20,markerSizeComparison, kBlue+2, kBlue+2);
// // 		graphRatioPrelimPCM4060->Draw("E1psame");
// // 		graphRatioLowPtChargedPionsPCM4060->Draw("E1psame");
// // 		DrawGammaSetMarkerTGraphErr(graphRatioPrelimPHOS4060,21,markerSizeComparison,  kRed+2 , kRed+2);
// // 		DrawGammaSetMarkerTGraphErr(graphRatioLowPtChargedPionsPHOS4060,20,markerSizeComparison,  kMagenta+1, kMagenta+1);
// // 		graphRatioPrelimPHOS4060->Draw("E1psame");
// // 		graphRatioLowPtChargedPionsPHOS4060->Draw("E1psame");
// 		
// 		labelPi0PrelimCompFinalPbPb4060->Draw();		
// 		DrawGammaLines(0., 19.5 , 1, 1 ,1,kGray);
// 
// 	histo2DCompCombinedRatio->Draw("axis,same");
// 	
// 	pad6PartCompChargedIndPions4->Update();
// 	pad6PartCompChargedIndPions5->cd();
// 	histo2DCompCombinedRatio->GetYaxis()->SetRangeUser(0.6,2.1);
// 	histo2DCompCombinedRatio->DrawCopy();
// 	
// 		DrawGammaSetMarkerTGraphErr(graphRatioPrelimPCM1020,21,markerSizeComparison, kBlack , kBlack);
// 		graphRatioPrelimPCM1020->Draw("E1psame");
// 		DrawGammaSetMarkerTGraphErr(graphRatioPrelimPHOS1020,21,markerSizeComparison, kRed+2 , kRed+2);
// 		graphRatioPrelimPHOS1020->Draw("E1psame");
// 
// 	
// 		labelPi0PrelimCompFinalPbPb1020->Draw();		
// 		DrawGammaLines(0., 19.5 , 1, 1 ,1,kGray);
// 		
// 	histo2DCompCombinedRatio->Draw("axis,same");
// 	pad6PartCompChargedIndPions5->Update();
// 	pad6PartCompChargedIndPions6->cd();
// 	histo2DCompCombinedRatio->GetYaxis()->SetRangeUser(0.6,2.1);
// 	histo2DCompCombinedRatio->DrawCopy();
// 	
// // 		DrawGammaSetMarkerTGraphErr(graphRatioPrelimPCM6080,21,markerSizeComparison, kBlack , kBlack);
// // 		DrawGammaSetMarkerTGraphErr(graphRatioLowPtChargedPionsPCM6080,20,markerSizeComparison, kBlue+2, kBlue+2);
// // 		graphRatioPrelimPCM6080->Draw("E1psame");
// // 		graphRatioLowPtChargedPionsPCM6080->Draw("E1psame");
// // 		DrawGammaSetMarkerTGraphErr(graphRatioPrelimPHOS6080,21,markerSizeComparison, kRed+2 , kRed+2);
// // 		DrawGammaSetMarkerTGraphErr(graphRatioLowPtChargedPionsPHOS6080,20,markerSizeComparison,  kMagenta+1, kMagenta+1);
// // 		graphRatioPrelimPHOS6080->Draw("E1psame");
// // 		graphRatioLowPtChargedPionsPHOS6080->Draw("E1psame");
// 		
// 		labelPi0PrelimCompFinalPbPb6080->Draw();	
// 		DrawGammaLines(0., 19.5 , 1, 1 ,1,kGray);
// 
// 	histo2DCompCombinedRatio->Draw("axis,same");
// 	
// 	pad6PartCompChargedIndPions6->Update();
// 
// 	canvas6PartCompChargedIndPions->Update();	
// 	canvas6PartCompChargedIndPions->SaveAs(Form("%s/ComparisonPreliminarytoNewInd_6Parted_Paper.%s",outputDir.Data(),suffix.Data()));
// 	delete pad6PartCompChargedIndPions1;	
// 	delete pad6PartCompChargedIndPions2;	
// 	delete pad6PartCompChargedIndPions3;	
// 	delete pad6PartCompChargedIndPions4;	
// 	delete canvas6PartCompChargedIndPions;

}