# TCP Server Application

A TCP server built in C using BSD sockets. Tested against a client binary provided by the course.

## Features
- TCP connection over IPv4 using socket, bind, listen, accept
- Receives client messages and sends a response
- Error handling at each system call
- Successfully compiled and tested end-to-end

## Files
- server.c : TCP server implementation (my code)
- makefile : build automation (my code)

## How to Compile
Run: make

Or manually: gcc -o server server.c

## How to Run
Run the server: ./server 8080

Then connect with any TCP client (like netcat): nc 127.0.0.1 8080

## What I Learned
- BSD socket API and TCP connection lifecycle
- Server-side socket programming: bind, listen, accept, recv, send
- Error handling in network programming
- Build automation with Makefiles
