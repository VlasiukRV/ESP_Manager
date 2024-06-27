
# See the build system documentation in IDF programming guide
# for more information about component CMakeLists.txt files.

set(src_dir			
			"src/cppgpio_input.cpp"
			"src/cppgpio_output.cpp"
			"src/threadable.cpp"
)

set(incl_dir "include")		
			
idf_component_register(

	SRCS ${src_dir}
    INCLUDE_DIRS ${incl_dir}
	REQUIRES driver
)

