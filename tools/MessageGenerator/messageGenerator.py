'''
    A Tool to generate a messageTypes.h file for the LAPDOG messaging system
    Messages are defined in messages.json

    Written by Lucas Ringe
    12/28/2021
'''

import json

real_struct_strings = []
raw_struct_strings = []
realToRaw_conversions = []
rawToReal_conversions = []
message_collection_struct = ''
message_union_struct = ''
ids_enum = ''
collection_case_statements = ''
conversion_case_statement = ''

def signalToRawString(signal):
    return 'int ' + signal['name'] + ' : ' + str(signal['bits']) + ';\n'

def signalToRealString(signal):
    if(signal['init']):
        return signal['ctype'] + ' ' + signal['name'] + ' = ' + str(signal['init']) + ';\n'
    else:
        return signal['ctype'] + ' ' + signal['name'] + ';\n'
 
def signalRawToReal(signal):
    # real.signal = raw.signal * factor + min
    if signal['ctype'] in ['float', 'double']:
        factor = (signal['max'] - signal['min']) / 2**signal['bits']
    else:
        factor = 1

    return signal['name'] + ' = (raw->' + signal['name'] + ' * ' + str(factor) + ') + ' + str(signal['min']) + ';\n'

def signalRealToRaw(signal):
    # raw.signal = (real.signal - min) / factor
    if signal['ctype'] in ['float', 'double']:
        factor = (signal['max'] - signal['min']) / 2**signal['bits']
    else:
        factor = 1

    return signal['name'] + ' = (real->' + signal['name'] + ' - ' + str(signal['min']) + ') / ' + str(factor) + ';\n'

def createRawStructStr(message):
    struct = "struct " + message['name'] + ' : GENERIC_MESSAGE {\n'
    struct += '    ' + message['name'] + '() { id = msg::id::' + message['name'] + '; size = sizeof(' + message['name'] + '); }\n'
    for signal in message['signals']:
        struct += '    ' + signalToRawString(signal)
    struct += '};\n'
    return struct

def createRealStructStr(message):
    struct = "struct " + message['name'] + ' : GENERIC_MESSAGE {\n'
    struct += '    ' + message['name'] + '() { id = msg::id::' + message['name'] + '; size = sizeof(' + message['name'] + '); }\n'
    for signal in message['signals']:
        struct += '    ' + signalToRealString(signal)
    struct += '};\n'
    return struct

def addMessageToIds(message, id):
    '''
        Adds a message to the message id enum with a specified id
    '''
    global ids_enum
    ids_enum += '    ' + message['name'] + ' = ' + str(id) + ',\n'
    return

def addMessageToTypes(message):
    '''
        Append the string version of the real and raw C struct to the correct global var
    '''
    raw_struct_strings.append(createRawStructStr(message))
    real_struct_strings.append(createRealStructStr(message))
    return

def addMessageToCollectionStruct(message):
    '''
        Adds a message type to the main MessageCollection struct
    '''
    global message_collection_struct
    message_collection_struct += '    real::' + message['name'] + ' ' + message['name'] + ';\n'
    return

def addMessageToCollectionUnion(message):
    '''
        Adds a message type to the main MessageUnion struct
    '''
    global message_union_struct
    message_union_struct += '    real::' + message['name'] + ' ' + message['name'] + ';\n'
    #message_union_struct += '    raw::' + message['name'] + ' ' + message['name'] + ';\n'
    return

def addMessageToCollectionCaseStatement(message):
    '''
        Generates a case statement for the collection address function
    '''
    global collection_case_statements
    collection_case_statements += '        case msg::id::' + message['name'] + ':\n            return &collection.' + message['name'] + ';\n'
    return

def addMessageRawToRealConversion(message):
    '''
        Generates function for raw to real message conversion
    '''
    global rawToReal_conversions

    function = 'inline msg::real::' + message['name'] + ' ' + message['name'] + '_TO_REAL(msg::raw::' + message['name'] + '* raw) {\n'
    function += '    msg::real::' + message['name'] + ' real;\n'
    for signal in message['signals']:
        function += '    real.' + signalRawToReal(signal)
    function += '    return real;\n}\n'

    rawToReal_conversions.append(function)
    return

def addMessageRealToRawConversion(message):
    '''
        Generates function for real to raw message conversion
    '''
    global realToRaw_conversions
    
    function = 'inline msg::raw::' + message['name'] + ' ' + message['name'] + '_TO_RAW(msg::real::' + message['name'] + '* real) {\n'
    function += '    msg::raw::' + message['name'] + ' raw;\n'
    for signal in message['signals']:
        function += '    raw.' + signalRealToRaw(signal)
    function += '    return raw;\n}\n'

    realToRaw_conversions.append(function)
    return

def addMessageToConversionStatement(message):
    global conversion_case_statement

    statement = '        case msg::id::' + message['name'] + ':\n'
    statement += '            dest->' + message['name'] + ' = msg::conv::' + message['name'] + '_TO_REAL((msg::raw::' + message['name'] + '*)(raw));\n'           

    conversion_case_statement += (statement)
    return

def addMessage(message, id):
    '''
        Add a JSON message to the string collections
        Must be called for every message
    '''
    addMessageToIds(message, id)
    addMessageToTypes(message)
    addMessageToCollectionStruct(message)
    addMessageToCollectionUnion(message)
    addMessageToCollectionCaseStatement(message)
    addMessageRealToRawConversion(message)
    addMessageRawToRealConversion(message)
    addMessageToConversionStatement(message)

    return

