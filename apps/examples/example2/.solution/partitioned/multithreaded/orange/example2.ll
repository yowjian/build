; ModuleID = '/workspaces/build/apps/examples/example2/partitioned/multithreaded/orange/example2.c'
source_filename = "/workspaces/build/apps/examples/example2/partitioned/multithreaded/orange/example2.c"
target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-pc-linux-gnu"

@get_a.a = internal global double 0.000000e+00, align 8, !dbg !0
@.str = private unnamed_addr constant [7 x i8] c"ORANGE\00", section "llvm.metadata"
@.str.1 = private unnamed_addr constant [85 x i8] c"/workspaces/build/apps/examples/example2/partitioned/multithreaded/orange/example2.c\00", section "llvm.metadata"
@.str.2 = private unnamed_addr constant [4 x i8] c"%f\0A\00", align 1
@.str.3 = private unnamed_addr constant [10 x i8] c"EWMA_MAIN\00", section "llvm.metadata"
@llvm.global.annotations = appending global [2 x { i8*, i8*, i8*, i32 }] [{ i8*, i8*, i8*, i32 } { i8* bitcast (double* @get_a.a to i8*), i8* getelementptr inbounds ([7 x i8], [7 x i8]* @.str, i32 0, i32 0), i8* getelementptr inbounds ([85 x i8], [85 x i8]* @.str.1, i32 0, i32 0), i32 50 }, { i8*, i8*, i8*, i32 } { i8* bitcast (i32 ()* @ewma_main to i8*), i8* getelementptr inbounds ([10 x i8], [10 x i8]* @.str.3, i32 0, i32 0), i8* getelementptr inbounds ([85 x i8], [85 x i8]* @.str.1, i32 0, i32 0), i32 61 }], section "llvm.metadata"

; Function Attrs: noinline nounwind optnone uwtable
define dso_local double @get_a() #0 !dbg !2 {
  %1 = load double, double* @get_a.a, align 8, !dbg !15
  %2 = fadd double %1, 1.000000e+00, !dbg !15
  store double %2, double* @get_a.a, align 8, !dbg !15
  %3 = load double, double* @get_a.a, align 8, !dbg !16
  ret double %3, !dbg !17
}

; Function Attrs: noinline nounwind optnone uwtable
define dso_local i32 @ewma_main() #0 !dbg !18 {
  %1 = alloca double, align 8
  %2 = alloca double, align 8
  %3 = alloca double, align 8
  %4 = alloca i32, align 4
  call void @llvm.dbg.declare(metadata double* %1, metadata !22, metadata !DIExpression()), !dbg !23
  call void @llvm.dbg.declare(metadata double* %2, metadata !24, metadata !DIExpression()), !dbg !25
  call void @llvm.dbg.declare(metadata double* %3, metadata !26, metadata !DIExpression()), !dbg !27
  call void @llvm.dbg.declare(metadata i32* %4, metadata !28, metadata !DIExpression()), !dbg !30
  store i32 0, i32* %4, align 4, !dbg !30
  br label %5, !dbg !31

5:                                                ; preds = %15, %0
  %6 = load i32, i32* %4, align 4, !dbg !32
  %7 = icmp slt i32 %6, 10, !dbg !34
  br i1 %7, label %8, label %18, !dbg !35

8:                                                ; preds = %5
  %9 = call double @get_a(), !dbg !36
  store double %9, double* %1, align 8, !dbg !38
  %10 = load double, double* %1, align 8, !dbg !39
  store double %10, double* %2, align 8, !dbg !40
  %11 = load double, double* %2, align 8, !dbg !41
  %12 = call double @_err_handle_rpc_get_ewma(double %11), !dbg !42
  store double %12, double* %3, align 8, !dbg !43
  %13 = load double, double* %3, align 8, !dbg !44
  %14 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str.2, i64 0, i64 0), double %13), !dbg !45
  br label %15, !dbg !46

15:                                               ; preds = %8
  %16 = load i32, i32* %4, align 4, !dbg !47
  %17 = add nsw i32 %16, 1, !dbg !47
  store i32 %17, i32* %4, align 4, !dbg !47
  br label %5, !dbg !48, !llvm.loop !49

18:                                               ; preds = %5
  ret i32 0, !dbg !51
}

; Function Attrs: nounwind readnone speculatable willreturn
declare void @llvm.dbg.declare(metadata, metadata, metadata) #1

declare dso_local double @_err_handle_rpc_get_ewma(double) #2

declare dso_local i32 @printf(i8*, ...) #2

; Function Attrs: noinline nounwind optnone uwtable
define dso_local i32 @main() #0 !dbg !52 {
  %1 = alloca i32, align 4
  store i32 0, i32* %1, align 4
  call void (...) @_master_rpc_init(), !dbg !53
  %2 = call i32 @ewma_main(), !dbg !54
  ret i32 %2, !dbg !55
}

declare dso_local void @_master_rpc_init(...) #2

attributes #0 = { noinline nounwind optnone uwtable "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "frame-pointer"="all" "less-precise-fpmad"="false" "min-legal-vector-width"="0" "no-infs-fp-math"="false" "no-jump-tables"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { nounwind readnone speculatable willreturn }
attributes #2 = { "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "frame-pointer"="all" "less-precise-fpmad"="false" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }

!llvm.dbg.cu = !{!7}
!llvm.module.flags = !{!11, !12, !13}
!llvm.ident = !{!14}

!0 = !DIGlobalVariableExpression(var: !1, expr: !DIExpression())
!1 = distinct !DIGlobalVariable(name: "a", scope: !2, file: !3, line: 50, type: !6, isLocal: true, isDefinition: true)
!2 = distinct !DISubprogram(name: "get_a", scope: !3, file: !3, line: 47, type: !4, scopeLine: 47, spFlags: DISPFlagDefinition, unit: !7, retainedNodes: !9)
!3 = !DIFile(filename: "partitioned/multithreaded/orange/example2.c", directory: "/workspaces/build/apps/examples/example2")
!4 = !DISubroutineType(types: !5)
!5 = !{!6}
!6 = !DIBasicType(name: "double", size: 64, encoding: DW_ATE_float)
!7 = distinct !DICompileUnit(language: DW_LANG_C99, file: !8, producer: "clang version 10.0.0-4ubuntu1 ", isOptimized: false, runtimeVersion: 0, emissionKind: FullDebug, enums: !9, globals: !10, splitDebugInlining: false, nameTableKind: None)
!8 = !DIFile(filename: "/workspaces/build/apps/examples/example2/partitioned/multithreaded/orange/example2.c", directory: "/workspaces/build/apps/examples/example2")
!9 = !{}
!10 = !{!0}
!11 = !{i32 7, !"Dwarf Version", i32 4}
!12 = !{i32 2, !"Debug Info Version", i32 3}
!13 = !{i32 1, !"wchar_size", i32 4}
!14 = !{!"clang version 10.0.0-4ubuntu1 "}
!15 = !DILocation(line: 53, column: 5, scope: !2)
!16 = !DILocation(line: 54, column: 10, scope: !2)
!17 = !DILocation(line: 54, column: 3, scope: !2)
!18 = distinct !DISubprogram(name: "ewma_main", scope: !3, file: !3, line: 61, type: !19, scopeLine: 61, spFlags: DISPFlagDefinition, unit: !7, retainedNodes: !9)
!19 = !DISubroutineType(types: !20)
!20 = !{!21}
!21 = !DIBasicType(name: "int", size: 32, encoding: DW_ATE_signed)
!22 = !DILocalVariable(name: "x", scope: !18, file: !3, line: 64, type: !6)
!23 = !DILocation(line: 64, column: 10, scope: !18)
!24 = !DILocalVariable(name: "y", scope: !18, file: !3, line: 65, type: !6)
!25 = !DILocation(line: 65, column: 10, scope: !18)
!26 = !DILocalVariable(name: "ewma", scope: !18, file: !3, line: 66, type: !6)
!27 = !DILocation(line: 66, column: 10, scope: !18)
!28 = !DILocalVariable(name: "i", scope: !29, file: !3, line: 67, type: !21)
!29 = distinct !DILexicalBlock(scope: !18, file: !3, line: 67, column: 3)
!30 = !DILocation(line: 67, column: 12, scope: !29)
!31 = !DILocation(line: 67, column: 8, scope: !29)
!32 = !DILocation(line: 67, column: 17, scope: !33)
!33 = distinct !DILexicalBlock(scope: !29, file: !3, line: 67, column: 3)
!34 = !DILocation(line: 67, column: 19, scope: !33)
!35 = !DILocation(line: 67, column: 3, scope: !29)
!36 = !DILocation(line: 68, column: 9, scope: !37)
!37 = distinct !DILexicalBlock(scope: !33, file: !3, line: 67, column: 30)
!38 = !DILocation(line: 68, column: 7, scope: !37)
!39 = !DILocation(line: 69, column: 9, scope: !37)
!40 = !DILocation(line: 69, column: 7, scope: !37)
!41 = !DILocation(line: 70, column: 37, scope: !37)
!42 = !DILocation(line: 70, column: 12, scope: !37)
!43 = !DILocation(line: 70, column: 10, scope: !37)
!44 = !DILocation(line: 71, column: 20, scope: !37)
!45 = !DILocation(line: 71, column: 5, scope: !37)
!46 = !DILocation(line: 72, column: 3, scope: !37)
!47 = !DILocation(line: 67, column: 26, scope: !33)
!48 = !DILocation(line: 67, column: 3, scope: !33)
!49 = distinct !{!49, !35, !50}
!50 = !DILocation(line: 72, column: 3, scope: !29)
!51 = !DILocation(line: 73, column: 3, scope: !18)
!52 = distinct !DISubprogram(name: "main", scope: !3, file: !3, line: 76, type: !19, scopeLine: 76, spFlags: DISPFlagDefinition, unit: !7, retainedNodes: !9)
!53 = !DILocation(line: 77, column: 3, scope: !52)
!54 = !DILocation(line: 78, column: 10, scope: !52)
!55 = !DILocation(line: 78, column: 3, scope: !52)
