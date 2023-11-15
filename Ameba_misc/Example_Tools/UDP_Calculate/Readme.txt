This is the guide of MacOS, Linux or Windows OS user to compile the tool of the 3 UDP calculate examples.

Users can use the existing tools in this folders directly.

Pre-request
    For Windows OS user, please download and install MIGW64/CYGWIN for "g++" environment.

Compile the tools
    Open the terminal(or git bash/cygwin terminal), then apply the following commands. $strip is optional.
    ### strip SendDelay_win.exe
    ### strip SendDelay_linux
    ### strip SendDelay_mac

    g++.exe SendDelay.cpp ../../Ameba_Icon/ico-out.o -o SendDelay_win.exe -lwsock32
    g++ SendDelay.cpp -o SendDelay_linux
    g++ SendDelay.cpp -o SendDelay_mac

    g++.exe ReceiveDelay.cpp ../../Ameba_Icon/ico-out.o -o ReceiveDelay_win.exe -lwsock32
    g++ ReceiveDelay.cpp -o ReceiveDelay_linux
    g++ ReceiveDelay.cpp -o ReceiveDelay_mac

    g++.exe ReceiveTimeout.cpp ../../Ameba_Icon/ico-out.o -o ReceiveTimeout_win.exe -lwsock32
    g++ ReceiveTimeout.cpp -o ReceiveTimeout_linux
    g++ ReceiveTimeout.cpp -o ReceiveTimeout_mac

Use the tools
    Open the terminal(or git bash/cygwin terminal), then apply the following commands.

    ./ReceiveTimeout_win.exe <client IP address>
    ./ReceiveDelay_win.exe <client IP address>
    ./SendDelay_win.exe

    ./ReceiveDelay_linux <client IP address>
    ./ReceiveTimeout_linux <client IP address>
    ./SendDelay_linux

    ./ReceiveDelay_mac <client IP address>
    ./ReceiveTimeout_mac <client IP address>
    ./SendDelay_mac
