void PlotStandard2D( TH2* histo2D, TString nameOutput, TString title, TString xTitle, TString yTitle, TString zTitle, Bool_t kRangeX, Double_t startX, Double_t endX, Bool_t kRangeY, Double_t startY, Double_t endY,  Bool_t kRangeZ, Double_t startZ, Double_t endZ, Int_t logX, Int_t logY, Int_t logZ, Float_t* floatLogo, Int_t canvasSizeX = 500, Int_t canvasSizeY = 500, Double_t rightMargin = 0.12, Double_t leftMargin = 0.12, Double_t bottomMargin = 0.1, Double_t topMargin = 0.04, TString drawLogo ="Perf", TString option2DPlot = "SURF2", TString addInfo = ""){
	TLatex *alice;
	if (addInfo.CompareTo("") != 0){
		alice = new TLatex(0.05,0.94,addInfo.Data());
	}
	
	TCanvas * canvasStandard = new TCanvas("canvasStandard","",10,10,canvasSizeX,canvasSizeY);  // gives the page size		
	canvasStandard->SetLogx(logX);
	canvasStandard->SetLogz(logZ);
	canvasStandard->SetLogy(logY);
	canvasStandard->SetRightMargin(rightMargin); 		
	canvasStandard->SetLeftMargin(leftMargin); 		
	canvasStandard->SetBottomMargin(bottomMargin); 		
	canvasStandard->SetTopMargin(topMargin); 		
	canvasStandard->cd();
	if (kRangeZ){
		histo2D->GetZaxis()->SetRangeUser(startZ,endZ);
	}
	DrawHistoCorrelationSurf2D(	histo2D,
									title.Data(), xTitle.Data(), yTitle.Data(),zTitle.Data(),kRangeY, startY, endY, kRangeX, startX, endX, option2DPlot.Data());
	if (addInfo.CompareTo("") != 0){
		alice->SetNDC();
		alice->SetTextColor(1);
		alice->SetTextSize(0.035);
		alice->Draw();

	}
// 	if(!thesis){
// 		if (drawLogo.CompareTo("Perf")==0) DrawAliceLogoPerformance(floatLogo[0],floatLogo[1],floatLogo[2],floatLogo[3],0.00, textDate,collisionSystem, "","",canvasSizeX,canvasSizeY);	
// 		if (drawLogo.CompareTo("Wip")==0)DrawAliceLogo(floatLogo[0],floatLogo[1],floatLogo[2],floatLogo[3],canvasSizeX,canvasSizeY);	
// 	}
	canvasStandard->Update();
	canvasStandard->SaveAs(nameOutput.Data());
	delete canvasStandard;
	if (addInfo.CompareTo("") != 0){
		delete alice;
	}
}

void PlotStandard1D( TH1* histo1D, TString nameOutput, TString title, TString xTitle, TString yTitle, Bool_t kRangeX, Double_t startX, Double_t endX, Bool_t kRangeY, Double_t startY, Double_t endY, Bool_t kRangeYMax, Int_t logX, Int_t logY, Float_t* floatLogo, Int_t canvasSizeX = 500, Int_t canvasSizeY = 500, Double_t rightMargin = 0.12, Double_t leftMargin = 0.12, Double_t bottomMargin = 0.1, Double_t topMargin = 0.04, TString drawLogo ="Perf"){
	TCanvas * canvasStandard = new TCanvas("canvasStandard","",10,10,canvasSizeX,canvasSizeY);  // gives the page size		
	canvasStandard->SetLogx(logX);
	canvasStandard->SetLogy(logY);
	canvasStandard->SetRightMargin(rightMargin); 		
	canvasStandard->SetLeftMargin(leftMargin); 		
	canvasStandard->SetBottomMargin(bottomMargin); 		
	canvasStandard->SetTopMargin(topMargin); 		
	canvasStandard->cd();
	DrawCorrelationHisto1D( histo1D, title.Data(), xTitle.Data(), yTitle.Data(), 
									kRangeYMax, startY, endY,
									kRangeY, startY, endY,
									kRangeX, startX, endX);
// 	if(!thesis){
// 		if (drawLogo.CompareTo("Perf")==0) DrawAliceLogoPerformance(floatLogo[0],floatLogo[1],floatLogo[2],floatLogo[3],0.00, textDate,collisionSystem, "","",canvasSizeX,canvasSizeY);	
// 		if (drawLogo.CompareTo("Wip")==0)DrawAliceLogo(floatLogo[0],floatLogo[1],floatLogo[2],floatLogo[3],canvasSizeX,canvasSizeY);	
// 	}
	canvasStandard->Update();
	canvasStandard->SaveAs(nameOutput.Data());
	delete canvasStandard;
}

