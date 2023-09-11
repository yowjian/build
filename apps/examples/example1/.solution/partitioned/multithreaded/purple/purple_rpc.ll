; ModuleID = '/workspaces/build/apps/examples/example1/partitioned/multithreaded/purple/purple_rpc.c'
source_filename = "/workspaces/build/apps/examples/example1/partitioned/multithreaded/purple/purple_rpc.c"
target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-pc-linux-gnu"

%struct._tag = type { i32, i32, i32 }
%struct._request_get_a_datatype = type { i32, %struct._trailer_datatype }
%struct._trailer_datatype = type { i32, i32, i32, i16, i16 }
%struct._response_get_a_datatype = type { double, %struct._trailer_datatype }

@_rpc_get_a.req_counter = internal global i32 -2147483648, align 4, !dbg !0
@_rpc_get_a.last_processed_result = internal global double 0.000000e+00, align 8, !dbg !16
@_rpc_get_a.last_processed_error = internal global i32 0, align 4, !dbg !18
@_rpc_get_a.inited = internal global i32 0, align 4, !dbg !20
@_rpc_get_a.psocket = internal global i8* null, align 8, !dbg !22
@_rpc_get_a.ssocket = internal global i8* null, align 8, !dbg !25
@.str = private unnamed_addr constant [10 x i8] c"RPC_GET_A\00", section "llvm.metadata"
@.str.1 = private unnamed_addr constant [87 x i8] c"/workspaces/build/apps/examples/example1/partitioned/multithreaded/purple/purple_rpc.c\00", section "llvm.metadata"
@.str.2 = private unnamed_addr constant [21 x i8] c"ERR_HANDLE_RPC_GET_A\00", section "llvm.metadata"
@.str.3 = private unnamed_addr constant [26 x i8] c"ipc:///tmp/sock_subpurple\00", align 1
@.str.4 = private unnamed_addr constant [26 x i8] c"ipc:///tmp/sock_pubpurple\00", align 1
@llvm.global.annotations = appending global [2 x { i8*, i8*, i8*, i32 }] [{ i8*, i8*, i8*, i32 } { i8* bitcast (double (i32*)* @_rpc_get_a to i8*), i8* getelementptr inbounds ([10 x i8], [10 x i8]* @.str, i32 0, i32 0), i8* getelementptr inbounds ([87 x i8], [87 x i8]* @.str.1, i32 0, i32 0), i32 18 }, { i8*, i8*, i8*, i32 } { i8* bitcast (double ()* @_err_handle_rpc_get_a to i8*), i8* getelementptr inbounds ([21 x i8], [21 x i8]* @.str.2, i32 0, i32 0), i8* getelementptr inbounds ([87 x i8], [87 x i8]* @.str.1, i32 0, i32 0), i32 164 }], section "llvm.metadata"

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
  call void @xdc_register(void (i8*, i8*, i64*)* @request_get_a_data_encode, void (i8*, i8*, i64*)* @request_get_a_data_decode, i32 3), !dbg !43
  call void @xdc_register(void (i8*, i8*, i64*)* @response_get_a_data_encode, void (i8*, i8*, i64*)* @response_get_a_data_decode, i32 4), !dbg !44
  ret void, !dbg !45
}

; Function Attrs: nounwind readnone speculatable willreturn
declare void @llvm.dbg.declare(metadata, metadata, metadata) #1

declare dso_local void @xdc_log_level(i32) #2

declare dso_local i8* @xdc_set_in(i8*) #2

declare dso_local i8* @xdc_set_out(i8*) #2

declare dso_local void @xdc_register(void (i8*, i8*, i64*)*, void (i8*, i8*, i64*)*, i32) #2

declare dso_local void @request_get_a_data_encode(i8*, i8*, i64*) #2

declare dso_local void @request_get_a_data_decode(i8*, i8*, i64*) #2

declare dso_local void @response_get_a_data_encode(i8*, i8*, i64*) #2

declare dso_local void @response_get_a_data_decode(i8*, i8*, i64*) #2

