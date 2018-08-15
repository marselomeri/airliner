from collections import OrderedDict
import sys
import json

def setup_serialization_dict(apps):
    base_dict = {}
    base_dict["Airliner"] = {}
    base_dict["Airliner"]["apps"] = {}
    
    for app in apps:
        base_dict["Airliner"]["apps"][app] = {}
    
    return base_dict
    
explain = {}
with open("symbols.json", "r") as explain_json:
    explain = json.load(explain_json)

apps = [app.split('.')[0] for app in explain["files"]]
serial_input = setup_serialization_dict(apps)

for symbol, data in explain["symbols"].iteritems():
    app_name = symbol.split("_")[0]
    if app_name in apps:
        serial_input["Airliner"]["apps"][app_name][symbol] = data
        
        
        
with open("cookiecutter.json", "w") as cc:
    output = serial_input#OrderedDict(sorted(serial_input.items(), key = lambda x: serial_input['Airliner']['apps'][x]))
    json.dump(output, cc, indent=4)



