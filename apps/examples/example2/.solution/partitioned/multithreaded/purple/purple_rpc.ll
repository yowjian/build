; ModuleID = '/workspaces/build/apps/examples/example2/partitioned/multithreaded/purple/purple_rpc.c'
source_filename = "/workspaces/build/apps/examples/example2/partitioned/multithreaded/purple/purple_rpc.c"
target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-pc-linux-gnu"

%struct._tag = type { i32, i32, i32 }
%struct._request_get_ewma_datatype = type { double, %struct._trailer_datatype }
%struct._trailer_datatype = type { i32, i32, i32, i16, i16 }
%struct._response_get_ewma_datatype = type { double, %struct._trailer_datatype }
%union.pthread_attr_t = type { i64, [48 x i8] }

@_handle_request_get_ewma.res_counter = internal global i32 0, align 4, !dbg !0
@_handle_request_get_ewma.last_processed_result = internal global double 0.000000e+00, align 8, !dbg !14
@_handle_request_get_ewma.last_processed_error = internal global i32 0, align 4, !dbg !17
@_handle_request_get_ewma.inited = internal global i32 0, align 4, !dbg !20
@_handle_request_get_ewma.psocket = internal global i8* null, align 8, !dbg !22
@_handle_request_get_ewma.ssocket = internal global i8* null, align 8, !dbg !24
@.str = private unnamed_addr constant [24 x i8] c"HANDLE_REQUEST_GET_EWMA\00", section "llvm.metadata"
@.str.1 = private unnamed_addr constant [87 x i8] c"/workspaces/build/apps/examples/example2/partitioned/multithreaded/purple/purple_rpc.c\00", section "llvm.metadata"
@.str.2 = private unnamed_addr constant [26 x i8] c"ipc:///tmp/sock_subpurple\00", align 1
@.str.3 = private unnamed_addr constant [26 x i8] c"ipc:///tmp/sock_pubpurple\00", align 1
@llvm.global.annotations = appending global [1 x { i8*, i8*, i8*, i32 }] [{ i8*, i8*, i8*, i32 } { i8* bitcast (void ()* @_handle_request_get_ewma to i8*), i8* getelementptr inbounds ([24 x i8], [24 x i8]* @.str, i32 0, i32 0), i8* getelementptr inbounds ([87 x i8], [87 x i8]* @.str.1, i32 0, i32 0), i32 18 }], section "llvm.metadata"

; Function Attrs: noinline nounwind optnone uwtable
define dso_local void @_hal_init(i8* %0, i8* %1) #0 !dbg !30 {
  %3 = alloca i8*, align 8
  %4 = alloca i8*, align 8
  store i8* %0, i8** %3, align 8
  call void @llvm.dbg.declare(metadata i8** %3, metadata !33, metadata !DIExpression()), !dbg !34
  store i8* %1, i8** %4, align 8
  call void @llvm.dbg.declare(metadata i8** %4, metadata !35, metadata !DIExpression()), !dbg !36
  call void @xdc_log_level(i32 2), !dbg !37
  %5 = load i8*, i8** %3, align 8, !dbg !38
  %6 = call i8* @xdc_set_in(i8* %5), !dbg !39
  %7 = load i8*, i8** %4, align 8, !dbg !40
  %8 = call i8* @xdc_set_out(i8* %7), !dbg !41
  call void @xdc_register(void (i8*, i8*, i64*)* @request_get_ewma_data_encode, void (i8*, i8*, i64*)* @request_get_ewma_data_decode, i32 3), !dbg !42
  call void @xdc_register(void (i8*, i8*, i64*)* @response_get_ewma_data_encode, void (i8*, i8*, i64*)* @response_get_ewma_data_decode, i32 4), !dbg !43
  ret void, !dbg !44
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
define dso_local void @_handle_request_get_ewma() #0 !dbg !2 {
  %1 = alloca %struct._tag, align 4
  %2 = alloca %struct._tag, align 4
  %3 = alloca %struct._request_get_ewma_datatype, align 1
  %4 = alloca %struct._response_get_ewma_datatype, align 1
  %5 = alloca { i64, i32 }, align 4
  %6 = alloca i32, align 4
  %7 = alloca i32, align 4
  call void @llvm.dbg.declare(metadata %struct._tag* %1, metadata !45, metadata !DIExpression()), !dbg !58
  call void @llvm.dbg.declare(metadata %struct._tag* %2, metadata !59, metadata !DIExpression()), !dbg !60
  call void @tag_write(%struct._tag* %1, i32 1, i32 1, i32 3), !dbg !61
  call void @tag_write(%struct._tag* %2, i32 2, i32 2, i32 4), !dbg !62
  call void @llvm.dbg.declare(metadata %struct._request_get_ewma_datatype* %3, metadata !63, metadata !DIExpression()), !dbg !81
  call void @llvm.dbg.declare(metadata %struct._response_get_ewma_datatype* %4, metadata !82, metadata !DIExpression()), !dbg !88
  %8 = load i32, i32* @_handle_request_get_ewma.inited, align 4, !dbg !89
  %9 = icmp ne i32 %8, 0, !dbg !89
  br i1 %9, label %20, label %10, !dbg !91