; Function Attrs: noinline nounwind optnone uwtable
define dso_local double @_rpc_get_a(i32* %0) #0 !dbg !2 {
  %2 = alloca i32*, align 8
  %3 = alloca %struct._tag, align 4
  %4 = alloca %struct._tag, align 4
  %5 = alloca %struct._request_get_a_datatype, align 1
  %6 = alloca %struct._response_get_a_datatype, align 1
  %7 = alloca double, align 8
  %8 = alloca { i64, i32 }, align 4
  %9 = alloca i32, align 4
  %10 = alloca i32, align 4
  store i32* %0, i32** %2, align 8
  call void @llvm.dbg.declare(metadata i32** %2, metadata !46, metadata !DIExpression()), !dbg !47
  call void @llvm.dbg.declare(metadata %struct._tag* %3, metadata !48, metadata !DIExpression()), !dbg !61
  call void @llvm.dbg.declare(metadata %struct._tag* %4, metadata !62, metadata !DIExpression()), !dbg !63
  call void @tag_write(%struct._tag* %3, i32 2, i32 2, i32 3), !dbg !64
  call void @tag_write(%struct._tag* %4, i32 1, i32 1, i32 4), !dbg !65
  call void @llvm.dbg.declare(metadata %struct._request_get_a_datatype* %5, metadata !66, metadata !DIExpression()), !dbg !87
  call void @llvm.dbg.declare(metadata %struct._response_get_a_datatype* %6, metadata !88, metadata !DIExpression()), !dbg !94
  call void @llvm.dbg.declare(metadata double* %7, metadata !95, metadata !DIExpression()), !dbg !96
  %11 = load i32, i32* @_rpc_get_a.inited, align 4, !dbg !97
  %12 = icmp ne i32 %11, 0, !dbg !97
  br i1 %12, label %23, label %13, !dbg !99

13:                                               ; preds = %1
  store i32 1, i32* @_rpc_get_a.inited, align 4, !dbg !100
  %14 = call i8* @xdc_pub_socket(), !dbg !102
  store i8* %14, i8** @_rpc_get_a.psocket, align 8, !dbg !103
  %15 = bitcast { i64, i32 }* %8 to i8*, !dbg !104
  %16 = bitcast %struct._tag* %4 to i8*, !dbg !104
  call void @llvm.memcpy.p0i8.p0i8.i64(i8* align 4 %15, i8* align 4 %16, i64 12, i1 false), !dbg !104
  %17 = getelementptr inbounds { i64, i32 }, { i64, i32 }* %8, i32 0, i32 0, !dbg !104
  %18 = load i64, i64* %17, align 4, !dbg !104
  %19 = getelementptr inbounds { i64, i32 }, { i64, i32 }* %8, i32 0, i32 1, !dbg !104
  %20 = load i32, i32* %19, align 4, !dbg !104
  %21 = call i8* @xdc_sub_socket_non_blocking(i64 %18, i32 %20, i32 1000), !dbg !104
  store i8* %21, i8** @_rpc_get_a.ssocket, align 8, !dbg !105
  %22 = call i32 @sleep(i32 1), !dbg !106
  br label %23, !dbg !107

23:                                               ; preds = %13, %1
  %24 = getelementptr inbounds %struct._request_get_a_datatype, %struct._request_get_a_datatype* %5, i32 0, i32 0, !dbg !108
  store i32 0, i32* %24, align 1, !dbg !109
  %25 = load i32, i32* @_rpc_get_a.req_counter, align 4, !dbg !110
  %26 = getelementptr inbounds %struct._request_get_a_datatype, %struct._request_get_a_datatype* %5, i32 0, i32 1, !dbg !111
  %27 = getelementptr inbounds %struct._trailer_datatype, %struct._trailer_datatype* %26, i32 0, i32 0, !dbg !112
  store i32 %25, i32* %27, align 1, !dbg !113
  %28 = load i32, i32* @_rpc_get_a.req_counter, align 4, !dbg !114
  %29 = icmp eq i32 %28, -2147483648, !dbg !116
  br i1 %29, label %30, label %59, !dbg !117

30:                                               ; preds = %23
  call void @llvm.dbg.declare(metadata i32* %9, metadata !118, metadata !DIExpression()), !dbg !120
  store i32 30, i32* %9, align 4, !dbg !120
  br label %31, !dbg !121

