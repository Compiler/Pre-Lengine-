#version 130


//in takes in from vertex shader when in fragment shader
in vec4 fragmentColor;	
in vec2 fragmentPosition;
in vec2 fragmentUV;

out vec4 color;

uniform sampler2D tex;

void main(){



	vec4 texCol = texture(tex, fragmentUV);
	color = texCol * fragmentColor;
	
	

}