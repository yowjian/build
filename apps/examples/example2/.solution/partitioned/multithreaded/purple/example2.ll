; ModuleID = '/workspaces/build/apps/examples/example2/partitioned/multithreaded/purple/example2.c'
source_filename = "/workspaces/build/apps/examples/example2/partitioned/multithreaded/purple/example2.c"
target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-pc-linux-gnu"

@calc_ewma.c = internal global double 0.000000e+00, align 8, !dbg !0
@get_b.b = internal global double 1.000000e+00, align 8, !dbg !11
@.str = private unnamed_addr constant [7 x i8] c"PURPLE\00", section "llvm.metadata"
@.str.1 = private unnamed_addr constant [85 x i8] c"/workspaces/build/apps/examples/example2/partitioned/multithreaded/purple/example2.c\00", section "llvm.metadata"
@.str.2 = private unnamed_addr constant [17 x i8] c"PURPLE_SHAREABLE\00", section "llvm.metadata"
@.str.3 = private unnamed_addr constant [19 x i8] c"XDLINKAGE_GET_EWMA\00", section "llvm.metadata"
@llvm.global.annotations = appending global [2 x { i8*, i8*, i8*, i32 }] [{ i8*, i8*, i8*, i32 } { i8* bitcast (double* @get_b.b to i8*), i8* getelementptr inbounds ([7 x i8], [7 x i8]* @.str, i32 0, i32 0), i8* getelementptr inbounds ([85 x i8], [85 x i8]* @.str.1, i32 0, i32 0), i32 57 }, { i8*, i8*, i8*, i32 } { i8* bitcast (double (double)* @get_ewma to i8*), i8* getelementptr inbounds ([19 x i8], [19 x i8]* @.str.3, i32 0, i32 0), i8* getelementptr inbounds ([85 x i8], [85 x i8]* @.str.1, i32 0, i32 0), i32 66 }], section "llvm.metadata"

; Function Attrs: noinline nounwind optnone uwtable
define dso_local double @calc_ewma(double %0, double %1) #0 !dbg !2 {
  %3 = alloca double, align 8
  %4 = alloca double, align 8
  %5 = alloca double, align 8
  store double %0, double* %3, align 8
  call void @llvm.dbg.declare(metadata double* %3, metadata !20, metadata !DIExpression()), !dbg !21
  store double %1, double* %4, align 8
  call void @llvm.dbg.declare(metadata double* %4, metadata !22, metadata !DIExpression()), !dbg !23
  call void @llvm.dbg.declare(metadata double* %5, metadata !24, metadata !DIExpression()), !dbg !26
  store double 2.500000e-01, double* %5, align 8, !dbg !26
  %6 = load double, double* %3, align 8, !dbg !27
  %7 = load double, double* %4, align 8, !dbg !28
  %8 = fadd double %6, %7, !dbg !29
  %9 = fmul double 2.500000e-01, %8, !dbg !30
  %10 = load double, double* @calc_ewma.c, align 8, !dbg !31
  %11 = fmul double 7.500000e-01, %10, !dbg !32
  %12 = fadd double %9, %11, !dbg !33
  store double %12, double* @calc_ewma.c, align 8, !dbg !34
  %13 = load double, double* @calc_ewma.c, align 8, !dbg !35
  ret double %13, !dbg !36
}

; Function Attrs: nounwind readnone speculatable willreturn
declare void @llvm.dbg.declare(metadata, metadata, metadata) #1

; Function Attrs: noinline nounwind optnone uwtable
define dso_local double @get_b() #0 !dbg !13 {
  %1 = load double, double* @get_b.b, align 8, !dbg !37
  %2 = load double, double* @get_b.b, align 8, !dbg !38
  %3 = fadd double %2, %1, !dbg !38
  store double %3, double* @get_b.b, align 8, !dbg !38
  %4 = load double, double* @get_b.b, align 8, !dbg !39
  ret double %4, !dbg !40
}

