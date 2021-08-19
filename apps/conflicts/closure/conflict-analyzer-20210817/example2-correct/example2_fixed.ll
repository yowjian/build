; ModuleID = 'example2_fixed.bc'
source_filename = "example2_fixed.c"
target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

@calc_ewma.c = internal global double 0.000000e+00, align 8, !dbg !0
@get_a.a = internal global double 0.000000e+00, align 8, !dbg !10
@get_b.b = internal global double 1.000000e+00, align 8, !dbg !15
@.str = private unnamed_addr constant [4 x i8] c"%f\0A\00", align 1

; Function Attrs: noinline nounwind optnone uwtable
define dso_local double @calc_ewma(double %0, double %1) #0 !dbg !2 {
  %3 = alloca double, align 8
  %4 = alloca double, align 8
  %5 = alloca double, align 8
  store double %0, double* %3, align 8
  call void @llvm.dbg.declare(metadata double* %3, metadata !22, metadata !DIExpression()), !dbg !23
  store double %1, double* %4, align 8
  call void @llvm.dbg.declare(metadata double* %4, metadata !24, metadata !DIExpression()), !dbg !25
  call void @llvm.dbg.declare(metadata double* %5, metadata !26, metadata !DIExpression()), !dbg !28
  store double 2.500000e-01, double* %5, align 8, !dbg !28
  %6 = load double, double* %3, align 8, !dbg !29
  %7 = load double, double* %4, align 8, !dbg !30
  %8 = fadd double %6, %7, !dbg !31
  %9 = fmul double 2.500000e-01, %8, !dbg !32
  %10 = load double, double* @calc_ewma.c, align 8, !dbg !33
  %11 = fmul double 7.500000e-01, %10, !dbg !34
  %12 = fadd double %9, %11, !dbg !35
  store double %12, double* @calc_ewma.c, align 8, !dbg !36
  %13 = load double, double* @calc_ewma.c, align 8, !dbg !37
  ret double %13, !dbg !38
}

; Function Attrs: nounwind readnone speculatable willreturn
declare void @llvm.dbg.declare(metadata, metadata, metadata) #1

; Function Attrs: noinline nounwind optnone uwtable
define dso_local double @get_a() #0 !dbg !12 {
  %1 = load double, double* @get_a.a, align 8, !dbg !39
  %2 = fadd double %1, 1.000000e+00, !dbg !39
  store double %2, double* @get_a.a, align 8, !dbg !39
  %3 = load double, double* @get_a.a, align 8, !dbg !40
  ret double %3, !dbg !41
}

; Function Attrs: noinline nounwind optnone uwtable
define dso_local double @get_b() #0 !dbg !17 {
  %1 = load double, double* @get_b.b, align 8, !dbg !42
  %2 = load double, double* @get_b.b, align 8, !dbg !43
  %3 = fadd double %2, %1, !dbg !43
  store double %3, double* @get_b.b, align 8, !dbg !43
  %4 = load double, double* @get_b.b, align 8, !dbg !44
  ret double %4, !dbg !45
}

; Function Attrs: noinline nounwind optnone uwtable
define dso_local double @get_ewma(double %0) #0 !dbg !46 {
  %2 = alloca double, align 8
  %3 = alloca double, align 8
  %4 = alloca double, align 8
  %5 = alloca double, align 8
  store double %0, double* %2, align 8
  call void @llvm.dbg.declare(metadata double* %2, metadata !49, metadata !DIExpression()), !dbg !50
  call void @llvm.dbg.declare(metadata double* %3, metadata !51, metadata !DIExpression()), !dbg !52
  call void @llvm.dbg.declare(metadata double* %4, metadata !53, metadata !DIExpression()), !dbg !54
  call void @llvm.dbg.declare(metadata double* %5, metadata !55, metadata !DIExpression()), !dbg !56
  %6 = load double, double* %2, align 8, !dbg !57
  store double %6, double* %3, align 8, !dbg !58
  %7 = call double @get_b(), !dbg !59
  store double %7, double* %4, align 8, !dbg !60
  %8 = load double, double* %3, align 8, !dbg !61
  %9 = load double, double* %4, align 8, !dbg !62
  %10 = call double @calc_ewma(double %8, double %9), !dbg !63
  store double %10, double* %5, align 8, !dbg !64
  %11 = load double, double* %5, align 8, !dbg !65
  ret double %11, !dbg !66
}

