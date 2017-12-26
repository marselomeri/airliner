\mainpage Software Architecture


OVERVIEW
========

This page documents the software architecture for ground control system also called commander. The commander is a web-based application which allows users to interact with the flight software. Flight software deals will a large spectrum of telemetry and commanding. The commander application makes it convenient for the end users to observe telemetry and send commanding signals to the flight software in real time. Additionally, it also has features such as live video streaming, Air traffic monitoring, and native console logging. The web application is written in python and maintained with Django framework.

SPECIFICATION DETAILS
======================

The commander architecture has the following specifications.
DJANGO - A widely popular, fast, fully loaded, secure and scalable framework called Django is used. Because Django was developed in a fast-paced newsroom environment, it was designed to make common Web-development tasks fast and easy. Django is a python based framework and requires python interpreter to work. Django is supported in python 2.x.y and python 3.x.y. We shall use Django 1.10.2 with python 2.7.12.
ASGI (Asynchronous Server Gateway Interface) - ASGI servers intent to handle multiple protocol styles including HTTP, HTTP2, and web sockets. ASGI attempts to preserve a simple application interface, but provide an abstraction that allows for data to be sent and received at any time, and from different application threads or processes.
REDIS -  It is an in-memory data structure store that can be used as a caching engine. Since it keeps data in RAM, Redis can deliver it very quickly. Redis is not the only product that we can use for caching. Memcached is another popular in-memory caching system, but many people agree that Redis is superior to Memcached in most circumstances.
CHANNELS - Channels changes Django to weave asynchronous code underneath and through Django’s synchronous core, allowing Django projects to handle not only HTTP, but protocols that require long-running connections too - WebSockets, Streams, and more.
BROWSER - It is a software application for retrieving, presenting and traversing information resources from or to the Django application. We recommend Mozilla Firefox for running commander application.
PUG (JADE) FILES -  At run time, Pug (and other template engines) replace variables in our file with actual values, and then send the resulting HTML string to the client. This engine was formerly known as JADE. PyPugJS is a high-performance port of PugJS for python, that converts any .pug source to the Django compliant Template-language.

ARCHITECTURE
=============

CLIENT-SERVER ARCHITECTURE
--------------------------

The server-side application is developed, tested and maintained in Django framework. An ASGI (Asynchronous Server Gateway Interface) uses a Daphne server to serve web pages, scripts, templates, and styles. Daphne can handle multiple protocols such as HTTP, HTTP2, and web sockets. To launch a Daphne server cd to Django working directory and simply point Daphne to your ASGI channel layer instance, and optionally set a bind address and port (defaults to localhost, port 8000) :

>Daphne commander.asgi:channel_layer --port 8000

Click here for Daphne documentation and source code.
Django channels serve web socket connections. They are designed to provide a low latency (few milliseconds) and high throughput over guaranteed delivery, also they are easily scalable by launching more number of workers. Workers use multiprocessing library to spawn a process. Each worker takes an instances of objects in the consumer.py file, process requests independently and puts messages on channels. The maximum number of workers to be launched depends on CPU speed and kernel limit. A Redis caching server is also included to facilitate faster access to resources. To launch a worker enter the following command in the terminal, and optionally set debugging verbosity (-v) and number of threads (–threads) :

>python manage.py runworker -v 3 --threads 1

Click here for channels documentation.
The client-server architecture is illustrated in the image below. The browser sends HTTP and WebSocket request to ASGI, the Interface server, routes HTTP requests to Daphne layer and WebSocket connections to the channel layer. These requests are later appropriately forwarded. The Daphne server calls the view function that is invoked by the URL address in the request. The messages that arrive on channels are distributed among the workers, each worker processes their messages independently and puts the response on the channel which is sent over to the browser.

DATA TRANSMISSION ARCHITECTURE
------------------------------

The channel layer uses eight dedicated socket/channels. Each of these handles three different operations such as one shot, stream, and full-duplex data transmission. When the application loads, the DOM object is scraped, the requirement of the application is recognized and all associated data objects are extracted. These data objects are appropriately channeled into these 8 sockets which later perform one of the above-mentioned operations.The instance list and directory lists are obtained in one shot and updated in DOM; Events, video, and ADS-B are streams of data sent from server to client side; Telemetry, commanding and miscellaneous channels communicate bidirectionally and asynchronously. All data received on the client side is rendered onto the GUI using javascript callbacks.

TYPES OF DATA TRANSMISSION
--------------------------

One-Shot
Streaming
Full-Duplex

ONE-SHOT
--------

One shot data transmission gets data in a single call and halts connection until a pre-defined event happens. The client sends a invoke signal to the server over a socket, which in turn invokes a method that returns the required data. This data is packaged as a JSON object which is serialized, put on a message object and sent back to the client over a socket. An error occurred while receiving data at client side will resend the invoke signal, and if the error occurred while sending invoke to the server, it is written to the log, creates a custom error and sends it over to the client. Out of eight dedicated sockets two sockets, Instance and Directory communicate in one shot.

