#ifndef TCPEXAMPLE
#define TCPEXAMPLE

#include <iostream>
#include <cassert>

namespace tcp
{
	class TCPConnection;

	// Abstract base class of all states
	class TCPState
	{
	public:

		// There is a fixed set of requests states can handle, but each state
		// has total freedom in how to handle each request

		// The book does not show, but it appears these functions are given default
		// implementation that may or may not be overridden by concrete states
		// depending on whether the request is relevant to that state
		virtual void transmit(TCPConnection* context, std::ostream& stream);
		virtual void active_open(TCPConnection* context);
		virtual void passive_open(TCPConnection* context);
		virtual void close(TCPConnection* context);
		virtual void synchronize(TCPConnection* context);
		virtual void acknowledge(TCPConnection* context);
		virtual void send(TCPConnection* context);

		// It is also possible to force concrete states to implemement every
		// function by making these pure virtual, but if most states only handle
		// a subset of requests the default approach above may be preferable

		// Pure virtual destructor to ensure that this class is abstract
		virtual ~TCPState() = 0;

	protected:

		void change_state(TCPConnection* context, TCPState* state);
	};

	// The state destructor doesn't do anything in this case, but is required to
	// be defined so that it can be called during the destruction process
	TCPState::~TCPState() = default;


	// The context which provides an interface for clients
	class TCPConnection
	{
	public:

		TCPConnection(bool is_server);

		// The public interface that specifies the requests that can be made
		// It does not implement requests, but forwards them to the active state
		void transmit(std::ostream& stream) { current_state_->transmit(this, stream); };
		void active_open() { current_state_->active_open(this); };
		void passive_open() { current_state_->passive_open(this); };
		void close() { current_state_->close(this); };
		void synchronize() { current_state_->synchronize(this); };
		void acknowledge() { current_state_->acknowledge(this); };
		void send() { current_state_->send(this); };

		bool is_server() { return is_server_; };

	private:

		// To allow only states to access the change_state function
		friend TCPState;

		void change_state(TCPState* state)
		{
			assert(state);

			current_state_ = state;
		}

		// This pointer does not maintain ownership of the state (no new/delete)
		// it is only used to have a changeable reference to the current state
		TCPState* current_state_{};

		bool is_server_{ false };
	};

	// Normally would define this in implementation file to avoid cyclic dependence
	void TCPState::change_state(TCPConnection* context, TCPState* state)
	{
		assert(context);

		context->change_state(state);
	}


	// Concrete States shown in the example

	class TCPEstablished : public TCPState
	{
	public:

		static TCPState* instance();

		virtual void transmit(TCPConnection* context, std::ostream& stream) override;
		virtual void close(TCPConnection* context) override;
	};

	class TCPListen : public TCPState
	{
	public:

		static TCPState* instance();

		virtual void send(TCPConnection* context) override;
	};

	class TCPClosed : public TCPState
	{
	public:

		static TCPState* instance();

		virtual void active_open(TCPConnection* context) override;
		virtual void passive_open(TCPConnection* context) override;
	};

	// Concrete states added to reflect the possible tcp states

	class TCPSynSent : public TCPState
	{
	public:

		static TCPState* instance();

		//virtual void send(TCPConnection* context) override;
	};

	class TCPSynRecieved : public TCPState
	{
	public:

		static TCPState* instance();

		//virtual void send(TCPConnection* context) override;
	};

	class TCPFinWait1 : public TCPState
	{
	public:

		static TCPState* instance();

		//virtual void send(TCPConnection* context) override;
	};

	class TCPFinWait2 : public TCPState
	{
	public:

		static TCPState* instance();

		//virtual void send(TCPConnection* context) override;
	};

	class TCPCloseWait : public TCPState
	{
	public:

		static TCPState* instance();

		//virtual void send(TCPConnection* context) override;
	};

	class TCPClosing : public TCPState
	{
	public:

		static TCPState* instance();

		//virtual void send(TCPConnection* context) override;
	};

	class TCPLastAck : public TCPState
	{
	public:

		static TCPState* instance();

		//virtual void send(TCPConnection* context) override;
	};

	class TCPTimeWait : public TCPState
	{
	public:

		static TCPState* instance();

		//virtual void send(TCPConnection* context) override;
	};

	// All of the handler functions should normally be defined in separate
	// implementation files to avoid cyclical dependencies when changing states
	// There are other methods of chosing the next state to transition to
	// without the current state needing to know the class of the next state
	// such as a lookup table or map but this is how the book example does it