; Function Attrs: noinline nounwind optnone uwtable
define dso_local double @get_ewma(double %0) #0 !dbg !41 {
  %2 = alloca double, align 8
  %3 = alloca double, align 8
  %4 = alloca double, align 8
  %5 = alloca double, align 8
  store double %0, double* %2, align 8
  call void @llvm.dbg.declare(metadata double* %2, metadata !44, metadata !DIExpression()), !dbg !45
  call void @llvm.dbg.declare(metadata double* %3, metadata !46, metadata !DIExpression()), !dbg !47
  %6 = bitcast double* %3 to i8*, !dbg !48
  call void @llvm.var.annotation(i8* %6, i8* getelementptr inbounds ([17 x i8], [17 x i8]* @.str.2, i32 0, i32 0), i8* getelementptr inbounds ([85 x i8], [85 x i8]* @.str.1, i32 0, i32 0), i32 71), !dbg !48
  call void @llvm.dbg.declare(metadata double* %4, metadata !49, metadata !DIExpression()), !dbg !50
  %7 = bitcast double* %4 to i8*, !dbg !48
  call void @llvm.var.annotation(i8* %7, i8* getelementptr inbounds ([17 x i8], [17 x i8]* @.str.2, i32 0, i32 0), i8* getelementptr inbounds ([85 x i8], [85 x i8]* @.str.1, i32 0, i32 0), i32 71), !dbg !48
  call void @llvm.dbg.declare(metadata double* %5, metadata !51, metadata !DIExpression()), !dbg !52
  %8 = bitcast double* %5 to i8*, !dbg !48
  call void @llvm.var.annotation(i8* %8, i8* getelementptr inbounds ([17 x i8], [17 x i8]* @.str.2, i32 0, i32 0), i8* getelementptr inbounds ([85 x i8], [85 x i8]* @.str.1, i32 0, i32 0), i32 71), !dbg !48
  %9 = load double, double* %2, align 8, !dbg !53
  store double %9, double* %3, align 8, !dbg !54
  %10 = call double @get_b(), !dbg !55
  store double %10, double* %4, align 8, !dbg !56
  %11 = load double, double* %3, align 8, !dbg !57
  %12 = load double, double* %4, align 8, !dbg !58
  %13 = call double @calc_ewma(double %11, double %12), !dbg !59
  store double %13, double* %5, align 8, !dbg !60
  %14 = load double, double* %5, align 8, !dbg !61
  ret double %14, !dbg !62
}

; Function Attrs: nounwind willreturn
declare void @llvm.var.annotation(i8*, i8*, i8*, i32) #2

; Function Attrs: noinline nounwind optnone uwtable
define dso_local i32 @main(i32 %0, i8** %1) #0 !dbg !63 {
  %3 = alloca i32, align 4
  %4 = alloca i32, align 4
  %5 = alloca i8**, align 8
  store i32 0, i32* %3, align 4
  store i32 %0, i32* %4, align 4
  call void @llvm.dbg.declare(metadata i32* %4, metadata !70, metadata !DIExpression()), !dbg !71
  store i8** %1, i8*** %5, align 8
  call void @llvm.dbg.declare(metadata i8*** %5, metadata !72, metadata !DIExpression()), !dbg !73
  %6 = call i32 (...) @_slave_rpc_loop(), !dbg !74
  ret i32 %6, !dbg !75
}

declare dso_local i32 @_slave_rpc_loop(...) #3

attributes #0 = { noinline nounwind optnone uwtable "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "frame-pointer"="all" "less-precise-fpmad"="false" "min-legal-vector-width"="0" "no-infs-fp-math"="false" "no-jump-tables"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { nounwind readnone speculatable willreturn }
attributes #2 = { nounwind willreturn }
attributes #3 = { "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "frame-pointer"="all" "less-precise-fpmad"="false" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }

!llvm.dbg.cu = !{!7}
!llvm.module.flags = !{!16, !17, !18}
!llvm.ident = !{!19}

