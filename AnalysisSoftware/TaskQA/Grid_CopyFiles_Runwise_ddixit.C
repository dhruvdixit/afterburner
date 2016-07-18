#include <iostream>
#include <vector>
#include <fstream>

#include <TFile.h>
#include <TGrid.h>
#include <TSystem.h>
#include <TString.h>
#include <TObject.h>

Bool_t readin(TString fileRuns, std::vector<TString> &vec);
Bool_t copyAlien2Local(TString loc, TString rem);

/*/////////////////////////////////////////////////////////////////////////////////////////////////
Works very similar to Grid_CopyFiles, with the differece being that the Grid_CopyFiles uses location of /alice/cern.ch/user/a/alitrain/PWGGA/GA_pp/ (could be pPb or PbPb), while Grid_CopyFiles uses the location /alice/data/year/LHC#letter/ etc
/////////////////////////////////////////////////////////////////////////////////////////////////*/

void Grid_CopyFiles_Runwise_ddixit(TString folder = "/home/dhruv/afterburner/AnalysisSoftware")
{
    cout<<"Connecting to Alien..."<<endl;
    TGrid::Connect("alien://");
    cout<<"==============================="<<endl;
    cout<<"Successfully connected to Alien"<<endl;
    cout<<"==============================="<<endl;

    const Int_t nFiles = 1;
    TString Tag = "20160307";
//    TString DataSetsFile[nFiles] = {"GammaCalo_201.root","GammaConvCalo_201.root"};
    TString DataSetsFile[nFiles] = {"GammaConvCalo_20.root"};

    const Int_t nSets = 10;
    TString DataSets[nSets]={"LHC13b_pass3",
			     "LHC13c_pass2",
			     "LHC13d_pass2",
			     "LHC13e_pass2",
			     "LHC13f_pass2",
			     "LHC13b2_efix_p1",
			     "LHC13b2_efix_p2",
			     "LHC13b2_efix_p3",
			     "LHC13b2_efix_p4",
			     "LHC13e7"};
    
    TString DataSetsFolder[nSets]= {"LHC13b_pass3",
			     "LHC13c_pass2",
			     "LHC13d_pass2",
			     "LHC13e_pass2",
			     "LHC13f_pass2",
			     "LHC13b2_efix_p1",
			     "LHC13b2_efix_p2",
			     "LHC13b2_efix_p3",
			     "LHC13b2_efix_p4",
			     "LHC13e7"};
    
    TString PrefixDataSets[nSets]={"/alice/data/2013/LHC13b/000",
                                   "/alice/data/2013/LHC13c/000",
                                   "/alice/data/2013/LHC13d/000",
                                   "/alice/data/2013/LHC13e/000",
                                   "/alice/data/2013/LHC13f/000",
				   "/alice/data/2013/LHC13b2_efix_p1/",
				   "/alice/data/2013/LHC13b2_efix_p2/",
				   "/alice/data/2013/LHC13b2_efix_p3/",
				   "/alice/data/2013/LHC13b2_efix_p4/",
				   "/alice/data/2013/LHC13e7/"};

    TString SuffixDataSets[nSets]={"/ESDs/pass3/PWGGA/GA_pPb/536_20160307-2213/",
                                   "/ESDs/pass2/PWGGA/GA_pPb/537_20160307-2214/",
                                   "/pass2/PWGGA/GA_pPb/538_20160307-2214/",
                                   "/pass2/PWGGA/GA_pPb/539_20160307-2215/",
                                   "/pass2/PWGGA/GA_pPb/540_20160307-2215/",
                                   "/PWGGA/GA_pPb_MC/721_20160307-2216/",
                                   "/PWGGA/GA_pPb_MC/722_20160307-2216/",
                                   "/PWGGA/GA_pPb_MC/723_20160307-2217/",
                                   "/PWGGA/GA_pPb_MC/724_20160307-2218/",
                                   "/PWGGA/GA_pPb_MC/725_20160307-2218/"};


    //pPb
//    const Int_t nSets = 6;
//    TString DataSets[nSets]={"LHC13b",
//                             "LHC13c",
//                             "LHC13b2_efix1",
//                             "LHC13b2_efix2",
//                             "LHC13b2_efix3",
//                             "LHC13b2_efix4"};
//    TString PrefixDataSets[nSets]={"/alice/data/2013/LHC13b/000",
//                                   "/alice/data/2013/LHC13c/000",
//                                   "/alice/sim/2013/LHC13b2_efix_p1/",
//                                   "/alice/sim/2013/LHC13b2_efix_p2/",
//                                   "/alice/sim/2013/LHC13b2_efix_p3/",
//                                   "/alice/sim/2013/LHC13b2_efix_p4/"};
//    TString SuffixDataSets[nSets]={"/ESDs/pass3/PWGGA/GA_pPb/289_20141208-1140/",
//                                   "/ESDs/pass2/PWGGA/GA_pPb/290_20141208-1144/",
//                                   "/PWGGA/GA_pPb_MC/399_20141208-1239/",
//                                   "/PWGGA/GA_pPb_MC/400_20141208-1237/",
//                                   "/PWGGA/GA_pPb_MC/401_20141208-1237/",
//                                   "/PWGGA/GA_pPb_MC/402_20141208-1238/"};



    std::vector<TString> vecRuns;
    std::vector<TString> vecErrors[nSets];
    TString fDataSet;
    TString fPathGrid;
    TString fPathLocal;
    TString fileRuns;

    Int_t nErr[nSets];

    for(Int_t i=0; i<nSets; i++)
    {
        vecRuns.clear();
	fDataSet = DataSets[i];
        if(fDataSet.CompareTo("")==0) 
	  continue;
	fileRuns = Form("%s/runNumbers%s.txt", folder.Data(), fDataSet.Data());
        cout << "\n------------------------------------------------------" << endl;
	if(!readin(fileRuns, vecRuns)) 
	  cout << "\n\n\n**********************ERROR, no Run Numbers could be found!**********************\n\n\n" << endl;
        cout << "------------------------------------------------------" << endl;

	Bool_t doNormalFolder = kFALSE;
	if(DataSetsFolder[i].IsNull()) 
	  doNormalFolder = kTRUE;
	
        nErr[i]=0;
        vecErrors[i].clear();
        for(Int_t j=0; j<(Int_t)vecRuns.size(); j++)
        {
	  // exclude files from unavailable SEs
	  //if(fDataSet.CompareTo("LHC12g")==0 && vecRuns.at(j).CompareTo("188443")==0) continue;
	  for(Int_t k=0; k<nFiles; k++)
            {
	      fPathGrid = Form("%s%s%s%s", PrefixDataSets[i].Data(), vecRuns.at(j).Data(), SuffixDataSets[i].Data(), DataSetsFile[k].Data());
	      if(doNormalFolder) 
		fPathLocal = Form("%s/DataQA/%s/%s/%s", folder.Data(), Tag.Data(), fDataSet.Data(), vecRuns.at(j).Data());
	      else 
		fPathLocal = Form("%s/DataQA/%s/%s/%s", folder.Data(), Tag.Data(), DataSetsFolder[i].Data(), vecRuns.at(j).Data());
	      gSystem->Exec(Form("mkdir -p %s",fPathLocal.Data()));
	      
	      fPathLocal+="/"; fPathLocal+=DataSetsFile[k];
	      
	      cout << endl;
	      cout << "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;
	      cout << "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;
	      cout << "Copying from (grid): " << fPathGrid.Data() << endl;
	      cout << "Copying to (local): " << fPathLocal.Data() << endl;
	      cout << "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;
	      cout << "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;
	      
	      TFile fileCheck(fPathLocal.Data());
	      if(!fileCheck.IsZombie()) 
		{
		  cout << "\n\t\t>>>>>>>>>>>>>>>>>>Info: ROOT-File |" << fPathLocal.Data() << "| does already exist! Continue...<<<<<<<<<<<<<<\n" << endl; 
		  continue;
		}
	      
	      if(copyAlien2Local(fPathGrid,fPathLocal)) 
		continue;
	      else
		{
		  cout << "\n\n\t**********************************************************************************************" << endl;
                  cout << "\t**********************************************************************************************" << endl;
                  cout << "\t*******************Err: copyAlien2Local(), check runlist in photonconv rep!*******************" << endl;
                  cout << "\t**********************************************************************************************" << endl;
                  cout << "\t**********************************************************************************************\n" << endl;
                  nErr[i]++;
                  vecErrors[i].push_back(vecRuns.at(j));
                }
	    }
	}
	
	if(!doNormalFolder) 
	  gSystem->Exec(Form("ln -s %s %s",Form("%s/DataQA/%s/%s", folder.Data(), Tag.Data(), DataSetsFolder[i].Data()),Form("%s/DataQA/%s/%s", folder.Data(), Tag.Data(), fDataSet.Data())));
    }

    for(Int_t i=0; i<nSets; i++)
      {
	cout << "DataSet: " << DataSets[i].Data() << ", number of errors: " << nErr[i] << endl;
	cout << "\t\tRuns: ";
	for(Int_t iRuns=0; iRuns < (Int_t)vecErrors[i].size(); iRuns++) 
	  cout << vecErrors[i].at(iRuns).Data() << ", ";
	cout << endl;
      }
    
    return;
}

