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
										"include/Shader.h" "Shader.cpp" 
										"include/Camera.h" "Camera.cpp" 
										"include/CelestialBody.h" "CelestialBody.cpp" 
										"include/Planet.h" "Planet.cpp" 
										"include/Star.h" "Star.cpp" 
										"include/Light.h" "Light.cpp" 
										"include/PointLight.h" "PointLight.cpp" 
										"include/SimpleShader.h" "SimpleShader.cpp"
										"include/Satellite.h" "Satellite.cpp" 
										"include/RevolutionableBody.h" "RevolutionableBody.cpp" 
										"include/ShadowMap.h" "ShadowMap.cpp" 
										"include/Graphic.h" "Graphic.cpp"
										"include/OmniShadowMap.h" "OmniShadowMap.cpp")


# TODO: Add tests and install targets if needed.
target_link_libraries(${CMAKE_PROJECT_NAME}
	glfw
	libglew_static
	assimp)