from flask import Flask, render_template
from flask_socketio import SocketIO

app = Flask(__name__)
app.config['SECRET_KEY'] = 'secret!'
socketio = SocketIO(app)

@socketio.on('message')
def handle_message(message):
    print message
    print('received message: ' + str(message))
    #while True:
        #send('hello')

    #print('received message: ' + str(message))

if __name__ == '__main__':
    socketio.run(app, host= '127.0.0.1',port = 8050,debug=True)