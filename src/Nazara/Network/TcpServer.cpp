// Copyright (C) 2015 Jérôme Leclercq
// This file is part of the "Nazara Engine - Utility module"
// For conditions of distribution and use, see copyright notice in Config.hpp

#include <Nazara/Network/TcpServer.hpp>
#include <Nazara/Core/CallOnExit.hpp>
#include <Nazara/Core/Error.hpp>
#include <Nazara/Network/TcpClient.hpp>
#include <limits>
#include <Nazara/Network/Debug.hpp>

#if defined(NAZARA_PLATFORM_WINDOWS)
#include <Nazara/Network/Win32/SocketImpl.hpp>
#else
#error Missing implementation: Socket
#endif

namespace Nz
{
	bool TcpServer::AcceptClient(TcpClient* newClient)
	{
		NazaraAssert(m_handle != SocketImpl::InvalidHandle, "Server isn't listening");
		NazaraAssert(newClient, "Invalid client socket");

		IpAddress clientAddress;
		SocketHandle handle = SocketImpl::Accept(m_handle, &clientAddress, &m_lastError);
		if (handle != SocketImpl::InvalidHandle)
		{
			newClient->Reset(handle, clientAddress);
			return true;
		}
		else
			return false;
	}

	SocketState TcpServer::Listen(const IpAddress& address, unsigned int queueSize)
	{
		NazaraAssert(address.IsValid(), "Invalid address");

		Open(address.GetProtocol());

		SocketState state = SocketImpl::Listen(m_handle, address, queueSize, &m_lastError);
		if (state == SocketState_Bound)
			m_boundAddress = SocketImpl::QuerySocketAddress(m_handle);

		ChangeState(state);
		return state;
	}

	void TcpServer::OnClose()
	{
		TcpBase::OnClose();

		m_boundAddress = IpAddress::Invalid;
	}

	void TcpServer::OnOpened()
	{
		TcpBase::OnOpened();

		m_boundAddress = IpAddress::Invalid;
	}
}