#include "SpriteBatch.h"
#include <algorithm>
namespace Lengine{


	
	//default vertex buffer object and vertex array object id to 0
	SpriteBatch::SpriteBatch() : _vbo(0), _vao(0)
	{



	}







	
	//wrapper
	void SpriteBatch::init(){

		createVertexArray();

	}
	//creates the render batches based on glyphs
	void SpriteBatch::createRenderBatches(){
		std::vector<Vertex> vertices;
		vertices.resize(_glyphs.size() * 6);
		if(_glyphs.empty()){
			return;
		}
		int offset = 0;
		int cv = 0;//current vertice


		_renderBatches.emplace_back(offset, 6, _glyphs[0]->texture);
		vertices[cv++] = _glyphs[0]->topLeft;
		vertices[cv++] = _glyphs[0]->bottomLeft;
		vertices[cv++] = _glyphs[0]->bottomRight;
		vertices[cv++] = _glyphs[0]->bottomRight;
		vertices[cv++] = _glyphs[0]->topRight;
		vertices[cv++] = _glyphs[0]->topLeft;
		offset += 6;
		//current glyph,cg
		for(int cg = 1; cg < _glyphs.size(); cg++){

			if(_glyphs[cg]->texture != _glyphs[cg - 1]->texture)
				_renderBatches.emplace_back(offset, 6, _glyphs[cg]->texture);
			else
				_renderBatches.back().numVertices += 6;


			vertices[cv++] = _glyphs[cg]->topLeft;
			vertices[cv++] = _glyphs[cg]->bottomLeft;
			vertices[cv++] = _glyphs[cg]->bottomRight;
			vertices[cv++] = _glyphs[cg]->bottomRight;
			vertices[cv++] = _glyphs[cg]->topRight;
			vertices[cv++] = _glyphs[cg]->topLeft;
			offset += 6;
		}

		glBindBuffer(GL_ARRAY_BUFFER, _vbo);
		//orphan data
		glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), nullptr, GL_DYNAMIC_DRAW);
		//upload
		glBufferSubData(GL_ARRAY_BUFFER, 0, vertices.size() * sizeof(Vertex), vertices.data());


		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	//assigns attrib arrays
	void SpriteBatch::createVertexArray(){
		if(_vao == 0)
			glGenVertexArrays(1, &_vao);

		glBindVertexArray(_vao);

		if(_vbo == 0)
			glGenBuffers(1, &_vbo);

		glBindBuffer(GL_ARRAY_BUFFER, _vbo);


		//as of right now we only use position so we take the first (0th) index of the array in vertex attribs
		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
		glEnableVertexAttribArray(2);
		//tells opengl this is where we start to draw for position
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));

		glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(Vertex), (void*)offsetof(Vertex, color));

		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, uv));



		glBindVertexArray(0);

	}

	//begins with or without sort type because of defualt vals
	void SpriteBatch::begin(GlyphSortType sortType/* = GlyphSortType::TEXTURE*/){
		_sortType = sortType;
		_renderBatches.clear();
		for(int i = 0; i < _glyphs.size(); i++)
			delete _glyphs[i];
		_glyphs.clear();

	}


	//sorts glyphs and creates render batches
	void SpriteBatch::end(){

		sortGlyphs();
		createRenderBatches();
	}

	
	//now begins to draw everything to the shaders
	void SpriteBatch::draw(const glm::vec4& destRect, const glm::vec4& uvRect, GLuint texture, float depth, const Color& color){
		Glyph* newGlyph = new Glyph;
		newGlyph->texture = texture;
		newGlyph->depth = depth;

		newGlyph->topLeft.color = color;
		newGlyph->topLeft.setPosition(destRect.x, destRect.y + destRect.w);
		newGlyph->topLeft.setUV(uvRect.x, uvRect.y + uvRect.w);

		newGlyph->topRight.color = color;
		newGlyph->topRight.setPosition(destRect.x + destRect.z, destRect.y + destRect.w);
		newGlyph->topRight.setUV(uvRect.x + uvRect.z, uvRect.y + uvRect.w);


		newGlyph->bottomLeft.color = color;
		newGlyph->bottomLeft.setPosition(destRect.x, destRect.y);
		newGlyph->bottomLeft.setUV(uvRect.x, uvRect.y);



		newGlyph->bottomRight.color = color;
		newGlyph->bottomRight.setPosition(destRect.x + destRect.z, destRect.y);
		newGlyph->bottomRight.setUV(uvRect.x + uvRect.z, uvRect.y);


		_glyphs.push_back(newGlyph);

	}

	//sorts glyph based upon type
	void SpriteBatch::sortGlyphs(){
		switch(_sortType){
			
		case GlyphSortType::BACK_TO_FRONT: 
			std::stable_sort(_glyphs.begin(), _glyphs.end(), compareBackToFront);	

			break;

		case GlyphSortType::FRONT_TO_BACK:
			std::stable_sort(_glyphs.begin(), _glyphs.end(), compareFrontToBack);

			break;

		case GlyphSortType::TEXTURE:
			std::stable_sort(_glyphs.begin(), _glyphs.end(), compareTexture);

			break;
		}
		
	
	}
	
	//renders
	void SpriteBatch::renderBatch(){

		glBindVertexArray(_vao);

		for(int i = 0; i < _renderBatches.size(); i++){
			
			glBindTexture(GL_TEXTURE_2D, _renderBatches[i].texture);
			glDrawArrays(GL_TRIANGLES, _renderBatches[i].offset, _renderBatches[i].numVertices);
		}

		glBindVertexArray(0);
	}


	//sort method from front to back
	bool SpriteBatch::compareFrontToBack(Glyph* a, Glyph* b){

		return (a->depth < b->depth);

	}
	//sort method from back to front
	bool SpriteBatch::compareBackToFront(Glyph* a, Glyph* b){


		return (a->depth > b->depth);
	}
	//sort method by texture
	bool SpriteBatch::compareTexture(Glyph* a, Glyph* b){
		

		return (a->texture < b->texture);
	}


	SpriteBatch::~SpriteBatch(){
	}


}
