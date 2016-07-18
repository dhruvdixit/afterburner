	TF1 *fitPi0Exp7TeV = 				(TF1*)directoryPi07TeVFits->Get("fitPtExpPi0SysErr");
	TF1 *fitPi0Powerlaw7TeV = 				(TF1*)directoryPi07TeVFits->Get("fitPtModPowerlawPi0SysErr");
	TF1 *fitEtaPowerlaw7TeV = 				        (TF1*)directoryEta7TeVFits->Get("fitPtModPowerlawEtaSysErr");
	TF1 *fitPi0Exp2760GeV = 				(TF1*)directoryPi02760GeVFits->Get("fitPtExpPi0SysErr");
	TF1 *fitPi0Powerlaw2760GeV = 				(TF1*)directoryPi02760GeVFits->Get("fitPtModPowerlawPi0SysErr");
	TF1 *fitEtaPowerlaw2760GeV = 				        (TF1*)directoryEta2760GeVFits->Get("fitPtModPowerlawEtaSysErr");
	TF1 *fitPi0Exp900GeV = 				(TF1*)directoryPi0900GeVFits->Get("fitPtExpPi0SysErr");
	TF1 *fitPi0Powerlaw900GeV = 				(TF1*)directoryPi0900GeVFits->Get("fitPtModPowerlawPi0SysErr");



	//***************** Read data for charged pions -- all corrected to N Inelastic !!!!! ******************************
	
	// low pt - 7 TeV
	fileChargedPions7TeV = 		new TFile(fileNameChargedPions7TeV);
	listChargedPions7TeV = 		(TList*)fileChargedPions7TeV->Get("output"); 
	histChargedPions7TeV  = 	(TH1D*)listChargedPions7TeV->FindObject("PionsPos_MB_combine_sum");
	CorrectHistoToBinCenter(histChargedPions7TeV);
	histChargedPions7TeV->Scale(1./TMath::Pi()/2.);
	DrawGammaSetMarker(histChargedPions7TeV, markerStyleEMCAL,markerSizeInvYield, colorEMCAL, colorEMCAL);

	fitChargedPions7TeV = FitObject("l","fitChargedPions7TeV","Pi0",histChargedPions7TeV,0.15,1.5);
	fitChargedPions7TeV->SetLineColor(colorEMCAL);

	cout << "loaded 7TeV low pt charged pions" << endl;

	// high pt - 7TeV
	fileChargedHadrons7TeV = new TFile(fileNameChargedHadrons7TeV);
	histChargedPions7TeVHighPtWideRange = 	(TH1D*)fileChargedHadrons7TeV->Get("dNdPt_stat");
	histChargedHadrons7TeVWideRange = 	(TH1D*)fileChargedHadrons7TeV->Get("dNdPt_stat");

	fileFractionPions = new TFile(fileNameFractionPions);
	histFractionPions = 	(TH1D*)fileFractionPions->Get("hPionFraction_PP");

	histChargedPions7TeVHighPt=ConvertChargedHadronHisto(histChargedPions7TeVHighPtWideRange,histFractionPions);
	DrawGammaSetMarker(histChargedPions7TeVHighPt, 29,markerSizeInvYield, 2, 2);

	fitChargedPions7TeVHighPt = FitObject("l","fitChargedPions7TeV","Pi0",histChargedPions7TeV,3.,20.);
	fitChargedPions7TeVHighPt->SetLineColor(2);

	fileChargedHadrons2760GeV = new TFile(fileNameChargedHadrons2760GeV);
	histChargedHadrons2760GeVWideRange = 	(TH1D*)fileChargedHadrons2760GeV->Get("dNdPt_stat");

	fileChargedPions2760GeV = 		new TFile(fileNameChargedPions2760GeV);
	histChargedPions2760GeV  = 	(TH1D*)fileChargedPions2760GeV->Get("hPionSpectrumSyst_PP");
	DrawGammaSetMarker(histChargedPions2760GeV, markerStyleEMCAL,markerSizeInvYield, colorEMCAL, colorEMCAL);

	fitChargedPions2760GeV = FitObject("l","fitChargedPions2760GeV","Pi0",histChargedPions2760GeV,3.,16.);
	fitChargedPions2760GeV->SetLineColor(colorEMCAL);

	cout << "loaded 2760GeV  charged high pt pions" << endl;

	fileChargedHadrons900GeV = new TFile(fileNameChargedHadrons900GeV);
	histChargedHadrons900GeVWideRange = 	(TH1D*)fileChargedHadrons900GeV->Get("dNdPt_stat");

	fileChargedPions900GeV = 	new TFile(fileNameChargedPions900GeV);
	graphChargedNegPions900GeV  = 	(TGraphAsymmErrors*)fileChargedPions900GeV->Get("PiMinus_900");
	graphChargedPosPions900GeV  = 	(TGraphAsymmErrors*)fileChargedPions900GeV->Get("PiPlus_900");

	graphChargedPions900GeV =  Add2TGraphAsymmErrorsSameBinning(graphChargedNegPions900GeV,graphChargedPosPions900GeV);
	CorrectTGraphAsymmErrorsToBinCenter(graphChargedPions900GeV);
	ScaleGraph(graphChargedPions900GeV,1./TMath::Pi()/2.);
	DrawGammaSetMarkerTGraphAsym(graphChargedPions900GeV, markerStyleConv,markerSizeInvYield, colorEMCAL, colorEMCAL);

	fitChargedPions900GeV = FitObject("l","fitChargedPions900GeV","Pi0",graphChargedPions900GeV,0.25,2.5);
	fitChargedPions900GeV->SetLineColor(colorEMCAL);

	cout << "loaded 900GeV charged pions" << endl;
	//************************** End data for charged pions  **************************************************

	
	
		//**************************************************************************************************
	//*********************** Include Charged spectra, PHOS, PHOS+conv *********************************
	//**************************************************************************************************
	
	TCanvas* canvasComparison = new TCanvas("canvasComparison","",1350,1500);  // gives the page size
	DrawGammaCanvasSettings( canvasComparison, 0.13, 0.02, 0.02, 0.09);
	
	TPad* padComparison = new TPad("padComparison", "", 0., 0.25, 1., 1.,-1, -1, -2);
	DrawGammaPadSettings( padComparison, 0.12, 0.02, 0.02, 0.);
	padComparison->Draw();
	
	TPad* padComparisonRatio = new TPad("padComparisonRatio", "", 0., 0., 1., 0.25,-1, -1, -2);
	DrawGammaPadSettings( padComparisonRatio, 0.12, 0.02, 0., 0.2);
	padComparisonRatio->Draw();
	
	padComparison->cd();
	padComparison->SetLogy();		
	
	TH2F * histo2DCompareCharged = new TH2F("histo2DCompareCharged","histo2DCompareCharged",10,0.,maxPtPi0,1000.,(histoPi0Phos7TeV->GetMinimum())/1000.,100);
	//histo2DCompareCharged->SetXTitle("p_{t} (GeV/c)");
	histo2DCompareCharged->SetYTitle("#frac{1}{2#pi N_{ev.}} #frac{d^{2}N}{p_{t}dp_{t}dy} (c/GeV)^{2}");
	histo2DCompareCharged->SetTitle("");
	histo2DCompareCharged->GetYaxis()->SetDecimals();
	histo2DCompareCharged->GetYaxis()->SetLabelSize(0.025);
	histo2DCompareCharged->GetYaxis()->SetTitleOffset(1.1);
	histo2DCompareCharged->GetXaxis()->SetNdivisions(515,kTRUE);
	histo2DCompareCharged->DrawCopy();  
	
	//************************** extracting charged particle spectra **********************************
	
	cout << "charged beginn" << endl;
	fileCharged.open(fileNameChargedSpectra7TeV,ios_base::in);
	cout << fileNameChargedSpectra7TeV << endl;
	
	Int_t nLinesCharged = 0;		
	
	while(!fileCharged.eof()){
		nLinesCharged++;
		fileCharged >> ptCharged[nLinesCharged] >> chargedValue[nLinesCharged] >> chargedSystError[nLinesCharged] >> chargedStatError[nLinesCharged];	
		chargedValue[nLinesCharged] = chargedValue[nLinesCharged]/2.;
		chargedSystError[nLinesCharged] = chargedSystError[nLinesCharged]/2.;
		chargedStatError[nLinesCharged] = chargedStatError[nLinesCharged]/2.;
		chargedErrorY[nLinesCharged] = TMath::Sqrt(TMath::Power(chargedStatError[nLinesCharged],2)+ 						
		TMath::Power(chargedStatError[nLinesCharged],2));
		chargedErrorX[nLinesCharged]=0;
	}
	fileCharged.close();
	
	graphFitChargedSpect = new TGraphAsymmErrors(nLinesCharged,ptCharged,chargedValue,chargedErrorX,chargedErrorX,chargedErrorY,chargedErrorY);
	graphChargedSpectrum = new TGraphAsymmErrors(nLinesCharged,ptCharged,chargedValue,chargedErrorX,chargedErrorX,chargedErrorY,chargedErrorY);
	graphChargedSpectrumWideRange = new TGraphAsymmErrors(histChargedHadrons7TeVWideRange); 
	graphFitChargedSpectrumWideRange = new TGraphAsymmErrors(histChargedHadrons7TeVWideRange); 
	ScaleGraph(graphChargedSpectrumWideRange,0.5);
	ScaleGraph(graphFitChargedSpectrumWideRange,0.5);
	
	
	cout << "charged particle spectra read in" << endl;
	
	//----------------------- fitting Charged Particle ------------------------------
	//Double_t chargedParticleParam[3] = {1.,0.37,7.5};
	fitCharged = FitObject("l","fitCharged","Pi0",graphFitChargedSpectrumWideRange,0.2,maxPtPi0);
	
	DrawGammaSetMarkerTGraph(graphChargedSpectrum, markerStyleConv, markerSizeInvYield , colorCharged, colorCharged);
	//graphChargedSpectrum->Draw("pe");
	DrawGammaSetMarkerTGraph(graphChargedSpectrumWideRange, markerStyleConv, markerSizeInvYield , colorCharged, colorCharged);
	graphChargedSpectrumWideRange->Draw("same,pe"); // kk

	DrawGammaSetMarkerTF1( fitCharged, 8, 1, colorCharged);
	fitCharged->SetRange(0.,maxPtPi0);
	fitCharged->Draw("same");
	cout << "fitted charged particle" <<endl;
	
	
	DrawGammaSetMarker(histoPi0ToChargedPhojet7TeV, markerStyleConvMC, markerSizeInvYield-0.3, kCyan-6, kCyan-6);		
	DrawGammaSetMarker(histoPi0ToChargedPythia7TeV, markerStyleConvMC, markerSizeInvYield-0.3, kCyan+3, kCyan+3);		
	
	cout << "MC expectations" << endl;
	//-------------------------- Drawing Spectrum
	DrawGammaSetMarker(histoPi0CorrYieldBinShifted, markerStyleConv,markerSizeInvYield, colorConv, colorConv);
	histoPi0CorrYieldBinShifted->DrawCopy("same,e1,p");
	
	DrawGammaSetMarker(histoPi0Phos7TeV, markerStylePHOS, markerSizeInvYield , colorPHOS,colorPHOS);
	histoPi0Phos7TeV->Draw("same");
	cout << "bis hier her und nicht weiter" << endl;

	//histChargedPions7TeV->DrawCopy("same,e1,p");

	
	TLegend* legendYieldWithCharged = new TLegend(0.15,0.03,0.56,0.15);
	legendYieldWithCharged->SetTextSize(0.02);			
	legendYieldWithCharged->SetFillColor(0);
	//legendYieldWithCharged->AddEntry(graphChargedSpectrum,"ALICE #frac{h^{+} + h^{-}}{2} (stat. 30.11.2010)", "p");
	legendYieldWithCharged->AddEntry(graphChargedSpectrumWideRange,"ALICE #frac{h^{+} + h^{-}}{2} (stat. 29.09.2011)","pe");
	legendYieldWithCharged->AddEntry(histoPi0CorrYieldBinShifted,"Conversion","pe");
	legendYieldWithCharged->AddEntry(histoPi0Phos7TeV,"PHOS", "pe");
	legendYieldWithCharged->AddEntry(histoPi0ToChargedPhojet7TeV, "Phojet","p");
	legendYieldWithCharged->AddEntry(histoPi0ToChargedPythia7TeV, "Pythia Perugia 0","p");
	legendYieldWithCharged->Draw();
	
	if(!thesis)DrawAliceLogoPi0WithPHOSPrelim(pictDrawingCoordinatesCombineMeas[0], pictDrawingCoordinatesCombineMeas[1], pictDrawingCoordinatesCombineMeas[2], pictDrawingCoordinatesCombineMeas[3], pictDrawingCoordinatesCombineMeas[4], pictDrawingCoordinatesCombineMeas[5], pictDrawingCoordinatesCombineMeas[6], pictDrawingCoordinatesCombineMeas[7], pictDrawingCoordinates[8],collisionSystem7TeV, pictDrawingOptions[1], pictDrawingOptions[2], kTRUE,1350,1125);
	
	padComparisonRatio->cd();
	padComparisonRatio->SetGridx();
	padComparisonRatio->SetGridy();
	
	// ************************ Creating Ratios ******************************************************
	histoRatioConversion = (TH1D*) histoPi0CorrYieldBinShifted->Clone();	
	histoRatioChargedConvPhos = (TH1D*) histoPi0Phos7TeV->Clone();	
	//TH1D *histoRatioChargedPionsToCharged7TeV = (TH1D*)histChargedPions7TeV->Clone();	

	
	//-----------PHOS to charged ----------------------------------------
	npPHOS=histoPi0Phos7TeV->GetNbinsX(); 
	histoRatioChargedConvPhos = CalculateHistoRatioToFit (histoRatioChargedConvPhos, fitCharged); 
	
	//----------- Conv to charged ---------------------------------------
	histoRatioConversion = CalculateHistoRatioToFit (histoRatioConversion, fitCharged); 
	
	//----------- charged pions  to charged hadrons---------------------------------------
	//histoRatioChargedPionsToCharged7TeV = CalculateHistoRatioToFit (histoRatioChargedPionsToCharged7TeV, fitCharged); 	
	//----------- Plotting Ratios --------------------------------------
	TH2D *histo2DRatioOthers = new TH2D("histo2DRatioOthers", "histo2DRatioOthers", 20,0.,maxPtPi0,1000.,0.4,1.55);
	histo2DRatioOthers->SetYTitle("#frac{#pi^{0} Data}{0.5 (h^{+}+h^{-}) Data}");
	histo2DRatioOthers->SetXTitle("p_{t} (GeV/c)");
	histo2DRatioOthers->GetYaxis()->SetNdivisions(510,kTRUE);
	histo2DRatioOthers->GetYaxis()->SetLabelSize(0.075);
	histo2DRatioOthers->GetYaxis()->SetTitleSize(0.1);	
	histo2DRatioOthers->GetYaxis()->SetDecimals();
	histo2DRatioOthers->GetYaxis()->SetTitleOffset(0.43);
	histo2DRatioOthers->GetXaxis()->SetTitleSize(0.11);	
	histo2DRatioOthers->GetXaxis()->SetLabelSize(0.075);
	histo2DRatioOthers->SetTitle("");
	
	histo2DRatioOthers->DrawCopy("");
	
	histoPi0ToChargedPhojet7TeV->Draw("same,p");
	histoPi0ToChargedPythia7TeV->Draw("same,p");
	
	DrawGammaSetMarker(histoRatioConversion, markerStyleConv, markerSizeInvYield , colorConv,colorConv);
	histoRatioConversion->Draw("same");
	
	DrawGammaSetMarker(histoRatioChargedConvPhos, markerStylePHOS, markerSizeInvYield, colorPHOS,colorPHOS);
	histoRatioChargedConvPhos->Draw("same");

	//histoRatioChargedPionsToCharged7TeV->Draw("same");

	  DrawGammaLines(0., maxPtPi0,1., 1.,0.1);
	
	canvasComparison->Update();
	
	canvasComparison->SaveAs(Form("%s/Pi0_%s_InvYield_PHOS+CTS+Charged_7TeV.%s",outputDir.Data(),prefix2.Data(),suffix.Data()));
	delete padComparisonRatio;
	delete padComparison;
	delete canvasComparison;




	//**************************************************************************************************
	//*********************** Compare to Charged Pions 7 TeV    ****************************************
	//**************************************************************************************************

	TCanvas* canvasCompCharged = new TCanvas("canvasCompCharged","",1350,1500);  // gives the page size
	DrawGammaCanvasSettings( canvasCompCharged, 0.13, 0.02, 0.02, 0.09);
	
	TPad* padCompCharged = new TPad("padCompCharged", "", 0., 0.25, 1., 1.,-1, -1, -2);
	DrawGammaPadSettings( padCompCharged, 0.12, 0.02, 0.02, 0.);
	padCompCharged->Draw();
	
	TPad* padCompChargedRatio = new TPad("padCompChargedRatio", "", 0., 0., 1., 0.25,-1, -1, -2);
	DrawGammaPadSettings( padCompChargedRatio, 0.12, 0.02, 0., 0.2);
	padCompChargedRatio->Draw();
	
	padCompCharged->cd();
	padCompCharged->SetLogy();	

	Double_t maxPtPi0Conv =histoPi0CorrYieldBinShifted->GetXaxis()->GetBinUpEdge(histoPi0CorrYieldBinShifted->GetNbinsX()); 
	//Double_t maxPtPi0Conv =2.;; 

	TH2F * histo2DCompareChargedPions = new TH2F("histo2DCompareChargedPions","histo2DCompareChargedPions",20,0.,maxPtPi0Conv,1000.,10e-8,100.);
	//histo2DCompareChargedPions->SetXTitle("p_{t} (GeV/c)");
	histo2DCompareChargedPions->SetYTitle("#frac{1}{2#pi N_{INEL}} #frac{d^{2}N}{p_{t}dp_{t}dy(d#eta)} (c/GeV)^{2}");
	histo2DCompareChargedPions->SetTitle("");
	histo2DCompareChargedPions->GetYaxis()->SetDecimals();
	histo2DCompareChargedPions->GetYaxis()->SetLabelSize(0.025);
	histo2DCompareChargedPions->GetYaxis()->SetTitleOffset(1.1);
	histo2DCompareChargedPions->GetXaxis()->SetNdivisions(515,kTRUE);
	histo2DCompareChargedPions->DrawCopy(); 

	TH1D *histoPi0CorrYieldBinShifted7TeVINEL = (TH1D*)histoPi0CorrYieldBinShifted->Clone("histoPi0CorrYieldBinShifted7TeVINEL");
	histoPi0CorrYieldBinShifted7TeVINEL->Scale(0.852);
	histoPi0CorrYieldBinShifted7TeVINEL->Scale(2.);
	histoPi0CorrYieldBinShifted7TeVINEL->SetMarkerColor(kBlue);
	histoPi0CorrYieldBinShifted7TeVINEL->SetLineColor(kBlue);
	histoPi0CorrYieldBinShifted7TeVINEL->SetMarkerStyle(22);
	histoPi0CorrYieldBinShifted7TeVINEL->DrawCopy("same,e1,p");

	TGraphAsymmErrors* graphCorrectedYieldPi0SysErrBinShiftedINEL = (TGraphAsymmErrors*)graphCorrectedYieldPi0SysErrBinShifted->Clone();
	ScaleGraph(graphCorrectedYieldPi0SysErrBinShiftedINEL,0.852);
	ScaleGraph(graphCorrectedYieldPi0SysErrBinShiftedINEL,2.);
	graphCorrectedYieldPi0SysErrBinShiftedINEL = CalculateSysErrFromRelSysHisto( histoPi0CorrYieldBinShifted7TeVINEL,"graphCorrectedYieldPi0SysErrBinShiftedINEL",relSystErrorPi07TeVDown , relSystErrorPi07TeVUp, 2, nPointsPi0);	
	DrawGammaSetMarkerTGraphAsym(graphCorrectedYieldPi0SysErrBinShiftedINEL, 22,markerSizeInvYield, kBlue, kBlue);
	graphCorrectedYieldPi0SysErrBinShiftedINEL->SetFillStyle(1001);
	graphCorrectedYieldPi0SysErrBinShiftedINEL->SetFillColor(kBlue-8);
	graphCorrectedYieldPi0SysErrBinShiftedINEL->SetMarkerColor(kBlue);	
	graphCorrectedYieldPi0SysErrBinShiftedINEL->Draw("same,p,e2");

	histoPi0CorrYieldBinShifted7TeVINEL->DrawCopy("same,e1,p");

	TF1 * fitPi07TeVINEL = FitObject("l", "fitPi07TeVINEL","Pi0",	histoPi0CorrYieldBinShifted7TeVINEL,0.3,10.);

	TGraphAsymmErrors *graphChargedSpectrumTwice = (TGraphAsymmErrors*)graphChargedSpectrum->Clone("graphChargedSpectrumTwice");
	ScaleGraph(graphChargedSpectrumTwice,2.); // was divided by 2 before in comp to phos,...
	graphChargedSpectrumTwice->Draw("same,pe");



	fitChargedTwice = FitObject("l","fitChargedTwice","Pi0",graphChargedSpectrumTwice,0.2,maxPtPi0);
	DrawGammaSetMarkerTF1( fitChargedTwice, 8, 1, colorCharged);
	fitChargedTwice->SetRange(0.,maxPtPi0);
	fitChargedTwice->Draw("same");


	histChargedPions7TeV->DrawCopy("same,e1,p");
	histChargedPions7TeVHighPt->DrawCopy("same,e1,p");

	fitChargedPions7TeV->SetLineColor(colorEMCAL);
	fitChargedPions7TeV->SetLineWidth(0.8);
	//fitChargedPions7TeV->Draw("same");

	TLegend* legendYieldCharged = new TLegend(0.15,0.03,0.5,0.15);
	legendYieldCharged->SetTextSize(0.02);			
	legendYieldCharged->SetFillColor(0);
	legendYieldCharged->AddEntry(histChargedPions7TeV,"ALICE #pi^{+} + #pi^{-} low pt", "p");
	legendYieldCharged->AddEntry(histChargedPions7TeVHighPt,"ALICE #pi^{+} + #pi^{-} high pt", "p");
	legendYieldCharged->AddEntry(graphCorrectedYieldPi0SysErrBinShiftedINEL,"2 x Conversion, sys error","pe");
	legendYieldCharged->AddEntry(graphChargedSpectrumTwice,"charged hadrons","pe");
	legendYieldCharged->Draw();


	TLatex *labelTrigger7TeV = new TLatex(0.15,0.9,"#pi^{0} @ #sqrt{#it{s}} = 7TeV            #frac{N^{MB_{OR}}_events}{N^{INEL}_events} = 0.852 for PCM appl.");
	SetStyleTLatex( labelTrigger7TeV, 0.03,4);
	labelTrigger7TeV->Draw();

	TLatex *labeldydeta1 = new TLatex(0.5,0.7,"h^{+}+h^{-} meas. in d#eta");
	SetStyleTLatex( labeldydeta1, 0.03,4);
	labeldydeta1->Draw();

	TLatex *labeldydeta2 = new TLatex(0.5,0.64,"#pi^{+}+#pi^{-} and #pi^{0} meas. in dy");
	SetStyleTLatex( labeldydeta2, 0.03,4);
	labeldydeta2->Draw();

	if(!thesis)DrawAliceLogoPi0Preliminary(pictDrawingCoordinatesOnlyCTSMeasCross[0], pictDrawingCoordinatesOnlyCTSMeasCross[1], pictDrawingCoordinatesOnlyCTSMeasCross[2], pictDrawingCoordinatesOnlyCTSMeasCross[3], pictDrawingCoordinatesOnlyCTSMeasCross[4], pictDrawingCoordinatesOnlyCTSMeasCross[5], pictDrawingCoordinatesOnlyCTSMeasCross[6], pictDrawingCoordinatesOnlyCTSMeasCross[7], pictDrawingCoordinates[8],collisionSystemCombinedReallyAll, pictDrawingOptions[1], pictDrawingOptions[2], kTRUE,1200,1220);

	padCompChargedRatio->cd();
	padCompChargedRatio->SetGridx();
	padCompChargedRatio->SetGridy();

	TH2D *histo2DRatioChargedPion = new TH2D("histo2DRatioChargedPion", "histo2DRatioChargedPion", 20,0.,maxPtPi0Conv,1000.,0.25,1.25);
	histo2DRatioChargedPion->SetYTitle("#frac{Data}{(h^{+}+h^{-}) Fit}");
	histo2DRatioChargedPion->SetXTitle("p_{t} (GeV/c)");
	histo2DRatioChargedPion->GetYaxis()->SetNdivisions(510,kTRUE);
	histo2DRatioChargedPion->GetYaxis()->SetLabelSize(0.075);
	histo2DRatioChargedPion->GetYaxis()->SetTitleSize(0.1);	
	histo2DRatioChargedPion->GetYaxis()->SetDecimals();
	histo2DRatioChargedPion->GetYaxis()->SetTitleOffset(0.43);
	histo2DRatioChargedPion->GetXaxis()->SetTitleSize(0.11);	
	histo2DRatioChargedPion->GetXaxis()->SetLabelSize(0.075);
	histo2DRatioChargedPion->SetTitle("");
	histo2DRatioChargedPion->DrawCopy("");

	TH1D *histoPi0CorrYieldBinShiftedRatioToCharged7TeVINEL = (TH1D*)histoPi0CorrYieldBinShifted7TeVINEL->Clone("histoPi0CorrYieldBinShiftedRatioToCharged7TeVINEL");
	CalculateHistoRatioToFit(histoPi0CorrYieldBinShiftedRatioToCharged7TeVINEL, fitChargedTwice );

	TGraphAsymmErrors* graphRatioChargedPionsToChargedBinShifted7TeVINEL = (TGraphAsymmErrors*)graphCorrectedYieldPi0SysErrBinShiftedINEL->Clone("graphRatioChargedPionsToChargedBinShifted7TeVINEL");
	CalculateGraphErrRatioToFit(graphRatioChargedPionsToChargedBinShifted7TeVINEL, fitChargedTwice );
	DrawGammaSetMarkerTGraphAsym(graphRatioChargedPionsToChargedBinShifted7TeVINEL, 22,markerSizeInvYield, kBlue, kBlue);
	graphRatioChargedPionsToChargedBinShifted7TeVINEL->Draw("same,p,e2");

	TH1D *histoChargedPionRatioToCharged7TeV = (TH1D*)histChargedPions7TeV->Clone("histoChargedPionRatioToCharged7TeV");
	CalculateHistoRatioToFit(histoChargedPionRatioToCharged7TeV, fitChargedTwice );

	TH1D *histoChargedPionRatioToCharged7TeVHighPt = (TH1D*)histChargedPions7TeVHighPt->Clone("histoChargedPionRatioToCharged7TeVHighPt");
	CalculateHistoRatioToFit(histoChargedPionRatioToCharged7TeVHighPt, fitChargedTwice );

	histoPi0CorrYieldBinShiftedRatioToCharged7TeVINEL->Draw("same,p,e1");
	histoChargedPionRatioToCharged7TeV->Draw("same,p,e1");
	histoChargedPionRatioToCharged7TeVHighPt->Draw("same,p,e1");
	DrawGammaLines(0., maxPtPi0,1., 1.,0.1);


	TH1D *histoPi0FitToChargedSpectrumFit7TeVINEL = (TH1D*)histoPi0CorrYieldBinShifted7TeVINEL->Clone("histoPi0FitToChargedSpectrumFit7TeVINEL");
	histoPi0FitToChargedSpectrumFit7TeVINEL = CalculateFitToFitRatio(  fitPi07TeVINEL,	fitChargedPions7TeV);
	histoPi0FitToChargedSpectrumFit7TeVINEL->SetLineColor(2);
	//histoPi0FitToChargedSpectrumFit7TeVINEL->Draw("same");



	
	canvasCompCharged->Update();
	
	canvasCompCharged->SaveAs(Form("%s/Pi0_%s_InvYield_ComparisonChargedPions_7TeV.%s",outputDir.Data(),prefix2.Data(),suffix.Data()));
	//canvasCompCharged->SaveAs(Form("%s/Pi0_%s_InvYield_ComparisonChargedPions_7TeV_upto2.%s",outputDir.Data(),prefix2.Data(),suffix.Data()));

	delete padCompChargedRatio;
	delete padCompCharged;
	delete canvasCompCharged;



	//****************************************************************************************************************************************
	//******************************************* 2760 GeV ************************************************************************************
	//****************************************************************************************************************************************
	
	
	//**************************************************************************************************
	//*********************** Include Charged spectra, PHOS, PHOS+conv *********************************
	//**************************************************************************************************

	TCanvas* canvasComparison2760GeV = new TCanvas("canvasComparison2760GeV","",1350,1500);  // gives the page size
	DrawGammaCanvasSettings( canvasComparison2760GeV, 0.13, 0.02, 0.02, 0.09);
	
	TPad* padComparison2760GeV = new TPad("padComparison2760GeV", "", 0., 0.25, 1., 1.,-1, -1, -2);
	DrawGammaPadSettings( padComparison2760GeV, 0.12, 0.02, 0.02, 0.);
	padComparison2760GeV->Draw();
	
	TPad* padComparison2760GeVRatio = new TPad("padComparison2760GeVRatio", "", 0., 0., 1., 0.25,-1, -1, -2);
	DrawGammaPadSettings( padComparison2760GeVRatio, 0.12, 0.02, 0., 0.2);
	padComparison2760GeVRatio->Draw();
	
	padComparison2760GeV->cd();
	padComparison2760GeV->SetLogy();		
	
	TH2F * histo2DCompareCharged2760GeV = new TH2F("histo2DCompareCharged2760GeV","histo2DCompareCharged2760GeV",10,0.,maxPtPi02760GeV,1000.,(histoPi0Phos2760GeV->GetMinimum())/1000.,100);
	//histo2DCompareCharged2760GeV->SetXTitle("p_{t} (GeV/c)");
	histo2DCompareCharged2760GeV->SetYTitle("#frac{1}{2#pi N_{ev.}} #frac{d^{2}N}{p_{t}dp_{t}dy} (c/GeV)^{2}");	
	histo2DCompareCharged2760GeV->SetTitle("");
	histo2DCompareCharged2760GeV->GetYaxis()->SetDecimals();
	histo2DCompareCharged2760GeV->GetYaxis()->SetLabelSize(0.025);
	histo2DCompareCharged2760GeV->GetYaxis()->SetTitleOffset(1.1);
	histo2DCompareCharged2760GeV->GetXaxis()->SetNdivisions(515,kTRUE);
	histo2DCompareCharged2760GeV->DrawCopy();  
	
	//*************************** extracting charged particle spectra **********************************
	fileCharged2760GeV = 		new TFile(fileNameChargedSpectra2760GeV);
	histoCharged2760GeV = 		(TH1D*)fileCharged2760GeV->Get("dNdPt_276");	
	histoCharged2760GeV->Scale(0.5);

	DrawGammaSetMarker(histChargedHadrons2760GeVWideRange, markerStyleConv, markerSizeInvYield , colorCharged, colorCharged);
	histChargedHadrons2760GeVWideRange->Scale(0.5);
	histChargedHadrons2760GeVWideRange->Draw("same,pe1");	
	//----------------------- fitting Charged Particle ------------------------------
	
	fitCharged2760GeV = FitObject("l","fitCharged","Pi0",histChargedHadrons2760GeVWideRange,0.2,15.);
	
	DrawGammaSetMarker(histoCharged2760GeV, markerStyleConv, markerSizeInvYield , colorCharged, colorCharged);
	//histoCharged2760GeV->Draw("same,pe1");
	//fitCharged2760GeV = FitObject("l","fitCharged","Pi0",histoCharged2760GeV,0.2,15.);
	
	DrawGammaSetMarkerTF1( fitCharged2760GeV, 8, 1, colorCharged);
	fitCharged2760GeV->SetRange(0.,maxPtPi02760GeV);
	fitCharged2760GeV->Draw("same");
	cout << "fitted charged particle" <<endl;
	
	//-------------------------- Drawing Spectrum
	DrawGammaSetMarker(histoPi0CorrYieldBinShifted2760GeV, markerStyleConv, markerSizeInvYield , colorConv, colorConv);
	histoPi0CorrYieldBinShifted2760GeV->DrawCopy("same,e1,p");

	DrawGammaSetMarker(histoPi0Phos2760GeV, markerStylePHOS, markerSizeInvYield , colorPHOS,colorPHOS);
	histoPi0Phos2760GeV->Draw("same");
	cout << "bis hier her und nicht weiter" << endl;

	TLegend* legendYieldWithCharged2760GeV = new TLegend(0.15,0.03,0.56,0.15);
	legendYieldWithCharged2760GeV->SetTextSize(0.02);			
	legendYieldWithCharged2760GeV->SetFillColor(0);
	legendYieldWithCharged2760GeV->AddEntry(histoCharged2760GeV,"ALICE #frac{h^{+} + h^{-}}{2}", "p");
	legendYieldWithCharged2760GeV->AddEntry(histoPi0CorrYieldBinShifted2760GeV,"Conversion","pe");
	legendYieldWithCharged2760GeV->AddEntry(histoPi0Phos2760GeV,"PHOS", "pe");
	legendYieldWithCharged2760GeV->Draw();

	if(!thesis)DrawAliceLogoPi0WithPHOSPrelim(pictDrawingCoordinatesCombineMeas[0], pictDrawingCoordinatesCombineMeas[1], pictDrawingCoordinatesCombineMeas[2], pictDrawingCoordinatesCombineMeas[3], pictDrawingCoordinatesCombineMeas[4], pictDrawingCoordinatesCombineMeas[5], pictDrawingCoordinatesCombineMeas[6], pictDrawingCoordinatesCombineMeas[7], pictDrawingCoordinates[8],collisionSystem2760GeV, pictDrawingOptions[1], pictDrawingOptions[2], kTRUE,1350,1125);

	padComparison2760GeVRatio->cd();
	padComparison2760GeVRatio->SetGridx();
	padComparison2760GeVRatio->SetGridy();

	// ************************ Creating Ratios ******************************************************
	histoRatioConversion2760GeV = (TH1D*) histoPi0CorrYieldBinShifted2760GeV->Clone();	
	histoRatioChargedConvPhos2760GeV = (TH1D*) histoPi0Phos2760GeV->Clone();	

	//-----------PHOS to charged ----------------------------------------
	npPHOS2760GeV=histoPi0Phos2760GeV->GetNbinsX(); 
	histoRatioChargedConvPhos2760GeV = CalculateHistoRatioToFit (histoRatioChargedConvPhos2760GeV, fitCharged2760GeV); 

	//----------- Conv to charged ---------------------------------------
	histoRatioConversion2760GeV = CalculateHistoRatioToFit (histoRatioConversion2760GeV, fitCharged2760GeV); 

	//----------- Plotting Ratios --------------------------------------
	TH2D *histo2DRatioOthers2760GeV = new TH2D("histo2DRatioOthers2760GeV", "histo2DRatioOthers2760GeV", 20,0.,maxPtPi02760GeV,1000.,0.4,1.55);
	histo2DRatioOthers2760GeV->SetYTitle("#frac{#pi^{0} Data}{0.5 (h^{+}+h^{-}) Data}");
	histo2DRatioOthers2760GeV->SetXTitle("p_{t} (GeV/c)");
	histo2DRatioOthers2760GeV->GetYaxis()->SetNdivisions(510,kTRUE);
	histo2DRatioOthers2760GeV->GetYaxis()->SetLabelSize(0.075);
	histo2DRatioOthers2760GeV->GetYaxis()->SetTitleSize(0.1);	
	histo2DRatioOthers2760GeV->GetYaxis()->SetDecimals();
	histo2DRatioOthers2760GeV->GetYaxis()->SetTitleOffset(0.43);
	histo2DRatioOthers2760GeV->GetXaxis()->SetTitleSize(0.11);	
	histo2DRatioOthers2760GeV->GetXaxis()->SetLabelSize(0.075);
	histo2DRatioOthers2760GeV->SetTitle("");
	histo2DRatioOthers2760GeV->DrawCopy("");
		
	DrawGammaSetMarker(histoRatioConversion2760GeV, markerStyleConv, markerSizeInvYield , colorConv,colorConv);
	histoRatioConversion2760GeV->Draw("same");

	DrawGammaSetMarker(histoRatioChargedConvPhos2760GeV, markerStylePHOS, markerSizeInvYield , colorPHOS,colorPHOS);
	histoRatioChargedConvPhos2760GeV->Draw("same");
	DrawGammaLines(0., maxPtPi02760GeV,1., 1.,0.1);
	
	canvasComparison2760GeV->Update();

	canvasComparison2760GeV->SaveAs(Form("%s/Pi0_%s_InvYield_PHOS+CTS+Charged_2760GeV.%s",outputDir.Data(),prefix2.Data(),suffix.Data()));
	delete padComparison2760GeVRatio;
	delete padComparison2760GeV;
	delete canvasComparison2760GeV;
	



	//**************************************************************************************************
	//*********************** Compare to Charged Pions 2.76TeV    ****************************************
	//**************************************************************************************************

	TCanvas* canvasCompCharged2760GeV = new TCanvas("canvasCompCharged2760GeV","",1350,1500);  // gives the page size
	DrawGammaCanvasSettings( canvasCompCharged2760GeV, 0.13, 0.02, 0.02, 0.09);
	
	TPad* padCompCharged2760GeV = new TPad("padCompCharged2760GeV", "", 0., 0.25, 1., 1.,-1, -1, -2);
	DrawGammaPadSettings( padCompCharged2760GeV, 0.12, 0.02, 0.02, 0.);
	padCompCharged2760GeV->Draw();
	
	TPad* padCompCharged2760GeVRatio = new TPad("padCompCharged2760GeVRatio", "", 0., 0., 1., 0.25,-1, -1, -2);
	DrawGammaPadSettings( padCompCharged2760GeVRatio, 0.12, 0.02, 0., 0.2);
	padCompCharged2760GeVRatio->Draw();
	
	padCompCharged2760GeV->cd();
	padCompCharged2760GeV->SetLogy();	

	Double_t maxPtPi0Conv2760GeV =histoPi0CorrYieldBinShifted2760GeV->GetXaxis()->GetBinUpEdge(histoPi0CorrYieldBinShifted2760GeV->GetNbinsX()); 
	TH2F * histo2DCompareChargedPions2760GeV = new TH2F("histo2DCompareChargedPions2760GeV","histo2DCompareChargedPions2760GeV",20,0.,maxPtPi0Conv2760GeV,1000.,10e-8,100.);
	//histo2DCompareChargedPions2760GeV->SetXTitle("p_{t} (GeV/c)");
	histo2DCompareChargedPions2760GeV->SetYTitle("#frac{1}{2#pi N_{INEL}} #frac{d^{2}N}{p_{t}dp_{t}dy(d#eta)} (c/GeV)^{2}");
	histo2DCompareChargedPions2760GeV->SetTitle("");
	histo2DCompareChargedPions2760GeV->GetYaxis()->SetDecimals();
	histo2DCompareChargedPions2760GeV->GetYaxis()->SetLabelSize(0.025);
	histo2DCompareChargedPions2760GeV->GetYaxis()->SetTitleOffset(1.1);
	histo2DCompareChargedPions2760GeV->GetXaxis()->SetNdivisions(515,kTRUE);
	histo2DCompareChargedPions2760GeV->DrawCopy(); 


	TH1D *histoPi0CorrYieldBinShifted2760GeVINEL = (TH1D*)histoPi0CorrYieldBinShifted2760GeV->Clone("histoPi0CorrYieldBinShifted2760GeVINEL");
	histoPi0CorrYieldBinShifted2760GeVINEL->Scale(0.883);
	histoPi0CorrYieldBinShifted2760GeVINEL->Scale(2.);
	histoPi0CorrYieldBinShifted2760GeVINEL->SetMarkerColor(kBlue);
	histoPi0CorrYieldBinShifted2760GeVINEL->SetLineColor(kBlue);
	histoPi0CorrYieldBinShifted2760GeVINEL->SetMarkerStyle(22);	histoPi0CorrYieldBinShifted2760GeVINEL->DrawCopy("same,e1,p");


	TF1 * fitPi02760GeVINEL = FitObject("l", "fitPi02760GeVINEL","Pi0",	histoPi0CorrYieldBinShifted2760GeVINEL,0.3,10.);

	TGraphAsymmErrors* graphCorrectedYieldPi0SysErrBinShiftedINEL2760GeV = (TGraphAsymmErrors*)graphCorrectedYieldPi0SysErrBinShifted2760GeV->Clone();
	ScaleGraph(graphCorrectedYieldPi0SysErrBinShiftedINEL2760GeV,0.883);
	ScaleGraph(graphCorrectedYieldPi0SysErrBinShiftedINEL2760GeV,2.);
	graphCorrectedYieldPi0SysErrBinShiftedINEL2760GeV = CalculateSysErrFromRelSysHisto( histoPi0CorrYieldBinShifted2760GeVINEL,"graphCorrectedYieldPi0SysErrBinShiftedINEL2760GeV",relSystErrorPi02760GeVDown , relSystErrorPi02760GeVUp, 2, nPointsPi0);	
	DrawGammaSetMarkerTGraphAsym(graphCorrectedYieldPi0SysErrBinShiftedINEL2760GeV, 22,markerSizeInvYield, kBlue, kBlue);
	graphCorrectedYieldPi0SysErrBinShiftedINEL2760GeV->SetFillStyle(1001);
	graphCorrectedYieldPi0SysErrBinShiftedINEL2760GeV->SetFillColor(kBlue-8);
	graphCorrectedYieldPi0SysErrBinShiftedINEL2760GeV->SetMarkerColor(kBlue);	
	graphCorrectedYieldPi0SysErrBinShiftedINEL2760GeV->Draw("same,p,e2");

	
	histoPi0CorrYieldBinShifted2760GeVINEL->DrawCopy("same,e1,p");

	TH1D *histoChargedSpectrum2760GeVTwice = (TH1D*)histChargedHadrons2760GeVWideRange->Clone("histoChargedSpectrum2760GeVTwice");
	histoChargedSpectrum2760GeVTwice->Scale(2.); // was divided by 2 before for comp phos ...
	histoChargedSpectrum2760GeVTwice->DrawCopy("same, pe");


	fitCharged2760GeVTwice = FitObject("l","fitCharged2760GeVTwice","Pi0",histoChargedSpectrum2760GeVTwice,0.15,maxPtPi02760GeV);
	DrawGammaSetMarkerTF1( fitCharged2760GeVTwice, 8, 1, colorCharged);
	fitCharged2760GeVTwice->SetRange(0.,maxPtPi02760GeV);
	fitCharged2760GeVTwice->Draw("same");


	histChargedPions2760GeV->DrawCopy("same,e1,p");

	fitChargedPions2760GeV->SetLineColor(colorEMCAL);
	fitChargedPions2760GeV->SetLineWidth(0.8);
	//fitChargedPions2760GeV->Draw("same");

	labeldydeta1->Draw();
	labeldydeta2->Draw();

	TLegend* legendYieldCharged2670GeV = new TLegend(0.15,0.03,0.5,0.15);
	legendYieldCharged2670GeV->SetTextSize(0.02);			
	legendYieldCharged2670GeV->SetFillColor(0);
	legendYieldCharged2670GeV->AddEntry(histChargedPions2760GeV,"ALICE #pi^{+} + #pi^{-}", "p");
	legendYieldCharged2670GeV->AddEntry(histoChargedSpectrum2760GeVTwice,"charged hadrons","pe");
	legendYieldCharged2670GeV->AddEntry(graphCorrectedYieldPi0SysErrBinShiftedINEL2760GeV,"2 x Conversion, sys error","pe");
	//legendYieldCharged2670GeV->AddEntry(histoPi0CorrYieldBinShifted2760GeVINEL,"2 x Conversion","pe");
	legendYieldCharged2670GeV->Draw();

	TLatex *labelTrigger2760GeV = new TLatex(0.15,0.9,"#pi^{0} @ #sqrt{#it{s}} = 2.76TeV            #frac{N^{MB_{OR}}_events}{N^{INEL}_events} = 0.883 for PCM appl.");
	SetStyleTLatex( labelTrigger2760GeV, 0.03,4);
	labelTrigger2760GeV->Draw();

	if(!thesis)DrawAliceLogoPi0Preliminary(pictDrawingCoordinatesOnlyCTSMeasCross[0], pictDrawingCoordinatesOnlyCTSMeasCross[1], pictDrawingCoordinatesOnlyCTSMeasCross[2], pictDrawingCoordinatesOnlyCTSMeasCross[3], pictDrawingCoordinatesOnlyCTSMeasCross[4], pictDrawingCoordinatesOnlyCTSMeasCross[5], pictDrawingCoordinatesOnlyCTSMeasCross[6], pictDrawingCoordinatesOnlyCTSMeasCross[7], pictDrawingCoordinates[8],collisionSystemCombinedReallyAll, pictDrawingOptions[1], pictDrawingOptions[2], kTRUE,1200,1220);
	
	padCompCharged2760GeVRatio->cd();
	padCompCharged2760GeVRatio->SetGridx();
	padCompCharged2760GeVRatio->SetGridy();

	TH2D *histo2DRatioCharged2670GeVPion = new TH2D("histo2DRatioCharged2670GeVPion", "histo2DRatioCharged2670GeVPion", 20,0.,maxPtPi0Conv2760GeV,1000.,0.25,1.25);
	histo2DRatioCharged2670GeVPion->SetYTitle("#frac{Data}{(h^{+}+h^{-}) Fit}");
	histo2DRatioCharged2670GeVPion->SetXTitle("p_{t} (GeV/c)");
	histo2DRatioCharged2670GeVPion->GetYaxis()->SetNdivisions(510,kTRUE);
	histo2DRatioCharged2670GeVPion->GetYaxis()->SetLabelSize(0.075);
	histo2DRatioCharged2670GeVPion->GetYaxis()->SetTitleSize(0.1);	
	histo2DRatioCharged2670GeVPion->GetYaxis()->SetDecimals();
	histo2DRatioCharged2670GeVPion->GetYaxis()->SetTitleOffset(0.43);
	histo2DRatioCharged2670GeVPion->GetXaxis()->SetTitleSize(0.11);	
	histo2DRatioCharged2670GeVPion->GetXaxis()->SetLabelSize(0.075);
	histo2DRatioCharged2670GeVPion->SetTitle("");
	histo2DRatioCharged2670GeVPion->DrawCopy("");

	TH1D *histoPi0CorrYieldBinShiftedRatioToCharged2760GeVINEL = (TH1D*)histoPi0CorrYieldBinShifted2760GeVINEL->Clone("histoPi0CorrYieldBinShiftedRatioToCharged2760GeVINEL");
	CalculateHistoRatioToFit(histoPi0CorrYieldBinShiftedRatioToCharged2760GeVINEL, fitCharged2760GeVTwice );

	
	TGraphAsymmErrors* graphRatioChargedPionsToChargedBinShifted2760GeVINEL = (TGraphAsymmErrors*)graphCorrectedYieldPi0SysErrBinShiftedINEL2760GeV->Clone("graphRatioChargedPionsToChargedBinShifted2760GeVINEL");
	CalculateGraphErrRatioToFit(graphRatioChargedPionsToChargedBinShifted2760GeVINEL, fitCharged2760GeVTwice );
	DrawGammaSetMarkerTGraphAsym(graphRatioChargedPionsToChargedBinShifted2760GeVINEL, 22,markerSizeInvYield, kBlue, kBlue);
	graphRatioChargedPionsToChargedBinShifted2760GeVINEL->Draw("same,p,e2");
	

	TH1D *histoChargedPionRatioToCharged2760GeV = (TH1D*)histChargedPions2760GeV->Clone("histoChargedPionRatioToCharged2760GeV");
	CalculateHistoRatioToFit(histoChargedPionRatioToCharged2760GeV, fitCharged2760GeVTwice );


	histoPi0CorrYieldBinShiftedRatioToCharged2760GeVINEL->Draw("same,p,e1");
	histoChargedPionRatioToCharged2760GeV->Draw("same,p,e1");
	DrawGammaLines(0., maxPtPi0,1., 1.,0.1);


	TH1D *histoPi0FitToChargedSpectrumFit2760GeVINEL = (TH1D*)histoPi0CorrYieldBinShifted2760GeVINEL->Clone("histoPi0FitToChargedSpectrumFit2760GeVINEL");
	histoPi0FitToChargedSpectrumFit2760GeVINEL = CalculateFitToFitRatio(  fitPi02760GeVINEL,	fitChargedPions2760GeV);
	histoPi0FitToChargedSpectrumFit2760GeVINEL->SetLineColor(2);
	//histoPi0FitToChargedSpectrumFit2760GeVINEL->Draw("same");


	
	canvasCompCharged2760GeV->Update();
	
	canvasCompCharged2760GeV->SaveAs(Form("%s/Pi0_%s_InvYield_ComparisonChargedPions_2760GeV.%s",outputDir.Data(),prefix2.Data(),suffix.Data()));

	delete padCompCharged2760GeVRatio;
	delete padCompCharged2760GeV;
	delete canvasCompCharged2760GeV;


	//****************************************************************************************************************************************
	//******************************************* 900 GeV ************************************************************************************
	//****************************************************************************************************************************************
	
	
	//**************************************************************************************************
	//*********************** Include Charged spectra, PHOS, PHOS+conv *********************************
	//**************************************************************************************************
	
	DrawGammaSetMarker(histoPi0ToChargedPhojet900GeV, markerStyleConvMC, markerSizeInvYield-0.3, kCyan-6, kCyan-6);		
	DrawGammaSetMarker(histoPi0ToChargedPythia900GeV, markerStyleConvMC, markerSizeInvYield-0.3, kCyan+3, kCyan+3);		
	
	
	TCanvas* canvasComparison900GeV = new TCanvas("canvasComparison900GeV","",1350,1500);  // gives the page size
	DrawGammaCanvasSettings( canvasComparison900GeV, 0.13, 0.02, 0.02, 0.09);
	
	TPad* padComparison900GeV = new TPad("padComparison900GeV", "", 0., 0.25, 1., 1.,-1, -1, -2);
	DrawGammaPadSettings( padComparison900GeV, 0.12, 0.02, 0.02, 0.);
	padComparison900GeV->Draw();
	
	TPad* padComparison900GeVRatio = new TPad("padComparison900GeVRatio", "", 0., 0., 1., 0.25,-1, -1, -2);
	DrawGammaPadSettings( padComparison900GeVRatio, 0.12, 0.02, 0., 0.2);
	padComparison900GeVRatio->Draw();
	
	padComparison900GeV->cd();
	padComparison900GeV->SetLogy();		
	
	TH2F * histo2DCompareCharged900GeV = new TH2F("histo2DCompareCharged900GeV","histo2DCompareCharged900GeV",10,0.,maxPtPi0900GeV,1000.,(histoPi0Phos900GeV->GetMinimum())/1000.,100);
	//histo2DCompareCharged900GeV->SetXTitle("p_{t} (GeV/c)");
	histo2DCompareCharged900GeV->SetYTitle("#frac{1}{2#pi N_{ev.}} #frac{d^{2}N}{p_{t}dp_{t}dy} (c/GeV)^{2}");	
	histo2DCompareCharged900GeV->SetTitle("");
	histo2DCompareCharged900GeV->GetYaxis()->SetDecimals();
	histo2DCompareCharged900GeV->GetYaxis()->SetLabelSize(0.025);
	histo2DCompareCharged900GeV->GetYaxis()->SetTitleOffset(1.1);
	histo2DCompareCharged900GeV->GetXaxis()->SetNdivisions(515,kTRUE);
	histo2DCompareCharged900GeV->DrawCopy();  
	
	//*************************** extracting charged particle spectra **********************************
	for (Int_t i = 0; i < 46; i++){
		p7853_d4x1y1_yval[i] = p7853_d4x1y1_yval[i]/2.;
		p7853_d4x1y1_yerrplus[i] = p7853_d4x1y1_yerrplus[i]/2.;
		p7853_d4x1y1_yerrplus[i] = p7853_d4x1y1_yerrplus[i]/2.;
	}
	
	graphFitChargedSpect900GeV = new TGraphAsymmErrors(p7853_d4x1y1_numpoints, p7853_d4x1y1_xval, p7853_d4x1y1_yval, p7853_d4x1y1_xerrminus, p7853_d4x1y1_xerrplus, p7853_d4x1y1_yerrminus, p7853_d4x1y1_yerrplus);
	graphChargedSpectrum900GeV = new TGraphAsymmErrors(p7853_d4x1y1_numpoints, p7853_d4x1y1_xval, p7853_d4x1y1_yval, p7853_d4x1y1_xerrminus, p7853_d4x1y1_xerrplus, p7853_d4x1y1_yerrminus, p7853_d4x1y1_yerrplus);
	

	graphChargedSpectrum900GeVWideRange = new TGraphAsymmErrors(histChargedHadrons900GeVWideRange); 
	graphFitChargedSpectrum900GeVWideRange = new TGraphAsymmErrors(histChargedHadrons900GeVWideRange); 
	ScaleGraph(graphChargedSpectrum900GeVWideRange,0.5);
	ScaleGraph(graphFitChargedSpectrum900GeVWideRange,0.5);
	
	
	//----------------------- fitting Charged Particle ------------------------------
	
	fitCharged900GeV = FitObject("l","fitCharged","Pi0",graphFitChargedSpectrum900GeVWideRange,0.2,15.);
	
	DrawGammaSetMarkerTGraphAsym(graphChargedSpectrum900GeV, markerStyleConv, markerSizeInvYield , colorCharged, colorCharged);
	//graphChargedSpectrum900GeV->Draw("pe");

	DrawGammaSetMarkerTGraphAsym(graphChargedSpectrum900GeVWideRange, markerStyleConv, markerSizeInvYield ,  colorCharged, colorCharged );
	graphChargedSpectrum900GeV->Draw("pe");
	
	DrawGammaSetMarkerTF1( fitCharged900GeV, 8, 1, colorCharged);
	fitCharged900GeV->SetRange(0.,maxPtPi0900GeV);
	fitCharged900GeV->Draw("same");
	cout << "fitted charged particle" <<endl;
	
	//-------------------------- Drawing Spectrum
	DrawGammaSetMarker(histoPi0CorrYieldBinShifted900GeV, markerStyleConv, markerSizeInvYield , colorConv, colorConv);
	histoPi0CorrYieldBinShifted900GeV->DrawCopy("same,e1,p");

	DrawGammaSetMarker(histoPi0Phos900GeV, markerStylePHOS, markerSizeInvYield , colorPHOS,colorPHOS);
	histoPi0Phos900GeV->Draw("same");
	cout << "bis hier her und nicht weiter" << endl;

	TLegend* legendYieldWithCharged900GeV = new TLegend(0.15,0.03,0.56,0.15);
	legendYieldWithCharged900GeV->SetTextSize(0.02);			
	legendYieldWithCharged900GeV->SetFillColor(0);
	legendYieldWithCharged900GeV->AddEntry(graphChargedSpectrum900GeVWideRange,"ALICE #frac{h^{+} + h^{-}}{2}", "p");
	legendYieldWithCharged900GeV->AddEntry(histoPi0CorrYieldBinShifted900GeV,"Conversion","pe");
	legendYieldWithCharged900GeV->AddEntry(histoPi0Phos900GeV,"PHOS", "pe");
	legendYieldWithCharged900GeV->AddEntry(histoPi0ToChargedPhojet900GeV,"Phojet","p");
	legendYieldWithCharged900GeV->AddEntry(histoPi0ToChargedPythia900GeV,"Pythia Perugia 0","p");
	legendYieldWithCharged900GeV->Draw();

	if(!thesis)DrawAliceLogoPi0WithPHOSPrelim(pictDrawingCoordinatesCombineMeas[0], pictDrawingCoordinatesCombineMeas[1], pictDrawingCoordinatesCombineMeas[2], pictDrawingCoordinatesCombineMeas[3], pictDrawingCoordinatesCombineMeas[4], pictDrawingCoordinatesCombineMeas[5], pictDrawingCoordinatesCombineMeas[6], pictDrawingCoordinatesCombineMeas[7], pictDrawingCoordinates[8],collisionSystem900GeV, pictDrawingOptions[1], pictDrawingOptions[2], kTRUE,1350,1125);

	padComparison900GeVRatio->cd();
	padComparison900GeVRatio->SetGridx();
	padComparison900GeVRatio->SetGridy();

	// ************************ Creating Ratios ******************************************************
	histoRatioConversion900GeV = (TH1D*) histoPi0CorrYieldBinShifted900GeV->Clone();	
	histoRatioChargedConvPhos900GeV = (TH1D*) histoPi0Phos900GeV->Clone();	

	//-----------PHOS to charged ----------------------------------------
	npPHOS=histoPi0Phos900GeV->GetNbinsX(); 
	histoRatioChargedConvPhos900GeV = CalculateHistoRatioToFit (histoRatioChargedConvPhos900GeV, fitCharged900GeV); 

	//----------- Conv to charged ---------------------------------------
	histoRatioConversion900GeV = CalculateHistoRatioToFit (histoRatioConversion900GeV, fitCharged900GeV); 

	//----------- Plotting Ratios --------------------------------------
	TH2D *histo2DRatioOthers900GeV = new TH2D("histo2DRatioOthers900GeV", "histo2DRatioOthers900GeV", 20,0.,maxPtPi0900GeV,1000.,0.4,1.55);
	histo2DRatioOthers900GeV->SetYTitle("#frac{#pi^{0} Data}{0.5 (h^{+}+h^{-}) Data}");
	histo2DRatioOthers900GeV->SetXTitle("p_{t} (GeV/c)");
	histo2DRatioOthers900GeV->GetYaxis()->SetNdivisions(510,kTRUE);
	histo2DRatioOthers900GeV->GetYaxis()->SetLabelSize(0.075);
	histo2DRatioOthers900GeV->GetYaxis()->SetTitleSize(0.1);	
	histo2DRatioOthers900GeV->GetYaxis()->SetDecimals();
	histo2DRatioOthers900GeV->GetYaxis()->SetTitleOffset(0.43);
	histo2DRatioOthers900GeV->GetXaxis()->SetTitleSize(0.11);	
	histo2DRatioOthers900GeV->GetXaxis()->SetLabelSize(0.075);
	histo2DRatioOthers900GeV->SetTitle("");
	histo2DRatioOthers900GeV->DrawCopy("");
	
	histoPi0ToChargedPhojet900GeV->Draw("same,p");
	histoPi0ToChargedPythia900GeV->Draw("same,p");
	
	DrawGammaSetMarker(histoRatioConversion900GeV, markerStyleConv, markerSizeInvYield , colorConv,colorConv);
	histoRatioConversion900GeV->Draw("same");

	DrawGammaSetMarker(histoRatioChargedConvPhos900GeV, markerStylePHOS, markerSizeInvYield , colorPHOS,colorPHOS);
	histoRatioChargedConvPhos900GeV->Draw("same");
	DrawGammaLines(0., maxPtPi0900GeV,1., 1.,0.1);
	
	canvasComparison900GeV->Update();

	canvasComparison900GeV->SaveAs(Form("%s/Pi0_%s_InvYield_PHOS+CTS+Charged_900GeV.%s",outputDir.Data(),prefix2.Data(),suffix.Data()));
	delete padComparison900GeVRatio;
	delete padComparison900GeV;
	delete canvasComparison900GeV;






	//**************************************************************************************************
	//*********************** Compare to Charged Pions 900 GeV    ****************************************
	//**************************************************************************************************

	TCanvas* canvasCompCharged900GeV = new TCanvas("canvasCompCharged900GeV","",1350,1500);  // gives the page size
	DrawGammaCanvasSettings( canvasCompCharged900GeV, 0.13, 0.02, 0.02, 0.09);
	
	TPad* padCompCharged900GeV = new TPad("padCompCharged900GeV", "", 0., 0.25, 1., 1.,-1, -1, -2);
	DrawGammaPadSettings( padCompCharged900GeV, 0.12, 0.02, 0.02, 0.);
	padCompCharged900GeV->Draw();
	
	TPad* padCompCharged900GeVRatio = new TPad("padCompCharged900GeVRatio", "", 0., 0., 1., 0.25,-1, -1, -2);
	DrawGammaPadSettings( padCompCharged900GeVRatio, 0.12, 0.02, 0., 0.2);
	padCompCharged900GeVRatio->Draw();
	
	padCompCharged900GeV->cd();
	padCompCharged900GeV->SetLogy();	

	Double_t maxPtPi0900GeVConv =histoPi0CorrYieldBinShifted900GeV->GetXaxis()->GetBinUpEdge(histoPi0CorrYieldBinShifted900GeV->GetNbinsX()); 

	TH2F * histo2DCompareChargedPion900GeV = new TH2F("histo2DCompareChargedPion900GeV","histo2DCompareChargedPion900GeV",20,0.,maxPtPi0900GeVConv,1000.,10.e-6,10.);
	//histo2DCompareCharged->SetXTitle("p_{t} (GeV/c)");
	histo2DCompareChargedPion900GeV->SetYTitle("#frac{1}{2#pi N_{INEL}} #frac{d^{2}N}{p_{t}dp_{t}dy(d#eta)} (c/GeV)^{2}");
	histo2DCompareChargedPion900GeV->SetTitle("");
	histo2DCompareChargedPion900GeV->GetYaxis()->SetDecimals();
	histo2DCompareChargedPion900GeV->GetYaxis()->SetLabelSize(0.025);
	histo2DCompareChargedPion900GeV->GetYaxis()->SetTitleOffset(1.1);
	histo2DCompareChargedPion900GeV->GetXaxis()->SetNdivisions(515,kTRUE);
	histo2DCompareChargedPion900GeV->DrawCopy();  

	TH1D *histoPi0CorrYieldBinShifted900GeVINEL = (TH1D*)histoPi0CorrYieldBinShifted900GeV->Clone("histoPi0CorrYieldBinShifted900GeVINEL");
	histoPi0CorrYieldBinShifted900GeVINEL->Scale(0.916);
	histoPi0CorrYieldBinShifted900GeVINEL->Scale(2.);
	histoPi0CorrYieldBinShifted900GeVINEL->SetMarkerColor(kBlue);
	histoPi0CorrYieldBinShifted900GeVINEL->SetLineColor(kBlue);
	histoPi0CorrYieldBinShifted900GeVINEL->SetMarkerStyle(22);
	histoPi0CorrYieldBinShifted900GeVINEL->Draw("same,e1,p");

	//neu 900
	TGraphAsymmErrors* graphCorrectedYieldPi0SysErrBinShiftedINEL900GeV = (TGraphAsymmErrors*)graphCorrectedYieldPi0SysErrBinShifted900GeV->Clone();
	ScaleGraph(graphCorrectedYieldPi0SysErrBinShiftedINEL900GeV,0.916);
	ScaleGraph(graphCorrectedYieldPi0SysErrBinShiftedINEL900GeV,2.);
	graphCorrectedYieldPi0SysErrBinShiftedINEL900GeV = CalculateSysErrFromRelSysHisto( histoPi0CorrYieldBinShifted900GeVINEL,"graphCorrectedYieldPi0SysErrBinShiftedINEL900GeV",relSystErrorPi0900GeVDown , relSystErrorPi0900GeVUp, 2, nPointsPi0);	
	DrawGammaSetMarkerTGraphAsym(graphCorrectedYieldPi0SysErrBinShiftedINEL900GeV, 22,markerSizeInvYield, kBlue, kBlue);
	graphCorrectedYieldPi0SysErrBinShiftedINEL900GeV->SetFillStyle(1001);
	graphCorrectedYieldPi0SysErrBinShiftedINEL900GeV->SetFillColor(kBlue-8);
	graphCorrectedYieldPi0SysErrBinShiftedINEL900GeV->SetMarkerColor(kBlue);	
	graphCorrectedYieldPi0SysErrBinShiftedINEL900GeV->Draw("same,p,e2");
	//ende neu
	histoPi0CorrYieldBinShifted900GeVINEL->Draw("same,e1,p");


	DrawGammaSetMarkerTGraphAsym(graphChargedSpectrum900GeVWideRange, markerStyleConv,markerSizeInvYield, colorEMCAL, colorEMCAL);
	graphChargedSpectrum900GeVWideRange->Draw("same,e1,p");

	fitChargedPions900GeV->SetLineColor(colorEMCAL);
	fitChargedPions900GeV->SetLineWidth(0.8);
	//fitChargedPions900GeV->Draw("same");

	TGraphAsymmErrors * graphChargedSpectrum900GeVTwice = (TGraphAsymmErrors *)graphChargedSpectrum900GeVWideRange->Clone("graphChargedSpectrum900GeVTwice");
	ScaleGraph(graphChargedSpectrum900GeVTwice, 2.); // was divided by 2 before for comp phos ...
	graphChargedSpectrum900GeVTwice->Draw("same,pe");

	fitCharged900GeVTwice = FitObject("l","fitCharged900GeVTwice","Pi0",graphChargedSpectrum900GeVTwice,0.2,15.);
	DrawGammaSetMarkerTF1( fitCharged900GeVTwice, 8, 1, colorCharged);
	//fitCharged900GeVTwice->Draw("same");

	TLegend* legendYieldCharged900GeV = new TLegend(0.15,0.03,0.5,0.15);
	legendYieldCharged900GeV->SetTextSize(0.02);			
	legendYieldCharged900GeV->SetFillColor(0);
	legendYieldCharged900GeV->AddEntry(graphChargedPions900GeV,"ALICE #pi^{+} + #pi^{-}", "p");
	legendYieldCharged900GeV->AddEntry(graphChargedSpectrum900GeVTwice,"ALICE h^{+} + h^{-}", "p");
	legendYieldCharged900GeV->AddEntry(graphCorrectedYieldPi0SysErrBinShiftedINEL900GeV,"2 x Conversion, sys error","pe");
	//legendYieldCharged900GeV->AddEntry(histoPi0CorrYieldBinShifted900GeVINEL,"2 x Conversion","pe");
	legendYieldCharged900GeV->Draw();

	TLatex *labelTrigger900GeV = new TLatex(0.2,0.9,"#pi^{0} @ #sqrt{#it{s}} = 0.9TeV         #frac{N^{MB_{OR}}_events}{N^{INEL}_events} = 0.916 for PCM appl.");
	SetStyleTLatex( labelTrigger900GeV, 0.03,4);
	labelTrigger900GeV->Draw();


	labeldydeta1->Draw();
	labeldydeta2->Draw();


	if(!thesis)DrawAliceLogoPi0Preliminary(pictDrawingCoordinatesOnlyCTSMeasCross[0], pictDrawingCoordinatesOnlyCTSMeasCross[1], pictDrawingCoordinatesOnlyCTSMeasCross[2], pictDrawingCoordinatesOnlyCTSMeasCross[3], pictDrawingCoordinatesOnlyCTSMeasCross[4], pictDrawingCoordinatesOnlyCTSMeasCross[5], pictDrawingCoordinatesOnlyCTSMeasCross[6], pictDrawingCoordinatesOnlyCTSMeasCross[7], pictDrawingCoordinates[8],collisionSystemCombinedReallyAll, pictDrawingOptions[1], pictDrawingOptions[2], kTRUE,1200,1220);

	padCompCharged900GeVRatio->cd();
	padCompCharged900GeVRatio->SetGridx();
	padCompCharged900GeVRatio->SetGridy();



	TH2D *histo2DRatioChargedPion900GeV = new TH2D("histo2DRatioChargedPion900GeV", "histo2DRatioChargedPion900GeV", 20,0.,maxPtPi0900GeVConv,1000.,0.25,1.25);
	histo2DRatioChargedPion900GeV->SetYTitle("#frac{Data}{h^{+}+h^{-} Fit}");
	histo2DRatioChargedPion900GeV->SetXTitle("p_{t} (GeV/c)");
	histo2DRatioChargedPion900GeV->GetYaxis()->SetNdivisions(510,kTRUE);
	histo2DRatioChargedPion900GeV->GetYaxis()->SetLabelSize(0.075);
	histo2DRatioChargedPion900GeV->GetYaxis()->SetTitleSize(0.1);	
	histo2DRatioChargedPion900GeV->GetYaxis()->SetDecimals();
	histo2DRatioChargedPion900GeV->GetYaxis()->SetTitleOffset(0.43);
	histo2DRatioChargedPion900GeV->GetXaxis()->SetTitleSize(0.11);	
	histo2DRatioChargedPion900GeV->GetXaxis()->SetLabelSize(0.075);
	histo2DRatioChargedPion900GeV->SetTitle("");
	histo2DRatioChargedPion900GeV->DrawCopy("");



	//neu 900
	TGraphAsymmErrors* graphRatioChargedPionsToChargedBinShifted900GeVINEL = (TGraphAsymmErrors*)graphCorrectedYieldPi0SysErrBinShiftedINEL900GeV->Clone("graphRatioChargedPionsToChargedBinShifted900GeVINEL");
	CalculateGraphErrRatioToFit(graphRatioChargedPionsToChargedBinShifted900GeVINEL, fitCharged900GeVTwice );
	DrawGammaSetMarkerTGraphAsym(graphRatioChargedPionsToChargedBinShifted900GeVINEL, 22,markerSizeInvYield, kBlue, kBlue);
	graphRatioChargedPionsToChargedBinShifted900GeVINEL->Draw("same,p,e2");
	//ende neu
					   
	TH1D *histoPi0CorrYieldBinShiftedRatioToCharged900GeVINEL = (TH1D*)histoPi0CorrYieldBinShifted900GeVINEL->Clone("histoPi0CorrYieldBinShiftedRatioToCharged900GeVINEL");
	CalculateHistoRatioToFit(histoPi0CorrYieldBinShiftedRatioToCharged900GeVINEL, fitCharged900GeVTwice );
	histoPi0CorrYieldBinShiftedRatioToCharged900GeVINEL->Draw("same,p,e1");

	TGraphAsymmErrors* graphRatioChargedPionsToCharged900GeV = (TGraphAsymmErrors*)graphChargedPions900GeV->Clone("graphRatioChargedPionsToCharged900GeV");
	CalculateGraphErrRatioToFit(graphRatioChargedPionsToCharged900GeV,fitCharged900GeVTwice);
	graphRatioChargedPionsToCharged900GeV->Draw("same,p,e");


					   
	DrawGammaLines(0., maxPtPi0,1., 1.,0.1);
	
	canvasCompCharged900GeV->Update();
	
	canvasCompCharged900GeV->SaveAs(Form("%s/Pi0_%s_InvYield_ComparisonChargedPions_900GeV.%s",outputDir.Data(),prefix2.Data(),suffix.Data()));

	delete padCompCharged900GeVRatio;
	delete padCompCharged900GeV;
	delete canvasCompCharged900GeV;

































	// **************************  CalculateMeanPt for conversion   *************************************************
 
  
	Float_t mean_Pi0_7TeV, mean_Pi0_7TeV_err;
	CalculateMeanPtWithError(fitLevyConvStatErrPi07TeV,mean_Pi0_7TeV,mean_Pi0_7TeV_err);

	Float_t mean_Pi0_2760GeV,mean_Pi0_2760GeV_err;
	CalculateMeanPtWithError(fitLevyConvStatErrPi02760GeV, mean_Pi0_2760GeV, mean_Pi0_2760GeV_err );

	Float_t mean_Pi0_900GeV,mean_Pi0_900GeV_err;
	CalculateMeanPtWithError(fitLevyConvStatErrPi0900GeV, mean_Pi0_900GeV, mean_Pi0_900GeV_err);

	Float_t mean_Eta_7TeV, mean_Eta_7TeV_err;
	CalculateMeanPtWithError(fitLevyConvStatErrEta7TeV, mean_Eta_7TeV, mean_Eta_7TeV_err);

	Float_t mean_Eta_2760GeV, mean_Eta_2760GeV_err;
	  CalculateMeanPtWithError(fitLevyConvStatErrEta2760GeV,mean_Eta_2760GeV,mean_Eta_2760GeV_err);



	// **************************  end CalculateMeanPt for conversion   *************************************************

	if (onlyConv) {
		CalculateFitResults( fitLevyConvStatErrPi07TeV , fitLevyConvSysErrPi07TeV ,fitResultsPi07TeV, "Levy" ,xSection7TeV*recalcBarn);
	} else {
		CalculateFitResults( fitLevyConvStatErrPi07TeV , fitLevyConvSysErrPi07TeV, fitResultsPi07TeV );
	}
	CalculateFitResults( fitLevyConvStatErrEta7TeV , fitLevyConvSysErrEta7TeV, fitResultsEta7TeV);
	CalculateFitResults( fitLevyConvStatErrPi02760GeV , fitLevyConvSysErrPi02760GeV, fitResultsPi02760GeV);
	CalculateFitResults( fitLevyConvStatErrEta2760GeV , fitLevyConvSysErrEta2760GeV, fitResultsEta2760GeV);
	CalculateFitResults( fitLevyConvStatErrPi0900GeV , fitLevyConvSysErrPi0900GeV, fitResultsPi0900GeV);
	
	TBox* boxErrorSigmaCTSPi07TeV = CreateBoxConv(kRed-9, 0.25, 1E11, 0.29, 1E11+2*xSection7TeVErr*1E9);
	TBox* boxErrorSigmaCTSPi0900GeV = CreateBoxConv(kRed-9, 0.32, 1E11, 0.38, 1E11+(2*xSection900GeVErr*1E9));
	TBox* boxErrorSigmaCTSPi02760GeV = CreateBoxConv(kRed-9, 0.32, 1E11, 0.38, 1E11+2*xSection2760GeVErr*1E9);
	TBox* boxErrorSigmaCTSEta7TeV = CreateBoxConv(kRed-9, 0.32, 1E10, 0.38, 1E10+2*xSection7TeVErr*1E9);
	TBox* boxErrorSigmaCTSEta900GeV = CreateBoxConv(kRed-9, 0.72, 1E9, 0.78, 1E9+(2*xSection900GeVErr*1E9));
	TBox* boxErrorSigmaCTSEta2760GeV = CreateBoxConv(kRed-9, 0.42, 1E10, 0.48, 1E10+2*xSection2760GeVErr*1E9);

	TCanvas* canvasInvXSectionPi07TeV = new TCanvas("canvasInvXSectionPi07TeV","",1200,900);  // gives the page size
	DrawGammaCanvasSettings( canvasInvXSectionPi07TeV, 0.13, 0.02, 0.02, 0.09);
	canvasInvXSectionPi07TeV->SetLogy();
	canvasInvXSectionPi07TeV->SetLogx();
	
	TH2F * histo2DInvXSectionPi07TeV = new TH2F("histo2DInvXSectionPi07TeV","histo2DInvXSectionPi07TeV",1000,0.23,20.,1000,2e3,2e12);
	SetStyleHistoTH2ForGraphs(histo2DInvXSectionPi07TeV, "p_{T} (GeV/c)","E #frac{d^{3}#sigma}{dp^{3}} (pb GeV^{-2} c^{3} )", 0.032,0.04, 0.04,0.04, 1,1.55);
	histo2DInvXSectionPi07TeV->DrawCopy(); 

