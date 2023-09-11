; ModuleID = 'llvm-link'
source_filename = "llvm-link"
target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-pc-linux-gnu"

@llvm.global.annotations = appending global [4 x { i8*, i8*, i8*, i32 }] [{ i8*, i8*, i8*, i32 } { i8* bitcast (double* @get_a.a to i8*), i8* getelementptr inbounds ([7 x i8], [7 x i8]* @.str, i32 0, i32 0), i8* getelementptr inbounds ([36 x i8], [36 x i8]* @.str.1, i32 0, i32 0), i32 49 }, { i8*, i8*, i8*, i32 } { i8* bitcast (i32 ()* @ewma_main to i8*), i8* getelementptr inbounds ([10 x i8], [10 x i8]* @.str.3, i32 0, i32 0), i8* getelementptr inbounds ([36 x i8], [36 x i8]* @.str.1, i32 0, i32 0), i32 60 }, { i8*, i8*, i8*, i32 } { i8* bitcast (double* @get_b.b to i8*), i8* getelementptr inbounds ([7 x i8], [7 x i8]* @.str.4, i32 0, i32 0), i8* getelementptr inbounds ([36 x i8], [36 x i8]* @.str.1.5, i32 0, i32 0), i32 56 }, { i8*, i8*, i8*, i32 } { i8* bitcast (double (double)* @get_ewma to i8*), i8* getelementptr inbounds ([19 x i8], [19 x i8]* @.str.3.8, i32 0, i32 0), i8* getelementptr inbounds ([36 x i8], [36 x i8]* @.str.1.5, i32 0, i32 0), i32 65 }], section "llvm.metadata"
@get_a.a = internal global double 0.000000e+00, align 8, !dbg !0
@.str = private unnamed_addr constant [7 x i8] c"ORANGE\00", section "llvm.metadata"
@.str.1 = private unnamed_addr constant [36 x i8] c"./divvied-working/orange/example2.c\00", section "llvm.metadata"
@.str.3 = private unnamed_addr constant [10 x i8] c"EWMA_MAIN\00", section "llvm.metadata"
@.str.2 = private unnamed_addr constant [4 x i8] c"%f\0A\00", align 1
@get_b.b = internal global double 1.000000e+00, align 8, !dbg !11
@.str.4 = private unnamed_addr constant [7 x i8] c"PURPLE\00", section "llvm.metadata"
@.str.1.5 = private unnamed_addr constant [36 x i8] c"./divvied-working/purple/example2.c\00", section "llvm.metadata"
@.str.3.8 = private unnamed_addr constant [19 x i8] c"XDLINKAGE_GET_EWMA\00", section "llvm.metadata"
@.str.2.9 = private unnamed_addr constant [17 x i8] c"PURPLE_SHAREABLE\00", section "llvm.metadata"
@calc_ewma.c = internal global double 0.000000e+00, align 8, !dbg !18

; Function Attrs: noinline nounwind optnone uwtable
define dso_local i32 @ewma_main() #0 !dbg !27 {
  %1 = alloca double, align 8
  %2 = alloca double, align 8
  %3 = alloca double, align 8
  %4 = alloca i32, align 4
  call void @llvm.dbg.declare(metadata double* %1, metadata !31, metadata !DIExpression()), !dbg !32
  call void @llvm.dbg.declare(metadata double* %2, metadata !33, metadata !DIExpression()), !dbg !34
  call void @llvm.dbg.declare(metadata double* %3, metadata !35, metadata !DIExpression()), !dbg !36
  call void @llvm.dbg.declare(metadata i32* %4, metadata !37, metadata !DIExpression()), !dbg !39
  store i32 0, i32* %4, align 4, !dbg !39
  br label %5, !dbg !40

5:                                                ; preds = %16, %0
  %6 = load i32, i32* %4, align 4, !dbg !41
  %7 = icmp slt i32 %6, 10, !dbg !43
  br i1 %7, label %8, label %19, !dbg !44

