; ModuleID = 'llvm-link'
source_filename = "llvm-link"
target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-pc-linux-gnu"

@llvm.global.annotations = appending global [4 x { i8*, i8*, i8*, i32 }] [{ i8*, i8*, i8*, i32 } { i8* bitcast (double* @get_a.a to i8*), i8* getelementptr inbounds ([7 x i8], [7 x i8]* @.str, i32 0, i32 0), i8* getelementptr inbounds ([36 x i8], [36 x i8]* @.str.1, i32 0, i32 0), i32 46 }, { i8*, i8*, i8*, i32 } { i8* bitcast (double ()* @get_a to i8*), i8* getelementptr inbounds ([16 x i8], [16 x i8]* @.str.2, i32 0, i32 0), i8* getelementptr inbounds ([36 x i8], [36 x i8]* @.str.1, i32 0, i32 0), i32 41 }, { i8*, i8*, i8*, i32 } { i8* bitcast (double* @get_b.b to i8*), i8* getelementptr inbounds ([7 x i8], [7 x i8]* @.str.3, i32 0, i32 0), i8* getelementptr inbounds ([36 x i8], [36 x i8]* @.str.1.4, i32 0, i32 0), i32 48 }, { i8*, i8*, i8*, i32 } { i8* bitcast (i32 ()* @ewma_main to i8*), i8* getelementptr inbounds ([10 x i8], [10 x i8]* @.str.3.5, i32 0, i32 0), i8* getelementptr inbounds ([36 x i8], [36 x i8]* @.str.1.4, i32 0, i32 0), i32 56 }], section "llvm.metadata"
@get_a.a = internal global double 0.000000e+00, align 8, !dbg !0
@.str = private unnamed_addr constant [7 x i8] c"ORANGE\00", section "llvm.metadata"
@.str.1 = private unnamed_addr constant [36 x i8] c"./divvied-working/orange/example1.c\00", section "llvm.metadata"
@.str.2 = private unnamed_addr constant [16 x i8] c"XDLINKAGE_GET_A\00", section "llvm.metadata"
@get_b.b = internal global double 1.000000e+00, align 8, !dbg !11
@.str.3 = private unnamed_addr constant [7 x i8] c"PURPLE\00", section "llvm.metadata"
@.str.1.4 = private unnamed_addr constant [36 x i8] c"./divvied-working/purple/example1.c\00", section "llvm.metadata"
@.str.3.5 = private unnamed_addr constant [10 x i8] c"EWMA_MAIN\00", section "llvm.metadata"
@.str.2.6 = private unnamed_addr constant [4 x i8] c"%f\0A\00", align 1
@calc_ewma.c = internal global double 0.000000e+00, align 8, !dbg !18

; Function Attrs: noinline nounwind optnone uwtable
define dso_local double @get_a() #0 !dbg !2 {
  %1 = load double, double* @get_a.a, align 8, !dbg !27
  %2 = fadd double %1, 1.000000e+00, !dbg !27
  store double %2, double* @get_a.a, align 8, !dbg !27
  %3 = load double, double* @get_a.a, align 8, !dbg !28
  ret double %3, !dbg !29
}

; Function Attrs: noinline nounwind optnone uwtable
define dso_local i32 @ewma_main() #0 !dbg !30 {
  %1 = alloca double, align 8
  %2 = alloca double, align 8
  %3 = alloca double, align 8
  %4 = alloca i32, align 4
  call void @llvm.dbg.declare(metadata double* %1, metadata !34, metadata !DIExpression()), !dbg !35
  call void @llvm.dbg.declare(metadata double* %2, metadata !36, metadata !DIExpression()), !dbg !37
  call void @llvm.dbg.declare(metadata double* %3, metadata !38, metadata !DIExpression()), !dbg !39
  %5 = bitcast double* %3 to i8*, !dbg !40
  call void @llvm.var.annotation(i8* %5, i8* getelementptr inbounds ([7 x i8], [7 x i8]* @.str.3, i32 0, i32 0), i8* getelementptr inbounds ([36 x i8], [36 x i8]* @.str.1.4, i32 0, i32 0), i32 63), !dbg !40
  call void @llvm.dbg.declare(metadata i32* %4, metadata !41, metadata !DIExpression()), !dbg !43
  store i32 0, i32* %4, align 4, !dbg !43
  br label %6, !dbg !44

6:                                                ; preds = %18, %0
  %7 = load i32, i32* %4, align 4, !dbg !45
  %8 = icmp slt i32 %7, 10, !dbg !47
  br i1 %8, label %9, label %21, !dbg !48

