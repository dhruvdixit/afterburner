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
#include "TRandom2.h"
#include "TRandom3.h"
#include "TLatex.h"
#include "TASImage.h"
#include "TPostScript.h"
#include "TGraphErrors.h"
#include "TGraph.h"
#include "TArrow.h"
#include "TMarker.h"
#include "TGraphAsymmErrors.h"
#include "../CommonHeaders/PlottingGammaConversionHistos.h"
#include "../CommonHeaders/PlottingGammaConversionAdditional.h"
#include "CalculateGammaToPi0.h"
#include "../CommonHeaders/FittingGammaConversion.h"
#include "../CommonHeaders/ConversionFunctionsBasicsAndLabeling.h"
#include "../CommonHeaders/ConversionFunctions.h"
#include "../CommonHeaders/ExtractSignalBinning.h"
#include "TMath.h"
#include "TSpline.h"

extern TRandom *gRandom;
extern TBenchmark *gBenchmark;
extern TSystem *gSystem;


//-----------------------------------------------------------------------------
Double_t Hagedorn(Double_t *x, Double_t *p)
{
   Double_t hagd = p[0]/TMath::TwoPi()/TMath::Power((1.+x[0]/p[1]/p[2]),p[2]);
   return hagd;
}
//-----------------------------------------------------------------------------
Double_t Exponent(Double_t *x, Double_t *p)
{
   Double_t expo = p[0]*TMath::Exp(-x[0]/p[1]);
   return expo;
}
Double_t FitSpectrum(Double_t *x, Double_t *p)
{
   // Double_t hagd = p[0]*(p[2]-1)*(p[2]-2)/p[1]/p[2]/TMath::TwoPi()/TMath::Power((1.+x[0]/p[1]/p[2]),p[2]);
   Double_t hagd = p[0]/TMath::TwoPi()/TMath::Power((1.+x[0]/p[1]/p[2]),p[2]);
   Double_t expo = p[3]*TMath::Exp(-x[0]/p[4]);
   return hagd+expo;
}


