; ModuleID = 'example2.bc'
source_filename = "example2.c"
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
  store double %0, double* %2, align 8
  call void @llvm.dbg.declare(metadata double* %2, metadata !49, metadata !DIExpression()), !dbg !50
  call void @llvm.dbg.declare(metadata double* %3, metadata !51, metadata !DIExpression()), !dbg !52
  %4 = call double @get_b(), !dbg !53
  store double %4, double* %3, align 8, !dbg !52
  %5 = load double, double* %2, align 8, !dbg !54
  %6 = load double, double* %3, align 8, !dbg !55
  %7 = call double @calc_ewma(double %5, double %6), !dbg !56
  ret double %7, !dbg !57
}

; Function Attrs: noinline nounwind optnone uwtable
define dso_local i32 @ewma_main() #0 !dbg !58 {
  %1 = alloca double, align 8
  %2 = alloca double, align 8
  %3 = alloca double, align 8
  %4 = alloca i32, align 4
  call void @llvm.dbg.declare(metadata double* %1, metadata !62, metadata !DIExpression()), !dbg !63
  call void @llvm.dbg.declare(metadata double* %2, metadata !64, metadata !DIExpression()), !dbg !65
  call void @llvm.dbg.declare(metadata double* %3, metadata !66, metadata !DIExpression()), !dbg !67
  call void @llvm.dbg.declare(metadata i32* %4, metadata !68, metadata !DIExpression()), !dbg !70
  store i32 0, i32* %4, align 4, !dbg !70
  br label %5, !dbg !71

5:                                                ; preds = %14, %0
  %6 = load i32, i32* %4, align 4, !dbg !72
  %7 = icmp slt i32 %6, 10, !dbg !74
  br i1 %7, label %8, label %17, !dbg !75

8:                                                ; preds = %5
  %9 = call double @get_a(), !dbg !76
  store double %9, double* %1, align 8, !dbg !78
  %10 = load double, double* %1, align 8, !dbg !79
  %11 = call double @get_ewma(double %10), !dbg !80
  store double %11, double* %3, align 8, !dbg !81
  %12 = load double, double* %3, align 8, !dbg !82
  %13 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str, i64 0, i64 0), double %12), !dbg !83
  br label %14, !dbg !84

14:                                               ; preds = %8
  %15 = load i32, i32* %4, align 4, !dbg !85
  %16 = add nsw i32 %15, 1, !dbg !85
  store i32 %16, i32* %4, align 4, !dbg !85
  br label %5, !dbg !86, !llvm.loop !87

17:                                               ; preds = %5
  ret i32 0, !dbg !89
}

declare dso_local i32 @printf(i8*, ...) #2

; Function Attrs: noinline nounwind optnone uwtable
define dso_local i32 @main() #0 !dbg !90 {
  %1 = alloca i32, align 4
  store i32 0, i32* %1, align 4
  %2 = call i32 @ewma_main(), !dbg !91
  ret i32 %2, !dbg !92
}

attributes #0 = { noinline nounwind optnone uwtable "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "frame-pointer"="all" "less-precise-fpmad"="false" "min-legal-vector-width"="0" "no-infs-fp-math"="false" "no-jump-tables"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { nounwind readnone speculatable willreturn }
attributes #2 = { "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "frame-pointer"="all" "less-precise-fpmad"="false" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }

!llvm.dbg.cu = !{!7}
!llvm.module.flags = !{!18, !19, !20}
!llvm.ident = !{!21}

