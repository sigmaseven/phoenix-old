#include "./help.h"
#include "./util.h"

std::string Help::getHelp(std::string topic)
{
	std::stringstream file_name;
	std::string file_content;

	Util::checkDirectory("./help");

	file_name << "./help/" << topic << ".txt";
	file_content = Util::readFromFile(file_name.str().c_str());

	return file_content;
}