10:                                               ; preds = %0
  store i32 1, i32* @_handle_request_get_ewma.inited, align 4, !dbg !92
  %11 = call i8* @xdc_pub_socket(), !dbg !94
  store i8* %11, i8** @_handle_request_get_ewma.psocket, align 8, !dbg !95
  %12 = bitcast { i64, i32 }* %5 to i8*, !dbg !96
  %13 = bitcast %struct._tag* %1 to i8*, !dbg !96
  call void @llvm.memcpy.p0i8.p0i8.i64(i8* align 4 %12, i8* align 4 %13, i64 12, i1 false), !dbg !96
  %14 = getelementptr inbounds { i64, i32 }, { i64, i32 }* %5, i32 0, i32 0, !dbg !96
  %15 = load i64, i64* %14, align 4, !dbg !96
  %16 = getelementptr inbounds { i64, i32 }, { i64, i32 }* %5, i32 0, i32 1, !dbg !96
  %17 = load i32, i32* %16, align 4, !dbg !96
  %18 = call i8* @xdc_sub_socket(i64 %15, i32 %17), !dbg !96
  store i8* %18, i8** @_handle_request_get_ewma.ssocket, align 8, !dbg !97
  %19 = call i32 @sleep(i32 1), !dbg !98
  br label %20, !dbg !99

20:                                               ; preds = %10, %0
  call void @llvm.dbg.declare(metadata i32* %6, metadata !100, metadata !DIExpression()), !dbg !101
  store i32 1, i32* %6, align 4, !dbg !101
  br label %21, !dbg !102

21:                                               ; preds = %41, %20
  %22 = load i32, i32* %6, align 4, !dbg !103
  %23 = icmp eq i32 %22, 1, !dbg !104
  br i1 %23, label %24, label %51, !dbg !102

24:                                               ; preds = %21
  %25 = load i8*, i8** @_handle_request_get_ewma.ssocket, align 8, !dbg !105
  %26 = bitcast %struct._request_get_ewma_datatype* %3 to i8*, !dbg !107
  call void @xdc_blocking_recv(i8* %25, i8* %26, %struct._tag* %1), !dbg !108
  call void @llvm.dbg.declare(metadata i32* %7, metadata !109, metadata !DIExpression()), !dbg !110
  %27 = getelementptr inbounds %struct._request_get_ewma_datatype, %struct._request_get_ewma_datatype* %3, i32 0, i32 1, !dbg !111
  %28 = getelementptr inbounds %struct._trailer_datatype, %struct._trailer_datatype* %27, i32 0, i32 0, !dbg !112
  %29 = load i32, i32* %28, align 1, !dbg !112
  store i32 %29, i32* %7, align 4, !dbg !110
  %30 = load i32, i32* %7, align 4, !dbg !113
  %31 = load i32, i32* @_handle_request_get_ewma.res_counter, align 4, !dbg !115
  %32 = icmp sgt i32 %30, %31, !dbg !116
  br i1 %32, label %33, label %41, !dbg !117

