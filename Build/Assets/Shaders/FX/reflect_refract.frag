#version 430 core

in vec3 reflection_dir;
in vec3 refraction_dir;

out vec4 fcolor;

uniform samplerCube cubeMap;
uniform float interpolation;

void main()
{
	vec3 reflect_color = texture(cubeMap, reflection_dir).rgb;
	vec3 refract_color = texture(cubeMap, refraction_dir).rgb;

	vec3 color = mix(reflect_color, refract_color, interpolation); 
	fcolor = vec4(color, 1);
	// set fragment color
}