// 	boxErrorSigmaCTSPi07TeV->Draw();
	DrawGammaSetMarkerTGraph(graphInvCrossSectionSysPi0 , 20, 0.2, kBlack, kBlack);
	graphInvCrossSectionSysPi0->SetFillStyle(1001);
	graphInvCrossSectionSysPi0->SetFillColor(colorConvSyst);
	graphInvCrossSectionSysPi0->SetLineColor(colorConvSyst);
	graphInvCrossSectionSysPi0->Draw("same,e2,p");
	DrawGammaSetMarker(histoInvCrossSectionPi0 , 20, 0.5, kBlack, kBlack);
	histoInvCrossSectionPi0->Draw("same,e1,x0,p");
	histo2DInvXSectionPi07TeV->DrawCopy("same");  

/*	DrawBinShiftingText(binshiftingRightMiddle[0], binshiftingRightMiddle[1], binshiftingRightMiddle[2]);*/
	DrawNormalizationErrorText(normalizationInvXSingleEn[0],normalizationInvXSingleEn[1],normalizationInvXSingleEn[2],
						  normalizationInvXSingleEn[3],normalizationInvXSingleEn[4],"7TeV"); 



	if(!thesis)DrawAliceLogoPi0Preliminary(pictDrawingCoordinatesInvX[0], pictDrawingCoordinatesInvX[1], pictDrawingCoordinatesInvX[2], pictDrawingCoordinatesInvX[3], pictDrawingCoordinatesInvX[4], pictDrawingCoordinatesInvX[5], pictDrawingCoordinatesInvX[6], pictDrawingCoordinatesInvX[7], pictDrawingCoordinates[8],collisionSystem7TeV, pictDrawingOptions[1], pictDrawingOptions[2], kTRUE,1200,900);
	canvasInvXSectionPi07TeV->Update();	
	canvasInvXSectionPi07TeV->SaveAs(Form("%s/Pi0_InvXSectionOnlyCTS7TeV.%s",outputDir.Data(),suffix.Data()));
	
	canvasInvXSectionPi07TeV->cd();
	
	DrawGammaSetMarkerTF1( fitInvCrossSectionPi0, styleFitIndivid, widthCommonFit, colorFitIndivid);
	fitInvCrossSectionPi0->SetRange(0.3,15.5);
	fitInvCrossSectionPi0->Draw("same");
	histoInvCrossSectionPi0->Draw("same,e1,x0,p");
	
	PrintLevyFitResults(0.18, 0.25 , 0.11,0.1, 0.05 ,0.035, 
					fitResultsPi07TeV);
	canvasInvXSectionPi07TeV->Update();	
	canvasInvXSectionPi07TeV->SaveAs(Form("%s/Pi0_InvXSectionOnlyCTS7TeVInclFit.%s",outputDir.Data(),suffix.Data()));	
	delete canvasInvXSectionPi07TeV;

	TCanvas* canvasInvXSectionEtaCombined7TeV = new TCanvas("canvasInvXSectionEtaCombined7TeV","",1200,900);  // gives the page size
	DrawGammaCanvasSettings( canvasInvXSectionEtaCombined7TeV, 0.13, 0.02, 0.02, 0.09);
	canvasInvXSectionEtaCombined7TeV->SetLogy();
	canvasInvXSectionEtaCombined7TeV->SetLogx();
	
	TH2F * histo2DInvXSectionCombEta7TeV = new TH2F("histo2DInvXSectionCombEta7TeV","histo2DInvXSectionCombEta7TeV",1000,0.3,20.,1000,2e4,2e11);
	SetStyleHistoTH2ForGraphs(histo2DInvXSectionCombEta7TeV, "p_{T} (GeV/c)","E #frac{d^{3}#sigma}{dp^{3}} (pb GeV^{-2} c^{3} )", 0.032,0.04, 0.04,0.04, 1,1.55);
	histo2DInvXSectionCombEta7TeV->DrawCopy(); 

