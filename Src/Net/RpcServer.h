#ifndef NET_RPC_SERVER_H
#define NET_RPC_SERVER_H
#include "base/base.h"

namespace Hainan {

class RpcServer: public boost::enable_shared_from_this<RpcServer>
{
private:
	typedef boost::unordered_set<RpcSessionPtr> RpcSessionSet;
	google::protobuf::Service& service;
	boost::asio::io_service io_service;
	boost::asio::ip::tcp::acceptor acceptor;
	ThreadPool thread_pool;
	RpcSessionSet sessions;

	void RpcServer::Callback(RpcSessionPtr session,
			boost::function<void (RpcSessionPtr, RpcResponsePtr)> handler);

public:
	RpcServer(google::protobuf::Service& pservice, int port);
	~RpcServer();
	void Start();
	void Stop();

	void RunService(RpcSessionPtr session, RpcRequestPtr request,
			boost::function<void (RpcSessionPtr, RpcResponsePtr)> handler);
};

} // namespace Hainan

#endif // NET_RPC_SERVER_H
