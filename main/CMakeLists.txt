
# See the build system documentation in IDF programming guide
# for more information about component CMakeLists.txt files.

set(src_dir  
			"worker_main.cpp"
			"main.cpp"		
)

set(incl_dir 
			"include"
)		
			
idf_component_register(
	
	SRCS ${src_dir}
	
    INCLUDE_DIRS ${incl_dir}
    
    REQUIRES util esp32_driver device state_machine
	# esp_http_server cv_mqtt cv_ota
    
)