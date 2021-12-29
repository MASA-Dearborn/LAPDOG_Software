import json

real_struct_strings = []
raw_struct_strings = []
realToRaw_conversions = []
rawToReal_conversions = []
message_collection_struct = ''
ids_enum = ''
collection_case_statements = ''

def signalToRawString(signal):
    return 'int ' + signal['name'] + ' : ' + str(signal['bits']) + ';\n'

def signalToRealString(signal):
    if(signal['init']):
        return signal['ctype'] + ' ' + signal['name'] + ' = ' + str(signal['init']) + ';\n'
    else:
        return signal['ctype'] + ' ' + signal['name'] + ';\n'
 
def signalRawToReal(signal):
    # real.signal = raw.signal * factor + min
    if signal['ctype'] in ['int', 'unsigned int', 'char', 'unsigned char']:
        factor = 1
    else:
        factor = (signal['max'] - signal['min']) / 2**signal['bits']

    return signal['name'] + ' = (raw.' + signal['name'] + ' * ' + str(factor) + ') + ' + str(signal['min']) + ';\n'

def signalRealToRaw(signal):
    # raw.signal = (real.signal - min) / factor
    if signal['ctype'] in ['int', 'unsigned int', 'char', 'unsigned char']:
        factor = 1
    else:
        factor = (signal['max'] - signal['min']) / 2**signal['bits']

    return signal['name'] + ' = (real.' + signal['name'] + ' - ' + str(signal['min']) + ') / ' + str(factor) + ';\n'

def createRawStructStr(message):
    struct = "struct " + message['name'] + ' {\n'
    struct += '    msg::id::MessageType id = msg::id::MessageType::' + message['name'] + ';\n'
    for signal in message['signals']:
        struct += '    ' + signalToRawString(signal)
    struct += '};\n'
    return struct

def createRealStructStr(message):
    struct = "struct " + message['name'] + ' {\n'
    struct += '    msg::id::MessageType id = msg::id::MessageType::' + message['name'] + ';\n'
    for signal in message['signals']:
        struct += '    ' + signalToRealString(signal)
    struct += '};\n'
    return struct

def addMessageToIds(message, id):
    global ids_enum
    ids_enum += '    ' + message['name'] + ' = ' + str(id) + ',\n'
    return

def addMessageToTypes(message):
    raw_struct_strings.append(createRawStructStr(message))
    real_struct_strings.append(createRealStructStr(message))
    return

def addMessageToCollectionStruct(message):
    global message_collection_struct
    message_collection_struct += '    real::' + message['name'] + ' ' + message['name'] + ';\n'
    return

def addMessageToCollectionCaseStatement(message):
    global collection_case_statements
    collection_case_statements += '        case msg::id::' + message['name'] + ':\n            return &collection.' + message['name'] + ';\n'
    return

def addMessageRawToRealConversion(message):
    global rawToReal_conversions

    function = 'inline msg::real::' + message['name'] + ' ' + message['name'] + '_TO_REAL(msg::raw::' + message['name'] + ' raw) {\n'
    function += '    msg::real::' + message['name'] + ' real;\n'
    for signal in message['signals']:
        function += '    real.' + signalRawToReal(signal)
    function += '    return real;\n}\n'

    rawToReal_conversions.append(function)
    return

def addMessageRealToRawConversion(message):
    global realToRaw_conversions
    
    function = 'inline msg::raw::' + message['name'] + ' ' + message['name'] + '_TO_RAW(msg::real::' + message['name'] + ' real) {\n'
    function += '    msg::raw::' + message['name'] + ' raw;\n'
    for signal in message['signals']:
        function += '    raw.' + signalRealToRaw(signal)
    function += '    return raw;\n}\n'

    realToRaw_conversions.append(function)
    return

def addMessage(message, id):
    addMessageToIds(message, id)
    addMessageToTypes(message)
    addMessageToCollectionStruct(message)
    addMessageToCollectionCaseStatement(message)
    addMessageRealToRawConversion(message)
    addMessageRawToRealConversion(message)

    return

def initGlobalStrings():
    global ids_enum, message_collection_struct, collection_case_statements

    message_collection_struct += 'struct MessageCollection {\n'

    collection_case_statements += 'inline void* getMessageAddressFromCollection(MessageCollection& collection, const id::MessageType type) {\n'
    collection_case_statements += '    ' + 'switch (type) {\n'

    ids_enum += 'enum MessageType {\n'

    return

def finishGlobalStrings():
    global ids_enum, message_collection_struct, collection_case_statements

    message_collection_struct += '};\n'

    collection_case_statements += '        default:\n'
    collection_case_statements += '            return nullptr;\n'
    collection_case_statements += '    ' + '}\n'
    collection_case_statements += '}\n'

    ids_enum += '    META_NUM_MESSAGES,\n'
    ids_enum += '    UNDEFINED_MESSAGE,\n'
    ids_enum += '};\n'

    return

def writeNamespaceIds(file):
    global ids_enum

    ids_enum = '    ' + ids_enum
    ids_enum = ids_enum.replace('\n', '\n    ')

    file.write('namespace msg::id {\n\n')
    file.write(ids_enum)
    file.write('\n}\n\n')
    return

def writeNamespaceReal(file):
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
    global realToRaw_conversions, rawToReal_conversions

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
    
    file.write('\n}\n\n')
    return

def writeNamespaceMsg(file):
    global collection_case_statements, message_collection_struct

    collection_case_statements = '    ' + collection_case_statements
    collection_case_statements = collection_case_statements.replace('\n', '\n    ')

    message_collection_struct = '    ' + message_collection_struct
    message_collection_struct = message_collection_struct.replace('\n', '\n    ')

    file.write('namespace msg {\n\n')

    file.write(message_collection_struct)
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
        outputFile.write('#pragma once\n\n')
        writeNamespaceIds(outputFile)
        writeNamespaceReal(outputFile)
        writeNamespaceRaw(outputFile)
        writeNamespaceMsg(outputFile)
        writeNamespaceConv(outputFile)
    