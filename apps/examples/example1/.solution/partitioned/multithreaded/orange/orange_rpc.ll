; ModuleID = '/workspaces/build/apps/examples/example1/partitioned/multithreaded/orange/orange_rpc.c'
source_filename = "/workspaces/build/apps/examples/example1/partitioned/multithreaded/orange/orange_rpc.c"
target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-pc-linux-gnu"

%struct._tag = type { i32, i32, i32 }
%struct._request_get_a_datatype = type { i32, %struct._trailer_datatype }
%struct._trailer_datatype = type { i32, i32, i32, i16, i16 }
%struct._response_get_a_datatype = type { double, %struct._trailer_datatype }
%union.pthread_attr_t = type { i64, [48 x i8] }

@_handle_request_get_a.res_counter = internal global i32 0, align 4, !dbg !0
@_handle_request_get_a.last_processed_result = internal global double 0.000000e+00, align 8, !dbg !14
@_handle_request_get_a.last_processed_error = internal global i32 0, align 4, !dbg !17
@_handle_request_get_a.inited = internal global i32 0, align 4, !dbg !20
@_handle_request_get_a.psocket = internal global i8* null, align 8, !dbg !22
@_handle_request_get_a.ssocket = internal global i8* null, align 8, !dbg !24
@.str = private unnamed_addr constant [21 x i8] c"HANDLE_REQUEST_GET_A\00", section "llvm.metadata"
@.str.1 = private unnamed_addr constant [87 x i8] c"/workspaces/build/apps/examples/example1/partitioned/multithreaded/orange/orange_rpc.c\00", section "llvm.metadata"
@.str.2 = private unnamed_addr constant [26 x i8] c"ipc:///tmp/sock_suborange\00", align 1
@.str.3 = private unnamed_addr constant [26 x i8] c"ipc:///tmp/sock_puborange\00", align 1
@llvm.global.annotations = appending global [1 x { i8*, i8*, i8*, i32 }] [{ i8*, i8*, i8*, i32 } { i8* bitcast (void ()* @_handle_request_get_a to i8*), i8* getelementptr inbounds ([21 x i8], [21 x i8]* @.str, i32 0, i32 0), i8* getelementptr inbounds ([87 x i8], [87 x i8]* @.str.1, i32 0, i32 0), i32 18 }], section "llvm.metadata"

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
  call void @xdc_register(void (i8*, i8*, i64*)* @request_get_a_data_encode, void (i8*, i8*, i64*)* @request_get_a_data_decode, i32 3), !dbg !42
  call void @xdc_register(void (i8*, i8*, i64*)* @response_get_a_data_encode, void (i8*, i8*, i64*)* @response_get_a_data_decode, i32 4), !dbg !43
  ret void, !dbg !44
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
define dso_local void @_handle_request_get_a() #0 !dbg !2 {
  %1 = alloca %struct._tag, align 4
  %2 = alloca %struct._tag, align 4
  %3 = alloca %struct._request_get_a_datatype, align 1
  %4 = alloca %struct._response_get_a_datatype, align 1
  %5 = alloca { i64, i32 }, align 4
  %6 = alloca i32, align 4
  %7 = alloca i32, align 4
  call void @llvm.dbg.declare(metadata %struct._tag* %1, metadata !45, metadata !DIExpression()), !dbg !58
  call void @llvm.dbg.declare(metadata %struct._tag* %2, metadata !59, metadata !DIExpression()), !dbg !60
  call void @tag_write(%struct._tag* %1, i32 2, i32 2, i32 3), !dbg !61
  call void @tag_write(%struct._tag* %2, i32 1, i32 1, i32 4), !dbg !62
  call void @llvm.dbg.declare(metadata %struct._request_get_a_datatype* %3, metadata !63, metadata !DIExpression()), !dbg !84
  call void @llvm.dbg.declare(metadata %struct._response_get_a_datatype* %4, metadata !85, metadata !DIExpression()), !dbg !91
  %8 = load i32, i32* @_handle_request_get_a.inited, align 4, !dbg !92
  %9 = icmp ne i32 %8, 0, !dbg !92
  br i1 %9, label %20, label %10, !dbg !94