// 	boxErrorSigmaCTSEta7TeV->Draw();
	graphInvCrossSectionEtaComb7TeV->Draw("p,E2same");
	fitInvCrossSectionEta7TeV->Draw("same");
	histo2DInvXSectionCombEta7TeV->DrawCopy("same");  

/*	DrawBinShiftingText(binshiftingRightMiddle[0], binshiftingRightMiddle[1], binshiftingRightMiddle[2]); */
	DrawNormalizationErrorText(normalizationInvXSingleEn[0],normalizationInvXSingleEn[1],normalizationInvXSingleEn[2],
						  normalizationInvXSingleEn[3],normalizationInvXSingleEn[4],"7TeV"); 


	if(!thesis)DrawAliceLogoPi0Preliminary(pictDrawingCoordinatesInvX[0], pictDrawingCoordinatesInvX[1], pictDrawingCoordinatesInvX[2], pictDrawingCoordinatesInvX[3], pictDrawingCoordinatesInvX[4], pictDrawingCoordinatesInvX[5], pictDrawingCoordinatesInvX[6], pictDrawingCoordinatesInvX[7], pictDrawingCoordinates[8],collisionSystem7TeV, pictDrawingOptions[1], pictDrawingOptions[2], kFALSE,1200,900);
	canvasInvXSectionEtaCombined7TeV->Update();	
	canvasInvXSectionEtaCombined7TeV->SaveAs(Form("%s/Eta_InvXSectionComb7TeV.%s",outputDir.Data(),suffix.Data()));
	
	canvasInvXSectionEtaCombined7TeV->cd();

	
	TCanvas* canvasInvXSectionEta7TeV = new TCanvas("canvasInvXSectionEta7TeV","",1200,900);  // gives the page size
	DrawGammaCanvasSettings( canvasInvXSectionEta7TeV, 0.13, 0.02, 0.02, 0.09);
	canvasInvXSectionEta7TeV->SetLogy();
	canvasInvXSectionEta7TeV->SetLogx();
	
	TH2F * histo2DInvXSectionEta7TeV = new TH2F("histo2DInvXSectionEta7TeV","histo2DInvXSectionEta7TeV",1000,0.3,10.,1000,2e4,2e11);
	SetStyleHistoTH2ForGraphs(histo2DInvXSectionEta7TeV, "p_{T} (GeV/c)","E #frac{d^{3}#sigma}{dp^{3}} (pb GeV^{-2} c^{3} )", 0.032,0.04, 0.04,0.04, 1,1.55);
	histo2DInvXSectionEta7TeV->DrawCopy(); 

// 	boxErrorSigmaCTSEta7TeV->Draw();
	graphInvCrossSectionSysEta = ScaleGraph(graphInvCrossSectionSysEta,1e3);
	DrawGammaSetMarkerTGraph(graphInvCrossSectionSysEta , 20, 0.2, kBlack, kBlack);
	graphInvCrossSectionSysEta->SetFillStyle(1001);
	graphInvCrossSectionSysEta->SetFillColor(colorConvSyst);
	graphInvCrossSectionSysEta->SetLineColor(colorConvSyst);
	graphInvCrossSectionSysEta->Draw("same,e2,p");
	histoInvCrossSectionEta->Scale(1e3);
	DrawGammaSetMarker(histoInvCrossSectionEta , 20, 0.5, kBlack, kBlack);
	histoInvCrossSectionEta->Draw("same,e1,x0,p");
	histo2DInvXSectionEta7TeV->DrawCopy("same");  

/*	DrawBinShiftingText(binshiftingRightMiddle[0], binshiftingRightMiddle[1], binshiftingRightMiddle[2]); */
	DrawNormalizationErrorText(normalizationInvXSingleEn[0],normalizationInvXSingleEn[1],normalizationInvXSingleEn[2],
						  normalizationInvXSingleEn[3],normalizationInvXSingleEn[4],"7TeV"); 


	if(!thesis)DrawAliceLogoPi0Preliminary(pictDrawingCoordinatesInvX[0], pictDrawingCoordinatesInvX[1], pictDrawingCoordinatesInvX[2], pictDrawingCoordinatesInvX[3], pictDrawingCoordinatesInvX[4], pictDrawingCoordinatesInvX[5], pictDrawingCoordinatesInvX[6], pictDrawingCoordinatesInvX[7], pictDrawingCoordinates[8],collisionSystem7TeV, pictDrawingOptions[1], pictDrawingOptions[2], kFALSE,1200,900);
	canvasInvXSectionEta7TeV->Update();	
	canvasInvXSectionEta7TeV->SaveAs(Form("%s/Eta_InvXSectionOnlyCTS7TeV.%s",outputDir.Data(),suffix.Data()));
	
	canvasInvXSectionEta7TeV->cd();
	
	DrawGammaSetMarkerTF1( fitInvCrossSectionEta7TeV, styleFitIndivid, widthCommonFit, colorFitIndivid);
	fitInvCrossSectionEta7TeV->SetRange(0.4,8.);
	fitInvCrossSectionEta7TeV->Draw("same");
	histoInvCrossSectionEta->Draw("same,e1,x0,p");
	
	PrintLevyFitResults(0.18, 0.25 , 0.11,0.1, 0.05 ,0.035, 
					fitResultsEta7TeV);
	canvasInvXSectionEta7TeV->Update();	
	canvasInvXSectionEta7TeV->SaveAs(Form("%s/Eta_InvXSectionOnlyCTS7TeVInclFit.%s",outputDir.Data(),suffix.Data()));	
	delete canvasInvXSectionEta7TeV;

	TCanvas* canvasInvXSectionPi02760GeV = new TCanvas("canvasInvXSectionPi02760GeV","",1200,900);  // gives the page size
	DrawGammaCanvasSettings( canvasInvXSectionPi02760GeV, 0.13, 0.02, 0.02, 0.09);
	canvasInvXSectionPi02760GeV->SetLogy();
	canvasInvXSectionPi02760GeV->SetLogx();

	TH2F * histo2DInvXSectionPi02760GeV = new TH2F("histo2DInvXSectionPi02760GeV","histo2DInvXSectionPi02760GeV",1000,0.3,10.,1000,1e4,1e12);
	SetStyleHistoTH2ForGraphs(histo2DInvXSectionPi02760GeV, "p_{T} (GeV/c)","E #frac{d^{3}#sigma}{dp^{3}} (pb GeV^{-2} c^{3} )", 0.032,0.04, 0.04,0.04, 1,1.55);
	histo2DInvXSectionPi02760GeV->DrawCopy(); 

// 	boxErrorSigmaCTSPi02760GeV->Draw();
	DrawGammaSetMarkerTGraph(graphInvCrossSectionSysPi02760GeV , 20, 0.2, kBlack, kBlack);
	graphInvCrossSectionSysPi02760GeV->SetFillStyle(1001);
	graphInvCrossSectionSysPi02760GeV->SetFillColor(colorConvSyst);
	graphInvCrossSectionSysPi02760GeV->SetLineColor(colorConvSyst);
	graphInvCrossSectionSysPi02760GeV->Draw("same,e2,p");
	DrawGammaSetMarker(histoInvCrossSectionPi02760GeV , 20, 0.5, kBlack, kBlack);
	histoInvCrossSectionPi02760GeV->Draw("same,e1,x0,p");
	histo2DInvXSectionPi02760GeV->DrawCopy("same");  

/*	DrawBinShiftingText(binshiftingRightMiddle[0], binshiftingRightMiddle[1], binshiftingRightMiddle[2]);*/
	DrawNormalizationErrorText(normalizationInvXSingleEn[0],normalizationInvXSingleEn[1],normalizationInvXSingleEn[2],
						  normalizationInvXSingleEn[3],normalizationInvXSingleEn[4],"2.76TeV"); 

	if(!thesis)DrawAliceLogoPi0Preliminary(pictDrawingCoordinatesInvX[0], pictDrawingCoordinatesInvX[1], pictDrawingCoordinatesInvX[2], pictDrawingCoordinatesInvX[3], pictDrawingCoordinatesInvX[4], pictDrawingCoordinatesInvX[5], pictDrawingCoordinatesInvX[6], pictDrawingCoordinatesInvX[7], pictDrawingCoordinates[8],collisionSystem2760GeV, pictDrawingOptions[1], pictDrawingOptions[2], kTRUE,1200,900);

	canvasInvXSectionPi02760GeV->Update();	
	canvasInvXSectionPi02760GeV->SaveAs(Form("%s/Pi0_InvXSectionOnlyCTS2760GeV.%s",outputDir.Data(),suffix.Data()));
	
	canvasInvXSectionPi02760GeV->cd();
	
	DrawGammaSetMarkerTF1( fitInvCrossSectionPi02760GeV, styleFitIndivid, widthCommonFit, colorFitIndivid);
	fitInvCrossSectionPi02760GeV->SetRange(0.4,8.);
	fitInvCrossSectionPi02760GeV->Draw("same");
	histoInvCrossSectionPi02760GeV->Draw("same,e1,x0,p");
	
	PrintLevyFitResults(0.18, 0.25 , 0.11,0.1, 0.05 ,0.035, 
					fitResultsPi02760GeV);
	canvasInvXSectionPi02760GeV->Update();	
	canvasInvXSectionPi02760GeV->SaveAs(Form("%s/Pi0_InvXSectionOnlyCTS2760GeVInclFit.%s",outputDir.Data(),suffix.Data()));	
	delete canvasInvXSectionPi02760GeV;

	TCanvas* canvasInvXSectionEta2760GeV = new TCanvas("canvasInvXSectionEta2760GeV","",1200,900);  // gives the page size
	DrawGammaCanvasSettings( canvasInvXSectionEta2760GeV, 0.13, 0.02, 0.02, 0.09);
	canvasInvXSectionEta2760GeV->SetLogy();
	canvasInvXSectionEta2760GeV->SetLogx();
	
	TH2F * histo2DInvXSectionEta2760GeV = new TH2F("histo2DInvXSectionEta2760GeV","histo2DInvXSectionEta2760GeV",1000,0.4,10.,1000,2e4,2e10);
	SetStyleHistoTH2ForGraphs(histo2DInvXSectionEta2760GeV, "p_{T} (GeV/c)","E #frac{d^{3}#sigma}{dp^{3}} (pb GeV^{-2} c^{3} )", 0.032,0.04, 0.04,0.04, 1,1.55);
	histo2DInvXSectionEta2760GeV->DrawCopy(); 

// 	boxErrorSigmaCTSEta2760GeV->Draw();
	DrawGammaSetMarkerTGraph(graphInvCrossSectionSysEta2760GeV , 20, 0.2, kBlack, kBlack);
	graphInvCrossSectionSysEta2760GeV->SetFillStyle(1001);
	graphInvCrossSectionSysEta2760GeV->SetFillColor(colorConvSyst);
	graphInvCrossSectionSysEta2760GeV->SetLineColor(colorConvSyst);
	graphInvCrossSectionSysEta2760GeV->Draw("same,e2,p");
	DrawGammaSetMarker(histoInvCrossSectionEta2760GeV , 20, 0.5, kBlack, kBlack);
	histoInvCrossSectionEta2760GeV->Draw("same,e1,x0,p");
	histo2DInvXSectionEta2760GeV->DrawCopy("same");  

	DrawNormalizationErrorText(normalizationInvXSingleEn[0],normalizationInvXSingleEn[1],normalizationInvXSingleEn[2],
						  normalizationInvXSingleEn[3],normalizationInvXSingleEn[4],"2.76TeV"); 


	if(!thesis)DrawAliceLogoPi0Preliminary(pictDrawingCoordinatesInvX[0], pictDrawingCoordinatesInvX[1], pictDrawingCoordinatesInvX[2], pictDrawingCoordinatesInvX[3], pictDrawingCoordinatesInvX[4], pictDrawingCoordinatesInvX[5], pictDrawingCoordinatesInvX[6], pictDrawingCoordinatesInvX[7], pictDrawingCoordinates[8],collisionSystem2760GeV, pictDrawingOptions[1], pictDrawingOptions[2], kFALSE,1200,900);
	canvasInvXSectionEta2760GeV->Update();	
	canvasInvXSectionEta2760GeV->SaveAs(Form("%s/Eta_InvXSectionOnlyCTS2760GeV.%s",outputDir.Data(),suffix.Data()));
	
	canvasInvXSectionEta2760GeV->cd();
	
	DrawGammaSetMarkerTF1( fitInvCrossSectionEta2760GeV, styleFitIndivid, widthCommonFit, colorFitIndivid);
	fitInvCrossSectionEta2760GeV->SetRange(0.6,6.0);
	fitInvCrossSectionEta2760GeV->Draw("same");
	histoInvCrossSectionEta2760GeV->Draw("same,e1,x0,p");
	
	PrintLevyFitResults(0.18, 0.25 , 0.11,0.1, 0.05 ,0.035, 
					fitResultsEta2760GeV);
	
	canvasInvXSectionEta2760GeV->Update();	
	canvasInvXSectionEta2760GeV->SaveAs(Form("%s/Eta_InvXSectionOnlyCTS2760GeVInclFit.%s",outputDir.Data(),suffix.Data()));	
	delete canvasInvXSectionEta2760GeV;

		TCanvas* canvasInvXSectionPi0900GeV = new TCanvas("canvasInvXSectionPi0900GeV","",1200,900);  // gives the page size
	DrawGammaCanvasSettings( canvasInvXSectionPi0900GeV, 0.13, 0.02, 0.02, 0.09);
	canvasInvXSectionPi0900GeV->SetLogy();
	canvasInvXSectionPi0900GeV->SetLogx();

	TH2F * histo2DInvXSectionPi0900GeV = new TH2F("histo2DInvXSectionPi0900GeV","histo2DInvXSectionPi0900GeV",1000,0.3,6.,1000,2e5,1e12);
	SetStyleHistoTH2ForGraphs(histo2DInvXSectionPi0900GeV, "p_{T} (GeV/c)","E #frac{d^{3}#sigma}{dp^{3}} (pb GeV^{-2} c^{3} )", 0.032,0.04, 0.04,0.04, 1,1.55);
	histo2DInvXSectionPi0900GeV->DrawCopy(); 

  // boxErrorSigmaCTSPi0900GeV->Draw(); 
	graphInvCrossSectionSysPi0900GeV = ScaleGraph(graphInvCrossSectionSysPi0900GeV,1e1);
	DrawGammaSetMarkerTGraph(graphInvCrossSectionSysPi0900GeV , 20, 0.2, kBlack, kBlack);
	graphInvCrossSectionSysPi0900GeV->SetFillStyle(1001);
	graphInvCrossSectionSysPi0900GeV->SetFillColor(colorConvSyst);
	graphInvCrossSectionSysPi0900GeV->SetLineColor(colorConvSyst);
	graphInvCrossSectionSysPi0900GeV->Draw("same,e2,p");
	histoInvCrossSectionPi0900GeV->Scale(1e1);
	DrawGammaSetMarker(histoInvCrossSectionPi0900GeV , 20, 0.5, kBlack, kBlack);
	histoInvCrossSectionPi0900GeV->Draw("same,e1,x0,p");
	histo2DInvXSectionPi0900GeV->DrawCopy("same");  