void DrawCorrelation3Histos( TH1* histo1, 
									TH1*histo2, 
					 TH1*histo3, 
					 TString Title, TString XTitle, TString YTitle,
					 Bool_t YRangeMax, Float_t YMaxFactor, Float_t YMinimum, 
					 Bool_t YRange, Float_t YMin ,Float_t YMax, 
					 Bool_t XRange, Float_t XMin, Float_t XMax) {
	if (YRangeMax && !XRange){
		YRange = kFALSE;
		Double_t maxRangeR = histo1->GetMaximum();
		if(maxRangeR < histo2->GetMaximum()){
			maxRangeR = histo2->GetMaximum();
		}
		Double_t minRangeR = histo3->GetMinimum();		
		histo1->GetYaxis()->SetRangeUser(minRangeR, maxRangeR*YMaxFactor);	
	}
	if (YRangeMax && XRange){
		YRange = kFALSE;
		Double_t maxRangeR = histo1->GetMaximum();
		if(maxRangeR < histo2->GetMaximum()){
			maxRangeR = histo2->GetMaximum();
		}
		Double_t minRangeR = histo3->GetMinimum();		
		histo1->GetYaxis()->SetRangeUser(minRangeR, maxRangeR*YMaxFactor);	
		histo1->GetXaxis()->SetRangeUser(XMin, XMax);	
	}
	if (YRange && XRange){
		histo1->GetYaxis()->SetRangeUser(YMin, YMax);	
		histo1->GetXaxis()->SetRangeUser(XMin, XMax);	
	}
	if (!YRangeMax && !YRange && XRange){
		histo1->GetXaxis()->SetRangeUser(XMin, XMax);	
	}
	if (YRange && !XRange){
		histo1->GetYaxis()->SetRangeUser(YMin, YMax);
	}
	
	if(Title.CompareTo("") != 0){
		histo1->SetTitle(Title.Data());
	}else{histo1->SetTitle("");
	histo2->SetTitle("");}
	if(XTitle.CompareTo("") != 0){
		histo1->SetXTitle(XTitle.Data());
	}
	if(YTitle.CompareTo("") != 0){
		histo1->SetYTitle(YTitle.Data());
	}
	DrawGammaSetMarker(histo1, 20, 1.5, kBlack, kBlack);
	DrawGammaSetMarker(histo2, 21, 1.5, kRed+2, kRed+2);
	DrawGammaSetMarker(histo3, 22, 1.5, kGreen+3, kGreen+3);
	histo1->GetYaxis()->SetLabelSize(0.035);
	histo1->GetYaxis()->SetTitleSize(0.04);	
	histo1->GetYaxis()->SetDecimals();
	histo1->GetYaxis()->SetTitleOffset(1.5);
	histo1->GetXaxis()->SetTitleSize(0.04);	
	histo1->GetXaxis()->SetLabelSize(0.035);
	histo1->DrawCopy("e1,p");
	histo2->SetLineColor(kRed+2);
	histo2->DrawCopy("e1,p,same");
	histo3->SetLineColor(kGreen+3);
	histo3->Draw("same,pe1");
	histo1->DrawCopy("same,axis");	
}

void DrawCorrHisto( TH1* histo1,
				 TString Title, TString XTitle, TString YTitle) {
	
	if(Title.Length() > 0){
		histo1->SetTitle(Form("%s",Title.Data()));
		histo1->SetTitleSize(0.08);
// 		TLatex *alice = new TLatex(0.1,0.95,Form("%s",Title.Data())); // Bo: this was 
// 		alice->SetNDC();
// 		alice->SetTextColor(1);
// 		alice->SetTextSize(0.062);
// 		alice->Draw();		
	}
	if(XTitle.Length() > 0){
		histo1->SetXTitle(XTitle.Data());
	}
	if(YTitle.Length() > 0){
		histo1->SetYTitle(YTitle.Data());
	}
	histo1->GetYaxis()->SetDecimals();
	histo1->GetYaxis()->SetTitleOffset(1.);
	histo1->GetXaxis()->SetTitleOffset(0.7);
	histo1->SetMarkerStyle(20);
	histo1->SetMarkerColor(1);
	histo1->SetLineColor(1);
	histo1->SetLineWidth(0.5);
	histo1->SetMarkerSize(0.2);
	histo1->SetTitleSize(0.05,"xy");		
	histo1->GetYaxis()->SetLabelSize(0.05);
	histo1->GetXaxis()->SetLabelSize(0.05);
	histo1->GetXaxis()->SetNdivisions(507,kTRUE);
	histo1->DrawCopy("e1,p");
}
