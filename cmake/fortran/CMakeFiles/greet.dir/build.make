# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.10

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
CMAKE_SOURCE_DIR = /home/user/cernbox/codesketch/cmake/fortran

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/user/cernbox/codesketch/cmake/fortran

# Include any dependencies generated for this target.
include CMakeFiles/greet.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/greet.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/greet.dir/flags.make

CMakeFiles/greet.dir/hello.f90.o: CMakeFiles/greet.dir/flags.make
CMakeFiles/greet.dir/hello.f90.o: hello.f90
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/user/cernbox/codesketch/cmake/fortran/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building Fortran object CMakeFiles/greet.dir/hello.f90.o"
	/usr/bin/gfortran $(Fortran_DEFINES) $(Fortran_INCLUDES) $(Fortran_FLAGS) -c /home/user/cernbox/codesketch/cmake/fortran/hello.f90 -o CMakeFiles/greet.dir/hello.f90.o

CMakeFiles/greet.dir/hello.f90.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing Fortran source to CMakeFiles/greet.dir/hello.f90.i"
	/usr/bin/gfortran $(Fortran_DEFINES) $(Fortran_INCLUDES) $(Fortran_FLAGS) -E /home/user/cernbox/codesketch/cmake/fortran/hello.f90 > CMakeFiles/greet.dir/hello.f90.i

CMakeFiles/greet.dir/hello.f90.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling Fortran source to assembly CMakeFiles/greet.dir/hello.f90.s"
	/usr/bin/gfortran $(Fortran_DEFINES) $(Fortran_INCLUDES) $(Fortran_FLAGS) -S /home/user/cernbox/codesketch/cmake/fortran/hello.f90 -o CMakeFiles/greet.dir/hello.f90.s

CMakeFiles/greet.dir/hello.f90.o.requires:

.PHONY : CMakeFiles/greet.dir/hello.f90.o.requires

CMakeFiles/greet.dir/hello.f90.o.provides: CMakeFiles/greet.dir/hello.f90.o.requires
	$(MAKE) -f CMakeFiles/greet.dir/build.make CMakeFiles/greet.dir/hello.f90.o.provides.build
.PHONY : CMakeFiles/greet.dir/hello.f90.o.provides

CMakeFiles/greet.dir/hello.f90.o.provides.build: CMakeFiles/greet.dir/hello.f90.o


# Object files for target greet
greet_OBJECTS = \
"CMakeFiles/greet.dir/hello.f90.o"

# External object files for target greet
greet_EXTERNAL_OBJECTS =

greet: CMakeFiles/greet.dir/hello.f90.o
greet: CMakeFiles/greet.dir/build.make
greet: CMakeFiles/greet.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/user/cernbox/codesketch/cmake/fortran/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking Fortran executable greet"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/greet.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/greet.dir/build: greet

.PHONY : CMakeFiles/greet.dir/build

CMakeFiles/greet.dir/requires: CMakeFiles/greet.dir/hello.f90.o.requires

.PHONY : CMakeFiles/greet.dir/requires

CMakeFiles/greet.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/greet.dir/cmake_clean.cmake
.PHONY : CMakeFiles/greet.dir/clean

CMakeFiles/greet.dir/depend:
	cd /home/user/cernbox/codesketch/cmake/fortran && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/user/cernbox/codesketch/cmake/fortran /home/user/cernbox/codesketch/cmake/fortran /home/user/cernbox/codesketch/cmake/fortran /home/user/cernbox/codesketch/cmake/fortran /home/user/cernbox/codesketch/cmake/fortran/CMakeFiles/greet.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/greet.dir/depend

