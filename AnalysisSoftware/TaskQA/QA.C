﻿#include "QA.h"
#include "EventQA.C"
#include "PhotonQA.C"
#include "ClusterQA.C"



/*
Performs quality assuarance on an event, cluster and photon level. Most of the code is selecting your data set and defining the path. Keep track of the function parameters as if set incorrectly, the photon, event, and cluster QAs will not happen. 
*/
void QA(TString select = "LHC11a",
	Bool_t doEventQA = kFALSE,
	Bool_t doPhotonQA = kFALSE,
	Bool_t doClusterQA = kFALSE,
	Int_t mode = 2,                                  //Defined in PhotonQA, EventQA, and ClusterQA file
	Int_t cutNr = -1,				// if -1: you have to choose number at runtime
	Int_t doExtQA = 2,				// 0: switched off, 1: normal extQA, 2: with Cell level plots
	TString suffix = "eps"
	)
{
    const Int_t maxSets = 12;
	//nSets == 0 is always data!

	Int_t nSets = 0;
	TString fEnergyFlag = "";
	TString labelData = "Data";
	Bool_t addSubfolder = kFALSE;

	TString DataSets[maxSets];
	TString plotDataSets[maxSets];
	TString pathDataSets[maxSets];
	TString pathPhotonQA[maxSets];

//choose which data set to process
//**************************************************************************************************************
    if(select.CompareTo("LHC13g-kEMCEG1")==0||select.CompareTo("LHC13g-kEMCEG2")==0){
	//LHC13g EGA Trigger
		nSets = 2;
		fEnergyFlag = "2.76TeV";
        if(mode == 4){
          pathDataSets[0] = "/home/daniel/data/work/Grid/Legotrain-vAN-20160226-2.76TeV-Calo-QA/LHC13g_GammaCalo_60.root";
          pathDataSets[1] = "/home/daniel/data/work/Grid/Legotrain-vAN-20160226-2.76TeV-Calo-QA/LHC15a3a+_GammaCalo_60.root";
        }else{
          pathDataSets[0] = "/home/daniel/data/work/Grid/Legotrain-vAN-20160302-2.76TeV-ConvCalo-QA/LHC13g_GammaConvCalo_95.root";
          pathDataSets[1] = "/home/daniel/data/work/Grid/Legotrain-vAN-20160302-2.76TeV-ConvCalo-QA/LHC15a3a+_GammaConvCalo_95.root";
        }
		if(select.CompareTo("LHC13g-kEMCEG1")==0){
			DataSets[0]="LHC13g-kEMCEG1";
			cutNr=0;
            if(mode == 4) cutNr=3;
		}else{
			DataSets[0]="LHC13g-kEMCEG2";
			cutNr=1;
            if(mode == 4) cutNr=4;
		}
		DataSets[1]="LHC15a3a";
		plotDataSets[0]="LHC13g";
		plotDataSets[1]="JetJet";
		pathPhotonQA[0] = "";
	}
//**************************************************************************************************************
	else if(select.CompareTo("LHC13g-kEMC7")==0){
	//LHC13g Trigger
		cutNr=1;
		nSets = 2;
		fEnergyFlag = "2.76TeV";
        if(mode == 4){
          cutNr=2;
          pathDataSets[0] = "/home/daniel/data/work/Grid/Legotrain-vAN-20160226-2.76TeV-Calo-QA/LHC13g_GammaCalo_60.root";
          pathDataSets[1] = "/home/daniel/data/work/Grid/Legotrain-vAN-20160226-2.76TeV-Calo-QA/LHC15a3a+_GammaCalo_60.root";
        }else{
          pathDataSets[0] = "/home/daniel/data/work/Grid/Legotrain-vAN-20160302-2.76TeV-ConvCalo-QA/LHC13g_GammaConvCalo_96.root";
          pathDataSets[1] = "/home/daniel/data/work/Grid/Legotrain-vAN-20160302-2.76TeV-ConvCalo-QA/LHC15a3a+_GammaConvCalo_96.root";
        }
		DataSets[0]="LHC13g-kEMC7";
		DataSets[1]="LHC15a3a";
		plotDataSets[0]="LHC13g";
		plotDataSets[1]="JetJet";
		pathPhotonQA[0] = "";
	}
//**************************************************************************************************************
	else if(select.CompareTo("LHC13g")==0){
	//LHC13g Trigger+MB
		cutNr=0;
		nSets = 2;
		fEnergyFlag = "2.76TeV";
        if(mode == 4){
          pathDataSets[0] = "/home/daniel/data/work/Grid/Legotrain-vAN-20160226-2.76TeV-Calo-QA/LHC13g_GammaCalo_60.root";
          pathDataSets[1] = "/home/daniel/data/work/Grid/Legotrain-vAN-20160226-2.76TeV-Calo-QA/LHC15g2_GammaCalo_60.root";
        }else{
          pathDataSets[0] = "/home/daniel/data/work/Grid/Legotrain-vAN-20160302-2.76TeV-ConvCalo-QA/LHC13g_GammaConvCalo_96.root";
          pathDataSets[1] = "/home/daniel/data/work/Grid/Legotrain-vAN-20160302-2.76TeV-ConvCalo-QA/LHC15g2_GammaConvCalo_96.root";
        }
		DataSets[0]="LHC13g";
		DataSets[1]="LHC15g2";
		plotDataSets[0]="LHC13g";
		plotDataSets[1]="Pythia8";
		pathPhotonQA[0] = "";
	}
//**************************************************************************************************************
    else if(select.CompareTo("LHC13g+")==0){
      //LHC13g Trigger+MB+JetJet
      cutNr=0;
      nSets = 3;
      fEnergyFlag = "2.76TeV";
      if(mode == 4){
        pathDataSets[0] = "/home/daniel/data/work/Grid/Legotrain-vAN-20160226-2.76TeV-Calo-QA/LHC13g_GammaCalo_60.root";
        pathDataSets[1] = "/home/daniel/data/work/Grid/Legotrain-vAN-20160226-2.76TeV-Calo-QA/LHC15g2_GammaCalo_60.root";
        pathDataSets[2] = "/home/daniel/data/work/Grid/Legotrain-vAN-20160226-2.76TeV-Calo-QA/LHC15a3a+_GammaCalo_60.root";
      }else{
        pathDataSets[0] = "/home/daniel/data/work/Grid/Legotrain-vAN-20160302-2.76TeV-ConvCalo-QA/LHC13g_GammaConvCalo_96.root";
        pathDataSets[1] = "/home/daniel/data/work/Grid/Legotrain-vAN-20160302-2.76TeV-ConvCalo-QA/LHC15g2_GammaConvCalo_96.root";
        pathDataSets[2] = "/home/daniel/data/work/Grid/Legotrain-vAN-20160302-2.76TeV-ConvCalo-QA/LHC15a3a+_GammaConvCalo_96.root";
      }
      DataSets[0]="LHC13g";
      DataSets[1]="LHC15g2";
      DataSets[2]="LHC15a3a";
      plotDataSets[0]="LHC13g";
      plotDataSets[1]="Pythia8";
      plotDataSets[2]="JetJet";
      pathPhotonQA[0] = "";
      pathPhotonQA[1] = "";
      pathPhotonQA[2] = "";
    }
//**************************************************************************************************************
	else if(select.CompareTo("LHC11a-kEMC1")==0){
	//LHC11a Trigger
		cutNr = 1;
		nSets = 1;
		fEnergyFlag = "2.76TeV";
        if(mode == 4){
          pathDataSets[0] = "/home/daniel/data/work/Grid/Legotrain-vAN-20160226-2.76TeV-Calo-QA/LHC11a_GammaCalo_1.root";
        }else{
          pathDataSets[0] = "/home/daniel/data/work/Grid/Legotrain-vAN-20151019-2.76TeV-QA/GammaConvCalo_LHC11a-pass4_1.root";
        }
		DataSets[0]="LHC11a_p4_wSDD-kEMC1";
		plotDataSets[0]="LHC11a";
		pathPhotonQA[0] = "";
	}
//**************************************************************************************************************
	else if(select.CompareTo("LHC11a-kEMC1+")==0){
	//LHC11a-kEMC1 + MC
		cutNr = 1;
		nSets = 2;
		fEnergyFlag = "2.76TeV";
        if(mode == 4){
          pathDataSets[0] = "/home/daniel/data/work/Grid/Legotrain-vAN-20160226-2.76TeV-Calo-QA/LHC11a_GammaCalo_1.root";
          pathDataSets[1] = "/home/daniel/data/work/Grid/Legotrain-vAN-20160226-2.76TeV-Calo-QA/LHC15g1a_GammaCalo_1.root";
        }else{
          pathDataSets[0] = "/home/daniel/data/work/Grid/Legotrain-vAN-20151019-2.76TeV-QA/GammaConvCalo_LHC11a-pass4_1.root";
          pathDataSets[1] = "/home/daniel/data/work/Grid/Legotrain-vAN-20151019-2.76TeV-QA/GammaConvCalo_MC_LHC15g1a_1.root";
        }
		DataSets[0]="LHC11a_p4_wSDD-kEMC1"; DataSets[1]="LHC15g1a";
		plotDataSets[0]="LHC11a"; plotDataSets[1]="JetJet";
		pathPhotonQA[0] = "";
		pathPhotonQA[1] = "";
	}
//**************************************************************************************************************
	else if(select.CompareTo("LHC11a")==0){
	//LHC11a + MC
		cutNr = 0;
		nSets = 3;
		fEnergyFlag = "2.76TeV";
        if(mode == 4){
          pathDataSets[0] = "/home/daniel/data/work/Grid/Legotrain-vAN-20160226-2.76TeV-Calo-QA/LHC11a_GammaCalo_1.root";
          pathDataSets[1] = "/home/daniel/data/work/Grid/Legotrain-vAN-20160226-2.76TeV-Calo-QA/LHC12f1a_GammaCalo_1.root";
          pathDataSets[2] = "/home/daniel/data/work/Grid/Legotrain-vAN-20160226-2.76TeV-Calo-QA/LHC12f1b_GammaCalo_1.root";
        }else{
          pathDataSets[0] = "/home/daniel/data/work/Grid/Legotrain-vAN-20151019-2.76TeV-QA/GammaConvCalo_LHC11a-pass4_1.root";
          pathDataSets[1] = "/home/daniel/data/work/Grid/Legotrain-vAN-20151019-2.76TeV-QA/GammaConvCalo_MC_LHC12f1a_1.root";
          pathDataSets[2] = "/home/daniel/data/work/Grid/Legotrain-vAN-20151019-2.76TeV-QA/GammaConvCalo_MC_LHC12f1b_1.root";
        }
		DataSets[0]="LHC11a_p4_wSDD"; DataSets[1]="LHC12f1a"; DataSets[2]="LHC12f1b";
		plotDataSets[0]="LHC11a"; plotDataSets[1]="Pythia8"; plotDataSets[2]="Phojet";
		pathPhotonQA[0] = "";
		pathPhotonQA[1] = "";
		pathPhotonQA[2] = "";
	}
//**************************************************************************************************************
	else if(select.CompareTo("LHC11a+")==0){
	//LHC11a + MC
		cutNr = 0;
		nSets = 4;
		fEnergyFlag = "2.76TeV";
        if(mode == 4){
          pathDataSets[0] = "/home/daniel/data/work/Grid/Legotrain-vAN-20160226-2.76TeV-Calo-QA/LHC11a_GammaCalo_1.root";
          pathDataSets[1] = "/home/daniel/data/work/Grid/Legotrain-vAN-20160226-2.76TeV-Calo-QA/LHC12f1a_GammaCalo_1.root";
          pathDataSets[2] = "/home/daniel/data/work/Grid/Legotrain-vAN-20160226-2.76TeV-Calo-QA/LHC12f1b_GammaCalo_1.root";
          pathDataSets[3] = "/home/daniel/data/work/Grid/Legotrain-vAN-20160226-2.76TeV-Calo-QA/LHC15g1a_GammaCalo_1.root";
        }else{
          pathDataSets[0] = "/home/daniel/data/work/Grid/Legotrain-vAN-20151019-2.76TeV-QA/GammaConvCalo_LHC11a-pass4_1.root";
          pathDataSets[1] = "/home/daniel/data/work/Grid/Legotrain-vAN-20151019-2.76TeV-QA/GammaConvCalo_MC_LHC12f1a_1.root";
          pathDataSets[2] = "/home/daniel/data/work/Grid/Legotrain-vAN-20151019-2.76TeV-QA/GammaConvCalo_MC_LHC12f1b_1.root";
          pathDataSets[3] = "/home/daniel/data/work/Grid/Legotrain-vAN-20151019-2.76TeV-QA/GammaConvCalo_MC_LHC15g1a_1.root";
        }
		DataSets[0]="LHC11a_p4_wSDD"; DataSets[1]="LHC12f1a"; DataSets[2]="LHC12f1b"; DataSets[3]="LHC15g1a";
		plotDataSets[0]="LHC11a"; plotDataSets[1]="Pythia8"; plotDataSets[2]="Phojet"; plotDataSets[3]="JetJet";
		pathPhotonQA[0] = "";
		pathPhotonQA[1] = "";
		pathPhotonQA[2] = "";
		pathPhotonQA[3] = "";
	}
//**************************************************************************************************************
//    else if(select.CompareTo("2.76TeV")==0){
//      //LHC11a + MC
//      cutNr = 0;
//      nSets = 6;
//      fEnergyFlag = "2.76TeV";
//      pathDataSets[0] = "/home/daniel/data/work/Grid/Legotrain-vAN-20151019-2.76TeV-QA/GammaConvCalo_LHC11a-pass4_1.root";
//      pathDataSets[1] = "/home/daniel/data/work/Grid/Legotrain-vAN-20151019-2.76TeV-QA/GammaConvCalo_MC_LHC12f1a_1.root";
//      pathDataSets[2] = "/home/daniel/data/work/Grid/Legotrain-vAN-20151019-2.76TeV-QA/GammaConvCalo_MC_LHC12f1b_1.root";
//      pathDataSets[3] = "/home/daniel/data/work/Grid/Legotrain-vAN-20151019-2.76TeV-QA/GammaConvCalo_MC_LHC15g1a_1.root";
//      pathDataSets[4] = "/home/daniel/data/work/Grid/Legotrain-vAN-20151019-2.76TeV-QA/GammaConvCalo_LHC13g-pass3_96.root";
//      pathDataSets[5] = "/home/daniel/data/work/Grid/Legotrain-vAN-20151019-2.76TeV-QA/GammaConvCalo_MC_LHC15g2_96.root";
//      DataSets[0]="LHC11a_p4_wSDD"; DataSets[1]="LHC12f1a"; DataSets[2]="LHC12f1b"; DataSets[3]="LHC15g1a";
//      DataSets[4]="LHC13g"; DataSets[5]="LHC15g2";
//      plotDataSets[0]="LHC11a"; plotDataSets[1]="Pythia8"; plotDataSets[2]="Phojet"; plotDataSets[3]="JetJet";
//      plotDataSets[4]="LHC13g"; plotDataSets[5]="Pythia8";
//      pathPhotonQA[0] = "";
//      pathPhotonQA[1] = "";
//      pathPhotonQA[2] = "";
//      pathPhotonQA[3] = "";
//      pathPhotonQA[4] = "";
//      pathPhotonQA[5] = "";
//    }
//**************************************************************************************************************
	else if(select.CompareTo("LHC11a+AddSig")==0){
	//LHC11a + MC + AddSignals
		cutNr = 0;
		nSets = 4;
		fEnergyFlag = "2.76TeV";
		pathDataSets[0] = "/home/daniel/data/work/Grid/Legotrain-vAN-20150825-ConvCalo/GammaConvCalo_LHC11a-pass4_1.root";
		pathDataSets[1] = "/home/daniel/data/work/Grid/Legotrain-vAN-20150825-ConvCalo/GammaConvCalo_MC_LHC12f1a_1.root";
		pathDataSets[2] = "/home/daniel/data/work/Grid/Legotrain-vAN-20150825-ConvCalo/GammaConvCalo_MC_LHC12f1b_1.root";
		pathDataSets[3] = "/home/daniel/data/work/Grid/Legotrain-vAN-20150825-ConvCalo/GammaConvCalo_MC_LHC12i3_1.root";
		DataSets[0]="LHC11a_p4_wSDD"; DataSets[1]="LHC12f1a"; DataSets[2]="LHC12f1b"; DataSets[3]="LHC12i3";
		plotDataSets[0]="LHC11a"; plotDataSets[1]="Pythia8"; plotDataSets[2]="Phojet"; plotDataSets[3]="Pythia8-AddedSignals";
		pathPhotonQA[0] = "";
		pathPhotonQA[1] = "";
		pathPhotonQA[2] = "";
		pathPhotonQA[3] = "";
	}
//**************************************************************************************************************
	else if(select.CompareTo("LHC15-JJ")==0){
	//LHC15-JJ EvsM02
		cutNr = 0;
        nSets = 2;
		fEnergyFlag = "2.76TeV";
        pathDataSets[0] = "/home/daniel/data/work/Grid/Legotrain-vAN-20150720-EvsM02/GammaConvCalo_23.root";
        pathDataSets[1] = "/home/daniel/data/work/Grid/Legotrain-vAN-20150720-EvsM02/GammaConvCalo_23.root";
		pathPhotonQA[0] = "";
        pathPhotonQA[1] = "";
        DataSets[0]="LHC15a3"; DataSets[1]="LHC15a3";
        plotDataSets[0]="LHC15a3a,b"; plotDataSets[1]="LHC15a3a+b";
	}
//**************************************************************************************************************
	else if(select.CompareTo("LHC10")==0){
	//LHC10
		cutNr = 0;
		nSets = 2;
		fEnergyFlag = "7TeV";
		pathDataSets[0] = "/home/daniel/data/work/Grid/Legotrain-vAN-20150922-LHC10_p4-QA/GammaConvCalo_LHC10bcdef-pass4_201.root";
		pathDataSets[1] = "/home/daniel/data/work/Grid/Legotrain-vAN-20150922-LHC10_p4-QA/GammaConvCalo_MC_LHC14j4b_LHC14j4c_LHC14j4d_LHC14j4e_LHC14j4f_201.root";
		DataSets[0]="LHC10_pass4"; DataSets[1]="LHC14j4";
		plotDataSets[0]="LHC10bcdef"; plotDataSets[1]="Pythia8";
		pathPhotonQA[0] = Form("/home/daniel/data/work/photonconv/AnalysisSoftware/DataQA/20150922/%s/PhotonQA_%s.root",DataSets[0].Data(),DataSets[0].Data());
		pathPhotonQA[1] = Form("/home/daniel/data/work/photonconv/AnalysisSoftware/DataQA/20150922/%s/PhotonQA_%s.root",DataSets[1].Data(),DataSets[1].Data());
	}
//**************************************************************************************************************
	else if(select.BeginsWith("LHC10") && select.Length()==6){
	//LHC10
		addSubfolder=kTRUE;
		cutNr = 0;
		nSets = 2;
		fEnergyFlag = "7TeV";
		TString tmpPeriod = select;
		tmpPeriod.Remove(0,tmpPeriod.Length()-1);
		pathDataSets[0] = Form("/home/daniel/data/work/Grid/Legotrain-vAN-20150922-LHC10_p4-QA/GammaConvCalo_LHC10%s-pass4_201.root",tmpPeriod.Data());
		pathDataSets[1] = Form("/home/daniel/data/work/Grid/Legotrain-vAN-20150922-LHC10_p4-QA/GammaConvCalo_MC_LHC14j4%s_201.root",tmpPeriod.Data());
		DataSets[0]=Form("%s_pass4",select.Data()); DataSets[1]=Form("LHC14j4%s",tmpPeriod.Data());
		plotDataSets[0]=select; plotDataSets[1]="Pythia8";
		pathPhotonQA[0] = Form("/home/daniel/data/work/photonconv/AnalysisSoftware/DataQA/20150922/%s/PhotonQA_%s.root",DataSets[0].Data(),DataSets[0].Data());
		pathPhotonQA[1] = Form("/home/daniel/data/work/photonconv/AnalysisSoftware/DataQA/20150922/%s/PhotonQA_%s.root",DataSets[1].Data(),DataSets[1].Data());
	}
//**************************************************************************************************************
	else if(select.CompareTo("LHC12")==0){
	//LHC12
		cutNr = 0;
		nSets = 3;
		fEnergyFlag = "8TeV";
        pathDataSets[0] = "/home/daniel/data/work/photonconv/AnalysisSoftware/DataQA/20160125/LHC12_GammaConvCalo_120.root";
        pathDataSets[1] = "/home/daniel/data/work/photonconv/AnalysisSoftware/DataQA/20160125/LHC15h1_GammaConvCalo_120.root";
        pathDataSets[2] = "/home/daniel/data/work/photonconv/AnalysisSoftware/DataQA/20160125/LHC15h2_GammaConvCalo_120.root";
        DataSets[0]="LHC12"; DataSets[1]="LHC15h1"; DataSets[2]="LHC15h2";
        plotDataSets[0]="LHC12a-i"; plotDataSets[1]="Pythia8"; plotDataSets[2]="Phojet";
        pathPhotonQA[0] = "/home/daniel/data/work/photonconv/AnalysisSoftware/DataQA/20160104/LHC12/PhotonQA_LHC12.root";
        pathPhotonQA[1] = "/home/daniel/data/work/photonconv/AnalysisSoftware/DataQA/20160104/LHC15h1/PhotonQA_LHC15h1.root";
        pathPhotonQA[2] = "/home/daniel/data/work/photonconv/AnalysisSoftware/DataQA/20160104/LHC15h2/PhotonQA_LHC15h2.root";
	}
//**************************************************************************************************************
	else if(select.BeginsWith("LHC12") && select.Length()==6){
	//LHC12 Periodwise
		addSubfolder=kTRUE;
		cutNr = 0;
		nSets = 4;
		fEnergyFlag="8TeV";
//		pathDataSets[0] = Form("/home/daniel/data/work/Grid/Legotrain-vAN-20150728-LHC12_QA-2nd/GammaConvCalo_%s-pass1_120.root",select.Data());
//		pathDataSets[1] = Form("/home/daniel/data/work/Grid/Legotrain-vAN-20150728-LHC12_QA-2nd/GammaConvCalo_MC_LHC14e2a-%s_120.root",select.Data());
//		pathDataSets[2] = Form("/home/daniel/data/work/Grid/Legotrain-vAN-20150728-LHC12_QA-2nd/GammaConvCalo_MC_LHC14e2b-%s_120.root",select.Data());
//		pathDataSets[3] = Form("/home/daniel/data/work/Grid/Legotrain-vAN-20150728-LHC12_QA-2nd/GammaConvCalo_MC_LHC14e2c-%s_120.root",select.Data());
		pathDataSets[0] = Form("/home/daniel/data/work/Grid/Legotrain-vAN-20151002-LHC12_pass2-QA/GammaConvCalo_%s-pass1_120.root",select.Data());
		pathDataSets[1] = Form("/home/daniel/data/work/Grid/Legotrain-vAN-20151002-LHC12_pass2-QA/GammaConvCalo_MC_LHC14e2a-%s_120.root",select.Data());
		pathDataSets[2] = Form("/home/daniel/data/work/Grid/Legotrain-vAN-20151002-LHC12_pass2-QA/GammaConvCalo_MC_LHC14e2b-%s_120.root",select.Data());
		pathDataSets[3] = Form("/home/daniel/data/work/Grid/Legotrain-vAN-20151002-LHC12_pass2-QA/GammaConvCalo_MC_LHC14e2c-%s_120.root",select.Data());
		DataSets[0]=select; DataSets[1]=Form("LHC14e2a-%s",select.Data()); DataSets[2]=Form("LHC14e2b-%s",select.Data()); DataSets[3]=Form("LHC14e2c-%s",select.Data());
		plotDataSets[0]=select; plotDataSets[1]="Pythia8"; plotDataSets[2]="Pythia8+AddSig"; plotDataSets[3]="Phojet";
		pathPhotonQA[0] = "";
		pathPhotonQA[1] = "";
		pathPhotonQA[2] = "";
		pathPhotonQA[3] = "";
	}
//**************************************************************************************************************
	else if(select.BeginsWith("LHC12") && select.Length()==9 && select.EndsWith("-p2")){
	//LHC12x-p2 Periodwise
		addSubfolder=kTRUE;
		cutNr = 0;
		nSets = 3;
		fEnergyFlag="8TeV";
		select.Remove(select.Length()-3,select.Length());
        TString tmpPeriod = select;
        TString tmpA = "";
        tmpPeriod.Remove(0,tmpPeriod.Length()-1);
        if(tmpPeriod.CompareTo("a")==0) tmpA="1";
        pathDataSets[0] = Form("/home/daniel/data/work/photonconv/AnalysisSoftware/DataQA/20160125/%s_GammaConvCalo_120.root",select.Data());
        pathDataSets[1] = Form("/home/daniel/data/work/photonconv/AnalysisSoftware/DataQA/20160125/LHC15h1%s%s_GammaConvCalo_120.root",tmpPeriod.Data(),tmpA.Data());
        pathDataSets[2] = Form("/home/daniel/data/work/photonconv/AnalysisSoftware/DataQA/20160125/LHC15h2%s_GammaConvCalo_120.root",tmpPeriod.Data());
        DataSets[0]=select; DataSets[1]=Form("LHC15h1%s%s",tmpPeriod.Data(),tmpA.Data()); DataSets[2]=Form("LHC15h2%s",tmpPeriod.Data());
		plotDataSets[0]=select; plotDataSets[1]="Pythia8"; plotDataSets[2]="Phojet";
        pathPhotonQA[0] = Form("/home/daniel/data/work/photonconv/AnalysisSoftware/DataQA/20160104/%s/PhotonQA_%s.root",DataSets[0].Data(),DataSets[0].Data());
        pathPhotonQA[1] = Form("/home/daniel/data/work/photonconv/AnalysisSoftware/DataQA/20160104/%s/PhotonQA_%s.root",DataSets[1].Data(),DataSets[1].Data());
        pathPhotonQA[2] = Form("/home/daniel/data/work/photonconv/AnalysisSoftware/DataQA/20160104/%s/PhotonQA_%s.root",DataSets[2].Data(),DataSets[2].Data());
	}
    //**************************************************************************************************************
    else if(select.CompareTo("LHC12g-Vertex")==0){
      //LHC12g-p2 VertexCheck
      addSubfolder=kTRUE;
      cutNr = 0;
      nSets = 2;
      fEnergyFlag="8TeV";
      select.Remove(select.Length()-7,select.Length());
      pathDataSets[0] = "/home/daniel/data/work/Grid/Legotrain-vAN-20151027-LHC12a_QA_MC_p2/VertexCheck/GammaConvCalo_LHC12g_pass2_120.root";
      pathDataSets[1] = "/home/daniel/data/work/Grid/Legotrain-vAN-20151027-LHC12a_QA_MC_p2/VertexCheck/GammaConvCalo_MC_LHC15h1g_pass2_120.root";
      DataSets[0]=select; DataSets[1]="LHC15h1g";
      plotDataSets[0]=select; plotDataSets[1]="Pythia8";
    }
    //**************************************************************************************************************
    else if(select.CompareTo("LHC12-periods")==0){
      //LHC12 comparison of all periods
      addSubfolder=kTRUE;
      cutNr = 0;
      nSets = 8;
      fEnergyFlag="8TeV";
      labelData="LHC12";
      pathDataSets[0] = "/home/daniel/data/work/photonconv/AnalysisSoftware/DataQA/20160125/LHC12_GammaConvCalo_120.root";
      pathDataSets[1] = "/home/daniel/data/work/photonconv/AnalysisSoftware/DataQA/20160125/LHC12a_GammaConvCalo_120.root";
      pathDataSets[2] = "/home/daniel/data/work/photonconv/AnalysisSoftware/DataQA/20160125/LHC12b_GammaConvCalo_120.root";
      pathDataSets[3] = "/home/daniel/data/work/photonconv/AnalysisSoftware/DataQA/20160125/LHC12c_GammaConvCalo_120.root";
      pathDataSets[4] = "/home/daniel/data/work/photonconv/AnalysisSoftware/DataQA/20160125/LHC12d_GammaConvCalo_120.root";
      pathDataSets[5] = "/home/daniel/data/work/photonconv/AnalysisSoftware/DataQA/20160125/LHC12f_GammaConvCalo_120.root";
      //pathDataSets[6] = "/home/daniel/data/work/photonconv/AnalysisSoftware/DataQA/20160125/LHC12g_GammaConvCalo_120.root";
      pathDataSets[6] = "/home/daniel/data/work/photonconv/AnalysisSoftware/DataQA/20160125/LHC12h_GammaConvCalo_120.root";
      pathDataSets[7] = "/home/daniel/data/work/photonconv/AnalysisSoftware/DataQA/20160125/LHC12i_GammaConvCalo_120.root";
      DataSets[0]="LHC12"; DataSets[1]="LHC12a"; DataSets[2]="LHC12b"; DataSets[3]="LHC12c"; DataSets[4]="LHC12d"; DataSets[5]="LHC12f"; /*DataSets[6]="LHC12g";*/ DataSets[6]="LHC12h"; DataSets[7]="LHC12i";
      plotDataSets[0]="LHC12"; plotDataSets[1]="LHC12a"; plotDataSets[2]="LHC12b"; plotDataSets[3]="LHC12c"; plotDataSets[4]="LHC12d"; plotDataSets[5]="LHC12f"; /*plotDataSets[6]="LHC12g";*/ plotDataSets[6]="LHC12h"; plotDataSets[7]="LHC12i";
      pathPhotonQA[0] = "/home/daniel/data/work/photonconv/AnalysisSoftware/DataQA/20160104/LHC12/PhotonQA_LHC12.root";
      pathPhotonQA[1] = "/home/daniel/data/work/photonconv/AnalysisSoftware/DataQA/20160104/LHC12a/PhotonQA_LHC12a.root";
      pathPhotonQA[2] = "/home/daniel/data/work/photonconv/AnalysisSoftware/DataQA/20160104/LHC12b/PhotonQA_LHC12b.root";
      pathPhotonQA[3] = "/home/daniel/data/work/photonconv/AnalysisSoftware/DataQA/20160104/LHC12c/PhotonQA_LHC12c.root";
      pathPhotonQA[4] = "/home/daniel/data/work/photonconv/AnalysisSoftware/DataQA/20160104/LHC12d/PhotonQA_LHC12d.root";
      pathPhotonQA[5] = "/home/daniel/data/work/photonconv/AnalysisSoftware/DataQA/20160104/LHC12f/PhotonQA_LHC12f.root";
      //pathPhotonQA[6] = "/home/daniel/data/work/photonconv/AnalysisSoftware/DataQA/20160104/LHC12g/PhotonQA_LHC12g.root";
      pathPhotonQA[6] = "/home/daniel/data/work/photonconv/AnalysisSoftware/DataQA/20160104/LHC12h/PhotonQA_LHC12h.root";
      pathPhotonQA[7] = "/home/daniel/data/work/photonconv/AnalysisSoftware/DataQA/20160104/LHC12i/PhotonQA_LHC12i.root";
    }
//**************************************************************************************************************
    else if(select.BeginsWith("LHC12-kEMC") && !select.Contains("-periods")){
	//LHC12 Trigger
		cutNr = 0;
		nSets = 1;
		fEnergyFlag="8TeV";
		TString number = "";
		if(select.CompareTo("LHC12-kEMC7")==0) number = "121";
		else if(select.CompareTo("LHC12-kEMCEGA")==0) number = "122";
		else { cout << "No valid selection! Returning..." << endl; return;}
        pathDataSets[0] = Form("/home/daniel/data/work/photonconv/AnalysisSoftware/DataQA/20160125/%s_GammaConvCalo_%s.root",select.Data(),number.Data());
		DataSets[0]=select;
		plotDataSets[0]="LHC12";
		pathPhotonQA[0] = "";
	}
//**************************************************************************************************************
    else if(select.BeginsWith("LHC12-kEMC") && select.Contains("-periods")){
      //LHC12 Trigger
      addSubfolder=kTRUE;
      cutNr = 0;
      nSets = 1;
      fEnergyFlag="8TeV";
      if(select.CompareTo("LHC12-kEMC7-periods")==0) {
        nSets=7;
        labelData="LHC12-kEMC7";
        pathDataSets[0] = "/home/daniel/data/work/photonconv/AnalysisSoftware/DataQA/20160125/LHC12-kEMC7_GammaConvCalo_121.root";
        pathDataSets[1] = "/home/daniel/data/work/photonconv/AnalysisSoftware/DataQA/20160125/LHC12b-kEMC7_GammaConvCalo_121.root";
        pathDataSets[2] = "/home/daniel/data/work/photonconv/AnalysisSoftware/DataQA/20160125/LHC12c-kEMC7_GammaConvCalo_121.root";
        pathDataSets[3] = "/home/daniel/data/work/photonconv/AnalysisSoftware/DataQA/20160125/LHC12d-kEMC7_GammaConvCalo_121.root";
        pathDataSets[4] = "/home/daniel/data/work/photonconv/AnalysisSoftware/DataQA/20160125/LHC12f-kEMC7_GammaConvCalo_121.root";
        //pathDataSets[5] = "/home/daniel/data/work/photonconv/AnalysisSoftware/DataQA/20160125/LHC12g-kEMC7_GammaConvCalo_121.root";
        pathDataSets[6] = "/home/daniel/data/work/photonconv/AnalysisSoftware/DataQA/20160125/LHC12h-kEMC7_GammaConvCalo_121.root";
        pathDataSets[7] = "/home/daniel/data/work/photonconv/AnalysisSoftware/DataQA/20160125/LHC12i-kEMC7_GammaConvCalo_121.root";
        DataSets[0]="LHC12-kEMC7"; DataSets[1]="LHC12b-kEMC7"; DataSets[2]="LHC12c-kEMC7"; DataSets[3]="LHC12d-kEMC7";
        DataSets[4]="LHC12f-kEMC7"; DataSets[5]="LHC12g-kEMC7"; DataSets[6]="LHC12h-kEMC7"; DataSets[7]="LHC12i-kEMC7";
        plotDataSets[0]="LHC12"; plotDataSets[1]="LHC12b"; plotDataSets[2]="LHC12c"; plotDataSets[3]="LHC12d";
        plotDataSets[4]="LHC12f"; plotDataSets[5]="LHC12g"; plotDataSets[6]="LHC12h"; plotDataSets[7]="LHC12i";
        pathPhotonQA[0] = "";pathPhotonQA[1] = "";pathPhotonQA[2] = "";pathPhotonQA[3] = "";pathPhotonQA[4] = "";pathPhotonQA[5] = "";
        pathPhotonQA[6] = "";//pathPhotonQA[7] = "";
      }
      else if(select.CompareTo("LHC12-kEMCEGA-periods")==0){
        nSets=6;
        labelData="LHC12-kEMCEGA";
        pathDataSets[0] = "/home/daniel/data/work/photonconv/AnalysisSoftware/DataQA/20160125/LHC12-kEMCEGA_GammaConvCalo_122.root";
        pathDataSets[1] = "/home/daniel/data/work/photonconv/AnalysisSoftware/DataQA/20160125/LHC12c-kEMCEGA_GammaConvCalo_122.root";
        pathDataSets[2] = "/home/daniel/data/work/photonconv/AnalysisSoftware/DataQA/20160125/LHC12d-kEMCEGA_GammaConvCalo_122.root";
        pathDataSets[3] = "/home/daniel/data/work/photonconv/AnalysisSoftware/DataQA/20160125/LHC12f-kEMCEGA_GammaConvCalo_122.root";
        //pathDataSets[4] = "/home/daniel/data/work/photonconv/AnalysisSoftware/DataQA/20160125/LHC12g-kEMCEGA_GammaConvCalo_122.root";
        pathDataSets[4] = "/home/daniel/data/work/photonconv/AnalysisSoftware/DataQA/20160125/LHC12h-kEMCEGA_GammaConvCalo_122.root";
        pathDataSets[5] = "/home/daniel/data/work/photonconv/AnalysisSoftware/DataQA/20160125/LHC12i-kEMCEGA_GammaConvCalo_122.root";
        DataSets[0]="LHC12-kEMCEGA"; DataSets[1]="LHC12c-kEMCEGA"; DataSets[2]="LHC12d-kEMCEGA";
        DataSets[3]="LHC12f-kEMCEGA"; /*DataSets[4]="LHC12g-kEMCEGA";*/ DataSets[4]="LHC12h-kEMCEGA"; DataSets[5]="LHC12i-kEMCEGA";
        plotDataSets[0]="LHC12"; plotDataSets[1]="LHC12c"; plotDataSets[2]="LHC12d";
        plotDataSets[3]="LHC12f"; /*plotDataSets[4]="LHC12g";*/ plotDataSets[4]="LHC12h"; plotDataSets[5]="LHC12i";
        pathPhotonQA[0] = "";pathPhotonQA[1] = "";pathPhotonQA[2] = "";pathPhotonQA[3] = "";pathPhotonQA[4] = "";pathPhotonQA[5] = "";
        //pathPhotonQA[6] = "";
      }
      else { cout << "No valid selection! Returning..." << endl; return;}
    }
//**************************************************************************************************************
	else if(!select.BeginsWith("LHC12-kEMC") && select.BeginsWith("LHC12") && select.Contains("-kEMC")){
	//LHC12 Trigger Periodwise
		addSubfolder=kTRUE;
		cutNr = 0;
		nSets = 1;
		fEnergyFlag="8TeV";
		TString number = "";
        TString selectResize = select;
        selectResize.Resize(6);
		if(select.EndsWith("-kEMC7")) number = "121";
		else if(select.EndsWith("-kEMCEGA")) number = "122";
		else { cout << "No valid selection! Returning..." << endl; return;}
        pathDataSets[0] = Form("/home/daniel/data/work/photonconv/AnalysisSoftware/DataQA/20160125/%s_GammaConvCalo_%s.root",select.Data(),number.Data());
		DataSets[0]=select;
        plotDataSets[0]=selectResize;
		pathPhotonQA[0] = "";
	}
    //TESTING
    //**************************************************************************************************************
        else if( select.CompareTo("JJ-LHC12-kEMCEGA") == 0 || select.CompareTo("JJ-LHC12-kEMC7") == 0){
        //LHC12 Trigger Periodwise
        select.Remove(0,3);
            addSubfolder=kTRUE;
            cutNr = 0;
            nSets = 2;
            fEnergyFlag="8TeV";
            TString number = "";
            TString selectResize = select;
            selectResize.Resize(6);
            if(select.EndsWith("-kEMC7")) number = "121";
            else if(select.EndsWith("-kEMCEGA")) number = "122";
            else { cout << "No valid selection! Returning..." << endl; return;}
            pathDataSets[0] = Form("/home/daniel/data/work/photonconv/AnalysisSoftware/DataQA/20160309/%s_GammaConvCalo_%s.root",select.Data(),number.Data());
            pathDataSets[1] = "/home/daniel/data/work/Grid/Legotrain-vAN-20160324-8TeV_JetJet_QA_10/GammaConvCalo_31.root";
            DataSets[0]=select;
            DataSets[1]="LHC16c2";
            plotDataSets[0]=selectResize;
            plotDataSets[1]="JetJet";
            pathPhotonQA[0] = "";
            pathPhotonQA[1] = "";
        }
    //**************************************************************************************************************
        else if( select.CompareTo("TenderVariations") == 0 ){
        //LHC12 Trigger Periodwise
            labelData = "S500/A100/T500";
            mode = 4;
            addSubfolder=kTRUE;
            cutNr = 0;
            nSets = 11;
            fEnergyFlag="8TeV";
            pathDataSets[0] = "/home/daniel/data/work/Grid/Legotrain-vAN-20160309-8TeV-TenderVariations/LHC12d_GammaCalo_101.root";
            pathDataSets[1] = "/home/daniel/data/work/Grid/Legotrain-vAN-20160309-8TeV-TenderVariations/LHC12d_S400_GammaCalo_101.root";
            pathDataSets[2] = "/home/daniel/data/work/Grid/Legotrain-vAN-20160309-8TeV-TenderVariations/LHC12d_S600_GammaCalo_101.root";
            pathDataSets[3] = "/home/daniel/data/work/Grid/Legotrain-vAN-20160309-8TeV-TenderVariations/LHC12d_A75_GammaCalo_101.root";
            pathDataSets[4] = "/home/daniel/data/work/Grid/Legotrain-vAN-20160309-8TeV-TenderVariations/LHC12d_A125_GammaCalo_101.root";
            pathDataSets[5] = "/home/daniel/data/work/Grid/Legotrain-vAN-20160309-8TeV-TenderVariations/LHC12d_A150_GammaCalo_101.root";
            pathDataSets[6] = "/home/daniel/data/work/Grid/Legotrain-vAN-20160309-8TeV-TenderVariations/LHC12d_A150_T50_GammaCalo_101.root";
            pathDataSets[7] = "/home/daniel/data/work/Grid/Legotrain-vAN-20160309-8TeV-TenderVariations/LHC12d_T50_GammaCalo_101.root";
            pathDataSets[8] = "/home/daniel/data/work/Grid/Legotrain-vAN-20160309-8TeV-TenderVariations/LHC12d_T100_GammaCalo_101.root";
            pathDataSets[9] = "/home/daniel/data/work/Grid/Legotrain-vAN-20160309-8TeV-TenderVariations/LHC12d_T200_GammaCalo_101.root";
            pathDataSets[10] = "/home/daniel/data/work/Grid/Legotrain-vAN-20160309-8TeV-TenderVariations/LHC12d_T300_GammaCalo_101.root";
            DataSets[0]="LHC12d";
            DataSets[1]="LHC12d";
            DataSets[2]="LHC12d";
            DataSets[3]="LHC12d";
            DataSets[4]="LHC12d";
            DataSets[5]="LHC12d";
            DataSets[6]="LHC12d";
            DataSets[7]="LHC12d";
            DataSets[8]="LHC12d";
            DataSets[9]="LHC12d";
            DataSets[10]="LHC12d";
            plotDataSets[0]="S500/A100/T500";
            plotDataSets[1]="S400";
            plotDataSets[2]="S600";
            plotDataSets[3]="A75";
            plotDataSets[4]="A125";
            plotDataSets[5]="A150";
            plotDataSets[6]="A150/T50";
            plotDataSets[7]="T50";
            plotDataSets[8]="T100";
            plotDataSets[9]="T200";
            plotDataSets[10]="T300";
            pathPhotonQA[0] = "";
            pathPhotonQA[1] = "";
            pathPhotonQA[2] = "";
            pathPhotonQA[3] = "";
            pathPhotonQA[4] = "";
            pathPhotonQA[5] = "";
            pathPhotonQA[6] = "";
            pathPhotonQA[7] = "";
            pathPhotonQA[8] = "";
            pathPhotonQA[9] = "";
            pathPhotonQA[10] = "";
        }
    //**************************************************************************************************************
        else if( select.CompareTo("TenderVariations2") == 0 ){
        //LHC12 Trigger Periodwise
            labelData = "S500/A100";
            mode = 4;
            addSubfolder=kTRUE;
            cutNr = 0;
            nSets = 7;
            fEnergyFlag="8TeV";
            pathDataSets[0] = "/home/daniel/data/work/Grid/Legotrain-vAN-20160401-8TeV-TenderVariations/LHC12d_GammaCalo_101.root";
            pathDataSets[1] = "/home/daniel/data/work/Grid/Legotrain-vAN-20160401-8TeV-TenderVariations/LHC12d_S400_GammaCalo_101.root";
            pathDataSets[2] = "/home/daniel/data/work/Grid/Legotrain-vAN-20160401-8TeV-TenderVariations/LHC12d_S600_GammaCalo_101.root";
            pathDataSets[3] = "/home/daniel/data/work/Grid/Legotrain-vAN-20160401-8TeV-TenderVariations/LHC12d_A50_GammaCalo_101.root";
            pathDataSets[4] = "/home/daniel/data/work/Grid/Legotrain-vAN-20160401-8TeV-TenderVariations/LHC12d_A75_GammaCalo_101.root";
            pathDataSets[5] = "/home/daniel/data/work/Grid/Legotrain-vAN-20160401-8TeV-TenderVariations/LHC12d_A125_GammaCalo_101.root";
            pathDataSets[6] = "/home/daniel/data/work/Grid/Legotrain-vAN-20160401-8TeV-TenderVariations/LHC12d_A150_GammaCalo_101.root";
            DataSets[0]="LHC12d";
            DataSets[1]="LHC12d";
            DataSets[2]="LHC12d";
            DataSets[3]="LHC12d";
            DataSets[4]="LHC12d";
            DataSets[5]="LHC12d";
            DataSets[6]="LHC12d";
            plotDataSets[0]="S500/A100";
            plotDataSets[1]="S400/A100";
            plotDataSets[2]="S600/A100";
            plotDataSets[3]="S500/A50";
            plotDataSets[4]="S500/A75";
            plotDataSets[5]="S500/A125";
            plotDataSets[6]="S500/A150";
            pathPhotonQA[0] = "";
            pathPhotonQA[1] = "";
            pathPhotonQA[2] = "";
            pathPhotonQA[3] = "";
            pathPhotonQA[4] = "";
            pathPhotonQA[5] = "";
            pathPhotonQA[6] = "";
        }
    //**************************************************************************************************************
        else if( select.CompareTo("TenderVariations3") == 0 ){
        //LHC12 Trigger Periodwise
            labelData = "S500/A100/T500";
            mode = 4;
            addSubfolder=kTRUE;
            cutNr = 0;
            nSets = 6;
            fEnergyFlag="8TeV";
            pathDataSets[0] = "/home/daniel/data/work/Grid/Legotrain-vAN-20160309-8TeV-TenderVariations/LHC12d_GammaCalo_101.root";
            pathDataSets[1] = "/home/daniel/data/work/Grid/Legotrain-vAN-20160309-8TeV-TenderVariations/LHC12d_A150_T50_GammaCalo_101.root";
            pathDataSets[2] = "/home/daniel/data/work/Grid/Legotrain-vAN-20160309-8TeV-TenderVariations/LHC12d_T50_GammaCalo_101.root";
            pathDataSets[3] = "/home/daniel/data/work/Grid/Legotrain-vAN-20160309-8TeV-TenderVariations/LHC12d_T100_GammaCalo_101.root";
            pathDataSets[4] = "/home/daniel/data/work/Grid/Legotrain-vAN-20160309-8TeV-TenderVariations/LHC12d_T200_GammaCalo_101.root";
            pathDataSets[5] = "/home/daniel/data/work/Grid/Legotrain-vAN-20160309-8TeV-TenderVariations/LHC12d_T300_GammaCalo_101.root";
            DataSets[0]="LHC12d";
            DataSets[1]="LHC12d";
            DataSets[2]="LHC12d";
            DataSets[3]="LHC12d";
            DataSets[4]="LHC12d";
            DataSets[5]="LHC12d";
            plotDataSets[0]="T500";
            plotDataSets[1]="A150/T50";
            plotDataSets[2]="T50";
            plotDataSets[3]="T100";
            plotDataSets[4]="T200";
            plotDataSets[5]="T300";
            pathPhotonQA[0] = "";
            pathPhotonQA[1] = "";
            pathPhotonQA[2] = "";
            pathPhotonQA[3] = "";
            pathPhotonQA[4] = "";
            pathPhotonQA[5] = "";
        }
    //**************************************************************************************************************
        else if( select.CompareTo("TenderVariations4") == 0 ){
        //LHC12 Trigger Periodwise
            mode = 4;
            addSubfolder=kTRUE;
            cutNr = 0;
            nSets = 2;
            fEnergyFlag="8TeV";
            pathDataSets[0] = "/home/daniel/data/work/Grid/Legotrain-vAN-20160401-8TeV-TenderVariations/LHC12d_GammaCalo_101.root";
            pathDataSets[1] = "/home/daniel/data/work/Grid/Legotrain-vAN-20160401-8TeV-TenderVariations/LHC15h1d_GammaCalo_101.root";
            //pathDataSets[2] = "/home/daniel/data/work/Grid/Legotrain-vAN-20160401-8TeV-TenderVariations/LHC15h2d_GammaCalo_101.root";
            DataSets[0]="LHC12d";
            DataSets[1]="LHC15h1d";
            //DataSets[2]="LHC15h2d";
            plotDataSets[0]="LHC12d";
            plotDataSets[1]="Pythia";
            //plotDataSets[2]="Phojet";
            pathPhotonQA[0] = "";
            pathPhotonQA[1] = "";
            //pathPhotonQA[2] = "";
        }
//**************************************************************************************************************
// TESTING XROOTD
	else if(select.CompareTo("LHC12-XROOTD")==0){
	//LHC12 with/without xROOTd fix
		labelData = "LHC12i, new XrootD";
		nSets = 2;
		fEnergyFlag = "8TeV";
		pathDataSets[0] = "/home/daniel/data/work/Grid/Legotrain-vAN-20150903-LHC12_pass2/GammaConvCalo_LHC12i-pass1_117.root";
		pathDataSets[1] = "/home/daniel/data/work/Grid/Legotrain-vAN-20150903-LHC12_pass2-oldXrootD/GammaConvCalo_LHC12i-pass1_117.root";
		DataSets[0]="LHC12"; DataSets[1]="LHC12";
		plotDataSets[0]="LHC12i"; plotDataSets[1]="LHC12i, old XrootD";
		pathPhotonQA[0] = "";
		pathPhotonQA[1] = "";
	}
//**************************************************************************************************************
	else{
		cout << "No valid selection! Returning..." << endl;
		return;
	}
//**************************************************************************************************************
	if(doEventQA) EventQA(nSets,fEnergyFlag,DataSets,plotDataSets,pathDataSets,mode,cutNr,doExtQA,suffix,labelData,addSubfolder);
	if(doPhotonQA) PhotonQA(nSets,fEnergyFlag,DataSets,plotDataSets,pathPhotonQA,mode,cutNr,doExtQA,suffix,labelData,addSubfolder);
	if(doClusterQA) ClusterQA(nSets,fEnergyFlag,DataSets,plotDataSets,pathDataSets,mode,cutNr,doExtQA,suffix,labelData,addSubfolder);

	return;
}
