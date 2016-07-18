// provided by Gamma Conversion Group, $ALICE_ROOT/PWG4/GammaConv ;https://twiki.cern.ch/twiki/bin/view/ALICE/PWG4GammaConversion

//This file is not supposed to be run on outputfiles of the GammaConv-Software before the 30th Sept 2010.


#include <stdlib.h>
#include <iostream>
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
#include "TCanvas.h"
#include "TGraph.h"
#include "TGraphErrors.h"
#include "TGraphAsymmErrors.h"
#include "TLegend.h"
#include "TMath.h"
#include "TLatex.h"
#include "TASImage.h"
#include "TArrow.h"
#include "TMarker.h"
#include "TDatabasePDG.h"
#include "TTree.h"
#include "../CommonHeaders/PlottingMeson.h"
#include "../CommonHeaders/PlottingGammaConversionHistos.h"
#include "../CommonHeaders/PlottingGammaConversionAdditional.h"
#include "../CommonHeaders/ExtractSignalBinning.h"
#include "../CommonHeaders/FittingGammaConversion.h"
//#include "../CommonHeaders/ConversionFunctionsBasicsAndLabeling.h"
#include "../CommonHeaders/ConversionFunctions.h"
#include "ExtractGammaSignal.h"


// Main Function
void ExtractGammaSignal(    TString meson               = "", 
                            TString file                = "", 
                            TString cutSelection        = "", 
                            TString Suffix              = "", 
                            TString isMC                = "", 
                            TString option              = "", 
                            TString crystal             = "", 
                            TString directphotonPlots   = "",
                            TString multFlag            = "",
                            TString period              = "", 
                            TString thesis              = "",
                            Int_t numberOfBins          = 30, 
                            Bool_t addSig               = kFALSE, 
                            Int_t mode                  = 9) {

   // Avoiding Warnings
   if(multFlag){};
   if(thesis){};
   if(crystal){};

   StyleSettingsThesis();
   SetPlotStyle();

   fdate = ReturnDateString();

   fOutputDir = Form("%s/%s/%s/ExtractGammaSignal",cutSelection.Data(),option.Data(),Suffix.Data());
   gSystem->Exec("mkdir -p "+fOutputDir);

   cout<<"Pictures are saved as "<< Suffix.Data()<< endl;
   fdate = ReturnDateString();
   fdirectphoton = directphotonPlots;
   fEnergyFlag = option;
   fPrefix = meson;
   fPeriodFlag = period;
   fSuffix = Suffix;
   fmeson = meson;
   //***************************** Specification Data/MC ************************************************************
   if(isMC.CompareTo("kTRUE") == 0){
      fIsMC = 1;
      fPrefix2 = "MC";
   } else {
      fIsMC = 0;
      fPrefix2 = "data";
   }

   //************************* Start of Main routine ***************************************************************

   TFile f(file.Data());

   TString nameMainDir = "";
   if (mode == 9 || mode == 0) nameMainDir = "GammaConvV1";
   else if (mode == 2 || mode == 3) nameMainDir = "GammaConvCalo";
   else if (mode == 4 || mode == 5) nameMainDir = "GammaCalo";

   TList *TopDir =(TList*)f.Get(nameMainDir.Data());
   if(TopDir == NULL){
       cout<<"ERROR: TopDir not Found"<<endl;
       return;
   }

   	TString eventCutNumber="";
	TString gammaCutNumber="";
	TString clusterCutNumber="";
	TString electronCutNumber="";
	TString mesonCutNumber="";
	
	fCutSelection = cutSelection;
	TString cutSelectionRead = cutSelection;
	if (mode == 9){
		ReturnSeparatedCutNumber(cutSelection, gammaCutNumber, electronCutNumber,mesonCutNumber);
		eventCutNumber = gammaCutNumber(0,7);
		gammaCutNumber = gammaCutNumber(7,gammaCutNumber.Length()-7);
		cout << eventCutNumber.Data() << "\t" << gammaCutNumber.Data() << endl;
	} else {
		ReturnSeparatedCutNumberAdvanced(cutSelection,eventCutNumber, gammaCutNumber, clusterCutNumber, electronCutNumber, mesonCutNumber, mode);
	}
	
	TString eventCutSelectionRead = eventCutNumber.Data();
	TString gammaCutSelectionRead = gammaCutNumber.Data();
	TString mesonCutSelectionRead = mesonCutNumber.Data();
	if (addSig) {
		cout << "running added Signal" << endl;
		cout << eventCutNumber.Data() << endl;
		eventCutNumber.Replace(GetEventRejectExtraSignalsCutPosition(),1,"2");
		cout << eventCutNumber.Data() << endl;
		eventCutSelectionRead = eventCutNumber;
		gammaCutSelectionRead = gammaCutNumber;
		mesonCutSelectionRead = mesonCutNumber;
		if (mode==9)cutSelectionRead = Form("%s%s_%s", eventCutNumber.Data(), gammaCutNumber.Data(), mesonCutNumber.Data());
		else if (mode==0) cutSelectionRead = Form("%s_%s_%s",eventCutNumber.Data(), gammaCutNumber.Data(), mesonCutNumber.Data());
		cout << cutSelectionRead.Data() << endl;
	}

   
   TList *HistosGammaConversion = (TList*)TopDir->FindObject(Form("Cut Number %s",cutSelectionRead.Data()));
   TList *ESDContainer = (TList*) HistosGammaConversion->FindObject(Form("%s ESD histograms",cutSelectionRead.Data()));
   TList *ConvCutsContainer = (TList*) HistosGammaConversion->FindObject(Form("ConvCuts_%s",gammaCutSelectionRead.Data()));

   PhotonIsSelected = (TH1D*)ConvCutsContainer->FindObject(Form("IsPhotonSelected %s",gammaCutSelectionRead.Data()));
   PhotonIsSelected->Scale(1./PhotonIsSelected->GetEntries());



   fNumberOfGoodESDTracks = (TH1D*)ESDContainer->FindObject("GoodESDTracks");
   fEventQuality = (TH1D*)ESDContainer->FindObject("NEvents");
   
   fnEvt = 0;
   if (option.CompareTo("PbPb_2.76TeV") == 0){
      fnEvt = fEventQuality->GetBinContent(1);
   } else {
      fnEvt = GetNEvents(fEventQuality);
      //fnEvt =  histoEventQuality->GetEntries()-histoEventQuality->GetBinContent(4)-histoEventQuality->GetBinContent(5)-histoEventQuality->GetBinContent(7);
   }
   Initialize(meson,option,numberOfBins); // Initialize Binning

   // Gamma ESD
   fHistoGammaESDConvPt = (TH1D*)ESDContainer->FindObject("ESD_ConvGamma_Pt");
   fHistoGammaESDConvPt->Sumw2();
   fHistoGammaESDConvPtOriginalBinning = (TH1D*)fHistoGammaESDConvPt->Clone("ESD_ConvGamma_Pt_OriginalBinning");
   RebinSpectrum(fHistoGammaESDConvPt,"");
   //fHistoGammaESDConvPt->Scale(1./fnEvt);
   // Conversion R Study
   // fHistoGammaESDConvR = (TH1D*)ESDContainer->FindObject("ESD_ConvGamma_R");
   // fHistoGammaESDConvR->Sumw2();


   TTree* dcaTree;
   TList *DCAContainer = NULL;
   Bool_t pileUpCorrection = kFALSE;
   if(!addSig){
      DCAContainer = (TList*) HistosGammaConversion->FindObject(Form("%s Photon DCA tree",cutSelectionRead.Data()));
      if(DCAContainer){
         dcaTree = (TTree*)DCAContainer->FindObject("ESD_ConvGamma_Pt_Dcaz_R_Eta");
         FillDCAHistogrmasFromTree(dcaTree,kFALSE);
         CalculatePileUpBackground(kFALSE);
         pileUpCorrection = kTRUE;
      }         
   }

   if(fIsMC){

      fHistoGammaMCESDConvPt = (TH1D*) fHistoGammaESDConvPt->Clone("MCESD_ConvGamma_Pt");

      TList *MCContainer = (TList*)HistosGammaConversion->FindObject(Form("%s MC histograms",cutSelectionRead.Data()));
      TList *TrueConversionContainer = (TList*)HistosGammaConversion->FindObject(Form("%s True histograms",cutSelectionRead.Data()));

      fHistoGammaMCConvPt = (TH1D*)MCContainer->FindObject("MC_ConvGamma_Pt");
      fHistoGammaMCConvPt->Sumw2();
      RebinSpectrum(fHistoGammaMCConvPt);
      //fHistoGammaMCConvPt->Scale(1./fnEvt);
      //fHistoGammaMCConvPt->Scale(1./fnEvt);
      fHistoGammaMCAllPt  = (TH1D*)MCContainer->FindObject("MC_AllGamma_Pt");
      fHistoGammaMCAllPt->Sumw2();
      fHistoGammaMCAllPtOriginalBinning = (TH1D*)fHistoGammaMCAllPt->Clone("MC_AllGamma_Pt_OriginalBinning");
      fHistoGammaMCAllPtOriginalBinning->Scale(1./fHistoGammaMCAllPtOriginalBinning->GetBinWidth(5));
      fHistoGammaMCAllPtOriginalBinning->GetXaxis()->SetRangeUser(0.,25.);
      RebinSpectrum(fHistoGammaMCAllPt);
      //fHistoGammaMCAllPt->Scale(1./fnEvt);
      fHistoGammaESDTrueConvPt = (TH1D*)TrueConversionContainer->FindObject("ESD_TrueConvGamma_Pt");
      fHistoGammaESDTrueConvPt->Sumw2();
      RebinSpectrum(fHistoGammaESDTrueConvPt);
      //fHistoGammaESDTrueConvPt->Scale(1./fnEvt);
      fHistoGammaESDTruePrimaryConvPt = (TH1D*)TrueConversionContainer->FindObject("ESD_TruePrimaryConvGamma_Pt");
      fHistoGammaESDTruePrimaryConvPt->Sumw2();
      fHistoGammaESDTruePrimaryConvPtOriginalBinning = (TH1D*)fHistoGammaESDTruePrimaryConvPt->Clone("ESD_TruePrimaryConvGamma_Pt_OriginalBinning");
      RebinSpectrum(fHistoGammaESDTruePrimaryConvPt);
      //fHistoGammaESDTruePrimaryConvPt->Scale(1./fnEvt);
      fHistoGammaESDTrueSecondaryConvPt = (TH1D*)TrueConversionContainer->FindObject("ESD_TrueSecondaryConvGamma_Pt");
      fHistoGammaESDTrueSecondaryConvPt->Sumw2();
      fHistoGammaESDTrueSecondaryConvPtOriginalBinning = (TH1D*)fHistoGammaESDTrueSecondaryConvPt->Clone("ESD_TrueSecondaryConvGamma_Pt_OriginalBinning");
      RebinSpectrum(fHistoGammaESDTrueSecondaryConvPt);
      //fHistoGammaESDTrueSecondaryConvPt->Scale(1./fnEvt);
      fHistoGammaESDTrueSecondaryConvGammaFromXFromK0sPt = (TH1D*)TrueConversionContainer->FindObject("ESD_TrueSecondaryConvGammaFromXFromK0s_Pt");
      fHistoGammaESDTrueSecondaryConvGammaFromXFromK0sPt->Sumw2();
      fHistoGammaESDTrueSecondaryConvGammaFromXFromK0sPtOriginalBinning = (TH1D*)fHistoGammaESDTrueSecondaryConvGammaFromXFromK0sPt->Clone("ESD_TrueSecondaryConvGammaFromXFromK0s_Pt_OriginalBinning");
      RebinSpectrum(fHistoGammaESDTrueSecondaryConvGammaFromXFromK0sPt);
      //fHistoGammaESDTrueSecondaryConvGammaFromXFromK0sPt->Scale(1./fnEvt);
      // Gamma from Decay
      fHistoGammaMCDecayPi0Pt = (TH1D*)MCContainer->FindObject("MC_DecayGammaPi0_Pt");
      fHistoGammaMCDecayPi0Pt->Sumw2();
      fHistoGammaMCDecayPi0Pt->Scale(1./fHistoGammaMCDecayPi0Pt->GetBinWidth(5));
      fHistoGammaMCDecayEtaPt = (TH1D*)MCContainer->FindObject("MC_DecayGammaEta_Pt");
      fHistoGammaMCDecayEtaPt->Sumw2();
      fHistoGammaMCDecayEtaPt->Scale(1./fHistoGammaMCDecayEtaPt->GetBinWidth(5));
      fHistoGammaMCDecayEtapPt = (TH1D*)MCContainer->FindObject("MC_DecayGammaEtap_Pt");
      fHistoGammaMCDecayEtapPt->Sumw2();
      fHistoGammaMCDecayEtapPt->Scale(1./fHistoGammaMCDecayEtapPt->GetBinWidth(5));
      fHistoGammaMCDecayOmegaPt = (TH1D*)MCContainer->FindObject("MC_DecayGammaOmega_Pt");
      fHistoGammaMCDecayOmegaPt->Sumw2();
      fHistoGammaMCDecayOmegaPt->Scale(1./fHistoGammaMCDecayOmegaPt->GetBinWidth(5));
      fHistoGammaMCDecayRho0Pt = (TH1D*)MCContainer->FindObject("MC_DecayGammaRho_Pt");
      fHistoGammaMCDecayRho0Pt->Sumw2();
      fHistoGammaMCDecayRho0Pt->Scale(1./fHistoGammaMCDecayRho0Pt->GetBinWidth(5));
      fHistoGammaMCDecayPhiPt = (TH1D*)MCContainer->FindObject("MC_DecayGammaPhi_Pt");
      fHistoGammaMCDecayPhiPt->Sumw2();
      fHistoGammaMCDecayPhiPt->Scale(1./fHistoGammaMCDecayPhiPt->GetBinWidth(5));
      fHistoGammaMCDecaySigmaPt = (TH1D*)MCContainer->FindObject("MC_DecayGammaSigma_Pt");
      fHistoGammaMCDecaySigmaPt->Sumw2();
      fHistoGammaMCDecaySigmaPt->Scale(1./fHistoGammaMCDecaySigmaPt->GetBinWidth(5));

      fHistoCombinatorialBackground = (TH2D*)TrueConversionContainer->FindObject("ESD_TrueCombinatorial_Pt");


      TString combinatorics[17] = {"Elec+Elec","Elec+Pion","Elec+Kaon","Elec+Proton","Elec+Muon","Pion+Pion","Pion+Kaon","Pion+Proton",
                                   "Pion+Muon","Kaon+Kaon","Kaon+Proton","Kaon+Muon","Proton+Proton","Proton+Muon","Muon+Muon","Rest","All"};


      fHistoCombinatorialSpecies = new TH1D*[17];
      fHistoCombinatorialSpecies[16] = (TH1D*)fHistoCombinatorialBackground->ProjectionX(Form("ESD_TrueComb%s_Pt",combinatorics[16].Data()));
      fHistoCombinatorialSpecies[16]->Sumw2();
      RebinSpectrum(fHistoCombinatorialSpecies[16]);

      for(Int_t i = 0; i<16; i++){
         fHistoCombinatorialSpecies[i] = (TH1D*)fHistoCombinatorialBackground->ProjectionX(Form("ESD_TrueComb%s_Pt",combinatorics[i].Data()),i+1,i+1);
         fHistoCombinatorialSpecies[i]->Sumw2();
         RebinSpectrum(fHistoCombinatorialSpecies[i]);
      }

      fHistoGammaESDTruePrimary_ESDPt_MCPt_MC = (TH2D*)TrueConversionContainer->FindObject("ESD_TruePrimaryConvGammaESD_PtMCPt");
      fHistoGammaESDTruePrimary_ESDPt_MCPt_MC->Sumw2();
      fHistoGammaESDTruePrimaryGammaMCPt = (TH1D*)fHistoGammaESDTruePrimary_ESDPt_MCPt_MC->ProjectionY("ESD_TruePrimaryConvGamma_MCPt");
      RebinSpectrum(fHistoGammaESDTruePrimaryGammaMCPt);
      
      CalculateGammaCorrection();

      if(pileUpCorrection && !addSig){
         FillDCAHistogrmasFromTree(dcaTree,kTRUE);
         CalculatePileUpBackground(kTRUE);
         CalculatePileUpGammaCorrection();
      }
      // // Conversion R Study
      // fHistoGammaMCConvR = (TH1D*)MCContainer->FindObject("MC_ConvGamma_R");
      // fHistoGammaMCConvR->Sumw2();
      // fHistoGammaESDTruePrimaryConvR = (TH1D*)TrueConversionContainer->FindObject("ESD_TruePrimaryConvGamma_R");
      // fHistoGammaESDTruePrimaryConvR->Sumw2();
      // fHistoGammaESDTrueSecondaryConvR = (TH1D*)TrueConversionContainer->FindObject("ESD_TrueSecondaryConvGamma_R");
      // fHistoGammaESDTrueSecondaryConvR->Sumw2();

      SaveCorrectionHistos(cutSelection,fPrefix2,pileUpCorrection);
   }

   SaveHistos(fIsMC,cutSelection,fPrefix2,pileUpCorrection);
   if(pileUpCorrection && !addSig){
      SaveDCAHistos(fIsMC,cutSelection,fPrefix2);
      PlotAdditionalDCAz(fIsMC,cutSelection);
   }
   

}

