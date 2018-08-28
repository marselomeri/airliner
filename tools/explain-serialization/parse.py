from collections import OrderedDict
import sys
import json


def setup_serialization_dict(apps):
    base_dict = {}
    base_dict["Airliner"] = {}
    base_dict["Airliner"]["apps"] = {}
    base_dict["autogen_version"] = ""
    base_dict["_extensions"] = ["jinja2.ext.do", "jinja2.ext.loopcontrols"]
    
    for app in apps:
        base_dict["Airliner"]["apps"][app] = {}
        base_dict["Airliner"]["apps"][app]["app_name"] = app
        base_dict["Airliner"]["apps"][app]["app_ops_name"] = app
        base_dict["Airliner"]["apps"][app]["proto_msgs"] = {}
        base_dict["Airliner"]["apps"][app]["operations"] = {}

    return base_dict
    
def get_pb_name(sym_name):
    return sym_name + "_pb"

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
    global explain
    
    if sym in type_map:
        return type_map[sym]
    elif is_enum(sym):
        return "uint32"
    elif sym in explain["symbols"] and "real_type" in explain["symbols"][sym] and explain["symbols"][sym]["real_type"] in type_map:
        print explain["symbols"][sym]["real_type"]
        type_map[explain["symbols"][sym]["real_type"]]
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
#        if "bit_size" in fields[name]:
#            del fields[name]["bit_size"]
#        if "bit_offset" in fields[name]:
#            del fields[name]["bit_offset"]

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
        try:
        
            if "fields" not in sym:
                return req_pb

            # Iterate over all fields in this symbol
            for field, data in sym["fields"].iteritems():
                # Don't do anything to fields which are not other structs
                if "fields" not in data:
                    continue
                
                if "airliner_type" in data and "pb_type" in data:
                    sym_type = data["airliner_type"]
                    pb_type = data["pb_type"]
                else:
                    continue
                
                if parent:
                    #print "\nhave parent" + str(parent)
                    if pb_type in parent["required_pb_msgs"]:
                        #print "type in parent"
                        # Need the value to be populated because jinja struggles with arrays, so we use a dictionary instead.
                        parent["required_pb_msgs"][pb_type]["parent_field"][field] = 0
                    else:            
                       # print "type not in parent"
                        # Add required pb message
                        parent["required_pb_msgs"][pb_type] = {}
                        parent["required_pb_msgs"][pb_type]["airliner_msg"] = sym_type
                        parent["required_pb_msgs"][pb_type]["parent_field"] = {field:0}
                        parent["required_pb_msgs"][pb_type]["fields"] = data["fields"]
                        parent["required_pb_msgs"][pb_type]["required_pb_msgs"] = {}
                        
                    # Recur into next level of nested fields and fix top down
                    req_pb = fix(data, req_pb, parent["required_pb_msgs"][pb_type])
                    
                else:
                    # If this required pb message already exists, add our current field to the parent field dict in req_pb
                    if req_pb and pb_type in req_pb:
                        #print "found type in req pb"
                        # Need the value to be populated because jinja struggles with arrays, so we use a dictionary instead.
                        req_pb[pb_type]["parent_field"][field] = 0
                    else:
                        #print "adding type to req pb"
                        # Add required pb message
                        req_pb[pb_type] = {}
                        req_pb[pb_type]["airliner_msg"] = sym_type
                        req_pb[pb_type]["parent_field"] = {field:0}
                        req_pb[pb_type]["fields"] = data["fields"]
                        req_pb[pb_type]["required_pb_msgs"] = {}
    
                    # Recur into next level of nested fields and fix top down
                    req_pb = fix(data, req_pb, req_pb[pb_type])

                # Remove fields from struct field
                del data["fields"]
                
        except Exception as e:
            print "\n"
            print repr(e)
            print field
            print data
            print "\n"
            print req_pb
            
            
        return req_pb

    return fix(symbol, OrderedDict())
                
                
def is_enum(sym):
    global explain
    if explain and sym in explain["symbols"]:
        if explain["symbols"][sym]["bit_size"] == 32 and "fields" not in explain["symbols"][sym]:
            return True
    return False
        

def valid_symbol(sym, data):
    if "fields" not in data:
        return False
    elif "_pb" in sym:
        return False

    return True        
                
explain = {}
with open("symbols.json", "r") as explain_json:
    explain = json.load(explain_json)

# Parse app names
apps = [app.split('.')[0] for app in explain["files"]]
apps.append("PX4")
apps.append("CFE")
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
    if "real_type" in serial_input["Airliner"]["apps"][app_name]["proto_msgs"][symbol]:
        del serial_input["Airliner"]["apps"][app_name]["proto_msgs"][symbol]["real_type"]

    serial_input["Airliner"]["apps"][app_name]["proto_msgs"][symbol]["operational_names"] = {}

    serial_input["Airliner"]["apps"][app_name]["proto_msgs"][symbol]["proto_msg"] = get_pb_name(symbol)
    serial_input["Airliner"]["apps"][app_name]["proto_msgs"][symbol]["required_pb_msgs"] = fix_required(data)


    serial_input["Airliner"]["apps"][app_name]["operations"][symbol] = {}
    serial_input["Airliner"]["apps"][app_name]["operations"][symbol]["airliner_msg"] = symbol
    serial_input["Airliner"]["apps"][app_name]["operations"][symbol]["airliner_cc"] = -1
    serial_input["Airliner"]["apps"][app_name]["operations"][symbol]["airliner_mid"] = ""
    #print serial_input["Airliner"]["apps"][app_name]["proto_msgs"][symbol]
    #print "\n\n\n\n"
       
        
with open("cookiecutter.json", "w") as cc:
    output = serial_input#OrderedDict(sorted(serial_input.items(), key = lambda x: serial_input['Airliner']['apps'][x]))
    json.dump(output, cc, indent=4)