10:                                               ; preds = %0
  store i32 1, i32* @_handle_request_get_a.inited, align 4, !dbg !95
  %11 = call i8* @xdc_pub_socket(), !dbg !97
  store i8* %11, i8** @_handle_request_get_a.psocket, align 8, !dbg !98
  %12 = bitcast { i64, i32 }* %5 to i8*, !dbg !99
  %13 = bitcast %struct._tag* %1 to i8*, !dbg !99
  call void @llvm.memcpy.p0i8.p0i8.i64(i8* align 4 %12, i8* align 4 %13, i64 12, i1 false), !dbg !99
  %14 = getelementptr inbounds { i64, i32 }, { i64, i32 }* %5, i32 0, i32 0, !dbg !99
  %15 = load i64, i64* %14, align 4, !dbg !99
  %16 = getelementptr inbounds { i64, i32 }, { i64, i32 }* %5, i32 0, i32 1, !dbg !99
  %17 = load i32, i32* %16, align 4, !dbg !99
  %18 = call i8* @xdc_sub_socket(i64 %15, i32 %17), !dbg !99
  store i8* %18, i8** @_handle_request_get_a.ssocket, align 8, !dbg !100
  %19 = call i32 @sleep(i32 1), !dbg !101
  br label %20, !dbg !102

20:                                               ; preds = %10, %0
  call void @llvm.dbg.declare(metadata i32* %6, metadata !103, metadata !DIExpression()), !dbg !104
  store i32 1, i32* %6, align 4, !dbg !104
  br label %21, !dbg !105

21:                                               ; preds = %39, %20
  %22 = load i32, i32* %6, align 4, !dbg !106
  %23 = icmp eq i32 %22, 1, !dbg !107
  br i1 %23, label %24, label %49, !dbg !105

24:                                               ; preds = %21
  %25 = load i8*, i8** @_handle_request_get_a.ssocket, align 8, !dbg !108
  %26 = bitcast %struct._request_get_a_datatype* %3 to i8*, !dbg !110
  call void @xdc_blocking_recv(i8* %25, i8* %26, %struct._tag* %1), !dbg !111
  call void @llvm.dbg.declare(metadata i32* %7, metadata !112, metadata !DIExpression()), !dbg !113
  %27 = getelementptr inbounds %struct._request_get_a_datatype, %struct._request_get_a_datatype* %3, i32 0, i32 1, !dbg !114
  %28 = getelementptr inbounds %struct._trailer_datatype, %struct._trailer_datatype* %27, i32 0, i32 0, !dbg !115
  %29 = load i32, i32* %28, align 1, !dbg !115
  store i32 %29, i32* %7, align 4, !dbg !113
  %30 = load i32, i32* %7, align 4, !dbg !116
  %31 = load i32, i32* @_handle_request_get_a.res_counter, align 4, !dbg !118
  %32 = icmp sgt i32 %30, %31, !dbg !119
  br i1 %32, label %33, label %39, !dbg !120

33:                                               ; preds = %24
  store i32 0, i32* %6, align 4, !dbg !121
  %34 = load i32, i32* %7, align 4, !dbg !123
  store i32 %34, i32* @_handle_request_get_a.res_counter, align 4, !dbg !124
  %35 = call double @get_a(), !dbg !125
  store double %35, double* @_handle_request_get_a.last_processed_result, align 8, !dbg !126
  %36 = load double, double* @_handle_request_get_a.last_processed_result, align 8, !dbg !127
  %37 = getelementptr inbounds %struct._response_get_a_datatype, %struct._response_get_a_datatype* %4, i32 0, i32 0, !dbg !128
  store double %36, double* %37, align 1, !dbg !129
  %38 = load i32, i32* %6, align 4, !dbg !130
  store i32 %38, i32* @_handle_request_get_a.last_processed_error, align 4, !dbg !131
  br label %39, !dbg !132

