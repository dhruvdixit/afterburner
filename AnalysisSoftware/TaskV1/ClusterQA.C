#include "ClusterQA.h"

using namespace std;

void ClusterQA(
				TString select = "LHC12",
				Int_t cutNr = -1,			// if -1: you have to choose number at runtime
				Int_t doExtQA = 2,			// 0: switched off, 1: normal extQA, 2: with Cell level plots
				TString suffix = "eps",
				Int_t mode = 2
				)
{
	cout << "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;
	cout << "ClusterQA" << endl;
	cout << "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;

	gROOT->Reset();

	StyleSettingsThesis();
	SetPlotStyle();
//**************************************************************************************************************
	TString fEnergyFlag;
	TString fDate = ReturnDateString();
	TString fTextMeasurement = Form("#pi^{0} #rightarrow #gamma#gamma");
	TString fTextMeasurementEta = Form("#eta #rightarrow #gamma#gamma");
	TString fTextMeasurementMeson[2]={fTextMeasurement,fTextMeasurementEta};

	const Int_t maxSets = 8;
	Int_t nSets = 0;
	//nSets == 0 is always data!

	TString labelData = "Data";
	Color_t colorCompare[maxSets] = {kBlack, kRed+1, kMagenta+2, 807, 800, kGreen+2, kCyan+2, kBlue+1};

	TString DataSets[maxSets];
	TString plotDataSets[maxSets];
	TString pathDataSets[maxSets];
	TString nameMainDir[maxSets];

	Bool_t addSubfolder = kFALSE;

//choose which data set to process
//**************************************************************************************************************
	if(select.CompareTo("LHC13g-kEMCEG1")==0||select.CompareTo("LHC13g-kEMCEG2")==0){
	//LHC13g EGA Trigger
		nSets = 1;
		fEnergyFlag = "2.76TeV";
		pathDataSets[0] = "/home/daniel/data/work/Grid/Legotrain-vAN-20150825-ConvCalo/GammaConvCalo_LHC13g-pass3_95.root";
		if(select.CompareTo("LHC13g-kEMCEG1")==0){
			DataSets[0]="LHC13g-kEMCEG1"; cutNr=0;
		}else{
			DataSets[0]="LHC13g-kEMCEG2"; cutNr=1;
		}
		plotDataSets[0]="LHC13g";
	}
//**************************************************************************************************************
	else if(select.CompareTo("LHC13g")==0||select.CompareTo("LHC13g-kEMC7")==0){
	//LHC13g Trigger+MB
		nSets = 1;
		fEnergyFlag = "2.76TeV";
		pathDataSets[0] = "/home/daniel/data/work/Grid/Legotrain-vAN-20150825-ConvCalo/GammaConvCalo_LHC13g-pass3_96.root";
		if(select.CompareTo("LHC13g")==0){
			DataSets[0]="LHC13g"; cutNr=0;
		}else{
			DataSets[0]="LHC13g-kEMC7"; cutNr=1;
		}
		plotDataSets[0]="LHC13g";
	}
//**************************************************************************************************************
	else if(select.CompareTo("LHC11a-kEMC1")==0){
	//LHC11a Trigger
		cutNr = 1;
		nSets = 1;
		fEnergyFlag = "2.76TeV";
		pathDataSets[0] = "/home/daniel/data/work/Grid/Legotrain-vAN-20150825-ConvCalo/GammaConvCalo_LHC11a-pass4_1.root";
		DataSets[0]="LHC11a_p4_wSDD-kEMC1";
		plotDataSets[0]="LHC11a";
	}
//**************************************************************************************************************
	else if(select.CompareTo("LHC11a")==0){
	//LHC11a + MC
		cutNr = 0;
		nSets = 3;
		fEnergyFlag = "2.76TeV";
		pathDataSets[0] = "/home/daniel/data/work/Grid/Legotrain-vAN-20150825-ConvCalo/GammaConvCalo_LHC11a-pass4_1.root";
		pathDataSets[1] = "/home/daniel/data/work/Grid/Legotrain-vAN-20150825-ConvCalo/GammaConvCalo_MC_LHC12f1a_1.root";
		pathDataSets[2] = "/home/daniel/data/work/Grid/Legotrain-vAN-20150825-ConvCalo/GammaConvCalo_MC_LHC12f1b_1.root";
		DataSets[0]="LHC11a_p4_wSDD"; DataSets[1]="LHC12f1a"; DataSets[2]="LHC12f1b";
		plotDataSets[0]="LHC11a"; plotDataSets[1]="Pythia8"; plotDataSets[2]="Phojet";
	}
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
	}
//**************************************************************************************************************
	else if(select.CompareTo("LHC15-JJ")==0){
	//LHC15-JJ EvsM02
		cutNr = 0;
		nSets = 1;
		fEnergyFlag = "2.76TeV";
		pathDataSets[0] = "/home/daniel/data/work/Grid/Legotrain-vAN-20150720-EvsM02/GammaConvCalo_23.root";
		DataSets[0]="LHC15a3";
		plotDataSets[0]="LHC15a3a+b";
	}
//**************************************************************************************************************
	else if(select.CompareTo("LHC12")==0){
	//LHC12
		cutNr = 0;
		nSets = 4;
		fEnergyFlag = "8TeV";
		pathDataSets[0] = "/home/daniel/data/work/Grid/Legotrain-vAN-20150728-LHC12_QA-2nd/GammaConvCalo_LHC12abcdfghi-pass1_120.root";
		pathDataSets[1] = "/home/daniel/data/work/Grid/Legotrain-vAN-20150728-LHC12_QA-2nd/GammaConvCalo_MC_LHC14e2a_120.root";
		pathDataSets[2] = "/home/daniel/data/work/Grid/Legotrain-vAN-20150728-LHC12_QA-2nd/GammaConvCalo_MC_LHC14e2b_120.root";
		pathDataSets[3] = "/home/daniel/data/work/Grid/Legotrain-vAN-20150728-LHC12_QA-2nd/GammaConvCalo_MC_LHC14e2c_120.root";
		DataSets[0]="LHC12"; DataSets[1]="LHC14e2a"; DataSets[2]="LHC14e2b"; DataSets[3]="LHC14e2c";
		plotDataSets[0]="LHC12a-i"; plotDataSets[1]="Pythia8"; plotDataSets[2]="Pythia8+AddSig"; plotDataSets[3]="Phojet";
	}
//**************************************************************************************************************
	else if(select.BeginsWith("LHC12") && select.Length()==6){
	//LHC12 Periodwise
		addSubfolder=kTRUE;
		cutNr = 0;
		nSets = 4;
		fEnergyFlag="8TeV";
		pathDataSets[0] = Form("/home/daniel/data/work/Grid/Legotrain-vAN-20150728-LHC12_QA-2nd/GammaConvCalo_%s-pass1_120.root",select.Data());
		pathDataSets[1] = Form("/home/daniel/data/work/Grid/Legotrain-vAN-20150728-LHC12_QA-2nd/GammaConvCalo_MC_LHC14e2a-%s_120.root",select.Data());
		pathDataSets[2] = Form("/home/daniel/data/work/Grid/Legotrain-vAN-20150728-LHC12_QA-2nd/GammaConvCalo_MC_LHC14e2b-%s_120.root",select.Data());
		pathDataSets[3] = Form("/home/daniel/data/work/Grid/Legotrain-vAN-20150728-LHC12_QA-2nd/GammaConvCalo_MC_LHC14e2c-%s_120.root",select.Data());
		DataSets[0]=select; DataSets[1]=Form("LHC14e2a-%s",select.Data()); DataSets[2]=Form("LHC14e2b-%s",select.Data()); Form("LHC14e2c-%s",select.Data());
		plotDataSets[0]=select; plotDataSets[1]="Pythia8"; plotDataSets[2]="Pythia8+AddSig"; plotDataSets[3]="Phojet";
	}
//**************************************************************************************************************
	else if(select.BeginsWith("LHC12-kEMC")){
	//LHC12 Trigger
		cutNr = 0;
		nSets = 1;
		fEnergyFlag="8TeV";
		TString number = "";
		if(select.CompareTo("LHC12-kEMC7")==0) number = "121";
		else if(select.CompareTo("LHC12-kEMCEGA")==0) number = "122";
		else if(select.CompareTo("LHC12-kEMCEJE")==0) number = "123";
		else { cout << "No valid selection! Returning..." << endl; return;}
		pathDataSets[0] = Form("/home/daniel/data/work/Grid/Legotrain-vAN-20150625/GammaConvCalo_LHC12abcdfghi-pass1_%s.root",number.Data());
		DataSets[0]=select;
		plotDataSets[0]="LHC12";
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
		else if(select.EndsWith("-kEMCEJE")) number = "123";
		else { cout << "No valid selection! Returning..." << endl; return;}
		pathDataSets[0] = Form("/home/daniel/data/work/Grid/Legotrain-vAN-20150625/GammaConvCalo_%s-pass1_%s.root",selectResize.Data(),number.Data());
		DataSets[0]=select;
		plotDataSets[0]=selectResize;
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
	}

	else{
		cout << "No valid selection! Returning..." << endl;
		return;
	}
//**************************************************************************************************************
//**************************************************************************************************************
	if(nSets>maxSets){
		cout << "Maximum hardcoded number of Data Sets: " << maxSets << endl;
		cout << "You have chosen: " << nSets << ", returning!" << endl;
		return;
	}
//**************************************************************************************************************
//*****************************************************************************************************
//*****************************************************************************************************

	Int_t fMode = mode;
	// mode:	0 // new output PCM-PCM
	//			1 // new output PCM dalitz
	//			2 // new output PCM-EMCal
	//			3 // new output PCM-PHOS
	//          4 // new output EMCal-EMCal
	//          5 // new output PHOS-PHOS
	//			9 // old output PCM-PCM
	if(fMode == 0 || fMode == 1 || fMode == 9){ cout << "Returning, given mode contains no calo information: " << fMode << endl; return;}

	TFile** fFile = new TFile*[nSets];
	TFile** fOutput = new TFile*[nSets];
	TString *fCutSelection = new TString[nSets];
	TString *fEventCutSelection = new TString[nSets];
	TString *fGammaCutSelection = new TString[nSets];
	TString *fClusterCutSelection = new TString[nSets];
	TString *fElectronCutSelection = new TString[nSets];
	TString *fMesonCutSelection = new TString[nSets];

	for(Int_t i=0; i<nSets; i++){
		fFile[i] = new TFile(pathDataSets[i].Data(),"READ");
		if(fFile[i]->IsZombie()){cout << "ERROR: File " << pathDataSets[i].Data() << " could not be openend! Returning..." << endl; return;}
		else{
			cout << "Processing file: " << pathDataSets[i].Data();
			TKey *key;
			TIter next(fFile[i]->GetListOfKeys());
			while ((key=(TKey*)next())){
				cout << Form(" - found TopDir: %s",key->GetName());
				nameMainDir[i] = key->GetName();
			}
			cout << endl;
			if(nameMainDir[i].IsNull() || !nameMainDir[i].BeginsWith("Gamma")){cout << "ERROR, Unable to obtain valid name of MainDir:|" << nameMainDir[i].Data() << "|, running in mode: " << fMode << endl; return;}
		}
	}

//*****************************************************************************************************
//*****************************************************************************************************
//****************************** Determine which cut to process ***************************************
//*****************************************************************************************************
//*****************************************************************************************************

	vector <TString> cutsTemp;
	map<TString,Int_t> mapCuts;

	for(Int_t i=0; i<nSets; i++){
		TList *listInput =(TList*)fFile[i]->Get(nameMainDir[i].Data());
		if(!listInput) {cout << "ERROR: Could not find main dir: " << nameMainDir[i].Data() << " in file! Returning..." << endl; return;}
		for(Int_t j = 0; j<listInput->GetSize(); j++){
			TList *listCuts = (TList*)listInput->At(j);
			TString nameCuts = listCuts->GetName();
			if(nameCuts.BeginsWith("Cut Number")){
				nameCuts.Replace(0,11,"");
				if(i==0) {
					cutsTemp.push_back(nameCuts);
					mapCuts[nameCuts]=1;
				}else if( mapCuts.find(nameCuts) != mapCuts.end() ) mapCuts[nameCuts] += 1;
			}
		}
	}

	cout << "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;
	cout << "The following cuts are available:" << endl;
	Int_t nCuts = 0;
	vector <TString> cuts;
	for(Int_t i = 0; i < (Int_t) cutsTemp.size(); i++) {
		if(mapCuts[cutsTemp.at(i)]==nSets){ cout << Form("(%i) -- %s", i, cutsTemp.at(i).Data()) << endl; cuts.push_back(cutsTemp.at(i)); nCuts++;}
	}
	if(nCuts==0){ cout << "ERROR: No cut is available in all given data/MC sets! Returning..." << endl; return;}
	if(cutNr<0 || cutNr>nCuts){ cout << "ERROR: Specified cutNr not available (cutNr<0 or cutNr>nCuts)! Returning..." << endl; return;}

	if(cutNr == -1){
		do{ cin >> cutNr;}
		while( (cutNr < 0) || (cutNr > (Int_t) cuts.size()) );
	}

	cout << "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;
	cout << "Processing Cut Number: " << cutNr << endl;
	cout << cuts.at(cutNr) << endl;
	cout << "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;
	cout << "Pictures are saved as " << suffix.Data() << "!" << endl;
	cout << "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;
	for(Int_t i=0; i<nSets; i++){
		fCutSelection[i] = cuts.at(cutNr);
		fEventCutSelection[i] = ""; fGammaCutSelection[i] = ""; fClusterCutSelection[i] = ""; fElectronCutSelection[i] = ""; fMesonCutSelection[i] = "";
		ReturnSeparatedCutNumberAdvanced(fCutSelection[i], fEventCutSelection[i], fGammaCutSelection[i], fClusterCutSelection[i], fElectronCutSelection[i], fMesonCutSelection[i], fMode);
	}
	cout << "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;

	TString TrackMatchingEtaMax[10] = {"0","0.008", "0.012", "0.016", "0.018", "0.02", "0.022", "0.005", "0.01", "0.015"};
	TString TrackMatchingPhiMin[10] = {"0","-0.03", "-0.05", "-0.09", "-0.11", "-0.13", "-0.15", "-0.03", "-0.09", "-0.15"};
	TString TrackMatchingPhiMax[10] = {"0","0.03", "0.04", "0.06", "0.07", "0.08", "0.1", "0.03", "0.07", "0.11"};

	cout << "Obtaining trigger - ";
	TString fTriggerCut = fEventCutSelection[0](3,2);
	TString fTrigger = AnalyseSpecialTriggerCut(fTriggerCut.Atoi(), DataSets[0].Data());
	plotDataSets[0] += Form(" %s",fTrigger.Data());
	cout << fTrigger.Data() << " - was found!" << endl;
	if(plotDataSets[0].EndsWith("defined")){ cout << "ERROR, Trigger cut not defined, check settings of macro!, returning..." << endl; return;}

	cout << "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;

	TString calo;
	TString fClusters;
	Int_t iCalo = 0;
	Int_t nCaloModules = 0;
	Int_t nCaloCells = 0;

	if(fClusterCutSelection[0].BeginsWith('1')){
		calo="EMCal"; iCalo=1;
		fClusters = Form("%s clusters", calo.Data());
		nCaloModules = 10;
		nCaloCells = 11520;
	}else if(fClusterCutSelection[0].BeginsWith('2')){
		calo="PHOS"; iCalo=2;
		fClusters = Form("%s clusters", calo.Data());
		nCaloModules = 5;
		nCaloCells = 6000;
	}else {cout << "No correct calorimeter type found: " << calo.Data() << ", returning..." << endl; return;}

	TString fCollisionSystem = ReturnFullCollisionsSystem(fEnergyFlag);
	if (fCollisionSystem.CompareTo("") == 0){
		cout << "No correct collision system specification, has been given" << endl;
		return;
	}

	TString fDetectionProcess = ReturnFullTextReconstructionProcess(fMode);

	TString outputDir = Form("%s/%s/ClusterQA/%s",cuts.at(cutNr).Data(),fEnergyFlag.Data(),suffix.Data());
	if(addSubfolder) outputDir+=Form("/%s",DataSets[0].Data());

	gSystem->Exec("mkdir -p "+outputDir);
	gSystem->Exec("mkdir -p "+outputDir+"/Comparison");
	gSystem->Exec("mkdir -p "+outputDir+"/Comparison/Ratios");
	gSystem->Exec("mkdir -p "+outputDir+"/Cells");
	gSystem->Exec("mkdir -p "+outputDir+"/Cells/Detailed");

//*****************************************************************************************************
//*****************************************************************************************************
//*****************************************************************************************************

	fstream fLog;
	fLog.open(Form("%s/A-%s.log",outputDir.Data(),DataSets[0].Data()), ios::out);
	fLog << "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;
	for(Int_t i=0; i<nSets; i++) fLog << "Using file: " << pathDataSets[i].Data() << endl;
	fLog << "Energy: " << fEnergyFlag.Data() << endl;
	fLog << fCollisionSystem.Data() << endl;
	fLog << "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;
	fLog << "processed cut: " << cuts.at(cutNr).Data() << endl;
	fLog << calo.Data() << ", Modules: " << nCaloModules << ", Cells: " << nCaloCells << endl;

	TList** TopDir = new TList*[nSets];
	TList** TopContainer = new TList*[nSets];
	TList** ESDContainer = new TList*[nSets];
	TList** CaloCutsContainer = new TList*[nSets];
	TList** ConvCutsContainer = new TList*[nSets];
	TList** CaloExtQAContainer = new TList*[nSets];
	TList** TrueContainer = new TList*[nSets];
	TList** ClusterContainer = new TList*[nSets];

