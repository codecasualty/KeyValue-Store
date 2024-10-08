#include <iostream>
#include <memory>
#include <string>
#include <thread>
#include "keyvalue.grpc.pb.h"

#include <grpcpp/grpcpp.h>

using grpc::Channel;
using grpc::ClientAsyncResponseReader;
using grpc::ClientContext;
using grpc::CompletionQueue;
using grpc::Status;
using keyvaluestore::Functions;
using keyvaluestore::keyonly;
using keyvaluestore::keyvaluepair;
using keyvaluestore::Reply;
using namespace std;


class Kv_client {
 public:
  explicit Kv_client(std::shared_ptr<Channel> channel)
      : stub_(Functions::NewStub(channel)) {}

  // Assembles the client's payload and sends it to the server.
  std::string GET(const std::string key) {
    // Data we are sending to the server.
    keyonly request;
    keyvaluepair reply;
    request.set_key(key);

    // Call object to store rpc data
    ClientContext context;

    // The producer-consumer queue we use to communicate asynchronously with the
    // gRPC runtime.
    CompletionQueue cq;

    // Storage for the status of the RPC upon completion.
    Status status;

    // stub_->PrepareAsyncSayHello() creates an RPC object, returning
    // an instance to store in "call" but does not actually start the RPC
    // Because we are using the asynchronous API, we need to hold on to
    // the "call" instance in order to get updates on the ongoing RPC.
    std::unique_ptr<ClientAsyncResponseReader<keyvaluepair> > rpc(
        stub_->PrepareAsyncGET(&context, request, &cq));

    // StartCall initiates the RPC call
    rpc->StartCall();

    // Request that, upon completion of the RPC, "reply" be updated with the
    // server's response; "status" with the indication of whether the operation
    // was successful. Tag the request with the integer 1.
    rpc->Finish(&reply, &status, (void*)1);
    void* got_tag;
    bool ok = false;
    // Block until the next result is available in the completion queue "cq".
    // The return value of Next should always be checked. This return value
    // tells us whether there is any kind of event or the cq_ is shutting down.
    GPR_ASSERT(cq.Next(&got_tag, &ok));

    // Verify that the result from "cq" corresponds, by its tag, our previous
    // request.
    GPR_ASSERT(got_tag == (void*)1);
    // ... and that the request was completed successfully. Note that "ok"
    // corresponds solely to the request for updates introduced by Finish().
    GPR_ASSERT(ok);

    // Act upon the status of the actual RPC.
    if (status.ok()) {
      return reply.message();
    } else {
      return "RPC failed";
    }
  }

  std::string PUT(string key,string value) {
    // Data we are sending to the server.
    
    keyvaluepair request;
    Reply reply;
    request.set_key(key);
    request.set_value(value);

    // Call object to store rpc data
    ClientContext context;

    // The producer-consumer queue we use to communicate asynchronously with the
    // gRPC runtime.
    CompletionQueue cq;

    // Storage for the status of the RPC upon completion.
    Status status;

    // stub_->PrepareAsyncSayHello() creates an RPC object, returning
    // an instance to store in "call" but does not actually start the RPC
    // Because we are using the asynchronous API, we need to hold on to
    // the "call" instance in order to get updates on the ongoing RPC.
    std::unique_ptr<ClientAsyncResponseReader<Reply> > rpc(
        stub_->PrepareAsyncPUT(&context, request, &cq));

    // StartCall initiates the RPC call
    rpc->StartCall();
    // Request that, upon completion of the RPC, "reply" be updated with the
    // server's response; "status" with the indication of whether the operation
    // was successful. Tag the request with the integer 1.
    rpc->Finish(&reply, &status, (void*)1);
    void* got_tag;
    bool ok = false;
    // Block until the next result is available in the completion queue "cq".
    // The return value of Next should always be checked. This return value
    // tells us whether there is any kind of event or the cq_ is shutting down.
    GPR_ASSERT(cq.Next(&got_tag, &ok));
    // Verify that the result from "cq" corresponds, by its tag, our previous
    // request.
    GPR_ASSERT(got_tag == (void*)1);
    // ... and that the request was completed successfully. Note that "ok"
    // corresponds solely to the request for updates introduced by Finish().
    GPR_ASSERT(ok);
    if (status.ok()) {
      return reply.message();
    } else {
      return "RPC failed";
    }
  }

