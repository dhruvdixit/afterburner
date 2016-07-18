

# root -l -b -x -q TaskV1/BuildHistogramsForMaterial.C\+\+\(\"$2/GammaConvV1_Material_$1.root\"\,\"$6\"\,0\,0\,\"MappingDetailedGammaConv_LHC11aPass4_$1\"\)
# root -l -b -x -q TaskV1/BuildHistogramsForMaterial.C\+\+\(\"$3/GammaConvV1_Material_$1.root\"\,\"$6\"\,1\,0\,\"MappingDetailedGammaConv_LHC12f1a_Pythia8_$1\"\)
# root -l -b -x -q TaskV1/BuildHistogramsForMaterial.C\+\+\(\"$4/GammaConvV1_Material_$1.root\"\,\"$6\"\,1\,0\,\"MappingDetailedGammaConv_LHC12f1b_Phojet_$1\"\)
#  
# root -l -b -q -x TaskV1/BuildHistogramsForGammaQA.C\+\+\(\"$2/GammaConvV1_QA_$1.root\"\,\"$6_$1\"\,0\,0\,\"PhotonQA_LHC11aPass4_$1\"\)
# root -l -b -q -x TaskV1/BuildHistogramsForGammaQA.C\+\+\(\"$3/GammaConvV1_QA_$1.root\"\,\"$6_$1\"\,1\,0\,\"PhotonQA_LHC12f1a_Pythia8_$1\"\)
# root -l -b -q -x TaskV1/BuildHistogramsForGammaQA.C\+\+\(\"$4/GammaConvV1_QA_$1.root\"\,\"$6_$1\"\,1\,0\,\"PhotonQA_LHC12f1b_Phojet_$1\"\)


root -l -q -x -b TaskV1/MappingMaterialTree.C\+\+\(\"MappingDetailedGammaConv_LHC11aPass4_$1_Data.root\"\,\"MappingDetailedGammaConv_LHC12f1a_Pythia8_$1_MC.root\"\,\"$6_$1\"\,\"Mapping\"\,\"$5\"\,\"\"\,\"2.76TeV\"\,\"Pythia8\"\,\"LHC11a\"\,\"thesis\"\)
root -l -q -x -b TaskV1/MappingMaterialTree.C\+\+\(\"MappingDetailedGammaConv_LHC11aPass4_$1_Data.root\"\,\"MappingDetailedGammaConv_LHC12f1b_Phojet_$1_MC.root\"\,\"$6_$1\"\,\"Mapping\"\,\"$5\"\,\"\"\,\"2.76TeV\"\,\"Phojet\"\,\"LHC11a\"\,\"thesis\"\)

root -l -q -b -x TaskV1/PhotonQA.C\+\+\(\"PhotonQA_LHC11aPass4_$1_Data.root\"\,\"PhotonQA_LHC12f1b_Phojet_$1_MC.root\"\,\"$6_$1\"\,\"$5\"\,\"2.76TeV\"\,\"Phojet\"\,\"LHC11a\"\)
root -l -q -b -x TaskV1/PhotonQA.C\+\+\(\"PhotonQA_LHC11aPass4_$1_Data.root\"\,\"PhotonQA_LHC12f1a_Pythia8_$1_MC.root\"\,\"$6_$1\"\,\"$5\"\,\"2.76TeV\"\,\"Pythia8\"\,\"LHC11a\"\)