void RebinSpectrum(TH1D *Spectrum, TString NewName){
   if(NewName.CompareTo(""))
      NewName = Spectrum->GetName();

   *Spectrum = *((TH1D*)Spectrum->Rebin(fNBinsPt,NewName,fBinsPt));
   Spectrum->Divide(fDeltaPt);
}

void CalculatePileUpBackground(Bool_t doMC){

   Double_t DCARange[2] = {-10,10};

   if(fIsMC && doMC){

      fESDMCGammaPtDCAzBins = new TH1D*[fNBinsPt+1];
      fESDMCSubGammaPtDCAzBins = new TH1D*[fNBinsPt+1];
      fESDMCGammaPtDCAzBinsBack = new TH1D*[fNBinsPt+1];
      fTruePrimaryPhotonPtDCAzBins = new TH1D*[fNBinsPt+1];
      fTrueSecondaryPhotonPtDCAzBins = new TH1D*[fNBinsPt+1];
      fTrueSecondaryPhotonFromXFromK0sPtDCAzBins = new TH1D*[fNBinsPt+1];
      fTrueBackgroundPtDCAzBins = new TH1D*[fNBinsPt+1];
      fTrueGammaPtDCAzBins = new TH1D*[fNBinsPt+1];
      fTrueSubGammaPtDCAzBins = new TH1D*[fNBinsPt+1];

      fESDMCGammaPtPileUp = (TH1D*)fHistoGammaMCESDConvPt->Clone("ESDMC_ConvGamma_Pt_PileUp");
      fTruePrimaryConvGammaPtPileUp = (TH1D*)fHistoGammaESDTruePrimaryConvPt->Clone("ESD_TruePrimaryConvGamma_Pt_PileUp");
      fTrueSecondaryConvGammaPtPileUp = (TH1D*)fHistoGammaESDTrueSecondaryConvPt->Clone("ESD_TrueSecondaryConvGamma_Pt_PileUp");
      fTrueSecondaryFromXFromK0sConvGammaPtPileUp = (TH1D*) fHistoGammaESDTrueSecondaryConvGammaFromXFromK0sPt->Clone("ESD_TrueSecondaryFromXFromK0sConvGamma_Pt_PileUp");


      fESDMCGammaPtDCAzBins[0] = (TH1D*)fESDGammaPtDCAz[5]->ProjectionY("ESDMC_GammaPtDCAzBin_Full");
      fESDMCGammaPtDCAzBins[0]->Sumw2();
      fESDMCGammaPtDCAzBinsBack[0] = (TH1D*)fESDMCGammaPtDCAzBins[0]->ShowBackground(13,"BackSmoothing10");
      fESDMCGammaPtDCAzBinsBack[0]->SetName("ESDMC_GammaPtDCAzBackBin_Full");

      fTruePrimaryPhotonPtDCAzBins[0] = (TH1D*)fTruePrimaryPhotonPtDCAz[5]->ProjectionY("ESD_TruePrimaryGammaPtDCAzBin_Full");
      fTruePrimaryPhotonPtDCAzBins[0]->Sumw2();
      fTrueSecondaryPhotonPtDCAzBins[0] = (TH1D*)fTrueSecondaryPhotonPtDCAz[5]->ProjectionY("ESD_TrueSecondaryGammaPtDCAzBin_Full");
      fTrueSecondaryPhotonPtDCAzBins[0]->Sumw2();
      fTrueSecondaryPhotonFromXFromK0sPtDCAzBins[0] = (TH1D*)fTrueSecondaryPhotonFromXFromK0sPtDCAz[5]->ProjectionY("ESD_TrueSecondaryGammaFromXFromK0sPtDCAzBin_Full");
      fTrueSecondaryPhotonFromXFromK0sPtDCAzBins[0]->Sumw2();

      fTrueBackgroundPtDCAzBins[0] = (TH1D*)fESDMCGammaPtDCAzBins[0]->Clone("ESD_TrueGammaBackgroundPtDCAzBin_Full");
      fTrueBackgroundPtDCAzBins[0]->Add(fTruePrimaryPhotonPtDCAzBins[0],-1);
      fTrueBackgroundPtDCAzBins[0]->Add(fTrueSecondaryPhotonPtDCAzBins[0],-1);

      fTrueGammaPtDCAzBins[0] = (TH1D*)fTruePrimaryPhotonPtDCAzBins[0]->Clone("ESD_TrueGammaPtDCAz_Full");
      fTrueGammaPtDCAzBins[0]->Add(fTrueSecondaryPhotonPtDCAzBins[0],1);

      Double_t fracAllGammaToPrimMC = fTrueGammaPtDCAzBins[0]->Integral()/fTruePrimaryPhotonPtDCAzBins[0]->Integral();
      Double_t fracAllGammaToSecMC = fTrueGammaPtDCAzBins[0]->Integral()/fTrueSecondaryPhotonPtDCAzBins[0]->Integral();
      Double_t fracAllGammaToSecFromXFromK0sMC = fTrueGammaPtDCAzBins[0]->Integral()/fTrueSecondaryPhotonFromXFromK0sPtDCAzBins[0]->Integral();

      fESDMCSubGammaPtDCAzBins[0] = (TH1D*)fESDMCGammaPtDCAzBins[0]->Clone("ESDMC_SubGammaPtDCAzBin_Full");
      fESDMCSubGammaPtDCAzBins[0]->Add(fESDMCGammaPtDCAzBinsBack[0],-1); // Vom Allem Übrig

      fTrueSubGammaPtDCAzBins[0] = (TH1D*)fTrueGammaPtDCAzBins[0]->Clone("ESD_TrueSubGammaPtDCAz_Full");
      fTrueSubGammaPtDCAzBins[0]->Add(fESDMCGammaPtDCAzBinsBack[0],-1);
      for(Int_t i = 0; i<fTrueGammaPtDCAzBins[0]->GetNbinsX();i++){
         if(fTrueSubGammaPtDCAzBins[0]->GetBinContent(i+1)<0){
            fTrueSubGammaPtDCAzBins[0]->SetBinContent(i+1,0);
            fTrueSubGammaPtDCAzBins[0]->SetBinError(i+1,0);
         }
      }


      for(Int_t i = 0; i<fTrueGammaPtDCAzBins[0]->GetNbinsX();i++){
         if(fTrueGammaPtDCAzBins[0]->GetBinContent(i+1) && fTruePrimaryPhotonPtDCAzBins[0]->GetBinContent(i+1))
            fracAllGammaToPrimMC = fTrueGammaPtDCAzBins[0]->GetBinContent(i+1)/fTruePrimaryPhotonPtDCAzBins[0]->GetBinContent(i+1);
         else fracAllGammaToPrimMC = fTrueGammaPtDCAzBins[0]->Integral()/fTruePrimaryPhotonPtDCAzBins[0]->Integral();

         fTruePrimaryPhotonPtDCAzBins[0]->SetBinContent(i+1,fTrueSubGammaPtDCAzBins[0]->GetBinContent(i+1)/fracAllGammaToPrimMC);

         if(fTrueGammaPtDCAzBins[0]->GetBinContent(i+1) && fTrueSecondaryPhotonPtDCAzBins[0]->GetBinContent(i+1))
            fracAllGammaToSecMC = fTrueGammaPtDCAzBins[0]->GetBinContent(i+1)/fTrueSecondaryPhotonPtDCAzBins[0]->GetBinContent(i+1);
         else fracAllGammaToSecMC = fTrueGammaPtDCAzBins[0]->Integral()/fTrueSecondaryPhotonPtDCAzBins[0]->Integral();

         fTrueSecondaryPhotonPtDCAzBins[0]->SetBinContent(i+1,fTrueSubGammaPtDCAzBins[0]->GetBinContent(i+1)/fracAllGammaToSecMC);

         if(fTrueGammaPtDCAzBins[0]->GetBinContent(i+1) && fTrueSecondaryPhotonFromXFromK0sPtDCAzBins[0]->GetBinContent(i+1))
            fracAllGammaToSecFromXFromK0sMC = fTrueGammaPtDCAzBins[0]->GetBinContent(i+1)/fTrueSecondaryPhotonFromXFromK0sPtDCAzBins[0]->GetBinContent(i+1);
         else fracAllGammaToSecFromXFromK0sMC = fTrueGammaPtDCAzBins[0]->Integral()/fTrueSecondaryPhotonFromXFromK0sPtDCAzBins[0]->Integral();

         fTrueSecondaryPhotonFromXFromK0sPtDCAzBins[0]->SetBinContent(i+1,fTrueSubGammaPtDCAzBins[0]->GetBinContent(i+1)/fracAllGammaToSecFromXFromK0sMC);
      }

      for(Int_t bin = 1; bin<fNBinsPt+1; bin++){
         Int_t startBin = fHistoGammaESDConvPtOriginalBinning->FindBin(fBinsPt[bin-1]+0.001);
         Int_t endBin   = fHistoGammaESDConvPtOriginalBinning->FindBin(fBinsPt[bin]-0.001);

         fESDMCGammaPtDCAzBins[bin] = (TH1D*)fESDGammaPtDCAz[5]->ProjectionY(Form("ESDMC_GammaPtDCAzBin_%.1f_%.1f",fBinsPt[bin-1],fBinsPt[bin]),startBin,endBin);
         fESDMCGammaPtDCAzBins[bin]->Sumw2();
         fESDMCGammaPtDCAzBinsBack[bin] = (TH1D*)fESDMCGammaPtDCAzBins[bin]->ShowBackground(13,"BackSmoothing10");
         fESDMCGammaPtDCAzBinsBack[bin]->SetName(Form("ESDMC_GammaPtDCAzBackBin_%.1f_%.1f",fBinsPt[bin-1],fBinsPt[bin]));
         fESDMCGammaPtDCAzBinsBack[bin]->Sumw2();

         fTruePrimaryPhotonPtDCAzBins[bin] = (TH1D*)fTruePrimaryPhotonPtDCAz[5]->ProjectionY(Form("ES_TruPrimaryGammaPtDCAzBin_%.1f_%.1f",fBinsPt[bin-1],fBinsPt[bin]),startBin,endBin);
         fTruePrimaryPhotonPtDCAzBins[bin]->Sumw2();

         fTrueSecondaryPhotonPtDCAzBins[bin] = (TH1D*)fTrueSecondaryPhotonPtDCAz[5]->ProjectionY(Form("ES_TruSecondaryGammaPtDCAzBin_%.1f_%.1f",fBinsPt[bin-1],fBinsPt[bin]),startBin,endBin);
         fTrueSecondaryPhotonPtDCAzBins[bin]->Sumw2();
         fTrueSecondaryPhotonFromXFromK0sPtDCAzBins[bin]
            = (TH1D*)fTrueSecondaryPhotonFromXFromK0sPtDCAz[5]->ProjectionY(Form("ES_TruSecondaryGammaFromXFromK0sPtDCAz_Bin_%.1f_%.1f",fBinsPt[bin-1],fBinsPt[bin]),startBin,endBin);
         fTrueSecondaryPhotonFromXFromK0sPtDCAzBins[bin]->Sumw2();

         fTrueBackgroundPtDCAzBins[bin] = (TH1D*)fESDMCGammaPtDCAzBins[bin]->Clone(Form("ESD_TrueGammaBackgroundPtDCAz_Bin_%.1f_%.1f",fBinsPt[bin-1],fBinsPt[bin]));
         fTrueBackgroundPtDCAzBins[bin]->Add(fTruePrimaryPhotonPtDCAzBins[bin],-1);
         fTrueBackgroundPtDCAzBins[bin]->Add(fTrueSecondaryPhotonPtDCAzBins[bin],-1);

         fTrueGammaPtDCAzBins[bin] = (TH1D*)fTruePrimaryPhotonPtDCAzBins[bin]->Clone(Form("ESD_TrueGammaPtDCAz_Bin_%.1f_%.1f",fBinsPt[bin-1],fBinsPt[bin]));
         fTrueGammaPtDCAzBins[bin]->Add(fTrueSecondaryPhotonPtDCAzBins[bin],1);

         Double_t fracAllGammaToPrim = fTrueGammaPtDCAzBins[bin]->Integral()/fTruePrimaryPhotonPtDCAzBins[bin]->Integral();
         Double_t fracAllGammaToSec = fTrueGammaPtDCAzBins[bin]->Integral()/fTrueSecondaryPhotonPtDCAzBins[bin]->Integral();
         Double_t fracAllGammaToSecFromXFromK0s = fTrueGammaPtDCAzBins[bin]->Integral()/fTrueSecondaryPhotonFromXFromK0sPtDCAzBins[bin]->Integral();

         fESDMCSubGammaPtDCAzBins[bin] = (TH1D*)fESDMCGammaPtDCAzBins[bin]->Clone(Form("ESDMC_SubGammaPtDCAzBin_Bin_%.1f_%.1f",fBinsPt[bin-1],fBinsPt[bin]));
         fESDMCSubGammaPtDCAzBins[bin]->Add(fESDMCGammaPtDCAzBinsBack[bin],-1); // Vom Allem Übrig

         fTrueSubGammaPtDCAzBins[bin] = (TH1D*)fTrueGammaPtDCAzBins[bin]->Clone(Form("ESD_TrueSubGammaPtDCAz_Bin_%.1f_%.1f",fBinsPt[bin-1],fBinsPt[bin]));
         fTrueSubGammaPtDCAzBins[bin]->Add(fESDMCGammaPtDCAzBinsBack[bin],-1);
         for(Int_t i = 0; i<fTrueGammaPtDCAzBins[bin]->GetNbinsX();i++){
            if(fTrueSubGammaPtDCAzBins[bin]->GetBinContent(i+1)<0){
               fTrueSubGammaPtDCAzBins[bin]->SetBinContent(i+1,0);
               fTrueSubGammaPtDCAzBins[bin]->SetBinError(i+1,0);
            }
         }

         for(Int_t i = 0; i<fTrueGammaPtDCAzBins[bin]->GetNbinsX();i++){
            if(fTrueGammaPtDCAzBins[bin]->GetBinContent(i+1) && fTruePrimaryPhotonPtDCAzBins[bin]->GetBinContent(i+1))
               fracAllGammaToPrim = fTrueGammaPtDCAzBins[bin]->GetBinContent(i+1)/fTruePrimaryPhotonPtDCAzBins[bin]->GetBinContent(i+1);
            else fracAllGammaToPrim = fTrueGammaPtDCAzBins[bin]->Integral()/fTruePrimaryPhotonPtDCAzBins[bin]->Integral();

            fTruePrimaryPhotonPtDCAzBins[bin]->SetBinContent(i+1,fTrueSubGammaPtDCAzBins[bin]->GetBinContent(i+1)/fracAllGammaToPrim);

            if(fTrueGammaPtDCAzBins[bin]->GetBinContent(i+1) && fTrueSecondaryPhotonPtDCAzBins[bin]->GetBinContent(i+1))
               fracAllGammaToSec = fTrueGammaPtDCAzBins[bin]->GetBinContent(i+1)/fTrueSecondaryPhotonPtDCAzBins[bin]->GetBinContent(i+1);
            else fracAllGammaToSec = fTrueGammaPtDCAzBins[bin]->Integral()/fTrueSecondaryPhotonPtDCAzBins[bin]->Integral();

            fTrueSecondaryPhotonPtDCAzBins[bin]->SetBinContent(i+1,fTrueSubGammaPtDCAzBins[bin]->GetBinContent(i+1)/fracAllGammaToSec);

            if(fTrueGammaPtDCAzBins[bin]->GetBinContent(i+1) && fTrueSecondaryPhotonFromXFromK0sPtDCAzBins[bin]->GetBinContent(i+1))
               fracAllGammaToSecFromXFromK0s = fTrueGammaPtDCAzBins[bin]->GetBinContent(i+1)/fTrueSecondaryPhotonFromXFromK0sPtDCAzBins[bin]->GetBinContent(i+1);
            else fracAllGammaToSecFromXFromK0s = fTrueGammaPtDCAzBins[bin]->Integral()/fTrueSecondaryPhotonFromXFromK0sPtDCAzBins[bin]->Integral();

            fTrueSecondaryPhotonFromXFromK0sPtDCAzBins[bin]->SetBinContent(i+1,fTrueSubGammaPtDCAzBins[bin]->GetBinContent(i+1)/fracAllGammaToSecFromXFromK0s);
         }


         Double_t binContent, binError;
         binContent = fESDMCSubGammaPtDCAzBins[bin]->IntegralAndError(-1000,1000,binError);
         fESDMCGammaPtPileUp->SetBinContent(bin,binContent);
         fESDMCGammaPtPileUp->SetBinError(bin,binError);

         binContent = fTruePrimaryPhotonPtDCAzBins[bin]->IntegralAndError(-1000,1000,binError);
         fTruePrimaryConvGammaPtPileUp->SetBinContent(bin,binContent);
         fTruePrimaryConvGammaPtPileUp->SetBinError(bin,binError);

         binContent = fTrueSecondaryPhotonPtDCAzBins[bin]->IntegralAndError(-1000,1000,binError);
         fTrueSecondaryConvGammaPtPileUp->SetBinContent(bin,binContent);
         fTrueSecondaryConvGammaPtPileUp->SetBinError(bin,binError);

         binContent = fTrueSecondaryPhotonFromXFromK0sPtDCAzBins[bin]->IntegralAndError(-1000,1000,binError);
         fTrueSecondaryFromXFromK0sConvGammaPtPileUp->SetBinContent(bin,binContent);
         fTrueSecondaryFromXFromK0sConvGammaPtPileUp->SetBinError(bin,binError);


      }
      fESDMCGammaPtPileUp->Divide(fDeltaPt);
      fTruePrimaryConvGammaPtPileUp->Divide(fDeltaPt);
      fTrueSecondaryConvGammaPtPileUp->Divide(fDeltaPt);
      fTrueSecondaryFromXFromK0sConvGammaPtPileUp->Divide(fDeltaPt);

      TString nameFile = Form("%s/%s_%s_ESDMC_DCAz_vs_Pt_%s.%s",fOutputDir.Data(),fPrefix.Data(),fPrefix2.Data(),fCutSelection.Data(),fSuffix.Data());
      PlotDCAzInPtBinsWitchack(fESDMCGammaPtDCAzBins,fESDMCGammaPtDCAzBinsBack,NULL, nameFile, "CanvasESDDCAz", "PadESDDCAz", DCARange, fdate, fmeson, 6 , 6, 1, fNBinsPt, fBinsPt, "#gamma --> e^{+}e^{-}", fIsMC, "#gamma --> e^{+}e^{-}",  "MinBias");
      nameFile = Form("%s/%s_%s_SignalAfterSubtraction_DCAz_vs_Pt_%s.%s",fOutputDir.Data(),fPrefix.Data(),fPrefix2.Data(),fCutSelection.Data(),fSuffix.Data());
      PlotDCAzInPtBinsWitchack(fESDMCSubGammaPtDCAzBins,fTrueSubGammaPtDCAzBins,NULL, nameFile, "CanvasESDDCAz", "PadESDDCAz", DCARange, fdate, fmeson, 6 , 6, 1, fNBinsPt, fBinsPt, "#gamma --> e^{+}e^{-}", fIsMC, "#gamma --> e^{+}e^{-}",  "MinBias");

      nameFile = Form("%s/%s_%s_TrueBackDCAz_vs_Pt_%s.%s",fOutputDir.Data(),fPrefix.Data(),fPrefix2.Data(),fCutSelection.Data(),fSuffix.Data());
      PlotDCAzInPtBinsWitchack(fTrueBackgroundPtDCAzBins,fESDMCGammaPtDCAzBinsBack,NULL, nameFile, "CanvasESDDCAz", "PadESDDCAz", DCARange, fdate, fmeson, 6 , 6, 1, fNBinsPt, fBinsPt, "#gamma --> e^{+}e^{-}", fIsMC, "#gamma --> e^{+}e^{-}",  "MinBias");

      nameFile = Form("%s/%s_%s_TrueSignalDCAz_vs_Pt_%s.%s",fOutputDir.Data(),fPrefix.Data(),fPrefix2.Data(),fCutSelection.Data(),fSuffix.Data());
      PlotDCAzInPtBinsWitchack(fESDMCGammaPtDCAzBins,fTrueGammaPtDCAzBins, NULL,nameFile, "CanvasESDDCAz", "PadESDDCAz", DCARange, fdate, fmeson, 6 , 6, 1, fNBinsPt, fBinsPt, "#gamma --> e^{+}e^{-}", fIsMC, "#gamma --> e^{+}e^{-}",  "MinBias");




   }
   else{ // Data

      fESDGammaPtDCAzBins = new TH1D*[fNBinsPt+1];
      fESDGammaPtDCAzBinsBack = new TH1D*[fNBinsPt+1];
      fESDSubGammaPtDCAzBins = new TH1D*[fNBinsPt+1];
      fESDGammaPtPileUp = (TH1D*)fHistoGammaESDConvPt->Clone("ESD_ConvGamma_Pt_PileUp");

      fESDGammaPtDCAzBins[0] = (TH1D*)fESDGammaPtDCAz[5]->ProjectionY("ESD_GammaPtDCAzBin_Full");
      fESDGammaPtDCAzBins[0]->Sumw2();
      fESDGammaPtDCAzBinsBack[0] = (TH1D*)fESDGammaPtDCAzBins[0]->ShowBackground(13,"BackSmoothing10");
      fESDGammaPtDCAzBinsBack[0]->SetName("ESD_GammaPtDCAzBackBin_Full");

      fESDSubGammaPtDCAzBins[0] = (TH1D*)fESDGammaPtDCAzBins[0]->Clone("ESD_SubGammaPtDCAzBin_Full");
      fESDSubGammaPtDCAzBins[0]->Add(fESDGammaPtDCAzBinsBack[0],-1); // Vom Allem Übrig

      for(Int_t bin = 1; bin<fNBinsPt+1; bin++){
         Int_t startBin = fHistoGammaESDConvPtOriginalBinning->FindBin(fBinsPt[bin-1]+0.001);
         Int_t endBin   = fHistoGammaESDConvPtOriginalBinning->FindBin(fBinsPt[bin]-0.001);

         fESDGammaPtDCAzBins[bin] = (TH1D*)fESDGammaPtDCAz[5]->ProjectionY(Form("ESD_GammaPtDCAzBin_%.1f_%.1f",fBinsPt[bin-1],fBinsPt[bin]),startBin,endBin);
         fESDGammaPtDCAzBins[bin]->Sumw2();
         fESDGammaPtDCAzBinsBack[bin] = (TH1D*)fESDGammaPtDCAzBins[bin]->ShowBackground(13,"BackSmoothing10");
         fESDGammaPtDCAzBinsBack[bin]->SetName(Form("ESD_GammaPtDCAzBackBin_%.1f_%0.1f",fBinsPt[bin-1],fBinsPt[bin]));
         fESDGammaPtDCAzBinsBack[bin]->Sumw2();

         fESDSubGammaPtDCAzBins[bin] = (TH1D*)fESDGammaPtDCAzBins[bin]->Clone(Form("ESD_SubGammaPtDCAzBin_%.1f_%.1f",fBinsPt[bin-1],fBinsPt[bin]));
         fESDSubGammaPtDCAzBins[bin]->Add(fESDGammaPtDCAzBinsBack[bin],-1); // Vom Allem Übrig

         Double_t binContent, binError;
         binContent = fESDSubGammaPtDCAzBins[bin]->IntegralAndError(-1000,1000,binError);
         fESDGammaPtPileUp->SetBinContent(bin,binContent);
         fESDGammaPtPileUp->SetBinError(bin,binError);

      }

      fESDGammaPtPileUp->Divide(fDeltaPt);

      TString nameFile = Form("%s/%s_%s_ESD_DCAz_vs_Pt_%s.%s",fOutputDir.Data(),fPrefix.Data(),fPrefix2.Data(),fCutSelection.Data(),fSuffix.Data());
      PlotDCAzInPtBinsWitchack(fESDGammaPtDCAzBins,fESDGammaPtDCAzBinsBack,NULL,nameFile, "CanvasESDDCAz", "PadESDDCAz", DCARange, fdate, fmeson, 6 , 6, 1, fNBinsPt, fBinsPt, "#gamma --> e^{+}e^{-}", fIsMC, "#gamma --> e^{+}e^{-}",  "MinBias");

      TCanvas *RatioWithWithoutPileUpCanvas = GetAndSetCanvas("canvasRatioWithWithoutPileUp");
      fRatioWithWithoutPileUp = (TH1D*)fHistoGammaESDConvPt->Clone("RatioWithWithoutPileUp");
      fRatioWithWithoutPileUp->SetTitle("");
      fRatioWithWithoutPileUp->Divide(fRatioWithWithoutPileUp,fESDGammaPtPileUp,1,1,"B");
      SetHistogramm(fRatioWithWithoutPileUp,"p_{T} (GeV/c)","#gamma / #gamma Pile-Up correted",0.98,1.2);
      
      fRatioWithWithoutPileUp->DrawCopy();

      RatioWithWithoutPileUpCanvas->Print(Form("%s/%s_%s_ESD_With_vs_Without_Pileup_pT_%s.%s",fOutputDir.Data(),fPrefix.Data(),fPrefix2.Data(),fCutSelection.Data(),fSuffix.Data()));
      delete RatioWithWithoutPileUpCanvas;
   }
}