33:                                               ; preds = %24
  store i32 0, i32* %6, align 4, !dbg !118
  %34 = load i32, i32* %7, align 4, !dbg !120
  store i32 %34, i32* @_handle_request_get_ewma.res_counter, align 4, !dbg !121
  %35 = getelementptr inbounds %struct._request_get_ewma_datatype, %struct._request_get_ewma_datatype* %3, i32 0, i32 0, !dbg !122
  %36 = load double, double* %35, align 1, !dbg !122
  %37 = call double @get_ewma(double %36), !dbg !123
  store double %37, double* @_handle_request_get_ewma.last_processed_result, align 8, !dbg !124
  %38 = load double, double* @_handle_request_get_ewma.last_processed_result, align 8, !dbg !125
  %39 = getelementptr inbounds %struct._response_get_ewma_datatype, %struct._response_get_ewma_datatype* %4, i32 0, i32 0, !dbg !126
  store double %38, double* %39, align 1, !dbg !127
  %40 = load i32, i32* %6, align 4, !dbg !128
  store i32 %40, i32* @_handle_request_get_ewma.last_processed_error, align 4, !dbg !129
  br label %41, !dbg !130

41:                                               ; preds = %33, %24
  %42 = load i32, i32* @_handle_request_get_ewma.res_counter, align 4, !dbg !131
  %43 = shl i32 %42, 2, !dbg !132
  %44 = load i32, i32* @_handle_request_get_ewma.last_processed_error, align 4, !dbg !133
  %45 = shl i32 %44, 1, !dbg !134
  %46 = or i32 %43, %45, !dbg !135
  %47 = getelementptr inbounds %struct._response_get_ewma_datatype, %struct._response_get_ewma_datatype* %4, i32 0, i32 1, !dbg !136
  %48 = getelementptr inbounds %struct._trailer_datatype, %struct._trailer_datatype* %47, i32 0, i32 0, !dbg !137
  store i32 %46, i32* %48, align 1, !dbg !138
  %49 = load i8*, i8** @_handle_request_get_ewma.psocket, align 8, !dbg !139
  %50 = bitcast %struct._response_get_ewma_datatype* %4 to i8*, !dbg !140
  call void @xdc_asyn_send(i8* %49, i8* %50, %struct._tag* %2), !dbg !141
  br label %21, !dbg !102, !llvm.loop !142

51:                                               ; preds = %21
  ret void, !dbg !144
}

declare dso_local void @tag_write(%struct._tag*, i32, i32, i32) #2

declare dso_local i8* @xdc_pub_socket() #2

declare dso_local i8* @xdc_sub_socket(i64, i32) #2

; Function Attrs: argmemonly nounwind willreturn
declare void @llvm.memcpy.p0i8.p0i8.i64(i8* noalias nocapture writeonly, i8* noalias nocapture readonly, i64, i1 immarg) #3

declare dso_local i32 @sleep(i32) #2

declare dso_local void @xdc_blocking_recv(i8*, i8*, %struct._tag*) #2

declare dso_local double @get_ewma(double) #2

declare dso_local void @xdc_asyn_send(i8*, i8*, %struct._tag*) #2

; Function Attrs: noinline nounwind optnone uwtable
define dso_local i8* @_wrapper_request_get_ewma(i8* %0) #0 !dbg !145 {
  %2 = alloca i8*, align 8
  store i8* %0, i8** %2, align 8
  call void @llvm.dbg.declare(metadata i8** %2, metadata !148, metadata !DIExpression()), !dbg !149
  br label %3, !dbg !149

3:                                                ; preds = %1, %3
  call void @_handle_request_get_ewma(), !dbg !150
  br label %3, !dbg !149, !llvm.loop !152
}

