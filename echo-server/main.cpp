#include <utility>
#include <iostream>
#include <boost/asio.hpp>
#include <glog/logging.h>

void init_glog(char** argv) {
    google::InitGoogleLogging(argv[0]);
    // google::InitGoogleTest(&argc, argv);
    FLAGS_alsologtostderr = 1;
}

int main(int argc, char** argv) {
    init_glog(argv);
    
    using namespace boost::asio;
    
    io_service ioService;
    ip::tcp::endpoint endpoint(ip::tcp::v4(), 12345);

    auto sock = ip::tcp::socket{ioService};
    auto acceptor = ip::tcp::acceptor{ioService, endpoint};


    LOG(INFO) << "Accepting...";
    acceptor.accept(sock);

    char s[256];

    LOG(INFO) << "Reading some...";
    auto data = sock.read_some(buffer(s));


    for (auto c : s) {
        std::cout << c << ' ';
    }

    sock.close();

    return 0;
}