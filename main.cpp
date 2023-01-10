#include <iostream>
#include <string>
#include <boost/asio.hpp>
#include <boost/serialization/vector.hpp>
#include <boost/serialization/string.hpp>

using namespace boost::asio;
using namespace boost::asio::ip;

const int BUFFER_SIZE=1024;

class Message{
	public:
	std::string sendr;
	std::string msg;
};


// serializing the message object;
template <typename Archive>
void serialize(Arhive& ar, Message& msg, const unsigned int version){
	ar & m.sendr;
	ar & m.content;
}

//client class to represent each connected client;



int main(int argc, char *argv[])
{
	std::cout << "Hello world!" << std::endl;
}