def initGlobalStrings():
    '''
        Prefixes global strings to ensure valid C code
        Called before string creation section
    '''
    global ids_enum, message_collection_struct, collection_case_statements, message_union_struct, conversion_case_statement

    message_collection_struct += 'struct MessageCollection {\n'
    message_union_struct += 'union MessageUnion {\n'
    message_union_struct += '    MessageUnion() { memset( this, 0, sizeof( MessageUnion ) ); }'

    collection_case_statements += 'inline void* getMessageAddressFromCollection(MessageCollection& collection, const id::MessageType type) {\n'
    collection_case_statements += '    ' + 'switch (type) {\n'

    ids_enum += 'enum MessageType {\n'

    conversion_case_statement += 'inline msg::id::MessageType convertRawToReal(msg::MessageUnion* dest, GENERIC_MESSAGE* raw) {\n'
    conversion_case_statement += '    switch(raw->id) {\n'

    return

def finishGlobalStrings():
    '''
        Appends endings to global strings to make valid C code
        Called at end of string creation section
    '''
    global ids_enum, message_collection_struct, collection_case_statements, message_union_struct, conversion_case_statement

    message_collection_struct += '};\n'
    message_union_struct += '};\n'

    collection_case_statements += '        default:\n'
    collection_case_statements += '            return nullptr;\n'
    collection_case_statements += '    ' + '}\n'
    collection_case_statements += '}\n'

    ids_enum += '    META_NUM_MESSAGES,\n'
    ids_enum += '    UNDEFINED_MESSAGE,\n'
    ids_enum += '};\n'

    conversion_case_statement += '    }\n    return raw->id;\n}'

    return

def writeNamespaceIds(file):
    '''
        Writes the namespace for the id enum definition
    '''
    global ids_enum

    ids_enum = '    ' + ids_enum
    ids_enum = ids_enum.replace('\n', '\n    ')

    file.write('namespace msg::id {\n\n')
    file.write(ids_enum)
    file.write('\n}\n\n')
    return

def writeNamespaceReal(file):
    '''
        Writes the namespace for the real struct definitions
    '''
    global real_struct_strings

    file.write('namespace msg::real {\n')

    for struct in real_struct_strings:
        file.write('\n')
        struct = '    ' + struct
        struct = struct.replace('\n', '\n    ')
        file.write(struct)

    file.write('\n}\n\n')
    return

def writeNamespaceRaw(file):
    '''
        Writes the namespace for the raw struct definitions
    '''
    global raw_struct_strings

    file.write('namespace msg::raw {\n')

    for struct in raw_struct_strings:
        file.write('\n')
        struct = '    ' + struct
        struct = struct.replace('\n', '\n    ')
        file.write(struct)

    file.write('\n}\n\n')
    return

def writeNamespaceConv(file):
    '''
        Writes the namespace for conversion functions
    '''
    global realToRaw_conversions, rawToReal_conversions, conversion_case_statement

    file.write('namespace msg::conv {\n')

    for func in rawToReal_conversions:
        file.write('\n')
        func = '    ' + func
        func = func.replace('\n', '\n    ')
        file.write(func)

    for func in realToRaw_conversions:
        file.write('\n')
        func = '    ' + func
        func = func.replace('\n', '\n    ')
        file.write(func)
        
    conversion_case_statement = '\n' + conversion_case_statement
    conversion_case_statement = conversion_case_statement.replace('\n', '\n    ')
    file.write(conversion_case_statement)

    file.write('\n}\n\n')
    return

def writeGenericNamespace(file):
    file.write('namespace msg {\n\n')

    # Write Generic Messages
    file.write('    struct GENERIC_MESSAGE {\n')
    file.write('        msg::id::MessageType id = msg::id::UNDEFINED_MESSAGE;\n')
    file.write('        unsigned int size = sizeof(GENERIC_MESSAGE);\n')
    file.write('    };\n')

    file.write('\n}\n\n')

def writeNamespaceMsg(file):
    global collection_case_statements, message_collection_struct, message_union_struct

    collection_case_statements = '    ' + collection_case_statements
    collection_case_statements = collection_case_statements.replace('\n', '\n    ')

    message_collection_struct = '    ' + message_collection_struct
    message_collection_struct = message_collection_struct.replace('\n', '\n    ')

    message_union_struct = '    ' + message_union_struct
    message_union_struct = message_union_struct.replace('\n', '\n    ')

    file.write('namespace msg {\n\n')

    # Write Generated Messages
    file.write(message_collection_struct)
    file.write('\n')
    file.write(message_union_struct)
    file.write('\n')
    file.write(collection_case_statements)

    file.write('\n}\n\n')

if __name__ == "__main__":

    with open('messages.json') as message_file:
        messages = json.load(message_file)['MessageCollection']

    initGlobalStrings()

    for id, message in enumerate(messages):
        addMessage(message, id)

    finishGlobalStrings()

    with open('messageTypes.h', 'w') as outputFile:
        outputFile.write('/* Auto-generated Code from messageGenerator.py */\n\n')
        outputFile.write('#pragma once\n#include "string.h"\n\n')
        writeNamespaceIds(outputFile)
        writeGenericNamespace(outputFile)
        writeNamespaceReal(outputFile)
        writeNamespaceRaw(outputFile)
        writeNamespaceMsg(outputFile)
        writeNamespaceConv(outputFile)
    