8:                                                ; preds = %5
  %9 = call double @get_a() #4, !dbg !45
  store double %9, double* %1, align 8, !dbg !47
  %10 = load double, double* %1, align 8, !dbg !48
  store double %10, double* %2, align 8, !dbg !49
  %11 = load double, double* %2, align 8, !dbg !50
  %12 = call i32 (double, ...) bitcast (double (double)* @get_ewma to i32 (double, ...)*)(double %11) #4, !dbg !51
  %13 = sitofp i32 %12 to double, !dbg !51
  store double %13, double* %3, align 8, !dbg !52
  %14 = load double, double* %3, align 8, !dbg !53
  %15 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str.2, i64 0, i64 0), double %14) #4, !dbg !54
  br label %16, !dbg !55

16:                                               ; preds = %8
  %17 = load i32, i32* %4, align 4, !dbg !56
  %18 = add nsw i32 %17, 1, !dbg !56
  store i32 %18, i32* %4, align 4, !dbg !56
  br label %5, !dbg !57, !llvm.loop !58

19:                                               ; preds = %5
  ret i32 0, !dbg !60
}

; Function Attrs: nounwind readnone speculatable willreturn
declare void @llvm.dbg.declare(metadata, metadata, metadata) #1

; Function Attrs: noinline nounwind optnone uwtable
define dso_local double @get_a() #0 !dbg !2 {
  %1 = load double, double* @get_a.a, align 8, !dbg !61
  %2 = fadd double %1, 1.000000e+00, !dbg !61
  store double %2, double* @get_a.a, align 8, !dbg !61
  %3 = load double, double* @get_a.a, align 8, !dbg !62
  ret double %3, !dbg !63
}

declare dso_local i32 @printf(i8*, ...) #2

; Function Attrs: noinline nounwind optnone uwtable
define dso_local i32 @main() #0 !dbg !64 {
  %1 = alloca i32, align 4
  store i32 0, i32* %1, align 4
  %2 = call i32 @ewma_main() #4, !dbg !65
  ret i32 %2, !dbg !66
}

; Function Attrs: noinline nounwind optnone uwtable
define dso_local double @get_ewma(double %0) #0 !dbg !67 {
  %2 = alloca double, align 8
  %3 = alloca double, align 8
  %4 = alloca double, align 8
  %5 = alloca double, align 8
  store double %0, double* %2, align 8
  call void @llvm.dbg.declare(metadata double* %2, metadata !70, metadata !DIExpression()), !dbg !71
  call void @llvm.dbg.declare(metadata double* %3, metadata !72, metadata !DIExpression()), !dbg !73
  %6 = bitcast double* %3 to i8*, !dbg !74
  call void @llvm.var.annotation(i8* %6, i8* getelementptr inbounds ([17 x i8], [17 x i8]* @.str.2.9, i32 0, i32 0), i8* getelementptr inbounds ([36 x i8], [36 x i8]* @.str.1.5, i32 0, i32 0), i32 70), !dbg !74
  call void @llvm.dbg.declare(metadata double* %4, metadata !75, metadata !DIExpression()), !dbg !76
  %7 = bitcast double* %4 to i8*, !dbg !74
  call void @llvm.var.annotation(i8* %7, i8* getelementptr inbounds ([17 x i8], [17 x i8]* @.str.2.9, i32 0, i32 0), i8* getelementptr inbounds ([36 x i8], [36 x i8]* @.str.1.5, i32 0, i32 0), i32 70), !dbg !74
  call void @llvm.dbg.declare(metadata double* %5, metadata !77, metadata !DIExpression()), !dbg !78
  %8 = bitcast double* %5 to i8*, !dbg !74
  call void @llvm.var.annotation(i8* %8, i8* getelementptr inbounds ([17 x i8], [17 x i8]* @.str.2.9, i32 0, i32 0), i8* getelementptr inbounds ([36 x i8], [36 x i8]* @.str.1.5, i32 0, i32 0), i32 70), !dbg !74
  %9 = load double, double* %2, align 8, !dbg !79
  store double %9, double* %3, align 8, !dbg !80
  %10 = call double @get_b() #4, !dbg !81
  store double %10, double* %4, align 8, !dbg !82
  %11 = load double, double* %3, align 8, !dbg !83
  %12 = load double, double* %4, align 8, !dbg !84
  %13 = call double @calc_ewma(double %11, double %12) #4, !dbg !85
  store double %13, double* %5, align 8, !dbg !86
  %14 = load double, double* %5, align 8, !dbg !87
  ret double %14, !dbg !88
}

