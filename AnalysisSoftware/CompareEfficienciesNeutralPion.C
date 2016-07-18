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

void CompareEfficienciesNeutralPion(TString outputDir = "eps/EfficiencyComparison", TString suffix = "eps"){

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
	TString collisionSystemCent = "0-10% Pb-Pb #sqrt{#it{s}_{_{NN}}} = 2.76 TeV";		
	TString collisionSystemSemiCent = "20-40% Pb-Pb #sqrt{#it{s}_{_{NN}}} = 2.76 TeV";		
	TString collisionSystemSemiPer = "40-60% Pb-Pb #sqrt{#it{s}_{_{NN}}} = 2.76 TeV";		
	TString collisionSystemPer = "60-80% Pb-Pb #sqrt{#it{s}_{_{NN}}} = 2.76 TeV";		

	Size_t markerSizeComparison = 0.5;
	Double_t maxPtMesonEffFit = 12.;
	Double_t minPtMesonEffFit = 1.2;
	Int_t offsetCorrectionHighPt= 1;
	TF1* fitTrueEffi = new TF1("EffiFitDummy","1 - [0]*exp([1]*x)+[1]");
	fitTrueEffi->SetRange(minPtMesonEffFit,maxPtMesonEffFit);

	//************************************************************************************************************************
	//******************************************** 0 - 5% ********************************************************************
	//************************************************************************************************************************
	TFile* fileNeutralPionData0005 = new TFile("900297209450304221200003012002000/PbPb_2.76TeV/Pi0_data_GammaConvV1WithoutCorrection_900297209450304221200003012002000.root");
	TH1D*	histoNEventsData0005 = (TH1D*)fileNeutralPionData0005->Get("NEvents");
	Int_t nEvtData0005 = histoNEventsData0005->GetBinContent(1);
	TH1D*	histoNTPCTracksData0005 = (TH1D*)fileNeutralPionData0005->Get("GoodESDTracks");
	histoNTPCTracksData0005->Rebin(4);
	Double_t meanNTPCTracksData0005 = histoNTPCTracksData0005->GetMean();
	
	TFile* fileNeutralPionWOAddSignalWOCorr0005 = new TFile("900297209450304221200003012002000/PbPb_2.76TeV/Pi0_MC_GammaConvV1WithoutCorrectionWOAddSig_900297209450304221200003012002000.root");
 	TH1D*	histoNEventsWOAddSig0005 = (TH1D*)fileNeutralPionWOAddSignalWOCorr0005->Get("NEvents");
	Int_t nEvtMCWOAddSig0005 = histoNEventsWOAddSig0005->GetBinContent(1);
	TH1D*	histoNTPCTracksWOAddSig0005 = (TH1D*)fileNeutralPionWOAddSignalWOCorr0005->Get("GoodESDTracks");
	histoNTPCTracksWOAddSig0005->Rebin(4);
	Double_t meanNTPCTracksWOAddSig0005 = histoNTPCTracksWOAddSig0005->GetMean();
	histoNTPCTracksWOAddSig0005->Scale(nEvtData0005/nEvtMCWOAddSig0005);
	
	TFile* fileNeutralPionWAddSignalWOCorr0005 = new TFile("900297209450304221200003012002000/PbPb_2.76TeV/Pi0_MC_GammaConvV1WithoutCorrectionAddSig_900297209450304221200003012002000.root");
	TH1D*	histoNEventsWAddSig0005 = (TH1D*)fileNeutralPionWAddSignalWOCorr0005->Get("NEvents");
	Int_t nEvtMCWAddSig0005 = histoNEventsWAddSig0005->GetBinContent(1);
	TH1D*	histoNTPCTracksWAddSig0005 = (TH1D*)fileNeutralPionWAddSignalWOCorr0005->Get("GoodESDTracks");
	histoNTPCTracksWAddSig0005->Rebin(4);
	Double_t meanNTPCTracksWAddSig0005 = histoNTPCTracksWAddSig0005->GetMean();
	histoNTPCTracksWAddSig0005->Scale(nEvtData0005/nEvtMCWAddSig0005);
	
	TFile* fileNeutralPionWAddSignalCorr0005 = new TFile("900297209450304221200003012002000/PbPb_2.76TeV/Pi0_MC_GammaConvV1CorrectionHistosAddSig_900297209450304221200003012002000.root");
	TH1D*	histoEffiWAddSig0005 = (TH1D*)fileNeutralPionWAddSignalCorr0005->Get("TrueMesonEffiPt");
	TH1D*	histoEffiWAddSig0005AddSig = (TH1D*)fileNeutralPionWAddSignalCorr0005->Get("TrueMesonEffiPtAddSig");
	TH1D*	histoGammaEffiWAddSig0005 = (TH1D*)fileNeutralPionWAddSignalCorr0005->Get("fMCGammaRecoEff");
	TH1D*	histoGammaPrimEffiWAddSig0005 = (TH1D*)fileNeutralPionWAddSignalCorr0005->Get("fMCGammaPrimaryRecoEff");
	TH1D*	histoGammaPurWAddSig0005 = (TH1D*)fileNeutralPionWAddSignalCorr0005->Get("fMCGammaPurity");
	TH1D*	histoGammaPrimPurWAddSig0005 = (TH1D*)fileNeutralPionWAddSignalCorr0005->Get("fMCGammaTruePurity");
	
	TFitResultPtr resultEffiWAddSig0005 = histoEffiWAddSig0005->Fit(fitTrueEffi,"SINRME+","",minPtMesonEffFit,maxPtMesonEffFit);
	TH1D* histoEffiFitWAddSig0005 = (TH1D*)histoEffiWAddSig0005->Clone("histoEffiFit");
	for (Int_t i = histoEffiWAddSig0005->GetXaxis()->FindBin(minPtMesonEffFit)+1; i < histoEffiWAddSig0005->GetXaxis()->FindBin(maxPtMesonEffFit)+offsetCorrectionHighPt; i++){
		Double_t ptStart = histoEffiWAddSig0005->GetXaxis()->GetBinLowEdge(i);
		Double_t ptEnd = histoEffiWAddSig0005->GetXaxis()->GetBinUpEdge(i);
		Double_t binWidth = ptEnd-ptStart;
		Double_t effi = fitTrueEffi->Integral(ptStart, ptEnd, resultEffiWAddSig0005->GetParams()) / binWidth;
		Double_t errorEffi = fitTrueEffi->IntegralError(ptStart, ptEnd, resultEffiWAddSig0005->GetParams(), resultEffiWAddSig0005->GetCovarianceMatrix().GetMatrixArray() ) / binWidth;
		histoEffiFitWAddSig0005->SetBinContent(i, effi);
		histoEffiFitWAddSig0005->SetBinError(i, errorEffi);
	}
	
	TFile* fileNeutralPionWOAddSignalCorr0005 = new TFile("900297209450304221200003012002000/PbPb_2.76TeV/Pi0_MC_GammaConvV1CorrectionHistosWOAddSig_900297209450304221200003012002000.root");
	TH1D*	histoEffiWOAddSig0005 = (TH1D*)fileNeutralPionWOAddSignalCorr0005->Get("TrueMesonEffiPt");
	TH1D*	histoGammaEffiWOAddSig0005 = (TH1D*)fileNeutralPionWOAddSignalCorr0005->Get("fMCGammaRecoEff");
	TH1D*	histoGammaPrimEffiWOAddSig0005 = (TH1D*)fileNeutralPionWOAddSignalCorr0005->Get("fMCGammaPrimaryRecoEff");
	TH1D*	histoGammaPurWOAddSig0005 = (TH1D*)fileNeutralPionWOAddSignalCorr0005->Get("fMCGammaPurity");
	TH1D*	histoGammaPrimPurWOAddSig0005 = (TH1D*)fileNeutralPionWOAddSignalCorr0005->Get("fMCGammaTruePurity");

	TFitResultPtr resultEffiWOAddSig0005 = histoEffiWOAddSig0005->Fit(fitTrueEffi,"SINRME+","",minPtMesonEffFit,maxPtMesonEffFit);
	TH1D* histoEffiFitWOAddSig0005 = (TH1D*)histoEffiWOAddSig0005->Clone("histoEffiFit");
	for (Int_t i = histoEffiWOAddSig0005->GetXaxis()->FindBin(minPtMesonEffFit)+1; i < histoEffiWOAddSig0005->GetXaxis()->FindBin(maxPtMesonEffFit)+offsetCorrectionHighPt; i++){
		Double_t ptStart = histoEffiWOAddSig0005->GetXaxis()->GetBinLowEdge(i);
		Double_t ptEnd = histoEffiWOAddSig0005->GetXaxis()->GetBinUpEdge(i);
		Double_t binWidth = ptEnd-ptStart;
		Double_t effi = fitTrueEffi->Integral(ptStart, ptEnd, resultEffiWOAddSig0005->GetParams()) / binWidth;
		Double_t errorEffi = fitTrueEffi->IntegralError(ptStart, ptEnd, resultEffiWOAddSig0005->GetParams(), resultEffiWOAddSig0005->GetCovarianceMatrix().GetMatrixArray() ) / binWidth;
		histoEffiFitWOAddSig0005->SetBinContent(i, effi);
		histoEffiFitWOAddSig0005->SetBinError(i, errorEffi);
	}

	TFile* fileNeutralPionCorr0005 = new TFile("900297209450304221200003012002000/PbPb_2.76TeV/Pi0_MC_GammaConvV1CorrectionHistos_900297209450304221200003012002000.root");
	TH1D*	histoGammaEffi0005 = (TH1D*)fileNeutralPionCorr0005->Get("fMCGammaRecoEff");
	TH1D*	histoGammaPrimEffi0005 = (TH1D*)fileNeutralPionCorr0005->Get("fMCGammaPrimaryRecoEff");
	TH1D*	histoGammaPur0005 = (TH1D*)fileNeutralPionCorr0005->Get("fMCGammaPurity");
	TH1D*	histoGammaPrimPur0005 = (TH1D*)fileNeutralPionCorr0005->Get("fMCGammaTruePurity");
	
	TFile* fileNeutralPionFinalCorr0005 = new TFile("900297209450304221200003012002000/PbPb_2.76TeV/Pi0_MC_GammaConvV1Correction_900297209450304221200003012002000.root");
	TH1D*	histoEffiFinal0005 = (TH1D*)fileNeutralPionFinalCorr0005->Get("TrueMesonEffiPt");
	TH1D*	histoEffiFinalFitted0005 = (TH1D*)fileNeutralPionFinalCorr0005->Get("histoTrueEffiPtFit");
	TH1D*	histoNTPCTracksFinal0005 = (TH1D*)fileNeutralPionFinalCorr0005->Get("GoodESDTracks");
	histoNTPCTracksFinal0005->Rebin(4);
	Double_t meanNTPCTracksFinal0005 = histoNTPCTracksFinal0005->GetMean();

	//************************************************************************************************************************
	//******************************************** 5 - 10% *******************************************************************
	//************************************************************************************************************************

	TFile* fileNeutralPionData0510 = new TFile("900297209450304221200003122002000/PbPb_2.76TeV/Pi0_data_GammaConvV1WithoutCorrection_900297209450304221200003122002000.root");
	TH1D*	histoNEventsData0510 = (TH1D*)fileNeutralPionData0510->Get("NEvents");
	Int_t nEvtData0510 = histoNEventsData0510->GetBinContent(1);
	TH1D*	histoNTPCTracksData0510 = (TH1D*)fileNeutralPionData0510->Get("GoodESDTracks");
	histoNTPCTracksData0510->Rebin(4);
	Double_t meanNTPCTracksData0510 = histoNTPCTracksData0510->GetMean();
	
	TFile* fileNeutralPionWOAddSignalWOCorr0510 = new TFile("900297209450304221200003122002000/PbPb_2.76TeV/Pi0_MC_GammaConvV1WithoutCorrectionWOAddSig_900297209450304221200003122002000.root");
 	TH1D*	histoNEventsWOAddSig0510 = (TH1D*)fileNeutralPionWOAddSignalWOCorr0510->Get("NEvents");
	Int_t nEvtMCWOAddSig0510 = histoNEventsWOAddSig0510->GetBinContent(1);
	TH1D*	histoNTPCTracksWOAddSig0510 = (TH1D*)fileNeutralPionWOAddSignalWOCorr0510->Get("GoodESDTracks");
	histoNTPCTracksWOAddSig0510->Rebin(4);
	Double_t meanNTPCTracksWOAddSig0510 = histoNTPCTracksWOAddSig0510->GetMean();
	histoNTPCTracksWOAddSig0510->Scale(nEvtData0510/nEvtMCWOAddSig0510);
	
	TFile* fileNeutralPionWAddSignalWOCorr0510 = new TFile("900297209450304221200003122002000/PbPb_2.76TeV/Pi0_MC_GammaConvV1WithoutCorrectionAddSig_900297209450304221200003122002000.root");
	TH1D*	histoNEventsWAddSig0510 = (TH1D*)fileNeutralPionWAddSignalWOCorr0510->Get("NEvents");
	Int_t nEvtMCWAddSig0510 = histoNEventsWAddSig0510->GetBinContent(1);
	TH1D*	histoNTPCTracksWAddSig0510 = (TH1D*)fileNeutralPionWAddSignalWOCorr0510->Get("GoodESDTracks");
	histoNTPCTracksWAddSig0510->Rebin(4);
	Double_t meanNTPCTracksWAddSig0510 = histoNTPCTracksWAddSig0510->GetMean();
	histoNTPCTracksWAddSig0510->Scale(nEvtData0510/nEvtMCWAddSig0510);
	
	
	TFile* fileNeutralPionWAddSignalCorr0510 = new TFile("900297209450304221200003122002000/PbPb_2.76TeV/Pi0_MC_GammaConvV1CorrectionHistosAddSig_900297209450304221200003122002000.root");
	TH1D*	histoEffiWAddSig0510 = (TH1D*)fileNeutralPionWAddSignalCorr0510->Get("TrueMesonEffiPt");
	TH1D*	histoGammaEffiWAddSig0510 = (TH1D*)fileNeutralPionWAddSignalCorr0510->Get("fMCGammaRecoEff");
	TH1D*	histoGammaPrimEffiWAddSig0510 = (TH1D*)fileNeutralPionWAddSignalCorr0510->Get("fMCGammaPrimaryRecoEff");
	TH1D*	histoGammaPurWAddSig0510 = (TH1D*)fileNeutralPionWAddSignalCorr0510->Get("fMCGammaPurity");
	TH1D*	histoGammaPrimPurWAddSig0510 = (TH1D*)fileNeutralPionWAddSignalCorr0510->Get("fMCGammaTruePurity");

	TFitResultPtr resultEffiWAddSig0510 = histoEffiWAddSig0510->Fit(fitTrueEffi,"SINRME+","",minPtMesonEffFit,maxPtMesonEffFit);
	TH1D* histoEffiFitWAddSig0510 = (TH1D*)histoEffiWAddSig0510->Clone("histoEffiFit");
	for (Int_t i = histoEffiWAddSig0510->GetXaxis()->FindBin(minPtMesonEffFit)+1; i < histoEffiWAddSig0510->GetXaxis()->FindBin(maxPtMesonEffFit)+offsetCorrectionHighPt; i++){
		Double_t ptStart = histoEffiWAddSig0510->GetXaxis()->GetBinLowEdge(i);
		Double_t ptEnd = histoEffiWAddSig0510->GetXaxis()->GetBinUpEdge(i);
		Double_t binWidth = ptEnd-ptStart;
		Double_t effi = fitTrueEffi->Integral(ptStart, ptEnd, resultEffiWAddSig0510->GetParams()) / binWidth;
		Double_t errorEffi = fitTrueEffi->IntegralError(ptStart, ptEnd, resultEffiWAddSig0510->GetParams(), resultEffiWAddSig0510->GetCovarianceMatrix().GetMatrixArray() ) / binWidth;
		histoEffiFitWAddSig0510->SetBinContent(i, effi);
		histoEffiFitWAddSig0510->SetBinError(i, errorEffi);
	}

	TFile* fileNeutralPionWOAddSignalCorr0510 = new TFile("900297209450304221200003122002000/PbPb_2.76TeV/Pi0_MC_GammaConvV1CorrectionHistosWOAddSig_900297209450304221200003122002000.root");
	TH1D*	histoEffiWOAddSig0510 = (TH1D*)fileNeutralPionWOAddSignalCorr0510->Get("TrueMesonEffiPt");
	TH1D*	histoGammaEffiWOAddSig0510 = (TH1D*)fileNeutralPionWOAddSignalCorr0510->Get("fMCGammaRecoEff");
	TH1D*	histoGammaPrimEffiWOAddSig0510 = (TH1D*)fileNeutralPionWOAddSignalCorr0510->Get("fMCGammaPrimaryRecoEff");
	TH1D*	histoGammaPurWOAddSig0510 = (TH1D*)fileNeutralPionWOAddSignalCorr0510->Get("fMCGammaPurity");
	TH1D*	histoGammaPrimPurWOAddSig0510 = (TH1D*)fileNeutralPionWOAddSignalCorr0510->Get("fMCGammaTruePurity");

	TFitResultPtr resultEffiWOAddSig0510 = histoEffiWOAddSig0510->Fit(fitTrueEffi,"SINRME+","",minPtMesonEffFit,maxPtMesonEffFit);
	TH1D* histoEffiFitWOAddSig0510 = (TH1D*)histoEffiWOAddSig0510->Clone("histoEffiFit");
	for (Int_t i = histoEffiWOAddSig0510->GetXaxis()->FindBin(minPtMesonEffFit)+1; i < histoEffiWOAddSig0510->GetXaxis()->FindBin(maxPtMesonEffFit)+offsetCorrectionHighPt; i++){
		Double_t ptStart = histoEffiWOAddSig0510->GetXaxis()->GetBinLowEdge(i);
		Double_t ptEnd = histoEffiWOAddSig0510->GetXaxis()->GetBinUpEdge(i);
		Double_t binWidth = ptEnd-ptStart;
		Double_t effi = fitTrueEffi->Integral(ptStart, ptEnd, resultEffiWOAddSig0510->GetParams()) / binWidth;
		Double_t errorEffi = fitTrueEffi->IntegralError(ptStart, ptEnd, resultEffiWOAddSig0510->GetParams(), resultEffiWOAddSig0510->GetCovarianceMatrix().GetMatrixArray() ) / binWidth;
		histoEffiFitWOAddSig0510->SetBinContent(i, effi);
		histoEffiFitWOAddSig0510->SetBinError(i, errorEffi);
	}

	TFile* fileNeutralPionCorr0510 = new TFile("900297209450304221200003122002000/PbPb_2.76TeV/Pi0_MC_GammaConvV1CorrectionHistos_900297209450304221200003122002000.root");
	TH1D*	histoGammaEffi0510 = (TH1D*)fileNeutralPionCorr0510->Get("fMCGammaRecoEff");
	TH1D*	histoGammaPrimEffi0510 = (TH1D*)fileNeutralPionCorr0510->Get("fMCGammaPrimaryRecoEff");
	TH1D*	histoGammaPur0510 = (TH1D*)fileNeutralPionCorr0510->Get("fMCGammaPurity");
	TH1D*	histoGammaPrimPur0510 = (TH1D*)fileNeutralPionCorr0510->Get("fMCGammaTruePurity");

	TFile* fileNeutralPionFinalCorr0510 = new TFile("900297209450304221200003122002000/PbPb_2.76TeV/Pi0_MC_GammaConvV1Correction_900297209450304221200003122002000.root");
	TH1D*	histoEffiFinal0510 = (TH1D*)fileNeutralPionFinalCorr0510->Get("TrueMesonEffiPt");
	TH1D*	histoEffiFinalFitted0510 = (TH1D*)fileNeutralPionFinalCorr0510->Get("histoTrueEffiPtFit");
	TH1D*	histoNTPCTracksFinal0510 = (TH1D*)fileNeutralPionFinalCorr0510->Get("GoodESDTracks");
	histoNTPCTracksFinal0510->Rebin(4);
	Double_t meanNTPCTracksFinal0510 = histoNTPCTracksFinal0510->GetMean();

	//************************************************************************************************************************
	//******************************************** 10 - 20% ******************************************************************
	//************************************************************************************************************************
	TFile* fileNeutralPionData1020 = new TFile("900297209450304221200001122002000/PbPb_2.76TeV/Pi0_data_GammaConvV1WithoutCorrection_900297209450304221200001122002000.root");
	TH1D*	histoNEventsData1020 = (TH1D*)fileNeutralPionData1020->Get("NEvents");
	Int_t nEvtData1020 = histoNEventsData1020->GetBinContent(1);
	TH1D*	histoNTPCTracksData1020 = (TH1D*)fileNeutralPionData1020->Get("GoodESDTracks");
	histoNTPCTracksData1020->Rebin(4);
	Double_t meanNTPCTracksData1020 = histoNTPCTracksData1020->GetMean();
//   	histoNTPCTracksData1020->Scale(1./nEvtData1020);
	
	TFile* fileNeutralPionWOAddSignalWOCorr1020 = new TFile("900297209450304221200001122002000/PbPb_2.76TeV/Pi0_MC_GammaConvV1WithoutCorrectionWOAddSig_900297209450304221200001122002000.root");
 	TH1D*	histoNEventsWOAddSig1020 = (TH1D*)fileNeutralPionWOAddSignalWOCorr1020->Get("NEvents");
	Int_t nEvtMCWOAddSig1020 = histoNEventsWOAddSig1020->GetBinContent(1);
	TH1D*	histoNTPCTracksWOAddSig1020 = (TH1D*)fileNeutralPionWOAddSignalWOCorr1020->Get("GoodESDTracks");
	histoNTPCTracksWOAddSig1020->Rebin(4);
	Double_t meanNTPCTracksWOAddSig1020 = histoNTPCTracksWOAddSig1020->GetMean();
	histoNTPCTracksWOAddSig1020->Scale(nEvtData1020/nEvtMCWOAddSig1020);
	
	TFile* fileNeutralPionWAddSignalWOCorr1020 = new TFile("900297209450304221200001122002000/PbPb_2.76TeV/Pi0_MC_GammaConvV1WithoutCorrectionAddSig_900297209450304221200001122002000.root");
	TH1D*	histoNEventsWAddSig1020 = (TH1D*)fileNeutralPionWAddSignalWOCorr1020->Get("NEvents");
	Int_t nEvtMCWAddSig1020 = histoNEventsWAddSig1020->GetBinContent(1);
	TH1D*	histoNTPCTracksWAddSig1020 = (TH1D*)fileNeutralPionWAddSignalWOCorr1020->Get("GoodESDTracks");
	histoNTPCTracksWAddSig1020->Rebin(4);
	Double_t meanNTPCTracksWAddSig1020 = histoNTPCTracksWAddSig1020->GetMean();
	histoNTPCTracksWAddSig1020->Scale(nEvtData1020/nEvtMCWAddSig1020);
		
	TFile* fileNeutralPionWAddSignalCorr1020 = new TFile("900297209450304221200001122002000/PbPb_2.76TeV/Pi0_MC_GammaConvV1CorrectionHistosAddSig_900297209450304221200001122002000.root");
	TH1D*	histoEffiWAddSig1020 = (TH1D*)fileNeutralPionWAddSignalCorr1020->Get("TrueMesonEffiPt");
	TH1D*	histoGammaEffiWAddSig1020 = (TH1D*)fileNeutralPionWAddSignalCorr1020->Get("fMCGammaRecoEff");
	TH1D*	histoGammaPrimEffiWAddSig1020 = (TH1D*)fileNeutralPionWAddSignalCorr1020->Get("fMCGammaPrimaryRecoEff");
	TH1D*	histoGammaPurWAddSig1020 = (TH1D*)fileNeutralPionWAddSignalCorr1020->Get("fMCGammaPurity");
	TH1D*	histoGammaPrimPurWAddSig1020 = (TH1D*)fileNeutralPionWAddSignalCorr1020->Get("fMCGammaTruePurity");

	TFitResultPtr resultEffiWAddSig1020 = histoEffiWAddSig1020->Fit(fitTrueEffi,"SINRME+","",minPtMesonEffFit,maxPtMesonEffFit);
	TH1D* histoEffiFitWAddSig1020 = (TH1D*)histoEffiWAddSig1020->Clone("histoEffiFit");
	for (Int_t i = histoEffiWAddSig1020->GetXaxis()->FindBin(minPtMesonEffFit)+1; i < histoEffiWAddSig1020->GetXaxis()->FindBin(maxPtMesonEffFit)+offsetCorrectionHighPt; i++){
		Double_t ptStart = histoEffiWAddSig1020->GetXaxis()->GetBinLowEdge(i);
		Double_t ptEnd = histoEffiWAddSig1020->GetXaxis()->GetBinUpEdge(i);
		Double_t binWidth = ptEnd-ptStart;
		Double_t effi = fitTrueEffi->Integral(ptStart, ptEnd, resultEffiWAddSig1020->GetParams()) / binWidth;
		Double_t errorEffi = fitTrueEffi->IntegralError(ptStart, ptEnd, resultEffiWAddSig1020->GetParams(), resultEffiWAddSig1020->GetCovarianceMatrix().GetMatrixArray() ) / binWidth;
		histoEffiFitWAddSig1020->SetBinContent(i, effi);
		histoEffiFitWAddSig1020->SetBinError(i, errorEffi);
	}

	TFile* fileNeutralPionWOAddSignalCorr1020 = new TFile("900297209450304221200001122002000/PbPb_2.76TeV/Pi0_MC_GammaConvV1CorrectionHistosWOAddSig_900297209450304221200001122002000.root");
	TH1D*	histoEffiWOAddSig1020 = (TH1D*)fileNeutralPionWOAddSignalCorr1020->Get("TrueMesonEffiPt");
	TH1D*	histoGammaEffiWOAddSig1020 = (TH1D*)fileNeutralPionWOAddSignalCorr1020->Get("fMCGammaRecoEff");
	TH1D*	histoGammaPrimEffiWOAddSig1020 = (TH1D*)fileNeutralPionWOAddSignalCorr1020->Get("fMCGammaPrimaryRecoEff");
	TH1D*	histoGammaPurWOAddSig1020 = (TH1D*)fileNeutralPionWOAddSignalCorr1020->Get("fMCGammaPurity");
	TH1D*	histoGammaPrimPurWOAddSig1020 = (TH1D*)fileNeutralPionWOAddSignalCorr1020->Get("fMCGammaTruePurity");

	TFitResultPtr resultEffiWOAddSig1020 = histoEffiWOAddSig1020->Fit(fitTrueEffi,"SINRME+","",minPtMesonEffFit,maxPtMesonEffFit);
	TH1D* histoEffiFitWOAddSig1020 = (TH1D*)histoEffiWOAddSig1020->Clone("histoEffiFit");
	for (Int_t i = histoEffiWOAddSig1020->GetXaxis()->FindBin(minPtMesonEffFit)+1; i < histoEffiWOAddSig1020->GetXaxis()->FindBin(maxPtMesonEffFit)+offsetCorrectionHighPt; i++){
		Double_t ptStart = histoEffiWOAddSig1020->GetXaxis()->GetBinLowEdge(i);
		Double_t ptEnd = histoEffiWOAddSig1020->GetXaxis()->GetBinUpEdge(i);
		Double_t binWidth = ptEnd-ptStart;
		Double_t effi = fitTrueEffi->Integral(ptStart, ptEnd, resultEffiWOAddSig1020->GetParams()) / binWidth;
		Double_t errorEffi = fitTrueEffi->IntegralError(ptStart, ptEnd, resultEffiWOAddSig1020->GetParams(), resultEffiWOAddSig1020->GetCovarianceMatrix().GetMatrixArray() ) / binWidth;
		histoEffiFitWOAddSig1020->SetBinContent(i, effi);
		histoEffiFitWOAddSig1020->SetBinError(i, errorEffi);
	}

	TFile* fileNeutralPionCorr1020 = new TFile("900297209450304221200001122002000/PbPb_2.76TeV/Pi0_MC_GammaConvV1CorrectionHistos_900297209450304221200001122002000.root");
	TH1D*	histoGammaEffi1020 = (TH1D*)fileNeutralPionCorr1020->Get("fMCGammaRecoEff");
	TH1D*	histoGammaPrimEffi1020 = (TH1D*)fileNeutralPionCorr1020->Get("fMCGammaPrimaryRecoEff");
	TH1D*	histoGammaPur1020 = (TH1D*)fileNeutralPionCorr1020->Get("fMCGammaPurity");
	TH1D*	histoGammaPrimPur1020 = (TH1D*)fileNeutralPionCorr1020->Get("fMCGammaTruePurity");

	TFile* fileNeutralPionFinalCorr1020 = new TFile("900297209450304221200001122002000/PbPb_2.76TeV/Pi0_MC_GammaConvV1Correction_900297209450304221200001122002000.root");
	TH1D*	histoEffiFinal1020 = (TH1D*)fileNeutralPionFinalCorr1020->Get("TrueMesonEffiPt");
	TH1D*	histoEffiFinalFitted1020 = (TH1D*)fileNeutralPionFinalCorr1020->Get("histoTrueEffiPtFit");
	TH1D*	histoNTPCTracksFinal1020 = (TH1D*)fileNeutralPionFinalCorr1020->Get("GoodESDTracks");
	histoNTPCTracksFinal1020->Rebin(4);
	Double_t meanNTPCTracksFinal1020 = histoNTPCTracksFinal1020->GetMean();

	//************************************************************************************************************************
	//******************************************** 20 - 40% ******************************************************************
	//************************************************************************************************************************
	TFile* fileNeutralPionData2040 = new TFile("900297209450304221200001242002000/PbPb_2.76TeV/Pi0_data_GammaConvV1WithoutCorrection_900297209450304221200001242002000.root");
	TH1D*	histoNEventsData2040 = (TH1D*)fileNeutralPionData2040->Get("NEvents");
	Int_t nEvtData2040 = histoNEventsData2040->GetBinContent(1);
	TH1D*	histoNTPCTracksData2040 = (TH1D*)fileNeutralPionData2040->Get("GoodESDTracks");
	histoNTPCTracksData2040->Rebin(4);
	Double_t meanNTPCTracksData2040 = histoNTPCTracksData2040->GetMean();
//   	histoNTPCTracksData2040->Scale(1./nEvtData2040);
	
	TFile* fileNeutralPionWOAddSignalWOCorr2040 = new TFile("900297209450304221200001242002000/PbPb_2.76TeV/Pi0_MC_GammaConvV1WithoutCorrectionWOAddSig_900297209450304221200001242002000.root");
 	TH1D*	histoNEventsWOAddSig2040 = (TH1D*)fileNeutralPionWOAddSignalWOCorr2040->Get("NEvents");
	Int_t nEvtMCWOAddSig2040 = histoNEventsWOAddSig2040->GetBinContent(1);
	TH1D*	histoNTPCTracksWOAddSig2040 = (TH1D*)fileNeutralPionWOAddSignalWOCorr2040->Get("GoodESDTracks");
	histoNTPCTracksWOAddSig2040->Rebin(4);
	Double_t meanNTPCTracksWOAddSig2040 = histoNTPCTracksWOAddSig2040->GetMean();
	histoNTPCTracksWOAddSig2040->Scale(nEvtData2040/nEvtMCWOAddSig2040);
	
	TFile* fileNeutralPionWAddSignalWOCorr2040 = new TFile("900297209450304221200001242002000/PbPb_2.76TeV/Pi0_MC_GammaConvV1WithoutCorrectionAddSig_900297209450304221200001242002000.root");
	TH1D*	histoNEventsWAddSig2040 = (TH1D*)fileNeutralPionWAddSignalWOCorr2040->Get("NEvents");
	Int_t nEvtMCWAddSig2040 = histoNEventsWAddSig2040->GetBinContent(1);
	TH1D*	histoNTPCTracksWAddSig2040 = (TH1D*)fileNeutralPionWAddSignalWOCorr2040->Get("GoodESDTracks");
	histoNTPCTracksWAddSig2040->Rebin(4);
	Double_t meanNTPCTracksWAddSig2040 = histoNTPCTracksWAddSig2040->GetMean();
	histoNTPCTracksWAddSig2040->Scale(nEvtData2040/nEvtMCWAddSig2040);
		
	TFile* fileNeutralPionWAddSignalCorr2040 = new TFile("900297209450304221200001242002000/PbPb_2.76TeV/Pi0_MC_GammaConvV1CorrectionHistosAddSig_900297209450304221200001242002000.root");
	TH1D*	histoEffiWAddSig2040 = (TH1D*)fileNeutralPionWAddSignalCorr2040->Get("TrueMesonEffiPt");
	TH1D*	histoGammaEffiWAddSig2040 = (TH1D*)fileNeutralPionWAddSignalCorr2040->Get("fMCGammaRecoEff");
	TH1D*	histoGammaPrimEffiWAddSig2040 = (TH1D*)fileNeutralPionWAddSignalCorr2040->Get("fMCGammaPrimaryRecoEff");
	TH1D*	histoGammaPurWAddSig2040 = (TH1D*)fileNeutralPionWAddSignalCorr2040->Get("fMCGammaPurity");
	TH1D*	histoGammaPrimPurWAddSig2040 = (TH1D*)fileNeutralPionWAddSignalCorr2040->Get("fMCGammaTruePurity");

	TFitResultPtr resultEffiWAddSig2040 = histoEffiWAddSig2040->Fit(fitTrueEffi,"SINRME+","",minPtMesonEffFit,maxPtMesonEffFit);
	TH1D* histoEffiFitWAddSig2040 = (TH1D*)histoEffiWAddSig2040->Clone("histoEffiFit");
	for (Int_t i = histoEffiWAddSig2040->GetXaxis()->FindBin(minPtMesonEffFit)+1; i < histoEffiWAddSig2040->GetXaxis()->FindBin(maxPtMesonEffFit)+offsetCorrectionHighPt; i++){
		Double_t ptStart = histoEffiWAddSig2040->GetXaxis()->GetBinLowEdge(i);
		Double_t ptEnd = histoEffiWAddSig2040->GetXaxis()->GetBinUpEdge(i);
		Double_t binWidth = ptEnd-ptStart;
		Double_t effi = fitTrueEffi->Integral(ptStart, ptEnd, resultEffiWAddSig2040->GetParams()) / binWidth;
		Double_t errorEffi = fitTrueEffi->IntegralError(ptStart, ptEnd, resultEffiWAddSig2040->GetParams(), resultEffiWAddSig2040->GetCovarianceMatrix().GetMatrixArray() ) / binWidth;
		histoEffiFitWAddSig2040->SetBinContent(i, effi);
		histoEffiFitWAddSig2040->SetBinError(i, errorEffi);
	}

	TFile* fileNeutralPionWOAddSignalCorr2040 = new TFile("900297209450304221200001242002000/PbPb_2.76TeV/Pi0_MC_GammaConvV1CorrectionHistosWOAddSig_900297209450304221200001242002000.root");
	TH1D*	histoEffiWOAddSig2040 = (TH1D*)fileNeutralPionWOAddSignalCorr2040->Get("TrueMesonEffiPt");
	TH1D*	histoGammaEffiWOAddSig2040 = (TH1D*)fileNeutralPionWOAddSignalCorr2040->Get("fMCGammaRecoEff");
	TH1D*	histoGammaPrimEffiWOAddSig2040 = (TH1D*)fileNeutralPionWOAddSignalCorr2040->Get("fMCGammaPrimaryRecoEff");
	TH1D*	histoGammaPurWOAddSig2040 = (TH1D*)fileNeutralPionWOAddSignalCorr2040->Get("fMCGammaPurity");
	TH1D*	histoGammaPrimPurWOAddSig2040 = (TH1D*)fileNeutralPionWOAddSignalCorr2040->Get("fMCGammaTruePurity");

	TFitResultPtr resultEffiWOAddSig2040 = histoEffiWOAddSig2040->Fit(fitTrueEffi,"SINRME+","",minPtMesonEffFit,maxPtMesonEffFit);
	TH1D* histoEffiFitWOAddSig2040 = (TH1D*)histoEffiWOAddSig2040->Clone("histoEffiFit");
	for (Int_t i = histoEffiWOAddSig2040->GetXaxis()->FindBin(minPtMesonEffFit)+1; i < histoEffiWOAddSig2040->GetXaxis()->FindBin(maxPtMesonEffFit)+offsetCorrectionHighPt; i++){
		Double_t ptStart = histoEffiWOAddSig2040->GetXaxis()->GetBinLowEdge(i);
		Double_t ptEnd = histoEffiWOAddSig2040->GetXaxis()->GetBinUpEdge(i);
		Double_t binWidth = ptEnd-ptStart;
		Double_t effi = fitTrueEffi->Integral(ptStart, ptEnd, resultEffiWOAddSig2040->GetParams()) / binWidth;
		Double_t errorEffi = fitTrueEffi->IntegralError(ptStart, ptEnd, resultEffiWOAddSig2040->GetParams(), resultEffiWOAddSig2040->GetCovarianceMatrix().GetMatrixArray() ) / binWidth;
		histoEffiFitWOAddSig2040->SetBinContent(i, effi);
		histoEffiFitWOAddSig2040->SetBinError(i, errorEffi);
	}

	TFile* fileNeutralPionCorr2040 = new TFile("900297209450304221200001242002000/PbPb_2.76TeV/Pi0_MC_GammaConvV1CorrectionHistos_900297209450304221200001242002000.root");
	TH1D*	histoGammaEffi2040 = (TH1D*)fileNeutralPionCorr2040->Get("fMCGammaRecoEff");
	TH1D*	histoGammaPrimEffi2040 = (TH1D*)fileNeutralPionCorr2040->Get("fMCGammaPrimaryRecoEff");
	TH1D*	histoGammaPur2040 = (TH1D*)fileNeutralPionCorr2040->Get("fMCGammaPurity");
	TH1D*	histoGammaPrimPur2040 = (TH1D*)fileNeutralPionCorr2040->Get("fMCGammaTruePurity");
	
	TFile* fileNeutralPionFinalCorr2040 = new TFile("900297209450304221200001242002000/PbPb_2.76TeV/Pi0_MC_GammaConvV1Correction_900297209450304221200001242002000.root");
	TH1D*	histoEffiFinal2040 = (TH1D*)fileNeutralPionFinalCorr2040->Get("TrueMesonEffiPt");
	TH1D*	histoEffiFinalFitted2040 = (TH1D*)fileNeutralPionFinalCorr2040->Get("histoTrueEffiPtFit");
	TH1D*	histoNTPCTracksFinal2040 = (TH1D*)fileNeutralPionFinalCorr2040->Get("GoodESDTracks");
	histoNTPCTracksFinal2040->Rebin(4);
	Double_t meanNTPCTracksFinal2040 = histoNTPCTracksFinal2040->GetMean();
	
	//************************************************************************************************************************
	//******************************************** 40 - 60% ******************************************************************
	//************************************************************************************************************************	
	TFile* fileNeutralPionData4060 = new TFile("900297209450306221200001462002000/PbPb_2.76TeV/Pi0_data_GammaConvV1WithoutCorrection_900297209450306221200001462002000.root");
	TH1D*	histoNEventsData4060 = (TH1D*)fileNeutralPionData4060->Get("NEvents");
	Int_t nEvtData4060 = histoNEventsData4060->GetBinContent(1);
	TH1D*	histoNTPCTracksData4060 = (TH1D*)fileNeutralPionData4060->Get("GoodESDTracks");
	histoNTPCTracksData4060->Rebin(4);
	Double_t meanNTPCTracksData4060 = histoNTPCTracksData4060->GetMean();
//   	histoNTPCTracksData4060->Scale(1./nEvtData4060);
	
	TFile* fileNeutralPionWOAddSignalWOCorr4060 = new TFile("900297209450306221200001462002000/PbPb_2.76TeV/Pi0_MC_GammaConvV1WithoutCorrectionWOAddSig_900297209450306221200001462002000.root");
 	TH1D*	histoNEventsWOAddSig4060 = (TH1D*)fileNeutralPionWOAddSignalWOCorr4060->Get("NEvents");
	Int_t nEvtMCWOAddSig4060 = histoNEventsWOAddSig4060->GetBinContent(1);
	TH1D*	histoNTPCTracksWOAddSig4060 = (TH1D*)fileNeutralPionWOAddSignalWOCorr4060->Get("GoodESDTracks");
	histoNTPCTracksWOAddSig4060->Rebin(4);
	Double_t meanNTPCTracksWOAddSig4060 = histoNTPCTracksWOAddSig4060->GetMean();
	histoNTPCTracksWOAddSig4060->Scale(nEvtData4060/nEvtMCWOAddSig4060);
	
	TFile* fileNeutralPionWAddSignalWOCorr4060 = new TFile("900297209450306221200001462002000/PbPb_2.76TeV/Pi0_MC_GammaConvV1WithoutCorrectionAddSig_900297209450306221200001462002000.root");
	TH1D*	histoNEventsWAddSig4060 = (TH1D*)fileNeutralPionWAddSignalWOCorr4060->Get("NEvents");
	Int_t nEvtMCWAddSig4060 = histoNEventsWAddSig4060->GetBinContent(1);
	TH1D*	histoNTPCTracksWAddSig4060 = (TH1D*)fileNeutralPionWAddSignalWOCorr4060->Get("GoodESDTracks");
	histoNTPCTracksWAddSig4060->Rebin(4);
	Double_t meanNTPCTracksWAddSig4060 = histoNTPCTracksWAddSig4060->GetMean();
	histoNTPCTracksWAddSig4060->Scale(nEvtData4060/nEvtMCWAddSig4060);
		
	TFile* fileNeutralPionWAddSignalCorr4060 = new TFile("900297209450306221200001462002000/PbPb_2.76TeV/Pi0_MC_GammaConvV1CorrectionHistosAddSig_900297209450306221200001462002000.root");
	TH1D*	histoEffiWAddSig4060 = (TH1D*)fileNeutralPionWAddSignalCorr4060->Get("TrueMesonEffiPt");
	TH1D*	histoGammaEffiWAddSig4060 = (TH1D*)fileNeutralPionWAddSignalCorr4060->Get("fMCGammaRecoEff");
	TH1D*	histoGammaPrimEffiWAddSig4060 = (TH1D*)fileNeutralPionWAddSignalCorr4060->Get("fMCGammaPrimaryRecoEff");
	TH1D*	histoGammaPurWAddSig4060 = (TH1D*)fileNeutralPionWAddSignalCorr4060->Get("fMCGammaPurity");
	TH1D*	histoGammaPrimPurWAddSig4060 = (TH1D*)fileNeutralPionWAddSignalCorr4060->Get("fMCGammaTruePurity");
	TFitResultPtr resultEffiWAddSig4060 = histoEffiWAddSig4060->Fit(fitTrueEffi,"SINRME+","",minPtMesonEffFit,maxPtMesonEffFit);
	TH1D* histoEffiFitWAddSig4060 = (TH1D*)histoEffiWAddSig4060->Clone("histoEffiFit");
	for (Int_t i = histoEffiWAddSig4060->GetXaxis()->FindBin(minPtMesonEffFit)+1; i < histoEffiWAddSig4060->GetXaxis()->FindBin(maxPtMesonEffFit)+offsetCorrectionHighPt; i++){
		Double_t ptStart = histoEffiWAddSig4060->GetXaxis()->GetBinLowEdge(i);
		Double_t ptEnd = histoEffiWAddSig4060->GetXaxis()->GetBinUpEdge(i);
		Double_t binWidth = ptEnd-ptStart;
		Double_t effi = fitTrueEffi->Integral(ptStart, ptEnd, resultEffiWAddSig4060->GetParams()) / binWidth;
		Double_t errorEffi = fitTrueEffi->IntegralError(ptStart, ptEnd, resultEffiWAddSig4060->GetParams(), resultEffiWAddSig4060->GetCovarianceMatrix().GetMatrixArray() ) / binWidth;
		histoEffiFitWAddSig4060->SetBinContent(i, effi);
		histoEffiFitWAddSig4060->SetBinError(i, errorEffi);
	}

	TFile* fileNeutralPionWOAddSignalCorr4060 = new TFile("900297209450306221200001462002000/PbPb_2.76TeV/Pi0_MC_GammaConvV1CorrectionHistosWOAddSig_900297209450306221200001462002000.root");
	TH1D*	histoEffiWOAddSig4060 = (TH1D*)fileNeutralPionWOAddSignalCorr4060->Get("TrueMesonEffiPt");
	TH1D*	histoGammaEffiWOAddSig4060 = (TH1D*)fileNeutralPionWOAddSignalCorr4060->Get("fMCGammaRecoEff");
	TH1D*	histoGammaPrimEffiWOAddSig4060 = (TH1D*)fileNeutralPionWOAddSignalCorr4060->Get("fMCGammaPrimaryRecoEff");
	TH1D*	histoGammaPurWOAddSig4060 = (TH1D*)fileNeutralPionWOAddSignalCorr4060->Get("fMCGammaPurity");
	TH1D*	histoGammaPrimPurWOAddSig4060 = (TH1D*)fileNeutralPionWOAddSignalCorr4060->Get("fMCGammaTruePurity");
	TFitResultPtr resultEffiWOAddSig4060 = histoEffiWOAddSig4060->Fit(fitTrueEffi,"SINRME+","",minPtMesonEffFit,maxPtMesonEffFit);
	TH1D* histoEffiFitWOAddSig4060 = (TH1D*)histoEffiWOAddSig4060->Clone("histoEffiFit");
	for (Int_t i = histoEffiWOAddSig4060->GetXaxis()->FindBin(minPtMesonEffFit)+1; i < histoEffiWOAddSig4060->GetXaxis()->FindBin(maxPtMesonEffFit)+offsetCorrectionHighPt; i++){
		Double_t ptStart = histoEffiWOAddSig4060->GetXaxis()->GetBinLowEdge(i);
		Double_t ptEnd = histoEffiWOAddSig4060->GetXaxis()->GetBinUpEdge(i);
		Double_t binWidth = ptEnd-ptStart;
		Double_t effi = fitTrueEffi->Integral(ptStart, ptEnd, resultEffiWOAddSig4060->GetParams()) / binWidth;
		Double_t errorEffi = fitTrueEffi->IntegralError(ptStart, ptEnd, resultEffiWOAddSig4060->GetParams(), resultEffiWOAddSig4060->GetCovarianceMatrix().GetMatrixArray() ) / binWidth;
		histoEffiFitWOAddSig4060->SetBinContent(i, effi);
		histoEffiFitWOAddSig4060->SetBinError(i, errorEffi);
	}

	TFile* fileNeutralPionCorr4060 = new TFile("900297209450306221200001462002000/PbPb_2.76TeV/Pi0_MC_GammaConvV1CorrectionHistos_900297209450306221200001462002000.root");
	TH1D*	histoGammaEffi4060 = (TH1D*)fileNeutralPionCorr4060->Get("fMCGammaRecoEff");
	TH1D*	histoGammaPrimEffi4060 = (TH1D*)fileNeutralPionCorr4060->Get("fMCGammaPrimaryRecoEff");
	TH1D*	histoGammaPur4060 = (TH1D*)fileNeutralPionCorr4060->Get("fMCGammaPurity");
	TH1D*	histoGammaPrimPur4060 = (TH1D*)fileNeutralPionCorr4060->Get("fMCGammaTruePurity");
	
	TFile* fileNeutralPionFinalCorr4060 = new TFile("900297209450306221200001462002000/PbPb_2.76TeV/Pi0_MC_GammaConvV1Correction_900297209450306221200001462002000.root");
	TH1D*	histoEffiFinal4060 = (TH1D*)fileNeutralPionFinalCorr4060->Get("TrueMesonEffiPt");
	TH1D*	histoEffiFinalFitted4060 = (TH1D*)fileNeutralPionFinalCorr4060->Get("histoTrueEffiPtFit");
	TH1D*	histoNTPCTracksFinal4060 = (TH1D*)fileNeutralPionFinalCorr4060->Get("GoodESDTracks");
	histoNTPCTracksFinal4060->Rebin(4);
	Double_t meanNTPCTracksFinal4060 = histoNTPCTracksFinal4060->GetMean();
	
	//************************************************************************************************************************
	//******************************************** 60 - 80% ******************************************************************
	//************************************************************************************************************************	
	TFile* fileNeutralPionData6080 = new TFile("900297209450306221200001682002000/PbPb_2.76TeV/Pi0_data_GammaConvV1WithoutCorrection_900297209450306221200001682002000.root");
	TH1D*	histoNEventsData6080 = (TH1D*)fileNeutralPionData6080->Get("NEvents");
	Int_t nEvtData6080 = histoNEventsData6080->GetBinContent(1);
	TH1D*	histoNTPCTracksData6080 = (TH1D*)fileNeutralPionData6080->Get("GoodESDTracks");
	histoNTPCTracksData6080->Rebin(4);
	Double_t meanNTPCTracksData6080 = histoNTPCTracksData6080->GetMean();
//   	histoNTPCTracksData6080->Scale(1./nEvtData6080);
	
	TFile* fileNeutralPionWOAddSignalWOCorr6080 = new TFile("900297209450306221200001682002000/PbPb_2.76TeV/Pi0_MC_GammaConvV1WithoutCorrectionWOAddSig_900297209450306221200001682002000.root");
 	TH1D*	histoNEventsWOAddSig6080 = (TH1D*)fileNeutralPionWOAddSignalWOCorr6080->Get("NEvents");
	Int_t nEvtMCWOAddSig6080 = histoNEventsWOAddSig6080->GetBinContent(1);
	TH1D*	histoNTPCTracksWOAddSig6080 = (TH1D*)fileNeutralPionWOAddSignalWOCorr6080->Get("GoodESDTracks");
	histoNTPCTracksWOAddSig6080->Rebin(4);
	Double_t meanNTPCTracksWOAddSig6080 = histoNTPCTracksWOAddSig6080->GetMean();
	histoNTPCTracksWOAddSig6080->Scale(nEvtData6080/nEvtMCWOAddSig6080);
	
	TFile* fileNeutralPionWAddSignalWOCorr6080 = new TFile("900297209450306221200001682002000/PbPb_2.76TeV/Pi0_MC_GammaConvV1WithoutCorrectionAddSig_900297209450306221200001682002000.root");
	TH1D*	histoNEventsWAddSig6080 = (TH1D*)fileNeutralPionWAddSignalWOCorr6080->Get("NEvents");
	Int_t nEvtMCWAddSig6080 = histoNEventsWAddSig6080->GetBinContent(1);
	TH1D*	histoNTPCTracksWAddSig6080 = (TH1D*)fileNeutralPionWAddSignalWOCorr6080->Get("GoodESDTracks");
	histoNTPCTracksWAddSig6080->Rebin(4);
	Double_t meanNTPCTracksWAddSig6080 = histoNTPCTracksWAddSig6080->GetMean();
	histoNTPCTracksWAddSig6080->Scale(nEvtData6080/nEvtMCWAddSig6080);
		
	TFile* fileNeutralPionWAddSignalCorr6080 = new TFile("900297209450306221200001682002000/PbPb_2.76TeV/Pi0_MC_GammaConvV1CorrectionHistosAddSig_900297209450306221200001682002000.root");
	TH1D*	histoEffiWAddSig6080 = (TH1D*)fileNeutralPionWAddSignalCorr6080->Get("TrueMesonEffiPt");
	TH1D*	histoGammaEffiWAddSig6080 = (TH1D*)fileNeutralPionWAddSignalCorr6080->Get("fMCGammaRecoEff");
	TH1D*	histoGammaPrimEffiWAddSig6080 = (TH1D*)fileNeutralPionWAddSignalCorr6080->Get("fMCGammaPrimaryRecoEff");
	TH1D*	histoGammaPurWAddSig6080 = (TH1D*)fileNeutralPionWAddSignalCorr6080->Get("fMCGammaPurity");
	TH1D*	histoGammaPrimPurWAddSig6080 = (TH1D*)fileNeutralPionWAddSignalCorr6080->Get("fMCGammaTruePurity");
	TFitResultPtr resultEffiWAddSig6080 = histoEffiWAddSig6080->Fit(fitTrueEffi,"SINRME+","",minPtMesonEffFit,maxPtMesonEffFit);
	TH1D* histoEffiFitWAddSig6080 = (TH1D*)histoEffiWAddSig6080->Clone("histoEffiFit");
	for (Int_t i = histoEffiWAddSig6080->GetXaxis()->FindBin(minPtMesonEffFit)+1; i < histoEffiWAddSig6080->GetXaxis()->FindBin(maxPtMesonEffFit)+offsetCorrectionHighPt; i++){
		Double_t ptStart = histoEffiWAddSig6080->GetXaxis()->GetBinLowEdge(i);
		Double_t ptEnd = histoEffiWAddSig6080->GetXaxis()->GetBinUpEdge(i);
		Double_t binWidth = ptEnd-ptStart;
		Double_t effi = fitTrueEffi->Integral(ptStart, ptEnd, resultEffiWAddSig6080->GetParams()) / binWidth;
		Double_t errorEffi = fitTrueEffi->IntegralError(ptStart, ptEnd, resultEffiWAddSig6080->GetParams(), resultEffiWAddSig6080->GetCovarianceMatrix().GetMatrixArray() ) / binWidth;
		histoEffiFitWAddSig6080->SetBinContent(i, effi);
		histoEffiFitWAddSig6080->SetBinError(i, errorEffi);
	}

	TFile* fileNeutralPionWOAddSignalCorr6080 = new TFile("900297209450306221200001682002000/PbPb_2.76TeV/Pi0_MC_GammaConvV1CorrectionHistosWOAddSig_900297209450306221200001682002000.root");
	TH1D*	histoEffiWOAddSig6080 = (TH1D*)fileNeutralPionWOAddSignalCorr6080->Get("TrueMesonEffiPt");
	TH1D*	histoGammaEffiWOAddSig6080 = (TH1D*)fileNeutralPionWOAddSignalCorr6080->Get("fMCGammaRecoEff");
	TH1D*	histoGammaPrimEffiWOAddSig6080 = (TH1D*)fileNeutralPionWOAddSignalCorr6080->Get("fMCGammaPrimaryRecoEff");
	TH1D*	histoGammaPurWOAddSig6080 = (TH1D*)fileNeutralPionWOAddSignalCorr6080->Get("fMCGammaPurity");
	TH1D*	histoGammaPrimPurWOAddSig6080 = (TH1D*)fileNeutralPionWOAddSignalCorr6080->Get("fMCGammaTruePurity");
	TFitResultPtr resultEffiWOAddSig6080 = histoEffiWOAddSig6080->Fit(fitTrueEffi,"SINRME+","",minPtMesonEffFit,maxPtMesonEffFit);
	TH1D* histoEffiFitWOAddSig6080 = (TH1D*)histoEffiWOAddSig6080->Clone("histoEffiFit");
	for (Int_t i = histoEffiWOAddSig6080->GetXaxis()->FindBin(minPtMesonEffFit)+1; i < histoEffiWOAddSig6080->GetXaxis()->FindBin(maxPtMesonEffFit)+offsetCorrectionHighPt; i++){
		Double_t ptStart = histoEffiWOAddSig6080->GetXaxis()->GetBinLowEdge(i);
		Double_t ptEnd = histoEffiWOAddSig6080->GetXaxis()->GetBinUpEdge(i);
		Double_t binWidth = ptEnd-ptStart;
		Double_t effi = fitTrueEffi->Integral(ptStart, ptEnd, resultEffiWOAddSig6080->GetParams()) / binWidth;
		Double_t errorEffi = fitTrueEffi->IntegralError(ptStart, ptEnd, resultEffiWOAddSig6080->GetParams(), resultEffiWOAddSig6080->GetCovarianceMatrix().GetMatrixArray() ) / binWidth;
		histoEffiFitWOAddSig6080->SetBinContent(i, effi);
		histoEffiFitWOAddSig6080->SetBinError(i, errorEffi);
	}

	TFile* fileNeutralPionCorr6080 = new TFile("900297209450306221200001682002000/PbPb_2.76TeV/Pi0_MC_GammaConvV1CorrectionHistos_900297209450306221200001682002000.root");
	TH1D*	histoGammaEffi6080 = (TH1D*)fileNeutralPionCorr6080->Get("fMCGammaRecoEff");
	TH1D*	histoGammaPrimEffi6080 = (TH1D*)fileNeutralPionCorr6080->Get("fMCGammaPrimaryRecoEff");
	TH1D*	histoGammaPur6080 = (TH1D*)fileNeutralPionCorr6080->Get("fMCGammaPurity");
	TH1D*	histoGammaPrimPur6080 = (TH1D*)fileNeutralPionCorr6080->Get("fMCGammaTruePurity");

	TFile* fileNeutralPionFinalCorr6080 = new TFile("900297209450306221200001682002000/PbPb_2.76TeV/Pi0_MC_GammaConvV1Correction_900297209450306221200001682002000.root");
	TH1D*	histoEffiFinal6080 = (TH1D*)fileNeutralPionFinalCorr6080->Get("TrueMesonEffiPt");
	TH1D*	histoEffiFinalFitted6080 = (TH1D*)fileNeutralPionFinalCorr6080->Get("histoTrueEffiPtFit");
	TH1D*	histoNTPCTracksFinal6080 = (TH1D*)fileNeutralPionFinalCorr6080->Get("GoodESDTracks");
	histoNTPCTracksFinal6080->Rebin(4);
	Double_t meanNTPCTracksFinal6080 = histoNTPCTracksFinal6080->GetMean();
	
	cout << "Centrality \t # Events data \t # Events MC wo add sig \t # Events MC w add sig" << endl;
	cout << "0-5% \t"  <<nEvtData0005 << "\t" <<nEvtMCWOAddSig0005 << "\t" <<nEvtMCWAddSig0005 << "\t" <<endl;
	cout << "5-10% \t" <<nEvtData0510 << "\t" <<nEvtMCWOAddSig0510 << "\t" <<nEvtMCWAddSig0510 << "\t" <<endl;
	cout << "10-20% \t"  <<nEvtData1020 << "\t" <<nEvtMCWOAddSig1020 << "\t" <<nEvtMCWAddSig1020 << "\t" <<endl;
	cout << "20-40% \t"  <<nEvtData2040 << "\t" <<nEvtMCWOAddSig2040 << "\t" <<nEvtMCWAddSig2040 << "\t" <<endl;
	cout << "40-60% \t"  <<nEvtData4060 << "\t" <<nEvtMCWOAddSig4060 << "\t" <<nEvtMCWAddSig4060 << "\t" <<endl;
	cout << "60-80% \t"  <<nEvtData6080 << "\t" <<nEvtMCWOAddSig6080 << "\t" <<nEvtMCWAddSig6080 << "\t" <<endl<<endl;
	
	cout << "Centrality \t mean Mult data \t mean Mult MC wo add sig \t mean Mult MC w add sig \t mean Mult MC merged" << endl;
	cout << "0-5% \t" << meanNTPCTracksData0005 << "+-" << histoNTPCTracksData0005->GetRMS() << "\t" << meanNTPCTracksWOAddSig0005 << "+-" << histoNTPCTracksWOAddSig0005->GetRMS() <<"\t" << meanNTPCTracksWAddSig0005 << "+-" << histoNTPCTracksWAddSig0005->GetRMS() << "\t" << meanNTPCTracksFinal0005 << "+-"<< histoNTPCTracksFinal0005->GetRMS() << endl;
	cout << "5-10% \t" << meanNTPCTracksData0510 << "+-" << histoNTPCTracksData0510->GetRMS() << "\t" << meanNTPCTracksWOAddSig0510 << "+-" << histoNTPCTracksWOAddSig0510->GetRMS() <<"\t" << meanNTPCTracksWAddSig0510 << "+-" << histoNTPCTracksWAddSig0510->GetRMS() << "\t" << meanNTPCTracksFinal0510 << "+-"<< histoNTPCTracksFinal0510->GetRMS() << endl;
	cout << "10-20% \t" << meanNTPCTracksData1020 << "+-" << histoNTPCTracksData1020->GetRMS() << "\t" << meanNTPCTracksWOAddSig1020 << "+-" << histoNTPCTracksWOAddSig1020->GetRMS() <<"\t" << meanNTPCTracksWAddSig1020 << "+-" << histoNTPCTracksWAddSig1020->GetRMS() << "\t" << meanNTPCTracksFinal1020 << "+-"<< histoNTPCTracksFinal1020->GetRMS() << endl;
	cout << "20-40% \t" << meanNTPCTracksData2040 << "+-" << histoNTPCTracksData2040->GetRMS() << "\t" << meanNTPCTracksWOAddSig2040 << "+-" << histoNTPCTracksWOAddSig2040->GetRMS() <<"\t" << meanNTPCTracksWAddSig2040 << "+-" << histoNTPCTracksWAddSig2040->GetRMS() << "\t" << meanNTPCTracksFinal2040 << "+-"<< histoNTPCTracksFinal2040->GetRMS() << endl;
	cout << "40-60% \t" << meanNTPCTracksData4060 << "+-" << histoNTPCTracksData4060->GetRMS() << "\t" << meanNTPCTracksWOAddSig4060 << "+-" << histoNTPCTracksWOAddSig4060->GetRMS() <<"\t" << meanNTPCTracksWAddSig4060 << "+-" << histoNTPCTracksWAddSig4060->GetRMS() << "\t" << meanNTPCTracksFinal4060 << "+-"<< histoNTPCTracksFinal4060->GetRMS() << endl;
	cout << "60-80% \t" << meanNTPCTracksData6080 << "+-" << histoNTPCTracksData6080->GetRMS() << "\t" << meanNTPCTracksWOAddSig6080 << "+-" << histoNTPCTracksWOAddSig6080->GetRMS() <<"\t" << meanNTPCTracksWAddSig6080 << "+-" << histoNTPCTracksWAddSig6080->GetRMS() << "\t" << meanNTPCTracksFinal6080 << "+-"<< histoNTPCTracksFinal6080->GetRMS() << endl<< endl;
		
	
	TCanvas* canvasMult0005 = new TCanvas("canvasMult0005","",200,10,700,500);  // gives the page size
	DrawGammaCanvasSettings( canvasMult0005,  0.12, 0.05, 0.05, 0.12);
	
  	canvasMult0005->SetLogy();
		TH2F * histo2DMult;
		histo2DMult = new TH2F("histo2DMult","histo2DMult",1000,0,3000.,20000,2.,5e8	);
 		histo2DMult->GetYaxis()->SetRangeUser(2.,5e6);
		histo2DMult->GetXaxis()->SetRangeUser(0.,3000.);
		SetStyleHistoTH2ForGraphs(histo2DMult, "# TPC tracks","normalized counts",0.03,0.04, 0.03,0.04, 1.,1.5);
		histo2DMult->Draw("copy");
	
		DrawGammaSetMarker(histoNTPCTracksData0005,20,markerSizeComparison, kBlack , kBlack);
// 		histoNTPCTracksData0005->GetYaxis()->SetRangeUser(0.,histoNTPCTracksData0005->GetMaximum());
		histoNTPCTracksData0005->Draw("E1psame");
		DrawGammaSetMarker(histoNTPCTracksWOAddSig0005,21,markerSizeComparison, kRed+2 , kRed+2);
		histoNTPCTracksWOAddSig0005->Draw("E1psame");
		DrawGammaSetMarker(histoNTPCTracksWAddSig0005,22,markerSizeComparison, kBlue , kBlue);
		histoNTPCTracksWAddSig0005->Draw("E1psame");
// 		
		TLatex *labelMult0005 = new TLatex(0.55,0.9,collisionSystemCent0.Data());
		SetStyleTLatex( labelMult0005, 0.035,4);
		labelMult0005->Draw();

		TLegend* legendMult0005 = new TLegend(0.13,0.8,0.3,0.93);
		legendMult0005->SetFillColor(0);
		legendMult0005->SetLineColor(0);
// 		legendMult0005->SetNColumns(2);
		legendMult0005->SetTextSize(0.03);
		legendMult0005->AddEntry(histoNTPCTracksData0005,Form("Data, #mu = %2.2e",meanNTPCTracksData0005),"p");
		legendMult0005->AddEntry(histoNTPCTracksWOAddSig0005,Form("MC (w\o add Sig), #mu = %2.2e",meanNTPCTracksWOAddSig0005),"p");
		legendMult0005->AddEntry(histoNTPCTracksWAddSig0005,Form("MC (w add Sig), #mu = %2.2e",meanNTPCTracksWAddSig0005),"p");
		legendMult0005->Draw();
	
	canvasMult0005->Update();
	canvasMult0005->Print(Form("%s/Mult0005.%s",outputDir.Data(),suffix.Data()));

	TCanvas* canvasEff0005 = new TCanvas("canvasEff0005","",200,10,1350,900);  // gives the page size
	DrawGammaCanvasSettings( canvasEff0005, 0.09, 0.02, 0.035, 0.09);
// 	canvasEff0005->SetLogy(1);	
					
	DrawAutoGammaMesonHistos( histoEffiFitWAddSig0005, 
			"", "p_{T} (GeV/c)", "#pi^{0} efficiency fitted", 
			kTRUE, 1.5, 3e-6, kFALSE,
			kFALSE, 0., 0.7, 
			kTRUE, 0., 7.);
			
	DrawGammaSetMarker(histoEffiFinalFitted0005, 22, 1., kBlack,kBlack);	
	histoEffiFinalFitted0005->DrawCopy("e1,same"); 	
	DrawGammaSetMarker(histoEffiFitWAddSig0005, 20, 1., kRed-2, kRed-2);	
	histoEffiFitWAddSig0005->DrawCopy("e1,same"); 	
	DrawGammaSetMarker(histoEffiFitWOAddSig0005, 21, 1., kBlue-2, kBlue-2);	
	histoEffiFitWOAddSig0005->DrawCopy("e1,same"); 	

	TLegend* legendEffiComp0005 = new TLegend(0.53,0.13,0.93,0.3);
	legendEffiComp0005->SetFillColor(0);
	legendEffiComp0005->SetLineColor(0);
	legendEffiComp0005->SetTextSize(0.03);
	legendEffiComp0005->AddEntry(histoEffiFinalFitted0005,Form("MC merged, #mu_{# TPC track} = %2.2e",meanNTPCTracksFinal0005),"p");
	legendEffiComp0005->AddEntry(histoEffiFitWOAddSig0005,Form("MC (w\o add Sig), #mu_{# TPC track} = %2.2e",meanNTPCTracksWOAddSig0005),"p");
	legendEffiComp0005->AddEntry(histoEffiFitWAddSig0005,Form("MC (w add Sig), #mu_{# TPC track} = %2.2e",meanNTPCTracksWAddSig0005),"p");
	legendEffiComp0005->Draw();
	
	canvasEff0005->SaveAs(Form("%s/EffCompSimple0005.%s",outputDir.Data(),suffix.Data()));
	delete canvasEff0005;

	TCanvas* canvasGamma0005 = new TCanvas("canvasGamma0005","",200,10,1350,900);  // gives the page size
	DrawGammaCanvasSettings( canvasGamma0005, 0.09, 0.02, 0.035, 0.09);
// 	canvasGamma0005->SetLogy(1);	
					
	DrawAutoGammaMesonHistos( histoGammaEffi0005, 
			"", "p_{T} (GeV/c)", "#gamma #epsilon_{eff}", 
			kFALSE, 1.5, 3e-6, kFALSE,
			kTRUE, 0.1, 1., 
			kFALSE, 0., 10.);
			
	DrawGammaSetMarker(histoGammaEffi0005, 20, 1.5, kBlack,kBlack);	
	histoGammaEffi0005->DrawCopy("e1,same"); 	
	DrawGammaSetMarker(histoGammaEffiWAddSig0005, 21, 1.5, kRed-2, kRed-2);	
	histoGammaEffiWAddSig0005->DrawCopy("e1,same"); 	
	DrawGammaSetMarker(histoGammaEffiWOAddSig0005, 22, 1.5, kBlue-2, kBlue-2);	
	histoGammaEffiWOAddSig0005->DrawCopy("e1,same"); 	

// 	DrawGammaSetMarker(histoGammaPur0005, 24, 1.5, kBlack,kBlack);	
// 	histoGammaPur0005->DrawCopy("e1,same"); 	
// 	DrawGammaSetMarker(histoGammaPurWAddSig0005, 25, 1.5, kRed-2, kRed-2);	
// 	histoGammaPurWAddSig0005->DrawCopy("e1,same"); 	
// 	DrawGammaSetMarker(histoGammaPurWOAddSig0005, 26, 1.5, kBlue-2, kBlue-2);	
// 	histoGammaPurWOAddSig0005->DrawCopy("e1,same"); 	

	TLegend* legendGammaComp0005 = new TLegend(0.33,0.13,0.63,0.3);
	legendGammaComp0005->SetFillColor(0);
	legendGammaComp0005->SetLineColor(0);
	legendGammaComp0005->SetNColumns(1);
	legendGammaComp0005->SetTextSize(0.03);
// 	legendGammaComp0005->AddEntry(histoGammaPur0005,"#epsilon_{pur}","p");
	legendGammaComp0005->AddEntry(histoGammaEffi0005,Form("#epsilon_{eff}, MC merged, #mu_{# TPC track} = %2.2e",meanNTPCTracksFinal0005),"p");
// 	legendGammaComp0005->AddEntry(histoGammaPurWAddSig0005,"#epsilon_{pur}","p");
	legendGammaComp0005->AddEntry(histoGammaEffiWAddSig0005,Form("#epsilon_{eff}, MC (w\o add Sig), #mu_{# TPC track} = %2.2e",meanNTPCTracksWOAddSig0005),"p");
// 	legendGammaComp0005->AddEntry(histoGammaPurWOAddSig0005,"#epsilon_{pur}","p");
	legendGammaComp0005->AddEntry(histoGammaEffiWOAddSig0005,Form("#epsilon_{eff}, MC (w add Sig), #mu_{# TPC track} = %2.2e",meanNTPCTracksWAddSig0005),"p");
	legendGammaComp0005->Draw();
	
	canvasGamma0005->SaveAs(Form("%s/GammaCompSimple0005.%s",outputDir.Data(),suffix.Data()));
	delete canvasGamma0005;

	TCanvas* canvasEff0005All = new TCanvas("canvasEff0005All","",200,10,1350,900);  // gives the page size
	DrawGammaCanvasSettings( canvasEff0005All, 0.09, 0.02, 0.035, 0.09);
// 	canvasEff0005All->SetLogy(1);	
					
	DrawAutoGammaMesonHistos( histoEffiFinal0005, 
			"", "p_{T} (GeV/c)", "#pi^{0} efficiency fitted", 
			kFALSE, 1.5, 3e-6, kFALSE,
			kFALSE, 0., 0.7, 
			kTRUE, 0., 7.);
			
	DrawGammaSetMarker(histoEffiFinal0005, 22, 1., kGreen+2, kGreen+2);	
	histoEffiFinal0005->DrawCopy("e1"); 	
// 	DrawGammaSetMarker(histoEffiFinalFitted0005, 22, 1., kBlack,kBlack);	
// 	histoEffiFinalFitted0005->DrawCopy("e1,same"); 	
	
	DrawGammaSetMarker(histoEffiWAddSig0005, 20, 1., kOrange+2, kOrange+2);	
	histoEffiWAddSig0005->DrawCopy("e1,same"); 	
// 	DrawGammaSetMarker(histoEffiFitWAddSig0005, 20, 1., kRed-2, kRed-2);	
// 	histoEffiFitWAddSig0005->DrawCopy("e1,same"); 	
// 	DrawGammaSetMarker(histoEffiWAddSig0005AddSig, 20, 1., kRed-2, kRed-2);	
// 	histoEffiWAddSig0005AddSig->DrawCopy("e1,same"); 	
// 	
	DrawGammaSetMarker(histoEffiWOAddSig0005, 21, 1., kViolet, kViolet);	
	histoEffiWOAddSig0005->DrawCopy("e1,same"); 	
// 	DrawGammaSetMarker(histoEffiFitWOAddSig0005, 21, 1., kBlue-2, kBlue-2);	
// 	histoEffiFitWOAddSig0005->DrawCopy("e1,same"); 	

	TLegend* legendEffiComp0005All = new TLegend(0.53,0.13,0.93,0.3);
	legendEffiComp0005All->SetFillColor(0);
	legendEffiComp0005All->SetLineColor(0);
	legendEffiComp0005All->SetNColumns(1);
	legendEffiComp0005All->SetTextSize(0.025);
	legendEffiComp0005All->AddEntry(histoEffiFinal0005,Form("MC merged #mu_{# TPC track} = %2.2e",meanNTPCTracksFinal0005),"p");
// 	legendEffiComp0005All->AddEntry(histoEffiFinalFitted0005,Form("MC merged, fitted, #mu_{# TPC track} = %2.2e",meanNTPCTracksFinal0005),"p");
	legendEffiComp0005All->AddEntry(histoEffiWOAddSig0005,Form("MC (w\o add Sig), #mu_{# TPC track} = %2.2e",meanNTPCTracksWOAddSig0005),"p");
// 	legendEffiComp0005All->AddEntry(histoEffiFitWOAddSig0005,Form("MC (w\o add Sig), fitted, #mu_{# TPC track} = %2.2e",meanNTPCTracksWOAddSig0005),"p");
	legendEffiComp0005All->AddEntry(histoEffiWAddSig0005,Form("MC (w add Sig), #mu_{# TPC track} = %2.2e",meanNTPCTracksWAddSig0005),"p");
// 	legendEffiComp0005All->AddEntry(histoEffiFitWAddSig0005,Form("MC (w add Sig), fitted, #mu_{# TPC track} = %2.2e",meanNTPCTracksWAddSig0005),"p");
	legendEffiComp0005All->Draw();
	
	canvasEff0005All->SaveAs(Form("%s/EffCompSimple0005All.%s",outputDir.Data(),suffix.Data()));
	delete canvasEff0005All;

	
	TCanvas* canvasMult0510 = new TCanvas("canvasMult0510","",200,10,700,500);  // gives the page size
	DrawGammaCanvasSettings( canvasMult0510,  0.12, 0.05, 0.05, 0.12);
	
  	canvasMult0510->SetLogy();
		histo2DMult->GetYaxis()->SetRangeUser(2.,5e6);
		histo2DMult->GetXaxis()->SetRangeUser(0.,3000.);
		histo2DMult->Draw("copy");
	
		DrawGammaSetMarker(histoNTPCTracksData0510,20,markerSizeComparison, kBlack , kBlack);
// 		histoNTPCTracksData0510->GetYaxis()->SetRangeUser(0.,histoNTPCTracksData0510->GetMaximum());
		histoNTPCTracksData0510->Draw("E1psame");
		DrawGammaSetMarker(histoNTPCTracksWOAddSig0510,21,markerSizeComparison, kRed+2 , kRed+2);
		histoNTPCTracksWOAddSig0510->Draw("E1psame");
		DrawGammaSetMarker(histoNTPCTracksWAddSig0510,22,markerSizeComparison, kBlue , kBlue);
		histoNTPCTracksWAddSig0510->Draw("E1psame");
// 
		TLatex *labelMult0510 = new TLatex(0.55,0.9,collisionSystemCent1.Data());
		SetStyleTLatex( labelMult0510, 0.035,4);
		labelMult0510->Draw();

		TLegend* legendMult0510 = new TLegend(0.13,0.8,0.3,0.93);
		legendMult0510->SetFillColor(0);
		legendMult0510->SetLineColor(0);
// 		legendMult0510->SetNColumns(2);
		legendMult0510->SetTextSize(0.03);
		legendMult0510->AddEntry(histoNTPCTracksData0510,Form("Data, #mu = %2.2e",meanNTPCTracksData0510),"p");
		legendMult0510->AddEntry(histoNTPCTracksWOAddSig0510,Form("MC (w\o add Sig), #mu = %2.2e",meanNTPCTracksWOAddSig0510),"p");
		legendMult0510->AddEntry(histoNTPCTracksWAddSig0510,Form("MC (w add Sig), #mu = %2.2e",meanNTPCTracksWAddSig0510),"p");
		legendMult0510->Draw();
	
	canvasMult0510->Update();
	canvasMult0510->Print(Form("%s/Mult0510.%s",outputDir.Data(),suffix.Data()));

	TCanvas* canvasEff0510 = new TCanvas("canvasEff0510","",200,10,1350,900);  // gives the page size
	DrawGammaCanvasSettings( canvasEff0510, 0.09, 0.02, 0.035, 0.09);
					
		DrawAutoGammaMesonHistos( histoEffiFitWAddSig0510, 
				"", "p_{T} (GeV/c)", "#pi^{0} efficiency fitted", 
				kTRUE, 1.5, 3e-6, kFALSE,
				kFALSE, 0., 0.7, 
				kTRUE, 0., 7.);
				
		DrawGammaSetMarker(histoEffiFinalFitted0510, 22, 1., kBlack,kBlack);	
		histoEffiFinalFitted0510->DrawCopy("e1,same"); 	
		DrawGammaSetMarker(histoEffiFitWAddSig0510, 20, 1., kRed-2, kRed-2);	
		histoEffiFitWAddSig0510->DrawCopy("e1,same"); 	
		DrawGammaSetMarker(histoEffiFitWOAddSig0510, 21, 1., kBlue-2, kBlue-2);	
		histoEffiFitWOAddSig0510->DrawCopy("e1,same"); 	
		
		TLegend* legendEffiComp0510 = new TLegend(0.53,0.13,0.93,0.3);
		legendEffiComp0510->SetFillColor(0);
		legendEffiComp0510->SetLineColor(0);
		legendEffiComp0510->SetTextSize(0.03);
		legendEffiComp0510->AddEntry(histoEffiFinalFitted0510,Form("MC merged, #mu_{# TPC track} = %2.2e",meanNTPCTracksFinal0510),"p");
		legendEffiComp0510->AddEntry(histoEffiFitWOAddSig0510,Form("MC (w\o add Sig), #mu_{# TPC track} = %2.2e",meanNTPCTracksWOAddSig0510),"p");
		legendEffiComp0510->AddEntry(histoEffiFitWAddSig0510,Form("MC (w add Sig), #mu_{# TPC track} = %2.2e",meanNTPCTracksWAddSig0510),"p");
		legendEffiComp0510->Draw();
		
	canvasEff0510->SaveAs(Form("%s/EffCompSimple0510.%s",outputDir.Data(),suffix.Data()));
	delete canvasEff0510;

	TCanvas* canvasGamma0510 = new TCanvas("canvasGamma0510","",200,10,1350,900);  // gives the page size
	DrawGammaCanvasSettings( canvasGamma0510, 0.09, 0.02, 0.035, 0.09);
// 	canvasGamma0510->SetLogy(1);	
					
		DrawAutoGammaMesonHistos( histoGammaEffi0510, 
				"", "p_{T} (GeV/c)", "#gamma #epsilon_{eff}", 
				kFALSE, 1.5, 3e-6, kFALSE,
				kTRUE, 0.1, 1., 
				kFALSE, 0., 10.);
				
		DrawGammaSetMarker(histoGammaEffi0510, 20, 1.5, kBlack,kBlack);	
		histoGammaEffi0510->DrawCopy("e1,same"); 	
		DrawGammaSetMarker(histoGammaEffiWAddSig0510, 21, 1.5, kRed-2, kRed-2);	
		histoGammaEffiWAddSig0510->DrawCopy("e1,same"); 	
		DrawGammaSetMarker(histoGammaEffiWOAddSig0510, 22, 1.5, kBlue-2, kBlue-2);	
		histoGammaEffiWOAddSig0510->DrawCopy("e1,same"); 	

// 		DrawGammaSetMarker(histoGammaPur0510, 24, 1.5, kBlack,kBlack);	
// 		histoGammaPur0510->DrawCopy("e1,same"); 	
// 		DrawGammaSetMarker(histoGammaPurWAddSig0510, 25, 1.5, kRed-2, kRed-2);	
// 		histoGammaPurWAddSig0510->DrawCopy("e1,same"); 	
// 		DrawGammaSetMarker(histoGammaPurWOAddSig0510, 26, 1.5, kBlue-2, kBlue-2);	
// 		histoGammaPurWOAddSig0510->DrawCopy("e1,same"); 	

		TLegend* legendGammaComp0510 = new TLegend(0.33,0.13,0.63,0.3);
		legendGammaComp0510->SetFillColor(0);
		legendGammaComp0510->SetLineColor(0);
		legendGammaComp0510->SetNColumns(1);
		legendGammaComp0510->SetTextSize(0.03);
// 		legendGammaComp0510->AddEntry(histoGammaPur0510,"#epsilon_{pur}","p");
		legendGammaComp0510->AddEntry(histoGammaEffi0510,Form("#epsilon_{eff}, MC merged, #mu_{# TPC track} = %2.2e",meanNTPCTracksFinal0510),"p");
// 		legendGammaComp0510->AddEntry(histoGammaPurWAddSig0510,"#epsilon_{pur}","p");
		legendGammaComp0510->AddEntry(histoGammaEffiWAddSig0510,Form("#epsilon_{eff}, MC (w\o add Sig), #mu_{# TPC track} = %2.2e",meanNTPCTracksWOAddSig0510),"p");
// 		legendGammaComp0510->AddEntry(histoGammaPurWOAddSig0510,"#epsilon_{pur}","p");
		legendGammaComp0510->AddEntry(histoGammaEffiWOAddSig0510,Form("#epsilon_{eff}, MC (w add Sig), #mu_{# TPC track} = %2.2e",meanNTPCTracksWAddSig0510),"p");
		legendGammaComp0510->Draw();
	
	canvasGamma0510->SaveAs(Form("%s/GammaCompSimple0510.%s",outputDir.Data(),suffix.Data()));
	delete canvasGamma0510;

	TCanvas* canvasEff0510All = new TCanvas("canvasEff0510All","",200,10,1350,900);  // gives the page size
	DrawGammaCanvasSettings( canvasEff0510All, 0.09, 0.02, 0.035, 0.09);
// 	canvasEff0510All->SetLogy(1);	
					
	DrawAutoGammaMesonHistos( histoEffiFinal0510, 
			"", "p_{T} (GeV/c)", "#pi^{0} efficiency fitted", 
			kFALSE, 1.5, 3e-6, kFALSE,
			kFALSE, 0., 0.7, 
			kTRUE, 0., 7.);
			
	DrawGammaSetMarker(histoEffiFinal0510, 22, 1., kGreen+2, kGreen+2);	
	histoEffiFinal0510->DrawCopy("e1"); 	
// 	DrawGammaSetMarker(histoEffiFinalFitted0510, 22, 1., kBlack,kBlack);	
// 	histoEffiFinalFitted0510->DrawCopy("e1,same"); 	
	
	DrawGammaSetMarker(histoEffiWAddSig0510, 20, 1., kOrange+2, kOrange+2);	
	histoEffiWAddSig0510->DrawCopy("e1,same"); 	
// 	DrawGammaSetMarker(histoEffiFitWAddSig0510, 20, 1., kRed-2, kRed-2);	
// 	histoEffiFitWAddSig0510->DrawCopy("e1,same"); 	
	
	DrawGammaSetMarker(histoEffiWOAddSig0510, 21, 1., kViolet, kViolet);	
	histoEffiWOAddSig0510->DrawCopy("e1,same"); 	
// 	DrawGammaSetMarker(histoEffiFitWOAddSig0510, 21, 1., kBlue-2, kBlue-2);	
// 	histoEffiFitWOAddSig0510->DrawCopy("e1,same"); 	

	TLegend* legendEffiComp0510All = new TLegend(0.53,0.13,0.93,0.3);
	legendEffiComp0510All->SetFillColor(0);
	legendEffiComp0510All->SetLineColor(0);
	legendEffiComp0510All->SetNColumns(1);
	legendEffiComp0510All->SetTextSize(0.025);
	legendEffiComp0510All->AddEntry(histoEffiFinal0510,Form("MC merged #mu_{# TPC track} = %2.2e",meanNTPCTracksFinal0510),"p");
// 	legendEffiComp0510All->AddEntry(histoEffiFinalFitted0510,Form("MC merged, fitted, #mu_{# TPC track} = %2.2e",meanNTPCTracksFinal0510),"p");
	legendEffiComp0510All->AddEntry(histoEffiWOAddSig0510,Form("MC (w\o add Sig), #mu_{# TPC track} = %2.2e",meanNTPCTracksWOAddSig0510),"p");
// 	legendEffiComp0510All->AddEntry(histoEffiFitWOAddSig0510,Form("MC (w\o add Sig), fitted, #mu_{# TPC track} = %2.2e",meanNTPCTracksWOAddSig0510),"p");
	legendEffiComp0510All->AddEntry(histoEffiWAddSig0510,Form("MC (w add Sig), #mu_{# TPC track} = %2.2e",meanNTPCTracksWAddSig0510),"p");
// 	legendEffiComp0510All->AddEntry(histoEffiFitWAddSig0510,Form("MC (w add Sig), fitted, #mu_{# TPC track} = %2.2e",meanNTPCTracksWAddSig0510),"p");
	legendEffiComp0510All->Draw();
	
	canvasEff0510All->SaveAs(Form("%s/EffCompSimple0510All.%s",outputDir.Data(),suffix.Data()));
	delete canvasEff0510All;
	
	TCanvas* canvasMult1020 = new TCanvas("canvasMult1020","",200,10,700,500);  // gives the page size
	DrawGammaCanvasSettings( canvasMult1020,  0.12, 0.05, 0.05, 0.12);
	
  	canvasMult1020->SetLogy();
		histo2DMult->GetYaxis()->SetRangeUser(2.,5e6);
		histo2DMult->GetXaxis()->SetRangeUser(0.,3000.);
		histo2DMult->Draw("copy");
	
		DrawGammaSetMarker(histoNTPCTracksData1020,20,markerSizeComparison, kBlack , kBlack);
// 		histoNTPCTracksData1020->GetYaxis()->SetRangeUser(0.,histoNTPCTracksData1020->GetMaximum());
		histoNTPCTracksData1020->Draw("E1psame");
		DrawGammaSetMarker(histoNTPCTracksWOAddSig1020,21,markerSizeComparison, kRed+2 , kRed+2);
		histoNTPCTracksWOAddSig1020->Draw("E1psame");
		DrawGammaSetMarker(histoNTPCTracksWAddSig1020,22,markerSizeComparison, kBlue , kBlue);
		histoNTPCTracksWAddSig1020->Draw("E1psame");
// 
		TLatex *labelMult1020 = new TLatex(0.55,0.9,collisionSystemCent2.Data());
		SetStyleTLatex( labelMult1020, 0.035,4);
		labelMult1020->Draw();

		TLegend* legendMult1020 = new TLegend(0.13,0.8,0.3,0.93);
		legendMult1020->SetFillColor(0);
		legendMult1020->SetLineColor(0);
// 		legendMult1020->SetNColumns(2);
		legendMult1020->SetTextSize(0.03);
		legendMult1020->AddEntry(histoNTPCTracksData1020,Form("Data, #mu = %2.2e",meanNTPCTracksData1020),"p");
		legendMult1020->AddEntry(histoNTPCTracksWOAddSig1020,Form("MC (w\o add Sig), #mu = %2.2e",meanNTPCTracksWOAddSig1020),"p");
		legendMult1020->AddEntry(histoNTPCTracksWAddSig1020,Form("MC (w add Sig), #mu = %2.2e",meanNTPCTracksWAddSig1020),"p");
		legendMult1020->Draw();
	
	canvasMult1020->Update();
	canvasMult1020->Print(Form("%s/Mult1020.%s",outputDir.Data(),suffix.Data()));

	TCanvas* canvasEff1020 = new TCanvas("canvasEff1020","",200,10,1350,900);  // gives the page size
	DrawGammaCanvasSettings( canvasEff1020, 0.09, 0.02, 0.035, 0.09);
					
		DrawAutoGammaMesonHistos( histoEffiFitWAddSig1020, 
				"", "p_{T} (GeV/c)", "#pi^{0} efficiency fitted", 
				kTRUE, 1.5, 3e-6, kFALSE,
				kFALSE, 0., 0.7, 
				kTRUE, 0., 7.);
		DrawGammaSetMarker(histoEffiFinalFitted1020, 22, 1., kBlack,kBlack);	
		histoEffiFinalFitted1020->DrawCopy("e1,same"); 	
		DrawGammaSetMarker(histoEffiFitWAddSig1020, 20, 1., kRed-2, kRed-2);	
		histoEffiFitWAddSig1020->DrawCopy("e1,same"); 	
		DrawGammaSetMarker(histoEffiFitWOAddSig1020, 21, 1., kBlue-2, kBlue-2);	
		histoEffiFitWOAddSig1020->DrawCopy("e1,same"); 	
		
		TLegend* legendEffiComp1020 = new TLegend(0.53,0.13,0.93,0.3);
		legendEffiComp1020->SetFillColor(0);
		legendEffiComp1020->SetLineColor(0);
		legendEffiComp1020->SetTextSize(0.03);
		legendEffiComp1020->AddEntry(histoEffiFinalFitted1020,Form("MC merged, #mu_{# TPC track} = %2.2e",meanNTPCTracksFinal1020),"p");
		legendEffiComp1020->AddEntry(histoEffiFitWOAddSig1020,Form("MC (w\o add Sig), #mu_{# TPC track} = %2.2e",meanNTPCTracksWOAddSig1020),"p");
		legendEffiComp1020->AddEntry(histoEffiFitWAddSig1020,Form("MC (w add Sig), #mu_{# TPC track} = %2.2e",meanNTPCTracksWAddSig1020),"p");
		legendEffiComp1020->Draw();
	
	canvasEff1020->SaveAs(Form("%s/EffCompSimple1020.%s",outputDir.Data(),suffix.Data()));
	delete canvasEff1020;

	TCanvas* canvasEff1020All = new TCanvas("canvasEff1020All","",200,10,1350,900);  // gives the page size
	DrawGammaCanvasSettings( canvasEff1020All, 0.09, 0.02, 0.035, 0.09);
// 	canvasEff1020All->SetLogy(1);	
					
	DrawAutoGammaMesonHistos( histoEffiFinal1020, 
			"", "p_{T} (GeV/c)", "#pi^{0} efficiency fitted", 
			kFALSE, 1.5, 3e-6, kFALSE,
			kFALSE, 0., 0.7, 
			kTRUE, 0., 7.);
			
	DrawGammaSetMarker(histoEffiFinal1020, 22, 1., kGreen+2, kGreen+2);	
	histoEffiFinal1020->DrawCopy("e1"); 	
// 	DrawGammaSetMarker(histoEffiFinalFitted1020, 22, 1., kBlack,kBlack);	
// 	histoEffiFinalFitted1020->DrawCopy("e1,same"); 	
// 	
	DrawGammaSetMarker(histoEffiWAddSig1020, 20, 1., kOrange+2, kOrange+2);	
	histoEffiWAddSig1020->DrawCopy("e1,same"); 	
// 	DrawGammaSetMarker(histoEffiFitWAddSig1020, 20, 1., kRed-2, kRed-2);	
// 	histoEffiFitWAddSig1020->DrawCopy("e1,same"); 	
// 	
	DrawGammaSetMarker(histoEffiWOAddSig1020, 21, 1., kViolet, kViolet);	
	histoEffiWOAddSig1020->DrawCopy("e1,same"); 	
// 	DrawGammaSetMarker(histoEffiFitWOAddSig1020, 21, 1., kBlue-2, kBlue-2);	
// 	histoEffiFitWOAddSig1020->DrawCopy("e1,same"); 	

	TLegend* legendEffiComp1020All = new TLegend(0.53,0.13,0.93,0.3);
	legendEffiComp1020All->SetFillColor(0);
	legendEffiComp1020All->SetLineColor(0);
	legendEffiComp1020All->SetNColumns(1);
	legendEffiComp1020All->SetTextSize(0.025);
	legendEffiComp1020All->AddEntry(histoEffiFinal1020,Form("MC merged #mu_{# TPC track} = %2.2e",meanNTPCTracksFinal1020),"p");
// 	legendEffiComp1020All->AddEntry(histoEffiFinalFitted1020,Form("MC merged, fitted, #mu_{# TPC track} = %2.2e",meanNTPCTracksFinal1020),"p");
	legendEffiComp1020All->AddEntry(histoEffiWOAddSig1020,Form("MC (w\o add Sig), #mu_{# TPC track} = %2.2e",meanNTPCTracksWOAddSig1020),"p");
// 	legendEffiComp1020All->AddEntry(histoEffiFitWOAddSig1020,Form("MC (w\o add Sig), fitted, #mu_{# TPC track} = %2.2e",meanNTPCTracksWOAddSig1020),"p");
	legendEffiComp1020All->AddEntry(histoEffiWAddSig1020,Form("MC (w add Sig), #mu_{# TPC track} = %2.2e",meanNTPCTracksWAddSig1020),"p");
// 	legendEffiComp1020All->AddEntry(histoEffiFitWAddSig1020,Form("MC (w add Sig), fitted, #mu_{# TPC track} = %2.2e",meanNTPCTracksWAddSig1020),"p");
	legendEffiComp1020All->Draw();
	
	canvasEff1020All->SaveAs(Form("%s/EffCompSimple1020All.%s",outputDir.Data(),suffix.Data()));
	delete canvasEff1020All;

	TCanvas* canvasGamma1020 = new TCanvas("canvasGamma1020","",200,10,1350,900);  // gives the page size
	DrawGammaCanvasSettings( canvasGamma1020, 0.09, 0.02, 0.035, 0.09);
// 	canvasGamma1020->SetLogy(1);	
					
		DrawAutoGammaMesonHistos( histoGammaEffi1020, 
				"", "p_{T} (GeV/c)", "#gamma #epsilon_{eff}", 
				kFALSE, 1.5, 3e-6, kFALSE,
				kTRUE, 0.1, 1., 
				kFALSE, 0., 10.);
				
		DrawGammaSetMarker(histoGammaEffi1020, 20, 1.5, kBlack,kBlack);	
		histoGammaEffi1020->DrawCopy("e1,same"); 	
		DrawGammaSetMarker(histoGammaEffiWAddSig1020, 21, 1.5, kRed-2, kRed-2);	
		histoGammaEffiWAddSig1020->DrawCopy("e1,same"); 	
		DrawGammaSetMarker(histoGammaEffiWOAddSig1020, 22, 1.5, kBlue-2, kBlue-2);	
		histoGammaEffiWOAddSig1020->DrawCopy("e1,same"); 	

// 		DrawGammaSetMarker(histoGammaPur1020, 24, 1.5, kBlack,kBlack);	
// 		histoGammaPur1020->DrawCopy("e1,same"); 	
// 		DrawGammaSetMarker(histoGammaPurWAddSig1020, 25, 1.5, kRed-2, kRed-2);	
// 		histoGammaPurWAddSig1020->DrawCopy("e1,same"); 	
// 		DrawGammaSetMarker(histoGammaPurWOAddSig1020, 26, 1.5, kBlue-2, kBlue-2);	
// 		histoGammaPurWOAddSig1020->DrawCopy("e1,same"); 	

		TLegend* legendGammaComp1020 = new TLegend(0.33,0.13,0.63,0.3);
		legendGammaComp1020->SetFillColor(0);
		legendGammaComp1020->SetLineColor(0);
		legendGammaComp1020->SetNColumns(1);
		legendGammaComp1020->SetTextSize(0.03);
// 		legendGammaComp1020->AddEntry(histoGammaPur1020,"#epsilon_{pur}","p");
		legendGammaComp1020->AddEntry(histoGammaEffi1020,Form("#epsilon_{eff}, MC merged, #mu_{# TPC track} = %2.2e",meanNTPCTracksFinal1020),"p");
// 		legendGammaComp1020->AddEntry(histoGammaPurWAddSig1020,"#epsilon_{pur}","p");
		legendGammaComp1020->AddEntry(histoGammaEffiWAddSig1020,Form("#epsilon_{eff}, MC (w\o add Sig), #mu_{# TPC track} = %2.2e",meanNTPCTracksWOAddSig1020),"p");
// 		legendGammaComp1020->AddEntry(histoGammaPurWOAddSig1020,"#epsilon_{pur}","p");
		legendGammaComp1020->AddEntry(histoGammaEffiWOAddSig1020,Form("#epsilon_{eff}, MC (w add Sig), #mu_{# TPC track} = %2.2e",meanNTPCTracksWAddSig1020),"p");
		legendGammaComp1020->Draw();
	
	canvasGamma1020->SaveAs(Form("%s/GammaCompSimple1020.%s",outputDir.Data(),suffix.Data()));
	delete canvasGamma1020;

	TCanvas* canvasMult2040 = new TCanvas("canvasMult2040","",200,10,700,500);  // gives the page size
	DrawGammaCanvasSettings( canvasMult2040,  0.12, 0.05, 0.05, 0.12);
	
  	canvasMult2040->SetLogy();
		histo2DMult->GetYaxis()->SetRangeUser(2.,5e6);
		histo2DMult->GetXaxis()->SetRangeUser(0.,3000.);
		histo2DMult->Draw("copy");
	
		DrawGammaSetMarker(histoNTPCTracksData2040,20,markerSizeComparison, kBlack , kBlack);
// 		histoNTPCTracksData2040->GetYaxis()->SetRangeUser(0.,histoNTPCTracksData2040->GetMaximum());
		histoNTPCTracksData2040->Draw("E1psame");
		DrawGammaSetMarker(histoNTPCTracksWOAddSig2040,21,markerSizeComparison, kRed+2 , kRed+2);
		histoNTPCTracksWOAddSig2040->Draw("E1psame");
		DrawGammaSetMarker(histoNTPCTracksWAddSig2040,22,markerSizeComparison, kBlue , kBlue);
		histoNTPCTracksWAddSig2040->Draw("E1psame");
// 
		TLatex *labelMult2040 = new TLatex(0.55,0.9,collisionSystemSemiCent.Data());
		SetStyleTLatex( labelMult2040, 0.035,4);
		labelMult2040->Draw();

		TLegend* legendMult2040 = new TLegend(0.13,0.8,0.3,0.93);
		legendMult2040->SetFillColor(0);
		legendMult2040->SetLineColor(0);
// 		legendMult2040->SetNColumns(2);
		legendMult2040->SetTextSize(0.03);
		legendMult2040->AddEntry(histoNTPCTracksData2040,Form("Data, #mu = %2.2e",meanNTPCTracksData2040),"p");
		legendMult2040->AddEntry(histoNTPCTracksWOAddSig2040,Form("MC (w\o add Sig), #mu = %2.2e",meanNTPCTracksWOAddSig2040),"p");
		legendMult2040->AddEntry(histoNTPCTracksWAddSig2040,Form("MC (w add Sig), #mu = %2.2e",meanNTPCTracksWAddSig2040),"p");
		legendMult2040->Draw();
	
	canvasMult2040->Update();
	canvasMult2040->Print(Form("%s/Mult2040.%s",outputDir.Data(),suffix.Data()));

	TCanvas* canvasEff2040 = new TCanvas("canvasEff2040","",200,10,1350,900);  // gives the page size
	DrawGammaCanvasSettings( canvasEff2040, 0.09, 0.02, 0.035, 0.09);
					
		DrawAutoGammaMesonHistos( histoEffiFinalFitted2040, 
				"", "p_{T} (GeV/c)", "#pi^{0} efficiency fitted", 
				kTRUE, 1.5, 3e-6, kFALSE,
				kFALSE, 0., 0.7, 
				kTRUE, 0., 7.);
		DrawGammaSetMarker(histoEffiFinalFitted2040, 22, 1., kBlack,kBlack);	
		histoEffiFinalFitted2040->DrawCopy("e1,same"); 	
		DrawGammaSetMarker(histoEffiFitWAddSig2040, 20, 1., kRed-2, kRed-2);	
		histoEffiFitWAddSig2040->DrawCopy("e1,same"); 	
		DrawGammaSetMarker(histoEffiFitWOAddSig2040, 21, 1., kBlue-2, kBlue-2);	
		histoEffiFitWOAddSig2040->DrawCopy("e1,same"); 	
		
		TLegend* legendEffiComp2040 = new TLegend(0.53,0.13,0.93,0.3);
		legendEffiComp2040->SetFillColor(0);
		legendEffiComp2040->SetLineColor(0);
		legendEffiComp2040->SetTextSize(0.03);
		legendEffiComp2040->AddEntry(histoEffiFinalFitted2040,Form("MC merged, #mu_{# TPC track} = %2.2e",meanNTPCTracksFinal2040),"p");
		legendEffiComp2040->AddEntry(histoEffiFitWOAddSig2040,Form("MC (w\o add Sig), #mu_{# TPC track} = %2.2e",meanNTPCTracksWOAddSig2040),"p");
		legendEffiComp2040->AddEntry(histoEffiFitWAddSig2040,Form("MC (w add Sig), #mu_{# TPC track} = %2.2e",meanNTPCTracksWAddSig2040),"p");
		legendEffiComp2040->Draw();
	
	canvasEff2040->SaveAs(Form("%s/EffCompSimple2040.%s",outputDir.Data(),suffix.Data()));
	delete canvasEff2040;

	TCanvas* canvasEff2040All = new TCanvas("canvasEff2040All","",200,10,1350,900);  // gives the page size
	DrawGammaCanvasSettings( canvasEff2040All, 0.09, 0.02, 0.035, 0.09);
	// 	canvasEff2040All->SetLogy(1);	
						
		DrawAutoGammaMesonHistos( histoEffiFinal2040, 
				"", "p_{T} (GeV/c)", "#pi^{0} efficiency fitted", 
				kFALSE, 1.5, 3e-6, kFALSE,
				kFALSE, 0., 0.7, 
				kTRUE, 0., 7.);
				
		DrawGammaSetMarker(histoEffiFinal2040, 22, 1., kGreen+2, kGreen+2);	
		histoEffiFinal2040->DrawCopy("e1"); 	
// 		DrawGammaSetMarker(histoEffiFinalFitted2040, 22, 1., kBlack,kBlack);	
// 		histoEffiFinalFitted2040->DrawCopy("e1,same"); 	
// 		
		DrawGammaSetMarker(histoEffiWAddSig2040, 20, 1., kOrange+2, kOrange+2);	
		histoEffiWAddSig2040->DrawCopy("e1,same"); 	
// 		DrawGammaSetMarker(histoEffiFitWAddSig2040, 20, 1., kRed-2, kRed-2);	
// 		histoEffiFitWAddSig2040->DrawCopy("e1,same"); 	
// 		
		DrawGammaSetMarker(histoEffiWOAddSig2040, 21, 1., kViolet, kViolet);	
		histoEffiWOAddSig2040->DrawCopy("e1,same"); 	
// 		DrawGammaSetMarker(histoEffiFitWOAddSig2040, 21, 1., kBlue-2, kBlue-2);	
// 		histoEffiFitWOAddSig2040->DrawCopy("e1,same"); 	

		TLegend* legendEffiComp2040All = new TLegend(0.53,0.13,0.93,0.3);
		legendEffiComp2040All->SetFillColor(0);
		legendEffiComp2040All->SetLineColor(0);
		legendEffiComp2040All->SetNColumns(1);
		legendEffiComp2040All->SetTextSize(0.025);
		legendEffiComp2040All->AddEntry(histoEffiFinal2040,Form("MC merged #mu_{# TPC track} = %2.2e",meanNTPCTracksFinal2040),"p");
// 		legendEffiComp2040All->AddEntry(histoEffiFinalFitted2040,Form("MC merged, fitted, #mu_{# TPC track} = %2.2e",meanNTPCTracksFinal2040),"p");
		legendEffiComp2040All->AddEntry(histoEffiWOAddSig2040,Form("MC (w\o add Sig), #mu_{# TPC track} = %2.2e",meanNTPCTracksWOAddSig2040),"p");
// 		legendEffiComp2040All->AddEntry(histoEffiFitWOAddSig2040,Form("MC (w\o add Sig), fitted, #mu_{# TPC track} = %2.2e",meanNTPCTracksWOAddSig2040),"p");
		legendEffiComp2040All->AddEntry(histoEffiWAddSig2040,Form("MC (w add Sig), #mu_{# TPC track} = %2.2e",meanNTPCTracksWAddSig2040),"p");
// 		legendEffiComp2040All->AddEntry(histoEffiFitWAddSig2040,Form("MC (w add Sig), fitted, #mu_{# TPC track} = %2.2e",meanNTPCTracksWAddSig2040),"p");
		legendEffiComp2040All->Draw();
		
	canvasEff2040All->SaveAs(Form("%s/EffCompSimple2040All.%s",outputDir.Data(),suffix.Data()));
	delete canvasEff2040All;

	TCanvas* canvasGamma2040 = new TCanvas("canvasGamma2040","",200,10,1350,900);  // gives the page size
	DrawGammaCanvasSettings( canvasGamma2040, 0.09, 0.02, 0.035, 0.09);
// 	canvasGamma2040->SetLogy(1);	
					
		DrawAutoGammaMesonHistos( histoGammaEffi2040, 
				"", "p_{T} (GeV/c)", "#gamma #epsilon_{eff}", 
				kFALSE, 1.5, 3e-6, kFALSE,
				kTRUE, 0.1, 1., 
				kFALSE, 0., 10.);
				
		DrawGammaSetMarker(histoGammaEffi2040, 20, 1.5, kBlack,kBlack);	
		histoGammaEffi2040->DrawCopy("e1,same"); 	
		DrawGammaSetMarker(histoGammaEffiWAddSig2040, 21, 1.5, kRed-2, kRed-2);	
		histoGammaEffiWAddSig2040->DrawCopy("e1,same"); 	
		DrawGammaSetMarker(histoGammaEffiWOAddSig2040, 22, 1.5, kBlue-2, kBlue-2);	
		histoGammaEffiWOAddSig2040->DrawCopy("e1,same"); 	

// 		DrawGammaSetMarker(histoGammaPur2040, 24, 1.5, kBlack,kBlack);	
// 		histoGammaPur2040->DrawCopy("e1,same"); 	
// 		DrawGammaSetMarker(histoGammaPurWAddSig2040, 25, 1.5, kRed-2, kRed-2);	
// 		histoGammaPurWAddSig2040->DrawCopy("e1,same"); 	
// 		DrawGammaSetMarker(histoGammaPurWOAddSig2040, 26, 1.5, kBlue-2, kBlue-2);	
// 		histoGammaPurWOAddSig2040->DrawCopy("e1,same"); 	

		TLegend* legendGammaComp2040 = new TLegend(0.33,0.13,0.63,0.3);
		legendGammaComp2040->SetFillColor(0);
		legendGammaComp2040->SetLineColor(0);
		legendGammaComp2040->SetNColumns(1);
		legendGammaComp2040->SetTextSize(0.03);
// 		legendGammaComp2040->AddEntry(histoGammaPur2040,"#epsilon_{pur}","p");
		legendGammaComp2040->AddEntry(histoGammaEffi2040,Form("#epsilon_{eff}, MC merged, #mu_{# TPC track} = %2.2e",meanNTPCTracksFinal2040),"p");
// 		legendGammaComp2040->AddEntry(histoGammaPurWAddSig2040,"#epsilon_{pur}","p");
		legendGammaComp2040->AddEntry(histoGammaEffiWAddSig2040,Form("#epsilon_{eff}, MC (w\o add Sig), #mu_{# TPC track} = %2.2e",meanNTPCTracksWOAddSig2040),"p");
// 		legendGammaComp2040->AddEntry(histoGammaPurWOAddSig2040,"#epsilon_{pur}","p");
		legendGammaComp2040->AddEntry(histoGammaEffiWOAddSig2040,Form("#epsilon_{eff}, MC (w add Sig), #mu_{# TPC track} = %2.2e",meanNTPCTracksWAddSig2040),"p");
		legendGammaComp2040->Draw();
	
	canvasGamma2040->SaveAs(Form("%s/GammaCompSimple2040.%s",outputDir.Data(),suffix.Data()));
	delete canvasGamma2040;

	
	TCanvas* canvasMult4060 = new TCanvas("canvasMult4060","",200,10,700,500);  // gives the page size
	DrawGammaCanvasSettings( canvasMult4060,  0.12, 0.05, 0.05, 0.12);
	
  	canvasMult4060->SetLogy();
		histo2DMult->GetYaxis()->SetRangeUser(2.,5e6);
		histo2DMult->GetXaxis()->SetRangeUser(0.,3000.);
		histo2DMult->Draw("copy");
	
		DrawGammaSetMarker(histoNTPCTracksData4060,20,markerSizeComparison, kBlack , kBlack);
// 		histoNTPCTracksData4060->GetYaxis()->SetRangeUser(0.,histoNTPCTracksData4060->GetMaximum());
		histoNTPCTracksData4060->Draw("E1psame");
		DrawGammaSetMarker(histoNTPCTracksWOAddSig4060,21,markerSizeComparison, kRed+2 , kRed+2);
		histoNTPCTracksWOAddSig4060->Draw("E1psame");
		DrawGammaSetMarker(histoNTPCTracksWAddSig4060,22,markerSizeComparison, kBlue , kBlue);
		histoNTPCTracksWAddSig4060->Draw("E1psame");
// 
		TLatex *labelMult4060 = new TLatex(0.55,0.9,collisionSystemSemiPer.Data());
		SetStyleTLatex( labelMult4060, 0.035,4);
		labelMult4060->Draw();

		TLegend* legendMult4060 = new TLegend(0.13,0.8,0.3,0.93);
		legendMult4060->SetFillColor(0);
		legendMult4060->SetLineColor(0);
// 		legendMult4060->SetNColumns(2);
		legendMult4060->SetTextSize(0.03);
		legendMult4060->AddEntry(histoNTPCTracksData4060,Form("Data, #mu = %2.2e",meanNTPCTracksData4060),"p");
		legendMult4060->AddEntry(histoNTPCTracksWOAddSig4060,Form("MC (w\o add Sig), #mu = %2.2e",meanNTPCTracksWOAddSig4060),"p");
		legendMult4060->AddEntry(histoNTPCTracksWAddSig4060,Form("MC (w add Sig), #mu = %2.2e",meanNTPCTracksWAddSig4060),"p");
		legendMult4060->Draw();
	
	canvasMult4060->Update();
	canvasMult4060->Print(Form("%s/Mult4060.%s",outputDir.Data(),suffix.Data()));

	TCanvas* canvasEff4060 = new TCanvas("canvasEff4060","",200,10,1350,900);  // gives the page size
	DrawGammaCanvasSettings( canvasEff4060, 0.09, 0.02, 0.035, 0.09);
					
		DrawAutoGammaMesonHistos( histoEffiFitWAddSig4060, 
				"", "p_{T} (GeV/c)", "#pi^{0} efficiency fitted", 
				kTRUE, 1.5, 3e-6, kFALSE,
				kFALSE, 0., 0.7, 
				kTRUE, 0., 7.);
		DrawGammaSetMarker(histoEffiFinalFitted4060, 22, 1., kBlack,kBlack);	
		histoEffiFinalFitted4060->DrawCopy("e1,same"); 	
		DrawGammaSetMarker(histoEffiFitWAddSig4060, 20, 1., kRed-2, kRed-2);	
		histoEffiFitWAddSig4060->DrawCopy("e1,same"); 	
		DrawGammaSetMarker(histoEffiFitWOAddSig4060, 21, 1., kBlue-2, kBlue-2);	
		histoEffiFitWOAddSig4060->DrawCopy("e1,same"); 	
		
		TLegend* legendEffiComp4060 = new TLegend(0.53,0.13,0.93,0.3);
		legendEffiComp4060->SetFillColor(0);
		legendEffiComp4060->SetLineColor(0);
		legendEffiComp4060->SetTextSize(0.03);
		legendEffiComp4060->AddEntry(histoEffiFinalFitted4060,Form("MC merged, #mu_{# TPC track} = %2.2e",meanNTPCTracksFinal4060),"p");
		legendEffiComp4060->AddEntry(histoEffiFitWOAddSig4060,Form("MC (w\o add Sig), #mu_{# TPC track} = %2.2e",meanNTPCTracksWOAddSig4060),"p");
		legendEffiComp4060->AddEntry(histoEffiFitWAddSig4060,Form("MC (w add Sig), #mu_{# TPC track} = %2.2e",meanNTPCTracksWAddSig4060),"p");
		legendEffiComp4060->Draw();

	canvasEff4060->SaveAs(Form("%s/EffCompSimple4060.%s",outputDir.Data(),suffix.Data()));
	delete canvasEff4060;

	TCanvas* canvasEff4060All = new TCanvas("canvasEff4060All","",200,10,1350,900);  // gives the page size
	DrawGammaCanvasSettings( canvasEff4060All, 0.09, 0.02, 0.035, 0.09);
	// 	canvasEff4060All->SetLogy(1);	
						
		DrawAutoGammaMesonHistos( histoEffiFinal4060, 
				"", "p_{T} (GeV/c)", "#pi^{0} efficiency fitted", 
				kFALSE, 1.5, 3e-6, kFALSE,
				kFALSE, 0., 0.7, 
				kTRUE, 0., 7.);
				
		DrawGammaSetMarker(histoEffiFinal4060, 22, 1., kGreen+2, kGreen+2);	
		histoEffiFinal4060->DrawCopy("e1"); 	
// 		DrawGammaSetMarker(histoEffiFinalFitted4060, 22, 1., kBlack,kBlack);	
// 		histoEffiFinalFitted4060->DrawCopy("e1,same"); 	
// 		
		DrawGammaSetMarker(histoEffiWAddSig4060, 20, 1., kOrange+2, kOrange+2);	
		histoEffiWAddSig4060->DrawCopy("e1,same"); 	
// 		DrawGammaSetMarker(histoEffiFitWAddSig4060, 20, 1., kRed-2, kRed-2);	
// 		histoEffiFitWAddSig4060->DrawCopy("e1,same"); 	
// 		
		DrawGammaSetMarker(histoEffiWOAddSig4060, 21, 1., kViolet, kViolet);	
		histoEffiWOAddSig4060->DrawCopy("e1,same"); 	
// 		DrawGammaSetMarker(histoEffiFitWOAddSig4060, 21, 1., kBlue-2, kBlue-2);	
// 		histoEffiFitWOAddSig4060->DrawCopy("e1,same"); 	

		TLegend* legendEffiComp4060All = new TLegend(0.53,0.13,0.93,0.3);
		legendEffiComp4060All->SetFillColor(0);
		legendEffiComp4060All->SetLineColor(0);
		legendEffiComp4060All->SetNColumns(1);
		legendEffiComp4060All->SetTextSize(0.025);
		legendEffiComp4060All->AddEntry(histoEffiFinal4060,Form("MC merged #mu_{# TPC track} = %2.2e",meanNTPCTracksFinal4060),"p");
// 		legendEffiComp4060All->AddEntry(histoEffiFinalFitted4060,Form("MC merged, fitted, #mu_{# TPC track} = %2.2e",meanNTPCTracksFinal4060),"p");
		legendEffiComp4060All->AddEntry(histoEffiWOAddSig4060,Form("MC (w\o add Sig), #mu_{# TPC track} = %2.2e",meanNTPCTracksWOAddSig4060),"p");
// 		legendEffiComp4060All->AddEntry(histoEffiFitWOAddSig4060,Form("MC (w\o add Sig), fitted, #mu_{# TPC track} = %2.2e",meanNTPCTracksWOAddSig4060),"p");
		legendEffiComp4060All->AddEntry(histoEffiWAddSig4060,Form("MC (w add Sig), #mu_{# TPC track} = %2.2e",meanNTPCTracksWAddSig4060),"p");
// 		legendEffiComp4060All->AddEntry(histoEffiFitWAddSig4060,Form("MC (w add Sig), fitted, #mu_{# TPC track} = %2.2e",meanNTPCTracksWAddSig4060),"p");
		legendEffiComp4060All->Draw();
		
	canvasEff4060All->SaveAs(Form("%s/EffCompSimple4060All.%s",outputDir.Data(),suffix.Data()));
	delete canvasEff4060All;

	TCanvas* canvasGamma4060 = new TCanvas("canvasGamma4060","",200,10,1350,900);  // gives the page size
	DrawGammaCanvasSettings( canvasGamma4060, 0.09, 0.02, 0.035, 0.09);
// 	canvasGamma4060->SetLogy(1);	
					
		DrawAutoGammaMesonHistos( histoGammaEffi4060, 
				"", "p_{T} (GeV/c)", "#gamma #epsilon_{eff}", 
				kFALSE, 1.5, 3e-6, kFALSE,
				kTRUE, 0.1, 1., 
				kFALSE, 0., 10.);
				
		DrawGammaSetMarker(histoGammaEffi4060, 20, 1.5, kBlack,kBlack);	
		histoGammaEffi4060->DrawCopy("e1,same"); 	
		DrawGammaSetMarker(histoGammaEffiWAddSig4060, 21, 1.5, kRed-2, kRed-2);	
		histoGammaEffiWAddSig4060->DrawCopy("e1,same"); 	
		DrawGammaSetMarker(histoGammaEffiWOAddSig4060, 22, 1.5, kBlue-2, kBlue-2);	
		histoGammaEffiWOAddSig4060->DrawCopy("e1,same"); 	

// 		DrawGammaSetMarker(histoGammaPur4060, 24, 1.5, kBlack,kBlack);	
// 		histoGammaPur4060->DrawCopy("e1,same"); 	
// 		DrawGammaSetMarker(histoGammaPurWAddSig4060, 25, 1.5, kRed-2, kRed-2);	
// 		histoGammaPurWAddSig4060->DrawCopy("e1,same"); 	
// 		DrawGammaSetMarker(histoGammaPurWOAddSig4060, 26, 1.5, kBlue-2, kBlue-2);	
// 		histoGammaPurWOAddSig4060->DrawCopy("e1,same"); 	

		TLegend* legendGammaComp4060 = new TLegend(0.33,0.13,0.63,0.3);
		legendGammaComp4060->SetFillColor(0);
		legendGammaComp4060->SetLineColor(0);
		legendGammaComp4060->SetNColumns(1);
		legendGammaComp4060->SetTextSize(0.03);
// 		legendGammaComp4060->AddEntry(histoGammaPur4060,"#epsilon_{pur}","p");
		legendGammaComp4060->AddEntry(histoGammaEffi4060,Form("#epsilon_{eff}, MC merged, #mu_{# TPC track} = %2.2e",meanNTPCTracksFinal4060),"p");
// 		legendGammaComp4060->AddEntry(histoGammaPurWAddSig4060,"#epsilon_{pur}","p");
		legendGammaComp4060->AddEntry(histoGammaEffiWAddSig4060,Form("#epsilon_{eff}, MC (w\o add Sig), #mu_{# TPC track} = %2.2e",meanNTPCTracksWOAddSig4060),"p");
// 		legendGammaComp4060->AddEntry(histoGammaPurWOAddSig4060,"#epsilon_{pur}","p");
		legendGammaComp4060->AddEntry(histoGammaEffiWOAddSig4060,Form("#epsilon_{eff}, MC (w add Sig), #mu_{# TPC track} = %2.2e",meanNTPCTracksWAddSig4060),"p");
		legendGammaComp4060->Draw();
	
	canvasGamma4060->SaveAs(Form("%s/GammaCompSimple4060.%s",outputDir.Data(),suffix.Data()));
	delete canvasGamma4060;

	
	TCanvas* canvasMult6080 = new TCanvas("canvasMult6080","",200,10,700,500);  // gives the page size
	DrawGammaCanvasSettings( canvasMult6080,  0.12, 0.05, 0.05, 0.12);
	
  	canvasMult6080->SetLogy();
		histo2DMult->GetYaxis()->SetRangeUser(2.,5e6);
		histo2DMult->GetXaxis()->SetRangeUser(0.,3000.);
		histo2DMult->Draw("copy");
	
		DrawGammaSetMarker(histoNTPCTracksData6080,20,markerSizeComparison, kBlack , kBlack);
// 		histoNTPCTracksData6080->GetYaxis()->SetRangeUser(0.,histoNTPCTracksData6080->GetMaximum());
		histoNTPCTracksData6080->Draw("E1psame");
		DrawGammaSetMarker(histoNTPCTracksWOAddSig6080,21,markerSizeComparison, kRed+2 , kRed+2);
		histoNTPCTracksWOAddSig6080->Draw("E1psame");
		DrawGammaSetMarker(histoNTPCTracksWAddSig6080,22,markerSizeComparison, kBlue , kBlue);
		histoNTPCTracksWAddSig6080->Draw("E1psame");
// 
		TLatex *labelMult6080 = new TLatex(0.55,0.9,collisionSystemPer.Data());
		SetStyleTLatex( labelMult6080, 0.035,4);
		labelMult6080->Draw();

		TLegend* legendMult6080 = new TLegend(0.13,0.8,0.3,0.93);
		legendMult6080->SetFillColor(0);
		legendMult6080->SetLineColor(0);
// 		legendMult6080->SetNColumns(2);
		legendMult6080->SetTextSize(0.03);
		legendMult6080->AddEntry(histoNTPCTracksData6080,Form("Data, #mu = %2.2e",meanNTPCTracksData6080),"p");
		legendMult6080->AddEntry(histoNTPCTracksWOAddSig6080,Form("MC (w\o add Sig), #mu = %2.2e",meanNTPCTracksWOAddSig6080),"p");
		legendMult6080->AddEntry(histoNTPCTracksWAddSig6080,Form("MC (w add Sig), #mu = %2.2e",meanNTPCTracksWAddSig6080),"p");
		legendMult6080->Draw();
	
	canvasMult6080->Update();
	canvasMult6080->Print(Form("%s/Mult6080.%s",outputDir.Data(),suffix.Data()));

	TCanvas* canvasEff6080 = new TCanvas("canvasEff6080","",200,10,1350,900);  // gives the page size
	DrawGammaCanvasSettings( canvasEff6080, 0.09, 0.02, 0.035, 0.09);
					
		DrawAutoGammaMesonHistos( histoEffiFitWAddSig6080, 
				"", "p_{T} (GeV/c)", "#pi^{0} efficiency fitted", 
				kTRUE, 1.5, 3e-6, kFALSE,
				kFALSE, 0., 0.7, 
				kTRUE, 0., 7.);
		DrawGammaSetMarker(histoEffiFinalFitted6080, 22, 1., kBlack,kBlack);	
		histoEffiFinalFitted6080->DrawCopy("e1,same"); 	
		DrawGammaSetMarker(histoEffiFitWAddSig6080, 20, 1., kRed-2, kRed-2);	
		histoEffiFitWAddSig6080->DrawCopy("e1,same"); 	
		DrawGammaSetMarker(histoEffiFitWOAddSig6080, 21, 1., kBlue-2, kBlue-2);	
		histoEffiFitWOAddSig6080->DrawCopy("e1,same"); 	
		
		TLegend* legendEffiComp6080 = new TLegend(0.53,0.13,0.93,0.3);
		legendEffiComp6080->SetFillColor(0);
		legendEffiComp6080->SetLineColor(0);
		legendEffiComp6080->SetTextSize(0.03);
		legendEffiComp6080->AddEntry(histoEffiFinalFitted6080,Form("MC merged, #mu_{# TPC track} = %2.2e",meanNTPCTracksFinal6080),"p");
		legendEffiComp6080->AddEntry(histoEffiFitWOAddSig6080,Form("MC (w\o add Sig), #mu_{# TPC track} = %2.2e",meanNTPCTracksWOAddSig6080),"p");
		legendEffiComp6080->AddEntry(histoEffiFitWAddSig6080,Form("MC (w add Sig), #mu_{# TPC track} = %2.2e",meanNTPCTracksWAddSig6080),"p");
		legendEffiComp6080->Draw();
		
	canvasEff6080->SaveAs(Form("%s/EffCompSimple6080.%s",outputDir.Data(),suffix.Data()));
	delete canvasEff6080;

	TCanvas* canvasEff6080All = new TCanvas("canvasEff6080All","",200,10,1350,900);  // gives the page size
	DrawGammaCanvasSettings( canvasEff6080All, 0.09, 0.02, 0.035, 0.09);
	// 	canvasEff6080All->SetLogy(1);	
						
		DrawAutoGammaMesonHistos( histoEffiFinal6080, 
				"", "p_{T} (GeV/c)", "#pi^{0} efficiency fitted", 
				kFALSE, 1.5, 3e-6, kFALSE,
				kFALSE, 0., 0.7, 
				kTRUE, 0., 7.);
				
		DrawGammaSetMarker(histoEffiFinal6080, 22, 1., kGreen+2, kGreen+2);	
		histoEffiFinal6080->DrawCopy("e1"); 	
// 		DrawGammaSetMarker(histoEffiFinalFitted6080, 22, 1., kBlack,kBlack);	
// 		histoEffiFinalFitted6080->DrawCopy("e1,same"); 	
// 		
		DrawGammaSetMarker(histoEffiWAddSig6080, 20, 1., kOrange+2, kOrange+2);	
		histoEffiWAddSig6080->DrawCopy("e1,same"); 	
// 		DrawGammaSetMarker(histoEffiFitWAddSig6080, 20, 1., kRed-2, kRed-2);	
// 		histoEffiFitWAddSig6080->DrawCopy("e1,same"); 	
// 		
		DrawGammaSetMarker(histoEffiWOAddSig6080, 21, 1., kViolet, kViolet);	
		histoEffiWOAddSig6080->DrawCopy("e1,same"); 	
// 		DrawGammaSetMarker(histoEffiFitWOAddSig6080, 21, 1., kBlue-2, kBlue-2);	
// 		histoEffiFitWOAddSig6080->DrawCopy("e1,same"); 	

		TLegend* legendEffiComp6080All = new TLegend(0.53,0.13,0.93,0.3);
		legendEffiComp6080All->SetFillColor(0);
		legendEffiComp6080All->SetLineColor(0);
		legendEffiComp6080All->SetNColumns(1);
		legendEffiComp6080All->SetTextSize(0.025);
		legendEffiComp6080All->AddEntry(histoEffiFinal6080,Form("MC merged #mu_{# TPC track} = %2.2e",meanNTPCTracksFinal6080),"p");
// 		legendEffiComp6080All->AddEntry(histoEffiFinalFitted6080,Form("MC merged, fitted, #mu_{# TPC track} = %2.2e",meanNTPCTracksFinal6080),"p");
		legendEffiComp6080All->AddEntry(histoEffiWOAddSig6080,Form("MC (w\o add Sig), #mu_{# TPC track} = %2.2e",meanNTPCTracksWOAddSig6080),"p");
// 		legendEffiComp6080All->AddEntry(histoEffiFitWOAddSig6080,Form("MC (w\o add Sig), fitted, #mu_{# TPC track} = %2.2e",meanNTPCTracksWOAddSig6080),"p");
		legendEffiComp6080All->AddEntry(histoEffiWAddSig6080,Form("MC (w add Sig), #mu_{# TPC track} = %2.2e",meanNTPCTracksWAddSig6080),"p");
// 		legendEffiComp6080All->AddEntry(histoEffiFitWAddSig6080,Form("MC (w add Sig), fitted, #mu_{# TPC track} = %2.2e",meanNTPCTracksWAddSig6080),"p");
		legendEffiComp6080All->Draw();
		
	canvasEff6080All->SaveAs(Form("%s/EffCompSimple6080All.%s",outputDir.Data(),suffix.Data()));
	delete canvasEff6080All;

	
	TCanvas* canvasGamma6080 = new TCanvas("canvasGamma6080","",200,10,1350,900);  // gives the page size
	DrawGammaCanvasSettings( canvasGamma6080, 0.09, 0.02, 0.035, 0.09);
					
		DrawAutoGammaMesonHistos( histoGammaEffi6080, 
				"", "p_{T} (GeV/c)", "#gamma #epsilon_{eff}", 
				kFALSE, 1.5, 3e-6, kFALSE,
				kTRUE, 0.1, 1., 
				kFALSE, 0., 10.);
				
		DrawGammaSetMarker(histoGammaEffi6080, 20, 1.5, kBlack,kBlack);	
		histoGammaEffi6080->DrawCopy("e1,same"); 	
		DrawGammaSetMarker(histoGammaEffiWAddSig6080, 21, 1.5, kRed-2, kRed-2);	
		histoGammaEffiWAddSig6080->DrawCopy("e1,same"); 	
		DrawGammaSetMarker(histoGammaEffiWOAddSig6080, 22, 1.5, kBlue-2, kBlue-2);	
		histoGammaEffiWOAddSig6080->DrawCopy("e1,same"); 	

// 		DrawGammaSetMarker(histoGammaPur6080, 24, 1.5, kBlack,kBlack);	
// 		histoGammaPur6080->DrawCopy("e1,same"); 	
// 		DrawGammaSetMarker(histoGammaPurWAddSig6080, 25, 1.5, kRed-2, kRed-2);	
// 		histoGammaPurWAddSig6080->DrawCopy("e1,same"); 	
// 		DrawGammaSetMarker(histoGammaPurWOAddSig6080, 26, 1.5, kBlue-2, kBlue-2);	
// 		histoGammaPurWOAddSig6080->DrawCopy("e1,same"); 	

		TLegend* legendGammaComp6080 = new TLegend(0.33,0.13,0.63,0.3);
		legendGammaComp6080->SetFillColor(0);
		legendGammaComp6080->SetLineColor(0);
		legendGammaComp6080->SetNColumns(2);
		legendGammaComp6080->SetTextSize(0.03);
		legendGammaComp6080->AddEntry(histoGammaPur6080,"#epsilon_{pur}","p");
// 		legendGammaComp6080->AddEntry(histoGammaEffi6080,Form("#epsilon_{eff}, MC merged, #mu_{# TPC track} = %2.2e",meanNTPCTracksFinal6080),"p");
		legendGammaComp6080->AddEntry(histoGammaPurWAddSig6080,"#epsilon_{pur}","p");
// 		legendGammaComp6080->AddEntry(histoGammaEffiWAddSig6080,Form("#epsilon_{eff}, MC (w\o add Sig), #mu_{# TPC track} = %2.2e",meanNTPCTracksWOAddSig6080),"p");
		legendGammaComp6080->AddEntry(histoGammaPurWOAddSig6080,"#epsilon_{pur}","p");
// 		legendGammaComp6080->AddEntry(histoGammaEffiWOAddSig6080,Form("#epsilon_{eff}, MC (w add Sig), #mu_{# TPC track} = %2.2e",meanNTPCTracksWAddSig6080),"p");
		legendGammaComp6080->Draw();
	
	canvasGamma6080->SaveAs(Form("%s/GammaCompSimple6080.%s",outputDir.Data(),suffix.Data()));
	delete canvasGamma6080;

	
	TCanvas* canvasEffAllCent = new TCanvas("canvasEffAllCent","",200,10,1350,1350);  // gives the page size
	DrawGammaCanvasSettings( canvasEffAllCent, 0.1, 0.02, 0.035, 0.09);
		TH2F * histo2DEffAllCent;
		histo2DEffAllCent = new TH2F("histo2DEffAllCent","histo2DEffAllCent",1000,0,8.,2000,0.e-3,2.e-3	);
		histo2DEffAllCent->GetXaxis()->SetRangeUser(0.,12.);
		SetStyleHistoTH2ForGraphs(histo2DEffAllCent, "p_{T} (GeV/c)","#pi^{0} efficiency",0.03,0.04, 0.03,0.04, 1.,1.);
		histo2DEffAllCent->Draw("copy");

		DrawGammaSetMarker(histoEffiFinalFitted6080, markerStyleCommmonSpectrum6080, markerSizeCommonSpectrum6080, colorComb6080, colorComb6080);	
		histoEffiFinalFitted6080->DrawCopy("e1,same"); 	
		DrawGammaSetMarker(histoEffiFinalFitted0005, markerStyleCommmonSpectrum0005, markerSizeCommonSpectrum0005, colorComb0005, colorComb0005);	
		histoEffiFinalFitted0005->DrawCopy("e1,same"); 	
		DrawGammaSetMarker(histoEffiFinalFitted0510, markerStyleCommmonSpectrum0510, markerSizeCommonSpectrum0510, colorComb0510, colorComb0510);	
		histoEffiFinalFitted0510->DrawCopy("e1,same"); 	
		DrawGammaSetMarker(histoEffiFinalFitted1020, markerStyleCommmonSpectrum1020, markerSizeCommonSpectrum1020, colorComb1020, colorComb1020);	
		histoEffiFinalFitted1020->DrawCopy("e1,same"); 	
		DrawGammaSetMarker(histoEffiFinalFitted2040, markerStyleCommmonSpectrum2040, markerSizeCommonSpectrum2040, colorComb2040, colorComb2040);	
		histoEffiFinalFitted2040->DrawCopy("e1,same"); 	
		DrawGammaSetMarker(histoEffiFinalFitted4060, markerStyleCommmonSpectrum4060, markerSizeCommonSpectrum4060, colorComb4060, colorComb4060);	
		histoEffiFinalFitted4060->DrawCopy("e1,same"); 	

		TLegend* legendEffiCompAllCent = new TLegend(0.4,0.13,0.93,0.4);
		legendEffiCompAllCent->SetFillColor(0);
		legendEffiCompAllCent->SetLineColor(0);
		legendEffiCompAllCent->SetTextSize(0.03);
		legendEffiCompAllCent->AddEntry(histoEffiFinalFitted0005,Form("MC merged, #mu_{# TPC track} = %2.2e",meanNTPCTracksFinal0005),"p");
		legendEffiCompAllCent->AddEntry(histoEffiFinalFitted0510,Form("MC merged, #mu_{# TPC track} = %2.2e",meanNTPCTracksFinal0510),"p");
		legendEffiCompAllCent->AddEntry(histoEffiFinalFitted1020,Form("MC merged, #mu_{# TPC track} = %2.2e",meanNTPCTracksFinal1020),"p");
		legendEffiCompAllCent->AddEntry(histoEffiFinalFitted2040,Form("MC merged, #mu_{# TPC track} = %2.2e",meanNTPCTracksFinal2040),"p");
		legendEffiCompAllCent->AddEntry(histoEffiFinalFitted4060,Form("MC merged, #mu_{# TPC track} = %2.2e",meanNTPCTracksFinal4060),"p");
		legendEffiCompAllCent->AddEntry(histoEffiFinalFitted6080,Form("MC merged, #mu_{# TPC track} = %2.2e",meanNTPCTracksFinal6080),"p");
		legendEffiCompAllCent->Draw();
	
	canvasEffAllCent->SaveAs(Form("%s/EffCompSimpleAllCent.%s",outputDir.Data(),suffix.Data()));
	delete canvasEffAllCent;

// 	TCanvas* canvasEffGammaAllCent = new TCanvas("canvasEffGammaAllCent","",200,10,1350,1350);  // gives the page size
// 	DrawGammaCanvasSettings( canvasEffGammaAllCent, 0.1, 0.02, 0.035, 0.09);
// 	TH2F * histo2DEffGammaAllCent;
// 	histo2DEffGammaAllCent = new TH2F("histo2DEffGammaAllCent","histo2DEffGammaAllCent",1000,0,12.,2000,0.2,0.8);
// 	histo2DEffGammaAllCent->GetXaxis()->SetRangeUser(0.,12.);
// 	SetStyleHistoTH2ForGraphs(histo2DEffGammaAllCent, "p_{T} (GeV/c)","#gamma efficiency",0.03,0.04, 0.03,0.04, 1.,1.);
// 	histo2DEffGammaAllCent->Draw("copy");
// 
// 	DrawGammaSetMarker(histoGammaEffi6080, markerStyleCommmonSpectrum6080, markerSizeCommonSpectrum6080, colorComb6080, colorComb6080);	
// 	histoGammaEffi6080->DrawCopy("e1,same"); 	
// 	DrawGammaSetMarker(histoGammaEffi0005, markerStyleCommmonSpectrum0005, markerSizeCommonSpectrum0005, colorComb0005, colorComb0005);	
// 	histoGammaEffi0005->DrawCopy("e1,same"); 	
// 	DrawGammaSetMarker(histoGammaEffi0510, markerStyleCommmonSpectrum0510, markerSizeCommonSpectrum0510, colorComb0510, colorComb0510);	
// 	histoGammaEffi0510->DrawCopy("e1,same"); 	
// 	DrawGammaSetMarker(histoGammaEffi1020, markerStyleCommmonSpectrum1020, markerSizeCommonSpectrum1020, colorComb1020, colorComb1020);	
// 	histoGammaEffi1020->DrawCopy("e1,same"); 	
// 	DrawGammaSetMarker(histoGammaEffi2040, markerStyleCommmonSpectrum2040, markerSizeCommonSpectrum2040, colorComb2040, colorComb2040);	
// 	histoGammaEffi2040->DrawCopy("e1,same"); 	
// 	DrawGammaSetMarker(histoGammaEffi4060, markerStyleCommmonSpectrum4060, markerSizeCommonSpectrum4060, colorComb4060, colorComb4060);	
// 	histoGammaEffi4060->DrawCopy("e1,same"); 	
// 
// 	TLegend* legendEffiGammaAllCent = new TLegend(0.4,0.72,0.93,0.96);
// 	legendEffiGammaAllCent->SetFillColor(0);
// 	legendEffiGammaAllCent->SetLineColor(0);
// 	legendEffiGammaAllCent->SetTextSize(0.03);
// 	legendEffiGammaAllCent->AddEntry(histoGammaEffi0005,Form("MC merged, #mu_{# TPC track} = %2.2e",meanNTPCTracksFinal0005),"p");
// 	legendEffiGammaAllCent->AddEntry(histoGammaEffi0510,Form("MC merged, #mu_{# TPC track} = %2.2e",meanNTPCTracksFinal0510),"p");
// 	legendEffiGammaAllCent->AddEntry(histoGammaEffi1020,Form("MC merged, #mu_{# TPC track} = %2.2e",meanNTPCTracksFinal1020),"p");
// 	legendEffiGammaAllCent->AddEntry(histoGammaEffi2040,Form("MC merged, #mu_{# TPC track} = %2.2e",meanNTPCTracksFinal2040),"p");
// 	legendEffiGammaAllCent->AddEntry(histoGammaEffi4060,Form("MC merged, #mu_{# TPC track} = %2.2e",meanNTPCTracksFinal4060),"p");
// 	legendEffiGammaAllCent->AddEntry(histoGammaEffi6080,Form("MC merged, #mu_{# TPC track} = %2.2e",meanNTPCTracksFinal6080),"p");
// 	legendEffiGammaAllCent->Draw();
// 	
// 	canvasEffGammaAllCent->SaveAs(Form("%s/EffGammaSimpleAllCent.%s",outputDir.Data(),suffix.Data()));
// 	delete canvasEffGammaAllCent;

	TCanvas* canvasEffGammaMinBiasAllCent = new TCanvas("canvasEffGammaMinBiasAllCent","",200,10,1350,1350);  // gives the page size
	DrawGammaCanvasSettings( canvasEffGammaMinBiasAllCent, 0.1, 0.02, 0.035, 0.09);
	TH2F * histo2DEffGammaMinBiasAllCent;
	histo2DEffGammaMinBiasAllCent = new TH2F("histo2DEffGammaMinBiasAllCent","histo2DEffGammaMinBiasAllCent",1000,0,12.,2000,0.2,0.8);
	histo2DEffGammaMinBiasAllCent->GetXaxis()->SetRangeUser(0.,12.);
	SetStyleHistoTH2ForGraphs(histo2DEffGammaMinBiasAllCent, "p_{T} (GeV/c)","#gamma efficiency",0.03,0.04, 0.03,0.04, 1.,1.);
	histo2DEffGammaMinBiasAllCent->Draw("copy");

	DrawGammaSetMarker(histoGammaEffiWOAddSig6080, markerStyleCommmonSpectrum6080, markerSizeCommonSpectrum6080, colorComb6080, colorComb6080);	
	histoGammaEffiWOAddSig6080->DrawCopy("e1,same"); 	
	DrawGammaSetMarker(histoGammaEffiWOAddSig0005, markerStyleCommmonSpectrum0005, markerSizeCommonSpectrum0005, colorComb0005, colorComb0005);	
	histoGammaEffiWOAddSig0005->DrawCopy("e1,same"); 	
	DrawGammaSetMarker(histoGammaEffiWOAddSig0510, markerStyleCommmonSpectrum0510, markerSizeCommonSpectrum0510, colorComb0510, colorComb0510);	
	histoGammaEffiWOAddSig0510->DrawCopy("e1,same"); 	
	DrawGammaSetMarker(histoGammaEffiWOAddSig1020, markerStyleCommmonSpectrum1020, markerSizeCommonSpectrum1020, colorComb1020, colorComb1020);	
	histoGammaEffiWOAddSig1020->DrawCopy("e1,same"); 	
	DrawGammaSetMarker(histoGammaEffiWOAddSig2040, markerStyleCommmonSpectrum2040, markerSizeCommonSpectrum2040, colorComb2040, colorComb2040);	
	histoGammaEffiWOAddSig2040->DrawCopy("e1,same"); 	
	DrawGammaSetMarker(histoGammaEffiWOAddSig4060, markerStyleCommmonSpectrum4060, markerSizeCommonSpectrum4060, colorComb4060, colorComb4060);	
	histoGammaEffiWOAddSig4060->DrawCopy("e1,same"); 	

	TLegend* legendEffGammaMinBiasAllCent = new TLegend(0.35,0.72,0.93,0.96);
	legendEffGammaMinBiasAllCent->SetFillColor(0);
	legendEffGammaMinBiasAllCent->SetLineColor(0);
	legendEffGammaMinBiasAllCent->SetTextSize(0.03);
	legendEffGammaMinBiasAllCent->AddEntry(histoGammaEffiWOAddSig0005,Form("MC wo add sig, #mu_{# TPC track} = %2.2e",meanNTPCTracksWOAddSig0005),"p");
	legendEffGammaMinBiasAllCent->AddEntry(histoGammaEffiWOAddSig0510,Form("MC wo add sig, #mu_{# TPC track} = %2.2e",meanNTPCTracksWOAddSig0510),"p");
	legendEffGammaMinBiasAllCent->AddEntry(histoGammaEffiWOAddSig1020,Form("MC wo add sig, #mu_{# TPC track} = %2.2e",meanNTPCTracksWOAddSig1020),"p");
	legendEffGammaMinBiasAllCent->AddEntry(histoGammaEffiWOAddSig2040,Form("MC wo add sig, #mu_{# TPC track} = %2.2e",meanNTPCTracksWOAddSig2040),"p");
	legendEffGammaMinBiasAllCent->AddEntry(histoGammaEffiWOAddSig4060,Form("MC wo add sig, #mu_{# TPC track} = %2.2e",meanNTPCTracksWOAddSig4060),"p");
	legendEffGammaMinBiasAllCent->AddEntry(histoGammaEffiWOAddSig6080,Form("MC wo add sig, #mu_{# TPC track} = %2.2e",meanNTPCTracksWOAddSig6080),"p");
	legendEffGammaMinBiasAllCent->Draw();
	
	canvasEffGammaMinBiasAllCent->SaveAs(Form("%s/EffGammaMinBiasSimpleAllCent.%s",outputDir.Data(),suffix.Data()));
	delete canvasEffGammaMinBiasAllCent;

// 	TCanvas* canvasPurGammaAllCent = new TCanvas("canvasPurGammaAllCent","",200,10,1350,1350);  // gives the page size
// 	DrawGammaCanvasSettings( canvasPurGammaAllCent, 0.1, 0.02, 0.035, 0.09);
// 	TH2F * histo2DPurGammaAllCent;
// 	histo2DPurGammaAllCent = new TH2F("histo2DPurGammaAllCent","histo2DPurGammaAllCent",1000,0,12.,2000,0.8,1.);
// 	histo2DPurGammaAllCent->GetXaxis()->SetRangeUser(0.,12.);
// 	SetStyleHistoTH2ForGraphs(histo2DPurGammaAllCent, "p_{T} (GeV/c)","#gamma purity",0.03,0.04, 0.03,0.04, 1.,1.3);
// 	histo2DPurGammaAllCent->Draw("copy");
// 
// 	DrawGammaSetMarker(histoGammaPur6080, markerStyleCommmonSpectrum6080, markerSizeCommonSpectrum6080, colorComb6080, colorComb6080);	
// 	histoGammaPur6080->DrawCopy("e1,same"); 	
// 	DrawGammaSetMarker(histoGammaPur0005, markerStyleCommmonSpectrum0005, markerSizeCommonSpectrum0005, colorComb0005, colorComb0005);	
// 	histoGammaPur0005->DrawCopy("e1,same"); 	
// 	DrawGammaSetMarker(histoGammaPur0510, markerStyleCommmonSpectrum0510, markerSizeCommonSpectrum0510, colorComb0510, colorComb0510);	
// 	histoGammaPur0510->DrawCopy("e1,same"); 	
// 	DrawGammaSetMarker(histoGammaPur1020, markerStyleCommmonSpectrum1020, markerSizeCommonSpectrum1020, colorComb1020, colorComb1020);	
// 	histoGammaPur1020->DrawCopy("e1,same"); 	
// 	DrawGammaSetMarker(histoGammaPur2040, markerStyleCommmonSpectrum2040, markerSizeCommonSpectrum2040, colorComb2040, colorComb2040);	
// 	histoGammaPur2040->DrawCopy("e1,same"); 	
// 	DrawGammaSetMarker(histoGammaPur4060, markerStyleCommmonSpectrum4060, markerSizeCommonSpectrum4060, colorComb4060, colorComb4060);	
// 	histoGammaPur4060->DrawCopy("e1,same"); 	
// 
// 	TLegend* legendPurGammaAllCent = new TLegend(0.4,0.13,0.93,0.38);
// 	legendPurGammaAllCent->SetFillColor(0);
// 	legendPurGammaAllCent->SetLineColor(0);
// 	legendPurGammaAllCent->SetTextSize(0.03);
// 	legendPurGammaAllCent->AddEntry(histoGammaPur0005,Form("MC merged, #mu_{# TPC track} = %2.2e",meanNTPCTracksFinal0005),"p");
// 	legendPurGammaAllCent->AddEntry(histoGammaPur0510,Form("MC merged, #mu_{# TPC track} = %2.2e",meanNTPCTracksFinal0510),"p");
// 	legendPurGammaAllCent->AddEntry(histoGammaPur1020,Form("MC merged, #mu_{# TPC track} = %2.2e",meanNTPCTracksFinal1020),"p");
// 	legendPurGammaAllCent->AddEntry(histoGammaPur2040,Form("MC merged, #mu_{# TPC track} = %2.2e",meanNTPCTracksFinal2040),"p");
// 	legendPurGammaAllCent->AddEntry(histoGammaPur4060,Form("MC merged, #mu_{# TPC track} = %2.2e",meanNTPCTracksFinal4060),"p");
// 	legendPurGammaAllCent->AddEntry(histoGammaPur6080,Form("MC merged, #mu_{# TPC track} = %2.2e",meanNTPCTracksFinal6080),"p");
// 	legendPurGammaAllCent->Draw();
// 	
// 	canvasPurGammaAllCent->SaveAs(Form("%s/PurityGammaSimpleAllCent.%s",outputDir.Data(),suffix.Data()));
// 	delete canvasPurGammaAllCent;

	TCanvas* canvasPurGammaMinBiasAllCent = new TCanvas("canvasPurGammaMinBiasAllCent","",200,10,1350,1350);  // gives the page size
	DrawGammaCanvasSettings( canvasPurGammaMinBiasAllCent, 0.1, 0.02, 0.035, 0.09);
	TH2F * histo2DPurGammaMinBiasAllCent;
	histo2DPurGammaMinBiasAllCent = new TH2F("histo2DPurGammaMinBiasAllCent","histo2DPurGammaMinBiasAllCent",1000,0,12.,2000,0.8,1.);
	histo2DPurGammaMinBiasAllCent->GetXaxis()->SetRangeUser(0.,12.);
	SetStyleHistoTH2ForGraphs(histo2DPurGammaMinBiasAllCent, "p_{T} (GeV/c)","#gamma purity",0.03,0.04, 0.03,0.04, 1.,1.3);
	histo2DPurGammaMinBiasAllCent->Draw("copy");

	DrawGammaSetMarker(histoGammaPurWOAddSig6080, markerStyleCommmonSpectrum6080, markerSizeCommonSpectrum6080, colorComb6080, colorComb6080);	
	histoGammaPurWOAddSig6080->DrawCopy("e1,same"); 	
	DrawGammaSetMarker(histoGammaPurWOAddSig0005, markerStyleCommmonSpectrum0005, markerSizeCommonSpectrum0005, colorComb0005, colorComb0005);	
	histoGammaPurWOAddSig0005->DrawCopy("e1,same"); 	
	DrawGammaSetMarker(histoGammaPurWOAddSig0510, markerStyleCommmonSpectrum0510, markerSizeCommonSpectrum0510, colorComb0510, colorComb0510);	
	histoGammaPurWOAddSig0510->DrawCopy("e1,same"); 	
	DrawGammaSetMarker(histoGammaPurWOAddSig1020, markerStyleCommmonSpectrum1020, markerSizeCommonSpectrum1020, colorComb1020, colorComb1020);	
	histoGammaPurWOAddSig1020->DrawCopy("e1,same"); 	
	DrawGammaSetMarker(histoGammaPurWOAddSig2040, markerStyleCommmonSpectrum2040, markerSizeCommonSpectrum2040, colorComb2040, colorComb2040);	
	histoGammaPurWOAddSig2040->DrawCopy("e1,same"); 	
	DrawGammaSetMarker(histoGammaPurWOAddSig4060, markerStyleCommmonSpectrum4060, markerSizeCommonSpectrum4060, colorComb4060, colorComb4060);	
	histoGammaPurWOAddSig4060->DrawCopy("e1,same"); 	

	TLegend* legendPurGammaMinBiasAllCent = new TLegend(0.35,0.13,0.93,0.38);
	legendPurGammaMinBiasAllCent->SetFillColor(0);
	legendPurGammaMinBiasAllCent->SetLineColor(0);
	legendPurGammaMinBiasAllCent->SetTextSize(0.03);
	legendPurGammaMinBiasAllCent->AddEntry(histoGammaPurWOAddSig0005,Form("MC wo add sig, #mu_{# TPC track} = %2.2e",meanNTPCTracksWOAddSig0005),"p");
	legendPurGammaMinBiasAllCent->AddEntry(histoGammaPurWOAddSig0510,Form("MC wo add sig, #mu_{# TPC track} = %2.2e",meanNTPCTracksWOAddSig0510),"p");
	legendPurGammaMinBiasAllCent->AddEntry(histoGammaPurWOAddSig1020,Form("MC wo add sig, #mu_{# TPC track} = %2.2e",meanNTPCTracksWOAddSig1020),"p");
	legendPurGammaMinBiasAllCent->AddEntry(histoGammaPurWOAddSig2040,Form("MC wo add sig, #mu_{# TPC track} = %2.2e",meanNTPCTracksWOAddSig2040),"p");
	legendPurGammaMinBiasAllCent->AddEntry(histoGammaPurWOAddSig4060,Form("MC wo add sig, #mu_{# TPC track} = %2.2e",meanNTPCTracksWOAddSig4060),"p");
	legendPurGammaMinBiasAllCent->AddEntry(histoGammaPurWOAddSig6080,Form("MC wo add sig, #mu_{# TPC track} = %2.2e",meanNTPCTracksWOAddSig6080),"p");
	legendPurGammaMinBiasAllCent->Draw();
	
	canvasPurGammaMinBiasAllCent->SaveAs(Form("%s/PurityGammaSimpleAllCentMinBias.%s",outputDir.Data(),suffix.Data()));
	delete canvasPurGammaMinBiasAllCent;

	TGraphAsymmErrors* graphEfficienciesMerged = new TGraphAsymmErrors(6);
	graphEfficienciesMerged->SetPoint(0, meanNTPCTracksFinal6080,  histoEffiFinalFitted6080->GetBinContent(histoEffiFinalFitted6080->GetNbinsX()));
	graphEfficienciesMerged->SetPointError(0, histoNTPCTracksFinal6080->GetRMS(), histoNTPCTracksFinal6080->GetRMS(), histoEffiFinalFitted6080->GetBinError(histoEffiFinalFitted6080->GetNbinsX()), histoEffiFinalFitted6080->GetBinError(histoEffiFinalFitted6080->GetNbinsX()));
	graphEfficienciesMerged->SetPoint(1, meanNTPCTracksFinal4060,  histoEffiFinalFitted4060->GetBinContent(histoEffiFinalFitted4060->GetNbinsX()));
	graphEfficienciesMerged->SetPointError(1, histoNTPCTracksFinal4060->GetRMS(), histoNTPCTracksFinal4060->GetRMS(), histoEffiFinalFitted4060->GetBinError(histoEffiFinalFitted4060->GetNbinsX()), histoEffiFinalFitted4060->GetBinError(histoEffiFinalFitted4060->GetNbinsX()));
	graphEfficienciesMerged->SetPoint(2, meanNTPCTracksFinal2040,  histoEffiFinalFitted2040->GetBinContent(histoEffiFinalFitted2040->GetNbinsX()));
	graphEfficienciesMerged->SetPointError(2, histoNTPCTracksFinal2040->GetRMS(), histoNTPCTracksFinal2040->GetRMS(), histoEffiFinalFitted2040->GetBinError(histoEffiFinalFitted2040->GetNbinsX()), histoEffiFinalFitted2040->GetBinError(histoEffiFinalFitted2040->GetNbinsX()));
	graphEfficienciesMerged->SetPoint(3, meanNTPCTracksFinal1020,  histoEffiFinalFitted1020->GetBinContent(histoEffiFinalFitted1020->GetNbinsX()));
	graphEfficienciesMerged->SetPointError(3, histoNTPCTracksFinal1020->GetRMS(), histoNTPCTracksFinal1020->GetRMS(), histoEffiFinalFitted1020->GetBinError(histoEffiFinalFitted1020->GetNbinsX()), histoEffiFinalFitted1020->GetBinError(histoEffiFinalFitted1020->GetNbinsX()));
	graphEfficienciesMerged->SetPoint(4, meanNTPCTracksFinal0510,  histoEffiFinalFitted0510->GetBinContent(histoEffiFinalFitted0510->GetNbinsX()));
	graphEfficienciesMerged->SetPointError(4, histoNTPCTracksFinal0510->GetRMS(), histoNTPCTracksFinal0510->GetRMS(), histoEffiFinalFitted0510->GetBinError(histoEffiFinalFitted0510->GetNbinsX()), histoEffiFinalFitted0510->GetBinError(histoEffiFinalFitted0510->GetNbinsX()));
	graphEfficienciesMerged->SetPoint(5, meanNTPCTracksFinal0005,  histoEffiFinalFitted0005->GetBinContent(histoEffiFinalFitted0005->GetNbinsX()));
	graphEfficienciesMerged->SetPointError(5, histoNTPCTracksFinal0005->GetRMS(), histoNTPCTracksFinal0005->GetRMS(), histoEffiFinalFitted0005->GetBinError(histoEffiFinalFitted0005->GetNbinsX()), histoEffiFinalFitted0005->GetBinError(histoEffiFinalFitted0005->GetNbinsX()));

	graphEfficienciesMerged->Print();

	TGraphAsymmErrors* graphEfficienciesWOAddSig = new TGraphAsymmErrors(6);
	graphEfficienciesWOAddSig->SetPoint(0, meanNTPCTracksWOAddSig6080,  histoEffiFitWOAddSig6080->GetBinContent(histoEffiFitWOAddSig6080->GetNbinsX()));
	graphEfficienciesWOAddSig->SetPointError(0, histoNTPCTracksWOAddSig6080->GetRMS(), histoNTPCTracksWOAddSig6080->GetRMS(), histoEffiFitWOAddSig6080->GetBinError(histoEffiFitWOAddSig6080->GetNbinsX()), histoEffiFitWOAddSig6080->GetBinError(histoEffiFitWOAddSig6080->GetNbinsX()));
	graphEfficienciesWOAddSig->SetPoint(1, meanNTPCTracksWOAddSig4060,  histoEffiFitWOAddSig4060->GetBinContent(histoEffiFitWOAddSig4060->GetNbinsX()));
	graphEfficienciesWOAddSig->SetPointError(1, histoNTPCTracksWOAddSig4060->GetRMS(), histoNTPCTracksWOAddSig4060->GetRMS(), histoEffiFitWOAddSig4060->GetBinError(histoEffiFitWOAddSig4060->GetNbinsX()), histoEffiFitWOAddSig4060->GetBinError(histoEffiFitWOAddSig4060->GetNbinsX()));
	graphEfficienciesWOAddSig->SetPoint(2, meanNTPCTracksWOAddSig2040,  histoEffiFitWOAddSig2040->GetBinContent(histoEffiFitWOAddSig2040->GetNbinsX()));
	graphEfficienciesWOAddSig->SetPointError(2, histoNTPCTracksWOAddSig2040->GetRMS(), histoNTPCTracksWOAddSig2040->GetRMS(), histoEffiFitWOAddSig2040->GetBinError(histoEffiFitWOAddSig2040->GetNbinsX()), histoEffiFitWOAddSig2040->GetBinError(histoEffiFitWOAddSig2040->GetNbinsX()));
	graphEfficienciesWOAddSig->SetPoint(3, meanNTPCTracksWOAddSig1020,  histoEffiFitWOAddSig1020->GetBinContent(histoEffiFitWOAddSig1020->GetNbinsX()));
	graphEfficienciesWOAddSig->SetPointError(3, histoNTPCTracksWOAddSig1020->GetRMS(), histoNTPCTracksWOAddSig1020->GetRMS(), histoEffiFitWOAddSig1020->GetBinError(histoEffiFitWOAddSig1020->GetNbinsX()), histoEffiFitWOAddSig1020->GetBinError(histoEffiFitWOAddSig1020->GetNbinsX()));
	graphEfficienciesWOAddSig->SetPoint(4, meanNTPCTracksWOAddSig0510,  histoEffiFitWOAddSig0510->GetBinContent(histoEffiFitWOAddSig0510->GetNbinsX()));
	graphEfficienciesWOAddSig->SetPointError(4, histoNTPCTracksWOAddSig0510->GetRMS(), histoNTPCTracksWOAddSig0510->GetRMS(), histoEffiFitWOAddSig0510->GetBinError(histoEffiFitWOAddSig0510->GetNbinsX()), histoEffiFitWOAddSig0510->GetBinError(histoEffiFitWOAddSig0510->GetNbinsX()));
	graphEfficienciesWOAddSig->SetPoint(5, meanNTPCTracksWOAddSig0005,  histoEffiFitWOAddSig0005->GetBinContent(histoEffiFitWOAddSig0005->GetNbinsX()));
	graphEfficienciesWOAddSig->SetPointError(5, histoNTPCTracksWOAddSig0005->GetRMS(), histoNTPCTracksWOAddSig0005->GetRMS(), histoEffiFitWOAddSig0005->GetBinError(histoEffiFitWOAddSig0005->GetNbinsX()), histoEffiFitWOAddSig0005->GetBinError(histoEffiFitWOAddSig0005->GetNbinsX()));
	graphEfficienciesWOAddSig->Print();

	TGraphAsymmErrors* graphEfficienciesWAddSig = new TGraphAsymmErrors(6);
	graphEfficienciesWAddSig->SetPoint(0, meanNTPCTracksWAddSig6080,  histoEffiFitWAddSig6080->GetBinContent(histoEffiFitWAddSig6080->GetNbinsX()));
	graphEfficienciesWAddSig->SetPointError(0, histoNTPCTracksWAddSig6080->GetRMS(), histoNTPCTracksWAddSig6080->GetRMS(), histoEffiFitWAddSig6080->GetBinError(histoEffiFitWAddSig6080->GetNbinsX()), histoEffiFitWAddSig6080->GetBinError(histoEffiFitWAddSig6080->GetNbinsX()));
	graphEfficienciesWAddSig->SetPoint(1, meanNTPCTracksWAddSig4060,  histoEffiFitWAddSig4060->GetBinContent(histoEffiFitWAddSig4060->GetNbinsX()));
	graphEfficienciesWAddSig->SetPointError(1, histoNTPCTracksWAddSig4060->GetRMS(), histoNTPCTracksWAddSig4060->GetRMS(), histoEffiFitWAddSig4060->GetBinError(histoEffiFitWAddSig4060->GetNbinsX()), histoEffiFitWAddSig4060->GetBinError(histoEffiFitWAddSig4060->GetNbinsX()));
	graphEfficienciesWAddSig->SetPoint(2, meanNTPCTracksWAddSig2040,  histoEffiFitWAddSig2040->GetBinContent(histoEffiFitWAddSig2040->GetNbinsX()));
	graphEfficienciesWAddSig->SetPointError(2, histoNTPCTracksWAddSig2040->GetRMS(), histoNTPCTracksWAddSig2040->GetRMS(), histoEffiFitWAddSig2040->GetBinError(histoEffiFitWAddSig2040->GetNbinsX()), histoEffiFitWAddSig2040->GetBinError(histoEffiFitWAddSig2040->GetNbinsX()));
	graphEfficienciesWAddSig->SetPoint(3, meanNTPCTracksWAddSig1020,  histoEffiFitWAddSig1020->GetBinContent(histoEffiFitWAddSig1020->GetNbinsX()));
	graphEfficienciesWAddSig->SetPointError(3, histoNTPCTracksWAddSig1020->GetRMS(), histoNTPCTracksWAddSig1020->GetRMS(), histoEffiFitWAddSig1020->GetBinError(histoEffiFitWAddSig1020->GetNbinsX()), histoEffiFitWAddSig1020->GetBinError(histoEffiFitWAddSig1020->GetNbinsX()));
	graphEfficienciesWAddSig->SetPoint(4, meanNTPCTracksWAddSig0510,  histoEffiFitWAddSig0510->GetBinContent(histoEffiFitWAddSig0510->GetNbinsX()));
	graphEfficienciesWAddSig->SetPointError(4, histoNTPCTracksWAddSig0510->GetRMS(), histoNTPCTracksWAddSig0510->GetRMS(), histoEffiFitWAddSig0510->GetBinError(histoEffiFitWAddSig0510->GetNbinsX()), histoEffiFitWAddSig0510->GetBinError(histoEffiFitWAddSig0510->GetNbinsX()));
	graphEfficienciesWAddSig->SetPoint(5, meanNTPCTracksWAddSig0005,  histoEffiFitWAddSig0005->GetBinContent(histoEffiFitWAddSig0005->GetNbinsX()));
	graphEfficienciesWAddSig->SetPointError(5, histoNTPCTracksWAddSig0005->GetRMS(), histoNTPCTracksWAddSig0005->GetRMS(), histoEffiFitWAddSig0005->GetBinError(histoEffiFitWAddSig0005->GetNbinsX()), histoEffiFitWAddSig0005->GetBinError(histoEffiFitWAddSig0005->GetNbinsX()));
	graphEfficienciesWAddSig->Print();

	
	TCanvas* canvasEffiVsCent = new TCanvas("canvasEffiVsCent","",200,10,1350,900);  // gives the page size
	DrawGammaCanvasSettings( canvasEffiVsCent, 0.1, 0.04, 0.04, 0.09);
// 	canvasEffiVsCent->SetLogy();
	
	TH2F * histo2DEff;
	histo2DEff = new TH2F("histo2DEff","histo2DEff",1000,0,2100.,2000,1.e-3,2.e-3	);
	histo2DEff->GetXaxis()->SetRangeUser(0.,2100.);
	SetStyleHistoTH2ForGraphs(histo2DEff, "# TPC tracks","maximum efficiency",0.03,0.04, 0.03,0.04, 1.,1.);
	histo2DEff->Draw("copy");

	DrawGammaSetMarkerTGraphAsym(graphEfficienciesMerged, 20, 2., kBlack,kBlack);	
	graphEfficienciesMerged->Draw("psame");
	DrawGammaSetMarkerTGraphAsym(graphEfficienciesWOAddSig, 21, 2., kBlue-2, kBlue-2);	
	graphEfficienciesWOAddSig->Draw("psame");
	DrawGammaSetMarkerTGraphAsym(graphEfficienciesWAddSig, 33, 2.5, kRed-2, kRed-2);	
	graphEfficienciesWAddSig->Draw("psame");

	TLegend* legendEffiComp = new TLegend(0.73,0.73,0.93,0.93);
	legendEffiComp->SetFillColor(0);
	legendEffiComp->SetLineColor(0);
	legendEffiComp->SetTextSize(0.03);
	legendEffiComp->AddEntry(graphEfficienciesMerged,"MC merged","p");
	legendEffiComp->AddEntry(graphEfficienciesWOAddSig,"MC (w\o add Sig)","p");
	legendEffiComp->AddEntry(graphEfficienciesWAddSig,"MC (w add Sig)","p");
	legendEffiComp->Draw();

	canvasEffiVsCent->SaveAs(Form("%s/EffVsCent.%s",outputDir.Data(),suffix.Data()));
	delete canvasEffiVsCent;

	
}