  std::string DEL(std::string key) {
    // Data we are sending to the server.
    
    keyonly request;
    Reply reply;
    request.set_key(key);
    

    // Call object to store rpc data
    ClientContext context;

    // The producer-consumer queue we use to communicate asynchronously with the
    // gRPC runtime.
    CompletionQueue cq;

    // Storage for the status of the RPC upon completion.
    Status status;

    // stub_->PrepareAsyncSayHello() creates an RPC object, returning
    // an instance to store in "call" but does not actually start the RPC
    // Because we are using the asynchronous API, we need to hold on to
    // the "call" instance in order to get updates on the ongoing RPC.
    std::unique_ptr<ClientAsyncResponseReader<Reply> > rpc(
        stub_->PrepareAsyncDEL(&context, request, &cq));

    // StartCall initiates the RPC call
    rpc->StartCall();

    // Request that, upon completion of the RPC, "reply" be updated with the
    // server's response; "status" with the indication of whether the operation
    // was successful. Tag the request with the integer 1.
    rpc->Finish(&reply, &status, (void*)1);
    void* got_tag;
    bool ok = false;
    // Block until the next result is available in the completion queue "cq".
    // The return value of Next should always be checked. This return value
    // tells us whether there is any kind of event or the cq_ is shutting down.
    GPR_ASSERT(cq.Next(&got_tag, &ok));

    // Verify that the result from "cq" corresponds, by its tag, our previous
    // request.
    GPR_ASSERT(got_tag == (void*)1);
    // ... and that the request was completed successfully. Note that "ok"
    // corresponds solely to the request for updates introduced by Finish().
    GPR_ASSERT(ok);

    // Act upon the status of the actual RPC.
    if (status.ok()) {
      return reply.message();
    } else {
      return "RPC failed";
    }
  }
  

 private:
  // Out of the passed in Channel comes the stub, stored here, our view of the
  // server's exposed services.
  std::unique_ptr<Functions::Stub> stub_;

  // The producer-consumer queue we use to communicate asynchronously with the
  // gRPC runtime.
  // CompletionQueue cq_;
};

int main(int argc, char** argv) {
  // Instantiate the client. It requires a channel, out of which the actual RPCs
  // are created. This channel models a connection to an endpoint (in this case,
  // localhost at port 50051). We indicate that the channel isn't authenticated
  // (use of InsecureChannelCredentials()).
  Kv_client client(grpc::CreateChannel(
      "localhost:50052", grpc::InsecureChannelCredentials()));

 
  while(1)
  {
    std::string key = "";
    std::string value = "";
    int num;
    cout<<"Select \n1.GET\n2.PUT\n3.DEL\n\nEnter your choice :";

    cin>>num;

    if(num == 1)
    {
      cout<<"\nEnter the Key for the value to be search :";
      cin>>key;
      string reply = client.GET(key);
      cout << "Reply from the server : " << reply << std::endl;
    }
    else if(num == 2)
    {
      cout<<"\nEnter the Key to be insert :";
      cin>>key;
      cout<<"\nEnter the value of the corresponding key :";
      cin>>value;
      string reply = client.PUT(key,value);
      cout << "Reply from the server : " << reply << std::endl;
    }
    else if(num==3)
    {
      cout<<"\nEnter the Key to be delete :";
      cin>>key;
      std::string reply = client.DEL(key);
      cout << "Reply from the server : " << reply << std::endl;
    }
    else{
      cout<<"Enter the correct choice: ";
    }
  }

  return 0;
}