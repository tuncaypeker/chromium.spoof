# chromium.spoof
Custom Chromium Build — Fingerprint Spoofing Patches

This repository documents the custom fingerprint-spoofing work applied on top of a private Chromium build.
Each module shows before → after behavior, the exact patch logic, and test outputs from major detection sites (iphey, pixelscan, fingerprint.com, browserleaks).

🎯 Purpose  
--
To keep a clear, version-controlled record of:  
The spoof patches I add to Chromium (C++, GN args, build flags)  
Their expected outcomes  
Test results before/after the patch  
Known issues, crashes, or edge-case behaviors  
Notes for future debugging  

🔧 What This Repo Does Not Include  
--
Full Chromium source (not allowed + unnecessary here)  
Pre-built binaries  
Proprietary internal tools  
Sensitive project configuration  
