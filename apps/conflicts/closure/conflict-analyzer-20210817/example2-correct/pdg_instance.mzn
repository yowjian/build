Inst_FunCall_start = 1;
Inst_FunCall_end = 6;
Inst_Ret_start = 7;
Inst_Ret_end = 12;
Inst_Br_start = 13;
Inst_Br_end = 16;
Inst_Other_start = 17;
Inst_Other_end = 72;
Inst_start = 1;
Inst_end = 72;
VarNode_StaticGlobal_start = 0;
VarNode_StaticGlobal_end = -1;
VarNode_StaticModule_start = 0;
VarNode_StaticModule_end = -1;
VarNode_StaticFunction_start = 73;
VarNode_StaticFunction_end = 75;
VarNode_StaticOther_start = 0;
VarNode_StaticOther_end = -1;
VarNode_start = 73;
VarNode_end = 75;
FunctionEntry_start = 76;
FunctionEntry_end = 81;
Param_FormalIn_start = 82;
Param_FormalIn_end = 84;
Param_FormalOut_start = 85;
Param_FormalOut_end = 87;
Param_ActualIn_start = 88;
Param_ActualIn_end = 90;
Param_ActualOut_start = 91;
Param_ActualOut_end = 93;
Param_start = 82;
Param_end = 93;
Annotation_Var_start = 94;
Annotation_Var_end = 97;
Annotation_Global_start = 98;
Annotation_Global_end = 98;
Annotation_Other_start = 0;
Annotation_Other_end = -1;
Annotation_start = 94;
Annotation_end = 98;
PDGNode_start = 1;
PDGNode_end = 98;
ControlDep_CallInv_start = 1;
ControlDep_CallInv_end = 5;
ControlDep_CallRet_start = 6;
ControlDep_CallRet_end = 10;
ControlDep_Entry_start = 11;
ControlDep_Entry_end = 82;
ControlDep_Br_start = 83;
ControlDep_Br_end = 94;
ControlDep_Other_start = 0;
ControlDep_Other_end = -1;
ControlDep_start = 1;
ControlDep_end = 94;
DataDepEdge_DefUse_start = 95;
DataDepEdge_DefUse_end = 160;
DataDepEdge_RAW_start = 161;
DataDepEdge_RAW_end = 170;
DataDepEdge_Ret_start = 171;
DataDepEdge_Ret_end = 175;
DataDepEdge_Alias_start = 176;
DataDepEdge_Alias_end = 179;
DataDepEdge_start = 95;
DataDepEdge_end = 179;
Parameter_In_start = 180;
Parameter_In_end = 194;
Parameter_Out_start = 195;
Parameter_Out_end = 203;
Parameter_Field_start = 0;
Parameter_Field_end = -1;
Parameter_start = 180;
Parameter_end = 203;
Anno_Global_start = 204;
Anno_Global_end = 206;
Anno_Var_start = 207;
Anno_Var_end = 214;
Anno_Other_start = 0;
Anno_Other_end = -1;
Anno_start = 204;
Anno_end = 214;
PDGEdge_start = 1;
PDGEdge_end = 214;
hasFunction = [
76,76,80,80,80,81,76,77,78,79,80,81,80,80,80,80,76,76,76,76,
76,76,76,77,76,76,76,76,76,76,76,76,77,77,77,77,78,78,78,78,
78,78,78,78,78,78,78,78,78,78,78,79,79,79,79,80,80,80,80,80,
80,80,80,80,80,80,80,80,80,80,81,81,0,0,0,76,77,78,79,80,
81,76,78,78,76,78,78,78,78,76,78,78,76,76,76,76,80,0
];
hasSource = [
1,2,3,4,6,7,8,9,10,11,76,76,76,76,76,76,76,76,76,76,
76,76,76,76,76,76,76,76,77,77,77,77,77,77,78,78,78,78,78,78,
78,78,78,78,78,78,78,78,78,78,79,79,79,79,79,80,80,80,80,80,
80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,81,81,
81,81,14,14,14,14,14,14,14,14,14,14,14,14,73,73,73,74,74,74,
74,75,75,75,17,17,18,18,18,19,19,19,20,20,20,24,26,1,29,30,
2,32,33,34,36,37,37,38,38,39,43,44,45,46,47,48,49,51,52,53,
55,56,56,58,58,58,59,59,59,59,62,63,3,65,4,67,68,69,71,6,
21,28,31,35,40,41,50,54,64,66,7,8,9,10,11,22,23,25,60,82,
76,29,30,2,2,78,78,83,84,65,4,88,89,90,76,2,2,78,78,4,
91,92,93,73,74,76,76,76,76,80,22,23,25,60
];
hasDest = [
77,78,79,76,80,4,1,2,3,6,18,19,20,21,22,23,25,26,27,1,
28,29,30,2,31,32,7,17,33,24,34,35,36,8,38,39,40,41,42,43,
44,45,46,47,48,49,50,51,9,37,52,53,54,55,10,57,58,59,60,61,
13,62,63,14,3,64,65,4,66,67,5,15,68,69,70,16,11,56,71,72,
6,12,3,64,65,4,66,67,5,15,68,69,70,16,55,54,52,36,35,24,
33,51,50,47,26,21,29,27,22,30,28,23,32,31,25,34,27,28,2,2,
31,7,34,35,8,43,40,44,41,42,45,45,46,49,48,49,50,9,53,54,
10,65,64,67,66,60,70,68,62,61,63,14,64,4,66,5,69,70,72,12,
26,30,32,36,43,44,51,55,65,67,4,1,2,3,6,18,19,20,58,26,
82,88,89,88,89,83,84,43,44,90,90,83,84,82,85,91,92,86,87,93,
29,30,65,98,98,98,94,95,96,97,94,95,96,97
];
hasParamIdx = array1d(Param, [
1,1,2,1,1,2,1,2,1,1,2,1
]);
userAnnotatedFunction = array1d(FunctionEntry, [
 true,false,false,false,false,false
]);
MaxFuncParms = 3;
constraint ::  "TaintOnNodeIdx22" taint[22]=PURPLE_SHAREABLE;
constraint ::  "TaintOnNodeIdx23" taint[23]=PURPLE_SHAREABLE;
constraint ::  "TaintOnNodeIdx25" taint[25]=PURPLE_SHAREABLE;
constraint ::  "TaintOnNodeIdx60" taint[60]=ORANGE;
constraint ::  "TaintOnNodeIdx73" taint[73]=ORANGE;
constraint ::  "TaintOnNodeIdx74" taint[74]=PURPLE;
constraint ::  "TaintOnNodeIdx76" taint[76]=XDLINKAGE_GET_EWMA;
