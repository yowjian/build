<h1> VS Code Notes</h1>

# Installation

Log on to jaga and create a project directory and cd to it
* mkdir helloworld
* cd helloworld

Copy VS Code project files
* cp -r ~tchen/test/helloworld/.vscode .

Copy source code
* cp -r ~tchen/test/helloworld/helloworld.cpp .

Start vs code
* code .

Do the following if the backspace key is not working in vnc.
* File>Preferences>Settings
* Type Keyboard into the search box.
* Select keyboard
* Change the value to keyCode

Install C/C++ extensions
* Select the bottom icon (four squares) and type c/c++ into the search box.
* Check 'C/C++ IntelliSense, debugging, and code browsing' is in the ENABLED box.
* If not, type C/C++ into the search box, find and install it.

Execute a build task defined in tasks.json
The following will compile helloworld.cpp and create the executable helloworld.out
* From the menu: "Terminal>Run Build Task"
* Keyboard shortcut: Ctrl-Shift-B

# Debugging
* only gdb is supported, not lldb
* if the code will spawn a subprocess and you want to debug the subprocess (e.g. clang)
* put the following in ~/.gdbinit
** set follow-fork-mode child
** set detach-on-fork off

Execute the debugging task in launch.json, do one of the following
* Debug>Start Debugging
* Keyboard Shortcut: F5

# Syntax Highlighting for CLE
The easiest way at the momement is to
* Install the extension [Reloaded Themes](https://github.com/kobalicek/reloaded-themes)
* Customize, enhanced and install the extension [Reloaded C++](https://github.com/kobalicek/reloaded-cpp)

The most basic enhancement of Reloaded C++ is to add a rule to reloaded-cpp/syntaxes/c++.json to match pragma CLE's.
```
    "preprocessor-pragma-cle": {
      "name": "meta.preprocessor.block",
      "match": "^\\s*((#)\\s*(pragma\\s+cle\\s+def))\\s+(.*)",
      "captures": {
        "1": { "name": "meta.preprocessor.command.cpp" },
        "2": { "name": "meta.preprocessor.hash.cpp" },
        "3": { "name": "meta.preprocessor.keyword.pragma-mark.cpp" },
        "4": { "name": "meta.toc-list.pragma-mark.cpp" }
      }
    },
```

To build a VS Code extension, do the following
* npm install -g vsce             // to make sure you have vsce installed globally
* npm install                     // to install dependencies if you haven't already done so
* cd reloaded-cpp
* vsce package                    // to build the package. This will generate a file with extension vsix
* Run the command Extensions: Install from VSIX..., choose the vsix file generated in the previous step

To sideload an extension
* Open Visual Studio Code
* Select the Extensions pane.
* Click the ... at the top-right corner of the Extensions pane and select "Install from VSIX..." on the menu that appears.
* Locate the .vsix file and click "Install".
