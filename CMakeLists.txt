cmake_minimum_required(VERSION 3.5)
project(wolftest VERSION 1.0.0 LANGUAGES CXX)

add_subdirectory(external)

set(util_sources
	src/util/interval_helpers.h
	src/util/interval_tree.h
)

add_executable(WolfTestBasic
	src/basic.cc
	${util_sources}
)

add_executable(WolfTestAdvanced
	src/advanced.cc
	${util_sources}
)

target_compile_features(WolfTestBasic
	PRIVATE
		cxx_std_17
)

target_compile_features(WolfTestAdvanced
	PRIVATE
		cxx_std_17
)

target_link_libraries(WolfTestBasic
	PRIVATE
		-lstdc++fs
)

target_link_libraries(WolfTestAdvanced
	PRIVATE
		RapidJSON::RapidJSON
		-lstdc++fs
)
