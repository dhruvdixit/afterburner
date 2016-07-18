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
#include "TFitResultPtr.h"
#include "TFitResult.h"
#include "CommonHeaders/PlottingGammaConversionHistos.h"
#include "CommonHeaders/PlottingGammaConversionAdditional.h"
#include "CommonHeaders/FittingGammaConversion.h"
#include "CommonHeaders/ConversionFunctionsBasicsAndLabeling.h"
#include "CommonHeaders/ConversionFunctions.h"
#include "CommonHeaders/CombinationFunctions.h"
#include "CombineMesonMeasurementsPbPbLHC11hV2.h"


extern TRandom*	gRandom;
extern TBenchmark*	gBenchmark;
extern TSystem*	gSystem;
extern TMinuit*  	gMinuit;	

struct SysErrorConversion {
	Double_t value;
	Double_t error;
	//	TString name;
};

void CombineMesonMeasurementsPbPbLHC11hV2(TString meson = "Eta", 	
										TString fileNamePCM = "", 
										TString fileNameEMCalFull = "",  
										TString suffix = "pdf", 
										Bool_t PaperPi0 = kTRUE,
										Bool_t noXerrorBars = kTRUE,
										TString isMC= "", 
										TString thesisPlots = "", 
										TString bWCorrection=""){	
	
	gROOT->Reset();	
	gROOT->SetStyle("Plain");
	
	StyleSettingsThesis();	
	SetPlotStyle();
	
	TString date = ReturnDateString();
	TString dateForOutput 			= ReturnDateStringForOutput();
	cout << dateForOutput.Data() << endl;
	
	
	//___________________________________ Labels definition _____________________________________________
	
	TString collisionSystem2760GeV 		= "Pb-Pb, #sqrt{#it{s}_{_{NN}}} = 2.76 TeV";	
	TString collisionSystemPbPb0010 	= "0-10% Pb-Pb #sqrt{s_{_{NN}}} = 2.76 TeV"	;      
	TString collisionSystemPbPb2050 	= "20-50% Pb-Pb #sqrt{s_{_{NN}}} = 2.76 TeV";      
	
	TString collisionSystemPP2760GeV 	= "pp, #sqrt{#it{s}} = 2.76 TeV";		
	TString collisionSystemPP7TeV 		= "pp, #sqrt{#it{s}} = 7 TeV";		
	TString collisionSystemPP900GeV 	= "pp #sqrt{#it{s}} = 0.9 TeV";		
	TString collisionSystempPb 			= "p-Pb  #sqrt{s_{_{NN}}} = 5.02 TeV";
	
	
	TLatex *labelPreliminary = new TLatex(0.62,0.92,"ALICE Preliminary");
	SetStyleTLatex( labelPreliminary, 0.035,4);
	
	TLatex *labelFactorLower;
	if(meson.CompareTo("Pi0")==0){
		labelFactorLower = new TLatex(0.89,0.34,"x 4");
	} else if(meson.CompareTo("Eta")==0){
		labelFactorLower = new TLatex(0.88,0.335,"x 4");
	}
	SetStyleTLatex( labelFactorLower, 0.035,4,colorCombo0010);

	TLatex *labelFactorUpper;
	if(meson.CompareTo("Pi0")==0){
		labelFactorUpper = new TLatex(0.415,0.89,"x 4");
	} else if(meson.CompareTo("Eta")==0){
		labelFactorUpper = new TLatex(0.42,0.89,"x 4");
	}
	SetStyleTLatex( labelFactorUpper, 0.035,4,colorCombo0010);

	TLatex *labelEnergy = new TLatex(0.6,0.88,collisionSystem2760GeV.Data());
	SetStyleTLatex( labelEnergy, 0.035,4);
	TLatex *labelSyst;
	if(meson.CompareTo("Pi0")==0){
		labelSyst= new TLatex(0.6,0.84,"#pi^{0} #rightarrow #gamma#gamma");
	} else if(meson.CompareTo("Eta")==0){
		labelSyst= new TLatex(0.6,0.84,"#eta #rightarrow #gamma#gamma");
	}
	SetStyleTLatex(labelSyst, 0.035,4);

	
	TLatex *labelEnergyInvYieldSectionPi0LHC11h = new TLatex(0.6,0.88,collisionSystem2760GeV.Data());
	SetStyleTLatex( labelEnergyInvYieldSectionPi0LHC11h, 0.035,4);
	TLatex *labelDetSysInvYieldSectionPi0LHC11h;
	if(meson.CompareTo("Pi0")==0){
		labelDetSysInvYieldSectionPi0LHC11h= new TLatex(0.6,0.84,"#pi^{0} #rightarrow #gamma#gamma");
	} else if(meson.CompareTo("Eta")==0){
		labelDetSysInvYieldSectionPi0LHC11h= new TLatex(0.6,0.84,"#eta #rightarrow #gamma#gamma");
	}
	SetStyleTLatex( labelDetSysInvYieldSectionPi0LHC11h, 0.035,4);

	TLatex *labelEnergyInvYieldSectionPi0LHC11hnoPrelim = new TLatex(0.6,0.92,collisionSystem2760GeV.Data());
	SetStyleTLatex( labelEnergyInvYieldSectionPi0LHC11hnoPrelim, 0.035,4);
	TLatex *labelDetSysInvYieldSectionPi0LHC11hnoPrelim;
	if(meson.CompareTo("Pi0")==0){
		labelDetSysInvYieldSectionPi0LHC11hnoPrelim= new TLatex(0.6,0.88,"#pi^{0} #rightarrow #gamma#gamma");
	} else if(meson.CompareTo("Eta")==0){
		labelDetSysInvYieldSectionPi0LHC11hnoPrelim= new TLatex(0.6,0.88,"#eta #rightarrow #gamma#gamma");
	}
	SetStyleTLatex( labelDetSysInvYieldSectionPi0LHC11hnoPrelim, 0.035,4);

	TLatex *labelDetSysInvYieldSectionPi0LHC11hwithPP;
	if(meson.CompareTo("Pi0")==0){
		labelDetSysInvYieldSectionPi0LHC11hwithPP= new TLatex(0.62,0.88,"#pi^{0} #rightarrow #gamma#gamma");
	} else if(meson.CompareTo("Eta")==0){
		labelDetSysInvYieldSectionPi0LHC11hwithPP= new TLatex(0.62,0.88,"#eta #rightarrow #gamma#gamma");
	}
	SetStyleTLatex( labelDetSysInvYieldSectionPi0LHC11hwithPP, 0.035,4);


	
	Double_t mesonMassExpectPi0 = TDatabasePDG::Instance()->GetParticle(111)->Mass();
	Double_t mesonMassExpectEta = TDatabasePDG::Instance()->GetParticle(221)->Mass();
	
	Width_t		widthLinesBoxes		= 1.4;
	Width_t		widthCommonFit		= 2;
	
	// Definition of colors, styles and markers sizes
	Color_t		colorComb			= kMagenta+2;
	Style_t		markerStyleComb		= 20;
	Size_t		markerSizeComb		= 2;
	
	Color_t 	colorCombLowPt 			= GetDefaultColorDiffDetectors("Comb", kFALSE, kFALSE, kFALSE);
	Color_t 	colorCombHighPt 		= GetDefaultColorDiffDetectors("Comb", kFALSE, kFALSE, kTRUE);
	Style_t 	markerStyleCombLowPt	= 20;
	Style_t 	markerStyleCombHighPt	= 20;	
	Size_t 		markerSizeComparison = 2;
	
	TString 	nameMeasGlobal[11] 	= {"PCM", "PHOS", "EMCal", "PCM-PHOS", "PCM - EMCal", "PCM-Dalitz", "PHOS-Dalitz", "EMCal-Dalitz", "EMCal high pT", "EMCal merged", "PCM 2010"};
	Color_t 	colorDet[11];
	Color_t 	colorDetMC[11];
	Style_t 	markerStyleDet[11];
	Style_t 	markerStyleDetMC[11];
	Size_t 		markerSizeDet[11];
	Size_t 		markerSizeDetMC[11];

	Style_t 	styleMarkerNLOMuHalf	= 24;
	Style_t 	styleMarkerNLOMuOne		= 27;
	Style_t 	styleMarkerNLOMuTwo		= 30;
	Style_t 	styleLineNLOMuHalf		= 8;
	Style_t 	styleLineNLOMuOne		= 7;
	Style_t 	styleLineNLOMuTwo		= 4;
	Style_t 	styleLineNLOMuTwoBKK	= 3;
	Style_t 	styleLineNLOMuTwoDSS	= 6;
	Size_t		sizeMarkerNLO			= 1;
	Width_t		widthLineNLO			= 2.;

	for (Int_t i = 0; i < 11; i++){
		colorDet[i]					= GetDefaultColorDiffDetectors(nameMeasGlobal[i].Data(), kFALSE, kFALSE, kTRUE);
		colorDetMC[i]				= GetDefaultColorDiffDetectors(nameMeasGlobal[i].Data(), kTRUE, kFALSE, kTRUE);
		markerStyleDet[i]			= GetDefaultMarkerStyleDiffDetectors(nameMeasGlobal[i].Data(), kFALSE);
		markerStyleDetMC[i]			= GetDefaultMarkerStyleDiffDetectors(nameMeasGlobal[i].Data(), kTRUE);
		markerSizeDet[i]			= GetDefaultMarkerSizeDiffDetectors(nameMeasGlobal[i].Data(), kFALSE)*2;
		markerSizeDetMC[i]			= GetDefaultMarkerSizeDiffDetectors(nameMeasGlobal[i].Data(), kTRUE)*2;
	}	
	
	Double_t normErr0010 = pow(pow(xSection2760GeVErrpp/(xSection2760GeVpp*1e3),2)+pow((tAAErr0010/tAA0010),2)+pow((commonCentralityErr0010/100),2),0.5);
	Double_t normErr2040 = pow(pow(xSection2760GeVErrpp/(xSection2760GeVpp*1e3),2)+pow((tAAErr2040/tAA2040),2)+pow((commonCentralityErr2040/100),2),0.5);
	Double_t normErr2050 = pow(pow(xSection2760GeVErrpp/(xSection2760GeVpp*1e3),2)+pow((tAAErr2050/tAA2050),2)+pow((commonCentralityErr2040/100),2),0.5);

	TBox* boxErrorNorm0010_Single = CreateBoxConv(colorComb0005Box, 0.2, 1.-normErr0010 , 0.5, 1.+normErr0010);
	TBox* boxErrorNorm2040_Single = CreateBoxConv(colorComb2040Box, 0.2, 1.-normErr2040 , 0.5, 1.+normErr2040);
	TBox* boxErrorNorm2050_Single = CreateBoxConv(colorCombo2050, 0.2, 1.-normErr2050 , 0.5, 1.+normErr2050);

	TBox* boxErrorNorm0010 = CreateBoxConv(kRed-7, 0.25, 1.-normErr2050 , 0.5, 1.+normErr2050);
	TBox* boxErrorNorm2050 = CreateBoxConv(kAzure-4, 0.5, 1.-normErr2050 , 0.75, 1.+normErr2050);

	TBox* boxErrorNorm0010Only = CreateBoxConv(kRed-7, 0.25, 1.-normErr2050 , 0.5, 1.+normErr2050);
	TBox* boxErrorNorm2050Only = CreateBoxConv(kAzure-4, 0.25, 1.-normErr2050 , 0.5, 1.+normErr2050);

	
	
	
	//___________________________________ Declaration of files _____________________________________________
	
	TString fileNameTheory					= "ExternalInputPbPb/Theory/TheoryCompilationPbPbforLHC11h.root";	
// 	TFile* fileDataALICEChargedHadrons = new TFile("ExternalInputPbPb/IdentifiedCharged/PbPb_RAA_sigma_2760GeV_20120809.root");
// 	TFile* fileChargedPionInputPrelim2012 = new TFile("ExternalInputPbPb/IdentifiedCharged/ChargedPionSpectraPbPb_4_Apr_2014.root");

	TString filePPpublished					= "CombinedResultsPaperX_18_Feb_2014.root";
	//with EMCal refernce: "LHC11hExternalInputs/CombinedResultsPaperPP2760GeV_2015_08_25.root";  //
	TString filePPEtaPCM					= "LHC11hExternalInputs/CombinedResultsEta2760X_2015_09_01.root"; //"CombinedResultsEta2760X_2015_07_10.root";
// 	TString fileEtaScaledEMCal				= "LHC11hExternalInputs/ppReferenceSpectraEMCal27LowandHighPt.root";
	TString fileNamePCMPublished 			= "LHC11hExternalInputs/data_PCMResults_PbPb_2.76TeV_LHC10h.root";
	TString fileNamePHOS 					= "ExternalInputPbPb/PHOS/LHC10h_PHOS_pi0_PbPb_06022014.root";
// 	TString fileNameChargedSpectra			= "ExternalInputPbPb/IdentifiedCharged/JIRA_PWGLF-258/PbPb276.fullpT.INEL.20140329.root";
	TString fileNameChargedRatios			= "ExternalInputPbPb/IdentifiedCharged/JIRA_PWGLF-258/PbPb276.fullpT.RATIOS.20140329.root";
	TString fileNameChargedPionRAA			= "ExternalInputPbPb/IdentifiedCharged/JIRA_PWGLF-258/RAA_Pion_08052014.root";
	TString fileNameChargedKaonRAA			= "ExternalInputPbPb/IdentifiedCharged/JIRA_PWGLF-258/RAA_Kaon_08052014.root";
	TString	fileNameDataOtherEnergyInput 	= "ExternalInputPbPb/OtherExperiments/DataCompilationFromOtherEnergiesPbPbWithEta.root";
	
	TString outputDir 						= Form("%s/%s/CombineMesonMeasurements2760GeVCentTogether%s",suffix.Data(),dateForOutput.Data(),bWCorrection.Data());
	TString nameFinalResDat 				= Form("%s/CombinedResults%s_FitResults.dat",outputDir.Data(),bWCorrection.Data());
	cout << outputDir.Data() << endl;
	cout << fileNamePCM.Data() << endl;	
	cout << fileNameEMCalFull.Data() << endl;

	gSystem->Exec("mkdir -p "+outputDir);
 	gSystem->Exec(Form("cp %s %s/InputPHOS.root", fileNamePHOS.Data(), outputDir.Data()));
 	gSystem->Exec(Form("cp %s %s/InputPCM.root", fileNamePCM.Data(), outputDir.Data()));
	gSystem->Exec(Form("cp %s %s/InputPCMPublished.root", fileNamePCMPublished.Data(), outputDir.Data()));
	gSystem->Exec(Form("cp LHC11hExternalInputs/%s %s/InputEMCalFull.root", fileNameEMCalFull.Data(), outputDir.Data()));
	gSystem->Exec(Form("cp %s %s/Theory.root", fileNameTheory.Data(), outputDir.Data()));
	gSystem->Exec(Form("cp %s %s/ChargedRatios.root", fileNameChargedRatios.Data(), outputDir.Data()));
	gSystem->Exec(Form("cp %s %s/ChargedPionRAA.root", fileNameChargedPionRAA.Data(), outputDir.Data()));
	gSystem->Exec(Form("cp %s %s/ChargedKaonRAA.root", fileNameChargedKaonRAA.Data(), outputDir.Data()));
	gSystem->Exec(Form("cp %s %s/OtherExperimentsInput.root", fileNameDataOtherEnergyInput.Data(), outputDir.Data()));
	
	TString paperPlots = Form("%s/PaperPlotsforPreview_%s",outputDir.Data(),dateForOutput.Data());
	gSystem->Exec("mkdir -p "+paperPlots);
	Bool_t thesis 							= kFALSE;
	if(thesisPlots.CompareTo("thesis") == 0){
		thesis 								= kTRUE;
	}
	
	TString prefix2							= "";	
	if (isMC.CompareTo("kTRUE")==0){ 
		prefix2 = "MC";
	} else {	
		prefix2 = "Data";
	}

	
	
	//*********************************************************************************************************//
	//*************************************        Theory inputs      *****************************************//
	//*********************************************************************************************************//
	TFile* fileTheoryGraphs = new TFile(fileNameTheory);

	
	//**************************** EPOS ****************************//
	TFile* filePredictionEpos = new TFile("ExternalInputPbPb/Theory/EPOS/pi0_eta_forPbPb11h_NoUrQMD.root");

	TGraphErrors *graphEPOSPi0_0010 = (TGraphErrors*)fileTheoryGraphs->Get("epos_pi0_pt_cent0_10");
	TGraphErrors *graphEPOSEta_0010 = (TGraphErrors*)fileTheoryGraphs->Get("epos_eta_pt_cent0_10");

	
// // // 	TH1D *histoEPOSPi0_0010 = (TH1D*)filePredictionEpos->Get("pi0_pt_cent0_10");
// // // 	TH1D *histoEPOSPi0_2050 = (TH1D*)filePredictionEpos->Get("pi0_pt_cent20_50");
// // // 
// // // 	TH1D *histoEPOSEta_0010 = (TH1D*)filePredictionEpos->Get("eta_pt_cent0_10");
// // // 	TH1D *histoEPOSEta_2050 = (TH1D*)filePredictionEpos->Get("eta_pt_cent20_50");
// // // 	
// // // 	TH1D *histoEPOSpred_0010;
// // // 	TH1D *histoEPOSpred_2050;
// // // 	if(meson.CompareTo("Pi0")==0){
// // // 		histoEPOSpred_0010 = (TH1D*)histoEPOSPi0_0010->Clone("histoEPOSpred_0010");
// // // 		histoEPOSpred_2050 = (TH1D*)histoEPOSPi0_2050->Clone("histoEPOSpred_2050");
// // // 					
// // // 	} else if(meson.CompareTo("Eta")==0){
// // // 		histoEPOSpred_0010 = (TH1D*)histoEPOSEta_0010->Clone("histoEPOSpred_0010");
// // // 		histoEPOSpred_2050 = (TH1D*)histoEPOSEta_2050->Clone("histoEPOSpred_2050");
// // // 		
// // // 	}
// // // 
// // // 	Int_t nbins = histoEPOSpred_0010->GetNbinsX();
// // // 	Double_t xRebin[nbins];
// // // 	for(Int_t b = 0; b<nbins; b++){
// // // // 				cout << "bin center: " << histoEPOSpred_0010->GetBinCenter(b+1) << endl;
// // // // 				cout << "low edge: " << histoEPOSpred_0010->GetBinLowEdge(b+1) << endl;
// // // 		if(histoEPOSpred_0010->GetBinCenter(b+1) < 3.){
// // // 			xRebin[b] = histoEPOSpred_0010->GetBinLowEdge(b+1);
// // // // 						cout << "new low edge: " << xRebin[b] << endl;
// // // 		} else {
// // // 			xRebin[b] = xRebin[b-1] + 1.5;
// // // 			cout << "new low edge: " << xRebin[b] << endl;
// // // 		}
// // // 	}
// // // 	Int_t rebinFactor = histoEPOSpred_0010->FindBin(xRebin[0]+1.5) - histoEPOSpred_0010->FindBin(xRebin[0]);
// // // 	cout << "rebin factor: " << rebinFactor << endl;
// // // 
// // // 	TH1D* histoEPOSRebin_0010 = (TH1D*)histoEPOSpred_0010->Rebin(nbins-1,"rebinEPOSPi0_0010",xRebin);
// // // 	TH1D* histoEPOSRebin_2050 = (TH1D*)histoEPOSpred_2050->Rebin(nbins-1,"rebinEPOSPi0_2050",xRebin);
// // // 	TH1D* DeltaPt  = new TH1D("DeltaPt","",nbins-1,xRebin);
// // // 	TH1D* DeltaPt2050  = new TH1D("DeltaPt2050","",nbins-1,xRebin);
// // // 	for(Int_t b = 0; b<nbins; b++){
// // // 		if(histoEPOSRebin_0010->GetBinCenter(b+1) < 3.){
// // // 			DeltaPt->SetBinContent(b+1,1);
// // // 			DeltaPt2050->SetBinContent(b+1,1);
// // // 		} else {
// // // 			DeltaPt->SetBinContent(b+1,rebinFactor);
// // // 			DeltaPt2050->SetBinContent(b+1,rebinFactor);
// // // 		}
// // // 	}
// // // 	DeltaPt->Sumw2();
// // // 	histoEPOSRebin_0010->Divide(DeltaPt);
// // // 	DeltaPt2050->Sumw2();
// // // 	histoEPOSRebin_2050->Divide(DeltaPt2050);
// // // 
// // // 	
// // // 	for (Int_t i = 1; i < histoEPOSRebin_0010->GetNbinsX()+1 ; i++){
// // // 		Double_t newBinContent = histoEPOSRebin_0010->GetBinContent(i)/(2*TMath::Pi()*histoEPOSRebin_0010->GetBinCenter(i));
// // // 		Double_t newBinError = histoEPOSRebin_0010->GetBinError(i)/(2*TMath::Pi()*histoEPOSRebin_0010->GetBinCenter(i));
// // // 		histoEPOSRebin_0010->SetBinContent(i,newBinContent);
// // // 		histoEPOSRebin_0010->SetBinError(i,newBinError);
// // // 	}
// // // 	for (Int_t i = 1; i < histoEPOSRebin_2050->GetNbinsX()+1 ; i++){
// // // 		Double_t newBinContent = histoEPOSRebin_2050->GetBinContent(i)/(2*TMath::Pi()*histoEPOSRebin_2050->GetBinCenter(i));
// // // 		Double_t newBinError = histoEPOSRebin_2050->GetBinError(i)/(2*TMath::Pi()*histoEPOSRebin_2050->GetBinCenter(i));
// // // 		histoEPOSRebin_2050->SetBinContent(i,newBinContent);
// // // 		histoEPOSRebin_2050->SetBinError(i,newBinError);
// // // 	}
// // // 
// // // 	Double_t xRebinEtaToPi0[nbins];
// // // 	for(Int_t b = 0; b<nbins; b++){
// // // 		if(histoEPOSpred_0010->GetBinCenter(b+1) < 3.){
// // // 			xRebinEtaToPi0[b] = histoEPOSpred_0010->GetBinLowEdge(b+1);
// // // 		} else {
// // // 			xRebinEtaToPi0[b] = xRebinEtaToPi0[b-1] + 1.5;
// // // 		}
// // // 	}
// // // 	Int_t rebinFactorEtaToPi0 = histoEPOSpred_0010->FindBin(xRebinEtaToPi0[0]+1.5) - histoEPOSpred_0010->FindBin(xRebinEtaToPi0[0]);
// // // 	cout << "rebin factor: " << rebinFactorEtaToPi0 << endl;
// // // 
// // // 
// // // 	TH1D* histoEtaforRatioEPOS_0010 = (TH1D*)histoEPOSEta_0010->Clone("histoEtaforRatioEPOS_0010");
// // // 	TH1D* histoEtaforRatioEPOS_2050 = (TH1D*)histoEPOSEta_2050->Clone("histoEtaforRatioEPOS_2050");
// // // 	TH1D* histoPi0forRatioEPOS_0010 = (TH1D*)histoEPOSPi0_0010->Clone("histoPi0forRatioEPOS_0010");
// // // 	TH1D* histoPi0forRatioEPOS_2050 = (TH1D*)histoEPOSPi0_2050->Clone("histoPi0forRatioEPOS_2050");
// // // 	
// // // 	TH1D* histoEtaforRatioEPOSRebin_0010 = (TH1D*)histoEPOSEta_0010->Rebin(nbins-1,"histoEtaforRatioEPOSRebin_0010",xRebinEtaToPi0);
// // // 	TH1D* histoEtaforRatioEPOSRebin_2050 = (TH1D*)histoEPOSEta_2050->Rebin(nbins-1,"histoEtaforRatioEPOSRebin_2050",xRebinEtaToPi0);
// // // 	TH1D* histoPi0forRatioEPOSRebin_0010 = (TH1D*)histoEPOSPi0_0010->Rebin(nbins-1,"histoPi0forRatioEPOSRebin_0010",xRebinEtaToPi0);
// // // 	TH1D* histoPi0forRatioEPOSRebin_2050 = (TH1D*)histoEPOSPi0_2050->Rebin(nbins-1,"histoPi0forRatioEPOSRebin_2050",xRebinEtaToPi0);
// // // 
// // // 	TH1D* DeltaPtEtaToPi0  = new TH1D("DeltaPtEtaToPi0","",nbins-1,xRebinEtaToPi0);
// // // 	TH1D* DeltaPtEtaToPi02050  = new TH1D("DeltaPtEtaToPi02050","",nbins-1,xRebinEtaToPi0);
// // // 	for(Int_t b = 0; b<nbins; b++){
// // // 		if(histoEPOSRebin_0010->GetBinCenter(b+1) < 3.){
// // // 			DeltaPtEtaToPi0->SetBinContent(b+1,1);
// // // 			DeltaPtEtaToPi02050->SetBinContent(b+1,1);
// // // 		} else {
// // // 			DeltaPtEtaToPi0->SetBinContent(b+1,rebinFactorEtaToPi0);
// // // 			DeltaPtEtaToPi02050->SetBinContent(b+1,rebinFactorEtaToPi0);
// // // 		}
// // // 	}
// // // 	DeltaPtEtaToPi0->Sumw2();
// // // 	DeltaPtEtaToPi02050->Sumw2();
// // // 	histoEtaforRatioEPOSRebin_0010->Divide(DeltaPtEtaToPi0);
// // // 	histoEtaforRatioEPOSRebin_2050->Divide(DeltaPtEtaToPi02050);
// // // 	histoPi0forRatioEPOSRebin_0010->Divide(DeltaPtEtaToPi0);
// // // 	histoPi0forRatioEPOSRebin_2050->Divide(DeltaPtEtaToPi02050);
// // // 	
// // // 	TH1D *histoEtaToPi0EPOSRebin_0010 = (TH1D*)histoEtaforRatioEPOSRebin_0010->Clone("histoEtaToPi0EPOSRebin_0010");
// // // 	histoEtaToPi0EPOSRebin_0010->Divide(histoEtaToPi0EPOSRebin_0010,histoPi0forRatioEPOSRebin_0010,1.,1.,"");
// // // 	TH1D *histoEtaToPi0EPOSRebin_2050 = (TH1D*)histoEtaforRatioEPOSRebin_2050->Clone("histoEtaToPi0EPOSRebin_2050");
// // // 	histoEtaToPi0EPOSRebin_2050->Divide(histoEtaToPi0EPOSRebin_2050,histoPi0forRatioEPOSRebin_2050,1.,1.,"");
	
// 	TH1D *histoEPOSPi0_0010 = (TH1D*)filePredictionEpos->Get("rb_pi0_pt_cent0_10");
// 	TH1D *histoEPOSEta_0010 = (TH1D*)filePredictionEpos->Get("rb_eta_pt_cent0_10");
	
	TH1D *histoEPOSPi0_0010 = (TH1D*)GraphToHist(graphEPOSPi0_0010,14,"histoEPOSPi0_0010");
	TH1D *histoEPOSEta_0010 = (TH1D*)GraphToHist(graphEPOSEta_0010,14,"histoEPOSEta_0010");
	TH1D *histoEPOSPi0_2050 = (TH1D*)filePredictionEpos->Get("rb_pi0_pt_cent20_50");
	TH1D *histoEPOSEta_2050 = (TH1D*)filePredictionEpos->Get("rb_eta_pt_cent20_50");

	
	TH1D *histoEPOSpred_0010;
	TH1D *histoEPOSpred_2050;
	if(meson.CompareTo("Pi0")==0){
		histoEPOSpred_0010 = (TH1D*)histoEPOSPi0_0010->Clone("histoEPOSpred_0010");
		histoEPOSpred_2050 = (TH1D*)histoEPOSPi0_2050->Clone("histoEPOSpred_2050");
					
	} else if(meson.CompareTo("Eta")==0){
		histoEPOSpred_0010 = (TH1D*)histoEPOSEta_0010->Clone("histoEPOSpred_0010");
		histoEPOSpred_2050 = (TH1D*)histoEPOSEta_2050->Clone("histoEPOSpred_2050");
		
	}

// 	TH1D* histoEPOSRebin_0010 = (TH1D*)histoEPOSpred_0010->Clone("histoEPOSpred_0010");
//from here down the rebin for the 0-10 only
	Int_t nbins = histoEPOSpred_0010->GetNbinsX();
	Double_t xRebin[nbins];
	for(Int_t b = 0; b<nbins; b++){
		if(histoEPOSpred_0010->GetBinCenter(b+1) < 4.){
			xRebin[b] = histoEPOSpred_0010->GetBinLowEdge(b+1);
		} else {
			xRebin[b] = xRebin[b-1] + 1.;
			cout << "new low edge: " << xRebin[b] << endl;
		}
	}
	Int_t rebinFactor = histoEPOSpred_0010->FindBin(xRebin[0]+1.) - histoEPOSpred_0010->FindBin(xRebin[0]);
	cout << "rebin factor: " << rebinFactor << endl;
	TH1D* histoEPOSRebin_0010 = (TH1D*)histoEPOSpred_0010->Rebin(nbins-1,"rebinEPOSPi0_0010",xRebin);
	TH1D* DeltaPt  = new TH1D("DeltaPt","",nbins-1,xRebin);
	for(Int_t b = 0; b<nbins; b++){
		if(histoEPOSRebin_0010->GetBinCenter(b+1) < 4.){
			DeltaPt->SetBinContent(b+1,1);
		} else {
			DeltaPt->SetBinContent(b+1,rebinFactor);
		}
	}
	DeltaPt->Sumw2();
	histoEPOSRebin_0010->Divide(DeltaPt);
// until here
	
	for (Int_t i = 1; i < histoEPOSRebin_0010->GetNbinsX()+1 ; i++){
		Double_t newBinContent = histoEPOSRebin_0010->GetBinContent(i)/(2*TMath::Pi()*histoEPOSRebin_0010->GetBinCenter(i));
		Double_t newBinError = histoEPOSRebin_0010->GetBinError(i)/(2*TMath::Pi()*histoEPOSRebin_0010->GetBinCenter(i));
		histoEPOSRebin_0010->SetBinContent(i,newBinContent);
		histoEPOSRebin_0010->SetBinError(i,newBinError);
	}
	TH1D* histoEPOSRebin_2050 = (TH1D*)histoEPOSpred_2050->Clone("histoEPOSpred_2050");
	for (Int_t i = 1; i < histoEPOSRebin_2050->GetNbinsX()+1 ; i++){
		Double_t newBinContent = histoEPOSRebin_2050->GetBinContent(i)/(2*TMath::Pi()*histoEPOSRebin_2050->GetBinCenter(i));
		Double_t newBinError = histoEPOSRebin_2050->GetBinError(i)/(2*TMath::Pi()*histoEPOSRebin_2050->GetBinCenter(i));
		histoEPOSRebin_2050->SetBinContent(i,newBinContent);
		histoEPOSRebin_2050->SetBinError(i,newBinError);
	}

	TH1D* histoEtaforRatioEPOS_0010 = (TH1D*)histoEPOSEta_0010->Clone("histoEtaforRatioEPOS_0010");
	TH1D* histoEtaforRatioEPOS_2050 = (TH1D*)histoEPOSEta_2050->Clone("histoEtaforRatioEPOS_2050");
	TH1D* histoPi0forRatioEPOS_0010 = (TH1D*)histoEPOSPi0_0010->Clone("histoPi0forRatioEPOS_0010");
	TH1D* histoPi0forRatioEPOS_2050 = (TH1D*)histoEPOSPi0_2050->Clone("histoPi0forRatioEPOS_2050");
	
	TH1D *histoEtaToPi0EPOSRebin_0010 = (TH1D*)histoEtaforRatioEPOS_0010->Clone("histoEtaToPi0EPOSRebin_0010");
	histoEtaToPi0EPOSRebin_0010->Divide(histoEtaToPi0EPOSRebin_0010,histoPi0forRatioEPOS_0010,1.,1.,"");
	TH1D *histoEtaToPi0EPOSRebin_2050 = (TH1D*)histoEtaforRatioEPOS_2050->Clone("histoEtaToPi0EPOSRebin_2050");
	histoEtaToPi0EPOSRebin_2050->Divide(histoEtaToPi0EPOSRebin_2050,histoPi0forRatioEPOS_2050,1.,1.,"");
	
	
		
	//**************************** pQCD calculation ****************************//
	TGraphAsymmErrors *graphNLOCalcmuHalfDSS14InvSecPi02760GeV = (TGraphAsymmErrors*)fileTheoryGraphs->Get("graphNLOCalcmuHalfDSS14InvSecPi02760GeV");
	TGraphAsymmErrors *graphNLOCalcmuHalfDSS14InvYieldPi02760GeV = (TGraphAsymmErrors*)fileTheoryGraphs->Get("graphNLOCalcmuHalfDSS14InvSecPi02760GeV");
// 	graphNLOCalcmuHalfDSS14InvYieldPi02760GeV->RemovePoint(0);
// 	graphNLOCalcmuHalfDSS14InvYieldPi02760GeV = ScaleGraph(graphNLOCalcmuHalfDSS14InvYieldPi02760GeV,1./xSection2760GeVppINEL);
	
	TGraphAsymmErrors *graphNLOCalcmuTwoDSS14InvSecPi02760GeV = (TGraphAsymmErrors*)fileTheoryGraphs->Get("graphNLOCalcmuTwoDSS14InvSecPi02760GeV");
	TGraphAsymmErrors *graphNLOCalcmuTwoDSS14InvYieldPi02760GeV = (TGraphAsymmErrors*)fileTheoryGraphs->Get("graphNLOCalcmuTwoDSS14InvSecPi02760GeV");
// 	graphNLOCalcmuTwoDSS14InvYieldPi02760GeV->RemovePoint(0);
// 	graphNLOCalcmuTwoDSS14InvYieldPi02760GeV = ScaleGraph(graphNLOCalcmuTwoDSS14InvYieldPi02760GeV,1./xSection2760GeVppINEL);

	TGraphAsymmErrors* graphNLOCalcmuHalfDSS14InvSecPi02760GeVNcoll0010 = (TGraphAsymmErrors*)graphNLOCalcmuHalfDSS14InvSecPi02760GeV->Clone("graphNLOCalcmuHalfDSS14InvSecPi02760GeVNcoll0010");
	graphNLOCalcmuHalfDSS14InvSecPi02760GeVNcoll0010->RemovePoint(0);
	graphNLOCalcmuHalfDSS14InvSecPi02760GeVNcoll0010 = ScaleGraph(graphNLOCalcmuHalfDSS14InvSecPi02760GeVNcoll0010,nColl0010*4/xSection2760GeVppINEL);
	
	TGraphAsymmErrors* graphNLOCalcmuTwoDSS14InvSecPi02760GeVNcoll0010 = (TGraphAsymmErrors*)graphNLOCalcmuTwoDSS14InvSecPi02760GeV->Clone("graphNLOCalcmuTwoDSS14InvSecPi02760GeVNcoll0010");
	graphNLOCalcmuTwoDSS14InvSecPi02760GeVNcoll0010->RemovePoint(0);
	graphNLOCalcmuTwoDSS14InvSecPi02760GeVNcoll0010 = ScaleGraph(graphNLOCalcmuTwoDSS14InvSecPi02760GeVNcoll0010,nColl0010*4/xSection2760GeVppINEL);
	
	TGraphAsymmErrors* graphNLOCalcmuHalfDSS14InvSecPi02760GeVNcoll2050 = (TGraphAsymmErrors*)graphNLOCalcmuHalfDSS14InvSecPi02760GeV->Clone("graphNLOCalcmuHalfDSS14InvSecPi02760GeVNcoll2050");
	graphNLOCalcmuHalfDSS14InvSecPi02760GeVNcoll2050->RemovePoint(0);
	graphNLOCalcmuHalfDSS14InvSecPi02760GeVNcoll2050 = ScaleGraph(graphNLOCalcmuHalfDSS14InvSecPi02760GeVNcoll2050,nColl2050/xSection2760GeVppINEL);
	
	TGraphAsymmErrors* graphNLOCalcmuTwoDSS14InvSecPi02760GeVNcoll2050 = (TGraphAsymmErrors*)graphNLOCalcmuTwoDSS14InvSecPi02760GeV->Clone("graphNLOCalcmuTwoDSS14InvSecPi02760GeVNcoll2050");
	graphNLOCalcmuTwoDSS14InvSecPi02760GeVNcoll2050->RemovePoint(0);
	graphNLOCalcmuTwoDSS14InvSecPi02760GeVNcoll2050 = ScaleGraph(graphNLOCalcmuTwoDSS14InvSecPi02760GeVNcoll2050,nColl2050/xSection2760GeVppINEL);

	
	TGraphAsymmErrors *graphNLOCalcDSS14InvSecPi02760GeV = (TGraphAsymmErrors*)fileTheoryGraphs->Get("graphNLOCalcDSS14InvCrossSecPi02760GeV");
	TGraphAsymmErrors *graphNLOCalcDSS14InvYieldPi02760GeV = (TGraphAsymmErrors*)fileTheoryGraphs->Get("graphNLOCalcDSS14InvYieldPi02760GeV");
	TGraphAsymmErrors *graphNLOCalcDSS14InvYieldPi02760GeVScaledNcoll0010 = (TGraphAsymmErrors*)fileTheoryGraphs->Get("graphNLOCalcDSS14InvYieldPi02760GeV");
	graphNLOCalcDSS14InvYieldPi02760GeVScaledNcoll0010->RemovePoint(0);
	graphNLOCalcDSS14InvYieldPi02760GeVScaledNcoll0010 = ScaleGraph(graphNLOCalcDSS14InvYieldPi02760GeVScaledNcoll0010,nColl0010*4);
	TGraphAsymmErrors *graphNLOCalcDSS14InvYieldPi02760GeVScaledNcoll2050 = (TGraphAsymmErrors*)fileTheoryGraphs->Get("graphNLOCalcDSS14InvYieldPi02760GeV");
	graphNLOCalcDSS14InvYieldPi02760GeVScaledNcoll2050->RemovePoint(0);
	graphNLOCalcDSS14InvYieldPi02760GeVScaledNcoll2050 = ScaleGraph(graphNLOCalcDSS14InvYieldPi02760GeVScaledNcoll2050,nColl2050);

	
	TGraphAsymmErrors* graphNLOCalcDSS14InvYieldPi0Band = (TGraphAsymmErrors*)fileTheoryGraphs->Get("graphNLOCalcDSS14InvCrossSecPi02760GeV");
	Double_t *yPi0PointDSS14muHalf = graphNLOCalcmuHalfDSS14InvSecPi02760GeV->GetY();
	Double_t *yPi0PointDSS14muOne = graphNLOCalcDSS14InvSecPi02760GeV->GetY();
	Double_t *yPi0PointDSS14muTwo  = graphNLOCalcmuTwoDSS14InvSecPi02760GeV->GetY();
	for(Int_t i =0; i<graphNLOCalcDSS14InvYieldPi0Band->GetN(); i++){	
		graphNLOCalcDSS14InvYieldPi0Band->SetPointEYhigh(i,yPi0PointDSS14muTwo[i]-yPi0PointDSS14muOne[i]);
		graphNLOCalcDSS14InvYieldPi0Band->SetPointEYlow(i,yPi0PointDSS14muOne[i]-yPi0PointDSS14muHalf[i]);
	}
	graphNLOCalcDSS14InvYieldPi0Band->RemovePoint(0);
	graphNLOCalcDSS14InvYieldPi0Band = ScaleGraph(graphNLOCalcDSS14InvYieldPi0Band,1./xSection2760GeVppINEL);
	
	
	TGraphAsymmErrors* graphNLOCalcmuHalfDSS07InvSecEta2760GeV = (TGraphAsymmErrors*)fileTheoryGraphs->Get("graphNLOCalcmuHalfDSS07InvSecEta2760GeV");
	TGraphAsymmErrors* graphNLOCalcmuHalfDSS07InvYieldEta2760GeV = (TGraphAsymmErrors*)fileTheoryGraphs->Get("graphNLOCalcmuHalfDSS07InvSecEta2760GeV");
// 	graphNLOCalcmuHalfDSS07InvYieldEta2760GeV->RemovePoint(0);
// 	graphNLOCalcmuHalfDSS07InvYieldEta2760GeV = ScaleGraph(graphNLOCalcmuHalfDSS07InvYieldEta2760GeV,1./xSection2760GeVppINEL);
	TGraphAsymmErrors* graphNLOCalcmuTwoDSS07InvSecEta2760GeV = (TGraphAsymmErrors*)fileTheoryGraphs->Get("graphNLOCalcmuTwoDSS07InvSecEta2760GeV");
	TGraphAsymmErrors* graphNLOCalcmuTwoDSS07InvYieldEta2760GeV = (TGraphAsymmErrors*)fileTheoryGraphs->Get("graphNLOCalcmuTwoDSS07InvSecEta2760GeV");
// 	graphNLOCalcmuTwoDSS07InvYieldEta2760GeV->RemovePoint(0);
// 	graphNLOCalcmuTwoDSS07InvYieldEta2760GeV = ScaleGraph(graphNLOCalcmuTwoDSS07InvYieldEta2760GeV,1./xSection2760GeVppINEL);

	TGraphAsymmErrors* graphNLOCalcmuHalfDSS07InvSecEta2760GeVNcoll0010 = (TGraphAsymmErrors*)graphNLOCalcmuHalfDSS07InvSecEta2760GeV->Clone("graphNLOCalcmuHalfDSS07InvSecEta2760GeVNcoll0010");
	graphNLOCalcmuHalfDSS07InvSecEta2760GeVNcoll0010->RemovePoint(0);
	graphNLOCalcmuHalfDSS07InvSecEta2760GeVNcoll0010 = ScaleGraph(graphNLOCalcmuHalfDSS07InvSecEta2760GeVNcoll0010,nColl0010*4/xSection2760GeVppINEL);
	
	TGraphAsymmErrors* graphNLOCalcmuTwoDSS07InvSecEta2760GeVNcoll0010 = (TGraphAsymmErrors*)graphNLOCalcmuTwoDSS07InvSecEta2760GeV->Clone("graphNLOCalcmuTwoDSS07InvSecEta2760GeVNcoll0010");
	graphNLOCalcmuTwoDSS07InvSecEta2760GeVNcoll0010->RemovePoint(0);
	graphNLOCalcmuTwoDSS07InvSecEta2760GeVNcoll0010 = ScaleGraph(graphNLOCalcmuTwoDSS07InvSecEta2760GeVNcoll0010,nColl0010*4/xSection2760GeVppINEL);

	
	
	TGraphAsymmErrors* graphNLOCalcmuHalfDSS07InvSecEta2760GeVNcoll2050 = (TGraphAsymmErrors*)graphNLOCalcmuHalfDSS07InvSecEta2760GeV->Clone("graphNLOCalcmuHalfDSS07InvSecEta2760GeVNcoll2050");
	graphNLOCalcmuHalfDSS07InvSecEta2760GeVNcoll2050->RemovePoint(0);
	graphNLOCalcmuHalfDSS07InvSecEta2760GeVNcoll2050 = ScaleGraph(graphNLOCalcmuHalfDSS07InvSecEta2760GeVNcoll2050,nColl2050/xSection2760GeVppINEL);
	
	TGraphAsymmErrors* graphNLOCalcmuTwoDSS07InvSecEta2760GeVNcoll2050 = (TGraphAsymmErrors*)graphNLOCalcmuTwoDSS07InvSecEta2760GeV->Clone("graphNLOCalcmuTwoDSS07InvSecEta2760GeVNcoll2050");
	graphNLOCalcmuTwoDSS07InvSecEta2760GeVNcoll2050->RemovePoint(0);
	graphNLOCalcmuTwoDSS07InvSecEta2760GeVNcoll2050 = ScaleGraph(graphNLOCalcmuTwoDSS07InvSecEta2760GeVNcoll2050,nColl2050/xSection2760GeVppINEL);

	
	TGraphAsymmErrors* graphNLOCalcDSS07InvSecEta2760GeV = (TGraphAsymmErrors*)fileTheoryGraphs->Get("graphNLOCalcDSS07InvCrossSecEta2760GeV");
	TGraphAsymmErrors* graphNLOCalcDSS07InvYieldEta2760GeV = (TGraphAsymmErrors*)fileTheoryGraphs->Get("graphNLOCalcDSS07InvYieldEta2760GeV");
	
	TGraphAsymmErrors* graphNLOCalcDSS07InvYieldEta2760GeVScaledNcoll0010 = (TGraphAsymmErrors*)fileTheoryGraphs->Get("graphNLOCalcDSS07InvYieldEta2760GeV");
	graphNLOCalcDSS07InvYieldEta2760GeVScaledNcoll0010 = ScaleGraph(graphNLOCalcDSS07InvYieldEta2760GeVScaledNcoll0010,nColl0010*4);
	graphNLOCalcDSS07InvYieldEta2760GeVScaledNcoll0010->RemovePoint(0);

	TGraphAsymmErrors* graphNLOCalcDSS07InvYieldEta2760GeVScaledNcoll2050 = (TGraphAsymmErrors*)fileTheoryGraphs->Get("graphNLOCalcDSS07InvYieldEta2760GeV");
	graphNLOCalcDSS07InvYieldEta2760GeVScaledNcoll2050 = ScaleGraph(graphNLOCalcDSS07InvYieldEta2760GeVScaledNcoll2050,nColl2050);
	graphNLOCalcDSS07InvYieldEta2760GeVScaledNcoll2050->RemovePoint(0);
	
	
	TGraphAsymmErrors* graphNLOCalcDSS07InvYieldEtaBand = (TGraphAsymmErrors*)fileTheoryGraphs->Get("graphNLOCalcDSS07InvCrossSecEta2760GeV");
	Double_t *yEtaPointDSS07muHalf = graphNLOCalcmuHalfDSS07InvSecEta2760GeV->GetY();
	Double_t *yEtaPointDSS07muOne = graphNLOCalcDSS07InvSecEta2760GeV->GetY();
	Double_t *yEtaPointDSS07muTwo  = graphNLOCalcmuTwoDSS07InvSecEta2760GeV->GetY();
	for(Int_t i =0; i<graphNLOCalcDSS07InvYieldEtaBand->GetN(); i++){	
		graphNLOCalcDSS07InvYieldEtaBand->SetPointEYhigh(i,yEtaPointDSS07muTwo[i]-yEtaPointDSS07muOne[i]);
		graphNLOCalcDSS07InvYieldEtaBand->SetPointEYlow(i,yEtaPointDSS07muOne[i]-yEtaPointDSS07muHalf[i]);
	}
	graphNLOCalcDSS07InvYieldEtaBand->RemovePoint(0);
	graphNLOCalcDSS07InvYieldEtaBand = ScaleGraph(graphNLOCalcDSS07InvYieldEtaBand,1./xSection2760GeVppINEL);
	
	
	
	//**************************** Cracow model ****************************//	
	TGraphAsymmErrors *TheoryCracowPi0LowPt_0010 = (TGraphAsymmErrors*)fileTheoryGraphs->Get("TheoryCracowPi0LowPt_0010");
	TGraphAsymmErrors *TheoryCracowPi0LowPt_2050 = (TGraphAsymmErrors*)fileTheoryGraphs->Get("TheoryCracowPi0LowPt_2050");

	TGraphAsymmErrors *TheoryCracowEtaLowPt_0010 = (TGraphAsymmErrors*)fileTheoryGraphs->Get("TheoryCracowEtaLowPt_0010");
	TGraphAsymmErrors *TheoryCracowEtaLowPt_2050 = (TGraphAsymmErrors*)fileTheoryGraphs->Get("TheoryCracowEtaLowPt_2050");

	TGraphAsymmErrors* TheoryCracowLowPt_0010 = NULL;
	TGraphAsymmErrors* TheoryCracowLowPt_2050 = NULL;
	
	TGraphAsymmErrors* TheoryCracowEtaToPi0LowPt_0010 = (TGraphAsymmErrors*)fileTheoryGraphs->Get("TheoryCracowEtaToPi0LowPt_0010");
	TGraphAsymmErrors* TheoryCracowEtaToPi0LowPt_2050 = (TGraphAsymmErrors*)fileTheoryGraphs->Get("TheoryCracowEtaToPi0LowPt_2050");
	
	if(meson.CompareTo("Pi0")==0){
		
		TheoryCracowLowPt_0010 = (TGraphAsymmErrors*)TheoryCracowPi0LowPt_0010->Clone("TheoryCracowLowPt_0010"); 
		TheoryCracowLowPt_2050 = (TGraphAsymmErrors*)TheoryCracowPi0LowPt_2050->Clone("TheoryCracowLowPt_2050"); 
		
	} else if(meson.CompareTo("Eta")==0){

		TheoryCracowLowPt_0010 = (TGraphAsymmErrors*)TheoryCracowEtaLowPt_0010->Clone("TheoryCracowLowPt_0010"); 
		TheoryCracowLowPt_2050 = (TGraphAsymmErrors*)TheoryCracowEtaLowPt_2050->Clone("TheoryCracowLowPt_2050"); 

	}

	TheoryCracowLowPt_0010 = ScaleGraph(TheoryCracowLowPt_0010,4);

	
	
	//**************************** Jet Quenching NLO arXiv:1506.00838 ****************************//
	graphPi0JetQuenching18 = (TGraph*)fileTheoryGraphs->Get("graphPi0JetQuenching18_0010");
	graphPi0JetQuenching22 = (TGraph*)fileTheoryGraphs->Get("graphPi0JetQuenching22_0010");
	graphPi0JetQuenching26 = (TGraph*)fileTheoryGraphs->Get("graphPi0JetQuenching26_0010");
	
	graphEtaJetQuenching18 = (TGraph*)fileTheoryGraphs->Get("graphEtaJetQuenching18_0010");
	graphEtaJetQuenching22 = (TGraph*)fileTheoryGraphs->Get("graphEtaJetQuenching22_0010");
	graphEtaJetQuenching26 = (TGraph*)fileTheoryGraphs->Get("graphEtaJetQuenching26_0010");
	
	graphEtatoPi0RatioJetQuenching18 = (TGraph*)fileTheoryGraphs->Get("graphEtatoPi0RatioJetQuenching18_0010");
	graphEtatoPi0RatioJetQuenching22 = (TGraph*)fileTheoryGraphs->Get("graphEtatoPi0RatioJetQuenching22_0010");
	graphEtatoPi0RatioJetQuenching26 = (TGraph*)fileTheoryGraphs->Get("graphEtatoPi0RatioJetQuenching26_0010");
	
	
	TGraphAsymmErrors* graphPi0RAAJetQuenching_0010 = (TGraphAsymmErrors*)fileTheoryGraphs->Get("graphPi0RAAJetQuenching_0010");
	TGraphAsymmErrors* graphEtaRAAJetQuenching_0010 = (TGraphAsymmErrors*)fileTheoryGraphs->Get("graphEtaRAAJetQuenching_0010");
	TGraphAsymmErrors* graphEtaToPi0JetQuenching_0010 = (TGraphAsymmErrors*)fileTheoryGraphs->Get("graphEtaToPi0JetQuenching_0010");
	
	
	//**************************** WHDG ****************************//
	gWHDG_Raa_0510 = (TGraphAsymmErrors*)fileTheoryGraphs->Get("graphWHDGRAA0510");
	gWHDG_Raa_0005 = (TGraphAsymmErrors*)fileTheoryGraphs->Get("graphWHDGRAA0005");
	gWHDG_Raa_0010 = (TGraphAsymmErrors*)fileTheoryGraphs->Get("graphWHDGRAA0010");
	gWHDG_Raa_2040 = (TGraphAsymmErrors*)fileTheoryGraphs->Get("graphWHDGRAA2040");

	gWHDG_Eta_Raa_0010 = (TGraphAsymmErrors*)fileTheoryGraphs->Get("graphWHDGetaRAA0010");
	gWHDG_Eta_Raa_2050 = (TGraphAsymmErrors*)fileTheoryGraphs->Get("graphWHDGetaRAA2050");
	
	
	
	//*********************************************************************************************************//
	//********************************        Other experiment inputs     *************************************//
	//*********************************************************************************************************//
	
	TFile* fileDataOtherEnergies = new TFile(fileNameDataOtherEnergyInput);

	graphWA98_17_3GeVRAA_0013= (TGraphErrors*)fileDataOtherEnergies->Get("graphWA98RAA_0013");

	graphPHENIX200GeVRAA_0010= (TGraphErrors*)fileDataOtherEnergies->Get("graphPHENIX200GeVRAA_0010");
	graphPHENIX200GeVRAA_2040= (TGraphErrors*)fileDataOtherEnergies->Get("graphPHENIX200GeVRAA_2040");
	graphPHENIX39GeVRAA_0010= (TGraphErrors*)fileDataOtherEnergies->Get("graphPHENIX39GeVRAA_0010");
	graphPHENIX39GeVRAA_2040= (TGraphErrors*)fileDataOtherEnergies->Get("graphPHENIX39GeVRAA_2040");
	graphPHENIX62GeVRAA_0010= (TGraphErrors*)fileDataOtherEnergies->Get("graphPHENIX62GeVRAA_0010");
	graphPHENIX62GeVRAA_2040= (TGraphErrors*)fileDataOtherEnergies->Get("graphPHENIX62GeVRAA_2040");

	graphPHENIX200GeVEtaRAA_0010= (TGraphErrors*)fileDataOtherEnergies->Get("graphPHENIX200GeVEtaRAA_0010");
	graphPHENIX200GeVEtaRAA_2040= (TGraphErrors*)fileDataOtherEnergies->Get("graphPHENIX200GeVEtaRAA_2040");
	graphPHENIX200GeVEtaRAA_2060= (TGraphErrors*)fileDataOtherEnergies->Get("graphPHENIX200GeVEtaRAA_2060");

	TGraphAsymmErrors* graphEtaRAAPhenix0010 = (TGraphAsymmErrors*)fileDataOtherEnergies->Get("graphPHENIX200GeVEtaRAA_0010"); 
	TGraphAsymmErrors* graphEtaRAAPhenix2040 = (TGraphAsymmErrors*)fileDataOtherEnergies->Get("graphPHENIX200GeVEtaRAA_2040"); 
	TGraphAsymmErrors* graphEtaRAAPhenix2060 = (TGraphAsymmErrors*)fileDataOtherEnergies->Get("graphPHENIX200GeVEtaRAA_2060"); 
	
	
	
	//*********************************************************************************************************//
	//**********************************     Charged pions and kaons     **************************************//
	//*********************************************************************************************************//
	
	//**************************** Charged ratios ****************************//
	TFile* fileDataALICEChargedRatioKaonToPion	= new TFile(fileNameChargedRatios);	
	TH1D *histoStatChargedRatioKaonToPion0005 = (TH1D*)fileDataALICEChargedRatioKaonToPion->Get("hstat_PbPb276_0005_kaon_to_pion_sum");
	TH1D *histoSystChargedRatioKaonToPion0005 = (TH1D*)fileDataALICEChargedRatioKaonToPion->Get("hsys_PbPb276_0005_kaon_to_pion_sum");

	TGraphAsymmErrors* graphChargedRatioKaonToPion0005 = new TGraphAsymmErrors(histoStatChargedRatioKaonToPion0005); 
	TGraphAsymmErrors* graphChargedRatioKaonToPionSys0005 = new TGraphAsymmErrors(histoSystChargedRatioKaonToPion0005); 
	
	TH1D *histoStatChargedRatioKaonToPion0510 = (TH1D*)fileDataALICEChargedRatioKaonToPion->Get("hstat_PbPb276_0510_kaon_to_pion_sum");
	TH1D *histoSystChargedRatioKaonToPion0510 = (TH1D*)fileDataALICEChargedRatioKaonToPion->Get("hsys_PbPb276_0510_kaon_to_pion_sum");
	
	TGraphAsymmErrors* graphChargedRatioKaonToPion0510 = new TGraphAsymmErrors(histoStatChargedRatioKaonToPion0510); 
	TGraphAsymmErrors* graphChargedRatioKaonToPionSys0510 = new TGraphAsymmErrors(histoSystChargedRatioKaonToPion0510); 

	TH1D* histoStatChargedRatioKaonToPion0010 = (TH1D*)histoStatChargedRatioKaonToPion0510->Clone("histoStatChargedRatioKaonToPion0010");
	TH1D* histoSystChargedRatioKaonToPion0010 = (TH1D*)histoSystChargedRatioKaonToPion0510->Clone("histoSystChargedRatioKaonToPion0010");
	histoStatChargedRatioKaonToPion0010->Add(histoStatChargedRatioKaonToPion0005);
	histoSystChargedRatioKaonToPion0010->Add(histoSystChargedRatioKaonToPion0005);
	histoStatChargedRatioKaonToPion0010->Scale(0.5);
	histoSystChargedRatioKaonToPion0010->Scale(0.5);

	for (Int_t i = 1; i < histoSystChargedRatioKaonToPion0010->GetNbinsX()+1; i++){
		Double_t relErrLowerCent = 0;
		if (histoSystChargedRatioKaonToPion0005->GetBinContent(i) != 0){
			relErrLowerCent= histoSystChargedRatioKaonToPion0005->GetBinError(i)/histoSystChargedRatioKaonToPion0005->GetBinContent(i)*100 ;
		}
		Double_t relErrHigherCent = 0;
		if (histoSystChargedRatioKaonToPion0510->GetBinContent(i) != 0){
			relErrHigherCent = histoSystChargedRatioKaonToPion0510->GetBinError(i)/histoSystChargedRatioKaonToPion0510->GetBinContent(i)*100 ;
		}
		
		if (relErrHigherCent > relErrLowerCent){
			histoSystChargedRatioKaonToPion0010->SetBinError(i, histoSystChargedRatioKaonToPion0010->GetBinContent(i)*relErrHigherCent/100);
		} else {
			histoSystChargedRatioKaonToPion0010->SetBinError(i, histoSystChargedRatioKaonToPion0010->GetBinContent(i)*relErrLowerCent/100);
		}         
	}   

	TGraphAsymmErrors* graphChargedRatioKaonToPion0010 = new TGraphAsymmErrors(histoStatChargedRatioKaonToPion0010); 
	TGraphAsymmErrors* graphChargedRatioKaonToPionSys0010 = new TGraphAsymmErrors(histoSystChargedRatioKaonToPion0010); 
	
	
	TH1D *histoStatChargedRatioKaonToPion2040 = (TH1D*)fileDataALICEChargedRatioKaonToPion->Get("hstat_PbPb276_2040_kaon_to_pion_sum");
	TH1D *histoSystChargedRatioKaonToPion2040 = (TH1D*)fileDataALICEChargedRatioKaonToPion->Get("hsys_PbPb276_2040_kaon_to_pion_sum");
	TGraphAsymmErrors* graphChargedRatioKaonToPion2040 = new TGraphAsymmErrors(histoStatChargedRatioKaonToPion2040); 
	TGraphAsymmErrors* graphChargedRatioKaonToPionSys2040 = new TGraphAsymmErrors(histoSystChargedRatioKaonToPion2040); 


	//**************************** Charged pion ****************************//
	TFile* fileDataALICEChargedPionRAA = new TFile(fileNameChargedPionRAA);
	
	TH1D *histoStatChargedPion0005 = (TH1D*)fileDataALICEChargedPionRAA->Get("RAAPion_Stat_0_5");
	TH1D *histoSystChargedPion0005 = (TH1D*)fileDataALICEChargedPionRAA->Get("RAAPion_Syst_0_5");

	TGraphAsymmErrors* graphChargedPionRAA0005 = new TGraphAsymmErrors(histoStatChargedPion0005); 
	TGraphAsymmErrors* graphChargedPionRAASys0005 = new TGraphAsymmErrors(histoSystChargedPion0005); 
	
	TH1D *histoStatChargedPion0510 = (TH1D*)fileDataALICEChargedPionRAA->Get("RAAPion_Stat_5_10");
	TH1D *histoSystChargedPion0510 = (TH1D*)fileDataALICEChargedPionRAA->Get("RAAPion_Syst_5_10");
	
	TGraphAsymmErrors* graphChargedPionRAA0510 = new TGraphAsymmErrors(histoStatChargedPion0510); 
	TGraphAsymmErrors* graphChargedPionRAASys0510 = new TGraphAsymmErrors(histoSystChargedPion0510); 


	TH1D* histoStatChargedPion0010 = (TH1D*)histoStatChargedPion0510->Clone("histoStatChargedPion0010");
	TH1D* histoSystChargedPion0010 = (TH1D*)histoSystChargedPion0510->Clone("histoSystChargedPion0010");
	histoStatChargedPion0010->Add(histoStatChargedPion0005);
	histoSystChargedPion0010->Add(histoSystChargedPion0005);
	histoStatChargedPion0010->Scale(0.5);
	histoSystChargedPion0010->Scale(0.5);

	for (Int_t i = 1; i < histoSystChargedPion0010->GetNbinsX()+1; i++){
		Double_t relErrLowerCent = 0;
		if (histoSystChargedPion0005->GetBinContent(i) != 0){
			relErrLowerCent= histoSystChargedPion0005->GetBinError(i)/histoSystChargedPion0005->GetBinContent(i)*100 ;
		}
		Double_t relErrHigherCent = 0;
		if (histoSystChargedPion0510->GetBinContent(i) != 0){
			relErrHigherCent = histoSystChargedPion0510->GetBinError(i)/histoSystChargedPion0510->GetBinContent(i)*100 ;
		}
		
		if (relErrHigherCent > relErrLowerCent){
			histoSystChargedPion0010->SetBinError(i, histoSystChargedPion0010->GetBinContent(i)*relErrHigherCent/100);
		} else {
			histoSystChargedPion0010->SetBinError(i, histoSystChargedPion0010->GetBinContent(i)*relErrLowerCent/100);
		}         
	}   

	TGraphAsymmErrors* graphChargedPionRAA0010 = new TGraphAsymmErrors(histoStatChargedPion0010); 
	TGraphAsymmErrors* graphChargedPionRAASys0010 = new TGraphAsymmErrors(histoSystChargedPion0010); 
	
	TH1D *histoStatChargedPion2040 = (TH1D*)fileDataALICEChargedPionRAA->Get("RAAPion_Stat_20_40");
	TH1D *histoSystChargedPion2040 = (TH1D*)fileDataALICEChargedPionRAA->Get("RAAPion_Syst_20_40");
	TGraphAsymmErrors* graphChargedPionRAA2040 = new TGraphAsymmErrors(histoStatChargedPion2040); 
	TGraphAsymmErrors* graphChargedPionRAASys2040 = new TGraphAsymmErrors(histoSystChargedPion2040); 


	//**************************** Charged kaon ****************************//
	TFile* fileDataALICEChargedKaonRAA = new TFile(fileNameChargedKaonRAA);

	TH1D *histoStatChargedKaon0005 = (TH1D*)fileDataALICEChargedKaonRAA->Get("RAAKaon_Stat_0_5");
	TH1D *histoSystChargedKaon0005 = (TH1D*)fileDataALICEChargedKaonRAA->Get("RAAKaon_Syst_0_5");

	TGraphAsymmErrors* graphChargedKaonRAA0005 = new TGraphAsymmErrors(histoStatChargedKaon0005); 
	TGraphAsymmErrors* graphChargedKaonRAASys0005 = new TGraphAsymmErrors(histoSystChargedKaon0005); 
	
	TH1D *histoStatChargedKaon0510 = (TH1D*)fileDataALICEChargedKaonRAA->Get("RAAKaon_Stat_5_10");
	TH1D *histoSystChargedKaon0510 = (TH1D*)fileDataALICEChargedKaonRAA->Get("RAAKaon_Syst_5_10");

	TGraphAsymmErrors* graphChargedKaonRAA0510 = new TGraphAsymmErrors(histoStatChargedKaon0510); 
	TGraphAsymmErrors* graphChargedKaonRAASys0510 = new TGraphAsymmErrors(histoSystChargedKaon0510); 

	TH1D* histoStatChargedKaon0010 = (TH1D*)histoStatChargedKaon0510->Clone("histoStatChargedKaon0010");
	TH1D* histoSystChargedKaon0010 = (TH1D*)histoSystChargedKaon0510->Clone("histoSystChargedKaon0010");
	histoStatChargedKaon0010->Add(histoStatChargedKaon0005);
	histoSystChargedKaon0010->Add(histoSystChargedKaon0005);
	histoStatChargedKaon0010->Scale(0.5);
	histoSystChargedKaon0010->Scale(0.5);

	for (Int_t i = 1; i < histoSystChargedKaon0010->GetNbinsX()+1; i++){
		Double_t relErrLowerCent = 0;
		if (histoSystChargedKaon0005->GetBinContent(i) != 0){
			relErrLowerCent= histoSystChargedKaon0005->GetBinError(i)/histoSystChargedKaon0005->GetBinContent(i)*100 ;
		}
		Double_t relErrHigherCent = 0;
		if (histoSystChargedKaon0510->GetBinContent(i) != 0){
			relErrHigherCent = histoSystChargedKaon0510->GetBinError(i)/histoSystChargedKaon0510->GetBinContent(i)*100 ;
		}
		
		if (relErrHigherCent > relErrLowerCent){
			histoSystChargedKaon0010->SetBinError(i, histoSystChargedKaon0010->GetBinContent(i)*relErrHigherCent/100);
		} else {
			histoSystChargedKaon0010->SetBinError(i, histoSystChargedKaon0010->GetBinContent(i)*relErrLowerCent/100);
		}         
	}   

	TGraphAsymmErrors* graphChargedKaonRAA0010 = new TGraphAsymmErrors(histoStatChargedKaon0010); 
	TGraphAsymmErrors* graphChargedKaonRAASys0010 = new TGraphAsymmErrors(histoSystChargedKaon0010); 

	TH1D *histoStatChargedKaon2040 = (TH1D*)fileDataALICEChargedKaonRAA->Get("RAAKaon_Stat_20_40");
	TH1D *histoSystChargedKaon2040 = (TH1D*)fileDataALICEChargedKaonRAA->Get("RAAKaon_Syst_20_40");
	TGraphAsymmErrors* graphChargedKaonRAA2040 = new TGraphAsymmErrors(histoStatChargedKaon2040); 
	TGraphAsymmErrors* graphChargedKaonRAASys2040 = new TGraphAsymmErrors(histoSystChargedKaon2040); 
	
	
	
	//*********************************************************************************************************//
	//***************************************     LHC data input     ******************************************//
	//*********************************************************************************************************//
	
	//**************************** PP 2.76TeV ****************************//
	fileFinalResultsPP = 		new TFile(filePPpublished.Data());
	graphInvSectionCombStatPi02760GeVPlot = (TGraphAsymmErrors*)fileFinalResultsPP->Get("graphInvCrossSectionPi0Comb2760GeVStatErr"); 
	graphInvSectionCombStatPi02760GeVPlot = ScaleGraph(graphInvSectionCombStatPi02760GeVPlot,1./xSection2760GeVppINEL);
	graphInvSectionCombStatPi02760GeVPlot->RemovePoint(graphInvSectionCombStatPi02760GeVPlot->GetN()-1);
	graphInvSectionCombSysPi02760GeVPlot = (TGraphAsymmErrors*)fileFinalResultsPP->Get("graphInvCrossSectionPi0Comb2760GeVSysErr");
	graphInvSectionCombSysPi02760GeVPlot = ScaleGraph(graphInvSectionCombSysPi02760GeVPlot,1./xSection2760GeVppINEL);
	graphInvSectionCombSysPi02760GeVPlot->RemovePoint(graphInvSectionCombSysPi02760GeVPlot->GetN()-1);

	graphInvSectionCombStatEta2760GeVPlot = (TGraphAsymmErrors*)fileFinalResultsPP->Get("graphInvCrossSectionEtaComb2760GeVStatErr_PrelimQM2011"); 
	graphInvSectionCombStatEta2760GeVPlot = ScaleGraph(graphInvSectionCombStatEta2760GeVPlot,1./xSection2760GeVppINEL);
// 	graphInvSectionCombStatEta2760GeVPlot->RemovePoint(graphInvSectionCombStatEta2760GeVPlot->GetN()-1);
	graphInvSectionCombSysEta2760GeVPlot = (TGraphAsymmErrors*)fileFinalResultsPP->Get("graphInvCrossSectionEtaComb2760GeVSysErr_PrelimQM2011");
	graphInvSectionCombSysEta2760GeVPlot = ScaleGraph(graphInvSectionCombSysEta2760GeVPlot,1./xSection2760GeVppINEL);
// 	graphInvSectionCombSysEta2760GeVPlot->RemovePoint(graphInvSectionCombSysEta2760GeVPlot->GetN()-1);
	
	
		//!!!!!! not approved references !!!!
// 	graphInvSectionCombStatPi02760GeVPlot = (TGraphAsymmErrors*)fileFinalResultsPP->Get("graphInvCrossSectionPi0Comb2760GeVAStatErr"); //it is shifted already in X!!
// 	graphInvSectionCombStatPi02760GeVPlot = ScaleGraph(graphInvSectionCombStatPi02760GeVPlot,1./xSection2760GeVppINEL);
// 	graphInvSectionCombStatPi02760GeVPlot->RemovePoint(graphInvSectionCombStatPi02760GeVPlot->GetN()-1);
// 	graphInvSectionCombSysPi02760GeVPlot = (TGraphAsymmErrors*)fileFinalResultsPP->Get("graphInvCrossSectionPi0Comb2760GeVASysErr");
// 	graphInvSectionCombSysPi02760GeVPlot = ScaleGraph(graphInvSectionCombSysPi02760GeVPlot,1./xSection2760GeVppINEL);
// 	graphInvSectionCombSysPi02760GeVPlot->RemovePoint(graphInvSectionCombSysPi02760GeVPlot->GetN()-1);
	
// 	graphInvSectionCombStatPi02760GeVPlot = (TGraphAsymmErrors*)fileFinalResultsPP->Get("graphInvCrossSectionPi0Comb2760GeVStatErr");
// 	graphInvSectionCombStatPi02760GeVPlot = ScaleGraph(graphInvSectionCombStatPi02760GeVPlot,1./xSection2760GeVppINEL);
// 	graphInvSectionCombStatPi02760GeVPlot->RemovePoint(graphInvSectionCombStatPi02760GeVPlot->GetN()-1);
// 	graphInvSectionCombSysPi02760GeVPlot = (TGraphAsymmErrors*)fileFinalResultsPP->Get("graphInvCrossSectionPi0Comb2760GeVSysErr");
// 	graphInvSectionCombSysPi02760GeVPlot = ScaleGraph(graphInvSectionCombSysPi02760GeVPlot,1./xSection2760GeVppINEL);
// 	graphInvSectionCombSysPi02760GeVPlot->RemovePoint(graphInvSectionCombSysPi02760GeVPlot->GetN()-1);

// 	fileFinalResultsPCMPPeta = 		new TFile(filePPEtaPCM.Data());
// // 	graphInvSectionCombStatEta2760GeVPlot = (TGraphAsymmErrors*)fileFinalResultsPCMPPeta->Get("graphInvCrossSectionEtaComb2760GeVStatErr_YShifted");
// // 	graphInvSectionCombStatEta2760GeVPlot = ScaleGraph(graphInvSectionCombStatEta2760GeVPlot,1./xSection2760GeVppINEL);
// // 	graphInvSectionCombSysEta2760GeVPlot = (TGraphAsymmErrors*)fileFinalResultsPCMPPeta->Get("graphInvCrossSectionEtaComb2760GeVSysErr_YShifted");
// // 	graphInvSectionCombSysEta2760GeVPlot = ScaleGraph(graphInvSectionCombSysEta2760GeVPlot,1./xSection2760GeVppINEL);
// 
// 	graphInvSectionCombStatEta2760GeVPlot = (TGraphAsymmErrors*)fileFinalResultsPCMPPeta->Get("graphPCMXSectionStatEta2760GeV_XShifted"); //graphInvCrossSectionEtaComb2760GeVStatErr");
// 	graphInvSectionCombStatEta2760GeVPlot = ScaleGraph(graphInvSectionCombStatEta2760GeVPlot,1./xSection2760GeVppINEL);
// // 	graphInvSectionCombStatEta2760GeVPlot->RemovePoint(graphInvSectionCombStatEta2760GeVPlot->GetN()-1);
// 	graphInvSectionCombSysEta2760GeVPlot = (TGraphAsymmErrors*)fileFinalResultsPCMPPeta->Get("graphPCMXSectionSysEta2760GeV_XShifted"); //graphInvCrossSectionEtaComb2760GeVSysErr");
// 	graphInvSectionCombSysEta2760GeVPlot = ScaleGraph(graphInvSectionCombSysEta2760GeVPlot,1./xSection2760GeVppINEL);
// // 	graphInvSectionCombSysEta2760GeVPlot->RemovePoint(graphInvSectionCombSysEta2760GeVPlot->GetN()-1);
// 
// 	
// 	TGraphAsymmErrors *graphMtScaledEtaStat = (TGraphAsymmErrors*)fileFinalResultsPCMPPeta->Get("graphEMCALXSectionStatEta2760GeV_XShifted");
// 	graphMtScaledEtaStat = ScaleGraph(graphMtScaledEtaStat,1./xSection2760GeVppINEL);
// 	TGraphAsymmErrors *graphMtScaledEtaSys = (TGraphAsymmErrors*)fileFinalResultsPCMPPeta->Get("graphEMCALXSectionSysEta2760GeV_XShifted");
// 	graphMtScaledEtaSys = ScaleGraph(graphMtScaledEtaSys,1./xSection2760GeVppINEL);
	
	
	
	//**************************** PHOS ****************************//
	cout << "Loading PHOS histos" << endl;
	TFile *filePHOSPbPb = 		new TFile(fileNamePHOS);
	TDirectory *directoryPHOSPi0PbPb0005 = (TDirectory*)filePHOSPbPb->Get("pi0_PbPb_2760_Centrality_0-5%");
	TDirectory *directoryPHOSPi0PbPb0010 = (TDirectory*)filePHOSPbPb->Get("pi0_PbPb_2760_Centrality_0-10%");
	TDirectory *directoryPHOSPi0PbPb2040 = (TDirectory*)filePHOSPbPb->Get("pi0_PbPb_2760_Centrality_20-40%");

	cout << "PHOS: 0-5%" << endl;
		histoPi0PHOSPbPb0005 = 		(TH1D*)directoryPHOSPi0PbPb0005->Get("hPi0_PbPb_cen0_NoBW_Stat");
		histoPi0PHOSSysPbPb0005 = 	(TH1D*)directoryPHOSPi0PbPb0005->Get("hPi0_PbPb_cen0_NoBW_Syst");
		graphPHOSYieldPi0SysErrPbPb0005 = new TGraphAsymmErrors(histoPi0PHOSSysPbPb0005);	
		histoPi0PHOSSysRAAPbPb0005 = 	(TH1D*)directoryPHOSPi0PbPb0005->Get("hPi0_PbPb_cen0_SystRaa");
		graphSysErrRAAYieldPi0PHOSPbPb0005 = new TGraphAsymmErrors(histoPi0PHOSSysRAAPbPb0005);	

	cout << "PHOS: 0-10%" << endl;
		histoPi0PHOSPbPb0010 = 		(TH1D*)directoryPHOSPi0PbPb0010->Get("hPi0_PbPb_cen7_NoBW_Stat");
		TGraphAsymmErrors *graphPHOSPi0InvYieldStatPbPb2760GeV_0010 = new TGraphAsymmErrors(histoPi0PHOSPbPb0010);	
		histoPi0PHOSSysPbPb0010 = 	(TH1D*)directoryPHOSPi0PbPb0010->Get("hPi0_PbPb_cen7_NoBW_Syst");
		TGraphAsymmErrors *graphPHOSPi0InvYieldSysPbPb2760GeV_0010 = new TGraphAsymmErrors(histoPi0PHOSSysPbPb0010);	
		histoPi0PHOSSysRAAPbPb0010 = 	(TH1D*)directoryPHOSPi0PbPb0010->Get("hPi0_PbPb_cen7_SystRaa");
		graphSysErrRAAYieldPi0PHOSPbPb0010 = new TGraphAsymmErrors(histoPi0PHOSSysRAAPbPb0010);	

		graphPHOSPi0InvYieldStatPbPb2760GeV_0010->RemovePoint(0);
		graphPHOSPi0InvYieldStatPbPb2760GeV_0010->RemovePoint(0);
		
		graphPHOSPi0InvYieldSysPbPb2760GeV_0010->RemovePoint(0);
		graphPHOSPi0InvYieldSysPbPb2760GeV_0010->RemovePoint(0);
		
// 		graphPHOSPi0InvYieldStatPbPb2760GeV_0010->Print();
// 		graphPHOSPi0InvYieldSysPbPb2760GeV_0010->Print();
		
	cout << "PHOS: 20-40%" << endl;
		histoPi0PHOSPbPb2040 = 		(TH1D*)directoryPHOSPi0PbPb2040->Get("hPi0_PbPb_cen3_NoBW_Stat");
		TGraphAsymmErrors *graphPHOSPi0InvYieldStatPbPb2760GeV_2040 = new TGraphAsymmErrors(histoPi0PHOSPbPb2040);	
		histoPi0PHOSSysPbPb2040 = 	(TH1D*)directoryPHOSPi0PbPb2040->Get("hPi0_PbPb_cen3_NoBW_Syst");
		TGraphAsymmErrors *graphPHOSPi0InvYieldSysPbPb2760GeV_2040 = new TGraphAsymmErrors(histoPi0PHOSSysPbPb2040);	
		histoPi0PHOSSysRAAPbPb2040 = 	(TH1D*)directoryPHOSPi0PbPb2040->Get("hPi0_PbPb_cen3_SystRaa");
		graphSysErrRAAYieldPi0PHOSPbPb2040 = new TGraphAsymmErrors(histoPi0PHOSSysRAAPbPb2040);	

		graphPHOSPi0InvYieldSysPbPb2760GeV_2040->RemovePoint(0);
		graphPHOSPi0InvYieldSysPbPb2760GeV_2040->RemovePoint(0);
		
		
	
	//**************************** PCM Pb-Pb published data 2010 ****************************//
	cout << "Loading 2010 PCM histos" << endl;
	TFile* filePCMPublished 									= new TFile(fileNamePCMPublished.Data());

 	TH1D* histoPCMPublishedNumberOfEventsPbPb2760GeV_0010 					= (TH1D*)filePCMPublished->Get("histoNumberOfEventsPbPb_2.76TeV0-10%");
 	TH1D* histoPCMPublishedNumberOfEventsPbPb2760GeV_0005 					= (TH1D*)filePCMPublished->Get("histoNumberOfEventsPbPb_2.76TeV0-5%");
	TH1D* histoPCMPublishedNumberOfEventsPbPb2760GeV_2040 					= (TH1D*)filePCMPublished->Get("histoNumberOfEventsPbPb_2.76TeV20-40%");

	cout << "For the published Pi0 in 0-10% " << endl;
	TDirectoryFile* directoryPCMPublishedPi0PbPb2760GeV_0010 				= (TDirectoryFile*)filePCMPublished->Get("Pi0_PbPb_2.76TeV_0-10%"); 
		TH1D* histoPCMPublishedPi0MassPbPb2760GeV_0010 						= (TH1D*)directoryPCMPublishedPi0PbPb2760GeV_0010->Get("MassPi0");
		TH1D* histoPCMPublishedPi0FWHMMeVPbPb2760GeV_0010 					= (TH1D*)directoryPCMPublishedPi0PbPb2760GeV_0010->Get("FWHMPi0MeV");
		TH1D* histoPCMPublishedPi0TrueMassPbPb2760GeV_0010 					= (TH1D*)directoryPCMPublishedPi0PbPb2760GeV_0010->Get("TrueMassPi0");
		TH1D* histoPCMPublishedPi0TrueFWHMMeVPbPb2760GeV_0010 				= (TH1D*)directoryPCMPublishedPi0PbPb2760GeV_0010->Get("TrueFWHMPi0MeV");
		TH1D* histoPCMPublishedPi0AccPbPb2760GeV_0010 						= (TH1D*)directoryPCMPublishedPi0PbPb2760GeV_0010->Get("Pi0_Acceptance");
		TH1D* histoPCMPublishedPi0TrueEffPtPbPb2760GeV_0010 				= (TH1D*)directoryPCMPublishedPi0PbPb2760GeV_0010->Get("Pi0_Efficiency");
		TH1D* histoPCMPublishedPi0InvYieldPbPb2760GeV_0010 					= (TH1D*)directoryPCMPublishedPi0PbPb2760GeV_0010->Get("CorrectedYieldPi0");   

		TGraphAsymmErrors* graphPCMPublishedPi0RAAStat2760GeV_0010			= (TGraphAsymmErrors*)directoryPCMPublishedPi0PbPb2760GeV_0010->Get("RAA");
		graphPCMPublishedPi0RAAStat2760GeV_0010->RemovePoint(0);
		TH1D* histoPCMPublishedPi0RAAStatPbPb2760GeV_0010 = (TH1D*)GraphAsymErrorsToHist(graphPCMPublishedPi0RAAStat2760GeV_0010,12,"histoPCMPublishedPi0RAAStatPbPb2760GeV_0010");
		TGraphAsymmErrors* graphPCMPublishedPi0RAASys2760GeV_0010			= (TGraphAsymmErrors*)directoryPCMPublishedPi0PbPb2760GeV_0010->Get("RAASys");
		graphPCMPublishedPi0RAASys2760GeV_0010->RemovePoint(0);
		
		TGraphAsymmErrors* graphPCMPublishedPi0InvYieldStatPbPb2760GeV_0010 = new TGraphAsymmErrors(histoPCMPublishedPi0InvYieldPbPb2760GeV_0010);
			graphPCMPublishedPi0InvYieldStatPbPb2760GeV_0010->RemovePoint(graphPCMPublishedPi0InvYieldStatPbPb2760GeV_0010->GetN()-1);
			graphPCMPublishedPi0InvYieldStatPbPb2760GeV_0010->RemovePoint(0);

		TGraphAsymmErrors* graphPCMPublishedPi0InvYieldSysA2760GeV_0010			= (TGraphAsymmErrors*)directoryPCMPublishedPi0PbPb2760GeV_0010->Get("Pi0SystErrorA");
		TGraphAsymmErrors* graphPCMPublishedPi0CorrYieldSysErrPbPb2760GeV_0010 	= (TGraphAsymmErrors*)directoryPCMPublishedPi0PbPb2760GeV_0010->Get("Pi0SystError"); 
		TGraphAsymmErrors* graphPCMPublishedPi0InvYieldSysPbPb2760GeV_0010		= (TGraphAsymmErrors*)directoryPCMPublishedPi0PbPb2760GeV_0010->Get("Pi0SystError");
			graphPCMPublishedPi0InvYieldSysPbPb2760GeV_0010->RemovePoint(graphPCMPublishedPi0InvYieldSysPbPb2760GeV_0010->GetN()-1);

// 		cout << "printing the spectra" << endl;
// 			graphPCMPublishedPi0InvYieldStatPbPb2760GeV_0010->Print();
// 			graphPCMPublishedPi0InvYieldSysPbPb2760GeV_0010->Print();

			
	cout << "For the published Pi0 in 0-5% " << endl;
	TDirectoryFile* directoryPCMPublishedPi0PbPb2760GeV_0005 				= (TDirectoryFile*)filePCMPublished->Get("Pi0_PbPb_2.76TeV_0-5%"); 
		TH1D* histoPCMPublishedPi0MassPbPb2760GeV_0005 						= (TH1D*)directoryPCMPublishedPi0PbPb2760GeV_0005->Get("MassPi0");
		TH1D* histoPCMPublishedPi0FWHMMeVPbPb2760GeV_0005 					= (TH1D*)directoryPCMPublishedPi0PbPb2760GeV_0005->Get("FWHMPi0MeV");
		TH1D* histoPCMPublishedPi0TrueMassPbPb2760GeV_0005 					= (TH1D*)directoryPCMPublishedPi0PbPb2760GeV_0005->Get("TrueMassPi0");
		TH1D* histoPCMPublishedPi0TrueFWHMMeVPbPb2760GeV_0005 				= (TH1D*)directoryPCMPublishedPi0PbPb2760GeV_0005->Get("TrueFWHMPi0MeV");
		TH1D* histoPCMPublishedPi0AccPbPb2760GeV_0005 						= (TH1D*)directoryPCMPublishedPi0PbPb2760GeV_0005->Get("Pi0_Acceptance");
		TH1D* histoPCMPublishedPi0TrueEffPtPbPb2760GeV_0005 				= (TH1D*)directoryPCMPublishedPi0PbPb2760GeV_0005->Get("Pi0_Efficiency");
		TH1D* histoPCMPublishedPi0InvYieldPbPb2760GeV_0005 					= (TH1D*)directoryPCMPublishedPi0PbPb2760GeV_0005->Get("CorrectedYieldPi0");   

		TGraphAsymmErrors* graphPCMPublishedPi0RAAStat2760GeV_0005			= (TGraphAsymmErrors*)directoryPCMPublishedPi0PbPb2760GeV_0005->Get("RAA");
		TGraphAsymmErrors* graphPCMPublishedPi0RAASys2760GeV_0005			= (TGraphAsymmErrors*)directoryPCMPublishedPi0PbPb2760GeV_0005->Get("RAASys");
		
		TGraphAsymmErrors* graphPCMPublishedPi0InvYieldStatPbPb2760GeV_0005 = new TGraphAsymmErrors(histoPCMPublishedPi0InvYieldPbPb2760GeV_0005);
			graphPCMPublishedPi0InvYieldStatPbPb2760GeV_0005->RemovePoint(graphPCMPublishedPi0InvYieldStatPbPb2760GeV_0005->GetN()-1);
			graphPCMPublishedPi0InvYieldStatPbPb2760GeV_0005->RemovePoint(0);

		TGraphAsymmErrors* graphPCMPublishedPi0InvYieldSysA2760GeV_0005			= (TGraphAsymmErrors*)directoryPCMPublishedPi0PbPb2760GeV_0005->Get("Pi0SystErrorA");
		TGraphAsymmErrors* graphPCMPublishedPi0CorrYieldSysErrPbPb2760GeV_0005 	= (TGraphAsymmErrors*)directoryPCMPublishedPi0PbPb2760GeV_0005->Get("Pi0SystError"); 
		TGraphAsymmErrors* graphPCMPublishedPi0InvYieldSysPbPb2760GeV_0005		= (TGraphAsymmErrors*)directoryPCMPublishedPi0PbPb2760GeV_0005->Get("Pi0SystError");
			graphPCMPublishedPi0InvYieldSysPbPb2760GeV_0005->RemovePoint(graphPCMPublishedPi0InvYieldSysPbPb2760GeV_0005->GetN()-1);
	
			
	cout << "For the published Pi0 in 20-40% " << endl;
	TDirectoryFile* directoryPCMPublishedPi0PbPb2760GeV_2040 				= (TDirectoryFile*)filePCMPublished->Get("Pi0_PbPb_2.76TeV_20-40%"); 
		TH1D* histoPCMPublishedPi0MassPbPb2760GeV_2040 						= (TH1D*)directoryPCMPublishedPi0PbPb2760GeV_2040->Get("MassPi0");
		TH1D* histoPCMPublishedPi0FWHMMeVPbPb2760GeV_2040 					= (TH1D*)directoryPCMPublishedPi0PbPb2760GeV_2040->Get("FWHMPi0MeV");
		TH1D* histoPCMPublishedPi0TrueMassPbPb2760GeV_2040 					= (TH1D*)directoryPCMPublishedPi0PbPb2760GeV_2040->Get("TrueMassPi0");
		TH1D* histoPCMPublishedPi0TrueFWHMMeVPbPb2760GeV_2040 				= (TH1D*)directoryPCMPublishedPi0PbPb2760GeV_2040->Get("TrueFWHMPi0MeV");
		TH1D* histoPCMPublishedPi0AccPbPb2760GeV_2040 						= (TH1D*)directoryPCMPublishedPi0PbPb2760GeV_2040->Get("Pi0_Acceptance");
		TH1D* histoPCMPublishedPi0TrueEffPtPbPb2760GeV_2040 				= (TH1D*)directoryPCMPublishedPi0PbPb2760GeV_2040->Get("Pi0_Efficiency");
		TH1D* histoPCMPublishedPi0InvYieldPbPb2760GeV_2040 					= (TH1D*)directoryPCMPublishedPi0PbPb2760GeV_2040->Get("CorrectedYieldPi0");   

		TGraphAsymmErrors* graphPCMPublishedPi0RAAStat2760GeV_2040			= (TGraphAsymmErrors*)directoryPCMPublishedPi0PbPb2760GeV_2040->Get("RAA");
		graphPCMPublishedPi0RAAStat2760GeV_2040->RemovePoint(0);
		TH1D* histoPCMPublishedPi0RAAStatPbPb2760GeV_2040 = (TH1D*)GraphAsymErrorsToHist(graphPCMPublishedPi0RAAStat2760GeV_2040,12,"histoPCMPublishedPi0RAAStatPbPb2760GeV_2040");
		TGraphAsymmErrors* graphPCMPublishedPi0RAASys2760GeV_2040			= (TGraphAsymmErrors*)directoryPCMPublishedPi0PbPb2760GeV_2040->Get("RAASys");
		graphPCMPublishedPi0RAASys2760GeV_2040->RemovePoint(0);
		
		TGraphAsymmErrors* graphPCMPublishedPi0InvYieldStatPbPb2760GeV_2040 = new TGraphAsymmErrors(histoPCMPublishedPi0InvYieldPbPb2760GeV_2040);
			graphPCMPublishedPi0InvYieldStatPbPb2760GeV_2040->RemovePoint(graphPCMPublishedPi0InvYieldStatPbPb2760GeV_2040->GetN()-1);
			graphPCMPublishedPi0InvYieldStatPbPb2760GeV_2040->RemovePoint(0);

		TGraphAsymmErrors* graphPCMPublishedPi0InvYieldSysA2760GeV_2040			= (TGraphAsymmErrors*)directoryPCMPublishedPi0PbPb2760GeV_2040->Get("Pi0SystErrorA");
		TGraphAsymmErrors* graphPCMPublishedPi0CorrYieldSysErrPbPb2760GeV_2040 	= (TGraphAsymmErrors*)directoryPCMPublishedPi0PbPb2760GeV_2040->Get("Pi0SystError"); 
		TGraphAsymmErrors* graphPCMPublishedPi0InvYieldSysPbPb2760GeV_2040		= (TGraphAsymmErrors*)directoryPCMPublishedPi0PbPb2760GeV_2040->Get("Pi0SystError");
			graphPCMPublishedPi0InvYieldSysPbPb2760GeV_2040->RemovePoint(graphPCMPublishedPi0InvYieldSysPbPb2760GeV_2040->GetN()-1);
	
// 		cout << "printing the spectra" << endl;
// 			graphPCMPublishedPi0InvYieldStatPbPb2760GeV_2040->Print();
// 			graphPCMPublishedPi0InvYieldSysPbPb2760GeV_2040->Print();


			
	//**************************** PCM Pb-Pb data 2011 ****************************//
	cout << "Loading PCM histos" << endl;
	TFile* filePCM = new TFile(fileNamePCM.Data());
	
	TH1D* histoPCMNumberOfEventsPbPb2760GeV_0005 			= (TH1D*)filePCM->Get("histoNumberOfEventsPbPb_2.76TeV0-5%");
 	TH1D* histoPCMNumberOfEventsPbPb2760GeV_0010 			= (TH1D*)filePCM->Get("histoNumberOfEventsPbPb_2.76TeV0-10%");
	TH1D* histoPCMNumberOfEventsPbPb2760GeV_2040 			= (TH1D*)filePCM->Get("histoNumberOfEventsPbPb_2.76TeV20-40%");
	TH1D* histoPCMNumberOfEventsPbPb2760GeV_2050 			= (TH1D*)filePCM->Get("histoNumberOfEventsPbPb_2.76TeV20-50%");

	cout << "For the Pi0 in 0-10% " << endl;
	TDirectoryFile* directoryPCMPi0PbPb2760GeV_0010 		= (TDirectoryFile*)filePCM->Get("Pi0_PbPb_2.76TeV_0-10%"); 
		TH1D* histoPCMPi0MassPbPb2760GeV_0010 				= (TH1D*)directoryPCMPi0PbPb2760GeV_0010->Get("MassPi0");
		TH1D* histoPCMPi0FWHMMeVPbPb2760GeV_0010 			= (TH1D*)directoryPCMPi0PbPb2760GeV_0010->Get("FWHMPi0MeV");
		TH1D* histoPCMPi0TrueMassPbPb2760GeV_0010 			= (TH1D*)directoryPCMPi0PbPb2760GeV_0010->Get("TrueMassPi0");
		TH1D* histoPCMPi0TrueFWHMMeVPbPb2760GeV_0010 		= (TH1D*)directoryPCMPi0PbPb2760GeV_0010->Get("TrueFWHMPi0MeV");
		TH1D* histoPCMPi0AccPbPb2760GeV_0010 				= (TH1D*)directoryPCMPi0PbPb2760GeV_0010->Get("Pi0_Acceptance");
		TH1D* histoPCMPi0TrueEffPtPbPb2760GeV_0010 			= (TH1D*)directoryPCMPi0PbPb2760GeV_0010->Get("Pi0_Efficiency");
		
		TH1D* histoPCMPi0InvYieldPbPb2760GeV_0010 					= (TH1D*)directoryPCMPi0PbPb2760GeV_0010->Get("CorrectedYieldPi0");   
		TGraphAsymmErrors* graphPCMPi0InvYieldStatPbPb2760GeV_0010 	= new TGraphAsymmErrors(histoPCMPi0InvYieldPbPb2760GeV_0010);
			graphPCMPi0InvYieldStatPbPb2760GeV_0010->RemovePoint(0);

		TGraphAsymmErrors* graphPCMPi0InvYieldSysA2760GeV_0010			= (TGraphAsymmErrors*)directoryPCMPi0PbPb2760GeV_0010->Get("Pi0SystErrorA");
			graphPCMPi0InvYieldSysA2760GeV_0010->RemovePoint(graphPCMPi0InvYieldSysA2760GeV_0010->GetN()-1);
		
		TGraphAsymmErrors* graphPCMPi0CorrYieldSysErrPbPb2760GeV_0010 	= (TGraphAsymmErrors*)directoryPCMPi0PbPb2760GeV_0010->Get("Pi0SystError"); 
			graphPCMPi0CorrYieldSysErrPbPb2760GeV_0010->RemovePoint(graphPCMPi0CorrYieldSysErrPbPb2760GeV_0010->GetN()-1);

		TGraphAsymmErrors* graphPCMPi0InvYieldSysPbPb2760GeV_0010		= (TGraphAsymmErrors*)directoryPCMPi0PbPb2760GeV_0010->Get("Pi0SystError");
			graphPCMPi0InvYieldSysPbPb2760GeV_0010->RemovePoint(graphPCMPi0InvYieldSysPbPb2760GeV_0010->GetN()-1);

		TGraphAsymmErrors* graphPCMPi0RAAStat2760GeV_0010	= (TGraphAsymmErrors*)directoryPCMPi0PbPb2760GeV_0010->Get("Pi0RAA");
		TH1D* histoPCMPi0RAAStatPbPb2760GeV_0010 = (TH1D*)GraphAsymErrorsToHist(graphPCMPi0RAAStat2760GeV_0010,14,"histoPCMPi0RAAStatPbPb2760GeV_0010");
		TGraphAsymmErrors* graphPCMPi0RAASys2760GeV_0010	= (TGraphAsymmErrors*)directoryPCMPi0PbPb2760GeV_0010->Get("Pi0RAASys");

		TH1D* ratioPCMPi0MassMCDiffData_0010 = (TH1D*)histoPCMPi0TrueMassPbPb2760GeV_0010->Clone("ratioPCMPi0MassMCDiffData_0010");
			ratioPCMPi0MassMCDiffData_0010->Sumw2();
			ratioPCMPi0MassMCDiffData_0010->Add(histoPCMPi0MassPbPb2760GeV_0010,-1);
			ratioPCMPi0MassMCDiffData_0010->Divide(ratioPCMPi0MassMCDiffData_0010, histoPCMPi0MassPbPb2760GeV_0010,1.,1.,"");
			ratioPCMPi0MassMCDiffData_0010->Scale(1./mesonMassExpectPi0);

 		TH1D *histoPCMPi0AccTimesEffPbPb2760GeV_0010 = (TH1D*)histoPCMPi0TrueEffPtPbPb2760GeV_0010->Clone("histoPCMPi0AccTimesEffPbPb2760GeV_0010");
			histoPCMPi0AccTimesEffPbPb2760GeV_0010->Sumw2();
			histoPCMPi0AccTimesEffPbPb2760GeV_0010->Multiply(histoPCMPi0AccPbPb2760GeV_0010);
		
// 		cout << "printing the spectra" << endl;
// 			graphPCMPi0InvYieldStatPbPb2760GeV_0010->Print();
// 			graphPCMPi0InvYieldSysPbPb2760GeV_0010->Print();
			
	cout << "For the Pi0 in 0-5% " << endl;
	TDirectoryFile* directoryPCMPi0PbPb2760GeV_0005 				= (TDirectoryFile*)filePCM->Get("Pi0_PbPb_2.76TeV_0-5%"); 
		TH1D* histoPCMPi0MassPbPb2760GeV_0005 						= (TH1D*)directoryPCMPi0PbPb2760GeV_0005->Get("MassPi0");
		TH1D* histoPCMPi0FWHMMeVPbPb2760GeV_0005 					= (TH1D*)directoryPCMPi0PbPb2760GeV_0005->Get("FWHMPi0MeV");
		TH1D* histoPCMPi0TrueMassPbPb2760GeV_0005 					= (TH1D*)directoryPCMPi0PbPb2760GeV_0005->Get("TrueMassPi0");
		TH1D* histoPCMPi0TrueFWHMMeVPbPb2760GeV_0005 				= (TH1D*)directoryPCMPi0PbPb2760GeV_0005->Get("TrueFWHMPi0MeV");
		TH1D* histoPCMPi0AccPbPb2760GeV_0005 						= (TH1D*)directoryPCMPi0PbPb2760GeV_0005->Get("Pi0_Acceptance");
		TH1D* histoPCMPi0TrueEffPtPbPb2760GeV_0005 					= (TH1D*)directoryPCMPi0PbPb2760GeV_0005->Get("Pi0_Efficiency");
		
		TH1D* histoPCMPi0InvYieldPbPb2760GeV_0005 					= (TH1D*)directoryPCMPi0PbPb2760GeV_0005->Get("CorrectedYieldPi0");   
		TGraphAsymmErrors* graphPCMPi0InvYieldStatPbPb2760GeV_0005 	= new TGraphAsymmErrors(histoPCMPi0InvYieldPbPb2760GeV_0005);
			graphPCMPi0InvYieldStatPbPb2760GeV_0005->RemovePoint(0);
			
		TGraphAsymmErrors* graphPCMPi0InvYieldSysA2760GeV_0005			= (TGraphAsymmErrors*)directoryPCMPi0PbPb2760GeV_0005->Get("Pi0SystErrorA");
			graphPCMPi0InvYieldSysA2760GeV_0005->RemovePoint(graphPCMPi0InvYieldSysA2760GeV_0005->GetN()-1);

		TGraphAsymmErrors* graphPCMPi0CorrYieldSysErrPbPb2760GeV_0005 	= (TGraphAsymmErrors*)directoryPCMPi0PbPb2760GeV_0005->Get("Pi0SystError"); 
			graphPCMPi0CorrYieldSysErrPbPb2760GeV_0005->RemovePoint(graphPCMPi0CorrYieldSysErrPbPb2760GeV_0005->GetN()-1);

		TGraphAsymmErrors* graphPCMPi0InvYieldSysPbPb2760GeV_0005		= (TGraphAsymmErrors*)directoryPCMPi0PbPb2760GeV_0005->Get("Pi0SystError");
			graphPCMPi0InvYieldSysPbPb2760GeV_0005->RemovePoint(graphPCMPi0InvYieldSysPbPb2760GeV_0005->GetN()-1);

		TGraphAsymmErrors* graphPCMPi0RAAStat2760GeV_0005	= (TGraphAsymmErrors*)directoryPCMPi0PbPb2760GeV_0005->Get("Pi0RAA");
		TGraphAsymmErrors* graphPCMPi0RAASys2760GeV_0005	= (TGraphAsymmErrors*)directoryPCMPi0PbPb2760GeV_0005->Get("Pi0RAASys");

		TH1D* ratioPCMPi0MassMCDiffData_0005 = (TH1D*)histoPCMPi0TrueMassPbPb2760GeV_0005->Clone("ratioPCMPi0MassMCDiffData_0005");
			ratioPCMPi0MassMCDiffData_0005->Sumw2();
			ratioPCMPi0MassMCDiffData_0005->Add(histoPCMPi0MassPbPb2760GeV_0005,-1);
			ratioPCMPi0MassMCDiffData_0005->Divide(ratioPCMPi0MassMCDiffData_0005, histoPCMPi0MassPbPb2760GeV_0005,1.,1.,"");
			ratioPCMPi0MassMCDiffData_0005->Scale(1./mesonMassExpectPi0);

 		TH1D *histoPCMPi0AccTimesEffPbPb2760GeV_0005 = (TH1D*)histoPCMPi0TrueEffPtPbPb2760GeV_0005->Clone("histoPCMPi0AccTimesEffPbPb2760GeV_0005");
			histoPCMPi0AccTimesEffPbPb2760GeV_0005->Sumw2();
			histoPCMPi0AccTimesEffPbPb2760GeV_0005->Multiply(histoPCMPi0AccPbPb2760GeV_0005);

	cout << "For the Pi0 in 20-40% " << endl;
	TDirectoryFile* directoryPCMPi0PbPb2760GeV_2040 				= (TDirectoryFile*)filePCM->Get("Pi0_PbPb_2.76TeV_20-40%"); 
		TH1D* histoPCMPi0MassPbPb2760GeV_2040 						= (TH1D*)directoryPCMPi0PbPb2760GeV_2040->Get("MassPi0");
		TH1D* histoPCMPi0FWHMMeVPbPb2760GeV_2040 					= (TH1D*)directoryPCMPi0PbPb2760GeV_2040->Get("FWHMPi0MeV");
		TH1D* histoPCMPi0TrueMassPbPb2760GeV_2040 					= (TH1D*)directoryPCMPi0PbPb2760GeV_2040->Get("TrueMassPi0");
		TH1D* histoPCMPi0TrueFWHMMeVPbPb2760GeV_2040 				= (TH1D*)directoryPCMPi0PbPb2760GeV_2040->Get("TrueFWHMPi0MeV");
		TH1D* histoPCMPi0AccPbPb2760GeV_2040 						= (TH1D*)directoryPCMPi0PbPb2760GeV_2040->Get("Pi0_Acceptance");
		TH1D* histoPCMPi0TrueEffPtPbPb2760GeV_2040 					= (TH1D*)directoryPCMPi0PbPb2760GeV_2040->Get("Pi0_Efficiency");
		
		TH1D* histoPCMPi0InvYieldPbPb2760GeV_2040 					= (TH1D*)directoryPCMPi0PbPb2760GeV_2040->Get("CorrectedYieldPi0");   
		TGraphAsymmErrors* graphPCMPi0InvYieldStatPbPb2760GeV_2040 	= new TGraphAsymmErrors(histoPCMPi0InvYieldPbPb2760GeV_2040);
			graphPCMPi0InvYieldStatPbPb2760GeV_2040->RemovePoint(0);
			
		TGraphAsymmErrors* graphPCMPi0InvYieldSysA2760GeV_2040			= (TGraphAsymmErrors*)directoryPCMPi0PbPb2760GeV_2040->Get("Pi0SystErrorA");
			graphPCMPi0InvYieldSysA2760GeV_2040->RemovePoint(graphPCMPi0InvYieldSysA2760GeV_2040->GetN()-1);

		TGraphAsymmErrors* graphPCMPi0CorrYieldSysErrPbPb2760GeV_2040 	= (TGraphAsymmErrors*)directoryPCMPi0PbPb2760GeV_2040->Get("Pi0SystError"); 
			graphPCMPi0CorrYieldSysErrPbPb2760GeV_2040->RemovePoint(graphPCMPi0CorrYieldSysErrPbPb2760GeV_2040->GetN()-1);

		TGraphAsymmErrors* graphPCMPi0InvYieldSysPbPb2760GeV_2040		= (TGraphAsymmErrors*)directoryPCMPi0PbPb2760GeV_2040->Get("Pi0SystError");
			graphPCMPi0InvYieldSysPbPb2760GeV_2040->RemovePoint(graphPCMPi0InvYieldSysPbPb2760GeV_2040->GetN()-1);

		TGraphAsymmErrors* graphPCMPi0RAAStat2760GeV_2040	= (TGraphAsymmErrors*)directoryPCMPi0PbPb2760GeV_2040->Get("Pi0RAA");
		TH1D* histoPCMPi0RAAStatPbPb2760GeV_2040 = (TH1D*)GraphAsymErrorsToHist(graphPCMPi0RAAStat2760GeV_2040,14,"histoPCMPi0RAAStatPbPb2760GeV_2040");
		TGraphAsymmErrors* graphPCMPi0RAASys2760GeV_2040	= (TGraphAsymmErrors*)directoryPCMPi0PbPb2760GeV_2040->Get("Pi0RAASys");

		TH1D* ratioPCMPi0MassMCDiffData_2040 = (TH1D*)histoPCMPi0TrueMassPbPb2760GeV_2040->Clone("ratioPCMPi0MassMCDiffData_2040");
			ratioPCMPi0MassMCDiffData_2040->Sumw2();
			ratioPCMPi0MassMCDiffData_2040->Add(histoPCMPi0MassPbPb2760GeV_2040,-1);
			ratioPCMPi0MassMCDiffData_2040->Divide(ratioPCMPi0MassMCDiffData_2040, histoPCMPi0MassPbPb2760GeV_2040,1.,1.,"");
			ratioPCMPi0MassMCDiffData_2040->Scale(1./mesonMassExpectPi0);

 		TH1D *histoPCMPi0AccTimesEffPbPb2760GeV_2040 = (TH1D*)histoPCMPi0TrueEffPtPbPb2760GeV_2040->Clone("histoPCMPi0AccTimesEffPbPb2760GeV_2040");
			histoPCMPi0AccTimesEffPbPb2760GeV_2040->Sumw2();
			histoPCMPi0AccTimesEffPbPb2760GeV_2040->Multiply(histoPCMPi0AccPbPb2760GeV_2040);			
			
// 		cout << "printing the spectra" << endl;
// 			graphPCMInvYieldStatPbPb2760GeV_2040->Print();
// 			graphPCMInvYieldSysPbPb2760GeV_2040->Print();

		
	cout << "For the Pi0 in 20-50% " << endl;
	TDirectory* directoryPCMPi0PbPb2760GeV_2050 					= (TDirectory*)filePCM->Get("Pi0_PbPb_2.76TeV_20-50%"); 
		TH1D* histoPCMPi0MassPbPb2760GeV_2050 						= (TH1D*)directoryPCMPi0PbPb2760GeV_2050->Get("MassPi0");
		TH1D* histoPCMPi0FWHMMeVPbPb2760GeV_2050 					= (TH1D*)directoryPCMPi0PbPb2760GeV_2050->Get("FWHMPi0MeV");
		TH1D* histoPCMPi0TrueMassPbPb2760GeV_2050 					= (TH1D*)directoryPCMPi0PbPb2760GeV_2050->Get("TrueMassPi0");
		TH1D* histoPCMPi0TrueFWHMMeVPbPb2760GeV_2050 				= (TH1D*)directoryPCMPi0PbPb2760GeV_2050->Get("TrueFWHMPi0MeV");
		TH1D* histoPCMPi0AccPbPb2760GeV_2050 						= (TH1D*)directoryPCMPi0PbPb2760GeV_2050->Get("Pi0_Acceptance");
		TH1D* histoPCMPi0TrueEffPtPbPb2760GeV_2050 					= (TH1D*)directoryPCMPi0PbPb2760GeV_2050->Get("Pi0_Efficiency");
		
	    TH1D* histoPCMPi0InvYieldPbPb2760GeV_2050 					= (TH1D*)directoryPCMPi0PbPb2760GeV_2050->Get("CorrectedYieldPi0");   
		TGraphAsymmErrors* graphPCMPi0InvYieldStatPbPb2760GeV_2050 	= new TGraphAsymmErrors(histoPCMPi0InvYieldPbPb2760GeV_2050);
			graphPCMPi0InvYieldStatPbPb2760GeV_2050->RemovePoint(0);
						
		TGraphAsymmErrors* graphPCMPi0InvYieldSysA2760GeV_2050			= (TGraphAsymmErrors*)directoryPCMPi0PbPb2760GeV_2050->Get("Pi0SystErrorA");
			graphPCMPi0InvYieldSysA2760GeV_2050->RemovePoint(graphPCMPi0InvYieldSysA2760GeV_2050->GetN()-1);
		
		TGraphAsymmErrors* graphPCMPi0CorrYieldSysErrPbPb2760GeV_2050 	= (TGraphAsymmErrors*)directoryPCMPi0PbPb2760GeV_2050->Get("Pi0SystError"); 
			graphPCMPi0CorrYieldSysErrPbPb2760GeV_2050->RemovePoint(graphPCMPi0CorrYieldSysErrPbPb2760GeV_2050->GetN()-1);
		
		TGraphAsymmErrors* graphPCMPi0InvYieldSysPbPb2760GeV_2050	 	= (TGraphAsymmErrors*)directoryPCMPi0PbPb2760GeV_2050->Get("Pi0SystError");
			graphPCMPi0InvYieldSysPbPb2760GeV_2050->RemovePoint(graphPCMPi0InvYieldSysPbPb2760GeV_2050->GetN()-1);
				
		TGraphAsymmErrors* graphPCMPi0RAAStat2760GeV_2050	= (TGraphAsymmErrors*)directoryPCMPi0PbPb2760GeV_2050->Get("Pi0RAA");
		TH1D* histoPCMPi0RAAStatPbPb2760GeV_2050 = (TH1D*)GraphAsymErrorsToHist(graphPCMPi0RAAStat2760GeV_2050,14,"histoPCMPi0RAAStatPbPb2760GeV_2050");
		TGraphAsymmErrors* graphPCMPi0RAASys2760GeV_2050	= (TGraphAsymmErrors*)directoryPCMPi0PbPb2760GeV_2050->Get("Pi0RAASys");

		TH1D* ratioPCMPi0MassMCDiffData_2050 = (TH1D*)histoPCMPi0TrueMassPbPb2760GeV_2050->Clone("ratioPCMPi0MassMCDiffData_2050");
			ratioPCMPi0MassMCDiffData_2050->Sumw2();
			ratioPCMPi0MassMCDiffData_2050->Add(histoPCMPi0MassPbPb2760GeV_2050,-1);
			ratioPCMPi0MassMCDiffData_2050->Divide(ratioPCMPi0MassMCDiffData_2050, histoPCMPi0MassPbPb2760GeV_2050,1.,1.,"");
			ratioPCMPi0MassMCDiffData_2050->Scale(1./mesonMassExpectPi0);
		
 		TH1D* histoPCMPi0AccTimesEffPbPb2760GeV_2050 = (TH1D*)histoPCMPi0TrueEffPtPbPb2760GeV_2050->Clone("histoPCMPi0AccTimesEffPbPb2760GeV_2050");
			histoPCMPi0AccTimesEffPbPb2760GeV_2050->Sumw2();
			histoPCMPi0AccTimesEffPbPb2760GeV_2050->Multiply(histoPCMPi0AccPbPb2760GeV_2050);
			
		TGraphAsymmErrors* graphPCMPi0RCPStat2760GeV	= (TGraphAsymmErrors*)filePCM->Get("Pi0RCP");
		TGraphAsymmErrors* graphPCMPi0RCPSys2760GeV	= (TGraphAsymmErrors*)filePCM->Get("Pi0RCPsys");
		

	cout << "For the Eta in 0-10% " << endl;
	TDirectory* directoryPCMEtaPbPb2760GeV_0010 					= (TDirectory*)filePCM->Get("Eta_PbPb_2.76TeV_0-10%"); 
		TH1D* histoPCMEtaMassPbPb2760GeV_0010 						= (TH1D*)directoryPCMEtaPbPb2760GeV_0010->Get("MassEta");
		TH1D* histoPCMEtaFWHMMeVPbPb2760GeV_0010					= (TH1D*)directoryPCMEtaPbPb2760GeV_0010->Get("FWHMEtaMeV");
		TH1D* histoPCMEtaTrueMassPbPb2760GeV_0010 					= (TH1D*)directoryPCMEtaPbPb2760GeV_0010->Get("TrueMassEta");
		TH1D* histoPCMEtaTrueFWHMMeVPbPb2760GeV_0010 				= (TH1D*)directoryPCMEtaPbPb2760GeV_0010->Get("TrueFWHMEtaMeV");
		TH1D* histoPCMEtaAccPbPb2760GeV_0010 						= (TH1D*)directoryPCMEtaPbPb2760GeV_0010->Get("Eta_Acceptance");
		TH1D* histoPCMEtaTrueEffPtPbPb2760GeV_0010 					= (TH1D*)directoryPCMEtaPbPb2760GeV_0010->Get("Eta_Efficiency");
		
	    TH1D* histoPCMEtaInvYieldPbPb2760GeV_0010 					= (TH1D*)directoryPCMEtaPbPb2760GeV_0010->Get("CorrectedYieldEta");   
		TGraphAsymmErrors* graphPCMEtaInvYieldStatPbPb2760GeV_0010 	= new TGraphAsymmErrors(histoPCMEtaInvYieldPbPb2760GeV_0010);
			graphPCMEtaInvYieldStatPbPb2760GeV_0010->RemovePoint(0);
			graphPCMEtaInvYieldStatPbPb2760GeV_0010->RemovePoint(0);

		TGraphAsymmErrors* graphPCMEtaInvYieldSysA2760GeV_0010			= (TGraphAsymmErrors*)directoryPCMEtaPbPb2760GeV_0010->Get("EtaSystErrorA");
			graphPCMEtaInvYieldSysA2760GeV_0010->RemovePoint(0);
		
		TGraphAsymmErrors* graphPCMEtaCorrYieldSysErrPbPb2760GeV_0010 	= (TGraphAsymmErrors*)directoryPCMEtaPbPb2760GeV_0010->Get("EtaSystError"); 
 			graphPCMEtaCorrYieldSysErrPbPb2760GeV_0010->RemovePoint(0);

		TGraphAsymmErrors* graphPCMEtaInvYieldSysPbPb2760GeV_0010		= (TGraphAsymmErrors*)directoryPCMEtaPbPb2760GeV_0010->Get("EtaSystError");
			graphPCMEtaInvYieldSysPbPb2760GeV_0010->RemovePoint(0);
			
		TGraphAsymmErrors* graphPCMEtaRAAStat2760GeV_0010	= (TGraphAsymmErrors*)directoryPCMEtaPbPb2760GeV_0010->Get("EtaRAA");
		TH1D* histoPCMEtaRAAStatPbPb2760GeV_0010 = (TH1D*)GraphAsymErrorsToHist(graphPCMEtaRAAStat2760GeV_0010,10,"histoPCMEtaRAAStatPbPb2760GeV_0010");
		TGraphAsymmErrors* graphPCMEtaRAASys2760GeV_0010	= (TGraphAsymmErrors*)directoryPCMEtaPbPb2760GeV_0010->Get("EtaRAASys");

		TH1D* histoPCMEtatoPi0Stat2760GeV_0010 					= (TH1D*)directoryPCMEtaPbPb2760GeV_0010->Get("EtatoPi0Ratio"); 
		TGraphAsymmErrors* graphPCMEtatoPi0Stat2760GeV_0010	= new TGraphAsymmErrors(histoPCMEtatoPi0Stat2760GeV_0010);
		graphPCMEtatoPi0Stat2760GeV_0010->RemovePoint(0);
		graphPCMEtatoPi0Stat2760GeV_0010->RemovePoint(0);

		TGraphAsymmErrors* graphPCMEtatoPi0Sys2760GeV_0010	= (TGraphAsymmErrors*)directoryPCMEtaPbPb2760GeV_0010->Get("EtatoPi0RatioSys");
		graphPCMEtatoPi0Sys2760GeV_0010->RemovePoint(graphPCMEtatoPi0Sys2760GeV_0010->GetN()-1);

		TH1D* ratioPCMEtaMassMCDiffData_0010						= (TH1D*)histoPCMEtaTrueMassPbPb2760GeV_0010->Clone("ratioPCMEtaMassMCDiffData_0010");
			ratioPCMEtaMassMCDiffData_0010->Sumw2();
			ratioPCMEtaMassMCDiffData_0010->Add(histoPCMEtaMassPbPb2760GeV_0010,-1);
			ratioPCMEtaMassMCDiffData_0010->Divide(ratioPCMEtaMassMCDiffData_0010, histoPCMEtaMassPbPb2760GeV_0010,1.,1.,"");
			ratioPCMEtaMassMCDiffData_0010->Scale(1./mesonMassExpectEta);
		
 		TH1D* histoPCMEtaAccTimesEffPbPb2760GeV_0010				= (TH1D*)histoPCMEtaTrueEffPtPbPb2760GeV_0010->Clone("histoPCMEtaAccTimesEffPbPb2760GeV_0010");
			histoPCMEtaAccTimesEffPbPb2760GeV_0010->Sumw2();
			histoPCMEtaAccTimesEffPbPb2760GeV_0010->Multiply(histoPCMEtaAccPbPb2760GeV_0010);
		
		
	cout << "For the Eta in 20-50% " << endl;
	TDirectory* directoryPCMEtaPbPb2760GeV_2050 					= (TDirectory*)filePCM->Get("Eta_PbPb_2.76TeV_20-50%"); 
		TH1D* histoPCMEtaMassPbPb2760GeV_2050 						= (TH1D*)directoryPCMEtaPbPb2760GeV_2050->Get("MassEta");
		TH1D* histoPCMEtaFWHMMeVPbPb2760GeV_2050 					= (TH1D*)directoryPCMEtaPbPb2760GeV_2050->Get("FWHMEtaMeV");
		TH1D* histoPCMEtaTrueMassPbPb2760GeV_2050 					= (TH1D*)directoryPCMEtaPbPb2760GeV_2050->Get("TrueMassEta");
		TH1D* histoPCMEtaTrueFWHMMeVPbPb2760GeV_2050 				= (TH1D*)directoryPCMEtaPbPb2760GeV_2050->Get("TrueFWHMEtaMeV");
		TH1D* histoPCMEtaAccPbPb2760GeV_2050 						= (TH1D*)directoryPCMEtaPbPb2760GeV_2050->Get("Eta_Acceptance");
		TH1D* histoPCMEtaTrueEffPtPbPb2760GeV_2050 					= (TH1D*)directoryPCMEtaPbPb2760GeV_2050->Get("Eta_Efficiency");
		
	    TH1D* histoPCMEtaInvYieldPbPb2760GeV_2050 					= (TH1D*)directoryPCMEtaPbPb2760GeV_2050->Get("CorrectedYieldEta"); 
		TGraphAsymmErrors* graphPCMEtaInvYieldStatPbPb2760GeV_2050 	= new TGraphAsymmErrors(histoPCMEtaInvYieldPbPb2760GeV_2050);
			graphPCMEtaInvYieldStatPbPb2760GeV_2050->RemovePoint(0);
			graphPCMEtaInvYieldStatPbPb2760GeV_2050->RemovePoint(0);
			
		TGraphAsymmErrors* graphPCMEtaInvYieldSysA2760GeV_2050	= (TGraphAsymmErrors*)directoryPCMEtaPbPb2760GeV_2050->Get("EtaSystErrorA");
			graphPCMEtaInvYieldSysA2760GeV_2050->RemovePoint(0);

		TGraphAsymmErrors* graphPCMEtaCorrYieldSysErrPbPb2760GeV_2050 	= (TGraphAsymmErrors*)directoryPCMEtaPbPb2760GeV_2050->Get("EtaSystError"); 
	 		graphPCMEtaCorrYieldSysErrPbPb2760GeV_2050->RemovePoint(0);
			
		TGraphAsymmErrors* graphPCMEtaInvYieldSysPbPb2760GeV_2050		= (TGraphAsymmErrors*)directoryPCMEtaPbPb2760GeV_2050->Get("EtaSystError");
 			graphPCMEtaInvYieldSysPbPb2760GeV_2050->RemovePoint(0);

		TGraphAsymmErrors* graphPCMEtaRAAStat2760GeV_2050	= (TGraphAsymmErrors*)directoryPCMEtaPbPb2760GeV_2050->Get("EtaRAA");
		TH1D* histoPCMEtaRAAStatPbPb2760GeV_2050 = (TH1D*)GraphAsymErrorsToHist(graphPCMEtaRAAStat2760GeV_2050,10,"histoPCMEtaRAAStatPbPb2760GeV_2050");
		TGraphAsymmErrors* graphPCMEtaRAASys2760GeV_2050	= (TGraphAsymmErrors*)directoryPCMEtaPbPb2760GeV_2050->Get("EtaRAASys");

		TH1D* histoPCMEtatoPi0Stat2760GeV_2050 					= (TH1D*)directoryPCMEtaPbPb2760GeV_2050->Get("EtatoPi0Ratio"); 
		TGraphAsymmErrors* graphPCMEtatoPi0Stat2760GeV_2050	= new TGraphAsymmErrors(histoPCMEtatoPi0Stat2760GeV_2050);
			graphPCMEtatoPi0Stat2760GeV_2050->RemovePoint(0);
			graphPCMEtatoPi0Stat2760GeV_2050->RemovePoint(0);

		TGraphAsymmErrors* graphPCMEtatoPi0Sys2760GeV_2050	= (TGraphAsymmErrors*)directoryPCMEtaPbPb2760GeV_2050->Get("EtatoPi0RatioSys");
			graphPCMEtatoPi0Sys2760GeV_2050->RemovePoint(graphPCMEtatoPi0Sys2760GeV_2050->GetN()-1);

		TH1D* ratioPCMEtaMassMCDiffData_2050						= (TH1D*)histoPCMEtaTrueMassPbPb2760GeV_2050->Clone("ratioPCMEtaMassMCDiffData_2050");
			ratioPCMEtaMassMCDiffData_2050->Sumw2();
			ratioPCMEtaMassMCDiffData_2050->Add(histoPCMEtaMassPbPb2760GeV_2050,-1);
			ratioPCMEtaMassMCDiffData_2050->Divide(ratioPCMEtaMassMCDiffData_2050, histoPCMEtaMassPbPb2760GeV_2050,1.,1.,"");
			ratioPCMEtaMassMCDiffData_2050->Scale(1./mesonMassExpectEta);
		
 		TH1D* histoPCMEtaAccTimesEffPbPb2760GeV_2050				= (TH1D*)histoPCMEtaTrueEffPtPbPb2760GeV_2050->Clone("histoPCMEtaAccTimesEffPbPb2760GeV_2050");
			histoPCMEtaAccTimesEffPbPb2760GeV_2050->Sumw2();
			histoPCMEtaAccTimesEffPbPb2760GeV_2050->Multiply(histoPCMEtaAccPbPb2760GeV_2050);	
			
// 		TGraphAsymmErrors* graphPCMEtaRCPStat2760GeV	= (TGraphAsymmErrors*)filePCM->Get("EtaRCP");
// 		TGraphAsymmErrors* graphPCMEtaRCPSys2760GeV	= (TGraphAsymmErrors*)filePCM->Get("EtaRCPsys");

	histoPCMPi0MassPbPb2760GeV_0010->Scale(1000.);
	histoPCMPi0TrueMassPbPb2760GeV_0010->Scale(1000.);
	histoPCMEtaMassPbPb2760GeV_0010->Scale(1000.);
	histoPCMEtaTrueMassPbPb2760GeV_0010->Scale(1000.);
	
	histoPCMPi0MassPbPb2760GeV_2050->Scale(1000.);
	histoPCMPi0TrueMassPbPb2760GeV_2050->Scale(1000.);
	histoPCMEtaMassPbPb2760GeV_2050->Scale(1000.);
	histoPCMEtaTrueMassPbPb2760GeV_2050->Scale(1000.);
	
	
	
	//**************************** EMCal Pb-Pb data 2011 ****************************//
	cout << "Loading EMCal histos" << endl;	
	TFile* fileEMCal								= new TFile(Form("LHC11hExternalInputs/%s",fileNameEMCalFull.Data()));
	
	//for EMCal file with histos, used naming below
	TDirectory* directoryEMCalPi0PbPb2760GeV 				= (TDirectory*)fileEMCal->Get("Pi02.76TeV_PbPb");
	cout << "Pi0 0-10%" << endl;
		TH1D* histoEMCalPi0InvYieldPbPb2760GeV_0010			= (TH1D*)directoryEMCalPi0PbPb2760GeV->Get("InvYieldPbPbStatErrPi_0010");
		TGraphAsymmErrors* graphEMCalPi0InvYieldStatPbPb2760GeV_0010 		= new TGraphAsymmErrors(histoEMCalPi0InvYieldPbPb2760GeV_0010);
			graphEMCalPi0InvYieldStatPbPb2760GeV_0010->RemovePoint(graphEMCalPi0InvYieldStatPbPb2760GeV_0010->GetN()-1);
			graphEMCalPi0InvYieldStatPbPb2760GeV_0010->RemovePoint(graphEMCalPi0InvYieldStatPbPb2760GeV_0010->GetN()-1);

		TH1D* histoEMCalPi0InvYieldSysPbPb2760GeV_0010 	= (TH1D*)directoryEMCalPi0PbPb2760GeV->Get("InvYieldPbPbSysErrPi_0010");
		TGraphAsymmErrors* graphEMCalPi0CorrYieldSysErrPbPb2760GeV_0010 	= new TGraphAsymmErrors(histoEMCalPi0InvYieldSysPbPb2760GeV_0010); 
			graphEMCalPi0CorrYieldSysErrPbPb2760GeV_0010->RemovePoint(graphEMCalPi0CorrYieldSysErrPbPb2760GeV_0010->GetN()-1);
			graphEMCalPi0CorrYieldSysErrPbPb2760GeV_0010->RemovePoint(graphEMCalPi0CorrYieldSysErrPbPb2760GeV_0010->GetN()-1);

		TGraphAsymmErrors* graphEMCalPi0InvYieldSysPbPb2760GeV_0010 	= new TGraphAsymmErrors(histoEMCalPi0InvYieldSysPbPb2760GeV_0010);
			graphEMCalPi0InvYieldSysPbPb2760GeV_0010->RemovePoint(graphEMCalPi0InvYieldSysPbPb2760GeV_0010->GetN()-1);
			graphEMCalPi0InvYieldSysPbPb2760GeV_0010->RemovePoint(graphEMCalPi0InvYieldSysPbPb2760GeV_0010->GetN()-1);

		TH1D*	histoEMCalEtatoPi0StatPbPb2760GeV_0010 	= (TH1D*)directoryEMCalPi0PbPb2760GeV->Get("StatErrEtatoPi0Ratio_0010");
		TGraphAsymmErrors* graphEMCalEtatoPi0Stat2760GeV_0010 	= new TGraphAsymmErrors(histoEMCalEtatoPi0StatPbPb2760GeV_0010);
			graphEMCalEtatoPi0Stat2760GeV_0010->RemovePoint(graphEMCalEtatoPi0Stat2760GeV_0010->GetN()-1);
			graphEMCalEtatoPi0Stat2760GeV_0010->RemovePoint(graphEMCalEtatoPi0Stat2760GeV_0010->GetN()-1);

		TH1D*	histoEMCalEtatoPi0SysPbPb2760GeV_0010 	= (TH1D*)directoryEMCalPi0PbPb2760GeV->Get("SysErrEtatoPi0Ratio_0010");
		TGraphAsymmErrors* graphEMCalEtatoPi0Sys2760GeV_0010 	= new TGraphAsymmErrors(histoEMCalEtatoPi0SysPbPb2760GeV_0010);
			graphEMCalEtatoPi0Sys2760GeV_0010->RemovePoint(graphEMCalEtatoPi0Sys2760GeV_0010->GetN()-1);
			graphEMCalEtatoPi0Sys2760GeV_0010->RemovePoint(graphEMCalEtatoPi0Sys2760GeV_0010->GetN()-1);
		
	cout << "Pi0 20-50%" << endl;		
		TH1D* histoEMCalPi0InvYieldPbPb2760GeV_2050			= (TH1D*)directoryEMCalPi0PbPb2760GeV->Get("InvYieldPbPbStatErrPi_2050");
		TGraphAsymmErrors* graphEMCalPi0InvYieldStatPbPb2760GeV_2050 		= new TGraphAsymmErrors(histoEMCalPi0InvYieldPbPb2760GeV_2050);
			graphEMCalPi0InvYieldStatPbPb2760GeV_2050->RemovePoint(graphEMCalPi0InvYieldStatPbPb2760GeV_2050->GetN()-1);
			graphEMCalPi0InvYieldStatPbPb2760GeV_2050->RemovePoint(graphEMCalPi0InvYieldStatPbPb2760GeV_2050->GetN()-1);

		TH1D* histoEMCalPi0InvYieldSysPbPb2760GeV_2050 	= (TH1D*)directoryEMCalPi0PbPb2760GeV->Get("InvYieldPbPbSysErrPi_2050");
		TGraphAsymmErrors* graphEMCalPi0CorrYieldSysErrPbPb2760GeV_2050 	= new TGraphAsymmErrors(histoEMCalPi0InvYieldSysPbPb2760GeV_2050); 
			graphEMCalPi0CorrYieldSysErrPbPb2760GeV_2050->RemovePoint(graphEMCalPi0CorrYieldSysErrPbPb2760GeV_2050->GetN()-1);
			graphEMCalPi0CorrYieldSysErrPbPb2760GeV_2050->RemovePoint(graphEMCalPi0CorrYieldSysErrPbPb2760GeV_2050->GetN()-1);

		TGraphAsymmErrors* graphEMCalPi0InvYieldSysPbPb2760GeV_2050 	= new TGraphAsymmErrors(histoEMCalPi0InvYieldSysPbPb2760GeV_2050);
			graphEMCalPi0InvYieldSysPbPb2760GeV_2050->RemovePoint(graphEMCalPi0InvYieldSysPbPb2760GeV_2050->GetN()-1);
			graphEMCalPi0InvYieldSysPbPb2760GeV_2050->RemovePoint(graphEMCalPi0InvYieldSysPbPb2760GeV_2050->GetN()-1);

		TH1D*	histoEMCalEtatoPi0StatPbPb2760GeV_2050 	= (TH1D*)directoryEMCalPi0PbPb2760GeV->Get("StatErrEtatoPi0Ratio_2050");
		TGraphAsymmErrors* graphEMCalEtatoPi0Stat2760GeV_2050 	= new TGraphAsymmErrors(histoEMCalEtatoPi0StatPbPb2760GeV_2050);
			graphEMCalEtatoPi0Stat2760GeV_2050->RemovePoint(graphEMCalEtatoPi0Stat2760GeV_2050->GetN()-1);
			graphEMCalEtatoPi0Stat2760GeV_2050->RemovePoint(graphEMCalEtatoPi0Stat2760GeV_2050->GetN()-1);

		TH1D*	histoEMCalEtatoPi0SysPbPb2760GeV_2050 	= (TH1D*)directoryEMCalPi0PbPb2760GeV->Get("SysErrEtatoPi0Ratio_2050");
		TGraphAsymmErrors* graphEMCalEtatoPi0Sys2760GeV_2050 	= new TGraphAsymmErrors(histoEMCalEtatoPi0SysPbPb2760GeV_2050);
			graphEMCalEtatoPi0Sys2760GeV_2050->RemovePoint(graphEMCalEtatoPi0Sys2760GeV_2050->GetN()-1);
			graphEMCalEtatoPi0Sys2760GeV_2050->RemovePoint(graphEMCalEtatoPi0Sys2760GeV_2050->GetN()-1);

// 		TH1D*	histoEMCalPi0RCPStatPbPb2760GeV 	= (TH1D*)directoryEMCalPi0PbPb2760GeV->Get("StatErrRcpPi");
// 		TGraphAsymmErrors* graphEMCalPi0RCPStat2760GeV 	= new TGraphAsymmErrors(histoEMCalPi0RCPStatPbPb2760GeV);
// 		TH1D*	histoEMCalPi0RCPSysPbPb2760GeV 	= (TH1D*)directoryEMCalPi0PbPb2760GeV->Get("SysErrRcpPi");
// 		TGraphAsymmErrors* graphEMCalPi0RCPSys2760GeV 	= new TGraphAsymmErrors(histoEMCalPi0RCPSysPbPb2760GeV);

		
	TDirectory* directoryEMCalEtaPbPb2760GeV 				= (TDirectory*)fileEMCal->Get("Eta2.76TeV_PbPb");
	cout << "Eta 0-10%" << endl;
		TH1D* histoEMCalEtaInvYieldPbPb2760GeV_0010			= (TH1D*)directoryEMCalEtaPbPb2760GeV->Get("InvYieldPbPbStatErrEta_0010");
		TGraphAsymmErrors* graphEMCalEtaInvYieldStatPbPb2760GeV_0010 		= new TGraphAsymmErrors(histoEMCalEtaInvYieldPbPb2760GeV_0010);
			graphEMCalEtaInvYieldStatPbPb2760GeV_0010->RemovePoint(graphEMCalEtaInvYieldStatPbPb2760GeV_0010->GetN()-1);
			graphEMCalEtaInvYieldStatPbPb2760GeV_0010->RemovePoint(graphEMCalEtaInvYieldStatPbPb2760GeV_0010->GetN()-1);

		TH1D*	histoEMCalEtaInvYieldSysPbPb2760GeV_0010 	= (TH1D*)directoryEMCalEtaPbPb2760GeV->Get("InvYieldPbPbSysErrEta_0010");
		TGraphAsymmErrors* graphEMCalEtaCorrYieldSysErrPbPb2760GeV_0010 	= new TGraphAsymmErrors(histoEMCalEtaInvYieldSysPbPb2760GeV_0010);
			graphEMCalEtaCorrYieldSysErrPbPb2760GeV_0010->RemovePoint(graphEMCalEtaCorrYieldSysErrPbPb2760GeV_0010->GetN()-1);
			graphEMCalEtaCorrYieldSysErrPbPb2760GeV_0010->RemovePoint(graphEMCalEtaCorrYieldSysErrPbPb2760GeV_0010->GetN()-1);

		TGraphAsymmErrors* graphEMCalEtaInvYieldSysPbPb2760GeV_0010 	= new TGraphAsymmErrors(histoEMCalEtaInvYieldSysPbPb2760GeV_0010);
			graphEMCalEtaInvYieldSysPbPb2760GeV_0010->RemovePoint(graphEMCalEtaInvYieldSysPbPb2760GeV_0010->GetN()-1);
			graphEMCalEtaInvYieldSysPbPb2760GeV_0010->RemovePoint(graphEMCalEtaInvYieldSysPbPb2760GeV_0010->GetN()-1);

	cout << "Eta 20-50%" << endl;		
		TH1D* histoEMCalEtaInvYieldPbPb2760GeV_2050			= (TH1D*)directoryEMCalEtaPbPb2760GeV->Get("InvYieldPbPbStatErrEta_2050");
		TGraphAsymmErrors* graphEMCalEtaInvYieldStatPbPb2760GeV_2050 		= new TGraphAsymmErrors(histoEMCalEtaInvYieldPbPb2760GeV_2050);
			graphEMCalEtaInvYieldStatPbPb2760GeV_2050->RemovePoint(graphEMCalEtaInvYieldStatPbPb2760GeV_2050->GetN()-1);
			graphEMCalEtaInvYieldStatPbPb2760GeV_2050->RemovePoint(graphEMCalEtaInvYieldStatPbPb2760GeV_2050->GetN()-1);

		TH1D*	histoEMCalEtaInvYieldSysPbPb2760GeV_2050 	= (TH1D*)directoryEMCalEtaPbPb2760GeV->Get("InvYieldPbPbSysErrEta_2050");
		TGraphAsymmErrors* graphEMCalEtaCorrYieldSysErrPbPb2760GeV_2050 	= new TGraphAsymmErrors(histoEMCalEtaInvYieldSysPbPb2760GeV_2050);
			graphEMCalEtaCorrYieldSysErrPbPb2760GeV_2050->RemovePoint(graphEMCalEtaCorrYieldSysErrPbPb2760GeV_2050->GetN()-1);
			graphEMCalEtaCorrYieldSysErrPbPb2760GeV_2050->RemovePoint(graphEMCalEtaCorrYieldSysErrPbPb2760GeV_2050->GetN()-1);

		TGraphAsymmErrors* graphEMCalEtaInvYieldSysPbPb2760GeV_2050 	= new TGraphAsymmErrors(histoEMCalEtaInvYieldSysPbPb2760GeV_2050);
			graphEMCalEtaInvYieldSysPbPb2760GeV_2050->RemovePoint(graphEMCalEtaInvYieldSysPbPb2760GeV_2050->GetN()-1);
			graphEMCalEtaInvYieldSysPbPb2760GeV_2050->RemovePoint(graphEMCalEtaInvYieldSysPbPb2760GeV_2050->GetN()-1);
		
// 		TH1D*	histoEMCalEtaRCPStatPbPb2760GeV 	= (TH1D*)directoryEMCalEtaPbPb2760GeV->Get("StatErrRcpEta");
// 		TGraphAsymmErrors* graphEMCalEtaRCPStat2760GeV 	= new TGraphAsymmErrors(histoEMCalEtaRCPStatPbPb2760GeV);

// 		TH1D*	histoEMCalEtaRCPSysPbPb2760GeV 	= (TH1D*)directoryEMCalEtaPbPb2760GeV->Get("SysErrRcpEta");
// 		TGraphAsymmErrors* graphEMCalEtaRCPSys2760GeV 	= new TGraphAsymmErrors(histoEMCalEtaRCPSysPbPb2760GeV);
		
	//Raa files from EMCal <----- with mt scaled spectra
	TFile* fileEMCalRaa								= new TFile("LHC11hExternalInputs/ppReferenceSpectraEMCal27August2015.root");
		TH1D*	histoEMCalPi0RAAStatPbPb2760GeV_0010 	= (TH1D*)fileEMCalRaa->Get("RAAStatPion010");
		TGraphAsymmErrors* graphEMCalPi0RAAStatPbPb2760GeV_0010 	= new TGraphAsymmErrors(histoEMCalPi0RAAStatPbPb2760GeV_0010);
			
		TH1D*	histoEMCalPi0RAASystPbPb2760GeV_0010 	= (TH1D*)fileEMCalRaa->Get("RAASysPion010");
		TGraphAsymmErrors* graphEMCalPi0RAASysPbPb2760GeV_0010 	= new TGraphAsymmErrors(histoEMCalPi0RAASystPbPb2760GeV_0010);

		TH1D*	histoEMCalPi0RAAStatPbPb2760GeV_2050 	= (TH1D*)fileEMCalRaa->Get("RAAStatPion2050");
		TGraphAsymmErrors* graphEMCalPi0RAAStatPbPb2760GeV_2050 	= new TGraphAsymmErrors(histoEMCalPi0RAAStatPbPb2760GeV_2050);
			
		TH1D*	histoEMCalPi0RAASystPbPb2760GeV_2050 	= (TH1D*)fileEMCalRaa->Get("RAASysPion2050");
		TGraphAsymmErrors* graphEMCalPi0RAASysPbPb2760GeV_2050 	= new TGraphAsymmErrors(histoEMCalPi0RAASystPbPb2760GeV_2050);


		TH1D*	histoEMCalEtaRAAStatPbPb2760GeV_0010 	= (TH1D*)fileEMCalRaa->Get("RAAStatEta010");
		TGraphAsymmErrors* graphEMCalEtaRAAStatPbPb2760GeV_0010 	= new TGraphAsymmErrors(histoEMCalEtaRAAStatPbPb2760GeV_0010);
			
		TH1D*	histoEMCalEtaRAASystPbPb2760GeV_0010 	= (TH1D*)fileEMCalRaa->Get("RAASysEta010");
		TGraphAsymmErrors* graphEMCalEtaRAASysPbPb2760GeV_0010 	= new TGraphAsymmErrors(histoEMCalEtaRAASystPbPb2760GeV_0010);

		TH1D*	histoEMCalEtaRAAStatPbPb2760GeV_2050 	= (TH1D*)fileEMCalRaa->Get("RAAStatEta2050");
		TGraphAsymmErrors* graphEMCalEtaRAAStatPbPb2760GeV_2050 	= new TGraphAsymmErrors(histoEMCalEtaRAAStatPbPb2760GeV_2050);
			
		TH1D*	histoEMCalEtaRAASystPbPb2760GeV_2050 	= (TH1D*)fileEMCalRaa->Get("RAASysEta2050");
		TGraphAsymmErrors* graphEMCalEtaRAASysPbPb2760GeV_2050 	= new TGraphAsymmErrors(histoEMCalEtaRAASystPbPb2760GeV_2050);
		
		
		
		
	// *******************************************************************************************************
	// ************************** Combination of different measurements **************************************
	// *******************************************************************************************************
	// REMARKS: 
	// 		- order of measurements defined in CombinePtPointsSpectraFullCorrMat from CombinationFunctions.h
	//		- correlations are defined in CombinePtPointsSpectraFullCorrMat from CombinationFunctions.h
	// 		- currently only PCM - EMCal vs others fully implemeted energy independent
	// 		- extendable to other energies
	//		- offsets have to be determined manually, see cout's in shell from combination function, more can be uncommented
		
	
	// definition of array of histograms (NULL - means we have no measurement at this energy for this rec-method)
	// for statistical error and final value from respective method
	TH1D* statErrorCollectionLHC11h_0010[11];
	TH1D* statErrorCollectionLHC11h_2050[11];
	TH1D* statErrorCollectionEtatoPi0LHC11h_0010[11];
	TH1D* statErrorCollectionEtatoPi0LHC11h_2050[11];
	TH1D* statErrorCollectionRaaLHC11h_0010[11];
	TH1D* statErrorCollectionRaaLHC11h_2050[11];

	TH1D* statErrorCollection_0010[11];
	TH1D* statErrorCollection_0005[11];
	TH1D* statErrorCollection_2040[11];
	TH1D* statErrorCollectionRaa_0010[11];
	TH1D* statErrorCollectionRaa_2040[11];

	for (Int_t i = 0; i< 11; i++){
		statErrorCollectionLHC11h_0010[i] = NULL;
		statErrorCollectionLHC11h_2050[i] = NULL;
		statErrorCollectionEtatoPi0LHC11h_0010[i] = NULL;
		statErrorCollectionEtatoPi0LHC11h_2050[i] = NULL;
		statErrorCollectionRaaLHC11h_0010[i] = NULL;
		statErrorCollectionRaaLHC11h_2050[i] = NULL;

		statErrorCollection_0010[i] = NULL;
		statErrorCollection_0005[i] = NULL;
		statErrorCollection_2040[i] = NULL;
		statErrorCollectionRaa_0010[i] = NULL;
		statErrorCollectionRaa_2040[i] = NULL;
		
	}	
	if(meson.CompareTo("Pi0")==0){
		// for combination PCM - EMCal 2011
		statErrorCollectionLHC11h_0010[0] = (TH1D*)histoPCMPi0InvYieldPbPb2760GeV_0010->Clone("statErrPCMPi0_0010");
		statErrorCollectionLHC11h_0010[2] = (TH1D*)histoEMCalPi0InvYieldPbPb2760GeV_0010->Clone("statErrEMCalPi0_0010");

		statErrorCollectionLHC11h_2050[0] = (TH1D*)histoPCMPi0InvYieldPbPb2760GeV_2050->Clone("statErrPCMPi0_2050");
		statErrorCollectionLHC11h_2050[2] = (TH1D*)histoEMCalPi0InvYieldPbPb2760GeV_2050->Clone("statErrEMCalPi0_2050");

		statErrorCollectionRaaLHC11h_0010[0] = (TH1D*)histoPCMPi0RAAStatPbPb2760GeV_0010->Clone("statErrPCMPi0RAA_0010");
		statErrorCollectionRaaLHC11h_0010[2] = (TH1D*)histoEMCalPi0RAAStatPbPb2760GeV_0010->Clone("statErrEMCalPi0RAA_0010");		

		statErrorCollectionRaaLHC11h_2050[0] = (TH1D*)histoPCMPi0RAAStatPbPb2760GeV_2050->Clone("statErrPCMPi0RAA_2050");
		statErrorCollectionRaaLHC11h_2050[2] = (TH1D*)histoEMCalPi0RAAStatPbPb2760GeV_2050->Clone("statErrEMCalPi0RAA_2050");		
		
		
		// for combination with published 2010
		statErrorCollection_0010[0] = (TH1D*)histoPCMPi0InvYieldPbPb2760GeV_0010->Clone("statErrPCMPi0_0010");
		statErrorCollection_0010[1] = (TH1D*)histoPi0PHOSPbPb0010->Clone("statErrPHOSPi0_0010");
// 		statErrorCollection_0010[2] = (TH1D*)histoEMCalPi0InvYieldPbPb2760GeV_0010->Clone("statErrEMCalPi0_0010");
		statErrorCollection_0010[10] = (TH1D*)histoPCMPublishedPi0InvYieldPbPb2760GeV_0010->Clone("statErrPCMPublishedPi0_0010");

		statErrorCollection_0005[0] = (TH1D*)histoPCMPi0InvYieldPbPb2760GeV_0005->Clone("statErrPCMPi0_0005");
		statErrorCollection_0005[1] = (TH1D*)histoPi0PHOSPbPb0005->Clone("statErrPHOSPi0_0005");
		statErrorCollection_0005[10] = (TH1D*)histoPCMPublishedPi0InvYieldPbPb2760GeV_0005->Clone("statErrPCMPublishedPi0_0005");

		statErrorCollection_2040[0] = (TH1D*)histoPCMPi0InvYieldPbPb2760GeV_2040->Clone("statErrPCMPi0_2040");
		statErrorCollection_2040[1] = (TH1D*)histoPi0PHOSPbPb2040->Clone("statErrPHOSPi0_2040");
		statErrorCollection_2040[10] = (TH1D*)histoPCMPublishedPi0InvYieldPbPb2760GeV_2040->Clone("statErrPCMPublishedPi0_2040");

		statErrorCollectionRaa_0010[0] = (TH1D*)histoPCMPi0RAAStatPbPb2760GeV_0010->Clone("statErrPCMPi0RAA_0010");
		statErrorCollectionRaa_0010[10] = (TH1D*)histoPCMPublishedPi0RAAStatPbPb2760GeV_0010->Clone("statErrPCMPublishedPi0RAA_0010");
		
		statErrorCollectionRaa_2040[0] = (TH1D*)histoPCMPi0RAAStatPbPb2760GeV_2040->Clone("statErrPCMPi0RAA_2040");
		statErrorCollectionRaa_2040[10] = (TH1D*)histoPCMPublishedPi0RAAStatPbPb2760GeV_2040->Clone("statErrPCMPublishedPi0RAA_2040");

		
 
	} else if(meson.CompareTo("Eta")==0) {
		
		statErrorCollectionLHC11h_0010[0] = (TH1D*)histoPCMEtaInvYieldPbPb2760GeV_0010->Clone("statErrPCMEta_0010");
		statErrorCollectionLHC11h_0010[2] = (TH1D*)histoEMCalEtaInvYieldPbPb2760GeV_0010->Clone("statErrEMCalEta_0010");
		
		statErrorCollectionLHC11h_2050[0] = (TH1D*)histoPCMEtaInvYieldPbPb2760GeV_2050->Clone("statErrPCMEta_2050");
		statErrorCollectionLHC11h_2050[2] = (TH1D*)histoEMCalEtaInvYieldPbPb2760GeV_2050->Clone("statErrEMCalEta_2050");

		statErrorCollectionEtatoPi0LHC11h_0010[0] = (TH1D*)histoPCMEtatoPi0Stat2760GeV_0010->Clone("statErrPCMEtatoPi0_0010");
		statErrorCollectionEtatoPi0LHC11h_0010[2] = (TH1D*)histoEMCalEtatoPi0StatPbPb2760GeV_0010->Clone("statErrEMCalEtatoPi0_0010");		

		statErrorCollectionEtatoPi0LHC11h_2050[0] = (TH1D*)histoPCMEtatoPi0Stat2760GeV_2050->Clone("statErrPCMEtatoPi0_2050");
		statErrorCollectionEtatoPi0LHC11h_2050[2] = (TH1D*)histoEMCalEtatoPi0StatPbPb2760GeV_2050->Clone("statErrEMCalEtatoPi0_2050");	
		
		statErrorCollectionRaaLHC11h_0010[0] = (TH1D*)histoPCMEtaRAAStatPbPb2760GeV_0010->Clone("statErrPCMEtaRAA_0010");
		statErrorCollectionRaaLHC11h_0010[2] = (TH1D*)histoEMCalEtaRAAStatPbPb2760GeV_0010->Clone("statErrEMCalEtaRAA_0010");		

		statErrorCollectionRaaLHC11h_2050[0] = (TH1D*)histoPCMEtaRAAStatPbPb2760GeV_2050->Clone("statErrPCMEtaRAA_2050");
		statErrorCollectionRaaLHC11h_2050[2] = (TH1D*)histoEMCalEtaRAAStatPbPb2760GeV_2050->Clone("statErrEMCalEtaRAA_2050");		

		
	}
	
	// definition of array of TGraphAsymmErrors (NULL - means we have no measurement at this energy for this rec-method)	
	// for systematic error from respective method
	TGraphAsymmErrors* sysErrorCollectionLHC11h_0010[11];
	TGraphAsymmErrors* sysErrorCollectionLHC11h_2050[11];
	TGraphAsymmErrors* sysErrorCollectionEtatoPi0LHC11h_0010[11];
	TGraphAsymmErrors* sysErrorCollectionEtatoPi0LHC11h_2050[11];
	TGraphAsymmErrors* sysErrorCollectionRaaLHC11h_0010[11];
	TGraphAsymmErrors* sysErrorCollectionRaaLHC11h_2050[11];
	
	
	TGraphAsymmErrors* sysErrorCollection_0010[11];
	TGraphAsymmErrors* sysErrorCollection_0005[11];
	TGraphAsymmErrors* sysErrorCollection_2040[11];
	TGraphAsymmErrors* sysErrorCollectionRaa_0010[11];
	TGraphAsymmErrors* sysErrorCollectionRaa_2040[11];


	for (Int_t i = 0; i< 11; i++){
		sysErrorCollectionLHC11h_0010[i] = NULL;
		sysErrorCollectionLHC11h_2050[i] = NULL;

		sysErrorCollectionEtatoPi0LHC11h_0010[i] = NULL;
		sysErrorCollectionEtatoPi0LHC11h_2050[i] = NULL;

		sysErrorCollectionRaaLHC11h_0010[i] = NULL;
		sysErrorCollectionRaaLHC11h_2050[i] = NULL;

		sysErrorCollection_0010[i] = NULL;
		sysErrorCollection_0005[i] = NULL;
		sysErrorCollection_2040[i] = NULL;
		sysErrorCollectionRaa_0010[i] = NULL;
		sysErrorCollectionRaa_2040[i] = NULL;

	}	
	if(meson.CompareTo("Pi0")==0){
		// for combination PCM - EMCal 2011
		sysErrorCollectionLHC11h_0010[0] = (TGraphAsymmErrors*)graphPCMPi0CorrYieldSysErrPbPb2760GeV_0010->Clone("sysErrPCMPi0_0010");
		sysErrorCollectionLHC11h_0010[2] = (TGraphAsymmErrors*)graphEMCalPi0CorrYieldSysErrPbPb2760GeV_0010->Clone("sysErrEMCalPi0_0010");

		sysErrorCollectionLHC11h_2050[0] = (TGraphAsymmErrors*)graphPCMPi0CorrYieldSysErrPbPb2760GeV_2050->Clone("sysErrPCMPi0_2050");
		sysErrorCollectionLHC11h_2050[2] = (TGraphAsymmErrors*)graphEMCalPi0CorrYieldSysErrPbPb2760GeV_2050->Clone("sysErrEMCalPi0_2050");

		sysErrorCollectionRaaLHC11h_0010[0] = (TGraphAsymmErrors*)graphPCMPi0RAASys2760GeV_0010->Clone("sysErrPCMPi0Raa_0010");
		sysErrorCollectionRaaLHC11h_0010[2] = (TGraphAsymmErrors*)graphEMCalPi0RAASysPbPb2760GeV_0010->Clone("sysErrEMCalPi0Raa_0010");	

		sysErrorCollectionRaaLHC11h_2050[0] = (TGraphAsymmErrors*)graphPCMPi0RAASys2760GeV_2050->Clone("sysErrPCMPi0Raa_2050");
		sysErrorCollectionRaaLHC11h_2050[2] = (TGraphAsymmErrors*)graphEMCalPi0RAASysPbPb2760GeV_2050->Clone("sysErrEMCalPi0Raa_2050");	

		
		// for combination with published 2010
		sysErrorCollection_0010[0] = (TGraphAsymmErrors*)graphPCMPi0CorrYieldSysErrPbPb2760GeV_0010->Clone("sysErrPCMPi0_0010");
		sysErrorCollection_0010[1] = (TGraphAsymmErrors*)graphPHOSPi0InvYieldSysPbPb2760GeV_0010->Clone("sysErrPHOSPi0_0010");
// 		sysErrorCollection_0010[2] = (TGraphAsymmErrors*)graphEMCalPi0CorrYieldSysErrPbPb2760GeV_0010->Clone("sysErrEMCalPi0_0010");
		sysErrorCollection_0010[10] = (TGraphAsymmErrors*)graphPCMPublishedPi0CorrYieldSysErrPbPb2760GeV_0010->Clone("sysErrPCMPublishedPi0_0010");

		sysErrorCollection_0005[0] = (TGraphAsymmErrors*)graphPCMPi0CorrYieldSysErrPbPb2760GeV_0005->Clone("sysErrPCMPi0_0005");
		sysErrorCollection_0005[1] = (TGraphAsymmErrors*)graphPHOSYieldPi0SysErrPbPb0005->Clone("sysErrPHOSPi0_0005");
		sysErrorCollection_0005[10] = (TGraphAsymmErrors*)graphPCMPublishedPi0CorrYieldSysErrPbPb2760GeV_0005->Clone("sysErrPCMPublishedPi0_0005");

		sysErrorCollection_2040[0] = (TGraphAsymmErrors*)graphPCMPi0CorrYieldSysErrPbPb2760GeV_2040->Clone("sysErrPCMPi0_2040");
		sysErrorCollection_2040[1] = (TGraphAsymmErrors*)graphPHOSPi0InvYieldSysPbPb2760GeV_2040->Clone("sysErrPHOSPi0_2040");
		sysErrorCollection_2040[10] = (TGraphAsymmErrors*)graphPCMPublishedPi0CorrYieldSysErrPbPb2760GeV_2040->Clone("sysErrPCMPublishedPi0_2040");

		sysErrorCollectionRaa_0010[0] = (TGraphAsymmErrors*)graphPCMPi0RAASys2760GeV_0010->Clone("sysErrPCMPi0Raa_0010");
		sysErrorCollectionRaa_0010[10] = (TGraphAsymmErrors*)graphPCMPublishedPi0RAASys2760GeV_0010->Clone("sysErrPCMPublishedPi0Raa_0010");	

		sysErrorCollectionRaa_2040[0] = (TGraphAsymmErrors*)graphPCMPi0RAASys2760GeV_2040->Clone("sysErrPCMPi0Raa_2040");
		sysErrorCollectionRaa_2040[10] = (TGraphAsymmErrors*)graphPCMPublishedPi0RAASys2760GeV_2040->Clone("sysErrPCMPublishedPi0Raa_2040");	

		
	} else if(meson.CompareTo("Eta")==0) {
		sysErrorCollectionLHC11h_0010[0] = (TGraphAsymmErrors*)graphPCMEtaCorrYieldSysErrPbPb2760GeV_0010->Clone("sysErrPCMEta_0010");
		sysErrorCollectionLHC11h_0010[2] = (TGraphAsymmErrors*)graphEMCalEtaCorrYieldSysErrPbPb2760GeV_0010->Clone("sysErrEMCalEta_0010");	
		
		sysErrorCollectionLHC11h_2050[0] = (TGraphAsymmErrors*)graphPCMEtaCorrYieldSysErrPbPb2760GeV_2050->Clone("sysErrPCMEta_2050");
		sysErrorCollectionLHC11h_2050[2] = (TGraphAsymmErrors*)graphEMCalEtaCorrYieldSysErrPbPb2760GeV_2050->Clone("sysErrEMCalEta_2050");

		sysErrorCollectionEtatoPi0LHC11h_0010[0] = (TGraphAsymmErrors*)graphPCMEtatoPi0Sys2760GeV_0010->Clone("sysErrPCMEtatoPi0_0010");
		sysErrorCollectionEtatoPi0LHC11h_0010[2] = (TGraphAsymmErrors*)graphEMCalEtatoPi0Sys2760GeV_0010->Clone("sysErrEMCalEtatoPi0_0010");	

		sysErrorCollectionEtatoPi0LHC11h_2050[0] = (TGraphAsymmErrors*)graphPCMEtatoPi0Sys2760GeV_2050->Clone("sysErrPCMEtatoPi0_2050");
		sysErrorCollectionEtatoPi0LHC11h_2050[2] = (TGraphAsymmErrors*)graphEMCalEtatoPi0Sys2760GeV_2050->Clone("sysErrEMCalEtatoPi0_2050");	

		sysErrorCollectionRaaLHC11h_0010[0] = (TGraphAsymmErrors*)graphPCMEtaRAASys2760GeV_0010->Clone("sysErrPCMEtaRaa_0010");
		sysErrorCollectionRaaLHC11h_0010[2] = (TGraphAsymmErrors*)graphEMCalEtaRAASysPbPb2760GeV_0010->Clone("sysErrEMCalEtaRaa_0010");	

		sysErrorCollectionRaaLHC11h_2050[0] = (TGraphAsymmErrors*)graphPCMEtaRAASys2760GeV_2050->Clone("sysErrPCMEtaRaa_2050");
		sysErrorCollectionRaaLHC11h_2050[2] = (TGraphAsymmErrors*)graphEMCalEtaRAASysPbPb2760GeV_2050->Clone("sysErrEMCalEtaRaa_2050");	

	}
	
	// Definition of final pt binning (has to be set manually)
	Double_t xPtLimitsPi0[24] =  {0.0, 0.4, 0.6, 0.8, 1.0,
								  1.2, 1.4, 1.6, 1.8, 2.0,
								  2.2, 2.4, 2.6, 3.0, 3.5,
								  4.0, 5.0, 6.0, 8.0, 10.0, 
								  12.0, 14.,17.,20.};
	Double_t xPtLimitsEta[14] =  {0.0, 0.5, 1.0, 1.5, 2,
								  3.0, 4.0, 6.0, 8.0, 10.,
								  12., 14., 17., 20.};
// 	Double_t xPtLimitsEta[18] =  {0.0, 0.6, 1.0, 1.4, 1.8,
// 								  2.2, 2.6, 3.0 ,3.5, 4., 
// 								  5.,  6.0, 8.0, 10,  12., 
// 								  14., 20., 30.};

	// matrix order: 	= {"PCM", "PHOS", "EMCal", "PCM-PHOS", "PCM - EMCal", 
	//					  "PCM-Dalitz", "PHOS-Dalitz", "EMCal-Dalitz", "EMCal high pT", "EMCal merged"};
	// Definition of offsets for stat & sys see output of function in shell, make sure pt bins match							
	Int_t offSetsPi0[11]	= 	{ 0, 2, 15, 0, 0,
								  0, 0, 0, 0, 0, 0};
	Int_t offSetsPi0Sys[11]= 	{ 1, 3, 15, 0, 0,
								  0, 0, 0, 0, 0, 1};
								
	Int_t offSetsEta[11]	= 	{ 0, 0, 6, 0, 0,
								  0, 0, 0, 0, 0, 0};//qui
	Int_t offSetsEtaSys[11]= 	{ 2, 0, 6, 0, 0,
								  0, 0, 0, 0, 0, 0};
// 	Int_t offSetsEta[11]	= 	{ 0, 0, 10, 0, 0,
// 								  0, 0, 0, 0, 0, 0};//qui
// 	Int_t offSetsEtaSys[11]= 	{ 1, 0, 10, 0, 0,
// 								  0, 0, 0, 0, 0, 0};
									
								  
	Int_t textSizeLabelsPixel = 900*0.04;
	TCanvas* canvasWeights = new TCanvas("canvasWeights","",200,10,1350,900);  // gives the page size
	DrawGammaCanvasSettings( canvasWeights, 0.08, 0.02, 0.035, 0.09);
	canvasWeights->SetLogx();

	TH2F * histo2DWeights;
	histo2DWeights = new TH2F("histo2DWeights","histo2DWeights",11000,0.23,70.,1000,-0.5,1.1);
	SetStyleHistoTH2ForGraphs(histo2DWeights, "#it{p}_{T} (GeV/#it{c})","#omega_{a} for BLUE",0.035,0.04, 0.035,0.04, 1.,1.);
	histo2DWeights->GetXaxis()->SetMoreLogLabels();
	histo2DWeights->GetXaxis()->SetLabelOffset(-0.01);
	histo2DWeights->Draw("copy");

	TLatex *labelWeightsEnergy = new TLatex(0.7,0.20,collisionSystem2760GeV.Data());
	SetStyleTLatex( labelWeightsEnergy, 0.85*textSizeLabelsPixel,4);
	labelWeightsEnergy->SetTextFont(43);
	
	TLatex *labelWeightsPi0;
	if(meson.CompareTo("Pi0")==0){
		labelWeightsPi0 = new TLatex(0.7,0.16,"#pi^{0} #rightarrow #gamma#gamma");
	} else 	if(meson.CompareTo("Eta")==0){
		labelWeightsPi0 = new TLatex(0.7,0.16,"#eta #rightarrow #gamma#gamma");
	}
	SetStyleTLatex( labelWeightsPi0, 0.85*textSizeLabelsPixel,4);
	labelWeightsPi0->SetTextFont(43);

	
		
	//**********************************************************************************************************************//
	//******************************************* Assuming maximal correlation *********************************************//
	//**********************************************************************************************************************//
			
	TGraph* graphWeightsALHC11h_0010[11];
	TGraph* graphWeightsALHC11h_2050[11];
	for (Int_t i = 0; i< 11; i++){
			graphWeightsALHC11h_0010[i] = NULL;
			graphWeightsALHC11h_2050[i] = NULL;
	}       

	TString fileNameOutputWeightingALHC11h_0010                                           = Form("%s/0010LHC11h_WeightingMethodA%s.dat",outputDir.Data(),meson.Data());
	TString fileNameOutputWeightingALHC11h_2050                                           = Form("%s/2050LHC11h_WeightingMethodA%s.dat",outputDir.Data(),meson.Data());

	TGraphAsymmErrors* graphCombInvYieldStat2760GeVALHC11h_0010   = NULL;
	TGraphAsymmErrors* graphCombInvYieldSys2760GeVALHC11h_0010    = NULL;
	TGraphAsymmErrors* graphCombInvYieldStat2760GeVALHC11h_2050   = NULL;
	TGraphAsymmErrors* graphCombInvYieldSys2760GeVALHC11h_2050    = NULL;
	TGraphAsymmErrors* graphCombInvYieldTot2760GeVALHC11h_0010    = NULL;
	TGraphAsymmErrors* graphCombInvYieldTot2760GeVALHC11h_2050    = NULL;
	
	if(meson.CompareTo("Pi0")==0){
		// Declaration & calculation of combined spectrum

		graphCombInvYieldTot2760GeVALHC11h_0010       = CombinePtPointsSpectraFullCorrMat( statErrorCollectionLHC11h_0010, sysErrorCollectionLHC11h_0010,
																						   xPtLimitsPi0, 23, offSetsPi0, offSetsPi0Sys,
																						   graphCombInvYieldStat2760GeVALHC11h_0010, graphCombInvYieldSys2760GeVALHC11h_0010,
																						   fileNameOutputWeightingALHC11h_0010,1 );

		graphCombInvYieldTot2760GeVALHC11h_2050       = CombinePtPointsSpectraFullCorrMat( statErrorCollectionLHC11h_2050, sysErrorCollectionLHC11h_2050,
																						   xPtLimitsPi0, 23, offSetsPi0, offSetsPi0Sys,
																						   graphCombInvYieldStat2760GeVALHC11h_2050, graphCombInvYieldSys2760GeVALHC11h_2050,
																						   fileNameOutputWeightingALHC11h_2050,1 );
		graphCombInvYieldStat2760GeVALHC11h_0010->RemovePoint(0);
		graphCombInvYieldStat2760GeVALHC11h_2050->RemovePoint(0);

		graphCombInvYieldSys2760GeVALHC11h_0010->RemovePoint(0);
		graphCombInvYieldSys2760GeVALHC11h_2050->RemovePoint(0);

		graphCombInvYieldTot2760GeVALHC11h_0010->RemovePoint(0);
		graphCombInvYieldTot2760GeVALHC11h_2050->RemovePoint(0);


	} else  if(meson.CompareTo("Eta")==0){
		// Declaration & calculation of combined spectrum

		graphCombInvYieldTot2760GeVALHC11h_0010       = CombinePtPointsSpectraFullCorrMat(  statErrorCollectionLHC11h_0010,       sysErrorCollectionLHC11h_0010,        
																							xPtLimitsEta, /*17*/13,
																							offSetsEta, offSetsEtaSys,
																							graphCombInvYieldStat2760GeVALHC11h_0010, graphCombInvYieldSys2760GeVALHC11h_0010,
																							fileNameOutputWeightingALHC11h_0010,1 );

		graphCombInvYieldTot2760GeVALHC11h_2050       = CombinePtPointsSpectraFullCorrMat(  statErrorCollectionLHC11h_2050,       sysErrorCollectionLHC11h_2050,        
																							xPtLimitsEta, /*17*/13,
																							offSetsEta, offSetsEtaSys,
																							graphCombInvYieldStat2760GeVALHC11h_2050, graphCombInvYieldSys2760GeVALHC11h_2050,
																							fileNameOutputWeightingALHC11h_2050,1 );
		graphCombInvYieldStat2760GeVALHC11h_0010->RemovePoint(0);
		graphCombInvYieldStat2760GeVALHC11h_2050->RemovePoint(0);
		graphCombInvYieldStat2760GeVALHC11h_0010->RemovePoint(0);
		graphCombInvYieldStat2760GeVALHC11h_2050->RemovePoint(0);

		graphCombInvYieldSys2760GeVALHC11h_0010->RemovePoint(0);
		graphCombInvYieldSys2760GeVALHC11h_0010->RemovePoint(0);
		graphCombInvYieldSys2760GeVALHC11h_2050->RemovePoint(0);
		graphCombInvYieldSys2760GeVALHC11h_2050->RemovePoint(0);

		graphCombInvYieldTot2760GeVALHC11h_0010->RemovePoint(0);
		graphCombInvYieldTot2760GeVALHC11h_2050->RemovePoint(0);
		graphCombInvYieldTot2760GeVALHC11h_0010->RemovePoint(0);
		graphCombInvYieldTot2760GeVALHC11h_2050->RemovePoint(0);

	}

// 	cout << "here" << endl;
// 	graphCombInvYieldTot2760GeVALHC11h_0010->Print();
// 	cout << "here" << endl;
// 	graphCombInvYieldTot2760GeVALHC11h_2050->Print();
// 
// 	cout << "here" << endl;
// 	graphCombInvYieldStat2760GeVALHC11h_0010->Print();
// 	cout << "here" << endl;
// 	graphCombInvYieldStat2760GeVALHC11h_2050->Print();
// 
// 	cout << "here" << endl;
// 	graphCombInvYieldSys2760GeVALHC11h_0010->Print();
// 	cout << "here" << endl;
// 	graphCombInvYieldSys2760GeVALHC11h_2050->Print();

	// Reading weights from output file for plotting
	ifstream fileWeightsReadALHC11h_0010;
	fileWeightsReadALHC11h_0010.open(fileNameOutputWeightingALHC11h_0010,ios_base::in);
	ifstream fileWeightsReadALHC11h_2050;
	fileWeightsReadALHC11h_2050.open(fileNameOutputWeightingALHC11h_2050,ios_base::in);
	cout << "reading" << fileNameOutputWeightingALHC11h_0010 << " and " << fileNameOutputWeightingALHC11h_2050 << endl;
	Double_t xValuesReadALHC11h_0010[50];
	Double_t weightsReadALHC11h_0010[11][50];
	Int_t availableMeasALHC11h_0010[11] = {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1};
	Double_t xValuesReadALHC11h_2050[50];
	Double_t weightsReadALHC11h_2050[11][50];
	Int_t availableMeasALHC11h_2050[11] = {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1};

	Int_t nMeasSetALHC11h                         = 2;
	Int_t nPtBinsReadALHC11h              = 0;
	while(!fileWeightsReadALHC11h_0010.eof() && nPtBinsReadALHC11h < 50){
			TString garbage = "";
			if (nPtBinsReadALHC11h == 0){
					fileWeightsReadALHC11h_0010 >> garbage ;//>> availableMeas[0] >> availableMeas[1] >> availableMeas[2] >> availableMeas[3];
					fileWeightsReadALHC11h_2050 >> garbage ;//>> availableMeas[0] >> availableMeas[1] >> availableMeas[2] >> availableMeas[3];
					for (Int_t i = 0; i < nMeasSetALHC11h; i++){
							fileWeightsReadALHC11h_0010 >> availableMeasALHC11h_0010[i] ;
							fileWeightsReadALHC11h_2050 >> availableMeasALHC11h_2050[i] ;
					}       
					cout << "read following measurements: "; 
					for (Int_t i = 0; i < 11; i++){
							cout << availableMeasALHC11h_0010[i] << "\t" ;
							cout << availableMeasALHC11h_2050[i] << "\t" ;
					}       
					cout << endl;
			} else {
					fileWeightsReadALHC11h_0010 >> xValuesReadALHC11h_0010[nPtBinsReadALHC11h-1];
					fileWeightsReadALHC11h_2050 >> xValuesReadALHC11h_2050[nPtBinsReadALHC11h-1];
					for (Int_t i = 0; i < nMeasSetALHC11h; i++){
							fileWeightsReadALHC11h_0010 >> weightsReadALHC11h_0010[availableMeasALHC11h_0010[i]][nPtBinsReadALHC11h-1] ;
							fileWeightsReadALHC11h_2050 >> weightsReadALHC11h_2050[availableMeasALHC11h_2050[i]][nPtBinsReadALHC11h-1] ;
					}       
					cout << "read: "<<  nPtBinsReadALHC11h << " xValuesReadALHC11h_0010 "<< xValuesReadALHC11h_0010[nPtBinsReadALHC11h-1] << "\t" ;
					cout << "read: "<<  nPtBinsReadALHC11h << " xValuesReadALHC11h_2050 "<< xValuesReadALHC11h_2050[nPtBinsReadALHC11h-1] << "\t" ;
					for (Int_t i = 0; i < nMeasSetALHC11h; i++){
							cout << weightsReadALHC11h_0010[availableMeasALHC11h_0010[i]][nPtBinsReadALHC11h-1] << "\t";
							cout << weightsReadALHC11h_2050[availableMeasALHC11h_2050[i]][nPtBinsReadALHC11h-1] << "\t";
					}
					cout << endl;
			}
			nPtBinsReadALHC11h++;
	}
	nPtBinsReadALHC11h = nPtBinsReadALHC11h-2 ;
	
	fileWeightsReadALHC11h_0010.close();
	fileWeightsReadALHC11h_2050.close();

	for (Int_t i = 0; i < nMeasSetALHC11h; i++){
			graphWeightsALHC11h_0010[availableMeasALHC11h_0010[i]] = new TGraph(nPtBinsReadALHC11h,xValuesReadALHC11h_0010,weightsReadALHC11h_0010[availableMeasALHC11h_0010[i]]);
			graphWeightsALHC11h_2050[availableMeasALHC11h_2050[i]] = new TGraph(nPtBinsReadALHC11h,xValuesReadALHC11h_2050,weightsReadALHC11h_2050[availableMeasALHC11h_2050[i]]);
	graphWeightsALHC11h_0010[availableMeasALHC11h_0010[i]]->Print();
	graphWeightsALHC11h_2050[availableMeasALHC11h_2050[i]]->Print();

			Int_t bin = 0;
			for (Int_t n = 0; n< nPtBinsReadALHC11h; n++){
					if (graphWeightsALHC11h_0010[availableMeasALHC11h_0010[i]]->GetY()[bin] == 0 && graphWeightsALHC11h_2050[availableMeasALHC11h_2050[i]]->GetY()[bin] == 0){
							graphWeightsALHC11h_0010[availableMeasALHC11h_0010[i]]->RemovePoint(bin);
							graphWeightsALHC11h_2050[availableMeasALHC11h_2050[i]]->RemovePoint(bin);
					} else bin++;
			}       
	}       
	

	
	//**********************************************************************************************************************//
	//******************************************* Plotting weights Method A ************************************************//
	//**********************************************************************************************************************//
// 	canvasWeights->cd();
// 	histo2DWeights->Draw("copy");
// 
// 	TLegend* legendAccWeights = GetAndSetLegend2(0.12, 0.14, 0.45, 0.14+(0.035*nMeasSetALHC11h*1.35), 32);
// 	for (Int_t i = 0; i < nMeasSetALHC11h; i++){
// 			DrawGammaSetMarkerTGraph(graphWeightsALHC11h_0010[availableMeasALHC11h_0010[i]], markerStyleDet[availableMeasALHC11h_0010[i]], markerSizeDet[availableMeasALHC11h_0010[i]]*0.5, colorDet[availableMeasALHC11h_0010[i]] , colorDet[availableMeasALHC11h_0010[i]]);
// 			graphWeightsALHC11h_0010[availableMeasALHC11h_0010[i]]->Draw("p,same,e1");
// 			legendAccWeights->AddEntry(graphWeightsALHC11h_0010[availableMeasALHC11h_0010[i]],nameMeasGlobal[availableMeasALHC11h_0010[i]],"p");
// 			
// 			DrawGammaSetMarkerTGraph(graphWeightsALHC11h_2050[availableMeasALHC11h_2050[i]], markerStyleDet[availableMeasALHC11h_2050[i]], markerSizeDet[availableMeasALHC11h_2050[i]]*0.5, colorDet[availableMeasALHC11h_2050[i]]+1 , colorDet[availableMeasALHC11h_2050[i]]+1);
// 			graphWeightsALHC11h_2050[availableMeasALHC11h_2050[i]]->Draw("p,same,e1");
// 			legendAccWeights->AddEntry(graphWeightsALHC11h_2050[availableMeasALHC11h_2050[i]],nameMeasGlobal[availableMeasALHC11h_2050[i]],"p");
// 
// 	}       
// 	legendAccWeights->Draw();
// 	labelWeightsEnergy->Draw();
// 	labelWeightsPi0->Draw();
// 
// //              DrawGammaLines(0.23, 70. , 0.8, 0.8,0.1, kGray, 3);
// 	DrawGammaLines(0.23, 70. , 0.5, 0.5,0.1, kGray, 7);
// 	DrawGammaLines(0.23, 70. , 0.4, 0.4,0.1, kGray, 1);
// 	DrawGammaLines(0.23, 70. , 0.3, 0.3,0.1, kGray, 7);
// 	DrawGammaLines(0.23, 70. , 0.2, 0.2,0.1, kGray, 3);
// 	
// 	canvasWeights->SaveAs(Form("%s/%s_WeightsA.%s",outputDir.Data(),meson.Data(),suffix.Data()));




	//**********************************************************************************************************************//
	//******************************************* Calculation of spectrum PCM - EMCal LHC11h *******************************//
	//**********************************************************************************************************************//
							
	TGraph* graphWeightsLHC11h_0010[11];
	TGraph* graphWeightsLHC11h_2050[11];
	for (Int_t i = 0; i< 11; i++){
		graphWeightsLHC11h_0010[i] = NULL;
		graphWeightsLHC11h_2050[i] = NULL;
	}	

	// Declaration & calculation of combined spectrum
	TString fileNameOutputWeightingLHC11h_0010					= Form("%s/0010LHC11h_WeightingEMCal%s.dat",outputDir.Data(),meson.Data());
	TString fileNameOutputWeightingLHC11h_2050					= Form("%s/2050LHC11h_WeightingEMCal%s.dat",outputDir.Data(),meson.Data());
	
	TGraphAsymmErrors* graphCombInvYieldStat2760GeVLHC11h_0010 = NULL;
	TGraphAsymmErrors* graphCombInvYieldSys2760GeVLHC11h_0010  = NULL;
	TGraphAsymmErrors* graphCombInvYieldTot2760GeVLHC11h_0010 = NULL;
	
	TGraphAsymmErrors* graphCombInvYieldStat2760GeVLHC11h_2050 = NULL;
	TGraphAsymmErrors* graphCombInvYieldSys2760GeVLHC11h_2050 = NULL;
	TGraphAsymmErrors* graphCombInvYieldTot2760GeVLHC11h_2050 = NULL;
		
	if(meson.CompareTo("Pi0")==0){
		cout << "******************************************* calculating the 0-10% combined spectra *******************************************\n\n\n" << endl;
		graphCombInvYieldTot2760GeVLHC11h_0010  = CombinePtPointsSpectraFullCorrMat( statErrorCollectionLHC11h_0010,	sysErrorCollectionLHC11h_0010, 	
																						xPtLimitsPi0, 23,
																						offSetsPi0, offSetsPi0Sys,
																						graphCombInvYieldStat2760GeVLHC11h_0010, graphCombInvYieldSys2760GeVLHC11h_0010,
																						fileNameOutputWeightingLHC11h_0010, 1);
		cout << "******************************************* calculating the 20-50% combined spectra *******************************************\n\n\n" << endl;
		graphCombInvYieldTot2760GeVLHC11h_2050 = CombinePtPointsSpectraFullCorrMat(  statErrorCollectionLHC11h_2050,	sysErrorCollectionLHC11h_2050, 	
																						xPtLimitsPi0, 23,
																						offSetsPi0, offSetsPi0Sys,
																						graphCombInvYieldStat2760GeVLHC11h_2050, graphCombInvYieldSys2760GeVLHC11h_2050,
																						fileNameOutputWeightingLHC11h_2050, 1);		
		graphCombInvYieldStat2760GeVLHC11h_0010->RemovePoint(0);
		graphCombInvYieldStat2760GeVLHC11h_2050->RemovePoint(0);

		graphCombInvYieldSys2760GeVLHC11h_0010->RemovePoint(0);
		graphCombInvYieldSys2760GeVLHC11h_2050->RemovePoint(0);

		graphCombInvYieldTot2760GeVLHC11h_0010->RemovePoint(0);
		graphCombInvYieldTot2760GeVLHC11h_2050->RemovePoint(0);

	} else 	if(meson.CompareTo("Eta")==0){
		cout << "******************************************* calculating the 0-10% combined spectra *******************************************\n\n\n" << endl;
		graphCombInvYieldTot2760GeVLHC11h_0010  = CombinePtPointsSpectraFullCorrMat( statErrorCollectionLHC11h_0010,	sysErrorCollectionLHC11h_0010, 	
																						xPtLimitsEta, /*17*/13,
																						offSetsEta, offSetsEtaSys,
																						graphCombInvYieldStat2760GeVLHC11h_0010, graphCombInvYieldSys2760GeVLHC11h_0010,
																						fileNameOutputWeightingLHC11h_0010,1 );
		cout << "******************************************* calculating the 20-50% combined spectra *******************************************\n\n\n" << endl;
		graphCombInvYieldTot2760GeVLHC11h_2050 = CombinePtPointsSpectraFullCorrMat(  statErrorCollectionLHC11h_2050,	sysErrorCollectionLHC11h_2050, 	
																						xPtLimitsEta, /*17*/13,
																						offSetsEta, offSetsEtaSys,
																						graphCombInvYieldStat2760GeVLHC11h_2050, graphCombInvYieldSys2760GeVLHC11h_2050,
																						fileNameOutputWeightingLHC11h_2050,1 );
		
		graphCombInvYieldStat2760GeVLHC11h_0010->RemovePoint(0);
		graphCombInvYieldStat2760GeVLHC11h_2050->RemovePoint(0);
		graphCombInvYieldStat2760GeVLHC11h_0010->RemovePoint(0);
		graphCombInvYieldStat2760GeVLHC11h_2050->RemovePoint(0);

		graphCombInvYieldSys2760GeVLHC11h_0010->RemovePoint(0);
		graphCombInvYieldSys2760GeVLHC11h_0010->RemovePoint(0);
		graphCombInvYieldSys2760GeVLHC11h_2050->RemovePoint(0);
		graphCombInvYieldSys2760GeVLHC11h_2050->RemovePoint(0);

		graphCombInvYieldTot2760GeVLHC11h_0010->RemovePoint(0);
		graphCombInvYieldTot2760GeVLHC11h_0010->RemovePoint(0);
		graphCombInvYieldTot2760GeVLHC11h_2050->RemovePoint(0);
		graphCombInvYieldTot2760GeVLHC11h_2050->RemovePoint(0);

	}

// 	cout << "here" << endl;
// 	graphCombInvYieldTot2760GeVLHC11h_0010->Print();
// 	cout << "here" << endl;
// 	graphCombInvYieldTot2760GeVLHC11h_2050->Print();
// 
// 	cout << "here" << endl;
// 	graphCombInvYieldStat2760GeVLHC11h_0010->Print();
// 	cout << "here" << endl;
// 	graphCombInvYieldStat2760GeVLHC11h_2050->Print();
// 
// 	cout << "here" << endl;
// 	graphCombInvYieldSys2760GeVLHC11h_0010->Print();
// 	cout << "here" << endl;
// 	graphCombInvYieldSys2760GeVLHC11h_2050->Print();
// 	return;

	// Reading weights from output file for plotting
	ifstream fileWeightsReadLHC11h_0010;
	fileWeightsReadLHC11h_0010.open(fileNameOutputWeightingLHC11h_0010,ios_base::in);
	ifstream fileWeightsReadLHC11h_2050;
	fileWeightsReadLHC11h_2050.open(fileNameOutputWeightingLHC11h_2050,ios_base::in);

	cout << "reading " << fileNameOutputWeightingLHC11h_0010 << " and " << fileNameOutputWeightingLHC11h_2050 << endl;
	Double_t xValuesReadLHC11h_0010[50];
	Double_t xValuesReadLHC11h_2050[50];
	Double_t weightsReadLHC11h_0010[11][50];
	Double_t weightsReadLHC11h_2050[11][50];
	Int_t availableMeasLHC11h_0010[11] = {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1};
	Int_t availableMeasLHC11h_2050[11] = {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1};
		
	Int_t nMeasSetLHC11h 			= 2;
	Int_t nPtBinsReadLHC11h 		= 0;
	while(!fileWeightsReadLHC11h_0010.eof() && nPtBinsReadLHC11h < 50){
		TString garbage = "";
		if (nPtBinsReadLHC11h == 0){
			fileWeightsReadLHC11h_0010 >> garbage;
			fileWeightsReadLHC11h_2050 >> garbage;
			for (Int_t i = 0; i < nMeasSetLHC11h; i++){
				fileWeightsReadLHC11h_0010 >> availableMeasLHC11h_0010[i];
				fileWeightsReadLHC11h_2050 >> availableMeasLHC11h_2050[i] ;
			}	
			cout << "read following measurements: "; 
			for (Int_t i = 0; i < 11; i++){
				cout << availableMeasLHC11h_0010[i] << "\t" ;
				cout << availableMeasLHC11h_2050[i] << "\t" ;
			}	
			cout << endl;
		} else {
			fileWeightsReadLHC11h_0010 >> xValuesReadLHC11h_0010[nPtBinsReadLHC11h-1];
			fileWeightsReadLHC11h_2050 >> xValuesReadLHC11h_2050[nPtBinsReadLHC11h-1];
			for (Int_t i = 0; i < nMeasSetLHC11h; i++){
				fileWeightsReadLHC11h_0010 >> weightsReadLHC11h_0010[availableMeasLHC11h_0010[i]][nPtBinsReadLHC11h-1] ;
				fileWeightsReadLHC11h_2050 >> weightsReadLHC11h_2050[availableMeasLHC11h_2050[i]][nPtBinsReadLHC11h-1] ;
			}	
			cout << "read: "<<  nPtBinsReadLHC11h << "\t"<< xValuesReadLHC11h_0010[nPtBinsReadLHC11h-1] << "\t" ;
			cout << "read: "<<  nPtBinsReadLHC11h << "\t"<< xValuesReadLHC11h_2050[nPtBinsReadLHC11h-1] << "\t" ;
			for (Int_t i = 0; i < nMeasSetLHC11h; i++){
				cout << weightsReadLHC11h_0010[availableMeasLHC11h_0010[i]][nPtBinsReadLHC11h-1] << "\t";
				cout << weightsReadLHC11h_2050[availableMeasLHC11h_2050[i]][nPtBinsReadLHC11h-1] << "\t";
			}
			cout << endl;
		}
		nPtBinsReadLHC11h++;
	}
	nPtBinsReadLHC11h = nPtBinsReadLHC11h-2 ;
	fileWeightsReadLHC11h_0010.close();
	fileWeightsReadLHC11h_2050.close();

	for (Int_t i = 0; i < nMeasSetLHC11h; i++){
		graphWeightsLHC11h_0010[availableMeasLHC11h_0010[i]] = new TGraph(nPtBinsReadLHC11h,xValuesReadLHC11h_0010,weightsReadLHC11h_0010[availableMeasLHC11h_0010[i]]);
		graphWeightsLHC11h_2050[availableMeasLHC11h_2050[i]] = new TGraph(nPtBinsReadLHC11h,xValuesReadLHC11h_2050,weightsReadLHC11h_2050[availableMeasLHC11h_2050[i]]);
		Int_t bin = 0;
		for (Int_t n = 0; n< nPtBinsReadLHC11h; n++){
			if (graphWeightsLHC11h_0010[availableMeasLHC11h_0010[i]]->GetY()[bin] == 0 && graphWeightsLHC11h_2050[availableMeasLHC11h_2050[i]]->GetY()[bin] == 0){
					graphWeightsLHC11h_0010[availableMeasLHC11h_0010[i]]->RemovePoint(bin);
					graphWeightsLHC11h_2050[availableMeasLHC11h_2050[i]]->RemovePoint(bin);
			} else bin++;

		}	
	}	

	//**********************************************************************************************************************//
	//******************************************* Plotting weights method only EMC *****************************************//
	//**********************************************************************************************************************//
	
	canvasWeights->cd();
	histo2DWeights->Draw("copy");

	TLegend* legendAccWeightsLHC11h = GetAndSetLegend2(0.12, 0.14, 0.45, 0.14+(0.06*nMeasSetLHC11h*1.35), 32);
	for (Int_t i = 0; i < nMeasSetLHC11h; i++){
		DrawGammaSetMarkerTGraph(graphWeightsLHC11h_0010[availableMeasLHC11h_0010[i]],
								markerStyleDet[availableMeasLHC11h_0010[i]], 
								markerSizeDet[availableMeasLHC11h_0010[i]]*0.5, 
								colorDet[availableMeasLHC11h_0010[i]] , 
								colorDet[availableMeasLHC11h_0010[i]]);
		graphWeightsLHC11h_0010[availableMeasLHC11h_0010[i]]->Draw("p,same,e1");
		legendAccWeightsLHC11h->AddEntry(graphWeightsLHC11h_0010[availableMeasLHC11h_0010[i]],nameMeasGlobal[availableMeasLHC11h_0010[i]],"p");
		
		DrawGammaSetMarkerTGraph(graphWeightsLHC11h_2050[availableMeasLHC11h_2050[i]],
								markerStyleDet[availableMeasLHC11h_2050[i]], 
								markerSizeDet[availableMeasLHC11h_2050[i]]*0.5, 
								colorDet[availableMeasLHC11h_2050[i]]+1, 
								colorDet[availableMeasLHC11h_2050[i]]+1);
		graphWeightsLHC11h_2050[availableMeasLHC11h_2050[i]]->Draw("p,same,e1");
		legendAccWeightsLHC11h->AddEntry(graphWeightsLHC11h_2050[availableMeasLHC11h_2050[i]],nameMeasGlobal[availableMeasLHC11h_2050[i]],"p");
	}	
	legendAccWeightsLHC11h->Draw();
	labelWeightsEnergy->Draw();
	labelWeightsPi0->Draw();

//	DrawGammaLines(0.23, 70. , 0.8, 0.8,0.1, kGray, 3);
	DrawGammaLines(0.23, 70. , 0.5, 0.5,0.1, kGray, 7);
	DrawGammaLines(0.23, 70. , 0.4, 0.4,0.1, kGray, 1);
	DrawGammaLines(0.23, 70. , 0.3, 0.3,0.1, kGray, 7);
	DrawGammaLines(0.23, 70. , 0.2, 0.2,0.1, kGray, 3);
		
	canvasWeights->SaveAs(Form("%s/%s_WeightsPCM-EMCal_LHC11h.%s",outputDir.Data(),meson.Data(),suffix.Data()));

		
	TH1D* statErrorRelCollectionLHC11h_0010[11];
	TH1D* statErrorRelCollectionLHC11h_2050[11];

	for (Int_t i = 0; i< 11; i++){
		statErrorRelCollectionLHC11h_0010[i] = NULL;
		statErrorRelCollectionLHC11h_2050[i] = NULL;
	}	
	for (Int_t i = 0; i < 11; i++){
		if (statErrorCollectionLHC11h_0010[i]) statErrorRelCollectionLHC11h_0010[i] = CalculateRelErrUpTH1D( statErrorCollectionLHC11h_0010[i], Form("relativeStatErrorLHC11h_%s_0010", nameMeasGlobal[i].Data()));
		
		if (statErrorCollectionLHC11h_2050[i]) statErrorRelCollectionLHC11h_2050[i] = CalculateRelErrUpTH1D( statErrorCollectionLHC11h_2050[i], Form("relativeStatErrorLHC11h_%s_2050", nameMeasGlobal[i].Data()));
	}
		
	TGraphAsymmErrors* sysErrorRelCollectionLHC11h_0010[11];
	TGraphAsymmErrors* sysErrorRelCollectionLHC11h_2050[11];
	for (Int_t i = 0; i< 11; i++){
		sysErrorRelCollectionLHC11h_0010[i] = NULL;
		sysErrorRelCollectionLHC11h_2050[i] = NULL;
	}	
	for (Int_t i = 0; i < 11; i++){
		if (sysErrorCollectionLHC11h_0010[i]) sysErrorRelCollectionLHC11h_0010[i] = CalculateRelErrUpAsymmGraph( sysErrorCollectionLHC11h_0010[i], Form("relativeSysErrorLHC11h_%s_0010", nameMeasGlobal[i].Data()));
		
		if (sysErrorCollectionLHC11h_2050[i]) sysErrorRelCollectionLHC11h_2050[i] = CalculateRelErrUpAsymmGraph( sysErrorCollectionLHC11h_2050[i], Form("relativeSysErrorLHC11h_%s_2050", nameMeasGlobal[i].Data()));				
	}
		


	//*********************************************************************************************************************//
	//******************************* Visualize relative errors - PCM - EMCal 2011 ****************************************//
	//*********************************************************************************************************************//
	
	TCanvas* canvasRelSysErrLHC11h = new TCanvas("canvasRelSysErrLHC11h","",200,10,1350,900);  // gives the page size
	DrawGammaCanvasSettings( canvasRelSysErrLHC11h, 0.08, 0.02, 0.035, 0.09);
	canvasRelSysErrLHC11h->SetLogx();

		TH2F * histo2DRelSysErrLHC11h;
		histo2DRelSysErrLHC11h = new TH2F("histo2DRelSysErrLHC11h","histo2DRelSysErrLHC11h",11000,0.23,70.,1000,0,80.5);
		SetStyleHistoTH2ForGraphs(histo2DRelSysErrLHC11h, "#it{p}_{T} (GeV/#it{c})","sys Err (%)",0.035,0.04, 0.035,0.04, 1.,1.);
		histo2DRelSysErrLHC11h->GetXaxis()->SetMoreLogLabels();
		histo2DRelSysErrLHC11h->GetXaxis()->SetLabelOffset(-0.01);
		histo2DRelSysErrLHC11h->Draw("copy");	
		
		TLegend* legendRelSysErrLHC11h = GetAndSetLegend2(0.62, 0.94-(0.06*nMeasSetLHC11h*1.35), 0.95, 0.94, 32);
		for (Int_t i = 0; i < nMeasSetLHC11h; i++){
			DrawGammaSetMarkerTGraph(sysErrorRelCollectionLHC11h_0010[availableMeasLHC11h_0010[i]], markerStyleDet[availableMeasLHC11h_0010[i]], 
										markerSizeDet[availableMeasLHC11h_0010[i]]*0.5, 	
										colorDet[availableMeasLHC11h_0010[i]], colorDet[availableMeasLHC11h_0010[i]]);
			sysErrorRelCollectionLHC11h_0010[availableMeasLHC11h_0010[i]]->Draw("p,same,e1");
			legendRelSysErrLHC11h->AddEntry(sysErrorRelCollectionLHC11h_0010[availableMeasLHC11h_0010[i]],nameMeasGlobal[availableMeasLHC11h_0010[i]],"p");

			DrawGammaSetMarkerTGraph(sysErrorRelCollectionLHC11h_2050[availableMeasLHC11h_2050[i]], markerStyleDet[availableMeasLHC11h_2050[i]],
										markerSizeDet[availableMeasLHC11h_2050[i]]*0.5, 
										colorDet[availableMeasLHC11h_2050[i]]+1, colorDet[availableMeasLHC11h_2050[i]]+1);	
			sysErrorRelCollectionLHC11h_2050[availableMeasLHC11h_2050[i]]->Draw("p,same,e1");
			legendRelSysErrLHC11h->AddEntry(sysErrorRelCollectionLHC11h_2050[availableMeasLHC11h_2050[i]],nameMeasGlobal[availableMeasLHC11h_2050[i]],"p");
		}
		legendRelSysErrLHC11h->Draw();


		TLatex *labelRelSysErrEnergy = new TLatex(0.7,0.89,collisionSystem2760GeV.Data());
		SetStyleTLatex( labelRelSysErrEnergy, 0.85*textSizeLabelsPixel,4);
		labelRelSysErrEnergy->SetTextFont(43);
		labelRelSysErrEnergy->Draw();
			
		TLatex *labelRelSysErrPi0;
		if(meson.CompareTo("Pi0")==0){
			labelRelSysErrPi0= new TLatex(0.7,0.8,"#pi^{0} #rightarrow #gamma#gamma");
		} else if(meson.CompareTo("Eta")==0){
			labelRelSysErrPi0= new TLatex(0.7,0.8,"#eta #rightarrow #gamma#gamma");
		}
		SetStyleTLatex( labelRelSysErrPi0, 0.85*textSizeLabelsPixel,4);
		labelRelSysErrPi0->SetTextFont(43);
		labelRelSysErrPi0->Draw();
	
	canvasRelSysErrLHC11h->SaveAs(Form("%s/%s_RelSysErrLHC11h.%s",outputDir.Data(),meson.Data(),suffix.Data()));
		
		histo2DRelSysErrLHC11h->GetYaxis()->SetRangeUser(0,30.5);
		histo2DRelSysErrLHC11h->Draw("copy");	

		for (Int_t i = 0; i < nMeasSetLHC11h; i++){
			sysErrorRelCollectionLHC11h_0010[availableMeasLHC11h_0010[i]]->Draw("p,same,e1");
			sysErrorRelCollectionLHC11h_2050[availableMeasLHC11h_2050[i]]->Draw("p,same,e1");								
			
		}	
		legendRelSysErrLHC11h->Draw();
		labelRelSysErrEnergy->Draw();
		labelRelSysErrPi0->Draw();

	canvasRelSysErrLHC11h->SaveAs(Form("%s/%s_RelSysErrZoomedLHC11h.%s",outputDir.Data(),meson.Data(), suffix.Data()));
		
	
	//*********************************************************************************************************************//
	//******************************* Visualize relative errors PCM - EMCal 2011 ******************************************//
	//*********************************************************************************************************************//
		
	TCanvas* canvasRelStatErrLHC11h = new TCanvas("canvasRelStatErrLHC11h","",200,10,1350,900);  // gives the page size
		DrawGammaCanvasSettings( canvasRelStatErrLHC11h, 0.08, 0.02, 0.035, 0.09);
		canvasRelStatErrLHC11h->SetLogx();
		
		TH2F * histo2DRelStatErrLHC11h;
		histo2DRelStatErrLHC11h = new TH2F("histo2DRelStatErrLHC11h","histo2DRelStatErrLHC11h",11000,0.23,70.,1000,0,80.5);
		SetStyleHistoTH2ForGraphs(histo2DRelStatErrLHC11h, "#it{p}_{T} (GeV/#it{c})","stat Err (%)",0.035,0.04, 0.035,0.04, 1.,1.);
		histo2DRelStatErrLHC11h->GetXaxis()->SetMoreLogLabels();
		histo2DRelStatErrLHC11h->GetXaxis()->SetLabelOffset(-0.01);
		histo2DRelStatErrLHC11h->Draw("copy");	

		TLegend* legendRelStatErrLHC11h = GetAndSetLegend2(0.14, 0.94-(0.06*nMeasSetLHC11h*1.35), 0.45, 0.94, 32);
		for (Int_t i = 0; i < nMeasSetLHC11h; i++){
			DrawGammaSetMarker(statErrorRelCollectionLHC11h_0010[availableMeasLHC11h_0010[i]], 
							markerStyleDet[availableMeasLHC11h_0010[i]], markerSizeDet[availableMeasLHC11h_0010[i]]*0.5, 
							colorDet[availableMeasLHC11h_0010[i]] , colorDet[availableMeasLHC11h_0010[i]]);
			statErrorRelCollectionLHC11h_0010[availableMeasLHC11h_0010[i]]->Draw("p,same,e1");
			legendRelStatErrLHC11h->AddEntry(statErrorRelCollectionLHC11h_0010[availableMeasLHC11h_0010[i]],nameMeasGlobal[availableMeasLHC11h_0010[i]],"p");
			
			DrawGammaSetMarker(statErrorRelCollectionLHC11h_2050[availableMeasLHC11h_2050[i]], 
							markerStyleDet[availableMeasLHC11h_2050[i]], markerSizeDet[availableMeasLHC11h_2050[i]]*0.5, 
							colorDet[availableMeasLHC11h_2050[i]]+1, colorDet[availableMeasLHC11h_2050[i]]+1);
			statErrorRelCollectionLHC11h_2050[availableMeasLHC11h_2050[i]]->Draw("p,same,e1");
			legendRelStatErrLHC11h->AddEntry(statErrorRelCollectionLHC11h_2050[availableMeasLHC11h_2050[i]],nameMeasGlobal[availableMeasLHC11h_2050[i]],"p");		
		}	
		legendRelStatErrLHC11h->Draw();

		TLatex *labelRelStatErrEnergy = new TLatex(0.7,0.89,collisionSystem2760GeV.Data());
		SetStyleTLatex( labelRelStatErrEnergy, 0.85*textSizeLabelsPixel,4);
		labelRelStatErrEnergy->SetTextFont(43);
		labelRelStatErrEnergy->Draw();
		TLatex *labelRelStatErrPi0;
		if(meson.CompareTo("Pi0")==0){
			labelRelStatErrPi0= new TLatex(0.75,0.85,"#pi^{0} #rightarrow #gamma#gamma");
		} else if(meson.CompareTo("Eta")==0){
			labelRelStatErrPi0= new TLatex(0.75,0.85,"#eta #rightarrow #gamma#gamma");
		}
		SetStyleTLatex( labelRelStatErrPi0, 0.85*textSizeLabelsPixel,4);
		labelRelStatErrPi0->SetTextFont(43);
		labelRelStatErrPi0->Draw();
			
	canvasRelStatErrLHC11h->SaveAs(Form("%s/%s_RelStatErrLHC11h.%s",outputDir.Data(),meson.Data(),suffix.Data()));

		histo2DRelStatErrLHC11h->GetYaxis()->SetRangeUser(0,30.5);
		histo2DRelStatErrLHC11h->Draw("copy");	
			for (Int_t i = 0; i < nMeasSetLHC11h; i++){
				statErrorRelCollectionLHC11h_0010[availableMeasLHC11h_0010[i]]->Draw("p,same,e1");
				statErrorRelCollectionLHC11h_2050[availableMeasLHC11h_2050[i]]->Draw("p,same,e1");
			}	
			legendRelStatErrLHC11h->Draw();

			labelRelStatErrEnergy->Draw();
			labelRelStatErrPi0->Draw();
			
	canvasRelStatErrLHC11h->SaveAs(Form("%s/%s_RelStatErrZoomedLHC11h.%s",outputDir.Data(),meson.Data(),suffix.Data()));
		
		
	//*********************************************************************************************************************//
	//**************************************** Visualize relative total errors ********************************************//
	//*********************************************************************************************************************//
	
	TGraphAsymmErrors* graphCombInvYieldRelStat2760GeVALHC11h_0010        = CalculateRelErrUpAsymmGraph( graphCombInvYieldStat2760GeVALHC11h_0010, "relativeStatErrorLHC11h_MethodA_0010");
	TGraphAsymmErrors* graphCombInvYieldRelSys2760GeVALHC11h_0010         = CalculateRelErrUpAsymmGraph( graphCombInvYieldSys2760GeVALHC11h_0010, "relativeSysErrorLHC11h_MethodA_0010");
	TGraphAsymmErrors* graphCombInvYieldRelTot2760GeVALHC11h_0010         = CalculateRelErrUpAsymmGraph( graphCombInvYieldTot2760GeVALHC11h_0010, "relativeTotalErrorLHC11h_MethodA_0010");
	
	TGraphAsymmErrors* graphCombInvYieldRelTot2760GeVLHC11h_0010 = CalculateRelErrUpAsymmGraph( graphCombInvYieldTot2760GeVLHC11h_0010, "relativeTotalError_OEMC_0010");

	TGraphAsymmErrors* graphCombInvYieldRelStat2760GeVALHC11h_2050        = CalculateRelErrUpAsymmGraph( graphCombInvYieldStat2760GeVALHC11h_2050, "relativeStatErrorLHC11h_MethodA_2050");
	TGraphAsymmErrors* graphCombInvYieldRelSys2760GeVALHC11h_2050         = CalculateRelErrUpAsymmGraph( graphCombInvYieldSys2760GeVALHC11h_2050, "relativeSysErrorLHC11h_MethodA_2050");
	TGraphAsymmErrors* graphCombInvYieldRelTot2760GeVALHC11h_2050         = CalculateRelErrUpAsymmGraph( graphCombInvYieldTot2760GeVALHC11h_2050, "relativeTotalErrorLHC11h_MethodA_2050");
 
				
// 	TGraphAsymmErrors* graphCombInvYieldRelTot2760GeVLHC11h_0010 = CalculateRelErrUpAsymmGraph( graphCombInvYieldTot2760GeVLHC11h_0010,"relativeTotalError_LHC11h_0010");
// 	TGraphAsymmErrors* graphCombInvYieldRelSys2760GeVLHC11h_0010 = CalculateRelErrUpAsymmGraph( graphCombInvYieldSys2760GeVLHC11h_0010,"relativeSysError_LHC11h_0010");
// 	TGraphAsymmErrors* graphCombInvYieldRelStat2760GeVLHC11h_0010 = CalculateRelErrUpAsymmGraph( graphCombInvYieldStat2760GeVLHC11h_0010,"relativeStatError_LHC11h_0010");
// 
// 	TGraphAsymmErrors* graphCombInvYieldRelTot2760GeVLHC11h_2050 = CalculateRelErrUpAsymmGraph( graphCombInvYieldTot2760GeVLHC11h_2050, "relativeTotalError_LHC11h_2050");
// 	TGraphAsymmErrors* graphCombInvYieldRelSys2760GeVLHC11h_2050 = CalculateRelErrUpAsymmGraph( graphCombInvYieldSys2760GeVLHC11h_2050,"relativeSysError_LHC11h_2050");
// 	TGraphAsymmErrors* graphCombInvYieldRelStat2760GeVLHC11h_2050 = CalculateRelErrUpAsymmGraph( graphCombInvYieldStat2760GeVLHC11h_2050,"relativeStatError_LHC11h_2050");
// 
// 	TCanvas* canvasRelTotErrLHC11h = new TCanvas("canvasRelTotErrLHC11h","",200,10,1350,900);  // gives the page size
// 	DrawGammaCanvasSettings( canvasRelTotErrLHC11h, 0.08, 0.02, 0.035, 0.09);
// 	canvasRelTotErrLHC11h->SetLogx();
// 	
// 		TH2F * histo2DRelTotErrLHC11h;
// 		histo2DRelTotErrLHC11h = new TH2F("histo2DRelTotErrLHC11h","histo2DRelTotErrLHC11h",11000,0.23,70.,1000,0,80.5);
// 		SetStyleHistoTH2ForGraphs(histo2DRelTotErrLHC11h, "#it{p}_{T} (GeV/#it{c})","tot Err (%)",0.035,0.04, 0.035,0.04, 1.,1.);
// 		histo2DRelTotErrLHC11h->GetXaxis()->SetMoreLogLabels();
// 		histo2DRelTotErrLHC11h->GetXaxis()->SetLabelOffset(-0.01);
// 		histo2DRelTotErrLHC11h->Draw("copy");	
// 
// 		DrawGammaSetMarkerTGraphAsym(graphCombInvYieldRelTot2760GeVLHC11h_0010, markerStyleComb, markerSizeComb, colorComb, colorComb);
// 		graphCombInvYieldRelTot2760GeVLHC11h_0010->Draw("p,same,e1");
// 
// 		TLegend* legendRelTotErrLHC11h = GetAndSetLegend2(0.14, 0.94-(0.06*4*1.35), 0.45, 0.94, 32);
// 		legendRelTotErrLHC11h->AddEntry(graphCombInvYieldRelTot2760GeVLHC11h_0010,"PCM, EMCal","p");
// 		legendRelTotErrLHC11h->Draw();
// 
// 		TLatex *labelRelTotErrEnergy = new TLatex(0.75,0.89,collisionSystem2760GeV.Data());
// 		SetStyleTLatex( labelRelTotErrEnergy, 0.85*textSizeLabelsPixel,4);
// 		labelRelTotErrEnergy->SetTextFont(43);
// 		labelRelTotErrEnergy->Draw();
// 		TLatex *labelRelTotErrPi0;
// 		if(meson.CompareTo("Pi0")==0){
// 			labelRelTotErrPi0 = new TLatex(0.75,0.85,"#pi^{0} #rightarrow #gamma#gamma");
// 		} else if(meson.CompareTo("Eta")==0){
// 			labelRelTotErrPi0 = new TLatex(0.75,0.85,"#eta #rightarrow #gamma#gamma");
// 		}
// 		SetStyleTLatex( labelRelTotErrPi0, 0.85*textSizeLabelsPixel,4);
// 		labelRelTotErrPi0->SetTextFont(43);
// 		labelRelTotErrPi0->Draw();
// 			
// 	canvasRelTotErrLHC11h->SaveAs(Form("%s/%s_0010_RelTotErrLHC11h.%s",outputDir.Data(),meson.Data(),suffix.Data()));
// 
// 		
// 		histo2DRelTotErrLHC11h->Draw("copy");	
// 		DrawGammaSetMarkerTGraphAsym(graphCombInvYieldRelTot2760GeVLHC11h_2050, markerStyleComb, markerSizeComb, colorComb ,colorComb);
// 		graphCombInvYieldRelTot2760GeVLHC11h_2050->Draw("p,same,e1");
// 
// 		TLegend* legendRelTotErrLHC11ha = GetAndSetLegend2(0.14, 0.94-(0.06*4*1.35), 0.45, 0.94, 32);
// 		legendRelTotErrLHC11ha->AddEntry(graphCombInvYieldRelTot2760GeVLHC11h_2050,"PCM, EMCal","p");
// 		legendRelTotErrLHC11ha->Draw();
// 
// 		labelRelTotErrEnergy->Draw();
// 		labelRelTotErrPi0->Draw();
// 		
// 	canvasRelTotErrLHC11h->SaveAs(Form("%s/%s_2050_RelTotErrLHC11h.%s",outputDir.Data(),meson.Data(),suffix.Data()));
// 			
// 		histo2DRelTotErrLHC11h->GetYaxis()->SetRangeUser(0,30.5);
// 		histo2DRelTotErrLHC11h->Draw("copy");	
// 		graphCombInvYieldRelTot2760GeVLHC11h_0010->Draw("p,same,e1");
// 
// 		legendRelTotErrLHC11h->Draw();
// 		labelRelTotErrEnergy->Draw();//da qui
// 		labelRelTotErrPi0->Draw();
// 			
// // 	canvasRelTotErrLHC11h->SaveAs(Form("%s/%s_0010_RelTotErrZoomedLHC11h.%s",outputDir.Data(),meson.Data(),suffix.Data()));
// 
// 		
// 		histo2DRelTotErrLHC11h->GetYaxis()->SetRangeUser(0,30.5);
// 		histo2DRelTotErrLHC11h->Draw("copy");	
// 		graphCombInvYieldRelTot2760GeVLHC11h_2050->Draw("p,same,e1");
// 
// 		legendRelTotErrLHC11h->Draw();
// 		labelRelTotErrEnergy->Draw();
// 		labelRelTotErrPi0->Draw();
// 		
// // 	canvasRelTotErrLHC11h->SaveAs(Form("%s/%s_2050_RelTotErrZoomedLHC11h.%s",outputDir.Data(),meson.Data(),suffix.Data()));
// 		
// 		
// 		histo2DRelTotErrLHC11h->GetYaxis()->SetRangeUser(0,80.5);
// 		histo2DRelTotErrLHC11h->GetYaxis()->SetTitle("Err (%)");
// 		histo2DRelTotErrLHC11h->Draw("copy");	
// 
// 		graphCombInvYieldRelTot2760GeVLHC11h_0010->Draw("p,same,e1");
// 		DrawGammaSetMarkerTGraphAsym(graphCombInvYieldRelStat2760GeVLHC11h_0010, markerStyleComb, markerSizeComb, colorComb-6 , colorComb-6);
// 		graphCombInvYieldRelStat2760GeVLHC11h_0010->Draw("l,x0,same,e1");
// 		DrawGammaSetMarkerTGraphAsym(graphCombInvYieldRelSys2760GeVLHC11h_0010, markerStyleComb, markerSizeComb, colorComb+2, colorComb+2);
// 		graphCombInvYieldRelSys2760GeVLHC11h_0010->SetLineStyle(7);
// 		graphCombInvYieldRelSys2760GeVLHC11h_0010->Draw("l,x0,same,e1");
// 
// 		TLegend* legendRelTotErrLHC11h2 = GetAndSetLegend2(0.14, 0.94-(0.06*3*1.35), 0.45, 0.94, 32);
// 		legendRelTotErrLHC11h2->AddEntry(graphCombInvYieldRelTot2760GeVLHC11h_0010,"tot","p");
// 		legendRelTotErrLHC11h2->AddEntry(graphCombInvYieldRelStat2760GeVLHC11h_0010,"stat","l");
// 		legendRelTotErrLHC11h2->AddEntry(graphCombInvYieldRelSys2760GeVLHC11h_0010,"sys","l");
// 		legendRelTotErrLHC11h2->Draw();
// 		labelRelTotErrEnergy->Draw();
// 		labelRelTotErrPi0->Draw();
// 			
// 	canvasRelTotErrLHC11h->SaveAs(Form("%s/%s_0010_ReldecompLHC11h.%s",outputDir.Data(),meson.Data(),suffix.Data()));
// 
// 		
// 		histo2DRelTotErrLHC11h->GetYaxis()->SetRangeUser(0,80.5);
// 		histo2DRelTotErrLHC11h->GetYaxis()->SetTitle("Err (%)");
// 		histo2DRelTotErrLHC11h->Draw("copy");	
// 
// 			graphCombInvYieldRelTot2760GeVLHC11h_2050->Draw("p,same,e1");
// 			DrawGammaSetMarkerTGraphAsym(graphCombInvYieldRelStat2760GeVLHC11h_2050, markerStyleComb, markerSizeComb, colorComb-6 , colorComb-6);
// 			graphCombInvYieldRelStat2760GeVLHC11h_2050->Draw("l,x0,same,e1");
// 			DrawGammaSetMarkerTGraphAsym(graphCombInvYieldRelSys2760GeVLHC11h_2050, markerStyleComb, markerSizeComb, colorComb+2, colorComb+2);
// 			graphCombInvYieldRelSys2760GeVLHC11h_2050->SetLineStyle(7);
// 			graphCombInvYieldRelSys2760GeVLHC11h_2050->Draw("l,x0,same,e1");
// 
// 			TLegend* legendRelTotErrLHC11h2a = GetAndSetLegend2(0.14, 0.94-(0.06*3*1.35), 0.45, 0.94, 32);
// 			legendRelTotErrLHC11h2a->AddEntry(graphCombInvYieldRelTot2760GeVLHC11h_2050,"tot","p");
// 			legendRelTotErrLHC11h2a->AddEntry(graphCombInvYieldRelStat2760GeVLHC11h_2050,"stat","l");
// 			legendRelTotErrLHC11h2a->AddEntry(graphCombInvYieldRelSys2760GeVLHC11h_2050,"sys","l");
// 			legendRelTotErrLHC11h2a->Draw();
// 			labelRelTotErrEnergy->Draw();
// 			labelRelTotErrPi0->Draw();
// 			
// 		canvasRelTotErrLHC11h->SaveAs(Form("%s/%s_2050_ReldecompLHC11h.%s",outputDir.Data(),meson.Data(),suffix.Data()));
// 

		

	
	//**********************************************************************************************************************//
	//************************************* Calculating bin shifted spectra & fitting **************************************//
	//**********************************************************************************************************************//
		
	// Cloning spectra
	TGraphAsymmErrors* graphCombInvYieldTot2760GeVALHC11hUnShifted_0010 		= (TGraphAsymmErrors*)graphCombInvYieldTot2760GeVALHC11h_0010->Clone("Unshifted_0010"); 
	TGraphAsymmErrors* graphCombInvYieldStat2760GeVALHC11hUnShifted_0010 		= (TGraphAsymmErrors*)graphCombInvYieldStat2760GeVALHC11h_0010->Clone("UnshiftedStat_0010"); 
	TGraphAsymmErrors* graphCombInvYieldSys2760GeVALHC11hUnShifted_0010 		= (TGraphAsymmErrors*)graphCombInvYieldSys2760GeVALHC11h_0010->Clone("UnshiftedSys_0010"); 

	TGraphAsymmErrors* graphCombInvYieldTot2760GeVALHC11hUnShifted_2050 		= (TGraphAsymmErrors*)graphCombInvYieldTot2760GeVALHC11h_2050->Clone("Unshifted_2050"); 
	TGraphAsymmErrors* graphCombInvYieldStat2760GeVALHC11hUnShifted_2050 		= (TGraphAsymmErrors*)graphCombInvYieldStat2760GeVALHC11h_2050->Clone("UnshiftedStat_2050"); 
	TGraphAsymmErrors* graphCombInvYieldSys2760GeVALHC11hUnShifted_2050  		= (TGraphAsymmErrors*)graphCombInvYieldSys2760GeVALHC11h_2050->Clone("UnshiftedSys_2050"); 
	
	TGraphAsymmErrors* graphPCMInvYieldStatPbPb2760GeVUnShifted_0010;
	TGraphAsymmErrors* graphPCMInvYieldSysPbPb2760GeVUnShifted_0010;
	TGraphAsymmErrors* graphEMCalInvYieldStatPbPb2760GeVUnshifted_0010;
	TGraphAsymmErrors* graphEMCalInvYieldSysPbPb2760GeVUnshifted_0010;

	TGraphAsymmErrors* graphPCMInvYieldStatPbPb2760GeVUnShifted_2050;
	TGraphAsymmErrors* graphPCMInvYieldSysPbPb2760GeVUnShifted_2050;
	TGraphAsymmErrors* graphEMCalInvYieldStatPbPb2760GeVUnshifted_2050;
	TGraphAsymmErrors* graphEMCalInvYieldSysPbPb2760GeVUnshifted_2050;

	if(meson.CompareTo("Pi0")==0){
		graphPCMInvYieldStatPbPb2760GeVUnShifted_0010 		= (TGraphAsymmErrors*)graphPCMPi0InvYieldStatPbPb2760GeV_0010->Clone("UnshiftedStatPCMPi0_0010"); 
		graphPCMInvYieldSysPbPb2760GeVUnShifted_0010 		= (TGraphAsymmErrors*)graphPCMPi0InvYieldSysPbPb2760GeV_0010->Clone("UnshiftedSysPCMPi0_0010"); 

		graphEMCalInvYieldStatPbPb2760GeVUnshifted_0010 	= (TGraphAsymmErrors*)graphEMCalPi0InvYieldStatPbPb2760GeV_0010->Clone("UnshiftedStatEMCalPi0_0010"); 
		graphEMCalInvYieldSysPbPb2760GeVUnshifted_0010 	= (TGraphAsymmErrors*)graphEMCalPi0InvYieldSysPbPb2760GeV_0010->Clone("UnshiftedSysEMCalPi0_0010"); 
		
		graphPCMInvYieldStatPbPb2760GeVUnShifted_2050 		= (TGraphAsymmErrors*)graphPCMPi0InvYieldStatPbPb2760GeV_2050->Clone("UnshiftedStatPCMPi0_2050"); 
		graphPCMInvYieldSysPbPb2760GeVUnShifted_2050 		= (TGraphAsymmErrors*)graphPCMPi0InvYieldSysPbPb2760GeV_2050->Clone("UnshiftedSysPCMPi0_2050"); 

		graphEMCalInvYieldStatPbPb2760GeVUnshifted_2050 	= (TGraphAsymmErrors*)graphEMCalPi0InvYieldStatPbPb2760GeV_2050->Clone("UnshiftedStatEMCalPi0_2050"); 
		graphEMCalInvYieldSysPbPb2760GeVUnshifted_2050 	= (TGraphAsymmErrors*)graphEMCalPi0InvYieldSysPbPb2760GeV_2050->Clone("UnshiftedSysEMCalPi0_2050"); 
		
	} else if(meson.CompareTo("Eta")==0){
		graphPCMInvYieldStatPbPb2760GeVUnShifted_0010 		= (TGraphAsymmErrors*)graphPCMEtaInvYieldStatPbPb2760GeV_0010->Clone("UnshiftedStatPCMEta_0010"); 
		graphPCMInvYieldSysPbPb2760GeVUnShifted_0010 		= (TGraphAsymmErrors*)graphPCMEtaInvYieldSysPbPb2760GeV_0010->Clone("UnshiftedSysPCMEta_0010"); 

		graphEMCalInvYieldStatPbPb2760GeVUnshifted_0010 	= (TGraphAsymmErrors*)graphEMCalEtaInvYieldStatPbPb2760GeV_0010->Clone("UnshiftedStatEMCalEta_0010"); 
		graphEMCalInvYieldSysPbPb2760GeVUnshifted_0010 	= (TGraphAsymmErrors*)graphEMCalEtaInvYieldSysPbPb2760GeV_0010->Clone("UnshiftedSysEMCalEta_0010"); 		

		graphPCMInvYieldStatPbPb2760GeVUnShifted_2050 		= (TGraphAsymmErrors*)graphPCMEtaInvYieldStatPbPb2760GeV_2050->Clone("UnshiftedStatPCMEta_2050"); 
		graphPCMInvYieldSysPbPb2760GeVUnShifted_2050 		= (TGraphAsymmErrors*)graphPCMEtaInvYieldSysPbPb2760GeV_2050->Clone("UnshiftedSysPCMEta_2050"); 

		graphEMCalInvYieldStatPbPb2760GeVUnshifted_2050 	= (TGraphAsymmErrors*)graphEMCalEtaInvYieldStatPbPb2760GeV_2050->Clone("UnshiftedStatEMCalEta_2050"); 
		graphEMCalInvYieldSysPbPb2760GeVUnshifted_2050 	= (TGraphAsymmErrors*)graphEMCalEtaInvYieldSysPbPb2760GeV_2050->Clone("UnshiftedSysEMCalEta_2050"); 		
		
	}

	// Calculating binshifts
	TF1* fitBylinkinPbPb2760GeVPtLHC11h_0010;
	TF1* fitBylinkinPbPb2760GeVPtLHC11h_2050;
	if(meson.CompareTo("Pi0")==0){
		fitBylinkinPbPb2760GeVPtLHC11h_0010 = FitObject("tcm","BylinkinFitPi00010","Pi0",graphCombInvYieldTot2760GeVALHC11hUnShifted_0010,0.4,20.);
		graphCombInvYieldTot2760GeVALHC11hUnShifted_0010->Fit(fitBylinkinPbPb2760GeVPtLHC11h_0010,"QNRMEX0+","",0.4,20.);

		fitBylinkinPbPb2760GeVPtLHC11h_2050 = FitObject("tcm","BylinkinFitPi02050","Pi0",graphCombInvYieldTot2760GeVALHC11hUnShifted_2050,0.4,20.);
		graphCombInvYieldTot2760GeVALHC11hUnShifted_2050->Fit(fitBylinkinPbPb2760GeVPtLHC11h_2050,"QNRMEX0+","",0.4,20.);

		if(bWCorrection.CompareTo("X")==0 ){
			TF1* fitBylinkinPbPb2760GeVPtMultLHC11h_0010 = FitObject("tcmpt","BylinkinFitPi0","Pi0",graphCombInvYieldTot2760GeVALHC11h_0010);	
			
			graphCombInvYieldTot2760GeVALHC11h_0010			= ApplyXshift(graphCombInvYieldTot2760GeVALHC11h_0010, fitBylinkinPbPb2760GeVPtMultLHC11h_0010,"Pi0");
			
			graphCombInvYieldStat2760GeVALHC11h_0010 		= ApplyXshiftIndividualSpectra (graphCombInvYieldTot2760GeVALHC11h_0010, 
																							graphCombInvYieldStat2760GeVALHC11h_0010, 
																							fitBylinkinPbPb2760GeVPtMultLHC11h_0010,
																							0, 21,"Pi0");

			graphCombInvYieldSys2760GeVALHC11h_0010 		= ApplyXshiftIndividualSpectra (graphCombInvYieldTot2760GeVALHC11h_0010, 
																							graphCombInvYieldSys2760GeVALHC11h_0010, 
																							fitBylinkinPbPb2760GeVPtMultLHC11h_0010, 
																							0, 21,"Pi0");
			
			graphPCMPi0InvYieldStatPbPb2760GeV_0010			= ApplyXshiftIndividualSpectra( graphCombInvYieldTot2760GeVALHC11h_0010,
																							graphPCMPi0InvYieldStatPbPb2760GeV_0010,
																							fitBylinkinPbPb2760GeVPtMultLHC11h_0010, 
																							0, 18,"Pi0");
			
			graphPCMPi0InvYieldSysPbPb2760GeV_0010			= ApplyXshiftIndividualSpectra( graphCombInvYieldTot2760GeVALHC11h_0010, 
																							graphPCMPi0InvYieldSysPbPb2760GeV_0010, 
																							fitBylinkinPbPb2760GeVPtMultLHC11h_0010, 
																							0, 18,"Pi0");
			
			graphEMCalPi0InvYieldStatPbPb2760GeV_0010 		= ApplyXshiftIndividualSpectra( graphCombInvYieldTot2760GeVALHC11h_0010, 
																							graphEMCalPi0InvYieldStatPbPb2760GeV_0010, 
																							fitBylinkinPbPb2760GeVPtMultLHC11h_0010,
																							14, 7,"Pi0");	
			
			graphEMCalPi0InvYieldSysPbPb2760GeV_0010 		= ApplyXshiftIndividualSpectra( graphCombInvYieldTot2760GeVALHC11h_0010, 
																							graphEMCalPi0InvYieldSysPbPb2760GeV_0010, 
																							fitBylinkinPbPb2760GeVPtMultLHC11h_0010,
																							14, 7,"Pi0");	

			TF1* fitBylinkinPbPb2760GeVPtMultLHC11h_2050 = FitObject("tcmpt","BylinkinFitPi0","Pi0",graphCombInvYieldTot2760GeVALHC11h_2050);		
			graphCombInvYieldTot2760GeVALHC11h_2050			= ApplyXshift(graphCombInvYieldTot2760GeVALHC11h_2050, fitBylinkinPbPb2760GeVPtMultLHC11h_2050,"Pi0");
			
			graphCombInvYieldStat2760GeVALHC11h_2050 		= ApplyXshiftIndividualSpectra (graphCombInvYieldTot2760GeVALHC11h_2050, 
																							graphCombInvYieldStat2760GeVALHC11h_2050, 
																							fitBylinkinPbPb2760GeVPtMultLHC11h_2050,
																							0, 21,"Pi0");
			
			graphCombInvYieldSys2760GeVALHC11h_2050 		= ApplyXshiftIndividualSpectra (graphCombInvYieldTot2760GeVALHC11h_2050, 
																							graphCombInvYieldSys2760GeVALHC11h_2050, 
																							fitBylinkinPbPb2760GeVPtMultLHC11h_2050, 
																							0, 21,"Pi0");
			
			graphPCMPi0InvYieldStatPbPb2760GeV_2050			= ApplyXshiftIndividualSpectra( graphCombInvYieldTot2760GeVALHC11h_2050,
																							graphPCMPi0InvYieldStatPbPb2760GeV_2050,
																							fitBylinkinPbPb2760GeVPtMultLHC11h_2050, 
																							0, 18,"Pi0");
			
			graphPCMPi0InvYieldSysPbPb2760GeV_2050			= ApplyXshiftIndividualSpectra( graphCombInvYieldTot2760GeVALHC11h_2050, 
																							graphPCMPi0InvYieldSysPbPb2760GeV_2050, 
																							fitBylinkinPbPb2760GeVPtMultLHC11h_2050, 
																							0, 18,"Pi0");
			
			graphEMCalPi0InvYieldStatPbPb2760GeV_2050 		= ApplyXshiftIndividualSpectra( graphCombInvYieldTot2760GeVALHC11h_2050, 
																							graphEMCalPi0InvYieldStatPbPb2760GeV_2050, 
																							fitBylinkinPbPb2760GeVPtMultLHC11h_2050,
																							14, 7,"Pi0");	
			
			graphEMCalPi0InvYieldSysPbPb2760GeV_2050 		= ApplyXshiftIndividualSpectra( graphCombInvYieldTot2760GeVALHC11h_2050, 
																							graphEMCalPi0InvYieldSysPbPb2760GeV_2050, 
																							fitBylinkinPbPb2760GeVPtMultLHC11h_2050,
																							14, 7,"Pi0");	
						
			TCanvas* canvasDummy2 = new TCanvas("canvasDummy2","",200,10,1200,1100);  // gives the page size
			DrawGammaCanvasSettings( canvasDummy2,  0.1, 0.01, 0.015, 0.08);
			canvasDummy2->SetLogy();
			canvasDummy2->SetLogx();
			TH2F * histo2DDummy2;
			histo2DDummy2 = new TH2F("histo2DDummy2","histo2DDummy2",1000,0.23,40.,1000,1e-7,1e4);
			SetStyleHistoTH2ForGraphs(histo2DDummy2, "#it{p}_{T} (GeV/#it{c})","#it{E} #frac{d^{3}#sigma}{d#it{p}^{3}} (pb GeV^{-2} #it{c}^{3} )", 0.032,0.04, 0.04,0.04, 1,1.55);
			histo2DDummy2->DrawCopy(); 
		
			DrawGammaSetMarkerTGraphAsym(graphCombInvYieldStat2760GeVALHC11hUnShifted_0010, 20, 1.5, kRed, kRed, widthLinesBoxes, kTRUE);
			graphCombInvYieldStat2760GeVALHC11hUnShifted_0010->Draw("pEsame");
			DrawGammaSetMarkerTGraphAsym(graphCombInvYieldStat2760GeVALHC11h_0010, 24, 1.5, kBlack, kBlack, widthLinesBoxes, kTRUE);
			graphCombInvYieldStat2760GeVALHC11h_0010->Draw("pEsame");
			
			DrawGammaSetMarkerTGraphAsym(graphCombInvYieldStat2760GeVALHC11hUnShifted_2050, 20, 1.5, kRed, kRed, widthLinesBoxes, kTRUE);
			graphCombInvYieldStat2760GeVALHC11hUnShifted_2050->Draw("pEsame");

			DrawGammaSetMarkerTGraphAsym(graphCombInvYieldStat2760GeVALHC11h_2050, 24, 1.5, kBlack, kBlack, widthLinesBoxes, kTRUE);
			graphCombInvYieldStat2760GeVALHC11h_2050->Draw("pEsame");
			
			fitBylinkinPbPb2760GeVPtLHC11h_0010->SetLineColor(kBlue+2);
			fitBylinkinPbPb2760GeVPtLHC11h_0010->Draw("same");
			fitBylinkinPbPb2760GeVPtLHC11h_2050->SetLineColor(kBlue+2);
			fitBylinkinPbPb2760GeVPtLHC11h_2050->Draw("same");

			TLegend* legendXdummy = new TLegend(0.6,0.8,0.9,0.95);
			legendXdummy->SetFillColor(0);
			legendXdummy->SetLineColor(0);
			legendXdummy->SetTextFont(42);
			legendXdummy->SetTextSize(FontSize);
			legendXdummy->AddEntry(graphCombInvYieldStat2760GeVALHC11hUnShifted_0010,"combined unshifted","lp");
			legendXdummy->AddEntry(graphCombInvYieldStat2760GeVALHC11h_0010,"combined shifted","lp");
			legendXdummy->Draw();

			canvasDummy2->Update();
			canvasDummy2->Print(Form("%s/%s_ComparisonShiftedPi0_PbPb2760GeVLHC11h.%s",outputDir.Data(),meson.Data(),suffix.Data()));
			delete canvasDummy2;
		}
		
	} else if(meson.CompareTo("Eta")==0){
		fitBylinkinPbPb2760GeVPtLHC11h_0010 = FitObject("tcm","BylinkinFitEta0010","Eta",graphCombInvYieldTot2760GeVALHC11hUnShifted_0010,1.,20.);
		graphCombInvYieldTot2760GeVALHC11hUnShifted_0010->Fit(fitBylinkinPbPb2760GeVPtLHC11h_0010,"QNRMEX0+","",1.,20.);

		fitBylinkinPbPb2760GeVPtLHC11h_2050 = FitObject("tcm","BylinkinFitEta2050","Eta",graphCombInvYieldTot2760GeVALHC11hUnShifted_2050,1.,20.);
		graphCombInvYieldTot2760GeVALHC11hUnShifted_2050->Fit(fitBylinkinPbPb2760GeVPtLHC11h_2050,"QNRMEX0+","",1.,20.);

// 		cout << WriteParameterToFile(fitBylinkinPbPb2760GeVPtLHC11h_0010)<< endl << endl;
// 		cout << WriteParameterToFile(fitBylinkinPbPb2760GeVPtLHC11h_2050)<< endl << endl;
// 		return;

		if(bWCorrection.CompareTo("X")==0 ){
			TF1* fitBylinkinPbPb2760GeVPtMultLHC11h_0010 = FitObject("tcmpt","BylinkinFitEta0010","Eta",graphCombInvYieldTot2760GeVALHC11h_0010);
			
			graphCombInvYieldTot2760GeVALHC11h_0010			= ApplyXshift(graphCombInvYieldTot2760GeVALHC11h_0010, fitBylinkinPbPb2760GeVPtMultLHC11h_0010,"Eta");
			
			graphCombInvYieldStat2760GeVALHC11h_0010 		= ApplyXshiftIndividualSpectra (graphCombInvYieldTot2760GeVALHC11h_0010, 
																							graphCombInvYieldStat2760GeVALHC11h_0010, 
																							fitBylinkinPbPb2760GeVPtMultLHC11h_0010,
																							0, 10,"Eta");
			graphCombInvYieldSys2760GeVALHC11h_0010 		= ApplyXshiftIndividualSpectra (graphCombInvYieldTot2760GeVALHC11h_0010, 
																							graphCombInvYieldSys2760GeVALHC11h_0010, 
																							fitBylinkinPbPb2760GeVPtMultLHC11h_0010, 
																							0, 10,"Eta");
			graphPCMEtaInvYieldStatPbPb2760GeV_0010			= ApplyXshiftIndividualSpectra( graphCombInvYieldTot2760GeVALHC11h_0010,
																							graphPCMEtaInvYieldStatPbPb2760GeV_0010,
																							fitBylinkinPbPb2760GeVPtMultLHC11h_0010, 
																							0, 7,"Eta");
			graphPCMEtaInvYieldSysPbPb2760GeV_0010			= ApplyXshiftIndividualSpectra( graphCombInvYieldTot2760GeVALHC11h_0010, 
																							graphPCMEtaInvYieldSysPbPb2760GeV_0010, 
																							fitBylinkinPbPb2760GeVPtMultLHC11h_0010, 
																							0, 7,"Eta");
			
			graphEMCalEtaInvYieldStatPbPb2760GeV_0010 		= ApplyXshiftIndividualSpectra( graphCombInvYieldTot2760GeVALHC11h_0010, 
																							graphEMCalEtaInvYieldStatPbPb2760GeV_0010, 
																							fitBylinkinPbPb2760GeVPtMultLHC11h_0010,
																							4, 7,"Eta");	
			
			graphEMCalEtaInvYieldSysPbPb2760GeV_0010 		= ApplyXshiftIndividualSpectra( graphCombInvYieldTot2760GeVALHC11h_0010, 
																							graphEMCalEtaInvYieldSysPbPb2760GeV_0010, 
																							fitBylinkinPbPb2760GeVPtMultLHC11h_0010,
																							4, 7,"Eta");	

			TF1* fitBylinkinPbPb2760GeVPtMultLHC11h_2050 = FitObject("tcmpt","BylinkinFitEta2050","Eta",graphCombInvYieldTot2760GeVALHC11h_2050);
			
			graphCombInvYieldTot2760GeVALHC11h_2050			= ApplyXshift(graphCombInvYieldTot2760GeVALHC11h_2050, fitBylinkinPbPb2760GeVPtMultLHC11h_2050,"Eta");
			
			graphCombInvYieldStat2760GeVALHC11h_2050 		= ApplyXshiftIndividualSpectra (graphCombInvYieldTot2760GeVALHC11h_2050, 
																							graphCombInvYieldStat2760GeVALHC11h_2050, 
																							fitBylinkinPbPb2760GeVPtMultLHC11h_2050,
																							0, 10,"Eta");
			
			graphCombInvYieldSys2760GeVALHC11h_2050 		= ApplyXshiftIndividualSpectra (graphCombInvYieldTot2760GeVALHC11h_2050, 
																							graphCombInvYieldSys2760GeVALHC11h_2050, 
																							fitBylinkinPbPb2760GeVPtMultLHC11h_2050, 
																							0, 10,"Eta");
			
			graphPCMEtaInvYieldStatPbPb2760GeV_2050			= ApplyXshiftIndividualSpectra( graphCombInvYieldTot2760GeVALHC11h_2050,
																							graphPCMEtaInvYieldStatPbPb2760GeV_2050,
																							fitBylinkinPbPb2760GeVPtMultLHC11h_2050, 
																							0, 7,"Eta");
			
			graphPCMEtaInvYieldSysPbPb2760GeV_2050			= ApplyXshiftIndividualSpectra( graphCombInvYieldTot2760GeVALHC11h_2050, 
																							graphPCMEtaInvYieldSysPbPb2760GeV_2050, 
																							fitBylinkinPbPb2760GeVPtMultLHC11h_2050, 
																							0, 7,"Eta");
			
			graphEMCalEtaInvYieldStatPbPb2760GeV_2050 		= ApplyXshiftIndividualSpectra( graphCombInvYieldTot2760GeVALHC11h_2050, 
																							graphEMCalEtaInvYieldStatPbPb2760GeV_2050, 
																							fitBylinkinPbPb2760GeVPtMultLHC11h_2050,
																							4, 7,"Eta");	
			
			graphEMCalEtaInvYieldSysPbPb2760GeV_2050 		= ApplyXshiftIndividualSpectra( graphCombInvYieldTot2760GeVALHC11h_2050, 
																							graphEMCalEtaInvYieldSysPbPb2760GeV_2050, 
																							fitBylinkinPbPb2760GeVPtMultLHC11h_2050,
																							4, 7,"Eta");	
			
					
			TCanvas* canvasDummy2 = new TCanvas("canvasDummy2","",200,10,1200,1100);  // gives the page size
			DrawGammaCanvasSettings( canvasDummy2,  0.1, 0.01, 0.015, 0.08);
			canvasDummy2->SetLogy();
			canvasDummy2->SetLogx();
			TH2F * histo2DDummy2;
			histo2DDummy2 = new TH2F("histo2DDummy2","histo2DDummy2",1000,0.23,40.,1000,1e-7,1e4);
			SetStyleHistoTH2ForGraphs(histo2DDummy2, "#it{p}_{T} (GeV/#it{c})","#it{E} #frac{d^{3}#sigma}{d#it{p}^{3}} (pb GeV^{-2} #it{c}^{3} )", 0.032,0.04, 0.04,0.04, 1,1.55);
			histo2DDummy2->DrawCopy(); 
		
			DrawGammaSetMarkerTGraphAsym(graphCombInvYieldStat2760GeVALHC11hUnShifted_0010, 20, 1.5, kRed, kRed, widthLinesBoxes, kTRUE);
			graphCombInvYieldStat2760GeVALHC11hUnShifted_0010->Draw("pEsame");
			DrawGammaSetMarkerTGraphAsym(graphCombInvYieldStat2760GeVALHC11h_0010, 24, 1.5, kBlack, kBlack, widthLinesBoxes, kTRUE);
			graphCombInvYieldStat2760GeVALHC11h_0010->Draw("pEsame");
			fitBylinkinPbPb2760GeVPtLHC11h_0010->SetLineColor(kBlue+2);
			fitBylinkinPbPb2760GeVPtLHC11h_0010->Draw("same");

			DrawGammaSetMarkerTGraphAsym(graphCombInvYieldStat2760GeVALHC11hUnShifted_2050, 20, 1.5, kRed, kRed, widthLinesBoxes, kTRUE);
			graphCombInvYieldStat2760GeVALHC11hUnShifted_2050->Draw("pEsame");
			DrawGammaSetMarkerTGraphAsym(graphCombInvYieldStat2760GeVALHC11h_2050, 24, 1.5, kBlack, kBlack, widthLinesBoxes, kTRUE);
			graphCombInvYieldStat2760GeVALHC11h_2050->Draw("pEsame");	
			
			fitBylinkinPbPb2760GeVPtLHC11h_2050->SetLineColor(kBlue+2);
			fitBylinkinPbPb2760GeVPtLHC11h_2050->Draw("same");

			TLegend* legendXdummy = new TLegend(0.6,0.8,0.9,0.95);
			legendXdummy->SetFillColor(0);
			legendXdummy->SetLineColor(0);
			legendXdummy->SetTextFont(42);
			legendXdummy->SetTextSize(FontSize);
			legendXdummy->AddEntry(graphCombInvYieldStat2760GeVALHC11hUnShifted_0010,"combined unshifted","lp");
			legendXdummy->AddEntry(graphCombInvYieldStat2760GeVALHC11h_0010,"combined shifted","lp");
			legendXdummy->Draw();
			
			canvasDummy2->Update();
			canvasDummy2->Print(Form("%s/%s_ComparisonShiftedEta_PbPb2760GeVLHC11h.%s",outputDir.Data(),meson.Data(),suffix.Data()));
			delete canvasDummy2;
		}
		
	}

	
	TF1* fitTCMInvYield2760GeVLHC11h_0010;
	TF1* fitTCMInvYield2760GeVLHC11h_2050;
	if(meson.CompareTo("Pi0")==0){
		cout << "Fit to the 0-10% spectrum" << endl;
		Double_t paramTCM_0010[5] = {graphCombInvYieldTot2760GeVALHC11h_0010->GetY()[0],0.3,graphCombInvYieldTot2760GeVALHC11h_0010->GetY()[0],0.3,8};
		fitTCMInvYield2760GeVLHC11h_0010 = FitObject("tcm","fitBylinkin","Pi0",graphCombInvYieldTot2760GeVALHC11h_0010,0.4,20.,paramTCM_0010,"NRMEX0+");

		cout << "Fit to the 20-50% spectrum" << endl;
		Double_t paramTCM_2050[5] = {graphCombInvYieldTot2760GeVALHC11h_2050->GetY()[0],0.3,graphCombInvYieldTot2760GeVALHC11h_2050->GetY()[0],0.3,8};
		fitTCMInvYield2760GeVLHC11h_2050 = FitObject("tcm","fitBylinkin","Pi0",graphCombInvYieldTot2760GeVALHC11h_2050,0.4,20.,paramTCM_2050,"NRMEX0+");

	} else if(meson.CompareTo("Eta")==0){
		cout << "Fit to the 0-10% spectrum" << endl;
		Double_t paramTCM_0010[5] = {graphCombInvYieldTot2760GeVALHC11h_0010->GetY()[0],0.3,graphCombInvYieldTot2760GeVALHC11h_0010->GetY()[0],0.3,8};
		fitTCMInvYield2760GeVLHC11h_0010 = FitObject("tcm","fitBylinkin","Eta",graphCombInvYieldTot2760GeVALHC11h_0010,1.,20.,paramTCM_0010,"NRMEX0+");

		cout << "Fit to the 20-50% spectrum" << endl;
		Double_t paramTCM_2050[5] = {1.,0.3,1,0.3,8};
		fitTCMInvYield2760GeVLHC11h_2050 = FitObject("tcm","fitBylinkin","Eta",graphCombInvYieldStat2760GeVALHC11h_2050,1.,20.,paramTCM_2050,"NRMEX0+");
	}

	cout << WriteParameterToFile(fitTCMInvYield2760GeVLHC11h_0010)<< endl << endl;
	cout << WriteParameterToFile(fitTCMInvYield2760GeVLHC11h_2050)<< endl << endl;

	TGraphAsymmErrors* graphRatioCombCombFitTot2760GeVLHC11h_0010 	= (TGraphAsymmErrors*)graphCombInvYieldTot2760GeVALHC11h_0010->Clone();
	graphRatioCombCombFitTot2760GeVLHC11h_0010 						= CalculateGraphErrRatioToFit(graphRatioCombCombFitTot2760GeVLHC11h_0010, fitTCMInvYield2760GeVLHC11h_0010); 
	TGraphAsymmErrors* graphRatioCombCombFitStat2760GeVLHC11h_0010 	= (TGraphAsymmErrors*)graphCombInvYieldStat2760GeVALHC11h_0010->Clone();
	graphRatioCombCombFitStat2760GeVLHC11h_0010 						= CalculateGraphErrRatioToFit(graphRatioCombCombFitStat2760GeVLHC11h_0010, fitTCMInvYield2760GeVLHC11h_0010); 
	TGraphAsymmErrors* graphRatioCombCombFitSys2760GeVLHC11h_0010 	= (TGraphAsymmErrors*)graphCombInvYieldSys2760GeVALHC11h_0010->Clone();
	graphRatioCombCombFitSys2760GeVLHC11h_0010 						= CalculateGraphErrRatioToFit(graphRatioCombCombFitSys2760GeVLHC11h_0010, fitTCMInvYield2760GeVLHC11h_0010); 

	TGraphAsymmErrors* graphRatioCombCombFitTot2760GeVLHC11h_2050 	= (TGraphAsymmErrors*)graphCombInvYieldTot2760GeVALHC11h_2050->Clone();
	graphRatioCombCombFitTot2760GeVLHC11h_2050 						= CalculateGraphErrRatioToFit(graphRatioCombCombFitTot2760GeVLHC11h_2050, fitTCMInvYield2760GeVLHC11h_2050); 
	TGraphAsymmErrors* graphRatioCombCombFitStat2760GeVLHC11h_2050 	= (TGraphAsymmErrors*)graphCombInvYieldStat2760GeVALHC11h_2050->Clone();
	graphRatioCombCombFitStat2760GeVLHC11h_2050 						= CalculateGraphErrRatioToFit(graphRatioCombCombFitStat2760GeVLHC11h_2050, fitTCMInvYield2760GeVLHC11h_2050); 
	TGraphAsymmErrors* graphRatioCombCombFitSys2760GeVLHC11h_2050 	= (TGraphAsymmErrors*)graphCombInvYieldSys2760GeVALHC11h_2050->Clone();
	graphRatioCombCombFitSys2760GeVLHC11h_2050 						= CalculateGraphErrRatioToFit(graphRatioCombCombFitSys2760GeVLHC11h_2050, fitTCMInvYield2760GeVLHC11h_2050); 

	TGraphAsymmErrors* graphRatioPCMCombFitStat2760GeV_0010;
	TGraphAsymmErrors* graphRatioPCMCombFitSys2760GeV_0010;
	TGraphAsymmErrors* graphRatioEMCalCombFitStat2760GeV_0010;
	TGraphAsymmErrors* graphRatioEMCalCombFitSys2760GeV_0010;
	
	TGraphAsymmErrors* graphRatioPCMCombFitStat2760GeV_2050;
	TGraphAsymmErrors* graphRatioPCMCombFitSys2760GeV_2050;
	TGraphAsymmErrors* graphRatioEMCalCombFitStat2760GeV_2050;
	TGraphAsymmErrors* graphRatioEMCalCombFitSys2760GeV_2050;
	
	if(meson.CompareTo("Pi0")==0){
		
		graphRatioPCMCombFitStat2760GeV_0010		= (TGraphAsymmErrors*)graphPCMPi0InvYieldStatPbPb2760GeV_0010->Clone();
		graphRatioPCMCombFitStat2760GeV_0010						= CalculateGraphErrRatioToFit(graphRatioPCMCombFitStat2760GeV_0010, fitTCMInvYield2760GeVLHC11h_0010); 
		graphRatioPCMCombFitSys2760GeV_0010 		= (TGraphAsymmErrors*)graphPCMPi0InvYieldSysPbPb2760GeV_0010->Clone();
		graphRatioPCMCombFitSys2760GeV_0010 						= CalculateGraphErrRatioToFit(graphRatioPCMCombFitSys2760GeV_0010, fitTCMInvYield2760GeVLHC11h_0010); 
		graphRatioEMCalCombFitStat2760GeV_0010 	= (TGraphAsymmErrors*)graphEMCalPi0InvYieldStatPbPb2760GeV_0010->Clone();
		graphRatioEMCalCombFitStat2760GeV_0010 						= CalculateGraphErrRatioToFit(graphRatioEMCalCombFitStat2760GeV_0010, fitTCMInvYield2760GeVLHC11h_0010); 
		graphRatioEMCalCombFitSys2760GeV_0010 	= (TGraphAsymmErrors*)graphEMCalPi0InvYieldSysPbPb2760GeV_0010->Clone();
		graphRatioEMCalCombFitSys2760GeV_0010 						= CalculateGraphErrRatioToFit(graphRatioEMCalCombFitSys2760GeV_0010, fitTCMInvYield2760GeVLHC11h_0010); 
		
		graphRatioPCMCombFitStat2760GeV_2050		= (TGraphAsymmErrors*)graphPCMPi0InvYieldStatPbPb2760GeV_2050->Clone();
		graphRatioPCMCombFitStat2760GeV_2050						= CalculateGraphErrRatioToFit(graphRatioPCMCombFitStat2760GeV_2050, fitTCMInvYield2760GeVLHC11h_2050); 
		graphRatioPCMCombFitSys2760GeV_2050 		= (TGraphAsymmErrors*)graphPCMPi0InvYieldSysPbPb2760GeV_2050->Clone();
		graphRatioPCMCombFitSys2760GeV_2050 						= CalculateGraphErrRatioToFit(graphRatioPCMCombFitSys2760GeV_2050, fitTCMInvYield2760GeVLHC11h_2050); 
		graphRatioEMCalCombFitStat2760GeV_2050 	= (TGraphAsymmErrors*)graphEMCalPi0InvYieldStatPbPb2760GeV_2050->Clone();
		graphRatioEMCalCombFitStat2760GeV_2050 						= CalculateGraphErrRatioToFit(graphRatioEMCalCombFitStat2760GeV_2050, fitTCMInvYield2760GeVLHC11h_2050); 
		graphRatioEMCalCombFitSys2760GeV_2050 	= (TGraphAsymmErrors*)graphEMCalPi0InvYieldSysPbPb2760GeV_2050->Clone();
		graphRatioEMCalCombFitSys2760GeV_2050 						= CalculateGraphErrRatioToFit(graphRatioEMCalCombFitSys2760GeV_2050, fitTCMInvYield2760GeVLHC11h_2050); 
		
	} else if(meson.CompareTo("Eta")==0){
		
		graphRatioPCMCombFitStat2760GeV_0010		= (TGraphAsymmErrors*)graphPCMEtaInvYieldStatPbPb2760GeV_0010->Clone();
		graphRatioPCMCombFitStat2760GeV_0010						= CalculateGraphErrRatioToFit(graphRatioPCMCombFitStat2760GeV_0010, fitTCMInvYield2760GeVLHC11h_0010); 
		graphRatioPCMCombFitSys2760GeV_0010 		= (TGraphAsymmErrors*)graphPCMEtaInvYieldSysPbPb2760GeV_0010->Clone();
		graphRatioPCMCombFitSys2760GeV_0010 						= CalculateGraphErrRatioToFit(graphRatioPCMCombFitSys2760GeV_0010, fitTCMInvYield2760GeVLHC11h_0010); 
		graphRatioEMCalCombFitStat2760GeV_0010 	= (TGraphAsymmErrors*)graphEMCalEtaInvYieldStatPbPb2760GeV_0010->Clone();
		graphRatioEMCalCombFitStat2760GeV_0010 						= CalculateGraphErrRatioToFit(graphRatioEMCalCombFitStat2760GeV_0010, fitTCMInvYield2760GeVLHC11h_0010); 
		graphRatioEMCalCombFitSys2760GeV_0010 	= (TGraphAsymmErrors*)graphEMCalEtaInvYieldSysPbPb2760GeV_0010->Clone();
		graphRatioEMCalCombFitSys2760GeV_0010 						= CalculateGraphErrRatioToFit(graphRatioEMCalCombFitSys2760GeV_0010, fitTCMInvYield2760GeVLHC11h_0010); 
		
		graphRatioPCMCombFitStat2760GeV_2050		= (TGraphAsymmErrors*)graphPCMEtaInvYieldStatPbPb2760GeV_2050->Clone();
		graphRatioPCMCombFitStat2760GeV_2050						= CalculateGraphErrRatioToFit(graphRatioPCMCombFitStat2760GeV_2050, fitTCMInvYield2760GeVLHC11h_2050); 
		graphRatioPCMCombFitSys2760GeV_2050 		= (TGraphAsymmErrors*)graphPCMEtaInvYieldSysPbPb2760GeV_2050->Clone();
		graphRatioPCMCombFitSys2760GeV_2050 						= CalculateGraphErrRatioToFit(graphRatioPCMCombFitSys2760GeV_2050, fitTCMInvYield2760GeVLHC11h_2050); 
		graphRatioEMCalCombFitStat2760GeV_2050 	= (TGraphAsymmErrors*)graphEMCalEtaInvYieldStatPbPb2760GeV_2050->Clone();
		graphRatioEMCalCombFitStat2760GeV_2050 						= CalculateGraphErrRatioToFit(graphRatioEMCalCombFitStat2760GeV_2050, fitTCMInvYield2760GeVLHC11h_2050); 
		graphRatioEMCalCombFitSys2760GeV_2050 	= (TGraphAsymmErrors*)graphEMCalEtaInvYieldSysPbPb2760GeV_2050->Clone();
		graphRatioEMCalCombFitSys2760GeV_2050 						= CalculateGraphErrRatioToFit(graphRatioEMCalCombFitSys2760GeV_2050, fitTCMInvYield2760GeVLHC11h_2050); 
		
	}
		
	if(PaperPi0 && meson.CompareTo("Pi0")==0){
		
		graphRatioCombCombFitStat2760GeVLHC11h_0010->RemovePoint(0);
		graphRatioCombCombFitStat2760GeVLHC11h_0010->RemovePoint(0);
		graphRatioCombCombFitStat2760GeVLHC11h_0010->RemovePoint(0);
		
		graphRatioCombCombFitSys2760GeVLHC11h_0010->RemovePoint(0);
		graphRatioCombCombFitSys2760GeVLHC11h_0010->RemovePoint(0);
		graphRatioCombCombFitSys2760GeVLHC11h_0010->RemovePoint(0);

		graphRatioCombCombFitStat2760GeVLHC11h_2050->RemovePoint(0);
		graphRatioCombCombFitStat2760GeVLHC11h_2050->RemovePoint(0);
		graphRatioCombCombFitStat2760GeVLHC11h_2050->RemovePoint(0);

		graphRatioCombCombFitSys2760GeVLHC11h_2050->RemovePoint(0);
		graphRatioCombCombFitSys2760GeVLHC11h_2050->RemovePoint(0);
		graphRatioCombCombFitSys2760GeVLHC11h_2050->RemovePoint(0);
	}
	//**********************************************************************************************************************//
	//*********************************************     Ratio of Comb to Fit    ********************************************//
	//**********************************************************************************************************************//
	
	textSizeLabelsPixel = 48;
	TCanvas* canvasRatioToCombFitLHC11h = new TCanvas("canvasRatioToCombFitLHC11h","",200,10,1350,900);  // gives the page size
	DrawGammaCanvasSettings( canvasRatioToCombFitLHC11h, 0.12, 0.01, 0.01, 0.11);
	canvasRatioToCombFitLHC11h->SetLogx();

		Double_t textsizeLabelsPP = 0;
		Double_t textsizeFacPP= 0;
		if (canvasRatioToCombFitLHC11h->XtoPixel(canvasRatioToCombFitLHC11h->GetX2()) <canvasRatioToCombFitLHC11h->YtoPixel(canvasRatioToCombFitLHC11h->GetY1()) ){
			textsizeLabelsPP = (Double_t)textSizeLabelsPixel/canvasRatioToCombFitLHC11h->XtoPixel(canvasRatioToCombFitLHC11h->GetX2()) ;
			textsizeFacPP = (Double_t)1./canvasRatioToCombFitLHC11h->XtoPixel(canvasRatioToCombFitLHC11h->GetX2()) ;
		} else {
			textsizeLabelsPP = (Double_t)textSizeLabelsPixel/canvasRatioToCombFitLHC11h->YtoPixel(canvasRatioToCombFitLHC11h->GetY1());
			textsizeFacPP = (Double_t)1./canvasRatioToCombFitLHC11h->YtoPixel(canvasRatioToCombFitLHC11h->GetY1());
		}
		cout << textsizeLabelsPP << endl;
	
		TH2F * histo2DRatioToCombFitLHC11h;
		histo2DRatioToCombFitLHC11h = new TH2F("histo2DRatioToCombFitLHC11h","histo2DRatioToCombFitLHC11h",1000,0.23,70.,1000,0.2,4.	);
		SetStyleHistoTH2ForGraphs(histo2DRatioToCombFitLHC11h, "#it{p}_{T} (GeV/#it{c})","#frac{Data}{Comb Fit}", 0.85*textsizeLabelsPP, textsizeLabelsPP, 
								0.85*textsizeLabelsPP,textsizeLabelsPP, 0.9, 0.95, 510, 505);
		histo2DRatioToCombFitLHC11h->GetXaxis()->SetMoreLogLabels();
		histo2DRatioToCombFitLHC11h->GetXaxis()->SetLabelOffset(-0.01);
	// 	histo2DRatioToCombFitLHC11h->GetYaxis()->SetRangeUser(-10,10);
		histo2DRatioToCombFitLHC11h->GetYaxis()->SetRangeUser(0.05,2.45);
		histo2DRatioToCombFitLHC11h->Draw("copy");

		DrawGammaSetMarkerTGraphAsym(graphRatioCombCombFitSys2760GeVLHC11h_0010, markerStyleComb, markerSizeComb, colorComb , colorComb, widthLinesBoxes, kTRUE);
		graphRatioCombCombFitSys2760GeVLHC11h_0010->Draw("E2same");
		DrawGammaSetMarkerTGraphAsym(graphRatioCombCombFitStat2760GeVLHC11h_0010, markerStyleComb, markerSizeComb, colorComb , colorComb);
		graphRatioCombCombFitStat2760GeVLHC11h_0010->Draw("p,same,e1");

		DrawGammaSetMarkerTGraphAsym(graphRatioCombCombFitSys2760GeVLHC11h_2050, markerStyleComb, markerSizeComb, colorComb+1, colorComb+1, widthLinesBoxes, kTRUE);
		graphRatioCombCombFitSys2760GeVLHC11h_2050->Draw("E2same");
		DrawGammaSetMarkerTGraphAsym(graphRatioCombCombFitStat2760GeVLHC11h_2050, markerStyleComb, markerSizeComb, colorComb+1, colorComb+1);
		graphRatioCombCombFitStat2760GeVLHC11h_2050->Draw("p,same,e1");

		TLegend* legendCombToCombFit = new TLegend(0.2,0.75,0.5,0.94);
		legendCombToCombFit->SetFillColor(0);
		legendCombToCombFit->SetLineColor(0);
		legendCombToCombFit->SetTextFont(42);
		legendCombToCombFit->SetTextSize(0.04);
		legendCombToCombFit->AddEntry(graphRatioCombCombFitSys2760GeVLHC11h_0010,"0-10%","fp");
		legendCombToCombFit->AddEntry(graphRatioCombCombFitSys2760GeVLHC11h_2050,"20-50%","fp");
		legendCombToCombFit->Draw();

		DrawGammaLines(0.23, 70. , 1., 1.,0.1, kGray+2);
		DrawGammaLines(0.23, 70. , 1.1, 1.1,0.1, kGray, 7);
		DrawGammaLines(0.23, 70. , 0.9, 0.9,0.1, kGray, 7);

		TLatex *labelRatioToFitEnergy = new TLatex(0.65,0.92,collisionSystem2760GeV.Data());
		SetStyleTLatex( labelRatioToFitEnergy, 0.85*textSizeLabelsPixel,4);
		labelRatioToFitEnergy->SetTextFont(43);
		labelRatioToFitEnergy->Draw();
		TLatex *labelRatioToFitPi0;
		if(meson.CompareTo("Pi0")==0){
			labelRatioToFitPi0= new TLatex(0.73,0.87,"#pi^{0} #rightarrow #gamma#gamma");
		} else if(meson.CompareTo("Eta")==0){
			labelRatioToFitPi0= new TLatex(0.73,0.87,"#eta #rightarrow #gamma#gamma");
		}
		SetStyleTLatex( labelRatioToFitPi0, 0.85*textSizeLabelsPixel,4);
		labelRatioToFitPi0->SetTextFont(43);
		labelRatioToFitPi0->Draw();

	canvasRatioToCombFitLHC11h->SaveAs(Form("%s/%s_RatioOfCombToCombFit_PbPb2760GeVLHC11h.%s",outputDir.Data(),meson.Data(),suffix.Data()));
// 	canvasRatioToCombFitLHC11h->SaveAs(Form("%s/%s_RatioOfCombToCombFit_PbPb2760GeVLHC11h.%s",paperPlots.Data(),meson.Data(),suffix.Data()));
	
	//**********************************************************************************************************************//
	//******************************************* Ratio of Individual meas to Fit ******************************************//
	//**********************************************************************************************************************//
	
	canvasRatioToCombFitLHC11h->cd();
	histo2DRatioToCombFitLHC11h->Draw("copy");

		DrawGammaSetMarkerTGraphAsym(graphRatioPCMCombFitSys2760GeV_0010, markerStyleDet[0] ,markerSizeDet[0]*0.5, colorPCM0010, colorPCM0010, widthLinesBoxes, kTRUE);
		DrawGammaSetMarkerTGraphAsym(graphRatioPCMCombFitStat2760GeV_0010, markerStyleDet[0] ,markerSizeDet[0]*0.5, colorPCM0010, colorPCM0010);
		DrawGammaSetMarkerTGraphAsym(graphRatioEMCalCombFitSys2760GeV_0010, markerStyleDet[2] ,markerSizeDet[2]*0.5, colorEMCal0010, colorEMCal0010, widthLinesBoxes, kTRUE);
		DrawGammaSetMarkerTGraphAsym(graphRatioEMCalCombFitStat2760GeV_0010, markerStyleDet[2] ,markerSizeDet[2]*0.5, colorEMCal0010, colorEMCal0010);
		
		graphRatioPCMCombFitSys2760GeV_0010->Draw("E2same");
		graphRatioEMCalCombFitSys2760GeV_0010->Draw("E2same");
		
		graphRatioPCMCombFitStat2760GeV_0010->Draw("p,same,e");
		graphRatioEMCalCombFitStat2760GeV_0010->Draw("p,same,e");

		DrawGammaSetMarkerTGraphAsym(graphRatioPCMCombFitSys2760GeV_2050, markerStyleDet[0] ,markerSizeDet[0]*0.5, colorPCM2050, colorPCM2050, widthLinesBoxes, kTRUE);
		DrawGammaSetMarkerTGraphAsym(graphRatioPCMCombFitStat2760GeV_2050, markerStyleDet[0] ,markerSizeDet[0]*0.5, colorPCM2050, colorPCM2050);
		DrawGammaSetMarkerTGraphAsym(graphRatioEMCalCombFitSys2760GeV_2050, markerStyleDet[2] ,markerSizeDet[2]*0.5, colorEMCal2050, colorEMCal2050, widthLinesBoxes, kTRUE);
		DrawGammaSetMarkerTGraphAsym(graphRatioEMCalCombFitStat2760GeV_2050, markerStyleDet[2] ,markerSizeDet[2]*0.5, colorEMCal2050, colorEMCal2050);
		
		graphRatioPCMCombFitSys2760GeV_2050->Draw("E2same");
		graphRatioEMCalCombFitSys2760GeV_2050->Draw("E2same");
		
		graphRatioPCMCombFitStat2760GeV_2050->Draw("p,same,e");
		graphRatioEMCalCombFitStat2760GeV_2050->Draw("p,same,e");

		DrawGammaLines(0.23, 70. , 1., 1.,0.5, kGray+2);
		DrawGammaLines(0.23, 70. , 1.1, 1.1,0.5, kGray, 7);
		DrawGammaLines(0.23, 70. , 0.9, 0.9,0.5, kGray, 7);
		
		labelRatioToFitEnergy->Draw();
		labelRatioToFitPi0->Draw();
	
		// ****************************** Definition of the Legend ******************************************
		// **************** Row def ************************
		Double_t rowsLegendOnlyPi0Ratio[5] 		= {0.92,0.88,0.84,0.80,0.76};
		Double_t rowsLegendOnlyPi0RatioAbs[5] 	= {0.91,2.2,2.1,2.0,1.9};
		Double_t columnsLegendOnlyPi0Ratio[3] 	= {0.15,0.32, 0.38};
		Double_t columnsLegendOnlyPi0RatioAbs[3]= {0.15,1.04, 1.37};
		Double_t lengthBox						= 0.2/2;
		Double_t heightBox						= 0.08/2;
		// ****************** first Column **************************************************
		TLatex *textPCMOnlyRatioPi0LHC11h = new TLatex(columnsLegendOnlyPi0Ratio[0],rowsLegendOnlyPi0Ratio[1],"PCM");
		SetStyleTLatex( textPCMOnlyRatioPi0LHC11h, 0.85*textSizeLabelsPixel,4);
		textPCMOnlyRatioPi0LHC11h->SetTextFont(43);
		textPCMOnlyRatioPi0LHC11h->Draw();
		TLatex *textEMCalOnlyRatioPi0LHC11h = new TLatex(columnsLegendOnlyPi0Ratio[0],rowsLegendOnlyPi0Ratio[3],"EMCal");
		SetStyleTLatex( textEMCalOnlyRatioPi0LHC11h,  0.85*textSizeLabelsPixel,4);
		textEMCalOnlyRatioPi0LHC11h->SetTextFont(43);
		textEMCalOnlyRatioPi0LHC11h->Draw();
		
		// ****************** second Column *************************************************
		TLatex *textStatOnlyRatioPi0LHC11h = new TLatex(columnsLegendOnlyPi0Ratio[1],rowsLegendOnlyPi0Ratio[0] ,"stat");
		SetStyleTLatex( textStatOnlyRatioPi0LHC11h, 0.85*textSizeLabelsPixel,4);
		textStatOnlyRatioPi0LHC11h->SetTextFont(43);
		textStatOnlyRatioPi0LHC11h->Draw();
		TLatex *textSysOnlyRatioPi0LHC11h = new TLatex(columnsLegendOnlyPi0Ratio[2] ,rowsLegendOnlyPi0Ratio[0],"syst");
		SetStyleTLatex( textSysOnlyRatioPi0LHC11h, 0.85*textSizeLabelsPixel,4);
		textSysOnlyRatioPi0LHC11h->SetTextFont(43);
		textSysOnlyRatioPi0LHC11h->Draw();
		
		TMarker* markerPCMPi0OnlyRatioPi0LHC11h = CreateMarkerFromGraph(graphRatioPCMCombFitSys2760GeV_0010,columnsLegendOnlyPi0Ratio[1] ,rowsLegendOnlyPi0Ratio[1],1);
		markerPCMPi0OnlyRatioPi0LHC11h->DrawMarker(columnsLegendOnlyPi0RatioAbs[1] ,rowsLegendOnlyPi0RatioAbs[1]);
		TMarker* markerEMCalPi0OnlyRatioPi0LHC11h = CreateMarkerFromGraph(graphRatioEMCalCombFitSys2760GeV_0010, columnsLegendOnlyPi0Ratio[1] ,rowsLegendOnlyPi0Ratio[3],1);
		markerEMCalPi0OnlyRatioPi0LHC11h->DrawMarker(columnsLegendOnlyPi0RatioAbs[1] ,rowsLegendOnlyPi0RatioAbs[3]);

		TBox* boxPCMPi0OnlyRatioPi0 = CreateBoxFromGraph(graphRatioPCMCombFitSys2760GeV_0010, columnsLegendOnlyPi0RatioAbs[2]-0.5*lengthBox , rowsLegendOnlyPi0RatioAbs[1]- heightBox,
														columnsLegendOnlyPi0RatioAbs[2]+ 3*lengthBox, rowsLegendOnlyPi0RatioAbs[1]+ heightBox);
		boxPCMPi0OnlyRatioPi0->Draw("l");
		TBox* boxEMCalPi0OnlyRatioPi0 = CreateBoxFromGraph(graphRatioEMCalCombFitSys2760GeV_0010, columnsLegendOnlyPi0RatioAbs[2]-0.5*lengthBox , rowsLegendOnlyPi0RatioAbs[3]- heightBox,
														columnsLegendOnlyPi0RatioAbs[2]+ 3*lengthBox, rowsLegendOnlyPi0RatioAbs[3]+ heightBox);
		
		TMarker* markerPCMPi0OnlyRatioPi0LHC11h_2050 = CreateMarkerFromGraph(graphRatioPCMCombFitSys2760GeV_2050,columnsLegendOnlyPi0Ratio[1] ,rowsLegendOnlyPi0Ratio[1],1);
		markerPCMPi0OnlyRatioPi0LHC11h_2050->DrawMarker(columnsLegendOnlyPi0RatioAbs[1] ,rowsLegendOnlyPi0RatioAbs[1]);
		TMarker* markerEMCalPi0OnlyRatioPi0LHC11h_2050 = CreateMarkerFromGraph(graphRatioEMCalCombFitSys2760GeV_2050, columnsLegendOnlyPi0Ratio[1] ,rowsLegendOnlyPi0Ratio[3],1);
		markerEMCalPi0OnlyRatioPi0LHC11h_2050->DrawMarker(columnsLegendOnlyPi0RatioAbs[1] ,rowsLegendOnlyPi0RatioAbs[3]);

		TBox* boxPCMPi0OnlyRatioPi0LHC11h_2050 = CreateBoxFromGraph(graphRatioPCMCombFitSys2760GeV_2050, columnsLegendOnlyPi0RatioAbs[2]-0.5*lengthBox , rowsLegendOnlyPi0RatioAbs[1]- heightBox,
														columnsLegendOnlyPi0RatioAbs[2]+ 3*lengthBox, rowsLegendOnlyPi0RatioAbs[1]+ heightBox);
		boxPCMPi0OnlyRatioPi0LHC11h_2050->Draw("l");
		TBox* boxEMCalPi0OnlyRatioPi0LHC11h_2050 = CreateBoxFromGraph(graphRatioEMCalCombFitSys2760GeV_2050, columnsLegendOnlyPi0RatioAbs[2]-0.5*lengthBox , rowsLegendOnlyPi0RatioAbs[3]- heightBox,
														columnsLegendOnlyPi0RatioAbs[2]+ 3*lengthBox, rowsLegendOnlyPi0RatioAbs[3]+ heightBox);

		boxEMCalPi0OnlyRatioPi0LHC11h_2050->Draw("l");
	
	canvasRatioToCombFitLHC11h->SaveAs(Form("%s/%s_RatioOfIndividualMeasToCombFit_PbPb2760GeVLHC11h.%s",outputDir.Data(),meson.Data(),suffix.Data()));

	
	
	//===================================================================================================================================================//
	//                                       starting here to draw actual plots for combined spectra                                                      //
	//===================================================================================================================================================//
	
	//**********************************************************************************************************************//
	//***************************************** Plotting Combined Invariant Yields *****************************************//
	//**********************************************************************************************************************//
	
	TCanvas* canvasInvYieldSectionPi0LHC11h = new TCanvas("canvasInvYieldSectionPi0LHC11h","",200,10,1350,1350*1.15);  // gives the page size
	DrawGammaCanvasSettings( canvasInvYieldSectionPi0LHC11h, 0.16, 0.02, 0.02, 0.09);
	canvasInvYieldSectionPi0LHC11h->SetLogx();
	canvasInvYieldSectionPi0LHC11h->SetLogy();
	
		TH2F * histo2DInvYieldSectionPi0LHC11h;
		histo2DInvYieldSectionPi0LHC11h = new TH2F("histo2DInvYieldSectionPi0LHC11h","histo2DInvYieldSectionPi0LHC11h",11000,0.23,70.,1000,2e-9,1e3);
		SetStyleHistoTH2ForGraphs(histo2DInvYieldSectionPi0LHC11h, "#it{p}_{T} (GeV/#it{c})","#it{E} #frac{d^{3}#sigma}{d#it{p}^{3}} (pb GeV^{-2} #it{c}^{3} )",0.035,0.04, 0.035,0.04, 1.,1.45);
		histo2DInvYieldSectionPi0LHC11h->GetXaxis()->SetMoreLogLabels();
		histo2DInvYieldSectionPi0LHC11h->GetXaxis()->SetLabelOffset(-0.01);
		histo2DInvYieldSectionPi0LHC11h->Draw("copy");

		if(meson.CompareTo("Pi0")==0){
			histo2DInvYieldSectionPi0LHC11h = new TH2F("histo2DInvYieldSectionPi0LHC11h","histo2DInvYieldSectionPi0LHC11h",11000,0.23,30.,1000,2e-7,1e3);
			SetStyleHistoTH2ForGraphs(histo2DInvYieldSectionPi0LHC11h, "#it{p}_{T} (GeV/#it{c})","#it{E} #frac{d^{3}#sigma}{d#it{p}^{3}} (pb GeV^{-2} #it{c}^{3} )",0.035,0.04, 0.035,0.04, 1.,1.45);
			histo2DInvYieldSectionPi0LHC11h->GetXaxis()->SetMoreLogLabels();
			histo2DInvYieldSectionPi0LHC11h->GetXaxis()->SetLabelOffset(-0.01);
			histo2DInvYieldSectionPi0LHC11h->Draw("copy");
			
			DrawGammaSetMarkerTGraphAsym(graphPCMPi0InvYieldSysPbPb2760GeV_0010, markerStyleDet[0], markerSizeDet[0]*0.75, colorPCM0010, colorPCM0010, widthLinesBoxes, kTRUE);
			graphPCMPi0InvYieldSysPbPb2760GeV_0010->Draw("E2same");
			DrawGammaSetMarkerTGraphAsym(graphEMCalPi0InvYieldSysPbPb2760GeV_0010, markerStyleDet[2], markerSizeDet[2]*0.75, colorEMCal0010, colorEMCal0010, widthLinesBoxes, kTRUE);
			graphEMCalPi0InvYieldSysPbPb2760GeV_0010->Draw("E2same");
	
			DrawGammaSetMarkerTGraphAsym(graphPCMPi0InvYieldStatPbPb2760GeV_0010,markerStyleDet[0], markerSizeDet[0]*0.75, colorPCM0010, colorPCM0010);
			graphPCMPi0InvYieldStatPbPb2760GeV_0010->Draw("p,same,e1");
			DrawGammaSetMarkerTGraphAsym(graphEMCalPi0InvYieldStatPbPb2760GeV_0010, markerStyleDet[2], markerSizeDet[2]*0.75, colorEMCal0010, colorEMCal0010);
			graphEMCalPi0InvYieldStatPbPb2760GeV_0010->Draw("p,same,e1");
			
			DrawGammaSetMarkerTGraphAsym(graphPCMPi0InvYieldSysPbPb2760GeV_2050, markerStyleDet[0], markerSizeDet[0]*0.75, colorPCM2050, colorPCM2050, widthLinesBoxes, kTRUE);
			graphPCMPi0InvYieldSysPbPb2760GeV_2050->Draw("E2same");
			DrawGammaSetMarkerTGraphAsym(graphEMCalPi0InvYieldSysPbPb2760GeV_2050, markerStyleDet[2], markerSizeDet[2]*0.75, colorEMCal2050, colorEMCal2050, widthLinesBoxes, kTRUE);
			graphEMCalPi0InvYieldSysPbPb2760GeV_2050->Draw("E2same");
		
			DrawGammaSetMarkerTGraphAsym(graphPCMPi0InvYieldStatPbPb2760GeV_2050,markerStyleDet[0], markerSizeDet[0]*0.75, colorPCM2050, colorPCM2050);
			graphPCMPi0InvYieldStatPbPb2760GeV_2050->Draw("p,same,e1");
			DrawGammaSetMarkerTGraphAsym(graphEMCalPi0InvYieldStatPbPb2760GeV_2050, markerStyleDet[2], markerSizeDet[2]*0.75, colorEMCal2050, colorEMCal2050);
			graphEMCalPi0InvYieldStatPbPb2760GeV_2050->Draw("p,same,e1");

			
		} else if(meson.CompareTo("Eta")==0){
			histo2DInvYieldSectionPi0LHC11h = new TH2F("histo2DInvYieldSectionPi0LHC11h","histo2DInvYieldSectionPi0LHC11h",11000,0.8,30.,1000,2e-9,1e3);
			SetStyleHistoTH2ForGraphs(histo2DInvYieldSectionPi0LHC11h, "#it{p}_{T} (GeV/#it{c})","#it{E} #frac{d^{3}#sigma}{d#it{p}^{3}} (pb GeV^{-2} #it{c}^{3} )",0.035,0.04, 0.035,0.04, 1.,1.45);
			histo2DInvYieldSectionPi0LHC11h->GetXaxis()->SetMoreLogLabels();
			histo2DInvYieldSectionPi0LHC11h->GetXaxis()->SetLabelOffset(-0.01);
			histo2DInvYieldSectionPi0LHC11h->Draw("copy");

			DrawGammaSetMarkerTGraphAsym(graphPCMEtaInvYieldSysPbPb2760GeV_0010, markerStyleDet[0], markerSizeDet[0]*0.75, colorPCM0010, colorPCM0010, widthLinesBoxes, kTRUE);
			graphPCMEtaInvYieldSysPbPb2760GeV_0010->Draw("E2same");
			DrawGammaSetMarkerTGraphAsym(graphEMCalEtaInvYieldSysPbPb2760GeV_0010, markerStyleDet[2], markerSizeDet[2]*0.75, colorEMCal0010 , colorEMCal0010, widthLinesBoxes, kTRUE);
			graphEMCalEtaInvYieldSysPbPb2760GeV_0010->Draw("E2same");
	
			DrawGammaSetMarkerTGraphAsym(graphPCMEtaInvYieldStatPbPb2760GeV_0010,markerStyleDet[0], markerSizeDet[0]*0.75, colorPCM0010, colorPCM0010);
			graphPCMEtaInvYieldStatPbPb2760GeV_0010->Draw("p,same,e1");
			DrawGammaSetMarkerTGraphAsym(graphEMCalEtaInvYieldStatPbPb2760GeV_0010, markerStyleDet[2], markerSizeDet[2]*0.75, colorEMCal0010 , colorEMCal0010);
			graphEMCalEtaInvYieldStatPbPb2760GeV_0010->Draw("p,same,e1");
			
			DrawGammaSetMarkerTGraphAsym(graphPCMEtaInvYieldSysPbPb2760GeV_2050, markerStyleDet[0], markerSizeDet[0]*0.75, colorPCM2050, colorPCM2050, widthLinesBoxes, kTRUE);
			graphPCMEtaInvYieldSysPbPb2760GeV_2050->Draw("E2same");
			DrawGammaSetMarkerTGraphAsym(graphEMCalEtaInvYieldSysPbPb2760GeV_2050, markerStyleDet[2], markerSizeDet[2]*0.75, colorEMCal2050 , colorEMCal2050, widthLinesBoxes, kTRUE);
			graphEMCalEtaInvYieldSysPbPb2760GeV_2050->Draw("E2same");
		
			DrawGammaSetMarkerTGraphAsym(graphPCMEtaInvYieldStatPbPb2760GeV_2050,markerStyleDet[0], markerSizeDet[0]*0.75, colorPCM2050, colorPCM2050);
			graphPCMEtaInvYieldStatPbPb2760GeV_2050->Draw("p,same,e1");
			DrawGammaSetMarkerTGraphAsym(graphEMCalEtaInvYieldStatPbPb2760GeV_2050, markerStyleDet[2], markerSizeDet[2]*0.75, colorEMCal2050 , colorEMCal2050);
			graphEMCalEtaInvYieldStatPbPb2760GeV_2050->Draw("p,same,e1");

		}
		
		TLegend* legendInvYieldSectionPi0LHC11h_separate = new TLegend(0.2,0.15,0.5,0.34);
		legendInvYieldSectionPi0LHC11h_separate->SetFillColor(0);
		legendInvYieldSectionPi0LHC11h_separate->SetLineColor(0);
		legendInvYieldSectionPi0LHC11h_separate->SetTextFont(42);
		legendInvYieldSectionPi0LHC11h_separate->SetTextSize(FontSize);
		if(meson.CompareTo("Pi0")==0){
			legendInvYieldSectionPi0LHC11h_separate->AddEntry(graphPCMPi0InvYieldSysPbPb2760GeV_0010,"PCM - 0-10%","fp");
			legendInvYieldSectionPi0LHC11h_separate->AddEntry(graphEMCalPi0InvYieldStatPbPb2760GeV_0010,"EMCal - 0-10%","fp");
			legendInvYieldSectionPi0LHC11h_separate->AddEntry(graphPCMPi0InvYieldSysPbPb2760GeV_2050,"PCM - 20-50%","fp");
			legendInvYieldSectionPi0LHC11h_separate->AddEntry(graphEMCalPi0InvYieldStatPbPb2760GeV_2050,"EMCal - 20-50%","fp");
// 			legendInvYieldSectionPi0LHC11h_separate->AddEntry(fitTCMInvYield2760GeVLHC11h_0010, "Bylinkin Fit","l");
			
		} else if(meson.CompareTo("Eta")==0){

			legendInvYieldSectionPi0LHC11h_separate->AddEntry(graphPCMEtaInvYieldSysPbPb2760GeV_0010,"PCM - 0-10%","fp");
			legendInvYieldSectionPi0LHC11h_separate->AddEntry(graphEMCalEtaInvYieldStatPbPb2760GeV_0010,"EMCal - 0-10%","fp");
			legendInvYieldSectionPi0LHC11h_separate->AddEntry(graphPCMEtaInvYieldSysPbPb2760GeV_2050,"PCM - 20-50%","fp");
			legendInvYieldSectionPi0LHC11h_separate->AddEntry(graphEMCalEtaInvYieldStatPbPb2760GeV_2050,"EMCal - 20-50%","fp");
// 			legendInvYieldSectionPi0LHC11h_separate->AddEntry(fitTCMInvYield2760GeVLHC11h_2050, "Bylinkin Fit","l");
			
		}
		
		legendInvYieldSectionPi0LHC11h_separate->Draw();
		labelEnergyInvYieldSectionPi0LHC11h->Draw();
		labelDetSysInvYieldSectionPi0LHC11h->Draw();

	canvasInvYieldSectionPi0LHC11h->SaveAs(Form("%s/%s_YieldsCompAllSystemsLHC11h.%s",outputDir.Data(),meson.Data(),suffix.Data()));
// 	canvasInvYieldSectionPi0LHC11h->SaveAs(Form("%s/%s_YieldsCompAllSystemsLHC11h.%s",paperPlots.Data(),meson.Data(),suffix.Data()));
	
	canvasInvYieldSectionPi0LHC11h->cd();
// 	histo2DInvYieldSectionPi0LHC11h->Draw("copy");

		if(meson.CompareTo("Pi0")==0){
			histo2DInvYieldSectionPi0LHC11h = new TH2F("histo2DInvYieldSectionPi0LHC11h","histo2DInvYieldSectionPi0LHC11h",11000,0.23,30,1000,1e-8,1e3); //invece di 2e4
			SetStyleHistoTH2ForGraphs(histo2DInvYieldSectionPi0LHC11h, "#it{p}_{T} (GeV/#it{c})","#frac{1}{2#pi #it{N}_{ev}} #frac{d^{2}#it{N_{#pi^{0}}}}{#it{p}_{T}d#it{p}_{T}d#it{y}} (GeV/#it{c})^{-2}",0.035,0.04, 0.035,0.04, 1.,1.5);
			
		} else if(meson.CompareTo("Eta")==0){
			histo2DInvYieldSectionPi0LHC11h = new TH2F("histo2DInvYieldSectionPi0LHC11h","histo2DInvYieldSectionPi0LHC11h",11000,0.23,30.,1000,1e-8,1e2);
			SetStyleHistoTH2ForGraphs(histo2DInvYieldSectionPi0LHC11h, "#it{p}_{T} (GeV/#it{c})","#frac{1}{2#pi #it{N}_{ev}} #frac{d^{2}#it{N_{#eta}}}{#it{p}_{T}d#it{p}_{T}d#it{y}} (GeV/#it{c})^{-2}",0.035,0.04, 0.035,0.04, 1.,1.6);			
		}
		histo2DInvYieldSectionPi0LHC11h->GetXaxis()->SetMoreLogLabels();
		histo2DInvYieldSectionPi0LHC11h->GetXaxis()->SetLabelOffset(-0.01);
		histo2DInvYieldSectionPi0LHC11h->Draw("copy");
		histo2DInvYieldSectionPi0LHC11h->GetXaxis()->SetRangeUser(minPtRange,maxPtRange);
		
		if(PaperPi0 && meson.CompareTo("Pi0")==0){
			graphCombInvYieldSys2760GeVALHC11h_0010->RemovePoint(0);
			graphCombInvYieldStat2760GeVALHC11h_0010->RemovePoint(0);

			graphCombInvYieldSys2760GeVALHC11h_0010->RemovePoint(0);
			graphCombInvYieldStat2760GeVALHC11h_0010->RemovePoint(0);

			graphCombInvYieldSys2760GeVALHC11h_0010->RemovePoint(0);
			graphCombInvYieldStat2760GeVALHC11h_0010->RemovePoint(0);

			graphCombInvYieldSys2760GeVALHC11h_2050->RemovePoint(0);
			graphCombInvYieldStat2760GeVALHC11h_2050->RemovePoint(0);

			graphCombInvYieldSys2760GeVALHC11h_2050->RemovePoint(0);
			graphCombInvYieldStat2760GeVALHC11h_2050->RemovePoint(0);
			
			graphCombInvYieldSys2760GeVALHC11h_2050->RemovePoint(0);
			graphCombInvYieldStat2760GeVALHC11h_2050->RemovePoint(0);

		}
		
		DrawGammaSetMarkerTGraphAsym(graphCombInvYieldSys2760GeVALHC11h_0010, markerStyleComb, markerSizeComb, colorComb , colorComb, widthLinesBoxes, kTRUE);
		DrawGammaSetMarkerTGraphAsym(graphCombInvYieldStat2760GeVALHC11h_0010, markerStyleComb, markerSizeComb, colorComb , colorComb);
// 			graphCombInvYieldSys2760GeVALHC11h_0010->Draw("E2same");
// 			graphCombInvYieldStat2760GeVALHC11h_0010->Draw("p,same,e1");	
		
		DrawGammaSetMarkerTGraphAsym(graphCombInvYieldSys2760GeVALHC11h_2050, markerStyleComb, markerSizeComb, colorComb+1 , colorComb+1, widthLinesBoxes, kTRUE);
		DrawGammaSetMarkerTGraphAsym(graphCombInvYieldStat2760GeVALHC11h_2050, markerStyleComb, markerSizeComb, colorComb+1, colorComb+1);
// 			graphCombInvYieldSys2760GeVALHC11h_2050->Draw("E2same");
// 			graphCombInvYieldStat2760GeVALHC11h_2050->Draw("p,same,e1");	

			
		TGraphAsymmErrors *graphCombInvYieldSys2760GeVALHC11hColor_0010 = (TGraphAsymmErrors*)graphCombInvYieldSys2760GeVALHC11h_0010->Clone("graphCombInvYieldSys2760GeVALHC11hColor_0010");	
		TGraphAsymmErrors *graphCombInvYieldStat2760GeVALHC11hColor_0010 = (TGraphAsymmErrors*)graphCombInvYieldStat2760GeVALHC11h_0010->Clone("graphCombInvYieldStat2760GeVALHC11hColor_0010");

		TGraphAsymmErrors *graphCombInvYieldSys2760GeVALHC11hColor_2050 = (TGraphAsymmErrors*)graphCombInvYieldSys2760GeVALHC11h_2050->Clone("graphCombInvYieldSys2760GeVALHC11hColor_2050");	
		TGraphAsymmErrors *graphCombInvYieldStat2760GeVALHC11hColor_2050 = (TGraphAsymmErrors*)graphCombInvYieldStat2760GeVALHC11h_2050->Clone("graphCombInvYieldStat2760GeVALHC11hColor_2050");
		
		TGraphAsymmErrors *graphCombInvYieldSys2760GeVALHC11hScaled_0010 = (TGraphAsymmErrors*)graphCombInvYieldSys2760GeVALHC11h_0010->Clone("graphCombInvYieldSys2760GeVALHC11hScaled_0010");
		graphCombInvYieldSys2760GeVALHC11hScaled_0010 = ScaleGraph(graphCombInvYieldSys2760GeVALHC11hScaled_0010, 4); 
		TGraphAsymmErrors *graphCombInvYieldStat2760GeVALHC11hScaled_0010 = (TGraphAsymmErrors*)graphCombInvYieldStat2760GeVALHC11h_0010->Clone("graphCombInvYieldStat2760GeVALHC11hScaled_0010");
		graphCombInvYieldStat2760GeVALHC11hScaled_0010 = ScaleGraph(graphCombInvYieldStat2760GeVALHC11hScaled_0010,4);

		DrawGammaSetMarkerTGraphAsym(graphCombInvYieldSys2760GeVALHC11hScaled_0010, markerStyleComb, markerSizeComb, colorCombo0010 , colorCombo0010, 2, kTRUE);
		DrawGammaSetMarkerTGraphAsym(graphCombInvYieldStat2760GeVALHC11hScaled_0010, markerStyleComb, markerSizeComb, colorCombo0010, colorCombo0010);
		graphCombInvYieldSys2760GeVALHC11hScaled_0010->Draw("E2same");
		if(noXerrorBars) ProduceGraphAsymmWithoutXErrors(graphCombInvYieldStat2760GeVALHC11hScaled_0010);
		graphCombInvYieldStat2760GeVALHC11hScaled_0010->Draw("p,same,e1");	
	
	
		DrawGammaSetMarkerTGraphAsym(graphCombInvYieldSys2760GeVALHC11hColor_2050, markerStyleComb, markerSizeComb, colorCombo2050 , colorCombo2050, 2, kTRUE);
		DrawGammaSetMarkerTGraphAsym(graphCombInvYieldStat2760GeVALHC11hColor_2050, markerStyleComb, markerSizeComb, colorCombo2050, colorCombo2050);
		graphCombInvYieldSys2760GeVALHC11hColor_2050->Draw("E2same");
		if(noXerrorBars) ProduceGraphAsymmWithoutXErrors(graphCombInvYieldStat2760GeVALHC11hColor_2050);
		graphCombInvYieldStat2760GeVALHC11hColor_2050->Draw("p,same,e1");	
			
		TLegend* legendInvYieldSectionPi0LHC11h_onlyPbPb = new TLegend(0.2,0.13,0.53,0.22);
		legendInvYieldSectionPi0LHC11h_onlyPbPb->SetMargin(0.17);
		legendInvYieldSectionPi0LHC11h_onlyPbPb->SetFillColor(0);
		legendInvYieldSectionPi0LHC11h_onlyPbPb->SetLineColor(0);
		legendInvYieldSectionPi0LHC11h_onlyPbPb->SetTextFont(42);
		legendInvYieldSectionPi0LHC11h_onlyPbPb->SetTextSize(FontSize);
// 		legendInvYieldSectionPi0LHC11h_onlyPbPb->AddEntry(graphCombInvYieldSys2760GeVALHC11hScaled_0010,Form("%s %s x 2^{2}",cent0010.Data(),collisionSystem2760GeV.Data()),"fp");
// 		legendInvYieldSectionPi0LHC11h_onlyPbPb->AddEntry(graphCombInvYieldSys2760GeVALHC11hColor_2050,Form("%s %s",cent2050.Data(),collisionSystem2760GeV.Data()),"fp");
		legendInvYieldSectionPi0LHC11h_onlyPbPb->AddEntry(graphCombInvYieldSys2760GeVALHC11hScaled_0010,Form("  %s",cent0010.Data()),"fp");
		legendInvYieldSectionPi0LHC11h_onlyPbPb->AddEntry(graphCombInvYieldSys2760GeVALHC11hColor_2050,Form("%s",cent2050.Data()),"fp");

		legendInvYieldSectionPi0LHC11h_onlyPbPb->Draw();
		labelEnergyInvYieldSectionPi0LHC11h->Draw();
		labelDetSysInvYieldSectionPi0LHC11h->Draw();
		labelFactorLower->Draw();
// 		labelPreliminary->Draw();

	canvasInvYieldSectionPi0LHC11h->SaveAs(Form("%s/%s_YieldCombinedLHC11h_DataOnly.%s",outputDir.Data(),meson.Data(),suffix.Data()));
// 	canvasInvYieldSectionPi0LHC11h->SaveAs(Form("%s/%s_YieldCombinedLHC11h_DataOnly.%s",paperPlots.Data(),meson.Data(),suffix.Data()));
	
	canvasInvYieldSectionPi0LHC11h->cd();
	histo2DInvYieldSectionPi0LHC11h->Draw("copy");
	
		graphCombInvYieldSys2760GeVALHC11hScaled_0010->Draw("E2same");
		if(noXerrorBars) ProduceGraphAsymmWithoutXErrors(graphCombInvYieldStat2760GeVALHC11hScaled_0010);
		graphCombInvYieldStat2760GeVALHC11hScaled_0010->Draw("p,same,e1");	
	
		graphCombInvYieldSys2760GeVALHC11hColor_2050->Draw("E2same");
		if(noXerrorBars) ProduceGraphAsymmWithoutXErrors(graphCombInvYieldStat2760GeVALHC11hColor_2050);
		graphCombInvYieldStat2760GeVALHC11hColor_2050->Draw("p,same,e1");	
	
		TF1* dummy = FitObject("tcm","fitBylinkin");
		dummy->SetLineColor(kBlack);
		dummy->SetLineWidth(2);
		fitTCMInvYield2760GeVLHC11h_0010->SetLineColor(kRed+2);
		fitTCMInvYield2760GeVLHC11h_2050->SetLineColor(kBlue+2);
		fitTCMInvYield2760GeVLHC11h_0010->SetParameter(0,fitTCMInvYield2760GeVLHC11h_0010->GetParameter(0)*4);
		fitTCMInvYield2760GeVLHC11h_0010->SetParameter(2,fitTCMInvYield2760GeVLHC11h_0010->GetParameter(2)*4);
		
		fitTCMInvYield2760GeVLHC11h_0010->Draw("same");
		fitTCMInvYield2760GeVLHC11h_2050->Draw("same");
		
		TLegend* legendInvYieldSectionPi0LHC11h_onlyPbPbwithFit = new TLegend(0.17,0.14,0.5,0.26);
		legendInvYieldSectionPi0LHC11h_onlyPbPbwithFit->SetFillColor(0);
		legendInvYieldSectionPi0LHC11h_onlyPbPbwithFit->SetLineColor(0);
		legendInvYieldSectionPi0LHC11h_onlyPbPbwithFit->SetTextFont(42);
		legendInvYieldSectionPi0LHC11h_onlyPbPbwithFit->SetTextSize(FontSize);

// 		legendInvYieldSectionPi0LHC11h_onlyPbPbwithFit->AddEntry(graphCombInvYieldSys2760GeVALHC11hScaled_0010,Form("%s %s x 2^{2}",cent0010.Data(),collisionSystem2760GeV.Data()),"fp");
		legendInvYieldSectionPi0LHC11h_onlyPbPbwithFit->AddEntry(graphCombInvYieldSys2760GeVALHC11hScaled_0010,Form("  %s",cent0010.Data()),"fp");
// 		legendInvYieldSectionPi0LHC11h_onlyPbPbwithFit->AddEntry(graphCombInvYieldSys2760GeVALHC11hColor_2050,Form("%s %s",cent2050.Data(),collisionSystem2760GeV.Data()),"fp");			
		legendInvYieldSectionPi0LHC11h_onlyPbPbwithFit->AddEntry(graphCombInvYieldSys2760GeVALHC11hColor_2050,Form("%s",cent2050.Data()),"fp");	
// 		legendInvYieldSectionPi0LHC11h_onlyPbPbwithFit->AddEntry(fitTCMInvYield2760GeVLHC11h_0010, "Bylinkin Fit","l");
// 		legendInvYieldSectionPi0LHC11h_onlyPbPbwithFit->AddEntry(fitTCMInvYield2760GeVLHC11h_2050, "Bylinkin Fit","l");
		legendInvYieldSectionPi0LHC11h_onlyPbPbwithFit->AddEntry(dummy, "#it{A}_{e} exp(-#it{E}_{T, kin}/#it{T}_{e}) + #it{A}/#(){1 + #frac{#it{p}_{T}^{2}}{#it{T}^{2}#upoint n}}^{-n}","l");
		legendInvYieldSectionPi0LHC11h_onlyPbPbwithFit->Draw();
		
		labelFactorLower->Draw();
		labelEnergyInvYieldSectionPi0LHC11hnoPrelim->Draw();
		labelDetSysInvYieldSectionPi0LHC11hnoPrelim->Draw();
		
	canvasInvYieldSectionPi0LHC11h->Update();
	canvasInvYieldSectionPi0LHC11h->SaveAs(Form("%s/%s_YieldCombinedLHC11h_DataWithFit.%s",outputDir.Data(),meson.Data(),suffix.Data()));
// 	canvasInvYieldSectionPi0LHC11h->SaveAs(Form("%s/%s_YieldCombinedLHC11h_DataWithFit.%s",paperPlots.Data(),meson.Data(),suffix.Data()));

	
	canvasInvYieldSectionPi0LHC11h->cd();
	histo2DInvYieldSectionPi0LHC11h->DrawCopy();

		DrawGammaSetMarkerTGraphAsym(TheoryCracowLowPt_0010, 0, 0, colorCracow0010,colorCracow0010, 5, kTRUE, colorCracow0010);
		TheoryCracowLowPt_0010->Draw("l,same");

		DrawGammaSetMarkerTGraphAsym(TheoryCracowLowPt_2050, 0, 0, colorCracow2050,colorCracow2050, 5, kTRUE,colorCracow2050);
		TheoryCracowLowPt_2050->Draw("l,same");

		DrawGammaSetMarker(histoEPOSRebin_0010,1,2,colorEPOS0010,colorEPOS0010);
		DrawGammaSetMarker(histoEPOSRebin_2050,1,2,colorEPOS2050,colorEPOS2050);
		histoEPOSRebin_0010->SetLineWidth(2);
		histoEPOSRebin_2050->SetLineWidth(2);
		
		histoEPOSRebin_0010->Scale(4);
		histoEPOSRebin_0010->GetXaxis()->SetRangeUser(0.,13.);
		histoEPOSRebin_2050->GetXaxis()->SetRangeUser(0.,13.);
		histoEPOSRebin_0010->Draw("same,c,histo");
		histoEPOSRebin_2050->Draw("same,c,histo");
		
		graphCombInvYieldSys2760GeVALHC11hScaled_0010->Draw("E2same");
		if(noXerrorBars) ProduceGraphAsymmWithoutXErrors(graphCombInvYieldStat2760GeVALHC11hScaled_0010);
		graphCombInvYieldStat2760GeVALHC11hScaled_0010->Draw("p,same,e1");	
	
		graphCombInvYieldSys2760GeVALHC11hColor_2050->Draw("E2same");
		if(noXerrorBars) ProduceGraphAsymmWithoutXErrors(graphCombInvYieldStat2760GeVALHC11hColor_2050);
		graphCombInvYieldStat2760GeVALHC11hColor_2050->Draw("p,same,e1");	
		
// 		TLegend* legtheory = new TLegend(0.17,0.13,0.5,0.24);
		TLegend* legtheory = new TLegend(0.18,0.13,0.51,0.24);
		legtheory->SetFillColor(0);
		legtheory->SetLineColor(0);
		legtheory->SetTextFont(42);
		legtheory->SetTextSize(FontSize);
		legtheory->SetHeader("PRC 90, 014906 (2014)");
		legtheory->AddEntry(TheoryCracowLowPt_0010,"NEQ SHM 0-10%", "l");
		legtheory->AddEntry(TheoryCracowLowPt_2050,"NEQ SHM 20-50%", "l");
// 		legtheory->AddEntry(TheoryLowPtH_0010, "  Cent = 10%", "l");
// 		legtheory->AddEntry(TheoryLowPtMean_0010, "NEQ SHM 0-10%", "l");
// 		legtheory->AddEntry(TheoryLowPtL_0010, "  Cent = 0%", "l");
// 		legtheory->AddEntry(TheoryLowPtH_2050, "  Cent = 50%", "l");
// 		legtheory->AddEntry(TheoryLowPtMean_2050,"NEQ SHM 20-50%", "l");
// 		legtheory->AddEntry(TheoryLowPtL_2050,"  Cent = 20%", "l");
		legtheory->Draw("same");
		
		TLegend* legtheory2 = new TLegend(0.18,0.24,0.51,0.35);
		legtheory2->SetFillColor(0);
		legtheory2->SetLineColor(0);
		legtheory2->SetTextFont(42);
		legtheory2->SetTextSize(FontSize);
		legtheory2->SetHeader("PRC 89, 064903 (2014)");
		legtheory2->AddEntry(histoEPOSRebin_0010,"EPOS3 0-10%", "l");
		legtheory2->AddEntry(histoEPOSRebin_2050,"EPOS2 20-50%", "l");
		legtheory2->Draw("same");
		
		TLegend* legendInvYieldSectionPi0LHC11h_onlyPbPbWithModels = new TLegend(0.6,0.74,0.95,0.82);
// 		TLegend* legendInvYieldSectionPi0LHC11h_onlyPbPbWithModels = new TLegend(0.17,0.31,0.5,0.37);
		legendInvYieldSectionPi0LHC11h_onlyPbPbWithModels->SetMargin(0.17);
		legendInvYieldSectionPi0LHC11h_onlyPbPbWithModels->SetFillColor(0);
		legendInvYieldSectionPi0LHC11h_onlyPbPbWithModels->SetLineColor(0);
		legendInvYieldSectionPi0LHC11h_onlyPbPbWithModels->SetTextFont(42);
		legendInvYieldSectionPi0LHC11h_onlyPbPbWithModels->SetTextSize(FontSize);
		legendInvYieldSectionPi0LHC11h_onlyPbPbWithModels->AddEntry(graphCombInvYieldSys2760GeVALHC11hScaled_0010,Form("  %s",cent0010.Data()),"fp");
		legendInvYieldSectionPi0LHC11h_onlyPbPbWithModels->AddEntry(graphCombInvYieldSys2760GeVALHC11hColor_2050,Form("%s",cent2050.Data()),"fp");
		legendInvYieldSectionPi0LHC11h_onlyPbPbWithModels->Draw();

// 		labelPreliminary->Draw();
		labelFactorLower->Draw();
		labelEnergyInvYieldSectionPi0LHC11h->Draw();
		labelDetSysInvYieldSectionPi0LHC11h->Draw();

	canvasInvYieldSectionPi0LHC11h->Update();
	canvasInvYieldSectionPi0LHC11h->SaveAs(Form("%s/%s_YieldCombinedLHC11h_DataWithModels.%s",outputDir.Data(),meson.Data(),suffix.Data()));
	canvasInvYieldSectionPi0LHC11h->SaveAs(Form("%s/%s_YieldCombinedLHC11h_DataWithModels.%s",paperPlots.Data(),meson.Data(),suffix.Data()));

	
	//*************************************************************************************************************
	//***************************** Paper plot inv yields and ratios ***********************************************
	//*************************************************************************************************************

// 	Double_t arrayBoundariesX1_XSec[2];
// 	Double_t arrayBoundariesY1_XSec[6];
// 	Double_t relativeMarginsXXSec[3];
// 	Double_t relativeMarginsYXSec[3];
// 	textSizeLabelsPixel = 90;
// 	ReturnCorrectValuesForCanvasScaling(2500,4000, 1, 5,0.13, 0.025, 0.003,0.05,arrayBoundariesX1_XSec,arrayBoundariesY1_XSec,relativeMarginsXXSec,relativeMarginsYXSec);
// 	
// 	TCanvas* canvasInvYieldSectionRatiosCentTogether = new TCanvas("canvasInvYieldSectionRatiosCentTogether","",0,0,2500,4000);  // gives the page size
// 	DrawGammaCanvasSettings( canvasInvYieldSectionRatiosCentTogether,  0.13, 0.02, 0.03, 0.06);
// 
// 		TPad* padInvSectionSpecCentTogether = new TPad("padInvSectionSpecCentTogether", "", arrayBoundariesX1_XSec[0], arrayBoundariesY1_XSec[3], arrayBoundariesX1_XSec[1], arrayBoundariesY1_XSec[0],-1, -1, -2);
// 		DrawGammaPadSettings( padInvSectionSpecCentTogether, relativeMarginsXXSec[0], relativeMarginsXXSec[2], relativeMarginsYXSec[0], relativeMarginsYXSec[1]);
// 		padInvSectionSpecCentTogether->Draw();
// 		Double_t marginXSec = relativeMarginsXXSec[0]*2500;
// 		Double_t textsizeLabelsXSecUp = 0;
// 		Double_t textsizeFacXSecUp = 0;
// 		if (padInvSectionSpecCentTogether->XtoPixel(padInvSectionSpecCentTogether->GetX2()) < padInvSectionSpecCentTogether->YtoPixel(padInvSectionSpecCentTogether->GetY1())){
// 			textsizeLabelsXSecUp = (Double_t)textSizeLabelsPixel/padInvSectionSpecCentTogether->XtoPixel(padInvSectionSpecCentTogether->GetX2()) ;
// 			textsizeFacXSecUp = (Double_t)1./padInvSectionSpecCentTogether->XtoPixel(padInvSectionSpecCentTogether->GetX2()) ;
// 		} else {
// 			textsizeLabelsXSecUp = (Double_t)textSizeLabelsPixel/padInvSectionSpecCentTogether->YtoPixel(padInvSectionSpecCentTogether->GetY1());
// 			textsizeFacXSecUp = (Double_t)1./padInvSectionSpecCentTogether->YtoPixel(padInvSectionSpecCentTogether->GetY1());
// 		}
// 			
// 		TPad* padInvSectionLowPtRatioCentTogether = new TPad("padInvSectionLowPtRatioCentTogether", "", arrayBoundariesX1_XSec[0], arrayBoundariesY1_XSec[4], arrayBoundariesX1_XSec[1], arrayBoundariesY1_XSec[3],-1, -1, -2);
// 		DrawGammaPadSettings( padInvSectionLowPtRatioCentTogether, relativeMarginsXXSec[0], relativeMarginsXXSec[2], relativeMarginsYXSec[1], relativeMarginsYXSec[1]);
// 		padInvSectionLowPtRatioCentTogether->Draw();
// 		Double_t textsizeLabelsXSecMiddle = 0;
// 		Double_t textsizeFacXSecMiddle = 0;
// 		if (padInvSectionLowPtRatioCentTogether->XtoPixel(padInvSectionLowPtRatioCentTogether->GetX2()) < padInvSectionLowPtRatioCentTogether->YtoPixel(padInvSectionLowPtRatioCentTogether->GetY1())){
// 			textsizeLabelsXSecMiddle = (Double_t)textSizeLabelsPixel/padInvSectionLowPtRatioCentTogether->XtoPixel(padInvSectionLowPtRatioCentTogether->GetX2()) ;
// 			textsizeFacXSecMiddle = (Double_t)1./padInvSectionLowPtRatioCentTogether->XtoPixel(padInvSectionLowPtRatioCentTogether->GetX2()) ;
// 		} else {
// 			textsizeLabelsXSecMiddle = (Double_t)textSizeLabelsPixel/padInvSectionLowPtRatioCentTogether->YtoPixel(padInvSectionLowPtRatioCentTogether->GetY1());
// 			textsizeFacXSecMiddle = (Double_t)1./padInvSectionLowPtRatioCentTogether->YtoPixel(padInvSectionLowPtRatioCentTogether->GetY1());
// 		}
// 	
// 		TPad* padInvSectionEPOSRatioCentTogether = new TPad("padInvSectionEPOSRatioCentTogether", "", arrayBoundariesX1_XSec[0], arrayBoundariesY1_XSec[5], arrayBoundariesX1_XSec[1], arrayBoundariesY1_XSec[4],-1, -1, -2);
// 		DrawGammaPadSettings( padInvSectionEPOSRatioCentTogether, relativeMarginsXXSec[0], relativeMarginsXXSec[2], relativeMarginsYXSec[1], relativeMarginsYXSec[2]);
// 		padInvSectionEPOSRatioCentTogether->Draw();
// 		Double_t textsizeLabelsXSecDown = 0;
// 		Double_t textsizeFacXSecDown = 0;
// 		if (padInvSectionEPOSRatioCentTogether->XtoPixel(padInvSectionEPOSRatioCentTogether->GetX2()) < padInvSectionEPOSRatioCentTogether->YtoPixel(padInvSectionEPOSRatioCentTogether->GetY1())){
// 			textsizeLabelsXSecDown = (Double_t)textSizeLabelsPixel/padInvSectionEPOSRatioCentTogether->XtoPixel(padInvSectionEPOSRatioCentTogether->GetX2()) ;
// 			textsizeFacXSecDown = (Double_t)1./padInvSectionEPOSRatioCentTogether->XtoPixel(padInvSectionEPOSRatioCentTogether->GetX2()) ;
// 		} else {
// 			textsizeLabelsXSecDown = (Double_t)textSizeLabelsPixel/padInvSectionEPOSRatioCentTogether->YtoPixel(padInvSectionEPOSRatioCentTogether->GetY1());
// 			textsizeFacXSecDown = (Double_t)1./padInvSectionEPOSRatioCentTogether->YtoPixel(padInvSectionEPOSRatioCentTogether->GetY1());
// 		}
// 	
// 		
// 		padInvSectionSpecCentTogether->cd();
// 		padInvSectionSpecCentTogether->SetLogy(1);
// 		padInvSectionSpecCentTogether->SetLogx(1);
// 		TH2F *histo2DRatioToModelsLHC11hCentTogether = new TH2F("histo2DRatioToModelsLHC11hCentTogether","histo2DRatioToModelsLHC11hCentTogether",11000,0.8,30.,1000,5e-8,2e3);
// 		SetStyleHistoTH2ForGraphs(histo2DRatioToModelsLHC11hCentTogether, "#it{p}_{T} (GeV/#it{c})","#frac{1}{2#pi #it{N}_{ev}} #frac{d^{2}#it{N}}{#it{p}_{T}d#it{p}_{T}d#it{y}} (GeV/#it{c})^{-2}",0.035,0.04, 0.035,0.04, 1.,1.45);
// 		histo2DRatioToModelsLHC11hCentTogether->GetXaxis()->SetMoreLogLabels();
// 		histo2DRatioToModelsLHC11hCentTogether->GetXaxis()->SetLabelOffset(-0.01);
// 		histo2DRatioToModelsLHC11hCentTogether->Draw("copy");
// 
// 		TGraphAsymmErrors *TheoryCracowLowPtforRatio_0010 = (TGraphAsymmErrors*)TheoryCracowLowPt_0010->Clone("TheoryCracowLowPtforRatio_0010");
// // 		DrawGammaSetMarkerTGraphAsym(TheoryCracowLowPtforRatio_0010, 0, 0, colorCracowRatio, colorCracowRatio, widthLinesBoxes, kTRUE, colorCracowRatio);
// 		DrawGammaSetMarkerTGraphAsym(TheoryCracowLowPtforRatio_0010, 0, 0, colorCracowRatio, colorCracowRatio, 5, kTRUE, colorCracowRatio);
// 		TheoryCracowLowPtforRatio_0010->Draw("l,same");
// 		histoEPOSRebin_0010->SetLineColor(colorEPOSRatio);
// 		histoEPOSRebin_0010->Draw("same,c,histo");
// 
// 		graphCombInvYieldSys2760GeVALHC11hScaled_0010->Draw("E2same");
// 				if(noXerrorBars) ProduceGraphAsymmWithoutXErrors(graphCombInvYieldStat2760GeVALHC11hScaled_0010);
// 		graphCombInvYieldStat2760GeVALHC11hScaled_0010->Draw("p,same,e1");	
// 
// 		fitTCMInvYield2760GeVLHC11h_0010->SetLineStyle(4);
// 		fitTCMInvYield2760GeVLHC11h_0010->Draw("same");		
// 		
// 		TLatex *labelEnergyRatioToModelsLHC11h = new TLatex(0.5,0.89,collisionSystemPbPb0010.Data());
// 		SetStyleTLatex( labelEnergyRatioToModelsLHC11h, 0.035,4);
// 		labelEnergyRatioToModelsLHC11h->Draw();
// // 		labelPreliminary->Draw();
// 		
// 		TLatex *labelDetSysRatioToModelsLHC11h;
// 		if(meson.CompareTo("Pi0")==0){
// 			labelDetSysRatioToModelsLHC11h= new TLatex(0.5,0.86,"#pi^{0} #rightarrow #gamma#gamma");
// 		} else if(meson.CompareTo("Eta")==0){
// 			labelDetSysRatioToModelsLHC11h= new TLatex(0.5,0.86,"#eta #rightarrow #gamma#gamma");
// 		}
// 		SetStyleTLatex( labelDetSysRatioToModelsLHC11h, 0.035,4);
// 		labelDetSysRatioToModelsLHC11h->Draw();
// 		
// 		TLegend* legendXsectionPaper = GetAndSetLegend2(0.17, 0.3-4*0.06, 0.5, 0.3, 0.85* textSizeLabelsPixel);
// 		legendXsectionPaper->SetNColumns(1);
// 		legendXsectionPaper->SetMargin(0.2);
// 		if(meson.CompareTo("Pi0")==0) legendXsectionPaper->AddEntry(graphCombInvYieldSys2760GeVALHC11hScaled_0010,"#pi^{0} ALICE","pf");
// 		else if(meson.CompareTo("Eta")==0) legendXsectionPaper->AddEntry(graphCombInvYieldSys2760GeVALHC11hScaled_0010,"#eta ALICE","pf");
// 		legendXsectionPaper->AddEntry(TheoryCracowLowPtforRatio_0010,"NEQ SHM","l");
// 		legendXsectionPaper->AddEntry(histoEPOSRebin_0010,"EPOS 3","l");
// 		legendXsectionPaper->AddEntry(fitTCMInvYield2760GeVLHC11h_0010,"#it{A}_{e} exp(-#it{E}_{T, kin}/#it{T}_{e}) + #it{A}/#(){1 + #frac{#it{p}_{T}^{2}}{#it{T}^{2}#upoint n}}^{-n}","l");
// 		legendXsectionPaper->Draw();		
// 
// 		TGraphAsymmErrors *TheoryCracowLowPtforRatio_2050 = (TGraphAsymmErrors*)TheoryCracowLowPt_2050->Clone("TheoryCracowLowPtforRatio_2050");
// // 		DrawGammaSetMarkerTGraphAsym(TheoryCracowLowPtforRatio_2050, 0, 0, colorCracowRatio,colorCracowRatio, widthLinesBoxes, kTRUE,colorCracowRatio);
// 		DrawGammaSetMarkerTGraphAsym(TheoryCracowLowPtforRatio_2050, 0, 0, colorCracowRatio,colorCracowRatio, 5, kTRUE,colorCracowRatio);
// 		TheoryCracowLowPtforRatio_2050->Draw("l,same");
// 		histoEPOSRebin_2050->SetLineColor(colorEPOSRatio);
// 		histoEPOSRebin_2050->Draw("same,c,histo");
// 
// 		graphCombInvYieldSys2760GeVALHC11hColor_2050->Draw("E2same");
// 				if(noXerrorBars) ProduceGraphAsymmWithoutXErrors(graphCombInvYieldStat2760GeVALHC11hColor_2050);
// 		graphCombInvYieldStat2760GeVALHC11hColor_2050->Draw("p,same,e1");	
// 
// 		fitTCMInvYield2760GeVLHC11h_2050->SetLineStyle(4);
// 		fitTCMInvYield2760GeVLHC11h_2050->Draw("same");		
// // 		labelPreliminary->Draw();
// 		TLatex *labelEnergyRatioToModelsLHC11h2 = new TLatex(0.5,0.89,collisionSystemPbPb2050.Data());
// 		SetStyleTLatex( labelEnergyRatioToModelsLHC11h2, 0.035,4);
// 		labelEnergyRatioToModelsLHC11h2->Draw();
// 		labelDetSysRatioToModelsLHC11h->Draw();
// 		
// 		TLegend* legendXsectionPaper2 = GetAndSetLegend2(0.17, 0.3-4*0.06, 0.5, 0.3, 0.85* textSizeLabelsPixel);
// 		legendXsectionPaper2->SetNColumns(1);
// 		legendXsectionPaper2->SetMargin(0.2);
// 		if(meson.CompareTo("Pi0")==0) legendXsectionPaper2->AddEntry(graphCombInvYieldSys2760GeVALHC11hColor_2050,"#pi^{0} ALICE","pf");
// 		else if(meson.CompareTo("Eta")==0) legendXsectionPaper2->AddEntry(graphCombInvYieldSys2760GeVALHC11hColor_2050,"#eta ALICE","pf");
// 		legendXsectionPaper2->AddEntry(TheoryCracowLowPtforRatio_2050,"NEQ SHM","l");
// 		legendXsectionPaper2->AddEntry(histoEPOSRebin_2050,"EPOS 2","l");
// 		legendXsectionPaper2->AddEntry(fitTCMInvYield2760GeVLHC11h_2050,"#it{A}_{e} exp(-#it{E}_{T, kin}/#it{T}_{e}) + #it{A}/#(){1 + #frac{#it{p}_{T}^{2}}{#it{T}^{2}#upoint n}}^{-n}","l");
// 		legendXsectionPaper2->Draw();		
// 		legendXsectionPaper2->Draw();		
// 
// 		
// 	padInvSectionLowPtRatioCentTogether->cd();
// 	padInvSectionLowPtRatioCentTogether->SetLogx(1);
// 		TH2F * ratio2DLowPt;
// 		if(meson.CompareTo("Pi0")==0) ratio2DLowPt=  new TH2F("ratio2DLowPt","ratio2DLowPt",1000,0.8,30.,1000,0.2,2.45);
// 		if(meson.CompareTo("Eta")==0) ratio2DLowPt=  new TH2F("ratio2DLowPt","ratio2DLowPt",1000,0.8,30.,1000,0.2,2.45);
// 		SetStyleHistoTH2ForGraphs(ratio2DLowPt, "#it{p}_{T} (GeV/#it{c})","#frac{NEQ SHM, Data}{fit}", 0.85*textsizeLabelsXSecMiddle, textsizeLabelsXSecMiddle, 
// 								  0.85*textsizeLabelsXSecMiddle,textsizeLabelsXSecMiddle, 1,0.2/(textsizeFacXSecMiddle*marginXSec), 510, 505);
// 		ratio2DLowPt->GetYaxis()->SetMoreLogLabels(kTRUE);
// 		ratio2DLowPt->GetYaxis()->SetNdivisions(505);
// 		ratio2DLowPt->GetYaxis()->SetNoExponent(kTRUE);
// 		ratio2DLowPt->GetXaxis()->SetMoreLogLabels(kTRUE);
// 		ratio2DLowPt->GetXaxis()->SetNoExponent(kTRUE);
// 		ratio2DLowPt->GetXaxis()->SetLabelFont(42);
// 		ratio2DLowPt->GetYaxis()->SetLabelFont(42);
// 		ratio2DLowPt->GetYaxis()->SetLabelOffset(+0.01);
// 		ratio2DLowPt->GetXaxis()->SetTickLength(0.07);
// 		ratio2DLowPt->DrawCopy();
// 
// 		TGraphAsymmErrors* graphRatioCombLowPt2760GeVLHC11h_0010 = (TGraphAsymmErrors*)TheoryCracowLowPt_0010->Clone("graphRatioCombLowPt2760GeVLHC11h_0010");	
// 		graphRatioCombLowPt2760GeVLHC11h_0010 = CalculateGraphErrRatioToFit(graphRatioCombLowPt2760GeVLHC11h_0010, fitTCMInvYield2760GeVLHC11h_0010); 
// 
// // 		DrawGammaSetMarkerTGraphAsym(graphRatioCombLowPt2760GeVLHC11h_0010, 0, 0, colorCracowRatio, colorCracowRatio, widthLinesBoxes, kTRUE, colorCracowRatio);
// 		DrawGammaSetMarkerTGraphAsym(graphRatioCombLowPt2760GeVLHC11h_0010, 0, 0, colorCracowRatio, colorCracowRatio, 5, kTRUE, colorCracowRatio);
// 		graphRatioCombLowPt2760GeVLHC11h_0010->Draw("l,same");
// 
// 		DrawGammaSetMarkerTGraphAsym(graphRatioCombCombFitStat2760GeVLHC11h_0010, markerStyleComb, markerSizeComb*2, kBlack, kBlack, widthLinesBoxes, kFALSE);
// 		graphRatioCombCombFitStat2760GeVLHC11h_0010->SetLineWidth(widthLinesBoxes);
// 		DrawGammaSetMarkerTGraphAsym(graphRatioCombCombFitSys2760GeVLHC11h_0010, markerStyleComb, markerSizeComb*2, kBlack, kBlack, widthLinesBoxes, kTRUE, 0);
// 		graphRatioCombCombFitSys2760GeVLHC11h_0010->SetLineWidth(0);
// 		graphRatioCombCombFitSys2760GeVLHC11h_0010->Draw("2,same");
// 		graphRatioCombCombFitStat2760GeVLHC11h_0010->Draw("p,same,e1");
// 		
// 		TGraphAsymmErrors* graphRatioCombLowPt2760GeVLHC11h_2050 = (TGraphAsymmErrors*)TheoryCracowLowPt_2050->Clone("graphRatioCombLowPt2760GeVLHC11h_2050");	
// 		graphRatioCombLowPt2760GeVLHC11h_2050 = CalculateGraphErrRatioToFit(graphRatioCombLowPt2760GeVLHC11h_2050, fitTCMInvYield2760GeVLHC11h_2050); 
// 
// // 		DrawGammaSetMarkerTGraphAsym(graphRatioCombLowPt2760GeVLHC11h_2050, 0, 0, colorCracowRatio,colorCracowRatio, widthLinesBoxes, kTRUE,colorCracowRatio);
// 		DrawGammaSetMarkerTGraphAsym(graphRatioCombLowPt2760GeVLHC11h_2050, 0, 0, colorCracowRatio,colorCracowRatio, 5, kTRUE,colorCracowRatio);
// 		graphRatioCombLowPt2760GeVLHC11h_2050->Draw("l,same");
// 
// 		DrawGammaSetMarkerTGraphAsym(graphRatioCombCombFitStat2760GeVLHC11h_2050, markerStyleComb, markerSizeComb*2, kBlack, kBlack, widthLinesBoxes, kFALSE);
// 		graphRatioCombCombFitStat2760GeVLHC11h_2050->SetLineWidth(widthLinesBoxes);
// 		DrawGammaSetMarkerTGraphAsym(graphRatioCombCombFitSys2760GeVLHC11h_2050, markerStyleComb, markerSizeComb*2, kBlack, kBlack, widthLinesBoxes, kTRUE, 0);
// 		graphRatioCombCombFitSys2760GeVLHC11h_2050->SetLineWidth(0);
// 		graphRatioCombCombFitSys2760GeVLHC11h_2050->Draw("2,same");
// 		graphRatioCombCombFitStat2760GeVLHC11h_2050->Draw("p,same,e1");
// 		
// 		DrawGammaLines(0.8, 30.,1., 1.,0.1,kGray);
// 		
// 	padInvSectionEPOSRatioCentTogether->cd();
// 	padInvSectionEPOSRatioCentTogether->SetLogx(1);
// 
// 		TH2F * ratio2DPythia;
// 		if(meson.CompareTo("Pi0")==0) ratio2DPythia=  new TH2F("ratio2DPythia","ratio2DPythia",1000,0.8,30.,1000,0.2,2.45);
// 		if(meson.CompareTo("Eta")==0) ratio2DPythia=  new TH2F("ratio2DPythia","ratio2DPythia",1000,0.8,30.,1000,0.2,2.45);
// 		SetStyleHistoTH2ForGraphs(ratio2DPythia, "#it{p}_{T} (GeV/#it{c})","#frac{EPOS, Data}{fit}", 0.85*textsizeLabelsXSecDown, textsizeLabelsXSecDown, 
// 								  0.85*textsizeLabelsXSecDown,textsizeLabelsXSecDown, 0.9,0.2/(textsizeFacXSecDown*marginXSec), 510, 505);
// 		ratio2DPythia->GetYaxis()->SetMoreLogLabels(kTRUE);
// 		ratio2DPythia->GetYaxis()->SetNdivisions(505);
// 		ratio2DPythia->GetYaxis()->SetNoExponent(kTRUE);
// 		ratio2DPythia->GetXaxis()->SetMoreLogLabels(kTRUE);
// 		ratio2DPythia->GetXaxis()->SetNoExponent(kTRUE);
// 		ratio2DPythia->GetXaxis()->SetLabelFont(42);
// 		ratio2DPythia->GetYaxis()->SetLabelFont(42);
// 		ratio2DPythia->GetYaxis()->SetLabelOffset(+0.01);
// 		ratio2DPythia->GetXaxis()->SetTickLength(0.06);
// 		ratio2DPythia->GetYaxis()->SetTickLength(0.04);
// 		ratio2DPythia->DrawCopy();
// 
// 		TH1D* histoRatioEPOSToFit2760GeVLHC11h_0010 = (TH1D*) histoEPOSRebin_0010->Clone();     
// 		histoRatioEPOSToFit2760GeVLHC11h_0010 = CalculateHistoRatioToFit (histoRatioEPOSToFit2760GeVLHC11h_0010, fitTCMInvYield2760GeVLHC11h_0010); 
// 
// 		DrawGammaSetMarker(histoRatioEPOSToFit2760GeVLHC11h_0010, 24, 1.5,colorEPOSRatio,colorEPOSRatio);  
// 		histoRatioEPOSToFit2760GeVLHC11h_0010->SetLineWidth(widthCommonFit);
// // 		histoRatioEPOSToFit2760GeVLHC11h_0010->GetXaxis()->SetRangeUser(0.5,14);
// 		histoRatioEPOSToFit2760GeVLHC11h_0010->Draw("same,hist,c");
// 		
// 		DrawGammaSetMarkerTGraphAsym(graphRatioCombCombFitStat2760GeVLHC11h_0010, markerStyleComb, markerSizeComb*2, kBlack, kBlack, widthLinesBoxes, kFALSE);
// 		graphRatioCombCombFitStat2760GeVLHC11h_0010->SetLineWidth(widthLinesBoxes);
// 		DrawGammaSetMarkerTGraphAsym(graphRatioCombCombFitSys2760GeVLHC11h_0010, markerStyleComb, markerSizeComb*2, kBlack, kBlack, widthLinesBoxes, kTRUE, 0);
// 		graphRatioCombCombFitSys2760GeVLHC11h_0010->SetLineWidth(0);
// 		graphRatioCombCombFitSys2760GeVLHC11h_0010->Draw("2,same");
// 		graphRatioCombCombFitStat2760GeVLHC11h_0010->Draw("p,same,e1");
// 
// 		TH1D* histoRatioEPOSToFit2760GeVLHC11h_2050 = (TH1D*) histoEPOSRebin_2050->Clone();     
// 		histoRatioEPOSToFit2760GeVLHC11h_2050 = CalculateHistoRatioToFit (histoRatioEPOSToFit2760GeVLHC11h_2050, fitTCMInvYield2760GeVLHC11h_2050); 
// 
// 		DrawGammaSetMarker(histoRatioEPOSToFit2760GeVLHC11h_2050, 24, 1.5, colorEPOSRatio,colorEPOSRatio);  
// 		histoRatioEPOSToFit2760GeVLHC11h_2050->SetLineWidth(widthCommonFit);
// // 		histoRatioEPOSToFit2760GeVLHC11h_2050->GetXaxis()->SetRangeUser(0.5,14);
// 		histoRatioEPOSToFit2760GeVLHC11h_2050->Draw("same,hist,c");
// 		
// 		DrawGammaSetMarkerTGraphAsym(graphRatioCombCombFitStat2760GeVLHC11h_2050, markerStyleComb, markerSizeComb*2, kBlack, kBlack, widthLinesBoxes, kFALSE);
// 		graphRatioCombCombFitStat2760GeVLHC11h_2050->SetLineWidth(widthLinesBoxes);
// 		DrawGammaSetMarkerTGraphAsym(graphRatioCombCombFitSys2760GeVLHC11h_2050, markerStyleComb, markerSizeComb*2, kBlack, kBlack, widthLinesBoxes, kTRUE, 0);
// 		graphRatioCombCombFitSys2760GeVLHC11h_2050->SetLineWidth(0);
// 		graphRatioCombCombFitSys2760GeVLHC11h_2050->Draw("2,same");
// 		graphRatioCombCombFitStat2760GeVLHC11h_2050->Draw("p,same,e1");
// 
// 		DrawGammaLines(0.8, 30.,1., 1.,0.1,kGray);
// 		
// 	canvasInvYieldSectionRatiosCentTogether->Update();
// 	canvasInvYieldSectionRatiosCentTogether->SaveAs(Form("%s/%s_YieldCombinedLHC11h_DataWithModelsAndRatios.%s",outputDir.Data(),meson.Data(),suffix.Data()));
// 	canvasInvYieldSectionRatiosCentTogether->SaveAs(Form("%s/%s_YieldCombinedLHC11h_DataWithModelsAndRatios.%s",paperPlots.Data(),meson.Data(),suffix.Data()));

	Double_t arrayBoundariesX1_XSec[2];
	Double_t arrayBoundariesY1_XSec[6];
	Double_t relativeMarginsXXSec[3];
	Double_t relativeMarginsYXSec[3];
	textSizeLabelsPixel = 90;
	ReturnCorrectValuesForCanvasScaling(2500,4000, 1, 5,0.13, 0.025, 0.003,0.05,arrayBoundariesX1_XSec,arrayBoundariesY1_XSec,relativeMarginsXXSec,relativeMarginsYXSec);
	
	TCanvas* canvasInvYieldSectionRatios = new TCanvas("canvasInvYieldSectionRatios","",0,0,2500,4000);  // gives the page size
	DrawGammaCanvasSettings( canvasInvYieldSectionRatios,  0.13, 0.02, 0.03, 0.06);

		TPad* padInvSectionSpec = new TPad("padInvSectionSpec", "", arrayBoundariesX1_XSec[0], arrayBoundariesY1_XSec[3], arrayBoundariesX1_XSec[1], arrayBoundariesY1_XSec[0],-1, -1, -2);
		DrawGammaPadSettings( padInvSectionSpec, relativeMarginsXXSec[0], relativeMarginsXXSec[2], relativeMarginsYXSec[0], relativeMarginsYXSec[1]);
		padInvSectionSpec->Draw();
		Double_t marginXSec = relativeMarginsXXSec[0]*2500;
		Double_t textsizeLabelsXSecUp = 0;
		Double_t textsizeFacXSecUp = 0;
		if (padInvSectionSpec->XtoPixel(padInvSectionSpec->GetX2()) < padInvSectionSpec->YtoPixel(padInvSectionSpec->GetY1())){
			textsizeLabelsXSecUp = (Double_t)textSizeLabelsPixel/padInvSectionSpec->XtoPixel(padInvSectionSpec->GetX2()) ;
			textsizeFacXSecUp = (Double_t)1./padInvSectionSpec->XtoPixel(padInvSectionSpec->GetX2()) ;
		} else {
			textsizeLabelsXSecUp = (Double_t)textSizeLabelsPixel/padInvSectionSpec->YtoPixel(padInvSectionSpec->GetY1());
			textsizeFacXSecUp = (Double_t)1./padInvSectionSpec->YtoPixel(padInvSectionSpec->GetY1());
		}
			
		TPad* padInvSectionLowPtRatio = new TPad("padInvSectionLowPtRatio", "", arrayBoundariesX1_XSec[0], arrayBoundariesY1_XSec[4], arrayBoundariesX1_XSec[1], arrayBoundariesY1_XSec[3],-1, -1, -2);
		DrawGammaPadSettings( padInvSectionLowPtRatio, relativeMarginsXXSec[0], relativeMarginsXXSec[2], relativeMarginsYXSec[1], relativeMarginsYXSec[1]);
		padInvSectionLowPtRatio->Draw();
		Double_t textsizeLabelsXSecMiddle = 0;
		Double_t textsizeFacXSecMiddle = 0;
		if (padInvSectionLowPtRatio->XtoPixel(padInvSectionLowPtRatio->GetX2()) < padInvSectionLowPtRatio->YtoPixel(padInvSectionLowPtRatio->GetY1())){
			textsizeLabelsXSecMiddle = (Double_t)textSizeLabelsPixel/padInvSectionLowPtRatio->XtoPixel(padInvSectionLowPtRatio->GetX2()) ;
			textsizeFacXSecMiddle = (Double_t)1./padInvSectionLowPtRatio->XtoPixel(padInvSectionLowPtRatio->GetX2()) ;
		} else {
			textsizeLabelsXSecMiddle = (Double_t)textSizeLabelsPixel/padInvSectionLowPtRatio->YtoPixel(padInvSectionLowPtRatio->GetY1());
			textsizeFacXSecMiddle = (Double_t)1./padInvSectionLowPtRatio->YtoPixel(padInvSectionLowPtRatio->GetY1());
		}
	
		TPad* padInvSectionEPOSRatio = new TPad("padInvSectionEPOSRatio", "", arrayBoundariesX1_XSec[0], arrayBoundariesY1_XSec[5], arrayBoundariesX1_XSec[1], arrayBoundariesY1_XSec[4],-1, -1, -2);
		DrawGammaPadSettings( padInvSectionEPOSRatio, relativeMarginsXXSec[0], relativeMarginsXXSec[2], relativeMarginsYXSec[1], relativeMarginsYXSec[2]);
		padInvSectionEPOSRatio->Draw();
		Double_t textsizeLabelsXSecDown = 0;
		Double_t textsizeFacXSecDown = 0;
		if (padInvSectionEPOSRatio->XtoPixel(padInvSectionEPOSRatio->GetX2()) < padInvSectionEPOSRatio->YtoPixel(padInvSectionEPOSRatio->GetY1())){
			textsizeLabelsXSecDown = (Double_t)textSizeLabelsPixel/padInvSectionEPOSRatio->XtoPixel(padInvSectionEPOSRatio->GetX2()) ;
			textsizeFacXSecDown = (Double_t)1./padInvSectionEPOSRatio->XtoPixel(padInvSectionEPOSRatio->GetX2()) ;
		} else {
			textsizeLabelsXSecDown = (Double_t)textSizeLabelsPixel/padInvSectionEPOSRatio->YtoPixel(padInvSectionEPOSRatio->GetY1());
			textsizeFacXSecDown = (Double_t)1./padInvSectionEPOSRatio->YtoPixel(padInvSectionEPOSRatio->GetY1());
		}
	
		
		padInvSectionSpec->cd();
		padInvSectionSpec->SetLogy(1);
		padInvSectionSpec->SetLogx(1);
// 		SetStyleHistoTH2ForGraphs(histo2DXSectionPi0, "#it{p}_{T} (GeV/#it{c})","#it{E} #frac{d^{3}#sigma}{d#it{p}^{3}} (pb GeV^{-2} #it{c}^{3} )",
// 								0.85*textsizeLabelsXSecUp,textsizeLabelsXSecUp, 0.85*textsizeLabelsXSecUp, textsizeLabelsXSecUp, 1,0.2/(textsizeFacXSecUp*marginXSec));
// 		histo2DXSectionPi0->GetXaxis()->SetMoreLogLabels();
// 		histo2DXSectionPi0->GetXaxis()->SetLabelOffset(+0.01);
		TH2F *histo2DRatioToModelsLHC11h = new TH2F("histo2DRatioToModelsLHC11h","histo2DRatioToModelsLHC11h",11000,0.8,30.,1000,5e-8,2e3);
		SetStyleHistoTH2ForGraphs(histo2DRatioToModelsLHC11h, "#it{p}_{T} (GeV/#it{c})","#frac{1}{2#pi #it{N}_{ev}} #frac{d^{2}#it{N}}{#it{p}_{T}d#it{p}_{T}d#it{y}} (GeV/#it{c})^{-2}",0.035,0.04, 0.035,0.04, 1.,1.45);
		histo2DRatioToModelsLHC11h->GetXaxis()->SetMoreLogLabels();
		histo2DRatioToModelsLHC11h->GetXaxis()->SetLabelOffset(-0.01);
		histo2DRatioToModelsLHC11h->Draw("copy");

		TGraphAsymmErrors *TheoryCracowLowPtforRatio_0010 = (TGraphAsymmErrors*)TheoryCracowLowPt_0010->Clone("TheoryCracowLowPtforRatio_0010");
// 		DrawGammaSetMarkerTGraphAsym(TheoryCracowLowPtforRatio_0010, 0, 0, colorCracowRatio, colorCracowRatio, widthLinesBoxes, kTRUE, colorCracowRatio);
		DrawGammaSetMarkerTGraphAsym(TheoryCracowLowPtforRatio_0010, 0, 0, colorCracowRatio, colorCracowRatio, 5, kTRUE, colorCracowRatio);
		TheoryCracowLowPtforRatio_0010->Draw("l,same");
		histoEPOSRebin_0010->SetLineColor(colorEPOSRatio);
		histoEPOSRebin_0010->Draw("same,c,histo");

		graphCombInvYieldSys2760GeVALHC11hScaled_0010->Draw("E2same");
				if(noXerrorBars) ProduceGraphAsymmWithoutXErrors(graphCombInvYieldStat2760GeVALHC11hScaled_0010);
		graphCombInvYieldStat2760GeVALHC11hScaled_0010->Draw("p,same,e1");	

		fitTCMInvYield2760GeVLHC11h_0010->SetLineStyle(4);
		fitTCMInvYield2760GeVLHC11h_0010->Draw("same");		
		
		TLatex *labelEnergyRatioToModelsLHC11h = new TLatex(0.5,0.89,collisionSystemPbPb0010.Data());
		SetStyleTLatex( labelEnergyRatioToModelsLHC11h, 0.035,4);
		labelEnergyRatioToModelsLHC11h->Draw();
// 		labelPreliminary->Draw();
		
		TLatex *labelDetSysRatioToModelsLHC11h;
		if(meson.CompareTo("Pi0")==0){
			labelDetSysRatioToModelsLHC11h= new TLatex(0.5,0.86,"#pi^{0} #rightarrow #gamma#gamma");
		} else if(meson.CompareTo("Eta")==0){
			labelDetSysRatioToModelsLHC11h= new TLatex(0.5,0.86,"#eta #rightarrow #gamma#gamma");
		}
		SetStyleTLatex( labelDetSysRatioToModelsLHC11h, 0.035,4);
		labelDetSysRatioToModelsLHC11h->Draw();
		
		TLegend* legendXsectionPaper = GetAndSetLegend2(0.17, 0.3-4*0.06, 0.5, 0.3, 0.85* textSizeLabelsPixel);
		legendXsectionPaper->SetNColumns(1);
		legendXsectionPaper->SetMargin(0.2);
		if(meson.CompareTo("Pi0")==0) legendXsectionPaper->AddEntry(graphCombInvYieldSys2760GeVALHC11hScaled_0010,"#pi^{0} ALICE","pf");
		else if(meson.CompareTo("Eta")==0) legendXsectionPaper->AddEntry(graphCombInvYieldSys2760GeVALHC11hScaled_0010,"#eta ALICE","pf");
		legendXsectionPaper->AddEntry(TheoryCracowLowPtforRatio_0010,"NEQ SHM","l");
		legendXsectionPaper->AddEntry(histoEPOSRebin_0010,"EPOS 3","l");
		legendXsectionPaper->AddEntry(fitTCMInvYield2760GeVLHC11h_0010,"#it{A}_{e} exp(-#it{E}_{T, kin}/#it{T}_{e}) + #it{A}/#(){1 + #frac{#it{p}_{T}^{2}}{#it{T}^{2}#upoint n}}^{-n}","l");
		legendXsectionPaper->Draw();		
		
	padInvSectionLowPtRatio->cd();
	padInvSectionLowPtRatio->SetLogx(1);
		TH2F * ratio2DLowPt;
		if(meson.CompareTo("Pi0")==0) ratio2DLowPt=  new TH2F("ratio2DLowPt","ratio2DLowPt",1000,0.8,30.,1000,0.2,2.45);
		if(meson.CompareTo("Eta")==0) ratio2DLowPt=  new TH2F("ratio2DLowPt","ratio2DLowPt",1000,0.8,30.,1000,0.2,2.45);
		SetStyleHistoTH2ForGraphs(ratio2DLowPt, "#it{p}_{T} (GeV/#it{c})","#frac{NEQ SHM, Data}{fit}", 0.85*textsizeLabelsXSecMiddle, textsizeLabelsXSecMiddle, 
								  0.85*textsizeLabelsXSecMiddle,textsizeLabelsXSecMiddle, 1,0.2/(textsizeFacXSecMiddle*marginXSec), 510, 505);
		ratio2DLowPt->GetYaxis()->SetMoreLogLabels(kTRUE);
		ratio2DLowPt->GetYaxis()->SetNdivisions(505);
		ratio2DLowPt->GetYaxis()->SetNoExponent(kTRUE);
		ratio2DLowPt->GetXaxis()->SetMoreLogLabels(kTRUE);
		ratio2DLowPt->GetXaxis()->SetNoExponent(kTRUE);
		ratio2DLowPt->GetXaxis()->SetLabelFont(42);
		ratio2DLowPt->GetYaxis()->SetLabelFont(42);
		ratio2DLowPt->GetYaxis()->SetLabelOffset(+0.01);
		ratio2DLowPt->GetXaxis()->SetTickLength(0.07);
		ratio2DLowPt->DrawCopy();

		TGraphAsymmErrors* graphRatioCombLowPt2760GeVLHC11h_0010 = (TGraphAsymmErrors*)TheoryCracowLowPt_0010->Clone("graphRatioCombLowPt2760GeVLHC11h_0010");	
		graphRatioCombLowPt2760GeVLHC11h_0010 = CalculateGraphErrRatioToFit(graphRatioCombLowPt2760GeVLHC11h_0010, fitTCMInvYield2760GeVLHC11h_0010); 

// 		DrawGammaSetMarkerTGraphAsym(graphRatioCombLowPt2760GeVLHC11h_0010, 0, 0, colorCracowRatio, colorCracowRatio, widthLinesBoxes, kTRUE, colorCracowRatio);
		DrawGammaSetMarkerTGraphAsym(graphRatioCombLowPt2760GeVLHC11h_0010, 0, 0, colorCracowRatio, colorCracowRatio, 5, kTRUE, colorCracowRatio);
		graphRatioCombLowPt2760GeVLHC11h_0010->Draw("l,same");

		DrawGammaSetMarkerTGraphAsym(graphRatioCombCombFitStat2760GeVLHC11h_0010, markerStyleComb, markerSizeComb*2, kBlack, kBlack, widthLinesBoxes, kFALSE);
		graphRatioCombCombFitStat2760GeVLHC11h_0010->SetLineWidth(widthLinesBoxes);
		DrawGammaSetMarkerTGraphAsym(graphRatioCombCombFitSys2760GeVLHC11h_0010, markerStyleComb, markerSizeComb*2, kBlack, kBlack, widthLinesBoxes, kTRUE, 0);
		graphRatioCombCombFitSys2760GeVLHC11h_0010->SetLineWidth(0);
		graphRatioCombCombFitSys2760GeVLHC11h_0010->Draw("2,same");
		graphRatioCombCombFitStat2760GeVLHC11h_0010->Draw("p,same,e1");
		
		DrawGammaLines(0.8, 30.,1., 1.,0.1,kGray);
		
	padInvSectionEPOSRatio->cd();
	padInvSectionEPOSRatio->SetLogx(1);

		TH2F * ratio2DPythia;
		if(meson.CompareTo("Pi0")==0) ratio2DPythia=  new TH2F("ratio2DPythia","ratio2DPythia",1000,0.8,30.,1000,0.2,2.45);
		if(meson.CompareTo("Eta")==0) ratio2DPythia=  new TH2F("ratio2DPythia","ratio2DPythia",1000,0.8,30.,1000,0.2,2.45);
		SetStyleHistoTH2ForGraphs(ratio2DPythia, "#it{p}_{T} (GeV/#it{c})","#frac{EPOS, Data}{fit}", 0.85*textsizeLabelsXSecDown, textsizeLabelsXSecDown, 
								  0.85*textsizeLabelsXSecDown,textsizeLabelsXSecDown, 0.9,0.2/(textsizeFacXSecDown*marginXSec), 510, 505);
		ratio2DPythia->GetYaxis()->SetMoreLogLabels(kTRUE);
		ratio2DPythia->GetYaxis()->SetNdivisions(505);
		ratio2DPythia->GetYaxis()->SetNoExponent(kTRUE);
		ratio2DPythia->GetXaxis()->SetMoreLogLabels(kTRUE);
		ratio2DPythia->GetXaxis()->SetNoExponent(kTRUE);
		ratio2DPythia->GetXaxis()->SetLabelFont(42);
		ratio2DPythia->GetYaxis()->SetLabelFont(42);
		ratio2DPythia->GetYaxis()->SetLabelOffset(+0.01);
		ratio2DPythia->GetXaxis()->SetTickLength(0.06);
		ratio2DPythia->GetYaxis()->SetTickLength(0.04);
		ratio2DPythia->DrawCopy();

		TH1D* histoRatioEPOSToFit2760GeVLHC11h_0010 = (TH1D*) histoEPOSRebin_0010->Clone();     
		histoRatioEPOSToFit2760GeVLHC11h_0010 = CalculateHistoRatioToFit (histoRatioEPOSToFit2760GeVLHC11h_0010, fitTCMInvYield2760GeVLHC11h_0010); 

		DrawGammaSetMarker(histoRatioEPOSToFit2760GeVLHC11h_0010, 24, 1.5,colorEPOSRatio,colorEPOSRatio);  
		histoRatioEPOSToFit2760GeVLHC11h_0010->SetLineWidth(widthCommonFit);
// 		histoRatioEPOSToFit2760GeVLHC11h_0010->GetXaxis()->SetRangeUser(0.5,14);
		histoRatioEPOSToFit2760GeVLHC11h_0010->Draw("same,hist,c");
		
		DrawGammaSetMarkerTGraphAsym(graphRatioCombCombFitStat2760GeVLHC11h_0010, markerStyleComb, markerSizeComb*2, kBlack, kBlack, widthLinesBoxes, kFALSE);
		graphRatioCombCombFitStat2760GeVLHC11h_0010->SetLineWidth(widthLinesBoxes);
		DrawGammaSetMarkerTGraphAsym(graphRatioCombCombFitSys2760GeVLHC11h_0010, markerStyleComb, markerSizeComb*2, kBlack, kBlack, widthLinesBoxes, kTRUE, 0);
		graphRatioCombCombFitSys2760GeVLHC11h_0010->SetLineWidth(0);
		graphRatioCombCombFitSys2760GeVLHC11h_0010->Draw("2,same");
		graphRatioCombCombFitStat2760GeVLHC11h_0010->Draw("p,same,e1");

		DrawGammaLines(0.8, 30.,1., 1.,0.1,kGray);
		
	canvasInvYieldSectionRatios->Update();
	canvasInvYieldSectionRatios->SaveAs(Form("%s/%s_YieldCombinedLHC11h_DataWithModelsAndRatios_0010.%s",outputDir.Data(),meson.Data(),suffix.Data()));
	canvasInvYieldSectionRatios->SaveAs(Form("%s/%s_YieldCombinedLHC11h_DataWithModelsAndRatios_0010.%s",paperPlots.Data(),meson.Data(),suffix.Data()));

	
	TCanvas* canvasInvYieldSectionRatios_2050 = new TCanvas("canvasInvYieldSectionRatios_2050","",0,0,2500,4000);  // gives the page size
	DrawGammaCanvasSettings( canvasInvYieldSectionRatios_2050,  0.13, 0.02, 0.03, 0.06);
	
		TPad* padInvSectionSpec_2050 = new TPad("padInvSectionSpec_2050", "", arrayBoundariesX1_XSec[0], arrayBoundariesY1_XSec[3], arrayBoundariesX1_XSec[1], arrayBoundariesY1_XSec[0],-1, -1, -2);
		DrawGammaPadSettings( padInvSectionSpec_2050, relativeMarginsXXSec[0], relativeMarginsXXSec[2], relativeMarginsYXSec[0], relativeMarginsYXSec[1]);
		padInvSectionSpec_2050->Draw();
		if (padInvSectionSpec_2050->XtoPixel(padInvSectionSpec_2050->GetX2()) < padInvSectionSpec_2050->YtoPixel(padInvSectionSpec_2050->GetY1())){
			textsizeLabelsXSecUp = (Double_t)textSizeLabelsPixel/padInvSectionSpec_2050->XtoPixel(padInvSectionSpec_2050->GetX2()) ;
			textsizeFacXSecUp = (Double_t)1./padInvSectionSpec_2050->XtoPixel(padInvSectionSpec_2050->GetX2()) ;
		} else {
			textsizeLabelsXSecUp = (Double_t)textSizeLabelsPixel/padInvSectionSpec_2050->YtoPixel(padInvSectionSpec_2050->GetY1());
			textsizeFacXSecUp = (Double_t)1./padInvSectionSpec_2050->YtoPixel(padInvSectionSpec_2050->GetY1());
		}
			
		TPad* padInvSectionLowPtRatio_2050 = new TPad("padInvSectionLowPtRatio_2050", "", arrayBoundariesX1_XSec[0], arrayBoundariesY1_XSec[4], arrayBoundariesX1_XSec[1], arrayBoundariesY1_XSec[3],-1, -1, -2);
		DrawGammaPadSettings( padInvSectionLowPtRatio_2050, relativeMarginsXXSec[0], relativeMarginsXXSec[2], relativeMarginsYXSec[1], relativeMarginsYXSec[1]);
		padInvSectionLowPtRatio_2050->Draw();
		if (padInvSectionLowPtRatio_2050->XtoPixel(padInvSectionLowPtRatio_2050->GetX2()) < padInvSectionLowPtRatio_2050->YtoPixel(padInvSectionLowPtRatio_2050->GetY1())){
			textsizeLabelsXSecMiddle = (Double_t)textSizeLabelsPixel/padInvSectionLowPtRatio_2050->XtoPixel(padInvSectionLowPtRatio_2050->GetX2()) ;
			textsizeFacXSecMiddle = (Double_t)1./padInvSectionLowPtRatio_2050->XtoPixel(padInvSectionLowPtRatio_2050->GetX2()) ;
		} else {
			textsizeLabelsXSecMiddle = (Double_t)textSizeLabelsPixel/padInvSectionLowPtRatio_2050->YtoPixel(padInvSectionLowPtRatio_2050->GetY1());
			textsizeFacXSecMiddle = (Double_t)1./padInvSectionLowPtRatio_2050->YtoPixel(padInvSectionLowPtRatio_2050->GetY1());
		}
	
		TPad* padInvSectionEPOSRatio_2050 = new TPad("padInvSectionEPOSRatio_2050", "", arrayBoundariesX1_XSec[0], arrayBoundariesY1_XSec[5], arrayBoundariesX1_XSec[1], arrayBoundariesY1_XSec[4],-1, -1, -2);
		DrawGammaPadSettings( padInvSectionEPOSRatio_2050, relativeMarginsXXSec[0], relativeMarginsXXSec[2], relativeMarginsYXSec[1], relativeMarginsYXSec[2]);
		padInvSectionEPOSRatio_2050->Draw();
		if (padInvSectionEPOSRatio_2050->XtoPixel(padInvSectionEPOSRatio_2050->GetX2()) < padInvSectionEPOSRatio_2050->YtoPixel(padInvSectionEPOSRatio_2050->GetY1())){
			textsizeLabelsXSecDown = (Double_t)textSizeLabelsPixel/padInvSectionEPOSRatio_2050->XtoPixel(padInvSectionEPOSRatio_2050->GetX2()) ;
			textsizeFacXSecDown = (Double_t)1./padInvSectionEPOSRatio_2050->XtoPixel(padInvSectionEPOSRatio_2050->GetX2()) ;
		} else {
			textsizeLabelsXSecDown = (Double_t)textSizeLabelsPixel/padInvSectionEPOSRatio_2050->YtoPixel(padInvSectionEPOSRatio_2050->GetY1());
			textsizeFacXSecDown = (Double_t)1./padInvSectionEPOSRatio_2050->YtoPixel(padInvSectionEPOSRatio_2050->GetY1());
		}

		padInvSectionSpec_2050->cd();
		padInvSectionSpec_2050->SetLogy(1);
		padInvSectionSpec_2050->SetLogx(1);
		histo2DRatioToModelsLHC11h->DrawCopy();
	
		TGraphAsymmErrors *TheoryCracowLowPtforRatio_2050 = (TGraphAsymmErrors*)TheoryCracowLowPt_2050->Clone("TheoryCracowLowPtforRatio_2050");
// 		DrawGammaSetMarkerTGraphAsym(TheoryCracowLowPtforRatio_2050, 0, 0, colorCracowRatio,colorCracowRatio, widthLinesBoxes, kTRUE,colorCracowRatio);
		DrawGammaSetMarkerTGraphAsym(TheoryCracowLowPtforRatio_2050, 0, 0, colorCracowRatio,colorCracowRatio, 5, kTRUE,colorCracowRatio);
		TheoryCracowLowPtforRatio_2050->Draw("l,same");
		histoEPOSRebin_2050->SetLineColor(colorEPOSRatio);
		histoEPOSRebin_2050->Draw("same,c,histo");

		graphCombInvYieldSys2760GeVALHC11hColor_2050->Draw("E2same");
				if(noXerrorBars) ProduceGraphAsymmWithoutXErrors(graphCombInvYieldStat2760GeVALHC11hColor_2050);
		graphCombInvYieldStat2760GeVALHC11hColor_2050->Draw("p,same,e1");	

		fitTCMInvYield2760GeVLHC11h_2050->SetLineStyle(4);
		fitTCMInvYield2760GeVLHC11h_2050->Draw("same");		
// 		labelPreliminary->Draw();
		TLatex *labelEnergyRatioToModelsLHC11h2 = new TLatex(0.5,0.89,collisionSystemPbPb2050.Data());
		SetStyleTLatex( labelEnergyRatioToModelsLHC11h2, 0.035,4);
		labelEnergyRatioToModelsLHC11h2->Draw();
		labelDetSysRatioToModelsLHC11h->Draw();
		
		TLegend* legendXsectionPaper2 = GetAndSetLegend2(0.17, 0.3-4*0.06, 0.5, 0.3, 0.85* textSizeLabelsPixel);
		legendXsectionPaper2->SetNColumns(1);
		legendXsectionPaper2->SetMargin(0.2);
		if(meson.CompareTo("Pi0")==0) legendXsectionPaper2->AddEntry(graphCombInvYieldSys2760GeVALHC11hColor_2050,"#pi^{0} ALICE","pf");
		else if(meson.CompareTo("Eta")==0) legendXsectionPaper2->AddEntry(graphCombInvYieldSys2760GeVALHC11hColor_2050,"#eta ALICE","pf");
		legendXsectionPaper2->AddEntry(TheoryCracowLowPtforRatio_2050,"NEQ SHM","l");
		legendXsectionPaper2->AddEntry(histoEPOSRebin_2050,"EPOS 2","l");
		legendXsectionPaper2->AddEntry(fitTCMInvYield2760GeVLHC11h_2050,"#it{A}_{e} exp(-#it{E}_{T, kin}/#it{T}_{e}) + #it{A}/#(){1 + #frac{#it{p}_{T}^{2}}{#it{T}^{2}#upoint n}}^{-n}","l");
		legendXsectionPaper2->Draw();		
		legendXsectionPaper2->Draw();		

		
		padInvSectionLowPtRatio_2050->cd();
		padInvSectionLowPtRatio_2050->SetLogx(1);
		ratio2DLowPt->DrawCopy();

		TGraphAsymmErrors* graphRatioCombLowPt2760GeVLHC11h_2050 = (TGraphAsymmErrors*)TheoryCracowLowPt_2050->Clone("graphRatioCombLowPt2760GeVLHC11h_2050");	
		graphRatioCombLowPt2760GeVLHC11h_2050 = CalculateGraphErrRatioToFit(graphRatioCombLowPt2760GeVLHC11h_2050, fitTCMInvYield2760GeVLHC11h_2050); 

// 		DrawGammaSetMarkerTGraphAsym(graphRatioCombLowPt2760GeVLHC11h_2050, 0, 0, colorCracowRatio,colorCracowRatio, widthLinesBoxes, kTRUE,colorCracowRatio);
		DrawGammaSetMarkerTGraphAsym(graphRatioCombLowPt2760GeVLHC11h_2050, 0, 0, colorCracowRatio,colorCracowRatio, 5, kTRUE,colorCracowRatio);
		graphRatioCombLowPt2760GeVLHC11h_2050->Draw("l,same");

		DrawGammaSetMarkerTGraphAsym(graphRatioCombCombFitStat2760GeVLHC11h_2050, markerStyleComb, markerSizeComb*2, kBlack, kBlack, widthLinesBoxes, kFALSE);
		graphRatioCombCombFitStat2760GeVLHC11h_2050->SetLineWidth(widthLinesBoxes);
		DrawGammaSetMarkerTGraphAsym(graphRatioCombCombFitSys2760GeVLHC11h_2050, markerStyleComb, markerSizeComb*2, kBlack, kBlack, widthLinesBoxes, kTRUE, 0);
		graphRatioCombCombFitSys2760GeVLHC11h_2050->SetLineWidth(0);
		graphRatioCombCombFitSys2760GeVLHC11h_2050->Draw("2,same");
		graphRatioCombCombFitStat2760GeVLHC11h_2050->Draw("p,same,e1");
		
		DrawGammaLines(0.8, 30.,1., 1.,0.1,kGray);
		
		
		padInvSectionEPOSRatio_2050->cd();
		padInvSectionEPOSRatio_2050->SetLogx(1);
		ratio2DPythia->DrawCopy();

		TH1D* histoRatioEPOSToFit2760GeVLHC11h_2050 = (TH1D*) histoEPOSRebin_2050->Clone();     
		histoRatioEPOSToFit2760GeVLHC11h_2050 = CalculateHistoRatioToFit (histoRatioEPOSToFit2760GeVLHC11h_2050, fitTCMInvYield2760GeVLHC11h_2050); 

		DrawGammaSetMarker(histoRatioEPOSToFit2760GeVLHC11h_2050, 24, 1.5, colorEPOSRatio,colorEPOSRatio);  
		histoRatioEPOSToFit2760GeVLHC11h_2050->SetLineWidth(widthCommonFit);
// 		histoRatioEPOSToFit2760GeVLHC11h_2050->GetXaxis()->SetRangeUser(0.5,14);
		histoRatioEPOSToFit2760GeVLHC11h_2050->Draw("same,hist,c");
		
		DrawGammaSetMarkerTGraphAsym(graphRatioCombCombFitStat2760GeVLHC11h_2050, markerStyleComb, markerSizeComb*2, kBlack, kBlack, widthLinesBoxes, kFALSE);
		graphRatioCombCombFitStat2760GeVLHC11h_2050->SetLineWidth(widthLinesBoxes);
		DrawGammaSetMarkerTGraphAsym(graphRatioCombCombFitSys2760GeVLHC11h_2050, markerStyleComb, markerSizeComb*2, kBlack, kBlack, widthLinesBoxes, kTRUE, 0);
		graphRatioCombCombFitSys2760GeVLHC11h_2050->SetLineWidth(0);
		graphRatioCombCombFitSys2760GeVLHC11h_2050->Draw("2,same");
		graphRatioCombCombFitStat2760GeVLHC11h_2050->Draw("p,same,e1");

		DrawGammaLines(0.8, 30.,1., 1.,0.1,kGray);

		
	canvasInvYieldSectionRatios_2050->Update();
	canvasInvYieldSectionRatios_2050->SaveAs(Form("%s/%s_YieldCombinedLHC11h_DataWithModelsAndRatios_2050.%s",outputDir.Data(),meson.Data(),suffix.Data()));
	canvasInvYieldSectionRatios_2050->SaveAs(Form("%s/%s_YieldCombinedLHC11h_DataWithModelsAndRatios_2050.%s",paperPlots.Data(),meson.Data(),suffix.Data()));	

	
	
// 	Double_t arrayBoundariesX1_XSec[2];
// 	Double_t arrayBoundariesY1_XSec[4];
// 	Double_t relativeMarginsXXSec[3];
// 	Double_t relativeMarginsYXSec[2];
// 	textSizeLabelsPixel = 90;
// 	ReturnCorrectValuesForCanvasScaling(2500,3200, 1, 4,0.13, 0.025, 0.005,0.07,arrayBoundariesX1_XSec,arrayBoundariesY1_XSec,relativeMarginsXXSec,relativeMarginsYXSec);
// 	
// 	TCanvas* canvasInvYieldSectionRatios = new TCanvas("canvasInvYieldSectionRatios","",0,0,2500,3200);  // gives the page size
// 	DrawGammaCanvasSettings( canvasInvYieldSectionRatios,  0.13, 0.02, 0.03, 0.06);
// 
// 		TPad* padInvSectionSpec = new TPad("padInvSectionSpec", "", arrayBoundariesX1_XSec[0], arrayBoundariesY1_XSec[3], arrayBoundariesX1_XSec[1], arrayBoundariesY1_XSec[0],-1, -1, -2);
// 		DrawGammaPadSettings( padInvSectionSpec, relativeMarginsXXSec[0], relativeMarginsXXSec[2], relativeMarginsYXSec[0], relativeMarginsYXSec[1]);
// 		padInvSectionSpec->Draw();
// 		Double_t marginXSec = relativeMarginsXXSec[0]*2500;
// 		Double_t textsizeLabelsXSecUp = 0;
// 		Double_t textsizeFacXSecUp = 0;
// 		if (padInvSectionSpec->XtoPixel(padInvSectionSpec->GetX2()) < padInvSectionSpec->YtoPixel(padInvSectionSpec->GetY1())){
// 			textsizeLabelsXSecUp = (Double_t)textSizeLabelsPixel/padInvSectionSpec->XtoPixel(padInvSectionSpec->GetX2()) ;
// 			textsizeFacXSecUp = (Double_t)1./padInvSectionSpec->XtoPixel(padInvSectionSpec->GetX2()) ;
// 		} else {
// 			textsizeLabelsXSecUp = (Double_t)textSizeLabelsPixel/padInvSectionSpec->YtoPixel(padInvSectionSpec->GetY1());
// 			textsizeFacXSecUp = (Double_t)1./padInvSectionSpec->YtoPixel(padInvSectionSpec->GetY1());
// 		}
// 			
// 		TPad* padInvSectionLowPtRatio = new TPad("padInvSectionLowPtRatio", "", arrayBoundariesX1_XSec[0], arrayBoundariesY1_XSec[4], arrayBoundariesX1_XSec[1], arrayBoundariesY1_XSec[3],-1, -1, -2);
// 		DrawGammaPadSettings( padInvSectionLowPtRatio, relativeMarginsXXSec[0], relativeMarginsXXSec[2], relativeMarginsYXSec[1], relativeMarginsYXSec[2]);
// 		padInvSectionLowPtRatio->Draw();
// 		Double_t textsizeLabelsXSecMiddle = 0;
// 		Double_t textsizeFacXSecMiddle = 0;
// 		if (padInvSectionLowPtRatio->XtoPixel(padInvSectionLowPtRatio->GetX2()) < padInvSectionLowPtRatio->YtoPixel(padInvSectionLowPtRatio->GetY1())){
// 			textsizeLabelsXSecMiddle = (Double_t)textSizeLabelsPixel/padInvSectionLowPtRatio->XtoPixel(padInvSectionLowPtRatio->GetX2()) ;
// 			textsizeFacXSecMiddle = (Double_t)1./padInvSectionLowPtRatio->XtoPixel(padInvSectionLowPtRatio->GetX2()) ;
// 		} else {
// 			textsizeLabelsXSecMiddle = (Double_t)textSizeLabelsPixel/padInvSectionLowPtRatio->YtoPixel(padInvSectionLowPtRatio->GetY1());
// 			textsizeFacXSecMiddle = (Double_t)1./padInvSectionLowPtRatio->YtoPixel(padInvSectionLowPtRatio->GetY1());
// 		}
// 			
// 		padInvSectionSpec->cd();
// 		padInvSectionSpec->SetLogy(1);
// 		padInvSectionSpec->SetLogx(1);
// // 		SetStyleHistoTH2ForGraphs(histo2DXSectionPi0, "#it{p}_{T} (GeV/#it{c})","#it{E} #frac{d^{3}#sigma}{d#it{p}^{3}} (pb GeV^{-2} #it{c}^{3} )",
// // 								0.85*textsizeLabelsXSecUp,textsizeLabelsXSecUp, 0.85*textsizeLabelsXSecUp, textsizeLabelsXSecUp, 1,0.2/(textsizeFacXSecUp*marginXSec));
// // 		histo2DXSectionPi0->GetXaxis()->SetMoreLogLabels();
// // 		histo2DXSectionPi0->GetXaxis()->SetLabelOffset(+0.01);
// 		TH2F *histo2DRatioToModelsLHC11h;
// 		if(meson.CompareTo("Pi0")==0){
// 			histo2DRatioToModelsLHC11h = new TH2F("histo2DRatioToModelsLHC11h","histo2DRatioToModelsLHC11h",11000,0.8,25.,1000,1.5e-8,1e3);
// 			SetStyleHistoTH2ForGraphs(histo2DRatioToModelsLHC11h, "#it{p}_{T} (GeV/#it{c})","#frac{1}{2#pi #it{N}_{ev}} #frac{d^{2}#it{N^{#pi^{0}}}}{#it{p}_{T}d#it{p}_{T}d#it{y}} (GeV/#it{c})^{-2}",0.035,0.04, 0.035,0.04, 1.,1.38);
// 		} else if(meson.CompareTo("Eta")==0){
// 			histo2DRatioToModelsLHC11h = new TH2F("histo2DRatioToModelsLHC11h","histo2DRatioToModelsLHC11h",11000,0.8,25.,1000,1.5e-8,1e2);
// 			SetStyleHistoTH2ForGraphs(histo2DRatioToModelsLHC11h, "#it{p}_{T} (GeV/#it{c})","#frac{1}{2#pi #it{N}_{ev}} #frac{d^{2}#it{N^{#eta}}}{#it{p}_{T}d#it{p}_{T}d#it{y}} (GeV/#it{c})^{-2}",0.035,0.04, 0.035,0.04, 1.,1.38);			
// 			
// 		}
// 		histo2DRatioToModelsLHC11h->GetXaxis()->SetMoreLogLabels();
// 		histo2DRatioToModelsLHC11h->GetXaxis()->SetLabelOffset(-0.01);
// 		histo2DRatioToModelsLHC11h->Draw("copy");
// 
// 		TGraphAsymmErrors *TheoryCracowLowPtforRatio_0010 = (TGraphAsymmErrors*)TheoryCracowLowPt_0010->Clone("TheoryCracowLowPtforRatio_0010");
// 		TheoryCracowLowPtforRatio_0010 = ScaleGraph(TheoryCracowLowPtforRatio_0010,0.25);
// 		DrawGammaSetMarkerTGraphAsym(TheoryCracowLowPtforRatio_0010, 0, 0, colorCracowRatio, colorCracowRatio, 5, kTRUE, colorCracowRatio);
// 		TheoryCracowLowPtforRatio_0010->Draw("l,same");
// 
// 		graphCombInvYieldStat2760GeVALHC11hScaled_0010 = ScaleGraph(graphCombInvYieldStat2760GeVALHC11hScaled_0010,0.25);
// 		graphCombInvYieldSys2760GeVALHC11hScaled_0010 = ScaleGraph(graphCombInvYieldSys2760GeVALHC11hScaled_0010,0.25);
// 		DrawGammaSetMarkerTGraphAsym(graphCombInvYieldSys2760GeVALHC11hScaled_0010, markerStyleComb, markerSizeComb, colorCombo0010 , colorCombo0010, 2, kTRUE);
// 		DrawGammaSetMarkerTGraphAsym(graphCombInvYieldStat2760GeVALHC11hScaled_0010, markerStyleComb, markerSizeComb, colorCombo0010, colorCombo0010);
// 		graphCombInvYieldSys2760GeVALHC11hScaled_0010->Draw("E2same");
// 		if(noXerrorBars) ProduceGraphAsymmWithoutXErrors(graphCombInvYieldStat2760GeVALHC11hScaled_0010);
// 		graphCombInvYieldStat2760GeVALHC11hScaled_0010->Draw("p,same,e1");	
// 
// 		fitTCMInvYield2760GeVLHC11h_0010->SetLineStyle(4);
// 		fitTCMInvYield2760GeVLHC11h_0010->Draw("same");		
// 		fitTCMInvYield2760GeVLHC11h_0010->SetParameter(0,fitTCMInvYield2760GeVLHC11h_0010->GetParameter(0)*0.25);
// 		fitTCMInvYield2760GeVLHC11h_0010->SetParameter(2,fitTCMInvYield2760GeVLHC11h_0010->GetParameter(2)*0.25);
// 
// 		
// 		TLatex *labelEnergyRatioToModelsLHC11h = new TLatex(0.55,0.87,collisionSystemPbPb0010.Data());
// 		SetStyleTLatex( labelEnergyRatioToModelsLHC11h, 0.035,4);
// 		TLatex *labelPreliminary3;
// 		labelPreliminary3= new TLatex(0.55,0.92,"ALICE Preliminary");
// 		SetStyleTLatex( labelPreliminary3, 0.035,4);
// 		TLatex *labelDetSysRatioToModelsLHC11h;
// 		if(meson.CompareTo("Pi0")==0){
// 			labelDetSysRatioToModelsLHC11h= new TLatex(0.55,0.83,"#pi^{0} #rightarrow #gamma#gamma");
// 		} else if(meson.CompareTo("Eta")==0){
// 			labelDetSysRatioToModelsLHC11h= new TLatex(0.55,0.83,"#eta #rightarrow #gamma#gamma");
// 		}
// 		SetStyleTLatex( labelDetSysRatioToModelsLHC11h, 0.035,4);
// 		labelEnergyRatioToModelsLHC11h->Draw();
// 		labelPreliminary3->Draw();
// 		labelDetSysRatioToModelsLHC11h->Draw();
// 		
// 		TLegend* legendXsectionPaper = GetAndSetLegend2(0.17, 0.3-4*0.06, 0.5, 0.25, 0.85* textSizeLabelsPixel);
// 		legendXsectionPaper->SetNColumns(1);
// 		legendXsectionPaper->SetMargin(0.2);
// 		if(meson.CompareTo("Pi0")==0) legendXsectionPaper->AddEntry(graphCombInvYieldSys2760GeVALHC11hScaled_0010,"#pi^{0} ALICE","pf");
// 		else if(meson.CompareTo("Eta")==0) legendXsectionPaper->AddEntry(graphCombInvYieldSys2760GeVALHC11hScaled_0010,"#eta ALICE","pf");
// 		legendXsectionPaper->AddEntry(TheoryCracowLowPtforRatio_0010,"NEQ SHM","l");
// 		legendXsectionPaper->AddEntry(fitTCMInvYield2760GeVLHC11h_0010,"#it{A}_{e} exp(-#it{E}_{T, kin}/#it{T}_{e}) + #it{A}/#(){1 + #frac{#it{p}_{T}^{2}}{#it{T}^{2}#upoint n}}^{-n}","l");
// 		legendXsectionPaper->Draw();		
// 		
// 	padInvSectionLowPtRatio->cd();
// 	padInvSectionLowPtRatio->SetLogx(1);
// 		TH2F * ratio2DLowPt;
// 		if(meson.CompareTo("Pi0")==0) ratio2DLowPt=  new TH2F("ratio2DLowPt","ratio2DLowPt",1000,0.8,25.,1000,0.2,2.45);
// 		if(meson.CompareTo("Eta")==0) ratio2DLowPt=  new TH2F("ratio2DLowPt","ratio2DLowPt",1000,0.8,25.,1000,0.2,2.45);
// 		SetStyleHistoTH2ForGraphs(ratio2DLowPt, "#it{p}_{T} (GeV/#it{c})","#frac{NEQ SHM, Data}{fit}", 0.85*textsizeLabelsXSecMiddle, textsizeLabelsXSecMiddle, 
// 								  0.85*textsizeLabelsXSecMiddle,textsizeLabelsXSecMiddle, 1,0.2/(textsizeFacXSecMiddle*marginXSec), 510, 505);
// 		ratio2DLowPt->GetYaxis()->SetMoreLogLabels(kTRUE);
// 		ratio2DLowPt->GetYaxis()->SetNdivisions(505);
// 		ratio2DLowPt->GetYaxis()->SetNoExponent(kTRUE);
// 		ratio2DLowPt->GetXaxis()->SetMoreLogLabels(kTRUE);
// 		ratio2DLowPt->GetXaxis()->SetNoExponent(kTRUE);
// 		ratio2DLowPt->GetXaxis()->SetLabelFont(42);
// 		ratio2DLowPt->GetYaxis()->SetLabelFont(42);
// 		ratio2DLowPt->GetYaxis()->SetLabelOffset(+0.01);
// 		ratio2DLowPt->GetXaxis()->SetTickLength(0.07);
// 		ratio2DLowPt->DrawCopy();
// 
// 		TGraphAsymmErrors* graphRatioCombLowPt2760GeVLHC11h_0010 = (TGraphAsymmErrors*)TheoryCracowLowPt_0010->Clone("graphRatioCombLowPt2760GeVLHC11h_0010");	
// 		graphRatioCombLowPt2760GeVLHC11h_0010 = ScaleGraph(graphRatioCombLowPt2760GeVLHC11h_0010,0.25);
// 		graphRatioCombLowPt2760GeVLHC11h_0010 = CalculateGraphErrRatioToFit(graphRatioCombLowPt2760GeVLHC11h_0010, fitTCMInvYield2760GeVLHC11h_0010); 
// 
// // 		DrawGammaSetMarkerTGraphAsym(graphRatioCombLowPt2760GeVLHC11h_0010, 0, 0, colorCracowRatio, colorCracowRatio, widthLinesBoxes, kTRUE, colorCracowRatio);
// 		DrawGammaSetMarkerTGraphAsym(graphRatioCombLowPt2760GeVLHC11h_0010, 0, 0, colorCracowRatio, colorCracowRatio, 5, kTRUE, colorCracowRatio);
// 		graphRatioCombLowPt2760GeVLHC11h_0010->Draw("l,same");
// 
// 		DrawGammaSetMarkerTGraphAsym(graphRatioCombCombFitStat2760GeVLHC11h_0010, markerStyleComb, markerSizeComb*2, kBlack, kBlack, widthLinesBoxes, kFALSE);
// 		graphRatioCombCombFitStat2760GeVLHC11h_0010->SetLineWidth(widthLinesBoxes);
// 		DrawGammaSetMarkerTGraphAsym(graphRatioCombCombFitSys2760GeVLHC11h_0010, markerStyleComb, markerSizeComb*2, kBlack, kBlack, widthLinesBoxes, kTRUE, 0);
// 		graphRatioCombCombFitSys2760GeVLHC11h_0010->SetLineWidth(0);
// 		graphRatioCombCombFitSys2760GeVLHC11h_0010->Draw("2,same");
// 		if(noXerrorBars) ProduceGraphAsymmWithoutXErrors(graphRatioCombCombFitStat2760GeVLHC11h_0010);
// 		graphRatioCombCombFitStat2760GeVLHC11h_0010->Draw("p,same,e1");
// 		
// 		DrawGammaLines(0.8, 30.,1., 1.,0.1,kGray);
// 		
// 	canvasInvYieldSectionRatios->Update();
// 	canvasInvYieldSectionRatios->SaveAs(Form("%s/%s_YieldCombinedLHC11h_DataWithModelsAndRatios_0010.%s",outputDir.Data(),meson.Data(),suffix.Data()));
// 	canvasInvYieldSectionRatios->SaveAs(Form("%s/%s_YieldCombinedLHC11h_DataWithModelsAndRatios_0010.%s",paperPlots.Data(),meson.Data(),suffix.Data()));
// 
// 	
// 	TCanvas* canvasInvYieldSectionRatios_2050 = new TCanvas("canvasInvYieldSectionRatios_2050","",0,0,2500,3200);  // gives the page size
// 	DrawGammaCanvasSettings( canvasInvYieldSectionRatios_2050,  0.13, 0.02, 0.03, 0.06);
// 	
// 		TPad* padInvSectionSpec_2050 = new TPad("padInvSectionSpec_2050", "", arrayBoundariesX1_XSec[0], arrayBoundariesY1_XSec[3], arrayBoundariesX1_XSec[1], arrayBoundariesY1_XSec[0],-1, -1, -2);
// 		DrawGammaPadSettings( padInvSectionSpec_2050, relativeMarginsXXSec[0], relativeMarginsXXSec[2], relativeMarginsYXSec[0], relativeMarginsYXSec[1]);
// 		padInvSectionSpec_2050->Draw();
// 		if (padInvSectionSpec_2050->XtoPixel(padInvSectionSpec_2050->GetX2()) < padInvSectionSpec_2050->YtoPixel(padInvSectionSpec_2050->GetY1())){
// 			textsizeLabelsXSecUp = (Double_t)textSizeLabelsPixel/padInvSectionSpec_2050->XtoPixel(padInvSectionSpec_2050->GetX2()) ;
// 			textsizeFacXSecUp = (Double_t)1./padInvSectionSpec_2050->XtoPixel(padInvSectionSpec_2050->GetX2()) ;
// 		} else {
// 			textsizeLabelsXSecUp = (Double_t)textSizeLabelsPixel/padInvSectionSpec_2050->YtoPixel(padInvSectionSpec_2050->GetY1());
// 			textsizeFacXSecUp = (Double_t)1./padInvSectionSpec_2050->YtoPixel(padInvSectionSpec_2050->GetY1());
// 		}
// 			
// 		TPad* padInvSectionLowPtRatio_2050 = new TPad("padInvSectionLowPtRatio_2050", "", arrayBoundariesX1_XSec[0], arrayBoundariesY1_XSec[4], arrayBoundariesX1_XSec[1], arrayBoundariesY1_XSec[3],-1, -1, -2);
// 		DrawGammaPadSettings( padInvSectionLowPtRatio_2050, relativeMarginsXXSec[0], relativeMarginsXXSec[2], relativeMarginsYXSec[1], relativeMarginsYXSec[2]);
// 		padInvSectionLowPtRatio_2050->Draw();
// 		if (padInvSectionLowPtRatio_2050->XtoPixel(padInvSectionLowPtRatio_2050->GetX2()) < padInvSectionLowPtRatio_2050->YtoPixel(padInvSectionLowPtRatio_2050->GetY1())){
// 			textsizeLabelsXSecMiddle = (Double_t)textSizeLabelsPixel/padInvSectionLowPtRatio_2050->XtoPixel(padInvSectionLowPtRatio_2050->GetX2()) ;
// 			textsizeFacXSecMiddle = (Double_t)1./padInvSectionLowPtRatio_2050->XtoPixel(padInvSectionLowPtRatio_2050->GetX2()) ;
// 		} else {
// 			textsizeLabelsXSecMiddle = (Double_t)textSizeLabelsPixel/padInvSectionLowPtRatio_2050->YtoPixel(padInvSectionLowPtRatio_2050->GetY1());
// 			textsizeFacXSecMiddle = (Double_t)1./padInvSectionLowPtRatio_2050->YtoPixel(padInvSectionLowPtRatio_2050->GetY1());
// 		}
// 		
// 			
// 		padInvSectionSpec_2050->cd();
// 		padInvSectionSpec_2050->SetLogy(1);
// 		padInvSectionSpec_2050->SetLogx(1);
// 		histo2DRatioToModelsLHC11h->DrawCopy();
// 	
// 		TGraphAsymmErrors *TheoryCracowLowPtforRatio_2050 = (TGraphAsymmErrors*)TheoryCracowLowPt_2050->Clone("TheoryCracowLowPtforRatio_2050");
// // 		DrawGammaSetMarkerTGraphAsym(TheoryCracowLowPtforRatio_2050, 0, 0, colorCracowRatio,colorCracowRatio, widthLinesBoxes, kTRUE,colorCracowRatio);
// 		DrawGammaSetMarkerTGraphAsym(TheoryCracowLowPtforRatio_2050, 0, 0, colorCracowRatio,colorCracowRatio, 5, kTRUE,colorCracowRatio);
// 		TheoryCracowLowPtforRatio_2050->Draw("l,same");
// 
// 		graphCombInvYieldSys2760GeVALHC11hColor_2050->Draw("E2same");
// 		if(noXerrorBars) ProduceGraphAsymmWithoutXErrors(graphCombInvYieldStat2760GeVALHC11hColor_2050);
// 		graphCombInvYieldStat2760GeVALHC11hColor_2050->Draw("p,same,e1");	
// 
// 		fitTCMInvYield2760GeVLHC11h_2050->SetLineStyle(4);
// 		fitTCMInvYield2760GeVLHC11h_2050->Draw("same");		
// 		labelPreliminary3->Draw();
// 		TLatex *labelEnergyRatioToModelsLHC11h2 = new TLatex(0.55,0.87,collisionSystemPbPb2050.Data());
// 		SetStyleTLatex( labelEnergyRatioToModelsLHC11h2, 0.035,4);
// 		labelEnergyRatioToModelsLHC11h2->Draw();
// 		labelDetSysRatioToModelsLHC11h->Draw();
// 		
// 		TLegend* legendXsectionPaper2 = GetAndSetLegend2(0.17, 0.3-4*0.06, 0.5, 0.25, 0.85* textSizeLabelsPixel);
// 		legendXsectionPaper2->SetNColumns(1);
// 		legendXsectionPaper2->SetMargin(0.2);
// 		if(meson.CompareTo("Pi0")==0) legendXsectionPaper2->AddEntry(graphCombInvYieldSys2760GeVALHC11hColor_2050,"#pi^{0} ALICE","pf");
// 		else if(meson.CompareTo("Eta")==0) legendXsectionPaper2->AddEntry(graphCombInvYieldSys2760GeVALHC11hColor_2050,"#eta ALICE","pf");
// 		legendXsectionPaper2->AddEntry(TheoryCracowLowPtforRatio_2050,"NEQ SHM","l");
// 		legendXsectionPaper2->AddEntry(fitTCMInvYield2760GeVLHC11h_2050,"#it{A}_{e} exp(-#it{E}_{T, kin}/#it{T}_{e}) + #it{A}/#(){1 + #frac{#it{p}_{T}^{2}}{#it{T}^{2}#upoint n}}^{-n}","l");
// 		legendXsectionPaper2->Draw();		
// 		legendXsectionPaper2->Draw();		
// 
// 		
// 		padInvSectionLowPtRatio_2050->cd();
// 		padInvSectionLowPtRatio_2050->SetLogx(1);
// 		ratio2DLowPt->DrawCopy();
// 
// 		TGraphAsymmErrors* graphRatioCombLowPt2760GeVLHC11h_2050 = (TGraphAsymmErrors*)TheoryCracowLowPt_2050->Clone("graphRatioCombLowPt2760GeVLHC11h_2050");	
// 		graphRatioCombLowPt2760GeVLHC11h_2050 = CalculateGraphErrRatioToFit(graphRatioCombLowPt2760GeVLHC11h_2050, fitTCMInvYield2760GeVLHC11h_2050); 
// 
// // 		DrawGammaSetMarkerTGraphAsym(graphRatioCombLowPt2760GeVLHC11h_2050, 0, 0, colorCracowRatio,colorCracowRatio, widthLinesBoxes, kTRUE,colorCracowRatio);
// 		DrawGammaSetMarkerTGraphAsym(graphRatioCombLowPt2760GeVLHC11h_2050, 0, 0, colorCracowRatio,colorCracowRatio, 5, kTRUE,colorCracowRatio);
// 		graphRatioCombLowPt2760GeVLHC11h_2050->Draw("l,same");
// 
// 		DrawGammaSetMarkerTGraphAsym(graphRatioCombCombFitStat2760GeVLHC11h_2050, markerStyleComb, markerSizeComb*2, kBlack, kBlack, widthLinesBoxes, kFALSE);
// 		graphRatioCombCombFitStat2760GeVLHC11h_2050->SetLineWidth(widthLinesBoxes);
// 		DrawGammaSetMarkerTGraphAsym(graphRatioCombCombFitSys2760GeVLHC11h_2050, markerStyleComb, markerSizeComb*2, kBlack, kBlack, widthLinesBoxes, kTRUE, 0);
// 		graphRatioCombCombFitSys2760GeVLHC11h_2050->SetLineWidth(0);
// 		graphRatioCombCombFitSys2760GeVLHC11h_2050->Draw("2,same");
// 		if(noXerrorBars) ProduceGraphAsymmWithoutXErrors(graphRatioCombCombFitStat2760GeVLHC11h_2050);
// 		graphRatioCombCombFitStat2760GeVLHC11h_2050->Draw("p,same,e1");
// 		
// 		DrawGammaLines(0.8, 30.,1., 1.,0.1,kGray);
// 		
// 	canvasInvYieldSectionRatios_2050->Update();
// 	canvasInvYieldSectionRatios_2050->SaveAs(Form("%s/%s_YieldCombinedLHC11h_DataWithModelsAndRatios_2050.%s",outputDir.Data(),meson.Data(),suffix.Data()));
// 	canvasInvYieldSectionRatios_2050->SaveAs(Form("%s/%s_YieldCombinedLHC11h_DataWithModelsAndRatios_2050.%s",paperPlots.Data(),meson.Data(),suffix.Data()));	
	
	TheoryCracowLowPtforRatio_0010 = ScaleGraph(TheoryCracowLowPtforRatio_0010,4);
	graphCombInvYieldStat2760GeVALHC11hScaled_0010 = ScaleGraph(graphCombInvYieldStat2760GeVALHC11hScaled_0010,4);
	graphCombInvYieldSys2760GeVALHC11hScaled_0010 = ScaleGraph(graphCombInvYieldSys2760GeVALHC11hScaled_0010,4);
	DrawGammaSetMarkerTGraphAsym(graphCombInvYieldSys2760GeVALHC11hScaled_0010, markerStyleComb, markerSizeComb, colorCombo0010 , colorCombo0010, 2, kTRUE);
	DrawGammaSetMarkerTGraphAsym(graphCombInvYieldStat2760GeVALHC11hScaled_0010, markerStyleComb, markerSizeComb, colorCombo0010, colorCombo0010);
	fitTCMInvYield2760GeVLHC11h_0010->SetParameter(0,fitTCMInvYield2760GeVLHC11h_0010->GetParameter(0)*4);
	fitTCMInvYield2760GeVLHC11h_0010->SetParameter(2,fitTCMInvYield2760GeVLHC11h_0010->GetParameter(2)*4);

	
	canvasInvYieldSectionPi0LHC11h->cd();
	histo2DInvYieldSectionPi0LHC11h->Draw("copy");
// 	if(meson.CompareTo("Pi0")==0) histo2DInvYieldSectionPi0LHC11h->GetXaxis()->SetRangeUser(0.3,maxPtRange);
// 	if(meson.CompareTo("Eta")==0) histo2DInvYieldSectionPi0LHC11h->GetXaxis()->SetRangeUser(0.4,maxPtRange);

		Int_t textSizeLabelsPixelSpectra = 50;
		Double_t marginSpectra = 0.14*1200;
		Double_t textsizeLabelsSpectra = 0;
		Double_t textsizeFacSpectra = 0;

		if (canvasInvYieldSectionPi0LHC11h->XtoPixel(canvasInvYieldSectionPi0LHC11h->GetX2()) < canvasInvYieldSectionPi0LHC11h->YtoPixel(canvasInvYieldSectionPi0LHC11h->GetY1())){
			textsizeLabelsSpectra = (Double_t)textSizeLabelsPixelSpectra/canvasInvYieldSectionPi0LHC11h->XtoPixel(canvasInvYieldSectionPi0LHC11h->GetX2()) ;
			textsizeFacSpectra = (Double_t)1./canvasInvYieldSectionPi0LHC11h->XtoPixel(canvasInvYieldSectionPi0LHC11h->GetX2()) ;
		} else {
			textsizeLabelsSpectra = (Double_t)textSizeLabelsPixelSpectra/canvasInvYieldSectionPi0LHC11h->YtoPixel(canvasInvYieldSectionPi0LHC11h->GetY1());
			textsizeFacSpectra = (Double_t)1./canvasInvYieldSectionPi0LHC11h->YtoPixel(canvasInvYieldSectionPi0LHC11h->GetY1());
		}

		TLegend* legendSpectraPP = new TLegend(0.19,0.15,0.52,0.22);
		legendSpectraPP->SetFillColor(0);
		legendSpectraPP->SetLineColor(0);
		legendSpectraPP->SetTextFont(42);
		legendSpectraPP->SetMargin(0.17);
		legendSpectraPP->SetTextSize(FontSize);

		if(meson.CompareTo("Pi0")==0){
			
			DrawGammaSetMarkerTGraphAsym(graphInvSectionCombStatPi02760GeVPlot, markerStyleCommmonSpectrumpp,markerSizeSpectrum, kBlack , kBlack);
			if(noXerrorBars) ProduceGraphAsymmWithoutXErrors(graphInvSectionCombStatPi02760GeVPlot);
			graphInvSectionCombStatPi02760GeVPlot->Draw("p,same,e1");
			DrawGammaSetMarkerTGraphAsym(graphInvSectionCombSysPi02760GeVPlot, markerStyleCommmonSpectrumpp,markerSizeSpectrum, kBlack , kBlack, widthLinesBoxes, kTRUE);//, colorComb1020-5);
			graphInvSectionCombSysPi02760GeVPlot->Draw("E2same");
			
						
// 			legendSpectraPP->SetHeader("Eur.Phys.J. C (2014)");
			legendSpectraPP->SetHeader(collisionSystemPP2760GeV.Data());
			legendSpectraPP->AddEntry(graphInvSectionCombSysPi02760GeVPlot,"EPJC 74 (2014) 3108","pf");//"Eur. Phys. J. C (2014) 74:3108","pf");
// 			legendSpectraPP->AddEntry((TObject*)0,"22 April 2015","");
// 			legendSpectraPP->AddEntry(graphNLOCalcDSS14InvYieldPi02760GeVScaledNcoll0010,"pQCD DSS14","l");

		} else if(meson.CompareTo("Eta")==0){

			DrawGammaSetMarkerTGraphAsym(graphInvSectionCombStatEta2760GeVPlot, markerStyleCommmonSpectrumpp,markerSizeSpectrum, kBlack , kBlack);
			if(noXerrorBars) ProduceGraphAsymmWithoutXErrors(graphInvSectionCombStatEta2760GeVPlot);
			graphInvSectionCombStatEta2760GeVPlot->Draw("p,same,e1");
			DrawGammaSetMarkerTGraphAsym(graphInvSectionCombSysEta2760GeVPlot, markerStyleCommmonSpectrumpp,markerSizeSpectrum, kBlack , kBlack, widthLinesBoxes, kTRUE);//, colorComb1020-5);
			graphInvSectionCombSysEta2760GeVPlot->Draw("E2same");
			
// 			DrawGammaSetMarkerTGraphAsym(graphMtScaledEtaStat,24, 2, kGray+2, kGray+2);
// 			DrawGammaSetMarkerTGraphAsym(graphMtScaledEtaSys,24, 2, kGray+2, kGray+2);
// // 			graphMtScaledEtaStat->Draw("same");
// 			graphMtScaledEtaSys->Draw("p,same");		
			
// 			legendSpectraPP->SetHeader("J. Phys. G 38 (2011) 124076");
			legendSpectraPP->SetHeader(collisionSystemPP2760GeV.Data());
			legendSpectraPP->AddEntry(graphInvSectionCombSysEta2760GeVPlot,"JPG 38 (2011) 124076","pf"); //"J. Phys. G 38 (2011) 124076","pf");
// 			legendSpectraPP->AddEntry(graphInvSectionCombSysEta2760GeVPlot,collisionSystemPP2760GeV.Data(),"pf");
// 			legendSpectraPP->AddEntry((TObject*)0,"J. Phys. G 38 (2011) 124076","");
// 			legendSpectraPP->AddEntry(graphMtScaledEtaSys,"derived from #pi^{0} (pQCD)","pl");
// 			legendSpectraPP->AddEntry(graphNLOCalcDSS07InvYieldEta2760GeVScaledNcoll0010,"pQCD DSS07","l");

		}
// 		legendSpectraPPnlo->Draw();
		legendSpectraPP->Draw();
		
		TLegend* legendInvYieldSectionPi0LHC11h_WitPP = new TLegend(0.61,0.76,0.95,0.86); //0.17,0.13,0.5,0.24);
		legendInvYieldSectionPi0LHC11h_WitPP->SetFillColor(0);
		legendInvYieldSectionPi0LHC11h_WitPP->SetMargin(0.17);
		legendInvYieldSectionPi0LHC11h_WitPP->SetLineColor(0);
		legendInvYieldSectionPi0LHC11h_WitPP->SetTextFont(42);
		legendInvYieldSectionPi0LHC11h_WitPP->SetTextSize(FontSize);
		legendInvYieldSectionPi0LHC11h_WitPP->SetHeader(collisionSystem2760GeV.Data());
		legendInvYieldSectionPi0LHC11h_WitPP->AddEntry(graphCombInvYieldSys2760GeVALHC11hScaled_0010,Form("  %s",cent0010.Data()),"fp");
		legendInvYieldSectionPi0LHC11h_WitPP->AddEntry(graphCombInvYieldSys2760GeVALHC11hColor_2050,Form("%s",cent2050.Data()),"fp");
		legendInvYieldSectionPi0LHC11h_WitPP->Draw();

		labelDetSysInvYieldSectionPi0LHC11hwithPP->Draw();
		labelPreliminary->Draw();
		labelFactorLower->Draw();

		graphCombInvYieldSys2760GeVALHC11hScaled_0010->Draw("E2same");
		if(noXerrorBars) ProduceGraphAsymmWithoutXErrors(graphCombInvYieldStat2760GeVALHC11hScaled_0010);
		graphCombInvYieldStat2760GeVALHC11hScaled_0010->Draw("p,same,e1");	
	
	
		graphCombInvYieldSys2760GeVALHC11hColor_2050->Draw("E2same");
		if(noXerrorBars) ProduceGraphAsymmWithoutXErrors(graphCombInvYieldStat2760GeVALHC11hColor_2050);
		graphCombInvYieldStat2760GeVALHC11hColor_2050->Draw("p,same,e1");	
	
		
	canvasInvYieldSectionPi0LHC11h->SaveAs(Form("%s/%s_YieldCombinedLHC11h_DataOnly_withPP.%s",outputDir.Data(),meson.Data(),suffix.Data()));
	canvasInvYieldSectionPi0LHC11h->SaveAs(Form("%s/%s_YieldCombinedLHC11h_DataOnly_withPP.%s",paperPlots.Data(),meson.Data(),suffix.Data()));
	

	
	
		
	canvasInvYieldSectionPi0LHC11h->cd();
	histo2DInvYieldSectionPi0LHC11h->DrawCopy();
		
// 		if(meson.CompareTo("Pi0")==0){
// 			histo2DInvYieldSectionPi0LHC11h = new TH2F("histo2DInvYieldSectionPi0LHC11h","histo2DInvYieldSectionPi0LHC11h",11000,0.23,60.,1000,1e-2,1e1);
// 			SetStyleHistoTH2ForGraphs(histo2DInvYieldSectionPi0LHC11h, "#it{p}_{T} (GeV/#it{c})","#frac{1}{2#pi #it{N}_{ev}} #frac{d^{2}#it{N}}{#it{p}_{T}d#it{p}_{T}d#it{y}} (GeV/#it{c})^{-2}",0.035,0.04, 0.035,0.04, 1.,1.45);
// 			histo2DInvYieldSectionPi0LHC11h->GetXaxis()->SetMoreLogLabels();
// 			histo2DInvYieldSectionPi0LHC11h->GetXaxis()->SetLabelOffset(-0.01);
// 			histo2DInvYieldSectionPi0LHC11h->Draw("copy");
// 
// 		} else if(meson.CompareTo("Eta")==0){
// 			histo2DInvYieldSectionPi0LHC11h = new TH2F("histo2DInvYieldSectionPi0LHC11h","histo2DInvYieldSectionPi0LHC11h",11000,0.8,30.,1000,1e-10,1e2);
// 			SetStyleHistoTH2ForGraphs(histo2DInvYieldSectionPi0LHC11h, "#it{p}_{T} (GeV/#it{c})","#frac{1}{2#pi #it{N}_{ev}} #frac{d^{2}#it{N}}{#it{p}_{T}d#it{p}_{T}d#it{y}} (GeV/#it{c})^{-2} ",0.035,0.04, 0.035,0.039, 1.,1.47);
// 			histo2DInvYieldSectionPi0LHC11h->GetXaxis()->SetMoreLogLabels();
// 			histo2DInvYieldSectionPi0LHC11h->GetXaxis()->SetLabelOffset(-0.01);
// 			histo2DInvYieldSectionPi0LHC11h->Draw("copy");
// 	
// 		}
		labelFactorUpper->Draw();

		TLegend* legendSpectraPPnlo = new TLegend(0.19,0.12,0.52,0.36);//0.6,0.7,0.96,0.87);
		legendSpectraPPnlo->SetFillColor(0);
		legendSpectraPPnlo->SetLineColor(0);
		legendSpectraPPnlo->SetMargin(0.17);
		legendSpectraPPnlo->SetTextFont(42);
		legendSpectraPPnlo->SetTextSize(FontSize);
// 		legendSpectraPP->Draw();

		TGraphAsymmErrors *graphNLOforPi0PP = (TGraphAsymmErrors*)graphNLOCalcDSS14InvYieldPi0Band->Clone("graphNLOforPi0PP");
		TGraphAsymmErrors *graphNLOforPi00010 = (TGraphAsymmErrors*)graphNLOCalcDSS14InvYieldPi0Band->Clone("graphNLOforPi00010");		
		graphNLOforPi00010 = ScaleGraph(graphNLOforPi00010,nColl0010*4);
		TGraphAsymmErrors *graphNLOforPi02050 = (TGraphAsymmErrors*)graphNLOCalcDSS14InvYieldPi0Band->Clone("graphNLOforPi02050");
		graphNLOforPi02050 = ScaleGraph(graphNLOforPi02050,nColl2050);

		TGraphAsymmErrors *graphNLOforEtaPP = (TGraphAsymmErrors*)graphNLOCalcDSS07InvYieldEtaBand->Clone("graphNLOforEtaPP");
		TGraphAsymmErrors *graphNLOforEta0010 = (TGraphAsymmErrors*)graphNLOCalcDSS07InvYieldEtaBand->Clone("graphNLOforEta0010");		
		graphNLOforEta0010 = ScaleGraph(graphNLOforEta0010,nColl0010*4);
		TGraphAsymmErrors *graphNLOforEta2050 = (TGraphAsymmErrors*)graphNLOCalcDSS07InvYieldEtaBand->Clone("graphNLOforEta2050");
		graphNLOforEta2050 = ScaleGraph(graphNLOforEta2050,nColl2050);
		
		TLatex *labelNLO;
		labelNLO= new TLatex(0.61,0.75,"PDF: MSTW, FF: DSS14");
		SetStyleTLatex( labelNLO, 0.035,4);


		if(meson.CompareTo("Pi0")==0){
						
// 			DrawGammaNLOTGraph(graphNLOCalcmuHalfDSS14InvSecPi02760GeVNcoll0010, 2, 2, kGray+1);
// 			graphNLOCalcmuHalfDSS14InvSecPi02760GeVNcoll0010->Draw("l,same");
// 			DrawGammaNLOTGraph(graphNLOCalcmuHalfDSS14InvSecPi02760GeVNcoll2050, 2, 2,kGray+2);
// 			graphNLOCalcmuHalfDSS14InvSecPi02760GeVNcoll2050->Draw("l,same");
// 
// 			DrawGammaNLOTGraph(graphNLOCalcDSS14InvYieldPi02760GeVScaledNcoll0010, 2, 3, kGray+1);
// 			graphNLOCalcDSS14InvYieldPi02760GeVScaledNcoll0010->Draw("l,same");
// 			DrawGammaNLOTGraph(graphNLOCalcDSS14InvYieldPi02760GeVScaledNcoll2050, 2, 3, kGray+2);
// 			graphNLOCalcDSS14InvYieldPi02760GeVScaledNcoll2050->Draw("l,same");
// 			
// 			DrawGammaNLOTGraph(graphNLOCalcmuTwoDSS14InvSecPi02760GeVNcoll0010, 2, 4, kGray+1);
// 			graphNLOCalcmuTwoDSS14InvSecPi02760GeVNcoll0010->Draw("l,same");
// 			DrawGammaNLOTGraph(graphNLOCalcmuTwoDSS14InvSecPi02760GeVNcoll2050, 2, 4,kGray+2);
// 			graphNLOCalcmuTwoDSS14InvSecPi02760GeVNcoll2050->Draw("l,same");
						
// 			legendSpectraPPnlo->SetHeader("Eur.Phys.J. C (2014)");
// 			legendSpectraPPnlo->AddEntry(graphInvSectionCombSysPi02760GeVPlot,collisionSystemPP2760GeV.Data(),"pf");
// 			legendSpectraPPnlo->AddEntry((TObject*)0,"Eur.Phys.J. C (2014)","");
// 			legendSpectraPPnlo->AddEntry((TObject*)0,"22 April 2015","");
// 			legendSpectraPPnlo->AddEntry(graphNLOCalcDSS14InvYieldPi02760GeVScaledNcoll0010,"pQCD DSS14","l");
			legendSpectraPPnlo->SetHeader(collisionSystemPP2760GeV.Data());
			legendSpectraPPnlo->AddEntry(graphInvSectionCombSysPi02760GeVPlot,"EPJC 74 (2014) 3108","pf");//"Eur. Phys. J. C (2014) 74:3108","pf");
// 			legendSpectraPPnlo->AddEntry((TObject*)0,"","");
 			legendSpectraPPnlo->AddEntry(graphNLOforPi0PP,"pQCD NLO #mu = #it{p}_{T}","l");
			legendSpectraPPnlo->AddEntry((TObject*)0,"PDF: MSTW, FF: DSS14","");
			legendSpectraPPnlo->AddEntry((TObject*)0,"PRD 91 014035",""); //"Phys. Rev. D 91 014035","");
			legendSpectraPPnlo->AddEntry((TObject*)0,"scaled by <N_{coll}>","");
// 			legendSpectraPPnlo->AddEntry(graphNLOCalcmuHalfDSS14InvSecPi02760GeVNcoll0010,"NLO #mu = 0.5 #it{p}_{T}","l");
// 			legendSpectraPPnlo->AddEntry(graphNLOCalcDSS14InvYieldPi02760GeVScaledNcoll0010,"NLO #mu = #it{p}_{T}","l");
// 			legendSpectraPPnlo->AddEntry(graphNLOCalcmuTwoDSS14InvSecPi02760GeVNcoll0010,"NLO #mu = 2 #it{p}_{T}","l");
// 			legendSpectraPPnlo->AddEntry((TObject*)0,"PRD 91 014035",""); //"Phys. Rev. D 91 014035","");
// 			legendSpectraPPnlo->AddEntry(graphNLOCalcmuHalfDSS14InvSecPi02760GeVNcoll0010,"NLO #mu = 0.5 #it{p}_{T}","l");
// 			legendSpectraPPnlo->AddEntry(graphNLOCalcDSS14InvYieldPi02760GeVScaledNcoll0010,"NLO #mu = #it{p}_{T}","l");
// 			legendSpectraPPnlo->AddEntry(graphNLOCalcmuTwoDSS14InvSecPi02760GeVNcoll0010,"NLO #mu = 2 #it{p}_{T}","l");
// 			legendSpectraPPnlo->AddEntry((TObject*)0,"scaled by <N_{_{coll}>","");
			legendSpectraPPnlo->Draw();
// 			labelNLO->Draw();
			
			DrawGammaSetMarkerTGraphAsym(graphNLOforPi0PP, 0, 0, colorNLO, colorNLO, 3, kTRUE, colorNLO);
			graphNLOforPi0PP->Draw("3,same");
			DrawGammaSetMarkerTGraphAsym(graphNLOforPi00010, 0, 0, colorNLO, colorNLO, widthLinesBoxes, kTRUE, colorNLO);
			graphNLOforPi00010->Draw("3,same");
			DrawGammaSetMarkerTGraphAsym(graphNLOforPi02050, 0, 0, colorNLO, colorNLO, widthLinesBoxes, kTRUE, colorNLO);
			graphNLOforPi02050->Draw("3,same");
			
			DrawGammaSetMarkerTGraphAsym(graphInvSectionCombStatPi02760GeVPlot, markerStyleCommmonSpectrumpp,markerSizeSpectrum, kBlack , kBlack);
			graphInvSectionCombStatPi02760GeVPlot->Draw("p,same,e1");
			DrawGammaSetMarkerTGraphAsym(graphInvSectionCombSysPi02760GeVPlot, markerStyleCommmonSpectrumpp,markerSizeSpectrum, kBlack , kBlack, widthLinesBoxes, kTRUE);//, colorComb1020-5);
			graphInvSectionCombSysPi02760GeVPlot->Draw("E2same");


		} else if(meson.CompareTo("Eta")==0){


// 			DrawGammaNLOTGraph(graphNLOCalcmuHalfDSS07InvSecEta2760GeVNcoll0010, 2, 2, kGray+1);
// 			graphNLOCalcmuHalfDSS07InvSecEta2760GeVNcoll0010->Draw("l,same");
// 			DrawGammaNLOTGraph(graphNLOCalcmuHalfDSS07InvSecEta2760GeVNcoll2050, 2, 2, kGray+2);
// 			graphNLOCalcmuHalfDSS07InvSecEta2760GeVNcoll2050->Draw("l,same");
// 
// 			DrawGammaNLOTGraph(graphNLOCalcmuTwoDSS07InvSecEta2760GeVNcoll0010, 2, 4, kGray+1);
// 			graphNLOCalcmuTwoDSS07InvSecEta2760GeVNcoll0010->Draw("l,same");
// 			DrawGammaNLOTGraph(graphNLOCalcmuTwoDSS07InvSecEta2760GeVNcoll2050, 2, 4, kGray+2);
// 			graphNLOCalcmuTwoDSS07InvSecEta2760GeVNcoll2050->Draw("l,same");
// 			
// 			DrawGammaNLOTGraph(graphNLOCalcDSS07InvYieldEta2760GeVScaledNcoll0010, 2, 3, kGray+1);
// 			graphNLOCalcDSS07InvYieldEta2760GeVScaledNcoll0010->Draw("l,same");
// 			DrawGammaNLOTGraph(graphNLOCalcDSS07InvYieldEta2760GeVScaledNcoll2050, 2, 3, kGray+2);
// 			graphNLOCalcDSS07InvYieldEta2760GeVScaledNcoll2050->Draw("l,same");
			
// 			DrawGammaSetMarkerTGraphAsym(graphMtScaledEtaStat,24, 2, kGray+2, kGray+2);
// 			DrawGammaSetMarkerTGraphAsym(graphMtScaledEtaSys,24, 2, kGray+2, kGray+2);
// // 			graphMtScaledEtaStat->Draw("same");
// 			graphMtScaledEtaSys->Draw("p,same");		
			
// 			legendSpectraPPnlo->SetHeader("J. Phys. G 38 (2011) 124076");
// 			legendSpectraPPnlo->AddEntry(graphInvSectionCombSysEta2760GeVPlot,collisionSystemPP2760GeV.Data(),"pf");
// 			legendSpectraPPnlo->AddEntry((TObject*)0,"J. Phys. G 38 (2011) 124076","");
// 			legendSpectraPPnlo->AddEntry(graphMtScaledEtaSys,"derived from #pi^{0} (pQCD)","pl");
// 			legendSpectraPPnlo->AddEntry(graphNLOCalcDSS07InvYieldEta2760GeVScaledNcoll0010,"pQCD DSS07","l");
			legendSpectraPPnlo->SetHeader(collisionSystemPP2760GeV.Data());
			legendSpectraPPnlo->AddEntry(graphInvSectionCombSysEta2760GeVPlot,"JPG 38 (2011) 124076","pf"); //"J. Phys. G 38 (2011) 124076","pf");
// 			legendSpectraPPnlo->AddEntry(graphNLOCalcmuHalfDSS07InvSecEta2760GeVNcoll0010,"NLO #mu = 0.5 #it{p}_{T}","l");
// 			legendSpectraPPnlo->AddEntry(graphNLOCalcDSS07InvYieldEta2760GeVScaledNcoll0010,"NLO #mu = #it{p}_{T}","l");
// 			legendSpectraPPnlo->AddEntry(graphNLOCalcmuTwoDSS07InvSecEta2760GeVNcoll0010,"NLO #mu = 2 #it{p}_{T}","l");
// 			legendSpectraPPnlo->AddEntry((TObject*)0,"","");
 			legendSpectraPPnlo->AddEntry(graphNLOforEtaPP,"pQCD NLO #mu = #it{p}_{T}","l");
			legendSpectraPPnlo->AddEntry((TObject*)0,"PDF: MSTW, FF: DSS07","");
			legendSpectraPPnlo->AddEntry((TObject*)0,"PRD 91 014035",""); //"Phys. Rev. D 91 014035","");
			legendSpectraPPnlo->AddEntry((TObject*)0,"scaled by <N_{coll}>","");
// 			legendSpectraPPnlo->AddEntry((TObject*)0,"PRD 91 014035",""); //"Phys. Rev. D 91 014035","");
// 			legendSpectraPPnlo->AddEntry(graphNLOCalcmuHalfDSS14InvSecPi02760GeVNcoll0010,"NLO #mu = 0.5 #it{p}_{T}","l");
// 			legendSpectraPPnlo->AddEntry(graphNLOCalcDSS14InvYieldPi02760GeVScaledNcoll0010,"NLO #mu = #it{p}_{T}","l");
// 			legendSpectraPPnlo->AddEntry(graphNLOCalcmuTwoDSS14InvSecPi02760GeVNcoll0010,"NLO #mu = 2 #it{p}_{T}","l");
// 			legendSpectraPPnlo->AddEntry((TObject*)0,"scaled by <N_{_{coll}>","");
			legendSpectraPPnlo->Draw();
// 			labelNLO->Draw();

			DrawGammaSetMarkerTGraphAsym(graphNLOforEtaPP, 0, 0, colorNLO, colorNLO, 3, kTRUE, colorNLO);
			graphNLOforEtaPP->Draw("3,same");
			DrawGammaSetMarkerTGraphAsym(graphNLOforEta0010, 0, 0, colorNLO, colorNLO, widthLinesBoxes, kTRUE, colorNLO);
			graphNLOforEta0010->Draw("3,same");
			DrawGammaSetMarkerTGraphAsym(graphNLOforEta2050, 0, 0, colorNLO, colorNLO, widthLinesBoxes, kTRUE, colorNLO);
			graphNLOforEta2050->Draw("3,same");


			DrawGammaSetMarkerTGraphAsym(graphInvSectionCombStatEta2760GeVPlot, markerStyleCommmonSpectrumpp,markerSizeSpectrum, kBlack , kBlack);
			graphInvSectionCombStatEta2760GeVPlot->Draw("p,same,e1");
			DrawGammaSetMarkerTGraphAsym(graphInvSectionCombSysEta2760GeVPlot, markerStyleCommmonSpectrumpp,markerSizeSpectrum, kBlack , kBlack, widthLinesBoxes, kTRUE);//, colorComb1020-5);
			graphInvSectionCombSysEta2760GeVPlot->Draw("E2same");
		}
		legendInvYieldSectionPi0LHC11h_WitPP->Draw();
		labelPreliminary->Draw();
		labelDetSysInvYieldSectionPi0LHC11hwithPP->Draw();
		
		graphCombInvYieldSys2760GeVALHC11hScaled_0010->Draw("E2same");
		if(noXerrorBars) ProduceGraphAsymmWithoutXErrors(graphCombInvYieldStat2760GeVALHC11hScaled_0010);
		graphCombInvYieldStat2760GeVALHC11hScaled_0010->Draw("p,same,e1");	
	
	
		graphCombInvYieldSys2760GeVALHC11hColor_2050->Draw("E2same");
		if(noXerrorBars) ProduceGraphAsymmWithoutXErrors(graphCombInvYieldStat2760GeVALHC11hColor_2050);
		graphCombInvYieldStat2760GeVALHC11hColor_2050->Draw("p,same,e1");	
	


	canvasInvYieldSectionPi0LHC11h->Update();
	canvasInvYieldSectionPi0LHC11h->SaveAs(Form("%s/%s_YieldCombinedLHC11h_DataOnly_withPPandNLO.%s",outputDir.Data(),meson.Data(),suffix.Data()));
	canvasInvYieldSectionPi0LHC11h->SaveAs(Form("%s/%s_YieldCombinedLHC11h_DataOnly_withPPandNLO.%s",paperPlots.Data(),meson.Data(),suffix.Data()));

	

	
	canvasInvYieldSectionPi0LHC11h->cd();
// 	histo2DInvYieldSectionPi0LHC11h->DrawCopy();
		
		if(meson.CompareTo("Pi0")==0){
			histo2DInvYieldSectionPi0LHC11h = new TH2F("histo2DInvYieldSectionPi0LHC11h","histo2DInvYieldSectionPi0LHC11h",11000,0.23,60.,1000,1e-12,2e4);
			SetStyleHistoTH2ForGraphs(histo2DInvYieldSectionPi0LHC11h, "#it{p}_{T} (GeV/#it{c})","#frac{1}{2#pi #it{N}_{ev}} #frac{d^{2}#it{N}}{#it{p}_{T}d#it{p}_{T}d#it{y}} (GeV/#it{c})^{-2}",0.035,0.04, 0.035,0.04, 1.,1.45);
			histo2DInvYieldSectionPi0LHC11h->GetXaxis()->SetMoreLogLabels();
			histo2DInvYieldSectionPi0LHC11h->GetXaxis()->SetLabelOffset(-0.01);
			histo2DInvYieldSectionPi0LHC11h->Draw("copy");

		} else if(meson.CompareTo("Eta")==0){
			histo2DInvYieldSectionPi0LHC11h = new TH2F("histo2DInvYieldSectionPi0LHC11h","histo2DInvYieldSectionPi0LHC11h",11000,0.8,30.,1000,1e-12,1e3);
			SetStyleHistoTH2ForGraphs(histo2DInvYieldSectionPi0LHC11h, "#it{p}_{T} (GeV/#it{c})","#frac{1}{2#pi #it{N}_{ev}} #frac{d^{2}#it{N}}{#it{p}_{T}d#it{p}_{T}d#it{y}} (GeV/#it{c})^{-2} ",0.035,0.04, 0.035,0.039, 1.,1.47);
			histo2DInvYieldSectionPi0LHC11h->GetXaxis()->SetMoreLogLabels();
			histo2DInvYieldSectionPi0LHC11h->GetXaxis()->SetLabelOffset(-0.01);
			histo2DInvYieldSectionPi0LHC11h->Draw("copy");
	
		}

// 		Int_t textSizeLabelsPixelSpectra = 50;
// 		Double_t marginSpectra = 0.14*1200;
// 		Double_t textsizeLabelsSpectra = 0;
// 		Double_t textsizeFacSpectra = 0;
// 
// 		if (canvasInvYieldSectionPi0LHC11h->XtoPixel(canvasInvYieldSectionPi0LHC11h->GetX2()) < canvasInvYieldSectionPi0LHC11h->YtoPixel(canvasInvYieldSectionPi0LHC11h->GetY1())){
// 			textsizeLabelsSpectra = (Double_t)textSizeLabelsPixelSpectra/canvasInvYieldSectionPi0LHC11h->XtoPixel(canvasInvYieldSectionPi0LHC11h->GetX2()) ;
// 			textsizeFacSpectra = (Double_t)1./canvasInvYieldSectionPi0LHC11h->XtoPixel(canvasInvYieldSectionPi0LHC11h->GetX2()) ;
// 		} else {
// 			textsizeLabelsSpectra = (Double_t)textSizeLabelsPixelSpectra/canvasInvYieldSectionPi0LHC11h->YtoPixel(canvasInvYieldSectionPi0LHC11h->GetY1());
// 			textsizeFacSpectra = (Double_t)1./canvasInvYieldSectionPi0LHC11h->YtoPixel(canvasInvYieldSectionPi0LHC11h->GetY1());
// 		}

		TLegend* legendSpectraPP2 = new TLegend(0.53,0.8,0.95,0.87);
		legendSpectraPP2->SetFillColor(0);
		legendSpectraPP2->SetLineColor(0);
		legendSpectraPP2->SetTextFont(42);
		legendSpectraPP2->SetTextSize(FontSize);
// 		if(meson.CompareTo("Pi0")==0) legendSpectraPP->SetHeader("Eur.Phys.J. C(2014)74:3108");
// // 		else legendSpectraPP->SetHeader("");
// 		legendSpectraPP->SetTextSize(0.85*textsizeLabelsSpectra);
// 		legendSpectraPP->SetMargin(0.16);
// 		legendSpectraPP->SetTextFont(42);

		if(meson.CompareTo("Pi0")==0){
			
			DrawGammaSetMarkerTGraphAsym(graphInvSectionCombStatPi02760GeVPlot, markerStyleCommmonSpectrumpp,markerSizeSpectrum, kBlack , kBlack);
			graphInvSectionCombStatPi02760GeVPlot->Draw("p,same,e1");
			DrawGammaSetMarkerTGraphAsym(graphInvSectionCombSysPi02760GeVPlot, markerStyleCommmonSpectrumpp,markerSizeSpectrum, kBlack , kBlack, widthLinesBoxes, kTRUE);//, colorComb1020-5);
			graphInvSectionCombSysPi02760GeVPlot->Draw("E2same");
			
// 			graphNLOCalcDSS14InvYieldPi02760GeVScaledNcoll0010->Draw("l,same");
// 			graphNLOCalcDSS14InvYieldPi02760GeVScaledNcoll2050->Draw("l,same");

			legendSpectraPP2->SetHeader("Eur. Phys. J. C (2014) 74:3108");
// 			legendSpectraPP2->AddEntry((TObject*)0,"Eur.Phys.J. C (2014)","");
			legendSpectraPP2->AddEntry(graphInvSectionCombSysPi02760GeVPlot,collisionSystemPP2760GeV.Data(),"pf");
// 			legendSpectraPP2->AddEntry((TObject*)0,"22 April 2015","");
// 			legendSpectraPP2->AddEntry(graphNLOCalcDSS14InvYieldPi02760GeVScaledNcoll0010,"pQCD DSS14","l");

		} else if(meson.CompareTo("Eta")==0){

			DrawGammaSetMarkerTGraphAsym(graphInvSectionCombStatEta2760GeVPlot, markerStyleCommmonSpectrumpp,markerSizeSpectrum, kBlack , kBlack);
			graphInvSectionCombStatEta2760GeVPlot->Draw("p,same,e1");
			DrawGammaSetMarkerTGraphAsym(graphInvSectionCombSysEta2760GeVPlot, markerStyleCommmonSpectrumpp,markerSizeSpectrum, kBlack , kBlack, widthLinesBoxes, kTRUE);//, colorComb1020-5);
			graphInvSectionCombSysEta2760GeVPlot->Draw("E2same");
			
// // 			DrawGammaSetMarkerTGraphAsym(graphMtScaledEtaStat,24, 2, kGray+2, kGray+2);
// 			DrawGammaSetMarkerTGraphAsym(graphMtScaledEtaSys,24, 2, kGray+2, kGray+2);
// // 			graphMtScaledEtaStat->Draw("same");
// 			graphMtScaledEtaSys->Draw("psame");		

// 			graphNLOCalcDSS07InvYieldEta2760GeVScaledNcoll0010->Draw("l,same");
// 			graphNLOCalcDSS07InvYieldEta2760GeVScaledNcoll2050->Draw("l,same");

			
			legendSpectraPP2->SetHeader("J. Phys. G 38 (2011) 124076");
// 			legendSpectraPP2->AddEntry((TObject*)0,"QM2011 preliminary","");
			legendSpectraPP2->AddEntry(graphInvSectionCombSysEta2760GeVPlot,collisionSystemPP2760GeV.Data(),"pf");
// 			legendSpectraPP2->AddEntry(graphMtScaledEtaSys,"derived from #pi^{0} (pQCD)","pl");
// 			legendSpectraPP2->AddEntry(graphNLOCalcDSS07InvYieldEta2760GeVScaledNcoll0010,"pQCD DSS07","l");

		}
		
		TheoryCracowLowPt_0010->Draw("l,same");
		TheoryCracowLowPt_2050->Draw("l,same");

		DrawGammaSetMarker(histoEPOSRebin_0010,1,2,colorEPOS0010,colorEPOS0010);
		DrawGammaSetMarker(histoEPOSRebin_2050,1,2,colorEPOS2050,colorEPOS2050);

		histoEPOSRebin_0010->Draw("same,c,histo");
		histoEPOSRebin_2050->Draw("same,c,histo");

		legendSpectraPP2->Draw();

		TLegend* legendInvYieldSectionPi0LHC11h_WitPPAndModels = new TLegend(0.17,0.32,0.5,0.42);
		legendInvYieldSectionPi0LHC11h_WitPPAndModels->SetFillColor(0);
		legendInvYieldSectionPi0LHC11h_WitPPAndModels->SetLineColor(0);
		legendInvYieldSectionPi0LHC11h_WitPPAndModels->SetTextFont(42);
		legendInvYieldSectionPi0LHC11h_WitPPAndModels->SetTextSize(FontSize);
		legendInvYieldSectionPi0LHC11h_WitPPAndModels->SetHeader("Phys.Rev. C90, 014906 (2014)");
		legendInvYieldSectionPi0LHC11h_WitPPAndModels->AddEntry(TheoryCracowLowPt_0010,"NEQ SHM 0-10%", "l");
		legendInvYieldSectionPi0LHC11h_WitPPAndModels->AddEntry(TheoryCracowLowPt_2050,"NEQ SHM 20-50%", "l");
		TLegend* legendInvYieldSectionPi0LHC11h_WitPPAndModels2 = new TLegend(0.17,0.22,0.5,0.32);
		legendInvYieldSectionPi0LHC11h_WitPPAndModels2->SetFillColor(0);
		legendInvYieldSectionPi0LHC11h_WitPPAndModels2->SetLineColor(0);
		legendInvYieldSectionPi0LHC11h_WitPPAndModels2->SetTextFont(42);
		legendInvYieldSectionPi0LHC11h_WitPPAndModels2->SetTextSize(FontSize);
		legendInvYieldSectionPi0LHC11h_WitPPAndModels2->SetHeader("Phys.Rev. C89, 064903 (2014)");
		legendInvYieldSectionPi0LHC11h_WitPPAndModels2->AddEntry(histoEPOSRebin_0010,"EPOS 0-10%", "l");
		legendInvYieldSectionPi0LHC11h_WitPPAndModels2->AddEntry(histoEPOSRebin_2050,"EPOS 20-50%", "l");
// 		legendInvYieldSectionPi0LHC11h_WitPPAndModels2->AddEntry(graphCombInvYieldSys2760GeVALHC11hScaled_0010,Form("%s %s x 2^{2}",cent0010.Data(),collisionSystem2760GeV.Data()),"fp");
// 		legendInvYieldSectionPi0LHC11h_WitPPAndModels2->AddEntry(graphCombInvYieldSys2760GeVALHC11hColor_2050,Form("%s %s",cent2050.Data(),collisionSystem2760GeV.Data()),"fp");
		legendInvYieldSectionPi0LHC11h_WitPPAndModels->Draw();
		legendInvYieldSectionPi0LHC11h_WitPPAndModels2->Draw();
// 		legtheory->Draw("same");
// 		legtheory2->Draw("same");
		legendInvYieldSectionPi0LHC11h_WitPP->Draw();
		labelPreliminary->Draw();
		labelDetSysInvYieldSectionPi0LHC11hwithPP->Draw();
		
		graphCombInvYieldSys2760GeVALHC11hScaled_0010->Draw("E2same");
		if(noXerrorBars) ProduceGraphAsymmWithoutXErrors(graphCombInvYieldStat2760GeVALHC11hScaled_0010);
		graphCombInvYieldStat2760GeVALHC11hScaled_0010->Draw("p,same,e1");	
	
		graphCombInvYieldSys2760GeVALHC11hColor_2050->Draw("E2same");
		if(noXerrorBars) ProduceGraphAsymmWithoutXErrors(graphCombInvYieldStat2760GeVALHC11hColor_2050);
		graphCombInvYieldStat2760GeVALHC11hColor_2050->Draw("p,same,e1");	

	canvasInvYieldSectionPi0LHC11h->Update();
	canvasInvYieldSectionPi0LHC11h->SaveAs(Form("%s/%s_YieldCombinedLHC11h_DataWithModels_withPP.%s",outputDir.Data(),meson.Data(),suffix.Data()));
	canvasInvYieldSectionPi0LHC11h->SaveAs(Form("%s/%s_YieldCombinedLHC11h_DataWithModels_withPP.%s",paperPlots.Data(),meson.Data(),suffix.Data()));
	
	
	
	
	//*********************************************************************************************************************//
	//*************************	 Combination of RAA 	*******************************************************************//
	
	cout << " \n\nCalculating RAA for " << meson.Data() << endl;		
	TGraphAsymmErrors* graphCombRAAStat2760GeVLHC11h_0010 = NULL;
	TGraphAsymmErrors* graphCombRAASys2760GeVLHC11h_0010 = NULL;
	TGraphAsymmErrors* graphCombRAATot2760GeVLHC11h_0010 = NULL;

	TGraphAsymmErrors* graphCombRAAStat2760GeVLHC11h_2050 = NULL;
	TGraphAsymmErrors* graphCombRAASys2760GeVLHC11h_2050 = NULL;
	TGraphAsymmErrors* graphCombRAATot2760GeVLHC11h_2050 = NULL;
	
	if(meson.CompareTo("Pi0")==0){
		graphCombRAATot2760GeVLHC11h_0010 = CombinePtPointsRAA(graphPCMPi0RAAStat2760GeV_0010,	 graphPCMPi0RAASys2760GeV_0010, 	
																graphEMCalPi0RAAStatPbPb2760GeV_0010, graphEMCalPi0RAASysPbPb2760GeV_0010,								graphCombRAAStat2760GeVLHC11h_0010, graphCombRAASys2760GeVLHC11h_0010,
																xPtLimitsPi0, 24, 0, 1, 16, kFALSE);

		graphCombRAATot2760GeVLHC11h_2050 = CombinePtPointsRAA(graphPCMPi0RAAStat2760GeV_2050,	 graphPCMPi0RAASys2760GeV_2050, 	
																graphEMCalPi0RAAStatPbPb2760GeV_2050, graphEMCalPi0RAASysPbPb2760GeV_2050,								graphCombRAAStat2760GeVLHC11h_2050, graphCombRAASys2760GeVLHC11h_2050,
																xPtLimitsPi0, 24, 0, 1, 16, kFALSE);
	
	} else if(meson.CompareTo("Eta")==0){
		
		graphCombRAATot2760GeVLHC11h_0010 = CombinePtPointsRAA(graphPCMEtaRAAStat2760GeV_0010,	 graphPCMEtaRAASys2760GeV_0010, 	
																graphEMCalEtaRAAStatPbPb2760GeV_0010, graphEMCalEtaRAASysPbPb2760GeV_0010,								graphCombRAAStat2760GeVLHC11h_0010, graphCombRAASys2760GeVLHC11h_0010,
																xPtLimitsEta, 14, 0, 2, 6, kFALSE);

		graphCombRAATot2760GeVLHC11h_2050 = CombinePtPointsRAA(graphPCMEtaRAAStat2760GeV_2050,	 graphPCMEtaRAASys2760GeV_2050, 	
																graphEMCalEtaRAAStatPbPb2760GeV_2050, graphEMCalEtaRAASysPbPb2760GeV_2050,								graphCombRAAStat2760GeVLHC11h_2050, graphCombRAASys2760GeVLHC11h_2050,
																xPtLimitsEta, 14, 0, 2, 6, kFALSE);
		
	}

// 		cout << "here" << endl;
// 		graphCombRAASys2760GeVLHC11h_2050->Print();
// 		cout << "here" << endl;
// 		graphCombRAAStat2760GeVLHC11h_2050->Print();
// 		cout << "here" << endl;
// 		graphCombRAASys2760GeVLHC11h_0010->Print();
// 		cout << "here" << endl;
// 		graphCombRAAStat2760GeVLHC11h_0010->Print();

		if(PaperPi0 && meson.CompareTo("Pi0")==0){
			graphCombRAAStat2760GeVLHC11h_0010->RemovePoint(0);
			graphCombRAASys2760GeVLHC11h_0010->RemovePoint(0);

			graphCombRAAStat2760GeVLHC11h_0010->RemovePoint(0);
			graphCombRAASys2760GeVLHC11h_0010->RemovePoint(0);

			graphCombRAAStat2760GeVLHC11h_0010->RemovePoint(0);
			graphCombRAASys2760GeVLHC11h_0010->RemovePoint(0);

			graphCombRAASys2760GeVLHC11h_2050->RemovePoint(0);
			graphCombRAAStat2760GeVLHC11h_2050->RemovePoint(0);

			graphCombRAASys2760GeVLHC11h_2050->RemovePoint(0);
			graphCombRAAStat2760GeVLHC11h_2050->RemovePoint(0);
			
			graphCombRAASys2760GeVLHC11h_2050->RemovePoint(0);
			graphCombRAAStat2760GeVLHC11h_2050->RemovePoint(0);

		}

	TCanvas* canvasRAAcomboPi0andEta = new TCanvas("canvasRAAcomboPi0andEta","",200,10,1200,1100);  //200,10,1350,900);  // gives the page size
		DrawGammaCanvasSettings( canvasRAAcomboPi0andEta, 0.08, 0.02, 0.035, 0.09);
// 		canvasRAAcomboPi0andEta->SetLogx();
	
		TH2F * histo2DRAAcomboPi0andEta;
		histo2DRAAcomboPi0andEta = new TH2F("histo2DRAAcomboPi0andEta","histo2DRAAcomboPi0andEta",11000,0.23,70.,1000,-0.5,2.);
		SetStyleHistoTH2ForGraphs(histo2DRAAcomboPi0andEta, "#it{p}_{T} (GeV/#it{c})","#it{R}_{AA}",0.035,0.04, 0.035,0.04, 1.,.8);
// 		histo2DRAAcomboPi0andEta->GetXaxis()->SetMoreLogLabels();	
// 		histo2DRAAcomboPi0andEta->GetXaxis()->SetLabelOffset(-0.01);
		histo2DRAAcomboPi0andEta->GetYaxis()->SetRangeUser(0.,1.4);
		histo2DRAAcomboPi0andEta->GetXaxis()->SetRangeUser(0.,21);
		histo2DRAAcomboPi0andEta->Draw("copy");


		TGraphAsymmErrors* graphCombRAAStat2760GeVLHC11hPi0_0010 = NULL;
		TGraphAsymmErrors* graphCombRAASys2760GeVLHC11hPi0_0010 = NULL;
		TGraphAsymmErrors* graphCombRAATot2760GeVLHC11hPi0_0010 = NULL;

		TGraphAsymmErrors* graphCombRAAStat2760GeVLHC11hPi0_2050 = NULL;
		TGraphAsymmErrors* graphCombRAASys2760GeVLHC11hPi0_2050 = NULL;
		TGraphAsymmErrors* graphCombRAATot2760GeVLHC11hPi0_2050 = NULL;

		TGraphAsymmErrors* graphCombRAAStat2760GeVLHC11hEta_0010 = NULL;
		TGraphAsymmErrors* graphCombRAASys2760GeVLHC11hEta_0010 = NULL;
		TGraphAsymmErrors* graphCombRAATot2760GeVLHC11hEta_0010 = NULL;

		TGraphAsymmErrors* graphCombRAAStat2760GeVLHC11hEta_2050 = NULL;
		TGraphAsymmErrors* graphCombRAASys2760GeVLHC11hEta_2050 = NULL;
		TGraphAsymmErrors* graphCombRAATot2760GeVLHC11hEta_2050 = NULL;
		
		graphCombRAATot2760GeVLHC11hPi0_0010 = CombinePtPointsRAA(graphPCMPi0RAAStat2760GeV_0010,	 graphPCMPi0RAASys2760GeV_0010, 	
																	graphEMCalPi0RAAStatPbPb2760GeV_0010, graphEMCalPi0RAASysPbPb2760GeV_0010,								graphCombRAAStat2760GeVLHC11hPi0_0010, graphCombRAASys2760GeVLHC11hPi0_0010,
																	xPtLimitsPi0, 24, 0, 1, 16, kFALSE);

		graphCombRAATot2760GeVLHC11hPi0_2050 = CombinePtPointsRAA(graphPCMPi0RAAStat2760GeV_2050,	 graphPCMPi0RAASys2760GeV_2050, 	
																	graphEMCalPi0RAAStatPbPb2760GeV_2050, graphEMCalPi0RAASysPbPb2760GeV_2050,								graphCombRAAStat2760GeVLHC11hPi0_2050, graphCombRAASys2760GeVLHC11hPi0_2050,
																	xPtLimitsPi0, 24, 0, 1, 16, kFALSE);
		
		graphCombRAATot2760GeVLHC11hEta_0010 = CombinePtPointsRAA(graphPCMEtaRAAStat2760GeV_0010,	 graphPCMEtaRAASys2760GeV_0010, 	
																	graphEMCalEtaRAAStatPbPb2760GeV_0010, graphEMCalEtaRAASysPbPb2760GeV_0010,								graphCombRAAStat2760GeVLHC11hEta_0010, graphCombRAASys2760GeVLHC11hEta_0010,
																	xPtLimitsEta, 14, 0, 2, 6, kFALSE);

		graphCombRAATot2760GeVLHC11hEta_2050 = CombinePtPointsRAA(graphPCMEtaRAAStat2760GeV_2050,	 graphPCMEtaRAASys2760GeV_2050, 	
																	graphEMCalEtaRAAStatPbPb2760GeV_2050, graphEMCalEtaRAASysPbPb2760GeV_2050,								graphCombRAAStat2760GeVLHC11hEta_2050, graphCombRAASys2760GeVLHC11hEta_2050,
																	xPtLimitsEta, 14, 0, 2, 6, kFALSE);

		if(PaperPi0 && meson.CompareTo("Pi0")==0){
			graphCombRAAStat2760GeVLHC11hPi0_0010->RemovePoint(0);
			graphCombRAASys2760GeVLHC11hPi0_0010->RemovePoint(0);

			graphCombRAAStat2760GeVLHC11hPi0_0010->RemovePoint(0);
			graphCombRAASys2760GeVLHC11hPi0_0010->RemovePoint(0);

			graphCombRAAStat2760GeVLHC11hPi0_0010->RemovePoint(0);
			graphCombRAASys2760GeVLHC11hPi0_0010->RemovePoint(0);

			graphCombRAAStat2760GeVLHC11hPi0_2050->RemovePoint(0);
			graphCombRAASys2760GeVLHC11hPi0_2050->RemovePoint(0);

			graphCombRAAStat2760GeVLHC11hPi0_2050->RemovePoint(0);
			graphCombRAASys2760GeVLHC11hPi0_2050->RemovePoint(0);
			
			graphCombRAAStat2760GeVLHC11hPi0_2050->RemovePoint(0);
			graphCombRAASys2760GeVLHC11hPi0_2050->RemovePoint(0);

		}

		
		//=============Combined Pi0
		DrawGammaSetMarkerTGraphAsym(graphCombRAASys2760GeVLHC11hPi0_0010, markerStyleComb, markerSizeComb, colorPCM0010 , colorPCM0010, widthLinesBoxes, kTRUE);
		graphCombRAASys2760GeVLHC11hPi0_0010->Draw("E2same");
		DrawGammaSetMarkerTGraphAsym(graphCombRAAStat2760GeVLHC11hPi0_0010, markerStyleComb, markerSizeComb, colorPCM0010 , colorPCM0010);
		graphCombRAAStat2760GeVLHC11hPi0_0010->Draw("p,same,e1");


		//=============Combined Eta
		DrawGammaSetMarkerTGraphAsym(graphCombRAASys2760GeVLHC11hEta_0010, markerStyleComb, markerSizeComb, colorEMCal0010, colorEMCal0010, widthLinesBoxes, kTRUE);
		graphCombRAASys2760GeVLHC11hEta_0010->Draw("E2same");
		DrawGammaSetMarkerTGraphAsym(graphCombRAAStat2760GeVLHC11hEta_0010, markerStyleComb, markerSizeComb, colorEMCal0010 , colorEMCal0010);
		graphCombRAAStat2760GeVLHC11hEta_0010->Draw("p,same,e1");

		TLegend* legendRAAcomboPi0andEta0010 = new TLegend(0.3,0.66,0.6,0.9);
		legendRAAcomboPi0andEta0010->SetFillColor(0);
		legendRAAcomboPi0andEta0010->SetLineColor(0);
		legendRAAcomboPi0andEta0010->SetTextFont(42);
		legendRAAcomboPi0andEta0010->SetTextSize(0.038);
		legendRAAcomboPi0andEta0010->SetHeader(Form("%s",collisionSystemPbPb0010.Data()));
		legendRAAcomboPi0andEta0010->AddEntry(graphCombRAASys2760GeVLHC11hPi0_0010,"#pi^{0}","pf");
		legendRAAcomboPi0andEta0010->AddEntry(graphCombRAASys2760GeVLHC11hEta_0010,"#eta","fp");
		legendRAAcomboPi0andEta0010->Draw();

		boxErrorNorm0010Only->Draw();
	canvasRAAcomboPi0andEta->SaveAs(Form("%s/RAA_combinedPi0andEta_0010.%s",outputDir.Data(),suffix.Data()));
	canvasRAAcomboPi0andEta->SaveAs(Form("%s/RAA_combinedPi0andEta_0010.%s",paperPlots.Data(),suffix.Data()));

	
	canvasRAAcomboPi0andEta->cd();
	histo2DRAAcomboPi0andEta->Draw("copy");
	
		DrawGammaSetMarkerTGraphAsym(graphCombRAASys2760GeVLHC11hPi0_2050, markerStyleComb, markerSizeComb, colorPCM2050, colorPCM2050, widthLinesBoxes, kTRUE);
		graphCombRAASys2760GeVLHC11hPi0_2050->Draw("E2same");
		DrawGammaSetMarkerTGraphAsym(graphCombRAAStat2760GeVLHC11hPi0_2050, markerStyleComb, markerSizeComb, colorPCM2050 , colorPCM2050);
		graphCombRAAStat2760GeVLHC11hPi0_2050->Draw("p,same,e1");

		DrawGammaSetMarkerTGraphAsym(graphCombRAASys2760GeVLHC11hEta_2050, markerStyleComb, markerSizeComb, colorEMCal2050, colorEMCal2050, widthLinesBoxes, kTRUE);
		graphCombRAASys2760GeVLHC11hEta_2050->Draw("E2same");
		DrawGammaSetMarkerTGraphAsym(graphCombRAAStat2760GeVLHC11hEta_2050, markerStyleComb, markerSizeComb, colorEMCal2050 , colorEMCal2050);
		graphCombRAAStat2760GeVLHC11hEta_2050->Draw("p,same,e1");
		
		
		TLegend* legendRAAcomboPi0andEta2050 = new TLegend(0.3,0.66,0.6,0.9);
		legendRAAcomboPi0andEta2050->SetFillColor(0);
		legendRAAcomboPi0andEta2050->SetLineColor(0);
		legendRAAcomboPi0andEta2050->SetTextFont(42);
		legendRAAcomboPi0andEta2050->SetTextSize(0.038);
		legendRAAcomboPi0andEta2050->SetHeader(Form("%s",collisionSystemPbPb2050.Data()));
		legendRAAcomboPi0andEta2050->AddEntry(graphCombRAASys2760GeVLHC11hPi0_2050,"#pi^{0}","pf");
		legendRAAcomboPi0andEta2050->AddEntry(graphCombRAASys2760GeVLHC11hEta_2050,"#eta","fp");
		legendRAAcomboPi0andEta2050->Draw();

		boxErrorNorm2050Only->Draw();
	canvasRAAcomboPi0andEta->SaveAs(Form("%s/RAA_combinedPi0andEta_2050.%s",outputDir.Data(),suffix.Data()));
	canvasRAAcomboPi0andEta->SaveAs(Form("%s/RAA_combinedPi0andEta_2050.%s",paperPlots.Data(),suffix.Data()));

	
	TGraphAsymmErrors* graphRAAStatPi0Copy_0010 	= (TGraphAsymmErrors*) graphCombRAAStat2760GeVLHC11hPi0_0010->Clone("graphRAAStatPi0Copy_0010");
	TGraphAsymmErrors* graphRAASysPi0Copy_0010 		= (TGraphAsymmErrors*) graphCombRAASys2760GeVLHC11hPi0_0010->Clone("graphRAASysPi0Copy_0010");
	TGraphAsymmErrors* graphRAAStatEtaCopy_0010 	= (TGraphAsymmErrors*) graphCombRAAStat2760GeVLHC11hEta_0010->Clone("graphRAAStatEtaCopy_0010");
	TGraphAsymmErrors* graphRAASysEtaCopy_0010 		= (TGraphAsymmErrors*) graphCombRAASys2760GeVLHC11hEta_0010->Clone("graphRAASysEtaCopy_0010");

	TGraphErrors* graphratioRAAStatEta_0010 	= NULL;
	TGraphErrors* graphratioRAASysEta_0010 	= NULL;
	TGraphErrors* graphratioRAAStatPi0_0010 	= NULL;
	TGraphErrors* graphratioRAASysPi0_0010 	= NULL;
	
	TGraphErrors* graphratioRAAEtaToPi0_0010 = CalculateRatioBetweenSpectraWithDifferentBinning(graphRAAStatEtaCopy_0010, graphRAASysEtaCopy_0010, 
																										  graphRAAStatPi0Copy_0010, graphRAASysPi0Copy_0010, 
																									      kFALSE,  kFALSE, 
																									      &graphratioRAAStatEta_0010, &graphratioRAASysEta_0010, 
																									      &graphratioRAAStatPi0_0010, &graphratioRAASysPi0_0010);
	graphratioRAAEtaToPi0_0010->Print();
	
	TGraphAsymmErrors* graphRAAStatPi0Copy_2050 	= (TGraphAsymmErrors*) graphCombRAAStat2760GeVLHC11hPi0_2050->Clone("graphRAAStatPi0Copy_2050");
	TGraphAsymmErrors* graphRAASysPi0Copy_2050 		= (TGraphAsymmErrors*) graphCombRAASys2760GeVLHC11hPi0_2050->Clone("graphRAASysPi0Copy_2050");
	TGraphAsymmErrors* graphRAAStatEtaCopy_2050 	= (TGraphAsymmErrors*) graphCombRAAStat2760GeVLHC11hEta_2050->Clone("graphRAAStatEtaCopy_2050");
	TGraphAsymmErrors* graphRAASysEtaCopy_2050 		= (TGraphAsymmErrors*) graphCombRAASys2760GeVLHC11hEta_2050->Clone("graphRAASysEtaCopy_2050");

	TGraphErrors* graphratioRAAStatEta_2050 	= NULL;
	TGraphErrors* graphratioRAASysEta_2050 	= NULL;
	TGraphErrors* graphratioRAAStatPi0_2050 	= NULL;
	TGraphErrors* graphratioRAASysPi0_2050 	= NULL;

	TGraphErrors* graphratioRAAEtaToPi0_2050 = CalculateRatioBetweenSpectraWithDifferentBinning(graphRAAStatEtaCopy_2050, graphRAASysEtaCopy_2050, 
																										  graphRAAStatPi0Copy_2050, graphRAASysPi0Copy_2050, 
																									      kFALSE,  kFALSE, 
																									      &graphratioRAAStatEta_2050, &graphratioRAASysEta_2050, 
																									      &graphratioRAAStatPi0_2050, &graphratioRAASysPi0_2050);
	graphratioRAAEtaToPi0_2050->Print();
	
	
	Double_t arrayBoundariesX1_4[3];
	Double_t arrayBoundariesY1_4[2];
	Double_t relativeMarginsX[3];
	Double_t relativeMarginsY[3];
	ReturnCorrectValuesForCanvasScaling(1000,500, 2, 1,0.06, 0.005, 0.005,0.09,arrayBoundariesX1_4,arrayBoundariesY1_4,relativeMarginsX,relativeMarginsY);

	TCanvas* canvasRatioRAAEtaToPi0 = new TCanvas("canvasRatioRAAEtaToPi0","",0,0,1000,500);  // gives the page size
		DrawGammaCanvasSettings( canvasRatioRAAEtaToPi0,  0.13, 0.02, 0.03, 0.06);

		TPad* pad6PartCompChargedPionsLHC11h1 = new TPad("pad6PartCompChargedPionsLHC11h1", "", arrayBoundariesX1_4[0], arrayBoundariesY1_4[1], arrayBoundariesX1_4[1], arrayBoundariesY1_4[0],-1, -1, -2);
		DrawGammaPadSettings( pad6PartCompChargedPionsLHC11h1, relativeMarginsX[0], relativeMarginsX[1], relativeMarginsY[0], relativeMarginsY[2]);
		pad6PartCompChargedPionsLHC11h1->Draw();
		TPad* pad6PartCompChargedPionsLHC11h3 = new TPad("pad6PartCompChargedPionsLHC11h3", "", arrayBoundariesX1_4[1], arrayBoundariesY1_4[1], arrayBoundariesX1_4[2], arrayBoundariesY1_4[0],-1, -1, -2);
		DrawGammaPadSettings( pad6PartCompChargedPionsLHC11h3, relativeMarginsX[1], relativeMarginsX[2], relativeMarginsY[0], relativeMarginsY[2]);
		pad6PartCompChargedPionsLHC11h3->Draw();

		Double_t margin = relativeMarginsX[0]*0.8*1000;
		Double_t textsizeLabels1 = 0;
		Double_t textsizeFac1 = 0;
		Double_t textsizeLabels2 = 0;
		Double_t textsizeFac2 = 0;

		ReturnCorrectValuesTextSize(pad6PartCompChargedPionsLHC11h1,textsizeLabels1, textsizeFac1, 22, margin);
		ReturnCorrectValuesTextSize(pad6PartCompChargedPionsLHC11h3,textsizeLabels2, textsizeFac2, 22, margin);

		TH2F * histo2DCompCombinedRatioLHC11h2;
		histo2DCompCombinedRatioLHC11h2 = new TH2F("histo2DCompCombinedRatioLHC11h2","histo2DCompCombinedRatioLHC11h2",1000,0.3,40.,1000,0.2,4.	);
		SetStyleHistoTH2ForGraphs(histo2DCompCombinedRatioLHC11h2, "#it{p}_{T} (GeV/#it{c})","#eta #it{R}_{AA} / #pi^{0} #it{R}_{AA}",0.85*textsizeLabels1, textsizeLabels1,
									0.85*textsizeLabels1, textsizeLabels1, 0.8,0.2/(textsizeFac1*margin), 512, 505);
		histo2DCompCombinedRatioLHC11h2->GetYaxis()->SetRangeUser(0.,2.1);
		histo2DCompCombinedRatioLHC11h2->GetXaxis()->SetRangeUser(0.,20.);
		histo2DCompCombinedRatioLHC11h2->GetXaxis()->SetLabelOffset(-0.0105);
	
		TH2F* histo2DCompCombinedRatioLHC11h;
		histo2DCompCombinedRatioLHC11h = new TH2F("histo2DCompCombinedRatioLHC11h","histo2DCompCombinedRatioLHC11h",1000,0.3,40.,1000,0.2,4.	);
		SetStyleHistoTH2ForGraphs(histo2DCompCombinedRatioLHC11h, "#it{p}_{T} (GeV/#it{c})","#frac{ #eta #it{R}_{AA}}{ #pi^{0} #it{R}_{AA}}", 0.85*textsizeLabels2, textsizeLabels2,
									0.85*textsizeLabels2, textsizeLabels2, 0.8,0.25/(textsizeFac2*margin), 512, 505);
		histo2DCompCombinedRatioLHC11h->GetXaxis()->SetLabelOffset(-0.0105);
		histo2DCompCombinedRatioLHC11h->GetYaxis()->SetRangeUser(0.6,2.1);
		histo2DCompCombinedRatioLHC11h->GetXaxis()->SetRangeUser(.0,20.);

		pad6PartCompChargedPionsLHC11h1->cd();
		pad6PartCompChargedPionsLHC11h1->SetLogx();
		histo2DCompCombinedRatioLHC11h2->GetXaxis()->SetRangeUser(0.,30.);
		histo2DCompCombinedRatioLHC11h2->GetYaxis()->SetRangeUser(0.,2.1);
		histo2DCompCombinedRatioLHC11h2->DrawCopy();

		DrawGammaSetMarkerTGraphErr(graphratioRAAEtaToPi0_0010, markerStyleComb, markerSizeComb, colorCombo0010 , colorCombo0010);
		graphratioRAAEtaToPi0_0010->Draw("E1psame");

		TLatex *labelPi0CompChargedPionsPbPb0010 = new TLatex(0.16,0.9,collisionSystemPbPb0010.Data());
		SetStyleTLatex( labelPi0CompChargedPionsPbPb0010, 0.85*textsizeLabels1,4);
		labelPi0CompChargedPionsPbPb0010->Draw(); 
		DrawGammaLines(0., 19.5 , 1, 1 ,1, kGray, 2);

		TLegend* legendPi0CompChargedPionsPbPb0010 = new TLegend(0.12,0.68,0.95,0.88);
		legendPi0CompChargedPionsPbPb0010->SetFillColor(0);
		legendPi0CompChargedPionsPbPb0010->SetLineColor(0);
		legendPi0CompChargedPionsPbPb0010->SetNColumns(2);
		legendPi0CompChargedPionsPbPb0010->SetTextSize(0.85*textsizeLabels1);
		legendPi0CompChargedPionsPbPb0010->AddEntry(graphratioRAAEtaToPi0_0010,"0-10% #frac{ #eta #it{R}_{AA}}{ #pi^{0} #it{R}_{AA}}","p");
		legendPi0CompChargedPionsPbPb0010->AddEntry(graphratioRAAEtaToPi0_2050,"20-50% #frac{ #eta #it{R}_{AA}}{ #pi^{0} #it{R}_{AA}}","p");
// 		legendPi0CompChargedPionsPbPb0010->Draw();
		DrawGammaLines(0., 20.5 , 1, 1 ,1,kGray, 2);
	
		histo2DCompCombinedRatioLHC11h2->Draw("axis,same");
		pad6PartCompChargedPionsLHC11h1->Update();
		pad6PartCompChargedPionsLHC11h3->cd();
		pad6PartCompChargedPionsLHC11h3->SetLogx();
		histo2DCompCombinedRatioLHC11h->GetXaxis()->SetRangeUser(0.,30.);
		histo2DCompCombinedRatioLHC11h->GetYaxis()->SetRangeUser(0.,2.1);
		histo2DCompCombinedRatioLHC11h->DrawCopy();
			
		DrawGammaSetMarkerTGraphErr(graphratioRAAEtaToPi0_2050,markerStyleComb, markerSizeComb, colorCombo2050, colorCombo2050);
		graphratioRAAEtaToPi0_2050->Draw("E1psame");

		TLatex *labelPi0CompChargedPionsLHC11hPbPb2040 = new TLatex(0.16-relativeMarginsX[0],0.9,collisionSystemPbPb2050.Data());
		SetStyleTLatex( labelPi0CompChargedPionsLHC11hPbPb2040, 0.85*textsizeLabels2,4);
		labelPi0CompChargedPionsLHC11hPbPb2040->Draw();
		DrawGammaLines(0., 19.5 , 1, 1 ,1, kGray, 2);	

		
		histo2DCompCombinedRatioLHC11h->Draw("axis,same");
		pad6PartCompChargedPionsLHC11h3->Update();

	canvasRatioRAAEtaToPi0->Update();	
	canvasRatioRAAEtaToPi0->SaveAs(Form("%s/RAAratioEtaAndPi0_LHC11h.%s",outputDir.Data(),suffix.Data()));
// 	canvasRatioRAAEtaToPi0->SaveAs(Form("%s/RAAratioEtaAndPi0_LHC11h.%s",paperPlots.Data(),suffix.Data()));
	delete pad6PartCompChargedPionsLHC11h1;	
	delete pad6PartCompChargedPionsLHC11h3;	
	delete canvasRatioRAAEtaToPi0;
	
	
	TCanvas* canvasRAAcombo = new TCanvas("canvasRAAcombo","",200,10,1200,1100);  //200,10,1350,900);  // gives the page size
		DrawGammaCanvasSettings( canvasRAAcombo, 0.08, 0.02, 0.035, 0.09);
// 		canvasRAAcombo->SetLogx();
	
		TH2F * histo2DRAAcombo;
		histo2DRAAcombo = new TH2F("histo2DRAAcombo","histo2DRAAcombo",11000,0.23,70.,1000,-0.5,2.);
		SetStyleHistoTH2ForGraphs(histo2DRAAcombo, "#it{p}_{T} (GeV/#it{c})","#it{R}_{AA}",0.035,0.04, 0.035,0.04, 1.,.9);
// 		histo2DRAAcombo->GetXaxis()->SetMoreLogLabels();	
// 		histo2DRAAcombo->GetXaxis()->SetLabelOffset(-0.01);
		histo2DRAAcombo->GetYaxis()->SetRangeUser(0.,1.4);
		histo2DRAAcombo->GetXaxis()->SetRangeUser(0.,21);
		histo2DRAAcombo->Draw("copy");
		
		if(meson.CompareTo("Pi0")==0){
			
			//=============PCM 		
			DrawGammaSetMarkerTGraphAsym(graphPCMPi0RAASys2760GeV_0010, markerStyleDet[0], markerSizeDet[0]*0.75, colorPCM0010, colorPCM0010, widthLinesBoxes, kTRUE);
			graphPCMPi0RAASys2760GeV_0010->Draw("E2same");
			DrawGammaSetMarkerTGraphAsym(graphPCMPi0RAAStat2760GeV_0010,markerStyleDet[0], markerSizeDet[0]*0.75, colorPCM0010, colorPCM0010);
			graphPCMPi0RAAStat2760GeV_0010->Draw("p,same,e1");		

			DrawGammaSetMarkerTGraphAsym(graphPCMPi0RAASys2760GeV_2050, markerStyleDet[0], markerSizeDet[0]*0.75, colorPCM2050, colorPCM2050, widthLinesBoxes, kTRUE);
			graphPCMPi0RAASys2760GeV_2050->Draw("E2same");
			DrawGammaSetMarkerTGraphAsym(graphPCMPi0RAAStat2760GeV_2050,markerStyleDet[0], markerSizeDet[0]*0.75, colorPCM2050, colorPCM2050);
			graphPCMPi0RAAStat2760GeV_2050->Draw("p,same,e1");		
			
			
			//=============EMCal
			DrawGammaSetMarkerTGraphAsym(graphEMCalPi0RAASysPbPb2760GeV_0010, markerStyleDet[2], markerSizeDet[2]*0.75, colorEMCal0010 , colorEMCal0010, widthLinesBoxes, kTRUE);
			graphEMCalPi0RAASysPbPb2760GeV_0010->Draw("E2same");			
			DrawGammaSetMarkerTGraphAsym(graphEMCalPi0RAAStatPbPb2760GeV_0010, markerStyleDet[2], markerSizeDet[2]*0.75, colorEMCal0010 , colorEMCal0010);
			graphEMCalPi0RAAStatPbPb2760GeV_0010->Draw("p,same,e1");

			DrawGammaSetMarkerTGraphAsym(graphEMCalPi0RAASysPbPb2760GeV_2050, markerStyleDet[2], markerSizeDet[2]*0.75, colorEMCal2050 , colorEMCal2050, widthLinesBoxes, kTRUE);
			graphEMCalPi0RAASysPbPb2760GeV_2050->Draw("E2same");			
			DrawGammaSetMarkerTGraphAsym(graphEMCalPi0RAAStatPbPb2760GeV_2050, markerStyleDet[2], markerSizeDet[2]*0.75, colorEMCal2050 , colorEMCal2050);
			graphEMCalPi0RAAStatPbPb2760GeV_2050->Draw("p,same,e1");
			
		} else if(meson.CompareTo("Eta")==0){
			
			//=============PCM 		
			DrawGammaSetMarkerTGraphAsym(graphPCMEtaRAASys2760GeV_0010, markerStyleDet[0], markerSizeDet[0]*0.75, colorPCM0010, colorPCM0010, widthLinesBoxes, kTRUE);
			graphPCMEtaRAASys2760GeV_0010->Draw("E2same");
			DrawGammaSetMarkerTGraphAsym(graphPCMEtaRAAStat2760GeV_0010,markerStyleDet[0], markerSizeDet[0]*0.75, colorPCM0010, colorPCM0010);
			graphPCMEtaRAAStat2760GeV_0010->Draw("p,same,e1");		

			DrawGammaSetMarkerTGraphAsym(graphPCMEtaRAASys2760GeV_2050, markerStyleDet[0], markerSizeDet[0]*0.75, colorPCM2050, colorPCM2050, widthLinesBoxes, kTRUE);
			graphPCMEtaRAASys2760GeV_2050->Draw("E2same");
			DrawGammaSetMarkerTGraphAsym(graphPCMEtaRAAStat2760GeV_2050,markerStyleDet[0], markerSizeDet[0]*0.75, colorPCM2050, colorPCM2050);
			graphPCMEtaRAAStat2760GeV_2050->Draw("p,same,e1");		
			
			
			//=============EMCal
			DrawGammaSetMarkerTGraphAsym(graphEMCalEtaRAASysPbPb2760GeV_0010, markerStyleDet[2], markerSizeDet[2]*0.75, colorEMCal0010 , colorEMCal0010, widthLinesBoxes, kTRUE);
			graphEMCalEtaRAASysPbPb2760GeV_0010->Draw("E2same");			
			DrawGammaSetMarkerTGraphAsym(graphEMCalEtaRAAStatPbPb2760GeV_0010, markerStyleDet[2], markerSizeDet[2]*0.75, colorEMCal0010 , colorEMCal0010);
			graphEMCalEtaRAAStatPbPb2760GeV_0010->Draw("p,same,e1");

			DrawGammaSetMarkerTGraphAsym(graphEMCalEtaRAASysPbPb2760GeV_2050, markerStyleDet[2], markerSizeDet[2]*0.75, colorEMCal2050 , colorEMCal2050, widthLinesBoxes, kTRUE);
			graphEMCalEtaRAASysPbPb2760GeV_2050->Draw("E2same");			
			DrawGammaSetMarkerTGraphAsym(graphEMCalEtaRAAStatPbPb2760GeV_2050, markerStyleDet[2], markerSizeDet[2]*0.75, colorEMCal2050 , colorEMCal2050);
			graphEMCalEtaRAAStatPbPb2760GeV_2050->Draw("p,same,e1");
			
		}
		
		
		//=============Combined
		DrawGammaSetMarkerTGraphAsym(graphCombRAASys2760GeVLHC11h_0010, markerStyleComb, markerSizeComb, colorComb , colorComb, widthLinesBoxes, kTRUE);
// 		graphCombRAASys2760GeVLHC11h_0010->Draw("E2same");
		DrawGammaSetMarkerTGraphAsym(graphCombRAAStat2760GeVLHC11h_0010, markerStyleComb, markerSizeComb, colorComb , colorComb);
// 		graphCombRAAStat2760GeVLHC11h_0010->Draw("p,same,e1");

		DrawGammaSetMarkerTGraphAsym(graphCombRAASys2760GeVLHC11h_2050, markerStyleComb, markerSizeComb, colorComb+1, colorComb+1, widthLinesBoxes, kTRUE);
// 		graphCombRAASys2760GeVLHC11h_2050->Draw("E2same");
		DrawGammaSetMarkerTGraphAsym(graphCombRAAStat2760GeVLHC11h_2050, markerStyleComb, markerSizeComb, colorComb+1 , colorComb+1);
// 		graphCombRAAStat2760GeVLHC11h_2050->Draw("p,same,e1");

		
		TLegend* legendRAAcombo = new TLegend(0.3,0.66,0.6,0.9);
		legendRAAcombo->SetFillColor(0);
		legendRAAcombo->SetLineColor(0);
		legendRAAcombo->SetTextFont(42);
		legendRAAcombo->SetTextSize(FontSize);
// 		legendRAAcombo->AddEntry(graphCombRAASys2760GeVLHC11h_0010,"combined","pf");		
// 		legendRAAcombo->AddEntry(graphPCMPi0RAASys2760GeV_0010,"PCM","pf");
// 		legendRAAcombo->AddEntry(graphEMCalPi0RAASysPbPb2760GeV_0010,"EMCal","pf");
		if(meson.CompareTo("Pi0")==0){
			
			legendRAAcombo->AddEntry((TObject*)0,"0-10% Pb-Pb (2011)","");
			legendRAAcombo->AddEntry(graphPCMPi0RAASys2760GeV_0010,"PCM","pf");
			legendRAAcombo->AddEntry(graphEMCalPi0RAASysPbPb2760GeV_0010,"EMCal","fp");
			legendRAAcombo->AddEntry((TObject*)0,"20-50% Pb-Pb (2011)","");
			legendRAAcombo->AddEntry(graphPCMPi0RAASys2760GeV_2050,"PCM","pf");
			legendRAAcombo->AddEntry(graphEMCalPi0RAASysPbPb2760GeV_2050,"EMCal","fp");
		} else if(meson.CompareTo("Eta")==0){

			legendRAAcombo->AddEntry((TObject*)0,"0-10% Pb-Pb (2011)","");
			legendRAAcombo->AddEntry(graphPCMEtaRAASys2760GeV_0010,"PCM","pf");
			legendRAAcombo->AddEntry(graphEMCalEtaRAASysPbPb2760GeV_0010,"EMCal","fp");
			legendRAAcombo->AddEntry((TObject*)0,"20-50% Pb-Pb (2011)","");
			legendRAAcombo->AddEntry(graphPCMEtaRAASys2760GeV_2050,"PCM","pf");
			legendRAAcombo->AddEntry(graphEMCalEtaRAASysPbPb2760GeV_2050,"EMCal","fp");
		}
			
		legendRAAcombo->Draw();

		TLatex *labelRAAEnergy = new TLatex(0.7,0.20,collisionSystem2760GeV.Data());
		SetStyleTLatex( labelRAAEnergy, 0.85*textSizeLabelsPixel,4);
		labelRAAEnergy->SetTextFont(43);
// 		labelRAAEnergy->Draw();
		TLatex *labelRAAPi0 = new TLatex(0.7,0.16,"#pi^{0} #rightarrow #gamma#gamma");
		SetStyleTLatex( labelRAAPi0, 0.85*textSizeLabelsPixel,4);
		labelRAAPi0->SetTextFont(43);
// 		labelRAAPi0->Draw();

	canvasRAAcombo->SaveAs(Form("%s/%s_RAA_LHC11h.%s",outputDir.Data(),meson.Data(),suffix.Data()));
// 	canvasRAAcombo->SaveAs(Form("%s/%s_RAA_LHC11h.%s",paperPlots.Data(),meson.Data(),suffix.Data()));
		
	
	
	canvasRAAcombo->cd();
	histo2DRAAcombo->DrawCopy();
	
		DrawGammaSetMarkerTGraphAsym(graphCombRAASys2760GeVLHC11h_0010, markerStyleComb, markerSizeComb, colorCombo0010 , colorCombo0010, 2, kTRUE);
		graphCombRAASys2760GeVLHC11h_0010->Draw("E2same");
		DrawGammaSetMarkerTGraphAsym(graphCombRAAStat2760GeVLHC11h_0010, markerStyleComb, markerSizeComb, colorCombo0010 , colorCombo0010);
		if(noXerrorBars) ProduceGraphAsymmWithoutXErrors(graphCombRAAStat2760GeVLHC11h_0010);
		graphCombRAAStat2760GeVLHC11h_0010->Draw("p,same,e1");

		DrawGammaSetMarkerTGraphAsym(graphCombRAASys2760GeVLHC11h_2050, markerStyleComb, markerSizeComb, colorCombo2050, colorCombo2050, 2, kTRUE);
		graphCombRAASys2760GeVLHC11h_2050->Draw("E2same");
		DrawGammaSetMarkerTGraphAsym(graphCombRAAStat2760GeVLHC11h_2050, markerStyleComb, markerSizeComb, colorCombo2050 , colorCombo2050);
		if(noXerrorBars) ProduceGraphAsymmWithoutXErrors(graphCombRAAStat2760GeVLHC11h_2050);
		graphCombRAAStat2760GeVLHC11h_2050->Draw("p,same,e1");

		TLatex *labelEnergyRAALHC11h = new TLatex(0.58,0.87,collisionSystem2760GeV.Data());
		SetStyleTLatex( labelEnergyRAALHC11h, 0.035,4);
		TLatex *labelDetSysRAALHC11h;
		if(meson.CompareTo("Pi0")==0){
			labelDetSysRAALHC11h= new TLatex(0.58,0.82,"#pi^{0} #rightarrow #gamma#gamma");
		} else if(meson.CompareTo("Eta")==0){
			labelDetSysRAALHC11h= new TLatex(0.58,0.82,"#eta #rightarrow #gamma#gamma");
		}
		SetStyleTLatex( labelDetSysRAALHC11h, 0.035,4);
		labelEnergyRAALHC11h->Draw();
		labelDetSysRAALHC11h->Draw();
		
		TLegend* legendRAAcombo2 = new TLegend(0.58,0.68,0.85,0.8);
		legendRAAcombo2->SetFillColor(0);
		legendRAAcombo2->SetLineColor(0);
		legendRAAcombo2->SetTextFont(42);
		legendRAAcombo2->SetTextSize(FontSize);
// 		legendRAAcombo2->AddEntry(graphCombRAASys2760GeVLHC11h_0010,Form("%s %s",cent0010.Data(),collisionSystem2760GeV.Data()),"fp");
// 		legendRAAcombo2->AddEntry(graphCombRAASys2760GeVLHC11h_2050,Form("%s %s",cent2050.Data(),collisionSystem2760GeV.Data()),"fp");
		legendRAAcombo2->AddEntry(graphCombRAASys2760GeVLHC11h_0010,Form("%s ",cent0010.Data()),"fp");
		legendRAAcombo2->AddEntry(graphCombRAASys2760GeVLHC11h_2050,Form("%s ",cent2050.Data()),"fp");
// 		legendRAAcombo2->AddEntry(graphCombRAASys2760GeVLHC11h_0010,"0-10% Pb-Pb PCM - EMCal","pf");		
// 		legendRAAcombo2->AddEntry(graphCombRAASys2760GeVLHC11h_2050,"20-50% Pb-Pb PCM - EMCal","pf");		
		legendRAAcombo2->Draw();

		boxErrorNorm0010->Draw();		
		boxErrorNorm2050->Draw();

	canvasRAAcombo->SaveAs(Form("%s/%s_RAA_combined.%s",outputDir.Data(),meson.Data(),suffix.Data()));
	canvasRAAcombo->SaveAs(Form("%s/%s_RAA_combined.%s",paperPlots.Data(),meson.Data(),suffix.Data()));
	
	
	canvasRAAcombo->cd();
	histo2DRAAcombo->DrawCopy();

		TLatex *labelEnergyRAALHC11hwithModels = new TLatex(0.4,0.87,collisionSystem2760GeV.Data());
		SetStyleTLatex( labelEnergyRAALHC11hwithModels, 0.035,4);
		TLatex *labelDetSysRAALHC11hwithModels;
		if(meson.CompareTo("Pi0")==0){
			labelDetSysRAALHC11hwithModels= new TLatex(0.4,0.82,"#pi^{0} #rightarrow #gamma#gamma");
		} else if(meson.CompareTo("Eta")==0){
			labelDetSysRAALHC11hwithModels= new TLatex(0.4,0.82,"#eta #rightarrow #gamma#gamma");
		}
		SetStyleTLatex( labelDetSysRAALHC11hwithModels, 0.035,4);
		labelEnergyRAALHC11hwithModels->Draw();
		labelDetSysRAALHC11hwithModels->Draw();

		TLegend* legendRAAwithModels = new TLegend(0.4,0.68,0.85,0.8);
		legendRAAwithModels->SetFillColor(0);
		legendRAAwithModels->SetLineColor(0);
		legendRAAwithModels->SetTextFont(42);
		legendRAAwithModels->SetTextSize(FontSize);
		legendRAAwithModels->AddEntry(graphCombRAASys2760GeVLHC11h_0010,Form("%s ",cent0010.Data()),"fp");
		legendRAAwithModels->AddEntry(graphCombRAASys2760GeVLHC11h_2050,Form("%s ",cent2050.Data()),"fp");
		legendRAAwithModels->Draw();

		TLegend* legendRAATheoryPbPb = new TLegend(0.4,0.48,0.85,0.65);
		legendRAATheoryPbPb->SetFillColor(0);
		legendRAATheoryPbPb->SetLineColor(0);
		legendRAATheoryPbPb->SetTextFont(42);
		legendRAATheoryPbPb->SetTextSize(FontSize);
// 		legendRAATheoryPbPb->SetMargin(0.35);
// 		legendRAATheoryPbPb->SetNColumns(2);
// 		legendRAATheoryPbPb->SetTextSize(0.85*textsizeLabelsRatioUp);
		
		if(meson.CompareTo("Pi0")==0){ 
			
			DrawGammaSetMarkerTGraphAsym(graphPi0RAAJetQuenching_0010, 0, 0, colorNLO0010, colorNLO0010, widthLinesBoxes, kTRUE, colorNLO0010);
			graphPi0RAAJetQuenching_0010->Draw("3,same");

			DrawGammaSetMarkerTGraphAsym(gWHDG_Raa_0010, markerStyleCommmonSpectrum0010,markerSizeSpectrum, colorWHDG0005, colorWHDG0005,widthLinesBoxes, kTRUE);
			gWHDG_Raa_0010->SetFillStyle(fillStyleWHDG);
			gWHDG_Raa_0010->SetFillColor(colorWHDG0005);
			gWHDG_Raa_0010->Draw("3 same");

			DrawGammaSetMarkerTGraphAsym(gWHDG_Raa_2040, markerStyleCommmonSpectrum2040,markerSizeSpectrum, colorWHDG4060, colorWHDG4060,widthLinesBoxes, kTRUE);
			gWHDG_Raa_2040->SetFillStyle(fillStyleWHDG);
			gWHDG_Raa_2040->SetFillColor(colorWHDG4060);
			gWHDG_Raa_2040->Draw("3 same");
			
// 			DrawGammaSetMarkerTGraphErr(Vitev_Bas_Raa_0005, markerStyleCommmonSpectrum0005,markerSizeSpectrum, colorVitevBas0005 ,colorVitevBas0005,2);
// 			Vitev_Bas_Raa_0005->SetFillStyle(fillStyleVitev);
// 			Vitev_Bas_Raa_0005->SetFillColor(colorVitevBas0005);
// 			Vitev_Bas_Raa_0005->Draw("3 same");
// 			DrawGammaSetMarkerTGraphErr(Vitev_Bas_Raa_2040, markerStyleCommmonSpectrum2040,markerSizeSpectrum, colorVitevBas2040 ,colorVitevBas2040,2);
// 			Vitev_Bas_Raa_2040->SetFillStyle(fillStyleVitev);
// 			Vitev_Bas_Raa_2040->SetFillColor(colorVitevBas2040);
// 			Vitev_Bas_Raa_2040->Draw("3 same");

// 			TGraphAsymmErrors* gWHDG_Raa_Legend = (TGraphAsymmErrors*)gWHDG_Raa_0010->Clone();		
// 			DrawGammaSetMarkerTGraphAsym(gWHDG_Raa_Legend, markerStyleCommmonSpectrum0005,markerSizeSpectrum, kBlack, kBlack,widthLinesBoxes, kTRUE);
// 			gWHDG_Raa_Legend->SetFillStyle(fillStyleWHDG);
// 			gWHDG_Raa_Legend->SetFillColor(kBlack);
// 
			legendRAATheoryPbPb->AddEntry(gWHDG_Raa_0010,"WHDG - 0-10%","f");
			legendRAATheoryPbPb->AddEntry(gWHDG_Raa_2040,"WHDG - 20-40%","f");
			legendRAATheoryPbPb->AddEntry(graphPi0RAAJetQuenching_0010,"NLO pQCD DCZW - 0-10%","f");
// 			legendRAATheoryPbPb->AddEntry(graphPi0JetQuenching18semicent,"NLO pQCD DCZW - 20-40%","f");
// 			legendRAATheoryPbPb->AddEntry(Vitev_Bas_Raa_0005,"GLV - 0-5%","f");
// 			legendRAATheoryPbPb->AddEntry(Vitev_Bas_Raa_2040,"GLV - 20-40%","f");
		
		} else if(meson.CompareTo("Eta")==0){

			DrawGammaSetMarkerTGraphAsym(graphEtaRAAJetQuenching_0010, 0, 0, colorNLO0010, colorNLO0010, widthLinesBoxes, kTRUE, colorNLO0010);
			graphEtaRAAJetQuenching_0010->Draw("3,same");

			DrawGammaSetMarkerTGraphAsym(gWHDG_Eta_Raa_0010, markerStyleCommmonSpectrum0010,markerSizeSpectrum, colorWHDG0005, colorWHDG0005,widthLinesBoxes, kTRUE);
			gWHDG_Eta_Raa_0010->SetFillStyle(fillStyleWHDG);
			gWHDG_Eta_Raa_0010->SetFillColor(colorWHDG0005);
			gWHDG_Eta_Raa_0010->Draw("3 same");

			DrawGammaSetMarkerTGraphAsym(gWHDG_Eta_Raa_2050, markerStyleCommmonSpectrum2040,markerSizeSpectrum, colorWHDG4060, colorWHDG4060,widthLinesBoxes, kTRUE);
			gWHDG_Eta_Raa_2050->SetFillStyle(fillStyleWHDG);
			gWHDG_Eta_Raa_2050->SetFillColor(colorWHDG4060);
			gWHDG_Eta_Raa_2050->Draw("3 same");

			legendRAATheoryPbPb->AddEntry(gWHDG_Eta_Raa_0010,"WHDG - 0-10%","f");
			legendRAATheoryPbPb->AddEntry(gWHDG_Eta_Raa_2050,"WHDG - 20-50%","f");
			legendRAATheoryPbPb->AddEntry(graphEtaRAAJetQuenching_0010,"NLO pQCD DCZW - 0-10%","f");
// 			legendRAATheoryPbPb->AddEntry(graphPi0JetQuenching18semicent,"NLO pQCD DCZW - 20-40%","f");

		}
		
// 		TGraphAsymmErrors* gWHDG_Raa_Legend = (TGraphAsymmErrors*)gWHDG_Raa_0010->Clone();		
// 		DrawGammaSetMarkerTGraphAsym(gWHDG_Raa_Legend, markerStyleCommmonSpectrum0005,markerSizeSpectrum, kBlack, kBlack,widthLinesBoxes, kTRUE);
// 		gWHDG_Raa_Legend->SetFillStyle(fillStyleWHDG);
// 		gWHDG_Raa_Legend->SetFillColor(kBlack);
// 
// 		legendRAATheoryPbPb->AddEntry(gWHDG_Raa_Legend,"WHDG","f");
		legendRAATheoryPbPb->Draw();
		boxErrorNorm0010->Draw();		
		boxErrorNorm2050->Draw();

		graphCombRAASys2760GeVLHC11h_0010->Draw("E2same");
		if(noXerrorBars) ProduceGraphAsymmWithoutXErrors(graphCombRAAStat2760GeVLHC11h_0010);
		graphCombRAAStat2760GeVLHC11h_0010->Draw("p,same,e1");
		graphCombRAASys2760GeVLHC11h_2050->Draw("E2same");
		if(noXerrorBars) ProduceGraphAsymmWithoutXErrors(graphCombRAAStat2760GeVLHC11h_2050);
		graphCombRAAStat2760GeVLHC11h_2050->Draw("p,same,e1");

	canvasRAAcombo->SaveAs(Form("%s/%s_RAA_combinedWithTheoryModels.%s",outputDir.Data(),meson.Data(),suffix.Data()));
	canvasRAAcombo->SaveAs(Form("%s/%s_RAA_combinedWithTheoryModels.%s",paperPlots.Data(),meson.Data(),suffix.Data()));
	
	
	canvasRAAcombo->cd();
	histo2DRAAcombo->DrawCopy();
	
		labelEnergyRAALHC11h->Draw();
// 		labelDetSysRAALHC11h->Draw();

		TLegend* legendRAAcomboCharged = new TLegend(0.58,0.65,0.85,0.83);
// 		if(meson.CompareTo("Pi0")==0){
// 			legendRAAcomboCharged->SetHeader("#pi^{0} #rightarrow #gamma#gamma");
// 		} else if(meson.CompareTo("Eta")==0){
// 			legendRAAcomboCharged->SetHeader("#eta #rightarrow #gamma#gamma");
// 		}
		legendRAAcomboCharged->SetFillColor(0);
		legendRAAcomboCharged->SetLineColor(0);
		legendRAAcomboCharged->SetTextFont(42);
		legendRAAcomboCharged->SetTextSize(FontSize);
// 		legendRAAcomboCharged->AddEntry(graphCombRAASys2760GeVLHC11h_0010,Form("%s %s",cent0010.Data(),collisionSystem2760GeV.Data()),"fp");
		if(meson.CompareTo("Pi0")==0){
			legendRAAcomboCharged->AddEntry(graphCombRAASys2760GeVLHC11h_0010,Form("#pi^{0} - %s ",cent0010.Data()),"fp");
		} else if(meson.CompareTo("Eta")==0){
			legendRAAcomboCharged->AddEntry(graphCombRAASys2760GeVLHC11h_0010,Form("#eta - %s ",cent0010.Data()),"fp");

		}
	
		if(meson.CompareTo("Pi0")==0){ 
			
			DrawGammaSetMarkerTGraphAsym(graphChargedPionRAA0010, 21,2, colorCharged,colorCharged, 0.1, kFALSE);
			DrawGammaSetMarkerTGraphAsym(graphChargedPionRAASys0010,21,2, colorCharged,colorCharged, 2, kTRUE);
			graphChargedPionRAASys0010->Draw("2same");
			graphChargedPionRAA0010->Draw("p,same"); 
			legendRAAcomboCharged->AddEntry((TObject*)0,"","");
// 			legendRAAcomboCharged->AddEntry(graphChargedPionRAA0010,Form("#pi^{#pm} - %s %s",cent0010.Data(),collisionSystem2760GeV.Data()),"fp");
			legendRAAcomboCharged->AddEntry(graphChargedPionRAA0010,Form("#pi^{#pm} - %s ",cent0010.Data()),"fp");
			legendRAAcomboCharged->AddEntry((TObject*)0,"Phys. Lett. B736 (2014)","");
			
		} else if(meson.CompareTo("Eta")==0){

			DrawGammaSetMarkerTGraphAsym(graphChargedKaonRAA0010, 21,2, colorCharged,colorCharged, 0.1, kFALSE);
			DrawGammaSetMarkerTGraphAsym(graphChargedKaonRAASys0010,21,1, colorCharged,colorCharged, 1, kTRUE);
			graphChargedKaonRAASys0010->Draw("2same");
			graphChargedKaonRAA0010->Draw("p,same"); 
			legendRAAcomboCharged->AddEntry((TObject*)0,"","");
// 			legendRAAcomboCharged->AddEntry(graphChargedKaonRAA0010,Form("K^{#pm} - %s %s",cent0010.Data(),collisionSystem2760GeV.Data()),"fp");
			legendRAAcomboCharged->AddEntry(graphChargedKaonRAA0010,Form("K^{#pm} - %s ",cent0010.Data()),"fp");
			legendRAAcomboCharged->AddEntry((TObject*)0,"Phys. Lett. B736 (2014)","");
			
		}
		
		graphCombRAASys2760GeVLHC11h_0010->Draw("E2same");
		if(noXerrorBars) ProduceGraphAsymmWithoutXErrors(graphCombRAAStat2760GeVLHC11h_0010);
		graphCombRAAStat2760GeVLHC11h_0010->Draw("p,same,e1");

		boxErrorNorm0010Only->Draw();		

		legendRAAcomboCharged->Draw();
	
	canvasRAAcombo->SaveAs(Form("%s/%s_RAA_combinedWithCharged_0010.%s",outputDir.Data(),meson.Data(),suffix.Data()));
	canvasRAAcombo->SaveAs(Form("%s/%s_RAA_combinedWithCharged_0010.%s",paperPlots.Data(),meson.Data(),suffix.Data()));
	

	
	TGraphAsymmErrors* graphCombRAAStatCopy_0010 	= (TGraphAsymmErrors*) graphCombRAAStat2760GeVLHC11h_0010->Clone("graphCombRAAStatCopy_0010");
	TGraphAsymmErrors* graphCombRAASysCopy_0010 		= (TGraphAsymmErrors*) graphCombRAASys2760GeVLHC11h_0010->Clone("graphCombRAASysCopy_0010");
	TGraphAsymmErrors* graphRAAChargedPionStatCopy_0010 		= (TGraphAsymmErrors*) graphChargedPionRAA0010->Clone("graphRAAChargedPionStatCopy_0010");
	TGraphAsymmErrors* graphRAAChargedPionSysCopy_0010 		= (TGraphAsymmErrors*) graphChargedPionRAASys0010->Clone("graphRAAChargedPionSysCopy_0010");
	TGraphAsymmErrors* graphRAAChargedKaonStatCopy_0010 		= (TGraphAsymmErrors*) graphChargedKaonRAA0010->Clone("graphRAAChargedKaonStatCopy_0010");
	TGraphAsymmErrors* graphRAAChargedKaonSysCopy_0010 		= (TGraphAsymmErrors*) graphChargedKaonRAASys0010->Clone("graphRAAChargedKaonSysCopy_0010");

	TGraphErrors* graphRaaStatNeutral_0010 	= NULL;
	TGraphErrors* graphRaaSysNeutral_0010 	= NULL;
	TGraphErrors* graphRaaStatCharged_0010 	= NULL;
	TGraphErrors* graphRaaSysCharged_0010 	= NULL;
	TGraphErrors* graphRaaRatioNeutralToCharged_0010 =NULL;
		
	if(meson.CompareTo("Pi0")==0){ 

		graphRaaRatioNeutralToCharged_0010 = CalculateRatioBetweenSpectraWithDifferentBinning(graphCombRAAStatCopy_0010, graphCombRAASysCopy_0010, 
																										  graphRAAChargedPionStatCopy_0010, graphRAAChargedPionSysCopy_0010, 
																									      kFALSE,  kFALSE, 
																									      &graphRaaStatNeutral_0010, &graphRaaSysNeutral_0010, 
																									      &graphRaaStatCharged_0010, &graphRaaSysCharged_0010);
		graphRaaRatioNeutralToCharged_0010->Print();
	
	} else if(meson.CompareTo("Eta")==0){

		graphRaaRatioNeutralToCharged_0010 = CalculateRatioBetweenSpectraWithDifferentBinning(graphCombRAAStatCopy_0010, graphCombRAASysCopy_0010, 
																										  graphRAAChargedKaonStatCopy_0010, graphRAAChargedKaonSysCopy_0010, 
																									      kFALSE,  kFALSE, 
																									      &graphRaaStatNeutral_0010, &graphRaaSysNeutral_0010, 
																									      &graphRaaStatCharged_0010, &graphRaaSysCharged_0010);
		graphRaaRatioNeutralToCharged_0010->Print();

	}
		
		
	TCanvas* canvasRaaratio = new TCanvas("canvasRaaratio","",200,10,700,500);  // gives the page size
	DrawGammaCanvasSettings( canvasRaaratio,  0.12, 0.02, 0.02, 0.12);
	
 	canvasRaaratio->SetLogx();

	TH2F * histo2DCompCombinedRatio2;
	histo2DCompCombinedRatio2 = new TH2F("histo2DCompCombinedRatio2","histo2DCompCombinedRatio2",1000,0.3,40.,1000,0.,10.	);
	if(meson.CompareTo("Pi0")==0) histo2DCompCombinedRatio2->GetYaxis()->SetRangeUser(0.,2.);
	else if(meson.CompareTo("Eta")==0) histo2DCompCombinedRatio2->GetYaxis()->SetRangeUser(0.,5.);
	histo2DCompCombinedRatio2->GetXaxis()->SetRangeUser(0.6,20.5);
	histo2DCompCombinedRatio2->GetXaxis()->SetLabelOffset(-0.015);
	if(meson.CompareTo("Pi0")==0) SetStyleHistoTH2ForGraphs(histo2DCompCombinedRatio2, "#it{p}_{T} (GeV/#it{c})","#pi^{0} #it{R}_{AA} / #pi^{#pm} #it{R}_{AA}", 0.05,0.064, 0.05,0.06, 0.8,0.9, 512, 505);
	else if(meson.CompareTo("Eta")==0) SetStyleHistoTH2ForGraphs(histo2DCompCombinedRatio2, "#it{p}_{T} (GeV/#it{c})","#eta #it{R}_{AA} / K^{#pm} #it{R}_{AA}", 0.05,0.064, 0.05,0.06, 0.8,0.9, 512, 505);
	histo2DCompCombinedRatio2->DrawCopy();
	
		DrawGammaSetMarkerTGraphErr(graphRaaRatioNeutralToCharged_0010, markerStyleComb, markerSizeComb, colorCombo0010 , colorCombo0010);
		graphRaaRatioNeutralToCharged_0010->Draw("E1psame");
		
		TLatex *labelRatioPi02760GeV = new TLatex(0.16,0.9,collisionSystemPbPb0010.Data());
		SetStyleTLatex( labelRatioPi02760GeV, 0.06,0.35);
		labelRatioPi02760GeV->Draw();

		TLegend* legendPi0CompChargedPionsPP = new TLegend(0.15,0.77,0.6,0.87);
		legendPi0CompChargedPionsPP->SetFillColor(0);
		legendPi0CompChargedPionsPP->SetFillStyle(0);
		legendPi0CompChargedPionsPP->SetLineColor(0);
		legendPi0CompChargedPionsPP->SetNColumns(2);
		legendPi0CompChargedPionsPP->SetTextSize(0.045);
		legendPi0CompChargedPionsPP->SetMargin(0.12);
		if(meson.CompareTo("Pi0")==0) legendPi0CompChargedPionsPP->AddEntry(graphRaaRatioNeutralToCharged_0010,"#frac{#pi^{0} #it{R}_{AA}}{#pi^{#pm} #it{R}_{AA}}","p");
		else if(meson.CompareTo("Eta")==0) legendPi0CompChargedPionsPP->AddEntry(graphRaaRatioNeutralToCharged_0010,"#frac{#eta #it{R}_{AA} }{K^{#pm} #it{R}_{AA}}","p");
		legendPi0CompChargedPionsPP->Draw();
	
		DrawGammaLines(0., 15.,1., 1., 0.1,kGray,2);
	
	canvasRaaratio->Update();
	canvasRaaratio->SaveAs(Form("%s/%s_RatioRAA_combinedWithCharged_0010.%s",outputDir.Data(),meson.Data(),suffix.Data()));
// 	canvasRaaratio->SaveAs(Form("%s/%s_RatioRAA_combinedWithCharged_0010.%s",paperPlots.Data(),meson.Data(),suffix.Data()));
	
	canvasRAAcombo->cd();
	histo2DRAAcombo->DrawCopy();
	
		labelEnergyRAALHC11h->Draw();
	
		TLegend* legendRAAcomboCharged2050 = new TLegend(0.58,0.65,0.85,0.83);
// 		if(meson.CompareTo("Pi0")==0){
// 			legendRAAcomboCharged2050->SetHeader("#pi^{0} #rightarrow #gamma#gamma");
// 		} else if(meson.CompareTo("Eta")==0){
// 			legendRAAcomboCharged2050->SetHeader("#eta #rightarrow #gamma#gamma");
// 		}
		legendRAAcomboCharged2050->SetFillColor(0);
		legendRAAcomboCharged2050->SetLineColor(0);
		legendRAAcomboCharged2050->SetTextFont(42);
		legendRAAcomboCharged2050->SetTextSize(FontSize);
// 		legendRAAcomboCharged2050->AddEntry(graphCombRAASys2760GeVLHC11h_2050,Form("%s %s",cent2050.Data(),collisionSystem2760GeV.Data()),"fp");
		if(meson.CompareTo("Pi0")==0){
			legendRAAcomboCharged2050->AddEntry(graphCombRAASys2760GeVLHC11h_2050,Form("#pi^{0} - %s ",cent2050.Data()),"fp");
		} else if(meson.CompareTo("Eta")==0){
			legendRAAcomboCharged2050->AddEntry(graphCombRAASys2760GeVLHC11h_2050,Form("#eta - %s ",cent2050.Data()),"fp");

		}
	
		if(meson.CompareTo("Pi0")==0){ 
			
			DrawGammaSetMarkerTGraphAsym(graphChargedPionRAA2040, 21,2, colorCharged,colorCharged, 0.1, kFALSE);
			DrawGammaSetMarkerTGraphAsym(graphChargedPionRAASys2040,21,2, colorCharged,colorCharged, 1, kTRUE);
			graphChargedPionRAASys2040->Draw("2same");
			graphChargedPionRAA2040->Draw("p,same"); 
			legendRAAcomboCharged2050->AddEntry((TObject*)0,"","");
// 			legendRAAcomboCharged2050->AddEntry(graphChargedPionRAA2040,Form("#pi^{#pm} - 20-40%^{} %s",collisionSystem2760GeV.Data()),"fp");
			legendRAAcomboCharged2050->AddEntry(graphChargedPionRAA2040,"#pi^{#pm} - 20-40%","fp");
			legendRAAcomboCharged2050->AddEntry((TObject*)0,"Phys. Lett. B736 (2014)","");
			
		} else if(meson.CompareTo("Eta")==0){

			DrawGammaSetMarkerTGraphAsym(graphChargedKaonRAA2040, 21,2,  colorCharged,colorCharged, 0.1, kFALSE);
			DrawGammaSetMarkerTGraphAsym(graphChargedKaonRAASys2040,21,2, colorCharged,colorCharged, 1, kTRUE);
			graphChargedKaonRAASys2040->Draw("2same");
			graphChargedKaonRAA2040->Draw("p,same"); 
			legendRAAcomboCharged2050->AddEntry((TObject*)0,"","");
// 			legendRAAcomboCharged2050->AddEntry(graphChargedKaonRAA2040,Form("K^{#pm} - 20-40%^{} %s",collisionSystem2760GeV.Data()),"fp");
			legendRAAcomboCharged2050->AddEntry(graphChargedKaonRAA2040,"K^{#pm} - 20-40%","fp");
			legendRAAcomboCharged2050->AddEntry((TObject*)0,"Phys. Lett. B736 (2014)","");			
			
		}
		
		graphCombRAASys2760GeVLHC11h_2050->Draw("E2same");
		if(noXerrorBars) ProduceGraphAsymmWithoutXErrors(graphCombRAAStat2760GeVLHC11h_2050);
		graphCombRAAStat2760GeVLHC11h_2050->Draw("p,same,e1");

		boxErrorNorm2050Only->Draw();

		legendRAAcomboCharged2050->Draw();
	
	canvasRAAcombo->SaveAs(Form("%s/%s_RAA_combinedWithCharged_2040.%s",outputDir.Data(),meson.Data(),suffix.Data()));
	canvasRAAcombo->SaveAs(Form("%s/%s_RAA_combinedWithCharged_2040.%s",paperPlots.Data(),meson.Data(),suffix.Data()));

	
	TGraphAsymmErrors* graphCombRAAStatCopy_2050 	= (TGraphAsymmErrors*) graphCombRAAStat2760GeVLHC11h_2050->Clone("graphCombRAAStatCopy_2050");
	TGraphAsymmErrors* graphCombRAASysCopy_2050 		= (TGraphAsymmErrors*) graphCombRAASys2760GeVLHC11h_2050->Clone("graphCombRAASysCopy_2050");
	TGraphAsymmErrors* graphRAAChargedPionStatCopy_2040 		= (TGraphAsymmErrors*) graphChargedPionRAA2040->Clone("graphRAAChargedPionStatCopy_2040");
	TGraphAsymmErrors* graphRAAChargedPionSysCopy_2040 		= (TGraphAsymmErrors*) graphChargedPionRAASys2040->Clone("graphRAAChargedPionSysCopy_2040");
	TGraphAsymmErrors* graphRAAChargedKaonStatCopy_2040 		= (TGraphAsymmErrors*) graphChargedKaonRAA2040->Clone("graphRAAChargedKaonStatCopy_2040");
	TGraphAsymmErrors* graphRAAChargedKaonSysCopy_2040 		= (TGraphAsymmErrors*) graphChargedKaonRAASys2040->Clone("graphRAAChargedKaonSysCopy_2040");

	TGraphErrors* graphRaaStatNeutral_2050 	= NULL;
	TGraphErrors* graphRaaSysNeutral_2050 	= NULL;
	TGraphErrors* graphRaaStatCharged_2050 	= NULL;
	TGraphErrors* graphRaaSysCharged_2050 	= NULL;
	TGraphErrors* graphRaaRatioNeutralToCharged_2050 =NULL;
		
	if(meson.CompareTo("Pi0")==0){ 

		graphRaaRatioNeutralToCharged_2050 = CalculateRatioBetweenSpectraWithDifferentBinning(graphCombRAAStatCopy_2050, graphCombRAASysCopy_2050, 
																										  graphRAAChargedPionStatCopy_2040, graphRAAChargedPionSysCopy_2040, 
																									      kFALSE,  kFALSE, 
																									      &graphRaaStatNeutral_2050, &graphRaaSysNeutral_2050, 
																									      &graphRaaStatCharged_2050, &graphRaaSysCharged_2050);
		graphRaaRatioNeutralToCharged_2050->Print();
	
	} else if(meson.CompareTo("Eta")==0){

		graphRaaRatioNeutralToCharged_2050 = CalculateRatioBetweenSpectraWithDifferentBinning(graphCombRAAStatCopy_2050, graphCombRAASysCopy_2050, 
																										  graphRAAChargedKaonStatCopy_2040, graphRAAChargedKaonSysCopy_2040, 
																									      kFALSE,  kFALSE, 
																									      &graphRaaStatNeutral_2050, &graphRaaSysNeutral_2050, 
																									      &graphRaaStatCharged_2050, &graphRaaSysCharged_2050);
		graphRaaRatioNeutralToCharged_2050->Print();

	}
		
		
	canvasRaaratio->cd();
	histo2DCompCombinedRatio2->DrawCopy();
	if(meson.CompareTo("Pi0")==0) 	histo2DCompCombinedRatio2->GetYaxis()->SetRangeUser(0.5,2.5);
	else if(meson.CompareTo("Eta")==0) histo2DCompCombinedRatio2->GetYaxis()->SetRangeUser(0.,5.);


		DrawGammaSetMarkerTGraphErr(graphRaaRatioNeutralToCharged_2050, markerStyleComb, markerSizeComb, colorCombo2050 , colorCombo2050);
		graphRaaRatioNeutralToCharged_2050->Draw("E1psame");
		
		TLatex *labelRatioPi02760GeV2050 = new TLatex(0.16,0.9,collisionSystemPbPb2050.Data());
		SetStyleTLatex( labelRatioPi02760GeV2050, 0.06,4);
		labelRatioPi02760GeV2050->Draw();

		TLegend* legendPi0CompChargedPionsPP2050 = new TLegend(0.15,0.15,0.9,0.25);
		legendPi0CompChargedPionsPP2050->SetFillColor(0);
		legendPi0CompChargedPionsPP2050->SetFillStyle(0);
		legendPi0CompChargedPionsPP2050->SetLineColor(0);
		legendPi0CompChargedPionsPP2050->SetNColumns(2);
		legendPi0CompChargedPionsPP2050->SetTextSize(0.045);
		legendPi0CompChargedPionsPP2050->SetMargin(0.12);
		if(meson.CompareTo("Pi0")==0) legendPi0CompChargedPionsPP2050->AddEntry(graphRaaRatioNeutralToCharged_2050,"#frac{#pi^{0} #it{R}_{AA}}{#pi^{#pm} #it{R}_{AA}}","p");
		else if(meson.CompareTo("Eta")==0) legendPi0CompChargedPionsPP2050->AddEntry(graphRaaRatioNeutralToCharged_2050,"#frac{#eta #it{R}_{AA} }{K^{#pm} #it{R}_{AA}}","p");
		legendPi0CompChargedPionsPP2050->Draw();
	
		DrawGammaLines(0., 15.,1., 1., 0.1,kGray,2);
	
	canvasRaaratio->Update();
	canvasRaaratio->SaveAs(Form("%s/%s_RatioRAA_combinedWithCharged_2050.%s",outputDir.Data(),meson.Data(),suffix.Data()));
// 	canvasRaaratio->SaveAs(Form("%s/%s_RatioRAA_combinedWithCharged_2050.%s",paperPlots.Data(),meson.Data(),suffix.Data()));
	
	
	
	Int_t textSizeLabelsPixelRAA = 50;
	Double_t marginRAA = 0.14*1200;
	Double_t textsizeLabelsRAA = 0;
	Double_t textsizeFacRAA = 0;

	if (canvasRAAcombo->XtoPixel(canvasRAAcombo->GetX2()) < canvasRAAcombo->YtoPixel(canvasRAAcombo->GetY1())){
		textsizeLabelsRAA = (Double_t)textSizeLabelsPixelRAA/canvasRAAcombo->XtoPixel(canvasRAAcombo->GetX2()) ;
		textsizeFacRAA = (Double_t)1./canvasRAAcombo->XtoPixel(canvasRAAcombo->GetX2()) ;
	} else {
		textsizeLabelsRAA = (Double_t)textSizeLabelsPixelRAA/canvasRAAcombo->YtoPixel(canvasRAAcombo->GetY1());
		textsizeFacRAA = (Double_t)1./canvasRAAcombo->YtoPixel(canvasRAAcombo->GetY1());
	}

	if(meson.CompareTo("Pi0")==0){
		canvasRAAcombo->cd();
			TH2F * histo2DRAAcomboPHENIX;
			histo2DRAAcomboPHENIX = new TH2F("histo2DRAAcomboPHENIX","histo2DRAAcomboPHENIX",11000,0.23,70.,1000,-0.5,2.);
			SetStyleHistoTH2ForGraphs(histo2DRAAcomboPHENIX, "#it{p}_{T} (GeV/#it{c})","#it{R}_{AA}",0.035,0.04, 0.035,0.04, 1.,.9);
	// 		histo2DRAAcombo->GetXaxis()->SetMoreLogLabels();	
	// 		histo2DRAAcombo->GetXaxis()->SetLabelOffset(-0.01);
			histo2DRAAcomboPHENIX->GetYaxis()->SetRangeUser(0.,2.);
			histo2DRAAcomboPHENIX->GetXaxis()->SetRangeUser(0.,20.01);
			histo2DRAAcomboPHENIX->Draw("copy");
			
			DrawGammaSetMarkerTGraphErr(graphPHENIX200GeVRAA_0010, markerStylePHENIX200GeV,markerSizePHENIX200GeV, kBlack , kBlack);
			DrawGammaSetMarkerTGraphErr(graphPHENIX62GeVRAA_0010, markerStylePHENIX62GeV,markerSizePHENIX62GeV, kBlack, kBlack);
			DrawGammaSetMarkerTGraphErr(graphPHENIX39GeVRAA_0010, markerStylePHENIX39GeV,markerSizePHENIX39GeV, kBlack , kBlack);
			DrawGammaSetMarkerTGraphErr(graphWA98_17_3GeVRAA_0013, markerStyleWA98,markerSizeWA98, kGray+2 , kGray+2);

			graphPHENIX200GeVRAA_0010->Draw("p,same,e1");	
			graphPHENIX39GeVRAA_0010->Draw("p,same,e1");	
			graphPHENIX62GeVRAA_0010->Draw("p,same,e1");	
			graphWA98_17_3GeVRAA_0013->Draw("p,same,e1");	

			graphCombRAASys2760GeVLHC11h_0010->Draw("E2same");
			if(noXerrorBars) ProduceGraphAsymmWithoutXErrors(graphCombRAAStat2760GeVLHC11h_0010);
		graphCombRAAStat2760GeVLHC11h_0010->Draw("p,same,e1");

			TLatex *labelRAAALICEPbPb0010 = new TLatex(0.35,0.9,"#pi^{0} ALICE 0-10% Pb-Pb (2011)");
			SetStyleTLatex( labelRAAALICEPbPb0010, 0.85*textsizeLabelsRAA,4);
			labelRAAALICEPbPb0010->Draw();
			TLegend* legendRAASinglePbPb0010 = new TLegend(0.35,0.84,0.65,0.885);
			legendRAASinglePbPb0010->SetFillColor(0);
			legendRAASinglePbPb0010->SetLineColor(0);
			legendRAASinglePbPb0010->SetNColumns(1);
			legendRAASinglePbPb0010->SetTextFont(42);
			legendRAASinglePbPb0010->SetTextSize(0.85*textsizeLabelsRAA);
			legendRAASinglePbPb0010->AddEntry(graphCombRAASys2760GeVLHC11h_0010,"0-10% #sqrt{#it{s}_{_{NN}}} = 2.76 TeV","pf");
			legendRAASinglePbPb0010->Draw();

			TLatex *labelRAAPHENIXPbPb0010 = new TLatex(0.35,0.79,"#pi^{0} PHENIX 0-10% Au-Au");
			SetStyleTLatex( labelRAAPHENIXPbPb0010, 0.85*textsizeLabelsRAA,4);
			labelRAAPHENIXPbPb0010->Draw();

			TLegend* legendRAARHICPbPb0010 = new TLegend(0.35,0.66,0.95,0.78);
			legendRAARHICPbPb0010->SetFillColor(0);
			legendRAARHICPbPb0010->SetLineColor(0);
			legendRAARHICPbPb0010->SetNColumns(2);
			legendRAARHICPbPb0010->SetTextFont(42);
			legendRAARHICPbPb0010->SetTextSize(0.85*textsizeLabelsRAA);
			legendRAARHICPbPb0010->AddEntry(graphPHENIX200GeVRAA_0010,"#sqrt{#it{s}_{_{NN}}} = 200 GeV","p");
			legendRAARHICPbPb0010->AddEntry(graphPHENIX62GeVRAA_0010,"#sqrt{#it{s}_{_{NN}}} = 62.4 GeV","p");
			legendRAARHICPbPb0010->AddEntry(graphPHENIX39GeVRAA_0010,"#sqrt{#it{s}_{_{NN}}} = 39 GeV","p");
			legendRAARHICPbPb0010->Draw();

			TLatex *labelRAAWA98PbPb0010 = new TLatex(0.35,0.61,"#pi^{0} WA98     0-13% Pb-Pb");
			SetStyleTLatex( labelRAAWA98PbPb0010, 0.85*textsizeLabelsRAA,4);
			labelRAAWA98PbPb0010->Draw();

			TLegend* legendRAASPSPbPb0010 = new TLegend(0.35,0.55,0.95,0.59);
			legendRAASPSPbPb0010->SetFillColor(0);
			legendRAASPSPbPb0010->SetLineColor(0);
			legendRAASPSPbPb0010->SetNColumns(2);
			legendRAASPSPbPb0010->SetTextFont(42);
			legendRAASPSPbPb0010->SetTextSize(0.85*textsizeLabelsRAA);
			legendRAASPSPbPb0010->AddEntry(graphWA98_17_3GeVRAA_0013,"#sqrt{#it{s}_{_{NN}}} = 17.3 GeV","p");
			legendRAASPSPbPb0010->Draw();

			boxErrorNorm0010_Single->Draw();
			DrawGammaLines(0., 19.5 , 1, 1 ,1,kGray);
		
		
		canvasRAAcombo->SaveAs(Form("%s/%s_RAA_combinedwithPHENIX_asPaper_0010.%s",outputDir.Data(),meson.Data(),suffix.Data()));
		canvasRAAcombo->SaveAs(Form("%s/%s_RAA_combinedwithPHENIX_asPaper_0010.%s",paperPlots.Data(),meson.Data(),suffix.Data()));

		
		canvasRAAcombo->cd();
		histo2DRAAcomboPHENIX->DrawCopy();

			DrawGammaSetMarkerTGraphErr(graphPHENIX200GeVRAA_2040, markerStylePHENIX200GeV,markerSizePHENIX200GeV, kBlack , kBlack);
			DrawGammaSetMarkerTGraphErr(graphPHENIX62GeVRAA_2040, markerStylePHENIX62GeV,markerSizePHENIX62GeV, kBlack, kBlack);
			DrawGammaSetMarkerTGraphErr(graphPHENIX39GeVRAA_2040, markerStylePHENIX39GeV,markerSizePHENIX39GeV, kBlack , kBlack);

			graphPHENIX200GeVRAA_2040->Draw("p,same,e1");	
			graphPHENIX39GeVRAA_2040->Draw("p,same,e1");	
			graphPHENIX62GeVRAA_2040->Draw("p,same,e1");	

			graphCombRAASys2760GeVLHC11h_2050->Draw("E2same");
			if(noXerrorBars) ProduceGraphAsymmWithoutXErrors(graphCombRAAStat2760GeVLHC11h_2050);
		graphCombRAAStat2760GeVLHC11h_2050->Draw("p,same,e1");

			TLatex *labelRAAALICEPbPb2040 = new TLatex(0.5,0.87,"#pi^{0} ALICE Pb-Pb (2011)");
			SetStyleTLatex( labelRAAALICEPbPb2040, 0.85*textsizeLabelsRAA,4);
			labelRAAALICEPbPb2040->Draw();
			TLegend* legendRAASinglePbPb2040 = new TLegend(0.5,0.81,0.83,0.85);
			legendRAASinglePbPb2040->SetFillColor(0);
			legendRAASinglePbPb2040->SetLineColor(0);
			legendRAASinglePbPb2040->SetNColumns(1);
			legendRAASinglePbPb2040->SetTextFont(42);
			legendRAASinglePbPb2040->SetTextSize(0.85*textsizeLabelsRAA);
			legendRAASinglePbPb2040->AddEntry(graphCombRAASys2760GeVLHC11h_2050,"20-50% #sqrt{#it{s}_{_{NN}}} = 2.76 TeV","pf");
			legendRAASinglePbPb2040->Draw();

			TLatex *labelRAAPHENIXPbPb2040 = new TLatex(0.5,0.75,"#pi^{0} PHENIX 20-40% Au-Au");
			SetStyleTLatex( labelRAAPHENIXPbPb2040, 0.85*textsizeLabelsRAA,4);
			labelRAAPHENIXPbPb2040->Draw();

			TLegend* legendRAARHICPbPb2040 = new TLegend(0.5,0.55,0.84,0.73);
			legendRAARHICPbPb2040->SetFillColor(0);
			legendRAARHICPbPb2040->SetLineColor(0);
		// 	legendRAARHICPbPb2040->SetNColumns(2);
			legendRAARHICPbPb2040->SetTextFont(42);
			legendRAARHICPbPb2040->SetTextSize(0.85*textsizeLabelsRAA);
			legendRAARHICPbPb2040->AddEntry(graphPHENIX200GeVRAA_2040,"#sqrt{#it{s}_{_{NN}}} = 200 GeV","p");
			legendRAARHICPbPb2040->AddEntry(graphPHENIX62GeVRAA_2040,"#sqrt{#it{s}_{_{NN}}} = 62.4 GeV","p");
			legendRAARHICPbPb2040->AddEntry(graphPHENIX39GeVRAA_2040,"#sqrt{#it{s}_{_{NN}}} = 39 GeV","p");
			legendRAARHICPbPb2040->Draw();

	// 		boxErrorNorm2040_Single->Draw();
			boxErrorNorm2050_Single->Draw();
			DrawGammaLines(0., 19.5 , 1, 1 ,1,kGray);
			
		
		canvasRAAcombo->SaveAs(Form("%s/%s_RAA_combinedwithPHENIX_asPaper_2050.%s",outputDir.Data(),meson.Data(),suffix.Data()));
		canvasRAAcombo->SaveAs(Form("%s/%s_RAA_combinedwithPHENIX_asPaper_2050.%s",paperPlots.Data(),meson.Data(),suffix.Data()));
		
	}

	
	if(meson.CompareTo("Eta")==0){ 	

			canvasRAAcombo->cd();
			histo2DRAAcombo->DrawCopy();
			
			graphCombRAASys2760GeVLHC11h_0010->Draw("E2same");
			if(noXerrorBars) ProduceGraphAsymmWithoutXErrors(graphCombRAAStat2760GeVLHC11h_0010);
		graphCombRAAStat2760GeVLHC11h_0010->Draw("p,same,e1");

			DrawGammaSetMarkerTGraphAsym(graphEtaRAAPhenix0010, 24,2, colorPhenix,colorPhenix, 1, kFALSE);
			DrawGammaSetMarkerTGraphAsym(graphEtaRAAPhenix0010,24,2, colorPhenix,colorPhenix, 1, kTRUE, kGray+2);
			graphEtaRAAPhenix0010->SetFillStyle(1001);
			graphEtaRAAPhenix0010->Draw("2same");
			graphEtaRAAPhenix0010->Draw("p,same"); 
		
			TLegend* legendEtaRAAcomp = new TLegend(0.5,0.73,0.9,0.93);  //0.16,0.05,0.73,0.2);
			legendEtaRAAcomp->SetFillColor(0);
			legendEtaRAAcomp->SetFillStyle(0);
			legendEtaRAAcomp->SetLineColor(0);
			legendEtaRAAcomp->SetTextSize(FontSize);
// 			legendEtaRAAcomp->SetMargin(0.2);
			legendEtaRAAcomp->SetHeader("#eta - 0-10%");
			legendEtaRAAcomp->AddEntry(graphCombRAASys2760GeVLHC11h_0010,"Pb-Pb #sqrt{#it{s}_{_{NN}}} = 2.76 TeV", "pf");
			legendEtaRAAcomp->AddEntry(graphEtaRAAPhenix0010,"Au-Au #sqrt{#it{s}_{_{NN}}} = 200 GeV","pf");
			legendEtaRAAcomp->Draw();
			
			boxErrorNorm0010Only->Draw();		
					
		canvasRAAcombo->SaveAs(Form("%s/%s_RAA_combinedwithPHENIX_0010.%s",outputDir.Data(),meson.Data(),suffix.Data()));
		canvasRAAcombo->SaveAs(Form("%s/%s_RAA_combinedwithPHENIX_0010.%s",paperPlots.Data(),meson.Data(),suffix.Data()));
		
		canvasRAAcombo->cd();
		histo2DRAAcombo->Draw("copy");

			DrawGammaSetMarkerTGraphAsym(graphEtaRAAPhenix2040, 25,2, colorPhenix,colorPhenix, 0.1, kFALSE);
			DrawGammaSetMarkerTGraphAsym(graphEtaRAAPhenix2040,24,2, colorPhenix,colorPhenix, 1, kTRUE,colorPhenix);
			graphEtaRAAPhenix2040->SetFillStyle(3003);
			graphEtaRAAPhenix2040->Draw("2same");
			graphEtaRAAPhenix2040->Draw("p,same"); 

			DrawGammaSetMarkerTGraphAsym(graphEtaRAAPhenix2060, 25,2, colorPhenix,colorPhenix, 0.1, kFALSE);
			DrawGammaSetMarkerTGraphAsym(graphEtaRAAPhenix2060,25,2, colorPhenix,colorPhenix, 1, kTRUE, colorPhenix);
			graphEtaRAAPhenix2060->SetFillStyle(3002);
			graphEtaRAAPhenix2060->Draw("2same");
			graphEtaRAAPhenix2060->Draw("p,same"); 
		
			graphCombRAASys2760GeVLHC11h_2050->Draw("E2same");
			if(noXerrorBars) ProduceGraphAsymmWithoutXErrors(graphCombRAAStat2760GeVLHC11h_2050);
			graphCombRAAStat2760GeVLHC11h_2050->Draw("p,same,e1");

			TLegend* legendEtaRAAcomp1 = new TLegend(0.42,0.73,0.9,0.93);  //0.16,0.05,0.73,0.2);
			legendEtaRAAcomp1->SetFillColor(0);
			legendEtaRAAcomp1->SetFillStyle(0);
			legendEtaRAAcomp1->SetLineColor(0);
			legendEtaRAAcomp1->SetTextSize(FontSize);
		// 	legendEtaRAAcomp1->SetNColumns(2);
// 			legendEtaRAAcomp1->SetMargin(0.2);
			legendEtaRAAcomp1->SetHeader("#eta - semicentral");
			legendEtaRAAcomp1->AddEntry(graphCombRAASys2760GeVLHC11h_2050,"20-50% Pb-Pb #sqrt{#it{s}_{_{NN}}} = 2.76 TeV", "pf");
			legendEtaRAAcomp1->AddEntry(graphEtaRAAPhenix2040,"20-40% Au-Au #sqrt{#it{s}_{_{NN}}} = 200 GeV","pf");
			legendEtaRAAcomp1->AddEntry(graphEtaRAAPhenix2060,"20-60% Au-Au #sqrt{#it{s}_{_{NN}}} = 200 GeV","pf");
			legendEtaRAAcomp1->Draw();
			
			boxErrorNorm2050Only->Draw();
		
		canvasRAAcombo->SaveAs(Form("%s/%s_RAA_combinedwithPHENIX_2050.%s",outputDir.Data(),meson.Data(),suffix.Data()));
		canvasRAAcombo->SaveAs(Form("%s/%s_RAA_combinedwithPHENIX_2050.%s",paperPlots.Data(),meson.Data(),suffix.Data()));
		
	}
	
	// loop for all the measurements from published paper:
	if(meson.CompareTo("Pi0")==0){ 
		//**********************************************************************************************************************//
		//***************************** Assuming maximal correlation - all the measurements ************************************//
		//**********************************************************************************************************************//
				
		TGraph* graphWeightsAAll_0010[11];
		TGraph* graphWeightsAAll_2040[11];
		for (Int_t i = 0; i< 11; i++){
				graphWeightsAAll_0010[i] = NULL;
				graphWeightsAAll_2040[i] = NULL;
		}       

		TString fileNameOutputWeightingAAll_0010                                           = Form("%s/0010All_WeightingMethodA%s.dat",outputDir.Data(),meson.Data());
		TString fileNameOutputWeightingAAll_2040                                           = Form("%s/2040All_WeightingMethodA%s.dat",outputDir.Data(),meson.Data());

		TGraphAsymmErrors* graphCombInvYieldStat2760GeVAAll_0010   = NULL;
		TGraphAsymmErrors* graphCombInvYieldSys2760GeVAAll_0010    = NULL;
		TGraphAsymmErrors* graphCombInvYieldStat2760GeVAAll_2040   = NULL;
		TGraphAsymmErrors* graphCombInvYieldSys2760GeVAAll_2040    = NULL;
		TGraphAsymmErrors* graphCombInvYieldTot2760GeVAAll_0010    = NULL;
		TGraphAsymmErrors* graphCombInvYieldTot2760GeVAAll_2040    = NULL;
		
		// Declaration & calculation of combined spectrum
		graphCombInvYieldTot2760GeVAAll_0010       = CombinePtPointsSpectraFullCorrMat( statErrorCollection_0010, sysErrorCollection_0010,
																						xPtLimitsPi0, 23, offSetsPi0, offSetsPi0Sys,
																						graphCombInvYieldStat2760GeVAAll_0010, graphCombInvYieldSys2760GeVAAll_0010,
																						fileNameOutputWeightingAAll_0010,1 );

		graphCombInvYieldTot2760GeVAAll_2040       = CombinePtPointsSpectraFullCorrMat( statErrorCollection_2040, sysErrorCollection_2040,
																						   xPtLimitsPi0, 23, offSetsPi0, offSetsPi0Sys,
																						   graphCombInvYieldStat2760GeVAAll_2040, graphCombInvYieldSys2760GeVAAll_2040,
																						   fileNameOutputWeightingAAll_2040,1 );

		graphCombInvYieldStat2760GeVAAll_0010->RemovePoint(0);
		graphCombInvYieldSys2760GeVAAll_0010->RemovePoint(0);
		graphCombInvYieldTot2760GeVAAll_0010->RemovePoint(0);

		graphCombInvYieldStat2760GeVAAll_2040->RemovePoint(0);
		graphCombInvYieldSys2760GeVAAll_2040->RemovePoint(0);
		graphCombInvYieldTot2760GeVAAll_2040->RemovePoint(0);

		// Reading weights from output file for plotting
		ifstream fileWeightsReadAAll_0010;
		fileWeightsReadAAll_0010.open(fileNameOutputWeightingAAll_0010,ios_base::in);
		ifstream fileWeightsReadAAll_2040;
		fileWeightsReadAAll_2040.open(fileNameOutputWeightingAAll_2040,ios_base::in);
		cout << "reading" << fileNameOutputWeightingAAll_0010 << " and " << fileNameOutputWeightingAAll_2040 << endl;
		Double_t xValuesReadAAll_0010[50];
		Double_t weightsReadAAll_0010[11][50];
		Int_t availableMeasAAll_0010[11] = {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1};
		Double_t xValuesReadAAll_2040[50];
		Double_t weightsReadAAll_2040[11][50];
		Int_t availableMeasAAll_2040[11] = {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1};

		Int_t nMeasSetAAll                 = 3;
		Int_t nPtBinsReadAAll              = 0;
		while(!fileWeightsReadAAll_0010.eof() && nPtBinsReadAAll < 50){
				TString garbage = "";
				if (nPtBinsReadAAll == 0){
						fileWeightsReadAAll_0010 >> garbage ;//>> availableMeas[0] >> availableMeas[1] >> availableMeas[2] >> availableMeas[3];
						fileWeightsReadAAll_2040 >> garbage ;
						for (Int_t i = 0; i < nMeasSetAAll; i++){
								fileWeightsReadAAll_0010 >> availableMeasAAll_0010[i] ;
								fileWeightsReadAAll_2040 >> availableMeasAAll_2040[i] ;
						}       
						cout << "read following measurements: "; 
						for (Int_t i = 0; i < 11; i++){
								cout << availableMeasAAll_0010[i] << "\t" ;
								cout << availableMeasAAll_2040[i] << "\t" ;
						}       
						cout << endl;
				} else {
						fileWeightsReadAAll_0010 >> xValuesReadAAll_0010[nPtBinsReadAAll-1];
						fileWeightsReadAAll_2040 >> xValuesReadAAll_2040[nPtBinsReadAAll-1];
						for (Int_t i = 0; i < nMeasSetAAll; i++){
								fileWeightsReadAAll_0010 >> weightsReadAAll_0010[availableMeasAAll_0010[i]][nPtBinsReadAAll-1] ;
								fileWeightsReadAAll_2040 >> weightsReadAAll_2040[availableMeasAAll_2040[i]][nPtBinsReadAAll-1] ;
						}       
						cout << "read: "<<  nPtBinsReadAAll << "\t"<< xValuesReadAAll_0010[nPtBinsReadAAll-1] << "\t" ;
						cout << "read: "<<  nPtBinsReadAAll << "\t"<< xValuesReadAAll_2040[nPtBinsReadAAll-1] << "\t" ;
						for (Int_t i = 0; i < nMeasSetAAll; i++){
								cout << weightsReadAAll_0010[availableMeasAAll_0010[i]][nPtBinsReadAAll-1] << "\t";
								cout << weightsReadAAll_2040[availableMeasAAll_2040[i]][nPtBinsReadAAll-1] << "\t";
						}
						cout << endl;
				}
				nPtBinsReadAAll++;
		}
		nPtBinsReadAAll = nPtBinsReadAAll-2 ;
		fileWeightsReadAAll_0010.close();
		fileWeightsReadAAll_2040.close();

		for (Int_t i = 0; i < nMeasSetAAll; i++){
				graphWeightsAAll_0010[availableMeasAAll_0010[i]] = new TGraph(nPtBinsReadAAll,xValuesReadAAll_0010,weightsReadAAll_0010[availableMeasAAll_0010[i]]);
				graphWeightsAAll_2040[availableMeasAAll_2040[i]] = new TGraph(nPtBinsReadAAll,xValuesReadAAll_2040,weightsReadAAll_2040[availableMeasAAll_2040[i]]);
				Int_t bin = 0;
				for (Int_t n = 0; n< nPtBinsReadAAll; n++){
						if (graphWeightsAAll_0010[availableMeasAAll_0010[i]]->GetY()[bin] == 0 && graphWeightsAAll_2040[availableMeasAAll_2040[i]]->GetY()[bin] == 0){
								graphWeightsAAll_0010[availableMeasAAll_0010[i]]->RemovePoint(bin);
								graphWeightsAAll_2040[availableMeasAAll_2040[i]]->RemovePoint(bin);
						} else bin++;
				}       
		}       

		

		////	**********************************************************************************************************************
		////	******************************************* Calculation of spectrum all measurements *********************************
		////	**********************************************************************************************************************
								
		TGraph* graphWeightsAll_0010[11];
		TGraph* graphWeightsAll_2040[11];
		for (Int_t i = 0; i< 11; i++){
			graphWeightsAll_0010[i] = NULL;
			graphWeightsAll_2040[i] = NULL;
		}	

		// Declaration & calculation of combined spectrum
		TString fileNameOutputWeightingAll_0010					= Form("%s/0010All_WeightingEMCal%s.dat",outputDir.Data(),meson.Data());
		TString fileNameOutputWeightingAll_2040					= Form("%s/2040All_WeightingEMCal%s.dat",outputDir.Data(),meson.Data());
		
		TGraphAsymmErrors* graphCombInvYieldStat2760GeVAll_0010 = NULL;
		TGraphAsymmErrors* graphCombInvYieldSys2760GeVAll_0010  = NULL;
		TGraphAsymmErrors* graphCombInvYieldTot2760GeVAll_0010 = NULL;
		
		TGraphAsymmErrors* graphCombInvYieldStat2760GeVAll_2040 = NULL;
		TGraphAsymmErrors* graphCombInvYieldSys2760GeVAll_2040 = NULL;
		TGraphAsymmErrors* graphCombInvYieldTot2760GeVAll_2040 = NULL;
		
		cout << "******************************************* calculating the 0-10% combined spectra *******************************************\n\n\n" << endl;
		graphCombInvYieldTot2760GeVAll_0010  = CombinePtPointsSpectraFullCorrMat( statErrorCollection_0010,	sysErrorCollection_0010, 	
																						xPtLimitsPi0, 21,
																						offSetsPi0, offSetsPi0Sys,
																						graphCombInvYieldStat2760GeVAll_0010, graphCombInvYieldSys2760GeVAll_0010,
																						fileNameOutputWeightingAll_0010, 1);
		cout << "******************************************* calculating the 20-40% combined spectra *******************************************\n\n\n" << endl;
		graphCombInvYieldTot2760GeVAll_2040 = CombinePtPointsSpectraFullCorrMat(  statErrorCollection_2040,	sysErrorCollection_2040, 	
																						xPtLimitsPi0, 21,
																						offSetsPi0, offSetsPi0Sys,
																						graphCombInvYieldStat2760GeVAll_2040, graphCombInvYieldSys2760GeVAll_2040,
																						fileNameOutputWeightingAll_2040, 1);
		graphCombInvYieldStat2760GeVAll_0010->RemovePoint(0);
		graphCombInvYieldSys2760GeVAll_0010->RemovePoint(0);

		graphCombInvYieldStat2760GeVAll_2040->RemovePoint(0);
		graphCombInvYieldSys2760GeVAll_2040->RemovePoint(0);

		graphCombInvYieldTot2760GeVAll_0010->RemovePoint(0);
		graphCombInvYieldTot2760GeVAll_2040->RemovePoint(0);

// 		cout << "graphCombInvYieldStat2760GeVAll_0010" << endl;
// 		graphCombInvYieldStat2760GeVAll_0010->Print();
// 		cout << "graphCombInvYieldSys2760GeVAll_0010" << endl;
// 		graphCombInvYieldSys2760GeVAll_0010->Print();
// 
// 		cout << "graphCombInvYieldStat2760GeVAll_2040" << endl;
// 		graphCombInvYieldStat2760GeVAll_2040->Print();
// 		cout << "graphCombInvYieldSys2760GeVAll_2040" << endl;
// 		graphCombInvYieldSys2760GeVAll_2040->Print();
// 
// 		cout << "graphCombInvYieldTot2760GeVAll_0010" << endl;
// 		graphCombInvYieldTot2760GeVAll_0010->Print();
// 		cout << "graphCombInvYieldTot2760GeVAll_2040" << endl;
// 		graphCombInvYieldTot2760GeVAll_2040->Print();

			
		// Reading weights from output file for plotting
		ifstream fileWeightsReadAll_0010;
		fileWeightsReadAll_0010.open(fileNameOutputWeightingAll_0010,ios_base::in);
		ifstream fileWeightsReadAll_2040;
		fileWeightsReadAll_2040.open(fileNameOutputWeightingAll_2040,ios_base::in);

		cout << "reading " << fileNameOutputWeightingAll_0010 << " and " << fileNameOutputWeightingAll_2040 << endl;
		Double_t xValuesReadAll_0010[50];
		Double_t xValuesReadAll_2040[50];
		Double_t weightsReadAll_0010[11][50];
		Double_t weightsReadAll_2040[11][50];
		Int_t availableMeasAll_0010[11] = {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1};
		Int_t availableMeasAll_2040[11] = {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1};
			
		Int_t nMeasSetAll 			= 3;
		Int_t nPtBinsReadAll 		= 0;
		while(!fileWeightsReadAll_0010.eof() && nPtBinsReadAll < 50){
			TString garbage = "";
			if (nPtBinsReadAll == 0){
				fileWeightsReadAll_0010 >> garbage;
				fileWeightsReadAll_2040 >> garbage;
				for (Int_t i = 0; i < nMeasSetAll; i++){
					fileWeightsReadAll_0010 >> availableMeasAll_0010[i];
					fileWeightsReadAll_2040 >> availableMeasAll_2040[i] ;
				}	
				cout << "read following measurements: "; 
				for (Int_t i = 0; i < 11; i++){
					cout << availableMeasAll_0010[i] << "\t" ;
					cout << availableMeasAll_2040[i] << "\t" ;
				}	
				cout << endl;
			} else {
				fileWeightsReadAll_0010 >> xValuesReadAll_0010[nPtBinsReadAll-1];
				fileWeightsReadAll_2040 >> xValuesReadAll_2040[nPtBinsReadAll-1];
				for (Int_t i = 0; i < nMeasSetAll; i++){
					fileWeightsReadAll_0010 >> weightsReadAll_0010[availableMeasAll_0010[i]][nPtBinsReadAll-1] ;
					fileWeightsReadAll_2040 >> weightsReadAll_2040[availableMeasAll_2040[i]][nPtBinsReadAll-1] ;
				}	
				cout << "read: "<<  nPtBinsReadAll << "\t"<< xValuesReadAll_0010[nPtBinsReadAll-1] << "\t" ;
				cout << "read: "<<  nPtBinsReadAll << "\t"<< xValuesReadAll_2040[nPtBinsReadAll-1] << "\t" ;
				for (Int_t i = 0; i < nMeasSetAll; i++){
					cout << weightsReadAll_0010[availableMeasAll_0010[i]][nPtBinsReadAll-1] << "\t";
					cout << weightsReadAll_2040[availableMeasAll_2040[i]][nPtBinsReadAll-1] << "\t";
				}
				cout << endl;
			}
			nPtBinsReadAll++;
		}
		nPtBinsReadAll = nPtBinsReadAll-2 ;
		fileWeightsReadAll_0010.close();
		fileWeightsReadAll_2040.close();

		for (Int_t i = 0; i < nMeasSetAll; i++){
			graphWeightsAll_0010[availableMeasAll_0010[i]] = new TGraph(nPtBinsReadAll,xValuesReadAll_0010,weightsReadAll_0010[availableMeasAll_0010[i]]);
			graphWeightsAll_2040[availableMeasAll_2040[i]] = new TGraph(nPtBinsReadAll,xValuesReadAll_2040,weightsReadAll_2040[availableMeasAll_2040[i]]);
			Int_t bin = 0;
			for (Int_t n = 0; n< nPtBinsReadAll; n++){
				if (graphWeightsAll_0010[availableMeasAll_0010[i]]->GetY()[bin] == 0 && graphWeightsAll_2040[availableMeasAll_2040[i]]->GetY()[bin] == 0){
						graphWeightsAll_0010[availableMeasAll_0010[i]]->RemovePoint(bin);
						graphWeightsAll_2040[availableMeasAll_2040[i]]->RemovePoint(bin);
				} else bin++;

			}	
		}	

		////	**********************************************************************************************************************
		////	*************************************** Plotting weights method all measurements *************************************
		////	**********************************************************************************************************************
		canvasWeights->cd();
		histo2DWeights->Draw("copy");

		TLegend* legendAccWeightsAll = GetAndSetLegend2(0.12, 0.14, 0.45, 0.14+(0.06*nMeasSetAll*1.35), 32);
		for (Int_t i = 0; i < nMeasSetAll; i++){
			DrawGammaSetMarkerTGraph(graphWeightsAll_0010[availableMeasAll_0010[i]],
									markerStyleDet[availableMeasAll_0010[i]], 
									markerSizeDet[availableMeasAll_0010[i]]*0.5, 
									colorDet[availableMeasAll_0010[i]] , 
									colorDet[availableMeasAll_0010[i]]);
			graphWeightsAll_0010[availableMeasAll_0010[i]]->Draw("p,same,e1");
			legendAccWeightsAll->AddEntry(graphWeightsAll_0010[availableMeasAll_0010[i]],nameMeasGlobal[availableMeasAll_0010[i]],"p");
			
			DrawGammaSetMarkerTGraph(graphWeightsAll_2040[availableMeasAll_2040[i]],
									markerStyleDet[availableMeasAll_2040[i]], 
									markerSizeDet[availableMeasAll_2040[i]]*0.5, 
									colorDet[availableMeasAll_2040[i]]+1, 
									colorDet[availableMeasAll_2040[i]]+1);
			graphWeightsAll_2040[availableMeasAll_2040[i]]->Draw("p,same,e1");
			legendAccWeightsAll->AddEntry(graphWeightsAll_2040[availableMeasAll_2040[i]],nameMeasGlobal[availableMeasAll_2040[i]],"p");
		}	
		legendAccWeightsAll->Draw();
		labelWeightsEnergy->Draw();
		labelWeightsPi0->Draw();

	//	DrawGammaLines(0.23, 70. , 0.8, 0.8,0.1, kGray, 3);
		DrawGammaLines(0.23, 70. , 0.5, 0.5,0.1, kGray, 7);
		DrawGammaLines(0.23, 70. , 0.4, 0.4,0.1, kGray, 1);
		DrawGammaLines(0.23, 70. , 0.3, 0.3,0.1, kGray, 7);
		DrawGammaLines(0.23, 70. , 0.2, 0.2,0.1, kGray, 3);
			
// 		canvasWeights->SaveAs(Form("%s/%s_Weights_All.%s",outputDir.Data(),meson.Data(),suffix.Data()));

			
		TH1D* statErrorRelCollectionAll_0010[11];
		TH1D* statErrorRelCollectionAll_2040[11];
		TH1D* statErrorRelCollectionAllRaa_0010[11];
		TH1D* statErrorRelCollectionAllRaa_2040[11];

		for (Int_t i = 0; i< 11; i++){
			statErrorRelCollectionAll_0010[i] = NULL;
			statErrorRelCollectionAll_2040[i] = NULL;

			statErrorRelCollectionAllRaa_0010[i] = NULL;
			statErrorRelCollectionAllRaa_2040[i] = NULL;
		}	
		for (Int_t i = 0; i < 11; i++){
			if (statErrorCollection_0010[i]) statErrorRelCollectionAll_0010[i] = CalculateRelErrUpTH1D( statErrorCollection_0010[i], Form("relativeStatErrorAll_%s_0010", nameMeasGlobal[i].Data()));
			
			if (statErrorCollection_2040[i]) statErrorRelCollectionAll_2040[i] = CalculateRelErrUpTH1D( statErrorCollection_2040[i], Form("relativeStatErrorAll_%s_2040", nameMeasGlobal[i].Data()));

			if(i == 0 || i == 10){
				if (statErrorCollectionRaa_0010[i]) statErrorRelCollectionAllRaa_0010[i] = CalculateRelErrUpTH1D( statErrorCollectionRaa_0010[i], Form("relativeStatErrorAllRaa_%s_0010", nameMeasGlobal[i].Data()));			
				if (statErrorCollectionRaa_2040[i]) statErrorRelCollectionAllRaa_2040[i] = CalculateRelErrUpTH1D( statErrorCollectionRaa_2040[i], Form("relativeStatErrorAllRaa_%s_2040", nameMeasGlobal[i].Data()));
			}
		}
		TGraphAsymmErrors* sysErrorRelCollectionAll_0010[11];
		TGraphAsymmErrors* sysErrorRelCollectionAll_2040[11];

		TGraphAsymmErrors* sysErrorRelCollectionAllRaa_0010[11];
		TGraphAsymmErrors* sysErrorRelCollectionAllRaa_2040[11];

		for (Int_t i = 0; i< 11; i++){
			sysErrorRelCollectionAll_0010[i] = NULL;
			sysErrorRelCollectionAll_2040[i] = NULL;

			sysErrorRelCollectionAllRaa_0010[i] = NULL;
			sysErrorRelCollectionAllRaa_2040[i] = NULL;
		}	
		for (Int_t i = 0; i < 11; i++){
			if (sysErrorCollection_0010[i]) sysErrorRelCollectionAll_0010[i] = CalculateRelErrUpAsymmGraph( sysErrorCollection_0010[i], Form("relativeSysErrorAll_%s_0010", nameMeasGlobal[i].Data()));
			
			if (sysErrorCollection_2040[i]) sysErrorRelCollectionAll_2040[i] = CalculateRelErrUpAsymmGraph( sysErrorCollection_2040[i], Form("relativeSysErrorAll_%s_2040", nameMeasGlobal[i].Data()));				

			if(i == 0 || i == 10){
				
			if (sysErrorCollectionRaa_0010[i]) sysErrorRelCollectionAllRaa_0010[i] = CalculateRelErrUpAsymmGraph( sysErrorCollectionRaa_0010[i], Form("relativeSysErrorAllRaa_%s_0010", nameMeasGlobal[i].Data()));
			
			if (sysErrorCollectionRaa_2040[i]) sysErrorRelCollectionAllRaa_2040[i] = CalculateRelErrUpAsymmGraph( sysErrorCollectionRaa_2040[i], Form("relativeSysErrorAllRaa_%s_2040", nameMeasGlobal[i].Data()));				

				
			}
			
		}
		


		// 	*********************************************************************************************************************
		// 	******************************* Visualize relative errors - all measurements ****************************************
		// 	*********************************************************************************************************************
		
		TCanvas* canvasRelSysErrAll = new TCanvas("canvasRelSysErrAll","",200,10,1350,900);  // gives the page size
		DrawGammaCanvasSettings( canvasRelSysErrAll, 0.08, 0.02, 0.035, 0.09);
		canvasRelSysErrAll->SetLogx();

			TH2F * histo2DRelSysErrAll;
			histo2DRelSysErrAll = new TH2F("histo2DRelSysErrAll","histo2DRelSysErrAll",11000,0.23,70.,1000,0,80.5);
			SetStyleHistoTH2ForGraphs(histo2DRelSysErrAll, "#it{p}_{T} (GeV/#it{c})","sys Err (%)",0.035,0.04, 0.035,0.04, 1.,1.);
			histo2DRelSysErrAll->GetXaxis()->SetMoreLogLabels();
			histo2DRelSysErrAll->GetXaxis()->SetLabelOffset(-0.01);
			histo2DRelSysErrAll->Draw("copy");	
			
			TLegend* legendRelSysErrAll = GetAndSetLegend2(0.62, 0.94-(0.06*nMeasSetAll*1.35), 0.95, 0.94, 32);
			for (Int_t i = 0; i < nMeasSetAll; i++){
				DrawGammaSetMarkerTGraph(sysErrorRelCollectionAll_0010[availableMeasAll_0010[i]], markerStyleDet[availableMeasAll_0010[i]], 
											markerSizeDet[availableMeasAll_0010[i]]*0.5, 	
											colorDet[availableMeasAll_0010[i]], colorDet[availableMeasAll_0010[i]]);
				sysErrorRelCollectionAll_0010[availableMeasAll_0010[i]]->Draw("p,same,e1");
				legendRelSysErrAll->AddEntry(sysErrorRelCollectionAll_0010[availableMeasAll_0010[i]],nameMeasGlobal[availableMeasAll_0010[i]],"p");

				DrawGammaSetMarkerTGraph(sysErrorRelCollectionAll_2040[availableMeasAll_2040[i]], markerStyleDet[availableMeasAll_2040[i]],
											markerSizeDet[availableMeasAll_2040[i]]*0.5, 
											colorDet[availableMeasAll_2040[i]]+1, colorDet[availableMeasAll_2040[i]]+1);	
				sysErrorRelCollectionAll_2040[availableMeasAll_2040[i]]->Draw("p,same,e1");
				legendRelSysErrAll->AddEntry(sysErrorRelCollectionAll_2040[availableMeasAll_2040[i]],nameMeasGlobal[availableMeasAll_2040[i]],"p");
			}
			legendRelSysErrAll->Draw();
			labelRelSysErrEnergy->Draw();
				
			if(meson.CompareTo("Pi0")==0){
				labelRelSysErrPi0= new TLatex(0.7,0.83,"#pi^{0} #rightarrow #gamma#gamma");
			} else if(meson.CompareTo("Eta")==0){
				labelRelSysErrPi0= new TLatex(0.7,0.83,"#eta #rightarrow #gamma#gamma");
			}
			SetStyleTLatex( labelRelSysErrPi0, 0.85*textSizeLabelsPixel,4);
			labelRelSysErrPi0->SetTextFont(43);
			labelRelSysErrPi0->Draw();
		
// 		canvasRelSysErrAll->SaveAs(Form("%s/%s_RelSysErrAll.%s",outputDir.Data(),meson.Data(),suffix.Data()));
			
			histo2DRelSysErrAll->GetYaxis()->SetRangeUser(0,30.5);
			histo2DRelSysErrAll->Draw("copy");	

			for (Int_t i = 0; i < nMeasSetAll; i++){
				sysErrorRelCollectionAll_0010[availableMeasAll_0010[i]]->Draw("p,same,e1");
				sysErrorRelCollectionAll_2040[availableMeasAll_2040[i]]->Draw("p,same,e1");								
				
			}	
			legendRelSysErrAll->Draw();
			labelRelSysErrEnergy->Draw();
			labelRelSysErrPi0->Draw();

// 		canvasRelSysErrAll->SaveAs(Form("%s/%s_RelSysErrZoomedAll.%s",outputDir.Data(),meson.Data(), suffix.Data()));
			
		
//======================================== 2010 and 2011 PCM only  ===============================================
		histo2DRelSysErrAll->GetYaxis()->SetRangeUser(0,80.5);
		histo2DRelSysErrAll->GetXaxis()->SetRangeUser(0.2,20);
		histo2DRelSysErrAll->Draw("copy");	
		
			DrawGammaSetMarkerTGraph(sysErrorRelCollectionAll_0010[0], 20, 2, kRed, kRed);
			DrawGammaSetMarkerTGraph(sysErrorRelCollectionAll_0010[10], 24, 2, colorCombo0010 , colorCombo0010);
			
			DrawGammaSetMarkerTGraph(sysErrorRelCollectionAll_2040[0], 21, 2, kAzure-2, kAzure-2);
			DrawGammaSetMarkerTGraph(sysErrorRelCollectionAll_2040[10], 25, 2, colorEMCal2050 , colorEMCal2050);

			sysErrorRelCollectionAll_0010[10]->RemovePoint(0);
			sysErrorRelCollectionAll_2040[10]->RemovePoint(0);
			sysErrorRelCollectionAll_2040[10]->RemovePoint(sysErrorRelCollectionAll_2040[10]->GetN()-1);
			
			sysErrorRelCollectionAll_0010[0]->Draw("p,same,e1");
			sysErrorRelCollectionAll_0010[10]->Draw("p,same,e1");
			sysErrorRelCollectionAll_2040[0]->Draw("p,same,e1");
			sysErrorRelCollectionAll_2040[10]->Draw("p,same,e1");

			TLegend* legendRelSysErr20102011 = GetAndSetLegend2(0.12, 0.96-(0.06*nMeasSetAll*1.35), 0.45, 0.96, 32);
// 			legendRelSysErr20102011->SetFillStyle(1001);
			legendRelSysErr20102011->AddEntry(sysErrorRelCollectionAll_0010[0],"PCM 2011 - 0-10%","p");
			legendRelSysErr20102011->AddEntry(sysErrorRelCollectionAll_0010[10],"PCM 2010 - 0-10%","p");
			legendRelSysErr20102011->AddEntry(sysErrorRelCollectionAll_2040[0],"PCM 2011 - 20-40%","p");
			legendRelSysErr20102011->AddEntry(sysErrorRelCollectionAll_2040[10],"PCM 2010 - 20-40%","p");
			
			legendRelSysErr20102011->Draw();
			labelRelSysErrEnergy->Draw();
// 			labelRelSysErrPi0->Draw();
			
		canvasRelSysErrAll->SaveAs(Form("%s/%s_RelSysErr2010and2011.%s",outputDir.Data(),meson.Data(),suffix.Data()));

		
		TH2F * histo2DRelSysErrAllRaa;
		histo2DRelSysErrAllRaa = new TH2F("histo2DRelSysErrAllRaa","histo2DRelSysErrAllRaa",11000,0.23,70.,1000,0,80.5);
		SetStyleHistoTH2ForGraphs(histo2DRelSysErrAllRaa, "#it{p}_{T} (GeV/#it{c})","#it{R}_{AA} sys Err (%)",0.035,0.04, 0.035,0.04, 1.,1.);
		histo2DRelSysErrAllRaa->GetXaxis()->SetMoreLogLabels();
		histo2DRelSysErrAllRaa->GetXaxis()->SetLabelOffset(-0.01);
		histo2DRelSysErrAllRaa->GetYaxis()->SetRangeUser(0,80.5);
		histo2DRelSysErrAllRaa->GetXaxis()->SetRangeUser(0.2,20);
		histo2DRelSysErrAllRaa->Draw("copy");	
		
			DrawGammaSetMarkerTGraph(sysErrorRelCollectionAllRaa_0010[0], 20, 2, kRed, kRed);
			DrawGammaSetMarkerTGraph(sysErrorRelCollectionAllRaa_0010[10], 24, 2, colorCombo0010 , colorCombo0010);
			
			DrawGammaSetMarkerTGraph(sysErrorRelCollectionAllRaa_2040[0], 21, 2, kAzure-2, kAzure-2);
			DrawGammaSetMarkerTGraph(sysErrorRelCollectionAllRaa_2040[10], 25, 2, colorEMCal2050 , colorEMCal2050);

			sysErrorRelCollectionAllRaa_2040[10]->RemovePoint(sysErrorRelCollectionAllRaa_2040[10]->GetN()-1);

			sysErrorRelCollectionAllRaa_0010[0]->Draw("p,same,e1");
			sysErrorRelCollectionAllRaa_0010[10]->Draw("p,same,e1");
			sysErrorRelCollectionAllRaa_2040[0]->Draw("p,same,e1");
			sysErrorRelCollectionAllRaa_2040[10]->Draw("p,same,e1");
			
			legendRelSysErr20102011->Draw();
			labelRelSysErrEnergy->Draw();
// 			labelRelSysErrPi0->Draw();
			
		canvasRelSysErrAll->SaveAs(Form("%s/%s_RaaRelSysErr2010and2011.%s",outputDir.Data(),meson.Data(),suffix.Data()));

		
		
			
	//// 	*********************************************************************************************************************
	//// 	******************************* Visualize relative errors all measurements ******************************************
	//// 	*********************************************************************************************************************
		
		TCanvas* canvasRelStatErrAll = new TCanvas("canvasRelStatErrAll","",200,10,1350,900);  // gives the page size
			DrawGammaCanvasSettings( canvasRelStatErrAll, 0.08, 0.02, 0.035, 0.09);
			canvasRelStatErrAll->SetLogx();
			
			TH2F * histo2DRelStatErrAll;
			histo2DRelStatErrAll = new TH2F("histo2DRelStatErrAll","histo2DRelStatErrAll",11000,0.23,70.,1000,0,80.5);
			SetStyleHistoTH2ForGraphs(histo2DRelStatErrAll, "#it{p}_{T} (GeV/#it{c})","stat Err (%)",0.035,0.04, 0.035,0.04, 1.,1.);
			histo2DRelStatErrAll->GetXaxis()->SetMoreLogLabels();
			histo2DRelStatErrAll->GetXaxis()->SetLabelOffset(-0.01);
			histo2DRelStatErrAll->Draw("copy");	

		
			TLegend* legendRelStatErrAll = GetAndSetLegend2(0.14, 0.94-(0.06*nMeasSetAll*1.35), 0.45, 0.94, 32);
			for (Int_t i = 0; i < nMeasSetAll; i++){
				DrawGammaSetMarker(statErrorRelCollectionAll_0010[availableMeasAll_0010[i]], 
								markerStyleDet[availableMeasAll_0010[i]], markerSizeDet[availableMeasAll_0010[i]]*0.5, 
								colorDet[availableMeasAll_0010[i]] , colorDet[availableMeasAll_0010[i]]);
				statErrorRelCollectionAll_0010[availableMeasAll_0010[i]]->Draw("p,same,e1");
				legendRelStatErrAll->AddEntry(statErrorRelCollectionAll_0010[availableMeasAll_0010[i]],nameMeasGlobal[availableMeasAll_0010[i]],"p");
				
				DrawGammaSetMarker(statErrorRelCollectionAll_2040[availableMeasAll_2040[i]], 
								markerStyleDet[availableMeasAll_2040[i]], markerSizeDet[availableMeasAll_2040[i]]*0.5, 
								colorDet[availableMeasAll_2040[i]]+1, colorDet[availableMeasAll_2040[i]]+1);
				statErrorRelCollectionAll_2040[availableMeasAll_2040[i]]->Draw("p,same,e1");
				legendRelStatErrAll->AddEntry(statErrorRelCollectionAll_2040[availableMeasAll_2040[i]],nameMeasGlobal[availableMeasAll_2040[i]],"p");		
			}	
			legendRelStatErrAll->Draw();

			labelRelStatErrEnergy->Draw();
			if(meson.CompareTo("Pi0")==0){
				labelRelStatErrPi0= new TLatex(0.7,0.83,"#pi^{0} #rightarrow #gamma#gamma");
			} else if(meson.CompareTo("Eta")==0){
				labelRelStatErrPi0= new TLatex(0.7,0.83,"#eta #rightarrow #gamma#gamma");
			}
			SetStyleTLatex( labelRelStatErrPi0, 0.85*textSizeLabelsPixel,4);
			labelRelStatErrPi0->SetTextFont(43);
			labelRelStatErrPi0->Draw();
				
// 		canvasRelStatErrAll->SaveAs(Form("%s/%s_RelStatErrAll.%s",outputDir.Data(),meson.Data(),suffix.Data()));

			histo2DRelStatErrAll->GetYaxis()->SetRangeUser(0,30.5);
			histo2DRelStatErrAll->Draw("copy");	
				for (Int_t i = 0; i < nMeasSetAll; i++){
					statErrorRelCollectionAll_0010[availableMeasAll_0010[i]]->Draw("p,same,e1");
					statErrorRelCollectionAll_2040[availableMeasAll_2040[i]]->Draw("p,same,e1");
				}	
				legendRelStatErrAll->Draw();

				labelRelStatErrEnergy->Draw();
				labelRelStatErrPi0->Draw();
				
// 		canvasRelStatErrAll->SaveAs(Form("%s/%s_RelStatErrZoomedAll.%s",outputDir.Data(),meson.Data(),suffix.Data()));
		
//======================================== 2010 and 2011 PCM only  ===============================================
		histo2DRelStatErrAll->GetYaxis()->SetRangeUser(0,60.5);
		histo2DRelStatErrAll->GetXaxis()->SetRangeUser(0.2,20);
		histo2DRelStatErrAll->Draw("copy");	
		
			DrawGammaSetMarker(statErrorRelCollectionAll_0010[0], 20, 2, kRed, kRed);
			DrawGammaSetMarker(statErrorRelCollectionAll_0010[10], 24, 2, colorCombo0010 , colorCombo0010);
			
			DrawGammaSetMarker(statErrorRelCollectionAll_2040[0], 21, 2, kAzure-2, kAzure-2);
			DrawGammaSetMarker(statErrorRelCollectionAll_2040[10],25, 2, colorEMCal2050 , colorEMCal2050);

			statErrorRelCollectionAll_0010[0]->Draw("p,same,e1");
			statErrorRelCollectionAll_0010[10]->Draw("p,same,e1");
			statErrorRelCollectionAll_2040[0]->Draw("p,same,e1");
			statErrorRelCollectionAll_2040[10]->Draw("p,same,e1");

			TLegend* legendRelStatErr20102011 = GetAndSetLegend2(0.12, 0.96-(0.06*nMeasSetAll*1.35), 0.45, 0.96, 32);
			legendRelStatErr20102011->SetFillStyle(1001);
			legendRelStatErr20102011->AddEntry(statErrorRelCollectionAll_0010[0],"PCM 2011 - 0-10%","p");
			legendRelStatErr20102011->AddEntry(statErrorRelCollectionAll_0010[10],"PCM 2010 - 0-10%","p");
			legendRelStatErr20102011->AddEntry(statErrorRelCollectionAll_2040[0],"PCM 2011 - 20-40%","p");
			legendRelStatErr20102011->AddEntry(statErrorRelCollectionAll_2040[10],"PCM 2010 - 20-40%","p");
			
			legendRelStatErr20102011->Draw();
			labelRelStatErrEnergy->Draw();
// 			labelRelStatErrPi0->Draw();
			
		canvasRelStatErrAll->SaveAs(Form("%s/%s_RelStatErr2010and2011.%s",outputDir.Data(),meson.Data(),suffix.Data()));

		
		TH2F * histo2DRelStatErrAllRaa;
		histo2DRelStatErrAllRaa = new TH2F("histo2DRelStatErrAllRaa","histo2DRelStatErrAllRaa",11000,0.23,70.,1000,0,80.5);
		SetStyleHistoTH2ForGraphs(histo2DRelStatErrAllRaa, "#it{p}_{T} (GeV/#it{c})","#it{R}_{AA} stat Err (%)",0.035,0.04, 0.035,0.04, 1.,1.);
		histo2DRelStatErrAllRaa->GetXaxis()->SetMoreLogLabels();
		histo2DRelStatErrAllRaa->GetXaxis()->SetLabelOffset(-0.01);
		histo2DRelStatErrAllRaa->GetYaxis()->SetRangeUser(0,60.5);
		histo2DRelStatErrAllRaa->GetXaxis()->SetRangeUser(0.2,20);
		histo2DRelStatErrAllRaa->Draw("copy");	
		
			DrawGammaSetMarker(statErrorRelCollectionAllRaa_0010[0], 20, 2, kRed, kRed);
			DrawGammaSetMarker(statErrorRelCollectionAllRaa_0010[10], 24, 2, colorCombo0010 , colorCombo0010);
			
			DrawGammaSetMarker(statErrorRelCollectionAllRaa_2040[0], 21, 2, kAzure-2, kAzure-2);
			DrawGammaSetMarker(statErrorRelCollectionAllRaa_2040[10], 25, 2, colorEMCal2050 , colorEMCal2050);

			statErrorRelCollectionAllRaa_0010[0]->Scale(1./10);
			statErrorRelCollectionAllRaa_0010[10]->Scale(1./10);
			statErrorRelCollectionAllRaa_2040[0]->Scale(1./10);
			statErrorRelCollectionAllRaa_2040[10]->Scale(1./10);
			statErrorRelCollectionAllRaa_0010[0]->Draw("p,same,e1");
			statErrorRelCollectionAllRaa_0010[10]->Draw("p,same,e1");
			statErrorRelCollectionAllRaa_2040[0]->Draw("p,same,e1");
			statErrorRelCollectionAllRaa_2040[10]->Draw("p,same,e1");
			
			legendRelStatErr20102011->Draw();
			labelRelStatErrEnergy->Draw();
// 			labelRelStatErrPi0->Draw();
			
		canvasRelStatErrAll->SaveAs(Form("%s/%s_RaaRelStatErr2010and2011.%s",outputDir.Data(),meson.Data(),suffix.Data()));

	//// 	*********************************************************************************************************************
	//// 	******************************* Visualize relative total errors all measurements ************************************
	//// 	*********************************************************************************************************************
		
		TGraphAsymmErrors* graphCombInvYieldRelStat2760GeVAAll_0010        = CalculateRelErrUpAsymmGraph( graphCombInvYieldStat2760GeVAAll_0010, "relativeStatErrorAll_MethodA_0010");
		TGraphAsymmErrors* graphCombInvYieldRelSys2760GeVAAll_0010         = CalculateRelErrUpAsymmGraph( graphCombInvYieldSys2760GeVAAll_0010, "relativeSysErrorAll_MethodA_0010");
		TGraphAsymmErrors* graphCombInvYieldRelTot2760GeVAAll_0010         = CalculateRelErrUpAsymmGraph( graphCombInvYieldTot2760GeVAAll_0010, "relativeTotalErrorAll_MethodA_0010");
		
		TGraphAsymmErrors* graphCombInvYieldRelTot2760GeVAll_0010 = CalculateRelErrUpAsymmGraph( graphCombInvYieldTot2760GeVAll_0010, "relativeTotalError_OEMC_0010");

		TGraphAsymmErrors* graphCombInvYieldRelStat2760GeVAAll_2040        = CalculateRelErrUpAsymmGraph( graphCombInvYieldStat2760GeVAAll_2040, "relativeStatErrorAll_MethodA_2040");
		TGraphAsymmErrors* graphCombInvYieldRelSys2760GeVAAll_2040         = CalculateRelErrUpAsymmGraph( graphCombInvYieldSys2760GeVAAll_2040, "relativeSysErrorAll_MethodA_2040");
		TGraphAsymmErrors* graphCombInvYieldRelTot2760GeVAAll_2040         = CalculateRelErrUpAsymmGraph( graphCombInvYieldTot2760GeVAAll_2040, "relativeTotalErrorAll_MethodA_2040");

	////	**********************************************************************************************************************
	////	******************************* Calculating bin shifted spectra & fitting - all measurements *************************
	////	**********************************************************************************************************************
			
		// Cloning spectra
		TGraphAsymmErrors* graphCombInvYieldTot2760GeVAAllUnShifted_0010 		= (TGraphAsymmErrors*)graphCombInvYieldTot2760GeVAAll_0010->Clone("Unshifted_0010"); 
		TGraphAsymmErrors* graphCombInvYieldStat2760GeVAAllUnShifted_0010 		= (TGraphAsymmErrors*)graphCombInvYieldStat2760GeVAAll_0010->Clone("UnshiftedStat_0010"); 
		TGraphAsymmErrors* graphCombInvYieldSys2760GeVAAllUnShifted_0010 		= (TGraphAsymmErrors*)graphCombInvYieldSys2760GeVAAll_0010->Clone("UnshiftedSys_0010"); 

		TGraphAsymmErrors* graphCombInvYieldTot2760GeVAAllUnShifted_2040 		= (TGraphAsymmErrors*)graphCombInvYieldTot2760GeVAAll_2040->Clone("Unshifted_2040"); 
		TGraphAsymmErrors* graphCombInvYieldStat2760GeVAAllUnShifted_2040 		= (TGraphAsymmErrors*)graphCombInvYieldStat2760GeVAAll_2040->Clone("UnshiftedStat_2040"); 
		TGraphAsymmErrors* graphCombInvYieldSys2760GeVAAllUnShifted_2040  		= (TGraphAsymmErrors*)graphCombInvYieldSys2760GeVAAll_2040->Clone("UnshiftedSys_2040"); 
		
		TGraphAsymmErrors* graphPCMOldInvYieldStatPbPb2760GeVUnShifted_0010;
		TGraphAsymmErrors* graphPCMOldInvYieldSysPbPb2760GeVUnShifted_0010;
		TGraphAsymmErrors* graphPHOSInvYieldStatPbPb2760GeVUnshifted_0010;
		TGraphAsymmErrors* graphPHOSInvYieldSysPbPb2760GeVUnshifted_0010;
		
		graphPCMOldInvYieldStatPbPb2760GeVUnShifted_0010 		= (TGraphAsymmErrors*)graphPCMPublishedPi0InvYieldStatPbPb2760GeV_0010->Clone("UnshiftedStatPCMOldPi0_0010"); 
		graphPCMOldInvYieldSysPbPb2760GeVUnShifted_0010 		= (TGraphAsymmErrors*)graphPCMPublishedPi0InvYieldSysPbPb2760GeV_0010->Clone("UnshiftedSysPCMOldPi0_0010"); 

		graphPHOSInvYieldStatPbPb2760GeVUnshifted_0010 	= (TGraphAsymmErrors*)graphPHOSPi0InvYieldStatPbPb2760GeV_0010->Clone("UnshiftedStatPHOSPi0_0010"); 
		graphPHOSInvYieldSysPbPb2760GeVUnshifted_0010 	= (TGraphAsymmErrors*)graphPHOSPi0InvYieldSysPbPb2760GeV_0010->Clone("UnshiftedSysPHOSPi0_0010"); 

		TGraphAsymmErrors* graphPCMOldInvYieldStatPbPb2760GeVUnShifted_2040;
		TGraphAsymmErrors* graphPCMOldInvYieldSysPbPb2760GeVUnShifted_2040;
		TGraphAsymmErrors* graphPHOSInvYieldStatPbPb2760GeVUnshifted_2040;
		TGraphAsymmErrors* graphPHOSInvYieldSysPbPb2760GeVUnshifted_2040;

		graphPCMOldInvYieldStatPbPb2760GeVUnShifted_2040 		= (TGraphAsymmErrors*)graphPCMPublishedPi0InvYieldStatPbPb2760GeV_2040->Clone("UnshiftedStatPCMOldPi0_2040"); 
		graphPCMOldInvYieldSysPbPb2760GeVUnShifted_2040 		= (TGraphAsymmErrors*)graphPCMPublishedPi0InvYieldSysPbPb2760GeV_2040->Clone("UnshiftedSysPCMOldPi0_2040"); 
	
		graphPHOSInvYieldStatPbPb2760GeVUnshifted_2040 	= (TGraphAsymmErrors*)graphPHOSPi0InvYieldStatPbPb2760GeV_2040->Clone("UnshiftedStatPHOSPi0_2040"); 
		graphPHOSInvYieldSysPbPb2760GeVUnshifted_2040 	= (TGraphAsymmErrors*)graphPHOSPi0InvYieldStatPbPb2760GeV_2040->Clone("UnshiftedSysPHOSPi0_2040"); 

		// Calculating binshifts
		TF1* fitBylinkinPbPb2760GeVPtAll_0010;
		TF1* fitBylinkinPbPb2760GeVPtAll_2040;
		fitBylinkinPbPb2760GeVPtAll_0010 = FitObject("tcm","BylinkinFitPi00010","Pi0",graphCombInvYieldStat2760GeVAAll_0010,0.4,30.);
		graphCombInvYieldStat2760GeVAAll_0010->Fit(fitBylinkinPbPb2760GeVPtAll_0010,"QNRMEX0+","",0.4,30.);
	//	graphPCMInvYieldStatPbPb2760GeV->Fit(fitBylinkinPbPb2760GeVPt,"QNRMEX0+","",0.4,30.);

		fitBylinkinPbPb2760GeVPtAll_2040 = FitObject("tcm","BylinkinFitPi02040","Pi0",graphCombInvYieldStat2760GeVAAll_2040,0.4,30.);
		graphCombInvYieldStat2760GeVAAll_2040->Fit(fitBylinkinPbPb2760GeVPtAll_2040,"QNRMEX0+","",0.4,30.);
	//	graphPCMInvYieldStatPbPb2760GeV->Fit(fitBylinkinPbPb2760GeVPt,"QNRMEX0+","",0.4,30.);
		
		if(bWCorrection.CompareTo("X")==0 ){
			TF1* fitBylinkinPbPb2760GeVPtMultAll_0010 = FitObject("tcm","BylinkinFitPi0","Pi0");		
			graphCombInvYieldTot2760GeVAAll_0010			= ApplyXshift(graphCombInvYieldTot2760GeVAAll_0010, fitBylinkinPbPb2760GeVPtMultAll_0010,"Pi0");
			
			graphCombInvYieldStat2760GeVAAll_0010 		= ApplyXshiftIndividualSpectra (graphCombInvYieldTot2760GeVAAll_0010, 
																							graphCombInvYieldStat2760GeVAAll_0010, 
																							fitBylinkinPbPb2760GeVPtMultAll_0010,
																							0, 5,"Pi0");
			
			graphCombInvYieldSys2760GeVAAll_0010 			= ApplyXshiftIndividualSpectra (graphCombInvYieldTot2760GeVAAll_0010, 
																							graphCombInvYieldSys2760GeVAAll_0010, 
																							fitBylinkinPbPb2760GeVPtMultAll_0010, 
																							0, 5,"Pi0");
			
			graphPCMPi0InvYieldStatPbPb2760GeV_0010			= ApplyXshiftIndividualSpectra( graphCombInvYieldTot2760GeVAAll_0010,
																							graphPCMPi0InvYieldStatPbPb2760GeV_0010,
																							fitBylinkinPbPb2760GeVPtMultAll_0010, 
																							0, 5,"Pi0");
			
			graphPCMPi0InvYieldSysPbPb2760GeV_0010			= ApplyXshiftIndividualSpectra( graphCombInvYieldTot2760GeVAAll_0010, 
																							graphPCMPi0InvYieldSysPbPb2760GeV_0010, 
																							fitBylinkinPbPb2760GeVPtMultAll_0010, 
																							0, 5,"Pi0");

			graphEMCalPi0InvYieldStatPbPb2760GeV_0010 		= ApplyXshiftIndividualSpectra( graphCombInvYieldTot2760GeVAAll_0010, 
																							graphEMCalPi0InvYieldStatPbPb2760GeV_0010, 
																							fitBylinkinPbPb2760GeVPtMultAll_0010,
																							15, 5,"Pi0");	
			
			graphEMCalPi0InvYieldSysPbPb2760GeV_0010 		= ApplyXshiftIndividualSpectra( graphCombInvYieldTot2760GeVAAll_0010, 
																							graphEMCalPi0InvYieldSysPbPb2760GeV_0010, 
																							fitBylinkinPbPb2760GeVPtMultAll_0010,
																							15, 5,"Pi0");	

			graphPCMPublishedPi0InvYieldStatPbPb2760GeV_0010			= ApplyXshiftIndividualSpectra( graphCombInvYieldTot2760GeVAAll_0010,
																							graphPCMPublishedPi0InvYieldStatPbPb2760GeV_0010,
																							fitBylinkinPbPb2760GeVPtMultAll_0010, 
																							0, 5,"Pi0");
			
			graphPCMPublishedPi0InvYieldSysPbPb2760GeV_0010			= ApplyXshiftIndividualSpectra( graphCombInvYieldTot2760GeVAAll_0010, 
																							graphPCMPublishedPi0InvYieldSysPbPb2760GeV_0010, 
																							fitBylinkinPbPb2760GeVPtMultAll_0010, 
																							0, 5,"Pi0");
							
			graphPHOSPi0InvYieldStatPbPb2760GeV_0010 		= ApplyXshiftIndividualSpectra( graphCombInvYieldTot2760GeVAAll_0010, 
																							graphPHOSPi0InvYieldStatPbPb2760GeV_0010, 
																							fitBylinkinPbPb2760GeVPtMultAll_0010,
																							15, 5,"Pi0");	
			
			graphPHOSPi0InvYieldSysPbPb2760GeV_0010 		= ApplyXshiftIndividualSpectra( graphCombInvYieldTot2760GeVAAll_0010, 
																							graphPHOSPi0InvYieldSysPbPb2760GeV_0010, 
																							fitBylinkinPbPb2760GeVPtMultAll_0010,
																							15, 5,"Pi0");	

			
			
			TF1* fitBylinkinPbPb2760GeVPtMultAll_2040 = FitObject("tcm","BylinkinFitPi0","Pi0");		
			graphCombInvYieldTot2760GeVAAll_2040			= ApplyXshift(graphCombInvYieldTot2760GeVAAll_2040, fitBylinkinPbPb2760GeVPtMultAll_2040,"Pi0");
			
			graphCombInvYieldStat2760GeVAAll_2040 		= ApplyXshiftIndividualSpectra (graphCombInvYieldTot2760GeVAAll_2040, 
																							graphCombInvYieldStat2760GeVAAll_2040, 
																							fitBylinkinPbPb2760GeVPtMultAll_2040,
																							0, 5,"Pi0");
			
			graphCombInvYieldSys2760GeVAAll_2040 			= ApplyXshiftIndividualSpectra (graphCombInvYieldTot2760GeVAAll_2040, 
																							graphCombInvYieldSys2760GeVAAll_2040, 
																							fitBylinkinPbPb2760GeVPtMultAll_2040, 
																							0, 5,"Pi0");
			
			graphPCMPi0InvYieldStatPbPb2760GeV_2040			= ApplyXshiftIndividualSpectra( graphCombInvYieldTot2760GeVAAll_2040,
																							graphPCMPi0InvYieldStatPbPb2760GeV_2040,
																							fitBylinkinPbPb2760GeVPtMultAll_2040, 
																							0, 5,"Pi0");
			
			graphPCMPi0InvYieldSysPbPb2760GeV_2040			= ApplyXshiftIndividualSpectra( graphCombInvYieldTot2760GeVAAll_2040, 
																							graphPCMPi0InvYieldSysPbPb2760GeV_2040, 
																							fitBylinkinPbPb2760GeVPtMultAll_2040, 
																							0, 5,"Pi0");
			
// 					graphEMCalPi0InvYieldStatPbPb2760GeV_2040 		= ApplyXshiftIndividualSpectra( graphCombInvYieldTot2760GeVAAll_2040, 
// 																									graphEMCalPi0InvYieldStatPbPb2760GeV_2040, 
// 																									fitBylinkinPbPb2760GeVPtMultAll_2040,
// 																									15, 5,"Pi0");	
// 					
// 					graphEMCalPi0InvYieldSysPbPb2760GeV_2040 		= ApplyXshiftIndividualSpectra( graphCombInvYieldTot2760GeVAAll_2040, 
// 																									graphEMCalPi0InvYieldSysPbPb2760GeV_2040, 
// 																									fitBylinkinPbPb2760GeVPtMultAll_2040,
// 																									15, 5,"Pi0");	

			graphPCMPublishedPi0InvYieldStatPbPb2760GeV_2040			= ApplyXshiftIndividualSpectra( graphCombInvYieldTot2760GeVAAll_2040,
																							graphPCMPublishedPi0InvYieldStatPbPb2760GeV_2040,
																							fitBylinkinPbPb2760GeVPtMultAll_2040, 
																							0, 5,"Pi0");
			
			graphPCMPublishedPi0InvYieldSysPbPb2760GeV_2040			= ApplyXshiftIndividualSpectra( graphCombInvYieldTot2760GeVAAll_2040, 
																							graphPCMPublishedPi0InvYieldSysPbPb2760GeV_2040, 
																							fitBylinkinPbPb2760GeVPtMultAll_2040, 
																							0, 5,"Pi0");
							
			graphPHOSPi0InvYieldStatPbPb2760GeV_2040 		= ApplyXshiftIndividualSpectra( graphCombInvYieldTot2760GeVAAll_2040, 
																							graphPHOSPi0InvYieldStatPbPb2760GeV_2040, 
																							fitBylinkinPbPb2760GeVPtMultAll_2040,
																							15, 5,"Pi0");	
			
			graphPHOSPi0InvYieldSysPbPb2760GeV_2040 		= ApplyXshiftIndividualSpectra( graphCombInvYieldTot2760GeVAAll_2040, 
																						graphPHOSPi0InvYieldSysPbPb2760GeV_2040, 
																						fitBylinkinPbPb2760GeVPtMultAll_2040,
																						15, 5,"Pi0");	


					
			TCanvas* canvasDummy2 = new TCanvas("canvasDummy2","",200,10,1200,1100);  // gives the page size
			DrawGammaCanvasSettings( canvasDummy2,  0.1, 0.01, 0.015, 0.08);
			canvasDummy2->SetLogy();
			canvasDummy2->SetLogx();
			TH2F * histo2DDummy2;
			histo2DDummy2 = new TH2F("histo2DDummy2","histo2DDummy2",1000,0.23,40.,1000,1e-7,1e4);
			SetStyleHistoTH2ForGraphs(histo2DDummy2, "#it{p}_{T} (GeV/#it{c})","#it{E} #frac{d^{3}#sigma}{d#it{p}^{3}} (pb GeV^{-2} #it{c}^{3} )", 0.032,0.04, 0.04,0.04, 1,1.55);
			histo2DDummy2->DrawCopy(); 
		
			DrawGammaSetMarkerTGraphAsym(graphCombInvYieldStat2760GeVAAllUnShifted_0010, 20, 3, kRed, kRed, widthLinesBoxes, kTRUE);
			graphCombInvYieldStat2760GeVAAllUnShifted_0010->Draw("pEsame");
			DrawGammaSetMarkerTGraphAsym(graphCombInvYieldTot2760GeVAAll_0010, 24, 3, kBlack, kBlack, widthLinesBoxes, kTRUE);
			graphCombInvYieldTot2760GeVAAll_0010->Draw("pEsame");
			DrawGammaSetMarkerTGraphAsym(graphPCMPi0InvYieldSysPbPb2760GeV_0010, markerStyleDet[0] ,/*markerSizeDet[0]*/2, kRed, kRed, widthLinesBoxes, kTRUE);
			graphPCMPi0InvYieldSysPbPb2760GeV_0010->Draw("pEsame");
// 					DrawGammaSetMarkerTGraphAsym(graphEMCalPi0InvYieldSysPbPb2760GeV_0010, markerStyleDet[2] ,/*markerSizeDet[2]*/2.5, colorDet[2], colorDet[2], widthLinesBoxes, kTRUE);
// 					graphEMCalPi0InvYieldSysPbPb2760GeV_0010->Draw("pEsame");
			DrawGammaSetMarkerTGraphAsym(graphPCMPublishedPi0InvYieldSysPbPb2760GeV_0010, markerStyleDet[10] ,/*markerSizeDet[0]*/2, colorDet[10], colorDet[10], widthLinesBoxes, kTRUE);
			graphPCMPublishedPi0InvYieldSysPbPb2760GeV_0010->Draw("pEsame");
			DrawGammaSetMarkerTGraphAsym(graphPHOSPi0InvYieldSysPbPb2760GeV_0010, markerStyleDet[1] ,/*markerSizeDet[2]*/2.5, colorDet[1], colorDet[1], widthLinesBoxes, kTRUE);
			graphPHOSPi0InvYieldSysPbPb2760GeV_0010->Draw("pEsame");

			DrawGammaSetMarkerTGraphAsym(graphCombInvYieldStat2760GeVAAllUnShifted_2040, 20, 3, kRed, kRed, widthLinesBoxes, kTRUE);
			graphCombInvYieldStat2760GeVAAllUnShifted_2040->Draw("pEsame");
			DrawGammaSetMarkerTGraphAsym(graphCombInvYieldTot2760GeVAAll_2040, 24, 3, kGray+3, kGray+3, widthLinesBoxes, kTRUE);
			graphCombInvYieldTot2760GeVAAll_2040->Draw("pEsame");
			DrawGammaSetMarkerTGraphAsym(graphPCMPi0InvYieldSysPbPb2760GeV_2040, markerStyleDet[0] ,/*markerSizeDet[0]*/2, kBlue, kBlue, widthLinesBoxes, kTRUE);
			graphPCMPi0InvYieldSysPbPb2760GeV_2040->Draw("pEsame");
// 					DrawGammaSetMarkerTGraphAsym(graphEMCalPi0InvYieldSysPbPb2760GeV_2040, markerStyleDet[2] ,/*markerSizeDet[2]*/2.5, colorDet[2]+1, colorDet[2]+1, widthLinesBoxes, kTRUE);
// 					graphEMCalPi0InvYieldSysPbPb2760GeV_2040->Draw("pEsame");
			DrawGammaSetMarkerTGraphAsym(graphPCMPublishedPi0InvYieldSysPbPb2760GeV_2040, markerStyleDet[10] ,/*markerSizeDet[0]*/2, colorDet[10], colorDet[10], widthLinesBoxes, kTRUE);
			graphPCMPublishedPi0InvYieldSysPbPb2760GeV_2040->Draw("pEsame");
			DrawGammaSetMarkerTGraphAsym(graphPHOSPi0InvYieldSysPbPb2760GeV_2040, markerStyleDet[1] ,/*markerSizeDet[2]*/2.5, colorDet[1], colorDet[1], widthLinesBoxes, kTRUE);
			graphPHOSPi0InvYieldSysPbPb2760GeV_2040->Draw("pEsame");

			TLegend* legendXdummy = new TLegend(0.6,0.8,0.9,0.95);
			legendXdummy->SetFillColor(0);
			legendXdummy->SetLineColor(0);
			legendXdummy->SetTextFont(42);
			legendXdummy->SetTextSize(FontSize);
			legendXdummy->AddEntry(graphCombInvYieldStat2760GeVAAllUnShifted_0010,"combined unshifted","lp");
// 		// 			legendXdummy->AddEntry(graphCombInvYieldTot2760GeVAll,"combined unshifted (stat. err.)","lp");
			legendXdummy->AddEntry(graphPCMPi0InvYieldSysPbPb2760GeV_0010,"PCM 2011","fp");
// 					legendXdummy->AddEntry(graphEMCalPi0InvYieldSysPbPb2760GeV_0010,"EMCal","fp");
			legendXdummy->AddEntry(graphPCMPublishedPi0InvYieldSysPbPb2760GeV_0010,"PCM 2010","fp");
			legendXdummy->AddEntry(graphPHOSPi0InvYieldSysPbPb2760GeV_0010,"PHOS","fp");
			legendXdummy->AddEntry(graphCombInvYieldStat2760GeVAAllUnShifted_2040,"combined unshifted","lp");
// 			legendXdummy->AddEntry(graphCombInvYieldTot2760GeVAll,"combined unshifted (stat. err.)","lp");
			legendXdummy->AddEntry(graphPCMPi0InvYieldSysPbPb2760GeV_2040,"PCM 2011","fp");
// 					legendXdummy->AddEntry(graphEMCalPi0InvYieldSysPbPb2760GeV_2040,"EMCal","fp");
			legendXdummy->AddEntry(graphPCMPublishedPi0InvYieldSysPbPb2760GeV_2040,"PCM 2010","fp");
			legendXdummy->AddEntry(graphPHOSPi0InvYieldSysPbPb2760GeV_2040,"PHOS","fp");

			legendXdummy->Draw();
			canvasDummy2->Update();
// 			canvasDummy2->Print(Form("%s/%s_ComparisonShiftedPi0_PbPb2760GeVAll.%s",outputDir.Data(),meson.Data(),suffix.Data()));
		}
			
		TF1* fitTCMInvYield2760GeVAll_0010;
		TF1* fitTCMInvYield2760GeVAll_2040;

		Double_t paramTCM_0010[5] = {graphCombInvYieldTot2760GeVAAll_0010->GetY()[0],0.3,graphCombInvYieldTot2760GeVAAll_0010->GetY()[0]/10000,0.8,3};
		fitTCMInvYield2760GeVAll_0010 = FitObject("tcm","fitTCMInvYield2760GeV","Pi0",graphCombInvYieldTot2760GeVAAll_0010,0.4,50.,paramTCM_0010,"QNRMEX0+");
		fitTCMInvYield2760GeVAll_0010 = FitObject("tcm","fitTCMInvYield2760GeV","Pi0",graphCombInvYieldTot2760GeVAAll_0010,0.4,50. ,paramTCM_0010,"QNRMEX0+");
		
		Double_t paramTCM_2040[5] = {graphCombInvYieldTot2760GeVAAll_2040->GetY()[0],0.3,graphCombInvYieldTot2760GeVAAll_2040->GetY()[0]/10000,0.8,3};
		fitTCMInvYield2760GeVAll_2040 = FitObject("tcm","fitTCMInvYield2760GeV","Pi0",graphCombInvYieldTot2760GeVAAll_2040,0.4,50.,paramTCM_2040,"QNRMEX0+");
		fitTCMInvYield2760GeVAll_2040 = FitObject("tcm","fitTCMInvYield2760GeV","Pi0",graphCombInvYieldTot2760GeVAAll_2040,0.4,50. ,paramTCM_2040,"QNRMEX0+");

		cout << WriteParameterToFile(fitTCMInvYield2760GeVAll_0010)<< endl << endl;
		cout << WriteParameterToFile(fitTCMInvYield2760GeVAll_2040)<< endl << endl;
		
		TGraphAsymmErrors* graphRatioCombCombFitTot2760GeVAll_0010 	= (TGraphAsymmErrors*)graphCombInvYieldTot2760GeVAAll_0010->Clone();
		graphRatioCombCombFitTot2760GeVAll_0010 						= CalculateGraphErrRatioToFit(graphRatioCombCombFitTot2760GeVAll_0010, fitTCMInvYield2760GeVAll_0010); 
		TGraphAsymmErrors* graphRatioCombCombFitStat2760GeVAll_0010 	= (TGraphAsymmErrors*)graphCombInvYieldStat2760GeVAAll_0010->Clone();
		graphRatioCombCombFitStat2760GeVAll_0010 						= CalculateGraphErrRatioToFit(graphRatioCombCombFitStat2760GeVAll_0010, fitTCMInvYield2760GeVAll_0010); 
		TGraphAsymmErrors* graphRatioCombCombFitSys2760GeVAll_0010 	= (TGraphAsymmErrors*)graphCombInvYieldSys2760GeVAAll_0010->Clone();
		graphRatioCombCombFitSys2760GeVAll_0010 						= CalculateGraphErrRatioToFit(graphRatioCombCombFitSys2760GeVAll_0010, fitTCMInvYield2760GeVAll_0010); 

		TGraphAsymmErrors* graphRatioCombCombFitTot2760GeVAll_2040 	= (TGraphAsymmErrors*)graphCombInvYieldTot2760GeVAAll_2040->Clone();
		graphRatioCombCombFitTot2760GeVAll_2040 						= CalculateGraphErrRatioToFit(graphRatioCombCombFitTot2760GeVAll_2040, fitTCMInvYield2760GeVAll_2040); 
		TGraphAsymmErrors* graphRatioCombCombFitStat2760GeVAll_2040 	= (TGraphAsymmErrors*)graphCombInvYieldStat2760GeVAAll_2040->Clone();
		graphRatioCombCombFitStat2760GeVAll_2040 						= CalculateGraphErrRatioToFit(graphRatioCombCombFitStat2760GeVAll_2040, fitTCMInvYield2760GeVAll_2040); 
		TGraphAsymmErrors* graphRatioCombCombFitSys2760GeVAll_2040 	= (TGraphAsymmErrors*)graphCombInvYieldSys2760GeVAAll_2040->Clone();
		graphRatioCombCombFitSys2760GeVAll_2040 						= CalculateGraphErrRatioToFit(graphRatioCombCombFitSys2760GeVAll_2040, fitTCMInvYield2760GeVAll_2040); 

		TGraphAsymmErrors* graphRatioPCMOldCombFitStat2760GeV_0010;
		TGraphAsymmErrors* graphRatioPCMOldCombFitSys2760GeV_0010;
		TGraphAsymmErrors* graphRatioPHOSCombFitStat2760GeV_0010;
		TGraphAsymmErrors* graphRatioPHOSCombFitSys2760GeV_0010;
		
		TGraphAsymmErrors* graphRatioPCMOldCombFitStat2760GeV_2040;
		TGraphAsymmErrors* graphRatioPCMOldCombFitSys2760GeV_2040;
		TGraphAsymmErrors* graphRatioPHOSCombFitStat2760GeV_2040;
		TGraphAsymmErrors* graphRatioPHOSCombFitSys2760GeV_2040;
		
		TGraphAsymmErrors* graphRatioPCMCombFitStat2760GeV_2040;
		TGraphAsymmErrors* graphRatioPCMCombFitSys2760GeV_2040;
			
		graphRatioPCMOldCombFitStat2760GeV_0010		= (TGraphAsymmErrors*)graphPCMPublishedPi0InvYieldStatPbPb2760GeV_0010->Clone();
		graphRatioPCMOldCombFitStat2760GeV_0010						= CalculateGraphErrRatioToFit(graphRatioPCMOldCombFitStat2760GeV_0010, fitTCMInvYield2760GeVAll_0010); 
		graphRatioPCMOldCombFitSys2760GeV_0010 		= (TGraphAsymmErrors*)graphPCMPublishedPi0InvYieldSysPbPb2760GeV_0010->Clone();
		graphRatioPCMOldCombFitSys2760GeV_0010 						= CalculateGraphErrRatioToFit(graphRatioPCMOldCombFitSys2760GeV_0010, fitTCMInvYield2760GeVAll_0010); 
		graphRatioPHOSCombFitStat2760GeV_0010 	= (TGraphAsymmErrors*)graphPHOSPi0InvYieldStatPbPb2760GeV_0010->Clone();
		graphRatioPHOSCombFitStat2760GeV_0010 						= CalculateGraphErrRatioToFit(graphRatioPHOSCombFitStat2760GeV_0010, fitTCMInvYield2760GeVAll_0010); 
		graphRatioPHOSCombFitSys2760GeV_0010 	= (TGraphAsymmErrors*)graphPHOSPi0InvYieldSysPbPb2760GeV_0010->Clone();
		graphRatioPHOSCombFitSys2760GeV_0010 						= CalculateGraphErrRatioToFit(graphRatioPHOSCombFitSys2760GeV_0010, fitTCMInvYield2760GeVAll_0010); 
		
		graphRatioPCMOldCombFitStat2760GeV_2040		= (TGraphAsymmErrors*)graphPCMPublishedPi0InvYieldStatPbPb2760GeV_2040->Clone();
		graphRatioPCMOldCombFitStat2760GeV_2040						= CalculateGraphErrRatioToFit(graphRatioPCMOldCombFitStat2760GeV_2040, fitTCMInvYield2760GeVAll_2040); 
		graphRatioPCMOldCombFitSys2760GeV_2040 		= (TGraphAsymmErrors*)graphPCMPublishedPi0InvYieldSysPbPb2760GeV_2040->Clone();
		graphRatioPCMOldCombFitSys2760GeV_2040 						= CalculateGraphErrRatioToFit(graphRatioPCMOldCombFitSys2760GeV_2040, fitTCMInvYield2760GeVAll_2040); 
		graphRatioPHOSCombFitStat2760GeV_2040 	= (TGraphAsymmErrors*)graphPHOSPi0InvYieldStatPbPb2760GeV_2040->Clone();
		graphRatioPHOSCombFitStat2760GeV_2040 						= CalculateGraphErrRatioToFit(graphRatioPHOSCombFitStat2760GeV_2040, fitTCMInvYield2760GeVAll_2040); 
		graphRatioPHOSCombFitSys2760GeV_2040 	= (TGraphAsymmErrors*)graphPHOSPi0InvYieldSysPbPb2760GeV_2040->Clone();
		graphRatioPHOSCombFitSys2760GeV_2040 						= CalculateGraphErrRatioToFit(graphRatioPHOSCombFitSys2760GeV_2040, fitTCMInvYield2760GeVAll_2040); 
	
		graphRatioPCMCombFitStat2760GeV_2040		= (TGraphAsymmErrors*)graphPCMPi0InvYieldStatPbPb2760GeV_2040->Clone();
		graphRatioPCMCombFitStat2760GeV_2040						= CalculateGraphErrRatioToFit(graphRatioPCMCombFitStat2760GeV_2040, fitTCMInvYield2760GeVAll_2040); 
		graphRatioPCMCombFitSys2760GeV_2040 		= (TGraphAsymmErrors*)graphPCMPi0InvYieldSysPbPb2760GeV_2040->Clone();
		graphRatioPCMCombFitSys2760GeV_2040 						= CalculateGraphErrRatioToFit(graphRatioPCMCombFitSys2760GeV_2040, fitTCMInvYield2760GeVAll_2040); 
				
		
		//	**********************************************************************************************************************
		//	******************************************* Ratio of Comb to Fit ****************************************
		//	**********************************************************************************************************************
		textSizeLabelsPixel = 48;
		TCanvas* canvasRatioToCombFitAll = new TCanvas("canvasRatioToCombFitAll","",200,10,1350,900);  // gives the page size
		DrawGammaCanvasSettings( canvasRatioToCombFitAll, 0.12, 0.01, 0.01, 0.11);
		canvasRatioToCombFitAll->SetLogx();

			if (canvasRatioToCombFitAll->XtoPixel(canvasRatioToCombFitAll->GetX2()) <canvasRatioToCombFitAll->YtoPixel(canvasRatioToCombFitAll->GetY1()) ){
				textsizeLabelsPP = (Double_t)textSizeLabelsPixel/canvasRatioToCombFitAll->XtoPixel(canvasRatioToCombFitAll->GetX2()) ;
				textsizeFacPP = (Double_t)1./canvasRatioToCombFitAll->XtoPixel(canvasRatioToCombFitAll->GetX2()) ;
			} else {
				textsizeLabelsPP = (Double_t)textSizeLabelsPixel/canvasRatioToCombFitAll->YtoPixel(canvasRatioToCombFitAll->GetY1());
				textsizeFacPP = (Double_t)1./canvasRatioToCombFitAll->YtoPixel(canvasRatioToCombFitAll->GetY1());
			}
			cout << textsizeLabelsPP << endl;
		
			TH2F * histo2DRatioToCombFitAll;
			histo2DRatioToCombFitAll = new TH2F("histo2DRatioToCombFitAll","histo2DRatioToCombFitAll",1000,0.23,70.,1000,0.2,4.	);
			SetStyleHistoTH2ForGraphs(histo2DRatioToCombFitAll, "#it{p}_{T} (GeV/#it{c})","#frac{Data}{Comb Fit}", 0.85*textsizeLabelsPP, textsizeLabelsPP, 
									0.85*textsizeLabelsPP,textsizeLabelsPP, 0.9, 0.95, 510, 505);
			histo2DRatioToCombFitAll->GetXaxis()->SetMoreLogLabels();
			histo2DRatioToCombFitAll->GetXaxis()->SetLabelOffset(-0.01);
		// 	histo2DRatioToCombFitAll->GetYaxis()->SetRangeUser(-10,10);
			histo2DRatioToCombFitAll->GetYaxis()->SetRangeUser(0.05,2.45);
			histo2DRatioToCombFitAll->Draw("copy");

			DrawGammaSetMarkerTGraphAsym(graphRatioCombCombFitSys2760GeVAll_0010, markerStyleComb, markerSizeComb, colorComb , colorComb, widthLinesBoxes, kTRUE);
			graphRatioCombCombFitSys2760GeVAll_0010->Draw("E2same");
			DrawGammaSetMarkerTGraphAsym(graphRatioCombCombFitStat2760GeVAll_0010, markerStyleComb, markerSizeComb, colorComb , colorComb);
			graphRatioCombCombFitStat2760GeVAll_0010->Draw("p,same,e1");

			DrawGammaSetMarkerTGraphAsym(graphRatioCombCombFitSys2760GeVAll_2040, markerStyleComb, markerSizeComb, colorComb+1, colorComb+1, widthLinesBoxes, kTRUE);
			graphRatioCombCombFitSys2760GeVAll_2040->Draw("E2same");
			DrawGammaSetMarkerTGraphAsym(graphRatioCombCombFitStat2760GeVAll_2040, markerStyleComb, markerSizeComb, colorComb+1, colorComb+1);
			graphRatioCombCombFitStat2760GeVAll_2040->Draw("p,same,e1");

			
			DrawGammaLines(0.23, 70. , 1., 1.,0.1, kGray+2);
			DrawGammaLines(0.23, 70. , 1.1, 1.1,0.1, kGray, 7);
			DrawGammaLines(0.23, 70. , 0.9, 0.9,0.1, kGray, 7);

			labelRatioToFitEnergy->Draw();
			if(meson.CompareTo("Pi0")==0){
				labelRatioToFitPi0= new TLatex(0.73,0.87,"#pi^{0} #rightarrow #gamma#gamma");
			} else if(meson.CompareTo("Eta")==0){
				labelRatioToFitPi0= new TLatex(0.73,0.87,"#eta #rightarrow #gamma#gamma");
			}
			SetStyleTLatex( labelRatioToFitPi0, 0.85*textSizeLabelsPixel,4);
			labelRatioToFitPi0->SetTextFont(43);
			labelRatioToFitPi0->Draw();

// 		canvasRatioToCombFitAll->SaveAs(Form("%s/%s_RatioOfCombToCombFit_PbPb2760GeVAll.%s",outputDir.Data(),meson.Data(),suffix.Data()));
			
		//	**********************************************************************************************************************
		//	******************************************* Ratio of Individual meas to Fit ******************************************
		//	**********************************************************************************************************************
		
		canvasRatioToCombFitAll->cd();
		histo2DRatioToCombFitAll->Draw("copy");
		
			DrawGammaSetMarkerTGraphAsym(graphRatioPCMCombFitSys2760GeV_0010, markerStyleDet[0] ,markerSizeDet[0]*0.5, kRed, kRed, widthLinesBoxes, kTRUE);
			DrawGammaSetMarkerTGraphAsym(graphRatioPCMCombFitStat2760GeV_0010, markerStyleDet[0] ,markerSizeDet[0]*0.5, kRed, kRed);
// 				DrawGammaSetMarkerTGraphAsym(graphRatioEMCalCombFitSys2760GeV_0010, markerStyleDet[2] ,markerSizeDet[2]*0.5, colorDet[2], colorDet[2], widthLinesBoxes, kTRUE);
// 				DrawGammaSetMarkerTGraphAsym(graphRatioEMCalCombFitStat2760GeV_0010, markerStyleDet[2] ,markerSizeDet[2]*0.5, colorDet[2], colorDet[2]);
			
			graphRatioPCMCombFitSys2760GeV_0010->Draw("E2same");
			graphRatioEMCalCombFitSys2760GeV_0010->Draw("E2same");
			
			graphRatioPCMCombFitStat2760GeV_0010->Draw("p,same,e");
			graphRatioEMCalCombFitStat2760GeV_0010->Draw("p,same,e");

			DrawGammaSetMarkerTGraphAsym(graphRatioPCMOldCombFitSys2760GeV_0010, markerStyleDet[10] ,markerSizeDet[10]*0.5, colorDet[10], colorDet[10], widthLinesBoxes, kTRUE);
			DrawGammaSetMarkerTGraphAsym(graphRatioPCMOldCombFitStat2760GeV_0010, markerStyleDet[10] ,markerSizeDet[10]*0.5, colorDet[10], colorDet[10]);
			DrawGammaSetMarkerTGraphAsym(graphRatioPHOSCombFitSys2760GeV_0010, markerStyleDet[1] ,markerSizeDet[1]*0.5, colorDet[1], colorDet[1], widthLinesBoxes, kTRUE);
			DrawGammaSetMarkerTGraphAsym(graphRatioPHOSCombFitStat2760GeV_0010, markerStyleDet[1] ,markerSizeDet[1]*0.5, colorDet[1], colorDet[1]);
			
			graphRatioPCMOldCombFitSys2760GeV_0010->Draw("E2same");
			graphRatioPHOSCombFitSys2760GeV_0010->Draw("E2same");
			
			graphRatioPCMOldCombFitStat2760GeV_0010->Draw("p,same,e");
			graphRatioPHOSCombFitStat2760GeV_0010->Draw("p,same,e");

			
			DrawGammaSetMarkerTGraphAsym(graphRatioPCMCombFitSys2760GeV_2040, markerStyleDet[0] ,markerSizeDet[0]*0.5, kBlue, kBlue, widthLinesBoxes, kTRUE);
			DrawGammaSetMarkerTGraphAsym(graphRatioPCMCombFitStat2760GeV_2040, markerStyleDet[0] ,markerSizeDet[0]*0.5, kBlue, kBlue);
// 			DrawGammaSetMarkerTGraphAsym(graphRatioEMCalCombFitSys2760GeV_2040, markerStyleDet[2] ,markerSizeDet[2]*0.5, colorDet[2]+1, colorDet[2]+1, widthLinesBoxes, kTRUE);
// 			DrawGammaSetMarkerTGraphAsym(graphRatioEMCalCombFitStat2760GeV_2040, markerStyleDet[2] ,markerSizeDet[2]*0.5, colorDet[2]+1, colorDet[2]+1);
// 			
			graphRatioPCMCombFitSys2760GeV_2040->Draw("E2same");
// 			graphRatioEMCalCombFitSys2760GeV_2040->Draw("E2same");
// 			
			graphRatioPCMCombFitStat2760GeV_2040->Draw("p,same,e");
// 			graphRatioEMCalCombFitStat2760GeV_2040->Draw("p,same,e");
// 
			DrawGammaSetMarkerTGraphAsym(graphRatioPCMOldCombFitSys2760GeV_2040, markerStyleDet[0] ,markerSizeDet[0]*0.5, kRed, kRed, widthLinesBoxes, kTRUE);
			DrawGammaSetMarkerTGraphAsym(graphRatioPCMOldCombFitStat2760GeV_2040, markerStyleDet[0] ,markerSizeDet[0]*0.5, kRed, kRed);
			DrawGammaSetMarkerTGraphAsym(graphRatioPHOSCombFitSys2760GeV_2040, markerStyleDet[2] ,markerSizeDet[2]*0.5, colorDet[2], colorDet[2], widthLinesBoxes, kTRUE);
			DrawGammaSetMarkerTGraphAsym(graphRatioPHOSCombFitStat2760GeV_2040, markerStyleDet[2] ,markerSizeDet[2]*0.5, colorDet[2], colorDet[2]);
			
			graphRatioPCMOldCombFitSys2760GeV_2040->Draw("E2same");
			graphRatioPHOSCombFitSys2760GeV_2040->Draw("E2same");
			
			graphRatioPCMOldCombFitStat2760GeV_2040->Draw("p,same,e");
			graphRatioPHOSCombFitStat2760GeV_2040->Draw("p,same,e");

			
			DrawGammaLines(0.23, 70. , 1., 1.,0.5, kGray+2);
			DrawGammaLines(0.23, 70. , 1.1, 1.1,0.5, kGray, 7);
			DrawGammaLines(0.23, 70. , 0.9, 0.9,0.5, kGray, 7);
			
			labelRatioToFitEnergy->Draw();
			labelRatioToFitPi0->Draw();
			
			// ****************************** Definition of the Legend ******************************************
			// ****************** first Column **************************************************
			TLatex *textPCMOnlyRatioPi0All = new TLatex(columnsLegendOnlyPi0Ratio[0],rowsLegendOnlyPi0Ratio[1],"PCM");
			SetStyleTLatex( textPCMOnlyRatioPi0All, 0.85*textSizeLabelsPixel,4);
			textPCMOnlyRatioPi0All->SetTextFont(43);
			textPCMOnlyRatioPi0All->Draw();
			TLatex *textEMCalOnlyRatioPi0All = new TLatex(columnsLegendOnlyPi0Ratio[0],rowsLegendOnlyPi0Ratio[3],"EMCal");
			SetStyleTLatex( textEMCalOnlyRatioPi0All,  0.85*textSizeLabelsPixel,4);
			textEMCalOnlyRatioPi0All->SetTextFont(43);
			textEMCalOnlyRatioPi0All->Draw();
			
			// ****************** second Column *************************************************
			TLatex *textStatOnlyRatioPi0All = new TLatex(columnsLegendOnlyPi0Ratio[1],rowsLegendOnlyPi0Ratio[0] ,"stat");
			SetStyleTLatex( textStatOnlyRatioPi0All, 0.85*textSizeLabelsPixel,4);
			textStatOnlyRatioPi0All->SetTextFont(43);
			textStatOnlyRatioPi0All->Draw();
			TLatex *textSysOnlyRatioPi0All = new TLatex(columnsLegendOnlyPi0Ratio[2] ,rowsLegendOnlyPi0Ratio[0],"syst");
			SetStyleTLatex( textSysOnlyRatioPi0All, 0.85*textSizeLabelsPixel,4);
			textSysOnlyRatioPi0All->SetTextFont(43);
			textSysOnlyRatioPi0All->Draw();
			
			TMarker* markerPCMPi0OnlyRatioPi0All = CreateMarkerFromGraph(graphRatioPCMCombFitSys2760GeV_0010,columnsLegendOnlyPi0Ratio[1] ,rowsLegendOnlyPi0Ratio[1],1);
			markerPCMPi0OnlyRatioPi0All->DrawMarker(columnsLegendOnlyPi0RatioAbs[1] ,rowsLegendOnlyPi0RatioAbs[1]);
			
// 				TMarker* markerEMCalPi0OnlyRatioPi0All = CreateMarkerFromGraph(graphRatioEMCalCombFitSys2760GeV_0010, columnsLegendOnlyPi0Ratio[1] ,rowsLegendOnlyPi0Ratio[3],1);
// 				markerEMCalPi0OnlyRatioPi0All->DrawMarker(columnsLegendOnlyPi0RatioAbs[1] ,rowsLegendOnlyPi0RatioAbs[3]);

			boxPCMPi0OnlyRatioPi0->Draw("l");
			
// 			TBox* boxEMCalPi0OnlyRatioPi0 = CreateBoxFromGraph(graphRatioEMCalCombFitSys2760GeV_0010, columnsLegendOnlyPi0RatioAbs[2]-0.5*lengthBox , rowsLegendOnlyPi0RatioAbs[3]- heightBox,
// 															columnsLegendOnlyPi0RatioAbs[2]+ 3*lengthBox, rowsLegendOnlyPi0RatioAbs[3]+ heightBox);

			TBox* boxPCMOldPi0OnlyRatioPi0 = CreateBoxFromGraph(graphRatioPCMOldCombFitSys2760GeV_0010, columnsLegendOnlyPi0RatioAbs[2]-0.5*lengthBox , rowsLegendOnlyPi0RatioAbs[1]- heightBox,
															columnsLegendOnlyPi0RatioAbs[2]+ 3*lengthBox, rowsLegendOnlyPi0RatioAbs[1]+ heightBox);
			boxPCMOldPi0OnlyRatioPi0->Draw("l");
			
			TBox* boxPHOSPi0OnlyRatioPi0 = CreateBoxFromGraph(graphRatioPHOSCombFitSys2760GeV_0010, columnsLegendOnlyPi0RatioAbs[2]-0.5*lengthBox , rowsLegendOnlyPi0RatioAbs[3]- heightBox,
															columnsLegendOnlyPi0RatioAbs[2]+ 3*lengthBox, rowsLegendOnlyPi0RatioAbs[3]+ heightBox);
			
			TMarker* markerPCMPi0OnlyRatioPi0All_2040 = CreateMarkerFromGraph(graphRatioPCMCombFitSys2760GeV_2040,columnsLegendOnlyPi0Ratio[1] ,rowsLegendOnlyPi0Ratio[1],1);
			markerPCMPi0OnlyRatioPi0All_2040->DrawMarker(columnsLegendOnlyPi0RatioAbs[1] ,rowsLegendOnlyPi0RatioAbs[1]);
			
// 				TMarker* markerEMCalPi0OnlyRatioPi0All_2040 = CreateMarkerFromGraph(graphRatioEMCalCombFitSys2760GeV_2040, columnsLegendOnlyPi0Ratio[1] ,rowsLegendOnlyPi0Ratio[3],1);
// 				markerEMCalPi0OnlyRatioPi0All_2040->DrawMarker(columnsLegendOnlyPi0RatioAbs[1] ,rowsLegendOnlyPi0RatioAbs[3]);

			TBox* boxPCMPi0OnlyRatioPi0All_2040 = CreateBoxFromGraph(graphRatioPCMCombFitSys2760GeV_2040, columnsLegendOnlyPi0RatioAbs[2]-0.5*lengthBox , rowsLegendOnlyPi0RatioAbs[1]- heightBox,
															columnsLegendOnlyPi0RatioAbs[2]+ 3*lengthBox, rowsLegendOnlyPi0RatioAbs[1]+ heightBox);
			boxPCMPi0OnlyRatioPi0All_2040->Draw("l");
// 				TBox* boxEMCalPi0OnlyRatioPi0All_2040 = CreateBoxFromGraph(graphRatioEMCalCombFitSys2760GeV_2040, columnsLegendOnlyPi0RatioAbs[2]-0.5*lengthBox , rowsLegendOnlyPi0RatioAbs[3]- heightBox,
// 																columnsLegendOnlyPi0RatioAbs[2]+ 3*lengthBox, rowsLegendOnlyPi0RatioAbs[3]+ heightBox);
// 	
// 				boxEMCalPi0OnlyRatioPi0All_2040->Draw("l");
		
// 		canvasRatioToCombFitAll->SaveAs(Form("%s/%s_RatioOfIndividualMeasToCombFit_PbPb2760GeVAll.%s",outputDir.Data(),meson.Data(),suffix.Data()));

	
		
		//	**********************************************************************************************************************
		//	******************************** Invariant yields for pi0 single measurement 2.76TeV ************************************
		//	**********************************************************************************************************************
			
		TCanvas* canvasInvYieldSectionPi0All = new TCanvas("canvasInvYieldSectionPi0All","",200,10,1350,1350*1.15);  // gives the page size
		DrawGammaCanvasSettings( canvasInvYieldSectionPi0All, 0.14, 0.02, 0.02, 0.09);
		canvasInvYieldSectionPi0All->SetLogx();
		canvasInvYieldSectionPi0All->SetLogy();
		
			TH2F * histo2DInvYieldSectionPi0All;
			histo2DInvYieldSectionPi0All = new TH2F("histo2DInvYieldSectionPi0All","histo2DInvYieldSectionPi0All",11000,0.23,70.,1000,2e-8,1e3);
			SetStyleHistoTH2ForGraphs(histo2DInvYieldSectionPi0All, "#it{p}_{T} (GeV/#it{c})","#it{E} #frac{d^{3}#sigma}{d#it{p}^{3}} (pb GeV^{-2} #it{c}^{3} )",0.035,0.04, 0.035,0.04, 1.,1.45);
			histo2DInvYieldSectionPi0All->GetXaxis()->SetMoreLogLabels();
			histo2DInvYieldSectionPi0All->GetXaxis()->SetLabelOffset(-0.01);
			histo2DInvYieldSectionPi0All->Draw("copy");

			DrawGammaSetMarkerTGraphAsym(graphPCMPi0InvYieldSysPbPb2760GeV_0010, markerStyleDet[0], markerSizeDet[0]*0.75, kRed , kRed, widthLinesBoxes, kTRUE);
			graphPCMPi0InvYieldSysPbPb2760GeV_0010->Draw("E2same");
// 					DrawGammaSetMarkerTGraphAsym(graphEMCalPi0InvYieldSysPbPb2760GeV_0010, markerStyleDet[2], markerSizeDet[2]*0.75, colorDet[2] , colorDet[2], widthLinesBoxes, kTRUE);
// 					graphEMCalPi0InvYieldSysPbPb2760GeV_0010->Draw("E2same");
	
			DrawGammaSetMarkerTGraphAsym(graphPCMPi0InvYieldStatPbPb2760GeV_0010,markerStyleDet[0], markerSizeDet[0]*0.75, kRed , kRed);
			graphPCMPi0InvYieldStatPbPb2760GeV_0010->Draw("p,same,e1");
// 					DrawGammaSetMarkerTGraphAsym(graphEMCalPi0InvYieldStatPbPb2760GeV_0010, markerStyleDet[2], markerSizeDet[2]*0.75, colorDet[2] , colorDet[2]);
// 					graphEMCalPi0InvYieldStatPbPb2760GeV_0010->Draw("p,same,e1");
			
			DrawGammaSetMarkerTGraphAsym(graphPCMPublishedPi0InvYieldSysPbPb2760GeV_0010, markerStyleDet[10], markerSizeDet[10]*0.75, colorDet[10] , colorDet[10], widthLinesBoxes, kTRUE);
			graphPCMPublishedPi0InvYieldSysPbPb2760GeV_0010->Draw("E2same");
			DrawGammaSetMarkerTGraphAsym(graphPHOSPi0InvYieldSysPbPb2760GeV_0010, markerStyleDet[1], markerSizeDet[1]*0.6, colorDet[1] , colorDet[1], widthLinesBoxes, kTRUE);
			graphPHOSPi0InvYieldSysPbPb2760GeV_0010->Draw("E2same");
	
			DrawGammaSetMarkerTGraphAsym(graphPCMPublishedPi0InvYieldStatPbPb2760GeV_0010,markerStyleDet[10], markerSizeDet[10]*0.75, colorDet[10] , colorDet[10]);
			graphPCMPublishedPi0InvYieldStatPbPb2760GeV_0010->Draw("p,same,e1");
			DrawGammaSetMarkerTGraphAsym(graphPHOSPi0InvYieldStatPbPb2760GeV_0010, markerStyleDet[1], markerSizeDet[1]*0.6, colorDet[1] , colorDet[1]);
			graphPHOSPi0InvYieldStatPbPb2760GeV_0010->Draw("p,same,e1");
			
			DrawGammaSetMarkerTGraphAsym(graphPCMPi0InvYieldSysPbPb2760GeV_2040, markerStyleDet[0], markerSizeDet[0]*0.75, kBlue, kBlue, widthLinesBoxes, kTRUE);
			graphPCMPi0InvYieldSysPbPb2760GeV_2040->Draw("E2same");
// 					DrawGammaSetMarkerTGraphAsym(graphEMCalPi0InvYieldSysPbPb2760GeV_2040, markerStyleDet[2], markerSizeDet[2]*0.75, colorDet[2]+1 , colorDet[2]+1, widthLinesBoxes, kTRUE);
// 					graphEMCalPi0InvYieldSysPbPb2760GeV_2040->Draw("E2same");
		
			DrawGammaSetMarkerTGraphAsym(graphPCMPi0InvYieldStatPbPb2760GeV_2040,markerStyleDet[0], markerSizeDet[0]*0.75, kBlue, kBlue);
			graphPCMPi0InvYieldStatPbPb2760GeV_2040->Draw("p,same,e1");
// 					DrawGammaSetMarkerTGraphAsym(graphEMCalPi0InvYieldStatPbPb2760GeV_2040, markerStyleDet[2], markerSizeDet[2]*0.75, colorDet[2]+1 , colorDet[2]+1);
// 					graphEMCalPi0InvYieldStatPbPb2760GeV_2040->Draw("p,same,e1");

			DrawGammaSetMarkerTGraphAsym(graphPCMPublishedPi0InvYieldSysPbPb2760GeV_2040, markerStyleDet[10], markerSizeDet[10]*0.75, colorDet[10] , colorDet[10], widthLinesBoxes, kTRUE);
			graphPCMPublishedPi0InvYieldSysPbPb2760GeV_2040->Draw("E2same");
			DrawGammaSetMarkerTGraphAsym(graphPHOSPi0InvYieldSysPbPb2760GeV_2040, markerStyleDet[1], markerSizeDet[1]*0.75, colorDet[1] , colorDet[1], widthLinesBoxes, kTRUE);
			graphPHOSPi0InvYieldSysPbPb2760GeV_2040->Draw("E2same");
	
			DrawGammaSetMarkerTGraphAsym(graphPCMPublishedPi0InvYieldStatPbPb2760GeV_2040,markerStyleDet[10], markerSizeDet[10]*0.75, colorDet[10] , colorDet[10]);
			graphPCMPublishedPi0InvYieldStatPbPb2760GeV_2040->Draw("p,same,e1");
			DrawGammaSetMarkerTGraphAsym(graphPHOSPi0InvYieldStatPbPb2760GeV_2040, markerStyleDet[1], markerSizeDet[1]*0.75, colorDet[1] , colorDet[1]);
			graphPHOSPi0InvYieldStatPbPb2760GeV_2040->Draw("p,same,e1");

			
	//			fitBylinkinPbPb2760GeVPtAll_0010->SetRange(0.4,30.);
	// 			fitBylinkinPbPb2760GeVPtAll_0010->Draw("same");			
	// 		fitBylinkinPbPb2760GeVPtAll_2040->SetRange(0.4,30.);
	// 			fitBylinkinPbPb2760GeVPtAll_2040->Draw("same");
			
			
			TLatex *labelEnergyInvYieldSectionPi0All = new TLatex(0.56,0.92,collisionSystem2760GeV.Data());
			SetStyleTLatex( labelEnergyInvYieldSectionPi0All, 0.035,4);
			labelEnergyInvYieldSectionPi0All->Draw();
			TLatex *labelDetSysInvYieldSectionPi0All;
			if(meson.CompareTo("Pi0")==0){
				labelDetSysInvYieldSectionPi0All= new TLatex(0.56,0.88,"#pi^{0} #rightarrow #gamma#gamma");
			} else if(meson.CompareTo("Eta")==0){
				labelDetSysInvYieldSectionPi0All= new TLatex(0.56,0.88,"#eta #rightarrow #gamma#gamma");
			}
			SetStyleTLatex( labelDetSysInvYieldSectionPi0All, 0.035,4);
			labelDetSysInvYieldSectionPi0All->Draw();

			TLegend* legendInvYieldSectionPi0All = new TLegend(0.55,0.66,0.9,0.86);
			legendInvYieldSectionPi0All->SetFillColor(0);
			legendInvYieldSectionPi0All->SetLineColor(0);
			legendInvYieldSectionPi0All->SetTextFont(42);
			legendInvYieldSectionPi0All->SetTextSize(FontSize);
			if(meson.CompareTo("Pi0")==0){
				
				legendInvYieldSectionPi0All->AddEntry(graphPCMPi0InvYieldSysPbPb2760GeV_0010,"PCM  2011 - 0-10%","fp");
	// 					legendInvYieldSectionPi0All->AddEntry(graphEMCalPi0InvYieldStatPbPb2760GeV_0010,"EMCal - 0-10%","fp");
				legendInvYieldSectionPi0All->AddEntry(graphPCMPublishedPi0InvYieldSysPbPb2760GeV_0010,"PCM 2010 - 0-10%","fp");
				legendInvYieldSectionPi0All->AddEntry(graphPHOSPi0InvYieldStatPbPb2760GeV_0010,"PHOS - 0-10%","fp");
				
				legendInvYieldSectionPi0All->AddEntry(graphPCMPi0InvYieldSysPbPb2760GeV_2040,"PCM  2011 - 20-40%","fp");
				legendInvYieldSectionPi0All->AddEntry(graphPCMPublishedPi0InvYieldSysPbPb2760GeV_2040,"PCM 2010 - 20-40%","fp");
				legendInvYieldSectionPi0All->AddEntry(graphPHOSPi0InvYieldStatPbPb2760GeV_2040,"PHOS - 20-40%","fp");
			}
			
			legendInvYieldSectionPi0All->Draw();

// 		canvasInvYieldSectionPi0All->SaveAs(Form("%s/%s_YieldsCompAllSystemsAll.%s",outputDir.Data(),meson.Data(),suffix.Data()));

			
		
		canvasInvYieldSectionPi0All->cd();
		histo2DInvYieldSectionPi0All->Draw("copy");
			
			graphPCMPi0InvYieldSysPbPb2760GeV_0010->Draw("E2same");
			graphPCMPi0InvYieldStatPbPb2760GeV_0010->Draw("p,same,e1");
			graphEMCalPi0InvYieldSysPbPb2760GeV_0010->Draw("E2same");
			graphEMCalPi0InvYieldStatPbPb2760GeV_0010->Draw("p,same,e1");

			graphPCMPublishedPi0InvYieldSysPbPb2760GeV_0010->Draw("E2same");
			graphPCMPublishedPi0InvYieldStatPbPb2760GeV_0010->Draw("p,same,e1");
			graphPHOSPi0InvYieldSysPbPb2760GeV_0010->Draw("E2same");
			graphPHOSPi0InvYieldStatPbPb2760GeV_0010->Draw("p,same,e1");
							
			graphPCMPi0InvYieldSysPbPb2760GeV_2040->Draw("E2same");
			graphPCMPi0InvYieldStatPbPb2760GeV_2040->Draw("p,same,e1");
// 				graphEMCalPi0InvYieldSysPbPb2760GeV_2040->Draw("E2same");
// 				graphEMCalPi0InvYieldStatPbPb2760GeV_2040->Draw("p,same,e1");

			graphPCMPublishedPi0InvYieldSysPbPb2760GeV_2040->Draw("E2same");
			graphPCMPublishedPi0InvYieldStatPbPb2760GeV_2040->Draw("p,same,e1");
			graphPHOSPi0InvYieldSysPbPb2760GeV_2040->Draw("E2same");
			graphPHOSPi0InvYieldStatPbPb2760GeV_2040->Draw("p,same,e1");
			
			DrawGammaSetMarkerTGraphAsym(graphCombInvYieldSys2760GeVAAll_0010, markerStyleComb, markerSizeComb, colorComb , colorComb, widthLinesBoxes, kTRUE);
			DrawGammaSetMarkerTGraphAsym(graphCombInvYieldStat2760GeVAAll_0010, markerStyleComb, markerSizeComb, colorComb , colorComb);
			graphCombInvYieldSys2760GeVAAll_0010->Draw("E2same");
			graphCombInvYieldStat2760GeVAAll_0010->Draw("p,same,e1");	
			fitBylinkinPbPb2760GeVPtAll_0010->Draw("same");

			DrawGammaSetMarkerTGraphAsym(graphCombInvYieldSys2760GeVAAll_2040, markerStyleComb, markerSizeComb, colorComb+1 , colorComb+1, widthLinesBoxes, kTRUE);
			DrawGammaSetMarkerTGraphAsym(graphCombInvYieldStat2760GeVAAll_2040, markerStyleComb, markerSizeComb, colorComb+1, colorComb+1);
			graphCombInvYieldSys2760GeVAAll_2040->Draw("E2same");
			graphCombInvYieldStat2760GeVAAll_2040->Draw("p,same,e1");	
			fitBylinkinPbPb2760GeVPtAll_2040->SetLineStyle(2);
			fitBylinkinPbPb2760GeVPtAll_2040->Draw("same");

			labelEnergyInvYieldSectionPi0All->Draw();
			labelDetSysInvYieldSectionPi0All->Draw();
			
			legendInvYieldSectionPi0All->AddEntry(graphCombInvYieldSys2760GeVAAll_0010,"comb - 0-10%","fp");
// 			legendInvYieldSectionPi0All->AddEntry(fitBylinkinPbPb2760GeVPtAll_0010, "Bylinkin Fit - 0-10%","l");
// 			legendInvYieldSectionPi0All->AddEntry(graphCombInvYieldSys2760GeVAAll_2040,"comb - 20-50%","fp");
// 			legendInvYieldSectionPi0All->AddEntry(fitBylinkinPbPb2760GeVPtAll_2040, "Bylinkin Fit - 20-50%","l");
			legendInvYieldSectionPi0All->Draw();

	// 		DrawGammaSetMarkerTGraphAsym(graphChargedHadronsStatPP2760GeV, markerStyleDet[1], markerSizeDet[1]*0.75, kBlack , kBlack, widthLinesBoxes);
	// 		graphChargedHadronsStatPP2760GeV->Draw("E2same");
		
// 		canvasInvYieldSectionPi0All->SaveAs(Form("%s/%s_YieldCompAllSystemsAll_Comb.%s",outputDir.Data(),meson.Data(),suffix.Data()));
	}	
		

		
			
	if(meson.CompareTo("Eta")==0){
		//*********************************************************************************************************************//
		//************************************	 Combination of EtatoPi0 	***************************************************//
		cout << "\n\n\n *************************	 Combination of Eta to Pi0 ratio 	************************* \n\n\n" << endl;
		
		TLatex *labelEtaToPi0Energy = new TLatex(0.12,0.87,collisionSystem2760GeV.Data());
		SetStyleTLatex( labelEtaToPi0Energy,0.04,4);
// 		labelEtaToPi0Energy->SetTextFont(63);

		TLatex *labelPreliminaryEtaToPi0 = new TLatex(0.65,0.15,"ALICE Preliminary");
		SetStyleTLatex( labelPreliminaryEtaToPi0, 0.04,4);

		//===================== loading pp inputs =============================
		TFile* fEtatoPi0input = new TFile("EtaToPi0InputsForCombination.root");
		TH1D *histoPCMEtaToPi0RatioPbPb0010 = (TH1D*)fEtatoPi0input->Get("histoPCMEtaToPi0RatioPbPb0010");
		TH1D *histoPCMEtaToPi0RatioPbPb2050 = (TH1D*)fEtatoPi0input->Get("histoPCMEtaToPi0RatioPbPb2050");
		TH1D *histoPCMEtaToPi0RatiopPb = (TH1D*)fEtatoPi0input->Get("histoPCMEtaToPi0RatiopPb");
		TGraphAsymmErrors *graphPCMEtaToPi0RatioSysErrpPb = (TGraphAsymmErrors*)fEtatoPi0input->Get("graphPCMEtaToPi0RatioSysErrpPb");
			
		TGraphAsymmErrors *graphCombEtaToPi0RatioSysErrpp7TeV = (TGraphAsymmErrors*)fEtatoPi0input->Get("graphCombEtaToPi0RatioSysErrpp7TeV");
		DrawGammaSetMarkerTGraphAsym(graphCombEtaToPi0RatioSysErrpp7TeV, 21, 1.5, kBlack, kBlack, 1, kTRUE);
		TGraphAsymmErrors *graphCombEtaToPi0Ratiopp7TeVNoXErrors = (TGraphAsymmErrors*)fEtatoPi0input->Get("graphCombEtaToPi0Ratiopp7TeVNoXErrors");
		DrawGammaSetMarkerTGraphAsym(graphCombEtaToPi0Ratiopp7TeVNoXErrors, 21, 1.5, kBlack, kBlack, 1, kTRUE);

		TH1D *cocktailEtaToPi0Ratio7TeVRebined = (TH1D*)fEtatoPi0input->Get("cocktailEtaToPi0Ratio7TeVRebined");
		TH1D *cocktailEtaToPi0Ratio_MtScaledRebinned = (TH1D*)fEtatoPi0input->Get("cocktailEtaToPi0Ratio_MtScaledRebinned");
		TH1D *cocktailEtaToPi0Ratio_K0ScaledRebinned = (TH1D*)fEtatoPi0input->Get("cocktailEtaToPi0Ratio_K0ScaledRebinned");

		cocktailEtaToPi0Ratio7TeVRebined->GetXaxis()->SetRangeUser(0.1,16.);
		cocktailEtaToPi0Ratio_K0ScaledRebinned->GetXaxis()->SetRangeUser(0.1,16.);
		cocktailEtaToPi0Ratio_MtScaledRebinned->GetXaxis()->SetRangeUser(0.1,16.);
		cocktailEtaToPi0Ratio7TeVRebined->SetLineStyle(5);
		cocktailEtaToPi0Ratio7TeVRebined->SetLineWidth(2.5);
		cocktailEtaToPi0Ratio_K0ScaledRebinned->SetLineStyle(6);
		cocktailEtaToPi0Ratio_K0ScaledRebinned->SetLineWidth(2.5);
		cocktailEtaToPi0Ratio_MtScaledRebinned->SetLineStyle(7);
		cocktailEtaToPi0Ratio_MtScaledRebinned->SetLineWidth(2.5);
		//======================================================================
		
		TGraphAsymmErrors* graphCombEtatoPi0Stat2760GeVLHC11h_0010 = NULL;
		TGraphAsymmErrors* graphCombEtatoPi0Sys2760GeVLHC11h_0010 = NULL;
		TGraphAsymmErrors* graphCombEtatoPi0Tot2760GeVLHC11h_0010 = CombinePtPointsSpectraFullCorrMat( statErrorCollectionEtatoPi0LHC11h_0010,	sysErrorCollectionEtatoPi0LHC11h_0010, 	
																									xPtLimitsEta, /*17*/13, offSetsEta, offSetsEtaSys,
																									graphCombEtatoPi0Stat2760GeVLHC11h_0010, graphCombEtatoPi0Sys2760GeVLHC11h_0010, "weightEtatoPi0_0010.dat",1 );
		TGraphAsymmErrors* graphCombEtatoPi0Stat2760GeVLHC11h_2050 = NULL;
		TGraphAsymmErrors* graphCombEtatoPi0Sys2760GeVLHC11h_2050 = NULL;
		TGraphAsymmErrors* graphCombEtatoPi0Tot2760GeVLHC11h_2050 = CombinePtPointsSpectraFullCorrMat( statErrorCollectionEtatoPi0LHC11h_2050,	sysErrorCollectionEtatoPi0LHC11h_2050, 	
																									xPtLimitsEta, /*17*/13, offSetsEta, offSetsEtaSys,
																									graphCombEtatoPi0Stat2760GeVLHC11h_2050, graphCombEtatoPi0Sys2760GeVLHC11h_2050, "weightEtatoPi0_2050.dat",1 );

		graphCombEtatoPi0Tot2760GeVLHC11h_0010->RemovePoint(0);
		graphCombEtatoPi0Tot2760GeVLHC11h_0010->RemovePoint(0);
		graphCombEtatoPi0Tot2760GeVLHC11h_2050->RemovePoint(0);
		graphCombEtatoPi0Tot2760GeVLHC11h_2050->RemovePoint(0);
		
		graphCombEtatoPi0Stat2760GeVLHC11h_0010->RemovePoint(0);
		graphCombEtatoPi0Stat2760GeVLHC11h_0010->RemovePoint(0);
		
		graphCombEtatoPi0Sys2760GeVLHC11h_0010->RemovePoint(0);
		graphCombEtatoPi0Sys2760GeVLHC11h_0010->RemovePoint(0);

		graphCombEtatoPi0Stat2760GeVLHC11h_2050->RemovePoint(0);
		graphCombEtatoPi0Stat2760GeVLHC11h_2050->RemovePoint(0);

		graphCombEtatoPi0Sys2760GeVLHC11h_2050->RemovePoint(0);
		graphCombEtatoPi0Sys2760GeVLHC11h_2050->RemovePoint(0);

// 		cout << "here" << endl;
// 		graphCombEtatoPi0Tot2760GeVLHC11h_0010->Print();
// 		cout << "here" << endl;
// 		graphCombEtatoPi0Stat2760GeVLHC11h_0010->Print();
// 		cout << "here" << endl;
// 		graphCombEtatoPi0Sys2760GeVLHC11h_0010->Print();
// 		
// 		cout << "here" << endl;
// 		graphCombEtatoPi0Tot2760GeVLHC11h_2050->Print();
// 		cout << "here" << endl;
// 		graphCombEtatoPi0Stat2760GeVLHC11h_2050->Print();
// 		cout << "here" << endl;
// 		graphCombEtatoPi0Sys2760GeVLHC11h_2050->Print();


		TCanvas* canvasEtatoPi0combo = new TCanvas("canvasEtatoPi0combo","",200,10,1200,1100);  //200,10,1350,900);  // gives the page size
		DrawGammaCanvasSettings( canvasEtatoPi0combo, 0.09, 0.03, 0.035, 0.1);
		canvasEtatoPi0combo->SetLogx();
		
			TH2F * histo2DEtatoPi0combo = new TH2F("histo2DEtatoPi0combo","histo2DEtatoPi0combo",11000,0.35,25.,1000,-0.5,1.5);
			SetStyleHistoTH2ForGraphs(histo2DEtatoPi0combo, "#it{p}_{T} (GeV/#it{c})","#eta/#pi^{0}",0.035,0.04, 0.035,0.04, 1.2,1.);
			histo2DEtatoPi0combo->GetXaxis()->SetMoreLogLabels();
			histo2DEtatoPi0combo->GetXaxis()->SetLabelOffset(-0.01);
			histo2DEtatoPi0combo->Draw("copy");
			histo2DEtatoPi0combo->GetYaxis()->SetRangeUser(0.,1.2);
// 			histo2DEtatoPi0combo->GetXaxis()->SetRangeUser(0.2,25);
// 			histo2DEtatoPi0combo->GetYaxis()->SetTitle("#eta/#pi^{0}");

			
			DrawGammaSetMarkerTGraphAsym(graphPCMEtatoPi0Sys2760GeV_0010, markerStyleDet[0], markerSizeDet[0]*0.75, colorPCM0010, colorPCM0010, widthLinesBoxes, kTRUE);
				graphPCMEtatoPi0Sys2760GeV_0010->Draw("E2same");
			DrawGammaSetMarkerTGraphAsym(graphPCMEtatoPi0Stat2760GeV_0010,markerStyleDet[0], markerSizeDet[0]*0.75, colorPCM0010 , colorPCM0010);
				graphPCMEtatoPi0Stat2760GeV_0010->Draw("p,same,e1");		
			
			DrawGammaSetMarkerTGraphAsym(graphEMCalEtatoPi0Sys2760GeV_0010, markerStyleDet[2], markerSizeDet[2]*0.75, colorEMCal0010 ,colorEMCal0010,  widthLinesBoxes, kTRUE);
				graphEMCalEtatoPi0Sys2760GeV_0010->Draw("E2same");			
			DrawGammaSetMarkerTGraphAsym(graphEMCalEtatoPi0Stat2760GeV_0010, markerStyleDet[2], markerSizeDet[2]*0.75, colorEMCal0010,colorEMCal0010 );
				graphEMCalEtatoPi0Stat2760GeV_0010->Draw("p,same,e1");
			
			DrawGammaSetMarkerTGraphAsym(graphPCMEtatoPi0Sys2760GeV_2050, markerStyleDet[0], markerSizeDet[0]*0.75, colorPCM2050, colorPCM2050, widthLinesBoxes, kTRUE);
				graphPCMEtatoPi0Sys2760GeV_2050->Draw("E2same");
			DrawGammaSetMarkerTGraphAsym(graphPCMEtatoPi0Stat2760GeV_2050,markerStyleDet[0], markerSizeDet[0]*0.75, colorPCM2050 , colorPCM2050);
				graphPCMEtatoPi0Stat2760GeV_2050->Draw("p,same,e1");		
			
			DrawGammaSetMarkerTGraphAsym(graphEMCalEtatoPi0Sys2760GeV_2050, markerStyleDet[2], markerSizeDet[2]*0.75, colorEMCal2050,colorEMCal2050, widthLinesBoxes, kTRUE);
				graphEMCalEtatoPi0Sys2760GeV_2050->Draw("E2same");			
			DrawGammaSetMarkerTGraphAsym(graphEMCalEtatoPi0Stat2760GeV_2050, markerStyleDet[2], markerSizeDet[2]*0.75, colorEMCal2050,colorEMCal2050);
				graphEMCalEtatoPi0Stat2760GeV_2050->Draw("p,same,e1");

				
			TLegend* legendEtatoPi0LHC11h = new TLegend(0.12,0.5,0.45,0.75);
			legendEtatoPi0LHC11h->SetTextSize(0.04);			
			legendEtatoPi0LHC11h->SetFillColor(0);
			legendEtatoPi0LHC11h->SetFillStyle(0);
			legendEtatoPi0LHC11h->SetBorderSize(0);
// 			legendEtatoPi0LHC11h->AddEntry(graphCombEtatoPi0Sys2760GeVLHC11h_0010,"0-10% Pb-Pb, #sqrt{#it{s}_{_{NN}}} = 2.76 TeV (2011)","pl");
			legendEtatoPi0LHC11h->AddEntry((TObject*)0,"0-10% Pb-Pb (2011)","");
				legendEtatoPi0LHC11h->AddEntry(graphPCMEtatoPi0Sys2760GeV_0010,"PCM","pl");
				legendEtatoPi0LHC11h->AddEntry(graphEMCalEtatoPi0Sys2760GeV_0010,"EMCal","lp");
// 			legendEtatoPi0LHC11h->AddEntry(graphCombEtatoPi0Sys2760GeVLHC11h_2050,"20-50% Pb-Pb, #sqrt{#it{s}_{_{NN}}} = 2.76 TeV (2011)","lp");
			legendEtatoPi0LHC11h->AddEntry((TObject*)0,"20-50% Pb-Pb (2011)","");
				legendEtatoPi0LHC11h->AddEntry(graphPCMEtatoPi0Sys2760GeV_2050,"PCM","pl");
				legendEtatoPi0LHC11h->AddEntry(graphEMCalEtatoPi0Sys2760GeV_2050,"EMCal","lp");
			legendEtatoPi0LHC11h->Draw();
			

		canvasEtatoPi0combo->SaveAs(Form("%s/%s_EtatoPi0Ratio_LHC11h.%s",outputDir.Data(),meson.Data(),suffix.Data()));
// 		canvasEtatoPi0combo->SaveAs(Form("%s/%s_EtatoPi0Ratio_LHC11h.%s",paperPlots.Data(),meson.Data(),suffix.Data()));
		
		canvasEtatoPi0combo->cd();
			histo2DEtatoPi0combo->Draw("copy");
			histo2DEtatoPi0combo->GetYaxis()->SetRangeUser(0.,maxYEtatoPi0);
// 			histo2DEtatoPi0combo->GetXaxis()->SetRangeUser(0.8,25);
				

			DrawGammaSetMarkerTGraphAsym(graphCombEtatoPi0Sys2760GeVLHC11h_0010, markerStyleComb, markerSizeComb, colorCombo0010 , colorCombo0010, 2, kTRUE);
			graphCombEtatoPi0Sys2760GeVLHC11h_0010->Draw("E2same");
			DrawGammaSetMarkerTGraphAsym(graphCombEtatoPi0Stat2760GeVLHC11h_0010, markerStyleComb, markerSizeComb, colorCombo0010 , colorCombo0010);
			if(noXerrorBars) ProduceGraphAsymmWithoutXErrors(graphCombEtatoPi0Stat2760GeVLHC11h_0010);
			graphCombEtatoPi0Stat2760GeVLHC11h_0010->Draw("p,same,e1");

			DrawGammaSetMarkerTGraphAsym(graphCombEtatoPi0Sys2760GeVLHC11h_2050, markerStyleComb, markerSizeComb, colorCombo2050 , colorCombo2050, 2, kTRUE);
			graphCombEtatoPi0Sys2760GeVLHC11h_2050->Draw("E2same");
			DrawGammaSetMarkerTGraphAsym(graphCombEtatoPi0Stat2760GeVLHC11h_2050, markerStyleComb, markerSizeComb, colorCombo2050 , colorCombo2050);
			if(noXerrorBars) ProduceGraphAsymmWithoutXErrors(graphCombEtatoPi0Stat2760GeVLHC11h_2050);
			graphCombEtatoPi0Stat2760GeVLHC11h_2050->Draw("p,same,e1");
			
			TLegend* legendEtatoPi0combo_onlyPbPb = new TLegend(0.11,0.74,0.5,0.85);
			legendEtatoPi0combo_onlyPbPb->SetFillColor(0);
			legendEtatoPi0combo_onlyPbPb->SetLineColor(0);
			legendEtatoPi0combo_onlyPbPb->SetTextFont(42);
			legendEtatoPi0combo_onlyPbPb->SetTextSize(0.04);
			legendEtatoPi0combo_onlyPbPb->SetMargin(0.17);
// 			legendEtatoPi0combo_onlyPbPb->AddEntry(graphCombEtatoPi0Sys2760GeVLHC11h_0010,Form("%s %s",cent0010.Data(),collisionSystem2760GeV.Data()),"fp");
// 			legendEtatoPi0combo_onlyPbPb->AddEntry(graphCombEtatoPi0Sys2760GeVLHC11h_2050,Form("%s %s",cent2050.Data(),collisionSystem2760GeV.Data()),"fp");
			legendEtatoPi0combo_onlyPbPb->AddEntry(graphCombEtatoPi0Sys2760GeVLHC11h_0010,Form("  %s",cent0010.Data()),"fp");
			legendEtatoPi0combo_onlyPbPb->AddEntry(graphCombEtatoPi0Sys2760GeVLHC11h_2050,Form("%s",cent2050.Data()),"fp");
			legendEtatoPi0combo_onlyPbPb->Draw();

			labelEtaToPi0Energy->Draw();
			labelPreliminaryEtaToPi0->Draw();
			
		canvasEtatoPi0combo->SaveAs(Form("%s/%s_EtatoPi0Ratio_combined_DataOnly.%s",outputDir.Data(),meson.Data(),suffix.Data()));
		canvasEtatoPi0combo->SaveAs(Form("%s/%s_EtatoPi0Ratio_combined_DataOnly.%s",paperPlots.Data(),meson.Data(),suffix.Data()));
		
		
		
		canvasEtatoPi0combo->cd();
			histo2DEtatoPi0combo->Draw("copy");
			histo2DEtatoPi0combo->GetYaxis()->SetRangeUser(0.,maxYEtatoPi0);
// 			histo2DEtatoPi0combo->GetXaxis()->SetRangeUser(0.2,25);

			graphCombEtatoPi0Sys2760GeVLHC11h_0010->Draw("E2same");
			if(noXerrorBars) ProduceGraphAsymmWithoutXErrors(graphCombEtatoPi0Stat2760GeVLHC11h_0010);
			graphCombEtatoPi0Stat2760GeVLHC11h_0010->Draw("p,same,e1");

			graphCombEtatoPi0Sys2760GeVLHC11h_2050->Draw("E2same");
			if(noXerrorBars) ProduceGraphAsymmWithoutXErrors(graphCombEtatoPi0Stat2760GeVLHC11h_2050);
			graphCombEtatoPi0Stat2760GeVLHC11h_2050->Draw("p,same,e1");

			graphCombEtaToPi0RatioSysErrpp7TeV->Draw("same,pE2");
			graphCombEtaToPi0Ratiopp7TeVNoXErrors->Draw("same,pe");
			
			TLegend* legendEtatoPi0combo_onlyPbPbwithPP = new TLegend(0.12,0.78,0.5,0.92);
			legendEtatoPi0combo_onlyPbPbwithPP->SetFillColor(0);
			legendEtatoPi0combo_onlyPbPbwithPP->SetLineColor(0);
			legendEtatoPi0combo_onlyPbPbwithPP->SetTextFont(42);
			legendEtatoPi0combo_onlyPbPbwithPP->SetTextSize(0.04);
			legendEtatoPi0combo_onlyPbPbwithPP->SetMargin(0.17);
			legendEtatoPi0combo_onlyPbPbwithPP->SetHeader(collisionSystem2760GeV.Data());
			legendEtatoPi0combo_onlyPbPbwithPP->AddEntry(graphCombEtatoPi0Sys2760GeVLHC11h_0010,Form("  %s",cent0010.Data()),"fp");
			legendEtatoPi0combo_onlyPbPbwithPP->AddEntry(graphCombEtatoPi0Sys2760GeVLHC11h_2050,Form("%s",cent2050.Data()),"fp");
			legendEtatoPi0combo_onlyPbPbwithPP->Draw();
			
			TLegend* legendEtatoPi0combo_withPP = new TLegend(0.5,0.83,0.88,0.92); //0.12,0.67,0.5,0.77);
			legendEtatoPi0combo_withPP->SetFillColor(0);
			legendEtatoPi0combo_withPP->SetLineColor(0);
			legendEtatoPi0combo_withPP->SetTextFont(42);
			legendEtatoPi0combo_withPP->SetTextSize(0.04);
			legendEtatoPi0combo_withPP->SetMargin(0.17);
			legendEtatoPi0combo_withPP->SetHeader(collisionSystemPP7TeV.Data());
			legendEtatoPi0combo_withPP->AddEntry(graphCombEtaToPi0RatioSysErrpp7TeV,"PLB 717 (2012) 162","fp");//"Phys. Lett. B 717 (2012) 162-172","fp");
			legendEtatoPi0combo_withPP->Draw();

			labelPreliminaryEtaToPi0->Draw();
			
			//tre
		canvasEtatoPi0combo->SaveAs(Form("%s/%s_EtatoPi0Ratio_combined_DataOnlyWithPP.%s",outputDir.Data(),meson.Data(),suffix.Data()));
		canvasEtatoPi0combo->SaveAs(Form("%s/%s_EtatoPi0Ratio_combined_DataOnlyWithPP.%s",paperPlots.Data(),meson.Data(),suffix.Data()));
		
		
		canvasEtatoPi0combo->cd();
			histo2DEtatoPi0combo->Draw("copy");
// 			histo2DEtatoPi0combo->GetYaxis()->SetRangeUser(0.,1.2);
// 			histo2DEtatoPi0combo->GetXaxis()->SetRangeUser(0.8,25.);
			
			
			DrawGammaSetMarkerTGraphAsym(graphEtaToPi0JetQuenching_0010, 0, 0, colorNLO0010,colorNLO0010, widthLinesBoxes, kTRUE, colorNLO0010);
			graphEtaToPi0JetQuenching_0010->Draw("3,same");

			DrawGammaSetMarker(histoEtaToPi0EPOSRebin_0010,1,2,colorEPOS0010,colorEPOS0010);
			DrawGammaSetMarker(histoEtaToPi0EPOSRebin_2050,1,2,colorEPOS2050,colorEPOS2050);
			histoEtaToPi0EPOSRebin_0010->SetLineWidth(2);
			histoEtaToPi0EPOSRebin_2050->SetLineWidth(2);
			
			histoEtaToPi0EPOSRebin_0010->GetXaxis()->SetRangeUser(0.,13.9);
// 			histoEtaToPi0EPOSRebin_2050->GetXaxis()->SetRangeUser(0.,20.);
			histoEtaToPi0EPOSRebin_0010->Draw("same,c,histo");
			histoEtaToPi0EPOSRebin_2050->Draw("same,c,histo");
// 
			DrawGammaSetMarkerTGraphAsym(TheoryCracowEtaToPi0LowPt_0010, 0, 0, colorCracow0010,colorCracow0010, 5, kTRUE,colorCracow0010);
			TheoryCracowEtaToPi0LowPt_0010->Draw("l,same");
// 			DrawGammaSetMarkerTGraphAsym(TheoryCracowEtaToPi0LowPt_2050, 0, 0, colorCracow2050,colorCracow2050, 5, kTRUE,colorCracow2050);
// 			TheoryCracowEtaToPi0LowPt_2050->Draw("l,same");

			graphCombEtatoPi0Sys2760GeVLHC11h_0010->Draw("E2same");
			if(noXerrorBars) ProduceGraphAsymmWithoutXErrors(graphCombEtatoPi0Stat2760GeVLHC11h_0010);
			graphCombEtatoPi0Stat2760GeVLHC11h_0010->Draw("p,same,e1");

			graphCombEtatoPi0Sys2760GeVLHC11h_2050->Draw("E2same");
			if(noXerrorBars) ProduceGraphAsymmWithoutXErrors(graphCombEtatoPi0Stat2760GeVLHC11h_2050);
			graphCombEtatoPi0Stat2760GeVLHC11h_2050->Draw("p,same,e1");
			
			labelEtaToPi0Energy->Draw();
			legendEtatoPi0combo_onlyPbPb->Draw();

			TLegend* legendRatioALICE2 = new TLegend(0.5,0.75,0.88,0.9); //0.12,0.62,0.5,0.71);
			legendRatioALICE2->SetFillColor(0);
			legendRatioALICE2->SetLineColor(0);
			legendRatioALICE2->SetTextFont(42);
			legendRatioALICE2->SetTextSize(0.04);
			legendRatioALICE2->SetHeader("NLO DCZW (#tau_{0} = 0.6 fm)");
			legendRatioALICE2->AddEntry(graphEtaToPi0JetQuenching_0010,"0-10%","f");
			legendRatioALICE2->AddEntry((TObject*)0,"arXiv:1506.00838","");
			legendRatioALICE2->Draw();

			labelPreliminaryEtaToPi0->Draw();
			
			TLegend* legendRatioALICE3A = new TLegend(0.41,0.78,0.76,0.9);
			legendRatioALICE3A->SetFillColor(0);
			legendRatioALICE3A->SetLineColor(0);
			legendRatioALICE3A->SetTextFont(42);
			legendRatioALICE3A->SetTextSize(0.04);
			legendRatioALICE3A->SetHeader("Phys.Rev. C89, 064903 (2014)");
			legendRatioALICE3A->AddEntry(histoEPOSRebin_0010,"EPOS 0-10%", "l");
			legendRatioALICE3A->AddEntry(histoEPOSRebin_2050,"EPOS 20-50%", "l");
// 			legendRatioALICE3A->Draw();
			TLegend* legendRatioALICE3B = new TLegend(0.41,0.66,0.76,0.78);
			legendRatioALICE3B->SetFillColor(0);
			legendRatioALICE3B->SetLineColor(0);
			legendRatioALICE3B->SetTextFont(42);
			legendRatioALICE3B->SetTextSize(0.04);
			legendRatioALICE3B->SetHeader("Phys.Rev. C90, 014906 (2014)");
			legendRatioALICE3B->AddEntry(TheoryCracowEtaToPi0LowPt_0010,"NEQ SHM 0-10%", "l");
			legendRatioALICE3B->AddEntry(TheoryCracowEtaToPi0LowPt_2050,"NEQ SHM 20-50%", "l");
// 			legendRatioALICE3B->Draw();
			
		canvasEtatoPi0combo->SaveAs(Form("%s/%s_EtatoPi0Ratio_combined.%s",outputDir.Data(),meson.Data(),suffix.Data()));
		canvasEtatoPi0combo->SaveAs(Form("%s/%s_EtatoPi0Ratio_combined.%s",paperPlots.Data(),meson.Data(),suffix.Data()));
		
		
		canvasEtatoPi0combo->cd();
			histo2DEtatoPi0combo->Draw("copy");
			
// 			histo2DEtatoPi0combo->GetYaxis()->SetRangeUser(0.,1.05);
// 			histo2DEtatoPi0combo->GetXaxis()->SetRangeUser(0.8,30);

			graphEtaToPi0JetQuenching_0010->Draw("3,same");
				
			graphCombEtatoPi0Sys2760GeVLHC11h_0010->Draw("E2same");
			if(noXerrorBars) ProduceGraphAsymmWithoutXErrors(graphCombEtatoPi0Stat2760GeVLHC11h_0010);
			graphCombEtatoPi0Stat2760GeVLHC11h_0010->Draw("p,same,e1");

			TLegend* legendEtatoPi0combo_onlyPbPbOnly0010 = new TLegend(0.49,0.15,0.9,0.23);
			legendEtatoPi0combo_onlyPbPbOnly0010->SetTextSize(0.04);			
			legendEtatoPi0combo_onlyPbPbOnly0010->SetFillColor(0);
			legendEtatoPi0combo_onlyPbPbOnly0010->SetFillStyle(0);
			legendEtatoPi0combo_onlyPbPbOnly0010->SetBorderSize(0);
			legendEtatoPi0combo_onlyPbPbOnly0010->AddEntry(graphCombEtatoPi0Sys2760GeVLHC11h_0010,Form("%s %s",cent0010.Data(),collisionSystem2760GeV.Data()),"fp");
			legendEtatoPi0combo_onlyPbPbOnly0010->Draw();
// 			TH1D *histoCombEtatoPi0Sys2760GeVLHC11h_0010 = (TH1D*)GraphAsymErrorsToHist(graphCombEtatoPi0Sys2760GeVLHC11h_0010,20.,"histoCombEtatoPi0Sys2760GeVLHC11h_0010");
			TF1* pol1 = new TF1("pol1","[0]+[1]*x*x",4.,30.); 
			graphCombEtatoPi0Sys2760GeVLHC11h_0010->Fit(pol1,"NRMEX0+","",4.,20.);
			pol1->Draw("same");
			legendRatioALICE2->Draw();

		canvasEtatoPi0combo->SaveAs(Form("%s/%s_EtatoPi0Ratio_combined_Only010.%s",outputDir.Data(),meson.Data(),suffix.Data()));
		canvasEtatoPi0combo->SaveAs(Form("%s/%s_EtatoPi0Ratio_combined_Only010.%s",paperPlots.Data(),meson.Data(),suffix.Data()));		
		
		canvasEtatoPi0combo->cd();
			TH2F * histo2DEtatoPi0comboBand = new TH2F("histo2DEtatoPi0comboBand","histo2DEtatoPi0comboBand",11000,3.,25.,1000,0.5,2.);
			SetStyleHistoTH2ForGraphs(histo2DEtatoPi0comboBand, "#it{p}_{T} (GeV/#it{c})","#frac{NEQ SHM}{Fit}",0.035,0.04, 0.035,0.04, 1.2,1.);
			histo2DEtatoPi0comboBand->GetXaxis()->SetMoreLogLabels();
			histo2DEtatoPi0comboBand->GetXaxis()->SetLabelOffset(-0.01);
			histo2DEtatoPi0comboBand->Draw("copy");
// 			histo2DEtatoPi0comboBand->GetYaxis()->SetRangeUser(0.,1.2);
			
			TGraphAsymmErrors* graphRatioCombEtatoPi0Stat2760GeVLHC11h_0010 	= (TGraphAsymmErrors*)graphCombEtatoPi0Stat2760GeVLHC11h_0010->Clone();
			graphRatioCombEtatoPi0Stat2760GeVLHC11h_0010 						= CalculateGraphErrRatioToFit(graphRatioCombEtatoPi0Stat2760GeVLHC11h_0010, pol1); 
			TGraphAsymmErrors* graphRatioCombEtatoPi0Sys2760GeVLHC11h_0010 	= (TGraphAsymmErrors*)graphCombEtatoPi0Sys2760GeVLHC11h_0010->Clone();
			graphRatioCombEtatoPi0Sys2760GeVLHC11h_0010 						= CalculateGraphErrRatioToFit(graphRatioCombEtatoPi0Sys2760GeVLHC11h_0010, pol1); 

			TGraphAsymmErrors* graphRatioTheoryCombEtatoPi0Sys2760GeVLHC11h_0010 = (TGraphAsymmErrors*)graphEtaToPi0JetQuenching_0010->Clone();	
			graphRatioTheoryCombEtatoPi0Sys2760GeVLHC11h_0010 = CalculateGraphErrRatioToFit(graphRatioTheoryCombEtatoPi0Sys2760GeVLHC11h_0010, pol1); 

			DrawGammaSetMarkerTGraphAsym(graphRatioTheoryCombEtatoPi0Sys2760GeVLHC11h_0010, 0, 0, colorNLO0010,colorNLO0010, 5, kTRUE,colorNLO0010);
// 			DrawGammaSetMarkerTGraphAsym(graphRatioTheoryCombEtatoPi0Sys2760GeVLHC11h_0010, 0, 0, colorNLO0010,colorNLO0010, widthLinesBoxes, kTRUE, colorNLO0010);
			graphRatioTheoryCombEtatoPi0Sys2760GeVLHC11h_0010->Draw("l,same");

			DrawGammaSetMarkerTGraphAsym(graphRatioCombEtatoPi0Stat2760GeVLHC11h_0010, markerStyleComb, markerSizeComb*2, kBlack, kBlack, widthLinesBoxes, kFALSE);
			graphRatioCombEtatoPi0Stat2760GeVLHC11h_0010->SetLineWidth(widthLinesBoxes);
			DrawGammaSetMarkerTGraphAsym(graphRatioCombEtatoPi0Sys2760GeVLHC11h_0010, markerStyleComb, markerSizeComb*2, kBlack, kBlack, widthLinesBoxes, kTRUE, 0);
			graphRatioCombEtatoPi0Sys2760GeVLHC11h_0010->SetLineWidth(0);
			graphRatioCombEtatoPi0Sys2760GeVLHC11h_0010->Draw("2,same");
			if(noXerrorBars) ProduceGraphAsymmWithoutXErrors(graphRatioCombEtatoPi0Stat2760GeVLHC11h_0010);
			graphRatioCombEtatoPi0Stat2760GeVLHC11h_0010->Draw("p,same,e1");
		
			DrawGammaLines(4., 20.,1., 1.,0.1,kGray);

		canvasEtatoPi0combo->SaveAs(Form("%s/%s_EtatoPi0Ratio_BandOnly010.%s",outputDir.Data(),meson.Data(),suffix.Data()));
		canvasEtatoPi0combo->SaveAs(Form("%s/%s_EtatoPi0Ratio_BandOnly010.%s",paperPlots.Data(),meson.Data(),suffix.Data()));		

		canvasEtatoPi0combo->cd();
			histo2DEtatoPi0combo->Draw("copy");

			TGraphAsymmErrors* graphEtatoPi0SysAndStat = CalculateCombinedSysAndStatError( graphCombEtatoPi0Stat2760GeVLHC11h_0010, graphCombEtatoPi0Sys2760GeVLHC11h_0010);
			DrawGammaSetMarkerTGraphAsym(graphEtatoPi0SysAndStat, markerStyleComb, markerSizeComb*2, kBlack, kBlack, widthLinesBoxes, kFALSE);
			graphEtatoPi0SysAndStat->SetLineWidth(widthLinesBoxes);
			if(noXerrorBars) ProduceGraphAsymmWithoutXErrors(graphEtatoPi0SysAndStat);
			graphEtatoPi0SysAndStat->Draw("p,same,e1");
		
			graphEtaToPi0JetQuenching_0010->Draw("3,same");

		canvasEtatoPi0combo->SaveAs(Form("%s/%s_EtatoPi0Ratio_Band2Only010.%s",outputDir.Data(),meson.Data(),suffix.Data()));
		canvasEtatoPi0combo->SaveAs(Form("%s/%s_EtatoPi0Ratio_Band2Only010.%s",paperPlots.Data(),meson.Data(),suffix.Data()));		
		
		canvasEtatoPi0combo->cd();
			histo2DEtatoPi0combo->Draw("copy");
			
// 			histo2DEtatoPi0combo->GetYaxis()->SetRangeUser(0.,1.05);
// 			histo2DEtatoPi0combo->GetXaxis()->SetRangeUser(0.8,30);

			graphCombEtatoPi0Sys2760GeVLHC11h_2050->Draw("E2same");
			if(noXerrorBars) ProduceGraphAsymmWithoutXErrors(graphCombEtatoPi0Stat2760GeVLHC11h_2050);
			graphCombEtatoPi0Stat2760GeVLHC11h_2050->Draw("p,same,e1");

			TLegend* legendEtatoPi0combo_onlyPbPbOnly2050 = new TLegend(0.49,0.15,0.9,0.23);
			legendEtatoPi0combo_onlyPbPbOnly2050->SetTextSize(0.04);			
			legendEtatoPi0combo_onlyPbPbOnly2050->SetFillColor(0);
			legendEtatoPi0combo_onlyPbPbOnly2050->SetFillStyle(0);
			legendEtatoPi0combo_onlyPbPbOnly2050->SetBorderSize(0);
			legendEtatoPi0combo_onlyPbPbOnly2050->AddEntry(graphCombEtatoPi0Sys2760GeVLHC11h_2050,Form("%s %s",cent2050.Data(),collisionSystem2760GeV.Data()),"fp");
			legendEtatoPi0combo_onlyPbPbOnly2050->Draw();

		canvasEtatoPi0combo->SaveAs(Form("%s/%s_EtatoPi0Ratio_combined_Only2050.%s",outputDir.Data(),meson.Data(),suffix.Data()));
		canvasEtatoPi0combo->SaveAs(Form("%s/%s_EtatoPi0Ratio_combined_Only2050.%s",paperPlots.Data(),meson.Data(),suffix.Data()));
		
				
		canvasEtatoPi0combo->cd();
			histo2DEtatoPi0combo->Draw("copy");
			histo2DEtatoPi0combo->GetYaxis()->SetRangeUser(0.,maxYEtatoPi0);
// 			histo2DEtatoPi0combo->GetXaxis()->SetRangeUser(0.2,25);
			histo2DEtatoPi0combo->GetYaxis()->SetTitleOffset(1.1);
			histo2DEtatoPi0combo->GetYaxis()->SetTitle("Particle ratio");
				
			DrawGammaSetMarkerTGraphAsym(graphChargedRatioKaonToPion0010, 21,2, colorCharged, colorCharged, 0.1, kFALSE);
			DrawGammaSetMarkerTGraphAsym(graphChargedRatioKaonToPionSys0010,21,2, colorCharged, colorCharged, 1, kTRUE);
			graphChargedRatioKaonToPionSys0010->Draw("2same");
			graphChargedRatioKaonToPion0010->Draw("p,same"); 
			
			TLegend* legendChargedRatio = new TLegend(0.12,0.76,0.95,0.92); //0.12,0.76,0.96,0.92);
			legendChargedRatio->SetFillColor(0);
			legendChargedRatio->SetLineColor(0);
			legendChargedRatio->SetTextFont(42);
			legendChargedRatio->SetTextSize(0.04);
			legendChargedRatio->SetMargin(0.17);
			legendChargedRatio->SetHeader(collisionSystem2760GeV.Data());
			legendChargedRatio->SetNColumns(2);
			legendChargedRatio->AddEntry(graphCombEtatoPi0Sys2760GeVLHC11h_0010,Form("#eta/#pi^{0},   %s",cent0010.Data()),"fp");
// 			legendChargedRatio->AddEntry((TObject*)0,"","");
// 			legendChargedRatio->AddEntry(graphChargedRatioKaonToPionSys0010,Form("K^{#pm}/#pi^{#pm}, %s %s",cent0010.Data(),collisionSystem2760GeV.Data()),"fp");
			legendChargedRatio->AddEntry(graphChargedRatioKaonToPionSys0010,Form("K^{#pm}/#pi^{#pm}, %s",cent0010.Data()),"fp");
			legendChargedRatio->AddEntry(graphCombEtatoPi0Sys2760GeVLHC11h_2050,Form("#eta/#pi^{0}, %s",cent2050.Data()),"fp");
			legendChargedRatio->AddEntry((TObject*)0,"PLB 736 (2014) 196",""); //"Phys.Lett.B736 (2014) 196-207","");		
			legendChargedRatio->Draw();

// 			labelEtaToPi0Energy->Draw();
			
			graphCombEtatoPi0Sys2760GeVLHC11h_0010->Draw("E2same");
			if(noXerrorBars) ProduceGraphAsymmWithoutXErrors(graphCombEtatoPi0Stat2760GeVLHC11h_0010);
			graphCombEtatoPi0Stat2760GeVLHC11h_0010->Draw("p,same,e1");

			graphCombEtatoPi0Sys2760GeVLHC11h_2050->Draw("E2same");
			if(noXerrorBars) ProduceGraphAsymmWithoutXErrors(graphCombEtatoPi0Stat2760GeVLHC11h_2050);
			graphCombEtatoPi0Stat2760GeVLHC11h_2050->Draw("p,same,e1");

			labelPreliminaryEtaToPi0->Draw();
		canvasEtatoPi0combo->SaveAs(Form("%s/%s_EtatoPi0Ratio_combined_withKaonsToPions.%s",outputDir.Data(),meson.Data(),suffix.Data()));
		canvasEtatoPi0combo->SaveAs(Form("%s/%s_EtatoPi0Ratio_combined_withKaonsToPions.%s",paperPlots.Data(),meson.Data(),suffix.Data()));
		
		
		TCanvas* canvasRatioEtaToPi0ALICEPbPb = new TCanvas("canvasRatioEtaToPi0ALICEPbPb","",200,10,1350,900);  // gives the page size
		DrawGammaCanvasSettings( canvasRatioEtaToPi0ALICEPbPb, 0.08, 0.02, 0.035, 0.1);
		canvasRatioEtaToPi0ALICEPbPb->SetLogx();

			histo2DEtatoPi0combo->Draw("copy");
			histo2DEtatoPi0combo->GetYaxis()->SetRangeUser(0.,1.1);
			histo2DEtatoPi0combo->GetXaxis()->SetRangeUser(0.3,25.);
			cocktailEtaToPi0Ratio7TeVRebined->Draw("same,hist,c");
			cocktailEtaToPi0Ratio_K0ScaledRebinned->Draw("same,hist,c");
			cocktailEtaToPi0Ratio_MtScaledRebinned->Draw("same,hist,c");
			
			graphCombEtatoPi0Stat2760GeVLHC11h_0010->Draw("same,pe");
			graphCombEtatoPi0Sys2760GeVLHC11h_0010->Draw("same,pE2");

			graphCombEtatoPi0Stat2760GeVLHC11h_2050->Draw("same,pe");
			graphCombEtatoPi0Sys2760GeVLHC11h_2050->Draw("same,pE2");

			TLegend* legendRatioALICEdata2 = new TLegend(0.12,0.66,0.32,0.76);
			legendRatioALICEdata2->SetTextSize(0.04);			
			legendRatioALICEdata2->SetFillColor(0);
			legendRatioALICEdata2->SetFillStyle(0);
			legendRatioALICEdata2->SetBorderSize(0);
			legendRatioALICEdata2->AddEntry(graphCombEtaToPi0RatioSysErrpp7TeV,Form("ALICE, %s",collisionSystemPP7TeV.Data()),"pe");
			legendRatioALICEdata2->AddEntry((TObject*)0,"Phys.Lett.B717 (2012) 162-172","");
		// 	legendRatioALICEdata2->AddEntry(histoPCMEtaToPi0RatioPbPb0010,Form("%s, LHC11h",collisionSystemPbPb0010.Data()),"pe");
		// 	legendRatioALICEdata2->AddEntry(histoPCMEtaToPi0RatioPbPb2050,Form("%s, LHC11h",collisionSystemPbPb2050.Data()),"pe");
// 			legendRatioALICEdata2->Draw();

			TLegend* legendEtatoPi0combo_onlyPbPb2 = new TLegend(0.45,0.11,0.8,0.24);
			legendEtatoPi0combo_onlyPbPb2->SetTextSize(0.04);			
			legendEtatoPi0combo_onlyPbPb2->SetFillColor(0);
			legendEtatoPi0combo_onlyPbPb2->SetFillStyle(0);
			legendEtatoPi0combo_onlyPbPb2->SetBorderSize(0);
			legendEtatoPi0combo_onlyPbPb2->AddEntry(graphCombEtatoPi0Sys2760GeVLHC11h_0010,"0-10% Pb-Pb, #sqrt{#it{s}_{_{NN}}} = 2.76 TeV","fp");
			legendEtatoPi0combo_onlyPbPb2->AddEntry(graphCombEtatoPi0Sys2760GeVLHC11h_2050,"20-50% Pb-Pb, #sqrt{#it{s}_{_{NN}}} = 2.76 TeV","fp");
			legendEtatoPi0combo_onlyPbPb2->Draw();
			
			TLegend* legendRatioALICEpp = new TLegend(0.15,0.75,0.6,0.9);
			legendRatioALICEpp->SetTextSize(0.04);			
			legendRatioALICEpp->SetFillColor(0);
			legendRatioALICEpp->SetFillStyle(0);
			legendRatioALICEpp->SetBorderSize(0);
			legendRatioALICEpp->SetMargin(0.1);
			legendRatioALICEpp->AddEntry(cocktailEtaToPi0Ratio7TeVRebined,Form("#eta from %s as input",collisionSystemPP7TeV.Data()),"pl");
			legendRatioALICEpp->AddEntry(cocktailEtaToPi0Ratio_MtScaledRebinned,"#eta from m_{T} scaled #pi^{0}","pl");
			legendRatioALICEpp->AddEntry(cocktailEtaToPi0Ratio_K0ScaledRebinned,"0-20% Pb-Pb #sqrt{#it{s}_{_{NN}}} = 2.76 TeV, #eta from K^{0}_{s} scaled ","pl");
			legendRatioALICEpp->Draw();
		
		canvasRatioEtaToPi0ALICEPbPb->Update();  
		canvasRatioEtaToPi0ALICEPbPb->SaveAs(Form("%s/EtaToPi0Ratio_DiffSystems_PbPb.%s",outputDir.Data(), suffix.Data()));
// 		canvasRatioEtaToPi0ALICEPbPb->SaveAs(Form("%s/EtaToPi0Ratio_DiffSystems_PbPb.%s",paperPlots.Data(), suffix.Data()));
		
	}
	

	
		
	//******************************************************************************//
	//************************* Saving of final results ****************************//
	//******************************************************************************//
	
	TFile fCombResults(Form("%s/CombinedResultsPaperPbPb2760GeVLHC11h_%s.root", outputDir.Data(),dateForOutput.Data()), "UPDATE");

		graphCombInvYieldTot2760GeVALHC11h_0010->Write(Form("graphInvYield%sComb2760GeVLHC11h_0010",meson.Data()));
		graphCombInvYieldStat2760GeVALHC11h_0010->Write(Form("graphInvYield%sComb2760GeVLHC11hStatErr_0010",meson.Data()));
		graphCombInvYieldSys2760GeVALHC11h_0010->Write(Form("graphInvYield%sComb2760GeVLHC11hSysErr_0010",meson.Data()));    
		
		graphCombInvYieldTot2760GeVALHC11h_2050->Write(Form("graphInvYield%sComb2760GeVLHC11h_2050",meson.Data()));
		graphCombInvYieldStat2760GeVALHC11h_2050->Write(Form("graphInvYield%sComb2760GeVLHC11hStatErr_2050",meson.Data()));
		graphCombInvYieldSys2760GeVALHC11h_2050->Write(Form("graphInvYield%sComb2760GeVLHC11hSysErr_2050",meson.Data()));      

// 		if(meson.CompareTo("Eta")==0){
// 		
// 			graphCombEtatoPi0Sys2760GeVLHC11h_0010->Write("graphCombEtatoPi0Sys2760GeVLHC11h_0010");
// 			graphCombEtatoPi0Stat2760GeVLHC11h_0010->Write("graphCombEtatoPi0Stat2760GeVLHC11h_0010");
// 
// 			graphCombEtatoPi0Sys2760GeVLHC11h_2050->Write("graphCombEtatoPi0Sys2760GeVLHC11h_2050");
// 			graphCombEtatoPi0Stat2760GeVLHC11h_2050->Write("graphCombEtatoPi0Stat2760GeVLHC11h_2050");
// 
// 		}
		
// 		graphPCMPi0CorrYieldSysErrPbPb2760GeV_0010->Write("graphPCMPi0CorrYieldSysErrPbPb2760GeV_0010");
// 		graphPCMPi0InvYieldStatPbPb2760GeV_0010->Write("graphPCMPi0InvYieldStatPbPb2760GeV_0010");
// 		
// 		graphPCMPi0CorrYieldSysErrPbPb2760GeV_2040->Write("graphPCMPi0CorrYieldSysErrPbPb2760GeV_2040");
// 		graphPCMPi0InvYieldStatPbPb2760GeV_2040->Write("graphPCMPi0InvYieldStatPbPb2760GeV_2040");
// 
// 		graphEMCalPi0CorrYieldSysErrPbPb2760GeV_0010->Write("graphEMCalPi0CorrYieldSysErrPbPb2760GeV_0010");
// 		graphEMCalPi0InvYieldStatPbPb2760GeV_0010->Write("graphEMCalPi0InvYieldStatPbPb2760GeV_0010");

// 			graphCombInvYieldTot2760GeVALL_0010->Write(Form("graphInvYield%sComb2760GeVALL_0010",meson.Data()));
// 			graphCombInvYieldStat2760GeVALL_0010->Write(Form("graphInvYield%sComb2760GeVALLStatErr_0010",meson.Data()));
// 			graphCombInvYieldSys2760GeVALL_0010->Write(Form("graphInvYield%sComb2760GeVALLSysErr_0010",meson.Data()));    
// 			
// 			graphCombInvYieldTot2760GeVALL_2040->Write(Form("graphInvYield%sComb2760GeVALL_2040",meson.Data()));
// 			graphCombInvYieldStat2760GeVALL_2040->Write(Form("graphInvYield%sComb2760GeVALLStatErr_2040",meson.Data()));
// 			graphCombInvYieldSys2760GeVALL_2040->Write(Form("graphInvYield%sComb2760GeVALLSysErr_2040",meson.Data()));      
	fCombResults.Close();
		




		
		
}
	