31:                                               ; preds = %44, %30
  %32 = load i32, i32* %9, align 4, !dbg !122
  %33 = icmp ne i32 %32, 0, !dbg !123
  br i1 %33, label %34, label %48, !dbg !121

34:                                               ; preds = %31
  %35 = load i8*, i8** @_rpc_get_a.psocket, align 8, !dbg !124
  %36 = bitcast %struct._request_get_a_datatype* %5 to i8*, !dbg !126
  call void @xdc_asyn_send(i8* %35, i8* %36, %struct._tag* %3), !dbg !127
  %37 = load i8*, i8** @_rpc_get_a.ssocket, align 8, !dbg !128
  %38 = bitcast %struct._response_get_a_datatype* %6 to i8*, !dbg !129
  %39 = call i32 @xdc_recv(i8* %37, i8* %38, %struct._tag* %4), !dbg !130
  %40 = load i32*, i32** %2, align 8, !dbg !131
  store i32 %39, i32* %40, align 4, !dbg !132
  %41 = load i32*, i32** %2, align 8, !dbg !133
  %42 = load i32, i32* %41, align 4, !dbg !135
  %43 = icmp eq i32 %42, -1, !dbg !136
  br i1 %43, label %44, label %47, !dbg !137

44:                                               ; preds = %34
  %45 = load i32, i32* %9, align 4, !dbg !138
  %46 = add nsw i32 %45, -1, !dbg !138
  store i32 %46, i32* %9, align 4, !dbg !138
  br label %31, !dbg !140, !llvm.loop !141

47:                                               ; preds = %34
  br label %48, !dbg !143

48:                                               ; preds = %47, %31
  %49 = load i32*, i32** %2, align 8, !dbg !144
  %50 = load i32, i32* %49, align 4, !dbg !146
  %51 = icmp sge i32 %50, 0, !dbg !147
  br i1 %51, label %52, label %58, !dbg !148

52:                                               ; preds = %48
  %53 = getelementptr inbounds %struct._response_get_a_datatype, %struct._response_get_a_datatype* %6, i32 0, i32 1, !dbg !149
  %54 = getelementptr inbounds %struct._trailer_datatype, %struct._trailer_datatype* %53, i32 0, i32 0, !dbg !150
  %55 = load i32, i32* %54, align 1, !dbg !150
  %56 = lshr i32 %55, 2, !dbg !151
  %57 = add i32 1, %56, !dbg !152
  store i32 %57, i32* @_rpc_get_a.req_counter, align 4, !dbg !153
  br label %58, !dbg !154

58:                                               ; preds = %52, %48
  br label %59, !dbg !155

59:                                               ; preds = %58, %23
  %60 = getelementptr inbounds %struct._request_get_a_datatype, %struct._request_get_a_datatype* %5, i32 0, i32 0, !dbg !156
  store i32 0, i32* %60, align 1, !dbg !157
  %61 = load i32, i32* @_rpc_get_a.req_counter, align 4, !dbg !158
  %62 = getelementptr inbounds %struct._request_get_a_datatype, %struct._request_get_a_datatype* %5, i32 0, i32 1, !dbg !159
  %63 = getelementptr inbounds %struct._trailer_datatype, %struct._trailer_datatype* %62, i32 0, i32 0, !dbg !160
  store i32 %61, i32* %63, align 1, !dbg !161
  call void @llvm.dbg.declare(metadata i32* %10, metadata !162, metadata !DIExpression()), !dbg !163
  store i32 30, i32* %10, align 4, !dbg !163
  br label %64, !dbg !164

64:                                               ; preds = %77, %59
  %65 = load i32, i32* %10, align 4, !dbg !165
  %66 = icmp ne i32 %65, 0, !dbg !166
  br i1 %66, label %67, label %81, !dbg !164