/*		TLegend* legendYieldSysBinShifted = new TLegend(0.15,0.1,0.5,0.19);
	legendYieldSysBinShifted->SetTextSize(0.02);			
	legendYieldSysBinShifted->SetFillColor(0);
	legendYieldSysBinShifted->AddEntry(histoPi0CorrYieldBinShifted,"Corrected yield");
	legendYieldSysBinShifted->AddEntry(graphCorrectedYieldPi0SysErrBinShifted,"Systematic uncertainty","f");
	legendYieldSysBinShifted->Draw();*/

/*	DrawBinShiftingText(binshiftingRightMiddle[0], binshiftingRightMiddle[1], binshiftingRightMiddle[2]);*/
	DrawNormalizationErrorText(normalizationInvXSingleEn[0],normalizationInvXSingleEn[1],normalizationInvXSingleEn[2],
						  normalizationInvXSingleEn[3],normalizationInvXSingleEn[4],"900GeV"); 

	
	if(!thesis)DrawAliceLogoPi0Preliminary(pictDrawingCoordinatesInvX[0], pictDrawingCoordinatesInvX[1], pictDrawingCoordinatesInvX[2], pictDrawingCoordinatesInvX[3], pictDrawingCoordinatesInvX[4], pictDrawingCoordinatesInvX[5], pictDrawingCoordinatesInvX[6], pictDrawingCoordinatesInvX[7], pictDrawingCoordinates[8],collisionSystem900GeV, pictDrawingOptions[1], pictDrawingOptions[2], kTRUE,1200,900);
	canvasInvXSectionPi0900GeV->Update();	
	canvasInvXSectionPi0900GeV->SaveAs(Form("%s/Pi0_InvXSectionOnlyCTS900GeV.%s",outputDir.Data(),suffix.Data()));
	
	canvasInvXSectionPi0900GeV->cd();
	
	DrawGammaSetMarkerTF1( fitInvCrossSectionPi0900GeV, styleFitIndivid, widthCommonFit, colorFitIndivid);
	fitInvCrossSectionPi0900GeV->SetRange(0.4,4.);
	fitInvCrossSectionPi0900GeV->Draw("same");
	histoInvCrossSectionPi0900GeV->Draw("same,e1,x0,p");
	
	PrintLevyFitResults(0.18, 0.25 , 0.11,0.1, 0.05 ,0.035, 
					fitResultsPi0900GeV);
	canvasInvXSectionPi0900GeV->Update();	
	canvasInvXSectionPi0900GeV->SaveAs(Form("%s/Pi0_InvXSectionOnlyCTS900GeVInclFit.%s",outputDir.Data(),suffix.Data()));	
	delete canvasInvXSectionPi0900GeV;

	TCanvas* canvasInvXSectionEta900GeV = new TCanvas("canvasInvXSectionEta900GeV","",1200,900);  // gives the page size
	DrawGammaCanvasSettings( canvasInvXSectionEta900GeV, 0.13, 0.02, 0.02, 0.09);
	canvasInvXSectionEta900GeV->SetLogy();
	canvasInvXSectionEta900GeV->SetLogx();
	
	TH2F * histo2DInvXSectionEta900GeV = new TH2F("histo2DInvXSectionEta900GeV","histo2DInvXSectionEta900GeV",1000,0.7,4.,1000,2e6,1e10);
	SetStyleHistoTH2ForGraphs(histo2DInvXSectionEta900GeV, "p_{T} (GeV/c)","E #frac{d^{3}#sigma}{dp^{3}} (pb GeV^{-2} c^{3} )", 0.032,0.04, 0.04,0.04, 1,1.55);
	histo2DInvXSectionEta900GeV->DrawCopy(); 

// 	boxErrorSigmaCTSEta900GeV->Draw();
	DrawGammaSetMarkerTGraph(graphInvCrossSectionSysEta900GeV , 20, 0.2, kBlack, kBlack);
	graphInvCrossSectionSysEta900GeV->SetFillStyle(1001);
	graphInvCrossSectionSysEta900GeV->SetFillColor(colorConvSyst);
	graphInvCrossSectionSysEta900GeV->SetLineColor(colorConvSyst);
	graphInvCrossSectionSysEta900GeV->Draw("same,e2,p");
	DrawGammaSetMarker(histoInvCrossSectionEta900GeV , 20, 0.5, kBlack, kBlack);
	histoInvCrossSectionEta900GeV->Draw("same,e1,x0,p");
	histo2DInvXSectionEta900GeV->DrawCopy("same");  

/*	DrawBinShiftingText(binshiftingRightMiddle[0], binshiftingRightMiddle[1], binshiftingRightMiddle[2]);*/
	DrawNormalizationErrorText(normalizationInvXSingleEn[0],normalizationInvXSingleEn[1],normalizationInvXSingleEn[2],
						  normalizationInvXSingleEn[3],normalizationInvXSingleEn[4],"900GeV"); 

	if(!thesis)DrawAliceLogoPi0Preliminary(pictDrawingCoordinatesInvX[0], pictDrawingCoordinatesInvX[1], pictDrawingCoordinatesInvX[2], pictDrawingCoordinatesInvX[3], pictDrawingCoordinatesInvX[4], pictDrawingCoordinatesInvX[5], pictDrawingCoordinatesInvX[6], pictDrawingCoordinatesInvX[7], pictDrawingCoordinates[8],collisionSystem900GeV, pictDrawingOptions[1], pictDrawingOptions[2], kFALSE,1200,900);
	canvasInvXSectionEta900GeV->Update();	
	canvasInvXSectionEta900GeV->SaveAs(Form("%s/Eta_InvXSectionOnlyCTS900GeV.%s",outputDir.Data(),suffix.Data()));
	delete canvasInvXSectionEta900GeV;

	
	TCanvas* canvasInvXSectionPi0ConvOnlyAllEnergies = new TCanvas("canvasInvXSectionPi0ConvOnlyAllEnergies","",1200,900);  // gives the page size
	DrawGammaCanvasSettings( canvasInvXSectionPi0ConvOnlyAllEnergies, 0.13, 0.02, 0.02, 0.09);
	canvasInvXSectionPi0ConvOnlyAllEnergies->SetLogy();
	canvasInvXSectionPi0ConvOnlyAllEnergies->SetLogx();
	
	TH2F * histo2DInvXSectionPi0OnlyConvAllEnergies = new TH2F("histo2DInvXSectionPi0OnlyConvAllEnergies","histo2DInvXSectionPi0OnlyConvAllEnergies",1000,0.23,30.,1000,2e2,4e12);
	SetStyleHistoTH2ForGraphs(histo2DInvXSectionPi0OnlyConvAllEnergies, "p_{T} (GeV/c)","E #frac{d^{3}#sigma}{dp^{3}} (pb GeV^{-2} c^{3} )", 0.032,0.04, 0.04,0.04, 1,1.55);
	histo2DInvXSectionPi0OnlyConvAllEnergies->DrawCopy(); 

// 	boxErrorSigmaCTSPi07TeV->Draw();
	DrawGammaSetMarkerTGraph(graphInvCrossSectionSysPi0 , 20, 0.5, colorCommonSpectrumPi07TeV, colorCommonSpectrumPi07TeV);
	graphInvCrossSectionSysPi0->SetFillStyle(1001);
	graphInvCrossSectionSysPi0->SetFillColor(colorCommonSpectrumPi07TeVBox);
	graphInvCrossSectionSysPi0->SetLineColor(colorCommonSpectrumPi07TeVBox);
	graphInvCrossSectionSysPi0->Draw("same,e2,p");

	graphInvCrossSectionSysPi02760GeV = ScaleGraph(graphInvCrossSectionSysPi02760GeV,1e-1);
	DrawGammaSetMarkerTGraph(graphInvCrossSectionSysPi02760GeV , 20, 0.5, colorCommonSpectrumPi02760GeV, colorCommonSpectrumPi02760GeV);
	graphInvCrossSectionSysPi02760GeV->SetFillStyle(1001);
	graphInvCrossSectionSysPi02760GeV->SetFillColor(colorCommonSpectrumPi02760GeVBox);
	graphInvCrossSectionSysPi02760GeV->SetLineColor(colorCommonSpectrumPi02760GeVBox);
	graphInvCrossSectionSysPi02760GeV->Draw("same,e2,p");
	
	graphInvCrossSectionSysPi0900GeV = ScaleGraph(graphInvCrossSectionSysPi0900GeV,1e-2);
	DrawGammaSetMarkerTGraph(graphInvCrossSectionSysPi0900GeV , 20, 0.5, colorCommonSpectrumPi0900GeV, colorCommonSpectrumPi0900GeV);
	graphInvCrossSectionSysPi0900GeV->SetFillStyle(1001);
	graphInvCrossSectionSysPi0900GeV->SetFillColor(colorCommonSpectrumPi0900GeVBox);
	graphInvCrossSectionSysPi0900GeV->SetLineColor(colorCommonSpectrumPi0900GeVBox);
	graphInvCrossSectionSysPi0900GeV->Draw("same,e2,p");
	
	DrawGammaSetMarker(histoInvCrossSectionPi0 , 20, 1., colorCommonSpectrumPi07TeV, colorCommonSpectrumPi07TeV);
	histoInvCrossSectionPi0->Draw("same,e1,x0,p");
	histoInvCrossSectionPi02760GeV->Scale(1e-1);
	DrawGammaSetMarker(histoInvCrossSectionPi02760GeV , 20, 1., colorCommonSpectrumPi02760GeV, colorCommonSpectrumPi02760GeV);
	histoInvCrossSectionPi02760GeV->Draw("same,e1,x0,p");
	histoInvCrossSectionPi0900GeV->Scale(1e-2);
	DrawGammaSetMarker(histoInvCrossSectionPi0900GeV , 20, 1., colorCommonSpectrumPi0900GeV, colorCommonSpectrumPi0900GeV);
	histoInvCrossSectionPi0900GeV->Draw("same,e1,x0,p");
	
	histo2DInvXSectionPi0OnlyConvAllEnergies->DrawCopy("same");  

	//DrawBinShiftingText(binshiftingRightMiddle[0], binshiftingRightMiddle[1], binshiftingRightMiddle[2]);  
	DrawNormalizationErrorText(normalizationInvXCTSALLEn[0],normalizationInvXCTSALLEn[1],normalizationInvXCTSALLEn[2],
						  normalizationInvXCTSALLEn[3],normalizationInvXCTSALLEn[4],"all"); 

	labelScalingPi07TeVAllEnergiesOnlyCTS->Draw();

	labelScalingPi02760GeVAllEnergiesOnlyCTS->Draw();

	labelScalingPi0900GeVAllEnergiesOnlyCTS->Draw();

	
	TLegend* legendConvAllPi0 = new TLegend(0.15,0.34,0.4,0.44);
	legendConvAllPi0->SetTextSize(0.028);			
	legendConvAllPi0->SetFillColor(0);
	legendConvAllPi0->SetBorderSize(0);
	legendConvAllPi0->AddEntry(histoInvCrossSectionPi0,Form("PCM  #sqrt{#it{s}} = 7 TeV"),"p");
	legendConvAllPi0->AddEntry(histoInvCrossSectionPi02760GeV,Form("PCM  #sqrt{#it{s}} = 2.76 TeV"),"p");
	legendConvAllPi0->AddEntry(histoInvCrossSectionPi0900GeV,Form("PCM  #sqrt{#it{s}} = 0.9 TeV"),"p");
	legendConvAllPi0->Draw();

	
	if(!thesis)DrawAliceLogoPi0Preliminary(pictDrawingCoordinatesInvX[0]-0.1, pictDrawingCoordinatesInvX[1], pictDrawingCoordinatesInvX[2], pictDrawingCoordinatesInvX[3], pictDrawingCoordinatesInvX[4], pictDrawingCoordinatesInvX[5], pictDrawingCoordinatesInvX[6], pictDrawingCoordinatesInvX[7], pictDrawingCoordinates[8],collisionSystemCombinedReallyAll, pictDrawingOptions[1], pictDrawingOptions[2], kTRUE,1200,900);
	canvasInvXSectionPi0ConvOnlyAllEnergies->Update();	
	canvasInvXSectionPi0ConvOnlyAllEnergies->SaveAs(Form("%s/Pi0_InvXSectionOnlyCTSAllEnergies.%s",outputDir.Data(),suffix.Data()));

	

	
	TCanvas* canvasInvXSectionEtaConvOnlyAllEnergies = new TCanvas("canvasInvXSectionEtaConvOnlyAllEnergies","",1200,900);  // gives the page size
	DrawGammaCanvasSettings( canvasInvXSectionEtaConvOnlyAllEnergies, 0.13, 0.02, 0.02, 0.09);
	canvasInvXSectionEtaConvOnlyAllEnergies->SetLogy();
	canvasInvXSectionEtaConvOnlyAllEnergies->SetLogx();
	
	TH2F * histo2DInvXSectionEtaOnlyConvAllEnergies = new TH2F("histo2DInvXSectionEtaOnlyConvAllEnergies","histo2DInvXSectionEtaOnlyConvAllEnergies",1000,0.3,10.,1000,7e3,5e10);
	SetStyleHistoTH2ForGraphs(histo2DInvXSectionEtaOnlyConvAllEnergies, "p_{T} (GeV/c)","E #frac{d^{3}#sigma}{dp^{3}} (pb GeV^{-2} c^{3} )", 0.032,0.04, 0.04,0.04, 1,1.55);
	histo2DInvXSectionEtaOnlyConvAllEnergies->DrawCopy(); 

// 	boxErrorSigmaCTSEta7TeV->Draw();
	DrawGammaSetMarkerTGraph(graphInvCrossSectionSysEta , 20, 0.5, colorCommonSpectrumPi07TeV, colorCommonSpectrumPi07TeV);
	graphInvCrossSectionSysEta->SetFillStyle(1001);
	graphInvCrossSectionSysEta->SetFillColor(colorCommonSpectrumPi07TeVBox);
	graphInvCrossSectionSysEta->SetLineColor(colorCommonSpectrumPi07TeVBox);
	graphInvCrossSectionSysEta->Draw("same,e2,p");

	graphInvCrossSectionSysEta2760GeV = ScaleGraph(graphInvCrossSectionSysEta2760GeV,1e-1);
	DrawGammaSetMarkerTGraph(graphInvCrossSectionSysEta2760GeV , 20, 0.5, colorCommonSpectrumPi02760GeV, colorCommonSpectrumPi02760GeV);
	graphInvCrossSectionSysEta2760GeV->SetFillStyle(1001);
	graphInvCrossSectionSysEta2760GeV->SetFillColor(colorCommonSpectrumPi02760GeVBox);
	graphInvCrossSectionSysEta2760GeV->SetLineColor(colorCommonSpectrumPi02760GeVBox);
	graphInvCrossSectionSysEta2760GeV->Draw("same,e2,p");
	
	graphInvCrossSectionSysEta900GeV = ScaleGraph(graphInvCrossSectionSysEta900GeV,1e-2);
	DrawGammaSetMarkerTGraph(graphInvCrossSectionSysEta900GeV , 20, 0.5, colorCommonSpectrumPi0900GeV, colorCommonSpectrumPi0900GeV);
	graphInvCrossSectionSysEta900GeV->SetFillStyle(1001);
	graphInvCrossSectionSysEta900GeV->SetFillColor(colorCommonSpectrumPi0900GeVBox);
	graphInvCrossSectionSysEta900GeV->SetLineColor(colorCommonSpectrumPi0900GeVBox);
	graphInvCrossSectionSysEta900GeV->Draw("same,e2,p");
	
	DrawGammaSetMarker(histoInvCrossSectionEta , 20, 1., colorCommonSpectrumPi07TeV, colorCommonSpectrumPi07TeV);
	histoInvCrossSectionEta->Draw("same,e1,x0,p");
	histoInvCrossSectionEta2760GeV->Scale(1e-1);
	DrawGammaSetMarker(histoInvCrossSectionEta2760GeV , 20, 1., colorCommonSpectrumPi02760GeV, colorCommonSpectrumPi02760GeV);
	histoInvCrossSectionEta2760GeV->Draw("same,e1,x0,p");
	histoInvCrossSectionEta900GeV->Scale(1e-2);
	DrawGammaSetMarker(histoInvCrossSectionEta900GeV , 20, 1., colorCommonSpectrumPi0900GeV, colorCommonSpectrumPi0900GeV);
	histoInvCrossSectionEta900GeV->Draw("same,e1,x0,p");
	
	histo2DInvXSectionEtaOnlyConvAllEnergies->DrawCopy("same");  

 	labelScalingEta7TeVAllEnergiesOnlyCTS->Draw();
	labelScalingEta2760GeVAllEnergiesOnlyCTS->Draw();
	labelScalingEta900GeVAllEnergiesOnlyCTS->Draw();

	