void CalculatePileUpGammaCorrection(){


   fHistoFracAllGammaToSecPileUp = (TH1D*) fESDGammaPtPileUp->Clone("FracAllGammaToSecPileUp");
   fHistoFracAllGammaToSecPileUp->Divide(fTrueSecondaryConvGammaPtPileUp,fHistoFracAllGammaToSecPileUp,1,1,"B");

   fHistoFracAllGammaToSecFromXFromK0sPileUp = (TH1D*) fESDGammaPtPileUp->Clone("FracAllGammaToSecFromXFromK0sPileUp");
   fHistoFracAllGammaToSecFromXFromK0sPileUp->Divide(fTrueSecondaryFromXFromK0sConvGammaPtPileUp,fHistoFracAllGammaToSecFromXFromK0sPileUp,1,1,"B");

   // ================= PURITY =================
   fHistoGammaMCPurityPileUp = new TH1D("MCGammaPurityPileUp","",fNBinsPt,fBinsPt);
   fHistoGammaMCPurityPileUp->Sumw2();
   fHistoGammaMCPurityPileUp->Add(fTruePrimaryConvGammaPtPileUp);
   fHistoGammaMCPurityPileUp->Add(fTrueSecondaryConvGammaPtPileUp);
   fHistoGammaMCPurityPileUp->Divide(fHistoGammaMCPurityPileUp,fESDMCGammaPtPileUp,1,1,"B");

   fHistoGammaMCESDPrimaryConvPtPileUp = (TH1D*) fESDMCGammaPtPileUp->Clone("MCESD_PrimaryConvGamma_PtPileUp");
   fHistoGammaMCESDPrimaryConvPtPileUp->Add(fTrueSecondaryConvGammaPtPileUp,-1);
   fHistoGammaMCTruePurityPileUp = new TH1D("MCGammaTruePurityPileUp","",fNBinsPt,fBinsPt);
   fHistoGammaMCTruePurityPileUp->Sumw2();
   fHistoGammaMCTruePurityPileUp->Divide(fTruePrimaryConvGammaPtPileUp,fHistoGammaMCESDPrimaryConvPtPileUp,1,1,"B");
   // ==========================================

   // ================ Reco Eff ================
   fHistoGammaMCRecoEffPileUp = new TH1D("MCGammaRecoEffPileUp","",fNBinsPt,fBinsPt);
   fHistoGammaMCRecoEffPileUp->Sumw2();
   fHistoGammaMCRecoEffPileUp->Add(fTruePrimaryConvGammaPtPileUp);
   fHistoGammaMCRecoEffPileUp->Add(fTrueSecondaryConvGammaPtPileUp);
   fHistoGammaMCRecoEffPileUp->Divide(fHistoGammaMCRecoEffPileUp,fHistoGammaMCConvPt,1,1,"B");

   fHistoGammaMCPrimaryRecoEffPileUp = new TH1D("MCGammaPrimaryRecoEffPileUp","",fNBinsPt,fBinsPt);
   fHistoGammaMCPrimaryRecoEffPileUp->Sumw2();
   fHistoGammaMCPrimaryRecoEffPileUp->Divide(fTruePrimaryConvGammaPtPileUp,fHistoGammaMCConvPt,1,1,"B");
   // ==========================================


   // fHistoGammaMCTruePurityPileUp->Divide(fHistoGammaMCPrimaryRecoEffPileUp);
   // fHistoGammaMCTruePurity->Divide(fHistoGammaMCPrimaryRecoEff);

   // fHistoGammaMCTruePurityPileUp->Divide(fHistoGammaMCTruePurity);
   // fHistoGammaMCTruePurityPileUp->DrawCopy();

   // return;


   // fESDGammaPtPileUp->Add(fTrueSecondaryConvGammaPtPileUp,-1);
   // fESDGammaPtPileUp->Multiply(fHistoGammaMCTruePurityPileUp);
   // fESDGammaPtPileUp->Divide(fHistoGammaMCPrimaryRecoEffPileUp);

   // fHistoGammaESDConvPt->Add(fHistoGammaESDTrueSecondaryConvPt,-1);
   // fHistoGammaESDConvPt->Multiply(fHistoGammaMCTruePurity);
   // fHistoGammaESDConvPt->Divide(fHistoGammaMCPrimaryRecoEff);

   // fHistoGammaESDConvPt->Divide(fESDGammaPtPileUp);
   // fHistoGammaESDConvPt->DrawCopy()
}


