
# See the build system documentation in IDF programming guide
# for more information about component CMakeLists.txt files.

set(src_dir	
			"device_common/src/device.cpp"		
			"device_common/src/device_executive.cpp"
			"device_common/src/device_factory.cpp"
			
			"device_led/src/led.cpp"
)

set(incl_dir 
			"device_common/include"
			
			"device_led/include"
)		
			
idf_component_register(

	SRCS ${src_dir}
    INCLUDE_DIRS ${incl_dir}
	REQUIRES esp32_driver
)

