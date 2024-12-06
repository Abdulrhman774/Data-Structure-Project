#include <iostream>
#include "clsQueueLine.h"

using namespace std;

int main()
{

    clsQueueLine PayBillsQueue("A0", 10); // Constuctor must take prefix and المدة المتوقعة بالدقائق لخدمة كل العميل

    PayBillsQueue.IssueTicket(); // إصدرلي تيكيت
    PayBillsQueue.IssueTicket(); // إصدرلي تيكيت
    PayBillsQueue.IssueTicket(); // إصدرلي تيكيت
    PayBillsQueue.IssueTicket(); // إصدرلي تيكيت
    PayBillsQueue.IssueTicket(); // إصدرلي تيكيت

    cout << "\nPay Bills Queue Info:\n";
    PayBillsQueue.PrintInfo();/*
    Pay Bills Queue Info:

                         _________________________

                                Queue Info
                         _________________________

                            Prefix   = A0
                            Total Tickets   = 5
                            Served Clients  = 0
                            Wating Clients  = 5
                         _________________________
     */



    PayBillsQueue.PrintTicketsLineRTL(); //Tickets:  A01 <--  A02 <--  A03 <--  A04 <--  A05 <--
    PayBillsQueue.PrintTicketsLineLTR(); //Tickets:  A05 -->  A04 -->  A03 -->  A02 -->  A01 -->



    PayBillsQueue.PrintAllTickets();/*
         ---Tickets---
                          _______________________

                                    A01

                            6/12/2024 20:39:2
                            Wating Clients = 0
                              Serve Time In
                               0 Minutes.
                          _______________________

                          _______________________

                                    A02

                            6/12/2024 20:39:2
                            Wating Clients = 1
                              Serve Time In
                               10 Minutes.
                          _______________________

                          _______________________

                                    A03

                            6/12/2024 20:39:2
                            Wating Clients = 2
                              Serve Time In
                               20 Minutes.
                          _______________________

                          _______________________

                                    A04

                            6/12/2024 20:39:2
                            Wating Clients = 3
                              Serve Time In
                               30 Minutes.
                          _______________________

                          _______________________

                                    A05

                            6/12/2024 20:39:2
                            Wating Clients = 4
                              Serve Time In
                               40 Minutes.
                          _______________________
*/

    PayBillsQueue.ServeNextClient();
    cout << "\nPay Bills Queue After Serving One client\n"; // هنا زي ما حد دوره بيخلص فلو كانو 5 بيبقوا اربعه وكده
    PayBillsQueue.PrintInfo(); /*Pay Bills Queue After Serving One client

                         _________________________

                                Queue Info
                         _________________________

                            Prefix   = A0
                            Total Tickets   = 5
                            Served Clients  = 1
                            Wating Clients  = 4
                         _________________________
*/




//****----------------------------------------------------------------------****\\

    clsQueueLine SubscriptionsQueue("B0", 5);


    cout << "\nSubscriptions Queue Info:\n";

    SubscriptionsQueue.IssueTicket();
    SubscriptionsQueue.IssueTicket();
    SubscriptionsQueue.IssueTicket();


    SubscriptionsQueue.PrintInfo();

    SubscriptionsQueue.PrintTicketsLineRTL();
    SubscriptionsQueue.PrintTicketsLineLTR();

    SubscriptionsQueue.PrintAllTickets();

    SubscriptionsQueue.ServeNextClient();
    cout << "\nSubscriptions Queue After Serving One client\n";
    SubscriptionsQueue.PrintInfo();


    return 0;
}