void CalculateGammaCorrection()
{

   TAxis *xAxis = fHistoGammaESDTruePrimary_ESDPt_MCPt_MC->GetXaxis();
   TAxis *yAxis = fHistoGammaESDTruePrimary_ESDPt_MCPt_MC->GetYaxis();

   fHistoGammaESDTruePrimary_ESDPt_MCPt_MC_Rebin = new TH2D("ESD_TrueConvPrimaryGamma_ESDPt_MCPt_Rebin","",fNBinsPt,fBinsPt,fNBinsPt,fBinsPt);
   for(Int_t x = 1; x<fHistoGammaESDTruePrimary_ESDPt_MCPt_MC->GetNbinsX()+1; x++){
      for(Int_t y = 1; y<fHistoGammaESDTruePrimary_ESDPt_MCPt_MC->GetNbinsY()+1; y++){
         Double_t binContent = fHistoGammaESDTruePrimary_ESDPt_MCPt_MC->GetBinContent(x,y);
         Double_t xcenter = xAxis->GetBinCenter(x);
         Double_t ycenter = yAxis->GetBinCenter(y);
         fHistoGammaESDTruePrimary_ESDPt_MCPt_MC_Rebin->Fill(xcenter,ycenter,binContent);
      }
   }
   //      fHistoGammaMCESDConvR = (TH1D*) fHistoGammaESDConvR->Clone("fMC_ESDConvGammaR");


   fHistoFracAllGammaToSecOriginalBinning = (TH1D*) fHistoGammaESDConvPtOriginalBinning->Clone("FracAllGammaToSecOriginalBinning");
   fHistoFracAllGammaToSecOriginalBinning->Divide(fHistoGammaESDTrueSecondaryConvPtOriginalBinning,fHistoFracAllGammaToSecOriginalBinning,1,1,"B");

   fHistoFracAllGammaToSec = (TH1D*) fHistoGammaESDConvPt->Clone("FracAllGammaToSec");
   fHistoFracAllGammaToSec->Divide(fHistoGammaESDTrueSecondaryConvPt,fHistoFracAllGammaToSec,1,1,"B");

   fHistoFracAllGammaToSecFromXFromK0s = (TH1D*) fHistoGammaESDConvPt->Clone("FracAllGammaToSecFromXFromK0s");
   fHistoFracAllGammaToSecFromXFromK0s->Divide(fHistoGammaESDTrueSecondaryConvGammaFromXFromK0sPt,fHistoFracAllGammaToSecFromXFromK0s,1,1,"B");

   fHistoFracAllGammaToSecFromXFromK0sOriginalBinning = (TH1D*) fHistoGammaESDConvPtOriginalBinning->Clone("FracAllGammaToSecFromXFromK0sOriginalBinning");
   fHistoFracAllGammaToSecFromXFromK0sOriginalBinning->Divide(fHistoGammaESDTrueSecondaryConvGammaFromXFromK0sPtOriginalBinning,fHistoFracAllGammaToSecFromXFromK0sOriginalBinning,1,1,"B");

   // =============== Conv Prob ================
   fHistoGammaMCConvProb = new TH1D("MCGammaConvProb","",fNBinsPt,fBinsPt);
   fHistoGammaMCConvProb->Sumw2();
   fHistoGammaMCConvProb->Divide(fHistoGammaMCConvPt,fHistoGammaMCAllPt,1,1,"B");
   // ==========================================

   // ================= PURITY =================
   fHistoGammaMCPurity = new TH1D("MCGammaPurity","",fNBinsPt,fBinsPt);
   fHistoGammaMCPurity->Sumw2();
   fHistoGammaMCPurity->Divide(fHistoGammaESDTrueConvPt,fHistoGammaESDConvPt,1,1,"B");

   fHistoGammaMCESDPrimaryConvPt = (TH1D*) fHistoGammaESDConvPt->Clone("MCESD_PrimaryConvGamma_Pt");
   fHistoGammaMCESDPrimaryConvPt->Add(fHistoGammaESDTrueSecondaryConvPt,-1);
   fHistoGammaMCTruePurity = new TH1D("MCGammaTruePurity","",fNBinsPt,fBinsPt);
   fHistoGammaMCTruePurity->Sumw2();
   fHistoGammaMCTruePurity->Divide(fHistoGammaESDTruePrimaryConvPt,fHistoGammaMCESDPrimaryConvPt,1,1,"B");

   fHistoGammaMCESDPrimaryConvPtOriginalBinning = (TH1D*) fHistoGammaESDConvPtOriginalBinning->Clone("MC_ESDPrimaryConvGammaPt");
   fHistoGammaMCESDPrimaryConvPtOriginalBinning->Add(fHistoGammaESDTrueSecondaryConvPtOriginalBinning,-1);
   fHistoGammaMCTruePurityOriginalBinning = (TH1D*)fHistoGammaMCESDPrimaryConvPtOriginalBinning->Clone("MCGammaTruePurityOriginalBinning");
   fHistoGammaMCTruePurityOriginalBinning->Sumw2();
   fHistoGammaMCTruePurityOriginalBinning->Divide(fHistoGammaESDTruePrimaryConvPtOriginalBinning,fHistoGammaMCESDPrimaryConvPtOriginalBinning,1,1,"B");
   // ==========================================

   // ================ Reco Eff ================
   fHistoGammaMCRecoEff = new TH1D("MCGammaRecoEff","",fNBinsPt,fBinsPt);
   fHistoGammaMCRecoEff->Sumw2();
   fHistoGammaMCRecoEff->Divide(fHistoGammaESDTrueConvPt,fHistoGammaMCConvPt,1,1,"B");

   fHistoGammaMCPrimaryRecoEff = new TH1D("MCGammaPrimaryRecoEff","",fNBinsPt,fBinsPt);
   fHistoGammaMCPrimaryRecoEff->Sumw2();
   fHistoGammaMCPrimaryRecoEff->Divide(fHistoGammaESDTruePrimaryConvPt,fHistoGammaMCConvPt,1,1,"B");

   fHistoGammaMCPrimaryRecoEffMCPt = new TH1D("MCGammaPrimaryRecoEffMCPt","",fNBinsPt,fBinsPt);
   fHistoGammaMCPrimaryRecoEffMCPt->Sumw2();
   fHistoGammaMCPrimaryRecoEffMCPt->Divide(fHistoGammaESDTruePrimaryGammaMCPt,fHistoGammaMCConvPt,1,1,"B");

   // ==========================================

   fHistoGammaMCBackground = new TH1D("MCGammaBackground","",fNBinsPt,fBinsPt);
   fHistoGammaMCBackground->Sumw2();
   fHistoGammaMCBackground = (TH1D*)fHistoGammaMCESDConvPt->Clone("MCGammaBackground");
   fHistoGammaMCBackground->Add(fHistoGammaESDTrueConvPt,-1);


}

void Initialize(TString Binning, TString Energy , Int_t Bins)
{
   if (Binning.CompareTo("Pi0") == 0){
      fNBinsPt = Bins;
      fBinsPt = new Double_t[60];
      fNRebin = new Int_t[59];

      if (Energy.CompareTo("7TeV") == 0) {

         if (fdirectphoton.CompareTo("directPhoton") == 0){
            fStartPtBin= 1;

            if (fNBinsPt > 24) {
               cout << "You have chosen Direct Photon Plots and more than 24 bins, this is not possible, it will be reduced to 24 bins." << endl;
               fNBinsPt = 24;
            }
            for (Int_t i = 0; i < fNBinsPt+1; i++) {
               fBinsPt[i] = fBinsPi07TeVDirectPhotonPt[i];
               if (i < fNBinsPt+1) fNRebin[i] = fBinsPi07TeVDirectPhotonPtRebin[i];
            }
         } else {
            fStartPtBin = 1;

            if (fNBinsPt > 32) {
               cout << "You have chosen to have more than 32 bins, this is not possible, it will be reduced to 32" << endl;
               fNBinsPt = 32;
            }
            for (Int_t i = 0; i < fNBinsPt+1; i++) {
               fBinsPt[i] = fBinsPi07TeVPt[i];
               if (i < fNBinsPt+1) fNRebin[i] = fBinsPi07TeVPtRebin[i];
            }
         }
      } else if (Energy.CompareTo("2.76TeV") == 0) {
         if (fdirectphoton.CompareTo("directPhoton") == 0){
            fStartPtBin= 1;

            if (fNBinsPt > 21) {
               cout << "You have chosen Direct Photon Plots and more than 21 bins, this is not possible, it will be reduced to 21 bins." << endl;
               fNBinsPt = 21;
            }
            for (Int_t i = 0; i < fNBinsPt+1; i++) {
               fBinsPt[i] = fBinsPi02760GeVDirectPhotonPt[i];
               if (i < fNBinsPt+1) fNRebin[i] = fBinsPi02760GeVDirectPhotonPtRebin[i];
            }
         } else {
            fStartPtBin = 1;

            if (fNBinsPt > 19) {
               cout << "You have chosen to have more than 19 bins, this is not possible, it will be reduced to 19" << endl;
               fNBinsPt = 19;
            }
            for (Int_t i = 0; i < fNBinsPt+1; i++) {
               fBinsPt[i] = fBinsPi02760GeVPt[i];
               if (i < fNBinsPt+1) fNRebin[i] = fBinsPi02760GeVPtRebin[i];
            }
         }
      } else if (Energy.CompareTo("900GeV") == 0) {
         if (fdirectphoton.CompareTo("directPhoton") == 0){
            fStartPtBin= 1;

            if (fNBinsPt > 21) {
               cout << "You have chosen Direct Photon Plots and more than 21 bins, this is not possible, it will be reduced to 21 bins." << endl;
               fNBinsPt = 21;
            }
            for (Int_t i = 0; i < fNBinsPt+1; i++) {
               fBinsPt[i] = fBinsPi0900GeVDirectPhotonPt[i];
               if (i < fNBinsPt+1) fNRebin[i] = fBinsPi0900GeVDirectPhotonPtRebin[i];
            }
         }
         else {
            fStartPtBin= 1;

            if (fNBinsPt > 11) {
               cout << "You have chosen to have more than 11 bins, this is not possible, it will be reduced to 11" << endl;
               fNBinsPt = 11;
            }
            for (Int_t i = 0; i < fNBinsPt+1; i++) {
               fBinsPt[i] = fBinsPi0900GeVPt[i];
               if (i < fNBinsPt+1) fNRebin[i] = fBinsPi0900GeVPtRebin[i];
            }
         }
      } else if( fEnergyFlag.CompareTo("pPb_5.023TeV") == 0) {
         if (fdirectphoton.CompareTo("directPhoton") == 0){
            fStartPtBin = 1;

            if (fNBinsPt > 21) {
               cout << "You have chosen Direct Photon Plots and more than 21 bins, this is not possible, it will be reduced to 21 bins." << endl;
               fNBinsPt = 21;
            }
            for (Int_t i = 0; i < fNBinsPt+1; i++) {
               fBinsPt[i] = fBinsPi0pPbDirectPhotonPt[i];
               if (i < fNBinsPt+1) fNRebin[i] = fBinsPi0pPbDirectPhotonPtRebin[i];
            }
         } else{
            fStartPtBin=   1;
            if (fNBinsPt > 31) {
               cout << "You have chosen to have more than 30 bins, this is not possible, it will be reduced to 31" << endl;
               fNBinsPt = 31;
            }
            for (Int_t i = 0; i < fNBinsPt+1; i++) {
               fBinsPt[i] = fBinsPi0pPbPt[i];
               if (i < fNBinsPt+1) fNRebin[i] = fBinsPi0pPbPtRebin[i];
            }
         }
      } else { // HI
         if (fdirectphoton.CompareTo("directPhoton") == 0){
            fStartPtBin= 1;

            if (fNBinsPt > 60) {
               cout << "You have chosen Direct Photon Plots and more than 21 bins, this is not possible, it will be reduced to 21 bins." << endl;
               fNBinsPt = 21;
            }
            for (Int_t i = 0; i < fNBinsPt+1; i++) {
               fBinsPt[i] = fBinsPi0HIDirectPhotonPt[i];
               if (i < fNBinsPt+1) fNRebin[i] = fBinsPi0HIDirectPhotonPtRebin[i];
            }
         } else{
            fStartPtBin = 1;
            if (fNBinsPt > 20) {
               cout << "You have chosen to have more than 20 bins, this is not possible, it will be reduced to 20" << endl;
               fNBinsPt = 20;
            }
            for (Int_t i = 0; i < fNBinsPt+1; i++) {
               fBinsPt[i] = fBinsPi0HIPt[i];
               if (i < fNBinsPt+1) fNRebin[i] = fBinsPi0HIPtRebin[i];
            }
         }
      }
   } else if (Binning.CompareTo("Eta") == 0){
      fNBinsPt = Bins;
      fBinsPt = new Double_t[15];
      fNRebin =	new Int_t[14];

      if (Energy.CompareTo("7TeV") == 0) {
         fStartPtBin = 1;

         if (fNBinsPt > 12) {
            cout << "You have chosen to have more than 12 bins for Eta, this is not possible, it will be reduced to 12" << endl;
            fNBinsPt = 12;
         }
         for (Int_t i = 0; i < fNBinsPt+2; i++) {
            fBinsPt[i] = fBinsEta7TeVPt[i];
            if (i < fNBinsPt+1) fNRebin[i] = fBinsEta7TeVPtRebin[i];
         }
      } else if (Energy.CompareTo("2.76TeV") == 0) {
         fStartPtBin = 1;

         if (fNBinsPt > 7) {
            cout << "You have chosen to have more than 7 bins for Eta, this is not possible, it will be reduced to 9" << endl;
            fNBinsPt = 7;
         }
         for (Int_t i = 0; i < fNBinsPt+1; i++) {
            fBinsPt[i] = fBinsEta2760GeVPt[i];
            if (i < fNBinsPt+1) fNRebin[i] = fBinsEta2760GeVPtRebin[i];
         }
      } else if (Energy.CompareTo("900GeV") == 0) {
         fStartPtBin=	1;

         if (fNBinsPt > 3) {
            cout << "You have chosen to have more than 3 bins for Eta, this is not possible, it will be reduced to 3" << endl;
            fNBinsPt = 3;
         }
         for (Int_t i = 0; i < fNBinsPt+1; i++) {
            fBinsPt[i] = fBinsEta900GeVPt[i];
            if (i < fNBinsPt+1) fNRebin[i] = fBinsEta900GeVPtRebin[i];
         }
      }  else if( fEnergyFlag.CompareTo("PbPb_2.76TeV") == 0) {
         fStartPtBin=	1;
         fColumn = 	2;
         fRow = 		2;

         if (fNBinsPt > 4) {
            cout << "You have chosen to have more than 4 bins, this is not possible, it will be reduced to 4" << endl;
            fNBinsPt = 4;
         }
         for (Int_t i = 0; i < fNBinsPt+1; i++) {
            fBinsPt[i] = fBinsEtaHIPt[i];
            if (i < fNBinsPt+1) fNRebin[i] = fBinsEtaHIPtRebin[i];
         }

         fExampleBin = 2;
      } else if( fEnergyFlag.CompareTo("pPb_5.023TeV") == 0) {
         fStartPtBin=   1;

         if (fNBinsPt > 9) {
            cout << "You have chosen to have more than 9 bins, this is not possible, it will be reduced to 9" << endl;
            fNBinsPt = 9;
         }
         for (Int_t i = 0; i < fNBinsPt+1; i++) {
            fBinsPt[i] = fBinsEtapPbPt[i];
            if (i < fNBinsPt+1) fNRebin[i] = fBinsEtapPbPtRebin[i];
         }
      } else {
         fStartPtBin=	1;

         if (fNBinsPt > 4) {
            cout << "You have chosen to have more than 4 bins, this is not possible, it will be reduced to 4" << endl;
            fNBinsPt = 4;
         }
         for (Int_t i = 0; i < fNBinsPt+1; i++) {
            fBinsPt[i] = fBinsEtaHIPt[i];
            if (i < fNBinsPt+1) fNRebin[i] = fBinsEtaHIPtRebin[i];
         }
      }
   } else if (Binning.CompareTo("EtaPrim") == 0){
      fNBinsPt = Bins;

      if (Energy.CompareTo("7TeV") == 0) {
         fStartPtBin = 1;

         if (fNBinsPt > 7) {
            cout << "You have chosen directPhoton Plots and more than 7 bins for Eta, this is not possible, it will be reduced to 7 bins." << endl;
            fNBinsPt = 7;
         }
         for (Int_t i = 0; i < fNBinsPt+2; i++) {
            fBinsPt[i] = fBinsEtaPrim7TeVPt[i];
            if (i < fNBinsPt+1) fNRebin[i] = fBinsEtaPrim7TeVPtRebin[i];
         }
      }
   } else {
      fNBinsPt = Bins;

      if (Energy.CompareTo("7TeV") == 0) {
         if (fdirectphoton.CompareTo("directPhoton") == 0){
            fStartPtBin = 1;

            if (fNBinsPt > 12) {
               cout << "You have chosen directPhoton Plots and more than 12 bins for Eta, this is not possible, it will be reduced to 12 bins." << endl;
               fNBinsPt = 12;
            }
            for (Int_t i = 0; i < fNBinsPt+2; i++) {
               fBinsPt[i] = fBinsEta7TeVPt[i];
               if (i < fNBinsPt+1) fNRebin[i] = fBinsPi0EtaBinning7TeVPtRebin[i];
            }
         } else {
            fStartPtBin = 1;

            if (fNBinsPt > 12) {
               cout << "You have chosen to have more than 12 bins for Eta, this is not possible, it will be reduced to 12" << endl;
               fNBinsPt = 12;
            }
            for (Int_t i = 0; i < fNBinsPt+2; i++) {
               fBinsPt[i] = fBinsEta7TeVPt[i];
               if (i < fNBinsPt+1) fNRebin[i] = fBinsPi0EtaBinning7TeVPtRebin[i];
            }
         }
      } else if (Energy.CompareTo("2.76TeV") == 0) {
         fStartPtBin = 1;

         if (fNBinsPt > 7) {
            cout << "You have chosen to have more than 7 bins for Eta, this is not possible, it will be reduced to 9" << endl;
            fNBinsPt = 7;
         }
         for (Int_t i = 0; i < fNBinsPt+1; i++) {
            fBinsPt[i] = fBinsEta2760GeVPt[i];
            if (i < fNBinsPt+1) fNRebin[i] = fBinsPi0EtaBinning2760GeVPtRebin[i];
         }
      } else if (Energy.CompareTo("900GeV") == 0) {
         fStartPtBin = 1;

         if (fNBinsPt > 3) {
            cout << "You have chosen to have more than 3 bins for Eta, this is not possible, it will be reduced to 3" << endl;
            fNBinsPt = 3;
         }
         for (Int_t i = 0; i < fNBinsPt+1; i++) {
            fBinsPt[i] = fBinsEta900GeVPt[i];
            if (i < fNBinsPt+1) fNRebin[i] = fBinsPi0EtaBinning900GeVPtRebin[i];
         }
      } else {
         fStartPtBin = 1;

         if (fNBinsPt > 4) {
            cout << "You have chosen to have more than 4 bins, this is not possible, it will be reduced to 4" << endl;
            fNBinsPt = 4;
         }
         for (Int_t i = 0; i < fNBinsPt+1; i++) {
            fBinsPt[i] = fBinsEtaHIPt[i];
            if (i < fNBinsPt+1) fNRebin[i] = fBinsPi0EtaBinningHIPtRebin[i];
         }
      }
   }

   fDeltaPt = new TH1D("deltaPt","",fNBinsPt,fBinsPt);
   for(Int_t iPt=fStartPtBin+1;iPt<fNBinsPt+1;iPt++){
      fDeltaPt->SetBinContent(iPt,fBinsPt[iPt]-fBinsPt[iPt-1]);
      fDeltaPt->SetBinError(iPt,0);
   }
}