39:                                               ; preds = %33, %24
  %40 = load i32, i32* @_handle_request_get_a.res_counter, align 4, !dbg !133
  %41 = shl i32 %40, 2, !dbg !134
  %42 = load i32, i32* @_handle_request_get_a.last_processed_error, align 4, !dbg !135
  %43 = shl i32 %42, 1, !dbg !136
  %44 = or i32 %41, %43, !dbg !137
  %45 = getelementptr inbounds %struct._response_get_a_datatype, %struct._response_get_a_datatype* %4, i32 0, i32 1, !dbg !138
  %46 = getelementptr inbounds %struct._trailer_datatype, %struct._trailer_datatype* %45, i32 0, i32 0, !dbg !139
  store i32 %44, i32* %46, align 1, !dbg !140
  %47 = load i8*, i8** @_handle_request_get_a.psocket, align 8, !dbg !141
  %48 = bitcast %struct._response_get_a_datatype* %4 to i8*, !dbg !142
  call void @xdc_asyn_send(i8* %47, i8* %48, %struct._tag* %2), !dbg !143
  br label %21, !dbg !105, !llvm.loop !144

49:                                               ; preds = %21
  ret void, !dbg !146
}

declare dso_local void @tag_write(%struct._tag*, i32, i32, i32) #2

declare dso_local i8* @xdc_pub_socket() #2

declare dso_local i8* @xdc_sub_socket(i64, i32) #2

; Function Attrs: argmemonly nounwind willreturn
declare void @llvm.memcpy.p0i8.p0i8.i64(i8* noalias nocapture writeonly, i8* noalias nocapture readonly, i64, i1 immarg) #3

declare dso_local i32 @sleep(i32) #2

declare dso_local void @xdc_blocking_recv(i8*, i8*, %struct._tag*) #2

declare dso_local double @get_a() #2

declare dso_local void @xdc_asyn_send(i8*, i8*, %struct._tag*) #2

; Function Attrs: noinline nounwind optnone uwtable
define dso_local i8* @_wrapper_request_get_a(i8* %0) #0 !dbg !147 {
  %2 = alloca i8*, align 8
  store i8* %0, i8** %2, align 8
  call void @llvm.dbg.declare(metadata i8** %2, metadata !150, metadata !DIExpression()), !dbg !151
  br label %3, !dbg !151

3:                                                ; preds = %1, %3
  call void @_handle_request_get_a(), !dbg !152
  br label %3, !dbg !151, !llvm.loop !154
}

; Function Attrs: noinline nounwind optnone uwtable
define dso_local i32 @_slave_rpc_loop() #0 !dbg !155 {
  %1 = alloca [1 x i64], align 8
  %2 = alloca i32, align 4
  call void @_hal_init(i8* getelementptr inbounds ([26 x i8], [26 x i8]* @.str.2, i64 0, i64 0), i8* getelementptr inbounds ([26 x i8], [26 x i8]* @.str.3, i64 0, i64 0)), !dbg !158
  call void @llvm.dbg.declare(metadata [1 x i64]* %1, metadata !159, metadata !DIExpression()), !dbg !166
  %3 = getelementptr inbounds [1 x i64], [1 x i64]* %1, i64 0, i64 0, !dbg !167
  %4 = call i32 @pthread_create(i64* %3, %union.pthread_attr_t* null, i8* (i8*)* @_wrapper_request_get_a, i8* null) #5, !dbg !168
  call void @llvm.dbg.declare(metadata i32* %2, metadata !169, metadata !DIExpression()), !dbg !171
  store i32 0, i32* %2, align 4, !dbg !171
  br label %5, !dbg !172

5:                                                ; preds = %14, %0
  %6 = load i32, i32* %2, align 4, !dbg !173
  %7 = icmp slt i32 %6, 1, !dbg !175
  br i1 %7, label %8, label %17, !dbg !176

8:                                                ; preds = %5
  %9 = load i32, i32* %2, align 4, !dbg !177
  %10 = sext i32 %9 to i64, !dbg !178
  %11 = getelementptr inbounds [1 x i64], [1 x i64]* %1, i64 0, i64 %10, !dbg !178
  %12 = load i64, i64* %11, align 8, !dbg !178
  %13 = call i32 @pthread_join(i64 %12, i8** null), !dbg !179
  br label %14, !dbg !179

