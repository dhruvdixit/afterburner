#include "ClusterQA.h"

using namespace std;

void ClusterQARunwise(
				TString select = "LHC13bc",
				Int_t cutNr = -1, // if -1: you have to choose number at runtime
				Int_t doExtQA = 2,		// 0: switched off, 1: normal extQA, 2: with Cell level plots
				Bool_t doRange = kTRUE,
				Bool_t doEquidistantXaxis= kFALSE,
				Bool_t doTrigger = kTRUE,
				Bool_t doHistsForEverySet = kTRUE,
				TString suffix = "eps",
				Int_t mode = 2
				)
{
	cout << "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;
	cout << "ClusterQARunwise_pPb" << endl;
	cout << "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;

	gROOT->Reset();

	StyleSettingsThesis();
	SetPlotStyle();
//**************************************************************************************************************
	TString fEnergyFlag;
	TString fDate = ReturnDateString();
	TString fTextMeasurement = Form("#pi^{0} #rightarrow #gamma#gamma");

	std::vector<TString> vecDataSet;

	TString filePath, fileName, nameMainDir;

	const Int_t maxSets = 20;
	TString DataSets[maxSets];
	TString plotDataSets[maxSets];
	Style_t hMarkerStyle[maxSets];
	Size_t hMarkerSize[maxSets];
	Color_t hMarkerColor[maxSets];
	Color_t hLineColor[maxSets];
	Int_t nSets=0;
	Int_t nData=0;

	Bool_t doRunsFromDataLHC12 = kFALSE;

//choose which pp data set to process
//**************************************************************************************************************
	if(select.CompareTo("LHC13bc")==0){
	//LHC13bc
		doRange=kFALSE;
		doEquidistantXaxis=kTRUE;
		fEnergyFlag = "pPb_5.023TeV";
		filePath = "DataQA/20141208";
		fileName = "GammaConvCalo_8.root";
		nameMainDir = "GammaConvCalo_8";
		nSets = 6;
		nData = 2;
		DataSets[0]="LHC13b";DataSets[1]="LHC13c";DataSets[2]="LHC13b2_efix1";
		DataSets[3]="LHC13b2_efix2";DataSets[4]="LHC13b2_efix3";DataSets[5]="LHC13b2_efix4";
		plotDataSets[0]="LHC13b";plotDataSets[1]="LHC13c";plotDataSets[2]="DPMJET_p1";
		plotDataSets[3]="DPMJET_p2";plotDataSets[4]="DPMJET_p3";plotDataSets[5]="DPMJET_p4";
		for(Int_t iM=0;iM<nSets;iM++)hMarkerSize[iM]=3;
	}
//**************************************************************************************************************
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
	for(Int_t i=0; i<nSets; i++){
		vecDataSet.push_back(DataSets[i].Data());
		hMarkerStyle[i]=GetDefaultMarkerStyle(fEnergyFlag.Data(),DataSets[i].Data(),"");
		hMarkerColor[i]=GetColorDefaultColor(fEnergyFlag.Data(),DataSets[i].Data(),"");
		hLineColor[i]=GetColorDefaultColor(fEnergyFlag.Data(),DataSets[i].Data(),"");
	}

	Int_t fMode = mode;
	// mode:	0 // new output PCM-PCM
	//			1 // new output PCM dalitz
	//			2 // new output PCM-Calo
	//			3 // new output Calo-Calo
	//          4 // new output EMCAL-EMCAL
	//          5 // new output PHOS-PHOS
	//			9 // old output PCM-PCM
	if(fMode == 0 || fMode == 1 || fMode == 9){ cout << "Returning, given mode contains no calo information: " << fMode << endl; return;}

	if(nameMainDir.IsNull() || !nameMainDir.BeginsWith("Gamma")){cout << "ERROR, Unable to obtain valid name of MainDir:|" << nameMainDir.Data() << "|, running in mode: " << fMode << endl; return;}

	std::vector<TString> vecRuns;

//****************************** Determine which cut to process ************************************************
	TString fileRuns = Form("runNumbers%s.txt", (vecDataSet.at(0)).Data());
	if(!readin(fileRuns, vecRuns, kFALSE)) {cout << "ERROR, no Run Numbers could be found! Returning..." << endl; return;}
	TFile* fCutFile = new TFile(Form("%s/%s/%s/%s", filePath.Data(), ((TString)vecDataSet.at(0)).Data(), ((TString)vecRuns.at(0)).Data(), fileName.Data()));
	TList *listInput =(TList*)fCutFile->Get(nameMainDir.Data());
	vector <TString> cuts;
	for(Int_t i = 0; i<listInput->GetSize(); i++){
		TList *listCuts = (TList*)listInput->At(i);
		TString nameCuts = listCuts->GetName();
		if(nameCuts.BeginsWith("Cut Number")){
			nameCuts.Replace(0,11,"");
			cuts.push_back(nameCuts);
		}
	}
	cout << "The following cuts are available:" << endl;
	for(Int_t i = 0; i < (Int_t) cuts.size(); i++) {cout << Form("(%i) -- %s", i, cuts[i].Data()) << endl;}

	if(cutNr == -1){
		do{ cin >> cutNr;}
		while( (cutNr < 0) || (cutNr > (Int_t) cuts.size()) );
	}

	fCutFile->Delete();
	delete fCutFile;

	cout << "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;
	cout << "Processing Cut Number: " << cutNr << endl;
	cout << cuts.at(cutNr) << endl;
	cout << "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;
	cout << "Pictures are saved as " << suffix.Data() << "!" << endl;
	cout << "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;

	TString fCutSelection = cuts.at(cutNr);
	TString fEventCutSelection, fGammaCutSelection, fClusterCutSelection, fElectronCutSelection, fMesonCutSelection;
	ReturnSeparatedCutNumberAdvanced(fCutSelection, fEventCutSelection, fGammaCutSelection, fClusterCutSelection, fElectronCutSelection, fMesonCutSelection, fMode);

	TString calo;
	Int_t iCalo = 0;
	Int_t nCaloModules = 0;
	Int_t nCaloCells = 0;
	Double_t minClusE = ReturnMinClusterEnergy(fClusterCutSelection);
	Double_t minNCells = ReturnMinNCells(fClusterCutSelection);
	if(fClusterCutSelection.BeginsWith('1')){
		calo="EMCal"; iCalo=1;
		nCaloModules = 10;
		nCaloCells = 11520;
	}else if(fClusterCutSelection.BeginsWith('2')){
		calo="PHOS"; iCalo=2;
		nCaloModules = 5;
		nCaloCells = 6000;
	}else {cout << "No correct calorimeter type found: " << calo.Data() << ", returning..." << endl; return;}

	TString fCollisionSystem = ReturnFullCollisionsSystem(fEnergyFlag);
	if (fCollisionSystem.CompareTo("") == 0){
		cout << "No correct collision system specification, has been given" << endl;
		return;
	}

	TString fDetectionProcess = ReturnFullTextReconstructionProcess(fMode);

	TString outputDir = Form("%s/%s/ClusterQA/%s/Runwise",fCutSelection.Data(),fEnergyFlag.Data(),suffix.Data());
	gSystem->Exec("mkdir -p "+outputDir);

//****************************** Histograms ************************************************

	std::vector<TString> globalRuns;

	for(Int_t i=0; i<nSets; i++)
	{
		vecRuns.clear();
		fileRuns = Form("runNumbers%s.txt", vecDataSet.at(i).Data());
		if(doRunsFromDataLHC12 && i>=nData) {
			fileRuns = Form("runNumbers%s-%s.txt", vecDataSet.at(i).Data(),vecDataSet.at(0).Data());
			cout << "Switch doRunsFromDataLHC12 is true, reading runs from: " << fileRuns.Data() << endl;
		}
		if(!readin(fileRuns, vecRuns, kFALSE)) {cout << "ERROR, no Run Numbers could be found! Returning..." << endl; return;}

		for(Int_t j=0; j<(Int_t) vecRuns.size();j++)
		{
			if( i==0 ) globalRuns.push_back(vecRuns.at(j));
			else
			{
				Bool_t bFound = kFALSE;
				for(Int_t k=0; k<(Int_t) globalRuns.size();k++){ if(globalRuns.at(k)==vecRuns.at(j)) bFound=kTRUE;}
				if(!bFound) globalRuns.push_back(vecRuns.at(j));
			}
		}
	}

	selection_sort(globalRuns.begin(), globalRuns.end());

	map<TString,Int_t> mapBin;

	cout << "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;
	cout << "Processing following list of " << globalRuns.size() << " Runs:";
	for(Int_t i=0; i<(Int_t) globalRuns.size(); i++) {
		mapBin[globalRuns.at(i)]=i+1;
		if(i%10==0) cout << endl;
		cout << globalRuns.at(i) << ", ";
	}
	cout << endl;
	cout << "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;

	TH1D* hNEvents[nSets];

	TH1D* hTracksMeanGood[nSets];
	TH1D* hTracksRMSGood[nSets];

	TH1D* hConvNCandidates[nSets];
	TH1D* hConvNCandidatesQA[nSets];

	TH1D* hCaloNClusters[nSets];
	TH1D* hCaloNClustersQA[nSets];

	TH1D* hClusterMeanEnergy[nSets];
	TH1D* hClusterRMSEnergy[nSets];

	TH1D* hClusterEnergy01[nSets];
	TH1D* hClusterEnergy14[nSets];
	TH1D* hClusterEnergy4[nSets];

	TH1D* hClusterMeanNCells[nSets];
	TH1D* hClusterRMSNCells[nSets];

	TH1D* hClusterMeanDispersion[nSets];
	TH1D* hClusterRMSDispersion[nSets];

	TH1D* hClusterMeanM02[nSets];
	TH1D* hClusterRMSM02[nSets];

	TH1D* hClusterMeanR[nSets];
	TH1D* hClusterRMSR[nSets];

	TH1D* hClusterMeanTime[nSets];
	TH1D* hClusterRMSTime[nSets];

	TH1D* hClusterFractionMatches[nSets];
	TH1D* hClusterFractionMatchesS[nSets];
	TH1D* hClusterFractionMatchesM[nSets];
	TH1D* hClusterFractionMatchesH[nSets];

	TH1D* hClusterMeanDeltaEta[nSets];
	TH1D* hClusterMeanDeltaPhi[nSets];
	TH1D* hClusterRMSDeltaEta[nSets];
	TH1D* hClusterRMSDeltaPhi[nSets];

	TH1D* hClusterMeanM20[nSets];
	TH1D* hClusterRMSM20[nSets];

	std::vector<TString> vecBadCells[nSets];

	std::vector<TH2D*> vecClusterEtaPhi[nSets];
	std::vector<TH2D*> vecClusterEVsNCells[nSets];
	std::vector<TH1D*> vecClusterIncludedCells[nSets];
	std::vector<TH1D*> vecClusterIncludedCellsBefore[nSets];
	std::vector<TH1D*> vecClusterEFracCells[nSets];
	std::vector<TH1D*> vecClusterEFracCellsBefore[nSets];
	std::vector<TH2D*> vecClusterEnergyMeanSigma[nSets];
	std::vector<TH2D*> vecClusterTimeMeanSigma[nSets];

	std::vector<TH1D*> vecClusterEnergy[nSets];
	std::vector<TH1D*> vecClusterM02[nSets];
	std::vector<TH1D*> vecClusterM20[nSets];
	std::vector<TH1D*> vecClusterNCells[nSets];
	std::vector<TH1D*> vecClusterDispersion[nSets];
	std::vector<TH1D*> vecClusterTime[nSets];
	std::vector<TH1D*> vecClusterDeltaEta[nSets];
	std::vector<TH1D*> vecClusterDeltaPhi[nSets];
	std::vector<TH1D*> vecClusterPi0ConvPhotonEta[nSets];
	std::vector<TH1D*> vecClusterPi0ConvPhotonPhi[nSets];
	std::vector<TH1D*> vecClusterEtaConvPhotonEta[nSets];
	std::vector<TH1D*> vecClusterEtaConvPhotonPhi[nSets];

	std::vector<TH1D*> vecBadCellsEnergy[nSets];
	std::vector<TH1D*> vecBadCellsTime[nSets];

	std::vector<TH1D*> vecClusterEVsModule[nSets][nCaloModules];
	std::vector<TH1D*> vecModuleEVsModule[nSets][nCaloModules];
	std::vector<TH1D*> vecClusterNCells100VsModule[nSets][nCaloModules];
	std::vector<TH1D*> vecClusterNCells1500VsModule[nSets][nCaloModules];

	Int_t hFBin;
	Int_t hLBin;
	Int_t hNBin;

	if(doEquidistantXaxis)
	{
		hFBin = 0;
		hLBin = globalRuns.size();
		hNBin = globalRuns.size();
	}
	else
	{
		if(nSets>2){
			hFBin = ((TString) globalRuns.at(0)).Atoi() - 500;
			hLBin = ((TString) globalRuns.at(globalRuns.size()-1)).Atoi()  + 500;
			hNBin = hLBin - hFBin;
		}else{
			hFBin = ((TString) globalRuns.at(0)).Atoi() - 25;
			hLBin = ((TString) globalRuns.at(globalRuns.size()-1)).Atoi()  + 25;
			hNBin = hLBin - hFBin;
		}
	}

	std::vector<TH1D*> vecHistos[nSets];
	std::vector<TString> vecHistosName;
	TString histoName;

	for(Int_t i=0; i<nSets; i++)
	{
		histoName = "hNEvents";
		if(i==0) vecHistosName.push_back(histoName); //h==0
		hNEvents[i] = new TH1D(Form("%s_%s", histoName.Data(), DataSets[i].Data()),"hNEvents; Run Number ; # of Events",hNBin,hFBin,hLBin);
		if(doRange){
			if(iCalo==1) hNEvents[i]->GetYaxis()->SetRangeUser(1, 1E8);
			if(iCalo==2) hNEvents[i]->GetYaxis()->SetRangeUser(1, 1E8);
		}
		EditTH1(globalRuns, doEquidistantXaxis, hNEvents[i], hMarkerStyle[i], hMarkerSize[i], hMarkerColor[i], hLineColor[i]);
		vecHistos[i].push_back(hNEvents[i]);

		histoName = "hTracksGood-Mean";
		if(i==0) vecHistosName.push_back(histoName); //h==1
		hTracksMeanGood[i] = new TH1D(Form("%s_%s", histoName.Data(), DataSets[i].Data()),"hTracksMeanGood; Run Number ; #bar{#lower[0.1]{N}}_{Good Tracks}",hNBin,hFBin,hLBin);
		if(doRange){
			if(iCalo==1) hTracksMeanGood[i]->GetYaxis()->SetRangeUser(3.5, 5);
			if(iCalo==2) hTracksMeanGood[i]->GetYaxis()->SetRangeUser(3.5, 5);
		}
		EditTH1(globalRuns, doEquidistantXaxis, hTracksMeanGood[i], hMarkerStyle[i], hMarkerSize[i], hMarkerColor[i], hLineColor[i]);
		vecHistos[i].push_back(hTracksMeanGood[i]);
		histoName = "hTracksGood-RMS";
		if(i==0) vecHistosName.push_back(histoName); //h==2
		hTracksRMSGood[i] = new TH1D(Form("%s_%s", histoName.Data(), DataSets[i].Data()),"hTracksRMSGood; Run Number ; #sigma_{N_{Good Tracks}}",hNBin,hFBin,hLBin);
		if(doRange){
			if(iCalo==1) hTracksRMSGood[i]->GetYaxis()->SetRangeUser(3.2, 5);
			if(iCalo==2) hTracksRMSGood[i]->GetYaxis()->SetRangeUser(3.2, 5);
		}
		EditTH1(globalRuns, doEquidistantXaxis, hTracksRMSGood[i], hMarkerStyle[i], hMarkerSize[i], hMarkerColor[i], hLineColor[i]);
		vecHistos[i].push_back(hTracksRMSGood[i]);

		histoName = "hConvNCandidates";
		if(i==0) vecHistosName.push_back(histoName); //h==3
		hConvNCandidates[i] = new TH1D(Form("%s_%s", histoName.Data(), DataSets[i].Data()),"hConvNCandidates; Run Number ; #frac{1}{N_{Events}} N_{#gamma_{conv}, Candidates before Cuts}",hNBin,hFBin,hLBin);
		if(doRange){
			if(iCalo==1) hConvNCandidates[i]->GetYaxis()->SetRangeUser(0.05, 0.25);
			if(iCalo==2) hConvNCandidates[i]->GetYaxis()->SetRangeUser(0.05, 0.25);
		}
		EditTH1(globalRuns, doEquidistantXaxis, hConvNCandidates[i], hMarkerStyle[i], hMarkerSize[i], hMarkerColor[i], hLineColor[i]);
		vecHistos[i].push_back(hConvNCandidates[i]);
		histoName = "hConvNCandidatesQA";
		if(i==0) vecHistosName.push_back(histoName); //h==4
		hConvNCandidatesQA[i] = new TH1D(Form("%s_%s", histoName.Data(), DataSets[i].Data()),"hConvNCandidatesQA; Run Number ; #frac{1}{N_{Events}} N_{#gamma_{conv}, Candidates}",hNBin,hFBin,hLBin);
		if(doRange){
			if(iCalo==1) hConvNCandidatesQA[i]->GetYaxis()->SetRangeUser(0.06, 0.12);
			if(iCalo==2) hConvNCandidatesQA[i]->GetYaxis()->SetRangeUser(0.06, 0.12);
		}
		EditTH1(globalRuns, doEquidistantXaxis, hConvNCandidatesQA[i], hMarkerStyle[i], hMarkerSize[i], hMarkerColor[i], hLineColor[i]);
		vecHistos[i].push_back(hConvNCandidatesQA[i]);

		histoName = "hCaloNClusters";
		if(i==0) vecHistosName.push_back(histoName); //h==5
		hCaloNClusters[i] = new TH1D(Form("%s_%s", histoName.Data(), DataSets[i].Data()),"hCaloNClusters; Run Number ; #frac{1}{N_{Events}} N_{Clusters before Cuts}",hNBin,hFBin,hLBin);
		if(doRange){
			if(iCalo==1) hCaloNClusters[i]->GetYaxis()->SetRangeUser(0.3, 0.5);
			if(iCalo==2) hCaloNClusters[i]->GetYaxis()->SetRangeUser(0.3, 0.5);
		}
		EditTH1(globalRuns, doEquidistantXaxis, hCaloNClusters[i], hMarkerStyle[i], hMarkerSize[i], hMarkerColor[i], hLineColor[i]);
		vecHistos[i].push_back(hCaloNClusters[i]);
		histoName = "hCaloNClustersQA";
		if(i==0) vecHistosName.push_back(histoName); //h==6
		hCaloNClustersQA[i] = new TH1D(Form("%s_%s", histoName.Data(), DataSets[i].Data()),"hCaloNClustersQA; Run Number ; #frac{1}{N_{Events}} N_{Clusters}",hNBin,hFBin,hLBin);
		if(doRange){
			if(iCalo==1) hCaloNClustersQA[i]->GetYaxis()->SetRangeUser(0.15, 0.24);
			if(iCalo==2) hCaloNClustersQA[i]->GetYaxis()->SetRangeUser(0.15, 0.24);
		}
		EditTH1(globalRuns, doEquidistantXaxis, hCaloNClustersQA[i], hMarkerStyle[i], hMarkerSize[i], hMarkerColor[i], hLineColor[i]);
		vecHistos[i].push_back(hCaloNClustersQA[i]);

		histoName = "hClusterEnergy-Mean";
		if(i==0) vecHistosName.push_back(histoName); //h==7
		hClusterMeanEnergy[i] = new TH1D(Form("%s_%s", histoName.Data(), DataSets[i].Data()),"hClusterMeanEnergy; Run Number ; #bar{#lower[0.1]{E}}_{Cluster} (GeV)",hNBin,hFBin,hLBin);
		if(doRange){
			if(iCalo==1) hClusterMeanEnergy[i]->GetYaxis()->SetRangeUser(0.75, 0.84);
			if(iCalo==2) hClusterMeanEnergy[i]->GetYaxis()->SetRangeUser(0.75, 0.84);
		}
		EditTH1(globalRuns, doEquidistantXaxis, hClusterMeanEnergy[i], hMarkerStyle[i], hMarkerSize[i], hMarkerColor[i], hLineColor[i]);
		vecHistos[i].push_back(hClusterMeanEnergy[i]);
		histoName = "hClusterEnergy-RMS";
		if(i==0) vecHistosName.push_back(histoName); //h==8
		hClusterRMSEnergy[i] = new TH1D(Form("%s_%s", histoName.Data(), DataSets[i].Data()),"hClusterRMSEnergy; Run Number ; #sigma_{E_{Cluster}} (GeV)",hNBin,hFBin,hLBin);
		if(doRange){
			if(iCalo==1) hClusterRMSEnergy[i]->GetYaxis()->SetRangeUser(0.41, 0.46);
			if(iCalo==2) hClusterRMSEnergy[i]->GetYaxis()->SetRangeUser(0.41, 0.46);
		}
		EditTH1(globalRuns, doEquidistantXaxis, hClusterRMSEnergy[i], hMarkerStyle[i], hMarkerSize[i], hMarkerColor[i], hLineColor[i]);
		vecHistos[i].push_back(hClusterRMSEnergy[i]);

		histoName = "hClusterEnergy-01";
		if(i==0) vecHistosName.push_back(histoName); //h==9
		hClusterEnergy01[i] = new TH1D(Form("%s_%s", histoName.Data(), DataSets[i].Data()),"hClusterEnergy01; Run Number ; #frac{1}{N_{Events}} N_{Clusters, E<1 GeV}",hNBin,hFBin,hLBin);
		if(doRange){
			if(iCalo==1) hClusterEnergy01[i]->GetYaxis()->SetRangeUser(0.1, 0.2);
			if(iCalo==2) hClusterEnergy01[i]->GetYaxis()->SetRangeUser(0.1, 0.2);
		}
		EditTH1(globalRuns, doEquidistantXaxis, hClusterEnergy01[i], hMarkerStyle[i], hMarkerSize[i], hMarkerColor[i], hLineColor[i]);
		vecHistos[i].push_back(hClusterEnergy01[i]);
		histoName = "hClusterEnergy-14";
		if(i==0) vecHistosName.push_back(histoName); //h==10
		hClusterEnergy14[i] = new TH1D(Form("%s_%s", histoName.Data(), DataSets[i].Data()),"hClusterEnergy14; Run Number ; #frac{1}{N_{Events}} N_{Clusters, 1<E<4 GeV}",hNBin,hFBin,hLBin);
		if(doRange){
			if(iCalo==1) hClusterEnergy14[i]->GetYaxis()->SetRangeUser(0.01, 0.06);
			if(iCalo==2) hClusterEnergy14[i]->GetYaxis()->SetRangeUser(0.01, 0.06);
		}
		EditTH1(globalRuns, doEquidistantXaxis, hClusterEnergy14[i], hMarkerStyle[i], hMarkerSize[i], hMarkerColor[i], hLineColor[i]);
		vecHistos[i].push_back(hClusterEnergy14[i]);
		histoName = "hClusterEnergy-4";
		if(i==0) vecHistosName.push_back(histoName); //h==11
		hClusterEnergy4[i] = new TH1D(Form("%s_%s", histoName.Data(), DataSets[i].Data()),"hClusterEnergy4; Run Number ; #frac{1}{N_{Events}} N_{Clusters, E>4 GeV}",hNBin,hFBin,hLBin);
		if(doRange){
			if(iCalo==1) hClusterEnergy4[i]->GetYaxis()->SetRangeUser(0, 0.0005);
			if(iCalo==2) hClusterEnergy4[i]->GetYaxis()->SetRangeUser(0, 0.0005);
		}
		EditTH1(globalRuns, doEquidistantXaxis, hClusterEnergy4[i], hMarkerStyle[i], hMarkerSize[i], hMarkerColor[i], hLineColor[i]);
		vecHistos[i].push_back(hClusterEnergy4[i]);

		histoName = "hClusterNCells-Mean";
		if(i==0) vecHistosName.push_back(histoName); //h==12
		hClusterMeanNCells[i] = new TH1D(Form("%s_%s", histoName.Data(), DataSets[i].Data()),"hClusterMeanNCells; Run Number ; #bar{#lower[0.1]{N}}_{Cells, Cluster}",hNBin,hFBin,hLBin);
		if(doRange){
			if(iCalo==1) hClusterMeanNCells[i]->GetYaxis()->SetRangeUser(2.3, 2.45);
			if(iCalo==2) hClusterMeanNCells[i]->GetYaxis()->SetRangeUser(2.3, 2.45);
		}
		EditTH1(globalRuns, doEquidistantXaxis, hClusterMeanNCells[i], hMarkerStyle[i], hMarkerSize[i], hMarkerColor[i], hLineColor[i]);
		vecHistos[i].push_back(hClusterMeanNCells[i]);
		histoName = "hClusterNCells-RMS";
		if(i==0) vecHistosName.push_back(histoName); //h==13
		hClusterRMSNCells[i] = new TH1D(Form("%s_%s", histoName.Data(), DataSets[i].Data()),"hClusterRMSNCells; Run Number ; #sigma_{N_{Cells, Cluster}}",hNBin,hFBin,hLBin);
		if(doRange){
			if(iCalo==1) hClusterRMSNCells[i]->GetYaxis()->SetRangeUser(0.62, 0.74);
			if(iCalo==2) hClusterRMSNCells[i]->GetYaxis()->SetRangeUser(0.62, 0.74);
		}
		EditTH1(globalRuns, doEquidistantXaxis, hClusterRMSNCells[i], hMarkerStyle[i], hMarkerSize[i], hMarkerColor[i], hLineColor[i]);
		vecHistos[i].push_back(hClusterRMSNCells[i]);

		histoName = "hClusterDispersion-Mean";
		if(i==0) vecHistosName.push_back(histoName); //h==14
		hClusterMeanDispersion[i] = new TH1D(Form("%s_%s", histoName.Data(), DataSets[i].Data()),"hClusterMeanDispersion; Run Number ; #bar{#lower[0.1]{Dispersion}}_{Cluster}",hNBin,hFBin,hLBin);
		if(doRange){
			if(iCalo==1) hClusterMeanDispersion[i]->GetYaxis()->SetRangeUser(0.52, 0.55);
			if(iCalo==2) hClusterMeanDispersion[i]->GetYaxis()->SetRangeUser(0.52, 0.55);
		}
		EditTH1(globalRuns, doEquidistantXaxis, hClusterMeanDispersion[i], hMarkerStyle[i], hMarkerSize[i], hMarkerColor[i], hLineColor[i]);
		vecHistos[i].push_back(hClusterMeanDispersion[i]);
		histoName = "hClusterDispersion-RMS";
		if(i==0) vecHistosName.push_back(histoName); //h==15
		hClusterRMSDispersion[i] = new TH1D(Form("%s_%s", histoName.Data(), DataSets[i].Data()),"hClusterRMSDispersion; Run Number ; #sigma_{Dispersion_{Cluster}}",hNBin,hFBin,hLBin);
		if(doRange){
			if(iCalo==1) hClusterRMSDispersion[i]->GetYaxis()->SetRangeUser(0.07, 0.1);
			if(iCalo==2) hClusterRMSDispersion[i]->GetYaxis()->SetRangeUser(0.07, 0.1);
		}
		EditTH1(globalRuns, doEquidistantXaxis, hClusterRMSDispersion[i], hMarkerStyle[i], hMarkerSize[i], hMarkerColor[i], hLineColor[i]);
		vecHistos[i].push_back(hClusterRMSDispersion[i]);

		histoName = "hClusterM02-Mean";
		if(i==0) vecHistosName.push_back(histoName); //h==16
		hClusterMeanM02[i] = new TH1D(Form("%s_%s", histoName.Data(), DataSets[i].Data()),"hClusterMeanM02; Run Number ; #bar{#lower[0.1]{#lambda_{0}^{2}}}",hNBin,hFBin,hLBin);
		if(doRange){
			if(iCalo==1) hClusterMeanM02[i]->GetYaxis()->SetRangeUser(0.25, 0.265);
			if(iCalo==2) hClusterMeanM02[i]->GetYaxis()->SetRangeUser(0.25, 0.265);
		}
		EditTH1(globalRuns, doEquidistantXaxis, hClusterMeanM02[i], hMarkerStyle[i], hMarkerSize[i], hMarkerColor[i], hLineColor[i]);
		vecHistos[i].push_back(hClusterMeanM02[i]);
		histoName = "hClusterM02-RMS";
		if(i==0) vecHistosName.push_back(histoName); //h==17
		hClusterRMSM02[i] = new TH1D(Form("%s_%s", histoName.Data(), DataSets[i].Data()),"hClusterRMSM02; Run Number ; #sigma_{#lambda_{0}^{2}}",hNBin,hFBin,hLBin);
		if(doRange){
			if(iCalo==1) hClusterRMSM02[i]->GetYaxis()->SetRangeUser(0.04, 0.055);
			if(iCalo==2) hClusterRMSM02[i]->GetYaxis()->SetRangeUser(0.04, 0.055);
		}
		EditTH1(globalRuns, doEquidistantXaxis, hClusterRMSM02[i], hMarkerStyle[i], hMarkerSize[i], hMarkerColor[i], hLineColor[i]);
		vecHistos[i].push_back(hClusterRMSM02[i]);

		histoName = "hClusterR-Mean";
		if(i==0) vecHistosName.push_back(histoName); //h==18
		hClusterMeanR[i] = new TH1D(Form("%s_%s", histoName.Data(), DataSets[i].Data()),"hClusterMeanR; Run Number ; #bar{#lower[0.1]{R}}_{Cluster}",hNBin,hFBin,hLBin);
		if(doRange){
			if(iCalo==1) hClusterMeanR[i]->GetYaxis()->SetRangeUser(441, 441.6);
			if(iCalo==2) hClusterMeanR[i]->GetYaxis()->SetRangeUser(461, 462);
		}
		EditTH1(globalRuns, doEquidistantXaxis, hClusterMeanR[i], hMarkerStyle[i], hMarkerSize[i], hMarkerColor[i], hLineColor[i]);
		vecHistos[i].push_back(hClusterMeanR[i]);
		histoName = "hClusterR-RMS";
		if(i==0) vecHistosName.push_back(histoName); //h==19
		hClusterRMSR[i] = new TH1D(Form("%s_%s", histoName.Data(), DataSets[i].Data()),"hClusterRMSR; Run Number ; #sigma_{R_{Cluster}}",hNBin,hFBin,hLBin);
		if(doRange){
			if(iCalo==1) hClusterRMSR[i]->GetYaxis()->SetRangeUser(2.4, 2.65);
			if(iCalo==2) hClusterRMSR[i]->GetYaxis()->SetRangeUser(1.2, 1.7);
		}
		EditTH1(globalRuns, doEquidistantXaxis, hClusterRMSR[i], hMarkerStyle[i], hMarkerSize[i], hMarkerColor[i], hLineColor[i]);
		vecHistos[i].push_back(hClusterRMSR[i]);

		histoName = "hClusterTime-Mean";
		if(i==0) vecHistosName.push_back(histoName); //h==20
		hClusterMeanTime[i] = new TH1D(Form("%s_%s", histoName.Data(), DataSets[i].Data()),"hClusterMeanTime; Run Number ; #bar{#lower[0.1]{t}}_{Cluster} (s)",hNBin,hFBin,hLBin);
		if(doRange){
			if(iCalo==1) hClusterMeanTime[i]->GetYaxis()->SetRangeUser(1E-9, 1E-5);
			if(iCalo==2) hClusterMeanTime[i]->GetYaxis()->SetRangeUser(-2E-8, 1.2E-7);
		}
		EditTH1(globalRuns, doEquidistantXaxis, hClusterMeanTime[i], hMarkerStyle[i], hMarkerSize[i], hMarkerColor[i], hLineColor[i]);
		vecHistos[i].push_back(hClusterMeanTime[i]);
		histoName = "hClusterTime-RMS";
		if(i==0) vecHistosName.push_back(histoName); //h==21
		hClusterRMSTime[i] = new TH1D(Form("%s_%s", histoName.Data(), DataSets[i].Data()),"hClusterRMSTime; Run Number ; #sigma_{t_{Cluster}} (s)",hNBin,hFBin,hLBin);
		if(doRange){
			if(iCalo==1) hClusterRMSTime[i]->GetYaxis()->SetRangeUser(1E-9, 10E-9);
			if(iCalo==2) hClusterRMSTime[i]->GetYaxis()->SetRangeUser(1.5E-8, 3E-8);
		}
		EditTH1(globalRuns, doEquidistantXaxis, hClusterRMSTime[i], hMarkerStyle[i], hMarkerSize[i], hMarkerColor[i], hLineColor[i]);
		vecHistos[i].push_back(hClusterRMSTime[i]);

		histoName = "hCluster-FractionMatches";
		if(i==0) vecHistosName.push_back(histoName); //h==22
		hClusterFractionMatches[i] = new TH1D(Form("%s_%s", histoName.Data(), DataSets[i].Data()),"hClusterFractionMatches; Run Number ; #frac{N_{Removed Mother Candidates by Cluster-Track Matching}}{N_{Mother Candidates}}",hNBin,hFBin,hLBin);
		if(doRange){
			if(iCalo==1) hClusterFractionMatches[i]->GetYaxis()->SetRangeUser(0.04, 0.09);
			if(iCalo==2) hClusterFractionMatches[i]->GetYaxis()->SetRangeUser(0.04, 0.09);
		}
		EditTH1(globalRuns, doEquidistantXaxis, hClusterFractionMatches[i], hMarkerStyle[i], hMarkerSize[i], hMarkerColor[i], hLineColor[i]);
		vecHistos[i].push_back(hClusterFractionMatches[i]);
		histoName = "hCluster-FractionMatchesS";
		if(i==0) vecHistosName.push_back(histoName); //h==23
		hClusterFractionMatchesS[i] = new TH1D(Form("%s_%s", histoName.Data(), DataSets[i].Data()),"hClusterFractionMatchesS; Run Number ; #frac{N_{Removed Mother Candidates by Cluster-Track Matching}}{N_{Mother Candidates}} #scale[0.8]{for #it{p}_{T,Pair}<1.5 GeV/#it{c}}",hNBin,hFBin,hLBin);
		if(doRange){
			if(iCalo==1) hClusterFractionMatchesS[i]->GetYaxis()->SetRangeUser(0, 0.04);
			if(iCalo==2) hClusterFractionMatchesS[i]->GetYaxis()->SetRangeUser(0, 0.04);
		}
		EditTH1(globalRuns, doEquidistantXaxis, hClusterFractionMatchesS[i], hMarkerStyle[i], hMarkerSize[i], hMarkerColor[i], hLineColor[i]);
		vecHistos[i].push_back(hClusterFractionMatchesS[i]);
		histoName = "hCluster-FractionMatchesM";
		if(i==0) vecHistosName.push_back(histoName); //h==24
		hClusterFractionMatchesM[i] = new TH1D(Form("%s_%s", histoName.Data(), DataSets[i].Data()),"hClusterFractionMatchesM; Run Number ; #frac{N_{Removed Mother Candidates by Cluster-Track Matching}}{N_{Mother Candidates}} #scale[0.8]{for 1.5<#it{p}_{T,Pair}<2.5 GeV/#it{c}}",hNBin,hFBin,hLBin);
		if(doRange){
			if(iCalo==1) hClusterFractionMatchesM[i]->GetYaxis()->SetRangeUser(0.1, 0.25);
			if(iCalo==2) hClusterFractionMatchesM[i]->GetYaxis()->SetRangeUser(0.1, 0.25);
		}
		EditTH1(globalRuns, doEquidistantXaxis, hClusterFractionMatchesM[i], hMarkerStyle[i], hMarkerSize[i], hMarkerColor[i], hLineColor[i]);
		vecHistos[i].push_back(hClusterFractionMatchesM[i]);
		histoName = "hCluster-FractionMatchesH";
		if(i==0) vecHistosName.push_back(histoName); //h==25
		hClusterFractionMatchesH[i] = new TH1D(Form("%s_%s", histoName.Data(), DataSets[i].Data()),"hClusterFractionMatchesH; Run Number ; #frac{N_{Removed Mother Candidates by Cluster-Track Matching}}{N_{Mother Candidates}} #scale[0.8]{for #it{p}_{T,Pair}>2.5 GeV/#it{c}}",hNBin,hFBin,hLBin);
		if(doRange){
			if(iCalo==1) hClusterFractionMatchesH[i]->GetYaxis()->SetRangeUser(0.25, 0.5);
			if(iCalo==2) hClusterFractionMatchesH[i]->GetYaxis()->SetRangeUser(0.25, 0.5);
		}
		EditTH1(globalRuns, doEquidistantXaxis, hClusterFractionMatchesH[i], hMarkerStyle[i], hMarkerSize[i], hMarkerColor[i], hLineColor[i]);
		vecHistos[i].push_back(hClusterFractionMatchesH[i]);


		histoName = "hClusterDeltaEta-Mean";
		if(i==0) vecHistosName.push_back(histoName); //h==26
		hClusterMeanDeltaEta[i] = new TH1D(Form("%s_%s", histoName.Data(), DataSets[i].Data()),"hClusterMeanDeltaEta; Run Number ; #bar{#lower[0.1]{#Delta#eta}}_{Cluster, Tracks}",hNBin,hFBin,hLBin);
		if(doRange){
			if(iCalo==1) hClusterMeanDeltaEta[i]->GetYaxis()->SetRangeUser(-0.03, 0.03);
			if(iCalo==2) hClusterMeanDeltaEta[i]->GetYaxis()->SetRangeUser(-0.03, 0.03);
		}
		EditTH1(globalRuns, doEquidistantXaxis, hClusterMeanDeltaEta[i], hMarkerStyle[i], hMarkerSize[i], hMarkerColor[i], hLineColor[i]);
		vecHistos[i].push_back(hClusterMeanDeltaEta[i]);
		histoName = "hClusterDeltaPhi-Mean";
		if(i==0) vecHistosName.push_back(histoName); //h==27
		hClusterMeanDeltaPhi[i] = new TH1D(Form("%s_%s", histoName.Data(), DataSets[i].Data()),"hClusterMeanDeltaPhi; Run Number ; #bar{#lower[0.1]{#Delta#phi}}_{Cluster, Tracks}",hNBin,hFBin,hLBin);
		if(doRange){
			if(iCalo==1) hClusterMeanDeltaPhi[i]->GetYaxis()->SetRangeUser(-0.03, 0.03);
			if(iCalo==2) hClusterMeanDeltaPhi[i]->GetYaxis()->SetRangeUser(-0.03, 0.03);
		}
		EditTH1(globalRuns, doEquidistantXaxis, hClusterMeanDeltaPhi[i], hMarkerStyle[i], hMarkerSize[i], hMarkerColor[i], hLineColor[i]);
		vecHistos[i].push_back(hClusterMeanDeltaPhi[i]);
		histoName = "hClusterDeltaEta-RMS";
		if(i==0) vecHistosName.push_back(histoName); //h==28
		hClusterRMSDeltaEta[i] = new TH1D(Form("%s_%s", histoName.Data(), DataSets[i].Data()),"hClusterRMSDeltaEta; Run Number ; #sigma_{#Delta#eta_{Cluster, Tracks}}",hNBin,hFBin,hLBin);
		if(doRange){
			if(iCalo==1) hClusterRMSDeltaEta[i]->GetYaxis()->SetRangeUser(0.05, 0.15);
			if(iCalo==2) hClusterRMSDeltaEta[i]->GetYaxis()->SetRangeUser(0.05, 0.15);
		}
		EditTH1(globalRuns, doEquidistantXaxis, hClusterRMSDeltaEta[i], hMarkerStyle[i], hMarkerSize[i], hMarkerColor[i], hLineColor[i]);
		vecHistos[i].push_back(hClusterRMSDeltaEta[i]);
		histoName = "hClusterDeltaPhi-RMS";
		if(i==0) vecHistosName.push_back(histoName); //h==29
		hClusterRMSDeltaPhi[i] = new TH1D(Form("%s_%s", histoName.Data(), DataSets[i].Data()),"hClusterRMSDeltaPhi; Run Number ; #sigma_{#Delta#phi_{Cluster, Tracks}}",hNBin,hFBin,hLBin);
		if(doRange){
			if(iCalo==1) hClusterRMSDeltaPhi[i]->GetYaxis()->SetRangeUser(0.08, 0.16);
			if(iCalo==2) hClusterRMSDeltaPhi[i]->GetYaxis()->SetRangeUser(0.08, 0.16);
		}
		EditTH1(globalRuns, doEquidistantXaxis, hClusterRMSDeltaPhi[i], hMarkerStyle[i], hMarkerSize[i], hMarkerColor[i], hLineColor[i]);
		vecHistos[i].push_back(hClusterRMSDeltaPhi[i]);

		histoName = "hClusterM20-Mean";
		if(i==0) vecHistosName.push_back(histoName); //h==30
		hClusterMeanM20[i] = new TH1D(Form("%s_%s", histoName.Data(), DataSets[i].Data()),"hClusterMeanM20; Run Number ; #bar{#lower[0.1]{M20}}_{Cluster}",hNBin,hFBin,hLBin);
		if(doRange){
			if(iCalo==1) hClusterMeanM20[i]->GetYaxis()->SetRangeUser(0.03, 0.047);
			if(iCalo==2) hClusterMeanM20[i]->GetYaxis()->SetRangeUser(0.03, 0.047);
		}
		EditTH1(globalRuns, doEquidistantXaxis, hClusterMeanM20[i], hMarkerStyle[i], hMarkerSize[i], hMarkerColor[i], hLineColor[i]);
		vecHistos[i].push_back(hClusterMeanM20[i]);
		histoName = "hClusterM20-RMS";
		if(i==0) vecHistosName.push_back(histoName); //h==31
		hClusterRMSM20[i] = new TH1D(Form("%s_%s", histoName.Data(), DataSets[i].Data()),"hClusterRMSM20; Run Number ; #sigma_{M20_{Cluster}}",hNBin,hFBin,hLBin);
		if(doRange){
			if(iCalo==1) hClusterRMSM20[i]->GetYaxis()->SetRangeUser(0.058, 0.075);
			if(iCalo==2) hClusterRMSM20[i]->GetYaxis()->SetRangeUser(0.058, 0.075);
		}
		EditTH1(globalRuns, doEquidistantXaxis, hClusterRMSM20[i], hMarkerStyle[i], hMarkerSize[i], hMarkerColor[i], hLineColor[i]);
		vecHistos[i].push_back(hClusterRMSM20[i]);
	}

//****************************** Looping over DataSets ************************************************

	fstream fLog[nSets];
	fstream fLogRunwiseBadCells[nSets];
	fstream fLogRunwiseDeadCells[nSets];
	for(Int_t iStr=0; iStr<nSets; iStr++){
		fLog[iStr].open(Form("%s/A-%s.log",outputDir.Data(),DataSets[iStr].Data()), ios::out);
		if(doExtQA==2) fLogRunwiseBadCells[iStr].open(Form("%s/BadCellsRunwise-%s.log",outputDir.Data(),DataSets[iStr].Data()), ios::out);
		if(doExtQA==2) fLogRunwiseDeadCells[iStr].open(Form("%s/DeadCellsRunwise-%s.log",outputDir.Data(),DataSets[iStr].Data()), ios::out);
		fLog[iStr] << "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;
		fLog[iStr] << DataSets[iStr].Data() << endl;
		fLog[iStr] << "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;
		fLog[iStr] << fCollisionSystem.Data() << endl;
		fLog[iStr] << "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;
		fLog[iStr] << "processed cut: " << fCutSelection.Data() << endl;
		fLog[iStr] << calo.Data() << ", Modules: " << nCaloModules << ", Cells: " << nCaloCells << endl;
		fLog[iStr] << "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;
	}

	TList* TopDir = new TList();
	TList* TopContainer = new TList();
	TList* ESDContainer = new TList();
	TList* CaloCutsContainer = new TList();
	TList* ConvCutsContainer = new TList();
	TList* CaloExtQAContainer = new TList();

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

	TString sT[2]={"Pi0","Eta"};
	TString sL[2]={"#pi^{0}","#eta"};

	TString fRootFile;
	TString fDataSet;
	TString fRunNumber;
	TString fileCells;
	Int_t bin = -1;

	for(Int_t i=0; i<nSets; i++)
	{
		vecRuns.clear();
		fDataSet = vecDataSet.at(i);
		fileRuns = Form("runNumbers%s.txt", fDataSet.Data());
		if(doRunsFromDataLHC12 && i>=nData) {
			fileRuns = Form("runNumbers%s-%s.txt", vecDataSet.at(i).Data(),vecDataSet.at(0).Data());
			cout << "Switch doRunsFromDataLHC12 is true, reading runs from: " << fileRuns.Data() << endl;
		}
		if(!readin(fileRuns, vecRuns)) {cout << "ERROR, no Run Numbers could be found! Returning..." << endl; return;}

		fileCells = Form("%s/%s/ClusterQA/%s/%s/Cells/%s.log",fCutSelection.Data(),fEnergyFlag.Data(),suffix.Data(),DataSets[i].Data(),DataSets[i].Data());
		readin(fileCells, vecBadCells[i], kTRUE, kTRUE);
		fLog[i] << "Read in " << vecBadCells[i].size() << " bad cells: ";
		for(Int_t iBad=0; iBad<(Int_t) vecBadCells[i].size(); iBad++) fLog[i] << vecBadCells[i].at(iBad) << ", ";
		fLog[i] << endl;

//****************************** Looping over Runs ************************************************
		cout << endl;
		cout << "\t----------------------------------------------------------------------------" << endl;
		cout << "\tLooping over Runs of DataSet |" << (vecDataSet.at(i)).Data() << "|" << endl;
		cout << "\t----------------------------------------------------------------------------" << endl;
		cout << endl;
		fLog[i] << "Looping over Runs:" << endl;

		for(Int_t j=0; j<(Int_t) vecRuns.size(); j++)
		{
			fRunNumber = vecRuns.at(j);
			fRootFile = Form("%s/%s/%s/%s", filePath.Data(), fDataSet.Data(), fRunNumber.Data(), fileName.Data());
			TFile* RootFile = new TFile(fRootFile.Data(),"READ");
			if(RootFile->IsZombie()) {cout << "Info: ROOT file '" << fRootFile.Data() << "' could not be openend, continue!" << endl; continue;}

			cout << endl;
			cout << "\t\t----------------------------------------------------------------------------" << endl;
			cout << Form("\t\tRun %s", fRunNumber.Data()) << endl;
			cout << "\t\tProcessing file: " << fRootFile.Data() << endl;
			cout << "\t\t----------------------------------------------------------------------------" << endl;
			cout << endl;

			TopDir = (TList*) RootFile->Get(nameMainDir.Data());
				if(TopDir == NULL) {cout << "ERROR: TopDir not Found"<<endl; return;}
			TopContainer = (TList*) TopDir->FindObject(Form("Cut Number %s",fCutSelection.Data()));
				if(TopContainer == NULL) {cout << "ERROR: " << Form("Cut Number %s",fCutSelection.Data()) << " not found in File" << endl; return;}
			ESDContainer = (TList*) TopContainer->FindObject(Form("%s ESD histograms",fCutSelection.Data()));
				if(ESDContainer == NULL) {cout << "ERROR: " << Form("%s ESD histograms",fCutSelection.Data()) << " not found in File" << endl; return;}
			CaloCutsContainer = (TList*) TopContainer->FindObject(Form("CaloCuts_%s",fClusterCutSelection.Data()));
				if(CaloCutsContainer == NULL) {cout << "ERROR: " << Form("CaloCuts_%s",fClusterCutSelection.Data()) << " not found in File" << endl; return;}
			ConvCutsContainer = (TList*) TopContainer->FindObject(Form("ConvCuts_%s",fGammaCutSelection.Data()));
				if(ConvCutsContainer == NULL) {cout << "ERROR: " << Form("ConvCuts_%s",fGammaCutSelection.Data()) << " not found in File" << endl; return;}
			CaloExtQAContainer = (TList*) TopContainer->FindObject(Form("CaloExtQA_%s",fClusterCutSelection.Data()));
				if(CaloExtQAContainer == NULL) {
					cout << "WARNING: " << Form("CaloExtQA_%s",fClusterCutSelection.Data()) << " not found in File, using CaloCuts-Container" << endl;
					CaloExtQAContainer = CaloCutsContainer;
				}
	//---------
			//if(extendedRunwiseQA) ClusterQA(fRootFile,"","",nameMainDir,fEnergyFlag,plotDataSets[i],"","",fCutSelection,fRunNumber,suffix,mode);
	//---------
			if(doEquidistantXaxis) bin = mapBin[fRunNumber];
			else bin = fRunNumber.Atoi() - hFBin;
			Double_t nEvents = GetNEvents((TH1F*) ESDContainer->FindObject("NEvents"));
	//---------
			fLog[i] << "----------------------------------------------------------------------------" << endl;
			fLog[i] << "Processing file: " << fRootFile.Data() << endl;
			fLog[i] << "Run: " << fRunNumber.Data() << ", with NEvents: " << nEvents << endl;
			fLog[i] << "----------------------------------------------------------------------------" << endl;
			if(doExtQA==2) fLogRunwiseBadCells[i] << "Run-" << fRunNumber.Data() << endl;
			if(doExtQA==2) fLogRunwiseDeadCells[i] << "Run-" << fRunNumber.Data() << endl;
	//---------
			if( nEvents < 1 ){cout << "Warning: number of accepted events in run: " << nEvents << "! Setting nEvents to 1..." << endl; nEvents = 1;}
	//---------
			if(hNEvents){
				hNEvents[i]->SetBinContent(bin, nEvents);
			}else cout << "Info: Object |NEvents| could not be found! Skipping Fill..." << endl;
	//---------
			TH1F* GOODESD = (TH1F*) ESDContainer->FindObject("GoodESDTracks");
			if(GOODESD){
				hTracksMeanGood[i]->SetBinContent(bin, GOODESD->GetMean());
				hTracksMeanGood[i]->SetBinError(bin, GOODESD->GetMeanError());
				hTracksRMSGood[i]->SetBinContent(bin, GOODESD->GetRMS());
				hTracksRMSGood[i]->SetBinError(bin, GOODESD->GetRMSError());
			}else cout << "Info: Object |GoodESDTracks| could not be found! Skipping Fill..." << endl;
	//---------
			TH1F* EOC = (TH1F*) CaloCutsContainer->FindObject(Form("EnergyOfCluster_afterClusterQA %s", fClusterCutSelection.Data()));
			if(EOC){
				hClusterMeanEnergy[i]->SetBinContent(bin, EOC->GetMean());
				hClusterMeanEnergy[i]->SetBinError(bin, EOC->GetMeanError());
				hClusterRMSEnergy[i]->SetBinContent(bin, EOC->GetRMS());
				hClusterRMSEnergy[i]->SetBinError(bin, EOC->GetRMSError());
			}else cout << "Info: Object |EnergyOfCluster_afterClusterQA| could not be found! Skipping Fill..." << endl;
	//---------
			if(EOC){
				Double_t eps = 0.0001;
				Double_t Energy01 = EOC->Integral(1,EOC->GetXaxis()->FindBin(1-eps));
				Double_t Energy14 = EOC->Integral(EOC->GetXaxis()->FindBin(1+eps),EOC->GetXaxis()->FindBin(4-eps));
				Double_t Energy4 = EOC->Integral(EOC->GetXaxis()->FindBin(4+eps), EOC->GetXaxis()->GetLast());
				hClusterEnergy01[i]->SetBinContent(bin, Energy01 / nEvents);
				hClusterEnergy01[i]->SetBinError(bin, sqrt(Energy01) / nEvents);
				hClusterEnergy14[i]->SetBinContent(bin, Energy14 / nEvents);
				hClusterEnergy14[i]->SetBinError(bin, sqrt(Energy14) / nEvents);
				hClusterEnergy4[i]->SetBinContent(bin, Energy4 / nEvents);
				hClusterEnergy4[i]->SetBinError(bin, sqrt(Energy4) / nEvents);
			}else cout << "Info: Object |EnergyOfCluster_afterClusterQA| could not be found! Skipping Fill..." << endl;
	//---------
			TH1F* NCells = (TH1F*) CaloCutsContainer->FindObject(Form("NCellPerCluster_afterClusterQA %s", fClusterCutSelection.Data()));
			if(NCells){
				hClusterMeanNCells[i]->SetBinContent(bin, NCells->GetMean());
				hClusterMeanNCells[i]->SetBinError(bin, NCells->GetMeanError());
				hClusterRMSNCells[i]->SetBinContent(bin, NCells->GetRMS());
				hClusterRMSNCells[i]->SetBinError(bin, NCells->GetRMSError());
			}else cout << "Info: Object |NCellPerCluster_afterClusterQA| could not be found! Skipping Fill..." << endl;
	//---------
			TH1F* Dispersion = (TH1F*) CaloCutsContainer->FindObject(Form("Dispersion_afterClusterQA %s", fClusterCutSelection.Data()));
			if(Dispersion){
				hClusterMeanDispersion[i]->SetBinContent(bin, Dispersion->GetMean());
				hClusterMeanDispersion[i]->SetBinError(bin, Dispersion->GetMeanError());
				hClusterRMSDispersion[i]->SetBinContent(bin, Dispersion->GetRMS());
				hClusterRMSDispersion[i]->SetBinError(bin, Dispersion->GetRMSError());
			}else cout << "Info: Object |Dispersion_afterClusterQA| could not be found! Skipping Fill..." << endl;
	//---------
			TH1F* M02 = (TH1F*) CaloCutsContainer->FindObject(Form("M02_afterClusterQA %s", fClusterCutSelection.Data()));
			if(M02){
				hClusterMeanM02[i]->SetBinContent(bin, M02->GetMean());
				hClusterMeanM02[i]->SetBinError(bin, M02->GetMeanError());
				hClusterRMSM02[i]->SetBinContent(bin, M02->GetRMS());
				hClusterRMSM02[i]->SetBinError(bin, M02->GetRMSError());
			}else cout << "Info: Object |M02_afterClusterQA| could not be found! Skipping Fill..." << endl;
	//---------
			TH1F* R = (TH1F*) CaloCutsContainer->FindObject(Form("R_Cluster_afterClusterQA %s", fClusterCutSelection.Data()));
			if(R){
				hClusterMeanR[i]->SetBinContent(bin, R->GetMean());
				hClusterMeanR[i]->SetBinError(bin, R->GetMeanError());
				hClusterRMSR[i]->SetBinContent(bin, R->GetRMS());
				hClusterRMSR[i]->SetBinError(bin, R->GetRMSError());
			}else cout << "Info: Object |R_Cluster_afterClusterQA| could not be found! Skipping Fill..." << endl;
	//---------
			TH1F* CaloACC = (TH1F*) CaloCutsContainer->FindObject(Form("AcceptanceCuts %s", fClusterCutSelection.Data()));
			TH1F* CaloIPS = (TH1F*) CaloCutsContainer->FindObject(Form("IsPhotonSelected %s", fClusterCutSelection.Data()));
			if(CaloACC && CaloIPS){
				Double_t CaloNClusters = CaloACC->GetBinContent(1);
				Double_t CaloNClustersQA = CaloIPS->GetBinContent(5);
				hCaloNClusters[i]->SetBinContent(bin, CaloNClusters / nEvents);
				hCaloNClusters[i]->SetBinError(bin, sqrt(CaloNClusters) / nEvents);
				hCaloNClustersQA[i]->SetBinContent(bin, CaloNClustersQA / nEvents);
				hCaloNClustersQA[i]->SetBinError(bin, sqrt(CaloNClustersQA) / nEvents);
			}else cout << "Info: Object |AcceptanceCuts| or |IsPhotonSelected| could not be found! Skipping Fill..." << endl;
	//---------
			TH1F* ConvIPS = (TH1F*) ConvCutsContainer->FindObject(Form("IsPhotonSelected %s", fGammaCutSelection.Data()));
			if(ConvIPS){
				Double_t ConvNCandidates = ConvIPS->GetBinContent(1);
				Double_t ConvNCandidatesQA = ConvIPS->GetBinContent(9);
				hConvNCandidates[i]->SetBinContent(bin, ConvNCandidates / nEvents);
				hConvNCandidates[i]->SetBinError(bin, sqrt(ConvNCandidates) / nEvents);
				hConvNCandidatesQA[i]->SetBinContent(bin, ConvNCandidatesQA / nEvents);
				hConvNCandidatesQA[i]->SetBinError(bin, sqrt(ConvNCandidatesQA) / nEvents);
			}else cout << "Info: Object |IsPhotonSelected| could not be found! Skipping Fill..." << endl;
	//---------
			TH2F* Time = (TH2F*) CaloCutsContainer->FindObject(Form("ClusterTimeVsE_afterClusterQA %s", fClusterCutSelection.Data()));
			if(Time){
				hClusterMeanTime[i]->SetBinContent(bin, Time->GetMean());
				hClusterMeanTime[i]->SetBinError(bin, Time->GetMeanError());
				hClusterRMSTime[i]->SetBinContent(bin, Time->GetRMS());
				hClusterRMSTime[i]->SetBinError(bin, Time->GetRMSError());
			}else cout << "Info: Object |ClusterTimeVsE_afterClusterQA| could not be found! Skipping Fill..." << endl;
	//---------
			TH2F* ESD_Mother = (TH2F*) ESDContainer->FindObject("ESD_Mother_InvMass_Pt");
			TH2F* ESD_Mother_Matched = (TH2F*) ESDContainer->FindObject("ESD_MotherMatched_InvMass_Pt");
			if(ESD_Mother && ESD_Mother_Matched){
				CalculateFractionMatches(hClusterFractionMatches[i], ESD_Mother, ESD_Mother_Matched, bin, 0, 30);
				CalculateFractionMatches(hClusterFractionMatchesS[i], ESD_Mother, ESD_Mother_Matched, bin, 0, 1.5);
				CalculateFractionMatches(hClusterFractionMatchesM[i], ESD_Mother, ESD_Mother_Matched, bin, 1.5, 2.5);
				CalculateFractionMatches(hClusterFractionMatchesH[i], ESD_Mother, ESD_Mother_Matched, bin, 2.5, 30);
			}else cout << "Info: Object |ESD_Mother_InvMass_Pt| or |ESD_MotherMatched_InvMass_Pt| could not be found! Skipping Fill..." << endl;
	//---------
			TH2F* DeltaEtaPhi = (TH2F*) CaloCutsContainer->FindObject(Form("dEtaVsdPhi_beforeClusterQA %s", fClusterCutSelection.Data()));
			if(DeltaEtaPhi){
				hClusterMeanDeltaEta[i]->SetBinContent(bin, DeltaEtaPhi->GetMean(1));
				hClusterMeanDeltaEta[i]->SetBinError(bin, DeltaEtaPhi->GetMeanError(1));
				hClusterMeanDeltaPhi[i]->SetBinContent(bin, DeltaEtaPhi->GetMean(2));
				hClusterMeanDeltaPhi[i]->SetBinError(bin, DeltaEtaPhi->GetMeanError(2));
				hClusterRMSDeltaEta[i]->SetBinContent(bin, DeltaEtaPhi->GetRMS(1));
				hClusterRMSDeltaEta[i]->SetBinError(bin, DeltaEtaPhi->GetRMSError(1));
				hClusterRMSDeltaPhi[i]->SetBinContent(bin, DeltaEtaPhi->GetRMS(2));
				hClusterRMSDeltaPhi[i]->SetBinError(bin, DeltaEtaPhi->GetRMSError(2));
			}else cout << "Info: Object |dEtaVsdPhi_beforeClusterQA| could not be found! Skipping Fill..." << endl;
	//---------
			TH1F* M20 = (TH1F*) CaloCutsContainer->FindObject(Form("M20_afterClusterQA %s", fClusterCutSelection.Data()));
			if(M20){
				hClusterMeanM20[i]->SetBinContent(bin, M20->GetMean());
				hClusterMeanM20[i]->SetBinError(bin, M20->GetMeanError());
				hClusterRMSM20[i]->SetBinContent(bin, M20->GetRMS());
				hClusterRMSM20[i]->SetBinError(bin, M20->GetRMSError());
			}else cout << "Info: Object |M20_afterClusterQA| could not be found! Skipping Fill..." << endl;
	//---------
			TH2D* ClusEtaPhi = (TH2D*) CaloCutsContainer->FindObject(Form("EtaPhi_afterClusterQA %s", fClusterCutSelection.Data()));
			if(ClusEtaPhi){
				TH2D* tempClusEtaPhi = new TH2D(*ClusEtaPhi);
				tempClusEtaPhi->Scale(1 / nEvents);
				tempClusEtaPhi->Scale(1 / GetMeanTH2(tempClusEtaPhi));
				tempClusEtaPhi->SetName(Form("%s_EtaPhi_%s",fRunNumber.Data(),fDataSet.Data()));
				tempClusEtaPhi->SetTitle(fRunNumber);
				tempClusEtaPhi->GetXaxis()->SetTitle("#phi");
				tempClusEtaPhi->GetYaxis()->SetTitle("#eta");
				tempClusEtaPhi->GetZaxis()->SetRangeUser(0, 2);
				tempClusEtaPhi->SetDirectory(0);
				//if(tempClusEtaPhi->GetEntries()>0){
					vecClusterEtaPhi[i].push_back(tempClusEtaPhi);
				//}
				//else delete tempClusEtaPhi;
			}else cout << "Info: Object |EtaPhi_afterClusterQA| could not be found! Skipping..." << endl;
	//---------
			if(doExtQA>0){
				TH2D* ClusEVsNCells = (TH2D*) CaloExtQAContainer->FindObject(Form("ClusterEnergyVsNCells_afterQA %s", fClusterCutSelection.Data()));
				if(ClusEVsNCells){
					TH2D* tempClusEVsNCells = new TH2D(*ClusEVsNCells);
					tempClusEVsNCells->SetName(Form("%s_ClusterEnergyVsNCells_%s",fRunNumber.Data(),fDataSet.Data()));
					tempClusEVsNCells->SetTitle(fRunNumber);
					tempClusEVsNCells->GetXaxis()->SetTitle("Cluster Energy (GeV)");
					tempClusEVsNCells->GetYaxis()->SetTitle("#it{N}_{Cells} per Cluster");
					tempClusEVsNCells->SetDirectory(0);
					//if(tempClusEVsNCells->GetEntries()>0){
						vecClusterEVsNCells[i].push_back(tempClusEVsNCells);
					//}
					//else delete tempClusEVsNCells;
				}else cout << "Info: Object |ClusterEnergyVsNCells_afterQA| could not be found! Skipping..." << endl;
			}
//---------
			TH1D* ClusEnergy = (TH1D*) CaloCutsContainer->FindObject(Form("EnergyOfCluster_afterClusterQA %s", fClusterCutSelection.Data()));
			if(ClusEnergy){
				TH1D* ClusEnergyBin = (TH1D*) ClusEnergy->Rebin(fNBinsClusterPt, "name", fBinsClusterPt);
				TH1D* tempClusEnergy = new TH1D(*ClusEnergyBin);
				tempClusEnergy->Divide(fDeltaPt);
				tempClusEnergy->Sumw2();
				tempClusEnergy->Scale(1 / nEvents);
				tempClusEnergy->SetDirectory(0);
				tempClusEnergy->GetXaxis()->SetRangeUser(minClusE,40);
				tempClusEnergy->GetXaxis()->SetTitle("Cluster Energy (GeV)");
				tempClusEnergy->GetYaxis()->SetTitle("#frac{1}{N_{Events}} #frac{dN}{dE}");
				vecClusterEnergy[i].push_back(tempClusEnergy);
			}else cout << "Info: Object |EnergyOfCluster_afterClusterQA| could not be found! Skipping..." << endl;
	//---------
			TH1D* ClusM02 = (TH1D*) CaloCutsContainer->FindObject(Form("M02_afterClusterQA %s", fClusterCutSelection.Data()));
			if(ClusM02){
				TH1D* tempClusM02 = new TH1D(*ClusM02);
				tempClusM02->Sumw2();
				tempClusM02->Scale(1 / nEvents);
				tempClusM02->SetDirectory(0);
				tempClusM02->GetXaxis()->SetRangeUser(0.05,0.55);
				tempClusM02->GetXaxis()->SetTitle("#lambda_{0}^{2}");
				tempClusM02->GetYaxis()->SetTitle("#frac{1}{N_{Events}} #frac{dN}{d#lambda_{0}^{2}}");
				vecClusterM02[i].push_back(tempClusM02);
			}else cout << "Info: Object |M02_afterClusterQA| could not be found! Skipping..." << endl;
	//---------
			TH1D* ClusM20 = (TH1D*) CaloCutsContainer->FindObject(Form("M20_afterClusterQA %s", fClusterCutSelection.Data()));
			if(ClusM20){
				TH1D* tempClusM20 = new TH1D(*ClusM20);
				tempClusM20->Sumw2();
				tempClusM20->Scale(1 / nEvents);
				tempClusM20->SetDirectory(0);
				tempClusM20->GetXaxis()->SetRangeUser(0,0.55);
				tempClusM20->GetXaxis()->SetTitle("#lambda_{1}^{2}");
				tempClusM20->GetYaxis()->SetTitle("#frac{1}{N_{Events}} #frac{dN}{d#lambda_{1}^{2}}");
				vecClusterM20[i].push_back(tempClusM20);
			}else cout << "Info: Object |M20_afterClusterQA| could not be found! Skipping..." << endl;
	//---------
			TH1D* ClusNCells = (TH1D*) CaloCutsContainer->FindObject(Form("NCellPerCluster_afterClusterQA %s", fClusterCutSelection.Data()));
			if(ClusNCells){
				TH1D* tempClusNCells = new TH1D(*ClusNCells);
				tempClusNCells->Sumw2();
				tempClusNCells->Scale(1 / nEvents);
				tempClusNCells->SetDirectory(0);
				tempClusNCells->GetXaxis()->SetRangeUser(minNCells,30);
				tempClusNCells->GetXaxis()->SetTitle("N_{Cells} per Cluster");
				tempClusNCells->GetYaxis()->SetTitle("#frac{1}{N_{Events}} #frac{dN}{dN_{Cells}}");
				vecClusterNCells[i].push_back(tempClusNCells);
			}else cout << "Info: Object |NCellPerCluster_afterClusterQA| could not be found! Skipping..." << endl;
	//---------
			TH1D* ClusDispersion = (TH1D*) CaloCutsContainer->FindObject(Form("Dispersion_afterClusterQA %s", fClusterCutSelection.Data()));
			if(ClusDispersion){
				TH1D* tempClusDispersion = new TH1D(*ClusDispersion);
				tempClusDispersion->Sumw2();
				tempClusDispersion->Scale(1 / nEvents);
				tempClusDispersion->SetDirectory(0);
				tempClusDispersion->GetXaxis()->SetRangeUser(0.2,1.1);
				tempClusDispersion->GetXaxis()->SetTitle("Dispersion of Cluster");
				tempClusDispersion->GetYaxis()->SetTitle("#frac{1}{N_{Events}} #frac{dN}{dDisp}");
				vecClusterDispersion[i].push_back(tempClusDispersion);
			}else cout << "Info: Object |Dispersion_afterClusterQA| could not be found! Skipping..." << endl;
	//---------
			TH2D* ClusTimeE = (TH2D*) CaloCutsContainer->FindObject(Form("ClusterTimeVsE_afterClusterQA %s", fClusterCutSelection.Data()));
			if(ClusTimeE){
				TH1D* ClusTime = (TH1D*) ClusTimeE->ProjectionX("ProjectionClusTime",1,800);
				TH1D* tempClusTime = new TH1D(*ClusTime);
				tempClusTime->Sumw2();
				tempClusTime->Scale(1 / nEvents);
				tempClusTime->SetDirectory(0);
				Double_t tMin = 0;
				Double_t tMax = 0;
				if(i<nData){
					tMin = -0.6E-7;
					tMax = 0.6E-7;
				}else{
					tMin = 5.8E-7;
					tMax = 6.6E-7;
				}
				tempClusTime->GetXaxis()->SetRangeUser(tMin,tMax);
				tempClusTime->GetXaxis()->SetTitle("t_{Cluster} (ns)");
				tempClusTime->GetYaxis()->SetTitle("#frac{1}{N_{Events}} #frac{dN}{dt}");
				vecClusterTime[i].push_back(tempClusTime);
			}else cout << "Info: Object |ClusterTimeVsE_afterClusterQA| could not be found! Skipping..." << endl;
	//---------
			TH2D* ClusdEta_dPhi_before = (TH2D*)CaloCutsContainer->FindObject(Form("dEtaVsdPhi_beforeClusterQA %s", fClusterCutSelection.Data()));
			TH2D* ClusdEta_dPhi_after = (TH2D*)CaloCutsContainer->FindObject(Form("dEtaVsdPhi_afterClusterQA %s", fClusterCutSelection.Data()));
			if(ClusdEta_dPhi_before && ClusdEta_dPhi_after){
				TH2D* ClusdEta_dPhi_matched = (TH2D*) ClusdEta_dPhi_before->Clone();
				ClusdEta_dPhi_matched->Add(ClusdEta_dPhi_after,-1);
				TH1D* ClusdEta_matched = (TH1D*) ClusdEta_dPhi_matched->ProjectionX("ProjectionClusdEta",1,240);
				TH1D* ClusdPhi_matched = (TH1D*) ClusdEta_dPhi_matched->ProjectionY("ProjectionClusdPhi",1,240);
				TH1D* tempClusdEta_matched = new TH1D(*ClusdEta_matched);
				TH1D* tempClusdPhi_matched = new TH1D(*ClusdPhi_matched);
				tempClusdEta_matched->GetXaxis()->SetRangeUser(-0.02,0.02);
				tempClusdEta_matched->GetXaxis()->SetTitle("#Delta#eta");
				tempClusdEta_matched->GetYaxis()->SetTitle("#frac{1}{N} #frac{dN}{d#Delta#eta}");
				tempClusdPhi_matched->GetXaxis()->SetRangeUser(-0.1,0.1);
				tempClusdPhi_matched->GetXaxis()->SetTitle("#Delta#phi");
				tempClusdPhi_matched->GetYaxis()->SetTitle("#frac{1}{N} #frac{dN}{d#Delta#phi}");
				tempClusdEta_matched->Sumw2();
				tempClusdPhi_matched->Sumw2();
				if(tempClusdEta_matched->GetEntries() > 0) tempClusdEta_matched->Scale(1 / ((Double_t)tempClusdEta_matched->GetEntries()));
				if(tempClusdPhi_matched->GetEntries() > 0) tempClusdPhi_matched->Scale(1 / ((Double_t)tempClusdPhi_matched->GetEntries()));
				tempClusdEta_matched->SetDirectory(0);
				tempClusdPhi_matched->SetDirectory(0);

				vecClusterDeltaEta[i].push_back(tempClusdEta_matched);
				vecClusterDeltaPhi[i].push_back(tempClusdPhi_matched);
			}else cout << "Info: Object |dEtaVsdPhi_beforeClusterQA| or |dEtaVsdPhi_afterClusterQA| could not be found! Skipping..." << endl;
	//---------
			for(Int_t iT=0; iT<2; iT++)
			{
				TH2D* ConvPhotonEtaPhi = (TH2D*) ESDContainer->FindObject(Form("ESD_Mother%sConvPhoton_Eta_Phi", sT[iT].Data()));
				if(ConvPhotonEtaPhi){
					TH1D* ConvPhotonEta = (TH1D*) ConvPhotonEtaPhi->ProjectionY("ProjectionConvPhotonEta",1,200);
					TH1D* ConvPhotonPhi = (TH1D*) ConvPhotonEtaPhi->ProjectionX("ProjectionConvPhotonPhi",1,600);
					TH1D* tempConvPhotonEta = new TH1D(*ConvPhotonEta);
					TH1D* tempConvPhotonPhi = new TH1D(*ConvPhotonPhi);
					//tempConvPhotonEta->GetXaxis()->SetRangeUser(-1,1);
					tempConvPhotonEta->GetXaxis()->SetTitle(Form("#eta_{#gamma_{conv} under %s-peak}",sL[iT].Data()));
					tempConvPhotonEta->GetYaxis()->SetTitle("#frac{1}{N_{Events}} #frac{dN}{d#eta}");
					if(iT==0) tempConvPhotonPhi->GetXaxis()->SetRangeUser(0.8,3.8);
					tempConvPhotonPhi->GetXaxis()->SetTitle(Form("#phi_{#gamma_{conv} under %s-peak}",sL[iT].Data()));
					tempConvPhotonPhi->GetYaxis()->SetTitle("#frac{1}{N_{Events}} #frac{dN}{d#phi}");
					tempConvPhotonEta->Sumw2();
					tempConvPhotonPhi->Sumw2();
					tempConvPhotonEta->Scale(1 / nEvents);
					tempConvPhotonPhi->Scale(1 / nEvents);
					tempConvPhotonEta->SetDirectory(0);
					tempConvPhotonPhi->SetDirectory(0);
					if(iT==0){
						vecClusterPi0ConvPhotonEta[i].push_back(tempConvPhotonEta);
						vecClusterPi0ConvPhotonPhi[i].push_back(tempConvPhotonPhi);
					}else{
						vecClusterEtaConvPhotonEta[i].push_back(tempConvPhotonEta);
						vecClusterEtaConvPhotonPhi[i].push_back(tempConvPhotonPhi);
					}
				}else cout << Form("Info: Object |ESD_Mother%sConvPhoton_Eta_Phi| could not be found! Skipping...", sT[iT].Data()) << endl;
			}
	//---------
			if(doExtQA>0){
				TH2D* ClusterEVsModule = (TH2D*) CaloExtQAContainer->FindObject(Form("ClusterEnergyVsModule_afterClusterQA %s", fClusterCutSelection.Data()));
				TH2D* ModuleEnergyEVsModule = (TH2D*) CaloExtQAContainer->FindObject(Form("ModuleEnergyVsModule %s", fClusterCutSelection.Data()));
				TH2D* NCells100VsModule = (TH2D*) CaloExtQAContainer->FindObject(Form("NCellsAbove100VsModule %s", fClusterCutSelection.Data()));
				TH2D* NCells1500VsModule = (TH2D*) CaloExtQAContainer->FindObject(Form("NCellsAbove1500VsModule %s", fClusterCutSelection.Data()));

				for(Int_t iModule=0; iModule<nCaloModules; iModule++)
				{
					if(ClusterEVsModule){
						TH1D* ClusterEForModule = (TH1D*) ClusterEVsModule->ProjectionX(Form("projectClusterE_%i",iModule),iModule+1,iModule+1);
						TH1D* tempClusterEForModule = new TH1D(*ClusterEForModule);
						tempClusterEForModule->GetXaxis()->SetRangeUser(minClusE,40);
						tempClusterEForModule->GetXaxis()->SetTitle(Form("Cluster Energy of SM%i (GeV)",iModule));
						tempClusterEForModule->GetYaxis()->SetTitle("#frac{dE}{dN}");
						tempClusterEForModule->Sumw2();
						tempClusterEForModule->Scale(1 / nEvents);
						tempClusterEForModule->SetDirectory(0);
						vecClusterEVsModule[i][iModule].push_back(tempClusterEForModule);
					}else cout << "Info: Object |ClusterEnergyVsModule_afterClusterQA| could not be found! Skipping..." << endl;
					if(ModuleEnergyEVsModule){
						TH1D* ModuleEForModule = (TH1D*) ModuleEnergyEVsModule->ProjectionX(Form("projectModuleE_%i",iModule),iModule+1,iModule+1);
						TH1D* tempModuleEForModule = new TH1D(*ModuleEForModule);
						tempModuleEForModule->GetXaxis()->SetTitle(Form("Total SuperModule Energy per Event for SM%i(GeV)",iModule));
						tempModuleEForModule->GetYaxis()->SetTitle("#frac{dE}{dN}");
						tempModuleEForModule->Sumw2();
						tempModuleEForModule->Scale(1 / nEvents);
						tempModuleEForModule->SetDirectory(0);
						vecModuleEVsModule[i][iModule].push_back(tempModuleEForModule);
					}else cout << "Info: Object |ModuleEnergyVsModule_afterClusterQA| could not be found! Skipping..." << endl;
					if(NCells100VsModule){
						TH1D* NCells100ForModule = (TH1D*) NCells100VsModule->ProjectionX(Form("projectNCells100_%i",iModule),iModule+1,iModule+1);
						TH1D* tempNCells100ForModule = new TH1D(*NCells100ForModule);
						tempNCells100ForModule->GetXaxis()->SetTitle(Form("#it{N}_{Cells}>100 MeV in SM%i per Event",iModule));
						tempNCells100ForModule->GetYaxis()->SetTitle("#frac{d#it{N}_{Cells}>100 MeV}{dN}");
						tempNCells100ForModule->Sumw2();
						tempNCells100ForModule->Scale(1 / nEvents);
						tempNCells100ForModule->SetDirectory(0);
						vecClusterNCells100VsModule[i][iModule].push_back(tempNCells100ForModule);
					}else cout << "Info: Object |NCellsAbove100VsModule| could not be found! Skipping..." << endl;
					if(NCells1500VsModule){
						TH1D* NCells1500ForModule = (TH1D*) NCells1500VsModule->ProjectionX(Form("projectNCells1500_%i",iModule),iModule+1,iModule+1);
						TH1D* tempNCells1500ForModule = new TH1D(*NCells1500ForModule);
						tempNCells1500ForModule->GetXaxis()->SetTitle(Form("#it{N}_{Cells}>1500 MeV in SM%i per Event",iModule));
						tempNCells1500ForModule->GetYaxis()->SetTitle("#frac{d#it{N}_{Cells}>1500 MeV}{dN}");
						tempNCells1500ForModule->Sumw2();
						tempNCells1500ForModule->Scale(1 / nEvents);
						tempNCells1500ForModule->SetDirectory(0);
						vecClusterNCells1500VsModule[i][iModule].push_back(tempNCells1500ForModule);
					}else cout << "Info: Object |NCellsAbove1500VsModule| could not be found! Skipping..." << endl;
				}
		//---------
				TH1D* ClusIncludedCells = (TH1D*)CaloExtQAContainer->FindObject(Form("ClusterIncludedCells_afterClusterQA %s", fClusterCutSelection.Data()));
				if(ClusIncludedCells){
					TH1D* tempClusIncludedCells = new TH1D(*ClusIncludedCells);
					tempClusIncludedCells->SetName(Form("%s_ClusterIncludedCells_%s",fRunNumber.Data(),fDataSet.Data()));
					tempClusIncludedCells->SetTitle(fRunNumber);
					tempClusIncludedCells->GetXaxis()->SetTitle("Cell ID in accepted Clusters");
					tempClusIncludedCells->GetYaxis()->SetTitle("d#it{N}/d#it{CellID}");
					tempClusIncludedCells->Sumw2();
					tempClusIncludedCells->SetDirectory(0);
					vecClusterIncludedCells[i].push_back(tempClusIncludedCells);
				}else cout << "Info: Object |ClusterIncludedCells_afterClusterQA| could not be found! Skipping..." << endl;
		//---------
				TH1D* ClusIncludedCellsBefore = (TH1D*)CaloExtQAContainer->FindObject(Form("ClusterIncludedCells_beforeClusterQA %s", fClusterCutSelection.Data()));
				if(ClusIncludedCellsBefore){
					TH1D* tempClusIncludedCellBefore = new TH1D(*ClusIncludedCellsBefore);
					if(doExtQA==2) CheckIncludedCellsRunwise(fLogRunwiseBadCells[i],tempClusIncludedCellBefore,nCaloCells,kFALSE);
					if(doExtQA==2) CheckDeadCellsRunwise(fLogRunwiseDeadCells[i],tempClusIncludedCellBefore,nCaloCells);
					tempClusIncludedCellBefore->SetName(Form("%s_ClusterIncludedCells_beforeClusterQA_%s",fRunNumber.Data(),fDataSet.Data()));
					tempClusIncludedCellBefore->SetTitle(fRunNumber);
					tempClusIncludedCellBefore->GetXaxis()->SetTitle("Cell ID in all Clusters");
					tempClusIncludedCellBefore->GetYaxis()->SetTitle("d#it{N}/d#it{CellID}");
					tempClusIncludedCellBefore->Sumw2();
					tempClusIncludedCellBefore->SetDirectory(0);
					vecClusterIncludedCellsBefore[i].push_back(tempClusIncludedCellBefore);
				}else cout << "Info: Object |ClusterIncludedCells_beforeClusterQA| could not be found! Skipping..." << endl;
		//---------
				TH1D* ClusEFracCells = (TH1D*)CaloExtQAContainer->FindObject(Form("ClusterEnergyFracCells_afterClusterQA %s", fClusterCutSelection.Data()));
				if(ClusEFracCells){
					TH1D* tempClusEFracCells = new TH1D(*ClusEFracCells);
					tempClusEFracCells->SetName(Form("%s_EFracCells_%s",fRunNumber.Data(),fDataSet.Data()));
					tempClusEFracCells->SetTitle(fRunNumber);
					tempClusEFracCells->GetXaxis()->SetTitle("Cell ID in accepted Clusters");
					tempClusEFracCells->GetYaxis()->SetTitle("#sum^{events} E-Frac of Cell");
					tempClusEFracCells->Sumw2();
					tempClusEFracCells->SetDirectory(0);
					vecClusterEFracCells[i].push_back(tempClusEFracCells);
				}else cout << "Info: Object |ClusterEnergyFracCells_afterClusterQA| could not be found! Skipping..." << endl;
		//---------
				TH1D* ClusEFracCellsBefore = (TH1D*)CaloExtQAContainer->FindObject(Form("ClusterEnergyFracCells_beforeClusterQA %s", fClusterCutSelection.Data()));
				if(ClusEFracCellsBefore){
					TH1D* tempClusEFracCellBefore = new TH1D(*ClusEFracCellsBefore);
					//if(doExtQA==2) CheckEFracCellsRunwise(fLogRunwiseBadCells[i],tempClusEFracCellBefore,nCaloCells,kFALSE);
					tempClusEFracCellBefore->SetName(Form("%s_EFracCells_beforeQA_%s",fRunNumber.Data(),fDataSet.Data()));
					tempClusEFracCellBefore->SetTitle(fRunNumber);
					tempClusEFracCellBefore->GetXaxis()->SetTitle("Cell ID in all Clusters");
					tempClusEFracCellBefore->GetYaxis()->SetTitle("#sum^{events} E-Frac of Cell");
					tempClusEFracCellBefore->Sumw2();
					tempClusEFracCellBefore->SetDirectory(0);
					vecClusterEFracCellsBefore[i].push_back(tempClusEFracCellBefore);
				}else cout << "Info: Object |ClusterEnergyFracCells_beforeClusterQA| could not be found! Skipping..." << endl;
		//---------
				if(doExtQA==2){
					TH2D* fHistCellEnergyVsCellID = (TH2D*)CaloExtQAContainer->FindObject(Form("CellEnergyVsCellID %s", fClusterCutSelection.Data()));
					TH2D* fHistCellTimeVsCellID = (TH2D*)CaloExtQAContainer->FindObject(Form("CellTimeVsCellID %s", fClusterCutSelection.Data()));
					if(fHistCellEnergyVsCellID && fHistCellTimeVsCellID){
						TH2D** tempClusCell = PlotCellMeanVsSigmaForRunwise(nCaloCells,fHistCellEnergyVsCellID,fHistCellTimeVsCellID,
													"Mean Cell Energy (GeV)","#sigma_{Cell Energy} (GeV)","Mean Cell Time (s)","#sigma_{Cell Time} (s)",(i>=nData));
						tempClusCell[0]->SetName(Form("%s_ClusterEMeanVsSigma_%s",fRunNumber.Data(),fDataSet.Data()));
						tempClusCell[0]->SetTitle(fRunNumber);
						tempClusCell[0]->SetDirectory(0);
						vecClusterEnergyMeanSigma[i].push_back(tempClusCell[0]);
						tempClusCell[1]->SetName(Form("%s_ClusterTimeMeanVsSigma_%s",fRunNumber.Data(),fDataSet.Data()));
						tempClusCell[1]->SetTitle(fRunNumber);
						tempClusCell[1]->SetDirectory(0);
						vecClusterTimeMeanSigma[i].push_back(tempClusCell[1]);
					}else cout << "Info: Object |CellEnergyVsCellID or CellTimeVsCellID| could not be found! Skipping..." << endl;

					for(Int_t j=0; j<(Int_t) vecBadCells[i].size(); j++)
					{
						TH2D* fHistCellEnergyVsCellID = (TH2D*)CaloExtQAContainer->FindObject(Form("CellEnergyVsCellID %s", fClusterCutSelection.Data()));
						TH2D* fHistCellTimeVsCellID = (TH2D*)CaloExtQAContainer->FindObject(Form("CellTimeVsCellID %s", fClusterCutSelection.Data()));
						if(fHistCellEnergyVsCellID && fHistCellTimeVsCellID){
							TH1D* tempEnergy;
							TH1D* tempTime;
							tempEnergy = (TH1D*) fHistCellEnergyVsCellID->ProjectionX("energy",((TString)vecBadCells[i].at(j)).Atoi(),((TString)vecBadCells[i].at(j)).Atoi());
							tempTime = (TH1D*) fHistCellTimeVsCellID->ProjectionX("time",((TString)vecBadCells[i].at(j)).Atoi(),((TString)vecBadCells[i].at(j)).Atoi());

							TH1D* tempEnergyCell = new TH1D(*tempEnergy);
							tempEnergyCell->GetXaxis()->SetTitle(Form("Cell Energy of ID %i (GeV)",((TString)vecBadCells[i].at(j)).Atoi()));
							tempEnergyCell->GetYaxis()->SetTitle("#frac{dE}{dN}");
							tempEnergyCell->Sumw2();
							tempEnergyCell->Scale(1 / nEvents);
							tempEnergyCell->SetDirectory(0);
							vecBadCellsEnergy[i].push_back(tempEnergyCell);

							TH1D* tempTimeCell = new TH1D(*tempTime);
							tempTimeCell->GetXaxis()->SetTitle(Form("Cell Time of ID %i (s)",((TString)vecBadCells[i].at(j)).Atoi()));
							tempTimeCell->GetYaxis()->SetTitle("#frac{dTime}{dN}");
							tempTimeCell->Sumw2();
							tempTimeCell->Scale(1 / nEvents);
							tempTimeCell->SetDirectory(0);
							vecBadCellsTime[i].push_back(tempTimeCell);
						}
					}
				}
			}
	//---------
			CaloExtQAContainer->Clear();
			ConvCutsContainer->Clear();
			CaloCutsContainer->Clear();
			ESDContainer->Clear();
			TopContainer->Clear();
			TopDir->Clear();

			RootFile->Delete();
			delete RootFile;
		}

	}

//****************************** Drawing Histograms ************************************************
	cout << "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;
	cout << "Drawing Histograms" << endl;

	TCanvas* canvas = new TCanvas("canvas","",200,10,1350,900);  // gives the page size
	Double_t leftMar = 0.09; Double_t rightMar = 0.02; Double_t topMargin = 0.06; Double_t bottomMargin = 0.09;
	DrawGammaCanvasSettings(canvas, leftMar, rightMar, topMargin, bottomMargin);

	if(doHistsForEverySet)
	{
		TBox *boxLabel = new TBox(1.37,0.7,1.78,0.83);
		boxLabel->SetFillStyle(0);boxLabel->SetFillColor(0);boxLabel->SetLineColor(1);boxLabel->SetLineWidth(0.6);
		TBox *boxLabel2 = new TBox(-0.4,51,6.5,56.5);
		boxLabel2->SetFillStyle(0);boxLabel2->SetFillColor(0);boxLabel2->SetLineColor(1);boxLabel2->SetLineWidth(0.6);

		TString outputDirDataSet;

		for(Int_t i=0; i<nSets; i++)
		{
			cout << "DataSet: " << plotDataSets[i].Data() << endl;
			outputDirDataSet = Form("%s/%s",outputDir.Data(), plotDataSets[i].Data());
			if(doRunsFromDataLHC12 && i>=nData) {
				outputDirDataSet = Form("%s/%s-%s", outputDir.Data(), plotDataSets[i].Data(),plotDataSets[0].Data());
				cout << "Switch doRunsFromDataLHC12 is true, output to: " << outputDirDataSet.Data() << endl;
			}
			gSystem->Exec("mkdir -p "+outputDirDataSet);
			gSystem->Exec("mkdir -p "+outputDirDataSet+"/ExtQA");
			gSystem->Exec("mkdir -p "+outputDirDataSet+"/ExtQA/EFrac");
			gSystem->Exec("mkdir -p "+outputDirDataSet+"/ExtQA/IncludedCells");
			gSystem->Exec("mkdir -p "+outputDirDataSet+"/BadCells");

			TString fTrigger = "";
			if(i<nData){
				TString fTriggerCut = fEventCutSelection(3,2);
				fTrigger = AnalyseSpecialTriggerCut(fTriggerCut.Atoi(), plotDataSets[i]);
				cout << "Trigger: " << fTrigger.Data() << endl;
			}

			Int_t iD = 1;
			Int_t varDraw = 0;
			canvas->Divide(4,4);
			for(Int_t j=0; j<(Int_t) vecClusterEtaPhi[i].size(); j++, iD++)
			{
				if( iD > 16 )
				{
					SaveCanvas(canvas, Form("%s/hClusterEtaPhi_scaledNEventsAndMean_p%i.%s", outputDirDataSet.Data(), varDraw++, suffix.Data()));
					canvas->Divide(4,4);
					iD = 1;
				}
				TPad* currPad = (TPad*) canvas->cd(iD);
				currPad->SetLeftMargin(0.13);
				currPad->SetRightMargin(0.15);
				currPad->SetTopMargin(0.1);
				currPad->SetBottomMargin(0.1);

				TString title = ((TH2D*) vecClusterEtaPhi[i].at(j))->GetTitle();
				EditTH2(((TH2D*) vecClusterEtaPhi[i].at(j)), 0.6, 0.8);
				((TH2D*) vecClusterEtaPhi[i].at(j))->SetTitle(" ");
				((TH2D*) vecClusterEtaPhi[i].at(j))->Draw();

				boxLabel->Draw();
				TLatex *alice = new TLatex(0.12,0.93,title.Data());
				alice->SetNDC();
				alice->SetTextColor(1);
				alice->SetTextSize(0.08);
				alice->Draw();
			}
			SaveCanvas(canvas, Form("%s/hClusterEtaPhi_scaledNEventsAndMean_p%i.%s", outputDirDataSet.Data(), varDraw, suffix.Data()));

			if(doExtQA>0){
				iD = 1;
				varDraw = 0;
				canvas->Divide(4,4);
				for(Int_t j=0; j<(Int_t) vecClusterEVsNCells[i].size(); j++, iD++)
				{
					if( iD > 16 )
					{
						SaveCanvas(canvas, Form("%s/ExtQA/hClusterEVsNCells_p%i.%s", outputDirDataSet.Data(), varDraw++, suffix.Data()));
						canvas->Divide(4,4);
						iD = 1;
					}
					TPad* currPad = (TPad*) canvas->cd(iD);
					currPad->SetLeftMargin(0.13);
					currPad->SetRightMargin(0.15);
					currPad->SetTopMargin(0.1);
					currPad->SetBottomMargin(0.14);
					currPad->SetLogz(1);

					TString title = ((TH2D*) vecClusterEVsNCells[i].at(j))->GetTitle();
					EditTH2(((TH2D*) vecClusterEVsNCells[i].at(j)), 0.8, 0.8);
					((TH2D*) vecClusterEVsNCells[i].at(j))->SetTitle(" ");
					((TH2D*) vecClusterEVsNCells[i].at(j))->Draw();

					boxLabel2->Draw();
					TLatex *alice = new TLatex(0.12,0.93,title.Data());
					alice->SetNDC();
					alice->SetTextColor(1);
					alice->SetTextSize(0.08);
					alice->Draw();
				}
				SaveCanvas(canvas, Form("%s/ExtQA/hClusterEVsNCells_p%i.%s", outputDirDataSet.Data(), varDraw, suffix.Data()));

				iD = 1;
				varDraw = 0;
				canvas->Divide(4,4);
				for(Int_t j=0; j<(Int_t) vecClusterIncludedCells[i].size(); j++, iD++)
				{
					if( iD > 16 )
					{
						SaveCanvas(canvas, Form("%s/ExtQA/IncludedCells/hClusterIncludedCells_p%i.pdf", outputDirDataSet.Data(), varDraw++));
						canvas->Divide(4,4);
						iD = 1;
					}
					TPad* currPad = (TPad*) canvas->cd(iD);
					currPad->SetLeftMargin(0.13);
					currPad->SetRightMargin(0.15);
					currPad->SetTopMargin(0.1);
					currPad->SetBottomMargin(0.14);
					currPad->SetLogz(1);

					TString title = ((TH1D*) vecClusterIncludedCells[i].at(j))->GetTitle();
					EditTH1ForRunwise(((TH1D*) vecClusterIncludedCells[i].at(j)), 0.8, 0.9);
					((TH1D*) vecClusterIncludedCells[i].at(j))->SetTitle(" ");
					((TH1D*) vecClusterIncludedCells[i].at(j))->Draw();

					TLatex *alice = new TLatex(0.12,0.93,title.Data());
					alice->SetNDC();
					alice->SetTextColor(1);
					alice->SetTextSize(0.08);
					alice->Draw();
				}
				SaveCanvas(canvas, Form("%s/ExtQA/IncludedCells/hClusterIncludedCells_p%i.pdf", outputDirDataSet.Data(), varDraw));

				iD = 1;
				varDraw = 0;
				canvas->Divide(4,4);
				for(Int_t j=0; j<(Int_t) vecClusterIncludedCellsBefore[i].size(); j++, iD++)
				{
					if( iD > 16 )
					{
						SaveCanvas(canvas, Form("%s/ExtQA/IncludedCells/hClusterIncludedCellsBefore_p%i.pdf", outputDirDataSet.Data(), varDraw++));
						canvas->Divide(4,4);
						iD = 1;
					}
					TPad* currPad = (TPad*) canvas->cd(iD);
					currPad->SetLeftMargin(0.13);
					currPad->SetRightMargin(0.15);
					currPad->SetTopMargin(0.1);
					currPad->SetBottomMargin(0.14);
					currPad->SetLogz(1);

					TString title = ((TH1D*) vecClusterIncludedCellsBefore[i].at(j))->GetTitle();
					EditTH1ForRunwise(((TH1D*) vecClusterIncludedCellsBefore[i].at(j)), 0.8, 0.9);
					((TH1D*) vecClusterIncludedCellsBefore[i].at(j))->SetTitle(" ");
					((TH1D*) vecClusterIncludedCellsBefore[i].at(j))->Draw();

					TLatex *alice = new TLatex(0.12,0.93,title.Data());
					alice->SetNDC();
					alice->SetTextColor(1);
					alice->SetTextSize(0.08);
					alice->Draw();
				}
				SaveCanvas(canvas, Form("%s/ExtQA/IncludedCells/hClusterIncludedCellsBefore_p%i.pdf", outputDirDataSet.Data(), varDraw));

				iD = 1;
				varDraw = 0;
				canvas->Divide(4,4);
				for(Int_t j=0; j<(Int_t) vecClusterEFracCellsBefore[i].size(); j++, iD++)
				{
					if( iD > 16 )
					{
						SaveCanvas(canvas, Form("%s/ExtQA/EFrac/hClusterEFracCellsBefore_p%i.pdf", outputDirDataSet.Data(), varDraw++));
						canvas->Divide(4,4);
						iD = 1;
					}
					TPad* currPad = (TPad*) canvas->cd(iD);
					currPad->SetLeftMargin(0.13);
					currPad->SetRightMargin(0.15);
					currPad->SetTopMargin(0.1);
					currPad->SetBottomMargin(0.14);
					currPad->SetLogz(1);

					TString title = ((TH1D*) vecClusterEFracCellsBefore[i].at(j))->GetTitle();
					EditTH1ForRunwise(((TH1D*) vecClusterEFracCellsBefore[i].at(j)), 0.8, 0.9);
					((TH1D*) vecClusterEFracCellsBefore[i].at(j))->SetTitle(" ");
					((TH1D*) vecClusterEFracCellsBefore[i].at(j))->Draw();

					TLatex *alice = new TLatex(0.12,0.93,title.Data());
					alice->SetNDC();
					alice->SetTextColor(1);
					alice->SetTextSize(0.08);
					alice->Draw();
				}
				SaveCanvas(canvas, Form("%s/ExtQA/EFrac/hClusterEFracCellsBefore_p%i.pdf", outputDirDataSet.Data(), varDraw));

				iD = 1;
				varDraw = 0;
				canvas->Divide(4,4);
				for(Int_t j=0; j<(Int_t) vecClusterEFracCells[i].size(); j++, iD++)
				{
					if( iD > 16 )
					{
						SaveCanvas(canvas, Form("%s/ExtQA/EFrac/hClusterEFracCells_p%i.pdf", outputDirDataSet.Data(), varDraw++));
						canvas->Divide(4,4);
						iD = 1;
					}
					TPad* currPad = (TPad*) canvas->cd(iD);
					currPad->SetLeftMargin(0.13);
					currPad->SetRightMargin(0.15);
					currPad->SetTopMargin(0.1);
					currPad->SetBottomMargin(0.14);
					currPad->SetLogz(1);

					TString title = ((TH1D*) vecClusterEFracCells[i].at(j))->GetTitle();
					EditTH1ForRunwise(((TH1D*) vecClusterEFracCells[i].at(j)), 0.8, 0.9);
					((TH1D*) vecClusterEFracCells[i].at(j))->SetTitle(" ");
					((TH1D*) vecClusterEFracCells[i].at(j))->Draw();

					TLatex *alice = new TLatex(0.12,0.93,title.Data());
					alice->SetNDC();
					alice->SetTextColor(1);
					alice->SetTextSize(0.08);
					alice->Draw();
				}
				SaveCanvas(canvas, Form("%s/ExtQA/EFrac/hClusterEFracCells_p%i.pdf", outputDirDataSet.Data(), varDraw));
			}

			for(Int_t h=0; h<(Int_t) vecHistos[i].size(); h++)
			{
				((TH1D*) vecHistos[i].at(h))->SetTitle("");
				if(h==0) ((TH1D*) vecHistos[i].at(h))->Draw("p");
				else ((TH1D*) vecHistos[i].at(h))->Draw("px0e1");

				PutProcessLabelAndEnergyOnPlot(0.8, 0.9, 0.03, fCollisionSystem.Data(), plotDataSets[i].Data(), Form("%s clusters", calo.Data()));
				if(doTrigger && i<nData) PutProcessLabelAndEnergyOnPlot(0.8, 0.79, 0.03, fTrigger.Data(), "", "");

				if(h==0) SaveCanvas(canvas, Form("%s/%s.%s", outputDirDataSet.Data(), vecHistosName.at(h).Data(), suffix.Data()), kFALSE, kTRUE);
				else SaveCanvas(canvas, Form("%s/%s.%s", outputDirDataSet.Data(), vecHistosName.at(h).Data(), suffix.Data()));
			}
		}

//****************************** Drawing Runwise Histograms ************************************************
		cout << "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;
		cout << "Drawing Runwise Histograms" << endl;

		TCanvas* canvasRunwise;
		TLegend *legendRuns;

		for(Int_t i=0; i<nSets; i++)
		{
			vecRuns.clear();
			fDataSet = vecDataSet.at(i);
			fileRuns = Form("runNumbers%s.txt", fDataSet.Data());
			outputDirDataSet = Form("%s/%s",outputDir.Data(), plotDataSets[i].Data());

			if(doRunsFromDataLHC12 && i>=nData) {
				fileRuns = Form("runNumbers%s-%s.txt", vecDataSet.at(i).Data(),vecDataSet.at(0).Data());
				outputDirDataSet = Form("%s/%s-%s", outputDir.Data(), plotDataSets[i].Data(),plotDataSets[0].Data());
				cout << "Switch doRunsFromDataLHC12 is true, reading runs from: " << fileRuns.Data() << endl;
			}
			if(!readin(fileRuns, vecRuns, kFALSE)) {cout << "ERROR, no Run Numbers could be found! Returning..." << endl; return;}

			gSystem->Exec("mkdir -p "+outputDirDataSet+"/ExtQA");
			gSystem->Exec("mkdir -p "+outputDirDataSet+"/BadCells");

			Int_t NColumns = ((Int_t) vecRuns.size() / 31 ) + 1;

			//extending nHist for testing
			//for(Int_t i=123567; i<123667; i++) {globalRuns.push_back(Form("%i",i)); vecClusterEnergy[0].push_back(vecClusterEnergy[0].at(0));}

			canvasRunwise = new TCanvas("canvasRunwise","",200,10,1350+(NColumns*108),900);  // gives the page size
			DrawGammaCanvasSettings(canvasRunwise, 130.5/(1350.+(NColumns*108.)), (40.5+(NColumns*108.))/(1350.+(NColumns*108.)), topMargin, bottomMargin);
			canvasRunwise->cd();

			Double_t addRight = ((Double_t)NColumns*108)/(1350+((Double_t)NColumns*108));
			legendRuns = new TLegend(0.98-addRight,0.09,0.98,0.94);
			legendRuns->SetNColumns(NColumns);
			legendRuns->SetFillColor(0);
			legendRuns->SetLineColor(0);
			legendRuns->SetTextSize(0.03);
			legendRuns->SetTextFont(42);

			cout << "DataSet: " << plotDataSets[i].Data() << endl;
			TString fTrigger = "";
			if(i<nData){
				TString fTriggerCut = fEventCutSelection(3,2);
				fTrigger = AnalyseSpecialTriggerCut(fTriggerCut.Atoi(), plotDataSets[i]);
				cout << "Trigger: " << fTrigger.Data() << endl;
			}
		//---------
			for(Int_t h=0; h<(Int_t) vecClusterEnergy[i].size(); h++)
			{
				TString draw = (h==0)?"p":"p, same";
				EditRunwiseHists(((TH1D*) vecClusterEnergy[i].at(h)), h, "", 1E-8, 1);
				((TH1D*) vecClusterEnergy[i].at(h))->Draw(draw.Data());
				legendRuns->AddEntry(((TH1D*) vecClusterEnergy[i].at(h)),Form("%s",vecRuns.at(h).Data()),"p");
			}
			legendRuns->Draw();

			PutProcessLabelAndEnergyOnPlot(0.8-addRight, 0.91, 0.03, fCollisionSystem.Data(), Form("%s clusters", calo.Data()), plotDataSets[i].Data());
			if(doTrigger && i<nData) PutProcessLabelAndEnergyOnPlot(0.8-addRight, 0.8, 0.03, fTrigger.Data(), "", "");
			SaveCanvas(canvasRunwise, Form("%s/ClusterEnergy_Runwise_%s.%s", outputDirDataSet.Data(), plotDataSets[i].Data(),suffix.Data()),kTRUE,kTRUE);
			legendRuns->Clear();
		//---------
			for(Int_t h=0; h<(Int_t) vecClusterM02[i].size(); h++)
			{
				TString draw = (h==0)?"p":"p, same";
				EditRunwiseHists(((TH1D*) vecClusterM02[i].at(h)), h, "", 1E-6, 1);
				((TH1D*) vecClusterM02[i].at(h))->Draw(draw.Data());
				legendRuns->AddEntry(((TH1D*) vecClusterM02[i].at(h)),Form("%s",vecRuns.at(h).Data()),"p");
			}
			legendRuns->Draw();

			PutProcessLabelAndEnergyOnPlot(0.8-addRight, 0.91, 0.03, fCollisionSystem.Data(), Form("%s clusters", calo.Data()), plotDataSets[i].Data());
			if( doTrigger && i<nData) PutProcessLabelAndEnergyOnPlot(0.8-addRight, 0.8, 0.03, fTrigger.Data(), "", "");
			SaveCanvas(canvasRunwise, Form("%s/ClusterM02_Runwise_%s.%s", outputDirDataSet.Data(), plotDataSets[i].Data(),suffix.Data()),kFALSE,kTRUE);
			legendRuns->Clear();
		//---------
			for(Int_t h=0; h<(Int_t) vecClusterM20[i].size(); h++)
			{
				TString draw = (h==0)?"p":"p, same";
				EditRunwiseHists(((TH1D*) vecClusterM20[i].at(h)), h, "", 1E-8, 1);
				((TH1D*) vecClusterM20[i].at(h))->Draw(draw.Data());
				legendRuns->AddEntry(((TH1D*) vecClusterM20[i].at(h)),Form("%s",vecRuns.at(h).Data()),"p");
			}
			legendRuns->Draw();

			PutProcessLabelAndEnergyOnPlot(0.8-addRight, 0.91, 0.03, fCollisionSystem.Data(), Form("%s clusters", calo.Data()), plotDataSets[i].Data());
			if( doTrigger && i<nData) PutProcessLabelAndEnergyOnPlot(0.8-addRight, 0.8, 0.03, fTrigger.Data(), "", "");
			SaveCanvas(canvasRunwise, Form("%s/ClusterM20_Runwise_%s.%s", outputDirDataSet.Data(), plotDataSets[i].Data(),suffix.Data()),kFALSE,kTRUE);
			legendRuns->Clear();
		//---------
			for(Int_t h=0; h<(Int_t) vecClusterNCells[i].size(); h++)
			{
				TString draw = (h==0)?"p":"p, same";
				EditRunwiseHists(((TH1D*) vecClusterNCells[i].at(h)), h, "", 1E-8, 1);
				((TH1D*) vecClusterNCells[i].at(h))->Draw(draw.Data());
				legendRuns->AddEntry(((TH1D*) vecClusterNCells[i].at(h)),Form("%s",vecRuns.at(h).Data()),"p");
			}
			legendRuns->Draw();

			PutProcessLabelAndEnergyOnPlot(0.8-addRight, 0.91, 0.03, fCollisionSystem.Data(), Form("%s clusters", calo.Data()), plotDataSets[i].Data());
			if( doTrigger && i<nData) PutProcessLabelAndEnergyOnPlot(0.8-addRight, 0.8, 0.03, fTrigger.Data(), "", "");
			SaveCanvas(canvasRunwise, Form("%s/ClusterNCells_Runwise_%s.%s", outputDirDataSet.Data(), plotDataSets[i].Data(),suffix.Data()),kTRUE,kTRUE);
			legendRuns->Clear();
		//---------
			for(Int_t h=0; h<(Int_t) vecClusterDispersion[i].size(); h++)
			{
				TString draw = (h==0)?"p":"p, same";
				EditRunwiseHists(((TH1D*) vecClusterDispersion[i].at(h)), h, "", 1E-7, 1);
				((TH1D*) vecClusterDispersion[i].at(h))->Draw(draw.Data());
				legendRuns->AddEntry(((TH1D*) vecClusterDispersion[i].at(h)),Form("%s",vecRuns.at(h).Data()),"p");
			}
			legendRuns->Draw();

			PutProcessLabelAndEnergyOnPlot(0.8-addRight, 0.91, 0.03, fCollisionSystem.Data(), Form("%s clusters", calo.Data()), plotDataSets[i].Data());
			if( doTrigger && i<nData) PutProcessLabelAndEnergyOnPlot(0.8-addRight, 0.8, 0.03, fTrigger.Data(), "", "");
			SaveCanvas(canvasRunwise, Form("%s/ClusterDispersion_Runwise_%s.%s", outputDirDataSet.Data(), plotDataSets[i].Data(),suffix.Data()),kFALSE,kTRUE);
			legendRuns->Clear();
		//---------
			TGaxis::SetExponentOffset(0.5, 0, "x");
			for(Int_t h=0; h<(Int_t) vecClusterTime[i].size(); h++)
			{
				TString draw = (h==0)?"p":"p, same";
				EditRunwiseHists(((TH1D*) vecClusterTime[i].at(h)), h, "", 1E-7, 1E-1);
				((TH1D*) vecClusterTime[i].at(h))->GetXaxis()->SetNoExponent(kFALSE);
				((TH1D*) vecClusterTime[i].at(h))->Draw(draw.Data());
				legendRuns->AddEntry(((TH1D*) vecClusterTime[i].at(h)),Form("%s",vecRuns.at(h).Data()),"p");
			}
			legendRuns->Draw();

			PutProcessLabelAndEnergyOnPlot(0.8-addRight, 0.91, 0.03, fCollisionSystem.Data(), Form("%s clusters", calo.Data()), plotDataSets[i].Data());
			if( doTrigger && i<nData) PutProcessLabelAndEnergyOnPlot(0.8-addRight, 0.8, 0.03, fTrigger.Data(), "", "");
			SaveCanvas(canvasRunwise, Form("%s/ClusterTime_Runwise_%s.%s", outputDirDataSet.Data(), plotDataSets[i].Data(),suffix.Data()),kFALSE,kTRUE);
			legendRuns->Clear();
			TGaxis::SetExponentOffset(0, 0, "x");
		//---------
			TGaxis::SetExponentOffset(0.013, -0.0285, "x");
			for(Int_t h=0; h<(Int_t) vecClusterDeltaEta[i].size(); h++)
			{
				TString draw = (h==0)?"p":"p, same";
				EditRunwiseHists(((TH1D*) vecClusterDeltaEta[i].at(h)), h, "", 5E-4, 0.5);
				((TH1D*) vecClusterDeltaEta[i].at(h))->GetXaxis()->SetNoExponent(kFALSE);
				((TH1D*) vecClusterDeltaEta[i].at(h))->Draw(draw.Data());
				legendRuns->AddEntry(((TH1D*) vecClusterDeltaEta[i].at(h)),Form("%s",vecRuns.at(h).Data()),"p");
			}
			legendRuns->Draw();

			PutProcessLabelAndEnergyOnPlot(0.8-addRight, 0.91, 0.03, fCollisionSystem.Data(), Form("%s clusters", calo.Data()), plotDataSets[i].Data());
			if( doTrigger && i<nData) PutProcessLabelAndEnergyOnPlot(0.8-addRight, 0.8, 0.03, fTrigger.Data(), "", "");
			SaveCanvas(canvasRunwise, Form("%s/ClusterDeltaEta_Runwise_%s.%s", outputDirDataSet.Data(), plotDataSets[i].Data(),suffix.Data()),kFALSE,kTRUE);
			legendRuns->Clear();
		//---------
			for(Int_t h=0; h<(Int_t) vecClusterDeltaPhi[i].size(); h++)
			{
				TString draw = (h==0)?"p":"p, same";
				EditRunwiseHists(((TH1D*) vecClusterDeltaPhi[i].at(h)), h, "", 1E-4, 0.2);
				((TH1D*) vecClusterDeltaPhi[i].at(h))->GetXaxis()->SetNoExponent(kFALSE);
				((TH1D*) vecClusterDeltaPhi[i].at(h))->Draw(draw.Data());
				legendRuns->AddEntry(((TH1D*) vecClusterDeltaPhi[i].at(h)),Form("%s",vecRuns.at(h).Data()),"p");
			}
			legendRuns->Draw();

			PutProcessLabelAndEnergyOnPlot(0.8-addRight, 0.91, 0.03, fCollisionSystem.Data(), Form("%s clusters", calo.Data()), plotDataSets[i].Data());
			if( doTrigger && i<nData) PutProcessLabelAndEnergyOnPlot(0.8-addRight, 0.8, 0.03, fTrigger.Data(), "", "");
			SaveCanvas(canvasRunwise, Form("%s/ClusterDeltaPhi_Runwise_%s.%s", outputDirDataSet.Data(), plotDataSets[i].Data(),suffix.Data()),kFALSE,kTRUE);
			legendRuns->Clear();
			TGaxis::SetExponentOffset(0, 0, "x");
		//---------
			for(Int_t h=0; h<(Int_t) vecClusterPi0ConvPhotonEta[i].size(); h++)
			{
				TString draw = (h==0)?"p":"p, same";
				EditRunwiseHists(((TH1D*) vecClusterPi0ConvPhotonEta[i].at(h)), h, "", 3E-8, 1E-3);
				((TH1D*) vecClusterPi0ConvPhotonEta[i].at(h))->Draw(draw.Data());
				legendRuns->AddEntry(((TH1D*) vecClusterPi0ConvPhotonEta[i].at(h)),Form("%s",vecRuns.at(h).Data()),"p");
			}
			legendRuns->Draw();

			PutProcessLabelAndEnergyOnPlot(0.8-addRight, 0.91, 0.03, fCollisionSystem.Data(), Form("%s clusters", calo.Data()), plotDataSets[i].Data());
			if( doTrigger && i<nData) PutProcessLabelAndEnergyOnPlot(0.8-addRight, 0.8, 0.03, fTrigger.Data(), "", "");
			SaveCanvas(canvasRunwise, Form("%s/ClusterPi0ConvPhotonEta_Runwise_%s.%s", outputDirDataSet.Data(), plotDataSets[i].Data(),suffix.Data()),kFALSE,kTRUE);
			legendRuns->Clear();
		//---------
			for(Int_t h=0; h<(Int_t) vecClusterPi0ConvPhotonPhi[i].size(); h++)
			{
				TString draw = (h==0)?"p":"p, same";
				EditRunwiseHists(((TH1D*) vecClusterPi0ConvPhotonPhi[i].at(h)), h, "", 1E-8, 1E-3);
				((TH1D*) vecClusterPi0ConvPhotonPhi[i].at(h))->Draw(draw.Data());
				legendRuns->AddEntry(((TH1D*) vecClusterPi0ConvPhotonPhi[i].at(h)),Form("%s",vecRuns.at(h).Data()),"p");
			}
			legendRuns->Draw();

			PutProcessLabelAndEnergyOnPlot(0.8-addRight, 0.91, 0.03, fCollisionSystem.Data(), Form("%s clusters", calo.Data()), plotDataSets[i].Data());
			if( doTrigger && i<nData) PutProcessLabelAndEnergyOnPlot(0.8-addRight, 0.8, 0.03, fTrigger.Data(), "", "");
			SaveCanvas(canvasRunwise, Form("%s/ClusterPi0ConvPhotonPhi_Runwise_%s.%s", outputDirDataSet.Data(), plotDataSets[i].Data(),suffix.Data()),kFALSE,kTRUE);
			legendRuns->Clear();
		//--------
			for(Int_t h=0; h<(Int_t) vecClusterEtaConvPhotonEta[i].size(); h++)
			{
				TString draw = (h==0)?"p":"p, same";
				EditRunwiseHists(((TH1D*) vecClusterEtaConvPhotonEta[i].at(h)), h, "", 1E-7, 1E-3);
				((TH1D*) vecClusterEtaConvPhotonEta[i].at(h))->Draw(draw.Data());
				legendRuns->AddEntry(((TH1D*) vecClusterEtaConvPhotonEta[i].at(h)),Form("%s",vecRuns.at(h).Data()),"p");
			}
			legendRuns->Draw();

			PutProcessLabelAndEnergyOnPlot(0.8-addRight, 0.91, 0.03, fCollisionSystem.Data(), Form("%s clusters", calo.Data()), plotDataSets[i].Data());
			if( doTrigger && i<nData) PutProcessLabelAndEnergyOnPlot(0.8-addRight, 0.8, 0.03, fTrigger.Data(), "", "");
			SaveCanvas(canvasRunwise, Form("%s/ClusterEtaConvPhotonEta_Runwise_%s.%s", outputDirDataSet.Data(), plotDataSets[i].Data(),suffix.Data()),kFALSE,kTRUE);
			legendRuns->Clear();
		//---------
			for(Int_t h=0; h<(Int_t) vecClusterEtaConvPhotonPhi[i].size(); h++)
			{
				TString draw = (h==0)?"p":"p, same";
				EditRunwiseHists(((TH1D*) vecClusterEtaConvPhotonPhi[i].at(h)), h, "", 1E-8, 1E-3);
				((TH1D*) vecClusterEtaConvPhotonPhi[i].at(h))->Draw(draw.Data());
				legendRuns->AddEntry(((TH1D*) vecClusterEtaConvPhotonPhi[i].at(h)),Form("%s",vecRuns.at(h).Data()),"p");
			}
			legendRuns->Draw();

			PutProcessLabelAndEnergyOnPlot(0.8-addRight, 0.91, 0.03, fCollisionSystem.Data(), Form("%s clusters", calo.Data()), plotDataSets[i].Data());
			if( doTrigger && i<nData) PutProcessLabelAndEnergyOnPlot(0.8-addRight, 0.8, 0.03, fTrigger.Data(), "", "");
			SaveCanvas(canvasRunwise, Form("%s/ClusterEtaConvPhotonPhi_Runwise_%s.%s", outputDirDataSet.Data(), plotDataSets[i].Data(),suffix.Data()),kFALSE,kTRUE);
			legendRuns->Clear();
		//--------
			if(doExtQA>0){
				for(Int_t iModule=0; iModule<nCaloModules; iModule++){
					for(Int_t h=0; h<(Int_t) vecClusterEVsModule[i][iModule].size(); h++)
					{
						TString draw = (h==0)?"p":"p, same";
						EditRunwiseHists(((TH1D*) vecClusterEVsModule[i][iModule].at(h)), h, "", 1E-8, 1E-1);
						((TH1D*) vecClusterEVsModule[i][iModule].at(h))->Draw(draw.Data());
						legendRuns->AddEntry(((TH1D*) vecClusterEVsModule[i][iModule].at(h)),Form("%s",vecRuns.at(h).Data()),"p");
					}
					legendRuns->Draw();

					PutProcessLabelAndEnergyOnPlot(0.8-addRight, 0.91, 0.03, fCollisionSystem.Data(), Form("%s clusters", calo.Data()), plotDataSets[i].Data());
					if( doTrigger && i<nData) PutProcessLabelAndEnergyOnPlot(0.8-addRight, 0.8, 0.03, fTrigger.Data(), "", "");
					SaveCanvas(canvasRunwise, Form("%s/ExtQA/ClusterEVsModule%i_Runwise_%s.%s",outputDirDataSet.Data(),iModule,plotDataSets[i].Data(),suffix.Data()),kTRUE,kTRUE);
					legendRuns->Clear();
					for(Int_t h=0; h<(Int_t) vecModuleEVsModule[i][iModule].size(); h++)
					{
						TString draw = (h==0)?"p":"p, same";
						EditRunwiseHists(((TH1D*) vecModuleEVsModule[i][iModule].at(h)), h, "", 1E-8, 1);
						((TH1D*) vecModuleEVsModule[i][iModule].at(h))->Draw(draw.Data());
						legendRuns->AddEntry(((TH1D*) vecModuleEVsModule[i][iModule].at(h)),Form("%s",vecRuns.at(h).Data()),"p");
					}
					legendRuns->Draw();

					PutProcessLabelAndEnergyOnPlot(0.8-addRight, 0.91, 0.03, fCollisionSystem.Data(), Form("%s clusters", calo.Data()), plotDataSets[i].Data());
					if( doTrigger && i<nData) PutProcessLabelAndEnergyOnPlot(0.8-addRight, 0.8, 0.03, fTrigger.Data(), "", "");
					SaveCanvas(canvasRunwise, Form("%s/ExtQA/ModuleEVsModule%i_Runwise_%s.%s",outputDirDataSet.Data(),iModule,plotDataSets[i].Data(),suffix.Data()),kTRUE,kTRUE);
					legendRuns->Clear();
					for(Int_t h=0; h<(Int_t) vecClusterNCells100VsModule[i][iModule].size(); h++)
					{
						TString draw = (h==0)?"p":"p, same";
						EditRunwiseHists(((TH1D*) vecClusterNCells100VsModule[i][iModule].at(h)), h, "", 1E-8, 1);
						((TH1D*) vecClusterNCells100VsModule[i][iModule].at(h))->Draw(draw.Data());
						legendRuns->AddEntry(((TH1D*) vecClusterNCells100VsModule[i][iModule].at(h)),Form("%s",vecRuns.at(h).Data()),"p");
					}
					legendRuns->Draw();

					PutProcessLabelAndEnergyOnPlot(0.8-addRight, 0.91, 0.03, fCollisionSystem.Data(), Form("%s clusters", calo.Data()), plotDataSets[i].Data());
					if( doTrigger && i<nData) PutProcessLabelAndEnergyOnPlot(0.8-addRight, 0.8, 0.03, fTrigger.Data(), "", "");
					SaveCanvas(canvasRunwise, Form("%s/ExtQA/NCells100VsModule%i_Runwise_%s.%s",outputDirDataSet.Data(),iModule,plotDataSets[i].Data(),suffix.Data()),kTRUE,kTRUE);
					legendRuns->Clear();
					for(Int_t h=0; h<(Int_t) vecClusterNCells1500VsModule[i][iModule].size(); h++)
					{
						TString draw = (h==0)?"p":"p, same";
						EditRunwiseHists(((TH1D*) vecClusterNCells1500VsModule[i][iModule].at(h)), h, "", 1E-8, 1);
						((TH1D*) vecClusterNCells1500VsModule[i][iModule].at(h))->Draw(draw.Data());
						legendRuns->AddEntry(((TH1D*) vecClusterNCells1500VsModule[i][iModule].at(h)),Form("%s",vecRuns.at(h).Data()),"p");
					}
					legendRuns->Draw();

					PutProcessLabelAndEnergyOnPlot(0.8-addRight, 0.91, 0.03, fCollisionSystem.Data(), Form("%s clusters", calo.Data()), plotDataSets[i].Data());
					if( doTrigger && i<nData) PutProcessLabelAndEnergyOnPlot(0.8-addRight, 0.8, 0.03, fTrigger.Data(), "", "");
					SaveCanvas(canvasRunwise, Form("%s/ExtQA/NCells1500VsModule%i_Runwise_%s.%s",outputDirDataSet.Data(),iModule,plotDataSets[i].Data(),suffix.Data()),kTRUE,kTRUE);
					legendRuns->Clear();
				}
			}

			if(doExtQA==2){
				Int_t hC = 0;
				for(Int_t iBad=0; iBad<(Int_t)vecBadCells[i].size(); iBad++){
					hC = 0;
					for(Int_t h=0; h<(Int_t) vecBadCellsEnergy[i].size(); h++){
						if(h%(Int_t)vecBadCells[i].size()!=iBad) continue;
						TString draw = (hC==0)?"p":"p, same";
						EditRunwiseHists(((TH1D*) vecBadCellsEnergy[i].at(h)), hC, "", 1E-8, 1);
						((TH1D*) vecBadCellsEnergy[i].at(h))->GetXaxis()->SetNoExponent(kFALSE);
						((TH1D*) vecBadCellsEnergy[i].at(h))->Draw(draw.Data());
						legendRuns->AddEntry(((TH1D*) vecBadCellsEnergy[i].at(h)),Form("%s",vecRuns.at(hC).Data()),"p");
						hC++;
					}
					legendRuns->Draw();

					PutProcessLabelAndEnergyOnPlot(0.8-addRight, 0.91, 0.03, fCollisionSystem.Data(), Form("%s clusters", calo.Data()), plotDataSets[i].Data());
					if( doTrigger && i<nData) PutProcessLabelAndEnergyOnPlot(0.8-addRight, 0.8, 0.03, fTrigger.Data(), "", "");
					SaveCanvas(canvasRunwise, Form("%s/BadCells/Cell%i_Energy_%s.%s",outputDirDataSet.Data(),((TString)vecBadCells[i].at(iBad)).Atoi(),plotDataSets[i].Data(),suffix.Data()),kFALSE,kTRUE);
					legendRuns->Clear();

					hC = 0;
					for(Int_t h=0; h<(Int_t) vecBadCellsTime[i].size(); h++){
						if(h%(Int_t)vecBadCells[i].size()!=iBad) continue;
						TString draw = (hC==0)?"p":"p, same";
						EditRunwiseHists(((TH1D*) vecBadCellsTime[i].at(h)), hC, "", 1E-8, 1);
						((TH1D*) vecBadCellsTime[i].at(h))->GetXaxis()->SetNoExponent(kFALSE);
						((TH1D*) vecBadCellsTime[i].at(h))->Draw(draw.Data());
						legendRuns->AddEntry(((TH1D*) vecBadCellsTime[i].at(h)),Form("%s",vecRuns.at(hC).Data()),"p");
						hC++;
					}
					legendRuns->Draw();

					PutProcessLabelAndEnergyOnPlot(0.8-addRight, 0.91, 0.03, fCollisionSystem.Data(), Form("%s clusters", calo.Data()), plotDataSets[i].Data());
					if( doTrigger && i<nData) PutProcessLabelAndEnergyOnPlot(0.8-addRight, 0.8, 0.03, fTrigger.Data(), "", "");
					SaveCanvas(canvasRunwise, Form("%s/BadCells/Cell%i_Time_%s.%s",outputDirDataSet.Data(),((TString)vecBadCells[i].at(iBad)).Atoi(),plotDataSets[i].Data(),suffix.Data()),kFALSE,kTRUE);
					legendRuns->Clear();
				}
			}
		//--------
			delete legendRuns;
			delete canvasRunwise;
		}

		canvas->cd();
	}

//****************************** Combined Trending Histograms ************************************************
	cout << "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;
	cout << "Drawing Trending Histograms" << endl;
//---------
	if(doRunsFromDataLHC12) cout << "WARNING: doRunsFromDataLHC12 is true, overwriting histograms for DataSet!" << endl;

	TLegend *legend = new TLegend(0.12,0.95,0.9,0.98);
	legend->SetNColumns(nSets);
	legend->SetFillColor(0);
	legend->SetLineColor(0);
	legend->SetTextSize(0.03);
	legend->SetTextFont(42);
//---------
	if(nSets > 1)
	{
		for(Int_t h=0; h<(Int_t) vecHistos[0].size(); h++)
		{
			TString fTrigger = "";
			TString fTriggerCut = fEventCutSelection(3,2);
			for(Int_t i=0; i<nSets; i++)
			{
				if(doTrigger && i<nData && i==0) fTrigger = AnalyseSpecialTriggerCut(fTriggerCut.Atoi(), plotDataSets[i]);
				legend->AddEntry(((TH1D*) vecHistos[i].at(h)),plotDataSets[i].Data(),"p");
			}
			for(Int_t i=nSets-1; i>=0; i--)
			{
				TString draw;
				if(h==0) draw = (i==nSets-1)?"p":"p, same";
				else draw = (i==nSets-1)?"px0e1":"px0e1, same";
				((TH1D*) vecHistos[i].at(h))->SetTitle("");
				((TH1D*) vecHistos[i].at(h))->Draw(draw.Data());
			}
			legend->Draw();
			PutProcessLabelAndEnergyOnPlot(0.8, 0.9, 0.03, fCollisionSystem.Data(), Form("%s clusters", calo.Data()), fTrigger.Data());
			if(doRunsFromDataLHC12){
				if(h==0||h==20) SaveCanvas(canvas, Form("%s/%s/%s.%s", outputDir.Data(), select.Data(),vecHistosName.at(h).Data(),suffix.Data()), kFALSE, kTRUE);
				else SaveCanvas(canvas, Form("%s/%s/%s.%s", outputDir.Data(), select.Data(),vecHistosName.at(h).Data(),suffix.Data()));
			}
			else{
				if(h==0||h==20) SaveCanvas(canvas, Form("%s/%s.%s", outputDir.Data(), vecHistosName.at(h).Data(),suffix.Data()), kFALSE, kTRUE);
				else SaveCanvas(canvas, Form("%s/%s.%s", outputDir.Data(), vecHistosName.at(h).Data(),suffix.Data()));
			}
			legend->Clear();
		}
	}

//****************************** Combined Ratio Trending Histograms ************************************************
//	cout << "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;
//	cout << "Drawing Ratio Trending Histograms" << endl;

//    TString ratioSets[nData][nSets-nData];
//    TH1D* ratio[nData][nSets-nData];
//    Style_t hComMarkerStyle[nSets-nData];

//	if(nSets>1 && nSets>nData)
//    {
//        legend->SetNColumns(nData*(nSets-nData));

//		for(Int_t h=0; h<(Int_t) vecHistos[0].size(); h++)
//        {
//            for(Int_t i=0; i<nData; i++)
//            {
//                for(Int_t j=0; j<nSets-nData; j++)
//                {
//                    ratioSets[i][j]=Form("%s / %s", plotDataSets[i].Data(), plotDataSets[j+nData].Data());
//                    hComMarkerStyle[j]=29+j;
//                    ratio[i][j] = new TH1D(Form("%s%i%i",((TH1D*) vecHistos[i].at(h))->GetName(),i,j),
//                                           Form("%s%i%i;%s;%s - Ratio: Data / MC",((TH1D*) vecHistos[i].at(h))->GetTitle(),i,j,((TH1D*) vecHistos[i].at(h))->GetXaxis()->GetTitle(),((TH1D*) vecHistos[i].at(h))->GetYaxis()->GetTitle()),
//                                           hNBin,hFBin,hLBin);
//                    if(iCalo==1){
//                        if(h==0) ratio[i][j]->GetYaxis()->SetRangeUser(0,10);
//                        else ratio[i][j]->GetYaxis()->SetRangeUser(0,2);
//                    }
//                    if(iCalo==2){
//                        if(h==0||h==5) ratio[i][j]->GetYaxis()->SetRangeUser(0,10);
//                        else ratio[i][j]->GetYaxis()->SetRangeUser(0,2);
//                    }
//					EditTH1(globalRuns, doEquidistantXaxis, ratio[i][j], hComMarkerStyle[j], hMarkerSize[i], hMarkerColor[i], hLineColor[i]);
//                }
//            }

//            for(Int_t i=0; i<nData; i++)
//            {
//                for(Int_t b=1; b<hNBin+1; b++)
//                {
//                    Double_t hData = ((TH1D*) vecHistos[i].at(h))->GetBinContent(b);
//                    for(Int_t j=0; j<nSets-nData; j++)
//                    {
//                        Double_t hMC = ((TH1D*) vecHistos[j+nData].at(h))->GetBinContent(b);
//                        if(hData>0&&hMC>0) ratio[i][j]->SetBinContent(b,hData/hMC);
//                        else if(hData>0&&hMC==0) ratio[i][j]->SetBinContent(b,0.02);
//                    }
//                }
//            }

//            for(Int_t i=0; i<nData; i++)
//            {
//                for(Int_t j=0; j<nSets-nData; j++)
//                {
//                    TString draw = (i==0&&j==0)?"p":"p, same";
//                    ratio[i][j]->SetTitle("");
//                    ratio[i][j]->Draw(draw.Data());
//                    legend->AddEntry(ratio[i][j],ratioSets[i][j],"p");
//                }
//            }

//            legend->Draw();
//            legend->Clear();

//            for(Int_t i=0; i<nData; i++)
//            {
//                for(Int_t j=0; j<nSets-nData; j++)
//                {
//                    delete ratio[i][j];
//                }
//            }
//        }
//	}else cout << "...skipped due to nSets<=1 or nSets==nData!" << endl;

	delete legend;
	delete canvas;

//****************************** Create Output ROOT-File ************************************************

	const char* nameOutput;

	for(Int_t i=0; i<nSets; i++)
	{
		fDataSet = vecDataSet.at(i);

		nameOutput = Form("%s/%s/ClusterQA/%s_ClusterQARunwise_pPb.root",fCutSelection.Data(),fEnergyFlag.Data(),fDataSet.Data());

		TFile* fOutput = new TFile(nameOutput,"RECREATE");
		cout << "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;
		cout << "Output file: " << nameOutput << endl;
		cout << "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;
		fLog[i] << "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;
		fLog[i] << "Output file: " << nameOutput << endl;
		fLog[i] << "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;

		for(Int_t h=0; h<(Int_t) vecHistos[i].size(); h++)
		{
			WriteHistogram(((TH1D*) vecHistos[i].at(h)));
		}

		TDirectory *EtaPhi = fOutput->mkdir("EtaVsPhi");
		EtaPhi->cd();
		for(Int_t j=0; j<(Int_t) vecClusterEtaPhi[i].size(); j++)
		{
			WriteHistogram((TH2D*) vecClusterEtaPhi[i].at(j));
			delete (TH2D*) vecClusterEtaPhi[i].at(j);
		}

		if(doExtQA>0){
			TDirectory *ClusterEVsNCells = fOutput->mkdir("ClusterEVsNCells");
			ClusterEVsNCells->cd();
			for(Int_t j=0; j<(Int_t) vecClusterEVsNCells[i].size(); j++)
			{
				WriteHistogram((TH2D*) vecClusterEVsNCells[i].at(j));
				delete (TH2D*) vecClusterEVsNCells[i].at(j);
			}
			TDirectory *IncludedCells = fOutput->mkdir("IncludedCells");
			IncludedCells->cd();
			for(Int_t j=0; j<(Int_t) vecClusterIncludedCells[i].size(); j++)
			{
				WriteHistogram((TH1D*) vecClusterIncludedCells[i].at(j));
				delete (TH1D*) vecClusterIncludedCells[i].at(j);
			}
			TDirectory *IncludedCells_beforeQA = fOutput->mkdir("IncludedCells_beforeQA");
			IncludedCells_beforeQA->cd();
			for(Int_t j=0; j<(Int_t) vecClusterIncludedCellsBefore[i].size(); j++)
			{
				WriteHistogram((TH1D*) vecClusterIncludedCellsBefore[i].at(j));
				delete (TH1D*) vecClusterIncludedCellsBefore[i].at(j);
			}
			TDirectory *EFracCells = fOutput->mkdir("EFracCells");
			EFracCells->cd();
			for(Int_t j=0; j<(Int_t) vecClusterEFracCells[i].size(); j++)
			{
				WriteHistogram((TH1D*) vecClusterEFracCells[i].at(j));
				delete (TH1D*) vecClusterEFracCells[i].at(j);
			}
			TDirectory *EFracCells_beforeQA = fOutput->mkdir("EFracCells_beforeQA");
			EFracCells_beforeQA->cd();
			for(Int_t j=0; j<(Int_t) vecClusterEFracCellsBefore[i].size(); j++)
			{
				WriteHistogram((TH1D*) vecClusterEFracCellsBefore[i].at(j));
				delete (TH1D*) vecClusterEFracCellsBefore[i].at(j);
			}
			if(doExtQA==2){
				TDirectory *ClusterEMeanVsSigma = fOutput->mkdir("ClusterEMeanVsSigma");
				ClusterEMeanVsSigma->cd();
				for(Int_t j=0; j<(Int_t) vecClusterEnergyMeanSigma[i].size(); j++)
				{
					WriteHistogram((TH2D*) vecClusterEnergyMeanSigma[i].at(j));
					delete (TH2D*) vecClusterEnergyMeanSigma[i].at(j);
				}
				TDirectory *ClusterTimeMeanVsSigma = fOutput->mkdir("ClusterTimeMeanVsSigma");
				ClusterTimeMeanVsSigma->cd();
				for(Int_t j=0; j<(Int_t) vecClusterTimeMeanSigma[i].size(); j++)
				{
					WriteHistogram((TH2D*) vecClusterTimeMeanSigma[i].at(j));
					delete (TH2D*) vecClusterTimeMeanSigma[i].at(j);
				}
			}
		}

		fOutput->Write();
		fOutput->Close();
		fLog[i].close();
		if(doExtQA==2) fLogRunwiseBadCells[i].close();
		if(doExtQA==2) fLogRunwiseDeadCells[i].close();
	}

	if(doExtQA==2){
		std::vector <TString> vec[nSets];
		std::map <Int_t,Int_t> ma[nSets];
		TH1D* nCellsRun[nSets];
		Int_t nRuns[nSets];
		TCanvas* cvsRun = new TCanvas("canvas","",200,10,1350,900);  // gives the page size
		DrawGammaCanvasSettings(cvsRun, leftMar, rightMar, topMargin, bottomMargin);

		for(Int_t iStr=0; iStr<nSets; iStr++){
			nRuns[iStr]=0;
			fLogRunwiseBadCells[iStr].open(Form("%s/BadCellsRunwise-%s.log",outputDir.Data(),DataSets[iStr].Data()), ios::in);
			if(fLogRunwiseBadCells[iStr].good())
			{
				fLogRunwiseBadCells[iStr].seekg(0L, ios::beg);
				TString fVar;
				while(!fLogRunwiseBadCells[iStr].eof())
				{
					fLogRunwiseBadCells[iStr] >> fVar;
					if(fVar.BeginsWith("Run-")) {
						nRuns[iStr]++;
						vec[iStr].push_back(fVar);
					}
					else if(fVar.BeginsWith("NoNoisy")||fVar.BeginsWith("NotEnough")){
						continue;
					}
					else if(fVar.Sizeof()>1) {
						TObjArray *rNumber = fVar.Tokenize("-");
						TObjString* rString = (TObjString*)rNumber->At(0);
						TString vecString = rString->GetString();
						vec[iStr].push_back(vecString);
						if( ma[iStr].find(vecString.Atoi()) != ma[iStr].end() ) ma[iStr][vecString.Atoi()] += 1;
						else ma[iStr][vecString.Atoi()] = 1;
					}
				}
			}

			if((Int_t)ma[iStr].size()==0){
				cout << "No Bad Cells found for: " << DataSets[iStr].Data() << endl;
				continue;
			}

			Int_t plotting = 0;
			Int_t nPlot = 100;
			Int_t nPart = 0;
			map<Int_t, Int_t>::iterator it = ma[iStr].begin();
			do
			{
				plotting+=nPlot;
				if(plotting>(Int_t)ma[iStr].size()){
					plotting -= nPlot;
					nPlot = ma[iStr].size()-plotting;
					plotting = ma[iStr].size();
				}
				nCellsRun[iStr] = new TH1D(Form("%s, %i runs, %s clusters",DataSets[iStr].Data(), nRuns[iStr], calo.Data()),Form("%s, %i runs, Runwise Hot Cells for %s; CellID; Number of Runs",DataSets[iStr].Data(), nRuns[iStr], calo.Data()),nPlot,0,nPlot);
				OnlyEditTH1(nCellsRun[iStr], 20, 1, kBlack, kBlack);

				for (Int_t h=1; h<=nPlot; it++,h++){
					if(it == ma[iStr].end()) {cout << "ERROR while plotting BadCellsRunwiseOverview" << endl;break;}
					nCellsRun[iStr]->GetXaxis()->SetBinLabel(h,Form("%i",it->first));
					nCellsRun[iStr]->SetBinContent(h,it->second);
				}
				nCellsRun[iStr]->SetFillStyle(3004);
				nCellsRun[iStr]->SetFillColor(1);
				nCellsRun[iStr]->Draw();
				if(doRunsFromDataLHC12 && iStr>=nData) SaveCanvas(cvsRun, Form("%s/%s-%s/%s_%i.%s", outputDir.Data(), plotDataSets[iStr].Data(),plotDataSets[0].Data(), "BadCells_FiredInNRuns",nPart++,suffix.Data()));
				else SaveCanvas(cvsRun, Form("%s/%s/%s_%i.%s", outputDir.Data(), plotDataSets[iStr].Data(), "BadCells_FiredInNRuns",nPart++,suffix.Data()));
				delete nCellsRun[iStr];
			}while(plotting < (Int_t)ma[iStr].size());

			plotting = 0;
			nPlot = 100;
			nPart = 0;
			Int_t posInVec = 0;
			std::vector<TString>::iterator itVec = vec[iStr].begin();
			do
			{
				plotting+=nPlot;
				if(plotting>nRuns[iStr]){
					plotting -= nPlot;
					nPlot = nRuns[iStr]-plotting;
					plotting = nRuns[iStr];
				}
				nCellsRun[iStr] = new TH1D(Form("%s, %i runs, %s clusters",DataSets[iStr].Data(), nRuns[iStr], calo.Data()),Form("%s, %i runs, Runwise Hot Cells for %s; Run Number; Number of Hot Cells",DataSets[iStr].Data(), nRuns[iStr], calo.Data()),nPlot,0,nPlot);
				OnlyEditTH1(nCellsRun[iStr], 20, 1, kBlack, kBlack);

				for (Int_t h=1; h<=nPlot; h++){
					Int_t nBadCells = 0;
					do{
						if((vec[iStr].at(posInVec)).BeginsWith("Run-")){
							TString tempStr = (vec[iStr].at(posInVec)).Remove(0,4);
							nCellsRun[iStr]->GetXaxis()->SetBinLabel(h,Form("%s",tempStr.Data()));
						}else nBadCells++;
					}while(++itVec!=vec[iStr].end() && !((vec[iStr].at(++posInVec)).BeginsWith("Run-")));
					nCellsRun[iStr]->SetBinContent(h,nBadCells);
				}
				nCellsRun[iStr]->SetFillStyle(3004);
				nCellsRun[iStr]->SetFillColor(1);
				nCellsRun[iStr]->Draw();
				if(doRunsFromDataLHC12 && iStr>=nData) SaveCanvas(cvsRun, Form("%s/%s-%s/%s_%i.%s", outputDir.Data(), plotDataSets[iStr].Data(),plotDataSets[0].Data(), "BadCells_Runwise",nPart++,suffix.Data()));
				else SaveCanvas(cvsRun, Form("%s/%s/%s_%i.%s", outputDir.Data(), plotDataSets[iStr].Data(), "BadCells_Runwise",nPart++,suffix.Data()));
				delete nCellsRun[iStr];
			}while(plotting < nRuns[iStr]);
			fLogRunwiseBadCells[iStr].close();
		}
		delete cvsRun;
	}

	cout << "Done with ClusterQARunwise_pPb" << endl;
	cout << "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;

	return;

}//end
