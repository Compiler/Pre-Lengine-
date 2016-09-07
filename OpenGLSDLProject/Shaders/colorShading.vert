#version 130

in vec2 vertexPosition;
in vec4 vertexColor;
in vec2 vertexUV;

//out sends to frag when named the same and in vertex shader
out vec4 fragmentColor;
out vec2 fragmentPosition;
out vec2 fragmentUV;

uniform mat4 cameraMatrix;

void main(){

	
	//Assigns position
	gl_Position.xy = (cameraMatrix * vec4(vertexPosition, 0.0, 1.0)).xy;
	//gl_Position.xy = vec2(1,1);
	
	//Defaults the z coordinate
	gl_Position.z = 0.0;
	
	//Says that the coordinates ARE normalized
	gl_Position.w = 1.0;
	
	fragmentPosition = vertexPosition;
	
	//sets it to input then sends it out to fragment shader
	fragmentColor = vertexColor;
	
	fragmentUV = vec2(vertexUV.x, 1 - vertexUV.y);
	
	
}