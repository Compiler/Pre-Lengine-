#include "IOManager.h"
#include <fstream>


namespace Lengine{


	//takes info and loads it to the buffer given by reference
	bool IOManager::readFileToBuffer(std::string filePath, std::vector<unsigned char>& buffer){

		//read in binary 
		std::ifstream file(filePath, std::ios::binary);

		if(file.fail()){
			perror(filePath.c_str());
			return false;
		}

		//go to end of file, offest 0 bytes from end of file
		file.seekg(0, std::ios::end);

		//get size, tellg returns how many bytes we have gone through,
		//we started at the end so it gives us the full size ya dumb ass
		int fileSize = file.tellg();

		//seek to the beginning
		file.seekg(0, std::ios::beg);

		//for safety, get rid of header
		fileSize -= file.tellg();

		//resize our buffer to the filesize
		buffer.resize(fileSize);

		file.read((char *)&(buffer[0]), fileSize);

		file.close();

		return true;
	}
}
