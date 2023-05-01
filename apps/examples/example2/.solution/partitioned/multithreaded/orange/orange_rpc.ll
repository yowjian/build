; ModuleID = '/workspaces/build/apps/examples/example2/partitioned/multithreaded/orange/orange_rpc.c'
source_filename = "/workspaces/build/apps/examples/example2/partitioned/multithreaded/orange/orange_rpc.c"
target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-pc-linux-gnu"

%struct._tag = type { i32, i32, i32 }
%struct._request_get_ewma_datatype = type { double, %struct._trailer_datatype }
%struct._trailer_datatype = type { i32, i32, i32, i16, i16 }
%struct._response_get_ewma_datatype = type { double, %struct._trailer_datatype }

@_rpc_get_ewma.req_counter = internal global i32 -2147483648, align 4, !dbg !0
@_rpc_get_ewma.last_processed_result = internal global double 0.000000e+00, align 8, !dbg !16
@_rpc_get_ewma.last_processed_error = internal global i32 0, align 4, !dbg !18
@_rpc_get_ewma.inited = internal global i32 0, align 4, !dbg !20
@_rpc_get_ewma.psocket = internal global i8* null, align 8, !dbg !22
@_rpc_get_ewma.ssocket = internal global i8* null, align 8, !dbg !25
@.str = private unnamed_addr constant [13 x i8] c"RPC_GET_EWMA\00", section "llvm.metadata"
@.str.1 = private unnamed_addr constant [87 x i8] c"/workspaces/build/apps/examples/example2/partitioned/multithreaded/orange/orange_rpc.c\00", section "llvm.metadata"
@.str.2 = private unnamed_addr constant [24 x i8] c"ERR_HANDLE_RPC_GET_EWMA\00", section "llvm.metadata"
@.str.3 = private unnamed_addr constant [26 x i8] c"ipc:///tmp/sock_suborange\00", align 1
@.str.4 = private unnamed_addr constant [26 x i8] c"ipc:///tmp/sock_puborange\00", align 1
@llvm.global.annotations = appending global [2 x { i8*, i8*, i8*, i32 }] [{ i8*, i8*, i8*, i32 } { i8* bitcast (double (double, i32*)* @_rpc_get_ewma to i8*), i8* getelementptr inbounds ([13 x i8], [13 x i8]* @.str, i32 0, i32 0), i8* getelementptr inbounds ([87 x i8], [87 x i8]* @.str.1, i32 0, i32 0), i32 18 }, { i8*, i8*, i8*, i32 } { i8* bitcast (double (double)* @_err_handle_rpc_get_ewma to i8*), i8* getelementptr inbounds ([24 x i8], [24 x i8]* @.str.2, i32 0, i32 0), i8* getelementptr inbounds ([87 x i8], [87 x i8]* @.str.1, i32 0, i32 0), i32 164 }], section "llvm.metadata"

; Function Attrs: noinline nounwind optnone uwtable
define dso_local void @_hal_init(i8* %0, i8* %1) #0 !dbg !31 {
  %3 = alloca i8*, align 8
  %4 = alloca i8*, align 8
  store i8* %0, i8** %3, align 8
  call void @llvm.dbg.declare(metadata i8** %3, metadata !34, metadata !DIExpression()), !dbg !35
  store i8* %1, i8** %4, align 8
  call void @llvm.dbg.declare(metadata i8** %4, metadata !36, metadata !DIExpression()), !dbg !37
  call void @xdc_log_level(i32 2), !dbg !38
  %5 = load i8*, i8** %3, align 8, !dbg !39
  %6 = call i8* @xdc_set_in(i8* %5), !dbg !40
  %7 = load i8*, i8** %4, align 8, !dbg !41
  %8 = call i8* @xdc_set_out(i8* %7), !dbg !42
  call void @xdc_register(void (i8*, i8*, i64*)* @request_get_ewma_data_encode, void (i8*, i8*, i64*)* @request_get_ewma_data_decode, i32 3), !dbg !43
  call void @xdc_register(void (i8*, i8*, i64*)* @response_get_ewma_data_encode, void (i8*, i8*, i64*)* @response_get_ewma_data_decode, i32 4), !dbg !44
  ret void, !dbg !45
}

; Function Attrs: nounwind readnone speculatable willreturn
declare void @llvm.dbg.declare(metadata, metadata, metadata) #1

declare dso_local void @xdc_log_level(i32) #2

declare dso_local i8* @xdc_set_in(i8*) #2

declare dso_local i8* @xdc_set_out(i8*) #2

declare dso_local void @xdc_register(void (i8*, i8*, i64*)*, void (i8*, i8*, i64*)*, i32) #2

