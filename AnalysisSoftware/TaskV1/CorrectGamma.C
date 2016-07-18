// provided by Gamma Conversion Group, $ALICE_ROOT/PWGGA/GammaConv ;https://twiki.cern.ch/twiki/bin/view/ALICE/PWG4GammaConversion
// ***************************************************************************************************************
// **************** this macro has been written by Martin Wilde & Friederike Bock as of 29th Oct 2015 ************
// **************** it will not be maintained any longer and is superceeded by CorrectGammaV2 ********************
// ***************************************************************************************************************

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
#include "../CommonHeaders/PlottingGammaConversionHistos.h"
#include "../CommonHeaders/PlottingGammaConversionAdditional.h"
#include "../CommonHeaders/FittingGammaConversion.h"
//#include "../CommonHeaders/ConversionFunctionsBasicsAndLabeling.h"
#include "../CommonHeaders/ConversionFunctions.h"
#include "TLatex.h"
#include "../CommonHeaders/ExtractSignalBinning.h"
#include "RooUnfold.h"
#include "RooUnfoldResponse.h"
#include "RooUnfoldBayes.h"
#include "RooUnfoldBinByBin.h"


// extern TRandom *gRandom;
// extern TBenchmark *gBenchmark;
// extern TSystem *gSystem;


void CorrectGammaDataBackground(TH1D* histoGammaCorr, TH1D* histoBackground, TH1D* histoConvProb, TH1D* histoRecoEff, Double_t deltaEta, Double_t scaling, Double_t nEvt){
    histoGammaCorr->Scale(1./nEvt);
    histoGammaCorr->Add(histoBackground,-1);
    histoGammaCorr->Divide(histoGammaCorr,histoConvProb,1.,1.,"");
    histoGammaCorr->Divide(histoGammaCorr,histoRecoEff,1.,1.,"");
    histoGammaCorr->Scale(1./deltaEta);
    histoGammaCorr->Scale(scaling);
    for (Int_t i = 1; i < histoGammaCorr->GetNbinsX()+1 ; i++){
        Double_t newBinContent = histoGammaCorr->GetBinContent(i)/histoGammaCorr->GetBinCenter(i);
        Double_t newBinError = histoGammaCorr->GetBinError(i)/histoGammaCorr->GetBinCenter(i);
        histoGammaCorr->SetBinContent(i,newBinContent);
        histoGammaCorr->SetBinError(i,newBinError);
    }
}

void CorrectGammaDataPurity(TH1D* histoGammaCorr, TH1D* histoPurity, TH1D* histoConvProb, TH1D* histoRecoEff, Double_t deltaEta, Double_t scaling, Double_t nEvt){
    histoGammaCorr->Multiply(histoGammaCorr,histoPurity,1.,1.,"");
    histoGammaCorr->Divide(histoGammaCorr,histoConvProb,1.,1.,"");
    histoGammaCorr->Divide(histoGammaCorr,histoRecoEff,1.,1.,"");
    histoGammaCorr->Scale(1./deltaEta);
    histoGammaCorr->Scale(scaling);
    histoGammaCorr->Scale(1./nEvt);
    for (Int_t i = 1; i < histoGammaCorr->GetNbinsX()+1 ; i++){
        Double_t newBinContent = histoGammaCorr->GetBinContent(i)/histoGammaCorr->GetBinCenter(i);
        Double_t newBinError = histoGammaCorr->GetBinError(i)/histoGammaCorr->GetBinCenter(i);
        histoGammaCorr->SetBinContent(i,newBinContent);
        histoGammaCorr->SetBinError(i,newBinError);
    }
}

void surCorrectGammaDataUnfold(TH1D* histoGammaCorr, TH1D* histoConvProb, TH1D* histoRecoEff, Double_t deltaEta, Double_t scaling, Double_t nEvt){
    histoGammaCorr->Divide(histoGammaCorr,histoConvProb,1.,1.,"");
    histoGammaCorr->Divide(histoGammaCorr,histoRecoEff,1.,1.,"");
    histoGammaCorr->Scale(1./deltaEta);
    histoGammaCorr->Scale(scaling);
    histoGammaCorr->Scale(1./nEvt);
    for (Int_t i = 1; i < histoGammaCorr->GetNbinsX()+1 ; i++){
        Double_t newBinContent = histoGammaCorr->GetBinContent(i)/histoGammaCorr->GetBinCenter(i);
        Double_t newBinError = histoGammaCorr->GetBinError(i)/histoGammaCorr->GetBinCenter(i);
        histoGammaCorr->SetBinContent(i,newBinContent);
        histoGammaCorr->SetBinError(i,newBinError);
    }
}


void CorrectGammaDataPurityMinusSec(TH1D* histoGammaCorr, TH1D *histoAllSec, TH1D *histoK0sSec, TH1D* histoPurity, TH1D* histoConvProb, TH1D* histoRecoEff, Double_t deltaEta, Double_t scaling, Double_t nEvt){
    histoGammaCorr->Scale(1./nEvt);
    histoGammaCorr->Add(histoAllSec,-1);
    histoGammaCorr->Add(histoK0sSec,-1);
    histoGammaCorr->Multiply(histoGammaCorr,histoPurity,1.,1.,"");
    histoGammaCorr->Divide(histoGammaCorr,histoConvProb,1.,1.,"");
    histoGammaCorr->Divide(histoGammaCorr,histoRecoEff,1.,1.,"");
    histoGammaCorr->Scale(1./deltaEta);
    histoGammaCorr->Scale(scaling);
    for (Int_t i = 1; i < histoGammaCorr->GetNbinsX()+1 ; i++){
        Double_t newBinContent = histoGammaCorr->GetBinContent(i)/histoGammaCorr->GetBinCenter(i);
        Double_t newBinError = histoGammaCorr->GetBinError(i)/histoGammaCorr->GetBinCenter(i);
        histoGammaCorr->SetBinContent(i,newBinContent);
        histoGammaCorr->SetBinError(i,newBinError);
    }
}


void CorrectGammaDataBackgroundMinusSec(TH1D* histoGammaCorr, TH1D *histoAllSec, TH1D *histoK0sSec, TH1D* histoBackground, TH1D* histoConvProb, TH1D* histoRecoEff, Double_t deltaEta, Double_t scaling, Double_t nEvt){
    histoGammaCorr->Scale(1./nEvt);
    histoGammaCorr->Add(histoBackground,-1);
    histoGammaCorr->Add(histoAllSec,-1);
    histoGammaCorr->Add(histoK0sSec,-1);
    histoGammaCorr->Divide(histoGammaCorr,histoConvProb,1.,1.,"");
    histoGammaCorr->Divide(histoGammaCorr,histoRecoEff,1.,1.,"");
    histoGammaCorr->Scale(1./deltaEta);
    histoGammaCorr->Scale(scaling);
    for (Int_t i = 1; i < histoGammaCorr->GetNbinsX()+1 ; i++){
        Double_t newBinContent = histoGammaCorr->GetBinContent(i)/histoGammaCorr->GetBinCenter(i);
        Double_t newBinError = histoGammaCorr->GetBinError(i)/histoGammaCorr->GetBinCenter(i);
        histoGammaCorr->SetBinContent(i,newBinContent);
        histoGammaCorr->SetBinError(i,newBinError);
    }
}


void CorrectGammaMC(TH1D* histoGammaSpecMCCorr,  Double_t deltaEta, Double_t scaling, Double_t nEvtMC){
    histoGammaSpecMCCorr->Scale(1./deltaEta);
    histoGammaSpecMCCorr->Scale(scaling);
    histoGammaSpecMCCorr->Scale(1./nEvtMC);
    for (Int_t i = 1; i < histoGammaSpecMCCorr->GetNbinsX()+1 ; i++){
        Double_t newBinContent = histoGammaSpecMCCorr->GetBinContent(i)/histoGammaSpecMCCorr->GetBinCenter(i);
        Double_t newBinError = histoGammaSpecMCCorr->GetBinError(i)/histoGammaSpecMCCorr->GetBinCenter(i);
        histoGammaSpecMCCorr->SetBinContent(i,newBinContent);
        histoGammaSpecMCCorr->SetBinError(i,newBinError);
    }
}

void CorrectGammaMCTrue(TH1D* histoGammaCorr, TH1D* histoConvProb, TH1D* histoRecoEff, Double_t deltaEta, Double_t scaling, Double_t nEvt){

    histoGammaCorr->Divide(histoGammaCorr,histoConvProb,1.,1.,"");
    histoGammaCorr->Divide(histoGammaCorr,histoRecoEff,1.,1.,"");
    histoGammaCorr->Scale(1./deltaEta);
    histoGammaCorr->Scale(scaling);
    histoGammaCorr->Scale(1./nEvt);
    for (Int_t i = 1; i < histoGammaCorr->GetNbinsX()+1 ; i++){
        Double_t newBinContent = histoGammaCorr->GetBinContent(i)/histoGammaCorr->GetBinCenter(i);
        Double_t newBinError = histoGammaCorr->GetBinError(i)/histoGammaCorr->GetBinCenter(i);
        histoGammaCorr->SetBinContent(i,newBinContent);
        histoGammaCorr->SetBinError(i,newBinError);
    }
}

