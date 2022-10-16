#define EXPORT_CODE 0
#define EXPORT_DATA 1
#define CHARS 94
#define ASCII_START 33

typedef struct
{
    int letterSpacing;
    int wordSpacing;
    int lineSpacing;
    int baselineOffset;
    int indentation;
    char fontName[256];
    int fontCharWidths[CHARS];
}Font;

int pos;
int exportType = EXPORT_CODE;
Font font = { 1, 6, 25, 0, 28, "default"};

int fromASCII(int num);
void getWidths(void);
void printText(char *string, Font *fontPointer);
void generateFontDataFile(char *fileName);
void generateFontDataCodeFile(char *fileName);
void generateFontSVG(char *fileName, char *fontName, int fontSize);

int fromASCII(int num)
{
    int value = num - ASCII_START;

    if (value < 0 || value > CHARS - 1) return '?' - ASCII_START;
    else return value;
}

void getWidths(void)
{
    int i = 0;

    pos = 0;

    while (i < CHARS)
    {
        SendActivationEvent("textActor");
        pos ++;
        i ++;
    }
}

void printText(char *string, Font *fontPointer)
{
    int i;
    int len = strlen(string);
    int prevX = 0;
    int prevY = 175;

    DestroyActor("textActor");

    for (i = 0; i < len; i ++)
    {
        Actor *a;
        int tempIndentation;
        int letterNum = fromASCII(string[i]);

        switch (string[i])
        {
            case ' ': prevX += fontPointer->wordSpacing; break;
            case '\n': prevX = 0; prevY += fontPointer->lineSpacing; break;
            case '\t':
                if (fontPointer->indentation != 0)
                {
                    tempIndentation = ceil(prevX / fontPointer->indentation) * fontPointer->indentation + fontPointer->indentation;
                    prevX = tempIndentation;
                }
            break;

            default:
                prevX += floor(fontPointer->fontCharWidths[letterNum] * 0.5) + fontPointer->letterSpacing * (prevX != 0);
                a = CreateActor("textActor", "fontAnim", "(none)", "(none)", prevX, prevY, false);
                a->animpos = letterNum;
                prevX += ceil(fontPointer->fontCharWidths[letterNum] * 0.5);
            break;
        }
    }
}

void generateFontDataFile(char *fileName)
{
    FILE *f = fopen(addFileExtension(fileName, "fdf"), "w+b");

    if (f)
    {
        strcpy(font.fontName, trimIllegalCharacters(fileName));

        fwrite(&font, 1, sizeof(font), f);
        fclose(f);
    }
}

void generateFontDataCodeFile(char *fileName)
{
    FILE *f = fopen(addFileExtension(fileName, "c"), "w+");

    if (f)
    {
        int i, j;

        strcpy(font.fontName, trimIllegalCharacters(fileName));

        fprintf(f, "Font %s =\n", trimIllegalCharacters(fileName));
        fprintf(f, "{\n");
        fprintf(f, "    %2i, // Letter spacing in pixels\n", font.letterSpacing);
        fprintf(f, "    %2i, // Word spacing in pixels\n", font.wordSpacing);
        fprintf(f, "    %2i, // Line spacing in pixels\n", font.lineSpacing);
        fprintf(f, "    %2i, // Baseline offset in pixels\n", font.baselineOffset);
        fprintf(f, "    %2i, // Indentation in pixels\n", font.indentation);
        fprintf(f, "    \"%s\", // Font animation name\n", font.fontName);
        fprintf(f, "    {   // Character widths");

        for (i = 0; i < CHARS; i ++)
        {
            if (i % 10 == 0) fprintf(f, "\n        ");
            if (i < CHARS - 1)fprintf(f, "%2i, ", font.fontCharWidths[i]);
            else fprintf(f, "%2i", font.fontCharWidths[i]);
        }

        fprintf(f, "\n    }\n};");

        fclose(f);
    }
}

//This function generates an SVG-file of all the characters of a given font with a given size
//fileName - the name for the SVG-file, function accepts both forms, "name.svg" and "name"
//fontName - the name of the font to be used for the characters in the SVG-file
//fontSize - the size of the font to be used for the characters in the SVG-file
void generateFontSVG(char *fileName, char *fontName, int fontSize)
{
    FILE *f = fopen(addFileExtension(fileName, "svg"), "w+");

    //Write the file
    if (f)
    {
        int i;
        char temp[6];

        fprintf(f, "<svg>\n");
        fprintf(f, "\t<rect x=\"0\" y=\"0\" height=\"%i\" ", (int)ceil(fontSize * 1.5) * CHARS);
        fprintf(f, "width=\"%i\" ", fontSize * 2);
        fprintf(f, "style=\"fill: none; stroke: none;\"/>\n");

        for (i = 0; i < CHARS; i ++)
        {
            switch((char)i + ASCII_START)
            {
                case '&': sprintf(temp, "&amp;"); break;
                case '<': sprintf(temp, "&lt;"); break;
                case '>': sprintf(temp, "&gt;"); break;
                default:
                    sprintf(temp, "%c", (char)i + ASCII_START);
                break;
            }

            fprintf(f, "\t<text x=\"%i\" ", fontSize);
            fprintf(f, "y=\"%i\" ", fontSize + (int)ceil(fontSize * 1.5) * i);
            fprintf(f, "style=\"fill: #ffffff; font-family: %s; text-anchor: middle; ", fontName);
            fprintf(f, "font-size: %ipx;\">%s</text>\n", fontSize, temp);
        }

        fprintf(f, "</svg>");

        fclose(f);
    }
}

//This function generates an SVG-file of all the characters of a given font with a given size
//The difference to the first function is, that this one places the characters in a horizontal line
//The resulting image could then also be used as an image font in Game Editor
//Currently the results are unsatisfactory, so this remains a hidden "feature"
//fileName - the name for the SVG-file, function accepts both forms, "name.svg" and "name"
//fontName - the name of the font to be used for the characters in the SVG-file
//fontSize - the size of the font to be used for the characters in the SVG-file
void generateFontSVG2(char *fileName, char *fontName, int fontSize)
{
    FILE *f = fopen(addFileExtension(fileName, "svg"), "w+");

    //Write the file
    if (f)
    {
        int i;
        char temp[6];

        fprintf(f, "<svg>\n");
        fprintf(f, "\t<rect x=\"0\" y=\"0\" height=\"%i\" ", fontSize * 2);
        fprintf(f, "width=\"%i\" ", (int)fontSize * (CHARS + 1));
        fprintf(f, "style=\"fill: none; stroke: none;\"/>\n");

        for (i = 0; i < CHARS; i ++)
        {
            switch((char)i + ASCII_START)
            {
                case '&': sprintf(temp, "&amp;"); break;
                case '<': sprintf(temp, "&lt;"); break;
                case '>': sprintf(temp, "&gt;"); break;
                default:
                    sprintf(temp, "%c", (char)i + ASCII_START);
                break;
            }

            fprintf(f, "\t<text x=\"%i\" ", (int)(fontSize * 1.5) + fontSize * i);
            fprintf(f, "y=\"%i\" ", fontSize);
            fprintf(f, "style=\"fill: #ffffff; font-family: %s; text-anchor: middle; ", fontName);
            fprintf(f, "font-size: %ipx;\">%s</text>\n", fontSize, temp);
        }

        fprintf(f, "</svg>");

        fclose(f);
    }
}