declare dso_local void @request_get_ewma_data_encode(i8*, i8*, i64*) #2

declare dso_local void @request_get_ewma_data_decode(i8*, i8*, i64*) #2

declare dso_local void @response_get_ewma_data_encode(i8*, i8*, i64*) #2

declare dso_local void @response_get_ewma_data_decode(i8*, i8*, i64*) #2

; Function Attrs: noinline nounwind optnone uwtable
define dso_local double @_rpc_get_ewma(double %0, i32* %1) #0 !dbg !2 {
  %3 = alloca double, align 8
  %4 = alloca i32*, align 8
  %5 = alloca %struct._tag, align 4
  %6 = alloca %struct._tag, align 4
  %7 = alloca %struct._request_get_ewma_datatype, align 1
  %8 = alloca %struct._response_get_ewma_datatype, align 1
  %9 = alloca double, align 8
  %10 = alloca { i64, i32 }, align 4
  %11 = alloca i32, align 4
  %12 = alloca i32, align 4
  store double %0, double* %3, align 8
  call void @llvm.dbg.declare(metadata double* %3, metadata !46, metadata !DIExpression()), !dbg !47
  store i32* %1, i32** %4, align 8
  call void @llvm.dbg.declare(metadata i32** %4, metadata !48, metadata !DIExpression()), !dbg !49
  call void @llvm.dbg.declare(metadata %struct._tag* %5, metadata !50, metadata !DIExpression()), !dbg !63
  call void @llvm.dbg.declare(metadata %struct._tag* %6, metadata !64, metadata !DIExpression()), !dbg !65
  call void @tag_write(%struct._tag* %5, i32 1, i32 1, i32 3), !dbg !66
  call void @tag_write(%struct._tag* %6, i32 2, i32 2, i32 4), !dbg !67
  call void @llvm.dbg.declare(metadata %struct._request_get_ewma_datatype* %7, metadata !68, metadata !DIExpression()), !dbg !86
  call void @llvm.dbg.declare(metadata %struct._response_get_ewma_datatype* %8, metadata !87, metadata !DIExpression()), !dbg !93
  call void @llvm.dbg.declare(metadata double* %9, metadata !94, metadata !DIExpression()), !dbg !95
  %13 = load i32, i32* @_rpc_get_ewma.inited, align 4, !dbg !96
  %14 = icmp ne i32 %13, 0, !dbg !96
  br i1 %14, label %25, label %15, !dbg !98

15:                                               ; preds = %2
  store i32 1, i32* @_rpc_get_ewma.inited, align 4, !dbg !99
  %16 = call i8* @xdc_pub_socket(), !dbg !101
  store i8* %16, i8** @_rpc_get_ewma.psocket, align 8, !dbg !102
  %17 = bitcast { i64, i32 }* %10 to i8*, !dbg !103
  %18 = bitcast %struct._tag* %6 to i8*, !dbg !103
  call void @llvm.memcpy.p0i8.p0i8.i64(i8* align 4 %17, i8* align 4 %18, i64 12, i1 false), !dbg !103
  %19 = getelementptr inbounds { i64, i32 }, { i64, i32 }* %10, i32 0, i32 0, !dbg !103
  %20 = load i64, i64* %19, align 4, !dbg !103
  %21 = getelementptr inbounds { i64, i32 }, { i64, i32 }* %10, i32 0, i32 1, !dbg !103
  %22 = load i32, i32* %21, align 4, !dbg !103
  %23 = call i8* @xdc_sub_socket_non_blocking(i64 %20, i32 %22, i32 1000), !dbg !103
  store i8* %23, i8** @_rpc_get_ewma.ssocket, align 8, !dbg !104
  %24 = call i32 @sleep(i32 1), !dbg !105
  br label %25, !dbg !106

25:                                               ; preds = %15, %2
  %26 = getelementptr inbounds %struct._request_get_ewma_datatype, %struct._request_get_ewma_datatype* %7, i32 0, i32 0, !dbg !107
  store double 0.000000e+00, double* %26, align 1, !dbg !108
  %27 = load i32, i32* @_rpc_get_ewma.req_counter, align 4, !dbg !109
  %28 = getelementptr inbounds %struct._request_get_ewma_datatype, %struct._request_get_ewma_datatype* %7, i32 0, i32 1, !dbg !110
  %29 = getelementptr inbounds %struct._trailer_datatype, %struct._trailer_datatype* %28, i32 0, i32 0, !dbg !111
  store i32 %27, i32* %29, align 1, !dbg !112
  %30 = load i32, i32* @_rpc_get_ewma.req_counter, align 4, !dbg !113
  %31 = icmp eq i32 %30, -2147483648, !dbg !115
  br i1 %31, label %32, label %61, !dbg !116

