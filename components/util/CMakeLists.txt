
# See the build system documentation in IDF programming guide
# for more information about component CMakeLists.txt files.

set(src_dir	
	"string/string.cpp"
)

set(incl_dir 
			"."
			"string"
			"colections"
)		
			
idf_component_register(

	SRCS ${src_dir}
    INCLUDE_DIRS ${incl_dir}
)