void FillDCAHistogrmasFromTree(TTree *dcaTree,Bool_t isMC){


   Float_t dcaZPhoton, pt;
   UChar_t cat, photonMCInfo;
   dcaTree->SetBranchAddress("Pt",&pt);
   dcaTree->SetBranchAddress("DcaZPhoton",&dcaZPhoton);
   dcaTree->SetBranchAddress("cat",&cat);
   if (isMC) dcaTree->SetBranchAddress("photonMCInfo",&photonMCInfo);

   //fESDGammaPtDCAz = (TH2D*)ESDContainer->FindObject("ESD_GammaPtDCAz");

   if(!isMC){
      fESDGammaPtDCAz = new TH2F*[6];
      fESDGammaPtDCAz[0] = new TH2F("ESD_GammaPtDCAz_cat0","ESD_GammaPtDCAz_cat0",250,0,25,201,-10,10);
      fESDGammaPtDCAz[0]->Sumw2();
      fESDGammaPtDCAz[1] = new TH2F("ESD_GammaPtDCAz_cat1","ESD_GammaPtDCAz_cat1",250,0,25,201,-10,10);
      fESDGammaPtDCAz[1]->Sumw2();
      fESDGammaPtDCAz[2] = new TH2F("ESD_GammaPtDCAz_cat2","ESD_GammaPtDCAz_cat2",250,0,25,201,-10,10);
      fESDGammaPtDCAz[2]->Sumw2();
      fESDGammaPtDCAz[3] = new TH2F("ESD_GammaPtDCAz_cat3","ESD_GammaPtDCAz_cat3",250,0,25,201,-10,10);
      fESDGammaPtDCAz[3]->Sumw2();
      fESDGammaPtDCAz[4] = new TH2F("ESD_GammaPtDCAz_cat23","ESD_GammaPtDCAz_cat23",250,0,25,201,-10,10);
      fESDGammaPtDCAz[4]->Sumw2();
      fESDGammaPtDCAz[5] = new TH2F("ESD_GammaPtDCAz_all","ESD_GammaPtDCAz_all",250,0,25,201,-10,10);
      fESDGammaPtDCAz[5]->Sumw2();

      Long64_t nentries = dcaTree->GetEntries();
      for (Long64_t l=0;l<nentries;l++) {
         dcaTree->GetEntry(l);
         if(cat == 0) fESDGammaPtDCAz[0]->Fill(pt,dcaZPhoton);
         if(cat == 1) fESDGammaPtDCAz[1]->Fill(pt,dcaZPhoton);
         if(cat == 2) fESDGammaPtDCAz[2]->Fill(pt,dcaZPhoton);
         if(cat == 3) fESDGammaPtDCAz[3]->Fill(pt,dcaZPhoton);
         if(cat == 2 || cat == 3) fESDGammaPtDCAz[4]->Fill(pt,dcaZPhoton);
         if(cat != 0)fESDGammaPtDCAz[5]->Fill(pt,dcaZPhoton);
      }
   }
   if(isMC){
      fESDMCGammaPtDCAz = new TH2F("ESDMC_GammaPtDCAz_all","ESDMC_GammaPtDCAz_all",250,0,25,201,-10,10);
      fESDMCGammaPtDCAz->Sumw2();
      fTruePrimaryPhotonPtDCAz = new TH2F*[6];
      fTrueSecondaryPhotonPtDCAz = new TH2F*[6];
      fTrueSecondaryPhotonFromXFromK0sPtDCAz = new TH2F*[6];
      fTruePrimaryPhotonPtDCAz[0] = new TH2F("ESD_TruePrimaryGammaPtDCAz_cat0","ESD_TruePrimaryGammaPtDCAz_cat0",250,0,25,201,-10,10);
      fTrueSecondaryPhotonPtDCAz[0] = new TH2F("ESD_TrueSecondaryGammaPtDCAz_cat0","ESD_TrueSecondaryGammaPtDCAz_cat0",250,0,25,201,-10,10);
      fTrueSecondaryPhotonFromXFromK0sPtDCAz[0] = new TH2F("ESD_TrueSecondaryGammaFromXFromK0sDCAz_cat0","ESD_TrueSecondaryGammaFromXFromK0sDCAz_cat0",250,0,25,201,-10,10);
      fTruePrimaryPhotonPtDCAz[0]->Sumw2();
      fTrueSecondaryPhotonPtDCAz[0]->Sumw2();
      fTrueSecondaryPhotonFromXFromK0sPtDCAz[0]->Sumw2();
      fTruePrimaryPhotonPtDCAz[1] = new TH2F("ESD_TruePrimaryGammaPtDCAz_cat1","ESD_TruePrimaryGammaPtDCAz_cat1",250,0,25,201,-10,10);
      fTrueSecondaryPhotonPtDCAz[1] = new TH2F("ESD_TrueSecondaryGammaPtDCAz_cat1","ESD_TrueSecondaryGammaPtDCAz_cat1",250,0,25,201,-10,10);
      fTrueSecondaryPhotonFromXFromK0sPtDCAz[1] = new TH2F("ESD_TrueSecondaryGammaFromXFromK0sDCAz_cat1","ESD_TrueSecondaryGammaFromXFromK0sDCAz_cat1",250,0,25,201,-10,10);
      fTruePrimaryPhotonPtDCAz[1]->Sumw2();
      fTrueSecondaryPhotonPtDCAz[1]->Sumw2();
      fTrueSecondaryPhotonFromXFromK0sPtDCAz[1]->Sumw2();
      fTruePrimaryPhotonPtDCAz[2] = new TH2F("ESD_TruePrimaryGammaPtDCAz_cat2","ESD_TruePrimaryGammaPtDCAz_cat2",250,0,25,201,-10,10);
      fTrueSecondaryPhotonPtDCAz[2] = new TH2F("ESD_TrueSecondaryGammaPtDCAz_cat2","ESD_TrueSecondaryGammaPtDCAz_cat2",250,0,25,201,-10,10);
      fTrueSecondaryPhotonFromXFromK0sPtDCAz[2] = new TH2F("ESD_TrueSecondaryGammaFromXFromK0sDCAz_cat2","ESD_TrueSecondaryGammaFromXFromK0sDCAz_cat2",250,0,25,201,-10,10);
      fTruePrimaryPhotonPtDCAz[2]->Sumw2();
      fTrueSecondaryPhotonPtDCAz[2]->Sumw2();
      fTrueSecondaryPhotonFromXFromK0sPtDCAz[2]->Sumw2();
      fTruePrimaryPhotonPtDCAz[3] = new TH2F("ESD_TruePrimaryGammaPtDCAz_cat3","ESD_TruePrimaryGammaPtDCAz_cat3",250,0,25,201,-10,10);
      fTrueSecondaryPhotonPtDCAz[3] = new TH2F("ESD_TrueSecondaryGammaPtDCAz_cat3","ESD_TrueSecondaryGammaPtDCAz_cat3",250,0,25,201,-10,10);
      fTrueSecondaryPhotonFromXFromK0sPtDCAz[3] = new TH2F("ESD_TrueSecondaryGammaFromXFromK0sDCAz_cat3","ESD_TrueSecondaryGammaFromXFromK0sDCAz_cat3",250,0,25,201,-10,10);
      fTruePrimaryPhotonPtDCAz[3]->Sumw2();
      fTrueSecondaryPhotonPtDCAz[3]->Sumw2();
      fTrueSecondaryPhotonFromXFromK0sPtDCAz[3]->Sumw2();
      fTruePrimaryPhotonPtDCAz[4] = new TH2F("ESD_TruePrimaryGammaPtDCAz_cat23","ESD_TruePrimaryGammaPtDCAz_cat23",250,0,25,201,-10,10);
      fTrueSecondaryPhotonPtDCAz[4] = new TH2F("ESD_TrueSecondaryGammaPtDCAz_cat23","ESD_TrueSecondaryGammaPtDCAz_cat23",250,0,25,201,-10,10);
      fTrueSecondaryPhotonFromXFromK0sPtDCAz[4] = new TH2F("ESD_TrueSecondaryGammaFromXFromK0sDCAz_cat23","ESD_TrueSecondaryGammaFromXFromK0sDCAz_cat23",250,0,25,101,-10,10);
      fTruePrimaryPhotonPtDCAz[4]->Sumw2();
      fTrueSecondaryPhotonPtDCAz[4]->Sumw2();
      fTrueSecondaryPhotonFromXFromK0sPtDCAz[4]->Sumw2();
      fTruePrimaryPhotonPtDCAz[5] = new TH2F("ESD_TruePrimaryGammaPtDCAz_all","ESD_TruePrimaryGammaPtDCAz_all",250,0,25,201,-10,10);
      fTrueSecondaryPhotonPtDCAz[5] = new TH2F("ESD_TrueSecondaryGammaPtDCAz_all","ESD_TrueSecondaryGammaPtDCAz_all",250,0,25,201,-10,10);
      fTrueSecondaryPhotonFromXFromK0sPtDCAz[5] = new TH2F("ESD_TrueSecondaryGammaFromXFromK0sDCAz_all","ESD_TrueSecondaryGammaFromXFromK0sDCAz_all",250,0,25,201,-10,10);
      fTruePrimaryPhotonPtDCAz[5]->Sumw2();
      fTrueSecondaryPhotonPtDCAz[5]->Sumw2();
      fTrueSecondaryPhotonFromXFromK0sPtDCAz[5]->Sumw2();

      Long64_t nentries = dcaTree->GetEntries();
      for (Long64_t l=0;l<nentries;l++) {
         dcaTree->GetEntry(l);
         fESDMCGammaPtDCAz->Fill(pt,dcaZPhoton);
         if(cat == 0){
            if(photonMCInfo == 6) fTruePrimaryPhotonPtDCAz[0]->Fill(pt,dcaZPhoton);
            if(photonMCInfo == 2 || photonMCInfo == 3 || photonMCInfo == 4 || photonMCInfo == 5)
               fTrueSecondaryPhotonPtDCAz[0]->Fill(pt,dcaZPhoton);
            if(photonMCInfo == 4) fTrueSecondaryPhotonFromXFromK0sPtDCAz[0]->Fill(pt,dcaZPhoton);
         }
         if(cat == 1){
            if(photonMCInfo == 6) fTruePrimaryPhotonPtDCAz[1]->Fill(pt,dcaZPhoton);
            if(photonMCInfo == 2 || photonMCInfo == 3 || photonMCInfo == 4 || photonMCInfo == 5)
               fTrueSecondaryPhotonPtDCAz[1]->Fill(pt,dcaZPhoton);
            if(photonMCInfo == 4) fTrueSecondaryPhotonFromXFromK0sPtDCAz[1]->Fill(pt,dcaZPhoton);
         }
         if(cat == 2){
            if(photonMCInfo == 6) fTruePrimaryPhotonPtDCAz[2]->Fill(pt,dcaZPhoton);
            if(photonMCInfo == 2 || photonMCInfo == 3 || photonMCInfo == 4 || photonMCInfo == 5)
               fTrueSecondaryPhotonPtDCAz[2]->Fill(pt,dcaZPhoton);
            if(photonMCInfo == 4) fTrueSecondaryPhotonFromXFromK0sPtDCAz[2]->Fill(pt,dcaZPhoton);
         }
         if(cat == 3){
            if(photonMCInfo == 6) fTruePrimaryPhotonPtDCAz[3]->Fill(pt,dcaZPhoton);
            if(photonMCInfo == 2 || photonMCInfo == 3 || photonMCInfo == 4 || photonMCInfo == 5)
               fTrueSecondaryPhotonPtDCAz[3]->Fill(pt,dcaZPhoton);
            if(photonMCInfo == 4) fTrueSecondaryPhotonFromXFromK0sPtDCAz[3]->Fill(pt,dcaZPhoton);
         }
         if(cat == 2 || cat == 3){
            if(photonMCInfo == 6) fTruePrimaryPhotonPtDCAz[4]->Fill(pt,dcaZPhoton);
            if(photonMCInfo == 2 || photonMCInfo == 3 || photonMCInfo == 4 || photonMCInfo == 5)
               fTrueSecondaryPhotonPtDCAz[4]->Fill(pt,dcaZPhoton);
            if(photonMCInfo == 4) fTrueSecondaryPhotonFromXFromK0sPtDCAz[4]->Fill(pt,dcaZPhoton);
         }
         if(cat != 0){
            if(photonMCInfo == 6) fTruePrimaryPhotonPtDCAz[5]->Fill(pt,dcaZPhoton);
            if(photonMCInfo == 2 || photonMCInfo == 3 || photonMCInfo == 4 || photonMCInfo == 5)
               fTrueSecondaryPhotonPtDCAz[5]->Fill(pt,dcaZPhoton);
            if(photonMCInfo == 4) fTrueSecondaryPhotonFromXFromK0sPtDCAz[5]->Fill(pt,dcaZPhoton);
         }
      }
   }
}