/*////////////////////////////////////////////////////////////////////////////////
Reads in the contents of the file whose name is contained in filesRuns, and the contents are stored in vec, the input vector. The first line of the file is the first entry and it is stored in at vector at index 0. Returns false if vector is not empty.
*////////////////////////////////////////////////////////////////////////////////
Bool_t readin(TString fileRuns, std::vector<TString> &vec){
    cout << Form("Reading from %s...", fileRuns.Data()) << endl;
    fstream file;
    TString fVar;
    Int_t totalN=0;
    file.open(fileRuns.Data(), ios::in);
    if(file.good())
    {
        file.seekg(0L, ios::beg);
        cout << "Processing Runs: \"";
        while(!file.eof())
        {
            file >> fVar;
            if(fVar.Sizeof()>1)
            {
                cout << fVar.Data() << ", ";
                vec.push_back(fVar);
                totalN++;
            }
        }
        cout << "\"" << endl;
    }
    file.close();
    cout << "...done!\n\nIn total " << totalN << " Runs will be processed!" << endl;
    if(totalN > 0) return kTRUE;
    else return kFALSE;
}

/*/////////////////////////////////////////////////////////////////////////////////////////
Copies a file from the loc to rem.
/////////////////////////////////////////////////////////////////////////////////////////*/
Bool_t copyAlien2Local(TString loc, TString rem){
   TString sl(Form("alien://%s", loc.Data()));
   TString sr(Form("file://%s", rem.Data()));
   Bool_t ret = TFile::Cp(sl,sr);
   if (!ret) cout << Form("ERROR: Failed to copy %s to %s", sl.Data(), sr.Data()) << endl;
   return ret;
}
