
# See the build system documentation in IDF programming guide
# for more information about component CMakeLists.txt files.

set(src_dir	

)

set(incl_dir 
			"settings_manager/include"
)		
			
idf_component_register(

	SRCS ${src_dir}
    INCLUDE_DIRS ${incl_dir}
	REQUIRES json
)

