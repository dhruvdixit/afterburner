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
#include "CommonHeaders/PlottingMeson.h"
#include "CommonHeaders/PlottingGammaConversionAdditional.h"
#include "CommonHeaders/FittingGammaConversion.h"
#include "CommonHeaders/ConversionFunctionsBasicsAndLabeling.h"
#include "CommonHeaders/ConversionFunctions.h"
#include "CommonHeaders/CombinationFunctions.h"

void ComparisonOldAndNewPi0PbPb(TString suffix = "pdf"){
   gROOT->Reset();   
   gROOT->SetStyle("Plain");
   
   
   StyleSettingsThesis();  
   SetPlotStyle();

   Color_t  colorCombPbPb0005          = kRed+1;
   Color_t  colorCombPbPb0010          = kRed+1;
   Color_t  colorCombPbPb0510          = 807;
   Color_t  colorCombPbPb1020          = 800;
   Color_t  colorCombPbPb2040          = kGreen+2;
   Color_t  colorCombPbPb4060          = kCyan+2;
   Color_t  colorCombPbPb6080          = kBlue+1;

   Color_t  colorCombMCPbPb0005           = kRed+3;
   Color_t  colorCombMCPbPb0010           = kRed+3;
   Color_t  colorCombMCPbPb0510           = 807+2;
   Color_t  colorCombMCPbPb1020           = 800+2;
   Color_t  colorCombMCPbPb2040           = kGreen+4;
   Color_t  colorCombMCPbPb4060           = kCyan+4;
   Color_t  colorCombMCPbPb6080           = kBlue+3;

   Style_t  markerStylePbPb0005  = 20 ;
   Style_t  markerStylePbPb0010  = 20 ;
   Style_t  markerStylePbPb0510  = 21 ;
   Style_t  markerStylePbPb1020  = 29 ;
   Style_t  markerStylePbPb2040  = 33 ;
   Style_t  markerStylePbPb4060  = 20 ;
   Style_t  markerStylePbPb6080  = 21 ;

   Style_t  markerStylePbPb0005MC   = 24 ;
   Style_t  markerStylePbPb0010MC   = 24 ;
   Style_t  markerStylePbPb0510MC   = 25 ;
   Style_t  markerStylePbPb1020MC   = 30 ;
   Style_t  markerStylePbPb2040MC   = 27 ;
   Style_t  markerStylePbPb4060MC   = 24 ;
   Style_t  markerStylePbPb6080MC   = 25 ;
   
   Size_t   markerSizePbPb0005   = 2.;
   Size_t   markerSizePbPb0010   = 2.;
   Size_t   markerSizePbPb0510   = 2.;
   Size_t   markerSizePbPb1020   = 2.5;
   Size_t   markerSizePbPb2040   = 2.5;
   Size_t   markerSizePbPb4060   = 2.;
   Size_t   markerSizePbPb6080   = 2.;
    
   TString collisionSystemPbPb0005 = "0-5% Pb-Pb #sqrt{#it{s}_{_{NN}}} = 2.76 TeV";      
   TString collisionSystemPbPb0510 = "5-10% Pb-Pb #sqrt{#it{s}_{_{NN}}} = 2.76 TeV";     
   TString collisionSystemPbPb1020 = "10-20% Pb-Pb #sqrt{#it{s}_{_{NN}}} = 2.76 TeV";    
   TString collisionSystemPbPb0010 = "0-10% Pb-Pb #sqrt{#it{s}_{_{NN}}} = 2.76 TeV";     
   TString collisionSystemPbPb2040 = "20-40% Pb-Pb #sqrt{#it{s}_{_{NN}}} = 2.76 TeV";    
   TString collisionSystemPbPb4060 = "40-60% Pb-Pb #sqrt{#it{s}_{_{NN}}} = 2.76 TeV";    
   TString collisionSystemPbPb6080 = "60-80% Pb-Pb #sqrt{#it{s}_{_{NN}}} = 2.76 TeV";    
   TString collisionSystemPbPb0020 = "0-20% Pb-Pb #sqrt{#it{s}_{_{NN}}} = 2.76 TeV";     
   TString collisionSystemPbPb0080 = "0-80% Pb-Pb #sqrt{#it{s}_{_{NN}}} = 2.76 TeV";     
   TString collisionSystemPbPb0040 = "0-40% Pb-Pb #sqrt{#it{s}_{_{NN}}} = 2.76 TeV";     
   TString collisionSystemPbPb4080 = "40-80% Pb-Pb #sqrt{#it{s}_{_{NN}}} = 2.76 TeV";     
    
   
   //**************************************************************************************************************************
   //**************************************** Read files before weighting *****************************************************
   //**************************************************************************************************************************
   TFile*   filePCMPbPb0thIteration =              new TFile("/home/fredi/Photon/Results/PbPbTests/data_PCMResults_PbPb_2.76TeV_0thIterationRerun.root");
   cout << "0-5%" << endl;
   TDirectory* directory0thIterationPi0PbPb0005 =  (TDirectory*)filePCMPbPb0thIteration->Get("Pi0_PbPb_2.76TeV_0-5%");   
   TH1D* histo0thIterationTrueEffiPt0005 =        (TH1D*)directory0thIterationPi0PbPb0005->Get("Pi0_Efficiency");
   TH1D* histo0thIterationTrueEffiPtFit0005 =     (TH1D*)directory0thIterationPi0PbPb0005->Get("Pi0_EfficiencyFitted");

   cout << "0-10%" << endl;
   TDirectory* directory0thIterationPi0PbPb0010 =           (TDirectory*)filePCMPbPb0thIteration->Get("Pi0_PbPb_2.76TeV_0-10%"); 
   TH1D* histo0thIterationTrueEffiPt0010 =        (TH1D*)directory0thIterationPi0PbPb0010->Get("Pi0_Efficiency");
   TH1D* histo0thIterationTrueEffiPtFit0010 =     (TH1D*)directory0thIterationPi0PbPb0010->Get("Pi0_EfficiencyFitted");
   
   cout << "5-10%" << endl;
   TDirectory* directory0thIterationPi0PbPb0510 =           (TDirectory*)filePCMPbPb0thIteration->Get("Pi0_PbPb_2.76TeV_5-10%"); 
   TH1D* histo0thIterationTrueEffiPt0510 =        (TH1D*)directory0thIterationPi0PbPb0510->Get("Pi0_Efficiency");
   TH1D* histo0thIterationTrueEffiPtFit0510 =     (TH1D*)directory0thIterationPi0PbPb0510->Get("Pi0_EfficiencyFitted");
   
   cout << "10-20%" << endl;
   TDirectory* directory0thIterationPi0PbPb1020 =           (TDirectory*)filePCMPbPb0thIteration->Get("Pi0_PbPb_2.76TeV_10-20%"); 
   TH1D* histo0thIterationTrueEffiPt1020 =        (TH1D*)directory0thIterationPi0PbPb1020->Get("Pi0_Efficiency");
   TH1D* histo0thIterationTrueEffiPtFit1020 =     (TH1D*)directory0thIterationPi0PbPb1020->Get("Pi0_EfficiencyFitted");
   
   cout << "20-40%" << endl;
   TDirectory* directory0thIterationPi0PbPb2040 =           (TDirectory*)filePCMPbPb0thIteration->Get("Pi0_PbPb_2.76TeV_20-40%"); 
   TH1D* histo0thIterationTrueEffiPt2040 =        (TH1D*)directory0thIterationPi0PbPb2040->Get("Pi0_Efficiency");
   TH1D* histo0thIterationTrueEffiPtFit2040 =     (TH1D*)directory0thIterationPi0PbPb2040->Get("Pi0_EfficiencyFitted");
   
   cout << "40-60%" << endl;
   TDirectory* directory0thIterationPi0PbPb4060 =           (TDirectory*)filePCMPbPb0thIteration->Get("Pi0_PbPb_2.76TeV_40-60%"); 
   TH1D* histo0thIterationTrueEffiPt4060 =        (TH1D*)directory0thIterationPi0PbPb4060->Get("Pi0_Efficiency");
   TH1D* histo0thIterationTrueEffiPtFit4060 =     (TH1D*)directory0thIterationPi0PbPb4060->Get("Pi0_EfficiencyFitted");
   
   cout << "60-80%" << endl;
   TDirectory* directory0thIterationPi0PbPb6080 =           (TDirectory*)filePCMPbPb0thIteration->Get("Pi0_PbPb_2.76TeV_60-80%");
   TH1D* histo0thIterationTrueEffiPt6080 =        (TH1D*)directory0thIterationPi0PbPb6080->Get("Pi0_Efficiency");
   TH1D* histo0thIterationTrueEffiPtFit6080 =     (TH1D*)directory0thIterationPi0PbPb6080->Get("Pi0_EfficiencyFitted");

   TFile*   filePCMPbPb0thIterationNewMC =              new TFile("/home/fredi/Photon/Results/PbPbNewMCTest/0thIteration/data_PCMResults_PbPb_2.76TeV_TPCMultNewMCWeighted0thIteration.root");
   cout << "0-5%" << endl;
   TDirectory* directory0thIterationNewMCPi0PbPb0005 =  (TDirectory*)filePCMPbPb0thIterationNewMC->Get("Pi0_PbPb_2.76TeV_0-5%");   
   TH1D* histo0thIterationNewMCTrueEffiPt0005 =        (TH1D*)directory0thIterationNewMCPi0PbPb0005->Get("Pi0_Efficiency");

   cout << "0-10%" << endl;
   TDirectory* directory0thIterationNewMCPi0PbPb0010 =           (TDirectory*)filePCMPbPb0thIterationNewMC->Get("Pi0_PbPb_2.76TeV_0-10%"); 
   TH1D* histo0thIterationNewMCTrueEffiPt0010 =        (TH1D*)directory0thIterationNewMCPi0PbPb0010->Get("Pi0_Efficiency");
   
   cout << "5-10%" << endl;
   TDirectory* directory0thIterationNewMCPi0PbPb0510 =           (TDirectory*)filePCMPbPb0thIterationNewMC->Get("Pi0_PbPb_2.76TeV_5-10%"); 
   TH1D* histo0thIterationNewMCTrueEffiPt0510 =        (TH1D*)directory0thIterationNewMCPi0PbPb0510->Get("Pi0_Efficiency");
   
   cout << "10-20%" << endl;
   TDirectory* directory0thIterationNewMCPi0PbPb1020 =           (TDirectory*)filePCMPbPb0thIterationNewMC->Get("Pi0_PbPb_2.76TeV_10-20%"); 
   TH1D* histo0thIterationNewMCTrueEffiPt1020 =        (TH1D*)directory0thIterationNewMCPi0PbPb1020->Get("Pi0_Efficiency");
   
   cout << "20-40%" << endl;
   TDirectory* directory0thIterationNewMCPi0PbPb2040 =           (TDirectory*)filePCMPbPb0thIterationNewMC->Get("Pi0_PbPb_2.76TeV_20-40%"); 
   TH1D* histo0thIterationNewMCTrueEffiPt2040 =        (TH1D*)directory0thIterationNewMCPi0PbPb2040->Get("Pi0_Efficiency");
   
   cout << "40-60%" << endl;
   TDirectory* directory0thIterationNewMCPi0PbPb4060 =           (TDirectory*)filePCMPbPb0thIterationNewMC->Get("Pi0_PbPb_2.76TeV_40-60%"); 
   TH1D* histo0thIterationNewMCTrueEffiPt4060 =        (TH1D*)directory0thIterationNewMCPi0PbPb4060->Get("Pi0_Efficiency");
   
   cout << "60-80%" << endl;
   TDirectory* directory0thIterationNewMCPi0PbPb6080 =           (TDirectory*)filePCMPbPb0thIterationNewMC->Get("Pi0_PbPb_2.76TeV_60-80%");
   TH1D* histo0thIterationNewMCTrueEffiPt6080 =        (TH1D*)directory0thIterationNewMCPi0PbPb6080->Get("Pi0_Efficiency");
  

   
   //**************************************************************************************************************************
   //**************************************** Read files after weighting *****************************************************
   //**************************************************************************************************************************
   
   TFile*   filePCMPbPb2ndIteration =              new TFile("/home/fredi/Photon/Results/PbPbNewMCTest/data_PCMResults_PbPb_2.76TeV_TPCMultNewMCWeighted2ndIteration.root");
   cout << "0-5%" << endl;
   TDirectory* directory2ndIterationPi0PbPb0005 =  (TDirectory*)filePCMPbPb2ndIteration->Get("Pi0_PbPb_2.76TeV_0-5%");   
   TH1D* histo2ndIterationTrueEffiPt0005 =        (TH1D*)directory2ndIterationPi0PbPb0005->Get("Pi0_Efficiency");
   TH1D* histoPi02ndIterationWeights0005 = (TH1D*)directory2ndIterationPi0PbPb0005->Get("Pi0_HIJING_Weights");
   
   cout << "0-10%" << endl;
   TDirectory* directory2ndIterationPi0PbPb0010 =           (TDirectory*)filePCMPbPb2ndIteration->Get("Pi0_PbPb_2.76TeV_0-10%"); 
   TH1D* histo2ndIterationTrueEffiPt0010 =        (TH1D*)directory2ndIterationPi0PbPb0010->Get("Pi0_Efficiency");
   TH1D* histoPi02ndIterationWeights0010 = (TH1D*)directory2ndIterationPi0PbPb0010->Get("Pi0_HIJING_Weights");
   
   cout << "5-10%" << endl;
   TDirectory* directory2ndIterationPi0PbPb0510 =           (TDirectory*)filePCMPbPb2ndIteration->Get("Pi0_PbPb_2.76TeV_5-10%"); 
   TH1D* histo2ndIterationTrueEffiPt0510 =        (TH1D*)directory2ndIterationPi0PbPb0510->Get("Pi0_Efficiency");
   TH1D* histoPi02ndIterationWeights0510 = (TH1D*)directory2ndIterationPi0PbPb0510->Get("Pi0_HIJING_Weights");
   cout << "10-20%" << endl;
   TDirectory* directory2ndIterationPi0PbPb1020 =           (TDirectory*)filePCMPbPb2ndIteration->Get("Pi0_PbPb_2.76TeV_10-20%"); 
   TH1D* histo2ndIterationTrueEffiPt1020 =        (TH1D*)directory2ndIterationPi0PbPb1020->Get("Pi0_Efficiency");
   TH1D* histoPi02ndIterationWeights1020 = (TH1D*)directory2ndIterationPi0PbPb1020->Get("Pi0_HIJING_Weights");
   cout << "20-40%" << endl;
   TDirectory* directory2ndIterationPi0PbPb2040 =           (TDirectory*)filePCMPbPb2ndIteration->Get("Pi0_PbPb_2.76TeV_20-40%"); 
   TH1D* histo2ndIterationTrueEffiPt2040 =        (TH1D*)directory2ndIterationPi0PbPb2040->Get("Pi0_Efficiency");
   TH1D* histoPi02ndIterationWeights2040 = (TH1D*)directory2ndIterationPi0PbPb2040->Get("Pi0_HIJING_Weights");
   cout << "40-60%" << endl;
   TDirectory* directory2ndIterationPi0PbPb4060 =           (TDirectory*)filePCMPbPb2ndIteration->Get("Pi0_PbPb_2.76TeV_40-60%"); 
   TH1D* histo2ndIterationTrueEffiPt4060 =        (TH1D*)directory2ndIterationPi0PbPb4060->Get("Pi0_Efficiency");
   TH1D* histoPi02ndIterationWeights4060 = (TH1D*)directory2ndIterationPi0PbPb4060->Get("Pi0_HIJING_Weights");
   cout << "60-80%" << endl;
   TDirectory* directory2ndIterationPi0PbPb6080 =           (TDirectory*)filePCMPbPb2ndIteration->Get("Pi0_PbPb_2.76TeV_60-80%");
   TH1D* histo2ndIterationTrueEffiPt6080 =        (TH1D*)directory2ndIterationPi0PbPb6080->Get("Pi0_Efficiency");
   TH1D* histoPi02ndIterationWeights6080 = (TH1D*)directory2ndIterationPi0PbPb6080->Get("Pi0_HIJING_Weights");
   
   TFile*   filePCMPbPb2ndIterationAddSig0005 =              new TFile("601000104209297002322000000_01522045009000/PbPb_2.76TeV/Pi0_MC_GammaConvV1CorrectionHistosAddSig_601000104209297002322000000_01522045009000.root");
   TH1D* histoPi02ndIterationWeightsAddSig0005 = (TH1D*)filePCMPbPb2ndIterationAddSig0005->Get("MC_Meson_genPt_Weights");
   TFile*   filePCMPbPb2ndIterationAddSig0510 =              new TFile("612000104209297002322000000_01522045009000/PbPb_2.76TeV/Pi0_MC_GammaConvV1CorrectionHistosAddSig_612000104209297002322000000_01522045009000.root");
   TH1D* histoPi02ndIterationWeightsAddSig0510 = (TH1D*)filePCMPbPb2ndIterationAddSig0510->Get("MC_Meson_genPt_Weights");
   TFile*   filePCMPbPb2ndIterationAddSig1020 =              new TFile("512000104209297002322000000_01522045009000/PbPb_2.76TeV/Pi0_MC_GammaConvV1CorrectionHistosAddSig_512000104209297002322000000_01522045009000.root");
   TH1D* histoPi02ndIterationWeightsAddSig1020 = (TH1D*)filePCMPbPb2ndIterationAddSig1020->Get("MC_Meson_genPt_Weights");
   TFile*   filePCMPbPb2ndIterationAddSig2040 =              new TFile("524000104209297002322000000_01522045009000/PbPb_2.76TeV/Pi0_MC_GammaConvV1CorrectionHistosAddSig_524000104209297002322000000_01522045009000.root");
   TH1D* histoPi02ndIterationWeightsAddSig2040 = (TH1D*)filePCMPbPb2ndIterationAddSig2040->Get("MC_Meson_genPt_Weights");
   TFile*   filePCMPbPb2ndIterationAddSig4060 =              new TFile("546000104209297002322000000_01522065009000/PbPb_2.76TeV/Pi0_MC_GammaConvV1CorrectionHistosAddSig_546000104209297002322000000_01522065009000.root");
   TH1D* histoPi02ndIterationWeightsAddSig4060 = (TH1D*)filePCMPbPb2ndIterationAddSig4060->Get("MC_Meson_genPt_Weights");
   TFile*   filePCMPbPb2ndIterationAddSig6080 =              new TFile("568000104209297002322000000_01522065009000/PbPb_2.76TeV/Pi0_MC_GammaConvV1CorrectionHistosAddSig_568000104209297002322000000_01522065009000.root");
   TH1D* histoPi02ndIterationWeightsAddSig6080 = (TH1D*)filePCMPbPb2ndIterationAddSig6080->Get("MC_Meson_genPt_Weights");
   
      
   TCanvas* canvasFraction2 = new TCanvas("canvasFraction2","",1550,1200);  // gives the page size
   canvasFraction2->SetTickx();
   canvasFraction2->SetTicky();
   canvasFraction2->SetGridx(0);
   canvasFraction2->SetGridy(0);
   canvasFraction2->SetLogy(0);
   canvasFraction2->SetLeftMargin(0.13);
   canvasFraction2->SetRightMargin(0.02);
   canvasFraction2->SetTopMargin(0.02);
   canvasFraction2->SetFillColor(0);
   canvasFraction2->cd();
   
   TH1D* histoRatioEffi2ndIteDiv0thIte0005= (TH1D*)histo2ndIterationTrueEffiPt0005->Clone("histoRatioEffi2ndIteDiv0thIte0005");
   histoRatioEffi2ndIteDiv0thIte0005->Divide(histo2ndIterationTrueEffiPt0005, histo0thIterationNewMCTrueEffiPt0005, 1. ,1., "");
   TH1D* histoRatioEffi2ndIteDiv0thIte0510= (TH1D*)histo2ndIterationTrueEffiPt0510->Clone("histoRatioEffi2ndIteDiv0thIte0510");
   histoRatioEffi2ndIteDiv0thIte0510->Divide(histo2ndIterationTrueEffiPt0510, histo0thIterationNewMCTrueEffiPt0510, 1. ,1., "");
   TH1D* histoRatioEffi2ndIteDiv0thIte1020= (TH1D*)histo2ndIterationTrueEffiPt1020->Clone("histoRatioEffi2ndIteDiv0thIte1020");
   histoRatioEffi2ndIteDiv0thIte1020->Divide(histo2ndIterationTrueEffiPt1020, histo0thIterationNewMCTrueEffiPt1020, 1. ,1., "");
   TH1D* histoRatioEffi2ndIteDiv0thIte2040= (TH1D*)histo2ndIterationTrueEffiPt2040->Clone("histoRatioEffi2ndIteDiv0thIte2040");
   histoRatioEffi2ndIteDiv0thIte2040->Divide(histo2ndIterationTrueEffiPt2040, histo0thIterationNewMCTrueEffiPt2040, 1. ,1., "");
   TH1D* histoRatioEffi2ndIteDiv0thIte4060= (TH1D*)histo2ndIterationTrueEffiPt4060->Clone("histoRatioEffi2ndIteDiv0thIte4060");
   histoRatioEffi2ndIteDiv0thIte4060->Divide(histo2ndIterationTrueEffiPt4060, histo0thIterationNewMCTrueEffiPt4060, 1. ,1., "");
   TH1D* histoRatioEffi2ndIteDiv0thIte6080= (TH1D*)histo2ndIterationTrueEffiPt6080->Clone("histoRatioEffi2ndIteDiv0thIte6080");
   histoRatioEffi2ndIteDiv0thIte6080->Divide(histo2ndIterationTrueEffiPt6080, histo0thIterationNewMCTrueEffiPt6080, 1. ,1., "");
 
   
   canvasFraction2->cd();
   if (histoRatioEffi2ndIteDiv0thIte6080) DrawGammaSetMarker(histoRatioEffi2ndIteDiv0thIte6080, markerStylePbPb6080MC,markerSizePbPb6080, colorCombPbPb6080 , colorCombPbPb6080 );
   if (histoRatioEffi2ndIteDiv0thIte0005) DrawGammaSetMarker(histoRatioEffi2ndIteDiv0thIte0005, markerStylePbPb0005MC,markerSizePbPb0005, colorCombPbPb0005 , colorCombPbPb0005 );
   if (histoRatioEffi2ndIteDiv0thIte0510) DrawGammaSetMarker(histoRatioEffi2ndIteDiv0thIte0510, markerStylePbPb0510MC,markerSizePbPb0510, colorCombPbPb0510 , colorCombPbPb0510 );
   if (histoRatioEffi2ndIteDiv0thIte1020) DrawGammaSetMarker(histoRatioEffi2ndIteDiv0thIte1020, markerStylePbPb1020MC,markerSizePbPb1020, colorCombPbPb1020 , colorCombPbPb1020 );
   if (histoRatioEffi2ndIteDiv0thIte2040) DrawGammaSetMarker(histoRatioEffi2ndIteDiv0thIte2040, markerStylePbPb2040MC,markerSizePbPb2040, colorCombPbPb2040 , colorCombPbPb2040 );
   if (histoRatioEffi2ndIteDiv0thIte4060) DrawGammaSetMarker(histoRatioEffi2ndIteDiv0thIte4060, markerStylePbPb4060MC,markerSizePbPb4060, colorCombPbPb4060 , colorCombPbPb4060 );
   DrawAutoGammaMesonHistos( histoRatioEffi2ndIteDiv0thIte6080,
               "", "p_{T} (GeV/c)", "Effi 2nd Iteration of weighting/ no weighting, New MC",
               kFALSE, 1.5, 0, kTRUE,
               kTRUE, 0.5, 1.5,
               kTRUE, 0., 7.9);
   if (histoRatioEffi2ndIteDiv0thIte0005)histoRatioEffi2ndIteDiv0thIte0005->Draw("same,e,p");
//    if (histoRatioEffi2ndIteDiv0thIte0510)histoRatioEffi2ndIteDiv0thIte0510->Draw("same,e,p");  
   if (histoRatioEffi2ndIteDiv0thIte1020)histoRatioEffi2ndIteDiv0thIte1020->Draw("same,e,p");  
//    if (histoRatioEffi2ndIteDiv0thIte2040)histoRatioEffi2ndIteDiv0thIte2040->Draw("same,e,p");  
//    if (histoRatioEffi2ndIteDiv0thIte4060)histoRatioEffi2ndIteDiv0thIte4060->Draw("same,e,p");  
   
   TLegend* legendCompEffiDifferentWeighting = new TLegend(0.16,0.11,0.4,0.3);
   legendCompEffiDifferentWeighting->SetFillColor(0);
   legendCompEffiDifferentWeighting->SetLineColor(0);
   legendCompEffiDifferentWeighting->SetTextSize(0.025);
//    legendCompEffiDifferentWeighting->SetNColumns(3);
   legendCompEffiDifferentWeighting->SetMargin(0.2);
   if (histoRatioEffi2ndIteDiv0thIte0005)legendCompEffiDifferentWeighting->AddEntry(histoRatioEffi2ndIteDiv0thIte0005,Form("%s",collisionSystemPbPb0005.Data()),"p");
//    if (histoRatioEffi2ndIteDiv0thIte0510)legendCompEffiDifferentWeighting->AddEntry(histoRatioEffi2ndIteDiv0thIte0510,Form("%s",collisionSystemPbPb0510.Data()),"p");
   if (histoRatioEffi2ndIteDiv0thIte1020)legendCompEffiDifferentWeighting->AddEntry(histoRatioEffi2ndIteDiv0thIte1020,Form("%s",collisionSystemPbPb1020.Data()),"p");
//    if (histoRatioEffi2ndIteDiv0thIte2040)legendCompEffiDifferentWeighting->AddEntry(histoRatioEffi2ndIteDiv0thIte2040,Form("%s",collisionSystemPbPb2040.Data()),"p");
//    if (histoRatioEffi2ndIteDiv0thIte4060)legendCompEffiDifferentWeighting->AddEntry(histoRatioEffi2ndIteDiv0thIte4060,Form("%s",collisionSystemPbPb4060.Data()),"p");
   if (histoRatioEffi2ndIteDiv0thIte6080)legendCompEffiDifferentWeighting->AddEntry(histoRatioEffi2ndIteDiv0thIte6080,Form("%s",collisionSystemPbPb6080.Data()),"p");
   legendCompEffiDifferentWeighting->Draw();
   
   DrawGammaLines(0., 30.,1., 1.,0.1);
   canvasFraction2->Update();
   canvasFraction2->SaveAs(Form("RatioEffiFinalWeightsDivNoWeights.%s",suffix.Data()));

   TH1D* histoRatioEffiNewMCDivOldMC0005= (TH1D*)histo0thIterationNewMCTrueEffiPt0005->Clone("histoRatioEffiNewMCDivOldMC0005");
   histoRatioEffiNewMCDivOldMC0005->Divide(histo0thIterationNewMCTrueEffiPt0005, histo0thIterationTrueEffiPt0005, 1. ,1., "");
   TH1D* histoRatioEffiNewMCDivOldMC0510= (TH1D*)histo0thIterationNewMCTrueEffiPt0510->Clone("histoRatioEffiNewMCDivOldMC0510");
   histoRatioEffiNewMCDivOldMC0510->Divide(histo0thIterationNewMCTrueEffiPt0510, histo0thIterationTrueEffiPt0510, 1. ,1., "");
   TH1D* histoRatioEffiNewMCDivOldMC1020= (TH1D*)histo0thIterationNewMCTrueEffiPt1020->Clone("histoRatioEffiNewMCDivOldMC1020");
   histoRatioEffiNewMCDivOldMC1020->Divide(histo0thIterationNewMCTrueEffiPt1020, histo0thIterationTrueEffiPt1020, 1. ,1., "");
   TH1D* histoRatioEffiNewMCDivOldMC2040= (TH1D*)histo0thIterationNewMCTrueEffiPt2040->Clone("histoRatioEffiNewMCDivOldMC2040");
   histoRatioEffiNewMCDivOldMC2040->Divide(histo0thIterationNewMCTrueEffiPt2040, histo0thIterationTrueEffiPt2040, 1. ,1., "");
   TH1D* histoRatioEffiNewMCDivOldMC4060= (TH1D*)histo0thIterationNewMCTrueEffiPt4060->Clone("histoRatioEffiNewMCDivOldMC4060");
   histoRatioEffiNewMCDivOldMC4060->Divide(histo0thIterationNewMCTrueEffiPt4060, histo0thIterationTrueEffiPt4060, 1. ,1., "");
   TH1D* histoRatioEffiNewMCDivOldMC6080= (TH1D*)histo0thIterationNewMCTrueEffiPt6080->Clone("histoRatioEffiNewMCDivOldMC6080");
   histoRatioEffiNewMCDivOldMC6080->Divide(histo0thIterationNewMCTrueEffiPt6080, histo0thIterationTrueEffiPt6080, 1. ,1., "");
 
   
   canvasFraction2->cd();
   if (histoRatioEffiNewMCDivOldMC6080) DrawGammaSetMarker(histoRatioEffiNewMCDivOldMC6080, markerStylePbPb6080MC,markerSizePbPb6080, colorCombPbPb6080 , colorCombPbPb6080 );
   if (histoRatioEffiNewMCDivOldMC0005) DrawGammaSetMarker(histoRatioEffiNewMCDivOldMC0005, markerStylePbPb0005MC,markerSizePbPb0005, colorCombPbPb0005 , colorCombPbPb0005 );
   if (histoRatioEffiNewMCDivOldMC0510) DrawGammaSetMarker(histoRatioEffiNewMCDivOldMC0510, markerStylePbPb0510MC,markerSizePbPb0510, colorCombPbPb0510 , colorCombPbPb0510 );
   if (histoRatioEffiNewMCDivOldMC1020) DrawGammaSetMarker(histoRatioEffiNewMCDivOldMC1020, markerStylePbPb1020MC,markerSizePbPb1020, colorCombPbPb1020 , colorCombPbPb1020 );
   if (histoRatioEffiNewMCDivOldMC2040) DrawGammaSetMarker(histoRatioEffiNewMCDivOldMC2040, markerStylePbPb2040MC,markerSizePbPb2040, colorCombPbPb2040 , colorCombPbPb2040 );
   if (histoRatioEffiNewMCDivOldMC4060) DrawGammaSetMarker(histoRatioEffiNewMCDivOldMC4060, markerStylePbPb4060MC,markerSizePbPb4060, colorCombPbPb4060 , colorCombPbPb4060 );
   DrawAutoGammaMesonHistos( histoRatioEffiNewMCDivOldMC6080,
               "", "p_{T} (GeV/c)", "Effi New MC/ Old MC, wo weighting",
               kFALSE, 1.5, 0, kTRUE,
               kTRUE, 0.5, 1.5,
               kTRUE, 0., 7.9);
   if (histoRatioEffiNewMCDivOldMC0005)histoRatioEffiNewMCDivOldMC0005->Draw("same,e,p");
//    if (histoRatioEffiNewMCDivOldMC0510)histoRatioEffiNewMCDivOldMC0510->Draw("same,e,p");  
   if (histoRatioEffiNewMCDivOldMC1020)histoRatioEffiNewMCDivOldMC1020->Draw("same,e,p");  
//    if (histoRatioEffiNewMCDivOldMC2040)histoRatioEffiNewMCDivOldMC2040->Draw("same,e,p");  
//    if (histoRatioEffiNewMCDivOldMC4060)histoRatioEffiNewMCDivOldMC4060->Draw("same,e,p");  
   
   TLegend* legendCompEffiDifferentMC = new TLegend(0.16,0.11,0.4,0.3);
   legendCompEffiDifferentMC->SetFillColor(0);
   legendCompEffiDifferentMC->SetLineColor(0);
   legendCompEffiDifferentMC->SetTextSize(0.025);
//    legendCompEffiDifferentMC->SetNColumns(3);
   legendCompEffiDifferentMC->SetMargin(0.2);
   if (histoRatioEffiNewMCDivOldMC0005)legendCompEffiDifferentMC->AddEntry(histoRatioEffiNewMCDivOldMC0005,Form("%s",collisionSystemPbPb0005.Data()),"p");
//    if (histoRatioEffiNewMCDivOldMC0510)legendCompEffiDifferentMC->AddEntry(histoRatioEffiNewMCDivOldMC0510,Form("%s",collisionSystemPbPb0510.Data()),"p");
   if (histoRatioEffiNewMCDivOldMC1020)legendCompEffiDifferentMC->AddEntry(histoRatioEffiNewMCDivOldMC1020,Form("%s",collisionSystemPbPb1020.Data()),"p");
//    if (histoRatioEffiNewMCDivOldMC2040)legendCompEffiDifferentMC->AddEntry(histoRatioEffiNewMCDivOldMC2040,Form("%s",collisionSystemPbPb2040.Data()),"p");
//    if (histoRatioEffiNewMCDivOldMC4060)legendCompEffiDifferentMC->AddEntry(histoRatioEffiNewMCDivOldMC4060,Form("%s",collisionSystemPbPb4060.Data()),"p");
   if (histoRatioEffiNewMCDivOldMC6080)legendCompEffiDifferentMC->AddEntry(histoRatioEffiNewMCDivOldMC6080,Form("%s",collisionSystemPbPb6080.Data()),"p");
   legendCompEffiDifferentMC->Draw();
   
   DrawGammaLines(0., 30.,1., 1.,0.1);
   canvasFraction2->Update();
   canvasFraction2->SaveAs(Form("RatioEffiNewDivOldMC.%s",suffix.Data()));

   
//    TH1D* histoRatioNewDivOld0005= (TH1D*)histo2ndIterationTrueEffiPt0005->Clone("histoRatioNewDivOld0005");
//    histoRatioNewDivOld0005->Divide(histo2ndIterationTrueEffiPt0005, histo0thIterationTrueEffiPtFit0005, 1. ,1., "B");
//    TH1D* histoRatioNewDivOld0510= (TH1D*)histo2ndIterationTrueEffiPt0510->Clone("histoRatioNewDivOld0510");
//    histoRatioNewDivOld0510->Divide(histo2ndIterationTrueEffiPt0510, histo0thIterationTrueEffiPtFit0510, 1. ,1., "B");
//    TH1D* histoRatioNewDivOld1020= (TH1D*)histo2ndIterationTrueEffiPt1020->Clone("histoRatioNewDivOld1020");
//    histoRatioNewDivOld1020->Divide(histo2ndIterationTrueEffiPt1020, histo0thIterationTrueEffiPtFit1020, 1. ,1., "B");
//    TH1D* histoRatioNewDivOld2040= (TH1D*)histo2ndIterationTrueEffiPt2040->Clone("histoRatioNewDivOld2040");
//    histoRatioNewDivOld2040->Divide(histo2ndIterationTrueEffiPt2040, histo0thIterationTrueEffiPtFit2040, 1. ,1., "B");
//    TH1D* histoRatioNewDivOld4060= (TH1D*)histo2ndIterationTrueEffiPt4060->Clone("histoRatioNewDivOld4060");
//    histoRatioNewDivOld4060->Divide(histo2ndIterationTrueEffiPt4060, histo0thIterationTrueEffiPtFit4060, 1. ,1., "B");
//    TH1D* histoRatioNewDivOld6080= (TH1D*)histo2ndIterationTrueEffiPt6080->Clone("histoRatioNewDivOld6080");
//    histoRatioNewDivOld6080->Divide(histo2ndIterationTrueEffiPt6080, histo0thIterationTrueEffiPtFit6080, 1. ,1., "B");
//    
//    
//    canvasFraction2->cd();
//    if (histoRatioNewDivOld6080) DrawGammaSetMarker(histoRatioNewDivOld6080, markerStylePbPb6080MC,markerSizePbPb6080, colorCombPbPb6080 , colorCombPbPb6080 );
//    if (histoRatioNewDivOld0005) DrawGammaSetMarker(histoRatioNewDivOld0005, markerStylePbPb0005MC,markerSizePbPb0005, colorCombPbPb0005 , colorCombPbPb0005 );
//    if (histoRatioNewDivOld0510) DrawGammaSetMarker(histoRatioNewDivOld0510, markerStylePbPb0510MC,markerSizePbPb0510, colorCombPbPb0510 , colorCombPbPb0510 );
//    if (histoRatioNewDivOld1020) DrawGammaSetMarker(histoRatioNewDivOld1020, markerStylePbPb1020MC,markerSizePbPb1020, colorCombPbPb1020 , colorCombPbPb1020 );
//    if (histoRatioNewDivOld2040) DrawGammaSetMarker(histoRatioNewDivOld2040, markerStylePbPb2040MC,markerSizePbPb2040, colorCombPbPb2040 , colorCombPbPb2040 );
//    if (histoRatioNewDivOld4060) DrawGammaSetMarker(histoRatioNewDivOld4060, markerStylePbPb4060MC,markerSizePbPb4060, colorCombPbPb4060 , colorCombPbPb4060 );
//    DrawAutoGammaMesonHistos( histoRatioNewDivOld6080,
//                "", "p_{T} (GeV/c)", "Effi final/ fitted no weighting",
//                kFALSE, 1.5, 0, kTRUE,
//                kTRUE, 0.5, 1.5,
//                kTRUE, 0., 7.9);
//    if (histoRatioNewDivOld0005)histoRatioNewDivOld0005->Draw("same,e,p");
//    if (histoRatioNewDivOld0510)histoRatioNewDivOld0510->Draw("same,e,p");  
//    if (histoRatioNewDivOld1020)histoRatioNewDivOld1020->Draw("same,e,p");  
//    if (histoRatioNewDivOld2040)histoRatioNewDivOld2040->Draw("same,e,p");  
//    if (histoRatioNewDivOld4060)histoRatioNewDivOld4060->Draw("same,e,p");  
//    
//    TLegend* legendCompEffiFinalDivOld = new TLegend(0.16,0.11,0.4,0.3);
//    legendCompEffiFinalDivOld->SetFillColor(0);
//    legendCompEffiFinalDivOld->SetLineColor(0);
//    legendCompEffiFinalDivOld->SetTextSize(0.025);
// //    legendCompEffiFinalDivOld->SetNColumns(3);
//    legendCompEffiFinalDivOld->SetMargin(0.2);
//    if (histoRatioNewDivOld0005)legendCompEffiFinalDivOld->AddEntry(histoRatioNewDivOld0005,Form("%s",collisionSystemPbPb0005.Data()),"p");
//    if (histoRatioNewDivOld0510)legendCompEffiFinalDivOld->AddEntry(histoRatioNewDivOld0510,Form("%s",collisionSystemPbPb0510.Data()),"p");
//    if (histoRatioNewDivOld1020)legendCompEffiFinalDivOld->AddEntry(histoRatioNewDivOld1020,Form("%s",collisionSystemPbPb1020.Data()),"p");
//    if (histoRatioNewDivOld2040)legendCompEffiFinalDivOld->AddEntry(histoRatioNewDivOld2040,Form("%s",collisionSystemPbPb2040.Data()),"p");
//    if (histoRatioNewDivOld4060)legendCompEffiFinalDivOld->AddEntry(histoRatioNewDivOld4060,Form("%s",collisionSystemPbPb4060.Data()),"p");
//    if (histoRatioNewDivOld6080)legendCompEffiFinalDivOld->AddEntry(histoRatioNewDivOld6080,Form("%s",collisionSystemPbPb6080.Data()),"p");
//    legendCompEffiFinalDivOld->Draw();
//    
//    DrawGammaLines(0., 30.,1., 1.,0.1);
//    canvasFraction2->Update();
//    canvasFraction2->SaveAs(Form("RatioEffiFinalDivNoWeightsFitted.%s",suffix.Data()));
   
   canvasFraction2->cd();
   if (histoPi02ndIterationWeights6080) DrawGammaSetMarker(histoPi02ndIterationWeights6080, markerStylePbPb6080MC,markerSizePbPb6080, colorCombPbPb6080 , colorCombPbPb6080 );
   if (histoPi02ndIterationWeights0005) DrawGammaSetMarker(histoPi02ndIterationWeights0005, markerStylePbPb0005MC,markerSizePbPb0005, colorCombPbPb0005 , colorCombPbPb0005 );
   if (histoPi02ndIterationWeights0510) DrawGammaSetMarker(histoPi02ndIterationWeights0510, markerStylePbPb0510MC,markerSizePbPb0510, colorCombPbPb0510 , colorCombPbPb0510 );
   if (histoPi02ndIterationWeights1020) DrawGammaSetMarker(histoPi02ndIterationWeights1020, markerStylePbPb1020MC,markerSizePbPb1020, colorCombPbPb1020 , colorCombPbPb1020 );
   if (histoPi02ndIterationWeights2040) DrawGammaSetMarker(histoPi02ndIterationWeights2040, markerStylePbPb2040MC,markerSizePbPb2040, colorCombPbPb2040 , colorCombPbPb2040 );
   if (histoPi02ndIterationWeights4060) DrawGammaSetMarker(histoPi02ndIterationWeights4060, markerStylePbPb4060MC,markerSizePbPb4060, colorCombPbPb4060 , colorCombPbPb4060 );
   DrawAutoGammaMesonHistos( histoPi02ndIterationWeights6080,
               "", "p_{T} (GeV/c)", "Weights",
               kFALSE, 1.5, 0, kTRUE,
               kTRUE, 0., 3.,
               kTRUE, 0., 7.9);
   if (histoPi02ndIterationWeights0005)histoPi02ndIterationWeights0005->Draw("same,e,p");
   if (histoPi02ndIterationWeights0510)histoPi02ndIterationWeights0510->Draw("same,e,p");  
   if (histoPi02ndIterationWeights1020)histoPi02ndIterationWeights1020->Draw("same,e,p");  
   if (histoPi02ndIterationWeights2040)histoPi02ndIterationWeights2040->Draw("same,e,p");  
   if (histoPi02ndIterationWeights4060)histoPi02ndIterationWeights4060->Draw("same,e,p");  
   
   TLegend* legendWeights = new TLegend(0.56,0.71,0.95,0.95);
   legendWeights->SetFillColor(0);
   legendWeights->SetLineColor(0);
   legendWeights->SetTextSize(0.025);
//    legendWeights->SetNColumns(3);
   legendWeights->SetMargin(0.2);
   if (histoPi02ndIterationWeights0005)legendWeights->AddEntry(histoPi02ndIterationWeights0005,Form("%s",collisionSystemPbPb0005.Data()),"p");
   if (histoPi02ndIterationWeights0510)legendWeights->AddEntry(histoPi02ndIterationWeights0510,Form("%s",collisionSystemPbPb0510.Data()),"p");
   if (histoPi02ndIterationWeights1020)legendWeights->AddEntry(histoPi02ndIterationWeights1020,Form("%s",collisionSystemPbPb1020.Data()),"p");
   if (histoPi02ndIterationWeights2040)legendWeights->AddEntry(histoPi02ndIterationWeights2040,Form("%s",collisionSystemPbPb2040.Data()),"p");
   if (histoPi02ndIterationWeights4060)legendWeights->AddEntry(histoPi02ndIterationWeights4060,Form("%s",collisionSystemPbPb4060.Data()),"p");
   if (histoPi02ndIterationWeights6080)legendWeights->AddEntry(histoPi02ndIterationWeights6080,Form("%s",collisionSystemPbPb6080.Data()),"p");
   legendWeights->Draw();
   
   DrawGammaLines(0., 30.,1., 1.,0.1);
   canvasFraction2->Update();
   canvasFraction2->SaveAs(Form("Weights2ndIteration.%s",suffix.Data()));
   
   canvasFraction2->cd();
   canvasFraction2->SetLogy();
   if (histoPi02ndIterationWeightsAddSig6080) DrawGammaSetMarker(histoPi02ndIterationWeightsAddSig6080, markerStylePbPb6080MC,markerSizePbPb6080, colorCombPbPb6080 , colorCombPbPb6080 );
   if (histoPi02ndIterationWeightsAddSig0005) DrawGammaSetMarker(histoPi02ndIterationWeightsAddSig0005, markerStylePbPb0005MC,markerSizePbPb0005, colorCombPbPb0005 , colorCombPbPb0005 );
   if (histoPi02ndIterationWeightsAddSig0510) DrawGammaSetMarker(histoPi02ndIterationWeightsAddSig0510, markerStylePbPb0510MC,markerSizePbPb0510, colorCombPbPb0510 , colorCombPbPb0510 );
   if (histoPi02ndIterationWeightsAddSig1020) DrawGammaSetMarker(histoPi02ndIterationWeightsAddSig1020, markerStylePbPb1020MC,markerSizePbPb1020, colorCombPbPb1020 , colorCombPbPb1020 );
   if (histoPi02ndIterationWeightsAddSig2040) DrawGammaSetMarker(histoPi02ndIterationWeightsAddSig2040, markerStylePbPb2040MC,markerSizePbPb2040, colorCombPbPb2040 , colorCombPbPb2040 );
   if (histoPi02ndIterationWeightsAddSig4060) DrawGammaSetMarker(histoPi02ndIterationWeightsAddSig4060, markerStylePbPb4060MC,markerSizePbPb4060, colorCombPbPb4060 , colorCombPbPb4060 );
   DrawAutoGammaMesonHistos( histoPi02ndIterationWeightsAddSig6080,
               "", "p_{T} (GeV/c)", "Weights Added Signals",
               kFALSE, 1.5, 0, kTRUE,
               kTRUE, 1e-3, 1e5,
               kTRUE, 0., 7.9);
   if (histoPi02ndIterationWeightsAddSig0005)histoPi02ndIterationWeightsAddSig0005->Draw("same,e,p");
   if (histoPi02ndIterationWeightsAddSig0510)histoPi02ndIterationWeightsAddSig0510->Draw("same,e,p");  
   if (histoPi02ndIterationWeightsAddSig1020)histoPi02ndIterationWeightsAddSig1020->Draw("same,e,p");  
   if (histoPi02ndIterationWeightsAddSig2040)histoPi02ndIterationWeightsAddSig2040->Draw("same,e,p");  
   if (histoPi02ndIterationWeightsAddSig4060)histoPi02ndIterationWeightsAddSig4060->Draw("same,e,p");  
   
   TLegend* legendWeightsAddSig = new TLegend(0.56,0.71,0.95,0.95);
   legendWeightsAddSig->SetFillColor(0);
   legendWeightsAddSig->SetLineColor(0);
   legendWeightsAddSig->SetTextSize(0.025);
//    legendWeights->SetNColumns(3);
   legendWeightsAddSig->SetMargin(0.2);
   if (histoPi02ndIterationWeightsAddSig0005)legendWeightsAddSig->AddEntry(histoPi02ndIterationWeightsAddSig0005,Form("%s",collisionSystemPbPb0005.Data()),"p");
   if (histoPi02ndIterationWeightsAddSig0510)legendWeightsAddSig->AddEntry(histoPi02ndIterationWeightsAddSig0510,Form("%s",collisionSystemPbPb0510.Data()),"p");
   if (histoPi02ndIterationWeightsAddSig1020)legendWeightsAddSig->AddEntry(histoPi02ndIterationWeightsAddSig1020,Form("%s",collisionSystemPbPb1020.Data()),"p");
   if (histoPi02ndIterationWeightsAddSig2040)legendWeightsAddSig->AddEntry(histoPi02ndIterationWeightsAddSig2040,Form("%s",collisionSystemPbPb2040.Data()),"p");
   if (histoPi02ndIterationWeightsAddSig4060)legendWeightsAddSig->AddEntry(histoPi02ndIterationWeightsAddSig4060,Form("%s",collisionSystemPbPb4060.Data()),"p");
   if (histoPi02ndIterationWeightsAddSig6080)legendWeightsAddSig->AddEntry(histoPi02ndIterationWeightsAddSig6080,Form("%s",collisionSystemPbPb6080.Data()),"p");
   legendWeightsAddSig->Draw();
   
   DrawGammaLines(0., 30.,1., 1.,0.1);
   canvasFraction2->Update();
   canvasFraction2->SaveAs(Form("Weights2ndIterationAddSig.%s",suffix.Data()));
   
   
//    TH1D* histoRatio5thDiv2ndIte0005= (TH1D*)histo2ndIterationTrueEffiPt0005->Clone("histoRatio5thDiv2ndIte0005");
//    histoRatio5thDiv2ndIte0005->Divide(histo5thIterationTrueEffiPt0005, histo2ndIterationTrueEffiPtFit0005, 1. ,1., "B");
//    TH1D* histoRatio5thDiv2ndIte0510= (TH1D*)histo2ndIterationTrueEffiPt0510->Clone("histoRatio5thDiv2ndIte0510");
//    histoRatio5thDiv2ndIte0510->Divide(histo5thIterationTrueEffiPt0510, histo2ndIterationTrueEffiPtFit0510, 1. ,1., "B");
//    TH1D* histoRatio5thDiv2ndIte1020= (TH1D*)histo2ndIterationTrueEffiPt1020->Clone("histoRatio5thDiv2ndIte1020");
//    histoRatio5thDiv2ndIte1020->Divide(histo5thIterationTrueEffiPt1020, histo2ndIterationTrueEffiPtFit1020, 1. ,1., "B");
//    TH1D* histoRatio5thDiv2ndIte2040= (TH1D*)histo2ndIterationTrueEffiPt2040->Clone("histoRatio5thDiv2ndIte2040");
//    histoRatio5thDiv2ndIte2040->Divide(histo5thIterationTrueEffiPt2040, histo2ndIterationTrueEffiPtFit2040, 1. ,1., "B");
//    TH1D* histoRatio5thDiv2ndIte4060= (TH1D*)histo2ndIterationTrueEffiPt4060->Clone("histoRatio5thDiv2ndIte4060");
//    histoRatio5thDiv2ndIte4060->Divide(histo5thIterationTrueEffiPt4060, histo2ndIterationTrueEffiPtFit4060, 1. ,1., "B");
//    TH1D* histoRatio5thDiv2ndIte6080= (TH1D*)histo2ndIterationTrueEffiPt6080->Clone("histoRatio5thDiv2ndIte6080");
//    histoRatio5thDiv2ndIte6080->Divide(histo5thIterationTrueEffiPt6080, histo2ndIterationTrueEffiPtFit6080, 1. ,1., "B");
//    
//    
//    canvasFraction2->cd();
//    if (histoRatio5thDiv2ndIte6080) DrawGammaSetMarker(histoRatio5thDiv2ndIte6080, markerStylePbPb6080MC,markerSizePbPb6080, colorCombPbPb6080 , colorCombPbPb6080 );
//    if (histoRatio5thDiv2ndIte0005) DrawGammaSetMarker(histoRatio5thDiv2ndIte0005, markerStylePbPb0005MC,markerSizePbPb0005, colorCombPbPb0005 , colorCombPbPb0005 );
//    if (histoRatio5thDiv2ndIte0510) DrawGammaSetMarker(histoRatio5thDiv2ndIte0510, markerStylePbPb0510MC,markerSizePbPb0510, colorCombPbPb0510 , colorCombPbPb0510 );
//    if (histoRatio5thDiv2ndIte1020) DrawGammaSetMarker(histoRatio5thDiv2ndIte1020, markerStylePbPb1020MC,markerSizePbPb1020, colorCombPbPb1020 , colorCombPbPb1020 );
//    if (histoRatio5thDiv2ndIte2040) DrawGammaSetMarker(histoRatio5thDiv2ndIte2040, markerStylePbPb2040MC,markerSizePbPb2040, colorCombPbPb2040 , colorCombPbPb2040 );
//    if (histoRatio5thDiv2ndIte4060) DrawGammaSetMarker(histoRatio5thDiv2ndIte4060, markerStylePbPb4060MC,markerSizePbPb4060, colorCombPbPb4060 , colorCombPbPb4060 );
//    DrawAutoGammaMesonHistos( histoRatio5thDiv2ndIte6080,
//                "", "p_{T} (GeV/c)", "possible additional systematic error",
//                kFALSE, 1.5, 0, kTRUE,
//                kTRUE, 0.5, 1.5,
//                kTRUE, 0., 7.9);
//    if (histoRatio5thDiv2ndIte0005)histoRatio5thDiv2ndIte0005->Draw("same,e,p");
//    if (histoRatio5thDiv2ndIte0510)histoRatio5thDiv2ndIte0510->Draw("same,e,p");  
//    if (histoRatio5thDiv2ndIte1020)histoRatio5thDiv2ndIte1020->Draw("same,e,p");  
//    if (histoRatio5thDiv2ndIte2040)histoRatio5thDiv2ndIte2040->Draw("same,e,p");  
//    if (histoRatio5thDiv2ndIte4060)histoRatio5thDiv2ndIte4060->Draw("same,e,p");  
//    
//    TLegend* legendPossAddSyst = new TLegend(0.16,0.11,0.4,0.3);
//    legendPossAddSyst->SetFillColor(0);
//    legendPossAddSyst->SetLineColor(0);
//    legendPossAddSyst->SetTextSize(0.025);
// //    legendPossAddSyst->SetNColumns(3);
//    legendPossAddSyst->SetMargin(0.2);
//    if (histoRatio5thDiv2ndIte0005)legendPossAddSyst->AddEntry(histoRatio5thDiv2ndIte0005,Form("%s",collisionSystemPbPb0005.Data()),"p");
//    if (histoRatio5thDiv2ndIte0510)legendPossAddSyst->AddEntry(histoRatio5thDiv2ndIte0510,Form("%s",collisionSystemPbPb0510.Data()),"p");
//    if (histoRatio5thDiv2ndIte1020)legendPossAddSyst->AddEntry(histoRatio5thDiv2ndIte1020,Form("%s",collisionSystemPbPb1020.Data()),"p");
//    if (histoRatio5thDiv2ndIte2040)legendPossAddSyst->AddEntry(histoRatio5thDiv2ndIte2040,Form("%s",collisionSystemPbPb2040.Data()),"p");
//    if (histoRatio5thDiv2ndIte4060)legendPossAddSyst->AddEntry(histoRatio5thDiv2ndIte4060,Form("%s",collisionSystemPbPb4060.Data()),"p");
//    if (histoRatio5thDiv2ndIte6080)legendPossAddSyst->AddEntry(histoRatio5thDiv2ndIte6080,Form("%s",collisionSystemPbPb6080.Data()),"p");
//    legendPossAddSyst->Draw();
//    
//    DrawGammaLines(0., 30.,1., 1.,0.1);
//    canvasFraction2->Update();
//    canvasFraction2->SaveAs(Form("RatioOf5thDiv2ndIteration.%s",suffix.Data()));
   
  
//    Double_t fMesonPlotRange[2] = {0., 0.2};
//    
//    
//   TCanvas *c1 = new TCanvas("PCM","InvMass",0,0,600*1.2,600);
//   c1->SetRightMargin(0.03);
//   c1->SetTopMargin(0.05);
//   c1->SetLeftMargin(0.12);
//   c1->SetBottomMargin(0.13);
//   c1->cd();
//   
//   DrawGammaHisto( histoPi00thIterationInvMassBin9_0005,
//              "2.0 GeV/c < p_{T} < 2.2 GeV/c",
//              "M_{#gamma#gamma} (GeV/c^{2})","dN_{#gamma#gamma}/dM_{#gamma#gamma}",
//              fMesonPlotRange[0],fMesonPlotRange[1],0);
//   histoPi02ndIterationInvMassBin9_0005->SetLineColor(kRed+2);
//   histoPi02ndIterationInvMassBin9_0005->Draw("hist,e,same");
//   
//   TLatex *labelMassPi00005 = new TLatex(0.15,0.88,collisionSystemPbPb0005.Data());
//    SetStyleTLatex( labelMassPi00005, 0.035,4);
//    labelMassPi00005->Draw();
//    TLegend* legendInvMass = new TLegend(0.15,0.76,0.35,0.84);
//    legendInvMass->SetFillColor(0);
//    legendInvMass->SetLineColor(0);
//    legendInvMass->SetTextSize(0.025);
// //    legendInvMass->SetNColumns(3);
//    legendInvMass->SetMargin(0.2);
//    legendInvMass->AddEntry((TObject*)0, "2.0 GeV/c < p_{T} < 2.2 GeV/c","");
//    legendInvMass->AddEntry(histoPi00thIterationInvMassBin9_0005,"no weighting","l");
//    legendInvMass->AddEntry(histoPi02ndIterationInvMassBin9_0005,"2nd iteration reweighted","l");
//    legendInvMass->Draw();
//   
// 
//   c1->SaveAs(Form("InvMass_2000MeV-2200MeV_0005.%s",suffix.Data()));
//   
//    c1->cd();
//    DrawGammaHisto( histoPi00thIterationInvMassBin9_0510,
//              "2.0 GeV/c < p_{T} < 2.2 GeV/c",
//              "M_{#gamma#gamma} (GeV/c^{2})","dN_{#gamma#gamma}/dM_{#gamma#gamma}",
//              fMesonPlotRange[0],fMesonPlotRange[1],0);
//    histoPi02ndIterationInvMassBin9_0510->SetLineColor(kRed+2);
//    histoPi02ndIterationInvMassBin9_0510->Draw("hist,e,same");
//   
//    TLatex *labelMassPi00510 = new TLatex(0.15,0.88,collisionSystemPbPb0510.Data());
//    SetStyleTLatex( labelMassPi00510, 0.035,4);
//    labelMassPi00510->Draw();
//    legendInvMass->Draw();
//    c1->SaveAs(Form("InvMass_2000MeV-2200MeV_0510.%s",suffix.Data()));
//   
//    c1->cd();
//    DrawGammaHisto( histoPi00thIterationInvMassBin9_1020,
//              "2.0 GeV/c < p_{T} < 2.2 GeV/c",
//              "M_{#gamma#gamma} (GeV/c^{2})","dN_{#gamma#gamma}/dM_{#gamma#gamma}",
//              fMesonPlotRange[0],fMesonPlotRange[1],0);
//    histoPi02ndIterationInvMassBin9_1020->SetLineColor(kRed+2);
//    histoPi02ndIterationInvMassBin9_1020->Draw("hist,e,same");
//   
//    TLatex *labelMassPi01020 = new TLatex(0.15,0.88,collisionSystemPbPb1020.Data());
//    SetStyleTLatex( labelMassPi01020, 0.035,4);
//    labelMassPi01020->Draw();
//    legendInvMass->Draw();
//    c1->SaveAs(Form("InvMass_2000MeV-2200MeV_1020.%s",suffix.Data()));
// 
//       c1->cd();
//    DrawGammaHisto( histoPi00thIterationInvMassBin9_2040,
//              "2.0 GeV/c < p_{T} < 2.2 GeV/c",
//              "M_{#gamma#gamma} (GeV/c^{2})","dN_{#gamma#gamma}/dM_{#gamma#gamma}",
//              fMesonPlotRange[0],fMesonPlotRange[1],0);
//    histoPi02ndIterationInvMassBin9_2040->SetLineColor(kRed+2);
//    histoPi02ndIterationInvMassBin9_2040->Draw("hist,e,same");
//    TLatex *labelMassPi02040 = new TLatex(0.15,0.88,collisionSystemPbPb2040.Data());
//    SetStyleTLatex( labelMassPi02040, 0.035,4);
//    labelMassPi02040->Draw();
//    legendInvMass->Draw();
//    c1->SaveAs(Form("InvMass_2000MeV-2200MeV_2040.%s",suffix.Data()));
// 
//    
//    c1->cd();
//    DrawGammaHisto( histoPi00thIterationInvMassBin9_4060,
//              "2.0 GeV/c < p_{T} < 2.2 GeV/c",
//              "M_{#gamma#gamma} (GeV/c^{2})","dN_{#gamma#gamma}/dM_{#gamma#gamma}",
//              fMesonPlotRange[0],fMesonPlotRange[1],0);
//    histoPi02ndIterationInvMassBin9_4060->SetLineColor(kRed+2);
//    histoPi02ndIterationInvMassBin9_4060->Draw("hist,e,same");
// 
//    TLatex *labelMassPi04060 = new TLatex(0.15,0.88,collisionSystemPbPb4060.Data());
//    SetStyleTLatex( labelMassPi04060, 0.035,4);
//    labelMassPi04060->Draw();
//    legendInvMass->Draw();
//    c1->SaveAs(Form("InvMass_2000MeV-2200MeV_4060.%s",suffix.Data()));
// 
//       c1->cd();
//    DrawGammaHisto( histoPi00thIterationInvMassBin9_6080,
//              "2.0 GeV/c < p_{T} < 2.2 GeV/c",
//              "M_{#gamma#gamma} (GeV/c^{2})","dN_{#gamma#gamma}/dM_{#gamma#gamma}",
//              fMesonPlotRange[0],fMesonPlotRange[1],0);
//    histoPi02ndIterationInvMassBin9_6080->SetLineColor(kRed+2);
//    histoPi02ndIterationInvMassBin9_6080->Draw("hist,e,same");
//   
//    TLatex *labelMassPi06080 = new TLatex(0.15,0.88,collisionSystemPbPb6080.Data());
//    SetStyleTLatex( labelMassPi06080, 0.035,4);
//    labelMassPi06080->Draw();
//    legendInvMass->Draw();
//    c1->SaveAs(Form("InvMass_2000MeV-2200MeV_6080.%s",suffix.Data()));
// 
//    c1->cd();
//    DrawGammaHisto( histoPi00thIterationInvMassBin10_0005,
//              "2.0 GeV/c < p_{T} < 2.2 GeV/c",
//              "M_{#gamma#gamma} (GeV/c^{2})","dN_{#gamma#gamma}/dM_{#gamma#gamma}",
//              fMesonPlotRange[0],fMesonPlotRange[1],0);
//    histoPi02ndIterationInvMassBin10_0005->SetLineColor(kRed+2);
//    histoPi02ndIterationInvMassBin10_0005->Draw("hist,e,same");
//   
//    labelMassPi00005->Draw();
//    TLegend* legendInvMass2 = new TLegend(0.15,0.76,0.35,0.84);
//    legendInvMass2->SetFillColor(0);
//    legendInvMass2->SetLineColor(0);
//    legendInvMass2->SetTextSize(0.025);
// //    legendInvMass->SetNColumns(3);
//    legendInvMass2->SetMargin(0.2);
//    legendInvMass2->AddEntry((TObject*)0, "2.2 GeV/c < p_{T} < 2.4 GeV/c","");
//    legendInvMass2->AddEntry(histoPi00thIterationInvMassBin10_0005,"no weighting","l");
//    legendInvMass2->AddEntry(histoPi02ndIterationInvMassBin10_0005,"2nd iteration reweighted","l");
//    legendInvMass2->Draw();
// 
//    c1->SaveAs(Form("InvMass_2200MeV-2400MeV_0005.%s",suffix.Data()));
// 
//    c1->cd();
//    DrawGammaHisto( histoPi00thIterationInvMassBin10_0510,
//              "2.0 GeV/c < p_{T} < 2.2 GeV/c",
//              "M_{#gamma#gamma} (GeV/c^{2})","dN_{#gamma#gamma}/dM_{#gamma#gamma}",
//              fMesonPlotRange[0],fMesonPlotRange[1],0);
//    histoPi02ndIterationInvMassBin10_0510->SetLineColor(kRed+2);
//    histoPi02ndIterationInvMassBin10_0510->Draw("hist,e,same");
//   
//    labelMassPi00510->Draw();
//    legendInvMass2->Draw();
// 
//    c1->SaveAs(Form("InvMass_2200MeV-2400MeV_0510.%s",suffix.Data()));
// 
//    c1->cd();
//    DrawGammaHisto( histoPi00thIterationInvMassBin10_1020,
//              "2.0 GeV/c < p_{T} < 2.2 GeV/c",
//              "M_{#gamma#gamma} (GeV/c^{2})","dN_{#gamma#gamma}/dM_{#gamma#gamma}",
//              fMesonPlotRange[0],fMesonPlotRange[1],0);
//    histoPi02ndIterationInvMassBin10_1020->SetLineColor(kRed+2);
//    histoPi02ndIterationInvMassBin10_1020->Draw("hist,e,same");
//   
//    labelMassPi01020->Draw();
//    legendInvMass2->Draw();
// 
//    c1->SaveAs(Form("InvMass_2200MeV-2400MeV_1020.%s",suffix.Data()));
// 
//    c1->cd();
//    DrawGammaHisto( histoPi00thIterationInvMassBin10_2040,
//              "2.0 GeV/c < p_{T} < 2.2 GeV/c",
//              "M_{#gamma#gamma} (GeV/c^{2})","dN_{#gamma#gamma}/dM_{#gamma#gamma}",
//              fMesonPlotRange[0],fMesonPlotRange[1],0);
//    histoPi02ndIterationInvMassBin10_2040->SetLineColor(kRed+2);
//    histoPi02ndIterationInvMassBin10_2040->Draw("hist,e,same");
//   
//    labelMassPi02040->Draw();
//    legendInvMass2->Draw();
// 
//    c1->SaveAs(Form("InvMass_2200MeV-2400MeV_2040.%s",suffix.Data()));
// 
//    c1->cd();
//    DrawGammaHisto( histoPi00thIterationInvMassBin10_4060,
//              "2.0 GeV/c < p_{T} < 2.2 GeV/c",
//              "M_{#gamma#gamma} (GeV/c^{2})","dN_{#gamma#gamma}/dM_{#gamma#gamma}",
//              fMesonPlotRange[0],fMesonPlotRange[1],0);
//    histoPi02ndIterationInvMassBin10_4060->SetLineColor(kRed+2);
//    histoPi02ndIterationInvMassBin10_4060->Draw("hist,e,same");
//   
//    labelMassPi04060->Draw();
//    legendInvMass2->Draw();
// 
//    c1->SaveAs(Form("InvMass_2200MeV-2400MeV_4060.%s",suffix.Data()));
// 
//    c1->cd();
//    DrawGammaHisto( histoPi00thIterationInvMassBin10_6080,
//              "2.0 GeV/c < p_{T} < 2.2 GeV/c",
//              "M_{#gamma#gamma} (GeV/c^{2})","dN_{#gamma#gamma}/dM_{#gamma#gamma}",
//              fMesonPlotRange[0],fMesonPlotRange[1],0);
//    histoPi02ndIterationInvMassBin10_6080->SetLineColor(kRed+2);
//    histoPi02ndIterationInvMassBin10_6080->Draw("hist,e,same");
//   
//    labelMassPi06080->Draw();
//    legendInvMass2->Draw();
// 
//    c1->SaveAs(Form("InvMass_2200MeV-2400MeV_6080.%s",suffix.Data()));
   
}


