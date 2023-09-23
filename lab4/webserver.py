# Behnam Dezfouli
# CSEN, Santa Clara University

# This program implements a simple web server that serves html and jpg files

# Input arguments:
# argv[1]: Sever's port number


from socket import *  # Import socket module
import sys            # To terminate the program


if __name__ == "__main__":

    # check if port number is provided
    if len(sys.argv) != 2:
        print ('Usage: python %s <PortNumber>' % (sys.argv[0]))
        sys.exit()
    
    # STUDENT WORK
    servSock = socket(AF_INET, SOCK_STREAM)
    servSock.setsockopt(SOL_SOCKET, SO_REUSEADDR, 1)
    servPort = int(sys.argv[1])
    servSock.bind(("",servPort))

    # Server should be up and running and listening to the incoming connections
    while True:
        print('The server is ready to respond to incoming requests...')

        # STUDENT WORK
        servSock.listen(1)
        connSock, addr = servSock.accept()
        message = str(connSock.recv(1024))
        print(type(message))
        
        file_name = message.split(' ')[1]
        file_name = file_name[1:]
        if (len(file_name.split('.')[1]) < 2):
            raise IOError
        file_exten = file_name.split('.')[1]

        try:

            # STUDENT WORK
            head = 'HTTP/1.1 200 OK\n' 
            head += 'SCU COEN Python Web Server\n'
            
            try:
                f = open(file_name, 'rb')
                outputdata = f.read()
                f.close()
            except Exception:
                f = open('asdf.html', 'rb')
                outputdata = f.read()
                f.close()
                file_exten = 'html'
            
            if (file_exten == 'html'):
                response_headers = { 'Content-Type': 'text/html; encoding=utf8' }
            elif (file_exten == 'jpg'):
                response_headers = { 'Content-Type': 'image/jpeg; encoding=utf8' }
            else:
                print ('Invalid file type, we only support html and jpg!')
                continue
            
            # STUDENT WORK
            head += 'Content-Type: '
            head += str(response_headers['Content-Type'])
            head += 'Content_length: ' + str(len(outputdata))          
            head += '\n\n'
            print(head)
            connSock.send(bytes(head.encode()))
            connSock.send(outputdata)
            connSock.shutdown(SHUT_RDWR)
            connSock.close()

        #Raised when an I/O operation (such as a print statement, the built-in open() function or a method of a file object) fails for an I/O-related reason, e.g., "file not found" or "disk full"
        except IOError:
            # STUDENT WORK
            connSock.shutdown(SHUT_RDWR)
            connSock.close()
            servSock.close()