void SaveHistos(Int_t isMC, TString fCutID, TString fPrefix3,Bool_t PileUpCorrection)
{
   const char* nameOutput = Form("%s/%s/%s_%s_GammaConvV1WithoutCorrection%s_%s.root",fCutSelection.Data(),fEnergyFlag.Data(),fPrefix.Data(),fPrefix3.Data(),fPeriodFlag.Data(),fCutID.Data());
   TFile *Output1 = new TFile(nameOutput,"UPDATE");

   fDeltaPt->Write("deltaPt",TObject::kOverwrite);
   fEventQuality->Write("NEvents",TObject::kOverwrite);
   PhotonIsSelected->Write(Form("IsPhotonSelected %s",gammaCutSelectionRead.Data()),TObject::kOverwrite);
   fHistoGammaESDConvPt->Write("ESD_ConvGamma_Pt",TObject::kOverwrite);
   fHistoGammaESDConvPtOriginalBinning->Write("ESD_ConvGamma_Pt_OriginalBinning",TObject::kOverwrite);
   if(PileUpCorrection){
      fESDGammaPtPileUp->Write("ESD_ConvGamma_Pt_PileUp",TObject::kOverwrite);
      fESDGammaPtDCAzBins[0]->Write("ESD_GammaPtDCAzBin_Full",TObject::kOverwrite);
   }
   if(isMC){
      fHistoGammaMCConvPt->Write("MC_ConvGamma_Pt",TObject::kOverwrite);
      fHistoGammaESDTruePrimaryConvPt->Write("ESD_TruePrimaryConvGamma_Pt",TObject::kOverwrite);
      fHistoGammaESDTrueConvPt->Write("ESD_TrueConvGamma_Pt",TObject::kOverwrite);
   }
   Output1->Write();
   Output1->Close();
}

void SaveCorrectionHistos(TString fCutID, TString fPrefix3,Bool_t PileUpCorrection)
{
   const char* nameOutput = Form("%s/%s/%s_%s_GammaConvV1CorrectionHistos%s_%s.root",fCutSelection.Data(),fEnergyFlag.Data(),fPrefix.Data(),fPrefix3.Data(),fPeriodFlag.Data(),fCutID.Data());
   TFile *Output2 = new TFile(nameOutput,"UPDATE");
   fHistoGammaMCAllPt->Write("MC_AllGamma_Pt",TObject::kOverwrite);
   fHistoGammaMCAllPtOriginalBinning->Write("MC_AllGamma_Pt_OriginalBinning",TObject::kOverwrite);
   fHistoGammaMCConvPt->Write("MC_ConvGamma_Pt",TObject::kOverwrite);
   fHistoGammaESDTruePrimaryConvPt->Write("ESD_TruePrimaryConvGamma_Pt",TObject::kOverwrite);
   fHistoGammaESDTrueSecondaryConvPt->Write("ESD_TrueSecondaryConvGamma_Pt",TObject::kOverwrite);
   fHistoGammaESDTrueSecondaryConvGammaFromXFromK0sPt->Write("ESD_TrueSecondaryConvGammaFromXFromK0s_Pt",TObject::kOverwrite);
   fHistoGammaESDTrueSecondaryConvPtOriginalBinning->Write("ESD_TrueSecondaryConvGamma_Pt_OriginalBinning",TObject::kOverwrite);
   fHistoGammaESDTrueSecondaryConvGammaFromXFromK0sPtOriginalBinning->Write("ESD_TrueSecondaryConvGammaFromXFromK0s_Pt_OriginalBinning",TObject::kOverwrite);
   fHistoFracAllGammaToSec->Write("FracAllGammaToSec",TObject::kOverwrite);
   fHistoFracAllGammaToSecFromXFromK0s->Write("FracAllGammaToSecFromXFromK0s",TObject::kOverwrite);
   fHistoFracAllGammaToSecOriginalBinning->Write("FracAllGammaToSecOriginalBinning",TObject::kOverwrite);
   fHistoFracAllGammaToSecFromXFromK0sOriginalBinning->Write("FracAllGammaToSecFromXFromK0sOriginalBinning",TObject::kOverwrite);
   fHistoGammaMCESDConvPt->Write("MCESD_ConvGamma_Pt",TObject::kOverwrite);
   fHistoGammaMCESDPrimaryConvPt->Write("MCESD_PrimaryConvGamma_Pt",TObject::kOverwrite);
   fHistoGammaESDTrueConvPt->Write("ESD_TrueConvGamma_Pt",TObject::kOverwrite);
   fHistoGammaMCDecayPi0Pt->Write("MC_DecayGammaPi0_Pt",TObject::kOverwrite);
   fHistoGammaMCDecayEtaPt->Write("MC_DecayGammaEta_Pt",TObject::kOverwrite);
   fHistoGammaMCDecayEtapPt->Write("MC_DecayGammaEtap_Pt",TObject::kOverwrite);
   fHistoGammaMCDecayOmegaPt->Write("MC_DecayGammaOmega_Pt",TObject::kOverwrite);
   fHistoGammaMCDecayRho0Pt->Write("MC_DecayGammaRho_Pt",TObject::kOverwrite);
   fHistoGammaMCDecayPhiPt->Write("MC_DecayGammaPhi_Pt",TObject::kOverwrite);
   fHistoGammaMCDecaySigmaPt->Write("MC_DecayGammaSigma_Pt",TObject::kOverwrite);
   fHistoGammaMCPurity->Write("MCGammaPurity",TObject::kOverwrite);
   fHistoGammaMCTruePurity->Write("MCGammaTruePurity",TObject::kOverwrite);
   fHistoGammaMCTruePurityOriginalBinning->Write("MCGammaTruePurityOriginalBinning",TObject::kOverwrite);
   fHistoGammaMCConvProb->Write("MCGammaConvProb",TObject::kOverwrite);
   fHistoGammaMCRecoEff->Write("MCGammaRecoEff",TObject::kOverwrite);
   fHistoGammaMCPrimaryRecoEff->Write("MCGammaPrimaryRecoEff",TObject::kOverwrite);
   fHistoGammaMCPrimaryRecoEffMCPt->Write("MCGammaPrimaryRecoEffMCPt",TObject::kOverwrite);
   fHistoGammaESDTruePrimary_ESDPt_MCPt_MC->Write("ESD_TruePrimaryConvGammaESD_PtMCPt",TObject::kOverwrite);
   fHistoGammaESDTruePrimary_ESDPt_MCPt_MC_Rebin->Write("ESD_TrueConvPrimaryGamma_ESDPt_MCPt_Rebin",TObject::kOverwrite);
   fHistoGammaMCBackground->Write("MCGammaBackground",TObject::kOverwrite);
   fHistoCombinatorialBackground->Write("ESD_TrueCombinatorial_Pt",TObject::kOverwrite);
   fEventQuality->Write("NEvents",TObject::kOverwrite);

   if(PileUpCorrection){
      fESDMCGammaPtPileUp->Write("ESDMC_ConvGamma_Pt_PileUp",TObject::kOverwrite);
      fESDMCGammaPtDCAzBins[0]->Write("ESDMC_GammaPtDCAzBin_Full",TObject::kOverwrite);
      fHistoFracAllGammaToSecPileUp->Write("FracAllGammaToSecPileUp",TObject::kOverwrite);
      fHistoFracAllGammaToSecFromXFromK0sPileUp->Write("FracAllGammaToSecFromXFromK0sPileUp",TObject::kOverwrite);
      fHistoGammaMCPurityPileUp->Write("MCGammaPurityPileUp",TObject::kOverwrite);
      fHistoGammaMCESDPrimaryConvPtPileUp->Write("MCESD_PrimaryConvGamma_PtPileUp",TObject::kOverwrite);
      fHistoGammaMCTruePurityPileUp->Write("MCGammaTruePurityPileUp",TObject::kOverwrite);
      fHistoGammaMCRecoEffPileUp->Write("MCGammaRecoEffPileUp",TObject::kOverwrite);
      fHistoGammaMCPrimaryRecoEffPileUp->Write("MCGammaPrimaryRecoEffPileUp",TObject::kOverwrite);
   }
	TString combinatorics[17] = {"Elec+Elec","Elec+Pion","Elec+Kaon","Elec+Proton","Elec+Muon","Pion+Pion","Pion+Kaon","Pion+Proton",
                                   "Pion+Muon","Kaon+Kaon","Kaon+Proton","Kaon+Muon","Proton+Proton","Proton+Muon","Muon+Muon","Rest","All"};
   for(Int_t i = 0; i<17; i++)
      fHistoCombinatorialSpecies[i]->Write(Form("ESD_TrueComb%s_Pt",combinatorics[i].Data()),TObject::kOverwrite);



   Output2->Write();
   Output2->Close();
}

