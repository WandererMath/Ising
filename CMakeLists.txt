
include_directories(
	C:\\sdk\\glfw-3.3.8.bin.WIN64\\include
	C:\\sdk\\glew-2.1.0\\include
	C:\\sdk\\freeglut\\include
	C:\\sdk\\matplotlib-cpp
	C:\\Users\\Relax\\AppData\\Local\\Programs\\Python\\Python37\\include
	C:\\Users\\Relax\\AppData\\Local\\Programs\\Python\\Python37\\Lib\\site-packages\\numpy\\core\\include
)



link_directories(
		C:\\sdk\\glfw-3.3.8.bin.WIN64\\lib-vc2022
		C:\\Windows\\System32
		C:\\sdk\\glew-2.1.0\\lib\\Release\\x64
		C:\\sdk\\freeglut\\lib
		C:\\Users\\Relax\\AppData\\Local\\Programs\\Python\\Python37\\libs
)

##[[
#add_executable (MC "MC.cpp")
#add_executable( play "play.cpp")
add_executable (MC_Graph "MC_Graph.cpp")#]]
add_executable (Wolff_Graph "Wolff_Graph.cpp")
#add_executable (Wolff "Wolff.cpp")
#add_executable (PhaseTran "PhaseTran.cpp")

target_link_libraries(MC_Graph freeglut.lib)
target_link_libraries(Wolff_Graph freeglut.lib)
#[[
target_link_libraries(MC python37.lib)
target_link_libraries(play python37.lib)

target_link_libraries(Wolff freeglut.lib python37.lib)
target_link_libraries(PhaseTran python37_d.lib)
]]
if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET Wolff_Graph PROPERTY CXX_STANDARD 20)
endif()