32:                                               ; preds = %25
  call void @llvm.dbg.declare(metadata i32* %11, metadata !117, metadata !DIExpression()), !dbg !119
  store i32 5, i32* %11, align 4, !dbg !119
  br label %33, !dbg !120

33:                                               ; preds = %46, %32
  %34 = load i32, i32* %11, align 4, !dbg !121
  %35 = icmp ne i32 %34, 0, !dbg !122
  br i1 %35, label %36, label %50, !dbg !120

36:                                               ; preds = %33
  %37 = load i8*, i8** @_rpc_get_ewma.psocket, align 8, !dbg !123
  %38 = bitcast %struct._request_get_ewma_datatype* %7 to i8*, !dbg !125
  call void @xdc_asyn_send(i8* %37, i8* %38, %struct._tag* %5), !dbg !126
  %39 = load i8*, i8** @_rpc_get_ewma.ssocket, align 8, !dbg !127
  %40 = bitcast %struct._response_get_ewma_datatype* %8 to i8*, !dbg !128
  %41 = call i32 @xdc_recv(i8* %39, i8* %40, %struct._tag* %6), !dbg !129
  %42 = load i32*, i32** %4, align 8, !dbg !130
  store i32 %41, i32* %42, align 4, !dbg !131
  %43 = load i32*, i32** %4, align 8, !dbg !132
  %44 = load i32, i32* %43, align 4, !dbg !134
  %45 = icmp eq i32 %44, -1, !dbg !135
  br i1 %45, label %46, label %49, !dbg !136

46:                                               ; preds = %36
  %47 = load i32, i32* %11, align 4, !dbg !137
  %48 = add nsw i32 %47, -1, !dbg !137
  store i32 %48, i32* %11, align 4, !dbg !137
  br label %33, !dbg !139, !llvm.loop !140

49:                                               ; preds = %36
  br label %50, !dbg !142

50:                                               ; preds = %49, %33
  %51 = load i32*, i32** %4, align 8, !dbg !143
  %52 = load i32, i32* %51, align 4, !dbg !145
  %53 = icmp sge i32 %52, 0, !dbg !146
  br i1 %53, label %54, label %60, !dbg !147

54:                                               ; preds = %50
  %55 = getelementptr inbounds %struct._response_get_ewma_datatype, %struct._response_get_ewma_datatype* %8, i32 0, i32 1, !dbg !148
  %56 = getelementptr inbounds %struct._trailer_datatype, %struct._trailer_datatype* %55, i32 0, i32 0, !dbg !149
  %57 = load i32, i32* %56, align 1, !dbg !149
  %58 = lshr i32 %57, 2, !dbg !150
  %59 = add i32 1, %58, !dbg !151
  store i32 %59, i32* @_rpc_get_ewma.req_counter, align 4, !dbg !152
  br label %60, !dbg !153

60:                                               ; preds = %54, %50
  br label %61, !dbg !154

61:                                               ; preds = %60, %25
  %62 = load double, double* %3, align 8, !dbg !155
  %63 = getelementptr inbounds %struct._request_get_ewma_datatype, %struct._request_get_ewma_datatype* %7, i32 0, i32 0, !dbg !156
  store double %62, double* %63, align 1, !dbg !157
  %64 = load i32, i32* @_rpc_get_ewma.req_counter, align 4, !dbg !158
  %65 = getelementptr inbounds %struct._request_get_ewma_datatype, %struct._request_get_ewma_datatype* %7, i32 0, i32 1, !dbg !159
  %66 = getelementptr inbounds %struct._trailer_datatype, %struct._trailer_datatype* %65, i32 0, i32 0, !dbg !160
  store i32 %64, i32* %66, align 1, !dbg !161
  call void @llvm.dbg.declare(metadata i32* %12, metadata !162, metadata !DIExpression()), !dbg !163
  store i32 5, i32* %12, align 4, !dbg !163
  br label %67, !dbg !164

67:                                               ; preds = %80, %61
  %68 = load i32, i32* %12, align 4, !dbg !165
  %69 = icmp ne i32 %68, 0, !dbg !166
  br i1 %69, label %70, label %84, !dbg !164

