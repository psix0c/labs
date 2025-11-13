#include <stdio.h>
#include <string.h>
#include <locale.h>

void p(char *s, FILE *f) {
    char *word = strtok(s, " \n\r\t");
    int first = 1;

    while (word != NULL) {
        if (!first) {
            fprintf(f, " ");
        }

        char res[512];
        int idx = 0;
        int found = 0;
        size_t len = strlen(word);

        for (size_t i = 0; i < len;) {
            if (i + 1 < len && (unsigned char) word[i] == 0xD0 &&
                ((unsigned char) word[i + 1] == 0x90 || (unsigned char) word[i + 1] == 0xB0)) {
                found = 1;
                res[idx++] = '*';
                i += 2;
                } else {
                    res[idx++] = word[i];
                    i++;
                }
        }
        res[idx] = '\0';

        if (found) {
            fprintf(f, "<b><i>%s</i></b>", res);
        } else {
            fprintf(f, "%s", word);
        }

        first = 0;
        word = strtok(NULL, " \n\r\t");
    }
}

int main() {
    setlocale(LC_ALL, "");

    FILE *fin = fopen("input.txt", "rt");
    if (!fin) {
        perror("Ошибка открытия input.txt");
        return 1;
    }

    FILE *fout = fopen("output.html", "wt");
    if (!fout) {
        perror("Ошибка создания output.html");
        fclose(fin);
        return 1;
    }

    char line[255];

    if (fgets(line, sizeof(line), fin)) {
        line[strcspn(line, "\n\r")] = 0;

        fprintf(fout,
                "<HTML>\n<HEAD>\n"
                "<meta charset=\"UTF-8\">\n"
                "<TITLE>%s</TITLE>\n"
                "</HEAD>\n<BODY>\n<H1>", line);

        p(line, fout);
        fprintf(fout, "</H1><BR>\n");
    }


    while (fgets(line, sizeof(line), fin)) {
        line[strcspn(line, "\n\r")] = 0;
        p(line, fout);
        fprintf(fout, "<BR>\n");
    }

    fprintf(fout, "</BODY>\n</HTML>");

    fclose(fin);
    fclose(fout);

    printf("Файл output.html успешно создан.\n");

    return 0;
}