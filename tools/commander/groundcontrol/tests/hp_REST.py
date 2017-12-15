from flask import Flask, request
from flask_restful import Resource, Api
from flask import stream_with_context, request, Response
from json import dumps
#from flask.ext.jsonpify import jsonify
import time


app = Flask(__name__)
api = Api(app)


class Employees(Resource):
    def get(self):
        while True:
            return "OIOIASJDF)#@UFIEJFIJFOAISFJOA:FIP)#@*FOEIWJF@P#)(R)WJW)R(UJ@POIEJF)@(#RWPEOFJOWEGIRGJBOIWERF_@#_)R"

@app.route('/stream')
def streamed_response():

    def generate():

        time.sleep(2)
        yield 'HEllo'
    return Response(stream_with_context(generate()))

api.add_resource(Employees, '/test')  # Route_1


if __name__ == '__main__':
    app.run(port=9000)