/*	DrawBinShiftingText(binshiftingRightMiddle[0], binshiftingRightMiddle[1], binshiftingRightMiddle[2]);*/
	DrawNormalizationErrorText(normalizationInvXCTSALLEn[0],normalizationInvXCTSALLEn[1],normalizationInvXCTSALLEn[2],
						  normalizationInvXCTSALLEn[3],normalizationInvXCTSALLEn[4],"all"); 

	TLegend* legendConvAllEta = new TLegend(0.15,0.3,0.4,0.4);
	legendConvAllEta->SetTextSize(0.028);			
	legendConvAllEta->SetFillColor(0);
	legendConvAllEta->SetBorderSize(0);
	legendConvAllEta->AddEntry(histoInvCrossSectionEta,Form("PCM  #sqrt{#it{s}} = 7 TeV"),"p");
	legendConvAllEta->AddEntry(histoInvCrossSectionEta2760GeV,Form("PCM  #sqrt{#it{s}} = 2.76 TeV"),"p");
	legendConvAllEta->AddEntry(histoInvCrossSectionEta900GeV,Form("PCM  #sqrt{#it{s}} = 0.9 TeV"),"p");
	legendConvAllEta->Draw();

	
	if(!thesis)DrawAliceLogoPi0Preliminary(pictDrawingCoordinatesInvX[0]-0.1, pictDrawingCoordinatesInvX[1], pictDrawingCoordinatesInvX[2], pictDrawingCoordinatesInvX[3], pictDrawingCoordinatesInvX[4], pictDrawingCoordinatesInvX[5], pictDrawingCoordinatesInvX[6], pictDrawingCoordinatesInvX[7], pictDrawingCoordinates[8],collisionSystemCombinedReallyAll, pictDrawingOptions[1], pictDrawingOptions[2], kFALSE,1200,900);
	canvasInvXSectionEtaConvOnlyAllEnergies->Update();	
	canvasInvXSectionEtaConvOnlyAllEnergies->SaveAs(Form("%s/Eta_InvXSectionOnlyCTSAllEnergies.%s",outputDir.Data(),suffix.Data()));



	
	//_____________________________________________________________________________________________________________
	//_________________________________ Canvas Yield Pi0 all 3 energies only Conv _________________________________
	//_____________________________________________________________________________________________________________

	TCanvas* canvasInvYieldPi0ConvOnlyAllEnergies = new TCanvas("canvasInvYieldPi0ConvOnlyAllEnergies","",1200,900);  // gives the page size
	DrawGammaCanvasSettings( canvasInvYieldPi0ConvOnlyAllEnergies, 0.13, 0.02, 0.02, 0.09);
	canvasInvYieldPi0ConvOnlyAllEnergies->SetLogy();
	canvasInvYieldPi0ConvOnlyAllEnergies->SetLogx();
	
	TH2F * histo2DInvYieldPi0OnlyConvAllEnergies = new TH2F("histo2DInvYieldPi0OnlyConvAllEnergies","histo2DInvYieldPi0OnlyConvAllEnergies",1000,0.23,30.,1000,1.e-8,1.e1);
	SetStyleHistoTH2ForGraphs(histo2DInvYieldPi0OnlyConvAllEnergies, "p_{T} (GeV/c)","#frac{1}{2#pi N_{ev.}} #frac{d^{2}N}{p_{t}dp_{t}dy} (c/GeV)", 0.032,0.04, 0.04,0.04, 1,1.55);
	histo2DInvYieldPi0OnlyConvAllEnergies->DrawCopy(); 

	DrawGammaSetMarkerTGraph(graphCorrectedYieldPi0SysErrBinShifted , 20, 0.5, colorCommonSpectrumPi07TeV, colorCommonSpectrumPi07TeV);
	graphCorrectedYieldPi0SysErrBinShifted->SetFillStyle(1001);
	graphCorrectedYieldPi0SysErrBinShifted->SetFillColor(colorCommonSpectrumPi07TeVBox);
	graphCorrectedYieldPi0SysErrBinShifted->SetLineColor(colorCommonSpectrumPi07TeVBox);
	graphCorrectedYieldPi0SysErrBinShifted->Draw("same,e2,p");

	graphCorrectedYieldPi0SysErrBinShifted2760GeV = ScaleGraph(graphCorrectedYieldPi0SysErrBinShifted2760GeV,1.e-1);
	DrawGammaSetMarkerTGraph(graphCorrectedYieldPi0SysErrBinShifted2760GeV , 20, 0.5, colorCommonSpectrumPi02760GeV, colorCommonSpectrumPi02760GeV);
	graphCorrectedYieldPi0SysErrBinShifted2760GeV->SetFillStyle(1001);
	graphCorrectedYieldPi0SysErrBinShifted2760GeV->SetFillColor(colorCommonSpectrumPi02760GeVBox);
	graphCorrectedYieldPi0SysErrBinShifted2760GeV->SetLineColor(colorCommonSpectrumPi02760GeVBox);
	graphCorrectedYieldPi0SysErrBinShifted2760GeV->Draw("same,e2,p");

	graphCorrectedYieldPi0SysErrBinShifted900GeV = ScaleGraph(graphCorrectedYieldPi0SysErrBinShifted900GeV,1.e-2);
	DrawGammaSetMarkerTGraph(graphCorrectedYieldPi0SysErrBinShifted900GeV , 20, 0.5, colorCommonSpectrumPi0900GeV, colorCommonSpectrumPi0900GeV);
	graphCorrectedYieldPi0SysErrBinShifted900GeV->SetFillStyle(1001);
	graphCorrectedYieldPi0SysErrBinShifted900GeV->SetFillColor(colorCommonSpectrumPi0900GeVBox);
	graphCorrectedYieldPi0SysErrBinShifted900GeV->SetLineColor(colorCommonSpectrumPi0900GeVBox);
	graphCorrectedYieldPi0SysErrBinShifted900GeV->Draw("same,e2,p");
	
	DrawGammaSetMarker(histoPi0CorrYieldBinShifted , 20, 1., colorCommonSpectrumPi07TeV, colorCommonSpectrumPi07TeV);
	histoPi0CorrYieldBinShifted->Draw("same,e1,x0,p");
	histoPi0CorrYieldBinShifted2760GeV->Scale(1.e-1);
	DrawGammaSetMarker(histoPi0CorrYieldBinShifted2760GeV , 20, 1., colorCommonSpectrumPi02760GeV, colorCommonSpectrumPi02760GeV);
	histoPi0CorrYieldBinShifted2760GeV->Draw("same,e1,x0,p");
	histoPi0CorrYieldBinShifted900GeV->Scale(1.e-2);
	DrawGammaSetMarker(histoPi0CorrYieldBinShifted900GeV , 20, 1., colorCommonSpectrumPi0900GeV, colorCommonSpectrumPi0900GeV);
	histoPi0CorrYieldBinShifted900GeV->Draw("same,e1,x0,p");
	
	histo2DInvYieldPi0OnlyConvAllEnergies->DrawCopy("same");  



	TLatex *labelScalingPi07TeVAllEnergiesOnlyCTS_Yield = new TLatex(0.31,3.,"x 1");
	SetStyleTLatex( labelScalingPi07TeVAllEnergiesOnlyCTS_Yield, 0.028,4,colorCommonSpectrumPi07TeV ,kFALSE);
	labelScalingPi07TeVAllEnergiesOnlyCTS_Yield->Draw();

	TLatex *labelScalingPi02760GeVAllEnergiesOnlyCTS_Yield = new TLatex(0.31,0.1,"x 10^{-1}");
	SetStyleTLatex( labelScalingPi02760GeVAllEnergiesOnlyCTS_Yield, 0.028,4,colorCommonSpectrumPi02760GeV ,kFALSE);
	labelScalingPi02760GeVAllEnergiesOnlyCTS_Yield->Draw();

	TLatex *labelScalingPi0900GeVAllEnergiesOnlyCTS_Yield = new TLatex(0.31,0.002,"x 10^{-2}");
	SetStyleTLatex( labelScalingPi0900GeVAllEnergiesOnlyCTS_Yield, 0.028,4,colorCommonSpectrumPi0900GeV ,kFALSE);
	labelScalingPi0900GeVAllEnergiesOnlyCTS_Yield->Draw();



	TLegend* legendConvAllPi01 = new TLegend(0.15,0.24,0.4,0.34);
	legendConvAllPi01->SetTextSize(0.028);			
	legendConvAllPi01->SetFillColor(0);
	legendConvAllPi01->SetBorderSize(0);
	legendConvAllPi01->AddEntry(histoPi0CorrYieldBinShifted,Form("PCM  #sqrt{#it{s}} = 7 TeV"),"p");
	legendConvAllPi01->AddEntry(histoPi0CorrYieldBinShifted2760GeV,Form("PCM  #sqrt{#it{s}} = 2.76 TeV"),"p");
	legendConvAllPi01->AddEntry(histoPi0CorrYieldBinShifted900GeV,Form("PCM  #sqrt{#it{s}} = 0.9 TeV"),"p");
	legendConvAllPi01->Draw();

	
	if(!thesis)DrawAliceLogoPi0Preliminary(pictDrawingCoordinatesInvX[0]-0.1, pictDrawingCoordinatesInvX[1], pictDrawingCoordinatesInvX[2], pictDrawingCoordinatesInvX[3], pictDrawingCoordinatesInvX[4], pictDrawingCoordinatesInvX[5], pictDrawingCoordinatesInvX[6], pictDrawingCoordinatesInvX[7], pictDrawingCoordinates[8],collisionSystemCombinedReallyAll, pictDrawingOptions[1], pictDrawingOptions[2], kTRUE,1200,900);

	canvasInvYieldPi0ConvOnlyAllEnergies->Update();	
	canvasInvYieldPi0ConvOnlyAllEnergies->SaveAs(Form("%s/Pi0_InvYieldOnlyCTSAllEnergies.%s",outputDir.Data(),suffix.Data()));
	
	TH1D *histofitPi0Exp7TeV= (TH1D*)fitPi0Exp7TeV->GetHistogram();
	TH1D *histofitPi0Powerlaw7TeV= (TH1D*)fitPi0Powerlaw7TeV->GetHistogram();
	histofitPi0Powerlaw7TeV->SetLineStyle(1);
	histofitPi0Powerlaw7TeV->SetLineColor(colorCommonSpectrumPi07TeV);
	histofitPi0Exp7TeV->SetLineColor(colorCommonSpectrumPi07TeV);
	histofitPi0Exp7TeV->SetLineStyle(7);
	histofitPi0Exp7TeV->Draw("same,l");
	histofitPi0Powerlaw7TeV->Draw("same,l");

	TH1D *histofitPi0Exp2760GeV= (TH1D*)fitPi0Exp2760GeV->GetHistogram();
	TH1D *histofitPi0Powerlaw2760GeV= (TH1D*)fitPi0Powerlaw2760GeV->GetHistogram();
	histofitPi0Powerlaw2760GeV->SetLineStyle(1);
	histofitPi0Powerlaw2760GeV->SetLineColor(colorCommonSpectrumPi02760GeV);
	histofitPi0Exp2760GeV->SetLineColor(colorCommonSpectrumPi02760GeV);
	histofitPi0Exp2760GeV->SetLineStyle(7);
	histofitPi0Exp2760GeV->Scale(1.e-1);
	histofitPi0Powerlaw2760GeV->Scale(1.e-1);
	histofitPi0Exp2760GeV->Draw("same,l");
	histofitPi0Powerlaw2760GeV->Draw("same,l");

	TH1D *histofitPi0Exp900GeV= (TH1D*)fitPi0Exp900GeV->GetHistogram();
	TH1D *histofitPi0Powerlaw900GeV= (TH1D*)fitPi0Powerlaw900GeV->GetHistogram();
	histofitPi0Powerlaw900GeV->SetLineStyle(1);
	histofitPi0Powerlaw900GeV->SetLineColor(colorCommonSpectrumPi0900GeV);
	histofitPi0Exp900GeV->SetLineColor(colorCommonSpectrumPi0900GeV);
	histofitPi0Exp900GeV->SetLineStyle(7);
	histofitPi0Exp900GeV->Scale(1.e-2);
	histofitPi0Powerlaw900GeV->Scale(1.e-2);
	histofitPi0Exp900GeV->Draw("same,l");
	histofitPi0Powerlaw900GeV->Draw("same,l");
	
	canvasInvYieldPi0ConvOnlyAllEnergies->Update();	
	canvasInvYieldPi0ConvOnlyAllEnergies->SaveAs(Form("%s/Pi0_InvYieldOnlyCTSAllEnergies_fit.%s",outputDir.Data(),suffix.Data()));

	//_____________________________________________________________________________________________________________
	//_________________________________ Canvas Yield Eta all 3 energies only Conv _________________________________
	//_____________________________________________________________________________________________________________
	TCanvas* canvasInvYieldEtaConvOnlyAllEnergies = new TCanvas("canvasInvYieldEtaConvOnlyAllEnergies","",1200,900);  // gives the page size
	DrawGammaCanvasSettings( canvasInvYieldEtaConvOnlyAllEnergies, 0.13, 0.02, 0.02, 0.09);
	canvasInvYieldEtaConvOnlyAllEnergies->SetLogy();
	canvasInvYieldEtaConvOnlyAllEnergies->SetLogx();

	TH2F * histo2DInvYieldEtaOnlyConvAllEnergies = new TH2F("histo2DInvYieldEtaOnlyConvAllEnergies","histo2DInvYieldEtaOnlyConvAllEnergies",1000,0.23,10.,1000,1.e-8,1.e0);
	
	SetStyleHistoTH2ForGraphs(histo2DInvYieldEtaOnlyConvAllEnergies, "p_{T} (GeV/c)","#frac{1}{2#pi N_{ev.}} #frac{d^{2}N}{p_{t}dp_{t}dy} (c/GeV)", 0.032,0.04, 0.04,0.04, 1,1.55);
	histo2DInvYieldEtaOnlyConvAllEnergies->DrawCopy(); 
	
	DrawGammaSetMarkerTGraph(graphCorrectedYieldEtaSysErrBinShifted, 20, 0.5, colorCommonSpectrumPi07TeV, colorCommonSpectrumPi07TeV);

	graphCorrectedYieldEtaSysErrBinShifted->SetFillStyle(1001);
	graphCorrectedYieldEtaSysErrBinShifted->SetFillColor(colorCommonSpectrumPi07TeVBox);
	graphCorrectedYieldEtaSysErrBinShifted->SetLineColor(colorCommonSpectrumPi07TeVBox);
	graphCorrectedYieldEtaSysErrBinShifted->Draw("same,e2,p");

	graphCorrectedYieldEtaSysErrBinShifted2760GeV = ScaleGraph(graphCorrectedYieldEtaSysErrBinShifted2760GeV,1.e-1);
	DrawGammaSetMarkerTGraph(graphCorrectedYieldEtaSysErrBinShifted2760GeV , 20, 0.5, colorCommonSpectrumPi02760GeV, colorCommonSpectrumPi02760GeV);
	graphCorrectedYieldEtaSysErrBinShifted2760GeV->SetFillStyle(1001);
	graphCorrectedYieldEtaSysErrBinShifted2760GeV->SetFillColor(colorCommonSpectrumPi02760GeVBox);
	graphCorrectedYieldEtaSysErrBinShifted2760GeV->SetLineColor(colorCommonSpectrumPi02760GeVBox);
	graphCorrectedYieldEtaSysErrBinShifted2760GeV->Draw("same,e2,p");

	graphCorrectedYieldEtaSysErrBinShifted900GeV = ScaleGraph(graphCorrectedYieldEtaSysErrBinShifted900GeV,1.e-2);
	DrawGammaSetMarkerTGraph(graphCorrectedYieldEtaSysErrBinShifted900GeV , 20, 0.5, colorCommonSpectrumPi0900GeV, colorCommonSpectrumPi0900GeV);
	graphCorrectedYieldEtaSysErrBinShifted900GeV->SetFillStyle(1001);
	graphCorrectedYieldEtaSysErrBinShifted900GeV->SetFillColor(colorCommonSpectrumPi0900GeVBox);
	graphCorrectedYieldEtaSysErrBinShifted900GeV->SetLineColor(colorCommonSpectrumPi0900GeVBox);
	graphCorrectedYieldEtaSysErrBinShifted900GeV->Draw("same,e2,p");
	
	DrawGammaSetMarker(histoEtaCorrYieldBinShifted , 20, 1., colorCommonSpectrumPi07TeV, colorCommonSpectrumPi07TeV);
	histoEtaCorrYieldBinShifted->Draw("same,e1,x0,p");
	histoEtaCorrYieldBinShifted2760GeV->Scale(1.e-1);
	DrawGammaSetMarker(histoEtaCorrYieldBinShifted2760GeV , 20, 1., colorCommonSpectrumPi02760GeV, colorCommonSpectrumPi02760GeV);
	histoEtaCorrYieldBinShifted2760GeV->Draw("same,e1,x0,p");
	histoEtaCorrYieldBinShifted900GeV->Scale(1.e-2);
	DrawGammaSetMarker(histoEtaCorrYieldBinShifted900GeV , 20, 1., colorCommonSpectrumPi0900GeV, colorCommonSpectrumPi0900GeV);
	histoEtaCorrYieldBinShifted900GeV->Draw("same,e1,x0,p");
	
	histo2DInvYieldEtaOnlyConvAllEnergies->DrawCopy("same");  

	TLatex *labelScalingEta7TeVAllEnergiesOnlyCTS_Yield = new TLatex(0.3,5.0e-2,"x 1");
	SetStyleTLatex( labelScalingEta7TeVAllEnergiesOnlyCTS_Yield, 0.028,4,colorCommonSpectrumPi07TeV ,kFALSE);
	labelScalingEta7TeVAllEnergiesOnlyCTS_Yield->Draw();

	TLatex *labelScalingEta2760GeVAllEnergiesOnlyCTS_Yield = new TLatex(0.4,2.5e-3,"x 10^{-1}");
	SetStyleTLatex( labelScalingEta2760GeVAllEnergiesOnlyCTS_Yield, 0.028,4,colorCommonSpectrumPi02760GeV ,kFALSE);
	labelScalingEta2760GeVAllEnergiesOnlyCTS_Yield->Draw();

	TLatex *labelScalingEta900GeVAllEnergiesOnlyCTS_Yield = new TLatex(0.5,4.1e-5,"x 10^{-2}");
	SetStyleTLatex( labelScalingEta900GeVAllEnergiesOnlyCTS_Yield, 0.028,4,colorCommonSpectrumPi0900GeV ,kFALSE);
	labelScalingEta900GeVAllEnergiesOnlyCTS_Yield->Draw();
	
	TLegend* legendConvAllEta1 = new TLegend(0.15,0.24,0.4,0.34);
	legendConvAllEta1->SetTextSize(0.028);			
	legendConvAllEta1->SetFillColor(0);
	legendConvAllEta1->SetBorderSize(0);
	legendConvAllEta1->AddEntry(histoEtaCorrYieldBinShifted,Form("PCM  #sqrt{#it{s}} = 7 TeV"),"p");
	legendConvAllEta1->AddEntry(histoEtaCorrYieldBinShifted2760GeV,Form("PCM  #sqrt{#it{s}} = 2.76 TeV"),"p");
	legendConvAllEta1->AddEntry(histoEtaCorrYieldBinShifted900GeV,Form("PCM  #sqrt{#it{s}} = 0.9 TeV"),"p");
	legendConvAllEta1->Draw();

	if(!thesis)DrawAliceLogoPi0Preliminary(pictDrawingCoordinatesInvX[0]-0.1, pictDrawingCoordinatesInvX[1], pictDrawingCoordinatesInvX[2], pictDrawingCoordinatesInvX[3], pictDrawingCoordinatesInvX[4], pictDrawingCoordinatesInvX[5], pictDrawingCoordinatesInvX[6], pictDrawingCoordinatesInvX[7], pictDrawingCoordinates[8],collisionSystemCombinedReallyAll, pictDrawingOptions[1], pictDrawingOptions[2], kTRUE,1200,900);


	canvasInvYieldEtaConvOnlyAllEnergies->Update();	
	canvasInvYieldEtaConvOnlyAllEnergies->SaveAs(Form("%s/Eta_InvYieldOnlyCTSAllEnergies.%s",outputDir.Data(),suffix.Data()));	

	TH1D *histofitEtaPowerlaw7TeV= (TH1D*)fitEtaPowerlaw7TeV->GetHistogram();
	//histofitEtaPowerlaw7TeV->GetXaxis()->SetRangeUser(5.0,10.);
	histofitEtaPowerlaw7TeV->SetLineStyle(1);
	histofitEtaPowerlaw7TeV->SetLineColor(colorCommonSpectrumPi07TeV);
	histofitEtaPowerlaw7TeV->Draw("same,l");

	TH1D *histofitEtaPowerlaw2760GeV= (TH1D*)fitEtaPowerlaw2760GeV->GetHistogram();
	histofitEtaPowerlaw2760GeV->SetLineStyle(1);
	histofitEtaPowerlaw2760GeV->SetLineColor(colorCommonSpectrumPi02760GeV);
	histofitEtaPowerlaw2760GeV->Scale(1.e-1);
	histofitEtaPowerlaw2760GeV->Draw("same,l");

	canvasInvYieldEtaConvOnlyAllEnergies->Update();	
	canvasInvYieldEtaConvOnlyAllEnergies->SaveAs(Form("%s/Eta_InvYieldOnlyCTSAllEnergies_fit.%s",outputDir.Data(),suffix.Data()));

	
	//*******************************************************************************************************
	//************************************* Inv XSection Only CTS *******************************************
	//*******************************************************************************************************
	
		// **************************  CalculateMeanPt for conversion   *************************************************
 
  
	Float_t mean_Pi0_7TeV, mean_Pi0_7TeV_err;
	CalculateMeanPtWithError(fitLevyConvStatErrPi07TeV,mean_Pi0_7TeV,mean_Pi0_7TeV_err);

	Float_t mean_Pi0_2760GeV,mean_Pi0_2760GeV_err;
	CalculateMeanPtWithError(fitLevyConvStatErrPi02760GeV, mean_Pi0_2760GeV, mean_Pi0_2760GeV_err );

	Float_t mean_Pi0_900GeV,mean_Pi0_900GeV_err;
	CalculateMeanPtWithError(fitLevyConvStatErrPi0900GeV, mean_Pi0_900GeV, mean_Pi0_900GeV_err);

	Float_t mean_Eta_7TeV, mean_Eta_7TeV_err;
	CalculateMeanPtWithError(fitLevyConvStatErrEta7TeV, mean_Eta_7TeV, mean_Eta_7TeV_err);

	Float_t mean_Eta_2760GeV, mean_Eta_2760GeV_err;
	  CalculateMeanPtWithError(fitLevyConvStatErrEta2760GeV,mean_Eta_2760GeV,mean_Eta_2760GeV_err);



	// **************************  end CalculateMeanPt for conversion   *************************************************

	
	//______________________________ mean pT plot ___________________________________________________
	cout << "\n\nMean calculations  " << endl;
	cout << " pi0 7 TeV   " << mean_Pi0_7TeV << "   " << mean_Pi0_7TeV_err <<endl;
	cout << " pi0 2.76 TeV   " << mean_Pi0_2760GeV << "   " << mean_Pi0_2760GeV_err << endl;
	cout << " pi0 900 GeV   " << mean_Pi0_900GeV << "   " << mean_Pi0_900GeV_err << endl;
	cout << " eta 7 TeV   " << mean_Eta_7TeV << "   " << mean_Eta_7TeV_err << endl;
	cout << " eta 2760 TeV   " << mean_Eta_2760GeV << "   " << mean_Eta_2760GeV_err << endl;
	//cout << "\n\n eta 900 TeV   " << mean_Eta_900GeV << endl;

	
	TCanvas* canvasMeanPtPi0 = new TCanvas("canvasMeanPtPi0","",1200,900);  // gives the page size
	DrawGammaCanvasSettings( canvasMeanPtPi0, 0.13, 0.02, 0.02, 0.09);

	
	TH2F *histo2DMeanPtPi0 = new TH2F("histo2DMeanPtPi0","histo2DMeanPtPi0",1000,0.,10.,100,0.,1.);
	SetStyleHistoTH2ForGraphs(histo2DMeanPtPi0, "#sqrt{#it{s}} (TeV)","<p_{t}> (GeV/c )", 0.032,0.04, 0.04,0.04, 1,1.55);
	histo2DMeanPtPi0->GetXaxis()->SetLabelSize(0.04);
	histo2DMeanPtPi0->DrawCopy(); 



	Float_t sqrtPi0x[]={0.9,2.76,7.};
	Float_t sqrtPi0x_err[]={0.,0.,0.};

	Float_t meanPi0y[]={mean_Pi0_900GeV,mean_Pi0_2760GeV,mean_Pi0_7TeV};
	Float_t meanPi0y_err[]={mean_Pi0_900GeV_err,mean_Pi0_2760GeV_err,mean_Pi0_7TeV_err};

	Float_t sqrtEtax[]={2.76,7.};
	Float_t sqrtEtax_err[]={0.,0.};

	Float_t meanEtay[]={mean_Eta_2760GeV,mean_Eta_7TeV};
	Float_t meanEtay_err[]={mean_Eta_2760GeV_err,mean_Eta_7TeV_err};


	TGraphErrors *meanPi0 = new TGraphErrors(3,sqrtPi0x,meanPi0y,sqrtPi0x_err,meanPi0y_err);
	TGraphErrors *meanEta = new TGraphErrors(2,sqrtEtax,meanEtay,sqrtEtax_err,meanEtay_err);
	
	meanPi0->Print();
	meanEta->Print();

	TF1 *fit_Pi0 = new TF1("fit_Pi0","[0]*x+[1] ",0.9,7.0); 
	fit_Pi0->SetParNames("a","b");
	meanPi0->Fit("fit_Pi0","RME");

	Float_t a= fit_Pi0->GetParameter(0);
	Float_t b= fit_Pi0->GetParameter(1);

	TLatex *text = new TLatex(0.4,0.3,"Linear fit, incl. stat. uncertainties");
	text->SetNDC();
	text->SetTextSize(0.04);
	text->SetTextColor(kBlack);
	text->Draw("same");

	TLatex *text_pi0 = new TLatex(0.67,0.25,Form("#pi^{0}: %3.2f #times #sqrt{#it{s}} + %3.2f",a,b));
	text_pi0->SetNDC();
	text_pi0->SetTextSize(0.04);
	text_pi0->SetTextColor(kBlack);
	text_pi0->Draw("same");


	TF1 *fit_Eta = new TF1("fit_Eta","[0]*x+[1] ",2.76,7.0); 
	fit_Eta->SetLineColor(kRed);
	fit_Eta->SetParNames("a","b");
	meanEta->Fit("fit_Eta","RME");

	a= fit_Eta->GetParameter(0);
	b= fit_Eta->GetParameter(1);
	
	TLatex *text_Eta = new TLatex(0.67,0.2,Form(" #eta: %3.2f #times #sqrt{#it{s}} + %3.2f",a,b));
	text_Eta->SetNDC();
	text_Eta->SetTextSize(0.04);
	text_Eta->SetTextColor(kRed);
	text_Eta->Draw("same");
		
	DrawGammaSetMarkerTGraphErr(meanPi0, 20,1.5, 1, 1);
	DrawGammaSetMarkerTGraphErr(meanEta, 21,1.5, 2, 2);
 	meanPi0->Draw("same,p,e");
	meanEta->Draw("same,p,e");

	TLegend* legendMean = new TLegend(0.23,0.15,0.28,0.27);
	legendMean->SetTextSize(0.04);			
	legendMean->SetFillColor(0);
	legendMean->SetBorderSize(0);
	legendMean->AddEntry(meanPi0,Form("      #pi^{0}"),"p");
	legendMean->AddEntry(meanEta,Form("      #eta"),"p");
	legendMean->Draw();

	canvasMeanPtPi0->Update();
	canvasMeanPtPi0->SaveAs(Form("%s/MeanPt.%s",outputDir.Data(),suffix.Data()));
	

	//_______________________________ mt scaling 7TeV ______________________________________
	TF1 *fit_Pi0_7000 = new TF1("fit_Pi0_7000","[0] * pow(x + [1],-[2]) ",0.45,14.); // kr
	fit_Pi0_7000->SetParNames("C_Pi0","a","n");

	fit_Pi0_7000->SetParameter(0, 6.5);
	fit_Pi0_7000->SetParameter(1, 0.84);
	fit_Pi0_7000->SetParameter(2, 6.85);	
 	histoPi0CorrYieldMtBinShifted->Fit("fit_Pi0_7000","RME0");

	fit_Pi0_7000->SetLineColor(2);
	fit_Pi0_7000->SetLineWidth(0.7);
	fit_Pi0_7000->Draw("same");
	Double_t fit_Pi0_7000_parameter[3];
	fit_Pi0_7000->GetParameters(fit_Pi0_7000_parameter);


	TF1 *fit_Pi0_2760 = new TF1("fit_Pi0_2760","[0] * pow(x + [1],-[2]) ",0.45,14.); // kr
	fit_Pi0_2760->SetParNames("C_Pi0","a","n");

	fit_Pi0_2760->SetParameter(0, 6.5);
	fit_Pi0_2760->SetParameter(1, 0.84);
	fit_Pi0_2760->SetParameter(2, 6.85);	
 	histoPi0CorrYieldMtBinShifted2760GeV->Fit("fit_Pi0_2760","RME0");
	fit_Pi0_2760->SetLineColor(2);
	fit_Pi0_2760->SetLineWidth(0.7);
	fit_Pi0_2760->Draw("same");
	Double_t fit_Pi0_2760_parameter[3];
	fit_Pi0_2760->GetParameters(fit_Pi0_2760_parameter);



	TH1D* Eta_Ratio_7000 = (TH1D*)   histoEtaCorrYieldMtBinShifted->Clone();
	Eta_Ratio_7000->SetYTitle("#eta / (#pi^{0} fit)");
	Eta_Ratio_7000->Divide(fit_Pi0_7000);
	Eta_Ratio_7000->GetXaxis()->SetRangeUser(0.,8.);
	Eta_Ratio_7000->GetYaxis()->SetRangeUser(0.,0.8);

	// graph --> asymmetric systematic errors
	TGraphAsymmErrors* graph_Eta_Ratio_SysErr_7000 = (TGraphAsymmErrors*)graphCorrectedYieldEtaSysErrMtBinShifted->Clone();

	for (int i=0; i<graph_Eta_Ratio_SysErr_7000->GetN(); i++) {
    Double_t mt = graph_Eta_Ratio_SysErr_7000->GetX()[i];
    graph_Eta_Ratio_SysErr_7000->GetY()[i] = graph_Eta_Ratio_SysErr_7000->GetY()[i] / fit_Pi0_7000->Eval(mt);
    graph_Eta_Ratio_SysErr_7000->GetEYhigh()[i] = graph_Eta_Ratio_SysErr_7000->GetEYhigh()[i] / fit_Pi0_7000->Eval(mt);
    graph_Eta_Ratio_SysErr_7000->GetEYlow()[i] = graph_Eta_Ratio_SysErr_7000->GetEYlow()[i] / fit_Pi0_7000->Eval(mt);
  }
  


	TH1D* Eta_Ratio_2760 = (TH1D*)   histoEtaCorrYieldMtBinShifted2760GeV->Clone();
	Eta_Ratio_2760->Divide(fit_Pi0_2760);

	// graph --> asymmetric systematic errors
	TGraphAsymmErrors* graph_Eta_Ratio_SysErr_2760 = (TGraphAsymmErrors*)graphCorrectedYieldEtaSysErrMtBinShifted2760GeV->Clone();

	for (int i=0; i<graph_Eta_Ratio_SysErr_2760->GetN(); i++) {
    Double_t mt = graph_Eta_Ratio_SysErr_2760->GetX()[i];
    graph_Eta_Ratio_SysErr_2760->GetY()[i] = graph_Eta_Ratio_SysErr_2760->GetY()[i] / fit_Pi0_2760->Eval(mt);
    graph_Eta_Ratio_SysErr_2760->GetEYhigh()[i] = graph_Eta_Ratio_SysErr_2760->GetEYhigh()[i] / fit_Pi0_2760->Eval(mt);
    graph_Eta_Ratio_SysErr_2760->GetEYlow()[i] = graph_Eta_Ratio_SysErr_2760->GetEYlow()[i] / fit_Pi0_2760->Eval(mt);
  }
  

  // --------eta ratio ------------------------------------
	TCanvas* c_eta_ratio = new TCanvas("c_eta_ratio");
	c_eta_ratio->cd();

	DrawGammaSetMarker(Eta_Ratio_7000, 20,1.5, 1, 1);

	//----- eta sys ration 7000 GeV --------------------
	graph_Eta_Ratio_SysErr_7000->SetMarkerColor(kBlack);
	graph_Eta_Ratio_SysErr_7000->SetFillColor(kBlue-8);
	graph_Eta_Ratio_SysErr_7000->SetFillStyle(1001);
	graph_Eta_Ratio_SysErr_7000->SetMarkerStyle(20);

	Eta_Ratio_7000->Draw("EX0");
	graph_Eta_Ratio_SysErr_7000->Draw("p,E2");  
	Eta_Ratio_7000->Draw("EX0,same");
	

	//----- eta sys ration 2760 GeV --------------------
	DrawGammaSetMarker(Eta_Ratio_7000, 21,1.5, 1, 1);
		
	graph_Eta_Ratio_SysErr_2760->SetMarkerColor(kBlack);
	graph_Eta_Ratio_SysErr_2760->SetFillColor(kMagenta-9);
	graph_Eta_Ratio_SysErr_2760->SetFillStyle(1001);
	graph_Eta_Ratio_SysErr_2760->SetMarkerStyle(21);

	Eta_Ratio_2760->Draw("same,EX0");
	graph_Eta_Ratio_SysErr_2760->Draw("p,E2");  
	Eta_Ratio_2760->Draw("EX0,same");
	

	TLegend *legend_noBS = new TLegend(0.4,0.15,0.85,0.3);
	legend_noBS->SetTextSize(0.035);			
	legend_noBS->SetFillColor(0);
	legend_noBS->SetLineColor(0);
	legend_noBS->AddEntry(  graph_Eta_Ratio_SysErr_2760,"#sqrt{#it{s}}=2.76TeV") ;
	legend_noBS->AddEntry(  graph_Eta_Ratio_SysErr_7000,"#sqrt{#it{s}}=7TeV") ;
	legend_noBS->Draw("same");


	c_eta_ratio->SaveAs(Form("%s/%s_mt.%s",outputDir.Data(), prefix2.Data(), suffix.Data()));
	
	
		//**************************************************************************************************************************************
	//************************************ Inv Crosssection only ratio ***************************************************************
	//**************************************************************************************************************************************
	
	TCanvas* canvasInvXSectionOnlyRatio = new TCanvas("canvasInvXSectionOnlyRatio","",200,10,1200,1200);  // gives the page size
	DrawGammaCanvasSettings( canvasInvXSectionOnlyRatio,  0.15, 0.02, 0.03, 0.06);
	
	TPad* padXSectionLegendOnlyRatio = new TPad("padXSectionLegendOnlyRatio", "",  0.17, 0.8, 0.95, 1.,-1, -1, -2);
	DrawGammaPadSettings( padXSectionLegendOnlyRatio, 0.15, 0.02, 0.03, 0.);
	padXSectionLegendOnlyRatio->Draw();
	
	TPad* padXSectionOnlyRatioPi07TeV = new TPad("padXSectionOnlyRatioPi07TeV", "", 0., 0.565, 1., 0.8,-1, -1, -2);
	DrawGammaPadSettings( padXSectionOnlyRatioPi07TeV, 0.15, 0.02, 0., 0.);
	padXSectionOnlyRatioPi07TeV->Draw();
	
	TPad* padXSectionOnlyRatioPi0900GeV = new TPad("padXSectionOnlyRatioPi0900GeV", "", 0., 0.33, 1., 0.565,-1, -1, -2);
	DrawGammaPadSettings( padXSectionOnlyRatioPi0900GeV, 0.15, 0.02, 0., 0.);
	padXSectionOnlyRatioPi0900GeV->Draw();
	
	TPad* padXSectionOnlyRatioEta7TeV = new TPad("padXSectionOnlyRatioEta7TeV", "", 0., 0., 1., 0.33,-1, -1, -2);
	DrawGammaPadSettings( padXSectionOnlyRatioEta7TeV, 0.15, 0.02, 0., 0.28);
	padXSectionOnlyRatioEta7TeV->Draw();
	
	padXSectionOnlyRatioPi07TeV->cd();
	padXSectionOnlyRatioPi07TeV->SetLogx();
	
		ratio2DInvXSectionPi0->DrawCopy(); 
//		graphRatioCombPHOSPi0Sys->Draw("same,p");
		graphRatioCombPHOSPi0Sys->Draw("E2same");
//		graphRatioCombConvPi0Sys->Draw("p,same");
		graphRatioCombConvPi0Sys->Draw("E2same");
// 		histoRatioCombEMCALPi0->Draw("same,e1");
		graphRatioCombPHOSPi0->Draw("p,same,e1");
		graphRatioCombConvPi0->Draw("p,same,e1");
		boxErrorSigmaPi07TeVRatio->Draw();
		labelRatioNLOPi07TeV->Draw();
		DrawGammaLines(0., 30.,1., 1.,0.1);
		
	padXSectionOnlyRatioPi0900GeV->cd();
	padXSectionOnlyRatioPi0900GeV->SetLogx();
	
		ratio2DInvXSectionPi0900GeV->DrawCopy(); 	
//		graphRatioCombPHOSPi0900GeVSys->Draw("same,p");
		graphRatioCombPHOSPi0900GeVSys->Draw("E2same");
//		graphRatioCombConvPi0900GeVSys->Draw("same,p");
		graphRatioCombConvPi0900GeVSys->Draw("E2same");
		graphRatioCombConvPi0900GeV->Draw("p,same,e1");
		graphRatioCombPHOSPi0900GeV->Draw("p,same,e1");
		boxErrorSigmaPi0900GeVRatio->Draw();
		labelRatioNLOPi0900GeV->Draw();
		DrawGammaLines(0., 30.,1., 1.,0.1);
		
	padXSectionOnlyRatioEta7TeV->cd();
	padXSectionOnlyRatioEta7TeV->SetLogx();
	
		ratio2DInvXSectionEta->DrawCopy(); 
//		graphRatioCombPHOSEta7TeVSys->Draw("same,p");
		graphRatioCombPHOSEta7TeVSys->Draw("E2same");
//		graphRatioCombConvEta7TeVSys->Draw("p,same");
		graphRatioCombConvEta7TeVSys->Draw("E2same");
		graphRatioCombPHOSEta7TeV->Draw("p,same,e1");
		graphRatioCombConvEta7TeV->Draw("p,same,e1");
//		graphRatioCombEMCALEta7TeV->Draw("same,ep");
		boxErrorSigmaEta7TeVRatio->Draw();
		labelRatioNLOEta7TeV->Draw();
		DrawGammaLines(0., 30.,1., 1.,0.1);
		
	padXSectionLegendOnlyRatio->cd();
	DrawGammaPadSettings( padXSectionLegendOnlyRatio, 0., 0., 0., 0.);
	padXSectionLegendOnlyRatio->SetBorderMode(-1);
	padXSectionLegendOnlyRatio->SetBorderSize(3);
	padXSectionLegendOnlyRatio->Draw();
	padXSectionLegendOnlyRatio->cd();
	
	//****************************** Definition of the Legend ******************************************
	//**************** Row def ************************
	Double_t rowsLegendOnlyRatio[5] 		= {0.80,0.66,0.38,0.15,0.07}; //with EMCAL {0.88,0.75,0.52,0.3,0.07};
	
	//****************** first Column **************************************************
	TLatex *textCTSOnlyRatio = new TLatex(columnsLegend[0],rowsLegendOnlyRatio[2],"PCM");
	SetStyleTLatex( textCTSOnlyRatio, textSizeLeftColumn,4);
	textCTSOnlyRatio->Draw();
	TLatex *textPHOSOnlyRatio = new TLatex(columnsLegend[0],rowsLegendOnlyRatio[3],"PHOS");
	SetStyleTLatex( textPHOSOnlyRatio, textSizeLeftColumn,4);
	textPHOSOnlyRatio->Draw();
	TLatex *textEMCALOnlyRatio = new TLatex(columnsLegend[0],rowsLegendOnlyRatio[4],"EMCAL");
	SetStyleTLatex( textEMCALOnlyRatio, textSizeLeftColumn,4);
// 	textEMCALOnlyRatio->Draw();
	
	//****************** second Column *************************************************
	TLatex *textPi07TeVOnlyRatio = new TLatex(columnsLegend[1],rowsLegendOnlyRatio[0],"#pi^{0} @ #sqrt{#it{s}} = 7 TeV");
	SetStyleTLatex( textPi07TeVOnlyRatio, textSizeTopRow,4);
	textPi07TeVOnlyRatio->Draw();
	TLatex *textPi07TeVstatOnlyRatio = new TLatex(columnsLegend[1],rowsLegendOnlyRatio[1] ,"stat");
	SetStyleTLatex( textPi07TeVstatOnlyRatio, textSizeSecondRow,4);
	textPi07TeVstatOnlyRatio->Draw();
	TLatex *textPi07TeVsysOnlyRatio = new TLatex(columnsLegend[1]+ offsetSystColumn ,rowsLegendOnlyRatio[1],"syst");
	SetStyleTLatex( textPi07TeVsysOnlyRatio, textSizeSecondRow,4);
	textPi07TeVsysOnlyRatio->Draw();
	TMarker* markerCTSPi07TeVOnlyRatio = CreateMarkerFromGraph(graphConversionXSectionPi07TeV,columnsLegend[1]+ offsetMarkerX ,rowsLegendOnlyRatio[2]+ offsetMarkerY ,scaleWidthLine);
	markerCTSPi07TeVOnlyRatio->DrawMarker(columnsLegend[1]+ offsetMarkerX ,rowsLegendOnlyRatio[2]+ offsetMarkerY);
	TMarker* markerPHOSPi07TeVOnlyRatio = CreateMarkerFromGraph(graphPHOSXSectionPi07TeV, columnsLegend[1]+ offsetMarkerX ,rowsLegendOnlyRatio[3]+ offsetMarkerY ,scaleWidthLine);
	markerPHOSPi07TeVOnlyRatio->DrawMarker(columnsLegend[1]+ offsetMarkerX ,rowsLegendOnlyRatio[3]+ offsetMarkerY );
// 	TMarker* markerEMCALPi07TeVOnlyRatio = CreateMarkerFromHisto(histoInvCrossSectionPi0EMCAL, columnsLegend[1]+ offsetMarkerX ,rowsLegendOnlyRatio[4]+ offsetMarkerY ,scaleWidthLine);
// 	markerEMCALPi07TeVOnlyRatio->DrawMarker(columnsLegend[1]+ offsetMarkerX ,rowsLegendOnlyRatio[4]+ offsetMarkerY );
	TBox* boxCTSPi07TeVOnlyRatio = CreateBoxFromGraph(graphPHOSXSectionPi07TeV,columnsLegend[1]+offsetSystColumn+offsetMarkerX-offsetFit, rowsLegendOnlyRatio[2]+ offsetMarkerY- offsetBoxSizeY, columnsLegend[1]+ offsetSystColumn+ offsetMarkerX+ offsetFit, rowsLegendOnlyRatio[2]+ offsetMarkerY+ offsetBoxSizeY);
	boxCTSPi07TeVOnlyRatio->Draw("l");
	TBox* boxPHOSPi07TeVOnlyRatio = CreateBoxFromGraph(graphPHOSXSectionPi07TeV,columnsLegend[1]+offsetSystColumn+offsetMarkerX-offsetFit, rowsLegendOnlyRatio[3]+ offsetMarkerY- offsetBoxSizeY, columnsLegend[1]+ offsetSystColumn+ offsetMarkerX+ offsetFit, rowsLegendOnlyRatio[3]+ offsetMarkerY+ offsetBoxSizeY);
	boxPHOSPi07TeVOnlyRatio->Draw("l");