//*********************************************************************************************************
//***************************** Main routine to correct inclusive photons *********************************
//*********************************************************************************************************
void  CorrectGamma( const char *nameUnCorrectedFile     = "myOutput", 
                    const char *nameCorrectionFile      = "", 
                    TString cutSelection                ="", 
                    TString suffix                      = "eps", 
                    TString nameMeson                   = "Pi0", 
                    TString isMC                        = "kFALSE",
                    TString option                      = "", 
                    TString optionPeriod                = "", 
                    TString fEstimatePileup             = "",//Bool_t kDoPileup = kFALSE, 
                    Int_t mode                          = 9
                  ){
    
    gROOT->Reset();
    

    
    //*****************************************************************************************
    //************************** Set general style settings ***********************************
    //*****************************************************************************************
    StyleSettingsThesis();	
    SetPlotStyle();

    //*****************************************************************************************
    //*************************** Determine K0s scaling factor ********************************
    //*****************************************************************************************
    Double_t doubleAddFactorK0s = ReturnCorrectK0ScalingFactor( option,  cutSelection);
    if(isMC.CompareTo("kTRUE") == 0){
        doubleAddFactorK0s = 0.;
        cout<<" MC --> doubleAddFactorK0s = 0"<<endl;
    } else {
        cout << "The additional K0 correction factor is: "  << doubleAddFactorK0s<<endl;
    }

    //*****************************************************************************************
    //*************************** Find out cutSelections for different things *****************
    //*****************************************************************************************    
    TString fEventCutSelection      = "";
    TString fGammaCutSelection      = "";
    TString fClusterCutSelection    = "";
    TString fElectronCutSelection   = "";
    TString fMesonCutSelection      = "";
    TString fCutSelection           = cutSelection;
    if (mode == 9){
        ReturnSeparatedCutNumber(cutSelection, fGammaCutSelection, fElectronCutSelection,fMesonCutSelection);
        fEventCutSelection      = fGammaCutSelection(0,7);
        fGammaCutSelection      = fGammaCutSelection(7,fGammaCutSelection.Length()-7);
        cout << fEventCutSelection.Data() << "\t" << fGammaCutSelection.Data() << endl;
    } else {
        ReturnSeparatedCutNumberAdvanced(cutSelection,fEventCutSelection, fGammaCutSelection, fClusterCutSelection, fElectronCutSelection, fMesonCutSelection, mode);
    }

    
    
    //*****************************************************************************************
    //*************************** Determine centrality from CutString *************************
    //*****************************************************************************************        
    TString centrality          = GetCentralityString(fEventCutSelection);
    TString collisionSystem     = ReturnFullCollisionsSystem(option);
    TString cent                = "";
        
    if(option.Contains("PbPb")){
        cent        = Form("%s %s", centrality.Data(), collisionSystem.Data());
    } else {
        cent        = collisionSystem; 
    }    
    
    //******************************************************************************************
    //***************************** Set output directory ***************************************
    //******************************************************************************************
    TString outputDir           = Form("%s/%s/%s/CorrectGamma",cutSelection.Data(),option.Data(),suffix.Data());
    gSystem->Exec("mkdir "+outputDir);

    //******************************************************************************************
    //************************ Define additional global variables ******************************
    //******************************************************************************************
    TString textPi0New      = Form("Gamma_%s",nameMeson.Data());
    
    TString textPrefix2;
    if (isMC.CompareTo("kTRUE")==0){
        textPrefix2         = "MC";
    } else {
        textPrefix2         = "data";
    }
    
    Double_t deltaEta       = ReturnDeltaEta(fGammaCutSelection);
    Double_t eta            = deltaEta*0.5;
    Double_t scaling        = 1./(2.*TMath::Pi());
    Bool_t kDoPileup;
    if(fEstimatePileup.CompareTo("")) 
        kDoPileup = kFALSE;
    
    
    //****************************************************************************************** 
    //*******************File definitions and reading histograms from files ********************
    //******************************************************************************************
    // reading uncorrected quantities
    TString fileNameUncorrected             = nameUnCorrectedFile;
    TFile*  fileUnCorrected                 = new TFile(fileNameUncorrected.Data());
    TH1D*   histoESDConvGammaPt             = (TH1D*)fileUnCorrected->Get("ESD_ConvGamma_Pt");
    TH1D*   histoESDConvGammaPtOriginalBin  = (TH1D*)fileUnCorrected->Get("ESD_ConvGamma_Pt_OriginalBinning");
    TH1D*   histoEventQuality               = (TH1D*)fileUnCorrected->Get("NEvents");

    // reading pileup correction factors
    TFile *doPileUpCorr;
    if (kDoPileup){ 
        doPileUpCorr                        = new  TFile(Form("%s/%s/%s_%s_GammaConvV1DCAHistogramms%s_%s.root", cutSelection.Data(), option.Data(), nameMeson.Data(),
                                                              textPrefix2.Data(), optionPeriod.Data(), cutSelection.Data()));
        if(doPileUpCorr->IsZombie()) 
            doPileUpCorr                    = 0;
    } else {
        doPileUpCorr                        = 0;
    }    
    
    TH1D*   histoESDConvGammaPtPileUp;
    TH1D*   histoPhotonDCAzFullPt;
    TH1D*   histoPileUpCorrectionFactor;
    if(doPileUpCorr){
        histoESDConvGammaPtPileUp           = (TH1D*)fileUnCorrected->Get("ESD_ConvGamma_Pt_PileUp");
        histoPhotonDCAzFullPt               = (TH1D*)fileUnCorrected->Get("ESD_GammaPtDCAzBin_Full");
        histoPileUpCorrectionFactor         = (TH1D*)histoESDConvGammaPtPileUp->Clone("PileUpCorrectionFactor");
        histoPileUpCorrectionFactor->Divide(histoPileUpCorrectionFactor,histoESDConvGammaPt,1,1,"B");
    }

    // Calculate number of events used for normalization
    Float_t nEvt;
    if (option.CompareTo("PbPb_2.76TeV") == 0){
        nEvt                                = histoEventQuality->GetBinContent(1);
    } else {
        nEvt                                = GetNEvents(histoEventQuality);
    }
    
    // Read binning histogram
    TH1D*   deltaPt                         = (TH1D*)fileUnCorrected->Get("deltaPt");
    for (Int_t i = 0; i < deltaPt->GetNbinsX() +1; i++){
        deltaPt->SetBinError(i, 0);
    }

    // Read correction histograms
    TFile*  fileCorrections                     = new TFile(nameCorrectionFile);
    TH1D*   histoMCGammaPurity                  = (TH1D*)fileCorrections->Get("MCGammaPurity"); 
    TH1D*   histoMCGammaTruePurity              = (TH1D*)fileCorrections->Get("MCGammaTruePurity"); 
    TH1D*   histoMCGammaTruePurityOriginalBin   = (TH1D*)fileCorrections->Get("MCGammaTruePurityOriginalBinning"); 
    TH1D*   histoMCGammaConvProb                = (TH1D*)fileCorrections->Get("MCGammaConvProb");
    TH1D*   histoGammaRecoEff                   = (TH1D*)fileCorrections->Get("MCGammaRecoEff");
    TH1D*   histoGammaPrimaryRecoEff            = (TH1D*)fileCorrections->Get("MCGammaPrimaryRecoEff");
    TH1D*   histoGammaPrimaryRecoEffMCPt        = (TH1D*)fileCorrections->Get("MCGammaPrimaryRecoEffMCPt");

    // Pileup histograms from MC
    TH1D*   histoMCGammaPurityPileUp;
    TH1D*   histoMCGammaTruePurityPileUp;
    TH1D*   histoGammaRecoEffPileUp;
    TH1D*   histoGammaPrimaryRecoEffPileUp;
    if(doPileUpCorr){
        histoMCGammaPurityPileUp                = (TH1D*)fileCorrections->Get("MCGammaPurityPileUp"); 
        histoMCGammaTruePurityPileUp            = (TH1D*)fileCorrections->Get("MCGammaTruePurityPileUp"); 
        histoGammaRecoEffPileUp                 = (TH1D*)fileCorrections->Get("MCGammaRecoEffPileUp");
        histoGammaPrimaryRecoEffPileUp          = (TH1D*)fileCorrections->Get("MCGammaPrimaryRecoEffPileUp");
    }


    //TH1D *histoGammaPrimaryRecoEffEta                     = (TH1D*)fileCorrections->Get("MCGammaPrimaryRecoEffEta");
    TH1D*   histoGammaBackground                            = (TH1D*)fileCorrections->Get("MCGammaBackground");
    TH1D*   histoMCESDGamma                                 = (TH1D*)fileCorrections->Get("MCESD_ConvGamma_Pt");
    TH1D*   histoMCESDPrimaryGamma                          = (TH1D*)fileCorrections->Get("MCESD_PrimaryConvGamma_Pt");
    TH1D*   histoAllGammaPt                                 = (TH1D*)fileCorrections->Get("MC_AllGamma_Pt");
    TH1D*   histoGammaMCConvPt                              = (TH1D*)fileCorrections->Get("MC_ConvGamma_Pt");
    TH1D*   histoGammaESDTrueConvPt                         = (TH1D*)fileCorrections->Get("ESD_TrueConvGamma_Pt");
    TH1D*   histoGammaESDTruePrimaryConvPt                  = (TH1D*)fileCorrections->Get("ESD_TruePrimaryConvGamma_Pt");
    TH2D*   histoGammaESDTruePrimary_ESDPt_MCPt_MC          = (TH2D*)fileCorrections->Get("ESD_TruePrimaryConvGammaESD_PtMCPt");
    TH2D*   histoGammaESDTruePrimary_ESDPt_MCPt_MC_Rebin    = (TH2D*)fileCorrections->Get("ESD_TrueConvPrimaryGamma_ESDPt_MCPt_Rebin");

    TH1D*   histoMCESDGammaPileUp;
    TH1D*   histoPileUpCorrectionFactorMC;
    if(doPileUpCorr){
        histoMCESDGammaPileUp                               = (TH1D*)fileCorrections->Get("ESDMC_ConvGamma_Pt_PileUp");
        if (histoMCESDGammaPileUp){
            histoPileUpCorrectionFactorMC                   = (TH1D*)histoMCESDGammaPileUp->Clone("PileUpCorrectionFactorMC");
            histoPileUpCorrectionFactorMC->Divide(histoPileUpCorrectionFactorMC,histoMCESDGamma,1,1,"B");
        }
    }
    TH1F*   histoEventQualityMC                             = (TH1F*)fileCorrections->Get("NEvents");
    TH1D*   histoAllGammaOriginalBinPt                      = (TH1D*)fileCorrections->Get("MC_AllGamma_Pt_OriginalBinning");
    TH1D*   histoDecayPi0GammaPt                            = (TH1D*)fileCorrections->Get("MC_DecayGammaPi0_Pt");
    TH1D*   histoDecayEtaGammaPt                            = (TH1D*)fileCorrections->Get("MC_DecayGammaEta_Pt");
    TH1D*   histoDecayEtapGammaPt                           = (TH1D*)fileCorrections->Get("MC_DecayGammaEtap_Pt");
    TH1D*   histoDecayOmegaGammaPt                          = (TH1D*)fileCorrections->Get("MC_DecayGammaOmega_Pt");
    TH1D*   histoDecayRho0GammaPt                           = (TH1D*)fileCorrections->Get("MC_DecayGammaRho_Pt");
    TH1D*   histoDecayPhiGammaPt                            = (TH1D*)fileCorrections->Get("MC_DecayGammaPhi_Pt");
    
    // Read True Combinatorial Background
    TString combinatorics[17]                               = { "Elec+Elec","Elec+Pion","Elec+Kaon","Elec+Proton","Elec+Muon","Pion+Pion","Pion+Kaon","Pion+Proton",
                                                                "Pion+Muon","Kaon+Kaon","Kaon+Proton","Kaon+Muon","Proton+Proton","Proton+Muon","Muon+Muon","Rest","All"};
    TH1D**  histoCombinatorialSpeciesPt                     = new TH1D*[17];
    for(Int_t i = 0;i<17;i++){
        histoCombinatorialSpeciesPt[i]                      = (TH1D*)fileCorrections->Get(Form("ESD_TrueComb%s_Pt",combinatorics[i].Data()));
        histoCombinatorialSpeciesPt[i]->SetMinimum(1e-10);
    }
    // Read secondary contamination histos
    TH1D*   histoGammaESDTrueSecondaryConvPt                    = (TH1D*)fileCorrections->Get("ESD_TrueSecondaryConvGamma_Pt");
    TH1D*   histoGammaESDTrueSecondaryConvGammaFromXFromK0sPt   = (TH1D*)fileCorrections->Get("ESD_TrueSecondaryConvGammaFromXFromK0s_Pt");
    TH1D*   histoFracAllGammaToSec                              = (TH1D*)fileCorrections->Get("FracAllGammaToSec");
    TH1D*   histoFracAllGammaToSecFromXFromK0s                  = (TH1D*)fileCorrections->Get("FracAllGammaToSecFromXFromK0s");
    TH1D*   histoFracAllGammaToSecOriginalBin                   = (TH1D*)fileCorrections->Get("FracAllGammaToSecOriginalBinning");
    TH1D*   histoFracAllGammaToSecFromXFromK0sOriginalBin       = (TH1D*)fileCorrections->Get("FracAllGammaToSecFromXFromK0sOriginalBinning");

    TH1D*   histoFracAllGammaToSecPileUp;
    TH1D*   histoFracAllGammaToSecFromXFromK0sPileUp;
    TH1D*   histoPhotonDCAzFullPtMC;
    if(doPileUpCorr){
        histoFracAllGammaToSecPileUp                        = (TH1D*)fileCorrections->Get("FracAllGammaToSecPileUp");
        histoFracAllGammaToSecFromXFromK0sPileUp            = (TH1D*)fileCorrections->Get("FracAllGammaToSecFromXFromK0sPileUp");
        histoPhotonDCAzFullPtMC                             = (TH1D*)fileCorrections->Get("ESDMC_GammaPtDCAzBin_Full");
    }

    // Determine number of events in MC
    Float_t nEvtMC;
    if (option.CompareTo("PbPb_2.76TeV") == 0){
        nEvtMC = histoEventQualityMC->GetBinContent(1);
    } else {
        nEvtMC = GetNEvents(histoEventQualityMC);
    }

    // Determine maximum pT
    Double_t maxPtGamma                                     = histoESDConvGammaPt->GetXaxis()->GetBinUpEdge(histoESDConvGammaPt->GetNbinsX());
    
    
    // Proper Scaling Background
    TH1D *ScalingGammaBackground                            = (TH1D*) histoESDConvGammaPt->Clone("ScalingGammaBackground");
    ScalingGammaBackground->Divide(ScalingGammaBackground, histoMCESDGamma, 1., 1, "");
    ScalingGammaBackground->Scale(nEvtMC/nEvt);
    histoGammaBackground->Scale(1./nEvtMC);
    TH1D *histoGammaMCBackground                            = (TH1D*)histoGammaBackground->Clone("histoGammaMCBackground");
    histoGammaBackground->Multiply(ScalingGammaBackground);


    //**********************************************************************************
    //******************** PrimVtx DCA Plot ********************************************
    //**********************************************************************************

    if(doPileUpCorr){      
        TCanvas *canvasPileUpCorrFactor = GetAndSetCanvas("canvasPileUpCorrFactor");

            DrawGammaSetMarker(histoPileUpCorrectionFactor, 20, 3, 1, 1);
            if (histoMCESDGammaPileUp)DrawGammaSetMarker(histoPileUpCorrectionFactorMC, 24, 3, 2, 2);

            SetHistogramm(histoPileUpCorrectionFactor,"p_{T} (GeV/c)","Correction Factor (%)",0.84,1.02);
            if (histoMCESDGammaPileUp)SetHistogramm(histoPileUpCorrectionFactorMC,"p_{T} (GeV/c)","Correction Factor (%)",0.84,1.02);

            histoPileUpCorrectionFactor->DrawCopy("");
            if (histoMCESDGammaPileUp)histoPileUpCorrectionFactorMC->Draw("same");

            TLegend* legendPileUpCorrFactor = GetAndSetLegend(0.3,0.2,2.2,1,cent);
            legendPileUpCorrFactor->AddEntry(histoPileUpCorrectionFactor,"Correction Factor Data","lp");
            if (histoMCESDGammaPileUp)legendPileUpCorrFactor->AddEntry(histoPileUpCorrectionFactorMC,"Correction Factor MC","lp");
            legendPileUpCorrFactor->Draw();
        
        canvasPileUpCorrFactor->SaveAs(Form("%s/%s_PileUpCorrFactor_%s_%s.%s",outputDir.Data(),textPi0New.Data(),textPrefix2.Data(),cutSelection.Data(),suffix.Data()));
        delete canvasPileUpCorrFactor;
    }
    
    //**********************************************************************************
    //******************** Background Plot *********************************************
    //**********************************************************************************
    TCanvas *canvasBackground = GetAndSetCanvas("canvasBackground");
    canvasBackground->SetLogy();

        TH1D* RawGammaSpectrumMC = (TH1D*) histoMCESDGamma->Clone("RawGammaSpectrumMC");
        RawGammaSpectrumMC->Scale(1./nEvtMC);
        TH1D* RawGammaSpectrum = (TH1D*) histoESDConvGammaPt->Clone("RawGammaSpectrum");
        RawGammaSpectrum->Scale(1./nEvt);

        DrawGammaSetMarker(RawGammaSpectrum, 20, 1.0, 1, 1);
        DrawGammaSetMarker(histoGammaBackground, 20, 1.0, 2, 2);

        SetHistogramm(histoGammaBackground,"p_{T} (GeV/c)",Form("Background for #gamma in |#eta| < %g",eta));
        SetHistogramm(RawGammaSpectrum,"p_{T} (GeV/c)",Form("Background for #gamma in |#eta| < %g",eta),1e-8,5);

        RawGammaSpectrum->DrawCopy("");
        histoGammaBackground->Draw("same");


        TLegend* legendBackground = GetAndSetLegend(0.6,0.7,3,1,cent);
        legendBackground->AddEntry(RawGammaSpectrum,"raw #gamma spectrum","pl");
        legendBackground->AddEntry(histoGammaBackground,"#gamma background","pl");
        legendBackground->Draw();

    canvasBackground->SaveAs(Form("%s/%s_Background_%s_%s.%s",outputDir.Data(),textPi0New.Data(),textPrefix2.Data(),cutSelection.Data(),suffix.Data()));
    delete canvasBackground;
    

    //****************************************************************************************** 
    //************************ Calculating background from Secondaries *************************
    //****************************************************************************************** 
    TH1D *histoSecondaryGammaSpecPt                 = (TH1D*) histoESDConvGammaPt->Clone("SecondaryGammaSpecPt");
    TH1D *histoSecondaryGammaFromXFromK0sSpecPt     = (TH1D*) histoESDConvGammaPt->Clone("SecondaryGammaSpecFromXFromK0sPt");
    histoSecondaryGammaSpecPt->Multiply(histoFracAllGammaToSec);
    histoSecondaryGammaFromXFromK0sSpecPt->Multiply(histoFracAllGammaToSecFromXFromK0s);

    histoGammaESDTrueSecondaryConvPt->Scale(1./nEvtMC);
    histoGammaESDTrueSecondaryConvGammaFromXFromK0sPt->Scale(1./nEvtMC);
    histoSecondaryGammaSpecPt->Scale(1./nEvt);
    histoSecondaryGammaFromXFromK0sSpecPt->Scale(1./nEvt);

    // Correct the secondary fractions for pileup
    TH1D *histoSecondaryGammaSpecPtPileUp;
    TH1D *histoSecondaryGammaFromXFromK0sSpecPtPileUp;
    if(doPileUpCorr){
        histoSecondaryGammaSpecPtPileUp             = (TH1D*) histoESDConvGammaPtPileUp->Clone("SecondaryGammaSpecPtPileUp");
        histoSecondaryGammaFromXFromK0sSpecPtPileUp = (TH1D*) histoESDConvGammaPtPileUp->Clone("SecondaryGammaSpecFromXFromK0sPtPileUp");
        histoSecondaryGammaSpecPtPileUp->Multiply(histoFracAllGammaToSecPileUp);
        histoSecondaryGammaFromXFromK0sSpecPtPileUp->Multiply(histoFracAllGammaToSecFromXFromK0sPileUp);
        histoSecondaryGammaSpecPtPileUp->Scale(1./nEvt);
        histoSecondaryGammaFromXFromK0sSpecPtPileUp->Scale(1./nEvt);
        histoSecondaryGammaFromXFromK0sSpecPtPileUp->Scale(doubleAddFactorK0s);
    }
    
    // plotting secondary spectra
    TCanvas *canvasSecSpec = GetAndSetCanvas("canvasSecSpec");
    canvasSecSpec->SetLogy();

        SetHistogramm(histoSecondaryGammaSpecPt, "p_{T} (GeV/c)","Secondary Converted #gamma");
        SetHistogramm(histoSecondaryGammaFromXFromK0sSpecPt,"p_{T} (GeV/c)","Secondary Converted #gamma");
        SetHistogramm(histoGammaESDTrueSecondaryConvGammaFromXFromK0sPt,"p_{T} (GeV/c)","Secondary Converted #gamma");
        SetHistogramm(histoGammaESDTrueSecondaryConvPt,"p_{T} (GeV/c)","Secondary Converted #gamma",1e-10,1e-1);

        DrawGammaSetMarker(histoGammaESDTrueSecondaryConvPt, 20, 1.0, kRed+1, kRed+1);
        DrawGammaSetMarker(histoGammaESDTrueSecondaryConvGammaFromXFromK0sPt, 24, 1.0, kRed-1, kRed-1);
        DrawGammaSetMarker(histoSecondaryGammaSpecPt, 21, 1.0, kBlue+1, kBlue+1);
        DrawGammaSetMarker(histoSecondaryGammaFromXFromK0sSpecPt, 25, 1.0, kBlue-1, kBlue-1);

        histoGammaESDTrueSecondaryConvPt->Draw();
        histoGammaESDTrueSecondaryConvGammaFromXFromK0sPt->Draw("same");
        histoSecondaryGammaSpecPt->Draw("same");
        histoSecondaryGammaFromXFromK0sSpecPt->DrawCopy("same");

        histoSecondaryGammaFromXFromK0sSpecPt->Scale(doubleAddFactorK0s);
        TLegend* legendSecSpec = GetAndSetLegend(0.2,0.76,4);
        legendSecSpec->AddEntry(histoGammaESDTrueSecondaryConvPt,"Raw MC Sec #gamma Spectrum","pl");
        legendSecSpec->AddEntry(histoGammaESDTrueSecondaryConvGammaFromXFromK0sPt,"Raw MC Sec #gamma from X from K0s","pl");
        legendSecSpec->AddEntry(histoSecondaryGammaSpecPt,"Raw data Sec #gamma Spectrum (scaled with K0s factor)","pl");
        legendSecSpec->AddEntry(histoSecondaryGammaFromXFromK0sSpecPt,"Raw data Sec #gamma from X from K0s","pl");
        legendSecSpec->Draw();
        
    canvasSecSpec->SaveAs(Form("%s/%s_SecondarySpectra_%s.%s",outputDir.Data(),textPi0New.Data(),cutSelection.Data(),suffix.Data()));
    delete canvasSecSpec;
    
    // plotting secondary fractions
    TCanvas *canvasSecFrac = GetAndSetCanvas("canvasSecFrac");
    
        DrawGammaSetMarker(histoFracAllGammaToSec, 20, 1.0, 1, 1);
        DrawGammaSetMarker(histoFracAllGammaToSecFromXFromK0s, 20, 1.0, 2, 2);

        SetHistogramm(histoFracAllGammaToSecFromXFromK0s,"p_{T} (GeV/c)","Fraction of Secondary Converted #gamma");
        SetHistogramm(histoFracAllGammaToSec,"p_{T} (GeV/c)","Fraction of Secondary Converted #gamma");

        histoFracAllGammaToSec->Draw();
        histoFracAllGammaToSecFromXFromK0s->Draw("same");


        TLegend* legendSecFrac = GetAndSetLegend(0.15,0.8,2,1,cent);
        legendSecFrac->AddEntry(histoFracAllGammaToSec,"Fraction Sec #gamma","pl");
        legendSecFrac->AddEntry(histoFracAllGammaToSecFromXFromK0s,Form("Fraction Sec #gamma from X from K0s"),"pl");
        legendSecFrac->Draw();
    canvasSecFrac->SaveAs(Form("%s/%s_SecondaryGammaFraction_%s.%s",outputDir.Data(),textPi0New.Data(),cutSelection.Data(),suffix.Data()));
    delete canvasSecFrac;

    //**********************************************************************************
    //******************** Purity Plot *************************************************
    //**********************************************************************************
    // Plain Purity plotted
    TCanvas *canvasPurity = GetAndSetCanvas("canvasPurity");

        DrawGammaSetMarker(histoMCGammaPurity, 24, 1.0, kRed+2, kRed+2);
        DrawGammaSetMarker(histoMCGammaTruePurity, 20, 1.0, 1, 1);
        if(doPileUpCorr)DrawGammaSetMarker(histoMCGammaTruePurityPileUp, 20, 1.0, kBlue+2, kBlue+2);
        SetHistogramm(histoMCGammaTruePurity,"p_{T} (GeV/c)",Form("Purity for #gamma in |#eta| < %g",eta),0.4, 1.);
        histoMCGammaTruePurity->Draw();
        
        TLegend* legendPurity = GetAndSetLegend(0.2,0.15,1);
        legendPurity->AddEntry(histoMCGammaTruePurity,"Purity");
        legendPurity->Draw();

    canvasPurity->SaveAs(Form("%s/%s_Purity_%s.%s",outputDir.Data(),textPi0New.Data(),cutSelection.Data(),suffix.Data()));
    delete canvasPurity;
    
    // plotting purity comparison
    TCanvas* canvasCompPurity = GetAndSetCanvas("canvasCompPurity");
    DrawGammaCanvasSettings( canvasCompPurity, 0.1, 0.015, 0.02, 0.09);
    
        TPad* padCompPurity = new TPad("padCompPurity", "", 0., 0.25, 1., 1.,-1, -1, -2);
        DrawGammaPadSettings( padCompPurity, 0.10, 0.015, 0.02, 0.);
        padCompPurity->Draw();
        TPad* padBinCompPurityRatio = new TPad("padBinCompPurityRatio", "", 0., 0., 1., 0.25,-1, -1, -2);
        DrawGammaPadSettings( padBinCompPurityRatio, 0.1, 0.015, 0.0, 0.35);
        padBinCompPurityRatio->Draw();
        padCompPurity->cd();
        
        SetHistogramm(histoMCGammaPurity,"p_{T} (GeV/c)",Form("Purity for #gamma in |#eta| < %g",eta),0.4, 1.);
        SetHistogramm(histoMCGammaTruePurity,"p_{T} (GeV/c)",Form("Purity for #gamma in |#eta| < %g",eta),0.4, 1.);
        if(doPileUpCorr)SetHistogramm(histoMCGammaTruePurityPileUp,"p_{T} (GeV/c)",Form("Purity for #gamma in |#eta| < %g",eta),0.4, 1.);

        histoMCGammaTruePurity->Draw("e1");
        histoMCGammaPurity->Draw("e1,same");
        if(doPileUpCorr)histoMCGammaTruePurityPileUp->Draw("e1,same");

        TLegend* legendCompPurity = GetAndSetLegend(0.2,0.05,2,1,cent);
        legendCompPurity->AddEntry(histoMCGammaPurity,"Purity (prim+sec)");
        legendCompPurity->AddEntry(histoMCGammaTruePurity,"True Primary Purity");
        if(doPileUpCorr)legendCompPurity->AddEntry(histoMCGammaTruePurityPileUp,"True Primary Purity Pile Up");
        legendCompPurity->Draw();

        padBinCompPurityRatio->cd();
        
        TH1D* histoMCGammaTruePurityRatio = (TH1D*)histoMCGammaTruePurity->Clone("");
        histoMCGammaTruePurityRatio->Divide(histoMCGammaPurity);
        
        TH1D* histoMCGammaTruePurityPileUpRatio;
        if(doPileUpCorr){
            histoMCGammaTruePurityPileUpRatio = (TH1D*)histoMCGammaTruePurity->Clone("");
            histoMCGammaTruePurityPileUpRatio->Divide(histoMCGammaTruePurityPileUp);
        }
        
        SetHistogramm(histoMCGammaTruePurityRatio, "p_{T} (GeV/c)","#frac{True Purity}{Purity (pri+sec)}", 0.95, 1.05);
        histoMCGammaTruePurityRatio->GetYaxis()->SetTitleSize(0.1);
        histoMCGammaTruePurityRatio->GetYaxis()->SetTitleOffset(0.4);
        histoMCGammaTruePurityRatio->GetYaxis()->CenterTitle(kTRUE);
        histoMCGammaTruePurityRatio->GetYaxis()->SetNdivisions(5);

        histoMCGammaTruePurityRatio->DrawCopy("e1");
        if(doPileUpCorr)histoMCGammaTruePurityPileUpRatio->DrawCopy("e1,same");
        
        DrawGammaLines(0., maxPtGamma,1, 1,0.5);
   
    canvasCompPurity->SaveAs(Form("%s/%s_CompPurity_%s.%s",outputDir.Data(),textPi0New.Data(),cutSelection.Data(),suffix.Data()));
    delete padCompPurity;
    delete padBinCompPurityRatio;
    delete canvasCompPurity;

    //**********************************************************************************
    //******************** Conversion Prob Plot ****************************************
    //**********************************************************************************
    TCanvas *canvasConvProb = GetAndSetCanvas("canvasConvProb");
        DrawGammaSetMarker(histoMCGammaConvProb, 20, 1.0, 1, 1);
        SetHistogramm(histoMCGammaConvProb, "p_{T} (GeV/c)",Form("Conversion Probability for #gamma in |#eta| < %g",eta), 0.04, 0.10);
        histoMCGammaConvProb->Draw();

        TF1 *fConv  = new TF1("line","[0]",2.5,25.);
        histoMCGammaConvProb->Fit(fConv,"QRME0");
        Double_t parameterProb[1];
        fConv->GetParameters(parameterProb);

        DrawGammaLines(0., maxPtGamma,parameterProb[0], parameterProb[0],1);

        TLegend* legendConversionProb = GetAndSetLegend(0.15 ,0.15,1,1,cent);
        legendConversionProb->Draw();

    canvasConvProb->SaveAs(Form("%s/%s_ConversionProb_%s.%s",outputDir.Data(),textPi0New.Data(),cutSelection.Data(),suffix.Data()));
    delete canvasConvProb;

    //**********************************************************************************
    //******************** Reconstructin Eff Plot **************************************
    //**********************************************************************************
    // drawing reco Efficiency
    TCanvas *canvasRecoEff = GetAndSetCanvas("canvasRecoEff");
        DrawGammaSetMarker(histoGammaPrimaryRecoEffMCPt, 20, 1.0, 1, 1);
        SetHistogramm(histoGammaPrimaryRecoEffMCPt,"p_{T,MC} (GeV/c)",Form("Reconstruction Efficency for #gamma in |#eta| < %g",eta), 0., 1.0);
        histoGammaPrimaryRecoEffMCPt->Draw();
    
    canvasRecoEff->SaveAs(Form("%s/%s_ReconstructionEff_%s.%s",outputDir.Data(),textPi0New.Data(),cutSelection.Data(),suffix.Data()));
    delete canvasRecoEff;
    
    // draw comparison of reco efficiencies
    TCanvas* canvasCompRecoEff = GetAndSetCanvas("canvasCompRecoEff");
    DrawGammaCanvasSettings( canvasCompRecoEff,0.1, 0.015, 0.02, 0.09);
        TPad* padCompRecoEff = new TPad("padCompRecoEff", "", 0., 0.25, 1., 1.,-1, -1, -2);
        DrawGammaPadSettings( padCompRecoEff, 0.10, 0.015, 0.02, 0.);
        padCompRecoEff->Draw();
        TPad* padBinCompRecoEffRatio = new TPad("padBinCompRecoEffRatio", "", 0., 0., 1., 0.25,-1, -1, -2);
        DrawGammaPadSettings( padBinCompRecoEffRatio,  0.1, 0.015, 0.0, 0.35);
        padBinCompRecoEffRatio->Draw();

        padCompRecoEff->cd();
        SetHistogramm(histoGammaPrimaryRecoEffMCPt, "p_{T} (GeV/c)",Form("Reconstruction Efficency for #gamma in |#eta| < %g",eta), 0., 1.0);
        SetHistogramm(histoGammaPrimaryRecoEff, "p_{T} (GeV/c)",Form("Reconstruction Efficency for #gamma in |#eta| < %g",eta), 0., 1.0);
        if(doPileUpCorr)SetHistogramm(histoGammaPrimaryRecoEffPileUp, "p_{T} (GeV/c)",Form("Reconstruction Efficency for #gamma in |#eta| < %g",eta), 0., 1.0);
        
        DrawGammaSetMarker(histoGammaPrimaryRecoEffMCPt, 20, 1.0, 6, 6);
        DrawGammaSetMarker(histoGammaRecoEff, 20, 1.0, 1, 1);
        DrawGammaSetMarker(histoGammaPrimaryRecoEff, 20, 1.0, 2, 2);
        if(doPileUpCorr)DrawGammaSetMarker(histoGammaPrimaryRecoEffPileUp, 20, 1.0, 5, 5);
        
        histoGammaPrimaryRecoEff->Draw("e1");
        if(doPileUpCorr)histoGammaPrimaryRecoEffPileUp->Draw("e1,same");
        //histoGammaRecoEff->Draw("same,e1");
        histoGammaPrimaryRecoEffMCPt->Draw("same,e1");

        TLegend* legendCompRecoEff = GetAndSetLegend(0.15 ,0.05,4,1,cent);
        legendCompRecoEff->SetTextSize(0.04);
        legendCompRecoEff->AddEntry(histoGammaPrimaryRecoEffMCPt,"MC pT Reconstruction Efficiency (unfolding)");
        legendCompRecoEff->AddEntry(histoGammaPrimaryRecoEff,"Reconstruction Efficiency for primary  #gamma");
        if(doPileUpCorr)legendCompRecoEff->AddEntry(histoGammaPrimaryRecoEffPileUp,"Reconstruction Efficiency for primary  #gamma Pile Up");
        //legendCompRecoEff->AddEntry(histoGammaRecoEff,"Reco Eff with Sec");
        legendCompRecoEff->Draw();

        padBinCompRecoEffRatio->cd();

        TH1D* histoGammaPrimaryRecoEffRatio = (TH1D*)histoGammaPrimaryRecoEff->Clone("GammaPrimaryRecoEffRatio");
        histoGammaPrimaryRecoEffRatio->Divide(histoGammaPrimaryRecoEffMCPt);
        TH1D* histoGammaEffRatio = (TH1D*)histoGammaRecoEff->Clone("histoGammaEffRatio");
        histoGammaEffRatio->Divide(histoGammaPrimaryRecoEffMCPt);

        TH1D* histoGammaPrimaryRecoEffPileUpRatio;
        if(doPileUpCorr){
            histoGammaPrimaryRecoEffPileUpRatio = (TH1D*)histoGammaPrimaryRecoEffPileUp->Clone("GammaPrimaryRecoEffRatioPileUp");
            histoGammaPrimaryRecoEffPileUpRatio->Divide(histoGammaPrimaryRecoEff);
        }
        SetHistogramm(histoGammaPrimaryRecoEffRatio,"p_{T} (GeV/c)","#frac{Reco Eff x}{Primary MC Reco Eff}" , 0.7, 1.25);
        SetHistogramm(histoGammaEffRatio,"p_{T} (GeV/c)","#frac{Reco Eff x}{Primary MC Reco Eff}" , 0.7, 1.25);
        histoGammaPrimaryRecoEffRatio->GetYaxis()->SetTitleSize(0.1);
        histoGammaPrimaryRecoEffRatio->GetYaxis()->SetTitleOffset(0.4);
        histoGammaPrimaryRecoEffRatio->GetYaxis()->CenterTitle(kTRUE);
        histoGammaPrimaryRecoEffRatio->GetYaxis()->SetNdivisions(5);

        histoGammaPrimaryRecoEffRatio->DrawCopy("e1");
        if(doPileUpCorr)histoGammaPrimaryRecoEffPileUpRatio->DrawCopy("e1");
        
        DrawGammaLines(0., maxPtGamma,1, 1,0.5);
    
    //histoGammaEffRatio->Draw("same,e1");
    canvasCompRecoEff ->SaveAs(Form("%s/%s_CompRecEff_%s.%s",outputDir.Data(),textPi0New.Data(),cutSelection.Data(),suffix.Data()));
    delete padCompRecoEff;
    delete padBinCompRecoEffRatio;
    delete canvasCompRecoEff;
    
    //**********************************************************************************
    //******************** Response Matrix for detector resolution *********************
    //**********************************************************************************
    
    // Plotting response matrix
    TCanvas *canvasResponseMatrix = GetAndSetCanvas("canvasResponseMatrix");
    canvasResponseMatrix->SetRightMargin(0.1);
    canvasResponseMatrix->SetLogz();

        SetHistogramm(histoGammaESDTruePrimary_ESDPt_MCPt_MC, "Reconstructed p_{T} (GeV/c)","MC p_{T} (GeV/c)");
        histoGammaESDTruePrimary_ESDPt_MCPt_MC->GetYaxis()->SetRangeUser(0,25);
        histoGammaESDTruePrimary_ESDPt_MCPt_MC->GetXaxis()->SetRangeUser(0,25);
        
        histoGammaESDTruePrimary_ESDPt_MCPt_MC->Draw("colz");
        
        TLegend* legendResponseMatrix = GetAndSetLegend(0.15,0.90,1);
        legendResponseMatrix->AddEntry(histoGammaESDTruePrimary_ESDPt_MCPt_MC,"Pb-Pb #gamma Response Matrix","");
        legendResponseMatrix->Draw();
    canvasResponseMatrix->SaveAs(Form("%s/%s_ResponseMatrix_%s.%s",outputDir.Data(),textPi0New.Data(),cutSelection.Data(),suffix.Data()));

    //**********************************************************************************
    //************************ Unfolding of inclusive gamma spectrum *******************
    //**********************************************************************************
    
    // determine secondary contribution in orginal binning
    TH1D *histoSecondaryGammaSpecPtOriginalBin             = (TH1D*) histoESDConvGammaPtOriginalBin->Clone("SecondaryGammaSpecPt");
    TH1D *histoSecondaryGammaFromXFromK0sSpecPtOriginalBin = (TH1D*) histoESDConvGammaPtOriginalBin->Clone("SecondaryGammaSpecFromXFromK0sPt");
    histoSecondaryGammaSpecPtOriginalBin->Multiply(histoFracAllGammaToSecOriginalBin);
    histoSecondaryGammaFromXFromK0sSpecPtOriginalBin->Multiply(histoFracAllGammaToSecFromXFromK0sOriginalBin);
    histoSecondaryGammaFromXFromK0sSpecPtOriginalBin->Scale(doubleAddFactorK0s);

    //subtract secondary contribution from inclusive spectrum
    histoESDConvGammaPtOriginalBin->Add(histoSecondaryGammaSpecPtOriginalBin,-1);
    histoESDConvGammaPtOriginalBin->Add(histoSecondaryGammaFromXFromK0sSpecPtOriginalBin,-1);
    histoESDConvGammaPtOriginalBin->Multiply(histoMCGammaTruePurityOriginalBin);
    
    // create histograms for unfolding for different techniques
    TH1D *histoESDConvGammaPtUnfold             = (TH1D*) histoESDConvGammaPtOriginalBin->Clone("histoESDConvGammaPtUnfold");
    TH1D *histoESDConvGammaPtUnfoldBinByBin     = (TH1D*) histoESDConvGammaPtOriginalBin->Clone("histoESDConvGammaPtUnfoldBinByBin");
    //TH1D *histoESDConvGammaPtUnfoldSvD        =  (TH1D*) histoESDConvGammaPtOriginalBin->Clone("histoESDConvGammaPtUnfoldSvD");
    // TH1D *histoESDConvGammaPtUnfoldTUnfold   =  (TH1D*) histoESDConvGammaPtOriginalBin->Clone("histoESDConvGammaPtUnfoldTUnfold");

    // Unfolding setup:
    // RooUnfoldResponse constructor - create from already-filled histograms
    // "response" gives the response matrix, measured X truth.
    // "measured" and "truth" give the projections of "response" onto the X-axis and Y-axis respectively,
    // but with additional entries in "measured" for measurements with no corresponding truth (fakes/background) and
    // in "truth" for unmeasured events (inefficiency).
    // "measured" and/or "truth" can be specified as 0 (1D case only) or an empty histograms (no entries) as a shortcut
    // to indicate, respectively, no fakes and/or no inefficiency.
    RooUnfoldResponse   response(0,0,histoGammaESDTruePrimary_ESDPt_MCPt_MC);
    
    // unfold with different techniques, but same response matrix
    RooUnfoldBayes      unfold_Spectrum (&response,histoESDConvGammaPtUnfold, 4);
    RooUnfoldBinByBin   unfold_SpectrumBinByBin (&response,histoESDConvGammaPtUnfoldBinByBin);
    //RooUnfoldSvd      unfold_SpectrumSvD (&response, histoESDConvGammaPtUnfoldSvD, 20);   
    //RooUnfoldTUnfold  unfold_SpectrumTUnfold (&response,histoESDConvGammaPtUnfoldTUnfold);
    
    
    // get histograms from RooUnfold and rebin them 
    histoESDConvGammaPtUnfold           = (TH1D*) unfold_Spectrum.Hreco();
    histoESDConvGammaPtUnfold           = RebinTH1D(histoESDConvGammaPtUnfold,histoESDConvGammaPt,kTRUE);
    histoESDConvGammaPtUnfoldBinByBin   = (TH1D*) unfold_SpectrumBinByBin.Hreco();
    histoESDConvGammaPtUnfoldBinByBin   = RebinTH1D(histoESDConvGammaPtUnfoldBinByBin,histoESDConvGammaPt,kTRUE);
    // histoESDConvGammaPtUnfoldSvD     = (TH1D*) unfold_SpectrumSvD.Hreco();
    // histoESDConvGammaPtUnfoldSvD     = RebinTH1D(histoESDConvGammaPtUnfoldSvD,histoESDConvGammaPt,kTRUE);
    // histoESDConvGammaPtUnfoldTUnfold = (TH1D*) unfold_SpectrumTUnfold.Hreco();
    // histoESDConvGammaPtUnfoldTUnfold = RebinTH1D(histoESDConvGammaPtUnfoldTUnfold,histoESDConvGammaPt,kTRUE);

    // Correct inclusive photon spectrum with conversion probability & reco efficiency (both versus MC pt)
    TH1D *histoESDConvGammaPtUnfoldNotCorrected     = (TH1D*) histoESDConvGammaPtUnfold->Clone("GammaUnfoldNotCorrected");
    CorrectGammaDataUnfold(histoESDConvGammaPtUnfold,histoMCGammaConvProb, histoGammaPrimaryRecoEffMCPt, deltaEta, scaling, nEvt);
    CorrectGammaDataUnfold(histoESDConvGammaPtUnfoldBinByBin,histoMCGammaConvProb, histoGammaPrimaryRecoEffMCPt, deltaEta, scaling, nEvt);
    //CorrectGammaDataUnfold(histoESDConvGammaPtUnfoldSvD,histoMCGammaConvProb, histoGammaPrimaryRecoEffMCPt, deltaEta, scaling, nEvt);
    //CorrectGammaDataUnfold(histoESDConvGammaPtUnfoldTUnfold,histoMCGammaConvProb, histoGammaPrimaryRecoEffMCPt, deltaEta, scaling, nEvt);
    
    // Correct inclusive photon spectrum for pileup contribution
    DrawGammaSetMarker(histoESDConvGammaPtUnfold, 20, 1.0, 1, 1);
    TH1D *histoESDConvGammaPtUnfoldPileUp;
    if(doPileUpCorr){
        histoESDConvGammaPtUnfoldPileUp         = (TH1D*) histoESDConvGammaPtUnfold->Clone("GammaUnfoldPileUp");
        histoESDConvGammaPtUnfoldPileUp->Multiply(histoPileUpCorrectionFactor);
    }
    SetHistogramm(histoESDConvGammaPtUnfold,"p_{T} (GeV/c)", "#frac{1}{2#pi N_{ev.}} #frac{d^{2}N}{p_{T}dp_{T}dy} (c/GeV)^{2}");
    SetHistogramm(histoESDConvGammaPtUnfoldBinByBin,"p_{T} (GeV/c)", "#frac{1}{2#pi N_{ev.}} #frac{d^{2}N}{p_{T}dp_{T}dy} (c/GeV)^{2}");
    //SetHistogramm(histoESDConvGammaPtUnfoldSvD,"p_{T} (GeV/c)", "#frac{1}{2#pi N_{ev.}} #frac{d^{2}N}{p_{T}dp_{T}dy} (c/GeV)^{2}");
    //SetHistogramm(histoESDConvGammaPtUnfoldTUnfold,"p_{T} (GeV/c)", "#frac{1}{2#pi N_{ev.}} #frac{d^{2}N}{p_{T}dp_{T}dy} (c/GeV)^{2}");
    

    // Plotting corrected photon spectrum
    TCanvas *canvasCorrGammaSpecUnfold          = GetAndSetCanvas("canvasCorrGammaSpecUnfold");
    canvasCorrGammaSpecUnfold->SetLogy();
        TH1D *Dummy                             = (TH1D*)histoESDConvGammaPt->Clone("Dummy");
        SetHistogramm(Dummy,"p_{T} (GeV/c)", "#frac{1}{2#pi N_{ev.}} #frac{d^{2}N}{p_{T}dp_{T}dy} (c/GeV)^{2}",1e-8,10);
        Dummy->Reset();
        Dummy->Draw();
        histoESDConvGammaPtUnfold->DrawCopy("same");
        histoESDConvGammaPtUnfoldBinByBin->DrawCopy("same");
        //histoESDConvGammaPtUnfoldSvD->DrawCopy("same");
        //histoESDConvGammaPtUnfoldTUnfold->DrawCopy("same");

    canvasCorrGammaSpecUnfold->SaveAs(Form("%s/%s_%s_CorrGammaUnfoldSpectrumPurityMinusSec_%s.%s",outputDir.Data(),textPi0New.Data(),textPrefix2.Data(),cutSelection.Data(),suffix.Data()));
    delete canvasCorrGammaSpecUnfold;

    //****************************************************************************************** 
    //****************************************************************************************** 
    //****************************************************************************************** 

    // copy raw inc gamma spectrum and correct for purity, conversion probability & reco effi ( vs rec pT without sec correction)
    TH1D* histoCorrGammaSpecPurity              = (TH1D*)histoESDConvGammaPt->Clone("CorrGammaSpecPurity");
    CorrectGammaDataPurity(histoCorrGammaSpecPurity,histoMCGammaPurity, histoMCGammaConvProb, histoGammaRecoEff, deltaEta, scaling, nEvt);
    DrawGammaSetMarker(histoCorrGammaSpecPurity, 20, 1.0, 1, 1);
    SetHistogramm(histoCorrGammaSpecPurity,"p_{T} (GeV/c)", "#frac{1}{2#pi N_{ev.}} #frac{d^{2}N}{p_{T}dp_{T}dy} (c/GeV)^{2}");

    // copy raw inc gamma spectrum and correct for secondary contamination, purity, conversion probability & reco effi (vs rec pt with sec correction)
    TH1D* histoCorrGammaSpecPurityMinusSec      = (TH1D*)histoESDConvGammaPt->Clone("CorrGammaSpecPurityMinusSec");
    CorrectGammaDataPurityMinusSec( histoCorrGammaSpecPurityMinusSec, histoSecondaryGammaSpecPt, histoSecondaryGammaFromXFromK0sSpecPt, 
                                    histoMCGammaTruePurity, histoMCGammaConvProb, histoGammaPrimaryRecoEff, deltaEta, scaling, nEvt);
    DrawGammaSetMarker(histoCorrGammaSpecPurityMinusSec, 20, 1.0, kGreen+2, kGreen+2);
    SetHistogramm(histoCorrGammaSpecPurityMinusSec,"p_{T} (GeV/c)", "#frac{1}{2#pi N_{ev.}} #frac{d^{2}N}{p_{T}dp_{T}dy} (c/GeV)^{2}");

    // Do same as before with secondary corrections applied
    TH1D* histoCorrGammaSpecPurityMinusSecPileUp;
    TH1D* histoCorrGammaSpecPurityMinusSecPileUpNoMCUpdate;
    if(doPileUpCorr){
        // copy raw inc gamma spectrum after pure data driven pileup correction, correct with pileup corrected secondary histograms, pileup corrected purity, conversion prob, reco effi 
        // (pileup corrected, vs rec pT with sec correction) all contain MC update of pileup correction
        histoCorrGammaSpecPurityMinusSecPileUp              = (TH1D*)histoESDConvGammaPtPileUp->Clone("CorrGammaSpecPurityMinusSecPileUp");
        CorrectGammaDataPurityMinusSec( histoCorrGammaSpecPurityMinusSecPileUp, histoSecondaryGammaSpecPtPileUp, histoSecondaryGammaFromXFromK0sSpecPtPileUp, 
                                        histoMCGammaTruePurityPileUp, histoMCGammaConvProb, histoGammaPrimaryRecoEffPileUp, deltaEta, scaling, nEvt);
        
        DrawGammaSetMarker(histoCorrGammaSpecPurityMinusSecPileUp, 20, 1.0, kMagenta, kMagenta);
        SetHistogramm(histoCorrGammaSpecPurityMinusSecPileUp,"p_{T} (GeV/c)", "#frac{1}{2#pi N_{ev.}} #frac{d^{2}N}{p_{T}dp_{T}dy} (c/GeV)^{2}");

        // copy raw inc gamma spectrum after pure data driven pileup correction, correct with pileup corrected secondary histograms, pileup corrected purity, conversion prob, reco effi 
        // (pileup corrected, vs rec pT with sec correction)
        histoCorrGammaSpecPurityMinusSecPileUpNoMCUpdate    = (TH1D*)histoESDConvGammaPtPileUp->Clone("CorrGammaSpecPurityMinusSecPileUpNoMCUpdate");
        CorrectGammaDataPurityMinusSec( histoCorrGammaSpecPurityMinusSecPileUpNoMCUpdate, histoSecondaryGammaSpecPt, histoSecondaryGammaFromXFromK0sSpecPt, 
                                        histoMCGammaTruePurity, histoMCGammaConvProb, histoGammaPrimaryRecoEff, deltaEta, scaling, nEvt);
        
        DrawGammaSetMarker(histoCorrGammaSpecPurityMinusSecPileUpNoMCUpdate, 20, 1.0, kBlue+2, kBlue+2);
        SetHistogramm(histoCorrGammaSpecPurityMinusSecPileUpNoMCUpdate,"p_{T} (GeV/c)", "#frac{1}{2#pi N_{ev.}} #frac{d^{2}N}{p_{T}dp_{T}dy} (c/GeV)^{2}");
        histoCorrGammaSpecPurityMinusSecPileUpNoMCUpdate->Draw("same");
    }


    // plotting different correction procedures for full spectrum
    TCanvas *canvasCorrGammaSpecPurity = GetAndSetCanvas("canvasCorrGammaSpecPurity");
    canvasCorrGammaSpecPurity->SetLogy();

        histoCorrGammaSpecPurity->Draw();
        histoCorrGammaSpecPurityMinusSec->Draw();
        histoCorrGammaSpecPurity->Draw("same");

        if(doPileUpCorr){
            histoCorrGammaSpecPurityMinusSecPileUp->Draw("same");
            histoCorrGammaSpecPurityMinusSecPileUpNoMCUpdate->Draw("same");
        }
    canvasCorrGammaSpecPurity->SaveAs(Form("%s/%s_%s_CorrGammaSpectrumPurityMinusSec_%s.%s",outputDir.Data(),textPi0New.Data(),textPrefix2.Data(),cutSelection.Data(),suffix.Data()));
    delete canvasCorrGammaSpecPurity;
    
    // copy raw inclusive gamma spectrum and correct for MC gamma Background, conversion prob, reco eff (vs. rec pT, without sec correction)
    TH1D *histoCorrGammaSpecBackground = (TH1D*) histoESDConvGammaPt->Clone("CorrGammaSpecBackground");
    CorrectGammaDataBackground(histoCorrGammaSpecBackground,histoGammaBackground, histoMCGammaConvProb, histoGammaRecoEff, deltaEta, scaling, nEvt);

    DrawGammaSetMarker(histoCorrGammaSpecBackground, 20, 1.0, 4, 1);
    SetHistogramm(histoCorrGammaSpecBackground,"p_{T} (GeV/c)", "#frac{1}{2#pi N_{ev.}} #frac{d^{2}N}{p_{T}dp_{T}dy} (c/GeV)^{2}");
 
    // plotting
    TCanvas *canvasCorrGammaSpecBackground = GetAndSetCanvas("canvasCorrGammaSpecBackground");
    canvasCorrGammaSpecBackground->SetLogy();

        histoCorrGammaSpecBackground->Draw();

    canvasCorrGammaSpecBackground->SaveAs(Form("%s/%s_%s_CorrGammaSpectrumBackground_%s.%s",outputDir.Data(),textPi0New.Data(),textPrefix2.Data(),cutSelection.Data(),suffix.Data()));
    
    // copy raw inclusive photon spectrum, correct for secondaries, MC BG, conversion probability, reco effi (vs rec pT, corrected for secondaries)
    TH1D *histoCorrGammaSpecBackgroundMinusSec  = (TH1D*) histoESDConvGammaPt->Clone("CorrGammaSpecBackgroundMinusSec");
    CorrectGammaDataBackgroundMinusSec(histoCorrGammaSpecBackgroundMinusSec, histoSecondaryGammaSpecPt, histoSecondaryGammaFromXFromK0sSpecPt, histoGammaBackground,
                                       histoMCGammaConvProb, histoGammaPrimaryRecoEff, deltaEta, scaling, nEvt);

    DrawGammaSetMarker(histoCorrGammaSpecBackgroundMinusSec, 20, 1.0, kOrange-3, kOrange-3);
    SetHistogramm(histoCorrGammaSpecBackgroundMinusSec,"p_{T} (GeV/c)", "#frac{1}{2#pi N_{ev.}} #frac{d^{2}N}{p_{T}dp_{T}dy} (c/GeV)^{2}");

    // plotting  
        histoCorrGammaSpecBackgroundMinusSec->Draw();
    canvasCorrGammaSpecBackground->SaveAs(Form("%s/%s_%s_CorrGammaSpectrumBackgroundMinusSec_%s.%s",outputDir.Data(),textPi0New.Data(),textPrefix2.Data(),cutSelection.Data(),suffix.Data()));
    delete canvasCorrGammaSpecBackground;

    //*************************************************************************************************    
    //********** Sanity check for photon spectrum (do we get back what we put in) *********************
    //*************************************************************************************************
    // correct input inc gamma spectrum for delta Eta, delta phi & number of events
    TH1D* histoGammaSpecMC                      = (TH1D*)histoAllGammaPt->Clone("GammaSpecMC");
    CorrectGammaMC(histoGammaSpecMC, deltaEta, scaling, nEvtMC);

    // correct reconstructed MC gamma photon spectrum with purity, conv prob, reco effi (vs rec pT)
    TH1D* histoGammaCorrESDMC               = (TH1D*) histoMCESDGamma->Clone("GammaSpecCorrESDMC");
    CorrectGammaDataPurity(histoGammaCorrESDMC, histoMCGammaPurity, histoMCGammaConvProb, histoGammaRecoEff, deltaEta, scaling, nEvtMC);

    // plotting
    TCanvas *canvasGammaSpecMC                  = GetAndSetCanvas("canvasGammaSpecMC");
    canvasGammaSpecMC->SetLogy();
        DrawGammaSetMarker(histoGammaSpecMC, 20, 1.0, 2, 2);
        SetHistogramm(histoGammaSpecMC,"p_{T} (GeV/c)", "#frac{1}{2#pi N_{ev.}} #frac{d^{2}N}{p_{T}dp_{T}dy} (c/GeV)^{2}");
        
        DrawGammaSetMarker(histoGammaCorrESDMC, 20, 1.0, 3, 3);
        SetHistogramm(histoGammaCorrESDMC, "p_{T} (GeV/c)", "#frac{1}{2#pi N_{ev.}} #frac{d^{2}N}{p_{T}dp_{T}dy} (c/GeV)^{2}");
        histoGammaCorrESDMC->Draw();
        histoGammaSpecMC->Draw("same");
    canvasGammaSpecMC->SaveAs(Form("%s/%s_GammaSpectrumMC_%s.%s",outputDir.Data(),textPi0New.Data(),cutSelection.Data(),suffix.Data()));

    
    //*************************************************************************************************
    //********************************* Comparison Gamma Spec *****************************************
    //*************************************************************************************************

    TH1D* histoRatioGammaCorrMinusSecGammaUnfold    = (TH1D*)histoCorrGammaSpecPurityMinusSec->Clone("histoRatioGammaCorrMinusSecGammaUnfold");
    histoRatioGammaCorrMinusSecGammaUnfold->Divide(histoESDConvGammaPtUnfold);
    TH1D* histoRatioGammaCorrMinusSecGammaPileUp;
    TH1D* histoRatioGammaCorrMinusSecGammaPileUpNoMCUpdate;
    if(doPileUpCorr){
        histoRatioGammaCorrMinusSecGammaPileUp           = (TH1D*)histoCorrGammaSpecPurityMinusSec->Clone("histoRatioGammaCorrMinusSecGammaPileUp");
        histoRatioGammaCorrMinusSecGammaPileUp->Divide(histoCorrGammaSpecPurityMinusSecPileUp);

        histoRatioGammaCorrMinusSecGammaPileUpNoMCUpdate = (TH1D*)histoCorrGammaSpecPurityMinusSec->Clone("histoRatioGammaCorrMinusSecGammaPileUp");
        histoRatioGammaCorrMinusSecGammaPileUpNoMCUpdate->Divide(histoCorrGammaSpecPurityMinusSecPileUpNoMCUpdate);
    }

    TH1D* histoRatioGammaCorrMinusSecGamma               = (TH1D*)histoCorrGammaSpecPurityMinusSec->Clone("histoRatioGammaCorrMinusSecGammaUnfold");
    histoRatioGammaCorrMinusSecGamma->Divide(histoCorrGammaSpecPurity);
    TH1D* histoRatioGammaCorrMinusSecGammaMC             = (TH1D*)histoCorrGammaSpecPurityMinusSec->Clone("histoRatioGammaCorrMinusSecGammaUnfold");
    histoRatioGammaCorrMinusSecGammaMC->Divide(histoGammaCorrESDMC);

    
    TCanvas *canvasGammaSpecComp                    = GetAndSetCanvas("canvasGammaSpecComp");
//     canvasGammaSpecComp->SetGridx();
//     canvasGammaSpecComp->SetGridy();
    
        SetHistogramm(histoRatioGammaCorrMinusSecGammaUnfold,"p_{T} (GeV/c)", "#gamma / gamma_{Mod}",0.8,1.3);
        DrawGammaSetMarker(histoRatioGammaCorrMinusSecGammaUnfold, 24, 1.0, 1, 1);
        histoRatioGammaCorrMinusSecGammaUnfold->DrawCopy();

        if(doPileUpCorr){
            SetHistogramm(histoRatioGammaCorrMinusSecGammaPileUp,"p_{T} (GeV/c)", "#gamma / gamma_{Mod}");
            DrawGammaSetMarker(histoRatioGammaCorrMinusSecGammaPileUp, 26, 1.0, 3, 3);
            SetHistogramm(histoRatioGammaCorrMinusSecGammaPileUpNoMCUpdate,"p_{T} (GeV/c)", "#gamma / gamma_{Mod}");
            DrawGammaSetMarker(histoRatioGammaCorrMinusSecGammaPileUpNoMCUpdate, 26, 1.0, kOrange, kOrange);
            histoRatioGammaCorrMinusSecGammaPileUp->DrawCopy("same");
            histoRatioGammaCorrMinusSecGammaPileUpNoMCUpdate->DrawCopy("same");
        }
        SetHistogramm(histoRatioGammaCorrMinusSecGamma,"p_{T} (GeV/c)", "#gamma / gamma_{Mod}");
        DrawGammaSetMarker(histoRatioGammaCorrMinusSecGamma, 20, 1.0, 6, 6);
        SetHistogramm(histoRatioGammaCorrMinusSecGammaMC,"p_{T} (GeV/c)", "#gamma / gamma_{Mod}");
        DrawGammaSetMarker(histoRatioGammaCorrMinusSecGammaMC, 21, 1.0, 8, 8);
        histoRatioGammaCorrMinusSecGamma->DrawCopy("same");
        histoRatioGammaCorrMinusSecGammaMC->DrawCopy("same");

        TLegend* legendGammaSpecComp                = GetAndSetLegend(0.4,0.25,5);
        legendGammaSpecComp->AddEntry(histoRatioGammaCorrMinusSecGammaUnfold,"Gamma Minus Sec - Unfold");
        if(doPileUpCorr)legendGammaSpecComp->AddEntry(histoRatioGammaCorrMinusSecGammaPileUp,"Gamma Minus Sec - Pile Up");
        legendGammaSpecComp->AddEntry(histoRatioGammaCorrMinusSecGamma,"Gamma Minus Sec - Without - Sec. Corr");
        legendGammaSpecComp->AddEntry(histoRatioGammaCorrMinusSecGammaMC,"Gamma Minus Sec - Without - MC Input");
        legendGammaSpecComp->Draw();

    canvasGammaSpecComp->SaveAs(Form("%s/%s_%s_GammaSpectraRatios_%s.%s",outputDir.Data(),textPi0New.Data(),textPrefix2.Data(),cutSelection.Data(),suffix.Data()));


    //*************************************************************************************************
    //********************************* Gamma from Decay **********************************************
    //*************************************************************************************************
    
    // correct input spectra of different decay channels with delta eta, delta phi & events number
    CorrectGammaMC(histoDecayPi0GammaPt, deltaEta, scaling, nEvtMC);
    DrawGammaSetMarker(histoDecayPi0GammaPt, 22, 1.0,kRed , kRed);
    SetHistogramm(histoDecayPi0GammaPt,"p_{T} (GeV/c)", "#frac{1}{2#pi N_{ev.}} #frac{d^{2}N}{p_{T}dp_{T}dy} (c/GeV)^{2}");
    CorrectGammaMC(histoDecayEtaGammaPt, deltaEta, scaling, nEvtMC);
    DrawGammaSetMarker(histoDecayEtaGammaPt, 22, 1.0, kBlue, kBlue);
    SetHistogramm(histoDecayEtaGammaPt,"p_{T} (GeV/c)","#frac{1}{2#pi N_{ev.}} #frac{d^{2}N}{p_{T}dp_{T}dy} (c/GeV)^{2}");
    CorrectGammaMC(histoDecayEtapGammaPt, deltaEta, scaling, nEvtMC);
    DrawGammaSetMarker(histoDecayEtapGammaPt, 22, 1.0, kOrange+1, kOrange+1);
    SetHistogramm(histoDecayEtapGammaPt,"p_{T} (GeV/c)", "#frac{1}{2#pi N_{ev.}} #frac{d^{2}N}{p_{T}dp_{T}dy} (c/GeV)^{2}");
    CorrectGammaMC(histoDecayOmegaGammaPt, deltaEta, scaling, nEvtMC);
    DrawGammaSetMarker(histoDecayOmegaGammaPt, 22, 1.0, kYellow+2, kYellow+2);
    SetHistogramm(histoDecayOmegaGammaPt,"p_{T} (GeV/c)", "#frac{1}{2#pi N_{ev.}} #frac{d^{2}N}{p_{T}dp_{T}dy} (c/GeV)^{2}");
    CorrectGammaMC(histoDecayRho0GammaPt, deltaEta, scaling, nEvtMC);
    DrawGammaSetMarker(histoDecayRho0GammaPt, 22, 1.0, kAzure-2, kAzure-2);
    SetHistogramm(histoDecayRho0GammaPt,"p_{T} (GeV/c)", "#frac{1}{2#pi N_{ev.}} #frac{d^{2}N}{p_{T}dp_{T}dy} (c/GeV)^{2}");
    CorrectGammaMC(histoDecayPhiGammaPt, deltaEta, scaling, nEvtMC);
    DrawGammaSetMarker(histoDecayPhiGammaPt, 22, 1.0, kViolet, kViolet);
    SetHistogramm(histoDecayPhiGammaPt,"p_{T} (GeV/c)", "#frac{1}{2#pi N_{ev.}} #frac{d^{2}N}{p_{T}dp_{T}dy} (c/GeV)^{2}");

    // compute total decay spectrum
    TH1D *histoMCDecaySumGammaPt    = (TH1D*)histoDecayPi0GammaPt->Clone("MC_DecaySumGammaPt");
    histoMCDecaySumGammaPt->Add(histoDecayEtaGammaPt);
    histoMCDecaySumGammaPt->Add(histoDecayEtapGammaPt);
    histoMCDecaySumGammaPt->Add(histoDecayOmegaGammaPt);
    histoMCDecaySumGammaPt->Add(histoDecayRho0GammaPt);
    histoMCDecaySumGammaPt->Add(histoDecayPhiGammaPt);
    DrawGammaSetMarker(histoMCDecaySumGammaPt, 22, 1.0, kGreen+1,  kGreen+1);
    SetHistogramm(histoMCDecaySumGammaPt,"p_{T} (GeV/c)", "#frac{1}{2#pi N_{ev.}} #frac{d^{2}N}{p_{T}dp_{T}dy} (c/GeV)^{2}",1e-10, 20.);

    // compute direct photon spectrum
    TH1D* histMCAllMinusDecay       = (TH1D*)histoAllGammaOriginalBinPt->Clone("MC_Direct_or_All_Minus_Decay");
    CorrectGammaMC(histMCAllMinusDecay, deltaEta, scaling, nEvtMC);
    DrawGammaSetMarker(histMCAllMinusDecay, 4, 1.0, 1, 1);
    histMCAllMinusDecay->Add(histoMCDecaySumGammaPt,-1);
    SetHistogramm(histMCAllMinusDecay,"p_{T} (GeV/c)", "#frac{1}{2#pi N_{ev.}} #frac{d^{2}N}{p_{T}dp_{T}dy} (c/GeV)^{2}",1e-10, 20.);
    
    
    TCanvas *canvasDecayGammaSpecMC = GetAndSetCanvas("canvasDecayGammaSpecMC");

        canvasDecayGammaSpecMC->SetLogy();
        histoMCDecaySumGammaPt->DrawCopy("chist");
        histoDecayPi0GammaPt->DrawCopy("chist,same");
        histoDecayEtaGammaPt->DrawCopy("chist,same");
        histoDecayEtapGammaPt->DrawCopy("chist,same");
        histoDecayOmegaGammaPt->DrawCopy("chist,same");
        histoDecayRho0GammaPt->DrawCopy("chist,same");
        histoDecayPhiGammaPt->DrawCopy("chist,same");
        histMCAllMinusDecay->DrawCopy("chist,same");
        histoGammaSpecMC->DrawCopy("same");
        TLegend* legendDecaySpectra = GetAndSetLegend(0.4,0.65,8);
        legendDecaySpectra->AddEntry(histoMCDecaySumGammaPt,"Sum");
        legendDecaySpectra->AddEntry(histoDecayPi0GammaPt,"#gamma from #pi^{0}");
        legendDecaySpectra->AddEntry(histoDecayEtaGammaPt,"#gamma from #eta");
        legendDecaySpectra->AddEntry(histoDecayEtapGammaPt,"#gamma from #eta'");
        legendDecaySpectra->AddEntry(histoDecayOmegaGammaPt,"#gamma from #omega");
        legendDecaySpectra->AddEntry(histoDecayRho0GammaPt,"#gamma from #rho^{0}");
        legendDecaySpectra->AddEntry(histoDecayPhiGammaPt,"#gamma from #phi");
        legendDecaySpectra->AddEntry(histMCAllMinusDecay,"All #gamma minus sum decay");
        legendDecaySpectra->Draw();

    canvasDecayGammaSpecMC->SaveAs(Form("%s/%s_DecayGammaSpectrumMC_%s.%s",outputDir.Data(),textPi0New.Data(),cutSelection.Data(),suffix.Data()));


    
    //*************************************************************************************************
    //******************************* Gamma Combinatorial Background **********************************
    //*************************************************************************************************
    // pure BG plotting
    TCanvas *canvasCombBackSpecMC = GetAndSetCanvas("canvasCombBackSpecMC");
    canvasCombBackSpecMC->SetLogy();

        TLegend* legendCombSpectra = GetAndSetLegend(0.4,0.55,8,2);
        legendCombSpectra->SetNColumns(2);

        for(Int_t i = 0;i<17;i++){
            DrawGammaSetMarker(histoCombinatorialSpeciesPt[i], 22, 1.0, i+1, i+1);
            SetHistogramm(histoCombinatorialSpeciesPt[i],"p_{T} (GeV/c)", "#frac{1}{2#pi N_{ev.}} #frac{d^{2}N}{p_{T}dp_{T}dy} (c/GeV)^{2}");
            histoCombinatorialSpeciesPt[i]->Scale(1./nEvtMC);

            if(i==0) histoCombinatorialSpeciesPt[i]->DrawCopy("");
            else histoCombinatorialSpeciesPt[i]->DrawCopy("same");

            legendCombSpectra->AddEntry(histoCombinatorialSpeciesPt[i],combinatorics[i]);
        }

        legendCombSpectra->Draw();

    canvasCombBackSpecMC->SaveAs(Form("%s/%s_CombBackSpectrumMC_%s.%s",outputDir.Data(),textPi0New.Data(),cutSelection.Data(),suffix.Data()));
    delete canvasCombBackSpecMC;

    // plot ratio to real primary photons
    TCanvas *canvasSignalToCombBackgroundRatio = GetAndSetCanvas("canvasSignalToCombBackgroundRatio");
    canvasSignalToCombBackgroundRatio->SetLogy();

        TLegend* legendSignalToCombBackgroundRatio = GetAndSetLegend(0.15,0.66,6,3);
        
        Int_t colors[11]        = {kPink,kRed+1,kOrange+7,kMagenta+2,kRed-9,kAzure-1,kAzure+5,kBlue-6,kCyan-3,kGreen-3,kSpring+9};
        Int_t markers[11]       = {20,21,24,25,27,28,29,30,33,34,20};

        TH1D **histoSignalToCombBackgroundRatio = new TH1D*[17];
        TH1D *SummedSmallContributionsCombBack; //10,11,12,13,14,15
        
        for(Int_t i = 0;i<16;i++){
            histoSignalToCombBackgroundRatio[i] = (TH1D*) histoCombinatorialSpeciesPt[i]->Clone(Form("ESD_TrueCombRatioSignal_%s_Pt",combinatorics[i].Data()));
            histoSignalToCombBackgroundRatio[i]->Scale(nEvtMC);
            
            if(i==9){
                SummedSmallContributionsCombBack = (TH1D*)histoSignalToCombBackgroundRatio[i]->Clone("SummedSmallContributions");
                SetHistogramm(SummedSmallContributionsCombBack,"p_{T} (GeV/c)","SummedSmallContributions",10,5e7);
                SummedSmallContributionsCombBack->SetMinimum(1e-5);
            }
            
            if(i>9){
                SummedSmallContributionsCombBack->Add(histoSignalToCombBackgroundRatio[i]);
            }
            histoSignalToCombBackgroundRatio[i]->Divide(histoSignalToCombBackgroundRatio[i],histoGammaESDTruePrimaryConvPt,1,1,"");
            SetHistogramm(histoSignalToCombBackgroundRatio[i],"p_{T} (GeV/c)",combinatorics[i],10,5e7);
            histoSignalToCombBackgroundRatio[i]->SetMinimum(1e-5);
            
            if(i==0){
                histoSignalToCombBackgroundRatio[i]->GetYaxis()->SetRangeUser(1e-5,100);
                histoSignalToCombBackgroundRatio[i]->DrawCopy("e1");
            }
            if(i<9){
                histoSignalToCombBackgroundRatio[i]->SetMarkerStyle(markers[i]);
                histoSignalToCombBackgroundRatio[i]->SetMarkerColor(colors[i]);
                histoSignalToCombBackgroundRatio[i]->SetLineColor(colors[i]);
                histoSignalToCombBackgroundRatio[i]->DrawCopy("e1same");
            }
            else continue;
            
            legendSignalToCombBackgroundRatio->AddEntry(histoSignalToCombBackgroundRatio[i],combinatorics[i]);
        }

        SummedSmallContributionsCombBack->Divide(SummedSmallContributionsCombBack,histoGammaESDTruePrimaryConvPt,1,1,"");
        SummedSmallContributionsCombBack->SetMarkerStyle(markers[10]);
        SummedSmallContributionsCombBack->SetMarkerColor(colors[10]);
        SummedSmallContributionsCombBack->SetLineColor(colors[10]);
        SummedSmallContributionsCombBack->DrawCopy("e1same");
        legendSignalToCombBackgroundRatio->AddEntry(SummedSmallContributionsCombBack,"Protos+Kaons+Muons");
        legendSignalToCombBackgroundRatio->Draw();
        
    canvasSignalToCombBackgroundRatio->SaveAs(Form("%s/%s_CombBackgroundRatioToSignal_%s.%s",outputDir.Data(),textPi0New.Data(),cutSelection.Data(),suffix.Data()));
    delete canvasSignalToCombBackgroundRatio;

    // plot ratio to summed total MC BG
    TCanvas *canvasRatioCombBackToBack = GetAndSetCanvas("canvasRatioCombBackToBack");
    canvasRatioCombBackToBack->SetLogy();

        TLegend* legendRatioCombBackToBack = GetAndSetLegend(0.15,0.65,6,3);
        
        TH1D **histoRatioCombBackToBack = new TH1D*[17];
        TH1D *SummedSmallContributionsCombBackToBack; //10,11,12,13,14,15
        for(Int_t i = 0;i<16;i++){

            histoRatioCombBackToBack[i] = (TH1D*) histoCombinatorialSpeciesPt[i]->Clone(Form("ESD_TrueCombRatioSignal_%s_Pt",combinatorics[i].Data()));
            
            if(i==9){
                SummedSmallContributionsCombBackToBack = (TH1D*)histoRatioCombBackToBack[i]->Clone("SummedSmallContributions");
                SetHistogramm(SummedSmallContributionsCombBackToBack,"p_{T} (GeV/c)","SummedSmallContributions",10,5e7);
                SummedSmallContributionsCombBackToBack->SetMinimum(1e-5);
            }
            
            if(i>9){
                SummedSmallContributionsCombBackToBack->Add(histoRatioCombBackToBack[i]);
            }
            histoRatioCombBackToBack[i]->Divide(histoRatioCombBackToBack[i],histoGammaMCBackground,1,1,"");
            SetHistogramm(histoRatioCombBackToBack[i],"p_{T} (GeV/c)",combinatorics[i],10,5e7);
            histoRatioCombBackToBack[i]->SetMinimum(1e-5);
            
            if(i==0){
                histoRatioCombBackToBack[i]->GetYaxis()->SetRangeUser(1e-4,400);
                histoRatioCombBackToBack[i]->DrawCopy("e1");
            }
            if(i<9){
                histoRatioCombBackToBack[i]->SetMarkerStyle(markers[i]);
                histoRatioCombBackToBack[i]->SetMarkerColor(colors[i]);
                histoRatioCombBackToBack[i]->SetLineColor(colors[i]);
                histoRatioCombBackToBack[i]->DrawCopy("e1same");
            }
            else continue;
            
            legendRatioCombBackToBack->AddEntry(histoRatioCombBackToBack[i],combinatorics[i]);
        }
        
        SummedSmallContributionsCombBackToBack->Divide(SummedSmallContributionsCombBackToBack,histoGammaMCBackground,1,1,"");
        SummedSmallContributionsCombBackToBack->SetMarkerStyle(markers[10]);
        SummedSmallContributionsCombBackToBack->SetMarkerColor(colors[10]);
        SummedSmallContributionsCombBackToBack->SetLineColor(colors[10]);
        SummedSmallContributionsCombBackToBack->DrawCopy("e1same");
        legendRatioCombBackToBack->AddEntry(SummedSmallContributionsCombBackToBack,"Protos+Kaons+Muons");
        legendRatioCombBackToBack->Draw();
    
    canvasRatioCombBackToBack->SaveAs(Form("%s/%s_RatioCombBackToBack_%s.%s",outputDir.Data(),textPi0New.Data(),cutSelection.Data(),suffix.Data()));
    delete canvasRatioCombBackToBack;

    //*************************************************************************************************
    //**************** Calculate Purity for non combinatorial BG **************************************
    //*************************************************************************************************

    histoMCESDGamma->Scale(1/nEvtMC);
    histoGammaESDTrueConvPt->Scale(1/nEvtMC);
    
    // calculation of purity without combinatorial BG
    // Step 1: get reconstructed photon candidates MC
    // Step 2: subtract all combinatorics
    // Step 3: divide reco photons (true) by above constructed histo
    TH1D *histoPurityWOCombBG   = (TH1D*)histoMCESDGamma->Clone("histoPurityWOCombBG");
    histoPurityWOCombBG->Add(histoCombinatorialSpeciesPt[16],-1);// Signal plus Not Comb Back
    histoPurityWOCombBG->Divide(histoGammaESDTrueConvPt,histoPurityWOCombBG,1,1,"B");
    
    // calculation of BG without combinatorial
    // Step 1: copy total BG
    // Step 2: subtract all combinatorics
    TH1D *histoNotCombBG        = (TH1D*)histoGammaMCBackground->Clone("histoPurityCombOnlyBG");
    histoNotCombBG->Add(histoCombinatorialSpeciesPt[16],-1);
    
    // calculation of summed purity 
    // Step 1: copy all combinatorics
    // Step 2: add non combinatorical BG
    // Step 3: divide reconstructed photons by above constructed histo
    TH1D* histoSummedPurity = (TH1D*)histoCombinatorialSpeciesPt[16]->Clone("histoSummedPurity");
    histoSummedPurity->Add(histoNotCombBG);
    histoSummedPurity->Add(histoGammaESDTrueConvPt);
    histoSummedPurity->Divide(histoGammaESDTrueConvPt,histoSummedPurity,1,1,"B");
    
    
    // calculation of combinatorial BG only purity
    // Step 1: copy MC reco Gammas
    // Step 2: remove non comb BG
    // Step 3: divide reco photons by above constructed histo
    TH1D *histoPurityCombOnlyBG  = (TH1D*)histoMCESDGamma->Clone("histoPurityCombOnlyBG");
    histoPurityCombOnlyBG->Add(histoNotCombBG,-1);
    histoPurityCombOnlyBG->Divide(histoGammaESDTrueConvPt,histoPurityCombOnlyBG,1,1,"B");
    
    
    

    
    TCanvas *canvasPurityFromNotCombinatorial   = GetAndSetCanvas("canvasPurityFromNotCombinatorial");
//     canvasPurityFromNotCombinatorial->SetGridx();
//     canvasPurityFromNotCombinatorial->SetGridy();
        TLegend* legendPurityAdvanced           = GetAndSetLegend(0.2,0.2,3);
        SetHistogramm(histoPurityWOCombBG,"p_{T} (GeV/c)","Purity",0.6,1.1);
        SetHistogramm(histoPurityCombOnlyBG,"p_{T} (GeV/c)","",0.6,1.1);
        SetHistogramm(histoSummedPurity,"p_{T} (GeV/c)","Purity",0.6,1.1);
        DrawGammaSetMarker(histoPurityWOCombBG, 20, 1.0, kBlue+2,  kBlue+2);
        DrawGammaSetMarker(histoPurityCombOnlyBG, 20, 1.0, kRed+2,  kRed+2);
        DrawGammaSetMarker(histoSummedPurity, 20, 1.0, kGreen+2,  kGreen+2);
        histoPurityWOCombBG->DrawCopy();
        histoPurityCombOnlyBG->DrawCopy("same");
        histoMCGammaPurity->DrawCopy("same");
        //histoSummedPurity->DrawCopy("same");
        legendPurityAdvanced->AddEntry(histoMCGammaPurity,"Standard Purity");
        legendPurityAdvanced->AddEntry(histoPurityCombOnlyBG,"Purity Same Mother Background Excluded");
        legendPurityAdvanced->AddEntry(histoPurityWOCombBG,"Purity Combinatorial Background Excluded");
        legendPurityAdvanced->Draw();
    canvasPurityFromNotCombinatorial->SaveAs(Form("%s/%s_PurityCombinatorialHadronic_%s.%s",outputDir.Data(),textPi0New.Data(),cutSelection.Data(),suffix.Data()));
    delete canvasPurityFromNotCombinatorial;
    
    //*************************************************************************************************
    //*********************** Compare Gamma Yields MC/Reconstructed *************************************
    //*************************************************************************************************
    TCanvas *canvasPurBackGammaSpec = GetAndSetCanvas("canvasPurBackGammaSpec");
    DrawGammaCanvasSettings( canvasPurBackGammaSpec, 0.1, 0.015, 0.02, 0.09);
        TPad *padPurBackSpec = new TPad("padNLOHistos", "", 0., 0.25, 1., 1.,-1, -1, -2);
        DrawGammaPadSettings( padPurBackSpec, 0.10, 0.015, 0.02, 0.);
        padPurBackSpec->Draw();
        TPad *padPurBackRatio = new TPad("padNLORatios", "", 0., 0., 1., 0.25,-1, -1, -2);
        DrawGammaPadSettings( padPurBackRatio, 0.1, 0.015, 0.0, 0.35);
        padPurBackRatio->Draw();

        padPurBackSpec->cd();
        padPurBackSpec->SetLogy();

        DrawGammaSetMarker(histoCorrGammaSpecPurityMinusSec, 20, 1.0, kBlue+2,  kBlue+2);
        DrawGammaSetMarker(histoCorrGammaSpecPurity, 4, 1.0, kMagenta,  kMagenta);
        DrawGammaSetMarker(histoCorrGammaSpecBackgroundMinusSec, 32, 1.0, kRed+1,  kRed+1);
        DrawGammaSetMarker(histoCorrGammaSpecBackground, 26, 1.0, kAzure+7,  kAzure+7);
        DrawGammaSetMarker(histoESDConvGammaPtUnfold, 26, 1.0, kAzure+7,  kAzure+7);

        histoCorrGammaSpecPurityMinusSec->DrawCopy("e1");
        histoCorrGammaSpecPurity->DrawCopy("e1,same");
        histoESDConvGammaPtUnfold->DrawCopy("e1,same");
        
        TLegend* legendPurBackSpectra = GetAndSetLegend(0.5,0.85,3);
        legendPurBackSpectra->AddEntry(histoCorrGammaSpecPurityMinusSec,"#gamma with Purity and corrected for Secondaries","p");
        legendPurBackSpectra->AddEntry(histoCorrGammaSpecPurity,"#gamma with Purity without Secondary correction","p");
        legendPurBackSpectra->AddEntry(histoESDConvGammaPtUnfold,"#gamma unfolded with Secondary correction","p");
        legendPurBackSpectra->Draw();
        
        padPurBackRatio->cd();
        TH1D *histGammaRatioMinusSec = (TH1D*) histoCorrGammaSpecPurityMinusSec->Clone("histGammaRatioMinusSec");
        histGammaRatioMinusSec->Divide(histGammaRatioMinusSec,histoCorrGammaSpecPurity,1,1,"");
        TH1D *histGammaRatioUnfoldMinusSec = (TH1D*) histoCorrGammaSpecPurityMinusSec->Clone("histGammaRatioMinusSec");
        histGammaRatioUnfoldMinusSec->Divide(histGammaRatioUnfoldMinusSec,histoESDConvGammaPtUnfold,1,1,"");
        SetHistogramm(histGammaRatioMinusSec,"p_{T} (GeV/c)", "#frac{#gamma Secondary Corrected}{#gamma Purity}",0.8,1.1);
        histGammaRatioMinusSec->GetYaxis()->SetTitleSize(0.1);
        histGammaRatioMinusSec->GetYaxis()->SetTitleOffset(0.4);
        histGammaRatioMinusSec->GetYaxis()->CenterTitle(kTRUE);
        histGammaRatioMinusSec->GetYaxis()->SetNdivisions(5);
        
        DrawGammaSetMarker(histGammaRatioUnfoldMinusSec, 26, 1.0, kRed-7,  kRed-7);
        DrawGammaSetMarker(histGammaRatioMinusSec, 4, 1.0, kBlue-7,  kBlue-7);
        histGammaRatioMinusSec->DrawCopy("e1");
        histGammaRatioUnfoldMinusSec->DrawCopy("same");
        
        DrawGammaLines(0., maxPtGamma,1, 1,0.5);
    
    canvasPurBackGammaSpec->SaveAs(Form("%s/%s_%s_GammaSpectraComparison_%s.%s",outputDir.Data(),textPi0New.Data(),textPrefix2.Data(),cutSelection.Data(),suffix.Data()));
    delete canvasPurBackGammaSpec;
    
    TCanvas *canvasCompGamma = GetAndSetCanvas("canvasCompGamma");
        TH1D *histoCompareGammaPurity = (TH1D*) histoGammaSpecMC->Clone("CompareGama_MCtoRecPurity");
        TH1D *histoCompareGammaBackground = (TH1D*) histoGammaSpecMC->Clone("CompareGama_MCtoRecBack");
        DrawGammaSetMarker(histoCompareGammaPurity, 22, 1.0, 1, 1);
        DrawGammaSetMarker(histoCompareGammaBackground, 22, 1.0, 2, 1);

        histoCompareGammaPurity->Divide(histoCompareGammaPurity,histoCorrGammaSpecPurity,1,1,"B");
        histoCompareGammaBackground->Divide(histoCompareGammaBackground,histoCorrGammaSpecBackground,1,1,"B");

        SetHistogramm(histoCompareGammaPurity,"p_{T} (GeV/c)", Form("Ratio #gamma from MC / Reconstructed #gamma (%s)",textPrefix2.Data()),0., 2.);
        SetHistogramm(histoCompareGammaBackground,"p_{T} (GeV/c)", Form("Ratio #gamma from MC / Reconstructed #gamma (%s)",textPrefix2.Data()),0., 2.);

        TH1D *CompareBackgroundPurity = (TH1D*)histoCorrGammaSpecPurity->Clone("CompareBackgroundPurity");
        CompareBackgroundPurity->Divide(CompareBackgroundPurity,histoCorrGammaSpecBackground,1,1,"B");
        CompareBackgroundPurity->SetMarkerStyle(4);

        histoCompareGammaPurity->DrawCopy("e1");
        histoCompareGammaBackground->DrawCopy("e1,same");
        CompareBackgroundPurity->DrawCopy("e1,same");

        TLegend* legendCompareGamma = GetAndSetLegend(0.2,0.7,3,1,"Comparison of Gamma Spectra");
        legendCompareGamma->AddEntry(histoCompareGammaPurity,"MC #gamma / Corr #gamma Purity");
        legendCompareGamma->AddEntry(histoCompareGammaBackground,"MC #gamma / Corr #gamma Background");
        legendCompareGamma->AddEntry(CompareBackgroundPurity,"Corr #gamma Purity / Corr #gamma Background");
        legendCompareGamma->Draw();

    canvasCompGamma->SaveAs(Form("%s/%s_%s_ComparisonGammaSpec_%s.%s",outputDir.Data(),textPi0New.Data(),textPrefix2.Data(),cutSelection.Data(),suffix.Data()));
    delete canvasCompGamma;
    
    
    CorrectGammaMC(histoGammaMCConvPt, deltaEta, scaling, nEvtMC);
    CorrectGammaMC(histoGammaESDTrueConvPt, deltaEta, scaling, nEvtMC);

    TCanvas *canvasGammaMCconvAndTrueConv = GetAndSetCanvas("canvasGammaMCconvAndTrueConv");
    canvasGammaMCconvAndTrueConv->SetLogy();
    
        SetHistogramm(histoGammaMCConvPt,"p_{T} (GeV/c)","#frac{1}{2#pi N_{ev.}} #frac{d^{2}N}{p_{T}dp_{T}dy} (c/GeV)^{2}");
        SetHistogramm(histoGammaESDTrueConvPt,"p_{T} (GeV/c)","#frac{1}{2#pi N_{ev.}} #frac{d^{2}N}{p_{T}dp_{T}dy} (c/GeV)^{2}");
        
        histoGammaMCConvPt->Draw();
        // histoGammaESDTrueConvPt->Draw("same");

        canvasGammaMCconvAndTrueConv->SaveAs(Form("%s/%s_%s_ComparisonMCConvAndTrueConvGammaSpec_%s.%s",outputDir.Data(),textPi0New.Data(),textPrefix2.Data(),cutSelection.Data(),suffix.Data()));


        TCanvas *canvasGammaPurityConvBin = GetAndSetCanvas("canvasGammaPurityConvBin");
        canvasGammaPurityConvBin->SetLogy();

        DrawGammaSetMarker(histoCorrGammaSpecPurityMinusSec, 24, 1.0, 1, 1);
        DrawGammaSetMarker(histoCorrGammaSpecBackgroundMinusSec, 3, 1.0, kGreen+2, kGreen+2);
        
        histoGammaSpecMC->GetYaxis()->SetRangeUser(5e-10,100);
        histoGammaSpecMC->DrawCopy("e1");
        histoESDConvGammaPtUnfold->SetMarkerColor(1);
        histoESDConvGammaPtUnfold->SetLineColor(1);
        histoESDConvGammaPtUnfold->DrawCopy("e1,same");
        TLegend *legendGammaSpectraConvBin = GetAndSetLegend(0.45,0.6,2);
        legendGammaSpectraConvBin->AddEntry(histoESDConvGammaPtUnfold,"corrected data #gamma spectrum");
        if( option.CompareTo("PbPb_2.76TeV") == 0) legendGammaSpectraConvBin->AddEntry(histoGammaCorrESDMC,"Hijing #gamma spectrum");
        else legendGammaSpectraConvBin->AddEntry(histoGammaSpecMC,"MC #gamma spectrum");
        legendGammaSpectraConvBin->Draw();

//         DrawAliceLogoAdv(0.82,0.7,"Work in Progress",option,"l",canvasGammaPurityConvBin,centrality);
    
    canvasGammaPurityConvBin->SaveAs(Form("%s/%s_%s_GammaSpec_%s.%s",outputDir.Data(),textPi0New.Data(),textPrefix2.Data(),cutSelection.Data(),suffix.Data()));
    delete canvasGammaPurityConvBin;
    
    //***********************************************************************************************************
    //******************************* Write output file for photons *********************************************
    //***********************************************************************************************************
    TString nameOutput = Form("%s/%s/%s_%s_GammaConvV1Correction_%s.root",cutSelection.Data(),option.Data(),textPi0New.Data(),textPrefix2.Data(),cutSelection.Data());
    TFile* fileCorrectedOutput = new TFile(nameOutput,"RECREATE");
        for(Int_t i = 0;i<17;i++)
            histoCombinatorialSpeciesPt[i]->Write();

        histoCorrGammaSpecPurity->Write();
        histoCorrGammaSpecPurityMinusSec->Write();
        histoCorrGammaSpecBackground->Write();
        histoCorrGammaSpecBackgroundMinusSec->Write();
        if(doPileUpCorr){
            histoCorrGammaSpecPurityMinusSecPileUp->Write();
            histoCorrGammaSpecPurityMinusSecPileUpNoMCUpdate->Write();
            histoESDConvGammaPtUnfoldPileUp->Write("GammaUnfoldPileUp");
        }
        histoGammaSpecMC->Write();
        histoGammaCorrESDMC->Write();
        histoCompareGammaPurity->Write();
        histoCompareGammaBackground->Write();
        histoMCDecaySumGammaPt->Write();
        histoDecayPi0GammaPt->Write();
        histoDecayEtaGammaPt->Write();
        histoDecayEtapGammaPt->Write();
        histoDecayOmegaGammaPt->Write();
        histoDecayRho0GammaPt->Write();
        histoDecayPhiGammaPt->Write();
        histoGammaBackground->Write();
        histMCAllMinusDecay->Write();
        histoGammaESDTrueConvPt->Write();
        histoGammaMCConvPt->Write();

        ScalingGammaBackground->Write();
        histoMCESDGamma->Write();
        histoMCGammaPurity->Write();
        histoMCGammaTruePurity->Write();
        histoGammaRecoEff->Write();
        histoGammaPrimaryRecoEff->Write();
        histoGammaPrimaryRecoEffMCPt->Write();
        RawGammaSpectrum->Write();
        histoESDConvGammaPtUnfold->Write("GammaUnfold");
        
    fileCorrectedOutput->Close();

}

