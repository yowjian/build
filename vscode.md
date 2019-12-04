<h2> VS Code  </h2>

```
# log on to jaga.
# create a project directory and cd to it
mkdir helloworld
cd helloworld

# copy VS Code project files
cp -r ~tchen/test/helloworld/.vscode .

# start vs code
code .

# Do the following if the backspace key is not working in vnc.
File>Preferences>Settings
Type Keyboard into the search box.
Select keyboard
Change the value to keyCode

# execute a build task defined in tasks.json
# The following will compile helloworld.cpp and create the executable helloworld.out
From the menu: "Terminal>Run Build Task"
Keyboard shortcut: Ctrl-Shift-B

# debugging
# only gdb is supported, not lldb
# if the code will spawn a subproress and you want to debug the subprocess (e.g. clang)
# put the following in ~/.gdbinit
set follow-fork-mode child
set detach-on-fork off

# execute the debugging task in launch.json
Debug>Start Debugging
Keyboard Shortcut: F5
