aux_source_directory(${CMAKE_CURRENT_LIST_DIR} DIR_SRCS)
add_executable(testClient ${DIR_SRCS})
target_link_libraries(testClient ws2_32)

install(TARGETS testClient  
		RUNTIME DESTINATION ${PROJECT_SOURCE_DIR}/bin)