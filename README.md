#Electromedia Cipher (EMC) Core

## Preface
Public usage of EMC before release is expressly prohibited, NDA pending.

## Capabilities of EMC-Core
Todo...

## Installation
* Fork EMC-Core to a repository of your own
* Download [Boost Version 1.58.0](http://www.boost.org/) or later and unzip to your /Program Files (x86)/ directory
* Download [the dependencies suite for EMC-Core](http://www.neuravion.io/file.axd?file=/EMC/EMC%20Requirements.zip "EMC-Core Dependencies") and unzip to the folder containing your executable

## Changelog
* v0.1.8.0 -- Added EmcCore class, which is going to be responsible for handling the program's workflow and every single component (mostly Analyzers)
* v0.1.7.4c -- Removed an enum from ArduinoReadableFileWriter and fixed some stuff in CorrMath/EntryPoint
* v0.1.7.4 -- Fixed MANY method names to be consisten with naming conventions. Added CoreMath static class and removed CommonOperations... Lots of cleanup here.
* v0.1.7.3 -- Changed FFTPreprocessing functions to sit within a static class. Cleaned up some terminology within that new static class, and fixed a bug which prevented the ConfigurationHandler from accessing the config file in some random places
* v0.1.7.2g: Made project location agnostic (see installation)
* v0.1.7.2f: Improved main readme, started refactoring ConfigurationHandler and other major pieces of code
* v0.1.7.2e: Added readme with markup
* v0.1.7.2d: Cleanup of /ipch folder, which should not exist; began factoring out FrequencyRangeProfile
* v0.1.7.2c: Removed some more files (/Debug)
* v0.1.7.2b: Minor fixes to Git repository
* v0.1.7.2a: Refactored all Analyzers into separate files; added Constants.h; added redefinition prevention tags
* v0.1.7.1:  Beginning of refactoring towards EMC-Core 1.0.0 Release