70:                                               ; preds = %67
  %71 = load i8*, i8** @_rpc_get_ewma.psocket, align 8, !dbg !167
  %72 = bitcast %struct._request_get_ewma_datatype* %7 to i8*, !dbg !169
  call void @xdc_asyn_send(i8* %71, i8* %72, %struct._tag* %5), !dbg !170
  %73 = load i8*, i8** @_rpc_get_ewma.ssocket, align 8, !dbg !171
  %74 = bitcast %struct._response_get_ewma_datatype* %8 to i8*, !dbg !172
  %75 = call i32 @xdc_recv(i8* %73, i8* %74, %struct._tag* %6), !dbg !173
  %76 = load i32*, i32** %4, align 8, !dbg !174
  store i32 %75, i32* %76, align 4, !dbg !175
  %77 = load i32*, i32** %4, align 8, !dbg !176
  %78 = load i32, i32* %77, align 4, !dbg !178
  %79 = icmp eq i32 %78, -1, !dbg !179
  br i1 %79, label %80, label %83, !dbg !180

80:                                               ; preds = %70
  %81 = load i32, i32* %12, align 4, !dbg !181
  %82 = add nsw i32 %81, -1, !dbg !181
  store i32 %82, i32* %12, align 4, !dbg !181
  br label %67, !dbg !183, !llvm.loop !184

83:                                               ; preds = %70
  br label %84, !dbg !186

84:                                               ; preds = %83, %67
  %85 = load i32, i32* @_rpc_get_ewma.req_counter, align 4, !dbg !187
  %86 = add nsw i32 %85, 1, !dbg !187
  store i32 %86, i32* @_rpc_get_ewma.req_counter, align 4, !dbg !187
  %87 = getelementptr inbounds %struct._response_get_ewma_datatype, %struct._response_get_ewma_datatype* %8, i32 0, i32 0, !dbg !188
  %88 = load double, double* %87, align 1, !dbg !188
  store double %88, double* %9, align 8, !dbg !189
  %89 = load double, double* %9, align 8, !dbg !190
  ret double %89, !dbg !191
}

declare dso_local void @tag_write(%struct._tag*, i32, i32, i32) #2

declare dso_local i8* @xdc_pub_socket() #2

declare dso_local i8* @xdc_sub_socket_non_blocking(i64, i32, i32) #2

; Function Attrs: argmemonly nounwind willreturn
declare void @llvm.memcpy.p0i8.p0i8.i64(i8* noalias nocapture writeonly, i8* noalias nocapture readonly, i64, i1 immarg) #3

declare dso_local i32 @sleep(i32) #2

declare dso_local void @xdc_asyn_send(i8*, i8*, %struct._tag*) #2

declare dso_local i32 @xdc_recv(i8*, i8*, %struct._tag*) #2

; Function Attrs: noinline nounwind optnone uwtable
define dso_local double @_err_handle_rpc_get_ewma(double %0) #0 !dbg !192 {
  %2 = alloca double, align 8
  %3 = alloca i32, align 4
  %4 = alloca double, align 8
  store double %0, double* %2, align 8
  call void @llvm.dbg.declare(metadata double* %2, metadata !195, metadata !DIExpression()), !dbg !196
  call void @llvm.dbg.declare(metadata i32* %3, metadata !197, metadata !DIExpression()), !dbg !198
  call void @llvm.dbg.declare(metadata double* %4, metadata !199, metadata !DIExpression()), !dbg !200
  %5 = load double, double* %2, align 8, !dbg !201
  %6 = call double @_rpc_get_ewma(double %5, i32* %3), !dbg !202
  store double %6, double* %4, align 8, !dbg !200
  %7 = load double, double* %4, align 8, !dbg !203
  ret double %7, !dbg !204
}

; Function Attrs: noinline nounwind optnone uwtable
define dso_local void @_master_rpc_init() #0 !dbg !205 {
  call void @_hal_init(i8* getelementptr inbounds ([26 x i8], [26 x i8]* @.str.3, i64 0, i64 0), i8* getelementptr inbounds ([26 x i8], [26 x i8]* @.str.4, i64 0, i64 0)), !dbg !208
  ret void, !dbg !209
}

attributes #0 = { noinline nounwind optnone uwtable "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "frame-pointer"="all" "less-precise-fpmad"="false" "min-legal-vector-width"="0" "no-infs-fp-math"="false" "no-jump-tables"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { nounwind readnone speculatable willreturn }
attributes #2 = { "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "frame-pointer"="all" "less-precise-fpmad"="false" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #3 = { argmemonly nounwind willreturn }

!llvm.dbg.cu = !{!9}
!llvm.module.flags = !{!27, !28, !29}
!llvm.ident = !{!30}