/*	TBox* boxEMCALPi07TeVOnlyRatio = CreateBoxFromHisto(histoInvCrossSectionPi0EMCAL,columnsLegend[1]+offsetSystColumn+offsetMarkerX-offsetFit, rowsLegendOnlyRatio[4]+ offsetMarkerY- offsetBoxSizeY, columnsLegend[1]+ offsetSystColumn+ offsetMarkerX+ offsetFit, rowsLegendOnlyRatio[4]+ offsetMarkerY+ offsetBoxSizeY);
	boxEMCALPi07TeVOnlyRatio->Draw("l");*/
	
	//***************** third Column ***************************************************
	TLatex *textPi0900GeVOnlyRatio= new TLatex(columnsLegend[2],rowsLegendOnlyRatio[0],"#pi^{0} @ #sqrt{#it{s}} = 0.9 TeV");
	SetStyleTLatex( textPi0900GeVOnlyRatio, textSizeTopRow,4);
	textPi0900GeVOnlyRatio->Draw();
	TLatex *textPi0900GeVstatOnlyRatio = new TLatex(columnsLegend[2],rowsLegendOnlyRatio[1],"stat");
	SetStyleTLatex( textPi0900GeVstatOnlyRatio, textSizeSecondRow,4);
	textPi0900GeVstatOnlyRatio->Draw();
	TLatex *textPi0900GeVsysOnlyRatio = new TLatex(columnsLegend[2]+ offsetSystColumn,rowsLegendOnlyRatio[1],"syst");
	SetStyleTLatex( textPi0900GeVsysOnlyRatio, textSizeSecondRow,4);
	textPi0900GeVsysOnlyRatio->Draw();
	TMarker* markerCTSPi0900GeVOnlyRatio = CreateMarkerFromGraph(graphConversionXSectionPi0900GeV,columnsLegend[2]+ offsetMarkerX ,rowsLegendOnlyRatio[2]+ offsetMarkerY ,scaleWidthLine);
	markerCTSPi0900GeVOnlyRatio->DrawMarker(columnsLegend[2]+ offsetMarkerX ,rowsLegendOnlyRatio[2]+ offsetMarkerY);
	TMarker* markerPHOSPi0900GeVOnlyRatio = CreateMarkerFromGraph(graphPHOSXSectionPi0900GeV, columnsLegend[2]+ offsetMarkerX ,rowsLegendOnlyRatio[3]+ offsetMarkerY ,scaleWidthLine);
	markerPHOSPi0900GeVOnlyRatio->DrawMarker(columnsLegend[2]+ offsetMarkerX ,rowsLegendOnlyRatio[3]+ offsetMarkerY);
	/*		TMarker* markerEMCALPi0900GeVOnlyRatio = CreateMarkerFromGraph(graphInvCrossSectionPi0EMCAL, columnsLegend[2]+ offsetMarkerX ,rowsLegendOnlyRatio[4]+ offsetMarkerY ,scaleWidthLine);
	markerEMCALPi0900GeVOnlyRatio->DrawMarker(columnsLegend[2]+ offsetMarkerX ,rowsLegendOnlyRatio[4]+ offsetMarkerY);*/
	TBox* boxCTSPi0900GeVOnlyRatio = CreateBoxFromGraph(graphConversionXSectionPi0900GeV,columnsLegend[2]+offsetSystColumn+offsetMarkerX-offsetFit, rowsLegendOnlyRatio[2]+ offsetMarkerY- offsetBoxSizeY, columnsLegend[2]+ offsetSystColumn+ offsetMarkerX+ offsetFit, rowsLegendOnlyRatio[2]+ offsetMarkerY+ offsetBoxSizeY);
	boxCTSPi0900GeVOnlyRatio->Draw("l");		
	TBox* boxPHOSPi0900GeVOnlyRatio = CreateBoxFromGraph(graphPHOSXSectionPi0900GeV,columnsLegend[2]+offsetSystColumn+offsetMarkerX-offsetFit, rowsLegendOnlyRatio[3]+ offsetMarkerY- offsetBoxSizeY, columnsLegend[2]+ offsetSystColumn+ offsetMarkerX+ offsetFit, rowsLegendOnlyRatio[3]+ offsetMarkerY+ offsetBoxSizeY);
	boxPHOSPi0900GeVOnlyRatio->Draw("l");
	// 		TBox* boxEMCALPi0900GeVOnlyRatio =  CreateBoxFromGraph(graphInvCrossSectionPi0EMCAL,columnsLegend[2]+offsetSystColumn+offsetMarkerX-offsetFit, rowsLegendOnlyRatio[4]+ offsetMarkerY- offsetBoxSizeY, columnsLegend[2]+ offsetSystColumn+ offsetMarkerX+ offsetFit, rowsLegendOnlyRatio[4]+ offsetMarkerY+ offsetBoxSizeY);
	// 		boxEMCALPi0900GeVOnlyRatio->Draw("l");
	
	//***************** forth Column ***************************************************
	TLatex *textEta7TeVOnlyRatio = new TLatex(columnsLegend[3],rowsLegendOnlyRatio[0],"#eta @ #sqrt{#it{s}} = 7 TeV");
	SetStyleTLatex( textEta7TeVOnlyRatio, textSizeTopRow,4);
	textEta7TeVOnlyRatio->Draw();
	TLatex *textEta7TeVstatOnlyRatio = new TLatex(columnsLegend[3],rowsLegendOnlyRatio[1],"stat");
	SetStyleTLatex( textEta7TeVstatOnlyRatio, textSizeSecondRow,4);
	textEta7TeVstatOnlyRatio->Draw();
	TLatex *textEta7TeVsysOnlyRatio = new TLatex(columnsLegend[3]+ offsetSystColumn ,rowsLegendOnlyRatio[1],"syst");
	SetStyleTLatex( textEta7TeVsysOnlyRatio, textSizeSecondRow,4);
	textEta7TeVsysOnlyRatio->Draw();
	TMarker* markerCTSEta7TeVOnlyRatio = CreateMarkerFromGraph(graphConversionXSectionEta7TeV,columnsLegend[3]+ offsetMarkerX ,rowsLegendOnlyRatio[2]+ offsetMarkerY ,scaleWidthLine);
	markerCTSEta7TeVOnlyRatio->DrawMarker(columnsLegend[3]+ offsetMarkerX ,rowsLegendOnlyRatio[2]+ offsetMarkerY);
	TMarker* markerPHOSEta7TeVOnlyRatio = CreateMarkerFromGraph(graphPHOSXSectionEta7TeV, columnsLegend[3]+ offsetMarkerX ,rowsLegendOnlyRatio[3]+ offsetMarkerY ,scaleWidthLine);
	markerPHOSEta7TeVOnlyRatio->DrawMarker(columnsLegend[3]+ offsetMarkerX ,rowsLegendOnlyRatio[3]+ offsetMarkerY );
/*	TMarker* markerEMCALEta7TeVOnlyRatio = CreateMarkerFromGraph(graphInvCrossSectionEtaEMCAL, columnsLegend[3]+ offsetMarkerX ,rowsLegendOnlyRatio[4]+ offsetMarkerY ,scaleWidthLine);*/
	//markerEMCALEta7TeVOnlyRatio->DrawMarker(columnsLegend[3]+ offsetMarkerX ,rowsLegendOnlyRatio[4]+ offsetMarkerY);
	TBox* boxCTSEta7TeVOnlyRatio = CreateBoxFromGraph(graphConversionXSectionEta7TeV,columnsLegend[3]+offsetSystColumn+offsetMarkerX-offsetFit, rowsLegendOnlyRatio[2]+ offsetMarkerY- offsetBoxSizeY, columnsLegend[3]+ offsetSystColumn+ offsetMarkerX+ offsetFit, rowsLegendOnlyRatio[2]+ offsetMarkerY+ offsetBoxSizeY);
	boxCTSEta7TeVOnlyRatio->Draw("l");
	TBox* boxPHOSEta7TeVOnlyRatio = CreateBoxFromGraph(graphPHOSXSectionEta7TeV,columnsLegend[3]+offsetSystColumn+offsetMarkerX-offsetFit, rowsLegendOnlyRatio[3]+ offsetMarkerY- offsetBoxSizeY, columnsLegend[3]+ offsetSystColumn+ offsetMarkerX+ offsetFit, rowsLegendOnlyRatio[3]+ offsetMarkerY+ offsetBoxSizeY);
	boxPHOSEta7TeVOnlyRatio->Draw("l");
	/*	TBox* boxEMCALEta7TeVOnlyRatio = CreateBoxFromGraph(graphInvCrossSectionPi0EMCAL,columnsLegend[3]+offsetSystColumn+offsetMarkerX-offsetFit, rowsLegendOnlyRatio[4]+ offsetMarkerY- offsetBoxSizeY, columnsLegend[3]+ offsetSystColumn+ offsetMarkerX+ offsetFit, rowsLegendOnlyRatio[4]+ offsetMarkerY+ offsetBoxSizeY);
	boxEMCALEta7TeVOnlyRatio->Draw("l");*/
	
	
	canvasInvXSectionOnlyRatio->Update();
	canvasInvXSectionOnlyRatio->Print(Form("%s/InvXSection_OnlyRatio_Paper.%s",outputDir.Data(),suffix.Data()));

		//*****************************************************************************************************************
	//************************ Meson Combined + NLO just spectrum Pi0 *************************************************
	//*****************************************************************************************************************

	TCanvas* canvasInvXSectionNLOOnlySpectr = new TCanvas("canvasInvXSectionNLOOnlySpectr","",200,10,1200,1200);  // gives the page size
	DrawGammaCanvasSettings( canvasInvXSectionNLOOnlySpectr,  0.15, 0.02, 0.03, 0.06);
	
	TPad* padComparisonXSectionNLOOnlySpectra = new TPad("padComparisonXSectionNLOOnlySpectra", "", 0., 0., 1., 0.8,-1, -1, -2);
	DrawGammaPadSettings( padComparisonXSectionNLOOnlySpectra, 0.15, 0.02, 0.02, 0.09);
	padComparisonXSectionNLOOnlySpectra->Draw();
	
	TPad* padXSectionNLOLegendOnlySpectra = new TPad("padXSectionNLOLegendOnlySpectra", "",  0.17, 0.8, 0.95, 1.,-1, -1, -2);
	DrawGammaPadSettings( padXSectionNLOLegendOnlySpectra, 0.15, 0.02, 0.03, 0.);
	padXSectionNLOLegendOnlySpectra->Draw();
	
	padComparisonXSectionNLOOnlySpectra->cd();
	padComparisonXSectionNLOOnlySpectra->SetLogy();		
	padComparisonXSectionNLOOnlySpectra->SetLogx();		
	
	//-------------- Plotting ------------------------------------------------------
	TH2F * histo2DInvXSectionNLOOnlySpectra = new TH2F("histo2DInvXSectionNLOOnlySpectra","histo2DInvXSectionNLOOnlySpectra",1000,0.23,30.,1000,2e-1,10e12);
	SetStyleHistoTH2ForGraphs(histo2DInvXSectionNLOOnlySpectra, "p_{t} (GeV/c)","E #frac{d^{3}#sigma}{dp^{3}} (pb GeV^{-2} c^{3} )", 0.032,0.04, 0.04,0.04, 1,1.55);
	histo2DInvXSectionNLOOnlySpectra->DrawCopy(); 
	
	//graphInvCrossSectionPi0Comb900GeV->Draw("same,p");
	graphInvCrossSectionPi0Comb900GeV->Draw("p,E2same");
	
	//graphInvCrossSectionPi0Comb7TeV->Draw("p,same");
	graphInvCrossSectionPi0Comb7TeV->Draw("p,E2same");
	
	//graphInvCrossSectionEtaComb7TeV->Draw("same,p");
	graphInvCrossSectionEtaComb7TeV->Draw("p,E2same");
	
	fitInvCrossSectionPi0->Draw("same");
	
	histoFitInvCrossSectionPi0900GeV->Draw("same,c");
	
	histoFitInvCrossSectionEta7TeV->Draw("same,c");
	
	graphNLOMuHalfPi07TeV->Draw("same,c");
	graphNLOMuOnePi07TeV->Draw("same,c");
	graphNLOMuTwoPi07TeV->Draw("same,c");
	
	graphNLOMuHalfPi0900GeV->Draw("same,c");
	graphNLOMuOnePi0900GeV->Draw("same,c");
	graphNLOMuTwoPi0900GeV->Draw("same,c");
	
	graphNLOMuHalfEta7TeV->Draw("same,c");
	graphNLOMuOneEta7TeV->Draw("same,c");
	graphNLOMuTwoEta7TeV->Draw("same,c");
	
	labelScalingPi07TeV->Draw();
	labelScalingPi0900GeV->Draw();
	labelScalingEta7TeV->Draw();
  
/*	DrawBinShiftingText(0.4,0.23,0.026); */
	DrawNormalizationErrorText(normalizationInvXOnlySpec[0],normalizationInvXOnlySpec[1],normalizationInvXOnlySpec[2],
						  normalizationInvXOnlySpec[3],normalizationInvXOnlySpec[4],"No2.76"); 
	//DrawPrevPrelimPi0(0.48,0.83,0.023);   

	//************************************************* Begin Legend ***************************************************
	
	padXSectionNLOLegendOnlySpectra->cd();
	DrawGammaPadSettings( padXSectionNLOLegendOnlySpectra, 0., 0., 0., 0.);
	padXSectionNLOLegendOnlySpectra->SetBorderMode(-1);
	padXSectionNLOLegendOnlySpectra->SetBorderSize(3);
	padXSectionNLOLegendOnlySpectra->Draw();
	padXSectionNLOLegendOnlySpectra->cd();
	
	//*************** first Column **********************************************************
	textSpectrum->Draw();
	textFitComb->Draw();
	textNLOMuHalf->Draw();
	textNLOMuOne->Draw();
	textNLOMuTwo->Draw();
	
	//*************** second Column **********************************************************
	textPi07TeVNLO->Draw();
	textPi07TeVNLOsys->Draw();
	boxCombinedPi07TeV->Draw("l");
	markerCombinedPi07TeV->DrawMarker(columnsNLOLegend[1]+offsetNLOLegendMarkerX,rowsNLOLegend[2]+offsetNLOLegendMarkerY);
	lineFit7TeVNLO->Draw("same");
	lineNLOPi07TeVMuHalf->Draw("same");
	lineNLOPi07TeVMuOne->Draw("same");
	lineNLOPi07TeVMuTwo->Draw("same");
	
	//*************** third Column **********************************************************
	textPi0900GeVNLO->Draw();
	textPi0900GeVNLOsys->Draw();
	boxCombinedPi0900GeV->Draw("l");
	markerCombinedPi0900GeV->DrawMarker(columnsNLOLegend[2]+offsetNLOLegendMarkerX,rowsNLOLegend[2]+offsetNLOLegendMarkerY);
	lineFitPi0900GeVNLO->Draw("same");
	lineNLOPi0900GeVMuHalf->Draw("same");
	lineNLOPi0900GeVMuOne->Draw("same");
	lineNLOPi0900GeVMuTwo->Draw("same");
	
	//**************** forth Column **********************************************************
	textEta7TeVNLO->Draw();
	textEta7TeVNLOsys->Draw();
	boxCombinedEta7TeV->Draw("l");
	markerCombinedEta7TeV->DrawMarker(columnsNLOLegend[3]+offsetNLOLegendMarkerX,rowsNLOLegend[2]+offsetNLOLegendMarkerY);
	lineFitEta7TeVNLO->Draw("same");
	lineNLOEta7TeVMuHalf->Draw("same");
	lineNLOEta7TeVMuOne->Draw("same");
	lineNLOEta7TeVMuTwo->Draw("same");
	  //NLO_onlySpectrum
	
	canvasInvXSectionNLOOnlySpectr->Update();
	canvasInvXSectionNLOOnlySpectr->Print(Form("%s/InvXSectionNLO_OnlySpectrum_Paper.%s",outputDir.Data(),suffix.Data()));
	
	padComparisonXSectionNLOOnlySpectra->cd();
// 	if (onlyConv) {
// 		if(!thesis)DrawAliceLogoPi0EtaPrelim(pictDrawingCoordinatesOnlySpectrumOnlyCTS[0], pictDrawingCoordinatesOnlySpectrumOnlyCTS[1], pictDrawingCoordinatesOnlySpectrumOnlyCTS[2], pictDrawingCoordinatesOnlySpectrumOnlyCTS[3], pictDrawingCoordinatesOnlySpectrumOnlyCTS[4], pictDrawingCoordinatesOnlySpectrumOnlyCTS[5], pictDrawingCoordinatesOnlySpectrumOnlyCTS[5], pictDrawingCoordinatesOnlySpectrumOnlyCTS[7], pictDrawingCoordinates[8],collisionSystemCombined, pictDrawingOptions[1], pictDrawingOptions[2], kTRUE,1200,960);
// 
// 	} else {
		if(!thesis)DrawAliceLogoPi0WithPHOSPi0EtaPrelim(pictDrawingCoordinatesOnlySpectrum[0], pictDrawingCoordinatesOnlySpectrum[1], pictDrawingCoordinatesOnlySpectrum[2], pictDrawingCoordinatesOnlySpectrum[3], pictDrawingCoordinatesOnlySpectrum[4], pictDrawingCoordinatesOnlySpectrum[5], pictDrawingCoordinatesOnlySpectrum[5], pictDrawingCoordinatesOnlySpectrum[7], pictDrawingCoordinates[8],collisionSystemCombined, pictDrawingOptions[1], pictDrawingOptions[2], kTRUE,1200,960);
// 	}
	
	canvasInvXSectionNLOOnlySpectr->Update();
	canvasInvXSectionNLOOnlySpectr->Print(Form("%s/InvXSectionNLO_OnlySpectrum.%s",outputDir.Data(),suffix.Data()));
	
//**************************************************************************************************************************************
//************************************ Inv Crosssection + NLO only ratio ***************************************************************
//**************************************************************************************************************************************
	
	TCanvas* canvasInvXSectionNLOOnlyRatio = new TCanvas("canvasInvXSectionNLOOnlyRatio","",200,10,1200,1200);  // gives the page size
	DrawGammaCanvasSettings( canvasInvXSectionNLOOnlyRatio,  0.15, 0.02, 0.03, 0.06);
	
	TPad* padXSectionNLOLegendOnlyRatio = new TPad("padXSectionNLOLegendOnlyRatio", "",  0.17, 0.8, 0.95, 1.,-1, -1, -2);
	DrawGammaPadSettings( padXSectionNLOLegendOnlyRatio, 0.15, 0.02, 0.03, 0.);
	padXSectionNLOLegendOnlyRatio->Draw();

	TPad* padXSectionNLOOnlyRatioPi07TeV = new TPad("padXSectionNLOOnlyRatioPi07TeV", "", 0., 0.565, 1., 0.8,-1, -1, -2);
	DrawGammaPadSettings( padXSectionNLOOnlyRatioPi07TeV, 0.15, 0.02, 0., 0.);
	padXSectionNLOOnlyRatioPi07TeV->Draw();
	
	TPad* padXSectionNLOOnlyRatioPi0900GeV = new TPad("padXSectionNLOOnlyRatioPi0900GeV", "", 0., 0.33, 1., 0.565,-1, -1, -2);
	DrawGammaPadSettings( padXSectionNLOOnlyRatioPi0900GeV, 0.15, 0.02, 0., 0.);
	padXSectionNLOOnlyRatioPi0900GeV->Draw();
	
	TPad* padXSectionNLOOnlyRatioEta7TeV = new TPad("padXSectionNLOOnlyRatioEta7TeV", "", 0., 0., 1., 0.33,-1, -1, -2);
	DrawGammaPadSettings( padXSectionNLOOnlyRatioEta7TeV, 0.15, 0.02, 0., 0.28);
	padXSectionNLOOnlyRatioEta7TeV->Draw();
	
	padXSectionNLOOnlyRatioPi07TeV->cd();
	padXSectionNLOOnlyRatioPi07TeV->SetLogx();
	padXSectionNLOOnlyRatioPi07TeV->SetLogy();
	
	SetStyleHistoTH2ForGraphs(ratio2DInvXSectionNLOPi0, "p_{t} (GeV/c)","#frac{NLO}{fit}", 0.13,0.13, 0.175,0.18, 1,0.32, 512, 505);
	ratio2DInvXSectionNLOPi0->DrawCopy(); 
	graphRatioCombNLOPi07TeVMuHalf->Draw("same,c");
	graphRatioCombNLOPi07TeVMuOne->Draw("same,c");
	graphRatioCombNLOPi07TeVMuTwo->Draw("same,c");
	graphRatioCombNLOBKKPi07TeVMuTwo->Draw("same,c");
	boxErrorSigmaPi07TeVRatio->Draw();
	
	//graphRatioCombCombFit->Draw("p,same");
	graphRatioCombCombFit->Draw("p,E2same");
	labelRatioNLOPi07TeV->Draw();
	
	DrawGammaLines(0., 30.,1., 1.,0.1);
	
	padXSectionNLOOnlyRatioPi0900GeV->cd();
	padXSectionNLOOnlyRatioPi0900GeV->SetLogx();
	padXSectionNLOOnlyRatioPi0900GeV->SetLogy();
	SetStyleHistoTH2ForGraphs(ratio2DInvXSectionNLOPi0900GeV, "p_{t} (GeV/c)","#frac{NLO}{fit}", 0.13,0.13, 0.175,0.18, 1,0.32, 512, 505);
	ratio2DInvXSectionNLOPi0900GeV->DrawCopy(); 
	
	graphRatioCombNLOPi0900GeVMuHalf->Draw("same,c");
	graphRatioCombNLOPi0900GeVMuOne->Draw("same,c");
	graphRatioCombNLOPi0900GeVMuTwo->Draw("same,c");
	graphRatioCombNLOBKKPi0900GeVMuTwo->Draw("same,c");
	
	boxErrorSigmaPi0900GeVRatio->Draw();
// 	graphRatioCombCombFit900GeV->Draw("same,p");
	graphRatioCombCombFit900GeV->Draw("p,E2same");
	labelRatioNLOPi0900GeV->Draw();
	
	DrawGammaLines(0., 30.,1., 1.,0.1);
	
	padXSectionNLOOnlyRatioEta7TeV->cd();
	padXSectionNLOOnlyRatioEta7TeV->SetLogx();
	padXSectionNLOOnlyRatioEta7TeV->SetLogy();
	SetStyleHistoTH2ForGraphs(ratio2DInvXSectionNLOEta, "p_{t} (GeV/c)","#frac{NLO}{fit}", 0.12,0.13, 0.125,0.128, 0.9,0.45, 510, 505);
	ratio2DInvXSectionNLOEta->GetXaxis()->SetLabelOffset(-0.03);
	ratio2DInvXSectionNLOEta->DrawCopy(); 
	
	
	graphRatioCombNLOEta7TeVMuHalf->Draw("same,c");
	graphRatioCombNLOEta7TeVMuOne->Draw("same,c");
	graphRatioCombNLOEta7TeVMuTwo->Draw("same,c");
	
	//graphRatioCombCombFitEta7TeV->Draw("same,p");
	graphRatioCombCombFitEta7TeV->Draw("p,E2same");
	boxErrorSigmaEta7TeVRatio->Draw();
	labelRatioNLOEta7TeV->Draw();
	
	DrawGammaLines(0., 30.,1., 1.,0.1);
	
	
	padXSectionNLOLegendOnlyRatio->cd();
	DrawGammaPadSettings( padXSectionNLOLegendOnlyRatio, 0., 0., 0., 0.);
	padXSectionNLOLegendOnlyRatio->SetBorderMode(-1);
	padXSectionNLOLegendOnlyRatio->SetBorderSize(3);
	padXSectionNLOLegendOnlyRatio->Draw();
	padXSectionNLOLegendOnlyRatio->cd();
	
	//****************************** Definition of the Legend ******************************************
	//**************** Row def ************************
	Double_t rowsNLOLegendOnlyRatio[7] = {0.88,0.75,0.65,0.5,0.37,0.22,0.07};
	
	//*************** first Column **********************************************************
	TLatex *textSpectrumOnlyRatio = new TLatex(columnsNLOLegend[0],rowsNLOLegendOnlyRatio[2],"combined Spec.");
	SetStyleTLatex( textSpectrumOnlyRatio, textSizeLeftLabels,4);
	textSpectrumOnlyRatio->Draw();
	TLatex *textNLOMuHalfOnlyRatio = new TLatex(columnsNLOLegend[0],rowsNLOLegendOnlyRatio[3],"NLO #mu= 0.5 p_{t}");
	SetStyleTLatex( textNLOMuHalfOnlyRatio, textSizeLeftLabels,4);
	textNLOMuHalfOnlyRatio->Draw();
	TLatex *textNLOMuOneOnlyRatio = new TLatex(columnsNLOLegend[0],rowsNLOLegendOnlyRatio[4],"NLO #mu= p_{t}");
	SetStyleTLatex( textNLOMuOneOnlyRatio, textSizeLeftLabels,4);
	textNLOMuOneOnlyRatio->Draw();
	TLatex *textNLOMuTwoOnlyRatio = new TLatex(columnsNLOLegend[0],rowsNLOLegendOnlyRatio[5],"NLO #mu= 2 p_{t}");
	SetStyleTLatex( textNLOMuTwoOnlyRatio, textSizeLeftLabels,4);
	textNLOMuTwoOnlyRatio->Draw();
	TLatex *textNLOBKKMuTwoOnlyRatio = new TLatex(columnsNLOLegend[0],rowsNLOLegendOnlyRatio[6],"NLO #mu= 2 p_{t} (BKK)");
	SetStyleTLatex( textNLOBKKMuTwoOnlyRatio, textSizeLeftLabels,4);
	textNLOBKKMuTwoOnlyRatio->Draw();
	
	
	//*************** second Column **********************************************************
	TLatex *textPi07TeVNLOOnlyRatio = new TLatex(columnsNLOLegend[1],rowsNLOLegendOnlyRatio[0],"#pi^{0} @ #sqrt{#it{s}} = 7 TeV");
	SetStyleTLatex( textPi07TeVNLOOnlyRatio, textSizeTopLables,4);
	textPi07TeVNLOOnlyRatio->Draw();
	TLatex *textPi07TeVNLOsysOnlyRatio = new TLatex(columnsNLOLegend[1],rowsNLOLegendOnlyRatio[1],"syst + stat");
	SetStyleTLatex( textPi07TeVNLOsysOnlyRatio, textSizeTopLowerLables,4);
	textPi07TeVNLOsysOnlyRatio->Draw();
	TBox* boxCombinedPi07TeVOnlyRatio = CreateBoxFromGraph(graphInvCrossSectionPi0Comb7TeV,columnsNLOLegend[1]+offsetNLOLegendMarkerX-offsetNLOLegendLine, rowsNLOLegendOnlyRatio[2]+ offsetNLOLegendMarkerY- offsetNLOLegendBox, columnsNLOLegend[1]+offsetNLOLegendMarkerX+offsetNLOLegendLine, rowsNLOLegendOnlyRatio[2]+ offsetNLOLegendMarkerY+offsetNLOLegendBox);
	boxCombinedPi07TeVOnlyRatio->Draw("l");
	TMarker* markerCombinedPi07TeVOnlyRatio = CreateMarkerFromGraph(graphInvCrossSectionPi0Comb7TeV,columnsNLOLegend[1]+offsetNLOLegendMarkerX,rowsNLOLegendOnlyRatio[2]+offsetNLOLegendMarkerY ,scaleMarkerNLO);
	markerCombinedPi07TeVOnlyRatio->DrawMarker(columnsNLOLegend[1]+offsetNLOLegendMarkerX,rowsNLOLegendOnlyRatio[2]+offsetNLOLegendMarkerY);
	TLine * lineNLOPi07TeVMuHalfOnlyRatio = CreateLineFromGraph(graphNLOMuHalfPi07TeV, columnsNLOLegend[1]+ offsetNLOLegendMarkerX- offsetNLOLegendLine, rowsNLOLegendOnlyRatio[3] + offsetNLOLegendMarkerY, columnsNLOLegend[1]+ offsetNLOLegendMarkerX+ offsetNLOLegendLine, rowsNLOLegendOnlyRatio[3]+offsetNLOLegendMarkerY, scaleLineWidthNLO*1.5); 
	lineNLOPi07TeVMuHalfOnlyRatio->Draw("same");
	TLine * lineNLOPi07TeVMuOneOnlyRatio = CreateLineFromGraph(graphNLOMuOnePi07TeV,columnsNLOLegend[1]+ offsetNLOLegendMarkerX- offsetNLOLegendLine, rowsNLOLegendOnlyRatio[4]+offsetNLOLegendMarkerY, columnsNLOLegend[1]+ offsetNLOLegendMarkerX+ offsetNLOLegendLine,rowsNLOLegendOnlyRatio[4]+offsetNLOLegendMarkerY, scaleLineWidthNLO*1.5); 
	lineNLOPi07TeVMuOneOnlyRatio->Draw("same");
	TLine * lineNLOPi07TeVMuTwoOnlyRatio = CreateLineFromGraph(graphNLOMuTwoPi07TeV, columnsNLOLegend[1]+ offsetNLOLegendMarkerX- offsetNLOLegendLine, rowsNLOLegendOnlyRatio[5]+offsetNLOLegendMarkerY, columnsNLOLegend[1]+ offsetNLOLegendMarkerX+ offsetNLOLegendLine,rowsNLOLegendOnlyRatio[5]+offsetNLOLegendMarkerY, scaleLineWidthNLO*1.5); 
	lineNLOPi07TeVMuTwoOnlyRatio->Draw("same");
	TLine * lineNLOBKKPi07TeVMuTwoOnlyRatio = CreateLineFromGraph(graphRatioCombNLOBKKPi07TeVMuTwo, columnsNLOLegend[1]+ offsetNLOLegendMarkerX- offsetNLOLegendLine, rowsNLOLegendOnlyRatio[6]+offsetNLOLegendMarkerY, columnsNLOLegend[1]+ offsetNLOLegendMarkerX+ offsetNLOLegendLine,rowsNLOLegendOnlyRatio[6]+offsetNLOLegendMarkerY, scaleLineWidthNLO*1.5); 
	lineNLOBKKPi07TeVMuTwoOnlyRatio->Draw("same");
	
	
	//*************** third Column **********************************************************
	TLatex *textPi0900GeVNLOOnlyRatio = new TLatex(columnsNLOLegend[2],rowsNLOLegendOnlyRatio[0],"#pi^{0} @ #sqrt{#it{s}} = 0.9 TeV");
	SetStyleTLatex( textPi0900GeVNLOOnlyRatio, textSizeTopLables,4);
	textPi0900GeVNLOOnlyRatio->Draw();
	TLatex *textPi0900GeVNLOsysOnlyRatio = new TLatex(columnsNLOLegend[2],rowsNLOLegendOnlyRatio[1],"syst + stat");
	SetStyleTLatex( textPi0900GeVNLOsysOnlyRatio, textSizeTopLowerLables,4);
	textPi0900GeVNLOsysOnlyRatio->Draw();
	TBox* boxCombinedPi0900GeVOnlyRatio = CreateBoxFromGraph(graphInvCrossSectionPi0Comb900GeV,columnsNLOLegend[2]+offsetNLOLegendMarkerX-offsetNLOLegendLine, rowsNLOLegendOnlyRatio[2]+ offsetNLOLegendMarkerY- offsetNLOLegendBox, columnsNLOLegend[2]+offsetNLOLegendMarkerX+offsetNLOLegendLine, rowsNLOLegendOnlyRatio[2]+ offsetNLOLegendMarkerY+offsetNLOLegendBox);
	boxCombinedPi0900GeVOnlyRatio->Draw("l");
	TMarker* markerCombinedPi0900GeVOnlyRatio = CreateMarkerFromGraph(graphInvCrossSectionPi0Comb900GeV,columnsNLOLegend[2]+offsetNLOLegendMarkerX,rowsNLOLegendOnlyRatio[2]+offsetNLOLegendMarkerY ,scaleMarkerNLO);
	markerCombinedPi0900GeVOnlyRatio->DrawMarker(columnsNLOLegend[2]+offsetNLOLegendMarkerX,rowsNLOLegendOnlyRatio[2]+offsetNLOLegendMarkerY);
	TLine * lineNLOPi0900GeVMuHalfOnlyRatio = CreateLineFromGraph(graphNLOMuHalfPi0900GeV,  columnsNLOLegend[2]+ offsetNLOLegendMarkerX- offsetNLOLegendLine, rowsNLOLegendOnlyRatio[3] + offsetNLOLegendMarkerY, columnsNLOLegend[2]+ offsetNLOLegendMarkerX+ offsetNLOLegendLine, rowsNLOLegendOnlyRatio[3]+offsetNLOLegendMarkerY, scaleLineWidthNLO*1.5); 
	lineNLOPi0900GeVMuHalfOnlyRatio->Draw("same");
	TLine * lineNLOPi0900GeVMuOneOnlyRatio = CreateLineFromGraph(graphNLOMuOnePi0900GeV, columnsNLOLegend[2]+ offsetNLOLegendMarkerX- offsetNLOLegendLine, rowsNLOLegendOnlyRatio[4]+offsetNLOLegendMarkerY, columnsNLOLegend[2]+ offsetNLOLegendMarkerX+ offsetNLOLegendLine,rowsNLOLegendOnlyRatio[4]+offsetNLOLegendMarkerY, scaleLineWidthNLO*1.5); 
	lineNLOPi0900GeVMuOneOnlyRatio->Draw("same");
	TLine * lineNLOPi0900GeVMuTwoOnlyRatio = CreateLineFromGraph(graphNLOMuTwoPi0900GeV, columnsNLOLegend[2]+ offsetNLOLegendMarkerX- offsetNLOLegendLine, rowsNLOLegendOnlyRatio[5]+offsetNLOLegendMarkerY, columnsNLOLegend[2]+ offsetNLOLegendMarkerX+ offsetNLOLegendLine,rowsNLOLegendOnlyRatio[5]+offsetNLOLegendMarkerY, scaleLineWidthNLO*1.5); 
	lineNLOPi0900GeVMuTwoOnlyRatio->Draw("same");
	TLine * lineNLOBKKPi0900GeVMuTwoOnlyRatio = CreateLineFromGraph(graphRatioCombNLOBKKPi0900GeVMuTwo, columnsNLOLegend[2]+ offsetNLOLegendMarkerX- offsetNLOLegendLine, rowsNLOLegendOnlyRatio[6]+offsetNLOLegendMarkerY, columnsNLOLegend[2]+ offsetNLOLegendMarkerX+ offsetNLOLegendLine,rowsNLOLegendOnlyRatio[6]+offsetNLOLegendMarkerY, scaleLineWidthNLO*1.5); 
	lineNLOBKKPi0900GeVMuTwoOnlyRatio->Draw("same");
	
	//**************** forth Column **********************************************************
	TLatex *textEta7TeVNLOOnlyRatio = new TLatex(columnsNLOLegend[3],rowsNLOLegendOnlyRatio[0],"#eta @ #sqrt{#it{s}} = 7 TeV");
	SetStyleTLatex( textEta7TeVNLOOnlyRatio, textSizeTopLables,4);
	textEta7TeVNLOOnlyRatio->Draw();
	TLatex *textEta7TeVNLOsysOnlyRatio = new TLatex(columnsNLOLegend[3],rowsNLOLegendOnlyRatio[1],"syst + stat");
	SetStyleTLatex( textEta7TeVNLOsysOnlyRatio, textSizeTopLowerLables,4);
	textEta7TeVNLOsysOnlyRatio->Draw();
	TBox* boxCombinedEta7TeVOnlyRatio = CreateBoxFromGraph(graphInvCrossSectionEtaComb7TeV,columnsNLOLegend[3]+offsetNLOLegendMarkerX-offsetNLOLegendLine, rowsNLOLegendOnlyRatio[2]+ offsetNLOLegendMarkerY- offsetNLOLegendBox, columnsNLOLegend[3]+offsetNLOLegendMarkerX+offsetNLOLegendLine, rowsNLOLegendOnlyRatio[2]+ offsetNLOLegendMarkerY+offsetNLOLegendBox);
	boxCombinedEta7TeVOnlyRatio->Draw("l");
	TMarker* markerCombinedEta7TeVOnlyRatio = CreateMarkerFromGraph(graphInvCrossSectionEtaComb7TeV,columnsNLOLegend[3]+offsetNLOLegendMarkerX,rowsNLOLegendOnlyRatio[2]+offsetNLOLegendMarkerY ,scaleMarkerNLO);
	markerCombinedEta7TeVOnlyRatio->DrawMarker(columnsNLOLegend[3]+offsetNLOLegendMarkerX,rowsNLOLegendOnlyRatio[2]+offsetNLOLegendMarkerY);
	TLine * lineNLOEta7TeVMuHalfOnlyRatio =  CreateLineFromGraph(graphNLOMuHalfEta7TeV, columnsNLOLegend[3]+ offsetNLOLegendMarkerX- offsetNLOLegendLine, rowsNLOLegendOnlyRatio[3] + offsetNLOLegendMarkerY, columnsNLOLegend[3]+ offsetNLOLegendMarkerX+ offsetNLOLegendLine, rowsNLOLegendOnlyRatio[3]+offsetNLOLegendMarkerY, scaleLineWidthNLO*1.5); 
	lineNLOEta7TeVMuHalfOnlyRatio->Draw("same");
	TLine * lineNLOEta7TeVMuOneOnlyRatio =  CreateLineFromGraph(graphNLOMuOneEta7TeV,columnsNLOLegend[3]+ offsetNLOLegendMarkerX- offsetNLOLegendLine, rowsNLOLegendOnlyRatio[4]+offsetNLOLegendMarkerY, columnsNLOLegend[3]+ offsetNLOLegendMarkerX+ offsetNLOLegendLine,rowsNLOLegendOnlyRatio[4]+offsetNLOLegendMarkerY, scaleLineWidthNLO*1.5); 
	lineNLOEta7TeVMuOneOnlyRatio->Draw("same");
	TLine * lineNLOEta7TeVMuTwoOnlyRatio =  CreateLineFromGraph(graphNLOMuTwoEta7TeV, columnsNLOLegend[3]+ offsetNLOLegendMarkerX- offsetNLOLegendLine, rowsNLOLegendOnlyRatio[5]+offsetNLOLegendMarkerY, columnsNLOLegend[3]+ offsetNLOLegendMarkerX+ offsetNLOLegendLine,rowsNLOLegendOnlyRatio[5]+offsetNLOLegendMarkerY, scaleLineWidthNLO*1.5); 
	lineNLOEta7TeVMuTwoOnlyRatio->Draw("same");
	//************************************************* End Legend ***************************************************
	
	
	canvasInvXSectionNLOOnlyRatio->Update();
	canvasInvXSectionNLOOnlyRatio->Print(Form("%s/InvXSectionNLO_OnlyRatio_Paper.%s",outputDir.Data(),suffix.Data()));

	



	
	//************************ Meson Combined + NLO *******************************************************************
	TCanvas* canvasInvXSectionNLO = new TCanvas("canvasInvXSectionNLO","",200,10,1200,2000);  // gives the page size
	DrawGammaCanvasSettings( canvasInvXSectionNLO,  0.15, 0.02, 0.03, 0.06);
	
	TPad* padComparisonXSectionNLO = new TPad("padComparisonXSectionNLO", "", 0., 0.42, 1., 1.,-1, -1, -2);
	DrawGammaPadSettings( padComparisonXSectionNLO, 0.15, 0.02, 0.03, 0.);
	padComparisonXSectionNLO->Draw();
	
	TPad* padXSectionNLORatioPi07TeV = new TPad("padXSectionNLORatioPi07TeV", "", 0., 0.30, 1., 0.42,-1, -1, -2);
	DrawGammaPadSettings( padXSectionNLORatioPi07TeV, 0.15, 0.02, 0., 0.);
	padXSectionNLORatioPi07TeV->Draw();
	
	TPad* padXSectionNLORatioPi0900GeV = new TPad("padXSectionNLORatioPi0900GeV", "", 0., 0.18, 1., 0.30,-1, -1, -2);
	DrawGammaPadSettings( padXSectionNLORatioPi0900GeV, 0.15, 0.02, 0., 0.);
	padXSectionNLORatioPi0900GeV->Draw();
	
	TPad* padXSectionNLORatioEta7TeV = new TPad("padXSectionNLORatioEta7TeV", "", 0., 0., 1., 0.18,-1, -1, -2);
	DrawGammaPadSettings( padXSectionNLORatioEta7TeV, 0.15, 0.02, 0., 0.28);
	padXSectionNLORatioEta7TeV->Draw();
	
	
	padComparisonXSectionNLO->cd();
	padComparisonXSectionNLO->SetLogy();		
	padComparisonXSectionNLO->SetLogx();		
	
	//-------------- Plotting ------------------------------------------------------
	TH2F * histo2DInvXSectionNLO = new TH2F("histo2DInvXSectionNLO","histo2DInvXSectionNLO",1000,0.23,30.,1000,2e-4,10e12);
	SetStyleHistoTH2ForGraphs(histo2DInvXSectionNLO, "p_{t} (GeV/c)","E #frac{d^{3}#sigma}{dp^{3}} (pb GeV^{-2} c^{3} )", 0.032,0.04, 0.04,0.04, 1,1.55);
	histo2DInvXSectionNLO->GetYaxis()->SetRangeUser(2e-4,10e11);
	histo2DInvXSectionNLO->DrawCopy(); 
				