void  CalculateGammaToPi0(TString nameFileGamma = "",TString nameFilePi0 = "",  TString cutSel = "", TString suffix = "gif", TString nameMeson = "", TString isMC ="", TString option="", TString conference="", Int_t mode = 9){

   conference = " ";

   gROOT->Reset();
   gSystem->Load("libCore.so");
   gSystem->Load("libTree.so");
   gSystem->Load("libGeom.so");
   gSystem->Load("libVMC.so");
   gSystem->Load("libPhysics.so");
   gSystem->Load("libMinuit.so");
   gSystem->Load("libSTEERBase");
   gSystem->Load("libESD");
   gSystem->Load("libAOD");
   gSystem->Load("libANALYSIS");
   gSystem->Load("libANALYSISalice");
   gSystem->Load("libCORRFW.so");
   gSystem->Load("libPWGGAGammaConv.so");
   // gSystem->Load("libRooFit") ;
   // using namespace RooFit ;

   gROOT->SetStyle("Plain");
   gStyle->SetOptStat(0);   //gStyle->SetOptFit(1111);
   gStyle->SetOptTitle(0);
   gStyle->SetErrorX(0);

   cout<<Form("%s/%s/%s/GammaToPi0",cutSel.Data(),option.Data(),suffix.Data())<<endl;
   outputDir = Form("%s/%s/%s/GammaToPi0",cutSel.Data(),option.Data(),suffix.Data());
   gSystem->Exec("mkdir "+outputDir);


   // TDatime	now;
   // int		iDate = now.GetDate();
   // int		iYear=iDate/10000;
   // int		iMonth=(iDate%10000)/100;
   // int		iDay=iDate%100;
   // TString	cMonth[12]={"Jan","Feb","Mar","Apr","May","Jun",
   //      		    "Jul","Aug","Sep","Oct","Nov","Dec"};
	TString fEventCutSelection="";
	TString fGammaCutSelection="";
	TString fClusterCutSelection="";
	TString fElectronCutSelection="";
	TString fMesonCutSelection="";
	
	TString fCutSelection = cutSel;
	if (mode == 9){
		ReturnSeparatedCutNumber(fCutSelection, fGammaCutSelection, fElectronCutSelection,fMesonCutSelection);
		fEventCutSelection = fGammaCutSelection(0,7);
		fGammaCutSelection = fGammaCutSelection(7,fGammaCutSelection.Length()-7);
		cout << fEventCutSelection.Data() << "\t" << fGammaCutSelection.Data() << endl;
	} else {
		ReturnSeparatedCutNumberAdvanced(fCutSelection,fEventCutSelection, fGammaCutSelection, fClusterCutSelection, fElectronCutSelection, fMesonCutSelection, mode);
	}

 
   TString centralityCutNumberLow = fEventCutSelection(GetEventCentralityMinCutPosition(),1);
   TString centralityCutNumberHigh = fEventCutSelection(GetEventCentralityMaxCutPosition(),1);
   TString centralityCutNumberfife = fEventCutSelection(GetEventSystemCutPosition(),1);
   Int_t centCutNumberI  = centralityCutNumberLow.Atoi();
   Int_t centCutNumberBI  = centralityCutNumberHigh.Atoi();
   Int_t fife  = centralityCutNumberfife.Atoi();

   TString extraSignals(fEventCutSelection(GetEventRejectExtraSignalsCutPosition(),1));
   TString centrality = GetCentralityString(fEventCutSelection);
   FindCocktailFile(fEventCutSelection,centrality,option);
   TString centralityQM = fEventCutSelection(GetEventCentralityMinCutPosition(),2);


   // TString textDayth;
   // if (iDay%10 == 1){
   //    textDayth = "st";
   // } else if (iDay%10 == 2){
   //    textDayth = "nd";
   // } else if (iDay%10 == 3){
   //    textDayth = "rd";
   // } else {
   //    textDayth = "th";
   // }

   // TString textDate = Form("%i^{%s} %s %i",iDay, textDayth.Data(),cMonth[iMonth-1].Data(), iYear);


   textPi0New = Form("Gamma_%s",nameMeson.Data());

   if (isMC.CompareTo("kTRUE") == 0){
      textPrefix2 = "recMC";
      pictDrawingOptions[1] = kTRUE;
   } else {
      textPrefix2 = "data";
      pictDrawingOptions[1] = kFALSE;
   }

   TString mesonType;
   if ((nameMeson.CompareTo("Pi0") == 0) || (nameMeson.CompareTo("Pi0EtaBinning") == 0)){
      Meson_text = "#pi^{0}";
      pictDrawingOptions[3] = kTRUE;
      mesonType = "Pi0";
   } else {
      pictDrawingOptions[3] = kFALSE;
      Meson_text = "#eta";
      mesonType = "Eta";
   }

   One = new TF1("One","1",0,25);
   One->SetLineWidth(1.2);
   One->SetLineColor(1);

   fileGamma = new TFile(nameFileGamma);
   //histoGammaSpecCorrPurity = (TH1D*)fileGamma->Get("CorrGammaSpecPurityMinusSec");
   //histoGammaSpecCorrPurity = (TH1D*)fileGamma->Get("CorrGammaSpecPurity");

   // histoGammaSpecCorrPurity = (TH1D*)fileGamma->Get("CorrGammaSpecPurityMinusSecPileUpNoMCUpdate");
   //histoGammaSpecCorrPurity = (TH1D*)fileGamma->Get("CorrGammaSpecPurityMinusSecPileUp");
   //histoGammaSpecCorrPurity = (TH1D*)fileGamma->Get("GammaUnfoldPileUp");
   histoGammaSpecCorrPurity = (TH1D*)fileGamma->Get("GammaUnfold");
   if(!option.CompareTo("PbPb_2.76TeV")){
      if(centCutNumberI>3)histoGammaSpecCorrPurity = (TH1D*)fileGamma->Get("GammaUnfoldPileUp");
      else histoGammaSpecCorrPurity = (TH1D*)fileGamma->Get("GammaUnfold");
      //    //histoGammaSpecCorrPurity = (TH1D*)fileGamma->Get("CorrGammaSpecPurityMinusSec");
      //    //histoGammaSpecCorrPurity = (TH1D*)fileGamma->Get("GammaUnfold");ockcocktail
      //    //histoGammaSpecCorrPurity = (TH1D*)fileGamma->Get("GammaUnfoldPileUp");
      //    //histoGammaSpecCorrPurity = (TH1D*)fileGamma->Get("CorrGammaSpecPurityMinusSecPileUp");
   }

   histoGammaSpecMCAll = (TH1D*)fileGamma->Get("GammaSpecMC");
   histoGammaSpecCorrESDMC = (TH1D*)fileGamma->Get("GammaSpecCorrESDMC");
   histoMCDecaySumGammaPt = (TH1D*)fileGamma->Get("MC_DecaySumGammaPt");
   histoMCDecayPi0GammaPt = (TH1D*)fileGamma->Get("MC_DecayGammaPi0_Pt");
   histoMCDecayEtaGammaPt = (TH1D*)fileGamma->Get("MC_DecayGammaEta_Pt");
   histoMCDecayEtapGammaPt = (TH1D*)fileGamma->Get("MC_DecayGammaEtap_Pt");
   histoMCDecayOmegaGammaPt = (TH1D*)fileGamma->Get("MC_DecayGammaOmega_Pt");
   histoMCDecayRho0GammaPt = (TH1D*)fileGamma->Get("MC_DecayGammaRho_Pt");
   histoMCDecayPhiGammaPt = (TH1D*)fileGamma->Get("MC_DecayGammaPhi_Pt");
   //histoMCDecaySigmaGammaPt = (TH1D*)fileGamma->Get("MC_DecayGammaSigma_Pt");
   histMCAllMinusDecay = (TH1D*) fileGamma->Get("MC_Direct_or_All_Minus_Decay");

   filePi0 = new TFile(nameFilePi0);
   histoCorrectedYieldNormalEff = (TH1D*)filePi0->Get("CorrectedYieldNormEff");


   if(option.CompareTo("PbPb_2.76TeV") == 0){
      //histoCorrectedYieldTrueEff = (TH1D*)filePi0->Get("CorrectedYieldTrueEffBackFit");
      histoCorrectedYieldTrueEffWide = (TH1D*)filePi0->Get("CorrectedYieldTrueEffWide");
      histoCorrectedYieldTrueEffNarrow = (TH1D*)filePi0->Get("CorrectedYieldTrueEffNarrow");
      histoCorrectedYieldTrueEff = (TH1D*)filePi0->Get("CorrectedYieldTrueEff");
   }
   else{
      cout<<"---------------------------------------!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!-----------------------------------------"<<endl;
      histoCorrectedYieldTrueEff = (TH1D*)filePi0->Get("CorrectedYieldTrueEff");
      histoCorrectedYieldTrueEffWide = (TH1D*)filePi0->Get("CorrectedYieldTrueEffWide");
      histoCorrectedYieldTrueEffNarrow = (TH1D*)filePi0->Get("CorrectedYieldTrueEffNarrow");
   }

   // TFile *hhhh = new TFile("/home/martin/Pi0_data_GammaConvV1Correction_501000103209297002322000000_01523045009000.root");
   // TH1D *pi0fredi = (TH1D*)hhhh->Get("CorrectedYieldTrueEff");


   // pi0fredi = RebinTH1D(pi0fredi,histoCorrectedYieldTrueEff);

   // pi0fredi->Divide(histoCorrectedYieldTrueEff,pi0fredi,1,1,"B");

   // pi0fredi->Draw();


   // return;
   // Comparsion To PHOS IncGamma

   //TFile *PhosGamma = new TFile("PHOS_gamma_PbPb_18112013.root");
   // TFile *PhosPi0 = new TFile("PHOS_pi0_PbPb_18112013.root");


   // // // // cent0 = 0-5
   // // // // cent1 = 5-10
   // // // // cent2 = 10-20
   // // // // cent3 = 20-40
   // // // // cent4 = 40-60
   // // // // cent5 = 60-80
   // // // // cent6 = 0-20
   // // // // cent7 = 0-10


   //TH1D *phosGammaSpec = (TH1D*)PhosGamma->Get("hGamma_PbPb_cen6_Stat");
   // histoGammaSpecCorrPurity = phosGammaSpec;
   //phosGammaSpec = RebinTH1D(phosGammaSpec,histoGammaSpecCorrPurity);
   
   //histoGammaSpecCorrPurity->Draw("same");
   // phosGammaSpec->Draw("same");
   // ConversionFitPHOS->Draw("same");

   // TH1D *phosPi0Spec = (TH1D*)PhosPi0->Get("hPi0_PbPb_cen6_NoBW_Stat");_
   // histoCorrectedYieldTrueEff = phosPi0Spec;

   // phosPi0Spec = RebinTH1D(phosPi0Spec,histoCorrectedYieldTrueEff);
   // histoCorrectedYieldTrueEff = RebinTH1D(histoCorrectedYieldTrueEff,phosPi0Spec);

   // phosGammaSpec->Divide(phosPi0Spec);
   // //phosGammaSpec->Divide(histoGammaSpecCorrPurity);
   // // histoGammaSpecCorrPurity->Divide(phosGammaSpec);
   // // histoCorrectedYieldTrueEff->Divide(phosPi0Spec);
   // histoGammaSpecCorrPurity->Divide(histoCorrectedYieldTrueEff);


   // histoGammaSpecCorrPurity->Divide(phosGammaSpec);



   // TCanvas *ComPhos = GetAndSetCanvas("PHOS");

   // SetHistogramm(histoGammaSpecCorrPurity, "#it{p}_{T} (GeV/#it{c})", "#frac{#gamma}{#pi^{0}}_{PCM}/#frac{#gamma}{#pi^{0}}_{PHOS}",0.0,2.0);
   // DrawGammaSetMarker(histoGammaSpecCorrPurity, 20, 1.5, kRed+2, kRed+2);

   // histoGammaSpecCorrPurity->Draw("e1");
   // One->Draw("same");


   // //histoCorrectedYieldTrueEff->Draw("same");

   // DrawSystem(0.13,0.15,option.Data(),centrality);

   // ComPhos->Print(Form("%s/%s_GammaOverPi0_PCMoverPHOS_%s_%s_%s.%s",outputDir.Data(),textPi0New.Data(),textPrefix2.Data(),cutSel.Data(),fGammaCutSelection.Data(),suffix.Data()));
   // return;
   // //

   histoMCYieldMeson = (TH1D*)filePi0->Get("MCYield_Meson");
   histoMCYieldMesonOldBin = (TH1D*)filePi0->Get("MCYield_Meson_oldBin");

   histoIncRatioPurity = (TH1D*) histoGammaSpecCorrPurity->Clone("Rec_IncRatioPurity");
   histoIncRatioPurity->Divide(histoIncRatioPurity,histoCorrectedYieldNormalEff,1,1,"");

   histoIncRatioPurityTrueEff = (TH1D*) histoGammaSpecCorrPurity->Clone("IncRatioPurity_trueEff");
   histoIncRatioPurityTrueEff->Divide(histoIncRatioPurityTrueEff,histoCorrectedYieldTrueEff,1,1,"");

   histoIncRatioPurityTrueEff->Draw();

   histoIncRatioPurityTrueEffWide = (TH1D*) histoGammaSpecCorrPurity->Clone("IncRatioPurity_trueEffWide");
   histoIncRatioPurityTrueEffWide->Divide(histoIncRatioPurityTrueEffWide,histoCorrectedYieldTrueEffWide,1,1,"");

   histoIncRatioPurityTrueEffNarrow = (TH1D*) histoGammaSpecCorrPurity->Clone("IncRatioPurity_trueEffNarrow");
   histoIncRatioPurityTrueEffNarrow->Divide(histoIncRatioPurityTrueEffNarrow,histoCorrectedYieldTrueEffNarrow,1,1,"");

   histoMCIncRatio = (TH1D*) histoGammaSpecMCAll->Clone("MC_IncRatio");
   histoMCIncRatio->Divide(histoGammaSpecMCAll,histoMCYieldMeson,1,1,"");

   histoMCesdIncRatio = (TH1D*) histoGammaSpecCorrESDMC->Clone("MCesd_IncRatio");
   histoMCesdIncRatio->Divide(histoGammaSpecCorrESDMC,histoMCYieldMeson,1,1,"");

   histoIncRatioGammaMC = (TH1D*) histoGammaSpecMCAll->Clone("MC_MCGamma_DataPi0_IncRatio");
   histoIncRatioGammaMC->Divide(histoIncRatioGammaMC,histoCorrectedYieldNormalEff,1,1,"");

   // MC Data Ratios
   histoTruePi0MCData = (TH1D*) histoMCYieldMeson->Clone("TruePi0MCData");
   histoTruePi0MCData->Divide(histoCorrectedYieldTrueEff);

   histoNormalPi0MCData = (TH1D*) histoMCYieldMeson->Clone("NormalPi0MCData");
   histoNormalPi0MCData->Divide(histoCorrectedYieldNormalEff);

   histoPurityGammaMCData = (TH1D*) histoGammaSpecMCAll->Clone("PurityGammaMCData");
   histoPurityGammaMCData->Divide(histoGammaSpecCorrPurity);

   //MC Decay Ratios
   histoDecayRatioSumGamma = (TH1D*) histoMCDecaySumGammaPt->Clone();
   histoDecayRatioSumGamma->SetName("MC_DecayRatio_SumGamma");
   histoDecayRatioSumGamma->Divide(histoMCDecaySumGammaPt,histoMCYieldMesonOldBin,1,1,"");

   histoDecayRatioPi0Gamma = (TH1D*) histoMCDecayPi0GammaPt->Clone();
   histoDecayRatioPi0Gamma->SetName("MC_DecayRatio_Pi0Gamma");
   histoDecayRatioPi0Gamma->Divide(histoMCDecayPi0GammaPt,histoMCYieldMesonOldBin,1,1,"");

   histoDecayRatioEtaGamma = (TH1D*) histoMCDecayEtaGammaPt->Clone();
   histoDecayRatioEtaGamma->SetName("MC_DecayRatio_EtaGamma");
   histoDecayRatioEtaGamma->Divide(histoMCDecayEtaGammaPt,histoMCYieldMesonOldBin,1,1,"");

   histoDecayRatioEtapGamma = (TH1D*) histoMCDecayEtapGammaPt->Clone();
   histoDecayRatioEtapGamma->SetName("MC_DecayRatio_EtapGamma");
   histoDecayRatioEtapGamma->Divide(histoMCDecayEtapGammaPt,histoMCYieldMesonOldBin,1,1,"");

   histoDecayRatioOmegaGamma = (TH1D*) histoMCDecayOmegaGammaPt->Clone();
   histoDecayRatioOmegaGamma->SetName("MC_DecayRatio_OmegaGamma");
   histoDecayRatioOmegaGamma->Divide(histoMCDecayOmegaGammaPt,histoMCYieldMesonOldBin,1,1,"");

   histoDecayRatioRho0Gamma = (TH1D*) histoMCDecayRho0GammaPt->Clone();
   histoDecayRatioRho0Gamma->SetName("MC_DecayRatio_Rho0Gamma");
   histoDecayRatioRho0Gamma->Divide(histoMCDecayRho0GammaPt,histoMCYieldMesonOldBin,1,1,"");

   histoDecayRatioPhiGamma = (TH1D*) histoMCDecayPhiGammaPt->Clone();
   histoDecayRatioPhiGamma->SetName("MC_DecayRatio_PhiGamma");
   histoDecayRatioPhiGamma->Divide(histoMCDecayPhiGammaPt,histoMCYieldMesonOldBin,1,1,"");

   // histoDecayRatioSigmaGamma = (TH1D*) histoMCDecaySigmaGammaPt->Clone();
   // histoDecayRatioSigmaGamma->SetName("MC_DecayRatio_SigmaGamma");
   // histoDecayRatioSigmaGamma->Divide(histoMCDecaySigmaGammaPt,histoMCYieldMesonOldBin,1,1,"");


   //**********************************************************************************
   //******************** NLO Calculatins Ratio ***************************************
   //**********************************************************************************

   // Get the NLO Results
   if(option.CompareTo("7TeV") == 0){
      xSection = xSection7TeV;
      fileNameNLOPhotonHalf = "ExternalInput/Theory/ALICENLOcalcDirectPhoton7TeVmuhalf.dat";
      fileNameNLOPhotonOne = "ExternalInput/Theory/ALICENLOcalcDirectPhoton7TeVmu.dat";
      fileNameNLOPhotonTwo = "ExternalInput/Theory/ALICENLOcalcDirectPhoton7TeVtwomu.dat";
   }
   if(option.CompareTo("PbPb_2.76TeV") == 0 || option.CompareTo("2.76TeV") == 0){
      xSection = xSection2760GeV;
      fileNameNLOPhotonHalf = "ExternalInput/Theory/ALICENLOcalcDirectPhoton2760GeVmuhalf.dat";
      fileNameNLOPhotonOne = "ExternalInput/Theory/ALICENLOcalcDirectPhoton2760GeVmu.dat";
      fileNameNLOPhotonTwo = "ExternalInput/Theory/ALICENLOcalcDirectPhoton2760GeVtwomu.dat";
   }
   if(option.CompareTo("900GeV") == 0){
      xSection = xSection900GeV;
      fileNameNLOPhotonHalf = "ExternalInput/Theory/ALICENLOcalcDirectPhoton2760GeVmu.dat";
      fileNameNLOPhotonOne = "ExternalInput/Theory/ALICENLOcalcDirectPhoton2760GeVmu.dat";
      fileNameNLOPhotonTwo = "ExternalInput/Theory/ALICENLOcalcDirectPhoton2760GeVmu.dat";
   }
   if(option.CompareTo("pPb_5.023TeV") == 0){
      xSection = xSection7TeV;
      fileNameNLOPhotonHalf = "ExternalInput/Theory/ALICENLOcalcDirectPhoton7TeVmuhalf.dat";
      fileNameNLOPhotonOne = "ExternalInput/Theory/ALICENLOcalcDirectPhoton7TeVmu.dat";
      fileNameNLOPhotonTwo = "ExternalInput/Theory/ALICENLOcalcDirectPhoton7TeVtwomu.dat";
   }

   inHalf.open(fileNameNLOPhotonHalf,ios_base::in);
   cout << fileNameNLOPhotonHalf << endl;


   Double_t etascaling = 1./1.6;
   etascaling = 1.;

   while(!inHalf.eof()){
      nlinesNLOHalf++;

      //               Pt                              DirectPhoton           FragmentationPhoton         SumPhoton
      inHalf >> ptNLOPhotonHalf[nlinesNLOHalf] >> muHalfD[nlinesNLOHalf] >> muHalfF[nlinesNLOHalf] >> muHalfDF[nlinesNLOHalf];
      muHalfF[nlinesNLOHalf]=muHalfF[nlinesNLOHalf]/xSection/recalcBarn*fcmult*(etascaling);
      muHalfDF[nlinesNLOHalf] = muHalfDF[nlinesNLOHalf]/xSection/recalcBarn*fcmult*(etascaling);
      muHalfD[nlinesNLOHalf] = muHalfD[nlinesNLOHalf]/xSection/recalcBarn*fcmult*(etascaling);

   }
   inHalf.close();

   inOne.open(fileNameNLOPhotonOne,ios_base::in);
   cout << fileNameNLOPhotonOne << endl;

   while(!inOne.eof()){
      nlinesNLOOne++;
      inOne >> ptNLOPhotonOne[nlinesNLOOne] >> muOneD[nlinesNLOOne] >> muOneF[nlinesNLOOne] >> muOneDF[nlinesNLOOne];
      muOneF[nlinesNLOOne]=muOneF[nlinesNLOOne]/xSection/recalcBarn*fcmult*(etascaling);
      muOneDF[nlinesNLOOne] = muOneDF[nlinesNLOOne]/xSection/recalcBarn*fcmult*(etascaling);
      muOneD[nlinesNLOOne] = muOneD[nlinesNLOOne]/xSection/recalcBarn*fcmult*(etascaling);

   }
   inOne.close();

   inTwo.open(fileNameNLOPhotonTwo,ios_base::in);
   cout << fileNameNLOPhotonTwo << endl;

   while(!inTwo.eof()){
      nlinesNLOTwo++;
      inTwo >> ptNLOPhotonTwo[nlinesNLOTwo] >> muTwoD[nlinesNLOTwo] >> muTwoF[nlinesNLOTwo] >> muTwoDF[nlinesNLOTwo];
      muTwoF[nlinesNLOTwo]=muTwoF[nlinesNLOTwo]/xSection/recalcBarn*fcmult*(etascaling);
      muTwoDF[nlinesNLOTwo] = muTwoDF[nlinesNLOTwo]/xSection/recalcBarn*fcmult*(etascaling);
      muTwoD[nlinesNLOTwo] = muTwoD[nlinesNLOTwo]/xSection/recalcBarn*fcmult*(etascaling);
   }
   inTwo.close();

   TCanvas *NLOCalculationcanvas = GetAndSetCanvas("NLOCalculationcanvas");
   DrawGammaCanvasSettings( NLOCalculationcanvas, 0.1, 0.015, 0.01, 0.09);
   TPad* padNLOHistos = new TPad("padNLOHistos", "", 0., 0.25, 1., 1.,-1, -1, -2);
   DrawGammaPadSettings( padNLOHistos, 0.10, 0.015, 0.01, 0.);
   padNLOHistos->Draw();
   TPad* padNLORatios = new TPad("padNLORatios", "", 0., 0., 1., 0.25,-1, -1, -2);
   DrawGammaPadSettings( padNLORatios, 0.1, 0.015, 0.0, 0.35);
   padNLORatios->Draw();

   padNLOHistos->cd();
   padNLOHistos->SetLogy();

   SetHistogramm(histoMCDecaySumGammaPt,"#it{p}_{T} (GeV/#it{c})","#frac{1}{2#pi N_{ev.}} #frac{d^{2}N}{#it{p}_{T}d#it{p}_{T}dy} (GeV^{-2}c)",5e-12,250);
   histoMCDecaySumGammaPt->Draw();
   histoGammaSpecCorrPurity->Draw("");
   graphNLOCalcMuHalf = new TGraphErrors(nlinesNLOHalf,ptNLOPhotonHalf,muHalfDF,0,0);
   graphNLOCalcMuHalf->SetName("graphNLOCalcMuHalf");
   graphNLOCalcMuHalf->SetTitle("graphNLOCalcMuHalf");
   graphNLOCalcMuHalf->GetYaxis()->SetRangeUser(0.1e-12,1);
   DrawGammaSetMarkerTGraph(graphNLOCalcMuHalf, 24, 1., kRed+2, kRed+2);
   //      Double_t paramGraphNLOMuHalf[3] = {0.1,3.4,0.5};
   fitNLOMuHalf = FitObject("m","fitNLOMuHalf","Pi0",graphNLOCalcMuHalf,2.,25.);//,paramGraphNLOMuHalf);
   DrawGammaSetMarkerTF1( fitNLOMuHalf, 8, 2.0, kBlue+2);
   fitNLOMuHalf->Draw("same");
   graphNLOCalcMuHalf->Draw("p,same");
   graphNLOCalcMuOne = new TGraphErrors(nlinesNLOOne,ptNLOPhotonOne,muOneDF,0,0);
   graphNLOCalcMuOne->SetName("graphNLOCalcMuOne");
   DrawGammaSetMarkerTGraph(graphNLOCalcMuOne, 27, 1., kRed, kRed);
   //   Double_t paramGraphNLOMuOne[3] = {0.1,0.37,5.1};
   //Double_t paramGraphNLOMuOne[3] = {0.1,3.5,0.5};
   fitNLOMuOne = FitObject("m","fitNLOMuOne","Pi0",graphNLOCalcMuOne,2.,25.);//,paramGraphNLOMuOne);
   DrawGammaSetMarkerTF1( fitNLOMuOne, 8, 2.0, kBlue);
   fitNLOMuOne->Draw("same");
   graphNLOCalcMuOne->Draw("p,same");

   graphNLOCalcMuTwo = new TGraphErrors(nlinesNLOTwo,ptNLOPhotonTwo,muTwoDF,0,0);
   graphNLOCalcMuTwo->SetName("graphNLOCalcMuTwo");
   DrawGammaSetMarkerTGraph(graphNLOCalcMuTwo, 30, 1., kRed-2, kRed-2);
   //  Double_t paramGraphNLOMuTwo[3] = {0.1,0.37,5.1};
   //Double_t paramGraphNLOMuTwo[3] = {0.1,3.5,0.5};
   fitNLOMuTwo = FitObject("m","fitNLOMuTwo","Pi0",graphNLOCalcMuTwo,2.,25.);//,paramGraphNLOMuTwo);
   DrawGammaSetMarkerTF1( fitNLOMuTwo, 8, 2.0, kBlue-2);
   fitNLOMuTwo->Draw("same");
   graphNLOCalcMuTwo->Draw("p,same");
   //   histMCAllMinusDecay->Draw("same");

   TLegend* leg_NLOCalculationcanvas = GetAndSetLegend(0.5,0.7,5);
   leg_NLOCalculationcanvas->AddEntry(graphNLOCalcMuHalf,"Direct Photon NLO Calc #mu = #it{p}_{T}/2","lep");
   leg_NLOCalculationcanvas->AddEntry(graphNLOCalcMuOne,"Direct Photon NLO Calc #mu = #it{p}_{T}","lep");
   leg_NLOCalculationcanvas->AddEntry(graphNLOCalcMuTwo,"Direct Photon NLO Calc #mu = 2#it{p}_{T}","lep");
   leg_NLOCalculationcanvas->AddEntry(histMCAllMinusDecay,"Not Decay Photons from MC");
   leg_NLOCalculationcanvas->AddEntry(histoMCDecaySumGammaPt,"Decay Photons from MC");
   leg_NLOCalculationcanvas->AddEntry(histoGammaSpecCorrPurity,"Inclusive Photons from data");
   leg_NLOCalculationcanvas->Draw();

   padNLORatios->cd();
   padNLORatios->SetLogy();


   histRatioNLOMuHalf = (TH1D*) histoMCDecaySumGammaPt->Clone("histRatioNLOMuHalf");
   histRatioNLOMuOne = (TH1D*) histoMCDecaySumGammaPt->Clone("histRatioNLOMuOne");
   histRatioNLOMuTwo = (TH1D*) histoMCDecaySumGammaPt->Clone("histRatioNLOMuTwo");

   histRatioNLOMuHalf = CalculateHistoRatioToFitNLO(histRatioNLOMuHalf,fitNLOMuHalf,2.);
   histRatioNLOMuOne = CalculateHistoRatioToFitNLO(histRatioNLOMuOne,fitNLOMuOne,2.);
   histRatioNLOMuTwo = CalculateHistoRatioToFitNLO(histRatioNLOMuTwo,fitNLOMuTwo,2.);


   SetHistogramm(histRatioNLOMuHalf,"#it{p}_{T} (GeV/#it{c})","#frac{Decay #gamma}{NLO Direct #gamma}",1e2,5e4);
   SetHistogramm(histRatioNLOMuOne,"#it{p}_{T} (GeV/#it{c})","#frac{Decay #gamma}{NLO Direct #gamma}",1e2,5e4);
   SetHistogramm(histRatioNLOMuTwo,"#it{p}_{T} (GeV/#it{c})","#frac{Decay #gamma}{NLO Direct #gamma}",1e2,5e4);


   histRatioNLOMuHalf->GetYaxis()->CenterTitle(kTRUE);
   histRatioNLOMuOne->GetYaxis()->CenterTitle(kTRUE);
   histRatioNLOMuTwo->GetYaxis()->CenterTitle(kTRUE);
   histRatioNLOMuHalf->GetYaxis()->SetTitleSize(0.1);
   histRatioNLOMuHalf->GetYaxis()->SetTitleOffset(0.4);
   histRatioNLOMuHalf->GetYaxis()->CenterTitle(kTRUE);

   DrawGammaSetMarker(histRatioNLOMuHalf, 24, 0.5, kRed+2, kRed+2);
   histRatioNLOMuHalf->Draw();
   DrawGammaSetMarker(histRatioNLOMuOne, 27, 0.5, kRed, kRed);
   histRatioNLOMuOne->Draw("e1,same");
   DrawGammaSetMarker(histRatioNLOMuTwo, 30, 0.5, kRed-2, kRed-2);
   histRatioNLOMuTwo->Draw("e1,same");

   NLOCalculationcanvas->Print(Form("%s/%s_NLOCalculations_%s_%s_%s.%s",outputDir.Data(),textPi0New.Data(),textPrefix2.Data(),cutSel.Data(),fGammaCutSelection.Data(),suffix.Data()));


   graphNLOCalcMuHalfRebin = RebinNLOGraph(graphNLOCalcMuHalf);
   graphNLOCalcMuOneRebin = RebinNLOGraph(graphNLOCalcMuOne);
   graphNLOCalcMuTwoRebin = RebinNLOGraph(graphNLOCalcMuTwo);


   histNLOCalcMuTwoRebin = GraphToHist(graphNLOCalcMuTwoRebin,25,"histNLOCalcMuTwoRebin");
   histNLOCalcMuOneRebin = GraphToHist(graphNLOCalcMuOneRebin,25,"histNLOCalcMuOneRebin");
   histNLOCalcMuHalfRebin = GraphToHist(graphNLOCalcMuHalfRebin,25,"histNLOCalcMuHalfRebin");


   //**********************************************************************************
   //***************************** New NLO ********************************************
   //**********************************************************************************



   if(!option.CompareTo("PbPb_2.76TeV")){

      TFile *NPDFnloFile = new TFile("ExternalInputPbPb/PbPb276MartinPDFerr.root");
      TFile *PDFnloFile = new TFile("ExternalInputPbPb/pp276MartinPDFerr.root");
      TFile *NPDFnloFileScaleErr = new TFile("ExternalInputPbPb/PbPb276MartinScaleIndep.root");
      TFile *PDFnloFileScaleErr = new TFile("ExternalInputPbPb/pp276MartinScaleerr.root");


      PbPb276CTEQ61EPS09BFG2_sum_pdferr = (TGraphAsymmErrors*)NPDFnloFile->Get("PbPb276CTEQ61EPS09BFG2_sum_pdferr");
      PbPb276CTEQ61EPS09BFG2_sum_pdferr_InvYield = (TGraphAsymmErrors*)PbPb276CTEQ61EPS09BFG2_sum_pdferr->Clone("PbPb276CTEQ61EPS09BFG2_sum_pdferr_InvYield");
      
      PbPb276EPS09BFG2_sum_scale = (TGraphAsymmErrors*)NPDFnloFileScaleErr->Get("PbPb276EPS09BFG2_sum_scalevarIndep");
      PbPb276EPS09BFG2_sum_scale_InvYield = (TGraphAsymmErrors*)PbPb276EPS09BFG2_sum_scale->Clone("PbPb276EPS09BFG2_sum_scalevarIndep_InvYield");

      pp276CT10BFG2_sum_pdferr = (TGraphAsymmErrors*)PDFnloFile->Get("pp276CT10BFG2_sum_pdferr");
      pp276CT10BFG2_sum_pdferr_InvYield = (TGraphAsymmErrors*)pp276CT10BFG2_sum_pdferr->Clone("pp276CT10BFG2_sum_pdferr_InvYield");

      pp276CT10BFG2_sum_scale = (TGraphAsymmErrors*)PDFnloFileScaleErr->Get("pp276CT10BFG2_sum_scalevar");
      pp276CT10BFG2_sum_scale_InvYield = (TGraphAsymmErrors*)pp276CT10BFG2_sum_scale->Clone("pp276CT10BFG2_sum_pdferr_InvYield");

      PbPb276CTEQ61EPS09BFG2_sum_pdferr_InvYield = ScaleGraph(PbPb276CTEQ61EPS09BFG2_sum_pdferr,1./xSection/recalcBarn*fcmult);
      pp276CT10BFG2_sum_pdferr_InvYield = ScaleGraph(pp276CT10BFG2_sum_pdferr,1./xSection/recalcBarn*fcmult);

      PbPb276EPS09BFG2_sum_scale_InvYield = ScaleGraph(PbPb276EPS09BFG2_sum_scale,1./xSection/recalcBarn*fcmult);
      pp276CT10BFG2_sum_scale_InvYield = ScaleGraph(pp276CT10BFG2_sum_scale,1./xSection/recalcBarn*fcmult);
      
      // for(Int_t i = 0;i<PbPb276CTEQ61EPS09BFG2_sum_pdferr_InvYield->GetN();i++){
      //    Double_t yerrlow1 = PbPb276CTEQ61EPS09BFG2_sum_pdferr_InvYield->GetErrorYlow(i);
      //    Double_t yerrlow2 = PbPb276EPS09BFG2_sum_scale_InvYield->GetErrorYlow(i);
      //    Double_t yerrhigh1 = PbPb276CTEQ61EPS09BFG2_sum_pdferr_InvYield->GetErrorYhigh(i);
      //    Double_t yerrhigh2 = PbPb276EPS09BFG2_sum_scale_InvYield->GetErrorYhigh(i);
      //    Double_t xerrlow = PbPb276EPS09BFG2_sum_scale_InvYield->GetErrorXhigh(i);

      //    PbPb276CTEQ61EPS09BFG2_sum_pdferr_InvYield->SetPointError(i,xerrlow,xerrlow,
      //                                                              sqrt(yerrlow1*yerrlow1+ yerrlow2*yerrlow2),
      //                                                              sqrt(yerrhigh1*yerrhigh1+ yerrhigh2*yerrhigh2));
         
      // }

      // for(Int_t i = 0;i<pp276CT10BFG2_sum_scale_InvYield->GetN();i++){
      //    Double_t yerrlow1 = pp276CT10BFG2_sum_scale_InvYield->GetErrorYlow(i);
      //    Double_t yerrlow2 = pp276CT10BFG2_sum_scale_InvYield->GetErrorYlow(i);
      //    Double_t yerrhigh1 = pp276CT10BFG2_sum_scale_InvYield->GetErrorYhigh(i);
      //    Double_t yerrhigh2 = pp276CT10BFG2_sum_scale_InvYield->GetErrorYhigh(i);
      //    Double_t xerrlow = pp276CT10BFG2_sum_scale_InvYield->GetErrorXhigh(i);

      //    pp276CT10BFG2_sum_scale_InvYield->SetPointError(i,xerrlow,xerrlow,
      //                                                              sqrt(yerrlow1*yerrlow1+ yerrlow2*yerrlow2),
      //                                                              sqrt(yerrhigh1*yerrhigh1+ yerrhigh2*yerrhigh2));
         
      // }
   }



   //**********************************************************************************
   //******************** Inclusive Ratio *********************************************
   //**********************************************************************************
   TCanvas* canvasIncRatioPurity = GetAndSetCanvas("canvasIncRatioPurity");
   SetHistogramm(histoIncRatioPurity, "#it{p}_{T} (GeV/#it{c})", "Ratio Inclusive #gamma/#pi^{0}",0,2);
   DrawGammaSetMarker(histoIncRatioPurity, 20, 2.0, 1, 1);
   histoIncRatioPurity->Draw();


   if(option.CompareTo("PbPb_2.76TeV") == 0) DrawCentrality(0.8,0.9,centrality);
   canvasIncRatioPurity->Print(Form("%s/%s_IncRatioPurity%s_%s_%s_%s.%s",outputDir.Data(),textPi0New.Data(),centralityQM.Data(),textPrefix2.Data(),cutSel.Data(),fGammaCutSelection.Data(),suffix.Data()));

   TCanvas* canvasIncRatioPurityTrueEff = GetAndSetCanvas("canvasIncRatioPurityTrueEff");
   SetHistogramm(histoIncRatioPurityTrueEff, "#it{p}_{T} (GeV/#it{c})", "Ratio Inclusive #gamma/#pi^{0}",0,2);
   DrawGammaSetMarker(histoIncRatioPurityTrueEff, 20, 2.0, 4, 4);
   histoIncRatioPurityTrueEff->Draw();

   DrawAliceLogoAdv(0.2,0.65,"Work in Progress",option,"r",canvasIncRatioPurityTrueEff,centrality);
   canvasIncRatioPurityTrueEff->Print(Form("%s/%s_IncRatioPurity_trueEff%s_%s_%s_%s.%s",outputDir.Data(),textPi0New.Data(),centralityQM.Data(),textPrefix2.Data(),cutSel.Data(),fGammaCutSelection.Data(),suffix.Data()));


   TCanvas* canvasMCIncRatio = GetAndSetCanvas("canvasMCIncRatio");
   SetHistogramm(histoMCIncRatio, "#it{p}_{T} (GeV/#it{c})", "Ratio Inclusive #gamma/#pi^{0}",0,2);
   DrawGammaSetMarker(histoMCIncRatio, 24, 2.0, 2, 2);
   SetHistogramm(histoMCesdIncRatio, "#it{p}_{T} (GeV/#it{c})", "Ratio Inclusive #gamma/#pi^{0}",0,2);
   DrawGammaSetMarker(histoMCesdIncRatio, 20, 2.0, 3, 3);
   histoMCesdIncRatio->Draw();
   histoMCIncRatio->Draw("same");
   if(option.CompareTo("PbPb_2.76TeV") == 0) DrawCentrality(0.8,0.9,centrality);
   canvasMCIncRatio->Print(Form("%s/%s_MC_IncRatio%s_%s_%s.%s",outputDir.Data(),textPi0New.Data(),centralityQM.Data(),cutSel.Data(),fGammaCutSelection.Data(),suffix.Data()));


   TCanvas* canvasIncRatioAll = GetAndSetCanvas("canvasIncRatioAll");
   histoIncRatioPurity->Draw("e1");
   histoIncRatioPurityTrueEff->Draw("e1,same");
   histoMCIncRatio->Draw("e1,same");

   TLegend* leg_canvasIncRatioAll = GetAndSetLegend(0.18,0.7,5);
   leg_canvasIncRatioAll->AddEntry(histoIncRatioPurity,"Ratio with normal Eff Purity");
   leg_canvasIncRatioAll->AddEntry(histoIncRatioPurityTrueEff,"Ratio with true Eff Purity");
   leg_canvasIncRatioAll->AddEntry(histoMCIncRatio,"MC Ratio");
   leg_canvasIncRatioAll->Draw();
   if(option.CompareTo("PbPb_2.76TeV") == 0) DrawCentrality(0.8,0.9,centrality);
   canvasIncRatioAll->Print(Form("%s/%s_IncRatio_all%s_%s_%s_%s.%s",outputDir.Data(),textPi0New.Data(),centralityQM.Data(),textPrefix2.Data(),cutSel.Data(),fGammaCutSelection.Data(),suffix.Data()));



   //**********************************************************************************
   //********************** Charged Pions *********************************************
   //**********************************************************************************

   TFile* filePHOSPionInputPrelim2013;
   TGraphAsymmErrors *PHOS0010;

   Int_t iterations = 11;
   TFitResultPtr FitresultPHOS;
   if(!option.CompareTo("PbPb_2.76TeV")){
      filePHOSPionInputPrelim2013 = new TFile("CombinedResultsPbPb_25_Sep_2013.root");
      PHOS0010 = (TGraphAsymmErrors*) filePHOSPionInputPrelim2013->Get("InvYieldPbPbPHOSSysErr_0010");
      cout<<PHOS0010<<endl;

      ConversionFitPHOS = FitObject("qcd","ConversionFitPHOS","Pi0",PHOS0010,.9,11.);
      DrawGammaSetMarkerTF1(ConversionFitPHOS, 1, 1.8, kRed-2);
      PrintParameter(ConversionFitPHOS,"qcd","ConversionFitPHOS",7,gMinuit->fCstatu);

      for(Int_t i = 0; i<iterations; i++){
         FitresultPHOS = PHOS0010->Fit(ConversionFitPHOS, "SQNRME+", "", 0.9, 11.);
         //if(i == iterations-1 && ((gMinuit->fCstatu).CompareTo("SUCCESSFUL"))) iterations++;
      }
   }

   TFile* fileChargedPionInputPrelim2013;

   if(!option.CompareTo("PbPb_2.76TeV")){
      fileChargedPionInputPrelim2013 = new TFile("ExternalInputPbPb/IdentifiedCharged/ChargedPionSpectraPbPb_12_Nov_2013.root");//ChargedPionSpectraPbPb_4_Aug_2013.root");
      GetChargedPionsPbPb(fileChargedPionInputPrelim2013,fEventCutSelection);
      CombineChargedPions();
   }
   if(option.CompareTo("PbPb_2.76TeV")){
      fileChargedPionInputPrelim2013 = new TFile("ExternalInput/IdentifiedCharged/ChargedIdentifiedSpectraPP_12_Nov_2013.root");
      PionSummedStatHigh = (TH1D*)fileChargedPionInputPrelim2013->Get("histoChargedPionSpecHighPtStat2760GeV");
      PionSummedSystHigh = (TH1D*)fileChargedPionInputPrelim2013->Get("histoChargedPionSpecHighPtSyst2760GeV");
      PionSummedStatLow = (TH1D*)fileChargedPionInputPrelim2013->Get("histoChargedPionSpecLowPtStatPP2760GeV");
      PionSummedSystLow = (TH1D*)fileChargedPionInputPrelim2013->Get("histoChargedPionSpecLowPtSysPP2760GeV");
      CombineChargedPions();
   }

   if(option.CompareTo("PbPb_2.76TeV")){
      CombinedChargedPionsStatLow->Scale(xSection2760GeVppINEL);
      CombinedChargedPionsStatLow->Scale(1./(xSection*recalcBarn));
      CombinedChargedPionsStatHigh->Scale(xSection2760GeVppINEL);
      CombinedChargedPionsStatHigh->Scale(1./(xSection*recalcBarn));

      CombinedChargedPionsSystLow->Scale(xSection2760GeVppINEL);
      CombinedChargedPionsSystLow->Scale(1./(xSection*recalcBarn));
      CombinedChargedPionsSystHigh->Scale(xSection2760GeVppINEL);
      CombinedChargedPionsSystHigh->Scale(1./(xSection*recalcBarn));

      PionSummedStatLow->Scale(xSection2760GeVppINEL);
      PionSummedStatLow->Scale(1./(xSection*recalcBarn));
      PionSummedStatHigh->Scale(xSection2760GeVppINEL);
      PionSummedStatHigh->Scale(1./(xSection*recalcBarn));

      PionSummedSystLow->Scale(xSection2760GeVppINEL);
      PionSummedSystLow->Scale(1./(xSection*recalcBarn));
      PionSummedSystHigh->Scale(xSection2760GeVppINEL);
      PionSummedSystHigh->Scale(1./(xSection*recalcBarn));


   }



   TString fitParameterCharged = "QSNRME+";
   TString fitFuncCharged = "dmtsal";

   CombinedChargedPionsStatAverage = (TH1D*)CombinedChargedPionsStatHigh->Clone("CombinedChargedPionsAverage_stat");
   CombinedChargedPionsSystAverage = (TH1D*)CombinedChargedPionsSystHigh->Clone("CombinedChargedPionsAverage_syst");

   CombinedChargedPionsStatLow = RebinTH1D(CombinedChargedPionsStatLow,CombinedChargedPionsStatHigh);
   CombinedChargedPionsSystLow = RebinTH1D(CombinedChargedPionsSystLow,CombinedChargedPionsSystHigh);
   
   Double_t ParamsCharged[6];
   GetFitParameter(fitFuncCharged,centrality,ParamsCharged);

   for(Int_t i = 0; i<CombinedChargedPionsStatAverage->GetNbinsX(); i++){
      if(CombinedChargedPionsStatAverage->GetBinCenter(i+1)<2){
         CombinedChargedPionsStatAverage->SetBinContent(i+1,CombinedChargedPionsStatLow->GetBinContent(i+1));
         CombinedChargedPionsStatAverage->SetBinError(i+1,CombinedChargedPionsStatLow->GetBinError(i+1));

         CombinedChargedPionsSystAverage->SetBinContent(i+1,CombinedChargedPionsSystLow->GetBinContent(i+1));
         CombinedChargedPionsSystAverage->SetBinError(i+1,CombinedChargedPionsSystLow->GetBinError(i+1));

      }
      if(CombinedChargedPionsStatAverage->GetBinCenter(i+1)>2&&CombinedChargedPionsStatAverage->GetBinCenter(i+1)<3){
         CombinedChargedPionsStatAverage->SetBinContent(i+1,(CombinedChargedPionsStatLow->GetBinContent(i+1)+CombinedChargedPionsStatHigh->GetBinContent(i+1))/2);
         CombinedChargedPionsStatAverage->SetBinError(i+1,(CombinedChargedPionsStatLow->GetBinError(i+1)+CombinedChargedPionsStatHigh->GetBinError(i+1))/2);

         CombinedChargedPionsSystAverage->SetBinContent(i+1,(CombinedChargedPionsSystLow->GetBinContent(i+1)+CombinedChargedPionsSystHigh->GetBinContent(i+1))/2);
         CombinedChargedPionsSystAverage->SetBinError(i+1,(CombinedChargedPionsSystLow->GetBinError(i+1)+CombinedChargedPionsSystHigh->GetBinError(i+1))/2);

      }
      if(CombinedChargedPionsStatAverage->GetBinCenter(i+1)>3){
         CombinedChargedPionsStatAverage->SetBinContent(i+1,CombinedChargedPionsStatHigh->GetBinContent(i+1));
         CombinedChargedPionsStatAverage->SetBinError(i+1,CombinedChargedPionsStatHigh->GetBinError(i+1));

         CombinedChargedPionsSystAverage->SetBinContent(i+1,CombinedChargedPionsSystHigh->GetBinContent(i+1));
         CombinedChargedPionsSystAverage->SetBinError(i+1,CombinedChargedPionsSystHigh->GetBinError(i+1));
      }
   }

   ConversionFitPionsStatAverage = FitObject(fitFuncCharged,"FitPions Average","Pi0",CombinedChargedPionsStatAverage,.9,20.,ParamsCharged);
   TFitResultPtr FitresultChargedStatAverage;
   DrawGammaSetMarkerTF1(ConversionFitPionsStatAverage, 1, 1.8, kGreen-2);
   TString resultCombinedStatAverage = "";
   Int_t chargedIt = 3;
   for(Int_t i = 0; i<chargedIt;i++){
      cout<<"Fit Iteration "<<i<<endl;
      FitresultChargedStatAverage = CombinedChargedPionsStatAverage->Fit(ConversionFitPionsStatAverage, fitParameterCharged, "",0.9,20.);
      resultCombinedStatAverage = gMinuit->fCstatu;
      if(!resultCombinedStatAverage.CompareTo("SUCCESSFUL")) break;
      else chargedIt++;
      if(chargedIt>200) break;
   }
   cout<<"ConversionFitPionsAverage Stat "<<fitFuncCharged<<endl;
   PrintParameter(ConversionFitPionsStatAverage,fitFuncCharged,"FitPions Average Stat",7,gMinuit->fCstatu);


   //ConversionFitPionsSystAverage = FitObject(fitFuncCharged,"FitPions Average Syst","Pi0",CombinedChargedPionsSystAverage,.9,20.,ParamsCharged);
   ConversionFitPionsSystAverage = (TF1*)ConversionFitPionsStatAverage->Clone("FitPions Average Syst");

   TFitResultPtr FitresultChargedSystAverage;
   DrawGammaSetMarkerTF1(ConversionFitPionsSystAverage, 1, 1.8, kBlue-2);
   TString resultCombinedSystAverage = "";
   chargedIt = 3;
   for(Int_t i = 0; i<chargedIt;i++){
      cout<<"Fit Iteration "<<i<<endl;
      FitresultChargedSystAverage = CombinedChargedPionsSystAverage->Fit(ConversionFitPionsSystAverage, fitParameterCharged, "",0.9,20.);
      resultCombinedSystAverage = gMinuit->fCstatu;
      if(!resultCombinedSystAverage.CompareTo("SUCCESSFUL")) break;
      //if(!resultCombinedSystAverage.CompareTo("PROBLEMS  ")) break;
      else chargedIt++;
      if(chargedIt>200) break;
   }
   cout<<"ConversionFitPionsAverage Syst "<<fitFuncCharged<<endl;
   PrintParameter(ConversionFitPionsSystAverage,fitFuncCharged,"FitPions Average Syst",7,gMinuit->fCstatu);

   

   TCanvas *ChargedCanvas = GetAndSetCanvas("ChargedCanvas");
   //ChargedCanvas->SetLogy();

   DrawGammaSetMarker(CombinedChargedPionsStatHigh, 24, 1.0, kBlue-2, kBlue-2);
   DrawGammaSetMarker(CombinedChargedPionsStatLow, 24, 1.0, kRed-2, kRed-2);
   DrawGammaSetMarker(CombinedChargedPionsStatAverage, 24, 1.0, kGreen-2, kGreen-2);
   DrawGammaSetMarker(CombinedChargedPionsSystAverage, 24, 1.0, kBlue-2, kBlue-2);
   CombinedChargedPionsSystAverage->SetLineColor(kBlue-2);   
   CombinedChargedPionsStatAverage->SetLineColor(kGreen-2);
   CombinedChargedPionsSystAverage->SetFillColor(kBlue-2);   
   CombinedChargedPionsStatAverage->SetFillColor(kGreen-2);
   DrawGammaSetMarker(PionSummedStatLow, 20, 1.5, kRed-2, kRed-2);
   DrawGammaSetMarker(PionSummedStatHigh, 20, 1.5, kBlue-2, kBlue-2);
   SetHistogramm(histoCorrectedYieldTrueEff, "#it{p}_{T} (GeV/#it{c})", "#frac{1}{2#pi N_{ev.}} #frac{d^{2}N}{#it{p}_{T}d#it{p}_{T}dy} (GeV^{-2}c)");
   DrawGammaSetMarker(histoCorrectedYieldTrueEff, 24, 2.5, 1, 1);
   CombinedChargedPionsStatAverage->GetXaxis()->SetRangeUser(0,20);
   CombinedChargedPionsStatAverage->DrawCopy("");
   TLegend* leg_ChargedCanvas = GetAndSetLegend(0.13,0.11,6);
   leg_ChargedCanvas->AddEntry(histoCorrectedYieldTrueEff,"Neutral pions","pl");
   leg_ChargedCanvas->AddEntry(CombinedChargedPionsStatAverage,"Charged pions Average","pl");
   leg_ChargedCanvas->AddEntry(ConversionFitPionsStatAverage,"Fit on charged pions","l");
   leg_ChargedCanvas->AddEntry(PionSummedStatLow,"Low pT charged pions","pl");
   leg_ChargedCanvas->AddEntry(PionSummedStatHigh,"High pT charged pions","pl");
   leg_ChargedCanvas->Draw();

   TH1D *ChargeSpectrumOverFitStatAverage = (TH1D*)CombinedChargedPionsStatAverage->Clone();
   ChargeSpectrumOverFitStatAverage->Divide(ConversionFitPionsStatAverage);
   TH1D *ChargeSpectrumOverFitSystAverage = (TH1D*)CombinedChargedPionsSystAverage->Clone();
   ChargeSpectrumOverFitSystAverage->Divide(ConversionFitPionsSystAverage);


   CombinedChargedPionsStatHigh->Divide(CombinedChargedPionsStatAverage);
   CombinedChargedPionsStatLow->Divide(CombinedChargedPionsStatAverage);
   CombinedChargedPionsStatHigh->GetYaxis()->SetRangeUser(0.8,1.2);
   CombinedChargedPionsStatHigh->GetXaxis()->SetRangeUser(0.8,20);
   CombinedChargedPionsStatHigh->Draw();
   CombinedChargedPionsStatLow->Draw("same");

   ChargeSpectrumOverFitStatAverage->GetYaxis()->SetRangeUser(0.8,1.2);
   ChargeSpectrumOverFitStatAverage->GetXaxis()->SetRangeUser(0.8,20);

   CombinedChargedPionsStatAverage->Draw("e1");
   CombinedChargedPionsSystAverage->Draw("e1same");
   // ChargeSpectrumOverFitStatAverage->Draw();
   // ChargeSpectrumOverFitSystAverage->Draw("same");
   ChargedCanvas->Print(Form("%s/%s_Spectra_Charged_%s_%s_%s_%s.%s",outputDir.Data(),textPi0New.Data(),centralityQM.Data(),textPrefix2.Data(),cutSel.Data(),fGammaCutSelection.Data(),suffix.Data()));

  
   //**********************************************************************************
   //********************************* Conversion Pi0 *********************************
   //**********************************************************************************

   TCanvas* ConversionGammaCanvas = GetAndSetCanvas("ConversionGammaSpeccanvas");
   DrawGammaCanvasSettings( ConversionGammaCanvas, 0.1, 0.015, 0.01, 0.09);
   TPad* padConversionGamma = new TPad("padConversionGammaHistos", "", 0., 0.25, 1., 1.,-1, -1, -2);
   DrawGammaPadSettings( padConversionGamma, 0.10, 0.015, 0.01, 0.);
   padConversionGamma->Draw();
   TPad* padConversionGammaRatio = new TPad("padConversionGammaRatios", "", 0., 0., 1., 0.25,-1, -1, -2);
   DrawGammaPadSettings( padConversionGammaRatio, 0.1, 0.015, 0.0, 0.35);
   padConversionGammaRatio->Draw();

   padConversionGamma->cd();
   padConversionGamma->SetLogy();

   TString fitGammaA = "h";
   TString fitGammaB = "l";
   Double_t fitMaxPt = 16;
   Double_t fitMinPt = 0.3;

   if(option.CompareTo("PbPb_2.76TeV") == 0){
      if(centCutNumberI<4){
         fitGammaA  = "QCD";
         fitGammaB  = "oHag";
         fitMaxPt = 14;
      }
      else{
         fitGammaA = "ohag";
         fitGammaB = "oHag";
         fitMaxPt = 14;
      }
   }

   ConversionGammaFitA = FitObject(fitGammaA,"ConversionGammaFitA","Pi0",histoGammaSpecCorrPurity,fitMinPt,fitMaxPt);
   DrawGammaSetMarkerTF1(ConversionGammaFitA, 1, 2.0, kBlue-2);
   cout<<"CorrectedYieldTrueEff "<<fitGammaA<<endl;
   cout<<ConversionGammaFitA->GetChisquare()/ConversionGammaFitA->GetNDF()<<endl;
   cout<<ConversionGammaFitA->GetParameter(0)<<endl;
   cout<<ConversionGammaFitA->GetParameter(1)<<endl;
   cout<<ConversionGammaFitA->GetParameter(2)<<endl;
   cout<<ConversionGammaFitA->GetParameter(3)<<endl;
   cout<<ConversionGammaFitA->GetParameter(4)<<endl;
   cout<<ConversionGammaFitA->GetParameter(5)<<endl;

   ConversionGammaFitB = FitObject(fitGammaB,"ConversionGammaFitB","Pi0",histoGammaSpecCorrPurity,fitMinPt,fitMaxPt);
   DrawGammaSetMarkerTF1(ConversionGammaFitB, 2, 2.0, kRed-3);
   cout<<"CorrectedYieldTrueEff "<<fitGammaB<<endl;
   cout<<ConversionGammaFitB->GetChisquare()/ConversionGammaFitB->GetNDF()<<endl;
   cout<<ConversionGammaFitB->GetParameter(0)<<endl;
   cout<<ConversionGammaFitB->GetParameter(1)<<endl;
   cout<<ConversionGammaFitB->GetParameter(2)<<endl;
   cout<<ConversionGammaFitB->GetParameter(3)<<endl;
   cout<<ConversionGammaFitB->GetParameter(4)<<endl;
   cout<<ConversionGammaFitB->GetParameter(5)<<endl;

   ConversionGammaFitB->SetLineColor(2);
   ConversionGammaFitB->SetLineStyle(2);

   SetHistogramm(histoGammaSpecCorrPurity, "#it{p}_{T} (GeV/#it{c})", "#frac{1}{2#pi N_{ev.}} #frac{d^{2}N}{#it{p}_{T}d#it{p}_{T}dy} (GeV^{-2}c)");
   DrawGammaSetMarker(histoGammaSpecCorrPurity, 24, 2.0, kGreen-2, kGreen-2);
   histoGammaSpecCorrPurity->Draw("e1");
   ConversionGammaFitA->Draw("same");
   ConversionGammaFitB->Draw("Csame");


   TLegend* leg_ConversionGammaSpeccanvas = GetAndSetLegend(0.17,0.83,2);
   leg_ConversionGammaSpeccanvas->AddEntry(ConversionGammaFitA,fitGammaA);
   leg_ConversionGammaSpeccanvas->AddEntry(ConversionGammaFitB,fitGammaB);
   leg_ConversionGammaSpeccanvas->Draw();

   DrawAliceLogoAdv(0.8,0.4,"Work in Progress",option,"l",ConversionGammaCanvas,centrality);

   padConversionGammaRatio->cd();

   histRatioConversionGammaA = (TH1D*) histoGammaSpecCorrPurity->Clone("histRatioConversionGammaA");
   histRatioConversionGammaB = (TH1D*) histoGammaSpecCorrPurity->Clone("histRatioConversionGammaB");
   histRatioConversionGammaA = CalculateHistoRatioToFit(histRatioConversionGammaA,ConversionGammaFitA);
   histRatioConversionGammaB = CalculateHistoRatioToFit(histRatioConversionGammaB,ConversionGammaFitB);

   SetHistogramm(histRatioConversionGammaA,"#it{p}_{T} (GeV/#it{c})","#frac{Yield}{Fit}",0.5,1.9);
   DrawGammaSetMarker(histRatioConversionGammaA, 20, 1., kBlue-2, kBlue-2);
   histRatioConversionGammaA->GetYaxis()->SetTitleSize(0.1);
   histRatioConversionGammaA->GetYaxis()->SetTitleOffset(0.4);
   histRatioConversionGammaA->GetYaxis()->CenterTitle(kTRUE);
   SetHistogramm(histRatioConversionGammaB,"#it{p}_{T} (GeV/#it{c})","#frac{Yield}{Fit}",0.5,1.9);
   DrawGammaSetMarker(histRatioConversionGammaB, 24, 1., kRed-3, kRed-3);
   histRatioConversionGammaB->GetYaxis()->SetTitleSize(0.1);
   histRatioConversionGammaB->GetYaxis()->SetTitleOffset(0.4);
   histRatioConversionGammaB->GetYaxis()->CenterTitle(kTRUE);
   histRatioConversionGammaA->Draw();
   One->Draw("same");
   histRatioConversionGammaB->Draw("same");

   ConversionGammaCanvas->Print(Form("%s/%s_Spectra_ConversionGamma_%s_%s_%s_%s.%s",outputDir.Data(),textPi0New.Data(),centralityQM.Data(),textPrefix2.Data(),cutSel.Data(),fGammaCutSelection.Data(),suffix.Data()));

   TCanvas *ConversionSpeccanvas = GetAndSetCanvas("canvasPi0Fits",0.15,0.1,1000 ,1200);
   DrawGammaCanvasSettings( ConversionSpeccanvas, 0.15, 0.015, 0.01, 0.09);
   TPad* padConversionHistos = new TPad("padConversionHistos", "", 0., 0.25, 1., 1.,-1, -1, -2);
   DrawGammaPadSettings( padConversionHistos, 0.15, 0.025, 0.01, 0.);
   padConversionHistos->Draw();
   TPad* padConversionRatios = new TPad("padConversionRatios", "", 0., 0., 1., 0.25,-1, -1, -2);
   DrawGammaPadSettings( padConversionRatios, 0.15, 0.025, 0.0, 0.35);
   padConversionRatios->Draw();

   padConversionHistos->cd();
   padConversionHistos->SetLogy();
   //padConversionHistos->SetLogx();


   TString fitPi0A = "ohag";
   TString fitPi0B = "qcd";
   TString fitPi0C = "rad";


   Int_t nParam = 3;
   Double_t NN = 0.001;      // normalization
   Double_t TT = 90.;     // T, in MeV
   Double_t BB = 0.6;     // beta --> "velocity"
   Double_t xMin = .0;
   Double_t xMax = 1.;

   TF1 *FuncBWdndptPi0 = new TF1("Blast Wave Pi0",BWdndptPi0,xMin, xMax, nParam);
   FuncBWdndptPi0->SetParameters(NN, TT, BB);
   FuncBWdndptPi0->SetParNames("norm","T","beta");
   //FuncBWdndptPi0->FixParameter(0,0.0154833);
   FuncBWdndptPi0->FixParameter(1,80);
   FuncBWdndptPi0->FixParameter(2,0.66);
   FuncBWdndptPi0->SetLineColor(kSpring);

   cout<<"------------------------- Start Fitting ----------------------------"<<endl;
   cout<<"------------------------- Start Fitting ----------------------------"<<endl;
   cout<<"------------------------- Start Fitting ----------------------------"<<endl;

   histoCorrectedYieldTrueEff->Fit(FuncBWdndptPi0,"QINRME+", "");
   cout<<"BlastWave Pi0"<<endl;
   cout<<FuncBWdndptPi0->GetParameter(0)<<endl;
   cout<<FuncBWdndptPi0->GetParameter(1)<<endl;
   cout<<FuncBWdndptPi0->GetParameter(2)<<endl;


   TF1 *FuncBWdndptEta = new TF1("Blast Wave Eta",BWdndptEta,0, xMax, nParam);
   FuncBWdndptEta->SetParameters(NN, TT, BB);
   FuncBWdndptEta->SetParNames("norm","T","beta");
   FuncBWdndptEta->FixParameter(0,FuncBWdndptPi0->GetParameter(0)*2.7);
   FuncBWdndptEta->FixParameter(1,FuncBWdndptPi0->GetParameter(1));
   FuncBWdndptEta->FixParameter(2,FuncBWdndptPi0->GetParameter(2));
   FuncBWdndptEta ->SetLineColor(kBlue);

   //histoCorrectedYieldTrueEff->Fit(FuncBWdndptEta,"QNRME+", "");
   cout<<"BlastWave Eta"<<endl;
   cout<<FuncBWdndptEta->GetParameter(0)<<endl;
   cout<<FuncBWdndptEta->GetParameter(1)<<endl;
   cout<<FuncBWdndptEta->GetParameter(2)<<endl;


   fitMinPt = 0.8;
   fitMaxPt = 20;

   if(!option.CompareTo("PbPb_2.76TeV")){
      if(centCutNumberI==0 && centCutNumberBI == 2){
         fitPi0A = "dmtsal";
         fitPi0B = "dmtsal";
         fitPi0C = "dmtsal";
      }
      if(centCutNumberI==0 && centCutNumberBI == 4){
         fitPi0A = "dmtsal";
         fitPi0B = "dmtsal";
         fitPi0C = "dmtsal";
      }
      if(centCutNumberI==0 && centCutNumberBI == 1){
         fitPi0A = "dmtsal";
         fitPi0B = "dmtsal";
         fitPi0C = "dmtsal";
      }
      if(centCutNumberI==0 && centCutNumberBI == 1 && fife == 6){
         fitPi0A = "rad";
         fitPi0B = "dmtsal";
         fitPi0C = "dmtsal";
      }
      if(centCutNumberI==2 && centCutNumberBI == 4){
         fitPi0A = "dmtsal";
         fitPi0B = "dmtsal";
         fitPi0C = "dmtsal";
      }
      if(centCutNumberI==4 && centCutNumberBI == 8){
         fitPi0A = "dmtsal";
         fitPi0B = "dmtsal";
         fitPi0C = "dmtsal";
      }
      if(centCutNumberI==1 && centCutNumberBI == 2){
         fitPi0A = "dmtsal";
         fitPi0B = "dmtsal";
         fitPi0C = "dmtsal";
      }
      if(centCutNumberI==1 && centCutNumberBI == 2 && fife == 6){
         fitPi0A = "rad";
         fitPi0B = "qcd";
         fitPi0C = "oHag";
      }
   }
   else{
      fitPi0A = "dmtsal";
      fitPi0B = "dmtsal";
      fitPi0C = "dmtsal";
   }

   TString fitParameterA = "QSNRME+";
   TString fitParameterB = "QSNRME+";
   TString fitParameterC = "QSNRME+";
   Double_t Params[6];



   Double_t binsCombinedNeutralCharged[32];
   Double_t binsPbPb[32] = {0,  0.9,  1.1,  1.3,  1.5,  1.7,  1.9,  2.1,  2.3,  2.5,  2.7,  3,  3.3,  3.7,  4.1,  4.6,  5.4,  6.2,  7, 8, 11, 12,  13,  14,  15,  16,  18,  20,  22,  24, 26, 28};
   Double_t binspp2760GeV[32] = {0.0,0.4,0.6,0.8,1.0,1.2,1.4,1.6,1.8,2.0,2.2,2.4,2.6,3.0,3.5,4.0,5.0,6.0,6.5,7,8,9,10,11, 12,  13,  14,  15,  16,  18,  20,  22};
   Int_t lowEdge = 14;
   Int_t endPi0 = 8;
   if(!option.CompareTo("PbPb_2.76TeV")){
      for(Int_t i = 0;i<32;i++){
         binsCombinedNeutralCharged[i] = binsPbPb[i];
      }
      if(centCutNumberBI>2)
         lowEdge = 11;
   }
   else{
      for(Int_t i = 0;i<32;i++){
         binsCombinedNeutralCharged[i] = binspp2760GeV[i];
      }
      lowEdge = 6.5;      
      endPi0 = 6;
   }

   TH1D * CombinedNeutralAndChargedPions = new TH1D("CombinedNeutralAndChargedPions","",31,binsCombinedNeutralCharged);//29
      
   for(Int_t i = 0; i<31;i++){
      if(CombinedNeutralAndChargedPions->GetBinLowEdge(i)<=endPi0){
         CombinedNeutralAndChargedPions->SetBinContent(i,histoCorrectedYieldTrueEff->GetBinContent(i));
         CombinedNeutralAndChargedPions->SetBinError(i,histoCorrectedYieldTrueEff->GetBinError(i));
      }
      else if(CombinedNeutralAndChargedPions->GetBinLowEdge(i)>=lowEdge){
         CombinedNeutralAndChargedPions->SetBinContent(i,CombinedChargedPionsStatAverage->GetBinContent(CombinedChargedPionsStatAverage->FindBin(CombinedNeutralAndChargedPions->GetBinCenter(i))));
         CombinedNeutralAndChargedPions->SetBinError(i,CombinedChargedPionsStatAverage->GetBinError(CombinedChargedPionsStatAverage->FindBin(CombinedNeutralAndChargedPions->GetBinCenter(i))));//*i*0.5);
      }
   }

   GetFitParameter(fitPi0A,centrality,Params);
   //ConversionFitA = FitObject(fitPi0A,"ConversionFitA","Pi0",CombinedNeutralAndChargedPions,fitMinPt,fitMaxPt);
   //ConversionFitA = FitObject(fitPi0A,"ConversionFitA","Pi0",histoCorrectedYieldTrueEff,fitMinPt,fitMaxPt,Params);//, "NRME+");
   ConversionFitA = FitObject(fitPi0A,"ConversionFitA","Pi0",CombinedNeutralAndChargedPions,fitMinPt,fitMaxPt,Params);//, "NRME+");
   DrawGammaSetMarkerTF1(ConversionFitA, 1, 2.0, kBlue-2);
   ConversionFitA->SetRange(0.8,20);
   cout<<"Getting Fitter"<<endl;
   TFitResultPtr FitresultA;
   TString resultA = "";
   iterations = 11;
   for(Int_t i = 0; i<iterations;i++){
      cout<<"Fit Iteration "<<i<<endl;
      FitresultA = CombinedNeutralAndChargedPions->Fit(ConversionFitA, fitParameterA, "", fitMinPt, fitMaxPt);
      //FitresultA = histoCorrectedYieldTrueEff->Fit(ConversionFitA, fitParameterA, "", fitMinPt, fitMaxPt);
      resultA = gMinuit->fCstatu;
      if(!resultA.CompareTo("SUCCESSFUL")) break;
      else iterations++;
      if(iterations>600) break;
   }
   PrintParameter(ConversionFitA,fitPi0A,"histoCorrectedYieldTrueEff",7,gMinuit->fCstatu);
   

   //Create a histogram to hold the confidence intervals
   TH1D *hint = new TH1D("hint", 
                         "Fitted gaussian with .95 conf.band", 2000,0.9 ,20. );
   (TVirtualFitter::GetFitter())->GetConfidenceIntervals(hint);
   //Now the "hint" histogram has the fitted function values as the 
   //bin contents and the confidence intervals as bin errors
   hint->SetStats(kFALSE);
   hint->SetMarkerSize(0);
   hint->SetFillColor(kYellow);

   GetFitParameter(fitPi0B,centrality,Params);
   //ConversionFitB = FitObject(fitPi0B,"ConversionFitB","Pi0",CombinedNeutralAndChargedPions,fitMinPt,fitMaxPt);//, "NRME+");
   //ConversionFitB = FitObject(fitPi0B,"ConversionFitB","Pi0",histoCorrectedYieldTrueEff,fitMinPt,fitMaxPt,Params);//, "NRME+");
   ConversionFitB = FitObject(fitPi0B,"ConversionFitB","Pi0",CombinedNeutralAndChargedPions,fitMinPt,fitMaxPt,Params);//, "NRME+");
   DrawGammaSetMarkerTF1(ConversionFitB, 2, 2.0, kRed-3);
   ConversionFitB->SetRange(0.1,25);
   TFitResultPtr FitresultB;
   TString resultB = "";
   iterations = 11;
   for(Int_t i = 0; i<iterations;i++){
      cout<<"Fit Iteration "<<i<<endl;
      FitresultB = CombinedNeutralAndChargedPions->Fit(ConversionFitB, fitParameterB, "",fitMinPt ,fitMaxPt);
      //FitresultB = histoCorrectedYieldTrueEff->Fit(ConversionFitB, fitParameterB, "",fitMinPt ,fitMaxPt);
      resultB = gMinuit->fCstatu;
      if(!resultB.CompareTo("SUCCESSFUL")) break;
      else iterations++;
      if(iterations>600) break;
   }
   PrintParameter(ConversionFitB,fitPi0B,"histoCorrectedYieldTrueEff",7,gMinuit->fCstatu);

   GetFitParameter(fitPi0C,centrality,Params);
   //ConversionFitC = FitObject(fitPi0C,"ConversionFitC","Pi0",histoCorrectedYieldTrueEff,fitMinPt,fitMaxPt);//, "NRME+");
   ConversionFitC = FitObject(fitPi0C,"ConversionFitC","Pi0",histoCorrectedYieldTrueEff,fitMinPt,fitMaxPt,Params);//, "NRME+");
   //ConversionFitC = FitObject(fitPi0C,"ConversionFitC","Pi0",CombinedNeutralAndChargedPions,fitMinPt,fitMaxPt,Params);//, "NRME+");
   DrawGammaSetMarkerTF1(ConversionFitC, 3, 2.0, kYellow+2);
   ConversionFitC->SetRange(0.1,25);
   TFitResultPtr FitresultC;
   TString resultC = "";
   iterations = 11;
   for(Int_t i = 0; i<iterations;i++){
      cout<<"Fit Iteration "<<i<<endl;
      //FitresultC = CombinedNeutralAndChargedPions->Fit(ConversionFitC, fitParameterC, "", fitMinPt, fitMaxPt);
      FitresultC = histoCorrectedYieldTrueEff->Fit(ConversionFitC, fitParameterC, "", fitMinPt, fitMaxPt);
      resultC = gMinuit->fCstatu;
      if(!resultC.CompareTo("SUCCESSFUL")) break;
      else iterations++;
      if(iterations>600) break;
   }
   PrintParameter(ConversionFitC,fitPi0C,"histoCorrectedYieldTrueEff",7,gMinuit->fCstatu);

   TF1 *FuncBWdndptPi0Wide = new TF1("Blast Wave Pi0 Wide",BWdndptPi0,xMin, xMax, nParam);
   FuncBWdndptPi0Wide->SetParameters(NN, TT, BB);
   FuncBWdndptPi0Wide->SetParNames("norm","T","beta");
   //FuncBWdndptPi0Wide->FixParameter(0,0.0154833);
   FuncBWdndptPi0Wide->FixParameter(1,80);
   FuncBWdndptPi0Wide->FixParameter(2,0.66);
   FuncBWdndptPi0Wide->SetLineColor(kSpring);

   histoCorrectedYieldTrueEffWide->Fit(FuncBWdndptPi0Wide,"QNRME+", "");
   cout<<"BlastWave Pi0"<<endl;
   cout<<FuncBWdndptPi0Wide->GetParameter(0)<<endl;
   cout<<FuncBWdndptPi0Wide->GetParameter(1)<<endl;
   cout<<FuncBWdndptPi0Wide->GetParameter(2)<<endl;

   TF1 *FuncBWdndptEtaWide = new TF1("Blast Wave Eta",BWdndptEta,xMin, xMax, nParam);
   FuncBWdndptEtaWide->SetParameters(NN, TT, BB);
   FuncBWdndptEtaWide->SetParNames("norm","T","beta");
   FuncBWdndptEtaWide->FixParameter(0,FuncBWdndptPi0Wide->GetParameter(0)*3.3);
   FuncBWdndptEtaWide->FixParameter(1,FuncBWdndptPi0Wide->GetParameter(1));
   FuncBWdndptEtaWide->FixParameter(2,FuncBWdndptPi0Wide->GetParameter(2));
   FuncBWdndptEtaWide ->SetLineColor(kBlue);

   //histoCorrectedYieldTrueEff->Fit(FuncBWdndptEtaWide,"QNRME+", "");
   cout<<"BlastWave Eta Wide"<<endl;
   cout<<FuncBWdndptEtaWide->GetParameter(0)<<endl;
   cout<<FuncBWdndptEtaWide->GetParameter(1)<<endl;
   cout<<FuncBWdndptEtaWide->GetParameter(2)<<endl;


   TF1 *FuncBWdndptPi0Narrow = new TF1("Blast Wave Pi0 Narrow",BWdndptPi0,xMin, xMax, nParam);
   FuncBWdndptPi0Narrow->SetParameters(NN, TT, BB);
   FuncBWdndptPi0Narrow->SetParNames("norm","T","beta");
   //FuncBWdndptPi0Narrow->FixParameter(0,0.0154833);
   FuncBWdndptPi0Narrow->FixParameter(1,80);
   FuncBWdndptPi0Narrow->FixParameter(2,0.66);
   FuncBWdndptPi0Narrow->SetLineColor(kSpring);

   histoCorrectedYieldTrueEffNarrow->Fit(FuncBWdndptPi0Narrow,"QNRME+", "");
   cout<<"BlastWave Pi0 Narrow"<<endl;
   cout<<FuncBWdndptPi0Narrow->GetParameter(0)<<endl;
   cout<<FuncBWdndptPi0Narrow->GetParameter(1)<<endl;
   cout<<FuncBWdndptPi0Narrow->GetParameter(2)<<endl;

   TF1 *FuncBWdndptEtaNarrow = new TF1("Blast Wave Eta",BWdndptEta,xMin, xMax, nParam);
   FuncBWdndptEtaNarrow->SetParameters(NN, TT, BB);
   FuncBWdndptEtaNarrow->SetParNames("norm","T","beta");
   FuncBWdndptEtaNarrow->FixParameter(0,FuncBWdndptPi0Narrow->GetParameter(0)*3.3);
   FuncBWdndptEtaNarrow->FixParameter(1,FuncBWdndptPi0Narrow->GetParameter(1));
   FuncBWdndptEtaNarrow->FixParameter(2,FuncBWdndptPi0Narrow->GetParameter(2));
   FuncBWdndptEtaNarrow ->SetLineColor(kBlue);

   //histoCorrectedYieldTrueEff->Fit(FuncBWdndptEta,"QNRME+", "");
   cout<<"BlastWave Eta Narrow"<<endl;
   cout<<FuncBWdndptEtaNarrow->GetParameter(0)<<endl;
   cout<<FuncBWdndptEtaNarrow->GetParameter(1)<<endl;
   cout<<FuncBWdndptEtaNarrow->GetParameter(2)<<endl;


   TH1D * CombinedNeutralAndChargedPionsWide = new TH1D("CombinedNeutralAndChargedPionsWide","",31,binsCombinedNeutralCharged);//29
   TH1D * CombinedNeutralAndChargedPionsNarrow = new TH1D("CombinedNeutralAndChargedPionsNarrow","",31,binsCombinedNeutralCharged);//29
   


   lowEdge = 14;
   endPi0 = 8;
   if(!option.CompareTo("PbPb_2.76TeV")){
      for(Int_t i = 0;i<32;i++){
         binsCombinedNeutralCharged[i] = binsPbPb[i];
      }
      if(centCutNumberBI>2)
         lowEdge = 11;
   }
   else{
      for(Int_t i = 0;i<32;i++){
         binsCombinedNeutralCharged[i] = binspp2760GeV[i];
      }
      lowEdge = 6.5;      
      endPi0 = 6;
   }

   for(Int_t i = 0; i<31;i++){
      if(CombinedNeutralAndChargedPions->GetBinLowEdge(i)<=8){
         CombinedNeutralAndChargedPionsWide->SetBinContent(i,histoCorrectedYieldTrueEffWide->GetBinContent(i));
         CombinedNeutralAndChargedPionsWide->SetBinError(i,histoCorrectedYieldTrueEffWide->GetBinError(i));
         CombinedNeutralAndChargedPionsNarrow->SetBinContent(i,histoCorrectedYieldTrueEffNarrow->GetBinContent(i));
         CombinedNeutralAndChargedPionsNarrow->SetBinError(i,histoCorrectedYieldTrueEffNarrow->GetBinError(i));
      }
      else if(CombinedNeutralAndChargedPions->GetBinLowEdge(i)>=lowEdge){
         CombinedNeutralAndChargedPionsWide->SetBinContent(i,CombinedChargedPionsStatAverage->GetBinContent(CombinedChargedPionsStatAverage->FindBin(CombinedNeutralAndChargedPions->GetBinCenter(i))));
         CombinedNeutralAndChargedPionsWide->SetBinError(i,CombinedChargedPionsStatAverage->GetBinError(CombinedChargedPionsStatAverage->FindBin(CombinedNeutralAndChargedPions->GetBinCenter(i))));//*i*0.5);
         CombinedNeutralAndChargedPionsNarrow->SetBinContent(i,CombinedChargedPionsStatAverage->GetBinContent(CombinedChargedPionsStatAverage->FindBin(CombinedNeutralAndChargedPions->GetBinCenter(i))));
         CombinedNeutralAndChargedPionsNarrow->SetBinError(i,CombinedChargedPionsStatAverage->GetBinError(CombinedChargedPionsStatAverage->FindBin(CombinedNeutralAndChargedPions->GetBinCenter(i))));//*i*0.5);

      }
   }

   ConversionFitAWide = (TF1*) ConversionFitA->Clone("ConversionFitA Wide");
   cout<<"Getting Fitter"<<endl;
   TFitResultPtr FitresultAWide;
   TString resultAWide = "";
   iterations = 11;
   for(Int_t i = 0; i<iterations;i++){
      cout<<"Fit Iteration "<<i<<endl;
      //FitresultAWide= histoCorrectedYieldTrueEffWide->Fit(ConversionFitAWide, fitParameterA, "", fitMinPt, fitMaxPt);
      FitresultAWide = CombinedNeutralAndChargedPionsWide->Fit(ConversionFitAWide, fitParameterA, "", fitMinPt, fitMaxPt);
      resultAWide = gMinuit->fCstatu;
      if(!resultAWide.CompareTo("SUCCESSFUL")) break;
      else iterations++;
      if(iterations>200) break;
   }
   PrintParameter(ConversionFitAWide,fitPi0A,"histoCorrectedYieldTrueEff Wide",7,gMinuit->fCstatu);

   ConversionFitANarrow = (TF1*) ConversionFitA->Clone("ConversionFitA Narrow");
   cout<<"Getting Fitter"<<endl;
   TFitResultPtr FitresultANarrow;
   TString resultANarrow = "";
   iterations = 11;
   for(Int_t i = 0; i<iterations;i++){
      cout<<"Fit Iteration "<<i<<endl;
      //FitresultANarrow= histoCorrectedYieldTrueEffNarrow->Fit(ConversionFitANarrow, fitParameterA, "", fitMinPt, fitMaxPt);
      FitresultANarrow = CombinedNeutralAndChargedPionsNarrow->Fit(ConversionFitANarrow, fitParameterA, "", fitMinPt, fitMaxPt);
      resultANarrow = gMinuit->fCstatu;
      if(!resultANarrow.CompareTo("SUCCESSFUL")) break;
      else iterations++;
      if(iterations>200) break;
   }
   PrintParameter(ConversionFitANarrow,fitPi0A,"histoCorrectedYieldTrueEff Narrow",7,gMinuit->fCstatu);





   // ConversionFitAWide = FitObject(fitPi0A,"ConversionFitAWide","Pi0",CombinedNeutralAndChargedPionsWide,fitMinPt,fitMaxPt);
   // DrawGammaSetMarkerTF1(ConversionFitAWide, 1, 2.0, kBlue-2);
   // cout<<"CorrectedYieldTrueEff Wide"<<fitPi0A<<endl;
   // cout<<ConversionFitAWide->GetChisquare()/ConversionFitAWide->GetNDF()<<endl;
   // cout<<ConversionFitAWide->GetParameter(0)<<endl;
   // cout<<ConversionFitAWide->GetParameter(1)<<endl;
   // cout<<ConversionFitAWide->GetParameter(2)<<endl;
   // cout<<ConversionFitAWide->GetParameter(3)<<endl;
   // cout<<ConversionFitAWide->GetParameter(4)<<endl;
   // cout<<ConversionFitAWide->GetParameter(5)<<endl;


   // ConversionFitANarrow = FitObject(fitPi0A,"ConversionFitANarrow","Pi0",CombinedNeutralAndChargedPionsNarrow,fitMinPt,fitMaxPt);
   // DrawGammaSetMarkerTF1(ConversionFitANarrow, 1, 2.0, kBlue-2);
   // cout<<"CorrectedYieldTrueEff Narrow"<<fitPi0A<<endl;
   // cout<<ConversionFitANarrow->GetChisquare()/ConversionFitANarrow->GetNDF()<<endl;
   // cout<<ConversionFitANarrow->GetParameter(0)<<endl;
   // cout<<ConversionFitANarrow->GetParameter(1)<<endl;
   // cout<<ConversionFitANarrow->GetParameter(2)<<endl;
   // cout<<ConversionFitANarrow->GetParameter(3)<<endl;
   // cout<<ConversionFitANarrow->GetParameter(4)<<endl;
   // cout<<ConversionFitANarrow->GetParameter(5)<<endl;



   cout<<"------------------------- End Fitting ----------------------------"<<endl;
   cout<<"------------------------- End Fitting ----------------------------"<<endl;
   cout<<"------------------------- End Fitting ----------------------------"<<endl;

   TString fitEtaA = "h";
   TString fitEtaB = "l";


   fileEta = new TFile(Form("%s/%s/Eta_data_GammaConvV1Correction_%s.root",cutSel.Data(),option.Data(),cutSel.Data()));
   if(fileEta->IsZombie())
      fileEta = NULL;

   if(fileEta){

      histoCorrectedEtaNormalEff = (TH1D*)fileEta->Get("CorrectedYieldNormEff");
      histoCorrectedEtaTrueEff = (TH1D*)fileEta->Get("CorrectedYieldTrueEff");

      ConversionFitEtaA = FitObject(fitEtaA,"ConversionFitEtaA","Eta",histoCorrectedEtaTrueEff,.0,4.0);
      cout<<"CorrectedEtaTrueEff"<<endl;
      cout<<ConversionFitEtaA->GetChisquare()<<endl;
      cout<<ConversionFitEtaA->GetParameter(0)<<endl;
      cout<<ConversionFitEtaA->GetParameter(1)<<endl;
      cout<<ConversionFitEtaA->GetParameter(2)<<endl;
      cout<<ConversionFitEtaA->GetParameter(3)<<endl;
      cout<<ConversionFitEtaA->GetParameter(4)<<endl;
      cout<<ConversionFitEtaA->GetParameter(5)<<endl;

      ConversionFitEtaB = FitObject(fitEtaB,"ConversionFitEtaB","Eta",histoCorrectedEtaTrueEff,.0,4.0);
      cout<<"CorrectedEtaTrueEff"<<endl;
      cout<<ConversionFitEtaB->GetChisquare()<<endl;
      cout<<ConversionFitEtaB->GetParameter(0)<<endl;
      cout<<ConversionFitEtaB->GetParameter(1)<<endl;
      cout<<ConversionFitEtaB->GetParameter(2)<<endl;
      cout<<ConversionFitEtaB->GetParameter(3)<<endl;
      cout<<ConversionFitEtaB->GetParameter(4)<<endl;
      cout<<ConversionFitEtaB->GetParameter(5)<<endl;

      ConversionFitEtaB->SetLineColor(2);
      ConversionFitEtaB->SetLineStyle(5);
   }


   TH1D *dummy = new TH1D("dummy","dummy",1360,0.0,22);

   SetHistogramm(dummy, "#it{p}_{T} (GeV/#it{c})", "#frac{1}{2#pi N_{ev.}} #frac{d^{2}N}{#it{p}_{T}d#it{p}_{T}dy} (GeV^{-2}#it{c})");
   dummy->GetYaxis()->SetTitleSize(0.04);
   dummy->GetYaxis()->SetTitleOffset(1.55);
   dummy->GetYaxis()->SetRangeUser(ConversionFitA->GetMinimum()/10,ConversionFitA->GetMaximum()*10);
   DrawGammaSetMarker(histoCorrectedYieldTrueEff, 24, 2.0, kRed-2, kRed-2);
   DrawGammaSetMarker(CombinedNeutralAndChargedPions, 24, 2.0, kBlue-2, kBlue-2);
   histoCorrectedYieldTrueEff->SetLineColor(kRed-2);
   histoCorrectedYieldTrueEff->SetFillColor(kRed-2);
   dummy->DrawCopy();
   hint->SetFillColor(kYellow);
   hint->DrawCopy("samee3");
   CombinedNeutralAndChargedPions->Draw("e1,same");

   histoCorrectedYieldTrueEff->Draw("e1,same");
   //CombinedChargedPionsStatAverage->Draw("e1,same");
   //ConversionFitPionsStatAverage->Draw("same");
   ConversionFitA->Draw("same");
   ConversionFitB->Draw("same");
   ConversionFitC->Draw("same");
   ConversionFitPionsStatAverage->Draw("same");

   if(fileEta){
      DrawGammaSetMarker(histoCorrectedEtaTrueEff, 20, 2.0, kBlue+2, kBlue+2);
      histoCorrectedEtaTrueEff->Draw("e1,same");
      histoCorrectedEtaNormalEff->Draw("e1,same");
      ConversionFitEtaA->Draw("same");
      ConversionFitEtaB->Draw("same");
   }


   TLegend* leg_ConversionSpeccanvas = GetAndSetLegend(0.5,0.63,5);
   leg_ConversionSpeccanvas->AddEntry(histoCorrectedYieldTrueEff,"#pi^{0}, statistical errors only","p");
   leg_ConversionSpeccanvas->AddEntry(ConversionFitA,Form("%s Fit, #chi^{2}/ndf %.2f",fitPi0A.Data(),ConversionFitA->GetChisquare()/ConversionFitA->GetNDF()),"l");
   leg_ConversionSpeccanvas->AddEntry(ConversionFitB,Form("%s Fit, #chi^{2}/ndf %.2f",fitPi0B.Data(),ConversionFitB->GetChisquare()/ConversionFitB->GetNDF()),"l");
   leg_ConversionSpeccanvas->AddEntry(ConversionFitC,Form("%s Fit, #chi^{2}/ndf %.2f",fitPi0C.Data(),ConversionFitC->GetChisquare()/ConversionFitC->GetNDF()),"l");
   if(fileEta){
      leg_ConversionSpeccanvas->AddEntry(ConversionFitEtaA,Form("Parametrisation Eta A %s Chi2 %.2f",fitEtaA.Data(),ConversionFitEtaA->GetChisquare()),"l");
      leg_ConversionSpeccanvas->AddEntry(ConversionFitEtaB,Form("Parametrisation Eta B %s Chi2 %.2f",fitEtaA.Data(),ConversionFitEtaA->GetChisquare()),"l");
   }
   leg_ConversionSpeccanvas->Draw();

   DrawSystem(0.19,0.04,option.Data(),centrality);

   padConversionRatios->cd();

   // histRatioConversionPi0A = (TH1D*) histoCorrectedYieldTrueEff->Clone("histRatioConversionPi0A");
   // histRatioConversionPi0AHighpt = (TH1D*) histoCorrectedYieldTrueEff->Clone("histRatioConversionPi0A");
   // histRatioConversionPi0B = (TH1D*) histoCorrectedYieldTrueEff->Clone("histRatioConversionPi0B");
   // histRatioConversionPi0C =  (TH1D*) histoCorrectedYieldTrueEff->Clone("histRatioConversionPi0C");

   histRatioConversionPi0A = (TH1D*) CombinedNeutralAndChargedPions->Clone("histRatioConversionPi0A");
   histRatioConversionPi0AHighpt = (TH1D*) CombinedNeutralAndChargedPions->Clone("histRatioConversionPi0A");
   histRatioConversionPi0B = (TH1D*) CombinedNeutralAndChargedPions->Clone("histRatioConversionPi0B");
   histRatioConversionPi0C =  (TH1D*) CombinedNeutralAndChargedPions->Clone("histRatioConversionPi0C");
   histRatioConversionPi0Charged =  (TH1D*) CombinedNeutralAndChargedPions->Clone("histRatioConversionPi0C");

   histRatioConversionPi0A->Divide(ConversionFitA);
   histRatioConversionPi0B->Divide(ConversionFitB);
   histRatioConversionPi0C->Divide(ConversionFitC);
   histRatioConversionPi0Charged->Divide(ConversionFitPionsStatAverage);
   hint->Divide(ConversionFitA);

   SetHistogramm(dummy,"#it{p}_{T} (GeV/#it{c})","#frac{Yield}{Fit}",0.65,1.35);
   dummy->GetYaxis()->SetTitleSize(0.14);
   dummy->GetXaxis()->SetTitleSize(0.14);
   dummy->GetYaxis()->SetTitleOffset(0.45);
   dummy->GetYaxis()->SetNdivisions(5,5,0,kTRUE);
   dummy->GetYaxis()->CenterTitle(kTRUE);
   SetHistogramm(histRatioConversionPi0A,"#it{p}_{T} (GeV/#it{c})","#frac{Yield}{Fit}",0.5,1.9);
   histRatioConversionPi0A->GetYaxis()->SetTitleSize(0.1);
   histRatioConversionPi0A->GetYaxis()->SetTitleOffset(0.4);
   histRatioConversionPi0A->GetYaxis()->CenterTitle(kTRUE);

   SetHistogramm(histRatioConversionPi0AHighpt,"#it{p}_{T} (GeV/#it{c})","#frac{Yield}{Fit}",0.5,1.9);
   histRatioConversionPi0AHighpt->GetYaxis()->SetTitleSize(0.1);
   histRatioConversionPi0AHighpt->GetYaxis()->SetTitleOffset(0.4);
   histRatioConversionPi0AHighpt->GetYaxis()->CenterTitle(kTRUE);

   SetHistogramm(histRatioConversionPi0B,"#it{p}_{T} (GeV/#it{c})","#frac{Yield}{Fit}",0.5,1.9);
   histRatioConversionPi0B->GetYaxis()->SetTitleSize(0.1);
   histRatioConversionPi0B->GetYaxis()->SetTitleOffset(0.4);
   histRatioConversionPi0B->GetYaxis()->CenterTitle(kTRUE);
   SetHistogramm(histRatioConversionPi0C,"#it{p}_{T} (GeV/#it{c})","#frac{Yield}{Fit}",0.5,1.9);
   histRatioConversionPi0C->GetYaxis()->SetTitleSize(0.1);
   histRatioConversionPi0C->GetYaxis()->SetTitleOffset(0.4);
   histRatioConversionPi0C->GetYaxis()->CenterTitle(kTRUE);

   //padConversionRatios->SetLogx();

   histRatioConversionPi0A->GetYaxis()->SetTitleSize(0.1);
   histRatioConversionPi0A->GetYaxis()->SetTitleOffset(0.4);
   histRatioConversionPi0A->GetYaxis()->CenterTitle(kTRUE);
   histRatioConversionPi0A->GetYaxis()->SetNdivisions(5);

   DrawGammaSetMarker(histRatioConversionPi0A, 20, 1.,kBlue-2,kBlue-2);
   DrawGammaSetMarker(histRatioConversionPi0Charged, 20, 1.,kGreen+2,kGreen+2);
   DrawGammaSetMarker(histRatioConversionPi0B, 24, 1.,kRed-3,kRed-3);
   DrawGammaSetMarker(histRatioConversionPi0C, 25, 1.,kYellow+2,kYellow+2);


   histRatioConversionPi0B->SetLineStyle(2);
   histRatioConversionPi0C->SetLineStyle(3);
   dummy->DrawCopy();
   hint->DrawCopy("samee3");
   One->Draw("same");
   histRatioConversionPi0A->Draw("same");
   histRatioConversionPi0Charged->Draw("same");
   histRatioConversionPi0B->Draw("same");
   histRatioConversionPi0C->Draw("same");

   if(fileEta){
      histRatioConversionEtaA = (TH1D*) histoCorrectedEtaTrueEff->Clone("histRatioConversionEtaA");
      histRatioConversionEtaB = (TH1D*) histoCorrectedEtaTrueEff->Clone("histRatioConversionEtaB");

      histRatioConversionEtaA = CalculateHistoRatioToFit(histRatioConversionEtaA,ConversionFitEtaA);
      histRatioConversionEtaB = CalculateHistoRatioToFit(histRatioConversionEtaB,ConversionFitEtaB);

      histRatioConversionEtaA->Draw("same");
      histRatioConversionEtaB->Draw("same");
   }

   ConversionSpeccanvas->Print(Form("%s/%s_Spectra_ConversionPi0%s_%s_%s_%s.%s",outputDir.Data(),textPi0New.Data(),centralityQM.Data(),textPrefix2.Data(),cutSel.Data(),fGammaCutSelection.Data(),suffix.Data()));

   TCanvas *QCDFitExponent = GetAndSetCanvas("QCDFitExponent",0.05,0.1,1800 ,800);

   TF1 *qcdExponent = new TF1("qcdExponent","([0]+[1]/(TMath::Power(x,[2])+[3]*TMath::Power(x,[4])))",1,20);
   TF1 *qcdExponentConst = new TF1("qcdExponentConst","[0]",1,20);
   qcdExponentConst->SetLineWidth(0.5);

   qcdExponent->SetLineWidth(0.5);
   qcdExponent->SetLineColor(kRed+2);


   if(fitPi0A.Contains("qcd")){
      qcdExponentConst->SetParameter(0,ConversionFitA->GetParameter(1));
      qcdExponent->SetParameter(0,ConversionFitA->GetParameter(1));
      qcdExponent->SetParameter(1,ConversionFitA->GetParameter(2));
      qcdExponent->SetParameter(2,ConversionFitA->GetParameter(3));
      qcdExponent->SetParameter(3,ConversionFitA->GetParameter(4));
      qcdExponent->SetParameter(4,0.0);
      if(!fitPi0A.CompareTo("qcd"))qcdExponent->SetParameter(4,ConversionFitA->GetParameter(5));
   }
   else if(fitPi0B.Contains("qcd")){
      qcdExponentConst->SetParameter(0,ConversionFitB->GetParameter(1));
      qcdExponent->SetParameter(0,ConversionFitB->GetParameter(1));
      qcdExponent->SetParameter(1,ConversionFitB->GetParameter(2));
      qcdExponent->SetParameter(2,ConversionFitB->GetParameter(3));
      qcdExponent->SetParameter(3,ConversionFitB->GetParameter(4));
      qcdExponent->SetParameter(4,0.0);
      if(!fitPi0B.CompareTo("qcd"))qcdExponent->SetParameter(4,ConversionFitB->GetParameter(5));
   }
   else{
      qcdExponentConst->SetParameter(0,1);
      qcdExponent->SetParameter(0,1);
      qcdExponent->SetParameter(1,1);
      qcdExponent->SetParameter(2,1);
      qcdExponent->SetParameter(3,1);
      qcdExponent->SetParameter(4,0.0);
   }

   qcdExponent->Draw("");
   qcdExponentConst->Draw("same");

   qcdExponent->GetHistogram()->GetYaxis()->SetTitle("Exponent");
   qcdExponent->GetHistogram()->GetYaxis()->SetTitleOffset(0.6);
   qcdExponent->GetHistogram()->GetXaxis()->SetTitle("#it{p}_{T} (GeV/#it{c})");
   qcdExponentConst->GetHistogram()->GetYaxis()->SetTitle("Exponent");
   qcdExponentConst->GetHistogram()->GetYaxis()->SetTitleOffset(0.6);
   qcdExponentConst->GetHistogram()->GetXaxis()->SetTitle("#it{p}_{T} (GeV/#it{c})");

   QCDFitExponent->Modified();

   TLegend* leg_qcdExponent = GetAndSetLegend(0.6,0.7,3);
   leg_qcdExponent->AddEntry(qcdExponent,"Exponent of parametrization","l");
   leg_qcdExponent->AddEntry(qcdExponentConst,Form("Boundary value %.2f",qcdExponentConst->GetParameter(0)),"l");
   leg_qcdExponent->Draw();


   DrawSystem(0.75,0.15,option.Data(),centrality);
   QCDFitExponent->Print(Form("%s/%s_QCDFitExponent_%s_%s_%s_%s.%s",outputDir.Data(),textPi0New.Data(),centralityQM.Data(),textPrefix2.Data(),cutSel.Data(),fGammaCutSelection.Data(),suffix.Data()));


   // Fitted Double Ratios

   // // ---------------------------------------- Random Error Fit ----------------------------------

   TRandom3 *random = new TRandom3(0);
   Int_t nIter = 1;

   TH1D *LowErrorPi0Yield = (TH1D*) histoCorrectedYieldTrueEff->Clone("LowErrorPi0Yield");
   TH1D *HighErrorPi0Yield = (TH1D*) histoCorrectedYieldTrueEff->Clone("HighErrorPi0Yield");

   Double_t highParameterPi0A = 0;
   Double_t highParameterPi0B = 0;
   Double_t highParameterPi0C  = 0;
   Double_t highParameterPi0D = 0;
   Double_t highParameterPi0E = 0;

   Double_t lowParameterPi0A = 0;
   Double_t lowParameterPi0B = 0;
   Double_t lowParameterPi0C = 0;
   Double_t lowParameterPi0D = 0;
   Double_t lowParameterPi0E = 0;


   TFitResultPtr FitresultRandomLow;
   TFitResultPtr FitresultRandomHigh;
   GetFitParameter(fitPi0A,centrality,Params);
   for(Int_t it = 1; it<nIter+1; it++){

      for(Int_t i = 0; i<histoCorrectedYieldTrueEff->GetNbinsX(); i++){
         //Double_t randomDouble = random->Gaus(0,histoCorrectedYieldTrueEff->GetBinError(i+1));
         Double_t randomDouble = random->Rndm(0)*.5;
         //if(TMath::Abs(randomDouble)>histoCorrectedYieldTrueEff->GetBinError(i+1)*0.5) randomDouble = 0;
         LowErrorPi0Yield->SetBinContent(i+1, histoCorrectedYieldTrueEff->GetBinContent(i+1) - (randomDouble)*(histoCorrectedYieldTrueEff->GetBinError(i+1)) );
         HighErrorPi0Yield->SetBinContent(i+1, histoCorrectedYieldTrueEff->GetBinContent(i+1) + (randomDouble)*(histoCorrectedYieldTrueEff->GetBinError(i+1)) );
      }

      FitRandomLow = FitObject("qcd","FitRandomLow","Pi0",LowErrorPi0Yield,fitMinPt,11);//,Params, "QNRME+");
      FitresultRandomLow = LowErrorPi0Yield->Fit(FitRandomLow, "QSNRME+", "", fitMinPt, 11.);
      // if((gMinuit->fCstatu).CompareTo("SUCCESSFUL") || (gMinuit->fCstatu).CompareTo("PROBLEMS  ")){
      //    cout<<gMinuit->fCstatu.Data()<<endl;
      //    it--;
      //    continue;
      // }
      FitRandomHigh = FitObject("qcd","FitRandomHigh","Pi0",HighErrorPi0Yield,fitMinPt,11);//,Params, "QNRME+");
      // FitresultRandomHigh = HighErrorPi0Yield->Fit(FitRandomHigh, "QSNRME+", "",fitMinPt, 11.);
      // if((gMinuit->fCstatu).CompareTo("SUCCESSFUL") || (gMinuit->fCstatu).CompareTo("PROBLEMS  ")){
      //    it--;
      //    continue;
      // }

      lowParameterPi0A = lowParameterPi0A + FitRandomLow->GetParameter(0);
      lowParameterPi0B = lowParameterPi0B + FitRandomLow->GetParameter(1);
      lowParameterPi0C = lowParameterPi0C + FitRandomLow->GetParameter(2);
      lowParameterPi0D = lowParameterPi0D + FitRandomLow->GetParameter(3);
      lowParameterPi0E = lowParameterPi0E + FitRandomLow->GetParameter(4);

      highParameterPi0A = highParameterPi0A + FitRandomHigh->GetParameter(0);
      highParameterPi0B = highParameterPi0B + FitRandomHigh->GetParameter(1);
      highParameterPi0C = highParameterPi0C + FitRandomHigh->GetParameter(2);
      highParameterPi0D = highParameterPi0D + FitRandomHigh->GetParameter(3);
      highParameterPi0E = highParameterPi0E + FitRandomHigh->GetParameter(4);
   }

   FitRandomLow->SetParameter(0,lowParameterPi0A/nIter);
   FitRandomLow->SetParameter(1,lowParameterPi0B/nIter);
   FitRandomLow->SetParameter(2,lowParameterPi0C/nIter);
   FitRandomLow->SetParameter(3,lowParameterPi0D/nIter);
   FitRandomLow->SetParameter(4,lowParameterPi0E/nIter);

   FitRandomHigh->SetParameter(0,highParameterPi0A/nIter);
   FitRandomHigh->SetParameter(1,highParameterPi0B/nIter);
   FitRandomHigh->SetParameter(2,highParameterPi0C/nIter);
   FitRandomHigh->SetParameter(3,highParameterPi0D/nIter);
   FitRandomHigh->SetParameter(4,highParameterPi0E/nIter);

   histoIncRatioFitPurityA = (TH1D*) histoIncRatioPurityTrueEff->Clone("histoIncRatioFitPurityA");
   histoIncRatioFitPurityB = (TH1D*) histoIncRatioPurityTrueEff->Clone("histoIncRatioFitPurityB");
   histoIncRatioFitPurityC = (TH1D*) histoIncRatioPurityTrueEff->Clone("histoIncRatioFitPurityC");
   histoIncRatioFitPurityPionsStatAverage = (TH1D*) histoIncRatioPurityTrueEff->Clone("histoIncRatioFitPurityPionsStat");
   histoIncRatioFitPurityWide = (TH1D*) histoIncRatioPurityTrueEffWide->Clone("histoIncRatioFitPurityWide");
   histoIncRatioFitPurityNarrow = (TH1D*) histoIncRatioPurityTrueEffNarrow->Clone("histoIncRatioFitPurityNarrow");
   histoIncRatioFitFit = (TH1D*) histoIncRatioPurityTrueEff->Clone("histoIncRatioFitFit");

   histoIncRatioHighFitPurity = (TH1D*) histoIncRatioPurityTrueEff->Clone("histoIncRatioHighFitPurity");
   histoIncRatioLowFitPurity = (TH1D*) histoIncRatioPurityTrueEff->Clone("histoIncRatioLowFitPurity");
   histoCorrectedYieldTrueEffPi0Fit = (TH1D*)histoIncRatioPurityTrueEff->Clone("CorrectedYieldTrueEffPi0Fit");
   histoCorrectedYieldTrueEffPi0FitWide = (TH1D*)histoIncRatioPurityTrueEff->Clone("CorrectedYieldTrueEffPi0FitWide");
   histoCorrectedYieldTrueEffPi0FitNarrow = (TH1D*)histoIncRatioPurityTrueEff->Clone("CorrectedYieldTrueEffPi0FitNarrow");

   histoChargedPionsSystAverage = (TH1D*) histoIncRatioPurityTrueEff->Clone("histoChargedPionsSystAverage");
   histoChargedPionsStatAverage = (TH1D*) histoIncRatioPurityTrueEff->Clone("histoChargedPionsStatAverage");

   for(Int_t bin = 1; bin<histoIncRatioFitPurityA->GetNbinsX()+1; bin++){

      Double_t ptStart = histoIncRatioFitPurityA->GetBinLowEdge(bin);
      Double_t ptEnd = histoIncRatioFitPurityA->GetBinLowEdge(bin+1);
      Double_t binWidth = histoIncRatioFitPurityA->GetBinWidth(bin);

      histoCorrectedYieldTrueEffPi0Fit->SetBinContent(bin,ConversionFitA->Eval(histoIncRatioPurityTrueEff->GetBinCenter(bin)));
      histoCorrectedYieldTrueEffPi0Fit->SetBinError(bin,(ConversionFitC->IntegralError(ptStart, ptEnd, FitresultC->GetParams(), FitresultC->GetCovarianceMatrix().GetMatrixArray() ) / binWidth));

      histoCorrectedYieldTrueEffPi0FitWide->SetBinContent(bin,ConversionFitAWide->Eval(histoIncRatioPurityTrueEff->GetBinCenter(bin)));
      histoCorrectedYieldTrueEffPi0FitWide->SetBinError(bin,(ConversionFitC->IntegralError(ptStart, ptEnd, FitresultC->GetParams(), FitresultC->GetCovarianceMatrix().GetMatrixArray() ) / binWidth));
      
      histoCorrectedYieldTrueEffPi0FitNarrow->SetBinContent(bin,ConversionFitANarrow->Eval(histoIncRatioPurityTrueEff->GetBinCenter(bin)));
      histoCorrectedYieldTrueEffPi0FitNarrow->SetBinError(bin,(ConversionFitC->IntegralError(ptStart, ptEnd, FitresultC->GetParams(), FitresultC->GetCovarianceMatrix().GetMatrixArray() ) / binWidth));

      histoIncRatioFitPurityPionsStatAverage->SetBinContent(bin,ConversionFitPionsStatAverage->Eval(histoIncRatioPurityTrueEff->GetBinCenter(bin)));
      histoIncRatioFitPurityPionsStatAverage->SetBinError(bin,(ConversionFitPionsStatAverage->IntegralError(ptStart, ptEnd, FitresultChargedStatAverage->GetParams(), FitresultChargedStatAverage->GetCovarianceMatrix().GetMatrixArray() ) / binWidth));
      
      histoChargedPionsSystAverage->SetBinContent(bin,ConversionFitPionsStatAverage->Eval(histoIncRatioPurityTrueEff->GetBinCenter(bin)));
      //histoChargedPionsSystAverage->SetBinError(bin,(ConversionFitPionsSystAverage->IntegralError(ptStart, ptEnd, FitresultChargedSystAverage->GetParams(), FitresultChargedSystAverage->GetCovarianceMatrix().GetMatrixArray() ) / binWidth));
      histoChargedPionsSystAverage->SetBinError(bin,CombinedChargedPionsSystAverage->GetBinError(CombinedChargedPionsSystAverage->FindBin(histoChargedPionsSystAverage->GetBinCenter(bin))));

      histoChargedPionsStatAverage->SetBinContent(bin,ConversionFitPionsStatAverage->Eval(histoIncRatioPurityTrueEff->GetBinCenter(bin)));
      histoChargedPionsStatAverage->SetBinError(bin,(ConversionFitPionsStatAverage->IntegralError(ptStart, ptEnd, FitresultChargedStatAverage->GetParams(), FitresultChargedStatAverage->GetCovarianceMatrix().GetMatrixArray() ) / binWidth));
      //histoChargedPionsStatAverage->SetBinError(bin,CombinedChargedPionsStatAverage->GetBinError(CombinedChargedPionsStatAverage->FindBin(histoChargedPionsStatAverage->GetBinCenter(bin))));

      
      histoIncRatioFitPurityA->SetBinContent(bin,ConversionFitA->Eval(histoIncRatioPurityTrueEff->GetBinCenter(bin)));
      //histoIncRatioFitPurityA->SetBinError(bin,(ConversionFitA->IntegralError(ptStart, ptEnd, FitresultA->GetParams(), FitresultA->GetCovarianceMatrix().GetMatrixArray() ) / binWidth));
      histoIncRatioFitPurityA->SetBinError(bin,(ConversionFitC->IntegralError(ptStart, ptEnd, FitresultC->GetParams(), FitresultC->GetCovarianceMatrix().GetMatrixArray() ) / binWidth));

      histoIncRatioFitPurityB->SetBinContent(bin,ConversionFitB->Eval(histoIncRatioPurityTrueEff->GetBinCenter(bin)));
      //histoIncRatioFitPurityB->SetBinError(bin,(ConversionFitB->IntegralError(ptStart, ptEnd, FitresultB->GetParams(), FitresultB->GetCovarianceMatrix().GetMatrixArray() ) / binWidth));
      histoIncRatioFitPurityB->SetBinError(bin,(ConversionFitC->IntegralError(ptStart, ptEnd, FitresultC->GetParams(), FitresultC->GetCovarianceMatrix().GetMatrixArray() ) / binWidth));

      histoIncRatioFitPurityC->SetBinContent(bin,ConversionFitB->Eval(histoIncRatioPurityTrueEff->GetBinCenter(bin)));
      histoIncRatioFitPurityC->SetBinError(bin,(ConversionFitC->IntegralError(ptStart, ptEnd, FitresultC->GetParams(), FitresultC->GetCovarianceMatrix().GetMatrixArray() ) / binWidth)); // HERE FIT B IS USED

      histoIncRatioFitPurityWide->SetBinContent(bin,ConversionFitAWide->Eval(histoIncRatioPurityTrueEffWide->GetBinCenter(bin)));
      histoIncRatioFitPurityWide->SetBinError(bin,histoCorrectedYieldTrueEffWide->GetBinError(bin));
      histoIncRatioFitPurityNarrow->SetBinContent(bin,ConversionFitANarrow->Eval(histoIncRatioPurityTrueEffNarrow->GetBinCenter(bin)));
      histoIncRatioFitPurityNarrow->SetBinError(bin,histoCorrectedYieldTrueEffNarrow->GetBinError(bin));

      histoIncRatioLowFitPurity->SetBinContent(bin,FitRandomLow->Eval(histoIncRatioPurityTrueEff->GetBinCenter(bin)));
      histoIncRatioLowFitPurity->SetBinError(bin,histoIncRatioFitPurityA->GetBinError(bin));
      histoIncRatioHighFitPurity->SetBinContent(bin,FitRandomHigh->Eval(histoIncRatioPurityTrueEff->GetBinCenter(bin)));
      histoIncRatioHighFitPurity->SetBinError(bin,histoIncRatioFitPurityA->GetBinError(bin));

      Double_t binContentFit = ConversionGammaFitA->Integral(histoIncRatioFitPurityA->GetBinLowEdge(bin),histoIncRatioFitPurityA->GetBinLowEdge(bin+1)) / ConversionFitA->Integral(histoIncRatioFitPurityA->GetBinLowEdge(bin),histoIncRatioFitPurityA->GetBinLowEdge(bin+1));
      Double_t binErrorFit = histoIncRatioPurityTrueEff->GetBinError(bin);

      histoIncRatioFitFit->SetBinContent(bin,binContentFit);
      histoIncRatioFitFit->SetBinError(bin,binErrorFit);
   }


   TCanvas *FitRatioPi0ToChargedCanvas = new TCanvas();
   DrawGammaSetMarker(histoIncRatioPurityTrueEff, 20, 2.0, 1, 1);
   DrawGammaSetMarker(histoIncRatioFitPurityPionsStatAverage, 24, 1.0, kGreen-2, kGreen-2);

   TH1D* ChargedToPi0RatioStatAverage = (TH1D*) histoCorrectedYieldTrueEff->Clone("ChargedToPi0RatioStatAverage");
   SetHistogramm(ChargedToPi0RatioStatAverage,"#it{p}_{T} (GeV/#it{c})", "#pi^{0}/(#pi^{+}+#pi^{-})2");
   DrawGammaSetMarker(ChargedToPi0RatioStatAverage, 20, 1.0, kGreen-2, kGreen-2);
   ChargedToPi0RatioStatAverage->Divide(ConversionFitPionsStatAverage);


   TF1 *Const = new TF1("Const.","[0]",0.9,11.);
   Const->SetLineWidth(0.5);
   ChargedToPi0RatioStatAverage->Fit(Const, "", "", 0.9, 11.);

   ChargedToPi0RatioStatAverage->GetYaxis()->SetRangeUser(.3,1.8);
   ChargedToPi0RatioStatAverage->Draw("");
   Const->Draw("same");
   ChargedToPi0RatioStatAverage->Draw("same");


   TLegend* leg_FitRatioPi0ToCharged = GetAndSetLegend(0.12,0.12,4);
   leg_FitRatioPi0ToCharged->AddEntry(ChargedToPi0RatioStatAverage,"Average","p");
   leg_FitRatioPi0ToCharged->AddEntry(Const,Form("Const Fit %0.3f",Const->GetParameter(0)));
   leg_FitRatioPi0ToCharged->Draw();

   FitRatioPi0ToChargedCanvas->Print(Form("%s/%s_ChargedToNeutralPiFitRatio_%s_%s_%s.%s",outputDir.Data(),textPi0New.Data(),textPrefix2.Data(),cutSel.Data(),fGammaCutSelection.Data(),suffix.Data()));


   histoIncRatioFitPurityA->Divide(histoGammaSpecCorrPurity,histoIncRatioFitPurityA);
   histoIncRatioFitPurityB->Divide(histoGammaSpecCorrPurity,histoIncRatioFitPurityB);
   histoIncRatioFitPurityC->Divide(histoGammaSpecCorrPurity,histoIncRatioFitPurityC);
   histoIncRatioFitPurityWide->Divide(histoGammaSpecCorrPurity,histoIncRatioFitPurityWide);
   histoIncRatioFitPurityNarrow->Divide(histoGammaSpecCorrPurity,histoIncRatioFitPurityNarrow);
   histoIncRatioFitPurityPionsStatAverage->Divide(histoGammaSpecCorrPurity,histoIncRatioFitPurityPionsStatAverage);

   histoIncRatioLowFitPurity->Divide(histoGammaSpecCorrPurity,histoIncRatioLowFitPurity);
   histoIncRatioHighFitPurity->Divide(histoGammaSpecCorrPurity,histoIncRatioHighFitPurity);

   SetHistogramm(histoIncRatioFitPurityA,"#it{p}_{T} (GeV/#it{c})", "Ratio Inclusive #gamma/#pi^{0}",0.0,3.0);
   SetHistogramm(histoIncRatioFitFit,"#it{p}_{T} (GeV/#it{c})", "Ratio Inclusive #gamma/#pi^{0}",0.0,3.0);

   TCanvas *canvasIncRatioFit = GetAndSetCanvas("IncRatioFit");
   DrawGammaSetMarker(histoIncRatioFitFit, 20, 2.0, 6, 6);
   DrawGammaSetMarker(histoIncRatioFitPurityA, 20, 2.0, 7, 7);

   histoIncRatioFitPurityA->DrawCopy("e1");

   TLegend* leg_canvasIncRatioFit = GetAndSetLegend(0.4,0.8,3);
   leg_canvasIncRatioFit->AddEntry(histoIncRatioFitPurityA,"Inclusive Ratio PCM");
   leg_canvasIncRatioFit->Draw();


   if(option.CompareTo("PbPb_2.76TeV") == 0) DrawCentrality(0.8,0.9,centrality);

   canvasIncRatioFit->Print(Form("%s/%s_IncRatio_Fit%s_%s_%s_%s.%s",outputDir.Data(),textPi0New.Data(),centralityQM.Data(),textPrefix2.Data(),cutSel.Data(),fGammaCutSelection.Data(),suffix.Data()));


   //**********************************************************************************
   //******************** Comparison MC / Data ****************************************
   //**********************************************************************************

   TCanvas* canvasComparisonMCData = GetAndSetCanvas("canvasComparisonMCData");
   DrawGammaSetMarker(histoTruePi0MCData, 22, 2.0, kOrange-2, kOrange-2);
   DrawGammaSetMarker(histoNormalPi0MCData, 22, 2.0, kOrange+2, kOrange+2);
   DrawGammaSetMarker(histoPurityGammaMCData, 22, 2.0, kBlue+2, kBlue+2);

   SetHistogramm( histoTruePi0MCData, "#it{p}_{T} (GeV/#it{c})", "Comparison MC / Data",0.0,7.0);
   SetHistogramm( histoNormalPi0MCData, "#it{p}_{T} (GeV/#it{c})", "Comparison MC / Data",0.0,2.0);
   SetHistogramm( histoPurityGammaMCData, "#it{p}_{T} (GeV/#it{c})", "Comparison MC / Data",0.0,7.0);
   histoTruePi0MCData->Draw("e1");
   histoNormalPi0MCData->Draw("e1,same");
   histoPurityGammaMCData->Draw("e1,same");

   TLegend* leg_ComparisonMCData = GetAndSetLegend(0.12,0.7,4);
   leg_ComparisonMCData->AddEntry(histoTruePi0MCData,"Data #pi^{0} True Eff/ MC #pi^{0}");
   leg_ComparisonMCData->AddEntry(histoNormalPi0MCData,"Data #pi^{0} Normal Eff/ MC #pi^{0}");
   leg_ComparisonMCData->AddEntry(histoPurityGammaMCData,"Data #gamma Purity / MC #gamma");
   leg_ComparisonMCData->Draw();

   canvasComparisonMCData->Print(Form("%s/%s_ComparisonMCData_%s_%s_%s.%s",outputDir.Data(),textPi0New.Data(),textPrefix2.Data(),cutSel.Data(),fGammaCutSelection.Data(),suffix.Data()));


   // **********************************************************************************
   // ********************************* Combined Pi0 ***********************************
   // **********************************************************************************

   combinedFile = new TFile("FinalResults/CombinedResults_111216_nobinshift.root");

   TCanvas *CombinedSpeccanvas = GetAndSetCanvas("CombinedSpeccanvas");
   DrawGammaCanvasSettings(CombinedSpeccanvas, 0.1, 0.015, 0.01, 0.09);
   TPad* padCombinedHistos = new TPad("padCombinedHistos", "", 0., 0.25, 1., 1.,-1, -1, -2);
   DrawGammaPadSettings(padCombinedHistos, 0.10, 0.015, 0.01, 0.);
   padCombinedHistos->Draw();

   TPad* padCombinedRatios = new TPad("padCombinedRatios", "", 0., 0., 1., 0.25,-1, -1, -2);
   DrawGammaPadSettings( padCombinedRatios, 0.1, 0.015, 0.0, 0.35);
   padCombinedRatios->Draw();

   combined7TeV = (TGraphAsymmErrors*) combinedFile->Get("graphInvCrossSectionPi0Comb7TeV");
   combinedEta7TeV = (TGraphAsymmErrors*) combinedFile->Get("graphInvCrossSectionEtaComb7TeV");

   if(option.CompareTo("PbPb_2.76TeV") == 0){
      combined7TeV = (TGraphAsymmErrors*) combinedFile->Get("graphInvCrossSectionPi0Comb2760GeV");
      combinedEta7TeV = (TGraphAsymmErrors*) combinedFile->Get("graphInvCrossSectionEtaComb2760GeV");
   }

   combined7TeV = ScaleGraph(combined7TeV, 1./(xSection*recalcBarn));
   combinedEta7TeV = ScaleGraph(combinedEta7TeV, 1./(xSection*recalcBarn));

   histoCombinedPi0 = (TH1D*) histoGammaSpecCorrPurity->Clone("CombinedPi0");
   histoCombinedPi0->Reset();

   combined7TeVRebin = new TGraphAsymmErrors();
   combined7TeVRebin = RebinCombPi0Graph(combined7TeV, histoCombinedPi0);
   padCombinedHistos->cd();
   padCombinedHistos->SetLogy();

   SetGraph(combined7TeV,"#it{p}_{T} (GeV/#it{c})", "#frac{1}{2#pi N_{ev.}} #frac{d^{2}N}{#it{p}_{T}d#it{p}_{T}dy} (GeV^{-2}c)");

   DrawGammaSetMarkerTGraph(combined7TeV, 20, 1., kGreen+2, 1);
   DrawGammaSetMarkerTGraph(combinedEta7TeV, 21, 1., kSpring+2, 1);

   combined7TeV->GetXaxis()->SetRangeUser(0,25);
   combined7TeV->Draw("Ap");
   combinedEta7TeV->Draw("p,same");


   TGraphAsymmErrors *combined7TeVnoErrorX = (TGraphAsymmErrors*) combinedFile->Get("graphInvCrossSectionPi0Comb7TeV");
   combined7TeVnoErrorX = ScaleGraph(combined7TeVnoErrorX, 1./(xSection*recalcBarn));
   for(Int_t n = 0; n<combined7TeV->GetN(); n++){
      combined7TeVnoErrorX->SetPointEXhigh(n,0);
      combined7TeVnoErrorX->SetPointEXlow(n,0);
   }


   CombinedFitA = FitObject("h","CombinedFitA","Pi0",combined7TeV,fitMinPt,25);
   CombinedFitB = FitObject("l","CombinedFitB","Pi0",combined7TeV,fitMinPt,25);
   CombinedFitB->SetLineColor(2);
   CombinedFitB->SetLineStyle(5);


   if(fileEta){
      CombinedFitEtaA = FitObject("H","CombinedFitEtaA","Eta",combinedEta7TeV,0.6,16);
      CombinedFitEtaB = FitObject("l","CombinedFitEtaB","Eta",combinedEta7TeV,0.6,16);
      CombinedFitEtaA->SetLineColor(2);
      CombinedFitEtaA->SetLineStyle(5);
      CombinedFitEtaB->SetLineColor(3);
      CombinedFitEtaB->SetLineStyle(6);

      combined7TeV->Draw("");
      combinedEta7TeV->Draw("same");
      // CombinedFitA->Draw("same");
      //CombinedFitB->Draw("same");
      // ConversionFitEtaA->Draw("same");
      // CombinedFitEtaA->Draw("same");
      // CombinedFitEtaB->Draw("same");
      ConversionFitA->Draw("same");

      histoCorrectedYieldTrueEff->DrawCopy("same");
      //histoCorrectedEtaTrueEff->DrawCopy("same");


      padCombinedRatios->cd();

      graphRatioCombinedPi0A = (TGraphAsymmErrors*) combined7TeV->Clone("graphRatioCombinedPi0A");
      graphRatioCombinedPi0B = (TGraphAsymmErrors*) combined7TeV->Clone("graphRatioCombinedPi0B");
      graphRatioCombinedEtaA = (TGraphAsymmErrors*) combinedEta7TeV->Clone("graphRatioCombinedEtaA");
      graphRatioCombinedEtaB = (TGraphAsymmErrors*) combinedEta7TeV->Clone("graphRatioCombinedEtaB");

      graphRatioCombinedPi0A = CalculateGraphErrRatioToFit (graphRatioCombinedPi0A,CombinedFitA);
      graphRatioCombinedPi0B = CalculateGraphErrRatioToFit (graphRatioCombinedPi0B,CombinedFitB);
      graphRatioCombinedEtaA = CalculateGraphErrRatioToFit (graphRatioCombinedEtaA,CombinedFitEtaA);
      graphRatioCombinedEtaB = CalculateGraphErrRatioToFit (graphRatioCombinedEtaB,CombinedFitEtaB);

      DrawGammaSetMarkerTGraph(graphRatioCombinedPi0A, 20, 1., kGreen+2, 1);
      DrawGammaSetMarkerTGraph(graphRatioCombinedEtaA, 20, 1., kSpring+2, 1);

      SetGraph(graphRatioCombinedPi0A,"#it{p}_{T} (GeV/#it{c})", "#frac{Yield}{Fit}",0.5,1.5);
      graphRatioCombinedPi0A->GetYaxis()->SetTitleSize(0.1);
      graphRatioCombinedPi0A->GetYaxis()->SetTitleOffset(0.4);
      graphRatioCombinedPi0A->GetYaxis()->CenterTitle(kTRUE);
      graphRatioCombinedPi0A->GetYaxis()->SetNdivisions(5);

      graphRatioCombinedPi0A->GetXaxis()->SetRangeUser(0,25);
      graphRatioCombinedPi0A->Draw("Ap");
      //graphRatioCombinedEtaA->Draw("p,same");
      One->Draw("same");
      // graphRatioCombinedPi0B->Draw("p,same");
      //graphRatioCombinedEtaB->Draw("p,same");

      CombinedSpeccanvas->Print(Form("%s/%s_Spectra_Combined_%s_%s_%s.%s",outputDir.Data(),textPi0New.Data(),textPrefix2.Data(),cutSel.Data(),fGammaCutSelection.Data(),suffix.Data()));
   }

   TCanvas *CombinedIncRatioCanvas = GetAndSetCanvas("CombinedIncRatioCanvas");
   histoIncRatioCombinedPurity = (TH1D*) histoGammaSpecCorrPurity->Clone("IncRatioCombinedPurity");
   histoIncRatioCombinedPurity->Divide(histoCombinedPi0);

   SetHistogramm(histoIncRatioCombinedPurity,"#it{p}_{T} (GeV/#it{c})", "Ratio Inclusive #gamma/#pi^{0}");

   DrawGammaSetMarker(histoIncRatioCombinedPurity, 22, 2.0, 3, 3);

   histoIncRatioCombinedPurity->Draw("e1");
   histoMCIncRatio->Draw("e1,same");
   histoIncRatioCombinedPurity->Draw("e1,same");
   histoIncRatioPurityTrueEff->Draw("e1,same");


   TLegend* leg_canvasIncRatioComb = GetAndSetLegend(0.2,0.8,3);
   leg_canvasIncRatioComb->AddEntry(histoIncRatioCombinedPurity,"Combined (Conversion + PHOS) #pi^{0}, conversion #gamma","p");
   leg_canvasIncRatioComb->AddEntry(histoIncRatioPurityTrueEff,"Conversion #pi^{0} and #gamma","p");
   leg_canvasIncRatioComb->AddEntry(histoMCIncRatio,"MC Ratio Phojet + Pythia","p");
   leg_canvasIncRatioComb->Draw();

   DrawAliceLogoAdv(0.8,0.5,"Work in Progress",option,"l",CombinedIncRatioCanvas,centrality);

   CombinedIncRatioCanvas->Print(Form("%s/%s_IncRatio_CombResults_%s_%s_%s.%s",outputDir.Data(),textPi0New.Data(),textPrefix2.Data(),cutSel.Data(),fGammaCutSelection.Data(),suffix.Data()));


   TCanvas* canvasComparisonCombined = GetAndSetCanvas("canvasComparisonCombined");
   DrawGammaCanvasSettings( canvasComparisonCombined, 0.1, 0.015, 0.01, 0.09);
   canvasComparisonCombined->SetLogy();

   TPad* padComparisonCombined  = new TPad("padComparisonCombined ", "", 0., 0.25, 1., 1.,-1, -1, -2);
   DrawGammaPadSettings( padComparisonCombined, 0.10, 0.015, 0.01, 0.);
   padComparisonCombined->Draw();

   TPad* padComparisonCombinedRatio = new TPad("padComparisonCombinedRatio", "", 0., 0., 1., 0.25,-1, -1, -2);
   DrawGammaPadSettings( padComparisonCombinedRatio, 0.1, 0.015, 0.0, 0.35);
   padComparisonCombinedRatio->Draw();

   padComparisonCombined->cd();
   padComparisonCombined->SetLogy();

   DrawGammaSetMarker(histoCombinedPi0, 20, 2.0, 1, 1);
   histoCombinedPi0->Draw();
   histoCorrectedYieldTrueEff->DrawCopy("same");

   TLegend* leg_canvasComparisonCombined = GetAndSetLegend(0.52,0.8,2);
   leg_canvasComparisonCombined->AddEntry(histoCombinedPi0,"Combined #pi^{0}");
   leg_canvasComparisonCombined->AddEntry(histoCorrectedYieldTrueEff,"Conversion #pi^{0}");
   leg_canvasComparisonCombined->Draw();

   padComparisonCombinedRatio->cd();

   histoConversionCombinedRatio = (TH1D*)histoCorrectedYieldTrueEff->Clone("histoConversionCombinedRatio");
   histoConversionCombinedRatio->Divide(histoCombinedPi0);
   SetHistogramm(histoConversionCombinedRatio,"#it{p}_{T} (GeV/#it{c})", "#frac{Conversion #pi^{0}}{Combined #pi^{0}}",0.6,1.8);
   histoConversionCombinedRatio->GetYaxis()->SetTitleSize(0.1);
   histoConversionCombinedRatio->GetYaxis()->SetTitleOffset(0.4);
   histoConversionCombinedRatio->GetYaxis()->CenterTitle(kTRUE);
   histoConversionCombinedRatio->GetYaxis()->SetNdivisions(5);
   histoConversionCombinedRatio->Draw();
   One->Draw("same");

   canvasComparisonCombined->Print(Form("%s/%s_ComparisonCombined_%s_%s_%s.%s",outputDir.Data(),textPi0New.Data(),textPrefix2.Data(),cutSel.Data(),fGammaCutSelection.Data(),suffix.Data()));


   //**********************************************************************************
   //******************** MC Decay Ratios *********************************************
   //**********************************************************************************

   TCanvas* canvasDecayGammaRatioMC = GetAndSetCanvas("canvasDecayGammaRatioMC");
   canvasDecayGammaRatioMC->SetLogy();

   DrawGammaSetMarker(histoDecayRatioSumGamma, 22, 2.0, 1, 1);
   histoDecayRatioSumGamma->GetXaxis()->SetRangeUser(0.0,20.);
   SetHistogramm(histoDecayRatioSumGamma,"#it{p}_{T} (GeV/#it{c})","Ratio #gamma from Decay / #pi^{0}",1e-5, 5e1);
   DrawGammaSetMarker(histoDecayRatioPi0Gamma, 22, 2.0, 2, 2);
   SetHistogramm(histoDecayRatioPi0Gamma,"#it{p}_{T} (GeV/#it{c})","Ratio #gamma from Decay / #pi^{0}");
   DrawGammaSetMarker(histoDecayRatioEtaGamma, 22, 2.0, 3, 3);
   SetHistogramm(histoDecayRatioEtaGamma,"#it{p}_{T} (GeV/#it{c})","Ratio #gamma from Decay / #pi^{0}");
   DrawGammaSetMarker(histoDecayRatioEtapGamma, 22, 2.0, 4, 4);
   SetHistogramm(histoDecayRatioEtapGamma,"#it{p}_{T} (GeV/#it{c})","Ratio #gamma from Decay / #pi^{0}");
   DrawGammaSetMarker(histoDecayRatioOmegaGamma, 22, 2.0, 5, 5);
   SetHistogramm(histoDecayRatioOmegaGamma,"#it{p}_{T} (GeV/#it{c})","Ratio #gamma from Decay / #pi^{0}");
   DrawGammaSetMarker(histoDecayRatioRho0Gamma, 22, 2.0, 6, 6);
   SetHistogramm(histoDecayRatioRho0Gamma,"#it{p}_{T} (GeV/#it{c})","Ratio #gamma from Decay / #pi^{0}");
   DrawGammaSetMarker(histoDecayRatioPhiGamma, 22, 2.0, 7, 7);
   SetHistogramm(histoDecayRatioPhiGamma,"#it{p}_{T} (GeV/#it{c})","Ratio #gamma from Decay / #pi^{0}");
   // DrawGammaSetMarker(histoDecayRatioSigmaGamma, 22, 2.0, 7, 7);
   // SetHistogramm(histoDecayRatioSigmaGamma,"#it{p}_{T} (GeV/#it{c})","Ratio #gamma from Decay / #pi^{0}");

   histoDecayRatioSumGamma->Draw("chist");
   histoDecayRatioPi0Gamma->Draw("chistsame");
   histoDecayRatioEtaGamma->Draw("chistsame");
   histoDecayRatioEtapGamma->Draw("chistsame");
   histoDecayRatioOmegaGamma->Draw("chistsame");
   histoDecayRatioRho0Gamma->Draw("chistsame");
   histoDecayRatioPhiGamma->Draw("chistsame");
   //histoDecayRatioSigmaGamma->Draw("chistsame");

   TLegend* legendDecayRatios = GetAndSetLegend(0.6,0.77,4);
   legendDecayRatios->AddEntry(histoDecayRatioSumGamma,"Sum","l");
   legendDecayRatios->AddEntry(histoDecayRatioPi0Gamma,"#gamma_{#pi^{0}} / #pi^{0}","l");
   legendDecayRatios->AddEntry(histoDecayRatioEtaGamma,"#gamma_{#eta} / #pi^{0}","l");
   legendDecayRatios->AddEntry(histoDecayRatioEtapGamma,"#gamma_{#eta'} / #pi^{0}","l");
   legendDecayRatios->Draw();

   TLegend* legendDecayRatiosB = GetAndSetLegend(0.75,0.82,3);
   legendDecayRatiosB->AddEntry(histoDecayRatioOmegaGamma,"#gamma_{#omega} / #pi^{0}","l");
   legendDecayRatiosB->AddEntry(histoDecayRatioRho0Gamma,"#gamma_{#rho^{0}} / #pi^{0}","l");
   legendDecayRatiosB->AddEntry(histoDecayRatioPhiGamma,"#gamma_{#phi} / #pi^{0}","l");
   //legendDecayRatiosB->AddEntry(histoDecayRatioSigmaGamma,"#gamma_{#phi} / #pi^{0}","l");
   legendDecayRatiosB->Draw();

   canvasDecayGammaRatioMC->Print(Form("%s/%s_MC_DecayRatio%s_%s_%s.%s",outputDir.Data(),textPi0New.Data(),centralityQM.Data(),cutSel.Data(),fGammaCutSelection.Data(),suffix.Data()));


   //**********************************************************************************
   //*********************** Cocktail *************************************************
   //**********************************************************************************
   cocktailFileA = new TFile(Form("CocktailInput/%s.root",fcocktailFuncA.Data()));
   cocktailFileB = new TFile(Form("CocktailInput/%s.root",fcocktailFuncB.Data()));
   cocktailFileC = new TFile(Form("CocktailInput/%s.root",fcocktailFuncC.Data()));
   cocktailFilePions = new TFile(Form("CocktailInput/%s.root",fcocktailFuncPions.Data()));
   cocktailFilePHOS = new TFile(Form("CocktailInput/%s.root",fcocktailFuncPHOS.Data()));
   cocktailFileWide = new TFile(Form("CocktailInput/%s.root",fcocktailFuncWide.Data()));
   cocktailFileNarrow = new TFile(Form("CocktailInput/%s.root",fcocktailFuncNarrow.Data()));
   cocktailFileSyst = new TFile(Form("CocktailInput/%s.root",fcocktailFuncSyst.Data()));
   cocktailDirA = (TDirectoryFile*) cocktailFileA->Get(fcocktailFuncA);
   cocktailDirB = (TDirectoryFile*) cocktailFileB->Get(fcocktailFuncB);
   cocktailDirC = (TDirectoryFile*) cocktailFileC->Get(fcocktailFuncC);
   cocktailDirPions = (TDirectoryFile*) cocktailFilePions->Get(fcocktailFuncPions);
   cocktailDirPHOS = (TDirectoryFile*) cocktailFilePHOS->Get(fcocktailFuncPHOS);
   cocktailDirWide = (TDirectoryFile*) cocktailFileWide->Get(fcocktailFuncWide);
   cocktailDirNarrow = (TDirectoryFile*) cocktailFileNarrow->Get(fcocktailFuncNarrow);
   cocktailDirSyst = (TDirectoryFile*) cocktailFileSyst->Get(fcocktailFuncSyst);

   cocktailFilepp = new TFile("CocktailInput/cocktail_7TeV_pi0LevyetaLevy.root");
   finalppFile =  new TFile("FinalResults/CombinedResultsPaperX_IncludingPP2760YShifted.root");
   cocktailDirpp = (TDirectoryFile*) cocktailFilepp->Get("cocktail_7TeV_pi0LevyetaLevy");
   cout<<"**********************************************************************************"<<endl;
   cout<<"**********************************************************************************"<<endl;
   cout<<fcocktailFuncA<<endl;
   cout<<"**********************************************************************************"<<endl;
   cout<<"**********************************************************************************"<<endl;


   cocktailPi0Pions = (TH1D* )cocktailDirPions->Get("ptPi0");
   cocktailPi0A = (TH1D* )cocktailDirA->Get("ptPi0");
   cocktailPi0B = (TH1D* )cocktailDirB->Get("ptPi0");
   cocktailPi0C = (TH1D* )cocktailDirC->Get("ptPi0");
   cocktailEtaA = (TH1D* )cocktailDirA->Get("ptEta");
   cocktailEtaB = (TH1D* )cocktailDirB->Get("ptEta");
   cocktailPi0 = (TH1D*)cocktailPi0A->Clone();
   cocktailEta = (TH1D*) cocktailEtaA->Clone("ptEta");
   cocktailEta->Add(cocktailEtaB);
   cocktailEta->Scale(0.5);
   cocktailEtaC = (TH1D* )cocktailDirC->Get("ptEta");
   cocktailOmega = (TH1D* )cocktailDirC->Get("ptOmega");
   cocktailEtap = (TH1D* )cocktailDirC->Get("ptEtaprime");
   cocktailPhi = (TH1D* )cocktailDirC->Get("ptPhi");
   cocktailSigma = (TH1D* )cocktailDirC->Get("ptSigma");
   cocktailEtaGammaA = (TH1D* )cocktailDirA->Get("ptgEta");
   cocktailEtaGammaB = (TH1D* )cocktailDirB->Get("ptgEta");
   cocktailEtaGammaC = (TH1D* )cocktailDirC->Get("ptgEta");
   cocktailEtaGammaPi0A = (TH1D* )cocktailDirA->Get("etagammapi0");
   cocktailEtaGammaPi0B = (TH1D* )cocktailDirB->Get("etagammapi0");
   cocktailEtaGammaPi0C = (TH1D* )cocktailDirC->Get("etagammapi0");

   
   TCanvas *etaComparsion = GetAndSetCanvas("EtaGammaPi0");
   etaComparsion->SetGridx();
   etaComparsion->SetGridy();

   TH1D *cocktailEtaGammaComparisonA = (TH1D*)cocktailEtaGammaA->Clone();
   cocktailEtaGammaComparisonA->Divide(cocktailEtaGammaB);
   TH1D *cocktailEtaGammaComparisonB = (TH1D*)cocktailEtaGammaA->Clone();
   cocktailEtaGammaComparisonB->Divide(cocktailEtaGammaC);

   TH1D *cocktailEtaComparisonA = (TH1D*)cocktailEtaA->Clone();
   cocktailEtaComparisonA->Divide(cocktailEtaB);
   TH1D *cocktailEtaComparisonB = (TH1D*)cocktailEtaA->Clone();
   cocktailEtaComparisonB->Divide(cocktailEtaC);

   TH1D *cocktailEtaGammaPi0ComparisonA = (TH1D*)cocktailEtaGammaPi0A->Clone();
   cocktailEtaGammaPi0ComparisonA->Divide(cocktailEtaGammaPi0B);
   TH1D *cocktailEtaGammaPi0ComparisonB = (TH1D*)cocktailEtaGammaPi0A->Clone();
   cocktailEtaGammaPi0ComparisonB->Divide(cocktailEtaGammaPi0C);


   cocktailEtaGammaComparisonA = RebinTH1D(cocktailEtaGammaComparisonA,histoCorrectedYieldTrueEff);
   cocktailEtaGammaComparisonB = RebinTH1D(cocktailEtaGammaComparisonB,histoCorrectedYieldTrueEff);
   cocktailEtaComparisonA = RebinTH1D(cocktailEtaComparisonA,histoCorrectedYieldTrueEff);
   cocktailEtaComparisonB = RebinTH1D(cocktailEtaComparisonB,histoCorrectedYieldTrueEff);
   cocktailEtaGammaPi0ComparisonA = RebinTH1D(cocktailEtaGammaPi0ComparisonA,histoCorrectedYieldTrueEff);
   cocktailEtaGammaPi0ComparisonB = RebinTH1D(cocktailEtaGammaPi0ComparisonB,histoCorrectedYieldTrueEff);

   SetHistogramm(cocktailEtaGammaPi0ComparisonA,"#it{p}_{T} (GeV/#it{c})", "#eta contribution ratios");

   DrawGammaSetMarker(cocktailEtaGammaPi0ComparisonA, 20, 2.0,kRed-7,kRed-7);
   DrawGammaSetMarker(cocktailEtaGammaPi0ComparisonB, 20, 2.0,kRed+2,kRed+2);
   DrawGammaSetMarker(cocktailEtaComparisonA, 24, 2.0,kBlack,kBlack);
   DrawGammaSetMarker(cocktailEtaComparisonB, 24, 2.0,kGray+2,kGray+2);
   DrawGammaSetMarker(cocktailEtaGammaComparisonA, 28, 2.0,kBlue+2,kBlue+2);
   DrawGammaSetMarker(cocktailEtaGammaComparisonB, 28, 2.0,kBlue-9,kBlue-9);

   cocktailEtaGammaPi0ComparisonA->GetYaxis()->SetRangeUser(0.8,1.5);

   cocktailEtaGammaPi0ComparisonA->Draw("");
   cocktailEtaGammaPi0ComparisonB->Draw("same");
   cocktailEtaComparisonA->Draw("same");
   cocktailEtaComparisonB->Draw("same");
   cocktailEtaGammaComparisonA->Draw("same");
   cocktailEtaGammaComparisonB->Draw("same");


   TLegend* leg_EtaComp = GetAndSetLegend(0.5,0.55,8);
   leg_EtaComp->AddEntry(cocktailEtaGammaPi0ComparisonA,"(#gamma_{#eta}/#pi^{0})^{high-pT}/(#gamma_{#eta}/#pi^{0})^{thmodel}");
   leg_EtaComp->AddEntry(cocktailEtaGammaPi0ComparisonB,"(#gamma_{#eta}/#pi^{0})^{high-pT}/(#gamma_{#eta}/#pi^{0})^{mT}");
   leg_EtaComp->AddEntry(cocktailEtaComparisonA,"#eta^{high-pT}/#eta^{thmodel}");
   leg_EtaComp->AddEntry(cocktailEtaComparisonB,"#eta^{high-pT}/#eta^{mT}");
   leg_EtaComp->AddEntry(cocktailEtaGammaComparisonA,"#gamma_{#eta}^{high-pT}/#gamma_{#eta}^{thmodel}");
   leg_EtaComp->AddEntry(cocktailEtaGammaComparisonB,"#gamma_{#eta}^{high-pT}/#gamma_{#eta}^{mT}");
   leg_EtaComp->Draw();

   if(option.CompareTo("PbPb_2.76TeV") == 0) DrawCentrality(0.2,0.9,centrality);

   etaComparsion->Print(Form("%s/%s_ComparisonEta_%s_%s_%s.%s",outputDir.Data(),textPi0New.Data(),textPrefix2.Data(),cutSel.Data(),fGammaCutSelection.Data(),suffix.Data()));

   // TFile *dmcockb = new TFile("Cocktail.root");

   // // TFile *dmcock = new TFile("CocktailInput/cocktail_PbPb_0020_qcd_PHOS_scaledK0s.root");
   // // TDirectoryFile *dmcockdir = (TDirectoryFile*)dmcock->Get("cocktail_PbPb_0020_qcd_PHOS_scaledK0s");
   // // TH1D *Pi0Dmitric = (TH1D*)dmcockdir->Get("ptPi0");
   // // TH1D *gammapi0Dmitri = (TH1D*)dmcockdir->Get("ptgPi0");

   // // // Pi0Dmitri->Divide(cocktailPi0A);
   // // // Pi0Dmitri->Draw();

   // // // return;

   // TH1D *Pi0Dmitri = (TH1D*)dmcockb->Get("hPi0Sp_cen6");
   // TH1D *GammaDmitri = (TH1D*)dmcockb->Get("hTotGammaSp_cen6_Stat");


   // GammaDmitri->Divide(Pi0Dmitri);
   // GammaDmitri->Draw();
   // return;
   // // TH1D *EtaDmitri = (TH1D*)dmcock->Get("hEtaSp_cen6");
   // // TH1D *OmegaDmitri = (TH1D*)dmcock->Get("hOmegaSp_cen6");

   // for(Int_t i = 0;i<Pi0Dmitri->GetNbinsX();i++){
   //    Pi0Dmitri->SetBinContent(i+1,(Pi0Dmitri->GetBinContent(i+1))/(Pi0Dmitri->GetBinCenter(i+1)));
   //    //EtaDmitri->SetBinContent(i+1,EtaDmitri->GetBinContent(1+1)/EtaDmitri->GetBinWidth(1+1));
   //    //OmegaDmitri->SetBinContent(i+1,OmegaDmitri->GetBinContent(1+1)/OmegaDmitri->GetBinWidth(1+1));
   //    GammaDmitri->SetBinContent(i+1,(GammaDmitri->GetBinContent(i+1))/(GammaDmitri->GetBinCenter(i+1)));
   // }

   // Pi0Dmitric = RebinTH1D(Pi0Dmitric,Pi0Dmitri);
   // gammapi0Dmitri = RebinTH1D(gammapi0Dmitri,Pi0Dmitri);
   // Pi0Dmitric->Divide(Pi0Dmitri);
   // gammapi0Dmitri->Divide(GammaDmitri);


   // Pi0Dmitric->Draw();
   // gammapi0Dmitri->Draw("same");
   // // cocktailPi0A = RebinTH1D(cocktailPi0A,Pi0Dmitri);
   // // cocktailEtaGammaB = RebinTH1D(cocktailEtaGammaB,Pi0Dmitri);
   // // //cocktailEtaGammaB->Divide(cocktailPi0A);
   // // cocktailPi0A->Divide(Pi0Dmitric);
   // // cocktailEtaGammaB->Divide(GammaDmitric);
   // // // cocktailPi0A->Divide(Pi0Dmitri);
   // // cocktailEtaGammaB->Draw();
   // // cocktailPi0A->Draw("same");
   // // // GammaDmitri->Divide(Pi0Dmitri);
   //return;
   // // GammaDmitri->Draw();
   // // cocktailEtaGammaB->Draw("same");
   // //cocktailPi0A->Scale(Pi0Dmitri->GetBinContent(5)/cocktailPi0A->GetBinContent(5));
   // // histoCorrectedYieldTrueEff->Draw();
   // // CombinedChargedPionsStatAverage->Draw("same");
   // // //cocktailPi0A->Scale(histoCorrectedYieldTrueEff->GetBinContent(5)/cocktailPi0A->GetBinContent(5));
   // // Pi0Dmitri->Scale(cocktailPi0A->GetBinContent(5)/Pi0Dmitri->GetBinContent(5));
   // // Pi0Dmitri->Draw("same");
   // // cocktailPi0A->SetMarkerStyle(20);
   // // cocktailPi0A->SetMarkerColor(kBlue);
   // // cocktailPi0A->SetMarkerSize(1);
   // // cocktailPi0A->Draw("same");

   // //cocktailPi0A->Divide(cocktailEtaGammaB,cocktailPi0A);

   // return;

   //TH1D *pi0Syst = (TH1D*) cocktailDirSyst->Get("ptPi0");

   TCanvas *cocktailCanvasMesonSpec = GetAndSetCanvas("cocktailCanvasMesonSpec");
   cocktailCanvasMesonSpec->SetLogy();
   cocktailCanvasMesonSpec->SetGridx();
   cocktailCanvasMesonSpec->SetGridy();
   DrawGammaSetMarker(cocktailPi0A, 20, 2.0,kGreen+1,kGreen+1);
   if(option.CompareTo("PbPb_2.76TeV") == 0) SetHistogramm(cocktailPi0A,"#it{p}_{T} (GeV/#it{c})", "#frac{1}{2#pi N_{ev.}} #frac{d^{2}N}{#it{p}_{T}d#it{p}_{T}dy} (GeV^{-2}c)",5e-8,1e3);
   else SetHistogramm(cocktailPi0A,"#it{p}_{T} (GeV/#it{c})", "#frac{1}{2#pi N_{ev.}} #frac{d^{2}N}{#it{p}_{T}d#it{p}_{T}dy} (GeV^{-2}c)",5e-10,10);
   DrawGammaSetMarker(cocktailPi0A, 20, 2.0,kRed,kRed);
   SetHistogramm(cocktailEtaA,"#it{p}_{T} (GeV/#it{c})", "#frac{1}{2#pi N_{ev.}} #frac{d^{2}N}{#it{p}_{T}d#it{p}_{T}dy} (GeV^{-2}c)");
   DrawGammaSetMarker(cocktailEtaA, 20, 2.0,kMagenta,kMagenta);

   cocktailPi0A->GetXaxis()->SetRangeUser(0.4,(histoCorrectedYieldTrueEff->GetXaxis())->GetBinUpEdge(histoCorrectedYieldTrueEff->GetNbinsX()));
   cocktailPi0A->GetYaxis()->SetTitleSize(0.035);
   cocktailPi0A->GetYaxis()->SetTitleOffset(1.3);
   cocktailPi0A->GetXaxis()->SetRangeUser(0.4,16);
   cocktailPi0A->Draw("chist");
   cocktailPi0A->DrawCopy("same");
   cocktailEtaA->DrawCopy("csamehist");
   ConversionFitA->DrawCopy("same");
   ConversionFitB->DrawCopy("same");
   ConversionFitC->DrawCopy("same");
   //pi0Syst->DrawCopy("same");
   CombinedNeutralAndChargedPions->DrawCopy("same");
   CombinedChargedPionsStatAverage->DrawCopy("same");

   // explanation of points
   DrawGammaSetMarker(histoCorrectedYieldTrueEff, 4, 1., 1, 1);

   histoCorrectedYieldTrueEff->Draw("e1,same");
   //histoCorrectedEtaTrueEff->Draw("e1,same");

   if(option.CompareTo("PbPb_2.76TeV") == 0){
      gammaL= new TLatex(4.,0.053,"#pi^{0} from ALICE Data");
      tpi = new TLatex(.6,.3,"cocktail #pi^{0}");
      teta = new TLatex(.6,0.06,"cocktail #eta");
      tetaprime = new TLatex(1.5,6,"#eta yield obtained via m_{t} scaling");
      tomega = new TLatex(1.,60,"Blast Wave Fit, <#beta> = 0.66, T = 80 MeV");
      tomega->SetTextFont(42);
      tomega->SetTextColor(kBlue);
      tomega->SetTextSize(0.04);
      //tomega->Draw();
   }
   else{
      gammaL= new TLatex(3.0,0.002,"#pi^{0} from ALICE Data");
      tetaprime = new TLatex(1.0,0.0001,"#eta  from ALICE Data");
      tpi = new TLatex(.5,1.5,"#pi^{0}");
      teta = new TLatex(.5,0.005,"#eta");
   }

   gammaL->SetTextColor(kBlack);
   gammaL->SetTextSize(0.035);
   gammaL->SetTextFont(42);
   gammaL->Draw();
   tpi->SetTextColor(kRed);
   tpi->SetTextSize(0.04);
   tpi->SetTextFont(42);
   tpi->Draw();
   teta->SetTextColor(kBlue);
   teta->SetTextSize(0.04);
   teta->SetTextFont(42);
   teta->Draw();
   tetaprime->SetTextFont(42);
   tetaprime->SetTextColor(kMagenta);
   tetaprime->SetTextSize(0.035);
   tetaprime->Draw();

   TLegend* leg_MesonSpectra = GetAndSetLegend(0.5,0.7,4);
   leg_MesonSpectra->AddEntry(cocktailPi0A,"Cocktail Pi0");
   leg_MesonSpectra->AddEntry(ConversionFitA,ConversionFitA->GetName(),"l");
   leg_MesonSpectra->AddEntry(ConversionFitB,ConversionFitB->GetName(),"l");
   leg_MesonSpectra->AddEntry(ConversionFitC,ConversionFitC->GetName(),"l");
   leg_MesonSpectra->Draw();

   DrawAliceLogoAdv(0.12,0.13,"Work in Progress",option,"r",cocktailCanvasMesonSpec,centrality);

   cocktailCanvasMesonSpec->Print(Form("%s/%s_Cocktail_MesonSpectra%s_%s_%s.%s",outputDir.Data(),textPi0New.Data(),centralityQM.Data(),cutSel.Data(),fGammaCutSelection.Data(),suffix.Data()));


   TCanvas *canvasRatioCocktailToYield = GetAndSetCanvas("RatioCocktailToYield");

   cocktailAllGammaA = (TH1D* )cocktailDirA->Get("ptg");
   cocktailAllGammaB = (TH1D* )cocktailDirB->Get("ptg");
   cocktailAllGammaC = (TH1D* )cocktailDirC->Get("ptg");
   cocktailPi0Gamma = (TH1D* )cocktailDirA->Get("ptgPi0");
   cocktailEtaGamma = (TH1D* )cocktailDirA->Get("ptgEta");
   cocktailEtapGamma = (TH1D* )cocktailDirA->Get("ptgEtaprime");
   cocktailOmegaGamma = (TH1D* )cocktailDirA->Get("ptgOmega");
   cocktailPhiGamma = (TH1D* )cocktailDirA->Get("ptgPhi");
   cocktailRhoGamma = (TH1D* )cocktailDirA->Get("ptgRho");
   cocktailSigmaGamma = (TH1D* )cocktailDirA->Get("ptgSigma");

   TH1D *RatioCocktailToYield = (TH1D*)RebinTH1D(cocktailPi0A,histoCorrectedYieldTrueEff)->Clone("RatioCocktailToYield");
   RatioCocktailToYield->Divide(histoCorrectedYieldTrueEff);
   SetHistogramm(RatioCocktailToYield,"#it{p}_{T} (GeV/#it{c})", "Cocktail #pi^{0} / #pi^{0}",0.7,1.3);

   TH1D *RatioYieldToFit = (TH1D*)histoCorrectedYieldTrueEff->Clone("RatioYieldToFit");
   RatioYieldToFit->Divide(ConversionFitA);
   SetHistogramm(RatioYieldToFit,"#it{p}_{T} (GeV/#it{c})", "Cocktail #pi^{0} / #pi^{0}",0.7,1.3);
   TH1D *RatioYieldToFitB = (TH1D*)histoCorrectedYieldTrueEff->Clone("RatioYieldToFitB");
   RatioYieldToFitB->Divide(ConversionFitB);
   SetHistogramm(RatioYieldToFitB,"#it{p}_{T} (GeV/#it{c})", "Cocktail #pi^{0} / #pi^{0}",0.7,1.3);
   DrawGammaSetMarker(RatioYieldToFitB, 20, 2.0,kMagenta,kMagenta);


   TH1D *RatioCocktailToFit = (TH1D*) histoIncRatioFitPurityA->Clone("RatioCocktailToFit");
   RatioCocktailToFit->Divide(histoGammaSpecCorrPurity);
   RatioCocktailToFit->Multiply(RebinTH1D(cocktailPi0A,histoCorrectedYieldTrueEff));
   SetHistogramm(RatioCocktailToFit,"#it{p}_{T} (GeV/#it{c})", "Cocktail #pi^{0} / #pi^{0}",0,2);


   TH1D *RatioCocktailToChargedYield = (TH1D*) histoIncRatioFitPurityPionsStatAverage->Clone("RatioCocktailToFit");
   RatioCocktailToChargedYield->Divide(histoGammaSpecCorrPurity);
   RatioCocktailToChargedYield->Multiply(RebinTH1D(cocktailPi0Pions,histoCorrectedYieldTrueEff));
   RatioCocktailToYield->GetYaxis()->SetRangeUser(0.7,1.3);

   // RatioCocktailToYield->DrawCopy("e1");
   // RatioCocktailToFit->DrawCopy("e1same");
   RatioYieldToFit->DrawCopy("e1");
   RatioYieldToFitB->DrawCopy("e1same");
   One->Draw("same");
   // RatioCocktailToYield->DrawCopy("e1same");
   // RatioCocktailToFit->DrawCopy("e1same");
   // RatioCocktailToChargedYield->DrawCopy("e1same");


   // CombinedNeutralAndChargedPions->Divide(ConversionFitB);
   // CombinedChargedPionsStatAverage->Divide(ConversionFitB);

   // CombinedNeutralAndChargedPions->GetYaxis()->SetRangeUser(0.5,1.5);
   // CombinedNeutralAndChargedPions->GetXaxis()->SetRangeUser(0.8,20);
   // CombinedNeutralAndChargedPions->Draw("e1");
   // CombinedChargedPionsStatAverage->Draw("same");
   // One->Draw("same");


   TLegend* leg_RatioCocktailToYield = GetAndSetLegend(0.2,0.8,2);
   leg_RatioCocktailToYield->AddEntry(RatioCocktailToYield,"Cocktail #pi^{0} / #pi^{0} spectrum");
   leg_RatioCocktailToYield->AddEntry(RatioCocktailToFit,"Cocktail #pi^{0} / #pi^{0} fit");
   leg_RatioCocktailToYield->Draw();


   canvasRatioCocktailToYield->Print(Form("%s/%s_CocktailToYieldRatio_%s_%s_%s.%s",outputDir.Data(),textPi0New.Data(),centralityQM.Data(),cutSel.Data(),fGammaCutSelection.Data(),suffix.Data()));


   TCanvas *cocktailCanvasSpec = GetAndSetCanvas("cocktailCanvasSpec");
   cocktailCanvasSpec->SetLogy();
   SetHistogramm(cocktailAllGammaA,"#it{p}_{T} (GeV/#it{c})", "#frac{1}{2#pi N_{ev.}} #frac{d^{2}N}{#it{p}_{T}d#it{p}_{T}dy} (GeV^{-2}c)",5e-13,1e3);
   DrawGammaSetMarker(cocktailAllGammaA, 20, 2.0,kGreen+1,kGreen+1);
   SetHistogramm(cocktailPi0Gamma,"#it{p}_{T} (GeV/#it{c})", "#frac{1}{2#pi N_{ev.}} #frac{d^{2}N}{#it{p}_{T}d#it{p}_{T}dy} (GeV^{-2}c)");
   DrawGammaSetMarker(cocktailPi0Gamma, 20, 2.0,kRed,kRed);
   SetHistogramm(cocktailEtaGamma,"#it{p}_{T} (GeV/#it{c})", "#frac{1}{2#pi N_{ev.}} #frac{d^{2}N}{#it{p}_{T}d#it{p}_{T}dy} (GeV^{-2}c)");
   DrawGammaSetMarker(cocktailEtaGamma, 20, 2.0,kBlue,kBlue);
   SetHistogramm(cocktailEtapGamma,"#it{p}_{T} (GeV/#it{c})", "#frac{1}{2#pi N_{ev.}} #frac{d^{2}N}{#it{p}_{T}d#it{p}_{T}dy} (GeV^{-2}c)");
   DrawGammaSetMarker(cocktailEtapGamma, 20, 2.0,kOrange+1,kOrange+1);
   SetHistogramm(cocktailOmegaGamma,"#it{p}_{T} (GeV/#it{c})", "#frac{1}{2#pi N_{ev.}} #frac{d^{2}N}{#it{p}_{T}d#it{p}_{T}dy} (GeV^{-2}c)");
   DrawGammaSetMarker(cocktailOmegaGamma, 20, 2.0,kYellow+2,kYellow+2);
   SetHistogramm(cocktailPhiGamma,"#it{p}_{T} (GeV/#it{c})", "#frac{1}{2#pi N_{ev.}} #frac{d^{2}N}{#it{p}_{T}d#it{p}_{T}dy} (GeV^{-2}c)");
   DrawGammaSetMarker(cocktailPhiGamma, 20, 2.0,kViolet,kViolet);
   SetHistogramm(cocktailRhoGamma,"#it{p}_{T} (GeV/#it{c})", "#frac{1}{2#pi N_{ev.}} #frac{d^{2}N}{#it{p}_{T}d#it{p}_{T}dy} (GeV^{-2}c)");
   DrawGammaSetMarker(cocktailRhoGamma, 20, 2.0,kAzure-2,kAzure-2);
   SetHistogramm(cocktailSigmaGamma,"#it{p}_{T} (GeV/#it{c})", "#frac{1}{2#pi N_{ev.}} #frac{d^{2}N}{#it{p}_{T}d#it{p}_{T}dy} (GeV^{-2}c)");
   DrawGammaSetMarker(cocktailSigmaGamma, 20, 2.0,kRed-2,kRed-2);


   cocktailAllGammaA->GetXaxis()->SetRangeUser(0,(histoGammaSpecCorrPurity->GetXaxis())->GetBinUpEdge(histoGammaSpecCorrPurity->GetNbinsX()));
   cocktailAllGammaA->GetYaxis()->SetTitleSize(0.035);
   cocktailAllGammaA->GetYaxis()->SetTitleOffset(1.3);
   cocktailAllGammaA->GetXaxis()->SetRangeUser(0.0,16);
   cocktailAllGammaA->Draw("chist");
   cocktailPi0Gamma->Draw("csamehist");
   cocktailEtaGamma->Draw("csamehist");
   cocktailEtapGamma->Draw("csamehist");
   cocktailOmegaGamma->Draw("csamehist");
   cocktailPhiGamma->Draw("csamehist");
   cocktailRhoGamma->Draw("csamehist");
   cocktailSigmaGamma->Draw("csamehist");

   // explanation of points
   DrawGammaSetMarker(histoGammaSpecCorrPurity, 4, 1., 1, 1);

   histoCorrectedYieldTrueEff->Draw("e1,same");
   if(option.CompareTo("PbPb_2.76TeV") == 0){
      gammaL= new TLatex(2.0,5.0,"#gamma from ALICE Data");
      cocktail= new TLatex(9.0,120,"all decay #gamma");
      tpi = new TLatex(9.0,20.,"#pi^{0} #rightarrow #gamma#gamma (e^{+}e^{-}#gamma)");
      teta = new TLatex(9.0,4.,"#eta #rightarrow #gamma#gamma (#pi^{+}#pi^{-}#gamma,e^{+}e^{-}#gamma,#pi^{0}#gamma#gamma)");
      tomega = new TLatex(9.0,0.8,"#omega #rightarrow #pi^{0}#gamma (#eta#gamma)");
      tetaprime = new TLatex(9.0,0.15,"#eta' #rightarrow #rho#gamma (#omega#gamma, #gamma#gamma)");
      tphi = new TLatex(9.0,0.02,"#phi #rightarrow #eta#gamma (#pi^{0}#gamma, #omega#gamma)");
      trho = new TLatex(9.0,0.003,"#rho #rightarrow #pi^{+}#pi^{-}#gamma (#pi^{0}#gamma, #eta#gamma)");
      tsigma = new TLatex(10.0,0.0005,"#Sigma^{0} #rightarrow #Lambda #gamma (#Lambda#gamma#gamma)");
   }
   else{
      gammaL= new TLatex(3.0,0.0007,"#gamma from ALICE Data");
      nlo= new TLatex(7.9,0.000005,"NLO Direct Gamma (#mu=#it{p}_{T}/2, #it{p}_{T}, 2#it{p}_{T})");
      nlo->SetTextColor(kRed+2);
      nlo->SetTextSize(0.035);
      //nlo->Draw();
      cocktail= new TLatex(10.0,120,"all decay #gamma");
      tpi = new TLatex(10.0,20.,"#pi^{0} #rightarrow #gamma#gamma (e^{+}e^{-}#gamma)");
      teta = new TLatex(10.0,4.,"#eta #rightarrow #gamma#gamma (#pi^{+}#pi^{-}#gamma,e^{+}e^{-}#gamma,#pi^{0}#gamma#gamma)");
      tomega = new TLatex(10.0,0.8,"#omega #rightarrow #pi^{0}#gamma (#eta#gamma)");
      tetaprime = new TLatex(10.0,0.15,"#eta' #rightarrow #rho#gamma (#omega#gamma, #gamma#gamma)");
      tphi = new TLatex(10.0,0.02,"#phi #rightarrow #eta#gamma (#pi^{0}#gamma, #omega#gamma)");
      trho = new TLatex(10.0,0.003,"#rho #rightarrow #pi^{+}#pi^{-}#gamma (#pi^{0}#gamma, #eta#gamma)");
      tsigma = new TLatex(10.0,0.0005,"#Sigma^{0} #rightarrow #Lambda #gamma (#Lambda#gamma#gamma)");
   }

   // gammaL->SetTextColor(kBlack);
   // gammaL->SetTextSize(0.035);
   // gammaL->SetTextFont(42);
   // gammaL->Draw();
   cocktail->SetTextColor(kGreen+1);
   cocktail->SetTextSize(0.04);
   cocktail->SetTextFont(42);
   cocktail->Draw();
   tpi->SetTextColor(kRed);
   tpi->SetTextSize(0.04);
   tpi->SetTextFont(42);
   tpi->Draw();
   teta->SetTextColor(kBlue);
   teta->SetTextSize(0.04);
   teta->SetTextFont(42);
   teta->Draw();
   tomega->SetTextColor(kYellow+2);
   tomega->SetTextSize(0.04);
   tomega->SetTextFont(42);
   tomega->Draw();
   tetaprime->SetTextColor(kOrange+1);
   tetaprime->SetTextSize(0.04);
   tetaprime->SetTextFont(42);
   tetaprime->Draw();
   tphi->SetTextColor(kViolet);
   tphi->SetTextSize(0.04);
   tphi->SetTextFont(42);
   tphi->Draw();
   trho->SetTextColor(kAzure-2);
   trho->SetTextSize(0.04);
   trho->SetTextFont(42);
   trho->Draw();
   tsigma->SetTextColor(kRed-2);
   tsigma->SetTextSize(0.04);
   tsigma->SetTextFont(42);
   tsigma->Draw();


   if(option.CompareTo("PbPb_2.76TeV") == 0) DrawAliceLogoAdv(0.15,0.15,"Work in Progress",option,"r",cocktailCanvasSpec,centrality);
   else DrawAliceLogoAdv(0.22,0.7,"Work in Progress",option,"r",cocktailCanvasSpec,centrality);

   cocktailCanvasSpec->Print(Form("%s/%s_Cocktail_Spectra%s_%s_%s.%s",outputDir.Data(),textPi0New.Data(),centralityQM.Data(),cutSel.Data(),fGammaCutSelection.Data(),suffix.Data()));


   cocktailAllGammaPi0A = (TH1D*)cocktailDirA->Get("sumgammapi0");
   cocktailAllGammaPi0B = (TH1D*)cocktailDirB->Get("sumgammapi0");
   cocktailAllGammaPi0C = (TH1D*)cocktailDirC->Get("sumgammapi0");
   cocktailAllGammaPi0Pions = (TH1D*)cocktailDirPions->Get("sumgammapi0");

   TCanvas *CocktailComparsion = GetAndSetCanvas("EtaGammaPi0");
   CocktailComparsion->SetGridx();
   CocktailComparsion->SetGridy();

   TH1D *cocktailComparisonA = (TH1D*)cocktailAllGammaPi0A->Clone();
   cocktailComparisonA->Divide(cocktailAllGammaPi0B);
   TH1D *cocktailComparisonB = (TH1D*)cocktailAllGammaPi0A->Clone();
   cocktailComparisonB->Divide(cocktailAllGammaPi0C);

   cocktailComparisonA = RebinTH1D(cocktailComparisonA,histoCorrectedYieldTrueEff);
   cocktailComparisonB = RebinTH1D(cocktailComparisonB,histoCorrectedYieldTrueEff);

   SetHistogramm(cocktailComparisonA,"#it{p}_{T} (GeV/#it{c})", "cocktail ratios");

   DrawGammaSetMarker(cocktailComparisonA, 20, 2.0,kRed-7,kRed-7);
   DrawGammaSetMarker(cocktailComparisonB, 20, 2.0,kRed+2,kRed+2);

   cocktailComparisonA->GetYaxis()->SetRangeUser(0.9,1.1);

   cocktailComparisonA->Draw();
   cocktailComparisonB->Draw("same");

   TLegend* leg_CocktailComp = GetAndSetLegend(0.5,0.75,3);
   leg_CocktailComp->AddEntry(cocktailComparisonA,"(#gamma/#pi^{0})^{high-pT}/(#gamma/#pi^{0})^{thmodel}");
   leg_CocktailComp->AddEntry(cocktailComparisonB,"(#gamma/#pi^{0})^{high-pT}/(#gamma/#pi^{0})^{mT}");
   leg_CocktailComp->Draw();

   if(option.CompareTo("PbPb_2.76TeV") == 0) DrawCentrality(0.2,0.9,centrality);

   CocktailComparsion->Print(Form("%s/%s_ComparisonCocktail_%s_%s_%s.%s",outputDir.Data(),textPi0New.Data(),textPrefix2.Data(),cutSel.Data(),fGammaCutSelection.Data(),suffix.Data()));


   TCanvas *cocktailCanvasRatio = GetAndSetCanvas("cocktailCanvasRatio");
   cocktailCanvasRatio->SetLogy();


   TH1D *cocktailAllGammaPionsRebined = (TH1D*) cocktailDirPions->Get("ptg");
   cocktailAllGammaPionsRebined = RebinTH1D(cocktailAllGammaPionsRebined,histoIncRatioPurity);
   TH1D *cocktailPi0PionsRebined = (TH1D*) cocktailDirPions->Get("ptPi0");
   cocktailPi0PionsRebined = RebinTH1D(cocktailPi0PionsRebined,histoIncRatioPurity);
   cocktailAllGammaPi0Pions = RebinTH1D(cocktailPi0PionsRebined,histoIncRatioPurity);
   cocktailAllGammaPi0Pions->Divide(cocktailAllGammaPionsRebined,cocktailPi0PionsRebined);

   cocktailAllGammaPionsRebined->Draw();
   cocktailPi0PionsRebined->Draw("same");

   cocktailAllGammaPi0Wide = (TH1D*)cocktailDirWide->Get("sumgammapi0");
   cocktailAllGammaPi0Narrow = (TH1D*)cocktailDirNarrow->Get("sumgammapi0");
   cocktailAllGammaPi0Syst = (TH1D*)cocktailDirSyst->Get("sumgammapi0");
   cocktailPi0GammaPi0 = (TH1D*)cocktailDirA->Get("pi0gammapi0");
   cocktailEtaGammaPi0 = (TH1D*)cocktailDirA->Get("etagammapi0");
   cocktailOmegaGammaPi0 = (TH1D*)cocktailDirA->Get("omegagammapi0");
   cocktailEtapGammaPi0 = (TH1D*)cocktailDirA->Get("etapgammapi0");
   cocktailPhiGammaPi0 = (TH1D*)cocktailDirA->Get("phigammapi0");
   cocktailRhoGammaPi0 = (TH1D*)cocktailDirA->Get("rhogammapi0");
   cocktailSigmaGammaPi0 = (TH1D*)cocktailDirA->Get("sigmagammapi0");

   SetHistogramm(cocktailAllGammaPi0A,"#it{p}_{T} (GeV/#it{c})","Ratio #gamma / #pi^{0} from different sources",2e-6,5e3);
   DrawGammaSetMarker(cocktailAllGammaPi0A, 20, 2.0,kGreen+1,kGreen+1);
   SetHistogramm(cocktailPi0GammaPi0,"#it{p}_{T} (GeV/#it{c})","Ratio #gamma / #pi^{0} from different sources");
   DrawGammaSetMarker(cocktailPi0GammaPi0, 20, 2.0,kRed,kRed);
   SetHistogramm(cocktailEtaGammaPi0,"#it{p}_{T} (GeV/#it{c})","Ratio #gamma / #pi^{0} from different sources");
   DrawGammaSetMarker(cocktailEtaGammaPi0, 20, 2.0,kBlue,kBlue);
   SetHistogramm(cocktailEtapGammaPi0,"#it{p}_{T} (GeV/#it{c})","Ratio #gamma / #pi^{0} from different sources");
   DrawGammaSetMarker(cocktailEtapGammaPi0, 20, 2.0,kOrange+1,kOrange+1);
   SetHistogramm(cocktailOmegaGammaPi0,"#it{p}_{T} (GeV/#it{c})","Ratio #gamma / #pi^{0} from different sources");
   DrawGammaSetMarker(cocktailOmegaGammaPi0, 20, 2.0,kYellow+2,kYellow+2);
   SetHistogramm(cocktailPhiGammaPi0,"#it{p}_{T} (GeV/#it{c})","Ratio #gamma / #pi^{0} from different sources");
   DrawGammaSetMarker(cocktailPhiGammaPi0, 20, 2.0,kViolet,kViolet);
   SetHistogramm(cocktailRhoGammaPi0,"#it{p}_{T} (GeV/#it{c})","Ratio #gamma / #pi^{0} from different sources");
   DrawGammaSetMarker(cocktailRhoGammaPi0, 20, 2.0,kAzure-2,kAzure-2);
   SetHistogramm(cocktailSigmaGammaPi0,"#it{p}_{T} (GeV/#it{c})","Ratio #gamma / #pi^{0} from different sources");
   DrawGammaSetMarker(cocktailSigmaGammaPi0, 20, 2.0,kRed-2,kRed-2);

   cocktailAllGammaPi0A->GetXaxis()->SetRangeUser(0.,(histoGammaSpecCorrPurity->GetXaxis())->GetBinUpEdge(histoGammaSpecCorrPurity->GetNbinsX()));
   cocktailAllGammaPi0A->Draw("chist");
   cocktailPi0GammaPi0->Draw("csamehist");
   cocktailEtaGammaPi0->Draw("csamehist");
   cocktailEtapGammaPi0->Draw("csamehist");
   cocktailOmegaGammaPi0->Draw("csamehist");
   cocktailPhiGammaPi0->Draw("csamehist");
   cocktailRhoGammaPi0->Draw("csamehist");
   cocktailSigmaGammaPi0->Draw("csamehist");


   if(option.CompareTo("PbPb_2.76TeV") == 0){
      cocktail= new TLatex(7.0,1200.,"all decay #gamma");
      gammaL= new TLatex(4.7,0.1,"#gamma_{inc}/#pi^{0} from ALICE Data");
      tpi = new TLatex(7.0,400.,"#pi^{0} #rightarrow #gamma#gamma (e^{+}e^{-}#gamma)");
      teta = new TLatex(7.0,140.,"#eta #rightarrow #gamma#gamma (#pi^{+}#pi^{-}#gamma,e^{+}e^{-}#gamma,#pi^{0}#gamma#gamma)");
      tomega = new TLatex(7.0,40.,"#omega #rightarrow #pi^{0}#gamma (#eta#gamma)");
      tetaprime = new TLatex(7.0,17,"#eta' #rightarrow #rho#gamma (#omega#gamma, #gamma#gamma)");
      tphi = new TLatex(7.0,6.,"#phi #rightarrow #eta#gamma (#pi^{0}#gamma, #omega#gamma)");
      trho = new TLatex(7.0,2.,"#rho #rightarrow #pi^{+}#pi^{-}#gamma (#pi^{0}#gamma, #eta#gamma)");
      tsigma = new TLatex(7.0,0.7,"#Sigma^{0} #rightarrow #Lambda#gamma (#Lambda#gamma#gamma)");
   }
   else{
      gammaL= new TLatex(2.8,1,"#gamma_{inc}/#pi^{0} from ALICE Data");
      cocktail= new TLatex(10.5,1200.,"all decay #gamma");
      tpi = new TLatex(10.5,400.,"#pi^{0} #rightarrow #gamma#gamma (e^{+}e^{-}#gamma)");
      teta = new TLatex(10.5,140.,"#eta #rightarrow #gamma#gamma (#pi^{+}#pi^{-}#gamma,e^{+}e^{-}#gamma,#pi^{0}#gamma#gamma)");
      tomega = new TLatex(10.5,40.,"#omega #rightarrow #pi^{0}#gamma (#eta#gamma)");
      tetaprime = new TLatex(10.5,17,"#eta' #rightarrow #rho#gamma (#omega#gamma, #gamma#gamma)");
      tphi = new TLatex(10.5,6.,"#phi #rightarrow #eta#gamma (#pi^{0}#gamma, #omega#gamma)");
      trho = new TLatex(10.5,2.,"#rho #rightarrow #pi^{+}#pi^{-}#gamma (#pi^{0}#gamma, #eta#gamma)");
      tsigma = new TLatex(10.5,1.,"#Sigma^{0} #rightarrow #Lambda#gamma (#Lambda#gamma#gamma)");
   }

   // gammaL->SetTextColor(kBlack);
   // gammaL->SetTextSize(0.035);
   // gammaL->SetTextFont(42);
   // gammaL->Draw();
   cocktail->SetTextColor(kGreen+1);
   cocktail->SetTextSize(0.04);
   cocktail->SetTextFont(42);
   cocktail->Draw();
   tpi->SetTextColor(kRed);
   tpi->SetTextSize(0.04);
   tpi->SetTextFont(42);
   tpi->Draw();
   teta->SetTextColor(kBlue);
   teta->SetTextSize(0.04);
   teta->SetTextFont(42);
   teta->Draw();
   tomega->SetTextColor(kYellow+2);
   tomega->SetTextSize(0.04);
   tomega->SetTextFont(42);
   tomega->Draw();
   tetaprime->SetTextColor(kOrange+1);
   tetaprime->SetTextSize(0.04);
   tetaprime->SetTextFont(42);
   tetaprime->Draw();
   tphi->SetTextColor(kViolet);
   tphi->SetTextSize(0.04);
   tphi->SetTextFont(42);
   tphi->Draw();
   trho->SetTextColor(kAzure-2);
   trho->SetTextSize(0.04);
   trho->SetTextFont(42);
   trho->Draw();
   tsigma->SetTextColor(kRed-2);
   tsigma->SetTextSize(0.04);
   tsigma->SetTextFont(42);
   tsigma->Draw();

   DrawGammaSetMarker(histoIncRatioPurity, 4, 2.0, 1, 1);

   histoIncRatioPurity->SetMinimum(0.01);
   //histoIncRatioPurity->Draw("same");

   DrawAliceLogoAdv(0.12,0.7,"Work in Progress",option,"r",cocktailCanvasRatio,centrality);

   cocktailCanvasRatio->Print(Form("%s/%s_Cocktail_Ratios%s_%s_%s.%s",outputDir.Data(),textPi0New.Data(),centralityQM.Data(),cutSel.Data(),fGammaCutSelection.Data(),suffix.Data()));

   TH1D *cocktailAllGammaPi0original = (TH1D*)cocktailAllGammaPi0A->Clone("cocktailAllGammaPi0original");

   TFile *KaonFile = new TFile("KaonSpectraPbPb_12_Nov_2013.root");//Spectra_Kaon_13082012.root");
   GetKaonsPbPb(KaonFile,fEventCutSelection);

   TCanvas *KaonRatioCanvas = GetAndSetCanvas("cocktailCanvasEtaToKaon");

   CombinedKaonsRatioToFit = (TH1D*) RebinTH1D(cocktailEtaA,CombinedKaons);
   CombinedKaonsRatioToFit->Divide(CombinedKaons);
   NeutralKaonsRatioToFit = (TH1D*) RebinTH1D(cocktailEtaA,Kaon0s);
   NeutralKaonsRatioToFit->Divide(Kaon0s);


   SetHistogramm(CombinedKaonsRatioToFit,"#it{p}_{T} (GeV/#it{c})", "Ratios (see Legend)",0.0,1.5);
   SetHistogramm(NeutralKaonsRatioToFit,"#it{p}_{T} (GeV/#it{c})", "Ratios (see Legend)",0.0,1.5);

   DrawGammaSetMarker(CombinedKaonsRatioToFit, 24, 2.0,kOrange+2,kOrange+2);
   DrawGammaSetMarker(NeutralKaonsRatioToFit, 24, 2.0,kRed+2,kRed+2);
   CombinedKaonsRatioToFit->GetXaxis()->SetRangeUser(0.9,14);

   CombinedKaonsRatioToFit->DrawCopy("");
   NeutralKaonsRatioToFit->DrawCopy("same");
   One->Draw("same");

   TLegend* leg_EtaToKaonRatio = GetAndSetLegend(0.12,0.15,5);
   leg_EtaToKaonRatio->AddEntry(CombinedKaonsRatioToFit,"#eta_{from m_{T} scaling} / Charged Kaons");
   leg_EtaToKaonRatio->AddEntry(NeutralKaonsRatioToFit,"#eta_{from m_{T} scaling} / Neutral Kaons");
   //leg_EtaToKaonRatio->AddEntry(CombinedKaonsRatioToFit,Form("charged Kaons / Fit to charged Kaons; #chi^{2}/ndf = %0.2f", ConversionFitChargedKaons->GetChisquare()/ConversionFitChargedKaons->GetNDF()));
   //leg_EtaToKaonRatio->AddEntry(cocktailAllGammaPi0AoverB,"Ratio of cocktails: (#gamma_{sum}/#pi^{0})_{decay, with m_{T} scaling}/(#gamma_{sum}/#pi^{0})_{decay, with Kaons}");
   leg_EtaToKaonRatio->Draw();

   DrawSystem(0.16,0.9,option.Data(),centrality);
   KaonRatioCanvas->Print(Form("%s/%s_KaonToEtaRatio_%s_%s_%s.%s",outputDir.Data(),textPi0New.Data(),centralityQM.Data(),cutSel.Data(),fGammaCutSelection.Data(),suffix.Data()));

   TCanvas *cocktailCanvasEtaToPi0Ratio = GetAndSetCanvas("cocktailCanvasEtaToPi0Ratio",1000,1000);
   //cocktailCanvasEtaToPi0Ratio->SetLogy();

   TGraphAsymmErrors *Pi0pp7TeV = (TGraphAsymmErrors*) finalppFile->Get("graphInvCrossSectionPi0PCMStat7TeV");//graphInvCrossSectionPi0Comb7TeV");//graphInvCrossSectionPi0PCMStat7TeV");
   TGraphAsymmErrors *Etapp7TeV = (TGraphAsymmErrors*) finalppFile->Get("graphInvCrossSectionEtaComb7TeV");//graphInvCrossSectionEtaComb7TeV");//graphInvCrossSectionEtaPCMStat7TeV");
   TGraphAsymmErrors *EtaToPi0pp7TeV = (TGraphAsymmErrors*) finalppFile->Get("graphEtaToPi0Comb7TeV");

   //TH1D *ppPi0 = (TH1D*)cocktailDirpp->Get("ptPi0");
   TH1D *ppEta = (TH1D*)cocktailDirpp->Get("ptEta");

   Pi0pp7TeV = ScaleGraph(Pi0pp7TeV,1./xSection7TeV/recalcBarn);
   Etapp7TeV = ScaleGraph(Etapp7TeV,1./xSection7TeV/recalcBarn);

   TF1 *Pi0pp7TeVFit = FitObject("l","Pi0pp7TeVFit","Pi0",Pi0pp7TeV,.0,15.);
   TF1 *Etapp7TeVFit = FitObject("qcd","Etapp7TeVFit","Pi0",Etapp7TeV,.0,15.);

   Etapp7TeV->Fit(Etapp7TeVFit, "QNRME+", "", 0.1, 15.);
   Etapp7TeV->Fit(Etapp7TeVFit, "QNRME+", "", 0.1, 15.);
   Etapp7TeV->Fit(Etapp7TeVFit, "QNRME+", "", 0.1, 15.);
   Etapp7TeV->Fit(Etapp7TeVFit, "QNRME+", "", 0.1, 15.);
   Etapp7TeV->Fit(Etapp7TeVFit, "QNRME+", "", 0.1, 15.);
   Etapp7TeV->Fit(Etapp7TeVFit, "QNRME+", "", 0.1, 15.);



   // PrintParameter(Pi0pp7TeVFit,"l","Scaled Eta for PbPb",6);
   // PrintParameter(Etapp7TeVFit,"qcd","Scaled Eta for PbPb",6);


   // return;
   Pi0pp7TeVFit->SetRange(0.1,25);
   Etapp7TeVFit->SetRange(0.1,25);
   TH1D *Pi0ppFitHist = new TH1D("Pi0ppFitHist","Pi0ppFitHist",2500,0,25);
   TH1D *EtappFitHist = new TH1D("EtappFitHist","EtappFitHist",2500,0,25);
   Pi0ppFitHist->Sumw2();
   EtappFitHist->Sumw2();
   for(Int_t i = 1;i<Pi0ppFitHist->GetNbinsX()+1;i++){
      Pi0ppFitHist->SetBinContent(i,1);
      EtappFitHist->SetBinContent(i,1);
      Pi0ppFitHist->SetBinError(i,0.001);
      EtappFitHist->SetBinError(i,0.001);

   }
   Pi0ppFitHist->Multiply(Pi0pp7TeVFit);
   EtappFitHist->Multiply(Etapp7TeVFit);

   //EtappFitHist->Divide(Pi0ppFitHist);
   EtappFitHist->Divide(Pi0ppFitHist);
   EtappFitHist->Multiply(cocktailPi0A);
   

   //   Pi0ppFitHist->Draw();
   EtappFitHist->Rebin(10);
   EtappFitHist->Scale(1./10.);
   Etapp7TeVFit = FitObject("xqcd","Eta Fit","Pi0",EtappFitHist,.5,25.);
   Int_t ppIt = 3;
   TFitResultPtr FitresultppEta;
   TString resultppEta = "";
   TString fitParameterppEta = "SNRME+";
   for(Int_t i = 0; i<ppIt;i++){
      cout<<"Fit Iteration "<<i<<endl;
      FitresultppEta = EtappFitHist->Fit(Etapp7TeVFit, fitParameterppEta, "",.4,25.);
      resultppEta = gMinuit->fCstatu;
      if(!resultppEta.CompareTo("SUCCESSFUL")) break;
      else ppIt++;
      if(ppIt>100) break;
   }
   PrintParameter(Etapp7TeVFit,"xqcd","Scaled Eta for PbPb",7,gMinuit->fCstatu);

   TH1D *EtaToPi0RatioCocktail = (TH1D*)cocktailEtaA->Clone("EtaToPi0RatioCocktail");
   EtaToPi0RatioCocktail->Divide(cocktailPi0A);
   SetHistogramm(EtaToPi0RatioCocktail,"#it{p}_{T} (GeV/#it{c})", "#eta/#pi^{0}",0.0,1.0);
   EtaToPi0RatioCocktail->GetXaxis()->SetRangeUser(0.3,8);
   EtaToPi0RatioCocktail->Draw("chist");

   TH1D *EtaToPi0RatioCocktailB = (TH1D*)cocktailEtaB->Clone("EtaToPi0RatioCocktail");
   EtaToPi0RatioCocktailB->Divide(cocktailPi0B);
   SetHistogramm(EtaToPi0RatioCocktailB,"#it{p}_{T} (GeV/#it{c})", "#eta/#pi^{0}",0.0,2.4);
   EtaToPi0RatioCocktailB->GetXaxis()->SetRangeUser(0.2,12);
   EtaToPi0RatioCocktailB->SetLineColor(kAzure);
   EtaToPi0RatioCocktailB->Draw("chistsame");

   TH1D *EtaToPi0RatioCocktailC = (TH1D*)cocktailEtaC->Clone("EtaToPi0RatioCocktail");
   EtaToPi0RatioCocktailC->Divide(cocktailPi0C);
   SetHistogramm(EtaToPi0RatioCocktailC,"#it{p}_{T} (GeV/#it{c})", "#eta/#pi^{0}",0.0,2.4);
   EtaToPi0RatioCocktailC->GetXaxis()->SetRangeUser(0.2,12);
   //EtaToPi0RatioCocktailC->Draw("chistsame");

   TH1D *EtaToPi0RatioCocktailLow = (TH1D*)cocktailEtaA->Clone("EtaToPi0RatioCocktail");
   EtaToPi0RatioCocktailLow->Scale(0.8);
   EtaToPi0RatioCocktailLow->Divide(cocktailPi0A);
   EtaToPi0RatioCocktailLow->SetLineColor(kAzure);
   TH1D *EtaToPi0RatioCocktailHigh = (TH1D*)cocktailEtaA->Clone("EtaToPi0RatioCocktail");
   EtaToPi0RatioCocktailHigh->Scale(1.2);
   EtaToPi0RatioCocktailHigh->Divide(cocktailPi0A);
   EtaToPi0RatioCocktailHigh->SetLineColor(kAzure);
   // EtaToPi0RatioCocktailLow->Draw("chistsame");
   // EtaToPi0RatioCocktailHigh->Draw("chistsame");
   ppEta->Divide(cocktailPi0A);

   TF1 *mTValue = new TF1("","0.46",0,20);
   mTValue->SetLineWidth(0.3);
   mTValue->Draw("same");

   CombinedKaonsRatioToFit = (TH1D*)CombinedKaons->Clone();
   CombinedKaonsRatioToFit->Divide(ConversionFitPionsStatAverage);
   NeutralKaonsRatioToFit = (TH1D*)Kaon0s->Clone();
   NeutralKaonsRatioToFit->Divide(ConversionFitPionsStatAverage);

   CombinedKaonsCocktailRatioToFit = (TH1D*)CombinedKaons->Clone();
   CombinedKaonsCocktailRatioToFit->Divide(ConversionFitB);
   NeutralKaonsCocktailRatioToFit = (TH1D*)Kaon0s->Clone();
   NeutralKaonsCocktailRatioToFit->Divide(ConversionFitB);


   //TF1 *EtaPi0Fit = new TF1("EtaPi0Fit","[0]+x*[1]",4,25);
   TF1 *EtaPi0Fit = new TF1("EtaPi0Fit","[0]",6,10); // Constant Fit to K0s/pi+-
   EtaPi0Fit->SetLineColor(kRed-2);
   NeutralKaonsCocktailRatioToFit->Fit(EtaPi0Fit,"QNRME+","",6,10);
   //NeutralKaonsRatioToFit->Fit(EtaPi0Fit,"QNRME+","",4,25);
   //EtaToPi0RatioCocktail->Fit(EtaPi0Fit,"QNRME+","",7,10);
   EtaPi0Fit->Draw("same");

   TF1 *EtaPi0FitB = new TF1("EtaPi0Fit","[0]",6,10); // Constant Fit to K0s/pi+-
   EtaPi0FitB->SetLineColor(kRed-2);
   EtaToPi0RatioCocktailB->Fit(EtaPi0FitB,"NRME+","",6,10);
   //NeutralKaonsRatioToFit->Fit(EtaPi0Fit,"QNRME+","",4,25);
   //EtaToPi0RatioCocktail->Fit(EtaPi0Fit,"QNRME+","",7,10);
   EtaPi0FitB->Draw("same");

   return;

   
   Double_t ParamsK0s4080[6] = {0.621584,5.49931,-25.3105,2.24389,8.25061,0.289288};
   ConversionFitNeutralKaonsUnscaled = FitObject("xqcd","Neutral Kaons Unscaled","Pi0",Kaon0s,0.8,20.,ParamsK0s4080);
   DrawGammaSetMarkerTF1(ConversionFitNeutralKaonsUnscaled, 1, 1.8, kBlue);
   TFitResultPtr FitresultNeutralKaonsUnscaled;
   TString resultNeutralKaonsUnscaled = "";
   for(Int_t i = 0;i<1;i++){
      FitresultNeutralKaonsUnscaled = Kaon0s->Fit(ConversionFitNeutralKaonsUnscaled, "IQSNMRE+", "",0.8,20.);
      resultNeutralKaonsUnscaled = gMinuit->fCstatu;
      cout<<"-"<<gMinuit->fCstatu<<"-"<<endl;
      if(!resultNeutralKaonsUnscaled.CompareTo("SUCCESSFUL")) break;
      if(!resultNeutralKaonsUnscaled.CompareTo("PROBLEMS  ")) break;
      //i--;
      break;
   }
   PrintParameter(ConversionFitNeutralKaonsUnscaled,"xqcd",ConversionFitNeutralKaonsUnscaled->GetName(),7,gMinuit->fCstatu);



   Kaon0s->Scale(0.46/EtaPi0Fit->GetParameter(0));
   //Kaon0s->Scale(0.799);
   cout<<0.46/EtaPi0Fit->GetParameter(0)<<endl;

   NeutralKaonsRatioToFitAfterScaling = (TH1D*)Kaon0s->Clone();
   //NeutralKaonsRatioToFitAfterScaling->Divide(ConversionFitPionsStatAverage);
   NeutralKaonsRatioToFitAfterScaling->Divide(ConversionFitB);

   NeutralKaonsCocktailRatioToFitAfterScaling = (TH1D*) RebinTH1D(cocktailPi0A,Kaon0s);
   NeutralKaonsCocktailRatioToFitAfterScaling->Divide(Kaon0s,NeutralKaonsCocktailRatioToFitAfterScaling);

   //return;
   DrawGammaSetMarker(CombinedKaonsRatioToFit, 24, 2.0,kOrange+2,kOrange+2);
   DrawGammaSetMarker(NeutralKaonsRatioToFit, 24, 2.0,kRed+2,kRed+2);
   DrawGammaSetMarker(CombinedKaonsCocktailRatioToFit, 24, 2.0,kTeal+2,kTeal+2);
   DrawGammaSetMarker(NeutralKaonsCocktailRatioToFit, 24, 2.0,kSpring+2,kSpring+2);

   //CombinedKaonsRatioToFit->DrawCopy("same");
   //NeutralKaonsRatioToFit->DrawCopy("same");
   NeutralKaonsCocktailRatioToFit->Draw("psame");
   //CombinedKaonsCocktailRatioToFit->Draw("psame");
   DrawGammaSetMarker(NeutralKaonsRatioToFitAfterScaling, 21, 1.0,kRed+2,kRed+2);
   DrawGammaSetMarker(NeutralKaonsCocktailRatioToFitAfterScaling, 21, 1.0,kPink+2,kPink+2);
   NeutralKaonsRatioToFitAfterScaling->DrawCopy("same");
   //NeutralKaonsCocktailRatioToFitAfterScaling->DrawCopy("same");
   EtappFitHist->Divide(cocktailPi0A);
   //EtappFitHist->DrawCopy("same");
   DrawGammaSetMarkerTGraph(EtaToPi0pp7TeV, 20, 1., kBlack, kBlack);
   EtaToPi0pp7TeV->Draw("psame");

   TLegend* leg_EtaToPi0Ratio = GetAndSetLegend(0.12,0.70,5);
   leg_EtaToPi0Ratio->AddEntry(EtaToPi0RatioCocktailB,Form("#eta/#pi^{0} from m_{T} scaling"),"l");// %0.2f/0.46",EtaPi0FitB->GetParameter(0)),"l");
   leg_EtaToPi0Ratio->AddEntry(EtaToPi0RatioCocktail,Form("#eta/#pi^{0} from scaled K_{s}^{0}"),"l");// %0.2f/0.46",EtaPi0FitB->GetParameter(0)),"l");
   leg_EtaToPi0Ratio->AddEntry(NeutralKaonsCocktailRatioToFit,Form("K_{s}^{0}/#pi^{0} Ratio"),"p");// %0.2f/0.46",EtaPi0FitB->GetParameter(0)),"l");
   leg_EtaToPi0Ratio->AddEntry(EtaToPi0pp7TeV,"#eta to #pi^{0} pp 7TeV","ple");
   leg_EtaToPi0Ratio->AddEntry(mTValue,"PHENIX high p_{T} #eta/#pi^{0} = 0.46","l");
   
   
   // leg_EtaToPi0Ratio->AddEntry(EtaPi0Fit,Form("Linear Fit: %0.2f+%0.3f",EtaPi0Fit->GetParameter(0),EtaPi0Fit->GetParameter(1)),"l");
   // leg_EtaToPi0Ratio->AddEntry((TObject*)0,"Fit range: 4GeV/c<p_T<25GeV/c","");
   // leg_EtaToPi0Ratio->AddEntry(EtaToPi0RatioCocktailLow,"Uncertainty of 20%","l");
   // //leg_EtaToPi0Ratio->AddEntry(CombinedKaonsRatioToFit,"K^{#pm}/2 to #pi^{0} ratio","p");
   // leg_EtaToPi0Ratio->AddEntry(NeutralKaonsRatioToFit,"K_{s}^{0} to #pi^{#pm} ratio ","p");
   // leg_EtaToPi0Ratio->AddEntry(NeutralKaonsRatioToFitAfterScaling,Form("#eta to #pi^{#pm} after scaling with %0.2f/0.46",EtaPi0Fit->GetParameter(0)),"p");
   
   leg_EtaToPi0Ratio->Draw();


   ConversionFitChargedKaons = FitObject("xqcd","Fit Charged Kaons","Pi0",CombinedKaons,.8,20.);//,Params);//);
   DrawGammaSetMarkerTF1(ConversionFitChargedKaons, 1, 1.8, kRed);
   TFitResultPtr FitresultChargedKaons;
   TString resultChargedKaons = "";
   for(Int_t i = 0;i<1;i++){
      FitresultChargedKaons = CombinedKaons->Fit(ConversionFitChargedKaons, "IQSNMRE+", "",0.8,20.);
      resultChargedKaons = gMinuit->fCstatu;
      cout<<"-"<<gMinuit->fCstatu<<"-"<<endl;
      if(!resultChargedKaons.CompareTo("SUCCESSFUL")) break;
      if(!resultChargedKaons.CompareTo("PROBLEMS  ")) break;
      //i--;
      break;
   }
   PrintParameter(ConversionFitChargedKaons,"xqcd",ConversionFitChargedKaons->GetName(),7,gMinuit->fCstatu);

   //ConversionFitNeutralKaons = (TF1*)ConversionFitNeutralKaonsUnscaled->Clone("Fit Neutral Kaons");
   //ConversionFitNeutralKaons= (TF1*)ConversionFitChargedKaons->Clone("Neutral Kaons");
   ConversionFitNeutralKaons = FitObject("xqcd","Neutral Kaons","Pi0",Kaon0s,0.8,20.,ParamsK0s4080);
   DrawGammaSetMarkerTF1(ConversionFitNeutralKaons, 1, 1.8, kBlue);
   TFitResultPtr FitresultNeutralKaons;
   TString resultNeutralKaons = "";
   for(Int_t i = 0;i<155;i++){
      FitresultNeutralKaons = Kaon0s->Fit(ConversionFitNeutralKaons, "IQSNMRE+", "",0.8,20.);
      resultNeutralKaons = gMinuit->fCstatu;
      cout<<"-"<<gMinuit->fCstatu<<"-"<<endl;
      if(!resultNeutralKaons.CompareTo("SUCCESSFUL")) break;
      if(!resultNeutralKaons.CompareTo("PROBLEMS  ")) break;
      break;
      //i--;
   }
   PrintParameter(ConversionFitNeutralKaons,"xqcd",ConversionFitNeutralKaons->GetName(),7,gMinuit->fCstatu);


   cocktailCanvasEtaToPi0Ratio->Print(Form("%s/%s_Cocktail_EtaToPi0Ratio%s_%s_%s.%s",outputDir.Data(),textPi0New.Data(),centralityQM.Data(),cutSel.Data(),fGammaCutSelection.Data(),suffix.Data()));

   TCanvas *KaonCanvas = GetAndSetCanvas("cocktailCanvasEtaToKaon");
   KaonCanvas->SetLogy();
   ConversionFitChargedKaons->Draw();

   SetHistogramm(CombinedKaons,"#it{p}_{T} (GeV/#it{c})","#frac{1}{2#pi N_{ev.}} #frac{d^{2}N}{#it{p}_{T}d#it{p}_{T}dy} (GeV^{-2}c)");
   SetHistogramm(cocktailEtaA,"#it{p}_{T} (GeV/#it{c})","#frac{1}{2#pi N_{ev.}} #frac{d^{2}N}{#it{p}_{T}d#it{p}_{T}dy} (GeV^{-2}c)");
   SetHistogramm(Kaon0s,"#it{p}_{T} (GeV/#it{c})","#frac{1}{2#pi N_{ev.}} #frac{d^{2}N}{#it{p}_{T}d#it{p}_{T}dy} (GeV^{-2}c)");

   DrawGammaSetMarker(CombinedKaons, 20, 1.0,kGreen+2,kGreen+2);
   DrawGammaSetMarker(cocktailEtaA, 24, 1.0,kRed-2,kRed-2);
   DrawGammaSetMarker(Kaon0s, 24, 1.0,kBlue+2,kBlue+2);

   CombinedKaons->DrawCopy("");
   Kaon0s->DrawCopy("same");
   cocktailEtaA->DrawCopy("same");

   //ConversionFitChargedKaons->Draw("same");
   ConversionFitNeutralKaons->Draw("same");

   TLegend* leg_KaonCanvas = GetAndSetLegend(0.5,0.7,4);
   leg_KaonCanvas->AddEntry(CombinedKaons,"K^{#pm}/2, 12. Nov 2013)","p");
   leg_KaonCanvas->AddEntry(Kaon0s,"Scaled K^{0}_{s}, (12. Nov 2013)","p");
   leg_KaonCanvas->AddEntry(ConversionFitNeutralKaons,"Fit to scaled K^{0}_{s}","l");
   leg_KaonCanvas->AddEntry(cocktailEtaA,"cocktail #eta from m_{T} scaling");

   leg_KaonCanvas->Draw();

   DrawSystem(0.16,0.14,option.Data(),centrality);
   KaonCanvas->Print(Form("%s/%s_KaonSpectra_%s_%s_%s.%s",outputDir.Data(),textPi0New.Data(),centralityQM.Data(),cutSel.Data(),fGammaCutSelection.Data(),suffix.Data()));



   //**********************************************************************************
   //******************** NLO Direct Photon Ratio **************************************
   //**********************************************************************************

   TF1* QGPin7Tev = new TF1("QGPin7Tev","1+[0]*exp(-x/[1])+[2]*exp(-x/[3])",0,100);
   QGPin7Tev->SetParameters(4.24707e+01, 2.85766e+00, 1.63353e+02, 4.53670e-01);

   TH1D *cocktailAllGammaNLO = (TH1D*) cocktailAllGammaA->Clone("cocktailAllGammaNLO");
   graphNLOCalcMuHalfcopyA = (TGraphErrors*)graphNLOCalcMuHalf->Clone("arschloch");
   graphNLOCalcMuHalfcopyB = (TGraphErrors*)graphNLOCalcMuOne->Clone("arschloch");
   graphNLOCalcMuHalfcopyC = (TGraphErrors*)graphNLOCalcMuTwo->Clone("arschloch");

   xHalf = graphNLOCalcMuHalfcopyA->GetX();
   yHalf = graphNLOCalcMuHalfcopyA->GetY();
   eyHalf= graphNLOCalcMuHalfcopyA->GetEY();

   xOne = graphNLOCalcMuHalfcopyB->GetX();
   yOne = graphNLOCalcMuHalfcopyB->GetY();
   eyOne= graphNLOCalcMuHalfcopyB->GetEY();

   xTwo = graphNLOCalcMuHalfcopyC->GetX();
   yTwo = graphNLOCalcMuHalfcopyC->GetY();
   eyTwo= graphNLOCalcMuHalfcopyC->GetEY();

   TString cocktailFit = "qcd";

   TF1 *cocktailFitAllGammaForNLO = (TF1*)  FitObject("dmtsal","cocktailFit","Pi0",cocktailAllGammaNLO,2.0,11,Params,"QNRME+");

   TCanvas *canvasCocktailFitForNLO = GetAndSetCanvas("canvasCocktailFitForNLO");
   canvasCocktailFitForNLO->SetLogy();
   cocktailAllGammaNLO->DrawCopy();
   cocktailFitAllGammaForNLO->Draw("same");

   canvasCocktailFitForNLO->Print(Form("%s/%scocktailAllGammaNLO_cocktailFitForNLO_%s_%s_%s.%s",outputDir.Data(),textPi0New.Data(),centralityQM.Data(),cutSel.Data(),fGammaCutSelection.Data(),suffix.Data()));


   for(Int_t bin = 0; bin < graphNLOCalcMuHalf->GetN(); bin++){// Scale with N_collisions
      yHalf[bin] = (1 +( yHalf[bin] / (cocktailFitAllGammaForNLO->Eval(xHalf[bin]))));
      yOne[bin] = (1 +( yOne[bin] / (cocktailFitAllGammaForNLO->Eval(xOne[bin]))));
      yTwo[bin] = (1 +( yTwo[bin] / (cocktailFitAllGammaForNLO->Eval(xTwo[bin]))));
   }

   half = new TGraphErrors(graphNLOCalcMuHalf->GetN(),xHalf,yHalf,0);
   one = new TGraphErrors(graphNLOCalcMuOne->GetN(),xOne,yOne,0);
   two = new TGraphErrors(graphNLOCalcMuTwo->GetN(),xTwo,yTwo,0);





   //**********************************************************************************
   //******************** Double Ratios ***********************************************
   //**********************************************************************************

   cocktailAllGammaPi0A = RebinTH1D(cocktailAllGammaPi0A,histoIncRatioPurity);
   cocktailAllGammaPi0B = RebinTH1D(cocktailAllGammaPi0A,histoIncRatioPurity);
   cocktailAllGammaPi0C = RebinTH1D(cocktailAllGammaPi0C,histoIncRatioPurity);
   cocktailAllGammaPi0Pions = RebinTH1D(cocktailAllGammaPi0Pions,histoIncRatioPurity);
   cocktailAllGammaPi0Wide = RebinTH1D(cocktailAllGammaPi0Wide,histoIncRatioPurity);
   cocktailAllGammaPi0Narrow = RebinTH1D(cocktailAllGammaPi0Narrow,histoIncRatioPurity);
   cocktailAllGammaPi0Syst = RebinTH1D(cocktailAllGammaPi0Syst,histoIncRatioPurity);

   cocktailAllGammaPi0A->Divide(RebinTH1D(cocktailAllGammaA,histoIncRatioPurity),RebinTH1D(cocktailPi0A,histoIncRatioPurity));
   cocktailAllGammaPi0B->Divide(RebinTH1D(cocktailAllGammaB,histoIncRatioPurity),RebinTH1D(cocktailPi0B,histoIncRatioPurity));
   cocktailAllGammaPi0C->Divide(RebinTH1D(cocktailAllGammaC,histoIncRatioPurity),RebinTH1D(cocktailPi0C,histoIncRatioPurity));

   cocktailAllGammaPi0AB = (TH1D*)cocktailAllGammaPi0A->Clone();
   cocktailAllGammaPi0AB->Add(cocktailAllGammaPi0B);
   cocktailAllGammaPi0AB->Scale(0.5);

   cocktailAllGammaPi0Low = (TH1D*)cocktailAllGammaPi0A->Clone("cocktailAllGammaPi0Low");
   cocktailEtaGammaLow = (TH1D*)cocktailDirA->Get("ptgEta");
   cocktailEtaLow = (TH1D*)cocktailDirA->Get("ptEta");
   cocktailAllGammaPi0High = (TH1D*)cocktailAllGammaPi0B->Clone("cocktailAllGammaPi0High");
   cocktailEtaGammaHigh = (TH1D*)cocktailDirB->Get("ptgEta");
   cocktailEtaHigh = (TH1D*)cocktailDirB->Get("ptEta");
   
   cocktailAllGammaPi0EtaLow = (TH1D*)cocktailAllGammaPi0AB->Clone("cocktailAllGammaPi0EtaNorm");
   cocktailAllGammaPi0EtaHigh = (TH1D*)cocktailAllGammaPi0AB->Clone("cocktailAllGammaPi0EtaNorm");

   cocktailEtaGammaAB = (TH1D*)cocktailEtaGammaA->Clone();
   cocktailEtaGammaAB->Add(cocktailEtaGammaB);
   cocktailEtaGammaAB->Scale(0.5);
   cocktailAllGammaAB = (TH1D*)cocktailAllGammaA->Clone();
   cocktailAllGammaAB->Add(cocktailAllGammaB);
   cocktailAllGammaAB->Scale(0.5);
   cocktailAllGammaAB->Add(cocktailEtaGammaAB,-1);
   cocktailAllGammaAB->Add(cocktailEtaGammaAB,1.2);
   cocktailAllGammaPi0EtaHigh->Divide(RebinTH1D(cocktailAllGammaAB,histoIncRatioPurity),RebinTH1D(cocktailPi0A,histoIncRatioPurity));
   cocktailAllGammaAB->Add(cocktailEtaGammaAB,-1.2);
   cocktailAllGammaAB->Add(cocktailEtaGammaAB,0.8);
   cocktailAllGammaPi0EtaLow->Divide(RebinTH1D(cocktailAllGammaAB,histoIncRatioPurity),RebinTH1D(cocktailPi0A,histoIncRatioPurity));
   cocktailAllGammaAB->Add(cocktailEtaGammaAB,-0.8);
   cocktailAllGammaAB->Add(cocktailEtaGammaAB,1);

   TH1D *cocktailChargeToNeutral = (TH1D*)cocktailAllGammaPi0Pions->Clone("cocktailChargeToNeutral");
   cocktailChargeToNeutral->Divide(cocktailAllGammaPi0B);

   TCanvas *canvas_CocktailEtaUncert = GetAndSetCanvas("CocktailEtaUncert");
   
   TH1D *CocktailEtaUncert = (TH1D*)cocktailAllGammaPi0A->Clone("CocktailEtaUncert");
   CocktailEtaUncert->Divide(cocktailAllGammaPi0High);
   SetHistogramm(CocktailEtaUncert, "#it{p}_{T} (GeV/#it{c})", "Cocktail Ratio",0.97,1.06);
   DrawGammaSetMarker(CocktailEtaUncert, 20, 2.0, kRed-2, kRed-2);
   CocktailEtaUncert->Draw("e1");
   One->Draw("same");

   TLegend* leg_CocktailEtaUncert = GetAndSetLegend(0.13,0.8,1);
   leg_CocktailEtaUncert->AddEntry(CocktailEtaUncert,"Ratio of Cocktails, m_{T} vs. scaled K_{0}^{s}, for #eta");
   leg_CocktailEtaUncert->Draw();
   

   DrawSystem(0.14,0.15,option.Data(),centrality);
   canvas_CocktailEtaUncert->Print(Form("%s/%s_Cocktail_EtaUncert_%s_%s_%s_%s.%s",outputDir.Data(),textPi0New.Data(),centralityQM.Data(),textPrefix2.Data(),cutSel.Data(),fGammaCutSelection.Data(),suffix.Data()));


   TF1 *Pi0ParamCocktailUncert;
   if(!option.CompareTo("PbPb_2.76TeV")){
      if(centCutNumberI==0 && centCutNumberBI == 2)
         Pi0ParamCocktailUncert =  new TF1("0020","(2.49162e-02+1.26946e-02*tanh(x-4.44981e+00))+1.0",0.,20.) ;
      else if(centCutNumberI==0 && centCutNumberBI == 1)
         Pi0ParamCocktailUncert =  new TF1("0020","(2.49162e-02+1.26946e-02*tanh(x-4.44981e+00))+1.0",0.,20.) ;
      else if(centCutNumberI==2 && centCutNumberBI == 4)
         Pi0ParamCocktailUncert =  new TF1("2040","1.16749e-02+6.64667e-03*tanh(x+7.36921e+00)+1.0",0.,20.) ;
      else if(centCutNumberI==1 && centCutNumberBI == 2)
         Pi0ParamCocktailUncert =  new TF1("2040","1.16749e-02+6.64667e-03*tanh(x+7.36921e+00)+1.0",0.,20.) ;
      else if(centCutNumberI==4 && centCutNumberBI == 8)
         Pi0ParamCocktailUncert =  new TF1("4080","3.33604e-01+(-3.16839e-01)*tanh(x+8.21696e+02)+1.0",0.,20.) ;
      else
         Pi0ParamCocktailUncert =  new TF1("default","1",0.,20.) ;
   }
   else Pi0ParamCocktailUncert =  new TF1("default","1",0.,20.) ;

   cocktailAllGammaPi0ParamLow = (TH1D*)cocktailAllGammaPi0AB->Clone("cocktailAllGammaPi0ParamLow");
   cocktailAllGammaPi0ParamLow->Multiply(Pi0ParamCocktailUncert);
   cocktailAllGammaPi0ParamHigh = (TH1D*)cocktailAllGammaPi0AB->Clone("cocktailAllGammaPi0ParamHigh");
   cocktailAllGammaPi0ParamHigh->Divide(Pi0ParamCocktailUncert);
         

   cocktailAllGammaPi0A = cocktailAllGammaPi0AB;

   // cocktailAllGammaA->Add(cocktailEtaGamma,-1);
   // cocktailEtaGamma->Scale(0.8);
   // cocktailAllGammaA->Add(cocktailEtaGamma,1);
   // cocktailAllGammaA->Draw();
   //
   // cocktailAllGammaPi0Low->Divide(RebinTH1D(cocktailAllGammaA,histoIncRatioPurity),RebinTH1D(cocktailPi0A,histoIncRatioPurity));
   // cocktailAllGammaA->Add(cocktailEtaGamma,-1);
   // cocktailEtaGamma->Scale(1./0.8);
   // cocktailEtaGamma->Scale(1.2);
   // cocktailAllGammaA->Add(cocktailEtaGamma,1);
   //
   // cocktailAllGammaPi0High->Divide(RebinTH1D(cocktailAllGammaA,histoIncRatioPurity),RebinTH1D(cocktailPi0A,histoIncRatioPurity));
   // cocktailAllGammaA->Add(cocktailEtaGamma,-1);
   // cocktailEtaGamma->Scale(1./1.2);
   // cocktailAllGammaA->Add(cocktailEtaGamma,1);



   /////////////////////////////
   TCanvas* canvasIncRatioPurityTrueEffAll = GetAndSetCanvas(" canvasIncRatioPurityTrueEffAll");
   SetHistogramm(histoIncRatioPurityTrueEff, "#it{p}_{T} (GeV/#it{c})", "Ratio Inclusive #gamma/#pi^{0}",0,2);
   DrawGammaSetMarker(histoIncRatioPurityTrueEff, 20, 2.0, 4, 4);
   DrawGammaSetMarker(histoIncRatioPurityTrueEffWide, 20, 2.0, 6, 6);
   DrawGammaSetMarker(histoIncRatioPurityTrueEffNarrow, 20, 2.0, 3, 3);
   histoIncRatioPurityTrueEff->Draw();
   histoIncRatioPurityTrueEffWide->Draw("same");
   histoIncRatioPurityTrueEffNarrow->Draw("same");
   cocktailAllGammaPi0A->Draw("chistsame");
   DrawAliceLogoAdv(0.2,0.65,"Work in Progress",option,"r", canvasIncRatioPurityTrueEffAll,centrality);
   canvasIncRatioPurityTrueEffAll->Print(Form("%s/%s_IncRatioPurity_trueEff_all%s_%s_%s_%s.%s",outputDir.Data(),textPi0New.Data(),centralityQM.Data(),textPrefix2.Data(),cutSel.Data(),fGammaCutSelection.Data(),suffix.Data()));
   ///////////////////////////////


   TCanvas* canvasMCDoubleRatioSum = GetAndSetCanvas("canvasMCDoubleRatioSum");
   canvasMCDoubleRatioSum->SetLogy(0);
   histoMCDoubleRatioSum = (TH1D*)histoMCIncRatio->Clone("MC_DoubleRatio_Sum");
   histoMCesdDoubleRatioSum = (TH1D*)histoMCesdIncRatio->Clone("MCesd_DoubleRatio_Sum");

   histoDecayRatioSumGamma = RebinTH1D(histoDecayRatioSumGamma,histoMCIncRatio);

   histoMCDoubleRatioSum->Divide(histoMCDoubleRatioSum,histoDecayRatioSumGamma,1,1,"");
   histoMCesdDoubleRatioSum->Divide(histoMCesdDoubleRatioSum,histoDecayRatioSumGamma,1,1,"");

   DrawGammaSetMarker(histoMCDoubleRatioSum, 22, 2.0, 1, 1);
   DrawGammaSetMarker(histoMCesdDoubleRatioSum, 23, 2.0, 2, 2);
   SetHistogramm(histoMCDoubleRatioSum,"#it{p}_{T} (GeV/#it{c})","(#gamma_{inc}/#pi^{0})/(#gamma_{decay}/#pi^{0})",0.5,2.0);
   SetHistogramm(histoMCesdDoubleRatioSum,"#it{p}_{T} (GeV/#it{c})","(#gamma_{inc}/#pi^{0})/(#gamma_{decay}/#pi^{0})",0.5,2.0);
   histoMCesdDoubleRatioSum->Draw("");
   histoMCDoubleRatioSum->Draw("same");

   canvasMCDoubleRatioSum->Print(Form("%s/%s_DoubleRatioMC_Sum%s_%s_%s.%s",outputDir.Data(),textPi0New.Data(),centralityQM.Data(),cutSel.Data(),fGammaCutSelection.Data(),suffix.Data()));

   // //cocktailAllGammaPi0A = GammaDmitri;

   // cocktailAllGammaPi0A->Divide(GammaDmitri);
   // cocktailAllGammaPi0A->Draw();
   //    return;
   histoDoubleRatioConversionNormalPurity = (TH1D*) histoIncRatioPurity->Clone("DoubleRatioConversionNormalPurity");
   histoDoubleRatioConversionNormalPurity->Divide(cocktailAllGammaPi0A);

   histoDoubleRatioConversionTrueEffPurityA = (TH1D*) histoIncRatioPurityTrueEff->Clone("DoubleRatioConversionTrueEffPurity");
   histoDoubleRatioConversionTrueEffPurityA->Divide(cocktailAllGammaPi0A);
   histoDoubleRatioConversionTrueEffPurityB = (TH1D*) histoIncRatioPurityTrueEff->Clone("DoubleRatioConversionTrueEffPurity");
   histoDoubleRatioConversionTrueEffPurityB->Divide(cocktailAllGammaPi0B);
   histoDoubleRatioConversionTrueEffPurityC = (TH1D*) histoIncRatioPurityTrueEff->Clone("DoubleRatioConversionTrueEffPurity");
   histoDoubleRatioConversionTrueEffPurityC->Divide(cocktailAllGammaPi0C);
   histoDoubleRatioConversionTrueEffPurityAB = (TH1D*) histoIncRatioPurityTrueEff->Clone("DoubleRatioConversionTrueEffPurity");
   histoDoubleRatioConversionTrueEffPurityAB->Divide(cocktailAllGammaPi0AB);

   histoDoubleRatioConversionTrueEffPurityLow = (TH1D*) histoIncRatioPurityTrueEff->Clone("DoubleRatioConversionTrueEffPurityLow");
   histoDoubleRatioConversionTrueEffPurityLow->Divide(cocktailAllGammaPi0Low);
   histoDoubleRatioConversionTrueEffPurityHigh = (TH1D*) histoIncRatioPurityTrueEff->Clone("DoubleRatioConversionTrueEffPurityHigh");
   histoDoubleRatioConversionTrueEffPurityHigh->Divide(cocktailAllGammaPi0High);

   histoDoubleRatioConversionTrueEffPurityEtaLow = (TH1D*) histoIncRatioPurityTrueEff->Clone("DoubleRatioConversionTrueEffPurityEtaLow");
   histoDoubleRatioConversionTrueEffPurityEtaLow->Divide(cocktailAllGammaPi0EtaLow);
   histoDoubleRatioConversionTrueEffPurityEtaHigh = (TH1D*) histoIncRatioPurityTrueEff->Clone("DoubleRatioConversionTrueEffPurityEtaHigh");
   histoDoubleRatioConversionTrueEffPurityEtaHigh->Divide(cocktailAllGammaPi0EtaHigh);

   histoDoubleRatioConversionTrueEffPurityPi0ParamLow = (TH1D*) histoIncRatioPurityTrueEff->Clone("DoubleRatioConversionTrueEffPurityPi0ParamLow");
   histoDoubleRatioConversionTrueEffPurityPi0ParamLow->Divide(cocktailAllGammaPi0ParamLow);
   histoDoubleRatioConversionTrueEffPurityPi0ParamHigh = (TH1D*) histoIncRatioPurityTrueEff->Clone("DoubleRatioConversionTrueEffPurityPi0ParamHigh");
   histoDoubleRatioConversionTrueEffPurityPi0ParamHigh->Divide(cocktailAllGammaPi0ParamHigh);

   histoDoubleRatioConversionTrueEffPurityPions = (TH1D*) histoIncRatioPurityTrueEff->Clone("DoubleRatioConversionTrueEffPurityPions");
   histoDoubleRatioConversionTrueEffPurityPions->Divide(cocktailAllGammaPi0Pions);

   histoDoubleRatioConversionTrueEffPurityWide = (TH1D*) histoIncRatioPurityTrueEffWide->Clone("DoubleRatioConversionTrueEffPurityWide");
   histoDoubleRatioConversionTrueEffPurityWide->Divide(cocktailAllGammaPi0Wide);

   histoDoubleRatioConversionTrueEffPurityNarrow = (TH1D*) histoIncRatioPurityTrueEffNarrow->Clone("DoubleRatioConversionTrueEffPurityNarrow");
   histoDoubleRatioConversionTrueEffPurityNarrow->Divide(cocktailAllGammaPi0Narrow);

   histoDoubleRatioConversionTrueEffPuritySyst = (TH1D*) histoIncRatioPurityTrueEff->Clone("DoubleRatioConversionTrueEffPuritySyst");
   histoDoubleRatioConversionTrueEffPuritySyst->Divide(cocktailAllGammaPi0Syst);


   if(option.CompareTo("7TeV") == 0){
      histoDoubleRatioCombinedPurity = (TH1D*) histoIncRatioCombinedPurity->Clone("DoubleRatioCombinedPurity");
      histoDoubleRatioCombinedPurity->Divide(cocktailAllGammaPi0A);
   }

   TCanvas *canvasConversionFitDoubleRatioSum = GetAndSetCanvas("canvasConversionFitDoubleRatioSum");
   histoDoubleRatioConversionFitPurityA = (TH1D*) histoIncRatioFitPurityA->Clone("DoubleRatioConversionFitPurityA");
   histoDoubleRatioConversionFitPurityA->Divide(cocktailAllGammaPi0A);
   histoDoubleRatioConversionFitPurityB = (TH1D*) histoIncRatioFitPurityB->Clone("DoubleRatioConversionFitPurityB");
   histoDoubleRatioConversionFitPurityB->Divide(cocktailAllGammaPi0B);
   histoDoubleRatioConversionFitPurityC = (TH1D*) histoIncRatioFitPurityC->Clone("DoubleRatioConversionFitPurityC");
   histoDoubleRatioConversionFitPurityC->Divide(cocktailAllGammaPi0C);
   histoDoubleRatioConversionFitPurityAB = (TH1D*) histoIncRatioFitPurityA->Clone("DoubleRatioConversionFitPurityAB");
   histoDoubleRatioConversionFitPurityAB->Divide(cocktailAllGammaPi0AB);
   histoDoubleRatioConversionFitPurityLow = (TH1D*) histoIncRatioFitPurityA->Clone("DoubleRatioConversionFitPurityLow");
   histoDoubleRatioConversionFitPurityLow->Divide(cocktailAllGammaPi0Low);
   histoDoubleRatioConversionFitPurityHigh = (TH1D*) histoIncRatioFitPurityA->Clone("DoubleRatioConversionFitPurityHigh");
   histoDoubleRatioConversionFitPurityHigh->Divide(cocktailAllGammaPi0High);
   histoDoubleRatioConversionFitPurityEtaLow = (TH1D*) histoIncRatioFitPurityA->Clone("DoubleRatioConversionFitPurityEtaLow");
   histoDoubleRatioConversionFitPurityEtaLow->Divide(cocktailAllGammaPi0EtaLow);
   histoDoubleRatioConversionFitPurityEtaHigh = (TH1D*) histoIncRatioFitPurityA->Clone("DoubleRatioConversionFitPurityEtaHigh");
   histoDoubleRatioConversionFitPurityEtaHigh->Divide(cocktailAllGammaPi0EtaHigh);

   histoDoubleRatioConversionFitPurityPi0ParamLow = (TH1D*) histoIncRatioFitPurityA->Clone("DoubleRatioConversionFitPurityPi0ParamLow");
   histoDoubleRatioConversionFitPurityPi0ParamLow->Divide(cocktailAllGammaPi0ParamLow);
   histoDoubleRatioConversionFitPurityPi0ParamHigh = (TH1D*) histoIncRatioFitPurityA->Clone("DoubleRatioConversionFitPurityPi0ParamHigh");
   histoDoubleRatioConversionFitPurityPi0ParamHigh->Divide(cocktailAllGammaPi0ParamHigh);

  
   histoDoubleRatioConversionOnlyGamma = (TH1D*) histoGammaSpecCorrPurity->Clone("DoubleRatioConversionOnlyGamma");
   histoDoubleRatioConversionOnlyGamma->Divide(RebinTH1D(cocktailAllGammaA,histoIncRatioPurity));
   for(Int_t i = 0;i<histoDoubleRatioConversionFitPurityA->GetNbinsX();i++){
      histoDoubleRatioConversionOnlyGamma->SetBinError(i+1,histoDoubleRatioConversionFitPurityA->GetBinError(i+1));
   }

   histoDoubleRatioConversionFitPurityPionsAverage = (TH1D*) histoIncRatioFitPurityPionsStatAverage->Clone("DoubleRatioConversionFitPurityPionsAverage");
   histoDoubleRatioConversionFitPurityPionsAverage->Divide(cocktailAllGammaPi0Pions);
   histoDoubleRatioConversionFitPurityWide = (TH1D*) histoIncRatioFitPurityWide->Clone("DoubleRatioConversionFitPurityWide");
   histoDoubleRatioConversionFitPurityWide->Divide(cocktailAllGammaPi0A);
   histoDoubleRatioConversionFitPurityNarrow = (TH1D*) histoIncRatioFitPurityNarrow->Clone("DoubleRatioConversionFitPurityNarrow");
   histoDoubleRatioConversionFitPurityNarrow->Divide(cocktailAllGammaPi0A);
   histoDoubleRatioConversionFitPuritySyst = (TH1D*) histoIncRatioFitPurityA->Clone("DoubleRatioConversionFitPuritySyst");
   histoDoubleRatioConversionFitPuritySyst->Divide(cocktailAllGammaPi0Syst);
   histoDoubleRatioConversionFitFit = (TH1D*) histoIncRatioFitFit->Clone("DoubleRatioConversionFitFit");
   histoDoubleRatioConversionFitFit->Divide(cocktailAllGammaPi0A);
   histoDoubleRatioConversionLowFitPurity = (TH1D*) histoIncRatioLowFitPurity->Clone("DoubleRatioConversionLowFitPurity");
   histoDoubleRatioConversionLowFitPurity->Divide(cocktailAllGammaPi0A);
   histoDoubleRatioConversionHighFitPurity = (TH1D*) histoIncRatioHighFitPurity->Clone("DoubleRatioConversionHighFitPurity");
   histoDoubleRatioConversionHighFitPurity->Divide(cocktailAllGammaPi0A);





   // histoIncRatioFitPurityWide->Divide(histoIncRatioFitPurityNarrow);
   // histoDoubleRatioConversionFitPurityWide->Divide(histoDoubleRatioConversionFitPurityNarrow);

   // histoIncRatioFitPurityWide->SetMarkerStyle(20);

   // histoIncRatioFitPurityWide->Draw();
   // histoDoubleRatioConversionFitPurityWide->Draw("same");




   // return;
   SetHistogramm(histoDoubleRatioConversionFitPurityA,"#it{p}_{T} (GeV/#it{c})","(#gamma_{inc}/#pi^{0})/(#gamma_{decay}/#pi^{0})",0.7,2.0);
   SetHistogramm(histoDoubleRatioConversionFitPurityB,"#it{p}_{T} (GeV/#it{c})","(#gamma_{inc}/#pi^{0})/(#gamma_{decay}/#pi^{0})",0.7,2.0);
   SetHistogramm(histoDoubleRatioConversionFitPurityC,"#it{p}_{T} (GeV/#it{c})","(#gamma_{inc}/#pi^{0})/(#gamma_{decay}/#pi^{0})",0.7,2.0);
   SetHistogramm(histoDoubleRatioConversionFitPurityAB,"#it{p}_{T} (GeV/#it{c})","(#gamma_{inc}/#pi^{0})/(#gamma_{decay}/#pi^{0})",0.7,2.0);
   SetHistogramm(histoDoubleRatioConversionFitPurityWide,"#it{p}_{T} (GeV/#it{c})","(#gamma_{inc}/#pi^{0})/(#gamma_{decay}/#pi^{0})",0.8,3.0);
   SetHistogramm(histoDoubleRatioConversionFitPurityNarrow,"#it{p}_{T} (GeV/#it{c})","(#gamma_{inc}/#pi^{0})/(#gamma_{decay}/#pi^{0})",0.8,3.0);
   SetHistogramm(histoDoubleRatioConversionFitPuritySyst,"#it{p}_{T} (GeV/#it{c})","(#gamma_{inc}/#pi^{0})/(#gamma_{decay}/#pi^{0})",0.8,3.0);
   SetHistogramm(histoDoubleRatioConversionFitFit,"#it{p}_{T} (GeV/#it{c})","(#gamma_{inc}/#pi^{0})/(#gamma_{decay}/#pi^{0})",0.8,3.0);
   SetHistogramm(histoDoubleRatioConversionLowFitPurity,"#it{p}_{T} (GeV/#it{c})","(#gamma_{inc}/#pi^{0})/(#gamma_{decay}/#pi^{0})",0.8,3.0);
   SetHistogramm(histoDoubleRatioConversionHighFitPurity,"#it{p}_{T} (GeV/#it{c})","(#gamma_{inc}/#pi^{0})/(#gamma_{decay}/#pi^{0})",0.8,3.0);
   SetHistogramm(histoDoubleRatioConversionTrueEffPurityPions,"#it{p}_{T} (GeV/#it{c})","(#gamma_{inc}/#pi^{0})/(#gamma_{decay}/#pi^{0})",0.8,3.0);
   DrawGammaSetMarker(histoDoubleRatioConversionTrueEffPurityPions, 20, 2.0, 4, 4);


   Double_t BinsPi0HIDirectPhotonPt[19] = {0.0,0.9,1.1,1.3,1.5,1.7,1.9,2.1,2.3,2.5,2.7,3.0,3.3,3.7,4.1,4.6,5.4,6.2,7.0};
   TH1D *BinningDoubleRatio = new TH1D("","",18,BinsPi0HIDirectPhotonPt);

   // histoDoubleRatioConversionFitPurityA = RebinTH1D(histoDoubleRatioConversionFitPurityA,BinningDoubleRatio);
   // histoDoubleRatioConversionFitPurityB = RebinTH1D(histoDoubleRatioConversionFitPurityB,BinningDoubleRatio);
   // histoDoubleRatioConversionFitPurityC = RebinTH1D(histoDoubleRatioConversionFitPurityC,BinningDoubleRatio);



   // ------------------------------ NLO Calculations -----------------------------

   TGraphErrors *DirectPhotonDoubleNLOhalf =(TGraphErrors*) half->Clone("doubleRatioNLOhalf");
   TGraphErrors *DirectPhotonDoubleNLOone =(TGraphErrors*) one->Clone("doubleRatioNLOone");
   TGraphErrors *DirectPhotonDoubleNLOtwo  =(TGraphErrors*) two->Clone("doubleRatioNLOtwo");

   // DirectPhotonDoubleNLOhalf->RemovePoint(0);
   // DirectPhotonDoubleNLOone->RemovePoint(0);
   // DirectPhotonDoubleNLOtwo->RemovePoint(0);

   TGraphErrors *DirectPhotonNLOhalf =(TGraphErrors*) graphNLOCalcMuHalf->Clone("graphNLOCalcMuHalf");
   TGraphErrors *DirectPhotonNLOone =(TGraphErrors*) graphNLOCalcMuOne->Clone("graphNLOCalcMuOne");
   TGraphErrors *DirectPhotonNLOtwo  =(TGraphErrors*) graphNLOCalcMuTwo->Clone("graphNLOCalcMuTwo");

   // DirectPhotonNLOhalf->RemovePoint(0);
   // DirectPhotonNLOone->RemovePoint(0);
   // DirectPhotonNLOtwo->RemovePoint(0);

   Double_t *errorup = new Double_t[DirectPhotonDoubleNLOhalf->GetN()];
   Double_t *errorlow = new Double_t[DirectPhotonDoubleNLOtwo->GetN()];

   Double_t *errorSpecup = new Double_t[DirectPhotonDoubleNLOhalf->GetN()];
   Double_t *errorSpeclow = new Double_t[DirectPhotonDoubleNLOtwo->GetN()];

   yHalf = DirectPhotonDoubleNLOhalf->GetY();
   yOne = DirectPhotonDoubleNLOone->GetY();
   yTwo = DirectPhotonDoubleNLOtwo->GetY();

   Double_t *ySpecHalf = DirectPhotonNLOhalf->GetY();
   Double_t *ySpecOne = DirectPhotonNLOone->GetY();
   Double_t *ySpecTwo = DirectPhotonNLOtwo->GetY();

   for(Int_t i = 0;i<DirectPhotonDoubleNLOhalf->GetN(); i++){
      errorup[i] = yHalf[i]-yOne[i];
      errorlow[i] = -yTwo[i]+yOne[i];
      errorSpecup[i] = ySpecHalf[i]-ySpecOne[i];
      errorSpeclow[i] = -ySpecTwo[i]+ySpecOne[i];
   }

   TGraphAsymmErrors *NLODoubleRatio = new TGraphAsymmErrors( DirectPhotonDoubleNLOhalf->GetN(), DirectPhotonDoubleNLOone->GetX(), DirectPhotonDoubleNLOone->GetY(), DirectPhotonDoubleNLOone->GetEX(), DirectPhotonDoubleNLOone->GetEX(), errorlow,errorup );
   TGraphAsymmErrors *NLO = new TGraphAsymmErrors( DirectPhotonDoubleNLOhalf->GetN(), DirectPhotonNLOone->GetX(), DirectPhotonNLOone->GetY(), DirectPhotonNLOone->GetEX(), DirectPhotonNLOone->GetEX(),errorSpeclow ,errorSpecup );
   NLODoubleRatio->SetLineColor(kAzure);
   NLODoubleRatio->SetFillColor(kAzure);
   NLODoubleRatio->SetLineWidth(3.0);
   NLODoubleRatio->SetMarkerSize(0);
   NLO->SetLineColor(kAzure);
   NLO->SetFillColor(kAzure);
   NLO->SetLineWidth(3.0);
   NLO->SetMarkerSize(0);

   NLO->RemovePoint(0);


   TF1 *NLOdoubleRatioFit= new TF1("NLOdoubleRatioFit","(x<=2)*(1.0+[0]*x)+(x>2)*([1]+[2]*x+[3]*x*x)",0.,4.0);
   //TF1 *NLOdoubleRatioFit= new TF1("NLOdoubleRatioFit","1.02+[0]*x+[1]*x+[2]*x*x",0.,14.);
   //NLOdoubleRatioFit->SetParLimits(2, 0.5, 1);
   NLODoubleRatio->Fit(NLOdoubleRatioFit,"QNRME+","",0,4.0);
   NLOdoubleRatioFit->SetLineColor(2);

   //+abs([2])*pow(x,2)+abs([3])*pow(x,4)
   // ------------------------------ NLO Calculations -----------------------------

   DrawGammaSetMarker(histoDoubleRatioConversionFitFit, 20, 1.2, 1, 1);
   DrawGammaSetMarker(histoDoubleRatioConversionFitPurityA, 20, 1.2, 1, 1);

   if(option.CompareTo("PbPb_2.76TeV") == 0){
      histoDoubleRatioConversionFitPurityA->GetXaxis()->SetRangeUser(0,15);
      histoDoubleRatioConversionFitPurityA->GetYaxis()->SetRangeUser(0.8,3.0);
      histoMCDoubleRatioSum->GetYaxis()->SetRangeUser(0.8,3.0);
      DrawGammaSetMarker(histoMCDoubleRatioSum, 20, 1.2, 0, 0);
   }
   else histoMCDoubleRatioSum->GetYaxis()->SetRangeUser(0.7,2.0);
   histoMCDoubleRatioSum->GetXaxis()->SetRangeUser(0.,12.0);
   DrawGammaSetMarker(histoMCDoubleRatioSum, 20, 1.2, 0, 0);

   histoMCDoubleRatioSum->DrawCopy("");

   histoDoubleRatioConversionTrueEffPurityA->DrawCopy("same");
   //histoDoubleRatioConversionNormalPurity->DrawCopy("same");
   histoDoubleRatioConversionOnlyGamma->DrawCopy("same");
   DrawGammaSetMarker(histoMCDoubleRatioSum, 20, 0.7, 2, 2);


   TFile *DoubleRatioFile = new TFile("DoubleRatio_0020_2040.root","UPDATE");
   histoDoubleRatioConversionTrueEffPurityA->Write("DoubleRatio_2040");
   ConversionFitA->Write(Form("Pi0Fit_%s_2040",fitPi0A.Data()));
   ConversionFitB->Write(Form("Pi0Fit_%s_2040",fitPi0B.Data()));
   ConversionFitC->Write(Form("Pi0Fit_%s_2040",fitPi0C.Data()));
   histoCorrectedYieldTrueEff->Write("Pi0_2040");
   histoGammaSpecCorrPurity->Write("Gamma_2040");
   ConversionSpeccanvas->Write("Pi0WithFits_2040");


   DoubleRatioFile->Close();


   histoDoubleRatioConversionTrueEffPurityA->DrawCopy("same");

   histoDoubleRatioConversionFitPurityA->DrawCopy("");
   One->Draw("same");
   NLODoubleRatio->RemovePoint(0);
   NLODoubleRatio->Draw("lp3");
   DrawGammaSetMarker(histoDoubleRatioConversionOnlyGamma, 24, 2.0, kRed-2,kRed-2);
   histoDoubleRatioConversionOnlyGamma->DrawCopy("same,e1");
   histoDoubleRatioConversionFitPurityA->DrawCopy("same");

   DrawGammaSetMarker(histoDoubleRatioConversionFitPurityA, 24, 2.0, kMagenta+1,kMagenta+1);
   DrawGammaSetMarker(histoDoubleRatioConversionFitPurityWide, 27, 0.8, kMagenta+1,kMagenta+1);
   DrawGammaSetMarker(histoDoubleRatioConversionFitPurityNarrow, 27, 0.8, kMagenta+1,kMagenta+1);
   DrawGammaSetMarker(histoDoubleRatioConversionFitFit, 28, 1.2, kCyan,kCyan);

   TLegend* legendDoubleConversionFit = GetAndSetLegend(0.14,0.7,4,1,"Direct Photon Signal via Conversions");
   legendDoubleConversionFit->AddEntry(histoDoubleRatioConversionTrueEffPurityA,"Measured Direct Photon Signal","p");
   if(option.CompareTo("PbPb_2.76TeV") == 0) legendDoubleConversionFit->AddEntry(NLODoubleRatio,"pp NLO Direct Photon  pp 2.76TeV scaled N_{coll}","l");
   else legendDoubleConversionFit->AddEntry(NLODoubleRatio,"pp NLO Direct Photon","l");
   legendDoubleConversionFit->Draw();
   //legendDoubleConversionFit->AddEntry(NLOdoubleRatioFit,"Fit to NLO Double Ratio","l");

   DrawAliceLogoAdv(0.13,0.43,"Work in Progress",option,"r",canvasConversionFitDoubleRatioSum,centrality);

   canvasConversionFitDoubleRatioSum->Print(Form("%s/%s_DoubleRatioFit_Sum%s_%s_%s.%s",outputDir.Data(),textPi0New.Data(),centralityQM.Data(),cutSel.Data(),fGammaCutSelection.Data(),suffix.Data()));


   TCanvas *canvasConversionDoubleRatioSum = GetAndSetCanvas("canvasConversionDoubleRatioSum");
   canvasConversionDoubleRatioSum->SetLogx();

   SetHistogramm(histoDoubleRatioConversionTrueEffPurityA,"#it{p}_{T} (GeV/#it{c})","(#gamma_{inc}/#pi^{0})/(#gamma_{decay}/#pi^{0})",0.7,1.8);
   DrawGammaSetMarker(histoDoubleRatioConversionTrueEffPurityA, 20, 2.0, 1, 1);
   SetHistogramm(histoDoubleRatioConversionTrueEffPurityWide,"#it{p}_{T} (GeV/#it{c})","(#gamma_{inc}/#pi^{0})/(#gamma_{decay}/#pi^{0})",0.7,1.8);
   DrawGammaSetMarker(histoDoubleRatioConversionTrueEffPurityWide, 20, 0.8, 1, 1);
   SetHistogramm(histoDoubleRatioConversionTrueEffPurityNarrow,"#it{p}_{T} (GeV/#it{c})","(#gamma_{inc}/#pi^{0})/(#gamma_{decay}/#pi^{0})",0.7,1.8);
   DrawGammaSetMarker(histoDoubleRatioConversionTrueEffPurityNarrow, 20, 0.8, 1, 1);
   SetHistogramm(histoDoubleRatioConversionTrueEffPuritySyst,"#it{p}_{T} (GeV/#it{c})","(#gamma_{inc}/#pi^{0})/(#gamma_{decay}/#pi^{0})",0.7,1.8);

   if(!option.CompareTo("PbPb_2.76TeV")){
      histoDoubleRatioConversionTrueEffPurityA->GetYaxis()->SetRangeUser(0.7,3.0);
      histoDoubleRatioConversionTrueEffPurityA->GetXaxis()->SetRangeUser(0.3,10.1);
   }
   else{
      histoDoubleRatioConversionTrueEffPurityA->GetYaxis()->SetRangeUser(0.7,2.5);
   }
   dummy->GetYaxis()->SetRangeUser(0.7,3.0);
   dummy->GetXaxis()->SetRangeUser(0.8,8.0);
   SetHistogramm(dummy, "#it{p}_{T} (GeV/#it{c})", "(#gamma_{inc}/#pi^{0})/(#gamma_{decay}/#pi^{0})");
   dummy->DrawCopy();

   NLODoubleRatio->Draw("lp3same");
   One->Draw("same");

   // DrawGammaSetMarker(histoDoubleRatioConversionFitPurityPionsLow, 20, 2.0, kRed-2,kRed-2);
   // histoDoubleRatioConversionFitPurityPionsLow->Draw("same,e1");
   // DrawGammaSetMarker(histoDoubleRatioConversionFitPurityPionsHigh, 20, 2.0, kBlue-2,kBlue-2);
   // histoDoubleRatioConversionFitPurityPionsHigh->Draw("same,e1");
   // DrawGammaSetMarker(histoDoubleRatioConversionFitPurityPionsAverage, 25, 2.0, kGreen-2,kGreen-2);
   histoDoubleRatioConversionFitPurityPionsAverage->Draw("same,e1");

   DrawGammaSetMarker(histoDoubleRatioConversionFitPurityA, 20, 2.0, 1,1);
   DrawGammaSetMarker(histoDoubleRatioConversionFitPurityB, 24, 2.0, 2,2);
   DrawGammaSetMarker(histoDoubleRatioConversionFitPurityC, 27, 2.0, 3,3);
   DrawGammaSetMarker(histoDoubleRatioConversionFitPurityAB, 24, 2.0, 3,3);
   histoDoubleRatioConversionFitPurityA->DrawCopy("same,e1");
   //histoDoubleRatioConversionTrueEffPurityA->DrawCopy("same");
   // histoDoubleRatioConversionFitPurityLow->DrawCopy("same,e1");
   // histoDoubleRatioConversionFitPurityHigh->DrawCopy("same,e1");

   //histoDoubleRatioConversionFitPurityC->Divide(histoDoubleRatioConversionFitPurityB);
   //histoDoubleRatioConversionFitPurityPionsAverage->DrawCopy("same,e1");
   histoDoubleRatioConversionFitPurityB->DrawCopy("same,e1");
   //histoDoubleRatioConversionTrueEffPurityA->DrawCopy("same");
   histoDoubleRatioConversionFitPurityC->DrawCopy("same,e1");
   //histoDoubleRatioConversionFitPurityAB->DrawCopy("same,e1");
   //histoDoubleRatioConversionOnlyGamma->DrawCopy("same");
   // for(Int_t i = 0; i<histoDoubleRatioConversionFitPurityC->GetNbinsX();i++){
   //    cout<<histoDoubleRatioConversionFitPurityC->GetBinContent(i)<<endl;


   // }
   // return;


   TLegend* legendDoubleConversion = GetAndSetLegend(0.16,0.71, 5);
   legendDoubleConversion->AddEntry(histoDoubleRatioConversionFitPurityA,"Direct photons signal with neutral pions");
   // legendDoubleConversion->AddEntry(histoDoubleRatioConversionFitPurityB,"Direct photons signal with neutral and high p_{T} charged pions");
   // legendDoubleConversion->AddEntry(histoDoubleRatioConversionFitPurityA,"Direct photons signal with m_{T} scaling");
   // legendDoubleConversion->AddEntry(histoDoubleRatioConversionFitPurityB,"Direct photons signal with #pi^{0} R_{AA} scaling for #eta");
   // legendDoubleConversion->AddEntry(histoDoubleRatioConversionFitPurityC,"Direct photons signal with K^{0}_{s} for #eta");
   //legendDoubleConversion->AddEntry(histoDoubleRatioConversionFitPurityPions,"Direct photons signal with fit on charged pions");
   //legendDoubleConversion->AddEntry(NLODoubleRatio,"pp NLO Direct Photon  pp 2.76TeV scaled N_{^{coll}}","l");
   legendDoubleConversion->Draw();

   DrawAliceLogoAdv(0.13,0.45,"Work in Progress",option,"r",canvasConversionDoubleRatioSum,centrality);
   //DrawSystem(0.15,0.65,option.Data(),centrality);
   //DrawAliceLogoAdv(0.13,0.43,"Work in Progress",option,"r",canvasConversionDoubleRatioSum,centrality);


   canvasConversionDoubleRatioSum->Print(Form("%s/%s_DoubleRatio_Sum%s_%s_%s.%s",outputDir.Data(),textPi0New.Data(),centralityQM.Data(),cutSel.Data(),fGammaCutSelection.Data(),suffix.Data()));


   TCanvas* canvasDoubleRatioNeutralChargedRatio = GetAndSetCanvas("DoubleRatioNeutralChargedRatio",0.15,0.1);

   TH1D* DoubleRatioNeutralChargedRatio = (TH1D*)histoDoubleRatioConversionTrueEffPurityA->Clone("DoubleRatioNeutralChargedRatio");
   DoubleRatioNeutralChargedRatio->Divide(histoDoubleRatioConversionFitPurityPionsAverage);

   SetHistogramm(DoubleRatioNeutralChargedRatio,"#it{p}_{T} (GeV/#it{c})","Ratio: Double Ratio #pi^{0} / #pi^{#pm}",0.5,1.5);

   DoubleRatioNeutralChargedRatio->DrawCopy("e1");
   One->Draw("same");

   canvasDoubleRatioNeutralChargedRatio->Print(Form("%s/%s_DoubleRatioNeutralToCharged_%s_%s_%s.%s",outputDir.Data(),textPi0New.Data(),centralityQM.Data(),cutSel.Data(),fGammaCutSelection.Data(),suffix.Data()));



   // // --------------------- Slope Inclusive and Decay ---------------------

   // TCanvas *canvasSlopeInclusivePhoton = GetAndSetCanvas("SlopeInclusivePhoton");
   // canvasSlopeInclusivePhoton->SetLogy();

   // TF1 *exponetialInclusive = new TF1("Exponential Fit Inclusive","[0]*exp(-x/[1])",1.1,2.8);
   // TF1 *exponetialDecay = new TF1("Exponential Fit Decay","[0]*exp(-x/[1])",1.1,2.8);
   // exponetialInclusive->SetParameters(1.,0.3);
   // exponetialDecay->SetParameters(1.,0.3);
   // exponetialInclusive->SetLineColor(kGreen-2);
   // exponetialInclusive->SetLineStyle(1);
   // exponetialDecay->SetLineColor(kOrange-3);
   // exponetialDecay->SetLineStyle(7);


   // histoGammaSpecCorrPurity->Fit(exponetialInclusive,"IQNRME+","",0.8,2.2);
   // cocktailAllGammaA->Fit(exponetialDecay,"IQNRME+","",0.8,2.2);

   // histoGammaSpecCorrPurity->DrawCopy();
   // cocktailAllGammaA->DrawCopy("same");

   // exponetialInclusive->Draw("same");
   // exponetialDecay->Draw("same");

   // TLegend* legendSlopeInclusivePhoton = GetAndSetLegend(0.34,0.665, 6);
   // legendSlopeInclusivePhoton->SetTextSize(0.031);
   // legendSlopeInclusivePhoton->SetTextFont(42);
   // legendSlopeInclusivePhoton->AddEntry((TObject*)0,"Exponential fits:","");

   // legendSlopeInclusivePhoton->AddEntry(exponetialInclusive,Form("Inclusive Photons, T = %.0f #pm %.0f^{stat} MeV",exponetialInclusive->GetParameter(1)*1000,exponetialInclusive->GetParError(1)*1000),"l");
   // legendSlopeInclusivePhoton->AddEntry(exponetialDecay,Form("Decay Photons , T = %.0f #pm %.0f^{stat} MeV",exponetialDecay->GetParameter(1)*1000,exponetialDecay->GetParError(1)*1000),"l");
   // legendSlopeInclusivePhoton->Draw();

   // canvasSlopeInclusivePhoton->Print(Form("%s/%s_SlopeInclusivePhoton_%s_%s_%s.%s",outputDir.Data(),textPi0New.Data(),centralityQM.Data(),cutSel.Data(),fGammaCutSelection.Data(),suffix.Data()));





   // // --------------------- Direct Photon RAA wit QM Results -------------------------

   // TFile *PrelimFile = new TFile("DirectPhotons_00-40_QM.root");
   // TGraphAsymmErrors *grSystFullp = (TGraphAsymmErrors*)PrelimFile->Get("DirectPhotons_points_syst");
   // TGraphAsymmErrors *grStatFullp = (TGraphAsymmErrors*)PrelimFile->Get("DirectPhotons_points_stat");



   // //DirectPhotons_Prelim->SetLogy();

   // // if(grSystFullp)grSystFullp->Draw("aZ2");
   // // if(grStatFullp)grStatFullp->Draw("PZe1same");
   // TGraphAsymmErrors *NLOScaled = (TGraphAsymmErrors*)NLO->Clone("NLOScaled");
   // NLOScaled = ScaleGraph(NLOScaled,828); // 0-40%
   // NLOScaled->Draw("ap");

   // Double_t *errorHighPoints = new Double_t[NLOScaled->GetN()];
   // Double_t *errorLowPoints = new Double_t[NLOScaled->GetN()];

   // for(Int_t i = 0; i<NLOScaled->GetN(); i++){
   //    Double_t x,y;
   //    NLOScaled->GetPoint(i,x,y);
   //    errorHighPoints[i] = NLOScaled->GetErrorYhigh(i)+y;
   //    errorLowPoints[i] = y-NLOScaled->GetErrorYlow(i);

   // }

   // TGraphAsymmErrors *NLOScaledHighErrors = new TGraphAsymmErrors(NLOScaled->GetN(),NLOScaled->GetX(),errorHighPoints,NLOScaled->GetEXlow(),NLOScaled->GetEXhigh(),NULL,NULL);
   // TGraphAsymmErrors *NLOScaledLowErrors = new TGraphAsymmErrors(NLOScaled->GetN(),NLOScaled->GetX(),errorLowPoints, NLOScaled->GetEXlow(),NLOScaled->GetEXhigh(),NULL,NULL);

   // TSpline3 *SplineNLO = new TSpline3("SplineNLO",NLOScaled);
   // TSpline3 *SplineNLOHigh = new TSpline3("SplineNLOHigh",NLOScaledHighErrors);
   // TSpline3 *SplineNLOLow = new TSpline3("SplineNLOLow",NLOScaledLowErrors);


   // // SplineNLO->Draw();
   // // SplineNLOHigh->Draw("same");
   // // SplineNLOLow->Draw("same");



   // TGraphAsymmErrors *DirectPhotonRAA_syst = (TGraphAsymmErrors*)grSystFullp->Clone("DirectPhotonRAA_syst");
   // TGraphAsymmErrors *DirectPhotonRAA_stat = (TGraphAsymmErrors*)grStatFullp->Clone("DirectPhotonRAA_stat");
   // TGraphAsymmErrors *DirectPhotonRAA_NLOErrorHigh = (TGraphAsymmErrors*)grStatFullp->Clone("DirectPhotonRAA_NLOErrorHigh");
   // TGraphAsymmErrors *DirectPhotonRAA_NLOErrorLow = (TGraphAsymmErrors*)grStatFullp->Clone("DirectPhotonRAA_NLOErrorLow");
   // DirectPhotonRAA_syst = CalculateGraphErrRatioToSpline (DirectPhotonRAA_syst ,SplineNLO);
   // DirectPhotonRAA_stat = CalculateGraphErrRatioToSpline (DirectPhotonRAA_stat ,SplineNLO);
   // DirectPhotonRAA_NLOErrorHigh = CalculateGraphErrRatioToSpline (DirectPhotonRAA_NLOErrorHigh ,SplineNLOHigh);
   // DirectPhotonRAA_NLOErrorLow = CalculateGraphErrRatioToSpline (DirectPhotonRAA_NLOErrorLow ,SplineNLOLow);

   // for(Int_t i = 0;i<7;i++){
   //    DirectPhotonRAA_syst->RemovePoint(0);
   //    DirectPhotonRAA_stat->RemovePoint(0);
   //    DirectPhotonRAA_NLOErrorHigh->RemovePoint(0);
   //    DirectPhotonRAA_NLOErrorLow->RemovePoint(0);
   // }

   // Double_t *errorNLOHigh = new Double_t[DirectPhotonRAA_NLOErrorHigh->GetN()];
   // Double_t *errorNLOLow = new Double_t[DirectPhotonRAA_NLOErrorLow->GetN()];

   // for(Int_t i = 0;i<DirectPhotonRAA_NLOErrorHigh->GetN(); i++){
   //    Double_t x,y;
   //    DirectPhotonRAA_stat->GetPoint(i,x,y);
   //    Double_t xNLOHigh,yNLOHigh;
   //    DirectPhotonRAA_NLOErrorHigh->GetPoint(i,xNLOHigh,yNLOHigh);
   //    errorNLOHigh[i] = y-yNLOHigh;
   //    Double_t xNLOLow,yNLOLow;
   //    DirectPhotonRAA_NLOErrorLow->GetPoint(i,xNLOLow,yNLOLow);
   //    errorNLOLow[i] = yNLOLow-y;

   // }


   // TGraphAsymmErrors *DirectPhotonRAA_NLOErrors = new TGraphAsymmErrors(DirectPhotonRAA_stat->GetN(),DirectPhotonRAA_stat->GetX(),DirectPhotonRAA_stat->GetY(),DirectPhotonRAA_syst->GetEXlow(),DirectPhotonRAA_syst->GetEXhigh(),errorNLOHigh,errorNLOLow);
   // DrawGammaSetMarkerTGraphAsym(DirectPhotonRAA_NLOErrors , 20,2, kRed-2, kRed-2, 1, kTRUE);


   // TCanvas* DirectPhotons_Prelim = GetAndSetCanvas("DirectPhotons_Prelim",0.07,0.1);
   // SetHistogramm(dummy,"#it{p}_{T} (GeV/#it{c})","#it{R}_{AA}^{#gamma_{dir}}",0,7);
   // dummy->GetXaxis()->SetRangeUser(0,12.2);
   // dummy->GetYaxis()->SetNdivisions(10,5,0,kTRUE);
   // dummy->GetYaxis()->CenterTitle(kFALSE);
   // dummy->GetYaxis()->SetTitleOffset(0.7);
   // dummy->DrawCopy();

   // DirectPhotonRAA_syst->SetFillColor(kGray);
   // DirectPhotonRAA_syst->Draw("2");
   // One->Draw("same");
   // DirectPhotonRAA_stat->SetMarkerSize(2);
   // DirectPhotonRAA_stat->SetMarkerStyle(20);
   // DirectPhotonRAA_NLOErrors->Draw("Z2");
   // DirectPhotonRAA_stat->Draw("Pe1same");


   // DirectPhotonRAA_syst->SetMarkerSize(2);
   // DirectPhotonRAA_syst->SetMarkerStyle(20);

   // TGraphAsymmErrors *forLegend = (TGraphAsymmErrors*)DirectPhotonRAA_NLOErrors->Clone();
   // forLegend->SetFillStyle(1001);
   // forLegend->SetFillColor(kGray);
   // //DirectPhotonRAA_syst->SetLineColor(kGray);
   // TLegend* legendDirectPhotons_Prelim = GetAndSetLegend(0.35,0.7,4,1," Pb-Pb, #sqrt{s_{_{NN}}} = 2.76 TeV");
   // legendDirectPhotons_Prelim->AddEntry(DirectPhotonRAA_syst,"Direct Photon #it{R}_{AA} (NLO pp reference)","pfle");
   // legendDirectPhotons_Prelim->AddEntry(forLegend,"NLO energy scale uncertainty, #mu = 0.5, 1.0, 2.0","fe");
   // legendDirectPhotons_Prelim->AddEntry((TObject*)0,"(PDF: CTEQ6M5 FF: DSS)","");
   // legendDirectPhotons_Prelim->Draw();

   // DrawAliceLogoAdv(0.09,0.7,"Preliminary","","r",DirectPhotons_Prelim,"");


   // DirectPhotons_Prelim->Print(Form("%s/%s_DirectPhotons_RAA_%s_%s_%s.%s",outputDir.Data(),textPi0New.Data(),centralityQM.Data(),cutSel.Data(),fGammaCutSelection.Data(),suffix.Data()));
   // DirectPhotons_Prelim->Print(Form("%s/%s_DirectPhotons_RAA_%s_%s_%s.C",outputDir.Data(),textPi0New.Data(),centralityQM.Data(),cutSel.Data(),fGammaCutSelection.Data()));




   // TCanvas* DecayPhotonRCP = GetAndSetCanvas("DecayPhotonRCP");


   // TFile *cocktailFile0010 = new TFile("CocktailInput/cocktail_PbPb_0010_qcd.root");
   // TDirectoryFile* cocktailDir0010 = (TDirectoryFile*) cocktailFile0010->Get("cocktail_PbPb_0010_qcd");
   // TH1D *allDecayGamma0010 = (TH1D*)cocktailDir0010->Get("ptg");
   // TFile *cocktailFile1020 = new TFile("CocktailInput/cocktail_PbPb_1020_qcd.root");
   // TDirectoryFile* cocktailDir1020 = (TDirectoryFile*) cocktailFile1020->Get("cocktail_PbPb_1020_qcd");
   // TH1D *allDecayGamma1020 = (TH1D*)cocktailDir1020->Get("ptg");
   // TFile *cocktailFile0020 = new TFile("CocktailInput/cocktail_PbPb_0020_qcd.root");
   // TDirectoryFile* cocktailDir0020 = (TDirectoryFile*) cocktailFile0020->Get("cocktail_PbPb_0020_qcd");
   // TH1D *allDecayGamma0020 = (TH1D*)cocktailDir0020->Get("ptg");
   // TFile *cocktailFile2040 = new TFile("CocktailInput/cocktail_PbPb_2040_qcd.root");
   // TDirectoryFile* cocktailDir2040 = (TDirectoryFile*) cocktailFile2040->Get("cocktail_PbPb_2040_qcd");
   // TH1D *allDecayGamma2040 = (TH1D*)cocktailDir2040->Get("ptg");
   // TFile *cocktailFile4080 = new TFile("CocktailInput/cocktail_PbPb_4080_qcd.root");
   // TDirectoryFile* cocktailDir4080 = (TDirectoryFile*) cocktailFile4080->Get("cocktail_PbPb_4080_qcd");
   // TH1D *allDecayGamma4080 = (TH1D*)cocktailDir4080->Get("ptg");


   // Double_t mult0010 = 0;
   // for(Int_t i = 0; i<1;i++){
   //    mult0010 += multiplicity[i];
   //    cout<<multiplicity[i]<<endl;
   // }
   // mult0010 = mult0010/1;
   // Double_t mult1020 = 0;
   // for(Int_t i = 1; i<2;i++){
   //    mult1020 += multiplicity[i];
   //    cout<<multiplicity[i]<<endl;
   // }
   // mult1020 = mult1020/1;
   // Double_t mult0020 = 0;
   // for(Int_t i = 0; i<2;i++){
   //    mult0020 += multiplicity[i];
   //    cout<<multiplicity[i]<<endl;
   // }
   // mult0020 = mult0020/2;
   // Double_t mult2040 = 0;
   // for(Int_t i = 2; i<4;i++){
   //    mult2040 += multiplicity[i];
   //    cout<<multiplicity[i]<<endl;
   // }
   // mult2040 = mult2040/2;
   // Double_t mult4080 = 0;
   // for(Int_t i = 4; i<8;i++){
   //    mult4080 += multiplicity[i];
   //    cout<<multiplicity[i]<<endl;
   // }
   // mult4080 = mult4080/4;


   // allDecayGamma0010->Scale(1./mult0010);
   // allDecayGamma1020->Scale(1./mult1020);
   // allDecayGamma0020->Scale(1./mult0020);
   // allDecayGamma2040->Scale(1./mult2040);
   // allDecayGamma4080->Scale(1./mult4080);

   // if(centCutNumberI==0 && centCutNumberBI == 1){
   //    allDecayGamma0010->Divide(allDecayGamma0010);
   //    allDecayGamma0010->Draw();
   // }
   // if(centCutNumberI==1 && centCutNumberBI == 2){
   //    allDecayGamma0010->Divide(allDecayGamma1020);
   //    allDecayGamma0010->Draw();
   // }
   // if(centCutNumberI==0 && centCutNumberBI == 2){
   //    allDecayGamma0010->Divide(allDecayGamma0020);
   //    allDecayGamma0010->Draw();
   // }
   // if(centCutNumberI==2 && centCutNumberBI == 4){
   //    allDecayGamma0010->Divide(allDecayGamma2040);
   //    allDecayGamma0010->Draw();
   // }
   // if(centCutNumberI==4 && centCutNumberBI == 8){
   //    allDecayGamma0010->Divide(allDecayGamma4080);
   //    allDecayGamma0010->Draw();
   // }

   // allDecayGamma0010 = RebinTH1D(allDecayGamma0010,histoCorrectedYieldTrueEff);
   // allDecayGamma1020 = RebinTH1D(allDecayGamma1020,histoCorrectedYieldTrueEff);
   // allDecayGamma0020 = RebinTH1D(allDecayGamma0020,histoCorrectedYieldTrueEff);
   // allDecayGamma2040 = RebinTH1D(allDecayGamma2040,histoCorrectedYieldTrueEff);
   // allDecayGamma4080 = RebinTH1D(allDecayGamma4080,histoCorrectedYieldTrueEff);

   // DecayPhotonRCP->Print(Form("%s/%s_DecayPhotonRCP_%s_%s_%s.%s",outputDir.Data(),textPi0New.Data(),centralityQM.Data(),cutSel.Data(),fGammaCutSelection.Data(),suffix.Data()));


   // TCanvas* DirectPhotonDoubleRatioScaledWithRCP = GetAndSetCanvas("DirectPhotonDoubleRatioScaledWithRCP");

   // TH1D *DoubleRatioPurityFitAScaledRCP = (TH1D*)histoDoubleRatioConversionFitPurityA->Clone("DoubleRatioPurityFitAScaledRCP");

   // for(Int_t i = 0;i<DoubleRatioPurityFitAScaledRCP->GetNbinsX();i++){
   //    DoubleRatioPurityFitAScaledRCP->SetBinContent(i,(DoubleRatioPurityFitAScaledRCP->GetBinContent(i)-1));
   //    cout<<DoubleRatioPurityFitAScaledRCP->GetBinContent(i)<<endl;
   // }
   // DoubleRatioPurityFitAScaledRCP->Divide(allDecayGamma0010);
   // for(Int_t i = 0;i<DoubleRatioPurityFitAScaledRCP->GetNbinsX();i++){
   //    DoubleRatioPurityFitAScaledRCP->SetBinContent(i,DoubleRatioPurityFitAScaledRCP->GetBinContent(i)+1);
   // }

   // DrawGammaSetMarker(DoubleRatioPurityFitAScaledRCP, 20, 2.0, 2, 2);

   // DoubleRatioPurityFitAScaledRCP->DrawCopy();
   // histoDoubleRatioConversionFitPurityA->DrawCopy("same");
   // DirectPhotonDoubleRatioScaledWithRCP->Print(Form("%s/%s_DoubleRatioPurityFitAScaledRCP_%s_%s_%s.%s",outputDir.Data(),textPi0New.Data(),centralityQM.Data(),cutSel.Data(),fGammaCutSelection.Data(),suffix.Data()));
   // --------------------- Direct Photon Spectrum -------------------------


   // TH1D *histoDirectPhotonSpectrum = (TH1D*)histoGammaSpecCorrPurity->Clone("histoDirectPhotonSpectrum");
   // TH1D *histoDirectPhotonSpectrumFit = (TH1D*)histoGammaSpecCorrPurity->Clone("histoDirectPhotonSpectrumFit");
   // TH1D *histoDirectPhotonSpectrumCharged = (TH1D*)histoGammaSpecCorrPurity->Clone("histoDirectPhotonSpectrumCharged");
   // DrawGammaSetMarker(histoDirectPhotonSpectrum, 20, 2.0, 1,1);
   // DrawGammaSetMarker(histoDirectPhotonSpectrumFit, 24, 2.0, kRed+2,kRed+2);
   // DrawGammaSetMarker(histoDirectPhotonSpectrumCharged, 28, 2.0, kCyan+1,kCyan+1);

   // TH1D *histoThermalPhotonSpectrum = (TH1D*)histoGammaSpecCorrPurity->Clone("histoThermalPhotonSpectrum");
   // TH1D *histoPromptPhotonSpectrum = (TH1D*)histoGammaSpecCorrPurity->Clone("histoPromptPhotonSpectrum");
   // histoDirectPhotonSpectrum->GetYaxis()->SetRangeUser(1e-7,200);
   // DrawGammaSetMarker(histoDirectPhotonSpectrum, 24, 1.1, 1,1);
   // histoThermalPhotonSpectrum->GetYaxis()->SetRangeUser(1e-7,200);
   // DrawGammaSetMarker(histoThermalPhotonSpectrum, 21, 1.1, kRed,kRed);
   // histoPromptPhotonSpectrum->GetYaxis()->SetRangeUser(1e-7,200);
   // DrawGammaSetMarker(histoPromptPhotonSpectrum, 24, 1.1, kBlue,kBlue);
   // TCanvas* DirectPhotons = GetAndSetCanvas("DirectPhotons",0.15,0.1,1000 ,1500);
   // DirectPhotons->SetLogy();

   // for(Int_t i = 1; i<histoDirectPhotonSpectrum->GetNbinsX();i++){
   //    histoDirectPhotonSpectrum->SetBinContent(i+1,0);
   //    histoThermalPhotonSpectrum->SetBinContent(i+1,0);
   // }
   // //histoDoubleRatioConversionTrueEffPurity
   // //histoDoubleRatioConversionFitPurity
   // //histoDoubleRatioConversionFitPurityPions


   // for(Int_t i = 1; i<histoDirectPhotonSpectrum->GetNbinsX();i++){
   //    Double_t binContent = -1;
   //    Double_t binError = -1;

   //    binContent = 1-(1./( histoDoubleRatioConversionFitPurityPionsAverage->GetBinContent(i+1)));
   //    binContent = binContent*histoGammaSpecCorrPurity->GetBinContent(i+1);
   //    binError = 1-(1./( histoDoubleRatioConversionFitPurityPionsAverage->GetBinContent(i+1) + histoDoubleRatioConversionFitPurityPionsAverage->GetBinError(i+1)));
   //    binError = binError*histoGammaSpecCorrPurity->GetBinContent(i+1);
   //    binError = binError-binContent;
   //    histoDirectPhotonSpectrumCharged->SetBinContent(i+1,binContent);
   //    histoDirectPhotonSpectrumCharged->SetBinError(i+1,binError);

   //    binContent = 1-(1./( histoDoubleRatioConversionFitPurityA->GetBinContent(i+1)));
   //    binContent = binContent*histoGammaSpecCorrPurity->GetBinContent(i+1);
   //    binError = 1-(1./( histoDoubleRatioConversionFitPurityA->GetBinContent(i+1) + histoDoubleRatioConversionFitPurityA->GetBinError(i+1)));
   //    binError = binError*histoGammaSpecCorrPurity->GetBinContent(i+1);
   //    binError = binError-binContent;
   //    histoDirectPhotonSpectrumFit->SetBinContent(i+1,binContent);
   //    histoDirectPhotonSpectrumFit->SetBinError(i+1,binError);

   //    binContent = 1-(1./( histoDoubleRatioConversionTrueEffPurityA->GetBinContent(i+1)));
   //    binContent = binContent*histoGammaSpecCorrPurity->GetBinContent(i+1);
   //    binError = 1-(1./( histoDoubleRatioConversionTrueEffPurityA->GetBinContent(i+1) + histoDoubleRatioConversionTrueEffPurityA->GetBinError(i+1)));
   //    binError = binError*histoGammaSpecCorrPurity->GetBinContent(i+1);
   //    binError = binError-binContent;
   //    histoDirectPhotonSpectrum->SetBinContent(i+1,binContent);
   //    histoDirectPhotonSpectrum->SetBinError(i+1,binError);


   //    if(histoDirectPhotonSpectrum->GetBinCenter(i+1)<4.5){
   //       binContent = 1-(1./(1+ histoDoubleRatioConversionFitPurityPionsAverage->GetBinContent(i+1) - NLOdoubleRatioFit->Eval(histoDoubleRatioConversionFitPurityPionsAverage->GetBinCenter(i+1))));
   //       binContent = binContent*histoGammaSpecCorrPurity->GetBinContent(i+1);
   //       histoThermalPhotonSpectrum->SetBinContent(i+1,binContent);
   //       histoThermalPhotonSpectrum->SetBinError(i+1,binError);
   //    }
   //    else{
   //       histoThermalPhotonSpectrum->SetBinContent(i+1,0);
   //       histoThermalPhotonSpectrum->SetBinError(i+1,0);
   //    }
   //    if(histoDirectPhotonSpectrum->GetBinCenter(i+1)<4.5){
   //       binContent = 1-(1./(NLOdoubleRatioFit->Eval(histoDoubleRatioConversionFitPurityPionsAverage->GetBinCenter(i+1))));
   //       binContent = binContent*histoGammaSpecCorrPurity->GetBinContent(i+1);
   //       histoPromptPhotonSpectrum->SetBinContent(i+1,binContent);
   //       histoPromptPhotonSpectrum->SetBinError(i+1,0.0000001);
   //    }
   //    else{
   //       histoPromptPhotonSpectrum->SetBinContent(i+1,0);
   //       histoPromptPhotonSpectrum->SetBinError(i+1,0);
   //    }
   // }

   // dummy->GetYaxis()->SetLabelSize(0.035);
   // dummy->GetXaxis()->SetLabelSize(0.035);
   // dummy->GetYaxis()->SetTitleSize(0.035);
   // dummy->GetXaxis()->SetTitleSize(0.035);
   // dummy->GetYaxis()->SetTitleOffset(1.8);
   // dummy->GetXaxis()->SetTitleOffset(1.4);

   // dummy->GetXaxis()->SetRangeUser(0.6,8);
   // dummy->GetYaxis()->SetRangeUser(3e-5,10);

   // dummy->DrawCopy();


   // //histoThermalPhotonSpectrum->Draw("same");

   // // histoPromptPhotonSpectrum->GetXaxis()->SetRangeUser(1.2,14);
   // // histoPromptPhotonSpectrum->Draw("lpsame");

   // TF1 *exponetialA = new TF1("Exponential Fit A","[0]*exp(-x/[1])",1.0,3.0);
   // TF1 *exponetialB = new TF1("Exponential Fit B","[0]*exp(-x/[1])",1.0,3.0);
   // TF1 *exponetialC = new TF1("Exponential Fit C","[0]*exp(-x/[1])",1.0,3.0);
   // TF1 *exponetialD = new TF1("Exponential Fit D","[0]*exp(-x/[1])",1.0,3.0);

   // exponetialA->SetParameters(1.,0.3);
   // exponetialB->SetParameters(1.,0.3);
   // exponetialC->SetParameters(1.,0.3);
   // exponetialD->SetParameters(1.,0.3);
   // cout<<"============EXPO FIT=============="<<endl;
   // histoDirectPhotonSpectrum->Fit(exponetialA,"INRME+","",0.8,2.7);
   // histoDirectPhotonSpectrumFit->Fit(exponetialB,"INRME+","",0.8,2.7);
   // histoDirectPhotonSpectrumCharged->Fit(exponetialC,"INRME+","",0.8,2.7);
   // cout<<"Chi2  ----> "<<exponetialA->GetChisquare()/exponetialA->GetNDF()<<endl;
   // // histoThermalPhotonSpectrum->Fit(exponetialB,"IQNRME+","",1.1,2.2);
   // // histoThermalPhotonSpectrum->Fit(exponetialC,"IQNRME+","",0.8,3.0);
   // // histoDirectPhotonSpectrum->Fit(exponetialD,"IQNRME+","",0.8,3.0);
   // cout<<"============EXPO FIT=============="<<endl;
   // exponetialA->SetLineColor(kGreen-2);
   // exponetialA->SetLineStyle(1);
   // exponetialB->SetLineColor(kOrange-3);
   // exponetialB->SetLineStyle(7);
   // exponetialC->SetLineColor(kMagenta-2);
   // exponetialC->SetLineStyle(3);
   // exponetialD->SetLineColor(kYellow-1);
   // exponetialD->SetLineStyle(5);


   // exponetialA->Draw("same");
   // exponetialB->Draw("same");
   // exponetialC->Draw("same");
   // //exponetialD->Draw("same");

   // histoDirectPhotonSpectrum->Draw("same,e1");
   // histoDirectPhotonSpectrumFit->Draw("same,e1");
   // histoDirectPhotonSpectrumCharged->Draw("same,e1");


   // NLO->SetMarkerSize(0);
   // NLO->Draw("same");
   // //histoThermalPhotonSpectrum->Draw("same");
   // //histoDirectPhotonSpectrum->Draw("same");
   // TLegend* legendDirectPhoton = GetAndSetLegend(0.34,0.665, 6);
   // legendDirectPhoton->SetTextSize(0.031);
   // legendDirectPhoton->SetTextFont(42);
   // legendDirectPhoton->AddEntry(histoDirectPhotonSpectrum,"Direct Photon Spectrum","p");
   // legendDirectPhoton->AddEntry(histoDirectPhotonSpectrumFit,"Direct Photon Spectrum (#pi^{0} Fit)","p");
   // legendDirectPhoton->AddEntry(histoDirectPhotonSpectrumCharged,"Direct Photon Spectrum (#pi^{#pm})","p");
   // // legendDirectPhoton->AddEntry(histoThermalPhotonSpectrum,"Direct - NLO double ratio fit","p");
   // // legendDirectPhoton->AddEntry(NLO,"NLO Photons (PDF: CTEQ6M5 FF: DSS)","l");
   // // legendDirectPhoton->AddEntry(histoPromptPhotonSpectrum,"NLO Photons from doube ratio fit","p");
   // legendDirectPhoton->AddEntry((TObject*)0,"Exponential fits:","");
   // // legendDirectPhoton->AddEntry(exponetialA,Form("Direct Photons, T = %.0f #pm %.0f^{stat} MeV",exponetialA->GetParameter(1)*1000,exponetialA->GetParError(1)*1000),"l");
   // // legendDirectPhoton->AddEntry(exponetialD,Form("Up to 3.0 GeV/#it{c}, T = %.0f #pm %.0f^{stat} MeV",exponetialD->GetParameter(1)*1000,exponetialD->GetParError(1)*1000),"l");
   // // legendDirectPhoton->AddEntry(exponetialB,Form("Subtracted NLO, T = %.0f #pm %.0f^{stat} MeV",exponetialB->GetParameter(1)*1000,exponetialB->GetParError(1)*1000),"l");
   // // legendDirectPhoton->AddEntry(exponetialC,Form("Up to 3.0 GeV/#it{c}, T = %.0f #pm %.0f^{stat} MeV",exponetialC->GetParameter(1)*1000,exponetialC->GetParError(1)*1000),"l");

   // legendDirectPhoton->AddEntry(exponetialA,Form("Direct Photons, T = %.0f #pm %.0f^{stat} MeV",exponetialA->GetParameter(1)*1000,exponetialA->GetParError(1)*1000),"l");
   // legendDirectPhoton->AddEntry(exponetialB,Form("Direct Photons (#pi^{0} Fit), T = %.0f #pm %.0f^{stat} MeV",exponetialB->GetParameter(1)*1000,exponetialB->GetParError(1)*1000),"l");
   // legendDirectPhoton->AddEntry(exponetialC,Form("Direct Photons (#pi^{#pm}), T = %.0f #pm %.0f^{stat} MeV",exponetialC->GetParameter(1)*1000,exponetialC->GetParError(1)*1000),"l");


   // legendDirectPhoton->Draw();

   // DirectPhotons->Print(Form("%s/%s_DirectPhotons_Sum%s_%s_%s.%s",outputDir.Data(),textPi0New.Data(),centralityQM.Data(),cutSel.Data(),fGammaCutSelection.Data(),suffix.Data()));

   // dummy->GetXaxis()->SetRangeUser(0.6,15);
   // dummy->GetYaxis()->SetRangeUser(1e-7,10);



   // TCanvas* DirectPhotons2 = GetAndSetCanvas("DirectPhotons",0.15,0.1);
   // DirectPhotons2->SetLogy();

   // dummy->DrawCopy();

   // //histoDirectPhotonSpectrum->DrawCopy("same");
   // NLO->Draw("same");
   // //PbPb276CTEQ61EPS09BFG2_sum_pdferr_InvYield->Draw("same");
   // pp276CT10BFG2_sum_pdferr_InvYield->Draw("same");

   // //legendDirectPhoton2->Draw();


   // DirectPhotons2->Print(Form("%s/%s_DirectPhotons2_Sum%s_%s_%s.%s",outputDir.Data(),textPi0New.Data(),centralityQM.Data(),cutSel.Data(),fGammaCutSelection.Data(),suffix.Data()));

   // // TFile *Dimitri = new TFile("PCM_DoubleRatios_20140110.root","UPDATE");
   // // histoDoubleRatioConversionFitPurityA->Write(Form("DoubleRatio_fixK0sToPi0Ratio_%s",centrality.Data()));
   // // histoDoubleRatioConversionFitPurityB->Write(Form("DoubleRatio_thermalModel_%s",centrality.Data()));
   // // histoDoubleRatioConversionFitPurityC->Write(Form("DoubleRatio_mTscaling_%s",centrality.Data()));
   // // histoDoubleRatioConversionFitPurityAB->Write(Form("DoubleRatio_MeanOFmTscalingANDfixK0sToPi0Ratio_%s",centrality.Data()));
   // // histoDoubleRatioConversionFitPurityPionsAverage->Write(Form("DoubleRatio_ChargedPions_%s",centrality.Data()));
   // // histoGammaSpecCorrPurity->Write(Form("IncGamma_%s",centrality.Data()));
   // // histoCorrectedYieldTrueEff->Write(Form("Pi0_%s",centrality.Data()));
   // // RatioYieldToFit->Write(Form("FitQualityPi0_%s",centrality.Data()));
   // // ChargeSpectrumOverFitStatAverage->Write(Form("FitQualityCharged_%s",centrality.Data()));
   // // // RatioCocktailToYield->Write(Form("CocktailPi0ToPi0_%s",centrality.Data()));
   // // // RatioCocktailToFit->Write(Form("CocktailPi0ToPi0Fit_%s",centrality.Data()));
   // // // RatioCocktailToChargedYield->Write(Form("CocktailFromChargedToChargedFit_%s",centrality.Data()));
   // // Dimitri->Close();

   TString nameOutputFile = Form("%s/%s/%s_%s_GammaConvV1_InclusiveRatio_%s_%s.root",cutSel.Data(),option.Data(),textPi0New.Data(),textPrefix2.Data(),cutSel.Data(),fGammaCutSelection.Data());
   fileCorrectedOutput = new TFile(nameOutputFile,"RECREATE");

   histoTruePi0MCData->Write();
   histoNormalPi0MCData->Write();
   histoPurityGammaMCData->Write();
   histoDoubleRatioConversionFitFit->Write();
   histoDoubleRatioConversionFitPurityA->Write();
   histoDoubleRatioConversionFitPurityB->Write();
   histoDoubleRatioConversionFitPurityC->Write();
   histoDoubleRatioConversionFitPurityWide->Write();
   histoDoubleRatioConversionFitPurityNarrow->Write();
   ConversionFitA->Write();
   ConversionGammaFitA->Write();

   histoIncRatioPurity->Write();
   histoIncRatioPurityTrueEff->Write();
   histoMCIncRatio->Write();
   histoIncRatioGammaMC->Write();
   histoIncRatioFitFit->Write();
   histoIncRatioFitPurityA->Write();
   histoIncRatioFitPurityB->Write();
   histoIncRatioFitPurityC->Write();
   histoIncRatioFitPurityWide->Write();
   histoIncRatioFitPurityNarrow->Write();
   histoIncRatioPurityTrueEffWide->Write();
   histoIncRatioPurityTrueEffNarrow->Write();
   histoIncRatioLowFitPurity->Write();
   histoIncRatioHighFitPurity->Write();
   histoIncRatioFitPurityPionsStatAverage->Write();
   histoDoubleRatioConversionHighFitPurity->Write();
   histoDoubleRatioConversionLowFitPurity->Write();
   histoDoubleRatioConversionTrueEffPurityPions->Write();
   histoDoubleRatioConversionFitPurityPionsAverage->Write();

   if(!option.CompareTo("PbPb_2.76TeV")){
      PbPb276CTEQ61EPS09BFG2_sum_pdferr_InvYield->Write("PbPb276CTEQ61EPS09BFG2_sum_pdferr_InvYield");
      pp276CT10BFG2_sum_pdferr_InvYield->Write("pp276CT10BFG2_sum_pdferr_InvYield");
      PbPb276EPS09BFG2_sum_scale_InvYield->Write("PbPb276EPS09BFG2_sum_scale_InvYield");
      pp276CT10BFG2_sum_scale_InvYield->Write("pp276CT10BFG2_sum_scale_InvYield");
   }

   histoCorrectedYieldTrueEff->Write();
   histoCorrectedYieldTrueEffWide->Write();
   histoCorrectedYieldTrueEffNarrow->Write();
   histoCorrectedYieldTrueEffPi0Fit->Write();
   histoCorrectedYieldTrueEffPi0FitWide->Write();
   histoCorrectedYieldTrueEffPi0FitNarrow->Write();
   histoChargedPionsSystAverage->Write();
   histoChargedPionsStatAverage->Write();
   histoMCesdIncRatio->Write();
   histoDoubleRatioConversionTrueEffPurityA->Write();
   histoDoubleRatioConversionTrueEffPurityLow->Write();
   histoDoubleRatioConversionTrueEffPurityHigh->Write();
   histoDoubleRatioConversionFitPurityLow->Write();
   histoDoubleRatioConversionFitPurityHigh->Write();
   histoDoubleRatioConversionTrueEffPurityEtaLow->Write();
   histoDoubleRatioConversionTrueEffPurityEtaHigh->Write();
   histoDoubleRatioConversionFitPurityEtaLow->Write();
   histoDoubleRatioConversionFitPurityEtaHigh->Write();
   histoDoubleRatioConversionTrueEffPurityPi0ParamLow->Write();
   histoDoubleRatioConversionTrueEffPurityPi0ParamHigh->Write();
   histoDoubleRatioConversionFitPurityPi0ParamLow->Write();
   histoDoubleRatioConversionFitPurityPi0ParamHigh->Write();
   histoDoubleRatioConversionOnlyGamma->Write();
   histoDoubleRatioConversionTrueEffPurityNarrow->Write();
   histoDoubleRatioConversionTrueEffPurityWide->Write();
   histoDoubleRatioConversionTrueEffPuritySyst->Write();
   histoDoubleRatioConversionFitPuritySyst->Write();
   //histoDirectPhotonSpectrum->Write();
   histoGammaSpecCorrPurity->Write("histoGammaSpecCorrPurity");
   cocktailAllGammaPi0original->Write("sumgammapi0");
   cocktailPi0GammaPi0->Write();
   cocktailEtaGammaPi0->Write();
   cocktailOmegaGammaPi0->Write();
   cocktailEtapGammaPi0->Write();
   cocktailPhiGammaPi0->Write();
   cocktailRhoGammaPi0->Write();
   cocktailSigmaGammaPi0->Write();
   cocktailAllGammaA->Write();
   cocktailAllGammaB->Write();
   cocktailAllGammaC->Write();
   cocktailPi0Gamma->Write();
   cocktailEtaGamma->Write();
   cocktailEtapGamma->Write();
   cocktailOmegaGamma->Write();
   cocktailPhiGamma->Write();
   cocktailRhoGamma->Write();
   cocktailSigmaGamma->Write();
   //cocktailPi0A->Write();
   cocktailAllGammaPi0Pions->Write("cocktailAllGammaPi0Pions");
   cocktailAllGammaPi0A->Write("cocktailAllGammaPi0");
   cocktailChargeToNeutral->Write();
   cocktailPi0->Write();
   cocktailEta->Write();
   cocktailOmega->Write();
   cocktailEtap->Write();
   cocktailPhi->Write();
   cocktailSigma->Write();
   cocktailEtaLow->Write("ptEtaLow");
   cocktailEtaHigh->Write("ptEtaHigh");
   cocktailEtaGammaLow->Write("ptgEtaLow");
   cocktailEtaGammaHigh->Write("ptgEtaHigh");
   Kaon0s->Write("K0s");

   histoDecayRatioSumGamma->Write();
   histoDecayRatioPi0Gamma->Write();
   histoDecayRatioEtaGamma->Write();
   histoDecayRatioEtapGamma->Write();
   histoDecayRatioOmegaGamma->Write();
   histoDecayRatioRho0Gamma->Write();
   histoDecayRatioPhiGamma->Write();
   histoMCDoubleRatioSum->Write();
   //DoubleRatioPurityFitAScaledRCP->Write();
   half->Write("doubleRatioNLOhalf");
   one->Write("doubleRatioNLOone");
   two->Write("doubleRatioNLOtwo");

   //if(option.CompareTo("900GeV") != 0){
   graphNLOCalcMuTwo->Write("graphNLOCalcMuTwo");
   graphNLOCalcMuOne->Write("graphNLOCalcMuOne");
   graphNLOCalcMuHalf->Write("graphNLOCalcMuHalf");
   //}
   combined7TeV->Write("combined7TeV");
   //   incRatioCombined7TeV->Write("incRatioCombined7TeV");

   fileCorrectedOutput->Close();

   cout<<"CorrectedYieldTrueEff "<<fitPi0A<<"  "<<resultA<<"  "<<fitParameterA<<endl;
   cout<<ConversionFitA->GetChisquare()/ConversionFitA->GetNDF()<<endl;
   cout<<ConversionFitA->GetParameter(0)<<endl;
   cout<<ConversionFitA->GetParameter(1)<<endl;
   cout<<ConversionFitA->GetParameter(2)<<endl;
   cout<<ConversionFitA->GetParameter(3)<<endl;
   cout<<ConversionFitA->GetParameter(4)<<endl;
   cout<<ConversionFitA->GetParameter(5)<<endl;
   cout<<ConversionFitA->GetParameter(6)<<endl;

   cout<<"CorrectedYieldTrueEff "<<fitPi0B<<"  "<<resultB<<"  "<<fitParameterB<<endl;
   cout<<ConversionFitB->GetChisquare()/ConversionFitB->GetNDF()<<endl;
   cout<<ConversionFitB->GetParameter(0)<<endl;
   cout<<ConversionFitB->GetParameter(1)<<endl;
   cout<<ConversionFitB->GetParameter(2)<<endl;
   cout<<ConversionFitB->GetParameter(3)<<endl;
   cout<<ConversionFitB->GetParameter(4)<<endl;
   cout<<ConversionFitB->GetParameter(5)<<endl;
   cout<<ConversionFitB->GetParameter(6)<<endl;

   cout<<"CorrectedYieldTrueEff "<<fitPi0C<<"  "<<resultC<<"  "<<fitParameterC<<endl;
   cout<<ConversionFitC->GetChisquare()/ConversionFitC->GetNDF()<<endl;
   cout<<ConversionFitC->GetParameter(0)<<endl;
   cout<<ConversionFitC->GetParameter(1)<<endl;
   cout<<ConversionFitC->GetParameter(2)<<endl;
   cout<<ConversionFitC->GetParameter(3)<<endl;
   cout<<ConversionFitC->GetParameter(4)<<endl;
   cout<<ConversionFitC->GetParameter(5)<<endl;
   cout<<ConversionFitC->GetParameter(6)<<endl;


   // cout<<"ConversionFitPionsStatAverage Average "<<"qcd "<<fitParameterCharged<<"  "<<resultCombinedAverage<<endl;
   // cout<<ConversionFitPionsStatAverage->GetChisquare()/ConversionFitPionsStatAverage->GetNDF()<<endl;
   // cout<<ConversionFitPionsStatAverage->GetParameter(0)<<endl;
   // cout<<ConversionFitPionsStatAverage->GetParameter(1)<<endl;
   // cout<<ConversionFitPionsStatAverage->GetParameter(2)<<endl;
   // cout<<ConversionFitPionsStatAverage->GetParameter(3)<<endl;
   // cout<<ConversionFitPionsStatAverage->GetParameter(4)<<endl;

   cout<<"ConversionFitPionsStatAverage "<<fitFuncCharged<<"  "<<fitParameterCharged<<"  "<<resultCombinedStatAverage<<endl;
   cout<<ConversionFitPionsStatAverage->GetChisquare()/ConversionFitPionsStatAverage->GetNDF()<<endl;
   cout<<ConversionFitPionsStatAverage->GetParameter(0)<<endl;
   cout<<ConversionFitPionsStatAverage->GetParameter(1)<<endl;
   cout<<ConversionFitPionsStatAverage->GetParameter(2)<<endl;
   cout<<ConversionFitPionsStatAverage->GetParameter(3)<<endl;
   cout<<ConversionFitPionsStatAverage->GetParameter(4)<<endl;
   cout<<ConversionFitPionsStatAverage->GetParameter(5)<<endl;
   cout<<ConversionFitPionsStatAverage->GetParameter(6)<<endl;

   PrintParameter(ConversionFitNeutralKaons,fitFuncCharged,ConversionFitNeutralKaons->GetName(),6);
   cout<<"Scaling Factor "<<EtaPi0Fit->GetParameter(0)<<" Fit Result "<<resultNeutralKaons<<endl;

   PrintParameter(ConversionFitNeutralKaonsUnscaled,fitFuncCharged,ConversionFitNeutralKaonsUnscaled->GetName(),6);
   cout<<" Fit Result "<<resultNeutralKaonsUnscaled<<endl;


   cout<<0.46/EtaPi0Fit->GetParameter(0)<<endl;
}
