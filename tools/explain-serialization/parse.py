from collections import OrderedDict
import sys
import json


def setup_serialization_dict(apps):
    base_dict = {}
    base_dict["Airliner"] = {}
    base_dict["Airliner"]["apps"] = {}
    
    for app in apps:
        base_dict["Airliner"]["apps"][app] = {}
        base_dict["Airliner"]["apps"][app]["app_name"] = app
        base_dict["Airliner"]["apps"][app]["app_ops_name"] = app
        base_dict["Airliner"]["apps"][app]["proto_msgs"] = {}

    return base_dict
    
def get_pb_name(sym_name):
    if sym_name[-2:] == "_t":
        return sym_name[:-2].lower() + "_pb"
        
    return "OTHER SYMBOL TODO"

def get_pb_type(sym):
    type_map = {
        "uint8":   "uint32",
        "uint16":  "uint32",
        "uint32":  "uint32",
        "uint64":  "uint64",
        "int8":    "int32",
        "int16":   "int32",
        "int32":   "int32",
        "int64":   "int64",
        "char":    "string",
        "boolean": "bool",
        "float":   "float",
    }

    if sym in type_map:
        return type_map[sym]
    elif is_enum(sym):
        return "uint32"
    else:
        return get_pb_name(sym)

def fix_fields(sym):
    if "fields" not in sym:
        return sym

    # Iterate over all fields in this symbol
    fields = {}
    for field in sym["fields"]:
        name = field["name"]
        if "fields" in field:
            # Recur into lowest level of nested fields and fix bottom up
            field = fix_fields(field)

        # Set new dict key equal to this field
        fields[name] = field

        # Set name TODO this shouldn't really be needed
        fields[name]["airliner_name"] = name
        
        # Remove unused keys from field
        del fields[name]["name"]            
        if "type" in fields[name]:
            del fields[name]["type"]
        if "base_type" in fields[name]:
            del fields[name]["base_type"]
        if "bit_size" in fields[name]:
            del fields[name]["bit_size"]
        if "bit_offset" in fields[name]:
            del fields[name]["bit_offset"]

        # Set types
        if "real_type" in fields[name]:
            fields[name]["airliner_type"] = fields[name]["real_type"]
            fields[name]["pb_type"] = get_pb_type(fields[name]["real_type"])
            del fields[name]["real_type"]
        
        # Set array length
        if "array" in fields[name]:
            fields[name]["array_length"] = fields[name]["count"]
            fields[name]["pb_field_rule"] = "repeated"
            del fields[name]["count"]
            del fields[name]["array"]
        else:
            fields[name]["array_length"] = 0
            fields[name]["pb_field_rule"] = "required"
        
    sym["fields"] = fields
    return sym
        
def fix_required(symbol):
    if "fields" not in symbol:
        return {}
        
    def fix(sym, req_pb={}, parent=None):
        if "fields" not in sym:
            return

        # Iterate over all fields in this symbol
        for field, data in sym["fields"].iteritems():
            # Don't do anything to fields which are not other structs
            if "fields" not in data:
                continue
            
            # Some fields appear to have this missing - TODO check explain
            if "airliner_type" not in data:
                print "Warning - missing attrs in " + field
                continue
            
            if parent:
                if data["pb_type"] in parent["required_pb_msgs"]:
                    # Need the value to be populated because jinja struggles with arrays, so we use a dictionary instead.
                    parent["required_pb_msgs"][data["pb_type"]]["parent_field"][field] = 0
                else:            
                    # Add required pb message
                    parent["required_pb_msgs"][data["pb_type"]] = {}
                    parent["required_pb_msgs"][data["pb_type"]]["airliner_msg"] = data["airliner_type"]
                    parent["required_pb_msgs"][data["pb_type"]]["parent_field"] = {field:0}
                    parent["required_pb_msgs"][data["pb_type"]]["fields"] = data["fields"]
                    parent["required_pb_msgs"][data["pb_type"]]["required_pb_msgs"] = {}
            # If this required pb message already exists, add our current field to the parent field dict in req_pb
            elif req_pb and data["pb_type"] in req_pb:
                # Need the value to be populated because jinja struggles with arrays, so we use a dictionary instead.
                req_pb[data["pb_type"]]["parent_field"][field] = 0
            else:            
                # Add required pb message
                req_pb[data["pb_type"]] = {}
                req_pb[data["pb_type"]]["airliner_msg"] = data["airliner_type"]
                req_pb[data["pb_type"]]["parent_field"] = {field:0}
                req_pb[data["pb_type"]]["fields"] = data["fields"]
                req_pb[data["pb_type"]]["required_pb_msgs"] = {}
            
            # Remove fields from struct field
            del data["fields"]
            
            # Recur into next level of nested fields and fix top down
            field = fix(data, req_pb, req_pb[data["pb_type"]])
            
        return req_pb

        
    #sym["required_pb_msgs"] = fix(symbol)
    return fix(symbol)
                
                
def is_enum(sym):
    global explain
    if explain and sym in explain["symbols"]:
        if explain["symbols"][sym]["bit_size"] == 32 and "fields" not in explain["symbols"][sym]:
            return True
    return False
        

def valid_symbol(sym, data):
    if "fields" not in data:
        return False
    if "_pb" in sym:
        return False

    return True        
                
explain = {}
with open("symbols.json", "r") as explain_json:
    explain = json.load(explain_json)

# Parse app names
apps = [app.split('.')[0] for app in explain["files"]]
apps.append("PX4")
serial_input = setup_serialization_dict(apps)

# Reformat data into expected form
for symbol, data in explain["symbols"].iteritems():
    # Skip empty struct definitions - we don't care about those here
    if not valid_symbol(symbol, data):
        continue
    
    # Lookup app name for this message so it can be placed correctly. TODO find a better way
    app_name = symbol.split("_")[0]
    if app_name not in apps:
        continue

    # Fix fields so key is message name
    serial_input["Airliner"]["apps"][app_name]["proto_msgs"][symbol] = fix_fields(data)
    
    # Remove unused keys
    if "type" in serial_input["Airliner"]["apps"][app_name]["proto_msgs"][symbol]:
        del serial_input["Airliner"]["apps"][app_name]["proto_msgs"][symbol]["type"]
    if "base_type" in serial_input["Airliner"]["apps"][app_name]["proto_msgs"][symbol]:
        del serial_input["Airliner"]["apps"][app_name]["proto_msgs"][symbol]["base_type"]

    serial_input["Airliner"]["apps"][app_name]["proto_msgs"][symbol]
    serial_input["Airliner"]["apps"][app_name]["proto_msgs"][symbol]["required_pb_msgs"] = fix_required(data)

       
        
with open("cookiecutter.json", "w") as cc:
    output = serial_input#OrderedDict(sorted(serial_input.items(), key = lambda x: serial_input['Airliner']['apps'][x]))
    json.dump(output, cc, indent=4)