//	graphInvCrossSectionPi0Comb900GeV->Draw("same,p");
	graphInvCrossSectionPi0Comb900GeV->Draw("p,E2same");
	
//	graphInvCrossSectionPi0Comb7TeV->Draw("p,same");
	graphInvCrossSectionPi0Comb7TeV->Draw("p,E2same");
	
//	graphInvCrossSectionEtaComb7TeV->Draw("same,p");
	graphInvCrossSectionEtaComb7TeV->Draw("p,E2same");
	
	DrawGammaSetMarkerTF1( fitInvCrossSectionPi0, styleFitCommonSpectrum, widthCommonFit, colorCommonSpectrumPi07TeV);
	fitInvCrossSectionPi0->Draw("same");
	
	SetStyleHisto(histoFitInvCrossSectionPi0900GeV, widthCommonFit, styleFitCommonSpectrum, colorCommonSpectrumPi0900GeV);
	histoFitInvCrossSectionPi0900GeV->Draw("same,c");
	
	SetStyleHisto(histoFitInvCrossSectionEta7TeV, widthCommonFit, styleFitCommonSpectrum, colorCommonSpectrumEta7TeV);
	histoFitInvCrossSectionEta7TeV->Draw("same,c");

	graphNLOMuHalfPi07TeV->SetLineStyle(styleLineNLOMuHalf);
	graphNLOMuHalfPi07TeV->SetLineWidth(widthCommonFit );
	graphNLOMuHalfPi07TeV->Draw("same,c");
	graphNLOMuOnePi07TeV->SetLineStyle(styleLineNLOMuOne);
	graphNLOMuOnePi07TeV->SetLineWidth(widthCommonFit );
	graphNLOMuOnePi07TeV->Draw("same,c");
	graphNLOMuTwoPi07TeV->SetLineStyle(styleLineNLOMuTwo);
	graphNLOMuTwoPi07TeV->SetLineWidth(widthCommonFit );
	graphNLOMuTwoPi07TeV->Draw("same,c");
	DrawGammaSetMarkerTGraph(graphRatioCombNLOBKKPi07TeVMuTwo, styleMarkerNLOMuTwo, sizeMarkerNLO, colorNLOPi07TeVMuTwo, colorNLOPi07TeVMuTwo);
	graphRatioCombNLOBKKPi07TeVMuTwo->SetLineWidth(widthCommonFit);
	graphRatioCombNLOBKKPi07TeVMuTwo->SetLineStyle(styleLineNLOMuTwoBKK);
	DrawGammaSetMarkerTGraph(graphRatioCombNLODSSPi07TeVMuTwo, styleMarkerNLOMuTwo, sizeMarkerNLO, colorNLOPi07TeVMuTwo, colorNLOPi07TeVMuTwo);
	graphRatioCombNLODSSPi07TeVMuTwo->SetLineWidth(widthCommonFit);
	graphRatioCombNLODSSPi07TeVMuTwo->SetLineStyle(styleLineNLOMuTwoDSS);
	
	graphNLOMuHalfPi0900GeV= ScaleGraph(graphNLOMuHalfPi0900GeV,1e-1);
	DrawGammaSetMarkerTGraph(graphNLOMuHalfPi0900GeV, styleMarkerNLOMuHalf ,sizeMarkerNLO,colorNLOPi0900GeVMuHalf, colorNLOPi0900GeVMuHalf);
	graphNLOMuHalfPi0900GeV->SetLineStyle(styleLineNLOMuHalf);
	graphNLOMuHalfPi0900GeV->SetLineWidth(widthCommonFit);
	graphNLOMuHalfPi0900GeV->Draw("same,c");
	graphNLOMuOnePi0900GeV= ScaleGraph(graphNLOMuOnePi0900GeV,1e-1);
	DrawGammaSetMarkerTGraph(graphNLOMuOnePi0900GeV, styleMarkerNLOMuOne, sizeMarkerNLO, colorNLOPi0900GeVMuOne, colorNLOPi0900GeVMuOne);
	graphNLOMuOnePi0900GeV->SetLineStyle(styleLineNLOMuOne);
	graphNLOMuOnePi0900GeV->SetLineWidth(widthCommonFit);
	graphNLOMuOnePi0900GeV->Draw("same,c");
	graphNLOMuTwoPi0900GeV = ScaleGraph(graphNLOMuTwoPi0900GeV,1e-1);
	DrawGammaSetMarkerTGraph(graphNLOMuTwoPi0900GeV, styleMarkerNLOMuTwo, sizeMarkerNLO, colorNLOPi0900GeVMuTwo, colorNLOPi0900GeVMuTwo);
	graphNLOMuTwoPi0900GeV->SetLineStyle(styleLineNLOMuTwo);
	graphNLOMuTwoPi0900GeV->SetLineWidth(widthCommonFit);
	graphNLOMuTwoPi0900GeV->Draw("same,c");
	DrawGammaSetMarkerTGraph(graphRatioCombNLOBKKPi0900GeVMuTwo, styleMarkerNLOMuTwo, sizeMarkerNLO, colorNLOPi0900GeVMuTwo, colorNLOPi0900GeVMuTwo);
	graphRatioCombNLOBKKPi0900GeVMuTwo->SetLineWidth(widthCommonFit);
	graphRatioCombNLOBKKPi0900GeVMuTwo->SetLineStyle(styleLineNLOMuTwoBKK);
	
	
	graphNLOMuHalfEta7TeV= ScaleGraph(graphNLOMuHalfEta7TeV,1e-3);
	DrawGammaSetMarkerTGraph(graphNLOMuHalfEta7TeV, styleMarkerNLOMuHalf, sizeMarkerNLO, colorNLOEta7TeVMuHalf, colorNLOEta7TeVMuHalf);
	graphNLOMuHalfEta7TeV->SetLineStyle(styleLineNLOMuHalf);
	graphNLOMuHalfEta7TeV->SetLineWidth(widthCommonFit );
	graphNLOMuHalfEta7TeV->Draw("same,c");
	graphNLOMuOneEta7TeV= ScaleGraph(graphNLOMuOneEta7TeV,1e-3);
	DrawGammaSetMarkerTGraph(graphNLOMuOneEta7TeV, styleMarkerNLOMuOne, sizeMarkerNLO,colorNLOEta7TeVMuOne, colorNLOEta7TeVMuOne);
	graphNLOMuOneEta7TeV->SetLineStyle(styleLineNLOMuOne);
	graphNLOMuOneEta7TeV->SetLineWidth(widthCommonFit );
	graphNLOMuOneEta7TeV->Draw("same,c");
	graphNLOMuTwoEta7TeV = ScaleGraph(graphNLOMuTwoEta7TeV,1e-3);
	DrawGammaSetMarkerTGraph(graphNLOMuTwoEta7TeV, styleMarkerNLOMuTwo, sizeMarkerNLO, colorNLOEta7TeVMuTwo, colorNLOEta7TeVMuTwo);
	graphNLOMuTwoEta7TeV->SetLineStyle(styleLineNLOMuTwo);
	graphNLOMuTwoEta7TeV->SetLineWidth(widthCommonFit );
	graphNLOMuTwoEta7TeV->Draw("same,c");

	TLatex *labelLegendA = new TLatex(15,2E11,"a)");
	SetStyleTLatex( labelLegendA, 0.035,4,1,kFALSE);
	labelLegendA->Draw();
	
	labelScalingPi07TeV->Draw();
	labelScalingPi0900GeV->Draw();
	labelScalingEta7TeV->Draw();
	DrawNormalizationErrorText(normalizationInvX3En[0],normalizationInvX3En[1],normalizationInvX3En[2],normalizationInvX3En[3],normalizationInvX3En[4],"No2.76"); 

	
	
		
	//****************************** Definition of the Legend ******************************************
		//**************** Row def ************************
		Double_t rowsNLOLegend[8] = {0.89,0.79,0.68,0.54,0.43,0.31,0.17,0.05};
		//*************** Label sizes *********************
		Double_t textSizeLeftLabels = 0.125;
		Double_t textSizeTopLables = 0.125;
		Double_t textSizeTopLowerLables = 0.12;
		//*************** Column def ***********************
		Double_t columnsNLOLegend[4] = {0.,0.25,0.49,0.76};
		//*************** Size factors ********************
		Double_t scaleMarkerNLO = 1.5;
		Double_t scaleLineWidthNLO = 1.;
		//*************** Offsets *************************
		Double_t offsetNLOLegendMarkerX = 0.09;
		Double_t offsetNLOLegendMarkerY = 0.03;
		Double_t offsetNLOLegendBox = 0.05;
		Double_t offsetNLOLegendLine = 0.06;

		TPad* padXSectionNLOLegend = new TPad("padXSectionNLOLegend", "", 0.17, 0.005, 0.95, 0.19,-1, -1, -2); 
		//TPad* padXSectionNLOLegend = new TPad("padXSectionNLOLegend", "", 0.17, 0.02, 0.95, 0.23,-1, -1, -2);
		DrawGammaPadSettings( padXSectionNLOLegend, 0., 0., 0., 0.);
		padXSectionNLOLegend->Draw();
		padXSectionNLOLegend->cd();
		
		//*************** first Column **********************************************************
		TLatex *textSpectrum = new TLatex(columnsNLOLegend[0],rowsNLOLegend[2],"combined Spec.");
		SetStyleTLatex( textSpectrum, textSizeLeftLabels,4);
		textSpectrum->Draw();
		TLatex *textFitComb = new TLatex(columnsNLOLegend[0],rowsNLOLegend[3],"fit combined");
		SetStyleTLatex( textFitComb, textSizeLeftLabels,4);
		textFitComb->Draw();
		TLatex *textNLOMuHalf = new TLatex(columnsNLOLegend[0],rowsNLOLegend[4],"NLO #mu= 0.5 p_{t}");
		SetStyleTLatex( textNLOMuHalf, textSizeLeftLabels,4);
		textNLOMuHalf->Draw();
		TLatex *textNLOMuOne = new TLatex(columnsNLOLegend[0],rowsNLOLegend[5],"NLO #mu= p_{t}");
		SetStyleTLatex( textNLOMuOne, textSizeLeftLabels,4);
		textNLOMuOne->Draw();
		TLatex *textNLOMuTwo = new TLatex(columnsNLOLegend[0],rowsNLOLegend[6],"NLO #mu= 2 p_{t}");
		SetStyleTLatex( textNLOMuTwo, textSizeLeftLabels,4);
		textNLOMuTwo->Draw();
		TLatex *textNLOMuTwoBKK = new TLatex(columnsNLOLegend[0],rowsNLOLegend[7],"NLO #mu= 2 p_{t} (BKK)");
		SetStyleTLatex( textNLOMuTwoBKK, textSizeLeftLabels,4);
		textNLOMuTwoBKK->Draw();
		
		
		//*************** second Column **********************************************************
		TLatex *textPi07TeVNLO = new TLatex(columnsNLOLegend[1],rowsNLOLegend[0],"#pi^{0} @ #sqrt{#it{s}} = 7 TeV");
		SetStyleTLatex( textPi07TeVNLO, textSizeTopLables,4);
		textPi07TeVNLO->Draw();
		TLatex *textPi07TeVNLOsys = new TLatex(columnsNLOLegend[1],rowsNLOLegend[1],"syst + stat");
		SetStyleTLatex( textPi07TeVNLOsys, textSizeTopLowerLables,4);
		textPi07TeVNLOsys->Draw();
		TBox* boxCombinedPi07TeV = CreateBoxFromGraph(graphInvCrossSectionPi0Comb7TeV,columnsNLOLegend[1]+offsetNLOLegendMarkerX-offsetNLOLegendLine, rowsNLOLegend[2]+ offsetNLOLegendMarkerY- offsetNLOLegendBox, columnsNLOLegend[1]+offsetNLOLegendMarkerX+offsetNLOLegendLine, rowsNLOLegend[2]+ offsetNLOLegendMarkerY+offsetNLOLegendBox);
		boxCombinedPi07TeV->Draw("l");
		TMarker* markerCombinedPi07TeV = CreateMarkerFromGraph(graphInvCrossSectionPi0Comb7TeV,columnsNLOLegend[1]+offsetNLOLegendMarkerX,rowsNLOLegend[2]+offsetNLOLegendMarkerY ,scaleMarkerNLO);
		markerCombinedPi07TeV->DrawMarker(columnsNLOLegend[1]+offsetNLOLegendMarkerX,rowsNLOLegend[2]+offsetNLOLegendMarkerY);
		TLine * lineFit7TeVNLO = CreateLineFromFit(fitInvCrossSectionPi0, columnsNLOLegend[1]+ offsetNLOLegendMarkerX- offsetNLOLegendLine, rowsNLOLegend[3]+offsetNLOLegendMarkerY, columnsNLOLegend[1]+ offsetNLOLegendMarkerX+ offsetNLOLegendLine,rowsNLOLegend[3]+offsetNLOLegendMarkerY, scaleLineWidthNLO);
		lineFit7TeVNLO->Draw("same");
		TLine * lineNLOPi07TeVMuHalf = CreateLineFromGraph(graphNLOMuHalfPi07TeV, columnsNLOLegend[1]+ offsetNLOLegendMarkerX- offsetNLOLegendLine, rowsNLOLegend[4] + offsetNLOLegendMarkerY, columnsNLOLegend[1]+ offsetNLOLegendMarkerX+ offsetNLOLegendLine, rowsNLOLegend[4]+offsetNLOLegendMarkerY, scaleLineWidthNLO); 
		lineNLOPi07TeVMuHalf->Draw("same");
		TLine * lineNLOPi07TeVMuOne = CreateLineFromGraph(graphNLOMuOnePi07TeV,columnsNLOLegend[1]+ offsetNLOLegendMarkerX- offsetNLOLegendLine, rowsNLOLegend[5]+offsetNLOLegendMarkerY, columnsNLOLegend[1]+ offsetNLOLegendMarkerX+ offsetNLOLegendLine,rowsNLOLegend[5]+offsetNLOLegendMarkerY, scaleLineWidthNLO); 
		lineNLOPi07TeVMuOne->Draw("same");
		TLine * lineNLOPi07TeVMuTwo = CreateLineFromGraph(graphNLOMuTwoPi07TeV, columnsNLOLegend[1]+ offsetNLOLegendMarkerX- offsetNLOLegendLine, rowsNLOLegend[6]+offsetNLOLegendMarkerY, columnsNLOLegend[1]+ offsetNLOLegendMarkerX+ offsetNLOLegendLine,rowsNLOLegend[6]+offsetNLOLegendMarkerY, scaleLineWidthNLO); 
		lineNLOPi07TeVMuTwo->Draw("same");
		TLine * lineNLOPi07TeVMuTwoBKK = CreateLineFromGraph(graphRatioCombNLOBKKPi07TeVMuTwo, columnsNLOLegend[1]+ offsetNLOLegendMarkerX- offsetNLOLegendLine, rowsNLOLegend[7]+offsetNLOLegendMarkerY, columnsNLOLegend[1]+ offsetNLOLegendMarkerX+ offsetNLOLegendLine,rowsNLOLegend[7]+offsetNLOLegendMarkerY, scaleLineWidthNLO); 
		lineNLOPi07TeVMuTwoBKK->Draw("same");
		TLine * lineNLOPi07TeVMuTwoDSS = CreateLineFromGraph(graphRatioCombNLODSSPi07TeVMuTwo, columnsNLOLegend[1]+ offsetNLOLegendMarkerX- offsetNLOLegendLine, rowsNLOLegend[7]+offsetNLOLegendMarkerY, columnsNLOLegend[1]+ offsetNLOLegendMarkerX+ offsetNLOLegendLine,rowsNLOLegend[7]+offsetNLOLegendMarkerY, scaleLineWidthNLO); 
		lineNLOPi07TeVMuTwoDSS->Draw("same");		
		//*************** third Column **********************************************************
		TLatex *textPi0900GeVNLO = new TLatex(columnsNLOLegend[2],rowsNLOLegend[0],"#pi^{0} @ #sqrt{#it{s}} = 0.9 TeV");
		SetStyleTLatex( textPi0900GeVNLO, textSizeTopLables,4);
		textPi0900GeVNLO->Draw();
		TLatex *textPi0900GeVNLOsys = new TLatex(columnsNLOLegend[2],rowsNLOLegend[1],"syst + stat");
		SetStyleTLatex( textPi0900GeVNLOsys, textSizeTopLowerLables,4);
		textPi0900GeVNLOsys->Draw();
		TBox* boxCombinedPi0900GeV = CreateBoxFromGraph(graphInvCrossSectionPi0Comb900GeV,columnsNLOLegend[2]+offsetNLOLegendMarkerX-offsetNLOLegendLine, rowsNLOLegend[2]+ offsetNLOLegendMarkerY- offsetNLOLegendBox, columnsNLOLegend[2]+offsetNLOLegendMarkerX+offsetNLOLegendLine, rowsNLOLegend[2]+ offsetNLOLegendMarkerY+offsetNLOLegendBox);
		boxCombinedPi0900GeV->Draw("l");
		TMarker* markerCombinedPi0900GeV = CreateMarkerFromGraph(graphInvCrossSectionPi0Comb900GeV,columnsNLOLegend[2]+offsetNLOLegendMarkerX,rowsNLOLegend[2]+offsetNLOLegendMarkerY ,scaleMarkerNLO);
		markerCombinedPi0900GeV->DrawMarker(columnsNLOLegend[2]+offsetNLOLegendMarkerX,rowsNLOLegend[2]+offsetNLOLegendMarkerY);
		TLine * lineFitPi0900GeVNLO =CreateLineFromHisto(histoFitInvCrossSectionPi0900GeV, columnsNLOLegend[2]+ offsetNLOLegendMarkerX- offsetNLOLegendLine, rowsNLOLegend[3]+offsetNLOLegendMarkerY, columnsNLOLegend[2]+ offsetNLOLegendMarkerX+ offsetNLOLegendLine,rowsNLOLegend[3]+offsetNLOLegendMarkerY, scaleLineWidthNLO);
		lineFitPi0900GeVNLO->Draw("same");
		TLine * lineNLOPi0900GeVMuHalf = CreateLineFromGraph(graphNLOMuHalfPi0900GeV,  columnsNLOLegend[2]+ offsetNLOLegendMarkerX- offsetNLOLegendLine, rowsNLOLegend[4] + offsetNLOLegendMarkerY, columnsNLOLegend[2]+ offsetNLOLegendMarkerX+ offsetNLOLegendLine, rowsNLOLegend[4]+offsetNLOLegendMarkerY, scaleLineWidthNLO); 
		lineNLOPi0900GeVMuHalf->Draw("same");
		TLine * lineNLOPi0900GeVMuOne = CreateLineFromGraph(graphNLOMuOnePi0900GeV, columnsNLOLegend[2]+ offsetNLOLegendMarkerX- offsetNLOLegendLine, rowsNLOLegend[5]+offsetNLOLegendMarkerY, columnsNLOLegend[2]+ offsetNLOLegendMarkerX+ offsetNLOLegendLine,rowsNLOLegend[5]+offsetNLOLegendMarkerY, scaleLineWidthNLO); 
		lineNLOPi0900GeVMuOne->Draw("same");
		TLine * lineNLOPi0900GeVMuTwo = CreateLineFromGraph(graphNLOMuTwoPi0900GeV, columnsNLOLegend[2]+ offsetNLOLegendMarkerX- offsetNLOLegendLine, rowsNLOLegend[6]+offsetNLOLegendMarkerY, columnsNLOLegend[2]+ offsetNLOLegendMarkerX+ offsetNLOLegendLine,rowsNLOLegend[6]+offsetNLOLegendMarkerY, scaleLineWidthNLO); 
		lineNLOPi0900GeVMuTwo->Draw("same");
		TLine * lineNLOPi0900GeVMuTwoBKK = CreateLineFromGraph(graphRatioCombNLOBKKPi0900GeVMuTwo, columnsNLOLegend[2]+ offsetNLOLegendMarkerX- offsetNLOLegendLine, rowsNLOLegend[7]+offsetNLOLegendMarkerY, columnsNLOLegend[2]+ offsetNLOLegendMarkerX+ offsetNLOLegendLine,rowsNLOLegend[7]+offsetNLOLegendMarkerY, scaleLineWidthNLO); 
		lineNLOPi0900GeVMuTwoBKK->Draw("same");
		
		
		//**************** forth Column **********************************************************
		TLatex *textEta7TeVNLO = new TLatex(columnsNLOLegend[3],rowsNLOLegend[0],"#eta @ #sqrt{#it{s}} = 7 TeV");
		SetStyleTLatex( textEta7TeVNLO, textSizeTopLables,4);
		textEta7TeVNLO->Draw();
		TLatex *textEta7TeVNLOsys = new TLatex(columnsNLOLegend[3],rowsNLOLegend[1],"syst + stat");
		SetStyleTLatex( textEta7TeVNLOsys, textSizeTopLowerLables,4);
		textEta7TeVNLOsys->Draw();
		TBox* boxCombinedEta7TeV = CreateBoxFromGraph(graphInvCrossSectionEtaComb7TeV,columnsNLOLegend[3]+offsetNLOLegendMarkerX-offsetNLOLegendLine, rowsNLOLegend[2]+ offsetNLOLegendMarkerY- offsetNLOLegendBox, columnsNLOLegend[3]+offsetNLOLegendMarkerX+offsetNLOLegendLine, rowsNLOLegend[2]+ offsetNLOLegendMarkerY+offsetNLOLegendBox);
		boxCombinedEta7TeV->Draw("l");
		TMarker* markerCombinedEta7TeV = CreateMarkerFromGraph(graphInvCrossSectionEtaComb7TeV,columnsNLOLegend[3]+offsetNLOLegendMarkerX,rowsNLOLegend[2]+offsetNLOLegendMarkerY ,scaleMarkerNLO);
		markerCombinedEta7TeV->DrawMarker(columnsNLOLegend[3]+offsetNLOLegendMarkerX,rowsNLOLegend[2]+offsetNLOLegendMarkerY);
		TLine * lineFitEta7TeVNLO = CreateLineFromHisto(histoFitInvCrossSectionEta7TeV,columnsNLOLegend[3]+ offsetNLOLegendMarkerX- offsetNLOLegendLine, rowsNLOLegend[3]+offsetNLOLegendMarkerY, columnsNLOLegend[3]+ offsetNLOLegendMarkerX+ offsetNLOLegendLine,rowsNLOLegend[3]+offsetNLOLegendMarkerY, scaleLineWidthNLO);
		lineFitEta7TeVNLO->Draw("same");
		TLine * lineNLOEta7TeVMuHalf =  CreateLineFromGraph(graphNLOMuHalfEta7TeV, columnsNLOLegend[3]+ offsetNLOLegendMarkerX- offsetNLOLegendLine, rowsNLOLegend[4] + offsetNLOLegendMarkerY, columnsNLOLegend[3]+ offsetNLOLegendMarkerX+ offsetNLOLegendLine, rowsNLOLegend[4]+offsetNLOLegendMarkerY, scaleLineWidthNLO); 
		lineNLOEta7TeVMuHalf->Draw("same");
		TLine * lineNLOEta7TeVMuOne =  CreateLineFromGraph(graphNLOMuOneEta7TeV,columnsNLOLegend[3]+ offsetNLOLegendMarkerX- offsetNLOLegendLine, rowsNLOLegend[5]+offsetNLOLegendMarkerY, columnsNLOLegend[3]+ offsetNLOLegendMarkerX+ offsetNLOLegendLine,rowsNLOLegend[5]+offsetNLOLegendMarkerY, scaleLineWidthNLO); 
		lineNLOEta7TeVMuOne->Draw("same");
		TLine * lineNLOEta7TeVMuTwo =  CreateLineFromGraph(graphNLOMuTwoEta7TeV, columnsNLOLegend[3]+ offsetNLOLegendMarkerX- offsetNLOLegendLine, rowsNLOLegend[6]+offsetNLOLegendMarkerY, columnsNLOLegend[3]+ offsetNLOLegendMarkerX+ offsetNLOLegendLine,rowsNLOLegend[6]+offsetNLOLegendMarkerY, scaleLineWidthNLO); 
		lineNLOEta7TeVMuTwo->Draw("same");
	//************************************************* End Legend ***************************************************
	padXSectionNLORatioPi07TeV->cd();
	padXSectionNLORatioPi07TeV->SetLogx();
	padXSectionNLORatioPi07TeV->SetLogy();
	
	TH2F * ratio2DInvXSectionNLOPi0 = new TH2F("ratio2DInvXSectionNLOPi0","ratio2DInvXSectionNLOPi0",1000,0.23,30.,1000,0.4,3.55);
	SetStyleHistoTH2ForGraphs(ratio2DInvXSectionNLOPi0, "p_{t} (GeV/c)","#frac{NLO}{fit}", 0.13,0.13, 0.175,0.18, 1,0.32, 512, 505);
	ratio2DInvXSectionNLOPi0->DrawCopy(); 
	graphRatioCombNLOPi07TeVMuHalf->SetLineWidth(widthCommonFit);
	graphRatioCombNLOPi07TeVMuHalf->SetLineColor(colorNLOPi07TeVMuHalf);
	graphRatioCombNLOPi07TeVMuHalf->SetLineStyle(styleLineNLOMuHalf);
	graphRatioCombNLOPi07TeVMuHalf->Draw("same,c");
	graphRatioCombNLOPi07TeVMuOne->SetLineWidth(widthCommonFit);
	graphRatioCombNLOPi07TeVMuOne->SetLineColor(colorNLOPi07TeVMuOne);
	graphRatioCombNLOPi07TeVMuOne->SetLineStyle(styleLineNLOMuOne);
	graphRatioCombNLOPi07TeVMuOne->Draw("same,c");
	graphRatioCombNLOPi07TeVMuTwo->SetLineWidth(widthCommonFit);
	graphRatioCombNLOPi07TeVMuTwo->SetLineColor(colorNLOPi07TeVMuTwo);
	graphRatioCombNLOPi07TeVMuTwo->SetLineStyle(styleLineNLOMuTwo);
	graphRatioCombNLOPi07TeVMuTwo->Draw("same,c");
	graphRatioCombNLOBKKPi07TeVMuTwo->Draw("same,c");
	graphRatioCombNLOBKKPi07TeVMuTwo->Draw("same,c");
	
	boxErrorSigmaPi07TeVRatio->Draw();
	
	DrawGammaSetMarkerTGraphAsym(graphRatioCombCombFit, markerStyleCommmonSpectrumPi07TeV,markerSizeCommonSpectrumPi07TeV, colorCommonSpectrumPi07TeV, colorCommonSpectrumPi07TeV, widthCommonSpectrumBoxes, kTRUE);
	graphRatioCombCombFit->SetLineWidth(widthCommonErrors);
	//graphRatioCombCombFit->Draw("p,same");
	graphRatioCombCombFit->Draw("p,E2same");
	
	TLatex *labelLegendB = new TLatex(0.18,0.75,"b)");
	SetStyleTLatex( labelLegendB, 0.17,4);
	labelLegendB->Draw();
		
	DrawGammaLines(0., 30.,1., 1.,0.1);
	
	padXSectionNLORatioPi0900GeV->cd();
	padXSectionNLORatioPi0900GeV->SetLogx();
	padXSectionNLORatioPi0900GeV->SetLogy();
	TH2F * ratio2DInvXSectionNLOPi0900GeV;
	ratio2DInvXSectionNLOPi0900GeV = new TH2F("ratio2DInvXSectionNLOPi0900GeV","ratio2DInvXSectionNLOPi0900GeV",1000,0.23,30.,1000,0.4,3.55);
	SetStyleHistoTH2ForGraphs(ratio2DInvXSectionNLOPi0900GeV, "p_{t} (GeV/c)","#frac{NLO}{fit}", 0.13,0.13, 0.175,0.18, 1,0.32, 512, 505);
	ratio2DInvXSectionNLOPi0900GeV->DrawCopy(); 
	
	graphRatioCombNLOPi0900GeVMuHalf->SetLineWidth(widthCommonFit);
	graphRatioCombNLOPi0900GeVMuHalf->SetLineColor(colorNLOPi0900GeVMuHalf);
	graphRatioCombNLOPi0900GeVMuHalf->SetLineStyle(styleLineNLOMuHalf);
	graphRatioCombNLOPi0900GeVMuHalf->Draw("same,c");
	graphRatioCombNLOPi0900GeVMuOne->SetLineWidth(widthCommonFit);
	graphRatioCombNLOPi0900GeVMuOne->SetLineColor(colorNLOPi0900GeVMuOne);
	graphRatioCombNLOPi0900GeVMuOne->SetLineStyle(styleLineNLOMuOne);
	graphRatioCombNLOPi0900GeVMuOne->Draw("same,c");
	graphRatioCombNLOPi0900GeVMuTwo->SetLineWidth(widthCommonFit);
	graphRatioCombNLOPi0900GeVMuTwo->SetLineColor(colorNLOPi0900GeVMuTwo);
	graphRatioCombNLOPi0900GeVMuTwo->SetLineStyle(styleLineNLOMuTwo);
	graphRatioCombNLOPi0900GeVMuTwo->Draw("same,c");
	graphRatioCombNLOBKKPi0900GeVMuTwo->Draw("same,c");
	
	boxErrorSigmaPi0900GeVRatio->Draw();
	
	DrawGammaSetMarkerTGraphAsym(graphRatioCombCombFit900GeV, markerStyleCommmonSpectrumPi0900GeV,markerSizeCommonSpectrumPi0900GeV, colorCommonSpectrumPi0900GeV, colorCommonSpectrumPi0900GeV, widthCommonSpectrumBoxes, kTRUE);
	graphRatioCombCombFit900GeV->SetLineWidth(widthCommonErrors);
