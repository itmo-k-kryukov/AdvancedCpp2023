#include <utility>
#include <boost/asio.hpp>
#include <boost/beast.hpp>
#include <iostream>

namespace asio = boost::asio;
namespace beast = boost::beast;

int main() {
    // Создаем экземпляр io_context
    asio::io_context io_context;

    // Создаем TCP acceptor для приема входящих соединений
    asio::ip::tcp::acceptor acceptor(io_context, asio::ip::tcp::endpoint(asio::ip::tcp::v4(), 12345));

    while (true) {
        // Создаем сокет и ждем входящее соединение
        asio::ip::tcp::socket socket(io_context);
        acceptor.accept(socket);

        // Читаем данные из сокета
        beast::flat_buffer buffer;
        beast::http::request<beast::http::string_body> request;
        beast::http::read(socket, buffer, request);

        // Формируем ответ
        beast::http::response<beast::http::string_body> response;
        response.version(request.version());
        response.result(beast::http::status::ok);
        response.set(beast::http::field::content_type, "text/plain");
        response.body() = "Hello";
        response.prepare_payload();

        // Отправляем ответ
        beast::http::write(socket, response);

        // Закрываем соединение
        socket.shutdown(asio::ip::tcp::socket::shutdown_send);
    }

    return 0;
}