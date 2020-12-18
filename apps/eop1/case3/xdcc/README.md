# Overview

This directory contains CLOSURE artifacts for supporting the TA3 End-of-Phase1
demonstration application which is based on ActiveMQ. We expect that the
CLOSURE tools being developed for this purpose will be more generally useful to
develop messaging-based distributed cross-domain systems and to refactor those
applications in an agile fashion as the cross-domain security intent changes.

The CLOSURE tools will include:

  - a design GUI that will capture the components, message flows (dispatches), message contents and structure, cross-domain security annotations for each component, and cross-domain data sharing restrictions on each message
  - optionally, a sniffer that can capture and process application traffic to simplify the input of the message flows into the degin GUI
  - amqlib, a C library that wraps the AMQ C++ API to provide utility functions for the setup and teardown of AMQ broker connections, send and receive messages, and conversion from AMQ/Openwire/TextMessage/JSON to data structures matching the CLOSURE IDL
  - a hand-crafted C program of the cross-domain communications component (XDCC), including an egress handler and an ingress handler that calls amqlib and HAL API
  - autogenerator that takes an annotated design spec for a message-based cross-domain application and generates the XDCC component
