This directory includes a number of test applications, each intended to
exercise specific components of the CLOSURE toolchain.

Each test must include:
  1. Unannotated working input program 
  2. A document in English listing the partitioning intent, security policy 
     (what data needs to protected at what level, and what the cross-domain 
      sharing constraints are), and the properties of input program (e.g., 
      what C/C++ subset, deterministism, concurrency, control, and communication
      patterns)
  3. A document listing the test intent in terms of artifacts to be produces, 
     and success criteria for each tool/step, including Preprocessing,
     Conflicts, Refactoring Actions/Advice, Marshalling (IDL generation),
     Autogeneration (Serialization codecs, DFDL, gueard rules in DAGR, and HAL
     config), Security Compliance Verifier, Correctness Verifier, HAL, CVI, MBIG
     (e.g., x86/ARM targets), Emu
  
Until the toolchain is fully implemented, we will additionally need to include
sample output, and intermediate artifacts, which include:
  1. Correctly annotated working input program, conforming to CLE and 
     implementing the partitioning intent
  2. Correctly annotated working partitioned program, conforming to CLE, 
     HAL API, and documented refactoring methodology
  3. Pointers to documentation (with correct version) for CLE, HAL API, 
     DFDL, DAGR, Refactoring methodology, and CLOSURE tool versions to 
     be used for this test

