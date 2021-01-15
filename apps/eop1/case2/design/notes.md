flow 1501
  component 1 (orange) -> component 5 (green) 
  message type (01) : component_heartbeats (see schema)
  label ALLOW_ORANGE_GREEN

Implications:
  component 1 must be on orange
  component 4 must be on green
  component 1 on the correct slot (inFlow/outFlow sequence) must allow the ALLOW_ORANGE_GREEN taint
  component 4 on the correct slot (inFlow/outFlow sequence) must allow the ALLOW_ORANGE_GREEN taint


local_component_hearbeats is set to 0 // false 

egress_component_hearbeats must run on orange side
egress_component_hearbeats must call echo_component_hearbeats, which must run on green side usign XD RPC

this involves
  _rpc_echo_component_heartbeats on orange side creating and sending message
  (since it cannto call echo_component_heatbeats)
  _handle_echo_component_heartbeats on green side receiving message and calling
  echo_component_heartbeats which will posting to AMQ broker on green side

function and data annotations in generated code are inferred from design spec
-- design spec annotated message flows, not data and functions associated with RPCs in the generated code // these are inferred and generated

===
design -> verify -> autogen annotated code in C
apply classic CLOSURE workflow to autogen annotated code (similar to ERI summit)