!0 = !DIGlobalVariableExpression(var: !1, expr: !DIExpression())
!1 = distinct !DIGlobalVariable(name: "c", scope: !2, file: !3, line: 24, type: !6, isLocal: true, isDefinition: true)
!2 = distinct !DISubprogram(name: "calc_ewma", scope: !3, file: !3, line: 22, type: !4, scopeLine: 22, flags: DIFlagPrototyped, spFlags: DISPFlagDefinition, unit: !7, retainedNodes: !8)
!3 = !DIFile(filename: "example2.c", directory: "/home/rbrotzman/temp_zinc_data/20210817/example2-error")
!4 = !DISubroutineType(types: !5)
!5 = !{!6, !6, !6}
!6 = !DIBasicType(name: "double", size: 64, encoding: DW_ATE_float)
!7 = distinct !DICompileUnit(language: DW_LANG_C99, file: !3, producer: "clang version 10.0.1 (https://github.com/gaps-closure/llvm-project 4954dd8b02af91d5e8d4815824208b6004f667a8)", isOptimized: false, runtimeVersion: 0, emissionKind: FullDebug, enums: !8, globals: !9, splitDebugInlining: false, nameTableKind: None)
!8 = !{}
!9 = !{!0, !10, !15}
!10 = !DIGlobalVariableExpression(var: !11, expr: !DIExpression())
!11 = distinct !DIGlobalVariable(name: "a", scope: !12, file: !3, line: 31, type: !6, isLocal: true, isDefinition: true)
!12 = distinct !DISubprogram(name: "get_a", scope: !3, file: !3, line: 29, type: !13, scopeLine: 29, spFlags: DISPFlagDefinition, unit: !7, retainedNodes: !8)
!13 = !DISubroutineType(types: !14)
!14 = !{!6}
!15 = !DIGlobalVariableExpression(var: !16, expr: !DIExpression())
!16 = distinct !DIGlobalVariable(name: "b", scope: !17, file: !3, line: 39, type: !6, isLocal: true, isDefinition: true)
!17 = distinct !DISubprogram(name: "get_b", scope: !3, file: !3, line: 37, type: !13, scopeLine: 37, spFlags: DISPFlagDefinition, unit: !7, retainedNodes: !8)
!18 = !{i32 7, !"Dwarf Version", i32 4}
!19 = !{i32 2, !"Debug Info Version", i32 3}
!20 = !{i32 1, !"wchar_size", i32 4}
!21 = !{!"clang version 10.0.1 (https://github.com/gaps-closure/llvm-project 4954dd8b02af91d5e8d4815824208b6004f667a8)"}
!22 = !DILocalVariable(name: "a", arg: 1, scope: !2, file: !3, line: 22, type: !6)
!23 = !DILocation(line: 22, column: 25, scope: !2)
!24 = !DILocalVariable(name: "b", arg: 2, scope: !2, file: !3, line: 22, type: !6)
!25 = !DILocation(line: 22, column: 35, scope: !2)
!26 = !DILocalVariable(name: "alpha", scope: !2, file: !3, line: 23, type: !27)
!27 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !6)
!28 = !DILocation(line: 23, column: 17, scope: !2)
!29 = !DILocation(line: 25, column: 16, scope: !2)
!30 = !DILocation(line: 25, column: 20, scope: !2)
!31 = !DILocation(line: 25, column: 18, scope: !2)
!32 = !DILocation(line: 25, column: 13, scope: !2)
!33 = !DILocation(line: 25, column: 39, scope: !2)
!34 = !DILocation(line: 25, column: 37, scope: !2)
!35 = !DILocation(line: 25, column: 23, scope: !2)
!36 = !DILocation(line: 25, column: 5, scope: !2)
!37 = !DILocation(line: 26, column: 10, scope: !2)
!38 = !DILocation(line: 26, column: 3, scope: !2)
!39 = !DILocation(line: 33, column: 5, scope: !12)
!40 = !DILocation(line: 34, column: 10, scope: !12)
!41 = !DILocation(line: 34, column: 3, scope: !12)
!42 = !DILocation(line: 41, column: 8, scope: !17)
!43 = !DILocation(line: 41, column: 5, scope: !17)
!44 = !DILocation(line: 42, column: 10, scope: !17)
!45 = !DILocation(line: 42, column: 3, scope: !17)
!46 = distinct !DISubprogram(name: "get_ewma", scope: !3, file: !3, line: 46, type: !47, scopeLine: 46, flags: DIFlagPrototyped, spFlags: DISPFlagDefinition, unit: !7, retainedNodes: !8)
!47 = !DISubroutineType(types: !48)
!48 = !{!6, !6}
!49 = !DILocalVariable(name: "x", arg: 1, scope: !46, file: !3, line: 46, type: !6)
!50 = !DILocation(line: 46, column: 24, scope: !46)
!51 = !DILocalVariable(name: "y", scope: !46, file: !3, line: 48, type: !6)
!52 = !DILocation(line: 48, column: 10, scope: !46)
!53 = !DILocation(line: 48, column: 14, scope: !46)
!54 = !DILocation(line: 49, column: 20, scope: !46)
!55 = !DILocation(line: 49, column: 22, scope: !46)
!56 = !DILocation(line: 49, column: 10, scope: !46)
!57 = !DILocation(line: 49, column: 3, scope: !46)
!58 = distinct !DISubprogram(name: "ewma_main", scope: !3, file: !3, line: 52, type: !59, scopeLine: 52, spFlags: DISPFlagDefinition, unit: !7, retainedNodes: !8)
!59 = !DISubroutineType(types: !60)
!60 = !{!61}
!61 = !DIBasicType(name: "int", size: 32, encoding: DW_ATE_signed)
!62 = !DILocalVariable(name: "x", scope: !58, file: !3, line: 53, type: !6)
!63 = !DILocation(line: 53, column: 10, scope: !58)
!64 = !DILocalVariable(name: "y", scope: !58, file: !3, line: 54, type: !6)
!65 = !DILocation(line: 54, column: 10, scope: !58)
!66 = !DILocalVariable(name: "ewma", scope: !58, file: !3, line: 56, type: !6)
!67 = !DILocation(line: 56, column: 10, scope: !58)
!68 = !DILocalVariable(name: "i", scope: !69, file: !3, line: 58, type: !61)
!69 = distinct !DILexicalBlock(scope: !58, file: !3, line: 58, column: 3)
!70 = !DILocation(line: 58, column: 12, scope: !69)
!71 = !DILocation(line: 58, column: 8, scope: !69)
!72 = !DILocation(line: 58, column: 17, scope: !73)
!73 = distinct !DILexicalBlock(scope: !69, file: !3, line: 58, column: 3)
!74 = !DILocation(line: 58, column: 19, scope: !73)
!75 = !DILocation(line: 58, column: 3, scope: !69)
!76 = !DILocation(line: 59, column: 9, scope: !77)
!77 = distinct !DILexicalBlock(scope: !73, file: !3, line: 58, column: 30)
!78 = !DILocation(line: 59, column: 7, scope: !77)
!79 = !DILocation(line: 60, column: 21, scope: !77)
!80 = !DILocation(line: 60, column: 12, scope: !77)
!81 = !DILocation(line: 60, column: 10, scope: !77)
!82 = !DILocation(line: 61, column: 20, scope: !77)
!83 = !DILocation(line: 61, column: 5, scope: !77)
!84 = !DILocation(line: 62, column: 3, scope: !77)
!85 = !DILocation(line: 58, column: 26, scope: !73)
!86 = !DILocation(line: 58, column: 3, scope: !73)
!87 = distinct !{!87, !75, !88}
!88 = !DILocation(line: 62, column: 3, scope: !69)
!89 = !DILocation(line: 63, column: 3, scope: !58)
!90 = distinct !DISubprogram(name: "main", scope: !3, file: !3, line: 66, type: !59, scopeLine: 66, spFlags: DISPFlagDefinition, unit: !7, retainedNodes: !8)
!91 = !DILocation(line: 67, column: 10, scope: !90)
!92 = !DILocation(line: 67, column: 3, scope: !90)