; Function Attrs: nounwind willreturn
declare void @llvm.var.annotation(i8*, i8*, i8*, i32) #3

; Function Attrs: noinline nounwind optnone uwtable
define dso_local double @get_b() #0 !dbg !13 {
  %1 = load double, double* @get_b.b, align 8, !dbg !89
  %2 = load double, double* @get_b.b, align 8, !dbg !90
  %3 = fadd double %2, %1, !dbg !90
  store double %3, double* @get_b.b, align 8, !dbg !90
  %4 = load double, double* @get_b.b, align 8, !dbg !91
  ret double %4, !dbg !92
}

; Function Attrs: noinline nounwind optnone uwtable
define dso_local double @calc_ewma(double %0, double %1) #0 !dbg !20 {
  %3 = alloca double, align 8
  %4 = alloca double, align 8
  %5 = alloca double, align 8
  store double %0, double* %3, align 8
  call void @llvm.dbg.declare(metadata double* %3, metadata !93, metadata !DIExpression()), !dbg !94
  store double %1, double* %4, align 8
  call void @llvm.dbg.declare(metadata double* %4, metadata !95, metadata !DIExpression()), !dbg !96
  call void @llvm.dbg.declare(metadata double* %5, metadata !97, metadata !DIExpression()), !dbg !99
  store double 2.500000e-01, double* %5, align 8, !dbg !99
  %6 = load double, double* %3, align 8, !dbg !100
  %7 = load double, double* %4, align 8, !dbg !101
  %8 = fadd double %6, %7, !dbg !102
  %9 = fmul double 2.500000e-01, %8, !dbg !103
  %10 = load double, double* @calc_ewma.c, align 8, !dbg !104
  %11 = fmul double 7.500000e-01, %10, !dbg !105
  %12 = fadd double %9, %11, !dbg !106
  store double %12, double* @calc_ewma.c, align 8, !dbg !107
  %13 = load double, double* @calc_ewma.c, align 8, !dbg !108
  ret double %13, !dbg !109
}

attributes #0 = { noinline nounwind optnone uwtable "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "frame-pointer"="all" "less-precise-fpmad"="false" "min-legal-vector-width"="0" "no-builtins" "no-infs-fp-math"="false" "no-jump-tables"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { nounwind readnone speculatable willreturn }
attributes #2 = { "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "frame-pointer"="all" "less-precise-fpmad"="false" "no-builtins" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #3 = { nounwind willreturn }
attributes #4 = { nobuiltin "no-builtins" }

!llvm.dbg.cu = !{!7, !15}
!llvm.ident = !{!23, !23}
!llvm.module.flags = !{!24, !25, !26}

