# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.15

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

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "C:\Program Files\JetBrains\CLion 2019.2.4\bin\cmake\win\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Program Files\JetBrains\CLion 2019.2.4\bin\cmake\win\bin\cmake.exe" -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = "C:\Users\huc3\Documents\GitHub\Data-Structure\Lab11\check 4"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "C:\Users\huc3\Documents\GitHub\Data-Structure\Lab11\check 4\cmake-build-debug"

# Include any dependencies generated for this target.
include CMakeFiles/check_4.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/check_4.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/check_4.dir/flags.make

CMakeFiles/check_4.dir/main.cpp.obj: CMakeFiles/check_4.dir/flags.make
CMakeFiles/check_4.dir/main.cpp.obj: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="C:\Users\huc3\Documents\GitHub\Data-Structure\Lab11\check 4\cmake-build-debug\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/check_4.dir/main.cpp.obj"
	C:\PROGRA~2\mingw-w64\i686-8.1.0-posix-dwarf-rt_v6-rev0\mingw32\bin\g++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\check_4.dir\main.cpp.obj -c "C:\Users\huc3\Documents\GitHub\Data-Structure\Lab11\check 4\main.cpp"

CMakeFiles/check_4.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/check_4.dir/main.cpp.i"
	C:\PROGRA~2\mingw-w64\i686-8.1.0-posix-dwarf-rt_v6-rev0\mingw32\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "C:\Users\huc3\Documents\GitHub\Data-Structure\Lab11\check 4\main.cpp" > CMakeFiles\check_4.dir\main.cpp.i

CMakeFiles/check_4.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/check_4.dir/main.cpp.s"
	C:\PROGRA~2\mingw-w64\i686-8.1.0-posix-dwarf-rt_v6-rev0\mingw32\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "C:\Users\huc3\Documents\GitHub\Data-Structure\Lab11\check 4\main.cpp" -o CMakeFiles\check_4.dir\main.cpp.s

# Object files for target check_4
check_4_OBJECTS = \
"CMakeFiles/check_4.dir/main.cpp.obj"

# External object files for target check_4
check_4_EXTERNAL_OBJECTS =

check_4.exe: CMakeFiles/check_4.dir/main.cpp.obj
check_4.exe: CMakeFiles/check_4.dir/build.make
check_4.exe: CMakeFiles/check_4.dir/linklibs.rsp
check_4.exe: CMakeFiles/check_4.dir/objects1.rsp
check_4.exe: CMakeFiles/check_4.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="C:\Users\huc3\Documents\GitHub\Data-Structure\Lab11\check 4\cmake-build-debug\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable check_4.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\check_4.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/check_4.dir/build: check_4.exe

.PHONY : CMakeFiles/check_4.dir/build

CMakeFiles/check_4.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\check_4.dir\cmake_clean.cmake
.PHONY : CMakeFiles/check_4.dir/clean

CMakeFiles/check_4.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" "C:\Users\huc3\Documents\GitHub\Data-Structure\Lab11\check 4" "C:\Users\huc3\Documents\GitHub\Data-Structure\Lab11\check 4" "C:\Users\huc3\Documents\GitHub\Data-Structure\Lab11\check 4\cmake-build-debug" "C:\Users\huc3\Documents\GitHub\Data-Structure\Lab11\check 4\cmake-build-debug" "C:\Users\huc3\Documents\GitHub\Data-Structure\Lab11\check 4\cmake-build-debug\CMakeFiles\check_4.dir\DependInfo.cmake" --color=$(COLOR)
.PHONY : CMakeFiles/check_4.dir/depend
