#!/usr/bin/env python3
###############################################################################
##
##	File: GenerateAST.py
##
##	A script written to help in the automatic generation of Abstract Syntax
##  Trees for the interpreter/parser. It creates a .hpp, so the preferable
##  location to store the output file is in the include directory. This script
##  only takes one argument that specifies the output directory. Run using:
##  python GenerateAST.py <output directory>
##
###############################################################################

import sys

def defineAST(outputDir, baseName, types):
    path = outputDir + "\\" + baseName + ".hpp"

    f = open(path, "a")
    f.write("#include <string>\n")
    f.write("#include \"Token.hpp\"\n\n")
    f.write("using namespace std;\n\n")

    f.write("class " + baseName + " {\n\n")
    f.write("\tpublic: \n\n")
    f.write("\t\tvirtual ~" + baseName + "() { }\n\n")
    f.write("};\n\n")

    # The AST classes
    for t in types:
        className = t.split(":")[0].strip()
        fields = t.split(":")[1].strip()
        defineType(f, baseName, className, fields)

    f.close()

def defineType(f, baseName, className, fieldList):
    f.write("class " + className + " : public " + baseName + " \n{\n")
    f.write("\tpublic: \n\n")

    # Constructor
    f.write("\t\t" + className + "(" + fieldList + ")\n\t\t\t: ")

    # Store parameters in fields
    fields = fieldList.split(", ")
    for i, field in enumerate(fields):
        name = field.split(" ")[1]
        if i + 1 == len(fields):
            f.write("m" + name + "(" + name + ")")
        else:
            f.write("m" + name + "(" + name + "), ")
    f.write ("{ }\n\n")

    # Fields of the class
    f.write("\tprivate: \n\n")
    for i, field in enumerate(fields):
        t, name = field.split(" ")
        f.write("\t\t" + t + " m" + name + ";\n")

    f.write ("};\n\n")

if __name__ == "__main__":

    if len(sys.argv) != 2:
        print("Usage: generateAST <output directory>")
        sys.exit()

    outputDir = sys.argv[1]
    types = [
        "Binary   : Expr Left, Token Operator, Expr Right",
        "Grouping : Expr Expression",
        "Literal  : string Value",
        "Unary    : Token Operator, Expr Right"
    ]

    defineAST(outputDir, "Expr", types)
