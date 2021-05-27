#include <boost/asio/io_context.hpp>
#include <boost/asio/ssl/context.hpp>
#include <boost/asio/ssl/stream.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/connect.hpp>
#include <boost/beast/http/write.hpp>
#include <boost/beast/http/read.hpp>
#include <boost/beast/http/string_body.hpp>
#include <boost/beast/version.hpp>
#include <boost/beast/core.hpp>
#include <boost/beast/http/dynamic_body.hpp>
#include "Https.h"

std::string https::HttpsHelper::get(const char *host, const char *target)
{
	try {
		boost::asio::io_context ioc;
		boost::asio::ssl::context ctx(boost::asio::ssl::context::sslv23_client);
		boost::asio::ip::tcp::resolver resolver(ioc);
		
		boost::asio::ssl::stream<boost::asio::ip::tcp::socket> stream(ioc, ctx);
		boost::asio::connect(stream.next_layer(), resolver.resolve(host, "443"));

		stream.handshake(boost::asio::ssl::stream_base::client);
		{
			boost::beast::http::request<boost::beast::http::string_body>
				req(boost::beast::http::verb::get, target, 11);

			req.set(boost::beast::http::field::host, host);
			req.set(boost::beast::http::field::user_agent, BOOST_BEAST_VERSION_STRING);

			boost::beast::http::write(stream, req);
		}
		
		boost::beast::http::response<boost::beast::http::dynamic_body> res;
		{
			boost::beast::flat_buffer buffer;
			boost::beast::http::read(stream, buffer, res);
		}
		{
			boost::beast::error_code ec;

			stream.lowest_layer().shutdown(boost::asio::ip::tcp::socket::shutdown_both, ec);
			stream.shutdown(ec);
		}
		
		return boost::beast::buffers_to_string(res.body().data());
	} catch (const std::exception &e) { throw e; }
}

#pragma region HTTP
/*
	boost::asio::io_context ioc;
	boost::asio::ip::tcp::socket socket(ioc);
	boost::asio::ip::tcp::resolver resolver(ioc);

	boost::asio::connect(socket, resolver.resolve(host, "80"));
	{
		boost::beast::http::request<boost::beast::http::string_body>
			req(boost::beast::http::verb::get, target, 11);

		req.set(boost::beast::http::field::host, host);
		req.set(boost::beast::http::field::user_agent, BOOST_BEAST_VERSION_STRING);

		boost::beast::http::write(socket, req);
	}

	boost::beast::http::response<boost::beast::http::dynamic_body> res;
	{
		boost::beast::flat_buffer buffer;
		boost::beast::http::read(socket, buffer, res);
		response = boost::beast::buffers_to_string(res.body().data());
	}

	socket.shutdown(boost::asio::ip::tcp::socket::shutdown_both);

	return boost::beast::buffers_to_string(res.body().data());
*/
#pragma endregion