9:                                                ; preds = %6
  %10 = call i32 (...) bitcast (double ()* @get_a to i32 (...)*)() #4, !dbg !49
  %11 = sitofp i32 %10 to double, !dbg !49
  store double %11, double* %1, align 8, !dbg !51
  %12 = call double @get_b() #4, !dbg !52
  store double %12, double* %2, align 8, !dbg !53
  %13 = load double, double* %1, align 8, !dbg !54
  %14 = load double, double* %2, align 8, !dbg !55
  %15 = call double @calc_ewma(double %13, double %14) #4, !dbg !56
  store double %15, double* %3, align 8, !dbg !57
  %16 = load double, double* %3, align 8, !dbg !58
  %17 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str.2.6, i64 0, i64 0), double %16) #4, !dbg !59
  br label %18, !dbg !60

18:                                               ; preds = %9
  %19 = load i32, i32* %4, align 4, !dbg !61
  %20 = add nsw i32 %19, 1, !dbg !61
  store i32 %20, i32* %4, align 4, !dbg !61
  br label %6, !dbg !62, !llvm.loop !63

21:                                               ; preds = %6
  ret i32 0, !dbg !65
}

; Function Attrs: nounwind readnone speculatable willreturn
declare void @llvm.dbg.declare(metadata, metadata, metadata) #1

; Function Attrs: nounwind willreturn
declare void @llvm.var.annotation(i8*, i8*, i8*, i32) #2

; Function Attrs: noinline nounwind optnone uwtable
define dso_local double @get_b() #0 !dbg !13 {
  %1 = load double, double* @get_b.b, align 8, !dbg !66
  %2 = load double, double* @get_b.b, align 8, !dbg !67
  %3 = fadd double %2, %1, !dbg !67
  store double %3, double* @get_b.b, align 8, !dbg !67
  %4 = load double, double* @get_b.b, align 8, !dbg !68
  ret double %4, !dbg !69
}

; Function Attrs: noinline nounwind optnone uwtable
define dso_local double @calc_ewma(double %0, double %1) #0 !dbg !20 {
  %3 = alloca double, align 8
  %4 = alloca double, align 8
  %5 = alloca double, align 8
  store double %0, double* %3, align 8
  call void @llvm.dbg.declare(metadata double* %3, metadata !70, metadata !DIExpression()), !dbg !71
  store double %1, double* %4, align 8
  call void @llvm.dbg.declare(metadata double* %4, metadata !72, metadata !DIExpression()), !dbg !73
  call void @llvm.dbg.declare(metadata double* %5, metadata !74, metadata !DIExpression()), !dbg !76
  store double 2.500000e-01, double* %5, align 8, !dbg !76
  %6 = load double, double* %3, align 8, !dbg !77
  %7 = load double, double* %4, align 8, !dbg !78
  %8 = fadd double %6, %7, !dbg !79
  %9 = fmul double 2.500000e-01, %8, !dbg !80
  %10 = load double, double* @calc_ewma.c, align 8, !dbg !81
  %11 = fmul double 7.500000e-01, %10, !dbg !82
  %12 = fadd double %9, %11, !dbg !83
  store double %12, double* @calc_ewma.c, align 8, !dbg !84
  %13 = load double, double* @calc_ewma.c, align 8, !dbg !85
  ret double %13, !dbg !86
}

declare dso_local i32 @printf(i8*, ...) #3

; Function Attrs: noinline nounwind optnone uwtable
define dso_local i32 @main(i32 %0, i8** %1) #0 !dbg !87 {
  %3 = alloca i32, align 4
  %4 = alloca i32, align 4
  %5 = alloca i8**, align 8
  store i32 0, i32* %3, align 4
  store i32 %0, i32* %4, align 4
  call void @llvm.dbg.declare(metadata i32* %4, metadata !93, metadata !DIExpression()), !dbg !94
  store i8** %1, i8*** %5, align 8
  call void @llvm.dbg.declare(metadata i8*** %5, metadata !95, metadata !DIExpression()), !dbg !96
  %6 = call i32 @ewma_main() #4, !dbg !97
  ret i32 %6, !dbg !98
}

attributes #0 = { noinline nounwind optnone uwtable "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "frame-pointer"="all" "less-precise-fpmad"="false" "min-legal-vector-width"="0" "no-builtins" "no-infs-fp-math"="false" "no-jump-tables"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { nounwind readnone speculatable willreturn }
attributes #2 = { nounwind willreturn }
attributes #3 = { "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "frame-pointer"="all" "less-precise-fpmad"="false" "no-builtins" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #4 = { nobuiltin "no-builtins" }

