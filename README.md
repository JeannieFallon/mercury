# mercury
A local host auditing agent with LLM-powered analysis and automated system responses

## Description
Mercury is a lightweight, modular system auditor designed to provide local observability with human-readable insights.
The tool runs as a daemon or on-demand utility to gather system metrics, analyze metrics using locally hosted LLMs, and
then deliver customized insights and suggestions to the user.

By translating low-level system state into clear, actionable briefs, Mercury empowers users to understand and manage
their own machines without specialized systems knowledge.

The current implementation includes: 
- timestamped, leveled logging system with automatic file creation
- integration with `libcurl` to communicate with a locally running Ollama server
- initial support for sending static prompts and receiving full JSON responses

Mercury builds and runs natively on macOS with C++17, setting up the foundation for robust metric collection, 
natural language analysis, and automated system response in future versions.

## Purpose
- Audit and monitor local system state (open ports, services, logs)
- Analyze observations using local LLM inference for contextual insights
- Automate pre-configured system responses (alerts, remediation, reporting)
- Make advanced system introspection accessible to non-experts

## System Requirements
Mercury is designed to run natively on macOS, taking advantage of:
- Apple Silicon performance
- Metal-accelerated local LLM inference
- macOS-friendly build and deployment options
