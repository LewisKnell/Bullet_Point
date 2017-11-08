#include "stdafx.h"
#include <fstream>

#include "ioManager.h"

namespace LKengine {

	bool IOManager::readFileToBuffer(std::string filePath, std::vector<unsigned char>& buffer)
	{
		std::ifstream file(filePath, std::ios::binary);
		if (file.fail())
		{
			perror(filePath.c_str());
			return false;
		}

		//seek to the end
		file.seekg(0, std::ios::end);
		//get the file size
		int fileSize = file.tellg();

		//go back to beginning of file
		file.seekg(0, std::ios::beg);

		//reduce filesize by any header bytes that might be present
		fileSize -= file.tellg();

		buffer.resize(fileSize);

		file.read((char *)&(buffer[0]), fileSize);
		file.close();

		return true;
	}


	bool IOManager::readFileToBuffer(std::string filePath, std::string& buffer)
	{
		std::ifstream file(filePath, std::ios::binary);
		if (file.fail())
		{
			perror(filePath.c_str());
			return false;
		}

		//seek to the end
		file.seekg(0, std::ios::end);
		//get the file size
		int fileSize = file.tellg();

		//go back to beginning of file
		file.seekg(0, std::ios::beg);

		//reduce filesize by any header bytes that might be present
		fileSize -= file.tellg();

		buffer.resize(fileSize);

		file.read((char *)&(buffer[0]), fileSize);
		file.close();

		return true;
	}

}