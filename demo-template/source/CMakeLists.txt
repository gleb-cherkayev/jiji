file(GLOB_RECURSE JIJI_DEMO_TEMPLATE_SOURCE
	CONFIGURE_DEPENDS
	./*.?pp
	./*.?xx)
source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}" FILES ${JIJI_DEMO_TEMPLATE_SOURCE})
add_executable(jiji-demo-template ${JIJI_DEMO_TEMPLATE_SOURCE})
jiji_configure_executable(jiji-demo-template)


# library dependency
target_link_libraries(jiji-demo-template jiji-lib)
