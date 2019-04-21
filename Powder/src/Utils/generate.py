import os
import glob

fileDir = os.path.dirname(os.path.realpath('__file__'))

def parse_folder(typ, f, folderPath):
    names = [os.path.splitext(x)[0] for x in map(os.path.basename, glob.iglob(folderPath + '/' + '*.h'))]
    for idx, name in  enumerate(names):
        f.write('#define {0}_{1} {2}\n'.format(typ, name.upper(), idx + 1))
    return names

def includes(filename, idName, names, baseFolder):
    with open(filename, 'w') as f:
        f.write('#pragma once\n#include \"{0}\"\n'.format(idName))
        for name in names:
            f.write('#include \"{1}\\{0}.h\"\n'.format(name, baseFolder))

def tool_generate(idPath, includePath, toolsPath):
    with open(idPath, 'w') as f:
        names = parse_folder('TL', f, toolsPath)
    includes(includePath, 'ToolsIds.h', names, 'Tools')
    

def element_generate(idPath, includePath, elementsPath):
    with open(idPath, 'w') as eFile:
        eFile.write('''#pragma once
#define ST_GAS 0
#define ST_LIQUID 1
#define ST_POWDER 2
#define ST_SOLID 3

#define C_BLOCK 0
#define C_PASS 1
#define C_SWAP 2

static inline int IDX(int x, int y, int w)
{
	return y * w + x;
}\n''')
        eFile.write('''//ELEMENT_IDS
#define EL_NONE nullptr
#define EL_NONE_ID 0\n''')
        names = parse_folder('EL', eFile, elementsPath)
        #print(eFile.read())
    includes(includePath, 'ElementsIds.h', names, 'Elements')

def main(elIdFile, elIncFile, tlIdFile, tlIncFile):
    elementIdPath = os.path.abspath(os.path.realpath(os.path.join(fileDir, '../Element/' + elIdFile)))
    elementsPath = os.path.abspath(os.path.realpath(os.path.join(fileDir, '../Element/Elements/')))
    elementIncludePath = os.path.abspath(os.path.realpath(os.path.join(fileDir, '../Element/' + elIncFile)))

    toolIdPath = os.path.abspath(os.path.realpath(os.path.join(fileDir, '../SimTool/' + tlIdFile)))
    toolsPath = os.path.abspath(os.path.realpath(os.path.join(fileDir, '../SimTool/Tools/')))
    toolIncludePath = os.path.abspath(os.path.realpath(os.path.join(fileDir, '../SimTool/' + tlIncFile)))

    element_generate(elementIdPath, elementIncludePath, elementsPath)
    tool_generate(toolIdPath, toolIncludePath, toolsPath)

if __name__ == "__main__":
    #hardcoded for now, TODO make it with cmd params
    main('ElementsIds.h', 'ElementIncludes.h', 'ToolsIds.h', 'ToolIncludes.h')