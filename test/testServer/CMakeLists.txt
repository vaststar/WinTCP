#contain srcs
include_directories(${PROJECT_SOURCE_DIR}/include)
include_directories(${CMAKE_CURRENT_LIST_DIR})
aux_source_directory(${CMAKE_CURRENT_LIST_DIR} DIR_SRCS)

file(GLOB_RECURSE HEAD_RES "*.h")
source_group("include" FILES ${HEAD_RES})

#build exe
add_executable(testServer ${DIR_SRCS} ${HEAD_RES})

target_link_libraries(testServer ${PROJECT_SOURCE_DIR}/lib/WinBaseServer.lib ws2_32)

install(TARGETS testServer  
		RUNTIME DESTINATION ${PROJECT_SOURCE_DIR}/bin)