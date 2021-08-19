Inst_FunCall_start = 1;
Inst_FunCall_end = 6;
Inst_Ret_start = 7;
Inst_Ret_end = 12;
Inst_Br_start = 13;
Inst_Br_end = 16;
Inst_Other_start = 17;
Inst_Other_end = 63;
Inst_start = 1;
Inst_end = 63;
VarNode_StaticGlobal_start = 0;
VarNode_StaticGlobal_end = -1;
VarNode_StaticModule_start = 0;
VarNode_StaticModule_end = -1;
VarNode_StaticFunction_start = 64;
VarNode_StaticFunction_end = 66;
VarNode_StaticOther_start = 0;
VarNode_StaticOther_end = -1;
VarNode_start = 64;
VarNode_end = 66;
FunctionEntry_start = 67;
FunctionEntry_end = 72;
Param_FormalIn_start = 73;
Param_FormalIn_end = 75;
Param_FormalOut_start = 76;
Param_FormalOut_end = 78;
Param_ActualIn_start = 79;
Param_ActualIn_end = 81;
Param_ActualOut_start = 82;
Param_ActualOut_end = 84;
Param_start = 73;
Param_end = 84;
Annotation_Var_start = 85;
Annotation_Var_end = 85;
Annotation_Global_start = 86;
Annotation_Global_end = 86;
Annotation_Other_start = 0;
Annotation_Other_end = -1;
Annotation_start = 85;
Annotation_end = 86;
PDGNode_start = 1;
PDGNode_end = 86;
ControlDep_CallInv_start = 1;
ControlDep_CallInv_end = 5;
ControlDep_CallRet_start = 6;
ControlDep_CallRet_end = 10;
ControlDep_Entry_start = 11;
ControlDep_Entry_end = 73;
ControlDep_Br_start = 74;
ControlDep_Br_end = 85;
ControlDep_Other_start = 0;
ControlDep_Other_end = -1;
ControlDep_start = 1;
ControlDep_end = 85;
DataDepEdge_DefUse_start = 86;
DataDepEdge_DefUse_end = 142;
DataDepEdge_RAW_start = 143;
DataDepEdge_RAW_end = 151;
DataDepEdge_Ret_start = 152;
DataDepEdge_Ret_end = 156;
DataDepEdge_Alias_start = 157;
DataDepEdge_Alias_end = 157;
DataDepEdge_start = 86;
DataDepEdge_end = 157;
Parameter_In_start = 158;
Parameter_In_end = 172;
Parameter_Out_start = 173;
Parameter_Out_end = 181;
Parameter_Field_start = 0;
Parameter_Field_end = -1;
Parameter_start = 158;
Parameter_end = 181;
Anno_Global_start = 182;
Anno_Global_end = 184;
Anno_Var_start = 185;
Anno_Var_end = 186;
Anno_Other_start = 0;
Anno_Other_end = -1;
Anno_start = 182;
Anno_end = 186;
PDGEdge_start = 1;
PDGEdge_end = 186;
hasFunction = [
67,67,71,71,71,72,67,68,69,70,71,72,71,71,71,71,67,67,67,67,
67,67,69,68,68,68,68,68,69,69,69,69,69,69,69,69,69,69,69,69,
69,69,70,70,70,70,71,71,71,71,71,71,71,71,71,71,71,71,71,71,
71,72,72,0,0,0,67,68,69,70,71,72,67,69,69,67,69,69,69,69,
67,69,69,67,71,0
];
hasSource = [
1,2,3,4,6,7,8,9,10,11,67,67,67,67,67,67,67,67,67,68,
68,68,68,68,68,69,69,69,69,69,69,69,69,69,69,69,69,69,69,69,
69,70,70,70,70,70,71,71,71,71,71,71,71,71,71,71,71,71,71,71,
71,71,71,71,71,71,71,71,71,72,72,72,72,14,14,14,14,14,14,14,
14,14,14,14,14,64,64,64,65,65,65,65,66,66,66,17,17,18,18,1,
21,22,2,24,25,26,28,29,29,30,30,31,34,35,36,37,38,39,40,42,
43,44,46,47,47,49,49,49,50,50,50,50,53,54,3,56,4,58,59,60,
62,6,19,20,27,32,33,41,45,55,57,7,8,9,10,11,51,73,67,21,
22,2,2,69,69,74,75,56,4,79,80,81,67,2,2,69,69,4,82,83,
84,64,65,67,71,51
];
hasDest = [
68,69,70,67,71,4,1,2,3,6,18,19,1,20,21,22,2,7,17,25,
26,27,28,8,24,29,30,31,32,33,23,34,35,36,37,38,39,40,41,42,
9,44,45,46,10,43,47,48,49,50,51,52,13,53,54,14,3,55,56,4,
57,58,5,15,59,60,61,16,11,62,63,6,12,3,55,56,4,57,58,5,
15,59,60,61,16,46,45,43,28,27,25,24,42,41,38,21,19,22,20,20,
2,2,7,26,26,27,8,34,32,35,33,23,36,36,37,40,39,40,41,9,
44,45,10,56,55,58,57,51,61,59,53,52,54,14,55,4,57,5,60,61,
63,12,21,22,28,34,35,42,46,56,58,4,1,2,3,6,49,21,73,79,
80,79,80,74,75,34,35,81,81,74,75,73,76,82,83,77,78,84,21,22,
56,86,86,86,85,85
];
hasParamIdx = array1d(Param, [
1,1,2,1,1,2,1,2,1,1,2,1
]);
userAnnotatedFunction = array1d(FunctionEntry, [
 true,false,false,false,false,false
]);
MaxFuncParms = 3;
constraint ::  "TaintOnNodeIdx51" taint[51]=ORANGE;
constraint ::  "TaintOnNodeIdx64" taint[64]=ORANGE;
constraint ::  "TaintOnNodeIdx65" taint[65]=PURPLE;
constraint ::  "TaintOnNodeIdx67" taint[67]=XDLINKAGE_GET_EWMA;
