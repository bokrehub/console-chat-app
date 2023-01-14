#include <iostream>
#include <string>
#include <boost/asio.hpp>
#include <boost/bind.hpp>

using boost::asio::ip::udp;

const int PORT = 33000;
const int BUF_SIZE = 1024;

class ChatClient {
public:
    ChatClient(boost::asio::io_service& io_service) :
        socket_(io_service, udp::endpoint(udp::v4(), PORT)) {
        start_receive();
    }

    void send(const std::string& host, const std::string& message) {
        udp::resolver resolver(socket_.get_io_service());
        udp::resolver::query query(udp::v4(), host, std::to_string(PORT));
        udp::resolver::iterator iter = resolver.resolve(query);
        socket_.send_to(boost::asio::buffer(message), *iter);
    }

    void receive() {
        socket_.async_receive_from(
            boost::asio::buffer(recv_buf_), remote_endpoint_,
            boost::bind(&ChatClient::handle_receive, this,
            boost::asio::placeholders::error,
            boost::asio::placeholders::bytes_transferred));
    }

    void handle_receive(const boost::system::error_code& error,
        std::size_t bytes_transferred) {
        if (!error) {
            std::cout << "Received: " << recv_buf_ << std::endl;
            start_receive();
        }
    }

    void start_receive() {
        socket_.async_receive_from(
            boost::asio::buffer(recv_buf_), remote_endpoint_,
            boost::bind(&ChatClient::handle_receive, this,
            boost::asio::placeholders::error,
            boost::asio::placeholders::bytes_transferred));
    }

private:
    udp::socket socket_;
    udp::endpoint remote_endpoint_;
    char recv_buf_[BUF_SIZE];
};

int main() {
    boost::asio::io_service io_service;
    ChatClient client(io_service);
    std::string host, message;

    std::cout << "Enter hostname: ";
    std::getline(std::cin, host);

    while (true) {
        std::cout << "Enter message (or 'exit' to quit): ";
        std::getline(std::cin, message);

        if (message == "exit")
            break;

        client.send(host, message);
    }

    return 0;
}
