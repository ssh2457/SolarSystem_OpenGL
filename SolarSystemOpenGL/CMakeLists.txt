# CMakeList.txt : CMake project for SolarSystemOpenGL, include source and define
# project specific logic here.
#

# Add source to this project's executable.
add_executable (${CMAKE_PROJECT_NAME} "main.cpp" 
										"include/Window.h" "Window.cpp" 
										"include/Common.h" 
										"include/SolarSystem.h" "SolarSystem.cpp" 
										"include/Mesh.h" "Mesh.cpp" 
										"include/Texture.h" "Texture.cpp" 
										"include/Model.h" "Model.cpp" 
										"Shader.cpp" "include/Shader.h" 
										"include/Camera.h" "Camera.cpp" 
										"include/SpaceObject.h" "SpaceObject.cpp" 
										"include/RevolutionObject.h" "RevolutionObject.cpp" 
										"include/Star.h" "Star.cpp" "Light.cpp" "include/PointLight.h" "PointLight.cpp")


# TODO: Add tests and install targets if needed.
target_link_libraries(${CMAKE_PROJECT_NAME}
	glfw
	libglew_static
	assimp)