14:                                               ; preds = %8
  %15 = load i32, i32* %2, align 4, !dbg !180
  %16 = add nsw i32 %15, 1, !dbg !180
  store i32 %16, i32* %2, align 4, !dbg !180
  br label %5, !dbg !181, !llvm.loop !182

17:                                               ; preds = %5
  ret i32 0, !dbg !184
}

; Function Attrs: nounwind
declare !callback !185 dso_local i32 @pthread_create(i64*, %union.pthread_attr_t*, i8* (i8*)*, i8*) #4

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
!2 = distinct !DISubprogram(name: "_handle_request_get_a", scope: !3, file: !3, line: 18, type: !4, scopeLine: 18, spFlags: DISPFlagDefinition, unit: !6, retainedNodes: !8)
!3 = !DIFile(filename: "partitioned/multithreaded/orange/orange_rpc.c", directory: "/workspaces/build/apps/examples/example1")
!4 = !DISubroutineType(types: !5)
!5 = !{null}
!6 = distinct !DICompileUnit(language: DW_LANG_C99, file: !7, producer: "clang version 10.0.0-4ubuntu1 ", isOptimized: false, runtimeVersion: 0, emissionKind: FullDebug, enums: !8, retainedTypes: !9, globals: !13, splitDebugInlining: false, nameTableKind: None)
!7 = !DIFile(filename: "/workspaces/build/apps/examples/example1/partitioned/multithreaded/orange/orange_rpc.c", directory: "/workspaces/build/apps/examples/example1")
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
!63 = !DILocalVariable(name: "request_get_a", scope: !2, file: !3, line: 45, type: !64)
!64 = !DIDerivedType(tag: DW_TAG_typedef, name: "request_get_a_datatype", file: !65, line: 75, baseType: !66)
!65 = !DIFile(filename: "partitioned/multithreaded/autogen/codec.h", directory: "/workspaces/build/apps/examples/example1")
!66 = distinct !DICompositeType(tag: DW_TAG_structure_type, name: "_request_get_a_datatype", file: !65, line: 72, size: 160, elements: !67)
!67 = !{!68, !72}
!68 = !DIDerivedType(tag: DW_TAG_member, name: "dummy", scope: !66, file: !65, line: 73, baseType: !69, size: 32)
!69 = !DIDerivedType(tag: DW_TAG_typedef, name: "int32_t", file: !70, line: 26, baseType: !71)
!70 = !DIFile(filename: "/usr/include/x86_64-linux-gnu/bits/stdint-intn.h", directory: "")
!71 = !DIDerivedType(tag: DW_TAG_typedef, name: "__int32_t", file: !54, line: 41, baseType: !19)
!72 = !DIDerivedType(tag: DW_TAG_member, name: "trailer", scope: !66, file: !65, line: 74, baseType: !73, size: 128, offset: 32)
!73 = !DIDerivedType(tag: DW_TAG_typedef, name: "trailer_datatype", file: !65, line: 28, baseType: !74)
!74 = distinct !DICompositeType(tag: DW_TAG_structure_type, name: "_trailer_datatype", file: !65, line: 22, size: 128, elements: !75)
!75 = !{!76, !77, !78, !79, !83}
!76 = !DIDerivedType(tag: DW_TAG_member, name: "seq", scope: !74, file: !65, line: 23, baseType: !51, size: 32)
!77 = !DIDerivedType(tag: DW_TAG_member, name: "rqr", scope: !74, file: !65, line: 24, baseType: !51, size: 32, offset: 32)
!78 = !DIDerivedType(tag: DW_TAG_member, name: "oid", scope: !74, file: !65, line: 25, baseType: !51, size: 32, offset: 64)
!79 = !DIDerivedType(tag: DW_TAG_member, name: "mid", scope: !74, file: !65, line: 26, baseType: !80, size: 16, offset: 96)
!80 = !DIDerivedType(tag: DW_TAG_typedef, name: "uint16_t", file: !52, line: 25, baseType: !81)
!81 = !DIDerivedType(tag: DW_TAG_typedef, name: "__uint16_t", file: !54, line: 40, baseType: !82)
!82 = !DIBasicType(name: "unsigned short", size: 16, encoding: DW_ATE_unsigned)
!83 = !DIDerivedType(tag: DW_TAG_member, name: "crc", scope: !74, file: !65, line: 27, baseType: !80, size: 16, offset: 112)
!84 = !DILocation(line: 45, column: 28, scope: !2)
!85 = !DILocalVariable(name: "response_get_a", scope: !2, file: !3, line: 48, type: !86)
!86 = !DIDerivedType(tag: DW_TAG_typedef, name: "response_get_a_datatype", file: !65, line: 89, baseType: !87)
!87 = distinct !DICompositeType(tag: DW_TAG_structure_type, name: "_response_get_a_datatype", file: !65, line: 86, size: 192, elements: !88)
!88 = !{!89, !90}
!89 = !DIDerivedType(tag: DW_TAG_member, name: "ret", scope: !87, file: !65, line: 87, baseType: !16, size: 64)
!90 = !DIDerivedType(tag: DW_TAG_member, name: "trailer", scope: !87, file: !65, line: 88, baseType: !73, size: 128, offset: 64)
!91 = !DILocation(line: 48, column: 29, scope: !2)
!92 = !DILocation(line: 62, column: 10, scope: !93)
!93 = distinct !DILexicalBlock(scope: !2, file: !3, line: 62, column: 9)
!94 = !DILocation(line: 62, column: 9, scope: !2)
!95 = !DILocation(line: 63, column: 16, scope: !96)
!96 = distinct !DILexicalBlock(scope: !93, file: !3, line: 62, column: 18)
!97 = !DILocation(line: 64, column: 19, scope: !96)
!98 = !DILocation(line: 64, column: 17, scope: !96)
!99 = !DILocation(line: 65, column: 19, scope: !96)
!100 = !DILocation(line: 65, column: 17, scope: !96)
!101 = !DILocation(line: 66, column: 9, scope: !96)
!102 = !DILocation(line: 67, column: 5, scope: !96)
!103 = !DILocalVariable(name: "proc_error", scope: !2, file: !3, line: 92, type: !19)
!104 = !DILocation(line: 92, column: 9, scope: !2)
!105 = !DILocation(line: 93, column: 5, scope: !2)
!106 = !DILocation(line: 93, column: 12, scope: !2)
!107 = !DILocation(line: 93, column: 23, scope: !2)
!108 = !DILocation(line: 94, column: 27, scope: !109)
!109 = distinct !DILexicalBlock(scope: !2, file: !3, line: 93, column: 29)
!110 = !DILocation(line: 94, column: 36, scope: !109)
!111 = !DILocation(line: 94, column: 9, scope: !109)
!112 = !DILocalVariable(name: "req_counter", scope: !109, file: !3, line: 95, type: !19)
!113 = !DILocation(line: 95, column: 13, scope: !109)
!114 = !DILocation(line: 95, column: 41, scope: !109)
!115 = !DILocation(line: 95, column: 49, scope: !109)
!116 = !DILocation(line: 96, column: 12, scope: !117)
!117 = distinct !DILexicalBlock(scope: !109, file: !3, line: 96, column: 12)
!118 = !DILocation(line: 96, column: 26, scope: !117)
!119 = !DILocation(line: 96, column: 24, scope: !117)
!120 = !DILocation(line: 96, column: 12, scope: !109)
!121 = !DILocation(line: 97, column: 24, scope: !122)
!122 = distinct !DILexicalBlock(scope: !117, file: !3, line: 96, column: 38)
!123 = !DILocation(line: 98, column: 27, scope: !122)
!124 = !DILocation(line: 98, column: 25, scope: !122)
!125 = !DILocation(line: 99, column: 37, scope: !122)
!126 = !DILocation(line: 99, column: 35, scope: !122)
!127 = !DILocation(line: 100, column: 34, scope: !122)
!128 = !DILocation(line: 100, column: 28, scope: !122)
!129 = !DILocation(line: 100, column: 32, scope: !122)
!130 = !DILocation(line: 101, column: 36, scope: !122)
!131 = !DILocation(line: 101, column: 34, scope: !122)
!132 = !DILocation(line: 102, column: 9, scope: !122)
!133 = !DILocation(line: 104, column: 38, scope: !109)
!134 = !DILocation(line: 104, column: 50, scope: !109)
!135 = !DILocation(line: 104, column: 57, scope: !109)
!136 = !DILocation(line: 104, column: 78, scope: !109)
!137 = !DILocation(line: 104, column: 55, scope: !109)
!138 = !DILocation(line: 104, column: 24, scope: !109)
!139 = !DILocation(line: 104, column: 32, scope: !109)
!140 = !DILocation(line: 104, column: 36, scope: !109)
!141 = !DILocation(line: 105, column: 23, scope: !109)
!142 = !DILocation(line: 105, column: 32, scope: !109)
!143 = !DILocation(line: 105, column: 9, scope: !109)
!144 = distinct !{!144, !105, !145}
!145 = !DILocation(line: 109, column: 5, scope: !2)
!146 = !DILocation(line: 111, column: 1, scope: !2)
!147 = distinct !DISubprogram(name: "_wrapper_request_get_a", scope: !3, file: !3, line: 113, type: !148, scopeLine: 113, flags: DIFlagPrototyped, spFlags: DISPFlagDefinition, unit: !6, retainedNodes: !8)
!148 = !DISubroutineType(types: !149)
!149 = !{!12, !12}
!150 = !DILocalVariable(name: "tag", arg: 1, scope: !147, file: !3, line: 113, type: !12)
!151 = !DILocation(line: 113, column: 1, scope: !147)
!152 = !DILocation(line: 113, column: 1, scope: !153)
!153 = distinct !DILexicalBlock(scope: !147, file: !3, line: 113, column: 1)
!154 = distinct !{!154, !151, !151}
!155 = distinct !DISubprogram(name: "_slave_rpc_loop", scope: !3, file: !3, line: 116, type: !156, scopeLine: 116, spFlags: DISPFlagDefinition, unit: !6, retainedNodes: !8)
!156 = !DISubroutineType(types: !157)
!157 = !{!19}
!158 = !DILocation(line: 117, column: 5, scope: !155)
!159 = !DILocalVariable(name: "tid", scope: !155, file: !3, line: 118, type: !160)
!160 = !DICompositeType(tag: DW_TAG_array_type, baseType: !161, size: 64, elements: !164)
!161 = !DIDerivedType(tag: DW_TAG_typedef, name: "pthread_t", file: !162, line: 27, baseType: !163)
!162 = !DIFile(filename: "/usr/include/x86_64-linux-gnu/bits/pthreadtypes.h", directory: "")
!163 = !DIBasicType(name: "long unsigned int", size: 64, encoding: DW_ATE_unsigned)
!164 = !{!165}
!165 = !DISubrange(count: 1)
!166 = !DILocation(line: 118, column: 15, scope: !155)
!167 = !DILocation(line: 119, column: 21, scope: !155)
!168 = !DILocation(line: 119, column: 5, scope: !155)
!169 = !DILocalVariable(name: "i", scope: !170, file: !3, line: 120, type: !19)
!170 = distinct !DILexicalBlock(scope: !155, file: !3, line: 120, column: 5)
!171 = !DILocation(line: 120, column: 14, scope: !170)
!172 = !DILocation(line: 120, column: 10, scope: !170)
!173 = !DILocation(line: 120, column: 21, scope: !174)
!174 = distinct !DILexicalBlock(scope: !170, file: !3, line: 120, column: 5)
!175 = !DILocation(line: 120, column: 23, scope: !174)
!176 = !DILocation(line: 120, column: 5, scope: !170)
!177 = !DILocation(line: 120, column: 55, scope: !174)
!178 = !DILocation(line: 120, column: 51, scope: !174)
!179 = !DILocation(line: 120, column: 38, scope: !174)
!180 = !DILocation(line: 120, column: 34, scope: !174)
!181 = !DILocation(line: 120, column: 5, scope: !174)
!182 = distinct !{!182, !176, !183}
!183 = !DILocation(line: 120, column: 63, scope: !170)
!184 = !DILocation(line: 121, column: 5, scope: !155)
!185 = !{!186}
!186 = !{i64 2, i64 3, i1 false}
