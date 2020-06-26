# Expected Output Artifacts and Test Success Criteria

## MULES

Input:  

 * CLE-annotated input source

Output: 

 * On success produce Pre-processed C/C++ and Companion CLE-JSON file
 * On failure, produce diagnositics

Criteria:

 * Check CLE syntax is valid JSON 
 * Check CLE-JSON is syntactically valid JSON
 * Check CLE-JSON is semantically valid (to be elaborated)
 * Check for tags missing CLE-JSON 
 * Translate to clang annotations 
 * TBD -- distinguish between annotations for variable, function, and 
   cross-domain tag

## CAPO 

### Conflict analysis 

Input:

 * CLE-annotated program and Companion CLE-JSON

Output:

 * Conflict log
 * Action log

Criteria:

 * List of conflicts - TBD (XXX: based on partitioning intent)
 * Well-defined and documented conflict message 

### Marshalling 

Input:

 * CLE-annotated program and Companion CLE-JSON

Output:

 * IDL file for autogeneration
 * ACTIONS needed in code for cross-domain exchange including datatype munging

Criteria:

 * TBD

### Refactoring Guidance
Input:

 * CLE-annotated program, Companion CLE-JSON
 * HW/SW topology map

Output:

 * Structured guidance for refactoring program in terms of ACTIONs
 * Correct annotated partitioned programs (with human in loop)

Criteria:

 * Well-defined and documented ACTION messages: both for human and machine
 * Well-defined and documented topology map format
 * Actions are adequate for a typical programmer
 * Actions cover code changes, annotations, and library linkage needed
 * Applying the actions results in a correct partitioned program

### Automated Refactoring

Input:

 * CLE-annotated program and Companion CLE-JSON

Output:

 * Partitioned programs, codecs, DFDL, DAGR, HAL config

Criteria:

 * TBD

### Autogeneration 

Input:

 * IDL file
 * Companion CLE-JSON, repertoire of supported hardware actions
 * HW/SW topology map

Output:

 * Serialization codecs (from IDL)
 * DFDL (from IDL)
 * DAGR (from CLE-JSON and repertoire)
 * HAL config (from topology map)

### Security Compliance Verifier

Input:

 * CLE-annotated input and partitioned programs, Companion CLE-JSON

Output:

 * Summary and diagnostic verification report

Criteria:

 * Documented output format
 * XXX: Specific checks based on partitioning intent for this test
 * XXX: Elaborate based on requirements doc

### Correctness Verification

Input:

 * CLE-annotated input and partitioned programs, Companion CLE-JSON

Output:

 * Summary report, diagnostic report, and proof transcript

Criteria:

 * TBD

## HAL

Input:

 * Partitioned programs (for each comm pattern) and generated codecs
 * HAL configuration file

Criteria:

 * Support async-send/blocking-rev over zmq pub/sub
 * Support synchronous RPC over zmq TBD
 * Successful end-to-end test over HAL

## MBIG

Criteria:

 * Generate x86 binaries

## Emu

Criteria:

 * TBD

## CVI

Criteria:

 * TBD