; Function Attrs: noinline nounwind optnone uwtable
define dso_local i32 @_slave_rpc_loop() #0 !dbg !153 {
  %1 = alloca [1 x i64], align 8
  %2 = alloca i32, align 4
  call void @_hal_init(i8* getelementptr inbounds ([26 x i8], [26 x i8]* @.str.2, i64 0, i64 0), i8* getelementptr inbounds ([26 x i8], [26 x i8]* @.str.3, i64 0, i64 0)), !dbg !156
  call void @llvm.dbg.declare(metadata [1 x i64]* %1, metadata !157, metadata !DIExpression()), !dbg !164
  %3 = getelementptr inbounds [1 x i64], [1 x i64]* %1, i64 0, i64 0, !dbg !165
  %4 = call i32 @pthread_create(i64* %3, %union.pthread_attr_t* null, i8* (i8*)* @_wrapper_request_get_ewma, i8* null) #5, !dbg !166
  call void @llvm.dbg.declare(metadata i32* %2, metadata !167, metadata !DIExpression()), !dbg !169
  store i32 0, i32* %2, align 4, !dbg !169
  br label %5, !dbg !170

5:                                                ; preds = %14, %0
  %6 = load i32, i32* %2, align 4, !dbg !171
  %7 = icmp slt i32 %6, 1, !dbg !173
  br i1 %7, label %8, label %17, !dbg !174

8:                                                ; preds = %5
  %9 = load i32, i32* %2, align 4, !dbg !175
  %10 = sext i32 %9 to i64, !dbg !176
  %11 = getelementptr inbounds [1 x i64], [1 x i64]* %1, i64 0, i64 %10, !dbg !176
  %12 = load i64, i64* %11, align 8, !dbg !176
  %13 = call i32 @pthread_join(i64 %12, i8** null), !dbg !177
  br label %14, !dbg !177

14:                                               ; preds = %8
  %15 = load i32, i32* %2, align 4, !dbg !178
  %16 = add nsw i32 %15, 1, !dbg !178
  store i32 %16, i32* %2, align 4, !dbg !178
  br label %5, !dbg !179, !llvm.loop !180

17:                                               ; preds = %5
  ret i32 0, !dbg !182
}

; Function Attrs: nounwind
declare !callback !183 dso_local i32 @pthread_create(i64*, %union.pthread_attr_t*, i8* (i8*)*, i8*) #4

declare dso_local i32 @pthread_join(i64, i8**) #2

attributes #0 = { noinline nounwind optnone uwtable "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "frame-pointer"="all" "less-precise-fpmad"="false" "min-legal-vector-width"="0" "no-infs-fp-math"="false" "no-jump-tables"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { nounwind readnone speculatable willreturn }
attributes #2 = { "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "frame-pointer"="all" "less-precise-fpmad"="false" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #3 = { argmemonly nounwind willreturn }
attributes #4 = { nounwind "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "frame-pointer"="all" "less-precise-fpmad"="false" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #5 = { nounwind }

!llvm.dbg.cu = !{!6}
!llvm.module.flags = !{!26, !27, !28}
!llvm.ident = !{!29}