67:                                               ; preds = %64
  %68 = load i8*, i8** @_rpc_get_a.psocket, align 8, !dbg !167
  %69 = bitcast %struct._request_get_a_datatype* %5 to i8*, !dbg !169
  call void @xdc_asyn_send(i8* %68, i8* %69, %struct._tag* %3), !dbg !170
  %70 = load i8*, i8** @_rpc_get_a.ssocket, align 8, !dbg !171
  %71 = bitcast %struct._response_get_a_datatype* %6 to i8*, !dbg !172
  %72 = call i32 @xdc_recv(i8* %70, i8* %71, %struct._tag* %4), !dbg !173
  %73 = load i32*, i32** %2, align 8, !dbg !174
  store i32 %72, i32* %73, align 4, !dbg !175
  %74 = load i32*, i32** %2, align 8, !dbg !176
  %75 = load i32, i32* %74, align 4, !dbg !178
  %76 = icmp eq i32 %75, -1, !dbg !179
  br i1 %76, label %77, label %80, !dbg !180

77:                                               ; preds = %67
  %78 = load i32, i32* %10, align 4, !dbg !181
  %79 = add nsw i32 %78, -1, !dbg !181
  store i32 %79, i32* %10, align 4, !dbg !181
  br label %64, !dbg !183, !llvm.loop !184

80:                                               ; preds = %67
  br label %81, !dbg !186

81:                                               ; preds = %80, %64
  %82 = load i32, i32* @_rpc_get_a.req_counter, align 4, !dbg !187
  %83 = add nsw i32 %82, 1, !dbg !187
  store i32 %83, i32* @_rpc_get_a.req_counter, align 4, !dbg !187
  %84 = getelementptr inbounds %struct._response_get_a_datatype, %struct._response_get_a_datatype* %6, i32 0, i32 0, !dbg !188
  %85 = load double, double* %84, align 1, !dbg !188
  store double %85, double* %7, align 8, !dbg !189
  %86 = load double, double* %7, align 8, !dbg !190
  ret double %86, !dbg !191
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
define dso_local double @_err_handle_rpc_get_a() #0 !dbg !192 {
  %1 = alloca i32, align 4
  %2 = alloca double, align 8
  call void @llvm.dbg.declare(metadata i32* %1, metadata !195, metadata !DIExpression()), !dbg !196
  call void @llvm.dbg.declare(metadata double* %2, metadata !197, metadata !DIExpression()), !dbg !198
  %3 = call double @_rpc_get_a(i32* %1), !dbg !199
  store double %3, double* %2, align 8, !dbg !198
  %4 = load double, double* %2, align 8, !dbg !200
  ret double %4, !dbg !201
}

