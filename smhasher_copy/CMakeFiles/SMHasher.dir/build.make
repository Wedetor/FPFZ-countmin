# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.22

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

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
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
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/pregrado/joscortes2021/Escritorio/TMGVD-Proy1/smhasher_copy

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/pregrado/joscortes2021/Escritorio/TMGVD-Proy1/smhasher_copy

# Include any dependencies generated for this target.
include CMakeFiles/SMHasher.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/SMHasher.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/SMHasher.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/SMHasher.dir/flags.make

CMakeFiles/SMHasher.dir/main.o: CMakeFiles/SMHasher.dir/flags.make
CMakeFiles/SMHasher.dir/main.o: main.cpp
CMakeFiles/SMHasher.dir/main.o: CMakeFiles/SMHasher.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/pregrado/joscortes2021/Escritorio/TMGVD-Proy1/smhasher_copy/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/SMHasher.dir/main.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/SMHasher.dir/main.o -MF CMakeFiles/SMHasher.dir/main.o.d -o CMakeFiles/SMHasher.dir/main.o -c /home/pregrado/joscortes2021/Escritorio/TMGVD-Proy1/smhasher_copy/main.cpp

CMakeFiles/SMHasher.dir/main.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/SMHasher.dir/main.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/pregrado/joscortes2021/Escritorio/TMGVD-Proy1/smhasher_copy/main.cpp > CMakeFiles/SMHasher.dir/main.i

CMakeFiles/SMHasher.dir/main.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/SMHasher.dir/main.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/pregrado/joscortes2021/Escritorio/TMGVD-Proy1/smhasher_copy/main.cpp -o CMakeFiles/SMHasher.dir/main.s

# Object files for target SMHasher
SMHasher_OBJECTS = \
"CMakeFiles/SMHasher.dir/main.o"

# External object files for target SMHasher
SMHasher_EXTERNAL_OBJECTS =

SMHasher: CMakeFiles/SMHasher.dir/main.o
SMHasher: CMakeFiles/SMHasher.dir/build.make
SMHasher: libSMHasherSupport.a
SMHasher: CMakeFiles/SMHasher.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/pregrado/joscortes2021/Escritorio/TMGVD-Proy1/smhasher_copy/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable SMHasher"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/SMHasher.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/SMHasher.dir/build: SMHasher
.PHONY : CMakeFiles/SMHasher.dir/build

CMakeFiles/SMHasher.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/SMHasher.dir/cmake_clean.cmake
.PHONY : CMakeFiles/SMHasher.dir/clean

CMakeFiles/SMHasher.dir/depend:
	cd /home/pregrado/joscortes2021/Escritorio/TMGVD-Proy1/smhasher_copy && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/pregrado/joscortes2021/Escritorio/TMGVD-Proy1/smhasher_copy /home/pregrado/joscortes2021/Escritorio/TMGVD-Proy1/smhasher_copy /home/pregrado/joscortes2021/Escritorio/TMGVD-Proy1/smhasher_copy /home/pregrado/joscortes2021/Escritorio/TMGVD-Proy1/smhasher_copy /home/pregrado/joscortes2021/Escritorio/TMGVD-Proy1/smhasher_copy/CMakeFiles/SMHasher.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/SMHasher.dir/depend
