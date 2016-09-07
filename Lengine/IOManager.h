#pragma once

#include <vector>

namespace Lengine{

	class IOManager{
	public:
		static bool readFileToBuffer(std::string filePath, std::vector<unsigned char>& buffer);
	};

}