!0 = !DIGlobalVariableExpression(var: !1, expr: !DIExpression())
!1 = distinct !DIGlobalVariable(name: "c", scope: !2, file: !3, line: 48, type: !6, isLocal: true, isDefinition: true)
!2 = distinct !DISubprogram(name: "calc_ewma", scope: !3, file: !3, line: 46, type: !4, scopeLine: 46, flags: DIFlagPrototyped, spFlags: DISPFlagDefinition, unit: !7, retainedNodes: !9)
!3 = !DIFile(filename: "partitioned/multithreaded/purple/example2.c", directory: "/workspaces/build/apps/examples/example2")
!4 = !DISubroutineType(types: !5)
!5 = !{!6, !6, !6}
!6 = !DIBasicType(name: "double", size: 64, encoding: DW_ATE_float)
!7 = distinct !DICompileUnit(language: DW_LANG_C99, file: !8, producer: "clang version 10.0.0-4ubuntu1 ", isOptimized: false, runtimeVersion: 0, emissionKind: FullDebug, enums: !9, globals: !10, splitDebugInlining: false, nameTableKind: None)
!8 = !DIFile(filename: "/workspaces/build/apps/examples/example2/partitioned/multithreaded/purple/example2.c", directory: "/workspaces/build/apps/examples/example2")
!9 = !{}
!10 = !{!0, !11}
!11 = !DIGlobalVariableExpression(var: !12, expr: !DIExpression())
!12 = distinct !DIGlobalVariable(name: "b", scope: !13, file: !3, line: 57, type: !6, isLocal: true, isDefinition: true)
!13 = distinct !DISubprogram(name: "get_b", scope: !3, file: !3, line: 54, type: !14, scopeLine: 54, spFlags: DISPFlagDefinition, unit: !7, retainedNodes: !9)
!14 = !DISubroutineType(types: !15)
!15 = !{!6}
!16 = !{i32 7, !"Dwarf Version", i32 4}
!17 = !{i32 2, !"Debug Info Version", i32 3}
!18 = !{i32 1, !"wchar_size", i32 4}
!19 = !{!"clang version 10.0.0-4ubuntu1 "}
!20 = !DILocalVariable(name: "a", arg: 1, scope: !2, file: !3, line: 46, type: !6)
!21 = !DILocation(line: 46, column: 25, scope: !2)
!22 = !DILocalVariable(name: "b", arg: 2, scope: !2, file: !3, line: 46, type: !6)
!23 = !DILocation(line: 46, column: 35, scope: !2)
!24 = !DILocalVariable(name: "alpha", scope: !2, file: !3, line: 47, type: !25)
!25 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !6)
!26 = !DILocation(line: 47, column: 17, scope: !2)
!27 = !DILocation(line: 49, column: 16, scope: !2)
!28 = !DILocation(line: 49, column: 20, scope: !2)
!29 = !DILocation(line: 49, column: 18, scope: !2)
!30 = !DILocation(line: 49, column: 13, scope: !2)
!31 = !DILocation(line: 49, column: 39, scope: !2)
!32 = !DILocation(line: 49, column: 37, scope: !2)
!33 = !DILocation(line: 49, column: 23, scope: !2)
!34 = !DILocation(line: 49, column: 5, scope: !2)
!35 = !DILocation(line: 50, column: 10, scope: !2)
!36 = !DILocation(line: 50, column: 3, scope: !2)
!37 = !DILocation(line: 60, column: 8, scope: !13)
!38 = !DILocation(line: 60, column: 5, scope: !13)
!39 = !DILocation(line: 61, column: 10, scope: !13)
!40 = !DILocation(line: 61, column: 3, scope: !13)
!41 = distinct !DISubprogram(name: "get_ewma", scope: !3, file: !3, line: 66, type: !42, scopeLine: 66, flags: DIFlagPrototyped, spFlags: DISPFlagDefinition, unit: !7, retainedNodes: !9)
!42 = !DISubroutineType(types: !43)
!43 = !{!6, !6}
!44 = !DILocalVariable(name: "x", arg: 1, scope: !41, file: !3, line: 66, type: !6)
!45 = !DILocation(line: 66, column: 24, scope: !41)
!46 = !DILocalVariable(name: "x1", scope: !41, file: !3, line: 71, type: !6)
!47 = !DILocation(line: 71, column: 10, scope: !41)
!48 = !DILocation(line: 71, column: 3, scope: !41)
!49 = !DILocalVariable(name: "y1", scope: !41, file: !3, line: 71, type: !6)
!50 = !DILocation(line: 71, column: 14, scope: !41)
!51 = !DILocalVariable(name: "z1", scope: !41, file: !3, line: 71, type: !6)
!52 = !DILocation(line: 71, column: 18, scope: !41)
!53 = !DILocation(line: 74, column: 8, scope: !41)
!54 = !DILocation(line: 74, column: 6, scope: !41)
!55 = !DILocation(line: 75, column: 8, scope: !41)
!56 = !DILocation(line: 75, column: 6, scope: !41)
!57 = !DILocation(line: 76, column: 18, scope: !41)
!58 = !DILocation(line: 76, column: 22, scope: !41)
!59 = !DILocation(line: 76, column: 8, scope: !41)
!60 = !DILocation(line: 76, column: 6, scope: !41)
!61 = !DILocation(line: 77, column: 10, scope: !41)
!62 = !DILocation(line: 77, column: 3, scope: !41)
!63 = distinct !DISubprogram(name: "main", scope: !3, file: !3, line: 81, type: !64, scopeLine: 81, flags: DIFlagPrototyped, spFlags: DISPFlagDefinition, unit: !7, retainedNodes: !9)
!64 = !DISubroutineType(types: !65)
!65 = !{!66, !66, !67}
!66 = !DIBasicType(name: "int", size: 32, encoding: DW_ATE_signed)
!67 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !68, size: 64)
!68 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !69, size: 64)
!69 = !DIBasicType(name: "char", size: 8, encoding: DW_ATE_signed_char)
!70 = !DILocalVariable(name: "argc", arg: 1, scope: !63, file: !3, line: 81, type: !66)
!71 = !DILocation(line: 81, column: 14, scope: !63)
!72 = !DILocalVariable(name: "argv", arg: 2, scope: !63, file: !3, line: 81, type: !67)
!73 = !DILocation(line: 81, column: 26, scope: !63)
!74 = !DILocation(line: 82, column: 10, scope: !63)
!75 = !DILocation(line: 82, column: 3, scope: !63)
