# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.7

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /tmp/tmp.GXRjpGjsv7

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /tmp/tmp.GXRjpGjsv7/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/semPraca.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/semPraca.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/semPraca.dir/flags.make

CMakeFiles/semPraca.dir/main.c.o: CMakeFiles/semPraca.dir/flags.make
CMakeFiles/semPraca.dir/main.c.o: ../main.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/tmp/tmp.GXRjpGjsv7/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/semPraca.dir/main.c.o"
	/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/semPraca.dir/main.c.o   -c /tmp/tmp.GXRjpGjsv7/main.c

CMakeFiles/semPraca.dir/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/semPraca.dir/main.c.i"
	/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /tmp/tmp.GXRjpGjsv7/main.c > CMakeFiles/semPraca.dir/main.c.i

CMakeFiles/semPraca.dir/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/semPraca.dir/main.c.s"
	/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /tmp/tmp.GXRjpGjsv7/main.c -o CMakeFiles/semPraca.dir/main.c.s

CMakeFiles/semPraca.dir/main.c.o.requires:

.PHONY : CMakeFiles/semPraca.dir/main.c.o.requires

CMakeFiles/semPraca.dir/main.c.o.provides: CMakeFiles/semPraca.dir/main.c.o.requires
	$(MAKE) -f CMakeFiles/semPraca.dir/build.make CMakeFiles/semPraca.dir/main.c.o.provides.build
.PHONY : CMakeFiles/semPraca.dir/main.c.o.provides

CMakeFiles/semPraca.dir/main.c.o.provides.build: CMakeFiles/semPraca.dir/main.c.o


# Object files for target semPraca
semPraca_OBJECTS = \
"CMakeFiles/semPraca.dir/main.c.o"

# External object files for target semPraca
semPraca_EXTERNAL_OBJECTS =

semPraca: CMakeFiles/semPraca.dir/main.c.o
semPraca: CMakeFiles/semPraca.dir/build.make
semPraca: CMakeFiles/semPraca.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/tmp/tmp.GXRjpGjsv7/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable semPraca"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/semPraca.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/semPraca.dir/build: semPraca

.PHONY : CMakeFiles/semPraca.dir/build

CMakeFiles/semPraca.dir/requires: CMakeFiles/semPraca.dir/main.c.o.requires

.PHONY : CMakeFiles/semPraca.dir/requires

CMakeFiles/semPraca.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/semPraca.dir/cmake_clean.cmake
.PHONY : CMakeFiles/semPraca.dir/clean

CMakeFiles/semPraca.dir/depend:
	cd /tmp/tmp.GXRjpGjsv7/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /tmp/tmp.GXRjpGjsv7 /tmp/tmp.GXRjpGjsv7 /tmp/tmp.GXRjpGjsv7/cmake-build-debug /tmp/tmp.GXRjpGjsv7/cmake-build-debug /tmp/tmp.GXRjpGjsv7/cmake-build-debug/CMakeFiles/semPraca.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/semPraca.dir/depend

