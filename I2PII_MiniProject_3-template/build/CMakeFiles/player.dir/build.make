# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.17

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Disable VCS-based implicit rules.
% : %,v


# Disable VCS-based implicit rules.
% : RCS/%


# Disable VCS-based implicit rules.
% : RCS/%,v


# Disable VCS-based implicit rules.
% : SCCS/s.%


# Disable VCS-based implicit rules.
% : s.%


.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "C:\Program Files (x86)\Microsoft Visual Studio\2019\Community\Common7\IDE\CommonExtensions\Microsoft\CMake\CMake\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Program Files (x86)\Microsoft Visual Studio\2019\Community\Common7\IDE\CommonExtensions\Microsoft\CMake\CMake\bin\cmake.exe" -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = C:\Winston\projects\I2PII_MiniProject_3-template

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = C:\Winston\projects\I2PII_MiniProject_3-template\build

# Include any dependencies generated for this target.
include CMakeFiles/player.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/player.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/player.dir/flags.make

CMakeFiles/player.dir/player.cpp.obj: CMakeFiles/player.dir/flags.make
CMakeFiles/player.dir/player.cpp.obj: ../player.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Winston\projects\I2PII_MiniProject_3-template\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/player.dir/player.cpp.obj"
	C:\MinGW\bin\mingw32-g++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\player.dir\player.cpp.obj -c C:\Winston\projects\I2PII_MiniProject_3-template\player.cpp

CMakeFiles/player.dir/player.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/player.dir/player.cpp.i"
	C:\MinGW\bin\mingw32-g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Winston\projects\I2PII_MiniProject_3-template\player.cpp > CMakeFiles\player.dir\player.cpp.i

CMakeFiles/player.dir/player.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/player.dir/player.cpp.s"
	C:\MinGW\bin\mingw32-g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Winston\projects\I2PII_MiniProject_3-template\player.cpp -o CMakeFiles\player.dir\player.cpp.s

# Object files for target player
player_OBJECTS = \
"CMakeFiles/player.dir/player.cpp.obj"

# External object files for target player
player_EXTERNAL_OBJECTS =

../player.exe: CMakeFiles/player.dir/player.cpp.obj
../player.exe: CMakeFiles/player.dir/build.make
../player.exe: CMakeFiles/player.dir/linklibs.rsp
../player.exe: CMakeFiles/player.dir/objects1.rsp
../player.exe: CMakeFiles/player.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=C:\Winston\projects\I2PII_MiniProject_3-template\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable ..\player.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\player.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/player.dir/build: ../player.exe

.PHONY : CMakeFiles/player.dir/build

CMakeFiles/player.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\player.dir\cmake_clean.cmake
.PHONY : CMakeFiles/player.dir/clean

CMakeFiles/player.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" C:\Winston\projects\I2PII_MiniProject_3-template C:\Winston\projects\I2PII_MiniProject_3-template C:\Winston\projects\I2PII_MiniProject_3-template\build C:\Winston\projects\I2PII_MiniProject_3-template\build C:\Winston\projects\I2PII_MiniProject_3-template\build\CMakeFiles\player.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/player.dir/depend