!0 = !DIGlobalVariableExpression(var: !1, expr: !DIExpression())
!1 = distinct !DIGlobalVariable(name: "req_counter", scope: !2, file: !3, line: 33, type: !8, isLocal: true, isDefinition: true)
!2 = distinct !DISubprogram(name: "_rpc_get_ewma", scope: !3, file: !3, line: 18, type: !4, scopeLine: 18, flags: DIFlagPrototyped, spFlags: DISPFlagDefinition, unit: !9, retainedNodes: !11)
!3 = !DIFile(filename: "partitioned/multithreaded/orange/orange_rpc.c", directory: "/workspaces/build/apps/examples/example2")
!4 = !DISubroutineType(types: !5)
!5 = !{!6, !6, !7}
!6 = !DIBasicType(name: "double", size: 64, encoding: DW_ATE_float)
!7 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !8, size: 64)
!8 = !DIBasicType(name: "int", size: 32, encoding: DW_ATE_signed)
!9 = distinct !DICompileUnit(language: DW_LANG_C99, file: !10, producer: "clang version 10.0.0-4ubuntu1 ", isOptimized: false, runtimeVersion: 0, emissionKind: FullDebug, enums: !11, retainedTypes: !12, globals: !15, splitDebugInlining: false, nameTableKind: None)
!10 = !DIFile(filename: "/workspaces/build/apps/examples/example2/partitioned/multithreaded/orange/orange_rpc.c", directory: "/workspaces/build/apps/examples/example2")
!11 = !{}
!12 = !{!13}
!13 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !14, size: 64)
!14 = !DIBasicType(name: "char", size: 8, encoding: DW_ATE_signed_char)
!15 = !{!0, !16, !18, !20, !22, !25}
!16 = !DIGlobalVariableExpression(var: !17, expr: !DIExpression())
!17 = distinct !DIGlobalVariable(name: "last_processed_result", scope: !2, file: !3, line: 34, type: !6, isLocal: true, isDefinition: true)
!18 = !DIGlobalVariableExpression(var: !19, expr: !DIExpression())
!19 = distinct !DIGlobalVariable(name: "last_processed_error", scope: !2, file: !3, line: 35, type: !8, isLocal: true, isDefinition: true)
!20 = !DIGlobalVariableExpression(var: !21, expr: !DIExpression())
!21 = distinct !DIGlobalVariable(name: "inited", scope: !2, file: !3, line: 36, type: !8, isLocal: true, isDefinition: true)
!22 = !DIGlobalVariableExpression(var: !23, expr: !DIExpression())
!23 = distinct !DIGlobalVariable(name: "psocket", scope: !2, file: !3, line: 41, type: !24, isLocal: true, isDefinition: true)
!24 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: null, size: 64)
!25 = !DIGlobalVariableExpression(var: !26, expr: !DIExpression())
!26 = distinct !DIGlobalVariable(name: "ssocket", scope: !2, file: !3, line: 42, type: !24, isLocal: true, isDefinition: true)
!27 = !{i32 7, !"Dwarf Version", i32 4}
!28 = !{i32 2, !"Debug Info Version", i32 3}
!29 = !{i32 1, !"wchar_size", i32 4}
!30 = !{!"clang version 10.0.0-4ubuntu1 "}
!31 = distinct !DISubprogram(name: "_hal_init", scope: !3, file: !3, line: 5, type: !32, scopeLine: 5, flags: DIFlagPrototyped, spFlags: DISPFlagDefinition, unit: !9, retainedNodes: !11)
!32 = !DISubroutineType(types: !33)
!33 = !{null, !13, !13}
!34 = !DILocalVariable(name: "inuri", arg: 1, scope: !31, file: !3, line: 5, type: !13)
!35 = !DILocation(line: 5, column: 22, scope: !31)
!36 = !DILocalVariable(name: "outuri", arg: 2, scope: !31, file: !3, line: 5, type: !13)
!37 = !DILocation(line: 5, column: 35, scope: !31)
!38 = !DILocation(line: 6, column: 5, scope: !31)
!39 = !DILocation(line: 8, column: 16, scope: !31)
!40 = !DILocation(line: 8, column: 5, scope: !31)
!41 = !DILocation(line: 9, column: 17, scope: !31)
!42 = !DILocation(line: 9, column: 5, scope: !31)
!43 = !DILocation(line: 10, column: 5, scope: !31)
!44 = !DILocation(line: 11, column: 5, scope: !31)
!45 = !DILocation(line: 14, column: 1, scope: !31)
!46 = !DILocalVariable(name: "x", arg: 1, scope: !2, file: !3, line: 18, type: !6)
!47 = !DILocation(line: 18, column: 29, scope: !2)
!48 = !DILocalVariable(name: "error", arg: 2, scope: !2, file: !3, line: 18, type: !7)
!49 = !DILocation(line: 18, column: 37, scope: !2)
!50 = !DILocalVariable(name: "t_tag", scope: !2, file: !3, line: 21, type: !51)
!51 = !DIDerivedType(tag: DW_TAG_typedef, name: "gaps_tag", file: !52, line: 32, baseType: !53)
!52 = !DIFile(filename: "/opt/closure/include/xdcomms.h", directory: "")
!53 = distinct !DICompositeType(tag: DW_TAG_structure_type, name: "_tag", file: !52, line: 28, size: 96, elements: !54)
!54 = !{!55, !61, !62}
!55 = !DIDerivedType(tag: DW_TAG_member, name: "mux", scope: !53, file: !52, line: 29, baseType: !56, size: 32)
!56 = !DIDerivedType(tag: DW_TAG_typedef, name: "uint32_t", file: !57, line: 26, baseType: !58)
!57 = !DIFile(filename: "/usr/include/x86_64-linux-gnu/bits/stdint-uintn.h", directory: "")
!58 = !DIDerivedType(tag: DW_TAG_typedef, name: "__uint32_t", file: !59, line: 42, baseType: !60)
!59 = !DIFile(filename: "/usr/include/x86_64-linux-gnu/bits/types.h", directory: "")
!60 = !DIBasicType(name: "unsigned int", size: 32, encoding: DW_ATE_unsigned)
!61 = !DIDerivedType(tag: DW_TAG_member, name: "sec", scope: !53, file: !52, line: 30, baseType: !56, size: 32, offset: 32)
!62 = !DIDerivedType(tag: DW_TAG_member, name: "typ", scope: !53, file: !52, line: 31, baseType: !56, size: 32, offset: 64)
!63 = !DILocation(line: 21, column: 14, scope: !2)
!64 = !DILocalVariable(name: "o_tag", scope: !2, file: !3, line: 22, type: !51)
!65 = !DILocation(line: 22, column: 14, scope: !2)
!66 = !DILocation(line: 26, column: 5, scope: !2)
!67 = !DILocation(line: 31, column: 5, scope: !2)
!68 = !DILocalVariable(name: "request_get_ewma", scope: !2, file: !3, line: 45, type: !69)
!69 = !DIDerivedType(tag: DW_TAG_typedef, name: "request_get_ewma_datatype", file: !70, line: 75, baseType: !71)
!70 = !DIFile(filename: "partitioned/multithreaded/autogen/codec.h", directory: "/workspaces/build/apps/examples/example2")
!71 = distinct !DICompositeType(tag: DW_TAG_structure_type, name: "_request_get_ewma_datatype", file: !70, line: 72, size: 192, elements: !72)
!72 = !{!73, !74}
!73 = !DIDerivedType(tag: DW_TAG_member, name: "x", scope: !71, file: !70, line: 73, baseType: !6, size: 64)
!74 = !DIDerivedType(tag: DW_TAG_member, name: "trailer", scope: !71, file: !70, line: 74, baseType: !75, size: 128, offset: 64)
!75 = !DIDerivedType(tag: DW_TAG_typedef, name: "trailer_datatype", file: !70, line: 28, baseType: !76)
!76 = distinct !DICompositeType(tag: DW_TAG_structure_type, name: "_trailer_datatype", file: !70, line: 22, size: 128, elements: !77)
!77 = !{!78, !79, !80, !81, !85}
!78 = !DIDerivedType(tag: DW_TAG_member, name: "seq", scope: !76, file: !70, line: 23, baseType: !56, size: 32)
!79 = !DIDerivedType(tag: DW_TAG_member, name: "rqr", scope: !76, file: !70, line: 24, baseType: !56, size: 32, offset: 32)
!80 = !DIDerivedType(tag: DW_TAG_member, name: "oid", scope: !76, file: !70, line: 25, baseType: !56, size: 32, offset: 64)
!81 = !DIDerivedType(tag: DW_TAG_member, name: "mid", scope: !76, file: !70, line: 26, baseType: !82, size: 16, offset: 96)
!82 = !DIDerivedType(tag: DW_TAG_typedef, name: "uint16_t", file: !57, line: 25, baseType: !83)
!83 = !DIDerivedType(tag: DW_TAG_typedef, name: "__uint16_t", file: !59, line: 40, baseType: !84)
!84 = !DIBasicType(name: "unsigned short", size: 16, encoding: DW_ATE_unsigned)
!85 = !DIDerivedType(tag: DW_TAG_member, name: "crc", scope: !76, file: !70, line: 27, baseType: !82, size: 16, offset: 112)
!86 = !DILocation(line: 45, column: 31, scope: !2)
!87 = !DILocalVariable(name: "response_get_ewma", scope: !2, file: !3, line: 48, type: !88)
!88 = !DIDerivedType(tag: DW_TAG_typedef, name: "response_get_ewma_datatype", file: !70, line: 89, baseType: !89)
!89 = distinct !DICompositeType(tag: DW_TAG_structure_type, name: "_response_get_ewma_datatype", file: !70, line: 86, size: 192, elements: !90)
!90 = !{!91, !92}
!91 = !DIDerivedType(tag: DW_TAG_member, name: "ret", scope: !89, file: !70, line: 87, baseType: !6, size: 64)
!92 = !DIDerivedType(tag: DW_TAG_member, name: "trailer", scope: !89, file: !70, line: 88, baseType: !75, size: 128, offset: 64)
!93 = !DILocation(line: 48, column: 32, scope: !2)
!94 = !DILocalVariable(name: "result", scope: !2, file: !3, line: 50, type: !6)
!95 = !DILocation(line: 50, column: 12, scope: !2)
!96 = !DILocation(line: 63, column: 10, scope: !97)
!97 = distinct !DILexicalBlock(scope: !2, file: !3, line: 63, column: 9)
!98 = !DILocation(line: 63, column: 9, scope: !2)
!99 = !DILocation(line: 64, column: 16, scope: !100)
!100 = distinct !DILexicalBlock(scope: !97, file: !3, line: 63, column: 18)
!101 = !DILocation(line: 65, column: 19, scope: !100)
!102 = !DILocation(line: 65, column: 17, scope: !100)
!103 = !DILocation(line: 66, column: 19, scope: !100)
!104 = !DILocation(line: 66, column: 17, scope: !100)
!105 = !DILocation(line: 67, column: 9, scope: !100)
!106 = !DILocation(line: 68, column: 5, scope: !100)
!107 = !DILocation(line: 70, column: 22, scope: !2)
!108 = !DILocation(line: 70, column: 24, scope: !2)
!109 = !DILocation(line: 71, column: 36, scope: !2)
!110 = !DILocation(line: 71, column: 22, scope: !2)
!111 = !DILocation(line: 71, column: 30, scope: !2)
!112 = !DILocation(line: 71, column: 34, scope: !2)
!113 = !DILocation(line: 95, column: 9, scope: !114)
!114 = distinct !DILexicalBlock(scope: !2, file: !3, line: 95, column: 9)
!115 = !DILocation(line: 95, column: 21, scope: !114)
!116 = !DILocation(line: 95, column: 9, scope: !2)
!117 = !DILocalVariable(name: "tries_remaining", scope: !118, file: !3, line: 96, type: !8)
!118 = distinct !DILexicalBlock(scope: !114, file: !3, line: 95, column: 33)
!119 = !DILocation(line: 96, column: 13, scope: !118)
!120 = !DILocation(line: 97, column: 9, scope: !118)
!121 = !DILocation(line: 97, column: 15, scope: !118)
!122 = !DILocation(line: 97, column: 31, scope: !118)
!123 = !DILocation(line: 98, column: 27, scope: !124)
!124 = distinct !DILexicalBlock(scope: !118, file: !3, line: 97, column: 36)
!125 = !DILocation(line: 98, column: 36, scope: !124)
!126 = !DILocation(line: 98, column: 13, scope: !124)
!127 = !DILocation(line: 100, column: 31, scope: !124)
!128 = !DILocation(line: 100, column: 40, scope: !124)
!129 = !DILocation(line: 100, column: 22, scope: !124)
!130 = !DILocation(line: 100, column: 14, scope: !124)
!131 = !DILocation(line: 100, column: 20, scope: !124)
!132 = !DILocation(line: 101, column: 18, scope: !133)
!133 = distinct !DILexicalBlock(scope: !124, file: !3, line: 101, column: 17)
!134 = !DILocation(line: 101, column: 17, scope: !133)
!135 = !DILocation(line: 101, column: 24, scope: !133)
!136 = !DILocation(line: 101, column: 17, scope: !124)
!137 = !DILocation(line: 102, column: 32, scope: !138)
!138 = distinct !DILexicalBlock(scope: !133, file: !3, line: 101, column: 30)
!139 = !DILocation(line: 103, column: 17, scope: !138)
!140 = distinct !{!140, !120, !141}
!141 = !DILocation(line: 109, column: 9, scope: !118)
!142 = !DILocation(line: 108, column: 13, scope: !124)
!143 = !DILocation(line: 111, column: 14, scope: !144)
!144 = distinct !DILexicalBlock(scope: !118, file: !3, line: 111, column: 13)
!145 = !DILocation(line: 111, column: 13, scope: !144)
!146 = !DILocation(line: 111, column: 20, scope: !144)
!147 = !DILocation(line: 111, column: 13, scope: !118)
!148 = !DILocation(line: 111, column: 63, scope: !144)
!149 = !DILocation(line: 111, column: 71, scope: !144)
!150 = !DILocation(line: 111, column: 75, scope: !144)
!151 = !DILocation(line: 111, column: 42, scope: !144)
!152 = !DILocation(line: 111, column: 38, scope: !144)
!153 = !DILocation(line: 111, column: 26, scope: !144)
!154 = !DILocation(line: 115, column: 5, scope: !118)
!155 = !DILocation(line: 117, column: 26, scope: !2)
!156 = !DILocation(line: 117, column: 22, scope: !2)
!157 = !DILocation(line: 117, column: 24, scope: !2)
!158 = !DILocation(line: 118, column: 36, scope: !2)
!159 = !DILocation(line: 118, column: 22, scope: !2)
!160 = !DILocation(line: 118, column: 30, scope: !2)
!161 = !DILocation(line: 118, column: 34, scope: !2)
!162 = !DILocalVariable(name: "tries_remaining", scope: !2, file: !3, line: 138, type: !8)
!163 = !DILocation(line: 138, column: 9, scope: !2)
!164 = !DILocation(line: 139, column: 5, scope: !2)
!165 = !DILocation(line: 139, column: 11, scope: !2)
!166 = !DILocation(line: 139, column: 27, scope: !2)
!167 = !DILocation(line: 140, column: 23, scope: !168)
!168 = distinct !DILexicalBlock(scope: !2, file: !3, line: 139, column: 32)
!169 = !DILocation(line: 140, column: 32, scope: !168)
!170 = !DILocation(line: 140, column: 9, scope: !168)
!171 = !DILocation(line: 142, column: 27, scope: !168)
!172 = !DILocation(line: 142, column: 36, scope: !168)
!173 = !DILocation(line: 142, column: 18, scope: !168)
!174 = !DILocation(line: 142, column: 10, scope: !168)
!175 = !DILocation(line: 142, column: 16, scope: !168)
!176 = !DILocation(line: 143, column: 14, scope: !177)
!177 = distinct !DILexicalBlock(scope: !168, file: !3, line: 143, column: 13)
!178 = !DILocation(line: 143, column: 13, scope: !177)
!179 = !DILocation(line: 143, column: 20, scope: !177)
!180 = !DILocation(line: 143, column: 13, scope: !168)
!181 = !DILocation(line: 144, column: 28, scope: !182)
!182 = distinct !DILexicalBlock(scope: !177, file: !3, line: 143, column: 26)
!183 = !DILocation(line: 145, column: 13, scope: !182)
!184 = distinct !{!184, !164, !185}
!185 = !DILocation(line: 151, column: 5, scope: !2)
!186 = !DILocation(line: 150, column: 9, scope: !168)
!187 = !DILocation(line: 153, column: 16, scope: !2)
!188 = !DILocation(line: 155, column: 32, scope: !2)
!189 = !DILocation(line: 155, column: 12, scope: !2)
!190 = !DILocation(line: 156, column: 13, scope: !2)
!191 = !DILocation(line: 156, column: 5, scope: !2)
!192 = distinct !DISubprogram(name: "_err_handle_rpc_get_ewma", scope: !3, file: !3, line: 164, type: !193, scopeLine: 164, flags: DIFlagPrototyped, spFlags: DISPFlagDefinition, unit: !9, retainedNodes: !11)
!193 = !DISubroutineType(types: !194)
!194 = !{!6, !6}
!195 = !DILocalVariable(name: "x", arg: 1, scope: !192, file: !3, line: 164, type: !6)
!196 = !DILocation(line: 164, column: 40, scope: !192)
!197 = !DILocalVariable(name: "err_num", scope: !192, file: !3, line: 167, type: !8)
!198 = !DILocation(line: 167, column: 6, scope: !192)
!199 = !DILocalVariable(name: "res", scope: !192, file: !3, line: 168, type: !6)
!200 = !DILocation(line: 168, column: 9, scope: !192)
!201 = !DILocation(line: 168, column: 29, scope: !192)
!202 = !DILocation(line: 168, column: 15, scope: !192)
!203 = !DILocation(line: 170, column: 9, scope: !192)
!204 = !DILocation(line: 170, column: 2, scope: !192)
!205 = distinct !DISubprogram(name: "_master_rpc_init", scope: !3, file: !3, line: 172, type: !206, scopeLine: 172, spFlags: DISPFlagDefinition, unit: !9, retainedNodes: !11)
!206 = !DISubroutineType(types: !207)
!207 = !{null}
!208 = !DILocation(line: 173, column: 5, scope: !205)
!209 = !DILocation(line: 174, column: 1, scope: !205)