; Function Attrs: noinline nounwind optnone uwtable
define dso_local i32 @ewma_main() #0 !dbg !67 {
  %1 = alloca double, align 8
  %2 = alloca double, align 8
  %3 = alloca double, align 8
  %4 = alloca i32, align 4
  call void @llvm.dbg.declare(metadata double* %1, metadata !71, metadata !DIExpression()), !dbg !72
  call void @llvm.dbg.declare(metadata double* %2, metadata !73, metadata !DIExpression()), !dbg !74
  call void @llvm.dbg.declare(metadata double* %3, metadata !75, metadata !DIExpression()), !dbg !76
  call void @llvm.dbg.declare(metadata i32* %4, metadata !77, metadata !DIExpression()), !dbg !79
  store i32 0, i32* %4, align 4, !dbg !79
  br label %5, !dbg !80

5:                                                ; preds = %14, %0
  %6 = load i32, i32* %4, align 4, !dbg !81
  %7 = icmp slt i32 %6, 10, !dbg !83
  br i1 %7, label %8, label %17, !dbg !84

8:                                                ; preds = %5
  %9 = call double @get_a(), !dbg !85
  store double %9, double* %1, align 8, !dbg !87
  %10 = load double, double* %1, align 8, !dbg !88
  %11 = call double @get_ewma(double %10), !dbg !89
  store double %11, double* %3, align 8, !dbg !90
  %12 = load double, double* %3, align 8, !dbg !91
  %13 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str, i64 0, i64 0), double %12), !dbg !92
  br label %14, !dbg !93

14:                                               ; preds = %8
  %15 = load i32, i32* %4, align 4, !dbg !94
  %16 = add nsw i32 %15, 1, !dbg !94
  store i32 %16, i32* %4, align 4, !dbg !94
  br label %5, !dbg !95, !llvm.loop !96

17:                                               ; preds = %5
  ret i32 0, !dbg !98
}

declare dso_local i32 @printf(i8*, ...) #2

; Function Attrs: noinline nounwind optnone uwtable
define dso_local i32 @main() #0 !dbg !99 {
  %1 = alloca i32, align 4
  store i32 0, i32* %1, align 4
  %2 = call i32 @ewma_main(), !dbg !100
  ret i32 %2, !dbg !101
}

attributes #0 = { noinline nounwind optnone uwtable "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "frame-pointer"="all" "less-precise-fpmad"="false" "min-legal-vector-width"="0" "no-infs-fp-math"="false" "no-jump-tables"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { nounwind readnone speculatable willreturn }
attributes #2 = { "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "frame-pointer"="all" "less-precise-fpmad"="false" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }

!llvm.dbg.cu = !{!7}
!llvm.module.flags = !{!18, !19, !20}
!llvm.ident = !{!21}

