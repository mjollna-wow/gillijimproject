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
		void toBinFile(const std::vector<char> & binData);

	private:

		std::string fileName;

};

#endif