; Function Attrs: noinline nounwind optnone uwtable
define dso_local void @_master_rpc_init() #0 !dbg !202 {
  call void @_hal_init(i8* getelementptr inbounds ([26 x i8], [26 x i8]* @.str.3, i64 0, i64 0), i8* getelementptr inbounds ([26 x i8], [26 x i8]* @.str.4, i64 0, i64 0)), !dbg !205
  ret void, !dbg !206
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
!2 = distinct !DISubprogram(name: "_rpc_get_a", scope: !3, file: !3, line: 18, type: !4, scopeLine: 18, flags: DIFlagPrototyped, spFlags: DISPFlagDefinition, unit: !9, retainedNodes: !11)
!3 = !DIFile(filename: "partitioned/multithreaded/purple/purple_rpc.c", directory: "/workspaces/build/apps/examples/example1")
!4 = !DISubroutineType(types: !5)
!5 = !{!6, !7}
!6 = !DIBasicType(name: "double", size: 64, encoding: DW_ATE_float)
!7 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !8, size: 64)
!8 = !DIBasicType(name: "int", size: 32, encoding: DW_ATE_signed)
!9 = distinct !DICompileUnit(language: DW_LANG_C99, file: !10, producer: "clang version 10.0.0-4ubuntu1 ", isOptimized: false, runtimeVersion: 0, emissionKind: FullDebug, enums: !11, retainedTypes: !12, globals: !15, splitDebugInlining: false, nameTableKind: None)
!10 = !DIFile(filename: "/workspaces/build/apps/examples/example1/partitioned/multithreaded/purple/purple_rpc.c", directory: "/workspaces/build/apps/examples/example1")
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
!46 = !DILocalVariable(name: "error", arg: 1, scope: !2, file: !3, line: 18, type: !7)
!47 = !DILocation(line: 18, column: 24, scope: !2)
!48 = !DILocalVariable(name: "t_tag", scope: !2, file: !3, line: 21, type: !49)
!49 = !DIDerivedType(tag: DW_TAG_typedef, name: "gaps_tag", file: !50, line: 32, baseType: !51)
!50 = !DIFile(filename: "/opt/closure/include/xdcomms.h", directory: "")
!51 = distinct !DICompositeType(tag: DW_TAG_structure_type, name: "_tag", file: !50, line: 28, size: 96, elements: !52)
!52 = !{!53, !59, !60}
!53 = !DIDerivedType(tag: DW_TAG_member, name: "mux", scope: !51, file: !50, line: 29, baseType: !54, size: 32)
!54 = !DIDerivedType(tag: DW_TAG_typedef, name: "uint32_t", file: !55, line: 26, baseType: !56)
!55 = !DIFile(filename: "/usr/include/x86_64-linux-gnu/bits/stdint-uintn.h", directory: "")
!56 = !DIDerivedType(tag: DW_TAG_typedef, name: "__uint32_t", file: !57, line: 42, baseType: !58)
!57 = !DIFile(filename: "/usr/include/x86_64-linux-gnu/bits/types.h", directory: "")
!58 = !DIBasicType(name: "unsigned int", size: 32, encoding: DW_ATE_unsigned)
!59 = !DIDerivedType(tag: DW_TAG_member, name: "sec", scope: !51, file: !50, line: 30, baseType: !54, size: 32, offset: 32)
!60 = !DIDerivedType(tag: DW_TAG_member, name: "typ", scope: !51, file: !50, line: 31, baseType: !54, size: 32, offset: 64)
!61 = !DILocation(line: 21, column: 14, scope: !2)
!62 = !DILocalVariable(name: "o_tag", scope: !2, file: !3, line: 22, type: !49)
!63 = !DILocation(line: 22, column: 14, scope: !2)
!64 = !DILocation(line: 26, column: 5, scope: !2)
!65 = !DILocation(line: 31, column: 5, scope: !2)
!66 = !DILocalVariable(name: "request_get_a", scope: !2, file: !3, line: 45, type: !67)
!67 = !DIDerivedType(tag: DW_TAG_typedef, name: "request_get_a_datatype", file: !68, line: 75, baseType: !69)
!68 = !DIFile(filename: "partitioned/multithreaded/autogen/codec.h", directory: "/workspaces/build/apps/examples/example1")
!69 = distinct !DICompositeType(tag: DW_TAG_structure_type, name: "_request_get_a_datatype", file: !68, line: 72, size: 160, elements: !70)
!70 = !{!71, !75}
!71 = !DIDerivedType(tag: DW_TAG_member, name: "dummy", scope: !69, file: !68, line: 73, baseType: !72, size: 32)
!72 = !DIDerivedType(tag: DW_TAG_typedef, name: "int32_t", file: !73, line: 26, baseType: !74)
!73 = !DIFile(filename: "/usr/include/x86_64-linux-gnu/bits/stdint-intn.h", directory: "")
!74 = !DIDerivedType(tag: DW_TAG_typedef, name: "__int32_t", file: !57, line: 41, baseType: !8)
!75 = !DIDerivedType(tag: DW_TAG_member, name: "trailer", scope: !69, file: !68, line: 74, baseType: !76, size: 128, offset: 32)
!76 = !DIDerivedType(tag: DW_TAG_typedef, name: "trailer_datatype", file: !68, line: 28, baseType: !77)
!77 = distinct !DICompositeType(tag: DW_TAG_structure_type, name: "_trailer_datatype", file: !68, line: 22, size: 128, elements: !78)
!78 = !{!79, !80, !81, !82, !86}
!79 = !DIDerivedType(tag: DW_TAG_member, name: "seq", scope: !77, file: !68, line: 23, baseType: !54, size: 32)
!80 = !DIDerivedType(tag: DW_TAG_member, name: "rqr", scope: !77, file: !68, line: 24, baseType: !54, size: 32, offset: 32)
!81 = !DIDerivedType(tag: DW_TAG_member, name: "oid", scope: !77, file: !68, line: 25, baseType: !54, size: 32, offset: 64)
!82 = !DIDerivedType(tag: DW_TAG_member, name: "mid", scope: !77, file: !68, line: 26, baseType: !83, size: 16, offset: 96)
!83 = !DIDerivedType(tag: DW_TAG_typedef, name: "uint16_t", file: !55, line: 25, baseType: !84)
!84 = !DIDerivedType(tag: DW_TAG_typedef, name: "__uint16_t", file: !57, line: 40, baseType: !85)
!85 = !DIBasicType(name: "unsigned short", size: 16, encoding: DW_ATE_unsigned)
!86 = !DIDerivedType(tag: DW_TAG_member, name: "crc", scope: !77, file: !68, line: 27, baseType: !83, size: 16, offset: 112)
!87 = !DILocation(line: 45, column: 28, scope: !2)
!88 = !DILocalVariable(name: "response_get_a", scope: !2, file: !3, line: 48, type: !89)
!89 = !DIDerivedType(tag: DW_TAG_typedef, name: "response_get_a_datatype", file: !68, line: 89, baseType: !90)
!90 = distinct !DICompositeType(tag: DW_TAG_structure_type, name: "_response_get_a_datatype", file: !68, line: 86, size: 192, elements: !91)
!91 = !{!92, !93}
!92 = !DIDerivedType(tag: DW_TAG_member, name: "ret", scope: !90, file: !68, line: 87, baseType: !6, size: 64)
!93 = !DIDerivedType(tag: DW_TAG_member, name: "trailer", scope: !90, file: !68, line: 88, baseType: !76, size: 128, offset: 64)
!94 = !DILocation(line: 48, column: 29, scope: !2)
!95 = !DILocalVariable(name: "result", scope: !2, file: !3, line: 50, type: !6)
!96 = !DILocation(line: 50, column: 12, scope: !2)
!97 = !DILocation(line: 63, column: 10, scope: !98)
!98 = distinct !DILexicalBlock(scope: !2, file: !3, line: 63, column: 9)
!99 = !DILocation(line: 63, column: 9, scope: !2)
!100 = !DILocation(line: 64, column: 16, scope: !101)
!101 = distinct !DILexicalBlock(scope: !98, file: !3, line: 63, column: 18)
!102 = !DILocation(line: 65, column: 19, scope: !101)
!103 = !DILocation(line: 65, column: 17, scope: !101)
!104 = !DILocation(line: 66, column: 19, scope: !101)
!105 = !DILocation(line: 66, column: 17, scope: !101)
!106 = !DILocation(line: 67, column: 9, scope: !101)
!107 = !DILocation(line: 68, column: 5, scope: !101)
!108 = !DILocation(line: 70, column: 19, scope: !2)
!109 = !DILocation(line: 70, column: 25, scope: !2)
!110 = !DILocation(line: 71, column: 33, scope: !2)
!111 = !DILocation(line: 71, column: 19, scope: !2)
!112 = !DILocation(line: 71, column: 27, scope: !2)
!113 = !DILocation(line: 71, column: 31, scope: !2)
!114 = !DILocation(line: 95, column: 9, scope: !115)
!115 = distinct !DILexicalBlock(scope: !2, file: !3, line: 95, column: 9)
!116 = !DILocation(line: 95, column: 21, scope: !115)
!117 = !DILocation(line: 95, column: 9, scope: !2)
!118 = !DILocalVariable(name: "tries_remaining", scope: !119, file: !3, line: 96, type: !8)
!119 = distinct !DILexicalBlock(scope: !115, file: !3, line: 95, column: 33)
!120 = !DILocation(line: 96, column: 13, scope: !119)
!121 = !DILocation(line: 97, column: 9, scope: !119)
!122 = !DILocation(line: 97, column: 15, scope: !119)
!123 = !DILocation(line: 97, column: 31, scope: !119)
!124 = !DILocation(line: 98, column: 27, scope: !125)
!125 = distinct !DILexicalBlock(scope: !119, file: !3, line: 97, column: 36)
!126 = !DILocation(line: 98, column: 36, scope: !125)
!127 = !DILocation(line: 98, column: 13, scope: !125)
!128 = !DILocation(line: 100, column: 31, scope: !125)
!129 = !DILocation(line: 100, column: 40, scope: !125)
!130 = !DILocation(line: 100, column: 22, scope: !125)
!131 = !DILocation(line: 100, column: 14, scope: !125)
!132 = !DILocation(line: 100, column: 20, scope: !125)
!133 = !DILocation(line: 101, column: 18, scope: !134)
!134 = distinct !DILexicalBlock(scope: !125, file: !3, line: 101, column: 17)
!135 = !DILocation(line: 101, column: 17, scope: !134)
!136 = !DILocation(line: 101, column: 24, scope: !134)
!137 = !DILocation(line: 101, column: 17, scope: !125)
!138 = !DILocation(line: 102, column: 32, scope: !139)
!139 = distinct !DILexicalBlock(scope: !134, file: !3, line: 101, column: 30)
!140 = !DILocation(line: 103, column: 17, scope: !139)
!141 = distinct !{!141, !121, !142}
!142 = !DILocation(line: 109, column: 9, scope: !119)
!143 = !DILocation(line: 108, column: 13, scope: !125)
!144 = !DILocation(line: 111, column: 14, scope: !145)
!145 = distinct !DILexicalBlock(scope: !119, file: !3, line: 111, column: 13)
!146 = !DILocation(line: 111, column: 13, scope: !145)
!147 = !DILocation(line: 111, column: 20, scope: !145)
!148 = !DILocation(line: 111, column: 13, scope: !119)
!149 = !DILocation(line: 111, column: 60, scope: !145)
!150 = !DILocation(line: 111, column: 68, scope: !145)
!151 = !DILocation(line: 111, column: 72, scope: !145)
!152 = !DILocation(line: 111, column: 42, scope: !145)
!153 = !DILocation(line: 111, column: 38, scope: !145)
!154 = !DILocation(line: 111, column: 26, scope: !145)
!155 = !DILocation(line: 115, column: 5, scope: !119)
!156 = !DILocation(line: 117, column: 19, scope: !2)
!157 = !DILocation(line: 117, column: 25, scope: !2)
!158 = !DILocation(line: 118, column: 33, scope: !2)
!159 = !DILocation(line: 118, column: 19, scope: !2)
!160 = !DILocation(line: 118, column: 27, scope: !2)
!161 = !DILocation(line: 118, column: 31, scope: !2)
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
!188 = !DILocation(line: 155, column: 29, scope: !2)
!189 = !DILocation(line: 155, column: 12, scope: !2)
!190 = !DILocation(line: 156, column: 13, scope: !2)
!191 = !DILocation(line: 156, column: 5, scope: !2)
!192 = distinct !DISubprogram(name: "_err_handle_rpc_get_a", scope: !3, file: !3, line: 164, type: !193, scopeLine: 164, flags: DIFlagPrototyped, spFlags: DISPFlagDefinition, unit: !9, retainedNodes: !11)
!193 = !DISubroutineType(types: !194)
!194 = !{!6}
!195 = !DILocalVariable(name: "err_num", scope: !192, file: !3, line: 167, type: !8)
!196 = !DILocation(line: 167, column: 6, scope: !192)
!197 = !DILocalVariable(name: "res", scope: !192, file: !3, line: 168, type: !6)
!198 = !DILocation(line: 168, column: 9, scope: !192)
!199 = !DILocation(line: 168, column: 15, scope: !192)
!200 = !DILocation(line: 170, column: 9, scope: !192)
!201 = !DILocation(line: 170, column: 2, scope: !192)
!202 = distinct !DISubprogram(name: "_master_rpc_init", scope: !3, file: !3, line: 172, type: !203, scopeLine: 172, spFlags: DISPFlagDefinition, unit: !9, retainedNodes: !11)
!203 = !DISubroutineType(types: !204)
!204 = !{null}
!205 = !DILocation(line: 173, column: 5, scope: !202)
!206 = !DILocation(line: 174, column: 1, scope: !202)
