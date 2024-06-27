
# See the build system documentation in IDF programming guide
# for more information about component CMakeLists.txt files.

set(src_dir	
			"state_machine_common/src/state_machine.cpp"
)

set(incl_dir 
			"state_machine_common/include"
)		
			
idf_component_register(

	SRCS ${src_dir}
    INCLUDE_DIRS ${incl_dir}
    REQUIRES util device
			
)
