

# root -l -b -x -q TaskV1/BuildHistogramsForMaterial.C\+\+\(\"$2/GammaConvV1_Material_$1.root\"\,\"$5\"\,0\,0\,\"MappingDetailedGammaConv_LHC11aPass2_$1\"\)
# root -l -b -x -q TaskV1/BuildHistogramsForMaterial.C\+\+\(\"$3/GammaConvV1_Material_$1.root\"\,\"$5\"\,1\,0\,\"MappingDetailedGammaConv_LHC12e6_Pythia6_$1\"\)
#  
# root -l -b -q -x TaskV1/BuildHistogramsForGammaQA.C\+\+\(\"$2/GammaConvV1_QA_$1.root\"\,\"$5_$1\"\,0\,0\,\"PhotonQA_LHC11aPass2_$1\"\)
# root -l -b -q -x TaskV1/BuildHistogramsForGammaQA.C\+\+\(\"$3/GammaConvV1_QA_$1.root\"\,\"$5_$1\"\,1\,0\,\"PhotonQA_LHC12e6_Pythia6_$1\"\)


root -l -q -x -b TaskV1/MappingMaterialTree.C\+\+\(\"MappingDetailedGammaConv_LHC11aPass2_$1_Data.root\"\,\"MappingDetailedGammaConv_LHC12e6_Pythia6_$1_MC.root\"\,\"$5_$1\"\,\"Mapping\"\,\"$4\"\,\"\"\,\"2.76TeV\"\,\"Pythia6\"\,\"LHC11a\"\,\"thesis\"\)

root -l -q -b -x TaskV1/PhotonQA.C\+\+\(\"PhotonQA_LHC11aPass2_$1_Data.root\"\,\"PhotonQA_LHC12e6_Pythia6_$1_MC.root\"\,\"$5_$1\"\,\"$4\"\,\"2.76TeV\"\,\"Pythia6\"\,\"LHC11a\"\)
