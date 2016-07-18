//=============================
//0-10% Low is 0% while high is 10%
//=============================

Double_t pt[25]={
    0, 0.2, 0.4, 0.6, 0.8,
    1, 1.2, 1.4, 1.6, 1.8,
    2, 2.2, 2.4, 2.6, 2.8,
    3, 3.2, 3.4, 3.6, 3.8,
    4, 4.2, 4.4, 4.6, 4.8
};

Double_t charged010Mean[25]=
{
2651.81,   922.389,   339.035,    149.662,   72.2559,
36.8001,   19.4429,   10.5857,    5.89492,   3.32243,
1.90615,   1.1121,    0.650655,   0.381061,  0.231155,
0.13488,   0.0834954, 0.0493845,  0.0299603, 0.0180096,
0.0109032, 0.0071005, 0.00400082, 0.00270064,0.00159955
};

Double_t charged0Low[25]=
{
3140.83,  1093.92,   401.887,   177.373,   85.5725,
43.5416,  23.08,     12.5286,   6.9714,    3.93781,
2.25503,  1.30904,   0.769396,  0.455113,  0.267651,
0.159689, 0.0978393, 0.0590062, 0.0344751, 0.0217545,
0.0137536,0.00826068,0.00487104,0.00297516,0.00199068
};


Double_t charged10High[25]=
{
2200.06,   766.871,   281.66,    124.466,   60.1079,
30.65,     16.1822,   8.81206,   4.91249,   2.76753,
1.59168,   0.926406,  0.542096,  0.321615,  0.191594,
0.113799,  0.0683475, 0.0418038, 0.0248896, 0.0151789,
0.00970913,0.00561189,0.00332789,0.00216143,0.00124687
  };

Double_t pion010Mean[25]=
{
3247.13,   1008.98,   352.271,  153.222,  73.4168, 37.1526,
19.6458,   10.6783,   5.89825,  3.3531,   1.91626, 1.10949,
0.655872,  0.384887,  0.230378, 0.136688, 0.0819331,
0.0512445, 0.03016,   0.0181228,0.0113739,0.0069163,
0.00437672,0.00255106,0.00159881,
};

Double_t pion0Low[25]=
{
3832.55,   1195.47,   418.052,   181.558,   87.106,
44.1134,   23.3039,   12.6271,   7.00505,   3.95652,
2.28616,   1.31271,   0.770445,  0.456607,  0.273074,
0.159152,  0.0987644, 0.0607644, 0.0369101, 0.0220315,
0.0131346, 0.00833841,0.00527854,0.00291318,0.00177405
};

Double_t pion10High[25]=
{
2707.32,   838.414,   293.294,   127.63,    61.0826,
31.0063,   16.3382,   8.87333,   4.94463,   2.78508,
1.60362,   0.930789,  0.545243,  0.321535,  0.190514,
0.114968,  0.0687716, 0.042989,  0.0266507, 0.015583,
0.00964065,0.00564281,0.00375394,0.00231828,0.00163958
};


Double_t eta010Mean[25]=
{
24.0813,    20.8763,    15.844,     10.8357,    7.04125,
4.413,      2.75275,    1.66296,    1.02622,    0.633945,
0.386125,   0.242506,   0.149575,   0.0915417,  0.0573065,
0.0364585,  0.0206418,  0.0132958,  0.00844679, 0.00551169,
0.00332149, 0.00202383, 0.00126882, 0.00074311, 0.000566151
};



Double_t eta0Low[25]=
{
28.392,     24.6793,    18.7162,   12.9032,    8.32879,
5.24177,    3.24664,    1.99381,    1.21254,    0.753975,
0.464038,   0.285012,   0.173956,   0.109233,   0.0665855,
0.0425219,  0.0259506,  0.0156612,  0.0101212,  0.00610143,
0.00398349, 0.00242425, 0.00151082, 0.000743023,0.000672448
};


Double_t eta10High[25]=
{
20.3836,   17.4615,  13.1967,   9.04443,    5.83888,
3.68066,   2.30024,  1.40429,   0.864149,   0.53148,
0.325293,  0.201299, 0.1248,    0.0788187,  0.0484488,
0.0304845, 0.0182083,0.0113415, 0.00720322, 0.00440049,
0.00310005,0.0013477,0.00121608,0.000837337,0.000346279
};

