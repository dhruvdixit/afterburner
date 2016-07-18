#include "ClusterQA.h"

void ClusterQA_MergeGoodRuns(){

	TString folder = "/home/daniel/data/work/photonconv/AnalysisSoftware";

	TString Tag = "20150624";
	TString MergeFile = "GammaConvCalo_120.root";
	TString OutputFile = "LHC12.root";

	const Int_t nSets = 10;
	const Int_t nData = 7;
	TString DataSets[nSets]={"LHC12a",
							 "LHC12b",
							 "LHC12c",
							// "LHC12d",
							 "LHC12f",
							 "LHC12g",
							 "LHC12h",
							 "LHC12i",
							 "LHC14e2a",
							 "LHC14e2b",
							 "LHC14e2c"};

	std::vector<TString> vecRuns;
	TString fileRuns;
	TString fDataSet;
	TString mergeP = Form("%s/DataQA/%s/%s",folder.Data(), Tag.Data(), OutputFile.Data());
	gSystem->Exec(Form("rm %s",mergeP.Data()));
	TString mergePeriod = Form("hadd %s",mergeP.Data());

	for(Int_t iSet=0; iSet<nSets; iSet++)
	{
		vecRuns.clear();
		fDataSet = DataSets[iSet];
		fileRuns = Form("%s/runNumbers%s.txt", folder.Data(), fDataSet.Data());
//		fileRuns = Form("%s/runNumbers%s_EMCAL.txt", folder.Data(), fDataSet.Data());
//		if(iSet>=nData) fileRuns = Form("%s/runNumbers%s.txt", folder.Data(), fDataSet.Data());
		cout << "\n------------------------------------------------------" << endl;
		if(!readin(fileRuns, vecRuns)) cout << "\n\n\n**********************ERROR, no Run Numbers could be found!**********************\n\n\n" << endl;
		cout << "------------------------------------------------------" << endl;

		TString mergeR = Form("%s/DataQA/%s/%s",folder.Data(), Tag.Data(), fDataSet.Data());
		TString mergeR_MC[nSets-nData];
		for(Int_t i=0;i<(nSets-nData);i++){
			if(iSet<nData)mergeR_MC[i] = Form("%s/DataQA/%s/%s-%s",folder.Data(), Tag.Data(), DataSets[nData+i].Data(), fDataSet.Data());
		}

		gSystem->Exec(Form("rm %s.root",mergeR.Data()));
		for(Int_t i=0;i<(nSets-nData);i++){if(iSet<nData)gSystem->Exec(Form("rm %s.root",mergeR_MC[i].Data()));}

		TString mergeRuns = Form("hadd %s.root",mergeR.Data());
		TString mergeRuns_MC[nSets-nData];
		for(Int_t i=0;i<(nSets-nData);i++){if(iSet<nData)mergeRuns_MC[i] = Form("hadd %s.root",mergeR_MC[i].Data());}

		for(Int_t iRun=0; iRun<(Int_t)vecRuns.size(); iRun++){
			mergeRuns+=Form(" %s/DataQA/%s/%s/%s/%s", folder.Data(), Tag.Data(), fDataSet.Data(), (vecRuns.at(iRun)).Data(), MergeFile.Data());
			for(Int_t i=0;i<(nSets-nData);i++){if(iSet<nData)mergeRuns_MC[i]+=Form(" %s/DataQA/%s/%s/%s/%s", folder.Data(), Tag.Data(), DataSets[nData+i].Data(), (vecRuns.at(iRun)).Data(), MergeFile.Data());}
		}

		cout << "Merging " << vecRuns.size() << " runs from period" << fDataSet.Data() << "...";
		gSystem->Exec(mergeRuns.Data());
		for(Int_t i=0;i<(nSets-nData);i++){if(iSet<nData)gSystem->Exec(mergeRuns_MC[i].Data());}

		ChangeStrucToStd(Form("%s.root",mergeR.Data()),Form("%s-pass1_120.root",mergeR.Data()),"GammaConvCalo_120");
		for(Int_t i=0;i<(nSets-nData);i++){if(iSet<nData)ChangeStrucToStd(Form("%s.root",mergeR_MC[i].Data()),Form("%s-pass1_120.root",mergeR_MC[i].Data()),"GammaConvCalo_120");}
		cout << "done!" << endl;

		if(iSet<nData) mergePeriod+=Form(" %s/DataQA/%s/%s-pass1_120.root",folder.Data(), Tag.Data(), fDataSet.Data());
	}
	cout << "Merging " << nData << " periods...";
	gSystem->Exec(mergePeriod.Data());
	cout << "done!" << endl;
	return;
}

void ChangeStrucToStd(TString nameInputFile, TString namefileOutput, TString nameInputList){

   TFile *fileInput = NULL;
   fileInput = new TFile(nameInputFile.Data());
   cout << fileInput << endl;

   TList *listInput =(TList*)fileInput->Get(nameInputList.Data());
   if (listInput == NULL){
	  return;
   }
   TFile *fileOutput = new TFile(namefileOutput,"RECREATE");
   TList *listOutput =(TList*)fileOutput->Get("GammaConvCalo");
   Bool_t kNewList = kFALSE;
   if (!listOutput){
	  kNewList = kTRUE;
	  listOutput = new TList();
	  listOutput->SetName("GammaConvCalo");
   }

   for(Int_t i = 0; i<listInput->GetSize(); i++){
	  TList *listToSave = (TList*)listInput->At(i);
	  TString dirname = listToSave->GetName();
	  cout<<dirname<<endl;
	  if(listToSave){
		 cout<<"found"<<endl;
		 listOutput->Add(listToSave);
	  }
   }

   listOutput->Write("",TObject::kSingleKey);
   fileOutput->Close();
}

void MakeCLog(const char *inputRootFile = "GammaConvCalo.root", const char *InputName){

  TString filename = inputRootFile;
  TFile *file = new TFile(filename.Data());
  if (file->IsZombie()) return;

  fstream outputFile(InputName,ios::out);
  if(!outputFile.is_open()){
	cout<<"Problem opening file"<<endl;
	return;
  }

  //  Char_t filename_input1[200] = (Form("%s%s",path,input1));
  TKey *key;
  file->ls();

  cout<<file<<endl;
  //TIter nextkey(l.GetListOfKeys());
  TList *list = (TList*) file->Get("GammaConvCalo");

  for(Int_t i = 0; i<list->GetEntries(); i++){
	 TList *l2 = (TList*) list->At(i);
	 TString dirname = l2->GetName();
	 if(dirname.BeginsWith("Cut") == 1){
		TString CutNumber(dirname(11,dirname.Length()-11));
		outputFile << CutNumber.Data() <<endl;
		cout<<CutNumber<<endl;
	 }
  }
  outputFile.close();

}
