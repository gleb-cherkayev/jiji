# Building lili library
file(GLOB_RECURSE JIJI_LIB_SOURCE
	CONFIGURE_DEPENDS
	./*.?pp
	./*.?xx
	./*.inl)
source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}" FILES ${JIJI_LIB_SOURCE})
add_library(jiji-lib STATIC ${JIJI_LIB_SOURCE})
jiji_configure_library(jiji-lib)


# Compilation settings
include_directories(.)

# Cannot use with modules.
#add_compile_definitions(/FI"jiji/_prelude.hxx")  # global force-include
#target_precompile_headers(jiji-lib PRIVATE jiji/_precompiled.hpp)

add_definitions(-D"JIJI_BUILD_LIBRARY")  # To tell the lib that it is building itself


# Linking dependencies
target_link_libraries(jiji-lib INTERFACE
	libvorbisfile_static
	libvorbis_static
	libogg
	libpng16
	zlib
	d3d9
	dsound
	)
