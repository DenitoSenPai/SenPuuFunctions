// ConsoleApplication1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

//#include "stdafx.h"
#include <tchar.h>
#include <Windows.h>

#include "EASendMailObj.tlh"
using namespace EASendMailObjLib;

const int ConnectNormal = 0;
const int ConnectSSLAuto = 1;
const int ConnectSTARTTLS = 2;
const int ConnectDirectSSL = 3;
const int ConnectTryTLS = 4;

int _tmain(int argc, _TCHAR* argv[])
{
    ::CoInitialize(NULL);

    IMailPtr oSmtp = NULL;
    oSmtp.CreateInstance(__uuidof(EASendMailObjLib::Mail));
    oSmtp->LicenseCode = _T("TryIt");

    // Set your gmail email address
    oSmtp->FromAddr = _T("myemail@gmail.com");

    // Add recipient email address
    oSmtp->AddRecipientEx(_T("recipientemail@gmail.com"), 0);

    // Set email subject
    oSmtp->Subject = _T("Email Subject");

    // Set email body
    oSmtp->BodyText = _T("Email Body");

    // Gmail SMTP server address
    oSmtp->ServerAddr = _T("smtp.gmail.com");

    // Gmail user authentication should use your
    // Gmail email address as the user name.
    // For example: your email is "gmailid@gmail.com", then the user should be "gmailid@gmail.com"
    oSmtp->UserName = _T("myemail@gmail.com");
    oSmtp->Password = _T("myEmailPassword");

    // If you want to use direct SSL 465 port,
    // Please add this line, otherwise TLS will be used.
    // oSmtp->ServerPort = 465;

    // Set 25 or 587 SMTP port
    oSmtp->ServerPort = 587;

    // detect SSL/TLS automatically
    oSmtp->ConnectType = ConnectSSLAuto;

    _tprintf(_T("Start to send email via gmail account ...\r\n"));

    if (oSmtp->SendMail() == 0)
    {
        _tprintf(_T("email was sent successfully!\r\n"));
    }
    else
    {
        _tprintf(_T("failed to send email with the following error: %s\r\n"),
            (const TCHAR*)oSmtp->GetLastErrDescription());
    }

    return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
