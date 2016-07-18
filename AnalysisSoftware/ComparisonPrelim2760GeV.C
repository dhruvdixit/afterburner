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
#include "CommonHeaders/FittingGammaConversion.h"
#include "CommonHeaders/ConversionFunctionsBasicsAndLabeling.h"
#include "CommonHeaders/ConversionFunctions.h"
#include "CommonHeaders/CombinationFunctions.h"

struct SysErrorConversion {
   Double_t value;
   Double_t error;
   //	TString name;
};



void ComparisonPrelim2760GeV(const char *suffix = "eps"){

	TString 	FileDirectory[2];
   TString 	cutNumberAdv[2];
	char* 	Input[256];
	TString 	prefix2;
	Double_t 	nColls[2];

	StyleSettingsThesis();

	SetPlotStyle();

	Bool_t pictDrawingOptions[4] = {kFALSE, kFALSE, kFALSE, kTRUE};

	prefix2 = 			"data";
	pictDrawingOptions[1] = 	kFALSE;
   TString dateForOutput = ReturnDateStringForOutput();
   
	TString collisionSystem = "pp @ 2.76 TeV";
	
	TString FileNameCorrectedCombined[3];
	FileNameCorrectedCombined[0] = "/home/fredi/Photon/Results/ppAnalysis2760GeVFeb2013/CombinedResultsPaperX.root";
	FileNameCorrectedCombined[1] = "/home/fredi/Photon/Results/PbPbAnalysisFinerCentOnlyMinBias/FinalResults/CombinedResultsPaperX_IncludingPP2760YShifted.root";
   FileNameCorrectedCombined[2] = "/home/fredi/Photon/Results/PbPbNewMCTest/CombinedResultsPaperX_19_Sep_2013.root";
	TFile *Cutcorrfile[3];
	TFile *Cutuncorrfile[3];
   TString FileNameCorrectedPCM[3];
   FileNameCorrectedPCM[0] = "/home/fredi/Photon/Results/ppAnalysis2760GeVFeb2013/0000011002093663003800000_01631031009/data_GammaConversionResultsFullCorrectionNoBinShifting.root";
   FileNameCorrectedPCM[1] = "/home/fredi/Photon/Results/PbPbAnalysisFinerCentOnlyMinBias/FinalResults/data_GammaConversionResultsFullCorrection_110521_PreliminaryQM2011.root";
   FileNameCorrectedPCM[2] = "/home/fredi/Photon/Results/PbPbNewMCTest/000001100209366300380000000_01631031009000/data_PCMResultsFullCorrection_PP_NoBinShifting.root";

	TGraphAsymmErrors *finalSpectraComb[3];
	TGraphAsymmErrors *finalSpectraStatErr[3];
	TGraphAsymmErrors *finalSpectraSysErr[3];
	TGraphAsymmErrors *finalSpectraPCMStatErr[3];
	TGraphAsymmErrors *finalSpectraPCMSysErr[3];	
	TGraphAsymmErrors *finalSpectraPHOSStatErr[3];
	TGraphAsymmErrors *finalSpectraPHOSSysErr[3];
	
	TH1D *histoEffi[3];
	TH1D *histoRawYield[3];
	TDirectory *directoryPi02760GeV[3];
	TH1D* histoInvCrossSectionPi02760GeV[3];
	TGraphAsymmErrors* graphInvCrossSectionSysAPi02760GeV[3];
	TFile* CutcorrfilePCM[3];
	
	cout<< FileNameCorrectedCombined[0] << endl;
	Cutcorrfile[0] = new TFile( FileNameCorrectedCombined[0].Data());
	cout << "here" << endl;
	finalSpectraComb[0] = (TGraphAsymmErrors*)Cutcorrfile[0]->Get("graphInvCrossSectionPi0Comb2760GeV");
	cout << "here" << endl;
	finalSpectraStatErr[0] = (TGraphAsymmErrors*)Cutcorrfile[0]->Get("graphInvCrossSectionPi0Comb2760GeVStatErr");
	cout << "here" << endl;
	finalSpectraSysErr[0] = (TGraphAsymmErrors*)Cutcorrfile[0]->Get("graphInvCrossSectionPi0Comb2760GeVSysErr");
	finalSpectraPCMStatErr[0] = (TGraphAsymmErrors*)Cutcorrfile[0]->Get("graphInvCrossSectionPi0PCM2760GeVStatErr");
	cout << "here" << endl;
	finalSpectraPCMSysErr[0] = (TGraphAsymmErrors*)Cutcorrfile[0]->Get("graphInvCrossSectionPi0PCM2760GeVSysErr");
   finalSpectraPCMSysErr[0]->Print();
	finalSpectraPHOSStatErr[0] = (TGraphAsymmErrors*)Cutcorrfile[0]->Get("graphInvCrossSectionPi0PHOS2760GeVStatErr");
	cout << "here" << endl;
	finalSpectraPHOSSysErr[0] = (TGraphAsymmErrors*)Cutcorrfile[0]->Get("graphInvCrossSectionPi0PHOS2760GeVSysErr");
	
   cout << FileNameCorrectedPCM[0] << endl;
   CutcorrfilePCM[0] = new TFile( FileNameCorrectedPCM[0].Data());
   directoryPi02760GeV[0] =         (TDirectory*)CutcorrfilePCM[0]->Get("Pi02.76TeV");    
   histoInvCrossSectionPi02760GeV[0]=        (TH1D*)directoryPi02760GeV[0]->Get("InvCrossSectionPi0");
   graphInvCrossSectionSysAPi02760GeV[0]=       (TGraphAsymmErrors*)directoryPi02760GeV[0]->Get("InvCrossSectionPi0SysA");
   
	cout << "here" << endl;
	cout<<"=========================="<<endl;

	cout<< FileNameCorrectedCombined[1] << endl;
// 	Cutcorrfile[1] = new TFile("/home/fredi/Photon/Results/ppAnalysis2760GeVDec/FinalResults/CombinedResultsPaperX_IncludingPP2760YShifted.root");
// 	finalSpectraComb[1] = (TGraphAsymmErrors*)Cutcorrfile[1]->Get("graphInvCrossSectionPi0Comb2760GeV_PrelimQM2011");
// 	finalSpectraStatErr[1] = (TGraphAsymmErrors*)Cutcorrfile[1]->Get("graphInvCrossSectionPi0Comb2760GeVStatErr_PrelimQM2011");
// 	cout << "here" << endl;
// 	finalSpectraSysErr[1] = (TGraphAsymmErrors*)Cutcorrfile[1]->Get("graphInvCrossSectionPi0Comb2760GeVSysErr_PrelimQM2011");
// 	cout << "here" << endl;
	Cutcorrfile[1] = new TFile(FileNameCorrectedCombined[1].Data());
	finalSpectraComb[1] = (TGraphAsymmErrors*)Cutcorrfile[1]->Get("graphInvCrossSectionPi0Comb2760GeV_PrelimQM2011");
	finalSpectraPCMStatErr[1] = (TGraphAsymmErrors*)Cutcorrfile[1]->Get("graphInvCrossSectionPi0PCMStat2760GeV_PrelimQM2011_YShifted");
	cout << "here" << endl;
	finalSpectraPCMSysErr[1] = (TGraphAsymmErrors*)Cutcorrfile[1]->Get("graphInvCrossSectionPi0PCMSys2760GeV_PrelimQM2011_YShifted");
	finalSpectraPHOSStatErr[1] = (TGraphAsymmErrors*)Cutcorrfile[1]->Get("graphInvCrossSectionPi0PHOSSys2760GeV_PrelimQM2011_YShifted");
	cout << "here" << endl;
	finalSpectraPHOSSysErr[1] = (TGraphAsymmErrors*)Cutcorrfile[1]->Get("graphInvCrossSectionPi0PHOSSys2760GeV_PrelimQM2011_YShifted");
	
   cout << FileNameCorrectedPCM[1] << endl;
   CutcorrfilePCM[1] = new TFile( FileNameCorrectedPCM[1].Data());
   directoryPi02760GeV[1] =         (TDirectory*)CutcorrfilePCM[1]->Get("Pi02.76TeV");    
   histoInvCrossSectionPi02760GeV[1]=        (TH1D*)directoryPi02760GeV[1]->Get("InvCrossSectionPi0");
   graphInvCrossSectionSysAPi02760GeV[1]=       (TGraphAsymmErrors*)directoryPi02760GeV[1]->Get("InvCrossSectionPi0SysA");

	cout<<"=========================="<<endl;

   cout<< FileNameCorrectedCombined[2] << endl;
   Cutcorrfile[2] = new TFile( FileNameCorrectedCombined[2].Data());
   cout << "here" << endl;
   finalSpectraComb[2] = (TGraphAsymmErrors*)Cutcorrfile[2]->Get("graphInvCrossSectionPi0Comb2760GeV");
   cout << "here" << endl;
   finalSpectraStatErr[2] = (TGraphAsymmErrors*)Cutcorrfile[2]->Get("graphInvCrossSectionPi0Comb2760GeVStatErr");
   cout << "here" << endl;
   finalSpectraSysErr[2] = (TGraphAsymmErrors*)Cutcorrfile[2]->Get("graphInvCrossSectionPi0Comb2760GeVSysErr");
   finalSpectraPCMStatErr[2] = (TGraphAsymmErrors*)Cutcorrfile[2]->Get("graphInvCrossSectionPi0PCM2760GeVStatErr");
   cout << "here" << endl;
   finalSpectraPCMSysErr[2] = (TGraphAsymmErrors*)Cutcorrfile[2]->Get("graphInvCrossSectionPi0PCM2760GeVSysErr");
   finalSpectraPCMSysErr[2]->Print();
   finalSpectraPHOSStatErr[2] = (TGraphAsymmErrors*)Cutcorrfile[2]->Get("graphInvCrossSectionPi0PHOS2760GeVStatErr");
   cout << "here" << endl;
   finalSpectraPHOSSysErr[2] = (TGraphAsymmErrors*)Cutcorrfile[2]->Get("graphInvCrossSectionPi0PHOS2760GeVSysErr");

   cout << FileNameCorrectedPCM[2] << endl;
   CutcorrfilePCM[2] = new TFile( FileNameCorrectedPCM[2].Data());
   directoryPi02760GeV[2] =         (TDirectory*)CutcorrfilePCM[2]->Get("Pi02.76TeV");    
   histoInvCrossSectionPi02760GeV[2]=        (TH1D*)directoryPi02760GeV[2]->Get("InvCrossSectionPi0");
   graphInvCrossSectionSysAPi02760GeV[2]=       (TGraphAsymmErrors*)directoryPi02760GeV[2]->Get("InvCrossSectionPi0SysA");

   cout << "here" << endl;
   cout<<"=========================="<<endl;

   
	Double_t paramGraph[3] = {1.0e12,7.,0.13};
	TF1*	fitInvCrossSectionPi02760GeV = FitObject("l","fitInvCrossSectionPi02760GeV","Pi0",finalSpectraComb[1],0.4,12.,paramGraph);
	cout << WriteParameterToFile(fitInvCrossSectionPi02760GeV)<< endl;

	TGraphAsymmErrors *graphRatioFinalToPrelimStat = CalculateGraphErrRatioToFit (finalSpectraStatErr[2], fitInvCrossSectionPi02760GeV); 
	TGraphAsymmErrors *graphRatioFinalToPrelimSys = CalculateGraphErrRatioToFit (finalSpectraSysErr[2], fitInvCrossSectionPi02760GeV); 
	TGraphAsymmErrors *graphRatioFinalPCMToPrelimStat = CalculateGraphErrRatioToFit (finalSpectraPCMStatErr[2], fitInvCrossSectionPi02760GeV); 
	TGraphAsymmErrors *graphRatioFinalPCMToPrelimSys = CalculateGraphErrRatioToFit (finalSpectraPCMSysErr[2], fitInvCrossSectionPi02760GeV); 
	TGraphAsymmErrors *graphRatioFinalPHOSToPrelimStat = CalculateGraphErrRatioToFit (finalSpectraPHOSStatErr[2], fitInvCrossSectionPi02760GeV); 
	TGraphAsymmErrors *graphRatioFinalPHOSToPrelimSys = CalculateGraphErrRatioToFit (finalSpectraPHOSSysErr[2], fitInvCrossSectionPi02760GeV); 
	TGraphAsymmErrors *graphRatioFinalPCMPrelimToPrelimStat = CalculateGraphErrRatioToFit (finalSpectraPCMStatErr[1], fitInvCrossSectionPi02760GeV); 
	TGraphAsymmErrors *graphRatioFinalPCMPrelimToPrelimSys = CalculateGraphErrRatioToFit (finalSpectraPCMSysErr[1], fitInvCrossSectionPi02760GeV); 
	TGraphAsymmErrors *graphRatioFinalPHOSPrelimToPrelimStat = CalculateGraphErrRatioToFit (finalSpectraPHOSStatErr[1], fitInvCrossSectionPi02760GeV); 
	TGraphAsymmErrors *graphRatioFinalPHOSPrelimToPrelimSys = CalculateGraphErrRatioToFit (finalSpectraPHOSSysErr[1], fitInvCrossSectionPi02760GeV); 
	
   TGraphAsymmErrors* graphRatioFinalUpdatedPCMToFinalSys = CalculateGraphAsymErrRatioToGraphErr (finalSpectraStatErr[2],finalSpectraStatErr[0],kTRUE);
   TH1D* histoRatioFinalUpdatedPCMToFinalStat = (TH1D*)histoInvCrossSectionPi02760GeV[2]->Clone("histoRatioFinalUpdatedPCMToFinalStat");
   histoRatioFinalUpdatedPCMToFinalStat->Divide(histoRatioFinalUpdatedPCMToFinalStat,histoInvCrossSectionPi02760GeV[0],1.,1.,"B");
   
	//**************************************************************************************
	//********************* Plotting RAW-Yield *********************************************
	//**************************************************************************************

	TCanvas* canvasFraction = new TCanvas("canvasFraction","",1550,1200);  // gives the page size
	canvasFraction->SetTickx();
	canvasFraction->SetTicky();
	canvasFraction->SetGridx(0);
	canvasFraction->SetGridy(0);
	canvasFraction->SetLogy(0);
	canvasFraction->SetLogx(1);
	canvasFraction->SetLeftMargin(0.09);
	canvasFraction->SetRightMargin(0.02);
	canvasFraction->SetTopMargin(0.02);
	canvasFraction->SetFillColor(0);

	TH2F * ratio2DInvXSectionOnlyPi0;
	ratio2DInvXSectionOnlyPi0 = new TH2F("ratio2DInvXSectionOnlyPi0","ratio2DInvXSectionOnlyPi0",1000,0.33,15.,1000,0.5,2.1);
	SetStyleHistoTH2ForGraphs(ratio2DInvXSectionOnlyPi0, "p_{T} (GeV/c)","Final/Fit to Prelim", 0.03,0.042, 0.03,0.042, 0.9,0.82, 512, 505);
// 	ratio2DInvXSectionOnlyPi0->GetXaxis()->SetLabelOffset(-0.015);
// 	ratio2DInvXSectionOnlyPi0->GetYaxis()->SetLabelOffset(0.01);
	ratio2DInvXSectionOnlyPi0->DrawCopy(); 
	
	DrawGammaSetMarkerTGraphAsym(graphRatioFinalToPrelimSys, 20,1.5, kBlue+2 , kBlue+2, 1., kTRUE);
	graphRatioFinalToPrelimSys->Draw("E2same");
	DrawGammaSetMarkerTGraphAsym(graphRatioFinalPCMToPrelimSys, 20,1.5, kBlack , kBlack, 1., kTRUE);
	graphRatioFinalPCMToPrelimSys->Draw("E2same");
	DrawGammaSetMarkerTGraphAsym(graphRatioFinalPHOSToPrelimSys, 20,1.5, kRed+2 , kRed+2, 1., kTRUE);
	graphRatioFinalPHOSToPrelimSys->Draw("E2same");
	
	DrawGammaSetMarkerTGraphAsym(graphRatioFinalToPrelimStat, 20,2., kBlue+2 , kBlue+2);
 	graphRatioFinalToPrelimStat->Draw("p,same,e1");
	DrawGammaSetMarkerTGraphAsym(graphRatioFinalPCMToPrelimStat, 20,2., kBlack , kBlack);
 	graphRatioFinalPCMToPrelimStat->Draw("p,same,e1");
	DrawGammaSetMarkerTGraphAsym(graphRatioFinalPHOSToPrelimStat, 20,2., kRed+2 , kRed+2);
 	graphRatioFinalPHOSToPrelimStat->Draw("p,same,e1");

	TLegend* legendPrelim = new TLegend(0.18,0.83,0.4,0.95);
		legendPrelim->SetFillColor(0);
		legendPrelim->SetLineColor(0);
// 		legendPrelim->SetNColumns(2);
		legendPrelim->SetTextSize(0.045);
		legendPrelim->AddEntry(graphRatioFinalToPrelimSys,"#pi^{0} combined/ fit to combined prelim #pi^{0}","p");
		legendPrelim->AddEntry(graphRatioFinalPCMToPrelimSys,"#pi^{0} PCM/ fit to combined prelim #pi^{0}","p");
		legendPrelim->AddEntry(graphRatioFinalPHOSToPrelimSys,"#pi^{0} PHOS/ fit to combined prelim #pi^{0}","p");
		legendPrelim->Draw();

		legendPrelim->Draw();
	
	canvasFraction->Update();
	DrawGammaLines(0., 15.,1., 1.,0.1);

	canvasFraction->SaveAs(Form("Pi0_Ratio2760GeVFinalDivPrelim_%s.%s",dateForOutput.Data(),suffix));


	canvasFraction->cd();
	ratio2DInvXSectionOnlyPi0->DrawCopy(); 
	
	DrawGammaSetMarkerTGraphAsym(graphRatioFinalPCMPrelimToPrelimSys, 20,1.5, kBlack , kBlack, 1., kTRUE);
	graphRatioFinalPCMPrelimToPrelimSys->Draw("E2same");
	DrawGammaSetMarkerTGraphAsym(graphRatioFinalPHOSPrelimToPrelimSys, 20,1.5, kRed+2 , kRed+2, 1., kTRUE);
	graphRatioFinalPHOSPrelimToPrelimSys->Draw("E2same");
	
	DrawGammaSetMarkerTGraphAsym(graphRatioFinalPCMPrelimToPrelimStat, 20,2., kBlack , kBlack);
 	graphRatioFinalPCMPrelimToPrelimStat->Draw("p,same,e1");
	DrawGammaSetMarkerTGraphAsym(graphRatioFinalPHOSPrelimToPrelimStat, 20,2., kRed+2 , kRed+2);
 	graphRatioFinalPHOSPrelimToPrelimStat->Draw("p,same,e1");

	TLegend* legendPi0PrelimQM2011 = new TLegend(0.18,0.83,0.4,0.95);
		legendPi0PrelimQM2011->SetFillColor(0);
		legendPi0PrelimQM2011->SetLineColor(0);
// 		legendPi0PrelimQM2011->SetNColumns(2);
		legendPi0PrelimQM2011->SetTextSize(0.045);
		legendPi0PrelimQM2011->AddEntry(graphRatioFinalPCMToPrelimSys,"#pi^{0} PCM prelim/ fit to combined prelim #pi^{0}","p");
		legendPi0PrelimQM2011->AddEntry(graphRatioFinalPHOSToPrelimSys,"#pi^{0} PHOS prelim / fit to combined prelim #pi^{0}","p");
		legendPi0PrelimQM2011->Draw();

		legendPi0PrelimQM2011->Draw();
	
	canvasFraction->Update();
	DrawGammaLines(0., 15.,1., 1.,0.1);

	canvasFraction->SaveAs(Form("Pi0_Ratio2760GeVPrelimDivPrelim.%s",suffix));
   
   
   canvasFraction->cd();
   TH2F * ratio2DInvXSectionOnlyPi02;
   ratio2DInvXSectionOnlyPi02 = new TH2F("ratio2DInvXSectionOnlyPi02","ratio2DInvXSectionOnlyPi02",1000,0.33,15.,1000,0.5,2.1);
   SetStyleHistoTH2ForGraphs(ratio2DInvXSectionOnlyPi02, "p_{T} (GeV/c)","Final/Prelim", 0.03,0.042, 0.03,0.042, 0.9,0.82, 512, 505);
//    ratio2DInvXSectionOnlyPi0->GetXaxis()->SetLabelOffset(-0.015);
//    ratio2DInvXSectionOnlyPi0->GetYaxis()->SetLabelOffset(0.01);
   ratio2DInvXSectionOnlyPi02->DrawCopy(); 
   
    TH1D* histoRatioPCM_FinalOverPrelimStat = (TH1D*)histoInvCrossSectionPi02760GeV[1]->Clone("histoRatioPCM_FinalOverPrelimStat");
//    histoRatioPCM_FinalOverPrelimStat->Divide(histoRatioPCM_FinalOverPrelimStat,histoInvCrossSectionPi02760GeV[1],1.,1.,"B");
//    
   for (Int_t i = 2; i < histoInvCrossSectionPi02760GeV[1]->GetNbinsX()+1; i++){
     cout <<  i << "\t" << histoInvCrossSectionPi02760GeV[1]->GetBinCenter(i)-histoInvCrossSectionPi02760GeV[1]->GetBinWidth(i)/2 << endl;
     histoRatioPCM_FinalOverPrelimStat->SetBinContent(i,histoInvCrossSectionPi02760GeV[2]->GetBinContent(i)/histoInvCrossSectionPi02760GeV[1]->GetBinContent(i));
     Double_t error =  TMath::Sqrt( pow(histoInvCrossSectionPi02760GeV[2]->GetBinError(i)/histoInvCrossSectionPi02760GeV[1]->GetBinContent(i),2)  + pow( histoInvCrossSectionPi02760GeV[1]->GetBinError(i)*histoInvCrossSectionPi02760GeV[2]->GetBinContent(i)/pow(histoInvCrossSectionPi02760GeV[1]->GetBinContent(i),2),2) );
     histoRatioPCM_FinalOverPrelimStat->SetBinError(i,error);
     cout <<  i << "\t" << histoRatioPCM_FinalOverPrelimStat->GetBinContent(i) << "\t +- " << histoRatioPCM_FinalOverPrelimStat->GetBinError(i) << endl;
   }
   for (Int_t i = 1; i < histoInvCrossSectionPi02760GeV[2]->GetNbinsX()+1; i++){
     cout <<  i << "\t" << histoInvCrossSectionPi02760GeV[2]->GetBinCenter(i)-histoInvCrossSectionPi02760GeV[2]->GetBinWidth(i)/2 << endl;
   }
   
   
   TGraphAsymmErrors *graphRatioPCM_FinalOverPrelimSys = CalculateGraphAsymErrRatioToGraphErr (graphInvCrossSectionSysAPi02760GeV[2], graphInvCrossSectionSysAPi02760GeV[1]);
   
   DrawGammaSetMarkerTGraphAsym(graphRatioPCM_FinalOverPrelimSys, 20,1.5, kBlack , kBlack, 1., kTRUE);
   graphRatioPCM_FinalOverPrelimSys->Draw("E2same");
  
   DrawGammaSetMarker(histoRatioPCM_FinalOverPrelimStat, 20,2., kBlack , kBlack);
   histoRatioPCM_FinalOverPrelimStat->Draw("p,same,e1");
   
   TLatex *labelPi0PCM = new TLatex(0.15,0.93,"PCM current/ PCM preliminary, removed mat. error from systematics");
   SetStyleTLatex( labelPi0PCM, 0.036,4);
   labelPi0PCM->Draw();
   TLatex *labelPi0PCM2 = new TLatex(0.15,0.89,"Material error old: +8.3%, -4.8%");
   SetStyleTLatex( labelPi0PCM2, 0.036,4);
   labelPi0PCM2->Draw();
   TLatex *labelPi0PCM3 = new TLatex(0.15,0.85,"Material error new: #pm 9.0%");
   SetStyleTLatex( labelPi0PCM3, 0.036,4);
   labelPi0PCM3->Draw();

   canvasFraction->Update();
   DrawGammaLines(0., 15.,1., 1.,0.1);

   canvasFraction->SaveAs(Form("Pi0_Ratio2760GeVFinalDivPrelimPCMPoints_%s.%s",dateForOutput.Data(),suffix));
   
   canvasFraction->cd();
   ratio2DInvXSectionOnlyPi0->GetYaxis()->SetTitle("Final/FinalUpdatedStat");
   ratio2DInvXSectionOnlyPi0->GetYaxis()->SetRangeUser(0.9,1.1);
   ratio2DInvXSectionOnlyPi0->DrawCopy(); 
   
   /*DrawGammaSetMarkerTGraphAsym(graphRatioFinalUpdatedPCMToFinalStat, 20,1.5, kBlack , kBlack, 1., kTRUE);
   graphRatioFinalUpdatedPCMToFinalStat->Draw("Epsame");
   */
   DrawGammaSetMarker(histoRatioFinalUpdatedPCMToFinalStat, 20,1., kBlue , kBlue);
   histoRatioFinalUpdatedPCMToFinalStat->Draw("E1psame");
   canvasFraction->Update();
   DrawGammaLines(0., 15.,1., 1.,0.1);

   canvasFraction->SaveAs(Form("Pi0_Ratio2760GeVFinalDivFinalUpdatedStat_%s.%s",dateForOutput.Data(),suffix));   
	delete canvasFraction;
   
   

}


