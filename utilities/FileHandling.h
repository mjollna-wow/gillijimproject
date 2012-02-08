#ifndef FILE_HANDLING_H_
#define FILE_HANDLING_H_

#include <vector>
#include <string>

class FileHandling
{
	public:

		FileHandling(const std::string & fileName);
		std::string getFileName();
		std::vector<char> getFullFile();

	private:

		std::string fileName;

};

#endif