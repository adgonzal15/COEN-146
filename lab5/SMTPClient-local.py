
# Behnam Dezfouli
#  CSEN, Santa Clara University

# This program implements a simple smtp mail client to send an email to a local smtp server

# Note:
# Run a local smtp mail server using the following command before running this code:
# python -m smtpd -c DebuggingServer -n localhost:6000


from socket import *
import ssl


# Choose a mail server
mailserver = 'localhost'


# Create socket called clientSocket and establish a TCP connection with mailserver
# STUDENT WORK
clientSocket = socket(AF_INET, SOCK_STREAM)

# Port number may change according to the mail server
# STUDENT WORK
print("connecting to server")
clientSocket.connect((mailserver, 6000))

recv = clientSocket.recv(1024).decode()
print(recv)
if recv[:3] != '220':
    print('220 reply not received from server.')


# Send HELO command along with the server address
# STUDENT WORK
sendMsg = "HELO " + 'localhost.com' + '\r\n'
clientSocket.send(sendMsg.encode())

recv = clientSocket.recv(1024).decode()
print(recv)
if recv[:3] != '250':
    print('250 reply not received from server.')

# Send MAIL FROM command and print server response
# STUDENT WORK
sendMsg = "MAIL FROM: " + 'test@localhost.com' + '\r\n'
clientSocket.send(sendMsg.encode())

recv = clientSocket.recv(1024).decode()
print(recv)
if recv[:3] != '250':
    print('250 reply not received from server.')

# Send RCPT TO command and print server response
# STUDENT WORK
sendMsg = "RCPT TO: " + 'tester@localhost.com' + '\r\n'
clientSocket.send(sendMsg.encode())

recv = clientSocket.recv(1024).decode()
print(recv)
if recv[:3] != '250':
    print('250 reply not received from server.')

# Send DATA command and print server response
# STUDENT WORK
sendMsg = 'DATA\r\n'
clientSocket.send(sendMsg.encode())

recv = clientSocket.recv(1024).decode()
print(recv)
if recv[:3] != '354':
    print('354 reply not received from server.')


# Send message data.
# STUDENT WORK

# Message to send
# STUDENT WORK
sendMsg = "SUBJECT: Greeting To you!\n"
clientSocket.send(sendMsg.encode())
sendMsg = "This is line 1\n"
clientSocket.send(sendMsg.encode())
sendMsg = "This is line 2"
clientSocket.send(sendMsg.encode())

# Message ends with a single period
# STUDENT WORK
sendMsg = "."
clientSocket.send(sendMsg.encode())


# Send QUIT command and get server response
# STUDENT WORK
sendMsg = '\r\n.\r\n'
clientSocket.send(sendMsg.encode())

recv = clientSocket.recv(1024).decode()
print(recv)
if recv[:3] != '250':
    print('250 reply not received from server.')

clientSocket.close()
