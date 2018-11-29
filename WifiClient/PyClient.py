import sys
import socket
from urlparse import urlparse
import re

def http_checker():
	#input format check
	http_check = "http://"
	i = 0;
	for letter in http_check:	
		if (letter != sys.argv[1][i]):
			print "ERR 3: \r\n URL input must begin with 'http://'"
			sys.exit(3)
		i = i + 1;
	return

def parse_url(url):
	o = urlparse(url)
	if (o.scheme == "https"):
		print "ERR 1: \r\n Cannot Redirect to HTTPS://'"
		sys.exit(1)
	return o

def recv_body(socket, o):
	if (not o.path):
		path = '/'
	else:
		path = o.path

	if (end):
		return

	if (o.port):
		hostname = o.netloc.split(":")[0]+':'+str(o.port)
	else:
		hostname = o.netloc

	socket.sendall("GET {} HTTP/1.0\r\nHost: {}\r\n\r\n " .format(path, hostname)) 
	data = socket.recv(1024)
	tagline = ""
	for x in range(9,13):
		tagline += data[x]

	tagline = int(tagline)
	if (tagline >= 400):
		print "ERR 4: \r\n HTTP Response >= 400"
		sys.exit(4)
	body = ""
	while (len(data) > 0):	
		body += data
		data = socket.recv(1024)

	socket.close	
	return body

def check_content_type(body):
	header = body.split("\r\n\r\n")[0]
	header_tags = header.split("\r\n")

	for header in header_tags:
		if ("Content-Type: " in header):
			content_type = header.split(": ")[1]
			content_type = content_type.split(";")[0]
			if (content_type == "text/html"): #content_type == "text/html"
				ret = 1
			else:
				print "ERR 1: \r\n Content must be of type 'text/html'"
				ret = 0
				sys.exit(1)
	return ret

def check_redirect(body):
	header = body.split("\r\n\r\n")[0]
	header_tags = header.split("\r\n")
	redirect_s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
	end = 1

	o = parse_url("http:/google.com")
	for header in header_tags:
		if ("Location: " in header):
			website = header.split(": ")[1]
			sys.stderr.write("redirecting to: %s" % website)
			print '\n'
			end = 0
			o = parse_url(website)
			redirect_s.connect((o.netloc, 80))
			global redirects
			redirects += 1
			print "Num redirects: " + str(redirects)
	return (redirect_s, o, end)


#input format check
http_checker()
		
#parse input and connect
s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
o = parse_url(sys.argv[1])

if (o.port):
	deez = o.netloc.split(":")[0]
	s.connect((deez, o.port))
else:
	s.connect((o.netloc, 80))


end = 0
body = recv_body(s, o)
redirects = 0
while (not end):
	if (check_content_type(body)):
		print body
		s, o, end = check_redirect(body)
		body = recv_body(s, o)
	if redirects >= 10:
		print "ERR 5: \r\n Greater than 10 redirects"
		sys.exit(5) 



print "0: success"
sys.exit(0)