!llvm.dbg.cu = !{!7, !15}
!llvm.ident = !{!23, !23}
!llvm.module.flags = !{!24, !25, !26}

!0 = !DIGlobalVariableExpression(var: !1, expr: !DIExpression())
!1 = distinct !DIGlobalVariable(name: "a", scope: !2, file: !3, line: 46, type: !6, isLocal: true, isDefinition: true)
!2 = distinct !DISubprogram(name: "get_a", scope: !3, file: !3, line: 41, type: !4, scopeLine: 41, spFlags: DISPFlagDefinition, unit: !7, retainedNodes: !9)
!3 = !DIFile(filename: "./divvied-working/orange/example1.c", directory: "/workspaces/build/apps/examples/example1")
!4 = !DISubroutineType(types: !5)
!5 = !{!6}
!6 = !DIBasicType(name: "double", size: 64, encoding: DW_ATE_float)
!7 = distinct !DICompileUnit(language: DW_LANG_C99, file: !8, producer: "clang version 10.0.0-4ubuntu1 ", isOptimized: false, runtimeVersion: 0, emissionKind: FullDebug, enums: !9, globals: !10, splitDebugInlining: false, nameTableKind: None)
!8 = !DIFile(filename: "divvied-working/orange/example1.c", directory: "/workspaces/build/apps/examples/example1")
!9 = !{}
!10 = !{!0}
!11 = !DIGlobalVariableExpression(var: !12, expr: !DIExpression())
!12 = distinct !DIGlobalVariable(name: "b", scope: !13, file: !14, line: 48, type: !6, isLocal: true, isDefinition: true)
!13 = distinct !DISubprogram(name: "get_b", scope: !14, file: !14, line: 45, type: !4, scopeLine: 45, spFlags: DISPFlagDefinition, unit: !15, retainedNodes: !9)
!14 = !DIFile(filename: "./divvied-working/purple/example1.c", directory: "/workspaces/build/apps/examples/example1")
!15 = distinct !DICompileUnit(language: DW_LANG_C99, file: !16, producer: "clang version 10.0.0-4ubuntu1 ", isOptimized: false, runtimeVersion: 0, emissionKind: FullDebug, enums: !9, globals: !17, splitDebugInlining: false, nameTableKind: None)
!16 = !DIFile(filename: "divvied-working/purple/example1.c", directory: "/workspaces/build/apps/examples/example1")
!17 = !{!18, !11}
!18 = !DIGlobalVariableExpression(var: !19, expr: !DIExpression())
!19 = distinct !DIGlobalVariable(name: "c", scope: !20, file: !14, line: 41, type: !6, isLocal: true, isDefinition: true)
!20 = distinct !DISubprogram(name: "calc_ewma", scope: !14, file: !14, line: 39, type: !21, scopeLine: 39, flags: DIFlagPrototyped, spFlags: DISPFlagDefinition, unit: !15, retainedNodes: !9)
!21 = !DISubroutineType(types: !22)
!22 = !{!6, !6, !6}
!23 = !{!"clang version 10.0.0-4ubuntu1 "}
!24 = !{i32 7, !"Dwarf Version", i32 4}
!25 = !{i32 2, !"Debug Info Version", i32 3}
!26 = !{i32 1, !"wchar_size", i32 4}
!27 = !DILocation(line: 49, column: 5, scope: !2)
!28 = !DILocation(line: 50, column: 10, scope: !2)
!29 = !DILocation(line: 50, column: 3, scope: !2)
!30 = distinct !DISubprogram(name: "ewma_main", scope: !14, file: !14, line: 56, type: !31, scopeLine: 56, spFlags: DISPFlagDefinition, unit: !15, retainedNodes: !9)
!31 = !DISubroutineType(types: !32)
!32 = !{!33}
!33 = !DIBasicType(name: "int", size: 32, encoding: DW_ATE_signed)
!34 = !DILocalVariable(name: "x", scope: !30, file: !14, line: 59, type: !6)
!35 = !DILocation(line: 59, column: 10, scope: !30)
!36 = !DILocalVariable(name: "y", scope: !30, file: !14, line: 60, type: !6)
!37 = !DILocation(line: 60, column: 10, scope: !30)
!38 = !DILocalVariable(name: "ewma", scope: !30, file: !14, line: 63, type: !6)
!39 = !DILocation(line: 63, column: 10, scope: !30)
!40 = !DILocation(line: 63, column: 3, scope: !30)
!41 = !DILocalVariable(name: "i", scope: !42, file: !14, line: 66, type: !33)
!42 = distinct !DILexicalBlock(scope: !30, file: !14, line: 66, column: 3)
!43 = !DILocation(line: 66, column: 12, scope: !42)
!44 = !DILocation(line: 66, column: 8, scope: !42)
!45 = !DILocation(line: 66, column: 17, scope: !46)
!46 = distinct !DILexicalBlock(scope: !42, file: !14, line: 66, column: 3)
!47 = !DILocation(line: 66, column: 19, scope: !46)
!48 = !DILocation(line: 66, column: 3, scope: !42)
!49 = !DILocation(line: 67, column: 9, scope: !50)
!50 = distinct !DILexicalBlock(scope: !46, file: !14, line: 66, column: 30)
!51 = !DILocation(line: 67, column: 7, scope: !50)
!52 = !DILocation(line: 68, column: 9, scope: !50)
!53 = !DILocation(line: 68, column: 7, scope: !50)
!54 = !DILocation(line: 69, column: 22, scope: !50)
!55 = !DILocation(line: 69, column: 24, scope: !50)
!56 = !DILocation(line: 69, column: 12, scope: !50)
!57 = !DILocation(line: 69, column: 10, scope: !50)
!58 = !DILocation(line: 70, column: 20, scope: !50)
!59 = !DILocation(line: 70, column: 5, scope: !50)
!60 = !DILocation(line: 71, column: 3, scope: !50)
!61 = !DILocation(line: 66, column: 26, scope: !46)
!62 = !DILocation(line: 66, column: 3, scope: !46)
!63 = distinct !{!63, !48, !64}
!64 = !DILocation(line: 71, column: 3, scope: !42)
!65 = !DILocation(line: 72, column: 3, scope: !30)
!66 = !DILocation(line: 51, column: 8, scope: !13)
!67 = !DILocation(line: 51, column: 5, scope: !13)
!68 = !DILocation(line: 52, column: 10, scope: !13)
!69 = !DILocation(line: 52, column: 3, scope: !13)
!70 = !DILocalVariable(name: "a", arg: 1, scope: !20, file: !14, line: 39, type: !6)
!71 = !DILocation(line: 39, column: 25, scope: !20)
!72 = !DILocalVariable(name: "b", arg: 2, scope: !20, file: !14, line: 39, type: !6)
!73 = !DILocation(line: 39, column: 35, scope: !20)
!74 = !DILocalVariable(name: "alpha", scope: !20, file: !14, line: 40, type: !75)
!75 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !6)
!76 = !DILocation(line: 40, column: 17, scope: !20)
!77 = !DILocation(line: 42, column: 16, scope: !20)
!78 = !DILocation(line: 42, column: 20, scope: !20)
!79 = !DILocation(line: 42, column: 18, scope: !20)
!80 = !DILocation(line: 42, column: 13, scope: !20)
!81 = !DILocation(line: 42, column: 39, scope: !20)
!82 = !DILocation(line: 42, column: 37, scope: !20)
!83 = !DILocation(line: 42, column: 23, scope: !20)
!84 = !DILocation(line: 42, column: 5, scope: !20)
!85 = !DILocation(line: 43, column: 10, scope: !20)
!86 = !DILocation(line: 43, column: 3, scope: !20)
!87 = distinct !DISubprogram(name: "main", scope: !14, file: !14, line: 74, type: !88, scopeLine: 74, flags: DIFlagPrototyped, spFlags: DISPFlagDefinition, unit: !15, retainedNodes: !9)
!88 = !DISubroutineType(types: !89)
!89 = !{!33, !33, !90}
!90 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !91, size: 64)
!91 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !92, size: 64)
!92 = !DIBasicType(name: "char", size: 8, encoding: DW_ATE_signed_char)
!93 = !DILocalVariable(name: "argc", arg: 1, scope: !87, file: !14, line: 74, type: !33)
!94 = !DILocation(line: 74, column: 14, scope: !87)
!95 = !DILocalVariable(name: "argv", arg: 2, scope: !87, file: !14, line: 74, type: !90)
!96 = !DILocation(line: 74, column: 27, scope: !87)
!97 = !DILocation(line: 75, column: 10, scope: !87)
!98 = !DILocation(line: 75, column: 3, scope: !87)
