/*******************************************************************************
 ****** 	provided by Gamma Conversion Group, PWGGA,								*****
 ******		Ana Marin, marin@physi.uni-heidelberg.de								*****
 ******	  	Martin Wilde, m_wild03@uni-muenster.de 								*****
 ******		Friederike Bock, friederike.bock@cern.ch								*****
 *******************************************************************************/

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
#include "CommonHeaders/ConversionFunctionsBasicsAndLabeling.h"

void ShowEventStats_ConvCalo_pp(TString suffix = "eps"){
	gROOT->Reset();	
	gROOT->SetStyle("Plain");
	
	StyleSettingsThesis();	
	SetPlotStyle();
	TGaxis::SetMaxDigits(6);
	
	TString date = ReturnDateString();

// 	cout << fileNameEvents.Data() << endl;
	
	TString outputDir = "EventStats";
	gSystem->Exec("mkdir "+outputDir);
		
	const char* Inputname = Form("%s/EventStats.root",outputDir.Data());
	TFile* EventStatsFile = new TFile(Inputname);
		
		TGraphErrors* fractionOfGammasLHC11a_2760GeV = (TGraphErrors*)EventStatsFile->Get("fracGammas_pp2760GeV_LHC11a");
		TGraphErrors* fractionOfPi0LHC11a_2760GeV = (TGraphErrors*)EventStatsFile->Get("fractionOfPi0InCent_pp2760GeV_LHC11a");
		TGraphErrors* fractionOfEtaLHC11a_2760GeV = (TGraphErrors*)EventStatsFile->Get("fractionOfEtaInCent_pp2760GeV_LHC11a");
		TGraphErrors* fractionOfWOVtxLHC11a_2760GeV = (TGraphErrors*)EventStatsFile->Get("fracWOVtx_pp2760GeV_LHC11a");
		TGraphErrors* fractionOfWVtxOutside10cmLHC11a_2760GeV = (TGraphErrors*)EventStatsFile->Get("fracWVtxOutside10cm_pp2760GeV_LHC11a");
		TGraphErrors* fractionOfGoodEventsLHC11a_2760GeV = (TGraphErrors*)EventStatsFile->Get("fracGoodEvents_pp2760GeV_LHC11a");
		TGraphErrors* fractionOfNormAllLHC11a_2760GeV = (TGraphErrors*)EventStatsFile->Get("fracNormAll_pp2760GeV_LHC11a");
		TGraphErrors* fractionOfNormMinBiasLHC11a_2760GeV = (TGraphErrors*)EventStatsFile->Get("fracNormMinBias_pp2760GeV_LHC11a");
		TGraphErrors* fractionOfPileUpLHC11a_2760GeV = (TGraphErrors*)EventStatsFile->Get("fracPileUp_pp2760GeV_LHC11a");
		TGraphErrors* meanTrackMultTPCDataLHC11a_2760GeV = (TGraphErrors*)EventStatsFile->Get("meanTrackMultTPCInCent_pp2760GeV_LHC11a");
		TGraphErrors* widthPi0LHC11a_2760GeV = (TGraphErrors*)EventStatsFile->Get("widthPi0perRun_pp2760GeV_LHC11a");
		TGraphErrors* massPi0LHC11a_2760GeV = (TGraphErrors*)EventStatsFile->Get("massPi0perRun_pp2760GeV_LHC11a");
		TGraphErrors* widthEtaLHC11a_2760GeV = (TGraphErrors*)EventStatsFile->Get("widthEtaperRun_pp2760GeV_LHC11a");
		TGraphErrors* massEtaLHC11a_2760GeV = (TGraphErrors*)EventStatsFile->Get("massEtaperRun_pp2760GeV_LHC11a");

		TGraphErrors* fractionOfGammasLHC12f1a_2760GeV = (TGraphErrors*)EventStatsFile->Get("fracGammas_pp2760GeV_LHC12f1a");
		TGraphErrors* fractionOfPi0LHC12f1a_2760GeV = (TGraphErrors*)EventStatsFile->Get("fractionOfPi0InCent_pp2760GeV_LHC12f1a");
		TGraphErrors* fractionOfEtaLHC12f1a_2760GeV = (TGraphErrors*)EventStatsFile->Get("fractionOfEtaInCent_pp2760GeV_LHC12f1a");
		TGraphErrors* fractionOfWOVtxLHC12f1a_2760GeV = (TGraphErrors*)EventStatsFile->Get("fracWOVtx_pp2760GeV_LHC12f1a");
		TGraphErrors* fractionOfWVtxOutside10cmLHC12f1a_2760GeV = (TGraphErrors*)EventStatsFile->Get("fracWVtxOutside10cm_pp2760GeV_LHC12f1a");
		TGraphErrors* fractionOfGoodEventsLHC12f1a_2760GeV = (TGraphErrors*)EventStatsFile->Get("fracGoodEvents_pp2760GeV_LHC12f1a");
		TGraphErrors* fractionOfNormAllLHC12f1a_2760GeV = (TGraphErrors*)EventStatsFile->Get("fracNormAll_pp2760GeV_LHC12f1a");
		TGraphErrors* fractionOfNormMinBiasLHC12f1a_2760GeV = (TGraphErrors*)EventStatsFile->Get("fracNormMinBias_pp2760GeV_LHC12f1a");
		TGraphErrors* fractionOfPileUpLHC12f1a_2760GeV = (TGraphErrors*)EventStatsFile->Get("fracPileUp_pp2760GeV_LHC12f1a");
		TGraphErrors* meanTrackMultTPCDataLHC12f1a_2760GeV = (TGraphErrors*)EventStatsFile->Get("meanTrackMultTPCInCent_pp2760GeV_LHC12f1a");
		TGraphErrors* widthPi0LHC12f1a_2760GeV = (TGraphErrors*)EventStatsFile->Get("widthPi0perRun_pp2760GeV_LHC12f1a");
		TGraphErrors* massPi0LHC12f1a_2760GeV = (TGraphErrors*)EventStatsFile->Get("massPi0perRun_pp2760GeV_LHC12f1a");
		TGraphErrors* widthEtaLHC12f1a_2760GeV = (TGraphErrors*)EventStatsFile->Get("widthEtaperRun_pp2760GeV_LHC12f1a");
		TGraphErrors* massEtaLHC12f1a_2760GeV = (TGraphErrors*)EventStatsFile->Get("massEtaperRun_pp2760GeV_LHC12f1a");
		
		TGraphErrors* fractionOfGammasLHC12f1b_2760GeV = (TGraphErrors*)EventStatsFile->Get("fracGammas_pp2760GeV_LHC12f1b");
		TGraphErrors* fractionOfPi0LHC12f1b_2760GeV = (TGraphErrors*)EventStatsFile->Get("fractionOfPi0InCent_pp2760GeV_LHC12f1b");
		TGraphErrors* fractionOfEtaLHC12f1b_2760GeV = (TGraphErrors*)EventStatsFile->Get("fractionOfEtaInCent_pp2760GeV_LHC12f1b");
		TGraphErrors* fractionOfWOVtxLHC12f1b_2760GeV = (TGraphErrors*)EventStatsFile->Get("fracWOVtx_pp2760GeV_LHC12f1b");
		TGraphErrors* fractionOfWVtxOutside10cmLHC12f1b_2760GeV = (TGraphErrors*)EventStatsFile->Get("fracWVtxOutside10cm_pp2760GeV_LHC12f1b");
		TGraphErrors* fractionOfGoodEventsLHC12f1b_2760GeV = (TGraphErrors*)EventStatsFile->Get("fracGoodEvents_pp2760GeV_LHC12f1b");
		TGraphErrors* fractionOfNormAllLHC12f1b_2760GeV = (TGraphErrors*)EventStatsFile->Get("fracNormAll_pp2760GeV_LHC12f1b");
		TGraphErrors* fractionOfNormMinBiasLHC12f1b_2760GeV = (TGraphErrors*)EventStatsFile->Get("fracNormMinBias_pp2760GeV_LHC12f1b");
		TGraphErrors* fractionOfPileUpLHC12f1b_2760GeV = (TGraphErrors*)EventStatsFile->Get("fracPileUp_pp2760GeV_LHC12f1b");
		TGraphErrors* meanTrackMultTPCDataLHC12f1b_2760GeV = (TGraphErrors*)EventStatsFile->Get("meanTrackMultTPCInCent_pp2760GeV_LHC12f1b");
		TGraphErrors* widthPi0LHC12f1b_2760GeV = (TGraphErrors*)EventStatsFile->Get("widthPi0perRun_pp2760GeV_LHC12f1b");
		TGraphErrors* massPi0LHC12f1b_2760GeV = (TGraphErrors*)EventStatsFile->Get("massPi0perRun_pp2760GeV_LHC12f1b");
		TGraphErrors* widthEtaLHC12f1b_2760GeV = (TGraphErrors*)EventStatsFile->Get("widthEtaperRun_pp2760GeV_LHC12f1b");
		TGraphErrors* massEtaLHC12f1b_2760GeV = (TGraphErrors*)EventStatsFile->Get("massEtaperRun_pp2760GeV_LHC12f1b");

	
// 	Width_t 	widthLinesBoxes;

	TString collisionSystemPP = "pp #sqrt{#it{s}} = 2.76 TeV";		
// 	Color_t 	colorPi0900GeV 			= kRed;
	Color_t 	colorPi02760GeV 			= kMagenta+1;
// 	Color_t	colorPi07TeV				= kBlue;
// 	Color_t 	colorCommonMCPythia900GeV 	= colorPi0900GeV-4;
	Color_t 	colorCommonMCPythia2760GeV = colorPi02760GeV+2;
// 	Color_t 	colorCommonMCPythia7TeV 	= colorPi07TeV+3;
// 	Color_t 	colorCommonMCPhojet900GeV 	= colorPi0900GeV+2;
	Color_t 	colorCommonMCPhojet2760GeV = colorPi02760GeV-4;
// 	Color_t 	colorCommonMCPhojet7TeV 	= colorPi07TeV-3;

// 	Style_t 	markerStyleCommmonSpectrum7TeV 	= 20 ;
// 	Style_t 	markerStyleCommmonSpectrum900GeV = 21 ;
	Style_t 	markerStyleCommmonSpectrum2760GeV = 29 ;
	
// 	Style_t 	markerStyleCommmonSpectrumMC7TeV 	= 24 ;
// 	Style_t 	markerStyleCommmonSpectrumMC900GeV 	= 25 ;
	Style_t 	markerStyleCommmonSpectrumMC2760GeV 	= 30 ;
	
// 	Size_t 	markerSizeCommonSpectrumPi07TeV 	= 1.8;
// 	Size_t 	markerSizeCommonSpectrumPi0900GeV = 1.8;
	Size_t 	markerSizeCommonSpectrumPi02760GeV 	= 4.5;

	
	DrawGammaSetMarkerTGraphErr( fractionOfGammasLHC11a_2760GeV,  markerStyleCommmonSpectrum2760GeV, markerSizeCommonSpectrumPi02760GeV, colorPi02760GeV, colorPi02760GeV);
	DrawGammaSetMarkerTGraphErr( fractionOfPi0LHC11a_2760GeV,  markerStyleCommmonSpectrum2760GeV, markerSizeCommonSpectrumPi02760GeV, colorPi02760GeV, colorPi02760GeV);	
	DrawGammaSetMarkerTGraphErr( fractionOfEtaLHC11a_2760GeV,  markerStyleCommmonSpectrum2760GeV, markerSizeCommonSpectrumPi02760GeV, colorPi02760GeV, colorPi02760GeV);
	DrawGammaSetMarkerTGraphErr( massPi0LHC11a_2760GeV,  markerStyleCommmonSpectrum2760GeV, markerSizeCommonSpectrumPi02760GeV, colorPi02760GeV, colorPi02760GeV);
	DrawGammaSetMarkerTGraphErr( widthPi0LHC11a_2760GeV,  markerStyleCommmonSpectrum2760GeV, markerSizeCommonSpectrumPi02760GeV, colorPi02760GeV, colorPi02760GeV);
	DrawGammaSetMarkerTGraphErr( massEtaLHC11a_2760GeV,  markerStyleCommmonSpectrum2760GeV, markerSizeCommonSpectrumPi02760GeV, colorPi02760GeV, colorPi02760GeV);
	DrawGammaSetMarkerTGraphErr( widthEtaLHC11a_2760GeV,  markerStyleCommmonSpectrum2760GeV, markerSizeCommonSpectrumPi02760GeV, colorPi02760GeV, colorPi02760GeV);
	DrawGammaSetMarkerTGraphErr( fractionOfWOVtxLHC11a_2760GeV,  markerStyleCommmonSpectrum2760GeV, markerSizeCommonSpectrumPi02760GeV, colorPi02760GeV, colorPi02760GeV);
	DrawGammaSetMarkerTGraphErr( fractionOfWVtxOutside10cmLHC11a_2760GeV,  markerStyleCommmonSpectrum2760GeV, markerSizeCommonSpectrumPi02760GeV, colorPi02760GeV, colorPi02760GeV);
	DrawGammaSetMarkerTGraphErr( fractionOfGoodEventsLHC11a_2760GeV,  markerStyleCommmonSpectrum2760GeV, markerSizeCommonSpectrumPi02760GeV, colorPi02760GeV, colorPi02760GeV);
	DrawGammaSetMarkerTGraphErr( fractionOfNormAllLHC11a_2760GeV,  markerStyleCommmonSpectrum2760GeV, markerSizeCommonSpectrumPi02760GeV, colorPi02760GeV, colorPi02760GeV);
	DrawGammaSetMarkerTGraphErr( fractionOfNormMinBiasLHC11a_2760GeV,  markerStyleCommmonSpectrum2760GeV, markerSizeCommonSpectrumPi02760GeV, colorPi02760GeV, colorPi02760GeV);
	DrawGammaSetMarkerTGraphErr( fractionOfPileUpLHC11a_2760GeV,  markerStyleCommmonSpectrum2760GeV, markerSizeCommonSpectrumPi02760GeV, colorPi02760GeV, colorPi02760GeV);
	
	DrawGammaSetMarkerTGraphErr( fractionOfGammasLHC12f1a_2760GeV,  markerStyleCommmonSpectrumMC2760GeV, markerSizeCommonSpectrumPi02760GeV, colorCommonMCPythia2760GeV, colorCommonMCPythia2760GeV);
	DrawGammaSetMarkerTGraphErr( fractionOfPi0LHC12f1a_2760GeV,  markerStyleCommmonSpectrumMC2760GeV, markerSizeCommonSpectrumPi02760GeV, colorCommonMCPythia2760GeV, colorCommonMCPythia2760GeV);
	DrawGammaSetMarkerTGraphErr( fractionOfEtaLHC12f1a_2760GeV,  markerStyleCommmonSpectrumMC2760GeV, markerSizeCommonSpectrumPi02760GeV, colorCommonMCPythia2760GeV, colorCommonMCPythia2760GeV);
	DrawGammaSetMarkerTGraphErr( fractionOfWOVtxLHC12f1a_2760GeV,  markerStyleCommmonSpectrumMC2760GeV, markerSizeCommonSpectrumPi02760GeV, colorCommonMCPythia2760GeV, colorCommonMCPythia2760GeV);
	DrawGammaSetMarkerTGraphErr( fractionOfWVtxOutside10cmLHC12f1a_2760GeV,  markerStyleCommmonSpectrumMC2760GeV, markerSizeCommonSpectrumPi02760GeV, colorCommonMCPythia2760GeV, colorCommonMCPythia2760GeV);
	DrawGammaSetMarkerTGraphErr( fractionOfGoodEventsLHC12f1a_2760GeV,  markerStyleCommmonSpectrumMC2760GeV, markerSizeCommonSpectrumPi02760GeV, colorCommonMCPythia2760GeV, colorCommonMCPythia2760GeV);
	DrawGammaSetMarkerTGraphErr( fractionOfNormAllLHC12f1a_2760GeV,  markerStyleCommmonSpectrumMC2760GeV, markerSizeCommonSpectrumPi02760GeV, colorCommonMCPythia2760GeV, colorCommonMCPythia2760GeV);
	DrawGammaSetMarkerTGraphErr( fractionOfNormMinBiasLHC12f1a_2760GeV,  markerStyleCommmonSpectrumMC2760GeV, markerSizeCommonSpectrumPi02760GeV, colorCommonMCPythia2760GeV, colorCommonMCPythia2760GeV);
	DrawGammaSetMarkerTGraphErr( fractionOfPileUpLHC12f1a_2760GeV,  markerStyleCommmonSpectrumMC2760GeV, markerSizeCommonSpectrumPi02760GeV, colorCommonMCPythia2760GeV, colorCommonMCPythia2760GeV);
	DrawGammaSetMarkerTGraphErr( massPi0LHC12f1a_2760GeV,  markerStyleCommmonSpectrumMC2760GeV, markerSizeCommonSpectrumPi02760GeV, colorCommonMCPythia2760GeV, colorCommonMCPythia2760GeV);
	DrawGammaSetMarkerTGraphErr( widthPi0LHC12f1a_2760GeV,  markerStyleCommmonSpectrumMC2760GeV, markerSizeCommonSpectrumPi02760GeV, colorCommonMCPythia2760GeV, colorCommonMCPythia2760GeV);
	DrawGammaSetMarkerTGraphErr( massEtaLHC12f1a_2760GeV,  markerStyleCommmonSpectrumMC2760GeV, markerSizeCommonSpectrumPi02760GeV, colorCommonMCPythia2760GeV, colorCommonMCPythia2760GeV);
	DrawGammaSetMarkerTGraphErr( widthEtaLHC12f1a_2760GeV,  markerStyleCommmonSpectrumMC2760GeV, markerSizeCommonSpectrumPi02760GeV, colorCommonMCPythia2760GeV, colorCommonMCPythia2760GeV);
	
	DrawGammaSetMarkerTGraphErr( fractionOfGammasLHC12f1b_2760GeV,  markerStyleCommmonSpectrumMC2760GeV, markerSizeCommonSpectrumPi02760GeV, colorCommonMCPhojet2760GeV, colorCommonMCPhojet2760GeV);
	DrawGammaSetMarkerTGraphErr( fractionOfPi0LHC12f1b_2760GeV,  markerStyleCommmonSpectrumMC2760GeV, markerSizeCommonSpectrumPi02760GeV, colorCommonMCPhojet2760GeV, colorCommonMCPhojet2760GeV);
	DrawGammaSetMarkerTGraphErr( fractionOfEtaLHC12f1b_2760GeV,  markerStyleCommmonSpectrumMC2760GeV, markerSizeCommonSpectrumPi02760GeV, colorCommonMCPhojet2760GeV, colorCommonMCPhojet2760GeV);
	DrawGammaSetMarkerTGraphErr( fractionOfWOVtxLHC12f1b_2760GeV,  markerStyleCommmonSpectrumMC2760GeV, markerSizeCommonSpectrumPi02760GeV, colorCommonMCPhojet2760GeV, colorCommonMCPhojet2760GeV);
	DrawGammaSetMarkerTGraphErr( fractionOfWVtxOutside10cmLHC12f1b_2760GeV,  markerStyleCommmonSpectrumMC2760GeV, markerSizeCommonSpectrumPi02760GeV, colorCommonMCPhojet2760GeV, colorCommonMCPhojet2760GeV);
	DrawGammaSetMarkerTGraphErr( fractionOfGoodEventsLHC12f1b_2760GeV,  markerStyleCommmonSpectrumMC2760GeV, markerSizeCommonSpectrumPi02760GeV, colorCommonMCPhojet2760GeV, colorCommonMCPhojet2760GeV);
	DrawGammaSetMarkerTGraphErr( fractionOfNormAllLHC12f1b_2760GeV,  markerStyleCommmonSpectrumMC2760GeV, markerSizeCommonSpectrumPi02760GeV, colorCommonMCPhojet2760GeV, colorCommonMCPhojet2760GeV);
	DrawGammaSetMarkerTGraphErr( fractionOfNormMinBiasLHC12f1b_2760GeV,  markerStyleCommmonSpectrumMC2760GeV, markerSizeCommonSpectrumPi02760GeV, colorCommonMCPhojet2760GeV, colorCommonMCPhojet2760GeV);
	DrawGammaSetMarkerTGraphErr( fractionOfPileUpLHC12f1b_2760GeV,  markerStyleCommmonSpectrumMC2760GeV, markerSizeCommonSpectrumPi02760GeV, colorCommonMCPhojet2760GeV, colorCommonMCPhojet2760GeV);
	DrawGammaSetMarkerTGraphErr( massPi0LHC12f1b_2760GeV,  markerStyleCommmonSpectrumMC2760GeV, markerSizeCommonSpectrumPi02760GeV, colorCommonMCPhojet2760GeV, colorCommonMCPhojet2760GeV);
	DrawGammaSetMarkerTGraphErr( widthPi0LHC12f1b_2760GeV,  markerStyleCommmonSpectrumMC2760GeV, markerSizeCommonSpectrumPi02760GeV, colorCommonMCPhojet2760GeV, colorCommonMCPhojet2760GeV);
	DrawGammaSetMarkerTGraphErr( massEtaLHC12f1b_2760GeV,  markerStyleCommmonSpectrumMC2760GeV, markerSizeCommonSpectrumPi02760GeV, colorCommonMCPhojet2760GeV, colorCommonMCPhojet2760GeV);
	DrawGammaSetMarkerTGraphErr( widthEtaLHC12f1b_2760GeV,  markerStyleCommmonSpectrumMC2760GeV, markerSizeCommonSpectrumPi02760GeV, colorCommonMCPhojet2760GeV, colorCommonMCPhojet2760GeV);
	
	TCanvas* canvasNGammaEvtppData = new TCanvas("canvasNGammaEvtppData","",200,10,1800,1400);  // gives the page size
	DrawGammaCanvasSettings( canvasNGammaEvtppData, 0.13, 0.01, 0.1, 0.1);
//  	canvasNGammaEvtppData->SetLogy();
	canvasNGammaEvtppData->cd();
	TH2F * histoNGammaPPB;
	histoNGammaPPB = new TH2F("histoNGammaPPB","histoNGammaPPB",120,146730,146865,100,0.,0.185);
// 	histoNGammaPP->GetXaxis()->SetRangeUser(0.,2100.);
	SetStyleHistoTH2ForGraphs(histoNGammaPPB, "Run number","#gamma_{cand}/N_{evt}",0.05,0.06, 0.05,0.06, 0.7,1.05);
	histoNGammaPPB->GetXaxis()->SetNdivisions(504,kTRUE);
// 	histoNGammaPPB->GetXaxis()->SetLabelOffset(-0.018);
	histoNGammaPPB->Draw("copy");

	fractionOfGammasLHC11a_2760GeV->Draw("pesame");
	fractionOfGammasLHC12f1b_2760GeV->Draw("pesame");
	fractionOfGammasLHC12f1a_2760GeV->Draw("pesame");
	
	canvasNGammaEvtppData->cd();
	TLegend* legendDataPP = new TLegend(0.12,0.905,0.6,1.);
	legendDataPP->SetFillColor(0);
	legendDataPP->SetLineColor(0);
	legendDataPP->SetFillStyle(0);
	legendDataPP->SetTextSize(0.04);
	legendDataPP->SetNColumns(3);
	legendDataPP->AddEntry((TObject*)0, "2.76 TeV:","");
	legendDataPP->AddEntry(fractionOfGammasLHC11a_2760GeV,"Data","p");
	legendDataPP->AddEntry(fractionOfGammasLHC12f1b_2760GeV,"Phojet","p");
	legendDataPP->AddEntry((TObject*)0, "","");
	legendDataPP->AddEntry((TObject*)0, "","");
	legendDataPP->AddEntry(fractionOfGammasLHC12f1a_2760GeV,"Pythia 8","p");

	legendDataPP->Draw();
	canvasNGammaEvtppData->SaveAs(Form("%s/FractionOfPhotonsPerEvent_PP2760GeV.%s",outputDir.Data(),suffix.Data()));
// 	delete canvasNGammaEvtppData;

   cout << "Plot 28" << endl;
	TCanvas* canvasWOVtxppData = new TCanvas("canvasWOVtxppData","",200,10,1800,1400);  // gives the page size
	DrawGammaCanvasSettings( canvasWOVtxppData, 0.13, 0.01, 0.1, 0.1);
	TH2F * histoWOVtxPPB;
	histoWOVtxPPB = new TH2F("histoWOVtxPPB","histoWOVtxPPB",120,146730,146865,100,0.,0.185);
// 	histoWOVtxPP->GetXaxis()->SetRangeUser(0.,2100.);
	SetStyleHistoTH2ForGraphs(histoWOVtxPPB, "Run number","N^{evt}_{w/o Vtx}/N^{evt}_{min Bias}",0.05,0.06, 0.05,0.06, 0.7,1.05);
	histoWOVtxPPB->GetXaxis()->SetNdivisions(504,kTRUE);
// 	histoWOVtxPPB->GetXaxis()->SetLabelOffset(-0.018);
	histoWOVtxPPB->Draw("copy");

	fractionOfWOVtxLHC11a_2760GeV->Draw("pesame");
	fractionOfWOVtxLHC12f1b_2760GeV->Draw("pesame");
	fractionOfWOVtxLHC12f1a_2760GeV->Draw("pesame");
	
	canvasWOVtxppData->cd();
	legendDataPP->Draw();
	canvasWOVtxppData->SaveAs(Form("%s/FractionOfEventsWOVtx_PP2760GeV.%s",outputDir.Data(),suffix.Data()));

   cout << "Plot 29" << endl;
	TCanvas* canvasFracPi0ppData = new TCanvas("canvasFracPi0ppData","",200,10,1800,1400);  // gives the page size
	DrawGammaCanvasSettings( canvasFracPi0ppData, 0.165, 0.01, 0.1, 0.1);
	
	TH2F * histoFracPi0PPB;
	histoFracPi0PPB = new TH2F("histoFracPi0PPB","histoFracPi0PPB",120,146730,146865,100,0.,0.00205);
// 	histoFracPi0PP->GetXaxis()->SetRangeUser(0.,2100.);
	SetStyleHistoTH2ForGraphs(histoFracPi0PPB, "Run number","N_{#pi^{0}_{cand}}/N_{evt}",0.05,0.06, 0.05,0.06, 0.7,1.4);
	histoFracPi0PPB->GetXaxis()->SetNdivisions(504,kTRUE);
	histoFracPi0PPB->GetYaxis()->SetNdivisions(505,kTRUE);
// 	histoFracPi0PPB->GetXaxis()->SetLabelOffset(-0.018);
	histoFracPi0PPB->Draw("copy");

	fractionOfPi0LHC11a_2760GeV->Draw("pesame");
// 	fractionOfPi0LHC12f1b_2760GeV->Draw("pesame");
// 	fractionOfPi0LHC12f1a_2760GeV->Draw("pesame");
	
	canvasFracPi0ppData->cd();
	TLegend* legendDataPPOnlyData = new TLegend(0.18,0.91,0.8,1.);
	legendDataPPOnlyData->SetFillColor(0);
	legendDataPPOnlyData->SetLineColor(0);
	legendDataPPOnlyData->SetFillStyle(0);
	legendDataPPOnlyData->SetTextSize(0.04);
	legendDataPPOnlyData->SetNColumns(3);
	legendDataPPOnlyData->AddEntry((TObject*)0, "2.76 TeV:","");
	legendDataPPOnlyData->AddEntry(fractionOfGammasLHC11a_2760GeV,"Data","p");
// 	legendDataPPOnlyData->AddEntry(fractionOfGammasLHC12f1b_2760GeV,"Phojet","p");
// 	legendDataPPOnlyData->AddEntry((TObject*)0, "","");
// 	legendDataPPOnlyData->AddEntry((TObject*)0, "","");
// 	legendDataPPOnlyData->AddEntry(fractionOfGammasLHC12f1a_2760GeV,"Pythia 8","p");

	legendDataPPOnlyData->Draw();

	canvasFracPi0ppData->SaveAs(Form("%s/FractionOfPi0_PP2760GeV.%s",outputDir.Data(),suffix.Data()));

   cout << "Plot 30" << endl;
	TCanvas* canvasMassPi0ppData = new TCanvas("canvasMassPi0ppData","",200,10,1800,1400);  // gives the page size
	DrawGammaCanvasSettings( canvasMassPi0ppData, 0.15, 0.01, 0.1, 0.1);
	TH2F * histoMassPi0PPB;
	histoMassPi0PPB = new TH2F("histoMassPi0PPB","histoMassPi0PPB",120,146730,146865,100,0.130,0.145);
// 	histoMassPi0PP->GetXaxis()->SetRangeUser(0.,2100.);
	SetStyleHistoTH2ForGraphs(histoMassPi0PPB, "Run number","m_{#pi^{0}} (GeV/c^{2})",0.05,0.06, 0.05,0.06, 0.7,1.25);
	histoMassPi0PPB->GetXaxis()->SetNdivisions(504,kTRUE);
// 	histoMassPi0PPB->GetXaxis()->SetLabelOffset(-0.018);
	histoMassPi0PPB->Draw("copy");

	massPi0LHC11a_2760GeV->Draw("pesame");
// 	massPi0LHC12f1b_2760GeV->Draw("pesame");
// 	massPi0LHC12f1a_2760GeV->Draw("pesame");
	DrawGammaLines(146730, 146865.,0.135, 0.135,1,kGray+2);
	canvasMassPi0ppData->cd();
	legendDataPPOnlyData->Draw();
	canvasMassPi0ppData->SaveAs(Form("%s/MassPi0_PP2760GeV.%s",outputDir.Data(),suffix.Data()));

   cout << "Plot 31" << endl;
	TCanvas* canvasWidthPi0ppData = new TCanvas("canvasWidthPi0ppData","",200,10,1800,1400);  // gives the page size
	DrawGammaCanvasSettings( canvasWidthPi0ppData, 0.15, 0.01, 0.1, 0.1);
	
	TH2F * histoWidthPi0PPB;
	histoWidthPi0PPB = new TH2F("histoWidthPi0PPB","histoWidthPi0PPB",120,146730,146865,100,0.0,0.040);
// 	histoWidthPi0PP->GetXaxis()->SetRangeUser(0.,2100.);
	SetStyleHistoTH2ForGraphs(histoWidthPi0PPB, "Run number","FWHM_{#pi^{0}} (GeV/c^{2})",0.05,0.06, 0.05,0.06, 0.7,1.25);
	histoWidthPi0PPB->GetXaxis()->SetNdivisions(504,kTRUE);
// 	histoWidthPi0PPB->GetXaxis()->SetLabelOffset(-0.018);
	histoWidthPi0PPB->Draw("copy");

	widthPi0LHC11a_2760GeV->Draw("pesame");
// 	widthPi0LHC12f1b_2760GeV->Draw("pesame");
// 	widthPi0LHC12f1a_2760GeV->Draw("pesame");
	
	canvasWidthPi0ppData->cd();
	legendDataPPOnlyData->Draw();
	canvasWidthPi0ppData->SaveAs(Form("%s/WidthPi0_PP2760GeV.%s",outputDir.Data(),suffix.Data()));
	
   cout << "Plot 32" << endl;
	TCanvas* canvasMassEtappData = new TCanvas("canvasMassEtappData","",200,10,1800,1400);  // gives the page size
	DrawGammaCanvasSettings( canvasMassEtappData, 0.15, 0.01, 0.1, 0.1);
	
	TH2F * histoMassEtaPPB;
	histoMassEtaPPB = new TH2F("histoMassEtaPPB","histoMassEtaPPB",120,146730,146865,100,0.53,0.57);
// 	histoMassEtaPP->GetXaxis()->SetRangeUser(0.,2100.);
	SetStyleHistoTH2ForGraphs(histoMassEtaPPB, "Run number","m_{#eta} (GeV/c^{2})",0.05,0.06, 0.05,0.06, 0.7,1.25);
	histoMassEtaPPB->GetXaxis()->SetNdivisions(504,kTRUE);
// 	histoMassEtaPPB->GetXaxis()->SetLabelOffset(-0.018);
	histoMassEtaPPB->Draw("copy");

	massEtaLHC11a_2760GeV->Draw("pesame");
// 	massEtaLHC12f1b_2760GeV->Draw("pesame");
// 	massEtaLHC12f1a_2760GeV->Draw("pesame");
	DrawGammaLines(146730, 146865.,0.548, 0.548,1,kGray+2);
	canvasMassEtappData->cd();
	legendDataPPOnlyData->Draw();
	canvasMassEtappData->SaveAs(Form("%s/MassEta_PP2760GeV.%s",outputDir.Data(),suffix.Data()));

   cout << "Plot 33" << endl;
	TCanvas* canvasWidthEtappData = new TCanvas("canvasWidthEtappData","",200,10,1800,1400);  // gives the page size
	DrawGammaCanvasSettings( canvasWidthEtappData, 0.15, 0.01, 0.1, 0.1);
	
	TH2F * histoWidthEtaPPB;
	histoWidthEtaPPB = new TH2F("histoWidthEtaPPB","histoWidthEtaPPB",120,146730,146865,100,0.0,0.03);
// 	histoWidthEtaPP->GetXaxis()->SetRangeUser(0.,2100.);
	SetStyleHistoTH2ForGraphs(histoWidthEtaPPB, "Run number","FWHM_{#eta} (GeV/c^{2})",0.05,0.06, 0.05,0.06, 0.7,1.25);
	histoWidthEtaPPB->GetXaxis()->SetNdivisions(504,kTRUE);
// 	histoWidthEtaPPB->GetXaxis()->SetLabelOffset(-0.018);
	histoWidthEtaPPB->Draw("copy");

	widthEtaLHC11a_2760GeV->Draw("pesame");
// 	widthEtaLHC12f1b_2760GeV->Draw("pesame");
// 	widthEtaLHC12f1a_2760GeV->Draw("pesame");
	
	canvasWidthEtappData->cd();
	legendDataPPOnlyData->Draw();
	canvasWidthEtappData->SaveAs(Form("%s/WidthEta_PP2760GeV.%s",outputDir.Data(),suffix.Data()));

	cout << "Plot 34" << endl;
	TCanvas* canvasFracEtappData = new TCanvas("canvasFracEtappData","",200,10,1800,1400);  // gives the page size
	DrawGammaCanvasSettings( canvasFracEtappData, 0.19, 0.01, 0.1, 0.1);
	
	TH2F * histoFracEtaPPB;
	histoFracEtaPPB = new TH2F("histoFracEtaPPB","histoFracEtaPPB",120,146730,146865,100,0.,0.00019);
// 	histoFracEtaPP->GetXaxis()->SetRangeUser(0.,2100.);
	SetStyleHistoTH2ForGraphs(histoFracEtaPPB, "Run number","N_{#eta_{cand}}/N_{evt}",0.05,0.06, 0.05,0.06, 0.7,1.65);
	histoFracEtaPPB->GetXaxis()->SetNdivisions(504,kTRUE);
	histoFracEtaPPB->GetYaxis()->SetNdivisions(504,kTRUE);
// 	histoFracEtaPPB->GetYaxis()->SetMaxDigits(3);
// 	histoFracEtaPPB->GetXaxis()->SetLabelOffset(-0.018);
	histoFracEtaPPB->Draw("copy");

	fractionOfEtaLHC11a_2760GeV->Draw("pesame");
// 	fractionOfEtaLHC12f1b_2760GeV->Draw("pesame");
// 	fractionOfEtaLHC12f1a_2760GeV->Draw("pesame");
	
	canvasFracEtappData->cd();
	legendDataPPOnlyData->Draw();
	canvasFracEtappData->SaveAs(Form("%s/FractionOfEta_PP2760GeV.%s",outputDir.Data(),suffix.Data()));

	cout << "Plot 35" << endl;
	TCanvas* canvasWVtxOutside10cmppData = new TCanvas("canvasWVtxOutside10cmppData","",200,10,1800,1400);  // gives the page size
	DrawGammaCanvasSettings( canvasWVtxOutside10cmppData, 0.14, 0.01, 0.1, 0.1);
	
	TH2F * histoWVtxOutside10cmPPB;
	histoWVtxOutside10cmPPB = new TH2F("histoWVtxOutside10cmPPB","histoWVtxOutside10cmPPB",120,146730,146865,100,0.,0.185);
// 	histoWVtxOutside10cmPP->GetXaxis()->SetRangeUser(0.,2100.);
	SetStyleHistoTH2ForGraphs(histoWVtxOutside10cmPPB, "Run number","N^{evt}_{Z_{vtx} > #pm 10cm}/N^{evt}_{min Bias}",0.05,0.06, 0.05,0.06, 0.7,1.1);
	histoWVtxOutside10cmPPB->GetXaxis()->SetNdivisions(504,kTRUE);
// 	histoWVtxOutside10cmPPB->GetXaxis()->SetLabelOffset(-0.018);
	histoWVtxOutside10cmPPB->Draw("copy");

	fractionOfWVtxOutside10cmLHC11a_2760GeV->Draw("pesame");
	fractionOfWVtxOutside10cmLHC12f1b_2760GeV->Draw("pesame");
	fractionOfWVtxOutside10cmLHC12f1a_2760GeV->Draw("pesame");
	
	canvasWVtxOutside10cmppData->cd();
	legendDataPP->Draw();

	canvasWVtxOutside10cmppData->SaveAs(Form("%s/FractionOfEventsWVtxOutside10cm_PP2760GeV.%s",outputDir.Data(),suffix.Data()));

   cout << "Plot 36" << endl;
	TCanvas* canvasNormAllppData = new TCanvas("canvasNormAllppData","",200,10,1800,1400);  // gives the page size
	DrawGammaCanvasSettings( canvasNormAllppData, 0.13, 0.01, 0.1, 0.1);
	
	TH2F * histoNormAllPPB;
	histoNormAllPPB = new TH2F("histoNormAllPPB","histoNormAllPPB",120,146730,146865,100,0.,1.1);
// 	histoNormAllPP->GetXaxis()->SetRangeUser(0.,2100.);
	SetStyleHistoTH2ForGraphs(histoNormAllPPB, "Run number","N^{evt}_{norm}/N^{evt}_{Phys. Sel.}",0.05,0.06, 0.05,0.06, 0.7,1.0);
	histoNormAllPPB->GetXaxis()->SetNdivisions(504,kTRUE);
// 	histoNormAllPPB->GetXaxis()->SetLabelOffset(-0.018);
	histoNormAllPPB->Draw("copy");

	fractionOfNormAllLHC11a_2760GeV->Draw("pesame");
	fractionOfNormAllLHC12f1b_2760GeV->Draw("pesame");
	fractionOfNormAllLHC12f1a_2760GeV->Draw("pesame");
	
	canvasNormAllppData->cd();
	legendDataPP->Draw();

	canvasNormAllppData->SaveAs(Form("%s/FractionOfEventsNormAll_PP2760GeV.%s",outputDir.Data(),suffix.Data()));

   cout << "Plot 37" << endl;
	TCanvas* canvasNormMinBiasppData = new TCanvas("canvasNormMinBiasppData","",200,10,1800,1400);  // gives the page size
	DrawGammaCanvasSettings( canvasNormMinBiasppData, 0.13, 0.01, 0.1, 0.1);
	
	TH2F * histoNormMinBiasPPB;
	histoNormMinBiasPPB = new TH2F("histoNormMinBiasPPB","histoNormMinBiasPPB",120,146730,146865,100,0.,1.1);
// 	histoNormMinBiasPP->GetXaxis()->SetRangeUser(0.,2100.);
	SetStyleHistoTH2ForGraphs(histoNormMinBiasPPB, "Run number","N^{evt}_{norm}/N^{evt}_{Min. Bias.}",0.05,0.06, 0.05,0.06, 0.7,0.95);
	histoNormMinBiasPPB->GetXaxis()->SetNdivisions(504,kTRUE);
// 	histoNormMinBiasPPB->GetXaxis()->SetLabelOffset(-0.018);
	histoNormMinBiasPPB->Draw("copy");

	fractionOfNormMinBiasLHC11a_2760GeV->Draw("pesame");
	fractionOfNormMinBiasLHC12f1b_2760GeV->Draw("pesame");
	fractionOfNormMinBiasLHC12f1a_2760GeV->Draw("pesame");
	
	canvasNormMinBiasppData->cd();
	legendDataPP->Draw();

	canvasNormMinBiasppData->SaveAs(Form("%s/FractionOfEventsNormMinBias_PP2760GeV.%s",outputDir.Data(),suffix.Data()));

   cout << "Plot 38" << endl;
	TCanvas* canvasPileUpppData = new TCanvas("canvasPileUpppData","",200,10,1800,1400);  // gives the page size
	DrawGammaCanvasSettings( canvasPileUpppData, 0.16, 0.01, 0.11, 0.1);

	TH2F * histoPileUpPPB;
	histoPileUpPPB = new TH2F("histoPileUpPPB","histoPileUpPPB",120,146730,146865,100,0.,0.021);
// 	histoPileUpPP->GetXaxis()->SetRangeUser(0.,2100.);
	SetStyleHistoTH2ForGraphs(histoPileUpPPB, "Run number","N^{evt}_{Pile up SPD}/N^{evt}_{Min. Bias}",0.05,0.06, 0.05,0.06, 0.75,1.3);
	histoPileUpPPB->GetXaxis()->SetNdivisions(504,kTRUE);
// 	histoPileUpPPB->GetXaxis()->SetLabelOffset(-0.018);
	histoPileUpPPB->Draw("copy");

	fractionOfPileUpLHC11a_2760GeV->Draw("pesame");
	fractionOfPileUpLHC12f1b_2760GeV->Draw("pesame");
	fractionOfPileUpLHC12f1a_2760GeV->Draw("pesame");
	
	canvasPileUpppData->cd();
	legendDataPP->Draw();

	canvasPileUpppData->SaveAs(Form("%s/FractionOfEventsPileUp_PP2760GeV.%s",outputDir.Data(),suffix.Data()));


	
	DrawGammaSetMarkerTGraphErr( meanTrackMultTPCDataLHC11a_2760GeV,  markerStyleCommmonSpectrum2760GeV, markerSizeCommonSpectrumPi02760GeV, colorPi02760GeV, colorPi02760GeV);	
	DrawGammaSetMarkerTGraphErr( meanTrackMultTPCDataLHC12f1a_2760GeV,  markerStyleCommmonSpectrumMC2760GeV, markerSizeCommonSpectrumPi02760GeV, colorCommonMCPythia2760GeV, colorCommonMCPythia2760GeV);
	DrawGammaSetMarkerTGraphErr( meanTrackMultTPCDataLHC12f1b_2760GeV,  markerStyleCommmonSpectrumMC2760GeV, markerSizeCommonSpectrumPi02760GeV, colorCommonMCPhojet2760GeV, colorCommonMCPhojet2760GeV);
	
	cout << "Plot 39" << endl;
	TCanvas* canvasNTPCTracks = new TCanvas("canvasNTPCTracks","",200,10,1800,1400);  // gives the page size
	
	DrawGammaCanvasSettings( canvasNTPCTracks, 0.1, 0.01, 0.1, 0.1);
	
	TH2F * histoTrackMultPPB;
	histoTrackMultPPB = new TH2F("histoTrackMultPPB","histoTrackMultPPB",120,146730,146865,100,0.,8.5);
// 	histoTrackMultPP->GetXaxis()->SetRangeUser(0.,2100.);
	SetStyleHistoTH2ForGraphs(histoTrackMultPPB, "Run number","#LT n TPC tracks #GT",0.05,0.06, 0.05,0.06, 0.7,0.75);
	histoTrackMultPPB->GetXaxis()->SetNdivisions(504,kTRUE);
	histoTrackMultPPB->GetYaxis()->SetLabelOffset(0.012);
	histoTrackMultPPB->Draw("copy");

	meanTrackMultTPCDataLHC11a_2760GeV->Draw("pesame");
	meanTrackMultTPCDataLHC12f1b_2760GeV->Draw("pesame");
	meanTrackMultTPCDataLHC12f1a_2760GeV->Draw("pesame");
	
	canvasNTPCTracks->cd();
	TLegend* legendMultDataPP = new TLegend(0.12,0.91,0.6,1.);
	legendMultDataPP->SetFillColor(0);
	legendMultDataPP->SetLineColor(0);
	legendMultDataPP->SetFillStyle(0);
	legendMultDataPP->SetTextSize(0.04);
	legendMultDataPP->SetNColumns(3);
	legendMultDataPP->AddEntry((TObject*)0, "2.76 TeV:","");
	legendMultDataPP->AddEntry(meanTrackMultTPCDataLHC11a_2760GeV,"Data","p");
	legendMultDataPP->AddEntry(meanTrackMultTPCDataLHC12f1b_2760GeV,"Phojet","p");
	legendMultDataPP->AddEntry((TObject*)0, "","");
	legendMultDataPP->AddEntry((TObject*)0, "","");
	legendMultDataPP->AddEntry(meanTrackMultTPCDataLHC12f1a_2760GeV,"Pythia 8","p");
	legendMultDataPP->Draw();

	canvasNTPCTracks->SaveAs(Form("%s/MeanMultiplicity_TPCTracks_PP2760GeV.%s",outputDir.Data(),suffix.Data()));
	delete canvasNTPCTracks;
	
}
