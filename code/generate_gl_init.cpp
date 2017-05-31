#include <ctype.h>
#include <stdio.h>
#include <string.h>

/* TODO(joe)
 *  - Load the functions file.
 *  - Parse the name of the each function in the file
 *  - Create the typedef of the function.
 *  - Create the function pointer
 *  - Add an entry for the function in the InitGL() method.
 */

struct gl_function
{
    char Name[256];
    char Signature[256]; 
    char TypeDefName[256];
};

struct gl_function_table
{
    gl_function Functions[256];
    int FunctionCount;
};

static gl_function_table LoadFunctionTable(char *FileName)
{
    gl_function_table Table = {};

    FILE *File = fopen(FileName, "r");
    if (File)
    {
        char Buffer[256];
        while (fgets(Buffer, 256, File))
        {
            if (*Buffer != '\n' && *Buffer != '/')
            {
                gl_function *Function = Table.Functions + Table.FunctionCount++;

                char *NameStart = strstr(Buffer, "gl");
                char *NameEnd = strstr(Buffer, "(");
                char *LineEnd = strstr(Buffer, "\n");

                if (NameStart && NameEnd && LineEnd)
                {
                    // NOTE(joe): Name
                    size_t NameLength = NameEnd - NameStart;
                    strncpy(Function->Name, NameStart, NameLength);

                    // NOTE(joe): TypeDefName
                    char *Name = Function->Name;
                    char *TypeDef = Function->TypeDefName;
                    while(Name && *Name != '\0')
                    {
                        if (isupper(*Name))
                        {
                            *TypeDef++ = '_';
                            *TypeDef++ = tolower(*Name++);
                        }
                        else
                        {
                            *TypeDef++ = *Name++;
                        }
                    }
                    *TypeDef = '\0';

                    // NOTE(joe): Signature
                    char *Source = Buffer;
                    char *Dest = Function->Signature;
                    while (Source && *Source != '\n')
                    {
                        if (Source == NameStart)
                        {
                            *Dest++ = '(';
                            strcpy(Dest, Function->TypeDefName);
                            Dest += strlen(Function->TypeDefName);
                            *Dest++ = ')';

                            Source = NameEnd;
                        }
                        else
                        {
                            *Dest++ = *Source++;
                        }
                    }
                }
            }
        }
    }
    else
    {
        printf("Unable to load the function table.\n");
    }

    return Table;
}

static void WriteFunctionTypeDefs(FILE *File, gl_function_table *FunctionTable)
{
    for (int FunctionIndex = 0; FunctionIndex < FunctionTable->FunctionCount; ++FunctionIndex)
    {
        gl_function *Function = FunctionTable->Functions + FunctionIndex;

        fprintf(File, "typedef %s\n", Function->Signature);
    }
    fprintf(File, "\n");
}

static void WriteFunctionPointers(FILE *File, gl_function_table *FunctionTable)
{
    for (int FunctionIndex = 0; FunctionIndex < FunctionTable->FunctionCount; ++FunctionIndex)
    {
        gl_function *Function = FunctionTable->Functions + FunctionIndex;

        fprintf(File, "%s *aq%s;\n", Function->TypeDefName, Function->Name);
        fprintf(File, "#define %s aq%s\n\n", Function->Name, Function->Name);
    }
    fprintf(File, "\n");
}

static void WriteInitGL(FILE *File, gl_function_table *FunctionTable)
{

    fprintf(File, "static bool InitGL()\n{\n");
    for (int FunctionIndex = 0; FunctionIndex < FunctionTable->FunctionCount; ++FunctionIndex)
    {
        gl_function *Function = FunctionTable->Functions + FunctionIndex;

        fprintf(File, "    %s = (%s *)SDL_GL_GetProcAddress(\"%s\");\n", 
                Function->Name, Function->TypeDefName, Function->Name);
        fprintf(File, "    if (!%s) return false;\n\n", Function->Name);
    }
    fprintf(File, "    return true;\n");
    fprintf(File, "}\n\n");
}

int main(int argc, char **argv)
{
    gl_function_table FunctionTable = LoadFunctionTable("code\\gl.functions");

    FILE *File = fopen("code\\gl_init.h", "w");
    if (File)
    {
        fputs("#pragma once\n\n", File);

        fputs("//\n// OpenGL Function Typedefs\n//\n\n", File);
        WriteFunctionTypeDefs(File, &FunctionTable);

        fputs("//\n// OpenGL Function Pointers\n//\n\n", File);
        WriteFunctionPointers(File, &FunctionTable);

        WriteInitGL(File, &FunctionTable);

        fclose(File);
    }
    else
    {
        printf("Unable to open gl init file.\n");
    }

    return 0;
}
