add_definitions(-DWINBASESERVER_LIB )
include_directories(${CMAKE_CURRENT_LIST_DIR}/include)
aux_source_directory(${CMAKE_CURRENT_LIST_DIR}/src SRC)

file(GLOB_RECURSE HEAD_RES "include/*.h")
source_group("include" FILES ${HEAD_RES})

add_library(WinBaseServer SHARED  ${SRC} ${HEAD_RES})
target_link_libraries(WinBaseServer ws2_32)
install(FILES ${HEAD_RES} DESTINATION ${PROJECT_SOURCE_DIR}/include/WinBaseServer)
install(TARGETS WinBaseServer  
		RUNTIME DESTINATION ${PROJECT_SOURCE_DIR}/bin
		LIBRARY DESTINATION ${PROJECT_SOURCE_DIR}/lib
		ARCHIVE DESTINATION ${PROJECT_SOURCE_DIR}/lib)
