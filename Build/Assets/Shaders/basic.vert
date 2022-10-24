#version 430 core 

in layout (location = 0) vec3 vposition;
//in layout (location = 1) vec3 vcolor; 
in layout (location = 1) vec2 vtexcoord;
 
out vec3 color;
out vec2 texcoord;

uniform float scale;
uniform mat4 mvp;

void main()
{
	//color = vcolor;
	texcoord = vtexcoord;

	vec4 tposition = mvp * vec4(vposition, 1.0);
	gl_Position = tposition;
}