The method calls that are bound to the Instance socket, both server and client side are :
getInstanceList - client sends invoke signal to the server and receives instance list.
sendInstanceList - upon invoke server collects instance list and sends it over to the client.
transmitCurrentInstance - upon selection of an instance on the web application, the selected instance is sent over to the server.
setInstance - server updates its state with a new instance.

The method calls that are bound to the Directory socket, both server and client side are :
getDirectoryList - client sends invoke signal to the server and receives directory list.
sendDirectoryList - upon invoke server collects directory list and sends it over to the client.

STREAM
------

The stream data transmission sends continuous stream of data with a single call and halts connection until a pre-defined (shutdown) event happens. The client sends a invoke signal to the server over a socket, which in turn invokes a method that initializes the stream and emit frames at a certain rate which is defined by the stream driver. Each frame is packaged as a message object and sent back to client over socket. An error occurred while receiving data at client side will look if the error has a custom tag if so it is handled differently otherwise the error is logged and ignored. If the error occurred while sending invoke to the server, it is written to log, creates a custom error and sends it over to the client. Out of eight dedicated sockets three sockets, events, video and ADS-B communicate in streams.

The method calls that are bound to the Events socket, both server and client side are :
subscribeEvents - client sends invoke signal to the server and receives event list.
sendEvents- upon invoke server initializes event stream and push frames to the client over a socket.

The method calls that are bound to the Video socket, both server and client side are :
getVideoStream - client sends invoke signal to the server and receives live video frames.
sendVideo- upon invoke server initializes video stream and push frames to the client over a socket.
videoUDPClient - a UDP client gets live video data over UDP via airliner via video4linux.

The method calls that are bound to the ADS-B socket, both server and client side are :
getASDB - client sends invoke signal to the server and receives live decoded ADSB frames.
sendADSB- upon invoke server initializes ADSB stream and push frames to the client over a socket.

FULL-DUPLEX
-----------

The full-duplex data transmission sends and receives continuous streams of data. The client sends a message to the server over a socket, which in turn invokes a method that processess this message and returns a response to the client over a socket. At most 100 messages can be on a channel at any given second. Which means data can be transmitted asynchronously and bidirectionally. An error occurred while receiving data at client side will look if the error has a custom tag if so it is handled differently by calling the request function again, otherwise, the error is logged and ignored. If the error occurred while sending a message to the server, it is written to log, creates a custom error and sends it over to the client. Out of eight dedicated sockets three sockets, telemetry, commanding and misc communicate in full-duplex.

The method calls that are bound to the Telemetry socket, both server and client side are :
subscribeTelemetry - client sends a list of telemetry-subscription messages to the server and receives telemetry periodically.
unsubscribeTelemetry - client sends a list of telemetry-unsubscription messages to the server.
unsubscribeAllTelemetry - client sends a 'USALL' signal to the server.
sendTelemetry - upon receipt of a telemetry-subscription message, send the appropriate telemetry.
looseTelemetry - upon receipt of a telemetry-unsubscription message, unsubscribes telemetry. upon receipt of 'USALL' signal, all telemetry subscriptions are unsubscribed and closed.

The method calls that are bound to the Commanding socket, both server and client side are :
getCommandInfo- the client gets command information and attaches them to dom objects.
sendCommandInfo - server collects command information and sends it over to client
sendCommand- client sends the command over to the server.
sendCommand [Server] - Upon receipt of command it pushes it over to YAMCS/Pyliner

The method calls that are bound to the Misc socket, both server and client side are :
currently, there are no methods bound to misc.

LAUNCHING COMMANDER
===================
>Install the following packages on your workshop.

python
2.7.12
sudo apt install python
https://www.python.org/downloads/

Redis Server
4.0.2
sudo apt install redis-server
https://redis.io/download

jq
1.5
sudo apt install jq
https://stedolan.github.io/jq/

Django
1.10.2
pip install Django==1.10.2
https://docs.djangoproject.com/en/1.11/

asgi-redis
1.2.0
pip install asgi-redis==1.2.0
https://github.com/django/asgi_redis

channels
0.17.3
pip install channels==0.17.3
https://channels.readthedocs.io/en/latest/

daphne
1.3.0
pip install daphne==1.3.0
https://github.com/django/daphne

multiprocessing
2.6.2.1
pip install multiprocessing==2.6.2.1
https://docs.python.org/2/library/multiprocessing.html

psutil
3.4.2
pip install psutil==3.4.2
https://psutil.readthedocs.io/en/latest/

pypugjs
4.2.2
pip install pypugjs==4.2.2
https://github.com/matannoam/pypugjs

requests
2.18.4
pip install requests==2.18.4
http://docs.python-requests.org/en/master/

websocket-client
0.44.0
pip install websocket-client==0.44.0
https://websockets.readthedocs.io/en/stable/

>After installing required pacakges. cd to /airliner/tools/commander/scripts and execute  Launch_commander.sh

>Before launching commander initialize YAMCS_WORKSPACE, the environmental variable in bashrc and source it in the working directory.

>This script will initiate Daphne Server and 'n' number of workers. The value of n can be set in launch_config.json.

>Execution logs can be found under logs folder.

