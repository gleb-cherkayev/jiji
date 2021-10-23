# To be included from the top-level cmake file.


# BUILD CONFIGURATIONS
# - Debug is no optimisation, asserts on.
# - Release is optimised, but asserts still on (no /NDEBUG).
# - Ship is fully optimised, including link-time optimisation, and asserts off.

# Also, dev-mode is always on in both Debug and Release.
# Controllable with command-line option on Ship, off by default.

set(CMAKE_CONFIGURATION_TYPES "Debug;Release;Ship" CACHE STRING "" FORCE)
# Create Ship from Release, and add extra flags (for linking-time optimisation).
set(CMAKE_CXX_FLAGS_SHIP "${CMAKE_CXX_FLAGS_RELEASE} /GL")
set(CMAKE_EXE_LINKER_FLAGS_SHIP "${CMAKE_EXE_LINKER_FLAGS_SHIP} /LTCG /INCREMENTAL:NO")
# Turn off NDEBUG in Release (but not Ship).
#set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /UNDEBUG") # This would cause D9025
string(REGEX REPLACE " /DNDEBUG" ""
	CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE}")
# Enable incremental linking for Release (as it is not doing /LTCG)
set(CMAKE_EXE_LINKER_FLAGS_RELEASE "${CMAKE_EXE_LINKER_FLAGS_RELEASE} /INCREMENTAL")


# Put binaries in the local .bin
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/.bin" CACHE PATH "")


# Common build options
add_definitions(-D"UNICODE" -D"_CRT_SECURE_NO_WARNINGS")
add_definitions(/std:c++latest /permissive- /MP /W4 /WX)
# /W4 is a bit over the top:
add_definitions(/wd4005)  # macro redefinition
add_definitions(/wd4063)  # not a valid value for switch of enum
add_definitions(/wd4100)  # unreferenced formal parameter
add_definitions(/wd4189)  # local variable is initialized but not referenced (range-for loops)
add_definitions(/wd4201)  # nonstandard extension used: nameless struct/union
add_definitions(/wd4611)  # interaction between '_setjmp' and C++ object destruction is non-portable
add_definitions(/wd4456)  # declaration of '...' hides previous local declaration
add_definitions(/wd4457)  # declaration of '...' hides function parameter
add_definitions(/wd4458)  # declaration of '...' hides class member
add_definitions(/wd4459)  # declaration of '...' hides global declaration
add_definitions(/wd5105)  # macro expansion producing 'defined' has undefined behavior
add_definitions(/wd5106)  # macro redefined with different parameter names


# THIRD-PARTY

# Supposed to be accessible from subdirectories, hence `..`.
include_directories("../third-party/include")
message(STATUS "BOOST_ROOT is `$ENV{BOOST_ROOT}`")
include_directories("$ENV{BOOST_ROOT}")  # NOTE: Relies on environment variable to be set.
link_directories("../third-party/lib-vs")


# MACROS

# Tweaks project configuration, common part applicable for both libraries and executables.
macro(jiji_configure_common name)
# - use static runtime;
set_target_properties(${name}
		PROPERTIES MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
endmacro(jiji_configure_common)

# Library configuration.
macro(jiji_configure_library name)
jiji_configure_common(${name})
endmacro(jiji_configure_library)

# Executable configuration.
macro(jiji_configure_executable name)
jiji_configure_common(${name})
# - working directory for debugging (path to output exe file), based on configuration name.
set_target_properties(${name}
		PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}/.bin/$(Configuration)")
endmacro(jiji_configure_executable)

# Marks the project as startup project of the solution.
macro(jiji_startup name)
set_property(DIRECTORY PROPERTY VS_STARTUP_PROJECT ${name})
endmacro(jiji_startup)