	/* TCPSynSent
	TCPSynRecieved
	TCPFinWait1
	TCPFinWait2
	TCPCloseWait
	TCPClosing
	TCPLastAck
	TCPTimeWait */


	// Established
	void TCPEstablished::transmit(TCPConnection* context, std::ostream& stream)
	{
		assert(context);

		// Do something with the stream
	}

	void TCPEstablished::close(TCPConnection* context)
	{
		assert(context);

		// The example in the book simply transitions directly to Listen
		//change_state(context, TCPListen::instance());

		// In a real connection there are several intermediate steps as mentioned
		// "send FIN, recieve ACK of FIN"

		change_state(context, TCPListen::instance());
	}

	// Listen
	void TCPListen::send(TCPConnection* context)
	{
		assert(context);

		// The example in the book simply transitions directly to Established
		change_state(context, TCPEstablished::instance());

		// In a real connection there are several intermediate steps as mentioned
		// "send SYN, recieve SYN, ACK, etc."

		change_state(context, TCPEstablished::instance());
	}

	// Closed
	void TCPClosed::active_open(TCPConnection* context)
	{
		assert(context);

		// The example in the book simply transitions directly to Established
		change_state(context, TCPEstablished::instance());

		// In a real connection there are several intermediate steps as mentioned
		// "send SYN, recieve SYN, ACK, etc."

		change_state(context, TCPEstablished::instance());
	}

	void TCPClosed::passive_open(TCPConnection* context)
	{
		assert(context);

		// Transition to the listen state to prepare for establishing a connection
		change_state(context, TCPListen::instance());
	}



	void run_tcp_demo()
	{
		std::cout << "Sorry, This demo is a work in progress" << std::endl;
	}


	TCPConnection::TCPConnection(bool is_server)
		: is_server_(is_server)
	{
		// Start in the closed state
		change_state(TCPClosed::instance());
	}

	// The static instance functions could be defined in the header
	// or implementation files without causing cyclic dependency
	// so the choice comes down to conventions

	TCPState* TCPEstablished::instance()
	{
		static TCPEstablished state{};
		return &state;
	}

	TCPState* TCPListen::instance()
	{
		static TCPListen state{};
		return &state;
	}

	TCPState* TCPClosed::instance()
	{
		static TCPClosed state{};
		return &state;
	}

	TCPState* TCPSynSent::instance()
	{
		static TCPSynSent state{};
		return &state;
	}

	TCPState* TCPSynRecieved::instance()
	{
		static TCPSynRecieved state{};
		return &state;
	}

	TCPState* TCPFinWait1::instance()
	{
		static TCPFinWait1 state{};
		return &state;
	}

	TCPState* TCPFinWait2::instance()
	{
		static TCPFinWait2 state{};
		return &state;
	}

	TCPState* TCPCloseWait::instance()
	{
		static TCPCloseWait state{};
		return &state;
	}

	TCPState* TCPClosing::instance()
	{
		static TCPClosing state{};
		return &state;
	}

	TCPState* TCPLastAck::instance()
	{
		static TCPLastAck state{};
		return &state;
	}

	TCPState* TCPTimeWait::instance()
	{
		static TCPTimeWait state{};
		return &state;
	}


	// Default handler implementations to warn the user that a derived state does not implement them

	void TCPState::transmit(TCPConnection* context, std::ostream& stream)
	{
		std::cerr << "Error: current state does not implement TCPState::transmit" << std::endl;
	};

	void TCPState::active_open(TCPConnection* context)
	{
		std::cerr << "Error: current state does not implement TCPState::active_open" << std::endl;
	};

	void TCPState::passive_open(TCPConnection* context)
	{
		std::cerr << "Error: current state does not implement TCPState::passive_open" << std::endl;
	};

	void TCPState::close(TCPConnection* context)
	{
		std::cerr << "Error: current state does not implement TCPState::close" << std::endl;
	};

	void TCPState::synchronize(TCPConnection* context)
	{
		std::cerr << "Error: current state does not implement TCPState::synchronize" << std::endl;
	};

	void TCPState::acknowledge(TCPConnection* context)
	{
		std::cerr << "Error: current state does not implement TCPState::acknowledge" << std::endl;
	};

	void TCPState::send(TCPConnection* context)
	{
		std::cerr << "Error: current state does not implement TCPState::send" << std::endl;
	};
}

#endif
