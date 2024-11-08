#pragma once
#include <iostream>
#include <string>
#include "clsDate.h"
#include <queue>
#include <stack>

using namespace std;


class clsQueueLine
{
private:


	string _Prefix;
	short _TotalTickets;
	short _AverageServeTime;

	class clsTicket
	{
	private:
		clsDate _Date;
		short _Number;
		string _Prefix;
		string _TicketTime;
		short _WatingClients = 0;
		short _AverageServeTime = 0;

	public:

		clsTicket(string Prefix, short Number, short AverageServeTime, short WatingClients)
		{
			_Prefix = Prefix;
			_Number = Number;
			_AverageServeTime = AverageServeTime;
			_WatingClients = WatingClients;
			_TicketTime = _Date.GetCurrentDate() + " " + _Date.GetCurrentTime();
		}

		string Prefix()
		{
			return _Prefix;
		}

		short Number()
		{
			return _Number;
		}

		string FullTicketName()
		{
			return _Prefix + to_string(_Number);
		}

		string TicketTime()
		{
			return _TicketTime;
		}

		short WatingClients()
		{
			return _WatingClients;
		}

		short ExpectedServedClient()
		{
			return _WatingClients * _AverageServeTime;
		}

		void PrintTicket()
		{
			cout << "\n\t\t\t  _______________________\n";
			cout << "\n\t\t\t\t    " << FullTicketName();
			cout << "\n\n\t\t\t    " << TicketTime();
			cout << "\n\t\t\t    Wating Clients = " << WatingClients();
			cout << "\n\t\t\t      Serve Time In";
			cout << "\n\t\t\t       " << ExpectedServedClient() << " Minutes.";
			cout << "\n\t\t\t  _______________________\n";

		}

	};

	queue <clsTicket> _QueueLine;

public:

	clsQueueLine(string Prefix, short AverageServeTime)
	{
		_TotalTickets = 0;
		_Prefix = Prefix;
		_AverageServeTime = AverageServeTime;
	}

	string Previx()
	{
		return _Prefix;
	}

	short AverageServeTime()
	{
		return _AverageServeTime;
	}

	short WaitingClients()
	{
		return _QueueLine.size();
	}

	short ServedClients()
	{
		return _TotalTickets - WaitingClients();
	}

	void IssueTicket()
	{
		_TotalTickets++;
		clsTicket Ticket(Previx(), _TotalTickets, AverageServeTime(), WaitingClients());
		_QueueLine.push(Ticket);
	}

	bool ServeNextClient()
	{
		if (_QueueLine.empty()) return false;

		_QueueLine.pop();
		return true;
	}

	void PrintInfo()
	{
		cout << "\n\t\t\t _________________________\n";
		cout << "\n\t\t\t\tQueue Info";
		cout << "\n\t\t\t _________________________\n";
		cout << "\n\t\t\t    Prefix   = " << Previx();
		cout << "\n\t\t\t    Total Tickets   = " << _TotalTickets;
		cout << "\n\t\t\t    Served Clients  = " << ServedClients();
		cout << "\n\t\t\t    Wating Clients  = " << WaitingClients(); ;
		cout << "\n\t\t\t _________________________\n";
		cout << "\n";
	}

	void PrintTicketsLineRTL()
	{
		if (_QueueLine.empty())
			cout << "\n\t\tTickets: No Tickets.";
		else
			cout << "\n\t\tTickets: ";

		queue <clsTicket> _TempTicket = _QueueLine;

		while (!_QueueLine.empty())
		{
			cout << "  " << _QueueLine.front().FullTicketName() << "  <-- ";
			_QueueLine.pop();
		}
		_QueueLine = _TempTicket;
	}

	void PrintTicketsLineLTR()
	{
		if (_QueueLine.empty())
			cout << "\n\t\tTickets: No Tickets.";
		else
			cout << "\n\t\tTickets: ";

		queue <clsTicket> TempQueueLine = _QueueLine;
		stack <clsTicket> TempStackLine;

		while (!_QueueLine.empty())
		{
			TempStackLine.push(_QueueLine.front());
			_QueueLine.pop();
		}

		while (!TempStackLine.empty())
		{
			cout << "   " << TempStackLine.top().FullTicketName() << "  <-- ";
			TempStackLine.pop();
		}
		_QueueLine = TempQueueLine;
	}

	void PrintAllTickets()
	{
		queue <clsTicket> _TempQueueLine = _QueueLine;

		cout << "\n\n\t\t\t       ---Tickets---";

		while (!_QueueLine.empty())
		{
			_QueueLine.front().PrintTicket();
			_QueueLine.pop();
		}
		_QueueLine = _TempQueueLine;
	}

};

