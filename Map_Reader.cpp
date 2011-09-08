#include "Map_Reader.h"
#
void MapReader::loadFile(const string& file_name)
{
	infile.open(file_name.c_str());
	if ( !infile )
		throw FileCannotBeOpened();
}

void MapReader::readInFile(Map& file_receiver)
{
	string text_line;

	while (getline( infile, text_line, '\n' ))
	{
		file_receiver.add_row(text_line);
	}
}
