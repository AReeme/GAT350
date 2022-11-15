#version 430 core
 
#define POINT		0
#define DIRECTIONAL	1
#define SPOTLIGHT	2
#define MAX_LIGHTS  5

in vec3 position;
in vec2 texcoord;
in mat3 tbn;
 
out vec4 fcolor;

uniform struct Light
{
	int type; 
	vec3 color;
	vec4 position;
	vec3 direction;
	float cutoff;
	float exponent;
} lights[MAX_LIGHTS];
 
uniform struct Material
{
	vec3 color;
	float shininess;
	vec2 uv_tiling;
	vec2 uv_offset;
} material;

uniform int light_count;
uniform vec3 ambient_color;

layout (binding = 0) uniform sampler2D diffuseMap; //diffuse map
layout (binding = 1) uniform sampler2D normalMap; //specular map
layout (binding = 2) uniform sampler2D emissiveMap; //emissive map

void phong(vec3 position, vec3 normal, Light light, out vec3 diffuse, out vec3 specular)
{
    // direction vector to light
	// calculate light direction (unit vector)
	vec3 light_dir = (light.type == DIRECTIONAL) ? normalize(-light.direction) : normalize(vec3(light.position) - position);
 
	// if spotlight, compute intensity based on angle to cutoff
	float spot_intensity = 1;
	if (light.type == SPOTLIGHT)
	{
		// get cosine of light direction and direction vector from light
		float cosine = dot(light.direction, -light_dir);
		// get angle
		float angle = acos(cosine);
 
		// if inside of cutoff, set spot intensity
		spot_intensity = (angle < light.cutoff) ? pow(cosine, light.exponent) : 0;
	}
 
	// DIFFUSE
	// calculate light intensity with dot product (normal * light direction)
	float intensity = max(dot(light_dir, normal), 0) * spot_intensity;
	// calculate diffuse color
	diffuse = light.color * material.color * intensity;
 
	// SPECULAR
	if (intensity > 0)
	{
		// calculate reflection vector 
		// light direction reflected around normal vector [ \|/ ]
		vec3 reflection = reflect(-light_dir, normal);
		// create direction vector from eye (origin) to vertex position
		vec3 view_dir = normalize(-vec3(position));
		// calculate light intensity with dot production (reflection * view direction)
		intensity = max(dot(reflection, view_dir), 0);
		
		intensity = pow(intensity, material.shininess);
		// calculate specular color
		specular = light.color * material.color * intensity;
	}
 
}
 
void main()
{
    //ambient
    vec3 diffuse = vec3(0);
    vec3 specular = vec3(0);
    vec2 ttexcoord = (texcoord * material.uv_tiling) +  material.uv_offset;

    vec3 normal = texture(normalMap, ttexcoord).rgb; // 0 - 1
    normal = (normal * 2) - 1;// (0 - 1) -> ( -1 - 1)
    normal = normalize(tbn * normal);

    // calculate phong (diffuse, specular) for each light and add to color 
	 for (int i = 0; i < light_count; i++) 
	 { 
		vec3 dif; 
		vec3 spec;
		
		phong(position, normal, lights[i], dif, spec); 

		diffuse += dif;
		specular += spec;
	 } 

    vec4 texture_Color = texture(diffuseMap, ttexcoord);

    //fcolor = texture_Color;
    fcolor = vec4(ambient_color + diffuse, 1) * texture_Color + vec4(specular, 1);

}