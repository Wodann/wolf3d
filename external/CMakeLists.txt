# Wrap rapidjson in a target
add_library(RapidJSON::RapidJSON INTERFACE IMPORTED GLOBAL)
set_target_properties(RapidJSON::RapidJSON
	PROPERTIES
		INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_CURRENT_SOURCE_DIR}/rapidjson/include"
)