//***************** This Header is used to add an additional Plot
//***************** For the Gaussian Fit in Mode 4

// Using an different Fitrange for Mode 4
Double_t LinearBGExclusionnew(Double_t *x, Double_t *par) {
    if (x[0] > fBGFitRangeLeft[1] && x[0] < fBGFitRange[0]) {
        TF1::RejectPoint();
        return 0;
    } 
    if (x[0] < fBGFitRangeLeft[0]) {
        TF1::RejectPoint();
        return 0;
    } 
    if (x[0] > fBGFitRange[1]) {
        TF1::RejectPoint();
        return 0;
    } 
    return par[0] + par[1]*x[0];
}

// Variing the Integration range for different Pt Slices
void changeParamHighPt(Int_t fmode, Int_t iPt, Int_t binnum){

    if(fmode==4 && iPt <=binnum){
        Double_t arrayUp[30] = {0.05,0.05,0.05,0.045,0.04,0.04,0.04,0.04,0.04,0.04,0.035,0.035,0.035,0.035,0.035,0.035,0.03,0.03,0.03,0.03,0.03,0.03,0.03,0.03,0.04,0.045,0.045,0.05,0.06,0.07};

        fMesonIntDeltaRange[0]          = -0.05;
        fMesonIntDeltaRange[1]          = arrayUp[iPt];
        fMesonIntDeltaRangeWide[0]      = fMesonIntDeltaRange[0]*1.5; 
        fMesonIntDeltaRangeWide[1]      = fMesonIntDeltaRange[1]*1.5;
        fMesonIntDeltaRangeNarrow[0]    = fMesonIntDeltaRange[0]*0.5;
        fMesonIntDeltaRangeNarrow[1]    = fMesonIntDeltaRange[1]*0.5;
    }
}

