#include "ClusterQA.h"

using namespace std;

void ClusterQA_pp(Int_t cutNr = -1, //if -1: you have to choose number at runtime
				  TString select = "LHC12",
				  TString selectEventCut = "")
{
	// global variables
	TString fileData = "";
	TString fileMCPyt = "";
	TString fileMCPho = "";
	TString fPlotData = "";
	TString fPlotMCPyt = "";
	TString fPlotMCPho = "";
	TString DataSet = "";
	TString MCPyt = "";
	TString MCPho = "";
	TString nameMainDir = "";
	TString optionEnergy = "";
	TString cutSel = "";
	TString runNumber = "";
	TString suffix = "eps";
	Bool_t addSubfolder = kFALSE;
	Int_t mode = 2;

	Bool_t doTrigger = kFALSE;

	if(select.CompareTo("LHC11a")==0){
		fileData = "/home/daniel/data/work/Grid/Legotrain-vAN-20150825-ConvCalo/GammaConvCalo_LHC11a-pass4_1.root";
		fileMCPyt = "/home/daniel/data/work/Grid/Legotrain-vAN-20150825-ConvCalo/GammaConvCalo_MC_LHC12f1a_1.root";
		fileMCPho = "/home/daniel/data/work/Grid/Legotrain-vAN-20150825-ConvCalo/GammaConvCalo_MC_LHC12f1b_1.root";
		nameMainDir = "GammaConvCalo";
		optionEnergy = "2.76TeV";
		DataSet = "LHC11a_p4_wSDD";
		fPlotData = "LHC11a";
		MCPyt = "LHC12f1a";
		fPlotMCPyt = "Pythia8";
		MCPho = "LHC12f1b";
		fPlotMCPho = "Phojet";
	}else if(select.CompareTo("LHC11a-kEMC1")==0){
		doTrigger = kTRUE;
		fileData = "/home/daniel/data/work/Grid/Legotrain-vAN-20150825-ConvCalo/GammaConvCalo_LHC11a-pass4_1.root";
		nameMainDir = "GammaConvCalo";
		optionEnergy = "2.76TeV";
		DataSet = "LHC11a_p4_wSDD-kEMC1";
		fPlotData = "LHC11a";
		cutSel = "00051113_00200009327000008250400000_1111121053032230000_0163103100000010";
	}else if(select.CompareTo("LHC15-JJ")==0){
		fileData = "/home/daniel/data/work/Grid/Legotrain-vAN-20150720-EvsM02/GammaConvCalo_23.root";
		nameMainDir = "GammaConvCalo_23";
		optionEnergy = "2.76TeV";
		DataSet = "LHC15a3";
		fPlotData = "LHC15a3a+b";
		cutSel = "0000011_00200009327000008250400000_11111063032200000_0163103100000000";
	}else if(select.CompareTo("LHC13g-11")==0){
		fileData = "/home/daniel/data/work/Grid/Legotrain-vAN-20150601-ConvCalo/GammaConvCalo_LHC13g-pass3_11.root";
		nameMainDir = "GammaConvCalo";
		optionEnergy = "2.76TeV";
		DataSet = "LHC13g";
		fPlotData = "LHC13g";
		cutSel = "0008311_00200009327000008250400000_10000053032230000_01631031000000";
	}else if(select.CompareTo("LHC13g-kEMCEG1")==0){
		fileData = "/home/daniel/data/work/Grid/Legotrain-vAN-20150825-ConvCalo/GammaConvCalo_LHC13g-pass3_95.root";
		nameMainDir = "GammaConvCalo";
		optionEnergy = "2.76TeV";
		DataSet = "LHC13g-kEMCEG1";
		fPlotData = "LHC13g";
		cutSel = "00083113_00200009327000008250400000_1111121063032230000_0163103100000010";
	}else if(select.CompareTo("LHC13g-kEMCEG2")==0){
		fileData = "/home/daniel/data/work/Grid/Legotrain-vAN-20150825-ConvCalo/GammaConvCalo_LHC13g-pass3_95.root";
		nameMainDir = "GammaConvCalo";
		optionEnergy = "2.76TeV";
		DataSet = "LHC13g-kEMCEG2";
		fPlotData = "LHC13g";
		cutSel = "00085113_00200009327000008250400000_1111121063032230000_0163103100000010";
	}else if(select.CompareTo("LHC13g")==0){
		fileData = "/home/daniel/data/work/Grid/Legotrain-vAN-20150825-ConvCalo/GammaConvCalo_LHC13g-pass3_96.root";
		nameMainDir = "GammaConvCalo";
		optionEnergy = "2.76TeV";
		DataSet = "LHC13g";
		fPlotData = "LHC13g";
		cutSel = "00000113_00200009327000008250400000_1111121063032230000_0163103100000010";
//	}else if(select.CompareTo("LHC13c")==0){
//		fileData = "/home/daniel/data/work/Grid/Legotrain-vAN-20150720_LHC13c/GammaCalo_3.root";
//		nameMainDir = "GammaCalo_3";
//		optionEnergy = "pPb_5.023TeV";
//		DataSet = "LHC13c";
//		mode = 4;
//		fPlotData = "LHC13c";
//		cutSel = "8000001_11111050032230000_0163103100000000";
	}else if(select.CompareTo("LHC13g-kEMC7")==0){
		fileData = "/home/daniel/data/work/Grid/Legotrain-vAN-20150825-ConvCalo/GammaConvCalo_LHC13g-pass3_96.root";
		nameMainDir = "GammaConvCalo";
		optionEnergy = "2.76TeV";
		DataSet = "LHC13g-kEMC7";
		fPlotData = "LHC13g";
		cutSel = "00052113_00200009327000008250400000_1111121063032230000_0163103100000010";
	}else if(select.CompareTo("LHC12")==0){
		fileData = "/home/daniel/data/work/Grid/Legotrain-vAN-20150728-LHC12_QA-2nd/GammaConvCalo_LHC12abcdfghi-pass1_120.root";
		fileMCPyt = "/home/daniel/data/work/Grid/Legotrain-vAN-20150728-LHC12_QA-2nd/GammaConvCalo_MC_LHC14e2a_120.root";
		fileMCPho = "/home/daniel/data/work/Grid/Legotrain-vAN-20150728-LHC12_QA-2nd/GammaConvCalo_MC_LHC14e2c_120.root";
//		fileData = "/home/daniel/data/work/photonconv/AnalysisSoftware/DataQA/20150624/LHC12.root";
//		fileMCPyt = "/home/daniel/data/work/photonconv/AnalysisSoftware/DataQA/20150624/LHC14e2a-pass1_120.root";
//		fileMCPho = "/home/daniel/data/work/photonconv/AnalysisSoftware/DataQA/20150624/LHC14e2c-pass1_120.root";
		nameMainDir = "GammaConvCalo";
		optionEnergy = "8TeV";
		DataSet = "LHC12";
		fPlotData = "LHC12a-i, V0AND";
		MCPyt = "LHC14e2a";
		fPlotMCPyt = "Pythia8";
		MCPho = "LHC14e2c";
		fPlotMCPho = "Phojet";
	}else if(select.BeginsWith("LHC12") && select.Length()==6){
		addSubfolder=kTRUE;
		fileData = Form("/home/daniel/data/work/Grid/Legotrain-vAN-20150728-LHC12_QA-2nd/GammaConvCalo_%s-pass1_120.root",select.Data());
		fileMCPyt = Form("/home/daniel/data/work/Grid/Legotrain-vAN-20150728-LHC12_QA-2nd/GammaConvCalo_MC_LHC14e2a-%s_120.root",select.Data());
		fileMCPho = Form("/home/daniel/data/work/Grid/Legotrain-vAN-20150728-LHC12_QA-2nd/GammaConvCalo_MC_LHC14e2c-%s_120.root",select.Data());
//		fileData = Form("/home/daniel/data/work/photonconv/AnalysisSoftware/DataQA/20150624/%s-pass1_120.root",select.Data());
//		fileMCPyt = Form("/home/daniel/data/work/photonconv/AnalysisSoftware/DataQA/20150624/LHC14e2a-%s-pass1_120.root",select.Data());
//		fileMCPho = Form("/home/daniel/data/work/photonconv/AnalysisSoftware/DataQA/20150624/LHC14e2c-%s-pass1_120.root",select.Data());
		nameMainDir = "GammaConvCalo";
		optionEnergy = "8TeV";
		DataSet = select;
		fPlotData = Form("%s, V0AND",select.Data());
		MCPyt = Form("LHC14e2a-%s",select.Data());
		fPlotMCPyt = "Pythia8";
		MCPho = Form("LHC14e2c-%s",select.Data());
		fPlotMCPho = "Phojet";
	}else if(select.BeginsWith("LHC12-kEMC")){
		doTrigger = kTRUE;
		TString number = "";
		if(select.EndsWith("-kEMC7")) number = "121";
		if(select.EndsWith("-kEMCEGA")) number = "122";
		if(select.EndsWith("-kEMCEJE")) number = "123";
		fileData = Form("/home/daniel/data/work/Grid/Legotrain-vAN-20150625/GammaConvCalo_LHC12abcdfghi-pass1_%s.root",number.Data());
		nameMainDir = "GammaConvCalo";
		optionEnergy = "8TeV";
		if(select.EndsWith("-kEMC7"))DataSet = "LHC12-kEMC7";
		if(select.EndsWith("-kEMCEGA"))DataSet = "LHC12-kEMCEGA";
		if(select.EndsWith("-kEMCEJE"))DataSet = "LHC12-kEMCEJE";
		fPlotData = "LHC12";
		cutSel = "0005211_00200009327000008250400000_10000063032230000_0163103100000000";
		if(select.EndsWith("-kEMCEGA")) selectEventCut = "0008111";
		if(select.EndsWith("-kEMCEJE")) selectEventCut = "0009111";
	}else if(!select.BeginsWith("LHC12-kEMC") && select.BeginsWith("LHC12") && select.Contains("-kEMC")){
		addSubfolder=kTRUE;
		doTrigger = kTRUE;
		TString number = "";
		TString selectResize = select;
		selectResize.Resize(6);
		if(select.EndsWith("-kEMC7")) number = "121";
		if(select.EndsWith("-kEMCEGA")) number = "122";
		if(select.EndsWith("-kEMCEJE")) number = "123";
		fileData = Form("/home/daniel/data/work/Grid/Legotrain-vAN-20150625/GammaConvCalo_%s-pass1_%s.root",selectResize.Data(),number.Data());
		nameMainDir = "GammaConvCalo";
		optionEnergy = "8TeV";
		DataSet = select;
		fPlotData = selectResize;
		cutSel = "0005211_00200009327000008250400000_10000063032230000_0163103100000000";
		if(select.EndsWith("-kEMCEGA")) selectEventCut = "0008111";
		if(select.EndsWith("-kEMCEJE")) selectEventCut = "0009111";
	}

	else{ cout << "Could not find requested data set: " << select.Data() << ", returning..." << endl; return;}

    cout << "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;
    cout << "ClusterQA_pp" << endl;
    cout << "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;

    gROOT->Reset();

    StyleSettingsThesis();
    SetPlotStyle();

    Bool_t isRunNum = kFALSE;
    if( runNumber.CompareTo("")!=0 ) isRunNum = kTRUE;

	TString fPrefixData = DataSet;
	TString fPrefixMCPyt = MCPyt;
	TString fPrefixMCPho = MCPho;
	TString fComparison("Comparison");

    Bool_t isMCPytFile = kTRUE;
    Bool_t isMCPhoFile = kTRUE;
    Bool_t isDataFile = kTRUE;
    TFile* fMCPyt = new TFile(fileMCPyt.Data());
    TFile* fMCPho = new TFile(fileMCPho.Data());
    TFile* fData = new TFile(fileData.Data());

    if(fMCPyt->IsZombie()) {isMCPytFile=kFALSE; cout << "Info: MC-Pythia file " << fileMCPyt.Data() << " could not be openend!" << endl;}
    else {cout << "Processing MC file: " << fileMCPyt.Data() << endl;}
    if(fMCPho->IsZombie()) {isMCPhoFile=kFALSE; cout << "Info: MC-Phojet file " << fileMCPho.Data() << " could not be openend!" << endl;}
    else {cout << "Processing MC file: " << fileMCPho.Data() << endl;}
	if(fData->IsZombie()) {isDataFile=kFALSE; cout << "ERROR: Data file " << fileData.Data() << " could not be openend! Returning..." << endl; return;}
    else {cout << "Processing data file: " << fileData.Data() << endl;}
    if(fMCPyt->IsZombie() && fMCPho->IsZombie() && fData->IsZombie()) {cout << "ERROR, MC files: " << fileMCPyt.Data() << ", " << fileMCPho.Data() << ", and data file " << fileData.Data() << " could not be openend! Returning..." << endl; return;}

	if(isRunNum){fPlotData+=", Run "; fPlotData+=runNumber;}

    Int_t fMode = mode;
	// mode:	0 // new output PCM-PCM
	//			1 // new output PCM dalitz
	//			2 // new output PCM-EMCal
	//			3 // new output PCM-PHOS
	//          4 // new output EMCal-EMCal
	//          5 // new output PHOS-PHOS
	//			9 // old output PCM-PCM
    if(fMode == 0 || fMode == 1 || fMode == 9){
        cout << "Returning, given mode contains no calo information: " << fMode << endl;
        return;
    }

    if(nameMainDir.IsNull() || !nameMainDir.BeginsWith("Gamma")){cout << "ERROR, Unable to obtain valid name of MainDir:|" << nameMainDir.Data() << "|, running in mode: " << fMode << endl; return;}

//****************************** Collecting Cuts from MC/Data-Files ************************************************

	TString fCutSelection[3];
    cout << "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;

    if(cutSel.CompareTo("")==0)
    {
        TList *listInputMCPyt =(TList*)fMCPyt->Get(nameMainDir.Data());
        TList *listInputMCPho =(TList*)fMCPho->Get(nameMainDir.Data());
        TList *listInputData =(TList*)fData->Get(nameMainDir.Data());
        vector <TString> cutsMCPyt;
        vector <TString> cutsMCPho;
        vector <TString> cutsData;
        for(Int_t i = 0; i<listInputData->GetSize(); i++){
            TList *listMCPyt = (TList*)listInputMCPyt->At(i);
            TList *listMCPho = (TList*)listInputMCPho->At(i);
            TList *listData = (TList*)listInputData->At(i);
            TString nameMCPyt = listMCPyt->GetName();
            TString nameMCPho = listMCPho->GetName();
            TString nameData = listData->GetName();
            if(nameMCPyt.BeginsWith("Cut Number") && nameMCPho.BeginsWith("Cut Number") && nameData.BeginsWith("Cut Number")){
                nameMCPyt.Replace(0,11,"");
                nameMCPho.Replace(0,11,"");
                nameData.Replace(0,11,"");
                cutsMCPyt.push_back(nameMCPyt);
                cutsMCPho.push_back(nameMCPho);
                cutsData.push_back(nameData);
				if(nameMCPyt.CompareTo(nameMCPho)){cout << "INFO: No identical Cuts in MC Pythia/Phojet: " << nameMCPyt.Data() << ", : " << nameMCPho.Data() << ", maybe processing different time cuts?" << endl;}
				if(nameMCPyt.CompareTo(nameData)){cout << "INFO: No identical Cuts in MC/Data, MC: " << nameMCPyt.Data() << ", Data: " << nameData.Data() << ", maybe processing different time cuts?" << endl;}
				//ignoring time cut by cutting it out from cut-array
				nameMCPyt.Replace(41,1,"");
				nameMCPho.Replace(41,1,"");
				nameData.Replace(41,1,"");
				if(nameMCPyt.CompareTo(nameMCPho)){cout << "ERROR: No identical Cuts in MC Pythia/Phojet: " << nameMCPyt.Data() << ", : " << nameMCPho.Data() << ", returning..." << endl; return;}
				if(nameMCPyt.CompareTo(nameData)){cout << "ERROR: No identical Cuts in MC/Data, MC: " << nameMCPyt.Data() << ", Data: " << nameData.Data() << ", returning..." << endl; return;}
            }
        }

        cout << "The following cuts are available:" << endl;
		for(Int_t i = 0; i < (Int_t) cutsData.size(); i++) {cout << Form("(%i) -- %s", i, cutsData[i].Data()) << endl;}

        if(cutNr == -1){
            do{ cin >> cutNr;}
			while( (cutNr < 0) || (cutNr > (Int_t) cutsData.size()) );
        }

        cout << "Processing Cut Number: " << cutNr << endl;
		fCutSelection[2] = cutsData.at(cutNr);
		fCutSelection[0] = cutsMCPyt.at(cutNr);
		fCutSelection[1] = cutsMCPho.at(cutNr);
    }
    else
    {
		if(selectEventCut.CompareTo("")!=0){
			cutSel.Remove(0,7);
			selectEventCut+=cutSel;
			fCutSelection[0] = selectEventCut;
			fCutSelection[1] = selectEventCut;
			fCutSelection[2] = selectEventCut;
		}else{
			fCutSelection[0] = cutSel;
			fCutSelection[1] = cutSel;
			fCutSelection[2] = cutSel;
		}
    }


	cout << "Data: " << fCutSelection[2].Data() << endl;
	cout << "MC-Pythia: " << fCutSelection[0].Data() << endl;
	cout << "MC-Phojet: " << fCutSelection[1].Data() << endl;
    cout << "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;
    cout << "Pictures are saved as " << suffix.Data() << "!" << endl;
    cout << "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;

//****************************** Global Variables ************************************************

    TString TrackMatchingEtaMax[10] = {"0","0.008", "0.012", "0.016", "0.018", "0.02", "0.022", "0.005", "0.01", "0.015"};
    TString TrackMatchingPhiMin[10] = {"0","-0.03", "-0.05", "-0.09", "-0.11", "-0.13", "-0.15", "-0.03", "-0.09", "-0.15"};
    TString TrackMatchingPhiMax[10] = {"0","0.03", "0.04", "0.06", "0.07", "0.08", "0.1", "0.03", "0.07", "0.11"};

    TString fEnergyFlag = optionEnergy;
    TString fDate = ReturnDateString();
    TString fTextMeasurement = Form("#pi^{0} #rightarrow #gamma#gamma");
    TString fTextMeasurementEta = Form("#eta #rightarrow #gamma#gamma");
	TString fTextMeasurementMeson[2]={fTextMeasurement,fTextMeasurementEta};

    TString fCollisionSystem = ReturnFullCollisionsSystem(fEnergyFlag);
    if (fCollisionSystem.CompareTo("") == 0){
        cout << "No correct collision system specification, has been given" << endl;
        return;
    }

    TString fDetectionProcess = ReturnFullTextReconstructionProcess(fMode);

	TString fEventCutSelection[3], fGammaCutSelection[3], fClusterCutSelection[3], fElectronCutSelection[3], fMesonCutSelection[3];
	ReturnSeparatedCutNumberAdvanced(fCutSelection[0], fEventCutSelection[0], fGammaCutSelection[0], fClusterCutSelection[0], fElectronCutSelection[0], fMesonCutSelection[0], fMode);
	ReturnSeparatedCutNumberAdvanced(fCutSelection[1], fEventCutSelection[1], fGammaCutSelection[1], fClusterCutSelection[1], fElectronCutSelection[1], fMesonCutSelection[1], fMode);
	ReturnSeparatedCutNumberAdvanced(fCutSelection[2], fEventCutSelection[2], fGammaCutSelection[2], fClusterCutSelection[2], fElectronCutSelection[2], fMesonCutSelection[2], fMode);

	if(doTrigger){
		cout << "Obtaining trigger cut: ";
		TString fTriggerCut = fEventCutSelection[0](3,2);
		TString fTrigger = AnalyseSpecialTriggerCut(fTriggerCut.Atoi(), DataSet);
		fPlotData += Form("-%s",fTrigger.Data());
		cout << fTrigger.Data() << " was found!" << endl;
		if(fPlotData.EndsWith("defined")){ cout << "ERROR, Trigger cut not defined, check settings of macro!, returning..." << endl; return;}
	}

    TString calo;
    Int_t iCalo = 0;
	Int_t nCaloModules = 0;
	Int_t nCaloCells = 0;
	if(fClusterCutSelection[2].BeginsWith('1')){
		calo="EMCal"; iCalo=1;
		nCaloModules = 10;
		nCaloCells = 11520;
	}else if(fClusterCutSelection[2].BeginsWith('2')){
        calo="PHOS"; iCalo=2;
		nCaloModules = 5;
		nCaloCells = 6000;
    }else {cout << "No correct calorimeter type found: " << calo.Data() << ", returning..." << endl; return;}

    TList* TopDirMCPyt = new TList();
    TList *TopContainerMCPyt = new TList();
    TList *CaloCutsContainerMCPyt = new TList();
	TList *CaloExtQAContainerMCPyt = new TList();
    if(isMCPytFile){
        TopDirMCPyt =(TList*)fMCPyt->Get(nameMainDir.Data());
            if(TopDirMCPyt == NULL) {cout<<"ERROR: TopDirMCPyt not Found"<<endl; return;}
		TopContainerMCPyt = (TList*) TopDirMCPyt->FindObject(Form("Cut Number %s",fCutSelection[0].Data()));
			if(TopContainerMCPyt == NULL) {cout << "ERROR: " << Form("Cut Number %s",fCutSelection[0].Data()) << " not found in File" << endl; return;}
		CaloCutsContainerMCPyt = (TList*) TopContainerMCPyt->FindObject(Form("CaloCuts_%s",fClusterCutSelection[0].Data()));
			if(CaloCutsContainerMCPyt == NULL) {cout << "ERROR: " << Form("CaloCuts_%s",fClusterCutSelection[0].Data()) << " not found in File" << endl; return;}
		CaloExtQAContainerMCPyt = (TList*) TopContainerMCPyt->FindObject(Form("CaloExtQA_%s",fClusterCutSelection[0].Data()));
			if(CaloExtQAContainerMCPyt == NULL) {
				cout << "WARNING: " << Form("CaloExtQA_%s",fClusterCutSelection[0].Data()) << " not found in File, using CaloCuts-Container" << endl;
				CaloExtQAContainerMCPyt = CaloCutsContainerMCPyt;
			}
    }

    TList* TopDirMCPho = new TList();
    TList *TopContainerMCPho = new TList();
    TList *CaloCutsContainerMCPho = new TList();
	TList *CaloExtQAContainerMCPho = new TList();
    if(isMCPhoFile){
        TopDirMCPho =(TList*)fMCPho->Get(nameMainDir.Data());
            if(TopDirMCPho == NULL) {cout<<"ERROR: TopDirMCPho not Found"<<endl; return;}
		TopContainerMCPho = (TList*) TopDirMCPho->FindObject(Form("Cut Number %s",fCutSelection[1].Data()));
			if(TopContainerMCPho == NULL) {cout << "ERROR: " << Form("Cut Number %s",fCutSelection[1].Data()) << " not found in File" << endl; return;}
		CaloCutsContainerMCPho = (TList*) TopContainerMCPho->FindObject(Form("CaloCuts_%s",fClusterCutSelection[1].Data()));
			if(CaloCutsContainerMCPho == NULL) {cout << "ERROR: " << Form("CaloCuts_%s",fClusterCutSelection[1].Data()) << " not found in File" << endl; return;}
		CaloExtQAContainerMCPho = (TList*) TopContainerMCPho->FindObject(Form("CaloExtQA_%s",fClusterCutSelection[1].Data()));
		if(CaloExtQAContainerMCPho == NULL) {
			cout << "WARNING: " << Form("CaloExtQA_%s",fClusterCutSelection[1].Data()) << " not found in File, using CaloCuts-Container" << endl;
			CaloExtQAContainerMCPho = CaloCutsContainerMCPho;
		}
	}

    TList* TopDirData = new TList();
    TList* TopContainerData = new TList();
	TList* CaloCutsContainerData = new TList();
	TList* CaloExtQAContainerData = new TList();
    if(isDataFile){
        TopDirData =(TList*)fData->Get(nameMainDir.Data());
            if(TopDirData == NULL) {cout<<"ERROR: TopDirData not Found"<<endl; return;}
		TopContainerData = (TList*) TopDirData->FindObject(Form("Cut Number %s",fCutSelection[2].Data()));
			if(TopContainerData == NULL) {cout << "ERROR: " << Form("Cut Number %s",fCutSelection[2].Data()) << " not found in File" << endl; return;}
		CaloCutsContainerData = (TList*) TopContainerData->FindObject(Form("CaloCuts_%s",fClusterCutSelection[2].Data()));
			if(CaloCutsContainerData == NULL) {cout << "ERROR: " << Form("CaloCuts_%s",fClusterCutSelection[2].Data()) << " not found in File" << endl; return;}
		CaloExtQAContainerData = (TList*) TopContainerData->FindObject(Form("CaloExtQA_%s",fClusterCutSelection[2].Data()));
		if(CaloExtQAContainerData == NULL) {
			cout << "WARNING: " << Form("CaloExtQA_%s",fClusterCutSelection[2].Data()) << " not found in File, using CaloCuts-Container" << endl;
			CaloExtQAContainerData = CaloCutsContainerData;
		}
	}

	TString outputDir = Form("%s/%s/ClusterQA/%s",fCutSelection[2].Data(),fEnergyFlag.Data(),suffix.Data());
	if(addSubfolder) outputDir+=Form("/%s",DataSet.Data());
    if(isRunNum) {
		outputDir+=Form("/RunwiseQA/%s/%s", fPrefixData.Data(), runNumber.Data());
        gSystem->Exec("mkdir -p "+outputDir);
		gSystem->Exec("mkdir -p "+outputDir+"/Cells");
		gSystem->Exec("mkdir -p "+outputDir+"/Cells/Detailed");
    }
    else{
        gSystem->Exec("mkdir -p "+outputDir);
		gSystem->Exec("mkdir -p "+outputDir+"/"+fComparison);
		gSystem->Exec("mkdir -p "+outputDir+"/Cells");
		gSystem->Exec("mkdir -p "+outputDir+"/Cells/Detailed");
    }

	fstream fLog;
	fLog.open(Form("%s/A-%s.log",outputDir.Data(),DataSet.Data()), ios::out);
	fLog << "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;
	if(isDataFile)fLog << "dataFile: " << fileData.Data() << endl; else fLog << "no dataFile specified!" << endl;
	if(isMCPytFile)fLog << "mcFile1: " << fileMCPyt.Data() << endl; else fLog << "no MCPytFile specified!" << endl;
	if(isMCPhoFile)fLog << "mcFile2: " << fileMCPho.Data() << endl; else fLog << "no MCPhoFile specified!" << endl;
	fLog << "Energy: " << optionEnergy.Data() << endl;
	fLog << fCollisionSystem.Data() << endl;
	fLog << "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;
	fLog << "processed cut: " << fCutSelection[2].Data() << endl;
	fLog << calo.Data() << ", Modules: " << nCaloModules << ", Cells: " << nCaloCells << endl;

//****************************** Histograms from Task ************************************************

	TH1F *fHistNEvents                          = NULL; // bookkeeping of NEvents
    TH1F *fHistCutIndex                         = NULL; // bookkeeping for cuts
    TH1F *fHistAcceptanceCuts                   = NULL; // bookkeeping for acceptance cuts
    TH1F *fHistClusterIdentificationCuts        = NULL; // bookkeeping for cluster identification cuts
	TH1F *fHistVertexZ							= NULL; // vertex Z

    TH2F* fHistClusterEtavsPhiBeforeAcc         = NULL; // eta-phi-distribution before acceptance cuts
    TH2F* fHistClusterEtavsPhiAfterAcc          = NULL;	// eta-phi-distribution of all after acceptance cuts
    TH2F* fHistClusterEtavsPhiAfterQA           = NULL; // eta-phi-distribution of all after cluster quality cuts
    TH1F* fHistDistanceToBadChannelBeforeAcc    = NULL; // distance to bad channel before acceptance cuts
    TH1F* fHistDistanceToBadChannelAfterAcc     = NULL; // distance to bad channel after acceptance cuts
    TH2F* fHistClusterTimevsEBeforeQA           = NULL;	// Cluster time vs E before cluster quality cuts
    TH2F* fHistClusterTimevsEAfterQA            = NULL; // Cluster time vs E after cluster quality cuts
    TH2F* fHistExoticCellBeforeQA               = NULL;	// Exotic cell: 1-Ecross/E cell vs Ecluster before acceptance cuts
    TH2F* fHistExoticCellAfterQA                = NULL;	// Exotic cell: 1-Ecross/E cell vs Ecluster after cluster quality cuts
    TH1F* fHistNMatchedTracks                   = NULL;	// number of matched tracks
    TH1F* fHistEnergyOfClusterBeforeQA          = NULL; // enery per cluster before acceptance cuts
    TH1F* fHistEnergyOfClusterAfterQA           = NULL;	// enery per cluster after cluster quality cuts
    TH1F* fHistNCellsBeforeQA                   = NULL;	// number of cells per cluster before acceptance cuts
    TH1F* fHistNCellsAfterQA                    = NULL;	// number of cells per cluster after cluster quality cuts
    TH1F* fHistM02BeforeQA                      = NULL;	// M02 before acceptance cuts
    TH1F* fHistM02AfterQA                       = NULL;	// M02 after cluster quality cuts
    TH1F* fHistM20BeforeQA                      = NULL;	// M20 before acceptance cuts
    TH1F* fHistM20AfterQA                       = NULL;	// M20 after cluster quality cuts
    TH1F* fHistDispersionBeforeQA               = NULL; // dispersion before acceptance cuts
    TH1F* fHistDispersionAfterQA                = NULL;	// dispersion after cluster quality cuts
    TH1F* fHistNLMBeforeQA                      = NULL;	// number of local maxima in cluster before acceptance cuts
    TH1F* fHistNLMAfterQA                       = NULL;	// number of local maxima in cluster after cluster quality cuts

    //Track Matching Histograms
    TH1F* fHistClusterRBeforeQA                 = NULL;	// cluster position in R=SQRT(x^2+y^2) (before QA)
    TH1F* fHistClusterRAfterQA                  = NULL;	// cluster position in R=SQRT(x^2+y^2) for matched tracks (After QA)
    TH2F* fHistClusterdEtadPhiBeforeQA          = NULL; // 2-dim plot dEta vs. dPhi
    TH2F* fHistClusterdEtadPhiAfterQA           = NULL;	// 2-dim plot dEta vs. dPhi for matched tracks (after QA)
    TH1F* fHistDistanceTrackToClusterBeforeQA   = NULL; // distance cluster to track before acceptance cuts
    TH1F* fHistDistanceTrackToClusterAfterQA    = NULL; // distance cluster to track after cluster quality cuts

    //Extended track matching histograms
    TH2F* fHistClusterdEtadPhiPosTracksBeforeQA = NULL; // 2-dim plot dEta vs. dPhi
    TH2F* fHistClusterdEtadPhiNegTracksBeforeQA = NULL; // 2-dim plot dEta vs. dPhi
    TH2F* fHistClusterdEtadPhiPosTracksAfterQA  = NULL;	// 2-dim plot dEta vs. dPhi
    TH2F* fHistClusterdEtadPhiNegTracksAfterQA  = NULL;	// 2-dim plot dEta vs. dPhi
	TH2F* fHistClusterdEtadPhiPosTracksP_000_075BeforeQA = NULL; // 2-dim plot dEta vs. dPhi, positive Tracks, P < 0.75
	TH2F* fHistClusterdEtadPhiPosTracksP_075_125BeforeQA = NULL; // 2-dim plot dEta vs. dPhi, positive Tracks, 0.75 < P < 1.25
	TH2F* fHistClusterdEtadPhiPosTracksP_125_999BeforeQA = NULL; // 2-dim plot dEta vs. dPhi, positive Tracks, P > 1.25
	TH2F* fHistClusterdEtadPhiNegTracksP_000_075BeforeQA = NULL; // 2-dim plot dEta vs. dPhi, negative Tracks, P < 0.75
	TH2F* fHistClusterdEtadPhiNegTracksP_075_125BeforeQA = NULL; // 2-dim plot dEta vs. dPhi, negative Tracks, 0.75 < P < 1.25
	TH2F* fHistClusterdEtadPhiNegTracksP_125_999BeforeQA = NULL; // 2-dim plot dEta vs. dPhi, negative Tracks, P > 1.25
    TH2F* fHistClusterdEtadPtBeforeQA           = NULL; // 2-dim plot dEta vs. Pt
    TH2F* fHistClusterdPhidPtBeforeQA           = NULL; // 2-dim plot dEta vs. Pt
	TH2F* fHistClusterTrueGammaEM02				= NULL;	// 2-dim plot E vs. M02 for TrueGamma
	TH2F* fHistClusterTruePi0EM02				= NULL;	// 2-dim plot E vs. M02 for TruePi0
	TH2F* fHistClusterM20M02BeforeQA            = NULL; // 2-dim plot M20 vs. M02
	TH2F* fHistClusterM20M02AfterQA             = NULL; // 2-dim plot M20 vs. M20

	//Extended QA histograms
	TH1F* fHistClusterCellIDsBeforeQA			= NULL;
	TH1F* fHistClusterCellIDsAfterQA			= NULL;
	TH1F* fHistClusterCellEFracBeforeQA			= NULL;
	TH1F* fHistClusterCellEFracAfterQA			= NULL;
	TH2F* fHistClusterEM02BeforeQA				= NULL; // 2-dim plot E vs. M02
	TH2F* fHistClusterEM02AfterQA				= NULL; // 2-dim plot E vs. M02
	TH2F* fHistClusterEnergyVsModule			= NULL;
	TH2F* fHistClusterEnergyVsNCells			= NULL;
	TH2F* fHistModuleEnergyVsModule				= NULL;
	TH2F* fHistNCellsAbove100VsModule			= NULL;
	TH2F* fHistNCellsAbove1500VsModule			= NULL;
	TH2F* fHistCellEnergyVsCellID				= NULL;
	TH2F* fHistCellTimeVsCellID					= NULL;
	TProfile* fEMCalBadChannels					= NULL;

//****************************** Generated Histograms in This Script ************************************************

	TH1D* fHistClusterTimeBeforeQA				= NULL;
	TH1D* fHistClusterTimeAfterQA				= NULL;
    // Projection of Track Matching Histograms onto Eta/Phi-Axis
    TH1D* fHistClusterdEtaPosTracksBeforeQA     = NULL;
    TH1D* fHistClusterdPhiPosTracksBeforeQA     = NULL;
    TH1D* fHistClusterdEtaPosTracksAfterQA      = NULL;
    TH1D* fHistClusterdPhiPosTracksAfterQA      = NULL;
    TH1D* fHistClusterdEtaNegTracksBeforeQA     = NULL;
    TH1D* fHistClusterdPhiNegTracksBeforeQA     = NULL;
    TH1D* fHistClusterdEtaNegTracksAfterQA      = NULL;
    TH1D* fHistClusterdPhiNegTracksAfterQA      = NULL;
    TH1D* fHistClusterdEtaBeforeQA              = NULL;
    TH1D* fHistClusterdPhiBeforeQA              = NULL;
    TH1D* fHistClusterdEtaAfterQA               = NULL;
    TH1D* fHistClusterdPhiAfterQA               = NULL;

    TH2F* fHistClusterdEtadPhiMatchedAfterQA    = NULL;
    TH1D* fHistClusterdEtaMatchedAfterQA        = NULL;
    TH1D* fHistClusterdPhiMatchedAfterQA        = NULL;
    TH1F* fHistDistanceTrackToClusterMatchedAfterQA = NULL;
    TH2F* fHistClusterM20M02MatchedAfterQA      = NULL;

    TH2D* fHistInvMassPtMotherMotherMatched     = NULL;
	TH2D* fHistInvMassPtMotherMatchedCompare_Matched_True    = NULL;
	TH2D* fHistInvMassPtMotherMatchedCompare_Matched_MC    = NULL;
	TH2D* fHistInvMassPtMotherMatchedCompare_True_MC    = NULL;

	TH2D* MotherPi0Conv_Eta_Phi					= NULL;
	TH1D* MotherPi0Conv_Phi						= NULL;
	TH1D* MotherPi0Conv_Eta						= NULL;
	TH2D* MotherEtaConv_Eta_Phi					= NULL;
	TH1D* MotherEtaConv_Phi						= NULL;
	TH1D* MotherEtaConv_Eta						= NULL;

//****************************** Histograms for MC/Data ************************************************
// Binning for cluster energy histograms
	const Int_t fNBinsClusterPt 			= 60;
	Double_t fBinsClusterPt[fNBinsClusterPt+1] = {0.0, 0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9,
										 1.0, 1.1, 1.2, 1.3, 1.4, 1.5, 1.6, 1.7, 1.8, 1.9,
										 2.0, 2.2, 2.4, 2.6, 2.8, 3.0, 3.2, 3.4, 3.6, 3.8,
										 4.0, 4.2, 4.4, 4.6, 4.8, 5.0, 5.2, 5.4, 5.6, 5.8,
										 6.0, 6.2, 6.4, 6.6, 6.8, 7.0, 7.4, 7.8, 8.2, 8.6,
										 9.0, 9.5, 10, 11, 12, 14, 16, 18, 20, 25, 30};

	TH1D* fDeltaPt = new TH1D("deltaPt","",fNBinsClusterPt,fBinsClusterPt);
	for(Int_t iPt=1;iPt<fNBinsClusterPt+1;iPt++){
		fDeltaPt->SetBinContent(iPt,fBinsClusterPt[iPt]-fBinsClusterPt[iPt-1]);
		fDeltaPt->SetBinError(iPt,0);
	}

	const Int_t fNBins2760GeVPt = 16;
	Double_t fBins2760GeVPt[fNBins2760GeVPt+1] = {0.6, 0.8, 1.0,
							   1.2, 1.4, 1.6, 1.8, 2.0,
							   2.2, 2.4, 2.6, 3.0, 3.5,
							   4.0, 5.0, 6.0, 8.0};

	const Int_t fNBins8000GeVPt = 25;
	Double_t fBins8000GeVPt[fNBins8000GeVPt+1] = {0.6, 0.8, 1.0,
							   1.2, 1.4, 1.6, 1.8, 2.0,
							   2.2, 2.4, 2.6, 2.8, 3.0,
							   3.2, 3.4, 3.6, 3.8, 4.0,
							   4.5, 5.0, 5.5, 6.0, 7.0,
							   8.0, 10.0, 12.0};

	const Int_t fNBins8000GeVTriggerPt = 29;
	Double_t fBins8000GeVTriggerPt[fNBins8000GeVTriggerPt+1] = {0.6, 0.8, 1.0,
							   1.2, 1.4, 1.6, 1.8, 2.0,
							   2.2, 2.4, 2.6, 2.8, 3.0,
							   3.2, 3.4, 3.6, 3.8, 4.0,
							   4.5, 5.0, 5.5, 6.0, 7.0,
							   8.0, 10.0, 12.0, 16.0, 20.0, 25.0, 30.0};

	Int_t fNBinsAnalysisPt = 0;
	Double_t* fBinsAnalysisPt = 0x0;
	if(select.BeginsWith("LHC11") || select.BeginsWith("LHC13") || select.CompareTo("LHC12i3")==0){
		fNBinsAnalysisPt = fNBins2760GeVPt;
		fBinsAnalysisPt = new Double_t[fNBinsAnalysisPt+1];
		for(Int_t iB=0; iB<fNBinsAnalysisPt+1; iB++) {fBinsAnalysisPt[iB] = fBins2760GeVPt[iB];}
	}else if(CheckForData8TeV(DataSet)){
		fNBinsAnalysisPt = fNBins8000GeVPt;
		fBinsAnalysisPt = new Double_t[fNBinsAnalysisPt+1];
		for(Int_t iB=0; iB<fNBinsAnalysisPt+1; iB++) {fBinsAnalysisPt[iB] = fBins8000GeVPt[iB];}
	}else if(CheckForTriggerData8TeV(DataSet)){
		fNBinsAnalysisPt = fNBins8000GeVTriggerPt;
		fBinsAnalysisPt = new Double_t[fNBinsAnalysisPt+1];
		for(Int_t iB=0; iB<fNBinsAnalysisPt+1; iB++) {fBinsAnalysisPt[iB] = fBins8000GeVTriggerPt[iB];}
	}else{
		cout << "WARNING: No Binning loaded, nothing defined for " << DataSet.Data() << ". Loading standard 0.6-30 GeV..." << endl;
		fLog << "WARNING: No Binning loaded, nothing defined for " << DataSet.Data() << ". Loading standard 0.6-30 GeV..." << endl;
		fNBinsAnalysisPt = fNBins8000GeVTriggerPt;
		fBinsAnalysisPt = new Double_t[fNBinsAnalysisPt+1];
		for(Int_t iB=0; iB<fNBinsAnalysisPt+1; iB++) {fBinsAnalysisPt[iB] = fBins8000GeVTriggerPt[iB];}
	}

	cout << "Number of Bins: " << fNBinsAnalysisPt << ", analyzing pT-Bins: " << endl;
	fLog << "Number of Bins: " << fNBinsAnalysisPt << ", analyzing pT-Bins: " << endl;
	for(Int_t iB=0; iB<fNBinsAnalysisPt; iB++) {
		cout << fBinsAnalysisPt[iB] << "-" << fBinsAnalysisPt[iB+1] << ", ";
		fLog << fBinsAnalysisPt[iB] << "-" << fBinsAnalysisPt[iB+1] << ", ";
	}
	cout << endl;
	fLog << endl;

	CellQAObj* cellQAData;
	Bool_t plotQACuts = kFALSE;
	Bool_t useGoodRuns = kFALSE;
	TLine *line = new TLine();
	line->SetLineStyle(2);
	line->SetLineWidth(2);
	line->SetLineColor(1);
	if(CheckForData8TeV(DataSet)){
		plotQACuts = kTRUE;
		cellQAData = new CellQAObj();
		setQAEnergy(cellQAData,0,0.25,0,0.25);
		setQATime(cellQAData,-0.025E-6,0.025E-6,0.002E-6,0.05E-6);
		const Int_t dim2D= 9;
//		Double_t min2D[dim2D]={0,4,2.5,1.5,1,0.75,0.5,0.3,0.2};
//		Double_t max2D[dim2D]={0,105,105,105,105,105,105,105,105};
		Double_t min2D[dim2D]={0,2.5,1.5,0.8,0.4,0.25,0.15,0.1,0.08};
		Double_t max2D[dim2D]={0,105,105,105,105,105,105,105,105};
		setQAHotCells2D(cellQAData,dim2D,min2D,max2D);

		setQAHotCells1D(cellQAData,0,4E4,0,1.4);
		if(useGoodRuns && DataSet.CompareTo("LHC12")==0){
//			const Int_t nGoodCells = ;
//			Int_t goodCells[nGoodCells]={129,760,869,1039,1367,1377,};
//			FillGoodCells(cellQAData,nGoodCells,goodCells);
		}
		if(DataSet.CompareTo("LHC12a")==0) setQAHotCells1D(cellQAData,0,9E3,0,1.4);
		//	setQAHotCells1D(cellQAData,9E2,3E4,0,10);
		if(DataSet.CompareTo("LHC12b")==0) setQAHotCells1D(cellQAData,0,3E3,0,1.4);
		if(DataSet.CompareTo("LHC12c")==0) setQAHotCells1D(cellQAData,0,7E3,0,1.4);
		if(DataSet.CompareTo("LHC12d")==0) setQAHotCells1D(cellQAData,0,4E3,0,1.4);
		if(DataSet.CompareTo("LHC12f")==0) setQAHotCells1D(cellQAData,0,3.5E3,0,1.4);
		if(DataSet.CompareTo("LHC12g")==0) setQAHotCells1D(cellQAData,0,1E3,0,1.4);
		if(DataSet.CompareTo("LHC12h")==0) {
			setQATime(cellQAData,0,0.05E-6,0.05E-6,0.2E-6);
			setQAHotCells1D(cellQAData,0,3.5E3,0,1.4);
		}
		if(DataSet.CompareTo("LHC12i")==0) {
			setQATime(cellQAData,0,0.07E-6,0.05E-6,0.2E-6);
			setQAHotCells1D(cellQAData,0,5E2,0,1.5);
		}
	}else if(DataSet.BeginsWith("LHC12-kEMC")){//CheckForTriggerData8TeV(DataSet)){
		plotQACuts = kTRUE;
		cellQAData = new CellQAObj();
		setQAEnergy(cellQAData,0,0.4,0,0.35);
		setQATime(cellQAData,-0.1E-6,0.1E-6,0,0.4E-6);
		setQAHotCells1D(cellQAData,1E4,2E6,0,10);
		const Int_t dim2D= 9;
		Double_t min2D[dim2D]={0,4,2.5,1.5,1,0.75,0.5,0.3,0.2};
		Double_t max2D[dim2D]={0,105,105,105,105,105,105,105,105};
//		Double_t min2D[dim2D]={0,2.5,1.5,0.8,0.4,0.25,0.15,0.1,0.08};
//		Double_t max2D[dim2D]={0,105,105,105,105,105,105,105,105};
		setQAHotCells2D(cellQAData,dim2D,min2D,max2D);
	}else if(DataSet.CompareTo("LHC11a_p4_wSDD")==0){
		plotQACuts = kTRUE;
		cellQAData = new CellQAObj();
		setQAEnergy(cellQAData,0,0.25,0,0.25);
		setQATime(cellQAData,-0.005E-6,0.025E-6,0.005E-6,0.04E-6);
		setQAHotCells1D(cellQAData,0,6E3,0,1.5);
		const Int_t dim2D= 9;
		Double_t min2D[dim2D]={0,2.5,1.5,0.8,0.4,0.25,0.15,0.1,0.08};
		Double_t max2D[dim2D]={0,105,105,105,105,105,105,105,105};
		setQAHotCells2D(cellQAData,dim2D,min2D,max2D);
	}else if(DataSet.CompareTo("LHC11a_p4_wSDD-kEMC1")==0){
		plotQACuts = kTRUE;
		cellQAData = new CellQAObj();
		setQAEnergy(cellQAData,0,0.4,0,0.5);
		setQATime(cellQAData,-0.01E-6,0.025E-6,0,0.04E-6);
		setQAHotCells1D(cellQAData,0,1E3,0,1.5);
		const Int_t dim2D= 9;
		Double_t min2D[dim2D]={0,2.5,1.5,0.8,0.7,0.6,0.5,0.4,0.3};
		Double_t max2D[dim2D]={0,105,105,105,105,105,105,105,105};
		setQAHotCells2D(cellQAData,dim2D,min2D,max2D);
	}else{
		cellQAData = NULL;
		cout << "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;
		cout << "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;
		cout << "\tWARNING: For DataSet " << DataSet.Data() << " there are no cell cuts defined yet!" << endl;
		cout << "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;
		cout << "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;
		fLog << "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;
		fLog << "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;
		fLog << "\tWARNING: For DataSet " << DataSet.Data() << " there are no cell cuts defined yet!" << endl;
		fLog << "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;
		fLog << "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;
	}


	TH2F* tempEtaPhiMC[2];

    Bool_t isFileLoop = isMCPytFile;
	TList* CaloExtQAContainer = CaloExtQAContainerMCPyt;
    TList* CaloCutsContainer = CaloCutsContainerMCPyt;
    TList* TopContainer = TopContainerMCPyt;
    TString fPlot = fPlotMCPyt;
    TString fPrefix = fPrefixMCPyt;
	Bool_t isMC = kTRUE;
	CellQAObj* cellQA = NULL;

    for(Int_t i=0; i<=2; i++)
    {
        if(i==1){ //switch to Phojet
            isFileLoop = isMCPhoFile;
			CaloExtQAContainer = CaloExtQAContainerMCPho;
            CaloCutsContainer = CaloCutsContainerMCPho;
            TopContainer = TopContainerMCPho;
            fPlot = fPlotMCPho;
            fPrefix = fPrefixMCPho;
			isMC = kTRUE;
			cellQA = NULL;
        }

        if(i==2){ //switch to data
            isFileLoop = isDataFile;
			CaloExtQAContainer = CaloExtQAContainerData;
            CaloCutsContainer = CaloCutsContainerData;
            TopContainer = TopContainerData;
            fPlot = fPlotData;
            fPrefix = fPrefixData;
			isMC = kFALSE;
			cellQA = cellQAData;
        }

        TCanvas* canvas;
        TCanvas* cvsQuadratic;

        if(isFileLoop){

        cout << "Processing " << fPrefix.Data() << ", output-directory: " << outputDir.Data() << endl;

        canvas = new TCanvas("canvas","",200,10,1350,900);  // gives the page size
		cvsQuadratic = new TCanvas("cvsQuadratic","",200,10,1350,1350);  // gives the page size
		Double_t leftMargin = 0.1; Double_t rightMargin = 0.02; Double_t topMargin = 0.06; Double_t bottomMargin = 0.1;
        DrawGammaCanvasSettings(canvas, leftMargin, rightMargin, topMargin, bottomMargin);
		DrawGammaCanvasSettings(cvsQuadratic, 0.12, 0.12, topMargin, bottomMargin);
//---------
        canvas->cd();
//---------
		TList* hESDNEvents = (TList*) TopContainer->FindObject(Form("%s ESD histograms",fCutSelection[i].Data()));
		fHistNEvents = (TH1F*) hESDNEvents->FindObject("NEvents");
		Double_t nEvents = GetNEvents(fHistNEvents,kFALSE);
		fLog << "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;
		fLog << "Processing " << fPrefix.Data() << ", output-directory: " << outputDir.Data() << endl;
		fLog << "Plotting " << fPlot.Data() << ", cut: " << fCutSelection[i].Data() << endl;
		fLog << "NEvents: " << nEvents << endl;

//---------
		TList *ESDContainer = (TList*) TopContainer->FindObject(Form("%s ESD histograms", fCutSelection[i].Data()));
			if(!ESDContainer) {cout << "ERROR: could not find ESDContainer for Cut Number: " << fCutSelection[i].Data() << endl; return;}
		TList *TrueContainer = (TList*) TopContainer->FindObject(Form("%s True histograms", fCutSelection[i].Data()));
			if(!TrueContainer) {cout << "WARNING: could not find TrueContainer for Cut Number: " << fCutSelection[i].Data() << ", processing Data?"<< endl;}
		TList *ClusterContainer = (TList*) TopContainer->FindObject(Form("%s Cluster Output", fCutSelection[i].Data()));
			if(!ClusterContainer) {cout << "WARNING: could not find ClusterContainer for Cut Number: " << fCutSelection[i].Data() << endl;}

        if(fHistNEvents){
            DrawAutoGammaHisto(fHistNEvents,
                                 " ",
                                 "",
                                 "# of Entries",
                                 0,0,0,
                                 0,0,0,
								 0,0,0);
            PutProcessLabelAndEnergyOnPlot(0.8, 0.9, 0.03, fCollisionSystem.Data(), fPlot.Data(), Form("%s clusters", calo.Data()));
            canvas->Update();
            canvas->SaveAs(Form("%s/NEvents_%s.%s", outputDir.Data(), fPrefix.Data(), suffix.Data()));
            canvas->Clear();
		}
//---------
		fHistCutIndex = (TH1F*)CaloCutsContainer->FindObject(Form("IsPhotonSelected %s", fClusterCutSelection[i].Data()));
        if(fHistCutIndex){
            DrawAutoGammaHisto(fHistCutIndex,
                                 " ",
                                 "",
                                 "# of Entries",
                                 0,0,0,
                                 0,0,0,
								 0,0,0);
            PutProcessLabelAndEnergyOnPlot(0.8, 0.9, 0.03, fCollisionSystem.Data(), fPlot.Data(), Form("%s clusters", calo.Data()));
            canvas->Update();
            canvas->SaveAs(Form("%s/IsPhotonSelected_%s.%s", outputDir.Data(), fPrefix.Data(), suffix.Data()));
            canvas->Clear();
        }
//---------
		fHistClusterIdentificationCuts = (TH1F*)CaloCutsContainer->FindObject(Form("ClusterQualityCuts %s", fClusterCutSelection[i].Data()));
        if(fHistClusterIdentificationCuts){
            DrawAutoGammaHisto(fHistClusterIdentificationCuts,
                                 " ",
                                 "",
                                 "# of Entries",
                                 0,0,0,
                                 0,0,0,
                                 0,0,0);
            PutProcessLabelAndEnergyOnPlot(0.8, 0.9, 0.03, fCollisionSystem.Data(), fPlot.Data(), Form("%s clusters", calo.Data()));
            canvas->Update();
            canvas->SaveAs(Form("%s/ClusterQualityCuts_%s.%s", outputDir.Data(), fPrefix.Data(), suffix.Data()));
            canvas->Clear();
        }
//---------
		fHistVertexZ = (TH1F*)ESDContainer->FindObject("VertexZ");
		if(fHistVertexZ){
			DrawAutoGammaHisto(fHistVertexZ,
								 " ",
								 "",
								 "# of Entries",
								 0,0,0,
								 0,0,0,
								 0,0,0);
			PutProcessLabelAndEnergyOnPlot(0.8, 0.9, 0.03, fCollisionSystem.Data(), fPlot.Data(), Form("%s clusters", calo.Data()));
			canvas->Update();
			canvas->SaveAs(Form("%s/VertexZ_%s.%s", outputDir.Data(), fPrefix.Data(), suffix.Data()));
			canvas->Clear();
		}
//---------
		fHistClusterEtavsPhiBeforeAcc = (TH2F*)CaloCutsContainer->FindObject(Form("EtaPhi_beforeAcceptance %s", fClusterCutSelection[i].Data()));
        if(fHistClusterEtavsPhiBeforeAcc){
            fHistClusterEtavsPhiBeforeAcc->Sumw2();
			fHistClusterEtavsPhiBeforeAcc->Scale(1/nEvents);
            fHistClusterEtavsPhiBeforeAcc->Scale(1/GetMeanTH2(fHistClusterEtavsPhiBeforeAcc));
            fHistClusterEtavsPhiBeforeAcc->GetZaxis()->SetRangeUser(0,2);
            DrawAutoGammaHisto2D(fHistClusterEtavsPhiBeforeAcc,
                                 Form("%s - %s - %s",fCollisionSystem.Data(), fPlot.Data(), Form("%s clusters", calo.Data())),
                                 "#phi_{Cluster}",
                                 "#eta_{Cluster}",
                                 "",
                                 0,0,0,
                                 0,0,0,
                                 1,1);
            canvas->SetRightMargin(0.1);
            canvas->SetLogy(0); canvas->SetLogz(0); canvas->Update();
            canvas->SaveAs(Form("%s/EtaVsPhi_%s_%s.%s", outputDir.Data(), fPrefix.Data(), "_beforeAcceptance", suffix.Data()));
            canvas->Clear();
            canvas->SetRightMargin(rightMargin);
        }
//---------
		fHistClusterEtavsPhiAfterAcc = (TH2F*)CaloCutsContainer->FindObject(Form("EtaPhi_afterAcceptance %s", fClusterCutSelection[i].Data()));
        if(fHistClusterEtavsPhiAfterAcc){
            fHistClusterEtavsPhiAfterAcc->Sumw2();
			fHistClusterEtavsPhiAfterAcc->Scale(1/nEvents);
            fHistClusterEtavsPhiAfterAcc->Scale(1/GetMeanTH2(fHistClusterEtavsPhiAfterAcc));
            fHistClusterEtavsPhiAfterAcc->GetZaxis()->SetRangeUser(0,2);
            DrawAutoGammaHisto2D(fHistClusterEtavsPhiAfterAcc,
                                 Form("%s - %s - %s",fCollisionSystem.Data(), fPlot.Data(), Form("%s clusters", calo.Data())),
                                 "#phi_{Cluster}",
                                 "#eta_{Cluster}",
                                 "",
                                 0,0,0,
                                 0,0,0,
                                 1,1);
            canvas->SetRightMargin(0.1);
            canvas->SetLogy(0); canvas->SetLogz(0); canvas->Update();;
            canvas->SaveAs(Form("%s/EtaVsPhi_%s_%s.%s", outputDir.Data(), fPrefix.Data(), "_afterAcceptance", suffix.Data()));
            canvas->Clear();
            canvas->SetRightMargin(rightMargin);
        }
//---------
		fHistClusterEtavsPhiAfterQA = (TH2F*)CaloCutsContainer->FindObject(Form("EtaPhi_afterClusterQA %s", fClusterCutSelection[i].Data()));
        if(fHistClusterEtavsPhiAfterQA){
            fHistClusterEtavsPhiAfterQA->Sumw2();
			fHistClusterEtavsPhiAfterQA->Scale(1/nEvents);
            fHistClusterEtavsPhiAfterQA->Scale(1/GetMeanTH2(fHistClusterEtavsPhiAfterQA));
			if(i<2){
				tempEtaPhiMC[i] = new TH2F(*fHistClusterEtavsPhiAfterQA);
			}
            fHistClusterEtavsPhiAfterQA->GetZaxis()->SetRangeUser(0,2);
            DrawAutoGammaHisto2D(fHistClusterEtavsPhiAfterQA,
                                 Form("%s - %s - %s",fCollisionSystem.Data(), fPlot.Data(), Form("%s clusters", calo.Data())),
                                 "#phi_{Cluster}",
                                 "#eta_{Cluster}",
                                 "",
                                 0,0,0,
                                 0,0,0,
                                 1,1);
            //PutProcessLabelAndEnergyOnPlot(0.753, 0.92, 0.03, fCollisionSystem.Data(), fPlot.Data(), Form("%s clusters", calo.Data()));
            canvas->SetRightMargin(0.1);
            canvas->SetLogy(0); canvas->SetLogz(0); canvas->Update();
            canvas->SaveAs(Form("%s/EtaVsPhi_%s_%s.%s", outputDir.Data(), fPrefix.Data(),"_afterClusterQA", suffix.Data()));
            canvas->Clear();
			if(i==2 && cutSel.CompareTo("")==0){
				TString MC[2];
				MC[0]=fPlotMCPyt;
				MC[1]=fPlotMCPho;
				for(Int_t iMC=0; iMC<2; iMC++){
					Float_t tempBinMC = 0;
					Float_t tempBinData = 0;
					for(Int_t iX=1; iX<=124; iX++){
						for(Int_t iY=1; iY<=96; iY++){
							tempBinMC = tempEtaPhiMC[iMC]->GetBinContent(iX,iY);
							tempBinData = fHistClusterEtavsPhiAfterQA->GetBinContent(iX,iY);
							if( (tempBinMC+tempBinData) > 0) tempEtaPhiMC[iMC]->SetBinContent(iX,iY,(tempBinData-tempBinMC)/(tempBinData+tempBinMC));
							else tempEtaPhiMC[iMC]->SetBinContent(iX,iY,-2);
						}
					}
					tempEtaPhiMC[iMC]->GetZaxis()->SetRangeUser(-1,1);
					DrawAutoGammaHisto2D(tempEtaPhiMC[iMC],
										 Form("%s - %s & %s - (Data-MC) / (Data+MC) - %s",fCollisionSystem.Data(), fPlot.Data(), MC[iMC].Data(), Form("%s clusters", calo.Data())),
										 "#phi_{Cluster}",
										 "#eta_{Cluster}",
										 "",
										 0,0,0,
										 0,0,0,
										 1,1);
					canvas->SetLogy(0); canvas->SetLogz(0); canvas->Update();
					canvas->SaveAs(Form("%s/EtaVsPhi_Ratio%s_%s_%s.%s", outputDir.Data(), MC[iMC].Data(), fPrefix.Data(),"_afterClusterQA", suffix.Data()));
					canvas->Clear();
				}
			}
            canvas->SetRightMargin(rightMargin);
		}
//---------
		Float_t tMin = 0;
		Float_t tMax = 0;
        if(i==2){
            tMin = -1*1E-7;
            tMax = 1*1E-7;
        }else{
            tMin = 5*1E-7;
            tMax = 7*1E-7;
		}
		TGaxis::SetExponentOffset(0.5, 0, "x");
		fHistClusterTimevsEBeforeQA = (TH2F*)CaloCutsContainer->FindObject(Form("ClusterTimeVsE_beforeClusterQA %s", fClusterCutSelection[i].Data()));
		if(fHistClusterTimevsEBeforeQA){
            DrawAutoGammaHisto2D(fHistClusterTimevsEBeforeQA,
                                 " ",
								 "#it{t}_{Cluster} (#mus)",
								 "#it{E}_{Cluster} (GeV)",
                                 "",
								 0,0,0,
								 1,tMin,tMax,
                                 1,1);
			PutProcessLabelAndEnergyOnPlot(0.7, 0.9, 0.03, fCollisionSystem.Data(), fPlot.Data(), Form("%s clusters", calo.Data()));
            canvas->SetRightMargin(0.1);
            canvas->SetLogy(0); canvas->SetLogz(1); canvas->Update();
            canvas->SaveAs(Form("%s/ClusterTimeVsE_%s_%s.%s", outputDir.Data(), fPrefix.Data(),"_beforeClusterQA", suffix.Data()));
            canvas->Clear();
            canvas->SetRightMargin(rightMargin);
//---------
			fHistClusterTimeBeforeQA = (TH1D*) fHistClusterTimevsEBeforeQA->ProjectionX("fHistClusterTimeBeforeQA",1,100);
			if(fHistClusterTimeBeforeQA){
				DrawAutoGammaHisto(fHistClusterTimeBeforeQA,
								   " ",
								   "#it{t}_{Cluster} (ns)",
								   "#frac{d#it{N}}{d#it{t}_{Cluster}}",
								   0,0,0,
								   0,0,0,
								   1,tMin+0.3E-7,tMax-0.3E-7);
				PutProcessLabelAndEnergyOnPlot(0.8, 0.9, 0.03, fCollisionSystem.Data(), fPlot.Data(), Form("%s clusters", calo.Data()));
				canvas->SetLogy(1); canvas->SetLogz(0); canvas->Update();
				canvas->SaveAs(Form("%s/ClusterTime_%s_%s.%s", outputDir.Data(), fPrefix.Data(),"beforeClusterQA", suffix.Data()));
				canvas->Clear();
			}
		}
//---------
		fHistClusterTimevsEAfterQA = (TH2F*)CaloCutsContainer->FindObject(Form("ClusterTimeVsE_afterClusterQA %s", fClusterCutSelection[i].Data()));
		if(fHistClusterTimevsEAfterQA){
			DrawAutoGammaHisto2D(fHistClusterTimevsEAfterQA,
								 " ",
								 "#it{t}_{Cluster} (#mus)",
								 "#it{E}_{Cluster} (GeV)",
								 "",
								 0,0,0,
								 1,tMin,tMax,
								 1,1);
            PutProcessLabelAndEnergyOnPlot(0.7, 0.9, 0.03, fCollisionSystem.Data(), fPlot.Data(), Form("%s clusters", calo.Data()));
            canvas->SetRightMargin(0.1);
            canvas->SetLogy(0); canvas->SetLogz(1); canvas->Update();
            canvas->SaveAs(Form("%s/ClusterTimeVsE_%s_%s.%s", outputDir.Data(), fPrefix.Data(),"_afterClusterQA", suffix.Data()));
            canvas->Clear();
			canvas->SetRightMargin(rightMargin);
//---------
			fHistClusterTimeAfterQA = (TH1D*) fHistClusterTimevsEAfterQA->ProjectionX("fHistClusterTimeAfterQA",1,100);
			if(fHistClusterTimeAfterQA){
				DrawAutoGammaHisto(fHistClusterTimeAfterQA,
								   " ",
								   "#it{t}_{Cluster} (ns)",
								   "#frac{d#it{N}}{d#it{t}_{Cluster}}",
								   0,0,0,
								   0,0,0,
								   1,tMin+0.3E-7,tMax-0.3E-7);
				PutProcessLabelAndEnergyOnPlot(0.8, 0.9, 0.03, fCollisionSystem.Data(), fPlot.Data(), Form("%s clusters", calo.Data()));
				canvas->SetLogy(1); canvas->SetLogz(0); canvas->Update();
				canvas->SaveAs(Form("%s/ClusterTime_%s_%s.%s", outputDir.Data(), fPrefix.Data(),"afterClusterQA", suffix.Data()));
				canvas->Clear();
			}
		}
		TGaxis::SetExponentOffset(0, 0, "x");
//---------
		fHistEnergyOfClusterBeforeQA = (TH1F*)CaloCutsContainer->FindObject(Form("EnergyOfCluster_beforeClusterQA %s", fClusterCutSelection[i].Data()));
		fHistEnergyOfClusterBeforeQA = (TH1F*) fHistEnergyOfClusterBeforeQA->Rebin(fNBinsClusterPt, "energyBefore", fBinsClusterPt);
		fHistEnergyOfClusterBeforeQA->Divide(fDeltaPt);
        if(fHistEnergyOfClusterBeforeQA){
            DrawAutoGammaHisto(fHistEnergyOfClusterBeforeQA,
                                 " ",
								 "#it{E}_{Cluster} (GeV)",
								 "#frac{d#it{N}}{d#it{E}_{Cluster}}",
                                 0,0,0,
                                 0,0,0,
								 1,0,30);
            PutProcessLabelAndEnergyOnPlot(0.8, 0.9, 0.03, fCollisionSystem.Data(), fPlot.Data(), Form("%s clusters", calo.Data()));
            canvas->SetLogy(1); canvas->SetLogz(0); canvas->Update();
            canvas->SaveAs(Form("%s/EnergyOfCluster_%s_%s.%s", outputDir.Data(), fPrefix.Data(),"beforeClusterQA", suffix.Data()));
            canvas->Clear();
		}
//---------
		fHistEnergyOfClusterAfterQA = (TH1F*)CaloCutsContainer->FindObject(Form("EnergyOfCluster_afterClusterQA %s", fClusterCutSelection[i].Data()));
		fHistEnergyOfClusterAfterQA = (TH1F*) fHistEnergyOfClusterAfterQA->Rebin(fNBinsClusterPt, "energyAfter", fBinsClusterPt);
		fHistEnergyOfClusterAfterQA->Divide(fDeltaPt);
        if(fHistEnergyOfClusterAfterQA){
            DrawAutoGammaHisto(fHistEnergyOfClusterAfterQA,
                                 " ",
								 "#it{E}_{Cluster} (GeV)",
								 "#frac{d#it{N}}{d#it{E}_{Cluster}}",
                                 0,0,0,
                                 0,0,0,
								 1,0,30);
            PutProcessLabelAndEnergyOnPlot(0.8, 0.9, 0.03, fCollisionSystem.Data(), fPlot.Data(), Form("%s clusters", calo.Data()));
            canvas->SetLogy(1); canvas->SetLogz(0); canvas->Update();
            canvas->SaveAs(Form("%s/EnergyOfCluster_%s_%s.%s", outputDir.Data(), fPrefix.Data(),"afterClusterQA", suffix.Data()));
            canvas->Clear();
        }
//---------
		fHistNCellsBeforeQA = (TH1F*)CaloCutsContainer->FindObject(Form("NCellPerCluster_beforeClusterQA %s", fClusterCutSelection[i].Data()));
        if(fHistNCellsBeforeQA){
            DrawAutoGammaHisto(fHistNCellsBeforeQA,
                                 " ",
								 "#it{N}_{Cells} per Cluster",
								 "#frac{d#it{N}}{d#it{N}_{Cells}}",
                                 0,0,0,
                                 0,0,0,
                                 1,0,25);
            PutProcessLabelAndEnergyOnPlot(0.8, 0.9, 0.03, fCollisionSystem.Data(), fPlot.Data(), Form("%s clusters", calo.Data()));
            canvas->SetLogy(1); canvas->SetLogz(0); canvas->Update();
            canvas->SaveAs(Form("%s/NCellPerCluster_%s_%s.%s", outputDir.Data(), fPrefix.Data(),"beforeClusterQA", suffix.Data()));
            canvas->Clear();
        }
//---------
		fHistNCellsAfterQA = (TH1F*)CaloCutsContainer->FindObject(Form("NCellPerCluster_afterClusterQA %s", fClusterCutSelection[i].Data()));
        if(fHistNCellsAfterQA){
            DrawAutoGammaHisto(fHistNCellsAfterQA,
                                 " ",
								 "#it{N}_{Cells} per Cluster",
								 "#frac{d#it{N}}{d#it{N}_{Cells}}",
                                 0,0,0,
                                 0,0,0,
                                 1,0,25);
            PutProcessLabelAndEnergyOnPlot(0.8, 0.9, 0.03, fCollisionSystem.Data(), fPlot.Data(), Form("%s clusters", calo.Data()));
            canvas->SetLogy(1); canvas->SetLogz(0); canvas->Update();
            canvas->SaveAs(Form("%s/NCellPerCluster_%s_%s.%s", outputDir.Data(), fPrefix.Data(),"afterClusterQA", suffix.Data()));
            canvas->Clear();
        }
//---------
		fHistM02BeforeQA = (TH1F*)CaloCutsContainer->FindObject(Form("M02_beforeClusterQA %s", fClusterCutSelection[i].Data()));
        if(fHistM02BeforeQA){
            DrawAutoGammaHisto(fHistM02BeforeQA,
                                 " ",
								 "#lambda_{0}^{2}",
								 "#frac{d#it{N}}{d#lambda_{0}^{2}}",
                                 0,0,0,
                                 0,0,0,
                                 0,0,0);
            PutProcessLabelAndEnergyOnPlot(0.8, 0.9, 0.03, fCollisionSystem.Data(), fPlot.Data(), Form("%s clusters", calo.Data()));
            canvas->SetLogy(1); canvas->SetLogz(0); canvas->Update();
            canvas->SaveAs(Form("%s/M02_%s_%s.%s", outputDir.Data(), fPrefix.Data(),"beforeClusterQA", suffix.Data()));
            canvas->Clear();
        }
//---------
		fHistM02AfterQA = (TH1F*)CaloCutsContainer->FindObject(Form("M02_afterClusterQA %s", fClusterCutSelection[i].Data()));
        if(fHistM02AfterQA){
            DrawAutoGammaHisto(fHistM02AfterQA,
                                 " ",
								 "#lambda_{0}^{2}",
								 "#frac{d#it{N}}{d#lambda_{0}^{2}}",
                                 0,0,0,
                                 0,0,0,
								 1,0.05,0.55);
            PutProcessLabelAndEnergyOnPlot(0.8, 0.9, 0.03, fCollisionSystem.Data(), fPlot.Data(), Form("%s clusters", calo.Data()));
            canvas->SetLogy(1); canvas->SetLogz(0); canvas->Update();
            canvas->SaveAs(Form("%s/M02_%s_%s.%s", outputDir.Data(), fPrefix.Data(),"afterClusterQA", suffix.Data()));
            canvas->Clear();
        }
//---------
		fHistM20BeforeQA = (TH1F*)CaloCutsContainer->FindObject(Form("M20_beforeClusterQA %s", fClusterCutSelection[i].Data()));
        if(fHistM20BeforeQA){
            DrawAutoGammaHisto(fHistM20BeforeQA,
                                 " ",
								 "#lambda_{1}^{2}",
								 "#frac{d#it{N}}{d#lambda_{1}^{2}}",
                                 0,0,0,
                                 0,0,0,
                                 0,0,0);
            PutProcessLabelAndEnergyOnPlot(0.8, 0.9, 0.03, fCollisionSystem.Data(), fPlot.Data(), Form("%s clusters", calo.Data()));
            canvas->SetLogy(1); canvas->SetLogz(0); canvas->Update();
            canvas->SaveAs(Form("%s/M20_%s_%s.%s", outputDir.Data(), fPrefix.Data(),"beforeClusterQA", suffix.Data()));
            canvas->Clear();
        }
//---------
		fHistM20AfterQA = (TH1F*)CaloCutsContainer->FindObject(Form("M20_afterClusterQA %s", fClusterCutSelection[i].Data()));
        if(fHistM20AfterQA){
            DrawAutoGammaHisto(fHistM20AfterQA,
                                 " ",
								 "#lambda_{1}^{2}",
								 "#frac{d#it{N}}{d#lambda_{1}^{2}}",
                                 0,0,0,
                                 0,0,0,
								 1,0,0.55);
            PutProcessLabelAndEnergyOnPlot(0.8, 0.9, 0.03, fCollisionSystem.Data(), fPlot.Data(), Form("%s clusters", calo.Data()));
            canvas->SetLogy(1); canvas->SetLogz(0); canvas->Update();
            canvas->SaveAs(Form("%s/M20_%s_%s.%s", outputDir.Data(), fPrefix.Data(),"afterClusterQA", suffix.Data()));
            canvas->Clear();
        }
//---------
		fHistDispersionBeforeQA = (TH1F*)CaloCutsContainer->FindObject(Form("Dispersion_beforeClusterQA %s", fClusterCutSelection[i].Data()));
        if(fHistDispersionBeforeQA){
            DrawAutoGammaHisto(fHistDispersionBeforeQA,
                                 " ",
								 "Cluster Dispersion",
								 "#frac{d#it{N}}{dDisp}",
                                 0,0,0,
                                 0,0,0,
                                 1,0,2.5);
            PutProcessLabelAndEnergyOnPlot(0.8, 0.9, 0.03, fCollisionSystem.Data(), fPlot.Data(), Form("%s clusters", calo.Data()));
            canvas->SetLogy(1); canvas->SetLogz(0); canvas->Update();
            canvas->SaveAs(Form("%s/Dispersion_%s_%s.%s", outputDir.Data(), fPrefix.Data(),"beforeClusterQA", suffix.Data()));
            canvas->Clear();
        }
//---------
		fHistDispersionAfterQA = (TH1F*)CaloCutsContainer->FindObject(Form("Dispersion_afterClusterQA %s", fClusterCutSelection[i].Data()));
        if(fHistDispersionAfterQA){
            DrawAutoGammaHisto(fHistDispersionAfterQA,
                                 " ",
								 "Cluster Dispersion",
								 "#frac{d#it{N}}{dDisp}",
                                 0,0,0,
                                 0,0,0,
								 1,0.2,1.1);
            PutProcessLabelAndEnergyOnPlot(0.8, 0.9, 0.03, fCollisionSystem.Data(), fPlot.Data(), Form("%s clusters", calo.Data()));
            canvas->SetLogy(1); canvas->SetLogz(0); canvas->Update();
            canvas->SaveAs(Form("%s/Dispersion_%s_%s.%s", outputDir.Data(), fPrefix.Data(),"afterClusterQA", suffix.Data()));
            canvas->Clear();
        }
//---------
		fHistClusterRBeforeQA = (TH1F*)CaloCutsContainer->FindObject(Form("R_Cluster_beforeClusterQA %s", fClusterCutSelection[i].Data()));
        if(fHistClusterRBeforeQA){
            DrawAutoGammaHisto(fHistClusterRBeforeQA,
                                 " ",
								 "#it{R}_{Cluster} (cm)",
								 "#frac{d#it{N}}{d#it{R}}",
                                 0,0,0,
                                 0,0,0,
                                 1,430,460);
            PutProcessLabelAndEnergyOnPlot(0.8, 0.9, 0.03, fCollisionSystem.Data(), fPlot.Data(), Form("%s clusters", calo.Data()));
            canvas->SetLogy(0); canvas->SetLogz(0); canvas->Update();
            canvas->SaveAs(Form("%s/R_Cluster_%s_%s.%s", outputDir.Data(), fPrefix.Data(),"beforeClusterQA", suffix.Data()));
            canvas->Clear();
        }
//---------
		fHistClusterRAfterQA = (TH1F*)CaloCutsContainer->FindObject(Form("R_Cluster_afterClusterQA %s", fClusterCutSelection[i].Data()));
        if(fHistClusterRAfterQA){
            DrawAutoGammaHisto(fHistClusterRAfterQA,
                                 " ",
								 "#it{R}_{Cluster} (cm)",
								 "#frac{d#it{N}}{d#it{R}}",
                                 0,0,0,
                                 0,0,0,
                                 1,430,460);
            PutProcessLabelAndEnergyOnPlot(0.8, 0.9, 0.03, fCollisionSystem.Data(), fPlot.Data(), Form("%s clusters", calo.Data()));
            canvas->SetLogy(0); canvas->SetLogz(0); canvas->Update();
            canvas->SaveAs(Form("%s/R_Cluster_%s_%s.%s", outputDir.Data(), fPrefix.Data(),"afterClusterQA", suffix.Data()));
            canvas->Clear();
        }
//---------

//****************************** More Histograms ************************************************

		TBox *boxLabel = new TBox(0.075,0.19,0.26,0.265);
        boxLabel->SetFillColor(0);
//---------
		fHistClusterdEtadPhiBeforeQA = (TH2F*)CaloCutsContainer->FindObject(Form("dEtaVsdPhi_beforeClusterQA %s", fClusterCutSelection[i].Data()));
        if(fHistClusterdEtadPhiBeforeQA){
			cvsQuadratic->cd();
            DrawAutoGammaHisto2D(fHistClusterdEtadPhiBeforeQA,
                                 " ",
                                 "#Delta#eta_{Cluster - all Tracks}",
                                 "#Delta#phi_{Cluster - all Tracks}",
                                 "",
                                 0,0,0,
                                 0,0,0,
								 1,1.2);
            boxLabel->Draw();
			PutProcessLabelAndEnergyOnPlot(0.6, 0.9, 0.03, fCollisionSystem.Data(), fPlot.Data(), Form("%s clusters", calo.Data()));
			cvsQuadratic->SetLogy(0); cvsQuadratic->SetLogz(1); cvsQuadratic->Update();
			cvsQuadratic->SaveAs(Form("%s/dEtaVsdPhi_allTracks_%s_%s.%s", outputDir.Data(), fPrefix.Data(),"beforeClusterQA", suffix.Data()));
			cvsQuadratic->Clear();
//---------
			TBox *cutPos = new TBox(-0.016,-0.09,0.016,0.06);
			cutPos->SetFillStyle(0);
			cutPos->SetFillColor(0);
			cutPos->SetLineColor(kRed+3);
			cutPos->SetLineStyle(3);
			cutPos->SetLineWidth(4);
			TBox *cutNeg = new TBox(-0.016,-0.06,0.016,0.09);
			cutNeg->SetFillStyle(0);
			cutNeg->SetFillColor(0);
			cutNeg->SetLineColor(kRed+3);
			cutNeg->SetLineStyle(5);
			cutNeg->SetLineWidth(4);
			DrawAutoGammaHisto2D(fHistClusterdEtadPhiBeforeQA,
								 " ",
								 "#Delta#eta_{Cluster - all Tracks}",
								 "#Delta#phi_{Cluster - all Tracks}",
								 "",
								 0,0,0,
								 0,0,0,
								 1,1.2);
			boxLabel->Draw();
			cutPos->Draw();
			cutNeg->Draw();
			PutProcessLabelAndEnergyOnPlot(0.6, 0.9, 0.03, fCollisionSystem.Data(), fPlot.Data(), Form("%s clusters", calo.Data()));
			cvsQuadratic->SetLogy(0); cvsQuadratic->SetLogz(1); cvsQuadratic->Update();
			cvsQuadratic->SaveAs(Form("%s/dEtaVsdPhi_allTracks_WithCuts_%s_%s.%s", outputDir.Data(), fPrefix.Data(),"beforeClusterQA", suffix.Data()));
			cvsQuadratic->Clear();
//---------
			canvas->cd();
//---------
			fHistClusterdEtaBeforeQA = fHistClusterdEtadPhiBeforeQA->ProjectionX("fHistClusterdEtaBeforeQA",1,300);
            if(fHistClusterdEtaBeforeQA){
				fHistClusterdEtaBeforeQA->GetXaxis()->SetTitleOffset(0.9);
                DrawAutoGammaHisto(fHistClusterdEtaBeforeQA,
                                     " ",
                                     "#Delta#eta_{Cluster - all Tracks}",
									 "#frac{d#it{N}}{d#Delta#eta}",
                                     0,0,0,
                                     0,0,0,
                                     1,-0.3,0.3);
                PutProcessLabelAndEnergyOnPlot(0.8, 0.9, 0.03, fCollisionSystem.Data(), fPlot.Data(), Form("%s clusters", calo.Data()));
                canvas->SetLogy(0); canvas->SetLogz(0); canvas->Update();
                canvas->SaveAs(Form("%s/dEta_allTracks_%s_%s.%s", outputDir.Data(), fPrefix.Data(),"beforeQA", suffix.Data()));
                canvas->Clear();
            }
//---------
			fHistClusterdPhiBeforeQA = fHistClusterdEtadPhiBeforeQA->ProjectionY("fHistClusterdPhiBeforeQA",1,300);
            if(fHistClusterdPhiBeforeQA){
				fHistClusterdPhiBeforeQA->GetXaxis()->SetTitleOffset(0.9);
                DrawAutoGammaHisto(fHistClusterdPhiBeforeQA,
                                     " ",
                                     "#Delta#phi_{Cluster - all Tracks}",
									 "#frac{d#it{N}}{d#Delta#phi}",
                                     0,0,0,
                                     0,0,0,
                                     1,-0.3,0.3);
                PutProcessLabelAndEnergyOnPlot(0.8, 0.9, 0.03, fCollisionSystem.Data(), fPlot.Data(), Form("%s clusters", calo.Data()));
                canvas->SetLogy(0); canvas->SetLogz(0); canvas->Update();
                canvas->SaveAs(Form("%s/dPhi_allTracks_%s_%s.%s", outputDir.Data(), fPrefix.Data(),"beforeQA", suffix.Data()));
                canvas->Clear();
            }
        }

//---------
		fHistClusterdEtadPhiAfterQA = (TH2F*)CaloCutsContainer->FindObject(Form("dEtaVsdPhi_afterClusterQA %s", fClusterCutSelection[i].Data()));
        if(fHistClusterdEtadPhiAfterQA){
			cvsQuadratic->cd();
            DrawAutoGammaHisto2D(fHistClusterdEtadPhiAfterQA,
                                 " ",
                                 "#Delta#eta_{Cluster - unmatched Tracks}",
                                 "#Delta#phi_{Cluster - unmatched Tracks}",
                                 "",
                                 0,0,0,
                                 0,0,0,
								 1,1.2);
            boxLabel->Draw();
			PutProcessLabelAndEnergyOnPlot(0.6, 0.9, 0.03, fCollisionSystem.Data(), fPlot.Data(), Form("%s clusters", calo.Data()));
			cvsQuadratic->SetLogy(0); cvsQuadratic->SetLogz(0); cvsQuadratic->Update();
			cvsQuadratic->SaveAs(Form("%s/dEtaVsdPhi_unmatched_%s_%s.%s", outputDir.Data(), fPrefix.Data(),"afterClusterQA", suffix.Data()));
			cvsQuadratic->Clear();
//---------
			canvas->cd();
//---------
			fHistClusterdEtaAfterQA = fHistClusterdEtadPhiAfterQA->ProjectionX("fHistClusterdEtaAfterQA",1,300);
            if(fHistClusterdEtaAfterQA){
				fHistClusterdEtaAfterQA->GetXaxis()->SetTitleOffset(0.9);
                DrawAutoGammaHisto(fHistClusterdEtaAfterQA,
                                     " ",
                                     "#Delta#eta_{Cluster - unmatched Tracks}",
									 "#frac{d#it{N}}{d#Delta#eta}",
                                     0,0,0,
                                     0,0,0,
                                     1,-0.3,0.3);
                PutProcessLabelAndEnergyOnPlot(0.8, 0.9, 0.03, fCollisionSystem.Data(), fPlot.Data(), Form("%s clusters", calo.Data()));
                canvas->SetLogy(0); canvas->SetLogz(0); canvas->Update();
                canvas->SaveAs(Form("%s/dEta_unmatched_%s_%s.%s", outputDir.Data(), fPrefix.Data(),"afterQA", suffix.Data()));
                canvas->Clear();
            }
//---------
			fHistClusterdPhiAfterQA = fHistClusterdEtadPhiAfterQA->ProjectionY("fHistClusterdPhiAfterQA",1,300);
            if(fHistClusterdPhiAfterQA){
				fHistClusterdPhiAfterQA->GetXaxis()->SetTitleOffset(0.9);
                DrawAutoGammaHisto(fHistClusterdPhiAfterQA,
                                     " ",
                                     "#Delta#phi_{Cluster - unmatched Tracks}",
									 "#frac{d#it{N}}{d#Delta#phi}",
                                     0,0,0,
                                     0,0,0,
                                     1,-0.3,0.3);
                PutProcessLabelAndEnergyOnPlot(0.8, 0.9, 0.03, fCollisionSystem.Data(), fPlot.Data(), Form("%s clusters", calo.Data()));
                canvas->SetLogy(0); canvas->SetLogz(0); canvas->Update();
                canvas->SaveAs(Form("%s/dPhi_unmatched_%s_%s.%s", outputDir.Data(), fPrefix.Data(),"afterQA", suffix.Data()));
                canvas->Clear();
            }
        }
//---------
		fHistDistanceTrackToClusterBeforeQA = (TH1F*)CaloCutsContainer->FindObject(Form("DistanceToTrack_beforeClusterQA %s", fClusterCutSelection[i].Data()));
        if(fHistDistanceTrackToClusterBeforeQA){
            fHistDistanceTrackToClusterBeforeQA->GetXaxis()->SetTitleOffset(1.3);
            canvas->SetBottomMargin(0.15);
            DrawAutoGammaHisto(fHistDistanceTrackToClusterBeforeQA,
                                 " ",
								 "r = #sqrt{#Delta#eta_{Cluster - all Tracks}^{2}+#Delta#phi_{Cluster - all Tracks}^{2}}",
								 "#frac{d#it{N}}{d#it{r}}",
                                 0,0,0,
                                 1,1,1E5,
                                 0,0,0);
            PutProcessLabelAndEnergyOnPlot(0.8, 0.9, 0.03, fCollisionSystem.Data(), fPlot.Data(), Form("%s clusters", calo.Data()));
            canvas->SetLogy(1); canvas->SetLogz(0); canvas->Update();
            canvas->SaveAs(Form("%s/DistanceToTrack_%s_%s.%s", outputDir.Data(), fPrefix.Data(),"beforeClusterQA", suffix.Data()));
            canvas->Clear();
        }
//---------
		fHistDistanceTrackToClusterAfterQA = (TH1F*)CaloCutsContainer->FindObject(Form("DistanceToTrack_afterClusterQA %s", fClusterCutSelection[i].Data()));
        if(fHistDistanceTrackToClusterAfterQA){
            fHistDistanceTrackToClusterAfterQA->GetXaxis()->SetTitleOffset(1.3);
            DrawAutoGammaHisto(fHistDistanceTrackToClusterAfterQA,
                                 " ",
								 "r = #sqrt{#Delta#eta_{Cluster - unmatched Tracks}^{2}+#Delta#phi_{Cluster - unmatched Tracks}^{2}}",
								 "#frac{d#it{N}}{d#it{r}}",
                                 0,0,0,
                                 1,1,1E5,
                                 0,0,0);
            PutProcessLabelAndEnergyOnPlot(0.8, 0.9, 0.03, fCollisionSystem.Data(), fPlot.Data(), Form("%s clusters", calo.Data()));
            canvas->SetLogy(1); canvas->SetLogz(0); canvas->Update();
            canvas->SaveAs(Form("%s/DistanceToTrack_unmatched_%s_%s.%s", outputDir.Data(), fPrefix.Data(),"afterClusterQA", suffix.Data()));
            canvas->Clear();
            canvas->SetBottomMargin(bottomMargin);
        }
//---------
		fHistClusterdEtadPtBeforeQA = (TH2F*)CaloCutsContainer->FindObject(Form("dEtaVsPt_beforeClusterQA %s", fClusterCutSelection[i].Data()));
        if(fHistClusterdEtadPtBeforeQA){
            DrawAutoGammaHisto2D(fHistClusterdEtadPtBeforeQA,
                                 " ",
                                 "#Delta#eta_{Cluster - all Tracks}",
								 "#it{p}_{T} (GeV/#it{c})",
                                 "",
                                 1,0,20,
                                 0,0,0,
                                 1,1);
            PutProcessLabelAndEnergyOnPlot(0.7, 0.9, 0.03, fCollisionSystem.Data(), fPlot.Data(), Form("%s clusters", calo.Data()));
            canvas->SetRightMargin(0.1);
            canvas->SetLogy(0); canvas->SetLogz(1); canvas->Update();
            canvas->SaveAs(Form("%s/dEtaVsPt_%s_%s.%s", outputDir.Data(), fPrefix.Data(),"beforeClusterQA", suffix.Data()));
            canvas->Clear();
            canvas->SetRightMargin(rightMargin);
        }
//---------
		fHistClusterdPhidPtBeforeQA = (TH2F*)CaloCutsContainer->FindObject(Form("dPhiVsPt_beforeClusterQA %s", fClusterCutSelection[i].Data()));
        if(fHistClusterdPhidPtBeforeQA){
            DrawAutoGammaHisto2D(fHistClusterdPhidPtBeforeQA,
                                 " ",
                                 "#Delta#phi_{Cluster - all Tracks}",
								 "#it{p}_{T} (GeV/#it{c})",
                                 "",
                                 1,0,20,
                                 0,0,0,
                                 1,1);
            PutProcessLabelAndEnergyOnPlot(0.7, 0.9, 0.03, fCollisionSystem.Data(), fPlot.Data(), Form("%s clusters", calo.Data()));
            canvas->SetRightMargin(0.1);
            canvas->SetLogy(0); canvas->SetLogz(1); canvas->Update();
            canvas->SaveAs(Form("%s/dPhiVsPt_%s_%s.%s", outputDir.Data(), fPrefix.Data(),"beforeClusterQA", suffix.Data()));
            canvas->Clear();
            canvas->SetRightMargin(rightMargin);
        }
//---------
		fHistClusterEM02BeforeQA = (TH2F*)CaloCutsContainer->FindObject(Form("EVsM02_beforeClusterQA %s", fClusterCutSelection[i].Data()));
		if(fHistClusterEM02BeforeQA){
			DrawAutoGammaHisto2D(fHistClusterEM02BeforeQA,
                                 " ",
								 "E (GeV)",
								 "#lambda_{0}^{2}",
                                 "",
                                 0,0,0,
								 0,0,0,
                                 1,1);
            PutProcessLabelAndEnergyOnPlot(0.7, 0.9, 0.03, fCollisionSystem.Data(), fPlot.Data(), Form("%s clusters", calo.Data()));
            canvas->SetRightMargin(0.1);
            canvas->SetLogy(0); canvas->SetLogz(1); canvas->Update();
			canvas->SaveAs(Form("%s/EVsM02_%s_%s.%s", outputDir.Data(), fPrefix.Data(),"beforeClusterQA", suffix.Data()));
            canvas->Clear();
            canvas->SetRightMargin(rightMargin);
        }
//---------
		fHistClusterEM02AfterQA = (TH2F*)CaloCutsContainer->FindObject(Form("EVsM02_afterClusterQA %s", fClusterCutSelection[i].Data()));
		if(fHistClusterEM02AfterQA){
			DrawAutoGammaHisto2D(fHistClusterEM02AfterQA,
                                 " ",
								 "E (GeV)",
								 "#lambda_{0}^{2}",
                                 "",
								 1,0.05,0.55,
                                 0,0,0,
                                 1,1);
            PutProcessLabelAndEnergyOnPlot(0.7, 0.9, 0.03, fCollisionSystem.Data(), fPlot.Data(), Form("%s clusters", calo.Data()));
            canvas->SetRightMargin(0.1);
            canvas->SetLogy(0); canvas->SetLogz(1); canvas->Update();
			canvas->SaveAs(Form("%s/EVsM02_%s_%s.%s", outputDir.Data(), fPrefix.Data(),"afterClusterQA", suffix.Data()));
            canvas->Clear();
            canvas->SetRightMargin(rightMargin);
        }
//---------
        cvsQuadratic->cd();
//---------
		fHistClusterM20M02BeforeQA = (TH2F*)CaloCutsContainer->FindObject(Form("M20VsM02_beforeClusterQA %s", fClusterCutSelection[i].Data()));
        if(fHistClusterM20M02BeforeQA){
            fHistClusterM20M02BeforeQA->GetXaxis()->SetDecimals();
            fHistClusterM20M02BeforeQA->GetXaxis()->SetLabelOffset(0.01);
            fHistClusterM20M02BeforeQA->GetYaxis()->SetLabelOffset(0.01);
            DrawAutoGammaHisto2D(fHistClusterM20M02BeforeQA,
                                 " ",
								 "#lambda_{1}^{2}",
								 "#lambda_{0}^{2}",
                                 "",
								 1,0.05,0.55,
								 1,0,0.55,
                                 1,1.2);
			PutProcessLabelAndEnergyOnPlot(0.62, 0.25, 0.03, fCollisionSystem.Data(), fPlot.Data(), Form("%s clusters", calo.Data()));
            cvsQuadratic->SetLogy(0); cvsQuadratic->SetLogz(1); cvsQuadratic->Update();
            cvsQuadratic->SaveAs(Form("%s/M20VsM02_%s_%s.%s", outputDir.Data(), fPrefix.Data(),"beforeClusterQA", suffix.Data()));
            cvsQuadratic->Clear();
        }
//---------
		fHistClusterM20M02AfterQA = (TH2F*)CaloCutsContainer->FindObject(Form("M20VsM02_afterClusterQA %s", fClusterCutSelection[i].Data()));
        if(fHistClusterM20M02AfterQA){
            fHistClusterM20M02AfterQA->GetXaxis()->SetDecimals();
            fHistClusterM20M02AfterQA->GetXaxis()->SetLabelOffset(0.01);
            fHistClusterM20M02AfterQA->GetYaxis()->SetLabelOffset(0.01);
            DrawAutoGammaHisto2D(fHistClusterM20M02AfterQA,
                                 " ",
								 "#lambda_{1}^{2}",
								 "#lambda_{0}^{2}",
                                 "",
								 1,0.05,0.55,
								 1,0,0.55,
                                 1,1.2);
			PutProcessLabelAndEnergyOnPlot(0.62, 0.25, 0.03, fCollisionSystem.Data(), fPlot.Data(), Form("%s clusters", calo.Data()));
            cvsQuadratic->SetLogy(0); cvsQuadratic->SetLogz(1); cvsQuadratic->Update();
            cvsQuadratic->SaveAs(Form("%s/M20VsM02_unmatched_%s_%s.%s", outputDir.Data(), fPrefix.Data(),"afterClusterQA", suffix.Data()));
            cvsQuadratic->Clear();
        }
//---------
        canvas->cd();
//---------
		fHistClusterdEtadPhiPosTracksBeforeQA = (TH2F*)CaloCutsContainer->FindObject(Form("dEtaVsdPhi_posTracks_beforeClusterQA %s", fClusterCutSelection[i].Data()));
        if(fHistClusterdEtadPhiPosTracksBeforeQA){
			cvsQuadratic->cd();
            DrawAutoGammaHisto2D(fHistClusterdEtadPhiPosTracksBeforeQA,
                                 " ",
                                 "#Delta#eta_{Cluster - pos. Tracks}",
                                 "#Delta#phi_{Cluster - pos. Tracks}",
                                 "",
                                 0,0,0,
                                 0,0,0,
								 1,1.2);
            boxLabel->Draw();
			PutProcessLabelAndEnergyOnPlot(0.6, 0.9, 0.03, fCollisionSystem.Data(), fPlot.Data(), Form("%s clusters", calo.Data()));
			cvsQuadratic->SetLogy(0); canvas->SetLogz(1); canvas->Update();
			cvsQuadratic->SaveAs(Form("%s/dEtaVsdPhi_posTracks_%s_%s.%s", outputDir.Data(), fPrefix.Data(),"beforeClusterQA", suffix.Data()));
			cvsQuadratic->Clear();
//---------
			canvas->cd();
//---------
			fHistClusterdEtaPosTracksBeforeQA = fHistClusterdEtadPhiPosTracksBeforeQA->ProjectionX("fHistClusterdEtaPosTracksBeforeQA",1,300);
            if(fHistClusterdEtaPosTracksBeforeQA){
				fHistClusterdEtaPosTracksBeforeQA->GetXaxis()->SetTitleOffset(0.9);
                DrawAutoGammaHisto(fHistClusterdEtaPosTracksBeforeQA,
                                     " ",
                                     "#Delta#eta_{Cluster - pos. Tracks}",
									 "#frac{d#it{N}}{d#Delta#eta}",
                                     0,0,0,
                                     0,0,0,
                                     1,-0.3,0.3);
                PutProcessLabelAndEnergyOnPlot(0.8, 0.9, 0.03, fCollisionSystem.Data(), fPlot.Data(), Form("%s clusters", calo.Data()));
                canvas->SetLogy(0); canvas->SetLogz(0); canvas->Update();
                canvas->SaveAs(Form("%s/dEta_posTracks_%s_%s.%s", outputDir.Data(), fPrefix.Data(),"beforeClusterQA", suffix.Data()));
                canvas->Clear();
            }
//---------
			fHistClusterdPhiPosTracksBeforeQA = fHistClusterdEtadPhiPosTracksBeforeQA->ProjectionY("fHistClusterdPhiPosTracksBeforeQA",1,300);
            if(fHistClusterdPhiPosTracksBeforeQA){
				fHistClusterdPhiPosTracksBeforeQA->GetXaxis()->SetTitleOffset(0.9);
                DrawAutoGammaHisto(fHistClusterdPhiPosTracksBeforeQA,
                                     " ",
                                     "#Delta#phi_{Cluster - pos. Tracks}",
									 "#frac{d#it{N}}{d#Delta#phi}",
                                     0,0,0,
                                     0,0,0,
                                     1,-0.3,0.3);
                PutProcessLabelAndEnergyOnPlot(0.8, 0.9, 0.03, fCollisionSystem.Data(), fPlot.Data(), Form("%s clusters", calo.Data()));
                canvas->SetLogy(0); canvas->SetLogz(0); canvas->Update();
                canvas->SaveAs(Form("%s/dPhi_posTracks_%s_%s.%s", outputDir.Data(), fPrefix.Data(),"beforeClusterQA", suffix.Data()));
                canvas->Clear();
            }
        }
 //---------
		fHistClusterdEtadPhiPosTracksAfterQA = (TH2F*)CaloCutsContainer->FindObject(Form("dEtaVsdPhi_posTracks_afterClusterQA %s", fClusterCutSelection[i].Data()));
        if(fHistClusterdEtadPhiPosTracksAfterQA){
			cvsQuadratic->cd();
            DrawAutoGammaHisto2D(fHistClusterdEtadPhiPosTracksAfterQA,
                                 " ",
                                 "#Delta#eta_{Cluster - unmatched pos. Tracks}",
                                 "#Delta#phi_{Cluster - unmatched pos. Tracks}",
                                 "",
                                 0,0,0,
                                 0,0,0,
								 1,1.2);
            boxLabel->Draw();
			PutProcessLabelAndEnergyOnPlot(0.6, 0.9, 0.03, fCollisionSystem.Data(), fPlot.Data(), Form("%s clusters", calo.Data()));
			cvsQuadratic->SetLogy(0); cvsQuadratic->SetLogz(0); cvsQuadratic->Update();
			cvsQuadratic->SaveAs(Form("%s/dEtaVsdPhi_posTracks_%s_%s.%s", outputDir.Data(), fPrefix.Data(),"afterClusterQA", suffix.Data()));
			cvsQuadratic->Clear();
//---------
			canvas->cd();
//---------
			fHistClusterdEtaPosTracksAfterQA = fHistClusterdEtadPhiPosTracksAfterQA->ProjectionX("fHistClusterdEtaPosTracksAfterQA",1,300);
            if(fHistClusterdEtaPosTracksAfterQA){
				fHistClusterdEtaPosTracksAfterQA->GetXaxis()->SetTitleOffset(0.9);
                DrawAutoGammaHisto(fHistClusterdEtaPosTracksAfterQA,
                                     " ",
                                     "#Delta#eta_{Cluster - unmatched pos. Tracks}",
									 "#frac{d#it{N}}{d#Delta#eta}",
                                     0,0,0,
                                     0,0,0,
                                     1,-0.3,0.3);
                PutProcessLabelAndEnergyOnPlot(0.8, 0.9, 0.03, fCollisionSystem.Data(), fPlot.Data(), Form("%s clusters", calo.Data()));
                canvas->SetLogy(0); canvas->SetLogz(0); canvas->Update();
                canvas->SaveAs(Form("%s/dEta_posTracks_%s_%s.%s", outputDir.Data(), fPrefix.Data(),"afterClusterQA", suffix.Data()));
                canvas->Clear();
            }
//---------
			fHistClusterdPhiPosTracksAfterQA = fHistClusterdEtadPhiPosTracksAfterQA->ProjectionY("fHistClusterdPhiPosTracksAfterQA",1,300);
            if(fHistClusterdPhiPosTracksAfterQA){
				fHistClusterdPhiPosTracksAfterQA->GetXaxis()->SetTitleOffset(0.9);
                DrawAutoGammaHisto(fHistClusterdPhiPosTracksAfterQA,
                                     " ",
                                     "#Delta#phi_{Cluster - unmatched pos. Tracks}",
									 "#frac{d#it{N}}{d#Delta#phi}",
                                     0,0,0,
                                     0,0,0,
                                     1,-0.3,0.3);
                PutProcessLabelAndEnergyOnPlot(0.8, 0.9, 0.03, fCollisionSystem.Data(), fPlot.Data(), Form("%s clusters", calo.Data()));
                canvas->SetLogy(0); canvas->SetLogz(0); canvas->Update();
                canvas->SaveAs(Form("%s/dPhi_posTracks_%s_%s.%s", outputDir.Data(), fPrefix.Data(),"afterClusterQA", suffix.Data()));
                canvas->Clear();
            }
        }
//---------
		fHistClusterdEtadPhiNegTracksBeforeQA = (TH2F*)CaloCutsContainer->FindObject(Form("dEtaVsdPhi_negTracks_beforeClusterQA %s", fClusterCutSelection[i].Data()));
        if(fHistClusterdEtadPhiNegTracksBeforeQA){
			cvsQuadratic->cd();
            DrawAutoGammaHisto2D(fHistClusterdEtadPhiNegTracksBeforeQA,
                                 " ",
                                 "#Delta#eta_{Cluster - neg. Tracks}",
                                 "#Delta#phi_{Cluster - neg. Tracks}",
                                 "",
                                 0,0,0,
                                 0,0,0,
								 1,1.2);
            boxLabel->Draw();
			PutProcessLabelAndEnergyOnPlot(0.6, 0.9, 0.03, fCollisionSystem.Data(), fPlot.Data(), Form("%s clusters", calo.Data()));
			cvsQuadratic->SetLogy(0); cvsQuadratic->SetLogz(1); cvsQuadratic->Update();
			cvsQuadratic->SaveAs(Form("%s/dEtaVsdPhi_negTracks_%s_%s.%s", outputDir.Data(), fPrefix.Data(),"beforeClusterQA", suffix.Data()));
			cvsQuadratic->Clear();
//---------
			canvas->cd();
//---------
			fHistClusterdEtaNegTracksBeforeQA = fHistClusterdEtadPhiNegTracksBeforeQA->ProjectionX("fHistClusterdEtaNegTracksBeforeQA",1,300);
            if(fHistClusterdEtaNegTracksBeforeQA){
				fHistClusterdEtaNegTracksBeforeQA->GetXaxis()->SetTitleOffset(0.9);
                DrawAutoGammaHisto(fHistClusterdEtaNegTracksBeforeQA,
                                   " ",
                                   "#Delta#eta_{Cluster - neg. Tracks}",
								   "#frac{d#it{N}}{d#Delta#eta}",
                                   0,0,0,
                                   0,0,0,
                                   1,-0.3,0.3);
                PutProcessLabelAndEnergyOnPlot(0.8, 0.9, 0.03, fCollisionSystem.Data(), fPlot.Data(), Form("%s clusters", calo.Data()));
                canvas->SetLogy(0); canvas->SetLogz(0); canvas->Update();
                canvas->SaveAs(Form("%s/dEta_negTracks_%s_%s.%s", outputDir.Data(), fPrefix.Data(),"beforeClusterQA", suffix.Data()));
                canvas->Clear();
            }
//---------
			fHistClusterdPhiNegTracksBeforeQA = fHistClusterdEtadPhiNegTracksBeforeQA->ProjectionY("fHistClusterdPhiNegTracksBeforeQA",1,300);
            if(fHistClusterdPhiNegTracksBeforeQA){
				fHistClusterdPhiNegTracksBeforeQA->GetXaxis()->SetTitleOffset(0.9);
                DrawAutoGammaHisto(fHistClusterdPhiNegTracksBeforeQA,
                                   " ",
                                   "#Delta#phi_{Cluster - neg. Tracks}",
								   "#frac{d#it{N}}{d#Delta#phi}",
                                   0,0,0,
                                   0,0,0,
                                   1,-0.3,0.3);
                PutProcessLabelAndEnergyOnPlot(0.8, 0.9, 0.03, fCollisionSystem.Data(), fPlot.Data(), Form("%s clusters", calo.Data()));
                canvas->SetLogy(0); canvas->SetLogz(0); canvas->Update();
                canvas->SaveAs(Form("%s/dPhi_negTracks_%s_%s.%s", outputDir.Data(), fPrefix.Data(),"beforeClusterQA", suffix.Data()));
                canvas->Clear();
            }
        }
//---------
		fHistClusterdEtadPhiNegTracksAfterQA = (TH2F*)CaloCutsContainer->FindObject(Form("dEtaVsdPhi_negTracks_afterClusterQA %s", fClusterCutSelection[i].Data()));
        if(fHistClusterdEtadPhiNegTracksAfterQA){
			cvsQuadratic->cd();
            DrawAutoGammaHisto2D(fHistClusterdEtadPhiNegTracksAfterQA,
                                 " ",
                                 "#Delta#eta_{Cluster - unmatched neg. Tracks}",
                                 "#Delta#phi_{Cluster - unmatched neg. Tracks}",
                                 "",
                                 0,0,0,
                                 0,0,0,
								 1,1.2);
            boxLabel->Draw();
			PutProcessLabelAndEnergyOnPlot(0.6, 0.9, 0.03, fCollisionSystem.Data(), fPlot.Data(), Form("%s clusters", calo.Data()));
			cvsQuadratic->SetLogy(0); cvsQuadratic->SetLogz(0); cvsQuadratic->Update();
			cvsQuadratic->SaveAs(Form("%s/dEtaVsdPhi_negTracks_%s_%s.%s", outputDir.Data(), fPrefix.Data(),"afterClusterQA", suffix.Data()));
			cvsQuadratic->Clear();
//---------
			canvas->cd();
//---------
			fHistClusterdEtaNegTracksAfterQA = fHistClusterdEtadPhiNegTracksAfterQA->ProjectionX("fHistClusterdEtaNegTracksAfterQA",1,300);
            if(fHistClusterdEtaNegTracksAfterQA){
				fHistClusterdEtaNegTracksAfterQA->GetXaxis()->SetTitleOffset(0.9);
                DrawAutoGammaHisto(fHistClusterdEtaNegTracksAfterQA,
                                   " ",
                                   "#Delta#eta_{Cluster - unmatched neg. Tracks}",
								   "#frac{d#it{N}}{d#Delta#eta}",
                                   0,0,0,
                                   0,0,0,
                                   1,-0.3,0.3);
                PutProcessLabelAndEnergyOnPlot(0.8, 0.9, 0.03, fCollisionSystem.Data(), fPlot.Data(), Form("%s clusters", calo.Data()));
                canvas->SetLogy(0); canvas->SetLogz(0); canvas->Update();
                canvas->SaveAs(Form("%s/dEta_negTracks_%s_%s.%s", outputDir.Data(), fPrefix.Data(),"afterClusterQA", suffix.Data()));
                canvas->Clear();
            }
//---------
			fHistClusterdPhiNegTracksAfterQA = fHistClusterdEtadPhiNegTracksAfterQA->ProjectionY("fHistClusterdPhiNegTracksAfterQA",1,300);
            if(fHistClusterdPhiNegTracksAfterQA){
				fHistClusterdPhiNegTracksAfterQA->GetXaxis()->SetTitleOffset(0.9);
                DrawAutoGammaHisto(fHistClusterdPhiNegTracksAfterQA,
                                   " ",
                                   "#Delta#phi_{Cluster - unmatched neg. Tracks}",
								   "#frac{d#it{N}}{d#Delta#phi}",
                                   0,0,0,
                                   0,0,0,
                                   1,-0.3,0.3);
                PutProcessLabelAndEnergyOnPlot(0.8, 0.9, 0.03, fCollisionSystem.Data(), fPlot.Data(), Form("%s clusters", calo.Data()));
                canvas->SetLogy(0); canvas->SetLogz(0); canvas->Update();
                canvas->SaveAs(Form("%s/dPhi_negTracks_%s_%s.%s", outputDir.Data(), fPrefix.Data(),"afterClusterQA", suffix.Data()));
                canvas->Clear();
            }
        }
//---------
        if(fHistClusterdEtadPhiBeforeQA){
            fHistClusterdEtadPhiMatchedAfterQA = (TH2F*) fHistClusterdEtadPhiBeforeQA->Clone();
            fHistClusterdEtadPhiMatchedAfterQA->Add(fHistClusterdEtadPhiAfterQA,-1);
        }
        if(fHistClusterdEtadPhiMatchedAfterQA){
			cvsQuadratic->cd();
            DrawAutoGammaHisto2D(fHistClusterdEtadPhiMatchedAfterQA,
                                 " ",
								 "#Delta#eta_{Cluster - matched Tracks}",
                                 "#Delta#phi_{Cluster - matched Tracks}",
                                 "",
                                 0,0,0,
                                 0,0,0,
								 1,1.2);
            boxLabel->Draw();
			PutProcessLabelAndEnergyOnPlot(0.6, 0.9, 0.03, fCollisionSystem.Data(), fPlot.Data(), Form("%s clusters", calo.Data()));
			cvsQuadratic->SetLogy(0); cvsQuadratic->SetLogz(1); cvsQuadratic->Update();
			cvsQuadratic->SaveAs(Form("%s/dEtaVsdPhi_matched_%s_%s.%s", outputDir.Data(), fPrefix.Data(),"afterClusterQA", suffix.Data()));
			cvsQuadratic->Clear();
//---------
			canvas->cd();
//---------
			fHistClusterdEtaMatchedAfterQA = fHistClusterdEtadPhiMatchedAfterQA->ProjectionX("fHistClusterdEtaMatchedAfterQA",1,300);
            if(fHistClusterdEtaMatchedAfterQA){
                TGaxis::SetExponentOffset(-0.04, -0.04, "x");
				fHistClusterdEtaMatchedAfterQA->GetXaxis()->SetTitleOffset(0.9);
                DrawAutoGammaHisto(fHistClusterdEtaMatchedAfterQA,
                                     " ",
                                     "#Delta#eta_{Cluster - matched Tracks}",
									 "#frac{d#it{N}}{d#Delta#eta}",
                                     0,0,0,
                                     0,0,0,
                                     1,-0.05,0.05);
                PutProcessLabelAndEnergyOnPlot(0.8, 0.9, 0.03, fCollisionSystem.Data(), fPlot.Data(), Form("%s clusters", calo.Data()));
                canvas->SetLogy(0); canvas->SetLogz(0); canvas->Update();
                canvas->SaveAs(Form("%s/dEta_matched_%s_%s.%s", outputDir.Data(), fPrefix.Data(),"afterClusterQA", suffix.Data()));
                canvas->Clear();
                TGaxis::SetExponentOffset(0, 0, "x");
            }
//---------
			fHistClusterdPhiMatchedAfterQA = fHistClusterdEtadPhiMatchedAfterQA->ProjectionY("fHistClusterdPhiMatchedAfterQA",1,300);
            if(fHistClusterdPhiMatchedAfterQA){
                TGaxis::SetExponentOffset(-0.04, -0.04, "x");
				fHistClusterdPhiMatchedAfterQA->GetXaxis()->SetTitleOffset(0.9);
                DrawAutoGammaHisto(fHistClusterdPhiMatchedAfterQA,
                                     " ",
                                     "#Delta#phi_{Cluster - matched Tracks}",
									 "#frac{d#it{N}}{d#Delta#phi}",
                                     0,0,0,
                                     0,0,0,
                                     1,-0.05,0.05);
                PutProcessLabelAndEnergyOnPlot(0.8, 0.9, 0.03, fCollisionSystem.Data(), fPlot.Data(), Form("%s clusters", calo.Data()));
                canvas->SetLogy(0); canvas->SetLogz(0); canvas->Update();
                canvas->SaveAs(Form("%s/dPhi_matched_%s_%s.%s", outputDir.Data(), fPrefix.Data(),"afterClusterQA", suffix.Data()));
                canvas->Clear();
                TGaxis::SetExponentOffset(0, 0, "x");
            }
        }
//---------
        if(fHistDistanceTrackToClusterBeforeQA){
            fHistDistanceTrackToClusterMatchedAfterQA = (TH1F*) fHistDistanceTrackToClusterBeforeQA->Clone();
            fHistDistanceTrackToClusterMatchedAfterQA->Add(fHistDistanceTrackToClusterAfterQA, -1);
            fHistDistanceTrackToClusterMatchedAfterQA->GetXaxis()->SetTitleOffset(1.3);
            canvas->SetBottomMargin(0.15);
            DrawAutoGammaHisto(fHistDistanceTrackToClusterMatchedAfterQA,
                                 " ",
								 "r = #sqrt{#Delta#eta_{Cluster - matched Tracks}^{2}+#Delta#phi_{Cluster - matched Tracks}^{2}}",
								 "#frac{d#it{N}}{d#it{r}}",
                                 0,0,0,
                                 1,1,1E5,
                                 1,0,0.2);
            PutProcessLabelAndEnergyOnPlot(0.8, 0.9, 0.03, fCollisionSystem.Data(), fPlot.Data(), Form("%s clusters", calo.Data()));
            canvas->SetLogy(1); canvas->SetLogz(0); canvas->Update();
            canvas->SaveAs(Form("%s/DistanceToTrack_matched_%s_%s.%s", outputDir.Data(), fPrefix.Data(),"afterClusterQA", suffix.Data()));
            canvas->Clear();
            canvas->SetBottomMargin(bottomMargin);
        }
//---------
        cvsQuadratic->cd();
//---------
        if(fHistClusterM20M02BeforeQA){
            fHistClusterM20M02MatchedAfterQA = (TH2F*) fHistClusterM20M02BeforeQA->Clone();
            fHistClusterM20M02MatchedAfterQA->Add(fHistClusterM20M02AfterQA,-1);
            fHistClusterM20M02MatchedAfterQA->GetXaxis()->SetDecimals();
            fHistClusterM20M02MatchedAfterQA->GetXaxis()->SetLabelOffset(0.01);
            fHistClusterM20M02MatchedAfterQA->GetYaxis()->SetLabelOffset(0.01);
            DrawAutoGammaHisto2D(fHistClusterM20M02MatchedAfterQA,
                                 " ",
								 "#lambda_{1}^{2}",
								 "#lambda_{0}^{2}",
                                 "",
								 1,0.05,0.55,
								 1,0,0.55,
                                 1,1.2);
			PutProcessLabelAndEnergyOnPlot(0.62, 0.25, 0.03, fCollisionSystem.Data(), fPlot.Data(), Form("%s clusters", calo.Data()));
            cvsQuadratic->SetLogy(0); cvsQuadratic->SetLogz(1); cvsQuadratic->Update();
            cvsQuadratic->SaveAs(Form("%s/M20VsM02_matched_%s_%s.%s", outputDir.Data(), fPrefix.Data(),"afterClusterQA", suffix.Data()));
            cvsQuadratic->Clear();
        }
//---------
		fHistClusterdEtadPhiPosTracksP_000_075BeforeQA = (TH2F*)CaloCutsContainer->FindObject(Form("dEtaVsdPhi_posTracks_P<0.75_beforeClusterQA %s", fClusterCutSelection[i].Data()));
		if(fHistClusterdEtadPhiPosTracksP_000_075BeforeQA){
			DrawAutoGammaHisto2D(fHistClusterdEtadPhiPosTracksP_000_075BeforeQA,
                                 " ",
								 "#Delta#eta_{Cluster - pos. Tracks with #it{p}_{T}<0.75 GeV/#it{c}}",
								 "#Delta#phi_{Cluster - pos. Tracks with #it{p}_{T}<0.75 GeV/#it{c}}",
                                 "",
                                 0,0,0,
                                 0,0,0,
								 1,1.2);
            boxLabel->Draw();
			PutProcessLabelAndEnergyOnPlot(0.6, 0.9, 0.03, fCollisionSystem.Data(), fPlot.Data(), Form("%s clusters", calo.Data()));
			cvsQuadratic->SetLogy(0); cvsQuadratic->SetLogz(1); cvsQuadratic->Update();
			cvsQuadratic->SaveAs(Form("%s/dEtaVsdPhi_posTracks_000_075_%s_%s.%s", outputDir.Data(), fPrefix.Data(),"beforeClusterQA", suffix.Data()));
			cvsQuadratic->Clear();
        }
//---------
		cvsQuadratic->cd();
		fHistClusterdEtadPhiPosTracksP_075_125BeforeQA = (TH2F*)CaloCutsContainer->FindObject(Form("dEtaVsdPhi_posTracks_0.75<P<1.25_beforeClusterQA %s", fClusterCutSelection[i].Data()));
		if(fHistClusterdEtadPhiPosTracksP_075_125BeforeQA){
			DrawAutoGammaHisto2D(fHistClusterdEtadPhiPosTracksP_075_125BeforeQA,
                                 " ",
								 "#Delta#eta_{Cluster - pos. Tracks with 0.75<#it{p}_{T}<1.25 GeV/#it{c}}",
								 "#Delta#phi_{Cluster - pos. Tracks with 0.75<#it{p}_{T}<1.25 GeV/#it{c}}",
                                 "",
                                 0,0,0,
                                 0,0,0,
								 1,1.2);
            boxLabel->Draw();
			PutProcessLabelAndEnergyOnPlot(0.6, 0.9, 0.03, fCollisionSystem.Data(), fPlot.Data(), Form("%s clusters", calo.Data()));
			cvsQuadratic->SetLogy(0); cvsQuadratic->SetLogz(1); cvsQuadratic->Update();
			cvsQuadratic->SaveAs(Form("%s/dEtaVsdPhi_posTracks_075_125_%s_%s.%s", outputDir.Data(), fPrefix.Data(),"beforeClusterQA", suffix.Data()));
			cvsQuadratic->Clear();
        }
//---------
		fHistClusterdEtadPhiPosTracksP_125_999BeforeQA = (TH2F*)CaloCutsContainer->FindObject(Form("dEtaVsdPhi_posTracks_P>1.25_beforeClusterQA %s", fClusterCutSelection[i].Data()));
		if(fHistClusterdEtadPhiPosTracksP_125_999BeforeQA){
			DrawAutoGammaHisto2D(fHistClusterdEtadPhiPosTracksP_125_999BeforeQA,
                                 " ",
								 "#Delta#eta_{Cluster - pos. Tracks with #it{p}_{T}>1.25 GeV/#it{c}}",
								 "#Delta#phi_{Cluster - pos. Tracks with #it{p}_{T}>1.25 GeV/#it{c}}",
                                 "",
                                 0,0,0,
                                 0,0,0,
								 1,1.2);
            boxLabel->Draw();
			PutProcessLabelAndEnergyOnPlot(0.6, 0.9, 0.03, fCollisionSystem.Data(), fPlot.Data(), Form("%s clusters", calo.Data()));
			cvsQuadratic->SetLogy(0); cvsQuadratic->SetLogz(1); cvsQuadratic->Update();
			cvsQuadratic->SaveAs(Form("%s/dEtaVsdPhi_posTracks_125_999_%s_%s.%s", outputDir.Data(), fPrefix.Data(),"beforeClusterQA", suffix.Data()));
			cvsQuadratic->Clear();
        }
//---------
		fHistClusterdEtadPhiNegTracksP_000_075BeforeQA = (TH2F*)CaloCutsContainer->FindObject(Form("dEtaVsdPhi_negTracks_P<0.75_beforeClusterQA %s", fClusterCutSelection[i].Data()));
		if(!fHistClusterdEtadPhiNegTracksP_000_075BeforeQA) fHistClusterdEtadPhiNegTracksP_000_075BeforeQA = (TH2F*)CaloCutsContainer->FindObject(Form("dEtaVsdPhi_negTrack_P<0.75_beforeClusterQA %s", fClusterCutSelection[i].Data()));
		if(fHistClusterdEtadPhiNegTracksP_000_075BeforeQA){
			DrawAutoGammaHisto2D(fHistClusterdEtadPhiNegTracksP_000_075BeforeQA,
                                 " ",
								 "#Delta#eta_{Cluster - neg. Tracks with #it{p}_{T}<0.75 GeV/#it{c}}",
								 "#Delta#phi_{Cluster - neg. Tracks with #it{p}_{T}<0.75 GeV/#it{c}}",
                                 "",
                                 0,0,0,
                                 0,0,0,
								 1,1.2);
            boxLabel->Draw();
			PutProcessLabelAndEnergyOnPlot(0.6, 0.9, 0.03, fCollisionSystem.Data(), fPlot.Data(), Form("%s clusters", calo.Data()));
			cvsQuadratic->SetLogy(0); cvsQuadratic->SetLogz(1); cvsQuadratic->Update();
			cvsQuadratic->SaveAs(Form("%s/dEtaVsdPhi_negTracks_000_075_%s_%s.%s", outputDir.Data(), fPrefix.Data(),"beforeClusterQA", suffix.Data()));
			cvsQuadratic->Clear();
        }
//---------
		fHistClusterdEtadPhiNegTracksP_075_125BeforeQA = (TH2F*)CaloCutsContainer->FindObject(Form("dEtaVsdPhi_negTracks_0.75<P<1.25_beforeClusterQA %s", fClusterCutSelection[i].Data()));
		if(fHistClusterdEtadPhiNegTracksP_075_125BeforeQA){
			DrawAutoGammaHisto2D(fHistClusterdEtadPhiNegTracksP_075_125BeforeQA,
                                 " ",
								 "#Delta#eta_{Cluster - neg. Tracks with 0.75<#it{p}_{T}<1.25 GeV/#it{c}}",
								 "#Delta#phi_{Cluster - neg. Tracks with 0.75<#it{p}_{T}<1.25 GeV/#it{c}}",
                                 "",
                                 0,0,0,
                                 0,0,0,
								 1,1.2);
            boxLabel->Draw();
			PutProcessLabelAndEnergyOnPlot(0.6, 0.9, 0.03, fCollisionSystem.Data(), fPlot.Data(), Form("%s clusters", calo.Data()));
			cvsQuadratic->SetLogy(0); cvsQuadratic->SetLogz(1); cvsQuadratic->Update();
			cvsQuadratic->SaveAs(Form("%s/dEtaVsdPhi_negTracks_075_125_%s_%s.%s", outputDir.Data(), fPrefix.Data(),"beforeClusterQA", suffix.Data()));
			cvsQuadratic->Clear();
        }
//---------
		fHistClusterdEtadPhiNegTracksP_125_999BeforeQA = (TH2F*)CaloCutsContainer->FindObject(Form("dEtaVsdPhi_negTracks_P>1.25_beforeClusterQA %s", fClusterCutSelection[i].Data()));
		if(fHistClusterdEtadPhiNegTracksP_125_999BeforeQA){
			DrawAutoGammaHisto2D(fHistClusterdEtadPhiNegTracksP_125_999BeforeQA,
                                 " ",
								 "#Delta#eta_{Cluster - neg. Tracks with #it{p}_{T}>1.25 GeV/#it{c}}",
								 "#Delta#phi_{Cluster - neg. Tracks with #it{p}_{T}>1.25 GeV/#it{c}}",
                                 "",
                                 0,0,0,
                                 0,0,0,
								 1,1.2);
            boxLabel->Draw();
			PutProcessLabelAndEnergyOnPlot(0.6, 0.9, 0.03, fCollisionSystem.Data(), fPlot.Data(), Form("%s clusters", calo.Data()));
			cvsQuadratic->SetLogy(0); cvsQuadratic->SetLogz(1); cvsQuadratic->Update();
			cvsQuadratic->SaveAs(Form("%s/dEtaVsdPhi_negTracks_125_999_%s_%s.%s", outputDir.Data(), fPrefix.Data(),"beforeClusterQA", suffix.Data()));
			cvsQuadratic->Clear();
		}
//---------
		canvas->cd();
//---------
// Detailed QA: SuperModule  & Towers
		TGaxis::SetExponentOffset(-0.06, -0.04, "x");
		fHistClusterCellIDsBeforeQA = (TH1F*)CaloExtQAContainer->FindObject(Form("ClusterIncludedCells_beforeClusterQA %s", fClusterCutSelection[i].Data()));
		if(fHistClusterCellIDsBeforeQA){
			DrawAutoGammaHisto(fHistClusterCellIDsBeforeQA,
								 Form("%s - %s - %s clusters",fCollisionSystem.Data(), fPlot.Data(), calo.Data()),
								 "CellID in all Clusters",
								 "#frac{d#it{N}}{d#it{CellID}}",
								 0,0,0,
								 0,0,0,
								 1,0,nCaloCells);
			canvas->SetLogx(0); canvas->SetLogy(1); canvas->SetLogz(0); canvas->Update();
			canvas->SaveAs(Form("%s/ClusterIncludedCells_%s_%s.%s", outputDir.Data(), fPrefix.Data(),"beforeClusterQA", suffix.Data()));
			canvas->Clear();
		}
		fHistClusterCellIDsAfterQA = (TH1F*)CaloExtQAContainer->FindObject(Form("ClusterIncludedCells_afterClusterQA %s", fClusterCutSelection[i].Data()));
		if(fHistClusterCellIDsAfterQA){
			DrawAutoGammaHisto(fHistClusterCellIDsAfterQA,
								 Form("%s - %s - %s clusters",fCollisionSystem.Data(), fPlot.Data(), calo.Data()),
								 "Cell ID in accepted Clusters",
								 "#frac{d#it{N}}{d#it{Cell ID}}",
								 0,0,0,
								 0,0,0,
								 1,0,nCaloCells);
			canvas->SetLogx(0); canvas->SetLogy(1); canvas->SetLogz(0); canvas->Update();
			canvas->SaveAs(Form("%s/ClusterIncludedCells_%s_%s.%s", outputDir.Data(), fPrefix.Data(),"afterClusterQA", suffix.Data()));
			canvas->Clear();
		}
		fHistClusterCellEFracBeforeQA = (TH1F*)CaloExtQAContainer->FindObject(Form("ClusterEnergyFracCells_beforeClusterQA %s", fClusterCutSelection[i].Data()));
		if(fHistClusterCellEFracBeforeQA){
			fHistClusterCellEFracBeforeQA->Sumw2();
			fHistClusterCellIDsBeforeQA->Sumw2();
			fHistClusterCellEFracBeforeQA->Divide(fHistClusterCellIDsBeforeQA);
			DrawAutoGammaHisto(fHistClusterCellEFracBeforeQA,
								 Form("%s - %s - %s clusters",fCollisionSystem.Data(), fPlot.Data(), calo.Data()),
								 "Energy Fraction of CellID in all Clusters",
								 "#frac{d#it{N}}{d#it{CellID}}",
								 0,0,0,
								 1,0,1,
								 1,0,nCaloCells);
			canvas->SetLogx(0); canvas->SetLogy(0); canvas->SetLogz(0); canvas->Update();
			canvas->SaveAs(Form("%s/ClusterEnergyFracCells_%s_%s.%s", outputDir.Data(), fPrefix.Data(),"beforeClusterQA", suffix.Data()));
			canvas->Clear();
		}
		fHistClusterCellEFracAfterQA = (TH1F*)CaloExtQAContainer->FindObject(Form("ClusterEnergyFracCells_afterClusterQA %s", fClusterCutSelection[i].Data()));
		if(fHistClusterCellEFracAfterQA){
			fHistClusterCellEFracAfterQA->Sumw2();
			fHistClusterCellIDsAfterQA->Sumw2();
			fHistClusterCellEFracAfterQA->Divide(fHistClusterCellIDsAfterQA);
			DrawAutoGammaHisto(fHistClusterCellEFracAfterQA,
								 Form("%s - %s - %s clusters",fCollisionSystem.Data(), fPlot.Data(), calo.Data()),
								 "Energy Fraction of CellID in accepted Clusters",
								 "#frac{d#it{N}}{d#it{Cell ID}}",
								 0,0,0,
								 1,0,1,
								 1,0,nCaloCells);
			canvas->SetLogx(0); canvas->SetLogy(0); canvas->SetLogz(0); canvas->Update();
			canvas->SaveAs(Form("%s/ClusterEnergyFracCells_%s_%s.%s", outputDir.Data(), fPrefix.Data(),"afterClusterQA", suffix.Data()));
			canvas->Clear();
		}
		TGaxis::SetExponentOffset(0, 0, "x");
		canvas->SetRightMargin(0.1);
		fHistClusterEnergyVsModule = (TH2F*)CaloExtQAContainer->FindObject(Form("ClusterEnergyVsModule_afterClusterQA %s", fClusterCutSelection[i].Data()));
		if(fHistClusterEnergyVsModule){
			DrawAutoGammaHisto2D(fHistClusterEnergyVsModule,
								 Form("%s - %s - %s clusters",fCollisionSystem.Data(), fPlot.Data(), calo.Data()),
								 "Cluster Energy (GeV)",
								 "SuperModule Number",
								 "",
								 1,0,nCaloModules,
								 0,0,0,
								 1,1);
			canvas->SetLogx(0); canvas->SetLogy(0); canvas->SetLogz(1); canvas->Update();
			canvas->SaveAs(Form("%s/ClusterEnergyVsModule_%s.%s", outputDir.Data(), fPrefix.Data(), suffix.Data()));
			canvas->Clear();

			PlotCaloQAModule(fHistClusterEnergyVsModule,
							 nCaloModules,
							 "Cluster Energy (GeV)",
							 "#frac{dE}{dN}",
							 1,0,30,kTRUE);
			PutProcessLabelAndEnergyOnPlot(0.7, 0.9, 0.03, fCollisionSystem.Data(), fPlot.Data(), Form("%s clusters", calo.Data()));
			canvas->SetLogx(0); canvas->SetLogy(1); canvas->SetLogz(0); canvas->Update();
			canvas->SaveAs(Form("%s/ClusterEnergyVsModule_Projected_%s.%s", outputDir.Data(), fPrefix.Data(), suffix.Data()));
			canvas->Clear();
		}
		fHistClusterEnergyVsNCells = (TH2F*)CaloExtQAContainer->FindObject(Form("ClusterEnergyVsNCells_afterQA %s", fClusterCutSelection[i].Data()));
		if(fHistClusterEnergyVsNCells){
			DrawAutoGammaHisto2D(fHistClusterEnergyVsNCells,
								 " ",
								 "Cluster Energy (GeV)",
								 "#it{N}_{Cells} per Cluster",
								 "",
								 1,1,30,
								 0,0,0,
								 1,1);
			PutProcessLabelAndEnergyOnPlot(0.7, 0.9, 0.03, fCollisionSystem.Data(), fPlot.Data(), Form("%s clusters", calo.Data()));
			canvas->SetLogx(0); canvas->SetLogy(0); canvas->SetLogz(1); canvas->Update();
			canvas->SaveAs(Form("%s/ClusterEnergyVsNCells_%s.%s", outputDir.Data(), fPrefix.Data(), suffix.Data()));
			canvas->Clear();
		}
		fHistModuleEnergyVsModule = (TH2F*)CaloExtQAContainer->FindObject(Form("ModuleEnergyVsModule %s", fClusterCutSelection[i].Data()));
		if(fHistModuleEnergyVsModule){
			DrawAutoGammaHisto2D(fHistModuleEnergyVsModule,
								 Form("%s - %s - %s clusters",fCollisionSystem.Data(), fPlot.Data(), calo.Data()),
								 "Total SuperModule Energy per Event (GeV)",
								 "SuperModule Number",
								 "",
								 1,0,nCaloModules,
								 0,0,0,
								 1,1);
			canvas->SetLogx(0); canvas->SetLogy(0); canvas->SetLogz(1); canvas->Update();
			canvas->SaveAs(Form("%s/ModuleEnergyVsModule_%s.%s", outputDir.Data(), fPrefix.Data(), suffix.Data()));
			canvas->Clear();

			PlotCaloQAModule(fHistModuleEnergyVsModule,
							 nCaloModules,
							 "Total SuperModule Energy per Event (GeV)",
							 "#frac{dE}{dN}",
							 1,0,100,kFALSE);
			PutProcessLabelAndEnergyOnPlot(0.7, 0.9, 0.03, fCollisionSystem.Data(), fPlot.Data(), Form("%s clusters", calo.Data()));
			canvas->SetLogx(1); canvas->SetLogy(1); canvas->Update();
			canvas->SaveAs(Form("%s/ModuleEnergyVsModule_Projected_%s.%s", outputDir.Data(), fPrefix.Data(), suffix.Data()));
			canvas->Clear();
		}
		fHistNCellsAbove100VsModule = (TH2F*)CaloExtQAContainer->FindObject(Form("NCellsAbove100VsModule %s", fClusterCutSelection[i].Data()));
		if(fHistNCellsAbove100VsModule){
			DrawAutoGammaHisto2D(fHistNCellsAbove100VsModule,
								 Form("%s - %s - %s clusters",fCollisionSystem.Data(), fPlot.Data(), calo.Data()),
								 "#it{N}_{Cells}>100 MeV in SM per Event",
								 "SuperModule Number",
								 "",
								 1,0,nCaloModules,
								 0,0,0,
								 1,1);
			canvas->SetLogx(0); canvas->SetLogy(0); canvas->SetLogz(1); canvas->Update();
			canvas->SaveAs(Form("%s/NCellsAbove100VsModule_%s.%s", outputDir.Data(), fPrefix.Data(), suffix.Data()));
			canvas->Clear();

			PlotCaloQAModule(fHistNCellsAbove100VsModule,
							 nCaloModules,
							 "#it{N}_{Cells}>100 MeV in SM per Event",
							 "#frac{d#it{N}_{Cells}>100 MeV}{dN}",
							 0,0,0,kFALSE);
			PutProcessLabelAndEnergyOnPlot(0.7, 0.9, 0.03, fCollisionSystem.Data(), fPlot.Data(), Form("%s clusters", calo.Data()));
			canvas->SetLogx(1); canvas->SetLogy(1); canvas->Update();
			canvas->SaveAs(Form("%s/NCellsAbove100VsModule_Projected_%s.%s", outputDir.Data(), fPrefix.Data(), suffix.Data()));
			canvas->Clear();
		}
		fHistNCellsAbove1500VsModule = (TH2F*)CaloExtQAContainer->FindObject(Form("NCellsAbove1500VsModule %s", fClusterCutSelection[i].Data()));
		if(fHistNCellsAbove1500VsModule){
			DrawAutoGammaHisto2D(fHistNCellsAbove1500VsModule,
								 Form("%s - %s - %s clusters",fCollisionSystem.Data(), fPlot.Data(), calo.Data()),
								 "#it{N}_{Cells}>1500 MeV in SM per Event",
								 "SuperModule Number",
								 "",
								 1,0,nCaloModules,
								 0,0,0,
								 1,1);
			canvas->SetLogx(0); canvas->SetLogy(0); canvas->SetLogz(1); canvas->Update();
			canvas->SaveAs(Form("%s/NCellsAbove1500VsModule_%s.%s", outputDir.Data(), fPrefix.Data(), suffix.Data()));
			canvas->Clear();

			PlotCaloQAModule(fHistNCellsAbove1500VsModule,
							 nCaloModules,
							 "#it{N}_{Cells}>1500 MeV in SM per Event",
							 "#frac{d#it{N}_{Cells}>1500 MeV}{dN}",
							 0,0,0,kFALSE);
			PutProcessLabelAndEnergyOnPlot(0.7, 0.9, 0.03, fCollisionSystem.Data(), fPlot.Data(), Form("%s clusters", calo.Data()));
			canvas->SetLogx(1); canvas->SetLogy(1); canvas->Update();
			canvas->SaveAs(Form("%s/NCellsAbove1500VsModule_Projected_%s.%s", outputDir.Data(), fPrefix.Data(), suffix.Data()));
			canvas->Clear();
		}
// saved as .pdf per default due to size of histogram
		fHistCellEnergyVsCellID = (TH2F*)CaloExtQAContainer->FindObject(Form("CellEnergyVsCellID %s", fClusterCutSelection[i].Data()));
		fHistCellTimeVsCellID = (TH2F*)CaloExtQAContainer->FindObject(Form("CellTimeVsCellID %s", fClusterCutSelection[i].Data()));

		if(fHistCellEnergyVsCellID){
			DrawAutoGammaHisto2D(fHistCellEnergyVsCellID,
								 Form("%s - %s - %s clusters",fCollisionSystem.Data(), fPlot.Data(), calo.Data()),
								 "Cell Energy (GeV)",
								 "CellID",
								 "",
								 1,0,nCaloCells,
								 0,0,0,
								 1,1);
			canvas->SetLogx(0); canvas->SetLogy(0); canvas->SetLogz(1); canvas->Update();
			canvas->SaveAs(Form("%s/CellEnergyVsCellID_%s.pdf", outputDir.Data(), fPrefix.Data()));
			canvas->Clear();
			DrawAutoGammaHisto2D(fHistCellEnergyVsCellID,
								 Form("%s - %s - %s clusters",fCollisionSystem.Data(), fPlot.Data(), calo.Data()),
								 "Cell Energy (GeV)",
								 "CellID",
								 "",
								 1,0,nCaloCells,
								 1,0,2,
								 1,1);
			canvas->SetLogx(0); canvas->SetLogy(0); canvas->SetLogz(1); canvas->Update();
			canvas->SaveAs(Form("%s/CellEnergyVsCellID_LowEnergy_%s.pdf", outputDir.Data(), fPrefix.Data()));
			canvas->Clear();
			PlotCellMeanVsSigma(cellQA,nCaloCells,fHistCellEnergyVsCellID,
							 "Mean Cell Energy (GeV)",
							 "#sigma_{Cell Energy} (GeV)",
							 0,0,0,
							 0,0,0,kTRUE,isMC);
			if(i==2 && plotQACuts){
				line->DrawLine(cellQA->EnergyMean[1],cellQA->EnergySigma[0],cellQA->EnergyMean[1],cellQA->EnergySigma[1]);
				line->DrawLine(cellQA->EnergyMean[0],cellQA->EnergySigma[1],cellQA->EnergyMean[1],cellQA->EnergySigma[1]);
			}
			PutProcessLabelAndEnergyOnPlot(0.7, 0.9, 0.03, fCollisionSystem.Data(), fPlot.Data(), Form("%s clusters", calo.Data()));
			canvas->SetLogx(0); canvas->SetLogy(0); canvas->SetLogz(1); canvas->Update();
			canvas->SaveAs(Form("%s/CellEnergyVsSigma_%s.%s", outputDir.Data(), fPrefix.Data(), suffix.Data()));
			canvas->Clear();
			PlotHotCells(cellQA,0,nCaloCells,fHistCellTimeVsCellID,
							 "N_{Cell fired}",
							 "#frac{dN_{Cell fired with E>0.2 GeV}}{dN}",
							 0,0,0,
							 0,0,0,isMC);
			if(i==2 && plotQACuts){
				line->DrawLine(cellQA->HotCells1D[0],0,cellQA->HotCells1D[0],10);
				line->DrawLine(cellQA->HotCells1D[1],0,cellQA->HotCells1D[1],10);
			}
			PutProcessLabelAndEnergyOnPlot(0.7, 0.9, 0.03, fCollisionSystem.Data(), fPlot.Data(), Form("%s clusters", calo.Data()));
			canvas->SetLogx(0); canvas->SetLogy(1); canvas->SetLogz(0); canvas->Update();
			canvas->SaveAs(Form("%s/CellHotCells_%s.%s", outputDir.Data(), fPrefix.Data(), suffix.Data()));
			canvas->Clear();
			PlotHotCells(cellQA,1,nCaloCells,fHistCellEnergyVsCellID,
							 "N_{Cell fired with Energy L to 30 GeV} / N_{Cell fired with Energy 0 to L GeV}",
							 "Integration Limit 'L' (GeV)",
							 0,0,0,
							 0,0,0,isMC,0.95);
			if(i==2 && plotQACuts){
				const Int_t dim2D= 9;
				for(Int_t ii=0; ii<dim2D; ii++){
					line->DrawLine(cellQA->HotCells2D[ii][0],0.1+ii*0.1,cellQA->HotCells2D[ii][0],0.2+ii*0.1);
					line->DrawLine(cellQA->HotCells2D[ii][1],0.1+ii*0.1,cellQA->HotCells2D[ii][1],0.2+ii*0.1);
				}
			}
			PutProcessLabelAndEnergyOnPlot(0.7, 0.9, 0.03, fCollisionSystem.Data(), fPlot.Data(), Form("%s clusters", calo.Data()));
			canvas->SetLogx(1); canvas->SetLogy(0); canvas->SetLogz(1); canvas->Update();
			canvas->SaveAs(Form("%s/CellHotCells2D_%s.%s", outputDir.Data(), fPrefix.Data(), suffix.Data()));
			canvas->Clear();
		}
		TGaxis::SetExponentOffset(0.5, 0, "x");
// saved as .jpg per default due to size of histogram

		if(fHistCellTimeVsCellID){
			DrawAutoGammaHisto2D(fHistCellTimeVsCellID,
								 Form("%s - %s - %s clusters",fCollisionSystem.Data(), fPlot.Data(), calo.Data()),
								 "Cell Time (#mus)",
								 "CellID",
								 "",
								 1,0,nCaloCells,
								 0,0,0,
								 1,1);
			canvas->SetLogx(0); canvas->SetLogy(0); canvas->SetLogz(1); canvas->Update();
			canvas->SaveAs(Form("%s/CellTimeVsCellID_%s.jpg", outputDir.Data(), fPrefix.Data()));
			canvas->Clear();
			PlotCellMeanVsSigma(cellQA,nCaloCells,fHistCellTimeVsCellID,
							 "Mean Cell Time (#mus)",
							 "#sigma_{Cell Time} (#mus)",
							 0,0,0,
							 0,0,0,kFALSE,isMC);
			if(i==2 && plotQACuts){
				line->DrawLine(cellQA->TimeMean[0],cellQA->TimeSigma[0],cellQA->TimeMean[1],cellQA->TimeSigma[0]);
				line->DrawLine(cellQA->TimeMean[0],cellQA->TimeSigma[0],cellQA->TimeMean[0],cellQA->TimeSigma[1]);
				line->DrawLine(cellQA->TimeMean[1],cellQA->TimeSigma[0],cellQA->TimeMean[1],cellQA->TimeSigma[1]);
				line->DrawLine(cellQA->TimeMean[0],cellQA->TimeSigma[1],cellQA->TimeMean[1],cellQA->TimeSigma[1]);
			}
			TGaxis::SetExponentOffset(0, 0.5, "y");
			PutProcessLabelAndEnergyOnPlot(0.7, 0.9, 0.03, fCollisionSystem.Data(), fPlot.Data(), Form("%s clusters", calo.Data()));
			canvas->SetLogx(0); canvas->SetLogy(0); canvas->SetLogz(1); canvas->Update();
			canvas->SaveAs(Form("%s/CellTimeVsSigma_%s.%s", outputDir.Data(), fPrefix.Data(), suffix.Data()));
			canvas->Clear();
			PlotHotCells(cellQA,2,nCaloCells,fHistCellTimeVsCellID,
							 "N_{Cell fired} / N_{Cell fired at |t|< 0.02 (#mus)} - E_{Cell}>0.2 GeV",
							 "# of Entries",
							 0,0,0,
							 0,0,0,isMC,0.95);
			if(i==2 && plotQACuts){
				//line->DrawLine(cellQA->HotCellsTime1D[0],0,cellQA->HotCellsTime1D[0],10);
				line->DrawLine(cellQA->HotCellsTime1D[1],0,cellQA->HotCellsTime1D[1],10);
			}
			PutProcessLabelAndEnergyOnPlot(0.7, 0.9, 0.03, fCollisionSystem.Data(), fPlot.Data(), Form("%s clusters", calo.Data()));
			canvas->SetLogx(0); canvas->SetLogy(1); canvas->SetLogz(0); canvas->Update();
			canvas->SaveAs(Form("%s/CellHotCellsTime1D_%s.%s", outputDir.Data(), fPrefix.Data(), suffix.Data()));
			canvas->Clear();
		}
//-----------------------------------
		fEMCalBadChannels = (TProfile*)CaloExtQAContainer->FindObject(Form("%s - Bad Channels",calo.Data()));
		if(fEMCalBadChannels){
			fEMCalBadChannels->GetXaxis()->SetTitle("Cell ID");
			fEMCalBadChannels->GetYaxis()->SetTitle("Cell ID Bad in Fraction of Events");
			fEMCalBadChannels->GetYaxis()->SetLabelFont(42);
			fEMCalBadChannels->GetXaxis()->SetLabelFont(42);
			fEMCalBadChannels->GetYaxis()->SetTitleFont(62);
			fEMCalBadChannels->GetXaxis()->SetTitleFont(62);
			fEMCalBadChannels->GetYaxis()->SetLabelSize(0.035);
			fEMCalBadChannels->GetYaxis()->SetTitleSize(0.043);
			fEMCalBadChannels->GetYaxis()->SetDecimals();
			fEMCalBadChannels->GetXaxis()->SetTitleSize(0.043);
			fEMCalBadChannels->GetXaxis()->SetLabelSize(0.035);
			fEMCalBadChannels->DrawCopy();
			PutProcessLabelAndEnergyOnPlot(0.8, 0.9, 0.03, fCollisionSystem.Data(), fPlot.Data(), Form("%s clusters", calo.Data()));
			canvas->SetLogx(0); canvas->SetLogy(0); canvas->SetLogz(0); canvas->Update();
			canvas->SaveAs(Form("%s/BadChannels_%s.%s", outputDir.Data(), fPrefix.Data(), suffix.Data()));
			canvas->Clear();
		}

		canvas->SetRightMargin(rightMargin);
		TGaxis::SetExponentOffset(0, 0, "x");
		TGaxis::SetExponentOffset(0, 0, "y");

//---------
		if(ClusterContainer){
			TCanvas* cvsEM02 = new TCanvas("cvs2pads","",2250,1500);
			DrawGammaCanvasSettings(cvsEM02, 0.09, 0.13, 0.01, 0.1);
			cvsEM02->cd();
			TF1 *min = new TF1("min","exp(2.135-0.245*x)",4.95,13.63);
			min->SetLineColor(kBlack);
			min->SetLineStyle(2);
			TF1 *cnst = new TF1("cnst","0.3",13.63,50.05);
			cnst->SetLineColor(kBlack);
			cnst->SetLineStyle(2);
			TF1 *max = new TF1("max","exp(0.353-0.0264*x)-0.524+0.00559*x+21.9/x",9.5,50.05);
			max->SetLineColor(kBlack);
			max->SetLineStyle(2);
			fHistClusterTrueGammaEM02 = (TH2F*)ClusterContainer->FindObject("TrueClusGammaEM02");
			if(fHistClusterTrueGammaEM02){
				fHistClusterTrueGammaEM02->Scale(1/nEvents);
				DrawAutoGammaHistoPaper2D(fHistClusterTrueGammaEM02,
										" ",
										"E (GeV)",
										"#lambda_{0}^{2}",
										0,0,0,
										1,0.1,2.95,
										1,4.95,50.05,0.8,0.65);
				fHistClusterTrueGammaEM02->GetXaxis()->SetMoreLogLabels();
				fHistClusterTrueGammaEM02->GetXaxis()->SetLabelOffset(-0.02);
				fHistClusterTrueGammaEM02->GetZaxis()->SetRangeUser(1E-8,5E-5);
				fHistClusterTrueGammaEM02->GetZaxis()->SetLabelSize(0.051);
				fHistClusterTrueGammaEM02->GetXaxis()->SetTickLength(0.05);
				fHistClusterTrueGammaEM02->DrawCopy("COLZ");
				PutProcessLabelAndEnergyOnPlot(0.55, 0.99, 0.06, fCollisionSystem.Data(), "", "", 42);
				PutProcessLabelAndEnergyOnPlot(0.12, 0.2, 0.06, "#gamma", "", "", 42);
				cvsEM02->SetLogx(1); cvsEM02->SetLogy(0); cvsEM02->SetLogz(1); cvsEM02->Update();
				cvsEM02->SaveAs(Form("%s/EVsM02_TrueGamma_%s.%s", outputDir.Data(), fPrefix.Data(), suffix.Data()));
				cvsEM02->Clear();
			}
			fHistClusterTruePi0EM02 = (TH2F*)ClusterContainer->FindObject("TrueClusPi0EM02");
			if(fHistClusterTruePi0EM02){
				fHistClusterTruePi0EM02->Scale(1/nEvents);
				DrawAutoGammaHistoPaper2D(fHistClusterTruePi0EM02,
										" ",
										"E (GeV)",
										"#lambda_{0}^{2}",
										0,0,0,
										1,0.1,2.95,
										1,4.95,50.05,0.8,0.65);
				fHistClusterTruePi0EM02->GetXaxis()->SetMoreLogLabels();
				fHistClusterTruePi0EM02->GetXaxis()->SetLabelOffset(-0.02);
				fHistClusterTruePi0EM02->GetZaxis()->SetRangeUser(1E-8,5E-5);
				fHistClusterTruePi0EM02->GetZaxis()->SetLabelSize(0.051);
				fHistClusterTruePi0EM02->GetXaxis()->SetTickLength(0.05);
				fHistClusterTruePi0EM02->DrawCopy("COLZ");
				PutProcessLabelAndEnergyOnPlot(0.55, 0.99, 0.06, fCollisionSystem.Data(), "", "", 42);
				PutProcessLabelAndEnergyOnPlot(0.3, 0.6, 0.06, "#pi^{0}", "", "", 42);
				cvsEM02->SetLogx(1); cvsEM02->SetLogy(0); cvsEM02->SetLogz(1); cvsEM02->Update();
				cvsEM02->SaveAs(Form("%s/EVsM02_TruePi0_%s.%s", outputDir.Data(), fPrefix.Data(), suffix.Data()));
				cvsEM02->Clear();
			}
			if(fHistClusterTrueGammaEM02&&fHistClusterTruePi0EM02){
				fHistClusterTrueGammaEM02->Add(fHistClusterTruePi0EM02,1);
				fHistClusterTrueGammaEM02->SetName("TrueClusGammaPi0EM02");
				fHistClusterTrueGammaEM02->GetZaxis()->SetRangeUser(1E-8,5E-5);
				fHistClusterTrueGammaEM02->GetZaxis()->SetLabelSize(0.051);
				fHistClusterTrueGammaEM02->GetXaxis()->SetTickLength(0.05);
				fHistClusterTrueGammaEM02->DrawCopy("COLZ");
				min->Draw("same");
				cnst->Draw("same");
				max->Draw("same");
				PutProcessLabelAndEnergyOnPlot(0.55, 0.99, 0.06, fCollisionSystem.Data(), "", "", 42);
				PutProcessLabelAndEnergyOnPlot(0.3, 0.6, 0.06, "#pi^{0}", "", "", 42);
				PutProcessLabelAndEnergyOnPlot(0.12, 0.2, 0.06, "#gamma", "", "", 42);
				cvsEM02->SetLogx(1); cvsEM02->SetLogy(0); cvsEM02->SetLogz(1); cvsEM02->Update();
				cvsEM02->SaveAs(Form("%s/EVsM02_TrueGamma_Pi0_%s.%s", outputDir.Data(), fPrefix.Data(), suffix.Data()));
				cvsEM02->Clear();
			}
		}
//---------
		canvas->cd();
        TH2D* mother = (TH2D*) ESDContainer->FindObject("ESD_Mother_InvMass_Pt");
        TH2D* motherMatched = (TH2D*) ESDContainer->FindObject("ESD_MotherMatched_InvMass_Pt");

        if(mother && motherMatched){

            fHistInvMassPtMotherMotherMatched = new TH2D("Mother_InvMass/(MotherMatched_InvMass + Mother_InvMass)","Mother_InvMass/(MotherMatched_InvMass + Mother_InvMass)", 800, 0, 0.8, 250, 0, 25);
            for(Int_t x = 1; x <= 800; x++) {
                for(Int_t y = 1; y <= 250; y++) {
                    Double_t a = mother->GetBinContent(x,y);
                    Double_t b = motherMatched->GetBinContent(x,y);
                    Double_t r = 0;
                    if ( (a+b)!= 0 ) r = a/(a+b);
                    fHistInvMassPtMotherMotherMatched->SetBinContent(x,y,r);
                }
            }

            DrawAutoGammaHisto2D(fHistInvMassPtMotherMotherMatched,
                                 " ",
								 "#it{M}_{inv, Mother} (GeV/#it{c}^{2})",
								 "#it{p}_{T, Mother} (GeV/#it{c})",
                                 "",
                                 0,0,0,
                                 0,0,0,
                                 1,0.8);

			TString whichTrMatch = fClusterCutSelection[i].Copy();
            whichTrMatch.Remove(8,9); whichTrMatch.Remove(0,7);

            Double_t xLabel = 0.5;
            if(isRunNum) xLabel = 0.4;
			if(i==2 && CheckForData8TeV(DataSet)) xLabel = 0.45;
            TLatex* label1 = new TLatex(xLabel, 0.84, Form("%s: #frac{Accepted Mother-Candidates}{All Mother-Candidates}",fPlot.Data()));
            TLatex* label2 = new TLatex(xLabel, 0.79, Form( "PCM, %s TrackMatchingCuts:",calo.Data()));
            TLatex* label3 = new TLatex(xLabel, 0.75, Form( "- |#Delta#eta|<%s", TrackMatchingEtaMax[whichTrMatch.Atoi()].Data()));
            TLatex* label4 = new TLatex(xLabel, 0.71, Form( "- e^{+}: %s<#Delta#phi<%s; e^{-}: %.2f<#Delta#phi<%.2f", TrackMatchingPhiMin[whichTrMatch.Atoi()].Data(), TrackMatchingPhiMax[whichTrMatch.Atoi()].Data(), (-1* TrackMatchingPhiMax[whichTrMatch.Atoi()].Atof()) , (-1* TrackMatchingPhiMin[whichTrMatch.Atoi()].Atof()) ));

            label1->SetNDC();
            label1->SetTextColor(1);
            label1->SetTextSize(0.03);
            label1->Draw();
            label2->SetNDC();
            label2->SetTextColor(1);
            label2->SetTextSize(0.03);
            label2->Draw();
            label3->SetNDC();
            label3->SetTextColor(1);
            label3->SetTextSize(0.03);
            label3->Draw();
            label4->SetNDC();
            label4->SetTextColor(1);
            label4->SetTextSize(0.03);
            label4->Draw();

            canvas->SetRightMargin(0.1);
            canvas->SetLogy(0); canvas->SetLogz(0); canvas->Update();
			canvas->SaveAs(Form("%s/%s_%s_cut%i.%s", outputDir.Data(),"TrackMatchingCut", fPrefix.Data(), whichTrMatch.Atoi(), suffix.Data()));
            canvas->Clear();
//---------
			TH2D* mcPi0 = 0x0;
			TH2D* mcEta = 0x0;
			TH2D* mcPi0Matched_MC = 0x0;
			TH2D* mcEtaMatched_MC = 0x0;
			TH2D* mcPi0Matched_True = 0x0;
			TH2D* mcEtaMatched_True = 0x0;

			TH1D* mcFractionMatchesMissingPt[2] = {0x0,0x0};
			TH1D* mcFractionMatchesTooManyPt[2] = {0x0,0x0};

			Double_t nDataMatches = 0;
			Double_t nMCMatches = 0;
			Double_t nTrueMCMatches = 0;

			Double_t nMCMatches_Missing = 0;
			Double_t nMCMatches_TooMany = 0;

            if(TrueContainer)
            {
				mcPi0 = (TH2D*) TrueContainer->FindObject("ESD_TruePi0_InvMass_Pt");
				mcEta = (TH2D*) TrueContainer->FindObject("ESD_TrueEta_InvMass_Pt");
				mcPi0Matched_MC = (TH2D*) TrueContainer->FindObject("ESD_TruePi0_Matched_InvMass_Pt");
				mcEtaMatched_MC = (TH2D*) TrueContainer->FindObject("ESD_TrueEta_Matched_InvMass_Pt");
				mcPi0Matched_True = (TH2D*) TrueContainer->FindObject("ESD_TruePi0CaloConvertedPhotonMatched_InvMass_Pt");
				mcEtaMatched_True = (TH2D*) TrueContainer->FindObject("ESD_TrueEtaCaloConvertedPhotonMatched_InvMass_Pt");
            }

			if( mcPi0Matched_True && mcEtaMatched_True)
            {
				TH2D* matched_True = (TH2D*) mcPi0Matched_True->Clone("matched_True");
				matched_True->Add(mcEtaMatched_True,1);

				fHistInvMassPtMotherMatchedCompare_Matched_True = new TH2D("(MotherMatched_InvMass-TrueMotherMatched_InvMass)/(MotherMatched_InvMass+TrueMotherMatched_InvMass)","(MotherMatched_InvMass-TrueMotherMatched_InvMass)/(MotherMatched_InvMass+TrueMotherMatched_InvMass)", 800, 0, 0.8, 250, 0, 25);
                for(Int_t x = 1; x <= 800; x++) {
                    for(Int_t y = 1; y <= 250; y++) {
						Double_t a = motherMatched->GetBinContent(x,y);
						Double_t b = matched_True->GetBinContent(x,y);
						nDataMatches += a;
                        Double_t r = 0;
						if( a == 0 && b == 0) r = -2;
						else r = (a-b)/(a+b);
//                        if ( b != 0 ) r = a/b;
//                        else if( a > 0 ) r = 10;
						fHistInvMassPtMotherMatchedCompare_Matched_True->SetBinContent(x,y,r);
                    }
                }

//                fHistInvMassPtMotherMatchedCompare_Matched_True->GetZaxis()->SetRangeUser(0.1,10);
				fHistInvMassPtMotherMatchedCompare_Matched_True->GetZaxis()->SetRangeUser(-1,1);

				DrawAutoGammaHisto2D(fHistInvMassPtMotherMatchedCompare_Matched_True,
                                     " ",
									 "#it{M}_{inv, Mother} (GeV/#it{c}^{2})",
									 "#it{p}_{T, Mother} (GeV/#it{c})",
                                     "",
                                     0,0,0,
                                     0,0,0,
                                     1,0.8);
				TLatex* label11 = new TLatex(xLabel, 0.86, Form("%s: #frac{V0^{full MC}_{rejected} - V0^{TrueMC}_{rejected}}{V0^{full MC}_{rejected} + V0^{TrueMC}_{rejected}}",fPlot.Data()));
                label11->SetNDC();
                label11->SetTextColor(1);
                label11->SetTextSize(0.03);
                label11->Draw();
                label2->Draw();
                label3->Draw();
                label4->Draw();

                canvas->SetLogy(0); canvas->SetLogz(0); canvas->Update();
				canvas->SaveAs(Form("%s/%s_%s_cut%i.%s", outputDir.Data(),"TrackMatchingRatio_fullMC_TrueMC", fPrefix.Data(), whichTrMatch.Atoi(), suffix.Data()));
                canvas->Clear();
			}

			if( mcPi0Matched_MC && mcEtaMatched_MC)
			{
				TH2D* matched_MC = (TH2D*) mcPi0Matched_MC->Clone("matched_MC");
				matched_MC->Add(mcEtaMatched_MC,1);

				fHistInvMassPtMotherMatchedCompare_Matched_MC = new TH2D("(MotherMatched_InvMass-MCMatched_InvMass)/(MotherMatched_InvMass+MCMatched_InvMass)","(MotherMatched_InvMass-MCMatched_InvMass)/(MotherMatched_InvMass+MCMatched_InvMass)", 800, 0, 0.8, 250, 0, 25);
				for(Int_t x = 1; x <= 800; x++) {
					for(Int_t y = 1; y <= 250; y++) {
						Double_t a = motherMatched->GetBinContent(x,y);
						Double_t b = matched_MC->GetBinContent(x,y);
						Double_t r = 0;
						if( a == 0 && b == 0) r = -2;
						else r = (a-b)/(a+b);
//                        if ( b != 0 ) r = a/b;
//                        else if( a > 0 ) r = 10;
						fHistInvMassPtMotherMatchedCompare_Matched_MC->SetBinContent(x,y,r);
					}
				}

//                fHistInvMassPtMotherMatchedCompare_Matched_MC->GetZaxis()->SetRangeUser(0.1,10);
				fHistInvMassPtMotherMatchedCompare_Matched_MC->GetZaxis()->SetRangeUser(-1,1);

				DrawAutoGammaHisto2D(fHistInvMassPtMotherMatchedCompare_Matched_MC,
									 " ",
									 "#it{M}_{inv, Mother} (GeV/#it{c}^{2})",
									 "#it{p}_{T, Mother} (GeV/#it{c})",
									 "",
									 0,0,0,
									 0,0,0,
									 1,0.8);
				TLatex* label11 = new TLatex(xLabel, 0.86, Form("%s: #frac{V0^{full MC}_{rejected} - V0^{MC}_{rejected}}{V0^{full MC}_{rejected} + V0^{MC}_{rejected}}",fPlot.Data()));
				label11->SetNDC();
				label11->SetTextColor(1);
				label11->SetTextSize(0.03);
				label11->Draw();
				label2->Draw();
				label3->Draw();
				label4->Draw();

				canvas->SetLogy(0); canvas->SetLogz(0); canvas->Update();
				canvas->SaveAs(Form("%s/%s_%s_cut%i.%s", outputDir.Data(),"TrackMatchingRatio_fullMC_MC", fPrefix.Data(), whichTrMatch.Atoi(), suffix.Data()));
				canvas->Clear();
			}

			if( mcPi0Matched_True && mcEtaMatched_True && mcPi0Matched_MC && mcEtaMatched_MC)
			{
				TH2D* matched_True = (TH2D*) mcPi0Matched_True->Clone("matched_True2");
				matched_True->Add(mcEtaMatched_True,1);
				TH2D* matched_MC = (TH2D*) mcPi0Matched_MC->Clone("matched_MC2");
				matched_MC->Add(mcEtaMatched_MC,1);

				fHistInvMassPtMotherMatchedCompare_True_MC = new TH2D("(TrueMotherMatched_InvMass-MCMatched_InvMass)/(TrueMotherMatched_InvMass+MCMatched_InvMass)","(TrueMotherMatched_InvMass-MCMatched_InvMass)/(TrueMotherMatched_InvMass+MCMatched_InvMass)", 800, 0, 0.8, 250, 0, 25);
				for(Int_t x = 1; x <= 800; x++) {
					for(Int_t y = 1; y <= 250; y++) {
						Double_t a = matched_True->GetBinContent(x,y);
						Double_t b = matched_MC->GetBinContent(x,y);
						nTrueMCMatches += a;
						nMCMatches += b;
						Double_t r = 0;
						if( a == 0 && b == 0) r = -2;
						else r = (a-b)/(a+b);
//                        if ( b != 0 ) r = a/b;
//                        else if( a > 0 ) r = 10;
						fHistInvMassPtMotherMatchedCompare_True_MC->SetBinContent(x,y,r);
						if( a > b ) nMCMatches_Missing += abs(a-b);
						if( a < b ) nMCMatches_TooMany += abs(a-b);
					}
				}

//                fHistInvMassPtMotherMatchedCompare_True_MC->GetZaxis()->SetRangeUser(0.1,10);
				fHistInvMassPtMotherMatchedCompare_True_MC->GetZaxis()->SetRangeUser(-1,1);

				DrawAutoGammaHisto2D(fHistInvMassPtMotherMatchedCompare_True_MC,
									 " ",
									 "#it{M}_{inv, Mother} (GeV/#it{c}^{2})",
									 "#it{p}_{T, Mother} (GeV/#it{c})",
									 "",
									 0,0,0,
									 0,0,0,
									 1,0.8);
				TLatex* label11 = new TLatex(xLabel, 0.86, Form("%s: #frac{V0^{TrueMC}_{rejected} - V0^{MC}_{rejected}}{V0^{TrueMC}_{rejected} + V0^{MC}_{rejected}}",fPlot.Data()));
				label11->SetNDC();
				label11->SetTextColor(1);
				label11->SetTextSize(0.03);
				label11->Draw();
				label2->Draw();
				label3->Draw();
				label4->Draw();

				canvas->SetLogy(0); canvas->SetLogz(0); canvas->Update();
				canvas->SaveAs(Form("%s/%s_%s_cut%i.%s", outputDir.Data(),"TrackMatchingRatio_TrueMC_MC", fPrefix.Data(), whichTrMatch.Atoi(), suffix.Data()));
				canvas->Clear();
			}

			if( mcPi0Matched_True && mcEtaMatched_True && mcPi0Matched_MC && mcEtaMatched_MC )
			{
				TH2D* mcCompare = (TH2D*) mcPi0->Clone("mcPi0Eta_TrueTH1D");
				mcCompare->Add(mcEta,1);
				TH2D* matched_True = (TH2D*) mcPi0Matched_True->Clone("matched_TrueTH1D");
				matched_True->Add(mcEtaMatched_True,1);
				TH2D* matched_MC = (TH2D*) mcPi0Matched_MC->Clone("matched_MCTH1D");
				matched_MC->Add(mcEtaMatched_MC,1);

				Int_t rangeMin[2]={103,488};
				Int_t rangeMax[2]={157,598};

				for(Int_t iMeson=0; iMeson<2; iMeson++)
				{
					mcFractionMatchesMissingPt[iMeson] = new TH1D(Form("fractionMissing%i",iMeson)," ",fNBinsAnalysisPt,fBinsAnalysisPt);
					mcFractionMatchesTooManyPt[iMeson] = new TH1D(Form("fractionTooMany%i",iMeson)," ",fNBinsAnalysisPt,fBinsAnalysisPt);

					for(Int_t iPt = 0; iPt<fNBinsAnalysisPt; iPt++)
					{
						Double_t bMatchesMissing = 0;
						Double_t cMatchesTooMany = 0;
						Double_t tMatches = 0;
						for(Int_t x = rangeMin[iMeson]; x <= rangeMax[iMeson]; x++) {
							for(Int_t y = (fBinsAnalysisPt[iPt]*10)+1; y <= (fBinsAnalysisPt[iPt+1]*10); y++) {
								tMatches += mcCompare->GetBinContent(x,y);
								Double_t a = matched_True->GetBinContent(x,y);
								Double_t b = matched_MC->GetBinContent(x,y);
								if( a > b ) bMatchesMissing += abs(a-b);
								if( a < b) cMatchesTooMany += abs(a-b);
							}
						}
						Double_t rMiss, rTooMany;
						if(tMatches > 0 ) {
							rMiss = (bMatchesMissing / tMatches) * 100;
							rTooMany = (cMatchesTooMany / tMatches) * 100;
						}
						else{
							rMiss = 0;
							rTooMany = 0;
						}
						//cout << iMeson << " " << bMatchesMissing << " " << cMatchesTooMany << " " << tMatches << endl;
						mcFractionMatchesMissingPt[iMeson]->SetBinContent(iPt+1,rMiss);
						mcFractionMatchesTooManyPt[iMeson]->SetBinContent(iPt+1,rTooMany);
						//cout << fBinsAnalysisPt[iPt] << " - " << fBinsAnalysisPt[iPt+1] << ", rMiss:" << rMiss << ", rTooMany: " << rTooMany << ", rTotal: " << rTotal << ", rTooMany*rTotal*0.01: " << rTooMany*rTotal*0.01 <<endl;
					}

					EditTH1NoRunwise(mcFractionMatchesTooManyPt[iMeson],24,1.5,kAzure,kAzure,1.2,0.9);
					mcFractionMatchesTooManyPt[iMeson]->SetLineWidth(0.6);
					mcFractionMatchesTooManyPt[iMeson]->GetXaxis()->SetRangeUser(fBinsAnalysisPt[0],fBinsAnalysisPt[fNBinsAnalysisPt]+2);
					mcFractionMatchesTooManyPt[iMeson]->GetXaxis()->SetTitle("#it{p}_{T, #gamma#gamma} (GeV/#it{c})");
					mcFractionMatchesTooManyPt[iMeson]->GetYaxis()->SetRangeUser(1E-3,120);
					mcFractionMatchesTooManyPt[iMeson]->GetYaxis()->SetTitle("fraction of all true candidates (%)");
					mcFractionMatchesTooManyPt[iMeson]->Sumw2();
					mcFractionMatchesTooManyPt[iMeson]->Draw("p");

					EditTH1NoRunwise(mcFractionMatchesMissingPt[iMeson],20,1.5,kRed,kRed,1.2,0.9);
					mcFractionMatchesMissingPt[iMeson]->SetLineWidth(0.6);
					mcFractionMatchesMissingPt[iMeson]->Sumw2();
					mcFractionMatchesMissingPt[iMeson]->Draw("p, same");

					TLegend *legend = new TLegend(0.35,0.82,0.75,0.9);
					legend->SetNColumns(1);
					legend->SetFillColor(0);
					legend->SetLineColor(0);
					legend->SetTextSize(0.03);
					legend->SetTextFont(42);
					legend->AddEntry(mcFractionMatchesMissingPt[iMeson],"... misses true matching");
					legend->AddEntry(mcFractionMatchesTooManyPt[iMeson],"... removes true candidate by mistake");
					legend->Draw("same");

					TLatex* clusVZero = new TLatex(0.45, 0.91, "Cluster - V^{0}-track matching...");
					clusVZero->SetNDC();
					clusVZero->SetTextColor(1);
					clusVZero->SetTextFont(42);
					clusVZero->SetTextSize(0.03);
					clusVZero->Draw("SAME");

					PutProcessLabelAndEnergyOnPlot(0.15, 0.95, 0.03, fCollisionSystem.Data(), fPlot.Data(), fTextMeasurementMeson[iMeson].Data());
					PutProcessLabelAndEnergyOnPlot(0.15, 0.84, 0.03, Form("%i < #it{M}_{#gamma#gamma} < %i MeV/#it{c}^{2}",rangeMin[iMeson],rangeMax[iMeson]), Form("#gamma's rec. with PCM, %s",calo.Data()), "");

					canvas->SetRightMargin(0.02); canvas->SetLeftMargin(0.08); canvas->SetBottomMargin(0.12); canvas->SetTopMargin(0.02);
					canvas->SetLogx(1); canvas->SetLogy(1); canvas->SetLogz(0); canvas->Update();
					canvas->SaveAs(Form("%s/%s_%s_cut%i_%i.%s", outputDir.Data(),"TrackMatchingMissing_TrueMC_MC_Pt", fPrefix.Data(), whichTrMatch.Atoi(), iMeson, suffix.Data()));
					canvas->Clear();
					canvas->SetLogx(0);
					canvas->SetRightMargin(rightMargin); canvas->SetLeftMargin(leftMargin); canvas->SetBottomMargin(bottomMargin); canvas->SetTopMargin(topMargin);
				}
			}

			if( mcPi0 && mcPi0Matched_True && mcPi0Matched_MC)
			{
				TLegend *legend = new TLegend(0.3,0.8,0.7,0.9);
				legend->SetNColumns(1);
				legend->SetFillColor(0);
				legend->SetLineColor(0);
				legend->SetTextSize(0.03);
				legend->SetTextFont(42);

				TH2D* mcCompare = (TH2D*) mcPi0->Clone("mcCompare");
				//WORKAROUND - TO CHANGE WHEN NEW TRAIN RUN HAS HISTOGRAMS TILL 30 GeV!!!!!!!!!!!!!!!!!!
//				//--------------------------------------------------------------------------------------
				for(Int_t x = 1; x <= 800; x++) {
					for(Int_t y = 1; y <= 250; y++) {
						Double_t a = mcCompare->GetBinContent(x,y);
						Double_t b = mcPi0Matched_MC->GetBinContent(x,y);
						mcCompare->SetBinContent(x,y,(a+b));
					}
				}

				TH1D* projectTrue = (TH1D*) mcCompare->ProjectionX("projecttrue",1,300);
				legend->AddEntry(projectTrue,"True MC");
				projectTrue->Rebin(5);
				projectTrue->SetLineColor(1);
				DrawAutoGammaHisto(projectTrue,
								   " ",
								   "#it{M}_{#gamma#gamma} (GeV/#it{c}^{2})",
								   "d#it{N}/d#it{M}_{#gamma#gamma}",
								   0,0,0,
								   0,0,0,
								   1,0,0.8,0.7);

				TH1D* projectCompare = (TH1D*) mcPi0Matched_True->ProjectionX("projectcompare",1,300);
				legend->AddEntry(projectCompare,"Cluster - V^{0}-Track Matching");
				projectCompare->Rebin(5);
				projectCompare->SetLineColor(2);
				projectCompare->SetFillColor(2);
				projectCompare->SetFillStyle(3003);
				projectCompare->DrawCopy("same,e,hist");
				legend->Draw("same");

				PutProcessLabelAndEnergyOnPlot(0.7, 0.9, 0.03, fCollisionSystem.Data(), fPlot.Data(), Form("%s",fTextMeasurement.Data()));
				PutProcessLabelAndEnergyOnPlot(0.7, 0.79, 0.03, Form("#gamma's rec. with PCM, %s",calo.Data()), "", "");
				canvas->SetLogy(1); canvas->SetLogz(0); canvas->Update();
				canvas->SaveAs(Form("%s/TrackMatching_invMassPi0_withTrueMatches_%s.%s", outputDir.Data(), fPrefix.Data(), suffix.Data()));
				canvas->Clear();

				mcCompare->Add(mcPi0Matched_True,-1);
				TH1D* projectCompareW = (TH1D*) mcCompare->ProjectionX("projectcomparew",1,300);
				projectCompareW->Rebin(5);
				projectCompareW->SetLineColor(1);
				DrawAutoGammaHisto(projectCompareW,
								   " ",
								   "#it{M}_{#gamma#gamma} (GeV/#it{c}^{2})",
								   "d#it{N}/d#it{M}_{#gamma#gamma}",
								   0,0,0,
								   0,0,0,
								   1,0,0.8,0.7);
				PutProcessLabelAndEnergyOnPlot(0.7, 0.9, 0.03, fCollisionSystem.Data(), fPlot.Data(), Form("%s",fTextMeasurement.Data()));
				PutProcessLabelAndEnergyOnPlot(0.7, 0.79, 0.03, Form("#gamma's rec. with PCM, %s",calo.Data()), "", "");
				canvas->SetLogy(1); canvas->SetLogz(0); canvas->Update();
				canvas->SaveAs(Form("%s/TrackMatching_invMassPi0_withoutTrueMatches_%s.%s", outputDir.Data(), fPrefix.Data(), suffix.Data()));
				canvas->Clear();
			}

			if( mcPi0 && mcEta && mcPi0Matched_True && mcEtaMatched_True && mcPi0Matched_MC && mcEtaMatched_MC)
			{
				// QUICK IMPLEMENTATION OF PLOTTING 2 INV MASS HISTS, TO BE REMOVED...
				TCanvas* cvs2pads = new TCanvas("cvs2pads","",1350,1500);  // gives the page size
				TPad* pad1 = new TPad("pad1", "", 0., 0.53, 1., 1.,-1, -1, -2);
				pad1->SetLeftMargin(0.08);
				pad1->SetBottomMargin(0.00);
				pad1->SetRightMargin(0.02);
				pad1->SetTopMargin(0.02);
				pad1->SetLogy(1);
				pad1->Draw();
				TPad* pad2 = new TPad("pad2", "", 0., 0., 1., 0.53,-1, -1, -2);
				pad2->SetLeftMargin(0.08);
				pad2->SetBottomMargin(0.14);
				pad2->SetRightMargin(0.02);
				pad2->SetTopMargin(0.00);
				pad2->SetLogy(1);
				pad2->Draw();

				const Int_t nBin = 3;
				Int_t lowBin[nBin] = {0,10,40};
				Int_t upBin[nBin] = {300,12,50};
				for(Int_t iB=0; iB<nBin; iB++)
				{
					TLegend *legend = new TLegend(0.3,0.8,0.7,0.88);
					legend->SetNColumns(1);
					legend->SetFillColor(0);
					legend->SetLineColor(0);
					legend->SetTextSize(0.03);
					legend->SetTextFont(42);

					TH2D* mcCompare = (TH2D*) mcPi0->Clone(Form("mcComparePi0Eta_Bins%i-%i",lowBin[iB],upBin[iB]));
					mcCompare->Add(mcEta,1);
					//WORKAROUND - TO CHANGE WHEN NEW TRAIN RUN HAS HISTOGRAMS TILL 30 GeV!!!!!!!!!!!!!!!!!!
	//				//--------------------------------------------------------------------------------------
					for(Int_t x = 1; x <= 800; x++) {
						for(Int_t y = 1; y <= 250; y++) {
							Double_t a = mcCompare->GetBinContent(x,y);
							Double_t b = mcPi0Matched_MC->GetBinContent(x,y);
							Double_t c = mcEtaMatched_MC->GetBinContent(x,y);
							mcCompare->SetBinContent(x,y,(a+b+c));
						}
					}

					TH1D* projectTrue = (TH1D*) mcCompare->ProjectionX(Form("projecttruePi0Eta_Bins%i-%i",lowBin[iB],upBin[iB]),lowBin[iB],upBin[iB]);
					legend->AddEntry(projectTrue,"True MC");
					projectTrue->Rebin(10);
					projectTrue->SetLineColor(1);
					canvas->cd();
					DrawAutoGammaHisto(projectTrue,
									   " ",
									   "#it{M}_{#gamma#gamma} (GeV/#it{c}^{2})",
									   "d#it{N}/d#it{M}_{#gamma#gamma}",
									   0,0,0,
									   0,0,0,
									   1,0,0.8,0.7);

					canvas->SetRightMargin(rightMargin);
					TH1D* projectCompare = (TH1D*) mcPi0Matched_True->ProjectionX(Form("projectcomparePi0_Bins%i-%i",lowBin[iB],upBin[iB]),lowBin[iB],upBin[iB]);
					TH1D* projectCompareEta = (TH1D*) mcEtaMatched_True->ProjectionX(Form("projectcompareEta_Bins%i-%i",lowBin[iB],upBin[iB]),lowBin[iB],upBin[iB]);
					projectCompare->Add(projectCompareEta,1);
					legend->AddEntry(projectCompare,"Cluster - V^{0}-Track Matching");
					projectCompare->Rebin(10);
					projectCompare->SetLineColor(2);
					projectCompare->SetFillColor(2);
					projectCompare->SetFillStyle(3003);
					projectCompare->DrawCopy("same,e,hist");
					legend->Draw("same");

					PutProcessLabelAndEnergyOnPlot(0.7, 0.9, 0.03, fCollisionSystem.Data(), fPlot.Data(), Form("%s & %s",fTextMeasurement.Data(),fTextMeasurementEta.Data()));
					PutProcessLabelAndEnergyOnPlot(0.7, 0.785, 0.03, Form("%.1f < #it{p}_{T, #gamma#gamma} < %.1f GeV/#it{c}",mcCompare->GetYaxis()->GetBinUpEdge(lowBin[iB]),mcCompare->GetYaxis()->GetBinUpEdge(upBin[iB])),"","");
					PutProcessLabelAndEnergyOnPlot(0.7, 0.74, 0.03, Form("#gamma's rec. with PCM, %s",calo.Data()), "","");
					canvas->SetLogy(1); canvas->SetLogz(0); canvas->Update();
					canvas->SaveAs(Form("%s/TrackMatching_invMassPi0Eta_withTrueMatches_%s_Bins%i-%i.%s", outputDir.Data(), fPrefix.Data(), lowBin[iB],upBin[iB], suffix.Data()));
					canvas->Clear();

					// **** paper plots following, TrueMC+Matches
//					if(iB == nBin-1){
//						pad1->cd();
//						DrawAutoGammaHistoPaper(projectTrue,
//										   " ",
//										   "#it{M}_{#gamma#gamma} (GeV/#it{c}^{2})",
//										   "d#it{N}/d#it{M}_{#gamma#gamma}",
//										   0,0,0,
//										   1,0.5,8E3,
//										   1,0,0.8,0.6);
//						projectCompare->DrawCopy("same,e,hist");
//						PutProcessLabelAndEnergyOnPlot(0.65, 0.97, 0.051, fCollisionSystem.Data(), fPlot.Data(), Form("%s & %s",fTextMeasurement.Data(),fTextMeasurementEta.Data()));
//						PutProcessLabelAndEnergyOnPlot(0.1, 0.97, 0.051, Form("%.1f < #it{p}_{T, #gamma#gamma} < %.1f GeV/#it{c}",mcCompare->GetYaxis()->GetBinUpEdge(lowBin[iB]),mcCompare->GetYaxis()->GetBinUpEdge(upBin[iB])),"","");
//						PutProcessLabelAndEnergyOnPlot(0.65, 0.78, 0.051, Form("#gamma's rec. with PCM, %s",calo.Data()), "" ,"");
//					}else if(iB == nBin-2)
//					{
//						pad2->cd();
//						TLegend* leg2 = (TLegend*) legend->Clone();
//						leg2->SetX1(0.46);
//						leg2->SetX2(0.86);
//						leg2->SetY1(0.85);
//						leg2->SetY2(0.97);
//						leg2->SetTextSize(0.06);
//						DrawAutoGammaHistoPaper(projectTrue,
//										   " ",
//										   "#it{M}_{#gamma#gamma} (GeV/#it{c}^{2})",
//										   "d#it{N}/d#it{M}_{#gamma#gamma}",
//										   0,0,0,
//										   1,0.5,8E3,
//										   1,0,0.8,0.6);
//						projectCompare->DrawCopy("same,e,hist");
//						leg2->Draw("same");
//						PutProcessLabelAndEnergyOnPlot(0.1, 0.99, 0.048, Form("%.1f < #it{p}_{T, #gamma#gamma} < %.1f GeV/#it{c}",mcCompare->GetYaxis()->GetBinUpEdge(lowBin[iB]),mcCompare->GetYaxis()->GetBinUpEdge(upBin[iB])),"","");
//					}
					// **** paper plots following, TrueMC+Matches
					if(iB == nBin-1){
						pad1->cd();
						Double_t bin[2] = {0.7,9.9E3};
						if(CheckForData8TeV(DataSet)) {bin[1]=8E4;}
						DrawAutoGammaHistoPaper(projectTrue,
												" ",
												"#it{M}_{#gamma#gamma} (GeV/#it{c}^{2})",
												"d#it{N}/d#it{M}_{#gamma#gamma}",
												0,0,0,
												1,bin[0],bin[1],
												1,0,0.8,0.6);
						projectCompare->DrawCopy("same,e,hist");
						PutProcessLabelAndEnergyOnPlot(0.6, 0.98, 0.063, fCollisionSystem.Data(), fPlot.Data(), Form("%s & %s",fTextMeasurement.Data(),fTextMeasurementEta.Data()),42);
						PutProcessLabelAndEnergyOnPlot(0.1, 0.98, 0.063, Form("%.1f < #it{p}_{T, #gamma#gamma} < %.1f GeV/#it{c}",mcCompare->GetYaxis()->GetBinUpEdge(lowBin[iB]),mcCompare->GetYaxis()->GetBinUpEdge(upBin[iB])),"","",42);
						PutProcessLabelAndEnergyOnPlot(0.6, 0.74, 0.063, Form("#gamma's rec. with PCM, %s",calo.Data()), "" ,"",42);
					}else if(iB == nBin-2)
					{
						pad2->cd();
						TLegend* leg2 = (TLegend*) legend->Clone();
						leg2->SetX1(0.46);
						leg2->SetX2(0.86);
						leg2->SetY1(0.847);
						leg2->SetY2(0.967);
						leg2->SetTextSize(0.06);
						Double_t bin[2] = {0.7,9.9E3};
						if(CheckForData8TeV(DataSet)) {bin[1]=8E4;}
						DrawAutoGammaHistoPaper(projectTrue,
												" ",
												"#it{M}_{#gamma#gamma} (GeV/#it{c}^{2})",
												"d#it{N}/d#it{M}_{#gamma#gamma}",
												0,0,0,
												1,bin[0],bin[1],
												1,0,0.8,0.6);
						projectCompare->DrawCopy("same,e,hist");
						leg2->Draw("same");
						PutProcessLabelAndEnergyOnPlot(0.1, 1, 0.06, Form("%.1f < #it{p}_{T, #gamma#gamma} < %.1f GeV/#it{c}",mcCompare->GetYaxis()->GetBinUpEdge(lowBin[iB]),mcCompare->GetYaxis()->GetBinUpEdge(upBin[iB])),"","",42);
					}
					canvas->cd();

					mcCompare->Add(mcPi0Matched_True,-1);
					mcCompare->Add(mcEtaMatched_True,-1);
					TH1D* projectCompareW = (TH1D*) mcCompare->ProjectionX(Form("projectcomparew_Bins%i-%i",lowBin[iB],upBin[iB]),lowBin[iB],upBin[iB]);
					projectCompareW->Rebin(5);
					projectCompareW->SetLineColor(1);
					DrawAutoGammaHisto(projectCompareW,
									   " ",
									   "#it{M}_{#gamma#gamma} (GeV/#it{c}^{2})",
									   "d#it{N}/d#it{M}_{#gamma#gamma}",
									   0,0,0,
									   0,0,0,
									   1,0,0.8);
					PutProcessLabelAndEnergyOnPlot(0.7, 0.9, 0.03, fCollisionSystem.Data(), fPlot.Data(), Form("%s & %s",fTextMeasurement.Data(),fTextMeasurementEta.Data()));
					PutProcessLabelAndEnergyOnPlot(0.7, 0.785, 0.03, Form("%.1f < #it{p}_{T, #gamma#gamma} < %.1f GeV/#it{c}",mcCompare->GetYaxis()->GetBinUpEdge(lowBin[iB]),mcCompare->GetYaxis()->GetBinUpEdge(upBin[iB])),"","");
					PutProcessLabelAndEnergyOnPlot(0.7, 0.74, 0.03, Form("#gamma's rec. with PCM, %s",calo.Data()), "","");
					canvas->SetLogy(1); canvas->SetLogz(0); canvas->Update();
					canvas->SaveAs(Form("%s/TrackMatching_invMassPi0Eta_withoutTrueMatches_%s_Bins%i-%i.%s", outputDir.Data(), fPrefix.Data(),lowBin[iB],upBin[iB], suffix.Data()));
					canvas->Clear();
				}
				cvs2pads->cd();
				cvs2pads->Update();
				cvs2pads->SaveAs(Form("%s/TrackMatching_invMassPi0Eta_withTrueMatches_%s_Bins%i-%i_%i-%i.%s", outputDir.Data(), fPrefix.Data(),lowBin[nBin-2],upBin[nBin-2],lowBin[nBin-1],upBin[nBin-1], suffix.Data()));
				cvs2pads->Clear();
				delete cvs2pads;
				canvas->cd();
			}

			if(TrueContainer)
			{
				cout << "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;
				cout << "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;
				cout << "Matching efficiencies: "<< endl;
				cout << "nDataMatches: " << nDataMatches << endl;
				cout << "nMCMatches: " << nMCMatches << endl;
				cout << "nTrueMCMatches: " << nTrueMCMatches << endl;
				cout << "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;
				cout << "nData/nMC: " << nDataMatches/nMCMatches*100 << "%" << endl;
				cout << "nData/nTrueMC: " << nDataMatches/nTrueMCMatches*100 << "%" << endl;
				cout << "nMC/nTrueMC: " << (nMCMatches-nMCMatches_TooMany)/nTrueMCMatches*100  << "%, missing matches in MC: " << nMCMatches_Missing
					 << "(" << nMCMatches_Missing/nTrueMCMatches*100 << "%), too many matches in MC: " << nMCMatches_TooMany
					 << "(" << nMCMatches_TooMany/nTrueMCMatches*100 << "%)" << endl;
				cout << "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;
				cout << "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;
				fLog << "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;
				fLog << "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;
				fLog << "Matching efficiencies: "<< endl;
				fLog << "nDataMatches: " << nDataMatches << endl;
				fLog << "nMCMatches: " << nMCMatches << endl;
				fLog << "nTrueMCMatches: " << nTrueMCMatches << endl;
				fLog << "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;
				fLog << "nData/nMC: " << nDataMatches/nMCMatches*100 << "%" << endl;
				fLog << "nData/nTrueMC: " << nDataMatches/nTrueMCMatches*100 << "%" << endl;
				fLog << "nMC/nTrueMC: " << (nMCMatches-nMCMatches_TooMany)/nTrueMCMatches*100  << "%, missing matches in MC: " << nMCMatches_Missing
					 << "(" << nMCMatches_Missing/nTrueMCMatches*100 << "%), too many matches in MC: " << nMCMatches_TooMany
					 << "(" << nMCMatches_TooMany/nTrueMCMatches*100 << "%)" << endl;
				fLog << "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;
				fLog << "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;
			}

            canvas->SetRightMargin(rightMargin);
        }

		TH2D* MotherPi0Conv_Eta_Phi_ESD = (TH2D*) ESDContainer->FindObject("ESD_MotherPi0ConvPhoton_Eta_Phi");
		TH2D* MotherEtaConv_Eta_Phi_ESD = (TH2D*) ESDContainer->FindObject("ESD_MotherEtaConvPhoton_Eta_Phi");

		TBox *boxLabelConv = new TBox(3.15,0.62,3.8,0.9);
		boxLabelConv->SetFillColor(0);

		if(MotherPi0Conv_Eta_Phi_ESD)
		{
			MotherPi0Conv_Eta_Phi = (TH2D*) MotherPi0Conv_Eta_Phi_ESD->Clone();
			canvas->cd();
			canvas->SetRightMargin(0.1);
			DrawAutoGammaHisto2D(MotherPi0Conv_Eta_Phi,
								 " ",
								 "#phi_{#gamma_{conv} under #pi^{0}-peak}",
								 "#eta_{#gamma_{conv} under #pi^{0}-peak}",
								 "",
								 0,0,0,
								 1,0.6,4,
								 1,1);
			boxLabelConv->Draw();
			PutProcessLabelAndEnergyOnPlot(0.7, 0.9, 0.03, fCollisionSystem.Data(), fPlot.Data(), Form("%s clusters", calo.Data()));
			canvas->SetLogy(0); canvas->SetLogz(0); canvas->Update();
			canvas->SaveAs(Form("%s/ConvPhotonPi0_Eta_Phi_%s.%s", outputDir.Data(), fPrefix.Data(), suffix.Data()));
			canvas->Clear();
			canvas->SetRightMargin(rightMargin);
//---------
			MotherPi0Conv_Phi = (TH1D*) MotherPi0Conv_Eta_Phi->ProjectionX("MotherPi0Conv_Phi",1,200);
			if(MotherPi0Conv_Phi){
				DrawAutoGammaHisto(MotherPi0Conv_Phi,
								   " ",
								   "#phi_{#gamma_{conv} under #pi^{0}-peak}",
								   "#frac{d#it{N}}{d#phi}",
								   0,0,0,
								   0,0,0,
								   1,0.8,3.8);
				PutProcessLabelAndEnergyOnPlot(0.8, 0.9, 0.03, fCollisionSystem.Data(), fPlot.Data(), Form("%s clusters", calo.Data()));
				canvas->SetLogy(0); canvas->SetLogz(0); canvas->Update();
				canvas->SaveAs(Form("%s/ConvPhotonPi0_Phi_%s.%s", outputDir.Data(), fPrefix.Data(), suffix.Data()));
				canvas->Clear();
			}
//---------
			MotherPi0Conv_Eta = (TH1D*) MotherPi0Conv_Eta_Phi->ProjectionY("MotherPi0Conv_Eta",1,600);
			if(MotherPi0Conv_Eta){
				DrawAutoGammaHisto(MotherPi0Conv_Eta,
								   " ",
								   "#eta_{#gamma_{conv} under #pi^{0}-peak}",
								   "#frac{d#it{N}}{d#eta}",
								   0,0,0,
								   0,0,0,
								   1,-1,1);
				PutProcessLabelAndEnergyOnPlot(0.8, 0.9, 0.03, fCollisionSystem.Data(), fPlot.Data(), Form("%s clusters", calo.Data()));
				canvas->SetLogy(0); canvas->SetLogz(0); canvas->Update();
				canvas->SaveAs(Form("%s/ConvPhotonPi0_Eta_%s.%s", outputDir.Data(), fPrefix.Data(), suffix.Data()));
				canvas->Clear();
			}
		}
//---------
		TBox *boxLabelConvEta = new TBox(4.71,0.62,5.89,0.9);
		boxLabelConvEta->SetFillColor(0);

		if(MotherEtaConv_Eta_Phi_ESD)
		{
			MotherEtaConv_Eta_Phi = (TH2D*) MotherEtaConv_Eta_Phi_ESD->Clone();
			canvas->cd();
			canvas->SetRightMargin(0.1);
			DrawAutoGammaHisto2D(MotherEtaConv_Eta_Phi,
								 " ",
								 "#phi_{#gamma_{conv} under #eta-peak}",
								 "#eta_{#gamma_{conv} under #eta-peak}",
								 "",
								 0,0,0,
								 0,0,0,
								 1,1);
			boxLabelConvEta->Draw();
			PutProcessLabelAndEnergyOnPlot(0.7, 0.9, 0.03, fCollisionSystem.Data(), fPlot.Data(), Form("%s clusters", calo.Data()));
			canvas->SetLogy(0); canvas->SetLogz(0); canvas->Update();
			canvas->SaveAs(Form("%s/ConvPhotonEta_Eta_Phi_%s.%s", outputDir.Data(), fPrefix.Data(), suffix.Data()));
			canvas->Clear();
			canvas->SetRightMargin(rightMargin);
//---------
			MotherEtaConv_Phi = (TH1D*) MotherEtaConv_Eta_Phi->ProjectionX("MotherEtaConv_Phi",1,200);
			if(MotherEtaConv_Phi){
				DrawAutoGammaHisto(MotherEtaConv_Phi,
								   " ",
								   "#phi_{#gamma_{conv} under #eta-peak}",
								   "#frac{d#it{N}}{d#phi}",
								   0,0,0,
								   0,0,0,
								   0,0,0);
				PutProcessLabelAndEnergyOnPlot(0.8, 0.9, 0.03, fCollisionSystem.Data(), fPlot.Data(), Form("%s clusters", calo.Data()));
				canvas->SetLogy(0); canvas->SetLogz(0); canvas->Update();
				canvas->SaveAs(Form("%s/ConvPhotonEta_Phi_%s.%s", outputDir.Data(), fPrefix.Data(), suffix.Data()));
				canvas->Clear();
			}
//---------
			MotherEtaConv_Eta = (TH1D*) MotherEtaConv_Eta_Phi->ProjectionY("MotherEtaConv_Eta",1,600);
			if(MotherEtaConv_Eta){
				DrawAutoGammaHisto(MotherEtaConv_Eta,
								   " ",
								   "#eta_{#gamma_{conv} under #eta-peak}",
								   "#frac{d#it{N}}{d#eta}",
								   0,0,0,
								   0,0,0,
								   1,-1,1);
				PutProcessLabelAndEnergyOnPlot(0.8, 0.9, 0.03, fCollisionSystem.Data(), fPlot.Data(), Form("%s clusters", calo.Data()));
				canvas->SetLogy(0); canvas->SetLogz(0); canvas->Update();
				canvas->SaveAs(Form("%s/ConvPhotonEta_Eta_%s.%s", outputDir.Data(), fPrefix.Data(), suffix.Data()));
				canvas->Clear();
			}
		}
//---------
        Int_t nESDRebin = 5;
		Int_t iMinPt[5]={0,6,10,20,50};

		if(mode==2||mode==3){
			for(Int_t iMin=0; iMin<5; iMin++)
			{
				TH2D* ESD_InvMass_Pt = (TH2D*) mother->Clone();
				TH2D* ESD_Matched_InvMass_Pt = (TH2D*) motherMatched->Clone();

				TH1D* ESD_InvMass = (TH1D*) ESD_InvMass_Pt->ProjectionX("ESD_InvMass",iMinPt[iMin],ESD_InvMass_Pt->GetXaxis()->GetNbins());
				TH1D* ESD_Matched_InvMass = (TH1D*) ESD_Matched_InvMass_Pt->ProjectionX("ESD_InvMass_Matched",iMinPt[iMin],ESD_Matched_InvMass_Pt->GetXaxis()->GetNbins());
				TH1D* ESD_InvMass_Matched_Sum = (TH1D*) ESD_InvMass->Clone();
				ESD_InvMass->Sumw2();
				ESD_Matched_InvMass->Sumw2();
				ESD_InvMass_Matched_Sum->Sumw2();
				ESD_InvMass_Matched_Sum->Add(ESD_Matched_InvMass,1);

				ESD_InvMass->Rebin(nESDRebin);
				ESD_Matched_InvMass->Rebin(nESDRebin);
				ESD_InvMass_Matched_Sum->Rebin(nESDRebin);
	//---------
				Double_t bin[2] = {1,1E5};
				if(CheckForData8TeV(DataSet)) {bin[1]=1E6;}
				if(CheckForTriggerData8TeV(DataSet)) {bin[1]=1E7;}
				DrawAutoGammaHistMatch3H(ESD_InvMass_Matched_Sum, ESD_InvMass, ESD_Matched_InvMass,
								   " ",
								   "#it{M}_{inv, Mother} (GeV/#it{c}^{2})",
								   "d#it{N}/d#it{M}_{inv}",
								   0,0,0,
								   1,bin[0],bin[1],
								   1,0,0.8,
								   1,1.2,"Sum", "Accepted", "Rejected", kFALSE);
				PutProcessLabelAndEnergyOnPlot(0.13, 0.92, 0.03, fCollisionSystem.Data(), fPlot.Data(), Form("Excluded M_{inv}^{Mother}-candidates by V^{0}-track matching, #it{p}^{Mother}_{T} > %.01f GeV/#it{c}",((Float_t)iMinPt[iMin])/10));
				canvas->SetLogy(1); canvas->SetLogz(0); canvas->Update();
				canvas->SaveAs(Form("%s/TrackMatching_ESD_IntegratedPt_fromPtBin_%i_%s.%s", outputDir.Data(), iMinPt[iMin], fPrefix.Data(),suffix.Data()));
				canvas->Clear();
			}
		}
//---------

    if(TrueContainer)
    {
        Int_t nPi0Rebin = 5;
        Int_t nEtaRebin = 5;

        TH2D* TruePi0_InvMass_Pt = (TH2D*) TrueContainer->FindObject("ESD_TruePi0CaloConvertedPhoton_InvMass_Pt");
        TH2D* TruePi0_InvMass_Pt_matched = (TH2D*) TrueContainer->FindObject("ESD_TruePi0CaloConvertedPhotonMatched_InvMass_Pt");
        TH2D* TrueEta_InvMass_Pt = (TH2D*) TrueContainer->FindObject("ESD_TrueEtaCaloConvertedPhoton_InvMass_Pt");
        TH2D* TrueEta_InvMass_Pt_matched = (TH2D*) TrueContainer->FindObject("ESD_TrueEtaCaloConvertedPhotonMatched_InvMass_Pt");

		TH1D* TruePi0_InvMass = TruePi0_InvMass_Pt->ProjectionX("TruePi0_InvMass",1,300);
		TH1D* TruePi0_InvMass_matched = TruePi0_InvMass_Pt_matched->ProjectionX("TruePi0_InvMass_matched",1,300);
		TH1D* TrueEta_InvMass = TrueEta_InvMass_Pt->ProjectionX("TrueEta_InvMass",1,300);
		TH1D* TrueEta_InvMass_matched = TrueEta_InvMass_Pt_matched->ProjectionX("TrueEta_InvMass_matched",1,300);

        TruePi0_InvMass->Rebin(nPi0Rebin);
        TruePi0_InvMass_matched->Rebin(nPi0Rebin);
        TrueEta_InvMass->Rebin(nEtaRebin);
        TrueEta_InvMass_matched->Rebin(nEtaRebin);

        TruePi0_InvMass->Sumw2();
        TruePi0_InvMass_matched->Sumw2();
        TrueEta_InvMass->Sumw2();
        TrueEta_InvMass_matched->Sumw2();

        TH1D* TruePi0_InvMass_sum = (TH1D*) TruePi0_InvMass->Clone();
        TH1D* TrueEta_InvMass_sum = (TH1D*) TrueEta_InvMass->Clone();

        TruePi0_InvMass_sum->Add(TruePi0_InvMass_matched,1);
        TrueEta_InvMass_sum->Add(TrueEta_InvMass_matched,1);
        TruePi0_InvMass_sum->Sumw2();
        TrueEta_InvMass_sum->Sumw2();
//---------
		DrawAutoGammaHistMatch3H(TruePi0_InvMass_sum, TruePi0_InvMass_matched, TruePi0_InvMass,
                           " ",
						   "#it{M}_{#gamma e^{+/-}} (GeV/#it{c}^{2})",
						   "d#it{N}/d#it{M}_{#gamma e^{+/-}}",
                           0,0,0,
                           0,0,0,
                           1,0,0.8,
						   1,1.2, "Sum", "Rejected", "Accepted");
		PutProcessLabelAndEnergyOnPlot(0.74, 0.78, 0.03, fCollisionSystem.Data(), fPlot.Data(), fTextMeasurement.Data());
		PutProcessLabelAndEnergyOnPlot(0.74, 0.665, 0.03, "#gamma's rec. with PCM and", Form("%s, e^{+/-} leads cluster",calo.Data()), "");
        canvas->SetLogy(0); canvas->SetLogz(0); canvas->Update();
        canvas->SaveAs(Form("%s/TrackMatching_TrueMCPi0_IntegratedPt_%s.%s", outputDir.Data(), fPrefix.Data(),suffix.Data()));
        canvas->Clear();
//---------
		DrawAutoGammaHistMatch3H(TrueEta_InvMass_sum, TrueEta_InvMass_matched, TrueEta_InvMass,
                           " ",
						   "#it{M}_{#gamma e^{+/-}} (GeV/#it{c}^{2})",
						   "d#it{N}/d#it{M}_{#gamma e^{+/-}}",
                           0,0,0,
                           0,0,0,
                           1,0,0.8,
						   1,1.2, "Sum", "Rejected", "Accepted");
		PutProcessLabelAndEnergyOnPlot(0.74, 0.78, 0.03, fCollisionSystem.Data(), fPlot.Data(), fTextMeasurement.Data());
		PutProcessLabelAndEnergyOnPlot(0.74, 0.665, 0.03, "#gamma's rec. with PCM and", Form("%s, e^{+/-} leads cluster",calo.Data()), "");
        canvas->SetLogy(0); canvas->SetLogz(0); canvas->Update();
		canvas->SaveAs(Form("%s/TrackMatching_TrueMCEta_IntegratedPt_%s.%s", outputDir.Data(), fPrefix.Data(),suffix.Data()));
        canvas->Clear();
//---------
        const Int_t nPtExample = 2;
		Int_t ptExampleMin[nPtExample] = {10,40};
		Int_t ptExampleMax[nPtExample] = {12,50};
        for(Int_t iPt=0; iPt<nPtExample; iPt++)
        {
			Double_t ptMin = TruePi0_InvMass_Pt->GetYaxis()->GetBinUpEdge(ptExampleMin[iPt]);
            Double_t ptMax = TruePi0_InvMass_Pt->GetYaxis()->GetBinUpEdge(ptExampleMax[iPt]);

            TH1D* ExampleTruePi0_InvMass = TruePi0_InvMass_Pt->ProjectionX(Form("ExampleTruePi0_InvMass%01i",ptExampleMin[iPt]),ptExampleMin[iPt],ptExampleMax[iPt]);
            TH1D* ExampleTruePi0_InvMass_matched = TruePi0_InvMass_Pt_matched->ProjectionX(Form("ExampleTruePi0_InvMass_matched%01i",ptExampleMin[iPt]),ptExampleMin[iPt],ptExampleMax[iPt]);
            TH1D* ExampleTrueEta_InvMass = TrueEta_InvMass_Pt->ProjectionX(Form("ExampleTrueEta_InvMass%01i",ptExampleMin[iPt]),ptExampleMin[iPt],ptExampleMax[iPt]);
            TH1D* ExampleTrueEta_InvMass_matched = TrueEta_InvMass_Pt_matched->ProjectionX(Form("ExampleTrueEta_InvMass_matched%01i",ptExampleMin[iPt]),ptExampleMin[iPt],ptExampleMax[iPt]);

            ExampleTruePi0_InvMass->Rebin(nPi0Rebin);
            ExampleTruePi0_InvMass_matched->Rebin(nPi0Rebin);
            ExampleTrueEta_InvMass->Rebin(nEtaRebin);
            ExampleTrueEta_InvMass_matched->Rebin(nEtaRebin);

            ExampleTruePi0_InvMass->Sumw2();
            ExampleTruePi0_InvMass_matched->Sumw2();
            ExampleTrueEta_InvMass->Sumw2();
            ExampleTrueEta_InvMass_matched->Sumw2();

            TH1D* ExampleTruePi0_InvMass_sum = (TH1D*) ExampleTruePi0_InvMass->Clone();
            TH1D* ExampleTrueEta_InvMass_sum = (TH1D*) ExampleTrueEta_InvMass->Clone();

            ExampleTruePi0_InvMass_sum->Add(ExampleTruePi0_InvMass_matched,1);
            ExampleTrueEta_InvMass_sum->Add(ExampleTrueEta_InvMass_matched,1);
            ExampleTruePi0_InvMass_sum->Sumw2();
            ExampleTrueEta_InvMass_sum->Sumw2();
//---------
			DrawAutoGammaHistMatch3H(ExampleTruePi0_InvMass_sum, ExampleTruePi0_InvMass_matched, ExampleTruePi0_InvMass,
                               " ",
							   "#it{M}_{#gamma e^{+/-}} (GeV/#it{c}^{2})",
							   "d#it{N}/d#it{M}_{#gamma e^{+/-}}",
                               0,0,0,
                               0,0,0,
                               1,0,0.8,
							   1,1.2, "Sum", "Rejected", "Accepted");
			PutProcessLabelAndEnergyOnPlot(0.74, 0.78, 0.03, fCollisionSystem.Data(), Form("%s, %s",fPlot.Data(),fTextMeasurement.Data()), Form("%.01f < #it{p}_{T} < %.01f GeV/#it{c}",ptMin, ptMax));
			PutProcessLabelAndEnergyOnPlot(0.74, 0.665, 0.03, Form("#gamma's rec. with PCM, %s",calo.Data()), "e^{+/-} leads cluster", "");
            canvas->SetLogy(0); canvas->SetLogz(0); canvas->Update();
            canvas->SaveAs(Form("%s/TrackMatching_TrueMCPi0_PtBins%01i-%01i_%s.%s", outputDir.Data(), ptExampleMin[iPt], ptExampleMax[iPt], fPrefix.Data(),suffix.Data()));
            canvas->Clear();
//---------
			DrawAutoGammaHistMatch3H(ExampleTrueEta_InvMass_sum, ExampleTrueEta_InvMass_matched, ExampleTrueEta_InvMass,
                               " ",
							   "#it{M}_{#gamma e^{+/-}} (GeV/#it{c}^{2})",
							   "d#it{N}/d#it{M}_{#gamma e^{+/-}}",
                               0,0,0,
                               0,0,0,
                               1,0,0.8,
							   1,1.2, "Sum", "Rejected", "Accepted");
			PutProcessLabelAndEnergyOnPlot(0.74, 0.78, 0.03, fCollisionSystem.Data(), Form("%s, %s",fPlot.Data(),fTextMeasurementEta.Data()), Form("%.01f < #it{p}_{T} < %.01f GeV/#it{c}",ptMin, ptMax));
			PutProcessLabelAndEnergyOnPlot(0.74, 0.665, 0.03, Form("#gamma's rec. with PCM, %s",calo.Data()), "e^{+/-} leads cluster", "");
			canvas->SetLogy(0); canvas->SetLogz(0); canvas->Update();
			canvas->SaveAs(Form("%s/TrackMatching_TrueMCEta_PtBins%01i-%01i_%s.%s", outputDir.Data(), ptExampleMin[iPt], ptExampleMax[iPt], fPrefix.Data(),suffix.Data()));
            canvas->Clear();
        }
//---------
        TH2D* TruePi0Photon_InvMass_Pt = (TH2D*) TrueContainer->FindObject("ESD_TruePi0CaloPhoton_InvMass_Pt");
        TH2D* TruePi0Electron_InvMass_Pt = (TH2D*) TrueContainer->FindObject("ESD_TruePi0CaloElectron_InvMass_Pt");
        TH2D* TrueEtaPhoton_InvMass_Pt = (TH2D*) TrueContainer->FindObject("ESD_TrueEtaCaloPhoton_InvMass_Pt");
        TH2D* TrueEtaElectron_InvMass_Pt = (TH2D*) TrueContainer->FindObject("ESD_TrueEtaCaloElectron_InvMass_Pt");

		TH1D* TruePi0CaloPhoton_InvMass = TruePi0Photon_InvMass_Pt->ProjectionX("TruePi0CaloPhoton_InvMass",1,300);
		TH1D* TruePi0CaloElectron_InvMass = TruePi0Electron_InvMass_Pt->ProjectionX("TruePi0CaloElectron_InvMass",1,300);
		TH1D* TrueEtaCaloPhoton_InvMass = TrueEtaPhoton_InvMass_Pt->ProjectionX("TrueEtaCaloPhoton_InvMass",1,300);
		TH1D* TrueEtaCaloElectron_InvMass = TrueEtaElectron_InvMass_Pt->ProjectionX("TrueEtaCaloElectron_InvMass",1,300);

        TruePi0CaloPhoton_InvMass->Rebin(nPi0Rebin);
        TruePi0CaloElectron_InvMass->Rebin(nPi0Rebin);
        TrueEtaCaloPhoton_InvMass->Rebin(nEtaRebin);
        TrueEtaCaloElectron_InvMass->Rebin(nEtaRebin);

        TruePi0CaloPhoton_InvMass->Sumw2();
        TruePi0CaloElectron_InvMass->Sumw2();
        TrueEtaCaloPhoton_InvMass->Sumw2();
        TrueEtaCaloElectron_InvMass->Sumw2();

        TH1D* TruePi0Calo_InvMass_sum = (TH1D*) TruePi0CaloPhoton_InvMass->Clone();
        TH1D* TrueEtaCalo_InvMass_sum = (TH1D*) TrueEtaCaloPhoton_InvMass->Clone();

        TruePi0Calo_InvMass_sum->Add(TruePi0CaloElectron_InvMass,1);
        TrueEtaCalo_InvMass_sum->Add(TrueEtaCaloElectron_InvMass,1);
        TruePi0Calo_InvMass_sum->Sumw2();
        TrueEtaCalo_InvMass_sum->Sumw2();
//---------
		Double_t bin[2] = {0.5,1E4};
		if(CheckForData8TeV(DataSet)) {bin[1]=1E5;}
        DrawAutoGammaHistMatch3H(TruePi0Calo_InvMass_sum, TruePi0CaloPhoton_InvMass, TruePi0CaloElectron_InvMass,
                           " ",
						   "#it{M}_{#gamma#gamma} (GeV/#it{c}^{2})",
						   "d#it{N}/d#it{M}_{#gamma#gamma}",
                           0,0,0,
						   1,bin[0],bin[1],
                           1,0,0.8,
                           1,1.2,"Sum","TrueMC: #gamma_{EMCAL}","TrueMC: e^{+/-}_{EMCAL}");
		PutProcessLabelAndEnergyOnPlot(0.75, 0.72, 0.03, fCollisionSystem.Data(), fPlot.Data(), fTextMeasurement.Data());
		PutProcessLabelAndEnergyOnPlot(0.75, 0.61, 0.03, Form("#gamma's rec. with PCM, %s",calo.Data()), "", "");
        canvas->SetLogy(1); canvas->SetLogz(0); canvas->Update();
        canvas->SaveAs(Form("%s/TrueMCPi0_GammaGamma_GammaElectron_%s.%s", outputDir.Data(), fPrefix.Data(),suffix.Data()));
        canvas->Clear();
//---------
		bin[1]=800;
		if(CheckForData8TeV(DataSet)) {bin[1]=8E3;}
        DrawAutoGammaHistMatch3H(TrueEtaCalo_InvMass_sum, TrueEtaCaloPhoton_InvMass, TrueEtaCaloElectron_InvMass,
                           " ",
						   "#it{M}_{#gamma#gamma}  (GeV/#it{c}^{2})",
						   "d#it{N}/d#it{M}_{#gamma#gamma}",
                           0,0,0,
						   1,bin[0],bin[1],
                           1,0,0.8,
                           1,1.2,"Sum","TrueMC: #gamma_{EMCAL}","TrueMC: e^{+/-}_{EMCAL}");
		PutProcessLabelAndEnergyOnPlot(0.2, 0.9, 0.03, fCollisionSystem.Data(), fPlot.Data(), fTextMeasurementEta.Data());
		PutProcessLabelAndEnergyOnPlot(0.2, 0.79, 0.03, Form("#gamma's rec. with PCM, %s",calo.Data()), "", "");
        canvas->SetLogy(1); canvas->SetLogz(0); canvas->Update();
		canvas->SaveAs(Form("%s/TrueMCEta_GammaGamma_GammaElectron_%s.%s", outputDir.Data(), fPrefix.Data(),suffix.Data()));
        canvas->Clear();
//---------
		bin[1]=2E4;
		if(CheckForData8TeV(DataSet)) {bin[1]=1E5;}
		TruePi0Calo_InvMass_sum->Add(TrueEtaCalo_InvMass_sum,1);
		TruePi0CaloPhoton_InvMass->Add(TrueEtaCaloPhoton_InvMass,1);
		TruePi0CaloElectron_InvMass->Add(TrueEtaCaloElectron_InvMass,1);
		DrawAutoGammaHistMatch3H(TruePi0Calo_InvMass_sum, TruePi0CaloPhoton_InvMass, TruePi0CaloElectron_InvMass,
						   " ",
						   "#it{M}_{#gamma#gamma} (GeV/#it{c}^{2})",
						   "d#it{N}/d#it{M}_{#gamma#gamma}",
						   0,0,0,
						   1,bin[0],bin[1],
						   1,0,0.8,
						   1,1.2,"Sum","TrueMC: #gamma_{EMCAL}","TrueMC: e^{+/-}_{EMCAL}");
		PutProcessLabelAndEnergyOnPlot(0.4, 0.9, 0.03, fCollisionSystem.Data(), fPlot.Data(), Form("%s & %s", fTextMeasurement.Data(), fTextMeasurementEta.Data()));
		PutProcessLabelAndEnergyOnPlot(0.4, 0.79, 0.03, Form("#gamma's rec. with PCM, %s",calo.Data()), "", "");
		canvas->SetLogy(1); canvas->SetLogz(0); canvas->Update();
		canvas->SaveAs(Form("%s/TrueMCPi0Eta_GammaGamma_GammaElectron_%s.%s", outputDir.Data(), fPrefix.Data(),suffix.Data()));
		canvas->Clear();
//---------
    }

	delete canvas;
	delete cvsQuadratic;

    //****************************** Create Output ROOT-File ************************************************

    const char* nameOutput;
    if(isRunNum)
    {
		TString outputRunNum = Form("%s/%s/ClusterQA/%s", fCutSelection[2].Data(),fEnergyFlag.Data(),fPrefixData.Data());
        nameOutput = Form("%s/%s_ClusterQA_%s.root",outputRunNum.Data(),runNumber.Data(),fPrefix.Data());
        gSystem->Exec("mkdir -p "+outputRunNum);
    }
	else {nameOutput = Form("%s/%s/ClusterQA/ClusterQA_%s.root",fCutSelection[2].Data(),fEnergyFlag.Data(),fPrefix.Data());}

    TFile* fOutput = new TFile(nameOutput,"RECREATE");
    cout << "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;
    cout << "Output file: " << nameOutput << endl;
    cout << "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;
	fLog << "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;
	fLog << "Output file: " << nameOutput << endl;
	fLog << "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;

    WriteHistogram(fHistNEvents);
    WriteHistogram(fHistCutIndex);
    WriteHistogram(fHistAcceptanceCuts);
    WriteHistogram(fHistClusterIdentificationCuts);

    WriteHistogram(fHistClusterEtavsPhiBeforeAcc);
    WriteHistogram(fHistClusterEtavsPhiAfterAcc);
    WriteHistogram(fHistClusterEtavsPhiAfterQA);
    WriteHistogram(fHistDistanceToBadChannelBeforeAcc);
    WriteHistogram(fHistDistanceToBadChannelAfterAcc);
    WriteHistogram(fHistClusterTimevsEBeforeQA);
    WriteHistogram(fHistClusterTimevsEAfterQA);
    WriteHistogram(fHistExoticCellBeforeQA);
    WriteHistogram(fHistExoticCellAfterQA);
    WriteHistogram(fHistNMatchedTracks);
    WriteHistogram(fHistEnergyOfClusterBeforeQA);
    WriteHistogram(fHistEnergyOfClusterAfterQA);
    WriteHistogram(fHistNCellsBeforeQA);
    WriteHistogram(fHistNCellsAfterQA);
    WriteHistogram(fHistM02BeforeQA);
    WriteHistogram(fHistM02AfterQA);
    WriteHistogram(fHistM20BeforeQA);
    WriteHistogram(fHistM20AfterQA);
    WriteHistogram(fHistDispersionBeforeQA);
    WriteHistogram(fHistDispersionAfterQA);
    WriteHistogram(fHistNLMBeforeQA);
    WriteHistogram(fHistNLMAfterQA);

    WriteHistogram(fHistClusterRBeforeQA);
    WriteHistogram(fHistClusterRAfterQA);
    WriteHistogram(fHistClusterdEtadPhiBeforeQA);
    WriteHistogram(fHistClusterdEtadPhiAfterQA);
    WriteHistogram(fHistDistanceTrackToClusterBeforeQA);
    WriteHistogram(fHistDistanceTrackToClusterAfterQA);

    WriteHistogram(fHistClusterdEtadPhiPosTracksBeforeQA);
    WriteHistogram(fHistClusterdEtadPhiNegTracksBeforeQA);
    WriteHistogram(fHistClusterdEtadPtBeforeQA);
    WriteHistogram(fHistClusterdPhidPtBeforeQA);
	WriteHistogram(fHistClusterTrueGammaEM02);
	WriteHistogram(fHistClusterTruePi0EM02);
    WriteHistogram(fHistClusterM20M02BeforeQA);
    WriteHistogram(fHistClusterM20M02AfterQA);

	WriteHistogram(fHistClusterCellIDsBeforeQA);
	WriteHistogram(fHistClusterCellIDsAfterQA);
	WriteHistogram(fHistClusterCellEFracBeforeQA);
	WriteHistogram(fHistClusterCellEFracAfterQA);
	WriteHistogram(fHistClusterEM02BeforeQA);
	WriteHistogram(fHistClusterEM02AfterQA);
	WriteHistogram(fHistClusterEnergyVsModule);
	WriteHistogram(fHistClusterEnergyVsNCells);
	WriteHistogram(fHistModuleEnergyVsModule);
	WriteHistogram(fHistNCellsAbove100VsModule);
	WriteHistogram(fHistNCellsAbove1500VsModule);
	WriteHistogram(fHistCellEnergyVsCellID);
	WriteHistogram(fHistCellTimeVsCellID);
	WriteHistogram(fEMCalBadChannels);

	WriteHistogram(fHistClusterTimeBeforeQA);
	WriteHistogram(fHistClusterTimeAfterQA);
    WriteHistogram(fHistClusterdEtaPosTracksBeforeQA);
    WriteHistogram(fHistClusterdPhiPosTracksBeforeQA);
    WriteHistogram(fHistClusterdEtaNegTracksBeforeQA);
    WriteHistogram(fHistClusterdPhiNegTracksBeforeQA);
    WriteHistogram(fHistClusterdEtaBeforeQA);
    WriteHistogram(fHistClusterdPhiBeforeQA);
    WriteHistogram(fHistClusterdEtaAfterQA);
    WriteHistogram(fHistClusterdPhiAfterQA);

    WriteHistogram(fHistClusterdEtadPhiMatchedAfterQA);
    WriteHistogram(fHistClusterdEtaMatchedAfterQA);
    WriteHistogram(fHistClusterdPhiMatchedAfterQA);
    WriteHistogram(fHistDistanceTrackToClusterMatchedAfterQA);
    WriteHistogram(fHistClusterM20M02MatchedAfterQA);

    WriteHistogram(fHistInvMassPtMotherMotherMatched);
	WriteHistogram(fHistInvMassPtMotherMatchedCompare_Matched_True);
	WriteHistogram(fHistInvMassPtMotherMatchedCompare_Matched_MC);
	WriteHistogram(fHistInvMassPtMotherMatchedCompare_True_MC);

	WriteHistogram(MotherPi0Conv_Eta_Phi);
	WriteHistogram(MotherPi0Conv_Eta);
	WriteHistogram(MotherPi0Conv_Phi);
	WriteHistogram(MotherEtaConv_Eta_Phi);
	WriteHistogram(MotherEtaConv_Eta);
	WriteHistogram(MotherEtaConv_Phi);

    fOutput->Write();
    fOutput->Close();

	delete fHistInvMassPtMotherMotherMatched;
    }
  }

//****************************** Obtain Additional Histograms/Plots ************************************************
//****************************************** Comparison ************************************************************

	if(isMCPytFile && isMCPhoFile && isDataFile){
		fLog << "Comparison:" << endl;
        TCanvas* cs = new TCanvas("cs","",200,10,1350,900);  // gives the page size
        DrawGammaCanvasSettings(cs, 0.11, 0.02, 0.04, 0.11);
//        TCanvas* csRatio = new TCanvas("csRatio","",1350,1500);  // gives the page size
		//csRatio->SetTickx(); csRatio->SetTicky(); csRatio->SetGridx(0); csRatio->SetGridy(0);
		//csRatio->SetLeftMargin(0.13); csRatio->SetRightMargin(0.02); csRatio->SetTopMargin(0.02);
		//csRatio->SetFillColor(0);
//---------
		TList* hESDData = (TList*) TopContainerData->FindObject(Form("%s ESD histograms",fCutSelection[2].Data()));
		TList* hESDMCPyt = (TList*) TopContainerMCPyt->FindObject(Form("%s ESD histograms",fCutSelection[0].Data()));
		TList* hESDMCPho = (TList*) TopContainerMCPho->FindObject(Form("%s ESD histograms",fCutSelection[1].Data()));
		Double_t nEventsData = GetNEvents((TH1*)hESDData->FindObject("NEvents"),kFALSE);
		Double_t nEventsMCPyt = GetNEvents((TH1*)hESDMCPyt->FindObject("NEvents"),kFALSE);
		Double_t nEventsMCPho = GetNEvents((TH1*)hESDMCPho->FindObject("NEvents"),kFALSE);
//---------
        Double_t scaleData = 1/nEventsData;
        Double_t scaleMCPyt = 1/nEventsMCPyt;
        Double_t scaleMCPho = 1/nEventsMCPho;
        cout << "ScaleEvents - Data: " << scaleData << ", Pythia: " << scaleMCPyt << ", Phojet: " << scaleMCPho << endl;
		fLog << "ScaleEvents - Data: " << scaleData << ", Pythia: " << scaleMCPyt << ", Phojet: " << scaleMCPho << endl;
//---------
		TH1F* dataVertexZ = (TH1F*) hESDData->FindObject("VertexZ");
		TH1F* mcPytVertexZ = (TH1F*) hESDMCPyt->FindObject("VertexZ");
		TH1F* mcPhoVertexZ = (TH1F*) hESDMCPho->FindObject("VertexZ");

		if(dataVertexZ && mcPytVertexZ && mcPhoVertexZ){
			dataVertexZ->Sumw2();
			mcPytVertexZ->Sumw2();
			mcPhoVertexZ->Sumw2();
			dataVertexZ->Scale(scaleData);
			mcPytVertexZ->Scale(scaleMCPyt);
			mcPhoVertexZ->Scale(scaleMCPho);
			cs->cd();
			DrawAutoGammaCompare3H(mcPytVertexZ, mcPhoVertexZ, dataVertexZ,
								   " ",
								   "Vertex z (cm)",
								   "#frac{1}{N_{Events}} #frac{dN}{dz}",
								   0,0,0,
								   0,1E-3,1E-2,
								   1,-10,10,
								   1,1.3,"Data",fPlotMCPyt.Data(),fPlotMCPho.Data());
			PutProcessLabelAndEnergyOnPlot(0.8, 0.8, 0.03, fCollisionSystem.Data(), Form("%s clusters", calo.Data()), "");
			cs->SetLogy(0); cs->SetLogz(0); cs->Update();
			cs->SaveAs(Form("%s/%s/%s.%s", outputDir.Data(), fComparison.Data(), "Vertex_Z", suffix.Data()));
			cs->Clear();
		}
//---------
		TH2F* fHistDataClusterTimevsE = (TH2F*)CaloCutsContainerData->FindObject(Form("ClusterTimeVsE_afterClusterQA %s", fClusterCutSelection[2].Data()));
		TH2F* fHistMCPytClusterTimevsE = (TH2F*)CaloCutsContainerMCPyt->FindObject(Form("ClusterTimeVsE_afterClusterQA %s", fClusterCutSelection[0].Data()));
		TH2F* fHistMCPhoClusterTimevsE = (TH2F*)CaloCutsContainerMCPho->FindObject(Form("ClusterTimeVsE_afterClusterQA %s", fClusterCutSelection[1].Data()));

		if(fHistDataClusterTimevsE && fHistMCPytClusterTimevsE && fHistMCPhoClusterTimevsE){
			TH1F* dataClusterTime = (TH1F*)fHistDataClusterTimevsE->ProjectionX("dataClusterTimevsE",1,100);
			TH1F* pytClusterTimeTemp = (TH1F*)fHistMCPytClusterTimevsE->ProjectionX("pytClusterTimevsE",1,100);
			TH1F* phoClusterTimeTemp = (TH1F*)fHistMCPhoClusterTimevsE->ProjectionX("phoClusterTimevsE",1,100);

			TH1F* pytClusterTime = (TH1F*) dataClusterTime->Clone("clone_pytClusterTimevsE");
			pytClusterTime->Reset("ICE");
			TH1F* phoClusterTime = (TH1F*) dataClusterTime->Clone("clone_phoClusterTimevsE");
			phoClusterTime->Reset("ICE");
			Double_t meanPyt = pytClusterTimeTemp->GetMean(1);
			Double_t meanPho = phoClusterTimeTemp->GetMean(1);
			for(Int_t iBin=1; iBin<pytClusterTimeTemp->GetXaxis()->GetNbins(); iBin++){
				pytClusterTime->SetBinContent(pytClusterTime->GetXaxis()->FindBin(pytClusterTimeTemp->GetBinCenter(iBin) - meanPyt),pytClusterTimeTemp->GetBinContent(iBin));
				phoClusterTime->SetBinContent(phoClusterTime->GetXaxis()->FindBin(phoClusterTimeTemp->GetBinCenter(iBin) - meanPho),phoClusterTimeTemp->GetBinContent(iBin));
			}

			dataClusterTime->Sumw2();
			pytClusterTime->Sumw2();
			phoClusterTime->Sumw2();

			Double_t nData = dataClusterTime->GetBinContent(dataClusterTime->GetMaximumBin());
			Double_t nMCPyt = pytClusterTime->GetBinContent(pytClusterTime->GetMaximumBin());
			Double_t nMCPho = phoClusterTime->GetBinContent(phoClusterTime->GetMaximumBin());

			dataClusterTime->Scale(1/nData);
			pytClusterTime->Scale(1/nMCPyt);
			phoClusterTime->Scale(1/nMCPho);

			dataClusterTime->GetXaxis()->SetRangeUser(-0.6*1E-7,0.6*1E-7);
			pytClusterTime->GetXaxis()->SetRangeUser(-0.6*1E-7,0.6*1E-7);
			phoClusterTime->GetXaxis()->SetRangeUser(-0.6*1E-7,0.6*1E-7);

			TGaxis::SetExponentOffset(0.5, 0, "x");
			cs->cd();
			DrawAutoGammaCompare3H(pytClusterTime, phoClusterTime, dataClusterTime,
								   " ",
								   "#it{t}_{Cluster} (ns)",
								   "#frac{1}{N_{max}} #frac{dN}{dt}",
								   0,0,0,
								   0,0,0,
								   1,-0.6*1E-7,0.6*1E-7,
								   1,1.3,"Data",fPlotMCPyt.Data(),fPlotMCPho.Data());
			PutProcessLabelAndEnergyOnPlot(0.8, 0.8, 0.03, fCollisionSystem.Data(), Form("%s clusters", calo.Data()), "");
			cs->SetLogy(1); cs->SetLogz(0); cs->Update();
			cs->SaveAs(Form("%s/%s/%s.%s", outputDir.Data(), fComparison.Data(), "ClusterTime", suffix.Data()));
			cs->Clear();
			TGaxis::SetExponentOffset(0, 0, "x");
		}

		TH2F* fHistDataCell = (TH2F*)CaloExtQAContainerData->FindObject(Form("CellEnergyVsCellID %s", fClusterCutSelection[2].Data()));
		TH2F* fHistMCPytCell = (TH2F*)CaloExtQAContainerMCPyt->FindObject(Form("CellEnergyVsCellID %s", fClusterCutSelection[0].Data()));
		TH2F* fHistMCPhoCell = (TH2F*)CaloExtQAContainerMCPho->FindObject(Form("CellEnergyVsCellID %s", fClusterCutSelection[1].Data()));

		if(fHistDataCell && fHistMCPytCell && fHistMCPhoCell){
			cs->SetRightMargin(0.1);
			CheckCellsDataMC(cellQAData,
							 fHistDataCell,
							 fHistMCPytCell,
							 "Compare Cells: Data and Pythia",
							 "CellID",
							 nCaloCells,
							 "Data",
							 fPlotMCPyt.Data());
			PutProcessLabelAndEnergyOnPlot(0.7, 0.9, 0.03, fCollisionSystem.Data(), fPlot.Data(), Form("%s clusters", calo.Data()));
			cs->SetLogx(0); cs->SetLogy(0); cs->SetLogz(0); cs->Update();
			cs->SaveAs(Form("%s/CompareCells_Data_%s.%s", outputDir.Data(), fPrefixMCPyt.Data(), suffix.Data()));
			cs->Clear();

			CheckCellsDataMC(cellQAData,
							 fHistDataCell,
							 fHistMCPhoCell,
							 "Compare Cells: Data and Phojet",
							 "CellID",
							 nCaloCells,
							 "Data",
							 fPlotMCPho.Data());
			PutProcessLabelAndEnergyOnPlot(0.7, 0.9, 0.03, fCollisionSystem.Data(), fPlot.Data(), Form("%s clusters", calo.Data()));
			cs->SetLogx(0); cs->SetLogy(0); cs->SetLogz(0); cs->Update();
			cs->SaveAs(Form("%s/CompareCells_Data_%s.%s", outputDir.Data(), fPrefixMCPho.Data(), suffix.Data()));
			cs->Clear();
			cs->SetRightMargin(0.02);
		}

		TH1F* dataRClusterAfterQA = (TH1F*) CaloCutsContainerData->FindObject(Form("R_Cluster_afterClusterQA %s", fClusterCutSelection[2].Data()));
		TH1F* mcPytRClusterAfterQA = (TH1F*) CaloCutsContainerMCPyt->FindObject(Form("R_Cluster_afterClusterQA %s", fClusterCutSelection[0].Data()));
		TH1F* mcPhoRClusterAfterQA = (TH1F*) CaloCutsContainerMCPho->FindObject(Form("R_Cluster_afterClusterQA %s", fClusterCutSelection[1].Data()));

        if(dataRClusterAfterQA && mcPytRClusterAfterQA && mcPhoRClusterAfterQA){
            dataRClusterAfterQA->Sumw2();
            mcPytRClusterAfterQA->Sumw2();
            mcPhoRClusterAfterQA->Sumw2();

            Double_t nData = dataRClusterAfterQA->GetEntries();
            Double_t nMCPyt = mcPytRClusterAfterQA->GetEntries();
            Double_t nMCPho = mcPhoRClusterAfterQA->GetEntries();

            dataRClusterAfterQA->Scale(1/nData);
            mcPytRClusterAfterQA->Scale(1/nMCPyt);
            mcPhoRClusterAfterQA->Scale(1/nMCPho);
            cs->cd();
            DrawAutoGammaCompare3H(mcPytRClusterAfterQA, mcPhoRClusterAfterQA, dataRClusterAfterQA,
                                   " ",
								   "R_{Cluster} (cm)",
                                   "#frac{1}{N} #frac{dN}{dR}",
                                   0,0,0,
								   0,0,0,
                                   1,435,455,
								   1,1.3,"Data",fPlotMCPyt.Data(),fPlotMCPho.Data());
            PutProcessLabelAndEnergyOnPlot(0.8, 0.8, 0.03, fCollisionSystem.Data(), Form("%s clusters", calo.Data()), "");
            cs->SetLogy(1); cs->SetLogz(0); cs->Update();
			cs->SaveAs(Form("%s/%s/%s.%s", outputDir.Data(), fComparison.Data(), "R_Cluster_afterQA", suffix.Data()));
            cs->Clear();
        }
//---------
		TH1F* dataEnergyOfClusterAfterQA = (TH1F*) CaloCutsContainerData->FindObject(Form("EnergyOfCluster_afterClusterQA %s", fClusterCutSelection[2].Data()));
		TH1F* mcPytEnergyOfClusterAfterQA = (TH1F*) CaloCutsContainerMCPyt->FindObject(Form("EnergyOfCluster_afterClusterQA %s", fClusterCutSelection[0].Data()));
		TH1F* mcPhoEnergyOfClusterAfterQA = (TH1F*) CaloCutsContainerMCPho->FindObject(Form("EnergyOfCluster_afterClusterQA %s", fClusterCutSelection[1].Data()));

        if(dataEnergyOfClusterAfterQA && mcPytEnergyOfClusterAfterQA && mcPhoEnergyOfClusterAfterQA){
//			Int_t binEnergy = 2;
            dataEnergyOfClusterAfterQA->Sumw2();
            mcPytEnergyOfClusterAfterQA->Sumw2();
            mcPhoEnergyOfClusterAfterQA->Sumw2();
			dataEnergyOfClusterAfterQA = (TH1F*) dataEnergyOfClusterAfterQA->Rebin(fNBinsClusterPt, "dataEnergy", fBinsClusterPt);
			mcPytEnergyOfClusterAfterQA = (TH1F*) mcPytEnergyOfClusterAfterQA->Rebin(fNBinsClusterPt, "mcPyt", fBinsClusterPt);
			mcPhoEnergyOfClusterAfterQA = (TH1F*) mcPhoEnergyOfClusterAfterQA->Rebin(fNBinsClusterPt, "mcPho", fBinsClusterPt);
			dataEnergyOfClusterAfterQA->Divide(fDeltaPt);
			mcPytEnergyOfClusterAfterQA->Divide(fDeltaPt);
			mcPhoEnergyOfClusterAfterQA->Divide(fDeltaPt);
//            dataEnergyOfClusterAfterQA->Rebin(binEnergy);
//            mcPytEnergyOfClusterAfterQA->Rebin(binEnergy);
//            mcPhoEnergyOfClusterAfterQA->Rebin(binEnergy);
            dataEnergyOfClusterAfterQA->Scale(scaleData);
            mcPytEnergyOfClusterAfterQA->Scale(scaleMCPyt);
            mcPhoEnergyOfClusterAfterQA->Scale(scaleMCPho);
            cs->cd();
            DrawAutoGammaCompare3H(mcPytEnergyOfClusterAfterQA, mcPhoEnergyOfClusterAfterQA, dataEnergyOfClusterAfterQA,
                               " ",
							   "Cluster Energy (GeV)",
                               "#frac{1}{N_{Events}} #frac{dN}{dE}",
                               0,0,0,
							   0,0,0,
							   1,0,30,
							   1,1.3,"Data",fPlotMCPyt.Data(),fPlotMCPho.Data());
            PutProcessLabelAndEnergyOnPlot(0.8, 0.8, 0.03, fCollisionSystem.Data(), Form("%s clusters", calo.Data()), "");
            //((TAttAxis*) dataEnergyOfClusterAfterQA->GetYaxis())->SetTitleOffset(1);
            cs->SetLogy(1); cs->SetLogz(0); cs->Update();
			cs->SaveAs(Form("%s/%s/%s.%s", outputDir.Data(), fComparison.Data(), "Energy_Cluster_afterQA", suffix.Data()));
            cs->Clear();
        }
//---------
		TH1F* dataM02AfterQA = (TH1F*) CaloCutsContainerData->FindObject(Form("M02_afterClusterQA %s", fClusterCutSelection[2].Data()));
		TH1F* mcPytM02AfterQA = (TH1F*) CaloCutsContainerMCPyt->FindObject(Form("M02_afterClusterQA %s", fClusterCutSelection[0].Data()));
		TH1F* mcPhoM02AfterQA = (TH1F*) CaloCutsContainerMCPho->FindObject(Form("M02_afterClusterQA %s", fClusterCutSelection[1].Data()));

        if(dataM02AfterQA && mcPytM02AfterQA && mcPhoM02AfterQA){
            dataM02AfterQA->Sumw2();
            mcPytM02AfterQA->Sumw2();
            mcPhoM02AfterQA->Sumw2();
            dataM02AfterQA->Scale(scaleData);
            mcPytM02AfterQA->Scale(scaleMCPyt);
            mcPhoM02AfterQA->Scale(scaleMCPho);
            cs->cd();
            DrawAutoGammaCompare3H(mcPytM02AfterQA, mcPhoM02AfterQA, dataM02AfterQA,
                               " ",
							   "#lambda_{0}^{2}",
							   "#frac{1}{N_{Events}} #frac{dN}{d#lambda_{0}^{2}}",
                               0,0,0,
							   0,0,0,
							   1,0.05,0.55,
							   1,1.3,"Data",fPlotMCPyt.Data(),fPlotMCPho.Data());
            PutProcessLabelAndEnergyOnPlot(0.8, 0.8, 0.03, fCollisionSystem.Data(), Form("%s clusters", calo.Data()), "");
            cs->SetLogy(1); cs->SetLogz(0); cs->Update();
			cs->SaveAs(Form("%s/%s/%s.%s", outputDir.Data(), fComparison.Data(), "M02_afterQA", suffix.Data()));
            cs->Clear();
        }
//---------
		TH1F* dataM20AfterQA = (TH1F*) CaloCutsContainerData->FindObject(Form("M20_afterClusterQA %s", fClusterCutSelection[2].Data()));
		TH1F* mcPytM20AfterQA = (TH1F*) CaloCutsContainerMCPyt->FindObject(Form("M20_afterClusterQA %s", fClusterCutSelection[0].Data()));
		TH1F* mcPhoM20AfterQA = (TH1F*) CaloCutsContainerMCPho->FindObject(Form("M20_afterClusterQA %s", fClusterCutSelection[1].Data()));

        if(dataM20AfterQA && mcPytM20AfterQA && mcPhoM20AfterQA){
            dataM20AfterQA->Sumw2();
            mcPytM20AfterQA->Sumw2();
            mcPhoM20AfterQA->Sumw2();
            dataM20AfterQA->Scale(scaleData);
            mcPytM20AfterQA->Scale(scaleMCPyt);
            mcPhoM20AfterQA->Scale(scaleMCPho);
            cs->cd();
            DrawAutoGammaCompare3H(mcPytM20AfterQA, mcPhoM20AfterQA, dataM20AfterQA,
                               " ",
                               "M20",
                               "#frac{1}{N_{Events}} #frac{dN}{dM20}",
                               0,0,0,
							   0,0,0,
							   1,0,0.55,
							   1,1.3,"Data",fPlotMCPyt.Data(),fPlotMCPho.Data());
            PutProcessLabelAndEnergyOnPlot(0.8, 0.8, 0.03, fCollisionSystem.Data(), Form("%s clusters", calo.Data()), "");
            cs->SetLogy(1); cs->SetLogz(0); cs->Update();
			cs->SaveAs(Form("%s/%s/%s.%s", outputDir.Data(), fComparison.Data(), "M20_afterQA", suffix.Data()));
            cs->Clear();
        }
//---------
		TH1F* dataDispersionAfterQA = (TH1F*) CaloCutsContainerData->FindObject(Form("Dispersion_afterClusterQA %s", fClusterCutSelection[2].Data()));
		TH1F* mcPytDispersionAfterQA = (TH1F*) CaloCutsContainerMCPyt->FindObject(Form("Dispersion_afterClusterQA %s", fClusterCutSelection[0].Data()));
		TH1F* mcPhoDispersionAfterQA = (TH1F*) CaloCutsContainerMCPho->FindObject(Form("Dispersion_afterClusterQA %s", fClusterCutSelection[1].Data()));

        if(dataDispersionAfterQA && mcPytDispersionAfterQA && mcPhoDispersionAfterQA){
            dataDispersionAfterQA->Sumw2();
            mcPytDispersionAfterQA->Sumw2();
            mcPhoDispersionAfterQA->Sumw2();
            dataDispersionAfterQA->Scale(scaleData);
            mcPytDispersionAfterQA->Scale(scaleMCPyt);
            mcPhoDispersionAfterQA->Scale(scaleMCPho);
            cs->cd();
            DrawAutoGammaCompare3H(mcPytDispersionAfterQA, mcPhoDispersionAfterQA, dataDispersionAfterQA,
                                " ",
                                "Dispersion",
                                "#frac{1}{N_{Events}} #frac{dN}{dDisp}",
                                0,0,0,
								0,0,0,
								1,0.2,1.1,
								1,1.3,"Data",fPlotMCPyt.Data(),fPlotMCPho.Data());
            PutProcessLabelAndEnergyOnPlot(0.8, 0.8, 0.03, fCollisionSystem.Data(), Form("%s clusters", calo.Data()), "");
            cs->SetLogy(1); cs->SetLogz(0); cs->Update();
			cs->SaveAs(Form("%s/%s/%s.%s", outputDir.Data(), fComparison.Data(), "Dispersion_afterQA", suffix.Data()));
            cs->Clear();
        }
//---------
	  TH1F* dataNCellsAfterQA = (TH1F*) CaloCutsContainerData->FindObject(Form("NCellPerCluster_afterClusterQA %s", fClusterCutSelection[2].Data()));
	  TH1F* mcPytNCellsAfterQA = (TH1F*) CaloCutsContainerMCPyt->FindObject(Form("NCellPerCluster_afterClusterQA %s", fClusterCutSelection[0].Data()));
	  TH1F* mcPhoNCellsAfterQA = (TH1F*) CaloCutsContainerMCPho->FindObject(Form("NCellPerCluster_afterClusterQA %s", fClusterCutSelection[1].Data()));

      if(dataNCellsAfterQA && mcPytNCellsAfterQA && mcPhoNCellsAfterQA){
          dataNCellsAfterQA->Sumw2();
          mcPytNCellsAfterQA->Sumw2();
          mcPhoNCellsAfterQA->Sumw2();
          dataNCellsAfterQA->Scale(scaleData);
          mcPytNCellsAfterQA->Scale(scaleMCPyt);
          mcPhoNCellsAfterQA->Scale(scaleMCPho);
          cs->cd();
          DrawAutoGammaCompare3H(mcPytNCellsAfterQA, mcPhoNCellsAfterQA, dataNCellsAfterQA,
                              " ",
                              "N_{Cells} per Cluster",
                              "#frac{1}{N_{Events}} #frac{dN}{dN_{Cells}}",
                              0,0,0,
							  0,0,0,
							  1,1,30,
							  1,1.3,"Data",fPlotMCPyt.Data(),fPlotMCPho.Data());
          PutProcessLabelAndEnergyOnPlot(0.8, 0.8, 0.03, fCollisionSystem.Data(), Form("%s clusters", calo.Data()), "");
          cs->SetLogy(1); cs->SetLogz(0); cs->Update();
		  cs->SaveAs(Form("%s/%s/%s.%s", outputDir.Data(), fComparison.Data(), "NCells_afterQA", suffix.Data()));
          cs->Clear();
      }
//---------
	  TH2F* dataEtaPhiB = (TH2F*)CaloCutsContainerData->FindObject(Form("dEtaVsdPhi_beforeClusterQA %s", fClusterCutSelection[2].Data()));
	  TH2F* dataEtaPhiA = (TH2F*)CaloCutsContainerData->FindObject(Form("dEtaVsdPhi_afterClusterQA %s", fClusterCutSelection[2].Data()));
	  TH2F* mcPytEtaPhiB = (TH2F*)CaloCutsContainerMCPyt->FindObject(Form("dEtaVsdPhi_beforeClusterQA %s", fClusterCutSelection[0].Data()));
	  TH2F* mcPytEtaPhiA = (TH2F*)CaloCutsContainerMCPyt->FindObject(Form("dEtaVsdPhi_afterClusterQA %s", fClusterCutSelection[0].Data()));
	  TH2F* mcPhoEtaPhiB = (TH2F*)CaloCutsContainerMCPho->FindObject(Form("dEtaVsdPhi_beforeClusterQA %s", fClusterCutSelection[1].Data()));
	  TH2F* mcPhoEtaPhiA = (TH2F*)CaloCutsContainerMCPho->FindObject(Form("dEtaVsdPhi_afterClusterQA %s", fClusterCutSelection[1].Data()));

      if(dataEtaPhiA && dataEtaPhiB && mcPytEtaPhiA && mcPytEtaPhiB && mcPhoEtaPhiA && mcPhoEtaPhiB){
          TH2F* dataEtaPhiMatched = (TH2F*) dataEtaPhiB->Clone();
          TH2F* mcPytEtaPhiMatched = (TH2F*) mcPytEtaPhiB->Clone();
          TH2F* mcPhoEtaPhiMatched = (TH2F*) mcPhoEtaPhiB->Clone();
          dataEtaPhiMatched->Add(dataEtaPhiA,-1);
          mcPytEtaPhiMatched->Add(mcPytEtaPhiA,-1);
          mcPhoEtaPhiMatched->Add(mcPhoEtaPhiA,-1);

		  TH1F* dataEta = (TH1F*)dataEtaPhiMatched->ProjectionX("dataEta",1,300);
		  TH1F* pytEta = (TH1F*)mcPytEtaPhiMatched->ProjectionX("pytEta",1,300);
		  TH1F* phoEta = (TH1F*)mcPhoEtaPhiMatched->ProjectionX("phoEta",1,300);

          Int_t binEta = 1;
          dataEta->Rebin(binEta);
          pytEta->Rebin(binEta);
          phoEta->Rebin(binEta);

          dataEta->Sumw2();
          pytEta->Sumw2();
          phoEta->Sumw2();
          Double_t nData = dataEta->GetEntries();
          Double_t nMCPyt = pytEta->GetEntries();
          Double_t nMCPho = phoEta->GetEntries();

          dataEta->Scale(1/nData);
          pytEta->Scale(1/nMCPyt);
          phoEta->Scale(1/nMCPho);

          TGaxis::SetExponentOffset(-0.06, 0.01, "x");
          cs->cd();
          DrawAutoGammaCompare3H(pytEta, phoEta, dataEta,
                         " ",
                         "#Delta#eta",
                         "#frac{1}{N} #frac{dN}{d#Delta#eta}",
                         0,0,0,
						 0,0,0,
						 1,-0.02,0.02,
						 1,1.3,"Data",fPlotMCPyt.Data(),fPlotMCPho.Data());
          PutProcessLabelAndEnergyOnPlot(0.8, 0.8, 0.03, fCollisionSystem.Data(), Form("%s clusters", calo.Data()), "");
          cs->SetLogy(1); cs->SetLogz(0); cs->Update();
		  cs->SaveAs(Form("%s/%s/%s.%s", outputDir.Data(), fComparison.Data(), "DeltaEta", suffix.Data()));
          cs->Clear();
          TGaxis::SetExponentOffset(0, 0, "x");
      }
//---------
      if(dataEtaPhiA && dataEtaPhiB && mcPytEtaPhiA && mcPytEtaPhiB && mcPhoEtaPhiA && mcPhoEtaPhiB){
          TH2F* dataEtaPhiMatched2 = (TH2F*) dataEtaPhiB->Clone();
          TH2F* mcPytEtaPhiMatched2 = (TH2F*) mcPytEtaPhiB->Clone();
          TH2F* mcPhoEtaPhiMatched2 = (TH2F*) mcPhoEtaPhiB->Clone();
          dataEtaPhiMatched2->Add(dataEtaPhiA,-1);
          mcPytEtaPhiMatched2->Add(mcPytEtaPhiA,-1);
          mcPhoEtaPhiMatched2->Add(mcPhoEtaPhiA,-1);

		  TH1F* dataPhi = (TH1F*)dataEtaPhiMatched2->ProjectionY("dataPhi",1,300);
		  TH1F* pytPhi = (TH1F*)mcPytEtaPhiMatched2->ProjectionY("pytPhi",1,300);
		  TH1F* phoPhi = (TH1F*)mcPhoEtaPhiMatched2->ProjectionY("phoPhi",1,300);

          Int_t binPhi = 1;
          dataPhi->Rebin(binPhi);
          pytPhi->Rebin(binPhi);
          phoPhi->Rebin(binPhi);

          dataPhi->Sumw2();
          pytPhi->Sumw2();
          phoPhi->Sumw2();
          Double_t nData = dataPhi->GetEntries();
          Double_t nMCPyt = pytPhi->GetEntries();
          Double_t nMCPho = phoPhi->GetEntries();

          dataPhi->Scale(1/nData);
          pytPhi->Scale(1/nMCPyt);
          phoPhi->Scale(1/nMCPho);

          TGaxis::SetExponentOffset(-0.06, 0.01, "x");
          cs->cd();
          DrawAutoGammaCompare3H(pytPhi, phoPhi, dataPhi,
                         " ",
                         "#Delta#phi",
                         "#frac{1}{N} #frac{dN}{d#Delta#phi}",
                         0,0,0,
						 0,0,0,
						 1,-0.1,0.1,
						 1,1.3,"Data",fPlotMCPyt.Data(),fPlotMCPho.Data());
          PutProcessLabelAndEnergyOnPlot(0.8, 0.8, 0.03, fCollisionSystem.Data(), Form("%s clusters", calo.Data()), "");
          cs->SetLogy(1); cs->SetLogz(0); cs->Update();
		  cs->SaveAs(Form("%s/%s/%s.%s", outputDir.Data(), fComparison.Data(), "DeltaPhi", suffix.Data()));
          cs->Clear();
          TGaxis::SetExponentOffset(0, 0, "x");
      }
//---------
	  TH2F* dataEtaPhi = (TH2F*) dataEtaPhiB->Clone();
	  TH2F* mcPytEtaPhi = (TH2F*) mcPytEtaPhiB->Clone();
	  TH2F* mcPhoEtaPhi = (TH2F*) mcPhoEtaPhiB->Clone();

	  if(dataEtaPhiB && mcPytEtaPhiB && mcPhoEtaPhiB){
		  TH1F* dataEta = (TH1F*)dataEtaPhi->ProjectionX("dataEtaB",1,300);
		  TH1F* pytEta = (TH1F*)mcPytEtaPhi->ProjectionX("pytEtaB",1,300);
		  TH1F* phoEta = (TH1F*)mcPhoEtaPhi->ProjectionX("phoEtaB",1,300);

		  dataEta->Sumw2();
		  pytEta->Sumw2();
		  phoEta->Sumw2();
		  Double_t nData = dataEta->GetEntries();
		  Double_t nMCPyt = pytEta->GetEntries();
		  Double_t nMCPho = phoEta->GetEntries();

		  dataEta->Scale(1/nData);
		  pytEta->Scale(1/nMCPyt);
		  phoEta->Scale(1/nMCPho);

		  TGaxis::SetExponentOffset(-0.06, 0.01, "x");
		  cs->cd();
		  DrawAutoGammaCompare3H(pytEta, phoEta, dataEta,
						 " ",
						 "#Delta#eta",
						 "#frac{1}{N} #frac{dN}{d#Delta#eta}",
						 0,0,0,
						 0,0,0,
						 1,-0.3,0.3,
						 1,1.3,"Data",fPlotMCPyt.Data(),fPlotMCPho.Data());
		  PutProcessLabelAndEnergyOnPlot(0.8, 0.8, 0.03, fCollisionSystem.Data(), Form("%s clusters", calo.Data()), "");
		  cs->SetLogy(1); cs->SetLogz(0); cs->Update();
		  cs->SaveAs(Form("%s/%s/%s.%s", outputDir.Data(), fComparison.Data(), "DeltaEta_allTracks", suffix.Data()));
		  cs->Clear();
		  TGaxis::SetExponentOffset(0, 0, "x");
	  }
//---------
	  if(dataEtaPhiB && mcPytEtaPhiB && mcPhoEtaPhiB){
		  TH1F* dataPhi = (TH1F*)dataEtaPhi->ProjectionY("dataPhiB",1,300);
		  TH1F* pytPhi = (TH1F*)mcPytEtaPhi->ProjectionY("pytPhiB",1,300);
		  TH1F* phoPhi = (TH1F*)mcPhoEtaPhi->ProjectionY("phoPhiB",1,300);

		  dataPhi->Sumw2();
		  pytPhi->Sumw2();
		  phoPhi->Sumw2();
		  Double_t nData = dataPhi->GetEntries();
		  Double_t nMCPyt = pytPhi->GetEntries();
		  Double_t nMCPho = phoPhi->GetEntries();

		  dataPhi->Scale(1/nData);
		  pytPhi->Scale(1/nMCPyt);
		  phoPhi->Scale(1/nMCPho);

		  phoPhi->GetXaxis()->SetRangeUser(-0.3,0.3);
		  dataPhi->GetXaxis()->SetRangeUser(-0.3,0.3);

		  cs->cd();
		  DrawAutoGammaCompare3H(pytPhi, phoPhi, dataPhi,
						 " ",
						 "#Delta#phi",
						 "#frac{1}{N} #frac{dN}{d#Delta#phi}",
						 0,0,0,
						 0,0,0,
						 1,-0.3,0.3,
						 1,1.3,"Data",fPlotMCPyt.Data(),fPlotMCPho.Data());
		  PutProcessLabelAndEnergyOnPlot(0.8, 0.8, 0.03, fCollisionSystem.Data(), Form("%s clusters", calo.Data()), "");
		  cs->SetLogy(1); cs->SetLogz(0); cs->Update();
		  cs->SaveAs(Form("%s/%s/%s.%s", outputDir.Data(), fComparison.Data(), "DeltaPhi_allTracks", suffix.Data()));
		  cs->Clear();
	  }
//---------
	  TString charge[2]={"pos","neg"};
	  TString pTinterval[3]={"P<0.75","0.75<P<1.25","P>1.25"};
	  for(Int_t iC=0; iC<2; iC++)
	  {
		  for(Int_t iPt=0; iPt<3; iPt++)
		  {
			  TH2F* dataEtaPhi0B = (TH2F*)CaloCutsContainerData->FindObject(Form("dEtaVsdPhi_%sTracks_%s_beforeClusterQA %s", charge[iC].Data(), pTinterval[iPt].Data(), fClusterCutSelection[2].Data()));
			  if(!dataEtaPhi0B) dataEtaPhi0B = (TH2F*)CaloCutsContainerData->FindObject(Form("dEtaVsdPhi_%sTrack_%s_beforeClusterQA %s", charge[iC].Data(), pTinterval[iPt].Data(), fClusterCutSelection[2].Data()));
			  TH2F* mcPytEtaPhi0B = (TH2F*)CaloCutsContainerMCPyt->FindObject(Form("dEtaVsdPhi_%sTracks_%s_beforeClusterQA %s", charge[iC].Data(), pTinterval[iPt].Data(), fClusterCutSelection[0].Data()));
			  if(!mcPytEtaPhi0B) mcPytEtaPhi0B = (TH2F*)CaloCutsContainerMCPyt->FindObject(Form("dEtaVsdPhi_%sTrack_%s_beforeClusterQA %s", charge[iC].Data(), pTinterval[iPt].Data(), fClusterCutSelection[0].Data()));
			  TH2F* mcPhoEtaPhi0B = (TH2F*)CaloCutsContainerMCPho->FindObject(Form("dEtaVsdPhi_%sTracks_%s_beforeClusterQA %s", charge[iC].Data(), pTinterval[iPt].Data(), fClusterCutSelection[1].Data()));
			  if(!mcPhoEtaPhi0B) mcPhoEtaPhi0B = (TH2F*)CaloCutsContainerMCPho->FindObject(Form("dEtaVsdPhi_%sTrack_%s_beforeClusterQA %s", charge[iC].Data(), pTinterval[iPt].Data(), fClusterCutSelection[1].Data()));

			  if(dataEtaPhi0B && mcPytEtaPhi0B && mcPhoEtaPhi0B){
				  TH1F* dataEta0B = (TH1F*)dataEtaPhi0B->ProjectionX(Form("dataEta%s0B_%i",charge[iC].Data(),iPt),1,300);
				  TH1F* pytEta0B = (TH1F*)mcPytEtaPhi0B->ProjectionX(Form("pytEta%s0B_%i",charge[iC].Data(),iPt),1,300);
				  TH1F* phoEta0B = (TH1F*)mcPhoEtaPhi0B->ProjectionX(Form("phoEta%s0B_%i",charge[iC].Data(),iPt),1,300);

				  dataEta0B->GetXaxis()->SetRangeUser(-0.3,0.3);
				  pytEta0B->GetXaxis()->SetRangeUser(-0.3,0.3);
				  phoEta0B->GetXaxis()->SetRangeUser(-0.3,0.3);

				  dataEta0B->Sumw2();
				  pytEta0B->Sumw2();
				  phoEta0B->Sumw2();

				  Double_t nData0B = dataEta0B->GetEntries();
				  Double_t nMCPyt0B = pytEta0B->GetEntries();
				  Double_t nMCPho0B = phoEta0B->GetEntries();

				  dataEta0B->Scale(1/nData0B);
				  pytEta0B->Scale(1/nMCPyt0B);
				  phoEta0B->Scale(1/nMCPho0B);

				  TGaxis::SetExponentOffset(-0.06, 0.01, "x");
				  cs->cd();
				  DrawAutoGammaCompare3H(pytEta0B, phoEta0B, dataEta0B,
										 " ",
										 "#Delta#eta",
										 "#frac{1}{N} #frac{dN}{d#Delta#eta}",
										 0,0,0,
										 0,0,0,
										 1,-0.3,0.3,
										 1,1.3,"Data",fPlotMCPyt.Data(),fPlotMCPho.Data());
				  PutProcessLabelAndEnergyOnPlot(0.8, 0.8, 0.03, fCollisionSystem.Data(), Form("%s clusters", calo.Data()), "");
				  cs->SetLogy(1); cs->SetLogz(0); cs->Update();
				  cs->SaveAs(Form("%s/%s/%s_%s_%i.%s", outputDir.Data(), fComparison.Data(), "DeltaEta", charge[iC].Data(), iPt, suffix.Data()));
				  cs->Clear();
				  TGaxis::SetExponentOffset(0, 0, "x");
			  }
	//---------
			  if(dataEtaPhi0B && mcPytEtaPhi0B && mcPhoEtaPhi0B){
				  TH1F* dataPhi0B = (TH1F*)dataEtaPhi0B->ProjectionY(Form("dataPhi%s0B_%i",charge[iC].Data(),iPt),1,300);
				  TH1F* pytPhi0B = (TH1F*)mcPytEtaPhi0B->ProjectionY(Form("pytPhi%s0B_%i",charge[iC].Data(),iPt),1,300);
				  TH1F* phoPhi0B = (TH1F*)mcPhoEtaPhi0B->ProjectionY(Form("phoPhi%s0B_%i",charge[iC].Data(),iPt),1,300);

				  dataPhi0B->GetXaxis()->SetRangeUser(-0.3,0.3);
				  pytPhi0B->GetXaxis()->SetRangeUser(-0.3,0.3);
				  phoPhi0B->GetXaxis()->SetRangeUser(-0.3,0.3);

				  dataPhi0B->Sumw2();
				  pytPhi0B->Sumw2();
				  phoPhi0B->Sumw2();

				  Double_t nData0B = dataPhi0B->GetEntries();
				  Double_t nMCPyt0B = pytPhi0B->GetEntries();
				  Double_t nMCPho0B = phoPhi0B->GetEntries();

				  dataPhi0B->Scale(1/nData0B);
				  pytPhi0B->Scale(1/nMCPyt0B);
				  phoPhi0B->Scale(1/nMCPho0B);

				  TGaxis::SetExponentOffset(-0.06, 0.01, "x");
				  cs->cd();
				  DrawAutoGammaCompare3H(pytPhi0B, phoPhi0B, dataPhi0B,
										 " ",
										 "#Delta#phi",
										 "#frac{1}{N} #frac{dN}{d#Delta#phi}",
										 0,0,0,
										 0,0,0,
										 1,-0.3,0.3,
										 1,1.3,"Data",fPlotMCPyt.Data(),fPlotMCPho.Data());
				  PutProcessLabelAndEnergyOnPlot(0.8, 0.8, 0.03, fCollisionSystem.Data(), Form("%s clusters", calo.Data()), "");
				  cs->SetLogy(1); cs->SetLogz(0); cs->Update();
				  cs->SaveAs(Form("%s/%s/%s_%s_%i.%s", outputDir.Data(), fComparison.Data(), "DeltaPhi", charge[iC].Data(), iPt, suffix.Data()));
				  cs->Clear();
				  TGaxis::SetExponentOffset(0, 0, "x");
			  }
		  }
//---------
		  TH2F* dataEtaPhiChargeB = (TH2F*)CaloCutsContainerData->FindObject(Form("dEtaVsdPhi_%sTracks_beforeClusterQA %s", charge[iC].Data(),fClusterCutSelection[2].Data()));
		  TH2F* dataEtaPhiChargeA = (TH2F*)CaloCutsContainerData->FindObject(Form("dEtaVsdPhi_%sTracks_afterClusterQA %s", charge[iC].Data(),fClusterCutSelection[2].Data()));
		  TH2F* mcPytEtaPhiChargeB = (TH2F*)CaloCutsContainerMCPyt->FindObject(Form("dEtaVsdPhi_%sTracks_beforeClusterQA %s", charge[iC].Data(),fClusterCutSelection[0].Data()));
		  TH2F* mcPytEtaPhiChargeA = (TH2F*)CaloCutsContainerMCPyt->FindObject(Form("dEtaVsdPhi_%sTracks_afterClusterQA %s", charge[iC].Data(),fClusterCutSelection[0].Data()));
		  TH2F* mcPhoEtaPhiChargeB = (TH2F*)CaloCutsContainerMCPho->FindObject(Form("dEtaVsdPhi_%sTracks_beforeClusterQA %s", charge[iC].Data(),fClusterCutSelection[1].Data()));
		  TH2F* mcPhoEtaPhiChargeA = (TH2F*)CaloCutsContainerMCPho->FindObject(Form("dEtaVsdPhi_%sTracks_afterClusterQA %s", charge[iC].Data(),fClusterCutSelection[1].Data()));

		  if(dataEtaPhiChargeB && mcPytEtaPhiChargeB && mcPhoEtaPhiChargeB){
			  TH2F* dataEta = (TH2F*) dataEtaPhiChargeB->Clone("dEta");
			  TH2F* mcPytEta = (TH2F*) mcPytEtaPhiChargeB->Clone("pyEta");
			  TH2F* mcPhoEta = (TH2F*) mcPhoEtaPhiChargeB->Clone("phoEta");

			  dataEta->Add(dataEtaPhiChargeA,-1);
			  mcPytEta->Add(mcPytEtaPhiChargeA,-1);
			  mcPhoEta->Add(mcPhoEtaPhiChargeA,-1);

			  TH1F* dataEta0B = (TH1F*)dataEta->ProjectionX(Form("dataEtaCharge%s0B",charge[iC].Data()),1,300);
			  TH1F* pytEta0B = (TH1F*)mcPytEta->ProjectionX(Form("pytEtaCharge%s0B",charge[iC].Data()),1,300);
			  TH1F* phoEta0B = (TH1F*)mcPhoEta->ProjectionX(Form("phoEtaCharge%s0B",charge[iC].Data()),1,300);

			  dataEta0B->GetXaxis()->SetRangeUser(-0.02,0.02);
			  pytEta0B->GetXaxis()->SetRangeUser(-0.02,0.02);
			  phoEta0B->GetXaxis()->SetRangeUser(-0.02,0.02);

			  dataEta0B->Sumw2();
			  pytEta0B->Sumw2();
			  phoEta0B->Sumw2();

			  Double_t nData0B = dataEta0B->GetEntries();
			  Double_t nMCPyt0B = pytEta0B->GetEntries();
			  Double_t nMCPho0B = phoEta0B->GetEntries();

			  dataEta0B->Scale(1/nData0B);
			  pytEta0B->Scale(1/nMCPyt0B);
			  phoEta0B->Scale(1/nMCPho0B);

			  TGaxis::SetExponentOffset(-0.06, 0.01, "x");
			  cs->cd();
			  DrawAutoGammaCompare3H(pytEta0B, phoEta0B, dataEta0B,
									 " ",
									 "#Delta#eta",
									 "#frac{1}{N} #frac{dN}{d#Delta#eta}",
									 0,0,0,
									 0,0,0,
									 1,-0.02,0.02,
									 1,1.3,"Data",fPlotMCPyt.Data(),fPlotMCPho.Data());
			  PutProcessLabelAndEnergyOnPlot(0.8, 0.8, 0.03, fCollisionSystem.Data(), Form("%s clusters", calo.Data()), "");
			  cs->SetLogy(1); cs->SetLogz(0); cs->Update();
			  cs->SaveAs(Form("%s/%s/%s_%s.%s", outputDir.Data(), fComparison.Data(), "DeltaEta", charge[iC].Data(), suffix.Data()));
			  cs->Clear();
			  TGaxis::SetExponentOffset(0, 0, "x");
		  }
//---------
		  if(dataEtaPhiChargeB && mcPytEtaPhiChargeB && mcPhoEtaPhiChargeB){
			  TH2F* dataPhi = (TH2F*) dataEtaPhiChargeB->Clone("dphi");
			  TH2F* mcPytPhi = (TH2F*) mcPytEtaPhiChargeB->Clone("pyphi");
			  TH2F* mcPhoPhi = (TH2F*) mcPhoEtaPhiChargeB->Clone("phophi");

			  dataPhi->Add(dataEtaPhiChargeA,-1);
			  mcPytPhi->Add(mcPytEtaPhiChargeA,-1);
			  mcPhoPhi->Add(mcPhoEtaPhiChargeA,-1);

			  TH1F* dataPhi0B = (TH1F*)dataPhi->ProjectionY(Form("dataPhiCharge%s0B",charge[iC].Data()),1,300);
			  TH1F* pytPhi0B = (TH1F*)mcPytPhi->ProjectionY(Form("pytPhiCharge%s0B",charge[iC].Data()),1,300);
			  TH1F* phoPhi0B = (TH1F*)mcPhoPhi->ProjectionY(Form("phoPhiCharge%s0B",charge[iC].Data()),1,300);

			  dataPhi0B->GetXaxis()->SetRangeUser(-0.1,0.1);
			  pytPhi0B->GetXaxis()->SetRangeUser(-0.1,0.1);
			  phoPhi0B->GetXaxis()->SetRangeUser(-0.1,0.1);

			  dataPhi0B->Sumw2();
			  pytPhi0B->Sumw2();
			  phoPhi0B->Sumw2();

			  Double_t nData0B = dataPhi0B->GetEntries();
			  Double_t nMCPyt0B = pytPhi0B->GetEntries();
			  Double_t nMCPho0B = phoPhi0B->GetEntries();

			  dataPhi0B->Scale(1/nData0B);
			  pytPhi0B->Scale(1/nMCPyt0B);
			  phoPhi0B->Scale(1/nMCPho0B);

			  TGaxis::SetExponentOffset(-0.06, 0.01, "x");
			  cs->cd();
			  DrawAutoGammaCompare3H(pytPhi0B, phoPhi0B, dataPhi0B,
									 " ",
									 "#Delta#phi",
									 "#frac{1}{N} #frac{dN}{d#Delta#phi}",
									 0,0,0,
									 0,0,0,
									 1,-0.1,0.1,
									 1,1.3,"Data",fPlotMCPyt.Data(),fPlotMCPho.Data());
			  PutProcessLabelAndEnergyOnPlot(0.8, 0.8, 0.03, fCollisionSystem.Data(), Form("%s clusters", calo.Data()), "");
			  cs->SetLogy(1); cs->SetLogz(0); cs->Update();
			  cs->SaveAs(Form("%s/%s/%s_%s.%s", outputDir.Data(), fComparison.Data(), "DeltaPhi", charge[iC].Data(), suffix.Data()));
			  cs->Clear();
			  TGaxis::SetExponentOffset(0, 0, "x");
		  }
	  }
//---------
	  TH2D* dataMotherPi0Conv_Eta_Phi = (TH2D*) hESDData->FindObject("ESD_MotherPi0ConvPhoton_Eta_Phi");
	  TH2D* mcPytMotherPi0Conv_Eta_Phi = (TH2D*) hESDMCPyt->FindObject("ESD_MotherPi0ConvPhoton_Eta_Phi");
	  TH2D* mcPhoMotherPi0Conv_Eta_Phi = (TH2D*) hESDMCPho->FindObject("ESD_MotherPi0ConvPhoton_Eta_Phi");

	  if(dataMotherPi0Conv_Eta_Phi && mcPytMotherPi0Conv_Eta_Phi && mcPhoMotherPi0Conv_Eta_Phi){
		  TH1D* dataMotherPi0Conv_Eta = (TH1D*) dataMotherPi0Conv_Eta_Phi->ProjectionY("dataMotherPi0Conv_Eta",1,600);
		  TH1D* mcPytMotherPi0Conv_Eta = (TH1D*) mcPytMotherPi0Conv_Eta_Phi->ProjectionY("mcPytMotherPi0Conv_Eta",1,600);
		  TH1D* mcPhoMotherPi0Conv_Eta = (TH1D*) mcPhoMotherPi0Conv_Eta_Phi->ProjectionY("mcPhoMotherPi0Conv_Eta",1,600);

		  dataMotherPi0Conv_Eta->Sumw2();
		  mcPytMotherPi0Conv_Eta->Sumw2();
		  mcPhoMotherPi0Conv_Eta->Sumw2();
		  dataMotherPi0Conv_Eta->Scale(scaleData);
		  mcPytMotherPi0Conv_Eta->Scale(scaleMCPyt);
		  mcPhoMotherPi0Conv_Eta->Scale(scaleMCPho);
		  cs->cd();

		  Double_t bin[2]={6E-7,1E-4};
		  if(CheckForData8TeV(DataSet)) {bin[0]=6E-7; bin[1]=4E-4;}
		  DrawAutoGammaCompare3H(mcPytMotherPi0Conv_Eta, mcPhoMotherPi0Conv_Eta, dataMotherPi0Conv_Eta,
							  " ",
							  "#eta_{#gamma_{conv} under #pi^{0}-peak}",
							  "#frac{1}{N_{Events}} #frac{dN}{d#eta}",
							  0,0,0,
							  1,bin[0],bin[1],
							  1,-1,1,
							  1,1.3,"Data",fPlotMCPyt.Data(),fPlotMCPho.Data());
		  PutProcessLabelAndEnergyOnPlot(0.8, 0.8, 0.03, fCollisionSystem.Data(), Form("%s clusters", calo.Data()), "");
		  cs->SetLogy(1); cs->SetLogz(0); cs->Update();
		  cs->SaveAs(Form("%s/%s/%s.%s", outputDir.Data(), fComparison.Data(), "ConvPhotonPi0_Eta", suffix.Data()));
		  cs->Clear();
	  }

	  if(dataMotherPi0Conv_Eta_Phi && mcPytMotherPi0Conv_Eta_Phi && mcPhoMotherPi0Conv_Eta_Phi){
		  TH1D* dataMotherPi0Conv_Phi = (TH1D*) dataMotherPi0Conv_Eta_Phi->ProjectionX("dataMotherPi0Conv_Phi",1,200);
		  TH1D* mcPytMotherPi0Conv_Phi = (TH1D*) mcPytMotherPi0Conv_Eta_Phi->ProjectionX("mcPytMotherPi0Conv_Phi",1,200);
		  TH1D* mcPhoMotherPi0Conv_Phi = (TH1D*) mcPhoMotherPi0Conv_Eta_Phi->ProjectionX("mcPhoMotherPi0Conv_Phi",1,200);

		  dataMotherPi0Conv_Phi->Sumw2();
		  mcPytMotherPi0Conv_Phi->Sumw2();
		  mcPhoMotherPi0Conv_Phi->Sumw2();
		  dataMotherPi0Conv_Phi->Scale(scaleData);
		  mcPytMotherPi0Conv_Phi->Scale(scaleMCPyt);
		  mcPhoMotherPi0Conv_Phi->Scale(scaleMCPho);
		  cs->cd();

		  Double_t bin[2]={1E-8,1E-3};
		  if(CheckForData8TeV(DataSet)) {bin[0]=1E-9; bin[1]=1E-2;}
		  DrawAutoGammaCompare3H(mcPytMotherPi0Conv_Phi, mcPhoMotherPi0Conv_Phi, dataMotherPi0Conv_Phi,
							  " ",
							  "#phi_{#gamma_{conv} under #pi^{0}-peak}",
							  "#frac{1}{N_{Events}} #frac{dN}{d#phi}",
							  0,0,0,
							  1,bin[0],bin[1],
							  1,0.8,3.8,
							  1,1.3,"Data",fPlotMCPyt.Data(),fPlotMCPho.Data());
		  PutProcessLabelAndEnergyOnPlot(0.8, 0.8, 0.03, fCollisionSystem.Data(), Form("%s clusters", calo.Data()), "");
		  cs->SetLogy(1); cs->SetLogz(0); cs->Update();
		  cs->SaveAs(Form("%s/%s/%s.%s", outputDir.Data(), fComparison.Data(), "ConvPhotonPi0_Phi", suffix.Data()));
		  cs->Clear();
	  }
//---------
	  TH2D* dataMotherEtaConv_Eta_Phi = (TH2D*) hESDData->FindObject("ESD_MotherEtaConvPhoton_Eta_Phi");
	  TH2D* mcPytMotherEtaConv_Eta_Phi = (TH2D*) hESDMCPyt->FindObject("ESD_MotherEtaConvPhoton_Eta_Phi");
	  TH2D* mcPhoMotherEtaConv_Eta_Phi = (TH2D*) hESDMCPho->FindObject("ESD_MotherEtaConvPhoton_Eta_Phi");

	  if(dataMotherEtaConv_Eta_Phi && mcPytMotherEtaConv_Eta_Phi && mcPhoMotherEtaConv_Eta_Phi){
		  TH1D* dataMotherEtaConv_Eta = (TH1D*) dataMotherEtaConv_Eta_Phi->ProjectionY("dataMotherEtaConv_Eta",1,600);
		  TH1D* mcPytMotherEtaConv_Eta = (TH1D*) mcPytMotherEtaConv_Eta_Phi->ProjectionY("mcPytMotherEtaConv_Eta",1,600);
		  TH1D* mcPhoMotherEtaConv_Eta = (TH1D*) mcPhoMotherEtaConv_Eta_Phi->ProjectionY("mcPhoMotherEtaConv_Eta",1,600);

		  dataMotherEtaConv_Eta->Sumw2();
		  mcPytMotherEtaConv_Eta->Sumw2();
		  mcPhoMotherEtaConv_Eta->Sumw2();
		  dataMotherEtaConv_Eta->Scale(scaleData);
		  mcPytMotherEtaConv_Eta->Scale(scaleMCPyt);
		  mcPhoMotherEtaConv_Eta->Scale(scaleMCPho);
		  cs->cd();

		  Double_t bin[2]={5E-6,2E-4};
		  if(CheckForData8TeV(DataSet)) {bin[0]=8E-6; bin[1]=4E-4;}
		  DrawAutoGammaCompare3H(mcPytMotherEtaConv_Eta, mcPhoMotherEtaConv_Eta, dataMotherEtaConv_Eta,
								 " ",
								 "#eta_{#gamma_{conv} under #eta-peak}",
								 "#frac{1}{N_{Events}} #frac{dN}{d#eta}",
								 0,0,0,
								 1,bin[0],bin[1],
								 1,-1,1,
								 1,1.3,"Data",fPlotMCPyt.Data(),fPlotMCPho.Data());
		  PutProcessLabelAndEnergyOnPlot(0.8, 0.8, 0.03, fCollisionSystem.Data(), Form("%s clusters", calo.Data()), "");
		  cs->SetLogy(1); cs->SetLogz(0); cs->Update();
		  cs->SaveAs(Form("%s/%s/%s.%s", outputDir.Data(), fComparison.Data(), "ConvPhotonEta_Eta", suffix.Data()));
		  cs->Clear();
	  }

	  if(dataMotherEtaConv_Eta_Phi && mcPytMotherEtaConv_Eta_Phi && mcPhoMotherEtaConv_Eta_Phi){
		  TH1D* dataMotherEtaConv_Phi = (TH1D*) dataMotherEtaConv_Eta_Phi->ProjectionX("dataMotherEtaConv_Phi",1,200);
		  TH1D* mcPytMotherEtaConv_Phi = (TH1D*) mcPytMotherEtaConv_Eta_Phi->ProjectionX("mcPytMotherEtaConv_Phi",1,200);
		  TH1D* mcPhoMotherEtaConv_Phi = (TH1D*) mcPhoMotherEtaConv_Eta_Phi->ProjectionX("mcPhoMotherEtaConv_Phi",1,200);

		  Bool_t plotY = kTRUE;
		  if(CheckForData8TeV(DataSet)) plotY = kFALSE;

		  dataMotherEtaConv_Phi->Sumw2();
		  mcPytMotherEtaConv_Phi->Sumw2();
		  mcPhoMotherEtaConv_Phi->Sumw2();
		  dataMotherEtaConv_Phi->Scale(scaleData);
		  mcPytMotherEtaConv_Phi->Scale(scaleMCPyt);
		  mcPhoMotherEtaConv_Phi->Scale(scaleMCPho);
		  cs->cd();
		  DrawAutoGammaCompare3H(mcPytMotherEtaConv_Phi, mcPhoMotherEtaConv_Phi, dataMotherEtaConv_Phi,
								 " ",
								 "#phi_{#gamma_{conv} under #eta-peak}",
								 "#frac{1}{N_{Events}} #frac{dN}{d#phi}",
								 0,0,0,
								 plotY,1E-7,1E-4,
								 0,0,0,
								 1,1.3,"Data",fPlotMCPyt.Data(),fPlotMCPho.Data());
		  PutProcessLabelAndEnergyOnPlot(0.8, 0.8, 0.03, fCollisionSystem.Data(), Form("%s clusters", calo.Data()), "");
		  cs->SetLogy(1); cs->SetLogz(0); cs->Update();
		  cs->SaveAs(Form("%s/%s/%s.%s", outputDir.Data(), fComparison.Data(), "ConvPhotonEta_Phi", suffix.Data()));
		  cs->Clear();
	  }

//---------
	  TH1D* dataEnergyFracCells = (TH1D*) CaloExtQAContainerData->FindObject(Form("ClusterEnergyFracCells_afterClusterQA %s",fClusterCutSelection[2].Data()));
	  TH1D* mcPytEnergyFracCells = (TH1D*) CaloExtQAContainerMCPyt->FindObject(Form("ClusterEnergyFracCells_afterClusterQA %s",fClusterCutSelection[0].Data()));
	  TH1D* mcPhoEnergyFracCells = (TH1D*) CaloExtQAContainerMCPho->FindObject(Form("ClusterEnergyFracCells_afterClusterQA %s",fClusterCutSelection[1].Data()));
	  TH1D* dataClusterCellIDs = (TH1D*)CaloExtQAContainerData->FindObject(Form("ClusterIncludedCells_afterClusterQA %s", fClusterCutSelection[2].Data()));
	  TH1D* mcPytClusterCellIDs = (TH1D*)CaloExtQAContainerMCPyt->FindObject(Form("ClusterIncludedCells_afterClusterQA %s", fClusterCutSelection[0].Data()));
	  TH1D* mcPhoClusterCellIDs = (TH1D*)CaloExtQAContainerMCPho->FindObject(Form("ClusterIncludedCells_afterClusterQA %s", fClusterCutSelection[1].Data()));

	  TGaxis::SetExponentOffset(-0.06, -0.04, "x");
	  if(dataEnergyFracCells && mcPytEnergyFracCells && mcPhoEnergyFracCells && dataClusterCellIDs && mcPytClusterCellIDs && mcPhoClusterCellIDs){
		  dataEnergyFracCells->Sumw2();
		  mcPytEnergyFracCells->Sumw2();
		  mcPhoEnergyFracCells->Sumw2();
		  dataClusterCellIDs->Sumw2();
		  mcPytClusterCellIDs->Sumw2();
		  mcPhoClusterCellIDs->Sumw2();

//		  dataEnergyFracCells->Divide(dataClusterCellIDs);
//		  mcPytEnergyFracCells->Divide(mcPytClusterCellIDs);
//		  mcPhoEnergyFracCells->Divide(mcPhoClusterCellIDs);

		  mcPytEnergyFracCells->Add(dataEnergyFracCells,-1);
		  mcPhoEnergyFracCells->Add(dataEnergyFracCells,-1);

		  cs->cd();
		  DrawAutoGammaCompare2H(mcPytEnergyFracCells, mcPhoEnergyFracCells,
								" ",
								"CellID",
								"Difference between MC and Data #frac{dN}{dCellID}",
								0,0,0,
								1,-0.5,0.5,
								1,0,nCaloCells,
								1,1.3,fPlotMCPyt.Data(),fPlotMCPho.Data());
		  PutProcessLabelAndEnergyOnPlot(0.8, 0.8, 0.03, fCollisionSystem.Data(), Form("%s clusters", calo.Data()), "");
		  cs->SetLogy(0); cs->SetLogz(0); cs->Update();
		  cs->SaveAs(Form("%s/%s/%s.%s", outputDir.Data(), fComparison.Data(), "ClusterEnergyFracCells", suffix.Data()));
		  cs->Clear();
	  }

	  if(dataClusterCellIDs && mcPytClusterCellIDs && mcPhoClusterCellIDs){
		  dataClusterCellIDs->Sumw2();
		  mcPytClusterCellIDs->Sumw2();
		  mcPhoClusterCellIDs->Sumw2();

		  dataClusterCellIDs->Scale(1/dataClusterCellIDs->GetEntries());
		  mcPytClusterCellIDs->Scale(1/mcPytClusterCellIDs->GetEntries());
		  mcPhoClusterCellIDs->Scale(1/mcPhoClusterCellIDs->GetEntries());

		  mcPytClusterCellIDs->Add(dataClusterCellIDs,-1);
		  mcPhoClusterCellIDs->Add(dataClusterCellIDs,-1);

		  cs->cd();
		  DrawAutoGammaCompare2H(mcPytClusterCellIDs, mcPhoClusterCellIDs,
								 " ",
								 "Cell ID in accepted Clusters",
								 "Difference between MC and Data #frac{d#it{N}}{d#it{Cell ID}}",
								 0,0,0,
								 0,0,0,
								 1,0,nCaloCells,
								 1,1.3,fPlotMCPyt.Data(),fPlotMCPho.Data());
		  PutProcessLabelAndEnergyOnPlot(0.8, 0.8, 0.03, fCollisionSystem.Data(), Form("%s clusters", calo.Data()), "");
		  cs->SetLogy(0); cs->SetLogz(0); cs->Update();
		  cs->SaveAs(Form("%s/%s/%s.%s", outputDir.Data(), fComparison.Data(), "ClusterIncludedCells", suffix.Data()));
		  cs->Clear();
	  }
	  TGaxis::SetExponentOffset(0, 0, "x");
//---------
    delete cs;
    }

	if(cellQAData){
		TH2F* fHistDataCell = (TH2F*)CaloExtQAContainerData->FindObject(Form("CellEnergyVsCellID %s", fClusterCutSelection[2].Data()));
		TH2F* fHistDataCellTime = (TH2F*)CaloExtQAContainerData->FindObject(Form("CellTimeVsCellID %s", fClusterCutSelection[2].Data()));
		TH2F* fHistMCPytCell = (TH2F*)CaloExtQAContainerMCPyt->FindObject(Form("CellEnergyVsCellID %s", fClusterCutSelection[0].Data()));
		TH2F* fHistMCPytCellTime = (TH2F*)CaloExtQAContainerMCPyt->FindObject(Form("CellTimeVsCellID %s", fClusterCutSelection[0].Data()));
		TH2F* fHistMCPhoCell = (TH2F*)CaloExtQAContainerMCPho->FindObject(Form("CellEnergyVsCellID %s", fClusterCutSelection[1].Data()));
		TH2F* fHistMCPhoCellTime = (TH2F*)CaloExtQAContainerMCPho->FindObject(Form("CellTimeVsCellID %s", fClusterCutSelection[1].Data()));

		vector<Int_t> allCells;
		CollectAndPlotBadCellCandidates(fLog, allCells, cellQAData->cellIDsEnergy,"Energy - Mean/Sigma");
		CollectAndPlotBadCellCandidates(fLog, allCells, cellQAData->cellIDsTime,"Time - Mean/Sigma");
		CollectAndPlotBadCellCandidates(fLog, allCells, cellQAData->cellIDsHotCells1D,"HotCells1D");
		if(isMCPytFile&&isMCPhoFile)CheckBadCellCandidates(fHistDataCellTime, fHistMCPytCellTime, fHistMCPhoCellTime, cellQAData->cellIDsHotCellsTime1D,"HotCellsTime1D");
		CollectAndPlotBadCellCandidates(fLog, allCells, cellQAData->cellIDsHotCellsTime1D,"HotCellsTime1D");
		CollectAndPlotBadCellCandidates(fLog, allCells, cellQAData->cellIDsHotCells2D,"HotCells2D");
		CollectAndPlotBadCellCandidates(fLog, allCells, cellQAData->cellIDsMissing,"Missing MC-Data");

		cout << "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;
		fLog << "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;
		cout << "AllCells.size before sort and unique: " << allCells.size() << ".";
		fLog << "AllCells.size before sort and unique: " << allCells.size() << ".";
		if((Int_t)allCells.size()>500){
			cout << "\n++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;
			cout << "ERROR: allCells.size() too big " << allCells.size() << ", check cuts!" << endl;
			cout << "RETURNING..." << endl;
			fLog << "\n++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;
			fLog << "ERROR: allCells.size() too big " << allCells.size() << ", check cuts!" << endl;
			fLog << "RETURNING..." << endl;
			return;
		}
		selection_sort(allCells.begin(),allCells.end());
		vector<Int_t>::iterator it;
		it = unique(allCells.begin(),allCells.end());
		allCells.resize( distance(allCells.begin(),it) );
		cout << "Finally " << allCells.size() << " different cells found!" << endl;
		fLog << "Finally " << allCells.size() << " different cells found!" << endl;

		fstream fBadCells;
		fBadCells.open(Form("%s/Cells/%s.log",outputDir.Data(),DataSet.Data()), ios::out);
		for(Int_t iC=0; iC<(Int_t)allCells.size(); iC++){
			cout << allCells.at(iC) << ", ";
			fLog << allCells.at(iC) << ", ";
			fBadCells << allCells.at(iC) << endl;
		}
		fBadCells.close();
		cout << "\n++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;
		fLog << "\n++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;

		TCanvas* canvas = new TCanvas("canvas","",200,10,1350,900);  // gives the page size
		Double_t leftMargin = 0.1; Double_t rightMargin = 0.1; Double_t topMargin = 0.06; Double_t bottomMargin = 0.1;
		DrawGammaCanvasSettings(canvas, leftMargin, rightMargin, topMargin, bottomMargin);

		if((Int_t)allCells.size()>0){
			PlotBadCellReasons(cellQAData,allCells,canvas,outputDir,suffix,calo,fPlot,DataSet,fCollisionSystem);
			PlotBadCellOverview(kTRUE,kFALSE,fHistDataCell,allCells,canvas,outputDir,suffix,calo,fPlotData,DataSet,fCollisionSystem);
			if(isMCPytFile)PlotBadCellOverview(kTRUE,kTRUE,fHistMCPytCell,allCells,canvas,outputDir,suffix,calo,fPlotMCPyt,MCPyt,fCollisionSystem);
			if(isMCPhoFile)PlotBadCellOverview(kTRUE,kTRUE,fHistMCPhoCell,allCells,canvas,outputDir,suffix,calo,fPlotMCPho,MCPho,fCollisionSystem);
			PlotBadCellOverview(kFALSE,kFALSE,fHistDataCellTime,allCells,canvas,outputDir,suffix,calo,fPlotData,DataSet,fCollisionSystem);
			if(isMCPytFile)PlotBadCellOverview(kFALSE,kTRUE,fHistMCPytCellTime,allCells,canvas,outputDir,suffix,calo,fPlotMCPyt,MCPyt,fCollisionSystem);
			if(isMCPhoFile)PlotBadCellOverview(kFALSE,kTRUE,fHistMCPhoCellTime,allCells,canvas,outputDir,suffix,calo,fPlotMCPho,MCPho,fCollisionSystem);

			DrawGammaCanvasSettings(canvas, 0.11, 0.02, 0.04, 0.11);
			if(isMCPytFile&&isMCPhoFile)PlotBadCellComparison(fHistDataCell,fHistMCPytCell,fHistMCPhoCell,allCells,canvas,outputDir,suffix,calo,"Data",fPlotMCPyt,fPlotMCPho,fCollisionSystem);
		}
		char* nameOutput = Form("%s/%s/ClusterQA/ClusterQA_%s.root",fCutSelection[2].Data(),fEnergyFlag.Data(),fPrefixData.Data());
		TFile* fOutput = new TFile(nameOutput,"UPDATE");
		cout << "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;
		cout << "Reopening Output file: " << nameOutput << " to store BadCellCandidates" << endl;
		cout << "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;
		fLog << "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;
		fLog << "Reopening Output file: " << nameOutput << " to store BadCellCandidates" << endl;
		fLog << "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;

		SaveBadCellCandidates(cellQAData->cellIDsEnergy,"Energy");
		SaveBadCellCandidates(cellQAData->cellIDsTime,"Time");
		SaveBadCellCandidates(cellQAData->cellIDsHotCells1D,"HotCells1D");
		SaveBadCellCandidates(cellQAData->cellIDsHotCellsTime1D,"HotCellsTime1D");
		SaveBadCellCandidates(cellQAData->cellIDsHotCells2D,"HotCells2D");
		SaveBadCellCandidates(cellQAData->cellIDsMissing,"Missing");
		SaveBadCellCandidates(allCells,"allCells");

		fOutput->Close();

		delete canvas;
	}

	CaloExtQAContainerMCPyt->Clear();
	CaloCutsContainerMCPyt->Clear();
	TopContainerMCPyt->Clear();
	TopDirMCPyt->Clear();
	CaloExtQAContainerMCPho->Clear();
	CaloCutsContainerMCPho->Clear();
	TopContainerMCPho->Clear();
	TopDirMCPho->Clear();
	CaloExtQAContainerData->Clear();
	CaloCutsContainerData->Clear();
	TopContainerData->Clear();
	TopDirData->Clear();

	fMCPyt->Delete();
	fMCPho->Delete();
	fData->Delete();

	delete cellQAData;

    cout << "Done with ClusterQA_pp" << endl;
    cout << "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;

	fLog.close();

    return;

}//end
