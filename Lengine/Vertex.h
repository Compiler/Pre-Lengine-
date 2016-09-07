#pragma once
/*

Always make a Vertex data size a multiple of 4.. so we may need padding

*/

namespace Lengine{

	struct Color{
		/* Total of 4 bytes */
		GLubyte r;
		GLubyte g;
		GLubyte b;
		GLubyte a;


	};

	struct UV{
		float u;
		float v;
	};

	struct Position{
		/* Total of 8 bytes, 4 bytes per float * 2 floats */
		float x;
		float y;

	};

	struct Vertex{




		Position position;
		Color color;
		UV uv;

		void setColor(GLubyte r, GLubyte g, GLubyte b, GLubyte a){
			color.r = r;
			color.g = g;
			color.b = b;
			color.a = a;
		}

		void setPosition(float x, float y){
			position.x = x;
			position.y = y;
		}
		void setUV(float u, float v){
			uv.u = u;
			uv.v = v;
		}

	};


}