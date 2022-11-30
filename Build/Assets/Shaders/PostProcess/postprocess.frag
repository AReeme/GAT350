#version 430 core 
  
in vec2 texcoord; 
  
out vec4 fcolor; 
  
const float screen_height = 600.0; 
  
uniform sampler2D textureMap; 
  
void main() 
{ 
	 vec3 color = texture(textureMap, texcoord).rgb; 
 
	 // get the screen y position (uv coordinates range 0 <-> 1) 
	 int y = int(texcoord.y * screen_height); 
	 // set the alpha based on the modulus of the y position 
	 float alpha = (y % 3 != 0) ? 1 : 0; 
 
	 fcolor = vec4(color, alpha); 
} 