void SaveDCAHistos(Int_t isMC, TString fCutID, TString fPrefix3)
{
   const char* nameOutput = Form("%s/%s/%s_%s_GammaConvV1DCAHistogramms%s_%s.root",fCutSelection.Data(),fEnergyFlag.Data(),fPrefix.Data(),fPrefix3.Data(),fPeriodFlag.Data(),fCutID.Data());
   TFile *Output1 = new TFile(nameOutput,"RECREATE");

   fRatioWithWithoutPileUp->Write();


   if(!isMC){
      fESDGammaPtDCAz[5]->Write();
      TH2D *ESDGammaPtDCAzPerEvent = (TH2D*)fESDGammaPtDCAz[5]->Clone(Form("%s_perEvent",fESDGammaPtDCAz[5]->GetName()));
      ESDGammaPtDCAzPerEvent->Scale(1./fnEvt);
      ESDGammaPtDCAzPerEvent->Write();
      fESDGammaPtDCAzBinsBack[0]->Write();
      TH1D *ESDGammaPtDCAzBinsBackPerEvent = (TH1D*)fESDGammaPtDCAzBinsBack[0]->Clone(Form("%s_perEvent",fESDGammaPtDCAzBinsBack[0]->GetName()));
      ESDGammaPtDCAzBinsBackPerEvent->Scale(1./fnEvt);
      ESDGammaPtDCAzBinsBackPerEvent->Write();

      TH1D *ESDGammaDCAzAllSub = (TH1D*)fESDGammaPtDCAz[5]->ProjectionY("ESD_GammaDCAz_all_Subtracted");
      ESDGammaDCAzAllSub->Add(fESDGammaPtDCAzBinsBack[0],-1);
      ESDGammaDCAzAllSub->Write();
      TH1D *ESDGammaDCAzAllSubperEvent = (TH1D*)ESDGammaPtDCAzPerEvent->ProjectionY("ESD_GammaDCAz_all_Subtracted_perEvent");
      ESDGammaDCAzAllSubperEvent->Add(ESDGammaPtDCAzBinsBackPerEvent,-1);
      ESDGammaDCAzAllSubperEvent->Write();
   }
   if(isMC){
      fESDMCGammaPtDCAzBinsBack[0]->Write();
      TH1D *ESDMCGammaPtDCAzBinsBack = (TH1D*)fESDMCGammaPtDCAzBinsBack[0]->Clone(Form("%s_perEvent",fESDMCGammaPtDCAzBinsBack[0]->GetName()));
      ESDMCGammaPtDCAzBinsBack->Scale(1./fnEvt);
      ESDMCGammaPtDCAzBinsBack->Write();
      fESDMCGammaPtDCAz->Write();
      TH2D *ESDMCGammaPtDCAzPerEvent = (TH2D*)fESDMCGammaPtDCAz->Clone(Form("%s_perEvent",fESDMCGammaPtDCAz->GetName()));
      ESDMCGammaPtDCAzPerEvent->Scale(1./fnEvt);
      ESDMCGammaPtDCAzPerEvent->Write();

      fTruePrimaryPhotonPtDCAz[5]->Write();
      fTrueSecondaryPhotonPtDCAz[5]->Write();
      fTrueSecondaryPhotonFromXFromK0sPtDCAz[5]->Write();

      TH2D *TruePrimaryPhotonPtDCAzPerEvent = (TH2D*)fTruePrimaryPhotonPtDCAz[5]->Clone(Form("%s_perEvent",fTruePrimaryPhotonPtDCAz[5]->GetName()));
      TruePrimaryPhotonPtDCAzPerEvent->Scale(1./fnEvt);
      TruePrimaryPhotonPtDCAzPerEvent->Write();
      TH2D *TrueSecondaryPhotonPtDCAzPerEvent = (TH2D*)fTrueSecondaryPhotonPtDCAz[5]->Clone(Form("%s_perEvent",fTrueSecondaryPhotonPtDCAz[5]->GetName()));
      TrueSecondaryPhotonPtDCAzPerEvent->Scale(1./fnEvt);
      TrueSecondaryPhotonPtDCAzPerEvent->Write();
      TH2D *TrueSecondaryPhotonFromXFromK0sPtDCAzPerEvent = (TH2D*)fTrueSecondaryPhotonFromXFromK0sPtDCAz[5]->Clone(Form("%s_perEvent",fTrueSecondaryPhotonFromXFromK0sPtDCAz[5]->GetName()));
      TrueSecondaryPhotonFromXFromK0sPtDCAzPerEvent->Scale(1./fnEvt);
      TrueSecondaryPhotonFromXFromK0sPtDCAzPerEvent->Write();

   }
   
   // for(Int_t i = 0; i<NBinsPt+1; i++){
   //    if(isMC){
   //       //fESDMCGammaPtDCAzBins[i]->Scale(1./fESDMCGammaPtDCAzBins[i]->GetEntries());
   //       fESDMCGammaPtDCAzBins[i]->Write();
   //       //fESDMCSubGammaPtDCAzBins[i]->Scale(1./fESDMCSubGammaPtDCAzBins[i]->GetEntries());
   //       fESDMCSubGammaPtDCAzBins[i]->Write();
   //       //fESDMCGammaPtDCAzBinsBack[i]->Scale(1./fESDMCGammaPtDCAzBinsBack[i]->GetEntries());
   //       fESDMCGammaPtDCAzBinsBack[i]->Write();
   //       //fTruePrimaryPhotonPtDCAzBins[i]->Scale(1./fTruePrimaryPhotonPtDCAzBins[i]->GetEntries());
   //       fTruePrimaryPhotonPtDCAzBins[i]->Write();
   //       //fTrueSecondaryPhotonPtDCAzBins[i]->Scale(1./fTrueSecondaryPhotonPtDCAzBins[i]->GetEntries());
   //       fTrueSecondaryPhotonPtDCAzBins[i]->Write();
   //       //fTrueSecondaryPhotonFromXFromK0sPtDCAzBins[i]->Scale(1./fTrueSecondaryPhotonFromXFromK0sPtDCAzBins[i]->GetEntries());
   //       fTrueSecondaryPhotonFromXFromK0sPtDCAzBins[i]->Write();
   //       //fTrueBackgroundPtDCAzBins[i]->Scale(1./fTrueBackgroundPtDCAzBins[i]->GetEntries());
   //       fTrueBackgroundPtDCAzBins[i]->Write();
   //       //fTrueGammaPtDCAzBins[i]->Scale(1./fTrueGammaPtDCAzBins[i]->GetEntries());
   //       fTrueGammaPtDCAzBins[i]->Write();
   //       //fTrueSubGammaPtDCAzBins[i]->Scale(1./fTrueSubGammaPtDCAzBins[i]->GetEntries());
   //       fTrueSubGammaPtDCAzBins[i]->Write();
   //    }
   //    if(!isMC){
   //       //fESDGammaPtDCAzBins[i]->Scale(1./fESDGammaPtDCAzBins[i]->GetEntries());
   //       fESDGammaPtDCAzBins[i]->Write();
   //       //fESDGammaPtDCAzBinsBack[i]->Scale(1./fESDGammaPtDCAzBinsBack[i]->GetEntries());
   //       fESDGammaPtDCAzBinsBack[i]->Write();
   //       //fESDSubGammaPtDCAzBins[i]->Scale(1./fESDSubGammaPtDCAzBins[i]->GetEntries());
   //       fESDSubGammaPtDCAzBins[i]->Write();
   //    }
   // }

   Output1->Write();
   Output1->Close();
}
void PlotAdditionalDCAz(Int_t isMC, TString fCutID)
{

   gStyle->SetOptTitle(0);

   TString nameInputMC = Form("%s/%s/%s_MC_GammaConvV1DCAHistogramms%s_%s.root",fCutSelection.Data(),fEnergyFlag.Data(),fPrefix.Data(),fPeriodFlag.Data(),fCutID.Data());
   TFile *InputMC = new TFile(nameInputMC);
   if (InputMC->IsZombie()) InputMC = NULL;

   TString nameInputData = Form("%s/%s/%s_data_GammaConvV1DCAHistogramms%s_%s.root",fCutSelection.Data(),fEnergyFlag.Data(),fPrefix.Data(),fPeriodFlag.Data(),fCutID.Data());
   TFile *InputData = new TFile(nameInputData);
   if (InputData->IsZombie()) InputData = NULL;


   TH2D *ESDGammaPtDCAzAll;
   TH2D *ESDGammaPtDCAzAllperEvent;
   TH1D *ESDGammaDCAzBack;
   TH1D *ESDGammaDCAzBackperEvent;
   TH1D *ESDGammaDCAzAll;
   TH1D *ESDGammaDCAzAllperEvent;
   TH1D *ESDGammaDCAzAllSub;
   TH1D *ESDGammaDCAzAllSubperEvent;

   // Plot Data
   if(!isMC && InputData){
      
      ESDGammaPtDCAzAll = (TH2D*)InputData->Get("ESD_GammaPtDCAz_all");
      ESDGammaPtDCAzAllperEvent = (TH2D*)InputData->Get("ESD_GammaPtDCAz_all_perEvent");
      ESDGammaDCAzBack = (TH1D*)InputData->Get("ESD_GammaPtDCAzBackBin_Full");
      ESDGammaDCAzBackperEvent = (TH1D*)InputData->Get("ESD_GammaPtDCAzBackBin_Full_perEvent");
      ESDGammaDCAzAllSub = (TH1D*)InputData->Get("ESD_GammaDCAz_all_Subtracted");
      ESDGammaDCAzAllSubperEvent = (TH1D*)InputData->Get("ESD_GammaDCAz_all_Subtracted_perEvent");
     
      ESDGammaDCAzAll = (TH1D*)ESDGammaPtDCAzAll->ProjectionY();
      ESDGammaDCAzAllperEvent = (TH1D*)ESDGammaPtDCAzAllperEvent->ProjectionY();

      DrawGammaSetMarker(ESDGammaDCAzAll, 23, 1.0, kBlack, kBlack);
      DrawGammaSetMarker(ESDGammaDCAzAllperEvent, 23, 1.0, kBlack, kBlack);
      DrawGammaSetMarker(ESDGammaDCAzBack, 23, 1.0, kRed, kRed);
      DrawGammaSetMarker(ESDGammaDCAzBackperEvent, 23, 1.0, kRed, kRed);
      DrawGammaSetMarker(ESDGammaDCAzAllSub, 23, 1.0, kOrange+5, kOrange+5);
      DrawGammaSetMarker(ESDGammaDCAzAllSubperEvent, 23, 1.0,  kOrange+5, kOrange+5);

      TCanvas *canvasDCAzData = GetAndSetCanvas("canvasDCAzData");
      canvasDCAzData->SetLogy();

      SetHistogramm(ESDGammaDCAzAll,"Distance Prim Vtx (cm)","DCA z");
      SetHistogramm(ESDGammaDCAzAllperEvent,"Distance Prim Vtx (cm)","DCA z (per Event)");
      SetHistogramm(ESDGammaDCAzBack,"Distance Prim Vtx (cm)","DCA z");
      SetHistogramm(ESDGammaDCAzBackperEvent,"Distance Prim Vtx (cm)","DCA z (per Event)");
      SetHistogramm(ESDGammaDCAzAllSub,"Distance Prim Vtx (cm)","DCA z");
      SetHistogramm(ESDGammaDCAzAllSubperEvent,"Distance Prim Vtx (cm)","DCA z (per Event)");
   
      ESDGammaDCAzAll->DrawCopy();
      ESDGammaDCAzBack->DrawCopy("same");
      ESDGammaDCAzAllSub->DrawCopy("same");

      TLegend* legendDCAZData = GetAndSetLegend(0.6,0.75,3,1);
      legendDCAZData->AddEntry(ESDGammaDCAzAll,"DCA z","lp");
      legendDCAZData->AddEntry(ESDGammaDCAzBack,"Estimated Pile-Up Bckg","lp");
      legendDCAZData->AddEntry(ESDGammaDCAzAllSub,"Subtracted Pile-Up Bckg","lp");

      legendDCAZData->Draw();


      canvasDCAzData->Print(Form("%s/%s_data_ESD_DCAz_%s.%s",fOutputDir.Data(),fPrefix.Data(),fCutSelection.Data(),fSuffix.Data()));
      delete canvasDCAzData;

      TCanvas *canvasDCAzDataPerEvent = GetAndSetCanvas("canvasDCAzDataPerEvent");
      canvasDCAzDataPerEvent->SetLogy();
      
  
      ESDGammaDCAzAllperEvent->DrawCopy();
      ESDGammaDCAzBackperEvent->DrawCopy("same");
      ESDGammaDCAzAllSubperEvent->DrawCopy("same");

      legendDCAZData->Draw();

      canvasDCAzDataPerEvent->Print(Form("%s/%s_data_ESD_DCAz_PerEvent_%s.%s",fOutputDir.Data(),fPrefix.Data(),fCutSelection.Data(),fSuffix.Data()));
      delete legendDCAZData;
   }

   TH2D *ESDMCGammaPtDCAzAll;
   TH2D *ESDMCGammaPtDCAzAllperEvent;
   TH1D *ESDMCGammaDCAzBack;
   TH1D *ESDMCGammaDCAzBackperEvent;
   TH2D *TruePrimaryGammaPtDCAzAll;
   TH2D *TruePrimaryGammaPtDCAzAllperEvent;
   TH2D *TrueSecondaryGammaPtDCAzAll;
   TH2D *TrueSecondaryGammaPtDCAzAllperEvent;
   TH2D *TrueSecondaryFromXFromK0sGammaPtDCAzAll;
   TH2D *TrueSecondaryFromXFromK0sGammaPtDCAzAllperEvent;
   TH1D *ESDMCGammaDCAzAll;
   TH1D *ESDMCGammaDCAzAllperEvent;
   TH1D *TruePrimaryGammaDCAzAll;
   TH1D *TruePrimaryGammaDCAzAllperEvent;
   TH1D *TrueSecondaryGammaDCAzAll;
   TH1D *TrueSecondaryGammaDCAzAllperEvent;
   TH1D *TrueSecondaryFromXFromK0sGammaDCAzAll;
   TH1D *TrueSecondaryFromXFromK0sGammaDCAzAllperEvent;
   TH1D *ESDMCGammaBackgroundDCAzAll;
   TH1D *ESDMCGammaBackgroundDCAzAllperEvent;

   if(isMC && InputMC){
      
      ESDMCGammaPtDCAzAll = (TH2D*)InputMC->Get("ESDMC_GammaPtDCAz_all");
      ESDMCGammaPtDCAzAllperEvent = (TH2D*)InputMC->Get("ESDMC_GammaPtDCAz_all_perEvent");
      ESDMCGammaDCAzBack = (TH1D*)InputMC->Get("ESDMC_GammaPtDCAzBackBin_Full");
      ESDMCGammaDCAzBackperEvent = (TH1D*)InputMC->Get("ESDMC_GammaPtDCAzBackBin_Full_perEvent");

      TruePrimaryGammaPtDCAzAll = (TH2D*)InputMC->Get("ESD_TruePrimaryGammaPtDCAz_all");
      TruePrimaryGammaPtDCAzAllperEvent = (TH2D*)InputMC->Get("ESD_TruePrimaryGammaPtDCAz_all_perEvent");
      TrueSecondaryGammaPtDCAzAll = (TH2D*)InputMC->Get("ESD_TrueSecondaryGammaPtDCAz_all");
      TrueSecondaryGammaPtDCAzAllperEvent = (TH2D*)InputMC->Get("ESD_TrueSecondaryGammaPtDCAz_all_perEvent");
      TrueSecondaryFromXFromK0sGammaPtDCAzAll = (TH2D*)InputMC->Get("ESD_TrueSecondaryGammaFromXFromK0sDCAz_all");
      TrueSecondaryFromXFromK0sGammaPtDCAzAllperEvent = (TH2D*)InputMC->Get("ESD_TrueSecondaryGammaFromXFromK0sDCAz_all_perEvent");
     
      ESDMCGammaDCAzAll = (TH1D*)ESDMCGammaPtDCAzAll->ProjectionY();
      ESDMCGammaDCAzAllperEvent = (TH1D*)ESDMCGammaPtDCAzAllperEvent->ProjectionY();
      TruePrimaryGammaDCAzAll = (TH1D*)TruePrimaryGammaPtDCAzAll->ProjectionY();
      TruePrimaryGammaDCAzAllperEvent = (TH1D*)TruePrimaryGammaPtDCAzAllperEvent->ProjectionY();
      TrueSecondaryGammaDCAzAll = (TH1D*)TrueSecondaryGammaPtDCAzAll->ProjectionY();
      TrueSecondaryGammaDCAzAllperEvent = (TH1D*)TrueSecondaryGammaPtDCAzAllperEvent->ProjectionY();
      TrueSecondaryFromXFromK0sGammaDCAzAll = (TH1D*)TrueSecondaryFromXFromK0sGammaPtDCAzAll->ProjectionY();
      TrueSecondaryFromXFromK0sGammaDCAzAllperEvent = (TH1D*)TrueSecondaryFromXFromK0sGammaPtDCAzAllperEvent->ProjectionY();

      ESDMCGammaBackgroundDCAzAll = (TH1D*)ESDMCGammaDCAzAll->Clone("ESD_TrueGammaBackgroundDCAz_all");
      
      ESDMCGammaBackgroundDCAzAll->Add(TruePrimaryGammaDCAzAll,-1);
      //ESDMCGammaBackgroundDCAzAll->Add(TrueSecondaryGammaDCAzAll,-1);

      ESDMCGammaBackgroundDCAzAllperEvent = (TH1D*)ESDMCGammaDCAzAllperEvent->Clone("ESD_TrueGammaBackgroundDCAz_all");
      ESDMCGammaBackgroundDCAzAllperEvent->Add(TruePrimaryGammaDCAzAllperEvent,-1);
      //ESDMCGammaBackgroundDCAzAllperEvent->Add(TrueSecondaryGammaDCAzAllperEvent,-1);

      TrueSecondaryGammaDCAzAll->Add(TrueSecondaryFromXFromK0sGammaDCAzAll,-1);
      TrueSecondaryGammaDCAzAllperEvent->Add(TrueSecondaryFromXFromK0sGammaDCAzAllperEvent,-1);

      DrawGammaSetMarker(ESDMCGammaDCAzAll, 23, 1.0, kYellow+1, kYellow+1);
      DrawGammaSetMarker(ESDMCGammaDCAzAllperEvent, 23, 1.0, kYellow+1, kYellow+1);
      DrawGammaSetMarker(ESDMCGammaDCAzBack, 23, 1.0, kRed, kRed);
      DrawGammaSetMarker(ESDMCGammaDCAzBackperEvent, 23, 1.0, kRed, kRed);
      DrawGammaSetMarker(TruePrimaryGammaDCAzAll, 23, 1.0, kBlue+1, kBlue+1);
      DrawGammaSetMarker(TruePrimaryGammaDCAzAllperEvent, 23, 1.0, kBlue+1, kBlue+1);
      DrawGammaSetMarker(TrueSecondaryGammaDCAzAll, 23, 1.0, kCyan+2, kCyan+2);
      DrawGammaSetMarker(TrueSecondaryGammaDCAzAllperEvent, 23, 1.0, kCyan+2, kCyan+2);
      DrawGammaSetMarker(TrueSecondaryFromXFromK0sGammaDCAzAll, 23, 1.0, kViolet+2, kViolet+2);
      DrawGammaSetMarker(TrueSecondaryFromXFromK0sGammaDCAzAllperEvent, 23, 1.0, kViolet+2, kViolet+2);
      DrawGammaSetMarker(ESDMCGammaBackgroundDCAzAll, 23, 1.0, kGreen+2, kGreen+2);
      DrawGammaSetMarker(ESDMCGammaBackgroundDCAzAllperEvent, 23, 1.0, kGreen+2, kGreen+2);


      TCanvas *canvasDCAzMC = GetAndSetCanvas("canvasDCAzMC");
      canvasDCAzMC->SetLogy();

      SetHistogramm(ESDMCGammaDCAzAll,"Distance Prim Vtx (cm)","DCA z (per Event)");
      SetHistogramm(ESDMCGammaDCAzAllperEvent,"Distance Prim Vtx (cm)","DCA z (per Event)");
      SetHistogramm(ESDMCGammaDCAzBack,"Distance Prim Vtx (cm)","DCA z");
      SetHistogramm(ESDMCGammaDCAzBackperEvent,"Distance Prim Vtx (cm)","DCA z (per Event)");
      SetHistogramm(TruePrimaryGammaDCAzAll,"Distance Prim Vtx (cm)","DCA z");
      SetHistogramm(TruePrimaryGammaDCAzAllperEvent,"Distance Prim Vtx (cm)","DCA z (per Event)");
      SetHistogramm(TrueSecondaryGammaDCAzAll,"Distance Prim Vtx (cm)","DCA z");
      SetHistogramm(TrueSecondaryGammaDCAzAllperEvent,"Distance Prim Vtx (cm)","DCA z (per Event)");
      SetHistogramm(TrueSecondaryFromXFromK0sGammaDCAzAll,"Distance Prim Vtx (cm)","DCA z (per Event)");
      SetHistogramm(TrueSecondaryFromXFromK0sGammaDCAzAllperEvent,"Distance Prim Vtx (cm)","DCA z (per Event)");
      SetHistogramm(ESDMCGammaBackgroundDCAzAll,"Distance Prim Vtx (cm)","DCA z (per Event)");
      SetHistogramm(ESDMCGammaBackgroundDCAzAllperEvent,"Distance Prim Vtx (cm)","DCA z (per Event)");
          
      ESDMCGammaDCAzAll->DrawCopy();
      ESDMCGammaBackgroundDCAzAll->DrawCopy("same");
      ESDMCGammaDCAzBack->DrawCopy("same");
      TruePrimaryGammaDCAzAll->DrawCopy("same");
      TrueSecondaryGammaDCAzAll->DrawCopy("same");
      TrueSecondaryFromXFromK0sGammaDCAzAll->DrawCopy("same");

      TLegend* legendDCAZMC = GetAndSetLegend(0.6,0.65,6,1);
      legendDCAZMC->AddEntry(ESDMCGammaDCAzAll,"DCA z","lp");
      legendDCAZMC->AddEntry(ESDMCGammaDCAzBack,"Estimated Pile-Up Bckg","lp");
      legendDCAZMC->AddEntry(ESDMCGammaBackgroundDCAzAll,"Background + Secondary #gamma","lp");
      legendDCAZMC->AddEntry(TruePrimaryGammaDCAzAll,"True Primary #gamma","lp");
      legendDCAZMC->AddEntry(TrueSecondaryFromXFromK0sGammaDCAzAll,"True Secondary #gamma from K_{s}^{0}","lp");
      legendDCAZMC->AddEntry(TrueSecondaryGammaDCAzAll,"Additional Secondary #gamma","lp");      
      legendDCAZMC->Draw();


      canvasDCAzMC->Print(Form("%s/%s_MC_ESDMC_DCAz_%s.%s",fOutputDir.Data(),fPrefix.Data(),fCutSelection.Data(),fSuffix.Data()));
      delete canvasDCAzMC;

      TCanvas *canvasDCAzMCPerEvent = GetAndSetCanvas("canvasDCAzMCPerEvent");
      canvasDCAzMCPerEvent->SetLogy();
      TLegend* legendDCAZMCperEvent = GetAndSetLegend(0.6,0.65,5,1,"MC");
      TLegend* legendDCAZperEvent = GetAndSetLegend(0.15,0.85,1,1,"Data");
      if(InputData){
         ESDGammaDCAzAllSubperEvent = (TH1D*)InputData->Get("ESD_GammaDCAz_all_Subtracted_perEvent");
         DrawGammaSetMarker(ESDGammaDCAzAllSubperEvent, 23, 1.0,  kBlack, kBlack);
         SetHistogramm(ESDGammaDCAzAllSubperEvent,"Distance Prim Vtx (cm)","DCA z (per Event)",1e-8,5e-2);
         ESDGammaDCAzAllSubperEvent->DrawCopy("");
         ESDMCGammaDCAzAllperEvent->DrawCopy("same");
         legendDCAZperEvent->AddEntry(ESDGammaDCAzAllSubperEvent,"DCA z (Pile-Up Subtracted)","lp");
      }
      else ESDMCGammaDCAzAllperEvent->DrawCopy("");

      ESDMCGammaBackgroundDCAzAllperEvent->DrawCopy("same");
      ESDMCGammaDCAzBackperEvent->DrawCopy("same");
      TruePrimaryGammaDCAzAllperEvent->DrawCopy("same");
      TrueSecondaryGammaDCAzAllperEvent->DrawCopy("same");
      TrueSecondaryFromXFromK0sGammaDCAzAllperEvent->DrawCopy("same");

      legendDCAZMCperEvent->AddEntry(ESDMCGammaDCAzAllperEvent,"DCA z","lp");
      legendDCAZMCperEvent->AddEntry(ESDMCGammaDCAzBackperEvent,"Estimated Pile-Up Bckg","lp");
      legendDCAZMCperEvent->AddEntry(ESDMCGammaBackgroundDCAzAllperEvent,"Background + Secondary #gamma","lp");
      legendDCAZMCperEvent->AddEntry(TruePrimaryGammaDCAzAllperEvent,"True Primary #gamma","lp");
      legendDCAZMCperEvent->AddEntry(TrueSecondaryFromXFromK0sGammaDCAzAllperEvent,"True Secondary #gamma from K_{s}^{0}","lp");
      legendDCAZMCperEvent->AddEntry(TrueSecondaryGammaDCAzAllperEvent,"Additional Secondary #gamma","lp");      
      legendDCAZMCperEvent->Draw();
      legendDCAZperEvent->Draw();
      canvasDCAzMCPerEvent->Print(Form("%s/%s_MC_ESDMC_DCAz_PerEvent_%s.%s",fOutputDir.Data(),fPrefix.Data(),fCutSelection.Data(),fSuffix.Data()));
      delete canvasDCAzMCPerEvent;
      
   }

   TH1D *RatioWithWithoutPileUpData;
   TH1D *RatioWithWithoutPileUpMC;

   if(InputMC && InputData){
      RatioWithWithoutPileUpData = (TH1D*)InputData->Get("RatioWithWithoutPileUp");
      RatioWithWithoutPileUpMC = (TH1D*)InputMC->Get("RatioWithWithoutPileUp");
      
      DrawGammaSetMarker(RatioWithWithoutPileUpData, 20, 1.0, kBlack, kBlack);
      DrawGammaSetMarker(RatioWithWithoutPileUpMC, 20, 1.0, kRed, kRed);

      TCanvas *canvasComparisonWithWithoutPileUp = GetAndSetCanvas("canvasComparisonWithWithoutPileUp");
      TLegend* legendComparisonWithWithoutPileUp = GetAndSetLegend(0.3,0.75,2.4,1);
      legendComparisonWithWithoutPileUp->AddEntry(RatioWithWithoutPileUpData,"#gamma / #gamma Pile-Up Cor. data","lp");
      legendComparisonWithWithoutPileUp->AddEntry(RatioWithWithoutPileUpMC,"#gamma / #gamma Pile-Up Cor. MC","lp");

      RatioWithWithoutPileUpData->DrawCopy();
      RatioWithWithoutPileUpMC->DrawCopy("same");

      legendComparisonWithWithoutPileUp->Draw();

      canvasComparisonWithWithoutPileUp->Print(Form("%s/%s_PileUpComparisonMCDate_%s.%s",fOutputDir.Data(),fPrefix.Data(),fCutSelection.Data(),fSuffix.Data()));
      delete canvasComparisonWithWithoutPileUp;
   }
   
   gStyle->SetOptTitle(1);
}
   
   
void PlotDCAzInPtBinsWitchack(TH1D** ESDGammaPtDCAzBins, TH1D** ESDGammaPtDCAzBinsBack,TH1D** ESDGammaPtDCAzBinsBackB, TString namePlot, TString nameCanvas, TString namePad, Double_t* dcazRange, TString dateDummy, TString fMesonType,  Int_t fRowPlot, Int_t fColumnPlot, Int_t fStartBinPtRange, Int_t fNumberPtBins, Double_t* fRangeBinsPt, TString fDecayChannel, Bool_t fMonteCarloInfo, TString decayChannel, TString textCent){
   TGaxis::SetMaxDigits(3);

   TCanvas * canvasDataSpectra = new TCanvas(nameCanvas.Data(),"",2800,1800);  // gives the page size
   canvasDataSpectra->SetTopMargin(0.02);
   canvasDataSpectra->SetBottomMargin(0.02);
   canvasDataSpectra->SetRightMargin(0.02);
   canvasDataSpectra->SetLeftMargin(0.02);

   TPad * padDataSpectra = new TPad(namePad.Data(),"",0.0,0.0,1.,1.,0);   // gives the size of the histo areas
   padDataSpectra->SetFillColor(0);
   padDataSpectra->GetFrame()->SetFillColor(0);
   padDataSpectra->SetBorderMode(0);
   padDataSpectra->SetLogy(1);
   padDataSpectra->Divide(fColumnPlot,fRowPlot);
   padDataSpectra->Draw();

   Double_t relWidthLogo;
   if (fMesonType.CompareTo("Pi0") == 0){
      relWidthLogo=0.3;
   } else {
      relWidthLogo=0.3;
   }
   Double_t padXWidth = 2800/fColumnPlot;
   Double_t padYWidth = 1800/fRowPlot;

   cout<<"fColumnPlot: "<<fColumnPlot<<" fRowPlot: "<<fRowPlot<<endl;

   Int_t place = 0;
   for(Int_t iPt=fStartBinPtRange;iPt<fNumberPtBins;iPt++){
      cout<<"Pt: "<<iPt<<" of "<<fNumberPtBins<<endl;
      
      place = place + 1;						//give the right place in the page
      if (place == fColumnPlot){
         iPt--;
         padDataSpectra->cd(place);
         padDataSpectra->cd(place)->SetLogy();
         padDataSpectra->cd(place)->SetTopMargin(0.12);
         padDataSpectra->cd(place)->SetBottomMargin(0.15);
         padDataSpectra->cd(place)->SetRightMargin(0.05);
         padDataSpectra->cd(place)->SetLeftMargin(0.15);

         string textAlice = "ALICE performance";
         string textEvents;
         if(fMonteCarloInfo){textEvents = "MC";}
         else {textEvents = "Data";}
         Double_t textHeight = 0.055;
         Double_t startTextX = 0.0;
         Double_t startTextY = 0.75;
         Double_t differenceText = textHeight*1.25;
         Double_t widthLogoPix = padXWidth*relWidthLogo;
         Double_t heightLogoPix= widthLogoPix/0.73447;
         Double_t coordinatesStartPadX = 0.3;
         Double_t coordinatesStartPadY = 0.0;
         Double_t coordinatesEndPadX = (coordinatesStartPadX*padXWidth+widthLogoPix)/padXWidth;
         Double_t coordinatesEndPadY = (coordinatesStartPadY*padYWidth+heightLogoPix)/padYWidth;

         TLatex *alice = new TLatex(startTextX,(startTextY+(2*differenceText)),Form("%s",textAlice.c_str()));
         TLatex *energy = new TLatex(startTextX,(startTextY-differenceText),"RAW DATA");
         TLatex *process = new TLatex(startTextX, (startTextY+differenceText), fDecayChannel);
         //TLatex *events = new TLatex(startTextX,startTextY,Form("%s: %2.1e %s events",textEvents.c_str(), fNEvents, textCent.Data()));
         TLatex *latexDate = new TLatex(startTextX,startTextY-(2*differenceText),dateDummy.Data());
         TPad *myPadLogo = new TPad("myPadLogo", "Pad for ALICE Logo", coordinatesStartPadX, coordinatesStartPadY, coordinatesEndPadX ,coordinatesEndPadY, -1, -1, -2);

         alice->SetNDC();
         alice->SetTextColor(2);
         alice->SetTextSize(textHeight);
         alice->Draw();

         energy->SetNDC();
         energy->SetTextColor(1);
         energy->SetTextSize(textHeight);
         energy->Draw();

         process->SetNDC(kTRUE);
         process->SetTextSize(textHeight);
         process->Draw();

         /* events->SetNDC(); */
         /* events->SetTextColor(1); */
         /* events->SetTextSize(textHeight); */
         /* events->Draw(); */

         latexDate->SetNDC();
         latexDate->SetTextColor(1);
         latexDate->SetTextSize(textHeight);
         latexDate->Draw();


         myPadLogo->SetFillColor(0);
         myPadLogo->SetFrameFillColor(0);
         myPadLogo->SetBorderMode(0);
         myPadLogo->SetBorderSize(0);
         myPadLogo->SetFrameBorderMode(0);
         myPadLogo->SetLeftMargin(0.0);
         myPadLogo->SetTopMargin(0.0);
         myPadLogo->SetBottomMargin(0.0);
         myPadLogo->SetRightMargin(0.0);
         TASImage *myAliceLogo = new TASImage("ALICE_logo.eps");
         myPadLogo->Draw();
         myPadLogo->cd();
         myAliceLogo->Draw();
      } else {

         padDataSpectra->cd(place);
         padDataSpectra->cd(place)->SetLogy();
         padDataSpectra->cd(place)->SetTopMargin(0.12);
         padDataSpectra->cd(place)->SetBottomMargin(0.15);
         padDataSpectra->cd(place)->SetRightMargin(0.05);
         padDataSpectra->cd(place)->SetLeftMargin(0.15);

         ESDGammaPtDCAzBins[iPt]->SetTitle(Form("Pt %.1f - %.1f",fRangeBinsPt[iPt],fRangeBinsPt[iPt+1]));
         ESDGammaPtDCAzBinsBack[iPt]->SetTitle(Form("Pt %.1f - %.1f",fRangeBinsPt[iPt],fRangeBinsPt[iPt+1]));

         ESDGammaPtDCAzBins[iPt]->SetLineColor(kBlack);
         ESDGammaPtDCAzBins[iPt]->SetMarkerColor(kBlack);
         ESDGammaPtDCAzBinsBack[iPt]->SetLineColor(kRed);
         ESDGammaPtDCAzBinsBack[iPt]->SetMarkerColor(kRed);

         ESDGammaPtDCAzBins[iPt]->DrawCopy();
         ESDGammaPtDCAzBinsBack[iPt]->DrawCopy("same");
         if(ESDGammaPtDCAzBinsBackB){
            ESDGammaPtDCAzBinsBackB[iPt]->SetLineColor(kBlue+2);
            ESDGammaPtDCAzBinsBackB[iPt]->SetMarkerColor(kBlue+2);
            ESDGammaPtDCAzBinsBackB[iPt]->DrawCopy("same");
         }



      }
   }
   canvasDataSpectra->Print(namePlot.Data());
   delete padDataSpectra;
   delete canvasDataSpectra;

}
