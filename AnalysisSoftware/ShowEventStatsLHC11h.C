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
#include "CommonHeaders/ConversionFunctions.h"

void ShowEventStatsLHC11h(TString suffix = "pdf"){
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
	
		TGraphErrors* fracNEventsToTotal_Data0005 = (TGraphErrors*)EventStatsFile->Get("fracNEventsToTotal_0005_LHC11h");
		TGraphErrors* fracNEventsToTotal_Data0510 = (TGraphErrors*)EventStatsFile->Get("fracNEventsToTotal_0510_LHC11h");
		TGraphErrors* fracNEventsToTotal_Data1020 = (TGraphErrors*)EventStatsFile->Get("fracNEventsToTotal_1020_LHC11h");
		TGraphErrors* fracNEventsToTotal_Data2030 = (TGraphErrors*)EventStatsFile->Get("fracNEventsToTotal_2030_LHC11h");
		TGraphErrors* fracNEventsToTotal_Data3040 = (TGraphErrors*)EventStatsFile->Get("fracNEventsToTotal_3040_LHC11h");
		TGraphErrors* fracNEventsToTotal_Data4050 = (TGraphErrors*)EventStatsFile->Get("fracNEventsToTotal_4050_LHC11h");
		TGraphErrors* fracNEventsToTotal_Data5060 = (TGraphErrors*)EventStatsFile->Get("fracNEventsToTotal_5060_LHC11h");
		TGraphErrors* fracNEventsToTotal_Data6070 = (TGraphErrors*)EventStatsFile->Get("fracNEventsToTotal_6070_LHC11h");
		TGraphErrors* fracNEventsToTotal_Data2040 = (TGraphErrors*)EventStatsFile->Get("fracNEventsToTotal_2040_LHC11h");
		TGraphErrors* fracNEventsToTotal_Data4060 = (TGraphErrors*)EventStatsFile->Get("fracNEventsToTotal_4060_LHC11h");
		TGraphErrors* fracNEventsToTotal_Data6080 = (TGraphErrors*)EventStatsFile->Get("fracNEventsToTotal_6080_LHC11h");
	
		TGraphErrors* fractionOfGammasData0005 = (TGraphErrors*)EventStatsFile->Get("fracGammas_0005_LHC11h");
		TGraphErrors* fractionOfGammasData0510 = (TGraphErrors*)EventStatsFile->Get("fracGammas_0510_LHC11h");
		TGraphErrors* fractionOfGammasData1020 = (TGraphErrors*)EventStatsFile->Get("fracGammas_1020_LHC11h");
		TGraphErrors* fractionOfGammasData2030 = (TGraphErrors*)EventStatsFile->Get("fracGammas_2030_LHC11h");
		TGraphErrors* fractionOfGammasData3040 = (TGraphErrors*)EventStatsFile->Get("fracGammas_3040_LHC11h");
		TGraphErrors* fractionOfGammasData4050 = (TGraphErrors*)EventStatsFile->Get("fracGammas_4050_LHC11h");
		TGraphErrors* fractionOfGammasData5060 = (TGraphErrors*)EventStatsFile->Get("fracGammas_5060_LHC11h");
		TGraphErrors* fractionOfGammasData6070 = (TGraphErrors*)EventStatsFile->Get("fracGammas_6070_LHC11h");
		TGraphErrors* fractionOfGammasData2040 = (TGraphErrors*)EventStatsFile->Get("fracGammas_2040_LHC11h");
		TGraphErrors* fractionOfGammasData4060 = (TGraphErrors*)EventStatsFile->Get("fracGammas_4060_LHC11h");
		TGraphErrors* fractionOfGammasData6080 = (TGraphErrors*)EventStatsFile->Get("fracGammas_6080_LHC11h");

		TGraphErrors* fractionOfPi0Data0005 = (TGraphErrors*)EventStatsFile->Get("fractionOfPi0InCent_0005_LHC11h");
		TGraphErrors* fractionOfPi0Data0510 = (TGraphErrors*)EventStatsFile->Get("fractionOfPi0InCent_0510_LHC11h");
		TGraphErrors* fractionOfPi0Data1020 = (TGraphErrors*)EventStatsFile->Get("fractionOfPi0InCent_1020_LHC11h");
		TGraphErrors* fractionOfPi0Data2030 = (TGraphErrors*)EventStatsFile->Get("fractionOfPi0InCent_2030_LHC11h");
		TGraphErrors* fractionOfPi0Data3040 = (TGraphErrors*)EventStatsFile->Get("fractionOfPi0InCent_3040_LHC11h");
		TGraphErrors* fractionOfPi0Data4050 = (TGraphErrors*)EventStatsFile->Get("fractionOfPi0InCent_4050_LHC11h");
		TGraphErrors* fractionOfPi0Data5060 = (TGraphErrors*)EventStatsFile->Get("fractionOfPi0InCent_5060_LHC11h");
		TGraphErrors* fractionOfPi0Data6070 = (TGraphErrors*)EventStatsFile->Get("fractionOfPi0InCent_6070_LHC11h");
		TGraphErrors* fractionOfPi0Data2040 = (TGraphErrors*)EventStatsFile->Get("fractionOfPi0InCent_2040_LHC11h");
		TGraphErrors* fractionOfPi0Data4060 = (TGraphErrors*)EventStatsFile->Get("fractionOfPi0InCent_4060_LHC11h");
		TGraphErrors* fractionOfPi0Data6080 = (TGraphErrors*)EventStatsFile->Get("fractionOfPi0InCent_6080_LHC11h");

		TGraphErrors* massPi0Data0005 = (TGraphErrors*)EventStatsFile->Get("massPi0perRun_0005_LHC11h");
		TGraphErrors* massPi0Data0510 = (TGraphErrors*)EventStatsFile->Get("massPi0perRun_0510_LHC11h");
		TGraphErrors* massPi0Data1020 = (TGraphErrors*)EventStatsFile->Get("massPi0perRun_1020_LHC11h");
		TGraphErrors* massPi0Data2030 = (TGraphErrors*)EventStatsFile->Get("massPi0perRun_2030_LHC11h");
		TGraphErrors* massPi0Data3040 = (TGraphErrors*)EventStatsFile->Get("massPi0perRun_3040_LHC11h");
		TGraphErrors* massPi0Data4050 = (TGraphErrors*)EventStatsFile->Get("massPi0perRun_4050_LHC11h");
		TGraphErrors* massPi0Data5060 = (TGraphErrors*)EventStatsFile->Get("massPi0perRun_5060_LHC11h");
		TGraphErrors* massPi0Data6070 = (TGraphErrors*)EventStatsFile->Get("massPi0perRun_6070_LHC11h");
		TGraphErrors* massPi0Data2040 = (TGraphErrors*)EventStatsFile->Get("massPi0perRun_2040_LHC11h");
		TGraphErrors* massPi0Data4060 = (TGraphErrors*)EventStatsFile->Get("massPi0perRun_4060_LHC11h");
		TGraphErrors* massPi0Data6080 = (TGraphErrors*)EventStatsFile->Get("massPi0perRun_6080_LHC11h");

		TGraphErrors* massEtaData0005 = (TGraphErrors*)EventStatsFile->Get("massEtaperRun_0005_LHC11h");
		TGraphErrors* massEtaData0510 = (TGraphErrors*)EventStatsFile->Get("massEtaperRun_0510_LHC11h");
		TGraphErrors* massEtaData1020 = (TGraphErrors*)EventStatsFile->Get("massEtaperRun_1020_LHC11h");
		TGraphErrors* massEtaData2030 = (TGraphErrors*)EventStatsFile->Get("massEtaperRun_2030_LHC11h");
		TGraphErrors* massEtaData3040 = (TGraphErrors*)EventStatsFile->Get("massEtaperRun_3040_LHC11h");
		TGraphErrors* massEtaData4050 = (TGraphErrors*)EventStatsFile->Get("massEtaperRun_4050_LHC11h");
		TGraphErrors* massEtaData5060 = (TGraphErrors*)EventStatsFile->Get("massEtaperRun_5060_LHC11h");
		TGraphErrors* massEtaData6070 = (TGraphErrors*)EventStatsFile->Get("massEtaperRun_6070_LHC11h");
		TGraphErrors* massEtaData2040 = (TGraphErrors*)EventStatsFile->Get("massEtaperRun_2040_LHC11h");
		TGraphErrors* massEtaData4060 = (TGraphErrors*)EventStatsFile->Get("massEtaperRun_4060_LHC11h");
		TGraphErrors* massEtaData6080 = (TGraphErrors*)EventStatsFile->Get("massEtaperRun_6080_LHC11h");

		TGraphErrors* widthPi0Data0005 = (TGraphErrors*)EventStatsFile->Get("widthPi0perRun_0005_LHC11h");
		TGraphErrors* widthPi0Data0510 = (TGraphErrors*)EventStatsFile->Get("widthPi0perRun_0510_LHC11h");
		TGraphErrors* widthPi0Data1020 = (TGraphErrors*)EventStatsFile->Get("widthPi0perRun_1020_LHC11h");
		TGraphErrors* widthPi0Data2030 = (TGraphErrors*)EventStatsFile->Get("widthPi0perRun_2030_LHC11h");
		TGraphErrors* widthPi0Data3040 = (TGraphErrors*)EventStatsFile->Get("widthPi0perRun_3040_LHC11h");
		TGraphErrors* widthPi0Data4050 = (TGraphErrors*)EventStatsFile->Get("widthPi0perRun_4050_LHC11h");
		TGraphErrors* widthPi0Data5060 = (TGraphErrors*)EventStatsFile->Get("widthPi0perRun_5060_LHC11h");
		TGraphErrors* widthPi0Data6070 = (TGraphErrors*)EventStatsFile->Get("widthPi0perRun_6070_LHC11h");
		TGraphErrors* widthPi0Data2040 = (TGraphErrors*)EventStatsFile->Get("widthPi0perRun_2040_LHC11h");
		TGraphErrors* widthPi0Data4060 = (TGraphErrors*)EventStatsFile->Get("widthPi0perRun_4060_LHC11h");
		TGraphErrors* widthPi0Data6080 = (TGraphErrors*)EventStatsFile->Get("widthPi0perRun_6080_LHC11h");		

		TGraphErrors* meanTrackMultTPCData0005 = (TGraphErrors*)EventStatsFile->Get("meanTrackMultTPCInCent_0005_LHC11h");
		TGraphErrors* meanTrackMultTPCData0510 = (TGraphErrors*)EventStatsFile->Get("meanTrackMultTPCInCent_0510_LHC11h");
		TGraphErrors* meanTrackMultTPCData1020 = (TGraphErrors*)EventStatsFile->Get("meanTrackMultTPCInCent_1020_LHC11h");
		TGraphErrors* meanTrackMultTPCData2030 = (TGraphErrors*)EventStatsFile->Get("meanTrackMultTPCInCent_2030_LHC11h");
		TGraphErrors* meanTrackMultTPCData3040 = (TGraphErrors*)EventStatsFile->Get("meanTrackMultTPCInCent_3040_LHC11h");
		TGraphErrors* meanTrackMultTPCData4050 = (TGraphErrors*)EventStatsFile->Get("meanTrackMultTPCInCent_4050_LHC11h");
		TGraphErrors* meanTrackMultTPCData5060 = (TGraphErrors*)EventStatsFile->Get("meanTrackMultTPCInCent_5060_LHC11h");
		TGraphErrors* meanTrackMultTPCData6070 = (TGraphErrors*)EventStatsFile->Get("meanTrackMultTPCInCent_6070_LHC11h");
		TGraphErrors* meanTrackMultTPCData2040 = (TGraphErrors*)EventStatsFile->Get("meanTrackMultTPCInCent_2040_LHC11h");
		TGraphErrors* meanTrackMultTPCData4060 = (TGraphErrors*)EventStatsFile->Get("meanTrackMultTPCInCent_4060_LHC11h");
		TGraphErrors* meanTrackMultTPCData6080 = (TGraphErrors*)EventStatsFile->Get("meanTrackMultTPCInCent_6080_LHC11h");		

		TGraphErrors* fracNEventsToTotal_LHC11h_hadCharm_0005 = (TGraphErrors*)EventStatsFile->Get("fracNEventsToTotal_0005_LHC11h_hadCharm1");
		TGraphErrors* fracNEventsToTotal_LHC11h_hadCharm_0510 = (TGraphErrors*)EventStatsFile->Get("fracNEventsToTotal_0510_LHC11h_hadCharm1");
		TGraphErrors* fracNEventsToTotal_LHC11h_hadCharm_1020 = (TGraphErrors*)EventStatsFile->Get("fracNEventsToTotal_1020_LHC11h_hadCharm1");
		TGraphErrors* fracNEventsToTotal_LHC11h_hadCharm_2030 = (TGraphErrors*)EventStatsFile->Get("fracNEventsToTotal_2030_LHC11h_hadCharm2");
		TGraphErrors* fracNEventsToTotal_LHC11h_hadCharm_3040 = (TGraphErrors*)EventStatsFile->Get("fracNEventsToTotal_3040_LHC11h_hadCharm2");
		TGraphErrors* fracNEventsToTotal_LHC11h_hadCharm_4050 = (TGraphErrors*)EventStatsFile->Get("fracNEventsToTotal_4050_LHC11h_hadCharm2");
		TGraphErrors* fracNEventsToTotal_LHC11h_hadCharm_5060 = (TGraphErrors*)EventStatsFile->Get("fracNEventsToTotal_5060_LHC11h_hadCharm2");
// 		TGraphErrors* fracNEventsToTotal_LHC11h_hadCharm_6070 = (TGraphErrors*)EventStatsFile->Get("fracNEventsToTotal_6070_LHC11h_hadCharm2");
		
		TGraphErrors* fractionOfGammasLHC11h_hadCharm_0005 = (TGraphErrors*)EventStatsFile->Get("fracGammas_0005_LHC11h_hadCharm1");
		TGraphErrors* fractionOfGammasLHC11h_hadCharm_0510 = (TGraphErrors*)EventStatsFile->Get("fracGammas_0510_LHC11h_hadCharm1");
		TGraphErrors* fractionOfGammasLHC11h_hadCharm_1020 = (TGraphErrors*)EventStatsFile->Get("fracGammas_1020_LHC11h_hadCharm1");
		TGraphErrors* fractionOfGammasLHC11h_hadCharm_2030 = (TGraphErrors*)EventStatsFile->Get("fracGammas_2030_LHC11h_hadCharm2");
		TGraphErrors* fractionOfGammasLHC11h_hadCharm_3040 = (TGraphErrors*)EventStatsFile->Get("fracGammas_3040_LHC11h_hadCharm2");
		TGraphErrors* fractionOfGammasLHC11h_hadCharm_4050 = (TGraphErrors*)EventStatsFile->Get("fracGammas_4050_LHC11h_hadCharm2");
		TGraphErrors* fractionOfGammasLHC11h_hadCharm_5060 = (TGraphErrors*)EventStatsFile->Get("fracGammas_5060_LHC11h_hadCharm2");

		TGraphErrors* fractionOfPi0LHC11h_hadCharm_0005 = (TGraphErrors*)EventStatsFile->Get("fractionOfPi0InCent_0005_LHC11h_hadCharm1");
		TGraphErrors* fractionOfPi0LHC11h_hadCharm_0510 = (TGraphErrors*)EventStatsFile->Get("fractionOfPi0InCent_0510_LHC11h_hadCharm1");
		TGraphErrors* fractionOfPi0LHC11h_hadCharm_1020 = (TGraphErrors*)EventStatsFile->Get("fractionOfPi0InCent_1020_LHC11h_hadCharm1");
		TGraphErrors* fractionOfPi0LHC11h_hadCharm_2030 = (TGraphErrors*)EventStatsFile->Get("fractionOfPi0InCent_2030_LHC11h_hadCharm2");
		TGraphErrors* fractionOfPi0LHC11h_hadCharm_3040 = (TGraphErrors*)EventStatsFile->Get("fractionOfPi0InCent_3040_LHC11h_hadCharm2");
		TGraphErrors* fractionOfPi0LHC11h_hadCharm_4050 = (TGraphErrors*)EventStatsFile->Get("fractionOfPi0InCent_4050_LHC11h_hadCharm2");
		TGraphErrors* fractionOfPi0LHC11h_hadCharm_5060 = (TGraphErrors*)EventStatsFile->Get("fractionOfPi0InCent_5060_LHC11h_hadCharm2");
// 		TGraphErrors* fractionOfPi0LHC11h_hadCharm_6070 = (TGraphErrors*)EventStatsFile->Get("fractionOfPi0InCent_6070_LHC11h_hadCharm2");
		
		TGraphErrors* meanTrackMultTPCLHC11h_hadCharm_0005 = (TGraphErrors*)EventStatsFile->Get("meanTrackMultTPCInCent_0005_LHC11h_hadCharm1");
		TGraphErrors* meanTrackMultTPCLHC11h_hadCharm_0510 = (TGraphErrors*)EventStatsFile->Get("meanTrackMultTPCInCent_0510_LHC11h_hadCharm1");
		TGraphErrors* meanTrackMultTPCLHC11h_hadCharm_1020 = (TGraphErrors*)EventStatsFile->Get("meanTrackMultTPCInCent_1020_LHC11h_hadCharm1");
		TGraphErrors* meanTrackMultTPCLHC11h_hadCharm_2030 = (TGraphErrors*)EventStatsFile->Get("meanTrackMultTPCInCent_2030_LHC11h_hadCharm2");
		TGraphErrors* meanTrackMultTPCLHC11h_hadCharm_3040 = (TGraphErrors*)EventStatsFile->Get("meanTrackMultTPCInCent_3040_LHC11h_hadCharm2");
		TGraphErrors* meanTrackMultTPCLHC11h_hadCharm_4050 = (TGraphErrors*)EventStatsFile->Get("meanTrackMultTPCInCent_4050_LHC11h_hadCharm2");
		TGraphErrors* meanTrackMultTPCLHC11h_hadCharm_5060 = (TGraphErrors*)EventStatsFile->Get("meanTrackMultTPCInCent_5060_LHC11h_hadCharm2");
		
// 		TGraphErrors* fractionOfGammasLHC11a10b_bis0005 = (TGraphErrors*)EventStatsFile->Get("fracGammas_0005_LHC11a10b_bis");
// 		TGraphErrors* fractionOfGammasLHC11a10b_bis0510 = (TGraphErrors*)EventStatsFile->Get("fracGammas_0510_LHC11a10b_bis");
// 		TGraphErrors* fractionOfGammasLHC11a10b_bis1020 = (TGraphErrors*)EventStatsFile->Get("fracGammas_1020_LHC11a10b_bis");
// 		TGraphErrors* fractionOfGammasLHC11a10b_bis2040 = (TGraphErrors*)EventStatsFile->Get("fracGammas_2040_LHC11a10b_bis");
// 		TGraphErrors* fractionOfGammasLHC11a10b_bis4060 = (TGraphErrors*)EventStatsFile->Get("fracGammas_4060_LHC11a10b_bis");
// 		TGraphErrors* fractionOfGammasLHC11a10b_bis6080 = (TGraphErrors*)EventStatsFile->Get("fracGammas_6080_LHC11a10b_bis");
// 
// 
// 		TGraphErrors* fractionOfGammasLHC13d20005 = (TGraphErrors*)EventStatsFile->Get("fracGammas_0005_LHC13d2");
// 		TGraphErrors* fractionOfGammasLHC13d20510 = (TGraphErrors*)EventStatsFile->Get("fracGammas_0510_LHC13d2");
// 		TGraphErrors* fractionOfGammasLHC13d21020 = (TGraphErrors*)EventStatsFile->Get("fracGammas_1020_LHC13d2");
// 		TGraphErrors* fractionOfGammasLHC13d22040 = (TGraphErrors*)EventStatsFile->Get("fracGammas_2040_LHC13d2");
// 		TGraphErrors* fractionOfGammasLHC13d24060 = (TGraphErrors*)EventStatsFile->Get("fracGammas_4060_LHC13d2");
// 		TGraphErrors* fractionOfGammasLHC13d26080 = (TGraphErrors*)EventStatsFile->Get("fracGammas_6080_LHC13d2");
// 
// 
//       TGraphErrors* meanTrackMultTPCLHC13d20005 = (TGraphErrors*)EventStatsFile->Get("meanTrackMultTPCInCent_0005_LHC13d2");
//       TGraphErrors* meanTrackMultTPCLHC13d20510 = (TGraphErrors*)EventStatsFile->Get("meanTrackMultTPCInCent_0510_LHC13d2");
//       TGraphErrors* meanTrackMultTPCLHC13d21020 = (TGraphErrors*)EventStatsFile->Get("meanTrackMultTPCInCent_1020_LHC13d2");
//       TGraphErrors* meanTrackMultTPCLHC13d22040 = (TGraphErrors*)EventStatsFile->Get("meanTrackMultTPCInCent_2040_LHC13d2");
//       TGraphErrors* meanTrackMultTPCLHC13d24060 = (TGraphErrors*)EventStatsFile->Get("meanTrackMultTPCInCent_4060_LHC13d2");
//       TGraphErrors* meanTrackMultTPCLHC13d26080 = (TGraphErrors*)EventStatsFile->Get("meanTrackMultTPCInCent_6080_LHC13d2");

		
	Color_t	 colorComb0005	= kRed+1;
	Color_t	 colorComb0510	= 807;
	Color_t	 colorComb1020	= 800;
	Color_t	 colorComb2040	= kGreen+2;
	Color_t	 colorComb4060	= kCyan+2;
	Color_t	 colorComb6080	= kBlue+1;
	Color_t  colorComb2030	= kYellow-3;
	Color_t  colorComb3040	= kSpring-1;
	Color_t  colorComb4050	= kTeal+2;
	Color_t  colorComb5060	= kAzure+5;
	Color_t  colorComb6070	= kAzure-5;
	Color_t  colorComb7080	= kBlue-1;
	Color_t  colorComb8090	= kViolet+3;
	Color_t  colorComb7590	= kViolet-3;

	
	Color_t	colorCombMC0005	= kRed+3;
	Color_t	colorCombMC0510	= 807+2;
	Color_t	colorCombMC1020	= 800+2;
	Color_t	colorCombMC2040	= kGreen+4;
	Color_t	colorCombMC4060	= kCyan+4;
	Color_t	colorCombMC6080	= kBlue+3;
	Color_t colorCombMC2030	= kYellow-2;
	Color_t colorCombMC3040	= kSpring-7;
	Color_t colorCombMC4050	= kTeal+3;
	Color_t colorCombMC5060	= kAzure+4;
	Color_t colorCombMC6070	= kAzure-6;
	Color_t colorCombMC7080	= kBlue+4;
	Color_t colorCombMC8090	= kViolet+4;
	Color_t colorCombMC7590	= kViolet-6;

	
	Style_t 	markerStyleCommmonSpectrum0005 	= 20 ;
	Style_t 	markerStyleCommmonSpectrum0510 	= 21 ;
	Style_t 	markerStyleCommmonSpectrum1020 	= 29 ;
	Style_t 	markerStyleCommmonSpectrum2030 	= 33 ;
	Style_t 	markerStyleCommmonSpectrum3040 	= 20 ;
	Style_t 	markerStyleCommmonSpectrum4050 	= 21 ;
	Style_t 	markerStyleCommmonSpectrum5060 	= 29 ;
	Style_t 	markerStyleCommmonSpectrum6070 	= 33 ;
	Style_t 	markerStyleCommmonSpectrum2040 	= 33 ;
	Style_t 	markerStyleCommmonSpectrum4060 	= 20 ;
	Style_t 	markerStyleCommmonSpectrum6080 	= 21 ;

	Style_t 	markerStyleCommmonSpectrumMC0005 	= 24 ;
	Style_t 	markerStyleCommmonSpectrumMC0510 	= 25 ;
	Style_t 	markerStyleCommmonSpectrumMC1020 	= 30 ;
	Style_t 	markerStyleCommmonSpectrumMC2030 	= 27 ;
	Style_t 	markerStyleCommmonSpectrumMC3040 	= 24 ;
	Style_t 	markerStyleCommmonSpectrumMC4050 	= 25 ;
	Style_t 	markerStyleCommmonSpectrumMC5060 	= 30 ;
	Style_t 	markerStyleCommmonSpectrumMC6070 	= 27 ;
	Style_t 	markerStyleCommmonSpectrumMC2040 	= 27 ;
	Style_t 	markerStyleCommmonSpectrumMC4060 	= 24 ;
	Style_t 	markerStyleCommmonSpectrumMC6080 	= 25 ;

	
	Size_t 	markerSizeCommonSpectrum0005 	= 2.;
	Size_t 	markerSizeCommonSpectrum0510 	= 2.;
	Size_t 	markerSizeCommonSpectrum1020 	= 2.5;
	Size_t 	markerSizeCommonSpectrum2030 	= 2.5;
	Size_t 	markerSizeCommonSpectrum3040 	= 2.;
	Size_t 	markerSizeCommonSpectrum4050 	= 2.;
	Size_t 	markerSizeCommonSpectrum5060 	= 2.5;
	Size_t 	markerSizeCommonSpectrum6070 	= 2.5;
	Size_t 	markerSizeCommonSpectrum2040 	= 2.5;
	Size_t 	markerSizeCommonSpectrum4060 	= 2.;
	Size_t 	markerSizeCommonSpectrum6080 	= 2.;
	
	Width_t 	widthLinesBoxes;

	TString collisionSystemPbPb0005 = "0-5% Pb-Pb #sqrt{#it{s}_{_{NN}}} = 2.76 TeV";		
	TString collisionSystemPbPb0510 = "5-10% Pb-Pb #sqrt{#it{s}_{_{NN}}} = 2.76 TeV";		
	TString collisionSystemPbPb1020 = "10-20% Pb-Pb #sqrt{#it{s}_{_{NN}}} = 2.76 TeV";		
	TString collisionSystemPbPb0020 = "0-20% Pb-Pb #sqrt{#it{s}_{_{NN}}} = 2.76 TeV";		
	TString collisionSystemPbPb2040 = "20-40% Pb-Pb #sqrt{#it{s}_{_{NN}}} = 2.76 TeV";		
	TString collisionSystemPbPb2030 = "20-30% Pb-Pb #sqrt{#it{s}_{_{NN}}} = 2.76 TeV";		
	TString collisionSystemPbPb3040 = "30-40% Pb-Pb #sqrt{#it{s}_{_{NN}}} = 2.76 TeV";		
	TString collisionSystemPbPb3050 = "30-50% Pb-Pb #sqrt{#it{s}_{_{NN}}} = 2.76 TeV";		
	TString collisionSystemPbPb4060 = "40-60% Pb-Pb #sqrt{#it{s}_{_{NN}}} = 2.76 TeV";		
	TString collisionSystemPbPb4050 = "40-50% Pb-Pb #sqrt{#it{s}_{_{NN}}} = 2.76 TeV";		
	TString collisionSystemPbPb5060 = "50-60% Pb-Pb #sqrt{#it{s}_{_{NN}}} = 2.76 TeV";		
	TString collisionSystemPbPb6070 = "60-70% Pb-Pb #sqrt{#it{s}_{_{NN}}} = 2.76 TeV";		
	TString collisionSystemPbPb6080 = "60-80% Pb-Pb #sqrt{#it{s}_{_{NN}}} = 2.76 TeV";		

	TString collisionSystem0005 = "0-5%";		
	TString collisionSystem0510 = "5-10%";		
	TString collisionSystem1020 = "10-20%";		
	TString collisionSystem0020 = "0-20%";		
	TString collisionSystem2040 = "20-40%";		
	TString collisionSystem2030 = "20-30%";		
	TString collisionSystem3040 = "30-40%";		
	TString collisionSystem3050 = "30-50%";		
	TString collisionSystem4060 = "40-60%";		
	TString collisionSystem4050 = "40-50%";		
	TString collisionSystem5060 = "50-60%";		
	TString collisionSystem6070 = "60-70%";		
	TString collisionSystem6080 = "60-80%";		

	DrawGammaSetMarkerTGraphErr( fracNEventsToTotal_Data0005,  markerStyleCommmonSpectrum0005, markerSizeCommonSpectrum0005, colorComb0005, colorComb0005);
	DrawGammaSetMarkerTGraphErr( fracNEventsToTotal_Data0510,  markerStyleCommmonSpectrum0510, markerSizeCommonSpectrum0510, colorComb0510, colorComb0510);
	DrawGammaSetMarkerTGraphErr( fracNEventsToTotal_Data1020,  markerStyleCommmonSpectrum1020, markerSizeCommonSpectrum1020, colorComb1020, colorComb1020);
	DrawGammaSetMarkerTGraphErr( fracNEventsToTotal_Data2030,  markerStyleCommmonSpectrum2030, markerSizeCommonSpectrum2030, colorComb2030, colorComb2030);
	DrawGammaSetMarkerTGraphErr( fracNEventsToTotal_Data3040,  markerStyleCommmonSpectrum3040, markerSizeCommonSpectrum3040, colorComb3040, colorComb3040);
	DrawGammaSetMarkerTGraphErr( fracNEventsToTotal_Data4050,  markerStyleCommmonSpectrum4050, markerSizeCommonSpectrum4050, colorComb4050, colorComb4050);
	DrawGammaSetMarkerTGraphErr( fracNEventsToTotal_Data5060,  markerStyleCommmonSpectrum5060, markerSizeCommonSpectrum5060, colorComb5060, colorComb5060);
	DrawGammaSetMarkerTGraphErr( fracNEventsToTotal_Data6070,  markerStyleCommmonSpectrum6070, markerSizeCommonSpectrum6070, colorComb6070, colorComb6070);
	DrawGammaSetMarkerTGraphErr( fracNEventsToTotal_Data2040,  markerStyleCommmonSpectrum2040, markerSizeCommonSpectrum2040, colorComb2040, colorComb2040);
	DrawGammaSetMarkerTGraphErr( fracNEventsToTotal_Data4060,  markerStyleCommmonSpectrum4060, markerSizeCommonSpectrum4060, colorComb4060, colorComb4060);
	DrawGammaSetMarkerTGraphErr( fracNEventsToTotal_Data6080,  markerStyleCommmonSpectrum6080, markerSizeCommonSpectrum6080, colorComb6080, colorComb6080);
	
	DrawGammaSetMarkerTGraphErr( fractionOfGammasData0005,  markerStyleCommmonSpectrum0005, markerSizeCommonSpectrum0005, colorComb0005, colorComb0005);
	DrawGammaSetMarkerTGraphErr( fractionOfGammasData0510,  markerStyleCommmonSpectrum0510, markerSizeCommonSpectrum0510, colorComb0510, colorComb0510);
	DrawGammaSetMarkerTGraphErr( fractionOfGammasData1020,  markerStyleCommmonSpectrum1020, markerSizeCommonSpectrum1020, colorComb1020, colorComb1020);
	DrawGammaSetMarkerTGraphErr( fractionOfGammasData2030,  markerStyleCommmonSpectrum2030, markerSizeCommonSpectrum2030, colorComb2030, colorComb2030);
	DrawGammaSetMarkerTGraphErr( fractionOfGammasData3040,  markerStyleCommmonSpectrum3040, markerSizeCommonSpectrum3040, colorComb3040, colorComb3040);
	DrawGammaSetMarkerTGraphErr( fractionOfGammasData4050,  markerStyleCommmonSpectrum4050, markerSizeCommonSpectrum4050, colorComb4050, colorComb4050);
	DrawGammaSetMarkerTGraphErr( fractionOfGammasData5060,  markerStyleCommmonSpectrum5060, markerSizeCommonSpectrum5060, colorComb5060, colorComb5060);
	DrawGammaSetMarkerTGraphErr( fractionOfGammasData6070,  markerStyleCommmonSpectrum6070, markerSizeCommonSpectrum6070, colorComb6070, colorComb6070);
	DrawGammaSetMarkerTGraphErr( fractionOfGammasData2040,  markerStyleCommmonSpectrum2040, markerSizeCommonSpectrum2040, colorComb2040, colorComb2040);
	DrawGammaSetMarkerTGraphErr( fractionOfGammasData4060,  markerStyleCommmonSpectrum4060, markerSizeCommonSpectrum4060, colorComb4060, colorComb4060);
	DrawGammaSetMarkerTGraphErr( fractionOfGammasData6080,  markerStyleCommmonSpectrum6080, markerSizeCommonSpectrum6080, colorComb6080, colorComb6080);
	cout << "here"<< endl;
	
	DrawGammaSetMarkerTGraphErr( fractionOfPi0Data0005,  markerStyleCommmonSpectrum0005, markerSizeCommonSpectrum0005, colorComb0005, colorComb0005);
	DrawGammaSetMarkerTGraphErr( fractionOfPi0Data0510,  markerStyleCommmonSpectrum0510, markerSizeCommonSpectrum0510, colorComb0510, colorComb0510);
	DrawGammaSetMarkerTGraphErr( fractionOfPi0Data1020,  markerStyleCommmonSpectrum1020, markerSizeCommonSpectrum1020, colorComb1020, colorComb1020);
	DrawGammaSetMarkerTGraphErr( fractionOfPi0Data2030,  markerStyleCommmonSpectrum2030, markerSizeCommonSpectrum2030, colorComb2030, colorComb2030);
	DrawGammaSetMarkerTGraphErr( fractionOfPi0Data3040,  markerStyleCommmonSpectrum3040, markerSizeCommonSpectrum3040, colorComb3040, colorComb3040);
	DrawGammaSetMarkerTGraphErr( fractionOfPi0Data4050,  markerStyleCommmonSpectrum4050, markerSizeCommonSpectrum4050, colorComb4050, colorComb4050);
	DrawGammaSetMarkerTGraphErr( fractionOfPi0Data5060,  markerStyleCommmonSpectrum5060, markerSizeCommonSpectrum5060, colorComb5060, colorComb5060);
	DrawGammaSetMarkerTGraphErr( fractionOfPi0Data6070,  markerStyleCommmonSpectrum6070, markerSizeCommonSpectrum6070, colorComb6070, colorComb6070);
	DrawGammaSetMarkerTGraphErr( fractionOfPi0Data2040,  markerStyleCommmonSpectrum2040, markerSizeCommonSpectrum2040, colorComb2040, colorComb2040);
	DrawGammaSetMarkerTGraphErr( fractionOfPi0Data4060,  markerStyleCommmonSpectrum4060, markerSizeCommonSpectrum4060, colorComb4060, colorComb4060);
	DrawGammaSetMarkerTGraphErr( fractionOfPi0Data6080,  markerStyleCommmonSpectrum6080, markerSizeCommonSpectrum6080, colorComb6080, colorComb6080);
	cout << "here"<< endl;
	
	DrawGammaSetMarkerTGraphErr( massPi0Data0005,  markerStyleCommmonSpectrum0005, markerSizeCommonSpectrum0005, colorComb0005, colorComb0005);
	DrawGammaSetMarkerTGraphErr( massPi0Data0510,  markerStyleCommmonSpectrum0510, markerSizeCommonSpectrum0510, colorComb0510, colorComb0510);
	DrawGammaSetMarkerTGraphErr( massPi0Data1020,  markerStyleCommmonSpectrum1020, markerSizeCommonSpectrum1020, colorComb1020, colorComb1020);
	DrawGammaSetMarkerTGraphErr( massPi0Data2030,  markerStyleCommmonSpectrum2030, markerSizeCommonSpectrum2030, colorComb2030, colorComb2030);
	DrawGammaSetMarkerTGraphErr( massPi0Data3040,  markerStyleCommmonSpectrum3040, markerSizeCommonSpectrum3040, colorComb3040, colorComb3040);
	DrawGammaSetMarkerTGraphErr( massPi0Data4050,  markerStyleCommmonSpectrum4050, markerSizeCommonSpectrum4050, colorComb4050, colorComb4050);
	DrawGammaSetMarkerTGraphErr( massPi0Data5060,  markerStyleCommmonSpectrum5060, markerSizeCommonSpectrum5060, colorComb5060, colorComb5060);
	DrawGammaSetMarkerTGraphErr( massPi0Data6070,  markerStyleCommmonSpectrum6070, markerSizeCommonSpectrum6070, colorComb6070, colorComb6070);
	
	DrawGammaSetMarkerTGraphErr( massEtaData0005,  markerStyleCommmonSpectrum0005, markerSizeCommonSpectrum0005, colorComb0005, colorComb0005);
	DrawGammaSetMarkerTGraphErr( massEtaData0510,  markerStyleCommmonSpectrum0510, markerSizeCommonSpectrum0510, colorComb0510, colorComb0510);
	DrawGammaSetMarkerTGraphErr( massEtaData1020,  markerStyleCommmonSpectrum1020, markerSizeCommonSpectrum1020, colorComb1020, colorComb1020);
	DrawGammaSetMarkerTGraphErr( massEtaData2030,  markerStyleCommmonSpectrum2030, markerSizeCommonSpectrum2030, colorComb2030, colorComb2030);
	DrawGammaSetMarkerTGraphErr( massEtaData3040,  markerStyleCommmonSpectrum3040, markerSizeCommonSpectrum3040, colorComb3040, colorComb3040);
	DrawGammaSetMarkerTGraphErr( massEtaData4050,  markerStyleCommmonSpectrum4050, markerSizeCommonSpectrum4050, colorComb4050, colorComb4050);
	DrawGammaSetMarkerTGraphErr( massEtaData5060,  markerStyleCommmonSpectrum5060, markerSizeCommonSpectrum5060, colorComb5060, colorComb5060);
	DrawGammaSetMarkerTGraphErr( massEtaData6070,  markerStyleCommmonSpectrum6070, markerSizeCommonSpectrum6070, colorComb6070, colorComb6070);

	cout << "here"<< endl;
	
	DrawGammaSetMarkerTGraphErr( widthPi0Data0005,  markerStyleCommmonSpectrum0005, markerSizeCommonSpectrum0005, colorComb0005, colorComb0005);
	DrawGammaSetMarkerTGraphErr( widthPi0Data0510,  markerStyleCommmonSpectrum0510, markerSizeCommonSpectrum0510, colorComb0510, colorComb0510);
	DrawGammaSetMarkerTGraphErr( widthPi0Data1020,  markerStyleCommmonSpectrum1020, markerSizeCommonSpectrum1020, colorComb1020, colorComb1020);
	DrawGammaSetMarkerTGraphErr( widthPi0Data2030,  markerStyleCommmonSpectrum2030, markerSizeCommonSpectrum2030, colorComb2030, colorComb2030);
	DrawGammaSetMarkerTGraphErr( widthPi0Data3040,  markerStyleCommmonSpectrum3040, markerSizeCommonSpectrum3040, colorComb3040, colorComb3040);
	DrawGammaSetMarkerTGraphErr( widthPi0Data4050,  markerStyleCommmonSpectrum4050, markerSizeCommonSpectrum4050, colorComb4050, colorComb4050);
	DrawGammaSetMarkerTGraphErr( widthPi0Data5060,  markerStyleCommmonSpectrum5060, markerSizeCommonSpectrum5060, colorComb5060, colorComb5060);
	DrawGammaSetMarkerTGraphErr( widthPi0Data6070,  markerStyleCommmonSpectrum6070, markerSizeCommonSpectrum6070, colorComb6070, colorComb6070);
	
	cout << "here"<< endl;
	
	DrawGammaSetMarkerTGraphErr( meanTrackMultTPCData0005,  markerStyleCommmonSpectrum0005, markerSizeCommonSpectrum0005, colorComb0005, colorComb0005);
	DrawGammaSetMarkerTGraphErr( meanTrackMultTPCData0510,  markerStyleCommmonSpectrum0510, markerSizeCommonSpectrum0510, colorComb0510, colorComb0510);
	DrawGammaSetMarkerTGraphErr( meanTrackMultTPCData1020,  markerStyleCommmonSpectrum1020, markerSizeCommonSpectrum1020, colorComb1020, colorComb1020);
	DrawGammaSetMarkerTGraphErr( meanTrackMultTPCData2030,  markerStyleCommmonSpectrum2030, markerSizeCommonSpectrum2030, colorComb2030, colorComb2030);
	DrawGammaSetMarkerTGraphErr( meanTrackMultTPCData3040,  markerStyleCommmonSpectrum3040, markerSizeCommonSpectrum3040, colorComb3040, colorComb3040);
	DrawGammaSetMarkerTGraphErr( meanTrackMultTPCData4050,  markerStyleCommmonSpectrum4050, markerSizeCommonSpectrum4050, colorComb4050, colorComb4050);
	DrawGammaSetMarkerTGraphErr( meanTrackMultTPCData5060,  markerStyleCommmonSpectrum5060, markerSizeCommonSpectrum5060, colorComb5060, colorComb5060);
	DrawGammaSetMarkerTGraphErr( meanTrackMultTPCData6070,  markerStyleCommmonSpectrum6070, markerSizeCommonSpectrum6070, colorComb6070, colorComb6070);
	DrawGammaSetMarkerTGraphErr( meanTrackMultTPCData2040,  markerStyleCommmonSpectrum2040, markerSizeCommonSpectrum2040, colorComb2040, colorComb2040);
	DrawGammaSetMarkerTGraphErr( meanTrackMultTPCData4060,  markerStyleCommmonSpectrum4060, markerSizeCommonSpectrum4060, colorComb4060, colorComb4060);
	DrawGammaSetMarkerTGraphErr( meanTrackMultTPCData6080,  markerStyleCommmonSpectrum6080, markerSizeCommonSpectrum6080, colorComb6080, colorComb6080);

	cout << "here"<< endl;	
	
	DrawGammaSetMarkerTGraphErr( fracNEventsToTotal_LHC11h_hadCharm_0005,  markerStyleCommmonSpectrumMC0005, markerSizeCommonSpectrum0005, colorCombMC0005, colorCombMC0005);
	DrawGammaSetMarkerTGraphErr( fracNEventsToTotal_LHC11h_hadCharm_0510,  markerStyleCommmonSpectrumMC0510, markerSizeCommonSpectrum0510, colorCombMC0510, colorCombMC0510);
	DrawGammaSetMarkerTGraphErr( fracNEventsToTotal_LHC11h_hadCharm_1020,  markerStyleCommmonSpectrumMC1020, markerSizeCommonSpectrum1020, colorCombMC1020, colorCombMC1020);
	DrawGammaSetMarkerTGraphErr( fracNEventsToTotal_LHC11h_hadCharm_2030,  markerStyleCommmonSpectrumMC2030, markerSizeCommonSpectrum2030, colorCombMC2030, colorCombMC2030);
	DrawGammaSetMarkerTGraphErr( fracNEventsToTotal_LHC11h_hadCharm_3040,  markerStyleCommmonSpectrumMC3040, markerSizeCommonSpectrum3040, colorCombMC3040, colorCombMC3040);
	DrawGammaSetMarkerTGraphErr( fracNEventsToTotal_LHC11h_hadCharm_4050,  markerStyleCommmonSpectrumMC4050, markerSizeCommonSpectrum4050, colorCombMC4050, colorCombMC4050);
	DrawGammaSetMarkerTGraphErr( fracNEventsToTotal_LHC11h_hadCharm_5060,  markerStyleCommmonSpectrumMC5060, markerSizeCommonSpectrum5060, colorCombMC5060, colorCombMC5060);

	
	DrawGammaSetMarkerTGraphErr( fractionOfGammasLHC11h_hadCharm_0005,  markerStyleCommmonSpectrumMC0005, markerSizeCommonSpectrum0005, colorCombMC0005, colorCombMC0005);
	DrawGammaSetMarkerTGraphErr( fractionOfGammasLHC11h_hadCharm_0510,  markerStyleCommmonSpectrumMC0510, markerSizeCommonSpectrum0510, colorCombMC0510, colorCombMC0510);
	DrawGammaSetMarkerTGraphErr( fractionOfGammasLHC11h_hadCharm_1020,  markerStyleCommmonSpectrumMC1020, markerSizeCommonSpectrum1020, colorCombMC1020, colorCombMC1020);
	DrawGammaSetMarkerTGraphErr( fractionOfGammasLHC11h_hadCharm_2030,  markerStyleCommmonSpectrumMC2030, markerSizeCommonSpectrum2030, colorCombMC2030, colorCombMC2030);
	DrawGammaSetMarkerTGraphErr( fractionOfGammasLHC11h_hadCharm_3040,  markerStyleCommmonSpectrumMC3040, markerSizeCommonSpectrum3040, colorCombMC3040, colorCombMC3040);
	DrawGammaSetMarkerTGraphErr( fractionOfGammasLHC11h_hadCharm_4050,  markerStyleCommmonSpectrumMC4050, markerSizeCommonSpectrum4050, colorCombMC4050, colorCombMC4050);
	DrawGammaSetMarkerTGraphErr( fractionOfGammasLHC11h_hadCharm_5060,  markerStyleCommmonSpectrumMC5060, markerSizeCommonSpectrum5060, colorCombMC5060, colorCombMC5060);

	DrawGammaSetMarkerTGraphErr( fractionOfPi0LHC11h_hadCharm_0005,  markerStyleCommmonSpectrumMC0005, markerSizeCommonSpectrum0005, colorCombMC0005, colorCombMC0005);
	DrawGammaSetMarkerTGraphErr( fractionOfPi0LHC11h_hadCharm_0510,  markerStyleCommmonSpectrumMC0510, markerSizeCommonSpectrum0510, colorCombMC0510, colorCombMC0510);
	DrawGammaSetMarkerTGraphErr( fractionOfPi0LHC11h_hadCharm_1020,  markerStyleCommmonSpectrumMC1020, markerSizeCommonSpectrum1020, colorCombMC1020, colorCombMC1020);
	DrawGammaSetMarkerTGraphErr( fractionOfPi0LHC11h_hadCharm_2030,  markerStyleCommmonSpectrumMC2030, markerSizeCommonSpectrum2030, colorCombMC2030, colorCombMC2030);
	DrawGammaSetMarkerTGraphErr( fractionOfPi0LHC11h_hadCharm_3040,  markerStyleCommmonSpectrumMC3040, markerSizeCommonSpectrum3040, colorCombMC3040, colorCombMC3040);
	DrawGammaSetMarkerTGraphErr( fractionOfPi0LHC11h_hadCharm_4050,  markerStyleCommmonSpectrumMC4050, markerSizeCommonSpectrum4050, colorCombMC4050, colorCombMC4050);
	DrawGammaSetMarkerTGraphErr( fractionOfPi0LHC11h_hadCharm_5060,  markerStyleCommmonSpectrumMC5060, markerSizeCommonSpectrum5060, colorCombMC5060, colorCombMC5060);
	
	DrawGammaSetMarkerTGraphErr( meanTrackMultTPCLHC11h_hadCharm_0005,  markerStyleCommmonSpectrumMC0005, markerSizeCommonSpectrum0005, colorCombMC0005, colorCombMC0005);
	DrawGammaSetMarkerTGraphErr( meanTrackMultTPCLHC11h_hadCharm_0510,  markerStyleCommmonSpectrumMC0510, markerSizeCommonSpectrum0510, colorCombMC0510, colorCombMC0510);
	DrawGammaSetMarkerTGraphErr( meanTrackMultTPCLHC11h_hadCharm_1020,  markerStyleCommmonSpectrumMC1020, markerSizeCommonSpectrum1020, colorCombMC1020, colorCombMC1020);
	DrawGammaSetMarkerTGraphErr( meanTrackMultTPCLHC11h_hadCharm_2030,  markerStyleCommmonSpectrumMC2030, markerSizeCommonSpectrum2030, colorCombMC2030, colorCombMC2030);
	DrawGammaSetMarkerTGraphErr( meanTrackMultTPCLHC11h_hadCharm_3040,  markerStyleCommmonSpectrumMC3040, markerSizeCommonSpectrum3040, colorCombMC3040, colorCombMC3040);
	DrawGammaSetMarkerTGraphErr( meanTrackMultTPCLHC11h_hadCharm_4050,  markerStyleCommmonSpectrumMC4050, markerSizeCommonSpectrum4050, colorCombMC4050, colorCombMC4050);
	DrawGammaSetMarkerTGraphErr( meanTrackMultTPCLHC11h_hadCharm_5060,  markerStyleCommmonSpectrumMC5060, markerSizeCommonSpectrum5060, colorCombMC5060, colorCombMC5060);
	
// 	DrawGammaSetMarkerTGraphErr( fractionOfGammasLHC11a10b_bis0005,  markerStyleCommmonSpectrumMC0005, markerSizeCommonSpectrum0005, colorCombMC0005, colorCombMC0005);
// 	DrawGammaSetMarkerTGraphErr( fractionOfGammasLHC11a10b_bis0510,  markerStyleCommmonSpectrumMC0510, markerSizeCommonSpectrum0510, colorCombMC0510, colorCombMC0510);
// 	DrawGammaSetMarkerTGraphErr( fractionOfGammasLHC11a10b_bis1020,  markerStyleCommmonSpectrumMC1020, markerSizeCommonSpectrum1020, colorCombMC1020, colorCombMC1020);
// 	DrawGammaSetMarkerTGraphErr( fractionOfGammasLHC11a10b_bis2040,  markerStyleCommmonSpectrumMC2040, markerSizeCommonSpectrum2040, colorCombMC2040, colorCombMC2040);
// 	DrawGammaSetMarkerTGraphErr( fractionOfGammasLHC11a10b_bis4060,  markerStyleCommmonSpectrumMC4060, markerSizeCommonSpectrum4060, colorCombMC4060, colorCombMC4060);
// 	DrawGammaSetMarkerTGraphErr( fractionOfGammasLHC11a10b_bis6080,  markerStyleCommmonSpectrumMC6080, markerSizeCommonSpectrum6080, colorCombMC6080, colorCombMC6080);

   
// 	DrawGammaSetMarkerTGraphErr( fractionOfGammasLHC13d20005,  markerStyleCommmonSpectrumMC0005, markerSizeCommonSpectrum0005, colorCombMC0005, colorCombMC0005);
// 	DrawGammaSetMarkerTGraphErr( fractionOfGammasLHC13d20510,  markerStyleCommmonSpectrumMC0510, markerSizeCommonSpectrum0510, colorCombMC0510, colorCombMC0510);
// 	DrawGammaSetMarkerTGraphErr( fractionOfGammasLHC13d21020,  markerStyleCommmonSpectrumMC1020, markerSizeCommonSpectrum1020, colorCombMC1020, colorCombMC1020);
// 	DrawGammaSetMarkerTGraphErr( fractionOfGammasLHC13d22040,  markerStyleCommmonSpectrumMC2040, markerSizeCommonSpectrum2040, colorCombMC2040, colorCombMC2040);
// 	DrawGammaSetMarkerTGraphErr( fractionOfGammasLHC13d24060,  markerStyleCommmonSpectrumMC4060, markerSizeCommonSpectrum4060, colorCombMC4060, colorCombMC4060);
// 	DrawGammaSetMarkerTGraphErr( fractionOfGammasLHC13d26080,  markerStyleCommmonSpectrumMC6080, markerSizeCommonSpectrum6080, colorCombMC6080, colorCombMC6080);
	   
//    DrawGammaSetMarkerTGraphErr( meanTrackMultTPCLHC13d20005,  markerStyleCommmonSpectrumMC0005, markerSizeCommonSpectrum0005, colorCombMC0005, colorCombMC0005);
//    DrawGammaSetMarkerTGraphErr( meanTrackMultTPCLHC13d20510,  markerStyleCommmonSpectrumMC0510, markerSizeCommonSpectrum0510, colorCombMC0510, colorCombMC0510);
//    DrawGammaSetMarkerTGraphErr( meanTrackMultTPCLHC13d21020,  markerStyleCommmonSpectrumMC1020, markerSizeCommonSpectrum1020, colorCombMC1020, colorCombMC1020);
//    DrawGammaSetMarkerTGraphErr( meanTrackMultTPCLHC13d22040,  markerStyleCommmonSpectrumMC2040, markerSizeCommonSpectrum2040, colorCombMC2040, colorCombMC2040);
//    DrawGammaSetMarkerTGraphErr( meanTrackMultTPCLHC13d24060,  markerStyleCommmonSpectrumMC4060, markerSizeCommonSpectrum4060, colorCombMC4060, colorCombMC4060);
//    DrawGammaSetMarkerTGraphErr( meanTrackMultTPCLHC13d26080,  markerStyleCommmonSpectrumMC6080, markerSizeCommonSpectrum6080, colorCombMC6080, colorCombMC6080);

   
	cout << "Plot 1" << endl;
   

	TCanvas* canvasNEvtInCentToTotalData = new TCanvas("canvasNGammaEvtData","",200,10,1350,1000);  // gives the page size
	DrawGammaCanvasSettings( canvasNEvtInCentToTotalData, 0.08, 0.01, 0.06, 0.07);
 	canvasNEvtInCentToTotalData->SetLogy();
	
	TH2F * histo2DnEvt;
	histo2DnEvt = new TH2F("histo2DnEvt","histo2DnEvt",2700,167900,170600,10000,0.01,10);
// 	histo2DnEvt->GetXaxis()->SetRangeUser(0.,2100.);
	SetStyleHistoTH2ForGraphs(histo2DnEvt, "Run number","N_{evt,run}/N_{evt,period}",0.03,0.04, 0.03,0.04, 0.8,0.95);
	histo2DnEvt->Draw("copy");

	fracNEventsToTotal_Data0005->Draw("pesame");
	fracNEventsToTotal_Data0510->Draw("pesame");
	fracNEventsToTotal_Data1020->Draw("pesame");
	fracNEventsToTotal_Data2030->Draw("pesame");
	fracNEventsToTotal_Data3040->Draw("pesame");
	fracNEventsToTotal_Data4050->Draw("pesame");
	fracNEventsToTotal_Data5060->Draw("pesame");
	fracNEventsToTotal_Data6070->Draw("pesame");
// 	fracNEventsToTotal_Data2040->Draw("pesame");
// 	fracNEventsToTotal_Data4060->Draw("pesame");
// 	fracNEventsToTotal_Data6080->Draw("pesame");
	
	TLegend* legendDatanEvt = new TLegend(0.075,0.945,0.99,1.);
	legendDatanEvt->SetFillColor(0);
	legendDatanEvt->SetLineColor(0);
	legendDatanEvt->SetTextSize(0.04);
	legendDatanEvt->SetNColumns(8);
// 	legendDatanEvt->AddEntry((TObject*)0, "Data:","");
	legendDatanEvt->AddEntry(fracNEventsToTotal_Data0005,collisionSystem0005.Data(),"p");
	legendDatanEvt->AddEntry(fracNEventsToTotal_Data0510,collisionSystem0510.Data(),"p");
	legendDatanEvt->AddEntry(fracNEventsToTotal_Data1020,collisionSystem1020.Data(),"p");
	legendDatanEvt->AddEntry(fracNEventsToTotal_Data2030,collisionSystem2030.Data(),"p");
	legendDatanEvt->AddEntry(fracNEventsToTotal_Data3040,collisionSystem3040.Data(),"p");
	legendDatanEvt->AddEntry(fracNEventsToTotal_Data4050,collisionSystem4050.Data(),"p");
	legendDatanEvt->AddEntry(fracNEventsToTotal_Data5060,collisionSystem5060.Data(),"p");
	legendDatanEvt->AddEntry(fracNEventsToTotal_Data6070,collisionSystem6070.Data(),"p");
	legendDatanEvt->Draw();

	canvasNEvtInCentToTotalData->SaveAs(Form("%s/FractionEventsInCentToTotal_LHC11h.%s",outputDir.Data(),suffix.Data()));

		canvasNEvtInCentToTotalData->cd();
	histo2DnEvt->Draw("copy");
	fracNEventsToTotal_Data0005->Draw("pesame");
	fracNEventsToTotal_LHC11h_hadCharm_0005->Draw("pesame");
	
	TLegend* legendDataNEvt0005 = new TLegend(0.09,0.945,0.99,1.);
	legendDataNEvt0005->SetFillColor(0);
	legendDataNEvt0005->SetLineColor(0);
	legendDataNEvt0005->SetTextSize(0.04);
	legendDataNEvt0005->SetNColumns(8);
	legendDataNEvt0005->AddEntry((TObject*)0,collisionSystem0005.Data(),"");
	legendDataNEvt0005->AddEntry(fractionOfGammasData0005,"Data","p");
	legendDataNEvt0005->AddEntry(fractionOfGammasLHC11h_hadCharm_0005,"MC","p");
	legendDataNEvt0005->Draw();

	canvasNEvtInCentToTotalData->SaveAs(Form("%s/FractionEventsInCentToTotal_LHC11h_0005_hadCharm.%s",outputDir.Data(),suffix.Data()));

	histo2DnEvt->Draw("copy");
	fracNEventsToTotal_Data0510->Draw("pesame");
	fracNEventsToTotal_LHC11h_hadCharm_0510->Draw("pesame");
	
	TLegend* legendDataNEvt0510 = new TLegend(0.09,0.945,0.99,1.);
	legendDataNEvt0510->SetFillColor(0);
	legendDataNEvt0510->SetLineColor(0);
	legendDataNEvt0510->SetTextSize(0.04);
	legendDataNEvt0510->SetNColumns(8);
	legendDataNEvt0510->AddEntry((TObject*)0,collisionSystem0510.Data(),"");
	legendDataNEvt0510->AddEntry(fractionOfGammasData0510,"Data","p");
	legendDataNEvt0510->AddEntry(fractionOfGammasLHC11h_hadCharm_0510,"MC","p");
	legendDataNEvt0510->Draw();

	canvasNEvtInCentToTotalData->SaveAs(Form("%s/FractionEventsInCentToTotal_LHC11h_0510_hadCharm.%s",outputDir.Data(),suffix.Data()));

		histo2DnEvt->Draw("copy");
	fracNEventsToTotal_Data1020->Draw("pesame");
	fracNEventsToTotal_LHC11h_hadCharm_1020->Draw("pesame");
	
	TLegend* legendDataNEvt1020 = new TLegend(0.09,0.945,0.99,1.);
	legendDataNEvt1020->SetFillColor(0);
	legendDataNEvt1020->SetLineColor(0);
	legendDataNEvt1020->SetTextSize(0.04);
	legendDataNEvt1020->SetNColumns(8);
	legendDataNEvt1020->AddEntry((TObject*)0,collisionSystem1020.Data(),"");
	legendDataNEvt1020->AddEntry(fractionOfGammasData1020,"Data","p");
	legendDataNEvt1020->AddEntry(fractionOfGammasLHC11h_hadCharm_1020,"MC","p");
	legendDataNEvt1020->Draw();

	canvasNEvtInCentToTotalData->SaveAs(Form("%s/FractionEventsInCentToTotal_LHC11h_1020_hadCharm.%s",outputDir.Data(),suffix.Data()));

		histo2DnEvt->Draw("copy");
	fracNEventsToTotal_Data2030->Draw("pesame");
	fracNEventsToTotal_LHC11h_hadCharm_2030->Draw("pesame");
	
	TLegend* legendDataNEvt2030 = new TLegend(0.09,0.945,0.99,1.);
	legendDataNEvt2030->SetFillColor(0);
	legendDataNEvt2030->SetLineColor(0);
	legendDataNEvt2030->SetTextSize(0.04);
	legendDataNEvt2030->SetNColumns(8);
	legendDataNEvt2030->AddEntry((TObject*)0,collisionSystem2030.Data(),"");
	legendDataNEvt2030->AddEntry(fractionOfGammasData2030,"Data","p");
	legendDataNEvt2030->AddEntry(fractionOfGammasLHC11h_hadCharm_2030,"MC","p");
	legendDataNEvt2030->Draw();

	canvasNEvtInCentToTotalData->SaveAs(Form("%s/FractionEventsInCentToTotal_LHC11h_2030_hadCharm.%s",outputDir.Data(),suffix.Data()));

		histo2DnEvt->Draw("copy");
	fracNEventsToTotal_Data3040->Draw("pesame");
	fracNEventsToTotal_LHC11h_hadCharm_3040->Draw("pesame");
	
	TLegend* legendDataNEvt3040 = new TLegend(0.09,0.945,0.99,1.);
	legendDataNEvt3040->SetFillColor(0);
	legendDataNEvt3040->SetLineColor(0);
	legendDataNEvt3040->SetTextSize(0.04);
	legendDataNEvt3040->SetNColumns(8);
	legendDataNEvt3040->AddEntry((TObject*)0,collisionSystem3040.Data(),"");
	legendDataNEvt3040->AddEntry(fractionOfGammasData3040,"Data","p");
	legendDataNEvt3040->AddEntry(fractionOfGammasLHC11h_hadCharm_3040,"MC","p");
	legendDataNEvt3040->Draw();

	canvasNEvtInCentToTotalData->SaveAs(Form("%s/FractionEventsInCentToTotal_LHC11h_3040_hadCharm.%s",outputDir.Data(),suffix.Data()));

	histo2DnEvt->Draw("copy");
	fracNEventsToTotal_Data4050->Draw("pesame");
	fracNEventsToTotal_LHC11h_hadCharm_4050->Draw("pesame");
	
	TLegend* legendDataNEvt4050 = new TLegend(0.09,0.945,0.99,1.);
	legendDataNEvt4050->SetFillColor(0);
	legendDataNEvt4050->SetLineColor(0);
	legendDataNEvt4050->SetTextSize(0.04);
	legendDataNEvt4050->SetNColumns(8);
	legendDataNEvt4050->AddEntry((TObject*)0,collisionSystem4050.Data(),"");
	legendDataNEvt4050->AddEntry(fractionOfGammasData4050,"Data","p");
	legendDataNEvt4050->AddEntry(fractionOfGammasLHC11h_hadCharm_4050,"MC","p");
	legendDataNEvt4050->Draw();

	canvasNEvtInCentToTotalData->SaveAs(Form("%s/FractionEventsInCentToTotal_LHC11h_4050_hadCharm.%s",outputDir.Data(),suffix.Data()));

		histo2DnEvt->Draw("copy");
	fracNEventsToTotal_Data5060->Draw("pesame");
	fracNEventsToTotal_LHC11h_hadCharm_5060->Draw("pesame");
	
	TLegend* legendDataNEvt5060 = new TLegend(0.09,0.945,0.99,1.);
	legendDataNEvt5060->SetFillColor(0);
	legendDataNEvt5060->SetLineColor(0);
	legendDataNEvt5060->SetTextSize(0.04);
	legendDataNEvt5060->SetNColumns(8);
	legendDataNEvt5060->AddEntry((TObject*)0,collisionSystem5060.Data(),"");
	legendDataNEvt5060->AddEntry(fractionOfGammasData5060,"Data","p");
	legendDataNEvt5060->AddEntry(fractionOfGammasLHC11h_hadCharm_5060,"MC","p");
	legendDataNEvt5060->Draw();

	canvasNEvtInCentToTotalData->SaveAs(Form("%s/FractionEventsInCentToTotal_LHC11h_5060_hadCharm.%s",outputDir.Data(),suffix.Data()));

	
	TCanvas* canvasNGammaEvtData = new TCanvas("canvasNGammaEvtData","",200,10,1350,1000);  // gives the page size
	DrawGammaCanvasSettings( canvasNGammaEvtData, 0.08, 0.01, 0.06, 0.07);
 	canvasNGammaEvtData->SetLogy();
	
	TH2F * histo2DEff;
	histo2DEff = new TH2F("histo2DEff","histo2DEff",2700,167900,170600,10000,0.6,40	);
// 	histo2DEff->GetXaxis()->SetRangeUser(0.,2100.);
	SetStyleHistoTH2ForGraphs(histo2DEff, "Run number","#gamma_{cand}/N_{evt}",0.03,0.04, 0.03,0.04, 0.8,0.95);
	histo2DEff->Draw("copy");

	fractionOfGammasData0005->Draw("pesame");
	fractionOfGammasData0510->Draw("pesame");
	fractionOfGammasData1020->Draw("pesame");
	fractionOfGammasData2030->Draw("pesame");
	fractionOfGammasData3040->Draw("pesame");
	fractionOfGammasData4050->Draw("pesame");
	fractionOfGammasData5060->Draw("pesame");
	fractionOfGammasData6070->Draw("pesame");
// 	fractionOfGammasData2040->Draw("pesame");
// 	fractionOfGammasData4060->Draw("pesame");
// 	fractionOfGammasData6080->Draw("pesame");
	
	TLegend* legendData = new TLegend(0.075,0.945,0.99,1.);
	legendData->SetFillColor(0);
	legendData->SetLineColor(0);
	legendData->SetTextSize(0.04);
	legendData->SetNColumns(8);
// 	legendData->AddEntry((TObject*)0, "Data:","");
	legendData->AddEntry(fractionOfGammasData0005,collisionSystem0005.Data(),"p");
	legendData->AddEntry(fractionOfGammasData0510,collisionSystem0510.Data(),"p");
	legendData->AddEntry(fractionOfGammasData1020,collisionSystem1020.Data(),"p");
	legendData->AddEntry(fractionOfGammasData2030,collisionSystem2030.Data(),"p");
	legendData->AddEntry(fractionOfGammasData3040,collisionSystem3040.Data(),"p");
	legendData->AddEntry(fractionOfGammasData4050,collisionSystem4050.Data(),"p");
	legendData->AddEntry(fractionOfGammasData5060,collisionSystem5060.Data(),"p");
	legendData->AddEntry(fractionOfGammasData6070,collisionSystem6070.Data(),"p");
// 	legendData->AddEntry(fractionOfGammasData2040,"20-40%","p");
// 	legendData->AddEntry(fractionOfGammasData4060,"40-60%","p");
// 	legendData->AddEntry(fractionOfGammasData6080,"60-80%","p");
	legendData->Draw();

	canvasNGammaEvtData->SaveAs(Form("%s/FractionOfPhotonsPerEvent_LHC11h.%s",outputDir.Data(),suffix.Data()));
	
	canvasNGammaEvtData->SetLogy(0);
	
	histo2DEff->GetYaxis()->SetRangeUser(25,40);
	histo2DEff->Draw("copy");
	fractionOfGammasData0005->Draw("pesame");
	fractionOfGammasLHC11h_hadCharm_0005->Draw("pesame");
	
	TLegend* legendData0005 = new TLegend(0.09,0.945,0.99,1.);
	legendData0005->SetFillColor(0);
	legendData0005->SetLineColor(0);
	legendData0005->SetTextSize(0.04);
	legendData0005->SetNColumns(8);
	legendData0005->AddEntry((TObject*)0,collisionSystem0005.Data(),"");
	legendData0005->AddEntry(fractionOfGammasData0005,"Data","p");
	legendData0005->AddEntry(fractionOfGammasLHC11h_hadCharm_0005,"MC","p");
	legendData0005->Draw();

	canvasNGammaEvtData->SaveAs(Form("%s/FractionOfPhotonsPerEvent_LHC11h_0005_hadCharm.%s",outputDir.Data(),suffix.Data()));

	
	histo2DEff->GetYaxis()->SetRangeUser(20,35);
	histo2DEff->Draw("copy");
	fractionOfGammasData0510->Draw("pesame");
	fractionOfGammasLHC11h_hadCharm_0510->Draw("pesame");
	
	TLegend* legendData0510 = new TLegend(0.09,0.945,0.99,1.);
	legendData0510->SetFillColor(0);
	legendData0510->SetLineColor(0);
	legendData0510->SetTextSize(0.04);
	legendData0510->SetNColumns(8);
	legendData0510->AddEntry((TObject*)0,collisionSystem0510.Data(),"");
	legendData0510->AddEntry(fractionOfGammasData0510,"Data","p");
	legendData0510->AddEntry(fractionOfGammasLHC11h_hadCharm_0510,"MC","p");
	legendData0510->Draw();

	canvasNGammaEvtData->SaveAs(Form("%s/FractionOfPhotonsPerEvent_LHC11h_0510_hadCharm.%s",outputDir.Data(),suffix.Data()));
	
	histo2DEff->GetYaxis()->SetRangeUser(16,30);
	histo2DEff->Draw("copy");
	fractionOfGammasData1020->Draw("pesame");
	fractionOfGammasLHC11h_hadCharm_1020->Draw("pesame");
	
	TLegend* legendData1020 = new TLegend(0.09,0.945,0.99,1.);
	legendData1020->SetFillColor(0);
	legendData1020->SetLineColor(0);
	legendData1020->SetTextSize(0.04);
	legendData1020->SetNColumns(8);
	legendData1020->AddEntry((TObject*)0,collisionSystem1020.Data(),"");
	legendData1020->AddEntry(fractionOfGammasData1020,"Data","p");
	legendData1020->AddEntry(fractionOfGammasLHC11h_hadCharm_1020,"MC","p");
	legendData1020->Draw();

	canvasNGammaEvtData->SaveAs(Form("%s/FractionOfPhotonsPerEvent_LHC11h_1020_hadCharm.%s",outputDir.Data(),suffix.Data()));

	histo2DEff->GetYaxis()->SetRangeUser(11,18);
	histo2DEff->Draw("copy");
	fractionOfGammasData2030->Draw("pesame");
	fractionOfGammasLHC11h_hadCharm_2030->Draw("pesame");
	
	TLegend* legendData2030 = new TLegend(0.09,0.945,0.99,1.);
	legendData2030->SetFillColor(0);
	legendData2030->SetLineColor(0);
	legendData2030->SetTextSize(0.04);
	legendData2030->SetNColumns(8);
	legendData2030->AddEntry((TObject*)0,collisionSystem2030.Data(),"");
	legendData2030->AddEntry(fractionOfGammasData2030,"Data","p");
	legendData2030->AddEntry(fractionOfGammasLHC11h_hadCharm_2030,"MC","p");
	legendData2030->Draw();

	canvasNGammaEvtData->SaveAs(Form("%s/FractionOfPhotonsPerEvent_LHC11h_2030_hadCharm.%s",outputDir.Data(),suffix.Data()));

	histo2DEff->GetYaxis()->SetRangeUser(7,11);
	histo2DEff->Draw("copy");
	fractionOfGammasData3040->Draw("pesame");
	fractionOfGammasLHC11h_hadCharm_3040->Draw("pesame");
	
	TLegend* legendData3040 = new TLegend(0.09,0.945,0.99,1.);
	legendData3040->SetFillColor(0);
	legendData3040->SetLineColor(0);
	legendData3040->SetTextSize(0.04);
	legendData3040->SetNColumns(8);
	legendData3040->AddEntry((TObject*)0,collisionSystem3040.Data(),"");
	legendData3040->AddEntry(fractionOfGammasData3040,"Data","p");
	legendData3040->AddEntry(fractionOfGammasLHC11h_hadCharm_3040,"MC","p");
	legendData3040->Draw();

	canvasNGammaEvtData->SaveAs(Form("%s/FractionOfPhotonsPerEvent_LHC11h_3040_hadCharm.%s",outputDir.Data(),suffix.Data()));

	histo2DEff->GetYaxis()->SetRangeUser(4.5,6);
	histo2DEff->Draw("copy");
	fractionOfGammasData4050->Draw("pesame");
	fractionOfGammasLHC11h_hadCharm_4050->Draw("pesame");
	
	TLegend* legendData4050 = new TLegend(0.09,0.945,0.99,1.);
	legendData4050->SetFillColor(0);
	legendData4050->SetLineColor(0);
	legendData4050->SetTextSize(0.04);
	legendData4050->SetNColumns(8);
	legendData4050->AddEntry((TObject*)0,collisionSystem4050.Data(),"");
	legendData4050->AddEntry(fractionOfGammasData4050,"Data","p");
	legendData4050->AddEntry(fractionOfGammasLHC11h_hadCharm_4050,"MC","p");
	legendData4050->Draw();

	canvasNGammaEvtData->SaveAs(Form("%s/FractionOfPhotonsPerEvent_LHC11h_4050_hadCharm.%s",outputDir.Data(),suffix.Data()));

	histo2DEff->GetYaxis()->SetRangeUser(2.,4.5);
	histo2DEff->Draw("copy");
	fractionOfGammasData5060->Draw("pesame");
	fractionOfGammasLHC11h_hadCharm_5060->Draw("pesame");
	
	TLegend* legendData5060 = new TLegend(0.09,0.945,0.99,1.);
	legendData5060->SetFillColor(0);
	legendData5060->SetLineColor(0);
	legendData5060->SetTextSize(0.04);
	legendData5060->SetNColumns(8);
	legendData5060->AddEntry((TObject*)0,collisionSystem5060.Data(),"");
	legendData5060->AddEntry(fractionOfGammasData5060,"Data","p");
	legendData5060->AddEntry(fractionOfGammasLHC11h_hadCharm_5060,"MC","p");
	legendData5060->Draw();

	canvasNGammaEvtData->SaveAs(Form("%s/FractionOfPhotonsPerEvent_LHC11h_5060_hadCharm.%s",outputDir.Data(),suffix.Data()));

	histo2DEff->GetYaxis()->SetRangeUser(1,2);
	histo2DEff->Draw("copy");
	fractionOfGammasData6070->Draw("pesame");
	
	TLegend* legendData6070 = new TLegend(0.09,0.945,0.99,1.);
	legendData6070->SetFillColor(0);
	legendData6070->SetLineColor(0);
	legendData6070->SetTextSize(0.04);
	legendData6070->SetNColumns(8);
	legendData6070->AddEntry(fractionOfGammasData6070,collisionSystem6070.Data(),"p");
	legendData6070->Draw();

	canvasNGammaEvtData->SaveAs(Form("%s/FractionOfPhotonsPerEvent_LHC11h_6070.%s",outputDir.Data(),suffix.Data()));

   cout << "Plot 2" << endl;
	TCanvas* canvasNPi0EvtData = new TCanvas("canvasNPi0EvtData","",200,10,1350,1000);  // gives the page size
	DrawGammaCanvasSettings( canvasNPi0EvtData, 0.09, 0.01, 0.06, 0.09);
 	canvasNPi0EvtData->SetLogy();
	
	TH2F * histo2DFracPi0;
	histo2DFracPi0 = new TH2F("histo2DFracPi0","histo2DFracPi0",2700,167900,170600,10000,0.0002,0.6);
// 	histo2DFracPi0->GetXaxis()->SetRangeUser(0.,2100.);
	SetStyleHistoTH2ForGraphs(histo2DFracPi0, "Run number","N_{#pi^{0}_{cand}}/N_{evt}",0.03,0.04, 0.03,0.04, 1.,1.);
	histo2DFracPi0->Draw("copy");

	fractionOfPi0Data0005->Draw("pesame");
	fractionOfPi0Data0510->Draw("pesame");
	fractionOfPi0Data1020->Draw("pesame");
	fractionOfPi0Data2030->Draw("pesame");
	fractionOfPi0Data3040->Draw("pesame");
	fractionOfPi0Data4050->Draw("pesame");
	fractionOfPi0Data5060->Draw("pesame");
	fractionOfPi0Data6070->Draw("pesame");
// 	fractionOfPi0Data2040->Draw("pesame");
// 	fractionOfPi0Data4060->Draw("pesame");
// 	fractionOfPi0Data6080->Draw("pesame");
	
	legendData->Draw();

	canvasNPi0EvtData->SaveAs(Form("%s/FractionOfPi0PerEvent_LHC11h.%s",outputDir.Data(),suffix.Data()));
	
	canvasNPi0EvtData->SetLogy(0);
	histo2DFracPi0->GetYaxis()->SetRangeUser(0,0.3);
	histo2DFracPi0->Draw("copy");

	fractionOfPi0Data0005->Draw("pesame");
	fractionOfPi0LHC11h_hadCharm_0005->Draw("pesame");
	legendData0005->Draw();

	canvasNPi0EvtData->SaveAs(Form("%s/FractionOfPi0PerEvent_LHC11h_0005_hadCharm.%s",outputDir.Data(),suffix.Data()));

	histo2DFracPi0->GetYaxis()->SetRangeUser(0,0.25);
	histo2DFracPi0->Draw("copy");

	fractionOfPi0Data0510->Draw("pesame");
	fractionOfPi0LHC11h_hadCharm_0510->Draw("pesame");
	legendData0510->Draw();

	canvasNPi0EvtData->SaveAs(Form("%s/FractionOfPi0PerEvent_LHC11h_0510_hadCharm.%s",outputDir.Data(),suffix.Data()));

	histo2DFracPi0->GetYaxis()->SetRangeUser(0,0.25);
	histo2DFracPi0->Draw("copy");

	fractionOfPi0Data1020->Draw("pesame");
	fractionOfPi0LHC11h_hadCharm_1020->Draw("pesame");
	legendData1020->Draw();

	canvasNPi0EvtData->SaveAs(Form("%s/FractionOfPi0PerEvent_LHC11h_1020_hadCharm.%s",outputDir.Data(),suffix.Data()));

	histo2DFracPi0->GetYaxis()->SetRangeUser(0,0.1);
	histo2DFracPi0->Draw("copy");

	fractionOfPi0Data2030->Draw("pesame");
	fractionOfPi0LHC11h_hadCharm_2030->Draw("pesame");
	legendData2030->Draw();

	canvasNPi0EvtData->SaveAs(Form("%s/FractionOfPi0PerEvent_LHC11h_2030_hadCharm.%s",outputDir.Data(),suffix.Data()));

	histo2DFracPi0->GetYaxis()->SetRangeUser(0,0.1);
	histo2DFracPi0->Draw("copy");

	fractionOfPi0Data3040->Draw("pesame");
	fractionOfPi0LHC11h_hadCharm_3040->Draw("pesame");
	legendData3040->Draw();

	canvasNPi0EvtData->SaveAs(Form("%s/FractionOfPi0PerEvent_LHC11h_3040_hadCharm.%s",outputDir.Data(),suffix.Data()));

	histo2DFracPi0->GetYaxis()->SetRangeUser(0,0.07);
	histo2DFracPi0->Draw("copy");

	fractionOfPi0Data4050->Draw("pesame");
	fractionOfPi0LHC11h_hadCharm_4050->Draw("pesame");
	legendData4050->Draw();

	canvasNPi0EvtData->SaveAs(Form("%s/FractionOfPi0PerEvent_LHC11h_4050_hadCharm.%s",outputDir.Data(),suffix.Data()));

	histo2DFracPi0->GetYaxis()->SetRangeUser(0,0.07);
	histo2DFracPi0->Draw("copy");

	fractionOfPi0Data5060->Draw("pesame");
	fractionOfPi0LHC11h_hadCharm_5060->Draw("pesame");
	legendData5060->Draw();

	canvasNPi0EvtData->SaveAs(Form("%s/FractionOfPi0PerEvent_LHC11h_5060_hadCharm.%s",outputDir.Data(),suffix.Data()));

	histo2DFracPi0->GetYaxis()->SetRangeUser(0,0.02);
	histo2DFracPi0->Draw("copy");

	fractionOfPi0Data6070->Draw("pesame");
// 	fractionOfPi0LHC11h_hadCharm_6070->Draw("pesame");
	legendData6070->Draw();

	canvasNPi0EvtData->SaveAs(Form("%s/FractionOfPi0PerEvent_LHC11h_6070_hadCharm.%s",outputDir.Data(),suffix.Data()));
	
	delete canvasNPi0EvtData;

	
	
	
   cout << "Plot 3" << endl;
	TCanvas* canvasMassPi0Data = new TCanvas("canvasMassPi0Data","",200,10,1350,1000);  // gives the page size
	DrawGammaCanvasSettings( canvasMassPi0Data, 0.09, 0.01, 0.06, 0.09);
	
	TH2F * histo2DMassPi0;
	histo2DMassPi0 = new TH2F("histo2DMassPi0","histo2DMassPi0",2700,167900,170600,100,0.125,0.15);
// 	histo2DMassPi0->GetXaxis()->SetRangeUser(0.,2100.);
	SetStyleHistoTH2ForGraphs(histo2DMassPi0, "Run number","m_{#pi^{0}} (GeV/c^{2})",0.03,0.04, 0.03,0.04, 1.,1.15);
	histo2DMassPi0->Draw("copy");

	massPi0Data0005->Draw("pesame");
	massPi0Data0510->Draw("pesame");
	massPi0Data1020->Draw("pesame");
	massPi0Data2030->Draw("pesame");
	massPi0Data3040->Draw("pesame");
	massPi0Data4050->Draw("pesame");
	massPi0Data5060->Draw("pesame");
	massPi0Data6070->Draw("pesame");
	DrawGammaLines(167900, 170600.,0.135, 0.135,1,kGray+2);
	legendData->Draw();

	canvasMassPi0Data->SaveAs(Form("%s/MassPi0_PbPb_LHC11h.%s",outputDir.Data(),suffix.Data()));
	delete canvasMassPi0Data;

	TCanvas* canvasMassEtaData = new TCanvas("canvasMassEtaData","",200,10,1350,1000);  // gives the page size
	DrawGammaCanvasSettings( canvasMassEtaData, 0.09, 0.01, 0.06, 0.09);
	
	TH2F * histo2DMassEta;
	histo2DMassEta = new TH2F("histo2DMassEta","histo2DMassEta",2700,167900,170600,100,0.5,0.6);
// 	histo2DMassEta->GetXaxis()->SetRangeUser(0.,2100.);
	SetStyleHistoTH2ForGraphs(histo2DMassEta, "Run number","m_{#eta} (GeV/c^{2})",0.03,0.04, 0.03,0.04, 1.,1.15);
	histo2DMassEta->Draw("copy");

	massEtaData0005->Draw("pesame");
	massEtaData0510->Draw("pesame");
	massEtaData1020->Draw("pesame");
	massEtaData2030->Draw("pesame");
	massEtaData3040->Draw("pesame");
	massEtaData4050->Draw("pesame");
	massEtaData5060->Draw("pesame");
	massEtaData6070->Draw("pesame");
	DrawGammaLines(167900, 170600.,0.547853, 0.547853,1,kGray+2);
	legendData->Draw();

	canvasMassEtaData->SaveAs(Form("%s/MassEta_PbPb_LHC11h.%s",outputDir.Data(),suffix.Data()));
	delete canvasMassEtaData;
	
   cout << "Plot 4" << endl;
	TCanvas* canvasWidthPi0Data = new TCanvas("canvasWidthPi0Data","",200,10,1350,1000);  // gives the page size
	DrawGammaCanvasSettings( canvasWidthPi0Data, 0.09, 0.01, 0.06, 0.09);
	
	TH2F * histo2DWidthPi0;
	histo2DWidthPi0 = new TH2F("histo2DWidthPi0","histo2DWidthPi0",2700,167900,170600,100,0.0,0.042);
// 	histo2DWidthPi0->GetXaxis()->SetRangeUser(0.,2100.);
	SetStyleHistoTH2ForGraphs(histo2DWidthPi0, "Run number","FWHM_{#pi^{0}} (GeV/c^{2})",0.03,0.04, 0.03,0.04, 1.,1.15);
	histo2DWidthPi0->Draw("copy");

	widthPi0Data0005->Draw("pesame");
	widthPi0Data0510->Draw("pesame");
	widthPi0Data1020->Draw("pesame");
	widthPi0Data2030->Draw("pesame");
	widthPi0Data3040->Draw("pesame");
	widthPi0Data4050->Draw("pesame");
	widthPi0Data5060->Draw("pesame");
	widthPi0Data6070->Draw("pesame");
	legendData->Draw();

	canvasWidthPi0Data->SaveAs(Form("%s/WidthPi0_PbPb_LHC11h.%s",outputDir.Data(),suffix.Data()));
	delete canvasWidthPi0Data;
   
   cout << "Plot 5" << endl;
	TCanvas* canvasMultTPCData = new TCanvas("canvasMultTPCData","",200,10,1350,1000);  // gives the page size
	DrawGammaCanvasSettings( canvasMultTPCData, 0.09, 0.01, 0.06, 0.09);
// 	canvasMultTPCData->SetLogy();
	
	TH2F * histoMultTPC;
	histoMultTPC = new TH2F("histoMultTPC","histoMultTPC",2700,167900,170600,3000,0,3000);
// 	histoMultTPC->GetXaxis()->SetRangeUser(0.,2100.);
	SetStyleHistoTH2ForGraphs(histoMultTPC, "Run number","#LT n tracks TPC #GT",0.03,0.04, 0.03,0.04, 1.,1.2);
	histoMultTPC->Draw("copy");


	meanTrackMultTPCData0005->Draw("pesame");
	meanTrackMultTPCData0510->Draw("pesame");
	meanTrackMultTPCData1020->Draw("pesame");
	meanTrackMultTPCData2030->Draw("pesame");
	meanTrackMultTPCData3040->Draw("pesame");
	meanTrackMultTPCData4050->Draw("pesame");
	meanTrackMultTPCData5060->Draw("pesame");
	meanTrackMultTPCData6070->Draw("pesame");
	
	TLegend* legendMultTPC = new TLegend(0.085,0.945,0.99,1.);
	legendMultTPC->SetFillColor(0);
	legendMultTPC->SetLineColor(0);
	legendMultTPC->SetTextSize(0.04);
	legendMultTPC->SetNColumns(8);
// 	legendMultTPC->AddEntry((TObject*)0, "Data:","");
	legendMultTPC->AddEntry(meanTrackMultTPCData0005,"0-5%","p");
	legendMultTPC->AddEntry(meanTrackMultTPCData0510,"5-10%","p");
	legendMultTPC->AddEntry(meanTrackMultTPCData1020,"10-20%","p");
	legendMultTPC->AddEntry(meanTrackMultTPCData2030,"20-30%","p");
	legendMultTPC->AddEntry(meanTrackMultTPCData3040,"30-40%","p");
	legendMultTPC->AddEntry(meanTrackMultTPCData4050,"40-50%","p");
	legendMultTPC->AddEntry(meanTrackMultTPCData5060,"50-60%","p");
	legendMultTPC->AddEntry(meanTrackMultTPCData6070,"60-70%","p");
	legendMultTPC->Draw();

	canvasMultTPCData->SaveAs(Form("%s/MeanMultiplicity_TPCTracks_LHC11hAOD.%s",outputDir.Data(),suffix.Data()));
	

	histoMultTPC->GetYaxis()->SetRangeUser(2750,2950);
	histoMultTPC->Draw("copy");
	meanTrackMultTPCData0005->Draw("pesame");
	
	TLegend* legendMultTPC0005 = new TLegend(0.09,0.945,0.99,1.);
	legendMultTPC0005->SetFillColor(0);
	legendMultTPC0005->SetLineColor(0);
	legendMultTPC0005->SetTextSize(0.04);
	legendMultTPC0005->SetNColumns(4);
// 	legendMultTPC0005->AddEntry((TObject*)0, "Data:","");
	legendMultTPC0005->AddEntry(meanTrackMultTPCData0005,collisionSystem0005.Data(),"p");
	legendMultTPC0005->Draw();

	canvasMultTPCData->SaveAs(Form("%s/MeanMultiplicity_TPCTracks_LHC11hAOD_0005.%s",outputDir.Data(),suffix.Data()));

	histoMultTPC->GetYaxis()->SetRangeUser(2250,2500);
	histoMultTPC->Draw("copy");
	meanTrackMultTPCData0510->Draw("pesame");
	
	TLegend* legendMultTPC0510 = new TLegend(0.09,0.945,0.99,1.);
	legendMultTPC0510->SetFillColor(0);
	legendMultTPC0510->SetLineColor(0);
	legendMultTPC0510->SetTextSize(0.04);
	legendMultTPC0510->SetNColumns(4);
// 	legendMultTPC0510->AddEntry((TObject*)0, "Data:","");
	legendMultTPC0510->AddEntry(meanTrackMultTPCData0510,collisionSystem0510.Data(),"p");
	legendMultTPC0510->Draw();

	canvasMultTPCData->SaveAs(Form("%s/MeanMultiplicity_TPCTracks_LHC11hAOD_0510.%s",outputDir.Data(),suffix.Data()));

	histoMultTPC->GetYaxis()->SetRangeUser(1650,2100);
	histoMultTPC->Draw("copy");
	meanTrackMultTPCData1020->Draw("pesame");
	
	TLegend* legendMultTPC1020 = new TLegend(0.09,0.945,0.99,1.);
	legendMultTPC1020->SetFillColor(0);
	legendMultTPC1020->SetLineColor(0);
	legendMultTPC1020->SetTextSize(0.04);
	legendMultTPC1020->SetNColumns(4);
// 	legendMultTPC1020->AddEntry((TObject*)0, "Data:","");
	legendMultTPC1020->AddEntry(meanTrackMultTPCData1020,collisionSystem1020.Data(),"p");
	legendMultTPC1020->Draw();

	canvasMultTPCData->SaveAs(Form("%s/MeanMultiplicity_TPCTracks_LHC11hAOD_1020.%s",outputDir.Data(),suffix.Data()));
	
	histoMultTPC->GetYaxis()->SetRangeUser(1000,1250);
	histoMultTPC->Draw("copy");
	meanTrackMultTPCData2030->Draw("pesame");
	
	TLegend* legendMultTPC2030 = new TLegend(0.09,0.945,0.99,1.);
	legendMultTPC2030->SetFillColor(0);
	legendMultTPC2030->SetLineColor(0);
	legendMultTPC2030->SetTextSize(0.04);
	legendMultTPC2030->SetNColumns(4);
// 	legendMultTPC2030->AddEntry((TObject*)0, "Data:","");
	legendMultTPC2030->AddEntry(meanTrackMultTPCData2030,collisionSystem2030.Data(),"p");
	legendMultTPC2030->Draw();

	canvasMultTPCData->SaveAs(Form("%s/MeanMultiplicity_TPCTracks_LHC11hAOD_2030.%s",outputDir.Data(),suffix.Data()));
	
	histoMultTPC->GetYaxis()->SetRangeUser(600,800);
	histoMultTPC->Draw("copy");
	meanTrackMultTPCData3040->Draw("pesame");
	
	TLegend* legendMultTPC3040 = new TLegend(0.09,0.945,0.99,1.);
	legendMultTPC3040->SetFillColor(0);
	legendMultTPC3040->SetLineColor(0);
	legendMultTPC3040->SetTextSize(0.04);
	legendMultTPC3040->SetNColumns(4);
// 	legendMultTPC3040->AddEntry((TObject*)0, "Data:","");
	legendMultTPC3040->AddEntry(meanTrackMultTPCData3040,collisionSystem3040.Data(),"p");
	legendMultTPC3040->Draw();

	canvasMultTPCData->SaveAs(Form("%s/MeanMultiplicity_TPCTracks_LHC11hAOD_3040.%s",outputDir.Data(),suffix.Data()));
	
	histoMultTPC->GetYaxis()->SetRangeUser(400,500);
	histoMultTPC->Draw("copy");
	meanTrackMultTPCData4050->Draw("pesame");
	
	TLegend* legendMultTPC4050 = new TLegend(0.09,0.945,0.99,1.);
	legendMultTPC4050->SetFillColor(0);
	legendMultTPC4050->SetLineColor(0);
	legendMultTPC4050->SetTextSize(0.04);
	legendMultTPC4050->SetNColumns(4);
// 	legendMultTPC4050->AddEntry((TObject*)0, "Data:","");
	legendMultTPC4050->AddEntry(meanTrackMultTPCData4050,collisionSystem4050.Data(),"p");
	legendMultTPC4050->Draw();

	canvasMultTPCData->SaveAs(Form("%s/MeanMultiplicity_TPCTracks_LHC11hAOD_4050.%s",outputDir.Data(),suffix.Data()));
	
	histoMultTPC->GetYaxis()->SetRangeUser(200,350);
	histoMultTPC->Draw("copy");
	meanTrackMultTPCData5060->Draw("pesame");
	
	TLegend* legendMultTPC5060 = new TLegend(0.09,0.945,0.99,1.);
	legendMultTPC5060->SetFillColor(0);
	legendMultTPC5060->SetLineColor(0);
	legendMultTPC5060->SetTextSize(0.04);
	legendMultTPC5060->SetNColumns(4);
// 	legendMultTPC5060->AddEntry((TObject*)0, "Data:","");
	legendMultTPC5060->AddEntry(meanTrackMultTPCData5060,collisionSystem5060.Data(),"p");
	legendMultTPC5060->Draw();

	canvasMultTPCData->SaveAs(Form("%s/MeanMultiplicity_TPCTracks_LHC11hAOD_5060.%s",outputDir.Data(),suffix.Data()));

	histoMultTPC->GetYaxis()->SetRangeUser(100,160);
	histoMultTPC->Draw("copy");
	meanTrackMultTPCData6070->Draw("pesame");
	
	TLegend* legendMultTPC6070 = new TLegend(0.09,0.945,0.99,1.);
	legendMultTPC6070->SetFillColor(0);
	legendMultTPC6070->SetLineColor(0);
	legendMultTPC6070->SetTextSize(0.04);
	legendMultTPC6070->SetNColumns(4);
// 	legendMultTPC6070->AddEntry((TObject*)0, "Data:","");
	legendMultTPC6070->AddEntry(meanTrackMultTPCData6070,collisionSystem6070.Data(),"p");
	legendMultTPC6070->Draw();

	canvasMultTPCData->SaveAs(Form("%s/MeanMultiplicity_TPCTracks_LHC11hAOD_6070.%s",outputDir.Data(),suffix.Data()));
		
	delete canvasMultTPCData;

   
	TCanvas* canvasMultTPCComb = new TCanvas("canvasMultTPCComb","",200,10,1350,1000);  // gives the page size
	DrawGammaCanvasSettings( canvasMultTPCComb, 0.09, 0.01, 0.06, 0.09);
// 	canvasMultTPCComb->SetLogy();
	
	histoMultTPC->GetYaxis()->SetRangeUser(0,1950);
	histoMultTPC->Draw("copy");


// 	meanTrackMultTPCData0005->Draw("pesame");
// 	meanTrackMultTPCData0510->Draw("pesame");
// 	meanTrackMultTPCData1020->Draw("pesame");
// 	meanTrackMultTPCData2040->Draw("pesame");
// 	meanTrackMultTPCData4060->Draw("pesame");
// 	meanTrackMultTPCData6080->Draw("pesame");
	
	meanTrackMultTPCLHC11h_hadCharm_0005->Draw("pesame");
	meanTrackMultTPCLHC11h_hadCharm_0510->Draw("pesame");
	meanTrackMultTPCLHC11h_hadCharm_1020->Draw("pesame");
	meanTrackMultTPCLHC11h_hadCharm_2030->Draw("pesame");
	meanTrackMultTPCLHC11h_hadCharm_3040->Draw("pesame");
	meanTrackMultTPCLHC11h_hadCharm_4050->Draw("pesame");
	meanTrackMultTPCLHC11h_hadCharm_5060->Draw("pesame");	
	
// 	TLegend* legendMultTPCComb = new TLegend(0.07,0.945,0.99,1.);
// 	legendMultTPCComb->SetFillColor(0);
// 	legendMultTPCComb->SetLineColor(0);
// 	legendMultTPCComb->SetTextSize(0.04);
// 	legendMultTPCComb->SetNColumns(7);
// 	legendMultTPCComb->AddEntry((TObject*)0, "Data:","");
// 	legendMultTPCComb->AddEntry(meanTrackMultTPCData0005,"0-5%","p");
// 	legendMultTPCComb->AddEntry(meanTrackMultTPCData0510,"5-10%","p");
// 	legendMultTPCComb->AddEntry(meanTrackMultTPCData1020,"10-20%","p");
// 	legendMultTPCComb->AddEntry(meanTrackMultTPCData2040,"20-40%","p");
// 	legendMultTPCComb->AddEntry(meanTrackMultTPCData4060,"40-60%","p");
// 	legendMultTPCComb->AddEntry(meanTrackMultTPCData6080,"60-80%","p");
// 	legendMultTPCComb->Draw();

// 	TLegend* legendMultMC = new TLegend(0.07,0.885,0.99,0.945);
	TLegend* legendMultMC = new TLegend(0.07,0.945,0.99,1.);
	legendMultMC->SetFillColor(0);
	legendMultMC->SetLineColor(0);
	legendMultMC->SetTextSize(0.04);
	legendMultMC->SetNColumns(8);
	legendMultMC->AddEntry((TObject*)0, "MC:  ","");
	legendMultMC->AddEntry(meanTrackMultTPCLHC11h_hadCharm_0005,"0-5%","p");
	legendMultMC->AddEntry(meanTrackMultTPCLHC11h_hadCharm_0510,"5-10%","p");
	legendMultMC->AddEntry(meanTrackMultTPCLHC11h_hadCharm_1020,"10-20%","p");
	legendMultMC->AddEntry(meanTrackMultTPCLHC11h_hadCharm_2030,"20-30%","p");
	legendMultMC->AddEntry(meanTrackMultTPCLHC11h_hadCharm_3040,"30-40%","p");
	legendMultMC->AddEntry(meanTrackMultTPCLHC11h_hadCharm_4050,"40-50%","p");
	legendMultMC->AddEntry(meanTrackMultTPCLHC11h_hadCharm_5060,"50-60%","p");
	legendMultMC->Draw();


	canvasMultTPCComb->SaveAs(Form("%s/MeanMultiplicity_TPCTracks_LHC11h_hadCharm.%s",outputDir.Data(),suffix.Data()));
   
//    cout << "Plot 7" << endl;
//    canvasMultTPCComb->cd();
//    histoMultTPC->Draw("copy");
// 
// 
//    meanTrackMultTPCData0005->Draw("pesame");
//    meanTrackMultTPCData0510->Draw("pesame");
//    meanTrackMultTPCData1020->Draw("pesame");
//    meanTrackMultTPCData2040->Draw("pesame");
//    meanTrackMultTPCData4060->Draw("pesame");
//    meanTrackMultTPCData6080->Draw("pesame");
//    
//    meanTrackMultTPCLHC13d20005->Draw("pesame");
//    meanTrackMultTPCLHC13d20510->Draw("pesame");
//    meanTrackMultTPCLHC13d21020->Draw("pesame");
//    meanTrackMultTPCLHC13d22040->Draw("pesame");
//    meanTrackMultTPCLHC13d24060->Draw("pesame");
//    meanTrackMultTPCLHC13d26080->Draw("pesame");
//    
//    legendMultTPCComb->Draw();
// 
//    TLegend* legendMultMC2 = new TLegend(0.07,0.885,0.99,0.945);
//    legendMultMC2->SetFillColor(0);
//    legendMultMC2->SetLineColor(0);
//    legendMultMC2->SetTextSize(0.04);
//    legendMultMC2->SetNColumns(7);
//    legendMultMC2->AddEntry((TObject*)0, "MC:  ","");
//    legendMultMC2->AddEntry(meanTrackMultTPCLHC13d20005,"0-5%","p");
//    legendMultMC2->AddEntry(meanTrackMultTPCLHC13d20510,"5-10%","p");
//    legendMultMC2->AddEntry(meanTrackMultTPCLHC13d21020,"10-20%","p");
//    legendMultMC2->AddEntry(meanTrackMultTPCLHC13d22040,"20-40%","p");
//    legendMultMC2->AddEntry(meanTrackMultTPCLHC13d24060,"40-60%","p");
//    legendMultMC2->AddEntry(meanTrackMultTPCLHC13d26080,"60-80%","p");
//    legendMultMC2->Draw();
// 
// 
//    canvasMultTPCComb->SaveAs(Form("%s/MeanMultiplicity_TPCTracks_LHC13d2.%s",outputDir.Data(),suffix.Data()));
   
// 	delete canvasMultTPCComb;

   

//    cout << "Plot 11" << endl;
// 	TCanvas* canvasNGammaEvtComb = new TCanvas("canvasNGammaEvtComb","",200,10,1350,1000);  // gives the page size
// 	DrawGammaCanvasSettings( canvasNGammaEvtComb, 0.1, 0.04, 0.12, 0.09);
// 	canvasNGammaEvtComb->SetLogy();
// 	
// 	histo2DEff->Draw("copy");
// 	fractionOfGammasData0005->Draw("pesame");
// 	fractionOfGammasData0510->Draw("pesame");
// 	fractionOfGammasData1020->Draw("pesame");
// 	fractionOfGammasData2040->Draw("pesame");
// 	fractionOfGammasData4060->Draw("pesame");
// 	fractionOfGammasData6080->Draw("pesame");
// 
// 	fractionOfGammasLHC11h_hadCharm_0005->Draw("pesame");
// 	fractionOfGammasLHC11h_hadCharm_0510->Draw("pesame");
// 	fractionOfGammasLHC11h_hadCharm_1020->Draw("pesame");
// 	fractionOfGammasLHC11h_hadCharm_2030->Draw("pesame");
// 	fractionOfGammasLHC11h_hadCharm_3040->Draw("pesame");
// 	fractionOfGammasLHC11h_hadCharm_4050->Draw("pesame");
// 
// 	TLegend* legendDataComb = new TLegend(0.07,0.945,0.99,1.);
// 	legendDataComb->SetFillColor(0);
// 	legendDataComb->SetLineColor(0);
// 	legendDataComb->SetTextSize(0.04);
// 	legendDataComb->SetNColumns(7);
// 	legendDataComb->AddEntry((TObject*)0, "Data:","");
// 	legendDataComb->AddEntry(fractionOfGammasData0005,"0-5%","p");
// 	legendDataComb->AddEntry(fractionOfGammasData0510,"5-10%","p");
// 	legendDataComb->AddEntry(fractionOfGammasData1020,"10-20%","p");
// 	legendDataComb->AddEntry(fractionOfGammasData2040,"20-40%","p");
// 	legendDataComb->AddEntry(fractionOfGammasData4060,"40-60%","p");
// 	legendDataComb->AddEntry(fractionOfGammasData6080,"60-80%","p");
// 	legendDataComb->Draw();
// 
// 	TLegend* legendMC = new TLegend(0.07,0.885,0.99,0.945);
// 	legendMC->SetFillColor(0);
// 	legendMC->SetLineColor(0);
// 	legendMC->SetTextSize(0.04);
// 	legendMC->SetNColumns(7);
// 	legendMC->AddEntry((TObject*)0, "MC:  ","");
// 	legendMC->AddEntry(fractionOfGammasLHC11h_hadCharm_0005,"0-5%","p");
// 	legendMC->AddEntry(fractionOfGammasLHC11h_hadCharm_0510,"5-10%","p");
// 	legendMC->AddEntry(fractionOfGammasLHC11h_hadCharm_1020,"10-20%","p");
// 	legendMC->AddEntry(fractionOfGammasLHC11h_hadCharm_2030,"20-40%","p");
// 	legendMC->AddEntry(fractionOfGammasLHC11h_hadCharm_3040,"40-60%","p");
// 	legendMC->AddEntry(fractionOfGammasLHC11h_hadCharm_4050,"60-80%","p");
// 	legendMC->Draw();
// 
// 	canvasNGammaEvtComb->SaveAs(Form("%s/FractionOfPhotonsPerEvent_WithMCLHC11h_hadCharm_.%s",outputDir.Data(),suffix.Data()));
// 	delete canvasNGammaEvtComb;



//    cout << "Plot 23" << endl;
// 	TCanvas* canvasNGammaEvtLHC13d2 = new TCanvas("canvasNGammaEvtLHC13d2","",200,10,1350,1000);  // gives the page size
// 	DrawGammaCanvasSettings( canvasNGammaEvtLHC13d2, 0.1, 0.04, 0.12, 0.09);
// 	canvasNGammaEvtLHC13d2->SetLogy();
// 	
// 	histo2DEff->Draw("copy");
// 
// 	fractionOfGammasData0005->Draw("pesame");
// 	fractionOfGammasData0510->Draw("pesame");
// 	fractionOfGammasData1020->Draw("pesame");
// 	fractionOfGammasData2040->Draw("pesame");
// 	fractionOfGammasData4060->Draw("pesame");
// 	fractionOfGammasData6080->Draw("pesame");
// 
// 	fractionOfGammasLHC13d20005->Draw("pesame");
// 	fractionOfGammasLHC13d20510->Draw("pesame");
// 	fractionOfGammasLHC13d21020->Draw("pesame");
// 	fractionOfGammasLHC13d22040->Draw("pesame");
// 	fractionOfGammasLHC13d24060->Draw("pesame");
// 	fractionOfGammasLHC13d26080->Draw("pesame");
// 
// 	legendDataComb->Draw();
// 	legendMC->Draw();
// 
// 	canvasNGammaEvtLHC13d2->SaveAs(Form("%s/FractionOfPhotonsPerEvent_WithMCLHC13d2.%s",outputDir.Data(),suffix.Data()));
// 	delete canvasNGammaEvtLHC13d2;


}