//*****************************************************************************************************
//*****************************************************************************************************
//****************************** Histograms for MC/Data ***********************************************
//*****************************************************************************************************
//*****************************************************************************************************

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
	}else if(CheckForData8TeV(DataSets[0])){
		fNBinsAnalysisPt = fNBins8000GeVPt;
		fBinsAnalysisPt = new Double_t[fNBinsAnalysisPt+1];
		for(Int_t iB=0; iB<fNBinsAnalysisPt+1; iB++) {fBinsAnalysisPt[iB] = fBins8000GeVPt[iB];}
	}else if(CheckForTriggerData8TeV(DataSets[0])){
		fNBinsAnalysisPt = fNBins8000GeVTriggerPt;
		fBinsAnalysisPt = new Double_t[fNBinsAnalysisPt+1];
		for(Int_t iB=0; iB<fNBinsAnalysisPt+1; iB++) {fBinsAnalysisPt[iB] = fBins8000GeVTriggerPt[iB];}
	}else{
		cout << "WARNING: No Binning loaded, nothing defined for " << DataSets[0].Data() << ". Loading standard 0.6-30 GeV..." << endl;
		fLog << "WARNING: No Binning loaded, nothing defined for " << DataSets[0].Data() << ". Loading standard 0.6-30 GeV..." << endl;
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

//*****************************************************************************************************
//*****************************************************************************************************
//************************************* Cell QA *******************************************************
//*****************************************************************************************************
//*****************************************************************************************************

// Setup of CellQA+defining cuts
	CellQAObj* cellQAData = NULL;
	Bool_t doCellQA = kFALSE;
	Bool_t useGoodRuns = kFALSE;
	TLine *line = new TLine();
	line->SetLineStyle(2);
	line->SetLineWidth(2);
	line->SetLineColor(1);
	if(CheckForData8TeV(DataSets[0])){
		doCellQA = kTRUE;
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
		if(useGoodRuns && DataSets[0].CompareTo("LHC12")==0){
//			const Int_t nGoodCells = ;
//			Int_t goodCells[nGoodCells]={129,760,869,1039,1367,1377,};
//			FillGoodCells(cellQAData,nGoodCells,goodCells);
		}
		if(DataSets[0].CompareTo("LHC12a")==0) setQAHotCells1D(cellQAData,0,9E3,0,1.4);
		//	setQAHotCells1D(cellQAData,9E2,3E4,0,10);
		if(DataSets[0].CompareTo("LHC12b")==0) setQAHotCells1D(cellQAData,0,3E3,0,1.4);
		if(DataSets[0].CompareTo("LHC12c")==0) setQAHotCells1D(cellQAData,0,7E3,0,1.4);
		if(DataSets[0].CompareTo("LHC12d")==0) setQAHotCells1D(cellQAData,0,4E3,0,1.4);
		if(DataSets[0].CompareTo("LHC12f")==0) setQAHotCells1D(cellQAData,0,3.5E3,0,1.4);
		if(DataSets[0].CompareTo("LHC12g")==0) setQAHotCells1D(cellQAData,0,1E3,0,1.4);
		if(DataSets[0].CompareTo("LHC12h")==0) {
			setQATime(cellQAData,0,0.05E-6,0.05E-6,0.2E-6);
			setQAHotCells1D(cellQAData,0,3.5E3,0,1.4);
		}
		if(DataSets[0].CompareTo("LHC12i")==0) {
			setQATime(cellQAData,0,0.07E-6,0.05E-6,0.2E-6);
			setQAHotCells1D(cellQAData,0,5E2,0,1.5);
		}
	}else if(DataSets[0].BeginsWith("LHC12-kEMC")){//CheckForTriggerData8TeV(DataSet)){
		doCellQA = kTRUE;
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
	}else if(DataSets[0].CompareTo("LHC11a_p4_wSDD")==0){
		doCellQA = kTRUE;
		cellQAData = new CellQAObj();
		setQAEnergy(cellQAData,0,0.25,0,0.25);
		setQATime(cellQAData,-0.005E-6,0.025E-6,0.005E-6,0.04E-6);
		setQAHotCells1D(cellQAData,0,6E3,0,1.5);
		const Int_t dim2D= 9;
		Double_t min2D[dim2D]={0,2.5,1.5,0.8,0.4,0.25,0.15,0.1,0.08};
		Double_t max2D[dim2D]={0,105,105,105,105,105,105,105,105};
		setQAHotCells2D(cellQAData,dim2D,min2D,max2D);
	}else if(DataSets[0].CompareTo("LHC11a_p4_wSDD-kEMC1")==0){
		doCellQA = kTRUE;
		cellQAData = new CellQAObj();
		setQAEnergy(cellQAData,0,0.4,0,0.5);
		setQATime(cellQAData,-0.01E-6,0.025E-6,0,0.04E-6);
		setQAHotCells1D(cellQAData,0,1E3,0,1.5);
		const Int_t dim2D= 9;
		Double_t min2D[dim2D]={0,2.5,1.5,0.8,0.7,0.6,0.5,0.4,0.3};
		Double_t max2D[dim2D]={0,105,105,105,105,105,105,105,105};
		setQAHotCells2D(cellQAData,dim2D,min2D,max2D);
	}else{
		cout << "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;
		cout << "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;
		cout << "\tWARNING: For DataSet " << DataSets[0].Data() << " there are no cell cuts defined yet!" << endl;
		cout << "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;
		cout << "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;
		fLog << "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;
		fLog << "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;
		fLog << "\tWARNING: For DataSet " << DataSets[0].Data() << " there are no cell cuts defined yet!" << endl;
		fLog << "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;
		fLog << "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;
	}

	TString charge[2]={"pos","neg"};

	Bool_t isMC = kFALSE;
	CellQAObj* cellQA = cellQAData;

//*****************************************************************************************************
//*****************************************************************************************************
//****************************** Vectors for Histograms ***********************************************
//*****************************************************************************************************
//*****************************************************************************************************

	std::vector<TH1D*> vecNEvents;
	std::vector<TH1D*> vecVertexZ;
	std::vector<TH1D*> vecNGoodTracks;
	std::vector<TH1D*> vecClusterTimeBefore;
	std::vector<TH1D*> vecClusterTimeAfter;
	std::vector<TH2D*> vecEtaPhiAfterQA;
	std::vector<TH2D*> vecCellEnergyForComparison;
	std::vector<TH1D*> vecClusterR;
	std::vector<TH1D*> vecClusterEnergy;
	std::vector<TH1D*> vecClusterM02;
	std::vector<TH1D*> vecClusterM20;
	std::vector<TH1D*> vecClusterDispersion;
	std::vector<TH1D*> vecClusterNCells;
	std::vector<TH1D*> vecMatchingDeltaEtaPhi_matched[2];
	std::vector<TH1D*> vecMatchingDeltaEtaPhi_allTracks[2];
	std::vector<TH1D*> vecMatchingDeltaEtaPhiTracksAll[2][2];
	std::vector<TH1D*> vecMatchingDeltaEtaPhiTracksMatched[2][2];
	std::vector<TH2D*> vecMatchingDeltaEtaPhiTracksAllPt[3][2];
	std::vector<TH1D*> vecConvPhotonEtaPhi_Pi0[2];
	std::vector<TH1D*> vecConvPhotonEtaPhi_Eta[2];
	std::vector<TH1D*> vecClusterEnergyFracCells;
	std::vector<TH1D*> vecClusterIncludedCells;

	std::vector<TH2D*> vecESDMother;
	std::vector<TH2D*> vecESDMotherMatched;

	Double_t nEvents[nSets];
	Int_t minB = 0;
	Int_t maxB = 0;

//*****************************************************************************************************
//*****************************************************************************************************
//****************************** Looping over DataSets ************************************************
//*****************************************************************************************************
//*****************************************************************************************************

	TCanvas* canvas = new TCanvas("canvas","",200,10,1350,900);  // gives the page size
	TCanvas* cvsQuadratic = new TCanvas("cvsQuadratic","",200,10,1350,1350);  // gives the page size
	Double_t leftMargin = 0.1; Double_t rightMargin = 0.02; Double_t topMargin = 0.06; Double_t bottomMargin = 0.1;
	DrawGammaCanvasSettings(canvas,leftMargin,rightMargin,topMargin,bottomMargin);

	for(Int_t i=0; i<nSets; i++)
	{
	//-----------------------------------
		if(i>0){isMC = kTRUE; cellQA = 0x0;}
	//-----------------------------------
		TopDir[i] = (TList*) fFile[i]->Get(nameMainDir[i].Data());
		if(TopDir[i] == NULL) {cout << "ERROR: TopDir not Found"<<endl; return;}
		TopContainer[i]= (TList*) TopDir[i]->FindObject(Form("Cut Number %s",fCutSelection[i].Data()));
		if(TopContainer[i] == NULL) {cout << "ERROR: " << Form("Cut Number %s",fCutSelection[i].Data()) << " not found in File" << endl; return;}
		ESDContainer[i] = (TList*) TopContainer[i]->FindObject(Form("%s ESD histograms",fCutSelection[i].Data()));
		if(ESDContainer[i] == NULL) {cout << "ERROR: " << Form("%s ESD histograms",fCutSelection[i].Data()) << " not found in File" << endl; return;}
		CaloCutsContainer[i] = (TList*) TopContainer[i]->FindObject(Form("CaloCuts_%s",fClusterCutSelection[i].Data()));
		if(CaloCutsContainer[i] == NULL) {cout << "ERROR: " << Form("CaloCuts_%s",fClusterCutSelection[i].Data()) << " not found in File" << endl; return;}
		ConvCutsContainer[i] = (TList*) TopContainer[i]->FindObject(Form("ConvCuts_%s",fGammaCutSelection[i].Data()));
		if(ConvCutsContainer[i] == NULL) {cout << "ERROR: " << Form("ConvCuts_%s",fGammaCutSelection[i].Data()) << " not found in File" << endl; return;}
		ClusterContainer[i] = (TList*) TopContainer[i]->FindObject(Form("%s Cluster Output",fCutSelection[i].Data()));
		if(ClusterContainer[i] == NULL) {cout << "WARNING: " << Form("%s Cluster Output",fCutSelection[i].Data()) << " not found in File" << endl;}
		CaloExtQAContainer[i] = (TList*) TopContainer[i]->FindObject(Form("CaloExtQA_%s",fClusterCutSelection[i].Data()));
		if(CaloExtQAContainer[i] == NULL) {
			cout << "WARNING: " << Form("CaloExtQA_%s",fClusterCutSelection[i].Data()) << " not found in File, using CaloCuts-Container" << endl;
			CaloExtQAContainer[i] = CaloCutsContainer[i];
		}
		TrueContainer[i] = (TList*) TopContainer[i]->FindObject(Form("%s True histograms",fCutSelection[i].Data()));
		if(TrueContainer[i] == NULL) {cout << "INFO: " << Form("%s True histograms",fCutSelection[i].Data()) << " not found in File, processing data?" << endl;}
	//-----------------------------------
		nEvents[i] = 0;
		TH1D* fHistNEvents = (TH1D*)ESDContainer[i]->FindObject("NEvents");
		if(fHistNEvents) nEvents[i] = (Double_t) GetNEvents(fHistNEvents,kFALSE);
		else cout << "Info: Object |fHistNEvents| could not be found!" << endl;
	//-----------------------------------
		cout << endl;
		cout << "----------------------------------------------------------------------------" << endl;
		cout << "Processing file: " << pathDataSets[i].Data() << endl;
		cout << "Set: " << plotDataSets[i].Data() << " - NEvents: " << nEvents[i] << endl;
		cout << "----------------------------------------------------------------------------" << endl;
		cout << endl;
		fLog << "----------------------------------------------------------------------------" << endl;
		fLog << "Processing file: " << pathDataSets[i].Data() << endl;
		fLog << "Set: " << plotDataSets[i].Data() << " - NEvents: " << nEvents[i] << endl;
		fLog << "----------------------------------------------------------------------------" << endl;
	//-----------------------------------
		if( nEvents[i] < 1. ){cout << "ERROR: number of accepted events in data set is <1: " << nEvents[i] << "! Returning..." << endl; return;}
	//-----------------------------------
		const char* nameOutput = Form("%s/%s/ClusterQA/ClusterQA_%s.root",fCutSelection[i].Data(),fEnergyFlag.Data(),DataSets[i].Data());
		fOutput[i] = new TFile(nameOutput,"RECREATE");
		cout << endl;
		cout << "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;
		cout << "Output file: " << nameOutput << endl;
		cout << "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;
		cout << endl;
		fLog << "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;
		fLog << "Output file: " << nameOutput << endl;
		fLog << "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;
	//-----------------------------------
		if(fHistNEvents){
			DrawPeriodQAHistoTH1(canvas,leftMargin,rightMargin,topMargin,bottomMargin,kFALSE,kFALSE,kFALSE,
								fHistNEvents," ","","# of Entries",1,1,
								0.7,0.92,0.03,fCollisionSystem,plotDataSets[i],fClusters);
			SaveCanvasAndWriteHistogram(canvas, fHistNEvents, Form("%s/NEvents_%s.%s", outputDir.Data(), DataSets[i].Data(), suffix.Data()));
			vecNEvents.push_back(new TH1D(*fHistNEvents));
		}else cout << "Info: Object |fHistNEvents| could not be found! Skipping Draw..." << endl;
	//-----------------------------------
		TH1D* fHistCutIndex = (TH1D*)CaloCutsContainer[i]->FindObject(Form("IsPhotonSelected %s", fClusterCutSelection[i].Data()));
		if(fHistCutIndex){
			DrawPeriodQAHistoTH1(canvas,leftMargin,rightMargin,topMargin,bottomMargin,kFALSE,kFALSE,kFALSE,
								fHistCutIndex," ","","# of Entries",1,1,
								0.7,0.92,0.03,fCollisionSystem,plotDataSets[i],fClusters);
			SaveCanvasAndWriteHistogram(canvas, fHistCutIndex, Form("%s/IsPhotonSelected_%s.%s", outputDir.Data(), DataSets[i].Data(), suffix.Data()));
		}else cout << "Info: Object |fHistCutIndex| could not be found! Skipping Draw..." << endl;
	//-----------------------------------
		TH1D* fHistClusterIdentificationCuts = (TH1D*)CaloCutsContainer[i]->FindObject(Form("ClusterQualityCuts %s", fClusterCutSelection[i].Data()));
		if(fHistClusterIdentificationCuts){
			DrawPeriodQAHistoTH1(canvas,leftMargin,rightMargin,topMargin,bottomMargin,kFALSE,kFALSE,kFALSE,
								fHistClusterIdentificationCuts," ","","# of Entries",1,1,
								0.7,0.92,0.03,fCollisionSystem,plotDataSets[i],fClusters);
			SaveCanvasAndWriteHistogram(canvas, fHistClusterIdentificationCuts, Form("%s/ClusterQualityCuts_%s.%s", outputDir.Data(), DataSets[i].Data(), suffix.Data()));
		}else cout << "Info: Object |fHistClusterIdentificationCuts| could not be found! Skipping Draw..." << endl;
	//-----------------------------------
		TH1D* fHistVertexZ = (TH1D*)ESDContainer[i]->FindObject("VertexZ");
		if(fHistVertexZ){
			GetMinMaxBin(fHistVertexZ,minB,maxB);
			fHistVertexZ->GetXaxis()->SetRange(minB,maxB);
			DrawPeriodQAHistoTH1(canvas,leftMargin,rightMargin,topMargin,bottomMargin,kFALSE,kFALSE,kFALSE,
								fHistVertexZ," ","","# of Entries",1,1,
								0.7,0.92,0.03,fCollisionSystem,plotDataSets[i],fClusters);
			SaveCanvasAndWriteHistogram(canvas, fHistVertexZ, Form("%s/VertexZ_%s.%s", outputDir.Data(), DataSets[i].Data(), suffix.Data()));
			vecVertexZ.push_back(new TH1D(*fHistVertexZ));
		}else cout << "Info: Object |fHistVertexZ| could not be found! Skipping Draw..." << endl;
	//-----------------------------------
		TH1D* fHistNGoodTracks = (TH1D*)ESDContainer[i]->FindObject("GoodESDTracks");
		if(fHistNGoodTracks){
			GetMinMaxBin(fHistNGoodTracks,minB,maxB);
			fHistNGoodTracks->GetXaxis()->SetRange(minB,maxB);
			DrawPeriodQAHistoTH1(canvas,leftMargin,rightMargin,topMargin,bottomMargin,kFALSE,kTRUE,kFALSE,
								fHistNGoodTracks," ","","# of Entries",1,1,
								0.7,0.92,0.03,fCollisionSystem,plotDataSets[i],fClusters);
			SaveCanvasAndWriteHistogram(canvas, fHistNGoodTracks, Form("%s/NGoodTracks_%s.%s", outputDir.Data(), DataSets[i].Data(), suffix.Data()));
			vecNGoodTracks.push_back(new TH1D(*fHistNGoodTracks));
		}else cout << "Info: Object |fHistNGoodTracks| could not be found! Skipping Draw..." << endl;
	//-----------------------------------
		TH2D* fHistClusterEtavsPhiBeforeAcc = (TH2D*)CaloCutsContainer[i]->FindObject(Form("EtaPhi_beforeAcceptance %s", fClusterCutSelection[i].Data()));
		if(fHistClusterEtavsPhiBeforeAcc){
			fHistClusterEtavsPhiBeforeAcc->Sumw2();
			fHistClusterEtavsPhiBeforeAcc->Scale(1/nEvents[i]);
			fHistClusterEtavsPhiBeforeAcc->Scale(1/GetMeanTH2(fHistClusterEtavsPhiBeforeAcc));
			fHistClusterEtavsPhiBeforeAcc->GetZaxis()->SetRangeUser(0,2);
			DrawPeriodQAHistoTH2(canvas,leftMargin,0.1,topMargin,bottomMargin,kFALSE,kFALSE,kFALSE,
								fHistClusterEtavsPhiBeforeAcc,Form("%s - %s - %s",fCollisionSystem.Data(), plotDataSets[i].Data(), fClusters.Data()),"#phi_{Cluster}","#eta_{Cluster}",1,1);
			SaveCanvasAndWriteHistogram(canvas, fHistClusterEtavsPhiBeforeAcc, Form("%s/EtaVsPhi_%s_beforeAcceptance.%s", outputDir.Data(), DataSets[i].Data(), suffix.Data()));
		}else cout << "Info: Object |fHistClusterEtavsPhiBeforeAcc| could not be found! Skipping Draw..." << endl;
	//-----------------------------------
		TH2D* fHistClusterEtavsPhiAfterAcc = (TH2D*)CaloCutsContainer[i]->FindObject(Form("EtaPhi_afterAcceptance %s", fClusterCutSelection[i].Data()));
		if(fHistClusterEtavsPhiAfterAcc){
			fHistClusterEtavsPhiAfterAcc->Sumw2();
			fHistClusterEtavsPhiAfterAcc->Scale(1/nEvents[i]);
			fHistClusterEtavsPhiAfterAcc->Scale(1/GetMeanTH2(fHistClusterEtavsPhiAfterAcc));
			fHistClusterEtavsPhiAfterAcc->GetZaxis()->SetRangeUser(0,2);
			DrawPeriodQAHistoTH2(canvas,leftMargin,0.1,topMargin,bottomMargin,kFALSE,kFALSE,kFALSE,
								fHistClusterEtavsPhiAfterAcc,Form("%s - %s - %s",fCollisionSystem.Data(), plotDataSets[i].Data(), fClusters.Data()),"#phi_{Cluster}","#eta_{Cluster}",1,1);
			SaveCanvasAndWriteHistogram(canvas, fHistClusterEtavsPhiAfterAcc, Form("%s/EtaVsPhi_%s_afterAcceptance.%s", outputDir.Data(), DataSets[i].Data(), suffix.Data()));
		}else cout << "Info: Object |fHistClusterEtavsPhiAfterAcc| could not be found! Skipping Draw..." << endl;
	//-----------------------------------
		TH2D* fHistClusterEtavsPhiAfterQA = (TH2D*)CaloCutsContainer[i]->FindObject(Form("EtaPhi_afterClusterQA %s", fClusterCutSelection[i].Data()));
		if(fHistClusterEtavsPhiAfterQA){
			fHistClusterEtavsPhiAfterQA->Sumw2();
			fHistClusterEtavsPhiAfterQA->Scale(1/nEvents[i]);
			fHistClusterEtavsPhiAfterQA->Scale(1/GetMeanTH2(fHistClusterEtavsPhiAfterQA));
			fHistClusterEtavsPhiAfterQA->GetZaxis()->SetRangeUser(0,2);
			DrawPeriodQAHistoTH2(canvas,leftMargin,0.1,topMargin,bottomMargin,kFALSE,kFALSE,kFALSE,
								fHistClusterEtavsPhiAfterQA,Form("%s - %s - %s",fCollisionSystem.Data(), plotDataSets[i].Data(), fClusters.Data()),"#phi_{Cluster}","#eta_{Cluster}",1,1);
			SaveCanvasAndWriteHistogram(canvas, fHistClusterEtavsPhiAfterQA, Form("%s/EtaVsPhi_%s_afterClusterQA.%s", outputDir.Data(), DataSets[i].Data(), suffix.Data()));
			vecEtaPhiAfterQA.push_back(new TH2D(*fHistClusterEtavsPhiAfterQA));
		}else cout << "Info: Object |fHistClusterEtavsPhiAfterQA| could not be found! Skipping Draw..." << endl;
	//-----------------------------------
	//-----------------------------------
		TGaxis::SetExponentOffset(0.5, 0, "x");
	//-----------------------------------
		TH2D* fHistClusterTimevsEBeforeQA = (TH2D*)CaloCutsContainer[i]->FindObject(Form("ClusterTimeVsE_beforeClusterQA %s", fClusterCutSelection[i].Data()));
		TH1D* fHistClusterTimeBeforeQA = (TH1D*)fHistClusterTimevsEBeforeQA->ProjectionX("fHistClusterTimeBeforeQA",1,100);
		GetMinMaxBin(fHistClusterTimeBeforeQA,minB,maxB);

		if(fHistClusterTimevsEBeforeQA){
			fHistClusterTimevsEBeforeQA->GetXaxis()->SetRange(minB-10,maxB+10);
			DrawPeriodQAHistoTH2(canvas,leftMargin,0.1,topMargin,bottomMargin,kFALSE,kFALSE,kTRUE,
								fHistClusterTimevsEBeforeQA,Form("%s - %s - %s",fCollisionSystem.Data(), plotDataSets[i].Data(), fClusters.Data()),"#it{t}_{Cluster} (#mus)","#it{E}_{Cluster} (GeV)",1,1,
								0.65,0.92,0.03,fCollisionSystem,plotDataSets[i],fClusters);
			SaveCanvasAndWriteHistogram(canvas, fHistClusterTimevsEBeforeQA, Form("%s/ClusterTimeVsE_%s_beforeClusterQA.%s", outputDir.Data(), DataSets[i].Data(), suffix.Data()));
		}else cout << "Info: Object |fHistClusterTimevsEBeforeQA| could not be found! Skipping Draw..." << endl;

		if(fHistClusterTimeBeforeQA){
			fHistClusterTimeBeforeQA->GetXaxis()->SetRange(minB-10,maxB+10);
			DrawPeriodQAHistoTH1(canvas,leftMargin,rightMargin,topMargin,bottomMargin,kFALSE,kTRUE,kFALSE,
								fHistClusterTimeBeforeQA," ","#it{t}_{Cluster} (ns)","#frac{d#it{N}}{d#it{t}_{Cluster}}",1,1,
								0.7,0.92,0.03,fCollisionSystem,plotDataSets[i],fClusters);
			SaveCanvasAndWriteHistogram(canvas, fHistClusterTimeBeforeQA,Form("%s/ClusterTime_%s_beforeClusterQA.%s", outputDir.Data(), DataSets[i].Data(), suffix.Data()) );
			vecClusterTimeBefore.push_back(new TH1D(*fHistClusterTimeBeforeQA));
		}else cout << "Info: Object |fHistClusterTimeBeforeQA| could not be found! Skipping Draw..." << endl;
	//-----------------------------------
		TH2D* fHistClusterTimevsEAfterQA = (TH2D*)CaloCutsContainer[i]->FindObject(Form("ClusterTimeVsE_afterClusterQA %s", fClusterCutSelection[i].Data()));
		TH1D* fHistClusterTimeAfterQA = (TH1D*)fHistClusterTimevsEAfterQA->ProjectionX("fHistClusterTimeAfterQA",1,100);
		GetMinMaxBin(fHistClusterTimeAfterQA,minB,maxB);

		if(fHistClusterTimevsEAfterQA){
			fHistClusterTimevsEAfterQA->GetXaxis()->SetRange(minB-10,maxB+10);
			DrawPeriodQAHistoTH2(canvas,leftMargin,0.1,topMargin,bottomMargin,kFALSE,kFALSE,kTRUE,
								fHistClusterTimevsEAfterQA,Form("%s - %s - %s",fCollisionSystem.Data(), plotDataSets[i].Data(), fClusters.Data()),"#it{t}_{Cluster} (#mus)","#it{E}_{Cluster} (GeV)",1,1,
								0.65,0.92,0.03,fCollisionSystem,plotDataSets[i],fClusters);
			SaveCanvasAndWriteHistogram(canvas, fHistClusterTimevsEAfterQA, Form("%s/ClusterTimeVsE_%s_afterClusterQA.%s", outputDir.Data(), DataSets[i].Data(), suffix.Data()));
		}else cout << "Info: Object |fHistClusterTimevsEAfterQA| could not be found! Skipping Draw..." << endl;

		if(fHistClusterTimeAfterQA){
			fHistClusterTimeAfterQA->GetXaxis()->SetRange(minB-10,maxB+10);
			DrawPeriodQAHistoTH1(canvas,leftMargin,rightMargin,topMargin,bottomMargin,kFALSE,kTRUE,kFALSE,
								fHistClusterTimeAfterQA," ","#it{t}_{Cluster} (ns)","#frac{d#it{N}}{d#it{t}_{Cluster}}",1,1,
								0.7,0.92,0.03,fCollisionSystem,plotDataSets[i],fClusters);
			SaveCanvasAndWriteHistogram(canvas, fHistClusterTimeAfterQA, Form("%s/ClusterTime_%s_afterClusterQA.%s", outputDir.Data(), DataSets[i].Data(), suffix.Data()));
			vecClusterTimeAfter.push_back(new TH1D(*fHistClusterTimeAfterQA));
		}else cout << "Info: Object |fHistClusterTimeAfterQA| could not be found! Skipping Draw..." << endl;
	//-----------------------------------
		TGaxis::SetExponentOffset(0, 0, "x");
	//-----------------------------------
	//-----------------------------------
		TH1D* fHistEnergyOfClusterBeforeQA = (TH1D*)CaloCutsContainer[i]->FindObject(Form("EnergyOfCluster_beforeClusterQA %s", fClusterCutSelection[i].Data()));
		if(fHistEnergyOfClusterBeforeQA){
			fHistEnergyOfClusterBeforeQA = (TH1D*)fHistEnergyOfClusterBeforeQA->Rebin(fNBinsClusterPt, "energyBefore", fBinsClusterPt);
			fHistEnergyOfClusterBeforeQA->Divide(fDeltaPt);
			GetMinMaxBin(fHistEnergyOfClusterBeforeQA,minB,maxB);
			fHistEnergyOfClusterBeforeQA->GetXaxis()->SetRange(minB,maxB);
			//fHistEnergyOfClusterBeforeQA->GetXaxis()->SetRangeUser(minClusE,fBinsClusterPt[fNBinsClusterPt+1]);
			DrawPeriodQAHistoTH1(canvas,leftMargin,rightMargin,topMargin,bottomMargin,kTRUE,kTRUE,kFALSE,
								fHistEnergyOfClusterBeforeQA," ","#it{E}_{Cluster} (GeV)","#frac{d#it{N}}{d#it{E}_{Cluster}}",1,1,
								0.7,0.92,0.03,fCollisionSystem,plotDataSets[i],fClusters);
			SaveCanvasAndWriteHistogram(canvas, fHistEnergyOfClusterBeforeQA, Form("%s/EnergyOfCluster_%s_beforeClusterQA.%s", outputDir.Data(), DataSets[i].Data(), suffix.Data()));
		}else cout << "Info: Object |fHistEnergyOfClusterBeforeQA| could not be found! Skipping Draw..." << endl;
	//-----------------------------------
		TH1D* fHistEnergyOfClusterAfterQA = (TH1D*)CaloCutsContainer[i]->FindObject(Form("EnergyOfCluster_afterClusterQA %s", fClusterCutSelection[i].Data()));
		if(fHistEnergyOfClusterAfterQA){
			fHistEnergyOfClusterAfterQA = (TH1D*)fHistEnergyOfClusterAfterQA->Rebin(fNBinsClusterPt, "energyAfter", fBinsClusterPt);
			fHistEnergyOfClusterAfterQA->Sumw2();
			fHistEnergyOfClusterAfterQA->Divide(fDeltaPt);
			GetMinMaxBin(fHistEnergyOfClusterAfterQA,minB,maxB);
			fHistEnergyOfClusterAfterQA->GetXaxis()->SetRange(minB,maxB);
			//fHistEnergyOfClusterAfterQA->GetXaxis()->SetRangeUser(minClusE,fBinsClusterPt[fNBinsClusterPt+1]);
			DrawPeriodQAHistoTH1(canvas,leftMargin,rightMargin,topMargin,bottomMargin,kTRUE,kTRUE,kFALSE,
								fHistEnergyOfClusterAfterQA," ","#it{E}_{Cluster} (GeV)","#frac{d#it{N}}{d#it{E}_{Cluster}}",1,1,
								0.7,0.92,0.03,fCollisionSystem,plotDataSets[i],fClusters);
			SaveCanvasAndWriteHistogram(canvas, fHistEnergyOfClusterAfterQA, Form("%s/EnergyOfCluster_%s_afterClusterQA.%s", outputDir.Data(), DataSets[i].Data(), suffix.Data()));
			vecClusterEnergy.push_back(new TH1D(*fHistEnergyOfClusterAfterQA));
		}else cout << "Info: Object |fHistEnergyOfClusterAfterQA| could not be found! Skipping Draw..." << endl;
	//-----------------------------------
		TH1D* fHistNCellsBeforeQA = (TH1D*)CaloCutsContainer[i]->FindObject(Form("NCellPerCluster_beforeClusterQA %s", fClusterCutSelection[i].Data()));
		if(fHistNCellsBeforeQA){
			GetMinMaxBin(fHistNCellsBeforeQA,minB,maxB);
			fHistNCellsBeforeQA->GetXaxis()->SetRange(minB,maxB+1);
			//fHistNCellsBeforeQA->GetXaxis()->SetRangeUser(minNCells,25);
			DrawPeriodQAHistoTH1(canvas,leftMargin,rightMargin,topMargin,bottomMargin,kFALSE,kTRUE,kFALSE,
								 fHistNCellsBeforeQA," ","#it{E}_{Cluster} (GeV)","#frac{d#it{N}}{d#it{E}_{Cluster}}",1,1,
								 0.7,0.92,0.03,fCollisionSystem,plotDataSets[i],fClusters);
			SaveCanvasAndWriteHistogram(canvas, fHistNCellsBeforeQA, Form("%s/NCellPerCluster_%s_beforeClusterQA.%s", outputDir.Data(), DataSets[i].Data(), suffix.Data()));
		}else cout << "Info: Object |fHistNCellsBeforeQA| could not be found! Skipping Draw..." << endl;
	//-----------------------------------
		TH1D* fHistNCellsAfterQA = (TH1D*)CaloCutsContainer[i]->FindObject(Form("NCellPerCluster_afterClusterQA %s", fClusterCutSelection[i].Data()));
		if(fHistNCellsAfterQA){
			GetMinMaxBin(fHistNCellsAfterQA,minB,maxB);
			fHistNCellsAfterQA->GetXaxis()->SetRange(minB,maxB+1);
			//fHistNCellsAfterQA->GetXaxis()->SetRangeUser(minNCells,25);
			DrawPeriodQAHistoTH1(canvas,leftMargin,rightMargin,topMargin,bottomMargin,kFALSE,kTRUE,kFALSE,
								 fHistNCellsAfterQA," ","#it{E}_{Cluster} (GeV)","#frac{d#it{N}}{d#it{E}_{Cluster}}",1,1,
								 0.7,0.92,0.03,fCollisionSystem,plotDataSets[i],fClusters);
			SaveCanvasAndWriteHistogram(canvas, fHistNCellsAfterQA, Form("%s/NCellPerCluster_%s_afterClusterQA.%s", outputDir.Data(), DataSets[i].Data(), suffix.Data()));
			vecClusterNCells.push_back(new TH1D(*fHistNCellsAfterQA));
		}else cout << "Info: Object |fHistNCellsAfterQA| could not be found! Skipping Draw..." << endl;
	//-----------------------------------
		TH1D* fHistM02BeforeQA = (TH1D*)CaloCutsContainer[i]->FindObject(Form("M02_beforeClusterQA %s", fClusterCutSelection[i].Data()));
		if(fHistM02BeforeQA){
			GetMinMaxBin(fHistM02BeforeQA,minB,maxB);
			fHistM02BeforeQA->GetXaxis()->SetRange(minB-1,maxB+1);
			DrawPeriodQAHistoTH1(canvas,leftMargin,rightMargin,topMargin,bottomMargin,kFALSE,kTRUE,kFALSE,
								 fHistM02BeforeQA," ","#lambda_{0}^{2}","#frac{d#it{N}}{d#lambda_{0}^{2}}",1,1,
								 0.7,0.92,0.03,fCollisionSystem,plotDataSets[i],fClusters);
			SaveCanvasAndWriteHistogram(canvas, fHistM02BeforeQA, Form("%s/M02_%s_beforeClusterQA.%s", outputDir.Data(), DataSets[i].Data(), suffix.Data()));
		}else cout << "Info: Object |fHistM02BeforeQA| could not be found! Skipping Draw..." << endl;
	//-----------------------------------
		TH1D* fHistM02AfterQA = (TH1D*)CaloCutsContainer[i]->FindObject(Form("M02_afterClusterQA %s", fClusterCutSelection[i].Data()));
		if(fHistM02AfterQA){
			GetMinMaxBin(fHistM02AfterQA,minB,maxB);
			fHistM02AfterQA->GetXaxis()->SetRange(minB-1,maxB+1);
			DrawPeriodQAHistoTH1(canvas,leftMargin,rightMargin,topMargin,bottomMargin,kFALSE,kTRUE,kFALSE,
								 fHistM02AfterQA," ","#lambda_{0}^{2}","#frac{d#it{N}}{d#lambda_{0}^{2}}",1,1,
								 0.7,0.92,0.03,fCollisionSystem,plotDataSets[i],fClusters);
			SaveCanvasAndWriteHistogram(canvas, fHistM02AfterQA, Form("%s/M02_%s_afterClusterQA.%s", outputDir.Data(), DataSets[i].Data(), suffix.Data()));
			vecClusterM02.push_back(new TH1D(*fHistM02AfterQA));
		}else cout << "Info: Object |fHistM02AfterQA| could not be found! Skipping Draw..." << endl;
	//-----------------------------------
		TH1D* fHistM20BeforeQA = (TH1D*)CaloCutsContainer[i]->FindObject(Form("M20_beforeClusterQA %s", fClusterCutSelection[i].Data()));
		if(fHistM20BeforeQA){
			GetMinMaxBin(fHistM20BeforeQA,minB,maxB);
			fHistM20BeforeQA->GetXaxis()->SetRange(1,maxB+1);
			DrawPeriodQAHistoTH1(canvas,leftMargin,rightMargin,topMargin,bottomMargin,kFALSE,kTRUE,kFALSE,
								 fHistM20BeforeQA," ","#lambda_{0}^{2}","#frac{d#it{N}}{d#lambda_{1}^{2}}",1,1,
								 0.7,0.92,0.03,fCollisionSystem,plotDataSets[i],fClusters);
			SaveCanvasAndWriteHistogram(canvas, fHistM20BeforeQA, Form("%s/M20_%s_beforeClusterQA.%s", outputDir.Data(), DataSets[i].Data(), suffix.Data()));
		}else cout << "Info: Object |fHistM20BeforeQA| could not be found! Skipping Draw..." << endl;
	//-----------------------------------
		TH1D* fHistM20AfterQA = (TH1D*)CaloCutsContainer[i]->FindObject(Form("M20_afterClusterQA %s", fClusterCutSelection[i].Data()));
		if(fHistM20AfterQA){
			GetMinMaxBin(fHistM20AfterQA,minB,maxB);
			fHistM20AfterQA->GetXaxis()->SetRange(1,maxB+1);
			DrawPeriodQAHistoTH1(canvas,leftMargin,rightMargin,topMargin,bottomMargin,kFALSE,kTRUE,kFALSE,
								 fHistM20AfterQA," ","#lambda_{0}^{2}","#frac{d#it{N}}{d#lambda_{1}^{2}}",1,1,
								 0.7,0.92,0.03,fCollisionSystem,plotDataSets[i],fClusters);
			SaveCanvasAndWriteHistogram(canvas, fHistM20AfterQA, Form("%s/M20_%s_afterClusterQA.%s", outputDir.Data(), DataSets[i].Data(), suffix.Data()));
			vecClusterM20.push_back(new TH1D(*fHistM20AfterQA));
		}else cout << "Info: Object |fHistM20AfterQA| could not be found! Skipping Draw..." << endl;
	//-----------------------------------
		TH1D* fHistDispersionBeforeQA = (TH1D*)CaloCutsContainer[i]->FindObject(Form("Dispersion_beforeClusterQA %s", fClusterCutSelection[i].Data()));
		if(fHistDispersionBeforeQA){
			GetMinMaxBin(fHistDispersionBeforeQA,minB,maxB);
			fHistDispersionBeforeQA->GetXaxis()->SetRange(minB-1,maxB+1);
			DrawPeriodQAHistoTH1(canvas,leftMargin,rightMargin,topMargin,bottomMargin,kFALSE,kTRUE,kFALSE,
								 fHistDispersionBeforeQA," ","Cluster Dispersion","#frac{d#it{N}}{dDisp}",1,1,
								 0.7,0.92,0.03,fCollisionSystem,plotDataSets[i],fClusters);
			SaveCanvasAndWriteHistogram(canvas, fHistDispersionBeforeQA, Form("%s/Dispersion_%s_beforeClusterQA.%s", outputDir.Data(), DataSets[i].Data(), suffix.Data()));
		}else cout << "Info: Object |fHistDispersionBeforeQA| could not be found! Skipping Draw..." << endl;
	//-----------------------------------
		TH1D* fHistDispersionAfterQA = (TH1D*)CaloCutsContainer[i]->FindObject(Form("Dispersion_afterClusterQA %s", fClusterCutSelection[i].Data()));
		if(fHistDispersionAfterQA){
			GetMinMaxBin(fHistDispersionAfterQA,minB,maxB);
			fHistDispersionAfterQA->GetXaxis()->SetRange(minB-1,maxB+1);
			DrawPeriodQAHistoTH1(canvas,leftMargin,rightMargin,topMargin,bottomMargin,kFALSE,kTRUE,kFALSE,
								 fHistDispersionAfterQA," ","Cluster Dispersion","#frac{d#it{N}}{dDisp}",1,1,
								 0.7,0.92,0.03,fCollisionSystem,plotDataSets[i],fClusters);
			SaveCanvasAndWriteHistogram(canvas, fHistDispersionAfterQA, Form("%s/Dispersion_%s_afterClusterQA.%s", outputDir.Data(), DataSets[i].Data(), suffix.Data()));
			vecClusterDispersion.push_back(new TH1D(*fHistDispersionAfterQA));
		}else cout << "Info: Object |fHistDispersionAfterQA| could not be found! Skipping Draw..." << endl;
	//-----------------------------------
		TH1D* fHistClusterRBeforeQA = (TH1D*)CaloCutsContainer[i]->FindObject(Form("R_Cluster_beforeClusterQA %s", fClusterCutSelection[i].Data()));
		if(fHistClusterRBeforeQA){
			GetMinMaxBin(fHistClusterRBeforeQA,minB,maxB);
			fHistClusterRBeforeQA->GetXaxis()->SetRange(minB-5,maxB+5);
			DrawPeriodQAHistoTH1(canvas,leftMargin,rightMargin,topMargin,bottomMargin,kFALSE,kFALSE,kFALSE,
								 fHistClusterRBeforeQA," ","#it{R}_{Cluster} (cm)","#frac{d#it{N}}{d#it{R}}",1,1,
								 0.7,0.92,0.03,fCollisionSystem,plotDataSets[i],fClusters);
			SaveCanvasAndWriteHistogram(canvas, fHistClusterRBeforeQA, Form("%s/R_Cluster_%s_beforeClusterQA.%s", outputDir.Data(), DataSets[i].Data(), suffix.Data()));
		}else cout << "Info: Object |fHistClusterRBeforeQA| could not be found! Skipping Draw..." << endl;
	//-----------------------------------
		TH1D* fHistClusterRAfterQA = (TH1D*)CaloCutsContainer[i]->FindObject(Form("R_Cluster_afterClusterQA %s", fClusterCutSelection[i].Data()));
		if(fHistClusterRAfterQA){
			GetMinMaxBin(fHistClusterRAfterQA,minB,maxB);
			fHistClusterRAfterQA->GetXaxis()->SetRange(minB-5,maxB+5);
			DrawPeriodQAHistoTH1(canvas,leftMargin,rightMargin,topMargin,bottomMargin,kFALSE,kFALSE,kFALSE,
								 fHistClusterRAfterQA," ","#it{R}_{Cluster} (cm)","#frac{d#it{N}}{d#it{R}}",1,1,
								 0.7,0.92,0.03,fCollisionSystem,plotDataSets[i],fClusters);
			SaveCanvasAndWriteHistogram(canvas, fHistClusterRAfterQA, Form("%s/R_Cluster_%s_afterClusterQA.%s", outputDir.Data(), DataSets[i].Data(), suffix.Data()));
			vecClusterR.push_back(new TH1D(*fHistClusterRAfterQA));
		}else cout << "Info: Object |fHistClusterRAfterQA| could not be found! Skipping Draw..." << endl;
	//-----------------------------------
	//-----------------------------------
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

		TH2D* fHistClusterdEtadPhiBeforeQA = (TH2D*)CaloCutsContainer[i]->FindObject(Form("dEtaVsdPhi_beforeClusterQA %s", fClusterCutSelection[i].Data()));
		if(fHistClusterdEtadPhiBeforeQA){
			DrawPeriodQAHistoTH2(cvsQuadratic,0.12,0.12,topMargin,bottomMargin,kFALSE,kFALSE,kTRUE,
								fHistClusterdEtadPhiBeforeQA,Form("%s - %s - %s",fCollisionSystem.Data(), plotDataSets[i].Data(), fClusters.Data()),
								 "#Delta#eta_{Cluster - all Tracks}","#Delta#phi_{Cluster - all Tracks}",1,1.2);
			SaveCanvasAndWriteHistogram(cvsQuadratic, fHistClusterdEtadPhiBeforeQA, Form("%s/dEtaVsdPhi_allTracks_%s.%s", outputDir.Data(), DataSets[i].Data(), suffix.Data()));

			DrawPeriodQAHistoTH2(cvsQuadratic,0.12,0.12,topMargin,bottomMargin,kFALSE,kFALSE,kTRUE,
								fHistClusterdEtadPhiBeforeQA,Form("%s - %s - %s",fCollisionSystem.Data(), plotDataSets[i].Data(), fClusters.Data()),
								 "#Delta#eta_{Cluster - all Tracks}","#Delta#phi_{Cluster - all Tracks}",1,1.2);
			cutPos->Draw();
			cutNeg->Draw();
			SaveCanvasOnly(cvsQuadratic, Form("%s/dEtaVsdPhi_allTracks_WithCuts_%s.%s", outputDir.Data(), DataSets[i].Data(), suffix.Data()));

			TH1D* fHistClusterdEtaBeforeQA = (TH1D*) fHistClusterdEtadPhiBeforeQA->ProjectionX("fHistClusterdEtaBeforeQA",1,300);
			fHistClusterdEtaBeforeQA->GetXaxis()->SetRangeUser(-0.3,0.3);
			DrawPeriodQAHistoTH1(canvas,leftMargin,rightMargin,topMargin,bottomMargin,kFALSE,kFALSE,kFALSE,
								 fHistClusterdEtaBeforeQA," ","#Delta#eta_{Cluster - all Tracks}","#frac{d#it{N}}{d#Delta#eta}",0.9,1,
								 0.7,0.92,0.03,fCollisionSystem,plotDataSets[i],fClusters);
			SaveCanvasAndWriteHistogram(canvas, fHistClusterdEtaBeforeQA, Form("%s/dEta_allTracks_%s.%s", outputDir.Data(), DataSets[i].Data(), suffix.Data()));
			vecMatchingDeltaEtaPhi_allTracks[0].push_back(new TH1D(*fHistClusterdEtaBeforeQA));

			TH1D* fHistClusterdPhiBeforeQA = (TH1D*) fHistClusterdEtadPhiBeforeQA->ProjectionY("fHistClusterdPhiBeforeQA",1,300);
			fHistClusterdPhiBeforeQA->GetXaxis()->SetRangeUser(-0.3,0.3);
			DrawPeriodQAHistoTH1(canvas,leftMargin,rightMargin,topMargin,bottomMargin,kFALSE,kFALSE,kFALSE,
								 fHistClusterdPhiBeforeQA," ","#Delta#phi_{Cluster - all Tracks}","#frac{d#it{N}}{d#Delta#phi}",0.9,1,
								 0.7,0.92,0.03,fCollisionSystem,plotDataSets[i],fClusters);
			SaveCanvasAndWriteHistogram(canvas, fHistClusterdPhiBeforeQA, Form("%s/dPhi_allTracks_%s.%s", outputDir.Data(), DataSets[i].Data(), suffix.Data()));
			vecMatchingDeltaEtaPhi_allTracks[1].push_back(new TH1D(*fHistClusterdPhiBeforeQA));
		}else cout << "Info: Object |fHistClusterdEtadPhiBeforeQA| could not be found! Skipping Draw..." << endl;
	//-----------------------------------
		TH2D* fHistClusterdEtadPhiAfterQA = (TH2D*)CaloCutsContainer[i]->FindObject(Form("dEtaVsdPhi_afterClusterQA %s", fClusterCutSelection[i].Data()));
		if(fHistClusterdEtadPhiAfterQA){
			DrawPeriodQAHistoTH2(cvsQuadratic,0.12,0.12,topMargin,bottomMargin,kFALSE,kFALSE,kTRUE,
								fHistClusterdEtadPhiAfterQA,Form("%s - %s - %s",fCollisionSystem.Data(), plotDataSets[i].Data(), fClusters.Data()),
								 "#Delta#eta_{Cluster - unmatched Tracks}","#Delta#phi_{Cluster - unmatched Tracks}",1,1.2);
			SaveCanvasAndWriteHistogram(cvsQuadratic, fHistClusterdEtadPhiAfterQA, Form("%s/dEtaVsdPhi_unmatched_%s.%s", outputDir.Data(), DataSets[i].Data(), suffix.Data()));

			TH1D* fHistClusterdEtaAfterQA = (TH1D*) fHistClusterdEtadPhiAfterQA->ProjectionX("fHistClusterdEtaAfterQA",1,300);
			fHistClusterdEtaAfterQA->GetXaxis()->SetRangeUser(-0.3,0.3);
			DrawPeriodQAHistoTH1(canvas,leftMargin,rightMargin,topMargin,bottomMargin,kFALSE,kFALSE,kFALSE,
								 fHistClusterdEtaAfterQA," ","#Delta#eta_{Cluster - unmatched Tracks}","#frac{d#it{N}}{d#Delta#eta}",0.9,1,
								 0.7,0.92,0.03,fCollisionSystem,plotDataSets[i],fClusters);
			SaveCanvasAndWriteHistogram(canvas, fHistClusterdEtaAfterQA, Form("%s/dEta_unmatched_%s.%s", outputDir.Data(), DataSets[i].Data(), suffix.Data()));

			TH1D* fHistClusterdPhiAfterQA = (TH1D*) fHistClusterdEtadPhiAfterQA->ProjectionY("fHistClusterdPhiAfterQA",1,300);
			fHistClusterdPhiAfterQA->GetXaxis()->SetRangeUser(-0.3,0.3);
			DrawPeriodQAHistoTH1(canvas,leftMargin,rightMargin,topMargin,bottomMargin,kFALSE,kFALSE,kFALSE,
								 fHistClusterdPhiAfterQA," ","#Delta#phi_{Cluster - unmatched Tracks}","#frac{d#it{N}}{d#Delta#phi}",0.9,1,
								 0.7,0.92,0.03,fCollisionSystem,plotDataSets[i],fClusters);
			SaveCanvasAndWriteHistogram(canvas, fHistClusterdPhiAfterQA, Form("%s/dPhi_unmatched_%s.%s", outputDir.Data(), DataSets[i].Data(), suffix.Data()));
		}else cout << "Info: Object |fHistClusterdEtadPhiAfterQA| could not be found! Skipping Draw..." << endl;
	//-----------------------------------
		if(fHistClusterdEtadPhiBeforeQA && fHistClusterdEtadPhiAfterQA){
			TH2D* fHistClusterdEtadPhiMatchedAfterQA = (TH2D*) fHistClusterdEtadPhiBeforeQA->Clone();
			fHistClusterdEtadPhiMatchedAfterQA->Add(fHistClusterdEtadPhiAfterQA,-1);
			DrawPeriodQAHistoTH2(cvsQuadratic,0.12,0.12,topMargin,bottomMargin,kFALSE,kFALSE,kTRUE,
								fHistClusterdEtadPhiMatchedAfterQA,Form("%s - %s - %s",fCollisionSystem.Data(), plotDataSets[i].Data(), fClusters.Data()),
								 "#Delta#eta_{Cluster - matched Tracks}","#Delta#phi_{Cluster - matched Tracks}",1,1.2);
			SaveCanvasAndWriteHistogram(cvsQuadratic, fHistClusterdEtadPhiMatchedAfterQA, Form("%s/dEtaVsdPhi_matched_%s.%s", outputDir.Data(), DataSets[i].Data(), suffix.Data()));

			TGaxis::SetExponentOffset(-0.04, -0.04, "x");
			TH1D* fHistClusterdEtaMatchedAfterQA = (TH1D*) fHistClusterdEtadPhiMatchedAfterQA->ProjectionX("fHistClusterdEtaMatchedAfterQA",1,300);
			GetMinMaxBin(fHistClusterdEtaMatchedAfterQA,minB,maxB);
			fHistClusterdEtaMatchedAfterQA->GetXaxis()->SetRange(minB-1,maxB+1);
			DrawPeriodQAHistoTH1(canvas,leftMargin,rightMargin,topMargin,bottomMargin,kFALSE,kFALSE,kFALSE,
								 fHistClusterdEtaMatchedAfterQA," ","#Delta#eta_{Cluster - matched Tracks}","#frac{d#it{N}}{d#Delta#eta}",0.9,1,
								 0.7,0.92,0.03,fCollisionSystem,plotDataSets[i],fClusters);
			SaveCanvasAndWriteHistogram(canvas, fHistClusterdEtaMatchedAfterQA, Form("%s/dEta_matched_%s.%s", outputDir.Data(), DataSets[i].Data(), suffix.Data()));
			vecMatchingDeltaEtaPhi_matched[0].push_back(new TH1D(*fHistClusterdEtaMatchedAfterQA));

			TH1D* fHistClusterdPhiMatchedAfterQA = (TH1D*) fHistClusterdEtadPhiMatchedAfterQA->ProjectionY("fHistClusterdPhiMatchedAfterQA",1,300);
			GetMinMaxBin(fHistClusterdPhiMatchedAfterQA,minB,maxB);
			fHistClusterdPhiMatchedAfterQA->GetXaxis()->SetRange(minB-1,maxB+1);
			DrawPeriodQAHistoTH1(canvas,leftMargin,rightMargin,topMargin,bottomMargin,kFALSE,kFALSE,kFALSE,
								 fHistClusterdPhiMatchedAfterQA," ","#Delta#phi_{Cluster - matched Tracks}","#frac{d#it{N}}{d#Delta#phi}",0.9,1,
								 0.7,0.92,0.03,fCollisionSystem,plotDataSets[i],fClusters);
			SaveCanvasAndWriteHistogram(canvas, fHistClusterdPhiMatchedAfterQA, Form("%s/dPhi_matched_%s.%s", outputDir.Data(), DataSets[i].Data(), suffix.Data()));
			TGaxis::SetExponentOffset(0, 0, "x");
			vecMatchingDeltaEtaPhi_matched[1].push_back(new TH1D(*fHistClusterdPhiMatchedAfterQA));
		}
	//-----------------------------------
		TH1D* fHistDistanceTrackToClusterBeforeQA = (TH1D*)CaloCutsContainer[i]->FindObject(Form("DistanceToTrack_beforeClusterQA %s", fClusterCutSelection[i].Data()));
		if(fHistDistanceTrackToClusterBeforeQA){
			AdjustHistRange(fHistDistanceTrackToClusterBeforeQA,5,5,kTRUE,1,1.);
			DrawPeriodQAHistoTH1(canvas,leftMargin,rightMargin,topMargin,0.15,kFALSE,kTRUE,kFALSE,
								 fHistDistanceTrackToClusterBeforeQA," ","r = #sqrt{#Delta#eta_{Cluster - all Tracks}^{2}+#Delta#phi_{Cluster - all Tracks}^{2}}","#frac{d#it{N}}{d#it{r}}",1.3,1,
								 0.7,0.92,0.03,fCollisionSystem,plotDataSets[i],fClusters);
			SaveCanvasAndWriteHistogram(canvas, fHistDistanceTrackToClusterBeforeQA, Form("%s/DistanceToTrack_%s_beforeClusterQA.%s", outputDir.Data(), DataSets[i].Data(), suffix.Data()));
		}else cout << "Info: Object |fHistDistanceTrackToClusterBeforeQA| could not be found! Skipping Draw..." << endl;
	//-----------------------------------
		TH1D* fHistDistanceTrackToClusterAfterQA = (TH1D*)CaloCutsContainer[i]->FindObject(Form("DistanceToTrack_afterClusterQA %s", fClusterCutSelection[i].Data()));
		if(fHistDistanceTrackToClusterAfterQA){
			AdjustHistRange(fHistDistanceTrackToClusterAfterQA,5,5,kTRUE,1,1.);
			DrawPeriodQAHistoTH1(canvas,leftMargin,rightMargin,topMargin,0.15,kFALSE,kTRUE,kFALSE,
								 fHistDistanceTrackToClusterAfterQA," ","r = #sqrt{#Delta#eta_{Cluster - unmatched Tracks}^{2}+#Delta#phi_{Cluster - unmatched Tracks}^{2}}","#frac{d#it{N}}{d#it{r}}",1.3,1,
								 0.7,0.92,0.03,fCollisionSystem,plotDataSets[i],fClusters);
			SaveCanvasAndWriteHistogram(canvas, fHistDistanceTrackToClusterAfterQA, Form("%s/DistanceToTrack_unmatched_%s_afterClusterQA.%s", outputDir.Data(), DataSets[i].Data(), suffix.Data()));
		}else cout << "Info: Object |fHistDistanceTrackToClusterAfterQA| could not be found! Skipping Draw..." << endl;
	//-----------------------------------
		if(fHistDistanceTrackToClusterBeforeQA && fHistDistanceTrackToClusterAfterQA){
			TH1D* fHistDistanceTrackToClusterMatchedAfterQA = (TH1D*) fHistDistanceTrackToClusterBeforeQA->Clone();
			fHistDistanceTrackToClusterMatchedAfterQA->Add(fHistDistanceTrackToClusterAfterQA, -1);
			AdjustHistRange(fHistDistanceTrackToClusterMatchedAfterQA,5,5,kTRUE,1,1.);
			fHistDistanceTrackToClusterMatchedAfterQA->GetXaxis()->SetRangeUser(0,0.2);
			DrawPeriodQAHistoTH1(canvas,leftMargin,rightMargin,topMargin,0.15,kFALSE,kTRUE,kFALSE,
								 fHistDistanceTrackToClusterMatchedAfterQA," ","r = #sqrt{#Delta#eta_{Cluster - matched Tracks}^{2}+#Delta#phi_{Cluster - matched Tracks}^{2}}","#frac{d#it{N}}{d#it{r}}",1.3,1,
								 0.7,0.92,0.03,fCollisionSystem,plotDataSets[i],fClusters);
			SaveCanvasAndWriteHistogram(canvas, fHistDistanceTrackToClusterMatchedAfterQA, Form("%s/DistanceToTrack_matched_%s_afterClusterQA.%s", outputDir.Data(), DataSets[i].Data(), suffix.Data()));
		}
	//-----------------------------------
		TH2D* fHistClusterdEtadPtBeforeQA = (TH2D*)CaloCutsContainer[i]->FindObject(Form("dEtaVsPt_beforeClusterQA %s", fClusterCutSelection[i].Data()));
		if(fHistClusterdEtadPtBeforeQA){
			TH1D* fHistClusterdEtadPtBeforeQAPt = (TH1D*) fHistClusterdEtadPtBeforeQA->ProjectionY("dEtaVsPtOnPt_beforeClusterQA",1,300);
			GetMinMaxBin(fHistClusterdEtadPtBeforeQAPt,minB,maxB);
			fHistClusterdEtadPtBeforeQA->GetYaxis()->SetRange(minB,maxB+5);
			DrawPeriodQAHistoTH2(canvas,leftMargin,0.1,topMargin,bottomMargin,kFALSE,kFALSE,kTRUE,
								fHistClusterdEtadPtBeforeQA," ",
								 "#Delta#eta_{Cluster - all Tracks}","#it{p}_{T} (GeV/#it{c})",1,1,
								 0.65,0.92,0.03,fCollisionSystem,plotDataSets[i],fClusters);
			SaveCanvasAndWriteHistogram(canvas, fHistClusterdEtadPtBeforeQA, Form("%s/dEtaVsPt_%s_beforeClusterQA.%s", outputDir.Data(), DataSets[i].Data(), suffix.Data()));
		}else cout << "Info: Object |fHistClusterdEtadPtBeforeQA| could not be found! Skipping Draw..." << endl;
	//-----------------------------------
		TH2D* fHistClusterdPhidPtBeforeQA = (TH2D*)CaloCutsContainer[i]->FindObject(Form("dPhiVsPt_beforeClusterQA %s", fClusterCutSelection[i].Data()));
		if(fHistClusterdPhidPtBeforeQA){
			TH1D* fHistClusterdPhidPtBeforeQAPt = (TH1D*) fHistClusterdPhidPtBeforeQA->ProjectionY("dPhiVsPtOnPt_beforeClusterQA",1,300);
			GetMinMaxBin(fHistClusterdPhidPtBeforeQAPt,minB,maxB);
			fHistClusterdEtadPtBeforeQA->GetYaxis()->SetRange(minB,maxB+5);
			DrawPeriodQAHistoTH2(canvas,leftMargin,0.1,topMargin,bottomMargin,kFALSE,kFALSE,kTRUE,
								fHistClusterdPhidPtBeforeQA," ",
								 "#Delta#phi_{Cluster - all Tracks}","#it{p}_{T} (GeV/#it{c})",1,1,
								 0.65,0.92,0.03,fCollisionSystem,plotDataSets[i],fClusters);
			SaveCanvasAndWriteHistogram(canvas, fHistClusterdPhidPtBeforeQA, Form("%s/dPhiVsPt_%s_beforeClusterQA.%s", outputDir.Data(), DataSets[i].Data(), suffix.Data()));
		}else cout << "Info: Object |fHistClusterdPhidPtBeforeQA| could not be found! Skipping Draw..." << endl;
	//-----------------------------------
		TH2D* fHistClusterEM02BeforeQA = (TH2D*)CaloCutsContainer[i]->FindObject(Form("EVsM02_beforeClusterQA %s", fClusterCutSelection[i].Data()));
		if(fHistClusterEM02BeforeQA){
			DrawPeriodQAHistoTH2(canvas,leftMargin,0.1,topMargin,bottomMargin,kFALSE,kFALSE,kTRUE,
								fHistClusterEM02BeforeQA," ",
								 "E (GeV)","#lambda_{0}^{2}",1,1,
								 0.65,0.92,0.03,fCollisionSystem,plotDataSets[i],fClusters);
			SaveCanvasAndWriteHistogram(canvas, fHistClusterEM02BeforeQA, Form("%s/EVsM02_%s_beforeClusterQA.%s", outputDir.Data(), DataSets[i].Data(), suffix.Data()));
		}else cout << "Info: Object |fHistClusterEM02BeforeQA| could not be found! Skipping Draw..." << endl;
	//-----------------------------------
		TH2D* fHistClusterEM02AfterQA = (TH2D*)CaloCutsContainer[i]->FindObject(Form("EVsM02_afterClusterQA %s", fClusterCutSelection[i].Data()));
		if(fHistClusterEM02AfterQA){
			DrawPeriodQAHistoTH2(canvas,leftMargin,0.1,topMargin,bottomMargin,kFALSE,kFALSE,kTRUE,
								fHistClusterEM02AfterQA," ",
								 "E (GeV)","#lambda_{0}^{2}",1,1,
								 0.65,0.92,0.03,fCollisionSystem,plotDataSets[i],fClusters);
			SaveCanvasAndWriteHistogram(canvas, fHistClusterEM02AfterQA, Form("%s/EVsM02_%s_afterClusterQA.%s", outputDir.Data(), DataSets[i].Data(), suffix.Data()));
		}else cout << "Info: Object |fHistClusterEM02AfterQA| could not be found! Skipping Draw..." << endl;
	//-----------------------------------
		TH2D* fHistClusterM20M02BeforeQA = (TH2D*)CaloCutsContainer[i]->FindObject(Form("M20VsM02_beforeClusterQA %s", fClusterCutSelection[i].Data()));
		if(fHistClusterM20M02BeforeQA){
			fHistClusterM20M02BeforeQA->GetXaxis()->SetDecimals();
			fHistClusterM20M02BeforeQA->GetXaxis()->SetLabelOffset(0.01);
			fHistClusterM20M02BeforeQA->GetXaxis()->SetRangeUser(0,0.55);
			fHistClusterM20M02BeforeQA->GetYaxis()->SetLabelOffset(0.01);
			fHistClusterM20M02BeforeQA->GetYaxis()->SetRangeUser(0.05,0.55);
			DrawPeriodQAHistoTH2(cvsQuadratic,0.12,0.12,topMargin,bottomMargin,kFALSE,kFALSE,kTRUE,
								fHistClusterM20M02BeforeQA," ",
								 "#lambda_{1}^{2}","#lambda_{0}^{2}",1,1.2,
								 0.5,0.25,0.03,fCollisionSystem,plotDataSets[i],fClusters);
			SaveCanvasAndWriteHistogram(cvsQuadratic, fHistClusterM20M02BeforeQA, Form("%s/M20VsM02_all_%s.%s", outputDir.Data(), DataSets[i].Data(), suffix.Data()));
		}else cout << "Info: Object |fHistClusterM20M02BeforeQA| could not be found! Skipping Draw..." << endl;
	//-----------------------------------
		TH2D* fHistClusterM20M02AfterQA = (TH2D*)CaloCutsContainer[i]->FindObject(Form("M20VsM02_afterClusterQA %s", fClusterCutSelection[i].Data()));
		if(fHistClusterM20M02AfterQA){
			fHistClusterM20M02AfterQA->GetXaxis()->SetDecimals();
			fHistClusterM20M02AfterQA->GetXaxis()->SetLabelOffset(0.01);
			fHistClusterM20M02AfterQA->GetXaxis()->SetRangeUser(0,0.55);
			fHistClusterM20M02AfterQA->GetYaxis()->SetLabelOffset(0.01);
			fHistClusterM20M02AfterQA->GetYaxis()->SetRangeUser(0.05,0.55);
			DrawPeriodQAHistoTH2(cvsQuadratic,0.12,0.12,topMargin,bottomMargin,kFALSE,kFALSE,kTRUE,
								fHistClusterM20M02AfterQA," ",
								 "#lambda_{1}^{2}","#lambda_{0}^{2}",1,1.2,
								 0.5,0.25,0.03,fCollisionSystem,plotDataSets[i],fClusters);
			SaveCanvasAndWriteHistogram(cvsQuadratic, fHistClusterM20M02AfterQA, Form("%s/M20VsM02_unmatched_%s.%s", outputDir.Data(), DataSets[i].Data(), suffix.Data()));
		}else cout << "Info: Object |fHistClusterM20M02AfterQA| could not be found! Skipping Draw..." << endl;
	//-----------------------------------
		if(fHistClusterM20M02BeforeQA && fHistClusterM20M02AfterQA){
			TH2D* fHistClusterM20M02MatchedAfterQA = (TH2D*) fHistClusterM20M02BeforeQA->Clone();
			fHistClusterM20M02MatchedAfterQA->Add(fHistClusterM20M02AfterQA,-1);
			fHistClusterM20M02MatchedAfterQA->GetXaxis()->SetDecimals();
			fHistClusterM20M02MatchedAfterQA->GetXaxis()->SetLabelOffset(0.01);
			fHistClusterM20M02MatchedAfterQA->GetXaxis()->SetRangeUser(0,0.55);
			fHistClusterM20M02MatchedAfterQA->GetYaxis()->SetLabelOffset(0.01);
			fHistClusterM20M02MatchedAfterQA->GetYaxis()->SetRangeUser(0.05,0.55);
			DrawPeriodQAHistoTH2(cvsQuadratic,0.12,0.12,topMargin,bottomMargin,kFALSE,kFALSE,kTRUE,
								fHistClusterM20M02MatchedAfterQA," ",
								 "#lambda_{1}^{2}","#lambda_{0}^{2}",1,1.2,
								 0.5,0.25,0.03,fCollisionSystem,plotDataSets[i],fClusters);
			SaveCanvasAndWriteHistogram(cvsQuadratic, fHistClusterM20M02MatchedAfterQA, Form("%s/M20VsM02_matched_%s.%s", outputDir.Data(), DataSets[i].Data(), suffix.Data()));
		}
	//-----------------------------------
	//-----------------------------------
		for(Int_t iCharge=0;iCharge<2;iCharge++){
			TH2D* fHistClusterdEtadPhiTracksBeforeQA = (TH2D*)CaloCutsContainer[i]->FindObject(Form("dEtaVsdPhi_%sTracks_beforeClusterQA %s", charge[iCharge].Data(),fClusterCutSelection[i].Data()));
			if(fHistClusterdEtadPhiTracksBeforeQA){
				DrawPeriodQAHistoTH2(cvsQuadratic,0.12,0.12,topMargin,bottomMargin,kFALSE,kFALSE,kTRUE,
									fHistClusterdEtadPhiTracksBeforeQA,Form("%s - %s - %s",fCollisionSystem.Data(), plotDataSets[i].Data(), fClusters.Data()),
									 Form("#Delta#eta_{Cluster - %s. Tracks}", charge[iCharge].Data()),Form("#Delta#phi_{Cluster - %s. Tracks}", charge[iCharge].Data()),1,1.2);
				SaveCanvasAndWriteHistogram(cvsQuadratic, fHistClusterdEtadPhiTracksBeforeQA, Form("%s/dEtaVsdPhi_all_%sTracks_%s.%s", outputDir.Data(), charge[iCharge].Data(), DataSets[i].Data(), suffix.Data()));

				TH1D* fHistClusterdEtaBeforeQA = (TH1D*) fHistClusterdEtadPhiTracksBeforeQA->ProjectionX(Form("fHistClusterdEta%sBeforeQA", charge[iCharge].Data()),1,300);
				fHistClusterdEtaBeforeQA->GetXaxis()->SetRangeUser(-0.3,0.3);
				DrawPeriodQAHistoTH1(canvas,leftMargin,rightMargin,topMargin,bottomMargin,kFALSE,kFALSE,kFALSE,
									 fHistClusterdEtaBeforeQA," ",Form("#Delta#eta_{Cluster - %s. Tracks}", charge[iCharge].Data()),"#frac{d#it{N}}{d#Delta#eta}",0.9,1,
									 0.7,0.92,0.03,fCollisionSystem,plotDataSets[i],fClusters);
				SaveCanvasAndWriteHistogram(canvas, fHistClusterdEtaBeforeQA, Form("%s/dEta_all_%sTracks_%s.%s", outputDir.Data(), charge[iCharge].Data(), DataSets[i].Data(), suffix.Data()));
				vecMatchingDeltaEtaPhiTracksAll[0][iCharge].push_back(new TH1D(*fHistClusterdEtaBeforeQA));

				TH1D* fHistClusterdPhiBeforeQA = (TH1D*) fHistClusterdEtadPhiTracksBeforeQA->ProjectionY(Form("fHistClusterdPhi%sBeforeQA", charge[iCharge].Data()),1,300);
				fHistClusterdPhiBeforeQA->GetXaxis()->SetRangeUser(-0.3,0.3);
				DrawPeriodQAHistoTH1(canvas,leftMargin,rightMargin,topMargin,bottomMargin,kFALSE,kFALSE,kFALSE,
									 fHistClusterdPhiBeforeQA," ",Form("#Delta#phi_{Cluster - %s. Tracks}", charge[iCharge].Data()),"#frac{d#it{N}}{d#Delta#phi}",0.9,1,
									 0.7,0.92,0.03,fCollisionSystem,plotDataSets[i],fClusters);
				SaveCanvasAndWriteHistogram(canvas, fHistClusterdPhiBeforeQA, Form("%s/dPhi_all_%sTracks_%s.%s", outputDir.Data(), charge[iCharge].Data(), DataSets[i].Data(), suffix.Data()));
				vecMatchingDeltaEtaPhiTracksAll[1][iCharge].push_back(new TH1D(*fHistClusterdPhiBeforeQA));
			}else cout << "Info: Object |fHistClusterdEtadPhiTracksBeforeQA| could not be found! Skipping Draw..." << endl;
		//-----------------------------------
			TH2D* fHistClusterdEtadPhiTracksAfterQA = (TH2D*)CaloCutsContainer[i]->FindObject(Form("dEtaVsdPhi_%sTracks_afterClusterQA %s", charge[iCharge].Data(),fClusterCutSelection[i].Data()));
			if(fHistClusterdEtadPhiTracksAfterQA){
				DrawPeriodQAHistoTH2(cvsQuadratic,0.12,0.12,topMargin,bottomMargin,kFALSE,kFALSE,kTRUE,
									fHistClusterdEtadPhiTracksAfterQA,Form("%s - %s - %s",fCollisionSystem.Data(), plotDataSets[i].Data(), fClusters.Data()),
									 Form("#Delta#eta_{Cluster - unmatched %s. Tracks}", charge[iCharge].Data()),Form("#Delta#phi_{Cluster - unmatched %s. Tracks}", charge[iCharge].Data()),1,1.2);
				SaveCanvasAndWriteHistogram(cvsQuadratic, fHistClusterdEtadPhiTracksAfterQA, Form("%s/dEtaVsdPhi_unmatched_%sTracks_%s.%s", outputDir.Data(), charge[iCharge].Data(), DataSets[i].Data(), suffix.Data()));

				TH1D* fHistClusterdEtaAfterQA = (TH1D*) fHistClusterdEtadPhiTracksAfterQA->ProjectionX(Form("fHistClusterdEta%sAfterQA", charge[iCharge].Data()),1,300);
				fHistClusterdEtaAfterQA->GetXaxis()->SetRangeUser(-0.3,0.3);
				DrawPeriodQAHistoTH1(canvas,leftMargin,rightMargin,topMargin,bottomMargin,kFALSE,kFALSE,kFALSE,
									 fHistClusterdEtaAfterQA," ",Form("#Delta#eta_{Cluster - unmatched %s. Tracks}", charge[iCharge].Data()),"#frac{d#it{N}}{d#Delta#eta}",0.9,1,
									 0.7,0.92,0.03,fCollisionSystem,plotDataSets[i],fClusters);
				SaveCanvasAndWriteHistogram(canvas, fHistClusterdEtaAfterQA, Form("%s/dEta_unmatched_%sTracks_%s.%s", outputDir.Data(), charge[iCharge].Data(), DataSets[i].Data(), suffix.Data()));

				TH1D* fHistClusterdPhiAfterQA = (TH1D*) fHistClusterdEtadPhiTracksAfterQA->ProjectionY(Form("fHistClusterdPhi%sAfterQA", charge[iCharge].Data()),1,300);
				fHistClusterdPhiAfterQA->GetXaxis()->SetRangeUser(-0.3,0.3);
				DrawPeriodQAHistoTH1(canvas,leftMargin,rightMargin,topMargin,bottomMargin,kFALSE,kFALSE,kFALSE,
									 fHistClusterdPhiAfterQA," ",Form("#Delta#phi_{Cluster - unmatched %s. Tracks}", charge[iCharge].Data()),"#frac{d#it{N}}{d#Delta#phi}",0.9,1,
									 0.7,0.92,0.03,fCollisionSystem,plotDataSets[i],fClusters);
				SaveCanvasAndWriteHistogram(canvas, fHistClusterdPhiAfterQA, Form("%s/dPhi_unmatched_%sTracks_%s.%s", outputDir.Data(), charge[iCharge].Data(), DataSets[i].Data(), suffix.Data()));
			}else cout << "Info: Object |fHistClusterdEtadPhiTracksAfterQA| could not be found! Skipping Draw..." << endl;
		//-----------------------------------
			if(fHistClusterdEtadPhiTracksBeforeQA && fHistClusterdEtadPhiTracksAfterQA){
				TH2D* fHistClusterdEtadPhiTracksMatchedAfterQA = (TH2D*) fHistClusterdEtadPhiTracksBeforeQA->Clone();
				fHistClusterdEtadPhiTracksMatchedAfterQA->Add(fHistClusterdEtadPhiTracksAfterQA,-1);
				DrawPeriodQAHistoTH2(cvsQuadratic,0.12,0.12,topMargin,bottomMargin,kFALSE,kFALSE,kTRUE,
									fHistClusterdEtadPhiTracksMatchedAfterQA,Form("%s - %s - %s",fCollisionSystem.Data(), plotDataSets[i].Data(), fClusters.Data()),
									 Form("#Delta#eta_{Cluster - matched %s. Tracks}", charge[iCharge].Data()),Form("#Delta#phi_{Cluster - matched %s. Tracks}", charge[iCharge].Data()),1,1.2);
				SaveCanvasAndWriteHistogram(cvsQuadratic, fHistClusterdEtadPhiTracksMatchedAfterQA, Form("%s/dEtaVsdPhi_matched_%sTracks_%s.%s", outputDir.Data(), charge[iCharge].Data(), DataSets[i].Data(), suffix.Data()));

				TH1D* fHistClusterdEtaMatchedAfterQA = (TH1D*) fHistClusterdEtadPhiTracksMatchedAfterQA->ProjectionX(Form("fHistClusterdEta%sAfterQA", charge[iCharge].Data()),1,300);
				GetMinMaxBin(fHistClusterdEtaMatchedAfterQA,minB,maxB);
				fHistClusterdEtaMatchedAfterQA->GetXaxis()->SetRange(minB-1,maxB+1);
				DrawPeriodQAHistoTH1(canvas,leftMargin,rightMargin,topMargin,bottomMargin,kFALSE,kFALSE,kFALSE,
									 fHistClusterdEtaMatchedAfterQA," ",Form("#Delta#eta_{Cluster - matched %s. Tracks}", charge[iCharge].Data()),"#frac{d#it{N}}{d#Delta#eta}",0.9,1,
									 0.7,0.92,0.03,fCollisionSystem,plotDataSets[i],fClusters);
				SaveCanvasAndWriteHistogram(canvas, fHistClusterdEtaMatchedAfterQA, Form("%s/dEta_matched_%sTracks_%s.%s", outputDir.Data(), charge[iCharge].Data(), DataSets[i].Data(), suffix.Data()));
				vecMatchingDeltaEtaPhiTracksMatched[0][iCharge].push_back(new TH1D(*fHistClusterdEtaMatchedAfterQA));

				TH1D* fHistClusterdPhiMatchedAfterQA = (TH1D*) fHistClusterdEtadPhiTracksMatchedAfterQA->ProjectionY(Form("fHistClusterdPhi%sAfterQA", charge[iCharge].Data()),1,300);
				GetMinMaxBin(fHistClusterdPhiMatchedAfterQA,minB,maxB);
				fHistClusterdPhiMatchedAfterQA->GetXaxis()->SetRange(minB-1,maxB+1);
				DrawPeriodQAHistoTH1(canvas,leftMargin,rightMargin,topMargin,bottomMargin,kFALSE,kFALSE,kFALSE,
									 fHistClusterdPhiMatchedAfterQA," ",Form("#Delta#phi_{Cluster - matched %s. Tracks}", charge[iCharge].Data()),"#frac{d#it{N}}{d#Delta#phi}",0.9,1,
									 0.7,0.92,0.03,fCollisionSystem,plotDataSets[i],fClusters);
				SaveCanvasAndWriteHistogram(canvas, fHistClusterdPhiMatchedAfterQA, Form("%s/dPhi_matched_%sTracks_%s.%s", outputDir.Data(), charge[iCharge].Data(), DataSets[i].Data(), suffix.Data()));
				vecMatchingDeltaEtaPhiTracksMatched[1][iCharge].push_back(new TH1D(*fHistClusterdPhiMatchedAfterQA));
			}
		//-----------------------------------
			TH2D* fHistClusterdEtadPhiTracksP_000_075BeforeQA = (TH2D*)CaloCutsContainer[i]->FindObject(Form("dEtaVsdPhi_%sTracks_P<0.75_beforeClusterQA %s", charge[iCharge].Data(),fClusterCutSelection[i].Data()));
			if(fHistClusterdEtadPhiTracksP_000_075BeforeQA){
				DrawPeriodQAHistoTH2(cvsQuadratic,0.12,0.12,topMargin,bottomMargin,kFALSE,kFALSE,kTRUE,
									fHistClusterdEtadPhiTracksP_000_075BeforeQA,Form("%s - %s - %s",fCollisionSystem.Data(), plotDataSets[i].Data(), fClusters.Data()),
									 Form("#Delta#eta_{Cluster - %s. Tracks with #it{p}_{T}<0.75 GeV/#it{c}}", charge[iCharge].Data()),Form("#Delta#phi_{Cluster - %s. Tracks with #it{p}_{T}<0.75 GeV/#it{c}}", charge[iCharge].Data()),1,1.2);
				SaveCanvasAndWriteHistogram(cvsQuadratic, fHistClusterdEtadPhiTracksP_000_075BeforeQA, Form("%s/dEtaVsdPhi_%sTracks_000_075_%s.%s", outputDir.Data(), charge[iCharge].Data(), DataSets[i].Data(), suffix.Data()));
				vecMatchingDeltaEtaPhiTracksAllPt[0][iCharge].push_back(new TH2D(*fHistClusterdEtadPhiTracksP_000_075BeforeQA));
			}else cout << "Info: Object |fHistClusterdEtadPhiTracksP_000_075BeforeQA| could not be found! Skipping Draw..." << endl;

			TH2D* fHistClusterdEtadPhiTracksP_075_125BeforeQA = (TH2D*)CaloCutsContainer[i]->FindObject(Form("dEtaVsdPhi_%sTracks_0.75<P<1.25_beforeClusterQA %s", charge[iCharge].Data(),fClusterCutSelection[i].Data()));
			if(fHistClusterdEtadPhiTracksP_075_125BeforeQA){
				DrawPeriodQAHistoTH2(cvsQuadratic,0.12,0.12,topMargin,bottomMargin,kFALSE,kFALSE,kTRUE,
									fHistClusterdEtadPhiTracksP_075_125BeforeQA,Form("%s - %s - %s",fCollisionSystem.Data(), plotDataSets[i].Data(), fClusters.Data()),
									 Form("#Delta#eta_{Cluster - %s. Tracks with 0.75<#it{p}_{T}<1.25 GeV/#it{c}}", charge[iCharge].Data()),Form("#Delta#phi_{Cluster - %s. Tracks with 0.75<#it{p}_{T}<1.25 GeV/#it{c}}", charge[iCharge].Data()),1,1.2);
				SaveCanvasAndWriteHistogram(cvsQuadratic, fHistClusterdEtadPhiTracksP_075_125BeforeQA, Form("%s/dEtaVsdPhi_%sTracks_075_125_%s.%s", outputDir.Data(), charge[iCharge].Data(), DataSets[i].Data(), suffix.Data()));
				vecMatchingDeltaEtaPhiTracksAllPt[1][iCharge].push_back(new TH2D(*fHistClusterdEtadPhiTracksP_075_125BeforeQA));
			}else cout << "Info: Object |fHistClusterdEtadPhiTracksP_075_125BeforeQA| could not be found! Skipping Draw..." << endl;

			TH2D* fHistClusterdEtadPhiTracksP_125_999BeforeQA = (TH2D*)CaloCutsContainer[i]->FindObject(Form("dEtaVsdPhi_%sTracks_P>1.25_beforeClusterQA %s", charge[iCharge].Data(),fClusterCutSelection[i].Data()));
			if(fHistClusterdEtadPhiTracksP_125_999BeforeQA){
				DrawPeriodQAHistoTH2(cvsQuadratic,0.12,0.12,topMargin,bottomMargin,kFALSE,kFALSE,kTRUE,
									fHistClusterdEtadPhiTracksP_125_999BeforeQA,Form("%s - %s - %s",fCollisionSystem.Data(), plotDataSets[i].Data(), fClusters.Data()),
									 Form("#Delta#eta_{Cluster - %s. Tracks with #it{p}_{T}>1.25 GeV/#it{c}}", charge[iCharge].Data()),Form("#Delta#phi_{Cluster - %s. Tracks with #it{p}_{T}>1.25 GeV/#it{c}}", charge[iCharge].Data()),1,1.2);
				SaveCanvasAndWriteHistogram(cvsQuadratic, fHistClusterdEtadPhiTracksP_125_999BeforeQA, Form("%s/dEtaVsdPhi_%sTracks_125_999_%s.%s", outputDir.Data(), charge[iCharge].Data(), DataSets[i].Data(), suffix.Data()));
				vecMatchingDeltaEtaPhiTracksAllPt[2][iCharge].push_back(new TH2D(*fHistClusterdEtadPhiTracksP_125_999BeforeQA));
			}else cout << "Info: Object |fHistClusterdEtadPhiTracksP_125_999BeforeQA| could not be found! Skipping Draw..." << endl;
		//-----------------------------------
		}
	//-----------------------------------
	//-----------------------------------
		TGaxis::SetExponentOffset(-0.06, -0.04, "x");
		TH1D* fHistClusterCellIDsBeforeQA = (TH1D*)CaloExtQAContainer[i]->FindObject(Form("ClusterIncludedCells_beforeClusterQA %s", fClusterCutSelection[i].Data()));
		if(fHistClusterCellIDsBeforeQA){
			fHistClusterCellIDsBeforeQA->GetXaxis()->SetRangeUser(0,nCaloCells);
			DrawPeriodQAHistoTH1(canvas,leftMargin,rightMargin,topMargin,bottomMargin,kFALSE,kTRUE,kFALSE,
								 fHistClusterCellIDsBeforeQA,Form("%s - %s - %s clusters",fCollisionSystem.Data(), plotDataSets[i].Data(), calo.Data()),"CellID in all Clusters","#frac{d#it{N}}{d#it{CellID}}",1,1);
			SaveCanvasAndWriteHistogram(canvas, fHistClusterCellIDsBeforeQA, Form("%s/ClusterIncludedCells_%s_beforeClusterQA.%s", outputDir.Data(), DataSets[i].Data(), suffix.Data()));
		}
	//-----------------------------------
		TH1D* fHistClusterCellIDsAfterQA = (TH1D*)CaloExtQAContainer[i]->FindObject(Form("ClusterIncludedCells_afterClusterQA %s", fClusterCutSelection[i].Data()));
		if(fHistClusterCellIDsAfterQA){
			fHistClusterCellIDsAfterQA->GetXaxis()->SetRangeUser(0,nCaloCells);
			DrawPeriodQAHistoTH1(canvas,leftMargin,rightMargin,topMargin,bottomMargin,kFALSE,kTRUE,kFALSE,
								 fHistClusterCellIDsAfterQA,Form("%s - %s - %s clusters",fCollisionSystem.Data(), plotDataSets[i].Data(), calo.Data()),"Cell ID in accepted Clusters","#frac{d#it{N}}{d#it{CellID}}",1,1);
			SaveCanvasAndWriteHistogram(canvas, fHistClusterCellIDsAfterQA, Form("%s/ClusterIncludedCells_%s_afterClusterQA.%s", outputDir.Data(), DataSets[i].Data(), suffix.Data()));
			vecClusterIncludedCells.push_back(new TH1D(*fHistClusterCellIDsAfterQA));
		}
	//-----------------------------------
		TH1D* fHistClusterCellEFracBeforeQA = (TH1D*)CaloExtQAContainer[i]->FindObject(Form("ClusterEnergyFracCells_beforeClusterQA %s", fClusterCutSelection[i].Data()));
		if(fHistClusterCellEFracBeforeQA){
			fHistClusterCellEFracBeforeQA->Sumw2();
			fHistClusterCellIDsBeforeQA->Sumw2();
			fHistClusterCellEFracBeforeQA->Divide(fHistClusterCellIDsBeforeQA);
			fHistClusterCellEFracBeforeQA->GetXaxis()->SetRangeUser(0,nCaloCells);
			fHistClusterCellEFracBeforeQA->GetYaxis()->SetRangeUser(0,1);
			DrawPeriodQAHistoTH1(canvas,leftMargin,rightMargin,topMargin,bottomMargin,kFALSE,kFALSE,kFALSE,
								 fHistClusterCellEFracBeforeQA,Form("%s - %s - %s clusters",fCollisionSystem.Data(), plotDataSets[i].Data(), calo.Data()),"Energy Fraction of CellID in all Clusters","#frac{d#it{N}}{d#it{CellID}}",1,1);
			SaveCanvasAndWriteHistogram(canvas, fHistClusterCellEFracBeforeQA, Form("%s/ClusterEnergyFracCells_%s_beforeClusterQA.%s", outputDir.Data(), DataSets[i].Data(), suffix.Data()));
		}
	//-----------------------------------
		TH1D* fHistClusterCellEFracAfterQA = (TH1D*)CaloExtQAContainer[i]->FindObject(Form("ClusterEnergyFracCells_afterClusterQA %s", fClusterCutSelection[i].Data()));
		if(fHistClusterCellEFracAfterQA){
			fHistClusterCellEFracAfterQA->Sumw2();
			fHistClusterCellIDsAfterQA->Sumw2();
			fHistClusterCellEFracAfterQA->Divide(fHistClusterCellIDsAfterQA);
			fHistClusterCellEFracAfterQA->GetXaxis()->SetRangeUser(0,nCaloCells);
			fHistClusterCellEFracAfterQA->GetYaxis()->SetRangeUser(0,1);
			DrawPeriodQAHistoTH1(canvas,leftMargin,rightMargin,topMargin,bottomMargin,kFALSE,kFALSE,kFALSE,
								 fHistClusterCellEFracAfterQA,Form("%s - %s - %s clusters",fCollisionSystem.Data(), plotDataSets[i].Data(), calo.Data()),"Energy Fraction of CellID in accepted Clusters","#frac{d#it{N}}{d#it{CellID}}",1,1);
			SaveCanvasAndWriteHistogram(canvas, fHistClusterCellEFracAfterQA, Form("%s/ClusterEnergyFracCells_%s_afterClusterQA.%s", outputDir.Data(), DataSets[i].Data(), suffix.Data()));
			vecClusterEnergyFracCells.push_back(new TH1D(*fHistClusterCellEFracAfterQA));
		}
	//-----------------------------------
		TGaxis::SetExponentOffset(0, 0, "x");
	//-----------------------------------
	//-----------------------------------
		TH2D* fHistClusterEnergyVsModule = (TH2D*)CaloExtQAContainer[i]->FindObject(Form("ClusterEnergyVsModule_afterClusterQA %s", fClusterCutSelection[i].Data()));
		if(fHistClusterEnergyVsModule){
			GetMinMaxBin(fHistClusterEnergyVsModule,minB,maxB);
			fHistClusterEnergyVsModule->GetXaxis()->SetRange(minB,maxB+5);
			fHistClusterEnergyVsModule->GetYaxis()->SetRangeUser(0,nCaloModules);
			DrawPeriodQAHistoTH2(canvas,leftMargin,0.1,topMargin,bottomMargin,kFALSE,kFALSE,kTRUE,
								fHistClusterEnergyVsModule,Form("%s - %s - %s",fCollisionSystem.Data(), plotDataSets[i].Data(), fClusters.Data()),
								 "Cluster Energy (GeV)","SuperModule Number",1,1);
			SaveCanvasAndWriteHistogram(canvas, fHistClusterEnergyVsModule, Form("%s/ClusterEnergyVsModule_%s.%s", outputDir.Data(), DataSets[i].Data(), suffix.Data()));

			canvas->SetRightMargin(rightMargin);
			PlotCaloQAModule(fHistClusterEnergyVsModule,
							 nCaloModules,
							 "Cluster Energy (GeV)",
							 "#frac{dE}{dN}",
							 1,10,1,0.1,kTRUE,minB,maxB,kTRUE);
			PutProcessLabelAndEnergyOnPlot(0.7, 0.92, 0.03, fCollisionSystem.Data(), plotDataSets[i].Data(), fClusters.Data());
			SaveCanvas(canvas, Form("%s/ClusterEnergyVsModule_Projected_%s.%s", outputDir.Data(), DataSets[i].Data(), suffix.Data()), kTRUE, kTRUE);
		}
	//-----------------------------------
		TH2D* fHistClusterEnergyVsNCells = (TH2D*)CaloExtQAContainer[i]->FindObject(Form("ClusterEnergyVsNCells_afterQA %s", fClusterCutSelection[i].Data()));
		if(fHistClusterEnergyVsNCells){
			AdjustHistRange(fHistClusterEnergyVsNCells,1,1.1,kTRUE,1,1);
			GetMinMaxBin(fHistClusterEnergyVsNCells,minB,maxB);
			fHistClusterEnergyVsNCells->GetXaxis()->SetRange(1,maxB+5);
			DrawPeriodQAHistoTH2(canvas,leftMargin,0.1,topMargin,bottomMargin,kFALSE,kFALSE,kTRUE,
								fHistClusterEnergyVsNCells," ",
								 "Cluster Energy (GeV)","#it{N}_{Cells} per Cluster",1,1,
								 0.7,0.92,0.03,fCollisionSystem,plotDataSets[i],fClusters);
			SaveCanvasAndWriteHistogram(canvas, fHistClusterEnergyVsNCells, Form("%s/ClusterEnergyVsNCells_%s.%s", outputDir.Data(), DataSets[i].Data(), suffix.Data()));
		}
	//-----------------------------------
		TH2D* fHistModuleEnergyVsModule = (TH2D*)CaloExtQAContainer[i]->FindObject(Form("ModuleEnergyVsModule %s", fClusterCutSelection[i].Data()));
		if(fHistModuleEnergyVsModule){
			GetMinMaxBin(fHistModuleEnergyVsModule,minB,maxB);
			fHistModuleEnergyVsModule->GetXaxis()->SetRange(minB,maxB+5);
			fHistModuleEnergyVsModule->GetYaxis()->SetRangeUser(0,nCaloModules);
			DrawPeriodQAHistoTH2(canvas,leftMargin,0.1,topMargin,bottomMargin,kFALSE,kFALSE,kTRUE,
								fHistModuleEnergyVsModule,Form("%s - %s - %s",fCollisionSystem.Data(), plotDataSets[i].Data(), fClusters.Data()),
								 "Total SuperModule Energy per Event (GeV)","SuperModule Number",1,1);
			SaveCanvasAndWriteHistogram(canvas, fHistModuleEnergyVsModule, Form("%s/ModuleEnergyVsModule_%s.%s", outputDir.Data(), DataSets[i].Data(), suffix.Data()));

			canvas->SetRightMargin(rightMargin);
			PlotCaloQAModule(fHistModuleEnergyVsModule,
							 nCaloModules,
							 "Total SuperModule Energy per Event (GeV)",
							 "#frac{dE}{dN}",
							 1,10,1,0.1,kTRUE,minB,maxB+5,kFALSE);
			PutProcessLabelAndEnergyOnPlot(0.7, 0.92, 0.03, fCollisionSystem.Data(), plotDataSets[i].Data(), fClusters.Data());
			SaveCanvas(canvas, Form("%s/ModuleEnergyVsModule_Projected_%s.%s", outputDir.Data(), DataSets[i].Data(), suffix.Data()), kFALSE, kTRUE);
			PlotCaloQAModule(fHistModuleEnergyVsModule,
							 nCaloModules,
							 "Total SuperModule Energy per Event (GeV)",
							 "#frac{dE}{dN}",
							 1,10,1,0.1,kTRUE,2,maxB+5,kFALSE);
			PutProcessLabelAndEnergyOnPlot(0.7, 0.92, 0.03, fCollisionSystem.Data(), plotDataSets[i].Data(), fClusters.Data());
			SaveCanvas(canvas, Form("%s/ModuleEnergyVsModule_Projected_%s_LOG.%s", outputDir.Data(), DataSets[i].Data(), suffix.Data()), kTRUE, kTRUE);
		}
	//-----------------------------------
		TH2D* fHistNCellsAbove100VsModule = (TH2D*)CaloExtQAContainer[i]->FindObject(Form("NCellsAbove100VsModule %s", fClusterCutSelection[i].Data()));
		if(fHistNCellsAbove100VsModule){
			GetMinMaxBin(fHistNCellsAbove100VsModule,minB,maxB);
			fHistNCellsAbove100VsModule->GetXaxis()->SetRange(minB,maxB+5);
			fHistNCellsAbove100VsModule->GetYaxis()->SetRangeUser(0,nCaloModules);
			DrawPeriodQAHistoTH2(canvas,leftMargin,0.1,topMargin,bottomMargin,kFALSE,kFALSE,kTRUE,
								fHistNCellsAbove100VsModule,Form("%s - %s - %s",fCollisionSystem.Data(), plotDataSets[i].Data(), fClusters.Data()),
								 "#it{N}_{Cells}>100 MeV in SM per Event","SuperModule Number",1,1);
			SaveCanvasAndWriteHistogram(canvas, fHistNCellsAbove100VsModule, Form("%s/NCellsAbove100VsModule_%s.%s", outputDir.Data(), DataSets[i].Data(), suffix.Data()));

			canvas->SetRightMargin(rightMargin);
			PlotCaloQAModule(fHistNCellsAbove100VsModule,
							 nCaloModules,
							 "#it{N}_{Cells}>100 MeV in SM per Event",
							 "#frac{d#it{N}_{Cells}>100 MeV}{dN}",
							 1,10,1,0.1,kTRUE,minB,maxB,kFALSE);
			PutProcessLabelAndEnergyOnPlot(0.7, 0.92, 0.03, fCollisionSystem.Data(), plotDataSets[i].Data(), fClusters.Data());
			SaveCanvas(canvas, Form("%s/NCellsAbove100VsModule_Projected_%s.%s", outputDir.Data(), DataSets[i].Data(), suffix.Data()), kFALSE, kTRUE);
		}
	//-----------------------------------
		TH2D* fHistNCellsAbove1500VsModule = (TH2D*)CaloExtQAContainer[i]->FindObject(Form("NCellsAbove1500VsModule %s", fClusterCutSelection[i].Data()));
		if(fHistNCellsAbove1500VsModule){
			GetMinMaxBin(fHistNCellsAbove1500VsModule,minB,maxB);
			fHistNCellsAbove1500VsModule->GetXaxis()->SetRange(minB,maxB+5);
			fHistNCellsAbove1500VsModule->GetYaxis()->SetRangeUser(0,nCaloModules);
			DrawPeriodQAHistoTH2(canvas,leftMargin,0.1,topMargin,bottomMargin,kFALSE,kFALSE,kTRUE,
								fHistNCellsAbove1500VsModule,Form("%s - %s - %s",fCollisionSystem.Data(), plotDataSets[i].Data(), fClusters.Data()),
								 "#it{N}_{Cells}>1500 MeV in SM per Event","SuperModule Number",1,1);
			SaveCanvasAndWriteHistogram(canvas, fHistNCellsAbove1500VsModule, Form("%s/NCellsAbove1500VsModule_%s.%s", outputDir.Data(), DataSets[i].Data(), suffix.Data()));

			canvas->SetRightMargin(rightMargin);
			PlotCaloQAModule(fHistNCellsAbove1500VsModule,
							 nCaloModules,
							 "#it{N}_{Cells}>1500 MeV in SM per Event",
							 "#frac{d#it{N}_{Cells}>1500 MeV}{dN}",
							 1,10,1,0.1,kTRUE,minB,maxB,kFALSE);
			PutProcessLabelAndEnergyOnPlot(0.7, 0.92, 0.03, fCollisionSystem.Data(), plotDataSets[i].Data(), fClusters.Data());
			SaveCanvas(canvas, Form("%s/NCellsAbove1500VsModule_Projected_%s.%s", outputDir.Data(), DataSets[i].Data(), suffix.Data()), kFALSE, kTRUE);
		}
	//-----------------------------------
		TH2D* fHistCellEnergyVsCellID = (TH2D*)CaloExtQAContainer[i]->FindObject(Form("CellEnergyVsCellID %s", fClusterCutSelection[i].Data()));
		TH2D* fHistCellTimeVsCellID = (TH2D*)CaloExtQAContainer[i]->FindObject(Form("CellTimeVsCellID %s", fClusterCutSelection[i].Data()));

		if(fHistCellEnergyVsCellID){
			fHistCellEnergyVsCellID->GetYaxis()->SetRangeUser(0,nCaloCells);
			DrawPeriodQAHistoTH2(canvas,leftMargin,0.1,topMargin,bottomMargin,kFALSE,kFALSE,kTRUE,
								fHistCellEnergyVsCellID,Form("%s - %s - %s",fCollisionSystem.Data(), plotDataSets[i].Data(), fClusters.Data()),
								 "Cell Energy (GeV)","CellID",1,1);
			SaveCanvasAndWriteHistogram(canvas, fHistCellEnergyVsCellID, Form("%s/CellEnergyVsCellID_%s.pdf", outputDir.Data(), DataSets[i].Data()));
			vecCellEnergyForComparison.push_back(new TH2D(*fHistCellEnergyVsCellID));

			fHistCellEnergyVsCellID->GetXaxis()->SetRangeUser(0,2);
			DrawPeriodQAHistoTH2(canvas,leftMargin,0.1,topMargin,bottomMargin,kFALSE,kFALSE,kTRUE,
								fHistCellEnergyVsCellID,Form("%s - %s - %s",fCollisionSystem.Data(), plotDataSets[i].Data(), fClusters.Data()),
								 "Cell Energy (GeV)","CellID",1,1);
			SaveCanvasAndWriteHistogram(canvas, fHistCellEnergyVsCellID, Form("%s/CellEnergyVsCellID_LowEnergy_%s.pdf", outputDir.Data(), DataSets[i].Data()));

			PlotCellMeanVsSigma(cellQA,nCaloCells,fHistCellEnergyVsCellID,
							 "Mean Cell Energy (GeV)",
							 "#sigma_{Cell Energy} (GeV)",
							 0,0,0,
							 0,0,0,kTRUE,isMC);
			if(!isMC && doCellQA){
				line->DrawLine(cellQA->EnergyMean[1],cellQA->EnergySigma[0],cellQA->EnergyMean[1],cellQA->EnergySigma[1]);
				line->DrawLine(cellQA->EnergyMean[0],cellQA->EnergySigma[1],cellQA->EnergyMean[1],cellQA->EnergySigma[1]);
			}
			PutProcessLabelAndEnergyOnPlot(0.65, 0.92, 0.03, fCollisionSystem.Data(), plotDataSets[i].Data(), fClusters.Data());
			SaveCanvas(canvas, Form("%s/CellEnergyVsSigma_%s.%s", outputDir.Data(), DataSets[i].Data(), suffix.Data()), kFALSE, kFALSE, kTRUE);

			PlotHotCells(cellQA,1,nCaloCells,fHistCellEnergyVsCellID,
							 "N_{Cell fired with Energy L to 30 GeV} / N_{Cell fired with Energy 0 to L GeV}",
							 "Integration Limit 'L' (GeV)",
							 0,0,0,
							 0,0,0,isMC,0.95);
			if(!isMC && doCellQA){
				const Int_t dim2D= 9;
				for(Int_t ii=0; ii<dim2D; ii++){
					line->DrawLine(cellQA->HotCells2D[ii][0],0.1+ii*0.1,cellQA->HotCells2D[ii][0],0.2+ii*0.1);
					line->DrawLine(cellQA->HotCells2D[ii][1],0.1+ii*0.1,cellQA->HotCells2D[ii][1],0.2+ii*0.1);
				}
			}
			PutProcessLabelAndEnergyOnPlot(0.65, 0.92, 0.03, fCollisionSystem.Data(), plotDataSets[i].Data(), fClusters.Data());
			SaveCanvas(canvas, Form("%s/CellHotCells2D_%s.%s", outputDir.Data(), DataSets[i].Data(), suffix.Data()), kTRUE, kFALSE, kTRUE);

			canvas->SetRightMargin(rightMargin);
			PlotHotCells(cellQA,0,nCaloCells,fHistCellTimeVsCellID,
							 "N_{Cell fired}",
							 "#frac{dN_{Cell fired with E>0.2 GeV}}{dN}",
							 0,0,0,
							 0,0,0,isMC);
			if(!isMC && doCellQA){
				line->DrawLine(cellQA->HotCells1D[0],0,cellQA->HotCells1D[0],10);
				line->DrawLine(cellQA->HotCells1D[1],0,cellQA->HotCells1D[1],10);
			}
			PutProcessLabelAndEnergyOnPlot(0.7, 0.92, 0.03, fCollisionSystem.Data(), plotDataSets[i].Data(), fClusters.Data());
			SaveCanvas(canvas, Form("%s/CellHotCells_%s.%s", outputDir.Data(), DataSets[i].Data(), suffix.Data()), kFALSE, kTRUE);

		}

// saved as .jpg per default due to size of histogram
		TGaxis::SetExponentOffset(0.5, 0, "x");
		if(fHistCellTimeVsCellID){
			fHistCellTimeVsCellID->GetYaxis()->SetRangeUser(0,nCaloCells);
			DrawPeriodQAHistoTH2(canvas,leftMargin,0.1,topMargin,bottomMargin,kFALSE,kFALSE,kTRUE,
								fHistCellTimeVsCellID,Form("%s - %s - %s",fCollisionSystem.Data(), plotDataSets[i].Data(), fClusters.Data()),
								 "Cell Time (#mus)","CellID",1,1);
			SaveCanvasAndWriteHistogram(canvas, fHistCellTimeVsCellID, Form("%s/CellTimeVsCellID_%s.jpg", outputDir.Data(), DataSets[i].Data()));

			PlotCellMeanVsSigma(cellQA,nCaloCells,fHistCellTimeVsCellID,
							 "Mean Cell Time (#mus)",
							 "#sigma_{Cell Time} (#mus)",
							 0,0,0,
							 0,0,0,kFALSE,isMC);
			if(!isMC && doCellQA){
				line->DrawLine(cellQA->TimeMean[0],cellQA->TimeSigma[0],cellQA->TimeMean[1],cellQA->TimeSigma[0]);
				line->DrawLine(cellQA->TimeMean[0],cellQA->TimeSigma[0],cellQA->TimeMean[0],cellQA->TimeSigma[1]);
				line->DrawLine(cellQA->TimeMean[1],cellQA->TimeSigma[0],cellQA->TimeMean[1],cellQA->TimeSigma[1]);
				line->DrawLine(cellQA->TimeMean[0],cellQA->TimeSigma[1],cellQA->TimeMean[1],cellQA->TimeSigma[1]);
			}

			TGaxis::SetExponentOffset(0, 0.5, "y");
			PutProcessLabelAndEnergyOnPlot(0.65, 0.92, 0.03, fCollisionSystem.Data(), plotDataSets[i].Data(), fClusters.Data());
			SaveCanvas(canvas, Form("%s/CellTimeVsSigma_%s.%s", outputDir.Data(), DataSets[i].Data(), suffix.Data()), kFALSE, kFALSE, kTRUE);

			canvas->SetRightMargin(rightMargin);
			PlotHotCells(cellQA,2,nCaloCells,fHistCellTimeVsCellID,
							 "N_{Cell fired} / N_{Cell fired at |t|< 0.02 (#mus)} - E_{Cell}>0.2 GeV",
							 "# of Entries",
							 0,0,0,
							 0,0,0,isMC,0.95);
			if(!isMC && doCellQA){
				//line->DrawLine(cellQA->HotCellsTime1D[0],0,cellQA->HotCellsTime1D[0],10);
				line->DrawLine(cellQA->HotCellsTime1D[1],0,cellQA->HotCellsTime1D[1],10);
			}
			PutProcessLabelAndEnergyOnPlot(0.7, 0.92, 0.03, fCollisionSystem.Data(), plotDataSets[i].Data(), fClusters.Data());
			SaveCanvas(canvas, Form("%s/CellHotCellsTime1D_%s.%s", outputDir.Data(), DataSets[i].Data(), suffix.Data()), kFALSE, kTRUE, kFALSE);
		}
//-----------------------------------
		TProfile* fEMCalBadChannels = (TProfile*)CaloExtQAContainer[i]->FindObject(Form("%s - Bad Channels",calo.Data()));
		if(fEMCalBadChannels){
			fEMCalBadChannels->SetTitle(Form("%s - %s - %s",fCollisionSystem.Data(), plotDataSets[i].Data(), fClusters.Data()));
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
			WriteHistogram(fEMCalBadChannels);
			SaveCanvas(canvas, Form("%s/BadChannels_%s.%s", outputDir.Data(), DataSets[i].Data(), suffix.Data()));
		}
		TGaxis::SetExponentOffset(0, 0, "x");
		TGaxis::SetExponentOffset(0, 0, "y");
//-----------------------------------
//-----------------------------------
		if(ClusterContainer[i]){
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
			TH2D* fHistClusterTrueGammaEM02 = (TH2D*)ClusterContainer[i]->FindObject("TrueClusGammaEM02");
			if(fHistClusterTrueGammaEM02){
				fHistClusterTrueGammaEM02->Scale(1/nEvents[i]);
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
				WriteHistogram(fHistClusterTrueGammaEM02);
				PutProcessLabelAndEnergyOnPlot(0.55, 0.99, 0.06, fCollisionSystem.Data(), "", "", 42);
				PutProcessLabelAndEnergyOnPlot(0.12, 0.2, 0.06, "#gamma", "", "", 42);
				cvsEM02->SetLogx(1); cvsEM02->SetLogy(0); cvsEM02->SetLogz(1); cvsEM02->Update();
				cvsEM02->SaveAs(Form("%s/EVsM02_TrueGamma_%s.%s", outputDir.Data(), DataSets[i].Data(), suffix.Data()));
				cvsEM02->Clear();
			}
			TH2D* fHistClusterTruePi0EM02 = (TH2D*)ClusterContainer[i]->FindObject("TrueClusPi0EM02");
			if(fHistClusterTruePi0EM02){
				fHistClusterTruePi0EM02->Scale(1/nEvents[i]);
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
				WriteHistogram(fHistClusterTruePi0EM02);
				PutProcessLabelAndEnergyOnPlot(0.55, 0.99, 0.06, fCollisionSystem.Data(), "", "", 42);
				PutProcessLabelAndEnergyOnPlot(0.3, 0.6, 0.06, "#pi^{0}", "", "", 42);
				cvsEM02->SetLogx(1); cvsEM02->SetLogy(0); cvsEM02->SetLogz(1); cvsEM02->Update();
				cvsEM02->SaveAs(Form("%s/EVsM02_TruePi0_%s.%s", outputDir.Data(), DataSets[i].Data(), suffix.Data()));
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
				cvsEM02->SaveAs(Form("%s/EVsM02_TrueGamma_Pi0_%s.%s", outputDir.Data(), DataSets[i].Data(), suffix.Data()));
				cvsEM02->Clear();
			}
			delete cvsEM02;
		}
//-----------------------------------
//-----------------------------------


//-----------------------------------
//-----------------------------------
		TH2D* MotherPi0Conv_Eta_Phi_ESD = (TH2D*) ESDContainer[i]->FindObject("ESD_MotherPi0ConvPhoton_Eta_Phi");
		TH2D* MotherEtaConv_Eta_Phi_ESD = (TH2D*) ESDContainer[i]->FindObject("ESD_MotherEtaConvPhoton_Eta_Phi");

		if(MotherPi0Conv_Eta_Phi_ESD){
			TH2D* MotherPi0Conv_Eta_Phi = (TH2D*) MotherPi0Conv_Eta_Phi_ESD->Clone();
			MotherPi0Conv_Eta_Phi->GetXaxis()->SetRangeUser(0.6,4);
			DrawPeriodQAHistoTH2(canvas,leftMargin,0.1,topMargin,bottomMargin,kFALSE,kFALSE,kFALSE,
								MotherPi0Conv_Eta_Phi,Form("%s - %s - %s",fCollisionSystem.Data(), plotDataSets[i].Data(), fClusters.Data()),
								 "#phi_{#gamma_{conv} under #pi^{0}-peak}","#eta_{#gamma_{conv} under #pi^{0}-peak}",1,1);
			SaveCanvasAndWriteHistogram(canvas, MotherPi0Conv_Eta_Phi, Form("%s/ConvPhotonPi0_Eta_Phi_%s.%s", outputDir.Data(), DataSets[i].Data(), suffix.Data()));
//-----------------------------------
			TH1D* MotherPi0Conv_Phi = (TH1D*) MotherPi0Conv_Eta_Phi->ProjectionX("MotherPi0Conv_Phi",1,200);
			if(MotherPi0Conv_Phi){
				MotherPi0Conv_Phi->GetXaxis()->SetRangeUser(0.8,3.8);
				DrawPeriodQAHistoTH1(canvas,leftMargin,rightMargin,topMargin,bottomMargin,kFALSE,kFALSE,kFALSE,
									 MotherPi0Conv_Phi," ","#phi_{#gamma_{conv} under #pi^{0}-peak}","#frac{d#it{N}}{d#eta}",1,1,
									 0.7,0.92,0.03,fCollisionSystem,plotDataSets[i],fClusters);
				SaveCanvasAndWriteHistogram(canvas, MotherPi0Conv_Phi, Form("%s/ConvPhotonPi0_Phi_%s.%s", outputDir.Data(), DataSets[i].Data(), suffix.Data()));
				vecConvPhotonEtaPhi_Pi0[0].push_back(new TH1D(*MotherPi0Conv_Phi));
			}
//-----------------------------------
			TH1D* MotherPi0Conv_Eta = (TH1D*) MotherPi0Conv_Eta_Phi->ProjectionY("MotherPi0Conv_Eta",1,600);
			if(MotherPi0Conv_Eta){
				MotherPi0Conv_Eta->GetXaxis()->SetRangeUser(-1,1);
				DrawPeriodQAHistoTH1(canvas,leftMargin,rightMargin,topMargin,bottomMargin,kFALSE,kFALSE,kFALSE,
									 MotherPi0Conv_Eta," ","#eta_{#gamma_{conv} under #pi^{0}-peak}","#frac{d#it{N}}{d#phi}",1,1,
									 0.7,0.92,0.03,fCollisionSystem,plotDataSets[i],fClusters);
				SaveCanvasAndWriteHistogram(canvas, MotherPi0Conv_Eta, Form("%s/ConvPhotonPi0_Eta_%s.%s", outputDir.Data(), DataSets[i].Data(), suffix.Data()));
				vecConvPhotonEtaPhi_Pi0[1].push_back(new TH1D(*MotherPi0Conv_Eta));
			}
		}
//-----------------------------------
		if(MotherEtaConv_Eta_Phi_ESD){
			TH2D* MotherEtaConv_Eta_Phi = (TH2D*) MotherEtaConv_Eta_Phi_ESD->Clone();
			DrawPeriodQAHistoTH2(canvas,leftMargin,0.1,topMargin,bottomMargin,kFALSE,kFALSE,kFALSE,
								MotherEtaConv_Eta_Phi,Form("%s - %s - %s",fCollisionSystem.Data(), plotDataSets[i].Data(), fClusters.Data()),
								 "#phi_{#gamma_{conv} under #eta-peak}","#eta_{#gamma_{conv} under #eta-peak}",1,1);
			SaveCanvasAndWriteHistogram(canvas, MotherEtaConv_Eta_Phi, Form("%s/ConvPhotonEta_Eta_Phi_%s.%s", outputDir.Data(), DataSets[i].Data(), suffix.Data()));
//-----------------------------------
			TH1D* MotherEtaConv_Phi = (TH1D*) MotherEtaConv_Eta_Phi->ProjectionX("MotherEtaConv_Phi",1,200);
			if(MotherEtaConv_Phi){
				DrawPeriodQAHistoTH1(canvas,leftMargin,rightMargin,topMargin,bottomMargin,kFALSE,kFALSE,kFALSE,
									 MotherEtaConv_Phi," ","#phi_{#gamma_{conv} under #eta-peak}","#frac{d#it{N}}{d#phi}",1,1,
									 0.7,0.92,0.03,fCollisionSystem,plotDataSets[i],fClusters);
				SaveCanvasAndWriteHistogram(canvas, MotherEtaConv_Phi, Form("%s/ConvPhotonEta_Phi_%s.%s", outputDir.Data(), DataSets[i].Data(), suffix.Data()));
				vecConvPhotonEtaPhi_Eta[0].push_back(new TH1D(*MotherEtaConv_Phi));
			}
//-----------------------------------
			TH1D* MotherEtaConv_Eta = (TH1D*) MotherEtaConv_Eta_Phi->ProjectionY("MotherEtaConv_Eta",1,600);
			if(MotherEtaConv_Eta){
				MotherEtaConv_Eta->GetXaxis()->SetRangeUser(-1,1);
				DrawPeriodQAHistoTH1(canvas,leftMargin,rightMargin,topMargin,bottomMargin,kFALSE,kFALSE,kFALSE,
									 MotherEtaConv_Eta," ","#eta_{#gamma_{conv} under #eta-peak}","#frac{d#it{N}}{d#eta}",1,1,
									 0.7,0.92,0.03,fCollisionSystem,plotDataSets[i],fClusters);
				SaveCanvasAndWriteHistogram(canvas, MotherEtaConv_Eta, Form("%s/ConvPhotonEta_Eta_%s.%s", outputDir.Data(), DataSets[i].Data(), suffix.Data()));
				vecConvPhotonEtaPhi_Eta[1].push_back(new TH1D(*MotherEtaConv_Eta));
			}
		}
//-----------------------------------
//-----------------------------------
		TH2D* ESDMother = (TH2D*) ESDContainer[i]->FindObject("ESD_Mother_InvMass_Pt");
		if(ESDMother){
			WriteHistogram(ESDMother);
			vecESDMother.push_back(new TH2D(*ESDMother));
		}else {cout << "ERROR: Object |ESD_Mother_InvMass_Pt| could not be found! Skipping Draw & return..." << endl; return;}
//-----------------------------------
		TH2D* ESDMotherMatched = (TH2D*) ESDContainer[i]->FindObject("ESD_MotherMatched_InvMass_Pt");
		if(ESDMotherMatched){
			WriteHistogram(ESDMotherMatched);
			vecESDMotherMatched.push_back(new TH2D(*ESDMotherMatched));
		}else {cout << "ERROR: Object |ESD_MotherMatched_InvMass_Pt| could not be found! Skipping Draw & return..." << endl; return;}
//-----------------------------------
	}

//*****************************************************************************************************
//*****************************************************************************************************
//****************************** Drawing Special Histograms *******************************************
//*****************************************************************************************************
//*****************************************************************************************************

	cout << "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;
	cout << "Drawing Special Histograms" << endl;

	fOutput[0]->cd();

//-----------------------------------

	for(Int_t iMC=1; iMC<nSets; iMC++){
		TH2D* temp = (TH2D*) vecEtaPhiAfterQA.at(iMC)->Clone(Form("CloneEtaVsPhi-%i",iMC));
		for(Int_t iX=1; iX<=temp->GetNbinsX(); iX++){
			for(Int_t iY=1; iY<=temp->GetNbinsY(); iY++){
				Double_t tempBinMC = temp->GetBinContent(iX,iY);
				Double_t tempBinData = vecEtaPhiAfterQA.at(0)->GetBinContent(iX,iY);
				if( (tempBinMC+tempBinData) > 0) temp->SetBinContent(iX,iY,(tempBinData-tempBinMC)/(tempBinData+tempBinMC));
				else temp->SetBinContent(iX,iY,-2);
			}
		}
		temp->GetZaxis()->SetRangeUser(-1,1);
		DrawPeriodQAHistoTH2(canvas,leftMargin,0.1,topMargin,bottomMargin,kFALSE,kFALSE,kFALSE,
							temp,Form("%s - %s & %s - (Data-MC) / (Data+MC) - %s",fCollisionSystem.Data(), plotDataSets[0].Data(), plotDataSets[iMC].Data(), fClusters.Data()),"#phi_{Cluster}","#eta_{Cluster}",1,1);
		SaveCanvasAndWriteHistogram(canvas, temp, Form("%s/EtaVsPhi_Asym%s_%s_afterClusterQA.%s", outputDir.Data(), DataSets[iMC].Data(), DataSets[0].Data(), suffix.Data()));
	}

//-----------------------------------

	for(Int_t iMC=1; iMC<nSets; iMC++){
		TH2D* temp = (TH2D*) vecEtaPhiAfterQA.at(iMC)->Clone(Form("CloneEtaVsPhi-%i",iMC));
		for(Int_t iX=1; iX<=temp->GetNbinsX(); iX++){
			for(Int_t iY=1; iY<=temp->GetNbinsY(); iY++){
				Double_t tempBinMC = temp->GetBinContent(iX,iY);
				Double_t tempBinData = vecEtaPhiAfterQA.at(0)->GetBinContent(iX,iY);
				if( tempBinMC != 0) temp->SetBinContent(iX,iY,tempBinData/tempBinMC);
				else temp->SetBinContent(iX,iY,-2);
			}
		}
		temp->GetZaxis()->SetRangeUser(0,2);
		DrawPeriodQAHistoTH2(canvas,leftMargin,0.1,topMargin,bottomMargin,kFALSE,kFALSE,kFALSE,
							temp,Form("%s - %s & %s - Data / MC - %s",fCollisionSystem.Data(), plotDataSets[0].Data(), plotDataSets[iMC].Data(), fClusters.Data()),"#phi_{Cluster}","#eta_{Cluster}",1,1);
		SaveCanvasAndWriteHistogram(canvas, temp, Form("%s/EtaVsPhi_Ratio%s_%s_afterClusterQA.%s", outputDir.Data(), DataSets[iMC].Data(), DataSets[0].Data(), suffix.Data()));
	}

//-----------------------------------

	for(Int_t i=0; i<nSets; i++){
		TH2D* mother = (TH2D*) vecESDMother.at(i);
		TH2D* motherMatched = (TH2D*) vecESDMotherMatched.at(i);

		if(mother->GetNbinsX() != motherMatched->GetNbinsX()) {cout << "ERROR: NBinsX of ESD_Mother and ESD_Mother_Matched do not agree, return..." << endl; return;}
		if(mother->GetNbinsY() != motherMatched->GetNbinsY()) {cout << "ERROR: NBinsY of ESD_Mother and ESD_Mother_Matched do not agree, return..." << endl; return;}

		if(mother && motherMatched){
			TH2D* fHistInvMassPtMotherMotherMatched = (TH2D*) mother->Clone("Mother_InvMass/(MotherMatched_InvMass + Mother_InvMass)");
			//TH2D* fHistInvMassPtMotherMotherMatched = new TH2D("Mother_InvMass/(MotherMatched_InvMass + Mother_InvMass)","Mother_InvMass/(MotherMatched_InvMass + Mother_InvMass)", 800, 0, 0.8, 250, 0, 25);
			fHistInvMassPtMotherMotherMatched->Reset("ICE");
			for(Int_t x = 1; x <= fHistInvMassPtMotherMotherMatched->GetNbinsX(); x++) {
				for(Int_t y = 1; y <= fHistInvMassPtMotherMotherMatched->GetNbinsY(); y++) {
					Double_t a = mother->GetBinContent(x,y);
					Double_t b = motherMatched->GetBinContent(x,y);
					Double_t r = 0;
					if ( (a+b)!= 0 ) r = a/(a+b);
					fHistInvMassPtMotherMotherMatched->SetBinContent(x,y,r);
				}
			}

			DrawPeriodQAHistoTH2(canvas,leftMargin,0.1,topMargin,bottomMargin,kFALSE,kFALSE,kFALSE,
								fHistInvMassPtMotherMotherMatched," ","#it{M}_{inv, Mother} (GeV/#it{c}^{2})","#it{p}_{T, Mother} (GeV/#it{c})",1,0.8);

			TString whichTrMatch = fClusterCutSelection[i].Copy();
			whichTrMatch.Remove(10,9); whichTrMatch.Remove(0,9);

			TLatex* label[4];
			label[0] = new TLatex(0.4, 0.84, Form("%s: #frac{Accepted Mother-Candidates}{All Mother-Candidates}",plotDataSets[i].Data()));
			label[1] = new TLatex(0.4, 0.79, Form( "PCM, %s TrackMatchingCuts:",calo.Data()));
			label[2] = new TLatex(0.4, 0.75, Form( "- |#Delta#eta|<%s", TrackMatchingEtaMax[whichTrMatch.Atoi()].Data()));
			label[3] = new TLatex(0.4, 0.71, Form( "- e^{+}: %s<#Delta#phi<%s; e^{-}: %.2f<#Delta#phi<%.2f", TrackMatchingPhiMin[whichTrMatch.Atoi()].Data(), TrackMatchingPhiMax[whichTrMatch.Atoi()].Data(), (-1* TrackMatchingPhiMax[whichTrMatch.Atoi()].Atof()) , (-1* TrackMatchingPhiMin[whichTrMatch.Atoi()].Atof()) ));

			for(Int_t iL=0; iL<4; iL++){
				label[iL]->SetNDC();
				label[iL]->SetTextColor(1);
				label[iL]->SetTextSize(0.03);
				label[iL]->Draw();
			}

			SaveCanvasAndWriteHistogram(canvas, fHistInvMassPtMotherMotherMatched, Form("%s/%s_%s_cut%i.%s", outputDir.Data(),"TrackMatchingCut", DataSets[i].Data(), whichTrMatch.Atoi(), suffix.Data()));
			delete fHistInvMassPtMotherMotherMatched;

//---------

			TH2D* mcPi0 = 0x0;
			TH2D* mcEta = 0x0;
			TH2D* mcPi0Matched_MC = 0x0;
			TH2D* mcEtaMatched_MC = 0x0;
			TH2D* mcPi0Matched_True = 0x0;
			TH2D* mcEtaMatched_True = 0x0;

			Double_t nDataMatches = 0;
			Double_t nMCMatches = 0;
			Double_t nTrueMCMatches = 0;

			Double_t nMCMatches_Missing = 0;
			Double_t nMCMatches_TooMany = 0;

			if(TrueContainer[i]){
				mcPi0 = (TH2D*) TrueContainer[i]->FindObject("ESD_TruePi0_InvMass_Pt");
				mcEta = (TH2D*) TrueContainer[i]->FindObject("ESD_TrueEta_InvMass_Pt");
				mcPi0Matched_MC = (TH2D*) TrueContainer[i]->FindObject("ESD_TruePi0_Matched_InvMass_Pt");
				mcEtaMatched_MC = (TH2D*) TrueContainer[i]->FindObject("ESD_TrueEta_Matched_InvMass_Pt");
				mcPi0Matched_True = (TH2D*) TrueContainer[i]->FindObject("ESD_TruePi0CaloConvertedPhotonMatched_InvMass_Pt");
				mcEtaMatched_True = (TH2D*) TrueContainer[i]->FindObject("ESD_TrueEtaCaloConvertedPhotonMatched_InvMass_Pt");
			}

			if( mcPi0Matched_True && mcEtaMatched_True){
				TH2D* matched_True = (TH2D*) mcPi0Matched_True->Clone("matched_True");
				matched_True->Add(mcEtaMatched_True,1);

				TH2D* fHistInvMassPtMotherMatchedCompare_Matched_True = (TH2D*) mother->Clone("(MotherMatched_InvMass-TrueMotherMatched_InvMass)/(MotherMatched_InvMass+TrueMotherMatched_InvMass)");
				fHistInvMassPtMotherMatchedCompare_Matched_True->Reset("ICE");
				for(Int_t x = 1; x <= fHistInvMassPtMotherMatchedCompare_Matched_True->GetNbinsX(); x++) {
					for(Int_t y = 1; y <= fHistInvMassPtMotherMatchedCompare_Matched_True->GetNbinsY(); y++) {
						Double_t a = motherMatched->GetBinContent(x,y);
						Double_t b = matched_True->GetBinContent(x,y);
						nDataMatches += a;
						Double_t r = 0;
						if( a == 0 && b == 0) r = -2;
						else r = (a-b)/(a+b);
						fHistInvMassPtMotherMatchedCompare_Matched_True->SetBinContent(x,y,r);
					}
				}
				fHistInvMassPtMotherMatchedCompare_Matched_True->GetZaxis()->SetRangeUser(-1,1);

				DrawPeriodQAHistoTH2(canvas,leftMargin,0.1,topMargin,bottomMargin,kFALSE,kFALSE,kFALSE,
									fHistInvMassPtMotherMatchedCompare_Matched_True," ","#it{M}_{inv, Mother} (GeV/#it{c}^{2})","#it{p}_{T, Mother} (GeV/#it{c})",1,0.8);

				TLatex* label1 = new TLatex(0.4, 0.86, Form("%s: #frac{V0^{full MC}_{rejected} - V0^{TrueMC}_{rejected}}{V0^{full MC}_{rejected} + V0^{TrueMC}_{rejected}}",plotDataSets[i].Data()));
				label1->SetNDC();
				label1->SetTextColor(1);
				label1->SetTextSize(0.03);
				label1->Draw(); label[1]->Draw(); label[2]->Draw(); label[3]->Draw();
				SaveCanvasAndWriteHistogram(canvas, fHistInvMassPtMotherMatchedCompare_Matched_True, Form("%s/%s_%s_cut%i.%s", outputDir.Data(),"TrackMatchingRatio_fullMC_TrueMC", DataSets[i].Data(), whichTrMatch.Atoi(), suffix.Data()));
				delete fHistInvMassPtMotherMatchedCompare_Matched_True;
			}

			if( mcPi0Matched_MC && mcEtaMatched_MC){
				TH2D* matched_MC = (TH2D*) mcPi0Matched_MC->Clone("matched_MC");
				matched_MC->Add(mcEtaMatched_MC,1);

				TH2D* fHistInvMassPtMotherMatchedCompare_Matched_MC = (TH2D*) mother->Clone("(MotherMatched_InvMass-MCMatched_InvMass)/(MotherMatched_InvMass+MCMatched_InvMass)");
				fHistInvMassPtMotherMatchedCompare_Matched_MC->Reset("ICE");
				for(Int_t x = 1; x <= fHistInvMassPtMotherMatchedCompare_Matched_MC->GetNbinsX(); x++) {
					for(Int_t y = 1; y <= fHistInvMassPtMotherMatchedCompare_Matched_MC->GetNbinsY(); y++) {
						Double_t a = motherMatched->GetBinContent(x,y);
						Double_t b = matched_MC->GetBinContent(x,y);
						Double_t r = 0;
						if( a == 0 && b == 0) r = -2;
						else r = (a-b)/(a+b);
						fHistInvMassPtMotherMatchedCompare_Matched_MC->SetBinContent(x,y,r);
					}
				}
				fHistInvMassPtMotherMatchedCompare_Matched_MC->GetZaxis()->SetRangeUser(-1,1);

				DrawPeriodQAHistoTH2(canvas,leftMargin,0.1,topMargin,bottomMargin,kFALSE,kFALSE,kFALSE,
									fHistInvMassPtMotherMatchedCompare_Matched_MC," ","#it{M}_{inv, Mother} (GeV/#it{c}^{2})","#it{p}_{T, Mother} (GeV/#it{c})",1,0.8);

				TLatex* label2 = new TLatex(0.4, 0.86, Form("%s: #frac{V0^{full MC}_{rejected} - V0^{MC}_{rejected}}{V0^{full MC}_{rejected} + V0^{MC}_{rejected}}",plotDataSets[i].Data()));
				label2->SetNDC();
				label2->SetTextColor(1);
				label2->SetTextSize(0.03);
				label2->Draw(); label[1]->Draw(); label[2]->Draw(); label[3]->Draw();
				SaveCanvasAndWriteHistogram(canvas, fHistInvMassPtMotherMatchedCompare_Matched_MC, Form("%s/%s_%s_cut%i.%s", outputDir.Data(),"TrackMatchingRatio_fullMC_MC", DataSets[i].Data(), whichTrMatch.Atoi(), suffix.Data()));
				delete fHistInvMassPtMotherMatchedCompare_Matched_MC;
			}

			if( mcPi0Matched_True && mcEtaMatched_True && mcPi0Matched_MC && mcEtaMatched_MC){
				TH2D* matched_True = (TH2D*) mcPi0Matched_True->Clone("matched_True2");
				matched_True->Add(mcEtaMatched_True,1);
				TH2D* matched_MC = (TH2D*) mcPi0Matched_MC->Clone("matched_MC2");
				matched_MC->Add(mcEtaMatched_MC,1);

				TH2D* fHistInvMassPtMotherMatchedCompare_True_MC = (TH2D*) mother->Clone("(TrueMotherMatched_InvMass-MCMatched_InvMass)/(TrueMotherMatched_InvMass+MCMatched_InvMass)");
				fHistInvMassPtMotherMatchedCompare_True_MC->Reset("ICE");
				for(Int_t x = 1; x <= fHistInvMassPtMotherMatchedCompare_True_MC->GetNbinsX(); x++) {
					for(Int_t y = 1; y <= fHistInvMassPtMotherMatchedCompare_True_MC->GetNbinsY(); y++) {
						Double_t a = matched_True->GetBinContent(x,y);
						Double_t b = matched_MC->GetBinContent(x,y);
						nTrueMCMatches += a;
						nMCMatches += b;
						Double_t r = 0;
						if( a == 0 && b == 0) r = -2;
						else r = (a-b)/(a+b);
						fHistInvMassPtMotherMatchedCompare_True_MC->SetBinContent(x,y,r);
						if( a > b ) nMCMatches_Missing += abs(a-b);
						if( a < b ) nMCMatches_TooMany += abs(a-b);
					}
				}
				fHistInvMassPtMotherMatchedCompare_True_MC->GetZaxis()->SetRangeUser(-1,1);

				DrawPeriodQAHistoTH2(canvas,leftMargin,0.1,topMargin,bottomMargin,kFALSE,kFALSE,kFALSE,
									fHistInvMassPtMotherMatchedCompare_True_MC," ","#it{M}_{inv, Mother} (GeV/#it{c}^{2})","#it{p}_{T, Mother} (GeV/#it{c})",1,0.8);

				TLatex* label3 = new TLatex(0.4, 0.86, Form("%s: #frac{V0^{TrueMC}_{rejected} - V0^{MC}_{rejected}}{V0^{TrueMC}_{rejected} + V0^{MC}_{rejected}}",plotDataSets[i].Data()));
				label3->SetNDC();
				label3->SetTextColor(1);
				label3->SetTextSize(0.03);
				label3->Draw(); label[1]->Draw(); label[2]->Draw(); label[3]->Draw();
				SaveCanvasAndWriteHistogram(canvas, fHistInvMassPtMotherMatchedCompare_True_MC, Form("%s/%s_%s_cut%i.%s", outputDir.Data(),"TrackMatchingRatio_TrueMC_MC", DataSets[i].Data(), whichTrMatch.Atoi(), suffix.Data()));
				delete fHistInvMassPtMotherMatchedCompare_True_MC;
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
					TH1D* mcFractionMatchesMissingPt = new TH1D(Form("fractionMissing%i",iMeson)," ",fNBinsAnalysisPt,fBinsAnalysisPt);
					TH1D* mcFractionMatchesTooManyPt = new TH1D(Form("fractionTooMany%i",iMeson)," ",fNBinsAnalysisPt,fBinsAnalysisPt);

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
						mcFractionMatchesMissingPt->SetBinContent(iPt+1,rMiss);
						mcFractionMatchesTooManyPt->SetBinContent(iPt+1,rTooMany);
						//cout << fBinsAnalysisPt[iPt] << " - " << fBinsAnalysisPt[iPt+1] << ", rMiss:" << rMiss << ", rTooMany: " << rTooMany << ", rTotal: " << rTotal << ", rTooMany*rTotal*0.01: " << rTooMany*rTotal*0.01 <<endl;
					}

					EditTH1NoRunwise(mcFractionMatchesTooManyPt,24,1.5,kAzure,kAzure,1.2,0.9);
					mcFractionMatchesTooManyPt->SetLineWidth(0.6);
					mcFractionMatchesTooManyPt->GetXaxis()->SetRangeUser(fBinsAnalysisPt[0],fBinsAnalysisPt[fNBinsAnalysisPt]+2);
					mcFractionMatchesTooManyPt->GetXaxis()->SetTitle("#it{p}_{T, #gamma#gamma} (GeV/#it{c})");
					mcFractionMatchesTooManyPt->GetYaxis()->SetRangeUser(1E-3,120);
					mcFractionMatchesTooManyPt->GetYaxis()->SetTitle("fraction of all true candidates (%)");
					mcFractionMatchesTooManyPt->Sumw2();
					mcFractionMatchesTooManyPt->Draw("p");

					EditTH1NoRunwise(mcFractionMatchesMissingPt,20,1.5,kRed,kRed,1.2,0.9);
					mcFractionMatchesMissingPt->SetLineWidth(0.6);
					mcFractionMatchesMissingPt->Sumw2();
					mcFractionMatchesMissingPt->Draw("p, same");

					TLegend *legend = new TLegend(0.35,0.82,0.75,0.9);
					legend->SetNColumns(1);
					legend->SetFillColor(0);
					legend->SetLineColor(0);
					legend->SetTextSize(0.03);
					legend->SetTextFont(42);
					legend->AddEntry(mcFractionMatchesMissingPt,"... misses true matching");
					legend->AddEntry(mcFractionMatchesTooManyPt,"... removes true candidate by mistake");
					legend->Draw("same");

					TLatex* clusVZero = new TLatex(0.45, 0.91, "Cluster - V^{0}-track matching...");
					clusVZero->SetNDC();
					clusVZero->SetTextColor(1);
					clusVZero->SetTextFont(42);
					clusVZero->SetTextSize(0.03);
					clusVZero->Draw("SAME");

					PutProcessLabelAndEnergyOnPlot(0.15, 0.95, 0.03, fCollisionSystem.Data(), plotDataSets[i].Data(), fTextMeasurementMeson[iMeson].Data());
					PutProcessLabelAndEnergyOnPlot(0.15, 0.84, 0.03, Form("%i < #it{M}_{#gamma#gamma} < %i MeV/#it{c}^{2}",rangeMin[iMeson],rangeMax[iMeson]), Form("#gamma's rec. with PCM, %s",calo.Data()), "");

					canvas->SetRightMargin(0.02); canvas->SetLeftMargin(0.08); canvas->SetBottomMargin(0.12); canvas->SetTopMargin(0.02);
					SaveWriteCanvas(canvas, Form("%s/%s_%s_cut%i_%i.%s", outputDir.Data(),"TrackMatchingMissing_TrueMC_MC_Pt", DataSets[i].Data(), whichTrMatch.Atoi(), iMeson, suffix.Data()), kTRUE, kTRUE , kFALSE);
					canvas->SetRightMargin(rightMargin); canvas->SetLeftMargin(leftMargin); canvas->SetBottomMargin(bottomMargin); canvas->SetTopMargin(topMargin);

					delete mcFractionMatchesMissingPt;
					delete mcFractionMatchesTooManyPt;
					delete legend;
				}
			}

			if( mcPi0 && mcPi0Matched_True && mcPi0Matched_MC){
				TLegend *legend = new TLegend(0.3,0.8,0.7,0.9);
				legend->SetNColumns(1);
				legend->SetFillColor(0);
				legend->SetLineColor(0);
				legend->SetTextSize(0.03);
				legend->SetTextFont(42);

				TH2D* mcCompare = (TH2D*) mcPi0->Clone("mcCompare");
				for(Int_t x = 1; x <= mcCompare->GetNbinsX(); x++) {
					for(Int_t y = 1; y <= mcCompare->GetNbinsY(); y++) {
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

				PutProcessLabelAndEnergyOnPlot(0.7, 0.9, 0.03, fCollisionSystem.Data(), plotDataSets[i].Data(), Form("%s",fTextMeasurement.Data()));
				PutProcessLabelAndEnergyOnPlot(0.7, 0.79, 0.03, Form("#gamma's rec. with PCM, %s",calo.Data()), "", "");
				SaveWriteCanvas(canvas, Form("%s/TrackMatching_invMassPi0_withTrueMatches_%s.%s", outputDir.Data(), DataSets[i].Data(), suffix.Data()), kFALSE, kTRUE , kFALSE);

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
				PutProcessLabelAndEnergyOnPlot(0.7, 0.9, 0.03, fCollisionSystem.Data(), plotDataSets[i].Data(), Form("%s",fTextMeasurement.Data()));
				PutProcessLabelAndEnergyOnPlot(0.7, 0.79, 0.03, Form("#gamma's rec. with PCM, %s",calo.Data()), "", "");
				SaveWriteCanvas(canvas, Form("%s/TrackMatching_invMassPi0_withoutTrueMatches_%s.%s", outputDir.Data(), DataSets[i].Data(), suffix.Data()), kFALSE, kTRUE , kFALSE);
				delete legend;
			}

			if( mcPi0 && mcEta && mcPi0Matched_True && mcEtaMatched_True && mcPi0Matched_MC && mcEtaMatched_MC)
			{
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
				Int_t lastBinning[2];
				lastBinning[0]=0; lastBinning[1]=0;
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
					for(Int_t x = 1; x <= mcCompare->GetNbinsX(); x++) {
						for(Int_t y = 1; y <= mcCompare->GetNbinsY(); y++) {
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

					PutProcessLabelAndEnergyOnPlot(0.7, 0.9, 0.03, fCollisionSystem.Data(), plotDataSets[i].Data(), Form("%s & %s",fTextMeasurement.Data(),fTextMeasurementEta.Data()));
					PutProcessLabelAndEnergyOnPlot(0.7, 0.785, 0.03, Form("%.1f < #it{p}_{T, #gamma#gamma} < %.1f GeV/#it{c}",mcCompare->GetYaxis()->GetBinUpEdge(lowBin[iB]),mcCompare->GetYaxis()->GetBinUpEdge(upBin[iB])),"","");
					PutProcessLabelAndEnergyOnPlot(0.7, 0.74, 0.03, Form("#gamma's rec. with PCM, %s",calo.Data()), "","");
					SaveWriteCanvas(canvas, Form("%s/TrackMatching_invMassPi0Eta_withTrueMatches_%s_Bins%i-%i.%s", outputDir.Data(), DataSets[i].Data(), lowBin[iB],upBin[iB], suffix.Data()), kFALSE, kTRUE , kFALSE);

					if(iB == nBin-1){
						pad1->cd();
						AdjustHistRange(projectTrue,1,10,kTRUE,1,0.7);
						DrawAutoGammaHistoPaper(projectTrue,
												" ",
												"#it{M}_{#gamma#gamma} (GeV/#it{c}^{2})",
												"d#it{N}/d#it{M}_{#gamma#gamma}",
												0,0,0,
												0,0,0,
												1,0,0.8,0.6);
						projectCompare->DrawCopy("same,e,hist");
						PutProcessLabelAndEnergyOnPlot(0.6, 0.98, 0.063, fCollisionSystem.Data(), plotDataSets[i].Data(), Form("%s & %s",fTextMeasurement.Data(),fTextMeasurementEta.Data()),42);
						PutProcessLabelAndEnergyOnPlot(0.1, 0.98, 0.063, Form("%.1f < #it{p}_{T, #gamma#gamma} < %.1f GeV/#it{c}",mcCompare->GetYaxis()->GetBinUpEdge(lowBin[iB]),mcCompare->GetYaxis()->GetBinUpEdge(upBin[iB])),"","",42);
						PutProcessLabelAndEnergyOnPlot(0.6, 0.74, 0.063, Form("#gamma's rec. with PCM, %s",calo.Data()), "" ,"",42);
					}else if(iB == nBin-2){
						pad2->cd();
						AdjustHistRange(projectTrue,1,10,kTRUE,1,0.7);
						DrawAutoGammaHistoPaper(projectTrue,
												" ",
												"#it{M}_{#gamma#gamma} (GeV/#it{c}^{2})",
												"d#it{N}/d#it{M}_{#gamma#gamma}",
												0,0,0,
												0,0,0,
												1,0,0.8,0.6);
						projectCompare->DrawCopy("same,e,hist");
						TLegend* leg2 = (TLegend*) legend->Clone();
						leg2->SetX1(0.46);
						leg2->SetX2(0.86);
						leg2->SetY1(0.847);
						leg2->SetY2(0.967);
						leg2->SetTextSize(0.06);
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
					PutProcessLabelAndEnergyOnPlot(0.7, 0.9, 0.03, fCollisionSystem.Data(), plotDataSets[i].Data(), Form("%s & %s",fTextMeasurement.Data(),fTextMeasurementEta.Data()));
					PutProcessLabelAndEnergyOnPlot(0.7, 0.785, 0.03, Form("%.1f < #it{p}_{T, #gamma#gamma} < %.1f GeV/#it{c}",mcCompare->GetYaxis()->GetBinUpEdge(lowBin[iB]),mcCompare->GetYaxis()->GetBinUpEdge(upBin[iB])),"","");
					PutProcessLabelAndEnergyOnPlot(0.7, 0.74, 0.03, Form("#gamma's rec. with PCM, %s",calo.Data()), "","");
					SaveWriteCanvas(canvas, Form("%s/TrackMatching_invMassPi0Eta_withoutTrueMatches_%s_Bins%i-%i.%s", outputDir.Data(), DataSets[i].Data(),lowBin[iB],upBin[iB], suffix.Data()), kFALSE, kTRUE , kFALSE);
				}
				SaveCanvas(cvs2pads, Form("%s/TrackMatching_invMassPi0Eta_withTrueMatches_%s_Bins%i-%i_%i-%i.%s", outputDir.Data(), DataSets[i].Data(),lowBin[nBin-2],upBin[nBin-2],lowBin[nBin-1],upBin[nBin-1], suffix.Data()), kFALSE, kFALSE , kFALSE);
				delete cvs2pads;
			}

			if(TrueContainer[i]){
				if(nTrueMCMatches>0 && nMCMatches>0){
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
						 << "(" << nMCMatches_Missing/nTrueMCMatches*100 << "%) - too many matches in MC(already subtracted): " << nMCMatches_TooMany
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
						 << "(" << nMCMatches_Missing/nTrueMCMatches*100 << "%) - too many matches in MC(already subtracted): " << nMCMatches_TooMany
						 << "(" << nMCMatches_TooMany/nTrueMCMatches*100 << "%)" << endl;
					fLog << "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;
					fLog << "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;
				}else{cout << "ERROR: nTrueMCMatches == 0 (" << nTrueMCMatches << ") or nMCMatches == 0 (" << nMCMatches << "), returning" << endl; return;}
			}
		}else {cout << "WARNING: ESD_Mother_InvMass_Pt or ESD_MotherMatched_InvMass_Pt not found for " << DataSets[i].Data() << " ! Skipping drawing of related histograms..." << endl;}
	}

//-----------------------------------
//-----------------------------------

	canvas->cd();
	canvas->SetLeftMargin(leftMargin);
	canvas->SetRightMargin(rightMargin);
	canvas->SetBottomMargin(bottomMargin);
	canvas->SetTopMargin(topMargin);

	Int_t nESDRebin = 5;
	Int_t iMinPt[5]={0,6,10,20,50};
	std::vector<TH1D*> vecRange;

	for(Int_t i=0; i<nSets; i++){
		for(Int_t iMin=0; iMin<5; iMin++)
		{
			TH2D* ESD_InvMass_Pt = (TH2D*) vecESDMother.at(i)->Clone();
			TH2D* ESD_Matched_InvMass_Pt = (TH2D*) vecESDMotherMatched.at(i)->Clone();

			TH1D* ESD_InvMass = (TH1D*) ESD_InvMass_Pt->ProjectionX("ESD_InvMass",iMinPt[iMin],ESD_InvMass_Pt->GetXaxis()->GetNbins());
			TH1D* ESD_Matched_InvMass = (TH1D*) ESD_Matched_InvMass_Pt->ProjectionX("ESD_InvMass_Matched",iMinPt[iMin],ESD_Matched_InvMass_Pt->GetXaxis()->GetNbins());
			TH1D* ESD_InvMass_Matched_Sum = (TH1D*) ESD_InvMass->Clone();
			ESD_InvMass->Sumw2();
			vecRange.push_back(ESD_InvMass);
			ESD_Matched_InvMass->Sumw2();
			vecRange.push_back(ESD_Matched_InvMass);
			ESD_InvMass_Matched_Sum->Sumw2();
			vecRange.push_back(ESD_InvMass_Matched_Sum);
			ESD_InvMass_Matched_Sum->Add(ESD_Matched_InvMass,1);

			ESD_InvMass->Rebin(nESDRebin);
			ESD_Matched_InvMass->Rebin(nESDRebin);
			ESD_InvMass_Matched_Sum->Rebin(nESDRebin);
//-----------------------------------
			AdjustHistRange(vecRange,1.,10.,kTRUE,1,1.);
			DrawAutoGammaHistMatch3H(ESD_InvMass_Matched_Sum, ESD_InvMass, ESD_Matched_InvMass,
									 " ",
									 "#it{M}_{inv, Mother} (GeV/#it{c}^{2})",
									 "d#it{N}/d#it{M}_{inv}",
									 0,0,0,
									 0,0,0,
									 1,0,0.8,
									 1,1.2,"Sum", "Accepted", "Rejected", kFALSE);
			PutProcessLabelAndEnergyOnPlot(0.13, 0.92, 0.03, fCollisionSystem.Data(), plotDataSets[i].Data(), Form("Excluded M_{inv}^{Mother}-candidates by V^{0}-track matching, #it{p}^{Mother}_{T} > %.01f GeV/#it{c}",((Float_t)iMinPt[iMin])/10));
			SaveCanvas(canvas, Form("%s/TrackMatching_ESD_IntegratedPt_fromPtBin_%i_%s.%s", outputDir.Data(), iMinPt[iMin], DataSets[i].Data(),suffix.Data()), kFALSE, kTRUE);
			vecRange.clear();
		}
	}
//-----------------------------------

	for(Int_t i=1; i<nSets; i++){
		if(TrueContainer[i]){
			Int_t nPi0Rebin = 5;
			Int_t nEtaRebin = 5;

			TH2D* TruePi0_InvMass_Pt = (TH2D*) TrueContainer[i]->FindObject("ESD_TruePi0CaloConvertedPhoton_InvMass_Pt");
			TH2D* TruePi0_InvMass_Pt_matched = (TH2D*) TrueContainer[i]->FindObject("ESD_TruePi0CaloConvertedPhotonMatched_InvMass_Pt");
			TH2D* TrueEta_InvMass_Pt = (TH2D*) TrueContainer[i]->FindObject("ESD_TrueEtaCaloConvertedPhoton_InvMass_Pt");
			TH2D* TrueEta_InvMass_Pt_matched = (TH2D*) TrueContainer[i]->FindObject("ESD_TrueEtaCaloConvertedPhotonMatched_InvMass_Pt");

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
			vecRange.push_back(TruePi0_InvMass_sum);
			vecRange.push_back(TruePi0_InvMass_matched);
			vecRange.push_back(TruePi0_InvMass);
			AdjustHistRange(vecRange,1.,1.1,kTRUE,1,0.);
			DrawAutoGammaHistMatch3H(TruePi0_InvMass_sum, TruePi0_InvMass_matched, TruePi0_InvMass,
							   " ",
							   "#it{M}_{#gamma e^{+/-}} (GeV/#it{c}^{2})",
							   "d#it{N}/d#it{M}_{#gamma e^{+/-}}",
							   0,0,0,
							   0,0,0,
							   1,0,0.8,
							   1,1.2, "Sum", "Rejected", "Accepted");
			PutProcessLabelAndEnergyOnPlot(0.74, 0.78, 0.03, fCollisionSystem.Data(), plotDataSets[i].Data(), fTextMeasurement.Data());
			PutProcessLabelAndEnergyOnPlot(0.74, 0.665, 0.03, "#gamma's rec. with PCM and", Form("%s, e^{+/-} leads cluster",calo.Data()), "");
			SaveCanvas(canvas, Form("%s/TrackMatching_TrueMCPi0_IntegratedPt_%s.%s", outputDir.Data(), DataSets[i].Data(), suffix.Data()));
			vecRange.clear();
		//---------
			vecRange.push_back(TrueEta_InvMass_sum);
			vecRange.push_back(TrueEta_InvMass_matched);
			vecRange.push_back(TrueEta_InvMass);
			AdjustHistRange(vecRange,1.,1.1,kTRUE,1,0.);
			DrawAutoGammaHistMatch3H(TrueEta_InvMass_sum, TrueEta_InvMass_matched, TrueEta_InvMass,
							   " ",
							   "#it{M}_{#gamma e^{+/-}} (GeV/#it{c}^{2})",
							   "d#it{N}/d#it{M}_{#gamma e^{+/-}}",
							   0,0,0,
							   0,0,0,
							   1,0,0.8,
							   1,1.2, "Sum", "Rejected", "Accepted");
			PutProcessLabelAndEnergyOnPlot(0.74, 0.78, 0.03, fCollisionSystem.Data(), plotDataSets[i].Data(), fTextMeasurement.Data());
			PutProcessLabelAndEnergyOnPlot(0.74, 0.665, 0.03, "#gamma's rec. with PCM and", Form("%s, e^{+/-} leads cluster",calo.Data()), "");
			SaveCanvas(canvas, Form("%s/TrackMatching_TrueMCEta_IntegratedPt_%s.%s", outputDir.Data(), DataSets[i].Data(),suffix.Data()));
			vecRange.clear();
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
				vecRange.push_back(ExampleTruePi0_InvMass_sum);
				vecRange.push_back(ExampleTruePi0_InvMass_matched);
				vecRange.push_back(ExampleTruePi0_InvMass);
				AdjustHistRange(vecRange,1.,1.1,kTRUE,1,0.);
				DrawAutoGammaHistMatch3H(ExampleTruePi0_InvMass_sum, ExampleTruePi0_InvMass_matched, ExampleTruePi0_InvMass,
								   " ",
								   "#it{M}_{#gamma e^{+/-}} (GeV/#it{c}^{2})",
								   "d#it{N}/d#it{M}_{#gamma e^{+/-}}",
								   0,0,0,
								   0,0,0,
								   1,0,0.8,
								   1,1.2, "Sum", "Rejected", "Accepted");
				PutProcessLabelAndEnergyOnPlot(0.74, 0.78, 0.03, fCollisionSystem.Data(), Form("%s, %s",plotDataSets[i].Data(),fTextMeasurement.Data()), Form("%.01f < #it{p}_{T} < %.01f GeV/#it{c}",ptMin, ptMax));
				PutProcessLabelAndEnergyOnPlot(0.74, 0.665, 0.03, Form("#gamma's rec. with PCM, %s",calo.Data()), "e^{+/-} leads cluster", "");
				SaveCanvas(canvas, Form("%s/TrackMatching_TrueMCPi0_PtBins%01i-%01i_%s.%s", outputDir.Data(), ptExampleMin[iPt], ptExampleMax[iPt], DataSets[i].Data(),suffix.Data()));
				vecRange.clear();
		//---------
				vecRange.push_back(ExampleTrueEta_InvMass_sum);
				vecRange.push_back(ExampleTrueEta_InvMass_matched);
				vecRange.push_back(ExampleTrueEta_InvMass);
				AdjustHistRange(vecRange,1.,1.1,kTRUE,1,0.);
				DrawAutoGammaHistMatch3H(ExampleTrueEta_InvMass_sum, ExampleTrueEta_InvMass_matched, ExampleTrueEta_InvMass,
								   " ",
								   "#it{M}_{#gamma e^{+/-}} (GeV/#it{c}^{2})",
								   "d#it{N}/d#it{M}_{#gamma e^{+/-}}",
								   0,0,0,
								   0,0,0,
								   1,0,0.8,
								   1,1.2, "Sum", "Rejected", "Accepted");
				PutProcessLabelAndEnergyOnPlot(0.74, 0.78, 0.03, fCollisionSystem.Data(), Form("%s, %s",plotDataSets[i].Data(),fTextMeasurementEta.Data()), Form("%.01f < #it{p}_{T} < %.01f GeV/#it{c}",ptMin, ptMax));
				PutProcessLabelAndEnergyOnPlot(0.74, 0.665, 0.03, Form("#gamma's rec. with PCM, %s",calo.Data()), "e^{+/-} leads cluster", "");
				SaveCanvas(canvas, Form("%s/TrackMatching_TrueMCEta_PtBins%01i-%01i_%s.%s", outputDir.Data(), ptExampleMin[iPt], ptExampleMax[iPt], DataSets[i].Data(),suffix.Data()));
				vecRange.clear();
			}
		//---------
			TH2D* TruePi0Photon_InvMass_Pt = (TH2D*) TrueContainer[i]->FindObject("ESD_TruePi0CaloPhoton_InvMass_Pt");
			TH2D* TruePi0Electron_InvMass_Pt = (TH2D*) TrueContainer[i]->FindObject("ESD_TruePi0CaloElectron_InvMass_Pt");
			TH2D* TrueEtaPhoton_InvMass_Pt = (TH2D*) TrueContainer[i]->FindObject("ESD_TrueEtaCaloPhoton_InvMass_Pt");
			TH2D* TrueEtaElectron_InvMass_Pt = (TH2D*) TrueContainer[i]->FindObject("ESD_TrueEtaCaloElectron_InvMass_Pt");

			TH1D* TruePi0CaloPhoton_InvMass = (TH1D*) TruePi0Photon_InvMass_Pt->ProjectionX("TruePi0CaloPhoton_InvMass",1,300);
			TH1D* TruePi0CaloElectron_InvMass = (TH1D*) TruePi0Electron_InvMass_Pt->ProjectionX("TruePi0CaloElectron_InvMass",1,300);
			TH1D* TrueEtaCaloPhoton_InvMass = (TH1D*) TrueEtaPhoton_InvMass_Pt->ProjectionX("TrueEtaCaloPhoton_InvMass",1,300);
			TH1D* TrueEtaCaloElectron_InvMass = (TH1D*) TrueEtaElectron_InvMass_Pt->ProjectionX("TrueEtaCaloElectron_InvMass",1,300);

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
			vecRange.push_back(TruePi0Calo_InvMass_sum);
			vecRange.push_back(TruePi0CaloPhoton_InvMass);
			vecRange.push_back(TruePi0CaloElectron_InvMass);
			AdjustHistRange(vecRange,1.,10.,kTRUE,1,0.5);
			DrawAutoGammaHistMatch3H(TruePi0Calo_InvMass_sum, TruePi0CaloPhoton_InvMass, TruePi0CaloElectron_InvMass,
									 " ",
									 "#it{M}_{#gamma#gamma} (GeV/#it{c}^{2})",
									 "d#it{N}/d#it{M}_{#gamma#gamma}",
									 0,0,0,
									 0,0,0,
									 1,0,0.8,
									 1,1.2,"Sum","TrueMC: #gamma_{EMCAL}","TrueMC: e^{+/-}_{EMCAL}");
			PutProcessLabelAndEnergyOnPlot(0.75, 0.72, 0.03, fCollisionSystem.Data(), plotDataSets[i].Data(), fTextMeasurement.Data());
			PutProcessLabelAndEnergyOnPlot(0.75, 0.61, 0.03, Form("#gamma's rec. with PCM, %s",calo.Data()), "", "");
			SaveCanvas(canvas, Form("%s/TrueMCPi0_GammaGamma_GammaElectron_%s.%s", outputDir.Data(), DataSets[i].Data(),suffix.Data()), kFALSE, kTRUE);
			vecRange.clear();
		//---------
			vecRange.push_back(TrueEtaCalo_InvMass_sum);
			vecRange.push_back(TrueEtaCaloPhoton_InvMass);
			vecRange.push_back(TrueEtaCaloElectron_InvMass);
			AdjustHistRange(vecRange,1.,10.,kTRUE,1,0.5);
			DrawAutoGammaHistMatch3H(TrueEtaCalo_InvMass_sum, TrueEtaCaloPhoton_InvMass, TrueEtaCaloElectron_InvMass,
									 " ",
									 "#it{M}_{#gamma#gamma}  (GeV/#it{c}^{2})",
									 "d#it{N}/d#it{M}_{#gamma#gamma}",
									 0,0,0,
									 0,0,0,
									 1,0,0.8,
									 1,1.2,"Sum","TrueMC: #gamma_{EMCAL}","TrueMC: e^{+/-}_{EMCAL}");
			PutProcessLabelAndEnergyOnPlot(0.2, 0.9, 0.03, fCollisionSystem.Data(), plotDataSets[i].Data(), fTextMeasurementEta.Data());
			PutProcessLabelAndEnergyOnPlot(0.2, 0.79, 0.03, Form("#gamma's rec. with PCM, %s",calo.Data()), "", "");
			SaveCanvas(canvas, Form("%s/TrueMCEta_GammaGamma_GammaElectron_%s.%s", outputDir.Data(), DataSets[i].Data(),suffix.Data()), kFALSE, kTRUE);
			vecRange.clear();
		//---------
			vecRange.push_back(TruePi0Calo_InvMass_sum);
			vecRange.push_back(TruePi0CaloPhoton_InvMass);
			vecRange.push_back(TruePi0CaloElectron_InvMass);
			AdjustHistRange(vecRange,1.,10.,kTRUE,1,0.5);
			TruePi0Calo_InvMass_sum->Add(TrueEtaCalo_InvMass_sum,1);
			TruePi0CaloPhoton_InvMass->Add(TrueEtaCaloPhoton_InvMass,1);
			TruePi0CaloElectron_InvMass->Add(TrueEtaCaloElectron_InvMass,1);
			DrawAutoGammaHistMatch3H(TruePi0Calo_InvMass_sum, TruePi0CaloPhoton_InvMass, TruePi0CaloElectron_InvMass,
									 " ",
									 "#it{M}_{#gamma#gamma} (GeV/#it{c}^{2})",
									 "d#it{N}/d#it{M}_{#gamma#gamma}",
									 0,0,0,
									 0,0,0,
									 1,0,0.8,
									 1,1.2,"Sum","TrueMC: #gamma_{EMCAL}","TrueMC: e^{+/-}_{EMCAL}");
			PutProcessLabelAndEnergyOnPlot(0.4, 0.9, 0.03, fCollisionSystem.Data(), plotDataSets[i].Data(), Form("%s & %s", fTextMeasurement.Data(), fTextMeasurementEta.Data()));
			PutProcessLabelAndEnergyOnPlot(0.4, 0.79, 0.03, Form("#gamma's rec. with PCM, %s",calo.Data()), "", "");
			SaveCanvas(canvas, Form("%s/TrueMCPi0Eta_GammaGamma_GammaElectron_%s.%s", outputDir.Data(), DataSets[i].Data(),suffix.Data()), kFALSE, kTRUE);
			vecRange.clear();
		//---------
		}else {cout << "ERROR: TrueContainer not found for " << DataSets[i].Data() << ", really processing MC? Returning..." << endl; return;}
	}

//*****************************************************************************************************
//*****************************************************************************************************
//****************************** Comparison Histograms ************************************************
//*****************************************************************************************************
//*****************************************************************************************************

	if(nSets>1){
		cout << "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;
		cout << "Drawing Comparison Histograms" << endl;

//-----------------------------------
		for(Int_t iVec=0; iVec<(Int_t)vecNEvents.size(); iVec++){
			TH1D* temp = vecNEvents.at(iVec);
			temp->Sumw2();
		}
		DrawPeriodQACompareHistoTH1(canvas,0.11, 0.02, 0.04, 0.11,kFALSE,kFALSE,kFALSE,
							 vecNEvents," ","","N_{Events}",1,1.1,
							 labelData, colorCompare, kTRUE, 1.1, 1.1, kTRUE,
							 0.8,0.94,0.03,fCollisionSystem,plotDataSets,fClusters);
		SaveCanvas(canvas, Form("%s/Comparison/NEvents.%s", outputDir.Data(), suffix.Data()));

		DrawPeriodQACompareHistoRatioTH1(canvas,0.11, 0.02, 0.04, 0.11,kFALSE,kFALSE,kFALSE,
							 vecNEvents," ","","N_{Events}",1,1.1,
							 labelData, colorCompare, kTRUE, 1.1, 1.1, kTRUE,
							 0.8,0.94,0.03,fCollisionSystem,plotDataSets,fClusters);
		SaveCanvas(canvas, Form("%s/Comparison/Ratios/NEvents.%s", outputDir.Data(), suffix.Data()));

//-----------------------------------
		for(Int_t iVec=0; iVec<(Int_t)vecVertexZ.size(); iVec++){
			TH1D* temp = vecVertexZ.at(iVec);
			temp->Sumw2();
			temp->Scale(1/nEvents[iVec]);
		}
		DrawPeriodQACompareHistoTH1(canvas,0.11, 0.02, 0.04, 0.11,kFALSE,kFALSE,kFALSE,
							 vecVertexZ," ","Vertex z (cm)","#frac{1}{N_{Events}} #frac{dN}{dz}",1,1.1,
							 labelData, colorCompare, kTRUE, 1.1, 1.1, kTRUE,
							 0.8,0.94,0.03,fCollisionSystem,plotDataSets,fClusters);
		SaveCanvas(canvas, Form("%s/Comparison/Vertex_Z.%s", outputDir.Data(), suffix.Data()));

		DrawPeriodQACompareHistoRatioTH1(canvas,0.11, 0.02, 0.04, 0.11,kFALSE,kFALSE,kFALSE,
							 vecVertexZ," ","Vertex z (cm)","#frac{1}{N_{Events}} #frac{dN}{dz}",1,1.1,
							 labelData, colorCompare, kTRUE, 1.1, 1.1, kTRUE,
							 0.8,0.94,0.03,fCollisionSystem,plotDataSets,fClusters);
		SaveCanvas(canvas, Form("%s/Comparison/Ratios/Vertex_Z.%s", outputDir.Data(), suffix.Data()));

//-----------------------------------
		for(Int_t iVec=0; iVec<(Int_t)vecNGoodTracks.size(); iVec++){
			TH1D* temp = vecNGoodTracks.at(iVec);
			temp->Sumw2();
			temp->Scale(1/nEvents[iVec]);
		}
		DrawPeriodQACompareHistoTH1(canvas,0.11, 0.02, 0.04, 0.11,kFALSE,kTRUE,kFALSE,
									vecNGoodTracks," ","Number of Good Tracks","#frac{1}{N_{Events}} #frac{dN}{dTracks}",1,1.1,
									labelData, colorCompare, kTRUE, 5, 5, kTRUE,
									0.8,0.94,0.03,fCollisionSystem,plotDataSets,fClusters);
		SaveCanvas(canvas, Form("%s/Comparison/NGoodTracks.%s", outputDir.Data(), suffix.Data()), kFALSE, kTRUE);

		DrawPeriodQACompareHistoRatioTH1(canvas,0.11, 0.02, 0.04, 0.11,kFALSE,kFALSE,kFALSE,
										 vecNGoodTracks," ","Number of Good Tracks","#frac{1}{N_{Events}} #frac{dN}{dTracks}",1,1.1,
										 labelData, colorCompare, kTRUE, 5, 5, kTRUE,
										 0.8,0.94,0.03,fCollisionSystem,plotDataSets,fClusters);
		SaveCanvas(canvas, Form("%s/Comparison/Ratios/NGoodTracks.%s", outputDir.Data(), suffix.Data()));
//-----------------------------------
//-----------------------------------
		TGaxis::SetExponentOffset(0.5, 0, "x");
		TH1D* mcClusterTime[nSets];
		std::vector<TH1D*> vecClusterTimeAfterCorrected;
		for(Int_t iVec=0; iVec<nSets; iVec++){
			TH1D* temp = vecClusterTimeAfter.at(iVec);
			if(iVec==0){
				for(Int_t ii=1; ii<nSets; ii++){
					mcClusterTime[ii] = (TH1D*) temp->Clone(Form("clone_mc%iClusterTimeAfter",ii));
					mcClusterTime[ii]->Reset("ICE");
				}
				temp->Sumw2();
				Double_t nMax = temp->GetBinContent(temp->GetMaximumBin());
				temp->Scale(1/nMax);
				vecClusterTimeAfterCorrected.push_back(new TH1D(*temp));
			}else{
				Double_t meanMC = GetMaximumBinValueTH1(temp);//temp->GetMean(1);
				Double_t meanData = GetMaximumBinValueTH1(vecClusterTimeAfter.at(0));
				for(Int_t iBin=1; iBin<temp->GetXaxis()->GetNbins(); iBin++){
					mcClusterTime[iVec]->SetBinContent(temp->GetXaxis()->FindBin(temp->GetBinCenter(iBin) - meanMC + meanData),
													temp->GetBinContent(iBin));
				}
				mcClusterTime[iVec]->Sumw2();
				Double_t nMax = mcClusterTime[iVec]->GetBinContent(mcClusterTime[iVec]->GetMaximumBin());
				mcClusterTime[iVec]->Scale(1/nMax);
				vecClusterTimeAfterCorrected.push_back(new TH1D(*mcClusterTime[iVec]));
			}
		}
		DrawPeriodQACompareHistoTH1(canvas,0.11, 0.02, 0.04, 0.11,kFALSE,kTRUE,kFALSE,
							 vecClusterTimeAfterCorrected," ","#it{t}_{Cluster} (ns)","#frac{1}{N_{max}} #frac{dN}{dt}",1,1.1,
							 labelData, colorCompare, kTRUE, 5, 5, kTRUE,
							 0.8,0.94,0.03,fCollisionSystem,plotDataSets,fClusters);
		SaveCanvas(canvas, Form("%s/Comparison/ClusterTimeAfter.%s", outputDir.Data(), suffix.Data()), kFALSE, kTRUE);
//-----------------------------------
		std::vector<TH1D*> vecClusterTimeBeforeCorrected;
		for(Int_t iVec=0; iVec<(Int_t) vecClusterTimeBefore.size(); iVec++){
			TH1D* temp = vecClusterTimeBefore.at(iVec);
			if(iVec==0){
				for(Int_t ii=1; ii<nSets; ii++){
					mcClusterTime[ii] = (TH1D*) temp->Clone(Form("clone_mc%iClusterTimeBefore",ii));
					mcClusterTime[ii]->Reset("ICE");
				}
				temp->Sumw2();
				Double_t nMax = temp->GetBinContent(temp->GetMaximumBin());
				temp->Scale(1/nMax);
				vecClusterTimeBeforeCorrected.push_back(new TH1D(*temp));
			}else{
				Double_t meanMC = GetMaximumBinValueTH1(temp); //temp->GetMean(1);
				Double_t meanData = GetMaximumBinValueTH1(vecClusterTimeBefore.at(0));
				for(Int_t iBin=1; iBin<temp->GetXaxis()->GetNbins(); iBin++){
					mcClusterTime[iVec]->SetBinContent(temp->GetXaxis()->FindBin(temp->GetBinCenter(iBin) - meanMC + meanData),
													temp->GetBinContent(iBin));
				}
				mcClusterTime[iVec]->Sumw2();
				Double_t nMax = mcClusterTime[iVec]->GetBinContent(mcClusterTime[iVec]->GetMaximumBin());
				mcClusterTime[iVec]->Scale(1/nMax);
				vecClusterTimeBeforeCorrected.push_back(new TH1D(*mcClusterTime[iVec]));
			}
		}
		DrawPeriodQACompareHistoTH1(canvas,0.11, 0.02, 0.04, 0.11,kFALSE,kTRUE,kFALSE,
							 vecClusterTimeBeforeCorrected," ","#it{t}_{Cluster} (ns)","#frac{1}{N_{max}} #frac{dN}{dt}",1,1.1,
							 labelData, colorCompare, kTRUE, 5, 5, kTRUE,
							 0.8,0.94,0.03,fCollisionSystem,plotDataSets,fClusters);
		SaveCanvas(canvas, Form("%s/Comparison/ClusterTimeBefore.%s", outputDir.Data(), suffix.Data()), kFALSE, kTRUE);
		TGaxis::SetExponentOffset(0, 0, "x");
//-----------------------------------
//-----------------------------------
		for(Int_t iMC=1; iMC<nSets; iMC++){
			canvas->SetRightMargin(0.1);
			CheckCellsDataMC(cellQAData,
							 vecCellEnergyForComparison.at(0),
							 vecCellEnergyForComparison.at(iMC),
							 Form("Compare Cells: Data and %s",plotDataSets[iMC].Data()),
							 "CellID",
							 nCaloCells,
							 "Data",
							 plotDataSets[iMC].Data());
			PutProcessLabelAndEnergyOnPlot(0.7, 0.9, 0.03, fCollisionSystem.Data(), plotDataSets[iMC].Data(), fClusters.Data());
			SaveCanvas(canvas, Form("%s/Comparison/CompareCells_Data_%s.%s", outputDir.Data(), plotDataSets[iMC].Data(), suffix.Data()));
			canvas->SetRightMargin(0.02);
		}
//-----------------------------------
//-----------------------------------
		for(Int_t iVec=0; iVec<(Int_t)vecClusterR.size(); iVec++){
			TH1D* temp = vecClusterR.at(iVec);
			temp->Sumw2();
			Double_t nEntries = temp->GetEntries();
			temp->Scale(1/nEntries);
		}
		DrawPeriodQACompareHistoTH1(canvas,0.11, 0.02, 0.04, 0.11,kFALSE,kTRUE,kFALSE,
							 vecClusterR," ","R_{Cluster} (cm)","#frac{1}{N} #frac{dN}{dR}",1,1.1,
							 labelData, colorCompare, kTRUE, 5, 5, kTRUE,
							 0.8,0.94,0.03,fCollisionSystem,plotDataSets,fClusters);
		SaveCanvas(canvas, Form("%s/Comparison/R_Cluster_afterQA.%s", outputDir.Data(), suffix.Data()), kFALSE , kTRUE);

		DrawPeriodQACompareHistoRatioTH1(canvas,0.11, 0.02, 0.04, 0.11,kFALSE,kTRUE,kFALSE,
							 vecClusterR," ","R_{Cluster} (cm)","#frac{1}{N} #frac{dN}{dR}",1,1.1,
							 labelData, colorCompare, kTRUE, 1.1, 1.1, kTRUE,
							 0.8,0.94,0.03,fCollisionSystem,plotDataSets,fClusters);
		SaveCanvas(canvas, Form("%s/Comparison/Ratios/R_Cluster_afterQA.%s", outputDir.Data(), suffix.Data()));

//-----------------------------------
//-----------------------------------
		for(Int_t iVec=0; iVec<(Int_t)vecClusterEnergy.size(); iVec++){
			TH1D* temp = vecClusterEnergy.at(iVec);
			temp->Scale(1/nEvents[iVec]);
//			temp->GetXaxis()->SetRangeUser(minClusE,fBinsClusterPt[fNBinsClusterPt+1]);
		}
		DrawPeriodQACompareHistoTH1(canvas,0.11, 0.02, 0.04, 0.11,kTRUE,kTRUE,kFALSE,
							 vecClusterEnergy," ","Cluster Energy (GeV)","#frac{1}{N_{Events}} #frac{dN}{dE}",1,1.1,
							 labelData, colorCompare, kTRUE, 2, 5, kFALSE,
							 0.8,0.94,0.03,fCollisionSystem,plotDataSets,fClusters);
		SaveCanvas(canvas, Form("%s/Comparison/Energy_Cluster_afterQA.%s", outputDir.Data(), suffix.Data()), kTRUE, kTRUE);

		DrawPeriodQACompareHistoRatioTH1(canvas,0.11, 0.02, 0.04, 0.11,kFALSE,kTRUE,kFALSE,
							 vecClusterEnergy," ","Cluster Energy (GeV)","#frac{1}{N_{Events}} #frac{dN}{dE}",1,1.1,
							 labelData, colorCompare, kTRUE, 2, 5, kFALSE,
							 0.8,0.94,0.03,fCollisionSystem,plotDataSets,fClusters);
		SaveCanvas(canvas, Form("%s/Comparison/Ratios/Energy_Cluster_afterQA.%s", outputDir.Data(), suffix.Data()));
//-----------------------------------
//-----------------------------------
		for(Int_t iVec=0; iVec<(Int_t)vecClusterM02.size(); iVec++){
			TH1D* temp = vecClusterM02.at(iVec);
			temp->Sumw2();
			temp->Scale(1/nEvents[iVec]);
		}
		DrawPeriodQACompareHistoTH1(canvas,0.11, 0.02, 0.04, 0.11,kFALSE,kTRUE,kFALSE,
							 vecClusterM02," ","#lambda_{0}^{2}","#frac{1}{N_{Events}} #frac{dN}{d#lambda_{0}^{2}}",1,1.1,
							 labelData, colorCompare, kTRUE, 5, 5, kTRUE,
							 0.8,0.94,0.03,fCollisionSystem,plotDataSets,fClusters);
		SaveCanvas(canvas, Form("%s/Comparison/M02_afterQA.%s", outputDir.Data(), suffix.Data()), kFALSE, kTRUE);

		DrawPeriodQACompareHistoRatioTH1(canvas,0.11, 0.02, 0.04, 0.11,kFALSE,kTRUE,kFALSE,
							 vecClusterM02," ","#lambda_{0}^{2}","#frac{1}{N_{Events}} #frac{dN}{d#lambda_{0}^{2}}",1,1.1,
							 labelData, colorCompare, kTRUE, 5, 5, kTRUE,
							 0.8,0.94,0.03,fCollisionSystem,plotDataSets,fClusters);
		SaveCanvas(canvas, Form("%s/Comparison/Ratios/M02_afterQA.%s", outputDir.Data(), suffix.Data()));
//-----------------------------------
//-----------------------------------
		for(Int_t iVec=0; iVec<(Int_t)vecClusterM20.size(); iVec++){
			TH1D* temp = vecClusterM20.at(iVec);
			temp->Sumw2();
			temp->Scale(1/nEvents[iVec]);
		}
		DrawPeriodQACompareHistoTH1(canvas,0.11, 0.02, 0.04, 0.11,kFALSE,kTRUE,kFALSE,
							 vecClusterM20," ","#lambda_{1}^{2}","#frac{1}{N_{Events}} #frac{dN}{d#lambda_{1}^{2}}",1,1.1,
							 labelData, colorCompare, kTRUE, 5, 5, kTRUE,
							 0.8,0.94,0.03,fCollisionSystem,plotDataSets,fClusters);
		SaveCanvas(canvas, Form("%s/Comparison/M20_afterQA.%s", outputDir.Data(), suffix.Data()), kFALSE, kTRUE);

		DrawPeriodQACompareHistoRatioTH1(canvas,0.11, 0.02, 0.04, 0.11,kFALSE,kTRUE,kFALSE,
							 vecClusterM20," ","#lambda_{1}^{2}","#frac{1}{N_{Events}} #frac{dN}{d#lambda_{1}^{2}}",1,1.1,
							 labelData, colorCompare, kTRUE, 5, 5, kTRUE,
							 0.8,0.94,0.03,fCollisionSystem,plotDataSets,fClusters);
		SaveCanvas(canvas, Form("%s/Comparison/Ratios/M20_afterQA.%s", outputDir.Data(), suffix.Data()));
//-----------------------------------
//-----------------------------------
		for(Int_t iVec=0; iVec<(Int_t)vecClusterDispersion.size(); iVec++){
			TH1D* temp = vecClusterDispersion.at(iVec);
			temp->Sumw2();
			temp->Scale(1/nEvents[iVec]);
		}
		DrawPeriodQACompareHistoTH1(canvas,0.11, 0.02, 0.04, 0.11,kFALSE,kTRUE,kFALSE,
							 vecClusterDispersion," ","Dispersion","#frac{1}{N_{Events}} #frac{dN}{dDisp}",1,1.1,
							 labelData, colorCompare, kTRUE, 5, 5, kTRUE,
							 0.8,0.94,0.03,fCollisionSystem,plotDataSets,fClusters);
		SaveCanvas(canvas, Form("%s/Comparison/Dispersion_afterQA.%s", outputDir.Data(), suffix.Data()), kFALSE, kTRUE);

		DrawPeriodQACompareHistoRatioTH1(canvas,0.11, 0.02, 0.04, 0.11,kFALSE,kTRUE,kFALSE,
							 vecClusterDispersion," ","Dispersion","#frac{1}{N_{Events}} #frac{dN}{dDisp}",1,1.1,
							 labelData, colorCompare, kTRUE, 5, 5, kTRUE,
							 0.8,0.94,0.03,fCollisionSystem,plotDataSets,fClusters);
		SaveCanvas(canvas, Form("%s/Comparison/Ratios/Dispersion_afterQA.%s", outputDir.Data(), suffix.Data()));
//-----------------------------------
//-----------------------------------
		for(Int_t iVec=0; iVec<(Int_t)vecClusterNCells.size(); iVec++){
			TH1D* temp = vecClusterNCells.at(iVec);
			temp->Sumw2();
			temp->Scale(1/nEvents[iVec]);
		}
		DrawPeriodQACompareHistoTH1(canvas,0.11, 0.02, 0.04, 0.11,kFALSE,kTRUE,kFALSE,
							 vecClusterNCells," ","N_{Cells} per Cluster","#frac{1}{N_{Events}} #frac{dN}{dN_{Cells}}",1,1.1,
							 labelData, colorCompare, kTRUE, 5, 5, kTRUE,
							 0.8,0.94,0.03,fCollisionSystem,plotDataSets,fClusters);
		SaveCanvas(canvas, Form("%s/Comparison/NCells_afterQA.%s", outputDir.Data(), suffix.Data()), kFALSE, kTRUE);

		DrawPeriodQACompareHistoRatioTH1(canvas,0.11, 0.02, 0.04, 0.11,kFALSE,kTRUE,kFALSE,
							 vecClusterNCells," ","N_{Cells} per Cluster","#frac{1}{N_{Events}} #frac{dN}{dN_{Cells}}",1,1.1,
							 labelData, colorCompare, kTRUE, 5, 5, kTRUE,
							 0.8,0.94,0.03,fCollisionSystem,plotDataSets,fClusters);
		SaveCanvas(canvas, Form("%s/Comparison/Ratios/NCells_afterQA.%s", outputDir.Data(), suffix.Data()));
//-----------------------------------
//-----------------------------------
		TGaxis::SetExponentOffset(-0.06, -0.04, "x");
		for(Int_t iVec=1; iVec<(Int_t)vecClusterEnergyFracCells.size(); iVec++){
			TH1D* temp = vecClusterEnergyFracCells.at(iVec);
			temp->Sumw2();
			temp->Add(vecClusterEnergyFracCells.at(0),-1);
			temp->GetXaxis()->SetRangeUser(0,nCaloCells);
			AdjustHistRange(temp,1.2,1.2,kTRUE);
			DrawPeriodQAHistoTH1(canvas,0.11, 0.02, 0.04, 0.11,kFALSE,kFALSE,kFALSE,
								 temp," ","Cell ID",Form("Difference between %s and Data #frac{dN}{dCellID}",plotDataSets[iVec].Data()),1,1,
								 0.75,0.92,0.03,fCollisionSystem,fClusters,"");
			SaveCanvasAndWriteHistogram(canvas, temp, Form("%s/Comparison/ClusterEnergyFracCells_%s.%s", outputDir.Data(), DataSets[iVec].Data(), suffix.Data()));
		}
		for(Int_t iVec=1; iVec<(Int_t)vecClusterIncludedCells.size(); iVec++){
			TH1D* temp = vecClusterIncludedCells.at(iVec);
			temp->Sumw2();
			temp->Add(vecClusterIncludedCells.at(0),-1);
			temp->GetXaxis()->SetRangeUser(0,nCaloCells);
			AdjustHistRange(temp,1.2,1.2,kTRUE);
			DrawPeriodQAHistoTH1(canvas,0.11, 0.02, 0.04, 0.11,kFALSE,kFALSE,kFALSE,
								 temp," ","Cell ID in accepted Clusters",Form("Difference between %s and Data #frac{d#it{N}}{d#it{Cell ID}}",plotDataSets[iVec].Data()),1,1,
								 0.75,0.92,0.03,fCollisionSystem,fClusters,"");
			SaveCanvasAndWriteHistogram(canvas, temp, Form("%s/Comparison/ClusterIncludedCells_%s.%s", outputDir.Data(), DataSets[iVec].Data(), suffix.Data()));
		}
		TGaxis::SetExponentOffset(0, 0, "x");
//-----------------------------------
//-----------------------------------
		TGaxis::SetExponentOffset(-0.06, 0.01, "x");

		for(Int_t iProj=0; iProj<2; iProj++){
			for(Int_t iVec=0; iVec<(Int_t)vecMatchingDeltaEtaPhi_matched[iProj].size(); iVec++){
				TH1D* temp = vecMatchingDeltaEtaPhi_matched[iProj].at(iVec);
				temp->Sumw2();
				Double_t nEntries = temp->GetEntries();
				temp->Scale(1/nEntries);
//				if(iVec==0) {
//					GetMinMaxBin(temp,minB,maxB);
//					temp->GetXaxis()->SetRange(minB-1,maxB+1);
//				}
			}
		}
		DrawPeriodQACompareHistoTH1(canvas,0.11, 0.02, 0.04, 0.11,kFALSE,kTRUE,kFALSE,
							 vecMatchingDeltaEtaPhi_matched[0]," ","#Delta#eta","#frac{1}{N} #frac{dN}{d#Delta#eta}",1,1.1,
							 labelData, colorCompare, kTRUE, 2, 2, kTRUE,
							 0.8,0.94,0.03,fCollisionSystem,plotDataSets,fClusters);
		SaveCanvas(canvas, Form("%s/Comparison/DeltaEta.%s", outputDir.Data(), suffix.Data()), kFALSE, kTRUE);
		DrawPeriodQACompareHistoTH1(canvas,0.11, 0.02, 0.04, 0.11,kFALSE,kTRUE,kFALSE,
							 vecMatchingDeltaEtaPhi_matched[1]," ","#Delta#phi","#frac{1}{N} #frac{dN}{d#Delta#phi}",1,1.1,
							 labelData, colorCompare, kTRUE, 2, 2, kTRUE,
							 0.8,0.94,0.03,fCollisionSystem,plotDataSets,fClusters);
		SaveCanvas(canvas, Form("%s/Comparison/DeltaPhi.%s", outputDir.Data(), suffix.Data()), kFALSE, kTRUE);

		DrawPeriodQACompareHistoRatioTH1(canvas,0.11, 0.02, 0.04, 0.11,kFALSE,kTRUE,kFALSE,
							 vecMatchingDeltaEtaPhi_matched[0]," ","#Delta#eta","#frac{1}{N} #frac{dN}{d#Delta#eta}",1,1.1,
							 labelData, colorCompare, kTRUE, 2, 2, kTRUE,
							 0.8,0.94,0.03,fCollisionSystem,plotDataSets,fClusters);
		SaveCanvas(canvas, Form("%s/Comparison/Ratios/DeltaEta.%s", outputDir.Data(), suffix.Data()));
		DrawPeriodQACompareHistoRatioTH1(canvas,0.11, 0.02, 0.04, 0.11,kFALSE,kTRUE,kFALSE,
							 vecMatchingDeltaEtaPhi_matched[1]," ","#Delta#phi","#frac{1}{N} #frac{dN}{d#Delta#phi}",1,1.1,
							 labelData, colorCompare, kTRUE, 2, 2, kTRUE,
							 0.8,0.94,0.03,fCollisionSystem,plotDataSets,fClusters);
		SaveCanvas(canvas, Form("%s/Comparison/Ratios/DeltaPhi.%s", outputDir.Data(), suffix.Data()));
//-----------------------------------
		for(Int_t iProj=0; iProj<2; iProj++){
			for(Int_t iVec=0; iVec<(Int_t)vecMatchingDeltaEtaPhi_allTracks[iProj].size(); iVec++){
				TH1D* temp = vecMatchingDeltaEtaPhi_allTracks[iProj].at(iVec);
				temp->Sumw2();
				Double_t nEntries = temp->GetEntries();
				temp->Scale(1/nEntries);
			}
		}
		DrawPeriodQACompareHistoTH1(canvas,0.11, 0.02, 0.04, 0.11,kFALSE,kTRUE,kFALSE,
							 vecMatchingDeltaEtaPhi_allTracks[0]," ","#Delta#eta","#frac{1}{N} #frac{dN}{d#Delta#eta}",1,1.1,
							 labelData, colorCompare, kTRUE, 2, 4, kTRUE,
							 0.8,0.94,0.03,fCollisionSystem,plotDataSets,fClusters);
		SaveCanvas(canvas, Form("%s/Comparison/DeltaEta_allTracks.%s", outputDir.Data(), suffix.Data()), kFALSE, kTRUE);
		DrawPeriodQACompareHistoTH1(canvas,0.11, 0.02, 0.04, 0.11,kFALSE,kTRUE,kFALSE,
							 vecMatchingDeltaEtaPhi_allTracks[1]," ","#Delta#phi","#frac{1}{N} #frac{dN}{d#Delta#phi}",1,1.1,
							 labelData, colorCompare, kTRUE, 2, 4, kTRUE,
							 0.8,0.94,0.03,fCollisionSystem,plotDataSets,fClusters);
		SaveCanvas(canvas, Form("%s/Comparison/DeltaPhi_allTracks.%s", outputDir.Data(), suffix.Data()), kFALSE, kTRUE);

		DrawPeriodQACompareHistoRatioTH1(canvas,0.11, 0.02, 0.04, 0.11,kFALSE,kTRUE,kFALSE,
							 vecMatchingDeltaEtaPhi_allTracks[0]," ","#Delta#eta","#frac{1}{N} #frac{dN}{d#Delta#eta}",1,1.1,
							 labelData, colorCompare, kTRUE, 2, 4, kTRUE,
							 0.8,0.94,0.03,fCollisionSystem,plotDataSets,fClusters);
		SaveCanvas(canvas, Form("%s/Comparison/Ratios/DeltaEta_allTracks.%s", outputDir.Data(), suffix.Data()));
		DrawPeriodQACompareHistoRatioTH1(canvas,0.11, 0.02, 0.04, 0.11,kFALSE,kTRUE,kFALSE,
							 vecMatchingDeltaEtaPhi_allTracks[1]," ","#Delta#phi","#frac{1}{N} #frac{dN}{d#Delta#phi}",1,1.1,
							 labelData, colorCompare, kTRUE, 2, 4, kTRUE,
							 0.8,0.94,0.03,fCollisionSystem,plotDataSets,fClusters);
		SaveCanvas(canvas, Form("%s/Comparison/Ratios/DeltaPhi_allTracks.%s", outputDir.Data(), suffix.Data()));
//-----------------------------------
		for(Int_t iCharge=0; iCharge<2; iCharge++){
			for(Int_t iProj=0; iProj<2; iProj++){
				for(Int_t iVec=0; iVec<(Int_t)vecMatchingDeltaEtaPhiTracksAll[iProj][iCharge].size(); iVec++){
					TH1D* temp = vecMatchingDeltaEtaPhiTracksAll[iProj][iCharge].at(iVec);
					temp->Sumw2();
					Double_t nEntries = temp->GetEntries();
					temp->Scale(1/nEntries);
				}
			}
			DrawPeriodQACompareHistoTH1(canvas,0.11, 0.02, 0.04, 0.11,kFALSE,kTRUE,kFALSE,
								 vecMatchingDeltaEtaPhiTracksAll[0][iCharge]," ","#Delta#eta","#frac{1}{N} #frac{dN}{d#Delta#eta}",1,1.1,
								 labelData, colorCompare, kTRUE, 2, 4, kTRUE,
								 0.8,0.94,0.03,fCollisionSystem,plotDataSets,fClusters);
			SaveCanvas(canvas, Form("%s/Comparison/DeltaEta_%s.%s", outputDir.Data(), charge[iCharge].Data(), suffix.Data()), kFALSE, kTRUE);
			DrawPeriodQACompareHistoTH1(canvas,0.11, 0.02, 0.04, 0.11,kFALSE,kTRUE,kFALSE,
								 vecMatchingDeltaEtaPhiTracksAll[1][iCharge]," ","#Delta#phi","#frac{1}{N} #frac{dN}{d#Delta#phi}",1,1.1,
								 labelData, colorCompare, kTRUE, 2, 4, kTRUE,
								 0.8,0.94,0.03,fCollisionSystem,plotDataSets,fClusters);
			SaveCanvas(canvas, Form("%s/Comparison/DeltaPhi_%s.%s", outputDir.Data(), charge[iCharge].Data(), suffix.Data()), kFALSE, kTRUE);
//-----------------------------------
			for(Int_t iProj=0; iProj<2; iProj++){
				for(Int_t iVec=0; iVec<(Int_t)vecMatchingDeltaEtaPhiTracksMatched[iProj][iCharge].size(); iVec++){
					TH1D* temp = vecMatchingDeltaEtaPhiTracksMatched[iProj][iCharge].at(iVec);
//					GetMinMaxBin(temp,minB,maxB);
//					temp->GetXaxis()->SetRange(minB-1,maxB+1);
					temp->Sumw2();
					Double_t nEntries = temp->GetEntries();
					temp->Scale(1/nEntries);
				}
			}
			DrawPeriodQACompareHistoTH1(canvas,0.11, 0.02, 0.04, 0.11,kFALSE,kTRUE,kFALSE,
								 vecMatchingDeltaEtaPhiTracksMatched[0][iCharge]," ","#Delta#eta","#frac{1}{N} #frac{dN}{d#Delta#eta}",1,1.1,
								 labelData, colorCompare, kTRUE, 2, 4, kTRUE,
								 0.8,0.94,0.03,fCollisionSystem,plotDataSets,fClusters);
			SaveCanvas(canvas, Form("%s/Comparison/DeltaEta_%s_matched.%s", outputDir.Data(), charge[iCharge].Data(), suffix.Data()), kFALSE, kTRUE);
			DrawPeriodQACompareHistoTH1(canvas,0.11, 0.02, 0.04, 0.11,kFALSE,kTRUE,kFALSE,
								 vecMatchingDeltaEtaPhiTracksMatched[1][iCharge]," ","#Delta#phi","#frac{1}{N} #frac{dN}{d#Delta#phi}",1,1.1,
								 labelData, colorCompare, kTRUE, 2, 4, kTRUE,
								 0.8,0.94,0.03,fCollisionSystem,plotDataSets,fClusters);
			SaveCanvas(canvas, Form("%s/Comparison/DeltaPhi_%s_matched.%s", outputDir.Data(), charge[iCharge].Data(), suffix.Data()), kFALSE, kTRUE);
//-----------------------------------
			for(Int_t iPt=0; iPt<3; iPt++){
				std::vector<TH1D*> tempProjections[2];
				for(Int_t iProj=0; iProj<2; iProj++){
					tempProjections[iProj].clear();
					for(Int_t iVec=0; iVec<(Int_t)vecMatchingDeltaEtaPhiTracksAllPt[iPt][iCharge].size(); iVec++){
						TH2D* temp = (TH2D*) vecMatchingDeltaEtaPhiTracksAllPt[iPt][iCharge].at(iVec);

						if(iProj==0) tempProjections[iProj].push_back(new TH1D(*(TH1D*) temp->ProjectionX(Form("ProjEtaCharge%i-%s-%i", iVec, charge[iCharge].Data(), iPt),1,300)));
						else if(iProj==1) tempProjections[iProj].push_back(new TH1D(*(TH1D*) temp->ProjectionY(Form("ProjPhiCharge%i-%s-%i", iVec, charge[iCharge].Data(), iPt),1,300)));
						tempProjections[iProj].at(iVec)->GetXaxis()->SetRange(1,300);
						tempProjections[iProj].at(iVec)->Sumw2();
						Double_t nEntries = tempProjections[iProj].at(iVec)->GetEntries();
						tempProjections[iProj].at(iVec)->Scale(1/nEntries);
					}
				}
				DrawPeriodQACompareHistoTH1(canvas,0.11, 0.02, 0.04, 0.11,kFALSE,kTRUE,kFALSE,
									 tempProjections[0]," ","#Delta#eta","#frac{1}{N} #frac{dN}{d#Delta#eta}",1,1.1,
									 labelData, colorCompare, kTRUE, 2, 4, kTRUE,
									 0.8,0.94,0.03,fCollisionSystem,plotDataSets,fClusters);
				SaveCanvas(canvas, Form("%s/Comparison/DeltaEta_%s_%i.%s", outputDir.Data(), charge[iCharge].Data(), iPt, suffix.Data()), kFALSE, kTRUE);
				DrawPeriodQACompareHistoTH1(canvas,0.11, 0.02, 0.04, 0.11,kFALSE,kTRUE,kFALSE,
									 tempProjections[1]," ","#Delta#phi","#frac{1}{N} #frac{dN}{d#Delta#phi}",1,1.1,
									 labelData, colorCompare, kTRUE, 2, 4, kTRUE,
									 0.8,0.94,0.03,fCollisionSystem,plotDataSets,fClusters);
				SaveCanvas(canvas, Form("%s/Comparison/DeltaPhi_%s_%i.%s", outputDir.Data(), charge[iCharge].Data(), iPt, suffix.Data()), kFALSE, kTRUE);
			}
//-----------------------------------
		}
		TGaxis::SetExponentOffset(0, 0, "x");
//-----------------------------------
//-----------------------------------
		for(Int_t iProj=0; iProj<2; iProj++){
			for(Int_t iVec=0; iVec<(Int_t)vecConvPhotonEtaPhi_Pi0[iProj].size(); iVec++){
				TH1D* temp = vecConvPhotonEtaPhi_Pi0[iProj].at(iVec);
				temp->Sumw2();
				Double_t nEntries = temp->GetEntries();
				temp->Scale(1/nEntries);
			}
		}
		DrawPeriodQACompareHistoTH1(canvas,0.11, 0.02, 0.04, 0.11,kFALSE,kTRUE,kFALSE,
							 vecConvPhotonEtaPhi_Pi0[1]," ","#eta_{#gamma_{conv} under #pi^{0}-peak}","#frac{1}{N_{Events}} #frac{dN}{d#eta}",1,1.1,
							 labelData, colorCompare, kTRUE, 2, 8, kTRUE,
							 0.8,0.94,0.03,fCollisionSystem,plotDataSets,fClusters);
		SaveCanvas(canvas, Form("%s/Comparison/ConvPhotonPi0_Eta.%s", outputDir.Data(), suffix.Data()), kFALSE, kTRUE);
		DrawPeriodQACompareHistoTH1(canvas,0.11, 0.02, 0.04, 0.11,kFALSE,kTRUE,kFALSE,
							 vecConvPhotonEtaPhi_Pi0[0]," ","#phi_{#gamma_{conv} under #pi^{0}-peak}","#frac{1}{N_{Events}} #frac{dN}{d#phi}",1,1.1,
							 labelData, colorCompare, kTRUE, 2, 16, kTRUE,
							 0.8,0.94,0.03,fCollisionSystem,plotDataSets,fClusters);
		SaveCanvas(canvas, Form("%s/Comparison/ConvPhotonPi0_Phi.%s", outputDir.Data(), suffix.Data()), kFALSE, kTRUE);

		DrawPeriodQACompareHistoRatioTH1(canvas,0.11, 0.02, 0.04, 0.11,kFALSE,kTRUE,kFALSE,
							 vecConvPhotonEtaPhi_Pi0[1]," ","#eta_{#gamma_{conv} under #pi^{0}-peak}","#frac{1}{N_{Events}} #frac{dN}{d#eta}",1,1.1,
							 labelData, colorCompare, kTRUE, 2, 8, kTRUE,
							 0.8,0.94,0.03,fCollisionSystem,plotDataSets,fClusters);
		SaveCanvas(canvas, Form("%s/Comparison/Ratios/ConvPhotonPi0_Eta.%s", outputDir.Data(), suffix.Data()));
		DrawPeriodQACompareHistoRatioTH1(canvas,0.11, 0.02, 0.04, 0.11,kFALSE,kTRUE,kFALSE,
							 vecConvPhotonEtaPhi_Pi0[0]," ","#phi_{#gamma_{conv} under #pi^{0}-peak}","#frac{1}{N_{Events}} #frac{dN}{d#phi}",1,1.1,
							 labelData, colorCompare, kTRUE, 2, 16, kTRUE,
							 0.8,0.94,0.03,fCollisionSystem,plotDataSets,fClusters);
		SaveCanvas(canvas, Form("%s/Comparison/Ratios/ConvPhotonPi0_Phi.%s", outputDir.Data(), suffix.Data()));
//-----------------------------------
		for(Int_t iProj=0; iProj<2; iProj++){
			for(Int_t iVec=0; iVec<(Int_t)vecConvPhotonEtaPhi_Eta[iProj].size(); iVec++){
				TH1D* temp = vecConvPhotonEtaPhi_Eta[iProj].at(iVec);
				temp->Sumw2();
				Double_t nEntries = temp->GetEntries();
				temp->Scale(1/nEntries);
			}
		}
		DrawPeriodQACompareHistoTH1(canvas,0.11, 0.02, 0.04, 0.11,kFALSE,kTRUE,kFALSE,
							 vecConvPhotonEtaPhi_Eta[1]," ","#eta_{#gamma_{conv} under #eta-peak}","#frac{1}{N_{Events}} #frac{dN}{d#eta}",1,1.1,
							 labelData, colorCompare, kTRUE, 2, 4, kTRUE,
							 0.8,0.94,0.03,fCollisionSystem,plotDataSets,fClusters);
		SaveCanvas(canvas, Form("%s/Comparison/ConvPhotonEta_Eta.%s", outputDir.Data(), suffix.Data()), kFALSE, kTRUE);
		DrawPeriodQACompareHistoTH1(canvas,0.11, 0.02, 0.04, 0.11,kFALSE,kTRUE,kFALSE,
							 vecConvPhotonEtaPhi_Eta[0]," ","#phi_{#gamma_{conv} under #eta-peak}","#frac{1}{N_{Events}} #frac{dN}{d#phi}",1,1.1,
							 labelData, colorCompare, kTRUE, 2, 8, kTRUE,
							 0.8,0.94,0.03,fCollisionSystem,plotDataSets,fClusters);
		SaveCanvas(canvas, Form("%s/Comparison/ConvPhotonEta_Phi.%s", outputDir.Data(), suffix.Data()), kFALSE, kTRUE);

		DrawPeriodQACompareHistoRatioTH1(canvas,0.11, 0.02, 0.04, 0.11,kFALSE,kTRUE,kFALSE,
							 vecConvPhotonEtaPhi_Eta[1]," ","#eta_{#gamma_{conv} under #eta-peak}","#frac{1}{N_{Events}} #frac{dN}{d#eta}",1,1.1,
							 labelData, colorCompare, kTRUE, 2, 4, kTRUE,
							 0.8,0.94,0.03,fCollisionSystem,plotDataSets,fClusters);
		SaveCanvas(canvas, Form("%s/Comparison/Ratios/ConvPhotonEta_Eta.%s", outputDir.Data(), suffix.Data()));
		DrawPeriodQACompareHistoRatioTH1(canvas,0.11, 0.02, 0.04, 0.11,kFALSE,kTRUE,kFALSE,
							 vecConvPhotonEtaPhi_Eta[0]," ","#phi_{#gamma_{conv} under #eta-peak}","#frac{1}{N_{Events}} #frac{dN}{d#phi}",1,1.1,
							 labelData, colorCompare, kTRUE, 2, 8, kTRUE,
							 0.8,0.94,0.03,fCollisionSystem,plotDataSets,fClusters);
		SaveCanvas(canvas, Form("%s/Comparison/Ratios/ConvPhotonEta_Phi.%s", outputDir.Data(), suffix.Data()));
//-----------------------------------
	}

//*****************************************************************************************************
//*****************************************************************************************************
//****************************** Create Output ROOT-File **********************************************
//*****************************************************************************************************
//*****************************************************************************************************

	if(doCellQA){
		cellQA = cellQAData;
		std::vector<TH2F*> DataMCHists;
		std::vector<TH2F*> DataMCHistsTime;
		for(Int_t j=0; j<nSets; j++){
			TH2F* fHistDataMCCell = (TH2F*)CaloExtQAContainer[j]->FindObject(Form("CellEnergyVsCellID %s", fClusterCutSelection[j].Data()));
			TH2F* fHistDataMCCellTime = (TH2F*)CaloExtQAContainer[j]->FindObject(Form("CellTimeVsCellID %s", fClusterCutSelection[j].Data()));
			DataMCHists.push_back(fHistDataMCCell);
			DataMCHistsTime.push_back(fHistDataMCCellTime);
		}

		vector<Int_t> allCells;
		CollectAndPlotBadCellCandidates(fLog, allCells, cellQA->cellIDsEnergy,"Energy - Mean/Sigma");
		CollectAndPlotBadCellCandidates(fLog, allCells, cellQA->cellIDsTime,"Time - Mean/Sigma");
		CollectAndPlotBadCellCandidates(fLog, allCells, cellQA->cellIDsHotCells1D,"HotCells1D");
		CheckBadCellCandidatesVec(DataMCHistsTime, cellQA->cellIDsHotCellsTime1D,"HotCellsTime1D");
		CollectAndPlotBadCellCandidates(fLog, allCells, cellQA->cellIDsHotCellsTime1D,"HotCellsTime1D");
		CollectAndPlotBadCellCandidates(fLog, allCells, cellQA->cellIDsHotCells2D,"HotCells2D");
		CollectAndPlotBadCellCandidates(fLog, allCells, cellQA->cellIDsMissing,"Missing MC-Data");

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
		fBadCells.open(Form("%s/Cells/%s.log",outputDir.Data(),DataSets[0].Data()), ios::out);
		for(Int_t iC=0; iC<(Int_t)allCells.size(); iC++){
			cout << allCells.at(iC) << ", ";
			fLog << allCells.at(iC) << ", ";
			fBadCells << allCells.at(iC) << endl;
		}
		fBadCells.close();
		cout << "\n++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;
		fLog << "\n++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;

		canvas->SetLeftMargin(0.1);canvas->SetRightMargin(0.1);canvas->SetTopMargin(0.06);canvas->SetBottomMargin(0.1);
		if((Int_t)allCells.size()>0){
			PlotBadCellReasons(cellQA,allCells,canvas,outputDir,suffix,fClusters,plotDataSets[0],DataSets[0],fCollisionSystem);

			PlotBadCellOverview(kTRUE,kFALSE,DataMCHists.at(0),allCells,canvas,outputDir,suffix,fClusters,plotDataSets[0],DataSets[0],fCollisionSystem);
			PlotBadCellOverview(kFALSE,kFALSE,DataMCHistsTime.at(0),allCells,canvas,outputDir,suffix,fClusters,plotDataSets[0],DataSets[0],fCollisionSystem);
			for(Int_t j=1; j<nSets; j++){
				PlotBadCellOverview(kTRUE,kTRUE,DataMCHists.at(j),allCells,canvas,outputDir,suffix,fClusters,plotDataSets[j],DataSets[j],fCollisionSystem);
				PlotBadCellOverview(kFALSE,kTRUE,DataMCHistsTime.at(j),allCells,canvas,outputDir,suffix,fClusters,plotDataSets[j],DataSets[j],fCollisionSystem);
			}
			canvas->SetLeftMargin(0.11);canvas->SetRightMargin(0.02);canvas->SetTopMargin(0.04);canvas->SetBottomMargin(0.11);
			PlotBadCellComparisonVec(DataMCHists,colorCompare,allCells,canvas,outputDir,suffix,fClusters,plotDataSets,fCollisionSystem);
		}

		char* nameOutput = Form("%s/%s/ClusterQA/ClusterQA_%s.root",fCutSelection[0].Data(),fEnergyFlag.Data(),DataSets[0].Data());
		TFile* fOutput = new TFile(nameOutput,"UPDATE");
		cout << "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;
		cout << "Reopening Output file: " << nameOutput << " to store BadCellCandidates" << endl;
		cout << "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;
		fLog << "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;
		fLog << "Reopening Output file: " << nameOutput << " to store BadCellCandidates" << endl;
		fLog << "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;

		SaveBadCellCandidates(cellQA->cellIDsEnergy,"Energy");
		SaveBadCellCandidates(cellQA->cellIDsTime,"Time");
		SaveBadCellCandidates(cellQA->cellIDsHotCells1D,"HotCells1D");
		SaveBadCellCandidates(cellQA->cellIDsHotCellsTime1D,"HotCellsTime1D");
		SaveBadCellCandidates(cellQA->cellIDsHotCells2D,"HotCells2D");
		SaveBadCellCandidates(cellQA->cellIDsMissing,"Missing");
		SaveBadCellCandidates(allCells,"allCells");

		fOutput->Write();
		fOutput->Close();
		delete fOutput;

		DataMCHists.clear();
		DataMCHistsTime.clear();
	}

	fLog.close();

	delete[] TrueContainer;
	delete[] ClusterContainer;
	delete[] CaloCutsContainer;
	delete[] ConvCutsContainer;
	delete[] CaloExtQAContainer;
	delete[] ESDContainer;
	delete[] TopContainer;
	delete[] TopDir;
	delete[] fFile;
	delete[] fOutput;
	delete cellQA;
	delete cvsQuadratic;
	delete canvas;

	cout << "Done with ClusterQA" << endl;
	cout << "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;

	return;

}//end