!0 = !DIGlobalVariableExpression(var: !1, expr: !DIExpression())
!1 = distinct !DIGlobalVariable(name: "res_counter", scope: !2, file: !3, line: 33, type: !19, isLocal: true, isDefinition: true)
!2 = distinct !DISubprogram(name: "_handle_request_get_ewma", scope: !3, file: !3, line: 18, type: !4, scopeLine: 18, spFlags: DISPFlagDefinition, unit: !6, retainedNodes: !8)
!3 = !DIFile(filename: "partitioned/multithreaded/purple/purple_rpc.c", directory: "/workspaces/build/apps/examples/example2")
!4 = !DISubroutineType(types: !5)
!5 = !{null}
!6 = distinct !DICompileUnit(language: DW_LANG_C99, file: !7, producer: "clang version 10.0.0-4ubuntu1 ", isOptimized: false, runtimeVersion: 0, emissionKind: FullDebug, enums: !8, retainedTypes: !9, globals: !13, splitDebugInlining: false, nameTableKind: None)
!7 = !DIFile(filename: "/workspaces/build/apps/examples/example2/partitioned/multithreaded/purple/purple_rpc.c", directory: "/workspaces/build/apps/examples/example2")
!8 = !{}
!9 = !{!10, !12}
!10 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !11, size: 64)
!11 = !DIBasicType(name: "char", size: 8, encoding: DW_ATE_signed_char)
!12 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: null, size: 64)
!13 = !{!0, !14, !17, !20, !22, !24}
!14 = !DIGlobalVariableExpression(var: !15, expr: !DIExpression())
!15 = distinct !DIGlobalVariable(name: "last_processed_result", scope: !2, file: !3, line: 34, type: !16, isLocal: true, isDefinition: true)
!16 = !DIBasicType(name: "double", size: 64, encoding: DW_ATE_float)
!17 = !DIGlobalVariableExpression(var: !18, expr: !DIExpression())
!18 = distinct !DIGlobalVariable(name: "last_processed_error", scope: !2, file: !3, line: 35, type: !19, isLocal: true, isDefinition: true)
!19 = !DIBasicType(name: "int", size: 32, encoding: DW_ATE_signed)
!20 = !DIGlobalVariableExpression(var: !21, expr: !DIExpression())
!21 = distinct !DIGlobalVariable(name: "inited", scope: !2, file: !3, line: 36, type: !19, isLocal: true, isDefinition: true)
!22 = !DIGlobalVariableExpression(var: !23, expr: !DIExpression())
!23 = distinct !DIGlobalVariable(name: "psocket", scope: !2, file: !3, line: 41, type: !12, isLocal: true, isDefinition: true)
!24 = !DIGlobalVariableExpression(var: !25, expr: !DIExpression())
!25 = distinct !DIGlobalVariable(name: "ssocket", scope: !2, file: !3, line: 42, type: !12, isLocal: true, isDefinition: true)
!26 = !{i32 7, !"Dwarf Version", i32 4}
!27 = !{i32 2, !"Debug Info Version", i32 3}
!28 = !{i32 1, !"wchar_size", i32 4}
!29 = !{!"clang version 10.0.0-4ubuntu1 "}
!30 = distinct !DISubprogram(name: "_hal_init", scope: !3, file: !3, line: 5, type: !31, scopeLine: 5, flags: DIFlagPrototyped, spFlags: DISPFlagDefinition, unit: !6, retainedNodes: !8)
!31 = !DISubroutineType(types: !32)
!32 = !{null, !10, !10}
!33 = !DILocalVariable(name: "inuri", arg: 1, scope: !30, file: !3, line: 5, type: !10)
!34 = !DILocation(line: 5, column: 22, scope: !30)
!35 = !DILocalVariable(name: "outuri", arg: 2, scope: !30, file: !3, line: 5, type: !10)
!36 = !DILocation(line: 5, column: 35, scope: !30)
!37 = !DILocation(line: 6, column: 5, scope: !30)
!38 = !DILocation(line: 8, column: 16, scope: !30)
!39 = !DILocation(line: 8, column: 5, scope: !30)
!40 = !DILocation(line: 9, column: 17, scope: !30)
!41 = !DILocation(line: 9, column: 5, scope: !30)
!42 = !DILocation(line: 10, column: 5, scope: !30)
!43 = !DILocation(line: 11, column: 5, scope: !30)
!44 = !DILocation(line: 14, column: 1, scope: !30)
!45 = !DILocalVariable(name: "t_tag", scope: !2, file: !3, line: 21, type: !46)
!46 = !DIDerivedType(tag: DW_TAG_typedef, name: "gaps_tag", file: !47, line: 32, baseType: !48)
!47 = !DIFile(filename: "/opt/closure/include/xdcomms.h", directory: "")
!48 = distinct !DICompositeType(tag: DW_TAG_structure_type, name: "_tag", file: !47, line: 28, size: 96, elements: !49)
!49 = !{!50, !56, !57}
!50 = !DIDerivedType(tag: DW_TAG_member, name: "mux", scope: !48, file: !47, line: 29, baseType: !51, size: 32)
!51 = !DIDerivedType(tag: DW_TAG_typedef, name: "uint32_t", file: !52, line: 26, baseType: !53)
!52 = !DIFile(filename: "/usr/include/x86_64-linux-gnu/bits/stdint-uintn.h", directory: "")
!53 = !DIDerivedType(tag: DW_TAG_typedef, name: "__uint32_t", file: !54, line: 42, baseType: !55)
!54 = !DIFile(filename: "/usr/include/x86_64-linux-gnu/bits/types.h", directory: "")
!55 = !DIBasicType(name: "unsigned int", size: 32, encoding: DW_ATE_unsigned)
!56 = !DIDerivedType(tag: DW_TAG_member, name: "sec", scope: !48, file: !47, line: 30, baseType: !51, size: 32, offset: 32)
!57 = !DIDerivedType(tag: DW_TAG_member, name: "typ", scope: !48, file: !47, line: 31, baseType: !51, size: 32, offset: 64)
!58 = !DILocation(line: 21, column: 14, scope: !2)
!59 = !DILocalVariable(name: "o_tag", scope: !2, file: !3, line: 22, type: !46)
!60 = !DILocation(line: 22, column: 14, scope: !2)
!61 = !DILocation(line: 26, column: 5, scope: !2)
!62 = !DILocation(line: 31, column: 5, scope: !2)
!63 = !DILocalVariable(name: "request_get_ewma", scope: !2, file: !3, line: 45, type: !64)
!64 = !DIDerivedType(tag: DW_TAG_typedef, name: "request_get_ewma_datatype", file: !65, line: 75, baseType: !66)
!65 = !DIFile(filename: "partitioned/multithreaded/autogen/codec.h", directory: "/workspaces/build/apps/examples/example2")
!66 = distinct !DICompositeType(tag: DW_TAG_structure_type, name: "_request_get_ewma_datatype", file: !65, line: 72, size: 192, elements: !67)
!67 = !{!68, !69}
!68 = !DIDerivedType(tag: DW_TAG_member, name: "x", scope: !66, file: !65, line: 73, baseType: !16, size: 64)
!69 = !DIDerivedType(tag: DW_TAG_member, name: "trailer", scope: !66, file: !65, line: 74, baseType: !70, size: 128, offset: 64)
!70 = !DIDerivedType(tag: DW_TAG_typedef, name: "trailer_datatype", file: !65, line: 28, baseType: !71)
!71 = distinct !DICompositeType(tag: DW_TAG_structure_type, name: "_trailer_datatype", file: !65, line: 22, size: 128, elements: !72)
!72 = !{!73, !74, !75, !76, !80}
!73 = !DIDerivedType(tag: DW_TAG_member, name: "seq", scope: !71, file: !65, line: 23, baseType: !51, size: 32)
!74 = !DIDerivedType(tag: DW_TAG_member, name: "rqr", scope: !71, file: !65, line: 24, baseType: !51, size: 32, offset: 32)
!75 = !DIDerivedType(tag: DW_TAG_member, name: "oid", scope: !71, file: !65, line: 25, baseType: !51, size: 32, offset: 64)
!76 = !DIDerivedType(tag: DW_TAG_member, name: "mid", scope: !71, file: !65, line: 26, baseType: !77, size: 16, offset: 96)
!77 = !DIDerivedType(tag: DW_TAG_typedef, name: "uint16_t", file: !52, line: 25, baseType: !78)
!78 = !DIDerivedType(tag: DW_TAG_typedef, name: "__uint16_t", file: !54, line: 40, baseType: !79)
!79 = !DIBasicType(name: "unsigned short", size: 16, encoding: DW_ATE_unsigned)
!80 = !DIDerivedType(tag: DW_TAG_member, name: "crc", scope: !71, file: !65, line: 27, baseType: !77, size: 16, offset: 112)
!81 = !DILocation(line: 45, column: 31, scope: !2)
!82 = !DILocalVariable(name: "response_get_ewma", scope: !2, file: !3, line: 48, type: !83)
!83 = !DIDerivedType(tag: DW_TAG_typedef, name: "response_get_ewma_datatype", file: !65, line: 89, baseType: !84)
!84 = distinct !DICompositeType(tag: DW_TAG_structure_type, name: "_response_get_ewma_datatype", file: !65, line: 86, size: 192, elements: !85)
!85 = !{!86, !87}
!86 = !DIDerivedType(tag: DW_TAG_member, name: "ret", scope: !84, file: !65, line: 87, baseType: !16, size: 64)
!87 = !DIDerivedType(tag: DW_TAG_member, name: "trailer", scope: !84, file: !65, line: 88, baseType: !70, size: 128, offset: 64)
!88 = !DILocation(line: 48, column: 32, scope: !2)
!89 = !DILocation(line: 62, column: 10, scope: !90)
!90 = distinct !DILexicalBlock(scope: !2, file: !3, line: 62, column: 9)
!91 = !DILocation(line: 62, column: 9, scope: !2)
!92 = !DILocation(line: 63, column: 16, scope: !93)
!93 = distinct !DILexicalBlock(scope: !90, file: !3, line: 62, column: 18)
!94 = !DILocation(line: 64, column: 19, scope: !93)
!95 = !DILocation(line: 64, column: 17, scope: !93)
!96 = !DILocation(line: 65, column: 19, scope: !93)
!97 = !DILocation(line: 65, column: 17, scope: !93)
!98 = !DILocation(line: 66, column: 9, scope: !93)
!99 = !DILocation(line: 67, column: 5, scope: !93)
!100 = !DILocalVariable(name: "proc_error", scope: !2, file: !3, line: 92, type: !19)
!101 = !DILocation(line: 92, column: 9, scope: !2)
!102 = !DILocation(line: 93, column: 5, scope: !2)
!103 = !DILocation(line: 93, column: 12, scope: !2)
!104 = !DILocation(line: 93, column: 23, scope: !2)
!105 = !DILocation(line: 94, column: 27, scope: !106)
!106 = distinct !DILexicalBlock(scope: !2, file: !3, line: 93, column: 29)
!107 = !DILocation(line: 94, column: 36, scope: !106)
!108 = !DILocation(line: 94, column: 9, scope: !106)
!109 = !DILocalVariable(name: "req_counter", scope: !106, file: !3, line: 95, type: !19)
!110 = !DILocation(line: 95, column: 13, scope: !106)
!111 = !DILocation(line: 95, column: 44, scope: !106)
!112 = !DILocation(line: 95, column: 52, scope: !106)
!113 = !DILocation(line: 96, column: 12, scope: !114)
!114 = distinct !DILexicalBlock(scope: !106, file: !3, line: 96, column: 12)
!115 = !DILocation(line: 96, column: 26, scope: !114)
!116 = !DILocation(line: 96, column: 24, scope: !114)
!117 = !DILocation(line: 96, column: 12, scope: !106)
!118 = !DILocation(line: 97, column: 24, scope: !119)
!119 = distinct !DILexicalBlock(scope: !114, file: !3, line: 96, column: 38)
!120 = !DILocation(line: 98, column: 27, scope: !119)
!121 = !DILocation(line: 98, column: 25, scope: !119)
!122 = !DILocation(line: 99, column: 63, scope: !119)
!123 = !DILocation(line: 99, column: 37, scope: !119)
!124 = !DILocation(line: 99, column: 35, scope: !119)
!125 = !DILocation(line: 100, column: 37, scope: !119)
!126 = !DILocation(line: 100, column: 31, scope: !119)
!127 = !DILocation(line: 100, column: 35, scope: !119)
!128 = !DILocation(line: 101, column: 36, scope: !119)
!129 = !DILocation(line: 101, column: 34, scope: !119)
!130 = !DILocation(line: 102, column: 9, scope: !119)
!131 = !DILocation(line: 104, column: 41, scope: !106)
!132 = !DILocation(line: 104, column: 53, scope: !106)
!133 = !DILocation(line: 104, column: 60, scope: !106)
!134 = !DILocation(line: 104, column: 81, scope: !106)
!135 = !DILocation(line: 104, column: 58, scope: !106)
!136 = !DILocation(line: 104, column: 27, scope: !106)
!137 = !DILocation(line: 104, column: 35, scope: !106)
!138 = !DILocation(line: 104, column: 39, scope: !106)
!139 = !DILocation(line: 105, column: 23, scope: !106)
!140 = !DILocation(line: 105, column: 32, scope: !106)
!141 = !DILocation(line: 105, column: 9, scope: !106)
!142 = distinct !{!142, !102, !143}
!143 = !DILocation(line: 109, column: 5, scope: !2)
!144 = !DILocation(line: 111, column: 1, scope: !2)
!145 = distinct !DISubprogram(name: "_wrapper_request_get_ewma", scope: !3, file: !3, line: 113, type: !146, scopeLine: 113, flags: DIFlagPrototyped, spFlags: DISPFlagDefinition, unit: !6, retainedNodes: !8)
!146 = !DISubroutineType(types: !147)
!147 = !{!12, !12}
!148 = !DILocalVariable(name: "tag", arg: 1, scope: !145, file: !3, line: 113, type: !12)
!149 = !DILocation(line: 113, column: 1, scope: !145)
!150 = !DILocation(line: 113, column: 1, scope: !151)
!151 = distinct !DILexicalBlock(scope: !145, file: !3, line: 113, column: 1)
!152 = distinct !{!152, !149, !149}
!153 = distinct !DISubprogram(name: "_slave_rpc_loop", scope: !3, file: !3, line: 116, type: !154, scopeLine: 116, spFlags: DISPFlagDefinition, unit: !6, retainedNodes: !8)
!154 = !DISubroutineType(types: !155)
!155 = !{!19}
!156 = !DILocation(line: 117, column: 5, scope: !153)
!157 = !DILocalVariable(name: "tid", scope: !153, file: !3, line: 118, type: !158)
!158 = !DICompositeType(tag: DW_TAG_array_type, baseType: !159, size: 64, elements: !162)
!159 = !DIDerivedType(tag: DW_TAG_typedef, name: "pthread_t", file: !160, line: 27, baseType: !161)
!160 = !DIFile(filename: "/usr/include/x86_64-linux-gnu/bits/pthreadtypes.h", directory: "")
!161 = !DIBasicType(name: "long unsigned int", size: 64, encoding: DW_ATE_unsigned)
!162 = !{!163}
!163 = !DISubrange(count: 1)
!164 = !DILocation(line: 118, column: 15, scope: !153)
!165 = !DILocation(line: 119, column: 21, scope: !153)
!166 = !DILocation(line: 119, column: 5, scope: !153)
!167 = !DILocalVariable(name: "i", scope: !168, file: !3, line: 120, type: !19)
!168 = distinct !DILexicalBlock(scope: !153, file: !3, line: 120, column: 5)
!169 = !DILocation(line: 120, column: 14, scope: !168)
!170 = !DILocation(line: 120, column: 10, scope: !168)
!171 = !DILocation(line: 120, column: 21, scope: !172)
!172 = distinct !DILexicalBlock(scope: !168, file: !3, line: 120, column: 5)
!173 = !DILocation(line: 120, column: 23, scope: !172)
!174 = !DILocation(line: 120, column: 5, scope: !168)
!175 = !DILocation(line: 120, column: 55, scope: !172)
!176 = !DILocation(line: 120, column: 51, scope: !172)
!177 = !DILocation(line: 120, column: 38, scope: !172)
!178 = !DILocation(line: 120, column: 34, scope: !172)
!179 = !DILocation(line: 120, column: 5, scope: !172)
!180 = distinct !{!180, !174, !181}
!181 = !DILocation(line: 120, column: 63, scope: !168)
!182 = !DILocation(line: 121, column: 5, scope: !153)
!183 = !{!184}
!184 = !{i64 2, i64 3, i1 false}