!0 = !DIGlobalVariableExpression(var: !1, expr: !DIExpression())
!1 = distinct !DIGlobalVariable(name: "a", scope: !2, file: !3, line: 49, type: !6, isLocal: true, isDefinition: true)
!2 = distinct !DISubprogram(name: "get_a", scope: !3, file: !3, line: 46, type: !4, scopeLine: 46, spFlags: DISPFlagDefinition, unit: !7, retainedNodes: !9)
!3 = !DIFile(filename: "./divvied-working/orange/example2.c", directory: "/workspaces/build/apps/examples/example2")
!4 = !DISubroutineType(types: !5)
!5 = !{!6}
!6 = !DIBasicType(name: "double", size: 64, encoding: DW_ATE_float)
!7 = distinct !DICompileUnit(language: DW_LANG_C99, file: !8, producer: "clang version 10.0.0-4ubuntu1 ", isOptimized: false, runtimeVersion: 0, emissionKind: FullDebug, enums: !9, globals: !10, splitDebugInlining: false, nameTableKind: None)
!8 = !DIFile(filename: "divvied-working/orange/example2.c", directory: "/workspaces/build/apps/examples/example2")
!9 = !{}
!10 = !{!0}
!11 = !DIGlobalVariableExpression(var: !12, expr: !DIExpression())
!12 = distinct !DIGlobalVariable(name: "b", scope: !13, file: !14, line: 56, type: !6, isLocal: true, isDefinition: true)
!13 = distinct !DISubprogram(name: "get_b", scope: !14, file: !14, line: 53, type: !4, scopeLine: 53, spFlags: DISPFlagDefinition, unit: !15, retainedNodes: !9)
!14 = !DIFile(filename: "./divvied-working/purple/example2.c", directory: "/workspaces/build/apps/examples/example2")
!15 = distinct !DICompileUnit(language: DW_LANG_C99, file: !16, producer: "clang version 10.0.0-4ubuntu1 ", isOptimized: false, runtimeVersion: 0, emissionKind: FullDebug, enums: !9, globals: !17, splitDebugInlining: false, nameTableKind: None)
!16 = !DIFile(filename: "divvied-working/purple/example2.c", directory: "/workspaces/build/apps/examples/example2")
!17 = !{!18, !11}
!18 = !DIGlobalVariableExpression(var: !19, expr: !DIExpression())
!19 = distinct !DIGlobalVariable(name: "c", scope: !20, file: !14, line: 47, type: !6, isLocal: true, isDefinition: true)
!20 = distinct !DISubprogram(name: "calc_ewma", scope: !14, file: !14, line: 45, type: !21, scopeLine: 45, flags: DIFlagPrototyped, spFlags: DISPFlagDefinition, unit: !15, retainedNodes: !9)
!21 = !DISubroutineType(types: !22)
!22 = !{!6, !6, !6}
!23 = !{!"clang version 10.0.0-4ubuntu1 "}
!24 = !{i32 7, !"Dwarf Version", i32 4}
!25 = !{i32 2, !"Debug Info Version", i32 3}
!26 = !{i32 1, !"wchar_size", i32 4}
!27 = distinct !DISubprogram(name: "ewma_main", scope: !3, file: !3, line: 60, type: !28, scopeLine: 60, spFlags: DISPFlagDefinition, unit: !7, retainedNodes: !9)
!28 = !DISubroutineType(types: !29)
!29 = !{!30}
!30 = !DIBasicType(name: "int", size: 32, encoding: DW_ATE_signed)
!31 = !DILocalVariable(name: "x", scope: !27, file: !3, line: 63, type: !6)
!32 = !DILocation(line: 63, column: 10, scope: !27)
!33 = !DILocalVariable(name: "y", scope: !27, file: !3, line: 64, type: !6)
!34 = !DILocation(line: 64, column: 10, scope: !27)
!35 = !DILocalVariable(name: "ewma", scope: !27, file: !3, line: 65, type: !6)
!36 = !DILocation(line: 65, column: 10, scope: !27)
!37 = !DILocalVariable(name: "i", scope: !38, file: !3, line: 66, type: !30)
!38 = distinct !DILexicalBlock(scope: !27, file: !3, line: 66, column: 3)
!39 = !DILocation(line: 66, column: 12, scope: !38)
!40 = !DILocation(line: 66, column: 8, scope: !38)
!41 = !DILocation(line: 66, column: 17, scope: !42)
!42 = distinct !DILexicalBlock(scope: !38, file: !3, line: 66, column: 3)
!43 = !DILocation(line: 66, column: 19, scope: !42)
!44 = !DILocation(line: 66, column: 3, scope: !38)
!45 = !DILocation(line: 67, column: 9, scope: !46)
!46 = distinct !DILexicalBlock(scope: !42, file: !3, line: 66, column: 30)
!47 = !DILocation(line: 67, column: 7, scope: !46)
!48 = !DILocation(line: 68, column: 9, scope: !46)
!49 = !DILocation(line: 68, column: 7, scope: !46)
!50 = !DILocation(line: 69, column: 21, scope: !46)
!51 = !DILocation(line: 69, column: 12, scope: !46)
!52 = !DILocation(line: 69, column: 10, scope: !46)
!53 = !DILocation(line: 70, column: 20, scope: !46)
!54 = !DILocation(line: 70, column: 5, scope: !46)
!55 = !DILocation(line: 71, column: 3, scope: !46)
!56 = !DILocation(line: 66, column: 26, scope: !42)
!57 = !DILocation(line: 66, column: 3, scope: !42)
!58 = distinct !{!58, !44, !59}
!59 = !DILocation(line: 71, column: 3, scope: !38)
!60 = !DILocation(line: 72, column: 3, scope: !27)
!61 = !DILocation(line: 52, column: 5, scope: !2)
!62 = !DILocation(line: 53, column: 10, scope: !2)
!63 = !DILocation(line: 53, column: 3, scope: !2)
!64 = distinct !DISubprogram(name: "main", scope: !3, file: !3, line: 75, type: !28, scopeLine: 75, spFlags: DISPFlagDefinition, unit: !7, retainedNodes: !9)
!65 = !DILocation(line: 76, column: 10, scope: !64)
!66 = !DILocation(line: 76, column: 3, scope: !64)
!67 = distinct !DISubprogram(name: "get_ewma", scope: !14, file: !14, line: 65, type: !68, scopeLine: 65, flags: DIFlagPrototyped, spFlags: DISPFlagDefinition, unit: !15, retainedNodes: !9)
!68 = !DISubroutineType(types: !69)
!69 = !{!6, !6}
!70 = !DILocalVariable(name: "x", arg: 1, scope: !67, file: !14, line: 65, type: !6)
!71 = !DILocation(line: 65, column: 24, scope: !67)
!72 = !DILocalVariable(name: "x1", scope: !67, file: !14, line: 70, type: !6)
!73 = !DILocation(line: 70, column: 10, scope: !67)
!74 = !DILocation(line: 70, column: 3, scope: !67)
!75 = !DILocalVariable(name: "y1", scope: !67, file: !14, line: 70, type: !6)
!76 = !DILocation(line: 70, column: 14, scope: !67)
!77 = !DILocalVariable(name: "z1", scope: !67, file: !14, line: 70, type: !6)
!78 = !DILocation(line: 70, column: 18, scope: !67)
!79 = !DILocation(line: 73, column: 8, scope: !67)
!80 = !DILocation(line: 73, column: 6, scope: !67)
!81 = !DILocation(line: 74, column: 8, scope: !67)
!82 = !DILocation(line: 74, column: 6, scope: !67)
!83 = !DILocation(line: 75, column: 18, scope: !67)
!84 = !DILocation(line: 75, column: 22, scope: !67)
!85 = !DILocation(line: 75, column: 8, scope: !67)
!86 = !DILocation(line: 75, column: 6, scope: !67)
!87 = !DILocation(line: 76, column: 10, scope: !67)
!88 = !DILocation(line: 76, column: 3, scope: !67)
!89 = !DILocation(line: 59, column: 8, scope: !13)
!90 = !DILocation(line: 59, column: 5, scope: !13)
!91 = !DILocation(line: 60, column: 10, scope: !13)
!92 = !DILocation(line: 60, column: 3, scope: !13)
!93 = !DILocalVariable(name: "a", arg: 1, scope: !20, file: !14, line: 45, type: !6)
!94 = !DILocation(line: 45, column: 25, scope: !20)
!95 = !DILocalVariable(name: "b", arg: 2, scope: !20, file: !14, line: 45, type: !6)
!96 = !DILocation(line: 45, column: 35, scope: !20)
!97 = !DILocalVariable(name: "alpha", scope: !20, file: !14, line: 46, type: !98)
!98 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !6)
!99 = !DILocation(line: 46, column: 17, scope: !20)
!100 = !DILocation(line: 48, column: 16, scope: !20)
!101 = !DILocation(line: 48, column: 20, scope: !20)
!102 = !DILocation(line: 48, column: 18, scope: !20)
!103 = !DILocation(line: 48, column: 13, scope: !20)
!104 = !DILocation(line: 48, column: 39, scope: !20)
!105 = !DILocation(line: 48, column: 37, scope: !20)
!106 = !DILocation(line: 48, column: 23, scope: !20)
!107 = !DILocation(line: 48, column: 5, scope: !20)
!108 = !DILocation(line: 49, column: 10, scope: !20)
!109 = !DILocation(line: 49, column: 3, scope: !20)