//=============================
//20-50% Low is 20% while high is 50%
//=============================


Double_t charged2050Mean[25]=
{
841.792,   293.649,  108.563,   47.9871,   23.1539,
11.8415,   6.26131,  3.41434,   1.90192,   1.07935,
0.624021,  0.359306, 0.21225,   0.124509,  0.0757538,
0.0452875, 0.0273524,0.0161586, 0.00987804,0.00616362,
0.00372047,0.0023435,0.00147623,0.00090453,0.000514578
};

Double_t charged20Low[25]=
{
 1498.46,    522.477,    192.636,    85.0673,    41.1688,
 20.983,     11.1232,    6.06981,    3.37033,    1.91255,
 1.10312,    0.641435,   0.373367,   0.220711,   0.130695,
 0.0795254,  0.0478819,  0.0293038,  0.0171601,  0.0103708,
 0.00652849, 0.00401317, 0.00249573, 0.00159027, 0.000955238
};


Double_t charged50High[25]=
{
377.991,   131.094,    48.2368,    21.1732,    10.1414,
5.13039,   2.69641,    1.4571,     0.80475,    0.452809,
0.257851,  0.148852,   0.0868046,  0.0507479,  0.0301603,
0.0177707, 0.0108011,  0.00643111, 0.00389238, 0.00234543,
0.00144449,0.000845276,0.000511543,0.000340329,0.000211092
};

Double_t pion2050Mean[25]=
{
 1035.34,   321.724,   112.862,   49.1901,    23.5999,
 12.0037,   6.33956,   3.43158,   1.92006,    1.08701,
 0.623077,  0.363918,  0.21417,   0.126807,   0.0752206,
 0.0451259, 0.0277777, 0.0159632, 0.00954624, 0.00611817,
 0.00406999,0.00234165,0.00141776,0.000836132,0.000587706
};

Double_t pion20Low[25]=
{
 1853.05,    572.927,    200.431,    87.2475,    41.7805,
 21.2966,    11.2302,    6.1083,     3.38844,    1.91945,
 1.10121,    0.648199,   0.377053,   0.219845,   0.135229,
 0.0802143,  0.0477578,  0.0285435,  0.0171148,  0.0106176,
 0.00715895, 0.00384404, 0.00259265, 0.00153531, 0.000955702
};

Double_t pion50High[25]=
{
462.262,   142.819,    50.222,      21.6935,   10.302,
5.18859,   2.71836,    1.46792,    0.807876,   0.453139,
0.260482,  0.150383,   0.0880749,  0.0512848,  0.0301803,
0.0180367, 0.0107847,  0.00650864, 0.00378235, 0.00231245,
0.00152585,0.000884165,0.000539348,0.000310959,0.000220087
};


Double_t eta2050Mean[25]=
{
8.03078,   6.87598,    5.23854,    3.58492,   2.31688,
1.46198,   0.903876,   0.559657,   0.339126,  0.209968,
0.12852,   0.0801396,  0.0497238,  0.0305908, 0.0187917,
0.0118665, 0.00766455, 0.00447123, 0.00290857,0.00173256,
0.00101533,0.000736554,0.000477104,0.00025866,0.000262153
};



Double_t eta20Low[25]=
{
 13.671,     12.0395,    9.13334,     6.24784,     4.04751,
 2.56484,    1.57292,    0.967552,    0.601505,    0.368571,
 0.229673,   0.138933,   0.0871805,   0.0540491,   0.0328287,
 0.0201466,  0.0132529,  0.00760374,  0.0049839,   0.00350279,
 0.00194656, 0.00128671, 0.000831575, 0.000455258, 0.00039639
};


Double_t eta50High[25]=
 {
3.91714,    3.29214,    2.45987,    1.65601,    1.05657,
0.651794,   0.400534,   0.24407,    0.149082,   0.0903598,
0.055065,   0.0342466,  0.0207141,  0.0128285,  0.00776766,
0.00473873, 0.00297433, 0.00188237, 0.00113268, 0.000655391,
0.000422583,0.000264178,0.000145109,9.28514e-05,6.33193e-05
};















