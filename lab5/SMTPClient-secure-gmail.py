
# Behnam Dezfouli
#  CSEN, Santa Clara University

# This program implements a simple smtp mail client to send an email to a local smtp server
# the program runs the ping command, and emails the result using smtp.gmail.com

# NOTE: Do not forget to allow login from less secure apps in your gmail account. Otherwise gmail will complain about username and password.


import smtplib, ssl
import subprocess

port = 465  # For SSL
email_address = raw_input("Please enter your email address: ")
password = raw_input("Please enter your password: ")
receiver_email = raw_input("Please enter receiver's email address: ")

# ping google.com and save the result
# STUDENT WORK
ping1 = subprocess.Popen(['ping', '-c', '2', 'google.com'], stdout = subprocess.PIPE)
out, err = ping1.communicate()
print(type(out))

print ('\nNow contacting the mail server...')
# STUDENT WORK
smtp = smtplib.SMTP_SSL('smtp.gmail.com', port)
smtp.login(email_address, password)

print ('\nSending email...')
smtp.sendmail(email_address, receiver_email, out)

# STUDENT WORK


