void readin(TString fileRuns, std::vector<TString> &vec);
Bool_t copyAlien2Local(TString where, TString loc, TString rem);

void ClusterQARunwise_Copy(TString folder = "/home/daniel/data/work/photonconv/AnalysisSoftware")
{
    cout<<"Connecting to Alien..."<<endl;
    TGrid::Connect("alien://");
    cout<<"==============================="<<endl;
    cout<<"Successfully connected to Alien"<<endl;
    cout<<"==============================="<<endl;

	Bool_t switchAll = kFALSE;

	//pp LHC10 7 TeV
//	const Int_t nFiles = 2;
//	TString Tag = "20150922";
//	TString DataSetsFile[nFiles] = {"GammaCalo_201.root","GammaConvCalo_201.root"};

//	const Int_t nSets = 10;
//	//switchAll = kTRUE;
//	TString DataSets[nSets]={"LHC10b_pass4",
//							 "LHC10c_pass4",
//							 "LHC10d_pass4",
//							 "LHC10e_pass4",
//							 "LHC10f_pass4",
//							 "LHC14j4b",
//							 "LHC14j4c",
//							 "LHC14j4d",
//							 "LHC14j4e",
//							 "LHC14j4f"};
//	TString PrefixDataSets[nSets]={"/alice/data/2010/LHC10b/000",
//								   "/alice/data/2010/LHC10c/000",
//								   "/alice/data/2010/LHC10d/000",
//								   "/alice/data/2010/LHC10e/000",
//								   "/alice/data/2010/LHC10f/000",
//								   "/alice/sim/2014/LHC14j4b/",
//								   "/alice/sim/2014/LHC14j4c/",
//								   "/alice/sim/2014/LHC14j4d/",
//								   "/alice/sim/2014/LHC14j4e/",
//								   "/alice/sim/2014/LHC14j4f/"};
//	TString SuffixDataSets[nSets]={"/pass4/PWGGA/GA_pp/997_20150922-0953/",
//								   "/pass4/PWGGA/GA_pp/998_20150922-0953/",
//								   "/pass4/PWGGA/GA_pp/999_20150922-0954/",
//								   "/pass4/PWGGA/GA_pp/1000_20150922-0954/",
//								   "/pass4/PWGGA/GA_pp/1001_20150922-0954/",
//								   "/PWGGA/GA_pp_MC/1080_20150922-0945/",
//								   "/PWGGA/GA_pp_MC/1081_20150922-0946/",
//								   "/PWGGA/GA_pp_MC/1082_20150922-0946/",
//								   "/PWGGA/GA_pp_MC/1093_20150923-1117/",
//								   "/PWGGA/GA_pp_MC/1084_20150922-0947/"
//								  };

	//pp LHC10 7 TeV PhotonQA
	const Int_t nFiles = 1;
	TString Tag = "20150922";
	TString DataSetsFile[nFiles] = {"AnalysisResults.root"};

	const Int_t nSets = 10;
	//switchAll = kTRUE;
	TString DataSets[nSets]={"LHC10b_pass4",
							 "LHC10c_pass4",
							 "LHC10d_pass4",
							 "LHC10e_pass4",
							 "LHC10f_pass4",
							 "LHC14j4b",
							 "LHC14j4c",
							 "LHC14j4d",
							 "LHC14j4e",
							 "LHC14j4f"};
	TString PrefixDataSets[nSets]={"/alice/data/2010/LHC10b/000",
								   "/alice/data/2010/LHC10c/000",
								   "/alice/data/2010/LHC10d/000",
								   "/alice/data/2010/LHC10e/000",
								   "/alice/data/2010/LHC10f/000",
								   "/alice/sim/2014/LHC14j4b/",
								   "/alice/sim/2014/LHC14j4c/",
								   "/alice/sim/2014/LHC14j4d/",
								   "/alice/sim/2014/LHC14j4e/",
								   "/alice/sim/2014/LHC14j4f/"};
	TString SuffixDataSets[nSets]={"/pass4/PWGGA/GA_pp/1002_20150922-1900/",
								   "/pass4/PWGGA/GA_pp/1003_20150922-1825/",
								   "/pass4/PWGGA/GA_pp/1005_20150922-1901/",
								   "/pass4/PWGGA/GA_pp/1007_20150922-1906/",
								   "/pass4/PWGGA/GA_pp/1006_20150922-1902/",
								   "/PWGGA/GA_pp_MC/1096_20150925-0935/",
								   "/PWGGA/GA_pp_MC/1087_20150922-1859/",
								   "/PWGGA/GA_pp_MC/1089_20150922-1856/",
								   "/PWGGA/GA_pp_MC/1090_20150922-1857/",
								   "/PWGGA/GA_pp_MC/1095_20150925-0935/"
								  };

	//pp LHC12
//			const Int_t nFiles = 1;
//			TString Tag = "20150728";
//			TString DataSetsFile[nFiles] = {"GammaConvCalo_120.root"};

//			const Int_t nSets = 11;
//			//switchAll = kTRUE;
//			TString DataSets[nSets]={"LHC12a",
//									 "LHC12b",
//									 "LHC12c",
//									 "LHC12d",
//									 "LHC12f",
//									 "LHC12g",
//									 "LHC12h",
//									 "LHC12i",
//									 "LHC14e2a",
//									 "LHC14e2b",
//									 "LHC14e2c"};
//			TString PrefixDataSets[nSets]={"/alice/data/2012/LHC12a/000",
//										   "/alice/data/2012/LHC12b/000",
//										   "/alice/data/2012/LHC12c/000",
//										   "/alice/data/2012/LHC12d/000",
//										   "/alice/data/2012/LHC12f/000",
//										   "/alice/data/2012/LHC12g/000",
//										   "/alice/data/2012/LHC12h/000",
//										   "/alice/data/2012/LHC12i/000",
//										   "/alice/sim/2014/LHC14e2a/",
//										   "/alice/sim/2014/LHC14e2b/",
//										   "/alice/sim/2014/LHC14e2c/"};
//			TString SuffixDataSets[nSets]={"/pass1/PWGGA/GA_pp/813_20150728-0757/",
//										   "/pass1/PWGGA/GA_pp/814_20150728-0758/",
//										   "/pass1/PWGGA/GA_pp/815_20150728-0758/",
//										   "/pass1/PWGGA/GA_pp/816_20150728-0759/",
//										   "/pass1/PWGGA/GA_pp/817_20150728-0800/",
//										   "/pass1/PWGGA/GA_pp/818_20150728-0801/",
//										   "/pass1/PWGGA/GA_pp/819_20150728-0802/",
//										   "/pass1/PWGGA/GA_pp/820_20150728-0802/",
//										   "/PWGGA/GA_pp_MC/798_20150728-0851/",
//										   "/PWGGA/GA_pp_MC/799_20150728-0852/",
//										   "/PWGGA/GA_pp_MC/800_20150728-0854/"
//										  };

	//pp LHC12 MC
//			const Int_t nFiles = 2;
//			TString Tag = "20150823";
//			TString DataSetsFile[nFiles] = {"GammaConvCalo_110.root","GammaCalo_110.root"};

//			const Int_t nSets = 2;
//			//switchAll = kTRUE;
//			TString DataSets[nSets]={"LHC14e2a",
//									 "LHC14e2c"};
//			TString PrefixDataSets[nSets]={"/alice/sim/2014/LHC14e2a/",
//										   "/alice/sim/2014/LHC14e2c/"};
//			TString SuffixDataSets[nSets]={"/PWGGA/GA_pp_MC/916_20150824-1151/",
//										   "/PWGGA/GA_pp_MC/918_20150824-1152/"
//										  };

			// pp LHC12 pass2
//				const Int_t nFiles = 2;
//				TString Tag = "20150731";
//				TString DataSetsFile[nFiles] = {"GammaConvCalo_101.root","GammaCalo_101.root"};

//				const Int_t nSets = 1;
//				//switchAll = kTRUE;
//				TString DataSets[nSets]={
//										 "LHC14e2a"};
//				TString PrefixDataSets[nSets]={
//											   "/alice/sim/2014/LHC14e2a/"};
//				TString SuffixDataSets[nSets]={
//											   "/PWGGA/GA_pp_MC/822_20150801-0541/"
//											  };

	//pp LHC12 pass2
//			const Int_t nFiles = 1;
//			TString Tag = "20150728-p2";
//			TString DataSetsFile[nFiles] = {"GammaConvCalo_120.root"};

//			const Int_t nSets = 8;
//			switchAll = kTRUE;
//			TString DataSets[nSets]={"LHC12a",
//									 "LHC12b",
//									 "LHC12c",
//									 "LHC12d",
//									 "LHC12f",
//									 "LHC12g",
//									 "LHC12h",
//									 "LHC12i"};
//			TString PrefixDataSets[nSets]={"/alice/data/2012/LHC12a/000",
//										   "/alice/data/2012/LHC12b/000",
//										   "/alice/data/2012/LHC12c/000",
//										   "/alice/data/2012/LHC12d/000",
//										   "/alice/data/2012/LHC12f/000",
//										   "/alice/data/2012/LHC12g/000",
//										   "/alice/data/2012/LHC12h/000",
//										   "/alice/data/2012/LHC12i/000"};
//			TString SuffixDataSets[nSets]={"/pass2/PWGGA/GA_pp/821_20150728-0843/",
//										   "/pass2/PWGGA/GA_pp/822_20150728-0845/",
//										   "/pass2/PWGGA/GA_pp/823_20150728-0846/",
//										   "/pass2/PWGGA/GA_pp/824_20150728-0846/",
//										   "/pass2/PWGGA/GA_pp/825_20150728-0847/",
//										   "/pass2/PWGGA/GA_pp/826_20150728-0849/",
//										   "/pass2/PWGGA/GA_pp/827_20150728-0850/",
//										   "/pass2/PWGGA/GA_pp/828_20150728-0850/"
//										  };

//			const Int_t nFiles = 1;
//			TString Tag = "20150625";
//			TString DataSetsFile[nFiles] = {"GammaConvCalo_122.root"}; //120 extQA, 121 kEMC7, 122 kEGA, 123 EJE
//			const Int_t nSets = 9;
//			TString DataSets[nSets]={"LHC12a-kEMCEGA",
//									 "LHC12b-kEMCEGA",
//									 "LHC12c-kEMCEGA",
//									 "LHC12d-kEMCEGA",
//									 "LHC12e-kEMCEGA",
//									 "LHC12f-kEMCEGA",
//									 "LHC12g-kEMCEGA",
//									 "LHC12h-kEMCEGA",
//									 "LHC12i-kEMCEGA"};
//			TString PrefixDataSets[nSets]={"/alice/data/2012/LHC12a/000",
//										   "/alice/data/2012/LHC12b/000",
//										   "/alice/data/2012/LHC12c/000",
//										   "/alice/data/2012/LHC12d/000",
//										   "/alice/data/2012/LHC12e/000",
//										   "/alice/data/2012/LHC12f/000",
//										   "/alice/data/2012/LHC12g/000",
//										   "/alice/data/2012/LHC12h/000",
//										   "/alice/data/2012/LHC12i/000"};
//			TString SuffixDataSets[nSets]={"/pass1/PWGGA/GA_pp/708_20150625-0919/",
//										   "/pass1/PWGGA/GA_pp/709_20150625-0920/",
//										   "/pass1/PWGGA/GA_pp/710_20150625-0922/",
//										   "/pass1/PWGGA/GA_pp/711_20150625-0922/",
//										   "/pass1/PWGGA/GA_pp/712_20150625-0923/",
//										   "/pass1/PWGGA/GA_pp/713_20150625-0924/",
//										   "/pass1/PWGGA/GA_pp/714_20150625-0925/",
//										   "/pass1/PWGGA/GA_pp/715_20150625-0925/",
//										   "/pass1/PWGGA/GA_pp/716_20150625-0927/"
//										  };

//			const Int_t nSets = 8;
//			TString DataSets[nSets]={"LHC12a",
//									 "LHC12b",
//									 "LHC12c",
//									 "LHC12d",
//									 "LHC12f",
//									 "LHC12g",
//									 "LHC12h",
//									 "LHC12i"};
//			TString PrefixDataSets[nSets]={"/alice/data/2012/LHC12a/000",
//										   "/alice/data/2012/LHC12b/000",
//										   "/alice/data/2012/LHC12c/000",
//										   "/alice/data/2012/LHC12d/000",
//										   "/alice/data/2012/LHC12f/000",
//										   "/alice/data/2012/LHC12g/000",
//										   "/alice/data/2012/LHC12h/000",
//										   "/alice/data/2012/LHC12i/000"};
//			TString SuffixDataSets[nSets]={"/pass1/PWGGA/GA_pp/691_20150620-0025/",
//										   "/pass1/PWGGA/GA_pp/692_20150620-0025/",
//										   "/pass1/PWGGA/GA_pp/693_20150620-0026/",
//										   "/pass1/PWGGA/GA_pp/694_20150620-0026/",
//										   "/pass1/PWGGA/GA_pp/695_20150620-0029/",
//										   "/pass1/PWGGA/GA_pp/696_20150620-0029/",
//										   "/pass1/PWGGA/GA_pp/697_20150620-0029/",
//										   "/pass1/PWGGA/GA_pp/698_20150620-0030/"
//										  };

    //pp LHC11a
//			const Int_t nFiles = 1;
//			TString Tag = "20150825";
//			TString DataSetsFile[nFiles] = {"GammaConvCalo_1.root"};

//			const Int_t nSets = 4;
//			TString DataSets[nSets]={"LHC11a_p4_wSDD",
//									 "LHC12f1a",
//									 "LHC12f1b",
//									 "LHC12i3"
//									 };
//			TString PrefixDataSets[nSets]={"/alice/data/2011/LHC11a/000",
//										   "/alice/sim/2012/LHC12f1a/",
//										   "/alice/sim/2012/LHC12f1b/",
//										   "/alice/sim/2012/LHC12i3/"
//										  };
//			TString SuffixDataSets[nSets]={"/ESDs/pass4_with_SDD/PWGGA/GA_pp/912_20150826-2136/",
//										   "/PWGGA/GA_pp_MC/923_20150825-2153/",
//										   "/PWGGA/GA_pp_MC/924_20150825-2153/",
//										   "/PWGGA/GA_pp_MC/925_20150825-2154/"
//										  };

	//pp LHC11a kEMC triggers
//			const Int_t nSets = 1;
//			TString DataSets[nSets]={"LHC11a_p4_wSDD"};
//			TString PrefixDataSets[nSets]={"/alice/data/2011/LHC11a/000"};
//			TString SuffixDataSets[nSets]={"/ESDs/pass4_with_SDD/PWGGA/GA_pp/468_20150403-1639/"};

//	//pp LHC13g
//	const Int_t nFiles = 2;
//	TString Tag = "20150825";
//	TString DataSetsFile[nFiles] = {"GammaConvCalo_95.root","GammaConvCalo_96.root"};

//	const Int_t nSets = 1;
//	TString DataSets[nSets]={"LHC13g"};
//	TString PrefixDataSets[nSets]={"/alice/data/2013/LHC13g/000"};
//	TString SuffixDataSets[nSets]={"/pass1/PWGGA/GA_pp/910_20150826-2136/"};

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

//    TString SuffixDataSets[nSets]={"/ESDs/pass3/PWGGA/GA_pPb/284_20141201-1208/",
//                                   "/ESDs/pass2/PWGGA/GA_pPb/285_20141201-1208/",
//                                   "/PWGGA/GA_pPb_MC/394_20141201-1401/",
//                                   "/PWGGA/GA_pPb_MC/395_20141201-1402/",
//                                   "/PWGGA/GA_pPb_MC/396_20141201-1402/",
//                                   "/PWGGA/GA_pPb_MC/397_20141201-1421/"};

    //PbPb
//        const Int_t nSets = 2;
//        TString DataSets[nSets]={"LHC11h",
//                                 "LHC14a1a"};
//        TString PrefixDataSets[nSets]={"/alice/data/2011/LHC11h_2/000",
//                                       "/alice/sim/2014/LHC14a1a/"};
//        TString SuffixDataSets[nSets]={"/ESDs/pass2/PWGGA/GA_PbPb/147_20141117-1517/",
//                                       "/PWGGA/GA_PbPb_MC/182_20141117-1323/"
//                                      };

    std::vector<TString> vecRuns;
    TString fDataSet;
    TString fPathGrid;
    TString fPathLocal;
    TString fileRuns;

    for(Int_t i=0; i<nSets; i++)
    {
        vecRuns.clear();
        fDataSet = DataSets[i];
        if(fDataSet.CompareTo("")==0) continue;
		if(switchAll) fDataSet+="-all";
		fileRuns = Form("%s/runNumbers%s.txt", folder.Data(), fDataSet.Data());
        cout << "\n------------------------------------------------------" << endl;
		if(!readin(fileRuns, vecRuns)) cout << "\n\n\n**********************ERROR, no Run Numbers could be found!**********************\n\n\n" << endl;
        cout << "------------------------------------------------------" << endl;

        for(Int_t j=0; j<vecRuns.size(); j++)
        {
			// exclude files from unavailable SEs
			//if(fDataSet.CompareTo("LHC12f")==0 && vecRuns.at(j).CompareTo("187148")==0) continue;
			for(Int_t k=0; k<nFiles; k++)
			{
				fPathGrid = Form("%s%s%s%s", (PrefixDataSets[i]).Data(), (vecRuns.at(j)).Data(), (SuffixDataSets[i]).Data(), (DataSetsFile[k]).Data());
				fPathLocal = Form("%s/DataQA/%s/%s/%s", folder.Data(), Tag.Data(), (DataSets[i]).Data(), (vecRuns.at(j)).Data());
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
				if(!fileCheck.IsZombie()) {cout << "\n\t\t>>>>>>>>>>>>>>>>>>Info: ROOT-File |" << fPathLocal.Data() << "| does already exist! Continue...<<<<<<<<<<<<<<\n" << endl; continue;}

				if(copyAlien2Local("",fPathGrid,fPathLocal)) continue;
				else cout << "\n\n\t*******************Err: copyAlien2Local(), check runlist in photonconv rep!*******************\n" << endl;
			}
        }

    }
    return;
}

Bool_t readin(TString fileRuns, std::vector<TString> &vec)
{
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

Bool_t copyAlien2Local(TString where, TString loc, TString rem)
{
   TString sl(Form("alien://%s", loc.Data()));
   TString sr(Form("file://%s", rem.Data()));
   Bool_t ret = TFile::Cp(sl,sr);
   if (!ret) {
      Warning(where.Data(), "Failed to copy %s to %s", sl.Data(), sr.Data());
   }
   return ret;
}
