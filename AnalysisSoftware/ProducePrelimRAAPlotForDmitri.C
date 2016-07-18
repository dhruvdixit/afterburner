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
#include "TArrow.h"
#include "TGraphAsymmErrors.h" 
#include "TGaxis.h"
#include "TMarker.h"
#include "CommonHeaders/PlottingGammaConversionAdditional.h"
#include "CommonHeaders/PlottingGammaConversionHistos.h"
#include "CommonHeaders/ConversionFunctionsBasicsAndLabeling.h"
#include "CommonHeaders/ConversionFunctions.h"
#include "TFitResultPtr.h"
#include "TFitResult.h"
#include "TDirectoryFile.h"
#include "TPad.h"

void ProducePrelimRAAPlotForDmitri(){
	gROOT->Reset();	
	gROOT->SetStyle("Plain");
	
	StyleSettingsThesis();	
	SetPlotStyle();
	
	TString collisionSystem = "Pb-Pb #sqrt{#it{s}_{_{NN}}} = 2.76 TeV";		
	TString collisionSystemCent = "0-20% Pb-Pb #sqrt{#it{s}_{_{NN}}} = 2.76 TeV";		
	TString collisionSystemPer = "60-80% Pb-Pb #sqrt{#it{s}_{_{NN}}} = 2.76 TeV";		
	
	TFile* fileConversions = 		new TFile("FinalResults/Neutral_Pions_CTS_CONV_110521.root");
	TH1D*	histoRAA0020 = (TH1D*)fileConversions->Get("histoR_AA_00_20");
	TH1D*	histoRAA2040 = (TH1D*)fileConversions->Get("histoR_AA_20_40");
	TH1D*	histoRAA4060 = (TH1D*)fileConversions->Get("histoR_AA_40_60");
	TH1D*	histoRAA6080 = (TH1D*)fileConversions->Get("histoR_AA_60_80");
	TGraphAsymmErrors*	graphRAASyst0020 = (TGraphAsymmErrors*)fileConversions->Get("histoR_AA_00_20_sys");
	TGraphAsymmErrors*	graphRAASyst2040 = (TGraphAsymmErrors*)fileConversions->Get("histoR_AA_20_40_sys");
	TGraphAsymmErrors*	graphRAASyst4060 = (TGraphAsymmErrors*)fileConversions->Get("histoR_AA_40_60_sys");
	TGraphAsymmErrors*	graphRAASyst6080 = (TGraphAsymmErrors*)fileConversions->Get("histoR_AA_60_80_sys");
	graphRAASyst0020->RemovePoint(0);
	graphRAASyst0020->RemovePoint(0);
	graphRAASyst6080->RemovePoint(0);
	graphRAASyst6080->RemovePoint(0);
	
	TString fileNameTheoryInput = "ExternalInputPbPb/Theory/TheoryCompilationPbPb.root ";
	TString fileNameDataOtherEnergyInput = "ExternalInputPbPb/OtherExperiments/DataCompilationFromOtherEnergiesPbPb.root";

	TFile* fileTheoryGraphs = new TFile(fileNameTheoryInput);
	Vitev_Bas_Raa_0020 = (TGraphErrors*)fileTheoryGraphs->Get("graphVitevBasRAA0020");
	Vitev_ShlSel_Raa_0020 = (TGraphErrors*)fileTheoryGraphs->Get("graphVitevShlSelRAA0020");
	Xiao_Raa_0020 = (TGraphErrors*)fileTheoryGraphs->Get("graphXiaoRAA0020");
	
	Xiao_Raa_2040 = (TGraphErrors*)fileTheoryGraphs->Get("graphXiaoRAA2040");
	Xiao_Raa_4060 = (TGraphErrors*)fileTheoryGraphs->Get("graphXiaoRAA4060");
	Xiao_Raa_6080 = (TGraphErrors*)fileTheoryGraphs->Get("graphXiaoRAA6080");
	Xiao_Raa_4060->Print();
	for (Int_t i = 0; i < 49; i++){
		Xiao_Raa_0020->RemovePoint(12);
		Xiao_Raa_2040->RemovePoint(12);
		Xiao_Raa_4060->RemovePoint(12);
		Xiao_Raa_6080->RemovePoint(12);
	}
// 	
	gWHDG_Raa_0020 = (TGraphAsymmErrors*)fileTheoryGraphs->Get("graphWHDGRAA0020");
	gWHDG_Raa_2040 = (TGraphAsymmErrors*)fileTheoryGraphs->Get("graphWHDGRAA2040");
	gWHDG_Raa_4060 = (TGraphAsymmErrors*)fileTheoryGraphs->Get("graphWHDGRAA4060");
	gWHDG_Raa_6080 = (TGraphAsymmErrors*)fileTheoryGraphs->Get("graphWHDGRAA6080");
	for (Int_t i = 0; i < 1; i++){
		gWHDG_Raa_0020->RemovePoint(3);
		gWHDG_Raa_2040->RemovePoint(3);
		gWHDG_Raa_4060->RemovePoint(3);
		gWHDG_Raa_6080->RemovePoint(3);
	}
	
	TFile* fileDataOtherEnergies = new TFile(fileNameDataOtherEnergyInput);
	graphWA98_17_3GeVRAA_0013= (TGraphErrors*)fileDataOtherEnergies->Get("graphWA98RAA_0013");
	graphPHENIX200GeVRAA_0020= (TGraphErrors*)fileDataOtherEnergies->Get("graphPHENIX200GeVRAA_0020");
	graphPHENIX200GeVRAA_2040= (TGraphErrors*)fileDataOtherEnergies->Get("graphPHENIX200GeVRAA_2040");
	graphPHENIX200GeVRAA_4060= (TGraphErrors*)fileDataOtherEnergies->Get("graphPHENIX200GeVRAA_4060");
	graphPHENIX200GeVRAA_6080= (TGraphErrors*)fileDataOtherEnergies->Get("graphPHENIX200GeVRAA_6080");
	graphPHENIX39GeVRAA_0010= (TGraphErrors*)fileDataOtherEnergies->Get("graphPHENIX39GeVRAA_0010");
	graphPHENIX39GeVRAA_0020= (TGraphErrors*)fileDataOtherEnergies->Get("graphPHENIX39GeVRAA_0020");
	graphPHENIX39GeVRAA_2040= (TGraphErrors*)fileDataOtherEnergies->Get("graphPHENIX39GeVRAA_2040");
	graphPHENIX39GeVRAA_4060= (TGraphErrors*)fileDataOtherEnergies->Get("graphPHENIX39GeVRAA_4060");
	graphPHENIX39GeVRAA_6080= (TGraphErrors*)fileDataOtherEnergies->Get("graphPHENIX39GeVRAA_6086");
	graphPHENIX62GeVRAA_0010= (TGraphErrors*)fileDataOtherEnergies->Get("graphPHENIX62GeVRAA_0010");
	graphPHENIX62GeVRAA_0020= (TGraphErrors*)fileDataOtherEnergies->Get("graphPHENIX62GeVRAA_0020");
	graphPHENIX62GeVRAA_2040= (TGraphErrors*)fileDataOtherEnergies->Get("graphPHENIX62GeVRAA_2040");
	graphPHENIX62GeVRAA_4060= (TGraphErrors*)fileDataOtherEnergies->Get("graphPHENIX62GeVRAA_4060");
	graphPHENIX62GeVRAA_6080= (TGraphErrors*)fileDataOtherEnergies->Get("graphPHENIX62GeVRAA_6086");
	
	TFile* fileChargedPionRAAPrelim2012 = new TFile("ExternalInputPbPb/RAA_ChargedPion_02082012.root");
	TH1D*	hRAA_Pion_stat_20_40 = (TH1D*)fileChargedPionRAAPrelim2012->Get("hRAA_Pion_stat_20_40");
	TH1D*	hRAA_Pion_syst_20_40 = (TH1D*)fileChargedPionRAAPrelim2012->Get("hRAA_Pion_syst_20_40");
	TH1D*	hRAA_Pion_stat_40_60 = (TH1D*)fileChargedPionRAAPrelim2012->Get("hRAA_Pion_stat_40_60");
	TH1D*	hRAA_Pion_syst_40_60 = (TH1D*)fileChargedPionRAAPrelim2012->Get("hRAA_Pion_syst_40_60");
	TH1D*	hRAA_Pion_stat_60_80 = (TH1D*)fileChargedPionRAAPrelim2012->Get("hRAA_Pion_stat_60_80");
	TH1D*	hRAA_Pion_syst_60_80 = (TH1D*)fileChargedPionRAAPrelim2012->Get("hRAA_Pion_syst_60_80");
	TH1D*	hRAA_Pion_stat_0_20 = (TH1D*)fileChargedPionRAAPrelim2012->Get("hRAA_Pion_stat_0_20");
	TH1D*	hRAA_Pion_syst_0_20 = (TH1D*)fileChargedPionRAAPrelim2012->Get("hRAA_Pion_syst_0_20");
	
	Style_t 	markerStylePHENIX200GeV 	= 25 ;
	Style_t 	markerStylePHENIX62GeV 	= 27 ;
	Style_t 	markerStylePHENIX39GeV 	= 24 ;
	Style_t 	markerStyleWA98 	= 28 ;
	Size_t 	markerSizePHENIX200GeV 	= 2.;
	Size_t 	markerSizePHENIX62GeV 	= 2.5;
	Size_t 	markerSizePHENIX39GeV 	= 2.;
	Size_t 	markerSizeWA98 	= 2.3;

	Float_t 		pictDrawingCoordinates[9] = 		{0.7, 0.84, 0.7, 0.06, 0.58,0.82, 0.09, 0.03,0};
	Float_t 		pictDrawingCoordinates0020[9] = 		{0.68, 0.84, 0.68, 0.06, 0.55,0.81, 0.09, 0.03,0};
	Float_t 		pictDrawingCoordinates6080[9] = 		{0.27, 0.16, 0.27, 0.06, 0.15,0.14, 0.09, 0.03,0};
	Bool_t 		pictDrawingOptions[4] = 			{kFALSE, kFALSE, kFALSE, kTRUE};
	
	Color_t color_all = kBlack;
	Color_t color_all_sys = kGray;
	Color_t color_0020 = kRed+1;
	Color_t color_0020_sys = kRed-9;
	Color_t color_2040 = kGreen+3;
	Color_t color_2040_sys = kGreen-9;
	Color_t color_4060 = kBlue+1;
	Color_t color_4060_sys = kBlue-9;
	Color_t color_6080 = kMagenta+3;
	Color_t color_6080_sys = kMagenta-9;
	Color_t	colorWHDG0020				= kRed-4;
	Color_t	colorWHDG6080				= kMagenta-3;
	Color_t	colorXiao0020				= kRed+3;
	Color_t	colorXiao6080				= kMagenta+3;
	Color_t	colorVitevShlSel0020				= kRed+4;
	Color_t	colorVitevShlSel6080				= kMagenta+4;
	Color_t	colorVitevBas0020				= kRed-6;
	Color_t	colorVitevBas6080				= kMagenta-6;
	Style_t 	markerStyleCommmonSpectrum0020 	= 20 ;
	Style_t 	markerStyleCommmonSpectrum6080 	= 33 ;
	Size_t 	markerSizeSpectrum 	= 1.;
	//********************************************************************************************************************************************
	//************************************************************ all Pb-Pb Raa *****************************************************************
	TCanvas* canvassRAAAll = new TCanvas("canvassRAAAll","",200,10,1420,1320);  // gives the page size
	DrawGammaCanvasSettings( canvassRAAAll,  0.09, 0.02, 0.015, 0.09);
 	canvassRAAAll->SetLogy();
	
	TH2F * histo2DRAA;
	histo2DRAA = new TH2F("histo2DRAA","histo2DRAA",220,0.0,15.,200,0.0,4.2);
	SetStyleHistoTH2ForGraphs(histo2DRAA, "p_{T} (GeV/c)","R_{AA}", 0.04,0.045, 0.04,0.045, 0.93,0.96, 512, 510);
	histo2DRAA->GetXaxis()->SetNoExponent();
// 	histo2DRAA->GetYaxis()->SetMoreLogLabels();
	histo2DRAA->DrawCopy(); 
	histo2DRAA->GetYaxis()->SetRangeUser(0.06,4.2);
	
	TGraphErrors* Norm = new TGraphErrors(1);
	Norm->SetPoint(0, 0.3, 1.);
	Norm->SetPointError(0, 0.1, 0.1);
	Norm->SetMarkerStyle(0);
	Norm->SetFillColor(kGray+1);
	
	histo2DRAA->Draw();
	TGraphAsymmErrors *graphRAASyst0020FixX = (TGraphAsymmErrors*)graphRAASyst0020->Clone();
	ProduceGraphAsymmFixedXErrors(graphRAASyst0020FixX, 0.2);
	DrawGammaSetMarkerTGraphAsym(graphRAASyst0020FixX, 20, 2., color_0020, color_0020_sys);
	graphRAASyst0020FixX->SetFillStyle(0);
	graphRAASyst0020FixX->Draw("e2 p same");
	Norm->Draw("same e2");
	DrawGammaSetMarker(histoRAA0020, 20, 2., color_0020, color_0020);
 	histoRAA0020->Draw("e1 same");
	
		Xiao_Raa_0020->SetFillStyle(0); //3385
		cout << "here" << endl;
		Xiao_Raa_0020->SetLineWidth(2);
		Xiao_Raa_0020->SetLineWidth(colorXiao0020);
		
		Vitev_Bas_Raa_0020->SetFillStyle(3344);//3345
		cout << "here" << endl;
		Vitev_Bas_Raa_0020->SetLineWidth(2);
		Vitev_Bas_Raa_0020->SetLineWidth(colorVitevBas0020);
		Vitev_ShlSel_Raa_0020->SetFillStyle(3454);//
		cout << "here" << endl;
		gWHDG_Raa_0020->SetFillStyle(3345);//3451
	cout << "here" << endl;
	DrawGammaSetMarkerTGraphErr(Xiao_Raa_0020, markerStyleCommmonSpectrum0020,markerSizeSpectrum, colorXiao0020 ,colorXiao0020);
	Xiao_Raa_0020->SetFillColor(colorXiao0020);
	Xiao_Raa_0020->Draw("3 same");
	cout << "here" << endl;
	DrawGammaSetMarkerTGraphErr(Vitev_Bas_Raa_0020, markerStyleCommmonSpectrum0020,markerSizeSpectrum, colorVitevBas0020 ,colorVitevBas0020);
	Vitev_Bas_Raa_0020->SetFillColor(colorVitevBas0020);
	Vitev_Bas_Raa_0020->Draw("3 same");
	cout << "here" << endl;
	DrawGammaSetMarkerTGraphErr(Vitev_ShlSel_Raa_0020, markerStyleCommmonSpectrum0020,markerSizeSpectrum, colorVitevShlSel0020, colorVitevShlSel0020,0.8);
	Vitev_ShlSel_Raa_0020->SetFillColor(colorVitevShlSel0020);
	Vitev_ShlSel_Raa_0020->Draw("3 same");
	cout << "here" << endl;
	DrawGammaSetMarkerTGraphAsym(gWHDG_Raa_0020, markerStyleCommmonSpectrum0020,markerSizeSpectrum, colorWHDG0020, colorWHDG0020,0.8);
	gWHDG_Raa_0020->SetFillColor(colorWHDG0020);
	gWHDG_Raa_0020->Draw("3 same");

// 	TLatex *labelRAAPi0TheoryPbPb0020 = new TLatex(0.15,0.9,collisionSystemCent.Data());
// 	SetStyleTLatex( labelRAAPi0TheoryPbPb0020, 0.05,4);
// 	labelRAAPi0TheoryPbPb0020->Draw();
// 	TLatex *labelRAAPi0TheoryLabelPbPb0020 = new TLatex(0.15,0.83,"#pi^{0} #rightarrow #gamma #gamma #rightarrow e^{+}e^{-} e^{+}e^{-}");
// 	SetStyleTLatex( labelRAAPi0TheoryLabelPbPb0020, 0.04,4);
// 	labelRAAPi0TheoryLabelPbPb0020->Draw();
// 	histo2DRAAAll3->Draw("axis,same");
	TGraphErrors* Xiao_Raa_0020_Legend = (TGraphErrors*)Xiao_Raa_0020->Clone();
	TGraphErrors* Vitev_Bas_Raa_0020_Legend = (TGraphErrors*)Vitev_Bas_Raa_0020->Clone();
	TGraphErrors* Vitev_ShlSel_Raa_0020_Legend = (TGraphErrors*)Vitev_ShlSel_Raa_0020->Clone();
	TGraphAsymmErrors* gWHDG_Raa_0020_Legend = (TGraphAsymmErrors*)gWHDG_Raa_0020->Clone();
	
	Xiao_Raa_0020_Legend->SetFillStyle(0); //3385
	cout << "here" << endl;
	Xiao_Raa_0020_Legend->SetLineWidth(2);
	Xiao_Raa_0020_Legend->SetLineWidth(kBlack);
	
	Vitev_Bas_Raa_0020_Legend->SetFillStyle(3344);//3345
	cout << "here" << endl;
	Vitev_Bas_Raa_0020_Legend->SetLineWidth(2);
	Vitev_Bas_Raa_0020_Legend->SetLineWidth(kBlack);
	Vitev_ShlSel_Raa_0020_Legend->SetFillStyle(3454);//
	cout << "here" << endl;
	gWHDG_Raa_0020_Legend->SetFillStyle(3345);//3451
	cout << "here" << endl;
	DrawGammaSetMarkerTGraphErr(Xiao_Raa_0020_Legend, markerStyleCommmonSpectrum0020,markerSizeSpectrum, kBlack ,kBlack);
	Xiao_Raa_0020_Legend->SetFillColor(kBlack);
	DrawGammaSetMarkerTGraphErr(Vitev_Bas_Raa_0020_Legend, markerStyleCommmonSpectrum0020,markerSizeSpectrum, kBlack ,kBlack);
	Vitev_Bas_Raa_0020_Legend->SetFillColor(kBlack);
	DrawGammaSetMarkerTGraphErr(Vitev_ShlSel_Raa_0020_Legend, markerStyleCommmonSpectrum0020,markerSizeSpectrum, kBlack, kBlack,0.8);
	Vitev_ShlSel_Raa_0020_Legend->SetFillColor(kBlack);
	DrawGammaSetMarkerTGraphAsym(gWHDG_Raa_0020_Legend, markerStyleCommmonSpectrum0020,markerSizeSpectrum, kBlack, kBlack,0.8);
	gWHDG_Raa_0020_Legend->SetFillColor(kBlack);

	TGraphAsymmErrors *graphRAASyst6080FixX = (TGraphAsymmErrors*)graphRAASyst6080->Clone();
	ProduceGraphAsymmFixedXErrors(graphRAASyst6080FixX, 0.2);
	DrawGammaSetMarkerTGraphAsym(graphRAASyst6080FixX, 20, 2., color_6080, color_6080_sys);
	graphRAASyst6080FixX->SetFillStyle(0);
	graphRAASyst6080FixX->Draw("e2 p same");
	DrawGammaSetMarker(histoRAA6080, 20, 2., color_6080, color_6080);

	Xiao_Raa_6080->SetFillStyle(0); //3385
	Xiao_Raa_6080->SetLineWidth(2);
	Xiao_Raa_6080->SetLineWidth(colorXiao6080);
	gWHDG_Raa_6080->SetFillStyle(3345);//3451
	DrawGammaSetMarkerTGraphErr(Xiao_Raa_6080, markerStyleCommmonSpectrum6080,markerSizeSpectrum, colorXiao6080 ,colorXiao6080);
	Xiao_Raa_6080->SetFillColor(colorXiao6080);
	Xiao_Raa_6080->Draw("3 same");	
	DrawGammaSetMarkerTGraphAsym(gWHDG_Raa_6080, markerStyleCommmonSpectrum6080,markerSizeSpectrum, colorWHDG6080, colorWHDG6080,0.8);
	gWHDG_Raa_6080->SetFillColor(colorWHDG6080);
	gWHDG_Raa_6080->Draw("3 same");

 	TLegend* legendRAAPi0TheoryPbPb0020 = new TLegend(0.15,0.79,0.55,0.95);
	legendRAAPi0TheoryPbPb0020->SetFillColor(0);
	legendRAAPi0TheoryPbPb0020->SetLineColor(0);
	legendRAAPi0TheoryPbPb0020->SetNColumns(2);
	legendRAAPi0TheoryPbPb0020->SetTextSize(0.025);
	legendRAAPi0TheoryPbPb0020->AddEntry(graphRAASyst0020FixX,"#pi^{0} 0-20%","pf");
	legendRAAPi0TheoryPbPb0020->AddEntry(graphRAASyst6080FixX,"#pi^{0} 60-80%","pf");
	legendRAAPi0TheoryPbPb0020->AddEntry(Xiao_Raa_0020_Legend,"Chen (HT)","f");
	legendRAAPi0TheoryPbPb0020->AddEntry(Vitev_Bas_Raa_0020_Legend,"Vitev FS E-loss","f");
	legendRAAPi0TheoryPbPb0020->AddEntry(gWHDG_Raa_0020_Legend,"WHDG","f");
	legendRAAPi0TheoryPbPb0020->AddEntry(Vitev_ShlSel_Raa_0020_Legend,"Vitev IS & FS E-loss","f");
		
	legendRAAPi0TheoryPbPb0020->Draw();
	histoRAA6080->Draw("e1 same");
	
	histo2DRAA->Draw("same,axis");
	
	DrawAliceLogoPi0PreliminaryPbPb(pictDrawingCoordinates[0], pictDrawingCoordinates[1], pictDrawingCoordinates[2], pictDrawingCoordinates[3], pictDrawingCoordinates[4], pictDrawingCoordinates[5], pictDrawingCoordinates[6], pictDrawingCoordinates[7], pictDrawingCoordinates[8],collisionSystem, pictDrawingOptions[1], pictDrawingOptions[2], pictDrawingOptions[3],1420,1320);
	
// 	DrawGammaLines(0., 10.0 , 1, 1 ,1,kGray);
	
	canvassRAAAll->Update();
	canvassRAAAll->SaveAs(Form("RAA_2_Theory.eps"));
	
	//********************************************************************************************************************************************
	//************************************************************ all Pb-Pb Raa *****************************************************************
	TCanvas* canvasRAADataDiffEnergies = new TCanvas("canvasRAADataDiffEnergies","",200,10,1420,1320);  // gives the page size
	DrawGammaCanvasSettings( canvasRAADataDiffEnergies,  0.09, 0.02, 0.015, 0.09);
//  	histo2DRAA->GetXaxis()->SetRangeUser();
	histo2DRAA->GetYaxis()->SetRangeUser(0.0,1.45);
	histo2DRAA->DrawCopy(); 

	
	histo2DRAA->Draw();
	graphRAASyst0020FixX->Draw("e2 p same");
	histoRAA0020->Draw("e1 same");
	
	DrawGammaSetMarkerTGraphErr(graphPHENIX200GeVRAA_0020, markerStylePHENIX200GeV,markerSizePHENIX200GeV, kBlack , kBlack);
	graphPHENIX200GeVRAA_0020->Draw("p,same,e1");	
	DrawGammaSetMarkerTGraphErr(graphPHENIX62GeVRAA_0020, markerStylePHENIX62GeV,markerSizePHENIX62GeV, kGray+1, kGray+1);
	graphPHENIX62GeVRAA_0020->Draw("p,same,e1");	
	DrawGammaSetMarkerTGraphErr(graphPHENIX39GeVRAA_0020, markerStylePHENIX39GeV,markerSizePHENIX39GeV, kBlack , kBlack);
	graphPHENIX39GeVRAA_0020->Draw("p,same,e1");	
	
	DrawGammaSetMarkerTGraphErr(graphWA98_17_3GeVRAA_0013, markerStyleWA98,markerSizeWA98, kGray+2 , kGray+2);
	graphWA98_17_3GeVRAA_0013->Draw("p,same,e1");	
	
// 	DrawGammaLines(0., 20. , 1, 1 ,1,kGray);

	TLegend* legendRAAPi0DatExtPbPb0020 = new TLegend(0.48,0.55,0.8,0.75);
	legendRAAPi0DatExtPbPb0020->SetFillColor(0);
	legendRAAPi0DatExtPbPb0020->SetLineColor(0);
	legendRAAPi0DatExtPbPb0020->SetTextSize(0.025);
	legendRAAPi0DatExtPbPb0020->AddEntry(graphRAASyst0020FixX,"ALICE","pf");
	legendRAAPi0DatExtPbPb0020->AddEntry(graphPHENIX200GeVRAA_0020,"PHENIX","p");
	legendRAAPi0DatExtPbPb0020->AddEntry(graphPHENIX62GeVRAA_0020,"PHENIX","p");
	legendRAAPi0DatExtPbPb0020->AddEntry(graphPHENIX39GeVRAA_0020,"PHENIX","p");
	legendRAAPi0DatExtPbPb0020->AddEntry(graphWA98_17_3GeVRAA_0013,"WA98","p");
	legendRAAPi0DatExtPbPb0020->Draw();
// 
	TLatex *labelExtPbPb0020_1 = new TLatex(0.65,0.722,"0-20% Pb-Pb  #sqrt{#it{s}_{_{NN}}} = 2.76 TeV");
	TLatex *labelExtPbPb0020_2 = new TLatex(0.65,0.681,"0-20% Au-Au  #sqrt{#it{s}_{_{NN}}} = 200 GeV");
	TLatex *labelExtPbPb0020_3 = new TLatex(0.65,0.641,"0-20% Au-Au  #sqrt{#it{s}_{_{NN}}} = 62.4 GeV");
	TLatex *labelExtPbPb0020_4 = new TLatex(0.65,0.601,"0-20% Au-Au  #sqrt{#it{s}_{_{NN}}} = 39 GeV");
	TLatex *labelExtPbPb0020_5 = new TLatex(0.65,0.5615,"0-13% Pb-Pb  #sqrt{#it{s}_{_{NN}}} = 17.3 GeV");
// 
	SetStyleTLatex( labelExtPbPb0020_1, 0.025,4);
	SetStyleTLatex( labelExtPbPb0020_2, 0.025,4);
	SetStyleTLatex( labelExtPbPb0020_3, 0.025,4);
	SetStyleTLatex( labelExtPbPb0020_4, 0.025,4);
	SetStyleTLatex( labelExtPbPb0020_5, 0.025,4);
// 					
	labelExtPbPb0020_1->Draw();
	labelExtPbPb0020_2->Draw();
	labelExtPbPb0020_3->Draw();
	labelExtPbPb0020_4->Draw();
	labelExtPbPb0020_5->Draw();
	
 	Norm->Draw("same e2");
	
// 	graphRAASyst6080FixX->Draw("e2 p same");
// 	histoRAA6080->Draw("e1 same");
	
	histo2DRAA->Draw("same,axis");
	
	DrawAliceLogoPi0PreliminaryPbPb(pictDrawingCoordinates0020[0], pictDrawingCoordinates0020[1], pictDrawingCoordinates0020[2], pictDrawingCoordinates0020[3], pictDrawingCoordinates0020[4], pictDrawingCoordinates0020[5], pictDrawingCoordinates0020[6], pictDrawingCoordinates0020[7], pictDrawingCoordinates0020[8],collisionSystem, pictDrawingOptions[1], pictDrawingOptions[2], pictDrawingOptions[3],1420,1320);
	
// 	DrawGammaLines(0., 10.0 , 1, 1 ,1,kGray);
	
	canvasRAADataDiffEnergies->Update();
	canvasRAADataDiffEnergies->SaveAs(Form("RAA_2_RHIC_0020.eps"));


		//********************************************************************************************************************************************
	//************************************************************ all Pb-Pb Raa *****************************************************************
	TCanvas* canvasRAADataDiffEnergies6080 = new TCanvas("canvasRAADataDiffEnergies6080","",200,10,1420,1320);  // gives the page size
	DrawGammaCanvasSettings( canvasRAADataDiffEnergies6080,  0.09, 0.02, 0.015, 0.09);
 	histo2DRAA->GetYaxis()->SetRangeUser(0.0,1.75);
	histo2DRAA->DrawCopy(); 

	
	histo2DRAA->Draw();
	graphRAASyst6080FixX->Draw("e2 p same");
	histoRAA6080->Draw("e1 same");
	
	DrawGammaSetMarkerTGraphErr(graphPHENIX200GeVRAA_6080, markerStylePHENIX200GeV,markerSizePHENIX200GeV, kBlack , kBlack);
	graphPHENIX200GeVRAA_6080->Draw("p,same,e1");	
	DrawGammaSetMarkerTGraphErr(graphPHENIX62GeVRAA_6080, markerStylePHENIX62GeV,markerSizePHENIX62GeV, kGray+1, kGray+1);
	graphPHENIX62GeVRAA_6080->Draw("p,same,e1");	
	DrawGammaSetMarkerTGraphErr(graphPHENIX39GeVRAA_6080, markerStylePHENIX39GeV,markerSizePHENIX39GeV, kBlack , kBlack);
	graphPHENIX39GeVRAA_6080->Draw("p,same,e1");	
	
	TLegend* legendRAAPi0DatExtPbPb6080 = new TLegend(0.48,0.78,0.8,0.95);
	legendRAAPi0DatExtPbPb6080->SetFillColor(0);
	legendRAAPi0DatExtPbPb6080->SetLineColor(0);
	legendRAAPi0DatExtPbPb6080->SetTextSize(0.025);
	legendRAAPi0DatExtPbPb6080->AddEntry(graphRAASyst6080FixX,"ALICE","pf");
	legendRAAPi0DatExtPbPb6080->AddEntry(graphPHENIX200GeVRAA_6080,"PHENIX","p");
	legendRAAPi0DatExtPbPb6080->AddEntry(graphPHENIX62GeVRAA_6080,"PHENIX","p");
	legendRAAPi0DatExtPbPb6080->AddEntry(graphPHENIX39GeVRAA_6080,"PHENIX","p");
	legendRAAPi0DatExtPbPb6080->Draw();
// 
	TLatex *labelExtPbPb6080_1 = new TLatex(0.65,0.92,"60-80% Pb-Pb  #sqrt{#it{s}_{_{NN}}} = 2.76 TeV");
	TLatex *labelExtPbPb6080_2 = new TLatex(0.65,0.877,"60-80% Au-Au  #sqrt{#it{s}_{_{NN}}} = 200 GeV");
	TLatex *labelExtPbPb6080_3 = new TLatex(0.65,0.835,"60-86% Au-Au  #sqrt{#it{s}_{_{NN}}} = 62.4 GeV");
	TLatex *labelExtPbPb6080_4 = new TLatex(0.65,0.792,"60-86% Au-Au  #sqrt{#it{s}_{_{NN}}} = 39 GeV");
	
	SetStyleTLatex( labelExtPbPb6080_1, 0.025,4);
	SetStyleTLatex( labelExtPbPb6080_2, 0.025,4);
	SetStyleTLatex( labelExtPbPb6080_3, 0.025,4);
	SetStyleTLatex( labelExtPbPb6080_4, 0.025,4);
	
	labelExtPbPb6080_1->Draw();
	labelExtPbPb6080_2->Draw();
	labelExtPbPb6080_3->Draw();
	labelExtPbPb6080_4->Draw();
	
 	Norm->Draw("same e2");
	
// 	graphRAASyst6080FixX->Draw("e2 p same");
// 	histoRAA6080->Draw("e1 same");
	
	histo2DRAA->Draw("same,axis");
	
	DrawAliceLogoPi0PreliminaryPbPb(pictDrawingCoordinates6080[0], pictDrawingCoordinates6080[1], pictDrawingCoordinates6080[2], pictDrawingCoordinates6080[3], pictDrawingCoordinates6080[4], pictDrawingCoordinates6080[5], pictDrawingCoordinates6080[6], pictDrawingCoordinates6080[7], pictDrawingCoordinates6080[8],collisionSystem, pictDrawingOptions[1], pictDrawingOptions[2], pictDrawingOptions[3],1420,1320);
	
// 	DrawGammaLines(0., 10.0 , 1, 1 ,1,kGray);
	
	canvasRAADataDiffEnergies6080->Update();
	canvasRAADataDiffEnergies6080->SaveAs(Form("RAA_2_RHIC_6080.eps"));


	TCanvas* canvasRAAChargePion = new TCanvas("canvasRAAChargePion","",200,10,1420,1320);  // gives the page size
	DrawGammaCanvasSettings( canvasRAAChargePion,  0.09, 0.02, 0.015, 0.09);
	canvasRAAChargePion->SetLogy();
	histo2DRAA->GetYaxis()->SetRangeUser(0.09,1.5);
	
	TGraphErrors* Norm = new TGraphErrors(1);
	Norm->SetPoint(0, 0.3, 1.);
	Norm->SetPointError(0, 0.1, 0.1);
	Norm->SetMarkerStyle(0);
	Norm->SetFillColor(kGray+1);
	
	histo2DRAA->Draw();
	DrawGammaSetMarkerTGraphAsym(graphRAASyst0020FixX, 20, 2., color_0020, color_0020_sys);
	graphRAASyst0020FixX->SetFillStyle(0);
	graphRAASyst0020FixX->Draw("e2 p same");
	Norm->Draw("same e2");
	DrawGammaSetMarker(histoRAA0020, 20, 2., color_0020, color_0020);
 	histoRAA0020->Draw("e1 same");
	DrawGammaSetMarker(hRAA_Pion_syst_0_20, 21, 2., color_0020, color_0020_sys);
 	hRAA_Pion_syst_0_20->Draw("e2 p same");
	DrawGammaSetMarker(hRAA_Pion_stat_0_20, 21, 2., color_0020, color_0020);
 	hRAA_Pion_stat_0_20->Draw("e1 same");

// 	TGraphAsymmErrors *graphRAASyst2040FixX = (TGraphAsymmErrors*)graphRAASyst2040->Clone();
// 	ProduceGraphAsymmFixedXErrors(graphRAASyst2040FixX, 0.2);
// 	DrawGammaSetMarkerTGraphAsym(graphRAASyst2040FixX, 20, 2., color_2040, color_2040_sys);
// 	graphRAASyst2040FixX->SetFillStyle(0);
// 	graphRAASyst2040FixX->Draw("e2 p same");
// 	Norm->Draw("same e2");
// 	DrawGammaSetMarker(histoRAA2040, 20, 2., color_2040, color_2040);
//  	histoRAA2040->Draw("e1 same");

	TGraphAsymmErrors *graphRAASyst4060FixX = (TGraphAsymmErrors*)graphRAASyst4060->Clone();
	ProduceGraphAsymmFixedXErrors(graphRAASyst4060FixX, 0.2);
	DrawGammaSetMarkerTGraphAsym(graphRAASyst4060FixX, 20, 2., color_4060, color_4060_sys);
	graphRAASyst4060FixX->SetFillStyle(0);
	graphRAASyst4060FixX->Draw("e2 p same");
	Norm->Draw("same e2");
	DrawGammaSetMarker(histoRAA4060, 20, 2., color_4060, color_4060);
 	histoRAA4060->Draw("e1 same");
	DrawGammaSetMarker(hRAA_Pion_syst_40_60, 21, 2., color_4060, color_4060_sys);
 	hRAA_Pion_syst_40_60->Draw("e2 p same");
	DrawGammaSetMarker(hRAA_Pion_stat_40_60, 21, 2., color_4060, color_4060);
 	hRAA_Pion_stat_40_60->Draw("e1 same");
	
// 	DrawGammaSetMarkerTGraphAsym(graphRAASyst6080FixX, 20, 2., color_6080, color_6080_sys);
// 	graphRAASyst6080FixX->SetFillStyle(0);
// 	graphRAASyst6080FixX->Draw("e2 p same");
// 	DrawGammaSetMarker(histoRAA6080, 20, 2., color_6080, color_6080);
// 	histoRAA6080->Draw("e1 same");
	
 	TLegend* legendRAAPi0ChargedPions = new TLegend(0.15,0.79,0.75,0.95);
	legendRAAPi0ChargedPions->SetFillColor(0);
	legendRAAPi0ChargedPions->SetLineColor(0);
	legendRAAPi0ChargedPions->SetNColumns(2);
	legendRAAPi0ChargedPions->SetTextSize(0.025);
	legendRAAPi0ChargedPions->AddEntry(graphRAASyst0020FixX,"#pi^{0} prelim 2011","pf");
	legendRAAPi0ChargedPions->AddEntry(hRAA_Pion_syst_0_20,"#pi^{#pm} prelim 2012 0-20%","pf");
	legendRAAPi0ChargedPions->AddEntry(graphRAASyst4060FixX,"#pi^{0} prelim 2011","pf");
	legendRAAPi0ChargedPions->AddEntry(hRAA_Pion_syst_40_60,"#pi^{#pm} prelim 2012 40-60%","pf");
	legendRAAPi0ChargedPions->Draw();

	
	histo2DRAA->Draw("same,axis");
	
// 	DrawAliceLogoPi0PreliminaryPbPb(pictDrawingCoordinates[0], pictDrawingCoordinates[1], pictDrawingCoordinates[2], pictDrawingCoordinates[3], pictDrawingCoordinates[4], pictDrawingCoordinates[5], pictDrawingCoordinates[6], pictDrawingCoordinates[7], pictDrawingCoordinates[8],collisionSystem, pictDrawingOptions[1], pictDrawingOptions[2], pictDrawingOptions[3],1420,1320);
	
// 	DrawGammaLines(0., 10.0 , 1, 1 ,1,kGray);
	
	canvasRAAChargePion->Update();
	canvasRAAChargePion->SaveAs(Form("RAA_2_0020_4060_ChargedPions.eps"));

	TCanvas* canvasRAAChargePion2 = new TCanvas("canvasRAAChargePion2","",200,10,1420,1320);  // gives the page size
	DrawGammaCanvasSettings( canvasRAAChargePion2,  0.09, 0.02, 0.015, 0.09);
	canvasRAAChargePion2->SetLogy();
	histo2DRAA->GetYaxis()->SetRangeUser(0.09,4.1);
	
	TGraphErrors* Norm = new TGraphErrors(1);
	Norm->SetPoint(0, 0.3, 1.);
	Norm->SetPointError(0, 0.1, 0.1);
	Norm->SetMarkerStyle(0);
	Norm->SetFillColor(kGray+1);
	
	histo2DRAA->Draw();
	
	TGraphAsymmErrors *graphRAASyst2040FixX = (TGraphAsymmErrors*)graphRAASyst2040->Clone();
	ProduceGraphAsymmFixedXErrors(graphRAASyst2040FixX, 0.2);
	DrawGammaSetMarkerTGraphAsym(graphRAASyst2040FixX, 20, 2., color_2040, color_2040_sys);
	graphRAASyst2040FixX->SetFillStyle(0);
	graphRAASyst2040FixX->Draw("e2 p same");
	Norm->Draw("same e2");
	DrawGammaSetMarker(histoRAA2040, 20, 2., color_2040, color_2040);
 	histoRAA2040->Draw("e1 same");
	
	DrawGammaSetMarker(hRAA_Pion_syst_20_40, 21, 2., color_2040, color_2040_sys);
 	hRAA_Pion_syst_20_40->Draw("e2 p same");
	DrawGammaSetMarker(hRAA_Pion_stat_20_40, 21, 2., color_2040, color_2040);
 	hRAA_Pion_stat_20_40->Draw("e1 same");
	
	DrawGammaSetMarkerTGraphAsym(graphRAASyst6080FixX, 20, 2., color_6080, color_6080_sys);
	graphRAASyst6080FixX->SetFillStyle(0);
	graphRAASyst6080FixX->Draw("e2 p same");
	DrawGammaSetMarker(histoRAA6080, 20, 2., color_6080, color_6080);
	histoRAA6080->Draw("e1 same");
	DrawGammaSetMarker(hRAA_Pion_syst_60_80, 21, 2., color_6080, color_6080_sys);
 	hRAA_Pion_syst_60_80->Draw("e2 p same");
	DrawGammaSetMarker(hRAA_Pion_stat_60_80, 21, 2., color_6080, color_6080);
 	hRAA_Pion_stat_60_80->Draw("e1 same");
	
 	TLegend* legendRAAPi0ChargedPions = new TLegend(0.15,0.79,0.75,0.95);
	legendRAAPi0ChargedPions->SetFillColor(0);
	legendRAAPi0ChargedPions->SetLineColor(0);
	legendRAAPi0ChargedPions->SetNColumns(2);
	legendRAAPi0ChargedPions->SetTextSize(0.025);
	legendRAAPi0ChargedPions->AddEntry(graphRAASyst2040FixX,"#pi^{0} prelim 2011","pf");
	legendRAAPi0ChargedPions->AddEntry(hRAA_Pion_syst_20_40,"#pi^{#pm} prelim 2012 20-40%","pf");
	legendRAAPi0ChargedPions->AddEntry(graphRAASyst6080FixX,"#pi^{0} prelim 2011","pf");
	legendRAAPi0ChargedPions->AddEntry(hRAA_Pion_syst_60_80,"#pi^{#pm} prelim 2012 60-80%","pf");
	legendRAAPi0ChargedPions->Draw();

	
	histo2DRAA->Draw("same,axis");
	
// 	DrawAliceLogoPi0PreliminaryPbPb(pictDrawingCoordinates[0], pictDrawingCoordinates[1], pictDrawingCoordinates[2], pictDrawingCoordinates[3], pictDrawingCoordinates[4], pictDrawingCoordinates[5], pictDrawingCoordinates[6], pictDrawingCoordinates[7], pictDrawingCoordinates[8],collisionSystem, pictDrawingOptions[1], pictDrawingOptions[2], pictDrawingOptions[3],1420,1320);
	
// 	DrawGammaLines(0., 10.0 , 1, 1 ,1,kGray);
	
	canvasRAAChargePion2->Update();
	canvasRAAChargePion2->SaveAs(Form("RAA_2_2040_6080_ChargedPions.eps"));

	
}
