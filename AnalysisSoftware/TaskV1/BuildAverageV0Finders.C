//***********************************************************************************************
//**************************** CutStudiesOverview ***********************************************
//***********************************************************************************************
/***************************************************************************************************
 ******     provided by Gamma Conversion Group, PWG4,                                     *****
 ******        Ana Marin, marin@physi.uni-heidelberg.de                                *****
 ******           Kathrin Koch, kkoch@physi.uni-heidelberg.de                                 *****
 ******        Friederike Bock, friederike.bock@cern.ch                                *****
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
#include "../CommonHeaders/PlottingGammaConversionHistos.h"
#include "../CommonHeaders/PlottingGammaConversionAdditional.h"
#include "../CommonHeaders/FittingGammaConversion.h"
#include "../CommonHeaders/ConversionFunctionsBasicsAndLabeling.h"
#include "../CommonHeaders/ConversionFunctions.h"

void BuildAverageV0Finders(     TString ComparisonFile, 
                                TString cutSelection, 
                                TString suffix = "gif", 
                                TString meson = "", 
                                TString isMC = "", 
                                TString optionEnergy="", 
                                TString centralitySelec = "0005"
                          ){

    StyleSettingsThesis();
    SetPlotStyle();

    Bool_t pictDrawingOptions[4]            = {kFALSE, kFALSE, kFALSE, kTRUE};
        
    TString outputDir                       =  Form("CutStudies/%s/AverageV0Finders",optionEnergy.Data());
    gSystem->Exec("mkdir -p "+outputDir);

    TString textMeson;
    if (meson.CompareTo("Pi0")==0 || meson.CompareTo("Pi0EtaBinning")==0){
        textMeson = "#pi^{0}";
        pictDrawingOptions[3]               = kTRUE;
    } else {
        pictDrawingOptions[3]               = kFALSE;
        textMeson = "#eta";
    }
    if (isMC.CompareTo("kTRUE") ==0){
        pictDrawingOptions[1]               = kTRUE;
    } else {
        pictDrawingOptions[1]               = kFALSE;
    }

    Float_t pictDrawingCoordinates[9]       = {0.55, 0.8, 0.25, 0.04, 0.7,0.5, 0.18, 0.035,0};
    Float_t pictDrawingCoordinatesSB[9]     = {0.6, 0.80, 0.35, 0.04, 0.15, 0.68, 0.18, 0.035,0};
    Float_t pictDrawingCoordinatesSign[9]   = {0.6, 0.80, 0.35, 0.04, 0.7, 0.51, 0.18, 0.035,0};
    Float_t pictDrawingCoordinatesEff[9]    = {0.55, 0.8, 0.18, 0.04, 0.3, 0.2, 0.18, 0.035,0};
    Float_t pictDrawingCoordinatesAcc[9]    = {0.63, 0.2, 0.40, 0.04, 0.7,0.33, 0.18, 0.035,0};
    Float_t pictDrawingCoordinatesInv[9]    = {0.63, 0.8, 0.40, 0.04, 0.7, 0.5, 0.18, 0.035,0};
    Float_t pictDrawingCoordinatesMass[9]   = {0.4, 0.8, 0.75, 0.04, 0.2,0.7, 0.18, 0.035,0};
    Float_t pictDrawingCoordinatesFWHM[9]   = {0.4, 0.8, 0.75, 0.04, 0.2,0.68, 0.18, 0.035,0};
    Float_t pictDrawingCoordinatesNLO[9]    = {0.55, 0.8, 0.25, 0.04, 0.7,0.5, 0.18, 0.035,0};

    TString collisionSystem;
    if(optionEnergy.CompareTo("7TeV") == 0){
        collisionSystem                     = "pp @ 7TeV";
    } else if( optionEnergy.CompareTo("2.76TeV") == 0) {
        collisionSystem                     = "pp @ 2.76 TeV";
    } else if( optionEnergy.CompareTo("900GeV") == 0) {
        collisionSystem                     = "pp @ 900GeV";
    } else if( optionEnergy.CompareTo("HI") == 0) {
        collisionSystem                     = "PbPb @ 2.76TeV";
    } else {
        cout << "No correct collision system specification, has been given" << endl;
        return;
    }

    
    TFile *InputFileComparisonOffline       = new TFile(ComparisonFile.Data());
    TF1*  fitRatioCorrectedYieldCut         = (TF1*)InputFileComparisonOffline->Get( Form("%s_fitRatioCorrectedYieldCutV0Offline%s_data", meson.Data(), centralitySelec.Data()));
    TF1*  fitRatioConstCorrectedYieldCut    = (TF1*)InputFileComparisonOffline->Get( Form("%s_fitRatioConstCorrectedYieldCutV0Offline%s_data", meson.Data(), centralitySelec.Data()));
    TH1D* histoCorrectedYieldOfflineUnMod   = (TH1D*)InputFileComparisonOffline->Get( Form("%s_histoCorrectedYield_V0Offline%s_data", meson.Data(), centralitySelec.Data()));
    TH1D* histoCorrectedRatioOfflineUnMod   = (TH1D*)InputFileComparisonOffline->Get(Form("%s_histoRatioCorrectedYield_V0Offline%s_data", meson.Data(), centralitySelec.Data()));
    
    TString centralityString                = GetCentralityString(cutSelection.Data());
    
    cout << WriteParameterToFile(fitRatioCorrectedYieldCut)<< endl;
    cout << WriteParameterToFile(fitRatioConstCorrectedYieldCut)<< endl;
    
    Float_t constant                        = fitRatioConstCorrectedYieldCut->GetParameter(0);
    Float_t constantErr                     = fitRatioConstCorrectedYieldCut->GetParError(0);

    TFile *InputFileOnfly                   = new TFile(Form("%s/HI/Pi0_data_GammaConvV1Correction_%s.root ", cutSelection.Data(), cutSelection.Data()));
    TH1D *histoCorrectedYieldOnfly          = (TH1D*)InputFileOnfly->Get("CorrectedYieldTrueEffFitted");
    TH1D *histoCorrectedYieldOffline        = (TH1D*)histoCorrectedYieldOnfly->Clone("CorrectedYieldOffline");
        
    for (Int_t i = 1; i < histoCorrectedYieldOnfly->GetNbinsX()+1;i++){
        histoCorrectedYieldOffline->SetBinContent(i, histoCorrectedYieldOffline->GetBinContent(i)*constant);
        Double_t relativeErrorOfffline      = histoCorrectedYieldOfflineUnMod->GetBinError(i)/histoCorrectedYieldOfflineUnMod->GetBinContent(i);
        cout << "rel Error: " << i << "\t" << relativeErrorOfffline << endl;
        if (histoCorrectedYieldOfflineUnMod->GetBinContent(i) <= 0){
            histoCorrectedYieldOffline->SetBinError(i, 0. );
        } else {
            histoCorrectedYieldOffline->SetBinError(i, histoCorrectedYieldOffline->GetBinContent(i) * relativeErrorOfffline );
        }
    }

    TH1D* histoWeigtedAverage               = CalculateWeightedAveragePCM( histoCorrectedYieldOnfly,    histoCorrectedYieldOffline);
    TH1D* histoRatioWeightedOnfly           = (TH1D*) histoWeigtedAverage->Clone("ratioWeightedOnfly");
    histoRatioWeightedOnfly->Divide(histoRatioWeightedOnfly,histoCorrectedYieldOnfly,1.,1.,"");
    TH1D* histoRatioOfflineOnfly            = (TH1D*) histoCorrectedYieldOffline->Clone("ratioWeightedOnfly");
    histoRatioOfflineOnfly->Divide(histoRatioOfflineOnfly,histoCorrectedYieldOnfly,1.,1.,"");
    
    TCanvas* canvasYield                    = new TCanvas("canvasYield","",200,10,1350,900);// gives the page size
    DrawGammaCanvasSettings( canvasYield, 0.13, 0.02, 0.02, 0.09);
    canvasYield->SetLogy(1);

    DrawAutoGammaMesonHistos( histoCorrectedYieldOnfly, 
                                "", "p_{T} (GeV/c)", "Corrected Yield", 
                                kTRUE, 3., 4e-10, kTRUE,
                                kFALSE, 0., 0.7, 
                                kFALSE, 0., 10.);

    DrawGammaSetMarker(histoCorrectedYieldOffline, 21, 0.5, kBlue, kBlue); 
    histoCorrectedYieldOffline->DrawCopy("e1,same"); 

    DrawGammaSetMarker(histoWeigtedAverage, 25, 0.5, kRed, kRed); 
    histoWeigtedAverage->DrawCopy("e1,same"); 
    
    canvasYield->SaveAs(Form("%s/%s_ComparisonModOfflineOnfly_%s.%s",outputDir.Data(),meson.Data(),centralitySelec.Data(),suffix.Data()));
    delete canvasYield;

    TCanvas* canvasRatio                    = new TCanvas("canvasRatio","",200,10,1350,900);// gives the page size
    DrawGammaCanvasSettings( canvasRatio, 0.09, 0.02, 0.02, 0.09);

    DrawGammaSetMarker(histoRatioWeightedOnfly, 25, 1., kRed, kRed); 
    DrawAutoGammaMesonHistos( histoRatioWeightedOnfly, 
                             "", "p_{T} (GeV/c)", "Ratio", 
                             kFALSE, 3., 4e-10, kTRUE,
                             kTRUE, 0., 2., 
                             kTRUE, 0., 7.9);
    DrawGammaLines(0., 12.,1., 1.,0.1,kBlack);
    DrawGammaLines(0., 12.,constant, constant,0.5,kBlue);

    TLatex *labelConstantFit                = new TLatex(0.62,0.38,"constant fit to offline/onfly ratio");
    SetStyleTLatex( labelConstantFit, 0.038,4, kBlue);
    labelConstantFit->Draw();

    DrawGammaSetMarker(histoCorrectedRatioOfflineUnMod, 21, 1., kBlue, kBlue); 
    histoCorrectedRatioOfflineUnMod->DrawCopy("e1,same"); 

    if (optionEnergy.CompareTo("HI")==0){
        TLatex *labelCentrality             = new TLatex(0.65,0.93,Form("%s Pb-Pb #sqrt{#it{s}_{_{NN}}} = 2.76 TeV"    ,centralityString.Data()    ));
        SetStyleTLatex( labelCentrality, 0.038,4);
        labelCentrality->Draw();
    }

    TLegend* legendRatio                    = new TLegend(0.3,0.85,0.6,0.95);
    legendRatio->SetTextSize(0.038);
    legendRatio->SetFillColor(0);
    legendRatio->SetLineColor(0);
    legendRatio->AddEntry(histoRatioWeightedOnfly,"weighted average/onfly");
    legendRatio->AddEntry(histoCorrectedRatioOfflineUnMod,"intial offline/onfly");
    legendRatio->Draw();

    canvasRatio->SaveAs(Form("%s/%s_Ratio_%s.%s",outputDir.Data(),meson.Data(),centralitySelec.Data(),suffix.Data()));
    delete canvasRatio;

    TFile *InputFileOnflyWrite              = new TFile(Form("%s/HI/Pi0_data_GammaConvV1Correction_%s.root ", cutSelection.Data(), cutSelection.Data()),"UPDATE");
    histoWeigtedAverage->Write("CorrectedYieldTrueEffFittedAverage",TObject::kOverwrite);

    InputFileOnflyWrite->Write();
    InputFileOnflyWrite->Close();

}