//	graphRatioCombCombFit900GeV->Draw("same,p");
	graphRatioCombCombFit900GeV->Draw("p,E2same");
	
	TLatex *labelLegendC = new TLatex(0.18,0.75,"c)");
	SetStyleTLatex( labelLegendC, 0.17,4);
	labelLegendC->Draw();
		
	DrawGammaLines(0., 30.,1., 1.,0.1);
	
	padXSectionNLORatioEta7TeV->cd();
	padXSectionNLORatioEta7TeV->SetLogx();
	padXSectionNLORatioEta7TeV->SetLogy();
	TH2F * ratio2DInvXSectionNLOEta=  new TH2F("ratio2DInvXSectionNLOEta","ratio2DInvXSectionNLOEta",1000,0.23,30.,1000,0.4,3.55);
	SetStyleHistoTH2ForGraphs(ratio2DInvXSectionNLOEta, "p_{t} (GeV/c)","#frac{NLO}{fit}", 0.12,0.13, 0.125,0.128, 0.9,0.45, 510, 505);
	ratio2DInvXSectionNLOEta->GetXaxis()->SetLabelOffset(-0.03);
	ratio2DInvXSectionNLOEta->DrawCopy(); 

	boxErrorSigmaEta7TeVRatio->Draw();
	
	DrawGammaSetMarkerTGraph(graphRatioCombNLOEta7TeVMuHalf, styleMarkerNLOMuHalf, sizeMarkerNLO, colorNLOEta7TeVMuHalf, colorNLOEta7TeVMuHalf);
	graphRatioCombNLOEta7TeVMuHalf->SetLineWidth(widthCommonFit);
	graphRatioCombNLOEta7TeVMuHalf->SetLineStyle(styleLineNLOMuHalf);
	graphRatioCombNLOEta7TeVMuHalf->Draw("same,c");
	DrawGammaSetMarkerTGraph(graphRatioCombNLOEta7TeVMuOne, styleMarkerNLOMuOne, sizeMarkerNLO, colorNLOEta7TeVMuOne, colorNLOEta7TeVMuOne);
	graphRatioCombNLOEta7TeVMuOne->SetLineWidth(widthCommonFit);
	graphRatioCombNLOEta7TeVMuOne->SetLineStyle(styleLineNLOMuOne);
	graphRatioCombNLOEta7TeVMuOne->Draw("same,c");
	DrawGammaSetMarkerTGraph(graphRatioCombNLOEta7TeVMuTwo, styleMarkerNLOMuTwo, sizeMarkerNLO, colorNLOEta7TeVMuTwo, colorNLOEta7TeVMuTwo);
	graphRatioCombNLOEta7TeVMuTwo->SetLineWidth(widthCommonFit);
	graphRatioCombNLOEta7TeVMuTwo->SetLineStyle(styleLineNLOMuTwo);
	graphRatioCombNLOEta7TeVMuTwo->Draw("same,c");
	
	DrawGammaSetMarkerTGraphAsym(graphRatioCombCombFitEta7TeV,markerStyleCommmonSpectrumEta7TeV,markerSizeCommonSpectrumEta7TeV, colorCommonSpectrumEta7TeV, colorCommonSpectrumEta7TeV, widthCommonSpectrumBoxes, kTRUE);
	graphRatioCombCombFitEta7TeV->SetLineWidth(widthCommonErrors);
	//graphRatioCombCombFitEta7TeV->Draw("same,p");
	graphRatioCombCombFitEta7TeV->Draw("p,E2same");

	TLatex *labelLegendD = new TLatex(0.18,0.85,"d)");
	SetStyleTLatex( labelLegendD, 0.115,4);
	labelLegendD->Draw();
	
	DrawGammaLines(0., 30.,1., 1.,0.1);
	
	canvasInvXSectionNLO->Update();
	canvasInvXSectionNLO->Print(Form("%s/InvXSectionNLO_Paper.%s",outputDir.Data(),suffix.Data()));
	padComparisonXSectionNLO->cd();
	
	histo2DInvXSectionNLO->GetYaxis()->SetRangeUser(2e-4,10e12);
	histo2DInvXSectionNLO->Draw();
	graphInvCrossSectionPi0Comb900GeV->Draw("p,E2same");
	graphInvCrossSectionPi0Comb7TeV->Draw("p,E2same");
	graphInvCrossSectionEtaComb7TeV->Draw("p,E2same");
	fitInvCrossSectionPi0->Draw("same");
	histoFitInvCrossSectionPi0900GeV->Draw("same,c");
	histoFitInvCrossSectionEta7TeV->Draw("same,c");
	graphNLOMuHalfPi07TeV->Draw("same,c");
	graphNLOMuOnePi07TeV->Draw("same,c");
	graphNLOMuTwoPi07TeV->Draw("same,c");
	graphNLOMuHalfPi0900GeV->Draw("same,c");
	graphNLOMuOnePi0900GeV->Draw("same,c");
	graphNLOMuTwoPi0900GeV->Draw("same,c");
	graphNLOMuHalfEta7TeV->Draw("same,c");
	graphNLOMuOneEta7TeV->Draw("same,c");
	graphNLOMuTwoEta7TeV->Draw("same,c");

	labelScalingPi07TeV->Draw();
	labelScalingPi0900GeV->Draw();
	labelScalingEta7TeV->Draw();
	DrawNormalizationErrorText(normalizationInvX3En[0],normalizationInvX3En[1],normalizationInvX3En[2],normalizationInvX3En[3],normalizationInvX3En[4],"No2.76"); 
	
// 	if (onlyConv) {
// 		if(!thesis)DrawAliceLogoPi0EtaPrelim(pictDrawingCoordinatesOnlyCTSMeasCross[0], pictDrawingCoordinatesOnlyCTSMeasCross[1], pictDrawingCoordinatesOnlyCTSMeasCross[2], pictDrawingCoordinatesOnlyCTSMeasCross[3], pictDrawingCoordinatesOnlyCTSMeasCross[4], pictDrawingCoordinatesOnlyCTSMeasCross[5], pictDrawingCoordinatesOnlyCTSMeasCross[6], pictDrawingCoordinatesOnlyCTSMeasCross[7], pictDrawingCoordinates[8],collisionSystemCombined, pictDrawingOptions[1], pictDrawingOptions[2], kTRUE,1200,1220);
// 	} else {
		if(!thesis)DrawAliceLogoPi0WithPHOSPi0EtaPrelim(pictDrawingCoordinatesCombineMeasCross[0], pictDrawingCoordinatesCombineMeasCross[1], pictDrawingCoordinatesCombineMeasCross[2], pictDrawingCoordinatesCombineMeasCross[3], pictDrawingCoordinatesCombineMeasCross[4], pictDrawingCoordinatesCombineMeasCross[5], pictDrawingCoordinatesCombineMeasCross[6], pictDrawingCoordinatesCombineMeasCross[7], pictDrawingCoordinates[8],collisionSystemCombined, pictDrawingOptions[1], pictDrawingOptions[2], kTRUE,1200,1220);
// 	}	
	padComparisonXSectionNLO->cd();
	
	TPad* padXSectionNLOLegend2 = new TPad("padXSectionNLOLegend2", "", 0.17, 0.005, 0.95, 0.19,-1, -1, -2); 
	padXSectionNLOLegend2->Draw();
	padXSectionNLOLegend2->cd();
		textSpectrum->Draw();
		textFitComb->Draw();
		textNLOMuHalf->Draw();
		textNLOMuOne->Draw();
		textNLOMuTwo->Draw();
		textNLOMuTwoBKK->Draw();
		textPi07TeVNLO->Draw();
		textPi07TeVNLOsys->Draw();
		boxCombinedPi07TeV->Draw("l");
		markerCombinedPi07TeV->DrawMarker(columnsNLOLegend[1]+offsetNLOLegendMarkerX,rowsNLOLegend[2]+offsetNLOLegendMarkerY);
		lineFit7TeVNLO->Draw("same");
		lineNLOPi07TeVMuHalf->Draw("same");
		lineNLOPi07TeVMuOne->Draw("same");
		lineNLOPi07TeVMuTwo->Draw("same");
		lineNLOPi07TeVMuTwoBKK->Draw("same");
		textPi0900GeVNLO->Draw();
		textPi0900GeVNLOsys->Draw();
		boxCombinedPi0900GeV->Draw("l");
		markerCombinedPi0900GeV->DrawMarker(columnsNLOLegend[2]+offsetNLOLegendMarkerX,rowsNLOLegend[2]+offsetNLOLegendMarkerY);
		lineFitPi0900GeVNLO->Draw("same");
		lineNLOPi0900GeVMuHalf->Draw("same");
		lineNLOPi0900GeVMuOne->Draw("same");
		lineNLOPi0900GeVMuTwo->Draw("same");
		lineNLOPi0900GeVMuTwoBKK->Draw("same");
		textEta7TeVNLO->Draw();
		textEta7TeVNLOsys->Draw();
		boxCombinedEta7TeV->Draw("l");
		markerCombinedEta7TeV->DrawMarker(columnsNLOLegend[3]+offsetNLOLegendMarkerX,rowsNLOLegend[2]+offsetNLOLegendMarkerY);
		lineFitEta7TeVNLO->Draw("same");
		lineNLOEta7TeVMuHalf->Draw("same");
		lineNLOEta7TeVMuOne->Draw("same");
		lineNLOEta7TeVMuTwo->Draw("same");
	padXSectionNLORatioPi07TeV->cd();
	padXSectionNLORatioPi07TeV->SetLogx();
	padXSectionNLORatioPi07TeV->SetLogy();
	
	ratio2DInvXSectionNLOPi0->DrawCopy(); 
	graphRatioCombNLOPi07TeVMuHalf->Draw("same,c");
	graphRatioCombNLOPi07TeVMuOne->Draw("same,c");
	graphRatioCombNLOPi07TeVMuTwo->Draw("same,c");
	graphRatioCombNLOBKKPi07TeVMuTwo->Draw("same,c");
	boxErrorSigmaPi07TeVRatio->Draw();
	graphRatioCombCombFit->Draw("p,E2same");
	labelRatioNLOPi07TeV->Draw();
	DrawGammaLines(0., 30.,1., 1.,0.1);
	
	padXSectionNLORatioPi0900GeV->cd();
	padXSectionNLORatioPi0900GeV->SetLogx();
	padXSectionNLORatioPi0900GeV->SetLogy();
	ratio2DInvXSectionNLOPi0900GeV->DrawCopy(); 
	graphRatioCombNLOPi0900GeVMuHalf->Draw("same,c");
	graphRatioCombNLOPi0900GeVMuOne->Draw("same,c");
	graphRatioCombNLOPi0900GeVMuTwo->Draw("same,c");
	graphRatioCombNLOBKKPi0900GeVMuTwo->Draw("same,c");
	boxErrorSigmaPi0900GeVRatio->Draw();
	graphRatioCombCombFit900GeV->Draw("p,E2same");
	labelRatioNLOPi0900GeV->Draw();	
	DrawGammaLines(0., 30.,1., 1.,0.1);
	
	padXSectionNLORatioEta7TeV->cd();
	padXSectionNLORatioEta7TeV->SetLogx();
	padXSectionNLORatioEta7TeV->SetLogy();
	ratio2DInvXSectionNLOEta->DrawCopy(); 
	boxErrorSigmaEta7TeVRatio->Draw();
	graphRatioCombNLOEta7TeVMuHalf->Draw("same,c");
	graphRatioCombNLOEta7TeVMuOne->Draw("same,c");
	graphRatioCombNLOEta7TeVMuTwo->Draw("same,c");
	graphRatioCombCombFitEta7TeV->Draw("p,E2same");
	labelRatioNLOEta7TeV->Draw();
	DrawGammaLines(0., 30.,1., 1.,0.1);
	
	canvasInvXSectionNLO->Update();
	canvasInvXSectionNLO->Print(Form("%s/InvXSectionNLO.%s",outputDir.Data(),suffix.Data()));

	
	//***************************************** Only Combined Spectrum Pi0 All Energies **************************************************
	TCanvas* canvasIncXSectionPi0CombinedALLEnergies = new TCanvas("canvasIncXSectionPi0CombinedALLEnergies","",1200,900);  // gives the page size
	DrawGammaCanvasSettings( canvasIncXSectionPi0CombinedALLEnergies, 0.13, 0.02, 0.02, 0.09);
	canvasIncXSectionPi0CombinedALLEnergies->SetLogy();
	canvasIncXSectionPi0CombinedALLEnergies->SetLogx();
	
	TH2F * histo2DInvXSectionPi0CombinedAllEnergies = new TH2F("histo2DInvXSectionPi0CombinedAllEnergies","histo2DInvXSectionPi0CombinedAllEnergies",1000,0.23,30.,1000,2e1,8e12);
	SetStyleHistoTH2ForGraphs(histo2DInvXSectionPi0CombinedAllEnergies, "p_{t} (GeV/c)","E #frac{d^{3}#sigma}{dp^{3}} (pb GeV^{-2} c^{3} )", 0.032,0.04, 0.04,0.04, 1,1.55);
	histo2DInvXSectionPi0CombinedAllEnergies->DrawCopy(); 
	
	graphInvCrossSectionPi0Comb900GeV = ScaleGraph(graphInvCrossSectionPi0Comb900GeV,1e+1);
	DrawGammaSetMarkerTGraphAsym(graphInvCrossSectionPi0Comb900GeV, markerStyleCommmonSpectrum,markerSizeCommonSpectrum, colorCommonSpectrumPi0900GeV, colorCommonSpectrumPi0900GeV, widthCommonSpectrumBoxes, kTRUE);
	graphInvCrossSectionPi0Comb900GeV->SetLineWidth(widthCommonErrors);
	graphInvCrossSectionPi0Comb900GeV->Draw("p,E2same");
	
	DrawGammaSetMarkerTGraphAsym(graphInvCrossSectionPi0Comb2760GeV, markerStyleCommmonSpectrum,markerSizeCommonSpectrum, colorCommonSpectrumPi02760GeV, colorCommonSpectrumPi02760GeV, widthCommonSpectrumBoxes, kTRUE);
	graphInvCrossSectionPi0Comb2760GeV->SetLineWidth(widthCommonErrors);
	graphInvCrossSectionPi0Comb2760GeV->Draw("p,E2same");
	
	DrawGammaSetMarkerTGraphAsym(graphInvCrossSectionPi0Comb7TeV, markerStyleCommmonSpectrum,markerSizeCommonSpectrum, colorCommonSpectrumPi07TeV, colorCommonSpectrumPi07TeV, widthCommonSpectrumBoxes, kTRUE);
	graphInvCrossSectionPi0Comb7TeV->SetLineWidth(widthCommonErrors);
	graphInvCrossSectionPi0Comb7TeV->Draw("p,E2same");
	
	DrawGammaSetMarkerTF1( fitInvCrossSectionPi0, styleFitCommonSpectrum, widthCommonFit, colorCommonSpectrumPi07TeV);
	fitInvCrossSectionPi0->Draw("same");
	
	histoFitInvCrossSectionPi0900GeV->Scale(1e+1);
	histoFitInvCrossSectionPi0900GeV->Draw("same,c");
	
	histoFitInvCrossSectionPi02760GeV->Draw("same,c");
	
/*	DrawBinShiftingText(binshiftingRightMiddle[0], binshiftingRightMiddle[1], binshiftingRightMiddle[2]);  */
	DrawNormalizationErrorText(normalizationInvXCTSALLEn[0],normalizationInvXCTSALLEn[1],normalizationInvXCTSALLEn[2],
						  normalizationInvXCTSALLEn[3],normalizationInvXCTSALLEn[4],"all"); 

	
		TLatex *labelScalingPi07TeVAllEnergiesOnlyCTS = new TLatex(0.25,1.3E11,"x 1");
	SetStyleTLatex( labelScalingPi07TeVAllEnergiesOnlyCTS, 0.028,4,colorCommonSpectrumPi07TeV ,kFALSE);
	labelScalingPi07TeVAllEnergiesOnlyCTS->Draw();

	TLatex *labelScalingPi02760GeVAllEnergiesOnlyCTS = new TLatex(0.31,4E9,"x 10^{-1}");
	SetStyleTLatex( labelScalingPi02760GeVAllEnergiesOnlyCTS, 0.028,4,colorCommonSpectrumPi02760GeV ,kFALSE);
	labelScalingPi02760GeVAllEnergiesOnlyCTS->Draw();

	TLatex *labelScalingPi0900GeVAllEnergiesOnlyCTS = new TLatex(0.31,3E8,"x 10^{-2}");
	SetStyleTLatex( labelScalingPi0900GeVAllEnergiesOnlyCTS, 0.028,4,colorCommonSpectrumPi0900GeV ,kFALSE);
	labelScalingPi0900GeVAllEnergiesOnlyCTS->Draw();
	
	TLegend* legendCombAllPi0 = new TLegend(0.15,0.34,0.4,0.44);
	legendCombAllPi0->SetTextSize(0.028);			
	legendCombAllPi0->SetFillColor(0);
	legendCombAllPi0->SetBorderSize(0);
	legendCombAllPi0->AddEntry(graphInvCrossSectionPi0Comb7TeV,Form("#sqrt{#it{s}} = 7 TeV"),"p");
	legendCombAllPi0->AddEntry(graphInvCrossSectionPi0Comb2760GeV,Form("#sqrt{#it{s}} = 2.76 TeV"),"p");
	legendCombAllPi0->AddEntry(graphInvCrossSectionPi0Comb900GeV,Form("#sqrt{#it{s}} = 0.9 TeV"),"p");
	legendCombAllPi0->Draw();
	
	if(!thesis)DrawAliceLogoPi0WithPHOSPrelim(pictDrawingCoordinatesInvX[0]-0.1, pictDrawingCoordinatesInvX[1]+0.04, pictDrawingCoordinatesInvX[2]-0.16, pictDrawingCoordinatesInvX[3], pictDrawingCoordinatesInvX[4], pictDrawingCoordinatesInvX[5], pictDrawingCoordinatesInvX[6], pictDrawingCoordinatesInvX[7], pictDrawingCoordinates[8],collisionSystemCombinedReallyAll, pictDrawingOptions[1], pictDrawingOptions[2], kTRUE,1200,900);
	
	canvasIncXSectionPi0CombinedALLEnergies->Update();	
	canvasIncXSectionPi0CombinedALLEnergies->SaveAs(Form("%s/Pi0_InvXSectionCombinedSpectraAllEnergies.%s",outputDir.Data(),suffix.Data()));


	//***************************************** Only Combined Spectrum Eta All Energies **************************************************
	TCanvas* canvasIncXSectionEtaCombinedALLEnergies = new TCanvas("canvasIncXSectionEtaCombinedALLEnergies","",1200,900);  // gives the page size
	DrawGammaCanvasSettings( canvasIncXSectionEtaCombinedALLEnergies, 0.13, 0.02, 0.02, 0.09);
	canvasIncXSectionEtaCombinedALLEnergies->SetLogy();
	canvasIncXSectionEtaCombinedALLEnergies->SetLogx();
	
	TH2F * histo2DInvXSectionEtaCombinedAllEnergies = new TH2F("histo2DInvXSectionEtaCombinedAllEnergies","histo2DInvXSectionEtaCombinedAllEnergies",1000,0.23,30.,1000,1e2,4e11);
	SetStyleHistoTH2ForGraphs(histo2DInvXSectionEtaCombinedAllEnergies, "p_{t} (GeV/c)","E #frac{d^{3}#sigma}{dp^{3}} (pb GeV^{-2} c^{3} )", 0.032,0.04, 0.04,0.04, 1,1.55);
	histo2DInvXSectionEtaCombinedAllEnergies->DrawCopy(); 
	
	graphInvCrossSectionEtaComb900GeV = ScaleGraph(graphInvCrossSectionEtaComb900GeV,1e+1);
	DrawGammaSetMarkerTGraphAsym(graphInvCrossSectionEtaComb900GeV, markerStyleCommmonSpectrum,markerSizeCommonSpectrum, colorCommonSpectrumPi0900GeV, colorCommonSpectrumPi0900GeV, widthCommonSpectrumBoxes, kTRUE);
	graphInvCrossSectionEtaComb900GeV->SetLineWidth(widthCommonErrors);
	graphInvCrossSectionEtaComb900GeV->Draw("p,E2same");
	
	DrawGammaSetMarkerTGraphAsym(graphInvCrossSectionEtaComb2760GeV, markerStyleCommmonSpectrum,markerSizeCommonSpectrum, colorCommonSpectrumPi02760GeV, colorCommonSpectrumPi02760GeV, widthCommonSpectrumBoxes, kTRUE);
	graphInvCrossSectionEtaComb2760GeV->SetLineWidth(widthCommonErrors);
	graphInvCrossSectionEtaComb2760GeV->Draw("p,E2same");
	
	DrawGammaSetMarkerTGraphAsym(graphInvCrossSectionEtaComb7TeV, markerStyleCommmonSpectrum,markerSizeCommonSpectrum, colorCommonSpectrumPi07TeV, colorCommonSpectrumPi07TeV, widthCommonSpectrumBoxes, kTRUE);
	graphInvCrossSectionEtaComb7TeV->SetLineWidth(widthCommonErrors);
	graphInvCrossSectionEtaComb7TeV->Draw("p,E2same");
	
	DrawGammaSetMarkerTF1( fitInvCrossSectionEta7TeV, styleFitCommonSpectrum, widthCommonFit, colorCommonSpectrumPi07TeV);
	fitInvCrossSectionEta7TeV->Draw("same");
	
	histoFitInvCrossSectionEta900GeV->Scale(1e+1);
	histoFitInvCrossSectionEta900GeV->Draw("same,c");
	
	histoFitInvCrossSectionEta2760GeV->Draw("same,c");
	
/*	DrawBinShiftingText(binshiftingRightMiddle[0], binshiftingRightMiddle[1], binshiftingRightMiddle[2]);  */
	DrawNormalizationErrorText(normalizationInvXCTSALLEn[0],normalizationInvXCTSALLEn[1],normalizationInvXCTSALLEn[2],
						  normalizationInvXCTSALLEn[3],normalizationInvXCTSALLEn[4],"all"); 

	
	TLatex *labelScalingEta7TeVAllEnergiesOnlyCTS = new TLatex(0.35,5E9,"x 1");
	SetStyleTLatex( labelScalingEta7TeVAllEnergiesOnlyCTS, 0.028,4,colorCommonSpectrumPi07TeV,kFALSE);
	labelScalingEta7TeVAllEnergiesOnlyCTS->Draw();
	
	TLatex *labelScalingEta2760GeVAllEnergiesOnlyCTS = new TLatex(0.46,2E8,"x 10^{-1}");
	SetStyleTLatex( labelScalingEta2760GeVAllEnergiesOnlyCTS, 0.028,4,colorCommonSpectrumPi02760GeV,kFALSE);
	labelScalingEta2760GeVAllEnergiesOnlyCTS->Draw();

	TLatex *labelScalingEta900GeVAllEnergiesOnlyCTS = new TLatex(0.71,4E6,"x 10^{-2}");
	SetStyleTLatex( labelScalingEta900GeVAllEnergiesOnlyCTS, 0.028,4,colorCommonSpectrumPi0900GeV,kFALSE);
	labelScalingEta900GeVAllEnergiesOnlyCTS->Draw();
	
	TLegend* legendCombAllEta = new TLegend(0.15,0.34,0.4,0.44);
	legendCombAllEta->SetTextSize(0.028);			
	legendCombAllEta->SetFillColor(0);
	legendCombAllEta->SetBorderSize(0);
	legendCombAllEta->AddEntry(graphInvCrossSectionEtaComb7TeV,Form("#sqrt{#it{s}} = 7 TeV"),"p");
	legendCombAllEta->AddEntry(graphInvCrossSectionEtaComb2760GeV,Form("#sqrt{#it{s}} = 2.76 TeV"),"p");
	legendCombAllEta->AddEntry(graphInvCrossSectionEtaComb900GeV,Form("#sqrt{#it{s}} = 0.9 TeV"),"p");
	legendCombAllEta->Draw();
	
	if(!thesis)DrawAliceLogoPi0WithPHOSPrelim(pictDrawingCoordinatesInvX[0]-0.1, pictDrawingCoordinatesInvX[1]+0.04, pictDrawingCoordinatesInvX[2]-0.16, pictDrawingCoordinatesInvX[3], pictDrawingCoordinatesInvX[4], pictDrawingCoordinatesInvX[5], pictDrawingCoordinatesInvX[6], pictDrawingCoordinatesInvX[7], pictDrawingCoordinates[8],collisionSystemCombinedReallyAll, pictDrawingOptions[1], pictDrawingOptions[2], kFALSE,1200,900);
	
	canvasIncXSectionEtaCombinedALLEnergies->Update();	
	canvasIncXSectionEtaCombinedALLEnergies->SaveAs(Form("%s/Eta_InvXSectionCombinedSpectraAllEnergies.%s",outputDir.Data(),suffix.Data()));


	