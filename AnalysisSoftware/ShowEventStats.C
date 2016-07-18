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

void ShowEventStats(TString suffix = "eps"){
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
		TGraphErrors* fractionOfGammasData0005 = (TGraphErrors*)EventStatsFile->Get("fracGammas_0005_LHC10h");
		TGraphErrors* fractionOfGammasData0510 = (TGraphErrors*)EventStatsFile->Get("fracGammas_0510_LHC10h");
// 		TGraphErrors* fractionOfGammas0010 = (TGraphErrors*)EventStatsFile->Get("fracGammas_LHC10h_0010");
		TGraphErrors* fractionOfGammasData1020 = (TGraphErrors*)EventStatsFile->Get("fracGammas_1020_LHC10h");
		TGraphErrors* fractionOfGammasData2040 = (TGraphErrors*)EventStatsFile->Get("fracGammas_2040_LHC10h");
		TGraphErrors* fractionOfGammasData4060 = (TGraphErrors*)EventStatsFile->Get("fracGammas_4060_LHC10h");
		TGraphErrors* fractionOfGammasData6080 = (TGraphErrors*)EventStatsFile->Get("fracGammas_6080_LHC10h");

		TGraphErrors* fractionOfPi0Data0005 = (TGraphErrors*)EventStatsFile->Get("fractionOfPi0InCent_0005_LHC10h");
		TGraphErrors* fractionOfPi0Data0510 = (TGraphErrors*)EventStatsFile->Get("fractionOfPi0InCent_0510_LHC10h");
// 		TGraphErrors* fractionOfGammas0010 = (TGraphErrors*)EventStatsFile->Get("fractionOfPi0InCent_LHC10h_0010");
		TGraphErrors* fractionOfPi0Data1020 = (TGraphErrors*)EventStatsFile->Get("fractionOfPi0InCent_1020_LHC10h");
		TGraphErrors* fractionOfPi0Data2040 = (TGraphErrors*)EventStatsFile->Get("fractionOfPi0InCent_2040_LHC10h");
		TGraphErrors* fractionOfPi0Data4060 = (TGraphErrors*)EventStatsFile->Get("fractionOfPi0InCent_4060_LHC10h");
		TGraphErrors* fractionOfPi0Data6080 = (TGraphErrors*)EventStatsFile->Get("fractionOfPi0InCent_6080_LHC10h");

		TGraphErrors* massPi0Data0005 = (TGraphErrors*)EventStatsFile->Get("massPi0perRun_0005_LHC10h");
		TGraphErrors* massPi0Data0510 = (TGraphErrors*)EventStatsFile->Get("massPi0perRun_0510_LHC10h");
// 		TGraphErrors* massGammas0010 = (TGraphErrors*)EventStatsFile->Get("massPi0perRun_LHC10h_0010");
		TGraphErrors* massPi0Data1020 = (TGraphErrors*)EventStatsFile->Get("massPi0perRun_1020_LHC10h");
		TGraphErrors* massPi0Data2040 = (TGraphErrors*)EventStatsFile->Get("massPi0perRun_2040_LHC10h");
		TGraphErrors* massPi0Data4060 = (TGraphErrors*)EventStatsFile->Get("massPi0perRun_4060_LHC10h");
		TGraphErrors* massPi0Data6080 = (TGraphErrors*)EventStatsFile->Get("massPi0perRun_6080_LHC10h");

		TGraphErrors* widthPi0Data0005 = (TGraphErrors*)EventStatsFile->Get("widthPi0perRun_0005_LHC10h");
		TGraphErrors* widthPi0Data0510 = (TGraphErrors*)EventStatsFile->Get("widthPi0perRun_0510_LHC10h");
// 		TGraphErrors* widthGammas0010 = (TGraphErrors*)EventStatsFile->Get("widthPi0perRun_LHC10h_0010");
		TGraphErrors* widthPi0Data1020 = (TGraphErrors*)EventStatsFile->Get("widthPi0perRun_1020_LHC10h");
		TGraphErrors* widthPi0Data2040 = (TGraphErrors*)EventStatsFile->Get("widthPi0perRun_2040_LHC10h");
		TGraphErrors* widthPi0Data4060 = (TGraphErrors*)EventStatsFile->Get("widthPi0perRun_4060_LHC10h");
		TGraphErrors* widthPi0Data6080 = (TGraphErrors*)EventStatsFile->Get("widthPi0perRun_6080_LHC10h");

		TGraphErrors* fractionOfGoodEventsData0005 = (TGraphErrors*)EventStatsFile->Get("fracGoodEvents_0005_LHC10h");
		TGraphErrors* fractionOfGoodEventsData0510 = (TGraphErrors*)EventStatsFile->Get("fracGoodEvents_0510_LHC10h");
// 		TGraphErrors* fractionOfGoodEvents0010 = (TGraphErrors*)EventStatsFile->Get("fracGoodEvents_LHC10h_0010");
		TGraphErrors* fractionOfGoodEventsData1020 = (TGraphErrors*)EventStatsFile->Get("fracGoodEvents_1020_LHC10h");
		TGraphErrors* fractionOfGoodEventsData2040 = (TGraphErrors*)EventStatsFile->Get("fracGoodEvents_2040_LHC10h");
		TGraphErrors* fractionOfGoodEventsData4060 = (TGraphErrors*)EventStatsFile->Get("fracGoodEvents_4060_LHC10h");
		TGraphErrors* fractionOfGoodEventsData6080 = (TGraphErrors*)EventStatsFile->Get("fracGoodEvents_6080_LHC10h");
		
		TGraphErrors* fractionOfWOVtxData0005 = (TGraphErrors*)EventStatsFile->Get("fracWOVtx_0005_LHC10h");
		TGraphErrors* fractionOfWOVtxData0510 = (TGraphErrors*)EventStatsFile->Get("fracWOVtx_0510_LHC10h");
// 		TGraphErrors* fractionOfWOVtx0010 = (TGraphErrors*)EventStatsFile->Get("fracWOVtx_LHC10h_0010");
		TGraphErrors* fractionOfWOVtxData1020 = (TGraphErrors*)EventStatsFile->Get("fracWOVtx_1020_LHC10h");
		TGraphErrors* fractionOfWOVtxData2040 = (TGraphErrors*)EventStatsFile->Get("fracWOVtx_2040_LHC10h");
		TGraphErrors* fractionOfWOVtxData4060 = (TGraphErrors*)EventStatsFile->Get("fracWOVtx_4060_LHC10h");
		TGraphErrors* fractionOfWOVtxData6080 = (TGraphErrors*)EventStatsFile->Get("fracWOVtx_6080_LHC10h");

		TGraphErrors* fractionOfWVtxOutside10cmData0005 = (TGraphErrors*)EventStatsFile->Get("fracWVtxOutside10cm_0005_LHC10h");
		TGraphErrors* fractionOfWVtxOutside10cmData0510 = (TGraphErrors*)EventStatsFile->Get("fracWVtxOutside10cm_0510_LHC10h");
// 		TGraphErrors* fractionOfWVtxOutside10cm0010 = (TGraphErrors*)EventStatsFile->Get("fracWVtxOutside10cm_LHC10h_0010");
		TGraphErrors* fractionOfWVtxOutside10cmData1020 = (TGraphErrors*)EventStatsFile->Get("fracWVtxOutside10cm_1020_LHC10h");
		TGraphErrors* fractionOfWVtxOutside10cmData2040 = (TGraphErrors*)EventStatsFile->Get("fracWVtxOutside10cm_2040_LHC10h");
		TGraphErrors* fractionOfWVtxOutside10cmData4060 = (TGraphErrors*)EventStatsFile->Get("fracWVtxOutside10cm_4060_LHC10h");
		TGraphErrors* fractionOfWVtxOutside10cmData6080 = (TGraphErrors*)EventStatsFile->Get("fracWVtxOutside10cm_6080_LHC10h");


		TGraphErrors* fractionOfPileUpData0005 = (TGraphErrors*)EventStatsFile->Get("fracPileUp_0005_LHC10h");
		TGraphErrors* fractionOfPileUpData0510 = (TGraphErrors*)EventStatsFile->Get("fracPileUp_0510_LHC10h");
// 		TGraphErrors* fractionOfPileUp0010 = (TGraphErrors*)EventStatsFile->Get("fracPileUp_LHC10h_0010");
		TGraphErrors* fractionOfPileUpData1020 = (TGraphErrors*)EventStatsFile->Get("fracPileUp_1020_LHC10h");
		TGraphErrors* fractionOfPileUpData2040 = (TGraphErrors*)EventStatsFile->Get("fracPileUp_2040_LHC10h");
		TGraphErrors* fractionOfPileUpData4060 = (TGraphErrors*)EventStatsFile->Get("fracPileUp_4060_LHC10h");
		TGraphErrors* fractionOfPileUpData6080 = (TGraphErrors*)EventStatsFile->Get("fracPileUp_6080_LHC10h");
		
		TGraphErrors* fractionOfNormAllData0005 = (TGraphErrors*)EventStatsFile->Get("fracNormAll_0005_LHC10h");
		TGraphErrors* fractionOfNormAllData0510 = (TGraphErrors*)EventStatsFile->Get("fracNormAll_0510_LHC10h");
// 		TGraphErrors* fractionOfNormAll0010 = (TGraphErrors*)EventStatsFile->Get("fracNormAll_LHC10h_0010");
		TGraphErrors* fractionOfNormAllData1020 = (TGraphErrors*)EventStatsFile->Get("fracNormAll_1020_LHC10h");
		TGraphErrors* fractionOfNormAllData2040 = (TGraphErrors*)EventStatsFile->Get("fracNormAll_2040_LHC10h");
		TGraphErrors* fractionOfNormAllData4060 = (TGraphErrors*)EventStatsFile->Get("fracNormAll_4060_LHC10h");
		TGraphErrors* fractionOfNormAllData6080 = (TGraphErrors*)EventStatsFile->Get("fracNormAll_6080_LHC10h");		

		TGraphErrors* fractionOfNormMinBiasData0005 = (TGraphErrors*)EventStatsFile->Get("fracNormMinBias_0005_LHC10h");
		TGraphErrors* fractionOfNormMinBiasData0510 = (TGraphErrors*)EventStatsFile->Get("fracNormMinBias_0510_LHC10h");
// 		TGraphErrors* fractionOfNormMinBias0010 = (TGraphErrors*)EventStatsFile->Get("fracNormMinBias_LHC10h_0010");
		TGraphErrors* fractionOfNormMinBiasData1020 = (TGraphErrors*)EventStatsFile->Get("fracNormMinBias_1020_LHC10h");
		TGraphErrors* fractionOfNormMinBiasData2040 = (TGraphErrors*)EventStatsFile->Get("fracNormMinBias_2040_LHC10h");
		TGraphErrors* fractionOfNormMinBiasData4060 = (TGraphErrors*)EventStatsFile->Get("fracNormMinBias_4060_LHC10h");
		TGraphErrors* fractionOfNormMinBiasData6080 = (TGraphErrors*)EventStatsFile->Get("fracNormMinBias_6080_LHC10h");		

		TGraphErrors* meanTrackMultTPCData0005 = (TGraphErrors*)EventStatsFile->Get("meanTrackMultTPCInCent_0005_LHC10h");
		TGraphErrors* meanTrackMultTPCData0510 = (TGraphErrors*)EventStatsFile->Get("meanTrackMultTPCInCent_0510_LHC10h");
// 		TGraphErrors* meanTrackMultTPC0010 = (TGraphErrors*)EventStatsFile->Get("meanTrackMultTPCInCent_LHC10h_0010");
		TGraphErrors* meanTrackMultTPCData1020 = (TGraphErrors*)EventStatsFile->Get("meanTrackMultTPCInCent_1020_LHC10h");
		TGraphErrors* meanTrackMultTPCData2040 = (TGraphErrors*)EventStatsFile->Get("meanTrackMultTPCInCent_2040_LHC10h");
		TGraphErrors* meanTrackMultTPCData4060 = (TGraphErrors*)EventStatsFile->Get("meanTrackMultTPCInCent_4060_LHC10h");
		TGraphErrors* meanTrackMultTPCData6080 = (TGraphErrors*)EventStatsFile->Get("meanTrackMultTPCInCent_6080_LHC10h");
		
		TGraphErrors* meanTrackMultV0Data0005 = (TGraphErrors*)EventStatsFile->Get("meanMultV0InCent_0005_LHC10h");
		TGraphErrors* meanTrackMultV0Data0510 = (TGraphErrors*)EventStatsFile->Get("meanMultV0InCent_0510_LHC10h");
// 		TGraphErrors* meanTrackMultV00010 = (TGraphErrors*)EventStatsFile->Get("meanMultV0InCent_LHC10h_0010");
		TGraphErrors* meanTrackMultV0Data1020 = (TGraphErrors*)EventStatsFile->Get("meanMultV0InCent_1020_LHC10h");
		TGraphErrors* meanTrackMultV0Data2040 = (TGraphErrors*)EventStatsFile->Get("meanMultV0InCent_2040_LHC10h");
		TGraphErrors* meanTrackMultV0Data4060 = (TGraphErrors*)EventStatsFile->Get("meanMultV0InCent_4060_LHC10h");
		TGraphErrors* meanTrackMultV0Data6080 = (TGraphErrors*)EventStatsFile->Get("meanMultV0InCent_6080_LHC10h");
		
		
		TGraphErrors* fractionOfGammasLHC11a10a0005 = (TGraphErrors*)EventStatsFile->Get("fracGammas_0005_LHC11a10a");
		TGraphErrors* fractionOfGammasLHC11a10a0510 = (TGraphErrors*)EventStatsFile->Get("fracGammas_0510_LHC11a10a");
// 		TGraphErrors* fractionOfGammas0010 = (TGraphErrors*)EventStatsFile->Get("fracGammas_LHC11a10a_0010");
		TGraphErrors* fractionOfGammasLHC11a10a1020 = (TGraphErrors*)EventStatsFile->Get("fracGammas_1020_LHC11a10a");
		TGraphErrors* fractionOfGammasLHC11a10a2040 = (TGraphErrors*)EventStatsFile->Get("fracGammas_2040_LHC11a10a");
		TGraphErrors* fractionOfGammasLHC11a10a4060 = (TGraphErrors*)EventStatsFile->Get("fracGammas_4060_LHC11a10a");
		TGraphErrors* fractionOfGammasLHC11a10a6080 = (TGraphErrors*)EventStatsFile->Get("fracGammas_6080_LHC11a10a");
		
		TGraphErrors* fractionOfGoodEventsLHC11a10a0005 = (TGraphErrors*)EventStatsFile->Get("fracGoodEvents_0005_LHC11a10a");
		TGraphErrors* fractionOfGoodEventsLHC11a10a0510 = (TGraphErrors*)EventStatsFile->Get("fracGoodEvents_0510_LHC11a10a");
// 		TGraphErrors* fractionOfGoodEvents0010 = (TGraphErrors*)EventStatsFile->Get("fracGoodEvents_LHC11a10a_0010");
		TGraphErrors* fractionOfGoodEventsLHC11a10a1020 = (TGraphErrors*)EventStatsFile->Get("fracGoodEvents_1020_LHC11a10a");
		TGraphErrors* fractionOfGoodEventsLHC11a10a2040 = (TGraphErrors*)EventStatsFile->Get("fracGoodEvents_2040_LHC11a10a");
		TGraphErrors* fractionOfGoodEventsLHC11a10a4060 = (TGraphErrors*)EventStatsFile->Get("fracGoodEvents_4060_LHC11a10a");
		TGraphErrors* fractionOfGoodEventsLHC11a10a6080 = (TGraphErrors*)EventStatsFile->Get("fracGoodEvents_6080_LHC11a10a");
		
		TGraphErrors* fractionOfNormAllLHC11a10a0005 = (TGraphErrors*)EventStatsFile->Get("fracNormAll_0005_LHC11a10a");
		TGraphErrors* fractionOfNormAllLHC11a10a0510 = (TGraphErrors*)EventStatsFile->Get("fracNormAll_0510_LHC11a10a");
// 		TGraphErrors* fractionOfNormAll0010 = (TGraphErrors*)EventStatsFile->Get("fracNormAll_LHC11a10a_0010");
		TGraphErrors* fractionOfNormAllLHC11a10a1020 = (TGraphErrors*)EventStatsFile->Get("fracNormAll_1020_LHC11a10a");
		TGraphErrors* fractionOfNormAllLHC11a10a2040 = (TGraphErrors*)EventStatsFile->Get("fracNormAll_2040_LHC11a10a");
		TGraphErrors* fractionOfNormAllLHC11a10a4060 = (TGraphErrors*)EventStatsFile->Get("fracNormAll_4060_LHC11a10a");
		TGraphErrors* fractionOfNormAllLHC11a10a6080 = (TGraphErrors*)EventStatsFile->Get("fracNormAll_6080_LHC11a10a");
		
		TGraphErrors* fractionOfNormMinBiasLHC11a10a0005 = (TGraphErrors*)EventStatsFile->Get("fracNormMinBias_0005_LHC11a10a");
		TGraphErrors* fractionOfNormMinBiasLHC11a10a0510 = (TGraphErrors*)EventStatsFile->Get("fracNormMinBias_0510_LHC11a10a");
// 		TGraphErrors* fractionOfNormMinBias0010 = (TGraphErrors*)EventStatsFile->Get("fracNormMinBias_LHC11a10a_0010");
		TGraphErrors* fractionOfNormMinBiasLHC11a10a1020 = (TGraphErrors*)EventStatsFile->Get("fracNormMinBias_1020_LHC11a10a");
		TGraphErrors* fractionOfNormMinBiasLHC11a10a2040 = (TGraphErrors*)EventStatsFile->Get("fracNormMinBias_2040_LHC11a10a");
		TGraphErrors* fractionOfNormMinBiasLHC11a10a4060 = (TGraphErrors*)EventStatsFile->Get("fracNormMinBias_4060_LHC11a10a");
		TGraphErrors* fractionOfNormMinBiasLHC11a10a6080 = (TGraphErrors*)EventStatsFile->Get("fracNormMinBias_6080_LHC11a10a");
		
		TGraphErrors* fractionOfPileUpLHC11a10a0005 = (TGraphErrors*)EventStatsFile->Get("fracPileUp_0005_LHC11a10a");
		TGraphErrors* fractionOfPileUpLHC11a10a0510 = (TGraphErrors*)EventStatsFile->Get("fracPileUp_0510_LHC11a10a");
// 		TGraphErrors* fractionOfPileUp0010 = (TGraphErrors*)EventStatsFile->Get("fracPileUp_LHC11a10a_0010");
		TGraphErrors* fractionOfPileUpLHC11a10a1020 = (TGraphErrors*)EventStatsFile->Get("fracPileUp_1020_LHC11a10a");
		TGraphErrors* fractionOfPileUpLHC11a10a2040 = (TGraphErrors*)EventStatsFile->Get("fracPileUp_2040_LHC11a10a");
		TGraphErrors* fractionOfPileUpLHC11a10a4060 = (TGraphErrors*)EventStatsFile->Get("fracPileUp_4060_LHC11a10a");
		TGraphErrors* fractionOfPileUpLHC11a10a6080 = (TGraphErrors*)EventStatsFile->Get("fracPileUp_6080_LHC11a10a");
		
		TGraphErrors* fractionOfWOVtxLHC11a10a0005 = (TGraphErrors*)EventStatsFile->Get("fracWOVtx_0005_LHC11a10a");
		TGraphErrors* fractionOfWOVtxLHC11a10a0510 = (TGraphErrors*)EventStatsFile->Get("fracWOVtx_0510_LHC11a10a");
// 		TGraphErrors* fractionOfWOVtx0010 = (TGraphErrors*)EventStatsFile->Get("fracWOVtx_LHC11a10a_0010");
		TGraphErrors* fractionOfWOVtxLHC11a10a1020 = (TGraphErrors*)EventStatsFile->Get("fracWOVtx_1020_LHC11a10a");
		TGraphErrors* fractionOfWOVtxLHC11a10a2040 = (TGraphErrors*)EventStatsFile->Get("fracWOVtx_2040_LHC11a10a");
		TGraphErrors* fractionOfWOVtxLHC11a10a4060 = (TGraphErrors*)EventStatsFile->Get("fracWOVtx_4060_LHC11a10a");
		TGraphErrors* fractionOfWOVtxLHC11a10a6080 = (TGraphErrors*)EventStatsFile->Get("fracWOVtx_6080_LHC11a10a");
		
		TGraphErrors* fractionOfWVtxOutside10cmLHC11a10a0005 = (TGraphErrors*)EventStatsFile->Get("fracWVtxOutside10cm_0005_LHC11a10a");
		TGraphErrors* fractionOfWVtxOutside10cmLHC11a10a0510 = (TGraphErrors*)EventStatsFile->Get("fracWVtxOutside10cm_0510_LHC11a10a");
// 		TGraphErrors* fractionOfWVtxOutside10cm0010 = (TGraphErrors*)EventStatsFile->Get("fracWVtxOutside10cm_LHC11a10a_0010");
		TGraphErrors* fractionOfWVtxOutside10cmLHC11a10a1020 = (TGraphErrors*)EventStatsFile->Get("fracWVtxOutside10cm_1020_LHC11a10a");
		TGraphErrors* fractionOfWVtxOutside10cmLHC11a10a2040 = (TGraphErrors*)EventStatsFile->Get("fracWVtxOutside10cm_2040_LHC11a10a");
		TGraphErrors* fractionOfWVtxOutside10cmLHC11a10a4060 = (TGraphErrors*)EventStatsFile->Get("fracWVtxOutside10cm_4060_LHC11a10a");
		TGraphErrors* fractionOfWVtxOutside10cmLHC11a10a6080 = (TGraphErrors*)EventStatsFile->Get("fracWVtxOutside10cm_6080_LHC11a10a");
		
		TGraphErrors* fractionOfGammasLHC11a10a_bis0005 = (TGraphErrors*)EventStatsFile->Get("fracGammas_0005_LHC11a10a_bis");
		TGraphErrors* fractionOfGammasLHC11a10a_bis0510 = (TGraphErrors*)EventStatsFile->Get("fracGammas_0510_LHC11a10a_bis");
// 		TGraphErrors* fractionOfGammas0010 = (TGraphErrors*)EventStatsFile->Get("fracGammas_LHC11a10a_bis_0010");
		TGraphErrors* fractionOfGammasLHC11a10a_bis1020 = (TGraphErrors*)EventStatsFile->Get("fracGammas_1020_LHC11a10a_bis");
		TGraphErrors* fractionOfGammasLHC11a10a_bis2040 = (TGraphErrors*)EventStatsFile->Get("fracGammas_2040_LHC11a10a_bis");
		TGraphErrors* fractionOfGammasLHC11a10a_bis4060 = (TGraphErrors*)EventStatsFile->Get("fracGammas_4060_LHC11a10a_bis");
		TGraphErrors* fractionOfGammasLHC11a10a_bis6080 = (TGraphErrors*)EventStatsFile->Get("fracGammas_6080_LHC11a10a_bis");

		TGraphErrors* fractionOfGoodEventsLHC11a10a_bis0005 = (TGraphErrors*)EventStatsFile->Get("fracGoodEvents_0005_LHC11a10a_bis");
		TGraphErrors* fractionOfGoodEventsLHC11a10a_bis0510 = (TGraphErrors*)EventStatsFile->Get("fracGoodEvents_0510_LHC11a10a_bis");
// 		TGraphErrors* fractionOfGoodEvents0010 = (TGraphErrors*)EventStatsFile->Get("fracGoodEvents_LHC11a10a_bis_0010");
		TGraphErrors* fractionOfGoodEventsLHC11a10a_bis1020 = (TGraphErrors*)EventStatsFile->Get("fracGoodEvents_1020_LHC11a10a_bis");
		TGraphErrors* fractionOfGoodEventsLHC11a10a_bis2040 = (TGraphErrors*)EventStatsFile->Get("fracGoodEvents_2040_LHC11a10a_bis");
		TGraphErrors* fractionOfGoodEventsLHC11a10a_bis4060 = (TGraphErrors*)EventStatsFile->Get("fracGoodEvents_4060_LHC11a10a_bis");
		TGraphErrors* fractionOfGoodEventsLHC11a10a_bis6080 = (TGraphErrors*)EventStatsFile->Get("fracGoodEvents_6080_LHC11a10a_bis");
		
		TGraphErrors* fractionOfNormAllLHC11a10a_bis0005 = (TGraphErrors*)EventStatsFile->Get("fracNormAll_0005_LHC11a10a_bis");
		TGraphErrors* fractionOfNormAllLHC11a10a_bis0510 = (TGraphErrors*)EventStatsFile->Get("fracNormAll_0510_LHC11a10a_bis");
// 		TGraphErrors* fractionOfNormAll0010 = (TGraphErrors*)EventStatsFile->Get("fracNormAll_LHC11a10a_bis_0010");
		TGraphErrors* fractionOfNormAllLHC11a10a_bis1020 = (TGraphErrors*)EventStatsFile->Get("fracNormAll_1020_LHC11a10a_bis");
		TGraphErrors* fractionOfNormAllLHC11a10a_bis2040 = (TGraphErrors*)EventStatsFile->Get("fracNormAll_2040_LHC11a10a_bis");
		TGraphErrors* fractionOfNormAllLHC11a10a_bis4060 = (TGraphErrors*)EventStatsFile->Get("fracNormAll_4060_LHC11a10a_bis");
		TGraphErrors* fractionOfNormAllLHC11a10a_bis6080 = (TGraphErrors*)EventStatsFile->Get("fracNormAll_6080_LHC11a10a_bis");
		
		TGraphErrors* fractionOfNormMinBiasLHC11a10a_bis0005 = (TGraphErrors*)EventStatsFile->Get("fracNormMinBias_0005_LHC11a10a_bis");
		TGraphErrors* fractionOfNormMinBiasLHC11a10a_bis0510 = (TGraphErrors*)EventStatsFile->Get("fracNormMinBias_0510_LHC11a10a_bis");
// 		TGraphErrors* fractionOfNormMinBias0010 = (TGraphErrors*)EventStatsFile->Get("fracNormMinBias_LHC11a10a_bis_0010");
		TGraphErrors* fractionOfNormMinBiasLHC11a10a_bis1020 = (TGraphErrors*)EventStatsFile->Get("fracNormMinBias_1020_LHC11a10a_bis");
		TGraphErrors* fractionOfNormMinBiasLHC11a10a_bis2040 = (TGraphErrors*)EventStatsFile->Get("fracNormMinBias_2040_LHC11a10a_bis");
		TGraphErrors* fractionOfNormMinBiasLHC11a10a_bis4060 = (TGraphErrors*)EventStatsFile->Get("fracNormMinBias_4060_LHC11a10a_bis");
		TGraphErrors* fractionOfNormMinBiasLHC11a10a_bis6080 = (TGraphErrors*)EventStatsFile->Get("fracNormMinBias_6080_LHC11a10a_bis");
		
		TGraphErrors* fractionOfPileUpLHC11a10a_bis0005 = (TGraphErrors*)EventStatsFile->Get("fracPileUp_0005_LHC11a10a_bis");
		TGraphErrors* fractionOfPileUpLHC11a10a_bis0510 = (TGraphErrors*)EventStatsFile->Get("fracPileUp_0510_LHC11a10a_bis");
// 		TGraphErrors* fractionOfPileUp0010 = (TGraphErrors*)EventStatsFile->Get("fracPileUp_LHC11a10a_bis_0010");
		TGraphErrors* fractionOfPileUpLHC11a10a_bis1020 = (TGraphErrors*)EventStatsFile->Get("fracPileUp_1020_LHC11a10a_bis");
		TGraphErrors* fractionOfPileUpLHC11a10a_bis2040 = (TGraphErrors*)EventStatsFile->Get("fracPileUp_2040_LHC11a10a_bis");
		TGraphErrors* fractionOfPileUpLHC11a10a_bis4060 = (TGraphErrors*)EventStatsFile->Get("fracPileUp_4060_LHC11a10a_bis");
		TGraphErrors* fractionOfPileUpLHC11a10a_bis6080 = (TGraphErrors*)EventStatsFile->Get("fracPileUp_6080_LHC11a10a_bis");
		
		TGraphErrors* fractionOfWOVtxLHC11a10a_bis0005 = (TGraphErrors*)EventStatsFile->Get("fracWOVtx_0005_LHC11a10a_bis");
		TGraphErrors* fractionOfWOVtxLHC11a10a_bis0510 = (TGraphErrors*)EventStatsFile->Get("fracWOVtx_0510_LHC11a10a_bis");
// 		TGraphErrors* fractionOfWOVtx0010 = (TGraphErrors*)EventStatsFile->Get("fracWOVtx_LHC11a10a_bis_0010");
		TGraphErrors* fractionOfWOVtxLHC11a10a_bis1020 = (TGraphErrors*)EventStatsFile->Get("fracWOVtx_1020_LHC11a10a_bis");
		TGraphErrors* fractionOfWOVtxLHC11a10a_bis2040 = (TGraphErrors*)EventStatsFile->Get("fracWOVtx_2040_LHC11a10a_bis");
		TGraphErrors* fractionOfWOVtxLHC11a10a_bis4060 = (TGraphErrors*)EventStatsFile->Get("fracWOVtx_4060_LHC11a10a_bis");
		TGraphErrors* fractionOfWOVtxLHC11a10a_bis6080 = (TGraphErrors*)EventStatsFile->Get("fracWOVtx_6080_LHC11a10a_bis");
		
		TGraphErrors* fractionOfWVtxOutside10cmLHC11a10a_bis0005 = (TGraphErrors*)EventStatsFile->Get("fracWVtxOutside10cm_0005_LHC11a10a_bis");
		TGraphErrors* fractionOfWVtxOutside10cmLHC11a10a_bis0510 = (TGraphErrors*)EventStatsFile->Get("fracWVtxOutside10cm_0510_LHC11a10a_bis");
// 		TGraphErrors* fractionOfWVtxOutside10cm0010 = (TGraphErrors*)EventStatsFile->Get("fracWVtxOutside10cm_LHC11a10a_bis_0010");
		TGraphErrors* fractionOfWVtxOutside10cmLHC11a10a_bis1020 = (TGraphErrors*)EventStatsFile->Get("fracWVtxOutside10cm_1020_LHC11a10a_bis");
		TGraphErrors* fractionOfWVtxOutside10cmLHC11a10a_bis2040 = (TGraphErrors*)EventStatsFile->Get("fracWVtxOutside10cm_2040_LHC11a10a_bis");
		TGraphErrors* fractionOfWVtxOutside10cmLHC11a10a_bis4060 = (TGraphErrors*)EventStatsFile->Get("fracWVtxOutside10cm_4060_LHC11a10a_bis");
		TGraphErrors* fractionOfWVtxOutside10cmLHC11a10a_bis6080 = (TGraphErrors*)EventStatsFile->Get("fracWVtxOutside10cm_6080_LHC11a10a_bis");

		TGraphErrors* meanTrackMultTPCLHC11a10a_bis0005 = (TGraphErrors*)EventStatsFile->Get("meanTrackMultTPCInCent_0005_LHC11a10a_bis");
		TGraphErrors* meanTrackMultTPCLHC11a10a_bis0510 = (TGraphErrors*)EventStatsFile->Get("meanTrackMultTPCInCent_0510_LHC11a10a_bis");
		TGraphErrors* meanTrackMultTPCLHC11a10a_bis1020 = (TGraphErrors*)EventStatsFile->Get("meanTrackMultTPCInCent_1020_LHC11a10a_bis");
		TGraphErrors* meanTrackMultTPCLHC11a10a_bis2040 = (TGraphErrors*)EventStatsFile->Get("meanTrackMultTPCInCent_2040_LHC11a10a_bis");
		TGraphErrors* meanTrackMultTPCLHC11a10a_bis4060 = (TGraphErrors*)EventStatsFile->Get("meanTrackMultTPCInCent_4060_LHC11a10a_bis");
		TGraphErrors* meanTrackMultTPCLHC11a10a_bis6080 = (TGraphErrors*)EventStatsFile->Get("meanTrackMultTPCInCent_6080_LHC11a10a_bis");
		
		TGraphErrors* meanTrackMultV0LHC11a10a_bis0005 = (TGraphErrors*)EventStatsFile->Get("meanMultV0InCent_0005_LHC11a10a_bis");
		TGraphErrors* meanTrackMultV0LHC11a10a_bis0510 = (TGraphErrors*)EventStatsFile->Get("meanMultV0InCent_0510_LHC11a10a_bis");
		TGraphErrors* meanTrackMultV0LHC11a10a_bis1020 = (TGraphErrors*)EventStatsFile->Get("meanMultV0InCent_1020_LHC11a10a_bis");
		TGraphErrors* meanTrackMultV0LHC11a10a_bis2040 = (TGraphErrors*)EventStatsFile->Get("meanMultV0InCent_2040_LHC11a10a_bis");
		TGraphErrors* meanTrackMultV0LHC11a10a_bis4060 = (TGraphErrors*)EventStatsFile->Get("meanMultV0InCent_4060_LHC11a10a_bis");
		TGraphErrors* meanTrackMultV0LHC11a10a_bis6080 = (TGraphErrors*)EventStatsFile->Get("meanMultV0InCent_6080_LHC11a10a_bis");
	
		
		TGraphErrors* fractionOfGammasLHC11a10b_bis0005 = (TGraphErrors*)EventStatsFile->Get("fracGammas_0005_LHC11a10b_bis");
		TGraphErrors* fractionOfGammasLHC11a10b_bis0510 = (TGraphErrors*)EventStatsFile->Get("fracGammas_0510_LHC11a10b_bis");
// 		TGraphErrors* fractionOfGammas0010 = (TGraphErrors*)EventStatsFile->Get("fracGammas_LHC11a10b_bis_0010");
		TGraphErrors* fractionOfGammasLHC11a10b_bis1020 = (TGraphErrors*)EventStatsFile->Get("fracGammas_1020_LHC11a10b_bis");
		TGraphErrors* fractionOfGammasLHC11a10b_bis2040 = (TGraphErrors*)EventStatsFile->Get("fracGammas_2040_LHC11a10b_bis");
		TGraphErrors* fractionOfGammasLHC11a10b_bis4060 = (TGraphErrors*)EventStatsFile->Get("fracGammas_4060_LHC11a10b_bis");
		TGraphErrors* fractionOfGammasLHC11a10b_bis6080 = (TGraphErrors*)EventStatsFile->Get("fracGammas_6080_LHC11a10b_bis");

		TGraphErrors* fractionOfGoodEventsLHC11a10b_bis0005 = (TGraphErrors*)EventStatsFile->Get("fracGoodEvents_0005_LHC11a10b_bis");
		TGraphErrors* fractionOfGoodEventsLHC11a10b_bis0510 = (TGraphErrors*)EventStatsFile->Get("fracGoodEvents_0510_LHC11a10b_bis");
// 		TGraphErrors* fractionOfGoodEvents0010 = (TGraphErrors*)EventStatsFile->Get("fracGoodEvents_LHC11a10b_bis_0010");
		TGraphErrors* fractionOfGoodEventsLHC11a10b_bis1020 = (TGraphErrors*)EventStatsFile->Get("fracGoodEvents_1020_LHC11a10b_bis");
		TGraphErrors* fractionOfGoodEventsLHC11a10b_bis2040 = (TGraphErrors*)EventStatsFile->Get("fracGoodEvents_2040_LHC11a10b_bis");
		TGraphErrors* fractionOfGoodEventsLHC11a10b_bis4060 = (TGraphErrors*)EventStatsFile->Get("fracGoodEvents_4060_LHC11a10b_bis");
		TGraphErrors* fractionOfGoodEventsLHC11a10b_bis6080 = (TGraphErrors*)EventStatsFile->Get("fracGoodEvents_6080_LHC11a10b_bis");
		
		TGraphErrors* fractionOfNormAllLHC11a10b_bis0005 = (TGraphErrors*)EventStatsFile->Get("fracNormAll_0005_LHC11a10b_bis");
		TGraphErrors* fractionOfNormAllLHC11a10b_bis0510 = (TGraphErrors*)EventStatsFile->Get("fracNormAll_0510_LHC11a10b_bis");
// 		TGraphErrors* fractionOfNormAll0010 = (TGraphErrors*)EventStatsFile->Get("fracNormAll_LHC11a10b_bis_0010");
		TGraphErrors* fractionOfNormAllLHC11a10b_bis1020 = (TGraphErrors*)EventStatsFile->Get("fracNormAll_1020_LHC11a10b_bis");
		TGraphErrors* fractionOfNormAllLHC11a10b_bis2040 = (TGraphErrors*)EventStatsFile->Get("fracNormAll_2040_LHC11a10b_bis");
		TGraphErrors* fractionOfNormAllLHC11a10b_bis4060 = (TGraphErrors*)EventStatsFile->Get("fracNormAll_4060_LHC11a10b_bis");
		TGraphErrors* fractionOfNormAllLHC11a10b_bis6080 = (TGraphErrors*)EventStatsFile->Get("fracNormAll_6080_LHC11a10b_bis");
		
		TGraphErrors* fractionOfNormMinBiasLHC11a10b_bis0005 = (TGraphErrors*)EventStatsFile->Get("fracNormMinBias_0005_LHC11a10b_bis");
		TGraphErrors* fractionOfNormMinBiasLHC11a10b_bis0510 = (TGraphErrors*)EventStatsFile->Get("fracNormMinBias_0510_LHC11a10b_bis");
// 		TGraphErrors* fractionOfNormMinBias0010 = (TGraphErrors*)EventStatsFile->Get("fracNormMinBias_LHC11a10b_bis_0010");
		TGraphErrors* fractionOfNormMinBiasLHC11a10b_bis1020 = (TGraphErrors*)EventStatsFile->Get("fracNormMinBias_1020_LHC11a10b_bis");
		TGraphErrors* fractionOfNormMinBiasLHC11a10b_bis2040 = (TGraphErrors*)EventStatsFile->Get("fracNormMinBias_2040_LHC11a10b_bis");
		TGraphErrors* fractionOfNormMinBiasLHC11a10b_bis4060 = (TGraphErrors*)EventStatsFile->Get("fracNormMinBias_4060_LHC11a10b_bis");
		TGraphErrors* fractionOfNormMinBiasLHC11a10b_bis6080 = (TGraphErrors*)EventStatsFile->Get("fracNormMinBias_6080_LHC11a10b_bis");
		
		TGraphErrors* fractionOfPileUpLHC11a10b_bis0005 = (TGraphErrors*)EventStatsFile->Get("fracPileUp_0005_LHC11a10b_bis");
		TGraphErrors* fractionOfPileUpLHC11a10b_bis0510 = (TGraphErrors*)EventStatsFile->Get("fracPileUp_0510_LHC11a10b_bis");
// 		TGraphErrors* fractionOfPileUp0010 = (TGraphErrors*)EventStatsFile->Get("fracPileUp_LHC11a10b_bis_0010");
		TGraphErrors* fractionOfPileUpLHC11a10b_bis1020 = (TGraphErrors*)EventStatsFile->Get("fracPileUp_1020_LHC11a10b_bis");
		TGraphErrors* fractionOfPileUpLHC11a10b_bis2040 = (TGraphErrors*)EventStatsFile->Get("fracPileUp_2040_LHC11a10b_bis");
		TGraphErrors* fractionOfPileUpLHC11a10b_bis4060 = (TGraphErrors*)EventStatsFile->Get("fracPileUp_4060_LHC11a10b_bis");
		TGraphErrors* fractionOfPileUpLHC11a10b_bis6080 = (TGraphErrors*)EventStatsFile->Get("fracPileUp_6080_LHC11a10b_bis");
		
		TGraphErrors* fractionOfWOVtxLHC11a10b_bis0005 = (TGraphErrors*)EventStatsFile->Get("fracWOVtx_0005_LHC11a10b_bis");
		TGraphErrors* fractionOfWOVtxLHC11a10b_bis0510 = (TGraphErrors*)EventStatsFile->Get("fracWOVtx_0510_LHC11a10b_bis");
// 		TGraphErrors* fractionOfWOVtx0010 = (TGraphErrors*)EventStatsFile->Get("fracWOVtx_LHC11a10b_bis_0010");
		TGraphErrors* fractionOfWOVtxLHC11a10b_bis1020 = (TGraphErrors*)EventStatsFile->Get("fracWOVtx_1020_LHC11a10b_bis");
		TGraphErrors* fractionOfWOVtxLHC11a10b_bis2040 = (TGraphErrors*)EventStatsFile->Get("fracWOVtx_2040_LHC11a10b_bis");
		TGraphErrors* fractionOfWOVtxLHC11a10b_bis4060 = (TGraphErrors*)EventStatsFile->Get("fracWOVtx_4060_LHC11a10b_bis");
		TGraphErrors* fractionOfWOVtxLHC11a10b_bis6080 = (TGraphErrors*)EventStatsFile->Get("fracWOVtx_6080_LHC11a10b_bis");
		
		TGraphErrors* fractionOfWVtxOutside10cmLHC11a10b_bis0005 = (TGraphErrors*)EventStatsFile->Get("fracWVtxOutside10cm_0005_LHC11a10b_bis");
		TGraphErrors* fractionOfWVtxOutside10cmLHC11a10b_bis0510 = (TGraphErrors*)EventStatsFile->Get("fracWVtxOutside10cm_0510_LHC11a10b_bis");
// 		TGraphErrors* fractionOfWVtxOutside10cm0010 = (TGraphErrors*)EventStatsFile->Get("fracWVtxOutside10cm_LHC11a10b_bis_0010");
		TGraphErrors* fractionOfWVtxOutside10cmLHC11a10b_bis1020 = (TGraphErrors*)EventStatsFile->Get("fracWVtxOutside10cm_1020_LHC11a10b_bis");
		TGraphErrors* fractionOfWVtxOutside10cmLHC11a10b_bis2040 = (TGraphErrors*)EventStatsFile->Get("fracWVtxOutside10cm_2040_LHC11a10b_bis");
		TGraphErrors* fractionOfWVtxOutside10cmLHC11a10b_bis4060 = (TGraphErrors*)EventStatsFile->Get("fracWVtxOutside10cm_4060_LHC11a10b_bis");
		TGraphErrors* fractionOfWVtxOutside10cmLHC11a10b_bis6080 = (TGraphErrors*)EventStatsFile->Get("fracWVtxOutside10cm_6080_LHC11a10b_bis");

		TGraphErrors* fractionOfGammasLHC13d20005 = (TGraphErrors*)EventStatsFile->Get("fracGammas_0005_LHC13d2");
		TGraphErrors* fractionOfGammasLHC13d20510 = (TGraphErrors*)EventStatsFile->Get("fracGammas_0510_LHC13d2");
// 		TGraphErrors* fractionOfGammas0010 = (TGraphErrors*)EventStatsFile->Get("fracGammas_LHC13d2_0010");
		TGraphErrors* fractionOfGammasLHC13d21020 = (TGraphErrors*)EventStatsFile->Get("fracGammas_1020_LHC13d2");
		TGraphErrors* fractionOfGammasLHC13d22040 = (TGraphErrors*)EventStatsFile->Get("fracGammas_2040_LHC13d2");
		TGraphErrors* fractionOfGammasLHC13d24060 = (TGraphErrors*)EventStatsFile->Get("fracGammas_4060_LHC13d2");
		TGraphErrors* fractionOfGammasLHC13d26080 = (TGraphErrors*)EventStatsFile->Get("fracGammas_6080_LHC13d2");

				TGraphErrors* fractionOfGoodEventsLHC13d20005 = (TGraphErrors*)EventStatsFile->Get("fracGoodEvents_0005_LHC13d2");
		TGraphErrors* fractionOfGoodEventsLHC13d20510 = (TGraphErrors*)EventStatsFile->Get("fracGoodEvents_0510_LHC13d2");
// 		TGraphErrors* fractionOfGoodEvents0010 = (TGraphErrors*)EventStatsFile->Get("fracGoodEvents_LHC13d2_0010");
		TGraphErrors* fractionOfGoodEventsLHC13d21020 = (TGraphErrors*)EventStatsFile->Get("fracGoodEvents_1020_LHC13d2");
		TGraphErrors* fractionOfGoodEventsLHC13d22040 = (TGraphErrors*)EventStatsFile->Get("fracGoodEvents_2040_LHC13d2");
		TGraphErrors* fractionOfGoodEventsLHC13d24060 = (TGraphErrors*)EventStatsFile->Get("fracGoodEvents_4060_LHC13d2");
		TGraphErrors* fractionOfGoodEventsLHC13d26080 = (TGraphErrors*)EventStatsFile->Get("fracGoodEvents_6080_LHC13d2");
		
		TGraphErrors* fractionOfNormAllLHC13d20005 = (TGraphErrors*)EventStatsFile->Get("fracNormAll_0005_LHC13d2");
		TGraphErrors* fractionOfNormAllLHC13d20510 = (TGraphErrors*)EventStatsFile->Get("fracNormAll_0510_LHC13d2");
// 		TGraphErrors* fractionOfNormAll0010 = (TGraphErrors*)EventStatsFile->Get("fracNormAll_LHC13d2_0010");
		TGraphErrors* fractionOfNormAllLHC13d21020 = (TGraphErrors*)EventStatsFile->Get("fracNormAll_1020_LHC13d2");
		TGraphErrors* fractionOfNormAllLHC13d22040 = (TGraphErrors*)EventStatsFile->Get("fracNormAll_2040_LHC13d2");
		TGraphErrors* fractionOfNormAllLHC13d24060 = (TGraphErrors*)EventStatsFile->Get("fracNormAll_4060_LHC13d2");
		TGraphErrors* fractionOfNormAllLHC13d26080 = (TGraphErrors*)EventStatsFile->Get("fracNormAll_6080_LHC13d2");
		
		TGraphErrors* fractionOfNormMinBiasLHC13d20005 = (TGraphErrors*)EventStatsFile->Get("fracNormMinBias_0005_LHC13d2");
		TGraphErrors* fractionOfNormMinBiasLHC13d20510 = (TGraphErrors*)EventStatsFile->Get("fracNormMinBias_0510_LHC13d2");
// 		TGraphErrors* fractionOfNormMinBias0010 = (TGraphErrors*)EventStatsFile->Get("fracNormMinBias_LHC13d2_0010");
		TGraphErrors* fractionOfNormMinBiasLHC13d21020 = (TGraphErrors*)EventStatsFile->Get("fracNormMinBias_1020_LHC13d2");
		TGraphErrors* fractionOfNormMinBiasLHC13d22040 = (TGraphErrors*)EventStatsFile->Get("fracNormMinBias_2040_LHC13d2");
		TGraphErrors* fractionOfNormMinBiasLHC13d24060 = (TGraphErrors*)EventStatsFile->Get("fracNormMinBias_4060_LHC13d2");
		TGraphErrors* fractionOfNormMinBiasLHC13d26080 = (TGraphErrors*)EventStatsFile->Get("fracNormMinBias_6080_LHC13d2");
		
		TGraphErrors* fractionOfPileUpLHC13d20005 = (TGraphErrors*)EventStatsFile->Get("fracPileUp_0005_LHC13d2");
		TGraphErrors* fractionOfPileUpLHC13d20510 = (TGraphErrors*)EventStatsFile->Get("fracPileUp_0510_LHC13d2");
// 		TGraphErrors* fractionOfPileUp0010 = (TGraphErrors*)EventStatsFile->Get("fracPileUp_LHC13d2_0010");
		TGraphErrors* fractionOfPileUpLHC13d21020 = (TGraphErrors*)EventStatsFile->Get("fracPileUp_1020_LHC13d2");
		TGraphErrors* fractionOfPileUpLHC13d22040 = (TGraphErrors*)EventStatsFile->Get("fracPileUp_2040_LHC13d2");
		TGraphErrors* fractionOfPileUpLHC13d24060 = (TGraphErrors*)EventStatsFile->Get("fracPileUp_4060_LHC13d2");
		TGraphErrors* fractionOfPileUpLHC13d26080 = (TGraphErrors*)EventStatsFile->Get("fracPileUp_6080_LHC13d2");
		
		TGraphErrors* fractionOfWOVtxLHC13d20005 = (TGraphErrors*)EventStatsFile->Get("fracWOVtx_0005_LHC13d2");
		TGraphErrors* fractionOfWOVtxLHC13d20510 = (TGraphErrors*)EventStatsFile->Get("fracWOVtx_0510_LHC13d2");
// 		TGraphErrors* fractionOfWOVtx0010 = (TGraphErrors*)EventStatsFile->Get("fracWOVtx_LHC13d2_0010");
		TGraphErrors* fractionOfWOVtxLHC13d21020 = (TGraphErrors*)EventStatsFile->Get("fracWOVtx_1020_LHC13d2");
		TGraphErrors* fractionOfWOVtxLHC13d22040 = (TGraphErrors*)EventStatsFile->Get("fracWOVtx_2040_LHC13d2");
		TGraphErrors* fractionOfWOVtxLHC13d24060 = (TGraphErrors*)EventStatsFile->Get("fracWOVtx_4060_LHC13d2");
		TGraphErrors* fractionOfWOVtxLHC13d26080 = (TGraphErrors*)EventStatsFile->Get("fracWOVtx_6080_LHC13d2");
		
		TGraphErrors* fractionOfWVtxOutside10cmLHC13d20005 = (TGraphErrors*)EventStatsFile->Get("fracWVtxOutside10cm_0005_LHC13d2");
		TGraphErrors* fractionOfWVtxOutside10cmLHC13d20510 = (TGraphErrors*)EventStatsFile->Get("fracWVtxOutside10cm_0510_LHC13d2");
// 		TGraphErrors* fractionOfWVtxOutside10cm0010 = (TGraphErrors*)EventStatsFile->Get("fracWVtxOutside10cm_LHC13d2_0010");
		TGraphErrors* fractionOfWVtxOutside10cmLHC13d21020 = (TGraphErrors*)EventStatsFile->Get("fracWVtxOutside10cm_1020_LHC13d2");
		TGraphErrors* fractionOfWVtxOutside10cmLHC13d22040 = (TGraphErrors*)EventStatsFile->Get("fracWVtxOutside10cm_2040_LHC13d2");
		TGraphErrors* fractionOfWVtxOutside10cmLHC13d24060 = (TGraphErrors*)EventStatsFile->Get("fracWVtxOutside10cm_4060_LHC13d2");
		TGraphErrors* fractionOfWVtxOutside10cmLHC13d26080 = (TGraphErrors*)EventStatsFile->Get("fracWVtxOutside10cm_6080_LHC13d2");

      TGraphErrors* meanTrackMultTPCLHC13d20005 = (TGraphErrors*)EventStatsFile->Get("meanTrackMultTPCInCent_0005_LHC13d2");
      TGraphErrors* meanTrackMultTPCLHC13d20510 = (TGraphErrors*)EventStatsFile->Get("meanTrackMultTPCInCent_0510_LHC13d2");
      TGraphErrors* meanTrackMultTPCLHC13d21020 = (TGraphErrors*)EventStatsFile->Get("meanTrackMultTPCInCent_1020_LHC13d2");
      TGraphErrors* meanTrackMultTPCLHC13d22040 = (TGraphErrors*)EventStatsFile->Get("meanTrackMultTPCInCent_2040_LHC13d2");
      TGraphErrors* meanTrackMultTPCLHC13d24060 = (TGraphErrors*)EventStatsFile->Get("meanTrackMultTPCInCent_4060_LHC13d2");
      TGraphErrors* meanTrackMultTPCLHC13d26080 = (TGraphErrors*)EventStatsFile->Get("meanTrackMultTPCInCent_6080_LHC13d2");
      
//       TGraphErrors* meanTrackMultV0LHC13d20005 = (TGraphErrors*)EventStatsFile->Get("meanMultV0InCent_0005_LHC13d2");
//       TGraphErrors* meanTrackMultV0LHC13d20510 = (TGraphErrors*)EventStatsFile->Get("meanMultV0InCent_0510_LHC13d2");
//       TGraphErrors* meanTrackMultV0LHC13d21020 = (TGraphErrors*)EventStatsFile->Get("meanMultV0InCent_1020_LHC13d2");
//       TGraphErrors* meanTrackMultV0LHC13d22040 = (TGraphErrors*)EventStatsFile->Get("meanMultV0InCent_2040_LHC13d2");
//       TGraphErrors* meanTrackMultV0LHC13d24060 = (TGraphErrors*)EventStatsFile->Get("meanMultV0InCent_4060_LHC13d2");
//       TGraphErrors* meanTrackMultV0LHC13d26080 = (TGraphErrors*)EventStatsFile->Get("meanMultV0InCent_6080_LHC13d2");

		TGraphErrors* fractionOfGammasLHC10x_7TeV = (TGraphErrors*)EventStatsFile->Get("fracGammas_pp7TeV_LHC10x");
		TGraphErrors* fractionOfPi0LHC10x_7TeV = (TGraphErrors*)EventStatsFile->Get("fractionOfPi0InCent_pp7TeV_LHC10x");
		TGraphErrors* fractionOfEtaLHC10x_7TeV = (TGraphErrors*)EventStatsFile->Get("fractionOfEtaInCent_pp7TeV_LHC10x");
		TGraphErrors* fractionOfWOVtxLHC10x_7TeV = (TGraphErrors*)EventStatsFile->Get("fracWOVtx_pp7TeV_LHC10x");
		TGraphErrors* fractionOfWVtxOutside10cmLHC10x_7TeV = (TGraphErrors*)EventStatsFile->Get("fracWVtxOutside10cm_pp7TeV_LHC10x");
		TGraphErrors* fractionOfGoodEventsLHC10x_7TeV = (TGraphErrors*)EventStatsFile->Get("fracGoodEvents_pp7TeV_LHC10x");
		TGraphErrors* fractionOfNormAllLHC10x_7TeV = (TGraphErrors*)EventStatsFile->Get("fracNormAll_pp7TeV_LHC10x");
		TGraphErrors* fractionOfNormMinBiasLHC10x_7TeV = (TGraphErrors*)EventStatsFile->Get("fracNormMinBias_pp7TeV_LHC10x");
		TGraphErrors* fractionOfPileUpLHC10x_7TeV = (TGraphErrors*)EventStatsFile->Get("fracPileUp_pp7TeV_LHC10x");
		TGraphErrors* meanTrackMultTPCDataLHC10x_7TeV = (TGraphErrors*)EventStatsFile->Get("meanTrackMultTPCInCent_pp7TeV_LHC10x");
		TGraphErrors* widthPi0LHC10x_7TeV = (TGraphErrors*)EventStatsFile->Get("widthPi0perRun_pp7TeV_LHC10x");
		TGraphErrors* massPi0LHC10x_7TeV = (TGraphErrors*)EventStatsFile->Get("massPi0perRun_pp7TeV_LHC10x");
		TGraphErrors* widthEtaLHC10x_7TeV = (TGraphErrors*)EventStatsFile->Get("widthEtaperRun_pp7TeV_LHC10x");
		TGraphErrors* massEtaLHC10x_7TeV = (TGraphErrors*)EventStatsFile->Get("massEtaperRun_pp7TeV_LHC10x");

		TGraphErrors* fractionOfGammasLHC10d1_7TeV = (TGraphErrors*)EventStatsFile->Get("fracGammas_pp7TeV_LHC10d1");
		TGraphErrors* fractionOfPi0LHC10d1_7TeV = (TGraphErrors*)EventStatsFile->Get("fractionOfPi0InCent_pp7TeV_LHC10d1");
		TGraphErrors* fractionOfEtaLHC10d1_7TeV = (TGraphErrors*)EventStatsFile->Get("fracGammas_pp7TeV_LHC10d1");
		TGraphErrors* fractionOfWOVtxLHC10d1_7TeV = (TGraphErrors*)EventStatsFile->Get("fracWOVtx_pp7TeV_LHC10d1");
		TGraphErrors* fractionOfWVtxOutside10cmLHC10d1_7TeV = (TGraphErrors*)EventStatsFile->Get("fracWVtxOutside10cm_pp7TeV_LHC10d1");
		TGraphErrors* fractionOfGoodEventsLHC10d1_7TeV = (TGraphErrors*)EventStatsFile->Get("fracGoodEvents_pp7TeV_LHC10d1");
		TGraphErrors* fractionOfNormAllLHC10d1_7TeV = (TGraphErrors*)EventStatsFile->Get("fracNormAll_pp7TeV_LHC10d1");
		TGraphErrors* fractionOfNormMinBiasLHC10d1_7TeV = (TGraphErrors*)EventStatsFile->Get("fracNormMinBias_pp7TeV_LHC10d1");
		TGraphErrors* fractionOfPileUpLHC10d1_7TeV = (TGraphErrors*)EventStatsFile->Get("fracPileUp_pp7TeV_LHC10d1");
		TGraphErrors* meanTrackMultTPCDataLHC10d1_7TeV = (TGraphErrors*)EventStatsFile->Get("meanTrackMultTPCInCent_pp7TeV_LHC10d1");
		TGraphErrors* widthPi0LHC10d1_7TeV = (TGraphErrors*)EventStatsFile->Get("widthPi0perRun_pp7TeV_LHC10d1");
		TGraphErrors* massPi0LHC10d1_7TeV = (TGraphErrors*)EventStatsFile->Get("massPi0perRun_pp7TeV_LHC10d1");
		TGraphErrors* widthEtaLHC10d1_7TeV = (TGraphErrors*)EventStatsFile->Get("widthEtaperRun_pp7TeV_LHC10d1");
		TGraphErrors* massEtaLHC10d1_7TeV = (TGraphErrors*)EventStatsFile->Get("massEtaperRun_pp7TeV_LHC10d1");
	
		TGraphErrors* fractionOfGammasLHC10d2_7TeV = (TGraphErrors*)EventStatsFile->Get("fracGammas_pp7TeV_LHC10d2");
		TGraphErrors* fractionOfPi0LHC10d2_7TeV = (TGraphErrors*)EventStatsFile->Get("fractionOfPi0InCent_pp7TeV_LHC10d2");
		TGraphErrors* fractionOfEtaLHC10d2_7TeV = (TGraphErrors*)EventStatsFile->Get("fractionOfEtaInCent_pp7TeV_LHC10d2");
		TGraphErrors* fractionOfWOVtxLHC10d2_7TeV = (TGraphErrors*)EventStatsFile->Get("fracWOVtx_pp7TeV_LHC10d2");
		TGraphErrors* fractionOfWVtxOutside10cmLHC10d2_7TeV = (TGraphErrors*)EventStatsFile->Get("fracWVtxOutside10cm_pp7TeV_LHC10d2");
		TGraphErrors* fractionOfGoodEventsLHC10d2_7TeV = (TGraphErrors*)EventStatsFile->Get("fracGoodEvents_pp7TeV_LHC10d2");
		TGraphErrors* fractionOfNormAllLHC10d2_7TeV = (TGraphErrors*)EventStatsFile->Get("fracNormAll_pp7TeV_LHC10d2");
		TGraphErrors* fractionOfNormMinBiasLHC10d2_7TeV = (TGraphErrors*)EventStatsFile->Get("fracNormMinBias_pp7TeV_LHC10d2");
		TGraphErrors* fractionOfPileUpLHC10d2_7TeV = (TGraphErrors*)EventStatsFile->Get("fracPileUp_pp7TeV_LHC10d2");	
		TGraphErrors* meanTrackMultTPCDataLHC10d2_7TeV = (TGraphErrors*)EventStatsFile->Get("meanTrackMultTPCInCent_pp7TeV_LHC10d2");
		TGraphErrors* widthPi0LHC10d2_7TeV = (TGraphErrors*)EventStatsFile->Get("widthPi0perRun_pp7TeV_LHC10d2");
		TGraphErrors* massPi0LHC10d2_7TeV = (TGraphErrors*)EventStatsFile->Get("massPi0perRun_pp7TeV_LHC10d2");
		TGraphErrors* widthEtaLHC10d2_7TeV = (TGraphErrors*)EventStatsFile->Get("widthEtaperRun_pp7TeV_LHC10d2");
		TGraphErrors* massEtaLHC10d2_7TeV = (TGraphErrors*)EventStatsFile->Get("massEtaperRun_pp7TeV_LHC10d2");
		
		TGraphErrors* fractionOfGammasLHC10d4_7TeV = (TGraphErrors*)EventStatsFile->Get("fracGammas_pp7TeV_LHC10d4");
		TGraphErrors* fractionOfPi0LHC10d4_7TeV = (TGraphErrors*)EventStatsFile->Get("fractionOfPi0InCent_pp7TeV_LHC10d4");
		TGraphErrors* fractionOfEtaLHC10d4_7TeV = (TGraphErrors*)EventStatsFile->Get("fractionOfEtaInCent_pp7TeV_LHC10d4");
		TGraphErrors* fractionOfWOVtxLHC10d4_7TeV = (TGraphErrors*)EventStatsFile->Get("fracWOVtx_pp7TeV_LHC10d4");
		TGraphErrors* fractionOfWVtxOutside10cmLHC10d4_7TeV = (TGraphErrors*)EventStatsFile->Get("fracWVtxOutside10cm_pp7TeV_LHC10d4");
		TGraphErrors* fractionOfGoodEventsLHC10d4_7TeV = (TGraphErrors*)EventStatsFile->Get("fracGoodEvents_pp7TeV_LHC10d4");
		TGraphErrors* fractionOfNormAllLHC10d4_7TeV = (TGraphErrors*)EventStatsFile->Get("fracNormAll_pp7TeV_LHC10d4");
		TGraphErrors* fractionOfNormMinBiasLHC10d4_7TeV = (TGraphErrors*)EventStatsFile->Get("fracNormMinBias_pp7TeV_LHC10d4");
		TGraphErrors* fractionOfPileUpLHC10d4_7TeV = (TGraphErrors*)EventStatsFile->Get("fracPileUp_pp7TeV_LHC10d4");	
		TGraphErrors* meanTrackMultTPCDataLHC10d4_7TeV = (TGraphErrors*)EventStatsFile->Get("meanTrackMultTPCInCent_pp7TeV_LHC10d4");
		TGraphErrors* widthPi0LHC10d4_7TeV = (TGraphErrors*)EventStatsFile->Get("widthPi0perRun_pp7TeV_LHC10d4");
		TGraphErrors* massPi0LHC10d4_7TeV = (TGraphErrors*)EventStatsFile->Get("massPi0perRun_pp7TeV_LHC10d4");
		TGraphErrors* widthEtaLHC10d4_7TeV = (TGraphErrors*)EventStatsFile->Get("widthEtaperRun_pp7TeV_LHC10d4");
		TGraphErrors* massEtaLHC10d4_7TeV = (TGraphErrors*)EventStatsFile->Get("massEtaperRun_pp7TeV_LHC10d4");

		TGraphErrors* fractionOfWOVtxLHC10d4a_7TeV = (TGraphErrors*)EventStatsFile->Get("fracWOVtx_pp7TeV_LHC10d4a");
		TGraphErrors* fractionOfWVtxOutside10cmLHC10d4a_7TeV = (TGraphErrors*)EventStatsFile->Get("fracWVtxOutside10cm_pp7TeV_LHC10d4a");
		TGraphErrors* fractionOfGoodEventsLHC10d4a_7TeV = (TGraphErrors*)EventStatsFile->Get("fracGoodEvents_pp7TeV_LHC10d4a");
		TGraphErrors* fractionOfNormAllLHC10d4a_7TeV = (TGraphErrors*)EventStatsFile->Get("fracNormAll_pp7TeV_LHC10d4a");
		TGraphErrors* fractionOfNormMinBiasLHC10d4a_7TeV = (TGraphErrors*)EventStatsFile->Get("fracNormMinBias_pp7TeV_LHC10d4a");
		TGraphErrors* fractionOfPileUpLHC10d4a_7TeV = (TGraphErrors*)EventStatsFile->Get("fracPileUp_pp7TeV_LHC10d4a");	
		TGraphErrors* fractionOfGammasLHC10d4a_7TeV = (TGraphErrors*)EventStatsFile->Get("fracGammas_pp7TeV_LHC10d4a");
		TGraphErrors* fractionOfPi0LHC10d4a_7TeV = (TGraphErrors*)EventStatsFile->Get("fractionOfPi0InCent_pp7TeV_LHC10d4a");
		TGraphErrors* fractionOfEtaLHC10d4a_7TeV = (TGraphErrors*)EventStatsFile->Get("fractionOfEtaInCent_pp7TeV_LHC10d4a");
		TGraphErrors* meanTrackMultTPCDataLHC10d4a_7TeV = (TGraphErrors*)EventStatsFile->Get("meanTrackMultTPCInCent_pp7TeV_LHC10d4a");
		TGraphErrors* widthPi0LHC10d4a_7TeV = (TGraphErrors*)EventStatsFile->Get("widthPi0perRun_pp7TeV_LHC10d4a");
		TGraphErrors* massPi0LHC10d4a_7TeV = (TGraphErrors*)EventStatsFile->Get("massPi0perRun_pp7TeV_LHC10d4a");
		TGraphErrors* widthEtaLHC10d4a_7TeV = (TGraphErrors*)EventStatsFile->Get("widthEtaperRun_pp7TeV_LHC10d4a");
		TGraphErrors* massEtaLHC10d4a_7TeV = (TGraphErrors*)EventStatsFile->Get("massEtaperRun_pp7TeV_LHC10d4a");
		
		TGraphErrors* fractionOfGammasLHC10f6a_7TeV = (TGraphErrors*)EventStatsFile->Get("fracGammas_pp7TeV_LHC10f6a");
		TGraphErrors* fractionOfPi0LHC10f6a_7TeV = (TGraphErrors*)EventStatsFile->Get("fractionOfPi0InCent_pp7TeV_LHC10f6a");
		TGraphErrors* fractionOfEtaLHC10f6a_7TeV = (TGraphErrors*)EventStatsFile->Get("fractionOfEtaInCent_pp7TeV_LHC10f6a");
		TGraphErrors* fractionOfWOVtxLHC10f6a_7TeV = (TGraphErrors*)EventStatsFile->Get("fracWOVtx_pp7TeV_LHC10f6a");
		TGraphErrors* fractionOfWVtxOutside10cmLHC10f6a_7TeV = (TGraphErrors*)EventStatsFile->Get("fracWVtxOutside10cm_pp7TeV_LHC10f6a");
		TGraphErrors* fractionOfGoodEventsLHC10f6a_7TeV = (TGraphErrors*)EventStatsFile->Get("fracGoodEvents_pp7TeV_LHC10f6a");
		TGraphErrors* fractionOfNormAllLHC10f6a_7TeV = (TGraphErrors*)EventStatsFile->Get("fracNormAll_pp7TeV_LHC10f6a");
		TGraphErrors* fractionOfNormMinBiasLHC10f6a_7TeV = (TGraphErrors*)EventStatsFile->Get("fracNormMinBias_pp7TeV_LHC10f6a");
		TGraphErrors* fractionOfPileUpLHC10f6a_7TeV = (TGraphErrors*)EventStatsFile->Get("fracPileUp_pp7TeV_LHC10f6a");	
		TGraphErrors* meanTrackMultTPCDataLHC10f6a_7TeV = (TGraphErrors*)EventStatsFile->Get("meanTrackMultTPCInCent_pp7TeV_LHC10f6a");
		TGraphErrors* widthPi0LHC10f6a_7TeV = (TGraphErrors*)EventStatsFile->Get("widthPi0perRun_pp7TeV_LHC10f6a");
		TGraphErrors* massPi0LHC10f6a_7TeV = (TGraphErrors*)EventStatsFile->Get("massPi0perRun_pp7TeV_LHC10f6a");
		TGraphErrors* widthEtaLHC10f6a_7TeV = (TGraphErrors*)EventStatsFile->Get("widthEtaperRun_pp7TeV_LHC10f6a");
		TGraphErrors* massEtaLHC10f6a_7TeV = (TGraphErrors*)EventStatsFile->Get("massEtaperRun_pp7TeV_LHC10f6a");

		TGraphErrors* fractionOfGammasLHC10f6_7TeV = (TGraphErrors*)EventStatsFile->Get("fracGammas_pp7TeV_LHC10f6");
		TGraphErrors* fractionOfPi0LHC10f6_7TeV = (TGraphErrors*)EventStatsFile->Get("fractionOfPi0InCent_pp7TeV_LHC10f6");
		TGraphErrors* fractionOfEtaLHC10f6_7TeV = (TGraphErrors*)EventStatsFile->Get("fractionOfEtaInCent_pp7TeV_LHC10f6");
		TGraphErrors* fractionOfWOVtxLHC10f6_7TeV = (TGraphErrors*)EventStatsFile->Get("fracWOVtx_pp7TeV_LHC10f6");
		TGraphErrors* fractionOfWVtxOutside10cmLHC10f6_7TeV = (TGraphErrors*)EventStatsFile->Get("fracWVtxOutside10cm_pp7TeV_LHC10f6");
		TGraphErrors* fractionOfGoodEventsLHC10f6_7TeV = (TGraphErrors*)EventStatsFile->Get("fracGoodEvents_pp7TeV_LHC10f6");
		TGraphErrors* fractionOfNormAllLHC10f6_7TeV = (TGraphErrors*)EventStatsFile->Get("fracNormAll_pp7TeV_LHC10f6");
		TGraphErrors* fractionOfNormMinBiasLHC10f6_7TeV = (TGraphErrors*)EventStatsFile->Get("fracNormMinBias_pp7TeV_LHC10f6");
		TGraphErrors* fractionOfPileUpLHC10f6_7TeV = (TGraphErrors*)EventStatsFile->Get("fracPileUp_pp7TeV_LHC10f6");	
		TGraphErrors* meanTrackMultTPCDataLHC10f6_7TeV = (TGraphErrors*)EventStatsFile->Get("meanTrackMultTPCInCent_pp7TeV_LHC10f6");
		TGraphErrors* widthPi0LHC10f6_7TeV = (TGraphErrors*)EventStatsFile->Get("widthPi0perRun_pp7TeV_LHC10f6");
		TGraphErrors* massPi0LHC10f6_7TeV = (TGraphErrors*)EventStatsFile->Get("massPi0perRun_pp7TeV_LHC10f6");
		TGraphErrors* widthEtaLHC10f6_7TeV = (TGraphErrors*)EventStatsFile->Get("widthEtaperRun_pp7TeV_LHC10f6");
		TGraphErrors* massEtaLHC10f6_7TeV = (TGraphErrors*)EventStatsFile->Get("massEtaperRun_pp7TeV_LHC10f6");

		TGraphErrors* fractionOfGammasLHC10e20_7TeV = (TGraphErrors*)EventStatsFile->Get("fracGammas_pp7TeV_LHC10e20");
		TGraphErrors* fractionOfPi0LHC10e20_7TeV = (TGraphErrors*)EventStatsFile->Get("fractionOfPi0InCent_pp7TeV_LHC10e20");
		TGraphErrors* fractionOfEtaLHC10e20_7TeV = (TGraphErrors*)EventStatsFile->Get("fractionOfEtaInCent_pp7TeV_LHC10e20");
		TGraphErrors* fractionOfWOVtxLHC10e20_7TeV = (TGraphErrors*)EventStatsFile->Get("fracWOVtx_pp7TeV_LHC10e20");
		TGraphErrors* fractionOfWVtxOutside10cmLHC10e20_7TeV = (TGraphErrors*)EventStatsFile->Get("fracWVtxOutside10cm_pp7TeV_LHC10e20");
		TGraphErrors* fractionOfGoodEventsLHC10e20_7TeV = (TGraphErrors*)EventStatsFile->Get("fracGoodEvents_pp7TeV_LHC10e20");
		TGraphErrors* fractionOfNormAllLHC10e20_7TeV = (TGraphErrors*)EventStatsFile->Get("fracNormAll_pp7TeV_LHC10e20");
		TGraphErrors* fractionOfNormMinBiasLHC10e20_7TeV = (TGraphErrors*)EventStatsFile->Get("fracNormMinBias_pp7TeV_LHC10e20");
		TGraphErrors* fractionOfPileUpLHC10e20_7TeV = (TGraphErrors*)EventStatsFile->Get("fracPileUp_pp7TeV_LHC10e20");	
		TGraphErrors* meanTrackMultTPCDataLHC10e20_7TeV = (TGraphErrors*)EventStatsFile->Get("meanTrackMultTPCInCent_pp7TeV_LHC10e20");
		TGraphErrors* widthPi0LHC10e20_7TeV = (TGraphErrors*)EventStatsFile->Get("widthPi0perRun_pp7TeV_LHC10e20");
		TGraphErrors* massPi0LHC10e20_7TeV = (TGraphErrors*)EventStatsFile->Get("massPi0perRun_pp7TeV_LHC10e20");
		TGraphErrors* widthEtaLHC10e20_7TeV = (TGraphErrors*)EventStatsFile->Get("widthEtaperRun_pp7TeV_LHC10e20");
		TGraphErrors* massEtaLHC10e20_7TeV = (TGraphErrors*)EventStatsFile->Get("massEtaperRun_pp7TeV_LHC10e20");

		TGraphErrors* fractionOfGammasLHC10e21_7TeV = (TGraphErrors*)EventStatsFile->Get("fracGammas_pp7TeV_LHC10e21");
		TGraphErrors* fractionOfPi0LHC10e21_7TeV = (TGraphErrors*)EventStatsFile->Get("fractionOfPi0InCent_pp7TeV_LHC10e21");
		TGraphErrors* fractionOfEtaLHC10e21_7TeV = (TGraphErrors*)EventStatsFile->Get("fractionOfEtaInCent_pp7TeV_LHC10e21");
		TGraphErrors* fractionOfWOVtxLHC10e21_7TeV = (TGraphErrors*)EventStatsFile->Get("fracWOVtx_pp7TeV_LHC10e21");
		TGraphErrors* fractionOfWVtxOutside10cmLHC10e21_7TeV = (TGraphErrors*)EventStatsFile->Get("fracWVtxOutside10cm_pp7TeV_LHC10e21");
		TGraphErrors* fractionOfGoodEventsLHC10e21_7TeV = (TGraphErrors*)EventStatsFile->Get("fracGoodEvents_pp7TeV_LHC10e21");
		TGraphErrors* fractionOfNormAllLHC10e21_7TeV = (TGraphErrors*)EventStatsFile->Get("fracNormAll_pp7TeV_LHC10e21");
		TGraphErrors* fractionOfNormMinBiasLHC10e21_7TeV = (TGraphErrors*)EventStatsFile->Get("fracNormMinBias_pp7TeV_LHC10e21");
		TGraphErrors* fractionOfPileUpLHC10e21_7TeV = (TGraphErrors*)EventStatsFile->Get("fracPileUp_pp7TeV_LHC10e21");	
		TGraphErrors* meanTrackMultTPCDataLHC10e21_7TeV = (TGraphErrors*)EventStatsFile->Get("meanTrackMultTPCInCent_pp7TeV_LHC10e21");
		TGraphErrors* widthPi0LHC10e21_7TeV = (TGraphErrors*)EventStatsFile->Get("widthPi0perRun_pp7TeV_LHC10e21");
		TGraphErrors* massPi0LHC10e21_7TeV = (TGraphErrors*)EventStatsFile->Get("massPi0perRun_pp7TeV_LHC10e21");
		TGraphErrors* widthEtaLHC10e21_7TeV = (TGraphErrors*)EventStatsFile->Get("widthEtaperRun_pp7TeV_LHC10e21");
		TGraphErrors* massEtaLHC10e21_7TeV = (TGraphErrors*)EventStatsFile->Get("massEtaperRun_pp7TeV_LHC10e21");
	
		TGraphErrors* fractionOfGammasLHC10x_900GeV = (TGraphErrors*)EventStatsFile->Get("fracGammas_pp900GeV_LHC10x");
		TGraphErrors* fractionOfPi0LHC10x_900GeV = (TGraphErrors*)EventStatsFile->Get("fractionOfPi0InCent_pp900GeV_LHC10x");
		TGraphErrors* fractionOfEtaLHC10x_900GeV = (TGraphErrors*)EventStatsFile->Get("fractionOfEtaInCent_pp900GeV_LHC10x");
		TGraphErrors* fractionOfWOVtxLHC10x_900GeV = (TGraphErrors*)EventStatsFile->Get("fracWOVtx_pp900GeV_LHC10x");
		TGraphErrors* fractionOfWVtxOutside10cmLHC10x_900GeV = (TGraphErrors*)EventStatsFile->Get("fracWVtxOutside10cm_pp900GeV_LHC10x");
		TGraphErrors* fractionOfGoodEventsLHC10x_900GeV = (TGraphErrors*)EventStatsFile->Get("fracGoodEvents_pp900GeV_LHC10x");
		TGraphErrors* fractionOfNormAllLHC10x_900GeV = (TGraphErrors*)EventStatsFile->Get("fracNormAll_pp900GeV_LHC10x");
		TGraphErrors* fractionOfNormMinBiasLHC10x_900GeV = (TGraphErrors*)EventStatsFile->Get("fracNormMinBias_pp900GeV_LHC10x");
		TGraphErrors* fractionOfPileUpLHC10x_900GeV = (TGraphErrors*)EventStatsFile->Get("fracPileUp_pp900GeV_LHC10x");
		TGraphErrors* meanTrackMultTPCDataLHC10x_900GeV = (TGraphErrors*)EventStatsFile->Get("meanTrackMultTPCInCent_pp900GeV_LHC10x");
		TGraphErrors* widthPi0LHC10x_900GeV = (TGraphErrors*)EventStatsFile->Get("widthPi0perRun_pp900GeV_LHC10x");
		TGraphErrors* massPi0LHC10x_900GeV = (TGraphErrors*)EventStatsFile->Get("massPi0perRun_pp900GeV_LHC10x");
		TGraphErrors* widthEtaLHC10x_900GeV = (TGraphErrors*)EventStatsFile->Get("widthEtaperRun_pp900GeV_LHC10x");
		TGraphErrors* massEtaLHC10x_900GeV = (TGraphErrors*)EventStatsFile->Get("massEtaperRun_pp900GeV_LHC10x");
		
		TGraphErrors* fractionOfGammasLHC10e13_900GeV = (TGraphErrors*)EventStatsFile->Get("fracGammas_pp900GeV_LHC10e13");
		TGraphErrors* fractionOfPi0LHC10e13_900GeV = (TGraphErrors*)EventStatsFile->Get("fractionOfPi0InCent_pp900GeV_LHC10e13");
		TGraphErrors* fractionOfEtaLHC10e13_900GeV = (TGraphErrors*)EventStatsFile->Get("fractionOfEtaInCent_pp900GeV_LHC10e13");
		TGraphErrors* fractionOfWOVtxLHC10e13_900GeV = (TGraphErrors*)EventStatsFile->Get("fracWOVtx_pp900GeV_LHC10e13");
		TGraphErrors* fractionOfWVtxOutside10cmLHC10e13_900GeV = (TGraphErrors*)EventStatsFile->Get("fracWVtxOutside10cm_pp900GeV_LHC10e13");
		TGraphErrors* fractionOfGoodEventsLHC10e13_900GeV = (TGraphErrors*)EventStatsFile->Get("fracGoodEvents_pp900GeV_LHC10e13");
		TGraphErrors* fractionOfNormAllLHC10e13_900GeV = (TGraphErrors*)EventStatsFile->Get("fracNormAll_pp900GeV_LHC10e13");
		TGraphErrors* fractionOfNormMinBiasLHC10e13_900GeV = (TGraphErrors*)EventStatsFile->Get("fracNormMinBias_pp900GeV_LHC10e13");
		TGraphErrors* fractionOfPileUpLHC10e13_900GeV = (TGraphErrors*)EventStatsFile->Get("fracPileUp_pp900GeV_LHC10e13");
		TGraphErrors* meanTrackMultTPCDataLHC10e13_900GeV = (TGraphErrors*)EventStatsFile->Get("meanTrackMultTPCInCent_pp900GeV_LHC10e13");
		TGraphErrors* widthPi0LHC10e13_900GeV = (TGraphErrors*)EventStatsFile->Get("widthPi0perRun_pp900GeV_LHC10e13");
		TGraphErrors* massPi0LHC10e13_900GeV = (TGraphErrors*)EventStatsFile->Get("massPi0perRun_pp900GeV_LHC10e13");
		TGraphErrors* widthEtaLHC10e13_900GeV = (TGraphErrors*)EventStatsFile->Get("widthEtaperRun_pp900GeV_LHC10e13");
		TGraphErrors* massEtaLHC10e13_900GeV = (TGraphErrors*)EventStatsFile->Get("massEtaperRun_pp900GeV_LHC10e13");

		TGraphErrors* fractionOfGammasLHC10e12_900GeV = (TGraphErrors*)EventStatsFile->Get("fracGammas_pp900GeV_LHC10e12");
		TGraphErrors* fractionOfPi0LHC10e12_900GeV = (TGraphErrors*)EventStatsFile->Get("fractionOfPi0InCent_pp900GeV_LHC10e12");
		TGraphErrors* fractionOfEtaLHC10e12_900GeV = (TGraphErrors*)EventStatsFile->Get("fractionOfEtaInCent_pp900GeV_LHC10e12");
		TGraphErrors* fractionOfWOVtxLHC10e12_900GeV = (TGraphErrors*)EventStatsFile->Get("fracWOVtx_pp900GeV_LHC10e12");
		TGraphErrors* fractionOfWVtxOutside10cmLHC10e12_900GeV = (TGraphErrors*)EventStatsFile->Get("fracWVtxOutside10cm_pp900GeV_LHC10e12");
		TGraphErrors* fractionOfGoodEventsLHC10e12_900GeV = (TGraphErrors*)EventStatsFile->Get("fracGoodEvents_pp900GeV_LHC10e12");
		TGraphErrors* fractionOfNormAllLHC10e12_900GeV = (TGraphErrors*)EventStatsFile->Get("fracNormAll_pp900GeV_LHC10e12");
		TGraphErrors* fractionOfNormMinBiasLHC10e12_900GeV = (TGraphErrors*)EventStatsFile->Get("fracNormMinBias_pp900GeV_LHC10e12");
		TGraphErrors* fractionOfPileUpLHC10e12_900GeV = (TGraphErrors*)EventStatsFile->Get("fracPileUp_pp900GeV_LHC10e12");
		TGraphErrors* meanTrackMultTPCDataLHC10e12_900GeV = (TGraphErrors*)EventStatsFile->Get("meanTrackMultTPCInCent_pp900GeV_LHC10e12");
		TGraphErrors* widthPi0LHC10e12_900GeV = (TGraphErrors*)EventStatsFile->Get("widthPi0perRun_pp900GeV_LHC10e12");
		TGraphErrors* massPi0LHC10e12_900GeV = (TGraphErrors*)EventStatsFile->Get("massPi0perRun_pp900GeV_LHC10e12");
		TGraphErrors* widthEtaLHC10e12_900GeV = (TGraphErrors*)EventStatsFile->Get("widthEtaperRun_pp900GeV_LHC10e12");
		TGraphErrors* massEtaLHC10e12_900GeV = (TGraphErrors*)EventStatsFile->Get("massEtaperRun_pp900GeV_LHC10e12");
		
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


      TGraphErrors* fractionOfGammasLHC13x_pPb = (TGraphErrors*)EventStatsFile->Get("fracGammas_pPb_LHC13x");
      TGraphErrors* fractionOfPi0LHC13x_pPb = (TGraphErrors*)EventStatsFile->Get("fractionOfPi0InCent_pPb_LHC13x");
      TGraphErrors* fractionOfEtaLHC13x_pPb = (TGraphErrors*)EventStatsFile->Get("fractionOfEtaInCent_pPb_LHC13x");
      TGraphErrors* fractionOfWOVtxLHC13x_pPb = (TGraphErrors*)EventStatsFile->Get("fracWOVtx_pPb_LHC13x");
      TGraphErrors* fractionOfWVtxOutside10cmLHC13x_pPb = (TGraphErrors*)EventStatsFile->Get("fracWVtxOutside10cm_pPb_LHC13x");
      TGraphErrors* fractionOfGoodEventsLHC13x_pPb = (TGraphErrors*)EventStatsFile->Get("fracGoodEvents_pPb_LHC13x");
      TGraphErrors* fractionOfNormAllLHC13x_pPb = (TGraphErrors*)EventStatsFile->Get("fracNormAll_pPb_LHC13x");
      TGraphErrors* fractionOfNormMinBiasLHC13x_pPb = (TGraphErrors*)EventStatsFile->Get("fracNormMinBias_pPb_LHC13x");
      TGraphErrors* fractionOfPileUpLHC13x_pPb = (TGraphErrors*)EventStatsFile->Get("fracPileUp_pPb_LHC13x");
      TGraphErrors* meanTrackMultTPCDataLHC13x_pPb = (TGraphErrors*)EventStatsFile->Get("meanTrackMultTPCInCent_pPb_LHC13x");
      TGraphErrors* widthPi0LHC13x_pPb = (TGraphErrors*)EventStatsFile->Get("widthPi0perRun_pPb_LHC13x");
      TGraphErrors* massPi0LHC13x_pPb = (TGraphErrors*)EventStatsFile->Get("massPi0perRun_pPb_LHC13x");
      TGraphErrors* widthEtaLHC13x_pPb = (TGraphErrors*)EventStatsFile->Get("widthEtaperRun_pPb_LHC13x");
      TGraphErrors* massEtaLHC13x_pPb = (TGraphErrors*)EventStatsFile->Get("massEtaperRun_pPb_LHC13x");

      TGraphErrors* fractionOfGammasLHC13b_fix_1_pPb = (TGraphErrors*)EventStatsFile->Get("fracGammas_pPb_LHC13b_fix_1");
      TGraphErrors* fractionOfPi0LHC13b_fix_1_pPb = (TGraphErrors*)EventStatsFile->Get("fractionOfPi0InCent_pPb_LHC13b_fix_1");
      TGraphErrors* fractionOfEtaLHC13b_fix_1_pPb = (TGraphErrors*)EventStatsFile->Get("fracGammas_pPb_LHC13b_fix_1");
      TGraphErrors* fractionOfWOVtxLHC13b_fix_1_pPb = (TGraphErrors*)EventStatsFile->Get("fracWOVtx_pPb_LHC13b_fix_1");
      TGraphErrors* fractionOfWVtxOutside10cmLHC13b_fix_1_pPb = (TGraphErrors*)EventStatsFile->Get("fracWVtxOutside10cm_pPb_LHC13b_fix_1");
      TGraphErrors* fractionOfGoodEventsLHC13b_fix_1_pPb = (TGraphErrors*)EventStatsFile->Get("fracGoodEvents_pPb_LHC13b_fix_1");
      TGraphErrors* fractionOfNormAllLHC13b_fix_1_pPb = (TGraphErrors*)EventStatsFile->Get("fracNormAll_pPb_LHC13b_fix_1");
      TGraphErrors* fractionOfNormMinBiasLHC13b_fix_1_pPb = (TGraphErrors*)EventStatsFile->Get("fracNormMinBias_pPb_LHC13b_fix_1");
      TGraphErrors* fractionOfPileUpLHC13b_fix_1_pPb = (TGraphErrors*)EventStatsFile->Get("fracPileUp_pPb_LHC13b_fix_1");
      TGraphErrors* meanTrackMultTPCDataLHC13b_fix_1_pPb = (TGraphErrors*)EventStatsFile->Get("meanTrackMultTPCInCent_pPb_LHC13b_fix_1");
      TGraphErrors* widthPi0LHC13b_fix_1_pPb = (TGraphErrors*)EventStatsFile->Get("widthPi0perRun_pPb_LHC13b_fix_1");
      TGraphErrors* massPi0LHC13b_fix_1_pPb = (TGraphErrors*)EventStatsFile->Get("massPi0perRun_pPb_LHC13b_fix_1");
      TGraphErrors* widthEtaLHC13b_fix_1_pPb = (TGraphErrors*)EventStatsFile->Get("widthEtaperRun_pPb_LHC13b_fix_1");
      TGraphErrors* massEtaLHC13b_fix_1_pPb = (TGraphErrors*)EventStatsFile->Get("massEtaperRun_pPb_LHC13b_fix_1");
   
      TGraphErrors* fractionOfGammasLHC13b_fix_2_pPb = (TGraphErrors*)EventStatsFile->Get("fracGammas_pPb_LHC13b_fix_2");
      TGraphErrors* fractionOfPi0LHC13b_fix_2_pPb = (TGraphErrors*)EventStatsFile->Get("fractionOfPi0InCent_pPb_LHC13b_fix_2");
      TGraphErrors* fractionOfEtaLHC13b_fix_2_pPb = (TGraphErrors*)EventStatsFile->Get("fractionOfEtaInCent_pPb_LHC13b_fix_2");
      TGraphErrors* fractionOfWOVtxLHC13b_fix_2_pPb = (TGraphErrors*)EventStatsFile->Get("fracWOVtx_pPb_LHC13b_fix_2");
      TGraphErrors* fractionOfWVtxOutside10cmLHC13b_fix_2_pPb = (TGraphErrors*)EventStatsFile->Get("fracWVtxOutside10cm_pPb_LHC13b_fix_2");
      TGraphErrors* fractionOfGoodEventsLHC13b_fix_2_pPb = (TGraphErrors*)EventStatsFile->Get("fracGoodEvents_pPb_LHC13b_fix_2");
      TGraphErrors* fractionOfNormAllLHC13b_fix_2_pPb = (TGraphErrors*)EventStatsFile->Get("fracNormAll_pPb_LHC13b_fix_2");
      TGraphErrors* fractionOfNormMinBiasLHC13b_fix_2_pPb = (TGraphErrors*)EventStatsFile->Get("fracNormMinBias_pPb_LHC13b_fix_2");
      TGraphErrors* fractionOfPileUpLHC13b_fix_2_pPb = (TGraphErrors*)EventStatsFile->Get("fracPileUp_pPb_LHC13b_fix_2");  
      TGraphErrors* meanTrackMultTPCDataLHC13b_fix_2_pPb = (TGraphErrors*)EventStatsFile->Get("meanTrackMultTPCInCent_pPb_LHC13b_fix_2");
      TGraphErrors* widthPi0LHC13b_fix_2_pPb = (TGraphErrors*)EventStatsFile->Get("widthPi0perRun_pPb_LHC13b_fix_2");
      TGraphErrors* massPi0LHC13b_fix_2_pPb = (TGraphErrors*)EventStatsFile->Get("massPi0perRun_pPb_LHC13b_fix_2");
      TGraphErrors* widthEtaLHC13b_fix_2_pPb = (TGraphErrors*)EventStatsFile->Get("widthEtaperRun_pPb_LHC13b_fix_2");
      TGraphErrors* massEtaLHC13b_fix_2_pPb = (TGraphErrors*)EventStatsFile->Get("massEtaperRun_pPb_LHC13b_fix_2");

      TGraphErrors* fractionOfGammasLHC13b_fix_3_pPb = (TGraphErrors*)EventStatsFile->Get("fracGammas_pPb_LHC13b_fix_3");
      TGraphErrors* fractionOfPi0LHC13b_fix_3_pPb = (TGraphErrors*)EventStatsFile->Get("fractionOfPi0InCent_pPb_LHC13b_fix_3");
      TGraphErrors* fractionOfEtaLHC13b_fix_3_pPb = (TGraphErrors*)EventStatsFile->Get("fractionOfEtaInCent_pPb_LHC13b_fix_3");
      TGraphErrors* fractionOfWOVtxLHC13b_fix_3_pPb = (TGraphErrors*)EventStatsFile->Get("fracWOVtx_pPb_LHC13b_fix_3");
      TGraphErrors* fractionOfWVtxOutside10cmLHC13b_fix_3_pPb = (TGraphErrors*)EventStatsFile->Get("fracWVtxOutside10cm_pPb_LHC13b_fix_3");
      TGraphErrors* fractionOfGoodEventsLHC13b_fix_3_pPb = (TGraphErrors*)EventStatsFile->Get("fracGoodEvents_pPb_LHC13b_fix_3");
      TGraphErrors* fractionOfNormAllLHC13b_fix_3_pPb = (TGraphErrors*)EventStatsFile->Get("fracNormAll_pPb_LHC13b_fix_3");
      TGraphErrors* fractionOfNormMinBiasLHC13b_fix_3_pPb = (TGraphErrors*)EventStatsFile->Get("fracNormMinBias_pPb_LHC13b_fix_3");
      TGraphErrors* fractionOfPileUpLHC13b_fix_3_pPb = (TGraphErrors*)EventStatsFile->Get("fracPileUp_pPb_LHC13b_fix_3");  
      TGraphErrors* meanTrackMultTPCDataLHC13b_fix_3_pPb = (TGraphErrors*)EventStatsFile->Get("meanTrackMultTPCInCent_pPb_LHC13b_fix_3");
      TGraphErrors* widthPi0LHC13b_fix_3_pPb = (TGraphErrors*)EventStatsFile->Get("widthPi0perRun_pPb_LHC13b_fix_3");
      TGraphErrors* massPi0LHC13b_fix_3_pPb = (TGraphErrors*)EventStatsFile->Get("massPi0perRun_pPb_LHC13b_fix_3");
      TGraphErrors* widthEtaLHC13b_fix_3_pPb = (TGraphErrors*)EventStatsFile->Get("widthEtaperRun_pPb_LHC13b_fix_3");
      TGraphErrors* massEtaLHC13b_fix_3_pPb = (TGraphErrors*)EventStatsFile->Get("massEtaperRun_pPb_LHC13b_fix_3");

		
	Color_t	colorComb0005				= kRed+1;
	Color_t	colorComb0510				= 807;
	Color_t	colorComb1020				= 800;
	Color_t	colorComb2040				= kGreen+2;
	Color_t	colorComb4060				= kCyan+2;
	Color_t	colorComb6080				= kBlue+1;

	Color_t	colorCombMC0005				= kRed+3;
	Color_t	colorCombMC0510				= 807+2;
	Color_t	colorCombMC1020				= 800+2;
	Color_t	colorCombMC2040				= kGreen+4;
	Color_t	colorCombMC4060				= kCyan+4;
	Color_t	colorCombMC6080				= kBlue+3;

	
	Style_t 	markerStyleCommmonSpectrum0005 	= 20 ;
	Style_t 	markerStyleCommmonSpectrum0510 	= 21 ;
	Style_t 	markerStyleCommmonSpectrum1020 	= 29 ;
	Style_t 	markerStyleCommmonSpectrum2040 	= 33 ;
	Style_t 	markerStyleCommmonSpectrum4060 	= 20 ;
	Style_t 	markerStyleCommmonSpectrum6080 	= 21 ;

	Style_t 	markerStyleCommmonSpectrumMC0005 	= 24 ;
	Style_t 	markerStyleCommmonSpectrumMC0510 	= 25 ;
	Style_t 	markerStyleCommmonSpectrumMC1020 	= 30 ;
	Style_t 	markerStyleCommmonSpectrumMC2040 	= 27 ;
	Style_t 	markerStyleCommmonSpectrumMC4060 	= 24 ;
	Style_t 	markerStyleCommmonSpectrumMC6080 	= 25 ;

	
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

	DrawGammaSetMarkerTGraphErr( fractionOfGammasData0005,  markerStyleCommmonSpectrum0005, markerSizeCommonSpectrum0005, colorComb0005, colorComb0005);
	DrawGammaSetMarkerTGraphErr( fractionOfGammasData0510,  markerStyleCommmonSpectrum0510, markerSizeCommonSpectrum0510, colorComb0510, colorComb0510);
	DrawGammaSetMarkerTGraphErr( fractionOfGammasData1020,  markerStyleCommmonSpectrum1020, markerSizeCommonSpectrum1020, colorComb1020, colorComb1020);
	DrawGammaSetMarkerTGraphErr( fractionOfGammasData2040,  markerStyleCommmonSpectrum2040, markerSizeCommonSpectrum2040, colorComb2040, colorComb2040);
	DrawGammaSetMarkerTGraphErr( fractionOfGammasData4060,  markerStyleCommmonSpectrum4060, markerSizeCommonSpectrum4060, colorComb4060, colorComb4060);
	DrawGammaSetMarkerTGraphErr( fractionOfGammasData6080,  markerStyleCommmonSpectrum6080, markerSizeCommonSpectrum6080, colorComb6080, colorComb6080);
	
	DrawGammaSetMarkerTGraphErr( fractionOfPi0Data0005,  markerStyleCommmonSpectrum0005, markerSizeCommonSpectrum0005, colorComb0005, colorComb0005);
	DrawGammaSetMarkerTGraphErr( fractionOfPi0Data0510,  markerStyleCommmonSpectrum0510, markerSizeCommonSpectrum0510, colorComb0510, colorComb0510);
	DrawGammaSetMarkerTGraphErr( fractionOfPi0Data1020,  markerStyleCommmonSpectrum1020, markerSizeCommonSpectrum1020, colorComb1020, colorComb1020);
	DrawGammaSetMarkerTGraphErr( fractionOfPi0Data2040,  markerStyleCommmonSpectrum2040, markerSizeCommonSpectrum2040, colorComb2040, colorComb2040);
	DrawGammaSetMarkerTGraphErr( fractionOfPi0Data4060,  markerStyleCommmonSpectrum4060, markerSizeCommonSpectrum4060, colorComb4060, colorComb4060);
	DrawGammaSetMarkerTGraphErr( fractionOfPi0Data6080,  markerStyleCommmonSpectrum6080, markerSizeCommonSpectrum6080, colorComb6080, colorComb6080);
	
	DrawGammaSetMarkerTGraphErr( massPi0Data0005,  markerStyleCommmonSpectrum0005, markerSizeCommonSpectrum0005, colorComb0005, colorComb0005);
	DrawGammaSetMarkerTGraphErr( massPi0Data0510,  markerStyleCommmonSpectrum0510, markerSizeCommonSpectrum0510, colorComb0510, colorComb0510);
	DrawGammaSetMarkerTGraphErr( massPi0Data1020,  markerStyleCommmonSpectrum1020, markerSizeCommonSpectrum1020, colorComb1020, colorComb1020);
	DrawGammaSetMarkerTGraphErr( massPi0Data2040,  markerStyleCommmonSpectrum2040, markerSizeCommonSpectrum2040, colorComb2040, colorComb2040);
	DrawGammaSetMarkerTGraphErr( massPi0Data4060,  markerStyleCommmonSpectrum4060, markerSizeCommonSpectrum4060, colorComb4060, colorComb4060);
	DrawGammaSetMarkerTGraphErr( massPi0Data6080,  markerStyleCommmonSpectrum6080, markerSizeCommonSpectrum6080, colorComb6080, colorComb6080);
	
	DrawGammaSetMarkerTGraphErr( widthPi0Data0005,  markerStyleCommmonSpectrum0005, markerSizeCommonSpectrum0005, colorComb0005, colorComb0005);
	DrawGammaSetMarkerTGraphErr( widthPi0Data0510,  markerStyleCommmonSpectrum0510, markerSizeCommonSpectrum0510, colorComb0510, colorComb0510);
	DrawGammaSetMarkerTGraphErr( widthPi0Data1020,  markerStyleCommmonSpectrum1020, markerSizeCommonSpectrum1020, colorComb1020, colorComb1020);
	DrawGammaSetMarkerTGraphErr( widthPi0Data2040,  markerStyleCommmonSpectrum2040, markerSizeCommonSpectrum2040, colorComb2040, colorComb2040);
	DrawGammaSetMarkerTGraphErr( widthPi0Data4060,  markerStyleCommmonSpectrum4060, markerSizeCommonSpectrum4060, colorComb4060, colorComb4060);
	DrawGammaSetMarkerTGraphErr( widthPi0Data6080,  markerStyleCommmonSpectrum6080, markerSizeCommonSpectrum6080, colorComb6080, colorComb6080);
	
	DrawGammaSetMarkerTGraphErr( fractionOfGoodEventsData0005,  markerStyleCommmonSpectrum0005, markerSizeCommonSpectrum0005, colorComb0005, colorComb0005);
	DrawGammaSetMarkerTGraphErr( fractionOfGoodEventsData0510,  markerStyleCommmonSpectrum0510, markerSizeCommonSpectrum0510, colorComb0510, colorComb0510);
	DrawGammaSetMarkerTGraphErr( fractionOfGoodEventsData1020,  markerStyleCommmonSpectrum1020, markerSizeCommonSpectrum1020, colorComb1020, colorComb1020);
	DrawGammaSetMarkerTGraphErr( fractionOfGoodEventsData2040,  markerStyleCommmonSpectrum2040, markerSizeCommonSpectrum2040, colorComb2040, colorComb2040);
	DrawGammaSetMarkerTGraphErr( fractionOfGoodEventsData4060,  markerStyleCommmonSpectrum4060, markerSizeCommonSpectrum4060, colorComb4060, colorComb4060);
	DrawGammaSetMarkerTGraphErr( fractionOfGoodEventsData6080,  markerStyleCommmonSpectrum6080, markerSizeCommonSpectrum6080, colorComb6080, colorComb6080);
	
	DrawGammaSetMarkerTGraphErr( fractionOfNormAllData0005,  markerStyleCommmonSpectrum0005, markerSizeCommonSpectrum0005, colorComb0005, colorComb0005);
	DrawGammaSetMarkerTGraphErr( fractionOfNormAllData0510,  markerStyleCommmonSpectrum0510, markerSizeCommonSpectrum0510, colorComb0510, colorComb0510);
	DrawGammaSetMarkerTGraphErr( fractionOfNormAllData1020,  markerStyleCommmonSpectrum1020, markerSizeCommonSpectrum1020, colorComb1020, colorComb1020);
	DrawGammaSetMarkerTGraphErr( fractionOfNormAllData2040,  markerStyleCommmonSpectrum2040, markerSizeCommonSpectrum2040, colorComb2040, colorComb2040);
	DrawGammaSetMarkerTGraphErr( fractionOfNormAllData4060,  markerStyleCommmonSpectrum4060, markerSizeCommonSpectrum4060, colorComb4060, colorComb4060);
	DrawGammaSetMarkerTGraphErr( fractionOfNormAllData6080,  markerStyleCommmonSpectrum6080, markerSizeCommonSpectrum6080, colorComb6080, colorComb6080);
	
	DrawGammaSetMarkerTGraphErr( fractionOfNormMinBiasData0005,  markerStyleCommmonSpectrum0005, markerSizeCommonSpectrum0005, colorComb0005, colorComb0005);
	DrawGammaSetMarkerTGraphErr( fractionOfNormMinBiasData0510,  markerStyleCommmonSpectrum0510, markerSizeCommonSpectrum0510, colorComb0510, colorComb0510);
	DrawGammaSetMarkerTGraphErr( fractionOfNormMinBiasData1020,  markerStyleCommmonSpectrum1020, markerSizeCommonSpectrum1020, colorComb1020, colorComb1020);
	DrawGammaSetMarkerTGraphErr( fractionOfNormMinBiasData2040,  markerStyleCommmonSpectrum2040, markerSizeCommonSpectrum2040, colorComb2040, colorComb2040);
	DrawGammaSetMarkerTGraphErr( fractionOfNormMinBiasData4060,  markerStyleCommmonSpectrum4060, markerSizeCommonSpectrum4060, colorComb4060, colorComb4060);
	DrawGammaSetMarkerTGraphErr( fractionOfNormMinBiasData6080,  markerStyleCommmonSpectrum6080, markerSizeCommonSpectrum6080, colorComb6080, colorComb6080);
	
	DrawGammaSetMarkerTGraphErr( fractionOfPileUpData0005,  markerStyleCommmonSpectrum0005, markerSizeCommonSpectrum0005, colorComb0005, colorComb0005);
	DrawGammaSetMarkerTGraphErr( fractionOfPileUpData0510,  markerStyleCommmonSpectrum0510, markerSizeCommonSpectrum0510, colorComb0510, colorComb0510);
	DrawGammaSetMarkerTGraphErr( fractionOfPileUpData1020,  markerStyleCommmonSpectrum1020, markerSizeCommonSpectrum1020, colorComb1020, colorComb1020);
	DrawGammaSetMarkerTGraphErr( fractionOfPileUpData2040,  markerStyleCommmonSpectrum2040, markerSizeCommonSpectrum2040, colorComb2040, colorComb2040);
	DrawGammaSetMarkerTGraphErr( fractionOfPileUpData4060,  markerStyleCommmonSpectrum4060, markerSizeCommonSpectrum4060, colorComb4060, colorComb4060);
	DrawGammaSetMarkerTGraphErr( fractionOfPileUpData6080,  markerStyleCommmonSpectrum6080, markerSizeCommonSpectrum6080, colorComb6080, colorComb6080);
	
	DrawGammaSetMarkerTGraphErr( fractionOfWOVtxData0005,  markerStyleCommmonSpectrum0005, markerSizeCommonSpectrum0005, colorComb0005, colorComb0005);
	DrawGammaSetMarkerTGraphErr( fractionOfWOVtxData0510,  markerStyleCommmonSpectrum0510, markerSizeCommonSpectrum0510, colorComb0510, colorComb0510);
	DrawGammaSetMarkerTGraphErr( fractionOfWOVtxData1020,  markerStyleCommmonSpectrum1020, markerSizeCommonSpectrum1020, colorComb1020, colorComb1020);
	DrawGammaSetMarkerTGraphErr( fractionOfWOVtxData2040,  markerStyleCommmonSpectrum2040, markerSizeCommonSpectrum2040, colorComb2040, colorComb2040);
	DrawGammaSetMarkerTGraphErr( fractionOfWOVtxData4060,  markerStyleCommmonSpectrum4060, markerSizeCommonSpectrum4060, colorComb4060, colorComb4060);
	DrawGammaSetMarkerTGraphErr( fractionOfWOVtxData6080,  markerStyleCommmonSpectrum6080, markerSizeCommonSpectrum6080, colorComb6080, colorComb6080);
	
	DrawGammaSetMarkerTGraphErr( fractionOfWVtxOutside10cmData0005,  markerStyleCommmonSpectrum0005, markerSizeCommonSpectrum0005, colorComb0005, colorComb0005);
	DrawGammaSetMarkerTGraphErr( fractionOfWVtxOutside10cmData0510,  markerStyleCommmonSpectrum0510, markerSizeCommonSpectrum0510, colorComb0510, colorComb0510);
	DrawGammaSetMarkerTGraphErr( fractionOfWVtxOutside10cmData1020,  markerStyleCommmonSpectrum1020, markerSizeCommonSpectrum1020, colorComb1020, colorComb1020);
	DrawGammaSetMarkerTGraphErr( fractionOfWVtxOutside10cmData2040,  markerStyleCommmonSpectrum2040, markerSizeCommonSpectrum2040, colorComb2040, colorComb2040);
	DrawGammaSetMarkerTGraphErr( fractionOfWVtxOutside10cmData4060,  markerStyleCommmonSpectrum4060, markerSizeCommonSpectrum4060, colorComb4060, colorComb4060);
	DrawGammaSetMarkerTGraphErr( fractionOfWVtxOutside10cmData6080,  markerStyleCommmonSpectrum6080, markerSizeCommonSpectrum6080, colorComb6080, colorComb6080);
	
	
	DrawGammaSetMarkerTGraphErr( meanTrackMultTPCData0005,  markerStyleCommmonSpectrum0005, markerSizeCommonSpectrum0005, colorComb0005, colorComb0005);
	DrawGammaSetMarkerTGraphErr( meanTrackMultTPCData0510,  markerStyleCommmonSpectrum0510, markerSizeCommonSpectrum0510, colorComb0510, colorComb0510);
	DrawGammaSetMarkerTGraphErr( meanTrackMultTPCData1020,  markerStyleCommmonSpectrum1020, markerSizeCommonSpectrum1020, colorComb1020, colorComb1020);
	DrawGammaSetMarkerTGraphErr( meanTrackMultTPCData2040,  markerStyleCommmonSpectrum2040, markerSizeCommonSpectrum2040, colorComb2040, colorComb2040);
	DrawGammaSetMarkerTGraphErr( meanTrackMultTPCData4060,  markerStyleCommmonSpectrum4060, markerSizeCommonSpectrum4060, colorComb4060, colorComb4060);
	DrawGammaSetMarkerTGraphErr( meanTrackMultTPCData6080,  markerStyleCommmonSpectrum6080, markerSizeCommonSpectrum6080, colorComb6080, colorComb6080);
	
	DrawGammaSetMarkerTGraphErr( meanTrackMultV0Data0005,  markerStyleCommmonSpectrum0005, markerSizeCommonSpectrum0005, colorComb0005, colorComb0005);
	DrawGammaSetMarkerTGraphErr( meanTrackMultV0Data0510,  markerStyleCommmonSpectrum0510, markerSizeCommonSpectrum0510, colorComb0510, colorComb0510);
	DrawGammaSetMarkerTGraphErr( meanTrackMultV0Data1020,  markerStyleCommmonSpectrum1020, markerSizeCommonSpectrum1020, colorComb1020, colorComb1020);
	DrawGammaSetMarkerTGraphErr( meanTrackMultV0Data2040,  markerStyleCommmonSpectrum2040, markerSizeCommonSpectrum2040, colorComb2040, colorComb2040);
	DrawGammaSetMarkerTGraphErr( meanTrackMultV0Data4060,  markerStyleCommmonSpectrum4060, markerSizeCommonSpectrum4060, colorComb4060, colorComb4060);
	DrawGammaSetMarkerTGraphErr( meanTrackMultV0Data6080,  markerStyleCommmonSpectrum6080, markerSizeCommonSpectrum6080, colorComb6080, colorComb6080);
	
	DrawGammaSetMarkerTGraphErr( fractionOfGammasLHC11a10a0005,  markerStyleCommmonSpectrumMC0005, markerSizeCommonSpectrum0005, colorCombMC0005, colorCombMC0005);
	DrawGammaSetMarkerTGraphErr( fractionOfGammasLHC11a10a0510,  markerStyleCommmonSpectrumMC0510, markerSizeCommonSpectrum0510, colorCombMC0510, colorCombMC0510);
	DrawGammaSetMarkerTGraphErr( fractionOfGammasLHC11a10a1020,  markerStyleCommmonSpectrumMC1020, markerSizeCommonSpectrum1020, colorCombMC1020, colorCombMC1020);
	DrawGammaSetMarkerTGraphErr( fractionOfGammasLHC11a10a2040,  markerStyleCommmonSpectrumMC2040, markerSizeCommonSpectrum2040, colorCombMC2040, colorCombMC2040);
	DrawGammaSetMarkerTGraphErr( fractionOfGammasLHC11a10a4060,  markerStyleCommmonSpectrumMC4060, markerSizeCommonSpectrum4060, colorCombMC4060, colorCombMC4060);
	DrawGammaSetMarkerTGraphErr( fractionOfGammasLHC11a10a6080,  markerStyleCommmonSpectrumMC6080, markerSizeCommonSpectrum6080, colorCombMC6080, colorCombMC6080);

	DrawGammaSetMarkerTGraphErr( fractionOfGoodEventsLHC11a10a0005,  markerStyleCommmonSpectrumMC0005, markerSizeCommonSpectrum0005, colorCombMC0005, colorCombMC0005);
	DrawGammaSetMarkerTGraphErr( fractionOfGoodEventsLHC11a10a0510,  markerStyleCommmonSpectrumMC0510, markerSizeCommonSpectrum0510, colorCombMC0510, colorCombMC0510);
	DrawGammaSetMarkerTGraphErr( fractionOfGoodEventsLHC11a10a1020,  markerStyleCommmonSpectrumMC1020, markerSizeCommonSpectrum1020, colorCombMC1020, colorCombMC1020);
	DrawGammaSetMarkerTGraphErr( fractionOfGoodEventsLHC11a10a2040,  markerStyleCommmonSpectrumMC2040, markerSizeCommonSpectrum2040, colorCombMC2040, colorCombMC2040);
	DrawGammaSetMarkerTGraphErr( fractionOfGoodEventsLHC11a10a4060,  markerStyleCommmonSpectrumMC4060, markerSizeCommonSpectrum4060, colorCombMC4060, colorCombMC4060);
	DrawGammaSetMarkerTGraphErr( fractionOfGoodEventsLHC11a10a6080,  markerStyleCommmonSpectrumMC6080, markerSizeCommonSpectrum6080, colorCombMC6080, colorCombMC6080);

	DrawGammaSetMarkerTGraphErr( fractionOfNormAllLHC11a10a0005,  markerStyleCommmonSpectrumMC0005, markerSizeCommonSpectrum0005, colorCombMC0005, colorCombMC0005);
	DrawGammaSetMarkerTGraphErr( fractionOfNormAllLHC11a10a0510,  markerStyleCommmonSpectrumMC0510, markerSizeCommonSpectrum0510, colorCombMC0510, colorCombMC0510);
	DrawGammaSetMarkerTGraphErr( fractionOfNormAllLHC11a10a1020,  markerStyleCommmonSpectrumMC1020, markerSizeCommonSpectrum1020, colorCombMC1020, colorCombMC1020);
	DrawGammaSetMarkerTGraphErr( fractionOfNormAllLHC11a10a2040,  markerStyleCommmonSpectrumMC2040, markerSizeCommonSpectrum2040, colorCombMC2040, colorCombMC2040);
	DrawGammaSetMarkerTGraphErr( fractionOfNormAllLHC11a10a4060,  markerStyleCommmonSpectrumMC4060, markerSizeCommonSpectrum4060, colorCombMC4060, colorCombMC4060);
	DrawGammaSetMarkerTGraphErr( fractionOfNormAllLHC11a10a6080,  markerStyleCommmonSpectrumMC6080, markerSizeCommonSpectrum6080, colorCombMC6080, colorCombMC6080);

	DrawGammaSetMarkerTGraphErr( fractionOfNormMinBiasLHC11a10a0005,  markerStyleCommmonSpectrumMC0005, markerSizeCommonSpectrum0005, colorCombMC0005, colorCombMC0005);
	DrawGammaSetMarkerTGraphErr( fractionOfNormMinBiasLHC11a10a0510,  markerStyleCommmonSpectrumMC0510, markerSizeCommonSpectrum0510, colorCombMC0510, colorCombMC0510);
	DrawGammaSetMarkerTGraphErr( fractionOfNormMinBiasLHC11a10a1020,  markerStyleCommmonSpectrumMC1020, markerSizeCommonSpectrum1020, colorCombMC1020, colorCombMC1020);
	DrawGammaSetMarkerTGraphErr( fractionOfNormMinBiasLHC11a10a2040,  markerStyleCommmonSpectrumMC2040, markerSizeCommonSpectrum2040, colorCombMC2040, colorCombMC2040);
	DrawGammaSetMarkerTGraphErr( fractionOfNormMinBiasLHC11a10a4060,  markerStyleCommmonSpectrumMC4060, markerSizeCommonSpectrum4060, colorCombMC4060, colorCombMC4060);
	DrawGammaSetMarkerTGraphErr( fractionOfNormMinBiasLHC11a10a6080,  markerStyleCommmonSpectrumMC6080, markerSizeCommonSpectrum6080, colorCombMC6080, colorCombMC6080);

	DrawGammaSetMarkerTGraphErr( fractionOfPileUpLHC11a10a0005,  markerStyleCommmonSpectrumMC0005, markerSizeCommonSpectrum0005, colorCombMC0005, colorCombMC0005);
	DrawGammaSetMarkerTGraphErr( fractionOfPileUpLHC11a10a0510,  markerStyleCommmonSpectrumMC0510, markerSizeCommonSpectrum0510, colorCombMC0510, colorCombMC0510);
	DrawGammaSetMarkerTGraphErr( fractionOfPileUpLHC11a10a1020,  markerStyleCommmonSpectrumMC1020, markerSizeCommonSpectrum1020, colorCombMC1020, colorCombMC1020);
	DrawGammaSetMarkerTGraphErr( fractionOfPileUpLHC11a10a2040,  markerStyleCommmonSpectrumMC2040, markerSizeCommonSpectrum2040, colorCombMC2040, colorCombMC2040);
	DrawGammaSetMarkerTGraphErr( fractionOfPileUpLHC11a10a4060,  markerStyleCommmonSpectrumMC4060, markerSizeCommonSpectrum4060, colorCombMC4060, colorCombMC4060);
	DrawGammaSetMarkerTGraphErr( fractionOfPileUpLHC11a10a6080,  markerStyleCommmonSpectrumMC6080, markerSizeCommonSpectrum6080, colorCombMC6080, colorCombMC6080);

	DrawGammaSetMarkerTGraphErr( fractionOfWOVtxLHC11a10a0005,  markerStyleCommmonSpectrumMC0005, markerSizeCommonSpectrum0005, colorCombMC0005, colorCombMC0005);
	DrawGammaSetMarkerTGraphErr( fractionOfWOVtxLHC11a10a0510,  markerStyleCommmonSpectrumMC0510, markerSizeCommonSpectrum0510, colorCombMC0510, colorCombMC0510);
	DrawGammaSetMarkerTGraphErr( fractionOfWOVtxLHC11a10a1020,  markerStyleCommmonSpectrumMC1020, markerSizeCommonSpectrum1020, colorCombMC1020, colorCombMC1020);
	DrawGammaSetMarkerTGraphErr( fractionOfWOVtxLHC11a10a2040,  markerStyleCommmonSpectrumMC2040, markerSizeCommonSpectrum2040, colorCombMC2040, colorCombMC2040);
	DrawGammaSetMarkerTGraphErr( fractionOfWOVtxLHC11a10a4060,  markerStyleCommmonSpectrumMC4060, markerSizeCommonSpectrum4060, colorCombMC4060, colorCombMC4060);
	DrawGammaSetMarkerTGraphErr( fractionOfWOVtxLHC11a10a6080,  markerStyleCommmonSpectrumMC6080, markerSizeCommonSpectrum6080, colorCombMC6080, colorCombMC6080);

	DrawGammaSetMarkerTGraphErr( fractionOfWVtxOutside10cmLHC11a10a0005,  markerStyleCommmonSpectrumMC0005, markerSizeCommonSpectrum0005, colorCombMC0005, colorCombMC0005);
	DrawGammaSetMarkerTGraphErr( fractionOfWVtxOutside10cmLHC11a10a0510,  markerStyleCommmonSpectrumMC0510, markerSizeCommonSpectrum0510, colorCombMC0510, colorCombMC0510);
	DrawGammaSetMarkerTGraphErr( fractionOfWVtxOutside10cmLHC11a10a1020,  markerStyleCommmonSpectrumMC1020, markerSizeCommonSpectrum1020, colorCombMC1020, colorCombMC1020);
	DrawGammaSetMarkerTGraphErr( fractionOfWVtxOutside10cmLHC11a10a2040,  markerStyleCommmonSpectrumMC2040, markerSizeCommonSpectrum2040, colorCombMC2040, colorCombMC2040);
	DrawGammaSetMarkerTGraphErr( fractionOfWVtxOutside10cmLHC11a10a4060,  markerStyleCommmonSpectrumMC4060, markerSizeCommonSpectrum4060, colorCombMC4060, colorCombMC4060);
	DrawGammaSetMarkerTGraphErr( fractionOfWVtxOutside10cmLHC11a10a6080,  markerStyleCommmonSpectrumMC6080, markerSizeCommonSpectrum6080, colorCombMC6080, colorCombMC6080);

	
	DrawGammaSetMarkerTGraphErr( fractionOfGammasLHC11a10a_bis0005,  markerStyleCommmonSpectrumMC0005, markerSizeCommonSpectrum0005, colorCombMC0005, colorCombMC0005);
	DrawGammaSetMarkerTGraphErr( fractionOfGammasLHC11a10a_bis0510,  markerStyleCommmonSpectrumMC0510, markerSizeCommonSpectrum0510, colorCombMC0510, colorCombMC0510);
	DrawGammaSetMarkerTGraphErr( fractionOfGammasLHC11a10a_bis1020,  markerStyleCommmonSpectrumMC1020, markerSizeCommonSpectrum1020, colorCombMC1020, colorCombMC1020);
	DrawGammaSetMarkerTGraphErr( fractionOfGammasLHC11a10a_bis2040,  markerStyleCommmonSpectrumMC2040, markerSizeCommonSpectrum2040, colorCombMC2040, colorCombMC2040);
	DrawGammaSetMarkerTGraphErr( fractionOfGammasLHC11a10a_bis4060,  markerStyleCommmonSpectrumMC4060, markerSizeCommonSpectrum4060, colorCombMC4060, colorCombMC4060);
	DrawGammaSetMarkerTGraphErr( fractionOfGammasLHC11a10a_bis6080,  markerStyleCommmonSpectrumMC6080, markerSizeCommonSpectrum6080, colorCombMC6080, colorCombMC6080);

	DrawGammaSetMarkerTGraphErr( fractionOfGoodEventsLHC11a10a_bis0005,  markerStyleCommmonSpectrumMC0005, markerSizeCommonSpectrum0005, colorCombMC0005, colorCombMC0005);
	DrawGammaSetMarkerTGraphErr( fractionOfGoodEventsLHC11a10a_bis0510,  markerStyleCommmonSpectrumMC0510, markerSizeCommonSpectrum0510, colorCombMC0510, colorCombMC0510);
	DrawGammaSetMarkerTGraphErr( fractionOfGoodEventsLHC11a10a_bis1020,  markerStyleCommmonSpectrumMC1020, markerSizeCommonSpectrum1020, colorCombMC1020, colorCombMC1020);
	DrawGammaSetMarkerTGraphErr( fractionOfGoodEventsLHC11a10a_bis2040,  markerStyleCommmonSpectrumMC2040, markerSizeCommonSpectrum2040, colorCombMC2040, colorCombMC2040);
	DrawGammaSetMarkerTGraphErr( fractionOfGoodEventsLHC11a10a_bis4060,  markerStyleCommmonSpectrumMC4060, markerSizeCommonSpectrum4060, colorCombMC4060, colorCombMC4060);
	DrawGammaSetMarkerTGraphErr( fractionOfGoodEventsLHC11a10a_bis6080,  markerStyleCommmonSpectrumMC6080, markerSizeCommonSpectrum6080, colorCombMC6080, colorCombMC6080);

	DrawGammaSetMarkerTGraphErr( fractionOfNormAllLHC11a10a_bis0005,  markerStyleCommmonSpectrumMC0005, markerSizeCommonSpectrum0005, colorCombMC0005, colorCombMC0005);
	DrawGammaSetMarkerTGraphErr( fractionOfNormAllLHC11a10a_bis0510,  markerStyleCommmonSpectrumMC0510, markerSizeCommonSpectrum0510, colorCombMC0510, colorCombMC0510);
	DrawGammaSetMarkerTGraphErr( fractionOfNormAllLHC11a10a_bis1020,  markerStyleCommmonSpectrumMC1020, markerSizeCommonSpectrum1020, colorCombMC1020, colorCombMC1020);
	DrawGammaSetMarkerTGraphErr( fractionOfNormAllLHC11a10a_bis2040,  markerStyleCommmonSpectrumMC2040, markerSizeCommonSpectrum2040, colorCombMC2040, colorCombMC2040);
	DrawGammaSetMarkerTGraphErr( fractionOfNormAllLHC11a10a_bis4060,  markerStyleCommmonSpectrumMC4060, markerSizeCommonSpectrum4060, colorCombMC4060, colorCombMC4060);
	DrawGammaSetMarkerTGraphErr( fractionOfNormAllLHC11a10a_bis6080,  markerStyleCommmonSpectrumMC6080, markerSizeCommonSpectrum6080, colorCombMC6080, colorCombMC6080);

	DrawGammaSetMarkerTGraphErr( fractionOfNormMinBiasLHC11a10a_bis0005,  markerStyleCommmonSpectrumMC0005, markerSizeCommonSpectrum0005, colorCombMC0005, colorCombMC0005);
	DrawGammaSetMarkerTGraphErr( fractionOfNormMinBiasLHC11a10a_bis0510,  markerStyleCommmonSpectrumMC0510, markerSizeCommonSpectrum0510, colorCombMC0510, colorCombMC0510);
	DrawGammaSetMarkerTGraphErr( fractionOfNormMinBiasLHC11a10a_bis1020,  markerStyleCommmonSpectrumMC1020, markerSizeCommonSpectrum1020, colorCombMC1020, colorCombMC1020);
	DrawGammaSetMarkerTGraphErr( fractionOfNormMinBiasLHC11a10a_bis2040,  markerStyleCommmonSpectrumMC2040, markerSizeCommonSpectrum2040, colorCombMC2040, colorCombMC2040);
	DrawGammaSetMarkerTGraphErr( fractionOfNormMinBiasLHC11a10a_bis4060,  markerStyleCommmonSpectrumMC4060, markerSizeCommonSpectrum4060, colorCombMC4060, colorCombMC4060);
	DrawGammaSetMarkerTGraphErr( fractionOfNormMinBiasLHC11a10a_bis6080,  markerStyleCommmonSpectrumMC6080, markerSizeCommonSpectrum6080, colorCombMC6080, colorCombMC6080);

	DrawGammaSetMarkerTGraphErr( fractionOfPileUpLHC11a10a_bis0005,  markerStyleCommmonSpectrumMC0005, markerSizeCommonSpectrum0005, colorCombMC0005, colorCombMC0005);
	DrawGammaSetMarkerTGraphErr( fractionOfPileUpLHC11a10a_bis0510,  markerStyleCommmonSpectrumMC0510, markerSizeCommonSpectrum0510, colorCombMC0510, colorCombMC0510);
	DrawGammaSetMarkerTGraphErr( fractionOfPileUpLHC11a10a_bis1020,  markerStyleCommmonSpectrumMC1020, markerSizeCommonSpectrum1020, colorCombMC1020, colorCombMC1020);
	DrawGammaSetMarkerTGraphErr( fractionOfPileUpLHC11a10a_bis2040,  markerStyleCommmonSpectrumMC2040, markerSizeCommonSpectrum2040, colorCombMC2040, colorCombMC2040);
	DrawGammaSetMarkerTGraphErr( fractionOfPileUpLHC11a10a_bis4060,  markerStyleCommmonSpectrumMC4060, markerSizeCommonSpectrum4060, colorCombMC4060, colorCombMC4060);
	DrawGammaSetMarkerTGraphErr( fractionOfPileUpLHC11a10a_bis6080,  markerStyleCommmonSpectrumMC6080, markerSizeCommonSpectrum6080, colorCombMC6080, colorCombMC6080);

	DrawGammaSetMarkerTGraphErr( fractionOfWOVtxLHC11a10a_bis0005,  markerStyleCommmonSpectrumMC0005, markerSizeCommonSpectrum0005, colorCombMC0005, colorCombMC0005);
	DrawGammaSetMarkerTGraphErr( fractionOfWOVtxLHC11a10a_bis0510,  markerStyleCommmonSpectrumMC0510, markerSizeCommonSpectrum0510, colorCombMC0510, colorCombMC0510);
	DrawGammaSetMarkerTGraphErr( fractionOfWOVtxLHC11a10a_bis1020,  markerStyleCommmonSpectrumMC1020, markerSizeCommonSpectrum1020, colorCombMC1020, colorCombMC1020);
	DrawGammaSetMarkerTGraphErr( fractionOfWOVtxLHC11a10a_bis2040,  markerStyleCommmonSpectrumMC2040, markerSizeCommonSpectrum2040, colorCombMC2040, colorCombMC2040);
	DrawGammaSetMarkerTGraphErr( fractionOfWOVtxLHC11a10a_bis4060,  markerStyleCommmonSpectrumMC4060, markerSizeCommonSpectrum4060, colorCombMC4060, colorCombMC4060);
	DrawGammaSetMarkerTGraphErr( fractionOfWOVtxLHC11a10a_bis6080,  markerStyleCommmonSpectrumMC6080, markerSizeCommonSpectrum6080, colorCombMC6080, colorCombMC6080);

	DrawGammaSetMarkerTGraphErr( fractionOfWVtxOutside10cmLHC11a10a_bis0005,  markerStyleCommmonSpectrumMC0005, markerSizeCommonSpectrum0005, colorCombMC0005, colorCombMC0005);
	DrawGammaSetMarkerTGraphErr( fractionOfWVtxOutside10cmLHC11a10a_bis0510,  markerStyleCommmonSpectrumMC0510, markerSizeCommonSpectrum0510, colorCombMC0510, colorCombMC0510);
	DrawGammaSetMarkerTGraphErr( fractionOfWVtxOutside10cmLHC11a10a_bis1020,  markerStyleCommmonSpectrumMC1020, markerSizeCommonSpectrum1020, colorCombMC1020, colorCombMC1020);
	DrawGammaSetMarkerTGraphErr( fractionOfWVtxOutside10cmLHC11a10a_bis2040,  markerStyleCommmonSpectrumMC2040, markerSizeCommonSpectrum2040, colorCombMC2040, colorCombMC2040);
	DrawGammaSetMarkerTGraphErr( fractionOfWVtxOutside10cmLHC11a10a_bis4060,  markerStyleCommmonSpectrumMC4060, markerSizeCommonSpectrum4060, colorCombMC4060, colorCombMC4060);
	DrawGammaSetMarkerTGraphErr( fractionOfWVtxOutside10cmLHC11a10a_bis6080,  markerStyleCommmonSpectrumMC6080, markerSizeCommonSpectrum6080, colorCombMC6080, colorCombMC6080);


	DrawGammaSetMarkerTGraphErr( meanTrackMultTPCLHC11a10a_bis0005,  markerStyleCommmonSpectrumMC0005, markerSizeCommonSpectrum0005, colorCombMC0005, colorCombMC0005);
	DrawGammaSetMarkerTGraphErr( meanTrackMultTPCLHC11a10a_bis0510,  markerStyleCommmonSpectrumMC0510, markerSizeCommonSpectrum0510, colorCombMC0510, colorCombMC0510);
	DrawGammaSetMarkerTGraphErr( meanTrackMultTPCLHC11a10a_bis1020,  markerStyleCommmonSpectrumMC1020, markerSizeCommonSpectrum1020, colorCombMC1020, colorCombMC1020);
	DrawGammaSetMarkerTGraphErr( meanTrackMultTPCLHC11a10a_bis2040,  markerStyleCommmonSpectrumMC2040, markerSizeCommonSpectrum2040, colorCombMC2040, colorCombMC2040);
	DrawGammaSetMarkerTGraphErr( meanTrackMultTPCLHC11a10a_bis4060,  markerStyleCommmonSpectrumMC4060, markerSizeCommonSpectrum4060, colorCombMC4060, colorCombMC4060);
	DrawGammaSetMarkerTGraphErr( meanTrackMultTPCLHC11a10a_bis6080,  markerStyleCommmonSpectrumMC6080, markerSizeCommonSpectrum6080, colorCombMC6080, colorCombMC6080);

	DrawGammaSetMarkerTGraphErr( meanTrackMultV0LHC11a10a_bis0005,  markerStyleCommmonSpectrumMC0005, markerSizeCommonSpectrum0005, colorCombMC0005, colorCombMC0005);
	DrawGammaSetMarkerTGraphErr( meanTrackMultV0LHC11a10a_bis0510,  markerStyleCommmonSpectrumMC0510, markerSizeCommonSpectrum0510, colorCombMC0510, colorCombMC0510);
	DrawGammaSetMarkerTGraphErr( meanTrackMultV0LHC11a10a_bis1020,  markerStyleCommmonSpectrumMC1020, markerSizeCommonSpectrum1020, colorCombMC1020, colorCombMC1020);
	DrawGammaSetMarkerTGraphErr( meanTrackMultV0LHC11a10a_bis2040,  markerStyleCommmonSpectrumMC2040, markerSizeCommonSpectrum2040, colorCombMC2040, colorCombMC2040);
	DrawGammaSetMarkerTGraphErr( meanTrackMultV0LHC11a10a_bis4060,  markerStyleCommmonSpectrumMC4060, markerSizeCommonSpectrum4060, colorCombMC4060, colorCombMC4060);
	DrawGammaSetMarkerTGraphErr( meanTrackMultV0LHC11a10a_bis6080,  markerStyleCommmonSpectrumMC6080, markerSizeCommonSpectrum6080, colorCombMC6080, colorCombMC6080);

	
	DrawGammaSetMarkerTGraphErr( fractionOfGammasLHC11a10b_bis0005,  markerStyleCommmonSpectrumMC0005, markerSizeCommonSpectrum0005, colorCombMC0005, colorCombMC0005);
	DrawGammaSetMarkerTGraphErr( fractionOfGammasLHC11a10b_bis0510,  markerStyleCommmonSpectrumMC0510, markerSizeCommonSpectrum0510, colorCombMC0510, colorCombMC0510);
	DrawGammaSetMarkerTGraphErr( fractionOfGammasLHC11a10b_bis1020,  markerStyleCommmonSpectrumMC1020, markerSizeCommonSpectrum1020, colorCombMC1020, colorCombMC1020);
	DrawGammaSetMarkerTGraphErr( fractionOfGammasLHC11a10b_bis2040,  markerStyleCommmonSpectrumMC2040, markerSizeCommonSpectrum2040, colorCombMC2040, colorCombMC2040);
	DrawGammaSetMarkerTGraphErr( fractionOfGammasLHC11a10b_bis4060,  markerStyleCommmonSpectrumMC4060, markerSizeCommonSpectrum4060, colorCombMC4060, colorCombMC4060);
	DrawGammaSetMarkerTGraphErr( fractionOfGammasLHC11a10b_bis6080,  markerStyleCommmonSpectrumMC6080, markerSizeCommonSpectrum6080, colorCombMC6080, colorCombMC6080);

	DrawGammaSetMarkerTGraphErr( fractionOfGoodEventsLHC11a10b_bis0005,  markerStyleCommmonSpectrumMC0005, markerSizeCommonSpectrum0005, colorCombMC0005, colorCombMC0005);
	DrawGammaSetMarkerTGraphErr( fractionOfGoodEventsLHC11a10b_bis0510,  markerStyleCommmonSpectrumMC0510, markerSizeCommonSpectrum0510, colorCombMC0510, colorCombMC0510);
	DrawGammaSetMarkerTGraphErr( fractionOfGoodEventsLHC11a10b_bis1020,  markerStyleCommmonSpectrumMC1020, markerSizeCommonSpectrum1020, colorCombMC1020, colorCombMC1020);
	DrawGammaSetMarkerTGraphErr( fractionOfGoodEventsLHC11a10b_bis2040,  markerStyleCommmonSpectrumMC2040, markerSizeCommonSpectrum2040, colorCombMC2040, colorCombMC2040);
	DrawGammaSetMarkerTGraphErr( fractionOfGoodEventsLHC11a10b_bis4060,  markerStyleCommmonSpectrumMC4060, markerSizeCommonSpectrum4060, colorCombMC4060, colorCombMC4060);
	DrawGammaSetMarkerTGraphErr( fractionOfGoodEventsLHC11a10b_bis6080,  markerStyleCommmonSpectrumMC6080, markerSizeCommonSpectrum6080, colorCombMC6080, colorCombMC6080);

	DrawGammaSetMarkerTGraphErr( fractionOfNormAllLHC11a10b_bis0005,  markerStyleCommmonSpectrumMC0005, markerSizeCommonSpectrum0005, colorCombMC0005, colorCombMC0005);
	DrawGammaSetMarkerTGraphErr( fractionOfNormAllLHC11a10b_bis0510,  markerStyleCommmonSpectrumMC0510, markerSizeCommonSpectrum0510, colorCombMC0510, colorCombMC0510);
	DrawGammaSetMarkerTGraphErr( fractionOfNormAllLHC11a10b_bis1020,  markerStyleCommmonSpectrumMC1020, markerSizeCommonSpectrum1020, colorCombMC1020, colorCombMC1020);
	DrawGammaSetMarkerTGraphErr( fractionOfNormAllLHC11a10b_bis2040,  markerStyleCommmonSpectrumMC2040, markerSizeCommonSpectrum2040, colorCombMC2040, colorCombMC2040);
	DrawGammaSetMarkerTGraphErr( fractionOfNormAllLHC11a10b_bis4060,  markerStyleCommmonSpectrumMC4060, markerSizeCommonSpectrum4060, colorCombMC4060, colorCombMC4060);
	DrawGammaSetMarkerTGraphErr( fractionOfNormAllLHC11a10b_bis6080,  markerStyleCommmonSpectrumMC6080, markerSizeCommonSpectrum6080, colorCombMC6080, colorCombMC6080);

	DrawGammaSetMarkerTGraphErr( fractionOfNormMinBiasLHC11a10b_bis0005,  markerStyleCommmonSpectrumMC0005, markerSizeCommonSpectrum0005, colorCombMC0005, colorCombMC0005);
	DrawGammaSetMarkerTGraphErr( fractionOfNormMinBiasLHC11a10b_bis0510,  markerStyleCommmonSpectrumMC0510, markerSizeCommonSpectrum0510, colorCombMC0510, colorCombMC0510);
	DrawGammaSetMarkerTGraphErr( fractionOfNormMinBiasLHC11a10b_bis1020,  markerStyleCommmonSpectrumMC1020, markerSizeCommonSpectrum1020, colorCombMC1020, colorCombMC1020);
	DrawGammaSetMarkerTGraphErr( fractionOfNormMinBiasLHC11a10b_bis2040,  markerStyleCommmonSpectrumMC2040, markerSizeCommonSpectrum2040, colorCombMC2040, colorCombMC2040);
	DrawGammaSetMarkerTGraphErr( fractionOfNormMinBiasLHC11a10b_bis4060,  markerStyleCommmonSpectrumMC4060, markerSizeCommonSpectrum4060, colorCombMC4060, colorCombMC4060);
	DrawGammaSetMarkerTGraphErr( fractionOfNormMinBiasLHC11a10b_bis6080,  markerStyleCommmonSpectrumMC6080, markerSizeCommonSpectrum6080, colorCombMC6080, colorCombMC6080);

	DrawGammaSetMarkerTGraphErr( fractionOfPileUpLHC11a10b_bis0005,  markerStyleCommmonSpectrumMC0005, markerSizeCommonSpectrum0005, colorCombMC0005, colorCombMC0005);
	DrawGammaSetMarkerTGraphErr( fractionOfPileUpLHC11a10b_bis0510,  markerStyleCommmonSpectrumMC0510, markerSizeCommonSpectrum0510, colorCombMC0510, colorCombMC0510);
	DrawGammaSetMarkerTGraphErr( fractionOfPileUpLHC11a10b_bis1020,  markerStyleCommmonSpectrumMC1020, markerSizeCommonSpectrum1020, colorCombMC1020, colorCombMC1020);
	DrawGammaSetMarkerTGraphErr( fractionOfPileUpLHC11a10b_bis2040,  markerStyleCommmonSpectrumMC2040, markerSizeCommonSpectrum2040, colorCombMC2040, colorCombMC2040);
	DrawGammaSetMarkerTGraphErr( fractionOfPileUpLHC11a10b_bis4060,  markerStyleCommmonSpectrumMC4060, markerSizeCommonSpectrum4060, colorCombMC4060, colorCombMC4060);
	DrawGammaSetMarkerTGraphErr( fractionOfPileUpLHC11a10b_bis6080,  markerStyleCommmonSpectrumMC6080, markerSizeCommonSpectrum6080, colorCombMC6080, colorCombMC6080);

	DrawGammaSetMarkerTGraphErr( fractionOfWOVtxLHC11a10b_bis0005,  markerStyleCommmonSpectrumMC0005, markerSizeCommonSpectrum0005, colorCombMC0005, colorCombMC0005);
	DrawGammaSetMarkerTGraphErr( fractionOfWOVtxLHC11a10b_bis0510,  markerStyleCommmonSpectrumMC0510, markerSizeCommonSpectrum0510, colorCombMC0510, colorCombMC0510);
	DrawGammaSetMarkerTGraphErr( fractionOfWOVtxLHC11a10b_bis1020,  markerStyleCommmonSpectrumMC1020, markerSizeCommonSpectrum1020, colorCombMC1020, colorCombMC1020);
	DrawGammaSetMarkerTGraphErr( fractionOfWOVtxLHC11a10b_bis2040,  markerStyleCommmonSpectrumMC2040, markerSizeCommonSpectrum2040, colorCombMC2040, colorCombMC2040);
	DrawGammaSetMarkerTGraphErr( fractionOfWOVtxLHC11a10b_bis4060,  markerStyleCommmonSpectrumMC4060, markerSizeCommonSpectrum4060, colorCombMC4060, colorCombMC4060);
	DrawGammaSetMarkerTGraphErr( fractionOfWOVtxLHC11a10b_bis6080,  markerStyleCommmonSpectrumMC6080, markerSizeCommonSpectrum6080, colorCombMC6080, colorCombMC6080);

	DrawGammaSetMarkerTGraphErr( fractionOfWVtxOutside10cmLHC11a10b_bis0005,  markerStyleCommmonSpectrumMC0005, markerSizeCommonSpectrum0005, colorCombMC0005, colorCombMC0005);
	DrawGammaSetMarkerTGraphErr( fractionOfWVtxOutside10cmLHC11a10b_bis0510,  markerStyleCommmonSpectrumMC0510, markerSizeCommonSpectrum0510, colorCombMC0510, colorCombMC0510);
	DrawGammaSetMarkerTGraphErr( fractionOfWVtxOutside10cmLHC11a10b_bis1020,  markerStyleCommmonSpectrumMC1020, markerSizeCommonSpectrum1020, colorCombMC1020, colorCombMC1020);
	DrawGammaSetMarkerTGraphErr( fractionOfWVtxOutside10cmLHC11a10b_bis2040,  markerStyleCommmonSpectrumMC2040, markerSizeCommonSpectrum2040, colorCombMC2040, colorCombMC2040);
	DrawGammaSetMarkerTGraphErr( fractionOfWVtxOutside10cmLHC11a10b_bis4060,  markerStyleCommmonSpectrumMC4060, markerSizeCommonSpectrum4060, colorCombMC4060, colorCombMC4060);
	DrawGammaSetMarkerTGraphErr( fractionOfWVtxOutside10cmLHC11a10b_bis6080,  markerStyleCommmonSpectrumMC6080, markerSizeCommonSpectrum6080, colorCombMC6080, colorCombMC6080);
	
   
	DrawGammaSetMarkerTGraphErr( fractionOfGammasLHC13d20005,  markerStyleCommmonSpectrumMC0005, markerSizeCommonSpectrum0005, colorCombMC0005, colorCombMC0005);
	DrawGammaSetMarkerTGraphErr( fractionOfGammasLHC13d20510,  markerStyleCommmonSpectrumMC0510, markerSizeCommonSpectrum0510, colorCombMC0510, colorCombMC0510);
	DrawGammaSetMarkerTGraphErr( fractionOfGammasLHC13d21020,  markerStyleCommmonSpectrumMC1020, markerSizeCommonSpectrum1020, colorCombMC1020, colorCombMC1020);
	DrawGammaSetMarkerTGraphErr( fractionOfGammasLHC13d22040,  markerStyleCommmonSpectrumMC2040, markerSizeCommonSpectrum2040, colorCombMC2040, colorCombMC2040);
	DrawGammaSetMarkerTGraphErr( fractionOfGammasLHC13d24060,  markerStyleCommmonSpectrumMC4060, markerSizeCommonSpectrum4060, colorCombMC4060, colorCombMC4060);
	DrawGammaSetMarkerTGraphErr( fractionOfGammasLHC13d26080,  markerStyleCommmonSpectrumMC6080, markerSizeCommonSpectrum6080, colorCombMC6080, colorCombMC6080);
	
	DrawGammaSetMarkerTGraphErr( fractionOfGoodEventsLHC13d20005,  markerStyleCommmonSpectrumMC0005, markerSizeCommonSpectrum0005, colorCombMC0005, colorCombMC0005);
	DrawGammaSetMarkerTGraphErr( fractionOfGoodEventsLHC13d20510,  markerStyleCommmonSpectrumMC0510, markerSizeCommonSpectrum0510, colorCombMC0510, colorCombMC0510);
	DrawGammaSetMarkerTGraphErr( fractionOfGoodEventsLHC13d21020,  markerStyleCommmonSpectrumMC1020, markerSizeCommonSpectrum1020, colorCombMC1020, colorCombMC1020);
	DrawGammaSetMarkerTGraphErr( fractionOfGoodEventsLHC13d22040,  markerStyleCommmonSpectrumMC2040, markerSizeCommonSpectrum2040, colorCombMC2040, colorCombMC2040);
	DrawGammaSetMarkerTGraphErr( fractionOfGoodEventsLHC13d24060,  markerStyleCommmonSpectrumMC4060, markerSizeCommonSpectrum4060, colorCombMC4060, colorCombMC4060);
	DrawGammaSetMarkerTGraphErr( fractionOfGoodEventsLHC13d26080,  markerStyleCommmonSpectrumMC6080, markerSizeCommonSpectrum6080, colorCombMC6080, colorCombMC6080);
   
	DrawGammaSetMarkerTGraphErr( fractionOfNormAllLHC13d20005,  markerStyleCommmonSpectrumMC0005, markerSizeCommonSpectrum0005, colorCombMC0005, colorCombMC0005);
	DrawGammaSetMarkerTGraphErr( fractionOfNormAllLHC13d20510,  markerStyleCommmonSpectrumMC0510, markerSizeCommonSpectrum0510, colorCombMC0510, colorCombMC0510);
	DrawGammaSetMarkerTGraphErr( fractionOfNormAllLHC13d21020,  markerStyleCommmonSpectrumMC1020, markerSizeCommonSpectrum1020, colorCombMC1020, colorCombMC1020);
	DrawGammaSetMarkerTGraphErr( fractionOfNormAllLHC13d22040,  markerStyleCommmonSpectrumMC2040, markerSizeCommonSpectrum2040, colorCombMC2040, colorCombMC2040);
	DrawGammaSetMarkerTGraphErr( fractionOfNormAllLHC13d24060,  markerStyleCommmonSpectrumMC4060, markerSizeCommonSpectrum4060, colorCombMC4060, colorCombMC4060);
	DrawGammaSetMarkerTGraphErr( fractionOfNormAllLHC13d26080,  markerStyleCommmonSpectrumMC6080, markerSizeCommonSpectrum6080, colorCombMC6080, colorCombMC6080);
   
	DrawGammaSetMarkerTGraphErr( fractionOfNormMinBiasLHC13d20005,  markerStyleCommmonSpectrumMC0005, markerSizeCommonSpectrum0005, colorCombMC0005, colorCombMC0005);
	DrawGammaSetMarkerTGraphErr( fractionOfNormMinBiasLHC13d20510,  markerStyleCommmonSpectrumMC0510, markerSizeCommonSpectrum0510, colorCombMC0510, colorCombMC0510);
	DrawGammaSetMarkerTGraphErr( fractionOfNormMinBiasLHC13d21020,  markerStyleCommmonSpectrumMC1020, markerSizeCommonSpectrum1020, colorCombMC1020, colorCombMC1020);
	DrawGammaSetMarkerTGraphErr( fractionOfNormMinBiasLHC13d22040,  markerStyleCommmonSpectrumMC2040, markerSizeCommonSpectrum2040, colorCombMC2040, colorCombMC2040);
	DrawGammaSetMarkerTGraphErr( fractionOfNormMinBiasLHC13d24060,  markerStyleCommmonSpectrumMC4060, markerSizeCommonSpectrum4060, colorCombMC4060, colorCombMC4060);
	DrawGammaSetMarkerTGraphErr( fractionOfNormMinBiasLHC13d26080,  markerStyleCommmonSpectrumMC6080, markerSizeCommonSpectrum6080, colorCombMC6080, colorCombMC6080);
   
	DrawGammaSetMarkerTGraphErr( fractionOfPileUpLHC13d20005,  markerStyleCommmonSpectrumMC0005, markerSizeCommonSpectrum0005, colorCombMC0005, colorCombMC0005);
	DrawGammaSetMarkerTGraphErr( fractionOfPileUpLHC13d20510,  markerStyleCommmonSpectrumMC0510, markerSizeCommonSpectrum0510, colorCombMC0510, colorCombMC0510);
	DrawGammaSetMarkerTGraphErr( fractionOfPileUpLHC13d21020,  markerStyleCommmonSpectrumMC1020, markerSizeCommonSpectrum1020, colorCombMC1020, colorCombMC1020);
	DrawGammaSetMarkerTGraphErr( fractionOfPileUpLHC13d22040,  markerStyleCommmonSpectrumMC2040, markerSizeCommonSpectrum2040, colorCombMC2040, colorCombMC2040);
	DrawGammaSetMarkerTGraphErr( fractionOfPileUpLHC13d24060,  markerStyleCommmonSpectrumMC4060, markerSizeCommonSpectrum4060, colorCombMC4060, colorCombMC4060);
	DrawGammaSetMarkerTGraphErr( fractionOfPileUpLHC13d26080,  markerStyleCommmonSpectrumMC6080, markerSizeCommonSpectrum6080, colorCombMC6080, colorCombMC6080);
   
	DrawGammaSetMarkerTGraphErr( fractionOfWOVtxLHC13d20005,  markerStyleCommmonSpectrumMC0005, markerSizeCommonSpectrum0005, colorCombMC0005, colorCombMC0005);
	DrawGammaSetMarkerTGraphErr( fractionOfWOVtxLHC13d20510,  markerStyleCommmonSpectrumMC0510, markerSizeCommonSpectrum0510, colorCombMC0510, colorCombMC0510);
	DrawGammaSetMarkerTGraphErr( fractionOfWOVtxLHC13d21020,  markerStyleCommmonSpectrumMC1020, markerSizeCommonSpectrum1020, colorCombMC1020, colorCombMC1020);
	DrawGammaSetMarkerTGraphErr( fractionOfWOVtxLHC13d22040,  markerStyleCommmonSpectrumMC2040, markerSizeCommonSpectrum2040, colorCombMC2040, colorCombMC2040);
	DrawGammaSetMarkerTGraphErr( fractionOfWOVtxLHC13d24060,  markerStyleCommmonSpectrumMC4060, markerSizeCommonSpectrum4060, colorCombMC4060, colorCombMC4060);
	DrawGammaSetMarkerTGraphErr( fractionOfWOVtxLHC13d26080,  markerStyleCommmonSpectrumMC6080, markerSizeCommonSpectrum6080, colorCombMC6080, colorCombMC6080);
   
	DrawGammaSetMarkerTGraphErr( fractionOfWVtxOutside10cmLHC13d20005,  markerStyleCommmonSpectrumMC0005, markerSizeCommonSpectrum0005, colorCombMC0005, colorCombMC0005);
	DrawGammaSetMarkerTGraphErr( fractionOfWVtxOutside10cmLHC13d20510,  markerStyleCommmonSpectrumMC0510, markerSizeCommonSpectrum0510, colorCombMC0510, colorCombMC0510);
	DrawGammaSetMarkerTGraphErr( fractionOfWVtxOutside10cmLHC13d21020,  markerStyleCommmonSpectrumMC1020, markerSizeCommonSpectrum1020, colorCombMC1020, colorCombMC1020);
	DrawGammaSetMarkerTGraphErr( fractionOfWVtxOutside10cmLHC13d22040,  markerStyleCommmonSpectrumMC2040, markerSizeCommonSpectrum2040, colorCombMC2040, colorCombMC2040);
	DrawGammaSetMarkerTGraphErr( fractionOfWVtxOutside10cmLHC13d24060,  markerStyleCommmonSpectrumMC4060, markerSizeCommonSpectrum4060, colorCombMC4060, colorCombMC4060);
	DrawGammaSetMarkerTGraphErr( fractionOfWVtxOutside10cmLHC13d26080,  markerStyleCommmonSpectrumMC6080, markerSizeCommonSpectrum6080, colorCombMC6080, colorCombMC6080);
   
   DrawGammaSetMarkerTGraphErr( meanTrackMultTPCLHC13d20005,  markerStyleCommmonSpectrumMC0005, markerSizeCommonSpectrum0005, colorCombMC0005, colorCombMC0005);
   DrawGammaSetMarkerTGraphErr( meanTrackMultTPCLHC13d20510,  markerStyleCommmonSpectrumMC0510, markerSizeCommonSpectrum0510, colorCombMC0510, colorCombMC0510);
   DrawGammaSetMarkerTGraphErr( meanTrackMultTPCLHC13d21020,  markerStyleCommmonSpectrumMC1020, markerSizeCommonSpectrum1020, colorCombMC1020, colorCombMC1020);
   DrawGammaSetMarkerTGraphErr( meanTrackMultTPCLHC13d22040,  markerStyleCommmonSpectrumMC2040, markerSizeCommonSpectrum2040, colorCombMC2040, colorCombMC2040);
   DrawGammaSetMarkerTGraphErr( meanTrackMultTPCLHC13d24060,  markerStyleCommmonSpectrumMC4060, markerSizeCommonSpectrum4060, colorCombMC4060, colorCombMC4060);
   DrawGammaSetMarkerTGraphErr( meanTrackMultTPCLHC13d26080,  markerStyleCommmonSpectrumMC6080, markerSizeCommonSpectrum6080, colorCombMC6080, colorCombMC6080);
//    cout << "bla" << endl;
//    DrawGammaSetMarkerTGraphErr( meanTrackMultV0LHC13d20005,  markerStyleCommmonSpectrumMC0005, markerSizeCommonSpectrum0005, colorCombMC0005, colorCombMC0005);
//    cout << "bla" << endl;
//    DrawGammaSetMarkerTGraphErr( meanTrackMultV0LHC13d20510,  markerStyleCommmonSpectrumMC0510, markerSizeCommonSpectrum0510, colorCombMC0510, colorCombMC0510);
//    cout << "bla" << endl;
//    DrawGammaSetMarkerTGraphErr( meanTrackMultV0LHC13d21020,  markerStyleCommmonSpectrumMC1020, markerSizeCommonSpectrum1020, colorCombMC1020, colorCombMC1020);
//    cout << "bla" << endl;
//    DrawGammaSetMarkerTGraphErr( meanTrackMultV0LHC13d22040,  markerStyleCommmonSpectrumMC2040, markerSizeCommonSpectrum2040, colorCombMC2040, colorCombMC2040);
//    cout << "bla" << endl;
//    DrawGammaSetMarkerTGraphErr( meanTrackMultV0LHC13d24060,  markerStyleCommmonSpectrumMC4060, markerSizeCommonSpectrum4060, colorCombMC4060, colorCombMC4060);
//    cout << "bla" << endl;
//    DrawGammaSetMarkerTGraphErr( meanTrackMultV0LHC13d26080,  markerStyleCommmonSpectrumMC6080, markerSizeCommonSpectrum6080, colorCombMC6080, colorCombMC6080);
//    cout << "bla" << endl;

   
	cout << "Plot 1" << endl;
   
   
	TCanvas* canvasNGammaEvtData = new TCanvas("canvasNGammaEvtData","",200,10,1350,1000);  // gives the page size
	DrawGammaCanvasSettings( canvasNGammaEvtData, 0.1, 0.04, 0.06, 0.09);
 	canvasNGammaEvtData->SetLogy();
	
	TH2F * histo2DEff;
	histo2DEff = new TH2F("histo2DEff","histo2DEff",2450,137100,139550,100,0.6,40	);
// 	histo2DEff->GetXaxis()->SetRangeUser(0.,2100.);
	SetStyleHistoTH2ForGraphs(histo2DEff, "Run number","#gamma_{cand}/N_{evt}",0.03,0.04, 0.03,0.04, 1.,1.);
	histo2DEff->Draw("copy");

	fractionOfGammasData0005->Draw("pesame");
	fractionOfGammasData0510->Draw("pesame");
	fractionOfGammasData1020->Draw("pesame");
	fractionOfGammasData2040->Draw("pesame");
	fractionOfGammasData4060->Draw("pesame");
	fractionOfGammasData6080->Draw("pesame");
	
	TLegend* legendData = new TLegend(0.095,0.945,0.99,1.);
	legendData->SetFillColor(0);
	legendData->SetLineColor(0);
	legendData->SetTextSize(0.04);
	legendData->SetNColumns(6);
// 	legendData->AddEntry((TObject*)0, "Data:","");
	legendData->AddEntry(fractionOfGammasData0005,"0-5%","p");
	legendData->AddEntry(fractionOfGammasData0510,"5-10%","p");
	legendData->AddEntry(fractionOfGammasData1020,"10-20%","p");
	legendData->AddEntry(fractionOfGammasData2040,"20-40%","p");
	legendData->AddEntry(fractionOfGammasData4060,"40-60%","p");
	legendData->AddEntry(fractionOfGammasData6080,"60-80%","p");
	legendData->Draw();

	canvasNGammaEvtData->SaveAs(Form("%s/FractionOfPhotonsPerEvent.%s",outputDir.Data(),suffix.Data()));
	delete canvasNGammaEvtData;

   cout << "Plot 2" << endl;
	TCanvas* canvasNPi0EvtData = new TCanvas("canvasNPi0EvtData","",200,10,1350,1000);  // gives the page size
	DrawGammaCanvasSettings( canvasNPi0EvtData, 0.1, 0.04, 0.06, 0.09);
 	canvasNPi0EvtData->SetLogy();
	
	TH2F * histo2DFracPi0;
	histo2DFracPi0 = new TH2F("histo2DFracPi0","histo2DFracPi0",2450,137100,139550,100,0.0002,0.6);
// 	histo2DFracPi0->GetXaxis()->SetRangeUser(0.,2100.);
	SetStyleHistoTH2ForGraphs(histo2DFracPi0, "Run number","N_{#pi^{0}_{cand}}/N_{evt}",0.03,0.04, 0.03,0.04, 1.,1.);
	histo2DFracPi0->Draw("copy");

	fractionOfPi0Data0005->Draw("pesame");
	fractionOfPi0Data0510->Draw("pesame");
	fractionOfPi0Data1020->Draw("pesame");
	fractionOfPi0Data2040->Draw("pesame");
	fractionOfPi0Data4060->Draw("pesame");
	fractionOfPi0Data6080->Draw("pesame");
	
	legendData->Draw();

	canvasNPi0EvtData->SaveAs(Form("%s/FractionOfPi0PerEvent.%s",outputDir.Data(),suffix.Data()));
	delete canvasNPi0EvtData;

   cout << "Plot 3" << endl;
	TCanvas* canvasMassPi0Data = new TCanvas("canvasMassPi0Data","",200,10,1350,1000);  // gives the page size
	DrawGammaCanvasSettings( canvasMassPi0Data, 0.1, 0.04, 0.06, 0.09);
	
	TH2F * histo2DMassPi0;
	histo2DMassPi0 = new TH2F("histo2DMassPi0","histo2DMassPi0",2450,137100,139550,100,0.125,0.15);
// 	histo2DMassPi0->GetXaxis()->SetRangeUser(0.,2100.);
	SetStyleHistoTH2ForGraphs(histo2DMassPi0, "Run number","m_{#pi^{0}} (GeV/c^{2})",0.03,0.04, 0.03,0.04, 1.,1.3);
	histo2DMassPi0->Draw("copy");

	massPi0Data0005->Draw("pesame");
	massPi0Data0510->Draw("pesame");
	massPi0Data1020->Draw("pesame");
	massPi0Data2040->Draw("pesame");
	massPi0Data4060->Draw("pesame");
	massPi0Data6080->Draw("pesame");
	DrawGammaLines(137100, 139550.,0.135, 0.135,1,kGray+2);
	legendData->Draw();

	canvasMassPi0Data->SaveAs(Form("%s/MassPi0_PbPb.%s",outputDir.Data(),suffix.Data()));
	delete canvasMassPi0Data;

   cout << "Plot 4" << endl;
	TCanvas* canvasWidthPi0Data = new TCanvas("canvasWidthPi0Data","",200,10,1350,1000);  // gives the page size
	DrawGammaCanvasSettings( canvasWidthPi0Data, 0.1, 0.04, 0.06, 0.09);
	
	TH2F * histo2DWidthPi0;
	histo2DWidthPi0 = new TH2F("histo2DWidthPi0","histo2DWidthPi0",2450,137100,139550,100,0.0,0.042);
// 	histo2DWidthPi0->GetXaxis()->SetRangeUser(0.,2100.);
	SetStyleHistoTH2ForGraphs(histo2DWidthPi0, "Run number","FWHM_{#pi^{0}} (GeV/c^{2})",0.03,0.04, 0.03,0.04, 1.,1.3);
	histo2DWidthPi0->Draw("copy");

	widthPi0Data0005->Draw("pesame");
	widthPi0Data0510->Draw("pesame");
	widthPi0Data1020->Draw("pesame");
	widthPi0Data2040->Draw("pesame");
	widthPi0Data4060->Draw("pesame");
	widthPi0Data6080->Draw("pesame");
	legendData->Draw();

	canvasWidthPi0Data->SaveAs(Form("%s/WidthPi0_PbPb.%s",outputDir.Data(),suffix.Data()));
	delete canvasWidthPi0Data;
   
   cout << "Plot 5" << endl;
	TCanvas* canvasMultTPCData = new TCanvas("canvasMultTPCData","",200,10,1350,1000);  // gives the page size
	DrawGammaCanvasSettings( canvasMultTPCData, 0.1, 0.04, 0.06, 0.09);
// 	canvasMultTPCData->SetLogy();
	
	TH2F * histoMultTPC;
	histoMultTPC = new TH2F("histoMultTPC","histoMultTPC",2450,137100,139550,100,0,1950);
// 	histoMultTPC->GetXaxis()->SetRangeUser(0.,2100.);
	SetStyleHistoTH2ForGraphs(histoMultTPC, "Run number","#LT n tracks TPC #GT",0.03,0.04, 0.03,0.04, 1.,1.2);
	histoMultTPC->Draw("copy");


	meanTrackMultTPCData0005->Draw("pesame");
	meanTrackMultTPCData0510->Draw("pesame");
	meanTrackMultTPCData1020->Draw("pesame");
	meanTrackMultTPCData2040->Draw("pesame");
	meanTrackMultTPCData4060->Draw("pesame");
	meanTrackMultTPCData6080->Draw("pesame");
	
	TLegend* legendMultTPC = new TLegend(0.095,0.945,0.99,1.);
	legendMultTPC->SetFillColor(0);
	legendMultTPC->SetLineColor(0);
	legendMultTPC->SetTextSize(0.04);
	legendMultTPC->SetNColumns(6);
// 	legendMultTPC->AddEntry((TObject*)0, "Data:","");
	legendMultTPC->AddEntry(meanTrackMultTPCData0005,"0-5%","p");
	legendMultTPC->AddEntry(meanTrackMultTPCData0510,"5-10%","p");
	legendMultTPC->AddEntry(meanTrackMultTPCData1020,"10-20%","p");
	legendMultTPC->AddEntry(meanTrackMultTPCData2040,"20-40%","p");
	legendMultTPC->AddEntry(meanTrackMultTPCData4060,"40-60%","p");
	legendMultTPC->AddEntry(meanTrackMultTPCData6080,"60-80%","p");
	legendMultTPC->Draw();

	canvasMultTPCData->SaveAs(Form("%s/MeanMultiplicity_TPCTracks.%s",outputDir.Data(),suffix.Data()));
	delete canvasMultTPCData;

   cout << "Plot 6" << endl;
	TCanvas* canvasMultTPCComb = new TCanvas("canvasMultTPCComb","",200,10,1350,1000);  // gives the page size
	DrawGammaCanvasSettings( canvasMultTPCComb, 0.1, 0.04, 0.12, 0.09);
// 	canvasMultTPCComb->SetLogy();
	
	histoMultTPC->Draw("copy");


	meanTrackMultTPCData0005->Draw("pesame");
	meanTrackMultTPCData0510->Draw("pesame");
	meanTrackMultTPCData1020->Draw("pesame");
	meanTrackMultTPCData2040->Draw("pesame");
	meanTrackMultTPCData4060->Draw("pesame");
	meanTrackMultTPCData6080->Draw("pesame");
	
	meanTrackMultTPCLHC11a10a_bis0005->Draw("pesame");
	meanTrackMultTPCLHC11a10a_bis0510->Draw("pesame");
	meanTrackMultTPCLHC11a10a_bis1020->Draw("pesame");
	meanTrackMultTPCLHC11a10a_bis2040->Draw("pesame");
	meanTrackMultTPCLHC11a10a_bis4060->Draw("pesame");
	meanTrackMultTPCLHC11a10a_bis6080->Draw("pesame");
	
	
	TLegend* legendMultTPCComb = new TLegend(0.07,0.945,0.99,1.);
	legendMultTPCComb->SetFillColor(0);
	legendMultTPCComb->SetLineColor(0);
	legendMultTPCComb->SetTextSize(0.04);
	legendMultTPCComb->SetNColumns(7);
	legendMultTPCComb->AddEntry((TObject*)0, "Data:","");
	legendMultTPCComb->AddEntry(meanTrackMultTPCData0005,"0-5%","p");
	legendMultTPCComb->AddEntry(meanTrackMultTPCData0510,"5-10%","p");
	legendMultTPCComb->AddEntry(meanTrackMultTPCData1020,"10-20%","p");
	legendMultTPCComb->AddEntry(meanTrackMultTPCData2040,"20-40%","p");
	legendMultTPCComb->AddEntry(meanTrackMultTPCData4060,"40-60%","p");
	legendMultTPCComb->AddEntry(meanTrackMultTPCData6080,"60-80%","p");
	legendMultTPCComb->Draw();

	TLegend* legendMultMC = new TLegend(0.07,0.885,0.99,0.945);
	legendMultMC->SetFillColor(0);
	legendMultMC->SetLineColor(0);
	legendMultMC->SetTextSize(0.04);
	legendMultMC->SetNColumns(7);
	legendMultMC->AddEntry((TObject*)0, "MC:  ","");
	legendMultMC->AddEntry(meanTrackMultTPCLHC11a10a_bis0005,"0-5%","p");
	legendMultMC->AddEntry(meanTrackMultTPCLHC11a10a_bis0510,"5-10%","p");
	legendMultMC->AddEntry(meanTrackMultTPCLHC11a10a_bis1020,"10-20%","p");
	legendMultMC->AddEntry(meanTrackMultTPCLHC11a10a_bis2040,"20-40%","p");
	legendMultMC->AddEntry(meanTrackMultTPCLHC11a10a_bis4060,"40-60%","p");
	legendMultMC->AddEntry(meanTrackMultTPCLHC11a10a_bis6080,"60-80%","p");
	legendMultMC->Draw();


	canvasMultTPCComb->SaveAs(Form("%s/MeanMultiplicity_TPCTracks_LHC11a10a_bis.%s",outputDir.Data(),suffix.Data()));
   
   cout << "Plot 7" << endl;
   canvasMultTPCComb->cd();
   histoMultTPC->Draw("copy");


   meanTrackMultTPCData0005->Draw("pesame");
   meanTrackMultTPCData0510->Draw("pesame");
   meanTrackMultTPCData1020->Draw("pesame");
   meanTrackMultTPCData2040->Draw("pesame");
   meanTrackMultTPCData4060->Draw("pesame");
   meanTrackMultTPCData6080->Draw("pesame");
   
   meanTrackMultTPCLHC13d20005->Draw("pesame");
   meanTrackMultTPCLHC13d20510->Draw("pesame");
   meanTrackMultTPCLHC13d21020->Draw("pesame");
   meanTrackMultTPCLHC13d22040->Draw("pesame");
   meanTrackMultTPCLHC13d24060->Draw("pesame");
   meanTrackMultTPCLHC13d26080->Draw("pesame");
   
   legendMultTPCComb->Draw();

   TLegend* legendMultMC2 = new TLegend(0.07,0.885,0.99,0.945);
   legendMultMC2->SetFillColor(0);
   legendMultMC2->SetLineColor(0);
   legendMultMC2->SetTextSize(0.04);
   legendMultMC2->SetNColumns(7);
   legendMultMC2->AddEntry((TObject*)0, "MC:  ","");
   legendMultMC2->AddEntry(meanTrackMultTPCLHC13d20005,"0-5%","p");
   legendMultMC2->AddEntry(meanTrackMultTPCLHC13d20510,"5-10%","p");
   legendMultMC2->AddEntry(meanTrackMultTPCLHC13d21020,"10-20%","p");
   legendMultMC2->AddEntry(meanTrackMultTPCLHC13d22040,"20-40%","p");
   legendMultMC2->AddEntry(meanTrackMultTPCLHC13d24060,"40-60%","p");
   legendMultMC2->AddEntry(meanTrackMultTPCLHC13d26080,"60-80%","p");
   legendMultMC2->Draw();


   canvasMultTPCComb->SaveAs(Form("%s/MeanMultiplicity_TPCTracks_LHC13d2.%s",outputDir.Data(),suffix.Data()));
   
	delete canvasMultTPCComb;

	cout << "Plot 8" << endl;
	TCanvas* canvasMultV0Data = new TCanvas("canvasMultV0Data","",200,10,1350,1000);  // gives the page size
	DrawGammaCanvasSettings( canvasMultV0Data, 0.1, 0.04, 0.06, 0.09);
// 	canvasMultV0Data->SetLogy();
	
	TH2F * histoMultV0;
	histoMultV0 = new TH2F("histoMultV0","histoMultV0",2450,137100,139550,100,0,24500);
// 	histoMultV0->GetXaxis()->SetRangeUser(0.,2100.);
	SetStyleHistoTH2ForGraphs(histoMultV0, "Run number","#LT VZERO amplitude #GT",0.03,0.04, 0.03,0.04, 1.,1.2);
	histoMultV0->Draw("copy");


	meanTrackMultV0Data0005->Draw("pesame");
	meanTrackMultV0Data0510->Draw("pesame");
	meanTrackMultV0Data1020->Draw("pesame");
	meanTrackMultV0Data2040->Draw("pesame");
	meanTrackMultV0Data4060->Draw("pesame");
	meanTrackMultV0Data6080->Draw("pesame");
	
	TLegend* legendMultV0 = new TLegend(0.095,0.945,0.99,1.);
	legendMultV0->SetFillColor(0);
	legendMultV0->SetLineColor(0);
	legendMultV0->SetTextSize(0.04);
	legendMultV0->SetNColumns(6);
// 	legendMultV0->AddEntry((TObject*)0, "Data:","");
	legendMultV0->AddEntry(meanTrackMultV0Data0005,"0-5%","p");
	legendMultV0->AddEntry(meanTrackMultV0Data0510,"5-10%","p");
	legendMultV0->AddEntry(meanTrackMultV0Data1020,"10-20%","p");
	legendMultV0->AddEntry(meanTrackMultV0Data2040,"20-40%","p");
	legendMultV0->AddEntry(meanTrackMultV0Data4060,"40-60%","p");
	legendMultV0->AddEntry(meanTrackMultV0Data6080,"60-80%","p");
	legendMultV0->Draw();

	canvasMultV0Data->SaveAs(Form("%s/MeanMultiplicity_V0Tracks.%s",outputDir.Data(),suffix.Data()));
	delete canvasMultV0Data;

   cout << "Plot 9" << endl;
	TCanvas* canvasMultV0Comb = new TCanvas("canvasMultV0Comb","",200,10,1350,1000);  // gives the page size
	DrawGammaCanvasSettings( canvasMultV0Comb, 0.1, 0.04, 0.12, 0.09);
// 	canvasMultV0Comb->SetLogy();
	
	histoMultV0->Draw("copy");


	meanTrackMultV0Data0005->Draw("pesame");
	meanTrackMultV0Data0510->Draw("pesame");
	meanTrackMultV0Data1020->Draw("pesame");
	meanTrackMultV0Data2040->Draw("pesame");
	meanTrackMultV0Data4060->Draw("pesame");
	meanTrackMultV0Data6080->Draw("pesame");
	
	meanTrackMultV0LHC11a10a_bis0005->Draw("pesame");
	meanTrackMultV0LHC11a10a_bis0510->Draw("pesame");
	meanTrackMultV0LHC11a10a_bis1020->Draw("pesame");
	meanTrackMultV0LHC11a10a_bis2040->Draw("pesame");
	meanTrackMultV0LHC11a10a_bis4060->Draw("pesame");
	meanTrackMultV0LHC11a10a_bis6080->Draw("pesame");
	
	legendMultTPCComb->Draw();
	legendMultMC->Draw();

	canvasMultV0Comb->SaveAs(Form("%s/MeanMultiplicity_V0Tracks_LHC11a10a_bis.%s",outputDir.Data(),suffix.Data()));
   
//    cout << "Plot 10" << endl;
//    canvasMultV0Comb->cd();
//    histoMultV0->Draw("copy");
// 
//    meanTrackMultV0Data0005->Draw("pesame");
//    meanTrackMultV0Data0510->Draw("pesame");
//    meanTrackMultV0Data1020->Draw("pesame");
//    meanTrackMultV0Data2040->Draw("pesame");
//    meanTrackMultV0Data4060->Draw("pesame");
//    meanTrackMultV0Data6080->Draw("pesame");
//    
//    meanTrackMultV0LHC13d20005->Draw("pesame");
//    meanTrackMultV0LHC13d20510->Draw("pesame");
//    meanTrackMultV0LHC13d21020->Draw("pesame");
//    meanTrackMultV0LHC13d22040->Draw("pesame");
//    meanTrackMultV0LHC13d24060->Draw("pesame");
//    meanTrackMultV0LHC13d26080->Draw("pesame");
//    
//    legendMultTPCComb->Draw();
//    legendMultMC2->Draw();
// 
//    canvasMultV0Comb->SaveAs(Form("%s/MeanMultiplicity_V0Tracks_LHC13d2.%s",outputDir.Data(),suffix.Data()));
	delete canvasMultV0Comb;

   cout << "Plot 11" << endl;
	TCanvas* canvasNGammaEvtComb = new TCanvas("canvasNGammaEvtComb","",200,10,1350,1000);  // gives the page size
	DrawGammaCanvasSettings( canvasNGammaEvtComb, 0.1, 0.04, 0.12, 0.09);
	canvasNGammaEvtComb->SetLogy();
	
	histo2DEff->Draw("copy");
	fractionOfGammasData0005->Draw("pesame");
	fractionOfGammasData0510->Draw("pesame");
	fractionOfGammasData1020->Draw("pesame");
	fractionOfGammasData2040->Draw("pesame");
	fractionOfGammasData4060->Draw("pesame");
	fractionOfGammasData6080->Draw("pesame");

	fractionOfGammasLHC11a10a0005->Draw("pesame");
	fractionOfGammasLHC11a10a0510->Draw("pesame");
	fractionOfGammasLHC11a10a1020->Draw("pesame");
	fractionOfGammasLHC11a10a2040->Draw("pesame");
	fractionOfGammasLHC11a10a4060->Draw("pesame");
	fractionOfGammasLHC11a10a6080->Draw("pesame");

	TLegend* legendDataComb = new TLegend(0.07,0.945,0.99,1.);
	legendDataComb->SetFillColor(0);
	legendDataComb->SetLineColor(0);
	legendDataComb->SetTextSize(0.04);
	legendDataComb->SetNColumns(7);
	legendDataComb->AddEntry((TObject*)0, "Data:","");
	legendDataComb->AddEntry(fractionOfGammasData0005,"0-5%","p");
	legendDataComb->AddEntry(fractionOfGammasData0510,"5-10%","p");
	legendDataComb->AddEntry(fractionOfGammasData1020,"10-20%","p");
	legendDataComb->AddEntry(fractionOfGammasData2040,"20-40%","p");
	legendDataComb->AddEntry(fractionOfGammasData4060,"40-60%","p");
	legendDataComb->AddEntry(fractionOfGammasData6080,"60-80%","p");
	legendDataComb->Draw();

	TLegend* legendMC = new TLegend(0.07,0.885,0.99,0.945);
	legendMC->SetFillColor(0);
	legendMC->SetLineColor(0);
	legendMC->SetTextSize(0.04);
	legendMC->SetNColumns(7);
	legendMC->AddEntry((TObject*)0, "MC:  ","");
	legendMC->AddEntry(fractionOfGammasLHC11a10a0005,"0-5%","p");
	legendMC->AddEntry(fractionOfGammasLHC11a10a0510,"5-10%","p");
	legendMC->AddEntry(fractionOfGammasLHC11a10a1020,"10-20%","p");
	legendMC->AddEntry(fractionOfGammasLHC11a10a2040,"20-40%","p");
	legendMC->AddEntry(fractionOfGammasLHC11a10a4060,"40-60%","p");
	legendMC->AddEntry(fractionOfGammasLHC11a10a6080,"60-80%","p");
	legendMC->Draw();

	canvasNGammaEvtComb->SaveAs(Form("%s/FractionOfPhotonsPerEvent_WithMCLHC11a10a.%s",outputDir.Data(),suffix.Data()));
	delete canvasNGammaEvtComb;

   cout << "Plot 12" << endl;
	TCanvas* canvasGoodEventsCombLHC11a10a = new TCanvas("canvasGoodEventsCombLHC11a10a","",200,10,1350,1000);  // gives the page size
	DrawGammaCanvasSettings( canvasGoodEventsCombLHC11a10a, 0.1, 0.04, 0.12, 0.09);

	TH2F * histo2DGoodEvents;
	histo2DGoodEvents = new TH2F("histo2DGoodEvents","histo2DGoodEvents",2450,137100,139550,100,0.,0.26);
// 	histo2DGoodEvents->GetXaxis()->SetRangeUser(0.,2100.);
	SetStyleHistoTH2ForGraphs(histo2DGoodEvents, "Run number","N^{evt}_{good}/N^{evt}_{Min. Bias}",0.03,0.04, 0.03,0.04, 1.,1.3);
	histo2DGoodEvents->Draw("copy");
	
	fractionOfGoodEventsData0005->Draw("pesame");
	fractionOfGoodEventsData0510->Draw("pesame");
	fractionOfGoodEventsData1020->Draw("pesame");
	fractionOfGoodEventsData2040->Draw("pesame");
	fractionOfGoodEventsData4060->Draw("pesame");
	fractionOfGoodEventsData6080->Draw("pesame");

	fractionOfGoodEventsLHC11a10a0005->Draw("pesame");
	fractionOfGoodEventsLHC11a10a0510->Draw("pesame");
	fractionOfGoodEventsLHC11a10a1020->Draw("pesame");
	fractionOfGoodEventsLHC11a10a2040->Draw("pesame");
	fractionOfGoodEventsLHC11a10a4060->Draw("pesame");
	fractionOfGoodEventsLHC11a10a6080->Draw("pesame");

	legendDataComb->Draw();
	legendMC->Draw();

	canvasGoodEventsCombLHC11a10a->SaveAs(Form("%s/FractionOfGoodEvents_WithMCLHC11a10a.%s",outputDir.Data(),suffix.Data()));
	delete canvasGoodEventsCombLHC11a10a;

   cout << "Plot 13" << endl;
	TCanvas* canvasNormAllCombLHC11a10a = new TCanvas("canvasNormAllCombLHC11a10a","",200,10,1350,1000);  // gives the page size
	DrawGammaCanvasSettings( canvasNormAllCombLHC11a10a, 0.1, 0.04, 0.12, 0.09);
	
	TH2F * histo2DNormAll;
	histo2DNormAll = new TH2F("histo2DNormAll","histo2DNormAll",2450,137100,139550,100,0,0.31	);
// 	histo2DNormAll->GetXaxis()->SetRangeUser(0.,2100.);
	SetStyleHistoTH2ForGraphs(histo2DNormAll, "Run number","N^{evt}_{norm}/N^{evt}_{all}",0.03,0.04, 0.03,0.04, 1.,1.3);
	histo2DNormAll->Draw("copy");

	fractionOfNormAllData0005->Draw("pesame");
	fractionOfNormAllData0510->Draw("pesame");
	fractionOfNormAllData1020->Draw("pesame");
	fractionOfNormAllData2040->Draw("pesame");
	fractionOfNormAllData4060->Draw("pesame");
	fractionOfNormAllData6080->Draw("pesame");

	fractionOfNormAllLHC11a10a0005->Draw("pesame");
	fractionOfNormAllLHC11a10a0510->Draw("pesame");
	fractionOfNormAllLHC11a10a1020->Draw("pesame");
	fractionOfNormAllLHC11a10a2040->Draw("pesame");
	fractionOfNormAllLHC11a10a4060->Draw("pesame");
	fractionOfNormAllLHC11a10a6080->Draw("pesame");

	legendDataComb->Draw();
	legendMC->Draw();

	canvasNormAllCombLHC11a10a->SaveAs(Form("%s/FractionOfNormAll_WithMCLHC11a10a.%s",outputDir.Data(),suffix.Data()));
	delete canvasNormAllCombLHC11a10a;

   cout << "Plot 14" << endl;
	TCanvas* canvasNormMinBiasCombLHC11a10a = new TCanvas("canvasNormMinBiasCombLHC11a10a","",200,10,1350,1000);  // gives the page size
	DrawGammaCanvasSettings( canvasNormMinBiasCombLHC11a10a, 0.1, 0.04, 0.12, 0.09);
	
		TH2F * histo2DNormMinBias;
	histo2DNormMinBias = new TH2F("histo2DNormMinBias","histo2DNormMinBias",2450,137100,139550,100,0.,0.26	);
// 	histo2DNormMinBias->GetXaxis()->SetRangeUser(0.,2100.);
	SetStyleHistoTH2ForGraphs(histo2DNormMinBias, "Run number","N^{evt}_{norm}/N^{evt}_{Min. Bias}",0.03,0.04, 0.03,0.04, 1.,1.3);
	histo2DNormMinBias->Draw("copy");

	fractionOfNormMinBiasData0005->Draw("pesame");
	fractionOfNormMinBiasData0510->Draw("pesame");
	fractionOfNormMinBiasData1020->Draw("pesame");
	fractionOfNormMinBiasData2040->Draw("pesame");
	fractionOfNormMinBiasData4060->Draw("pesame");
	fractionOfNormMinBiasData6080->Draw("pesame");

	fractionOfNormMinBiasLHC11a10a0005->Draw("pesame");
	fractionOfNormMinBiasLHC11a10a0510->Draw("pesame");
	fractionOfNormMinBiasLHC11a10a1020->Draw("pesame");
	fractionOfNormMinBiasLHC11a10a2040->Draw("pesame");
	fractionOfNormMinBiasLHC11a10a4060->Draw("pesame");
	fractionOfNormMinBiasLHC11a10a6080->Draw("pesame");

	legendDataComb->Draw();
	legendMC->Draw();

	canvasNormMinBiasCombLHC11a10a->SaveAs(Form("%s/FractionOfNormMinBias_WithMCLHC11a10a.%s",outputDir.Data(),suffix.Data()));
	delete canvasNormMinBiasCombLHC11a10a;

	cout << "Plot 15" << endl;
	TCanvas* canvasNGammaEvtLHC11a10a_bis = new TCanvas("canvasNGammaEvtLHC11a10a_bis","",200,10,1350,1000);  // gives the page size
	DrawGammaCanvasSettings( canvasNGammaEvtLHC11a10a_bis, 0.1, 0.04, 0.12, 0.09);
	canvasNGammaEvtLHC11a10a_bis->SetLogy();
	
	histo2DEff->Draw("copy");

	fractionOfGammasData0005->Draw("pesame");
	fractionOfGammasData0510->Draw("pesame");
	fractionOfGammasData1020->Draw("pesame");
	fractionOfGammasData2040->Draw("pesame");
	fractionOfGammasData4060->Draw("pesame");
	fractionOfGammasData6080->Draw("pesame");

	fractionOfGammasLHC11a10a_bis0005->Draw("pesame");
	fractionOfGammasLHC11a10a_bis0510->Draw("pesame");
	fractionOfGammasLHC11a10a_bis1020->Draw("pesame");
	fractionOfGammasLHC11a10a_bis2040->Draw("pesame");
	fractionOfGammasLHC11a10a_bis4060->Draw("pesame");
	fractionOfGammasLHC11a10a_bis6080->Draw("pesame");

	legendDataComb->Draw();
	legendMC->Draw();

	canvasNGammaEvtLHC11a10a_bis->SaveAs(Form("%s/FractionOfPhotonsPerEvent_WithMCLHC11a10a_bis.%s",outputDir.Data(),suffix.Data()));
	delete canvasNGammaEvtLHC11a10a_bis;

   cout << "Plot 16" << endl;
	TCanvas* canvasGoodEventsCombLHC11a10a_bis = new TCanvas("canvasGoodEventsCombLHC11a10a_bis","",200,10,1350,1000);  // gives the page size
	DrawGammaCanvasSettings( canvasGoodEventsCombLHC11a10a_bis, 0.1, 0.04, 0.12, 0.09);

	histo2DGoodEvents->Draw("copy");
	
	fractionOfGoodEventsData0005->Draw("pesame");
	fractionOfGoodEventsData0510->Draw("pesame");
	fractionOfGoodEventsData1020->Draw("pesame");
	fractionOfGoodEventsData2040->Draw("pesame");
	fractionOfGoodEventsData4060->Draw("pesame");
	fractionOfGoodEventsData6080->Draw("pesame");

	fractionOfGoodEventsLHC11a10a_bis0005->Draw("pesame");
	fractionOfGoodEventsLHC11a10a_bis0510->Draw("pesame");
	fractionOfGoodEventsLHC11a10a_bis1020->Draw("pesame");
	fractionOfGoodEventsLHC11a10a_bis2040->Draw("pesame");
	fractionOfGoodEventsLHC11a10a_bis4060->Draw("pesame");
	fractionOfGoodEventsLHC11a10a_bis6080->Draw("pesame");

	legendDataComb->Draw();
	legendMC->Draw();

	canvasGoodEventsCombLHC11a10a_bis->SaveAs(Form("%s/FractionOfGoodEvents_WithMCLHC11a10a_bis.%s",outputDir.Data(),suffix.Data()));
	delete canvasGoodEventsCombLHC11a10a_bis;

   cout << "Plot 17" << endl;
	TCanvas* canvasNormAllCombLHC11a10a_bis = new TCanvas("canvasNormAllCombLHC11a10a_bis","",200,10,1350,1000);  // gives the page size
	DrawGammaCanvasSettings( canvasNormAllCombLHC11a10a_bis, 0.1, 0.04, 0.12, 0.09);
	
	histo2DNormAll->Draw("copy");

	fractionOfNormAllData0005->Draw("pesame");
	fractionOfNormAllData0510->Draw("pesame");
	fractionOfNormAllData1020->Draw("pesame");
	fractionOfNormAllData2040->Draw("pesame");
	fractionOfNormAllData4060->Draw("pesame");
	fractionOfNormAllData6080->Draw("pesame");

	fractionOfNormAllLHC11a10a_bis0005->Draw("pesame");
	fractionOfNormAllLHC11a10a_bis0510->Draw("pesame");
	fractionOfNormAllLHC11a10a_bis1020->Draw("pesame");
	fractionOfNormAllLHC11a10a_bis2040->Draw("pesame");
	fractionOfNormAllLHC11a10a_bis4060->Draw("pesame");
	fractionOfNormAllLHC11a10a_bis6080->Draw("pesame");

	legendDataComb->Draw();
	legendMC->Draw();

	canvasNormAllCombLHC11a10a_bis->SaveAs(Form("%s/FractionOfNormAll_WithMCLHC11a10a_bis.%s",outputDir.Data(),suffix.Data()));
	delete canvasNormAllCombLHC11a10a_bis;

   cout << "Plot 18" << endl;
	TCanvas* canvasNormMinBiasCombLHC11a10a_bis = new TCanvas("canvasNormMinBiasCombLHC11a10a_bis","",200,10,1350,1000);  // gives the page size
	DrawGammaCanvasSettings( canvasNormMinBiasCombLHC11a10a_bis, 0.1, 0.04, 0.12, 0.09);
	
	histo2DNormMinBias->Draw("copy");

	fractionOfNormMinBiasData0005->Draw("pesame");
	fractionOfNormMinBiasData0510->Draw("pesame");
	fractionOfNormMinBiasData1020->Draw("pesame");
	fractionOfNormMinBiasData2040->Draw("pesame");
	fractionOfNormMinBiasData4060->Draw("pesame");
	fractionOfNormMinBiasData6080->Draw("pesame");

	fractionOfNormMinBiasLHC11a10a_bis0005->Draw("pesame");
	fractionOfNormMinBiasLHC11a10a_bis0510->Draw("pesame");
	fractionOfNormMinBiasLHC11a10a_bis1020->Draw("pesame");
	fractionOfNormMinBiasLHC11a10a_bis2040->Draw("pesame");
	fractionOfNormMinBiasLHC11a10a_bis4060->Draw("pesame");
	fractionOfNormMinBiasLHC11a10a_bis6080->Draw("pesame");

	legendDataComb->Draw();
	legendMC->Draw();

	canvasNormMinBiasCombLHC11a10a_bis->SaveAs(Form("%s/FractionOfNormMinBias_WithMCLHC11a10a_bis.%s",outputDir.Data(),suffix.Data()));
	delete canvasNormMinBiasCombLHC11a10a_bis;

	cout << "Plot 19" << endl;
	TCanvas* canvasNGammaEvtLHC11a10b_bis = new TCanvas("canvasNGammaEvtLHC11a10b_bis","",200,10,1350,1000);  // gives the page size
	DrawGammaCanvasSettings( canvasNGammaEvtLHC11a10b_bis, 0.1, 0.04, 0.12, 0.09);
	canvasNGammaEvtLHC11a10b_bis->SetLogy();
	
	histo2DEff->Draw("copy");

	fractionOfGammasData0005->Draw("pesame");
	fractionOfGammasData0510->Draw("pesame");
	fractionOfGammasData1020->Draw("pesame");
	fractionOfGammasData2040->Draw("pesame");
	fractionOfGammasData4060->Draw("pesame");
	fractionOfGammasData6080->Draw("pesame");

	fractionOfGammasLHC11a10b_bis0005->Draw("pesame");
	fractionOfGammasLHC11a10b_bis0510->Draw("pesame");
	fractionOfGammasLHC11a10b_bis1020->Draw("pesame");
	fractionOfGammasLHC11a10b_bis2040->Draw("pesame");
	fractionOfGammasLHC11a10b_bis4060->Draw("pesame");
	fractionOfGammasLHC11a10b_bis6080->Draw("pesame");

	legendDataComb->Draw();
	legendMC->Draw();

	canvasNGammaEvtLHC11a10b_bis->SaveAs(Form("%s/FractionOfPhotonsPerEvent_WithMCLHC11a10b_bis.%s",outputDir.Data(),suffix.Data()));
	delete canvasNGammaEvtLHC11a10b_bis;

   cout << "Plot 20" << endl;
	TCanvas* canvasGoodEventsCombLHC11a10b_bis = new TCanvas("canvasGoodEventsCombLHC11a10b_bis","",200,10,1350,1000);  // gives the page size
	DrawGammaCanvasSettings( canvasGoodEventsCombLHC11a10b_bis, 0.1, 0.04, 0.12, 0.09);

	histo2DGoodEvents->Draw("copy");
	
	fractionOfGoodEventsData0005->Draw("pesame");
	fractionOfGoodEventsData0510->Draw("pesame");
	fractionOfGoodEventsData1020->Draw("pesame");
	fractionOfGoodEventsData2040->Draw("pesame");
	fractionOfGoodEventsData4060->Draw("pesame");
	fractionOfGoodEventsData6080->Draw("pesame");

	fractionOfGoodEventsLHC11a10b_bis0005->Draw("pesame");
	fractionOfGoodEventsLHC11a10b_bis0510->Draw("pesame");
	fractionOfGoodEventsLHC11a10b_bis1020->Draw("pesame");
	fractionOfGoodEventsLHC11a10b_bis2040->Draw("pesame");
	fractionOfGoodEventsLHC11a10b_bis4060->Draw("pesame");
	fractionOfGoodEventsLHC11a10b_bis6080->Draw("pesame");

	legendDataComb->Draw();
	legendMC->Draw();

	canvasGoodEventsCombLHC11a10b_bis->SaveAs(Form("%s/FractionOfGoodEvents_WithMCLHC11a10b_bis.%s",outputDir.Data(),suffix.Data()));
	delete canvasGoodEventsCombLHC11a10b_bis;

   cout << "Plot 21" << endl;
	TCanvas* canvasNormAllCombLHC11a10b_bis = new TCanvas("canvasNormAllCombLHC11a10b_bis","",200,10,1350,1000);  // gives the page size
	DrawGammaCanvasSettings( canvasNormAllCombLHC11a10b_bis, 0.1, 0.04, 0.12, 0.09);
	
	histo2DNormAll->Draw("copy");

	fractionOfNormAllData0005->Draw("pesame");
	fractionOfNormAllData0510->Draw("pesame");
	fractionOfNormAllData1020->Draw("pesame");
	fractionOfNormAllData2040->Draw("pesame");
	fractionOfNormAllData4060->Draw("pesame");
	fractionOfNormAllData6080->Draw("pesame");

	fractionOfNormAllLHC11a10b_bis0005->Draw("pesame");
	fractionOfNormAllLHC11a10b_bis0510->Draw("pesame");
	fractionOfNormAllLHC11a10b_bis1020->Draw("pesame");
	fractionOfNormAllLHC11a10b_bis2040->Draw("pesame");
	fractionOfNormAllLHC11a10b_bis4060->Draw("pesame");
	fractionOfNormAllLHC11a10b_bis6080->Draw("pesame");

	legendDataComb->Draw();
	legendMC->Draw();

	canvasNormAllCombLHC11a10b_bis->SaveAs(Form("%s/FractionOfNormAll_WithMCLHC11a10b_bis.%s",outputDir.Data(),suffix.Data()));
	delete canvasNormAllCombLHC11a10b_bis;

   cout << "Plot 22" << endl;
	TCanvas* canvasNormMinBiasCombLHC11a10b_bis = new TCanvas("canvasNormMinBiasCombLHC11a10b_bis","",200,10,1350,1000);  // gives the page size
	DrawGammaCanvasSettings( canvasNormMinBiasCombLHC11a10b_bis, 0.1, 0.04, 0.12, 0.09);
	
	histo2DNormMinBias->Draw("copy");

	fractionOfNormMinBiasData0005->Draw("pesame");
	fractionOfNormMinBiasData0510->Draw("pesame");
	fractionOfNormMinBiasData1020->Draw("pesame");
	fractionOfNormMinBiasData2040->Draw("pesame");
	fractionOfNormMinBiasData4060->Draw("pesame");
	fractionOfNormMinBiasData6080->Draw("pesame");

	fractionOfNormMinBiasLHC11a10b_bis0005->Draw("pesame");
	fractionOfNormMinBiasLHC11a10b_bis0510->Draw("pesame");
	fractionOfNormMinBiasLHC11a10b_bis1020->Draw("pesame");
	fractionOfNormMinBiasLHC11a10b_bis2040->Draw("pesame");
	fractionOfNormMinBiasLHC11a10b_bis4060->Draw("pesame");
	fractionOfNormMinBiasLHC11a10b_bis6080->Draw("pesame");

	legendDataComb->Draw();
	legendMC->Draw();

	canvasNormMinBiasCombLHC11a10b_bis->SaveAs(Form("%s/FractionOfNormMinBias_WithMCLHC11a10b_bis.%s",outputDir.Data(),suffix.Data()));
	delete canvasNormMinBiasCombLHC11a10b_bis;

   cout << "Plot 23" << endl;
	TCanvas* canvasNGammaEvtLHC13d2 = new TCanvas("canvasNGammaEvtLHC13d2","",200,10,1350,1000);  // gives the page size
	DrawGammaCanvasSettings( canvasNGammaEvtLHC13d2, 0.1, 0.04, 0.12, 0.09);
	canvasNGammaEvtLHC13d2->SetLogy();
	
	histo2DEff->Draw("copy");

	fractionOfGammasData0005->Draw("pesame");
	fractionOfGammasData0510->Draw("pesame");
	fractionOfGammasData1020->Draw("pesame");
	fractionOfGammasData2040->Draw("pesame");
	fractionOfGammasData4060->Draw("pesame");
	fractionOfGammasData6080->Draw("pesame");

	fractionOfGammasLHC13d20005->Draw("pesame");
	fractionOfGammasLHC13d20510->Draw("pesame");
	fractionOfGammasLHC13d21020->Draw("pesame");
	fractionOfGammasLHC13d22040->Draw("pesame");
	fractionOfGammasLHC13d24060->Draw("pesame");
	fractionOfGammasLHC13d26080->Draw("pesame");

	legendDataComb->Draw();
	legendMC->Draw();

	canvasNGammaEvtLHC13d2->SaveAs(Form("%s/FractionOfPhotonsPerEvent_WithMCLHC13d2.%s",outputDir.Data(),suffix.Data()));
	delete canvasNGammaEvtLHC13d2;

   cout << "Plot 24" << endl;
	TCanvas* canvasGoodEventsCombLHC13d2 = new TCanvas("canvasGoodEventsCombLHC13d2","",200,10,1350,1000);  // gives the page size
	DrawGammaCanvasSettings( canvasGoodEventsCombLHC13d2, 0.1, 0.04, 0.12, 0.09);

	histo2DGoodEvents->Draw("copy");
	
	fractionOfGoodEventsData0005->Draw("pesame");
	fractionOfGoodEventsData0510->Draw("pesame");
	fractionOfGoodEventsData1020->Draw("pesame");
	fractionOfGoodEventsData2040->Draw("pesame");
	fractionOfGoodEventsData4060->Draw("pesame");
	fractionOfGoodEventsData6080->Draw("pesame");

	fractionOfGoodEventsLHC13d20005->Draw("pesame");
	fractionOfGoodEventsLHC13d20510->Draw("pesame");
	fractionOfGoodEventsLHC13d21020->Draw("pesame");
	fractionOfGoodEventsLHC13d22040->Draw("pesame");
	fractionOfGoodEventsLHC13d24060->Draw("pesame");
	fractionOfGoodEventsLHC13d26080->Draw("pesame");

	legendDataComb->Draw();
	legendMC->Draw();

	canvasGoodEventsCombLHC13d2->SaveAs(Form("%s/FractionOfGoodEvents_WithMCLHC13d2.%s",outputDir.Data(),suffix.Data()));
	delete canvasGoodEventsCombLHC13d2;

   cout << "Plot 25" << endl;
	TCanvas* canvasNormAllCombLHC13d2 = new TCanvas("canvasNormAllCombLHC13d2","",200,10,1350,1000);  // gives the page size
	DrawGammaCanvasSettings( canvasNormAllCombLHC13d2, 0.1, 0.04, 0.12, 0.09);
	
	histo2DNormAll->Draw("copy");

	fractionOfNormAllData0005->Draw("pesame");
	fractionOfNormAllData0510->Draw("pesame");
	fractionOfNormAllData1020->Draw("pesame");
	fractionOfNormAllData2040->Draw("pesame");
	fractionOfNormAllData4060->Draw("pesame");
	fractionOfNormAllData6080->Draw("pesame");

	fractionOfNormAllLHC13d20005->Draw("pesame");
	fractionOfNormAllLHC13d20510->Draw("pesame");
	fractionOfNormAllLHC13d21020->Draw("pesame");
	fractionOfNormAllLHC13d22040->Draw("pesame");
	fractionOfNormAllLHC13d24060->Draw("pesame");
	fractionOfNormAllLHC13d26080->Draw("pesame");

	legendDataComb->Draw();
	legendMC->Draw();

	canvasNormAllCombLHC13d2->SaveAs(Form("%s/FractionOfNormAll_WithMCLHC13d2.%s",outputDir.Data(),suffix.Data()));
	delete canvasNormAllCombLHC13d2;

   cout << "Plot 26" << endl;
	TCanvas* canvasNormMinBiasCombLHC13d2 = new TCanvas("canvasNormMinBiasCombLHC13d2","",200,10,1350,1000);  // gives the page size
	DrawGammaCanvasSettings( canvasNormMinBiasCombLHC13d2, 0.1, 0.04, 0.12, 0.09);
	
	histo2DNormMinBias->Draw("copy");

	fractionOfNormMinBiasData0005->Draw("pesame");
	fractionOfNormMinBiasData0510->Draw("pesame");
	fractionOfNormMinBiasData1020->Draw("pesame");
	fractionOfNormMinBiasData2040->Draw("pesame");
	fractionOfNormMinBiasData4060->Draw("pesame");
	fractionOfNormMinBiasData6080->Draw("pesame");

	fractionOfNormMinBiasLHC13d20005->Draw("pesame");
	fractionOfNormMinBiasLHC13d20510->Draw("pesame");
	fractionOfNormMinBiasLHC13d21020->Draw("pesame");
	fractionOfNormMinBiasLHC13d22040->Draw("pesame");
	fractionOfNormMinBiasLHC13d24060->Draw("pesame");
	fractionOfNormMinBiasLHC13d26080->Draw("pesame");

	legendDataComb->Draw();
	legendMC->Draw();

	canvasNormMinBiasCombLHC13d2->SaveAs(Form("%s/FractionOfNormMinBias_WithMCLHC13d2.%s",outputDir.Data(),suffix.Data()));
	delete canvasNormMinBiasCombLHC13d2;


	Color_t 	colorPi0900GeV 			= kRed;
	Color_t 	colorPi02760GeV 			= kMagenta+1;
	Color_t	colorPi07TeV				= kBlue;
	Color_t 	colorCommonMCPythia900GeV 	= colorPi0900GeV-4;
	Color_t 	colorCommonMCPythia2760GeV = colorPi02760GeV+2;
	Color_t 	colorCommonMCPythia7TeV 	= colorPi07TeV+3;
	Color_t 	colorCommonMCPhojet900GeV 	= colorPi0900GeV+2;
	Color_t 	colorCommonMCPhojet2760GeV = colorPi02760GeV-4;
	Color_t 	colorCommonMCPhojet7TeV 	= colorPi07TeV-3;

	Style_t 	markerStyleCommmonSpectrum7TeV 	= 20 ;
	Style_t 	markerStyleCommmonSpectrum900GeV = 21 ;
	Style_t 	markerStyleCommmonSpectrum2760GeV = 29 ;
	
	Style_t 	markerStyleCommmonSpectrumMC7TeV 	= 24 ;
	Style_t 	markerStyleCommmonSpectrumMC900GeV 	= 25 ;
	Style_t 	markerStyleCommmonSpectrumMC2760GeV 	= 30 ;
	
	Size_t 	markerSizeCommonSpectrumPi07TeV 	= 1.8;
	Size_t 	markerSizeCommonSpectrumPi0900GeV = 1.8;
	Size_t 	markerSizeCommonSpectrumPi02760GeV 	= 2.2;

	
	DrawGammaSetMarkerTGraphErr( fractionOfGammasLHC10x_900GeV,  markerStyleCommmonSpectrum900GeV, markerSizeCommonSpectrumPi0900GeV, colorPi0900GeV, colorPi0900GeV);
	DrawGammaSetMarkerTGraphErr( fractionOfGammasLHC11a_2760GeV,  markerStyleCommmonSpectrum2760GeV, markerSizeCommonSpectrumPi02760GeV, colorPi02760GeV, colorPi02760GeV);
	DrawGammaSetMarkerTGraphErr( fractionOfGammasLHC10x_7TeV,  markerStyleCommmonSpectrum7TeV, markerSizeCommonSpectrumPi07TeV, colorPi07TeV, colorPi07TeV);
	
	DrawGammaSetMarkerTGraphErr( fractionOfPi0LHC10x_900GeV,  markerStyleCommmonSpectrum900GeV, markerSizeCommonSpectrumPi0900GeV, colorPi0900GeV, colorPi0900GeV);
	DrawGammaSetMarkerTGraphErr( fractionOfPi0LHC11a_2760GeV,  markerStyleCommmonSpectrum2760GeV, markerSizeCommonSpectrumPi02760GeV, colorPi02760GeV, colorPi02760GeV);
	DrawGammaSetMarkerTGraphErr( fractionOfPi0LHC10x_7TeV,  markerStyleCommmonSpectrum7TeV, markerSizeCommonSpectrumPi07TeV, colorPi07TeV, colorPi07TeV);
	
	DrawGammaSetMarkerTGraphErr( fractionOfEtaLHC10x_900GeV,  markerStyleCommmonSpectrum900GeV, markerSizeCommonSpectrumPi0900GeV, colorPi0900GeV, colorPi0900GeV);
	DrawGammaSetMarkerTGraphErr( fractionOfEtaLHC11a_2760GeV,  markerStyleCommmonSpectrum2760GeV, markerSizeCommonSpectrumPi02760GeV, colorPi02760GeV, colorPi02760GeV);
	DrawGammaSetMarkerTGraphErr( fractionOfEtaLHC10x_7TeV,  markerStyleCommmonSpectrum7TeV, markerSizeCommonSpectrumPi07TeV, colorPi07TeV, colorPi07TeV);

	DrawGammaSetMarkerTGraphErr( massPi0LHC10x_900GeV,  markerStyleCommmonSpectrum900GeV, markerSizeCommonSpectrumPi0900GeV, colorPi0900GeV, colorPi0900GeV);
	DrawGammaSetMarkerTGraphErr( massPi0LHC11a_2760GeV,  markerStyleCommmonSpectrum2760GeV, markerSizeCommonSpectrumPi02760GeV, colorPi02760GeV, colorPi02760GeV);
	DrawGammaSetMarkerTGraphErr( massPi0LHC10x_7TeV,  markerStyleCommmonSpectrum7TeV, markerSizeCommonSpectrumPi07TeV, colorPi07TeV, colorPi07TeV);

	DrawGammaSetMarkerTGraphErr( widthPi0LHC10x_900GeV,  markerStyleCommmonSpectrum900GeV, markerSizeCommonSpectrumPi0900GeV, colorPi0900GeV, colorPi0900GeV);
	DrawGammaSetMarkerTGraphErr( widthPi0LHC11a_2760GeV,  markerStyleCommmonSpectrum2760GeV, markerSizeCommonSpectrumPi02760GeV, colorPi02760GeV, colorPi02760GeV);
	DrawGammaSetMarkerTGraphErr( widthPi0LHC10x_7TeV,  markerStyleCommmonSpectrum7TeV, markerSizeCommonSpectrumPi07TeV, colorPi07TeV, colorPi07TeV);

	DrawGammaSetMarkerTGraphErr( massEtaLHC10x_900GeV,  markerStyleCommmonSpectrum900GeV, markerSizeCommonSpectrumPi0900GeV, colorPi0900GeV, colorPi0900GeV);
	DrawGammaSetMarkerTGraphErr( massEtaLHC11a_2760GeV,  markerStyleCommmonSpectrum2760GeV, markerSizeCommonSpectrumPi02760GeV, colorPi02760GeV, colorPi02760GeV);
	DrawGammaSetMarkerTGraphErr( massEtaLHC10x_7TeV,  markerStyleCommmonSpectrum7TeV, markerSizeCommonSpectrumPi07TeV, colorPi07TeV, colorPi07TeV);

	DrawGammaSetMarkerTGraphErr( widthEtaLHC10x_900GeV,  markerStyleCommmonSpectrum900GeV, markerSizeCommonSpectrumPi0900GeV, colorPi0900GeV, colorPi0900GeV);
	DrawGammaSetMarkerTGraphErr( widthEtaLHC11a_2760GeV,  markerStyleCommmonSpectrum2760GeV, markerSizeCommonSpectrumPi02760GeV, colorPi02760GeV, colorPi02760GeV);
	DrawGammaSetMarkerTGraphErr( widthEtaLHC10x_7TeV,  markerStyleCommmonSpectrum7TeV, markerSizeCommonSpectrumPi07TeV, colorPi07TeV, colorPi07TeV);

	DrawGammaSetMarkerTGraphErr( fractionOfWOVtxLHC10x_900GeV,  markerStyleCommmonSpectrum900GeV, markerSizeCommonSpectrumPi0900GeV, colorPi0900GeV, colorPi0900GeV);
	DrawGammaSetMarkerTGraphErr( fractionOfWOVtxLHC11a_2760GeV,  markerStyleCommmonSpectrum2760GeV, markerSizeCommonSpectrumPi02760GeV, colorPi02760GeV, colorPi02760GeV);
	DrawGammaSetMarkerTGraphErr( fractionOfWOVtxLHC10x_7TeV,  markerStyleCommmonSpectrum7TeV, markerSizeCommonSpectrumPi07TeV, colorPi07TeV, colorPi07TeV);

	DrawGammaSetMarkerTGraphErr( fractionOfWVtxOutside10cmLHC10x_900GeV,  markerStyleCommmonSpectrum900GeV, markerSizeCommonSpectrumPi0900GeV, colorPi0900GeV, colorPi0900GeV);
	DrawGammaSetMarkerTGraphErr( fractionOfWVtxOutside10cmLHC11a_2760GeV,  markerStyleCommmonSpectrum2760GeV, markerSizeCommonSpectrumPi02760GeV, colorPi02760GeV, colorPi02760GeV);
	DrawGammaSetMarkerTGraphErr( fractionOfWVtxOutside10cmLHC10x_7TeV,  markerStyleCommmonSpectrum7TeV, markerSizeCommonSpectrumPi07TeV, colorPi07TeV, colorPi07TeV);

	DrawGammaSetMarkerTGraphErr( fractionOfGoodEventsLHC10x_900GeV,  markerStyleCommmonSpectrum900GeV, markerSizeCommonSpectrumPi0900GeV, colorPi0900GeV, colorPi0900GeV);
	DrawGammaSetMarkerTGraphErr( fractionOfGoodEventsLHC11a_2760GeV,  markerStyleCommmonSpectrum2760GeV, markerSizeCommonSpectrumPi02760GeV, colorPi02760GeV, colorPi02760GeV);
	DrawGammaSetMarkerTGraphErr( fractionOfGoodEventsLHC10x_7TeV,  markerStyleCommmonSpectrum7TeV, markerSizeCommonSpectrumPi07TeV, colorPi07TeV, colorPi07TeV);

	DrawGammaSetMarkerTGraphErr( fractionOfNormAllLHC10x_900GeV,  markerStyleCommmonSpectrum900GeV, markerSizeCommonSpectrumPi0900GeV, colorPi0900GeV, colorPi0900GeV);
	DrawGammaSetMarkerTGraphErr( fractionOfNormAllLHC11a_2760GeV,  markerStyleCommmonSpectrum2760GeV, markerSizeCommonSpectrumPi02760GeV, colorPi02760GeV, colorPi02760GeV);
	DrawGammaSetMarkerTGraphErr( fractionOfNormAllLHC10x_7TeV,  markerStyleCommmonSpectrum7TeV, markerSizeCommonSpectrumPi07TeV, colorPi07TeV, colorPi07TeV);

	DrawGammaSetMarkerTGraphErr( fractionOfNormMinBiasLHC10x_900GeV,  markerStyleCommmonSpectrum900GeV, markerSizeCommonSpectrumPi0900GeV, colorPi0900GeV, colorPi0900GeV);
	DrawGammaSetMarkerTGraphErr( fractionOfNormMinBiasLHC11a_2760GeV,  markerStyleCommmonSpectrum2760GeV, markerSizeCommonSpectrumPi02760GeV, colorPi02760GeV, colorPi02760GeV);
	DrawGammaSetMarkerTGraphErr( fractionOfNormMinBiasLHC10x_7TeV,  markerStyleCommmonSpectrum7TeV, markerSizeCommonSpectrumPi07TeV, colorPi07TeV, colorPi07TeV);

	DrawGammaSetMarkerTGraphErr( fractionOfPileUpLHC10x_900GeV,  markerStyleCommmonSpectrum900GeV, markerSizeCommonSpectrumPi0900GeV, colorPi0900GeV, colorPi0900GeV);
	DrawGammaSetMarkerTGraphErr( fractionOfPileUpLHC11a_2760GeV,  markerStyleCommmonSpectrum2760GeV, markerSizeCommonSpectrumPi02760GeV, colorPi02760GeV, colorPi02760GeV);
	DrawGammaSetMarkerTGraphErr( fractionOfPileUpLHC10x_7TeV,  markerStyleCommmonSpectrum7TeV, markerSizeCommonSpectrumPi07TeV, colorPi07TeV, colorPi07TeV);

	
	DrawGammaSetMarkerTGraphErr( fractionOfGammasLHC10e12_900GeV,  markerStyleCommmonSpectrumMC900GeV, markerSizeCommonSpectrumPi0900GeV, colorCommonMCPhojet900GeV, colorCommonMCPhojet900GeV);
	DrawGammaSetMarkerTGraphErr( fractionOfPi0LHC10e12_900GeV,  markerStyleCommmonSpectrumMC900GeV, markerSizeCommonSpectrumPi0900GeV, colorCommonMCPhojet900GeV, colorCommonMCPhojet900GeV);
	DrawGammaSetMarkerTGraphErr( fractionOfEtaLHC10e12_900GeV,  markerStyleCommmonSpectrumMC900GeV, markerSizeCommonSpectrumPi0900GeV, colorCommonMCPhojet900GeV, colorCommonMCPhojet900GeV);
	DrawGammaSetMarkerTGraphErr( fractionOfWOVtxLHC10e12_900GeV,  markerStyleCommmonSpectrumMC900GeV, markerSizeCommonSpectrumPi0900GeV, colorCommonMCPhojet900GeV, colorCommonMCPhojet900GeV);
	DrawGammaSetMarkerTGraphErr( fractionOfWVtxOutside10cmLHC10e12_900GeV,  markerStyleCommmonSpectrumMC900GeV, markerSizeCommonSpectrumPi0900GeV, colorCommonMCPhojet900GeV, colorCommonMCPhojet900GeV);
	DrawGammaSetMarkerTGraphErr( fractionOfGoodEventsLHC10e12_900GeV,  markerStyleCommmonSpectrumMC900GeV, markerSizeCommonSpectrumPi0900GeV, colorCommonMCPhojet900GeV, colorCommonMCPhojet900GeV);
	DrawGammaSetMarkerTGraphErr( fractionOfNormAllLHC10e12_900GeV,  markerStyleCommmonSpectrumMC900GeV, markerSizeCommonSpectrumPi0900GeV, colorCommonMCPhojet900GeV, colorCommonMCPhojet900GeV);
	DrawGammaSetMarkerTGraphErr( fractionOfNormMinBiasLHC10e12_900GeV,  markerStyleCommmonSpectrumMC900GeV, markerSizeCommonSpectrumPi0900GeV, colorCommonMCPhojet900GeV, colorCommonMCPhojet900GeV);
	DrawGammaSetMarkerTGraphErr( fractionOfPileUpLHC10e12_900GeV,  markerStyleCommmonSpectrumMC900GeV, markerSizeCommonSpectrumPi0900GeV, colorCommonMCPhojet900GeV, colorCommonMCPhojet900GeV);
	DrawGammaSetMarkerTGraphErr( massPi0LHC10e12_900GeV,  markerStyleCommmonSpectrumMC900GeV, markerSizeCommonSpectrumPi0900GeV, colorCommonMCPhojet900GeV, colorCommonMCPhojet900GeV);
	DrawGammaSetMarkerTGraphErr( widthPi0LHC10e12_900GeV,  markerStyleCommmonSpectrumMC900GeV, markerSizeCommonSpectrumPi0900GeV, colorCommonMCPhojet900GeV, colorCommonMCPhojet900GeV);
	DrawGammaSetMarkerTGraphErr( massEtaLHC10e13_900GeV,  markerStyleCommmonSpectrumMC900GeV, markerSizeCommonSpectrumPi0900GeV, colorCommonMCPhojet900GeV, colorCommonMCPhojet900GeV);
	DrawGammaSetMarkerTGraphErr( widthEtaLHC10e12_900GeV,  markerStyleCommmonSpectrumMC900GeV, markerSizeCommonSpectrumPi0900GeV, colorCommonMCPhojet900GeV, colorCommonMCPhojet900GeV);
	
	DrawGammaSetMarkerTGraphErr( fractionOfGammasLHC10e13_900GeV,  markerStyleCommmonSpectrumMC900GeV, markerSizeCommonSpectrumPi0900GeV, colorCommonMCPythia900GeV, colorCommonMCPythia900GeV);
	DrawGammaSetMarkerTGraphErr( fractionOfPi0LHC10e13_900GeV,  markerStyleCommmonSpectrumMC900GeV, markerSizeCommonSpectrumPi0900GeV, colorCommonMCPythia900GeV, colorCommonMCPythia900GeV);
	DrawGammaSetMarkerTGraphErr( fractionOfEtaLHC10e13_900GeV,  markerStyleCommmonSpectrumMC900GeV, markerSizeCommonSpectrumPi0900GeV, colorCommonMCPythia900GeV, colorCommonMCPythia900GeV);
	DrawGammaSetMarkerTGraphErr( fractionOfWOVtxLHC10e13_900GeV,  markerStyleCommmonSpectrumMC900GeV, markerSizeCommonSpectrumPi0900GeV, colorCommonMCPythia900GeV, colorCommonMCPythia900GeV);
	DrawGammaSetMarkerTGraphErr( fractionOfWVtxOutside10cmLHC10e13_900GeV,  markerStyleCommmonSpectrumMC900GeV, markerSizeCommonSpectrumPi0900GeV, colorCommonMCPythia900GeV, colorCommonMCPythia900GeV);
	DrawGammaSetMarkerTGraphErr( fractionOfGoodEventsLHC10e13_900GeV,  markerStyleCommmonSpectrumMC900GeV, markerSizeCommonSpectrumPi0900GeV, colorCommonMCPythia900GeV, colorCommonMCPythia900GeV);
	DrawGammaSetMarkerTGraphErr( fractionOfNormAllLHC10e13_900GeV,  markerStyleCommmonSpectrumMC900GeV, markerSizeCommonSpectrumPi0900GeV, colorCommonMCPythia900GeV, colorCommonMCPythia900GeV);
	DrawGammaSetMarkerTGraphErr( fractionOfNormMinBiasLHC10e13_900GeV,  markerStyleCommmonSpectrumMC900GeV, markerSizeCommonSpectrumPi0900GeV, colorCommonMCPythia900GeV, colorCommonMCPythia900GeV);
	DrawGammaSetMarkerTGraphErr( fractionOfPileUpLHC10e13_900GeV,  markerStyleCommmonSpectrumMC900GeV, markerSizeCommonSpectrumPi0900GeV, colorCommonMCPythia900GeV, colorCommonMCPythia900GeV);
	DrawGammaSetMarkerTGraphErr( massPi0LHC10e13_900GeV,  markerStyleCommmonSpectrumMC900GeV, markerSizeCommonSpectrumPi0900GeV, colorCommonMCPythia900GeV, colorCommonMCPythia900GeV);
	DrawGammaSetMarkerTGraphErr( widthPi0LHC10e13_900GeV,  markerStyleCommmonSpectrumMC900GeV, markerSizeCommonSpectrumPi0900GeV, colorCommonMCPythia900GeV, colorCommonMCPythia900GeV);
	DrawGammaSetMarkerTGraphErr( massEtaLHC10e13_900GeV,  markerStyleCommmonSpectrumMC900GeV, markerSizeCommonSpectrumPi0900GeV, colorCommonMCPythia900GeV, colorCommonMCPythia900GeV);
	DrawGammaSetMarkerTGraphErr( widthEtaLHC10e13_900GeV,  markerStyleCommmonSpectrumMC900GeV, markerSizeCommonSpectrumPi0900GeV, colorCommonMCPythia900GeV, colorCommonMCPythia900GeV);
	
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
	
	DrawGammaSetMarkerTGraphErr( fractionOfGammasLHC10e20_7TeV,  markerStyleCommmonSpectrumMC7TeV, markerSizeCommonSpectrumPi07TeV, colorCommonMCPythia7TeV, colorCommonMCPythia7TeV);
	DrawGammaSetMarkerTGraphErr( fractionOfPi0LHC10e20_7TeV,  markerStyleCommmonSpectrumMC7TeV, markerSizeCommonSpectrumPi07TeV, colorCommonMCPythia7TeV, colorCommonMCPythia7TeV);
	DrawGammaSetMarkerTGraphErr( fractionOfEtaLHC10e20_7TeV,  markerStyleCommmonSpectrumMC7TeV, markerSizeCommonSpectrumPi07TeV, colorCommonMCPythia7TeV, colorCommonMCPythia7TeV);
	DrawGammaSetMarkerTGraphErr( fractionOfWOVtxLHC10e20_7TeV,  markerStyleCommmonSpectrumMC7TeV, markerSizeCommonSpectrumPi07TeV, colorCommonMCPythia7TeV, colorCommonMCPythia7TeV);
	DrawGammaSetMarkerTGraphErr( fractionOfWVtxOutside10cmLHC10e20_7TeV,  markerStyleCommmonSpectrumMC7TeV, markerSizeCommonSpectrumPi07TeV, colorCommonMCPythia7TeV, colorCommonMCPythia7TeV);
	DrawGammaSetMarkerTGraphErr( fractionOfGoodEventsLHC10e20_7TeV,  markerStyleCommmonSpectrumMC7TeV, markerSizeCommonSpectrumPi07TeV, colorCommonMCPythia7TeV, colorCommonMCPythia7TeV);
	DrawGammaSetMarkerTGraphErr( fractionOfNormAllLHC10e20_7TeV,  markerStyleCommmonSpectrumMC7TeV, markerSizeCommonSpectrumPi07TeV, colorCommonMCPythia7TeV, colorCommonMCPythia7TeV);
	DrawGammaSetMarkerTGraphErr( fractionOfNormMinBiasLHC10e20_7TeV,  markerStyleCommmonSpectrumMC7TeV, markerSizeCommonSpectrumPi07TeV, colorCommonMCPythia7TeV, colorCommonMCPythia7TeV);
	DrawGammaSetMarkerTGraphErr( fractionOfPileUpLHC10e20_7TeV,  markerStyleCommmonSpectrumMC7TeV, markerSizeCommonSpectrumPi07TeV, colorCommonMCPythia7TeV, colorCommonMCPythia7TeV);
	DrawGammaSetMarkerTGraphErr( massPi0LHC10e20_7TeV,  markerStyleCommmonSpectrumMC7TeV, markerSizeCommonSpectrumPi07TeV, colorCommonMCPythia7TeV, colorCommonMCPythia7TeV);
	DrawGammaSetMarkerTGraphErr( widthPi0LHC10e20_7TeV,  markerStyleCommmonSpectrumMC7TeV, markerSizeCommonSpectrumPi07TeV, colorCommonMCPythia7TeV, colorCommonMCPythia7TeV);
	DrawGammaSetMarkerTGraphErr( massEtaLHC10e20_7TeV,  markerStyleCommmonSpectrumMC7TeV, markerSizeCommonSpectrumPi07TeV, colorCommonMCPythia7TeV, colorCommonMCPythia7TeV);
	DrawGammaSetMarkerTGraphErr( widthEtaLHC10e20_7TeV,  markerStyleCommmonSpectrumMC7TeV, markerSizeCommonSpectrumPi07TeV, colorCommonMCPythia7TeV, colorCommonMCPythia7TeV);
	
	DrawGammaSetMarkerTGraphErr( fractionOfGammasLHC10e21_7TeV,  markerStyleCommmonSpectrumMC7TeV, markerSizeCommonSpectrumPi07TeV, colorCommonMCPhojet7TeV, colorCommonMCPhojet7TeV);
	DrawGammaSetMarkerTGraphErr( fractionOfEtaLHC10e21_7TeV,  markerStyleCommmonSpectrumMC7TeV, markerSizeCommonSpectrumPi07TeV, colorCommonMCPhojet7TeV, colorCommonMCPhojet7TeV);
	DrawGammaSetMarkerTGraphErr( fractionOfPi0LHC10e21_7TeV,  markerStyleCommmonSpectrumMC7TeV, markerSizeCommonSpectrumPi07TeV, colorCommonMCPhojet7TeV, colorCommonMCPhojet7TeV);
	DrawGammaSetMarkerTGraphErr( fractionOfWOVtxLHC10e21_7TeV,  markerStyleCommmonSpectrumMC7TeV, markerSizeCommonSpectrumPi07TeV, colorCommonMCPhojet7TeV, colorCommonMCPhojet7TeV);
	DrawGammaSetMarkerTGraphErr( fractionOfWVtxOutside10cmLHC10e21_7TeV,  markerStyleCommmonSpectrumMC7TeV, markerSizeCommonSpectrumPi07TeV, colorCommonMCPhojet7TeV, colorCommonMCPhojet7TeV);
	DrawGammaSetMarkerTGraphErr( fractionOfGoodEventsLHC10e21_7TeV,  markerStyleCommmonSpectrumMC7TeV, markerSizeCommonSpectrumPi07TeV, colorCommonMCPhojet7TeV, colorCommonMCPhojet7TeV);
	DrawGammaSetMarkerTGraphErr( fractionOfNormAllLHC10e21_7TeV,  markerStyleCommmonSpectrumMC7TeV, markerSizeCommonSpectrumPi07TeV, colorCommonMCPhojet7TeV, colorCommonMCPhojet7TeV);
	DrawGammaSetMarkerTGraphErr( fractionOfNormMinBiasLHC10e21_7TeV,  markerStyleCommmonSpectrumMC7TeV, markerSizeCommonSpectrumPi07TeV, colorCommonMCPhojet7TeV, colorCommonMCPhojet7TeV);
	DrawGammaSetMarkerTGraphErr( fractionOfPileUpLHC10e21_7TeV,  markerStyleCommmonSpectrumMC7TeV, markerSizeCommonSpectrumPi07TeV, colorCommonMCPhojet7TeV, colorCommonMCPhojet7TeV);
	DrawGammaSetMarkerTGraphErr( massPi0LHC10e21_7TeV,  markerStyleCommmonSpectrumMC7TeV, markerSizeCommonSpectrumPi07TeV, colorCommonMCPhojet7TeV, colorCommonMCPhojet7TeV);
	DrawGammaSetMarkerTGraphErr( widthPi0LHC10e21_7TeV,  markerStyleCommmonSpectrumMC7TeV, markerSizeCommonSpectrumPi07TeV, colorCommonMCPhojet7TeV, colorCommonMCPhojet7TeV);
	DrawGammaSetMarkerTGraphErr( massEtaLHC10e21_7TeV,  markerStyleCommmonSpectrumMC7TeV, markerSizeCommonSpectrumPi07TeV, colorCommonMCPhojet7TeV, colorCommonMCPhojet7TeV);
	DrawGammaSetMarkerTGraphErr( widthEtaLHC10e21_7TeV,  markerStyleCommmonSpectrumMC7TeV, markerSizeCommonSpectrumPi07TeV, colorCommonMCPhojet7TeV, colorCommonMCPhojet7TeV);

	DrawGammaSetMarkerTGraphErr( fractionOfGammasLHC10f6a_7TeV,  markerStyleCommmonSpectrumMC7TeV, markerSizeCommonSpectrumPi07TeV, colorCommonMCPythia7TeV, colorCommonMCPythia7TeV);
	DrawGammaSetMarkerTGraphErr( fractionOfEtaLHC10f6a_7TeV,  markerStyleCommmonSpectrumMC7TeV, markerSizeCommonSpectrumPi07TeV, colorCommonMCPythia7TeV, colorCommonMCPythia7TeV);
	DrawGammaSetMarkerTGraphErr( fractionOfPi0LHC10f6a_7TeV,  markerStyleCommmonSpectrumMC7TeV, markerSizeCommonSpectrumPi07TeV, colorCommonMCPythia7TeV, colorCommonMCPythia7TeV);
	DrawGammaSetMarkerTGraphErr( fractionOfWOVtxLHC10f6a_7TeV,  markerStyleCommmonSpectrumMC7TeV, markerSizeCommonSpectrumPi07TeV, colorCommonMCPythia7TeV, colorCommonMCPythia7TeV);
	DrawGammaSetMarkerTGraphErr( fractionOfWVtxOutside10cmLHC10f6a_7TeV,  markerStyleCommmonSpectrumMC7TeV, markerSizeCommonSpectrumPi07TeV, colorCommonMCPythia7TeV, colorCommonMCPythia7TeV);
	DrawGammaSetMarkerTGraphErr( fractionOfGoodEventsLHC10f6a_7TeV,  markerStyleCommmonSpectrumMC7TeV, markerSizeCommonSpectrumPi07TeV, colorCommonMCPythia7TeV, colorCommonMCPythia7TeV);
	DrawGammaSetMarkerTGraphErr( fractionOfNormAllLHC10f6a_7TeV,  markerStyleCommmonSpectrumMC7TeV, markerSizeCommonSpectrumPi07TeV, colorCommonMCPythia7TeV, colorCommonMCPythia7TeV);
	DrawGammaSetMarkerTGraphErr( fractionOfNormMinBiasLHC10f6a_7TeV,  markerStyleCommmonSpectrumMC7TeV, markerSizeCommonSpectrumPi07TeV, colorCommonMCPythia7TeV, colorCommonMCPythia7TeV);
	DrawGammaSetMarkerTGraphErr( fractionOfPileUpLHC10f6a_7TeV,  markerStyleCommmonSpectrumMC7TeV, markerSizeCommonSpectrumPi07TeV, colorCommonMCPythia7TeV, colorCommonMCPythia7TeV);
	DrawGammaSetMarkerTGraphErr( massPi0LHC10f6a_7TeV,  markerStyleCommmonSpectrumMC7TeV, markerSizeCommonSpectrumPi07TeV, colorCommonMCPythia7TeV, colorCommonMCPythia7TeV);
	DrawGammaSetMarkerTGraphErr( widthPi0LHC10f6a_7TeV,  markerStyleCommmonSpectrumMC7TeV, markerSizeCommonSpectrumPi07TeV, colorCommonMCPythia7TeV, colorCommonMCPythia7TeV);
	DrawGammaSetMarkerTGraphErr( massEtaLHC10f6a_7TeV,  markerStyleCommmonSpectrumMC7TeV, markerSizeCommonSpectrumPi07TeV, colorCommonMCPythia7TeV, colorCommonMCPythia7TeV);
	DrawGammaSetMarkerTGraphErr( widthEtaLHC10f6a_7TeV,  markerStyleCommmonSpectrumMC7TeV, markerSizeCommonSpectrumPi07TeV, colorCommonMCPythia7TeV, colorCommonMCPythia7TeV);

	DrawGammaSetMarkerTGraphErr( fractionOfGammasLHC10f6_7TeV,  markerStyleCommmonSpectrumMC7TeV, markerSizeCommonSpectrumPi07TeV, colorCommonMCPhojet7TeV, colorCommonMCPhojet7TeV);
	DrawGammaSetMarkerTGraphErr( fractionOfEtaLHC10f6_7TeV,  markerStyleCommmonSpectrumMC7TeV, markerSizeCommonSpectrumPi07TeV, colorCommonMCPhojet7TeV, colorCommonMCPhojet7TeV);
	DrawGammaSetMarkerTGraphErr( fractionOfPi0LHC10f6_7TeV,  markerStyleCommmonSpectrumMC7TeV, markerSizeCommonSpectrumPi07TeV, colorCommonMCPhojet7TeV, colorCommonMCPhojet7TeV);
	DrawGammaSetMarkerTGraphErr( fractionOfWOVtxLHC10f6_7TeV,  markerStyleCommmonSpectrumMC7TeV, markerSizeCommonSpectrumPi07TeV, colorCommonMCPhojet7TeV, colorCommonMCPhojet7TeV);
	DrawGammaSetMarkerTGraphErr( fractionOfWVtxOutside10cmLHC10f6_7TeV,  markerStyleCommmonSpectrumMC7TeV, markerSizeCommonSpectrumPi07TeV, colorCommonMCPhojet7TeV, colorCommonMCPhojet7TeV);
	DrawGammaSetMarkerTGraphErr( fractionOfGoodEventsLHC10f6_7TeV,  markerStyleCommmonSpectrumMC7TeV, markerSizeCommonSpectrumPi07TeV, colorCommonMCPhojet7TeV, colorCommonMCPhojet7TeV);
	DrawGammaSetMarkerTGraphErr( fractionOfNormAllLHC10f6_7TeV,  markerStyleCommmonSpectrumMC7TeV, markerSizeCommonSpectrumPi07TeV, colorCommonMCPhojet7TeV, colorCommonMCPhojet7TeV);
	DrawGammaSetMarkerTGraphErr( fractionOfNormMinBiasLHC10f6_7TeV,  markerStyleCommmonSpectrumMC7TeV, markerSizeCommonSpectrumPi07TeV, colorCommonMCPhojet7TeV, colorCommonMCPhojet7TeV);
	DrawGammaSetMarkerTGraphErr( fractionOfPileUpLHC10f6_7TeV,  markerStyleCommmonSpectrumMC7TeV, markerSizeCommonSpectrumPi07TeV, colorCommonMCPhojet7TeV,
	colorCommonMCPhojet7TeV);
	DrawGammaSetMarkerTGraphErr( massPi0LHC10f6_7TeV,  markerStyleCommmonSpectrumMC7TeV, markerSizeCommonSpectrumPi07TeV, colorCommonMCPhojet7TeV,
		colorCommonMCPhojet7TeV);
	DrawGammaSetMarkerTGraphErr( widthPi0LHC10f6_7TeV,  markerStyleCommmonSpectrumMC7TeV, markerSizeCommonSpectrumPi07TeV, colorCommonMCPhojet7TeV,
		colorCommonMCPhojet7TeV);
	DrawGammaSetMarkerTGraphErr( massEtaLHC10f6_7TeV,  markerStyleCommmonSpectrumMC7TeV, markerSizeCommonSpectrumPi07TeV, colorCommonMCPhojet7TeV,
		colorCommonMCPhojet7TeV);
	DrawGammaSetMarkerTGraphErr( widthEtaLHC10f6_7TeV,  markerStyleCommmonSpectrumMC7TeV, markerSizeCommonSpectrumPi07TeV, colorCommonMCPhojet7TeV,
		colorCommonMCPhojet7TeV);

	DrawGammaSetMarkerTGraphErr( fractionOfGammasLHC10d1_7TeV,  markerStyleCommmonSpectrumMC7TeV, markerSizeCommonSpectrumPi07TeV, colorCommonMCPythia7TeV, colorCommonMCPythia7TeV);
	DrawGammaSetMarkerTGraphErr( fractionOfEtaLHC10d1_7TeV,  markerStyleCommmonSpectrumMC7TeV, markerSizeCommonSpectrumPi07TeV, colorCommonMCPythia7TeV, colorCommonMCPythia7TeV);
	DrawGammaSetMarkerTGraphErr( fractionOfPi0LHC10d1_7TeV,  markerStyleCommmonSpectrumMC7TeV, markerSizeCommonSpectrumPi07TeV, colorCommonMCPythia7TeV, colorCommonMCPythia7TeV);
	DrawGammaSetMarkerTGraphErr( fractionOfWOVtxLHC10d1_7TeV,  markerStyleCommmonSpectrumMC7TeV, markerSizeCommonSpectrumPi07TeV, colorCommonMCPythia7TeV, colorCommonMCPythia7TeV);
	DrawGammaSetMarkerTGraphErr( fractionOfWVtxOutside10cmLHC10d1_7TeV,  markerStyleCommmonSpectrumMC7TeV, markerSizeCommonSpectrumPi07TeV, colorCommonMCPythia7TeV, colorCommonMCPythia7TeV);
	DrawGammaSetMarkerTGraphErr( fractionOfGoodEventsLHC10d1_7TeV,  markerStyleCommmonSpectrumMC7TeV, markerSizeCommonSpectrumPi07TeV, colorCommonMCPythia7TeV, colorCommonMCPythia7TeV);
	DrawGammaSetMarkerTGraphErr( fractionOfNormAllLHC10d1_7TeV,  markerStyleCommmonSpectrumMC7TeV, markerSizeCommonSpectrumPi07TeV, colorCommonMCPythia7TeV, colorCommonMCPythia7TeV);
	DrawGammaSetMarkerTGraphErr( fractionOfNormMinBiasLHC10d1_7TeV,  markerStyleCommmonSpectrumMC7TeV, markerSizeCommonSpectrumPi07TeV, colorCommonMCPythia7TeV, colorCommonMCPythia7TeV);
	DrawGammaSetMarkerTGraphErr( fractionOfPileUpLHC10d1_7TeV,  markerStyleCommmonSpectrumMC7TeV, markerSizeCommonSpectrumPi07TeV, colorCommonMCPythia7TeV, colorCommonMCPythia7TeV);
	DrawGammaSetMarkerTGraphErr( massPi0LHC10d1_7TeV,  markerStyleCommmonSpectrumMC7TeV, markerSizeCommonSpectrumPi07TeV, colorCommonMCPythia7TeV, colorCommonMCPythia7TeV);
	DrawGammaSetMarkerTGraphErr( widthPi0LHC10d1_7TeV,  markerStyleCommmonSpectrumMC7TeV, markerSizeCommonSpectrumPi07TeV, colorCommonMCPythia7TeV, colorCommonMCPythia7TeV);
	DrawGammaSetMarkerTGraphErr( massEtaLHC10d1_7TeV,  markerStyleCommmonSpectrumMC7TeV, markerSizeCommonSpectrumPi07TeV, colorCommonMCPythia7TeV, colorCommonMCPythia7TeV);
	DrawGammaSetMarkerTGraphErr( widthEtaLHC10d1_7TeV,  markerStyleCommmonSpectrumMC7TeV, markerSizeCommonSpectrumPi07TeV, colorCommonMCPythia7TeV, colorCommonMCPythia7TeV);

	DrawGammaSetMarkerTGraphErr( fractionOfGammasLHC10d2_7TeV,  markerStyleCommmonSpectrumMC7TeV, markerSizeCommonSpectrumPi07TeV, colorCommonMCPhojet7TeV, colorCommonMCPhojet7TeV);
	DrawGammaSetMarkerTGraphErr( fractionOfEtaLHC10d2_7TeV,  markerStyleCommmonSpectrumMC7TeV, markerSizeCommonSpectrumPi07TeV, colorCommonMCPhojet7TeV, colorCommonMCPhojet7TeV);
	DrawGammaSetMarkerTGraphErr( fractionOfPi0LHC10d2_7TeV,  markerStyleCommmonSpectrumMC7TeV, markerSizeCommonSpectrumPi07TeV, colorCommonMCPhojet7TeV, colorCommonMCPhojet7TeV);
	DrawGammaSetMarkerTGraphErr( fractionOfWOVtxLHC10d2_7TeV,  markerStyleCommmonSpectrumMC7TeV, markerSizeCommonSpectrumPi07TeV, colorCommonMCPhojet7TeV, colorCommonMCPhojet7TeV);
	DrawGammaSetMarkerTGraphErr( fractionOfWVtxOutside10cmLHC10d2_7TeV,  markerStyleCommmonSpectrumMC7TeV, markerSizeCommonSpectrumPi07TeV, colorCommonMCPhojet7TeV, colorCommonMCPhojet7TeV);
	DrawGammaSetMarkerTGraphErr( fractionOfGoodEventsLHC10d2_7TeV,  markerStyleCommmonSpectrumMC7TeV, markerSizeCommonSpectrumPi07TeV, colorCommonMCPhojet7TeV, colorCommonMCPhojet7TeV);
	DrawGammaSetMarkerTGraphErr( fractionOfNormAllLHC10d2_7TeV,  markerStyleCommmonSpectrumMC7TeV, markerSizeCommonSpectrumPi07TeV, colorCommonMCPhojet7TeV, colorCommonMCPhojet7TeV);
	DrawGammaSetMarkerTGraphErr( fractionOfNormMinBiasLHC10d2_7TeV,  markerStyleCommmonSpectrumMC7TeV, markerSizeCommonSpectrumPi07TeV, colorCommonMCPhojet7TeV, colorCommonMCPhojet7TeV);
	DrawGammaSetMarkerTGraphErr( fractionOfPileUpLHC10d2_7TeV,  markerStyleCommmonSpectrumMC7TeV, markerSizeCommonSpectrumPi07TeV, colorCommonMCPhojet7TeV, colorCommonMCPhojet7TeV);
	DrawGammaSetMarkerTGraphErr( massPi0LHC10d2_7TeV,  markerStyleCommmonSpectrumMC7TeV, markerSizeCommonSpectrumPi07TeV, colorCommonMCPhojet7TeV, colorCommonMCPhojet7TeV);
	DrawGammaSetMarkerTGraphErr( widthPi0LHC10d2_7TeV,  markerStyleCommmonSpectrumMC7TeV, markerSizeCommonSpectrumPi07TeV, colorCommonMCPhojet7TeV, colorCommonMCPhojet7TeV);
	DrawGammaSetMarkerTGraphErr( massEtaLHC10d2_7TeV,  markerStyleCommmonSpectrumMC7TeV, markerSizeCommonSpectrumPi07TeV, colorCommonMCPhojet7TeV, colorCommonMCPhojet7TeV);
	DrawGammaSetMarkerTGraphErr( widthEtaLHC10d2_7TeV,  markerStyleCommmonSpectrumMC7TeV, markerSizeCommonSpectrumPi07TeV, colorCommonMCPhojet7TeV, colorCommonMCPhojet7TeV);

	DrawGammaSetMarkerTGraphErr( fractionOfGammasLHC10d4a_7TeV,  markerStyleCommmonSpectrumMC7TeV, markerSizeCommonSpectrumPi07TeV, colorCommonMCPhojet7TeV, colorCommonMCPhojet7TeV);
	DrawGammaSetMarkerTGraphErr( fractionOfEtaLHC10d4a_7TeV,  markerStyleCommmonSpectrumMC7TeV, markerSizeCommonSpectrumPi07TeV, colorCommonMCPhojet7TeV, colorCommonMCPhojet7TeV);
	DrawGammaSetMarkerTGraphErr( fractionOfPi0LHC10d4a_7TeV,  markerStyleCommmonSpectrumMC7TeV, markerSizeCommonSpectrumPi07TeV, colorCommonMCPhojet7TeV, colorCommonMCPhojet7TeV);
	DrawGammaSetMarkerTGraphErr( fractionOfWOVtxLHC10d4a_7TeV,  markerStyleCommmonSpectrumMC7TeV, markerSizeCommonSpectrumPi07TeV, colorCommonMCPhojet7TeV, colorCommonMCPhojet7TeV);
	DrawGammaSetMarkerTGraphErr( fractionOfWVtxOutside10cmLHC10d4a_7TeV,  markerStyleCommmonSpectrumMC7TeV, markerSizeCommonSpectrumPi07TeV, colorCommonMCPhojet7TeV, colorCommonMCPhojet7TeV);
	DrawGammaSetMarkerTGraphErr( fractionOfGoodEventsLHC10d4a_7TeV,  markerStyleCommmonSpectrumMC7TeV, markerSizeCommonSpectrumPi07TeV, colorCommonMCPhojet7TeV, colorCommonMCPhojet7TeV);
	DrawGammaSetMarkerTGraphErr( fractionOfNormAllLHC10d4a_7TeV,  markerStyleCommmonSpectrumMC7TeV, markerSizeCommonSpectrumPi07TeV, colorCommonMCPhojet7TeV, colorCommonMCPhojet7TeV);
	DrawGammaSetMarkerTGraphErr( fractionOfNormMinBiasLHC10d4a_7TeV,  markerStyleCommmonSpectrumMC7TeV, markerSizeCommonSpectrumPi07TeV, colorCommonMCPhojet7TeV, colorCommonMCPhojet7TeV);
	DrawGammaSetMarkerTGraphErr( fractionOfPileUpLHC10d4a_7TeV,  markerStyleCommmonSpectrumMC7TeV, markerSizeCommonSpectrumPi07TeV, colorCommonMCPhojet7TeV, colorCommonMCPhojet7TeV);
	DrawGammaSetMarkerTGraphErr( massPi0LHC10d4a_7TeV,  markerStyleCommmonSpectrumMC7TeV, markerSizeCommonSpectrumPi07TeV, colorCommonMCPhojet7TeV, colorCommonMCPhojet7TeV);
	DrawGammaSetMarkerTGraphErr( massEtaLHC10d4a_7TeV,  markerStyleCommmonSpectrumMC7TeV, markerSizeCommonSpectrumPi07TeV, colorCommonMCPhojet7TeV, colorCommonMCPhojet7TeV);
	DrawGammaSetMarkerTGraphErr( widthPi0LHC10d4a_7TeV,  markerStyleCommmonSpectrumMC7TeV, markerSizeCommonSpectrumPi07TeV, colorCommonMCPhojet7TeV, colorCommonMCPhojet7TeV);
	DrawGammaSetMarkerTGraphErr( widthEtaLHC10d4a_7TeV,  markerStyleCommmonSpectrumMC7TeV, markerSizeCommonSpectrumPi07TeV, colorCommonMCPhojet7TeV, colorCommonMCPhojet7TeV);

	DrawGammaSetMarkerTGraphErr( fractionOfGammasLHC10d4_7TeV,  markerStyleCommmonSpectrumMC7TeV, markerSizeCommonSpectrumPi07TeV, colorCommonMCPythia7TeV, colorCommonMCPythia7TeV);
	DrawGammaSetMarkerTGraphErr( fractionOfEtaLHC10d4_7TeV,  markerStyleCommmonSpectrumMC7TeV, markerSizeCommonSpectrumPi07TeV, colorCommonMCPythia7TeV, colorCommonMCPythia7TeV);
	DrawGammaSetMarkerTGraphErr( fractionOfPi0LHC10d4_7TeV,  markerStyleCommmonSpectrumMC7TeV, markerSizeCommonSpectrumPi07TeV, colorCommonMCPythia7TeV, colorCommonMCPythia7TeV);
	DrawGammaSetMarkerTGraphErr( fractionOfWOVtxLHC10d4_7TeV,  markerStyleCommmonSpectrumMC7TeV, markerSizeCommonSpectrumPi07TeV, colorCommonMCPythia7TeV, colorCommonMCPythia7TeV);
	DrawGammaSetMarkerTGraphErr( fractionOfWVtxOutside10cmLHC10d4_7TeV,  markerStyleCommmonSpectrumMC7TeV, markerSizeCommonSpectrumPi07TeV, colorCommonMCPythia7TeV, colorCommonMCPythia7TeV);
	DrawGammaSetMarkerTGraphErr( fractionOfGoodEventsLHC10d4_7TeV,  markerStyleCommmonSpectrumMC7TeV, markerSizeCommonSpectrumPi07TeV, colorCommonMCPythia7TeV, colorCommonMCPythia7TeV);
	DrawGammaSetMarkerTGraphErr( fractionOfNormAllLHC10d4_7TeV,  markerStyleCommmonSpectrumMC7TeV, markerSizeCommonSpectrumPi07TeV, colorCommonMCPythia7TeV, colorCommonMCPythia7TeV);
	DrawGammaSetMarkerTGraphErr( fractionOfNormMinBiasLHC10d4_7TeV,  markerStyleCommmonSpectrumMC7TeV, markerSizeCommonSpectrumPi07TeV, colorCommonMCPythia7TeV, colorCommonMCPythia7TeV);
	DrawGammaSetMarkerTGraphErr( fractionOfPileUpLHC10d4_7TeV,  markerStyleCommmonSpectrumMC7TeV, markerSizeCommonSpectrumPi07TeV, colorCommonMCPythia7TeV, colorCommonMCPythia7TeV);
	DrawGammaSetMarkerTGraphErr( massPi0LHC10d4_7TeV,  markerStyleCommmonSpectrumMC7TeV, markerSizeCommonSpectrumPi07TeV, colorCommonMCPythia7TeV, colorCommonMCPythia7TeV);
	DrawGammaSetMarkerTGraphErr( massEtaLHC10d4_7TeV,  markerStyleCommmonSpectrumMC7TeV, markerSizeCommonSpectrumPi07TeV, colorCommonMCPythia7TeV, colorCommonMCPythia7TeV);
	DrawGammaSetMarkerTGraphErr( widthPi0LHC10d4_7TeV,  markerStyleCommmonSpectrumMC7TeV, markerSizeCommonSpectrumPi07TeV, colorCommonMCPythia7TeV, colorCommonMCPythia7TeV);
	DrawGammaSetMarkerTGraphErr( widthEtaLHC10d4_7TeV,  markerStyleCommmonSpectrumMC7TeV, markerSizeCommonSpectrumPi07TeV, colorCommonMCPythia7TeV, colorCommonMCPythia7TeV);


	cout << "Plot 27" << endl;
	
	TCanvas* canvasNGammaEvtppData = new TCanvas("canvasNGammaEvtppData","",200,10,1800,1000);  // gives the page size
	DrawGammaCanvasSettings( canvasNGammaEvtppData, 0.1, 0.04, 0.06, 0.09);
//  	canvasNGammaEvtppData->SetLogy();
	TPad* pad2010Data = new TPad("pad2010Data", "", 0., 0.0, 0.7, 0.94,-1, -1, -2);
	DrawGammaPadSettings( pad2010Data, 0.12, 0.0, 0.05, 0.09);
	pad2010Data->Draw();
	TPad* pad2011Data = new TPad("pad2011Data", "", 0.7, 0., 1., 0.94,-1, -1, -2);
	DrawGammaPadSettings( pad2011Data, 0., 0.06, 0.05, 0.09);
	pad2011Data->Draw();
		
	pad2010Data->cd();
	TH2F * histoNGammaPPA;
	histoNGammaPPA = new TH2F("histoNGammaPPA","histoNGammaPPA",15640,114800,131000,100,0.,0.185);
// 	histoNGammaPP->GetXaxis()->SetRangeUser(0.,2100.);
	SetStyleHistoTH2ForGraphs(histoNGammaPPA, "","#gamma_{cand}/N_{evt}",0.04,0.04, 0.04,0.06, 1.,1.);
	histoNGammaPPA->Draw("copy");
	
	fractionOfGammasLHC10e13_900GeV->Draw("pesame");
	fractionOfGammasLHC10d1_7TeV->Draw("pesame");
	fractionOfGammasLHC10d4_7TeV->Draw("pesame");
	fractionOfGammasLHC10f6a_7TeV->Draw("pesame");
	fractionOfGammasLHC10e20_7TeV->Draw("pesame");

	
	fractionOfGammasLHC10x_900GeV->Draw("pesame");
	fractionOfGammasLHC10x_7TeV->Draw("pesame");
	
	fractionOfGammasLHC10e12_900GeV->Draw("pesame");
	fractionOfGammasLHC10d2_7TeV->Draw("pesame");
	fractionOfGammasLHC10d4a_7TeV->Draw("pesame");
	fractionOfGammasLHC10f6_7TeV->Draw("pesame");
	fractionOfGammasLHC10e21_7TeV->Draw("pesame");
	
	pad2011Data->cd();
	TH2F * histoNGammaPPB;
	histoNGammaPPB = new TH2F("histoNGammaPPB","histoNGammaPPB",120,146730,146865,100,0.,0.185);
// 	histoNGammaPP->GetXaxis()->SetRangeUser(0.,2100.);
	SetStyleHistoTH2ForGraphs(histoNGammaPPB, "Run number","",0.067,0.08, 0.06,0.08, 0.5,1.);
	histoNGammaPPB->GetXaxis()->SetNdivisions(504,kTRUE);
	histoNGammaPPB->GetXaxis()->SetLabelOffset(-0.018);
	histoNGammaPPB->Draw("copy");

	fractionOfGammasLHC11a_2760GeV->Draw("pesame");
	fractionOfGammasLHC12f1b_2760GeV->Draw("pesame");
	fractionOfGammasLHC12f1a_2760GeV->Draw("pesame");
	
	canvasNGammaEvtppData->cd();
	TLegend* legendDataPP = new TLegend(0.06,0.9,0.99,1.);
	legendDataPP->SetFillColor(0);
	legendDataPP->SetLineColor(0);
	legendDataPP->SetTextSize(0.04);
	legendDataPP->SetNColumns(9);
 	legendDataPP->AddEntry((TObject*)0, "0.9 TeV:","");
	legendDataPP->AddEntry(fractionOfGammasLHC10x_900GeV,"Data","p");
	legendDataPP->AddEntry(fractionOfGammasLHC10e12_900GeV,"Phojet","p");
	legendDataPP->AddEntry((TObject*)0, "7 TeV:      ","");
	legendDataPP->AddEntry(fractionOfGammasLHC10x_7TeV,"Data","p");
	legendDataPP->AddEntry(fractionOfGammasLHC10e21_7TeV,"Phojet","p");
	legendDataPP->AddEntry((TObject*)0, "2.76 TeV:","");
	legendDataPP->AddEntry(fractionOfGammasLHC11a_2760GeV,"Data","p");
	legendDataPP->AddEntry(fractionOfGammasLHC12f1b_2760GeV,"Phojet","p");
	legendDataPP->AddEntry((TObject*)0, "","");
	legendDataPP->AddEntry((TObject*)0, "","");
	legendDataPP->AddEntry(fractionOfGammasLHC10e13_900GeV,"Pythia 6","p");
	legendDataPP->AddEntry((TObject*)0, "","");
	legendDataPP->AddEntry((TObject*)0, "","");
	legendDataPP->AddEntry(fractionOfGammasLHC10e20_7TeV,"Pythia 6","p");
	legendDataPP->AddEntry((TObject*)0, "","");
	legendDataPP->AddEntry((TObject*)0, "","");
	legendDataPP->AddEntry(fractionOfGammasLHC12f1a_2760GeV,"Pythia 8","p");

	legendDataPP->Draw();

	canvasNGammaEvtppData->SaveAs(Form("%s/FractionOfPhotonsPerEvent_PP.%s",outputDir.Data(),suffix.Data()));
// 	delete canvasNGammaEvtppData;

   cout << "Plot 28" << endl;
	TCanvas* canvasWOVtxppData = new TCanvas("canvasWOVtxppData","",200,10,1800,1000);  // gives the page size
	DrawGammaCanvasSettings( canvasWOVtxppData, 0.1, 0.04, 0.06, 0.09);
	pad2010Data->Draw();
	pad2011Data->Draw();
		
	pad2010Data->cd();
	TH2F * histoWOVtxPPA;
	histoWOVtxPPA = new TH2F("histoWOVtxPPA","histoWOVtxPPA",15640,114800,131000,100,0.,0.185);
// 	histoNGammaPP->GetXaxis()->SetRangeUser(0.,2100.);
	SetStyleHistoTH2ForGraphs(histoWOVtxPPA, "","N^{evt}_{w/o Vtx}/N^{evt}_{min Bias}",0.04,0.04, 0.04,0.06, 1.,1.);
	histoWOVtxPPA->Draw("copy");
	
	fractionOfWOVtxLHC10e13_900GeV->Draw("pesame");
	fractionOfWOVtxLHC10d1_7TeV->Draw("pesame");
	fractionOfWOVtxLHC10d4_7TeV->Draw("pesame");
	fractionOfWOVtxLHC10f6a_7TeV->Draw("pesame");
	fractionOfWOVtxLHC10e20_7TeV->Draw("pesame");

	
	fractionOfWOVtxLHC10x_900GeV->Draw("pesame");
	fractionOfWOVtxLHC10x_7TeV->Draw("pesame");
	
	fractionOfWOVtxLHC10e12_900GeV->Draw("pesame");
	fractionOfWOVtxLHC10d2_7TeV->Draw("pesame");
	fractionOfWOVtxLHC10d4a_7TeV->Draw("pesame");
	fractionOfWOVtxLHC10f6_7TeV->Draw("pesame");
	fractionOfWOVtxLHC10e21_7TeV->Draw("pesame");
	
	pad2011Data->cd();
	TH2F * histoWOVtxPPB;
	histoWOVtxPPB = new TH2F("histoWOVtxPPB","histoWOVtxPPB",120,146730,146865,100,0.,0.185);
// 	histoWOVtxPP->GetXaxis()->SetRangeUser(0.,2100.);
	SetStyleHistoTH2ForGraphs(histoWOVtxPPB, "Run number","",0.067,0.08, 0.06,0.08, 0.5,1.);
	histoWOVtxPPB->GetXaxis()->SetNdivisions(504,kTRUE);
	histoWOVtxPPB->GetXaxis()->SetLabelOffset(-0.018);
	histoWOVtxPPB->Draw("copy");

	fractionOfWOVtxLHC11a_2760GeV->Draw("pesame");
	fractionOfWOVtxLHC12f1b_2760GeV->Draw("pesame");
	fractionOfWOVtxLHC12f1a_2760GeV->Draw("pesame");
	
	canvasWOVtxppData->cd();
	legendDataPP->Draw();

	canvasWOVtxppData->SaveAs(Form("%s/FractionOfEventsWOVtx_PP.%s",outputDir.Data(),suffix.Data()));

   cout << "Plot 29" << endl;
	TCanvas* canvasFracPi0ppData = new TCanvas("canvasFracPi0ppData","",200,10,1800,1000);  // gives the page size
	DrawGammaCanvasSettings( canvasFracPi0ppData, 0.1, 0.04, 0.06, 0.09);
	
	pad2010Data->Draw();
	pad2010Data->SetLeftMargin(0.14);
	pad2011Data->Draw();
		
	pad2010Data->cd();
	TH2F * histoFracPi0PPA;
	histoFracPi0PPA = new TH2F("histoFracPi0PPA","histoFracPi0PPA",15640,114800,131000,100,0.,0.00115);
// 	histoNGammaPP->GetXaxis()->SetRangeUser(0.,2100.);
	SetStyleHistoTH2ForGraphs(histoFracPi0PPA, "","N_{#pi^{0}_{cand}}/N_{evt}",0.04,0.04, 0.04,0.06, 1.,1.2);
	histoFracPi0PPA->Draw("copy");
	
// 	fractionOfPi0LHC10e13_900GeV->Draw("pesame");
// 	fractionOfPi0LHC10d1_7TeV->Draw("pesame");
// 	fractionOfPi0LHC10d4_7TeV->Draw("pesame");
// 	fractionOfPi0LHC10f6a_7TeV->Draw("pesame");
// 	fractionOfPi0LHC10e20_7TeV->Draw("pesame");

	
	fractionOfPi0LHC10x_900GeV->Draw("pesame");
	fractionOfPi0LHC10x_7TeV->Draw("pesame");
	
// 	fractionOfPi0LHC10e12_900GeV->Draw("pesame");
// 	fractionOfPi0LHC10d2_7TeV->Draw("pesame");
// 	fractionOfPi0LHC10d4a_7TeV->Draw("pesame");
// 	fractionOfPi0LHC10f6_7TeV->Draw("pesame");
// 	fractionOfPi0LHC10e21_7TeV->Draw("pesame");
	
	pad2011Data->cd();
	TH2F * histoFracPi0PPB;
	histoFracPi0PPB = new TH2F("histoFracPi0PPB","histoFracPi0PPB",120,146730,146865,100,0.,0.00115);
// 	histoFracPi0PP->GetXaxis()->SetRangeUser(0.,2100.);
	SetStyleHistoTH2ForGraphs(histoFracPi0PPB, "Run number","",0.067,0.08, 0.06,0.08, 0.5,1.);
	histoFracPi0PPB->GetXaxis()->SetNdivisions(504,kTRUE);
	histoFracPi0PPB->GetXaxis()->SetLabelOffset(-0.018);
	histoFracPi0PPB->Draw("copy");

	fractionOfPi0LHC11a_2760GeV->Draw("pesame");
// 	fractionOfPi0LHC12f1b_2760GeV->Draw("pesame");
// 	fractionOfPi0LHC12f1a_2760GeV->Draw("pesame");
	
	canvasFracPi0ppData->cd();
	TLegend* legendDataPPOnlyData = new TLegend(0.06,0.9,0.99,1.);
	legendDataPPOnlyData->SetFillColor(0);
	legendDataPPOnlyData->SetLineColor(0);
	legendDataPPOnlyData->SetTextSize(0.04);
	legendDataPPOnlyData->SetNColumns(6);
 	legendDataPPOnlyData->AddEntry((TObject*)0, "0.9 TeV:","");
	legendDataPPOnlyData->AddEntry(fractionOfGammasLHC10x_900GeV,"Data","p");
// 	legendDataPPOnlyData->AddEntry(fractionOfGammasLHC10e12_900GeV,"Phojet","p");
	legendDataPPOnlyData->AddEntry((TObject*)0, "7 TeV:      ","");
	legendDataPPOnlyData->AddEntry(fractionOfGammasLHC10x_7TeV,"Data","p");
// 	legendDataPPOnlyData->AddEntry(fractionOfGammasLHC10e21_7TeV,"Phojet","p");
	legendDataPPOnlyData->AddEntry((TObject*)0, "2.76 TeV:","");
	legendDataPPOnlyData->AddEntry(fractionOfGammasLHC11a_2760GeV,"Data","p");
// 	legendDataPPOnlyData->AddEntry(fractionOfGammasLHC12f1b_2760GeV,"Phojet","p");
// 	legendDataPPOnlyData->AddEntry((TObject*)0, "","");
// 	legendDataPPOnlyData->AddEntry((TObject*)0, "","");
// 	legendDataPPOnlyData->AddEntry(fractionOfGammasLHC10e13_900GeV,"Pythia 6","p");
// 	legendDataPPOnlyData->AddEntry((TObject*)0, "","");
// 	legendDataPPOnlyData->AddEntry((TObject*)0, "","");
// 	legendDataPPOnlyData->AddEntry(fractionOfGammasLHC10e20_7TeV,"Pythia 6","p");
// 	legendDataPPOnlyData->AddEntry((TObject*)0, "","");
// 	legendDataPPOnlyData->AddEntry((TObject*)0, "","");
// 	legendDataPPOnlyData->AddEntry(fractionOfGammasLHC12f1a_2760GeV,"Pythia 8","p");

	legendDataPPOnlyData->Draw();

	pad2010Data->cd();
	histoFracPi0PPA->Draw("same,axis");
	canvasFracPi0ppData->SaveAs(Form("%s/FractionOfPi0_PP.%s",outputDir.Data(),suffix.Data()));

   cout << "Plot 30" << endl;
	TCanvas* canvasMassPi0ppData = new TCanvas("canvasMassPi0ppData","",200,10,1800,1000);  // gives the page size
	DrawGammaCanvasSettings( canvasMassPi0ppData, 0.1, 0.04, 0.06, 0.09);
	DrawGammaPadSettings( pad2010Data, 0.12, 0.0, 0.05, 0.09);
	pad2010Data->Draw();
	pad2011Data->Draw();
		
	pad2010Data->cd();
	TH2F * histoMassPi0PPA;
	histoMassPi0PPA = new TH2F("histoMassPi0PPA","histoMassPi0PPA",15640,114800,131000,100,0.130,0.145);
// 	histoNGammaPP->GetXaxis()->SetRangeUser(0.,2100.);
	SetStyleHistoTH2ForGraphs(histoMassPi0PPA, "","m_{#pi^{0}} (GeV/c^{2})",0.04,0.04, 0.04,0.06, 1.,1.);
	histoMassPi0PPA->Draw("copy");
	
// 	massPi0LHC10e13_900GeV->Draw("pesame");
// 	massPi0LHC10d1_7TeV->Draw("pesame");
// 	massPi0LHC10d4_7TeV->Draw("pesame");
// 	massPi0LHC10f6a_7TeV->Draw("pesame");
// 	massPi0LHC10e20_7TeV->Draw("pesame");

	
	massPi0LHC10x_900GeV->Draw("pesame");
	massPi0LHC10x_7TeV->Draw("pesame");
	
// 	massPi0LHC10e12_900GeV->Draw("pesame");
// 	massPi0LHC10d2_7TeV->Draw("pesame");
// 	massPi0LHC10d4a_7TeV->Draw("pesame");
// 	massPi0LHC10f6_7TeV->Draw("pesame");
// 	massPi0LHC10e21_7TeV->Draw("pesame");
	DrawGammaLines(114800, 131000.,0.135, 0.135,1,kGray+2);
	pad2011Data->cd();
	TH2F * histoMassPi0PPB;
	histoMassPi0PPB = new TH2F("histoMassPi0PPB","histoMassPi0PPB",120,146730,146865,100,0.130,0.145);
// 	histoMassPi0PP->GetXaxis()->SetRangeUser(0.,2100.);
	SetStyleHistoTH2ForGraphs(histoMassPi0PPB, "Run number","",0.067,0.08, 0.06,0.08, 0.5,1.);
	histoMassPi0PPB->GetXaxis()->SetNdivisions(504,kTRUE);
	histoMassPi0PPB->GetXaxis()->SetLabelOffset(-0.018);
	histoMassPi0PPB->Draw("copy");

	massPi0LHC11a_2760GeV->Draw("pesame");
// 	massPi0LHC12f1b_2760GeV->Draw("pesame");
// 	massPi0LHC12f1a_2760GeV->Draw("pesame");
	DrawGammaLines(146730, 146865.,0.135, 0.135,1,kGray+2);
	canvasMassPi0ppData->cd();
	legendDataPPOnlyData->Draw();
	canvasMassPi0ppData->SaveAs(Form("%s/MassPi0_PP.%s",outputDir.Data(),suffix.Data()));

   cout << "Plot 31" << endl;
	TCanvas* canvasWidthPi0ppData = new TCanvas("canvasWidthPi0ppData","",200,10,1800,1000);  // gives the page size
	DrawGammaCanvasSettings( canvasWidthPi0ppData, 0.1, 0.04, 0.06, 0.09);
	
	pad2010Data->Draw();
	pad2011Data->Draw();
		
	pad2010Data->cd();
	TH2F * histoWidthPi0PPA;
	histoWidthPi0PPA = new TH2F("histoWidthPi0PPA","histoWidthPi0PPA",15640,114800,131000,100,0.0,0.015);
// 	histoNGammaPP->GetXaxis()->SetRangeUser(0.,2100.);
	SetStyleHistoTH2ForGraphs(histoWidthPi0PPA, "","FWHM_{#pi^{0}} (GeV/c^{2})",0.04,0.04, 0.04,0.06, 1.,1.);
	histoWidthPi0PPA->Draw("copy");
	
// 	widthPi0LHC10e13_900GeV->Draw("pesame");
// 	widthPi0LHC10d1_7TeV->Draw("pesame");
// 	widthPi0LHC10d4_7TeV->Draw("pesame");
// 	widthPi0LHC10f6a_7TeV->Draw("pesame");
// 	widthPi0LHC10e20_7TeV->Draw("pesame");
// 
// 	
	widthPi0LHC10x_900GeV->Draw("pesame");
	widthPi0LHC10x_7TeV->Draw("pesame");
	
// 	widthPi0LHC10e12_900GeV->Draw("pesame");
// 	widthPi0LHC10d2_7TeV->Draw("pesame");
// 	widthPi0LHC10d4a_7TeV->Draw("pesame");
// 	widthPi0LHC10f6_7TeV->Draw("pesame");
// 	widthPi0LHC10e21_7TeV->Draw("pesame");
// 	
	pad2011Data->cd();
	TH2F * histoWidthPi0PPB;
	histoWidthPi0PPB = new TH2F("histoWidthPi0PPB","histoWidthPi0PPB",120,146730,146865,100,0.0,0.015);
// 	histoWidthPi0PP->GetXaxis()->SetRangeUser(0.,2100.);
	SetStyleHistoTH2ForGraphs(histoWidthPi0PPB, "Run number","",0.067,0.08, 0.06,0.08, 0.5,1.);
	histoWidthPi0PPB->GetXaxis()->SetNdivisions(504,kTRUE);
	histoWidthPi0PPB->GetXaxis()->SetLabelOffset(-0.018);
	histoWidthPi0PPB->Draw("copy");

	widthPi0LHC11a_2760GeV->Draw("pesame");
// 	widthPi0LHC12f1b_2760GeV->Draw("pesame");
// 	widthPi0LHC12f1a_2760GeV->Draw("pesame");
	
	canvasWidthPi0ppData->cd();
	legendDataPPOnlyData->Draw();
	canvasWidthPi0ppData->SaveAs(Form("%s/WidthPi0_PP.%s",outputDir.Data(),suffix.Data()));
	
   cout << "Plot 32" << endl;
	TCanvas* canvasMassEtappData = new TCanvas("canvasMassEtappData","",200,10,1800,1000);  // gives the page size
	DrawGammaCanvasSettings( canvasMassEtappData, 0.1, 0.04, 0.06, 0.09);
	
	pad2010Data->Draw();
	pad2011Data->Draw();
		
	pad2010Data->cd();
	TH2F * histoMassEtaPPA;
	histoMassEtaPPA = new TH2F("histoMassEtaPPA","histoMassEtaPPA",15640,114800,131000,100,0.53,0.57);
// 	histoNGammaPP->GetXaxis()->SetRangeUser(0.,2100.);
	SetStyleHistoTH2ForGraphs(histoMassEtaPPA, "","m_{#eta} (GeV/c^{2})",0.04,0.04, 0.04,0.06, 1.,1.);
	histoMassEtaPPA->Draw("copy");
	
// 	massEtaLHC10e13_900GeV->Draw("pesame");
// 	massEtaLHC10d1_7TeV->Draw("pesame");
// 	massEtaLHC10d4_7TeV->Draw("pesame");
// 	massEtaLHC10f6a_7TeV->Draw("pesame");
// 	massEtaLHC10e20_7TeV->Draw("pesame");

	
	massEtaLHC10x_900GeV->Draw("pesame");
	massEtaLHC10x_7TeV->Draw("pesame");
	
// 	massEtaLHC10e12_900GeV->Draw("pesame");
// 	massEtaLHC10d2_7TeV->Draw("pesame");
// 	massEtaLHC10d4a_7TeV->Draw("pesame");
// 	massEtaLHC10f6_7TeV->Draw("pesame");
// 	massEtaLHC10e21_7TeV->Draw("pesame");
	DrawGammaLines(114800, 131000.,0.548, 0.548,1,kGray+2);
	
	pad2011Data->cd();
	TH2F * histoMassEtaPPB;
	histoMassEtaPPB = new TH2F("histoMassEtaPPB","histoMassEtaPPB",120,146730,146865,100,0.53,0.57);
// 	histoMassEtaPP->GetXaxis()->SetRangeUser(0.,2100.);
	SetStyleHistoTH2ForGraphs(histoMassEtaPPB, "Run number","",0.067,0.08, 0.06,0.08, 0.5,1.);
	histoMassEtaPPB->GetXaxis()->SetNdivisions(504,kTRUE);
	histoMassEtaPPB->GetXaxis()->SetLabelOffset(-0.018);
	histoMassEtaPPB->Draw("copy");

	massEtaLHC11a_2760GeV->Draw("pesame");
// 	massEtaLHC12f1b_2760GeV->Draw("pesame");
// 	massEtaLHC12f1a_2760GeV->Draw("pesame");
	DrawGammaLines(146730, 146865.,0.548, 0.548,1,kGray+2);
	canvasMassEtappData->cd();
	legendDataPPOnlyData->Draw();
	canvasMassEtappData->SaveAs(Form("%s/MassEta_PP.%s",outputDir.Data(),suffix.Data()));

   cout << "Plot 33" << endl;
	TCanvas* canvasWidthEtappData = new TCanvas("canvasWidthEtappData","",200,10,1800,1000);  // gives the page size
	DrawGammaCanvasSettings( canvasWidthEtappData, 0.1, 0.04, 0.06, 0.09);
	
	pad2010Data->Draw();
	pad2011Data->Draw();
		
	pad2010Data->cd();
	TH2F * histoWidthEtaPPA;
	histoWidthEtaPPA = new TH2F("histoWidthEtaPPA","histoWidthEtaPPA",15640,114800,131000,100,0.0,0.03);
// 	histoNGammaPP->GetXaxis()->SetRangeUser(0.,2100.);
	SetStyleHistoTH2ForGraphs(histoWidthEtaPPA, "","FWHM_{#eta} (GeV/c^{2})",0.04,0.04, 0.04,0.06, 1.,1.);
	histoWidthEtaPPA->Draw("copy");
	
// 	widthEtaLHC10e13_900GeV->Draw("pesame");
// 	widthEtaLHC10d1_7TeV->Draw("pesame");
// 	widthEtaLHC10d4_7TeV->Draw("pesame");
// 	widthEtaLHC10f6a_7TeV->Draw("pesame");
// 	widthEtaLHC10e20_7TeV->Draw("pesame");
// 
// 	
	widthEtaLHC10x_900GeV->Draw("pesame");
	widthEtaLHC10x_7TeV->Draw("pesame");
	
// 	widthEtaLHC10e12_900GeV->Draw("pesame");
// 	widthEtaLHC10d2_7TeV->Draw("pesame");
// 	widthEtaLHC10d4a_7TeV->Draw("pesame");
// 	widthEtaLHC10f6_7TeV->Draw("pesame");
// 	widthEtaLHC10e21_7TeV->Draw("pesame");
// 	
	pad2011Data->cd();
	TH2F * histoWidthEtaPPB;
	histoWidthEtaPPB = new TH2F("histoWidthEtaPPB","histoWidthEtaPPB",120,146730,146865,100,0.0,0.03);
// 	histoWidthEtaPP->GetXaxis()->SetRangeUser(0.,2100.);
	SetStyleHistoTH2ForGraphs(histoWidthEtaPPB, "Run number","",0.067,0.08, 0.06,0.08, 0.5,1.);
	histoWidthEtaPPB->GetXaxis()->SetNdivisions(504,kTRUE);
	histoWidthEtaPPB->GetXaxis()->SetLabelOffset(-0.018);
	histoWidthEtaPPB->Draw("copy");

	widthEtaLHC11a_2760GeV->Draw("pesame");
// 	widthEtaLHC12f1b_2760GeV->Draw("pesame");
// 	widthEtaLHC12f1a_2760GeV->Draw("pesame");
	
	canvasWidthEtappData->cd();
	legendDataPPOnlyData->Draw();
	canvasWidthEtappData->SaveAs(Form("%s/WidthEta_PP.%s",outputDir.Data(),suffix.Data()));

	cout << "Plot 34" << endl;
	TCanvas* canvasFracEtappData = new TCanvas("canvasFracEtappData","",200,10,1800,1000);  // gives the page size
	DrawGammaCanvasSettings( canvasFracEtappData, 0.1, 0.04, 0.06, 0.09);
	
	pad2010Data->SetLeftMargin(0.15);
	pad2010Data->Draw();
	pad2011Data->Draw();
		
	pad2010Data->cd();
	TH2F * histoFracEtaPPA;
	histoFracEtaPPA = new TH2F("histoFracEtaPPA","histoFracEtaPPA",15640,114800,131000,100,0.,0.00019);
// 	histoNGammaPP->GetXaxis()->SetRangeUser(0.,2100.);
	SetStyleHistoTH2ForGraphs(histoFracEtaPPA, "","N_{#eta_{cand}}/N_{evt}",0.04,0.04, 0.04,0.06, 1.,1.3);
	histoFracEtaPPA->GetYaxis()->SetNdivisions(504,kTRUE);
	histoFracEtaPPA->Draw("copy");
	
// 	fractionOfEtaLHC10e13_900GeV->Draw("pesame");
// 	fractionOfEtaLHC10d1_7TeV->Draw("pesame");
// 	fractionOfEtaLHC10d4_7TeV->Draw("pesame");
// 	fractionOfEtaLHC10f6a_7TeV->Draw("pesame");
// 	fractionOfEtaLHC10e20_7TeV->Draw("pesame");
// 
	
	fractionOfEtaLHC10x_900GeV->Draw("pesame");
	fractionOfEtaLHC10x_7TeV->Draw("pesame");
	
// 	fractionOfEtaLHC10e12_900GeV->Draw("pesame");
// 	fractionOfEtaLHC10d2_7TeV->Draw("pesame");
// 	fractionOfEtaLHC10d4a_7TeV->Draw("pesame");
// 	fractionOfEtaLHC10f6_7TeV->Draw("pesame");
// 	fractionOfEtaLHC10e21_7TeV->Draw("pesame");
	
	pad2011Data->cd();
	TH2F * histoFracEtaPPB;
	histoFracEtaPPB = new TH2F("histoFracEtaPPB","histoFracEtaPPB",120,146730,146865,100,0.,0.00019);
// 	histoFracEtaPP->GetXaxis()->SetRangeUser(0.,2100.);
	SetStyleHistoTH2ForGraphs(histoFracEtaPPB, "Run number","",0.067,0.08, 0.06,0.08, 0.5,1.);
	histoFracEtaPPB->GetXaxis()->SetNdivisions(504,kTRUE);
	histoFracEtaPPB->GetYaxis()->SetNdivisions(504,kTRUE);
	histoFracEtaPPB->GetXaxis()->SetLabelOffset(-0.018);
	histoFracEtaPPB->Draw("copy");

	fractionOfEtaLHC11a_2760GeV->Draw("pesame");
// 	fractionOfEtaLHC12f1b_2760GeV->Draw("pesame");
// 	fractionOfEtaLHC12f1a_2760GeV->Draw("pesame");
	
	canvasFracEtappData->cd();
	legendDataPPOnlyData->Draw();
	pad2010Data->cd();
	histoFracEtaPPA->Draw("same,axis");
	canvasFracEtappData->SaveAs(Form("%s/FractionOfEta_PP.%s",outputDir.Data(),suffix.Data()));

	cout << "Plot 35" << endl;
	TCanvas* canvasWVtxOutside10cmppData = new TCanvas("canvasWVtxOutside10cmppData","",200,10,1800,1000);  // gives the page size
	DrawGammaCanvasSettings( canvasWVtxOutside10cmppData, 0.1, 0.04, 0.06, 0.09);
	DrawGammaPadSettings( pad2010Data, 0.12, 0.0, 0.05, 0.09);
	pad2010Data->Draw();
	pad2011Data->Draw();
		
	pad2010Data->cd();	
	TH2F * histoWVtxOutside10cmPPA;
	histoWVtxOutside10cmPPA = new TH2F("histoWVtxOutside10cmPPA","histoWVtxOutside10cmPPA",15640,114800,131000,100,0.,0.185);
// 	histoNGammaPP->GetXaxis()->SetRangeUser(0.,2100.);
	SetStyleHistoTH2ForGraphs(histoWVtxOutside10cmPPA, "","N^{evt}_{Z_{vtx} > #pm 10cm}/N^{evt}_{min Bias}",0.04,0.04, 0.04,0.06, 1.,1.);
	histoWVtxOutside10cmPPA->Draw("copy");
	
	fractionOfWVtxOutside10cmLHC10e13_900GeV->Draw("pesame");
	fractionOfWVtxOutside10cmLHC10d1_7TeV->Draw("pesame");
	fractionOfWVtxOutside10cmLHC10d4_7TeV->Draw("pesame");
	fractionOfWVtxOutside10cmLHC10f6a_7TeV->Draw("pesame");
	fractionOfWVtxOutside10cmLHC10e20_7TeV->Draw("pesame");

	
	fractionOfWVtxOutside10cmLHC10x_900GeV->Draw("pesame");
	fractionOfWVtxOutside10cmLHC10x_7TeV->Draw("pesame");
	
	fractionOfWVtxOutside10cmLHC10e12_900GeV->Draw("pesame");
	fractionOfWVtxOutside10cmLHC10d2_7TeV->Draw("pesame");
	fractionOfWVtxOutside10cmLHC10d4a_7TeV->Draw("pesame");
	fractionOfWVtxOutside10cmLHC10f6_7TeV->Draw("pesame");
	fractionOfWVtxOutside10cmLHC10e21_7TeV->Draw("pesame");
	
	pad2011Data->cd();
	TH2F * histoWVtxOutside10cmPPB;
	histoWVtxOutside10cmPPB = new TH2F("histoWVtxOutside10cmPPB","histoWVtxOutside10cmPPB",120,146730,146865,100,0.,0.185);
// 	histoWVtxOutside10cmPP->GetXaxis()->SetRangeUser(0.,2100.);
	SetStyleHistoTH2ForGraphs(histoWVtxOutside10cmPPB, "Run number","",0.067,0.08, 0.06,0.08, 0.5,1.);
	histoWVtxOutside10cmPPB->GetXaxis()->SetNdivisions(504,kTRUE);
	histoWVtxOutside10cmPPB->GetXaxis()->SetLabelOffset(-0.018);
	histoWVtxOutside10cmPPB->Draw("copy");

	fractionOfWVtxOutside10cmLHC11a_2760GeV->Draw("pesame");
	fractionOfWVtxOutside10cmLHC12f1b_2760GeV->Draw("pesame");
	fractionOfWVtxOutside10cmLHC12f1a_2760GeV->Draw("pesame");
	
	canvasWVtxOutside10cmppData->cd();
	legendDataPP->Draw();

	canvasWVtxOutside10cmppData->SaveAs(Form("%s/FractionOfEventsWVtxOutside10cm_PP.%s",outputDir.Data(),suffix.Data()));

   cout << "Plot 36" << endl;
	TCanvas* canvasNormAllppData = new TCanvas("canvasNormAllppData","",200,10,1800,1000);  // gives the page size
	DrawGammaCanvasSettings( canvasNormAllppData, 0.1, 0.04, 0.06, 0.09);
	pad2010Data->Draw();
	pad2011Data->Draw();
		
	pad2010Data->cd();	
	TH2F * histoNormAllPPA;
	histoNormAllPPA = new TH2F("histoNormAllPPA","histoNormAllPPA",15640,114800,131000,100,0.,1.1);
// 	histoNGammaPP->GetXaxis()->SetRangeUser(0.,2100.);
	SetStyleHistoTH2ForGraphs(histoNormAllPPA, "","N^{evt}_{norm}/N^{evt}_{Phys. Sel.}",0.04,0.04, 0.04,0.06, 1.,1.);
	histoNormAllPPA->Draw("copy");
	
	fractionOfNormAllLHC10e13_900GeV->Draw("pesame");
	fractionOfNormAllLHC10d1_7TeV->Draw("pesame");
	fractionOfNormAllLHC10d4_7TeV->Draw("pesame");
	fractionOfNormAllLHC10f6a_7TeV->Draw("pesame");
	fractionOfNormAllLHC10e20_7TeV->Draw("pesame");

	
	fractionOfNormAllLHC10x_900GeV->Draw("pesame");
	fractionOfNormAllLHC10x_7TeV->Draw("pesame");
	
	fractionOfNormAllLHC10e12_900GeV->Draw("pesame");
	fractionOfNormAllLHC10d2_7TeV->Draw("pesame");
	fractionOfNormAllLHC10d4a_7TeV->Draw("pesame");
	fractionOfNormAllLHC10f6_7TeV->Draw("pesame");
	fractionOfNormAllLHC10e21_7TeV->Draw("pesame");
	
	pad2011Data->cd();
	TH2F * histoNormAllPPB;
	histoNormAllPPB = new TH2F("histoNormAllPPB","histoNormAllPPB",120,146730,146865,100,0.,1.1);
// 	histoNormAllPP->GetXaxis()->SetRangeUser(0.,2100.);
	SetStyleHistoTH2ForGraphs(histoNormAllPPB, "Run number","",0.067,0.08, 0.06,0.08, 0.5,1.);
	histoNormAllPPB->GetXaxis()->SetNdivisions(504,kTRUE);
	histoNormAllPPB->GetXaxis()->SetLabelOffset(-0.018);
	histoNormAllPPB->Draw("copy");

	fractionOfNormAllLHC11a_2760GeV->Draw("pesame");
	fractionOfNormAllLHC12f1b_2760GeV->Draw("pesame");
	fractionOfNormAllLHC12f1a_2760GeV->Draw("pesame");
	
	canvasNormAllppData->cd();
	legendDataPP->Draw();

	canvasNormAllppData->SaveAs(Form("%s/FractionOfEventsNormAll_PP.%s",outputDir.Data(),suffix.Data()));

   cout << "Plot 37" << endl;
	TCanvas* canvasNormMinBiasppData = new TCanvas("canvasNormMinBiasppData","",200,10,1800,1000);  // gives the page size
	DrawGammaCanvasSettings( canvasNormMinBiasppData, 0.1, 0.04, 0.06, 0.09);
	pad2010Data->Draw();
	pad2011Data->Draw();
		
	pad2010Data->cd();	
	TH2F * histoNormMinBiasPPA;
	histoNormMinBiasPPA = new TH2F("histoNormMinBiasPPA","histoNormMinBiasPPA",15640,114800,131000,100,0.,1.1);
// 	histoNGammaPP->GetXaxis()->SetRangeUser(0.,2100.);
	SetStyleHistoTH2ForGraphs(histoNormMinBiasPPA, "","N^{evt}_{norm}/N^{evt}_{Min. Bias.}",0.04,0.04, 0.04,0.06, 1.,1.);
	histoNormMinBiasPPA->Draw("copy");
	
	fractionOfNormMinBiasLHC10e13_900GeV->Draw("pesame");
	fractionOfNormMinBiasLHC10d1_7TeV->Draw("pesame");
	fractionOfNormMinBiasLHC10d4_7TeV->Draw("pesame");
	fractionOfNormMinBiasLHC10f6a_7TeV->Draw("pesame");
	fractionOfNormMinBiasLHC10e20_7TeV->Draw("pesame");

	
	fractionOfNormMinBiasLHC10x_900GeV->Draw("pesame");
	fractionOfNormMinBiasLHC10x_7TeV->Draw("pesame");
	
	fractionOfNormMinBiasLHC10e12_900GeV->Draw("pesame");
	fractionOfNormMinBiasLHC10d2_7TeV->Draw("pesame");
	fractionOfNormMinBiasLHC10d4a_7TeV->Draw("pesame");
	fractionOfNormMinBiasLHC10f6_7TeV->Draw("pesame");
	fractionOfNormMinBiasLHC10e21_7TeV->Draw("pesame");
	
	pad2011Data->cd();
	TH2F * histoNormMinBiasPPB;
	histoNormMinBiasPPB = new TH2F("histoNormMinBiasPPB","histoNormMinBiasPPB",120,146730,146865,100,0.,1.1);
// 	histoNormMinBiasPP->GetXaxis()->SetRangeUser(0.,2100.);
	SetStyleHistoTH2ForGraphs(histoNormMinBiasPPB, "Run number","",0.067,0.08, 0.06,0.08, 0.5,1.);
	histoNormMinBiasPPB->GetXaxis()->SetNdivisions(504,kTRUE);
	histoNormMinBiasPPB->GetXaxis()->SetLabelOffset(-0.018);
	histoNormMinBiasPPB->Draw("copy");

	fractionOfNormMinBiasLHC11a_2760GeV->Draw("pesame");
	fractionOfNormMinBiasLHC12f1b_2760GeV->Draw("pesame");
	fractionOfNormMinBiasLHC12f1a_2760GeV->Draw("pesame");
	
	canvasNormMinBiasppData->cd();
	legendDataPP->Draw();

	canvasNormMinBiasppData->SaveAs(Form("%s/FractionOfEventsNormMinBias_PP.%s",outputDir.Data(),suffix.Data()));

   cout << "Plot 38" << endl;
	TCanvas* canvasPileUpppData = new TCanvas("canvasPileUpppData","",200,10,1800,1000);  // gives the page size
	DrawGammaCanvasSettings( canvasPileUpppData, 0.1, 0.04, 0.06, 0.09);
	pad2010Data->Draw();
	pad2011Data->Draw();
		
	pad2010Data->cd();	
	TH2F * histoPileUpPPA;
	histoPileUpPPA = new TH2F("histoPileUpPPA","histoPileUpPPA",15640,114800,131000,100,0.,0.075);
// 	histoNGammaPP->GetXaxis()->SetRangeUser(0.,2100.);
	SetStyleHistoTH2ForGraphs(histoPileUpPPA, "","N^{evt}_{Pile up SPD}/N^{evt}_{Min. Bias}",0.04,0.04, 0.04,0.06, 1.,1.);
	histoPileUpPPA->Draw("copy");
	
	fractionOfPileUpLHC10e13_900GeV->Draw("pesame");
	fractionOfPileUpLHC10d1_7TeV->Draw("pesame");
	fractionOfPileUpLHC10d4_7TeV->Draw("pesame");
	fractionOfPileUpLHC10f6a_7TeV->Draw("pesame");
	fractionOfPileUpLHC10e20_7TeV->Draw("pesame");

	
	fractionOfPileUpLHC10x_900GeV->Draw("pesame");
	fractionOfPileUpLHC10x_7TeV->Draw("pesame");
	
	fractionOfPileUpLHC10e12_900GeV->Draw("pesame");
	fractionOfPileUpLHC10d2_7TeV->Draw("pesame");
	fractionOfPileUpLHC10d4a_7TeV->Draw("pesame");
	fractionOfPileUpLHC10f6_7TeV->Draw("pesame");
	fractionOfPileUpLHC10e21_7TeV->Draw("pesame");
	
	pad2011Data->cd();
	TH2F * histoPileUpPPB;
	histoPileUpPPB = new TH2F("histoPileUpPPB","histoPileUpPPB",120,146730,146865,100,0.,0.075);
// 	histoPileUpPP->GetXaxis()->SetRangeUser(0.,2100.);
	SetStyleHistoTH2ForGraphs(histoPileUpPPB, "Run number","",0.067,0.08, 0.06,0.08, 0.5,1.);
	histoPileUpPPB->GetXaxis()->SetNdivisions(504,kTRUE);
	histoPileUpPPB->GetXaxis()->SetLabelOffset(-0.018);
	histoPileUpPPB->Draw("copy");

	fractionOfPileUpLHC11a_2760GeV->Draw("pesame");
	fractionOfPileUpLHC12f1b_2760GeV->Draw("pesame");
	fractionOfPileUpLHC12f1a_2760GeV->Draw("pesame");
	
	canvasPileUpppData->cd();
	legendDataPP->Draw();

	canvasPileUpppData->SaveAs(Form("%s/FractionOfEventsPileUp_PP.%s",outputDir.Data(),suffix.Data()));


	
	DrawGammaSetMarkerTGraphErr( meanTrackMultTPCDataLHC10x_900GeV,  markerStyleCommmonSpectrum900GeV, markerSizeCommonSpectrumPi0900GeV, colorPi0900GeV, colorPi0900GeV);
	DrawGammaSetMarkerTGraphErr( meanTrackMultTPCDataLHC11a_2760GeV,  markerStyleCommmonSpectrum2760GeV, markerSizeCommonSpectrumPi02760GeV, colorPi02760GeV, colorPi02760GeV);
	DrawGammaSetMarkerTGraphErr( meanTrackMultTPCDataLHC10x_7TeV,  markerStyleCommmonSpectrum7TeV, markerSizeCommonSpectrumPi07TeV, colorPi07TeV, colorPi07TeV);

	DrawGammaSetMarkerTGraphErr( meanTrackMultTPCDataLHC10e12_900GeV,  markerStyleCommmonSpectrumMC900GeV, markerSizeCommonSpectrumPi0900GeV, colorCommonMCPhojet900GeV, colorCommonMCPhojet900GeV);
	DrawGammaSetMarkerTGraphErr( meanTrackMultTPCDataLHC10e13_900GeV,  markerStyleCommmonSpectrumMC900GeV, markerSizeCommonSpectrumPi0900GeV, colorCommonMCPythia900GeV, colorCommonMCPythia900GeV);
	
	DrawGammaSetMarkerTGraphErr( meanTrackMultTPCDataLHC12f1a_2760GeV,  markerStyleCommmonSpectrumMC2760GeV, markerSizeCommonSpectrumPi02760GeV, colorCommonMCPythia2760GeV, colorCommonMCPythia2760GeV);
	DrawGammaSetMarkerTGraphErr( meanTrackMultTPCDataLHC12f1b_2760GeV,  markerStyleCommmonSpectrumMC2760GeV, markerSizeCommonSpectrumPi02760GeV, colorCommonMCPhojet2760GeV, colorCommonMCPhojet2760GeV);
	
	DrawGammaSetMarkerTGraphErr( meanTrackMultTPCDataLHC10e20_7TeV,  markerStyleCommmonSpectrumMC7TeV, markerSizeCommonSpectrumPi07TeV, colorCommonMCPythia7TeV, colorCommonMCPythia7TeV);
	DrawGammaSetMarkerTGraphErr( meanTrackMultTPCDataLHC10e21_7TeV,  markerStyleCommmonSpectrumMC7TeV, markerSizeCommonSpectrumPi07TeV, colorCommonMCPhojet7TeV, colorCommonMCPhojet7TeV);
	DrawGammaSetMarkerTGraphErr( meanTrackMultTPCDataLHC10f6a_7TeV,  markerStyleCommmonSpectrumMC7TeV, markerSizeCommonSpectrumPi07TeV, colorCommonMCPythia7TeV, colorCommonMCPythia7TeV);
	DrawGammaSetMarkerTGraphErr( meanTrackMultTPCDataLHC10f6_7TeV,  markerStyleCommmonSpectrumMC7TeV, markerSizeCommonSpectrumPi07TeV, colorCommonMCPhojet7TeV, colorCommonMCPhojet7TeV);
	DrawGammaSetMarkerTGraphErr( meanTrackMultTPCDataLHC10d1_7TeV,  markerStyleCommmonSpectrumMC7TeV, markerSizeCommonSpectrumPi07TeV, colorCommonMCPythia7TeV, colorCommonMCPythia7TeV);
	DrawGammaSetMarkerTGraphErr( meanTrackMultTPCDataLHC10d2_7TeV,  markerStyleCommmonSpectrumMC7TeV, markerSizeCommonSpectrumPi07TeV, colorCommonMCPhojet7TeV, colorCommonMCPhojet7TeV);
	DrawGammaSetMarkerTGraphErr( meanTrackMultTPCDataLHC10d4a_7TeV,  markerStyleCommmonSpectrumMC7TeV, markerSizeCommonSpectrumPi07TeV, colorCommonMCPhojet7TeV, colorCommonMCPhojet7TeV);
	DrawGammaSetMarkerTGraphErr( meanTrackMultTPCDataLHC10d4_7TeV,  markerStyleCommmonSpectrumMC7TeV, markerSizeCommonSpectrumPi07TeV, colorCommonMCPythia7TeV, colorCommonMCPythia7TeV);

	
	
	cout << "Plot 39" << endl;
	TCanvas* canvasNTPCTracks = new TCanvas("canvasNTPCTracks","",200,10,1800,1000);  // gives the page size
	
	DrawGammaCanvasSettings( canvasNTPCTracks, 0.1, 0.04, 0.06, 0.09);
	TPad* pad2010Mult = new TPad("pad2010Mult", "", 0., 0.0, 0.7, 0.94,-1, -1, -2);
	DrawGammaPadSettings( pad2010Mult, 0.12, 0.0, 0.05, 0.09);
	pad2010Mult->Draw();
	TPad* pad2011Mult = new TPad("pad2011Mult", "", 0.7, 0., 1., 0.94,-1, -1, -2);
	DrawGammaPadSettings( pad2011Mult, 0., 0.06, 0.05, 0.09);
	pad2011Mult->Draw();
		
	pad2010Mult->cd();
	TH2F * histoTrackMultPPA;
	histoTrackMultPPA = new TH2F("histoTrackMultPPA","histoTrackMultPPA",15640,114800,131000,100,0.,8.5);
// 	histoTrackMultPP->GetXaxis()->SetRangeUser(0.,2100.);
	SetStyleHistoTH2ForGraphs(histoTrackMultPPA, "","#LT n TPC tracks #GT",0.04,0.04, 0.04,0.06, 1.,1.);
	histoTrackMultPPA->Draw("copy");
	
	meanTrackMultTPCDataLHC10e13_900GeV->Draw("pesame");
	meanTrackMultTPCDataLHC10d1_7TeV->Draw("pesame");
	meanTrackMultTPCDataLHC10d4_7TeV->Draw("pesame");
	meanTrackMultTPCDataLHC10f6a_7TeV->Draw("pesame");
	meanTrackMultTPCDataLHC10e20_7TeV->Draw("pesame");

	
	meanTrackMultTPCDataLHC10x_900GeV->Draw("pesame");
	meanTrackMultTPCDataLHC10x_7TeV->Draw("pesame");
	
	meanTrackMultTPCDataLHC10e12_900GeV->Draw("pesame");
	meanTrackMultTPCDataLHC10d2_7TeV->Draw("pesame");
	meanTrackMultTPCDataLHC10d4a_7TeV->Draw("pesame");
	meanTrackMultTPCDataLHC10f6_7TeV->Draw("pesame");
	meanTrackMultTPCDataLHC10e21_7TeV->Draw("pesame");
	
	pad2011Mult->cd();
	TH2F * histoTrackMultPPB;
	histoTrackMultPPB = new TH2F("histoTrackMultPPB","histoTrackMultPPB",120,146730,146865,100,0.,8.5);
// 	histoTrackMultPP->GetXaxis()->SetRangeUser(0.,2100.);
	SetStyleHistoTH2ForGraphs(histoTrackMultPPB, "Run number","",0.067,0.08, 0.06,0.08, 0.5,1.);
	histoTrackMultPPB->GetXaxis()->SetNdivisions(504,kTRUE);
	histoTrackMultPPB->GetXaxis()->SetLabelOffset(-0.018);
	histoTrackMultPPB->Draw("copy");

	meanTrackMultTPCDataLHC11a_2760GeV->Draw("pesame");
	meanTrackMultTPCDataLHC12f1b_2760GeV->Draw("pesame");
	meanTrackMultTPCDataLHC12f1a_2760GeV->Draw("pesame");
	
	canvasNTPCTracks->cd();
	TLegend* legendMultDataPP = new TLegend(0.06,0.9,0.99,1.);
	legendMultDataPP->SetFillColor(0);
	legendMultDataPP->SetLineColor(0);
	legendMultDataPP->SetTextSize(0.04);
	legendMultDataPP->SetNColumns(9);
 	legendMultDataPP->AddEntry((TObject*)0, "0.9 TeV:","");
	legendMultDataPP->AddEntry(meanTrackMultTPCDataLHC10x_900GeV,"Data","p");
	legendMultDataPP->AddEntry(meanTrackMultTPCDataLHC10e12_900GeV,"Phojet","p");
	legendMultDataPP->AddEntry((TObject*)0, "7 TeV:      ","");
	legendMultDataPP->AddEntry(meanTrackMultTPCDataLHC10x_7TeV,"Data","p");
	legendMultDataPP->AddEntry(meanTrackMultTPCDataLHC10e21_7TeV,"Phojet","p");
	legendMultDataPP->AddEntry((TObject*)0, "2.76 TeV:","");
	legendMultDataPP->AddEntry(meanTrackMultTPCDataLHC11a_2760GeV,"Data","p");
	legendMultDataPP->AddEntry(meanTrackMultTPCDataLHC12f1b_2760GeV,"Phojet","p");
	legendMultDataPP->AddEntry((TObject*)0, "","");
	legendMultDataPP->AddEntry((TObject*)0, "","");
	legendMultDataPP->AddEntry(meanTrackMultTPCDataLHC10e13_900GeV,"Pythia 6","p");
	legendMultDataPP->AddEntry((TObject*)0, "","");
	legendMultDataPP->AddEntry((TObject*)0, "","");
	legendMultDataPP->AddEntry(meanTrackMultTPCDataLHC10e20_7TeV,"Pythia 6","p");
	legendMultDataPP->AddEntry((TObject*)0, "","");
	legendMultDataPP->AddEntry((TObject*)0, "","");
	legendMultDataPP->AddEntry(meanTrackMultTPCDataLHC12f1a_2760GeV,"Pythia 8","p");

	legendMultDataPP->Draw();

	canvasNTPCTracks->SaveAs(Form("%s/MeanMultiplicity_TPCTracks_PP.%s",outputDir.Data(),suffix.Data()));
	delete canvasNTPCTracks;

   
   Color_t  colorPi0pPb          = kGreen+2;
   Color_t  colorCommonMCpPb  = colorPi0pPb-5;
   Style_t  markerStyleCommmonSpectrumpPb = 34 ;
   Style_t  markerStyleCommmonSpectrumMCpPb  = 28 ;
   Size_t   markerSizeCommonSpectrumPi0pPb = 1.8;
  
   DrawGammaSetMarkerTGraphErr( fractionOfGammasLHC13x_pPb,  markerStyleCommmonSpectrumpPb, markerSizeCommonSpectrumPi0pPb, colorPi0pPb, colorPi0pPb); 
   DrawGammaSetMarkerTGraphErr( fractionOfPi0LHC13x_pPb,  markerStyleCommmonSpectrumpPb, markerSizeCommonSpectrumPi0pPb, colorPi0pPb, colorPi0pPb);
   DrawGammaSetMarkerTGraphErr( fractionOfEtaLHC13x_pPb,  markerStyleCommmonSpectrumpPb, markerSizeCommonSpectrumPi0pPb, colorPi0pPb, colorPi0pPb);
   DrawGammaSetMarkerTGraphErr( massPi0LHC13x_pPb,  markerStyleCommmonSpectrumpPb, markerSizeCommonSpectrumPi0pPb, colorPi0pPb, colorPi0pPb);
   DrawGammaSetMarkerTGraphErr( widthPi0LHC13x_pPb,  markerStyleCommmonSpectrumpPb, markerSizeCommonSpectrumPi0pPb, colorPi0pPb, colorPi0pPb);
   DrawGammaSetMarkerTGraphErr( massEtaLHC13x_pPb,  markerStyleCommmonSpectrumpPb, markerSizeCommonSpectrumPi0pPb, colorPi0pPb, colorPi0pPb);
   DrawGammaSetMarkerTGraphErr( widthEtaLHC13x_pPb,  markerStyleCommmonSpectrumpPb, markerSizeCommonSpectrumPi0pPb, colorPi0pPb, colorPi0pPb);
   DrawGammaSetMarkerTGraphErr( fractionOfWOVtxLHC13x_pPb,  markerStyleCommmonSpectrumpPb, markerSizeCommonSpectrumPi0pPb, colorPi0pPb, colorPi0pPb);
   DrawGammaSetMarkerTGraphErr( fractionOfWVtxOutside10cmLHC13x_pPb,  markerStyleCommmonSpectrumpPb, markerSizeCommonSpectrumPi0pPb, colorPi0pPb, colorPi0pPb);
   DrawGammaSetMarkerTGraphErr( fractionOfGoodEventsLHC13x_pPb,  markerStyleCommmonSpectrumpPb, markerSizeCommonSpectrumPi0pPb, colorPi0pPb, colorPi0pPb);
   DrawGammaSetMarkerTGraphErr( fractionOfNormAllLHC13x_pPb,  markerStyleCommmonSpectrumpPb, markerSizeCommonSpectrumPi0pPb, colorPi0pPb, colorPi0pPb);
   DrawGammaSetMarkerTGraphErr( fractionOfNormMinBiasLHC13x_pPb,  markerStyleCommmonSpectrumpPb, markerSizeCommonSpectrumPi0pPb, colorPi0pPb, colorPi0pPb);
   DrawGammaSetMarkerTGraphErr( fractionOfPileUpLHC13x_pPb,  markerStyleCommmonSpectrumpPb, markerSizeCommonSpectrumPi0pPb, colorPi0pPb, colorPi0pPb);
   DrawGammaSetMarkerTGraphErr( meanTrackMultTPCDataLHC13x_pPb,  markerStyleCommmonSpectrumpPb, markerSizeCommonSpectrumPi0pPb, colorPi0pPb, colorPi0pPb);
   
   
   DrawGammaSetMarkerTGraphErr( fractionOfGammasLHC13b_fix_1_pPb,  markerStyleCommmonSpectrumMCpPb, markerSizeCommonSpectrumPi0pPb, colorCommonMCpPb, colorCommonMCpPb);
   DrawGammaSetMarkerTGraphErr( fractionOfPi0LHC13b_fix_1_pPb,  markerStyleCommmonSpectrumMCpPb, markerSizeCommonSpectrumPi0pPb, colorCommonMCpPb, colorCommonMCpPb);
   DrawGammaSetMarkerTGraphErr( fractionOfEtaLHC13b_fix_1_pPb,  markerStyleCommmonSpectrumMCpPb, markerSizeCommonSpectrumPi0pPb, colorCommonMCpPb, colorCommonMCpPb);
   DrawGammaSetMarkerTGraphErr( fractionOfWOVtxLHC13b_fix_1_pPb,  markerStyleCommmonSpectrumMCpPb, markerSizeCommonSpectrumPi0pPb, colorCommonMCpPb, colorCommonMCpPb);
   DrawGammaSetMarkerTGraphErr( fractionOfWVtxOutside10cmLHC13b_fix_1_pPb,  markerStyleCommmonSpectrumMCpPb, markerSizeCommonSpectrumPi0pPb, colorCommonMCpPb, colorCommonMCpPb);
   DrawGammaSetMarkerTGraphErr( fractionOfGoodEventsLHC13b_fix_1_pPb,  markerStyleCommmonSpectrumMCpPb, markerSizeCommonSpectrumPi0pPb, colorCommonMCpPb, colorCommonMCpPb);
   DrawGammaSetMarkerTGraphErr( fractionOfNormAllLHC13b_fix_1_pPb,  markerStyleCommmonSpectrumMCpPb, markerSizeCommonSpectrumPi0pPb, colorCommonMCpPb, colorCommonMCpPb);
   DrawGammaSetMarkerTGraphErr( fractionOfNormMinBiasLHC13b_fix_1_pPb,  markerStyleCommmonSpectrumMCpPb, markerSizeCommonSpectrumPi0pPb, colorCommonMCpPb, colorCommonMCpPb);
   DrawGammaSetMarkerTGraphErr( fractionOfPileUpLHC13b_fix_1_pPb,  markerStyleCommmonSpectrumMCpPb, markerSizeCommonSpectrumPi0pPb, colorCommonMCpPb, colorCommonMCpPb);
   DrawGammaSetMarkerTGraphErr( massPi0LHC13b_fix_1_pPb,  markerStyleCommmonSpectrumMCpPb, markerSizeCommonSpectrumPi0pPb, colorCommonMCpPb, colorCommonMCpPb);
   DrawGammaSetMarkerTGraphErr( widthPi0LHC13b_fix_1_pPb,  markerStyleCommmonSpectrumMCpPb, markerSizeCommonSpectrumPi0pPb, colorCommonMCpPb, colorCommonMCpPb);
   DrawGammaSetMarkerTGraphErr( massEtaLHC13b_fix_1_pPb,  markerStyleCommmonSpectrumMCpPb, markerSizeCommonSpectrumPi0pPb, colorCommonMCpPb, colorCommonMCpPb);
   DrawGammaSetMarkerTGraphErr( widthEtaLHC13b_fix_1_pPb,  markerStyleCommmonSpectrumMCpPb, markerSizeCommonSpectrumPi0pPb, colorCommonMCpPb, colorCommonMCpPb);
   DrawGammaSetMarkerTGraphErr( meanTrackMultTPCDataLHC13b_fix_1_pPb,  markerStyleCommmonSpectrumMCpPb, markerSizeCommonSpectrumPi0pPb, colorCommonMCpPb, colorCommonMCpPb);
   
   DrawGammaSetMarkerTGraphErr( fractionOfGammasLHC13b_fix_2_pPb,  markerStyleCommmonSpectrumMCpPb, markerSizeCommonSpectrumPi0pPb, colorCommonMCpPb, colorCommonMCpPb);
   DrawGammaSetMarkerTGraphErr( fractionOfPi0LHC13b_fix_2_pPb,  markerStyleCommmonSpectrumMCpPb, markerSizeCommonSpectrumPi0pPb, colorCommonMCpPb, colorCommonMCpPb);
   DrawGammaSetMarkerTGraphErr( fractionOfEtaLHC13b_fix_2_pPb,  markerStyleCommmonSpectrumMCpPb, markerSizeCommonSpectrumPi0pPb, colorCommonMCpPb, colorCommonMCpPb);
   DrawGammaSetMarkerTGraphErr( fractionOfWOVtxLHC13b_fix_2_pPb,  markerStyleCommmonSpectrumMCpPb, markerSizeCommonSpectrumPi0pPb, colorCommonMCpPb, colorCommonMCpPb);
   DrawGammaSetMarkerTGraphErr( fractionOfWVtxOutside10cmLHC13b_fix_2_pPb,  markerStyleCommmonSpectrumMCpPb, markerSizeCommonSpectrumPi0pPb, colorCommonMCpPb, colorCommonMCpPb);
   DrawGammaSetMarkerTGraphErr( fractionOfGoodEventsLHC13b_fix_2_pPb,  markerStyleCommmonSpectrumMCpPb, markerSizeCommonSpectrumPi0pPb, colorCommonMCpPb, colorCommonMCpPb);
   DrawGammaSetMarkerTGraphErr( fractionOfNormAllLHC13b_fix_2_pPb,  markerStyleCommmonSpectrumMCpPb, markerSizeCommonSpectrumPi0pPb, colorCommonMCpPb, colorCommonMCpPb);
   DrawGammaSetMarkerTGraphErr( fractionOfNormMinBiasLHC13b_fix_2_pPb,  markerStyleCommmonSpectrumMCpPb, markerSizeCommonSpectrumPi0pPb, colorCommonMCpPb, colorCommonMCpPb);
   DrawGammaSetMarkerTGraphErr( fractionOfPileUpLHC13b_fix_2_pPb,  markerStyleCommmonSpectrumMCpPb, markerSizeCommonSpectrumPi0pPb, colorCommonMCpPb, colorCommonMCpPb);
   DrawGammaSetMarkerTGraphErr( massPi0LHC13b_fix_2_pPb,  markerStyleCommmonSpectrumMCpPb, markerSizeCommonSpectrumPi0pPb, colorCommonMCpPb, colorCommonMCpPb);
   DrawGammaSetMarkerTGraphErr( widthPi0LHC13b_fix_2_pPb,  markerStyleCommmonSpectrumMCpPb, markerSizeCommonSpectrumPi0pPb, colorCommonMCpPb, colorCommonMCpPb);
   DrawGammaSetMarkerTGraphErr( massEtaLHC13b_fix_2_pPb,  markerStyleCommmonSpectrumMCpPb, markerSizeCommonSpectrumPi0pPb, colorCommonMCpPb, colorCommonMCpPb);
   DrawGammaSetMarkerTGraphErr( widthEtaLHC13b_fix_2_pPb,  markerStyleCommmonSpectrumMCpPb, markerSizeCommonSpectrumPi0pPb, colorCommonMCpPb, colorCommonMCpPb);
   DrawGammaSetMarkerTGraphErr( meanTrackMultTPCDataLHC13b_fix_2_pPb,  markerStyleCommmonSpectrumMCpPb, markerSizeCommonSpectrumPi0pPb, colorCommonMCpPb, colorCommonMCpPb);
   
   DrawGammaSetMarkerTGraphErr( fractionOfGammasLHC13b_fix_3_pPb,  markerStyleCommmonSpectrumMCpPb, markerSizeCommonSpectrumPi0pPb, colorCommonMCpPb, colorCommonMCpPb);
   DrawGammaSetMarkerTGraphErr( fractionOfPi0LHC13b_fix_3_pPb,  markerStyleCommmonSpectrumMCpPb, markerSizeCommonSpectrumPi0pPb, colorCommonMCpPb, colorCommonMCpPb);
   DrawGammaSetMarkerTGraphErr( fractionOfEtaLHC13b_fix_3_pPb,  markerStyleCommmonSpectrumMCpPb, markerSizeCommonSpectrumPi0pPb, colorCommonMCpPb, colorCommonMCpPb);
   DrawGammaSetMarkerTGraphErr( fractionOfWOVtxLHC13b_fix_3_pPb,  markerStyleCommmonSpectrumMCpPb, markerSizeCommonSpectrumPi0pPb, colorCommonMCpPb, colorCommonMCpPb);
   DrawGammaSetMarkerTGraphErr( fractionOfWVtxOutside10cmLHC13b_fix_3_pPb,  markerStyleCommmonSpectrumMCpPb, markerSizeCommonSpectrumPi0pPb, colorCommonMCpPb, colorCommonMCpPb);
   DrawGammaSetMarkerTGraphErr( fractionOfGoodEventsLHC13b_fix_3_pPb,  markerStyleCommmonSpectrumMCpPb, markerSizeCommonSpectrumPi0pPb, colorCommonMCpPb, colorCommonMCpPb);
   DrawGammaSetMarkerTGraphErr( fractionOfNormAllLHC13b_fix_3_pPb,  markerStyleCommmonSpectrumMCpPb, markerSizeCommonSpectrumPi0pPb, colorCommonMCpPb, colorCommonMCpPb);
   DrawGammaSetMarkerTGraphErr( fractionOfNormMinBiasLHC13b_fix_3_pPb,  markerStyleCommmonSpectrumMCpPb, markerSizeCommonSpectrumPi0pPb, colorCommonMCpPb, colorCommonMCpPb);
   DrawGammaSetMarkerTGraphErr( fractionOfPileUpLHC13b_fix_3_pPb,  markerStyleCommmonSpectrumMCpPb, markerSizeCommonSpectrumPi0pPb, colorCommonMCpPb, colorCommonMCpPb);
   DrawGammaSetMarkerTGraphErr( massPi0LHC13b_fix_3_pPb,  markerStyleCommmonSpectrumMCpPb, markerSizeCommonSpectrumPi0pPb, colorCommonMCpPb, colorCommonMCpPb);
   DrawGammaSetMarkerTGraphErr( widthPi0LHC13b_fix_3_pPb,  markerStyleCommmonSpectrumMCpPb, markerSizeCommonSpectrumPi0pPb, colorCommonMCpPb, colorCommonMCpPb);
   DrawGammaSetMarkerTGraphErr( massEtaLHC13b_fix_3_pPb,  markerStyleCommmonSpectrumMCpPb, markerSizeCommonSpectrumPi0pPb, colorCommonMCpPb, colorCommonMCpPb);
   DrawGammaSetMarkerTGraphErr( widthEtaLHC13b_fix_3_pPb,  markerStyleCommmonSpectrumMCpPb, markerSizeCommonSpectrumPi0pPb, colorCommonMCpPb, colorCommonMCpPb);
   DrawGammaSetMarkerTGraphErr( meanTrackMultTPCDataLHC13b_fix_3_pPb,  markerStyleCommmonSpectrumMCpPb, markerSizeCommonSpectrumPi0pPb, colorCommonMCpPb, colorCommonMCpPb);
   
   cout << "Plot 40" << endl;
   TCanvas* canvasNGammaEvtDatapPb = new TCanvas("canvasNGammaEvtDatapPb","",200,10,1350,1000);  // gives the page size
   DrawGammaCanvasSettings( canvasNGammaEvtDatapPb, 0.1, 0.04, 0.06, 0.09);
   
   TH2F * histo2DNEvtpPb;
   histo2DNEvtpPb = new TH2F("histo2DNEvtpPb","histo2DNEvtpPb",2450,195340,195680,100,0.1,2 );
   SetStyleHistoTH2ForGraphs(histo2DNEvtpPb, "Run number","#gamma_{cand}/N_{evt}",0.03,0.04, 0.03,0.04, 1.,1.);
   histo2DNEvtpPb->Draw("copy");

   fractionOfGammasLHC13x_pPb->Draw("pesame");
   TLegend* legendDatapPb = new TLegend(0.095,0.945,0.99,1.);
   legendDatapPb->SetFillColor(0);
   legendDatapPb->SetLineColor(0);
   legendDatapPb->SetTextSize(0.04);
   legendDatapPb->SetNColumns(1);
   legendDatapPb->AddEntry(fractionOfGammasLHC13x_pPb,"p-Pb, #sqrt{#it{s}_{_{NN}}} = 5.02 TeV","p");
   legendDatapPb->Draw();

   canvasNGammaEvtDatapPb->SaveAs(Form("%s/FractionOfPhotonsPerEventpPb.%s",outputDir.Data(),suffix.Data()));
   delete canvasNGammaEvtDatapPb;
   
   cout << "Plot 41" << endl;
   TCanvas* canvasNGammaEvtCombpPb = new TCanvas("canvasNGammaEvtCombpPb","",200,10,1350,1000);  // gives the page size
   DrawGammaCanvasSettings( canvasNGammaEvtCombpPb, 0.1, 0.04, 0.12, 0.09);
   
   histo2DNEvtpPb->Draw("copy");
   fractionOfGammasLHC13x_pPb->Draw("pesame");
   fractionOfGammasLHC13b_fix_1_pPb->Draw("pesame");

   TLegend* legendDatapPbComb = new TLegend(0.075,0.91,0.99,1.);
   legendDatapPbComb->SetFillColor(0);
   legendDatapPbComb->SetLineColor(0);
   legendDatapPbComb->SetTextSize(0.04);
   legendDatapPbComb->SetMargin(0.1);
   legendDatapPbComb->SetNColumns(4);
   legendDatapPbComb->AddEntry((TObject*)0, "Data:","");
   legendDatapPbComb->AddEntry(fractionOfGammasLHC13x_pPb,"p-Pb, #sqrt{#it{s}_{_{NN}}} = 5.02 TeV","p");
   legendDatapPbComb->AddEntry((TObject*)0, "MC:  ","");
   legendDatapPbComb->AddEntry(fractionOfGammasLHC13b_fix_1_pPb,"DPMJET","p");
   
   legendDatapPbComb->Draw();

   canvasNGammaEvtCombpPb->SaveAs(Form("%s/FractionOfPhotonsPerEventpPb_WithMC.%s",outputDir.Data(),suffix.Data()));
   delete canvasNGammaEvtCombpPb;

   cout << "Plot 42" << endl;
   TCanvas* canvasNPi0EvtDatapPb = new TCanvas("canvasNPi0EvtDatapPb","",200,10,1350,1000);  // gives the page size
   DrawGammaCanvasSettings( canvasNPi0EvtDatapPb, 0.1, 0.04, 0.12, 0.09);
   
   TH2F * histo2DFracPi0pPb;
   histo2DFracPi0pPb = new TH2F("histo2DFracPi0pPb","histo2DFracPi0pPb",2450,195340,195680,100,0.001,0.006);
   SetStyleHistoTH2ForGraphs(histo2DFracPi0pPb, "Run number","N_{#pi^{0}_{cand}}/N_{evt}",0.03,0.04, 0.03,0.04, 1.,1.3);
   histo2DFracPi0pPb->Draw("copy");

   fractionOfPi0LHC13x_pPb->Draw("pesame");
   fractionOfPi0LHC13b_fix_1_pPb->Draw("pesame");
   
   legendDatapPbComb->Draw();

   canvasNPi0EvtDatapPb->SaveAs(Form("%s/FractionOfPi0PerEventpPb.%s",outputDir.Data(),suffix.Data()));
   delete canvasNPi0EvtDatapPb;

   cout << "Plot 43" << endl;
   TCanvas* canvasMassPi0DatapPb = new TCanvas("canvasMassPi0DatapPb","",200,10,1350,1000);  // gives the page size
   DrawGammaCanvasSettings( canvasMassPi0DatapPb, 0.1, 0.04, 0.06, 0.09);
   
   TH2F * histo2DMassPi0pPb;
   histo2DMassPi0pPb = new TH2F("histo2DMassPi0pPb","histo2DMassPi0pPb",2450,195340,195680,100,0.13,0.145);
   SetStyleHistoTH2ForGraphs(histo2DMassPi0pPb, "Run number","m_{#pi^{0}} (GeV/c^{2})",0.03,0.04, 0.03,0.04, 1.,1.3);
   histo2DMassPi0pPb->Draw("copy");

   massPi0LHC13x_pPb->Draw("pesame");
   massPi0LHC13b_fix_1_pPb->Draw("pesame");
   DrawGammaLines(195340,195680.,0.135, 0.135,1,kGray+2);
   legendDatapPbComb->Draw();
   canvasMassPi0DatapPb->SaveAs(Form("%s/MassPi0_pPb.%s",outputDir.Data(),suffix.Data()));
   delete canvasMassPi0DatapPb;

   cout << "Plot 44" << endl;
   TCanvas* canvasWidthPi0DatapPb = new TCanvas("canvasWidthPi0DatapPb","",200,10,1350,1000);  // gives the page size
   DrawGammaCanvasSettings( canvasWidthPi0DatapPb, 0.1, 0.04, 0.06, 0.09);
   
   TH2F * histo2DWidthPi0pPb;
   histo2DWidthPi0pPb = new TH2F("histo2DWidthPi0pPb","histo2DWidthPi0pPb",2450,195340,195680.,100,0.0,0.015);
   SetStyleHistoTH2ForGraphs(histo2DWidthPi0pPb, "Run number","FWHM_{#pi^{0}} (GeV/c^{2})",0.03,0.04, 0.03,0.04, 1.,1.3);
   histo2DWidthPi0pPb->Draw("copy");

   widthPi0LHC13x_pPb->Draw("pesame");
   widthPi0LHC13b_fix_1_pPb->Draw("pesame");
    legendDatapPbComb->Draw();

   canvasWidthPi0DatapPb->SaveAs(Form("%s/WidthPi0_pPb.%s",outputDir.Data(),suffix.Data()));
   delete canvasWidthPi0DatapPb;
   
   cout << "Plot 45" << endl;
   TCanvas* canvasMultTPCpPb = new TCanvas("canvasMultTPCpPb","",200,10,1350,1000);  // gives the page size
   DrawGammaCanvasSettings( canvasMultTPCpPb, 0.1, 0.04, 0.12, 0.09);
   
   TH2F * histoMultTPCpPb;
   histoMultTPCpPb = new TH2F("histoMultTPCpPb","histoMultTPCpPb",2450,195340,195680,100,0,50);
   SetStyleHistoTH2ForGraphs(histoMultTPCpPb, "Run number","#LT n tracks TPC #GT",0.03,0.04, 0.03,0.04, 1.,1.2);
   histoMultTPCpPb->Draw("copy");


   meanTrackMultTPCDataLHC13x_pPb->Draw("pesame");
   meanTrackMultTPCDataLHC13b_fix_1_pPb->Draw("pesame");
   
   legendDatapPbComb->Draw();

   canvasMultTPCpPb->SaveAs(Form("%s/MeanMultiplicity_TPCTracks_pPb.%s",outputDir.Data(),suffix.Data()));
   delete canvasMultTPCpPb;

   cout << "Plot 46" << endl;
   TCanvas* canvasGoodEventsCombpPb = new TCanvas("canvasGoodEventsCombpPb","",200,10,1350,1000);  // gives the page size
   DrawGammaCanvasSettings( canvasGoodEventsCombpPb, 0.1, 0.04, 0.12, 0.09);

   TH2F * histo2DGoodEventspPb;
   histo2DGoodEventspPb = new TH2F("histo2DGoodEventspPb","histo2DGoodEventspPb",2450,195340,195680,100,0.,1.);
//    histo2DGoodEventspPb->GetXaxis()->SetRangeUser(0.,2100.);
   SetStyleHistoTH2ForGraphs(histo2DGoodEventspPb, "Run number","N^{evt}_{good}/N^{evt}_{Min. Bias}",0.03,0.04, 0.03,0.04, 1.,1.3);
   histo2DGoodEventspPb->Draw("copy");
   
   fractionOfGoodEventsLHC13x_pPb->Draw("pesame");
   fractionOfGoodEventsLHC13b_fix_1_pPb->Draw("pesame");
   
   legendDatapPbComb->Draw();

   canvasGoodEventsCombpPb->SaveAs(Form("%s/FractionOfGoodEvents_pPb.%s",outputDir.Data(),suffix.Data()));
   delete canvasGoodEventsCombpPb;

   cout << "Plot 47" << endl;
   TCanvas* canvasNormAllCombpPb = new TCanvas("canvasNormAllCombpPb","",200,10,1350,1000);  // gives the page size
   DrawGammaCanvasSettings( canvasNormAllCombpPb, 0.1, 0.04, 0.12, 0.09);
   
   TH2F * histo2DNormpPb;
   histo2DNormpPb = new TH2F("histo2DNormpPb","histo2DNormpPb",2450,195340,195680,100,0,1. );
   SetStyleHistoTH2ForGraphs(histo2DNormpPb, "Run number","N^{evt}_{norm}/N^{evt}_{all}",0.03,0.04, 0.03,0.04, 1.,1.3);
   histo2DNormpPb->Draw("copy");

   fractionOfNormAllLHC13x_pPb->Draw("pesame");
   fractionOfNormAllLHC13b_fix_1_pPb->Draw("pesame");
   
   legendDatapPbComb->Draw();

   canvasNormAllCombpPb->SaveAs(Form("%s/FractionOfNormAll_pPb.%s",outputDir.Data(),suffix.Data()));
   delete canvasNormAllCombpPb;
   
   cout << "Plot 48" << endl;
   TCanvas* canvasNormMinBiasCombpPb = new TCanvas("canvasNormMinBiasCombpPb","",200,10,1350,1000);  // gives the page size
   DrawGammaCanvasSettings( canvasNormMinBiasCombpPb, 0.1, 0.04, 0.12, 0.09);
   
   TH2F * histo2DNormMinBiaspPb;
   histo2DNormMinBiaspPb = new TH2F("histo2DNormMinBiaspPb","histo2DNormMinBiaspPb",2450,195340,195680,100,0.,1   );
   SetStyleHistoTH2ForGraphs(histo2DNormMinBiaspPb, "Run number","N^{evt}_{norm}/N^{evt}_{Min. Bias}",0.03,0.04, 0.03,0.04, 1.,1.3);
   histo2DNormMinBiaspPb->Draw("copy");

   fractionOfNormMinBiasLHC13x_pPb->Draw("pesame");
   fractionOfNormMinBiasLHC13b_fix_1_pPb->Draw("pesame");
   
   legendDatapPbComb->Draw();

   canvasNormMinBiasCombpPb->SaveAs(Form("%s/FractionOfNormMinBias_pPb.%s",outputDir.Data(),suffix.Data()));
   delete canvasNormMinBiasCombpPb;
	
}

//    TCanvas* canvasPileUpCombLHC11a10a = new TCanvas("canvasPileUpCombLHC11a10a","",200,10,1350,1000);  // gives the page size
//    DrawGammaCanvasSettings( canvasPileUpCombLHC11a10a, 0.1, 0.04, 0.12, 0.09);
//    
//    TH2F * histo2DNormPileUp;
//    histo2DNormPileUp = new TH2F("histo2DNormPileUp","histo2DNormPileUp",2450,137100,139550,100,0.,0.009  );
// //    histo2DNormPileUp->GetXaxis()->SetRangeUser(0.,2100.);
//    SetStyleHistoTH2ForGraphs(histo2DNormPileUp, "Run number","N^{evt}_{SPD Pile Up}/N^{evt}_{Min. Bias}",0.03,0.04, 0.03,0.04, 1.,1.3);
//    histo2DNormPileUp->Draw("copy");
// 
//    fractionOfPileUpData0005->Draw("pesame");
//    fractionOfPileUpData0510->Draw("pesame");
//    fractionOfPileUpData1020->Draw("pesame");
//    fractionOfPileUpData2040->Draw("pesame");
//    fractionOfPileUpData4060->Draw("pesame");
//    fractionOfPileUpData6080->Draw("pesame");
// 
//    fractionOfPileUpLHC11a10a0005->Draw("pesame");
//    fractionOfPileUpLHC11a10a0510->Draw("pesame");
//    fractionOfPileUpLHC11a10a1020->Draw("pesame");
//    fractionOfPileUpLHC11a10a2040->Draw("pesame");
//    fractionOfPileUpLHC11a10a4060->Draw("pesame");
//    fractionOfPileUpLHC11a10a6080->Draw("pesame");
// 
//    legendDataComb->Draw();
//    legendMC->Draw();
// 
//    canvasPileUpCombLHC11a10a->SaveAs(Form("%s/FractionOfPileUp_WithMCLHC11a10a.%s",outputDir.Data(),suffix.Data()));
//    delete canvasPileUpCombLHC11a10a;
// 
//    TCanvas* canvasWOVtxCombLHC11a10a = new TCanvas("canvasWOVtxCombLHC11a10a","",200,10,1350,1000);  // gives the page size
//    DrawGammaCanvasSettings( canvasWOVtxCombLHC11a10a, 0.1, 0.04, 0.12, 0.09);
//    canvasWOVtxCombLHC11a10a->SetLogy(1);
//    TH2F * histo2DNormWOVtx;
//    histo2DNormWOVtx = new TH2F("histo2DNormWOVtx","histo2DNormWOVtx",2450,137100,139550,100,1.e-10,1);
// //    histo2DNormWOVtx->GetXaxis()->SetRangeUser(0.,2100.);
//    SetStyleHistoTH2ForGraphs(histo2DNormWOVtx, "Run number","N^{evt}_{w/o Vtx}/N^{evt}_{Min. Bias}",0.03,0.04, 0.03,0.04, 1.,1.3);
//    histo2DNormWOVtx->Draw("copy");
// 
//    fractionOfWOVtxData0005->Draw("pesame");
//    fractionOfWOVtxData0510->Draw("pesame");
//    fractionOfWOVtxData1020->Draw("pesame");
//    fractionOfWOVtxData2040->Draw("pesame");
//    fractionOfWOVtxData4060->Draw("pesame");
//    fractionOfWOVtxData6080->Draw("pesame");
// 
//    fractionOfWOVtxLHC11a10a0005->Draw("pesame");
//    fractionOfWOVtxLHC11a10a0510->Draw("pesame");
//    fractionOfWOVtxLHC11a10a1020->Draw("pesame");
//    fractionOfWOVtxLHC11a10a2040->Draw("pesame");
//    fractionOfWOVtxLHC11a10a4060->Draw("pesame");
//    fractionOfWOVtxLHC11a10a6080->Draw("pesame");
// 
//    legendDataComb->Draw();
//    legendMC->Draw();
// 
//    canvasWOVtxCombLHC11a10a->SaveAs(Form("%s/FractionOfWOVtx_WithMCLHC11a10a.%s",outputDir.Data(),suffix.Data()));
//    delete canvasWOVtxCombLHC11a10a;
// 
//    TCanvas* canvasWVtxOutside10cmCombLHC11a10a = new TCanvas("canvasWVtxOutside10cmCombLHC11a10a","",200,10,1350,1000);  // gives the page size
//    DrawGammaCanvasSettings( canvasWVtxOutside10cmCombLHC11a10a, 0.1, 0.04, 0.12, 0.09);
//    
//    TH2F * histo2DNormWVtxOutside10cm;
//    histo2DNormWVtxOutside10cm = new TH2F("histo2DNormWVtxOutside10cm","histo2DNormWVtxOutside10cm",2450,137100,139550,100,0.,0.26);
// //    histo2DNormWVtxOutside10cm->GetXaxis()->SetRangeUser(0.,2100.);
//    SetStyleHistoTH2ForGraphs(histo2DNormWVtxOutside10cm, "Run number","N^{evt}_{Z Vtx > 10cm}/N^{evt}_{Min. Bias}",0.03,0.04, 0.03,0.04, 1.,1.3);
//    histo2DNormWVtxOutside10cm->Draw("copy");
// 
//    fractionOfWVtxOutside10cmData0005->Draw("pesame");
//    fractionOfWVtxOutside10cmData0510->Draw("pesame");
//    fractionOfWVtxOutside10cmData1020->Draw("pesame");
//    fractionOfWVtxOutside10cmData2040->Draw("pesame");
//    fractionOfWVtxOutside10cmData4060->Draw("pesame");
//    fractionOfWVtxOutside10cmData6080->Draw("pesame");
// 
//    fractionOfWVtxOutside10cmLHC11a10a0005->Draw("pesame");
//    fractionOfWVtxOutside10cmLHC11a10a0510->Draw("pesame");
//    fractionOfWVtxOutside10cmLHC11a10a1020->Draw("pesame");
//    fractionOfWVtxOutside10cmLHC11a10a2040->Draw("pesame");
//    fractionOfWVtxOutside10cmLHC11a10a4060->Draw("pesame");
//    fractionOfWVtxOutside10cmLHC11a10a6080->Draw("pesame");
// 
//    legendDataComb->Draw();
//    legendMC->Draw();
// 
//    canvasWVtxOutside10cmCombLHC11a10a->SaveAs(Form("%s/FractionOfWVtxOutside10cm_WithMCLHC11a10a.%s",outputDir.Data(),suffix.Data()));
//    delete canvasWVtxOutside10cmCombLHC11a10a;
// 
//    
//    
//    TCanvas* canvasPileUpCombLHC11a10a_bis = new TCanvas("canvasPileUpCombLHC11a10a_bis","",200,10,1350,1000);  // gives the page size
//    DrawGammaCanvasSettings( canvasPileUpCombLHC11a10a_bis, 0.1, 0.04, 0.12, 0.09);
//    
//    histo2DNormPileUp->Draw("copy");
// 
//    fractionOfPileUpData0005->Draw("pesame");
//    fractionOfPileUpData0510->Draw("pesame");
//    fractionOfPileUpData1020->Draw("pesame");
//    fractionOfPileUpData2040->Draw("pesame");
//    fractionOfPileUpData4060->Draw("pesame");
//    fractionOfPileUpData6080->Draw("pesame");
// 
//    fractionOfPileUpLHC11a10a_bis0005->Draw("pesame");
//    fractionOfPileUpLHC11a10a_bis0510->Draw("pesame");
//    fractionOfPileUpLHC11a10a_bis1020->Draw("pesame");
//    fractionOfPileUpLHC11a10a_bis2040->Draw("pesame");
//    fractionOfPileUpLHC11a10a_bis4060->Draw("pesame");
//    fractionOfPileUpLHC11a10a_bis6080->Draw("pesame");
// 
//    legendDataComb->Draw();
//    legendMC->Draw();
// 
//    canvasPileUpCombLHC11a10a_bis->SaveAs(Form("%s/FractionOfPileUp_WithMCLHC11a10a_bis.%s",outputDir.Data(),suffix.Data()));
//    delete canvasPileUpCombLHC11a10a_bis;
// 
//    TCanvas* canvasWOVtxCombLHC11a10a_bis = new TCanvas("canvasWOVtxCombLHC11a10a_bis","",200,10,1350,1000);  // gives the page size
//    DrawGammaCanvasSettings( canvasWOVtxCombLHC11a10a_bis, 0.1, 0.04, 0.12, 0.09);
//    
//    histo2DNormWOVtx->Draw("copy");
// 
//    fractionOfWOVtxData0005->Draw("pesame");
//    fractionOfWOVtxData0510->Draw("pesame");
//    fractionOfWOVtxData1020->Draw("pesame");
//    fractionOfWOVtxData2040->Draw("pesame");
//    fractionOfWOVtxData4060->Draw("pesame");
//    fractionOfWOVtxData6080->Draw("pesame");
// 
//    fractionOfWOVtxLHC11a10a_bis0005->Draw("pesame");
//    fractionOfWOVtxLHC11a10a_bis0510->Draw("pesame");
//    fractionOfWOVtxLHC11a10a_bis1020->Draw("pesame");
//    fractionOfWOVtxLHC11a10a_bis2040->Draw("pesame");
//    fractionOfWOVtxLHC11a10a_bis4060->Draw("pesame");
//    fractionOfWOVtxLHC11a10a_bis6080->Draw("pesame");
// 
//    legendDataComb->Draw();
//    legendMC->Draw();
// 
//    canvasWOVtxCombLHC11a10a_bis->SaveAs(Form("%s/FractionOfWOVtx_WithMCLHC11a10a_bis.%s",outputDir.Data(),suffix.Data()));
//    delete canvasWOVtxCombLHC11a10a_bis;
// 
//    TCanvas* canvasWVtxOutside10cmCombLHC11a10a_bis = new TCanvas("canvasWVtxOutside10cmCombLHC11a10a_bis","",200,10,1350,1000);  // gives the page size
//    DrawGammaCanvasSettings( canvasWVtxOutside10cmCombLHC11a10a_bis, 0.1, 0.04, 0.12, 0.09);
//    
//    histo2DNormWVtxOutside10cm->Draw("copy");
// 
//    fractionOfWVtxOutside10cmData0005->Draw("pesame");
//    fractionOfWVtxOutside10cmData0510->Draw("pesame");
//    fractionOfWVtxOutside10cmData1020->Draw("pesame");
//    fractionOfWVtxOutside10cmData2040->Draw("pesame");
//    fractionOfWVtxOutside10cmData4060->Draw("pesame");
//    fractionOfWVtxOutside10cmData6080->Draw("pesame");
// 
//    fractionOfWVtxOutside10cmLHC11a10a_bis0005->Draw("pesame");
//    fractionOfWVtxOutside10cmLHC11a10a_bis0510->Draw("pesame");
//    fractionOfWVtxOutside10cmLHC11a10a_bis1020->Draw("pesame");
//    fractionOfWVtxOutside10cmLHC11a10a_bis2040->Draw("pesame");
//    fractionOfWVtxOutside10cmLHC11a10a_bis4060->Draw("pesame");
//    fractionOfWVtxOutside10cmLHC11a10a_bis6080->Draw("pesame");
// 
//    legendDataComb->Draw();
//    legendMC->Draw();
// 
//    canvasWVtxOutside10cmCombLHC11a10a_bis->SaveAs(Form("%s/FractionOfWVtxOutside10cm_WithMCLHC11a10a_bis.%s",outputDir.Data(),suffix.Data()));
//    delete canvasWVtxOutside10cmCombLHC11a10a_bis;
// 
//    TCanvas* canvasPileUpCombLHC11a10b_bis = new TCanvas("canvasPileUpCombLHC11a10b_bis","",200,10,1350,1000);  // gives the page size
//    DrawGammaCanvasSettings( canvasPileUpCombLHC11a10b_bis, 0.1, 0.04, 0.12, 0.09);
//    
//    histo2DNormPileUp->Draw("copy");
// 
//    fractionOfPileUpData0005->Draw("pesame");
//    fractionOfPileUpData0510->Draw("pesame");
//    fractionOfPileUpData1020->Draw("pesame");
//    fractionOfPileUpData2040->Draw("pesame");
//    fractionOfPileUpData4060->Draw("pesame");
//    fractionOfPileUpData6080->Draw("pesame");
// 
//    fractionOfPileUpLHC11a10b_bis0005->Draw("pesame");
//    fractionOfPileUpLHC11a10b_bis0510->Draw("pesame");
//    fractionOfPileUpLHC11a10b_bis1020->Draw("pesame");
//    fractionOfPileUpLHC11a10b_bis2040->Draw("pesame");
//    fractionOfPileUpLHC11a10b_bis4060->Draw("pesame");
//    fractionOfPileUpLHC11a10b_bis6080->Draw("pesame");
// 
//    legendDataComb->Draw();
//    legendMC->Draw();
// 
//    canvasPileUpCombLHC11a10b_bis->SaveAs(Form("%s/FractionOfPileUp_WithMCLHC11a10b_bis.%s",outputDir.Data(),suffix.Data()));
//    delete canvasPileUpCombLHC11a10b_bis;
// 
//    TCanvas* canvasWOVtxCombLHC11a10b_bis = new TCanvas("canvasWOVtxCombLHC11a10b_bis","",200,10,1350,1000);  // gives the page size
//    DrawGammaCanvasSettings( canvasWOVtxCombLHC11a10b_bis, 0.1, 0.04, 0.12, 0.09);
//    
//    histo2DNormWOVtx->Draw("copy");
// 
//    fractionOfWOVtxData0005->Draw("pesame");
//    fractionOfWOVtxData0510->Draw("pesame");
//    fractionOfWOVtxData1020->Draw("pesame");
//    fractionOfWOVtxData2040->Draw("pesame");
//    fractionOfWOVtxData4060->Draw("pesame");
//    fractionOfWOVtxData6080->Draw("pesame");
// 
//    fractionOfWOVtxLHC11a10b_bis0005->Draw("pesame");
//    fractionOfWOVtxLHC11a10b_bis0510->Draw("pesame");
//    fractionOfWOVtxLHC11a10b_bis1020->Draw("pesame");
//    fractionOfWOVtxLHC11a10b_bis2040->Draw("pesame");
//    fractionOfWOVtxLHC11a10b_bis4060->Draw("pesame");
//    fractionOfWOVtxLHC11a10b_bis6080->Draw("pesame");
// 
//    legendDataComb->Draw();
//    legendMC->Draw();
// 
//    canvasWOVtxCombLHC11a10b_bis->SaveAs(Form("%s/FractionOfWOVtx_WithMCLHC11a10b_bis.%s",outputDir.Data(),suffix.Data()));
//    delete canvasWOVtxCombLHC11a10b_bis;
// 
//    TCanvas* canvasWVtxOutside10cmCombLHC11a10b_bis = new TCanvas("canvasWVtxOutside10cmCombLHC11a10b_bis","",200,10,1350,1000);  // gives the page size
//    DrawGammaCanvasSettings( canvasWVtxOutside10cmCombLHC11a10b_bis, 0.1, 0.04, 0.12, 0.09);
//    
//    histo2DNormWVtxOutside10cm->Draw("copy");
// 
//    fractionOfWVtxOutside10cmData0005->Draw("pesame");
//    fractionOfWVtxOutside10cmData0510->Draw("pesame");
//    fractionOfWVtxOutside10cmData1020->Draw("pesame");
//    fractionOfWVtxOutside10cmData2040->Draw("pesame");
//    fractionOfWVtxOutside10cmData4060->Draw("pesame");
//    fractionOfWVtxOutside10cmData6080->Draw("pesame");
// 
//    fractionOfWVtxOutside10cmLHC11a10b_bis0005->Draw("pesame");
//    fractionOfWVtxOutside10cmLHC11a10b_bis0510->Draw("pesame");
//    fractionOfWVtxOutside10cmLHC11a10b_bis1020->Draw("pesame");
//    fractionOfWVtxOutside10cmLHC11a10b_bis2040->Draw("pesame");
//    fractionOfWVtxOutside10cmLHC11a10b_bis4060->Draw("pesame");
//    fractionOfWVtxOutside10cmLHC11a10b_bis6080->Draw("pesame");
// 
//    legendDataComb->Draw();
//    legendMC->Draw();
// 
//    canvasWVtxOutside10cmCombLHC11a10b_bis->SaveAs(Form("%s/FractionOfWVtxOutside10cm_WithMCLHC11a10b_bis.%s",outputDir.Data(),suffix.Data()));
//    delete canvasWVtxOutside10cmCombLHC11a10b_bis;
//    TCanvas* canvasPileUpCombLHC13d2 = new TCanvas("canvasPileUpCombLHC13d2","",200,10,1350,1000);  // gives the page size
//    DrawGammaCanvasSettings( canvasPileUpCombLHC13d2, 0.1, 0.04, 0.12, 0.09);
//    
//    histo2DNormPileUp->Draw("copy");
// 
//    fractionOfPileUpData0005->Draw("pesame");
//    fractionOfPileUpData0510->Draw("pesame");
//    fractionOfPileUpData1020->Draw("pesame");
//    fractionOfPileUpData2040->Draw("pesame");
//    fractionOfPileUpData4060->Draw("pesame");
//    fractionOfPileUpData6080->Draw("pesame");
// 
//    fractionOfPileUpLHC13d20005->Draw("pesame");
//    fractionOfPileUpLHC13d20510->Draw("pesame");
//    fractionOfPileUpLHC13d21020->Draw("pesame");
//    fractionOfPileUpLHC13d22040->Draw("pesame");
//    fractionOfPileUpLHC13d24060->Draw("pesame");
//    fractionOfPileUpLHC13d26080->Draw("pesame");
// 
//    legendDataComb->Draw();
//    legendMC->Draw();
// 
//    canvasPileUpCombLHC13d2->SaveAs(Form("%s/FractionOfPileUp_WithMCLHC13d2.%s",outputDir.Data(),suffix.Data()));
//    delete canvasPileUpCombLHC13d2;
// 
//    TCanvas* canvasWOVtxCombLHC13d2 = new TCanvas("canvasWOVtxCombLHC13d2","",200,10,1350,1000);  // gives the page size
//    DrawGammaCanvasSettings( canvasWOVtxCombLHC13d2, 0.1, 0.04, 0.12, 0.09);
//    
//    histo2DNormWOVtx->Draw("copy");
// 
//    fractionOfWOVtxData0005->Draw("pesame");
//    fractionOfWOVtxData0510->Draw("pesame");
//    fractionOfWOVtxData1020->Draw("pesame");
//    fractionOfWOVtxData2040->Draw("pesame");
//    fractionOfWOVtxData4060->Draw("pesame");
//    fractionOfWOVtxData6080->Draw("pesame");
// 
//    fractionOfWOVtxLHC13d20005->Draw("pesame");
//    fractionOfWOVtxLHC13d20510->Draw("pesame");
//    fractionOfWOVtxLHC13d21020->Draw("pesame");
//    fractionOfWOVtxLHC13d22040->Draw("pesame");
//    fractionOfWOVtxLHC13d24060->Draw("pesame");
//    fractionOfWOVtxLHC13d26080->Draw("pesame");
// 
//    legendDataComb->Draw();
//    legendMC->Draw();
// 
//    canvasWOVtxCombLHC13d2->SaveAs(Form("%s/FractionOfWOVtx_WithMCLHC13d2.%s",outputDir.Data(),suffix.Data()));
//    delete canvasWOVtxCombLHC13d2;
// 
//    TCanvas* canvasWVtxOutside10cmCombLHC13d2 = new TCanvas("canvasWVtxOutside10cmCombLHC13d2","",200,10,1350,1000);  // gives the page size
//    DrawGammaCanvasSettings( canvasWVtxOutside10cmCombLHC13d2, 0.1, 0.04, 0.12, 0.09);
//    
//    histo2DNormWVtxOutside10cm->Draw("copy");
// 
//    fractionOfWVtxOutside10cmData0005->Draw("pesame");
//    fractionOfWVtxOutside10cmData0510->Draw("pesame");
//    fractionOfWVtxOutside10cmData1020->Draw("pesame");
//    fractionOfWVtxOutside10cmData2040->Draw("pesame");
//    fractionOfWVtxOutside10cmData4060->Draw("pesame");
//    fractionOfWVtxOutside10cmData6080->Draw("pesame");
// 
//    fractionOfWVtxOutside10cmLHC13d20005->Draw("pesame");
//    fractionOfWVtxOutside10cmLHC13d20510->Draw("pesame");
//    fractionOfWVtxOutside10cmLHC13d21020->Draw("pesame");
//    fractionOfWVtxOutside10cmLHC13d22040->Draw("pesame");
//    fractionOfWVtxOutside10cmLHC13d24060->Draw("pesame");
//    fractionOfWVtxOutside10cmLHC13d26080->Draw("pesame");
// 
//    legendDataComb->Draw();
//    legendMC->Draw();
// 
//    canvasWVtxOutside10cmCombLHC13d2->SaveAs(Form("%s/FractionOfWVtxOutside10cm_WithMCLHC13d2.%s",outputDir.Data(),suffix.Data()));
//    delete canvasWVtxOutside10cmCombLHC13d2;