!0 = !DIGlobalVariableExpression(var: !1, expr: !DIExpression())
!1 = distinct !DIGlobalVariable(name: "c", scope: !2, file: !3, line: 35, type: !6, isLocal: true, isDefinition: true)
!2 = distinct !DISubprogram(name: "calc_ewma", scope: !3, file: !3, line: 33, type: !4, scopeLine: 33, flags: DIFlagPrototyped, spFlags: DISPFlagDefinition, unit: !7, retainedNodes: !8)
!3 = !DIFile(filename: "example2_fixed.c", directory: "/home/rbrotzman/temp_zinc_data/20210817/example2-correct")
!4 = !DISubroutineType(types: !5)
!5 = !{!6, !6, !6}
!6 = !DIBasicType(name: "double", size: 64, encoding: DW_ATE_float)
!7 = distinct !DICompileUnit(language: DW_LANG_C99, file: !3, producer: "clang version 10.0.1 (https://github.com/gaps-closure/llvm-project 4954dd8b02af91d5e8d4815824208b6004f667a8)", isOptimized: false, runtimeVersion: 0, emissionKind: FullDebug, enums: !8, globals: !9, splitDebugInlining: false, nameTableKind: None)
!8 = !{}
!9 = !{!0, !10, !15}
!10 = !DIGlobalVariableExpression(var: !11, expr: !DIExpression())
!11 = distinct !DIGlobalVariable(name: "a", scope: !12, file: !3, line: 42, type: !6, isLocal: true, isDefinition: true)
!12 = distinct !DISubprogram(name: "get_a", scope: !3, file: !3, line: 40, type: !13, scopeLine: 40, spFlags: DISPFlagDefinition, unit: !7, retainedNodes: !8)
!13 = !DISubroutineType(types: !14)
!14 = !{!6}
!15 = !DIGlobalVariableExpression(var: !16, expr: !DIExpression())
!16 = distinct !DIGlobalVariable(name: "b", scope: !17, file: !3, line: 50, type: !6, isLocal: true, isDefinition: true)
!17 = distinct !DISubprogram(name: "get_b", scope: !3, file: !3, line: 48, type: !13, scopeLine: 48, spFlags: DISPFlagDefinition, unit: !7, retainedNodes: !8)
!18 = !{i32 7, !"Dwarf Version", i32 4}
!19 = !{i32 2, !"Debug Info Version", i32 3}
!20 = !{i32 1, !"wchar_size", i32 4}
!21 = !{!"clang version 10.0.1 (https://github.com/gaps-closure/llvm-project 4954dd8b02af91d5e8d4815824208b6004f667a8)"}
!22 = !DILocalVariable(name: "a", arg: 1, scope: !2, file: !3, line: 33, type: !6)
!23 = !DILocation(line: 33, column: 25, scope: !2)
!24 = !DILocalVariable(name: "b", arg: 2, scope: !2, file: !3, line: 33, type: !6)
!25 = !DILocation(line: 33, column: 35, scope: !2)
!26 = !DILocalVariable(name: "alpha", scope: !2, file: !3, line: 34, type: !27)
!27 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !6)
!28 = !DILocation(line: 34, column: 17, scope: !2)
!29 = !DILocation(line: 36, column: 16, scope: !2)
!30 = !DILocation(line: 36, column: 20, scope: !2)
!31 = !DILocation(line: 36, column: 18, scope: !2)
!32 = !DILocation(line: 36, column: 13, scope: !2)
!33 = !DILocation(line: 36, column: 39, scope: !2)
!34 = !DILocation(line: 36, column: 37, scope: !2)
!35 = !DILocation(line: 36, column: 23, scope: !2)
!36 = !DILocation(line: 36, column: 5, scope: !2)
!37 = !DILocation(line: 37, column: 10, scope: !2)
!38 = !DILocation(line: 37, column: 3, scope: !2)
!39 = !DILocation(line: 44, column: 5, scope: !12)
!40 = !DILocation(line: 45, column: 10, scope: !12)
!41 = !DILocation(line: 45, column: 3, scope: !12)
!42 = !DILocation(line: 52, column: 8, scope: !17)
!43 = !DILocation(line: 52, column: 5, scope: !17)
!44 = !DILocation(line: 53, column: 10, scope: !17)
!45 = !DILocation(line: 53, column: 3, scope: !17)
!46 = distinct !DISubprogram(name: "get_ewma", scope: !3, file: !3, line: 57, type: !47, scopeLine: 57, flags: DIFlagPrototyped, spFlags: DISPFlagDefinition, unit: !7, retainedNodes: !8)
!47 = !DISubroutineType(types: !48)
!48 = !{!6, !6}
!49 = !DILocalVariable(name: "x", arg: 1, scope: !46, file: !3, line: 57, type: !6)
!50 = !DILocation(line: 57, column: 24, scope: !46)
!51 = !DILocalVariable(name: "x1", scope: !46, file: !3, line: 60, type: !6)
!52 = !DILocation(line: 60, column: 10, scope: !46)
!53 = !DILocalVariable(name: "y1", scope: !46, file: !3, line: 60, type: !6)
!54 = !DILocation(line: 60, column: 14, scope: !46)
!55 = !DILocalVariable(name: "z1", scope: !46, file: !3, line: 60, type: !6)
!56 = !DILocation(line: 60, column: 18, scope: !46)
!57 = !DILocation(line: 62, column: 8, scope: !46)
!58 = !DILocation(line: 62, column: 6, scope: !46)
!59 = !DILocation(line: 63, column: 8, scope: !46)
!60 = !DILocation(line: 63, column: 6, scope: !46)
!61 = !DILocation(line: 64, column: 18, scope: !46)
!62 = !DILocation(line: 64, column: 22, scope: !46)
!63 = !DILocation(line: 64, column: 8, scope: !46)
!64 = !DILocation(line: 64, column: 6, scope: !46)
!65 = !DILocation(line: 65, column: 10, scope: !46)
!66 = !DILocation(line: 65, column: 3, scope: !46)
!67 = distinct !DISubprogram(name: "ewma_main", scope: !3, file: !3, line: 68, type: !68, scopeLine: 68, spFlags: DISPFlagDefinition, unit: !7, retainedNodes: !8)
!68 = !DISubroutineType(types: !69)
!69 = !{!70}
!70 = !DIBasicType(name: "int", size: 32, encoding: DW_ATE_signed)
!71 = !DILocalVariable(name: "x", scope: !67, file: !3, line: 69, type: !6)
!72 = !DILocation(line: 69, column: 10, scope: !67)
!73 = !DILocalVariable(name: "y", scope: !67, file: !3, line: 70, type: !6)
!74 = !DILocation(line: 70, column: 10, scope: !67)
!75 = !DILocalVariable(name: "ewma", scope: !67, file: !3, line: 72, type: !6)
!76 = !DILocation(line: 72, column: 10, scope: !67)
!77 = !DILocalVariable(name: "i", scope: !78, file: !3, line: 74, type: !70)
!78 = distinct !DILexicalBlock(scope: !67, file: !3, line: 74, column: 3)
!79 = !DILocation(line: 74, column: 12, scope: !78)
!80 = !DILocation(line: 74, column: 8, scope: !78)
!81 = !DILocation(line: 74, column: 17, scope: !82)
!82 = distinct !DILexicalBlock(scope: !78, file: !3, line: 74, column: 3)
!83 = !DILocation(line: 74, column: 19, scope: !82)
!84 = !DILocation(line: 74, column: 3, scope: !78)
!85 = !DILocation(line: 75, column: 9, scope: !86)
!86 = distinct !DILexicalBlock(scope: !82, file: !3, line: 74, column: 30)
!87 = !DILocation(line: 75, column: 7, scope: !86)
!88 = !DILocation(line: 76, column: 21, scope: !86)
!89 = !DILocation(line: 76, column: 12, scope: !86)
!90 = !DILocation(line: 76, column: 10, scope: !86)
!91 = !DILocation(line: 77, column: 20, scope: !86)
!92 = !DILocation(line: 77, column: 5, scope: !86)
!93 = !DILocation(line: 78, column: 3, scope: !86)
!94 = !DILocation(line: 74, column: 26, scope: !82)
!95 = !DILocation(line: 74, column: 3, scope: !82)
!96 = distinct !{!96, !84, !97}
!97 = !DILocation(line: 78, column: 3, scope: !78)
!98 = !DILocation(line: 79, column: 3, scope: !67)
!99 = distinct !DISubprogram(name: "main", scope: !3, file: !3, line: 82, type: !68, scopeLine: 82, spFlags: DISPFlagDefinition, unit: !7, retainedNodes: !8)
!100 = !DILocation(line: 83, column: 10, scope: !99)
!101 = !DILocation(line: 83, column: 3, scope: !99)
